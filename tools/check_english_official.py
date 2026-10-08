#!/usr/bin/env python3
"""Official over machine: every served English row keeps Global's text wherever Global has one
(docs/english.md 7.6 "Precedence", 7.9 step 7; the user's rule: official (Global) > machine, and only
a human or reviewed row may replace Global's English).

For every JP master row and every story line it derives, independently of the merge, the English
Global offers for it:
  master  Global's English by id (rules id and id-ws; a credit row's Japanese name and romanization
          included, official-credit), else a Global token row rewritten (E3), else (a row with kana
          or kanji) the translation memory: exact, memory-ws or template, else Global's English by id
          for a Japanese text changed only in punctuation or an abbreviation (official-near);
  story   Global's English by id, else E3 (the story has no memory, english.md 7.9 step 8);
and checks the served row against it. The comparison allows only what the derivation itself does to
Global's text: glyph folding, %% in printf rows, a story line's strip and every re-break. Both sides
have their white space and line breaks collapsed to one space; any other difference is a reword.

Buckets:
  ok           the served text is Global's
  human        a human / reviewed row is served (allowed over Global; `differs` counts the overrides)
  fallthrough  Global's text fails a check of the derivation (english.md 7.9 step 6), so the next
               candidate (our machine row) is served legitimately
  violation    anything else: a machine or agent row (or the Japanese) served although Global's text passes,
               a derived source whose text is not Global's, or Global's text reworded
Exit 1 when there is a violation.

Usage:
  tools/check_english_official.py [--tables DIR] [--out FILE] [--data DIR] [--master DB] [--gl DB]
                                  [--scenario ZIP|DIR] [--font FILE]
  --tables DIR  check a written table instead of building it in memory: DIR/master-en-full.tsv and
                DIR/story-en-full/ (tools/english_text.py derive --out DIR), or DIR/master-en.tsv and
                DIR/story-en/ (soa-server --english-dump DIR)
  --out FILE    every checked row with its bucket and rule (TSV)
Without the 3.7.0 download (work/SOA-3.7.0-canonical-data.zip) the story part is skipped, as in
`tools/english_text.py build`.
"""
import argparse
import collections
import pathlib
import re
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))

import english_core as C  # noqa: E402
import english_text as T  # noqa: E402

DERIVED = ("official", "memory", "template")


def collapse(s):
    """White space and line breaks (real or the master's \\n) collapsed to one space, stripped."""
    return re.sub(r"\s+", " ", C.unesc(s)).strip()


def read_table(path):
    return {r["message_id"]: (r["ja_sha1"], r["en"], r["source"]) for r in T.read_tsv(path, T.OUT_COLS, required=True)}


def served_tables(ctx, tables):
    """({mid: (sha1, en, source)} of the master, the same of the story or None)."""
    if tables is None:
        b = T.build(ctx)
        s = T.build_story(ctx, b.glossary)
        return b.out, (s.out if s is not None else None)
    d = pathlib.Path(tables)
    master = d / "master-en-full.tsv" if (d / "master-en-full.tsv").exists() else d / "master-en.tsv"
    sdir = d / "story-en-full" if (d / "story-en-full").is_dir() else d / "story-en"
    story = None
    if sdir.is_dir() and ctx.src.has_story():
        story = {}
        for f in sorted(sdir.glob("TS_*.tsv")):
            story.update(read_table(f))
    return read_table(master), story


def master_expected(src, mem, mid, ja):
    """(rule, Global's English as stored) of a JP master row, or (None, None)."""
    off = src.official(mid, ja)
    if off is not None:
        return C.same_ja(src.gl_ja.get(mid), ja), off
    e3, _ = src.official_e3(mid, ja)
    if e3 is not None:
        return "e3", e3
    if C.has_kana(ja):
        en, kind = mem.lookup(ja)
        if en is not None:
            return {"exact": "memory", "exact_ws": "memory-ws"}.get(kind, kind), en
        near = src.official_near(mid, ja)
        if near is not None:
            return "near", near
    return None, None


def story_expected(src, mid, ja):
    en = src.story_official(mid, ja)
    if en is not None:
        return "id", en
    e3, _ = src.story_official_e3(mid, ja)
    return ("e3", e3) if e3 is not None else (None, None)


def judge(served, want, passes):
    """The bucket of one row: served (sha1, en, source) or None; want = Global's text after the
    derivation's own normalisation (fold, %%), not yet collapsed."""
    if served is not None and served[2] in T.HUMAN:
        return "human", collapse(served[1]) != collapse(want)
    if not passes:
        return "fallthrough", False
    if served is None:
        return "violation", True
    if collapse(served[1]) != collapse(want):
        return "violation", True
    return ("ok", False) if served[2] in DERIVED else ("violation", True)


def check(ctx, tables=None):
    src, font = ctx.src, ctx.fnt
    mem = C.Memory(src)
    master, story = served_tables(ctx, tables)
    rows = []  # (part, message_id, rule, bucket, served source, global (normalised), served en)
    for mid in sorted(src.jp_rows):
        ja = src.jp_rows[mid] or ""
        rule, en = master_expected(src, mem, mid, ja)
        served = master.get(mid)
        if rule is None:
            if served is not None and served[2] in DERIVED:
                rows.append(("master", mid, "", "violation", served[2], "", served[1]))  # derived, but not Global's
            continue
        source = "template" if rule == "template" else "memory" if rule.startswith("memory") else "official"
        _, probs, _ = T.finish(ctx, None, source, en, ja)
        want = C.fix_percent(font.fold(C.unesc(en)), ja)
        bucket, differs = judge(served, want, not probs)
        if bucket == "human" and not differs:
            bucket = "human-same"
        rows.append(("master", mid, rule, bucket, served[2] if served else "japanese", C.esc(want),
                     served[1] if served else ""))
    if story is not None:
        lines = {}
        for stem, mid, ja in src.story():
            lines[mid] = ja  # a later file's line of the same id wins (english_text.StoryDerived)
        for mid in sorted(lines):
            ja = lines[mid]
            rule, en = story_expected(src, mid, ja)
            served = story.get(mid)
            if rule is None:
                if served is not None and served[2] in DERIVED:
                    rows.append(("story", mid, "", "violation", served[2], "", served[1]))
                continue
            _, probs, _ = T.story_finish(ctx, None, "official", en, ja)
            want = font.fold(C.unesc(en)).strip()
            bucket, differs = judge(served, want, not probs)
            if bucket == "human" and not differs:
                bucket = "human-same"
            rows.append(("story", mid, rule, bucket, served[2] if served else "japanese", C.esc(want),
                         served[1] if served else ""))
    return rows, story is not None


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0], formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tables")
    ap.add_argument("--out")
    ap.add_argument("--data", default=str(T.DATA))
    ap.add_argument("--master", default=str(C.MASTER_DB))
    ap.add_argument("--gl", default=str(C.GLOBAL_DB))
    ap.add_argument("--scenario", default=str(C.SCENARIO))
    ap.add_argument("--font")
    a = ap.parse_args(argv)
    ctx = T.Ctx(data=pathlib.Path(a.data), master=a.master, gl=a.gl, scenario=a.scenario, font=a.font)
    rows, with_story = check(ctx, a.tables)
    count = collections.Counter((r[0], r[3]) for r in rows)
    rules = collections.Counter((r[0], r[2]) for r in rows if r[3] == "ok")
    for part in ("master", "story") if with_story else ("master",):
        print(f"{part}: " + ", ".join(f"{k} {count[(part, k)]}" for k in
                                      ("ok", "human", "human-same", "fallthrough", "violation"))
              + "; ok by rule: " + ", ".join(f"{r} {n}" for (p, r), n in sorted(rules.items()) if p == part))
    if not with_story:
        print("story: skipped (no Scenario files: work/SOA-3.7.0-canonical-data.zip)")
    if a.out:
        with open(a.out, "w", encoding="utf-8") as f:
            f.write("part\tmessage_id\trule\tbucket\tserved_source\tglobal\tserved\n")
            for r in rows:
                f.write("\t".join(r) + "\n")
    bad = [r for r in rows if r[3] == "violation"]
    for r in bad[:20]:
        print(f"VIOLATION {r[0]} {r[1]} (rule {r[2] or '-'}, served {r[4]}): global {r[5]!r} served {r[6]!r}")
    if bad:
        print(f"check_english_official: FAIL, {len(bad)} rows where Global's English loses to a non-human row")
        return 1
    print("check_english_official: ok (every served row keeps Global's English unless a person replaced it)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
