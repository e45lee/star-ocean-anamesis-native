#!/bin/sh
# The tutorial battle from a FRESH state (soa --server inproc, --new-player, no save, no server state):
# title -> Login (error 19001) -> terms -> name entry -> CreatePlayer -> the data check -> the tutorial
# (the opening, the battle tutorial ms00_001, the mission-menu step) -> home (UpdateTutorial 7) -> the
# home tutorial (UpdateTutorial 9), with CCharacterObject::OnDamage traced (SOA_TRACE); checks the
# damage, the battle, and tests/tutorial_milestones.txt (tools/compare_tutorial.py check port).
# OUT: fresh.log, fresh/lNNN.png, server.sqlite3 (tools/compare_tutorial.py compare OUT EMU_OUT).
#
# Usage: port/scripts/tutorial_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_PHONE (scripts/shared-phone.sh), NEWPLAYER_NAME, TUTORIAL_STEPS, WATCH=1.
# The session is control/soadrive/sessions/tutorial.py (its doc: the steps, the environment, the outputs):
# `control/run.py tutorial --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" tutorial "$@"
