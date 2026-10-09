"""The guest debugger at a milestone (PLAN-consolidate step 7's control-layer part): a run started
with Config(gdb=True) gets `--gdb 127.0.0.1:0` (the runtime's GDB remote stub for the AArch64
guest: soa, soa-emu, soa-viewer; `[::1]:0` with Config(loopback="::1"); port 0: the client picks
one and logs it, which works for a Windows client too: a port tried from WSL stays refused to
Windows for a while), and Run.gdb() connects control/gdbclient.py's GdbClient to it, e.g.

    s = Run(target, layout, Config(..., gdb=True))
    ... s.wait_for("home", ...)                      # a milestone
    with s.gdb() as g:                               # stops every guest thread
        gdb.break_symbol(g, "_ZN4Aska14RenderDeviceGL31SwapBuffers_RenderThreadContextEv")
        g.cont(timeout=60)
        this = g.reg("x0"); raw = g.read(this, 0x40)
    # leaving the block detaches: breakpoints removed, the client runs on

The stub and the client are runtime/src/core/gdbstub.cpp and control/gdbclient.py; Run.gdb() raises
GdbUnavailable for a run not started with it or a client that never logged its stub's port. The session `gdb-probe`
(control/run.py gdb-probe) is the end-to-end check: attach at home, a breakpoint hit, registers and
memory read, a step, detach, the client runs on."""
import contextlib

import gdbclient  # control/gdbclient.py


class GdbUnavailable(RuntimeError):
    pass


def host_port(host, port):
    return "[%s]:%d" % (host, port) if ":" in host else "%s:%d" % (host, port)


def client_args(port, host="127.0.0.1"):
    """The client's options for a stub on HOST:PORT (port 0: the client picks it, listen_port)."""
    return ["--gdb", host_port(host, port)]


LISTENING = "I/gdb: GDB stub listening on "


def listen_port(log):
    """The port the client's stub listens on, from its log line ("I/gdb: GDB stub listening on
    HOST:PORT (...)", core/gdbstub.cpp); None until it is there."""
    try:
        with open(log, errors="replace") as f:
            for line in f:
                if line.startswith(LISTENING):
                    return int(line[len(LISTENING):].split()[0].rsplit(":", 1)[1])
    except (OSError, ValueError, IndexError):
        pass
    return None


@contextlib.contextmanager
def attach(port, timeout=30.0, host="127.0.0.1"):
    """A GdbClient connected to the stub on HOST:PORT (the guest stopped); detached on exit."""
    g = gdbclient.GdbClient(host, port, timeout=timeout)
    try:
        yield g
    finally:
        try:
            g.detach()
        except Exception:
            pass


def symbol_vaddr(symbol, lib=None):
    """The ELF vaddr of a game-library symbol (mangled; gdbclient's, read with pyelftools)."""
    return gdbclient.symbol_vaddr(symbol, lib)


def break_symbol(g, symbol, lib=None):
    """A breakpoint on a game-library function; returns its address."""
    addr = g.lib_base() + symbol_vaddr(symbol, lib)
    g.set_break(addr)
    return addr
