#!/bin/sh
# Paid currency: a player with 50 stones draws once; the sale-stopped dialog (platform370's patch)
# opens the coin shop; the L set bought (paid + free stones, the purchase record), home, and a re-login:
# still there (control/soadrive/sessions/coins.py).
#
# Usage: port/scripts/coins_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/coins.py (its doc: the steps, the environment, the outputs):
# `control/run.py coins --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" coins "$@"
