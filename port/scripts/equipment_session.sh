#!/bin/sh
# An inheritance accessory takes in an ordinary accessory's factor on the strengthening screen
# (InheritAccessory), the equipment screen's 自動設定 (EquipAuto), then a re-login. About 6 minutes.
#
# Usage: port/scripts/equipment_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/equipment.py (its doc: the steps, the environment, the outputs):
# `control/run.py equipment --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" equipment "$@"
