#!/bin/sh
# Input on the debug windows (the CManager input frame): two overlapping draggable windows
# (style 0x101; +0x25 bit 0 = draggable), taps that activate the lower one (it comes to the
# front), a press on a title strip, the other one again, and a touch drag. Screen = 0.9 x debug
# coordinates in a 729x1296 window (CMouse reports 810x1440 pixels). A touch drag doesn't set
# CMouse's button (only taps do), so windows can't be dragged by touch; the drag is a no-op.
#
# The debug window manager is the guest's own code (3.7.0, no natives; the offline port compared
# its native CDebugWindows with the guest's on these shots). Checks: the windows' ids, and the
# screen: a tap on A brings it in front of B, closing them all brings the home back. Ends with
# PASS (exit 0) or FAIL (exit 1).
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/debug_input_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
export SOA_HEADLESS="${SOA_HEADLESS:-1}"  # soa --headless (no window); SOA_HEADLESS=0 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos"
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
timeout -k 10 2400 "$SOA" --data "$TMP/data" --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
fail() { echo "FAIL: $*"; c quit || true; exit 1; }
# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S"
python3 $FLOW login-popups "$TMP/fifo" "$L" - - - || fail "the login popups didn't close"
c wait:3000 shot:$S/02-home.png
NEW=_ZN9Framework13CDebugWindows15CreateNewWindowEPKcjiijjS2_b
c wait:500 debugwin:0:0; logw 'CDebugWindows::Initialize'
c wait:500 "call:$NEW:s=A:0x101:40:200:400:300:s=:0"; logw "call $NEW -> 0x1\$"
c "call:$NEW:s=B:0x101:200:350:400:300:s=:0"; logw "call $NEW -> 0x2"
c wait:1000 shot:$S/03-two.png
c tap:90:360 wait:1500 shot:$S/04-activate-A.png
c tap:270:185 wait:1500 shot:$S/05-press-title-A.png
c tap:400:500 wait:1500 shot:$S/06-activate-B.png
c drag:400:320:100:700 wait:1500 shot:$S/07-drag.png
c call:_ZN9Framework13CDebugWindows27PostQuitMessageToAllWindowsEv; logw 'call _ZN9Framework13CDebugWindows27PostQuitMessageToAllWindowsEv'
c wait:3000 shot:$S/08-closed.png
c quit
wait $pid || true
trap - EXIT

# The screen, in two strips the home character never reaches: A's title strip (400x14+46+208 on
# the screen: the windows are opaque) and B's title strip where it overlaps A (230x14+210+361,
# visible only while B is in front). B, created last, starts in front; the tap on A brings A to
# front; closed, A's strip shows the home again.
d() { compare -metric RMSE "$S/$1.png[$3]" "$S/$2.png[$3]" null: 2>&1 | sed 's/.*(\(.*\))/\1/'; }
A=400x14+46+208 B=230x14+210+361
ok=1
r=$(d 03-two 02-home $A); echo "  03-two vs home (A's strip): rmse $r"
awk -v r="$r" 'BEGIN { exit !(r > 0.05) }' || { echo "FAIL: window A doesn't show"; ok=0; }
r=$(d 03-two 04-activate-A $B); echo "  03-two vs 04-activate-A (B's strip over A): rmse $r"
awk -v r="$r" 'BEGIN { exit !(r > 0.05) }' || { echo "FAIL: the tap on A didn't bring it in front of B"; ok=0; }
# (The tap on B's own part afterwards, after the press on A's title strip, leaves A in front: the
# guest's behaviour, reported, not checked.)
echo "  04-activate-A vs 06-activate-B (B's strip over A): rmse $(d 04-activate-A 06-activate-B $B)"
r=$(d 08-closed 02-home $A); echo "  08-closed vs home (A's strip): rmse $r"
awk -v r="$r" 'BEGIN { exit !(r < 0.01) }' || { echo "FAIL: the windows didn't close"; ok=0; }
grep -qE 'Unhandled SIG|\*\*\* host signal' "$L" && { echo "FAIL: soa crashed"; ok=0; }
[ $ok = 1 ] || exit 1
echo "PASS: two debug windows, the lower one brought to front by a tap, a title press, a drag, closed"
