#!/bin/sh
# Favorability (the in-process local server): a first boot seeds the state, the favor table is set up
# (the home character one tap short of level 2), a second boot: two taps on the home character
# (UpdateFavorByTap, the rank-up), a battle (mission:mf01_001 phase:0xf: MissionEnd adds favor).
# OUT/shots, OUT/log.txt, OUT/favor-*.txt.
#
# Usage: port/scripts/restore_favor_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: FLOW_MISSION, SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/favor.py (its doc: the steps, the environment, the outputs):
# `control/run.py favor --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" favor "$@"
