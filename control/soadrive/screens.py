"""Screens: RMSE (ImageMagick, on a 182x324 copy as port/scripts/smoke.py), flat-frame and colour
probes, settled screenshots (PLAN-consolidate D10, D11)."""
import os
import shutil
import subprocess


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


def rmse(a, b, mask=()):
    """ImageMagick's normalized RMSE of a and b on 182x324 copies (with the regions in `mask`
    blanked on both); 1.0 when it can't compare."""
    if mask:
        a = _masked(a, mask, b + ".mask-a.png")
        b = _masked(b, mask, b + ".mask-b.png")
    r = subprocess.run(["compare", "-metric", "RMSE", "-resize", "182x324", a, b, "null:"], capture_output=True, text=True)
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
