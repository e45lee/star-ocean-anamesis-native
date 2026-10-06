#!/usr/bin/env python3
"""Data side of machine translation (MT) for the English mode: coverage, glossary, translation
memory, protected tokens, glyph folding, line widths, and the checks an MT (or human) row must pass.
docs/english.md section 7 describes the method and the trial; docs/PLAN-english.md the steps.

It only reads data (the committed master DBs, the 3.7.0 download's Scenario files, the font in the
committed APK) and writes to work/. It calls no MT engine: the engine adapters of the trial are
scratch scripts in work/english/mt-trial/ run with their own venv (work/tools/mt-venv), so this file
imports nothing outside requirements.txt.

Usage:
  tools/english_mt.py coverage  [--json OUT]           # rows by source: official id / exact memory /
                                                       # template memory / gap; characters; prefixes
  tools/english_mt.py glossary  --out TSV [--exclude IDS]
  tools/english_mt.py sample    --out DIR [--seed N]   # the trial sample (sample.jsonl, ids.txt)
  tools/english_mt.py post      --sample DIR/sample.jsonl --mt RAW.jsonl --out OUT.jsonl
                                                       # restore tokens, fold glyphs, re-break, check
Common options: --master data/basmaster-3.7.0.sqlite3 --gl data/basmaster-gl.sqlite3
                --scenario work/download-3.7.0/Scenario --glyphs FILE (default: the font of the
                committed APK, apk/...3.7.0...apk Font/etc2/font.fpk)

The shared code (sources, memory, glossary, font, checks) is tools/english_core.py; the committed
English table and its build are tools/english_text.py.

Definitions (docs/english.md 1.4 and 7.2):
  official (by id)  Global's `en` for the same message_id: English (no kana/kanji, not a copy of
                    `ja`), Global's `ja` == JP 3.7.0's `ja`, no Global-only token, the same printf
                    specifiers in the same order.
  exact memory      another official pair has the identical Japanese text.
  template memory   an official pair whose Japanese differs only in its numbers (full-width or
                    ASCII); the English template gets this row's numbers.
  gap               none of these: MT, a human, or Japanese.
"""
import argparse
import collections
import json
import os
import pathlib
import random
import re
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / "tools"))

# The shared library (tools/english_core.py); these names stay importable from here (the MT runner
# imports english_mt.Sources, Memory, build_glossary, glossary_hits, has_kana, sha1).
from english_core import (FOLD, GL_MARKUP, GL_TOKEN, HIRA, KANA, KATA, NUM, SPEC, SPEC_STRICT,  # noqa: E402,F401
                          TAG, TEMPLATE_UNSAFE, Font, Memory, Sources, build_glossary, check,
                          glossary_hits, has_kana, numkey, post_one, prefix, protected, sha1,
                          story_group)


def mask(text):
    """Text with each specifier/tag replaced by a placeholder an NMT model copies: (masked, tokens)."""
    toks = []

    def sub(m):
        toks.append(m.group())
        return f" X{len(toks) - 1}X "
    return re.sub(r"%(?:\d+\$)?[-+#0]*\d*(?:\.\d+)?(?:ll|l|h)?[dusfxXc]|%%|<[^<>\n]{1,40}>", sub, text), toks


def unmask(text, toks):
    for i, t in enumerate(toks):
        text = re.sub(rf"\s*X\s*{i}\s*X\s*", f" {t} " if not t.startswith("<") else t, text, count=1)
    return re.sub(r"[ \t]+", " ", text).strip()


# ---------------------------------------------------------------- commands

def cmd_coverage(a):
    src = Sources(a)
    mem = Memory(src)
    rows = collections.Counter()
    chars = collections.Counter()
    pref = collections.defaultdict(collections.Counter)
    distinct_gap = set()
    for mid, ja in src.jp_rows.items():
        ja = ja or ""
        if src.official(mid, ja):
            k = "official"
        elif not has_kana(ja):
            k = "neutral"
        else:
            en, kind = mem.lookup(ja)
            k = kind or "gap"
        rows[k] += 1
        chars[k] += len(ja)
        pref[k][prefix(mid)] += 1
        if k == "gap":
            distinct_gap.add(ja)
    stale = sum(1 for mid, ja in src.jp_rows.items()
                if src.gl_english(mid) and src.gl_ja.get(mid) != ja and has_kana(ja))
    story = collections.Counter()
    schars = collections.Counter()
    for stem, mid, ja in src.story():
        g = story_group(stem)
        k = "neutral" if not has_kana(ja) else "official" if src.story_official(mid, ja) else "gap"
        story[(g, k)] += 1
        schars[(g, k)] += len(ja)
    res = {
        "master_rows": dict(rows), "master_chars": dict(chars),
        "master_gap_distinct_texts": len(distinct_gap),
        "master_gap_distinct_chars": sum(len(t) for t in distinct_gap),
        "master_stale_global": stale,
        "gap_prefixes": pref["gap"].most_common(20),
        "template_prefixes": pref["template"].most_common(10),
        "story": {f"{g}/{k}": [n, schars[(g, k)]] for (g, k), n in sorted(story.items())},
    }
    print(json.dumps(res, ensure_ascii=False, indent=1))
    if a.json:
        pathlib.Path(a.json).write_text(json.dumps(res, ensure_ascii=False, indent=1))


def read_ids(path):
    return frozenset(pathlib.Path(path).read_text().split()) if path else frozenset()


def cmd_glossary(a):
    src = Sources(a)
    g = build_glossary(src, read_ids(a.exclude))
    os.makedirs(os.path.dirname(os.path.abspath(a.out)), exist_ok=True)
    with open(a.out, "w") as f:
        f.write("ja\ten\tkind\tvariants\tids\n")
        for ja in sorted(g):
            t = g[ja]
            f.write(f"{ja}\t{t['en']}\t{t['kind']}\t{' | '.join(t['variants'])}\t{' '.join(t['ids'][:5])}\n")
    kinds = collections.Counter(t["kind"] for t in g.values())
    print(f"{len(g)} terms {dict(kinds)}; {sum(1 for t in g.values() if t['variants'])} with variants -> {a.out}")


# strata of the trial: (name, size, predicate on (message_id, ja))
STRATA = [
    ("uimsg", 30, lambda m, j: m.startswith(("uimsg", "sys_", "error_"))),
    ("message", 25, lambda m, j: m.startswith("message")),
    ("seed/factor", 25, lambda m, j: m.startswith(("seed", "factor"))),
    ("item", 20, lambda m, j: m.lower().startswith("item")),
    ("name", 20, lambda m, j: m.startswith("name")),
    ("skill/talent", 20, lambda m, j: m.startswith(("AttackName", "AttackExplainName", "talentName"))),
    ("profile", 20, lambda m, j: re.match(r"c[pc]\d{4}_", m) is not None),
    ("specifier", 20, lambda m, j: bool(SPEC_STRICT.search(j))),
    ("newline", 20, lambda m, j: "\\n" in j),
]


def cmd_sample(a):
    src = Sources(a)
    font = Font(a.glyphs)
    rnd = random.Random(a.seed)
    out = pathlib.Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    taken, sample = set(), []
    pool = sorted(src.jp_rows.items())
    official = [(m, j) for m, j in pool if has_kana(j) and src.official(m, j)]
    for name, n, pred in STRATA:
        cand = [(m, j) for m, j in official if pred(m, j) and m not in taken]
        for m, j in rnd.sample(cand, min(n, len(cand))):
            taken.add(m)
            sample.append({"id": m, "kind": "master", "stratum": name, "ja": j, "ref": src.official(m, j)})
    # unscored gap rows from 3.x features (no official English exists)
    mem = Memory(src)
    gap = [(m, j) for m, j in pool if has_kana(j) and not src.official(m, j) and mem.lookup(j)[0] is None
           and m.startswith(("uimsg", "Guide", "message_sphere", "name_sphere", "universe", "Asset", "gachaPickup"))]
    for m, j in rnd.sample(gap, 40):
        sample.append({"id": m, "kind": "master", "stratum": "gap", "ja": j, "ref": None})
    # story: 50 EP1 lines with official English (scored), favouring <player> and names; 20 EP3 gap lines
    story = src.story()
    ep1 = [(s, m, j) for s, m, j in story if story_group(s) == "EP1" and has_kana(j) and src.story_official(m, j)]
    tagged = [x for x in ep1 if "<" in x[2]]
    pick = rnd.sample(tagged, min(10, len(tagged)))
    pick += rnd.sample([x for x in ep1 if x not in pick], 50 - len(pick))
    for s, m, j in pick:
        sample.append({"id": m, "kind": "story", "stratum": "story-EP1", "file": s, "ja": j,
                       "ref": src.story_official(m, j).replace("\\n", "\n")})
    ep3 = [(s, m, j) for s, m, j in story if story_group(s) == "EP3" and has_kana(j)]
    for s, m, j in rnd.sample(ep3, 20):
        sample.append({"id": m, "kind": "story", "stratum": "story-EP3-gap", "file": s, "ja": j, "ref": None})
    # line budget: master rows keep their own widest JP line; story lines the story window's
    # width, taken as the p99 widest JP line over all story text
    sw = sorted(font.widest(j) for _, _, j in story if has_kana(j))
    story_budget = sw[int(len(sw) * 0.99)]
    for r in sample:
        ja = r["ja"].replace("\\n", "\n")
        r["budget"] = story_budget if r["kind"] == "story" else font.widest(ja)
        r["multiline"] = r["kind"] == "story" or "\n" in ja
    with open(out / "sample.jsonl", "w") as f:
        for r in sample:
            f.write(json.dumps(r, ensure_ascii=False) + "\n")
    (out / "ids.txt").write_text("\n".join(r["id"] for r in sample) + "\n")
    print(f"{len(sample)} rows ({sum(1 for r in sample if r['ref'])} with official English); "
          f"story budget {story_budget} px -> {out}")


def cmd_post(a):
    src = Sources(a)
    font = Font(a.glyphs)
    excl = read_ids(a.exclude) if a.exclude else frozenset(
        json.loads(x)["id"] for x in open(a.sample))
    glossary = build_glossary(src, excl)
    sample = {json.loads(x)["id"]: json.loads(x) for x in open(a.sample)}
    n = collections.Counter()
    with open(a.out, "w") as f:
        for line in open(a.mt):
            m = json.loads(line)
            r = sample[m["id"]]
            en, probs = post_one(r, m["mt"], font, glossary)
            n["rows"] += 1
            for k in probs:
                n[k] += 1
            f.write(json.dumps({**r, "mt_raw": m["mt"], "mt": en, "problems": probs}, ensure_ascii=False) + "\n")
    print(json.dumps(dict(n)))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--master", default=str(REPO / "data/basmaster-3.7.0.sqlite3"))
    ap.add_argument("--gl", default=str(REPO / "data/basmaster-gl.sqlite3"))
    ap.add_argument("--scenario", default=str(REPO / "work/download-3.7.0/Scenario"))
    ap.add_argument("--glyphs", default=None,
                    help="font advances: default the committed APK's Font/etc2/font.fpk; or a font.fpk, .apk or the old glyphs.pkl")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("coverage")
    p.add_argument("--json")
    p = sub.add_parser("glossary")
    p.add_argument("--out", required=True)
    p.add_argument("--exclude")
    p = sub.add_parser("sample")
    p.add_argument("--out", required=True)
    p.add_argument("--seed", type=int, default=20261007)
    p = sub.add_parser("post")
    p.add_argument("--sample", required=True)
    p.add_argument("--mt", required=True)
    p.add_argument("--out", required=True)
    p.add_argument("--exclude")
    a = ap.parse_args()
    {"coverage": cmd_coverage, "glossary": cmd_glossary, "sample": cmd_sample, "post": cmd_post}[a.cmd](a)


if __name__ == "__main__":
    main()
