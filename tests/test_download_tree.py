"""soa_save/download_tree.py: the download as a folder and the same files as a stored zip (flat, or
under one top folder) read the same way, in place (no extraction)."""
import io
import os
import pathlib
import sys
import zipfile

import pytest

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))
from soa_save.download_tree import DEFAULT, DownloadTree, open_member_or_file  # noqa: E402

FILES = {
    "version.bin": b"\x81\xa8revision\xa41471",
    "manifest/etc2/hi/version_latest_ep1.bin": b"manifest",
    "Image/etc2/banner_a.aif": bytes(range(256)) * 40,
    "Image/etc2/banner_b.aif": b"",
    "Image/etc2/hi/banner_a.aif": b"hi",
    "Movie/m1.mp4": os.urandom(70000),
    "Scenario/TS_1000.msgp": b"ts",
}


def make_folder(d: pathlib.Path) -> pathlib.Path:
    for rel, data in FILES.items():
        (d / rel).parent.mkdir(parents=True, exist_ok=True)
        (d / rel).write_bytes(data)
    return d


def make_zip(p: pathlib.Path, top: str = "", deflate: bool = False) -> pathlib.Path:
    with zipfile.ZipFile(p, "w", zipfile.ZIP_DEFLATED if deflate else zipfile.ZIP_STORED) as z:
        dirs = sorted({top + rel.rsplit("/", 1)[0] + "/" for rel in FILES if "/" in rel})
        for d in dirs:  # directory entries, as the canonical zip has
            z.writestr(d, b"")
        for rel, data in FILES.items():
            z.writestr(top + rel, data)
    return p


@pytest.fixture(params=["flat", "nested", "deflated"])
def trees(tmp_path, request):
    folder = DownloadTree.open(make_folder(tmp_path / "folder"))
    zp = make_zip(tmp_path / "d.zip", "SOA-data/" if request.param == "nested" else "", request.param == "deflated")
    return folder, DownloadTree.open(zp), request.param


def test_same_tree(trees):
    folder, z, kind = trees
    assert not folder.is_zip and z.is_zip
    assert z.prefix == ("SOA-data/" if kind == "nested" else "")
    assert folder.files() == z.files() == sorted(FILES)
    assert folder.files("Image") == z.files("Image/") == ["Image/etc2/banner_a.aif", "Image/etc2/banner_b.aif", "Image/etc2/hi/banner_a.aif"]
    assert folder.list("Image/etc2") == z.list("Image/etc2") == ["banner_a.aif", "banner_b.aif"]
    assert folder.list("") == z.list("") == ["version.bin"]
    assert folder.list("Nope") == z.list("Nope") == []
    assert folder.glob("manifest/*/*/version_latest_*.bin") == z.glob("manifest/*/*/version_latest_*.bin")
    for t in (folder, z):
        assert t.is_dir("Image/etc2") and t.is_dir("") and not t.is_dir("Image/etc") and not t.is_dir("version.bin")
        assert t.exists("Movie/m1.mp4") and not t.exists("Movie") and not t.exists("missing")
        for rel, data in FILES.items():
            assert t.size(rel) == len(data) and t.read(rel) == data
        with t.open_file("Movie/m1.mp4") as f:
            f.seek(1000)
            assert f.read(10) == FILES["Movie/m1.mp4"][1000:1010]
            f.seek(-5, io.SEEK_END)
            assert f.read() == FILES["Movie/m1.mp4"][-5:]
            assert f.read() == b""
        with pytest.raises(FileNotFoundError):
            t.read("missing")


def test_in_place(trees):
    folder, z, kind = trees
    for rel, data in FILES.items():
        loc = z.locate(rel)
        if kind == "deflated":
            assert loc is None and z.host_spec(rel) is None  # not in place: read() inflates it
            continue
        path, off, size = loc
        with open(path, "rb") as f:
            f.seek(off)
            assert f.read(size) == data
        assert z.host_spec(rel) == f"{path}@{off}+{size}"
        assert folder.host_spec(rel) == folder.locate(rel)[0]


def test_open_errors_and_members(tmp_path):
    with pytest.raises(FileNotFoundError):
        DownloadTree.open(tmp_path / "none")
    (tmp_path / "junk.bin").write_bytes(b"not a zip")
    assert DownloadTree.open_or_none(tmp_path / "junk.bin") is None
    z = DownloadTree.open(make_zip(tmp_path / "d.zip"))
    assert open_member_or_file("Scenario/TS_1000.msgp", z) == b"ts"
    assert open_member_or_file(str(tmp_path / "junk.bin"), z) == b"not a zip"


def test_forked_readers(tmp_path):
    # a tree handed to worker processes (pickled: each reopens it) reads the same there
    import concurrent.futures as cf
    import multiprocessing as mp

    z = DownloadTree.open(make_zip(tmp_path / "d.zip"))
    z.read("version.bin")
    with cf.ProcessPoolExecutor(4, mp_context=mp.get_context("fork")) as ex:
        got = list(ex.map(_read_all, [z] * 8))
    assert all(g == [FILES[r] for r in sorted(FILES)] for g in got)


def _read_all(t):
    return [t.read(r) for r in t.files()]


@pytest.mark.skipif(not os.path.exists(DEFAULT), reason="no work/SOA-3.7.0-canonical-data.zip")
def test_the_canonical_zip():
    t = DownloadTree.open()
    assert t.is_zip and t.prefix == ""
    assert len(t.files()) == 26046 and t.exists("sqlite/basmaster.sqlite3")
    assert t.read("version.bin")[:1] in (b"\x84", b"\x85", b"\x83")  # a MessagePack map
