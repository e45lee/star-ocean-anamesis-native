#!/bin/bash
# Release package launcher (Linux): runs the desktop port (./soa) with its own network code against
# the local game server running as a separate program (./soa-server), which this script starts
# first and stops when soa exits (also on Ctrl-C). Both find the game files beside them or in
# ./game (README.txt). run-port.sh (the server inside soa) stays the usual way to play.
#
# Usage: ./run-port-server.sh [options]
#   --data DIR         soa's data dir, as soa --data (default ~/.local/share/soa-linux-370, the
#                      same as run-port.sh: the phone's data and save); the server keeps its state
#                      in DIR/server/ and logs into DIR/server.log
#   --port N           the game server's port (default 44310); its HTTP/CDN port is N+80
#   --server-log       show soa-server's log on the terminal too (it always goes to DIR/server.log)
#   server options, passed to soa-server (they set the server's rules and state):
#     --new-player, --seed FILE, --seed-rng N, --clock "YYYY-MM-DD HH:MM:SS", --start-coins N, --gacha-surprise PCT,
#     --stamina-heal-time S, --galaxy-pass, --enable-events, --event-keywords L, --restore-tower,
#     --download PATH, --master FILE, --db FILE, --log-packets DIR, --fail M:CODE[,..], --surprise,
#     --english (the English files: with --lang en for soa, the English game)
#   any other options go to soa, e.g. --fullscreen, --size 729x1296, --apk FILE (./soa --help)
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
. "$here/lib/with-server.sh"
ws_init run-port-server
data=${HOME:-.}/.local/share/soa-linux-370
port=44310
server_log_to_tty=0
soa_args=()
while [ $# -gt 0 ]; do
  case "$1" in
    -h|--help) sed -n '2,18p' "$0" | sed 's/^# \{0,1\}//'; exit 0;;
    --data) ws_need "$@"; data=$2; shift 2;;
    --port) ws_need "$@"; port=$2; shift 2;;
    --server-log) server_log_to_tty=1; shift;;
    --server|--http) echo "run-port-server: $1 is set by this script (see --port)" >&2; exit 2;;
    *) if ws_server_option "$@"; then shift "$ws_taken"; else soa_args+=("$1"); shift; fi;;
  esac
done
ws_check_port "$port"
http_port=$((port + 80))

mkdir -p "$data/server"
data=$(cd "$data" && pwd)
# --seed: a new server state takes the player of the phone's save, as soa's in-process server does
# with the same data dir (a save without a player, the client's first settings-only one, is skipped
# with a warning); a --seed among the user's options comes later and wins
ws_start_server "$data/server.log" "$server_log_to_tty" "$here/soa-server" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port \
    --data "$data/server" --seed "$data/data/shared_prefs/Game.xml" ${ws_srv_args[@]+"${ws_srv_args[@]}"}
echo "== soa-server (pid $ws_spid): game 127.0.0.1:$port, http 127.0.0.1:$http_port; state $data/server, log $ws_slog"
ws_wait_ready
echo "== soa --server 127.0.0.1:$port; data $data"
ws_run_client "$here/soa" --data "$data" --server 127.0.0.1:$port --http 127.0.0.1:$http_port ${soa_args[@]+"${soa_args[@]}"}
