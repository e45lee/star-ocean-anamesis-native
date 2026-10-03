"""Print the local server's state (soa's in-process server or soa-server): DATA/server.sqlite3.

    tools/server_state.py DATA/server.sqlite3 [--db data/basmaster-3.7.0.sqlite3]

Shows the player (level, EXP, FOL, stamina, coins), party 1 with its members' levels and EXP,
the stack items and unique items owned, mission progress, the gacha history and the present
box. Used by port/scripts/restore_session.sh and restore_missions.sh for the before/after dumps.
"""
import argparse
import os
import sqlite3


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("state")
    ap.add_argument("--db", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "work", "..", "data",
                                                 "basmaster-3.7.0.sqlite3"))
    a = ap.parse_args()
    st = sqlite3.connect("file:%s?mode=ro" % a.state, uri=True)
    m = sqlite3.connect("file:%s?mode=ro" % a.db, uri=True) if os.path.exists(a.db) else None

    def label(table, i):
        if not m:
            return str(i)
        r = m.execute("select id_label from %s where id = ?" % table, (i,)).fetchone()
        return r[0] if r else str(i)

    p = st.execute("select id, search_id, name, level, exp, fol, stamina, free_coin, pay_coin from player").fetchone()
    print("player %s (%s, id %d): level %d exp %d fol %d stamina %d coins free %d paid %d" %
          (p[1], p[2], p[0], p[3], p[4], p[5], p[6], p[7], p[8]))
    n = st.execute("select count(*) from roster").fetchone()[0]
    print("roster: %d characters" % n)
    def favor(role):
        """The character's favor points: the favor table keys them by the master's same_role_id (0
        without a row, or without the master)."""
        same = m.execute("select same_role_id from master_role where id = ?", (role,)).fetchone() if m else None
        try:
            r = st.execute("select point from favor where same_role_id = ?", (same[0],)).fetchone() if same else None
        except sqlite3.OperationalError:  # a state from before the favor table
            r = None
        return r[0] if r and r[0] is not None else 0

    for slot, uid, role, lv, exp, lb in st.execute(
            "select p.slot, p.uid, r.role_id, r.level, r.exp, r.limit_break from party p "
            "join roster r on r.uid = p.uid where p.party_id = 1 order by p.slot"):
        fav = favor(role)
        print("  party 1 slot %d: %#x %s level %d exp %d favor %d limit break %d" % (slot, uid, label("master_role", role), lv, exp, fav, lb))
    for mid, cnt in st.execute("select master_item_id, count from stock where count > 0 order by master_item_id"):
        print("  stock %s x%d" % (label("master_item", mid), cnt))
    for uid, mid in st.execute("select uid, master_item_id from items order by uid"):
        print("  item %#x %s" % (uid, label("master_item", mid)))
    for mid, cl, pc, cc in st.execute("select mission_id, cleared, play_count, clear_count from mission"):
        print("  mission %s: cleared %d, played %d, cleared %d times" % (label("master_mission", mid), cl, pc, cc))
    for gid, role, uid, rank, dup, cf, cp in st.execute(
            "select gacha_id, role_id, uid, rank, duplicate, cost_free, cost_pay from gacha_history order by id"):
        print("  gacha %s: %s %s uid %#x%s%s" % (label("master_gacha", gid), rank, label("master_role", role), uid,
                                                 " (duplicate)" if dup else "", " cost %d free + %d paid" % (cf, cp) if cf or cp else ""))
    n = st.execute("select count(*) from presents where received_at is null").fetchone()[0]
    print("present box: %d" % n)
    tables = {r[0] for r in st.execute("select name from sqlite_master where type = 'table'")}
    if "unlocks" in tables:
        for mid, t, by in st.execute("select mission_id, mission_type, by_mission from unlocks order by at, mission_id"):
            tab = {0: "master_mission", 1: "master_event_mission", 3: "master_world_map_mission"}.get(t, "master_mission")
            print("  unlocked %s (by %s)" % (label(tab, mid), label(tab, by)))
    if "stepup" in tables:
        for head, tries, restarts, nxt in st.execute("select head, try_count, restart_count, next_id from stepup order by head"):
            print("  step-up %s: %d draws, %d restarts, next %s" % (label("master_gacha", head), tries, restarts, label("master_gacha", nxt)))
    if "box_state" in tables:
        for gid, total, resets in st.execute("select gacha_id, total_count, reset_count from box_state order by gacha_id"):
            print("  box %s: %d drawn, %d resets" % (label("master_gacha", gid), total, resets))


if __name__ == "__main__":
    main()
