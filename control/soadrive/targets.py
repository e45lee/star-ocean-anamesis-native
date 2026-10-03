"""Targets: one client + one server, started fresh for one flow or session.

  emu          build/emulator/soa-emu (the unmodified 3.7.0 client, no natives) + soa-server
  port-server  build/port/soa --server 127.0.0.1:PORT (the port's client, its own network code) + soa-server
  port-inproc  build/port/soa with the in-process server (the default --server inproc: the FakeApiCaller route)

Where a run's files go is its Layout:
  Layout.diff(RDIR)            tests/diff's run directory, the same whatever the target (so
                               tools/compare_packets.py, compare_tutorial.py and server_state.py read
                               any of them): client.log (+ emu.log, a link: compare_tutorial.py's
                               name), server.log (soa-server's; the in-process server logs into
                               client.log), packets/packets.log (soa-server --log-packets, or soa
                               --log-packets for the in-process route) with the bodies,
                               server/server.sqlite3 (the state), shots/NN-name.png, state-TAG.txt,
                               milestones.txt; the phone (a link of the shared pre-downloaded phone,
                               scripts/shared-phone.sh) is phone/, deleted at the end unless kept.
  Layout.port_session(OUT, TMP)  the port's session scripts' (port/scripts/*_session.sh): OUT/log.txt
                               (+ log.txt.pos, the wait cursor), OUT/shots/NN-name.png,
                               OUT/state-TAG.txt, OUT/packets/packets.log, OUT/steps.txt; the phone
                               TMP/data (kept: scripts/make-phone-370.sh takes it), the in-process
                               server's state TMP/data/server.sqlite3, the FIFO TMP/fifo.
  Layout.emu_session(OUT, PHONE) emulator/scripts/emulator_session.sh's: OUT/emu.log, OUT/server.log,
                               OUT/packets/packets.log, OUT/server/server.sqlite3, OUT/NAME.png,
                               OUT/state-TAG.txt, OUT/steps.txt, the phone OUT/emu (its data/
                               deleted at the end unless kept) or a given one (EMU_DATA, never deleted).
A session can rename screenshots (Layout.shot_names) so that its files keep the names other tools
read (tools/compare_tutorial.py, tests/tutorial_milestones.txt).
"""
import os
import re
import shutil
import subprocess
import sys
import time

from . import fifo, milestones, prepared, proc, screens
from .proc import REPO

sys.path.insert(0, os.path.join(REPO, "control"))
import soaslot  # noqa: E402  (control/soaslot.py: the machine-wide game-process slot pool)

TARGETS = ("emu", "port-server", "port-inproc")
W, H = 729, 1296


class Abort(Exception):
    """A milestone the flow can't go on without was missed."""


class Config:
    """What a flow asks of its targets: the server's options (the same for every target), whether
    the client save goes on the phone, and the clock both sides start at. The keyword options are
    the sessions' (the defaults are tests/diff's):
      seed          None: data/saves/seed/Game.xml unless new_player (tests/diff); False: no --seed
                    (the server's own default); a path: that save
      seed_rng      --seed-rng N (None: not passed)
      client_save   False, True (the committed client save, copied), or "session" (as the port's
                    sessions install it: BAS:DownloadEpisodeFlag 0 unless SOA_EPISODE_PACKS=1)
      client_args   extra client options (e.g. a session's pass-through soa flags)
      env           extra environment for the client (e.g. SOA_TRACE)
      limit         the client's and server's `timeout` (seconds)
      windowed      --windowed instead of --headless (WATCH=1)
      explicit_data pass --master / --download-dir (and --db) to the in-process route too (soa-server
                    always gets them)
      log_packets   --log-packets (the packet log: milestones every target has)
      state_master  tools/server_state.py --db the master (names in the dumps)
      fresh_kvs     delete the phone's local KVS (Aska.xml: the client makes a new device UUID)
      phone         a phone directory to use as it is (EMU_DATA): never prepared nor deleted
      binary        the client binary (default by target: SOA / SOA_EMU), server_binary (SOA_SERVER)
    """

    def __init__(self, server_args=(), clock=None, client_save=False, new_player=False, prepared=None, seed=None,
                 seed_rng=1, client_args=(), env=None, limit=3600, windowed=False, explicit_data=True, log_packets=True,
                 state_master=True, fresh_kvs=True, phone=None, binary=None, server_binary=None):
        self.server_args, self.clock, self.client_save, self.new_player = list(server_args), clock, client_save, new_player
        # a prepared server state (soadrive/prepared.py: a state DB every target starts from a
        # copy of), or None: a fresh state
        self.prepared = prepared
        self.seed, self.seed_rng, self.client_args, self.env = seed, seed_rng, list(client_args), dict(env or {})
        self.limit, self.windowed, self.explicit_data, self.log_packets = limit, windowed, explicit_data, log_packets
        self.state_master, self.fresh_kvs, self.phone = state_master, fresh_kvs, phone
        self.binary, self.server_binary = binary, server_binary


def binaries():
    return {
        "soa": os.environ.get("SOA", os.path.join(REPO, "build/port/soa")),
        "emu": os.environ.get("SOA_EMU", os.path.join(REPO, "build/emulator/soa-emu")),
        "server": os.environ.get("SOA_SERVER", os.path.join(REPO, "build/server/soa-server")),
    }


def make_phone(dst, fresh_kvs=True):
    """The run's phone: the shared pre-downloaded phone linked (SOA_PHONE as the session scripts
    take it: unset = the shared phone, none = empty, DIR = that phone). Returns (a note, whether the
    data is on it)."""
    if os.path.isdir(dst):
        shutil.rmtree(dst)
    r = subprocess.run(["bash", "-c", '. scripts/shared-phone.sh; shared_phone_resolve "$1"; '
                        'if [ -n "$SOA_PHONE" ]; then shared_phone_link "$SOA_PHONE" "$2" && echo "linked from $SOA_PHONE"; '
                        'else mkdir -p "$2"; echo "empty (the client downloads)"; fi', "-", REPO, dst],
                       cwd=REPO, capture_output=True, text=True)
    if r.returncode != 0:
        raise Abort("preparing the phone: " + (r.stdout + r.stderr).strip()[-300:])
    os.makedirs(os.path.join(dst, "data", "shared_prefs"), exist_ok=True)
    aska = os.path.join(dst, "data", "shared_prefs", "Aska.xml")
    if fresh_kvs and os.path.exists(aska):
        os.remove(aska)
    note = r.stdout.strip().splitlines()[-1] if r.stdout.strip() else ""
    return note, note.startswith("linked")


def session_client_save(shared_prefs):
    """The committed client save (data/saves/client/Game.xml) as the port's sessions install it
    (port/scripts/phone370.sh phone370_client_save): BAS:DownloadEpisodeFlag 0, so no episode pack
    is on the client's books (SOA_EPISODE_PACKS=1 keeps the save's flag)."""
    os.makedirs(shared_prefs, exist_ok=True)
    src, dst = os.path.join(REPO, "data/saves/client/Game.xml"), os.path.join(shared_prefs, "Game.xml")
    if os.environ.get("SOA_EPISODE_PACKS", "0") == "1":
        shutil.copyfile(src, dst)
        return
    py = os.path.join(REPO, ".venv/bin/python")
    r = subprocess.run([py if os.path.exists(py) else sys.executable, "-m", "soa_save", "set", "--type", "u32", src,
                        "BAS:DownloadEpisodeFlag", "0", "-o", dst], cwd=REPO, capture_output=True, text=True)
    if r.returncode != 0:
        raise Abort("installing the client save: " + (r.stdout + r.stderr).strip()[-300:])


class Layout:
    """Where a run's files go (the module's doc). style: how steps are printed: "milestones"
    (PASS  name / FAIL  name lines: tests/diff, the emulator sessions) or "steps" (ok name /
    FAIL: name: the port sessions, whose only PASS line is the verdict)."""

    def __init__(self, kind, out, fifo, client_log, server_log, packets, state_db, shots, phone, state_dir, steps,
                 style="milestones", shot_names=None, flat_shots=False, phone_cleanup=None, state_end=True,
                 inproc_db_default=False):
        self.kind, self.out, self.fifo, self.client_log, self.server_log = kind, out, fifo, client_log, server_log
        self.packets, self.state_db, self.shots, self.phone, self.state_dir = packets, state_db, shots, phone, state_dir
        self.steps, self.style, self.shot_names, self.flat_shots = steps, style, dict(shot_names or {}), flat_shots
        self.phone_cleanup, self.state_end, self.inproc_db_default = phone_cleanup, state_end, inproc_db_default

    @staticmethod
    def diff(rdir, target):
        return Layout("diff", rdir, os.path.join(rdir, "fifo"), os.path.join(rdir, "client.log"),
                      os.path.join(rdir, "server.log") if target != "port-inproc" else os.path.join(rdir, "client.log"),
                      os.path.join(rdir, "packets", "packets.log"), os.path.join(rdir, "server", "server.sqlite3"),
                      os.path.join(rdir, "shots"), os.path.join(rdir, "phone"), rdir, os.path.join(rdir, "milestones.txt"),
                      phone_cleanup=os.path.join(rdir, "phone"))

    @staticmethod
    def port_session(out, tmp, target="port-inproc", shot_names=None):
        phone = os.path.join(tmp, "data")
        inproc = target == "port-inproc"
        return Layout("port-session", out, os.path.join(tmp, "fifo"), os.path.join(out, "log.txt"),
                      os.path.join(out, "log.txt") if inproc else os.path.join(out, "server.log"),
                      os.path.join(out, "packets", "packets.log"),
                      os.path.join(phone, "server.sqlite3") if inproc else os.path.join(tmp, "server", "server.sqlite3"),
                      os.path.join(out, "shots"), phone, out, os.path.join(out, "steps.txt"), style="steps",
                      shot_names=shot_names, state_end=False, inproc_db_default=inproc)

    @staticmethod
    def emu_session(out, phone=None, target="emu", shot_names=None):
        inproc = target == "port-inproc"
        return Layout("emu-session", out, os.path.join(out, "fifo"), os.path.join(out, "emu.log"),
                      os.path.join(out, "emu.log") if inproc else os.path.join(out, "server.log"),
                      os.path.join(out, "packets", "packets.log"), os.path.join(out, "server", "server.sqlite3"), out,
                      phone or os.path.join(out, "emu"), out, os.path.join(out, "steps.txt"), shot_names=shot_names,
                      flat_shots=True, phone_cleanup=None if phone else os.path.join(out, "emu", "data"))

    def shot_path(self, name):
        return os.path.join(self.shots, self.shot_names.get(name, name) + ".png")

    def prepare(self):
        """A fresh start: tests/diff's run dir is recreated; a session's own files are removed
        (other files in OUT stay, as the shell sessions left them)."""
        if self.kind == "diff":
            if os.path.isdir(self.out):
                shutil.rmtree(self.out)
        else:
            for p in (self.fifo, self.client_log, self.client_log + ".pos", self.steps):
                if os.path.lexists(p):
                    os.remove(p)
            for d in (os.path.dirname(self.packets),) + ((self.shots,) if not self.flat_shots else ()):
                if os.path.isdir(d):
                    shutil.rmtree(d)
            if os.path.isdir(self.state_dir):
                for f in os.listdir(self.state_dir):
                    if f.startswith("state-") and f.endswith(".txt"):
                        os.remove(os.path.join(self.state_dir, f))
        for d in (os.path.dirname(self.packets), os.path.dirname(self.state_db), self.shots, os.path.dirname(self.fifo)):
            os.makedirs(d, exist_ok=True)


class Run:
    """One target running one flow or session. The flow drives it through these helpers;
    milestones are read from the packet log (every target has one), the client's log (whole-file
    predicates, or the cursor: wait_log / tap_log) and the server's state.

    Run(target, RDIR, cfg) is tests/diff's (Layout.diff); Run(target, Layout..., cfg) a session's.
    slot: a game slot the caller holds (control/soaslot.py) for the client; None: the run takes one."""

    def __init__(self, target, where, cfg, keep=False, slot=None, prefix=None):
        assert target in TARGETS, target
        lay = where if isinstance(where, Layout) else Layout.diff(where, target)
        self.target, self.layout, self.cfg, self.keep = target, lay, cfg, keep
        self.dir = lay.out
        self.fifo, self.client_log, self.server_log, self.packets = lay.fifo, lay.client_log, lay.server_log, lay.packets
        self.state_db, self.shots, self.phone = lay.state_db, lay.shots, lay.phone
        self.server = self.client = None
        self.slot, self.own_slot = (slot, False) if slot is not None else (-1, True)
        self.queued = 0
        self.results, self.failed, self.t0 = [], False, time.monotonic()
        self.shot_names = []
        self.predownloaded = False
        self.ctl_timeout = 120 if lay.kind == "diff" else 400
        self._cursor = None
        # called after the phone and the client save are in place, before anything starts (a
        # session's own files on the phone)
        self.before_client = None
        if prefix is None:
            prefix = "[%s %s] " % (os.path.basename(os.path.dirname(lay.out)), target) if lay.kind == "diff" else ""
        self.prefix = prefix

    # ---- lifecycle --------------------------------------------------------------------------
    def start(self):
        lay, cfg = self.layout, self.cfg
        lay.prepare()
        # The client's slot (control/soaslot.py): queued here, before anything starts; the run's
        # clock starts once it has one.
        if self.own_slot:
            t = time.monotonic()
            name = ("tests/diff %s %s" % (os.path.basename(os.path.dirname(self.dir)), self.target) if lay.kind == "diff"
                    else "%s %s" % (lay.kind, self.target))
            self.slot = soaslot.acquire(name, quiet=True)
            self.queued = int(time.monotonic() - t)
        self.t0 = time.monotonic()
        if self.queued:
            self.note("waited %ds for a game slot (control/soaslot.py)" % self.queued)
        b = binaries()
        master = proc.repo_file("data/basmaster-3.7.0.sqlite3")
        download = proc.repo_file("work/download-3.7.0")
        server_side = self.target != "port-inproc"
        if (cfg.explicit_data or server_side) and (not master or not download):
            raise Abort("data/basmaster-3.7.0.sqlite3 or work/download-3.7.0 not found")
        if cfg.phone:
            os.makedirs(self.phone, exist_ok=True)
            if cfg.fresh_kvs and os.path.exists(os.path.join(self.phone, "data/shared_prefs/Aska.xml")):
                os.remove(os.path.join(self.phone, "data/shared_prefs/Aska.xml"))
            self.predownloaded = True
            self.note("phone: %s (as it is)" % self.phone)
        else:
            t = time.monotonic()
            note, self.predownloaded = make_phone(self.phone, cfg.fresh_kvs)
            self.note("phone: %s (%d ms)" % (note, int((time.monotonic() - t) * 1000)))
        if cfg.prepared:
            shutil.copyfile(cfg.prepared, self.state_db)
            # the side files go to the server's data dir: soa-server's --data, soa's --data (the phone)
            side_dir = self.phone if self.target == "port-inproc" else os.path.dirname(self.state_db)
            for f in prepared.side_files(cfg.prepared):
                shutil.copyfile(f, os.path.join(side_dir, os.path.basename(f)))
            self.note("server state: a copy of %s%s" % (cfg.prepared,
                      " (and %s)" % ", ".join(os.path.basename(f) for f in prepared.side_files(cfg.prepared))
                      if prepared.side_files(cfg.prepared) else ""))
        if cfg.client_save == "session":
            session_client_save(os.path.join(self.phone, "data/shared_prefs"))
        elif cfg.client_save:
            shutil.copyfile(os.path.join(REPO, "data/saves/client/Game.xml"), os.path.join(self.phone, "data/shared_prefs/Game.xml"))
        if self.before_client:
            self.before_client()
        srv = []
        if cfg.explicit_data or server_side:
            srv += ["--master", master]
        if cfg.seed_rng is not None:
            srv += ["--seed-rng", str(cfg.seed_rng)]
        if cfg.clock:
            srv += ["--clock", cfg.clock]
        srv += cfg.server_args
        if cfg.seed is None and not cfg.new_player:
            srv += ["--seed", os.path.join(REPO, "data/saves/seed/Game.xml")]
        elif cfg.seed:
            srv += ["--seed", cfg.seed]
        client = ["--data", self.phone, "--windowed" if cfg.windowed else "--headless", "--size", "%dx%d" % (W, H),
                  "--control", self.fifo]
        if cfg.clock:
            client += ["--device-clock", cfg.clock]
        env = {"SDL_AUDIODRIVER": os.environ.get("SDL_AUDIODRIVER", "dummy")}
        env.update(cfg.env)
        pkt = ["--log-packets", os.path.dirname(self.packets)] if cfg.log_packets else []
        if self.target == "port-inproc":
            extra = []
            if cfg.explicit_data or not self.layout.inproc_db_default:
                extra += ["--db", self.state_db]
            if cfg.explicit_data:
                extra += ["--download-dir", download]
            binary = cfg.binary or b["soa"]
            self.client = proc.Proc("soa", [binary] + client + cfg.client_args + srv + extra + pkt, self.client_log,
                                    limit=cfg.limit, env=env, slot_fd=self.slot)
        else:
            gp, hp = proc.free_ports(2)
            self.server = proc.Proc("soa-server", [cfg.server_binary or b["server"], "--listen", "127.0.0.1:%d" % gp,
                                                   "--http", "127.0.0.1:%d" % hp, "--data", os.path.dirname(self.state_db),
                                                   "--download-dir", download] + pkt + srv, self.server_log, limit=cfg.limit)
            end = time.monotonic() + 120
            while not self.grep(self.server_log, r"^soa-server: game"):
                if not self.server.running() or time.monotonic() > end:
                    raise Abort("soa-server didn't start (see %s)" % self.server_log)
                time.sleep(0.5)
            binary = cfg.binary or (b["emu"] if self.target == "emu" else b["soa"])
            self.client = proc.Proc(os.path.basename(binary), [binary] + client + cfg.client_args +
                                    ["--server", "127.0.0.1:%d" % gp, "--http", "127.0.0.1:%d" % hp], self.client_log, env=env,
                                    limit=cfg.limit, slot_fd=self.slot)
        emu_link = os.path.join(self.dir, "emu.log")
        if self.layout.kind == "diff" and not os.path.lexists(emu_link):
            os.symlink("client.log", emu_link)
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
        if self.own_slot:
            soaslot.release(self.slot)
            self.slot = -1
        if self.grep(self.client_log, r"Unhandled SIG|\*\*\* host signal"):
            # a crash whose backtrace is in the host's GPU driver (WSL's NVIDIA GL, seen once with
            # many clients at once) is the host's, not the game's: labelled so
            host = self.grep(self.client_log, r"^/usr/lib/wsl/drivers/|libnvwgf2umx|libnvidia-gl|libGLX_nvidia|d3d12_dri")
            self.miss("the client crashed%s (see %s)" % (" in the host GPU driver" if host else "", self.client_log))
        if self.grep(self.client_log, r"glx: failed to create|X Error of failed request"):
            self.note("the host's GL/GLX failed for this client (see %s): a host problem, not the game's" % self.client_log)
        if self.layout.state_end and os.path.exists(self.state_db):
            self.state("end")
        cleanup = self.layout.phone_cleanup
        if cleanup and not self.keep and os.path.isdir(cleanup):
            shutil.rmtree(cleanup, ignore_errors=True)
        with open(self.layout.steps, "w") as f:
            f.write("\n".join(self.results) + "\n" + ("FAIL" if self.failed else "PASS") + "\n")

    def alive(self):
        return self.client is not None and self.client.alive() and (self.server is None or self.server.running())

    # ---- recording ----------------------------------------------------------------------------
    def elapsed(self):
        return int(time.monotonic() - self.t0)

    def _rec(self, s, shown=None):
        self.results.append(s)
        print(self.prefix + (shown if shown is not None else s), flush=True)

    def ok(self, name):
        s = "PASS  %s (%ds)" % (name, self.elapsed())
        self._rec(s, "ok %s (%ds)" % (name, self.elapsed()) if self.layout.style == "steps" else None)

    def miss(self, name):
        self.failed = True
        self._rec("FAIL  %s (%ds)" % (name, self.elapsed()), "FAIL: %s" % name if self.layout.style == "steps" else None)
        # what the screen showed (the failure's evidence)
        if self.client is not None and self.client.running():
            self.send(["shot:" + os.path.join(self.dir, "fail-%02d.png" % len(self.results))], timeout=20)

    def note(self, s):
        self._rec("note  " + s, "note: " + s if self.layout.style == "steps" else None)

    def check(self, name, cond):
        (self.ok if cond else self.miss)(name)
        return cond

    def fail(self, name):
        """A step the session can't go on without: FAIL and stop (Abort)."""
        self.miss(name)
        raise Abort(name)

    # ---- driving ------------------------------------------------------------------------------
    def send(self, cmds, timeout=None):
        return fifo.send(self.fifo, cmds, self.ctl_timeout if timeout is None else timeout)

    def ctl(self, *cmds):
        return self.send(list(cmds))

    def shot(self, name, settle=None):
        """The screenshot NAME (the layout's path), settled (screens.settled_shot) unless settle is
        False; settle=None: settled in tests/diff, as is in a session (its waits are explicit)."""
        if settle is None:
            settle = self.layout.kind == "diff"
        path = self.layout.shot_path(name)
        if settle:
            screens.settled_shot(self.send, path)
        else:
            self.send(["shot:" + path])
        if os.path.exists(path):
            self.shot_names.append(name)
        else:
            self.note("screenshot %s not taken" % name)
        return path

    def shot_cmd(self, name):
        """The FIFO command that takes the screenshot NAME (for a batch: ctl("wait:3000", s.shot_cmd(...)))."""
        self.shot_names.append(name)
        return "shot:" + self.layout.shot_path(name)

    def keep_shot(self, name, src):
        dst = self.layout.shot_path(name)
        if os.path.exists(src):
            shutil.copyfile(src, dst)
            self.shot_names.append(name)
        return dst

    def scratch(self, name):
        return os.path.join(self.dir, name)

    # ---- milestones (soadrive/milestones.py) --------------------------------------------------------
    grep = staticmethod(milestones.grep)
    count = staticmethod(milestones.count)

    def in_packets(self, rx):
        return self.grep(self.packets, rx)

    def n_packets(self, rx):
        return self.count(self.packets, rx)

    def in_client(self, rx):
        return self.grep(self.client_log, rx)

    def in_server(self, rx):
        return self.grep(self.server_log, rx)

    def poll(self, secs, pred):
        return milestones.poll(secs, pred, alive=self.alive)

    def _wait(self, name, secs, pred, fatal, action=None, every=4):
        if milestones.poll(secs, pred, alive=self.alive, action=action, every=every):
            self.ok(name)
            return True
        if not self.alive():
            self.miss(name + " (the client exited)")
            raise Abort(name)
        self.miss("%s (not within %ds)" % (name, secs))
        if fatal:
            raise Abort(name)
        return False

    def wait_for(self, name, secs, pred, fatal=True):
        """Waits until pred(); PASS or FAIL for name (FAIL + Abort when fatal)."""
        return self._wait(name, secs, pred, fatal)

    def tap_until(self, name, secs, xy, pred, every=4, fatal=True):
        """Taps xy every `every` s until pred() (a tap can be lost while a screen fades in)."""
        return self._wait(name, secs, pred, fatal, action=lambda: self.ctl("tap:" + xy), every=every)

    def more_than(self, rx, n):
        return lambda: self.n_packets(rx) > n

    def _missed(self, name, why, fatal):
        """fatal True / False: a FAIL (Abort when True); None: an optional step, only noted."""
        if fatal is None:
            self.note("%s (%s)" % (name, why))
        else:
            self.miss("%s (%s)" % (name, why))

    # the client log's cursor (LOG.pos: the port sessions' `flowctl.py wait-log` chain)
    @property
    def cursor(self):
        if self._cursor is None:
            self._cursor = milestones.LogCursor(self.client_log)
        return self._cursor

    def wait_log(self, rx, secs=120, name=None, fatal=True):
        """The next client-log line matching rx after the previous cursor wait (flowctl.py wait-log):
        PASS / FAIL for name (default: the pattern); the line, or None (Abort when fatal; fatal=None:
        an optional step, noted, not failed)."""
        line = self.cursor.wait(rx, secs, alive=self.alive)
        if line is not None:
            self.ok(name or line)
            return line
        why = "the client exited" if not self.alive() else "not within %ds" % secs
        self._missed(name or "no log line matching %r" % rx, why, fatal)
        if fatal:
            raise Abort(name or rx)
        return None

    def tap_log(self, rx, secs, every, tries, *cmds, name=None, fatal=True, stop=milestones.PORT_PHASE):
        """cmds, resent until rx is logged (flowctl.py tap-until: every `every` s, at most `tries`
        sends, no resend once another phase began)."""
        line, sent = milestones.tap_until_log(lambda c: self.send(c), self.cursor, rx, secs, every, tries, cmds, stop=stop,
                                              note=lambda m: print(self.prefix + m, file=sys.stderr, flush=True),
                                              alive=self.alive)
        if line is not None:
            self.ok(name or line)
            return line
        why = "the client exited" if not self.alive() else "not within %ds, %d x %s" % (secs, sent, " ".join(cmds))
        self._missed(name or "no log line matching %r" % rx, why, fatal)
        if fatal:
            raise Abort(name or rx)
        return None

    # ---- the server's state -----------------------------------------------------------------------
    def state(self, tag):
        """state-TAG.txt: tools/server_state.py's dump of the server's state (its text)."""
        out = os.path.join(self.layout.state_dir, "state-%s.txt" % tag)
        db = proc.repo_file("data/basmaster-3.7.0.sqlite3") if self.cfg.state_master else None
        py = os.path.join(REPO, ".venv/bin/python")
        r = subprocess.run([py if os.path.exists(py) else sys.executable, os.path.join(REPO, "tools/server_state.py"),
                            self.state_db] + (["--db", db] if db else []), capture_output=True, text=True, cwd=REPO)
        with open(out, "w") as f:
            f.write(r.stdout + r.stderr)
        return r.stdout
