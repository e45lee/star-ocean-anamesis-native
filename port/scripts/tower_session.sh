#!/bin/sh
# The tower (試練の遺跡), opened by the opt-in --restore-tower: home -> スフィア211 (the extra-dungeon menu)
# -> 試練の遺跡 -> the floor list -> the top area's 1F -> its battle (master_tower_mission) -> the results
# -> 1F CLEAR, 2F New; the cleared floor in the state (OUT/state.txt). "PASS tower_session" or
# "FAIL tower_session (N)" (exit 1).
#
# Usage: port/scripts/tower_session.sh <soa> <out-dir> <scratch-dir> [soa flags...]   (from any directory)
# e.g. --live-check restore (the native CCocosNode::SearchByName).
# Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/tower.py (its doc: the steps, the environment, the outputs):
# `control/run.py tower --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" tower "$@"
