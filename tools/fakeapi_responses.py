"""Generate FakeApiCaller responses (for the port option --fake-server DIR) from master data.

    tools/fakeapi_responses.py DIR [--mission LABEL] [--gacha LABEL] [--draws N] [--seed S]
                               [--db data/basmaster-3.7.0.sqlite3]

This is OUR INVENTION, not the game's server logic: the real server's responses were never
shipped. It writes JSON sources plus the .msgp files the fake server serves:
  mission_start   data.MissionParameter (+ mission_stage rows of the mission, no drops),
                  data.PlayMission
  mission_end     data.MissionEndResult, data.DropList (fol from the mission, no items),
                  data.AddItem (one item), data.StockItem (one stack item),
                  data.MissionResultCharacter (for the first gacha character, uid 0x7f000000),
                  data.MissionResultCharacterFavor (character id 1)
  gacha_pc / gacha_ticket / gacha_once_item
                  data.GachaItems: N draws of random playable roles (seeded), each also added
                  as a new character (data.AddCharacter) with a fresh player_character_id
  player_get      {"data": {}, "status": 0}; with --save Game.xml, data.Character holds the
                  save's roster (person_master_role_id_N) as owned characters, uid 0x7e000000+N
  update_home     {"data": {}, "status": 0}
  present_get_all data.PresentBox: N_PRESENTS presents (ids 1..N, fol / free coin / item
                  contents, no deadline)
  present_get_item
                  data.PresentGetResult.get: the ids received (the first two), .add: the box
                  left afterwards (the rest), .result.fol / free_coin
  gacha_in_data   data.GachaHashMap: every master_gacha id with a hash, open until 2099;
                  data.Wallet: 100000 free 紋章石
                  (GetGachaInData; the port serves it, the guest fake never queued it)
Keys follow port/fakeapi/schema.txt and fields.txt; which ones a screen really needs is still to
be found by running it (see docs/notes.md "Offline server (FakeApiCaller)").
"""
import argparse
import json
import os
import random
import sqlite3
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
from fakeapi_msgp import build  # noqa: E402
from soa_save.adld import chash32 as _chash32  # noqa: E402


def rows(db, sql, *args):
    cur = db.execute(sql, args)
    cols = [d[0] for d in cur.description]
    return [dict(zip(cols, r)) for r in cur.fetchall()]


def u(v):
    return 0 if v is None else v


def chash32(text):
    """Framework::CHash32 of a string (soa_save.adld.chash32)."""
    return _chash32(text.encode())


def person_status(db, uid, role_id, level):
    """A CPersonStatusInfo (the battle status of one party member, as the server computed it).
    Stats are our invention: the role's base values scaled by level; no gear, no factors."""
    r = rows(db, "select * from master_role where id = ?", role_id)
    if not r:
        sys.exit("no role %s" % role_id)
    r = r[0]
    w = rows(db, "select * from master_weapon where master_weapon_kind_id = ? order by serial_number limit 1",
             r["master_weapon_kind_id"])
    w = w[0] if w else {"id": 0, "master_weapon_kind_id": 0, "master_weapon_kind_id_label": ""}
    scale = 1 + level / 10.0
    e = {
        "id": uid, "player_id": 1, "player_level": 1, "player_name": "Player",
        "master_role_id": r["id"], "level": level, "exp": 0, "next_exp": 0, "limit_break_count": 0,
        "weapon_item_id": 0, "accessory_item_id": 0,
        "hp": float(u(r["hp"])) * 10 * scale, "attack": float(u(r["attack"])) * scale,
        "intelligence": float(u(r["intelligence"])) * scale, "defence": float(u(r["defence"])) * scale,
        "hit": float(u(r["hit"])) * scale, "guard": float(u(r["guard"])) * scale, "ap": 100.0,
        "def_fire": 0.0, "def_water": 0.0, "def_wind": 0.0, "def_earth": 0.0, "def_thunder": 0.0,
        "def_light": 0.0, "def_dark": 0.0,
        "rush1": u(r["rush_skill1_id"]), "rush1_label": r["rush_skill1_id_label"] or "",
        "rush_skill1_factor_id": u(r["rush_skill1_factor_id"]), "rush1_level": 1,
        "rush_gauge_max": int(u(r["rush_gauge_max"])), "rush_gauge_use": int(u(r["rush_gauge_use"])),
        "weapon_id": w["id"], "master_weapon_kind_id": w["master_weapon_kind_id"],
        "weapon_kind_id_label": w["master_weapon_kind_id_label"], "weapon_master_item_id": 0,
        "weapon_limit_break_count": 0, "weapon_level": 1,
        "accessory_master_item_id": 0, "accessory_limit_break_count": 0, "accessory_level": 0,
        "awaken_level": 0, "favor_level": 1, "is_rookie": False, "is_subscription": False,
        "is_multi_main_character": False, "parent_master_role_id": 0, "mastery_talent_id": 0,
    }
    for i in (1, 2, 3):
        e["skill%d" % i] = u(r["master_skill%d_id" % i])
        e["skill%d_label" % i] = r["master_skill%d_id_label" % i] or ""
        e["skill%d_level" % i] = 1 if r["master_skill%d_id" % i] else 0
    return e


def mission_start(db, label, party):
    m = rows(db, "select * from master_mission where id_label = ?", label)
    if not m:
        sys.exit("no mission %s" % label)
    m = m[0]
    stages = rows(db, "select * from master_mission_stage where master_mission_id = ? order by order_id", m["id"])
    return m, {
        "data": {
            "MissionParameter": {
                "master_mission_id": m["id"],
                "master_mission_id_label": m["id_label"],
                "is_surprise": False,
                "multi_player_count": 1,
                "stamina_cost": u(m["use_stamina"]),
                "is_event_drop_by_favor": False,
                "overwrite_enemy_level": 0,
                "add_enemy_level": 0,
                "mission_stage": [
                    {
                        "id": s["id"],
                        "id_label": s["id_label"],
                        "order_id": u(s["order_id"]),
                        "is_boss": bool(s["is_boss"]),
                        "serial_number": u(s["serial_number"]),
                        "master_mission_id": s["master_mission_id"],
                        "master_mission_id_label": s["master_mission_id_label"],
                        "master_stage_layout_id": u(s["master_stage_layout_id"]),
                        "master_stage_layout_id_label": s["master_stage_layout_id_label"] or "",
                        "master_enemy_party_id": u(s["master_enemy_party_id"]),
                        "master_map_id": u(s["master_map_id"]),
                        "master_map_id_label": s["master_map_id_label"] or "",
                        # a uint in CMissionStageInfo: the CHash32 of the master row's name
                        "stage_bgm": chash32(s["stage_bgm"]) if s["stage_bgm"] else 0,
                        "is_surprise_enemy_stage": bool(s["is_surprise_enemy_stage"]),
                    }
                    for s in stages
                ],
                "mission_drop": [],
                "mission_drop_rare": [],
                "common_drop": [],
                "battle_evaluation_drop": [],
            },
            "PlayMission": {"mission_id": m["id"], "is_play": 1, "is_expired": False, "is_maintenance": False},
            # BattleParameter.PlayerCharacter (CPlayerCharacterInfoList = InfoBaseArray<CPersonStatusInfo>,
            # CParameterManager+0x23a0, vector at +0x23d8) is the selected party CStageManager takes.
            "BattleParameter": {"rental_sub_character_id": 0, "PlayerCharacter": party},
        },
        "status": 0,
    }


def mission_end(m, chara_uid, favor_id):
    # AddItem / StockItem / MissionResultCharacter exercise the handler's post-apply steps
    # (AddItem, UpdateStackItem, the per-character results); the values are placeholders.
    return {
        "data": {
            "MissionEndResult": {"mission_time": 60},
            "DropList": {"fol": u(m["fol"]), "free_coin": 0, "up_fol_rate": 0, "item": [], "character": [], "stock_item": []},
            "AddItem": [{"id": 0x7d000001, "master_item_id": 1, "item_type": 1, "boosted_point": 0, "limit_break_count": 0}],
            "StockItem": [{"id": 1, "master_item_id": 1, "item_type": 1, "use_count": 3}],
            # map-shaped infos: msgpack maps keyed by the id as a string
            "MissionResultCharacter": {str(chara_uid): {"id": chara_uid, "before_level": 1, "before_exp": 0, "after_level": 2,
                                                        "after_exp": 50}},
            "MissionResultCharacterFavor": {str(favor_id): {"id": favor_id, "master_role_same_role_id": favor_id,
                                                            "before_favor_level": 1, "before_favor_point": 0,
                                                            "after_favor_level": 1, "after_favor_point": 10,
                                                            "added_event_drop_at": ""}},
        },
        "status": 0,
    }


def gacha(db, rng, n, first_uid):
    roles = rows(db, "select id, id_label, rarity from master_role where id_label like 'role_cp%' order by id")
    items, chars = [], []
    for i in range(n):
        r = rng.choice(roles)
        uid = first_uid + i
        items.append({"master_item_id": 0, "player_item_id": 0, "master_role_id": r["id"], "player_character_id": uid,
                      "duplication": 0, "is_mutation": False})
        chars.append({"id": uid, "master_role_id": r["id"], "limit_break_count": 0, "awaken_level": 0})
    # AddCharacter (new characters, appended to the roster by CApiNotify::AddCharacter; no
    # duplicate check, so serving the same file twice adds the same uids twice) is a map-shaped
    # info: a msgpack map keyed by the uid (as a string). "Character" would replace the whole
    # owned roster.
    return {"data": {"GachaItems": items, "AddCharacter": {str(c["id"]): c for c in chars}}, "status": 0}


def present(i):
    # content_type: 1 fol, 2 free coin, 3 item (our choice; the screens aren't driven with these)
    ctype = (i % 3) + 1
    return {"id": i, "player_id": 0, "content_type": ctype, "content_id": 0 if ctype != 3 else 1,
            "reason_type": 1, "reason_param": 0, "is_receive": 0, "free_text_message_id": 0, "deadline_at": ""}


N_PRESENTS = 5


def present_get_all():
    return {"data": {"PresentBox": [present(i) for i in range(1, N_PRESENTS + 1)]}, "status": 0}


def present_get_item():
    # PresentGetResult.get -> CParameterManager +0x4430 (ids received), .add -> +0x4480: the box
    # afterwards (CApiNotify::ApplyGetPresent erases the received ids from the box, clears it and
    # refills it from .add)
    return {"data": {"PresentGetResult": {"get": [1, 2], "add": [present(i) for i in range(3, N_PRESENTS + 1)],
                                          "result": {"fol": 100, "free_coin": 10}}}, "status": 0}


def gacha_in_data(db):
    """GetGachaInData: data.GachaHashMap (CGachaHashInfoMap at CParameterManager+0x5070), a map
    master_gacha id -> {"GachaHashList": [CGachaHashInfo {master_gacha_id, hash, opened_at,
    closed_at}]}. CGacha::IsEnableHash(id) takes the first entry whose opened_at <= now <=
    closed_at and hands its hash to the draw request; a gacha without one isn't listed. We send
    one entry per master_gacha row, open until 2099 (the master row's own dates still apply)."""
    m = {}
    for r in rows(db, "select id, opened_at from master_gacha order by id"):
        m[str(r["id"])] = {"GachaHashList": [{"master_gacha_id": r["id"], "hash": "%08x" % r["id"],
                                              "opened_at": r["opened_at"] or "2016-01-01 00:00:00",
                                              "closed_at": "2099-12-31 23:59:59"}]}
    # The player's wallet (CWalletInfo at CParameterManager+0x1f20), so draws aren't refused for
    # want of 紋章石 (the offline save has none).
    wallet = {"free_coin": 100000, "pay_coin": 0, "total_coin": 100000, "android_coin": 0}
    return {"data": {"GachaHashMap": m, "Wallet": wallet}, "status": 0}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dir")
    ap.add_argument("--db", default="data/basmaster-3.7.0.sqlite3")
    ap.add_argument("--mission", default="mf01_001")
    ap.add_argument("--draws", type=int, default=10)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--save", help="shared_prefs Game.xml whose roster player_get returns (and the party)")
    ap.add_argument("--party", help="comma-separated master_role id_labels for the battle party "
                    "(default: the first 4 of --save's roster)")
    ap.add_argument("--level", type=int, default=50, help="party level")
    a = ap.parse_args()
    db = sqlite3.connect(a.db)
    rng = random.Random(a.seed)
    src = os.path.join(a.dir, "json")
    os.makedirs(src, exist_ok=True)
    player = {"data": {}, "status": 0}
    roles = []
    if a.save:
        from soa_save.kvs import KVSFile
        from soa_save.roster import roster
        roles = roster(KVSFile.load(a.save))
        player["data"]["Character"] = [
            {"id": 0x7e000000 + i, "master_role_id": rid, "limit_break_count": 0, "awaken_level": 0}
            for i, rid in enumerate(roles)
        ]
    if a.party:
        roles = [rows(db, "select id from master_role where id_label = ?", l)[0]["id"] for l in a.party.split(",")]
    party = [person_status(db, 0x7e000000 + i, rid, a.level) for i, rid in enumerate(roles[:4])]
    m, ms = mission_start(db, a.mission, party)
    out = {"mission_start": ms, "mission_end": mission_end(m, 0x7f000000, 1), "player_get": player,
           "update_home": {"data": {}, "status": 0}, "gacha_in_data": gacha_in_data(db),
           "present_get_all": present_get_all(), "present_get_item": present_get_item()}
    for i, name in enumerate(("gacha_pc", "gacha_ticket", "gacha_once_item")):
        out[name] = gacha(db, rng, a.draws if name != "gacha_once_item" else 1, 0x7f000000 + i * 0x100)
    for name, body in out.items():
        with open(os.path.join(src, name + ".json"), "w") as f:
            json.dump(body, f, indent=1, ensure_ascii=False)
        build(os.path.join(src, name + ".json"), os.path.join(a.dir, name + ".msgp"))


if __name__ == "__main__":
    main()
