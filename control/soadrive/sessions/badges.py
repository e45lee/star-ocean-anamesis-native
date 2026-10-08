"""Session `badges`: the NEW badges (docs/unimplemented-apis.md part 3 step 6; the server's
roster.is_new, ClearNewCharacter): title -> Login -> home -> a 10-draw (the shared gacha flow; the
seeded player gets new characters) -> キャラクター -> 装備・技・アシスト変更: the new characters show
NEW (shot) -> 戻る sends ClearNewCharacter (the server's line `ClearNewCharacter: N character(s)`,
the state's new characters cleared) -> the list again without NEW (shot); then a second boot on the
same phone and state: Login, the list again, and the state still has no new character. Shots go to
OUT/shots, the logs to OUT/log.txt and OUT/log-relogin.txt. Ends with PASS (exit 0) or FAIL (exit 1).

Usage: port/scripts/badges_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SEED_RNG, WATCH=1.
Targets: port-inproc (default), port-server (the port's phase lines; the state DB read directly)."""
import sqlite3

from ..flows import gacha
from . import common

TARGETS = ("port-inproc", "port-server")
TARGETS_WHY = "it waits on the port's phase lines (the character menu)"
WRAPPER = "port/scripts/badges_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def new_characters(s):
    """The state's characters flagged new (roster.is_new = 1), read-only."""
    db = sqlite3.connect("file:%s?mode=ro" % s.state_db, uri=True)
    try:
        return db.execute("select count(*) from roster where is_new = 1").fetchone()[0]
    finally:
        db.close()


def character_list(s, shot):
    """キャラクター -> 装備・技・アシスト変更: the character list."""
    common.settle(s, mask=common.HOME_MASK)
    common.tap_to_phase(s, "キャラクター -> the character menu", "180:1245", 11, mask=common.HOME_MASK, fatal=True)
    common.tap_to_screen(s, "装備・技・アシスト変更", "364:435", shot)


def main(o):
    s = common.port_run(o, common.port_config(o, limit=2400))
    counts = {}

    def body(s):
        common.port_login(s, notice=None, bonus=None)
        st1 = s.state("1-home")
        gacha.ten_draw(s, st1)
        counts["drawn"] = new_characters(s)
        s.check("new characters after the draw (%d)" % counts["drawn"], counts["drawn"] > 0)
        character_list(s, "20-list-new")
        common.tap_to_server(s, "戻る -> ClearNewCharacter", r"ClearNewCharacter: [1-9][0-9]* character\(s\)", ["tap:100:1120"], secs=60)
        common.tap_to_screen(s, "装備・技・アシスト変更", "364:435", "21-list-cleared")
        counts["cleared"] = new_characters(s)
        s.check("no new character after ClearNewCharacter (%d)" % counts["cleared"], counts["cleared"] == 0)

    if not common.drive(s, body):
        return 1
    s2 = common.port_run_again(o, common.port_config(o, limit=1800), "log-relogin.txt")

    def body2(s2):
        common.port_login(s2, title="30-title", notice=None, bonus=None, home="31-home")
        character_list(s2, "32-list-relogin")
        counts["relogin"] = new_characters(s2)
        s2.check("still no new character after a re-login (%d)" % counts["relogin"], counts["relogin"] == 0)

    if not common.drive(s2, body2):
        return 1
    fails = common.common_log_checks(s) + common.common_log_checks(s2)
    return common.verdict(s, fails if not s2.failed else fails + ["the re-login boot failed"],
                          "NEW badges: %s new characters drawn, cleared by ClearNewCharacter, still cleared after a re-login"
                          % counts.get("drawn"))
