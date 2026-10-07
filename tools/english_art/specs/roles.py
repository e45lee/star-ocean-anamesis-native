import os, sys; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); from common import *  # noqa: E402,F403
FIRE = {"main": {"size": 30, "bold": 2, "fill": "#ffeab0", "outline": "#5a0800", "outline_width": 3, "glow": "#ff6020a0", "glow_radius": 2, "align": "right"},
        "sub": {"size": 18, "bold": 2, "fill": "#ffffff", "outline": "#5a1000", "outline_width": 2, "align": "right", "clear": "none"},
        "tag": {"size": 15, "bold": 1, "fill": "#ffffff", "align": "left"}}
ROLES = {"Atk": ("アタッカー", "Attacker"), "Cas": ("キャスター", "Invoker"), "Def": ("ディフェンダー", "Defender"), "Hel": ("ヒーラー", "Healer"),
         "Shu": ("シューター", "Sharpshooter"), "All": ("全種", "All Roles")}
banners = ["banner_roleevoAtk_001", "banner_roleevoCas_001", "banner_roleevoDef_001", "banner_roleevoHel_001", "banner_roleevoShu_001", "banner_roleevoAll_002",
           "banner_roleexAtk_001", "banner_roleexCas_001", "banner_roleexDef_001", "banner_roleexHel_001", "banner_roleexShu_001", "banner_roleexAll_001"]
for b in banners:
    evo = "evo" in b
    role = b.split("evo" if evo else "ex")[1][:3]
    rjp, ren = ROLES[role]
    main = L("進化素材ミッション" if evo else "経験値素材ミッション", "Augment Mission" if evo else "EXP Material Mission",
             [190, 66, 262, 38] if evo else [166, 66, 286, 38], "main", [196, 42, 262, 70] if evo else [162, 42, 296, 68])
    labels = [main, L(rjp, ren, [250, 45, 202, 22], "sub")]
    if b == "banner_roleevoAll_002": labels.append(L("ドロップ率アップ!", "Drop Rate Up!", [94, 24, 118, 20], "tag", [92, 23, 120, 22], clear="inpaint"))
    if b == "banner_roleexAll_001": labels.append(L("全日解放", "Open All Day", [66, 26, 90, 22], "tag", [64, 26, 90, 22], clear="inpaint"))
    write(b, f"The {ren.lower()} {'augment' if evo else 'EXP'}-material event's banner (Global: Augment Mission, EXP materials, the role names).", FIRE, labels)
