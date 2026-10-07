"""The character pick-up panels (1024x512) of the live gachas: the "SOn より参戦!!" tag and a title band
with the role and the name (names: glossary.tsv / Global's; the skill blurb below stays Japanese)."""
import os, sys; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); from common import *  # noqa: E402,F403
S = {
 "erase": {"clear": "inpaint"},
 "tag": {"size": 40, "bold": 3, "fill": "#ffffff", "outline": "#2a0a40", "outline_width": 3, "glow": "#c080ffa0", "glow_radius": 2, "align": "left", "clear": "shade", "clear_color": "#1a0a28c0"},
 "name": {"size": 58, "bold": 3, "fill": "#ffffff", "outline": "#3a0a50", "outline_width": 4, "glow": "#ff80ffa0", "glow_radius": 3, "align": "right", "clear": "none"},
 "role": {"size": 28, "bold": 2, "fill": "#ffffff", "outline": "#5a0010", "outline_width": 2, "align": "right", "clear": "none"},
 "band": {"clear": "shade", "clear_color": "#1a0a28b0"},
}
ROLE = {"A": ("アタッカー", "Attacker"), "C": ("キャスター", "Invoker"), "D": ("ディフェンダー", "Defender"), "H": ("ヒーラー", "Healer"), "S": ("シューター", "Sharpshooter")}
# panels whose name sits at the top right (under the catch line), not at the middle right
TOP = {"20181115_chara_PU_004_02", "pickup_img_chara_0032_02", "pickup_img_chara_0103_02", "pickup_img_chara_1712_007_02"}
# panel: (series tag or None, role, Japanese name, English name)
PANELS = {
 "20181115_chara_PU_002": ("SO4", "A", "エイルマット", "Arumat"),
 "20181115_chara_PU_003": (None, "A", "カーリン", "Karlyn"),
 "20181115_chara_PU_004_02": ("SO4", "C", "フェイズ", "Faize"),
 "20190214_chara_PU_002": ("SO4", "A", "アンリ", "Henri"),
 "20190214_chara_PU_003": ("SO4", "D", "バッカス", "Bacchus"),
 "20190501_chara_PU_001": ("SO4", "C", "マスティマ", "Mastima"),
 "20190509_chara_PU_001": ("SO3", "A", "スフレ", "Peppita"),
 "20190815_chara_PU_003": ("SO1", "H", "ヨシュア", "Ioshua"),
 "20190912_chara_PU_001": ("SO2", "A", "蒼星のチサト", "Azure Chisato"),
 "pickup_img_chara_0032_02": ("SO4", "D", "エッジ", "Edge"),
 "pickup_img_chara_0045": ("SO4", "H", "青春のメリクル", "Youth Meracle"),
 "pickup_img_chara_0049_02": ("SO3", "A", "フェイト", "Fayt"),
 "pickup_img_chara_0066": ("SO2", "D", "灼炎のアシュトン", "Blazing Ashton"),
 "pickup_img_chara_0093": (None, "D", "ユーイン", "Euwin"),
 "pickup_img_chara_0094": ("SO2", "C", "紅輝のオペラ", "Crimson Opera"),
 "pickup_img_chara_0103_02": (None, "S", "ベルタ", "Berta"),
 "pickup_img_chara_1712_007_02": ("SO5", "A", "フィデル", "Fidel"),
}
for name, (tag, role, jp, en) in PANELS.items():
    labels = []
    if tag:
        labels.append(L(f"{tag}より参戦!!", f"From {tag}!!", [150, 18, 340, 56], "tag", [140, 14, 384, 70]))
    band = [560, 92, 340, 132] if name in TOP else [480, 248, 400, 116]
    x, y, w, h = band
    labels += [L("", "", band, "erase", band), L("", "", band, "band", band),
               L(jp, en, [x + 10, y + 6, w - 20, 66], "name"),
               L(ROLE[role][0], ROLE[role][1], [x + 20, y + 76, w - 30, 34], "role")] if name in TOP else [
               L("", "", band, "erase", band), L("", "", band, "band", band),
               L(ROLE[role][0], ROLE[role][1], [x + 20, y + 6, w - 30, 34], "role"),
               L(jp, en, [x + 10, y + 42, w - 16, 66], "name")]
    write(name, f"A character pick-up panel ({en}).", S, labels)
