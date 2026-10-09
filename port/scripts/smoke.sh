#!/bin/sh
# Usage: port/scripts/smoke.sh <soa-binary> <out-dir> [baseline-dir] [extra soa args...]
# See smoke.py.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/smoke.py" "$@"
