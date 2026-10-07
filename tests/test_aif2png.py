"""tools/aif2png (build/tools/aif2png/aif2png) on a committed stand-in image: the ADLD layer is
soa/adld.h, so an AES-wrapped copy (encType 2) converts to the same PNG as the XOR-wrapped file.
Skipped when aif2png isn't built."""
import pathlib
import subprocess

import pytest

from soa_save import adld

ROOT = pathlib.Path(__file__).resolve().parent.parent
AIF2PNG = ROOT / "build/tools/aif2png/aif2png"
NAME = "Image/etc2/banner_gacha_pickup_role_0054.aif"


@pytest.mark.skipif(not AIF2PNG.exists(), reason="aif2png isn't built (scripts/build.sh)")
def test_xor_and_aes_files_give_the_same_png(tmp_path):
    xored = (ROOT / "standin-assets" / NAME).read_bytes()
    plain = adld.decode(xored, NAME)
    assert adld.encode(plain, NAME, adld.XOR) == xored
    (tmp_path / "aes.aif").write_bytes(adld.encode(plain, NAME, adld.AES))
    outs = []
    for src, out in ((ROOT / "standin-assets" / NAME, tmp_path / "xor.png"), (tmp_path / "aes.aif", tmp_path / "aes.png")):
        r = subprocess.run([str(AIF2PNG), str(src), NAME, str(out)], capture_output=True, text=True)
        assert r.returncode == 0 and r.stdout.startswith("ok\t"), r.stdout + r.stderr
        outs.append(out.read_bytes())
    assert outs[0] == outs[1]
