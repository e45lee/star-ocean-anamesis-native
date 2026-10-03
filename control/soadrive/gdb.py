"""The guest debugger at a milestone (PLAN-consolidate step 7's control-layer part): a run started
with Config(gdb=True) gets `--gdb 127.0.0.1:PORT` (the runtime's GDB remote stub for the AArch64
guest: soa, soa-emu, soa-viewer), and Run.gdb() connects control/gdbclient.py's GdbClient to it, e.g.

    s = Run(target, layout, Config(..., gdb=True))
    ... s.wait_for("home", ...)                      # a milestone
    with s.gdb() as g:                               # stops every guest thread
        gdb.break_symbol(g, "_ZN4Aska14RenderDeviceGL31SwapBuffers_RenderThreadContextEv")
        g.cont(timeout=60)
        this = g.reg("x0"); raw = g.read(this, 0x40)
    # leaving the block detaches: breakpoints removed, the client runs on

The stub and the client are agent rebuild-tooling's (runtime/src/core/gdbstub.cpp,
control/gdbclient.py); without control/gdbclient.py available() is False, Run.gdb() raises
GdbUnavailable and a run asked for gdb fails at start with the reason. The session `gdb-probe`
(control/run.py gdb-probe) is the end-to-end check: attach at home, a breakpoint hit, registers and
memory read, a step, detach, the client runs on."""
import contextlib
import importlib
import os
import subprocess
import sys

from .proc import REPO


class GdbUnavailable(RuntimeError):
    pass


def _client_module():
    sys.path.insert(0, os.path.join(REPO, "control"))
    try:
        return importlib.import_module("gdbclient")
    except ImportError:
        return None


def available():
    """True when control/gdbclient.py exists (the runtime's --gdb comes with it)."""
    return _client_module() is not None


def client_args(port):
    """The client's options for a stub on 127.0.0.1:PORT."""
    return ["--gdb", "127.0.0.1:%d" % port]


@contextlib.contextmanager
def attach(port, timeout=30.0):
    """A GdbClient connected to the stub on 127.0.0.1:PORT (the guest stopped); detached on exit."""
    mod = _client_module()
    if mod is None:
        raise GdbUnavailable("control/gdbclient.py isn't in this checkout (the runtime's GDB stub, agent rebuild-tooling)")
    g = mod.GdbClient("127.0.0.1", port, timeout=timeout)
    try:
        yield g
    finally:
        try:
            g.detach()
        except Exception:
            pass


def symbol_vaddr(symbol, lib=None):
    """The ELF vaddr of a game-library symbol (mangled): gdbclient's (pyelftools), else `nm -D`
    (the system python the wrappers run may lack pyelftools)."""
    mod = _client_module()
    try:
        return mod.symbol_vaddr(symbol, lib)
    except ImportError:
        pass
    path = lib or os.path.join(REPO, "work", "libSOA-3.7.0.so")
    for args in (["nm", "-D", path], ["nm", path]):
        out = subprocess.run(args, capture_output=True, text=True).stdout
        for ln in out.splitlines():
            f = ln.split()
            if len(f) == 3 and f[2] == symbol and int(f[0], 16):
                return int(f[0], 16)
    raise KeyError("%s not in %s" % (symbol, path))


def break_symbol(g, symbol, lib=None):
    """A breakpoint on a game-library function; returns its address."""
    addr = g.lib_base() + symbol_vaddr(symbol, lib)
    g.set_break(addr)
    return addr
