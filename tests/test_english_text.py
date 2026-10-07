"""tools/english_text.py and tools/english_core.py: the English table's build, checks, E3 token
rewrites, the MT import and the edit round trips (docs/english.md 7.5, 7.6; PLAN-english.md E1/M1/E3).
Runs on the committed master DBs and the font of the committed APK; nothing from work/."""
import json
import pathlib
import shutil
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))

import english_core as C  # noqa: E402
import english_text as T  # noqa: E402


@pytest.fixture(scope="module")
def built():
    return T.build(T.Ctx())


@pytest.fixture(scope="module")
def font():
    return C.Font()


@pytest.fixture
def data(tmp_path):
    """A scratch data/english with the committed glossary and client strings, an empty table."""
    d = tmp_path / "data"
    d.mkdir()
    for n in ("glossary.tsv", "client-strings.tsv"):
        shutil.copy(T.DATA / n, d / n)
    (d / "master.tsv").write_text(T.tsv_text(T.TABLE_COLS, []), encoding="utf-8")
    return d


def run(data, *args):
    return T.main(["--data", str(data), "--work", str(data.parent / "work"), *args])


def table(data):
    return {r["message_id"]: r for r in T.read_tsv(data / "master.tsv", T.TABLE_COLS)}


# ---------------------------------------------------------------- the committed files

def test_master_en_is_fresh(built):
    """data/english/master-en.tsv and glossary.tsv are what `build` writes (run it after a change)."""
    assert (T.DATA / "master-en.tsv").read_text(encoding="utf-8") == built.master_en
    assert (T.DATA / "glossary.tsv").read_text(encoding="utf-8") == built.glossary_text


def test_two_builds_byte_identical(built):
    again = T.build(T.Ctx())
    assert again.master_en == built.master_en
    assert again.glossary_text == built.glossary_text


def test_counts_reproduce_english_md(built):
    """english.md 7.1: 19,145 official by id, 6,265 exact memory, 2,412 template; plus E3's rows."""
    assert built.candidates["official"] == 19145
    assert built.candidates["exact"] == 6265
    assert built.candidates["template"] == 2412
    assert built.candidates["official_e3"] == len(built.e3) > 0
    assert built.served["official"] == 19145 + len(built.e3) - sum(
        1 for f in built.failures if f["source"] == "official") - len(built.overrides)
    assert len(built.q7) == 803
    assert sum(1 for r in built.glossary_rows if r["source"] == "official" and r["variants"]) == 302


def test_served_rows_are_clean(built, font):
    src = T.Ctx().src
    for mid, (h, en, source) in built.out.items():
        assert source in T.C_SOURCES
        assert not C.GL_MARKUP.search(en), mid
        assert not C.has_kana(en), mid
        assert not font.missing(C.unesc(en)), mid
        if mid in src.jp_rows:
            assert h == C.sha1(src.jp_rows[mid])
            assert C.SPEC.findall(en) == C.SPEC.findall(src.jp_rows[mid]), mid


def test_master_en_format():
    lines = (T.DATA / "master-en.tsv").read_text(encoding="utf-8").split("\n")
    assert lines[0] == "message_id\tja_sha1\ten\tsource"
    assert lines[-1] == ""
    ids = [x.split("\t")[0] for x in lines[1:-1]]
    assert ids == sorted(ids, key=lambda m: m.encode())
    assert all(len(x.split("\t")) == 4 for x in lines[1:-1])


# ---------------------------------------------------------------- the font

def test_font_from_apk(font):
    """fontData.bin of Font/etc2/font.fpk (english.md 3.1): 7,133 glyphs, proportional ASCII."""
    assert len(C.read_font_glyphs()) == 7133
    assert font.adv[ord("i")] == 7 and font.adv[ord("m")] == 26 and font.adv[ord(" ")] == 12
    assert font.adv[ord("あ")] == 24
    assert ord("é") not in font.adv and ord("—") not in font.adv and ord("―") in font.adv


def test_fold(font):
    assert font.fold("Café — “déjà vu”") == 'Cafe ― "deja vu"'


# ---------------------------------------------------------------- checks (english.md 7.5)

def test_checks(font):
    ok = C.check("%d個入手", "Got %d", font)
    assert ok == {}
    assert "specifiers" in C.check("%d個入手", "Got some", font)            # dropped %d
    assert "specifiers" in C.check("入手しました", "Got %d", font)          # invented %d
    assert "specifiers" in C.check("%d％アップ", "%d% up", font)            # bare % in a printf row
    assert C.check("%d％アップ", "%d%% up", font) == {}
    assert "positional" in C.check("%s %d", "%2$d %1$s", font)
    assert "tags" in C.check("<player>、ありがとう", "Thank you", font)      # missing tag
    assert "kana" in C.check("ありがとう", "Thank you ありがとう", font)     # kana left
    assert "glyphs" in C.check("カフェ", "Café", font)                       # missing glyph (not folded)
    assert "global_token" in C.check("あ", "a<EMDASH>b", font)


def test_tags_subset_for_labels(font):
    ja = "<font color=green>スライド</font>で<font color=green>移動</font>"
    assert C.check(ja, "<font color=green>Slide</font> to move", font, tags="subset") == {}
    assert "tags" in C.check(ja, "<font color=green>Slide</font> to move", font)
    assert "tags" in C.check(ja, "<font color=red>Slide</font> to move", font, tags="subset")
    assert "tags" in C.check(ja, "<font color=green>Slide to move", font, tags="subset")


def test_glossary_check(font):
    g = {"紋章石": {"en": "Gems", "variants": ["Gem"], "kind": "ui", "source": "official"}}
    assert C.check("紋章石が不足", "Not enough Gems.", font, g) == {}
    assert C.check("紋章石が不足", "Not enough gem.", font, g) == {}
    assert C.check("紋章石が不足", "Not enough crests.", font, g)["glossary"] == [["紋章石", "Gems"]]


# ---------------------------------------------------------------- E3

def test_e3_rewrites():
    r = C.rewrite_tokens
    assert r("Tries Left: <NUM 1>", "あと%d回！") == ("Tries Left: %d", None)
    assert r("Until: <NUM 1>:<NUM 2>", "%d：%02dまで") == ("Until: %d:%02d", None)  # JP's spelling
    assert r("Clear rate: <NUM 1>%", "クリア率:%d%%") == ("Clear rate: %d%%", None)
    assert r("<NUM 1>/<NUM 2> <INSERT 1>player/players</INSERT>", "%d/%d人") == ("%d/%d players", None)
    assert r("Lobby ID: <STR 1>", "ルームID：%s") == ("Lobby ID: %s", None)
    en, why = r("Day <NUM 2> <STR 1>", "%s %d日目")
    assert en is None and "reorder" in why
    en, why = r("Block <STR 1>?", "をブロックします。")
    assert en is None and "composition" in why
    # a story line (real newlines, tags kept)
    assert r("<player>, wait<EMDASH>\nplease!", "<player>、待って――\nお願い！") == ("<player>, wait―\nplease!", None)


def test_e3_story_ep1(built):
    """english.md 7.1: E3 turns 117 EP1 story lines official (needs the download's Scenario files)."""
    ctx = T.Ctx()
    s = T.build_story(ctx, built.glossary)
    if s is None:
        pytest.skip("no Scenario files (work/SOA-3.7.0-canonical-data.zip)")
    d = s.derived
    ep1 = [m for m, ln in d.lines.items() if C.story_group(ln[0]) == "EP1" and C.has_kana(ln[1])]
    assert sum(1 for m in ep1 if d.lines[m][3] == "official_e3") == 117
    assert sum(1 for m in ep1 if d.lines[m][3] == "official") == 2979
    # 10 EP1 lines have no official English (the table's machine rows may fill them)
    assert sum(1 for m in ep1 if d.lines[m][3] not in ("official", "official_e3")) == 10


def test_story_en_is_fresh(built):
    """data/english/story-en/ is what `build` writes (only checkable with the Scenario files)."""
    ctx = T.Ctx()
    s = T.build_story(ctx, built.glossary)
    if s is None:
        pytest.skip("no Scenario files (work/SOA-3.7.0-canonical-data.zip)")
    outs = T.story_outputs(ctx, s)
    for p, text in outs.items():
        assert p.read_text(encoding="utf-8") == text, p
    assert set((T.DATA / "story-en").glob("TS_*.tsv")) == {p for p in outs if p.name != "index.tsv"}


# ---------------------------------------------------------------- the table: MT import, edits, stale

def gap_ids(built, n, pred=lambda ja: True):
    src = T.Ctx().src
    out = [m for m in sorted(built.klass) if built.klass[m] == "gap" and "\\n" not in src.jp_rows[m]
           and not C.SPEC.search(src.jp_rows[m]) and "<" not in src.jp_rows[m] and pred(src.jp_rows[m])]
    return out[:n]


def mt_line(src, ids, mt, model="gemma-4-31b-it", prompt="v2"):
    ja = src.jp_rows[ids[0]]
    return json.dumps({"ja_sha1": C.sha1(ja), "ja": ja, "mt": mt, "kind": "ui", "ids": ids, "model": model,
                       "quant": "UD-Q4_K_XL", "prompt": prompt, "llama_build": "b11443", "temperature": 0,
                       "slots": 4, "date": "2026-10-08"}, ensure_ascii=False)


def test_human_row_survives_mt_reimport(built, data, tmp_path):
    src = T.Ctx().src
    a, b = gap_ids(built, 2, lambda ja: not C.glossary_hits(ja, built.glossary))
    assert run(data, "--no-build", "set", a, "Human words", "--by", "tester", "--date", "2026-10-08") == 0
    ck = tmp_path / "ck.jsonl"
    ck.write_text(mt_line(src, [a], "Machine words a") + "\n" + mt_line(src, [b], "Machine words b") + "\n")
    assert run(data, "import-mt", str(ck)) == 0
    t = table(data)
    assert t[a]["source"] == "human" and t[a]["en"] == "Human words"
    assert t[b]["source"] == "machine" and t[b]["en"] == "Machine words b"
    assert t[b]["engine"] == "gemma-4-31b-it/UD-Q4_K_XL/v2/llama.cpp-b11443/t0"
    # a re-run with another prompt: kept without --replace, replaced with it; the human row never
    ck.write_text(mt_line(src, [a], "New a", prompt="v3") + "\n" + mt_line(src, [b], "New b", prompt="v3") + "\n")
    run(data, "--no-build", "import-mt", str(ck))
    assert table(data)[b]["en"] == "Machine words b"
    run(data, "import-mt", "--replace", str(ck))
    t = table(data)
    assert t[a]["en"] == "Human words" and t[b]["en"] == "New b" and "/v3/" in t[b]["engine"]
    served = {r["message_id"]: r for r in T.read_tsv(data / "master-en.tsv", T.OUT_COLS)}
    assert served[a]["source"] == "human" and served[b]["source"] == "machine"


def test_mt_import_rejects_failing_rows(built, data, tmp_path, font):
    src = T.Ctx().src
    spec = next(m for m in sorted(built.klass) if built.klass[m] == "gap"
                and C.SPEC.findall(src.jp_rows[m]) == ["%d"] and "<" not in src.jp_rows[m])
    a, = gap_ids(built, 1, lambda ja: not C.glossary_hits(ja, built.glossary))
    ck = tmp_path / "ck.jsonl"
    ck.write_text(mt_line(src, [spec], "No number here") + "\n" + mt_line(src, [a], "Half 日本語") + "\n")
    run(data, "import-mt", str(ck))
    assert table(data) == {}
    rej = {r["message_id"]: json.loads(r["problems"]) for r in T.read_tsv(data.parent / "work/mt-rejected.tsv", T.REJECT_COLS)}
    assert "specifiers" in rej[spec] and "kana" in rej[a]


def test_mt_post_processing(built, data, tmp_path):
    """NFC, glyph folding and the %% rule are applied at import."""
    src = T.Ctx().src
    spec = next(m for m in sorted(built.klass) if built.klass[m] == "gap" and "\\n" not in src.jp_rows[m]
                and C.SPEC.findall(src.jp_rows[m]) == ["%d"] and "<" not in src.jp_rows[m]
                and not C.glossary_hits(src.jp_rows[m], built.glossary))
    ck = tmp_path / "ck.jsonl"
    ck.write_text(mt_line(src, [spec], "Café — %d% more") + "\n")
    run(data, "--no-build", "import-mt", str(ck))
    assert table(data)[spec]["en"] == "Cafe ― %d%% more"


def test_changed_hash_is_stale(data, built, capsys):
    a, = gap_ids(built, 1)
    rows = [{"message_id": a, "ja_sha1": "0" * 40, "en": "Old text", "source": "human", "engine": "",
             "date": "2026-10-08", "editor": "tester", "note": ""}]
    (data / "master.tsv").write_text(T.tsv_text(T.TABLE_COLS, rows), encoding="utf-8")
    b = T.build(T.Ctx(data=data))
    assert [s[0] for s in b.stale] == [a] and a not in b.out
    assert run(data, "stale", "--fail") == 1
    assert a in capsys.readouterr().out


def test_human_row_with_problems_is_refused(data, built):
    a, = gap_ids(built, 1)
    assert run(data, "--no-build", "set", a, "まだ日本語", "--by", "tester") == 1
    assert table(data) == {}


def test_failing_human_row_falls_back(data, built):
    """A failing candidate is not served; the next source is (here Global's official English)."""
    src = T.Ctx().src
    mid = next(m for m in sorted(built.out) if built.out[m][2] == "official" and C.SPEC.findall(src.jp_rows[m]) == ["%d"])
    rows = [{"message_id": mid, "ja_sha1": C.sha1(src.jp_rows[mid]), "en": "no number", "source": "human",
             "engine": "", "date": "2026-10-08", "editor": "tester", "note": ""}]
    (data / "master.tsv").write_text(T.tsv_text(T.TABLE_COLS, rows), encoding="utf-8")
    b = T.build(T.Ctx(data=data))
    assert b.out[mid][2] == "official"
    assert any(f["message_id"] == mid and f["source"] == "human" for f in b.failures)


def test_review(data, built, tmp_path):
    src = T.Ctx().src
    a, = gap_ids(built, 1, lambda ja: not C.glossary_hits(ja, built.glossary))
    ck = tmp_path / "ck.jsonl"
    ck.write_text(mt_line(src, [a], "Machine words") + "\n")
    run(data, "--no-build", "import-mt", str(ck))
    assert run(data, "--no-build", "review", a, "--by", "tester", "--date", "2026-10-09") == 0
    t = table(data)[a]
    assert (t["source"], t["editor"], t["en"]) == ("reviewed", "tester", "Machine words")


def test_client_strings_merged(data):
    (data / "client-strings.tsv").write_text(T.tsv_text(T.CLIENT_COLS, [
        {"message_id": "port_en_test_close", "en": "Close", "note": "test"}]), encoding="utf-8")
    b = T.build(T.Ctx(data=data))
    assert b.out["port_en_test_close"] == ("", "Close", "human")


def test_glossary_machine_names(data, built, font):
    """M2's machine name rows are loaded and checked; a human row overrides an official one."""
    rows = [r for r in T.read_tsv(data / "glossary.tsv", T.GLOSSARY_COLS) if r["ja"] != "リーシュ"]
    rows.append({"ja": "リーシュ", "en": "Lishe", "kind": "name", "variants": "", "source": "machine", "note": "M2"})
    rows.append({"ja": "紋章石", "en": "Crests", "kind": "ui", "variants": "", "source": "human", "note": ""})
    (data / "glossary.tsv").write_text(T.tsv_text(T.GLOSSARY_COLS, rows), encoding="utf-8")
    ctx = T.Ctx(data=data)
    g = T.glossary_dict(T.glossary_rows(ctx))
    assert g["リーシュ"]["en"] == "Lishe" and g["リーシュ"]["source"] == "machine"
    assert g["紋章石"]["en"] == "Crests"
    assert "glossary" in C.check("リーシュっ！", "Leesh!", font, g)
    # regeneration keeps the human and machine rows
    regenerated = T.glossary_rows(ctx)
    assert any(r["ja"] == "リーシュ" and r["source"] == "machine" for r in regenerated)
    assert sum(1 for r in regenerated if r["ja"] == "紋章石") == 2


def test_csv_round_trip(data, built, tmp_path):
    import csv
    a, = gap_ids(built, 1, lambda ja: not C.glossary_hits(ja, built.glossary))
    out = tmp_path / "e.csv"
    run(data, "export-csv", "--out", str(out))
    rows = list(csv.DictReader(open(out, encoding="utf-8")))
    for r in rows:
        if r["message_id"] == a:
            r["en"] = "Edited in a sheet"
    with open(out, "w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, T.CSV_COLS)
        w.writeheader()
        w.writerows(rows)
    run(data, "--no-build", "import-csv", str(out), "--by", "sheet")
    t = table(data)
    assert list(t) == [a] and t[a]["en"] == "Edited in a sheet" and t[a]["editor"] == "sheet"


def test_po_round_trip(data, built, tmp_path):
    polib = pytest.importorskip("polib")
    src = T.Ctx().src
    a, b = gap_ids(built, 2, lambda ja: not C.glossary_hits(ja, built.glossary))
    ck = tmp_path / "ck.jsonl"
    ck.write_text(mt_line(src, [b], "Machine words") + "\n")
    run(data, "import-mt", str(ck))
    out = tmp_path / "po"
    run(data, "export-po", "--out", str(out))
    po = polib.pofile(str(out / f"{C.prefix(a)}.po"))
    for e in po:
        if e.msgctxt == a:
            e.msgstr = "Edited in Poedit"
        if e.msgctxt == b:
            assert "fuzzy" in e.flags
            e.flags.remove("fuzzy")
    po.save()
    run(data, "--no-build", "import-po", str(out / f"{C.prefix(a)}.po"), "--by", "poedit")
    t = table(data)
    assert t[a]["source"] == "human" and t[a]["en"] == "Edited in Poedit"
    assert t[b]["source"] == "reviewed" and t[b]["en"] == "Machine words"


# ---------------------------------------------------------------- the story (phase 2)

def emdash_story_id(src):
    for m in sorted(src.gl_ja):
        if m[:4].isdigit() and m[4] == "_" and "<EMDASH>" in (src.gl_en.get(m) or "") \
                and src.gl_token_english(m) and not C.SPEC.search(src.gl_ja[m]) \
                and C.rewrite_tokens(src.gl_en[m], src.gl_ja[m])[0]:
            return m


@pytest.fixture
def scenario(tmp_path):
    """A one-file Scenario dir: Global story lines (official, E3, one where Global names <player>),
    two gap lines and a language-neutral one."""
    import msgpack
    from soa_save import script
    src = T.Ctx().src
    e3 = emdash_story_id(src)
    rows = [(m, C.unesc(src.gl_ja[m])) for m in ("1010_065_49", "1010_030_17", e3)]
    rows += [("9999_t_01", "テストの行です。"), ("9999_t_02", "<player>、待って！"), ("9999_t_03", "……")]
    d = tmp_path / "Scenario"
    d.mkdir()
    plain = msgpack.packb({"master_text": [
        {"message_id": m, "lang": "ja", "text_value": ja, "category_id_label": "TS_1999", "data_type": "package",
         "id": i} for i, (m, ja) in enumerate(rows)]})
    (d / "TS_1999.msgp").write_bytes(script.encrypt(plain, "Scenario/TS_1999.msgp"))
    return d, e3


def srun(data, scen, *args):
    return T.main(["--data", str(data), "--work", str(data.parent / "work"), "--scenario", str(scen), *args])


def story_ck(lines, prompt="v2+s1"):
    return json.dumps({"key": "k", "scene": "1999_010", "kind": "story", "lines": lines, "raw": "", "finish": "stop",
                       "prompt": prompt, "model": "gemma-4-31b-it", "quant": "UD-Q4_K_XL", "llama_build": "b11443",
                       "temperature": 0, "slots": 4, "date": "2026-10-08"}, ensure_ascii=False)


def sline(mid, ja, mt):
    return {"message_id": mid, "file": "TS_1999", "ja_sha1": C.sha1(ja), "ja": ja, "speaker": "Coro", "mt": mt}


def index(data, scen):
    """story-en-full/index.tsv of `derive` (completeness needs the derived lines too)."""
    out = data.parent / "derived"
    srun(data, scen, "derive", "--out", str(out))
    return {r["file"]: r for r in T.read_tsv(out / "story-en-full/index.tsv", ["file", "lines", "need", "english", "complete"])}


def test_story_build(data, scenario, font):
    scen, e3 = scenario
    ctx = T.Ctx(data=data, scenario=scen)
    s = T.build_story(ctx, {})
    assert {m: v[2] for m, v in s.out.items()} == {"1010_065_49": "official", "1010_030_17": "official",
                                                  e3: "official"}
    assert "\u2015" in s.out[e3][1]
    for m, (h, en, _) in s.out.items():
        # broken for the message window (E7, E13: story_break, which re-breaking doesn't change)
        assert C.unesc(en) == T.story_break(font, C.unesc(en))
    c = s.files["TS_1999"]
    assert (c["lines"], c["need"], c["english"]) == (6, 5, 3)
    # the line's hash is of the text with real newlines
    assert s.out["1010_065_49"][0] == C.sha1(C.unesc(T.Ctx().src.gl_ja["1010_065_49"]))



def test_story_break_fewest_lines(font):
    """E13: a line that fits the window's 4 lines at 480 px keeps that break; a longer one is broken at
    story_budget(n) for the fewest n lines that hold it (128 n - 32 px)."""
    assert [T.story_budget(n) for n in (1, 4, 5, 6, 8)] == [480, 480, 608, 736, 992]
    short = "This fits in one line."
    assert T.story_break(font, short) == font.rebreak(short, 480, T.PLAYER_PX)
    long = " ".join(["Some long words that keep going on and on"] * 8)
    r = T.story_break(font, long)
    n = r.count("\n") + 1
    assert n > T.STORY_LINES and font.widest(r, T.PLAYER_PX) <= T.story_budget(n)
    assert font.rebreak(long, T.story_budget(n - 1), T.PLAYER_PX).count("\n") + 1 > n - 1


def test_story_import_mt_and_completeness(data, scenario, tmp_path):
    scen, _ = scenario
    ck = tmp_path / "story.jsonl"
    ck.write_text(story_ck([sline("9999_t_01", "テストの行です。", "This is a test line."),
                            sline("9999_t_02", "<player>、待って！", "Wait!"),        # drops <player>
                            sline("1010_065_49", C.unesc(T.Ctx().src.gl_ja["1010_065_49"]), "Covered"),
                            sline("9999_t_03", "……", None)]) + "\n")
    assert srun(data, scen, "import-mt", str(ck)) == 0
    t = {r["message_id"]: r for r in T.read_tsv(data / "story/TS_1999.tsv", T.TABLE_COLS)}
    assert list(t) == ["9999_t_01"] and t["9999_t_01"]["source"] == "machine"
    assert t["9999_t_01"]["engine"] == "gemma-4-31b-it/UD-Q4_K_XL/v2+s1/llama.cpp-b11443/t0"
    rej = {r["message_id"]: json.loads(r["problems"])
           for r in T.read_tsv(data.parent / "work/mt-rejected-story.tsv", T.REJECT_COLS)}
    assert "tags" in rej["9999_t_02"]
    assert index(data, scen)["TS_1999"]["complete"] == "no"
    served = {r["message_id"]: r for r in T.read_tsv(data / "story-en/TS_1999.tsv", T.OUT_COLS)}
    assert served["9999_t_01"]["source"] == "machine"
    # a person fills the last line: the file is complete
    assert srun(data, scen, "set", "9999_t_02", "<player>, wait!", "--by", "tester") == 0
    assert index(data, scen)["TS_1999"]["complete"] == "yes"
    # a re-import with --replace replaces the machine line and keeps the human one
    ck.write_text(story_ck([sline("9999_t_01", "テストの行です。", "A test line."),
                            sline("9999_t_02", "<player>、待って！", "<player>, hold on!")], prompt="v3") + "\n")
    srun(data, scen, "import-mt", "--replace", str(ck))
    t = {r["message_id"]: r for r in T.read_tsv(data / "story/TS_1999.tsv", T.TABLE_COLS)}
    assert t["9999_t_01"]["en"] == "A test line." and t["9999_t_02"]["en"] == "<player>, wait!"
    assert t["9999_t_02"]["source"] == "human"


def test_story_stale_and_check_without_scenario(data, scenario, tmp_path, capsys):
    scen, _ = scenario
    (data / "story").mkdir()
    (data / "story/TS_1999.tsv").write_text(T.tsv_text(T.TABLE_COLS, [
        {"message_id": "9999_t_01", "ja_sha1": "0" * 40, "en": "Old", "source": "human", "engine": "",
         "date": "2026-10-08", "editor": "tester", "note": ""}]), encoding="utf-8")
    s = T.build_story(T.Ctx(data=data, scenario=scen), {})
    assert [x[0] for x in s.stale] == ["9999_t_01"] and "9999_t_01" not in s.out
    assert srun(data, scen, "stale", "--fail") == 1
    # without the Scenario files the story part is skipped, and --check still judges the master part
    (data / "story/TS_1999.tsv").write_text(T.tsv_text(T.TABLE_COLS, [
        {"message_id": "9999_t_01", "ja_sha1": C.sha1("テストの行です。"), "en": "A line.", "source": "human",
         "engine": "", "date": "2026-10-08", "editor": "tester", "note": ""}]), encoding="utf-8")
    srun(data, scen, "build")
    before = (data / "story-en/TS_1999.tsv").read_text()
    assert srun(data, tmp_path / "no-such-dir", "build", "--check") == 0
    assert "story: skipped" in capsys.readouterr().out
    srun(data, tmp_path / "no-such-dir", "build")
    assert (data / "story-en/TS_1999.tsv").read_text() == before


def test_story_po_export(data, scenario, tmp_path):
    polib = pytest.importorskip("polib")
    scen, _ = scenario
    out = tmp_path / "po"
    srun(data, scen, "export-po", "--out", str(out))
    po = polib.pofile(str(out / "TS_1999.po"))
    e = {x.msgctxt: x for x in po}
    assert e["9999_t_01"].msgid == "テストの行です。" and e["9999_t_01"].msgstr == ""
    e["9999_t_01"].msgstr = "Edited in Poedit"
    po.save()
    srun(data, scen, "import-po", str(out / "TS_1999.po"), "--by", "poedit")
    t = {r["message_id"]: r for r in T.read_tsv(data / "story/TS_1999.tsv", T.TABLE_COLS)}
    assert t["9999_t_01"]["source"] == "human" and t["9999_t_01"]["en"] == "Edited in Poedit"


# ---------------------------------------------------------------- compositions and the glossary rules

def test_glossary_forms():
    g = {"レモングミ": {"en": "Lemon Gummy", "variants": []}, "ロール": {"en": "Role:", "variants": []},
         "エアリアル・アラモード": {"en": "Aerial à la Mode", "variants": []}}
    assert C.glossary_misses("レモングミを15個", "Obtain 15 Lemon Gummies", g) == []
    assert C.glossary_misses("全ロール", "All Roles", g) == []
    assert C.glossary_misses("エアリアル・アラモード", "Aerial a la Mode", g) == []
    assert C.glossary_misses("レモングミ", "Lime candy", g) == [["レモングミ", "Lemon Gummy"]]


def test_composed_fragments_served(built):
    """E3's second half: the fragments the client composes (english.md 7.6) are human rows, served
    as written: a leading space where the client prepends a name, an empty uimsg_remain_base."""
    out = {r["message_id"]: r for r in T.read_tsv(T.DATA / "master-en.tsv", T.OUT_COLS)}
    assert out["uimsg_remain_base"]["en"] == "" and out["uimsg_remain_base"]["source"] == "human"
    assert out["uimsg_block_decide"]["en"] == " has been blocked."
    assert out["uimsg_time_to_the_end"]["en"] == "Ends in "
    assert out["uimsg_time_limit_tail"]["en"] == " until %d:%02d"
    assert not [m for m, *_ in built.token_gaps if m not in out
                and m not in ("uimsg_chiket_error", "uimsg_gacha_need_head")]


def test_glossary_demotions(built):
    """Weak Global terms are removed by human rows; machine names Global contradicts get its spelling."""
    g = built.glossary
    assert "モンスター" not in g and "願い" not in g and "期間：" not in g
    assert g["ローク"]["en"] == "Roak" and g["ローク"]["source"] == "human"
    assert g["紋章石"]["en"] == "Gems"  # Global's names and terms stay


# ---------------------------------------------------------------- committed = our rows only (2026-10-07)

def test_committed_tables_hold_only_our_rows(built):
    """The user's decision: data/english carries machine / human / reviewed rows (+ client strings),
    never Global's English; official / memory / template are derived at build time."""
    for r in T.read_tsv(T.DATA / "master-en.tsv", T.OUT_COLS):
        assert r["source"] in ("machine", "human", "reviewed"), r
    for p in (T.DATA / "story-en").glob("*.tsv"):
        assert p.name != "index.tsv"
        for r in T.read_tsv(p, T.OUT_COLS):
            assert r["source"] in ("machine", "human", "reviewed"), r
    assert all(r["source"] != "official" for r in T.read_tsv(T.DATA / "glossary.tsv", T.GLOSSARY_COLS))
    # the derived glossary still holds Global's terms
    assert sum(1 for r in built.glossary_rows if r["source"] == "official") == 3246


def test_derive_full(built, tmp_path):
    """`derive` writes the resolved tables (all sources): our rows win as the precedence says."""
    T.derive(T.Ctx(), tmp_path)
    full = {r["message_id"]: r for r in T.read_tsv(tmp_path / "master-en-full.tsv", T.OUT_COLS)}
    assert len(full) == len(built.out)
    assert {r["source"] for r in full.values()} >= {"official", "memory", "template", "human"}
    for r in T.read_tsv(T.DATA / "master-en.tsv", T.OUT_COLS):
        if r["source"] != "machine":
            assert full[r["message_id"]] == r


def test_box_rows(font):
    # the home's speech box: two lines of 480 px (english.md 7.11); \n is the master's escaped break
    out = {"x_hmmsg_01": ("", "Short line.\\nAnother.", "official"),
           "x_hmmsg_02": ("", "One\\ntwo\\nthree", "machine"),
           "x_hmmsg_03": ("", "W" * 30, "machine"),
           "x_other": ("", "a\\nb\\nc", "machine")}
    rows = {r[1]: r for r in T.box_rows(font, out, {"x_hmmsg_01": "あ\\nい"})}
    assert set(rows) == {"x_hmmsg_01", "x_hmmsg_02", "x_hmmsg_03"}
    assert rows["x_hmmsg_01"][3:6] == [2, 24, 2] and rows["x_hmmsg_01"][9] == "fits"
    assert rows["x_hmmsg_02"][9] == "tall" and rows["x_hmmsg_02"][7] == 1  # re-broken: one line
    assert rows["x_hmmsg_03"][9] == "wide" and rows["x_hmmsg_03"][7] == 1  # one word: no break
    s = T.box_summary(list(rows.values()))["home-talk"]
    assert s["rows"] == 3 and s["fit_after_rebreak"] == 2  # the 810 px word does not fit
