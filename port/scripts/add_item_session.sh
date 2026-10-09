#!/bin/sh
# AddItem as a map: a weapon drawn from the gacha is in the item list at once (no re-login) and the
# client sells it (SellItemArray of the drawn uid).
#
# Usage: port/scripts/add_item_session.sh [--target port-inproc|port-server] <soa> <out-dir> <scratch-dir>
# Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/add_item.py (its doc: the steps, the outputs):
# `control/run.py add-item --help`; control/run.py --list. Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" add-item "$@"
