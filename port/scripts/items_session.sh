#!/bin/sh
# The item menu's lock (LockItem / UnlockItem: varargs on the FakeApiCaller route), a sale and an
# enhancement against the local server: 12 planted weapons; lock one, sell one, enhance the locked
# one with one material; after a re-login the lock is still there and is undone.
#
# Usage: port/scripts/items_session.sh [--target port-inproc|port-server] <soa> <out-dir> <scratch-dir>
# Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/items.py (its doc: the steps, the outputs):
# `control/run.py items --help`; control/run.py --list. Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" items "$@"
