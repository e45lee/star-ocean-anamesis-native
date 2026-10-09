"""The release packages' content check (tools/package.py check(); README.md "Packaging"): a clean
stage passes, and every kind of game file or unlisted file fails it. Also the README template
renders for every package without leftover tags."""
import pathlib
import shutil
import sqlite3

import pytest

import package

ROOT = pathlib.Path(__file__).resolve().parent.parent

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
    for rel in package.git("ls-files", "--", *package.DATA_FILES).splitlines():
        (root / rel).parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(ROOT / rel, root / rel)
    (root / "README.txt").write_text("x")
    return tmp_path / "stage", root


def test_clean_stage_passes(tmp_path):
    stage, _ = make_stage(tmp_path)
    assert package.check(str(stage), "port", None) == []


def test_english_tables_are_packaged(tmp_path):
    """PLAN-english P2 (M-Q5): the English tables the server reads with --english go in (the server
    builds the -en master and story files from them at every start), and nothing else of
    data/english/ (the tool's inputs)."""
    stage, root = make_stage(tmp_path)
    assert (root / "data/english/master-en.tsv").is_file()
    # our story rows (2026-10-07: only machine/human/reviewed rows are committed; there may be none yet)
    repo = pathlib.Path(__file__).resolve().parent.parent
    assert len(list((root / "data/english/story-en").glob("TS_*.tsv"))) == \
        len(list((repo / "data/english/story-en").glob("TS_*.tsv")))
    assert not (root / "data/english/glossary.tsv").exists() and not (root / "data/english/story-en/index.tsv").exists()
    assert len(list((root / "standin-assets-en/recipes").glob("*.json"))) > 0
    assert package.check(str(stage), "port", None) == []
    assert package.check(str(stage), "viewer", None) != []  # the viewer runs no server: not on its list


def test_global_master_is_the_one_exception(tmp_path):
    """The user, 2026-10-07 (PLAN-english M-Q5, P2): packages carry data/basmaster-gl.sqlite3, git's
    own blob of it, and the scan accepts nothing else that looks like a master DB."""
    stage, root = make_stage(tmp_path)
    assert (root / "data/basmaster-gl.sqlite3").read_bytes() == (ROOT / "data/basmaster-gl.sqlite3").read_bytes()
    assert package.check(str(stage), "port", None) == []


@pytest.mark.parametrize("case", ["other-master-at-path", "changed", "renamed", "copy-elsewhere", "jp-master"])
def test_global_master_exception_is_exact(tmp_path, case):
    stage, root = make_stage(tmp_path)
    gl = root / "data/basmaster-gl.sqlite3"
    if case == "other-master-at-path":  # another master DB under the allowed name
        gl.unlink()
        db = sqlite3.connect(gl)
        db.execute("create table master_text(message_id text, text_value text)")
        db.commit()
        db.close()
    elif case == "changed":  # Global's, one byte changed
        b = bytearray(gl.read_bytes())
        b[-1] ^= 1
        gl.write_bytes(bytes(b))
    elif case == "renamed":
        gl.rename(root / "data/basmaster-gl2.sqlite3")
    elif case == "copy-elsewhere":
        shutil.copyfile(gl, root / "data/english/basmaster-gl.sqlite3")
    else:  # the JP master under Global's name
        shutil.copyfile(ROOT / "data/basmaster-3.7.0.sqlite3", gl)
    problems = package.check(str(stage), "port", None)
    assert any("master_* tables" in x or "game file name" in x for x in problems), problems


def test_pools_are_cleaned(tmp_path):
    stage, root = make_stage(tmp_path)
    db = sqlite3.connect(root / "data/gacha_pools.sqlite3")
    assert db.execute("select count(*) from gacha where name != ''").fetchone()[0] == 0
    assert db.execute("select count(*) from gacha").fetchone()[0] > 1000  # the pools themselves stay


@pytest.mark.parametrize("rel,data,why", [
    ("data/basmaster-3.7.0.sqlite3", None, "master_* tables"),        # a decrypted master
    # a built English master (PLAN-english P2): never packaged, under any name or place
    ("data/basmaster-en.sqlite3", None, "master_* tables"),
    ("data/english/basmaster-en.sqlite3", None, "master_* tables"),
    ("data/english/master-en.sqlite3", None, "master_* tables"),
    ("data/english/story-en/TS_9999.tsv", None, "master_* tables"),   # on the allow-list, still scanned
    ("data/english/story-en/TS_1010-en.msgp", b"ADLD\x02" + b"\0" * 60, "ADLD"),  # a built -en story file
    ("data/english/glossary.tsv", b"x", "not on the allow-list"),
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
    assert package.launcher_files("port", False) == ["run-port.sh", "run-port-en.sh", "run-port-server.sh"]
    assert package.launcher_files("port", True) == ["run-port.cmd", "run-port-en.cmd", "run-port-server.cmd", "run-port-server.ps1"]
    # the English launchers (PLAN-english P1, Q5): run-emulator-en.cmd runs run-emulator.ps1
    assert package.launcher_files("emulator", False) == ["run-emulator.sh", "run-emulator-en.sh"]
    assert package.launcher_files("emulator", True) == ["run-emulator.cmd", "run-emulator.ps1", "run-emulator-en.cmd"]
    assert package.launcher_files("viewer", True) == ["run-viewer.cmd"]
    for kind in ("port", "emulator"):
        for f in package.launcher_files(kind, False) + package.launcher_files(kind, True):
            assert (ROOT / "scripts/package" / f).is_file(), f
            assert f in package.ALLOW[kind], f
