"""Screens: RMSE (ImageMagick, on a 182x324 copy as port/scripts/smoke.py), flat-frame and colour
probes, settled screenshots (PLAN-consolidate D10, D11)."""
import os
import shutil
import subprocess
import time


# Regions (window pixels at 729x1296: x0, y0, x1, y1) blanked on both images before a comparison.
# Home's character: her idle motion (she turns, shifts her weight) differs from run to run; the
# rest of home (the header's numbers, the buttons and their badges, the footer) is compared.
HOME_CHARACTER = (130, 240, 610, 1000)
# The gacha screen's banner carousel (and its page number): it turns every few seconds, so which
# banner a screenshot catches is timing; the banner drawn is in the packets (SaleGacha's arguments).
GACHA_CAROUSEL = (0, 320, 729, 875)


def _masked(path, regions, tmp):
    args = ["convert", path, "-resize", "729x1296!", "-fill", "black"]
    for x0, y0, x1, y1 in regions:
        args += ["-draw", "rectangle %d,%d %d,%d" % (x0, y0, x1, y1)]
    subprocess.run(args + [tmp], capture_output=True)
    return tmp


def rmse(a, b, mask=(), size="182x324"):
    """ImageMagick's normalized RMSE of a and b on `size` copies (182x324, with the regions in
    `mask` blanked on both); 1.0 when it can't compare."""
    if mask:
        a = _masked(a, mask, b + ".mask-a.png")
        b = _masked(b, mask, b + ".mask-b.png")
    r = subprocess.run(["compare", "-metric", "RMSE", "-resize", size, a, b, "null:"], capture_output=True, text=True)
    if mask:
        for f in (a, b):
            os.remove(f) if os.path.exists(f) else None
    out = r.stderr.strip()
    try:
        return float(out[out.index("(") + 1:out.index(")")])
    except ValueError:
        return 1.0


def fx(path, expr, crop=None):
    args = ["convert", path] + (["-crop", crop] if crop else []) + ["-format", "%[fx:" + expr + "]", "info:"]
    r = subprocess.run(args, capture_output=True, text=True)
    try:
        return float(r.stdout.strip())
    except ValueError:
        return None


def flat(path):
    """One flat colour: a transition frame (black or white)."""
    v = fx(path, "standard_deviation", None) if os.path.exists(path) else None
    return v is None or v < 0.015


def mean(path, crop=None, gray=True):
    if not gray:
        return fx(path, "mean", crop)
    r = subprocess.run(["convert", path] + (["-crop", crop] if crop else []) + ["-colorspace", "gray", "-format", "%[fx:mean]", "info:"],
                       capture_output=True, text=True)
    try:
        return float(r.stdout.strip())
    except ValueError:
        return None


def settled_shot(send, path, tries=6, still=0.01):
    """A screenshot of a screen that has stopped changing: send(["shot:PATH"]) until two in a row,
    1.5 s apart, are within `still` RMSE and not a flat transition frame. At most `tries` shots;
    the last is kept anyway (an animated screen, e.g. home's character, never settles). Returns
    True when it settled."""
    prev = path + ".prev.png"
    ok = False
    for i in range(tries):
        if send(["wait:1500" if i else "wait:0", "shot:" + path]) and os.path.exists(path):
            if not flat(path) and os.path.exists(prev) and rmse(prev, path) <= still:
                ok = True
                break
            shutil.copyfile(path, prev)
    if os.path.exists(prev):
        os.remove(prev)
    return ok


# Watch compares screens at this size: small enough that the backgrounds' twinkling stars and the
# buttons' glints average out (consecutive frames of a still screen within 0.005; at 182x324 the
# follow screen's stars alone make 0.02), large enough that a fade, a dialog or a filled panel shows
# (0.03 to 0.3). Measured on frame sequences 0.5 s apart, 2026-10-07.
WATCH_SIZE = "46x81"
# Home never holds still: its character moves in front of most of it, the mascot's speech bubble
# comes and goes, the プレゼント badge pulses, the main buttons glint, the character's legs show
# between the footer's buttons. Watch compares only the header and the side buttons but プレゼント
# (0.000 to 0.001 between frames of a still home; the screens home leads to 0.06+; the ≡ menu
# opened, its ≡ turned to an arrow, 0.008).
HOME_MOVING = ((0, 150, 600, 1296), (600, 270, 729, 380), (600, 850, 729, 1296))


# A screen that never holds still but moves only a little (a selected card's pulse 0.025, a 3D
# character's idle; a fade or a new screen 0.05 to 0.3 between looks) counts as settled once it has
# moved that little for CALM_SECS: no fade lasts that long.
CALM_LIMIT = 0.05
CALM_SECS = 3.0


class Watch:
    """A screen watched until it settles (code review T3: the sessions' condition waits). Each look()
    takes a screenshot to `path` (send(["wait:MS", "shot:PATH"])) and compares it with the previous
    one at WATCH_SIZE (the regions in `mask` blanked on both; e.g. HOME_MOVING). `still`: the two
    within `limit` RMSE and the newer no flat transition frame, `hold` looks in a row; or calm: every
    comparison within CALM_LIMIT for `hold` x CALM_SECS. `rmse` keeps the last comparison (for a
    failure's message)."""

    def __init__(self, send, path, mask=(), limit=0.01, interval_ms=600, hold=1):
        self.send, self.path, self.mask, self.limit, self.interval_ms = send, path, mask, limit, interval_ms
        self.prev = path + ".prev.png"
        self.rmse = None
        self.hold, self.stills, self.calm_since, self.last_at = hold, 0, None, None
        self.calm = False
        for f in (self.path, self.prev):  # a previous Watch's frames never count as this one's
            if os.path.exists(f):
                os.remove(f)

    def _compare(self):
        if not os.path.exists(self.path) or flat(self.path) or not os.path.exists(self.prev):
            return None
        return rmse(self.prev, self.path, self.mask, WATCH_SIZE)

    def look(self, wait_ms=None):
        """One more screenshot; True when the screen has settled (still, or calm)."""
        if os.path.exists(self.path):
            shutil.copyfile(self.path, self.prev)
            os.remove(self.path)
        ms = self.interval_ms if wait_ms is None else wait_ms
        before = self.last_at
        self.send(["wait:%d" % ms, "shot:" + self.path])
        self.last_at = time.monotonic()
        self.rmse = self._compare()
        if self.rmse is None or self.rmse > CALM_LIMIT:
            self.calm_since = None
        elif self.calm_since is None:
            self.calm_since = before
        self.stills = self.stills + 1 if self.rmse is not None and self.rmse <= self.limit else 0
        self.calm = self.calm_since is not None and self.last_at - self.calm_since >= self.hold * CALM_SECS
        return self.stills >= self.hold or self.calm

    def differs(self, ref, limit=0.02):
        """The last screenshot differs from the screenshot ref (RMSE above limit, the mask blanked)."""
        return os.path.exists(self.path) and rmse(ref, self.path, self.mask, WATCH_SIZE) > limit

    def done(self):
        if os.path.exists(self.prev):
            os.remove(self.prev)
