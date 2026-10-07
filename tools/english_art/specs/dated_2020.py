"""The 2020 dated banners (512x128) before 2020-12-24, newest first (the user, 2026-10-07): title bands
(inpaint + shade + English) over the dense lettering, in a few layout families; small art captions
(character names under portraits) stay. Terms: glossary.tsv, Global's master (e.g. 滅級 / 絶級 =
Misery 2 / 3), the MT names table for new names; epithets composed (聖夜 Christmas, 雪狐 Snow Fox...)."""
import os, sys; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); from common import *  # noqa: E402,F403
from gacha_banners import S as GS, erase_first  # noqa: E402
S = dict(GS)
S["omake"] = {"size": 11, "bold": 1, "fill": "#ffffff", "clear": "inpaint", "align": "left"}
S["cap"] = {"size": 11, "bold": 1, "fill": "#ffffff", "outline": "#000000", "outline_width": 1, "clear": "inpaint", "align": "left"}
TAGS = {"ガチャ": "Draws", "イベント": "Event", "キャンペーン": "Campaign", "ボックスガチャ": "Box Draws"}
def tag(jp):
    return L(jp, TAGS[jp], [73, 14, 80, 15], "tag", [72, 15, {"キャンペーン": 66, "ボックスガチャ": 76}.get(jp, 52), 13])
def w(name, note, labels):
    write(name, note, S, erase_first(labels))
def band(jp, en, rect, style="gold_r", size=18, **kw):
    return L(jp, en, [rect[0] + 4, rect[1] + 2, rect[2] - 8, rect[3] - 4], style, list(rect), size=size, **kw)
def xmas_rerun(name, year, title=None, x1=220, bonus=True):
    title = title or f"Rerun {year} Christmas"
    w(name, f"A step-up gacha's banner ({title}).", [
        tag("ガチャ")] + ([L("お負け付き", "Bonus", [58, 31, 50, 11], "omake", [57, 31, 48, 11])] if bonus else []) + [
        L("…10連10ステップ目 PUいずれか1体確定ガチャ", f"{title}\nStep 10: 1 Pick-up\nguaranteed (10-chain)",
          [66, 40, x1 - 70, 72], "gold", [60, 34, x1 - 60, 80], size=18),
        L("ステップ10はPUいずれか1体確定!", "Step 10: 1 pick-up guaranteed!", [270, 98, 186, 18], "bar_r", [min(270, x1), 96, 456 - min(270, x1), 20], clear="shade", clear_color="#200400c0")])
def weapon_pu(name):
    w(name, "A pick-up weapon gacha's banner (3 slots, with a bonus).", [
        tag("ガチャ"),
        L("ピックアップ武器ガチャ", "Pick-up Weapon Draws", [170, 15, 170, 14], "blue_s", [176, 15, 156, 14], clear="inpaint", size=13),
        L("3スロット", "3 Slots", [368, 15, 40, 13], "tag", [368, 15, 40, 13], clear="inpaint", size=10),
        L("10連で★5新武器1本確定!!", "10-chain: 1 new\n★5 weapon guaranteed!!", [250, 52, 206, 64], "gold_r", [248, 44, 208, 72], size=20),
        L("おまけ付き", "Bonus", [410, 27, 46, 11], "omake", [410, 27, 46, 11])])
def rateup(name, x0, who, kind="Character", exceed=False, extra=None, y0=30):
    """A pick-up gacha's banner with its right block: ★5 X arrives!! / Rate UP!! / 10th draw: x3."""
    labels = [tag("ガチャ"), band("★5 … 登場!! 出現確率UP!! 10連目はピックアップ確率3倍!", f"★5 {who}!!\nRate UP!!\n10th 10-chain: pick-up rate x3!", [x0, y0, 456 - x0, 118 - y0], size=18)]
    labels.append(L("ピックアップ…キャラガチャ", f"Pick-up {'Exceed ' if exceed else ''}{kind} Draws", [58, 101, 140, 13], "cap", [57, 86, 110, 30]))
    if extra: labels += extra
    w(name, f"A pick-up gacha's banner ({who}).", labels)
def awaken(name, who, x1=290):
    w(name, f"{who}'s awakening banner.", [band(f"{who}覚醒", f"{who}\nAwakened", [60, 32, x1 - 60, 80], "blue", size=26, align="left")])

# ---- 2020-12-17 / 12-10
w("20201217_event_001", "The Wadrum, Holy Land of Oblivion event's banner (hour 6).", [
    tag("イベント"),
    L("忘却の聖地 ウドラム", "Wadrum, Holy Land\nof Oblivion", [60, 32, 220, 58], "blue", [58, 32, 190, 64], size=22, align="left"),
    L("第6刻", "Hour 6", [350, 60, 100, 30], "blue", [356, 60, 90, 30], size=22, align="right")])
awaken("20201217_chara_003", "Official Reimi")
xmas_rerun("20201217_chara_002", 2018)
rateup("20201217_chara_001", 300, "Snow Fox Karlyn &\nChristmas Nell")
weapon_pu("20201210_weapon_001")
w("20201210_event_001", "The Cave of the Seven Stars divine event's banner (神級: Divine, a 3.x difficulty Global never had).", [
    tag("イベント"),
    L("神級", "Divine", [60, 36, 50, 36], "blue_s", [60, 38, 48, 36], clear="inpaint", size=14),
    band("七星の洞窟", "Cave of the Seven Stars", [236, 34, 220, 50], size=24),
    band("神級イベント", "Divine Event", [296, 88, 150, 26], size=16)])
xmas_rerun("20201210_chara_002", 2019)
rateup("20201210_chara_001", 244, "Black Evelysse", exceed=True)

def event_title(name, jp, en, rect, sub=None, top=None, rerun=None, tagjp="イベント", style="blue"):
    """An event / box gacha banner: the title band, an optional subtitle band (difficulties added),
    an optional small top caption, an optional 'rerun' badge."""
    labels = [tag(tagjp), band(jp, en, rect, style, size=24)]
    if sub: labels.append(band(sub[0], sub[1], sub[2], style, size=14))
    if top: labels.append(L(top[0], top[1], top[2], "blue_s", top[2], clear="inpaint", size=12))
    if rerun: labels.append(band("復刻", "Rerun", rerun, style, size=14))
    w(name, f"An event banner ({en.replace(chr(10), ' ')}).", labels)
MIS = ("滅級・絶級追加", "Misery 2 & 3 added")
FADE = "Where Fading\nMemories Dwell"
WAD = "Wadrum, Holy Land\nof Oblivion"
def wadrum(name, hour, rerun=False, sub=True):
    labels = [tag("イベント"), L("忘却の聖地 ワドラム", WAD, [60, 32, 220, 58], "blue", [58, 32, 190, 64], size=22, align="left"),
              L(f"第{hour}刻", f"Hour {hour}", [350, 60, 100, 30], "blue", [356, 60, 90, 30], size=22, align="right")]
    if sub: labels.append(L(MIS[0], MIS[1], [86, 96, 170, 18], "blue_s", [96, 96, 116, 18], clear="inpaint", size=13))
    if rerun: labels.append(band("復刻", "Rerun", [372, 30, 76, 26], "blue", size=14))
    w(name, f"The Wadrum, Holy Land of Oblivion event's banner (hour {hour}{', rerun' if rerun else ''}; Misery 2 / 3: Global's 滅級 / 絶級).", labels)

# ---- 2020-12-03 .. 2020-10-29
event_title("20201203_event_002", "色褪せぬ記憶の在処", FADE, [60, 30, 280, 60], tagjp="ボックスガチャ",
            sub=("ボックスガチャ", "Box Draws", [300, 88, 156, 30]))
event_title("20201203_event_001", "色褪せぬ記憶の在処", FADE, [70, 28, 380, 64], sub=(MIS[0], MIS[1], [120, 94, 216, 24]))
event_title("20201126_event_001", "色褪せぬ記憶の在処", FADE, [70, 28, 320, 64], rerun=[396, 46, 50, 36])
rateup("20201126_chara_001", 300, "Songstar Rena &\nSongstar Fayt")
wadrum("20201119_event_001", 5)
xmas_rerun("20201119_chara_001", 2019, "Rerun 2019 Anniversary\n(3rd)", x1=236)
w("20201112_weapon_002", "The rerun pick-up divine weapon gacha's banner.", [
    tag("ガチャ"), L("3スロット", "3 Slots", [374, 26, 76, 14], "tag", [372, 25, 80, 15], clear="inpaint", size=11),
    band("復刻 ピックアップ武器ガチャ 10連で★5PU武器1本確定!", "Rerun Pick-up Weapon Draws\n10-chain: 1 ★5 pick-up\nweapon guaranteed!", [248, 52, 208, 66], size=17)])
weapon_pu("20201112_weapon_001")
wadrum("20201112_event_001", 5, rerun=True, sub=False)
rateup("20201112_chara_003", 300, "Maria of the Divine Wings &\nWise God Mastima", y0=14)
w("20201112_chara_002", "Divine Dragon Ashton's step-up gacha banner.", [
    tag("ガチャ"),
    band("★5神龍のアシュトン ステップ10は神龍のアシュトン1体確定!", "★5 Divine Dragon Ashton\nStep 10: Divine Dragon\nAshton guaranteed!", [56, 26, 232, 92], "gold", size=18, align="left"),
    band("10連10ステップ目 PU1体確定ガチャ", "10-chain Step 10:\n1 pick-up guaranteed", [324, 56, 132, 62], size=13)])
rateup("20201112_chara_001", 240, "Divine Dragon Ashton")
awaken("20201105_chara_003", "Peppita")
w("20201105_chara_002", "The weekend-limited character pick-up gacha's banner.", [
    tag("ガチャ"), band("週末限定 キャラクターピックアップ ピックアップは期間限定キャラのみ!", "Weekend Limited\nCharacter Pick-up\nLimited characters only!", [266, 6, 192, 112], size=18)])
xmas_rerun("20201105_chara_001", 0, "Rerun Fairy Tale World", x1=210)
event_title("20201029_event_001", "逆襲のファントム", "Phantom Counterattack", [76, 34, 370, 60], sub=(MIS[0], MIS[1], [150, 94, 210, 24]),
            top=("EP3イベント", "EP3 Event", [200, 14, 150, 22]), style="gold")

# ---- 2020-10-29 .. 2020-10-08
xmas_rerun("20201029_chara_003", 0, "Rerun Halloween 2018", x1=226)
w("20201029_chara_002", "The Invoker role pick-up gacha's banner (Invoker: Global's キャスター).", [
    tag("ガチャ"), band("キャスターロール pick up ピックアップキャラガチャ", "Invoker Role\nPick-up Character Draws", [56, 26, 214, 88], "gold", size=20, align="left"),
    L("ピックアップは期間限定キャラのみ!", "Pick-ups: limited characters only!", [270, 102, 186, 16], "bar_r", [268, 100, 188, 18], clear="shade", clear_color="#200400c0")])
weapon_pu("20201022_weapon_001")
event_title("20201022_event_002", "逆襲のファントム", "Phantom Counterattack", [64, 40, 280, 50], tagjp="ボックスガチャ", sub=("ボックスガチャ", "Box Draws", [300, 86, 156, 30]), style="gold")
event_title("20201022_event_001", "逆襲のファントム", "Phantom Counterattack", [64, 38, 340, 56], top=("EP3イベント", "EP3 Event", [168, 14, 176, 24]),
            rerun=[394, 14, 62, 42], style="gold")
awaken("20201022_chara_002", "Adray")
w("20201022_chara_001", "The Halloween 2020 pick-up gacha's banner (Vampire Maria / Magician Peppita).", [
    tag("ガチャ"), band("ピックアップキャラガチャ ハロウィン2020 出現確率UP!! 10連目はピックアップ確率3倍!", "Pick-up Character Draws\nHalloween 2020\nRate UP!!\n10th 10-chain: pick-up x3!",
                        [172, 12, 176, 106], size=16)])
w("20201022_campaign_001", "The item shop's Halloween weapon sets campaign banner.", [
    tag("キャンペーン"), band("アイテムショップで ハロウィン武器強化セット 期間限定追加", "Limited-time Halloween\nWeapon Enhancement Sets\nin the Item Shop", [246, 4, 210, 116], size=17)])
weapon_pu("20201015_weapon_001")
wadrum("20201015_event_001", 4)
xmas_rerun("20201015_chara_003", 0, "Rerun Halloween 2017", x1=226)
xmas_rerun("20201015_chara_001", 0, "Rerun Maid", x1=226, bonus=False)
wadrum("20201008_event_001", 4, rerun=True, sub=False)
w("20201008_chara_004", "The rerun Tales of the Rays collaboration pick-up gacha's banner (Cress / Mint: glossary).", [
    tag("ガチャ"), L("テイルズ オブ ザ レイズ キャラクターピックアップ", "Tales of the Rays Character Pick-up", [166, 14, 290, 14], "blue_s", [164, 14, 292, 15], clear="inpaint", size=12),
    band("復刻", "Rerun", [58, 30, 46, 46], "blue", size=13),
    band("上方修正! 出現確率Up!! 10連目はピックアップ確率3倍!", "Rates raised!\nRate UP!!\n10th 10-chain: pick-up rate x3!", [286, 30, 170, 88], size=18)])
xmas_rerun("20201008_chara_003", 0, "Rerun Maid", x1=226, bonus=False)
xmas_rerun("20201008_chara_002", 0, "Rerun Maid", x1=226, bonus=False)

# ---- 2020-10-08 .. 2020-08-27
rateup("20201008_chara_001", 270, "Maid Reimi &\nButler Arumat", y0=24)
wadrum("20200917_event_001", 3)
w("20200917_campaign_001", "The owned-character bonus / treasured weapon ticket exchange's banner.", [
    band("所持キャラボーナス券 秘蔵武器引換券 交換所オープン!", "Owned Character Bonus Tickets &\nTreasured Weapon Exchange Tickets:\nthe Exchange is open!", [58, 26, 300, 92], "blue", size=18, align="left")])
weapon_pu("20200910_weapon_001")
w("20200910_event_002", "The Cave of the Seven Stars divine event's banner (神級: Divine).", [
    tag("イベント"), L("神級", "Divine", [60, 36, 50, 36], "blue_s", [58, 32, 52, 44], clear="inpaint", size=14),
    band("七星の洞窟", "Cave of the Seven Stars", [210, 30, 246, 50], size=24), band("神級イベント", "Divine Event", [296, 84, 156, 30], size=16)])
wadrum("20200910_event_001", 3, rerun=True, sub=False)
awaken("20200910_chara_004", "Karlyn")
rateup("20200910_chara_003", 260, "Divine Wing Fayt", y0=24, extra=[band("復刻", "Rerun", [58, 70, 46, 44], "blue", size=13)])
w("20200910_chara_002", "Rena of Divine Stars' step-up gacha banner.", [
    tag("ガチャ"),
    band("★5神星のレナ ステップ10は神星のレナ1体確定!", "★5 Rena of Divine Stars\nStep 10: Rena of Divine\nStars guaranteed!", [56, 26, 220, 92], "gold", size=18, align="left"),
    band("10連10ステップ目 PU1体確定ガチャ", "10-chain Step 10:\n1 pick-up guaranteed", [312, 40, 144, 78], size=13)])
rateup("20200910_chara_001", 260, "Rena of Divine Stars", y0=24, extra=[band("復刻", "Rerun", [58, 58, 46, 44], "blue", size=13)])
event_title("20200903_event_001", "ファントム・コマンダー討伐", "Defeat the\nPhantom Commander", [70, 36, 380, 56], sub=(MIS[0], MIS[1], [150, 94, 210, 24]),
            top=("EP3イベント", "EP3 Event", [168, 14, 176, 24]), style="gold")
xmas_rerun("20200903_chara_002", 0, "Rerun Costume\nContest 2019", x1=236)
w("20200903_chara_001", "The SO3 Memorial pick-up gacha's banner.", [
    tag("ガチャ"), L("お負け付き", "Bonus", [58, 31, 50, 11], "omake", [57, 31, 48, 11]),
    band("SO3メモリアル ピックアップキャラガチャ ピックアップは期間限定キャラのみ!", "SO3 Memorial\nPick-up Character Draws\nLimited characters only!", [262, 20, 194, 98], size=18)])
weapon_pu("20200827_weapon_001")
event_title("20200827_event_002", "ファントム・コマンダー討伐", "Defeat the\nPhantom Commander", [60, 30, 250, 64], tagjp="ボックスガチャ",
            sub=("ボックスガチャ", "Box Draws", [300, 86, 156, 30]))
event_title("20200827_event_001", "ファントム・コマンダー討伐", "Defeat the\nPhantom Commander", [80, 36, 310, 70],
            top=("EP3イベント", "EP3 Event", [168, 14, 176, 24]), rerun=[394, 14, 62, 42])

# ---- 2020-08-27 .. 2020-08-06
STAR = "Star Ocean and\nthe Dreamy Shore"
awaken("20200827_chara_003", "Official Edge", x1=300)
xmas_rerun("20200827_chara_002", 0, "Rerun Swimsuit\n2020 (3)", x1=236)
rateup("20200827_chara_001", 270, "Lavarnia of the Shore &\nErys of the Shore", y0=20, kind="Swimsuit 2020 Character")
weapon_pu("20200820_weapon_001")
event_title("20200820_event_001", "星の海と夢の渚 ミッション追加", STAR + "\nMissions added", [56, 26, 230, 92], style="blue",
            top=("滅級・絶級追加", "Misery 2 & 3 added", [330, 14, 126, 20]))
w("20200820_campaign_001", "Sphere 211's new season banner.", [band("スフィア211 新シーズン開始", "Sphere 211\nNew Season Begins", [100, 26, 316, 88], "blue", size=28)])
event_title("20200813_event_001", "星の海と夢の渚 ミッション追加", STAR + "\nMissions added", [56, 26, 230, 92], style="blue")
w("20200813_chara_003", "The weekend-limited character pick-up gacha's banner.", [
    tag("ガチャ"), band("週末限定 キャラクターピックアップ ピックアップは期間限定キャラのみ!", "Weekend Limited\nCharacter Pick-up\nLimited characters only!", [266, 6, 192, 112], size=18)])
xmas_rerun("20200813_chara_002", 0, "Rerun Swimsuit\n2020 (2)", x1=236)
rateup("20200813_chara_001", 270, "Midsummer Welch &\nMidsummer Euwin", y0=20, kind="Swimsuit 2020 Character")
weapon_pu("20200806_weapon_001")
event_title("20200806_event_002", "星の海と夢の渚", STAR, [60, 26, 200, 92], tagjp="ボックスガチャ", sub=("ボックスガチャ", "Box Draws", [300, 86, 156, 30]))
w("20200806_event_001", "The Star Ocean and the Dreamy Shore event's banner (Misery 2 & 3 added).", [
    tag("イベント"), band("滅級絶級追加!", "Misery 2 & 3\nadded!", [56, 26, 150, 92], "blue", size=22, align="left"),
    band("星の海と夢の渚", STAR, [270, 26, 186, 92], "blue", size=20)])
awaken("20200806_chara_003", "Noel")
xmas_rerun("20200806_chara_002", 0, "Rerun Bunny Ears\nCharacters", x1=300)
xmas_rerun("20200806_chara_001", 0, "Rerun Swimsuit\n2019", x1=236)

# ---- 2020-07-30 .. 2020-06-25
event_title("20200730_event_001", "星の海と夢の渚", STAR, [56, 26, 220, 92], rerun=[282, 86, 60, 28])
w("20200730_chara_005", "The SO2 release-day anniversary gacha's banner.", [
    tag("ガチャ"), band("スターオーシャン2 発売日記念ピックアップ ★5キャラが10連で1体確定!!", "Star Ocean 2\nRelease Day Pick-up\n10-chain: 1 ★5\ncharacter guaranteed!!", [56, 26, 190, 92], "blue", size=16, align="left"),
    L("1人3回限定", "3 per player", [394, 14, 62, 14], "omake", [392, 14, 64, 16], size=10)])
w("20200730_chara_004", "The Sharpshooter role pick-up gacha's banner (Sharpshooter: Global's シューター).", [
    tag("ガチャ"), band("シューターロール pick up ピックアップキャラガチャ", "Sharpshooter Role\nPick-up Character Draws", [56, 26, 214, 88], "gold", size=20, align="left"),
    L("ピックアップは期間限定キャラのみ!", "Pick-ups: limited characters only!", [270, 102, 186, 16], "bar_r", [244, 100, 212, 18], clear="shade", clear_color="#200400c0")])
xmas_rerun("20200730_chara_002", 0, "Rerun Swimsuit\n2020 (1)", x1=236)
rateup("20200730_chara_001", 270, "Eternal Summer Verda &\nSummer Clair", y0=20)
w("20200730_campaign_004", "The 2nd Galactic Federation survey's banner.", [
    band("第2回 銀河連邦アンケート 回答のご協力をお願いします!!", "The 2nd Galactic Federation Survey\nPlease help us with your answers!!", [56, 18, 400, 100], "blue", size=24)])
w("20200730_campaign_003", "The owned-character bonus ticket exchange's banner.", [
    band("所持キャラボーナス券 交換所オープン!", "Owned Character Bonus Tickets:\nthe Exchange is open!", [58, 26, 290, 88], "blue", size=22, align="left")])
w("20200730_campaign_002", "The item shop's summer vacation enhancement sets campaign banner.", [
    tag("キャンペーン"), band("アイテムショップで なつやすみ武器強化セット なつやすみキャラ強化セット 期間限定追加", "Limited-time Summer Vacation\nWeapon & Character\nEnhancement Sets in the Item Shop", [236, 4, 220, 116], size=16)])
w("20200730_campaign_001", "The summer vacation campaign's banner.", [
    tag("キャンペーン"), band("なつやすみ Summer vacation! キャンペーン", "Summer Vacation\nCampaign", [56, 22, 256, 96], "blue", size=28)])
w("20200722_chara_004", "The weekend-limited character pick-up gacha's banner.", [
    tag("ガチャ"), band("週末限定 キャラクターピックアップ ピックアップは期間限定キャラのみ!", "Weekend Limited\nCharacter Pick-up\nLimited characters only!", [266, 6, 192, 112], size=18)])
event_title("20200701_event_001", "マルチプル・ギア討伐", "Defeat the\nMultiple Gear", [76, 34, 370, 60], sub=(MIS[0], MIS[1], [150, 94, 210, 24]),
            top=("EP3イベント", "EP3 Event", [168, 14, 176, 24]), style="gold")
weapon_pu("20200625_weapon_001")
event_title("20200625_event_001", "マルチプル・ギア討伐", "Defeat the\nMultiple Gear", [76, 34, 310, 82], top=("EP3イベント", "EP3 Event", [168, 14, 176, 24]), rerun=[394, 14, 62, 42])
awaken("20200625_chara_004", "Official Anne", x1=300)
w("20200625_chara_003", "The x3! star pick-up character gacha's banner.", [
    band("3倍! スターピックアップキャラガチャ", "x3! Star Pick-up\nCharacter Draws", [70, 16, 380, 92], size=28), tag("ガチャ"),
    L("※10連特典枠はございません", "* No 10-chain bonus slot", [330, 106, 126, 11], "omake", [326, 106, 130, 12], size=9)])
w("20200625_chara_002", "The SOA Memorial pick-up gacha's banner.", [
    tag("ガチャ"), L("お負け付き", "Bonus", [58, 31, 50, 11], "omake", [57, 31, 48, 11]),
    band("SOAメモリアル ピックアップキャラガチャ ピックアップは期間限定キャラのみ!", "SOA Memorial\nPick-up Character Draws\nLimited characters only!", [262, 20, 194, 98], size=18)])

# ---- 2020-06-25 .. 2020-05-21
ONI = "Demons Dance Upon\nthe Dying Star"
rateup("20200625_chara_001", 280, "Heath &\nLavarnia", y0=20, extra=[L("お負け付き", "Bonus", [58, 31, 50, 11], "omake", [57, 31, 48, 11])])
w("20200625_campaign_002", "The item shop's Sphere 211 sets campaign banner.", [
    tag("キャンペーン"), band("アイテムショップで スフィア211応援セット 期間限定追加", "Limited-time Sphere 211\nSupport Sets\nin the Item Shop", [244, 4, 212, 116], size=17)])
w("20200625_campaign_001", "Sphere 211's release campaign banner.", [
    tag("キャンペーン"), band("スフィア211 リリースキャンペーン", "Sphere 211\nRelease Campaign", [226, 26, 230, 92], "blue", size=26)])
wadrum("20200618_event_001", 2)
wadrum("20200611_event_001", 2, rerun=True, sub=False)
awaken("20200611_chara_003", "Dark Albel", x1=300)
xmas_rerun("20200611_chara_002", 0, "Rerun Bride\n2018", x1=236)
rateup("20200611_chara_001", 270, "Bride Karlyn &\nBride Tika", y0=20)
weapon_pu("20200604_weapon_001")
event_title("20200604_event_002", "滅びの星に鬼が舞う", ONI, [60, 26, 220, 92], tagjp="ボックスガチャ", sub=("ボックスガチャ", "Box Draws", [300, 86, 156, 30]), style="gold")
event_title("20200604_event_001", "滅びの星に鬼が舞う", ONI + "\nMisery 2 & 3 added", [58, 26, 210, 92], style="gold")
event_title("20200528_event_001", "滅びの星に鬼が舞う", ONI, [58, 26, 210, 92], rerun=[262, 64, 74, 40], style="gold")
awaken("20200528_chara_003", "Crimson Phia", x1=300)
w("20200528_chara_002", "The SO1 Memorial pick-up gacha's banner.", [
    tag("ガチャ"), L("お負け付き", "Bonus", [58, 31, 50, 11], "omake", [57, 31, 48, 11]),
    band("SO1メモリアル ピックアップキャラガチャ ピックアップは期間限定キャラのみ!", "SO1 Memorial\nPick-up Character Draws\nLimited characters only!", [262, 20, 194, 98], size=18)])
w("20200528_chara_001", "The kimono demons pick-up gacha's banner (Nel the Demon Slayer / Albel of Demon Flame).", [
    band("ピックアップキャラガチャ 滅びの星に鬼が舞う 出現確率UP!! 10連目はピックアップ確率3倍", "Pick-up Character Draws\n" + ONI.replace("\n", " ") + "\nRate UP!! 10th 10-chain: pick-up x3!", [56, 14, 400, 104], "gold", size=17), tag("ガチャ")])
wadrum("20200521_event_001", 1)

# ---- 2020-05-14 .. 2020-04-16
CYN = "Defeat Phantomize\nCynard"
weapon_pu("20200514_weapon_001")
wadrum("20200514_event_001", 1, rerun=True, sub=False)
awaken("20200514_chara_003", "Crimson Opera", x1=300)
w("20200514_chara_002", "The Divine Wing Maria / Wise God Mastima step-up gacha's banner.", [
    tag("ガチャ"), band("10連10ステップ目 PUいずれか1体確定ガチャ ステップ10はPUいずれか1体確定!", "10-chain Step 10:\n1 Pick-up guaranteed\nStep 10: 1 pick-up\nguaranteed!", [56, 26, 200, 92], "gold", size=17, align="left")])
rateup("20200514_chara_001", 270, "Divine Wing Maria &\nWise God Mastima", y0=20)
weapon_pu("20200507_weapon_001")
event_title("20200507_event_001", "ファントマイズ・サイナード討伐", CYN, [76, 34, 370, 60], sub=(MIS[0], MIS[1], [150, 94, 210, 24]),
            top=("EP3イベント", "EP3 Event", [168, 14, 176, 24]), style="gold")
w("20200507_chara_001", "The SO5 Memorial pick-up gacha's banner.", [
    tag("ガチャ"), L("お負け付き", "Bonus", [58, 31, 50, 11], "omake", [57, 31, 48, 11]),
    band("SO5メモリアル ピックアップキャラガチャ ピックアップは期間限定キャラのみ!", "SO5 Memorial\nPick-up Character Draws\nLimited characters only!", [262, 20, 194, 98], size=18)])
event_title("20200430_event_001", "ファントマイズ・サイナード討伐", CYN, [76, 34, 310, 82], top=("EP3イベント", "EP3 Event", [168, 14, 176, 24]), rerun=[394, 14, 62, 42])
awaken("20200430_chara_004", "Bacchus", x1=300)
for n, vol in (("20200430_chara_003", 2), ("20200430_chara_002", 1)):
    w(n, f"The Golden Week pick-up gacha's banner (vol. {vol}).", [
        tag("ガチャ"), band(f"ゴールデンウィーク{vol} GW ピックアップキャラガチャ", f"Golden Week {vol}\nPick-up\nCharacter Draws", [250, 26, 206, 76], size=20),
        L("★5はPU8体のみ!! 10連目はピックアップ確率3倍!", "★5: the 8 pick-ups only!! 10th 10-chain: pick-up rate x3!", [210, 104, 246, 14], "bar_r", [146, 102, 310, 16], clear="shade", clear_color="#200400c0", size=12)])
rateup("20200430_chara_001", 270, "Karlyn the Fox General &\nRicardo of the Cannon Armor", y0=20)
w("20200430_campaign_002", "The item shop's EP3 start sets campaign banner.", [
    tag("キャンペーン"), band("アイテムショップで EP3スタート記念セット 期間限定追加", "Limited-time EP3 Start\nCelebration Sets\nin the Item Shop", [244, 4, 212, 116], size=17)])
w("20200430_campaign_001", "The EP3 start campaign banner (the logo is the game's).", [
    tag("キャンペーン"), L("EP3 The Leash Codeスタート記念キャンペーン", "EP3 -The Leash Code- Start Campaign", [60, 98, 396, 20], "blue_s", [58, 98, 398, 20], clear="inpaint", size=15)])
xmas_rerun("20200416_chara_003", 0, "Rerun Idol\n2019", x1=236)

# ---- 2020-04-16 .. 2020-02-27
SNOW = "Hot Springs and the\nMischievous Snow Monsters"
xmas_rerun("20200416_chara_002", 0, "Rerun Idol\n2018", x1=236, bonus=False)
w("20200326_chara_005", "The SO5 release-day anniversary gacha's banner.", [
    tag("ガチャ"), L("スターオーシャン5発売日記念ガチャ", "Star Ocean 5 Release Day Draws", [170, 14, 200, 14], "blue_s", [168, 14, 210, 15], clear="inpaint", size=12),
    L("1人3回限定", "3 per player", [384, 14, 72, 14], "omake", [382, 14, 74, 16], size=10),
    band("スターオーシャン5 ★5キャラが10連で1体確定!!", "Star Ocean 5\n10-chain: 1 ★5\ncharacter guaranteed!!", [270, 30, 186, 88], "blue", size=18)])
weapon_pu("20200312_weapon_001")
w("20200312_chara_006", "The new-life support free gacha's banner.", [
    tag("ガチャ"), band("新生活応援 10連無料キャラガチャ 期間中5回まで10連無料!", "New Life Support\nFree 10-chain\nCharacter Draws\n5 free 10-chains in the period!", [270, 14, 186, 104], size=16)])
awaken("20200312_chara_005", "Chisato", x1=270)
for n, vol in (("20200312_chara_004", 2), ("20200312_chara_003", 1)):
    w(n, f"The White Day limited rerun pick-up gacha's banner ({vol}).", [
        tag("ガチャ"), L("お負け付き", "Bonus", [58, 31, 50, 11], "omake", [57, 31, 48, 11]),
        band("ホワイトデー ピックアップキャラガチャ", f"White Day {vol}\nPick-up Character Draws", [266, 34, 190, 76] if vol == 2 else [210, 34, 246, 76], size=20),
        L("この5キャラをピックアップ!", "These 5 characters are picked up!", [58, 103, 180, 14], "cap", [56, 102, 160, 16])])
w("20200312_chara_002", "Divine Wing Fayt's step-up gacha banner.", [
    tag("ガチャ"), band("神翼のフェイト", "Divine Wing\nFayt", [56, 26, 140, 70], "gold", size=22, align="left"),
    band("10連10ステップ目 PU1体確定ガチャ", "10-chain Step 10:\n1 pick-up guaranteed", [320, 50, 136, 52], size=13),
    L("ステップ10は神翼のフェイト1体確定!", "Step 10: Divine Wing Fayt guaranteed!", [58, 103, 230, 14], "bar_r", [56, 101, 236, 18], clear="shade", clear_color="#200400c0", align="left", size=13)])
rateup("20200312_chara_001", 240, "Divine Wing Fayt", y0=20)
w("20200312_campaign_002", "The item shop's 2020 new-life sets campaign banner.", [
    tag("キャンペーン"), band("アイテムショップで 2020年新生活応援 期間限定追加", "Limited-time 2020 New Life\nSupport Sets\nin the Item Shop", [244, 4, 212, 116], size=17)])
w("20200312_campaign_001", "The new-life support campaign banner.", [
    tag("キャンペーン"), band("新生活応援キャンペーン", "New Life Support Campaign", [160, 40, 296, 50], "gold", size=24)])
weapon_pu("20200305_weapon_001")
w("20200305_event_001", "The hot springs event's banner (raid boss, Misery 2 & 3 added).", [
    tag("イベント"), band("大討伐", "Raid Boss", [56, 54, 120, 40], "gold", size=20),
    band("温泉と悪戯好きの雪の魔物", SNOW, [228, 26, 228, 76], "gold", size=18),
    band(MIS[0], MIS[1], [258, 102, 186, 16], "gold", size=12)])
event_title("20200227_event_002", "温泉と悪戯好きの雪の魔物", SNOW, [56, 26, 250, 70], tagjp="ボックスガチャ", sub=("ボックスガチャ", "Box Draws", [300, 86, 156, 30]), style="gold")
w("20200227_event_001", "The hot springs event's banner (raid boss).", [
    tag("イベント"), band("大討伐", "Raid Boss", [56, 54, 120, 40], "gold", size=20),
    band("温泉と悪戯好きの雪の魔物", SNOW, [228, 26, 228, 92], "gold", size=18)])
awaken("20200227_chara_004", "Lucifer", x1=300)

# ---- 2020-02-27 .. 2020-01-01
def release_day(name, so):
    w(name, f"The SO{so} release-day anniversary gacha's banner.", [
        tag("ガチャ"), L(f"スターオーシャン{so}発売日記念ガチャ", f"Star Ocean {so} Release Day Draws", [170, 14, 200, 14], "blue_s", [168, 14, 210, 15], clear="inpaint", size=12),
        L("1人3回まで", "3 per player", [384, 14, 72, 14], "omake", [382, 14, 74, 16], size=10),
        band(f"スターオーシャン{so} ★5キャラが10連で1体確定!!", f"Star Ocean {so}\n10-chain: 1 ★5\ncharacter guaranteed!!", [270, 30, 186, 88], "blue", size=18)])
SPIRIT = "Spirit of\nRenewal"
release_day("20200227_chara_003", 3)
rateup("20200227_chara_001", 270, "Hot Spring Evelysse &\nHot Spring Rena", y0=20)
w("20200220_campaign_004", "The purchase bonus campaign banner.", [tag("キャンペーン"), band("ご購入特典キャンペーン", "Purchase Bonus\nCampaign", [56, 26, 260, 92], "blue", size=26, align="left")])
w("20200220_campaign_003", "The Galaxy Pass banner (its GALAXY logo is the game's).", [
    L("ギャラクシーパス", "Galaxy Pass", [300, 36, 156, 34], "blue", [294, 34, 162, 36], clear="inpaint", size=22),
    band("お得な機能を30日間利用可能!", "Handy features for 30 days!", [110, 82, 330, 30], "blue", size=17)])
w("20200213_event_001", "The 2020 Valentine event's banner (Chocolate in the Bell).", [
    tag("イベント"), band("チョコレート・イン・ザ・ベル 2020バレンタインイベント", "Chocolate in the Bell\n2020 Valentine Event", [196, 30, 260, 88], "gold", size=22)])
awaken("20200213_chara_004", "Azure Rena", x1=290)
release_day("20200213_chara_003", 4)
rateup("20200213_chara_002", 270, "the Valentine 2019\ncharacters", y0=20, extra=[band("復刻", "Rerun", [58, 30, 46, 44], "blue", size=13)])
rateup("20200213_chara_001", 270, "Miki of Sweet Love &\nErys of the Heavenly Wings", y0=20)
w("20200206_campaign_001", "The treasured weapon exchange ticket exchange's banner.", [
    band("秘蔵武器引換券 交換所オープン!", "Treasured Weapon Exchange Tickets:\nthe Exchange is open!", [58, 26, 330, 88], "blue", size=22, align="left")])
weapon_pu("20200123_weapon_001")
awaken("20200123_chara_003", "Pericci", x1=270)
w("20200123_chara_002", "The Lunar New Year step-up gacha banner.", [
    tag("ガチャ"), band("春節ガチャ 10連10ステップ目PUいずれか1体確定!", "Lunar New Year Draws\n10-chain Step 10:\n1 pick-up guaranteed!", [250, 40, 206, 78], size=18)])
rateup("20200123_chara_001", 270, "Queen Nel &\nQueen Clair", y0=20)
event_title("20200106_event_002", "改新の志 2020新年イベント", SPIRIT, [56, 26, 220, 92], tagjp="ボックスガチャ", sub=("ボックスガチャ", "Box Draws", [300, 86, 156, 30]), style="gold")
w("20200106_event_001", "The 2020 New Year event's banner (Misery 2 & 3 added).", [
    tag("イベント"), band("改新の志 2020新年イベント", SPIRIT + "\n2020 New Year Event", [56, 26, 220, 92], "gold", size=20),
    band("滅級・絶級追加", "Misery 2 & 3\nadded", [380, 14, 76, 104], "gold", size=13)])
rateup("20200102_chara_001", 270, "New Year Evelysse &\nNew Year Tika", y0=20, extra=[band("復刻", "Rerun", [58, 30, 46, 44], "blue", size=13)])
weapon_pu("20200101_weapon_001")
event_title("20200101_event_001", "改新の志 2020新年イベント", SPIRIT + "\n2020 New Year Event", [56, 26, 220, 92], style="gold")
w("20200101_chara_002", "The New Year gift pick-up gacha's banner.", [
    tag("ガチャ"), band("新年お年玉 ピックアップキャラガチャ ★5はPU6体のみ!! 10連目はピックアップ確率3倍", "New Year's Gift\nPick-up Character Draws\n★5: the 6 pick-ups only!!\n10th 10-chain: pick-up x3", [250, 14, 206, 104], size=16)])
rateup("20200101_chara_001", 270, "Reimi of the Phoenix Bow &\nKarlyn of the Dawn Fox", y0=20)
w("20200101_campaign_001", "The item shop's New Year sets campaign banner.", [
    tag("キャンペーン"), band("アイテムショップで 新年あけましておめでとう福袋 期間限定追加", "Limited-time New Year\nLucky Bags\nin the Item Shop", [244, 4, 212, 116], size=17)])
