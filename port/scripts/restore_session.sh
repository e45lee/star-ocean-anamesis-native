#!/bin/sh
# End-to-end session of the restored online game (the in-process local server): boot -> home -> a
# battle (mf01_001 through `mission:` / `phase:0xf`; FLOW_MISSION) -> the Mission Result screens ->
# home -> the gacha -> a 10-draw that debits 紋章石 -> home; the server state after boot, the battle
# and the draw (OUT/state-*.txt). Prints "PASS: ..." or "FAIL: ..." (exit 1).
#
# Usage: port/scripts/restore_session.sh <soa> <out-dir> <scratch-dir> [soa flags...]   (from any directory)
# The extra flags go to soa, e.g. --campaign-seed mf01_001 or --live-check FAMILY.
# Env: SOA_PHONE (scripts/shared-phone.sh), FLOW_MISSION, SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/battle_gacha.py (its doc: the steps, the environment, the outputs):
# `control/run.py battle-gacha --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" battle-gacha "$@"
