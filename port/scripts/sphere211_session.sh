#!/bin/sh
# The restored Sphere 211 (the in-process local server): the rental bonus popup, then a dive on floor 1
# of the map --seed-rng 605 lots: 4 battles (GetSphere211Info, Sphere211AutoMemberSelect,
# Sphere211MissionStart / MissionEnd; a rental on the first, Sphere211StaminaHeal after it), 帰還
# (ReturnSphere211), the boss, Sphere211FloorClear, Sphere211UseRerollItem, Sphere211SelectedFloor to
# floor 2, 帰還 again. OUT/state-*.txt: the Sphere 211 tables. About 20 minutes.
#
# Usage: port/scripts/sphere211_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SEED_RNG (default 605), SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/sphere211.py (its doc: the steps, the environment, the outputs):
# `control/run.py sphere211 --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" sphere211 "$@"
