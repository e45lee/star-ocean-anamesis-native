#!/bin/sh
# Usage: port/scripts/smoke.sh <soa-binary> <out-dir> [baseline-dir] [extra soa args...]
# See smoke.py.
exec python3 "$(dirname "$0")/smoke.py" "$@"
