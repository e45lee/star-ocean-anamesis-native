"""tools/check_download.py on a tiny synthetic download: a version.bin, Bulk and Individual
manifests, one XOR-ADLD member, one plain (e = 0) member and a bundle entry (flags 1)."""
import hashlib
import pathlib
import struct
import sys

import msgpack
import pytest

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))
import check_download  # noqa: E402
from soa_save.adld import chash32, decode  # noqa: E402

VERSION_ID = "0123456789abcdef0123456789abcdef"
XOR_NAME, PLAIN_NAME = "Image/etc2/test_a.aif", "Sound/test_b.aac"
XOR_TEXT, PLAIN_TEXT = b"hello, anamnesis! " * 7, b" CAA plain payload"


def adld_xor(name, plain):
    key = b"%x" % chash32(name.encode())
    return b"ADLD" + struct.pack("<I", 1) + bytes(8) + bytes(b ^ key[i % len(key)] for i, b in enumerate(plain))


def make_download(d: pathlib.Path):
    stored = {XOR_NAME: (adld_xor(XOR_NAME, XOR_TEXT), XOR_TEXT, 1), PLAIN_NAME: (PLAIN_TEXT, PLAIN_TEXT, 0)}
    assert decode(stored[XOR_NAME][0], XOR_NAME) == XOR_TEXT
    bundles = {name: f"I/{chash32(name.encode()):08x}/{i:08x}.bin" for i, name in enumerate(stored)}
    individual, assets = {}, {}
    for name, (data, plain, e) in stored.items():
        (d / name).parent.mkdir(parents=True, exist_ok=True)
        (d / name).write_bytes(data)
        member = {"size": len(plain), "md5": hashlib.sha1(plain).hexdigest(), "meta": [], "p": bundles[name][:-4], "e": e, "ep_data": ""}
        individual[bundles[name]] = {name: member, "md5": "b" * 40, "size": len(plain) + 64, "meta": []}
        assets[name] = {"md5": member["md5"], "size": len(data), "time": 1, "parentHash": chash32(bundles[name].encode()),
                        "flags": 0, "encType": e, "ep_data": "", "meta": []}
    bulk = {"B/00000000/00000001.bin": {name: dict(m[name], p="B/00000000/00000001") for b, m in individual.items() for name in m if isinstance(m[name], dict)}}
    bulk["B/00000000/00000001.bin"].update({"md5": "c" * 40, "size": 999, "meta": []})
    first = bundles[XOR_NAME]
    assets[first] = {"md5": "b" * 40, "size": 0, "time": 0, "parentHash": chash32(first.encode()), "flags": 1, "encType": 0, "ep_data": "", "meta": []}
    (d / "version.bin").write_bytes(msgpack.packb({"appliversion": 1, "version": VERSION_ID, "revision": "1", "assets": assets}))
    mdir = d / "manifest/etc2/hi"
    mdir.mkdir(parents=True)
    total = len(XOR_TEXT) + len(PLAIN_TEXT)
    for name, m in (("Bulk", bulk), ("Individual", individual)):
        (mdir / f"version_latest_{name}.bin").write_bytes(msgpack.packb({"version": VERSION_ID, "toolversion": "1.2.0", "assets": m}))
        (mdir / f"version_latest_{name}.version").write_bytes(f"version:{VERSION_ID}\r\ntotalSize:{total}\r\n".encode())
    (mdir / "version.version").write_bytes(VERSION_ID.encode())
    return d


@pytest.fixture
def download(tmp_path):
    return make_download(tmp_path / "download")


def kinds(res):
    return sorted({p["kind"] for p in res["problems"]})


@pytest.mark.parametrize("quick", [False, True])
def test_clean(download, quick):
    res = check_download.check(str(download), jobs=2, quick=quick)
    assert res["ok"], res["problems"]
    assert res["warnings"] == []
    assert res["manifests"]["Bulk"]["members"] == 2 and res["manifests"]["Individual"]["status"] == "OK"
    assert res["version_bin"]["bundles"] == 1 and res["version_bin"]["parent_hash"] == {"Individual": 2}
    assert check_download.main([str(download), "--jobs", "2"]) == 0


def test_corrupted_member(download):
    path = download / XOR_NAME
    data = bytearray(path.read_bytes())
    data[20] ^= 0xFF  # same size, other payload
    path.write_bytes(bytes(data))
    res = check_download.check(str(download), jobs=2)
    assert kinds(res) == ["hash"]
    assert {p["name"] for p in res["problems"]} == {XOR_NAME}
    assert {p["manifest"] for p in res["problems"]} == {"Bulk", "Individual", None}  # None: version.bin's entry
    assert check_download.main([str(download), "--jobs", "2"]) == 1
    assert check_download.check(str(download), jobs=2, quick=True)["ok"]  # --quick doesn't hash


def test_missing_extra_and_sizes(download):
    (download / PLAIN_NAME).unlink()
    (download / "Sound/stray.bin").write_bytes(b"x")
    (download / "manifest/etc2/hi/version_latest_Bulk.version").write_bytes(f"version:{VERSION_ID}\r\ntotalSize:1\r\n".encode())
    res = check_download.check(str(download), jobs=2, quick=True)
    assert kinds(res) == ["extra", "missing", "version-file"]
    assert res["manifests"]["Bulk"]["status"] == "FAIL" and res["manifests"]["Bulk"]["bad_files"] == 1


def test_header_and_parent_hash(download):
    path = download / XOR_NAME
    path.write_bytes(path.read_bytes()[:4] + struct.pack("<I", 2) + path.read_bytes()[8:])  # e = 1 stored as AES
    vb = msgpack.unpackb((download / "version.bin").read_bytes(), raw=False)
    vb["assets"][PLAIN_NAME]["parentHash"] ^= 1
    vb["assets"]["Sound/unlisted.spk"] = dict(vb["assets"][PLAIN_NAME], flags=0)
    (download / "Sound/unlisted.spk").write_bytes(PLAIN_TEXT)
    (download / "version.bin").write_bytes(msgpack.packb(vb))
    res = check_download.check(str(download), jobs=2, quick=True)
    assert "enc" in kinds(res) and "parentHash" in kinds(res)
    assert [w["kind"] for w in res["warnings"]] == ["unbundled"]  # in version.bin, in no manifest: a warning


def test_claims_the_canonical_revision(download):
    if not pathlib.Path(check_download.CANONICAL).exists():
        pytest.skip("no data/version-3.7.0.bin")
    vb = msgpack.unpackb((download / "version.bin").read_bytes(), raw=False)
    vb["revision"] = msgpack.unpackb(pathlib.Path(check_download.CANONICAL).read_bytes(), raw=False)["revision"]
    (download / "version.bin").write_bytes(msgpack.packb(vb))
    res = check_download.check(str(download), jobs=2, quick=True)
    assert kinds(res) == ["version-bin"]  # revision 1471 but not the canonical bytes
