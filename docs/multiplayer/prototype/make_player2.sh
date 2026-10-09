#!/bin/bash
# Player 2 for the two-client experiment: a soa-server state DB seeded like the default LOCAL00001
# player, then made a different player (sanitized ids only):
#   - player.id 1000000002 (a synthetic numeric id: the co-op client compares numeric player ids,
#     README "Who is host"), search id LOCAL00002, name Player2;
#   - party 1's leader = the roster's role whose label starts with LEADER_LABEL (default
#     role_cp0204: Ashton), so the room and the battle show a different character from player 1's.
# Usage: make_player2.sh OUT_DB [LEADER_LABEL]
# Env: SOA_SERVER, MASTER as mp_client.sh.
set -eu
out_db=${1:?OUT_DB}; label=${2:-role_cp0204}
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../../.." && pwd)
srv=${SOA_SERVER:-$repo/build/server/soa-server}
master=${MASTER:-$repo/data/basmaster-3.7.0.sqlite3}
tmp=$(mktemp -d)
read -r port hport < <("$repo/tools/py" -c '
import socket
s = [socket.socket() for _ in range(2)]
for x in s: x.bind(("127.0.0.1", 0))
print(*[x.getsockname()[1] for x in s])')
"$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$hport --data "$tmp" --master "$master" \
    --campaign-seed mf01_001 > "$tmp/log" 2>&1 &
pid=$!
for _ in $(seq 1 120); do grep -q "^soa-server: game" "$tmp/log" 2>/dev/null && break; sleep 0.5; done
# a client session (bridge, Login, ...) makes the server seed its state
"$srv" --wire-tool session 127.0.0.1:$port 00000000-0000-0000-0000-000000000002 127.0.0.1:$hport > "$tmp/session.log" 2>&1 || true
kill $pid; wait $pid 2>/dev/null || true
db=$tmp/server.sqlite3
uid=$(sqlite3 "$db" "attach '$master' as m; select r.uid from roster r join m.master_role mr on mr.id = r.role_id
                     where mr.id_label like '$label%' order by r.level desc limit 1")
[ -n "$uid" ] || { echo "no roster role $label"; exit 1; }
sqlite3 "$db" "update player set id = 1000000002, search_id = 'LOCAL00002', name = 'Player2';
               delete from wire_device;
               delete from party where party_id = 1 and uid = $uid;
               update party set uid = $uid where party_id = 1 and slot = 0;"
cp "$db" "$out_db"
rm -rf "${tmp:?}"
echo "player 2: $out_db (leader uid $uid, $label)"
