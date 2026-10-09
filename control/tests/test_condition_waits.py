"""soadrive/waits.py, the condition waits (docs/code-review-2026-10-06.md T3) without a game (pytest): a
fake client whose screen is one of a few generated images and whose taps move between them. A lost
tap is made again, a screen still fading in is waited out, an animated region is masked, and a
step that doesn't arrive fails with what was expected and the last phase seen."""
import os
import shutil
import subprocess

import pytest

from soadrive import screens
from soadrive import waits as common
from soadrive.targets import Abort

pytestmark = pytest.mark.skipif(shutil.which("convert") is None or shutil.which("compare") is None,
                                reason="ImageMagick (convert, compare) not installed")


@pytest.fixture(scope="module")
def images(tmp_path_factory):
    """Screens at 182x324 (what screens.rmse compares): two distinct screens (a grey with a bar at
    the top or the bottom), a flat black transition frame, and a screen whose middle (the home
    character's region) alternates."""
    d = tmp_path_factory.mktemp("screens")

    def make(name, *draw):
        path = str(d / (name + ".png"))
        subprocess.run(["convert", "-size", "729x1296", "xc:gray50", "-fill", "white"] +
                       [a for r in draw for a in ("-draw", "rectangle %d,%d %d,%d" % r)] + [path], check=True)
        return path

    black = str(d / "black.png")
    subprocess.run(["convert", "-size", "729x1296", "xc:black", black], check=True)
    return {
        "a": make("a", (0, 0, 728, 200)),
        "b": make("b", (0, 1000, 728, 1295)),
        "black": black,
        "anim0": make("anim0", (0, 0, 728, 200), (200, 300, 500, 600)),
        "anim1": make("anim1", (0, 0, 728, 200), (200, 600, 500, 900)),
        "pulse": make("pulse", (0, 0, 728, 200), (300, 600, 380, 680)),  # "a" with a small square: a pulse
    }


class FakeRun:
    """The parts of targets.Run the helpers use. screen: the current screen's name, or a list of
    names shown one per screenshot (a fade, an animation; the last repeats, unless cycle); taps:
    {(screen, xy): next screen}; lose: taps to ignore (xy -> how many)."""

    def __init__(self, tmp, images, screen, taps, lose=None, cycle=False, log=None):
        self.dir, self.images, self.taps, self.lose, self.cycle = str(tmp), images, taps, dict(lose or {}), cycle
        self.set(screen)
        self.sent, self.results = [], []
        self.client_log = str(tmp / "log.txt")
        with open(self.client_log, "w") as f:
            f.write(log or "")
        from soadrive import milestones
        self.cursor = milestones.LogCursor(self.client_log, persist=False)

    def set(self, screen):
        self.frames = list(screen) if isinstance(screen, list) else [screen]
        self.i = 0

    def current(self):
        if self.cycle:
            return self.frames[self.i % len(self.frames)]
        return self.frames[min(self.i, len(self.frames) - 1)]

    def scratch(self, name):
        return os.path.join(self.dir, name)

    def send(self, cmds, timeout=None):
        for c in cmds:
            self.sent.append(c)
            if c.startswith("tap:"):
                xy = c[4:]
                if self.lose.get(xy):
                    self.lose[xy] -= 1
                    continue
                nxt = self.taps.get((self.current(), xy))
                if nxt is not None:
                    self.set(nxt)
            elif c.startswith("shot:"):
                shutil.copyfile(self.images[self.current()], c[5:])
                self.i += 1
        return True

    def ctl(self, *cmds):
        return self.send(list(cmds))

    def keep_shot(self, name, src):
        shutil.copyfile(src, self.scratch(name + ".png"))

    def last_line(self, rx, path=None):
        from soadrive import milestones
        return milestones.last(path or self.client_log, rx)

    def alive(self):
        return True

    def gone(self):
        return "gone"

    def ok(self, name):
        self.results.append("PASS " + name)

    def miss(self, name):
        self.results.append("FAIL " + name)

    def note(self, s):
        self.results.append("note " + s)


@pytest.fixture(autouse=True)
def fast(monkeypatch):
    # the waits between screenshots are the fake's: no real time passes between looks
    monkeypatch.setattr(screens.Watch, "__init__", _fast_init(screens.Watch.__init__))


def _fast_init(init):
    def f(self, send, path, mask=(), limit=0.01, interval_ms=600, hold=1):
        init(self, send, path, mask, limit, 0, hold)
    return f


def test_settle_waits_out_a_fade(tmp_path, images):
    s = FakeRun(tmp_path, images, ["black", "black", "a", "a"], {})
    assert common.settle(s, "shot", secs=10) is not None
    assert screens.rmse(s.scratch("shot.png"), images["a"]) < 0.01


def test_settle_ignores_an_earlier_watch(tmp_path, images):
    # a second settle on the same run starts afresh: the first one's last frame isn't its "previous"
    s = FakeRun(tmp_path, images, "a", {})
    assert common.settle(s, secs=5) is not None
    s.set(["a", "b"])  # the screen changes after the first look (a tap's effect showing late)
    assert common.settle(s, "again", secs=5) is not None
    assert screens.rmse(s.scratch("again.png"), images["b"]) < 0.01


def test_settle_masks_an_animation(tmp_path, images):
    mask = ((150, 250, 600, 1000),)
    s = FakeRun(tmp_path, images, ["anim0", "anim1"], {}, cycle=True)
    assert common.settle(s, secs=3, mask=mask) is not None
    s = FakeRun(tmp_path, images, ["anim0", "anim1"], {}, cycle=True)
    assert common.settle(s, "moving", secs=2) is None  # unmasked: never still; noted, the shot kept
    assert any(r.startswith("note moving") for r in s.results)
    assert os.path.exists(s.scratch("moving.png"))


def test_settle_takes_a_calm_screen(tmp_path, images):
    # a screen that moves only a little (a selected card's pulse) settles after screens.CALM_SECS
    assert 0.01 < screens.rmse(images["a"], images["pulse"], (), screens.WATCH_SIZE) < screens.CALM_LIMIT
    s = FakeRun(tmp_path, images, ["a", "pulse"], {}, cycle=True)
    s.send = _slow(s.send)
    assert common.settle(s, secs=10) is not None


def _slow(send):
    import time

    def f(cmds, timeout=None):
        time.sleep(0.2)
        return send(cmds, timeout)
    return f


def test_tap_settled_never_retaps(tmp_path, images):
    s = FakeRun(tmp_path, images, "a", {}, lose={"1:1": 1})
    common.tap_settled(s, "1:1", secs=5)
    assert s.sent.count("tap:1:1") == 1


def test_tap_to_server(tmp_path, images):
    s = FakeRun(tmp_path, images, "a", {("a", "1:1"): "b"}, lose={"1:1": 1})
    s.server_log = s.client_log
    s.poll = lambda secs, pred: pred()
    orig = s.send

    def send(cmds, timeout=None):  # the server logs the request once the tap is taken
        lost = s.lose.get("1:1")
        r = orig(cmds, timeout)
        if "tap:1:1" in cmds and not lost:
            with open(s.server_log, "a") as f:
                f.write("I/server: Thing done\n")
        return r

    s.send = send
    assert common.tap_to_server(s, "thing", r"Thing done", ["tap:1:1"], "after")
    assert s.sent.count("tap:1:1") == 2 and "PASS thing" in s.results
    assert screens.rmse(s.scratch("after.png"), images["b"]) < 0.01


def test_tap_to_screen_retries_a_lost_tap(tmp_path, images):
    s = FakeRun(tmp_path, images, "a", {("a", "1:1"): "b"}, lose={"1:1": 1})
    assert common.tap_to_screen(s, "a -> b", "1:1", "b-shot", secs=20, retap_after=0) is not None
    assert s.sent.count("tap:1:1") == 2
    assert "PASS a -> b" in s.results
    assert screens.rmse(s.scratch("b-shot.png"), images["b"]) < 0.01


def test_tap_to_screen_fails_with_what_it_expected(tmp_path, images):
    s = FakeRun(tmp_path, images, "a", {}, log="I/port_debug: phase 4 (0x4)\n")
    with pytest.raises(Abort):
        common.tap_to_screen(s, "a -> b", "1:1", secs=2, tries=2, retap_after=0)
    assert s.sent.count("tap:1:1") == 2
    fail = [r for r in s.results if r.startswith("FAIL")]
    assert fail and "expected a screen other than the one tapped" in fail[0] and "last seen: phase 4" in fail[0]


def test_tap_to_screen_waits_for_its_fingerprint(tmp_path, images):
    # a tap that leads through another screen to the one wanted: no retap while it moves on
    s = FakeRun(tmp_path, images, "a", {("a", "1:1"): ["black", "anim0", "anim0", "b"]})
    is_b = lambda p: screens.rmse(p, images["b"]) < 0.01
    assert common.tap_to_screen(s, "a -> b", "1:1", is_screen=is_b, secs=20, retap_after=6) is not None
    assert s.sent.count("tap:1:1") == 1


def test_tap_to_screen_retaps_on_another_settled_screen(tmp_path, images):
    # the tap came while the screen was changing (a list refreshing): it settles on a new screen
    # that isn't the one wanted, and the tap is made again there
    s = FakeRun(tmp_path, images, "a", {("a", "1:1"): "anim0", ("anim0", "1:1"): "b"})
    is_b = lambda p: screens.rmse(p, images["b"]) < 0.01
    assert common.tap_to_screen(s, "a -> b", "1:1", is_screen=is_b, secs=20, retap_after=0) is not None
    assert s.sent.count("tap:1:1") == 2


def test_scroll_to_end(tmp_path, images):
    # each drag moves the list one screen until its end (b): the drag that changes nothing ends it
    s = FakeRun(tmp_path, images, "a", {("a", "drag:1:2:3:4"): "pulse", ("pulse", "drag:1:2:3:4"): "b"})
    orig = s.send

    def send(cmds, timeout=None):  # drags are commands of their own here
        for c in cmds:
            if c.startswith("drag:"):
                nxt = s.taps.get((s.current(), c))
                if nxt:
                    s.set(nxt)
        return orig([c for c in cmds if not c.startswith("drag:")], timeout)

    s.send = send
    s.ctl = lambda *cmds: send(list(cmds))
    assert common.scroll_to_end(s, "drag:1:2:3:4", "end")
    assert screens.rmse(s.scratch("end.png"), images["b"]) < 0.01


def test_tap_to_log(tmp_path, images):
    s = FakeRun(tmp_path, images, "a", {("a", "1:1"): "b"})
    orig = s.send

    def send(cmds, timeout=None):  # the game logs its phase once the tap is taken
        r = orig(cmds, timeout)
        if any(c == "tap:1:1" for c in cmds):
            with open(s.client_log, "a") as f:
                f.write("I/port_debug: phase 5 (0x5)\n")
        return r

    s.send = send
    assert common.tap_to_phase(s, "a -> phase 5", "1:1", 5, "p5", secs=5) is not None
    assert "PASS a -> phase 5" in s.results
    assert screens.rmse(s.scratch("p5.png"), images["b"]) < 0.01


def test_tap_to_log_fails_with_the_last_phase(tmp_path, images):
    s = FakeRun(tmp_path, images, "a", {}, log="I/port_debug: phase 11 (0xb)\n")
    assert common.tap_to_phase(s, "a -> phase 5", "1:1", 5, secs=2, every=1, tries=2) is None
    fail = [r for r in s.results if r.startswith("FAIL")]
    assert fail and "port_debug: phase 5 " in fail[0] and "last seen: phase 11" in fail[0]
    with pytest.raises(Abort):
        common.tap_to_phase(s, "a -> phase 5", "1:1", 5, secs=1, every=1, tries=1, fatal=True)
