#!/bin/sh
# The gate tiers (tests/TIERS.md; tests/tiers.json is the list): T0 every commit, T1 per change
# (tools/tests_for.py), T2 per batch, T3 occasional. tools/gate.py --help for the options.
#   tools/gate.sh T0
#   tools/gate.sh T1 --git-diff main
#   tools/gate.sh T2 --out /tmp/gate-batch
exec python3 "$(dirname "$0")/gate.py" "$@"
