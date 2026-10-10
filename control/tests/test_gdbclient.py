"""control/gdbclient.py against the runtime's GDB stub (pytest; no game): the protocol encodings, then
`soaruntime_tests --gdb-demo` (a guest loop under the JIT with the stub listening) driven by the client
and, when installed, by gdb-multiarch, over 127.0.0.1 and over IPv6 (::1); a breakpoint on a native
(--native: the loop's leaf replaced by host code); a fault reported before the crash. Skipped when
build/runtime/soaruntime_tests isn't built.

SOA_GDB_DEMO=PATH runs another build of the demo, e.g. the Windows one from a stage on the Windows
drive (WSL's mirrored networking shares 127.0.0.1; the ::1 cases are skipped there):
    SOA_GDB_DEMO=/mnt/c/soa-win-NAME/build-win/runtime/soaruntime_tests.exe .venv/bin/pytest control/tests/test_gdbclient.py"""
import os
import shutil
import signal
import socket
import subprocess
import sys

import pytest

import gdbclient

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

GDBINIT = os.path.join(REPO, "control", "gdbinit-soa")
DEMO = os.environ.get("SOA_GDB_DEMO") or os.path.join(REPO, "build", "runtime", "soaruntime_tests")
WINDOWS = DEMO.lower().endswith(".exe")
needs_demo = pytest.mark.skipif(not os.access(DEMO, os.X_OK), reason=DEMO + " not built")


def ipv6_loopback():
    if not socket.has_ipv6:
        return False
    try:
        with socket.socket(socket.AF_INET6, socket.SOCK_STREAM) as s:
            s.bind(("::1", 0))
        return True
    except OSError:
        return False


# WSL's mirrored networking shares 127.0.0.1 with Windows, not ::1 (a Windows listener on ::1 refuses
# WSL's connections): a Windows demo is checked over ::1 by a Windows python instead (runtime/README.md).
V6_SKIP = "no IPv6 loopback" if not ipv6_loopback() else \
    "a Windows demo from WSL: mirrored networking doesn't share ::1" if WINDOWS and sys.platform.startswith("linux") else ""
HOSTS = ["127.0.0.1", pytest.param("::1", marks=pytest.mark.skipif(bool(V6_SKIP), reason=V6_SKIP))]


def test_encodings():
    assert gdbclient.frame(b"OK") == b"$OK#9a"
    assert gdbclient.frame(b"a$b") == b"$a}\x04b#44"
    pkts, rest = gdbclient.parse_packets(b"+$OK#9a$T05thread:1f;swbreak:;#")
    assert pkts == [b"OK"] and rest.startswith(b"$T05")
    assert gdbclient.unescape(b"a}\x03b0* ") == b"a#b0000"
    assert gdbclient.parse_stop("T05thread:1f;swbreak:;") == {"sig": 5, "tid": 0x1F, "swbreak": True}
    assert gdbclient.split_addr("[::1]:1234") == ("::1", 1234) and gdbclient.split_addr(":7") == ("127.0.0.1", 7)


def test_timeouts_with_a_fake_stub():
    """cont() without a timeout waits as long as the stop takes (not the client's 30 s or a previous call's);
    every other reply keeps the client's own timeout."""
    import threading
    import time
    srv = socket.socket()
    srv.bind(("127.0.0.1", 0))
    srv.listen(1)
    seen = []

    def stub():
        c, _ = srv.accept()
        buf = b""
        with c:
            while True:
                data = c.recv(4096)
                if not data:
                    return
                buf += data
                pkts, buf = gdbclient.parse_packets(buf)
                for p in pkts:
                    seen.append(p)
                    if p == b"vCont;c":
                        time.sleep(1.5)  # longer than the client's timeout
                        c.sendall(gdbclient.frame(b"T05thread:2;"))
                    elif p.startswith(b"qSupported"):
                        c.sendall(gdbclient.frame(b"PacketSize=4000"))
                    elif p == b"QStartNoAckMode":
                        c.sendall(b"+" + gdbclient.frame(b"OK"))
                    elif p == b"?":
                        c.sendall(gdbclient.frame(b"T05thread:1;"))
                    else:
                        c.sendall(gdbclient.frame(b"OK"))

    th = threading.Thread(target=stub, daemon=True)
    th.start()
    g = gdbclient.GdbClient("127.0.0.1", srv.getsockname()[1], timeout=0.5)
    try:
        assert g.cont()["tid"] == 2
        assert g.sock.gettimeout() is None
        assert g.cmd("Hg2") == "OK" and g.sock.gettimeout() == 0.5
        with pytest.raises(TimeoutError):
            g.cont(timeout=0.2)
    finally:
        g.sock.close()
        srv.close()


def listen_addr(host):
    return "[%s]:0" % host if ":" in host else "%s:0" % host


def start_demo(host="127.0.0.1", *extra):
    p = subprocess.Popen([DEMO, "--gdb-demo", listen_addr(host), *extra], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    words = p.stdout.readline().split()  # gdb-demo port N code A data D leaf L calls C
    if not words:
        p.kill()
        raise AssertionError("the demo didn't start: " + p.stderr.read())
    info = {words[i]: int(words[i + 1], 0) for i in range(1, len(words) - 1, 2)}
    return p, info


def finish(p):
    out, err = p.communicate(timeout=30)
    assert p.returncode == 0 and "gdb-demo done" in out, out + err


@needs_demo
@pytest.mark.parametrize("host", HOSTS)
def test_client_break_step_continue_detach(host):
    p, d = start_demo(host)
    try:
        g = gdbclient.GdbClient(host, d["port"])
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
        finish(p)
    finally:
        if p.poll() is None:
            p.kill()


# --at-leaf: the guest is already stopped at the leaf when the client attaches (as the demo's loop
# often is under load). --slow-park: a thread whose JIT stopped takes 200 ms to park; the stub must
# wait for it (it once reported such a thread "in host code" and answered a step with a stop in place).
AT_LEAF_OPTS = [pytest.param(o, id=" ".join(o)) for o in (["--at-leaf"], ["--slow-park"], ["--at-leaf", "--slow-park"])]


@needs_demo
@pytest.mark.parametrize("opts", AT_LEAF_OPTS)
def test_client_resumes_from_a_breakpoint_address(opts):
    p, d = start_demo("127.0.0.1", *opts)
    try:
        g = gdbclient.GdbClient("127.0.0.1", d["port"])
        if "--at-leaf" in opts:
            assert g.reg("pc") == d["leaf"]
        g.set_break(d["leaf"])
        n = g.read_u64(d["data"])
        st = g.cont(timeout=10)  # steps over the breakpoint at the pc (if there), then on to it
        assert st["swbreak"] and g.reg("pc") == d["leaf"] and g.read_u64(d["data"]) in (n, n + 1)
        n = g.read_u64(d["data"])
        st = g.cont(timeout=10)  # not the same stop again: one more iteration
        assert st["swbreak"] and g.reg("pc") == d["leaf"] and g.read_u64(d["data"]) == n + 1 and g.reg("x0") == n + 1
        g.del_break(d["leaf"])
        g.step()
        assert g.reg("pc") == d["leaf"] + 4 and g.reg("x0") == n + 1 + 0x10
        g.write(d["data"] + 8, (1).to_bytes(8, "little"))
        g.detach()
        finish(p)
    finally:
        if p.poll() is None:
            p.kill()


@needs_demo
@pytest.mark.parametrize("host", HOSTS)
def test_breakpoint_on_a_native(host):
    """--native: the leaf is host code. The breakpoint stops before it runs (x0 = the guest's argument),
    stepping over it runs it once, `monitor natives` lists it."""
    p, d = start_demo(host, "--native")
    try:
        g = gdbclient.GdbClient(host, d["port"])
        nat = g.natives("gdb_demo")
        assert len(nat) == 1 and nat[0]["addr"] == d["leaf"] and nat[0]["symbol"] == "gdb_demo_leaf" and nat[0]["native"] == "host_leaf"
        g.set_break(d["leaf"])
        st = g.cont(timeout=10)
        tid = st["tid"]
        assert st["swbreak"] and g.reg("pc", tid) == d["leaf"]
        n, calls = g.read_u64(d["data"]), g.read_u64(d["calls"])
        assert g.reg("x0", tid) == n and calls == n - 1  # the native hasn't run for this call yet
        st = g.cont(timeout=10)  # step over (the native runs once), on to the next call
        assert st["swbreak"] and g.reg("pc", st["tid"]) == d["leaf"]
        assert g.read_u64(d["data"]) == n + 1 and g.read_u64(d["calls"]) == calls + 1
        g.del_break(d["leaf"])
        g.write(d["data"] + 8, (1).to_bytes(8, "little"))
        g.detach()
        finish(p)
    finally:
        if p.poll() is None:
            p.kill()


@needs_demo
def test_step_from_a_native_then_step_again():
    """A step from a native's entry runs it and stops at the hook's RET; with --slow-park the thread is
    still on its way back to its JIT, where it parks: the next step waits for that, then runs the RET."""
    p, d = start_demo("127.0.0.1", "--native", "--slow-park")
    try:
        g = gdbclient.GdbClient("127.0.0.1", d["port"])
        g.set_break(d["leaf"])
        st = g.cont(timeout=10)
        assert st["swbreak"] and g.reg("pc", st["tid"]) == d["leaf"]
        g.del_break(d["leaf"])
        g.step(st["tid"])
        assert g.reg("pc", st["tid"]) == d["leaf"] + 4
        g.step(st["tid"])
        assert g.reg("pc", st["tid"]) == d["code"] + 0x18  # the RET: back after the loop's bl
        g.write(d["data"] + 8, (1).to_bytes(8, "little"))
        g.detach()
        finish(p)
    finally:
        if p.poll() is None:
            p.kill()


@needs_demo
def test_fault_is_reported_before_the_crash():
    p, d = start_demo("127.0.0.1", "--fault")
    try:
        g = gdbclient.GdbClient("127.0.0.1", d["port"])
        g.write(d["data"] + 8, (1).to_bytes(8, "little"))
        st = g.cont(timeout=20)
        assert st["sig"] == 11  # SIGSEGV in the protocol's numbering (an access violation on Windows)
        g.detach()
        p.communicate(timeout=20)
        # Windows: STATUS_ACCESS_VIOLATION, whose low byte is all a WSL interop process's exit status keeps
        assert p.returncode == (0xC0000005 & 0xFF if WINDOWS else -signal.SIGSEGV)
    finally:
        if p.poll() is None:
            p.kill()


@needs_demo
@pytest.mark.skipif(not shutil.which("gdb-multiarch"), reason="gdb-multiarch not installed")
@pytest.mark.parametrize("host", HOSTS)
@pytest.mark.parametrize("opts", [pytest.param([], id="running")] + AT_LEAF_OPTS)
def test_gdb_multiarch_attaches(host, opts):
    """gdb steps over a breakpoint at the pc itself (z0, step, Z0) when it resumes: continue ends at
    the leaf one iteration later at the latest, stepi one instruction on."""
    p, d = start_demo(host, *opts)
    try:
        target = "[%s]:%d" % (host, d["port"]) if ":" in host else "%s:%d" % (host, d["port"])
        cmds = ["set pagination off", "target remote " + target, "info registers x19", f"break *{d['leaf']:#x}",
                "continue", "p/x $pc", "stepi", "p/x $pc", "delete", f"set {{long}}({d['data'] + 8:#x}) = 1", "detach"]
        r = subprocess.run(["gdb-multiarch", "-batch", "-nx", "-x", GDBINIT] + [x for c in cmds for x in ("-ex", c)], capture_output=True,
                           text=True, timeout=60)
        assert f"{d['data']:#x}" in r.stdout, r.stdout + r.stderr
        assert "Breakpoint 1," in r.stdout and f"$1 = {d['leaf']:#x}" in r.stdout and f"$2 = {d['leaf'] + 4:#x}" in r.stdout, \
            r.stdout + r.stderr
        finish(p)
    finally:
        if p.poll() is None:
            p.kill()


@needs_demo
@pytest.mark.skipif(WINDOWS or not shutil.which("gdb"), reason="needs the host gdb on a Linux demo")
def test_gdbinit_host_native_break():
    """control/gdbinit-soa in a host gdb on the process: soa-native-break on a guest symbol stops in its
    native (the C++), called from the guest through the hook."""
    cmds = ["break soa::hook_guest_function", "run", "finish", "soa-natives gdb_demo", "soa-native-break gdb_demo_leaf", "delete 1",
            "continue", "bt 2", "kill"]
    r = subprocess.run(["gdb", "-batch", "-nx", "-x", GDBINIT] + [x for c in cmds for x in ("-ex", c)] +
                       ["--args", DEMO, "--gdb-demo", "127.0.0.1:0", "--native"], capture_output=True, text=True, timeout=120)
    out = r.stdout + r.stderr
    assert "gdb_demo_leaf  host_leaf" in out, out
    assert "soa: breakpoint 2 on the native for gdb_demo_leaf" in out and "hit Breakpoint 2" in out, out
    assert "host_leaf" in out.split("hit Breakpoint 2", 1)[1].splitlines()[0] and "CallSVC" in out, out
