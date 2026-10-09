"""soadrive.screens.rmse, the one screenshot RMSE (Pillow and numpy; smoke.py, compare_tutorial.py and
flowctl.py use it): ImageMagick's `compare -metric RMSE -resize SIZE` values, which the drivers'
thresholds were tuned on, to about 1e-5, without ImageMagick."""
import numpy as np
import pytest
from PIL import Image

from soadrive import screens

HOME, HOME_LATER = "tests/smoke-base/02-home.png", "tests/smoke-base/07-home.png"


@pytest.mark.parametrize("mask,size,magick", [
    ((), "182x324", 0.134632),                         # compare -metric RMSE -resize 182x324 (ImageMagick 6.9)
    ((), "46x81", 0.123635),
    ((screens.HOME_CHARACTER,), "46x81", 0.0230111),   # the masked copies (ImageMagick resized them with Mitchell)
    ((screens.HOME_CHARACTER,), "182x324", 0.0306537),
])
def test_imagemagicks_values(repo, mask, size, magick):
    assert screens.rmse(str(repo / HOME), str(repo / HOME_LATER), mask, size) == pytest.approx(magick, abs=5e-5)


def png(path, rgb, size=(729, 1296), box=None, box_rgb=(255, 255, 255)):
    a = np.zeros((size[1], size[0], 3), dtype=np.uint8)
    a[:] = rgb
    if box:
        x0, y0, x1, y1 = box
        a[y0:y1 + 1, x0:x1 + 1] = box_rgb
    Image.fromarray(a).save(path)
    return str(path)


def test_conventions(tmp_path):
    black, white = png(tmp_path / "k.png", (0, 0, 0)), png(tmp_path / "w.png", (255, 255, 255))
    assert screens.rmse(black, black) == 0.0
    assert screens.rmse(black, white) == pytest.approx(1.0)
    # can't compare: 1.0 (a missing file, different sizes as they are)
    assert screens.rmse(black, str(tmp_path / "missing.png")) == 1.0
    assert screens.rmse(black, png(tmp_path / "small.png", (0, 0, 0), (100, 100)), size=None) == 1.0


def test_the_mask_blanks_a_region(tmp_path):
    region = (130, 240, 610, 1000)
    plain = png(tmp_path / "a.png", (40, 80, 120))
    boxed = png(tmp_path / "b.png", (40, 80, 120), box=region)
    assert screens.rmse(plain, boxed) > 0.1
    assert screens.rmse(plain, boxed, (region,)) == 0.0
    assert screens.rmse(plain, boxed, (region,), screens.WATCH_SIZE) == 0.0
