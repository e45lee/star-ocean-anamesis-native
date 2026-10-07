"""The server's derived English (server/src/master/english_derive.cpp, docs/server-rules.md#english-derive)
against tools/english_text.py: the full master and story tables `soa-server --english-dump` builds
from Global's master, the JP master, the font and the story files plus our own rows must equal, byte
for byte, the tables the Python build makes. Needs build/server/soa-server and the 3.7.0
download (work/SOA-3.7.0-canonical-data.zip, read in place; local data); skipped without them."""
import pathlib
import re
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))

import english_text as T  # noqa: E402

SERVER = ROOT / "build/server/soa-server"
DOWNLOAD = ROOT / "work/SOA-3.7.0-canonical-data.zip"


def test_story_budget_is_the_tools():
    h = (ROOT / "server/src/master/english_derive.h").read_text(encoding="utf-8")
    assert int(re.search(r"kStoryBudget = (\d+);", h).group(1)) == T.STORY_BUDGET
    assert int(re.search(r"kStoryLines = (\d+);", h).group(1)) == T.STORY_LINES


@pytest.mark.skipif(not SERVER.exists() or not DOWNLOAD.exists(), reason="needs build/server/soa-server and the 3.7.0 download")
def test_server_derivation_equals_the_tools(tmp_path):
    # the reference: `tools/english_text.py derive` (master-en-full.tsv, story-en-full/), from the
    # committed data/english (our rows only)
    ref = tmp_path / "ref"
    T.derive(T.Ctx(), ref)
    out = tmp_path / "out"
    p = subprocess.run([str(SERVER), "--download-dir", str(DOWNLOAD), "--english-dump", str(out)], capture_output=True, text=True,
                       timeout=600)
    assert p.returncode == 0, p.stderr
    assert (out / "master-en.tsv").read_text(encoding="utf-8") == (ref / "master-en-full.tsv").read_text(encoding="utf-8")
    want = {f.stem: f.read_text(encoding="utf-8") for f in (ref / "story-en-full").glob("TS_*.tsv")}
    got = {f.stem: f.read_text(encoding="utf-8") for f in (out / "story-en").glob("TS_*.tsv")}
    assert sorted(got) == sorted(want)
    for stem, text in want.items():
        assert got[stem] == text, stem
