#!/bin/sh
# Scripted session with the framework's debug windows (all-characters save, 729x1296 window):
# title -> Login -> the data check -> home (notice board, LOGIN BONUS) -> port option `debugwin:0:0` (Framework::CDebugWindows::Initialize, which the
# release build never calls, then CDebugWindows::Progress every frame) -> CreateNewWindow x2 and
# CreateTabWindow through `call:` -> drag / tap on them -> close them -> home.
# Every step waits for its log line (the control command's result), then screenshots. The checks:
# the windows' ids (CreateNewWindow -> 1, 2), and the screen: each window changes it, closing them
# all brings the home back (ImageMagick RMSE against the home shot). The debug window manager is
# the guest's own code (3.7.0, no natives). Ends with PASS (exit 0) or FAIL (exit 1).
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/debug_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_COVERAGE / SOA_PROFILE pass through to soa.
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
HEADLESS=--headless; [ "${WATCH:-0}" != 1 ] || HEADLESS=--windowed  # soa --headless (no window); WATCH=1 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos"
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
timeout -k 10 2400 "$SOA" $HEADLESS --data "$TMP/data" --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
c() { tools/py $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { tools/py $FLOW wait-log "$L" "$1" "${2:-120}"; }

fail() { echo "FAIL: $*"; c quit || true; exit 1; }
# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S"
tools/py $FLOW login-popups "$TMP/fifo" "$L" - - - || fail "the login popups didn't close"
c wait:3000 shot:$S/02-home.png
NEW=_ZN9Framework13CDebugWindows15CreateNewWindowEPKcjiijjS2_b
TAB=_ZN9Framework13CDebugWindows15CreateTabWindowEPKcjiijjj
c wait:500 debugwin:0:0; logw 'CDebugWindows::Initialize'
c wait:500 "call:$NEW:s=PORT DEBUG:1:40:200:400:300:s=:1"; logw "call $NEW -> 0x1\$"
c wait:1000 shot:$S/03-window.png
c "call:$NEW:s=SECOND:2:200:600:460:360:s=:1"; logw "call $NEW -> 0x2\$"
c wait:1000 shot:$S/04-two-windows.png
c "call:$TAB:s=TABS:3:60:980:600:220:3"; logw "call $TAB"
c wait:1000 shot:$S/05-tab-window.png
c drag:200:215:300:420 wait:1500 shot:$S/06-dragged.png
c tap:300:500 wait:1500 tap:450:750 wait:1500 shot:$S/07-tapped.png
c call:_ZN9Framework13CDebugWindows27PostQuitMessageToAllWindowsEv; logw 'call _ZN9Framework13CDebugWindows27PostQuitMessageToAllWindowsEv'
c wait:3000 shot:$S/08-closed.png profile-dump
c quit
wait $pid || true
trap - EXIT

# The screen, in the tab window's lower part (debug 60,980 600x220: on the screen 540x70+54+1010,
# the home's main buttons; the home character, which animates and reacts to the taps, is above
# it): the tab window covers it, and once the windows are closed it is close to the home again.
d() { compare -metric RMSE "$S/$1.png[540x70+54+1010]" "$S/02-home.png[540x70+54+1010]" null: 2>&1 | sed 's/.*(\(.*\))/\1/'; }
ok=1
for n in 05-tab-window 07-tapped; do
  r=$(d $n); echo "  $n vs home (tab window area): rmse $r"
  awk -v r="$r" 'BEGIN { exit !(r > 0.25) }' || { echo "FAIL: $n doesn't show the tab window"; ok=0; }
done
open=$(d 07-tapped); r=$(d 08-closed); echo "  08-closed vs home (tab window area): rmse $r"
awk -v r="$r" -v o="$open" 'BEGIN { exit !(r < o / 2) }' || { echo "FAIL: the windows didn't close"; ok=0; }
grep -qE 'Unhandled SIG|\*\*\* host signal' "$L" && { echo "FAIL: soa crashed"; ok=0; }
[ $ok = 1 ] || exit 1
echo "PASS: debug windows created (two windows, a tab window), dragged, tapped and closed"
