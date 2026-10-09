"""Screens: RMSE (Pillow and numpy, on a 182x324 copy), flat-frame and colour probes (ImageMagick),
settled screenshots (PLAN-consolidate D10, D11)."""
import collections
import functools
import hashlib
import io
import os
import shutil
import subprocess
import time

import numpy as np
from PIL import Image


# Regions (window pixels at 729x1296: x0, y0, x1, y1) blanked on both images before a comparison.
# Home's character: her idle motion (she turns, shifts her weight) differs from run to run; the
# rest of home (the header's numbers, the buttons and their badges, the footer) is compared.
HOME_CHARACTER = (130, 240, 610, 1000)
# The gacha screen's banner carousel (and its page number): it turns every few seconds, so which
# banner a screenshot catches is timing; the banner drawn is in the packets (SaleGacha's arguments).
GACHA_CAROUSEL = (0, 320, 729, 875)
# The event screens' banner carousel at the top (the event list, a board): it turns every few seconds.
EVENT_CAROUSEL = (0, 190, 729, 320)


# ---- RMSE (Pillow and numpy; the one copy: port/scripts/smoke.py, tools/compare_tutorial.py and
# control/flowctl.py use it). It reproduces what the drivers' thresholds were tuned on, ImageMagick's
# `compare -metric RMSE -resize SIZE` (to about 1e-5): a copy fitted into SIZE (aspect kept, the
# size rounded), resampled in two clamped passes, the RMSE over R, G and B normalized to 0..1. Its
# filter: Lanczos (3 lobes), or Mitchell for a masked copy (ImageMagick's masked copy gained an
# alpha channel, which made it pick Mitchell; the masked thresholds were tuned on that).
def _lanczos(x):
    x = np.abs(x)
    return np.where(x < 3, np.sinc(x) * np.sinc(x / 3), 0.0)


def _mitchell(x, b=1 / 3, c=1 / 3):
    x = np.abs(x)
    near = ((12 - 9 * b - 6 * c) * x ** 3 + (-18 + 12 * b + 6 * c) * x ** 2 + (6 - 2 * b)) / 6
    far = ((-b - 6 * c) * x ** 3 + (6 * b + 30 * c) * x ** 2 + (-12 * b - 48 * c) * x + (8 * b + 24 * c)) / 6
    return np.where(x < 1, near, np.where(x < 2, far, 0.0))


_FILTERS = {"lanczos": (_lanczos, 3.0), "mitchell": (_mitchell, 2.0)}


@functools.lru_cache(maxsize=64)
def _weights(n_in, n_out, name):
    """One axis's resampling matrix (n_out, n_in), float32."""
    kernel, support = _FILTERS[name]
    scale = n_out / n_in
    blur = max(1.0 / scale, 1.0)
    reach = support * blur
    w = np.zeros((n_out, n_in), dtype=np.float32)
    for o in range(n_out):
        center = (o + 0.5) / scale
        lo, hi = max(int(center - reach + 0.5), 0), min(int(center + reach + 0.5), n_in)
        k = kernel((np.arange(lo, hi) + 0.5 - center) / blur)
        w[o, lo:hi] = k / k.sum()
    return w


def _resize(px, w, h, name):
    """px (H, W, 3) resampled to (h, w, 3): columns, then rows (each a matrix product), each pass
    clamped to 0..1."""
    rows, cols, ch = px.shape
    t = np.ascontiguousarray(px.transpose(0, 2, 1)).reshape(rows * ch, cols) @ _weights(cols, w, name).T
    t = np.clip(t, 0.0, 1.0).reshape(rows, ch * w)
    t = np.clip(_weights(rows, h, name) @ t, 0.0, 1.0)
    return t.reshape(h, ch, w).transpose(0, 2, 1)


def _fit(size, w, h):
    """(width, height) of a w x h image fitted into size ("WxH" or (W, H)), the aspect kept."""
    bw, bh = (int(v) for v in size.lower().split("x")) if isinstance(size, str) else size
    f = min(bw / w, bh / h)
    return max(1, int(w * f + 0.5)), max(1, int(h * f + 0.5))


_COPIES = collections.OrderedDict()  # (content hash, mask, size) -> pixels: a watcher compares each shot twice


def _pixels(path, mask, size):
    with open(path, "rb") as f:
        data = f.read()
    key = (hashlib.sha1(data).digest(), tuple(mask), size)
    if key in _COPIES:
        _COPIES.move_to_end(key)
        return _COPIES[key]
    with Image.open(io.BytesIO(data)) as im:
        px = np.asarray(im.convert("RGB"), dtype=np.float32) / np.float32(255)
    if mask:  # the regions are window pixels at 729x1296: the copy is that size first (8-bit)
        if px.shape[:2] != (1296, 729):
            px = np.round(_resize(px, 729, 1296, "lanczos") * 255) / np.float32(255)
        px = px.copy()
        for x0, y0, x1, y1 in mask:
            px[y0:y1 + 1, x0:x1 + 1] = 0.0
    if size is not None:
        w, h = _fit(size, px.shape[1], px.shape[0])
        if (w, h) != (px.shape[1], px.shape[0]):
            px = _resize(px, w, h, "mitchell" if mask else "lanczos")
    _COPIES[key] = px
    while len(_COPIES) > 8:
        _COPIES.popitem(last=False)
    return px


def rmse(a, b, mask=(), size="182x324"):
    """The normalized RMSE (0..1) of the screenshots a and b on copies fitted into `size` ("WxH";
    None: as they are), the regions in `mask` blanked on both. 1.0 (as different as can be) when
    it can't compare: a file missing or unreadable, or the copies' sizes differ."""
    try:
        x, y = _pixels(a, mask, size), _pixels(b, mask, size)
    except (OSError, ValueError):
        return 1.0
    if x.shape != y.shape:
        return 1.0
    return float(np.sqrt(np.mean((x.astype(np.float64) - y) ** 2)))


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
