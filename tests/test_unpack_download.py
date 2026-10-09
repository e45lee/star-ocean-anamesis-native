"""tools/unpack_download.py: archive layout handling (no game files needed)."""
import zipfile

import pytest

import unpack_download as u


def make_zip(path, names):
    with zipfile.ZipFile(path, "w") as z:
        for n in names:
            z.writestr(n, b"x")


def test_top_folder():
    assert u.top_folder(["version.bin", "manifest/a", "B/c"]) == ""
    assert u.top_folder(["SOA-data/version.bin", "SOA-data/B/c"]) == "SOA-data/"
    assert u.top_folder(["a/x", "b/y"]) == ""  # two top folders: taken as the tree itself


def test_extract_flat_and_nested(tmp_path):
    for layout, prefix in (("flat", ""), ("nested", "SOA-data/")):
        z = tmp_path / f"{layout}.zip"
        make_zip(z, [prefix + "version.bin", prefix + "B/one.aif", prefix + "B/one.aif:Zone.Identifier"])
        dest = tmp_path / layout
        files, skipped, strip = u.extract(str(z), str(dest))
        assert (files, skipped, strip) == (2, 1, prefix)
        assert (dest / "version.bin").exists() and (dest / "B" / "one.aif").exists()
        assert not (dest / "B" / "one.aif:Zone.Identifier").exists()


def test_refuses_paths_outside(tmp_path):
    z = tmp_path / "bad.zip"
    make_zip(z, ["version.bin", "../escape"])
    with pytest.raises(SystemExit):
        u.extract(str(z), str(tmp_path / "dest"))


def test_expected_sha256(tmp_path):
    f = tmp_path / "x.sha256"
    f.write_text("F8F310FCA4122C2DFD57549F2723AF987448093FEEBBD66EB3E643CF84304578  x.zip\n")
    assert u.expected_sha256(str(f)) == "f8f310fca4122c2dfd57549f2723af987448093feebbd66eb3e643cf84304578"
