"""The other pick-up panels (1024x512) of the live gachas: the standard character gacha, the apology
gacha's notice, the 2018 lucky bag, the Galaxy gacha."""
import os, sys; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); from common import *  # noqa: E402,F403
S = {
 "erase": {"clear": "inpaint"},
 "band": {"clear": "shade", "clear_color": "#200400c0"},
 "gold": {"size": 44, "bold": 3, "fill": "#ffeab0", "outline": "#3a0800", "outline_width": 4, "clear": "none"},
 "white": {"size": 26, "bold": 2, "fill": "#ffffff", "outline": "#0a1430", "outline_width": 3, "clear": "none"},
 "teal_t": {"size": 56, "bold": 3, "fill": "#ffffff", "outline": "#0a4a5a", "outline_width": 4, "glow": "#40ffffa0", "glow_radius": 3, "clear": "none"},
 "teal": {"size": 30, "bold": 2, "fill": "#ffffff", "outline": "#0a3a4a", "outline_width": 3, "align": "left", "leading": 10, "clear": "none"},
}
band = [150, 322, 720, 170]
write("pickup_img_chara_1610_002", "The standard character gacha's panel (Global's 10-chain).", S, [
    L("", "", band, "erase", band), L("", "", band, "band", band),
    L("10連で★4以上のキャラが1体確定!", "10-chain: 1 ★4+ character\nguaranteed!", [170, 326, 680, 120], "gold", size=40),
    L("一部のキャラをご紹介>>", "Some of the characters >>", [470, 446, 380, 34], "white", size=24, align="right")])
whole = [196, 40, 704, 420]
write("20200716_chara_PU_002", "The July 2020 apology gacha's notice panel.", S, [
    L("", "", whole, "erase", whole),
    L("お詫びキャラガチャ", "Apology Character Draws", [220, 50, 600, 80], "teal_t", size=50),
    L("※10連特典枠はございません。…", "* No 10-chain bonus slot.\n* No character chips.\n* Characters appear before enhancement\n   (evolution, awakening, etc.).",
      [290, 150, 560, 230], "teal", size=28),
    L("2020年7月", "July 2020", [690, 410, 190, 40], "teal", size=30, align="right")])
top = [220, 16, 590, 96]
low = [170, 404, 720, 52]
write("pickup_img_chara_1712_017", "The 2018 lucky-bag character gacha's panel.", S, [
    L("", "", top, "erase", top), L("", "", top, "band", top),
    L("2018年福袋限定キャラガチャ", "2018 Lucky Bag Limited Character Draws", [230, 20, 570, 48], "gold", size=34),
    L("★5エースをゲットするビッグチャンス!!", "A big chance to get a ★5 Ace!!", [260, 68, 510, 40], "white", size=24),
    L("", "", low, "erase", low), L("", "", low, "band", low),
    L("花嫁、常夏、ハロウィン、いずれかのキャラが必ず出現!", "A Bride, Summer or Halloween character, guaranteed!", [180, 408, 700, 44], "gold", size=30)])
write("20200220_chara_PU_001", "The Galaxy character gacha's panel (its GALAXY logo is the game's).", S, [
    L("キャラガチャ", "Character Draws", [556, 426, 280, 38], "white", [556, 426, 196, 36], clear="inpaint", align="left", size=28),
    L("ギャラクシー", "", [386, 381, 134, 23], "erase", [386, 381, 134, 23])])
