#!/bin/sh
# Scripted session of the restored entry flow (the in-process local server), in two boots: the seeded
# player (title -> Login -> data check -> the popups -> home), then a new player (--new-player: Login
# error 19001 -> terms -> name -> CreatePlayer -> the tutorial -> home -> the home tutorial, until
# UpdateTutorial(9)). OUT/seeded, OUT/newplayer (screenshots), OUT/*.log, OUT/state-*.txt.
#
# Usage: port/scripts/newplayer_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_PHONE (scripts/shared-phone.sh; none: both phones download), NEWPLAYER_NAME, NEWPLAYER_STEPS, WATCH=1.
# The session is control/soadrive/sessions/entry.py (its doc: the steps, the environment, the outputs):
# `control/run.py entry --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" entry "$@"
