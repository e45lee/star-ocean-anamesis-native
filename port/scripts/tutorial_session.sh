#!/bin/sh
# The tutorial battle from a FRESH state (soa --server inproc, the 3.7.0 client): a data dir with
# no save (no shared_prefs/Game.xml) and no local-server state (no server.sqlite3), new-player mode
# (SOA_RESTORE_NEW_PLAYER=1: the server starts without a player). SOA_PHONE=DIR starts from a copy
# of a pre-downloaded phone (its saves removed); without it the client downloads its data after
# CreatePlayer's Login (port/scripts/phone370.sh). Flow:
#   title -> Login (error 19001) -> terms -> name entry -> CreatePlayer -> Login -> data check ->
#   tutorial opening (mc00_010 ...) -> the battle tutorial ms00_001 (the NPC party) -> ... -> home
#   (UpdateTutorial 7) -> the home tutorial (present box, gacha; UpdateTutorial 9)
# with CCharacterObject::OnDamage traced (SOA_TRACE), then checks:
#   - the server created the player (never seeded from a save);
#   - every hit's damage is finite and positive; the battle ended (MissionEnd) and home was reached;
#   - the milestones of tests/tutorial_milestones.txt (tools/compare_tutorial.py check port), the same
#     list emulator/scripts/emulator_session.sh --new-player checks against the 3.7.0 client.
# OUT keeps the log, one screenshot per round (fresh/lNNN.png) and the server's state
# (server.sqlite3) for the parity report: tools/compare_tutorial.py compare OUT EMU_OUT.
# (newplayer_session.sh runs a seeded player first and then this flow without the checks.)
#
# Usage: port/scripts/tutorial_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Prints "PASS: ..." or "FAIL: ..." and exits non-zero on failure.
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
export SOA_HEADLESS="${SOA_HEADLESS:-1}"  # soa --headless (no window); SOA_HEADLESS=0 to watch
CTL=control/soactl.py
rm -rf "${TMP:?}/fresh" "${OUT:?}/fresh" "${OUT:?}/fresh.log.pos"
mkdir -p "$OUT/fresh"
D=$TMP/fresh/data; FIFO=$TMP/fresh/fifo; L=$OUT/fresh.log; S=$OUT/fresh
# The phone: SOA_PHONE's pre-downloaded copy without its saves, else empty (the client downloads
# its data after CreatePlayer's Login); port/scripts/phone370.sh.
. port/scripts/phone370.sh
phone370_prepare "$D"
rm -f "$D/data/shared_prefs/Game.xml"
pid=
trap '[ -n "$pid" ] && kill $pid 2>/dev/null || true' EXIT
fail() { echo "FAIL: $*"; exit 1; }
c() { python3 $CTL --timeout 400 "$FIFO" "$@"; }
waitlog() {  # waitlog <pattern> [timeout s]
    i=0
    while ! grep -q "$1" "$L"; do
        sleep 1; i=$((i + 1))
        [ $i -ge "${2:-240}" ] && return 1
    done
    return 0
}

# ---- a fresh state --------------------------------------------------------------------------
[ ! -e "$D/server.sqlite3" ] || fail "the data dir $D has a server state"
# SOA_TRACE on CCharacterObject::OnDamage: every hit's damage (its s0), as the emulator's
# --new-player session traces it (tools/compare_tutorial.py)
SDL_AUDIODRIVER=${SDL_AUDIODRIVER:-dummy} SOA_RESTORE_NEW_PLAYER=1 SOA_SERVER_SEED_RNG=1 \
    SOA_TRACE=_ZN16CCharacterObject8OnDamageERKN24IAttackCollisionCallback23CallbackArgument_DamageEfb \
    timeout -k 10 3600 "$SOA" --data "$D" --size 729x1296 --control "$FIFO" > "$L" 2>&1 &
pid=$!
while [ ! -p "$FIFO" ]; do sleep 1; done
waitlog 'port_debug: phase 1 ' || fail "the title never came up"
grep -q 'seeding from' "$L" && fail "the server seeded a player from a save (not a fresh state)"

# ---- title -> new player ----------------------------------------------------------------------
c wait:8000 shot:$S/01-title.png
n=0
until waitlog 'error 19001' 10; do  # a tap during the title's fade-in is sometimes ignored
    c tap:364:970 > /dev/null; n=$((n + 1)); [ $n -ge 6 ] && fail "the title tap never led to Login / error 19001"
done
c wait:3000 shot:$S/02-terms.png tap:364:689 wait:3000 shot:$S/03-name.png
# The name: tap the field until the keyboard opens, type, 決定; checks CreatePlayer's name.
python3 control/flowctl.py name-entry "$FIFO" "$L" "${NEWPLAYER_NAME:-Claire}" $S/04-name-typed.png || fail "the name entry failed"
waitlog "CreatePlayer: LOCAL[0-9]* (${NEWPLAYER_NAME:-Claire})" 30 || fail "the server didn't create the player \"${NEWPLAYER_NAME:-Claire}\""
# Login, then the 3.7.0 client's data check (or download) before the opening scene (phase 3).
phone370_data "$FIFO" "$L" "$S" 'port_debug: phase 3 '
waitlog 'port_debug: phase 3 ' 300 || fail "the tutorial opening never started"

# ---- tutorial + battle (same taps as newplayer_session.sh) ----------------------------------
c wait:15000 shot:$S/05-opening.png tap:612:1240 wait:1000 tap:115:45 wait:1000 || true
i=0; shot_battle=
while [ $i -lt "${TUTORIAL_STEPS:-200}" ]; do
    c wait:6000 shot:$S/l$(printf %03d $i).png > /dev/null || true
    if [ -z "$shot_battle" ] && grep -q 'I/trace: _ZN16CCharacterObject8OnDamage' "$L"; then shot_battle=$S/l$(printf %03d $i).png; fi
    c tap:364:506 wait:400 tap:364:562 wait:400 tap:527:1090 wait:400 tap:527:785 wait:400 tap:527:697 wait:400 \
      tap:175:890 wait:300 tap:440:430 wait:300 tap:650:1005 wait:300 tap:505:1075 wait:300 tap:450:1215 > /dev/null || true
    i=$((i + 1))
    grep -q 'port_debug: phase 4 ' "$L" && break
    grep -q 'request UpdateTutorial (fid [0-9a-f]*): 4$' "$L" && break
done
if ! grep -q 'port_debug: phase 4 ' "$L"; then  # the mission-menu step, then home
    waitlog 'request UpdateTutorial (fid [0-9a-f]*): 4$' 60 || fail "the tutorial never reached the mission-menu step"
    c wait:10000 shot:$S/90-mission-map.png tap:360:640 wait:3000 shot:$S/91-mission.png tap:515:714
    c wait:20000 shot:$S/92-story.png tap:115:1240 wait:2000 tap:515:742
    waitlog 'request UpdateTutorial (fid [0-9a-f]*): 6$' 120 || fail "no UpdateTutorial(6)"
    c wait:8000 shot:$S/93-companions.png tap:527:1090 wait:3000 shot:$S/94-go-home.png tap:60:1240
    waitlog 'port_debug: phase 4 ' 120 || fail "home was never reached"
fi
waitlog 'request UpdateTutorial (fid [0-9a-f]*): 7$' 60 || fail "no UpdateTutorial(7)"
# the 3.7.0 home tutorial: 次へ (present box), 閉じる (gacha) -> UpdateTutorial(9)
c wait:8000 shot:$S/95-home-tutorial.png tap:525:1085 wait:3000 shot:$S/96-home-tutorial-gacha.png tap:525:1090 || true
waitlog 'request UpdateTutorial (fid [0-9a-f]*): 9$' 60 || fail "the home tutorial didn't finish (no UpdateTutorial(9))"
c wait:5000 shot:$S/99-home.png || true
c quit || true
wait $pid || true; pid=; trap - EXIT
.venv/bin/python tools/server_state.py "$D/server.sqlite3" > "$OUT/state-fresh.txt" 2>/dev/null || true
# a copy of the server's state for tools/compare_tutorial.py compare
python3 -c 'import sqlite3, sys; sqlite3.connect(sys.argv[1]).backup(sqlite3.connect(sys.argv[2]))' "$D/server.sqlite3" "$OUT/server.sqlite3" || true

# ---- checks ---------------------------------------------------------------------------------
grep -q 'request MissionStart' "$L" || fail "no MissionStart (the tutorial battle never started)"
grep -q 'request MissionEnd' "$L" || fail "no MissionEnd (the tutorial battle didn't finish)"
# Every hit's damage: CCharacterObject::OnDamage's s0 (SOA_TRACE), as emulator_session.sh
# --new-player traces it (the battle natives' SOA_BATTLE_DAMAGE_LOG is gone with them).
hits=$(grep -c "I/trace: _ZN16CCharacterObject8OnDamage.* s0=" "$L" || true)
[ "$hits" -gt 0 ] || fail "no damage was traced (SOA_TRACE CCharacterObject::OnDamage)"
# (the damage is the call's s0 argument, inside the parentheses; the s0 after "->" is the result)
dmg() { grep "I/trace: _ZN16CCharacterObject8OnDamage" "$L" | grep -o '(x0=[^)]*)' | grep -o ' s0=[^ )]*' | cut -d= -f2; }
bad=$(dmg | awk '{v=$1+0; if (!(v>0) || v>1e7 || $1 ~ /nan|inf/) n++} END {print n+0}')
[ "$bad" -eq 0 ] || fail "$bad hits with a non-positive or non-finite damage"
# the shared milestone list (tests/tutorial_milestones.txt; emulator_session.sh --new-player checks
# the same against the unmodified 3.7.0 client)
python3 tools/compare_tutorial.py check port "$OUT" --name "${NEWPLAYER_NAME:-Claire}" > "$OUT/milestones.txt" 2>&1 ||
    fail "tutorial milestones: $(grep '^FAIL  ' "$OUT/milestones.txt" | head -3 | tr '\n' ';')"
range=$(dmg | awk '{v=$1+0; if (min==""||v<min) min=v; if (v>max) max=v} END {printf "%.0f..%.0f", min, max}')
echo "PASS: fresh state -> CreatePlayer \"${NEWPLAYER_NAME:-Claire}\" -> tutorial battle ms00_001 ($hits hits, damage $range) -> home (UpdateTutorial 7) -> home tutorial (UpdateTutorial 9); $(grep -c '^PASS  ' "$OUT/milestones.txt") tutorial milestones${shot_battle:+; battle shot $shot_battle}"
