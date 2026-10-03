"""Checks for the committed client save data/saves/client/Game.xml (every character; sanitized)."""
import pathlib

from soa_save.kvs import KVSFile
from soa_save.roster import roster

SAVES = pathlib.Path(__file__).resolve().parent.parent / "data/saves/client"


def test_all_characters_save():
    path = SAVES / "Game.xml"
    game = KVSFile.load(path)
    assert game.dumps() == path.read_text(encoding="utf-8")
    assert game.get_str("BAS:PlayerID") == "AAAAAAAAAA"
    ids = roster(game)
    assert len(ids) == len(set(ids)) == 276
