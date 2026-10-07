"""The 2020 dated pick-up panels (1024x512) before 2020-12-24, newest first: a title band over each
panel's Japanese headline (the character's role and name, the weapon's name and type, the gacha's
catch line); the CV / illustrator credits, the character's quote and the small print stay Japanese.
Names: glossary / Global's, else the MT run's names, as in dated_2020.py."""
import os, sys; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); from common import *  # noqa: E402,F403
S = {
 "erase": {"clear": "inpaint"},
 "band": {"clear": "shade", "clear_color": "#1a0a28c0"},
 "band_g": {"clear": "shade", "clear_color": "#200400c8"},
 "name": {"size": 50, "bold": 3, "fill": "#ffffff", "outline": "#3a0a50", "outline_width": 4, "glow": "#ff80ffa0", "glow_radius": 3, "clear": "none"},
 "role": {"size": 26, "bold": 2, "fill": "#ffffff", "outline": "#5a0010", "outline_width": 2, "clear": "none"},
 "tag": {"size": 36, "bold": 3, "fill": "#ffffff", "outline": "#2a0a40", "outline_width": 3, "glow": "#c080ffa0", "glow_radius": 2, "align": "left", "clear": "none"},
 "wname": {"size": 34, "bold": 2, "fill": "#ffffff", "outline": "#0a1430", "outline_width": 3, "align": "left", "clear": "none"},
 "wtype": {"size": 22, "bold": 2, "fill": "#ffffff", "outline": "#3a0000", "outline_width": 2, "align": "left", "clear": "none"},
 "gold": {"size": 30, "bold": 2, "fill": "#ffeab0", "outline": "#3a0800", "outline_width": 3, "clear": "none"},
}
ROLE = {"A": "Attacker", "C": "Invoker", "D": "Defender", "H": "Healer", "S": "Sharpshooter"}
def banded(rect, style="band"):
    return [L("", "", rect, "erase", rect), L("", "", rect, style, rect)]
def chara(name, en, role, rect, tag=None, tag_rect=(140, 12, 330, 56)):
    """rect: the band over the role + name headline; the role on top, the name below."""
    x, y, w, h = rect
    labels = []
    if tag:
        labels += banded(list(tag_rect)) + [L("", f"From {tag}!!", list(tag_rect), "tag")]
    labels += banded(list(rect)) + [L("", ROLE[role], [x + 8, y + 4, w - 16, 30], "role"), L("", en, [x + 8, y + 34, w - 16, h - 38], "name")]
    write(name, f"A character pick-up panel ({en}).", S, labels)
def weapon(name, en, wtype, name_rect, type_rect):
    write(name, f"A weapon pick-up panel ({en}).", S, banded(list(name_rect)) + [L("", en, list(name_rect), "wname")]
          + banded(list(type_rect)) + [L("", wtype, list(type_rect), "wtype")])
def catch(name, note, en, rect, size=30):
    write(name, note, S, banded(list(rect), "band_g") + [L("", en, [rect[0] + 8, rect[1] + 4, rect[2] - 16, rect[3] - 8], "gold", size=size)])

# ---- 2020-12-24 .. 2020-12-03
weapon("20201224_weapon_PU_002", "Eternal Pleasure", "Whip", (190, 44, 560, 52), (700, 382, 120, 40))
weapon("20201224_weapon_PU_001", "Rampage Ruby", "Knuckles", (190, 44, 560, 52), (700, 382, 150, 40))
catch("20201224_chara_PU_003", "The weekend pick-up panel.", "Weekend Limited\nCharacter Pick-up\nLimited characters only!", (200, 262, 670, 196))
catch("20201224_chara_PU_002", "Evelysse's birthday pick-up panel.", "Evelysse's Birthday Pick-up Character Draws\n10-chain: 1 bonus item!  Pick-ups: the 5 Evelysses only!\n10-chain: 1 pick-up guaranteed!", (170, 286, 720, 214), size=24)
catch("20201224_chara_PU_001", "The rerun 2017 Christmas step-up panel.", "Step 1:\nhalf price!\nStep 10:\n1 pick-up\nguaranteed!\n★5: Aces only!\n\nRerun 2017\nChristmas", (170, 16, 250, 390), size=24)
catch("20201217_chara_PU_003", "The rerun 2018 Christmas step-up panel.", "Step 1:\nhalf price!\nStep 10:\n1 pick-up\nguaranteed!\n★5: Aces only!\n\nRerun 2018\nChristmas", (160, 16, 250, 390), size=24)
chara("20201217_chara_PU_002", "Christmas Nel", "H", (600, 262, 280, 130), tag="SO3")
chara("20201217_chara_PU_001", "Snow Fox Karlyn", "A", (500, 270, 380, 120))
weapon("20201210_weapon_PU_002", "Ice Spirit Staff: Azure Wing", "Staff", (150, 44, 520, 52), (716, 372, 90, 44))
weapon("20201210_weapon_PU_001", "Liberty Providence", "Orb", (190, 44, 560, 52), (700, 372, 90, 44))
chara("20201210_chara_PU_001", "Black Evelysse", "C", (480, 262, 400, 140))
S["head"] = {"size": 34, "bold": 3, "fill": "#ffffff", "outline": "#0a1a5a", "outline_width": 3, "clear": "none"}
S["small"] = {"size": 18, "bold": 2, "fill": "#ffffff", "outline": "#0a1a5a", "outline_width": 2, "clear": "none"}
def box(name, title):
    """A box gacha's featured-items panel: its header and title; the item captions stay."""
    write(name, f"A box gacha's featured-items panel ({title.replace(chr(10), ' ')}).", S,
          banded([450, 10, 420, 90]) + [L("", "Box Draws: Featured Items", [454, 14, 412, 64], "head", size=30)]
          + banded([214, 22, 226, 56]) + [L("", title + "\n3 types", [218, 24, 218, 52], "small", size=16)])
def stepup(name, en, rect=(150, 16, 260, 390)):
    catch(name, "A step-up gacha's panel.", en, rect, size=24)

# ---- 2020-12-03 .. 2020-10-22
box("20201203_event_PU_001", "Where Fading Memories Dwell")
chara("20201126_chara_PU_002", "Songstar Fayt", "S", (530, 286, 360, 110), tag="SO3")
chara("20201126_chara_PU_001", "Songstar Rena", "D", (560, 290, 330, 110), tag="SO2")
weapon("20201112_weapon_PU_002", "Blaze Valvarizer", "Scythe", (190, 44, 560, 52), (700, 378, 150, 44))
weapon("20201112_weapon_PU_001", "Twin Dragon Swords: Crimson Blaze", "Dual", (190, 44, 560, 52), (700, 378, 150, 44))
write("20201112_chara_PU_002", "Divine Dragon Ashton's step-up panel.", S,
      banded([150, 16, 440, 140], "band_g") + [L("", "Step 10: Divine Dragon Ashton guaranteed!\n★5: Aces only!", [158, 20, 424, 132], "gold", size=26)]
      + banded([160, 236, 730, 210], "band_g") + [L("", "Divine Dragon Ashton\n10-chain Step 10: 1 pick-up guaranteed", [168, 240, 714, 202], "gold", size=34)])
chara("20201112_chara_PU_001", "Divine Dragon Ashton", "A", (460, 300, 420, 124), tag="SO2")
catch("20201105_chara_PU_002", "The weekend pick-up panel.", "Weekend Limited\nCharacter Pick-up\nLimited characters only!", (216, 262, 580, 190))
stepup("20201029_chara_PU_003", "Step 1:\nhalf price!\nStep 10:\n1 pick-up\nguaranteed!\n★5: Aces only!\n\nRerun Halloween\n2018")
weapon("20201022_weapon_PU_003", "Oni Spider Reaver", "Orb", (190, 44, 560, 52), (700, 378, 150, 44))
weapon("20201022_weapon_PU_002", "Dark Bunny Cannon", "Launcher", (190, 44, 560, 52), (700, 378, 170, 44))
weapon("20201022_weapon_PU_001", "Blood Bullet Gun: Bloodlust", "Gun", (190, 44, 560, 52), (700, 378, 150, 44))
box("20201022_event_PU_001", "Phantom Counterattack")

# ---- 2020-10-22 .. 2020-09-17
STEP = "Step 1:\nhalf price!\nStep 10:\n1 pick-up\nguaranteed!\n★5: Aces only!\n\n"
chara("20201022_chara_PU_002", "Magician Peppita", "S", (530, 276, 360, 110), tag="SO3")
chara("20201022_chara_PU_001", "Vampire Maria", "H", (536, 270, 350, 124), tag="SO3")
weapon("20201015_weapon_PU_003", "Perfalate Gale", "Bow", (190, 44, 560, 52), (700, 378, 150, 44))
weapon("20201015_weapon_PU_002", "Absolute Royal Guard", "Great Sword", (190, 44, 560, 52), (700, 378, 190, 44))
weapon("20201015_weapon_PU_001", "Majestic Labrys", "Axe", (190, 44, 560, 52), (700, 378, 150, 44))
stepup("20201015_chara_PU_002", STEP + "Rerun Halloween\n2017", (160, 16, 280, 440))
stepup("20201015_chara_PU_001", STEP + "Rerun Maid", (330, 16, 300, 440))
stepup("20201008_chara_PU_004", STEP + "Rerun Maid", (156, 20, 300, 440))
stepup("20201008_chara_PU_003", STEP + "Rerun Maid", (152, 20, 300, 440))
chara("20201008_chara_PU_002", "Butler Arumat", "D", (420, 262, 460, 124), tag="SO4")
chara("20201008_chara_PU_001", "Maid Reimi", "A", (546, 272, 340, 116), tag="SO4")
stepup("20200917_chara_PU_001", STEP + "Rerun Costume\nContest 2018", (350, 12, 300, 420))

# ---- 2020-09-10 .. 2020-08-27
W1, T1 = (190, 44, 560, 52), (700, 378, 190, 44)
weapon("20200910_weapon_PU_003", "Extinctive Trigger", "Rifle", W1, T1)
weapon("20200910_weapon_PU_002", "Crest Sword: Life Crystal", "Great Sword", W1, T1)
weapon("20200910_weapon_PU_001", "Silvery Crescent", "Knuckles", W1, T1)
write("20200910_chara_PU_002", "Rena of Divine Stars' step-up panel.", S,
      banded([170, 16, 320, 140], "band_g") + [L("", "Step 10: Rena of Divine\nStars guaranteed!\n★5: Aces only!", [178, 20, 304, 132], "gold", size=26)]
      + banded([170, 236, 330, 200], "band_g") + [L("", "Rena of Divine Stars\n10-chain Step 10:\n1 pick-up guaranteed", [178, 240, 314, 192], "gold", size=30)])
chara("20200910_chara_PU_001", "Rena of Divine Stars", "C", (560, 316, 340, 130), tag="SO2")
catch("20200903_chara_PU_001", "The SO3 Memorial pick-up panel.", "SO3 Memorial Pick-up Character Draws\n10-chain: 1 bonus item!\nPick-ups: limited characters only!", (290, 284, 580, 180), size=28)
weapon("20200827_weapon_PU_003", "Recoro Ball Saber", "Orb", W1, T1)
weapon("20200827_weapon_PU_002", "Eternal Devotion", "Whip", W1, T1)
weapon("20200827_weapon_PU_001", "Sakura Ice Blade: Glitter Trail", "Scythe", W1, T1)
box("20200827_event_PU_001", "Defeat the Phantom Commander")
stepup("20200827_chara_PU_003", STEP + "Rerun Swimsuit\n2020 (3)", (540, 16, 350, 430))
chara("20200827_chara_PU_002", "Erys of the Shore", "H", (600, 236, 300, 130), tag="SO1")

# ---- 2020-08-27 .. 2020-08-06
chara("20200827_chara_PU_001", "Lavarnia of the Shore", "A", (470, 276, 420, 124))
weapon("20200820_weapon_PU_003", "Blasting Drill", "Launcher", W1, T1)
weapon("20200820_weapon_PU_002", "Sprinkle Burst DX", "Arms", W1, T1)
weapon("20200820_weapon_PU_001", "Water Gun: Jet Scatter", "Gun", W1, T1)
catch("20200813_chara_PU_004", "The weekend pick-up panel.", "Weekend Limited\nCharacter Pick-up\nLimited characters only!", (170, 262, 660, 240))
stepup("20200813_chara_PU_003", STEP + "Rerun Swimsuit\n2020 (2)", (150, 16, 300, 440))
chara("20200813_chara_PU_002", "Midsummer Welch", "C", (500, 270, 390, 124))
chara("20200813_chara_PU_001", "Midsummer Euwin", "S", (506, 270, 390, 124))
weapon("20200806_weapon_PU_003", "TFW Rampage Vireau", "Axe", W1, T1)
weapon("20200806_weapon_PU_002", "Sea Breeze Blades: Dual Fans", "Dagger", W1, T1)
weapon("20200806_weapon_PU_001", "Protean Anima", "Whip", W1, T1)
box("20200806_event_PU_001", "Star Ocean and the Dreamy Shore")

# ---- 2020-08-06 .. 2020-06-11
stepup("20200806_chara_PU_001", STEP + "Rerun Bunny Ears\nCharacters", (150, 16, 360, 440))
write("20200730_chara_PU_004", "The SO2 release-day pick-up panel.", S,
      banded([210, 14, 600, 44], "band_g") + [L("", "Star Ocean 2 Release Day Pick-up", [214, 16, 592, 40], "gold", size=30)]
      + banded([176, 380, 690, 90], "band_g") + [L("", "A chance to collect the series' characters!!\nStar Ocean 2: 10-chain: 1 ★5 character guaranteed!", [180, 384, 682, 82], "gold", size=26)]
      + banded([650, 340, 190, 40], "band_g") + [L("", "3 per player", [654, 342, 182, 36], "gold", size=24)])
stepup("20200730_chara_PU_003", STEP + "Rerun Swimsuit\n2020 (1)", (150, 16, 320, 440))
chara("20200730_chara_PU_002", "Eternal Summer Verda", "S", (540, 268, 350, 124))
chara("20200730_chara_PU_001", "Summer Clair", "A", (570, 268, 330, 124), tag="SO3")
catch("20200722_chara_PU_004", "The weekend pick-up panel.", "Weekend Limited\nCharacter Pick-up\nLimited characters only!", (180, 262, 700, 220))
weapon("20200625_weapon_PU_003", "Cosmic Principle", "Orb", W1, T1)
weapon("20200625_weapon_PU_002", "Privilege Vitality", "Whip", W1, T1)
weapon("20200625_weapon_PU_001", "Innocent Light", "Dual", W1, T1)
write("20200625_chara_PU_004", "The SOA Memorial pick-up panel.", S,
      banded([280, 4, 460, 90], "band_g") + [L("", "SOA Memorial\nPick-up Character Draws", [284, 6, 452, 86], "gold", size=34)]
      + banded([220, 356, 600, 112], "band_g") + [L("", "10-chain: 1 bonus item!\nPick-ups: limited characters only!", [224, 360, 592, 82], "gold", size=30)])
catch("20200625_chara_PU_003", "The Heath / Lavarnia pick-up panel.", "10-chain: 1 bonus item!\nExchange 10 for Heath or Lavarnia!", (240, 356, 620, 116))
stepup("20200611_chara_PU_003", STEP + "Rerun Bride\n2018", (150, 16, 320, 440))

# ---- 2020-06-11 .. 2020-05-14
chara("20200611_chara_PU_002", "Bride Tika", "C", (560, 264, 330, 124))
chara("20200611_chara_PU_001", "Bride Karlyn", "S", (536, 268, 360, 124))
weapon("20200604_weapon_PU_003", "Vital Edge", "Dagger", W1, T1)
weapon("20200604_weapon_PU_002", "Bone Crusher: Rakshasa", "Great Sword", W1, T1)
weapon("20200604_weapon_PU_001", "Crescent Moon: Mist Phantom Blade", "B & S", W1, T1)
box("20200604_event_PU_001", "Demons Dance Upon the Dying Star")
write("20200528_chara_PU_003", "The SO1 Memorial pick-up panel.", S,
      banded([280, 0, 460, 92], "band_g") + [L("", "SO1 Memorial\nPick-up Character Draws", [284, 4, 452, 84], "gold", size=34)]
      + banded([220, 356, 600, 112], "band_g") + [L("", "10-chain: 1 bonus item!\nPick-ups: limited characters only!", [224, 360, 592, 104], "gold", size=30)])
chara("20200528_chara_PU_002", "Albel of Demon Flame", "A", (496, 250, 390, 124), tag="SO3")
chara("20200528_chara_PU_001", "Nel the Demon Slayer", "D", (580, 250, 320, 124), tag="SO3")
weapon("20200514_weapon_PU_003", "Struggle Knuckle", "Arms", W1, T1)
weapon("20200514_weapon_PU_002", "Oxis Cocoon", "Orb", W1, T1)
weapon("20200514_weapon_PU_001", "Deity Alternation", "Rifle", W1, T1)

# ---- 2020-05-14 .. 2020-03-26
def memorial(name, so):
    write(name, f"The {so} Memorial pick-up panel.", S,
          banded([280, 0, 460, 92], "band_g") + [L("", f"{so} Memorial\nPick-up Character Draws", [284, 4, 452, 84], "gold", size=34)]
          + banded([220, 356, 600, 112], "band_g") + [L("", "10-chain: 1 bonus item!\nPick-ups: limited characters only!", [224, 360, 592, 104], "gold", size=30)])
def release(name, so, logo_band=True):
    write(name, f"The SO{so} release-day pick-up panel.", S,
          banded([210, 14, 600, 44], "band_g") + [L("", f"Star Ocean {so} Release Day Draws", [214, 16, 592, 40], "gold", size=30)]
          + banded([176, 380, 690, 90], "band_g") + [L("", f"A chance to collect the series' characters!!\nStar Ocean {so}: 10-chain: 1 ★5 character guaranteed!", [180, 384, 682, 82], "gold", size=26)]
          + banded([650, 340, 190, 40], "band_g") + [L("", "3 per player", [654, 342, 182, 36], "gold", size=24)])
write("20200514_chara_PU_003", "The Divine Wing Maria / Wise God Mastima step-up panel.", S,
      banded([150, 16, 330, 190], "band_g") + [L("", "Step 10: Divine Wing Maria\nor Wise God Mastima\nguaranteed!\n★5: Aces only!", [158, 20, 314, 182], "gold", size=26)]
      + banded([150, 290, 430, 140], "band_g") + [L("", "10-chain Step 10:\n1 pick-up guaranteed", [158, 294, 414, 132], "gold", size=34)])
chara("20200514_chara_PU_002", "Wise God Mastima", "H", (420, 272, 470, 116))
chara("20200514_chara_PU_001", "Divine Wing Maria", "C", (520, 260, 380, 124), tag="SO3")
weapon("20200507_weapon_PU_003", "Lightning Blossom", "Staff", W1, T1)
weapon("20200507_weapon_PU_002", "Tremendous Generator", "Launcher", W1, T1)
weapon("20200507_weapon_PU_001", "Ferocious Fang", "Dual", W1, T1)
memorial("20200507_chara_PU_001", "SO5")
chara("20200430_chara_PU_002", "Ricardo of the Cannon Armor", "S", (440, 270, 450, 124))
chara("20200430_chara_PU_001", "Karlyn the Fox General", "A", (520, 268, 380, 124))
stepup("20200416_chara_PU_003", STEP + "Rerun Idol\n2019", (150, 16, 340, 440))
stepup("20200416_chara_PU_002", STEP + "Rerun Idol\n2018", (150, 16, 340, 440))
release("20200326_chara_PU_005", 5)

# ---- 2020-03-12 .. 2020-02-27
weapon("20200312_weapon_PU_003", "Eternal Straight", "Launcher", W1, T1)
weapon("20200312_weapon_PU_002", "Flare Plasma Gun", "Gun", W1, T1)
weapon("20200312_weapon_PU_001", "Heraldry Altar", "Great Sword", W1, T1)
write("20200312_chara_PU_005", "The new-life support free gacha's panel.", S,
      banded([300, 10, 420, 110], "band_g") + [L("", "New Life Support\nFree 10-chain Character Draws", [304, 14, 412, 102], "gold", size=30)]
      + banded([200, 390, 640, 60], "band_g") + [L("", "Up to 5 free 10-chains in the period!", [204, 394, 632, 52], "gold", size=30)])
for n, vol in (("20200312_chara_PU_004", 2), ("20200312_chara_PU_003", 1)):
    write(n, f"The White Day pick-up panel ({vol}).", S,
          banded([280, 4, 480, 56], "band_g") + [L("", "These 5 characters are picked up!", [284, 8, 472, 48], "gold", size=30)]
          + banded([150, 316, 730, 120], "band_g") + [L("", f"10-chain: 1 bonus item!\nWhite Day {vol} Pick-up Character Draws", [154, 320, 722, 112], "gold", size=34)])
write("20200312_chara_PU_002", "Divine Wing Fayt's step-up panel.", S,
      banded([150, 16, 360, 140], "band_g") + [L("", "Step 10: Divine Wing\nFayt guaranteed!\n★5: Aces only!", [158, 20, 344, 132], "gold", size=26)]
      + banded([150, 290, 720, 140], "band_g") + [L("", "Divine Wing Fayt\n10-chain Step 10: 1 pick-up guaranteed", [158, 294, 704, 132], "gold", size=34)])
chara("20200312_chara_PU_001", "Divine Wing Fayt", "A", (500, 260, 390, 124), tag="SO3")
weapon("20200305_weapon_PU_002", "Coloraba Blade", "Dagger", W1, T1)
weapon("20200305_weapon_PU_001", "Elite Bunny Snipe", "Rifle", W1, T1)
box("20200227_event_PU_001", "Hot Springs and the Mischievous Snow Monsters")
release("20200227_chara_PU_003", 3)

# ---- 2020-02-27 .. 2020-01-01
chara("20200227_chara_PU_002", "Hot Spring Evelysse", "A", (400, 262, 500, 124))
chara("20200227_chara_PU_001", "Hot Spring Rena", "S", (530, 262, 370, 124), tag="SO2")
release("20200213_chara_PU_003", 4)
chara("20200213_chara_PU_002", "Miki of Sweet Love", "S", (380, 316, 500, 124), tag="SO5")
chara("20200213_chara_PU_001", "Erys of the Heavenly Wings", "A", (330, 316, 560, 124), tag="SO1")
weapon("20200123_weapon_PU_003", "Heavy Iron Arms: Iron Wrist", "Arms", W1, T1)
weapon("20200123_weapon_PU_002", "Ice Scale Blade: Azure Dragon", "Great Sword", W1, T1)
weapon("20200123_weapon_PU_001", "Salute Cannon: Celebration", "Rifle", W1, T1)
write("20200123_chara_PU_003", "The Lunar New Year step-up panel.", S,
      banded([150, 16, 430, 170], "band_g") + [L("", "Step 10: Queen Clair or\nQueen Nel guaranteed!\n★5: Aces only!", [158, 20, 414, 162], "gold", size=26)]
      + banded([150, 316, 470, 150], "band_g") + [L("", "Lunar New Year Draws\n10-chain Step 10:\n1 pick-up guaranteed", [158, 320, 454, 142], "gold", size=30)])
chara("20200123_chara_PU_002", "Queen Clair", "A", (460, 262, 430, 124), tag="SO3")
chara("20200123_chara_PU_001", "Queen Nel", "S", (460, 262, 430, 124), tag="SO3")
box("20200106_event_PU_001", "Spirit of Renewal")
weapon("20200101_weapon_PU_003", "Monthly Anamne Girls", "Orb", W1, T1)
weapon("20200101_weapon_PU_002", "Divine Tail Axe: White Fox", "Axe", W1, T1)
weapon("20200101_weapon_PU_001", "Auspicious Bow: Phoenix Tail", "Bow", W1, T1)
chara("20200101_chara_PU_002", "Karlyn of the Dawn Fox", "A", (420, 262, 480, 124))
chara("20200101_chara_PU_001", "Reimi of the Phoenix Bow", "H", (420, 262, 480, 124), tag="SO4")
