#!/bin/sh
# キャラクター > スタンプ編成 (the chat stamps): the default stamps and palette, a changed palette
# sent (SetStampSlot) and kept: after a re-login the client starts from it.
#
# Usage: port/scripts/stamps_session.sh [--target port-inproc|port-server] <soa> <out-dir> <scratch-dir>
# Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/stamps.py (its doc: the steps, the outputs):
# `control/run.py stamps --help`; control/run.py --list. Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" stamps "$@"
