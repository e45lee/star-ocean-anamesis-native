#!/usr/bin/env python3
"""The machine-wide game-process slot pool: every game client (soa, soa-emu, soa-viewer) started by a
test or session script takes a slot first, so parallel agents queue instead of overloading the
machine (clients at 2-9 fps make milestones time out: false failures).

A slot is an exclusive flock(2) on one of N files in SOA_SLOT_DIR (default /tmp/soa-slots: one
place for every worktree and shell, whatever XDG_RUNTIME_DIR says). The lock belongs to the open
file, so it lasts as long as any process holding that file descriptor: `run` execs the command with
it (the PID stays the same, so `$!` is the game's `timeout`), the client inherits it, and the slot
frees itself when the client exits or is killed; no stale locks, no cleanup. flock(1) and Python's
fcntl.flock take the same locks.

    control/soaslot.py run [--name NAME] -- CMD ARGS...   take a slot (waiting for one), exec CMD
    control/soaslot.py status                             the slots: free, or who holds them
    control/soaslot.py slots                              N (what `run` uses)
    control/soaslot.py fps DIR...                         the frame rates of the client logs under DIR
    . control/soaslot.sh; soaslot_take NAME               (sh/bash) a slot for the calling shell's
                                                          lifetime, on fd 9 (its children inherit it)
    control/soaslot.py pick NAME                          (soaslot.sh's helper) waits until a slot is
                                                          free and prints its file

Env:
    SOA_SLOTS=N        the pool's size (0: no pool, never wait). Default: DEFAULT_SLOTS (measured on
                       the 32-core / 45 GB development machine, control/README.md), capped by
                       nproc/2 and MemTotal/3 GB on smaller machines.
    SOA_SLOT_DIR=DIR   where the slot files are (default /tmp/soa-slots)
    SOA_SLOT_MIN_FREE_GB=G  also wait while MemAvailable is below G GB (default 8: the agents'
                       brief), which covers game processes that don't go through the pool
    SOA_SLOT_STAGGER=S at least S seconds (default 4) between two clients' starts machine-wide:
                       a dozen clients booting at once saturate the cores
    SOA_SLOT_HELD=1    set by `run` for the command it starts: a nested `run` (a script that
                       starts another script) doesn't take a second slot (no hold-and-wait)

Only clients take slots, never soa-server: a server waits for its client, and N servers holding
the N slots while their clients queue would deadlock.

Used by tests/diff (diffdrive/targets.py), port/scripts/*_session.sh, smoke.sh,
emulator/scripts/*.sh and emulator-viewer/scripts/viewer_lib.sh (control/README.md).
"""
import fcntl
import os
import sys
import time

# Measured 2026-10-03 on the 32-core / 45 GB development machine (control/README.md "Measuring the
# pool's size"): 16 game clients at once (9 in the pool + 7 other agents') kept every client near
# 60 fps (p10 55) and every run passed; at 20 the load reached the core count, MemAvailable fell
# to 10 GB, booting clients dropped to 20-28 fps and a run timed out. 12 leaves room for the
# clients and builds outside the pool.
DEFAULT_SLOTS = 12


def slot_dir():
    return os.environ.get("SOA_SLOT_DIR") or "/tmp/soa-slots"


def _mem_kb(key):
    try:
        with open("/proc/meminfo") as f:
            for line in f:
                if line.startswith(key + ":"):
                    return int(line.split()[1])
    except OSError:
        pass
    return None


def n_slots():
    v = os.environ.get("SOA_SLOTS")
    if v not in (None, ""):
        return max(0, int(v))
    # on a smaller machine: a client per 2 cores and per 3 GB (a client is 1-2 GB RSS)
    n = DEFAULT_SLOTS
    cpus = os.cpu_count() or 4
    n = min(n, max(1, cpus // 2))
    mem = _mem_kb("MemTotal")
    if mem:
        n = min(n, max(1, mem // (3 * 1024 * 1024)))
    return n


def mem_ok():
    need = float(os.environ.get("SOA_SLOT_MIN_FREE_GB", "8"))
    avail = _mem_kb("MemAvailable")
    return avail is None or avail >= need * 1024 * 1024


def _open_dir():
    d = slot_dir()
    os.makedirs(d, exist_ok=True)
    try:
        os.chmod(d, 0o1777)
    except OSError:
        pass
    return d


def try_acquire(name):
    """One pass over the slot files: (fd, index) of the slot taken, or None."""
    d = _open_dir()
    for i in range(n_slots()):
        path = os.path.join(d, "slot.%d" % i)
        fd = os.open(path, os.O_RDWR | os.O_CREAT, 0o666)
        try:
            fcntl.flock(fd, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except OSError:
            os.close(fd)
            continue
        os.ftruncate(fd, 0)
        os.write(fd, ("%d %d %s %s\n" % (os.getpid(), int(time.time()), name, os.getcwd())).encode())
        return fd, i
    return None


def stagger():
    """Spaces the clients' starts machine-wide: at least SOA_SLOT_STAGGER s (default 4) after the
    last slot taken. A booting client is the heaviest (the JIT translates the game's startup), and
    a dozen booting at once saturated the 32 cores (load 32) where the same clients started a few
    seconds apart did not."""
    gap = float(os.environ.get("SOA_SLOT_STAGGER", "4"))
    if gap <= 0:
        return
    path = os.path.join(slot_dir(), "last-start")
    fd = os.open(path, os.O_RDWR | os.O_CREAT, 0o666)
    try:
        fcntl.flock(fd, fcntl.LOCK_EX)  # one starter at a time
        wait = os.path.getmtime(path) + gap - time.time()
        if 0 < wait <= gap:
            time.sleep(wait)
        os.utime(path, None)
    finally:
        os.close(fd)


def acquire(name="game", quiet=False, timeout=None):
    """Takes a slot, waiting as long as it takes (or `timeout` s: then None). Returns the slot's
    file descriptor (keep it open while the client runs; close it to free the slot), or -1 when the
    pool is off (SOA_SLOTS=0) or this process already runs under a slot (SOA_SLOT_HELD)."""
    if n_slots() == 0 or os.environ.get("SOA_SLOT_HELD"):
        return -1
    t0, said, end = time.monotonic(), False, (time.monotonic() + timeout) if timeout else None
    while True:
        if mem_ok():
            got = try_acquire(name)
            if got:
                fd, i = got
                stagger()
                waited = time.monotonic() - t0
                if said and not quiet:
                    print("soaslot: %s: slot %d after %.0f s" % (name, i, waited), file=sys.stderr, flush=True)
                return fd
            why = "all %d slots taken" % n_slots()
        else:
            why = "MemAvailable below %s GB" % os.environ.get("SOA_SLOT_MIN_FREE_GB", "8")
        if not said and not quiet:
            print("soaslot: %s: waiting for a slot (%s; control/soaslot.py status)" % (name, why), file=sys.stderr, flush=True)
            said = True
        if end and time.monotonic() > end:
            return None
        time.sleep(2)


def release(fd):
    if fd is not None and fd >= 0:
        os.close(fd)


def status():
    d = slot_dir()
    n = n_slots()
    print("slot pool: %d slots in %s (SOA_SLOTS overrides), MemAvailable %.1f GB" %
          (n, d, (_mem_kb("MemAvailable") or 0) / 1024 / 1024))
    for i in range(max(n, len([f for f in os.listdir(d) if f.startswith("slot.")]) if os.path.isdir(d) else n)):
        path = os.path.join(d, "slot.%d" % i)
        if not os.path.exists(path):
            print("  slot %d: free" % i)
            continue
        fd = os.open(path, os.O_RDONLY)
        try:
            fcntl.flock(fd, fcntl.LOCK_EX | fcntl.LOCK_NB)
            held = False
            fcntl.flock(fd, fcntl.LOCK_UN)
        except OSError:
            held = True
        os.close(fd)
        info = open(path).read().strip() if held else ""
        if held and info:
            pid, t, rest = (info.split(" ", 2) + ["", ""])[:3]
            print("  slot %d: held %ds by pid %s: %s%s" % (i, int(time.time()) - int(t or 0), pid, rest,
                                                         "" if i < n else " (beyond SOA_SLOTS)"))
        else:
            print("  slot %d: %s" % (i, "held" if held else "free"))


def fps(paths):
    """The frame rates the clients logged (runtime/src/app/host.cpp: `I/perf: X fps` every ~10 s)
    in the client logs under PATHs: per log the median and the 10th percentile (the boot's first
    30 s and the keyboard's frozen frames left out), and over all of them. How the pool's size
    was measured (control/README.md)."""
    logs = []
    for p in paths:
        if os.path.isfile(p):
            logs.append(p)
            continue
        for root, _, files in os.walk(p):
            logs += [os.path.join(root, f) for f in files if f in ("client.log", "log.txt", "emu.log") and not os.path.islink(os.path.join(root, f))]
    allv = []
    pct = lambda v, q: v[min(len(v) - 1, int(q * len(v)))] if v else 0
    for log in sorted(logs):
        v = []
        for ln in open(log, errors="replace"):
            if "I/perf: " in ln:
                try:
                    v.append(float(ln.split("I/perf: ")[1].split()[0]))
                except ValueError:
                    pass
        v = sorted(x for x in v[3:] if x >= 1.0)
        if not v:
            continue
        allv += v
        print("%6.1f median %6.1f p10 %6.1f min  %3d samples  %s" % (pct(v, 0.5), pct(v, 0.1), v[0], len(v), log))
    allv.sort()
    if allv:
        print("all: median %.1f, p10 %.1f, below 30 fps: %.0f%% of %d samples" %
              (pct(allv, 0.5), pct(allv, 0.1), 100.0 * sum(1 for x in allv if x < 30) / len(allv), len(allv)))


def main(argv):
    if not argv or argv[0] in ("-h", "--help"):
        print(__doc__)
        return 0
    cmd = argv[0]
    if cmd == "slots":
        print(n_slots())
        return 0
    if cmd == "status":
        status()
        return 0
    if cmd == "fps":
        fps(argv[1:])
        return 0
    if cmd == "pick":
        # soaslot.sh: wait until a slot is free and print its path; the shell then takes it with
        # flock -n on its own descriptor (and asks again if another process was quicker).
        fd = acquire(argv[1] if len(argv) > 1 else "game")
        if fd < 0:
            return 1
        path = os.readlink("/proc/self/fd/%d" % fd)
        os.close(fd)
        print(path)
        return 0
    if cmd == "run":
        args, name = argv[1:], None
        if args[:1] == ["--name"]:
            name, args = args[1], args[2:]
        if args[:1] == ["--"]:
            args = args[1:]
        if not args:
            print("soaslot: run: no command", file=sys.stderr)
            return 2
        if not name:  # the game binary's name (past `timeout -k 10 N`, `env`, `nice`)
            games = [os.path.basename(a) for a in args if os.path.basename(a) in ("soa", "soa-emu", "soa-viewer")]
            name = games[0] if games else os.path.basename(args[0])
        fd = acquire(name)
        if fd >= 0:
            os.set_inheritable(fd, True)
            os.environ["SOA_SLOT_HELD"] = "1"
        os.execvp(args[0], args)
    print("soaslot: unknown command %s (run, status, slots)" % cmd, file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
