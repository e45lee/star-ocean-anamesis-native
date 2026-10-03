"""Milestones: waiting for what a client or its server logged (PLAN-consolidate D4: the one
implementation; control/flowctl.py's wait-log / tap-until and targets.Run's waits use it).

Two ways to look at a log:
  * whole-file predicates (grep, count): "has X happened at all / how often" -- tests/diff's flows
    and the emulator sessions, which read the packet log;
  * a cursor (LogCursor): "the next line matching X after the previous wait" -- the port sessions'
    `flowctl.py wait-log` chain. Its position persists in LOG.pos, so successive CLI calls and
    library calls on the same log share it (the contract every shell session relies on).

poll() is the one wait loop: a predicate, a time limit, an alive() check and an optional action
repeated every `every` seconds (a tap the game can drop while a screen fades in)."""
import os
import re
import time


class Failed(Exception):
    """A step that wasn't reached (the CLI prints it as 'FAIL: ...' and exits 1)."""


def grep(path, rx):
    try:
        with open(path, errors="replace") as f:
            return re.search(rx, f.read(), re.M) is not None
    except FileNotFoundError:
        return False


def count(path, rx):
    try:
        with open(path, errors="replace") as f:
            return len(re.findall(rx, f.read(), re.M))
    except FileNotFoundError:
        return 0


def last(path, rx):
    """The last line matching rx (None when none does)."""
    try:
        with open(path, errors="replace") as f:
            hits = [ln for ln in f.read().splitlines() if re.search(rx, ln)]
    except FileNotFoundError:
        return None
    return hits[-1] if hits else None


def poll(secs, pred, alive=None, action=None, every=4, step=1.0):
    """Waits until pred() (True) or secs pass / alive() turns False (False). With action, calls it
    first and then every `every` seconds while pred() is False."""
    end, nxt = time.monotonic() + secs, 0.0
    while not pred():
        if alive is not None and not alive():
            return False
        now = time.monotonic()
        if now > end:
            return False
        if action is not None and now >= nxt:
            action()
            nxt = time.monotonic() + every
        time.sleep(step)
    return True


class LogCursor:
    """Reads a log from the position the previous wait left (LOG.pos; control/flowctl.py's Log).
    persist=False keeps the position in memory only."""

    def __init__(self, path, persist=True):
        self.path, self.posf, self.persist = path, path + ".pos", persist
        self.pos = 0
        self.load()

    def load(self):
        """The position LOG.pos holds (another cursor, or a flowctl.py call, may have moved it)."""
        if self.persist and os.path.exists(self.posf):
            try:
                self.pos = int(open(self.posf).read() or 0)
            except ValueError:
                pass

    def size(self):
        try:
            return os.path.getsize(self.path)
        except FileNotFoundError:
            return 0

    def lines(self):
        """The complete lines written since the position, as (start offset, end offset, text);
        the caller moves the position (self.pos = end) past the lines it consumed."""
        try:
            with open(self.path, "rb") as f:
                f.seek(self.pos)
                data = f.read()
        except FileNotFoundError:
            return []
        end = data.rfind(b"\n") + 1
        out, off = [], self.pos
        for raw in data[:end].split(b"\n")[:-1]:
            out.append((off, off + len(raw) + 1, raw.decode("utf-8", "replace")))
            off += len(raw) + 1
        return out

    def save(self):
        if self.persist:
            with open(self.posf, "w") as f:
                f.write(str(self.pos))

    def skip_to_end(self):
        self.pos = self.size()
        self.save()

    def wait(self, rx, timeout, stop=None, stop_from=0, alive=None):
        """The first new line matching rx within timeout s (None on timeout or when alive() turns
        False). With stop (a regex), returns ('stop', line) at the first line at or after offset
        stop_from matching it instead."""
        rx = re.compile(rx) if isinstance(rx, str) else rx
        stop = re.compile(stop) if isinstance(stop, str) else stop
        self.load()
        deadline = time.monotonic() + timeout
        while True:
            for off, end, line in self.lines():
                self.pos = end
                if rx.search(line):
                    self.save()
                    return line
                if stop is not None and off >= stop_from and stop.search(line):
                    self.save()
                    return ("stop", line)
            if time.monotonic() >= deadline or (alive is not None and not alive()):
                self.save()
                return None
            time.sleep(0.5)


# A transition the port logs (a port native: soa only); a tap followed by one was taken by the game.
PORT_PHASE = r"port_debug: phase "


def tap_until_log(send, log, pat, timeout=120, every=20, tries=5, cmds=(), stop=PORT_PHASE, note=None, alive=None):
    """Sends cmds and waits for pat on the log's cursor; resends after `every` s without it (at most
    `tries` sends), for taps the game drops under load. No resend once a `stop` line was logged
    after the send (a transition to somewhere else started: a second tap could land on the next
    screen). Returns (the matching line or None after timeout, the number of sends).
    control/flowctl.py tap-until."""
    rx = re.compile(pat)
    other = re.compile(stop) if stop else None
    lg = LogCursor(log) if isinstance(log, str) else log
    deadline = time.monotonic() + timeout
    sent, resend, sent_at = 0, True, 0
    while True:
        if resend and sent < tries:
            sent_at = lg.size()  # only lines after this count as "another phase started"
            send(list(cmds))
            sent += 1
            if sent > 1 and note:
                note("retry %d/%d: %s" % (sent, tries, " ".join(cmds)))
        left = deadline - time.monotonic()
        if left <= 0:
            return None, sent
        r = lg.wait(rx, min(every, left) if resend and sent < tries else left,
                    stop=other if resend else None, stop_from=sent_at, alive=alive)
        if isinstance(r, str):
            return r, sent
        if isinstance(r, tuple):  # another phase started: something took the tap, don't resend
            if note:
                note("note: %s after %s; not resending" % (r[1], " ".join(cmds)))
            resend = False
        elif alive is not None and not alive():
            return None, sent
