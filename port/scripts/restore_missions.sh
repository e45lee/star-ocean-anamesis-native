#!/bin/sh
# The mission side of the local server (in-process), end to end: a surprise-enemy battle of mf01_003
# (--surprise: the drops, mf01_004 unlocked), two steps of a step-up gacha (--clock 2021-05-25:
# gacha_pickup_role_1011), and MissionStart refused at stamina 0 (the 10004 error dialog -> the title).
#
# Usage: port/scripts/restore_missions.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/missions.py (its doc: the steps, the environment, the outputs):
# `control/run.py missions --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" missions "$@"
