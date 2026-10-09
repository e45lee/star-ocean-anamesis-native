#!/bin/sh
# The restored deep space mode (the in-process local server, --galaxy-pass): DeepSpaceActiveList, an
# expedition started (DeepSpaceAutoMemberSelect, DeepSpaceMissionStart), returned (clock:+1900) and
# collected (DeepSpaceMissionEnd), a quick return (DeepSpaceMissionEndNow), two ships at once (a pass
# ship), the achievements received (AchievementReceive). OUT/state-*.txt: the deep-space tables.
#
# Usage: port/scripts/deepspace_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/deepspace.py (its doc: the steps, the environment, the outputs):
# `control/run.py deepspace --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" deepspace "$@"
