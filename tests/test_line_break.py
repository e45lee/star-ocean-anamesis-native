"""The shared line-break vectors (common/tests/line_break_vectors.tsv) against tools/english_core.py
Font.rebreak, the derivation's breaker: the rows of its mode (keep_breaks 0, skip_japanese 0,
tags_are_words 1; trim is str.strip() first, as story_finish does). The C++ breaker
(soa/line_break.h) passes every row in build/common/soa_text_tests, so the two agree."""
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import english_core as C  # noqa: E402

VECTORS = ROOT / "common" / "tests" / "line_break_vectors.tsv"


def vector_font():
    """A Font whose advances are the vectors' measure (the file's header)."""
    adv = {}
    for cp in range(0x10000):
        c = chr(cp)
        adv[cp] = 1 if c in "il'.,! |" else 3 if c in "mwMW" else 4 if cp >= 0x3000 else 2
    f = object.__new__(C.Font)
    f.adv = adv
    return f


def rows():
    lines = [x for x in VECTORS.read_text(encoding="utf-8").split("\n") if x and not x.startswith("#")]
    assert lines[0] == "text\tbudget\tkeep_breaks\tskip_japanese\ttags_are_words\ttrim\tplayer\texpected"
    for x in lines[1:]:
        f = x.split("\t")
        assert len(f) == 8, x
        yield f


def unesc(s):
    return re.sub(r"\\([nt])", lambda m: "\n" if m.group(1) == "n" else "\t", s)


def test_rebreak_matches_the_shared_vectors():
    font = vector_font()
    n = 0
    for text, budget, kb, sj, tg, tr, pl, want in rows():
        if (kb, sj, tg) != ("0", "0", "1"):
            continue
        t = unesc(text)
        if tr == "1":
            t = t.strip()
        got = font.rebreak(t, float(budget), {"<player>": 16} if pl == "1" else None)
        assert got == unesc(want), (text, budget, got, want)
        n += 1
    assert n >= 30
