"""scripts/windows_stage.py, the Windows stage's whitelist (scripts/windows-stage.list): the plan
names only listed files, never .claude/ (worktrees), build/ or an unlisted work/ file, and a stage's
extras are found and pruned (run/ and the .exe side copies kept)."""
import os
import subprocess
import sys

import pytest

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "scripts"))
import windows_stage as ws  # noqa: E402

LIST = """\
port/CMakeLists.txt          # marker
data/                        # the data
data/*.sqlite3               # the DBs
work/lib.so                  # the library
work/phone/      --phone     # the phone
apk/*.xapk       --viewer    # the viewer's game
work/xapk/       --viewer-else  # its unpacked one
build-win/port/soa.exe       # the program
"""


def write(p, text="x"):
    os.makedirs(os.path.dirname(p), exist_ok=True)
    with open(p, "w") as f:
        f.write(text)


@pytest.fixture
def fake(tmp_path):
    """A fake checkout: tracked files, plus what must never be staged."""
    r = str(tmp_path / "repo")
    for p in ["port/CMakeLists.txt", "port/src/a.cpp", "data/a.sqlite3", "data/saves/Game.xml", "docs/x.md", "README.md"]:
        write(os.path.join(r, p))
    subprocess.run(["git", "init", "-q", r], check=True)
    subprocess.run(["git", "-C", r, "add", "."], check=True)
    for p in [".claude/worktrees/other/data/a.sqlite3", ".claude/worktrees/other/port/CMakeLists.txt", "build/port/soa",
              "work/lib.so", "work/extra.zip", "work/phone/data/f", "data/untracked.sqlite3",
              "data/a.sqlite3:Zone.Identifier", "build-win/port/soa.exe", "build-win/tools/other.exe"]:
        write(os.path.join(r, p))
    lst = str(tmp_path / "list")
    write(lst, LIST)
    return r, ws.parse(lst)


def rels(items):
    return sorted(rel for _, _, rel in items)


def test_plan_is_the_list_only(fake):
    r, entries = fake
    got = rels(ws.plan(r, entries))
    # (data/ and data/*.sqlite3 overlap: the tracked file twice is harmless to rsync)
    assert sorted(set(got)) == ["build-win/port/soa.exe", "data/a.sqlite3", "data/saves/Game.xml", "port/CMakeLists.txt",
                                "work/lib.so"]
    for p in got:
        assert not p.startswith((".claude", "build/", "docs/")) and p not in ("work/extra.zip", "README.md")
    assert "data/untracked.sqlite3" not in got  # (a directory of the checkout: its tracked files only)


def test_plan_options(fake):
    r, entries = fake
    assert ("mirror", r, "work/phone") in ws.plan(r, entries, options=["--phone"])
    v = rels(ws.plan(r, entries, options=["--viewer"]))
    assert "work/xapk" not in v and not any(p.startswith("apk/") for p in v)  # neither: warned, nothing staged
    write(os.path.join(r, "work/xapk/f"))
    assert ("mirror", r, "work/xapk") in ws.plan(r, entries, options=["--viewer"])
    write(os.path.join(r, "apk/game.xapk"))
    v = ws.plan(r, entries, options=["--viewer"])
    assert ("file", r, "apk/game.xapk") in v and ("mirror", r, "work/xapk") not in v
    q = rels(ws.plan(r, entries, quick=True))
    assert "work/lib.so" not in q and "build-win/port/soa.exe" in q


def test_stale_entry_fails(fake, tmp_path):
    r, _ = fake
    lst = str(tmp_path / "list2")
    write(lst, "port/gone.txt   # not there\n")
    with pytest.raises(ValueError):
        ws.plan(r, ws.parse(lst))
    write(lst, "port/CMakeLists.txt\n")  # (no why)
    with pytest.raises(ValueError):
        ws.parse(lst)


def test_extras_and_prune(fake, tmp_path):
    r, entries = fake
    dest = str(tmp_path / "stage")
    keep = ["port/CMakeLists.txt", "data/a.sqlite3", "work/lib.so", "work/phone/data/f", "work/phone/files.txt",
            "build-win/port/soa.exe", "build-win/port/soa.5f00-1a2b.exe", "run/soadrive/x/server.sqlite3", "apk/g.xapk"]
    drop = [".claude/worktrees/other/port/CMakeLists.txt", "work/extra.zip", "docs/x.md", "README.md", "port/src/a.cpp",
            "data/untracked.sqlite3", "data/a.sqlite3:Zone.Identifier", "build-win/tools/other.exe",
            "build-win/tools/other.5f00-1a2b.exe", "build/port/soa"]
    for p in keep + drop:
        write(os.path.join(dest, p))
    assert ws.extras(dest, entries, r) == sorted(drop)
    assert ws.prune(dest, entries, r, dry=True) == sorted(drop) and os.path.exists(os.path.join(dest, "README.md"))
    assert ws.prune(dest, entries, r) == sorted(drop)
    assert ws.extras(dest, entries, r) == []
    for p in keep:
        assert os.path.exists(os.path.join(dest, p)), p
    assert not os.path.exists(os.path.join(dest, ".claude")) and not os.path.exists(os.path.join(dest, "docs"))


def test_the_real_list():
    """scripts/windows-stage.list parses, every tracked entry exists, and the plan stays inside it."""
    entries = ws.parse()
    items = ws.plan(REPO, entries, warn=lambda m: None)
    for kind, root, rel in items:
        assert not rel.startswith((".claude/", "build/", ".git/", "docs/")), rel
        assert any(e.matches(rel) or e.matches(rel + "/") for e in entries), rel
    # the programs' checkout markers are on it (port/src/core/paths.cpp, server/app/main.cpp,
    # emulator/src/main.cpp, emulator-viewer/src/main.cpp is_repo)
    names = {e.path for e in entries}
    for m in ["port/CMakeLists.txt", "server/CMakeLists.txt", "emulator/CMakeLists.txt", "emulator-viewer/CMakeLists.txt",
              "runtime/CMakeLists.txt"]:
        assert m in names, m


def test_dry_run_writes_nothing(tmp_path):
    dest = str(tmp_path / "stage")
    write(os.path.join(dest, ".claude/worktrees/x/README.md"))
    write(os.path.join(dest, "work/extra.zip"))
    out = subprocess.run(["bash", os.path.join(REPO, "scripts/windows-stage.sh"), "--dry-run", dest], capture_output=True,
                         text=True, cwd=REPO)
    assert out.returncode == 0, out.stderr
    removed = out.stdout.split("== would remove from", 1)[1].splitlines()[1:]
    assert ".claude/worktrees/x/README.md" in removed and "work/extra.zip" in removed
    assert os.path.exists(os.path.join(dest, "work/extra.zip"))  # (nothing removed)
    staged = [line.split(" -> ", 1)[1] for line in out.stdout.split("== would remove from", 1)[0].splitlines() if " -> " in line]
    assert staged and not [p for p in staged if p.startswith((".claude/", "build/", ".git/"))]
