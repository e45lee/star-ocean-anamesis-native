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
    # (party_member since PLAN-schema S6; an empty slot's NULL uid prints 0, as the party table's 0 did)
    for r in c.execute("select p.party_id, p.slot, ifnull(p.uid, 0), r.role_id from party_member p left join roster r on r.uid = p.uid "
                       "order by 1, 2"):
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

    def screen(name, xy, shot=None, **kw):
        return common.tap_to_screen(s, name, xy, shot, **kw)

    def saved(name, rx, shot):
        """戻る saves the set (UpdatePartySet; one tap: a second would leave the party top)."""
        common.tap_to_log(s, name, "100:1120", rx, shot, secs=30, tries=1, fatal=True)

    def body(s):
        common.port_login(s)
        common.settle(s, mask=common.HOME_MASK)
        states[1] = party(s, "1-boot")
        # Footer "キャラクター" -> CPhase_PartyComposition (0xb), the 3.7.0 character menu.
        common.tap_to_phase(s, "キャラクター -> the character menu", "180:1245", 11, "03-character-menu", secs=120,
                            mask=common.HOME_MASK, fatal=True)
        screen("パーティ編成: party set 1", "364:325", "04-party-top")
        screen("メンバー変更", "620:1120", "05-member-select")
        # Slot 1, then the first character of the list's second row (selections: no retap; the
        # saved set checks them)
        common.tap_settled(s, "212:325")
        common.tap_settled(s, "95:725", "06-member-changed")
        saved("UpdatePartySet: party 1", r"UpdatePartySet: party 1 ", "07-party-saved")
        states[2] = party(s, "2-saved")
        # Swipe to party set 2 (2/10), change its slot 1 to the second character of the list's second
        # row and save it: the last saved set becomes the current party.
        # (once: the sets after 1 show the same members, so only the 1/10 -> 2/10 changes, too little to
        # tell a lost swipe; UpdatePartySet: party 2 checks it)
        s.ctl("drag:600:600:150:600")
        common.settle(s, "08-party-2")
        screen("メンバー変更", "620:1120")
        common.tap_settled(s, "212:325")
        common.tap_settled(s, "230:725", "09-party-2-changed")
        saved("UpdatePartySet: party 2", r"UpdatePartySet: party 2 ", "10-party-2-saved")
        states[3] = party(s, "3-saved-2")
        # 戻る to the character menu, footer ホーム.
        screen("戻る -> the character menu", "100:1120", "11-character-menu")
        common.tap_to_phase(s, "ホーム -> home", "60:1245", 4, "12-home", mask=common.HOME_MASK, fatal=True)
        # Home character: interactive mode -> お気に入り変更 (the restored 3.7.0 CAdjutantSelect) -> the
        # third one -> UpdateHome -> the home shows it.
        screen("会話モード", "90:740", mask=common.HOME_MASK)
        screen("お気に入り変更", "180:1245", "12a-favorite-select")
        common.tap_to_log(s, "UpdateHome", "362:330", r"UpdateHome: ", "12b-favorite-changed", secs=30, tries=1, fatal=True)
        screen("閉じる", "364:800", "12c-home-new-favorite")
        screen("ホーム", "60:1245", mask=common.HOME_MASK)
        # Battle: MissionStart takes the player's current party (the set just saved).
        mission.port_start(s, m)
        s.wait_log(r"MissionStart mission", 60, name="MissionStart")
        # fixed waits: two pictures of the fight at about 25 and 33 s, nothing to wait for
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
