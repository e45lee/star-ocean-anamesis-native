"""flows/mission.py's start_mission without a game (pytest): a fake client whose screen is a recorded
screenshot (control/tests/fixtures/mission-start: passing sessions' frames with everything but the
signature regions blacked out) and whose taps move between them as the game's do. A lost tap
(SOA_TEST_DROP_TAP, or a screen that ignores it) must be retried on the screen it is for, and
決定 must never be tapped on the party screen."""
import os
import shutil

import pytest

from soadrive import popups, ui370
from soadrive.flows import mission
from soadrive.targets import Abort

HERE = os.path.dirname(os.path.abspath(__file__))

FIX = os.path.join(HERE, "fixtures", "mission-start")


class FakeRun:
    """The parts of targets.Run the helper uses. screens: {screen: {tap xy: next screen}}; a tap
    the screen has no entry for changes nothing. lose: taps to ignore (xy -> how many)."""
    def __init__(self, tmp, screen, screens, lose=None, started_on="battle"):
        self.dir, self.screen, self.screens, self.lose = str(tmp), screen, screens, dict(lose or {})
        self.started_on, self.taps, self.results = started_on, [], []

    def scratch(self, name):
        return os.path.join(self.dir, name)

    def send(self, cmds, timeout=None):
        for c in cmds:
            if c.startswith("tap:"):
                xy = c[4:]
                self.taps.append((self.screen, xy))
                if self.lose.get(xy):
                    self.lose[xy] -= 1
                    continue
                self.screen = self.screens.get(self.screen, {}).get(xy, self.screen)
            elif c.startswith("shot:"):
                shutil.copyfile(os.path.join(FIX, self.screen + ".png"), c[5:])
        return True

    def ctl(self, *cmds):
        return self.send(list(cmds))

    def alive(self):
        return True

    def gone(self):
        return "gone"

    def poll(self, secs, pred):
        return pred()

    def started(self):
        return self.screen == self.started_on

    def ok(self, name):
        self.results.append("PASS " + name)

    def miss(self, name):
        self.results.append("FAIL " + name)

    def note(self, s):
        self.results.append("note " + s)

    def fail(self, name):
        self.miss(name)
        raise Abort(name)


MISSION_SCREENS = {"party": {ui370.PARTY_START: "confirm"}, "confirm": {ui370.CONFIRM_OK: "battle"}}


@pytest.fixture(autouse=True)
def no_drop(monkeypatch):
    monkeypatch.delenv("SOA_TEST_DROP_TAP", raising=False)


def test_the_signatures_tell_the_screens_apart():
    want = {"party": "is_party_start", "confirm": "is_mission_confirm", "sphere211-party": "is_sphere211_party",
            "deepspace-party": "is_deepspace_party", "deepspace-confirm": "is_deepspace_confirm", "battle": None}
    names = set(v for v in want.values() if v) | {"is_gacha_confirm", "is_gacha_detail"}
    for shot, match in want.items():
        got = [n for n in sorted(names) if getattr(popups, n)(os.path.join(FIX, shot + ".png"))]
        assert got == ([match] if match else []), shot


def test_start_without_a_lost_tap(tmp_path):
    s = FakeRun(tmp_path, "party", MISSION_SCREENS)
    assert mission.start_mission(s, "start", s.started)
    assert s.taps == [("party", ui370.PARTY_START), ("confirm", ui370.CONFIRM_OK)]
    assert s.results == ["PASS start"]


def test_a_lost_mission_start_tap_is_retried_and_decide_waits_for_the_dialog(tmp_path, monkeypatch):
    # session:tower 2026-10-06: ミッション開始 lost, the party screen stayed
    monkeypatch.setenv("SOA_TEST_DROP_TAP", "mission-start")
    s = FakeRun(tmp_path, "party", MISSION_SCREENS)
    assert mission.start_mission(s, "start", s.started)
    assert s.taps == [("party", ui370.PARTY_START), ("confirm", ui370.CONFIRM_OK)]  # the first never sent
    assert any("SOA_TEST_DROP_TAP" in r for r in s.results)
    assert any("isn't up: tapping %s again" % ui370.PARTY_START in r for r in s.results)
    assert ("party", ui370.CONFIRM_OK) not in s.taps


def test_taps_the_game_drops_are_retried(tmp_path):
    s = FakeRun(tmp_path, "party", MISSION_SCREENS, lose={ui370.PARTY_START: 2, ui370.CONFIRM_OK: 1})
    assert mission.start_mission(s, "start", s.started)
    assert [xy for _, xy in s.taps] == [ui370.PARTY_START] * 3 + [ui370.CONFIRM_OK] * 2
    assert ("party", ui370.CONFIRM_OK) not in s.taps
    assert s.results[-1] == "PASS start"


def test_a_dialog_that_never_opens_fails_without_tapping_decide(tmp_path):
    s = FakeRun(tmp_path, "party", MISSION_SCREENS, lose={ui370.PARTY_START: 99})
    with pytest.raises(Abort):
        mission.start_mission(s, "start", s.started)
    assert all(xy == ui370.PARTY_START for _, xy in s.taps)
    assert s.results[-1].startswith("FAIL the start confirmation didn't open")


def test_a_closed_confirmation_is_opened_again(tmp_path):
    # 決定 lost and the dialog gone (閉じる'd): back on the party screen, ミッション開始 again
    screens = {"party": {ui370.PARTY_START: "confirm"}, "confirm": {ui370.CONFIRM_OK: "party"}}
    s = FakeRun(tmp_path, "party", screens)
    calls = {"n": 0}

    def started():
        return s.screen == "battle"

    orig = s.send

    def send(cmds, timeout=None):  # the second 決定 starts the battle
        for c in cmds:
            if c == "tap:" + ui370.CONFIRM_OK:
                calls["n"] += 1
                if calls["n"] == 2:
                    s.screens["confirm"][ui370.CONFIRM_OK] = "battle"
        return orig(cmds, timeout)
    s.send = send
    assert mission.start_mission(s, "start", started)
    assert any("back on the party screen" in r for r in s.results)
    assert [xy for _, xy in s.taps] == [ui370.PARTY_START, ui370.CONFIRM_OK, ui370.PARTY_START, ui370.CONFIRM_OK]


def test_sphere211_and_deep_space_use_their_own_buttons(tmp_path, monkeypatch):
    monkeypatch.setenv("SOA_TEST_DROP_TAP", "mission-start,deepspace-start")
    s = FakeRun(tmp_path, "sphere211-party", {"sphere211-party": {ui370.SPHERE211_START: "confirm"},
                                              "confirm": {ui370.CONFIRM_OK: "battle"}})
    assert mission.start_mission(s, "start", s.started, d=mission.SPHERE211)
    assert s.taps == [("sphere211-party", ui370.SPHERE211_START), ("confirm", ui370.CONFIRM_OK)]
    s = FakeRun(tmp_path, "deepspace-party", {"deepspace-party": {ui370.DEEPSPACE_DECIDE: "deepspace-confirm"},
                                              "deepspace-confirm": {ui370.DEEPSPACE_START: "battle"}})
    assert mission.start_mission(s, "start", s.started, d=mission.DEEPSPACE)
    assert s.taps == [("deepspace-party", ui370.DEEPSPACE_DECIDE), ("deepspace-confirm", ui370.DEEPSPACE_START)]
