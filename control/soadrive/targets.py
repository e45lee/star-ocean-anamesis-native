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

from . import fifo, gdb, milestones, proc, screens, winhost
from .proc import REPO

sys.path.insert(0, os.path.join(REPO, "control"))
import soaslot  # noqa: E402  (control/soaslot.py: the machine-wide game-process slot pool)

# SOA_PACKAGE_DIR: the unpacked release package (README.md "Packaging") whose programs a run tests
# (scripts/package-verify.sh): they run with that folder as their working directory and get no
# --master / --download-dir / --seed, so they find the game files the way the package's README.txt
# says (soa/install.h). Unset: the checkout's own files, as always.
PACKAGE_DIR = os.environ.get("SOA_PACKAGE_DIR") or None
# With a package, the port-server target runs its launcher run-port-server.sh / .cmd (the package's
# README.txt "2. Running" b): soa-server, then soa --server against it, the server stopped when soa
# exits. No launcher options: its default data dir (soa's, the server in DATA/server/) under a
# scratch HOME (Linux) / LOCALAPPDATA (Windows), its default port unless that one is taken; the
# client's options (--control, --headless, ...) and the server's (--seed-rng, --log-packets, ...)
# go through it. The run fails when the launcher leaves its soa-server running after the client.
LAUNCHER_PORT = 44310
# the server options the launcher passes on to soa-server (the others go to soa)
LAUNCHER_SERVER_FLAGS = {"--new-player", "--galaxy-pass", "--enable-events", "--restore-tower", "--english"}
LAUNCHER_SERVER_VALUES = {"--seed", "--download", "--download-dir", "--master", "--log-packets", "--seed-rng", "--clock",
                          "--start-coins", "--event-keywords", "--stamina-heal-time"}


def package_launcher(win):
    """The package's run-port-server launcher, or None (no package, or one without it)."""
    if not PACKAGE_DIR:
        return None
    p = os.path.join(PACKAGE_DIR, "run-port-server.cmd" if win else "run-port-server.sh")
    return p if os.path.isfile(p) else None


def launcher_server_args(args):
    """args checked to be options the launcher hands to soa-server (Abort otherwise: soa would
    get them and only warn)."""
    i = 0
    while i < len(args):
        a = args[i]
        if a in LAUNCHER_SERVER_VALUES:
            i += 2
        elif a in LAUNCHER_SERVER_FLAGS:
            i += 1
        else:
            raise Abort("server option %s: run-port-server doesn't pass it to soa-server" % a)
    return list(args)


def port_in_use(port):
    """Someone listens on 127.0.0.1:port (here; on Windows also what WSL sees of it)."""
    import socket
    s = socket.socket()
    # (WSL's mirrored networking may let a connect to a closed port hang: no answer counts as free)
    s.settimeout(2)
    try:
        return s.connect_ex(("127.0.0.1", port)) == 0
    except OSError:
        return False
    finally:
        s.close()

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
      gdb           the runtime's GDB stub (--gdb 127.0.0.1:0, the port from the client's log; Run.gdb()
                    attaches: soadrive/gdb.py)
      loopback      the loopback address the programs use with each other: 127.0.0.1, or "::1" for IPv6
                    (port-server: soa-server's --listen / --http and the client's --server / --http;
                    the GDB stub, except for a Windows client: WSL reaches it on 127.0.0.1 only)
    """

    def __init__(self, server_args=(), clock=None, client_save=False, new_player=False, prepared=None, seed=None,
                 seed_rng=1, client_args=(), env=None, limit=3600, windowed=False, explicit_data=True, log_packets=True,
                 state_master=True, fresh_kvs=True, phone=None, binary=None, server_binary=None, gdb=False,
                 loopback="127.0.0.1"):
        self.server_args, self.clock, self.client_save, self.new_player = list(server_args), clock, client_save, new_player
        # a prepared server state (soadrive/prepared.py: a state DB every target starts from a
        # copy of), or None: a fresh state
        self.prepared = prepared
        self.seed, self.seed_rng, self.client_args, self.env = seed, seed_rng, list(client_args), dict(env or {})
        self.limit, self.windowed, self.explicit_data, self.log_packets = limit, windowed, explicit_data, log_packets
        self.state_master, self.fresh_kvs, self.phone = state_master, fresh_kvs, phone
        self.binary, self.server_binary, self.gdb = binary, server_binary, gdb
        self.loopback = loopback


def binaries():
    return {
        "soa": os.environ.get("SOA", os.path.join(REPO, "build/port/soa")),
        "emu": os.environ.get("SOA_EMU", os.path.join(REPO, "build/emulator/soa-emu")),
        "server": os.environ.get("SOA_SERVER", os.path.join(REPO, "build/server/soa-server")),
    }


def make_phone(dst, fresh_kvs=True, win=False):
    """The run's phone: the shared pre-downloaded phone linked (SOA_PHONE as the session scripts
    take it: unset = the shared phone, none = empty, DIR = that phone). Returns (a note, whether the
    data is on it). win: a Windows client's (the stage's shared phone, work/phone-3.7.0 there,
    unless SOA_SHARED_PHONE says otherwise: hard links within the Windows drive)."""
    if os.path.isdir(dst):
        shutil.rmtree(dst)
    env = dict(os.environ)
    if win and "SOA_SHARED_PHONE" not in env:
        env["SOA_SHARED_PHONE"] = os.path.join(winhost.STAGE, "work", "phone-3.7.0")
    if win:
        note, linked = winhost.make_phone(dst, env)
        aska = os.path.join(dst, "data", "shared_prefs", "Aska.xml")
        if fresh_kvs and os.path.exists(aska):
            os.remove(aska)
        return note, linked
    r = subprocess.run(["bash", "-c", '. scripts/shared-phone.sh; shared_phone_resolve "$1"; '
                        'if [ -n "$SOA_PHONE" ]; then shared_phone_link "$SOA_PHONE" "$2" && echo "linked from $SOA_PHONE"; '
                        'else mkdir -p "$2"; echo "empty (the client downloads)"; fi', "-", REPO, dst],
                       cwd=REPO, capture_output=True, text=True, env=env)
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
        self.name, self.continued = None, False

    @staticmethod
    def diff(rdir, target):
        return Layout("diff", rdir, os.path.join(rdir, "fifo"), os.path.join(rdir, "client.log"),
                      os.path.join(rdir, "server.log") if target != "port-inproc" else os.path.join(rdir, "client.log"),
                      os.path.join(rdir, "packets", "packets.log"), os.path.join(rdir, "server", "server.sqlite3"),
                      os.path.join(rdir, "shots"), os.path.join(rdir, "phone"), rdir, os.path.join(rdir, "milestones.txt"),
                      phone_cleanup=os.path.join(rdir, "phone"))

    @staticmethod
    def port_session(out, tmp, target="port-inproc", shot_names=None, name=None):
        """name: one of a session's several boots (OUT/NAME.log, OUT/NAME/ the shots,
        OUT/packets-NAME/, TMP/NAME/data the phone, TMP/NAME/fifo; newplayer / tutorial sessions)."""
        sub = (lambda p: os.path.join(tmp, name, p)) if name else (lambda p: os.path.join(tmp, p))
        phone = sub("data")
        inproc = target == "port-inproc"
        log = os.path.join(out, name + ".log" if name else "log.txt")
        lay = Layout("port-session", out, sub("fifo"), log, log if inproc else os.path.join(out, (name + "-" if name else "") + "server.log"),
                     os.path.join(out, "packets-" + name if name else "packets", "packets.log"),
                     os.path.join(phone, "server.sqlite3") if inproc else sub(os.path.join("server", "server.sqlite3")),
                     os.path.join(out, name or "shots"), phone, out, os.path.join(out, (name + "-" if name else "") + "steps.txt"),
                     style="steps", shot_names=shot_names, state_end=False, inproc_db_default=inproc)
        lay.name = name
        return lay

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
        if getattr(self, "continued", False):
            # a later boot of the same session: only its own log, packet log and FIFO are new
            for p in (self.fifo, self.client_log, self.client_log + ".pos"):
                if os.path.lexists(p):
                    os.remove(p)
            if os.path.isdir(os.path.dirname(self.packets)):
                shutil.rmtree(os.path.dirname(self.packets))
        elif self.kind == "diff":
            if os.path.isdir(self.out):
                shutil.rmtree(self.out)
        elif getattr(self, "name", None) and self.kind == "port-session":
            # a named boot: its scratch dir and its outputs (OUT/NAME/, OUT/NAME.log, ...)
            for d in (os.path.dirname(self.phone), self.shots, os.path.dirname(self.packets)):
                if os.path.isdir(d):
                    shutil.rmtree(d)
            for p in (self.client_log, self.client_log + ".pos", self.steps):
                if os.path.lexists(p):
                    os.remove(p)
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
        self.win = False  # a Windows client (start(): soadrive/winhost.py)
        self.ctl_timeout = 120 if lay.kind == "diff" else 400
        self._cursor = None
        # called after the phone and the client save are in place, before anything starts (a
        # session's own files on the phone)
        self.before_client = None
        # why the client is gone (None while it runs): _scan / alive
        self.death, self._scan_pos, self._perf_at = None, 0, None
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
        server_side = self.target != "port-inproc"
        binary = cfg.binary or (b["soa"] if self.target != "emu" else b["emu"])
        # A Windows client (build-win/*.exe; soadrive/winhost.py): the staged programs and data, Windows
        # paths, the TCP control channel, the phone and the server's state on the Windows drive.
        self.win = winhost.is_windows(binary)
        if self.win:
            built, binary = binary, winhost.staged_binary(binary)
            # its soa-server: the Windows one too (a Linux server given with it, e.g. a session's default,
            # is replaced by the build-win sibling of the client)
            server_binary = winhost.staged_binary(cfg.server_binary if winhost.is_windows(cfg.server_binary) else
                                                  os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(built))), "server", "soa-server.exe"))
            # (the download is the zip, read in place: scripts/windows-stage.sh)
            master = winhost.stage_file("data/basmaster-3.7.0.sqlite3")
            download = winhost.stage_file("work/SOA-3.7.0-canonical-data.zip")
            if (not master or not download) and not PACKAGE_DIR:
                raise Abort("data/basmaster-3.7.0.sqlite3 or work/SOA-3.7.0-canonical-data.zip not staged in %s "
                            "(scripts/windows-stage.sh)" % winhost.STAGE)
            wp, cwd = winhost.winpath, winhost.STAGE
            if not cfg.phone:
                inside = os.path.dirname(self.state_db) == self.phone or self.state_db.startswith(self.phone + os.sep)
                self.phone = winhost.local_dir(self.phone)
                if inside:
                    self.state_db = os.path.join(self.phone, os.path.relpath(self.layout.state_db, self.layout.phone))
            if not winhost.on_drive(os.path.dirname(self.state_db)):
                self.state_db = os.path.join(winhost.local_dir(os.path.dirname(self.state_db)), os.path.basename(self.state_db))
            # port 0: the client picks it and logs it (winhost.control_port), see below
            self.fifo = "tcp:127.0.0.1:0"
        else:
            master = proc.repo_file("data/basmaster-3.7.0.sqlite3")
            download = proc.repo_file("work/SOA-3.7.0-canonical-data.zip")  # the download, read in place
            server_binary = cfg.server_binary or b["server"]
            wp, cwd = (lambda p: p), REPO
        if PACKAGE_DIR:
            server_binary = os.path.join(PACKAGE_DIR, "soa-server.exe" if self.win else "soa-server")
            # a release package under test (scripts/package-verify.sh): its programs find the game
            # files beside them (soa/install.h) and run outside any checkout
            cwd = PACKAGE_DIR
            self.note("release package %s: no --master / --download-dir / --seed; the programs look beside themselves" % PACKAGE_DIR)
        elif (cfg.explicit_data or server_side) and (not master or not download):
            raise Abort("data/basmaster-3.7.0.sqlite3 or the download (work/SOA-3.7.0-canonical-data.zip) not found")
        self.launcher = package_launcher(self.win) if self.target == "port-server" else None
        launcher_env = {}
        if self.launcher:
            if cfg.phone:
                raise Abort("a phone given (EMU_DATA) and the package's launcher: the launcher keeps its own")
            # its default data dir, under a scratch HOME / LOCALAPPDATA (see LAUNCHER_PORT)
            root = os.path.join(self.dir, "launcher-home")
            if self.win:
                root = winhost.local_dir(root)
                launcher_env["LOCALAPPDATA"] = winhost.winpath(root)
                data = os.path.join(root, "soa", "port-370")
            else:
                if os.path.isdir(root):
                    shutil.rmtree(root)
                launcher_env["HOME"] = root
                data = os.path.join(root, ".local", "share", "soa-linux-370")
            self.phone, self.state_db = data, os.path.join(data, "server", "server.sqlite3")
            self.server_log = os.path.join(data, "server.log")
            self.layout.phone_cleanup = os.path.join(data, "data")
            self.note("release package launcher %s, data %s" % (self.launcher, data))
        if cfg.phone:
            os.makedirs(self.phone, exist_ok=True)
            if cfg.fresh_kvs and os.path.exists(os.path.join(self.phone, "data/shared_prefs/Aska.xml")):
                os.remove(os.path.join(self.phone, "data/shared_prefs/Aska.xml"))
            self.predownloaded = True
            self.note("phone: %s (as it is)" % self.phone)
        else:
            t = time.monotonic()
            note, self.predownloaded = make_phone(self.phone, cfg.fresh_kvs, self.win)
            self.note("phone: %s (%d ms)" % (note, int((time.monotonic() - t) * 1000)))
        if cfg.prepared:
            # the whole server state (the campaign's progress too, PLAN-schema S12: no side file)
            os.makedirs(os.path.dirname(self.state_db), exist_ok=True)
            shutil.copyfile(cfg.prepared, self.state_db)
            self.note("server state: a copy of %s" % cfg.prepared)
        if cfg.client_save == "session":
            session_client_save(os.path.join(self.phone, "data/shared_prefs"))
        elif cfg.client_save:
            shutil.copyfile(os.path.join(REPO, "data/saves/client/Game.xml"), os.path.join(self.phone, "data/shared_prefs/Game.xml"))
        if self.before_client:
            self.before_client()
        srv = []
        if (cfg.explicit_data or server_side) and not PACKAGE_DIR:
            srv += ["--master", wp(master)]
        if cfg.seed_rng is not None:
            srv += ["--seed-rng", str(cfg.seed_rng)]
        if cfg.clock:
            srv += ["--clock", cfg.clock]
        srv += cfg.server_args
        if cfg.seed is None and not cfg.new_player and not PACKAGE_DIR:
            srv += ["--seed", wp(os.path.join(winhost.STAGE if self.win else REPO, "data/saves/seed/Game.xml"))]
        elif cfg.seed:
            srv += ["--seed", wp(cfg.seed)]
        # --render-size window: the game screen is the window (W x H) on every host. The default
        # (desktop) scales it up to fill the desktop, and since the port renders at the game screen's
        # size (hi-res, port/README.md), the pixels drawn would depend on the host's monitor.
        client = ([] if self.launcher else ["--data", wp(self.phone)]) + [
            "--windowed" if cfg.windowed else "--headless", "--size", "%dx%d" % (W, H), "--render-size", "window",
            "--control", self.fifo]
        if cfg.gdb:
            if not gdb.available():
                raise Abort("a GDB stub was asked for, but control/gdbclient.py (the runtime's --gdb) isn't in this checkout")
            # port 0: the client logs the one it took (Run.gdb reads it). WSL's mirrored networking
            # shares 127.0.0.1 with Windows, not ::1.
            self.gdb_host = "127.0.0.1" if self.win else cfg.loopback
            self.gdb_port = 0
            client += gdb.client_args(0, self.gdb_host)
        if cfg.clock:
            client += ["--device-clock", cfg.clock]
        env = {"SDL_AUDIODRIVER": os.environ.get("SDL_AUDIODRIVER", "dummy")}
        # SOA_SLOT_SOFTWARE_GL (control/soaslot.py; docs/testing-software-gl.md): the client on Mesa's
        # llvmpipe, also when the caller holds the slot (acquire() not called here)
        gl = soaslot.apply_software_gl()
        if gl:
            self.note("software GL: " + " ".join("%s=%s" % kv for kv in sorted(gl.items())))
        env.update(gl)
        env.update(cfg.env)
        if self.win:
            # the client's environment reaches a Windows program only through WSLENV
            names = [k for k in env if k not in os.environ.get("WSLENV", "").split(":")]
            env["WSLENV"] = ":".join([x for x in os.environ.get("WSLENV", "").split(":") if x] + names)
        pkt = ["--log-packets", wp(os.path.dirname(self.packets))] if cfg.log_packets else []
        if self.launcher:
            env.update(launcher_env)
            if self.win:
                names = [k for k in launcher_env if k not in env["WSLENV"].split(":")]
                env["WSLENV"] = ":".join([x for x in env["WSLENV"].split(":") if x] + names)
                argv = ["cmd.exe", "/c", wp(self.launcher)]
            else:
                argv = [self.launcher]
            argv += client + cfg.client_args + launcher_server_args(srv + pkt)
            if port_in_use(LAUNCHER_PORT) or port_in_use(LAUNCHER_PORT + 80):
                gp = (winhost.free_ports if self.win else proc.free_ports)(1)[0]
                self.note("the launcher's port %d is taken: --port %d" % (LAUNCHER_PORT, gp))
                argv += ["--port", str(gp)]
            self.client = proc.Proc(os.path.basename(self.launcher), argv, self.client_log, env=env, limit=cfg.limit,
                                    slot_fd=self.slot, cwd=cwd)
            # the server listening first (its first start prepares the master and the CDN), then soa
            end = time.monotonic() + 300
            while not self.grep(self.client_log, r"^== soa \(pid"):
                if not self.client.running() or time.monotonic() > end:
                    raise Abort("the launcher didn't start soa (see %s, %s)" % (self.client_log, self.server_log))
                time.sleep(0.5)
        elif self.target == "port-inproc":
            extra = []
            if cfg.explicit_data or not self.layout.inproc_db_default:
                extra += ["--db", wp(self.state_db)]
            if cfg.explicit_data and not PACKAGE_DIR:
                extra += ["--download-dir", wp(download)]
            self.client = proc.Proc("soa", [binary] + client + cfg.client_args + srv + extra + pkt, self.client_log,
                                    limit=cfg.limit, env=env, slot_fd=self.slot, cwd=cwd)
        else:
            for attempt in range(4):
                gp, hp = (winhost.free_ports if self.win else proc.free_ports)(2)
                lo = cfg.loopback
                self.server = proc.Proc("soa-server", [server_binary, "--listen", gdb.host_port(lo, gp),
                                                       "--http", gdb.host_port(lo, hp), "--data", wp(os.path.dirname(self.state_db))] +
                                        ([] if PACKAGE_DIR else ["--download-dir", wp(download)]) + pkt + srv, self.server_log,
                                        limit=cfg.limit, cwd=cwd)
                # its "ready" line: every startup line (game, CDN) is out (scripts/lib/with-server.sh)
                end = time.monotonic() + 120
                while not self.grep(self.server_log, r"^soa-server: ready"):
                    if not self.server.running() or time.monotonic() > end:
                        break
                    time.sleep(0.5)
                if self.grep(self.server_log, r"^soa-server: ready"):
                    break
                self.server.stop()
                # a Windows soa-server whose ports Windows refused (winhost.free_ports): other ports
                if not (self.win and self.grep(self.server_log, re.escape(winhost.IN_USE))) or attempt == 3:
                    raise Abort("soa-server didn't start (see %s)" % self.server_log)
                self.note("soa-server: ports %d/%d in use on Windows; trying others" % (gp, hp))
            self.client = proc.Proc(os.path.basename(binary), [binary] + client + cfg.client_args +
                                    ["--server", gdb.host_port(cfg.loopback, gp), "--http", gdb.host_port(cfg.loopback, hp)],
                                    self.client_log, env=env,
                                    limit=cfg.limit, slot_fd=self.slot, cwd=cwd)
        emu_link = os.path.join(self.dir, "emu.log")
        if self.layout.kind == "diff" and not os.path.lexists(emu_link):
            os.symlink("client.log", emu_link)
        end = time.monotonic() + 120
        while self.win and self.fifo.endswith(":0"):
            port = winhost.control_port(self.client_log)
            if port:
                self.fifo = "tcp:127.0.0.1:%d" % port
                fifo.CLIENT_PATH[self.fifo] = wp
                break
            if not self.alive() or time.monotonic() > end:
                raise Abort("the client didn't open its control channel (%s; see %s)" % (
                    self.gone() if not self.alive() else "not within 120s", self.client_log))
            time.sleep(0.5)
        while not fifo.listening(self.fifo):
            if not self.alive() or time.monotonic() > end:
                raise Abort("the client didn't open its control FIFO (%s; see %s)" % (
                    self.gone() if not self.alive() else "not within 120s", self.client_log))
            time.sleep(0.5)
        # the test switch SOA_TEST_FRAME_DELAY=MS (docs/environment.md): a slow client on demand (the
        # runtime's frame-delay:MS hook, every frame MS longer), the load a session's waits must survive
        delay = os.environ.get("SOA_TEST_FRAME_DELAY")
        if delay:
            self.note("test: SOA_TEST_FRAME_DELAY: frame-delay:%d" % int(delay))
            self.send(["frame-delay:%d" % int(delay)])

    QUIT_SEND_SECS = 5  # stop(): how long `quit` waits for a reader of the control channel

    def stop(self):
        # A clean quit only for a client that can still hear it: not when it is known dead (a crash,
        # a host GPU failure, stuck); and when nobody opens its control channel for reading within
        # QUIT_SEND_SECS (it never opened it, or stopped reading), the quit isn't sent: both go
        # straight to Proc.stop (TERM, then KILL), not 10 + 15 s later. (No separate "is anyone
        # reading" probe: opening and closing the FIFO is an EOF to the client, and a quit written
        # right after it can be dropped; fifo.deliver's comment.)
        if (self.client and self.client.running() and not getattr(self, "death", None)
                and fifo.send(self.fifo, ["quit"], timeout=self.QUIT_SEND_SECS, alive=self.client.running)):
            self.client.wait(15)
        if getattr(self, "launcher", None) and self.client:
            self.launcher_check()
        for p in (self.client, self.server):
            if p:
                p.stop()
        if self.own_slot:
            soaslot.release(self.slot)
            self.slot = -1
        self._scan()
        if self.grep(self.client_log, r"Unhandled SIG|\*\*\* host signal"):
            # a crash whose backtrace is in the host's GPU driver (WSL's NVIDIA GL, seen once with
            # many clients at once) is the host's, not the game's: labelled so
            host = self.grep(self.client_log, r"^/usr/lib/wsl/drivers/|libnvwgf2umx|libnvidia-gl|libGLX_nvidia|d3d12_dri|libgallium-")
            self.miss("the client crashed%s (see %s)" % (" in the host GPU driver" if host else "", self.client_log))
        elif self.death and self.death.startswith("host GPU") and not self.failed:
            self.miss("the client lost the host GPU: %s (see %s)" % (self.death, self.client_log))
        if self.grep(self.client_log, r"glx: failed to create|X Error of failed request"):
            self.note("the host's GL/GLX failed for this client (see %s): a host problem, not the game's" % self.client_log)
        if (self.client is not None or self.server is not None) and os.path.exists(self.state_db):
            self.state_check()
        if self.layout.state_end and os.path.exists(self.state_db):
            self.state("end")
        cleanup = self.layout.phone_cleanup
        if cleanup and not self.keep and os.path.islink(cleanup):
            # a Windows run's phone: on the Windows drive (winhost.local_dir), linked here
            shutil.rmtree(os.path.realpath(cleanup), ignore_errors=True)
            os.remove(cleanup)
        elif cleanup and not self.keep and os.path.isdir(cleanup):
            shutil.rmtree(cleanup, ignore_errors=True)
        with open(self.layout.steps, "w") as f:
            f.write("\n".join(self.results) + "\n" + ("FAIL" if self.failed else "PASS") + "\n")

    def launcher_check(self):
        """The launcher stopped its soa-server when soa exited: the server's PID (its "== soa-server
        (pid N)" line) gone within 15 s of the launcher's exit."""
        m = re.search(r"^== soa-server \(pid (\d+)\)", open(self.client_log, errors="replace").read(), re.M)
        if not m:
            return
        pid = int(m.group(1))
        self.client.wait(15)

        def running():
            if self.win:
                r = subprocess.run(["tasklist.exe", "/FI", "PID eq %d" % pid, "/NH"], capture_output=True, text=True)
                return re.search(r"\b%d\b" % pid, r.stdout) is not None
            try:
                os.kill(pid, 0)
                return True
            except ProcessLookupError:
                return False
        end = time.monotonic() + 15
        while running() and time.monotonic() < end:
            time.sleep(0.5)
        if self.client.running():
            self.miss("the launcher still runs after soa's exit")
        elif running():
            self.miss("the launcher left its soa-server (pid %d) running after the client exited" % pid)
            if not self.win:
                os.kill(pid, 9)
            else:
                subprocess.run(["taskkill.exe", "/F", "/PID", str(pid)], capture_output=True)
        else:
            self.ok("the launcher stopped its soa-server (pid %d) when the client exited" % pid)

    # Why a client is gone though its process may still be there (it can hang after these lines: a
    # wedged GL driver): a crash (its signal handler's lines), or the host's GPU dropping out
    # (WSL: "D3D12: Removing Device.", a GLX context that can't be made, a backtrace in the NVIDIA
    # driver) -- the host's problem, not the game's: labelled "host GPU" so a gate can say so.
    CRASH = re.compile(rb"Unhandled SIG|\*\*\* host signal")
    HOST_GPU = re.compile(rb"D3D12: Removing Device|glx: failed to create|X Error of failed request|^/usr/lib/wsl/drivers/|"
                          rb"libnvwgf2umx|libnvidia-gl|libGLX_nvidia|d3d12_dri|libgallium-|"
                          # a Windows client: ANGLE's D3D11 device lost (winhost.py)
                          rb"D3D11 device was (removed|reset)|Device lost in SwapChain11", re.M)
    # no frame-rate line (the host loop logs "I/perf: N fps" every 10 s) for this long, after one was
    # seen: the client's main loop is stuck
    STALL_SECS = 120

    def _scan(self):
        """Reads what the client log gained since the last call; sets self.death (None while fine)."""
        if getattr(self, "death", None):
            return
        try:
            with open(self.client_log, "rb") as f:
                f.seek(max(0, getattr(self, "_scan_pos", 0) - 64))
                data = f.read()
                self._scan_pos = f.tell()
        except FileNotFoundError:
            return
        now = time.monotonic()
        if b"I/perf: " in data:
            self._perf_at = now
        host, crash = self.HOST_GPU.search(data), self.CRASH.search(data)
        if host:
            self.death = "host GPU (%s)" % host.group(0).decode(errors="replace").strip()
        elif crash:
            self.death = "crashed (%s)" % crash.group(0).decode(errors="replace")
        elif getattr(self, "_perf_at", None) and now - self._perf_at > self.STALL_SECS:
            self.death = "stuck (no frame-rate line for %ds)" % self.STALL_SECS
        if self.death:
            print("%s%s: %s (see %s)" % (self.prefix, "HOST-GPU-FAILURE" if self.death.startswith("host GPU") else "CLIENT-DIED",
                                         self.death, self.client_log), flush=True)

    def crashed(self):
        """The client logged a crash or a host GPU failure, or stopped drawing (self.death says
        which): it counts as gone even while its process lingers."""
        self._scan()
        return bool(getattr(self, "death", None))

    def alive(self):
        """The client (and its soa-server) still running and not dead by its log. Every wait checks it,
        so a dead client fails the step at once instead of at its time limit."""
        if self.client is None:
            return False
        if not self.client.alive():
            if not getattr(self, "death", None):
                self._scan()
                self.death = getattr(self, "death", None) or "exited (status %s)" % self.client.p.poll()
            return False
        if self.server is not None and not self.server.running():
            self.death = getattr(self, "death", None) or "its soa-server exited (status %s)" % self.server.p.poll()
            return False
        return not self.crashed()

    def gone(self):
        """Why the client is gone, for a step's FAIL line."""
        d = getattr(self, "death", None) or "exited"
        return "the client is gone: " + d + ("; a host problem, not the game's: rerun" if d.startswith("host GPU") else "")

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
        return fifo.send(self.fifo, cmds, self.ctl_timeout if timeout is None else timeout,
                         alive=self.alive if self.client is not None else None)

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

    def tap_until_changed(self, name, xy, before, wait_ms=4000, tries=4, limit=0.05):
        """Taps xy until the screen differs from the screenshot `before` (RMSE above `limit`): for a
        tap with no log line to wait for, dropped while a screen fades in. Records PASS / FAIL."""
        probe = self.scratch(".changed-probe.png")
        for i in range(tries):
            self.ctl("tap:" + xy, "wait:%d" % wait_ms)
            self.send(["shot:" + probe])
            if os.path.exists(probe) and screens.rmse(before, probe) > limit:
                self.ok(name)
                return True
            if not self.alive():
                break
            self.note("%s: the screen didn't change; tapping again (%d)" % (name, i + 1))
        self.miss(name if self.alive() else "%s (%s)" % (name, self.gone()))
        return False

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

    def last_line(self, rx, path=None):
        """The last line of the client log (or path) matching rx; None when none does."""
        return milestones.last(path or self.client_log, rx)

    def poll(self, secs, pred):
        return milestones.poll(secs, pred, alive=self.alive)

    def _wait(self, name, secs, pred, fatal, action=None, every=4):
        if milestones.poll(secs, pred, alive=self.alive, action=action, every=every):
            self.ok(name)
            return True
        if not self.alive():
            self.miss("%s (%s)" % (name, self.gone()))
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
        why = self.gone() if not self.alive() else "not within %ds" % secs
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
        why = self.gone() if not self.alive() else "not within %ds, %d x %s" % (secs, sent, " ".join(cmds))
        self._missed(name or "no log line matching %r" % rx, why, fatal)
        if fatal:
            raise Abort(name or rx)
        return None

    # ---- the guest debugger (soadrive/gdb.py) ----------------------------------------------------
    def gdb(self, timeout=30.0):
        """A GdbClient attached to this run's client (Config(gdb=True)), as a context manager: the
        guest is stopped inside the block and runs on after it (detached)."""
        if getattr(self, "gdb_port", None) is None:
            raise gdb.GdbUnavailable("this run wasn't started with Config(gdb=True)")
        if not self.gdb_port:
            self.gdb_port = gdb.listen_port(self.client_log)
            if not self.gdb_port:
                raise gdb.GdbUnavailable("the client didn't log its GDB stub's port (%s)" % self.client_log)
        return gdb.attach(self.gdb_port, timeout, self.gdb_host)

    # ---- the server's state -----------------------------------------------------------------------
    def _read_state(self, tool_args):
        """Runs a tools/ script over the server's state DB (tool_args with STATE where its path goes);
        a Windows server's state is read from a snapshot. Returns the CompletedProcess."""
        py = os.path.join(REPO, ".venv/bin/python")
        state_db, snap = self.state_db, None
        if self.win and os.path.exists(state_db):
            # a Windows server's live WAL database: SQLite here can't share its locks across the
            # drive, so a snapshot (the file and its WAL, checkpointed in the copy) is what's read
            import sqlite3
            import tempfile
            snap = tempfile.mkdtemp(prefix="soadrive-state.")
            state_db = os.path.join(snap, "server.sqlite3")
            shutil.copyfile(self.state_db, state_db)
            if os.path.exists(self.state_db + "-wal"):
                shutil.copyfile(self.state_db + "-wal", state_db + "-wal")
            con = sqlite3.connect(state_db)
            con.execute("pragma wal_checkpoint(TRUNCATE)")
            con.close()
        try:
            return subprocess.run([py if os.path.exists(py) else sys.executable] + [state_db if a == "STATE" else a for a in tool_args],
                                  capture_output=True, text=True, cwd=REPO)
        finally:
            if snap:
                shutil.rmtree(snap, ignore_errors=True)

    def state(self, tag):
        """state-TAG.txt: tools/server_state.py's dump of the server's state (its text)."""
        out = os.path.join(self.layout.state_dir, "state-%s.txt" % tag)
        db = proc.repo_file("data/basmaster-3.7.0.sqlite3") if self.cfg.state_master else None
        r = self._read_state([os.path.join(REPO, "tools/server_state.py"), "STATE"] + (["--db", db] if db else []))
        with open(out, "w") as f:
            f.write(r.stdout + r.stderr)
        return r.stdout

    # G9 of docs/history/PLAN-schema.md, permanent since S11: every run's end state (sessions, tests/diff,
    # the Windows runs) has its declared foreign keys holding, its master references resolved
    # against the master the server ran with, and this build's schema version. Run by stop(); a
    # violation is a failed step (so the session's or the flow's verdict is FAIL) and is recorded
    # in STATE_CHECKS for control/run.py's exit status.
    STATE_CHECKS = []  # (Run, ok, the check's summary line)

    def state_check(self):
        master = proc.repo_file("data/basmaster-3.7.0.sqlite3")
        r = self._read_state([os.path.join(REPO, "tools/schema_inventory.py"), "--check", "--strict", "STATE", master])
        lines = [ln for ln in (r.stdout + r.stderr).splitlines() if ln.strip()]
        summary = lines[-1].split(": ", 1)[-1] if lines else "no output (exit %d)" % r.returncode
        ok = r.returncode == 0
        Run.STATE_CHECKS.append((self, ok, summary))
        if ok:
            self.ok("state check: %s" % summary)
        else:
            for ln in lines[:-1][:20]:
                self.note("state check: " + ln)
            self.miss("state check (G9): %s (tools/schema_inventory.py --check --strict %s)" % (summary, self.state_db))
        return ok
