#!/bin/sh
# The in-process gate of the 3.7.0 rebase (docs/history/PLAN-rebase-370.md P1): soa on the 3.7.0 client with
# its defaults, --server inproc (the local server library on the FakeApiCaller route, plus its CDN
# in-process) and --natives route (only the route's own hooks and the CPhase::Progress observer),
# from the title to home: NoLoginStart, TAP TO START, Login, the downloader (its check, or the whole
# download on an empty phone), home (the notice board), the login popups (notice, LOGIN BONUS).
# Prints "PASS: ..." at the end, or "FAIL: ..." with exit status 1.
#
# Usage: port/scripts/rebase_inproc_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env:
#   SOA_PHONE       the phone (port/scripts/phone370.sh): unset -> linked from the shared
#                   pre-downloaded phone work/phone-3.7.0 when it is built; DIR -> from DIR, a phone
#                   with the game data downloaded already (e.g. a KEEP_DATA=1
#                   emulator/scripts/emulator_session.sh run's OUT/emu): the client only checks its
#                   data against the in-process CDN. SOA_PHONE=none: the data dir starts empty and
#                   the client downloads the 3 GB from the in-process CDN first (the download
#                   dialogs; about 3-4 minutes more; scripts/make-phone-370.sh's run).
#   CLIENT_SAVE=client|seed|phone  the client save copied into shared_prefs/Game.xml: the committed
#                   data/saves/client/Game.xml (default; an offline-build-era KVS, which 3.7.0 reads), the seed
#                   data/saves/seed/Game.xml, or the phone's own (SOA_PHONE only). The local KVS
#                   (Aska.xml: version, crc, device UUID) is always deleted: the client makes a new one.
#   SOA_SERVER_SEED_RNG (default 1)
# Screenshots go to OUT/shots, the log to OUT/log.txt, the server state (tools/server_state.py) to
# OUT/state-home.txt. Kills only the soa it started.
set -eu
SOA=$1; OUT=$2; TMP=$3
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
export SOA_HEADLESS="${SOA_HEADLESS:-1}"
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos" "${OUT:?}"/state-*.txt
mkdir -p "$TMP" "$OUT/shots"
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
case ${CLIENT_SAVE:-client} in
    client) phone370_client_save "$TMP/data/data/shared_prefs" ;;
    seed) cp data/saves/seed/Game.xml "$TMP/data/data/shared_prefs/Game.xml" ;;
    phone) [ -n "${SOA_PHONE:-}" ] || { echo "FAIL: CLIENT_SAVE=phone needs SOA_PHONE"; exit 1; }
           # The shared phone (stamped) carries no save: only a copied SOA_PHONE=DIR has one.
           [ -f "$TMP/data/data/shared_prefs/Game.xml" ] || { echo "FAIL: CLIENT_SAVE=phone: $SOA_PHONE has no save (the shared phone never does)"; exit 1; } ;;
    *) echo "FAIL: CLIENT_SAVE=${CLIENT_SAVE}"; exit 1 ;;
esac
SOA_SERVER_SEED_RNG=${SOA_SERVER_SEED_RNG:-1} timeout -k 10 1500 "$SOA" --data "$TMP/data" --size 729x1296 \
  --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
step=boot
trap 'rc=$?; kill $pid 2>/dev/null || true; [ $step = done ] || { echo "FAIL: stopped at step $step"; exit 1; }; exit $rc' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; kill -0 $pid 2>/dev/null || { echo "FAIL: soa exited (log $OUT/log.txt)"; exit 1; }; done
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
tapw() { python3 $FLOW tap-until "$TMP/fifo" "$L" "$@"; }
has() { grep -q -- "$1" "$L"; }

# The title's NoLoginStart, answered in-process (the title shows once it's done).
step=title; logw 'request NoLoginStart' 180; logw 'port_debug: phase 1 ' 120
c wait:3000 shot:$S/01-title.png
# TAP TO START -> Login (a tap during the title's fade-in is sometimes dropped).
step=login; tapw 'request Login ' 90 10 6 -- tap:364:1000
# The data download phase (CPhase_DataDownload): the client checks its data against the CDN
# (version_latest_*). On an empty phone it first says the episode data is missing (決定 364:1043),
# then reads the manifests and asks to download (ダウンロード 515:800): the bundles, then 完了 (364:790).
if [ -n "${SOA_PHONE:-}" ]; then
    # the data check, and the download dialog of what the phone lacks (the master the server edits
    # for the run's clock: every run since the master edits), as every session (phone370_data)
    step=home; phone370_data "$TMP/fifo" "$L" "$S"
else
    step=download
    # Phase 19: CPhase_DataDownload (a tap before it lands on the login and isn't resent).
    logw 'port_debug: phase 19 ' 120
    tapw 'version_latest_Bulk' 120 8 10 -- wait:3000 tap:364:1043
    c wait:5000 shot:$S/02-download-dialog.png
    tapw 'I/http: GET .*/Android/B/' 120 10 10 -- tap:515:800
    # The downloads stop: no new GET for 30 s.
    last=-1; same=0
    while [ $same -lt 30 ]; do
        n=$(grep -c 'I/http: GET' "$L" || true)
        if [ "$n" = "$last" ]; then same=$((same + 1)); else same=0; last=$n; fi
        kill -0 $pid 2>/dev/null || { echo "FAIL: soa exited during the download"; exit 1; }
        sleep 1
    done
    c shot:$S/03-download-done.png
    step=home; tapw 'port_debug: phase 4 ' 120 8 10 -- tap:364:790
fi
# Home (phase 4): the notice board (ShowWebView, an empty web view on the desktop), then the LOGIN
# BONUS popup of the day's first login; flowctl.py login-popups waits for each and closes it.
step=popups; python3 $FLOW login-popups "$TMP/fifo" "$L" $S/04-notice.png $S/05-login-bonus.png $S/06-home.png | tee "$OUT/popups.txt"
c wait:5000 shot:$S/07-home.png
.venv/bin/python tools/server_state.py "$TMP/data/server.sqlite3" > "$OUT/state-home.txt"
c quit
wait $pid || true
step=done

ok=1
has 'p370: patch: CParameterUtility::FindGlobalStringWithKey hooked' || { echo "FAIL: platform370's patch wasn't installed"; ok=0; }
has 'replaced by native code (--natives route)' || { echo "FAIL: not --natives route"; ok=0; }
has 'fakeapi: fid a01c67ef: player_get.msgp from the local server' || { echo "FAIL: Login wasn't answered by the local server"; ok=0; }
has 'version_latest_Individual' || { echo "FAIL: the client didn't check its data against the in-process CDN"; ok=0; }
grep -q 'refused with error' "$L" && { grep 'refused with error' "$L"; echo "FAIL: a request was refused"; ok=0; }
grep -qE 'Unhandled SIG|\*\*\* host signal' "$L" && { echo "FAIL: soa crashed"; ok=0; }
grep -q 'notice yes, login bonus x[1-9]' "$OUT/popups.txt" || { echo "FAIL: the notice board and the LOGIN BONUS popup didn't both open and close"; ok=0; }
grep -q '^player LOCAL00001 ' "$OUT/state-home.txt" || { echo "FAIL: no LOCAL00001 player in the server state"; ok=0; }
[ $ok = 1 ] || exit 1
gets=$(grep -c 'I/http: GET' "$L" || true)
echo "PASS: 3.7.0 client in-process: title, Login, data check ($gets HTTP GETs from the in-process CDN), home, login popups"
