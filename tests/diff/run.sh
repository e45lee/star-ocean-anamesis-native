#!/bin/bash
# tests/diff: the port against the emulator, flow by flow (tests/diff/README.md).
#
# Usage: tests/diff/run.sh [FLOW...] [--target emu,port-server,port-inproc] [--out DIR] [--keep]
#                          [--sequential] [--inject TARGET:SERVER-ARGS]
#   FLOW      seeded, tutorial, event (default: all, in that order)
#   --target  the targets (default all three; emu is the reference the others are compared with)
#   --out     the out dir (default a fresh /tmp/tests-diff.XXXX): OUT/<flow>/report.txt, OUT/<flow>/<target>/
#   --inject  extra server arguments for one target only (the check that a difference FAILs)
# Env: SOA, SOA_EMU, SOA_SERVER (the binaries; default build/port/soa, build/emulator/soa-emu,
#      build/server/soa-server), SOA_PHONE (scripts/shared-phone.sh: default the shared phone).
# Runs from any directory; headless; kills only the processes it started. Exit 1 on a difference.
exec python3 "$(dirname "$0")/difftest.py" "$@"
