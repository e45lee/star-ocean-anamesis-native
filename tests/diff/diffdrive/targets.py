"""Targets: one client + one server, started fresh for one flow in one run directory.

  emu          build/emulator/soa-emu (the unmodified 3.7.0 client, no natives) + soa-server
  port-server  build/port/soa --server 127.0.0.1:PORT (the port's client, its own network code) + soa-server
  port-inproc  build/port/soa with the in-process server (the default --server inproc: the FakeApiCaller route)

Every run directory has the same layout, whatever the target (so tools/compare_packets.py,
tools/compare_tutorial.py and tools/server_state.py read any of them):
  client.log (+ emu.log, a link: compare_tutorial.py's name), server.log (soa-server's; the
  in-process server logs into client.log), packets/packets.log (soa-server --log-packets, or soa
  --log-packets for the in-process route) with the bodies, server/server.sqlite3 (the state),
  shots/NN-name.png, state-TAG.txt, milestones.txt. The phone (a link of the shared pre-downloaded
  phone, scripts/shared-phone.sh) is phone/, deleted at the end unless kept.
"""
import os
import re
import shutil
import subprocess
import sys
import time

from . import fifo, prepared, proc, screens
from .proc import REPO

sys.path.insert(0, os.path.join(REPO, "control"))
import soaslot  # noqa: E402  (control/soaslot.py: the machine-wide game-process slot pool)

TARGETS = ("emu", "port-server", "port-inproc")
W, H = 729, 1296


class Abort(Exception):
    """A milestone the flow can't go on without was missed."""


class Config:
    """What a flow asks of its targets: the server's options (the same for every target), whether
    the client save goes on the phone, and the clock both sides start at."""

    def __init__(self, server_args, clock, client_save=False, new_player=False, prepared=None):
        self.server_args, self.clock, self.client_save, self.new_player = list(server_args), clock, client_save, new_player
        # a prepared server state (diffdrive/prepared.py: a state DB every target starts from a
        # copy of), or None: a fresh state
        self.prepared = prepared


def binaries():
    return {
        "soa": os.environ.get("SOA", os.path.join(REPO, "build/port/soa")),
        "emu": os.environ.get("SOA_EMU", os.path.join(REPO, "build/emulator/soa-emu")),
        "server": os.environ.get("SOA_SERVER", os.path.join(REPO, "build/server/soa-server")),
    }


def make_phone(dst):
    """The run's phone: the shared pre-downloaded phone linked (SOA_PHONE as the session scripts
    take it: unset = the shared phone, none = empty, DIR = that phone). Returns a note."""
    r = subprocess.run(["bash", "-c", '. scripts/shared-phone.sh; shared_phone_resolve "$1"; '
                        'if [ -n "$SOA_PHONE" ]; then shared_phone_link "$SOA_PHONE" "$2" && echo "linked from $SOA_PHONE"; '
                        'else mkdir -p "$2"; echo "empty (the client downloads)"; fi', "-", REPO, dst],
                       cwd=REPO, capture_output=True, text=True)
    if r.returncode != 0:
        raise Abort("preparing the phone: " + (r.stdout + r.stderr).strip()[-300:])
    os.makedirs(os.path.join(dst, "data", "shared_prefs"), exist_ok=True)
    aska = os.path.join(dst, "data", "shared_prefs", "Aska.xml")
    if os.path.exists(aska):
        os.remove(aska)
    return r.stdout.strip().splitlines()[-1] if r.stdout.strip() else ""


class Run:
    """One target running one flow. The flow drives it through these helpers; milestones are read
    from the packet log (every target has one), the client's log and the server's state."""

    def __init__(self, target, rdir, cfg, keep=False):
        assert target in TARGETS, target
        self.target, self.dir, self.cfg, self.keep = target, rdir, cfg, keep
        self.fifo = os.path.join(rdir, "fifo")
        self.client_log = os.path.join(rdir, "client.log")
        self.server_log = os.path.join(rdir, "server.log") if target != "port-inproc" else self.client_log
        self.packets = os.path.join(rdir, "packets", "packets.log")
        self.state_db = os.path.join(rdir, "server", "server.sqlite3")
        self.shots = os.path.join(rdir, "shots")
        self.phone = os.path.join(rdir, "phone")
        self.server = self.client = None
        self.slot = -1
        self.results, self.failed, self.t0 = [], False, time.monotonic()
        self.shot_names = []

    # ---- lifecycle --------------------------------------------------------------------------
    def start(self):
        if os.path.isdir(self.dir):
            shutil.rmtree(self.dir)
        for d in ("packets", "server", "shots"):
            os.makedirs(os.path.join(self.dir, d))
        # The client's slot (control/soaslot.py): queued here, before anything starts; the run's
        # clock starts once it has one.
        t = time.monotonic()
        self.slot = soaslot.acquire("tests/diff %s %s" % (os.path.basename(os.path.dirname(self.dir)), self.target), quiet=True)
        self.queued = int(time.monotonic() - t)
        self.t0 = time.monotonic()
        if self.queued:
            self.note("waited %ds for a game slot (control/soaslot.py)" % self.queued)
        b = binaries()
        master = proc.repo_file("data/basmaster-3.7.0.sqlite3")
        download = proc.repo_file("work/download-3.7.0")
        if not master or not download:
            raise Abort("data/basmaster-3.7.0.sqlite3 or work/download-3.7.0 not found")
        self.note("phone: " + make_phone(self.phone))
        if self.cfg.prepared:
            shutil.copyfile(self.cfg.prepared, self.state_db)
            # the side files go to the server's data dir: soa-server's --data, soa's --data (the phone)
            side_dir = self.phone if self.target == "port-inproc" else os.path.dirname(self.state_db)
            for f in prepared.side_files(self.cfg.prepared):
                shutil.copyfile(f, os.path.join(side_dir, os.path.basename(f)))
            self.note("server state: a copy of %s%s" % (self.cfg.prepared,
                      " (and %s)" % ", ".join(os.path.basename(f) for f in prepared.side_files(self.cfg.prepared))
                      if prepared.side_files(self.cfg.prepared) else ""))
        if self.cfg.client_save:
            shutil.copyfile(os.path.join(REPO, "data/saves/client/Game.xml"), os.path.join(self.phone, "data/shared_prefs/Game.xml"))
        srv = ["--master", master, "--seed-rng", "1", "--clock", self.cfg.clock] + self.cfg.server_args
        if not self.cfg.new_player:
            srv += ["--seed", os.path.join(REPO, "data/saves/seed/Game.xml")]
        client = ["--data", self.phone, "--headless", "--size", "%dx%d" % (W, H), "--control", self.fifo,
                  "--device-clock", self.cfg.clock]
        env = {"SDL_AUDIODRIVER": os.environ.get("SDL_AUDIODRIVER", "dummy")}
        if self.target == "port-inproc":
            self.client = proc.Proc("soa", [b["soa"]] + client + srv + ["--db", self.state_db, "--download-dir", download,
                                                                      "--log-packets", os.path.dirname(self.packets)],
                                    self.client_log, env=env, slot_fd=self.slot)
        else:
            gp, hp = proc.free_ports(2)
            self.server = proc.Proc("soa-server", [b["server"], "--listen", "127.0.0.1:%d" % gp, "--http", "127.0.0.1:%d" % hp,
                                                   "--data", os.path.dirname(self.state_db), "--download-dir", download,
                                                   "--log-packets", os.path.dirname(self.packets)] + srv, self.server_log)
            end = time.monotonic() + 120
            while not self.grep(self.server_log, r"^soa-server: game"):
                if not self.server.running() or time.monotonic() > end:
                    raise Abort("soa-server didn't start (see %s)" % self.server_log)
                time.sleep(0.5)
            binary = b["emu"] if self.target == "emu" else b["soa"]
            self.client = proc.Proc(os.path.basename(binary), [binary] + client +
                                    ["--server", "127.0.0.1:%d" % gp, "--http", "127.0.0.1:%d" % hp], self.client_log, env=env,
                                    slot_fd=self.slot)
        os.symlink("client.log", os.path.join(self.dir, "emu.log"))
        end = time.monotonic() + 120
        while not os.path.exists(self.fifo):
            if not self.client.running() or time.monotonic() > end:
                raise Abort("the client didn't open its control FIFO (see %s)" % self.client_log)
            time.sleep(0.5)

    def stop(self):
        if self.client and self.client.running():
            fifo.send(self.fifo, ["quit"], timeout=10)
            self.client.wait(15)
        for p in (self.client, self.server):
            if p:
                p.stop()
        soaslot.release(self.slot)
        self.slot = -1
        if self.grep(self.client_log, r"Unhandled SIG|\*\*\* host signal"):
            # a crash whose backtrace is in the host's GPU driver (WSL's NVIDIA GL, seen once with
            # many clients at once) is the host's, not the game's: labelled so
            host = self.grep(self.client_log, r"^/usr/lib/wsl/drivers/|libnvwgf2umx|libnvidia-gl|libGLX_nvidia|d3d12_dri")
            self.miss("the client crashed%s (see %s)" % (" in the host GPU driver" if host else "", self.client_log))
        if self.grep(self.client_log, r"glx: failed to create|X Error of failed request"):
            self.note("the host's GL/GLX failed for this client (see %s): a host problem, not the game's" % self.client_log)
        if os.path.exists(self.state_db):
            self.state("end")
        if not self.keep and os.path.isdir(self.phone):
            shutil.rmtree(self.phone, ignore_errors=True)
        with open(os.path.join(self.dir, "milestones.txt"), "w") as f:
            f.write("\n".join(self.results) + "\n" + ("FAIL" if self.failed else "PASS") + "\n")

    def alive(self):
        return self.client is not None and self.client.alive() and (self.server is None or self.server.running())

    # ---- recording ----------------------------------------------------------------------------
    def elapsed(self):
        return int(time.monotonic() - self.t0)

    def _rec(self, s):
        self.results.append(s)
        print("[%s %s] %s" % (os.path.basename(os.path.dirname(self.dir)), self.target, s), flush=True)

    def ok(self, name):
        self._rec("PASS  %s (%ds)" % (name, self.elapsed()))

    def miss(self, name):
        self.failed = True
        self._rec("FAIL  %s (%ds)" % (name, self.elapsed()))
        # what the screen showed (the failure's evidence)
        if self.client is not None and self.client.running():
            self.send(["shot:" + os.path.join(self.dir, "fail-%02d.png" % len(self.results))], timeout=20)

    def note(self, s):
        self._rec("note  " + s)

    def check(self, name, cond):
        (self.ok if cond else self.miss)(name)
        return cond

    # ---- driving ------------------------------------------------------------------------------
    def send(self, cmds, timeout=120):
        return fifo.send(self.fifo, cmds, timeout)

    def ctl(self, *cmds):
        return self.send(list(cmds))

    def shot(self, name, settle=True):
        """shots/NAME.png, settled (screens.settled_shot) unless settle=False."""
        path = os.path.join(self.shots, name + ".png")
        if settle:
            screens.settled_shot(self.send, path)
        else:
            self.send(["shot:" + path])
        if os.path.exists(path):
            self.shot_names.append(name)
        else:
            self.note("screenshot %s not taken" % name)
        return path

    def keep_shot(self, name, src):
        dst = os.path.join(self.shots, name + ".png")
        if os.path.exists(src):
            shutil.copyfile(src, dst)
            self.shot_names.append(name)
        return dst

    def scratch(self, name):
        return os.path.join(self.dir, name)

    # ---- milestones ---------------------------------------------------------------------------
    @staticmethod
    def grep(path, rx):
        try:
            with open(path, errors="replace") as f:
                return re.search(rx, f.read(), re.M) is not None
        except FileNotFoundError:
            return False

    @staticmethod
    def count(path, rx):
        try:
            with open(path, errors="replace") as f:
                return len(re.findall(rx, f.read(), re.M))
        except FileNotFoundError:
            return 0

    def in_packets(self, rx):
        return self.grep(self.packets, rx)

    def n_packets(self, rx):
        return self.count(self.packets, rx)

    def in_client(self, rx):
        return self.grep(self.client_log, rx)

    def in_server(self, rx):
        return self.grep(self.server_log, rx)

    def poll(self, secs, pred):
        end = time.monotonic() + secs
        while not pred():
            if not self.alive() or time.monotonic() > end:
                return False
            time.sleep(1)
        return True

    def wait_for(self, name, secs, pred, fatal=True):
        """Waits until pred(); PASS or FAIL for name (FAIL + Abort when fatal)."""
        end = time.monotonic() + secs
        while not pred():
            if not self.alive():
                self.miss(name + " (the client exited)")
                raise Abort(name)
            if time.monotonic() > end:
                self.miss("%s (not within %ds)" % (name, secs))
                if fatal:
                    raise Abort(name)
                return False
            time.sleep(1)
        self.ok(name)
        return True

    def tap_until(self, name, secs, xy, pred, every=4, fatal=True):
        """Taps xy every `every` s until pred() (a tap can be lost while a screen fades in)."""
        end, nxt = time.monotonic() + secs, 0
        while not pred():
            if not self.alive():
                self.miss(name + " (the client exited)")
                raise Abort(name)
            if time.monotonic() > end:
                self.miss("%s (not within %ds)" % (name, secs))
                if fatal:
                    raise Abort(name)
                return False
            if time.monotonic() >= nxt:
                self.ctl("tap:" + xy)
                nxt = time.monotonic() + every
            time.sleep(1)
        self.ok(name)
        return True

    def more_than(self, rx, n):
        return lambda: self.n_packets(rx) > n

    # ---- the server's state -----------------------------------------------------------------------
    def state(self, tag):
        out = os.path.join(self.dir, "state-%s.txt" % tag)
        db = proc.repo_file("data/basmaster-3.7.0.sqlite3")
        r = subprocess.run(["python3", os.path.join(REPO, "tools/server_state.py"), self.state_db] + (["--db", db] if db else []),
                           capture_output=True, text=True)
        with open(out, "w") as f:
            f.write(r.stdout + r.stderr)
        return r.stdout
