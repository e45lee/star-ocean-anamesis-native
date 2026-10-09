#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Reconstructs the per-gacha draw pools of STAR OCEAN: anamnesis (3.7.0).

The live server drew from tables named by `master_gacha.table_name` (`master_gacha_item_*`),
which were never shipped to the client: neither the 3.7.0 master DB nor the offline build's has them.
This script rebuilds a plausible pool for each of the 2,281 gachas from what the master DB
does contain, and writes it for the local server (`--server inproc`, server/).

Every rule is labelled with its source, as in docs/server-rules.md:
  (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
The rules are listed in RULES below, stored in the output's `rule` table and documented in
docs/server-rules.md#gacha-pools.

Usage:
  tools/build_gacha_pools.py [--master data/basmaster-3.7.0.sqlite3]
                             [--out data/gacha_pools.sqlite3] [--report FILE]

Output format (SQLite; see docs/server-rules.md for how the server uses it):
  gacha(gacha_id, id_label, name, gacha_type, kind, opened_at, closed_at, banner_id,
        pickup_source, kind_filter, is_bulk_bonus, bulk_count, is_stepup, stepup_number,
        next_stepup_gacha_id)                                    (the last five copied from master_gacha)
  gacha_rank(gacha_id, rank, rate, bonus_rate, set_id, rule)    rank in S A B C D
  pool_set(set_id, content_type, content_id, weight, released_at)  content_type 1 item, 2 role
  pool_set_info(set_id, size, description)
  gacha_pickup(gacha_id, content_type, content_id, source)       the banner's featured units
  rule(code, source, text)
  meta(key, value)
The output is deterministic for a given master DB.
"""
import argparse
import collections
import os
import re
import sqlite3
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

RULES = [
    # code, source, text
    ("R-TYPE", "a", "gacha_type 0 draws characters (roles), 1 weapons (master_item type 1), 2 is a box gacha whose "
     "contents are master_box_gacha (not rebuilt here; the server uses master_box_gacha directly)."),
    ("R-BASE", "a+b", "A drawn character is the base role of its role_category_id: the lowest-rarity member. Rarity 6 "
     "(and 4/5 of rank 1-2) roles are evolutions (master_role_evolution: rarity n -> n+1 for FOL and items), "
     "never drawn. The real 3.7.0 save owns rarity 3/rank 1, 4/2, 5/3 and 5/4 roles plus 4 rarity-6 roles (a); the banner "
     "images say '進化や覚醒などを含む、強化が行われる前の状態で出現いたします' (units come before any evolution or "
     "awakening) (b)."),
    ("R-RANK-ROLE", "a", "Character ranks: C = rarity 3 (rank 1, limitbreak common_people), B = rarity 4 (rank 2, "
     "common_guest), S and A = rarity 5. Evidence: the ticket gachas' rates and names - ★4キャラ (B 100), "
     "★4～5キャラ (S 2.2 / A 3.8 / B 94), ★5キャラ (S 2.2 / A 97.8), ★5エースキャラ (S 100); rate headings "
     "gacha_tilte_message_0002..0004 are ★5/★4/★3."),
    ("R-SA-PICKUP", "a+d", "On a banner with featured (pick-up) characters, S = the pick-up characters and A = every "
     "other ★5 in the general pool. Evidence: step-up steps named 'PU1体確定' (one pick-up guaranteed) have "
     "bonus_s_rank_rate 100 (a); that A is 'the rest' is (d)."),
    ("R-SA-ACEONLY", "b", "On the '10連10ステップ目PU1体確定' step-ups A holds the general aces only (no party roles): "
     "their banner images say '★5はエースだけ!' (e.g. 20200917_chara_PU_001, 20210610_chara_PU_003)."),
    ("R-SA-NOPICKUP", "a+d", "On a banner without pick-ups, S = the ace ★5s (rank 4, limitbreak common_ace) and A = "
     "the other ★5s (rank 3, common_party). Evidence: the ★5エース ticket is S 100 %, its text says an ace is a "
     "high-ability character, and the plain ★5 ticket is S 2.2 / A 97.8 (a); the split for the standard banner "
     "(S 2.2 / A 3.8) is (d)."),
    ("R-GENERAL", "a+b", "The general ★5 pool is the permanent line-up: the ★5 roles offered by the exchange shops "
     "that list it (福袋 / GW / 700万DL / 覚醒 / マーレゼリア coin shops, >= 50 roles each) or by a "
     "ピックアップキャラコイン shop (a new unit's coin): 70 aces and 15 party roles in their base forms (a). Every other ★5 - all "
     "seasonal costumes (花嫁, 渚, 歌星, 聖夜 ...), the 神 series, SRF, event units - is limited (期間限定): "
     "pick-up only. The split coincides with the costume names (a), and the SO2メモリアル banner image says "
     "'ピックアップは期間限定キャラのみ' over five seasonal SO2 units (b)."),
    ("R-LIMITED", "c+d", "Limited characters are never in a general pool, only as pick-ups of a banner that "
     "features them: the not-general ★5s (R-GENERAL), collaboration roles (id_label role_cc*: Tales of, Persona, NieR, Sakura Wars, Guilty Gear, "
     "FFBE, Attack on Titan, Valkyrie Profile, Radiata...) (c: collab units were limited to collab banners), exceed "
     "roles (rank 5, sold through the paid 'universe pass' banners gacha_paid_role_*) (a: those banners pick them "
     "up) and the units handed out by missions (master_mission_clear_present, master_mission_drop) (d)."),
    ("R-RELEASE-ROLE", "a+d", "A role is released at master_role.opened_at and withdrawn at closed_at (a). The 222 "
     "roles dated 2017-05-20 04:00 (the earliest value; the older history is collapsed into it) count as released "
     "at launch (d). Rows with id_label not starting role_c (check_*, cp*) and roles withdrawn at 2017-05-20 05:00, an "
     "hour after that epoch ('※ダミーホームテスト狼アンリ', 'ティニーク(狼版)', 'アイドル子ティカ'), are test rows and "
     "excluded (a)."),
    ("R-WINDOW", "a+d", "A gacha's pool holds every unit released by the end of its window (closed_at, cut at the "
     "service end 2021-06-24 14:30), each with its release time (pool_set.released_at); the server draws only units "
     "with released_at <= its clock, so a unit released mid-window joins the pool on its release day and a "
     "permanent banner grows over the years (a: dates; d: live pools grew the same way)."),
    ("R-PU-PERMANENT", "a+d", "Gachas drawing from the permanent tables (table_name master_gacha_item_jousetu = 常設 "
     "'permanent': the standard キャラガチャ, the ★3..★5 / ★5エース tickets, the 定常武器 gachas; _sphere211; _galaxy) "
     "have no pick-ups: their master_gacha_image rows are showcases (a: table names, the tickets' fixed rates; d: "
     "showcase reading)."),
    ("R-PU-GROUP", "a", "Pick-ups from master_gacha_pickup via master_gacha.gacha_pickup_group_id."),
    ("R-PU-IMAGE", "a", "Pick-ups from master_gacha_image rows of the gacha: content_type 2 = role (shown in its "
     "rarity-6 form; mapped to the base role, R-BASE), 1 = weapon item, 0 = role or item by id."),
    ("R-PU-NAME", "a+d", "Pick-ups from the banner title (master_text of name_message_id): names in brackets "
     "(e.g. 'ピックアップキャラガチャ(花嫁レナ/花嫁イヴリーシュ)') matched to master_person names (roles) or "
     "master_item names (weapons); a character name matches that person's ★5 base roles released by the close "
     "of the banner (d: the matching)."),
    ("R-PU-SERIES", "a+b+c", "A banner named after a game ('SO4キャラピックアップガチャ', 'スターオーシャン5発売日記念...', "
     "'SO3メモリアル...'; 'スターオーシャン発売日' = SO1) without named characters picks up that game's cast: its general "
     "★5s (aces and party), or for a メモリアル banner its limited (seasonal) aces (b: the SO5 banner image 'スターオーシャン5★5キャラが10連で"
     "1体確定' shows the base cast, the SO2メモリアル image says 'ピックアップは期間限定キャラのみ'). The cast is master_person id_label cp01xx..cp05xx = SO1..SO5 (a: labels; c: the casts, e.g. cp05 = Fidel, "
     "Miki of SO5, cp04 = Edge, Reimi of SO4; cp00 are anamnesis originals)."),
    ("R-PU-SIBLING", "a+d", "A gacha without own evidence takes the pick-ups of the gachas sharing its banner_id "
     "(the steps of a step-up and the single/10-draw variants of one banner) (a: shared banner; d: same pick-ups); "
     "applied to their own evidence first and again after R-PU-THEME and R-PU-NEW (a rerun under the original's "
     "banner_id, e.g. 復刻メイド1)."),
    ("R-PU-RERUN", "d", "A rerun (復刻) banner without own evidence takes the pick-ups of the earlier banners whose "
     "title contains its event key (e.g. 復刻花嫁2020 -> banners titled with 花嫁2020), or both halves of a two-word "
     "key (復刻桜花桜雲 -> 'ピックアップキャラガチャ(桜花のマリア/桜雲のディアス)'). Applied after R-PU-NEW and a second "
     "R-PU-SIBLING pass, so it sees every earlier banner's pick-ups."),
    ("R-PU-ROLEPICK", "a+d", "'ロールピックアップ' banners naming a class (アタッカー, ディフェンダー, シューター, "
     "キャスター, ヒーラー) pick up every general-pool ace of that master_role.category_type."),
    ("R-PU-THEME", "c+d", "A seasonal rerun without other evidence ('復刻花嫁2020', '復刻正月2021', '復刻ハロウィン1', "
     "'復刻神級(2)') picks up the aces of that event: units whose names carry the costume word (花嫁/花婿, 渚/真夏/常夏, "
     "歌星 for アイドル, メイド/執事) released in that year, or units released in the event's window (正月 01-01..01-07, "
     "xmas/クリスマス 12-01..12-24, ハロウィン 10-20..10-31, バレンタイン 01-25..02-14, costumes only: not a plain *_b01a character; ハロウィンN = the N-th Halloween, "
     "2016+N) (c: the seasonal events and their costume names; d: the windows). Checked against the banner images "
     "of 復刻正月2021, 復刻ハロウィン2020, 復刻クリスマス2020 and 復刻バレンタイン2021: all four match (b)."),
    ("R-PU-BANNERART", "b", "Pick-ups read off the banner images where the master data names none: the 衣装コンテスト "
     "2018 step-ups show ★5ヒーローベルダ / ★5ナースフィオーレ (20200917_chara_PU_001), the 2019 ones ★5花魁ミュリア / "
     "★5ハンターセリーヌ (20200903_chara_002); 復刻神級1 神翼のマリア / 賢神のマスティマ, 2 神龍のアシュトン / 神星のレナ / "
     "神翼のフェイト, 3 神弓のレイミ / 神導のソフィア (20210603_chara_PU_006, _007, 20210610_chara_PU_005); the 2020 "
     "maid step-ups メイド1 = メイドのクレア / メイドのネル, メイド2 = 執事のレオン / メイドのソフィア (20201008_chara_PU_003, _004; "
     "also their 復刻 reruns). Added to what the other rules found (tools/gacha_verify.py, docs/gacha-verify.md): "
     "ホワイトデー限定復刻1/2 (five units each, 'この5キャラをピックアップ!'), イヴリーシュ誕生日記念 (six Evelysse "
     "costumes), ステップアップシグムント1-3 (シグムント), EP2 CHAPTER:10 (six EP2 characters with マスティマ; its rates "
     "S 6 / A 0 (a)), 2018年福袋 (the 4 常夏 and 3 Halloween-2017 units next to the brides: '11キャラ')."),
    ("R-PU-NEW", "d", "A pick-up banner (not a rerun) still without evidence picks up the ★5 roles (weapons) released on its "
     "opening day (master_role.opened_at's date = the gacha's)."),
    ("R-PU-RELEASE", "d", "A pick-up unit released after the banner opened but before it closed counts as released "
     "by the banner (it is added to the S pool, never to the general pools)."),
    ("R-RANK-WEAPON", "a", "Weapon ranks: A = rarity 5, B = rarity 4, C = rarity 3. Evidence: ★3/★4/★5武器 tickets "
     "are C/B/A 100 %; the ★4～5 fill tickets are A 29.44 / B 70.56."),
    ("R-S-WEAPON", "a+d", "Weapon S (used by a few step-ups with bonus_s_rank_rate 100) = the banner's pick-up "
     "weapons; A = the general ★5 pool including those pick-ups (d: uniform within A)."),
    ("R-W5-POOL", "a+d", "The general ★5 weapon pool: the weapons ever featured by a weapon gacha image "
     "(master_gacha_image content_type 1; released = the first featuring gacha's opened_at) (a), plus the launch "
     "set: rarity-5 weapons of the W01..W17 families with serial_number <= 392, excluding placeholders (未定) and "
     "coin-shop weapons (コインウェポン) (d: the launch set). Other rarity-5 weapons (event rewards, item_weapon_*) "
     "are not drawn (d)."),
    ("R-W34-POOL", "a+d", "★3 and ★4 weapon pools: every master_item type 1 of that rarity (51 and 52 rows) (a), "
     "released at their weapon kind's opened_at (master_weapon_kind.opened_at, e.g. whip 2020-06-25) (a) or at "
     "launch (d)."),
    ("R-KIND", "a+d", "Weapon banners restricted by kind in their title ('定常武器ガチャ【近接】【ナックル/双剣/剣&鞘/鎌】', "
     "'補填武器チケット：杖', 'gacha_pickup_weapon_sword_*') draw only those kinds; 【遠距離】 alone = range-type 2 "
     "without the magic kinds; 紋章武器 = 杖/オーブ/本 (a: titles; d: the two group readings)."),
    ("R-WEIGHT", "d", "Within a rank, every unit has the same weight (the live per-unit rates are unknown; the rate "
     "dialog showed them, but no copy survives)."),
    ("R-EMPTY", "d", "A rank with rate > 0 whose pool would be empty falls back: S -> the A pool, A -> the S pool "
     "(recorded in gacha_rank.rule)."),
]

ROLE_CLASS = {"common_people": "people", "common_guest": "guest", "common_party": "party",
              "common_ace": "ace", "common_exceed": "exceed"}
CLASS_NAMES = {1: "アタッカー", 2: "ディフェンダー", 3: "シューター", 4: "キャスター", 5: "ヒーラー"}
LAUNCH = "2016-01-01 00:00:00"
# R-PU-BANNERART: pick-ups read off banner images (work/gacha-banners/images) for titles that name none.
BANNER_ART = [
    ("衣装コンテスト2018", ("ヒーローベルダ", "ナースフィオーレ"), "20200917_chara_PU_001"),
    ("衣装コンテスト2019", ("花魁ミュリア", "ハンターセリーヌ"), "20200903_chara_002"),
    ("神級(1)", ("神翼のマリア", "賢神のマスティマ"), "20210603_chara_PU_006"),
    ("神級(2)", ("神龍のアシュトン", "神星のレナ", "神翼のフェイト"), "20210603_chara_PU_007"),
    ("神級(3)", ("神弓のレイミ", "神導のソフィア"), "20210610_chara_PU_005"),
    # the 2020-10-08 maid step-ups (and their 2021-03-18 reruns): '…メイド1' / '…メイド2' carry no year, so
    # R-PU-THEME must not read the digit (docs/gacha-verify.md finding 2); the banners say 復刻メイド and show
    ("メイド1", ("メイドのクレア", "メイドのネル"), "20201008_chara_PU_003"),
    ("メイド2", ("執事のレオン", "メイドのソフィア"), "20201008_chara_PU_004"),
]
# R-PU-BANNERART (added units): banners whose featured units no rule recorded (docs/gacha-verify.md finding 1).
# (title regex, art keys = master_person id_label of the costume, image, what the banner says). The units are
# added to the gacha's pick-ups (so to its S pool), next to whatever the other rules found.
BANNER_ART_ADD = [
    (r"^ホワイトデー限定復刻ピックアップキャラガチャ1$",
     ("cp0301_b02a", "cp0401_b03a", "cp0501_b02a", "cp0101_b02a", "cp0207_b02a"), "20200312_chara_PU_003",
     "この5キャラをピックアップ! (花婿フェイト, 水着エッジ, 冬空フィデル, 渚のラティクス, 桜雲のディアス)"),
    (r"^ホワイトデー限定復刻ピックアップキャラガチャ2$",
     ("cp0304_b02a", "cp0503_b02a", "cp0204_b03a", "cp0306_b03a", "cp0208_b02a"), "20200312_chara_PU_004",
     "この5キャラをピックアップ! (花婿クリフ, 吸血鬼ヴィクトル, 雪空アシュトン, 狼アルベル, 執事のレオン)"),
    (r"^イヴリーシュ誕生日記念ガチャ$",
     ("cp0002_b03a", "cp0002_b05a", "cp0002_b06a", "cp0002_b07a", "cp0002_b08a", "cp0002_b09a"),
     "20201224_chara_PU_002", "ピックアップは6人のイヴリーシュのみ!"),
    (r"^ステップアップシグムントガチャ\d", ("cc0009_b01a",), "banner_gacha_pickup_role_0085",
     "★5シグムント出現確率UP!!"),
    (r"^EP2 CHAPTER:10 公開記念キャラガチャ$",
     ("cp0013_b01a", "cp0014_b01a", "cp0015_b01a", "cp0016_b01a", "cp0017_b01a", "cp0019_b01a"),
     "20190501_chara_PU_002", "★5キャラクターはピックアップされているEP2キャラクター6人のみ (S 6 %, A 0 %: a)"),
    (r"^2018年福袋限定チケットガチャ",
     ("cp0502_b03a", "cp0302_b02a", "cp0402_b02a", "cp0408_b02a", "cp0312_b02a", "cp0503_b02a", "cp0102_b02a"),
     "pickup_img_chara_1712_017", "花嫁、常夏、ハロウィン向けの11キャラ: the 4 brides R-PU-NAME finds plus the "
     "4 常夏 and 3 Halloween-2017 units (c: costume names)"),
]
# R-PU-PERMANENT: the server tables of the permanent banners and tickets (常設 = permanent).
PERMANENT_TABLES = {"master_gacha_item_jousetu", "master_gacha_item_sphere211", "master_gacha_item_galaxy"}
# R-PU-THEME: seasonal event keys in rerun titles -> (costume words in the unit names, or None; release
# window as (month-day from, month-day to) in the event's year).
THEMES = [
    ("花嫁", ("花嫁", "花婿"), None),
    ("水着", ("渚", "真夏", "常夏"), None),
    ("アイドル", ("歌星",), None),
    ("メイド", ("メイド", "執事"), None),
    ("正月", None, ("01-01", "01-07")),
    ("xmas", None, ("12-01", "12-24")),
    ("クリスマス", None, ("12-01", "12-24")),
    ("ハロウィン", None, ("10-20", "10-31")),
    ("バレンタイン", None, ("01-25", "02-14")),
]
# master_role.opened_at of every role that existed by May 2017 (222 roles): the history before it is
# collapsed into this one value, so those roles count as released at launch (R-RELEASE-ROLE).
ROLE_EPOCH = "2017-05-20 04:00:00"
# The service ended with master_global.service_stop_day (2021/06/24 14:30); banner windows are cut there.
SERVICE_END = "2021-06-24 14:30:00"


def zen2han(s):
    """Full-width ASCII -> half-width, and normalise a few punctuation variants."""
    out = []
    for ch in s or "":
        o = ord(ch)
        if 0xFF01 <= o <= 0xFF5E:
            ch = chr(o - 0xFEE0)
        elif ch == "　":
            ch = " "
        out.append(ch)
    return "".join(out).replace("＆", "&")


def norm_name(s):
    return re.sub(r"[\s・･]", "", zen2han(s or ""))


class Master:
    def __init__(self, path):
        self.db = sqlite3.connect(f"file:{path}?mode=ro", uri=True)
        self.db.row_factory = sqlite3.Row
        q = self.db.execute
        self.text = {r["message_id"]: r["text_value"] for r in q("select message_id, text_value from master_text")}
        self.roles = {r["id"]: dict(r) for r in q("select * from master_role")}
        self.persons = {r["id"]: dict(r) for r in q("select id, id_label, name_message_id from master_person")}
        self.items = {r["id"]: dict(r) for r in q(
            "select id, id_label, serial_number, name_message_id, rarity, type, master_weapon_id from master_item")}
        self.weapons = {r["id"]: dict(r) for r in q("select id, id_label, master_weapon_kind_id from master_weapon")}
        self.kinds = {r["id"]: dict(r) for r in q("select * from master_weapon_kind")}
        self.gachas = [dict(r) for r in q("select * from master_gacha order by opened_at, id")]
        self.gacha_by_id = {g["id"]: g for g in self.gachas}
        self.pickup_groups = collections.defaultdict(list)
        for r in q("select pickup_group_id, master_role_id from master_gacha_pickup order by id"):
            self.pickup_groups[r["pickup_group_id"]].append(r["master_role_id"])
        self.images = collections.defaultdict(list)
        for r in q("select master_gacha_id, content_type, content_id from master_gacha_image "
                   "where content_id is not null order by master_gacha_id, view_index, id"):
            self.images[r["master_gacha_id"]].append((r["content_type"], r["content_id"]))
        self.box_counts = {r[0]: r[1] for r in q("select master_gacha_id, count(*) from master_box_gacha group by 1")}
        # R-GENERAL: the roles of the exchange shops that list the permanent ★5 line-up (福袋 / GW / 700万DL /
        # 覚醒 / マーレゼリア coins: >= 50 roles each) and of the ピックアップキャラコイン shops (a new unit's coin)
        self.shop_roles = set()
        tx = self.text
        for sid, nm in q("select id, name_message_id from master_exchange_shop").fetchall():
            rs = {r[0] for r in q("select content_id from master_exchange_shop_contents "
                                  "where master_exchange_shop_id = ? and content_type = 2", (sid,))}
            if len(rs) >= 50 or "ピックアップキャラコイン" in (tx.get(nm) or ""):
                self.shop_roles |= rs
        self.mission_roles = {r[0] for r in q(
            "select content_id from master_mission_clear_present where content_type = 2 union "
            "select content_id from master_mission_drop where content_type = 2")}


class Builder:
    def __init__(self, m):
        self.m = m
        self._base_roles()
        self._weapons()

    # ---- characters ---------------------------------------------------------------------
    def _base_roles(self):
        m = self.m
        by_cat = collections.defaultdict(list)
        for r in m.roles.values():
            if r["id_label"].startswith("role_c"):
                by_cat[r["role_category_id"]].append(r)
        self.base_of = {}   # any role id -> base role id (R-BASE)
        self.base = {}      # base role id -> info
        for cat, rs in by_cat.items():
            rs.sort(key=lambda r: (r["rarity"], r["serial_number"] or 0, r["id"]))
            b = rs[0]
            for r in rs:
                self.base_of[r["id"]] = b["id"]
            if b["rarity"] not in (3, 4, 5):
                continue  # categories whose lowest form is rarity 6: special forms, never drawn
            cls = ROLE_CLASS.get(b["limitbreak_id_label"], "special")
            limited = []
            if b["id_label"].startswith("role_cc"):
                limited.append("collab")
            if cls == "exceed":
                limited.append("exceed")
            if b["id"] in m.mission_roles or any(r["id"] in m.mission_roles for r in rs):
                limited.append("mission")
            if b["rarity"] == 5 and not any(r["id"] in m.shop_roles for r in rs):
                limited.append("limited")  # R-GENERAL: not in the permanent line-up (seasonal, 神, SRF, events)
            if (b["closed_at"] or "9999") <= "2017-05-20 05:00:00":
                continue  # R-RELEASE-ROLE: withdrawn an hour after the epoch = test / dummy rows
            self.base[b["id"]] = dict(id=b["id"], label=b["id_label"], rarity=b["rarity"], rank=b["rank"], cls=cls,
                                      person=b["master_person_id"], ctype=b["category_type"],
                                      opened=LAUNCH if (b["opened_at"] or LAUNCH) <= ROLE_EPOCH else b["opened_at"], closed=b["closed_at"] or "9999",
                                      limited=limited)
        # the plain characters' names (persons *_b01a): a seasonal window never picks them up
        self.plain_names = {norm_name(self.m.text.get(p["name_message_id"])) for p in self.m.persons.values()
                            if p["id_label"].endswith("_b01a")}
        # costume (master_person id_label) -> base ★5 roles (R-PU-BANNERART added units)
        self.base_by_art = collections.defaultdict(list)
        for b in sorted(self.base.values(), key=lambda b: b["id"]):
            if b["rarity"] == 5:
                self.base_by_art[self.person_label(b)].append(b["id"])
        # person name -> base ★5 roles
        self.person_roles = collections.defaultdict(list)
        for b in self.base.values():
            if b["rarity"] == 5:
                p = self.m.persons.get(b["person"])
                if p:
                    self.person_roles[norm_name(self.m.text.get(p["name_message_id"]))].append(b["id"])

    def person_label(self, b):
        p = self.m.persons.get(b["person"])
        return p["id_label"] if p else ""

    def roles_released(self, t0, t1, pred):
        """Base roles released by t1 and not withdrawn before t0 (the gacha window)."""
        return sorted(b["id"] for b in self.base.values() if b["opened"] <= t1 and b["closed"] > t0 and pred(b))

    # ---- weapons ------------------------------------------------------------------------
    def _weapons(self):
        m = self.m
        self.first_featured = {}
        for g in m.gachas:
            if g["gacha_type"] != 1:
                continue
            for ct, cid in m.images.get(g["id"], []):
                if cid in m.items and m.items[cid]["type"] == 1:
                    t = g["opened_at"]
                    if cid not in self.first_featured or t < self.first_featured[cid]:
                        self.first_featured[cid] = t
        self.wpn = {}  # item id -> info (drawable weapons)
        for it in m.items.values():
            if it["type"] != 1 or it["rarity"] not in (3, 4, 5):
                continue
            w = m.weapons.get(it["master_weapon_id"])
            kind = m.kinds.get(w["master_weapon_kind_id"]) if w else None
            if not kind or not kind["is_show"] or kind["id_label"] == "W99St":
                continue
            name = m.text.get(it["name_message_id"]) or ""
            kopen = kind["opened_at"] or LAUNCH
            if it["rarity"] == 5:
                if it["id"] in self.first_featured:
                    rel, how = max(self.first_featured[it["id"]], kopen), "featured"
                elif (it["serial_number"] or 0) <= 392 and re.match(r"item_W\d\d[A-Za-z]{2}_", it["id_label"]) \
                        and "未定" not in name and "コインウェポン" not in name:
                    rel, how = kopen, "launch"
                else:
                    continue
            else:
                rel, how = kopen, "common"
            self.wpn[it["id"]] = dict(id=it["id"], rarity=it["rarity"], kind=kind["id_label"],
                                      kind_name=m.text.get(kind["kind_message_id"]) or "",
                                      range=kind["weapon_range_type"], released=rel, how=how, name=name)
        self.kind_by_name = {}
        for k in m.kinds.values():
            if k["is_show"] and k["kind_message_id"] and k["id_label"] != "W99St":
                self.kind_by_name[zen2han(m.text.get(k["kind_message_id"]) or "")] = k["id_label"]
        self.item_by_name = collections.defaultdict(list)
        for it in m.items.values():
            if it["type"] == 1 and it["rarity"] == 5:
                self.item_by_name[norm_name(m.text.get(it["name_message_id"]))].append(it["id"])

    def kind_filter(self, g):
        """R-KIND: the set of weapon kind labels a weapon gacha is restricted to, or None.
        Kind words are read only inside 【...】 and after '：' (e.g. 定常武器ガチャ【近接】【ナックル/双剣】,
        補填武器チケット：杖), so '1本確定' or '紋章石' in a title don't restrict it."""
        name = zen2han(self.m.text.get(g["name_message_id"]) or "")
        regions = re.findall(r"【([^】]*)】", name) + re.findall(r":(.*)$", name)
        tokens = [t for r in regions for t in re.split(r"[/・、,]", r)]
        kinds = {self.kind_by_name[t] for t in tokens if t in self.kind_by_name}
        magic = {"W02Ro", "W08Be", "W17Bo"}
        if "紋章武器" in tokens:
            kinds |= magic
        label_map = {"sword": {"W01Sw"}, "cane": {"W02Ro"}, "dagger": {"W06Da"}, "knuckle": {"W04Kn"},
                     "scabbard": {"W05Sa"}, "shoot": {"W03Gu", "W07Bw"}}
        mm = re.search(r"weapon_(sword|cane|dagger|knuckle|scabbard|shoot)_", g["id_label"])
        if mm and not kinds:
            kinds = set(label_map[mm.group(1)])
        if kinds:
            return kinds
        shown = {k["id_label"]: k for k in self.m.kinds.values() if k["is_show"] and k["id_label"] != "W99St"}
        if "近接" in tokens or "近距離" in tokens or name.startswith("近距離武器"):
            return {l for l, k in shown.items() if k["weapon_range_type"] == 1}
        if "遠距離" in tokens:
            return {l for l, k in shown.items() if k["weapon_range_type"] == 2} - magic
        return None

    def weapons_released(self, t1, rarity, kinds):
        return sorted(w["id"] for w in self.wpn.values()
                      if w["rarity"] == rarity and w["released"] <= t1 and (kinds is None or w["kind"] in kinds))

    def released_at(self, ct, cid):
        if ct == 2:
            return self.base[cid]["opened"] if cid in self.base else LAUNCH
        return self.wpn[cid]["released"] if cid in self.wpn else LAUNCH

    # ---- pick-ups -----------------------------------------------------------------------
    def title(self, g):
        return zen2han(self.m.text.get(g["name_message_id"]) or "")

    def own_pickups(self, g):
        """Pick-ups from the gacha's own rows: [(content_type, id, source)]."""
        m, out = self.m, []
        if g["table_name"] in PERMANENT_TABLES:
            return []  # R-PU-PERMANENT
        kind = g["gacha_type"]
        if kind == 0 and g["gacha_pickup_group_id"]:
            for rid in m.pickup_groups.get(g["gacha_pickup_group_id"], []):
                out.append((2, self.base_of.get(rid, rid), "R-PU-GROUP"))
        for ct, cid in m.images.get(g["id"], []):
            if kind == 0 and cid in m.roles:
                out.append((2, self.base_of.get(cid, cid), "R-PU-IMAGE"))
            elif kind == 1 and cid in m.items and m.items[cid]["type"] == 1:
                out.append((1, cid, "R-PU-IMAGE"))
        if not out:
            out = self.name_pickups(g)
        seen, res = set(), []
        for x in out:
            if (x[0], x[1]) not in seen and (x[0] != 2 or x[1] in self.base):
                seen.add((x[0], x[1]))
                res.append(x)
        return res

    def name_pickups(self, g):
        name = self.title(g)
        out = []
        groups = re.findall(r"[(（]([^()（）]*)[)）]", name)
        if g["gacha_type"] == 0:
            if "ロールピックアップ" in name:
                for ct, cn in CLASS_NAMES.items():
                    if cn in name:
                        for rid in self.roles_released(g["opened_at"], g["closed_at"], lambda b: b["cls"] == "ace" and
                                                       not b["limited"] and b["ctype"] == ct):
                            out.append((2, rid, "R-PU-ROLEPICK"))
            cands = [p for grp in groups for p in re.split(r"[/／、,]|or", grp)]
            # '連邦レイミ確定ガチャ', 'SO4HD発表記念エッジorレイミ確定ガチャ', '(ラティクスorミリー確定)'
            for mm in re.finditer(r"([^\s()]+?)確定", name):
                cands += re.split(r"or", mm.group(1))
            found = []
            for c in cands:
                c = norm_name(re.sub(r"確定$|のみ$", "", norm_name(c)))
                # not a name ('10連', '期間限定', '毎日'): skipped, unless it is one exactly ('連邦エッジ',
                # '2B', 'エレン巨人' hold those characters too)
                if len(c) < 2 or (c not in self.person_roles and re.search(r"\d|連|回|期間|ガチャ|限定|毎日|人", c)):
                    continue
                rids = self.person_roles.get(c)
                if not rids:  # 'SO4HD発表記念エッジ' -> エッジ: the longest person name the token ends with
                    ends = [n for n in self.person_roles if len(n) >= 2 and c.endswith(n)]
                    if ends:
                        rids = self.person_roles[max(ends, key=len)]
                if not rids:  # '花嫁/水着/ハロウィンのみ' -> every person whose name holds the word
                    rids = [r for n, rs in sorted(self.person_roles.items()) if c in n for r in rs]
                for rid in rids or []:
                    b = self.base[rid]
                    if b["opened"] <= g["closed_at"] and b["closed"] > g["opened_at"] and \
                            (b["rank"] >= 4 or len(rids) <= 3):
                        found.append((2, rid, "R-PU-NAME"))
            out += found
            if not found:
                # 'SO4キャラピックアップガチャ', 'スターオーシャン5発売日記念...': that game's cast (R-PU-SERIES)
                mm = re.search(r"SO([1-5])|スターオーシャン([1-5]?)発売", name)
                if mm:
                    n = mm.group(1) or mm.group(2) or "1"
                    # メモリアル: 'ピックアップは期間限定キャラのみ' (b: the SO2 memorial banner) -> the cast's limited
                    # (seasonal) aces; otherwise ('スターオーシャン5★5キャラが10連で1体確定') the cast's general aces
                    want = {"limited"} if "メモリアル" in name else set()
                    classes = ("ace",) if want else ("ace", "party")  # b: the SO5 image shows party members too
                    for rid in self.roles_released(g["opened_at"], g["closed_at"], lambda b: b["cls"] in classes and
                                                   set(b["limited"]) == want and
                                                   self.person_label(b).startswith("cp0" + n)):
                        out.append((2, rid, "R-PU-SERIES"))
        else:
            for grp in groups:
                for c in re.split(r"[/／、,]", grp):
                    for iid in self.item_by_name.get(norm_name(c), []):
                        out.append((1, iid, "R-PU-NAME"))
        return out

    def theme_pickups(self, g):
        """R-PU-THEME: '復刻花嫁2020/10連10ステップ目PU1体確定' -> the 花嫁/花婿 aces released in 2020."""
        name = self.title(g)
        for key, persons, _img in BANNER_ART:
            if re.search(re.escape(key) + r"(?!\d)", name):  # 'メイド2' is not 'メイド2018'

                return [(2, rid, "R-PU-BANNERART") for pn in persons for rid in self.person_roles.get(norm_name(pn), [])]
        aces = [b for b in sorted(self.base.values(), key=lambda b: (b["opened"], b["id"]))
                if b["cls"] == "ace" and set(b["limited"]) <= {"limited"} and b["opened"] <= g["closed_at"]]
        pname = lambda b: norm_name(self.m.text.get(self.m.persons[b["person"]]["name_message_id"])) \
            if b["person"] in self.m.persons else ""
        for word, costume, window in THEMES:
            mm = re.search(word + r"(\d{4}|\d)?", name)
            if not mm:
                continue
            y = mm.group(1)
            if y and len(y) == 1:
                y = str(2016 + int(y))  # ハロウィン1 = the first Halloween event (2017)
            if not y:
                continue
            out = []
            for b in aces:
                if costume and b["opened"][:4] == y and any(c in pname(b) for c in costume):
                    out.append((2, b["id"], "R-PU-THEME"))
                elif window and window[0] <= b["opened"][5:10] <= window[1] and b["opened"][:4] == y and \
                        pname(b) not in self.plain_names:  # costumes only, not a plain character
                    out.append((2, b["id"], "R-PU-THEME"))
            return out
        return []

    def resolve_pickups(self):
        m = self.m
        permanent = {g["id"] for g in m.gachas if g["table_name"] in PERMANENT_TABLES}
        own = {g["id"]: self.own_pickups(g) for g in m.gachas if g["gacha_type"] in (0, 1)}
        by_banner = collections.defaultdict(list)
        for g in m.gachas:
            if g["gacha_type"] in (0, 1) and g["banner_id"]:
                by_banner[(g["gacha_type"], g["banner_id"])].append(g["id"])
        res = {}
        for g in m.gachas:
            if g["gacha_type"] not in (0, 1):
                continue
            if g["id"] in permanent:
                res[g["id"]] = []
                continue
            p = own[g["id"]]
            if not p and g["banner_id"]:
                sib = []
                for s in by_banner[(g["gacha_type"], g["banner_id"])]:
                    sib += [(ct, cid, "R-PU-SIBLING") for ct, cid, _ in own[s]]
                p = sib
            res[g["id"]] = p
        # seasonal themes
        for g in m.gachas:
            if g["gacha_type"] == 0 and not res[g["id"]] and g["id"] not in permanent:
                res[g["id"]] = self.theme_pickups(g)
        # new releases on the opening day
        for g in m.gachas:
            if g["gacha_type"] not in (0, 1) or res[g["id"]] or g["id"] in permanent:
                continue
            name = self.title(g)
            if not re.search(r"PU|ピックアップ", name) or "復刻" in name:
                continue
            day = g["opened_at"][:10]
            if day <= ROLE_EPOCH[:10]:
                continue  # before the collapsed role dates: no release day is known
            if g["gacha_type"] == 0:
                res[g["id"]] = [(2, b["id"], "R-PU-NEW") for b in sorted(self.base.values(), key=lambda b: b["id"])
                                if b["rarity"] == 5 and b["rank"] >= 4 and b["opened"][:10] == day]
            else:
                res[g["id"]] = [(1, w["id"], "R-PU-NEW") for w in sorted(self.wpn.values(), key=lambda w: w["id"])
                                if w["rarity"] == 5 and w["how"] == "featured" and w["released"][:10] == day]
        # siblings again: a step or variant of a banner whose pick-ups came from a rule above (R-PU-NEW,
        # R-PU-THEME) shares them too (R-PU-SIBLING), e.g. a rerun under the original's banner_id
        for g in m.gachas:
            if g["gacha_type"] not in (0, 1) or res[g["id"]] or g["id"] in permanent or not g["banner_id"]:
                continue
            res[g["id"]] = [(ct, cid, "R-PU-SIBLING") for s in by_banner[(g["gacha_type"], g["banner_id"])]
                            for ct, cid, src in res.get(s, []) if src != "R-PU-SIBLING"]
        # reruns
        for g in m.gachas:
            if g["gacha_type"] not in (0, 1) or res[g["id"]] or g["id"] in permanent:
                continue
            name = self.title(g)
            if "復刻" not in name:
                continue
            key = re.sub(r"復刻|/?10連.*$|ピックアップ.*$|キャラガチャ.*$|ガチャ.*$|\(.*$|\d+$|\s+", "", name)
            key = key.strip()
            if len(key) < 3:
                continue
            # the key as a whole, else a two-word key's halves both in the title ('復刻桜花桜雲' ->
            # '(桜花のマリア/桜雲のディアス)')
            keys = [[key]] + [[key[:i], key[i:]] for i in range(2, len(key) - 1)]
            got = []
            for words in keys:
                for h in m.gachas:
                    if h["gacha_type"] == g["gacha_type"] and h["opened_at"] < g["opened_at"] and \
                            "復刻" not in self.title(h) and all(w in self.title(h) for w in words):
                        got += [(ct, cid, "R-PU-RERUN") for ct, cid, _ in res[h["id"]] if _ != "R-PU-RERUN"]
                if got:
                    break
            res[g["id"]] = got
        # R-PU-BANNERART (added units): featured units the banners show and no rule found
        for g in m.gachas:
            if g["gacha_type"] != 0 or g["id"] in permanent:
                continue
            name = self.title(g)
            for pat, arts, _img, _says in BANNER_ART_ADD:
                if re.search(pat, name):
                    res[g["id"]] = res[g["id"]] + [(2, rid, "R-PU-BANNERART") for a in arts
                                                   for rid in self.base_by_art.get(a, [])]
        # dedupe, stable
        for gid, p in res.items():
            seen, out = set(), []
            for x in p:
                if (x[0], x[1]) not in seen:
                    seen.add((x[0], x[1]))
                    out.append(x)
            res[gid] = out
        return res

    # ---- pools --------------------------------------------------------------------------
    def build(self):
        m = self.m
        pickups = self.resolve_pickups()
        sets, set_desc = {}, {}
        gacha_rows, rank_rows, pickup_rows = [], [], []

        def set_id(members, desc):
            key = tuple(members)
            if not key:
                return None
            if key not in sets:
                sets[key] = len(sets) + 1
                set_desc[sets[key]] = desc
            return sets[key]

        for g in m.gachas:
            t0, gt = g["opened_at"], g["gacha_type"]
            t = min(g["closed_at"] or SERVICE_END, SERVICE_END)  # R-WINDOW
            name = self.title(g)
            rates = {k: g[f"{k.lower()}_rank_rate"] or 0.0 for k in "SABCD"}
            bonus = {k: (g[f"bonus_{k.lower()}_rank_rate"] or 0.0) if g["is_bulk_bonus"] else 0.0 for k in "SABC"}
            bonus["D"] = 0.0
            kind = {0: "role", 1: "weapon", 2: "box"}.get(gt, "?")
            p = pickups.get(g["id"], [])
            srcs = sorted({s for _, _, s in p})
            kf = self.kind_filter(g) if gt == 1 else None
            gacha_rows.append((g["id"], g["id_label"], name, gt, kind, g["opened_at"], g["closed_at"], g["banner_id"],
                               ",".join(srcs) or None, ",".join(sorted(kf)) if kf else None,
                               g["is_bulk_bonus"] or 0, g["bulk_count"] or 0, g["is_stepup"] or 0,
                               g["stepup_number"] or 0, g["next_stepup_gacha_id"] or 0))
            for ct, cid, s in p:
                pickup_rows.append((g["id"], ct, cid, s))
            if gt == 2:
                continue
            pools = {}
            if gt == 0:
                pu = sorted({cid for ct, cid, _ in p if ct == 2})
                general5 = self.roles_released(t0, t, lambda b: b["rarity"] == 5 and not b["limited"])
                pools["C"] = (self.roles_released(t0, t, lambda b: b["cls"] == "people" and not b["limited"]),
                              f"★3 people roles released by {t[:10]}", "R-RANK-ROLE")
                pools["B"] = (self.roles_released(t0, t, lambda b: b["cls"] == "guest" and not b["limited"]),
                              f"★4 guest roles released by {t[:10]}", "R-RANK-ROLE")
                if pu and "10ステップ目" in name:
                    # R-SA-ACEONLY: the 10-step pick-up step-ups say '★5はエースだけ!' (b: banner images)
                    pools["S"] = (pu, f"pick-ups of {g['id_label']}", "R-SA-PICKUP")
                    pools["A"] = ([r for r in general5 if r not in pu and self.base[r]["cls"] == "ace"],
                                  f"general ★5 aces released by {t[:10]} minus pick-ups", "R-SA-PICKUP+R-SA-ACEONLY")
                elif pu:
                    pools["S"] = (pu, f"pick-ups of {g['id_label']}", "R-SA-PICKUP")
                    pools["A"] = ([r for r in general5 if r not in pu],
                                  f"general ★5 roles released by {t[:10]} minus pick-ups", "R-SA-PICKUP")
                else:
                    pools["S"] = ([r for r in general5 if self.base[r]["cls"] == "ace"],
                                  f"general ★5 aces released by {t[:10]}", "R-SA-NOPICKUP")
                    pools["A"] = ([r for r in general5 if self.base[r]["cls"] != "ace"],
                                  f"general ★5 non-ace (party) roles released by {t[:10]}", "R-SA-NOPICKUP")
                pools["D"] = ([], "", "")
                ct_all = 2
            else:
                ksuf = f" of kinds {','.join(sorted(kf))}" if kf else ""
                pu = sorted({cid for ct, cid, _ in p if ct == 1 and (kf is None or
                             (cid in self.wpn and self.wpn[cid]["kind"] in kf) or cid not in self.wpn)})
                pools["C"] = (self.weapons_released(t, 3, kf), f"★3 weapons released by {t[:10]}{ksuf}", "R-RANK-WEAPON")
                pools["B"] = (self.weapons_released(t, 4, kf), f"★4 weapons released by {t[:10]}{ksuf}", "R-RANK-WEAPON")
                a5 = self.weapons_released(t, 5, kf)
                a5 = sorted(set(a5) | set(pu))
                pools["A"] = (a5, f"general ★5 weapons released by {t[:10]}{ksuf} (with pick-ups)", "R-W5-POOL")
                pools["S"] = (pu, f"pick-up weapons of {g['id_label']}", "R-S-WEAPON")
                pools["D"] = ([], "", "")
                ct_all = 1
            # R-EMPTY fallbacks
            for k, alt in (("S", "A"), ("A", "S")):
                if (rates[k] > 0 or bonus[k] > 0) and not pools[k][0] and pools[alt][0]:
                    pools[k] = (pools[alt][0], pools[alt][1], pools[k][2] + "+R-EMPTY")
            for k in "SABCD":
                members, desc, r = pools[k]
                sid = set_id([(ct_all, x, self.released_at(ct_all, x)) for x in members], desc) if (rates[k] > 0 or bonus[k] > 0) else None
                rank_rows.append((g["id"], k, rates[k], bonus[k], sid, r if sid else None))
        return dict(sets=sets, set_desc=set_desc, gacha=gacha_rows, rank=rank_rows, pickup=pickup_rows,
                    pickups=pickups)


def write(out, res, master_path):
    if os.path.exists(out):
        os.remove(out)
    db = sqlite3.connect(out)
    db.executescript("""
    create table meta(key text primary key, value text);
    create table rule(code text primary key, source text, text text);
    create table gacha(gacha_id integer primary key, id_label text, name text, gacha_type integer, kind text,
                       opened_at text, closed_at text, banner_id text, pickup_source text, kind_filter text,
                       is_bulk_bonus integer, bulk_count integer, is_stepup integer, stepup_number integer,
                       next_stepup_gacha_id integer);
    create table gacha_rank(gacha_id integer, rank text, rate real, bonus_rate real, set_id integer, rule text,
                            primary key (gacha_id, rank));
    create table pool_set(set_id integer, content_type integer, content_id integer, weight integer,
                          released_at text);
    create index pool_set_idx on pool_set(set_id);
    create table pool_set_info(set_id integer primary key, size integer, description text);
    create table gacha_pickup(gacha_id integer, content_type integer, content_id integer, source text);
    create index gacha_pickup_idx on gacha_pickup(gacha_id);
    """)
    db.executemany("insert into rule values (?,?,?)", RULES)
    db.executemany("insert into gacha values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)", res["gacha"])
    db.executemany("insert into gacha_rank values (?,?,?,?,?,?)", res["rank"])
    for key, sid in sorted(res["sets"].items(), key=lambda x: x[1]):
        db.executemany("insert into pool_set values (?,?,?,1,?)", [(sid, ct, cid, rel) for ct, cid, rel in key])
        db.execute("insert into pool_set_info values (?,?,?)", (sid, len(key), res["set_desc"][sid]))
    db.executemany("insert into gacha_pickup values (?,?,?,?)", res["pickup"])
    db.executemany("insert into meta values (?,?)", [
        ("generator", "tools/build_gacha_pools.py"),
        ("master", os.path.basename(master_path)),
        ("format", "1"),
        ("draw", "rank by gacha_rank.rate (bonus_rate for the bonus draw of a bulk draw when "
                 "master_gacha.is_bulk_bonus), then a unit from pool_set by weight"),
    ])
    db.commit()
    db.execute("vacuum")
    db.close()


def report(m, b, res, out_db):
    """Sanity checks and statistics (docs/server-rules.md#gacha-pools)."""
    db = sqlite3.connect(out_db)
    q = lambda s, a=(): db.execute(s, a).fetchall()
    lines = []
    P = lines.append
    # 1. every pick-up is in its gacha's pool
    missing = q("""select p.gacha_id, p.content_id from gacha_pickup p join gacha g using (gacha_id)
                   where g.kind != 'box' and not exists (select 1 from gacha_rank r join pool_set s using (set_id)
                   where r.gacha_id = p.gacha_id and s.content_id = p.content_id)""")
    # pick-ups filtered out by the kind filter are expected to be missing
    P(f"- pick-up units not in their gacha's pool: {len(missing)}")
    # 2. non-empty pools for ranks with rate > 0
    empty = q("select gacha_id, rank from gacha_rank where (rate > 0 or bonus_rate > 0) and set_id is null")
    P(f"- ranks with a rate > 0 and an empty pool: {len(empty)}")
    for gid, rk in empty[:10]:
        P(f"  - {m.gacha_by_id[gid]['id_label']} {rk}")
    fb = q("select count(*) from gacha_rank where rule like '%R-EMPTY%'")[0][0]
    P(f"- ranks filled by the R-EMPTY fallback: {fb}")
    # 3. no unit before its release: every unit's released_at is inside the window (the server filters by
    # its clock); count the units that join mid-window
    late = q("""select count(*) from gacha_rank r join gacha g using (gacha_id) join pool_set s using (set_id)
                where s.released_at > min(g.closed_at, ?)""", (SERVICE_END,))[0][0]
    mid = q("""select count(*), count(distinct r.gacha_id) from gacha_rank r join gacha g using (gacha_id)
               join pool_set s using (set_id) where s.released_at > g.opened_at""")[0]
    P(f"- pool units released after their gacha closed: {late}")
    P(f"- pool units released after their gacha opened (join on release day, R-WINDOW): {mid[0]} in {mid[1]} gachas")
    pu_late = q("""select count(*) from gacha_pickup p join gacha g using (gacha_id)
                   join pool_set s on s.content_id = p.content_id
                   join gacha_rank r on r.gacha_id = p.gacha_id and r.set_id = s.set_id and r.rank = 'S'
                   where s.released_at > g.opened_at""")[0][0]
    P(f"- of which pick-ups released after their banner opened (R-PU-RELEASE): {pu_late}")
    # 4. pool sizes per gacha type
    P("")
    P("| gacha type | gachas | S (min–max) | A | B | C |")
    P("|---|---|---|---|---|---|")
    for gt, label in ((0, "0 character"), (1, "1 weapon")):
        row = [label, str(q("select count(*) from gacha where gacha_type = ?", (gt,))[0][0])]
        for rk in "SABC":
            mn, mx = q("""select min(i.size), max(i.size) from gacha_rank r join gacha g using (gacha_id)
                          join pool_set_info i using (set_id) where g.gacha_type = ? and r.rank = ?""", (gt, rk))[0]
            row.append(f"{mn}–{mx}" if mn is not None else "–")
        P("| " + " | ".join(row) + " |")
    boxes = q("select count(*) from gacha where gacha_type = 2")[0][0]
    P(f"| 2 box | {boxes} | contents from master_box_gacha ({sum(m.box_counts.values())} slots) | | | |")
    P("")
    P("Pick-up evidence per gacha (first source):")
    cnt = collections.Counter()
    for gid, gt, src in q("select gacha_id, gacha_type, pickup_source from gacha where gacha_type < 2"):
        cnt[(gt, (src or "none").split(",")[0])] += 1
    for (gt, s), n in sorted(cnt.items()):
        P(f"- type {gt}: {s}: {n}")
    P(f"- distinct pool sets: {q('select count(*) from pool_set_info')[0][0]}, "
      f"rows: {q('select count(*) from pool_set')[0][0]}")
    db.close()
    return "\n".join(lines), missing


def default_master():
    """data/basmaster-3.7.0.sqlite3 (untracked), here or in the main checkout of a git worktree."""
    from soa_save.paths import master_db

    db = master_db()
    return str(db) if db else os.path.join(ROOT, "data", "basmaster-3.7.0.sqlite3")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[1])
    ap.add_argument("--master", default=default_master())
    ap.add_argument("--out", default=os.path.join(ROOT, "data", "gacha_pools.sqlite3"))
    ap.add_argument("--report", help="write the sanity-check report (markdown) here")
    a = ap.parse_args()
    if not os.path.exists(a.master):
        sys.exit(f"master DB not found: {a.master}")
    m = Master(a.master)
    b = Builder(m)
    res = b.build()
    os.makedirs(os.path.dirname(os.path.abspath(a.out)), exist_ok=True)
    write(a.out, res, a.master)
    text, missing = report(m, b, res, a.out)
    print(text)
    if a.report:
        with open(a.report, "w") as f:
            f.write(text + "\n")


if __name__ == "__main__":
    main()
