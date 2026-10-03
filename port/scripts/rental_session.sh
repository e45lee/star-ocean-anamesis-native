#!/bin/sh
# A rental helper fought as member 4 (1-05 through the mission map; the rental list's first entry),
# then a second boot on the same phone a day later: the rental bonus paid at login and its popup.
#
# Usage: port/scripts/rental_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: CAMPAIGN_SEED, RENTAL_CLOCK (default "2026-09-30 12:00:00"), RENTAL_DAY2 (default 1),
# HOME_MISSION_X, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/rental.py (its doc: the steps, the environment, the outputs):
# `control/run.py rental --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" rental "$@"
