#!/bin/bash
# Boot check of the 3.8.0 viewer (emulator-viewer/README.md "Checks"): builds nothing.
#
# Usage: emulator-viewer/scripts/viewer_boot.sh [soa-viewer binary] [out dir] [extra soa-viewer args...]
#   defaults: build/emulator-viewer/soa-viewer (the repository build: scripts/build.sh); a fresh
#   mktemp dir (kept: the log and screenshots; the phone's data is deleted unless KEEP_DATA=1)
#
# Runs soa-viewer headless on a fresh phone (no save) and checks that the unmodified offline client
# boots to its first interactive screens:
#   1. the title (ref/title.png), with the "TAP TO START" prompt;
#   2. its one request, NoLoginStart, went nowhere: the lookup of production-game.so-ana.com was
#      answered "not found" (net_offline.cpp) and the client carried on without an error dialog;
#   3. TAP TO START opens the stand-alone terms prompt of a new player (ref/terms.png).
# Prints PASS or FAIL (exit 0 / 1). Kills only the soa-viewer it started.
here=$(cd "$(dirname "$0")" && pwd)
bin=${1:-$here/../../build/emulator-viewer/soa-viewer}
out=${2:-$(mktemp -d "${TMPDIR:-/tmp}/viewer-boot.XXXXXX")}
shift $(( $# > 2 ? 2 : $# ))
mkdir -p "$out"
out=$(cd "$out" && pwd)
# shellcheck source=viewer_lib.sh
. "$here/viewer_lib.sh"

start_viewer "$bin" "$@"
reach title 240 || finish
wait_log "NoLoginStart: production-game.so-ana.com not found (offline), no error dialog" 30 \
    "getaddrinfo(production-game.so-ana.com): the service is gone" || finish
reach terms 60 364:1000 || finish
finish
