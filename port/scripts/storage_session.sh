#!/bin/sh
# The equipment storage (装備倉庫) and the overflow box (一時保管庫) of the item menu: 500 planted
# weapons fill the inventory; deposit, withdraw and sell from the storage; a present's weapon goes to
# the overflow box; after a re-login the storage and the box keep their contents and the box's weapon
# is taken out.
#
# Usage: port/scripts/storage_session.sh [--target port-inproc|port-server] <soa> <out-dir> <scratch-dir>
# Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/storage.py (its doc: the steps, the outputs):
# `control/run.py storage --help`; control/run.py --list. Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" storage "$@"
