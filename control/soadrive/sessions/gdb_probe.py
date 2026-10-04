"""Session `gdb-probe`: the guest debugger at a milestone, end to end (soadrive/gdb.py over the
runtime's GDB stub, control/gdbclient.py): the client starts with --gdb 127.0.0.1:PORT, logs in to
home (the shared launch flow), then the session attaches (every guest thread stops), reads the game
library's load base, sets a breakpoint on a function the renderer calls every frame
(Aska::RenderDeviceGL::SwapBuffers_RenderThreadContext), continues to it, reads x0 and 64 bytes at
x0, single-steps; then a natived function (the port's targets): `monitor natives` lists it, a
breakpoint on its guest entry stops before the native runs (pc at the entry, x0 = its `this`), a
step runs the whole native (pc at the hook's RET); detaches; the client must run on afterwards (the
footer's ガチャ -> GetGachaInData). OUT/gdb.txt has what was read. Prints "PASS: ..." or "FAIL: ..."
(exit 1). A Windows binary (soa.exe) makes it a Windows run (soadrive/winhost.py).

Usage: control/run.py [--target T] gdb-probe [--ipv6] <soa> <out-dir> <scratch-dir>
  (soa is the port's binary; --target emu runs soa-emu, SOA_EMU overrides it)
  --ipv6: the programs talk over ::1 (soa-server --listen [::1]:P, soa --server [::1]:P, and the
          stub on [::1] for a Linux client)
Targets: port-inproc (default), port-server, emu."""
import os

from .. import gdb
from ..flows import gacha, launch
from . import common

TARGETS = ("port-inproc", "port-server", "emu")
WRAPPER = "control/run.py gdb-probe"
SYMBOL = "_ZN4Aska14RenderDeviceGL31SwapBuffers_RenderThreadContextEv"
# Natives called often at home, the first one installed that is hit within the timeout is used: the
# renderer's sort of renderable objects, then the asset map's lookup, then the port's own per-frame
# CPhase::Progress wrapper.
NATIVES = ("_ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE7DescendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE",
           "_ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE6AscendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE",
           "_ZN6CPhase8ProgressEv")


def options(ap):
    ap.add_argument("--ipv6", action="store_true", help="the programs talk over ::1 instead of 127.0.0.1")
    common.port_options(ap, extra=False)


def probe_native(s, g, got):
    """A breakpoint on a natived function: stops before the native runs; a step runs all of it."""
    natives = {n["symbol"]: n for n in g.natives()}
    got["natives"] = len(natives)
    s.check("monitor natives lists the installed natives (%d)" % len(natives), len(natives) > 0)
    for sym in NATIVES:
        n = natives.get(sym)
        if not n:
            continue
        g.set_break(n["addr"])
        try:
            stop = g.cont(timeout=20)
        except TimeoutError:
            g.del_break(n["addr"])
            s.note("native %s: not called within 20 s; the next one" % sym)
            continue
        tid = stop.get("tid")
        pc = g.reg("pc", tid)
        s.check("native breakpoint hit at %s (pc %#x, want %#x)" % (n["demangled"], pc, n["addr"]), stop.get("swbreak") and pc == n["addr"])
        got["native"], got["native_cpp"], got["native_x0"] = sym, n["native"], g.reg("x0", tid)
        g.del_break(n["addr"])
        g.step(tid)
        got["native_pc_after_step"] = g.reg("pc", tid)
        s.check("a step ran the whole native (pc %#x -> %#x, the hook's RET)" % (pc, got["native_pc_after_step"]),
                got["native_pc_after_step"] == pc + 4)
        return
    s.check("one of the natives %s was hit" % ", ".join(NATIVES), False)


def main(o):
    s = common.port_run(o, common.port_config(o, gdb=True, loopback="::1" if o.ipv6 else "127.0.0.1"))
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
            if o.target != "emu":  # (soa-emu has no natives)
                probe_native(s, g, got)
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
    if o.target != "emu":
        fails += common.checks((got.get("native"), "no native breakpoint was hit"))
    native = "; a native (%s, %s) stopped at its entry and stepped whole" % (got.get("native_cpp"), got.get("native")) if got.get("native") else ""
    return common.verdict(s, fails, "attached at home%s: a breakpoint on %s hit, x0 %#x and 64 bytes at it read, a step%s; "
                          "detached, the client ran on (GetGachaInData)" % (" over ::1" if o.ipv6 else "", SYMBOL, got.get("x0") or 0, native))


