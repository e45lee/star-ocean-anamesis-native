"""The weapon pick-up and ticket panels (1024x512) of the live gachas: weapon names (Global's where it
had them, else ours), the weapon type, headers and the guarantee lines; factor bullet lines stay Japanese."""
import os, sys; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); from common import *  # noqa: E402,F403
S = {
 "erase": {"clear": "inpaint"},
 "band": {"clear": "shade", "clear_color": "#200400c0"},
 "band_b": {"clear": "shade", "clear_color": "#08142cc0"},
 "wname": {"size": 50, "bold": 3, "fill": "#ffffff", "outline": "#2a1000", "outline_width": 4, "glow": "#ffc040a0", "glow_radius": 3, "align": "right", "clear": "none"},
 "wname_b": {"size": 34, "bold": 2, "fill": "#ffffff", "outline": "#0a1430", "outline_width": 3, "align": "left", "clear": "none"},
 "type": {"size": 26, "bold": 2, "fill": "#ffffff", "outline": "#3a0000", "outline_width": 2, "align": "left", "clear": "inpaint"},
 "head": {"size": 36, "bold": 2, "fill": "#ffffff", "outline": "#2a1000", "outline_width": 3, "align": "left", "clear": "inpaint"},
 "title": {"size": 50, "bold": 3, "fill": "#fff0c0", "outline": "#3a0800", "outline_width": 4, "clear": "none"},
 "line": {"size": 30, "bold": 2, "fill": "#ffe9a0", "outline": "#3a0800", "outline_width": 3, "clear": "none"},
 "wlist": {"size": 30, "bold": 2, "fill": "#ffffff", "outline": "#000000", "outline_width": 2, "clear": "inpaint", "align": "left"},
 "cap": {"size": 30, "bold": 2, "fill": "#ffffff", "outline": "#0a1430", "outline_width": 3, "clear": "none"},
 "big": {"size": 52, "bold": 3, "fill": "#ffe9a0", "outline": "#3a0800", "outline_width": 4, "clear": "none"},
}
TYPES = {"片手剣": "OHS", "杖": "Staff", "銃": "Gun", "ナックル": "Knuckles", "ダガー": "Dagger", "双剣": "Dual", "書": "Tome", "ライフル": "Rifle",
         "弓": "Bow", "鎌": "Scythe", "大剣": "Great Sword", "剣＆鞘": "B & S"}
# factor panels: weapon name, type
FACTOR = {"pickup_img_weapon_002": ("ルインズフェイト", "Blade of Ruin", "片手剣"), "pickup_img_weapon_003": ("エーテルフローズン", "Aether-in-Stasis", "杖"),
          "pickup_img_weapon_004": ("シャドウビュレット", "Umbral Blast", "銃"), "pickup_img_weapon_005": ("エレメンタルエッジ", "Elemental Edge", "ダガー"),
          "pickup_img_weapon_006": ("ブラッディダスター", "Bloody Knuckles", "ナックル"),
          "pickup_img_weapon_007": ("肢閃刀・村雨", "Murasame", "剣＆鞘"), "pickup_img_weapon_008": ("アーティファクトボウ", "Artifact Bow", "弓")}
# panel: (name band, type box, type cover); the default is the layout of 002-006
GEO = {"pickup_img_weapon_007": ([460, 362, 420, 116], [700, 312, 170, 40], [696, 310, 130, 40]),
       "pickup_img_weapon_008": ([340, 352, 560, 116], [790, 300, 120, 40], [786, 300, 100, 40])}
for n, (jp, en, t) in FACTOR.items():
    band, tbox, tcov = GEO.get(n, ([430, 352, 450, 116], [716, 306, 160, 44], [714, 310, 136, 40]))
    write(n, f"A factor weapon pick-up panel ({en}).", S, [
        L("ファクター", "Factor", [176, 32, 220, 56], "head", [172, 30, 196, 60]),
        L(t, TYPES[t], tbox, "type", tcov),
        L("", "", band, "erase", band), L("", "", band, "band", band),
        L(jp, en, [band[0] + 10, band[1] + 10, band[2] - 20, band[3] - 20], "wname")])
# pick-up weapon panels: the name plate top left, the type bottom right
PU = {"20190905_weapon_PU_004": ("罪禍の宝剣", "Blade of Sin", "片手剣"), "20190919_weapon_PU_003": ("キタブアルアジフ", "Kitab al-Azif", "書"),
      "20191114_weapon_PU_004": ("クロスバイヨネット", "Cross Bayonet", "ライフル"), "20191219_weapon_PU_001": ("サイレントスノーローズ", "Silent Snow Rose", "銃"),
      "20200220_weapon_PU_003": ("ロード・カーネリアン", "Lord Carnelian", "杖"), "20200305_weapon_PU_003": ("焔双・レイエッジ", "Flame Twins: Ray Edge", "双剣")}
for n, (jp, en, t) in PU.items():
    write(n, f"A weapon pick-up panel ({en}).", S, [
        L(jp, en, [196, 44, 360, 50], "wname_b", [196, 44, 300, 50], clear="inpaint"),
        L(t, TYPES[t], [700, 380, 150, 34], "type", [698, 380, 120, 34], size=22)])
# limited weapon gacha panels: the header, the weapon names, the guarantee line
LIM = {"pickup_img_weapon_032_002": ("near", ["Great Sword", "OHS", "Arms", "Axe"]), "pickup_img_weapon_033_002": ("far", ["Dagger", "Bow", "Gun"]),
       "pickup_img_weapon_033_003": ("far", ["Rifle", "Launcher"]), "pickup_img_weapon_034_002": ("crest", ["Staff", "Orb", "Tome"]),
       "pickup_img_weapon_100_003": ("near", ["Knuckles", "Dual", "B & S", "Scythe", "Whip"])}
HEAD = {"near": "Melee Weapon Limited Draws", "far": "Ranged Weapon Limited Draws", "crest": "Crest Weapon Limited Draws"}
KIND = {"near": "melee", "far": "ranged", "crest": "crest"}
for n, (k, ws) in LIM.items():
    top = [200, 26, 624, 74]
    low = [200, 388, 624, 44]
    write(n, "A limited weapon gacha's panel: the header, the weapon names and the guarantee line (the small print stays).", S, [
        L("", "", top, "erase", top), L("", "", top, "band", top), L("近距離武器限定ガチャ", HEAD[k], [210, 30, 604, 66], "title", size=44),
        L("", "", [180, 322, 680, 52], "erase", [180, 322, 680, 52]), L("", "", [180, 322, 680, 52], "band", [180, 322, 680, 52]),
        L("", "  ".join(ws), [190, 326, 660, 44], "cap", size=28),
        L("", "", low, "erase", low), L("", "", low, "band", low),
        L("10連で★4以上の…武器が1本確定!", f"10-chain: 1 ★4+ {KIND[k]} weapon guaranteed!", [210, 390, 604, 40], "line", size=28)])
# ticket panels
for n, (cap, big) in {"pickup_img_ticket_chara_1610_005": ("★4 Limited Character Ticket", "★4 character guaranteed!!"),
        "pickup_img_ticket_chara_1610_006": ("★4-5 Limited Character Ticket", "★4-5 character guaranteed!!"),
        "pickup_img_ticket_chara_1610_007": ("★5 Limited Character Ticket", "★5 character guaranteed!!"),
        "pickup_img_ticket_chara_1610_008": ("★5 Ace Limited Character Ticket", "★5 Ace guaranteed!!")}.items():
    band = [176, 388, 680, 100]
    write(n, "A character ticket gacha's panel.", S, [
        L("", "", band, "erase", band), L("", "", band, "band_b", band),
        L("", cap, [190, 390, 650, 34], "cap", size=26), L("", big, [190, 424, 650, 60], "big", size=46)])
for n, star in {"pickup_img_ticket_weapon_1610_000": "3", "pickup_img_ticket_weapon_1610_001": "4"}.items():
    band = [430, 388, 440, 100]
    write(n, "A weapon ticket gacha's panel.", S, [
        L(f"★{star}限定武器チケット", f"★{star} Limited Weapon Ticket", [380, 38, 290, 40], "cap", [394, 40, 258, 36], size=26, clear="inpaint"),
        L("", "", band, "erase", band), L("", "", band, "band", band),
        L(f"★{star}武器確定!!", f"★{star} weapon\nguaranteed!!", [440, 392, 420, 92], "big", size=34, align="right")])
write("pickup_img_ticket_weapon_1610_006", "The ★5 weapon ticket gacha's panel.", S, [
    L("★5限定武器チケット", "★5 Limited Weapon Ticket", [310, 20, 400, 40], "cap", [316, 22, 394, 36], size=28, clear="inpaint"),
    L("★5武器確定!チケットはアイテム交換所などで入手可能!", "★5 weapon guaranteed! Tickets from the Item Exchange and more!",
      [176, 406, 700, 40], "line", [176, 406, 700, 40], size=26, clear="inpaint")])
