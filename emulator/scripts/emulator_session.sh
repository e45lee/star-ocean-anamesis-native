#!/bin/sh
# End-to-end session of the 3.7.0 emulator against soa-server (emulator/README.md "Networking",
# "Checks"). Builds nothing.
#
# Usage: emulator/scripts/emulator_session.sh [--target T] [--new-player] [soa-emu] [soa-server] [out dir]
#   defaults: build/emulator/soa-emu; build/server/soa-server; a fresh mktemp dir (kept: logs,
#   screenshots, the packet log, the server's state dumps; the phone's 3 GB of downloaded data is
#   deleted at the end unless KEEP_DATA=1). The client may be soa (soa --server: the port's client on
#   the wire; port/scripts/rebase_server_diff.sh).
# Env: EMU_DATA=DIR (a phone used as it is), SOA_PHONE (scripts/shared-phone.sh), SESSION_PLAY=0 (stop
#   at home), NEWPLAYER_NAME, NEWPLAYER_STEPS, NO_RETRY=1, FRESH_KVS=1, SERVER_ARGS, KEEP_DATA=1.
# The seeded run (the LOCAL00001 player, soa-server --campaign-seed mf01_001): NoLoginStart,
# StartBridge, the bridge POST, UpdateSession, Login (+ GetPlayerRes), the data check or the download,
# home (the notice board), the login popups, ミッション -> GetMissionList, 1-05 -> MissionStart, the
# battle -> MissionEnd (the battle log the server decoded), the results -> the map, ガチャ -> a
# 10-draw (SaleGacha; coins debited, ten draws in the state), home.
# The --new-player run (soa-server --new-player): Login -> 19001, terms, the name, CreatePlayer, the
# data, the tutorial (UpdateTutorial 1-9, the battle tutorial ms00_001), the milestones of
# tests/tutorial_milestones.txt (tools/compare_tutorial.py check emu: OUT/milestones.txt).
# Prints PASS / FAIL per milestone and a final PASS / FAIL (exit 0 / 1). Kills only the processes
# it started.
# The sessions are control/soadrive/sessions/seeded.py and newplayer.py (their docs: the steps, the
# environment, the outputs); `control/run.py --list` shows the targets each runs against.
session=seeded
target=
if [ "${1:-}" = --target ]; then target="--target $2"; shift 2; fi
if [ "${1:-}" = --new-player ]; then session=newplayer; shift; fi
# shellcheck disable=SC2086
exec python3 "$(dirname "$0")/../../control/run.py" $target $session "$@"
