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


def test_set_refuses_an_ambiguous_type(tmp_path, capsys):
    """set without --type on 4 bytes that read as a 3-character string: a u32 too, so it asks."""
    import pytest
    from soa_save.__main__ import main
    path = tmp_path / "Game.xml"
    KVSFile({"role": (0x434241).to_bytes(4, "little"), "name": b"Coro\0"}).save(path)
    with pytest.raises(SystemExit):
        main(["set", str(path), "role", "12345"])
    assert "pass --type" in capsys.readouterr().err
    main(["set", str(path), "role", "12345", "--type", "u32"])
    main(["set", str(path), "name", "Clive"])
    k = KVSFile.load(path)
    assert k.get_u32("role") == 12345 and k.get_str("name") == "Clive"
