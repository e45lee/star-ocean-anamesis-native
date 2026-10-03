#!/usr/bin/env python3
"""Writes server/tests/fixtures/state-v0.sql, the committed v0 state of PLAN-schema 4.2.

    tools/make_state_fixture.py STATE_V0 [--master data/basmaster-3.7.0.sqlite3] [--out server/tests/fixtures/state-v0.sql]

STATE_V0 is a state DB written by a soa-server from before PLAN-schema S1 (user_version 0, the
modules' tables made lazily, no wire_device), seeded from the synthetic test seed. The committed
fixture was made from the `items-party` corpus replayed by 30db20b's soa-server:

    tools/server_build_at.sh 30db20b /tmp/v0                    # soa-server at the last v0 commit
    mkdir /tmp/fx && cp server/tests/replay/items-party/requests.txt /tmp/fx/
    sed 's#data/saves/seed/Game.xml#port/server-data/test-seed.xml#' server/tests/replay/items-party/options > /tmp/fx/options
    TZ=America/Toronto /tmp/v0/soa-server $(cat /tmp/fx/options) --replay /tmp/fx --out /tmp/fx/out   # one option per line
    tools/make_state_fixture.py /tmp/fx/out/data/server.sqlite3

On a copy of it the script (1) creates wire_device as soa-server's map_device did, (2) gives every
empty table synthetic rows (master ids taken from the master, so state::check resolves them),
(3) plants the dirt the later migrations must clean (below), then dumps the schema (each table's
stored CREATE text, verbatim) and every row as a column-named INSERT, sorted. No real ids: the
player is the test seed's LOCAL00001 "Tessa", every uid is the test seed's or made up here.

The dirt (PLAN-schema 4.2): a roster.weapon_uid naming a missing item; a party_member.weapon_uid
naming a sold item (deleted from items); an orphan roster_ext row; a gear_items row on that sold
weapon; favor.event_drop_at both '' and a time string; meta view_status = 18446744073709551615;
a titles.got_at = 0; player.party_id = 1 with no party_set row; wire_device with player_id 0.
S3's key cases (meta title '0', a dangling support_uid, the deep-space keys, the counters popup
flag, sphere_meta's other keys) are planted by the test server/schema-migrate-v3 itself.
"""
import argparse
import os
import sqlite3
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# soa-server's map_device created it with this text (net/game.cpp before S1; state/schema.cpp now)
WIRE_DEVICE = ("create table if not exists wire_device (uuid text primary key, player_id integer, device_type integer, "
               "first_seen integer, last_seen integer)")
T = 1790841600  # 2026-10-01 04:00:00 America/Toronto: the synthetic rows' times
DAY = 1790755200  # 2026-09-30 04:00:00: a reset-day start
MISSING_ITEM = 0x7D0FFFFF  # an item uid no state has (kItemUid0 + 0xfffff)
ORPHAN_UID = 0x7E0FFFFF  # a roster uid no state has


def literal(v):
    if v is None:
        return "NULL"
    if isinstance(v, int):
        return str(v)
    if isinstance(v, float):
        return repr(v)
    if isinstance(v, bytes):
        return "X'" + v.hex() + "'"
    return "'" + str(v).replace("'", "''") + "'"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("state")
    ap.add_argument("--master", default=os.path.join(ROOT, "data", "basmaster-3.7.0.sqlite3"))
    ap.add_argument("--out", default=os.path.join(ROOT, "server", "tests", "fixtures", "state-v0.sql"))
    a = ap.parse_args()

    src = sqlite3.connect("file:%s?mode=ro" % a.state, uri=True)
    db = sqlite3.connect(":memory:")
    src.backup(db)
    src.close()
    m = sqlite3.connect("file:%s?mode=ro" % a.master, uri=True)
    if db.execute("pragma user_version").fetchone()[0] != 0:
        sys.exit("make_state_fixture: %s isn't a v0 state (user_version != 0)" % a.state)
    if db.execute("select count(*) from player").fetchone()[0] != 1:
        sys.exit("make_state_fixture: %s has no player" % a.state)

    def one(conn, sql, *args):
        r = conn.execute(sql, args).fetchone()
        return r[0] if r else None

    def count(table):
        return one(db, 'select count(*) from "%s"' % table)

    def insert(table, **cols):
        db.execute('insert into "%s" (%s) values (%s)' % (table, ", ".join(cols), ", ".join("?" * len(cols))), tuple(cols.values()))

    # ---- (1) soa-server's table ------------------------------------------------------------------
    db.execute(WIRE_DEVICE)

    # ---- the ids the synthetic rows use ----------------------------------------------------------
    uids = [r[0] for r in db.execute("select uid from roster order by uid limit 2")]
    uid_a, uid_b = uids
    role_a = one(db, "select role_id from roster where uid = ?", uid_a)
    role_b = one(db, "select role_id from roster where uid = ?", uid_b)
    same_a = one(m, "select same_role_id from master_role where id = ?", role_a)
    same_b = one(m, "select same_role_id from master_role where id = ?", role_b)
    mission = one(m, "select min(id) from master_mission")
    mission2 = one(m, "select min(id) from master_mission where id > ?", mission)
    event_mission, event_area = m.execute("select id, master_event_area_id from master_event_mission order by id limit 1").fetchone()
    ds_mission, ds_area = m.execute("select id, master_deep_area_id from master_deep_space_mission order by id limit 1").fetchone()
    ranking, ranking_group = m.execute("select id, ranking_group_id from master_event_ranking order by id limit 1").fetchone()
    contents, ex_shop = m.execute("select id, master_exchange_shop_id from master_exchange_shop_contents order by id limit 1").fetchone()
    stepup_head = one(m, "select min(id) from master_gacha where is_stepup = 1")
    box_gacha = one(m, "select min(id) from master_gacha where is_box = 1")
    season = one(m, "select min(id) from master_sphere211")
    stack_item, stack_type = m.execute("select id, type from master_item where type not in (1, 2, 3) order by id limit 1").fetchone()

    # ---- (2) every empty table gets rows ----------------------------------------------------------
    fill = [
        ("achievements", dict(id=one(m, "select min(id) from master_achievement"), progress=0, received_at=T)),
        ("assist", dict(uid=uid_a, assist_uid=uid_b)),
        ("box_gacha", dict(gacha_id=box_gacha, box_index=0, reset_count=0, drawn="")),
        ("box_state", dict(gacha_id=box_gacha, total_count=3, reset_count=0)),
        ("box_slots", dict(gacha_id=box_gacha, slot_id=1, drawn=3)),
        ("ds_area", dict(area_id=ds_area, exp=10, is_new=0, last_play=1)),
        ("ds_offer", dict(mission_id=ds_mission, area_id=ds_area, bonus_set_id=0, closed_at=0, ship_id=1, is_new=0, play_count=1,
                          play_count_daily=1, play_count_weekly=1, updated_at=T)),
        ("ds_ship", dict(ship_id=1, area_id=ds_area, mission_id=ds_mission, bonus_set_id=0, item_id=0, uids="%d,%d," % (uid_a, uid_b),
                         started_at=T, closed_at=T + 3600)),
        ("ds_bonus", dict(ship_id=1, bonus_id=1, value=1.5)),
        ("ds_log", dict(mission_id=ds_mission, started_at=T)),
        ("event_last", dict(id=1, mission_id=event_mission, area_id=event_area)),
        ("event_rank_score", dict(ranking_id=ranking, group_id=ranking_group, score=100, roles="%d,%d," % (role_a, role_b), created_at=T,
                                  fresh=1)),
        ("event_rank_received", dict(group_id=ranking_group, received_at=T)),
        ("favor_bonus_state", dict(id=1, day_at=DAY, bonus_id=0, lot_uid=uid_a, healed_at=0)),
        ("favor_drop_play", dict(same_role_id=same_a, lots=1)),
        ("follow_rental", dict(day=DAY, count=1, paid=0)),
        ("gear", dict(uid=1, master_gear_id=1, data="")),
        ("mission", dict(mission_id=mission, cleared=1, best_rank=0, play_count=1, clear_count=1, first_clear_at=T)),
        ("play", dict(id=1, mission_id=mission, party_id=1, started_at=T, stamina_cost=5, uids="%d,%d," % (uid_a, uid_b))),
        ("play_ext", dict(id=1, mission_type=0, surprise=0, helper_uid=0, helper_kind=0, npc_id=0, campaign_lots=0)),
        ("premium_pass", dict(id=one(m, "select min(id) from master_premium_login_bonus"), granted_at=T, day=1, last_at=T)),
        ("roster_ext", dict(uid=uid_a, add_hp=5, add_attack=1, add_intelligence=0, add_defence=0, add_hit=0, add_guard=0, add_ap=0,
                            equip_skill1=0, equip_skill2=0, equip_skill3=0)),
        ("shop_counts", dict(id=one(m, "select min(id) from master_item_shop"), num=1, period=0, total=1)),
        ("exchange_counts", dict(id=contents, shop_id=ex_shop, num=1)),
        ("sphere", dict(id=1, season_id=season, floor_level=1, stamina=5, stamina_at=T, entered_at=T)),
        ("sphere_box", dict(id=1, floor_level=1, rank=1)),
        ("sphere_cell", dict(asset_id=one(m, "select min(id) from master_sphere211_floor_asset"), floor_level=1, mission_box_id=0,
                             mission_id=0, overwrite_enemy_level=0, cleared=0, playing=0, created_at=T, updated_at=T)),
        ("sphere_departed", dict(uid=uid_b)),
        ("sphere_log", dict(id=1, kind=1, value=1, at=T)),
        ("sphere_meta", dict(key="cycle", value=1)),
        ("sphere_rank", dict(season_id=season, floor_level=1, entered_at=T)),
        ("sphere_rental", dict(follow_player_id=0x7D000001, used=1, updated_at=T)),
        ("sphere_rental_day", dict(day=DAY, season_id=season, count=1, paid=0)),
        ("stepup", dict(head=stepup_head, try_count=1, restart_count=0, next_id=stepup_head)),
        ("stock", dict(master_item_id=stack_item, item_type=stack_type, count=5)),
        ("unlocks", dict(mission_id=mission2, mission_type=0, by_mission=mission, at=T)),
        ("view_flags", dict(kind=0, flags=0)),
        ("wboss", dict(boss_id=one(m, "select min(id) from master_world_boss"), area_id=event_area, wave=1, wave_started_at=T)),
        ("wboss_clear", dict(boss_id=one(m, "select min(id) from master_world_boss"), wave=1, cleared_at=T, notified=0)),
    ]
    for table, cols in fill:
        if count(table) == 0:
            insert(table, **cols)

    # ---- (3) the dirt ------------------------------------------------------------------------------
    # favor: event_drop_at both '' and a time string
    db.execute("delete from favor")
    insert("favor", same_role_id=same_a, point=100, tap_count=1, tapped_at=T, event_drop_at="")
    insert("favor", same_role_id=same_b, point=0, tap_count=0, tapped_at=0, event_drop_at="2026-10-01 04:00:00")
    # a roster.weapon_uid naming a missing item
    db.execute("update roster set weapon_uid = ? where uid = ?", (MISSING_ITEM, uid_b))
    # a party_member.weapon_uid naming a sold weapon, and a gear attached to it
    sold = one(db, "select max(uid) from items where item_type = 1")
    db.execute("delete from items where uid = ?", (sold,))
    db.execute("update party_member set weapon_uid = ? where rowid = (select min(rowid) from party_member)", (sold,))
    insert("gear_items", uid=0x7C0FFFFF, type=0, master_item_id=one(db, "select master_item_id from gear_items limit 1"), param2=0,
           item_uid=sold, slot=0, is_new=0, created_at=T)
    # an orphan roster_ext row
    insert("roster_ext", uid=ORPHAN_UID, add_hp=1, add_attack=0, add_intelligence=0, add_defence=0, add_hit=0, add_guard=0, add_ap=0,
           equip_skill1=0, equip_skill2=0, equip_skill3=0)
    # meta view_status all ones (the seed's), checked
    assert one(db, "select value from meta where key = 'view_status'") == "18446744073709551615"
    # a titles.got_at = 0
    db.execute("update titles set got_at = 0 where id = (select min(id) from titles)")
    # player.party_id = 1 with no party_set row
    db.execute("update player set party_id = 1")
    db.execute("delete from party_set where party_id = 1")
    # wire_device with player_id 0 (a device seen before the player existed)
    insert("wire_device", uuid="00000000-0000-4000-8000-000000000001", player_id=0, device_type=1, first_seen=T, last_seen=T)
    db.commit()

    empty = [t for (t,) in db.execute("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence'") if count(t) == 0]
    if empty:
        sys.exit("make_state_fixture: tables still empty: %s" % ", ".join(empty))

    # ---- the dump ---------------------------------------------------------------------------------
    out = ["-- The v0 state fixture (server/PLAN-schema.md 4.2): written by tools/make_state_fixture.py, do not edit.",
           "-- user_version 0 (the default); every table's CREATE text as a pre-S1 server stored it.", "begin;"]
    tables = [r for r in db.execute("select name, sql from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name")]
    for name, sql in tables:
        out.append(sql + ";")
    for (sql,) in db.execute("select sql from sqlite_master where type = 'index' and sql is not null order by name"):
        out.append(sql + ";")
    for name, _ in tables:
        cols = [r[1] for r in db.execute('pragma table_info("%s")' % name)]
        for row in db.execute('select * from "%s" order by %s' % (name, ", ".join('"%s"' % c for c in cols))):
            out.append('insert into %s (%s) values (%s);' % (name, ", ".join(cols), ", ".join(literal(v) for v in row)))
    out.append("commit;")
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    with open(a.out, "w", encoding="utf-8") as f:
        f.write("\n".join(out) + "\n")
    rows = sum(1 for line in out if line.startswith("insert "))
    print("make_state_fixture: %d tables, %d rows -> %s" % (len(tables), rows, os.path.relpath(a.out, ROOT)))


if __name__ == "__main__":
    main()
