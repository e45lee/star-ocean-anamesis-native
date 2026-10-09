"""Session `battle`: the scripted route into a battle (729x1296 window), for coverage/profiling and as
a battle check: title -> Login -> the data check -> home (notice board, LOGIN BONUS) -> ミッション (the
episode list, CPhase_SelectPart, phase 8) -> back home -> the port control commands
`mission:mf01_001` (the mission CPhase_Battle starts; FLOW_MISSION overrides it) + `phase:0xf`
(CPhase_Battle, the switch a mission's start button makes) -> MissionStart to the in-process local
server -> the battle (the party acts on its own) -> MissionEnd -> the Mission Result pages -> home.
(campaign_session.sh reaches the same battle through the mission map's UI.) Every step waits for its
log line (phase changes, the server's request lines), then screenshots. The server state
(tools/server_state.py) is dumped at home and after the battle (OUT/state-*.txt). Ends with PASS
(exit 0) or FAIL (exit 1).

The phone: the shared pre-downloaded one, linked (scripts/shared-phone.sh); SOA_PHONE=DIR another,
SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
Usage: port/scripts/battle_session.sh <soa> <out-dir> <scratch-dir> [--soa-arg FLAG]...   (from any directory)
Env: FLOW_MISSION, SEED_RNG, WATCH=1; SOA_COVERAGE / SOA_PROFILE pass through to soa.
Targets: port-inproc (the `mission:` / `phase:` shortcuts and the phase lines are the port's)."""
import os
import re

from ..flows import mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it enters the battle through the port's `mission:` / `phase:0xf` control commands"
WRAPPER = "port/scripts/battle_session.sh"


def options(ap):
    common.port_options(ap, extra=False)
    ap.add_argument("--soa-arg", action="append", default=[], dest="soa_args",
                    help="an extra soa flag (repeatable; e.g. --soa-arg=--seed --soa-arg=SEED.xml: another party, "
                         "tools/make_test_seed.py --home: the home character leads party 1)")


def main(o):
    m = os.environ.get("FLOW_MISSION") or "mf01_001"
    s = common.port_run(o, common.port_config(o))

    def body(s):
        common.port_login(s, notice=None, bonus=None)
        s.state("home")
        common.settle(s, mask=common.HOME_MASK)
        common.episode_list(s)
        common.settle(s, "03-episodes")
        common.tap_to_phase(s, "戻る -> home", "100:1120", 4, "04-home", mask=common.HOME_MASK, fatal=True)
        mission.port_start(s, m)
        s.wait_log(r"MissionStart mission [0-9]* \(master_mission\)", 60, name="MissionStart")
        # a fixed wait: a picture of the battle's loading screen, nothing to wait for
        s.ctl("wait:1500", s.shot_cmd("05-battle-loading"))
        mission.battle_shots(s, 10, 90, 4000)
        s.wait_log(r"MissionEnd mission [0-9]*: player exp", 30, name="the battle ended (MissionEnd)")
        common.settle(s, "90-result", hold=2)
        mission.results_until(s, mission.phase(4), 91, 105, 1000, name="the result pages -> home")
        common.settle(s, "99-home", mask=common.HOME_MASK)
        s.ctl("profile-dump")
        s.state("after-battle")

    if not common.drive(s, body):
        return 1
    st = lambda tag: open(os.path.join(o.out, "state-%s.txt" % tag)).read()
    exp0, exp1 = (common.state_value(st(t), r"(exp [0-9]+)", str) for t in ("home", "after-battle"))
    fails = common.checks(
        (common.log_has(s, r"selected mission %s " % re.escape(m)), "mission:%s wasn't selected" % m),
        (common.log_has(s, r"MissionEnd mission [0-9]*: player exp"), "no MissionEnd"),
    ) + common.common_log_checks(s) + common.checks(
        (exp0 and exp0 != exp1, "the player's EXP didn't change in the server state (%s -> %s)" % (exp0, exp1)))
    for ln in open(s.client_log, errors="replace").read().splitlines():
        if re.search(r"MissionStart mission|MissionEnd mission", ln):
            print("  " + ln)
    return common.verdict(s, fails, "%s fought (MissionStart, MissionEnd), the result pages, back home" % m)
