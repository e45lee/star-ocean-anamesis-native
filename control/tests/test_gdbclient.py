"""control/gdbclient.py against the runtime's GDB stub (pytest; no game): the protocol encodings, then
`soaruntime_tests --gdb-demo` (a guest loop under the JIT with the stub listening) driven by the client
and, when installed, by gdb-multiarch. Skipped when build/runtime/soaruntime_tests isn't built."""
import os
import shutil
import signal
import subprocess
import sys

import pytest

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(REPO, "control"))
import gdbclient  # noqa: E402

DEMO = os.path.join(REPO, "build", "runtime", "soaruntime_tests")
needs_demo = pytest.mark.skipif(not os.access(DEMO, os.X_OK), reason="build/runtime/soaruntime_tests not built")


def test_encodings():
    assert gdbclient.frame(b"OK") == b"$OK#9a"
    assert gdbclient.frame(b"a$b") == b"$a}\x04b#44"
    pkts, rest = gdbclient.parse_packets(b"+$OK#9a$T05thread:1f;swbreak:;#")
    assert pkts == [b"OK"] and rest.startswith(b"$T05")
    assert gdbclient.unescape(b"a}\x03b0* ") == b"a#b0000"
    assert gdbclient.parse_stop("T05thread:1f;swbreak:;") == {"sig": 5, "tid": 0x1F, "swbreak": True}


def start_demo(*extra):
    p = subprocess.Popen([DEMO, "--gdb-demo", "127.0.0.1:0", *extra], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    words = p.stdout.readline().split()  # gdb-demo port N code A data D leaf L
    info = {words[i]: int(words[i + 1], 0) for i in range(1, len(words) - 1, 2)}
    return p, info


@needs_demo
def test_client_break_step_continue_detach():
    p, d = start_demo()
    try:
        g = gdbclient.GdbClient("127.0.0.1", d["port"])
        assert g.stop_info["sig"] == 5 and g.stop_info["tid"] in g.threads()
        regs = g.regs()
        assert regs["x19"] == d["data"]
        g.set_break(d["leaf"])
        st = g.cont(timeout=10)
        assert st["swbreak"] and g.reg("pc") == d["leaf"]
        n = g.read_u64(d["data"])
        assert g.reg("x0") == n
        st = g.cont(timeout=10)  # steps over the breakpoint, then hits it again one iteration later
        assert st["swbreak"] and g.read_u64(d["data"]) == n + 1
        g.del_break(d["leaf"])
        g.step()
        assert g.reg("pc") == d["leaf"] + 4 and g.reg("x0") == n + 1 + 0x10
        assert "0x" in g.monitor("threads") or "parked" in g.monitor("threads")
        g.write(d["data"] + 8, (1).to_bytes(8, "little"))  # the loop's stop flag
        g.detach()
        out, _ = p.communicate(timeout=20)
        assert p.returncode == 0 and "gdb-demo done" in out
    finally:
        if p.poll() is None:
            p.kill()


@needs_demo
def test_fault_is_reported_before_the_crash():
    p, d = start_demo("--fault")
    try:
        g = gdbclient.GdbClient("127.0.0.1", d["port"])
        g.write(d["data"] + 8, (1).to_bytes(8, "little"))
        st = g.cont(timeout=20)
        assert st["sig"] == signal.SIGSEGV
        g.detach()
        p.communicate(timeout=20)
        assert p.returncode == -signal.SIGSEGV
    finally:
        if p.poll() is None:
            p.kill()


@needs_demo
@pytest.mark.skipif(not shutil.which("gdb-multiarch"), reason="gdb-multiarch not installed")
def test_gdb_multiarch_attaches():
    p, d = start_demo()
    try:
        cmds = ["set pagination off", f"target remote 127.0.0.1:{d['port']}", "info registers x19", f"break *{d['leaf']:#x}",
                "continue", "p/x $pc", "stepi", "p/x $pc", "delete", f"set {{long}}({d['data'] + 8:#x}) = 1", "detach"]
        r = subprocess.run(["gdb-multiarch", "-batch", "-nx"] + [x for c in cmds for x in ("-ex", c)], capture_output=True, text=True, timeout=60)
        assert f"{d['data']:#x}" in r.stdout, r.stdout + r.stderr
        assert "Breakpoint 1," in r.stdout and f"= {d['leaf'] + 4:#x}" in r.stdout, r.stdout + r.stderr
        out, _ = p.communicate(timeout=20)
        assert p.returncode == 0 and "gdb-demo done" in out
    finally:
        if p.poll() is None:
            p.kill()
