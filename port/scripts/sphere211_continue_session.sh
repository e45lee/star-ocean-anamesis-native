#!/bin/sh
# A lost Sphere 211 battle (enemy level 250 via the server's test hook) with a rental, continued
# (Sphere211MissionContinue, 100 coins) and retired (Sphere211MissionFailed), the stamina healed
# (Sphere211StaminaHeal), the board's 実績 tabs. About 5 minutes.
#
# Usage: port/scripts/sphere211_continue_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SEED_RNG (default 605), SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/sphere211_continue.py (its doc: the steps, the environment, the outputs):
# `control/run.py sphere211-continue --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" sphere211-continue "$@"
