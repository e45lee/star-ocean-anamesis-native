"""Shared library of the English text tools (tools/english_text.py, tools/english_mt.py):
the sources (JP 3.7.0 master, Global master, story files), translation memory, glossary, the font's
advances read from Font/etc2/font.fpk, glyph folding, line re-breaking, Global token rewrites (E3)
and the checks every English row must pass (docs/english.md 7.5, 7.6).

Only the standard library plus zstandard (SLZ codec 7) and, for the story files, msgpack via
soa_save. No engine is called here.
"""
import collections
import fnmatch
import hashlib
import io
import os
import pathlib
import pickle
import re
import sqlite3
import struct
import sys
import unicodedata
import zipfile
import zlib

REPO = pathlib.Path(__file__).resolve().parent.parent
if str(REPO) not in sys.path:
    sys.path.insert(0, str(REPO))

MASTER_DB = REPO / "data/basmaster-3.7.0.sqlite3"
GLOBAL_DB = REPO / "data/basmaster-gl.sqlite3"
# The story's Japanese: the 3.7.0 download's Scenario/ files. The download is its zip (read in place,
# soa_save/download_tree.py) or a folder; a folder holding the TS_*.msgp files themselves works too.
SCENARIO = REPO / "work/SOA-3.7.0-canonical-data.zip"
APK = REPO / "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk"
FONT_MEMBER = "assets/builtin_data/Font/etc2/font.fpk"
FONT_NAME = "Font/etc2/font.fpk"

KANA = re.compile("[぀-ヿ一-鿿]")
# a katakana term inside a longer katakana word is not that term (レイ in マルチプレイ)
KATA = re.compile("[ァ-ヿ]+")
HIRA = re.compile("[ぁ-ゟ]")
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


def unesc(s):
    """Master encoding (a line break is the two characters backslash-n) -> real newlines."""
    return s.replace("\\n", "\n")


def esc(s):
    return s.replace("\n", "\\n")


# ---------------------------------------------------------------- sources

class Sources:
    """The JP 3.7.0 master, Global's master and (lazily) the 3.7.0 story files.
    `a` is an argparse namespace with .master, .gl, .scenario (english_mt's options); or keywords."""

    def __init__(self, a=None, master=MASTER_DB, gl=GLOBAL_DB, scenario=SCENARIO):
        if a is not None:
            master, gl, scenario = a.master, a.gl, getattr(a, "scenario", scenario)
        self.jp = sqlite3.connect(f"file:{master}?mode=ro", uri=True)
        self.gl = sqlite3.connect(f"file:{gl}?mode=ro", uri=True)
        self.jp_rows = dict(self.jp.execute("select message_id, text_value from master_text"))
        self.gl_en = dict(self.gl.execute("select message_id, text_value from master_text where lang='en'"))
        self.gl_ja = dict(self.gl.execute("select message_id, text_value from master_text where lang='ja'"))
        self.scenario = pathlib.Path(scenario)
        self._scenario_tree = None
        self._story = None

    def scenario_tree(self):
        """(DownloadTree, folder) holding the TS_*.msgp Scenario files, or None without them: the
        download's Scenario/, or `scenario` itself when it holds them."""
        if self._scenario_tree is None:
            from soa_save.download_tree import DownloadTree
            found = False
            t = DownloadTree.open_or_none(self.scenario)
            if t is not None:
                for d in ("Scenario", ""):
                    if any(fnmatch.fnmatchcase(n, "TS_*.msgp") for n in t.list(d)):
                        found = (t, d)
                        break
            self._scenario_tree = found
        return self._scenario_tree or None

    def has_story(self):
        return self.scenario_tree() is not None

    def gl_english(self, mid):
        """Global's `en` for mid if it is real, usable English, else None (filters 1, 2, 4, 5)."""
        en, ja = self.gl_en.get(mid), self.gl_ja.get(mid)
        if not en or has_kana(en) or en == ja or GL_TOKEN.search(en):
            return None
        if SPEC_STRICT.findall(en) != SPEC_STRICT.findall(ja or ""):
            return None
        return en

    def gl_token_english(self, mid):
        """Global's `en` for mid when it is English but carries Global-only markup (<NUM n>, <STR n>,
        <INSERT>, <EMDASH>) and nothing else that filter 4 drops: E3's input. Else None."""
        en, ja = self.gl_en.get(mid), self.gl_ja.get(mid)
        if not en or has_kana(en) or en == ja or not GL_MARKUP.search(en):
            return None
        if GL_TOKEN.search(GL_MARKUP.sub("", en.replace("</INSERT>", ""))):
            return None  # also a [G]/[Red] chip name: filter 4 keeps dropping those
        return en

    def official(self, mid, ja):
        en = self.gl_english(mid)
        return en if en is not None and self.gl_ja.get(mid) == ja else None

    def official_e3(self, mid, ja):
        """(english, None) from a Global token row rewritten by E3, (None, reason) when the row has
        tokens that can't be rewritten, (None, None) when there is no such row. `ja` in the master's
        encoding."""
        en = self.gl_token_english(mid)
        if en is None or self.gl_ja.get(mid) != ja:
            return None, None
        return rewrite_tokens(en, ja)

    def story(self):
        """[(file stem, message_id, ja)] of the 3.7.0 Scenario files (real newlines); [] without them."""
        if self._story is None:
            from soa_save import script
            out = []
            found = self.scenario_tree()
            tree, d = found if found else (None, "")
            for n in tree.list(d) if tree else []:
                if not fnmatch.fnmatchcase(n, "TS_*.msgp"):
                    continue
                for row in script.load(tree.read(f"{d}/{n}" if d else n), "Scenario/" + n).get("master_text", []):
                    out.append((n[: -len(".msgp")], row["message_id"], row["text_value"] or ""))
            self._story = out
        return self._story

    def story_official(self, mid, ja):
        en = self.gl_english(mid)
        if en is None:
            return None
        gj = (self.gl_ja.get(mid) or "").replace("\\n", "\n")
        return en if gj == ja else None

    def story_official_e3(self, mid, ja):
        """As official_e3 for a story line (`ja` with real newlines). The English keeps Global's
        encoding (backslash-n)."""
        en = self.gl_token_english(mid)
        if en is None or unesc(self.gl_ja.get(mid) or "") != ja:
            return None, None
        return rewrite_tokens(en, esc(ja))


def story_group(stem):
    return ("EP1" if stem < "TS_2" else "EP2" if stem < "TS_3" else "TS_3xxx" if stem < "TS_4"
            else "TS_5xxx" if stem < "TS_6" else "EP3" if stem < "TS_7" else "events/other")


# ---------------------------------------------------------------- E3: Global's tokens

INSERT = re.compile(r"<INSERT \d+>([^<>/]*)/([^<>]*)</INSERT>")
NUMSTR = re.compile(r"<(NUM|STR) (\d+)>")


def fix_percent(en, ja):
    """In a printf row (the Japanese has a specifier) a literal percent must be %%: a bare % would be
    read as a conversion ("50% or" -> "% o"). docs/english.md 7.5."""
    if not SPEC.search(ja):
        return en
    return re.sub(r"%%|(" + SPEC.pattern + r")|%",
                  lambda m: m.group() if m.group() == "%%" or m.group(1) else "%%", en)


def rewrite_tokens(en, ja):
    """E3 (PLAN-english.md): Global's tokens in `en` rewritten for the 3.7.0 client, or why not.
    <EMDASH> -> U+2015 (the font has no em dash); <INSERT n>one/many</INSERT> -> the plural form
    (one fixed form: the client fills no count there); <NUM n>/<STR n> -> the n-th printf specifier of
    the JP row (n counts all arguments, as Global's "Day <NUM 2> <STR 1>"), spelled as JP spells it
    (%02d, %u). Only when the tokens use each JP argument once and in JP's order: a reordered row would
    need %2$d, which the port's printf doesn't support (docs/english.md 3.3), so it stays a gap.
    Returns (english, None) or (None, reason). Works on either newline encoding."""
    en = en.replace("<EMDASH>", "―")
    en = INSERT.sub(lambda m: m.group(2), en)
    toks = [int(n) for _, n in NUMSTR.findall(en)]
    specs = SPEC_STRICT.findall(ja)
    if toks:
        if not specs:
            return None, "composition: the JP row has no specifier (the client composes the name around it)"
        if sorted(toks) != list(range(1, len(specs) + 1)):
            return None, f"tokens {toks} don't match the JP specifiers {specs}"
        if toks != sorted(toks):
            return None, f"reorder needed: tokens {toks} (no positional printf)"
        en = NUMSTR.sub(lambda m: specs[int(m.group(2)) - 1], en)
    if GL_MARKUP.search(en):
        return None, "unknown Global token"
    en = fix_percent(en, ja)
    if SPEC_STRICT.findall(en) != specs:
        return None, f"specifiers {SPEC_STRICT.findall(en)} vs JP {specs}"
    return en, None


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
        # most used, then the smallest string: a deterministic choice among equal counts
        self.exact = {k: min(c, key=lambda e: (-c[e], e)) for k, c in exact.items()}
        self.template = {k: min(c, key=lambda e: (-c[e], e)) for k, c in tmpl.items()}

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
    Every message_id of a name field is used, in JP's master or only in Global's. A term with more
    than one official English takes the most used one, then the shortest (then the smallest string);
    the others are accepted variants."""
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
    for kind, mids in sorted(ids.items()):
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
    for ja in sorted(terms):
        t = terms[ja]
        ranked = sorted(t["en"], key=lambda e: (-t["en"][e], len(e), e))  # most used, then shortest
        kind = min(t["kind"], key=lambda k: (-t["kind"][k], k))
        out[ja] = {"en": ranked[0], "kind": kind, "variants": ranked[1:], "ids": t["ids"]}
    return out


class _HitIndex:
    """The terms of a glossary by length, to find the candidates of a text without scanning every term."""

    def __init__(self, glossary):
        self.order = sorted(glossary, key=len, reverse=True)
        self.rank = {t: i for i, t in enumerate(self.order)}
        self.lengths = sorted({len(t) for t in self.order if len(t) >= 2})
        self.terms = set(self.order)

    def candidates(self, ja):
        found = set()
        for i in range(len(ja)):
            for n in self.lengths:
                if i + n > len(ja):
                    break
                if ja[i:i + n] in self.terms:
                    found.add(ja[i:i + n])
        return sorted(found, key=self.rank.__getitem__)


_hit_cache = {}


def glossary_hits(ja, glossary, terms_sorted=None):
    """The glossary terms in a Japanese text, longest first, without overlaps."""
    if terms_sorted is None:
        idx = _hit_cache.get(id(glossary))
        if idx is None or idx[0] is not glossary or idx[2] != len(glossary):
            idx = (glossary, _HitIndex(glossary), len(glossary))
            _hit_cache.clear()
            _hit_cache[id(glossary)] = idx
        terms_sorted = idx[1].candidates(ja)
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


# ---------------------------------------------------------------- the font (docs/english.md 3.1)

def slz_decode(d):
    """An SLZ stream (codec 0 stored, 5 raw deflate, 7 zstd; chunked), decompressed whole."""
    if d[:3] != b"SLZ":
        return d
    codec, dsz = d[3], struct.unpack_from("<i", d, 0xc)[0]
    off, chunk = struct.unpack_from("<I", d, 0x14)[0], d[0x19] * 1024 or dsz
    out, p = bytearray(), off
    while len(out) < dsz:
        want = min(chunk, dsz - len(out))
        if codec == 0:
            out += d[p:p + want]
            p += want
            continue
        n = struct.unpack_from("<H", d, p)[0]
        p += 2
        if n == 0:  # a chunk that didn't shrink is stored
            out += d[p:p + want]
            p += want
            continue
        if codec == 5:
            out += zlib.decompressobj(-15).decompress(d[p:p + n])
        elif codec == 7:
            import zstandard
            out += zstandard.ZstdDecompressor().decompressobj().decompress(d[p:p + n])
        else:
            raise ValueError(f"SLZ codec {codec}")
        p += n
    return bytes(out)


def isf_members(d):
    """{name: bytes} of an ISF container: b"\\0ISF", u32 version, u32 count, u32 0, then per member
    16 bytes (u32 name offset, u32 data offset, u32 size, u32 hash), names NUL-terminated."""
    if d[:4] != b"\0ISF":
        raise ValueError("not an ISF container")
    n = struct.unpack_from("<I", d, 8)[0]
    out = {}
    for i in range(n):
        name_off, data_off, size, _ = struct.unpack_from("<4I", d, 0x10 + 16 * i)
        name = d[name_off:d.index(b"\0", name_off)].decode()
        out[name] = d[data_off:data_off + size]
    return out


def read_font_glyphs(fpk=None):
    """The glyph records of fontData.bin: [(id, x, y, w, h, xoff, yoff, xadvance, page, chnl)].
    `fpk` is the font.fpk bytes (ADLD XOR keyed by CHash32 of its path, then SLZ, then ISF); by
    default the copy in the committed 3.7.0 APK, which equals the download's (docs/english.md 3.1)."""
    from soa_save import adld
    if fpk is None:
        with zipfile.ZipFile(APK) as z:
            fpk = z.read(FONT_MEMBER)
    data = isf_members(slz_decode(adld.decode(fpk, FONT_NAME)))["fontData.bin"]
    hdr = struct.unpack_from("<3I", data, 0)
    if hdr[:2] != (24, 24) or len(data) != 12 + 40 * hdr[2]:
        raise ValueError(f"unexpected fontData.bin header {hdr}")
    return [struct.unpack_from("<10i", data, 12 + 40 * i) for i in range(hdr[2])]


FOLD = {"—": "―", "–": "-", "‘": "'", "’": "'", "“": '"', "”": '"',
        "•": "・", "·": "・", "™": "", "®": "", "€": "EUR", " ": " "}

_font_cache = {}


class Font:
    """Advances of the client's font (Font/etc2/font.fpk; docs/english.md 3.1). `path` None reads the
    committed APK; a .pkl is the old glyph dump (tuples as read_font_glyphs); anything else a font.fpk
    file (e.g. the download's)."""

    def __init__(self, path=None):
        key = str(path)
        if key not in _font_cache:
            if path is None:
                glyphs = read_font_glyphs()
            elif str(path).endswith(".pkl"):
                with open(path, "rb") as f:
                    glyphs = pickle.load(f)
            elif str(path).endswith(".apk"):
                with zipfile.ZipFile(path) as z:
                    glyphs = read_font_glyphs(z.read(FONT_MEMBER))
            else:
                glyphs = read_font_glyphs(pathlib.Path(path).read_bytes())
            # the loader reads only the low 16 bits of the id (CBitmapFontManager::RegistryFont)
            _font_cache[key] = {g[0] & 0xFFFF: g[7] for g in glyphs}
        self.adv = _font_cache[key]

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

    def width(self, line, tag_px=None):
        """Pixels of one line at the font's 24 px size; tags draw nothing unless `tag_px` gives them a
        width (the story's <player> expands to the player's name)."""
        extra = sum(tag_px.get(t.replace("\x01", " "), 0) for t in TAG.findall(line)) if tag_px else 0
        line = TAG.sub("", line)
        return extra + sum(self.adv.get(ord(c), self.adv[0x3F]) for c in line)

    def widest(self, text, tag_px=None):
        return max((self.width(x, tag_px) for x in text.split("\n")), default=0)

    def rebreak(self, text, budget, tag_px=None):
        """Greedy word wrap at spaces to `budget` px per line (existing breaks are dropped)."""
        # a tag is one word: "<font color=red>" must not break at its space
        text = TAG.sub(lambda m: m.group().replace(" ", "\x01"), re.sub(r"\s*\n\s*", " ", text))
        words = text.split(" ")
        lines, cur = [], ""
        for w in words:
            cand = w if not cur else cur + " " + w
            if cur and self.width(cand, tag_px) > budget:
                lines.append(cur)
                cur = w
            else:
                cur = cand
        if cur:
            lines.append(cur)
        return "\n".join(lines).replace("\x01", " ")


# ---------------------------------------------------------------- checks

def protected(text):
    """The tokens an English text must keep: printf specifiers (in order) and markup tags."""
    return SPEC.findall(text), sorted(TAG.findall(text))


# the tags ParseMessage reads in story lines (docs/english.md 1.2, 3.3); the 3.7.0 story files use
# <font color=blue|yellow|green|red>...</font> and <player>
STORY_TAG = re.compile(r"<player>|<font ?color=[^<>]*>|<fontsize=[^<>]*>|</font>")


def _tags_subset(tj, te):
    """Label rows: English tags only of the kinds the Japanese has, <font> opens and closes balanced
    (Global's own label English sometimes colours fewer or more words; harmless in labels)."""
    if not set(te) <= set(tj):
        return False
    opens = sum(1 for t in te if t.startswith("<font") or t.startswith("<fontcolor") or t.startswith("<fontsize"))
    return opens == te.count("</font>")


def check(ja, en, font, glossary=None, budget=None, tags="strict"):
    """Problems of an English row for a Japanese one, as a dict (empty = fine). Both texts with real
    newlines. tags: "strict" (the same tags; machine rows, story lines) or "subset" (label rows from
    Global or a person: _tags_subset)."""
    p = {}
    sj, tj = protected(ja)
    se, te = protected(en)
    if sj != se:
        p["specifiers"] = [sj, se]
    elif sj and re.sub(SPEC.pattern + "|%%", "", en).count("%"):
        p["specifiers"] = [sj, se, "bare %"]  # printf would read "% o" as a conversion
    if re.search(r"%\d+\$", en):
        p["positional"] = True  # the port's printf has no positional arguments (docs/english.md 3.3)
    if tj != te and not (tags == "subset" and _tags_subset(tj, te)):
        p["tags"] = [tj, te]
    if has_kana(en):
        p["kana"] = True
    miss = font.missing(en)
    if miss:
        p["glyphs"] = miss
    if GL_MARKUP.search(en):
        p["global_token"] = True
    if glossary:
        bad = glossary_misses(ja, en, glossary)
        if bad:
            p["glossary"] = bad
    if budget and font.widest(en) > budget:
        p["width"] = [font.widest(en), budget]
    return p


def _gloss_norm(s):
    """Lower case, one space for any whitespace (a \\n too), accents dropped (the output is folded to
    the font: "à la Mode" is written "a la Mode")."""
    s = unicodedata.normalize("NFKD", unesc(s))
    s = "".join(c for c in s if not unicodedata.combining(c))
    return re.sub(r"\s+", " ", s).lower().strip()


def _gloss_forms(term):
    """The forms of a glossary English that count as using it: as written, without label punctuation
    ("Role:" -> "role"), and singular/plural (-s, -y/-ies: "Gummy" ~ "Gummies")."""
    t = _gloss_norm(term)
    forms = {t}
    bare = t.strip(" :：.!?・")
    if bare:
        forms.add(bare)
    for f in list(forms):
        if f.endswith("ies"):
            forms.add(f[:-3] + "y")
        elif f.endswith("y"):
            forms.add(f[:-1] + "ies")
        if f.endswith("s"):
            forms.add(f[:-1])
    return {f for f in forms if f}


def glossary_misses(ja, en, glossary):
    """[[term, english]] of the glossary terms in `ja` whose English (or an accepted variant) isn't in
    `en`; case, line breaks, accents, a label's trailing colon and a plural/singular don't count."""
    flat = _gloss_norm(en)

    def used(term):
        return any(f in flat for f in _gloss_forms(term))
    return [[t, glossary[t]["en"]] for t in glossary_hits(ja, glossary)
            if not used(glossary[t]["en"]) and not any(used(v) for v in glossary[t]["variants"])]


def runaway(ja, en):
    """An engine output that ran away: far longer than the Japanese could need (more than 80
    characters and 8 times the Japanese), or a unit of 2-8 characters repeated 12+ times in a
    row. Machine rows only (english.md 7.5); a stretched scream of a few dozen letters passes."""
    flat = re.sub(r"\s+", " ", en)
    return (len(flat) > max(80, 8 * len(ja))) or bool(re.search(r"(.{2,8}?)\1{11,}", flat))


def post_one(r, en, font, glossary, mem=None):
    """Post-process one engine output for row r ({"ja" (master encoding), "budget", "multiline"}):
    NFC, glyph folding, %% in printf rows, re-break multi-line rows; returns (english, problems)."""
    en = (en or "").strip()
    en = font.fold(unicodedata.normalize("NFC", en))
    # an engine keeps the Japanese list dot between stat names ("ATK・INT・DEF"); Global writes a
    # slash ("ATK/INT/DEF/HIT/GRD +30%"), and the kana check would refuse the dot (U+30FB, U+FF65)
    en = re.sub(r"(?<=[A-Za-z0-9%])\s*[\u30fb\uff65]\s*(?=[A-Za-z0-9])", "/", en)
    en = fix_percent(en, r["ja"])  # a printf row: a literal percent must be %% (NFKC made ％ a bare %)
    if r.get("multiline") and r["budget"]:
        en = font.rebreak(en, max(r["budget"], 200))
    else:
        en = re.sub(r"\s*\n\s*", " ", en)
    ja = unesc(r["ja"])
    probs = check(ja, en, font, glossary)
    if runaway(ja, en):
        probs["runaway"] = len(en)
    if not r.get("multiline") and r["budget"] and font.widest(en) > 1.5 * max(r["budget"], 100):
        probs["width"] = [font.widest(en), r["budget"]]
    return en, probs
