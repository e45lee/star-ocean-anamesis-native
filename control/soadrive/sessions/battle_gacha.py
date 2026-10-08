"""Session `battle-gacha`: end-to-end session of the restored online game (the in-process local server):
boot -> home -> a battle (mf01_001 through the `mission:` / `phase:0xf` route) -> the Mission Result
screens with the server's EXP, FOL and drops -> home -> the gacha screen (the footer's ガチャ) -> a
10-draw that debits 紋章石 -> the result -> home (the shared gacha flow). Prints "PASS: ..." at the
end, or "FAIL: ..." with exit status 1 (a step that isn't reached, the battle not cleared, no coins
debited or no draw recorded by the server). Screenshots at each step go to OUT/shots; the server's
state (tools/server_state.py) is dumped after boot, after the battle and after the draw
(OUT/state-*.txt), and the log is OUT/log.txt.

The phone: the shared pre-downloaded one, linked; SOA_PHONE=DIR another, SOA_PHONE=none an empty one.
Usage: port/scripts/restore_session.sh <soa> <out-dir> <scratch-dir> [soa flags...]   (from any directory)
The extra flags go to soa, e.g. --campaign-seed mf01_001 (emulator/README.md "Parity") or
--live-check FAMILY. The client save is the committed test save; the server seeds itself from
data/saves/seed/Game.xml into a fresh <scratch-dir>/data/server.sqlite3. --seed-rng (SEED_RNG,
default 1) fixes the server's RNG. FLOW_MISSION picks the battle (default mf01_001).
Targets: port-inproc (the battle's `mission:` / `phase:` shortcut)."""
import os
import re
import sys

from ..flows import gacha, mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it enters the battle through the port's `mission:` / `phase:0xf` control commands"
WRAPPER = "port/scripts/restore_session.sh"


def options(ap):
    common.port_options(ap)


def main(o):
    m = os.environ.get("FLOW_MISSION") or "mf01_001"
    s = common.port_run(o, common.port_config(o))
    show = lambda text: sys.stdout.write(text) and sys.stdout.flush()

    def body(s):
        common.port_login(s)
        show(s.state("1-boot"))
        # Battle: MissionStart (stamina, the party set's own characters) ... MissionEnd (EXP, FOL, drops).
        mission.port_start(s, m)
        # a fixed wait: a picture of the battle's loading screen, nothing to wait for
        s.ctl("wait:1500", s.shot_cmd("03-battle-loading"))
        mission.battle_shots(s, 10, 70, 4000)
        s.wait_log(r"mission_end\.msgp", 30, name="the battle ended (MissionEnd)")
        common.settle(s, "80-result", hold=2)
        common.settle(s, "81-result", hold=3)
        mission.results_until(s, mission.phase(4), 82, 95, 4000, name="the result pages -> home")
        common.settle(s, "99-home", mask=common.HOME_MASK)
        st2 = s.state("2-after-battle")
        show(st2)
        # Gacha: GetGachaInData (the banners open now, the wallet), then a 10-draw of the first
        # recommended banner, its presentation and result list, then home.
        st3 = gacha.ten_draw(s, st2)
        show(st3)

    if not common.drive(s, body):
        return 1
    st = lambda tag: open(os.path.join(o.out, "state-%s.txt" % tag)).read()
    c2 = common.state_value(st("2-after-battle"), r" coins free ([0-9]+) ")
    c3 = common.state_value(st("3-after-gacha"), r" coins free ([0-9]+) ")
    fails = common.checks(
        (re.search(r"mission %s: cleared 1" % re.escape(m), st("2-after-battle")), "the battle wasn't cleared"),
        (c2 is not None and c3 is not None and c3 < c2, "the draw debited no coins (%s -> %s)" % (c2, c3)),
        (re.search(r"^  gacha ", st("3-after-gacha"), re.M), "the server recorded no draw"),
    ) + common.common_log_checks(s, crash=False)
    return common.verdict(s, fails, "login, popups, battle cleared, 10-draw debited %s -> %s coins, back home" % (c2, c3))
