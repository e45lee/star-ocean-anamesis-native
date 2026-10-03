"""The control FIFO (runtime/src/app/host.cpp; control/soactl.py is its CLI): one write of
newline-separated commands; screenshots are waited for."""
import os
import time


def deliver(fifo, cmds, timeout=120, on_shot=None, alive=None):
    """Sends cmds (tap:X:Y, wait:MS, shot:PATH, text:S, quit, ...) in one write, then waits until
    every shot in the batch is written (on_shot(path) for each, in the order they come). Returns
    (sent, pending): sent is False when nobody opened the FIFO for reading within timeout; pending
    lists the shots not written within timeout (or when alive(), checked every second, turns False:
    the client exited or crashed)."""
    cmds = ["shot:" + os.path.abspath(c[5:]) if c.startswith("shot:") else c for c in cmds]
    shots = {c[5:]: (os.path.getmtime(c[5:]) if os.path.exists(c[5:]) else None) for c in cmds if c.startswith("shot:")}
    deadline = time.monotonic() + timeout
    data = ("\n".join(cmds) + "\n").encode()
    while True:
        # Open without blocking forever: with no reader (the client exited, or isn't listening
        # yet) a plain open() would hang.
        try:
            fd = os.open(fifo, os.O_WRONLY | os.O_NONBLOCK)
        except OSError:
            if time.monotonic() > deadline:
                return False, list(shots)
            time.sleep(0.2)
            continue
        try:
            os.set_blocking(fd, True)
            os.write(fd, data)  # one write (under PIPE_BUF: atomic)
            break
        except BrokenPipeError:
            # the reader closed its end between our open and write (it reopens the FIFO after
            # each EOF): send again
            if time.monotonic() > deadline:
                return False, list(shots)
            time.sleep(0.2)
        finally:
            os.close(fd)
    deadline = time.monotonic() + timeout
    checked = time.monotonic()
    while shots and time.monotonic() < deadline:
        if alive is not None and time.monotonic() - checked >= 1:
            checked = time.monotonic()
            if not alive():
                break
        for p, old in list(shots.items()):
            if os.path.exists(p) and os.path.getmtime(p) != old and os.path.getsize(p) > 0:
                # the PNG is written in one go; give it a moment to be complete
                time.sleep(0.2)
                del shots[p]
                if on_shot:
                    on_shot(p)
        time.sleep(0.2)
    return True, list(shots)


def send(fifo, cmds, timeout=120, alive=None):
    """deliver(); True when the commands were sent and every shot was written."""
    sent, pending = deliver(fifo, cmds, timeout, alive=alive)
    return sent and not pending
