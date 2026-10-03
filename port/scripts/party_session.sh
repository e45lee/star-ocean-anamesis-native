#!/bin/sh
# The restored party screen (the in-process local server): party sets 1 and 2 edited and saved
# (UpdatePartySet), the home character changed (UpdateHome), then a battle (mission:mf01_001 phase:0xf)
# whose MissionStart takes the set saved last. OUT/shots, OUT/state-*.txt (the party table), OUT/log.txt.
#
# Usage: port/scripts/party_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: FLOW_MISSION, SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/party.py (its doc: the steps, the environment, the outputs):
# `control/run.py party --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" party "$@"
