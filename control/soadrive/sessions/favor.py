"""Session `favor`: favorability in the restored game (the in-process local server;
docs/server-rules.md section 8, docs/client-changes.md "Favorability"): boot once so the local
server seeds itself, give the owned characters favor points in the server DB (test setup: the home
character 9,900 points, one tap short of level 2; the others spread over levels 1..4), boot again,
then home (favor heart, level 1) -> two taps on the home character (UpdateFavorByTap, +50 each: the
second crosses 10,000 and plays the rank-up; the heart becomes level 2) -> a battle (mf01_001
through the `mission:` / `phase:0xf` route: MissionEnd adds favor) -> the result screens -> home.
Screenshots go to OUT/shots, the log to OUT/log.txt, the favor table to OUT/favor-*.txt.
Ends with PASS (exit 0) or FAIL (exit 1).

Usage: port/scripts/restore_favor_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SOA_PHONE (scripts/shared-phone.sh), FLOW_MISSION, SEED_RNG, WATCH=1.
Targets: port-inproc (the `mission:` / `phase:` shortcut, the in-process server's favor lines)."""
import os
import re
import sqlite3

from ..flows import mission
from ..proc import repo_file
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it enters the battle through the port's `mission:` / `phase:0xf` control commands"
WRAPPER = "port/scripts/restore_favor_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def favor(s, tag):
    c = sqlite3.connect(s.state_db)
    rows = ["%s %s %s" % r for r in c.execute("select same_role_id, point, tap_count from favor order by same_role_id")]
    c.close()
    with open(os.path.join(s.layout.state_dir, "favor-%s.txt" % tag), "w") as f:
        f.write("\n".join(rows) + ("\n" if rows else ""))
    return {r.split()[0]: r.split()[1] for r in rows}


def setup(db):
    """Favor points per same role (the home character's: 9,900)."""
    s, m = sqlite3.connect(db), sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
    s.execute("pragma foreign_keys = on")  # PLAN-schema S1: every connection that writes the state
    home = s.execute("select r.role_id from player p join roster r on r.uid = p.home_uid").fetchone()[0]
    home_same = m.execute("select same_role_id from master_role where id = ?", (home,)).fetchone()[0]
    sames = sorted({m.execute("select same_role_id from master_role where id = ?", (r,)).fetchone()[0]
                    for (r,) in s.execute("select distinct role_id from roster")})
    sames = [x for x in sames if m.execute("select 1 from master_favor_schedule where id = ?", (x,)).fetchone()]
    pts = [0, 5000, 10000, 20000, 30000, 45000, 60000, 80000]
    for i, x in enumerate(sames):
        s.execute("insert into favor (same_role_id, point, tap_count, tapped_at, event_drop_at) values (?, ?, 0, null, null) "
                  "on conflict(same_role_id) do update set point = excluded.point, tap_count = excluded.tap_count, "
                  "tapped_at = excluded.tapped_at, event_drop_at = excluded.event_drop_at",
                  (x, 9900 if x == home_same else pts[i % len(pts)]))
    s.commit()


def main(o):
    m = os.environ.get("FLOW_MISSION") or "mf01_001"
    for f in os.listdir(o.out) if os.path.isdir(o.out) else ():
        if f.startswith("favor-") and f.endswith(".txt"):
            os.remove(os.path.join(o.out, f))
    # 1. First boot: the server seeds its state from data/saves/seed/Game.xml.
    s1 = common.port_run(o, common.port_config(o, limit=2400))
    if not common.drive(s1, lambda s: common.port_login(s, home=None, notice=None, bonus=None, bonus_wait=20)):
        return 1
    # 2. Test setup: favor points per same role (the home character's first).
    setup(s1.state_db)
    tables = {"0-setup": favor(s1, "0-setup")}
    # 3. Second boot: home, taps, battle.
    s = common.port_run_again(o, common.port_config(o, limit=2400), "log.txt")

    def body(s):
        common.port_login(s, home=None, notice=None, bonus=None, bonus_wait=20)
        s.ctl("wait:8000", s.shot_cmd("02-home-level1"))
        # A character with favor can visit the home instead of the home character (its お気に入りに
        # 戻す button at 90:635 brings the home character back; on the home character's home the spot
        # is empty). Taps on a visitor send nothing.
        s.ctl("tap:90:635", "wait:6000")
        s.tap_log(r"favor: tap same_role [0-9]* \+50: 9900 -> 9950", 40, 10, 3, "tap:420:560",
                  name="the first tap on the home character (UpdateFavorByTap)")
        s.ctl("wait:6000", s.shot_cmd("03-tap-9950"))
        s.tap_log(r"favor: tap same_role [0-9]* \+50: 9950 -> 10000 \(level 1 -> 2\)", 40, 10, 3, "tap:420:560",
                  name="the second tap reaches level 2")
        s.ctl("wait:1500", s.shot_cmd("04-levelup"), "wait:6500", s.shot_cmd("05-level2"))
        tables["1-after-taps"] = favor(s, "1-after-taps")
        mission.port_start(s, m)
        mission.battle_shots(s, 10, 70, 4000)
        s.wait_log(r"mission_end\.msgp", 30, name="the battle ended (MissionEnd)")
        s.ctl("wait:4000", s.shot_cmd("80-result"))
        mission.results_until(s, mission.phase(4), 81, 95, 1000, name="the result pages -> home")
        s.ctl("wait:8000", s.shot_cmd("99-home"))
        tables["2-after-battle"] = favor(s, "2-after-battle")
        for ln in open(s.client_log, errors="replace").read().splitlines():
            if "favor:" in ln:
                print(ln)

    if not common.drive(s, body):
        return 1
    home = common.state_value(open(s.client_log, errors="replace").read(), r"favor: tap same_role ([0-9]+)", str)
    p = lambda tag: tables.get(tag, {}).get(home)
    print("home character (same_role %s): %s -> %s after the taps -> %s after the battle" % (home, p("0-setup"), p("1-after-taps"),
                                                                                          p("2-after-battle")))
    fails = common.checks(
        (p("0-setup") == "9900", "the setup didn't give the home character 9900 points"),
        (p("1-after-taps") == "10000", "two taps didn't add 100 points"),
        (s.in_client(r"favor: mission \(stamina [0-9]*\) same_role"), "MissionEnd added no favor"),
    ) + common.common_log_checks(s, crash=False)
    return common.verdict(s, fails, "favor taps (level 1 -> 2 with the rank-up), favor from a battle")
