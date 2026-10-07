"""Event script decoding (soa_save.script). The pack tests need the XAPK in apk/ (README "Game files")."""  # 380-ok: soa_save reads the offline XAPK
import pytest

from soa_save import paths
from soa_save.adld import decode
from soa_save.script import COMMANDS, asset_name, encrypt, listing, load, pack_files, texts_from


def test_asset_name():
    assert asset_name("x/assets/assetpack/Script/1000_010.msgp") == "Script/1000_010.msgp"
    assert asset_name("out/Scenario/TS_1000.msgp") == "Scenario/TS_1000.msgp"
    assert asset_name("a/builtin_data/Parameter/Home3D/x.msgp") == "Parameter/Home3D/x.msgp"
    with pytest.raises(ValueError):
        asset_name("1000_010.msgp")


def test_encrypt_roundtrip():
    plain = b"\x81\xa6Script\x80"
    assert decode(encrypt(plain, "Script/x.msgp"), "Script/x.msgp") == plain


def test_command_table():
    assert len(COMMANDS) == 78
    assert COMMANDS[23] == "MessageChange" and COMMANDS[77] == "SetEnableFastForwardButton"


@pytest.fixture(scope="module")
def pack():
    try:
        paths.xapk()  # 380-ok
    except FileNotFoundError:
        pytest.skip("no XAPK")  # 380-ok
    return list(pack_files())


def test_pack_decodes(pack):
    scripts = [(n, d) for n, d in pack if n.startswith("Script/")]
    assert len(scripts) == 458 and len(pack) == 486
    for name, data in pack:
        # every file re-encrypts to the identical bytes, so edited files can go back in the pack
        assert encrypt(decode(data, name), name) == data, name
        obj = load(data, name)
        assert set(obj) in ({"Script"}, {"master_text"}), name
    texts = texts_from((n, d) for n, d in pack if n.startswith("Scenario/"))
    out = listing(load(dict(scripts)["Script/1000_010.msgp"], "Script/1000_010.msgp"), texts)
    assert "MessageChange" in out and "コロ/Coro" in out and "３番ポッド射出" in out


def test_speaker_names():
    from soa_save.script import SPEAKER_DBS, speaker
    assert speaker(None) is None and speaker("<player>") == "<player>"
    assert speaker("cp0013_ta01a") == "cp0013_ta01a ユーイン/Yrian"  # names_en.json adds the English name
    if not any(p.exists() for p in SPEAKER_DBS):
        pytest.skip("no master DB in data/ (README \"Game files\")")
    assert speaker("cp0024_ta01a") == "cp0024_ta01a ケビン"  # an NPC: the game's nameplate (master_text)
    assert speaker("cp0006_ta51a") == "cp0006_ta51a ３人組"  # per full code, not per character
    assert speaker("cp0006_ta01b") == "cp0006_ta01b ヴァル"  # a variant without its own row: its base
