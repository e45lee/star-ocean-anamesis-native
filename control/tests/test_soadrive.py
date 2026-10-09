"""control/soadrive: the driver library without a game (pytest): the log cursor and its LOG.pos
contract with control/flowctl.py, tap_until_log's resend rules, poll, the FIFO, ui370's names."""
import os
import re
import subprocess
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
CONTROL = os.path.dirname(HERE)
sys.path.insert(0, CONTROL)
from soadrive import fifo, milestones, proc, ui370  # noqa: E402
from soadrive.milestones import LogCursor, tap_until_log  # noqa: E402


def test_repo_root():
    assert os.path.isfile(os.path.join(proc.REPO, "control", "soadrive", "proc.py"))


def test_cursor_persists_and_is_shared_with_the_cli(tmp_path):
    log = tmp_path / "log.txt"
    log.write_text("a\nport_debug: phase 1 \nb\nport_debug: phase 1 \n")
    assert LogCursor(str(log)).wait("phase 1", 1) == "port_debug: phase 1 "
    # the CLI continues after the first match (LOG.pos), finds the second, then nothing
    flow = [sys.executable, os.path.join(CONTROL, "flowctl.py"), "wait-log", str(log), "phase 1", "1"]
    assert subprocess.run(flow, capture_output=True).returncode == 0
    r = subprocess.run(flow, capture_output=True, text=True)
    assert r.returncode == 1 and "FAIL: no log line matching" in r.stderr
    assert int((tmp_path / "log.txt.pos").read_text()) == log.stat().st_size


def test_cursor_ignores_a_partial_line(tmp_path):
    log = tmp_path / "log"
    log.write_text("start\nhalf")
    c = LogCursor(str(log), persist=False)
    assert c.wait("half", 0.2) is None
    with open(log, "a") as f:
        f.write(" done\n")
    assert c.wait("half done", 1) == "half done"
    assert not (tmp_path / "log.pos").exists()


def test_tap_until_resends_until_the_line(tmp_path):
    log = tmp_path / "log"
    log.write_text("")
    sent = []

    def send(cmds):
        sent.append(cmds)
        if len(sent) == 3:
            with open(log, "a") as f:
                f.write("request Login (fid 1)\n")

    line, n = tap_until_log(send, str(log), r"request Login ", timeout=10, every=0.3, tries=5, cmds=["tap:1:2"])
    assert line == "request Login (fid 1)" and n == 3 and sent == [["tap:1:2"]] * 3


def test_tap_until_stops_resending_after_a_phase_line(tmp_path):
    log = tmp_path / "log"
    log.write_text("")
    sent = []

    def send(cmds):
        sent.append(cmds)
        with open(log, "a") as f:
            f.write("port_debug: phase 7 \n")

    line, n = tap_until_log(send, str(log), r"never", timeout=1.5, every=0.3, tries=5, cmds=["tap:1:2"])
    assert line is None and n == 1


def test_poll_action_and_alive():
    calls = []
    assert milestones.poll(5, lambda: len(calls) >= 2, action=lambda: calls.append(1), every=0, step=0.01)
    assert not milestones.poll(5, lambda: False, alive=lambda: False, step=0.01)


def test_grep_count_last(tmp_path):
    p = tmp_path / "packets.log"
    p.write_text("> Login fid=1\n< LoginResult\n> Login fid=2\n")
    assert milestones.grep(str(p), r"^< LoginResult") and not milestones.grep(str(tmp_path / "none"), "x")
    assert milestones.count(str(p), r"^> Login ") == 2
    assert milestones.last(str(p), r"> Login") == "> Login fid=2"


def test_fifo_delivers_and_waits_for_shots(tmp_path):
    path = str(tmp_path / "fifo")
    os.mkfifo(path)
    shot = str(tmp_path / "s.png")
    got = []

    def reader():
        with open(path) as f:
            for line in f:
                got.append(line.strip())
                if line.startswith("shot:"):
                    time.sleep(0.3)
                    open(line[5:].strip(), "wb").write(b"png")
                    return

    t = threading.Thread(target=reader)
    t.start()
    sent, pending = fifo.deliver(path, ["tap:1:2", "shot:" + shot], timeout=10)
    t.join()
    assert sent and pending == [] and got == ["tap:1:2", "shot:" + shot]
    # nobody reads: not sent
    assert fifo.deliver(path, ["tap:1:2"], timeout=0.5) == (False, [])


def test_tcp_channel_delivers_with_client_paths(tmp_path):
    """--control tcp:HOST:PORT (a Windows client from WSL): one connection per batch; a shot is sent
    in the client's spelling (fifo.CLIENT_PATH) and waited for at the local path."""
    import socket
    from soadrive import winhost
    ls = socket.socket()
    ls.bind(("127.0.0.1", 0))
    ls.listen(4)
    addr = "tcp:127.0.0.1:%d" % ls.getsockname()[1]
    shot = str(tmp_path / "s.png")
    got = []

    def server():
        while True:
            c, _ = ls.accept()
            data = b""
            while True:
                b = c.recv(1024)
                if not b:
                    break
                data += b
            c.close()
            lines = [x for x in data.decode().split("\n") if x]
            got.extend(lines)
            if any(x.startswith("shot:") for x in lines):
                open(shot, "wb").write(b"png")
                return

    t = threading.Thread(target=server)
    t.start()
    fifo.CLIENT_PATH[addr] = lambda p: "WIN:" + p
    try:
        assert fifo.listening(addr)
        sent, pending = fifo.deliver(addr, ["tap:1:2", "shot:" + shot], timeout=10)
    finally:
        del fifo.CLIENT_PATH[addr]
    t.join()
    ls.close()
    assert sent and pending == [] and got == ["tap:1:2", "shot:WIN:" + shot]
    # nobody listens: not sent
    assert not fifo.listening(addr)
    assert fifo.deliver(addr, ["tap:1:2"], timeout=0.5) == (False, [])
    assert winhost.winpath("/mnt/c/soa-win/run/x") == "C:\\soa-win\\run\\x"
    assert winhost.is_windows("build-win/port/soa.exe") and not winhost.is_windows("build/port/soa")


def test_ui370_points_are_window_coordinates():
    pts = {k: v for k, v in vars(ui370).items() if k.isupper() and isinstance(v, str)}
    assert len(pts) > 20
    for k, v in pts.items():
        assert re.fullmatch(r"\d{1,3}:\d{1,4}", v), k
        x, y = map(int, v.split(":"))
        assert 0 <= x < 729 and 0 <= y < 1296, k


def test_gdb_needs_a_run_started_with_it(tmp_path):
    import pytest
    from soadrive import gdb, targets
    r = targets.Run("port-inproc", targets.Layout.port_session(str(tmp_path / "out"), str(tmp_path / "tmp")), targets.Config())
    with pytest.raises(gdb.GdbUnavailable):
        r.gdb()
    assert gdb.client_args(1234) == ["--gdb", "127.0.0.1:1234"]
    assert gdb.client_args(0, "::1") == ["--gdb", "[::1]:0"]
    log = tmp_path / "client.log"
    assert gdb.listen_port(str(log)) is None
    log.write_text("I/x: y\nI/gdb: GDB stub listening on [::1]:40123 (gdb-multiarch -x control/gdbinit-soa, or ...)\n")
    assert gdb.listen_port(str(log)) == 40123


def test_every_session_module_declares_its_interface():
    import importlib
    import pkgutil
    from soadrive import sessions, targets
    names = [m.name for m in pkgutil.iter_modules(sessions.__path__) if not m.name.startswith("_") and m.name != "common"]
    assert names
    for n in names:
        m = importlib.import_module("soadrive.sessions." + n)
        assert m.TARGETS and set(m.TARGETS) <= set(targets.TARGETS), n
        assert callable(m.options) and callable(m.main), n
        assert os.path.exists(os.path.join(proc.REPO, m.WRAPPER.split()[0])), n


def _fake_run(tmp_path, script):
    """A Run whose client is a shell script standing in for the game (no FIFO reader)."""
    from soadrive import targets
    r = targets.Run("port-inproc", targets.Layout.port_session(str(tmp_path / "out"), str(tmp_path / "tmp")), targets.Config())
    r.layout.prepare()
    r.client = proc.Proc("fake-client", ["sh", "-c", script], r.client_log, limit=120)
    return r


def test_keep_shot_without_a_screenshot(tmp_path):
    # a dead client's look() is None: the shot is missing, not a driver error (session home, CR8)
    r = _fake_run(tmp_path, "exit 0")
    assert not os.path.exists(r.keep_shot("20-menu", None))
    r.stop()


def test_a_wait_fails_fast_when_the_client_exits(tmp_path):
    import pytest
    from soadrive import targets
    r = _fake_run(tmp_path, "echo booting; sleep 2; exit 3")
    t0 = time.monotonic()
    with pytest.raises(targets.Abort):
        r.wait_for("a milestone that never comes", 300, lambda: False)
    assert time.monotonic() - t0 < 10
    assert "exited (status" in r.results[-1] and r.failed
    r.stop()


def test_a_host_gpu_failure_is_named_and_ends_the_wait(tmp_path):
    import pytest
    from soadrive import targets
    # the process lingers after the driver dropped out (as a wedged client does)
    r = _fake_run(tmp_path, "echo 'D3D12: Removing Device.'; sleep 100")
    t0 = time.monotonic()
    with pytest.raises(targets.Abort):
        r.tap_log(r"never", 300, 20, 5, "tap:1:1", name="a tap that is never answered")
    assert time.monotonic() - t0 < 10
    assert "host GPU" in r.results[-1] and "rerun" in r.results[-1]
    t0 = time.monotonic()
    r.stop()  # a dead client gets no quit and no 15 s wait for it (25 s before)
    assert time.monotonic() - t0 < 5
    assert not r.client.running()


def test_stop_doesnt_wait_for_a_client_nobody_can_reach(tmp_path):
    r = _fake_run(tmp_path, "sleep 100")  # running, no death, but no reader on its FIFO
    t0 = time.monotonic()
    r.stop()
    assert time.monotonic() - t0 < r.QUIT_SEND_SECS + 3  # the quit's wait for a reader, not 10 + 15 s
    assert not r.client.running()


def _wait_for_fifo(path, secs=30):
    """The fake client made its FIFO (its reader then sits in open(), which a writer's
    non-blocking open counts: deliver gets through). No probe: an open-and-close is an EOF."""
    deadline = time.monotonic() + secs
    while not os.path.exists(path) and time.monotonic() < deadline:
        time.sleep(0.05)


def test_stop_quits_a_client_that_listens(tmp_path):
    """The positive control: a client reading its FIFO gets `quit` and exits by itself. Like the
    game it reads until EOF, then reopens (an empty batch counts for nothing)."""
    r = _fake_run(tmp_path, "")
    r.client.stop()
    r.client = proc.Proc("fake-client", ["sh", "-c", 'mkfifo "$0"; l=; while [ -z "$l" ]; do read l < "$0"; done; echo "got $l"', r.fifo],
                         r.client_log, limit=120)
    _wait_for_fifo(r.fifo)
    r.stop()
    assert "got quit" in open(r.client_log).read()
    assert r.client.p.returncode == 0  # it exited on its own, not by TERM


def test_stop_reaches_a_client_that_is_still_starting(tmp_path):
    """stop() right after the start, before the client opened its FIFO: the quit waits for the
    reader (deliver retries ENXIO) instead of a probe deciding nobody listens."""
    r = _fake_run(tmp_path, "")
    r.client.stop()
    r.client = proc.Proc("fake-client", ["sh", "-c", 'sleep 1; mkfifo "$0"; l=; while [ -z "$l" ]; do read l < "$0"; done; '
                                         'echo "got $l"', r.fifo], r.client_log, limit=120)
    r.stop()
    assert "got quit" in open(r.client_log).read()


def test_quit_after_an_eof_isnt_lost(tmp_path):
    """The flake (2026-10-07, a T0 at load 13): a batch written right after another writer's close
    (an EOF to the reader, which then closes and reopens) could be dropped. 20 empty batches back to
    back, then stop(): the quit still arrives."""
    r = _fake_run(tmp_path, "")
    r.client.stop()
    r.client = proc.Proc("fake-client", ["sh", "-c", 'mkfifo "$0"; l=; while [ -z "$l" ]; do read l < "$0"; done; echo "got $l"', r.fifo],
                         r.client_log, limit=120)
    _wait_for_fifo(r.fifo)
    for _ in range(20):  # empty batches, as a driver's other channel users might send
        fifo.deliver(r.fifo, [], timeout=5)
    r.stop()
    assert "got quit" in open(r.client_log).read()


def _stop_a_driver(tmp_path, busy):
    """A driver (proc.exit_on_signals) with a client in its own process group gets TERM while its
    main thread runs `busy`: it exits 143 and the client is gone."""
    script = ("import sys, threading, time; sys.path.insert(0, %r)\n"
              "from soadrive import proc\n"
              "proc.exit_on_signals()\n"
              "p = proc.Proc('fake-client', ['sleep', '100'], %r, limit=120)\n"
              "print(p.pid, flush=True)\n"
              "%s\n") % (CONTROL, str(tmp_path / "client.log"), busy)
    d = subprocess.Popen([sys.executable, "-c", script], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    pid = int(d.stdout.readline())
    # drain the driver's output so a busy printer never blocks on a full pipe
    threading.Thread(target=d.stdout.read, daemon=True).start()
    time.sleep(0.3)
    os.kill(d.pid, 15)
    try:
        rc = d.wait(10)
    except subprocess.TimeoutExpired:
        d.kill()
        raise
    err = d.stderr.read()
    assert rc == 143, (rc, err[-2000:])
    assert "stopped by signal 15" in err
    deadline = time.monotonic() + 5
    while time.monotonic() < deadline:
        try:
            os.killpg(pid, 0)
        except ProcessLookupError:
            return
        time.sleep(0.1)
    os.killpg(pid, 9)
    raise AssertionError("the client outlived its driver")


def test_a_stopped_driver_ends_its_clients(tmp_path):
    """proc.exit_on_signals (tests/diff/difftest.py): the clients run in their own process groups,
    each holding its game slot; a TERM to the driver ends them too."""
    _stop_a_driver(tmp_path, "time.sleep(100)")


def test_a_driver_stopped_while_printing_still_exits(tmp_path):
    """The regression: the TERM arrives while the main thread is inside print() (a driver logging
    its steps); a handler that printed raised "reentrant call" and the driver exited 1 instead."""
    _stop_a_driver(tmp_path, "while True: print('step ' * 50, flush=True)")


def test_a_driver_stopped_while_starting_clients_still_exits(tmp_path):
    """... or while the main thread holds proc.LIVE_LOCK (starting and stopping clients in a loop):
    the handler takes no lock, so it can't deadlock."""
    _stop_a_driver(tmp_path, "while True:\n    q = proc.Proc('c', ['true'], %r, limit=10); q.stop()" % str(tmp_path / "c.log"))


def test_the_gate_labels_host_gpu_failures(tmp_path):
    sys.path.insert(0, os.path.join(proc.REPO, "tools"))
    import gate
    log = tmp_path / "t.log"
    log.write_text("FAIL: a step (the client is gone: host GPU (D3D12: Removing Device); a host problem, not the game's: rerun)\n")
    assert gate.host_gpu({"log": str(log)})
    log.write_text("FAIL: a step (not within 60s)\n")
    assert not gate.host_gpu({"log": str(log)})


def test_gacha_result_probe(tmp_path):
    from soadrive import popups
    plain = str(tmp_path / "plain.png")
    subprocess.run(["convert", "-size", "729x1296", "xc:#3060a0", plain], check=True)
    assert not popups.is_gacha_result(plain)


def test_gacha_confirm_retries(tmp_path, monkeypatch):
    """popups.gacha_confirm (flows/gacha.open_confirm, flowctl.py gacha-confirm): 10連ガチャ again on the
    banner detail, 閉じる on anything else (a pick-up's character detail), True once the confirmation
    shows; False after its tries."""
    from soadrive import popups, ui370
    probe = str(tmp_path / "probe.png")
    screens = iter(["detail", "other", "confirm"])
    cur = {}
    sent = []

    def send(cmds):
        sent.append(cmds)
        if cmds[0].startswith("shot:"):
            cur["s"] = next(screens)
            open(probe, "w").close()

    monkeypatch.setattr(popups, "is_gacha_confirm", lambda p: cur.get("s") == "confirm")
    monkeypatch.setattr(popups, "is_gacha_detail", lambda p: cur.get("s") == "detail")
    assert popups.gacha_confirm(send, probe, note=lambda s: None)
    taps = [c[0] for c in sent if c[0].startswith("tap:")]
    assert taps == ["tap:" + ui370.GACHA_10, "tap:" + ui370.CHARACTER_DETAIL_CLOSE]
    screens = iter(["detail"] * 3)
    assert not popups.gacha_confirm(send, probe, note=lambda s: None, tries=3)


def _state_db(path, orphan):
    """A state DB at this build's schema version with one declared foreign key (and an orphan row)."""
    import sqlite3
    sys.path.insert(0, os.path.join(proc.REPO, "tools"))
    import schema_inventory
    con = sqlite3.connect(str(path))
    con.executescript("create table p (id integer primary key); create table c (pid integer references p(id));"
                      "insert into p values (1); insert into c values (1);" + ("insert into c values (2);" if orphan else ""))
    con.execute("pragma user_version = %d" % schema_inventory.schema_version())
    con.commit()
    con.close()


def test_the_end_state_is_checked_when_a_run_stops(tmp_path):
    """G9 (docs/history/PLAN-schema.md S11): Run.stop checks the server's end state; an orphan row is a
    failed step and is recorded for control/run.py, a clean state a passed one."""
    from soadrive import targets

    class Stopped:  # a server that already ran
        def stop(self):
            pass

        def running(self):
            return False

    for orphan in (False, True):
        sub = tmp_path / ("orphan" if orphan else "clean")
        r = targets.Run("port-inproc", targets.Layout.port_session(str(sub / "out"), str(sub / "tmp")), targets.Config())
        r.layout.prepare()
        os.makedirs(os.path.dirname(r.state_db), exist_ok=True)
        _state_db(r.state_db, orphan)
        r.server = Stopped()
        n = len(targets.Run.STATE_CHECKS)
        r.stop()
        assert len(targets.Run.STATE_CHECKS) == n + 1
        assert targets.Run.STATE_CHECKS[-1][1] == (not orphan)
        assert r.failed == orphan, r.results
        assert any(x.startswith("FAIL") and "state check (G9): 1 foreign key violation" in x for x in r.results) == orphan, r.results
        steps = open(r.layout.steps).read()
        assert ("state check" in steps) and steps.rstrip().endswith("FAIL" if orphan else "PASS")


def test_winhost_copy_verified(tmp_path, monkeypatch):
    """winhost.copy_verified: a copy that isn't the source (same size, other bytes: what a copy onto
    the Windows drive under memory pressure has left) is copied again once, then fails loudly."""
    import shutil
    import pytest
    from soadrive import winhost
    src, dst = tmp_path / "a.exe", tmp_path / "b.exe"
    src.write_bytes(b"MZ" + b"x" * 100)
    real = shutil.copy2
    bad = {"n": 0}

    def flaky(a, b):
        real(a, b)
        if bad["n"] > 0:
            bad["n"] -= 1
            with open(b, "r+b") as f:
                f.seek(50)
                f.write(b"y")
    monkeypatch.setattr(winhost.shutil, "copy2", flaky)
    winhost.copy_verified(str(src), str(dst))  # a good copy
    assert dst.read_bytes() == src.read_bytes()
    bad["n"] = 1  # one bad copy: retried
    winhost.copy_verified(str(src), str(dst))
    assert dst.read_bytes() == src.read_bytes() and bad["n"] == 0
    bad["n"] = 2  # two: an error
    with pytest.raises(winhost.CopyMismatch):
        winhost.copy_verified(str(src), str(dst))
