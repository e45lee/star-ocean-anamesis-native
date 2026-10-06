#!/usr/bin/env python3
"""Data side of machine translation (MT) for the English mode: coverage, glossary, translation
memory, protected tokens, glyph folding, line widths, and the checks an MT (or human) row must pass.
docs/english.md section 7 describes the method and the trial; docs/PLAN-english.md the steps.

It only reads data (the committed master DBs, the 3.7.0 download's Scenario files, the font metrics
dumped to work/) and writes to work/. It calls no MT engine: the engine adapters of the trial are
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
                --scenario work/download-3.7.0/Scenario --glyphs work/english/font/glyphs.pkl

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
import hashlib
import json
import os
import pathlib
import pickle
import random
import re
import sqlite3
import sys
import unicodedata

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))

KANA = re.compile("[\u3040-\u30ff\u4e00-\u9fff]")
# a katakana term inside a longer katakana word is not that term (レイ in マルチプレイ)
KATA = re.compile("[\u30a1-\u30ff]+")
HIRA = re.compile("[\u3041-\u309f]")
# printf conversions as the client's callers fill them (docs/english.md 1.1); %% is a literal.
# No space flag: "50% c..." in prose is not a specifier (docs/english.md 1.4).
SPEC = re.compile(r"%(?:\d+\$)?[-+#0]*\d*(?:\.\d+)?(?:ll|l|h)?[dusfxXc]")
SPEC_STRICT = re.compile(r"%[-+#0]*\d*(?:\.\d+)?(?:ll|l|h)?[dusfxXc]")
GL_TOKEN = re.compile(r"<NUM|<STR|<INSERT|</INSERT|<EMDASH>|\[(?:G|R|Y|B|Blue|Red|Green|Yellow|White|-)\]")
GL_MARKUP = re.compile(r"<NUM|<STR|<INSERT|</INSERT|<EMDASH>")  # [Red] etc. are plain text in 3.7.0
# markup the 3.7.0 client reads: <font color=..>..</font> (labels in tag mode), <player>,
# <fontcolor=..>, <fontsize=..>, </font> (story); docs/english.md 3.3
TAG = re.compile(r"<[^<>\n]{1,40}>")
NUM = re.compile(r"\d+(?:\.\d+)?")
# English templates that don't carry over to other numbers: month names, ordinals
TEMPLATE_UNSAFE = re.compile(r"January|February|March|April|May|June|July|August|September|October|"
                             r"November|December|\}(?:st|nd|rd|th)\b")


def has_kana(s):
    return bool(s and KANA.search(s))


def sha1(s):
    return hashlib.sha1(s.encode("utf-8")).hexdigest()


def prefix(mid):
    return re.split(r"[_0-9]", mid, 1)[0] or mid


# ---------------------------------------------------------------- sources

class Sources:
    def __init__(self, a):
        self.jp = sqlite3.connect(f"file:{a.master}?mode=ro", uri=True)
        self.gl = sqlite3.connect(f"file:{a.gl}?mode=ro", uri=True)
        self.jp_rows = dict(self.jp.execute("select message_id, text_value from master_text"))
        self.gl_en = dict(self.gl.execute("select message_id, text_value from master_text where lang='en'"))
        self.gl_ja = dict(self.gl.execute("select message_id, text_value from master_text where lang='ja'"))
        self.scenario_dir = pathlib.Path(a.scenario)
        self._story = None

    def gl_english(self, mid):
        """Global's `en` for mid if it is real, usable English, else None (filters 1, 2, 4, 5)."""
        en, ja = self.gl_en.get(mid), self.gl_ja.get(mid)
        if not en or has_kana(en) or en == ja or GL_TOKEN.search(en):
            return None
        if SPEC_STRICT.findall(en) != SPEC_STRICT.findall(ja or ""):
            return None
        return en

    def official(self, mid, ja):
        en = self.gl_english(mid)
        return en if en is not None and self.gl_ja.get(mid) == ja else None

    def story(self):
        """[(file stem, message_id, ja)] of the 3.7.0 Scenario files (real newlines)."""
        if self._story is None:
            from soa_save import script
            out = []
            for p in sorted(self.scenario_dir.glob("TS_*.msgp")):
                for row in script.load(p.read_bytes(), "Scenario/" + p.name).get("master_text", []):
                    out.append((p.stem, row["message_id"], row["text_value"] or ""))
            self._story = out
        return self._story

    def story_official(self, mid, ja):
        en = self.gl_english(mid)
        if en is None:
            return None
        gj = (self.gl_ja.get(mid) or "").replace("\\n", "\n")
        return en if gj == ja else None


def story_group(stem):
    return ("EP1" if stem < "TS_2" else "EP2" if stem < "TS_3" else "TS_3xxx" if stem < "TS_4"
            else "TS_5xxx" if stem < "TS_6" else "EP3" if stem < "TS_7" else "events/other")


# ---------------------------------------------------------------- memory

def numkey(ja):
    """(template, numbers) of a Japanese text: NFKC (full-width digits -> ASCII), numbers -> {}."""
    n = unicodedata.normalize("NFKC", ja)
    nums = NUM.findall(n)
    return NUM.sub("\x00", n), nums


class Memory:
    """Exact and template translation memory from Global's official pairs (any message_id).
    `exclude` drops pairs by message_id (the trial's sample, so it isn't scored against itself)."""

    def __init__(self, src, exclude=frozenset()):
        exact = collections.defaultdict(collections.Counter)
        tmpl = collections.defaultdict(collections.Counter)
        for mid, ja in src.gl_ja.items():
            if mid in exclude or not ja:
                continue
            en = src.gl_english(mid)
            if en is None:
                continue
            exact[ja][en] += 1
            key, nums = numkey(ja)
            if not nums or len(set(nums)) != len(nums):
                continue  # no numbers, or ambiguous (a repeated number)
            ens = NUM.findall(en)
            if sorted(ens) != sorted(nums):
                continue  # each Japanese number must appear once in the English
            idx = {v: i for i, v in enumerate(nums)}
            t = NUM.sub(lambda m: "{%d}" % idx[m.group()] if m.group() in idx else m.group(), en)
            if NUM.search(re.sub(r"\{\d+\}", "", t)) or TEMPLATE_UNSAFE.search(t):
                continue  # an English number with no Japanese counterpart; dates, ordinals
            tmpl[key][t] += 1
        self.exact = {k: c.most_common(1)[0][0] for k, c in exact.items()}
        self.template = {k: c.most_common(1)[0][0] for k, c in tmpl.items()}

    def lookup(self, ja):
        """(english, kind) or (None, None)."""
        if ja in self.exact:
            return self.exact[ja], "exact"
        key, nums = numkey(ja)
        t = self.template.get(key) if nums else None
        if t is not None:
            en = re.sub(r"\{(\d+)\}", lambda m: nums[int(m.group(1))], t)
            return re.sub(r"\b1 (time|hit|day|turn|battle|mission)s\b", r"1 \1", en, flags=re.I), "template"
        return None, None


# ---------------------------------------------------------------- glossary

GLOSSARY_KINDS = [
    # kind, SQL over the JP master giving message_ids whose whole text is a term
    ("character", "select name_message_id from master_person"),
    ("skill", "select name_message_id from master_skill"),
    ("item", "select name_message_id from master_item"),
    ("area", "select name_message_id from master_area"),
    ("mission", "select name_message_id from master_mission"),
]
GLOSSARY_PREFIXES = [("talent", "talentName_"), ("skill", "AttackName_")]
SPEAKER = re.compile(r"^c[a-z]\d{4}_[a-z]{2}\d{2}[a-z]$")  # model codes: speaker names (cp0312_ta99a)


def build_glossary(src, exclude=frozenset()):
    """{ja term: {"en", "kind", "variants", "ids"}} from Global's official text of name fields.
    Every message_id of a name field is used, in JP's master or only in Global's."""
    ids = collections.defaultdict(set)
    for kind, sql in GLOSSARY_KINDS:
        for (mid,) in src.jp.execute(sql):
            if mid:
                ids[kind].add(mid)
    for mid in src.gl_ja:
        for kind, p in GLOSSARY_PREFIXES:
            if mid.startswith(p):
                ids[kind].add(mid)
        if SPEAKER.match(mid):
            ids["speaker"].add(mid)
        ja = src.gl_ja[mid] or ""
        if mid.startswith("uimsg_") and len(ja) <= 8 and not HIRA.search(ja) and (len(ja) >= 3 or KATA.fullmatch(ja)):
            ids["ui"].add(mid)  # short UI labels: the game's own terms (スタミナ, 紋章石)
    terms = collections.defaultdict(lambda: {"en": collections.Counter(), "kind": collections.Counter(), "ids": []})
    for kind, mids in ids.items():
        for mid in sorted(mids):
            if mid in exclude:
                continue
            ja, en = src.gl_ja.get(mid), src.gl_english(mid)
            if not ja or en is None or "\\n" in ja or SPEC.search(ja) or len(ja) < 2 or len(ja) > 24:
                continue
            ja = ja.strip("　 ")
            t = terms[ja]
            t["en"][en.strip()] += 1
            t["kind"][kind] += 1
            t["ids"].append(mid)
    out = {}
    for ja, t in terms.items():
        ranked = sorted(t["en"], key=lambda e: (-t["en"][e], len(e), e))  # most used, then shortest
        out[ja] = {"en": ranked[0], "kind": t["kind"].most_common(1)[0][0],
                   "variants": ranked[1:], "ids": t["ids"]}
    return out


def glossary_hits(ja, glossary, terms_sorted=None):
    """The glossary terms in a Japanese text, longest first, without overlaps."""
    terms_sorted = terms_sorted or sorted(glossary, key=len, reverse=True)
    taken = [False] * len(ja)
    hits = []
    for t in terms_sorted:
        if len(t) < 2:
            continue
        start = 0
        while True:
            i = ja.find(t, start)
            if i < 0:
                break
            inside = KATA.fullmatch(t) and ((i > 0 and KATA.match(ja[i - 1]))
                                            or (i + len(t) < len(ja) and KATA.match(ja[i + len(t)])))
            if not inside and not any(taken[i:i + len(t)]):
                for k in range(i, i + len(t)):
                    taken[k] = True
                hits.append(t)
                break
            start = i + 1
    return hits


# ---------------------------------------------------------------- tokens, glyphs, widths

def protected(text):
    """The tokens an English text must keep: printf specifiers (in order) and markup tags."""
    return SPEC.findall(text), sorted(TAG.findall(text))


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


FOLD = {"—": "―", "–": "-", "‘": "'", "’": "'", "“": '"', "”": '"',
        "•": "・", "·": "・", "™": "", "®": "", "€": "EUR", " ": " "}


class Font:
    """Advances of the client's font (Font/etc2/font.fpk; docs/english.md 3.1), from the glyph dump
    in work/english/font/glyphs.pkl: tuples (id, x, y, w, h, xoff, yoff, xadvance, page, chnl)."""

    def __init__(self, path):
        with open(path, "rb") as f:
            self.adv = {g[0] & 0xFFFF: g[7] for g in pickle.load(f)}

    def fold(self, s):
        """Map to glyphs the font has: accents stripped, dashes and quotes replaced."""
        out = []
        for c in s:
            c = FOLD.get(c, c)
            if c and len(c) == 1 and ord(c) not in self.adv and c not in "\n\t":
                d = unicodedata.normalize("NFKD", c)
                c = "".join(x for x in d if ord(x) in self.adv) or "?"
            out.append(c)
        return "".join(out)

    def missing(self, s):
        return sorted({c for c in s if c not in "\n\t" and ord(c) not in self.adv})

    def width(self, line):
        line = TAG.sub("", line)
        return sum(self.adv.get(ord(c), self.adv[0x3F]) for c in line)

    def widest(self, text):
        return max((self.width(x) for x in text.split("\n")), default=0)

    def rebreak(self, text, budget):
        """Greedy word wrap at spaces to `budget` px per line (existing breaks are dropped)."""
        # a tag is one word: "<font color=red>" must not break at its space
        text = TAG.sub(lambda m: m.group().replace(" ", "\x01"), re.sub(r"\s*\n\s*", " ", text))
        words = text.split(" ")
        lines, cur = [], ""
        for w in words:
            cand = w if not cur else cur + " " + w
            if cur and self.width(cand) > budget:
                lines.append(cur)
                cur = w
            else:
                cur = cand
        if cur:
            lines.append(cur)
        return "\n".join(lines).replace("\x01", " ")


# ---------------------------------------------------------------- checks

def check(ja, en, font, glossary=None, budget=None):
    """Problems of an English row for a Japanese one, as a dict (empty = fine)."""
    p = {}
    sj, tj = protected(ja)
    se, te = protected(en)
    if sj != se:
        p["specifiers"] = [sj, se]
    if tj != te:
        p["tags"] = [tj, te]
    if has_kana(en):
        p["kana"] = True
    miss = font.missing(en)
    if miss:
        p["glyphs"] = miss
    if GL_MARKUP.search(en):
        p["global_token"] = True
    if glossary:
        flat = re.sub(r"\s+", " ", en).lower()

        def used(term):  # case, line breaks and a plural/singular -s don't count
            term = re.sub(r"\s+", " ", term).lower()
            return term in flat or term.rstrip("s") in flat
        bad = [t for t in glossary_hits(ja, glossary)
               if not used(glossary[t]["en"]) and not any(used(v) for v in glossary[t]["variants"])]
        if bad:
            p["glossary"] = [[t, glossary[t]["en"]] for t in bad]
    if budget and font.widest(en) > budget:
        p["width"] = [font.widest(en), budget]
    return p


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


def post_one(r, en, font, glossary, mem=None):
    """Restore, fold and re-break one engine output; returns (final english, problems)."""
    en = (en or "").strip()
    en = font.fold(unicodedata.normalize("NFC", en))
    if r.get("multiline") and r["budget"]:
        en = font.rebreak(en, max(r["budget"], 200))
    else:
        en = re.sub(r"\s*\n\s*", " ", en)
    ja = r["ja"].replace("\\n", "\n")
    probs = check(ja, en, font, glossary, budget=None if r.get("multiline") else None)
    if not r.get("multiline") and r["budget"] and font.widest(en) > 1.5 * max(r["budget"], 100):
        probs["width"] = [font.widest(en), r["budget"]]
    return en, probs


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
    ap.add_argument("--glyphs", default=str(REPO / "work/english/font/glyphs.pkl"))
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
