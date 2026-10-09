#!/bin/sh
# Summer demonstration: the unmodified 3.7.0 client in the emulator (soa-emu) against soa-server
# with the summer events enabled, from boot to a summer event battle (水着イベント2020: story mc99_565,
# battle me99_1054) and a summer gacha 10-draw (復刻水着2020①), with numbered screenshots and a
# contact sheet (OUT/summer-demonstration-grid.png); the server's state before / after checked.
# Builds nothing.
#
# Usage: emulator/scripts/summer_demo.sh [--target T] [--watch] [--clock C|host] [--emu FILE] [--server FILE] [OUT]
#   OUT default work/test/summer-demonstration (its old *.png, *.log, state-*.txt are deleted first)
# Env: SOA_PHONE (scripts/shared-phone.sh), EMU_DATA=DIR (a phone used as it is), KEEP_SCRATCH=1.
# Prints PASS / FAIL per milestone and a final PASS (exit 0) or FAIL (exit 1); OUT/milestones.txt.
# The session is control/soadrive/sessions/summer_demo.py (its doc: the steps and the outputs):
# `control/run.py summer-demo --help`.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" summer-demo "$@"
