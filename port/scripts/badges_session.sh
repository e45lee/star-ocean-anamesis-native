#!/bin/sh
# The NEW badges: a 10-draw, the character list with NEW, 戻る -> ClearNewCharacter, the list cleared,
# and a re-login: still cleared (control/soadrive/sessions/badges.py).
#
# Usage: port/scripts/badges_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/badges.py (its doc: the steps, the environment, the outputs):
# `control/run.py badges --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" badges "$@"
