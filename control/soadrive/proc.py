"""Processes: start under `timeout -k`, keep the PID, stop by PID (its own process group), an RSS cap;
free ports; repo files in a worktree (PLAN-consolidate D1-D3)."""
import os
import random
import signal
import socket
import subprocess
import sys
import threading
import time

# control/soadrive/proc.py -> the repository root
REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MAX_RSS_KB = 6 * 1024 * 1024
# every Proc started and not yet stopped: stop_all() ends them (a driver that is itself stopped)
LIVE, LIVE_LOCK = set(), threading.Lock()


def repo_file(rel):
    """REPO/rel, else the main checkout's (a worktree lacks untracked files; soa_save.paths.repo_file).
    Empty files don't count. None when neither exists."""
    if REPO not in sys.path:
        sys.path.insert(0, REPO)
    from soa_save.paths import repo_file as _repo_file

    p = _repo_file(rel, REPO)
    return str(p) if p is not None else None


def free_ports(n, win=False):
    """n distinct ports for a program to listen on. Nothing holds them: another process can take one
    before the program binds it, so a caller that starts a listener retries on ADDR_IN_USE in its
    log (targets.Run.start does, for soa-server on both platforms).
    Linux: the kernel's pick (bound to 127.0.0.1:0, then closed).
    win (a Windows program from WSL): random, below WSL's ephemeral range (mirrored networking
    reserves that for WSL's sockets), not listened on here. Not tried with a bind: in mirrored
    networking a port bound and closed in WSL stays refused to Windows for a while (WSAEADDRINUSE).
    A control channel takes port 0 instead (winhost.control_port)."""
    if not win:
        socks = [socket.socket() for _ in range(n)]
        for s in socks:
            s.bind(("127.0.0.1", 0))
        ports = [s.getsockname()[1] for s in socks]
        for s in socks:
            s.close()
        return ports
    lo, hi = 30000, 44000
    try:
        with open("/proc/sys/net/ipv4/ip_local_port_range") as f:
            hi = min(hi, int(f.read().split()[0]) - 1)
    except (OSError, ValueError, IndexError):
        pass
    used = set()
    for t in ("/proc/net/tcp", "/proc/net/tcp6"):
        try:
            with open(t) as f:
                for line in f.readlines()[1:]:
                    used.add(int(line.split()[1].rsplit(":", 1)[1], 16))
        except (OSError, ValueError, IndexError):
            pass
    out = []
    while len(out) < n:
        p = random.randint(lo, hi)
        if p not in used and p not in out:
            out.append(p)
    return out


# A listener's bind failure as soa-server logs it (sock::last_error: strerror(EADDRINUSE) on Linux,
# WSAEADDRINUSE's message on Windows).
ADDR_IN_USE = ("Address already in use", "Only one usage of each socket address")


def addr_in_use(log):
    """True when the log says a port was taken (ADDR_IN_USE)."""
    try:
        with open(log, errors="replace") as f:
            text = f.read()
    except OSError:
        return False
    return any(m in text for m in ADDR_IN_USE)


class Proc:
    """A program started in its own process group under `timeout -k 10 LIMIT`; stop() ends the
    group (TERM, up to 10 s, then KILL). Only this PID's group is ever signalled. slot_fd: the
    client's slot of the pool (control/soaslot.py), inherited so the slot stays taken while the
    client lives, even if the driver dies first."""

    def __init__(self, name, argv, log, limit=3600, env=None, cwd=REPO, slot_fd=-1):
        self.name, self.log = name, log
        e = dict(os.environ)
        e.update(env or {})
        self.f = open(log, "ab")
        self.p = subprocess.Popen(["timeout", "-k", "10", str(limit)] + list(argv), stdout=self.f, stderr=subprocess.STDOUT,
                                  env=e, cwd=cwd, start_new_session=True,
                                  pass_fds=(slot_fd,) if slot_fd >= 0 else ())
        self.pid = self.p.pid
        with LIVE_LOCK:
            LIVE.add(self)

    def running(self):
        return self.p.poll() is None

    def rss_kb(self):
        """The largest RSS in the group (the program itself, under timeout)."""
        r = subprocess.run(["ps", "-o", "rss=", "-g", str(self.pid)], capture_output=True, text=True)
        v = [int(x) for x in r.stdout.split() if x.isdigit()]
        return max(v) if v else 0

    def alive(self):
        if not self.running():
            return False
        if self.rss_kb() > MAX_RSS_KB:
            print("%s above %d GB RSS: stopping it" % (self.name, MAX_RSS_KB // (1024 * 1024)))
            self.stop()
            return False
        return True

    def stop(self, grace=10):
        if self.p.poll() is None:
            try:
                os.killpg(self.pid, signal.SIGTERM)
            except ProcessLookupError:
                pass
            end = time.monotonic() + grace
            while self.p.poll() is None and time.monotonic() < end:
                time.sleep(0.25)
            if self.p.poll() is None:
                try:
                    os.killpg(self.pid, signal.SIGKILL)
                except ProcessLookupError:
                    pass
                self.p.wait()
        self.f.close()
        with LIVE_LOCK:
            LIVE.discard(self)

    def wait(self, timeout):
        try:
            self.p.wait(timeout)
            return True
        except subprocess.TimeoutExpired:
            return False


def _live_snapshot():
    """The live Procs without LIVE_LOCK (a signal handler runs on the main thread, which may hold
    it): a copy of the set, retried if another thread changes it during the copy."""
    for _ in range(100):
        try:
            return list(LIVE)
        except RuntimeError:  # "Set changed size during iteration"
            continue
    return []


def kill_all():
    """KILLs the process group of every Proc not yet stopped. Each runs in its own group (not the
    driver's), so a driver that is killed leaves them running, each with the game slot it
    inherited, until its own time limit: a driver's TERM handler calls this first. Safe in a signal
    handler: no lock, no I/O but kill(2)."""
    for p in _live_snapshot():
        try:
            os.killpg(p.pid, signal.SIGKILL)
        except (ProcessLookupError, PermissionError):
            pass


def exit_on_signals(signals=(signal.SIGTERM, signal.SIGHUP)):
    """On TERM / HUP (a gate's interrupt or time limit, a closed terminal): end every Proc, then exit
    at once with 128 + the signal (a driver whose threads are blocked in waits; tests/diff/difftest.py).
    Main thread only. The handler is async-signal-safe in Python's sense: it runs between two
    bytecodes of the main thread, which may be inside print() (a reentrant print raises) or hold a
    lock, so it takes no lock and writes only with os.write to fd 2."""
    def handler(signum, _frame):
        kill_all()
        try:
            os.write(2, b"stopped by signal %d: ended the clients and servers it started\n" % signum)
        except OSError:
            pass
        os._exit(128 + signum)
    for s in signals:
        signal.signal(s, handler)
