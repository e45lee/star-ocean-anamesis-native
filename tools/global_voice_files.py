#!/usr/bin/env python3
"""List the voice files the Global (English) master names, and which characters they belong to.

  .venv/bin/python tools/global_voice_files.py [--gl data/basmaster-gl.sqlite3]
        [--jp data/basmaster-3.7.0.sqlite3] [--download work/download-3.7.0]
        [--apk apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk]
        [--txt docs/global-voice-files.txt] [--md docs/global-voice-files.md]

What names a voice file in the Global master (rule labels as in docs/server-rules.md):
  master_person.voice_parameter        Parameter/Battle/<x>.msgp   (b) + the download's names
  master_person.voice_sound_package    Sound/<x>.spk  battle voice (b)
  master_person.gacha_voice_package    Sound/<x>.spk  gacha voice  (b)
  master_event_area.voice_menu_pack_name  Sound/<x>.spk  event menu voice (b)
  master_skill.se_sound_package*       Sound/<x>.spk  when the pack is a Voice_ pack (b)
Derived (not named by the master):
  Sound/<stem>-en.spk   the English dub of a Voice_*.spk, from the client's voice-language
                        rule (CGameResourceManager::FileExistLanguage, (b)), for the packs of
                        persons whose profile names an English voice actor (prmsg_10, (a));
                        that Global shipped exactly these is assumption (d).
  Story packs           Voice_TS_* named by VoicePlay commands of the JP Script/*.msgp files of
                        chapters whose text is in the Global master (d); listed in the .md only.

A file is "JP same-name" when the JP 3.7.0 master names it or a source holds it, and "in hand"
when the 3.7.0 download or the 3.7.0 APK holds it (zero-size files don't count). Names: the
Global master's English when it has no kana / kanji, else soa_save/names_en.json marked "(tr.)".
Output is deterministic (everything sorted, no timestamps).
"""
from __future__ import annotations

import argparse
import collections
import dataclasses
import datetime
import os
import re
import sqlite3
import sys
import zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

JA = re.compile(r"[぀-ヿ㐀-鿿ｦ-ﾟ]")
CODE = re.compile(r"(?<![A-Za-z0-9])(c[cmnp]\d{3,4})")
SCRIPT_ID = re.compile(r"^([0-9A-Z][0-9A-Za-z]{3}_\d{3})_")
VOICE_PLAY = re.compile(r"\((\w+):(\w+)\)")


# ---------------------------------------------------------------- data
@dataclasses.dataclass
class Person:
    """One master_person row (a character variant, an enemy or an NPC)."""
    label: str
    code: str               # cp0302
    ja: str
    en: str                 # "" when unknown
    en_official: bool
    playable: bool          # has a role_% row
    rarity: str = ""        # e.g. "5,6"
    opened_at: str = ""     # earliest role opened_at (JST)
    released: bool = False  # earliest role opened_at <= s_end
    dummy: bool = False
    en_va: str = ""         # English voice actor (profile prmsg_10), official only


@dataclasses.dataclass
class VoiceFile:
    """One voice file path with what names it and who uses it."""
    path: str
    kind: str               # battle / battle params / gacha / event menu / skill SE / story
    rule: str               # (a)/(b)/(d) label of the path rule
    columns: set = dataclasses.field(default_factory=set)
    users: set = dataclasses.field(default_factory=set)   # person labels
    notes: set = dataclasses.field(default_factory=set)
    derived_from: str = ""  # for -en companions: the Japanese pack
    jp_same: bool = False
    in_hand: str = ""       # "download" / "APK" / ""


# ---------------------------------------------------------------- small helpers
def norm(p: str) -> str:
    """Logical asset path: drop everything up to builtin_data/ or assetpack/, fold etc2 folders."""
    p = p.replace("\\", "/")
    for m in ("builtin_data/", "assetpack/"):
        i = p.find(m)
        if i >= 0:
            p = p[i + len(m):]
    return re.sub(r"/etc2(/hi)?/", "/", p)


def has_ja(s: str) -> bool:
    return bool(JA.search(s or ""))


def parse_time(s: str):
    """'2019/11/6 14:00:00' or '2018-08-21 17:30:00' -> datetime (None if empty)."""
    if not s:
        return None
    s = s.strip().replace("/", "-")
    d, _, t = s.partition(" ")
    y, m, dd = (int(x) for x in d.split("-"))
    hh, mm, ss = (int(x) for x in (t or "0:0:0").split(":"))
    return datetime.datetime(y, m, dd, hh, mm, ss)


def en_companion(path: str) -> str:
    """Sound/Voice_x.spk -> Sound/Voice_x-en.spk: CLanguage::PostfixLanguageCodeFilepath's
    "%.*s-%s%s" (stem, code, extension)."""
    stem, ext = os.path.splitext(path)
    return f"{stem}-en{ext}"


def is_language_pack(path: str) -> bool:
    """FileExistLanguage's test: the file name contains "Voice_" and the extension ".spk"."""
    tail = path.rsplit("/", 1)[-1]
    return "Voice_" in tail and tail.endswith(".spk")


def anchor(code: str) -> str:
    return "ch-" + code


def md_escape(s: str) -> str:
    return (s or "").replace("|", "\\|").replace("\\n", " ").replace("\n", " ")


# ---------------------------------------------------------------- sources
def source_files(download: str | None, apk: str | None) -> dict:
    """logical path -> source label, the download first, then the APK (non-empty files only)."""
    out = {}
    if download and os.path.isdir(download):
        for dp, _, fs in os.walk(download):
            for f in fs:
                fp = os.path.join(dp, f)
                if os.path.getsize(fp) > 0:
                    out.setdefault(norm(os.path.relpath(fp, download)), "download")
    if apk and os.path.isfile(apk):
        with zipfile.ZipFile(apk) as z:
            for i in z.infolist():
                if i.file_size > 0 and not i.is_dir():
                    out.setdefault(norm(i.filename), "APK")
    return out


def jp_playable(jp: sqlite3.Connection | None) -> set:
    """Person labels that have a role_% row in the JP 3.7.0 master."""
    if jp is None:
        return set()
    return {r[0] for r in jp.execute("select distinct p.id_label from master_role r join master_person p "
                                     "on p.id = r.master_person_id where r.id_label like 'role_%'")}


def jp_named(jp: sqlite3.Connection | None) -> set:
    """Every voice path the JP 3.7.0 master names (same column rules)."""
    out = set()
    if jp is None:
        return out
    cols = {
        "master_person": ["voice_parameter", "voice_sound_package", "menu_voice_sound_package",
                          "home_voice_sound_package", "home_voice_sound_package_sub",
                          "gacha_voice_package"],
        "master_voice_switch": ["voice_parameter", "voice_sound_package", "menu_voice_sound_package",
                                "home_voice_sound_package", "home_voice_sound_package_sub"],
        "master_menu_common_voice": ["voice_sound_package"],
        "master_event_area": ["voice_menu_pack_name"],
        "master_stamp": ["sound_resource"],
        "master_skill": ["se_sound_package", "se_sound_package1", "se_sound_package2", "se_sound_package3"],
    }
    tables = {r[0] for r in jp.execute("select name from sqlite_master where type='table'")}
    for t, cs in cols.items():
        if t not in tables:
            continue
        have = {r[1] for r in jp.execute(f"pragma table_info({t})")}
        for c in cs:
            if c not in have:
                continue
            for (v,) in jp.execute(f"select distinct {c} from {t} where {c} is not null and {c} != ''"):
                out.add(f"Parameter/Battle/{v}.msgp" if c == "voice_parameter" else f"Sound/{v}.spk")
    return out


# ---------------------------------------------------------------- the Global master
class Global:
    """Reads the Global master: persons, their names and release state, and the voice columns."""

    def __init__(self, con: sqlite3.Connection):
        self.c = con
        self.c.row_factory = sqlite3.Row
        self.en, self.ja = {}, {}
        for r in self.c.execute("select lang, message_id, text_value from master_text"):
            (self.en if r["lang"] == "en" else self.ja)[r["message_id"]] = r["text_value"] or ""
        row = self.c.execute("select value from master_global where key='s_end'").fetchone()
        self.s_end = parse_time(row[0]) if row else None
        self.persons = self._persons()

    def _names_en(self, label, ja):
        try:
            from soa_save.master import english_name
        except Exception:  # pragma: no cover - soa_save is part of the repo
            return None
        return english_name(label, ja)

    def profile(self, label: str, n: int) -> str:
        """The person's profile line prmsg_<n> (variants _2.._9 share the base's profile)."""
        for k in (label, re.sub(r"_\d+$", "", label)):
            v = self.en.get(f"{k}_prmsg_{n:02d}")
            if v is not None:
                return v
        return ""

    def _persons(self) -> dict:
        roles = collections.defaultdict(list)
        for r in self.c.execute("select master_person_id, rarity, opened_at from master_role "
                                "where id_label like 'role_%'"):
            roles[r["master_person_id"]].append(r)
        out = {}
        for p in self.c.execute("select id, id_label, name_message_id from master_person"):
            label = p["id_label"]
            ja = (self.ja.get(p["name_message_id"] or "", "") or "").replace("\\n", " ").strip()
            en = (self.en.get(p["name_message_id"] or "", "") or "").replace("\\n", " ").strip()
            official = bool(en) and not has_ja(en)
            if not official:
                en = self._names_en(label, ja) or ""
            rs = roles.get(p["id"], [])
            per = Person(label=label, code=label.split("_")[0], ja=ja, en=en, en_official=official,
                         playable=bool(rs), dummy="ダミー" in ja or ja.startswith("※"))
            if rs:
                per.rarity = ",".join(sorted({str(r["rarity"]) for r in rs if r["rarity"] is not None}))
                per.opened_at = min((r["opened_at"] or "") for r in rs)
                t = parse_time(per.opened_at)
                per.released = bool(t and self.s_end and t <= self.s_end)
                va = self.profile(label, 10).replace("\\n", " ").strip()
                per.en_va = va if va and not has_ja(va) else ""
            out[label] = per
        return out


# ---------------------------------------------------------------- collection
def collect(gl: Global) -> dict:
    """path -> VoiceFile for every voice file the Global master names, plus the -en companions."""
    files: dict[str, VoiceFile] = {}

    def add(path, kind, col, user=None, note=None, rule="(b)"):
        f = files.setdefault(path, VoiceFile(path=path, kind=kind, rule=rule))
        f.columns.add(col)
        if user:
            f.users.add(user)
        if note:
            f.notes.add(note)

    c = gl.c
    for p in c.execute("select id_label, voice_parameter, voice_sound_package, gacha_voice_package, "
                       "gacha_voice_queue from master_person"):
        if p["voice_parameter"]:
            add(f"Parameter/Battle/{p['voice_parameter']}.msgp", "battle params",
                "master_person.voice_parameter", p["id_label"])
        if p["voice_sound_package"]:
            add(f"Sound/{p['voice_sound_package']}.spk", "battle", "master_person.voice_sound_package",
                p["id_label"])
        if p["gacha_voice_package"]:
            add(f"Sound/{p['gacha_voice_package']}.spk", "gacha", "master_person.gacha_voice_package",
                p["id_label"], f"cue {p['gacha_voice_queue']}" if p["gacha_voice_queue"] else None)
    for a in c.execute("select id_label, voice_menu_pack_name, voice_menu_cue_min, voice_menu_cue_max "
                       "from master_event_area where voice_menu_pack_name is not null and "
                       "voice_menu_pack_name != '' order by id_label"):
        add(f"Sound/{a['voice_menu_pack_name']}.spk", "event menu", "master_event_area.voice_menu_pack_name",
            note=f"{a['id_label']} (cues {a['voice_menu_cue_min']}-{a['voice_menu_cue_max']})")
    # skills that play a voice pack as their SE: attribute them to the roles that have the skill
    skill_cols = [r[1] for r in c.execute("pragma table_info(master_skill)") if r[1].startswith("se_sound_package")]
    role_cols = [r[1] for r in c.execute("pragma table_info(master_role)")
                 if re.fullmatch(r"(master_skill\d|rush_skill\d)_id", r[1])]
    for col in skill_cols:
        for s in c.execute(f"select id, id_label, {col} as pk from master_skill where {col} like 'Voice%'"):
            users = set()
            for rc in role_cols:
                for (pl,) in c.execute(f"select p.id_label from master_role r join master_person p "
                                       f"on p.id = r.master_person_id where r.{rc} = ?", (s["id"],)):
                    users.add(pl)
            path = f"Sound/{s['pk']}.spk"
            if path in files:
                files[path].columns.add(f"master_skill.{col}")
                files[path].notes.add(f"also the SE of skill {s['id_label']}")
            else:
                add(path, "skill SE", f"master_skill.{col}", note=f"skill {s['id_label']}")
            for u in users:
                files[path].users.add(u)
    # the English dub companions
    for f in sorted(list(files.values()), key=lambda f: f.path):
        if not is_language_pack(f.path):
            continue
        vas = sorted(u for u in f.users if gl.persons.get(u) and gl.persons[u].en_va)
        if vas:
            e = files.setdefault(en_companion(f.path), VoiceFile(
                path=en_companion(f.path), kind=f.kind + " (English dub)", rule="(b)+(d)",
                derived_from=f.path))
            e.columns.add("derived: -en of " + f.path)
            e.users.update(vas)
    return files


def mark(files: dict, jp_names: set, have: dict) -> None:
    """Fill jp_same and in_hand."""
    for f in files.values():
        f.in_hand = have.get(f.path, "")
        f.jp_same = f.path in jp_names or bool(f.in_hand)


@dataclasses.dataclass
class StoryPack:
    path: str
    scripts: set
    gl_scripts: set
    english_scripts: set
    speakers: set
    in_hand: str = ""


def story_packs(gl: Global, scripts_dir: str | None, have: dict) -> list:
    """Voice_TS packs that the JP scripts of Global-text chapters play (assumption (d))."""
    if not scripts_dir or not os.path.isdir(scripts_dir):
        return []
    from soa_save import script as S
    lines, eng = collections.Counter(), collections.Counter()
    for r in gl.c.execute("select lang, message_id, text_value from master_text where "
                          "data_type='package' and category_id_label != 'system'"):
        m = SCRIPT_ID.match(r["message_id"])
        if not m or r["lang"] != "en":
            continue
        lines[m.group(1)] += 1
        if r["text_value"] and not has_ja(r["text_value"]):
            eng[m.group(1)] += 1
    packs: dict[str, StoryPack] = {}
    for fn in sorted(os.listdir(scripts_dir)):
        if not fn.endswith(".msgp"):
            continue
        with open(os.path.join(scripts_dir, fn), "rb") as fh:
            obj = S.load(fh.read(), f"Script/{fn}")
        for sid, cmds in sorted(obj.get("Script", {}).items()):
            for cmd in cmds:
                if S.command_name(cmd.get("command_type", -1)) != "VoicePlay":
                    continue
                m = VOICE_PLAY.fullmatch(str(cmd.get("command_param0")))
                if not m:
                    continue
                path = f"Sound/{m.group(1)}.spk"
                sp = packs.setdefault(path, StoryPack(path, set(), set(), set(), set()))
                sp.scripts.add(sid)
                if sid in lines:
                    sp.gl_scripts.add(sid)
                    if eng[sid] * 2 > lines[sid]:
                        sp.english_scripts.add(sid)
                    sp.speakers.update(CODE.findall(m.group(2)))
    out = [p for p in packs.values() if p.gl_scripts]
    for p in out:
        p.in_hand = have.get(p.path, "")
    return sorted(out, key=lambda p: p.path)


# ---------------------------------------------------------------- output
def write_txt(files: dict, path: str) -> None:
    with open(path, "w", encoding="utf-8") as f:
        for p in sorted(files):
            f.write(p + "\n")


def character_name(gl: Global, code: str) -> tuple:
    """(Japanese, English, official?) of a character code from its first playable, non-dummy variant."""
    ps = sorted((p for p in gl.persons.values() if p.code == code and p.playable and not p.dummy),
                key=lambda p: (not p.released, p.label)) or \
        sorted((p for p in gl.persons.values() if p.code == code), key=lambda p: p.label)
    base = next((p for p in ps if p.label.endswith("_b01a") or p.label.endswith("_b01b")), ps[0])
    return base.ja, base.en, base.en_official


def en_cell(p_en: str, official: bool) -> str:
    if not p_en:
        return "—"
    return md_escape(p_en) + ("" if official else " (tr.)")


def owner_code(gl: Global, f: VoiceFile) -> str | None:
    """The character a file belongs to: the playable persons' code (the smallest when several)."""
    codes = sorted({gl.persons[u].code for u in f.users if u in gl.persons and gl.persons[u].playable})
    return codes[0] if codes else None


def write_md(gl: Global, files: dict, story: list, path: str, jp_play: set = frozenset()) -> None:
    L = []
    w = L.append
    fs = sorted(files.values(), key=lambda f: (f.derived_from or f.path, bool(f.derived_from)))
    master = [f for f in fs if not f.derived_from]
    derived = [f for f in fs if f.derived_from]
    by_code = collections.defaultdict(list)
    other = []
    for f in fs:
        oc = owner_code(gl, f)
        (by_code[oc].append(f) if oc else other.append(f))
    chars = sorted(by_code)
    released_chars = [c for c in chars if any(p.released for p in gl.persons.values()
                                              if p.code == c and p.playable)]
    kinds = collections.Counter(f.kind for f in master)
    jp_same = sum(f.jp_same for f in master)
    hand = sum(bool(f.in_hand) for f in fs)
    w("# Global voice files")
    w("")
    w("The voice files that the **Global (English) master** `data/basmaster-gl.sqlite3` names or implies, with the "
      "characters they belong to. Generated by `tools/global_voice_files.py` (re-run it to refresh); the file list "
      "alone is [`global-voice-files.txt`](global-voice-files.txt). The Global master is described in "
      "[basmaster-gl.md](basmaster-gl.md); rule labels (a) master data, (b) client-side evidence, (d) assumption are "
      "those of [server-rules.md](server-rules.md).")
    w("")
    w("## Summary")
    w("")
    w(f"- **{len(fs)} files** in the list: **{len(master)} named by the Global master** "
      f"({', '.join(f'{n} {k}' for k, n in sorted(kinds.items()))}) and **{len(derived)} English-dub "
      "companions** (`-en.spk`) derived from the client's voice-language rule.")
    w(f"- **Every master-named file has a JP 3.7.0 name: {jp_same} of {len(master)}.** The Global master names no "
      "Global-only voice file, so these are the same Japanese voices as JP's (the JP client also plays the bare name "
      "as the Japanese voice, see [Method](#method)).")
    w(f"- **Global-only names: the {len(derived)} `-en` companions**, the English dub. The master doesn't name them; "
      "the client builds them from the Japanese pack's name when the voice language is English. Which ones Global "
      "shipped is inferred from the characters whose profile names an English voice actor. "
      f"{sum(1 for f in derived if not any(gl.persons[u].released for u in f.users if u in gl.persons))} of them "
      "belong only to variants scheduled after the end of service (recorded, probably never shipped). None is in "
      "hand: the JP download has no `-en` file.")
    w(f"- **In hand: {hand} of {len(fs)}** ({sum(bool(f.in_hand) for f in master)} of the {len(master)} master-named "
      f"files, in the 3.7.0 download or APK). Missing master-named files: "
      + (", ".join(f"`{f.path}`" for f in master if not f.in_hand) or "none") + ".")
    w(f"- **Characters: {len(chars)}** with voice files (playable characters of the Global master), "
      f"{len(released_chars)} of them released in Global before the end of service "
      f"({gl.s_end:%Y-%m-%d %H:%M} JST); the others were in its data but never released. "
      f"{len(other)} files belong to enemies, NPCs or event menus only ([Other voice files](#other)).")
    if story:
        w(f"- **Story voices** are not named by the Global master. [Story voice packs](#story) lists the "
          f"{len(story)} `Voice_TS_*` packs that the JP scripts of chapters with Global text play; they are an "
          "assumption (d) and are not in the `.txt`.")
    w("- **Not covered:** home-screen voices (the Global master has no `home_voice_*` column; its 1.5.0 client found "
      "them some other way, not in hand), menu voices (`menu_voice_*`, JP-only columns), stamp voices "
      "(`master_stamp.voice_resource` is a Global-only column with no non-empty row), the title and navigation "
      "voices the client names itself, and the scripts of Global's own event stories (`TS_A*`, `TS_B*`).")
    w("")
    w("Columns: **kind** battle (battle voice pack), battle params (its cue parameters), gacha (the gacha "
      "draw voice), event menu, skill SE, and the English dub of each; **JP** = the same name is a JP 3.7.0 file "
      "(named by the JP master or held by the download); **in hand** = the 3.7.0 download or APK holds it; "
      "**rule** = the source label of the path. English names without \"(tr.)\" are the Global master's own; "
      "\"(tr.)\" marks names that are not official (from `soa_save/names_en.json`).")
    w("")
    w("## Contents")
    w("")
    w("- [Summary](#summary)")
    w("- Characters")
    for code in chars:
        ja, en, off = character_name(gl, code)
        rel = "" if code in released_chars else " (unreleased)"
        w(f"  - [`{code}` {md_escape(ja)} / {en_cell(en, off)}{rel}](#{anchor(code)})")
    w("- [Other voice files (enemies, NPCs, event menus)](#other)")
    if story:
        w("- [Story voice packs](#story)")
    w("- [Method](#method)")
    w("")
    w("## Characters")
    for code in chars:
        ja, en, off = character_name(gl, code)
        w("")
        w(f'<a id="{anchor(code)}"></a>')
        w("")
        w(f"### `{code}` {md_escape(ja)} / {en_cell(en, off)}")
        w("")
        vs = sorted((p for p in gl.persons.values() if p.code == code and p.playable),
                    key=lambda p: p.label)
        w("| Variant | Japanese | English | Rarity | Global | English VA |")
        w("|---|---|---|---|---|---|")
        for p in vs:
            st = ("released " if p.released else "unreleased, scheduled ") + (p.opened_at or "")[:10]
            if p.dummy:
                st = "test/dummy role"
            w(f"| `{p.label}` | {md_escape(p.ja)} | {en_cell(p.en, p.en_official)} | {p.rarity} | {st} | "
              f"{md_escape(p.en_va) or '—'} |")
        w("")
        w("| File | Kind | Used by | JP | In hand | Rule |")
        w("|---|---|---|---|---|---|")
        for f in by_code[code]:
            users = sorted(u for u in f.users if gl.persons.get(u) and gl.persons[u].code == code
                           and gl.persons[u].playable)
            npc = sorted(u for u in f.users if u not in users)
            used = ", ".join(f"`{u}`" for u in users)
            if npc:
                used += f" (+{len(npc)} other rows: " + ", ".join(f"`{u}`" for u in npc[:4]) + \
                    (", …" if len(npc) > 4 else "") + ")"
            note = "; ".join(sorted(f.notes))
            kind = f.kind + (f" ({md_escape(note)})" if note else "")
            w(f"| `{f.path}` | {kind} | {used} | {'yes' if f.jp_same else 'no'} | "
              f"{f.in_hand or 'no'} | {f.rule} |")
    w("")
    w('<a id="other"></a>')
    w("")
    w("## Other voice files (enemies, NPCs, event menus)")
    w("")
    w("Files no playable person of the Global master uses: enemy and NPC packs (named by their `master_person` "
      "rows), the packs of persons that are playable only in JP (the Global master has their person row but no "
      "role, e.g. Coro `cp0003` and the Tales of Phantasia collaboration; marked), and the event menus' voice packs "
      "(`master_event_area.voice_menu_pack_name`, with the cue range each area plays).")
    w("")
    w("| File | Kind | Used by | JP | In hand | Rule |")
    w("|---|---|---|---|---|---|")
    for f in other:
        if f.users:
            names = []
            for u in sorted(f.users):
                p = gl.persons.get(u)
                nm = md_escape(p.ja) if p else ""
                if p and p.en and p.en != p.ja:
                    nm += " / " + en_cell(p.en, p.en_official)
                if u in jp_play:
                    nm += " (playable in JP, no Global role)"
                names.append(f"`{u}` {nm}".strip())
            used = ", ".join(names[:6]) + (f", … ({len(names)} rows)" if len(names) > 6 else "")
        else:
            notes = sorted(f.notes)
            used = ", ".join(md_escape(n) for n in notes[:6]) + (f", … ({len(notes)} areas)" if len(notes) > 6 else "")
        w(f"| `{f.path}` | {f.kind} | {used} | {'yes' if f.jp_same else 'no'} | {f.in_hand or 'no'} | {f.rule} |")
    if story:
        w("")
        w('<a id="story"></a>')
        w("")
        w("## Story voice packs")
        w("")
        w("Assumption (d), not in the `.txt`: the Global master holds story **text** (`master_text` rows with "
          "`data_type = 'package'`, message ids `<script>_<line>`), not voice references. A story voice is named by a "
          "`VoicePlay` command, `(<pack>:<cue>)`, inside `Script/<script>.msgp`. These are the packs that the JP "
          "3.7.0 scripts play in the scripts whose lines the Global master has (\"English\": more than half of the "
          "script's Global `en` lines are English). Speakers are the character codes in the cue names. Global's own "
          "event stories (`TS_A*`, `TS_B*`) have no script in hand, so their voices are unknown.")
        w("")
        w("| File | Scripts with Global text (English) | Speakers | In hand |")
        w("|---|---|---|---|")
        for p in story:
            sc = ", ".join(sorted(p.gl_scripts))
            spk = ", ".join(f"`{c}` {md_escape(character_name(gl, c)[0])}" if any(q.code == c for q in gl.persons.values())
                            else f"`{c}`" for c in sorted(p.speakers))
            w(f"| `{p.path}` | {sc} ({len(p.english_scripts)} English) | {spk or '—'} | {p.in_hand or 'no'} |")
    w("")
    w('<a id="method"></a>')
    w("")
    w("## Method")
    w("")
    w("Everything is recomputed by `tools/global_voice_files.py` from `--gl` (the Global master), `--jp` (the JP 3.7.0 "
      "master), `--download` (the 3.7.0 download) and `--apk` (the 3.7.0 APK). Nothing is hard-coded.")
    w("")
    w("**Path rules.**")
    w("")
    w("| Column | Path | Label and evidence |")
    w("|---|---|---|")
    w("| `master_person.voice_parameter` | `Parameter/Battle/<x>.msgp` | (b): the 3.7.0 client has the string "
      "`Parameter/Battle/`; the download holds `Parameter/Battle/voice_*.msgp` under exactly these names (all but "
      "the missing ones listed in the summary) |")
    w("| `master_person.voice_sound_package`, `gacha_voice_package`, `master_event_area.voice_menu_pack_name`, "
      "`master_skill.se_sound_package*` | `Sound/<x>.spk` | (b): the client's `Sound/` and `.spk` strings and "
      "`CGameResourceManager::FileExistLanguage`'s `Voice_`/`.spk` test; the download's `Sound/` holds these names |")
    w("| (derived) | `Sound/<stem>-en.spk` | (b) for the name, (d) for which exist: see below |")
    w("| `VoicePlay` `(<pack>:<cue>)` in `Script/*.msgp` | `Sound/<pack>.spk` | (b) the download holds the packs; "
      "(d) that Global's scripts played the same packs |")
    w("")
    w("**The English dub rule** (3.7.0 client, `work/libSOA-3.7.0.so`; label (b)). "
      "`CGameResourceManager::FileExistLanguage` (vaddr 0x17f8634) first tests the file name: when the tail contains "
      "`Voice_` and the extension `.spk`, it calls `CLanguage::PostfixLanguageCodeFilepath(path, CLanguage::Voice(), "
      "true)` and checks that file before the plain one. `PostfixLanguageCodeFilepath` (0x13b4c18) formats "
      "`\"%.*s-%s%s\"` (stem, language code, extension), so `Sound/Voice_cp0302.spk` becomes "
      "`Sound/Voice_cp0302-en.spk` for English (code 1, `\"en\"`). For Japanese (code 0) it maps the language to "
      "`none` and strips any suffix, so **the Japanese voice is the bare name**. The voice language is the local "
      "setting `BAS:VoiceLanguage` (`CUIUtility::GetVoiceLanguage` / `SetVoiceLanguage`, values 0 ja, 1 en). The "
      "rule covers every `Voice_*.spk` (battle, gacha, event menu, story) and not `Parameter/Battle/voice_*.msgp`, "
      "whose names start with a lower-case `voice_`.")
    w("")
    w("Global master evidence that Global used it (label (a)): `uimsg_menu_voice_language_title` \"Voice\", "
      "`uimsg_menu_voice_language-ja` \"Japanese\", `uimsg_menu_voice_language-en` \"English\", "
      "`uimsg_menu_voice_language_explan` \"Switch between languages in the character voice settings.\", "
      "`uimsg_ch_profile_voiceactor_en` \"English VA:\", and the profiles' `<person>_prmsg_10` lines, which name "
      f"the English voice actor ({sum(1 for p in gl.persons.values() if p.en_va)} playable persons have an English "
      "one; the unreleased ones hold the Japanese placeholder `【メモ】英語版の声優名が入る項目です`, \"memo: the "
      "English version's voice-actor name goes here\").")
    w("")
    w("Assumption (d): the Global 1.5.0 client isn't in hand, so the list assumes it had the same rule and shipped "
      "an `-en` pack for every `Voice_*.spk` (battle, gacha, the skill SE pack) of a playable person whose profile "
      "names an English voice actor, released or not, and none for packs used only by persons with no English "
      "voice actor (enemies, NPCs, persons whose profile holds the Japanese placeholder) or by no playable person "
      "(the event-menu packs, whose speakers the master doesn't say).")
    w("")
    w("**JP same-name and in hand.** \"JP\" is yes when the JP 3.7.0 master names the path under the same column "
      "rules (plus `menu_voice_*`, `home_voice_*`, `master_voice_switch`, `master_menu_common_voice`, "
      "`master_stamp.sound_resource`) or a source holds it. \"In hand\" is the 3.7.0 download, else the 3.7.0 APK "
      "(non-empty files; `builtin_data/` stripped as in `tools/missing_assets.py`).")
    w("")
    w("**Characters and names.** A character is a person code (`cp0302`) with at least one playable variant "
      "(`master_person` with a `role_%` row in `master_role`). A file goes to the character whose playable "
      "variants use it; files no playable person uses go to [Other](#other). Release: a variant is released when "
      "its earliest role `opened_at` is at or before `master_global.s_end` (as in basmaster-gl.md section 6). "
      "Rarity is the set of its roles' `rarity`. English names: the Global master's `en` text of "
      "`name_message_id` when it has no kana or kanji, else `soa_save/names_en.json` marked \"(tr.)\".")
    w("")
    with open(path, "w", encoding="utf-8") as f:
        f.write("\n".join(L))


# ---------------------------------------------------------------- main
def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--gl", default=os.path.join(ROOT, "data/basmaster-gl.sqlite3"))
    ap.add_argument("--jp", default=os.path.join(ROOT, "data/basmaster-3.7.0.sqlite3"))
    ap.add_argument("--download", default=os.path.join(ROOT, "work/download-3.7.0"))
    ap.add_argument("--apk", default=os.path.join(ROOT, "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk"))
    ap.add_argument("--scripts", default=None, help="Script/ directory (default: <download>/Script)")
    ap.add_argument("--txt", default=os.path.join(ROOT, "docs/global-voice-files.txt"))
    ap.add_argument("--md", default=os.path.join(ROOT, "docs/global-voice-files.md"))
    a = ap.parse_args(argv)
    gl = Global(sqlite3.connect(f"file:{a.gl}?mode=ro", uri=True))
    jp = sqlite3.connect(f"file:{a.jp}?mode=ro", uri=True) if a.jp and os.path.exists(a.jp) else None
    have = source_files(a.download, a.apk)
    files = collect(gl)
    mark(files, jp_named(jp), have)
    story = story_packs(gl, a.scripts or os.path.join(a.download or "", "Script"), have)
    write_txt(files, a.txt)
    write_md(gl, files, story, a.md, jp_playable(jp))
    master = [f for f in files.values() if not f.derived_from]
    print(f"{len(files)} files ({len(master)} master-named, {len(files) - len(master)} -en), "
          f"{sum(f.jp_same for f in master)} JP same-name, {sum(bool(f.in_hand) for f in files.values())} in hand, "
          f"{len(story)} story packs")


if __name__ == "__main__":
    main()
