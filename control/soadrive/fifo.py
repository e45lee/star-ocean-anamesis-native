"""The control FIFO (runtime/src/app/host.cpp; control/soactl.py is its CLI): one write of
newline-separated commands; screenshots are waited for. An address "tcp:HOST:PORT" is the TCP
control channel instead (`--control tcp:...`: the Windows programs from WSL, soadrive/winhost.py):
one connection per batch."""
import os
import socket
import time

# address -> a function giving the client's spelling of a local path (the shot:PATH commands): set
# for a Windows client (winhost.winpath); the screenshot is still waited for at the local path
CLIENT_PATH = {}


def _open_tcp(addr):
    host, _, port = addr[4:].rpartition(":")
    return socket.create_connection((host or "127.0.0.1", int(port)), timeout=5)


def listening(addr):
    """The client's channel is there: the FIFO exists, or the TCP port accepts a connection."""
    if not addr.startswith("tcp:"):
        return os.path.exists(addr)
    try:
        _open_tcp(addr).close()
        return True
    except OSError:
        return False


def has_reader(addr, wait=0.0):
    """Someone reads the channel (within `wait` s): a FIFO with a reader (opening it for writing
    without blocking fails with ENXIO when there is none; listening() only sees that the FIFO
    exists; the client reopens it after each batch, hence the wait), or a TCP port that accepts a
    connection."""
    end = time.monotonic() + wait
    while True:
        if addr.startswith("tcp:"):
            if listening(addr):
                return True
        else:
            try:
                os.close(os.open(addr, os.O_WRONLY | os.O_NONBLOCK))
                return True
            except OSError:
                pass
        if time.monotonic() >= end:
            return False
        time.sleep(0.1)


def deliver(fifo, cmds, timeout=120, on_shot=None, alive=None):
    """Sends cmds (tap:X:Y, wait:MS, shot:PATH, text:S, quit, ...) in one write, then waits until
    every shot in the batch is written (on_shot(path) for each, in the order they come). Returns
    (sent, pending): sent is False when nobody opened the FIFO for reading within timeout; pending
    lists the shots not written within timeout (or when alive(), checked every second, turns False:
    the client exited or crashed)."""
    cmds = ["shot:" + os.path.abspath(c[5:]) if c.startswith("shot:") else c for c in cmds]
    shots = {c[5:]: (os.path.getmtime(c[5:]) if os.path.exists(c[5:]) else None) for c in cmds if c.startswith("shot:")}
    deadline = time.monotonic() + timeout
    conv = CLIENT_PATH.get(fifo)
    if conv:
        cmds = ["shot:" + conv(c[5:]) if c.startswith("shot:") else c for c in cmds]
    data = ("\n".join(cmds) + "\n").encode()
    while fifo.startswith("tcp:"):
        try:
            with _open_tcp(fifo) as c:
                c.sendall(data)
            break
        except OSError:
            if time.monotonic() > deadline or (alive is not None and not alive()):
                return False, list(shots)
            time.sleep(0.2)
    while not fifo.startswith("tcp:"):
        # Open without blocking forever: with no reader (the client exited, or isn't listening
        # yet) a plain open() would hang.
        try:
            fd = os.open(fifo, os.O_WRONLY | os.O_NONBLOCK)
        except OSError:
            if time.monotonic() > deadline or (alive is not None and not alive()):
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
