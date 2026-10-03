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
    r.stop()
    assert not r.client.running()


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
