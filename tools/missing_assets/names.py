"""Names: the 3.7.0 Japanese text and its English.

English for a name, first hit wins (``Names.english``):
  1. the hand-written TSV (docs/missing-assets-names.tsv, Japanese text -> English);
  2. the Global master's English text (data/basmaster-gl.sqlite3), by message id where the Global
     Japanese text equals the 3.7.0 one, else by identical Japanese text;
  3. the text itself when it has no kana / kanji;
  4. the phrase glossary (character names from the Global master or soa_save/names_en.json first),
     marked "(tr.)" when Japanese is left over.
Characters (``Names.person``): the Global master, else names_en.json, else the TSV.
"""
from __future__ import annotations

import collections
import json
import os
import re
import sqlite3
import unicodedata
from typing import Optional

from . import ROOT

#: Kana, kanji and half-width kana: "this text is (still) Japanese".
JA = re.compile(r"[぀-ヿ㐀-鿿ｦ-ﾟ]")

NAMES_EN_JSON = os.path.join(ROOT, "soa_save", "names_en.json")
#: Official Global wording missing from names_en.json's titles (docs/basmaster-gl.md).
EXTRA_TITLES = {"渚の": "Seaside", "涙目": "Tearful"}
#: TSV keys starting with this name an area by its id_label (areas without a name text).
TSV_LABEL_PREFIX = "@"

GL_PAIRS_SQL = ("select j.message_id, j.text_value, e.text_value from master_text j join master_text e "
                "on e.message_id = j.message_id and e.lang = 'en' where j.lang = 'ja' order by j.message_id")

GLOSSARY = [  # (Japanese, English), applied longest first after NFKC
    ("10連10ステップ目PU1体確定", "10-pull step-up, pick-up guaranteed at step 10"),
    ("10連10ステップ目ピックアップ1体確定", "10-pull step-up, pick-up guaranteed at step 10"),
    ("ピックアップ", "Pick-up "), ("PU", "Pick-up "), ("ステップアップ", "Step-up "),
    ("キャラガチャチケット", "Character Gacha Ticket"), ("武器ガチャチケット", "Weapon Gacha Ticket"),
    ("ガチャチケット", "Gacha Ticket"), ("チケットガチャ", "Ticket Gacha"),
    ("キャラガチャ", "Character Gacha"), ("武器ガチャ", "Weapon Gacha"), ("ボックスガチャ", "Box Gacha"),
    ("ガチャ", "Gacha"), ("チケット", "Ticket"), ("イベントミッション", "Event Missions"),
    ("イベント", "Event"), ("ミッション", "Missions"), ("ステップ", "Step "),
    ("【復刻】", "[Rerun] "), ("復刻", "Rerun "), ("覚醒キャラ", "Awakened Character "), ("覚醒", "Awakened "),
    ("限定", "Limited "), ("確定", "Guaranteed"), ("以上", "+"), ("1体", "1 unit "), ("記念", " Commemoration"),
    ("公開", "Release"), ("周年", " Anniversary"), ("アニバーサリー", "Anniversary"), ("コラボ", " Collab"),
    ("水着", "Swimsuit "), ("ハロウィン", "Halloween "), ("クリスマス", "Christmas "), ("正月", "New Year "),
    ("バレンタイン", "Valentine "), ("花嫁", "Bride "), ("メイド", "Maid "), ("アイドル", "Idol "),
    ("サマー", "Summer "), ("福袋", "Lucky Bag "), ("スペシャル", "Special "), ("第", "Part "), ("弾", ""),
    ("箱目", " box"), ("前半", " (first half)"), ("後半", " (second half)"), ("毎日1回", "once a day"),
    ("1日1回", "once a day"), ("日替", "Daily "), ("専用", " only"), ("10連のみ", "10-pull only"),
    ("期間中1人1回", "once per player during the period"), ("新キャラ", "New Character "), ("新", "New "),
    ("キャラ", "Character "), ("武器", "Weapon "), ("と", " & "), ("の", " "),
]


def text_key(s: Optional[str]) -> str:
    """Normalised text for lookups: NFKC, `\\n` escapes and runs of white space as one space."""
    return re.sub(r"\s+", " ", unicodedata.normalize("NFKC", s or "").replace("\\n", " ")).strip()


def load_tsv(path: Optional[str]) -> dict[str, str]:
    """The hand-written names: `Japanese<TAB>English` lines (`#` comments), keyed by `text_key`."""
    out: dict[str, str] = {}
    if path and os.path.exists(path):
        for line in open(path, encoding="utf-8"):
            if line.strip() and not line.startswith("#") and "\t" in line:
                k, v = line.rstrip("\n").split("\t", 1)
                out[text_key(k)] = v
    return out


def english_person_name(names_en: dict, label: Optional[str], ja: str) -> Optional[str]:
    """A person's English name from names_en.json: the character (by the label's code), its title
    prefix and suffix; None when a part has no English."""
    ch = names_en["characters"].get((label or "").split("_")[0])
    if not ch:
        return None
    base_ja, base_en = ch[0], ch[1]
    rest, suffix = ja, ""
    for sj, se in names_en["suffixes"].items():
        if rest.endswith(sj):
            rest, suffix = rest[:-len(sj)], se
    if base_ja not in rest:
        return None
    prefix = rest[:rest.rindex(base_ja)]
    if not prefix:
        return base_en + suffix
    title = names_en["titles"].get(prefix)
    if title is None:
        return None
    return (title + base_en if title.endswith("-") else f"{title} {base_en}") + suffix


class Names:
    """Japanese text of the 3.7.0 master and English per the resolution order above."""

    def __init__(self, master: sqlite3.Connection, gl_path: Optional[str], tsv_path: Optional[str]):
        self.ja: dict[str, str] = {r[0]: r[1] for r in master.execute("select message_id, text_value from master_text")}
        self.gl: dict[str, str] = {}       # message id -> English (same Japanese text as 3.7.0)
        self.gl_text: dict[str, str] = {}  # Japanese text -> English
        self._load_global(gl_path)
        self.tsv = load_tsv(tsv_path)
        self.people = self._load_people(master)  # Japanese person name -> English
        self.residue: collections.Counter = collections.Counter()  # Japanese the glossary left over

    key = staticmethod(text_key)

    def _load_global(self, gl_path: Optional[str]) -> None:
        if not (gl_path and os.path.exists(gl_path)):
            return
        gl = sqlite3.connect(f"file:{gl_path}?mode=ro", uri=True)
        for mid, tj, te in gl.execute(GL_PAIRS_SQL):
            te = text_key(te)
            if not te or JA.search(te):
                continue
            # only where the Global Japanese text is the 3.7.0 one (GL is an older revision)
            if text_key(tj) == text_key(self.ja.get(mid, "")):
                self.gl[mid] = te
            self.gl_text.setdefault(text_key(tj), te)

    def _load_people(self, master: sqlite3.Connection) -> dict[str, str]:
        names_en = json.load(open(NAMES_EN_JSON, encoding="utf-8"))
        names_en["titles"].update(EXTRA_TITLES)
        people: dict[str, str] = {}
        for label, mid in master.execute("select id_label, name_message_id from master_person"):
            ja = self.ja.get(mid)
            if not ja or JA.search(ja) is None:
                continue
            en = self.gl.get(mid) or english_person_name(names_en, label, ja)
            if en:
                people.setdefault(unicodedata.normalize("NFKC", ja), en)
        for base_ja, base_en, _full in names_en["characters"].values():
            people.setdefault(base_ja, base_en)
        return people

    def text(self, mid: Optional[str]) -> str:
        """The normalised Japanese text of a message id ("" when unknown)."""
        return text_key(self.ja.get(mid or "", ""))

    def english(self, mid: Optional[str], ja: Optional[str] = None) -> tuple[str, str]:
        """(English, how) for a message id or a Japanese string: the TSV, else the Global master
        (by message id, else by identical Japanese text), else the glossary."""
        ja = text_key(ja if ja is not None else self.ja.get(mid or "", ""))
        if not ja:
            return "", "none"
        if ja in self.tsv:
            return self.tsv[ja], "tsv"
        if mid and mid in self.gl:
            return self.gl[mid], "gl"
        if ja in self.gl_text:
            return self.gl_text[ja], "gl"
        if not JA.search(ja):
            return ja, "same"
        return self.gloss(ja), "glossary"

    def official(self, mid: Optional[str]) -> Optional[str]:
        """English from the TSV or the Global master only (no glossary), or None."""
        ja = self.text(mid)
        return self.tsv.get(ja) or self.gl.get(mid or "") or self.gl_text.get(ja)

    def gloss(self, ja: str) -> str:
        """A phrase-by-phrase translation: person names first, then the glossary, longest first.
        Counts what stays Japanese in `residue` and marks it "(tr.)"."""
        s = ja
        for jn in sorted(self.people, key=len, reverse=True):
            if jn in s:
                s = s.replace(jn, "\0" + self.people[jn] + "\1")  # protected from the glossary's "の" etc.
        for j, e in sorted(GLOSSARY, key=lambda x: -len(x[0])):
            s = s.replace(j, e)
        s = s.replace("\0", "").replace("\1", "")
        s = re.sub(r"\s+", " ", s).replace(" )", ")").replace("( ", "(").strip()
        if JA.search(s):
            self.residue[ja] += 1
            s += " (tr.)"
        return s

    def person(self, mid: Optional[str]) -> tuple[str, Optional[str]]:
        """(Japanese, English or None) of a person's name."""
        ja = self.text(mid)
        en = self.gl.get(mid) or self.people.get(ja) or (self.tsv.get(ja) if ja in self.tsv else None)
        return ja, en
