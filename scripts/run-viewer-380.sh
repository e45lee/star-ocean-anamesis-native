#!/bin/bash
# Runs the offline 3.8.0 client, unmodified, in the viewer (build/emulator-viewer/soa-viewer): the
# game as Square Enix shipped it after the service ended. It needs no server: its one request
# (NoLoginStart) goes unanswered, as on a phone today (emulator-viewer/README.md "Network").
#
# Usage: scripts/run-viewer-380.sh [options]
#   --data DIR   where the emulated phone keeps its data (saves, settings, the extracted library;
#                default ~/.local/share/soa-viewer-380, beside the port's ~/.local/share/soa-linux)
#   any other options go to soa-viewer, e.g. --fullscreen, --size 729x1296, --download-dir DIR
#   (serve assets missing from the APKs from DIR; soa-viewer --help)
#
# Needs: scripts/build.sh and work/extracted/xapk/ (the 3.8.0 XAPK unpacked by tools/extract.sh;
# README.md, "Game files").
set -euo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
viewer=$repo/build/emulator-viewer/soa-viewer

data=${HOME:-.}/.local/share/soa-viewer-380
viewer_args=()
while [ $# -gt 0 ]; do
  case "$1" in
    -h|--help) sed -n '2,13p' "$0" | sed 's/^# \{0,1\}//'; exit 0;;
    --data|--home) data=$2; shift 2;;
    *) viewer_args+=("$1"); shift;;
  esac
done

[ -x "$viewer" ] || { echo "run-viewer-380: $viewer isn't built; run scripts/build.sh first" >&2; exit 1; }
xapk=$repo/work/extracted/xapk
for f in com.square_enix.android_googleplay.StarOceanj.apk assetinstalltime.apk config.arm64_v8a.apk; do
  [ -s "$xapk/$f" ] || { echo "run-viewer-380: work/extracted/xapk/$f is missing; see README.md" >&2; exit 1; }
done

mkdir -p "$data"
vpid=
cleanup() {
  [ -n "$vpid" ] && kill "$vpid" 2>/dev/null || true
  wait 2>/dev/null || true
}
trap cleanup EXIT
trap 'exit 130' INT TERM

echo "== starting soa-viewer (phone data $data; no server)"
# In the background so Ctrl-C / a kill of this script reaches the trap, which stops it.
"$viewer" --apk-dir "$xapk" --data "$data" "${viewer_args[@]}" &
vpid=$!
wait "$vpid"
