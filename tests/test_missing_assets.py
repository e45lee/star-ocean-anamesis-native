"""tools/missing_assets/ on small fixtures: the path rules, the presence index and the AIF header
reader on a tiny synthetic tree, the guesser, the name resolution order and the renderer. The last
test regenerates the real documents and needs the 3.7.0 download (skipped without work/)."""
import pathlib
import sqlite3
import struct
import subprocess
import sys
import zipfile

import pytest

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))
from missing_assets import rules  # noqa: E402
from missing_assets.guess import Guesser, name_pattern  # noqa: E402
from missing_assets.model import ContentGroup, ContentItem, ContentKind  # noqa: E402
from missing_assets.names import Names  # noqa: E402
from missing_assets.presence import Presence, Source, image_info, logical_name  # noqa: E402
from missing_assets.render import merge_bg, missing_paths_text, render_document  # noqa: E402
from soa_save.adld import chash32  # noqa: E402


# ---------------------------------------------------------------- fixtures
def aif(width, height, fmt=49):
    """A minimal decoded AIF: an `Xgmi` image header at offset 16."""
    hdr = bytearray(0x40)
    hdr[0:4] = b"Xgmi"
    hdr[0x20] = fmt
    struct.pack_into("<HH", hdr, 0x28, width, height)
    return bytes(16) + bytes(hdr) + bytes(16)


def adld_xor(stored_name, plain):
    key = b"%x" % chash32(stored_name.encode())
    return b"ADLD" + struct.pack("<I", 1) + bytes(8) + bytes(b ^ key[i % len(key)] for i, b in enumerate(plain))


def slz_stored(plain):
    """An SLZ container with codec 0 (stored)."""
    hdr = bytearray(0x20)
    hdr[0:3] = b"SLZ"
    hdr[3] = 0
    struct.pack_into("<i", hdr, 0xc, len(plain))
    struct.pack_into("<I", hdr, 0x14, len(hdr))
    return bytes(hdr) + plain


@pytest.fixture
def tree(tmp_path):
    """A download-like tree (an ADLD-XOR image, an SLZ image, a map, a zero-size file) and a zip."""
    d = tmp_path / "download"
    (d / "Image" / "etc2").mkdir(parents=True)
    (d / "BG").mkdir()
    (d / "Image/etc2/bn_0001.aif").write_bytes(adld_xor("Image/etc2/bn_0001.aif", aif(512, 128)))
    (d / "Image/etc2/bn_0003.aif").write_bytes(slz_stored(aif(512, 128)))
    (d / "Image/etc2/bbg01_1_1.aif").write_bytes(aif(256, 256, 39))
    (d / "BG/bc01_01.asf").write_bytes(b"x")
    (d / "Image/etc2/empty.aif").write_bytes(b"")
    apk = tmp_path / "game.apk"
    with zipfile.ZipFile(apk, "w") as z:
        z.writestr("assets/builtin_data/Image/etc2/hi/apk_only.aif", aif(64, 64))
        z.writestr("assets/builtin_data/BG/bc01_01.aaf", b"y")
    standins = tmp_path / "standin"
    (standins / "Image").mkdir(parents=True)
    (standins / "Image/bn_0002.aif").write_bytes(aif(1, 1))
    return Presence([Source("download", str(d)), Source("APK 3.7.0", str(apk)), Source("stand-in", str(standins))])


# ---------------------------------------------------------------- path rules
def test_path_rules():
    assert rules.IMAGE.path("bn_0001") == "Image/bn_0001.aif"
    assert rules.SCRIPT.path("ev01") == "Script/ev01.msgp" and rules.SCENARIO.path("ev01") == "Scenario/ev01.msgp"
    assert rules.BGM.path("bgm1") == "Sound/bgm1.aac" and rules.SOUND_PACK.path("v1") == "Sound/v1.spk"
    assert rules.map_files("bc01_01") == [("asf", "BG/bc01_01.asf"), ("aaf", "BG/bc01_01.aaf"),
                                          ("acf", "BG/bc01_01.acf")]
    assert [r.path("x") for _, r, _, _ in rules.PERSON_RESOURCES] == [
        "Character/x.asf", "Character/x.acf", "Motion/x.apk", "Character/x.apk"]
    for rule in (rules.IMAGE, rules.SCRIPT, rules.BGM, rules.CHARACTER_MODEL, rules.UNIVERSE_CHIP):
        assert rule.label in ("a", "b", "d") and rule.reason
    assert rules.display_path("Image/x.aif") == "Image/etc2/x.aif"
    assert rules.display_path("BG/x.asf") == "BG/x.asf"


def test_standin_verdicts():
    v = rules.standin_verdict
    assert v("Image/x.aif") == "yes (2D image)"
    assert v("Sound/x.aac") == "yes (any BGM)"
    assert v("Sound/x.spk") == "partly (cue ids)"
    assert v("Script/x.msgp") == "partly (end scene)"
    assert v("Scenario/x.msgp") == "partly (text)"
    assert v("BG/x.asf") == v("Character/x.asf") == "no (3D)"


# ---------------------------------------------------------------- presence
def test_logical_names():
    assert logical_name("assets/builtin_data/Image/etc2/hi/x.aif") == "Image/x.aif"
    assert logical_name("foo/assetpack/Sound/x.aac") == "Sound/x.aac"
    assert logical_name("Image\\etc2\\x.aif") == "Image/x.aif"


def test_presence(tree):
    assert tree.where("Image/bn_0001.aif") == "download"
    assert tree.where("BG/bc01_01.asf") == "download"
    assert tree.where("BG/bc01_01.aaf") == "APK 3.7.0"
    assert tree.where("Image/apk_only.aif") == "APK 3.7.0"
    assert tree.where("Image/bn_0002.aif") == "stand-in"
    assert tree.where("Image/empty.aif") is None  # zero-size files don't count
    assert tree.where("Image/nothing.aif") is None
    assert [s.label for s in tree.real_sources()] == ["download", "APK 3.7.0"]


def test_image_info(tree):
    download, apk = tree.sources[0], tree.sources[1]
    info = image_info(download, "Image/bn_0001.aif")  # ADLD-XOR with the stored name's key
    assert (info.width, info.height, info.format) == (512, 128, "ETC2 RGBA")
    assert image_info(download, "Image/bn_0003.aif").width == 512  # SLZ, stored
    assert image_info(download, "Image/bbg01_1_1.aif").format == "JPEG"
    assert image_info(apk, "Image/apk_only.aif").height == 64
    assert image_info(download, "BG/bc01_01.asf") is None
    assert image_info(download, "Image/missing.aif") is None


# ---------------------------------------------------------------- guesser
def gacha_item(picks=()):
    o = ContentItem("gacha", "bn_g", "bn_g", "ガチャ", "Some Gacha", "gl", "2018-01-01", "2018-02-01", "1 gacha row(s)")
    o.picks = list(picks)
    return o


def test_guess_from_siblings(tree):
    g = Guesser(tree)
    o = gacha_item(["★4 A (Alpha)"])
    o.add("Image/bn_0002.aif", "gacha list banner", "master_banner.image", "bn_g", "subj")
    guess = g.guess(o, o.refs["Image/bn_0002.aif"])
    assert guess.text == 'list banner for the gacha "Some Gacha", featuring ★4 A (Alpha); 512×128 ETC2 RGBA'
    assert guess.confidence == "high"  # the stand-in bn_0002 is no evidence; both siblings agree
    assert guess.evidence == "2 existing `bn_#` (e.g. `bn_0001`: 512×128)"
    assert name_pattern("bn_0002_a1") == "bn_#_a#"


def test_guess_letter_family_and_no_siblings(tree):
    g = Guesser(tree)
    o = gacha_item()
    o.add("Image/bbc01_2_3.aif", "boss icon", "master_mission_stage.boss_icon", "st1", "Boss")
    guess = g.guess(o, o.refs["Image/bbc01_2_3.aif"])
    assert guess.text == "boss icon (Boss); 256×256 JPEG" and guess.confidence == "medium"
    assert guess.evidence.startswith("1 existing `*#_#_#`")
    o.add("Image/zz.aif", "event list banner", "master_event_area.bg_resource", "ev", "x")
    guess = g.guess(o, o.refs["Image/zz.aif"])
    assert guess.confidence == "medium" and guess.evidence == "no existing `zz` file"


def test_guess_panels_and_maps(tree):
    g = Guesser(tree)
    o = gacha_item(["P1", "P2"])
    o.add("Image/q.aif", "pick-up panel 2 (HTML-era gacha screen)", "master_gacha.image2", "g1", "s", 2)
    assert g.guess(o, o.refs["Image/q.aif"]).text.startswith('pick-up panel 2 of "Some Gacha", probably P2')
    for ext, path in rules.map_files("bc09_01"):
        o.add(path, f"battle map (.{ext})", "master_mission_stage.master_map_id", "st_1", "M", 3)
        o.add(path, f"battle map (.{ext})", "master_mission_stage.master_map_id", "st_2", "M", 3)
    guess = g.guess(o, o.refs["BG/bc09_01.asf"])
    assert guess.text == "3D battle map `bc09_01` for stage(s) st_1, st_2" and guess.evidence == ""


# ---------------------------------------------------------------- names
@pytest.fixture
def names(tmp_path):
    master = sqlite3.connect(":memory:")
    master.execute("create table master_text (message_id text, text_value text)")
    master.execute("create table master_person (id_label text, name_message_id text)")
    master.executemany("insert into master_text values (?, ?)", [
        ("m_tsv", "限定ガチャ"), ("m_gl", "テスト"), ("m_gltext", "同じ文"), ("m_same", "Plain"),
        ("m_gloss", "イヴリーシュピックアップガチャ"), ("m_left", "謎の箱"), ("m_old", "新しい文"),
        ("p_eve", "イヴリーシュ")])
    master.execute("insert into master_person values ('cp0002_b01a', 'p_eve')")
    gl = tmp_path / "gl.sqlite3"
    g = sqlite3.connect(gl)
    g.execute("create table master_text (message_id text, text_value text, lang text)")
    g.executemany("insert into master_text values (?, ?, ?)", [
        ("m_tsv", "限定ガチャ", "ja"), ("m_tsv", "GL Limited", "en"),
        ("m_gl", "テスト", "ja"), ("m_gl", "GL Test", "en"),
        ("x_other", "同じ文", "ja"), ("x_other", "Same Text", "en"),
        ("m_old", "古い文", "ja"), ("m_old", "Old Text", "en")])
    g.commit()
    tsv = tmp_path / "names.tsv"
    tsv.write_text("# comment\n限定ガチャ\tTSV Limited\n@event_x\tLabel Name\n", encoding="utf-8")
    return Names(master, str(gl), str(tsv))


def test_name_resolution_order(names):
    assert names.english("m_tsv") == ("TSV Limited", "tsv")      # 1. the TSV beats the Global master
    assert names.english("m_gl") == ("GL Test", "gl")            # 2. Global by message id
    assert names.english("m_gltext") == ("Same Text", "gl")      # 2. Global by identical text
    assert names.english("m_old") == ("New しい文 (tr.)", "glossary")  # Global text differs: not by id
    assert names.english("m_same") == ("Plain", "same")          # 3. no kana / kanji
    assert names.english("m_gloss") == ("EvelyssePick-up Gacha", "glossary")  # 4. people, then phrases
    assert names.english("m_left")[0].endswith("(tr.)") and names.residue["謎の箱"] == 1
    assert names.english(None, "") == ("", "none")
    assert names.official("m_gloss") is None and names.official("m_gl") == "GL Test"
    assert names.tsv["@event_x"] == "Label Name"


def test_person_names(names):
    assert names.person("p_eve") == ("イヴリーシュ", "Evelysse")   # names_en.json by the label's code
    assert names.people["イヴリーシュ"] == "Evelysse"


# ---------------------------------------------------------------- renderer
def test_merge_bg():
    o = ContentItem("event", 1, "ev", "", "", "none", "", "", "")
    for _, path in rules.map_files("bc01_01"):
        o.add(path, "battle map", "c", "r")
    o.add("Image/a.aif", "boss icon", "c", "r")
    rows = merge_bg(list(o.refs.values()))
    assert [(d, p) for d, _, p in rows] == [
        ("BG/bc01_01.asf/.aaf/.acf", ["BG/bc01_01.asf", "BG/bc01_01.aaf", "BG/bc01_01.acf"]),
        ("Image/etc2/a.aif", ["Image/a.aif"])]


def test_render_tiny_model(tree):
    ev = ContentItem("event", 7, "event_x", "イベント", "The Event", "gl", "2017-05-01 12:00", "2017-05-10", "1 term(s)")
    ev.add("Image/ev_banner.aif", "event banner", "master_banner.image", "bn_ev", "The Event")
    ev.add("Image/bn_0001.aif", "event list banner", "master_event_area.bg_resource", "event_x", "The Event")
    for ext, path in rules.map_files("bc01_01"):
        ev.add(path, f"battle map (.{ext})", "master_mission_stage.master_map_id", "st_1", "M", 3)
    ga = gacha_item(["P1"])
    ga.add("Image/bn_0002.aif", "gacha list banner", "master_banner.image", "bn_g", "s")  # stand-in only
    ga.add("Image/panel.aif", "main panel (view 0)", "master_gacha_image.image_resource", "g_1", "s", 10)
    row = ContentItem("character", 1, "role_x", "★5 X", "", "none", "", "", "")
    row.add("Character/cx.asf", "character model", "master_person.asf", "cp_x", "", 1)
    row.gate.add("Character/cx.asf")
    kinds = [ContentKind("Characters", "Roles.", [ContentGroup("キャラ", "Characters", "tsv", "master_role", [row])])]
    doc = render_document(tree, Guesser(tree), [ev], [ga], [], kinds)
    md = doc.text()
    assert "### イベント — The Event *GL*" in md
    assert "`event_x` (id 7) · 2017-05-01 12:00 → 2017-05-10 · 1 term(s) · 2 missing of 5 files" in md
    assert "| `Image/etc2/ev_banner.aif` | event banner | `master_banner.image`: `bn_ev` |" in md
    events_part = md.split("## Events")[1].split("## Gacha")[0]
    assert "| `BG/bc01_01.acf` | battle map (.acf) |" in events_part  # .asf (download) and .aaf (APK) present
    assert "bc01_01.asf" not in events_part
    assert "| Characters | 1 | 0 | 1 | Character 1 |" in md
    assert "Stand-ins (made-up, `standin-assets/`): `Image/etc2/bn_0002.aif` (gacha list banner)" in md
    assert "1 missing of 2 files, 1 stand-in" in md
    assert doc.events_missing == [ev] and doc.gachas_missing == [ga]
    assert missing_paths_text(doc.status) == "BG/bc01_01.acf\nCharacter/cx.asf\nImage/ev_banner.aif\nImage/panel.aif\n"


# ---------------------------------------------------------------- the real documents
REAL_INPUTS = [ROOT / "work/download-3.7.0", ROOT / "data/basmaster-3.7.0.sqlite3",
               ROOT / "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk"]


@pytest.mark.skipif(not all(p.exists() for p in REAL_INPUTS), reason="needs the 3.7.0 download (work/)")
def test_documents_current(tmp_path):
    """The committed documents are what the generator writes now."""
    md, txt = tmp_path / "out.md", tmp_path / "out.txt"
    subprocess.run([sys.executable, str(ROOT / "tools/missing_assets.py"), "--md", str(md), "--txt", str(txt)],
                   check=True, capture_output=True)
    assert md.read_bytes() == (ROOT / "docs/missing-assets-3.7.0.md").read_bytes()
    assert txt.read_bytes() == (ROOT / "docs/missing-assets-3.7.0.txt").read_bytes()
