"""The control FIFO (runtime/src/app/host.cpp; control/soactl.py's protocol): one write of
newline-separated commands; screenshots are waited for."""
import os
import time


def send(fifo, cmds, timeout=120):
    """Sends cmds (tap:X:Y, wait:MS, shot:PATH, text:S, quit, ...); returns once every shot in the
    batch is written. False when nobody reads the FIFO or a shot didn't come within timeout."""
    cmds = ["shot:" + os.path.abspath(c[5:]) if c.startswith("shot:") else c for c in cmds]
    shots = {c[5:]: (os.path.getmtime(c[5:]) if os.path.exists(c[5:]) else None) for c in cmds if c.startswith("shot:")}
    deadline = time.monotonic() + timeout
    data = ("\n".join(cmds) + "\n").encode()
    while True:
        try:
            fd = os.open(fifo, os.O_WRONLY | os.O_NONBLOCK)
        except OSError:
            if time.monotonic() > deadline:
                return False
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
                return False
            time.sleep(0.2)
        finally:
            os.close(fd)
    while shots and time.monotonic() < deadline:
        for p, old in list(shots.items()):
            if os.path.exists(p) and os.path.getmtime(p) != old and os.path.getsize(p) > 0:
                time.sleep(0.2)
                del shots[p]
        time.sleep(0.2)
    return not shots
