#!/bin/sh
# Scripted route into a battle (729x1296 window), for coverage/profiling and as a battle check:
# title -> Login -> home (notice board, LOGIN BONUS) -> ミッション (the episode list) -> back home ->
# `mission:mf01_001` + `phase:0xf` (FLOW_MISSION overrides the mission) -> MissionStart -> the battle
# -> MissionEnd -> the Mission Result pages -> home; the server state at home and after the battle.
#
# Usage: port/scripts/battle_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_PHONE (scripts/shared-phone.sh), FLOW_MISSION, SEED_RNG, WATCH=1; SOA_COVERAGE / SOA_PROFILE pass through.
# The session is control/soadrive/sessions/battle.py (its doc: the steps, the environment, the outputs):
# `control/run.py battle --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" battle "$@"
