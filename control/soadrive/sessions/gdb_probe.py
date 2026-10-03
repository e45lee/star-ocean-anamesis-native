"""Session `gdb-probe`: the guest debugger at a milestone, end to end (soadrive/gdb.py over the
runtime's GDB stub, control/gdbclient.py): the client starts with --gdb 127.0.0.1:PORT, logs in to
home (the shared launch flow), then the session attaches (every guest thread stops), reads the game
library's load base, sets a breakpoint on a function the renderer calls every frame
(Aska::RenderDeviceGL::SwapBuffers_RenderThreadContext), continues to it, reads x0 and 64 bytes at
x0, single-steps, detaches; the client must run on afterwards (the footer's ガチャ -> GetGachaInData).
OUT/gdb.txt has what was read. Prints "PASS: ..." or "FAIL: ..." (exit 1).

Usage: control/run.py [--target T] gdb-probe <soa> <out-dir> <scratch-dir>
  (soa is the port's binary; --target emu runs soa-emu, SOA_EMU overrides it)
Targets: port-inproc (default), port-server, emu."""
import os

from .. import gdb
from ..flows import gacha, launch
from . import common

TARGETS = ("port-inproc", "port-server", "emu")
WRAPPER = "control/run.py gdb-probe"
SYMBOL = "_ZN4Aska14RenderDeviceGL31SwapBuffers_RenderThreadContextEv"


def options(ap):
    common.port_options(ap, extra=False)


def main(o):
    s = common.port_run(o, common.port_config(o, gdb=True))
    got = {}

    def body(s):
        launch.title(s, "01-title")
        launch.login_to_home(s, None, None, "02-home")
        with s.gdb() as g:
            got["threads"] = len(g.threads())
            got["base"] = g.lib_base()
            addr = gdb.break_symbol(g, SYMBOL)
            stop = g.cont(timeout=60)
            pc = g.reg("pc", stop.get("tid"))
            s.check("breakpoint hit at %s (pc %#x, want %#x)" % (SYMBOL, pc, addr), stop.get("swbreak") and pc == addr)
            got["x0"] = x0 = g.reg("x0", stop.get("tid"))
            got["mem"] = g.read(x0, 0x40).hex()
            g.del_break(addr)
            g.step(stop.get("tid"))
            got["pc_after_step"] = g.reg("pc", stop.get("tid"))
            s.check("one instruction stepped (pc %#x -> %#x)" % (pc, got["pc_after_step"]), got["pc_after_step"] == pc + 4)
        s.ok("detached (%d guest threads, library at %#x)" % (got["threads"], got["base"]))
        # the client runs on after the detach
        gacha.open_gacha(s, "03-gacha-after-detach")

    ok = common.drive(s, body)
    with open(os.path.join(o.out, "gdb.txt"), "w") as f:
        for k, v in got.items():
            f.write("%s %s\n" % (k, hex(v) if isinstance(v, int) else v))
    if not ok:
        return 1
    fails = common.checks((got.get("x0"), "x0 is 0 at the breakpoint"),
                          (got.get("mem") and len(got["mem"]) == 128, "64 bytes at x0 weren't read"))
    return common.verdict(s, fails, "attached at home: a breakpoint on %s hit, x0 %#x and 64 bytes at it read, a step, "
                          "detached, the client ran on (GetGachaInData)" % (SYMBOL, got.get("x0") or 0))


