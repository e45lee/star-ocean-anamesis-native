#!/bin/sh
# The battle simulator (TrainingMissionStart: the current party, no play record) and a lost battle
# continued for 100 coins (MissionContinue 1) and retired (MissionContinue 0, MissionFailed), then a
# re-login. About 8 minutes.
#
# Usage: port/scripts/simulator_continue_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/simulator_continue.py (its doc: the steps, the environment, the outputs):
# `control/run.py simulator-continue --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" simulator-continue "$@"
