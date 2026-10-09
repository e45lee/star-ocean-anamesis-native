#!/bin/sh
# The in-process gate of the 3.7.0 rebase: soa with its defaults (--server inproc, --natives all)
# from the title to home: NoLoginStart, TAP TO START, Login, the data check (or, with SOA_PHONE=none,
# the whole 3 GB download from the in-process CDN: scripts/make-phone-370.sh takes the phone from
# <scratch-dir>/data afterwards), home, the login popups (notice, LOGIN BONUS). Prints "PASS: ..." at
# the end, or "FAIL: ..." with exit status 1.
#
# Usage: port/scripts/rebase_inproc_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_PHONE (unset: the shared phone; DIR; none: download), CLIENT_SAVE=client|seed|phone, SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/login.py (its doc: the steps, the environment, the outputs):
# `control/run.py login --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" login "$@"
