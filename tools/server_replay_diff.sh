#!/bin/sh
# RG4 (server/PLAN-readability.md 4.1): replay every corpus of server/tests/replay/ with two
# soa-server builds and compare replies, error codes, end state and log (tools/server_replay_diff.py).
#   tools/server_replay_diff.sh [--out DIR] [--keep] BIN_A BIN_B [CORPUS_DIR...]
# Exit 0 identical, 2 only other log lines (tier 2, to declare) differ, 1 anything else.
exec python3 "$(dirname "$0")/server_replay_diff.py" "$@"
