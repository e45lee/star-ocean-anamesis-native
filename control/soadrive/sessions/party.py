"""Session `party`: the restored party screen (the in-process local server): boot -> home -> the
footer's Character menu (3.7.0 CPartyComposition) -> Party (party set 1) -> Change members -> slot
1 := the 6th character of the list (sorted by rarity) -> Back, which saves the set with
UpdatePartySet -> swipe to set 2, change and save it too -> home -> a battle (mf01_001 through the
`mission:` / `phase:0xf` route) whose MissionStart takes the set saved last (set 2). Also changes the
home character (お気に入り, UpdateHome). Screenshots go to OUT/shots, the server's party table to
OUT/state-*.txt, the log to OUT/log.txt. Checks that the saved set reaches MissionStart; exit
status 1 if not.

Usage: port/scripts/party_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SOA_PHONE (scripts/shared-phone.sh), FLOW_MISSION, SEED_RNG, WATCH=1.
Targets: port-inproc (the `mission:` / `phase:` shortcut, the phase lines)."""
import os
import re
import sqlite3

from ..flows import mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it enters the battle through the port's `mission:` / `phase:0xf` control commands"
WRAPPER = "port/scripts/party_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def party(s, tag):
    """OUT/state-TAG.txt: the player's current party and every set's members (printed too)."""
    c = sqlite3.connect(s.state_db)
    lines = ["player.party_id %s" % c.execute("select party_id from player").fetchone()[0]]
    for r in c.execute("select p.party_id, p.slot, p.uid, r.role_id from party p left join roster r on r.uid = p.uid order by 1, 2"):
        lines.append("party " + " ".join(str(x) for x in r))
    c.close()
    text = "\n".join(lines) + "\n"
    with open(os.path.join(s.layout.state_dir, "state-%s.txt" % tag), "w") as f:
        f.write(text)
    print(text, end="", flush=True)
    return text


def main(o):
    m = os.environ.get("FLOW_MISSION") or "mf01_001"
    s = common.port_run(o, common.port_config(o, limit=2400))
    states = {}

    def body(s):
        common.port_login(s)
        states[1] = party(s, "1-boot")
        # Footer "キャラクター" -> CPhase_PartyComposition (0xb), the 3.7.0 character menu.
        s.tap_log(mission.phase(11), 120, 20, 3, "tap:180:1245", name="キャラクター -> the character menu")
        s.ctl("wait:6000", s.shot_cmd("03-character-menu"))
        s.ctl("tap:364:325", "wait:6000", s.shot_cmd("04-party-top"))  # パーティ編成: party set 1
        s.ctl("tap:620:1120", "wait:5000", s.shot_cmd("05-member-select"))  # メンバー変更
        # Slot 1, then the first character of the list's second row.
        s.ctl("tap:212:325", "wait:1500", "tap:95:725", "wait:2500", s.shot_cmd("06-member-changed"))
        # 戻る saves the set (UpdatePartySet) and returns to the party top.
        s.ctl("tap:100:1120")
        s.wait_log(r"UpdatePartySet: party 1 ", 30, name="UpdatePartySet: party 1")
        s.ctl("wait:4000", s.shot_cmd("07-party-saved"))
        states[2] = party(s, "2-saved")
        # Swipe to party set 2 (2/10), change its slot 1 to the second character of the list's second
        # row and save it: the last saved set becomes the current party.
        s.ctl("drag:600:600:150:600", "wait:3000", s.shot_cmd("08-party-2"))
        s.ctl("tap:620:1120", "wait:5000", "tap:212:325", "wait:1500", "tap:230:725", "wait:2500", s.shot_cmd("09-party-2-changed"))
        s.ctl("tap:100:1120")
        s.wait_log(r"UpdatePartySet: party 2 ", 30, name="UpdatePartySet: party 2")
        s.ctl("wait:4000", s.shot_cmd("10-party-2-saved"))
        states[3] = party(s, "3-saved-2")
        # 戻る to the character menu, footer ホーム.
        s.ctl("tap:100:1120", "wait:4000", s.shot_cmd("11-character-menu"))
        s.tap_log(mission.phase(4), 60, 20, 3, "tap:60:1245", name="ホーム -> home")
        s.ctl("wait:6000", s.shot_cmd("12-home"))
        # Home character: interactive mode -> お気に入り変更 (the restored 3.7.0 CAdjutantSelect) -> the
        # third one -> UpdateHome -> the home shows it.
        s.ctl("tap:90:740", "wait:5000", "tap:180:1245", "wait:5000", s.shot_cmd("12a-favorite-select"))
        s.ctl("tap:362:330")
        s.wait_log(r"UpdateHome: ", 30, name="UpdateHome")
        s.ctl("wait:3000", s.shot_cmd("12b-favorite-changed"), "tap:364:800", "wait:5000", s.shot_cmd("12c-home-new-favorite"))
        s.ctl("tap:60:1245", "wait:5000")
        # Battle: MissionStart takes the player's current party (the set just saved).
        mission.port_start(s, m)
        s.wait_log(r"MissionStart mission", 60, name="MissionStart")
        s.ctl("wait:25000", s.shot_cmd("13-battle"), "wait:8000", s.shot_cmd("14-battle"))

    if not common.drive(s, body):
        return 1
    slot0 = lambda text, k: common.state_value(text, r"^party %d 0 ([0-9]+) " % k, str)
    uid1, uid2 = slot0(states[3], 1), slot0(states[3], 2)
    cur = common.state_value(states[3], r"^player.party_id ([0-9]+)")
    print("saved: set 1 slot 0 uid %s, set 2 slot 0 uid %s, current set %s" % (uid1, uid2, cur))
    for ln in open(s.client_log, errors="replace").read().splitlines():
        if re.search(r"UpdatePartySet: party|MissionStart mission|MissionStart party member", ln):
            print(ln)
    fails = common.checks(
        (uid1 == slot0(states[2], 1), "set 1 changed"),
        (cur == 2, "current party is %s, not 2" % cur),
        (s.in_client(r"MissionStart party member 0: uid %s" % uid2), "MissionStart didn't use set 2 (uid %s)" % uid2))
    return common.verdict(s, fails, "the battle uses the saved party")
