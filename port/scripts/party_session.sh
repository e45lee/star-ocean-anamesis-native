#!/bin/sh
# Scripted session of the restored party screen (the in-process local server): boot -> home -> the
# footer's Character menu (3.7.0 CPartyComposition) -> Party (party set 1) -> Change members ->
# slot 1 := the 6th character of the list (sorted by rarity) -> Back, which saves the set with
# UpdatePartySet to the local server -> swipe to set 2, change and save it too -> home -> a
# battle (mf01_001 through the `mission:` / `phase:0xf` route) whose MissionStart takes the set
# saved last (set 2). Also changes the home character (お気に入り, UpdateHome).
# Screenshots go to OUT/shots, the server's party table to OUT/state-*.txt, the log to
# OUT/log.txt. The script checks that the saved set reaches MissionStart; exit status 1 if not.
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/party_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
HEADLESS=--headless; [ "${WATCH:-0}" != 1 ] || HEADLESS=--windowed  # soa --headless (no window); WATCH=1 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos" "${OUT:?}"/state-*.txt
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
timeout -k 10 2400 "$SOA" $HEADLESS --seed-rng "${SEED_RNG:-1}" --data "$TMP/data" \
  --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
# tapw REGEX TIMEOUT EVERY TRIES -- CMD...: the commands, resent until REGEX is logged (flowctl.py
# tap-until: for taps the game drops under load).
tapw() { python3 $FLOW tap-until "$TMP/fifo" "$L" "$@"; }
party() { .venv/bin/python - "$TMP/data/server.sqlite3" <<'PY'
import sqlite3, sys
c = sqlite3.connect(sys.argv[1])
print("player.party_id", c.execute("select party_id from player").fetchone()[0])
for r in c.execute("select p.party_id, p.slot, p.uid, r.role_id from party p left join roster r on r.uid = p.uid order by 1, 2"): print("party", *r)
PY
}

# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S"
# The restored 3.7.0 login opens the notice popup over home, then the LOGIN BONUS popup of the
# day's first login (the server grants the day on the title's NoLoginStart and reports it again on
# the Login; the 3.7.0 login arms the popups): flowctl.py login-popups closes both (閉じる), retried
# until they're gone.
python3 $FLOW login-popups "$TMP/fifo" "$L" $S/02-notice.png $S/02-login-bonus.png $S/02-home.png
party > "$OUT/state-1-boot.txt"; cat "$OUT/state-1-boot.txt"

# Footer "キャラクター" -> CPhase_PartyComposition (0xb), the 3.7.0 character menu.
tapw 'port_debug: phase 11 ' 120 20 3 -- tap:180:1245
c wait:6000 shot:$S/03-character-menu.png
# "パーティ編成": party set 1.
c tap:364:325 wait:6000 shot:$S/04-party-top.png
# "メンバー変更": member select with the owned-character list.
c tap:620:1120 wait:5000 shot:$S/05-member-select.png
# Slot 1, then the first character of the list's second row.
c tap:212:325 wait:1500 tap:95:725 wait:2500 shot:$S/06-member-changed.png
# "戻る" saves the set (UpdatePartySet) and returns to the party top.
c tap:100:1120; logw 'UpdatePartySet: party 1 ' 30
c wait:4000 shot:$S/07-party-saved.png
party > "$OUT/state-2-saved.txt"; cat "$OUT/state-2-saved.txt"
# Swipe to party set 2 (2/10), change its slot 1 to the second character of the list's second
# row and save it: the last saved set becomes the current party.
c drag:600:600:150:600 wait:3000 shot:$S/08-party-2.png
c tap:620:1120 wait:5000 tap:212:325 wait:1500 tap:230:725 wait:2500 shot:$S/09-party-2-changed.png
c tap:100:1120; logw 'UpdatePartySet: party 2 ' 30
c wait:4000 shot:$S/10-party-2-saved.png
party > "$OUT/state-3-saved-2.txt"; cat "$OUT/state-3-saved-2.txt"
# "戻る" to the character menu, footer "ホーム".
c tap:100:1120 wait:4000 shot:$S/11-character-menu.png
tapw 'port_debug: phase 4 ' 60 20 3 -- tap:60:1245
c wait:6000 shot:$S/12-home.png

# Home character: interactive mode -> "お気に入り変更" (the restored 3.7.0 CAdjutantSelect, owned
# characters) -> the third one -> UpdateHome to the local server -> the home shows it.
c tap:90:740 wait:5000 tap:180:1245 wait:5000 shot:$S/12a-favorite-select.png
c tap:362:330; logw 'UpdateHome: ' 30
c wait:3000 shot:$S/12b-favorite-changed.png tap:364:800 wait:5000 shot:$S/12c-home-new-favorite.png
c tap:60:1245 wait:5000

# Battle: MissionStart takes the player's current party (the set just saved).
c mission:${FLOW_MISSION:-mf01_001} phase:0xf; logw 'port_debug: phase 15 '
logw 'MissionStart mission' 60
c wait:25000 shot:$S/13-battle.png wait:8000 shot:$S/14-battle.png
c quit
wait $pid || true
trap - EXIT

# Set 1 keeps its edit; set 2 (saved last, so current) must be what MissionStart sends.
uid1=$(grep '^party 1 0 ' "$OUT/state-3-saved-2.txt" | awk '{print $4}')
uid2=$(grep '^party 2 0 ' "$OUT/state-3-saved-2.txt" | awk '{print $4}')
cur=$(grep '^player.party_id ' "$OUT/state-3-saved-2.txt" | awk '{print $2}')
echo "saved: set 1 slot 0 uid $uid1, set 2 slot 0 uid $uid2, current set $cur"
grep -E 'UpdatePartySet: party|MissionStart mission|MissionStart party member' "$L"
ok=1
[ "$uid1" = "$(grep '^party 1 0 ' "$OUT/state-2-saved.txt" | awk '{print $4}')" ] || { echo "FAIL: set 1 changed"; ok=0; }
[ "$cur" = 2 ] || { echo "FAIL: current party is $cur, not 2"; ok=0; }
grep -q "MissionStart party member 0: uid $uid2" "$L" || { echo "FAIL: MissionStart didn't use set 2 (uid $uid2)"; ok=0; }
[ $ok = 1 ] && echo "PASS: the battle uses the saved party" || exit 1
