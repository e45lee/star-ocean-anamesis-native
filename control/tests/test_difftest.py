"""tests/diff's verdicts without a game (pytest): a target without a run, or a comparison without the
reference run, FAILs instead of comparing nothing; --expect-fail (the negative control) passes only
on a comparison FAIL with every run passing."""
import types

import compare
import difftest


FLOW = types.SimpleNamespace(NAME="fake", SCREENS={})


def fake_run(target, failed=False):
    return types.SimpleNamespace(target=target, failed=failed, elapsed_total=1, dir="/nonexistent", results=[])


def test_a_missing_reference_fails(tmp_path):
    path = str(tmp_path / "report.txt")
    runs = {"port-inproc": fake_run("port-inproc")}
    assert not compare.report(FLOW, runs, "emu", path, expected=["emu", "port-inproc"])
    assert "no run" in open(path).read()
    assert not compare.report(FLOW, {}, "emu", path, expected=["emu", "port-inproc"])
    # the positive control: only the reference was asked for and it ran (nothing to compare)
    assert compare.report(FLOW, {"emu": fake_run("emu")}, "emu", path, expected=["emu"])


def test_a_target_whose_run_couldnt_be_made_fails(tmp_path, monkeypatch):
    """difftest.run_target used to raise in its thread when Run(...) failed, and the flow was
    compared without that target."""
    made = []

    class Run:
        def __init__(self, target, rdir, cfg, keep=False):
            if target == "port-inproc":
                raise RuntimeError("no such binary")
            self.target, self.failed, self.elapsed_total, self.dir, self.results = target, False, 1, rdir, []
            made.append(target)

        def start(self):
            pass

        def stop(self):
            pass

    flow = types.SimpleNamespace(NAME="fake", SCREENS={}, config=lambda cfg: types.SimpleNamespace(server_args=[]),
                                 run=lambda r: None)
    monkeypatch.setitem(difftest.FLOWS, "fake", flow)
    monkeypatch.setattr(difftest.targets, "Run", Run)
    results = {}
    import threading
    opts = types.SimpleNamespace(keep=False, sequential=True)
    difftest.run_flow("fake", ["emu", "port-inproc"], opts, {}, str(tmp_path), results, threading.Lock())
    ok, line, text, runs_ok = results["fake"]
    assert made == ["emu"]
    assert not ok and line.startswith("FAIL") and not runs_ok
    assert "port-inproc: FAIL: no run" in text
    # --expect-fail doesn't count a broken run as the comparison's FAIL
    assert difftest.expect_fail(["fake"], results) == 1


def test_expect_fail():
    assert difftest.expect_fail(["a"], {"a": (False, "FAIL a", "", True)}) == 0  # the comparison saw the difference
    assert difftest.expect_fail(["a"], {"a": (True, "PASS a", "", True)}) == 1  # it didn't
    assert difftest.expect_fail(["a"], {"a": (False, "FAIL a", "", False)}) == 1  # a run broke instead
    assert difftest.expect_fail(["a"], {}) == 1
