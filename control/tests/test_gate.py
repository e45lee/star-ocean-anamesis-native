"""tools/gate.py's verdicts and interrupts, without a game (pytest): the tests/diff verdict comes from
this run (exit code and a fresh summary.txt), and an interrupt starts nothing more and frees the slots."""
import os
import signal
import sys
import threading
import time

import pytest

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, "tools"))
sys.path.insert(0, os.path.join(REPO, "control"))
import gate  # noqa: E402
import soaslot  # noqa: E402

SHARD = {"name": "shard:login", "tier": "T1", "secs": 100, "kind": "shard", "game": 3, "cmd": "tests/diff/run.sh login --out {out}"}


@pytest.fixture(autouse=True)
def fresh_gate():
    def clear():
        getattr(gate, "CANCEL", threading.Event()).clear()
        del gate.PROCS[:]
    clear()
    yield
    clear()


def fake_driver(monkeypatch, rc, summary=None):
    """run_cmd standing in for tests/diff/run.sh: writes `summary` (if any) as this run's summary.txt
    and exits rc."""
    def run_cmd(cmd, out, tmp, limit, log, slot=-1):
        os.makedirs(out, exist_ok=True)
        open(log, "w").write("$ %s\n" % cmd)
        if summary is not None:
            open(os.path.join(out, "summary.txt"), "w").write(summary)
        return rc
    monkeypatch.setattr(gate, "run_cmd", run_cmd)


def stale_pass(tmp_path):
    """A summary.txt an earlier run with the same --out left behind."""
    os.makedirs(tmp_path / "tests-diff", exist_ok=True)
    (tmp_path / "tests-diff" / "summary.txt").write_text("PASS login            90s  emu 80s\n")


def test_a_stale_summary_doesnt_pass_a_crashed_run(tmp_path, monkeypatch):
    stale_pass(tmp_path)
    fake_driver(monkeypatch, 1)  # died (an import error, say) before writing its summary
    assert not gate.run_diff([SHARD], str(tmp_path), False)[0]["ok"]
    fake_driver(monkeypatch, 124)  # killed at its time limit
    stale_pass(tmp_path)
    assert not gate.run_diff([SHARD], str(tmp_path), False)[0]["ok"]
    fake_driver(monkeypatch, 0)  # exit 0 but no summary of its own
    stale_pass(tmp_path)
    assert not gate.run_diff([SHARD], str(tmp_path), False)[0]["ok"]


def test_the_exit_code_counts_besides_the_summary(tmp_path, monkeypatch):
    fake_driver(monkeypatch, 2, "PASS login            90s  emu 80s\n")  # a PASS line, then a crash
    assert not gate.run_diff([SHARD], str(tmp_path), False)[0]["ok"]
    fake_driver(monkeypatch, 1, "PASS login            90s  emu 80s\n")  # exit 1 with every flow PASS: contradictory
    assert not gate.run_diff([SHARD], str(tmp_path), False)[0]["ok"]
    fake_driver(monkeypatch, 0, "PASS login            90s  emu 80s\n")  # the positive control
    r = gate.run_diff([SHARD], str(tmp_path), False)[0]
    assert r["ok"] and r["secs"] == 90


def test_one_failing_flow_fails_only_its_test(tmp_path, monkeypatch):
    battle = dict(SHARD, name="shard:battle", cmd="tests/diff/run.sh battle --out {out}")
    fake_driver(monkeypatch, 1, "PASS login            90s\nFAIL battle           200s\n")
    rs = {r["name"]: r["ok"] for r in gate.run_diff([SHARD, battle], str(tmp_path), False)}
    assert rs == {"shard:login": True, "shard:battle": False}


def test_only_plain_tests_diff_runs_are_grouped():
    assert gate.is_diff(SHARD) and gate.is_diff(dict(SHARD, cmd="tests/diff/run.sh --out {out}"))
    assert not gate.is_diff(dict(SHARD, cmd="tests/diff/run.sh login --inject 'port-inproc:--start-coins 1000' --out {out}"))
    assert not gate.is_diff(dict(SHARD, cmd="tests/diff/run.sh login --expect-fail --out {out}"))


def test_acquire_stops_waiting_when_cancelled(tmp_path, monkeypatch):
    for k, v in dict(SOA_SLOT_DIR=str(tmp_path), SOA_SLOTS="1", SOA_SLOT_MIN_FREE_GB="0", SOA_SLOT_STAGGER="0").items():
        monkeypatch.setenv(k, v)
    monkeypatch.delenv("SOA_SLOT_HELD", raising=False)
    held = soaslot.acquire("holder")
    try:
        stop = threading.Event()
        threading.Timer(0.5, stop.set).start()
        t0 = time.monotonic()
        assert soaslot.acquire("waiter", quiet=True, cancel=stop.is_set) is None
        assert time.monotonic() - t0 < 2
    finally:
        soaslot.release(held)


def test_an_interrupt_starts_no_queued_test_and_frees_the_slots(tmp_path, monkeypatch):
    """Two game tests, one slot: one runs, the other queues. Ctrl-C ends the one running, and the
    queued one never starts (it doesn't take the freed slot after the gate was stopped)."""
    for k, v in dict(SOA_SLOT_DIR=str(tmp_path / "slots"), SOA_SLOTS="1", SOA_SLOT_MIN_FREE_GB="0",
                     SOA_SLOT_STAGGER="0").items():
        monkeypatch.setenv(k, v)
    monkeypatch.delenv("SOA_SLOT_HELD", raising=False)
    tests = [{"name": "fake:%s" % n, "tier": "T1", "secs": 1, "kind": "session", "game": 1, "cmd": "sleep 30", "covers": ""}
             for n in ("first", "second")]
    monkeypatch.setattr(gate.tests_for, "load_tiers", lambda: tests)
    out = tmp_path / "out"
    monkeypatch.setattr(sys, "argv", ["gate.py", "fake:first", "fake:second", "--out", str(out)])
    old = signal.getsignal(signal.SIGINT), signal.getsignal(signal.SIGTERM)
    timer = threading.Timer(1.5, os.kill, (os.getpid(), signal.SIGINT))
    t0 = time.monotonic()
    try:
        timer.start()
        with pytest.raises(SystemExit) as e:
            gate.main()
    finally:
        timer.cancel()
        signal.signal(signal.SIGINT, old[0])
        signal.signal(signal.SIGTERM, old[1])
    assert e.value.code == 130
    assert time.monotonic() - t0 < 8  # neither the 30 s test nor the queued one ran on
    # whichever took the slot ran; the other never started (run_cmd writes the log when a test starts)
    assert [(out / ("fake-%s.log" % n)).exists() for n in ("first", "second")].count(True) == 1
    got = soaslot.try_acquire("probe")  # the slot is free again
    assert got is not None
    soaslot.release(got[0])
    assert all(p.poll() is not None for p in gate.PROCS)


def test_a_lone_tests_diff_run_gets_the_long_limit(tmp_path, monkeypatch):
    """The negative control queues its clients for slots inside: its limit mustn't count the wait
    (it was killed at 600 s after waiting 556 s for a slot)."""
    limits = {}

    def run_cmd(cmd, out, tmp, limit, log, slot=-1):
        limits[cmd] = limit
        return 0
    monkeypatch.setattr(gate, "run_cmd", run_cmd)
    neg = dict(SHARD, name="diff-negative", game=0, secs=150,
               cmd="tests/diff/run.sh login --inject 'port-inproc:--start-coins 299000' --expect-fail --out {out}")
    other = dict(neg, name="check", cmd="true")
    gate.run_test(neg, str(tmp_path), False)
    gate.run_test(other, str(tmp_path), False)
    assert limits[neg["cmd"]] >= 3600 and limits["true"] == 600
