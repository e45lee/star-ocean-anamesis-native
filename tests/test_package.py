"""The release packages' content check (tools/package.py check(); README.md "Packaging"): a clean
stage passes, and every kind of game file or unlisted file fails it. Also the README template
renders for every package without leftover tags."""
import pathlib
import shutil
import sqlite3
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import package  # noqa: E402

TOP = "soa-port-test-linux-x64"


def make_stage(tmp_path):
    """A stage like stage_package's, without the binaries' build (placeholder x86-64 ELF)."""
    root = tmp_path / "stage" / TOP
    (root / "data").mkdir(parents=True)
    for prog in ("soa", "soa-server"):
        (root / prog).write_bytes(b"\x7fELF\x02\x01\x01" + b"\0" * 11 + b"\x3e\x00" + b"\0" * 44)
    for f in package.launcher_files("port", False):
        shutil.copyfile(ROOT / "scripts/package" / f, root / f)
    package.clean_pools(ROOT / "data/gacha_pools.sqlite3", root / "data/gacha_pools.sqlite3")
    for rel in package.git("ls-files", "standin-assets").splitlines():
        (root / rel).parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(ROOT / rel, root / rel)
    (root / "README.txt").write_text("x")
    return tmp_path / "stage", root


def test_clean_stage_passes(tmp_path):
    stage, _ = make_stage(tmp_path)
    assert package.check(str(stage), "port", None) == []


def test_pools_are_cleaned(tmp_path):
    stage, root = make_stage(tmp_path)
    db = sqlite3.connect(root / "data/gacha_pools.sqlite3")
    assert db.execute("select count(*) from gacha where name != ''").fetchone()[0] == 0
    assert db.execute("select count(*) from gacha").fetchone()[0] > 1000  # the pools themselves stay


@pytest.mark.parametrize("rel,data,why", [
    ("data/basmaster-3.7.0.sqlite3", None, "master_* tables"),        # a decrypted master
    ("extra.txt", b"hello", "not on the allow-list"),
    ("data/version.bin", b"\x00", "game file name"),
    ("game/x.aif", b"ADLD\x02" + b"\0" * 60, "ADLD"),
    ("libSOA.so", b"\x7fELF\x02\x01\x01" + b"\0" * 11 + b"\xb7\x00" + b"\0" * 44, "ARM64 ELF"),
    ("game/STAR+OCEAN.apk", b"PK\x03\x04" + b"\0" * 60, "zip"),
    ("standin-assets/Image/etc2/not_ours.aif", b"ADLD\x02" + b"\0" * 60, "not a tracked stand-in"),
])
def test_game_files_fail(tmp_path, rel, data, why):
    stage, root = make_stage(tmp_path)
    p = root / rel
    p.parent.mkdir(parents=True, exist_ok=True)
    if data is None:
        db = sqlite3.connect(p)
        db.execute("create table master_text(message_id text, text_value text)")
        db.commit()
        db.close()
    else:
        p.write_bytes(data)
    problems = package.check(str(stage), "port", None)
    assert any(why in x for x in problems), problems


def test_pools_with_titles_fail(tmp_path):
    stage, root = make_stage(tmp_path)
    shutil.copyfile(ROOT / "data/gacha_pools.sqlite3", root / "data/gacha_pools.sqlite3")  # not cleaned
    assert any("gacha.name" in x for x in package.check(str(stage), "port", None))


@pytest.mark.parametrize("kind", ["port", "emulator", "viewer"])
@pytest.mark.parametrize("windows", [False, True])
def test_readme_renders(kind, windows):
    t = (ROOT / "scripts/package/README.txt.in").read_text(encoding="utf-8")
    flags = {"windows": windows, "linux": not windows, "port": kind == "port", "emulator": kind == "emulator", "viewer": kind == "viewer"}
    v = dict(VERSION="V", TOP="T", EXE=".exe" if windows else "", PLATFORM="P", COMMIT="C")
    text = package.render(t, flags, v)
    assert "{{" not in text and "}}" not in text
    if kind == "viewer":
        assert ".xapk" in text and "3.7.0_APKPure.apk" not in text  # 380-ok: soa-viewer's game file
    else:
        assert "SOA-3.7.0-canonical-data.zip" in text and "STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk" in text
    assert "never uses a checkout around it" in text  # the user, 2026-10-07: release builds skip the checkout search
    for prog in {"port": ["soa", "soa-server"], "emulator": ["soa-emu", "soa-server"], "viewer": ["soa-viewer"]}[kind]:
        assert f"\n{prog}{v['EXE']}\n" in text  # a section per program
    if kind == "port":
        # both ways of running the port, and the separate server's launcher with its options
        launcher = "run-port-server" + (".cmd" if windows else ".sh")
        assert ("run-port.cmd" if windows else "run-port.sh") in text and f"\n{launcher}\n" in text
        assert "--port N" in text and "server.log" in text and "soa --server" in text


def test_seed_save_is_not_packaged(tmp_path):
    """The user, 2026-10-04: no seed save in the packages (data/saves/seed/Game.xml is a real player's)."""
    stage, root = make_stage(tmp_path)
    (root / "data/saves/seed").mkdir(parents=True)
    shutil.copyfile(ROOT / "data/saves/seed/Game.xml", root / "data/saves/seed/Game.xml")
    assert package.check(str(stage), "port", None) != []


def test_port_package_ships_the_server_and_its_launcher():
    """The port package: soa-server and the run-port-server launcher (the user, 2026-10-04), beside
    soa and run-port; on Windows the .cmd with the .ps1 it runs."""
    assert ("server", "soa-server") in package.PROGRAMS["port"]
    for f in ["soa-server", "soa-server.exe"] + package.launcher_files("port", False) + package.launcher_files("port", True):
        assert f in package.ALLOW["port"], f
    assert package.launcher_files("port", False) == ["run-port.sh", "run-port-server.sh"]
    assert package.launcher_files("port", True) == ["run-port.cmd", "run-port-server.cmd", "run-port-server.ps1"]
    assert package.launcher_files("emulator", True) == ["run-emulator.cmd", "run-emulator.ps1"]
    assert package.launcher_files("viewer", True) == ["run-viewer.cmd"]
    for f in package.launcher_files("port", False) + package.launcher_files("port", True):
        assert (ROOT / "scripts/package" / f).is_file(), f
