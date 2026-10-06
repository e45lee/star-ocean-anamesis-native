import os, sys; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); from common import *  # noqa: E402,F403
def erase_first(labels):
    out = []
    for l in labels:
        if l.get("style") in ("gold", "gold_r", "blue") and l.get("clear") is None and "cover" in l:
            out.append({"jp": "", "text": "", "box": l["cover"], "cover": l["cover"], "style": "erase"})
        out.append(l)
    return out
_write = write
def write(name, note, styles, labels, sources=None):
    _write(name, note, styles, erase_first(labels), sources)
TAG = L("ガチャ", "Draws", [73, 14, 60, 15], "tag", [72, 15, 42, 13])
S = {
 "tag": {"size": 12, "bold": 1, "fill": "#ffffff", "align": "left"},
 "gold": {"size": 24, "bold": 2, "fill": "#ffeab0", "outline": "#4a0800", "outline_width": 3, "clear": "shade", "clear_color": "#200400e0"},
 "gold_r": {"size": 24, "bold": 2, "fill": "#ffeab0", "outline": "#4a0800", "outline_width": 3, "align": "right", "clear": "shade", "clear_color": "#200400e0"},
 "bar_l": {"size": 14, "bold": 1, "fill": "#ffffff", "outline": "#000000", "outline_width": 1, "align": "left", "clear": "fill", "clear_color": "#0c0806ff"},
 "bar_r": {"size": 15, "bold": 2, "fill": "#ffe9a0", "outline": "#3a0800", "outline_width": 2, "align": "right", "clear": "none"},
 "blue": {"size": 24, "bold": 2, "fill": "#ffffff", "outline": "#0a3a8a", "outline_width": 3, "glow": "#40c0ffa0", "glow_radius": 2, "clear": "shade", "clear_color": "#0a1a3ab0"},
 "erase": {"clear": "inpaint"},
 "blue_s": {"size": 15, "bold": 1, "fill": "#ffffff", "outline": "#0a3a8a", "outline_width": 2, "clear": "none"},
}
def weapon_limited(name, kind, weapons):
    title = {"near": ("近距離武器\n限定ガチャ", "Melee Weapon\nLimited Draws"), "far": ("遠距離武器\n限定ガチャ", "Ranged Weapon\nLimited Draws"),
             "crest": ("紋章武器\n限定ガチャ", "Crest Weapon\nLimited Draws")}[kind]
    write(name, f"A limited weapon gacha's banner: a shaded title band and the bottom bar (weapon names: glossary.tsv / Global's).", S, [
        TAG,
        L(title[0], title[1], [268, 30, 186, 60], "gold_r", [262, 26, 194, 66], size=20),
        L("", weapons, [62, 92, 188, 20], "bar_l", [58, 90, 398, 24]),
        L("10連で★4以上1本確定!!", "10-chain: 1 ★4+ guaranteed!!", [258, 92, 196, 20], "bar_r", size=14)])
weapon_limited("banner_gacha_weapon_0002", "near", "Great Swords / OHS / Arms")
weapon_limited("banner_gacha_weapon_0002_002", "near", "Great Swords / OHS / Arms / Axes")
weapon_limited("banner_gacha_weapon_0003_002", "far", "Daggers / Bows / Guns")
weapon_limited("banner_gacha_weapon_0003_003", "far", "Rifles / Launchers")
weapon_limited("banner_gacha_weapon_0004", "crest", "Staffs / Orbs / Tomes")
weapon_limited("banner_gacha_weapon_0005_002", "near", "Knuckles / Dual / B & S / Scythes")
weapon_limited("banner_gacha_weapon_0005_003", "near", "Knuckles / Dual / B & S / Scythes / Whips")
write("banner_gacha_weapon_0001", "The standard weapon gacha's banner.", S, [
    TAG,
    L("武器ガチャ", "Weapons Draw", [190, 15, 140, 16], "blue_s", [188, 15, 144, 15], clear="inpaint"),
    L("10連で", "10-chain", [58, 34, 120, 32], "gold", [58, 32, 112, 36]),
    L("★4以上の武器が1本確定!!", "1 ★4+ weapon guaranteed!!", [104, 86, 260, 26], "gold", [100, 82, 270, 32], size=20)])
write("banner_gacha_role_0002", "The standard character gacha's banner.", S, [
    TAG,
    L("10連で", "10-chain", [58, 46, 100, 32], "gold", [56, 46, 98, 34]),
    L("★4以上のキャラが1体確定!", "1 ★4+ character guaranteed!", [58, 84, 344, 28], "gold", [56, 82, 346, 32], size=20)])
for n, (big_jp, big_en) in {"banner_ticketgacha_fill_weapon_sword_0001": ("片手剣", "OHS"), "banner_ticketgacha_fill_weapon_cane_0001": ("杖", "Staff"),
        "banner_ticketgacha_fill_weapon_dagger_0001": ("ダガー", "Dagger"), "banner_ticketgacha_fill_weapon_knuckle_0001": ("ナックル", "Knuckles"),
        "banner_ticketgacha_fill_weapon_scabbard_0001": ("剣&鞘", "B & S"), "banner_ticketgacha_fill_weapon_shoot_0001": ("銃・弓", "Gun / Bow"),
        "banner_ticketgacha_fill_weapon_0001": ("武器", "Weapon")}.items():
    write(n, "A make-up weapon ticket gacha's banner.", S, [
        L(f"補填★4～5{big_jp}ガチャチケット", f"Make-up ★4-5 {big_en} Draw Ticket", [150, 16, 236, 15], "blue_s", [148, 16, 240, 15], clear="inpaint", size=13),
        L(f"★4～5{big_jp}確定!!", f"★4-5 {big_en}\nguaranteed!!", [196, 66, 258, 44], "gold_r", [196, 64, 260, 48], size=19)])
for n, (small, big) in {"banner_ticketgacha_role_0005": ("★4限定キャラチケット", "★4 character guaranteed!!"),
        "banner_ticketgacha_role_0006": ("★4～5限定キャラチケット", "★4-5 character guaranteed!!"),
        "banner_ticketgacha_role_0007": ("★5限定キャラチケット", "★5 character guaranteed!!"),
        "banner_ticketgacha_role_0008": ("★5限定キャラチケット", "★5 character guaranteed!!")}.items():
    write(n, "A character ticket gacha's banner.", S, [
        TAG, L(small + "\n" + big.replace("character", "キャラ"), big, [58, 76, 240, 36], "gold", [56, 72, 250, 42], size=19)])
for n, star in {"banner_ticketgacha_weapon_0001": "3", "banner_ticketgacha_weapon_0002": "4", "banner_ticketgacha_weapon_0003": "5"}.items():
    write(n, "A weapon ticket gacha's banner.", S, [
        TAG,
        L(f"★{star}武器ガチャチケット", f"★{star} Weapon Draw Ticket", [176, 15, 166, 15], "blue_s", [174, 15, 170, 15], clear="inpaint", size=13),
        L(f"★{star}武器確定!!", f"★{star} weapon\nguaranteed!!", [270, 74, 186, 40], "gold_r", [268, 74, 188, 40], size=19)])
write("banner_ItemShop_003", "The premium shop's deco-set campaign banner.", dict(S, tag=S["tag"]), [
    L("キャンペーン", "Campaign", [73, 14, 80, 15], "tag", [72, 15, 66, 13]),
    L("プレミアムショップに", "New in the Premium Shop:", [58, 32, 246, 34], "blue", [56, 30, 250, 40], size=20),
    L("新しいデコセット追加!", "Deco Sets!", [80, 72, 196, 26], "blue", [80, 72, 196, 28], size=20)])
write("banner_enemy_event_000", "The event mission schedule banner.", S, [
    L("イベントミッション\nスケジュール", "Event Mission\nSchedule", [140, 42, 312, 58], "blue", [128, 40, 328, 60], size=22)])
write("banner_ingot_001", "The ingot mission banner (Ingot Mission: glossary.tsv).", S, [
    L("インゴットミッション", "Ingot Mission", [160, 60, 292, 46], "gold_r", [160, 58, 296, 52], size=30)])
write("banner_rental_point_item_gacha_001", "The support medal box gacha's banner (Box Draws: Global's ボックスガチャ).", S, [
    L("ボックスガチャ", "Box Draws", [76, 15, 80, 13], "tag", [74, 15, 76, 12]),
    L("サポートメダルボックスガチャ", "Support Medal Box Draws", [74, 76, 338, 32], "blue", [72, 74, 342, 36], size=22)])
for n, kind in {"banner_sphere_chara": ("キャラガチャ", "Character Draws"), "banner_sphere_weapon": ("武器ガチャ", "Weapon Draws")}.items():
    write(n, "Sphere 211's gacha banner.", S, [
        TAG, L("スフィア211\n" + kind[0], "Sphere 211\n" + kind[1], [58, 38, 160, 58], "blue", [56, 36, 156, 60], size=18, align="left")])
write("20200220_chara_002", "The Galaxy character gacha's banner (its GALAXY logo is the game's).", S, [
    TAG, L("ギャラクシー", "", [325, 39, 90, 12], "blue_s", [322, 38, 96, 13], clear="inpaint"),
    L("キャラガチャ", "Character Draws", [300, 80, 154, 24], "blue", [336, 80, 118, 24], size=18, align="right")])
write("20200716_chara_002", "The July 2020 apology character gacha's banner.", S, [
    TAG, L("お詫びキャラガチャ", "Apology Character Draws", [100, 50, 310, 40], "blue", [112, 48, 288, 44], size=24),
    L("2020年7月", "July 2020", [372, 94, 80, 18], "blue_s", [370, 93, 84, 20], clear="inpaint", align="right")])

write("banner_gacha_pickup_role_0118", "The 2018 lucky-bag character gacha's banner (dense text: one shaded title band).", S, [
    TAG, L("2018年福袋限定キャラガチャ\n…", "2018 Lucky Bag\nLimited Character Draws\n(tickets in the item shop)", [176, 16, 276, 98], "gold_r", [170, 14, 286, 104], size=17)])
