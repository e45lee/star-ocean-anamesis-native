"""Session `tower`: the tower (試練の遺跡), opened by the opt-in --restore-tower (3.7.0 had it closed;
server/src/api/tower/tower.cpp, port/src/native/restore/restore_tower.cpp, docs/client-changes.md
"Tower"). From the title through the real UI:

  title -> home -> スフィア211 button (phase 5: CExtraDungeonMenu, now two parts) -> 試練の遺跡
  (CTowerMissionMenu) -> the floor list (the open tower areas; the server lists them, the client
  master has stand-in banner rows for the five permanent areas) -> the top area -> its 1st floor
  -> detail -> single play -> 選択しない -> party 1 -> battle (MissionStart / MissionEnd of a
  master_tower_mission row) -> result pages -> the floor's list again: 1F CLEAR, 2F New.
  Then 戻る -> the floor list -> 戻る (the extra-dungeon menu).

Every step waits for its log line, then screenshots (<out>/shots); the cleared floor in the state
(OUT/state.txt). About 5 minutes.
Usage: port/scripts/tower_session.sh <soa> <out-dir> <scratch-dir> [soa flags...]   (from any directory)
The extra flags go to soa, e.g. --live-check restore (the native CCocosNode::SearchByName).
Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1. Ends with "PASS tower_session" or
"FAIL tower_session (N)" (exit 1).
Targets: port-inproc (--restore-tower's client changes are the port's)."""
import os
import re
import sqlite3

from ..flows import mission
from ..proc import repo_file
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "--restore-tower's client changes are port natives"
WRAPPER = "port/scripts/tower_session.sh"
P5 = mission.phase(5)


def options(ap):
    common.port_options(ap)


def main(o):
    s = common.port_run(o, common.port_config(o, ["--restore-tower"], limit=2100))

    def body(s):
        common.port_login(s, "01-title", "02-notice", "03-login-bonus", "04-home")
        line = s.last_line(r"server: tower: [0-9]+ areas")
        if line:
            print("  " + line)
        s.check("stand-in banners in the client master", s.in_client(r"tower: stand-in banner banner80"))
        # The home's スフィア211 button: with the tower open, the extra-dungeon menu lists 試練の遺跡 and スフィア211.
        s.tap_log(P5, 60, 20, 3, "tap:455:1085", name="extra-dungeon", fatal=False)
        s.ctl("wait:6000", s.shot_cmd("05-extra-dungeon"))
        # 試練の遺跡: the floor list (CTowerMissionMenu::Setup; the play_plate stand-ins are made here).
        s.ctl("tap:364:470", "wait:8000", s.shot_cmd("06-floors"))
        s.wait_log(r"layout node 'play_plate/3' missing", 30, name="tower menu (play_plate stand-ins)", fatal=False)
        s.ctl("tap:364:400", "wait:6000", s.shot_cmd("07-area"))  # the top area -> its missions (1F only)
        s.ctl("tap:364:415", "wait:4000", s.shot_cmd("08-detail"))
        # single play -> 選択しない -> party 1 -> ミッション開始 -> 決定
        s.ctl("tap:364:905", "wait:5000", s.shot_cmd("09-helper"), "tap:628:1120", "wait:5000", s.shot_cmd("10-party"))
        started = r"MissionStart mission [0-9]* \(master_tower_mission\)"
        mission.open_mission_confirm(s)
        s.ctl(s.shot_cmd("11-confirm"))
        mission.start_mission(s, "ミッション開始 -> 決定 (the start)", mission.log_more(s.client_log, started), opened=True)
        s.wait_log(started, 60, name="tower MissionStart", fatal=False)
        s.ctl("wait:12000", s.shot_cmd("12-battle"))
        s.wait_log(r"MissionEnd mission [0-9]*: player exp", 400, name="tower battle won", fatal=False)
        s.wait_log(r"MissionEnd mission [0-9]*: unlocked", 10, name="next floor unlocked", fatal=False)
        s.wait_log(r"server: tower: [0-9]+ areas, [0-9]+ missions listed", 10, name="lists refreshed", fatal=False)
        s.ctl("wait:6000", s.shot_cmd("13-result"))
        # the result pages (OK at 510:1050), each tap only while the tower menu isn't back (phase 5)
        mission.results_until(s, P5, 0, 15, 0, fmt=None, name="result pages", fatal=False, ok="510:1050")
        s.ctl("wait:8000", s.shot_cmd("14-area-after"))
        s.ctl("tap:100:1120", "wait:5000", s.shot_cmd("15-floors-again"), "tap:100:1120", "wait:5000", s.shot_cmd("16-back"))

    common.drive(s, body)
    # The server's state: the cleared floor
    out = []
    if os.path.exists(s.state_db):
        c = sqlite3.connect(s.state_db)
        m = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
        for (mid,) in c.execute("select mission_id from mission where cleared = 1"):
            r = m.execute("select id_label, master_tower_area_id from master_tower_mission where id = ?", (mid,)).fetchone()
            if r:
                out.append("tower mission cleared: %s (area %s)" % r)
    print("\n".join(out))
    with open(os.path.join(o.out, "state.txt"), "w") as f:
        f.write("\n".join(out) + ("\n" if out else ""))
    s.check("a tower mission cleared in the state DB", any(x.startswith("tower mission cleared") for x in out))
    return common.counted(s, "tower_session")
