"""tools/gacha_verify.py on a tiny synthetic image pair: an "illustration" (texture with alpha) is
scaled, moved and pasted onto a noisy "banner"; the matcher must find it with the right scale and
must not report an unrelated illustration. No game files are used."""

import pytest

import gacha_verify as gv

np = pytest.importorskip("numpy")
cv2 = pytest.importorskip("cv2")


def texture(seed, h=320, w=240):
    """A random scene of shapes on an opaque body with a transparent margin (BGRA)."""
    rng = np.random.default_rng(seed)
    img = np.zeros((h, w, 4), np.uint8)
    for _ in range(90):
        c = tuple(int(v) for v in rng.integers(0, 256, 3)) + (255,)
        x, y = int(rng.integers(20, w - 20)), int(rng.integers(20, h - 20))
        if rng.random() < 0.5:
            cv2.circle(img, (x, y), int(rng.integers(4, 22)), c, -1)
        else:
            cv2.rectangle(img, (x, y), (x + int(rng.integers(5, 30)), y + int(rng.integers(5, 30))), c, -1)
    img[:12, :, 3] = 0
    img[:, :12, 3] = 0
    return img


def test_art_keys():
    assert gv.art_key("cp0002_b07a_idol2020_02") == "cp0002_b07a"
    assert gv.art_key("cm115_b01a") == "cm115_b01a"
    assert gv.art_key("check_01") is None
    assert gv.art_of_ref("cp0305_fl01b") == "cp0305_b01b"
    assert gv.ref_names("cp0002_b10a") == {"fl": "cp0002_fl10a", "cs": "cp0002_cs10a"}
    assert gv.overlap([0, 0, 10, 10], [5, 5, 10, 10]) == 1.0


def test_detects_scaled_illustration():
    ref, other = texture(1), texture(2)
    rng = np.random.default_rng(3)
    banner = rng.integers(0, 60, (512, 1024, 3), dtype=np.uint8)
    small = cv2.resize(ref, None, fx=0.6, fy=0.6, interpolation=cv2.INTER_AREA)
    y, x = 100, 500
    a = small[:, :, 3:4].astype(np.float32) / 255
    roi = banner[y:y + small.shape[0], x:x + small.shape[1]]
    roi[:] = (small[:, :, :3] * a + roi * (1 - a)).astype(np.uint8)

    refs = {}
    for name, img in (("cp9001_fl01a", ref), ("cp9002_fl01a", other)):
        pts, desc = gv.features(img, max_side=gv.REF_MAX_SIDE)
        refs[name] = (pts, desc, img.shape[:2])
    matcher = gv.Matcher(refs)
    qpts, qdesc = gv.features(banner)
    found = matcher.detect(qpts, qdesc)
    names = [d["ref"] for d in found if d["inliers"] >= gv.ACCEPT["panel"]]
    assert names == ["cp9001_fl01a"]
    d = found[0]
    assert abs(d["scale"] - 0.6) < 0.05
    bx0, by0, bx1, by1 = d["box"]
    assert x - 10 <= bx0 and bx1 <= x + small.shape[1] + 10 and y - 10 <= by0 and by1 <= y + small.shape[0] + 10
