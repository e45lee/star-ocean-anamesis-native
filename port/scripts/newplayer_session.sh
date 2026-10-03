#!/bin/sh
# Scripted session of the restored entry flow (the in-process local server; docs/client-changes.md
# "Entry flow", docs/server-rules.md "Entry flow"), in two parts:
#   1. seeded player (the 3.7.0 save): title -> Login -> data check -> notice popup -> home;
#   2. new player (SOA_RESTORE_NEW_PLAYER=1, empty save): title -> Login (error 19001) -> terms
#      -> name entry -> CreatePlayer -> Login -> data check -> tutorial (the opening scene
#      mc00_010 in auto mode with its choices, mc00_015, the battle tutorial ms00_001, mc00_025,
#      the mission-menu step: 1-01's story, the companions, home) until home, or
#      NEWPLAYER_STEPS x ~9 s; then the home tutorial (present box, gacha) until UpdateTutorial(9).
# Prints PASS / FAIL (the home tutorial finished) and exits non-zero on FAIL.
# Screenshots go to OUT/seeded and OUT/newplayer, logs to OUT/*.log, the server state to
# OUT/state-*.txt.
#
# SOA_PHONE=DIR: start both phones from a copy of a pre-downloaded phone (port/scripts/phone370.sh);
# without it the 3.7.0 client downloads its data after each Login.
#
# Usage: port/scripts/newplayer_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
export SOA_HEADLESS="${SOA_HEADLESS:-1}"  # soa --headless (no window); SOA_HEADLESS=0 to watch
CTL=control/soactl.py
rm -rf "${TMP:?}/seeded" "${TMP:?}/newplayer" "${OUT:?}/seeded" "${OUT:?}/newplayer" "${OUT:?}/seeded.log.pos" "${OUT:?}/newplayer.log.pos"
mkdir -p "$OUT/seeded" "$OUT/newplayer"
# The phones: SOA_PHONE's pre-downloaded copy (the new player's without its saves), else empty (the
# client downloads its data after Login); port/scripts/phone370.sh.
. port/scripts/phone370.sh
phone370_prepare "$TMP/seeded/data"
phone370_prepare "$TMP/newplayer/data"
rm -f "$TMP/newplayer/data/data/shared_prefs/Game.xml"
pid=
trap '[ -n "$pid" ] && kill $pid 2>/dev/null || true' EXIT
fail() { echo "FAIL: $*"; exit 1; }

start() {  # start <name> [env...]: soa (the in-process server) with a control FIFO
    name=$1; shift
    SDL_AUDIODRIVER=${SDL_AUDIODRIVER:-dummy} env "$@" SOA_SERVER_SEED_RNG=1 timeout -k 10 3600 "$SOA" --data "$TMP/$name/data" \
        --size 729x1296 --control "$TMP/$name/fifo" > "$OUT/$name.log" 2>&1 &
    pid=$!
    while [ ! -p "$TMP/$name/fifo" ]; do sleep 1; done
}
c() { python3 $CTL --timeout 400 "$FIFO" "$@"; }
waitlog() {  # waitlog <log> <pattern> [timeout s]
    i=0
    while ! grep -q "$2" "$1"; do
        sleep 1; i=$((i + 1))
        if [ $i -ge "${3:-240}" ]; then echo "timeout waiting for '$2' in $1"; return 1; fi
    done
}
tap_title() {  # tap_title <log> <pattern>: tap "TAP TO START" until <pattern> is logged; a tap
    # during the title's fade-in is sometimes ignored, so retry up to 6 times (~10 s apart).
    n=0
    while :; do
        c tap:364:970
        if waitlog "$1" "$2" 10 >/dev/null; then return 0; fi
        n=$((n + 1)); [ $n -ge 6 ] && { echo "title tap never led to '$2'"; return 1; }
    done
}
state() { .venv/bin/python tools/server_state.py "$TMP/$1/data/server.sqlite3" > "$OUT/state-$1.txt" || true; }

# ---- 1. seeded player -----------------------------------------------------------------------
phone370_client_save "$TMP/seeded/data/data/shared_prefs"
start seeded
FIFO=$TMP/seeded/fifo; L=$OUT/seeded.log; S=$OUT/seeded
waitlog "$L" 'port_debug: phase 1 '
c wait:8000 shot:$S/01-title.png
tap_title "$L" 'request Login'
phone370_data "$FIFO" "$L" "$S"
# The notice board, then the LOGIN BONUS popup of the day's first login (flowctl.py login-popups
# taps 閉じる until each is gone).
python3 control/flowctl.py login-popups "$FIFO" "$L" $S/02-notice.png $S/02-login-bonus.png $S/03-home.png || fail "the login popups didn't close"
state seeded
c quit || true
wait $pid || true; pid=

# ---- 2. new player --------------------------------------------------------------------------
start newplayer SOA_RESTORE_NEW_PLAYER=1
FIFO=$TMP/newplayer/fifo; L=$OUT/newplayer.log; S=$OUT/newplayer
waitlog "$L" 'port_debug: phase 1 '
c wait:8000 shot:$S/01-title.png
tap_title "$L" 'error 19001'
c wait:3000 shot:$S/02-terms.png tap:364:689 wait:3000 shot:$S/03-name.png
# The name: tap the field until the keyboard opens, type, 決定; checks CreatePlayer's name.
python3 control/flowctl.py name-entry "$FIFO" "$L" "${NEWPLAYER_NAME:-Claire}" $S/04-name-typed.png || fail "the name entry failed"
waitlog "$L" 'CreatePlayer:'
phone370_data "$FIFO" "$L" "$S" 'port_debug: phase 3 '
waitlog "$L" 'port_debug: phase 3 ' 300
# auto mode and fast-forward
c wait:15000 shot:$S/05-opening.png tap:612:1240 wait:1000 tap:115:45 wait:1000 || true
# Each round taps, in order:
#  - 364:506 / 364:562: the first button of a choice (SelectMenu) with three / two choices;
#    otherwise the tap advances the text (auto mode advances it too);
#  - the battle tutorial: its dialog buttons (次へ at 527:1090 or 527:785, 閉じる at 527:697),
#    RUSH (175:890), the enemy area (440:430, a normal attack) and the three skill buttons.
# A command batch that times out (the game busy loading) is retried in the next round.
i=0
while [ $i -lt "${NEWPLAYER_STEPS:-200}" ]; do
    c wait:6000 shot:$S/l$(printf %03d $i).png > /dev/null || true
    c tap:364:506 wait:400 tap:364:562 wait:400 tap:527:1090 wait:400 tap:527:785 wait:400 tap:527:697 wait:400 \
      tap:175:890 wait:300 tap:440:430 wait:300 tap:650:1005 wait:300 tap:505:1075 wait:300 tap:450:1215 > /dev/null || true
    i=$((i + 1))
    grep -q 'port_debug: phase 4 ' "$L" && break  # home: the tutorial is over
    grep -q 'request UpdateTutorial (fid [0-9a-f]*): 4$' "$L" && break  # the mission-menu step
done
# The mission-menu step (UpdateTutorial(4), where the offline build + the local server used to crash in
# CMissionMenu::SetLastPlayPlanetNow): planet Mere's map with 1-01 (ここをタップ) -> ストーリー開始
# -> the story, skipped (スキップ -> はい) -> UpdateTutorial(6) -> "summoned companions" 次へ ->
# ホーム (ここをタップ) -> home, UpdateTutorial(7).
if ! grep -q 'port_debug: phase 4 ' "$L"; then
    waitlog "$L" 'request UpdateTutorial (fid [0-9a-f]*): 4$' 60
    c wait:10000 shot:$S/90-mission-map.png tap:360:640 wait:3000 shot:$S/91-mission.png tap:515:714
    c wait:20000 shot:$S/92-story.png tap:115:1240 wait:2000 tap:515:742
    waitlog "$L" 'request UpdateTutorial (fid [0-9a-f]*): 6$' 120
    c wait:8000 shot:$S/93-companions.png tap:527:1090 wait:3000 shot:$S/94-go-home.png tap:60:1240
    waitlog "$L" 'port_debug: phase 4 ' 120
    waitlog "$L" 'request UpdateTutorial (fid [0-9a-f]*): 7$' 60
fi
# The 3.7.0 home tutorial (CHome, tutorial memId 8): the present-box message (次へ), then the
# gacha message (閉じる); the client then sends UpdateTutorial(9) (tutorial clear) and the popups
# the login armed open: the notice board (the local server's page).
home_tut=FAIL
if grep -q 'request UpdateTutorial (fid [0-9a-f]*): 7$' "$L"; then
    c wait:8000 shot:$S/95-home-tutorial.png tap:525:1085 wait:3000 shot:$S/96-home-tutorial-gacha.png tap:525:1090 || true
    if waitlog "$L" 'request UpdateTutorial (fid [0-9a-f]*): 9$' 60; then
        home_tut=ok
        c wait:8000 shot:$S/97-notice.png || true
    fi
fi
c wait:8000 shot:$S/99-last.png || true
state newplayer
grep -E 'port_debug: phase|request (Login|CreatePlayer|UpdateTutorial|MissionTalk|MissionStart|MissionEnd)' "$L" || true
c quit || true
wait $pid || true; pid=
trap - EXIT

# ---- checks ---------------------------------------------------------------------------------
grep -q 'port_debug: phase 4 ' "$OUT/seeded.log" || fail "the seeded player never reached home"
grep -q "CreatePlayer: LOCAL[0-9]* (${NEWPLAYER_NAME:-Claire})" "$L" || fail "the server didn't create the player \"${NEWPLAYER_NAME:-Claire}\""
grep -q 'port_debug: phase 4 ' "$L" || fail "the new player never reached home"
grep -q 'request UpdateTutorial (fid [0-9a-f]*): 7$' "$L" || fail "no UpdateTutorial(7): the tutorial didn't finish"
[ $home_tut = ok ] || fail "the home tutorial didn't finish (no UpdateTutorial 9)"
echo "PASS: seeded player -> home; new player \"${NEWPLAYER_NAME:-Claire}\" -> CreatePlayer -> tutorial -> home (UpdateTutorial 7) -> home tutorial (UpdateTutorial 9)"
