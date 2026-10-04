import json
import pathlib
import subprocess
import sys

import pytest

from soa_save.kvs import KVSFile

ROOT = pathlib.Path(__file__).resolve().parent.parent
# The committed, sanitized saves (data/saves/README.md): the seed player and the client save.
SAVES = ROOT / "data/saves"
SAMPLES = sorted(SAVES.glob("*/*.xml"))
SEED = "data/saves/seed/Game.xml"


@pytest.mark.parametrize("path", SAMPLES, ids=lambda p: p.name)
def test_roundtrip_bytes(path):
    assert KVSFile.load(path).dumps() == path.read_text(encoding="utf-8")


def test_known_values():
    aska = KVSFile.load(ROOT / "data/saves/client/Aska.xml")
    assert aska.get_str("version") == "1.1"
    assert aska.get_str("uuid") == "00000000-0000-4000-8000-000000000001"  # sanitized
    game = KVSFile.load(ROOT / SEED)
    assert game.get_str("player_name") == "Fayt"
    assert game.get_str("BAS:PlayerID") == "LOCAL00001"  # sanitized
    assert game.get_u32("person_size") == sum(k.startswith("person_master_role_id_") for k in game.entries)


def test_edit_reload(tmp_path):
    game = KVSFile.load(ROOT / SEED)
    game.set_u32("player_fol", 9_999_999)
    game.set_str("player_name", "Fayt Leingod")
    out = tmp_path / "Game.xml"
    game.save(out)
    again = KVSFile.load(out)
    assert again.get_u32("player_fol") == 9_999_999
    assert again.get_str("player_name") == "Fayt Leingod"
    assert list(again.entries) == list(game.entries)


def test_cli_json_roundtrip(tmp_path):
    run = lambda *a: subprocess.run([sys.executable, "-m", "soa_save", *a], cwd=ROOT, check=True, capture_output=True, text=True).stdout
    js = tmp_path / "g.json"
    js.write_text(run("dump", SEED, "--json"), encoding="utf-8")
    run("load", str(js), str(tmp_path / "Game.xml"))
    assert (tmp_path / "Game.xml").read_text(encoding="utf-8") == (ROOT / SEED).read_text(encoding="utf-8")


def test_master_db_and_roster():
    from soa_save.adld import chash32
    from soa_save.master import Master
    m = Master()
    assert m.db.execute("PRAGMA integrity_check").fetchone()[0] == "ok"
    assert chash32(b"role_cc0050_b01a_6073") == 7715287
    game = KVSFile.load(ROOT / SEED)
    ids = [game.get_u32(f"person_master_role_id_{i}") for i in range(game.get_u32("person_size"))]
    assert all(m.role(r) for r in ids)
    assert m.role(game.get_u32("player_home_pc_roleid"))["label"] == "role_cp0303_b04a_6131"


def test_roster_english_names():
    from soa_save.master import Master
    m = Master()
    game = KVSFile.load(ROOT / SEED)
    ids = [game.get_u32(f"person_master_role_id_{i}") for i in range(game.get_u32("person_size"))]
    assert all(m.role(r)["name_en"] for r in ids)
    assert m.role(game.get_u32("player_home_pc_roleid"))["name_en"] == "Summer Maria"


@pytest.mark.skipif(not sorted((ROOT / "apk").glob("*.xapk")),
                    reason="needs the offline game's package in apk/ (untracked; absent in a worktree)")
def test_unlock_all_keeps_existing(tmp_path):
    from soa_save.roster import roster, unlock_all
    game = KVSFile.load(ROOT / SEED)
    before = roster(game)
    added = unlock_all(game)
    game.save(tmp_path / "Game.xml")
    after = roster(KVSFile.load(tmp_path / "Game.xml"))
    assert after[: len(before)] == before
    assert len(after) == len(before) + len(added) and len(set(after)) == len(after)
