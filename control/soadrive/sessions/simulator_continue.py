"""Session `simulator-continue`: the battle simulator and a lost battle's continue (the local server:
server/src/api/missions/; docs/server-rules.md#battle-simulator, #failure-continue-restart).
Boot 1: title -> Login -> home -> キャラクター -> バトルシミュレーター -> the rental list's 選択しない ->
the party (party 1) -> ミッション開始 -> 決定 (TrainingMissionStart: the simulator's mission with the
current party, no play record) -> the battle -> the pause menu's シミュレーター終了 -> はい (nothing
sent) -> the character menu. Then a lost battle: test setup in the server DB (party 1 reduced to its
first member with HP 10, attack and intelligence 1: tools of this session, not game rules; the
member's other slots emptied), mf01_001 through the port's `mission:` / `phase:0xf` shortcut, the
member falls -> the defeat dialog "紋章石100個を使用することで全員が復活できます" -> はい
(MissionContinue 1: 100 coins) -> the battle goes on, the member falls again -> いいえ -> 本当に
リタイアしますか? はい (MissionContinue 0, MissionFailed). The test setup is undone. Boot 2 (the
same phone): Login -> home; the coins stay 100 down and no play is in progress.
Screenshots in OUT/shots, the logs OUT/log.txt and OUT/log-relogin.txt, the server state
OUT/state-*.txt. Ends with PASS (exit 0) or FAIL (exit 1). About 8 minutes.

Usage: port/scripts/simulator_continue_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
Targets: port-inproc (default), port-server (the server's lines are read from soa-server's log; the
`mission:` shortcut and the phase lines are the client's, so both have them)."""
import os
import sqlite3

from .. import popups
from ..flows import mission
from ..proc import repo_file
from . import common

TARGETS = ("port-inproc", "port-server")
WRAPPER = "port/scripts/simulator_continue_session.sh"

CHARACTER = "180:1245"     # the footer's キャラクター
SIMULATOR = "364:860"      # the character menu (scrolled to its end): バトルシミュレーター
RENTAL_NONE = "620:1120"   # the rental list: 選択しない
PAUSE = "80:50"            # the battle's pause button
SIM_END = "364:455"        # the simulator's pause menu: シミュレーター終了
SIM_END_YES = "525:790"    # シミュレーターを終了し…よろしいですか? はい
CONTINUE_YES = "525:790"   # the defeat dialog: はい
CONTINUE_NO = "200:790"    # the defeat dialog: いいえ
RETIRE_YES = "525:713"     # 本当にリタイアしますか? はい
STATS = ("hp", 10), ("attack", 1), ("intelligence", 1)


def options(ap):
    common.port_options(ap, extra=False)


def weaken(db):
    """Test setup: party 1's first member alone, at HP 10 and attack / intelligence 1 (its seeds,
    roster add_*, set to reach those stats as server/src/api/player/person_status.cpp computes them).
    Returns what to restore."""
    s = sqlite3.connect(db, timeout=60)
    m = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
    s.execute("pragma foreign_keys = on")  # PLAN-schema S1: every connection that writes the state
    party = s.execute("select ifnull(party_id, 1) from player").fetchone()[0]
    slots = s.execute("select slot, uid from party_member where party_id = ? order by slot", (party,)).fetchall()
    uid = slots[0][1]
    role, level, lb = s.execute("select role_id, level, limit_break from roster where uid = ?", (uid,)).fetchone()
    saved = s.execute("select add_hp, add_attack, add_intelligence from roster where uid = ?", (uid,)).fetchone()
    for stat, want in STATS:
        base = m.execute("select %s from master_character_common_parameter where level = ?" % stat, (level,)).fetchone()[0]
        rv, rank = m.execute("select %s, rank from master_role where id = ?" % stat, (role,)).fetchone()
        pct = (m.execute("select %s from master_rank where rank = ? and limit_break = ?" % stat, (rank, lb)).fetchone() or (100,))[0]
        v = round(round(rv * base / 100.0) * pct / 100.0)
        s.execute("update roster set add_%s = ? where uid = ?" % stat, (want - v, uid))
    s.execute("update party_member set uid = null where party_id = ? and slot > ?", (party, slots[0][0]))
    s.commit()
    s.close()
    return party, slots, uid, saved


def restore(db, setup):
    party, slots, uid, saved = setup
    s = sqlite3.connect(db, timeout=60)
    s.execute("pragma foreign_keys = on")
    s.execute("update roster set add_hp = ?, add_attack = ?, add_intelligence = ? where uid = ?", tuple(saved) + (uid,))
    for slot, member in slots:
        s.execute("update party_member set uid = ? where party_id = ? and slot = ?", (member, party, slot))
    s.commit()
    s.close()


def play_rows(db):
    c = sqlite3.connect(db, timeout=60)
    n = c.execute("select count(*) from play").fetchone()[0]
    c.close()
    return n


def coins(text):
    return common.state_value(text, r"coins free ([0-9]+)")


def main(o):
    s = common.port_run(o, common.port_config(o, limit=2400))
    c = s.ctl
    got = {}

    def body(s):
        common.port_login(s, notice=None, bonus=None)
        got["coins0"] = coins(s.state("1-home"))
        # ---- the battle simulator
        common.settle(s, mask=common.HOME_MASK)
        common.tap_to_phase(s, "キャラクター -> the character menu", CHARACTER, 11, secs=120, mask=common.HOME_MASK, fatal=True)
        for _ in range(2):
            c("drag:364:900:364:300")
            common.settle(s)
        common.settle(s, "03-character-menu-end")
        common.tap_to_screen(s, "バトルシミュレーター", SIMULATOR, "04-simulator-rental")
        common.tap_to_screen(s, "選択しない -> the party", RENTAL_NONE, "05-simulator-party", is_screen=popups.is_party_start)
        mission.open_mission_confirm(s)
        c(s.shot_cmd("06-simulator-confirm"))
        mission.start_mission(s, "決定 -> TrainingMissionStart", lambda: s.in_server(r"TrainingMissionStart: mission [0-9]+, no play record"),
                              opened=True)
        s.check("the simulator fights with party 1", s.in_server(r"MissionStart mission [0-9]+ \(master_training_mission\) party 1 "))
        s.check("no stamina for the simulator", s.in_server(r"\(master_training_mission\) .*stamina ([0-9]+) -> \1\b"))
        s.check("no play record after the simulator's start", play_rows(s.state_db) == 0)
        s.wait_log(mission.phase(15), 120, name="the simulator's battle (CPhase_Battle)")
        # a fixed wait: a picture of the fight, nothing to wait for; the pause then stops it (a still screen)
        c("wait:15000", s.shot_cmd("07-simulator-battle"))
        common.tap_to_screen(s, "the pause button", PAUSE, "08-simulator-pause")
        common.tap_to_screen(s, "シミュレーター終了", SIM_END, "09-simulator-end")
        common.tap_to_log(s, "シミュレーター終了 -> the character menu", SIM_END_YES, mission.phase(11), "10-character-menu-again", secs=90,
                          tries=1, fatal=True)
        # ---- a lost battle: the test setup, mf01_001, the defeat dialog twice
        got["setup"] = weaken(s.state_db)
        # the mission type back to the story's (CParameterUI+0x140: the simulator left 4 there, and
        # CStageManager::InitializeMissionData then looks mf01_001 up as a simulator mission)
        c("uiset:0x140:0")
        mission.port_start(s, "mf01_001")
        s.tap_until("the defeat dialog's はい -> MissionContinue 1 (100 coins)", 300, CONTINUE_YES,
                    lambda: s.in_server(r"MissionContinue: mission [0-9]+ continued for 100 coins"), every=8)
        # a fixed wait: a picture of the fight going on (a battle never holds still)
        c("wait:3000", s.shot_cmd("11-continued"))
        got["coins1"] = coins(s.state("2-continued"))
        s.check("the play stays open across the continue", play_rows(s.state_db) == 1)

        def decline():
            c("tap:" + CONTINUE_NO, "wait:2500", "tap:" + RETIRE_YES)

        s._wait("the defeat dialog's いいえ -> retire (MissionContinue 0, MissionFailed)", 300,
                lambda: s.in_server(r"MissionContinue: declined") and s.in_packets(r"> MissionFailed "), True, action=decline, every=8)
        common.settle(s, "12-retired", hold=2)
        restore(s.state_db, got.pop("setup"))
        got["coins2"] = coins(s.state("3-retired"))

    if not common.drive(s, body):
        if "setup" in got:
            restore(s.state_db, got["setup"])
        return 1
    # ---- boot 2: the re-login keeps the coins, nothing to resume
    s2 = common.port_run_again(o, common.port_config(o, limit=2400), "log-relogin.txt")

    def again(s2):
        common.port_login(s2, title="20-title", notice=None, bonus=None, home="21-home")
        got["coins3"] = coins(s2.state("4-relogin"))
        s2.check("no play in progress after the re-login", play_rows(s2.state_db) == 0)

    if not common.drive(s2, again):
        return 1
    c0, c1, c2, c3 = (got.get(k) for k in ("coins0", "coins1", "coins2", "coins3"))
    print("free coins: %s at home -> %s after the continue -> %s after the retire -> %s after the re-login" % (c0, c1, c2, c3))
    fails = common.checks(
        (c0 is not None and c1 == c0 - 100, "the continue didn't take 100 coins"),
        (c2 == c1, "the decline took coins"),
        (c3 == c1, "the coins changed across the re-login"),
        (s.in_packets(r"> TrainingMissionStart .*args: [0-9]+ 1 0"), "no TrainingMissionStart(mission, 1, 0) in the packet log"),
    ) + common.common_log_checks(s)
    return common.verdict(s2, fails, "the simulator with party 1 (no stamina, no play record) and ended; a lost battle continued for 100 "
                          "coins and retired; the coins and the closed play kept across a re-login")
