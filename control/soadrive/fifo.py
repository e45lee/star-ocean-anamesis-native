"""The control FIFO (runtime/src/app/host.cpp; control/soactl.py is its CLI): one write of
newline-separated commands; screenshots are waited for. An address "tcp:HOST:PORT" is the TCP
control channel instead (`--control tcp:...`: the Windows programs from WSL, soadrive/winhost.py):
one connection per batch."""
import array
import fcntl
import os
import socket
import termios
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


def consumed(fd, deadline, alive=None):
    """Waits until the FIFO's pipe holds no unread bytes (FIONREAD on the write end; Linux): True,
    or False at the deadline / when alive() turns False."""
    n = array.array("i", [0])
    while True:
        fcntl.ioctl(fd, termios.FIONREAD, n, True)
        if n[0] == 0:
            return True
        if time.monotonic() > deadline or (alive is not None and not alive()):
            return False
        time.sleep(0.01)


# Never probe a FIFO by opening it for writing and closing it: the client reads until EOF, then
# closes and reopens (runtime/src/app/host.cpp control_thread: fgets until EOF, fclose, fopen), and
# the probe's close is such an EOF, as is every batch's own; a batch written right after one can
# land in the reader that is already closing, and when the last reader and writer have closed the
# kernel drops what is left in the pipe (a `quit` lost that way: Run.stop, 2026-10-07). deliver()
# waits for a reader (ENXIO) instead of probing, and keeps its end open until the batch is read
# (consumed()), so back-to-back batches arrive.
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
            # Keep the write end open until the client has read the batch: a reader that had
            # already seen EOF (another writer's close) closes without reading it, and with no
            # writer left either the kernel would drop it; with ours open it waits in the pipe for
            # the client's next open (see the comment above deliver)
            if not consumed(fd, deadline, alive):
                return False, list(shots)
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
