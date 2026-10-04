#!/usr/bin/env python3
"""List the files that events and gacha banners of the 3.7.0 master reference but no source has.

  .venv/bin/python tools/missing_assets.py [--db data/basmaster-3.7.0.sqlite3]
        [--download work/download-3.7.0] [--apk apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk]
        [--standins standin-assets]
        [--gl data/basmaster-gl.sqlite3] [--names docs/missing-assets-names.tsv]
        [--md docs/missing-assets-3.7.0.md] [--json OUT] [--residue OUT]

What an event or a gacha banner references (the master columns; the path rules and their labels
are printed in the document's "Path rules" section):
  event   master_event_area.bg_resource                         Image/<x>.aif
          master_banner.image (area.master_banner_id(_label); banners whose target_content_type = 3
            point at the area; master_banner_replace.image of their replace type)  Image/<x>.aif
          master_event_area.voice_menu_pack_name                Sound/<x>.spk
          master_event_mission.talk_event_id_label / talk_message_file   Script/<x>.msgp, Scenario/<x>.msgp
          master_mission_stage (by master_mission_id) map (through master_replace_resource res_type 4
            of the area's resource_replace_group_id) BG/<x>.asf/.aaf/.acf, stage_bgm Sound/<x>.aac,
            boss_icon Image/<x>.aif, the enemy party's persons (master_enemy_base_parameter ->
            master_person): Character/<asf>.asf, Character/<acf>.acf, Motion/<apk>.apk,
            Character/<unique_apk>.apk
          master_world_boss.enemy_icon (area.event_id_label = world boss id_label)  Image/<x>.aif
  gacha   grouped by master_gacha.banner_id (one list banner; step-up chains share it):
          master_banner.image (id_label = banner_id; banners whose target_content_type = 1 point at
            a gacha of the group; master_banner_replace.image)  Image/<x>.aif
          master_gacha.image1..image4, master_gacha_image.image_resource   Image/<x>.aif
          master_gacha.resource_replace_group_id -> master_replace_resource.replace_res (res_type 4)
            BG/<x>.asf/.aaf/.acf
A file is present when a source holds it (logical names: everything up to builtin_data/ or
assetpack/ dropped, the etc2/ and etc2/hi/ quality folders folded away; zero-size files don't
count). Sources in priority order: the 3.7.0 download, the 3.7.0 APK, the repo's stand-ins.

"What it probably is" comes from the referencing column and row, the subject (gacha title,
pick-up role / weapon, mission, person) and the size / format of existing files of the same name
pattern (digits folded), read from their AIF image header. Everything is recomputed; nothing is
hard-coded except the phrase glossary for translating titles. Names: the Global master's English
text when it has no kana / kanji, else soa_save/names_en.json for characters, else the
hand-written --names TSV (Japanese text -> English), else the phrase glossary. Output is
deterministic.
"""
import argparse
import collections
import json
import os
import re
import sqlite3
import struct
import sys
import unicodedata
import zipfile
import zlib

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
from soa_save.adld import chash32  # noqa: E402

try:
    import zstandard
except ImportError:  # sizes of zstd images are then unknown
    zstandard = None

JA = re.compile(r"[\u3040-\u30ff\u3400-\u9fff\uff66-\uff9f]")


# ---------------------------------------------------------------- sources
def norm(p):
    p = p.replace("\\", "/")
    for m in ("builtin_data/", "assetpack/"):
        i = p.find(m)
        if i >= 0:
            p = p[i + len(m):]
    return re.sub(r"/etc2(/hi)?/", "/", p)


class Source:
    def __init__(self, label, path):
        self.label, self.path, self.files = label, path, {}
        self.zip = None
        if not path or not os.path.exists(path):
            return
        if os.path.isdir(path):
            for dp, _, fs in os.walk(path):
                for f in fs:
                    fp = os.path.join(dp, f)
                    if os.path.getsize(fp) > 0:
                        self.files.setdefault(norm(os.path.relpath(fp, path)), fp)
        else:
            self.zip = zipfile.ZipFile(path)
            for i in self.zip.infolist():
                if i.file_size > 0 and not i.is_dir():
                    self.files.setdefault(norm(i.filename), i.filename)

    def read(self, logical, limit=None):
        p = self.files[logical]
        if self.zip:
            with self.zip.open(p) as f:
                return f.read(limit) if limit else f.read()
        with open(p, "rb") as f:
            return f.read(limit) if limit else f.read()

    def stored_name(self, logical):
        """The name the file's ADLD key is made from (relative to builtin_data / assetpack)."""
        p = self.files[logical]
        if self.zip:
            return re.sub(r"^.*?(builtin_data/|assetpack/)", "", p)
        return os.path.relpath(p, self.path)


def image_info(src, logical):
    """(width, height, format) from an Image/ file's AIF image header, or None."""
    try:
        d = src.read(logical, 0x40000)
    except (KeyError, OSError):
        return None
    if d[:4] == b"ADLD":
        fl = struct.unpack_from("<I", d, 4)[0]
        body = d[16:]
        if fl & 1:
            k = b"%x" % chash32(src.stored_name(logical).encode())
            kk = (k * (len(body) // len(k) + 1))[:len(body)]
            body = bytes(a ^ b for a, b in zip(body, kk))
        d = body
    if d[:3] == b"SLZ":
        codec, dsz = d[3], struct.unpack_from("<i", d, 0xc)[0]
        off = struct.unpack_from("<I", d, 0x14)[0]
        want = min(d[0x19] * 1024 if d[0x19] else dsz, dsz)
        try:
            if codec == 0:
                d = d[off:off + want]
            else:
                n = struct.unpack_from("<H", d, off)[0]
                p = off + 2
                if n == 0:
                    d = d[p:p + want]
                elif codec == 7 and zstandard:
                    d = zstandard.ZstdDecompressor().decompressobj().decompress(d[p:p + n])
                elif codec == 5:
                    d = zlib.decompressobj(-15).decompress(d[p:p + n])
                else:
                    return None
        except Exception:  # noqa: BLE001 - a broken file just has no known size
            return None
    for i in range(0, len(d) - 0x30, 16):
        if d[i:i + 4] == b"Xgmi":
            w, h = struct.unpack_from("<HH", d, i + 0x28)
            fmt = {39: "JPEG", 47: "ETC2 RGB", 48: "ETC2 RGB+A1", 49: "ETC2 RGBA"}.get(d[i + 0x20], f"fmt {d[i + 0x20]}")
            return w, h, fmt
    return None


# ---------------------------------------------------------------- names
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


class Names:
    def __init__(self, c, gl_path, tsv_path):
        self.c = c
        self.ja = {r[0]: r[1] for r in c.execute("select message_id, text_value from master_text")}
        self.gl, self.gl_text = {}, {}  # message id -> English; Japanese text -> English
        if gl_path and os.path.exists(gl_path):
            g = sqlite3.connect(f"file:{gl_path}?mode=ro", uri=True)
            pairs = g.execute("select j.message_id, j.text_value, e.text_value from master_text j join master_text e "
                              "on e.message_id = j.message_id and e.lang = 'en' where j.lang = 'ja' order by j.message_id")
            for mid, tj, te in pairs:
                te = self.key(te)
                if not te or JA.search(te):
                    continue
                # only where the Global Japanese text is the 3.7.0 one (GL is an older revision)
                if self.key(tj) == self.key(self.ja.get(mid, "")):
                    self.gl[mid] = te
                self.gl_text.setdefault(self.key(tj), te)
        self.tsv = {}
        if tsv_path and os.path.exists(tsv_path):
            for line in open(tsv_path, encoding="utf-8"):
                if line.strip() and not line.startswith("#") and "\t" in line:
                    k, v = line.rstrip("\n").split("\t", 1)
                    self.tsv[self.key(k)] = v
        ne = json.load(open(os.path.join(ROOT, "soa_save", "names_en.json"), encoding="utf-8"))
        ne["titles"].update({"渚の": "Seaside", "涙目": "Tearful"})  # official GL wording (docs/basmaster-gl.md)
        self.people = {}  # Japanese person name -> English
        for label, mid in c.execute("select id_label, name_message_id from master_person"):
            jn = self.ja.get(mid)
            if not jn or JA.search(jn) is None:
                continue
            en = self.gl.get(mid) or self._en_person(ne, label, jn)
            if en:
                self.people.setdefault(unicodedata.normalize("NFKC", jn), en)
        for code, (bj, be, _full) in ne["characters"].items():
            self.people.setdefault(bj, be)
        self.residue = collections.Counter()

    @staticmethod
    def _en_person(ne, label, jn):
        ch = ne["characters"].get((label or "").split("_")[0])
        if not ch:
            return None
        base_ja, base_en = ch[0], ch[1]
        rest, suffix = jn, ""
        for sj, se in ne["suffixes"].items():
            if rest.endswith(sj):
                rest, suffix = rest[:-len(sj)], se
        if base_ja not in rest:
            return None
        prefix = rest[:rest.rindex(base_ja)]
        if not prefix:
            return base_en + suffix
        title = ne["titles"].get(prefix)
        if title is None:
            return None
        return (title + base_en if title.endswith("-") else f"{title} {base_en}") + suffix

    @staticmethod
    def key(s):
        return re.sub(r"\s+", " ", unicodedata.normalize("NFKC", s or "").replace("\\n", " ")).strip()

    def text(self, mid):
        return self.key(self.ja.get(mid or "", ""))

    def english(self, mid, ja=None):
        """(English, how) for a message id or a Japanese string: the TSV, else the Global master
        (by message id, else by identical Japanese text), else the glossary."""
        ja = self.key(ja if ja is not None else self.ja.get(mid or "", ""))
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

    def official(self, mid):
        """English from the TSV or the Global master only (no glossary), or None."""
        ja = self.text(mid)
        return self.tsv.get(ja) or self.gl.get(mid or "") or self.gl_text.get(ja)

    def gloss(self, ja):
        s = ja
        for jn in sorted(self.people, key=len, reverse=True):
            if jn in s:
                s = s.replace(jn, "\0" + self.people[jn] + "\1")
        for j, e in sorted(GLOSSARY, key=lambda x: -len(x[0])):
            s = s.replace(j, e)
        s = s.replace("\0", "").replace("\1", "")
        s = re.sub(r"\s+", " ", s).replace(" )", ")").replace("( ", "(").strip()
        if JA.search(s):
            self.residue[ja] += 1
            s += " (tr.)"
        return s

    def person(self, mid):
        ja = self.text(mid)
        en = self.gl.get(mid) or self.people.get(ja) or (self.tsv.get(ja) if ja in self.tsv else None)
        return ja, en


# ---------------------------------------------------------------- references
class Ref:
    __slots__ = ("path", "kind", "cols", "rows", "subject", "order")

    def __init__(self, path, kind, col, row, subject, order):
        self.path, self.kind, self.cols, self.rows = path, kind, [col], [row]
        self.subject, self.order = subject, order


class Owner:
    def __init__(self, typ, key, label, ja, en, how, start, end, extra):
        self.typ, self.key, self.label, self.ja, self.en, self.how = typ, key, label, ja, en, how
        self.start, self.end, self.extra = start, end, extra
        self.refs = collections.OrderedDict()

    def add(self, path, kind, col, row, subject="", order=0):
        r = self.refs.get(path)
        if r:
            if col not in r.cols:
                r.cols.append(col)
            if row not in r.rows:
                r.rows.append(row)
            if subject and not r.subject:
                r.subject = subject
            return
        self.refs[path] = Ref(path, kind, col, row, subject, order)


BG_PARTS = {"asf": "(.asf)", "aaf": "(.aaf)", "acf": "(.acf)"}


class Build:
    def __init__(self, a):
        self.c = sqlite3.connect(f"file:{a.db}?mode=ro", uri=True)
        self.c.row_factory = sqlite3.Row
        self.names = Names(self.c, a.gl, a.names)
        self.sources = [Source("download", a.download), Source("APK 3.7.0", a.apk)]
        self.sources.append(Source("stand-in", a.standins))
        self.dims_cache = {}
        q = self.q
        self.banner_by_label = {r["id_label"]: r for r in q("select * from master_banner")}
        self.banner_by_id = {r["id"]: r for r in q("select * from master_banner")}
        self.banner_targets = collections.defaultdict(list)
        for r in q("select * from master_banner where target_content_type is not null order by id"):
            self.banner_targets[(r["target_content_type"], r["target_content_id"])].append(r)
        self.banner_replace = collections.defaultdict(list)
        for r in q("select * from master_banner_replace order by id"):
            self.banner_replace[r["type_id"]].append(r)
        self.replace = collections.defaultdict(dict)
        for r in q("select * from master_replace_resource where res_type=4 order by id"):
            self.replace[r["replace_group_id"]][r["original_res"]] = r["replace_res"]
        self.stages = collections.defaultdict(list)
        for r in q("select * from master_mission_stage order by master_mission_id, order_id, id"):
            self.stages[r["master_mission_id"]].append(r)
        self.parties = {r["id"]: r for r in q("select * from master_enemy_party")}
        self.ebase = {r["id"]: r["master_person_id"] for r in q("select id, master_person_id from master_enemy_base_parameter")}
        self.person = {r["id"]: r for r in q("select * from master_person")}
        self.roles = {r["id"]: r for r in q("select id, id_label, master_person_id, rarity from master_role")}
        self.items = {r["id"]: r for r in q("select id, id_label, name_message_id from master_item")}

    def q(self, sql, *p):
        return list(self.c.execute(sql, p))

    def where(self, path):
        for s in self.sources:
            if path in s.files:
                return s.label
        return None

    # -------------------------------------------------------- subjects
    def role_name(self, role_id):
        r = self.roles.get(role_id)
        if not r:
            return ""
        p = self.person.get(r["master_person_id"])
        ja, en = self.names.person(p["name_message_id"]) if p else ("", None)
        star = f"★{r['rarity']} " if r["rarity"] else ""
        return f"{star}{ja}" + (f" ({en})" if en else "")

    def item_name(self, item_id):
        it = self.items.get(item_id)
        if not it:
            return ""
        ja = self.names.text(it["name_message_id"])
        en = self.names.gl.get(it["name_message_id"]) or self.names.gl_text.get(ja)
        return ja + (f" ({en})" if en else "")

    def person_name(self, pid):
        p = self.person.get(pid)
        if not p:
            return ""
        ja, en = self.names.person(p["name_message_id"])
        return (ja or p["id_label"]) + (f" ({en})" if en else "")

    # -------------------------------------------------------- banners
    def add_banner(self, o, b, col, why, subject):
        if not b or not b["image"]:
            return
        o.add(f"Image/{b['image']}.aif", why, col, b["id_label"], subject, 0)
        for r in self.banner_replace.get(b["master_banner_replace_type_id"], []):
            if r["image"]:
                o.add(f"Image/{r['image']}.aif", why + " (dated replacement)", "master_banner_replace.image",
                      r["id_label"], subject, 0)

    # -------------------------------------------------------- missions
    def add_mission(self, o, m, rep, table):
        """Add a mission's files to `o`; return (label, name, gating paths). Gating = what the local
        server's playability check needs (server/src/api/events/event_missions.cpp `battle_files`,
        `story_playable`): each stage's map (.asf/.aaf/.acf) and its enemies' models (.asf); a
        mission without stages needs its Script (and Scenario when named)."""
        mja = self.names.text(m["name_message_id"])
        men = self.names.official(m["name_message_id"])
        mname = mja + (f" ({men})" if men else "")
        gate = set()
        keys = m.keys()
        stages = self.stages.get(m["id"], [])
        if "talk_event_id_label" in keys and m["talk_event_id_label"]:
            o.add(f"Script/{m['talk_event_id_label']}.msgp", "story scene script",
                  f"{table}.talk_event_id_label", m["id_label"], mname, 1)
            if not stages:
                gate.add(f"Script/{m['talk_event_id_label']}.msgp")
        if "talk_message_file" in keys and m["talk_message_file"]:
            o.add(f"Scenario/{m['talk_message_file']}.msgp", "story dialogue text pack",
                  f"{table}.talk_message_file", m["id_label"], mname, 2)
            if not stages:
                gate.add(f"Scenario/{m['talk_message_file']}.msgp")
        for st in stages:
            mp = st["master_map_id_label"]
            if mp:
                mp2 = rep.get(mp, mp)
                col = "master_mission_stage.master_map_id" + (" -> master_replace_resource" if mp2 != mp else "")
                for ext in ("asf", "aaf", "acf"):
                    o.add(f"BG/{mp2}.{ext}", f"battle map (.{ext})", col, st["id_label"], mname, 3)
                    gate.add(f"BG/{mp2}.{ext}")
            if st["stage_bgm"]:
                o.add(f"Sound/{st['stage_bgm']}.aac", "boss-stage BGM" if st["is_boss"] else "stage BGM",
                      "master_mission_stage.stage_bgm", st["id_label"], mname, 4)
            if st["boss_icon"]:
                o.add(f"Image/{st['boss_icon']}.aif", "boss icon", "master_mission_stage.boss_icon",
                      st["id_label"], mname, 5)
            p = self.parties.get(st["master_enemy_party_id"])
            for i in range(1, 9):
                pid = self.ebase.get(p[f"member{i}_id"]) if p else None
                per = self.person.get(pid)
                if not per:
                    continue
                who = self.person_name(pid) + (" (boss)" if p[f"member{i}_boss"] else "")
                for colname, fmt, what in (("asf", "Character/{}.asf", "enemy model"),
                                           ("acf", "Character/{}.acf", "enemy animation set"),
                                           ("apk", "Motion/{}.apk", "enemy motion package"),
                                           ("unique_apk", "Character/{}.apk", "enemy unique package")):
                    if per[colname]:
                        o.add(fmt.format(per[colname]), what, f"master_person.{colname} (enemy party)",
                              st["master_enemy_party_id_label"], who, 6)
                if per["asf"]:
                    gate.add(f"Character/{per['asf']}.asf")
        return m["id_label"], mname, gate

    # -------------------------------------------------------- events
    def events(self):
        terms = collections.defaultdict(list)
        for r in self.q("select * from master_event_term order by opened_day, opened_time, id"):
            terms[r["master_event_area_id"]].append(r)
        weekly = collections.defaultdict(list)
        for r in self.q("select * from master_event_weekly order by week_id, id"):
            weekly[r["master_event_area_id"]].append(r)
        missions = collections.defaultdict(list)
        for r in self.q("select * from master_event_mission order by order_id, id"):
            missions[r["master_event_area_id"]].append(r)
        wboss = {r["id_label"]: r for r in self.q("select * from master_world_boss")}
        out = []
        for ar in self.q("select * from master_event_area order by id"):
            t = terms.get(ar["id"], [])
            if t:
                start = f"{min(x['opened_day'] for x in t)} {t[0]['opened_time'] or ''}".strip()
                end = max(f"{x['closed_day']} {x['closed_time'] or ''}".strip() for x in t)
                extra = f"{len(t)} term(s)"
            elif ar["opened_at"]:
                start, end, extra = ar["opened_at"], ar["closed_at"] or "", "area window"
            elif weekly.get(ar["id"]):
                start, end = "", ""
                days = "Sun Mon Tue Wed Thu Fri Sat".split()
                extra = "weekly: " + ", ".join(sorted({days[w["week_id"] % 7] for w in weekly[ar["id"]]},
                                                       key=days.index))
            else:
                start, end, extra = "", "", "no term"
            ja = self.names.text(ar["name_message_id"])
            en, how = self.names.english(ar["name_message_id"])
            if ja in ("", "--") and "@" + ar["id_label"] in self.names.tsv:  # unnamed areas: named by label
                en, how = self.names.tsv["@" + ar["id_label"]], "tsv"
            o = Owner("event", ar["id"], ar["id_label"], ja, en, how, start, end, extra)
            subj = en or ar["id_label"]
            if ar["bg_resource"]:
                kind = "mission-board map background" if ar["is_mission_board"] == 1 else "event list banner"
                o.add(f"Image/{ar['bg_resource']}.aif", kind, "master_event_area.bg_resource", ar["id_label"], subj)
            b = self.banner_by_label.get(ar["master_banner_id_label"] or "") or self.banner_by_id.get(ar["master_banner_id"])
            self.add_banner(o, b, "master_banner.image (master_event_area.master_banner_id)", "event banner", subj)
            for b in self.banner_targets.get((3, ar["id"]), []):
                self.add_banner(o, b, "master_banner.image (target_content_type 3)", "home / notice banner", subj)
            if ar["voice_menu_pack_name"]:
                o.add(f"Sound/{ar['voice_menu_pack_name']}.spk", "event menu voice pack",
                      "master_event_area.voice_menu_pack_name", ar["id_label"],
                      f"cues {ar['voice_menu_cue_min']}-{ar['voice_menu_cue_max']}")
            rep = self.replace.get(ar["resource_replace_group_id"], {})
            o.missions = [self.add_mission(o, m, rep, "master_event_mission") for m in missions.get(ar["id"], [])]
            w = wboss.get(ar["event_id_label"] or "")
            if w and w["enemy_icon"]:
                o.add(f"Image/{w['enemy_icon']}.aif", "world boss icon", "master_world_boss.enemy_icon", w["id_label"],
                      self.names.text(w["message_id_label"]), 5)
            out.append(o)
        return out

    # -------------------------------------------------------- gachas
    def gachas(self):
        images = collections.defaultdict(list)
        for r in self.q("select * from master_gacha_image order by master_gacha_id, view_index, id"):
            images[r["master_gacha_id"]].append(r)
        groups = collections.OrderedDict()
        rows = self.q("select * from master_gacha order by opened_at, serial_number, id")
        for g in rows:
            groups.setdefault(g["banner_id"] or f"(none:{g['id_label']})", []).append(g)
        out, dangling = [], []
        for bid, gs in groups.items():
            first = gs[0]
            ja = self.names.text(first["name_message_id"])
            title = re.sub(r"\s*ステップ\s*\d+\s*$", "", ja) if len(gs) > 1 else ja
            title = re.sub(r"\s*ステップ\s*\d+(?=\()", "", title) if len(gs) > 1 else title
            en, how = self.names.english(None, title)
            start = min((g["opened_at"] or "") for g in gs)
            end = max((g["closed_at"] or "") for g in gs)
            kinds = sorted({{0: "character", 1: "weapon", 2: "box"}.get(g["gacha_type"], str(g["gacha_type"])) for g in gs})
            extra = f"{len(gs)} gacha row(s), {'/'.join(kinds)}" + (", step-up" if any(g["is_stepup"] for g in gs) else "")
            o = Owner("gacha", bid, bid, title, en, how, start, end, extra)
            o.gachas = [(g["id_label"], self.names.text(g["name_message_id"]), g["opened_at"], g["closed_at"]) for g in gs]
            picks = []
            for g in gs:
                for im in images.get(g["id"], []):
                    s = self.content_name(im)
                    if s and s not in picks:
                        picks.append(s)
            o.picks = picks
            subj = (en or title) + (" — pick-ups: " + "; ".join(picks[:4]) if picks else "")
            b = self.banner_by_label.get(bid)
            if b is None:
                dangling.append(o)
            self.add_banner(o, b, "master_banner.image (master_gacha.banner_id)", "gacha list banner", subj)
            for g in gs:
                for tb in self.banner_targets.get((1, g["id"]), []):
                    if tb is not b:
                        self.add_banner(o, tb, "master_banner.image (target_content_type 1)", "home / notice banner", subj)
            for g in gs:
                for k in range(1, 5):
                    if g[f"image{k}"]:
                        o.add(f"Image/{g['image' + str(k)]}.aif", f"pick-up panel {k} (HTML-era gacha screen)",
                              f"master_gacha.image{k}", g["id_label"], subj, k)
                for im in images.get(g["id"], []):
                    if im["image_resource"]:
                        s = self.content_name(im)
                        o.add(f"Image/{im['image_resource']}.aif",
                              f"pick-up panel (view {im['view_index']})" if s else f"main panel (view {im['view_index']})",
                              "master_gacha_image.image_resource", g["id_label"], s or subj, 10 + (im["view_index"] or 0))
                rep = self.replace.get(g["resource_replace_group_id"], {})
                for orig, res in sorted(rep.items()):
                    for ext in ("asf", "aaf", "acf"):
                        o.add(f"BG/{res}.{ext}", f"gacha scene map {BG_PARTS[ext]} (replaces {orig})",
                              "master_gacha.resource_replace_group_id -> master_replace_resource.replace_res",
                              g["id_label"], subj, 30)
            out.append(o)
        return out, dangling

    def content_name(self, im):
        lab = im["content_id_label"] or ""
        if lab.startswith("role_") or im["content_type"] == 2:
            return self.role_name(im["content_id"])
        if lab.startswith("item_") or im["content_type"] == 1:
            return self.item_name(im["content_id"])
        return ""

    # -------------------------------------------------------- beyond events and gacha
    def others(self):
        """Content outside events and gacha: list of (kind title, description, groups); a group is
        (heading ja, heading en, how, items); an item is an Owner whose `gate` lists the files its
        use needs (the rest of its refs are reported but don't block it)."""
        kinds = []
        names = self.names

        def item(typ, key, label, mid, ja=None, start="", end="", extra=""):
            ja = ja if ja is not None else names.text(mid)
            en = (names.official(mid) if mid else names.tsv.get(names.key(ja))) or ""  # no glossary for row names
            how = "gl" if en else "none"
            o = Owner(typ, key, label, ja, en, how, start, end, extra)
            o.gate = set()
            return o

        def mission_group(typ, rows, table, rep=None):
            items = []
            for m in rows:
                o = item(typ, m["id"], m["id_label"], m["name_message_id"])
                _, _, g = self.add_mission(o, m, rep or {}, table)
                o.gate = g
                items.append(o)
            return items

        # missions: EP1 planets, the world map (EP2 / EP3), tower, training
        groups = []
        area = {r["id"]: r for r in self.q("select * from master_area")}
        ms = collections.defaultdict(list)
        for m in self.q("select * from master_mission order by order_id, id"):
            ms[m["master_area_id"]].append(m)
        for aid, rows in sorted(ms.items(), key=lambda x: (area[x[0]]["order_id"] if x[0] in area else 0, x[0])):
            ar = area.get(aid)
            ja = names.text(ar["name_message_id"]) if ar else ""
            en, how = names.english(ar["name_message_id"]) if ar else ("", "none")
            if not ar:
                ja, en, how = f"master_area_id {aid}", "no master_area row (test missions, by their names)", "tsv"
            groups.append((ja or f"area {aid}", en, how, f"master_mission, area `{ar['id_label'] if ar else aid}`",
                           mission_group("mission", rows, "master_mission")))
        wm = collections.defaultdict(list)
        for m in self.q("select * from master_world_map_mission order by order_id, id"):
            wm[m["id_label"][:6]].append(m)
        for ch, rows in sorted(wm.items()):
            mm = re.match(r"m(\d\d)_(\d\d)", ch)
            ep = {"02": 2, "06": 3}.get(mm.group(1)) if mm else None
            ja = f"EP{ep} 第{int(mm.group(2))}章" if ep else ch
            en = f"Episode {ep}, Chapter {int(mm.group(2))}" if ep else ch
            groups.append((ja, en, "tsv", f"master_world_map_mission `{ch}_*` (EP from the label: m02 = EP2, "
                           "m06 = EP3, (d) from the chapters' dates and the EP2 / EP3 packs)",
                           mission_group("mission", rows, "master_world_map_mission")))
        tw = collections.defaultdict(list)
        for m in self.q("select * from master_tower_mission order by order_id, id"):
            tw[m["master_tower_area_id"]].append(m)
        for ar in self.q("select * from master_tower_area order by serial_number, id"):
            en, how = names.english(ar["name_message_id"])
            groups.append((names.text(ar["name_message_id"]), en, how,
                           f"master_tower_mission, tower area `{ar['id_label']}` ({ar['opened_at']} → {ar['closed_at']})",
                           mission_group("mission", tw.get(ar["id"], []), "master_tower_mission")))
        tm = self.q("select * from master_training_mission order by id")
        groups.append(("シミュレーター", "Simulator (training)", "tsv", "master_training_mission",
                       mission_group("mission", tm, "master_training_mission")))
        kinds.append(("Missions and story chapters", "Each mission is playable when the local server's check "
                      "passes: every stage's battle map (`BG/<map>.asf/.aaf/.acf`) and every enemy's model "
                      "(`Character/<asf>.asf`) are present; a story mission (no stages) needs its `Script/` and "
                      "`Scenario/` file (server/src/api/events/event_missions.cpp `battle_files` / `story_playable`, "
                      "the rule Sphere 211 and the tower use too; docs/server-rules.md). Stage BGM, enemy "
                      "animation / motion files and story scripts of battle missions are listed but don't block. "
                      "The episode packs (`EP1`-`EP3`: the main story's scripts, scenario text, talk scenes, voices, "
                      "SE and movies) are complete: every member of the ep1-3 manifests is in the download. Event "
                      "story voices and SE (`Sound/TS_*`, `Voice_TS_*`) are named inside the scripts, not by the "
                      "master, and are gone with the missing event scripts (part 1).",
                      groups))

        # Sphere 211: floors (their map, background, BGM) and the mission boxes' missions
        groups = []
        floors = collections.defaultdict(list)
        for f in self.q("select * from master_sphere211_floor order by floor_group_id, level, id"):
            floors[f["floor_group_id_label"]].append(f)
        for fg, rows in sorted(floors.items()):
            items = []
            for f in rows:
                o = item("floor", f["id"], f["id_label"], f["name_message_id"])
                if f["bg_resource"]:
                    o.add(f"Image/{f['bg_resource']}.aif", "floor background", "master_sphere211_floor.bg_resource", f["id_label"], o.ja)
                if f["master_map_id_label"]:
                    for ext in ("asf", "aaf", "acf"):
                        o.add(f"BG/{f['master_map_id_label']}.{ext}", f"battle map (.{ext})",
                              "master_sphere211_floor.master_map_id", f["id_label"], o.ja, 3)
                        o.gate.add(f"BG/{f['master_map_id_label']}.{ext}")
                if f["stage_bgm"]:
                    o.add(f"Sound/{f['stage_bgm']}.aac", "stage BGM", "master_sphere211_floor.stage_bgm", f["id_label"], o.ja, 4)
                items.append(o)
            groups.append((f"フロアグループ {fg}", f"Floor group {fg}", "tsv", "master_sphere211_floor", items))
        box = collections.defaultdict(list)
        for r in self.q("select b.mission_box_group_id_label g, m.* from master_sphere211_mission_box b "
                        "join master_event_mission m on m.id = b.master_mission_id order by b.mission_box_group_id_label, b.id"):
            box[r["g"]].append(r)
        evarea = {r["id"]: r for r in self.q("select * from master_event_area")}
        for g, rows in sorted(box.items()):
            items = []
            for m in rows:
                o = item("mission", m["id"], m["id_label"], m["name_message_id"])
                ar = evarea.get(m["master_event_area_id"])
                rep = self.replace.get(ar["resource_replace_group_id"], {}) if ar else {}
                o.gate = self.add_mission(o, m, rep, "master_event_mission")[2]
                items.append(o)
            groups.append((f"ミッションボックス {g}", f"Mission box {g}", "tsv",
                           "master_sphere211_mission_box -> master_event_mission", items))
        kinds.append(("Sphere 211", "Floors need their battle map; a cell battle is lotted from the floor's mission "
                      "box, and the server lots only playable missions (docs/server-rules.md \"Sphere 211\", "
                      "\"Missing maps\"; the same check as above). Floor backgrounds and BGM are listed but don't block.",
                      groups))

        # characters: roles -> persons
        items = []
        img_kinds = (("fl", "full-figure art"), ("ic", "icon"), ("fv", "face"), ("cs", "cut-in / status art"),
                     ("ca", "card art"))
        for r in self.q("select r.*, p.id_label person from master_role r join master_person p on p.id = r.master_person_id "
                        "order by r.order_id, r.id"):
            per = self.person[r["master_person_id"]]
            o = item("character", r["id"], r["id_label"], per["name_message_id"], start=r["opened_at"] or "")
            ja, en = names.person(per["name_message_id"])
            o.ja, o.en, o.how = ja, en or o.en, "names" if en else o.how
            o.ja = f"★{r['rarity']} {o.ja}"
            for colname, fmt, what in (("asf", "Character/{}.asf", "character model"),
                                       ("acf", "Character/{}.acf", "character animation set"),
                                       ("apk", "Motion/{}.apk", "character motion package"),
                                       ("unique_apk", "Character/{}.apk", "character unique package")):
                if per[colname]:
                    o.add(fmt.format(per[colname]), what, f"master_person.{colname}", per["id_label"], o.ja, 1)
                    o.gate.add(fmt.format(per[colname]))
            mm = re.match(r"(c[pc]\d+)_b(\d+[a-z])", per["id_label"])
            if mm:
                for k, what in img_kinds:
                    pth = f"Image/{mm.group(1)}_{k}{mm.group(2)}.aif"
                    o.add(pth, what, "master_person.id_label (naming rule (d))", per["id_label"], o.ja, 2)
                    o.gate.add(pth)
                if mm.end() == len(per["id_label"]):  # suffixed persons (`_2`, ...) have no chip of their own
                    o.add(f"Image/u_chip_{per['id_label']}.aif", "universe-chip portrait",
                          "master_person.id_label (naming rule (d))", per["id_label"], o.ja, 2)
            for colname, what in (("voice_sound_package", "battle voice pack"), ("menu_voice_sound_package", "menu voice pack"),
                                  ("home_voice_sound_package", "home voice pack"),
                                  ("home_voice_sound_package_sub", "home voice pack (sub)"),
                                  ("gacha_voice_package", "gacha voice pack")):
                if per[colname]:
                    o.add(f"Sound/{per[colname]}.spk", what, f"master_person.{colname}", per["id_label"], o.ja, 3)
            if per["home3d_file"]:
                o.add(f"Character/{per['home3d_file']}.asf", "home 3D model", "master_person.home3d_file", per["id_label"], o.ja, 4)
            items.append(o)
        kinds.append(("Characters", "Each playable role (`master_role`): its person's model files gate it (the "
                      "four person resource fields, docs/notes.md \"Characters\"), and its portraits "
                      "`Image/<code>_{fl,ic,fv,cs,ca}<variant>.aif` (code and variant from the person label "
                      "`<code>_b<variant>`; the rule is (d), from the names: 302 of 307 playable persons have all five) "
                      "gate it too, since the roster and party screens show them. Voices, the universe-chip "
                      "portrait and the home model are listed but don't block.",
                      [("キャラクター", "Characters", "tsv", "master_role -> master_person", items)]))

        # weapons and other items: thumbnails (+ the weapon model)
        items = []
        for it in self.q("select i.*, w.asf wasf, w.master_weapon_kind_id_label wkind from master_item i "
                         "left join master_weapon w on w.id = i.master_weapon_id order by i.type, i.serial_number, i.id"):
            o = item("item", it["id"], it["id_label"], it["name_message_id"])
            if it["thumbnail_id_label"]:
                pth = f"Image/{it['thumbnail_id_label']}.aif"
                o.add(pth, "item icon", "master_item.thumbnail_id", it["id_label"], o.ja, 1)
                o.gate.add(pth)
            if it["wasf"] and it["wkind"] != "W99St":
                o.add(f"Weapon/{it['wasf']}.asf", "weapon model", "master_weapon.asf", it["id_label"], o.ja, 2)
                o.gate.add(f"Weapon/{it['wasf']}.asf")
            items.append(o)
        bytype = collections.defaultdict(list)
        for o in items:
            bytype[o.label.split("_")[1] if o.label.startswith("item_W") else "other"].append(o)
        kinds.append(("Weapons, accessories and items", "Every `master_item` row: its icon "
                      "(`thumbnail_id` -> `Image/<label>.aif`, (b) libSOA has `Image/itm_th_%s.aif`) and, for "
                      "weapons, the model `Weapon/<master_weapon.asf>.asf` (docs/notes.md \"Resource names\"; "
                      "the `W99St` kind names an image there and is skipped). Weapon `.apk` files exist for "
                      "animated weapons only and aren't checked.",
                      [("アイテム", "Items", "tsv", "master_item", items)]))

        # small kinds: one item per row
        def rows_kind(title, desc, sql, mk):
            items = []
            for r in self.q(sql):
                o = mk(r)
                if o:
                    items.append(o)
            kinds.append((title, desc, [(title, title, "tsv", sql.split(" from ")[1].split()[0], items)]))

        def wb(r):
            o = item("world boss", r["id"], r["id_label"], r["message_id_label"], start=r["opened_at"] or "")
            o.add(f"Image/{r['enemy_icon']}.aif", "world boss icon", "master_world_boss.enemy_icon", r["id_label"], o.ja)
            o.gate.add(f"Image/{r['enemy_icon']}.aif")
            return o
        rows_kind("World bosses", "`master_world_boss.enemy_icon`; the fights are event missions (above).",
                  "select * from master_world_boss order by opened_at, id", wb)

        def ds(r):
            o = item("deep space area", r["id"], r["id_label"], r["name_message_id_label"])
            for col, what in (("resource", "area picture"), ("item_icon", "area item icon")):
                if r[col]:
                    o.add(f"Image/{r[col]}.aif", what, f"master_deep_space_area.{col}", r["id_label"], o.ja)
                    o.gate.add(f"Image/{r[col]}.aif")
            return o
        rows_kind("Deep space areas", "`master_deep_space_area.resource` / `item_icon` (images). Deep-space "
                  "missions are timed expeditions with no battle files.", "select * from master_deep_space_area order by id", ds)

        def lb(r, table="master_login_bonus"):
            o = item("login bonus", r["id"], r["id_label"], r["name_message_id"], start=r["opened_at"] or "",
                     end=r["closed_at"] or "")
            if r["banner_image"]:
                o.add(f"Image/{r['banner_image']}.aif", "login bonus banner", f"{table}.banner_image", r["id_label"], o.ja)
                o.gate.add(f"Image/{r['banner_image']}.aif")
            return o
        rows_kind("Login bonuses", "`master_login_bonus.banner_image` (the bonus screen's banner); "
                  "`master_premium_login_bonus` has no images.", "select * from master_login_bonus order by opened_at, id", lb)

        def ti(r):
            o = item("title", r["id"], r["id_label"], r["name_message_id"])
            if r["tips_resource"]:
                o.add(f"Image/{r['tips_resource']}.aif", "title plate", "master_title.tips_resource", r["id_label"], o.ja)
                o.gate.add(f"Image/{r['tips_resource']}.aif")
            return o
        rows_kind("Titles", "`master_title.tips_resource` (the plate image; most titles have none).",
                  "select * from master_title order by order_id, id", ti)

        def de(r):
            o = item("deco", r["id"], r["id_label"], None, ja=r["id_label"])
            o.en, o.how = "", "none"
            if r["model_resource_name"]:
                o.add(f"Deco/{r['model_resource_name']}.asf", "deco model", "master_deco_object.model_resource_name", r["id_label"], "")
                o.gate.add(f"Deco/{r['model_resource_name']}.asf")
            if r["animation_resource_name"]:
                o.add(f"Deco/{r['animation_resource_name']}.aaf", "deco animation",
                      "master_deco_object.animation_resource_name", r["id_label"], "")
            return o
        rows_kind("Deco (accessories worn on the model)", "`master_deco_object.model_resource_name` -> `Deco/<x>.asf` "
                  "(docs/notes.md \"Resource names\").", "select * from master_deco_object order by order_id, id", de)

        def st(r):
            o = item("stamp", r["id"], r["id_label"], r["name_message_id"])
            if r["resource_name"]:
                o.add(f"Image/{r['resource_name']}", "stamp image", "master_stamp.resource_name", r["id_label"], o.ja)
                o.gate.add(f"Image/{r['resource_name']}")
            if r["sound_resource"]:
                o.add(f"Sound/{r['sound_resource']}.spk", "stamp voice", "master_stamp.sound_resource", r["id_label"], o.ja)
            return o
        rows_kind("Stamps", "`master_stamp.resource_name` (an image name with its extension), `sound_resource`.",
                  "select * from master_stamp order by order_id, id", st)

        def ex(r):
            o = item("exchange shop", r["id"], r["id_label"], r["name_message_id"], start=r["opened_at"] or "",
                     end=r["closed_at"] or "")
            for c in self.shop_contents.get(r["id"], []):
                for iid in (c["ex_item_id"], c["content_id"] if c["content_type"] in (1, 8, 9) else None):
                    it = self.items.get(iid) if iid else None
                    th = self.item_thumb.get(iid) if iid else None
                    if it and th:
                        o.add(f"Image/{th}.aif", "item icon", "master_exchange_shop_contents -> master_item.thumbnail_id",
                              it["id_label"], names.text(it["name_message_id"]))
                        o.gate.add(f"Image/{th}.aif")
            return o
        self.item_thumb = {r["id"]: r["thumbnail_id_label"] for r in self.q("select id, thumbnail_id_label from master_item")}
        self.shop_contents = collections.defaultdict(list)
        for r in self.q("select * from master_exchange_shop_contents order by order_id, id"):
            self.shop_contents[r["master_exchange_shop_id"]].append(r)
        rows_kind("Exchange shops", "`master_exchange_shop` names no file; a shop needs the icons of its prices "
                  "and goods (`master_exchange_shop_contents` -> `master_item.thumbnail_id`).",
                  "select * from master_exchange_shop order by opened_at, id", ex)

        def sk(r):
            o = item("skill", r["id"], r["id_label"], r["name_message_id"])
            if r["skill_icon"]:
                o.add(f"Image/{r['skill_icon']}.aif", "skill icon", "master_skill.skill_icon", r["id_label"], o.ja)
                o.gate.add(f"Image/{r['skill_icon']}.aif")
            return o
        rows_kind("Skills", "`master_skill.skill_icon` (images). Skill effects (`Effect/<id>.asf/.apk/.aaf`, "
                  "loaded per battle) are not checked here.",
                  "select * from master_skill order by id", sk)

        def sb(r):
            o = item("studio background", r["id"], r["id_label"], r["name_id_label"])
            if r["thumbnail"]:
                o.add(f"Image/{r['thumbnail']}.aif", "studio background thumbnail", "master_studio_bg.thumbnail", r["id_label"], o.ja)
                o.gate.add(f"Image/{r['thumbnail']}.aif")
            return o
        rows_kind("Photo studio backgrounds", "`master_studio_bg.thumbnail`.", "select * from master_studio_bg order by order_id, id", sb)
        return kinds

    # -------------------------------------------------------- what it probably is
    @staticmethod
    def pattern(name):
        return re.sub(r"\d+", "#", name)

    def sibling_dims(self, path):
        """Sizes of existing images of the same name pattern (the first and last 3 by name)."""
        if not path.startswith("Image/"):
            return None
        stem = path[6:-4]
        pat = self.pattern(stem)
        if pat in self.dims_cache:
            return self.dims_cache[pat]
        real = [s for s in self.sources if s.label != "stand-in"]  # made-up files are no evidence
        have = sorted({p[6:-4] for s in real for p in s.files
                       if p.startswith("Image/") and p.endswith(".aif") and self.pattern(p[6:-4]) == pat})
        got = []
        for n in have[:3] + have[-3:] if len(have) > 6 else have:
            src = next(s for s in real if f"Image/{n}.aif" in s.files)
            d = image_info(src, f"Image/{n}.aif")
            if d and (n, d) not in got:
                got.append((n, d))
        if not have and re.match(r"[A-Za-z]+#", pat):  # e.g. `bbc#_#_#`: fall back to `bbg#_#_#` and kin
            rest = re.sub(r"^[A-Za-z]+", "", pat)
            fam = sorted({p[6:-4] for s in real for p in s.files if p.startswith("Image/") and p.endswith(".aif")
                          and re.fullmatch(r"[A-Za-z]+", re.sub(r"\d+", "#", p[6:-4])[:-len(rest)] or "-")
                          and self.pattern(p[6:-4]).endswith(rest) and self.pattern(p[6:-4])[0] == pat[0]})
            if fam:
                got = []
                for n in fam[:3]:
                    src = next(s for s in real if f"Image/{n}.aif" in s.files)
                    d = image_info(src, f"Image/{n}.aif")
                    if d:
                        got.append((n, d))
                self.dims_cache[pat] = ("*" + rest, len(fam), got)
                return self.dims_cache[pat]
        self.dims_cache[pat] = (pat, len(have), got)
        return self.dims_cache[pat]

    def guess(self, o, r):
        """(text, confidence, evidence)."""
        name = r.path.split("/", 1)[1].rsplit(".", 1)[0]
        conf, ev = "high", []
        sd = self.sibling_dims(r.path)
        size = ""
        if sd:
            pat, n, got = sd
            dims = collections.Counter(f"{w}×{h} {f}" for _, (w, h, f) in got)
            if dims:
                size = " / ".join(d for d, _ in dims.most_common(2))
                ev.append(f"{n} existing `{pat}` (e.g. `{got[0][0]}`: {got[0][1][0]}×{got[0][1][1]})")
                if len(dims) > 1 or pat.startswith("*"):
                    conf = "medium"
            else:
                conf = "medium"
                ev.append(f"no existing `{pat}` file")
        k = r.kind
        subj = r.subject
        if k == "gacha list banner":
            t = f"list banner for the gacha \"{o.en or o.ja}\"" + (f", featuring {'; '.join(o.picks[:3])}" if o.picks else "")
        elif k.startswith("pick-up panel (view") or k.startswith("main panel"):
            t = (f"pick-up panel for {subj}" if k.startswith("pick-up") else f"main (first) panel of \"{o.en or o.ja}\"")
            if k.startswith("main") and o.picks:
                t += f" showing {'; '.join(o.picks[:3])}"
                conf = "medium" if conf == "high" else conf
        elif k.startswith("pick-up panel"):
            n = re.search(r"panel (\d)", k).group(1)
            t = f"pick-up panel {n} of \"{o.en or o.ja}\""
            if len(o.picks) >= int(n):
                t += f", probably {o.picks[int(n) - 1]}"
                conf = "medium"
            elif o.picks:
                t += f" (pick-ups: {'; '.join(o.picks[:3])})"
                conf = "medium"
        elif k in ("event banner", "event banner (dated replacement)"):
            t = f"banner for the event \"{o.en or o.ja}\""
        elif k.startswith("home / notice banner"):
            t = f"home-screen / notice banner announcing \"{o.en or o.ja}\""
            ev.append(f"banner row `{r.rows[0]}`")
        elif k == "event list banner":
            t = f"event list banner for \"{o.en or o.ja}\""
        elif k == "mission-board map background":
            t = f"mission-board (event map) background for \"{o.en or o.ja}\""
            m = re.match(r"00_(bm\d+_b\d+[a-z])_", name)
            if m:
                t += f", a picture of home map `{m.group(1)}`"
                conf = "medium" if conf == "high" else conf
        elif k == "story scene script":
            t = f"story scene command script for mission {r.rows[0]} \"{subj}\""
            ev.append("path rule (b)")
        elif k == "story dialogue text pack":
            t = f"dialogue text for story chapter `{name}` (missions {', '.join(r.rows[:3])}{'…' if len(r.rows) > 3 else ''})"
            ev.append("path rule (b)")
        elif k.startswith("battle map"):
            t = f"3D battle map `{name}` for stage(s) {', '.join(r.rows[:2])}{'…' if len(r.rows) > 2 else ''}"
        elif k.startswith("gacha scene map"):
            t = f"{k}: the draw scene's backdrop `{name}`"
        elif "BGM" in k:
            t = f"{k} for \"{subj}\" (stage {r.rows[0]})"
        elif k == "event menu voice pack":
            t = f"voice lines of the event menu ({subj})"
        elif k.startswith("enemy"):
            t = f"{k} of {subj}"
            ev.append(f"party `{r.rows[0]}`")
        elif k in ("boss icon", "world boss icon"):
            t = f"{k} ({subj})"
        else:
            t = k + (f" of {subj}" if subj else "")
        if size:
            t += f"; {size}"
        return t, conf, "; ".join(ev)


# ---------------------------------------------------------------- output
def md_escape(s):
    return (s or "").replace("|", "\\|").replace("\n", " ")


def year_of(o):
    return o.start[:4] if o.start[:4].isdigit() else "undated"


STANDIN_LEGEND = ("Stand-in? **yes (2D image)**: a made-up image in the game's format shows in its place, as the "
                  "existing `standin-assets/` ones do; **yes (any BGM)**: another track under this name plays; "
                  "**partly (cue ids)**: a pack with the same cue ids (silent or borrowed lines) satisfies the "
                  "player; **partly (end scene)**: a minimal script that ends the scene lets the mission complete, "
                  "the story is lost; **partly (text)**: placeholder lines for the script's message ids; **no (3D)**: "
                  "a map, model or motion set, where a stand-in could only be another one under this name.")


def standin_verdict(path, kind=""):
    """Would a made-up stand-in (like standin-assets/) plausibly make the thing usable?"""
    if path.startswith("Image/"):
        return "yes (2D image)"
    if path.startswith("Sound/") and path.endswith(".aac"):
        return "yes (any BGM)"
    if path.startswith("Sound/"):
        return "partly (cue ids)"
    if path.startswith("Script/"):
        return "partly (end scene)"
    if path.startswith("Scenario/"):
        return "partly (text)"
    return "no (3D)"


def merge_bg(refs):
    """Fold the .asf / .aaf / .acf refs of one map into one display row: [(display path, ref, paths)]."""
    out, seen = [], {}
    for r in refs:
        if r.path.startswith("BG/"):
            stem = r.path.rsplit(".", 1)[0]
            if stem in seen:
                seen[stem][2].append(r.path)
                continue
            seen[stem] = [stem, r, [r.path]]
            out.append(seen[stem])
        else:
            out.append([r.path, r, [r.path]])
    res = []
    for disp, r, paths in out:
        if len(paths) > 1:
            disp = disp + "." + "/.".join(p.rsplit(".", 1)[1] for p in paths)
        elif disp.startswith("Image/"):
            disp = disp.replace("/", "/etc2/", 1)
        res.append((disp, r, paths))
    return res


def write_part2(L, b, kinds, status):
    w = L.append
    stats = []
    for title, desc, groups in kinds:
        allitems = [o for g in groups for o in g[4]]
        for o in allitems:
            for p in o.refs:
                if p not in status:
                    status[p] = b.where(p)
        blocked = [o for o in allitems if any(not status[p] for p in o.gate)]
        extra = [o for o in allitems if o not in blocked and any(not status[p] for p in o.refs)]
        stats.append((title, len(allitems), len(allitems) - len(blocked), len(blocked), len(extra),
                      collections.Counter(p.split("/")[0] for o in blocked for p in o.gate if not status[p])))
        w(f"### {title}\n")
        w(desc + "\n")
        w(f"{len(allitems)} rows: **{len(allitems) - len(blocked)} usable** (every gating file present), "
          f"**{len(blocked)} blocked by missing files**; {len(extra)} of the usable ones miss only non-blocking files.\n")
        for gja, gen, how, note, items in groups:
            gb = [o for o in items if o in blocked]
            gx = [o for o in items if o in extra]
            if not gb and not gx:
                continue
            if len(groups) > 1:
                w(f"#### {md_escape(gja)} — {md_escape(gen) or '(no name)'}{' *GL*' if how == 'gl' else ''}\n")
                w(f"{note}: {len(items)} rows, {len(gb)} blocked" + (f", {len(gx)} usable with non-blocking files missing" if gx else "") + ".\n")
            if gb:
                w("Blocked: " + "; ".join(f"`{o.label}` {md_escape(o.ja)}" + (f" ({md_escape(o.en)})" if o.en and o.en != o.ja else "")
                                           for o in gb[:60]) + (f"; … (+{len(gb) - 60})" if len(gb) > 60 else "") + "\n")
            files = collections.OrderedDict()
            for o in gb + gx:
                for r in o.refs.values():
                    if not status[r.path]:
                        e = files.setdefault(r.path, [r, o, [], []])
                        lst = e[2] if r.path in o.gate else e[3]
                        if o.label not in lst:
                            lst.append(o.label)
            w("| Missing file | Kind | Blocks | What it probably is | Conf. | Stand-in? |")
            w("|---|---|---|---|---|---|")
            order = sorted(files.values(), key=lambda e: (not e[2], e[0].order, e[0].path))
            for disp, r, paths in merge_bg([e[0] for e in order]):
                _, o, blk, nb = files[r.path]
                t, cf, evd = b.guess(o, r)
                blocks = (", ".join(f"`{x}`" for x in blk[:4]) + (f" (+{len(blk) - 4})" if len(blk) > 4 else "")) if blk else "— (not blocking)"
                w(f"| `{disp}` | {r.kind} | {blocks} | {md_escape(t)}" + (f" ({md_escape(evd)})" if evd else "")
                  + f" | {cf} | {standin_verdict(r.path)} |")
            w("")
    return stats


def write(b, events, gachas, dangling, a, part2=()):
    owners = events + gachas
    status = {}
    for o in owners:
        for p in o.refs:
            if p not in status:
                status[p] = b.where(p)
    # stats
    years = sorted({year_of(o) for o in owners}, key=lambda y: (y == "undated", y))
    kinds = collections.OrderedDict()
    for o in owners:
        for r in o.refs.values():
            kk = re.sub(r" \(view \d+\)| \d+ \(HTML-era gacha screen\)| \(\.\w+\)| \(replaces .*\)| \(dated replacement\)", "", r.kind)
            kinds.setdefault((o.typ, kk), collections.Counter())
            c = kinds[(o.typ, kk)]
            st = status[r.path]
            c["refs"] += 1
            c[st or "missing"] += 1
            if not st:
                c["y:" + year_of(o)] += 1
    distinct_missing = collections.defaultdict(set)
    for o in owners:
        for r in o.refs.values():
            if not status[r.path]:
                distinct_missing[o.typ].add(r.path)
    P2 = []
    p2stats = write_part2(P2, b, part2, status) if part2 else []
    L = []
    w = L.append
    src_lines = ", ".join(f"{s.label} `{os.path.relpath(s.path, ROOT) if s.path and os.path.isabs(s.path) else s.path}` "
                          f"({len(s.files)} files)" for s in b.sources)
    w("# Missing event and gacha assets in 3.7.0\n")
    w("**Generated file — do not edit by hand.** Regenerate with:\n")
    w("```\n.venv/bin/python tools/missing_assets.py\n```\n")
    w("This lists every file that an event (`master_event_area`) or a gacha banner (`master_gacha`, grouped by "
      "`banner_id`) of the 3.7.0 master (`data/basmaster-3.7.0.sqlite3`) references and that no asset source has. "
      f"Sources, in lookup order: {src_lines}. A file found in a source counts as present; a file found only "
      "in `standin-assets/` is listed as **stand-in** (made-up art, port/README.md \"Stand-in assets\"). The online "
      "CDN dropped old event and gacha art before the last download, so most of what is missing is art and "
      "story data of events and banners that had already closed.\n")
    w("Names: the heading gives the Japanese name from `master_text`, then an English name. English comes from "
      "the Global master (`data/basmaster-gl.sqlite3`, official text, marked *GL*) where it has one, else from "
      "the hand-written table `docs/missing-assets-names.tsv` (established series / anamnesis names where known; "
      "**(tr.)** marks uncertain translations), else from a phrase glossary in the generator (marked *gloss*). "
      "Character names: the Global master, else `soa_save/names_en.json` (the fan wiki's names).\n")
    w("\"What it probably is\" is inference (d) from the referencing column and row, the subject (gacha title, "
      "pick-up role / weapon from `master_gacha_image`, mission name, enemy person), and the size and format of "
      "existing files with the same name pattern (digits folded to `#`), read from their AIF image header. "
      "Confidence: **high** = column and sibling pattern agree; **medium** = subject or size inferred "
      "(siblings disagree, or the panel's subject comes from the pool); **low** = no sibling evidence. The path "
      "rules, the facts, carry the labels of docs/server-rules.md: (a) master data, (b) client-side evidence, "
      "(d) assumption.\n")
    if p2stats:
        w("**Beyond events and gacha** (part 2, at the end): what else the 3.7.0 master describes completely but "
          "missing files block. Usable / blocked master rows:\n")
        w("| Content | Rows | Usable | Blocked | Blocking file types |")
        w("|---|---|---|---|---|")
        for t, n, u, bl, x, ft in p2stats:
            w(f"| {t} | {n} | {u} | {bl} | " + (", ".join(f"{k} {v}" for k, v in ft.most_common()) or "—") + " |")
        w("")
        w("So yes: the blocked rows above would run with their files back. Blocked by 2D images only (icons, "
          "banners, portraits), they would run with made-up stand-ins too; blocked by battle maps, models or "
          "story scripts, they need the real files (a stand-in map or model would only be another one under the "
          "same name). Details per row and file are in part 2.\n")
    w("## Path rules and how they were checked\n")
    w("| Reference | File | Label and evidence |")
    w("|---|---|---|")
    w("| image columns (`bg_resource`, `master_banner.image`, `image1..4`, `image_resource`, `boss_icon`, `enemy_icon`) "
      "| `Image/etc2/<name>.aif` | (b): libSOA 3.7.0 has the format `Image/%s.aif`; docs/notes.md \"Image assets\": the "
      "game loads `\"Image/\" + name + \".aif\"`, the `etc2/` folder is the texture-format directory of the asset "
      "manager; the ADLD key is CHash32 of `Image/etc2/<name>.aif` (verified here: the size reader decrypts "
      "existing files with exactly that key). The join `master_gacha.banner_id` = `master_banner.id_label` is (a) "
      "and the list-banner use is (b) (docs/server-rules.md \"Banner images\") |")
    w("| `talk_event_id_label`, `talk_message_file` | `Script/<x>.msgp`, `Scenario/<x>.msgp` | (b): "
      "`EventScenario::CEventScenario::SetEventId` formats `Script/%s.msgp` and `Scenario/%s.msgp` "
      "(docs/notes.md; both strings are in libSOA 3.7.0) |")
    w("| `master_mission_stage.master_map_id` | `BG/<map>.asf` / `.aaf` / `.acf` | (b): `battle_files` loads the "
      "three, the map first mapped through `master_replace_resource` res_type 4 (docs/notes.md \"Resource names\") |")
    w("| enemy persons (`master_enemy_party` → `master_enemy_base_parameter` → `master_person`) | "
      "`Character/<asf>.asf`, `Character/<acf>.acf`, `Motion/<apk>.apk`, `Character/<unique_apk>.apk` | (a) the "
      "join; (b) the four person resource fields (docs/notes.md \"Characters\") |")
    w("| `stage_bgm`, `voice_menu_pack_name` | `Sound/<x>.aac`, `Sound/<x>.spk` | (b) only partly: libSOA 3.7.0 has "
      "`Sound/`, `.aac` and `.spk`; (d) the "
      "concatenation, backed by the presence counts below |")
    w("| `master_gacha.resource_replace_group_id` | `BG/<replace_res>.*` | (a) `master_replace_resource`; (b) "
      "`CResourceReplaceManager::GetResourceName(id, 4)` replaces the gacha map `bg99_01` |")
    w("")
    # presence per kind (verification)
    w("**Checks.** The download tree on disk equals its manifests (every member of the Bulk, Individual and "
      "ep1-3 manifests is a file; `tools/check_download.py`). Presence of what the master references, per kind "
      "(references, not distinct files; *present* = any source):\n")
    w("| Owner | Kind | References | " + " | ".join(s.label for s in b.sources) + " | Missing |")
    w("|---|---|---|" + "---|" * len(b.sources) + "---|")
    for (typ, kk), c in kinds.items():
        w(f"| {typ} | {kk} | {c['refs']} | " + " | ".join(str(c[s.label]) for s in b.sources) + f" | {c['missing']} |")
    w("\nThe kinds whose files mostly exist (enemy models, battle maps, voice packs, boss icons) confirm the "
      "path rules; the image kinds of old content are mostly gone, while the same kinds for 2021 content are "
      "present, which is the CDN pruning, not a wrong rule.\n")
    # summary per year
    w("## Summary: missing file references per kind and year\n")
    w("Year = the year the owner (event or banner) first opened. A file shared by several owners counts once "
      "per owner. Distinct missing files: " +
      ", ".join(f"{typ} {len(v)}" for typ, v in sorted(distinct_missing.items())) +
      f"; overall {len(set().union(*distinct_missing.values()))}.\n")
    w("| Owner | Kind | " + " | ".join(years) + " | Total |")
    w("|---|---|" + "---|" * len(years) + "---|")
    tot = collections.Counter()
    for (typ, kk), c in kinds.items():
        if not c["missing"]:
            continue
        w(f"| {typ} | {kk} | " + " | ".join(str(c['y:' + y]) for y in years) + f" | {c['missing']} |")
        for y in years:
            tot[y] += c["y:" + y]
    w("| **all** | | " + " | ".join(f"**{tot[y]}**" for y in years) + f" | **{sum(tot.values())}** |\n")
    ne = [o for o in events if any(not status[p] for p in o.refs)]
    ng = [o for o in gachas if any(not status[p] for p in o.refs)]
    w(f"Owners with at least one missing file: **{len(ne)} of {len(events)} events**, **{len(ng)} of "
      f"{len(gachas)} gacha banners** ({sum(len(o.gachas) for o in ng)} of {sum(len(o.gachas) for o in gachas)} "
      "gacha rows).\n")
    per_year = collections.defaultdict(lambda: [0, 0, 0, 0])
    for o in events:
        per_year[year_of(o)][0] += 1
        per_year[year_of(o)][1] += o in ne
    for o in gachas:
        per_year[year_of(o)][2] += 1
        per_year[year_of(o)][3] += o in ng
    w("| Year | Events | with missing files | Gacha banners | with missing files |")
    w("|---|---|---|---|---|")
    for y in years:
        e = per_year[y]
        w(f"| {y} | {e[0]} | {e[1]} | {e[2]} | {e[3]} |")
    w("")
    biggest = sorted(ne + ng, key=lambda o: (-sum(1 for p in o.refs if not status[p]), o.start, o.label))[:15]
    w("Biggest gaps (most missing files):\n")
    for o in biggest:
        n = sum(1 for p in o.refs if not status[p])
        w(f"- {o.typ} `{o.label}` {o.ja} — {o.en}: {n} of {len(o.refs)} files")
    w("")
    sk = [(o, p) for o in owners for p in o.refs if status[p] == "stand-in"]
    w(f"Stand-ins in use: {len({p for _, p in sk})} files for {len({o.label for o, _ in sk})} owners "
      "(listed in each section).\n")
    w("Not covered: files that the scripts themselves name (talk-scene `.csf`, `Sound/TS_*` SE and `Voice_TS_*` "
      "packs, movies; they are named inside `Script/*.msgp`, not by the master), item icons of event shops and "
      "drops (`master_exchange_shop*` names no file; item thumbnails are shared with the rest of the game), "
      "dated menu BGM (`master_menu_bgm`: by date, not by event), and `master_banner` rows that target nothing.\n")

    def section(o):
        miss = [r for r in o.refs.values() if not status[r.path]]
        stand = [r for r in o.refs.values() if status[r.path] == "stand-in"]
        dates = f"{o.start or '—'} → {o.end or '—'}" if (o.start or o.end) else "undated"
        how = {"gl": " *GL*", "glossary": " *gloss*"}.get(o.how, "")
        w(f"### {md_escape(o.ja) or '(no name)'} — {md_escape(o.en) or '(no name)'}{how}\n")
        w(f"`{o.label}` (id {o.key}) · {dates} · {o.extra} · {len(miss)} missing of {len(o.refs)} files"
          + (f", {len(stand)} stand-in" if stand else ""))
        if o.typ == "event" and getattr(o, "missions", None):
            ok = sum(1 for _, _, g in o.missions if all(status.get(p) for p in g))
            w(f"\nMissions playable by the local server's check (maps and enemy models; story: script and text): "
              f"**{ok} of {len(o.missions)}**")
        if o.typ == "gacha":
            rows = ", ".join(f"`{g[0]}`" for g in o.gachas[:6]) + (f" … (+{len(o.gachas) - 6})" if len(o.gachas) > 6 else "")
            w(f"\nGacha rows: {rows}" + (f"\n\nPick-ups: {md_escape('; '.join(o.picks[:6]))}" if o.picks else ""))
        w("")
        if miss:
            w("| Missing file | Kind | Referenced by | What it probably is | Conf. | Evidence | Stand-in? |")
            w("|---|---|---|---|---|---|---|")
            for disp, r, paths in merge_bg(sorted(miss, key=lambda r: (r.order, r.path))):
                t, cf, evd = b.guess(o, r)
                rows = ", ".join(f"`{x}`" for x in r.rows[:3]) + (f" (+{len(r.rows) - 3})" if len(r.rows) > 3 else "")
                cols = "; ".join(f"`{c}`" for c in r.cols)
                w(f"| `{disp}` | {r.kind} | {cols}: {rows} | {md_escape(t)} | {cf} | {md_escape(evd) or '—'} "
                  f"| {standin_verdict(r.path)} |")
            w("")
        if stand:
            w("Stand-ins (made-up, `standin-assets/`): " + ", ".join(
                f"`{r.path.replace('/', '/etc2/', 1)}` ({r.kind})" for r in stand) + "\n")

    w(STANDIN_LEGEND + "\n")
    w("## Events\n")
    w("Ordered by first opening (master_event_term; else the area's window); weekly and undated areas last.\n")
    for o in sorted(ne, key=lambda o: (o.start == "", o.start, o.label)):
        section(o)
    w("## Gacha banners\n")
    w("One section per `master_gacha.banner_id` (the list banner; step-up chains and their steps share one), "
      "ordered by the first row's `opened_at`.\n")
    for o in sorted(ng, key=lambda o: (o.start == "", o.start, o.label)):
        section(o)
    if dangling:
        w("## Gacha rows whose banner_id has no master_banner row\n")
        w("A master gap rather than a file gap: `master_gacha.banner_id` names no `master_banner.id_label`, so the "
          "client has no list banner image name for them at all (a). Their other files are in the sections above "
          "when missing.\n")
        w("| banner_id | Gacha rows | Name | Opened |")
        w("|---|---|---|---|")
        for o in sorted(dangling, key=lambda o: (o.start, o.label)):
            w(f"| `{o.label}` | {', '.join(f'`{g[0]}`' for g in o.gachas[:4])}{' …' if len(o.gachas) > 4 else ''} "
              f"| {md_escape(o.ja)} — {md_escape(o.en)} | {o.start} |")
        w("")
    if P2:
        w("## Part 2: content beyond events and gacha blocked only by missing files\n")
        w("For each kind of content: how many master rows have every file their use needs (\"gating\" files: "
          "what the local server's checks or the screens load), how many are blocked by a missing one, and per "
          "missing file what it probably is and whether a made-up stand-in (like `standin-assets/`) would "
          "plausibly do. Files that are missing but don't block (voices, BGM, animations) are listed with "
          "\"not blocking\". Same sources and path rules as above. Images count as blocking where the screen shows "
          "them (an empty frame otherwise, as with the gacha list banners); those rows run with stand-ins.\n")
        w(STANDIN_LEGEND + "\n")
        L.extend(P2)
    os.makedirs(os.path.dirname(os.path.abspath(a.md)), exist_ok=True)
    with open(a.md, "w", encoding="utf-8") as f:
        f.write("\n".join(L) + "\n")
    if a.json:
        def dump(o):
            return dict(type=o.typ, key=o.key, label=o.label, ja=o.ja, en=o.en, start=o.start, end=o.end,
                        files=[dict(path=r.path, kind=r.kind, cols=r.cols, rows=r.rows, status=status[r.path] or "missing",
                                    guess=b.guess(o, r) if not status[r.path] else None) for r in o.refs.values()])
        with open(a.json, "w", encoding="utf-8") as f:
            json.dump(dict(events=[dump(o) for o in events], gachas=[dump(o) for o in gachas]), f,
                      ensure_ascii=False, indent=1)
    if a.residue:
        with open(a.residue, "w", encoding="utf-8") as f:
            for k, n in sorted(b.names.residue.items()):
                f.write(f"{k}\t{n}\n")
    return ne, ng, status


def main():
    rel = lambda *p: os.path.join(ROOT, *p)  # noqa: E731
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--db", default=rel("data", "basmaster-3.7.0.sqlite3"))
    ap.add_argument("--download", default=rel("work", "download-3.7.0"))
    ap.add_argument("--apk", default=rel("apk", "STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk"))
    ap.add_argument("--standins", default=rel("standin-assets"))
    ap.add_argument("--gl", default=rel("data", "basmaster-gl.sqlite3"))
    ap.add_argument("--names", default=rel("docs", "missing-assets-names.tsv"))
    ap.add_argument("--md", default=rel("docs", "missing-assets-3.7.0.md"))
    ap.add_argument("--json")
    ap.add_argument("--residue", help="write the Japanese names the glossary could not fully translate")
    a = ap.parse_args()
    b = Build(a)
    ev = b.events()
    ga, dangling = b.gachas()
    ne, ng, status = write(b, ev, ga, dangling, a, b.others())
    miss = {p for p, s in status.items() if not s}
    print(f"events {len(ne)}/{len(ev)} with missing files; gacha banners {len(ng)}/{len(ga)}; "
          f"distinct missing files {len(miss)}; untranslated names {len(b.names.residue)}")


if __name__ == "__main__":
    main()
