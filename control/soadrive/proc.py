"""Processes: start under `timeout -k`, keep the PID, stop by PID (its own process group), an RSS cap;
free ports; repo files in a worktree (PLAN-consolidate D1-D3)."""
import os
import signal
import socket
import subprocess
import threading
import time

# control/soadrive/proc.py -> the repository root
REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MAX_RSS_KB = 6 * 1024 * 1024
# every Proc started and not yet stopped: stop_all() ends them (a driver that is itself stopped)
LIVE, LIVE_LOCK = set(), threading.Lock()


def repo_file(rel):
    """REPO/rel, else the main checkout's (the one work/ links to: a worktree lacks untracked files).
    Empty files don't count. None when neither exists."""
    for root in (REPO, os.path.dirname(os.path.realpath(os.path.join(REPO, "work")))):
        p = os.path.join(root, rel)
        if os.path.isdir(p) or (os.path.isfile(p) and os.path.getsize(p) > 0):
            return p
    return None


def free_ports(n):
    socks = [socket.socket() for _ in range(n)]
    for s in socks:
        s.bind(("127.0.0.1", 0))
    ports = [s.getsockname()[1] for s in socks]
    for s in socks:
        s.close()
    return ports


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


def kill_all():
    """KILLs the process group of every Proc not yet stopped. Each runs in its own group (not the
    driver's), so a driver that is killed leaves them running, each with the game slot it
    inherited, until its own time limit: a driver's TERM handler calls this first."""
    with LIVE_LOCK:
        live = list(LIVE)
    for p in live:
        try:
            os.killpg(p.pid, signal.SIGKILL)
        except (ProcessLookupError, PermissionError):
            pass


def exit_on_signals(code=143, signals=(signal.SIGTERM, signal.SIGHUP)):
    """On TERM / HUP (a gate's interrupt or time limit, a closed terminal): end every Proc, then exit
    at once (a driver whose threads are blocked in waits; tests/diff/difftest.py). Main thread only."""
    def handler(signum, _frame):
        kill_all()
        print("stopped by signal %d: ended %s" % (signum, "the clients and servers it started"), flush=True)
        os._exit(code)
    for s in signals:
        signal.signal(s, handler)
