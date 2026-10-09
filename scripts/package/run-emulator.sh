#!/bin/bash
# Release package launcher (Linux): runs the original 3.7.0 client, unmodified, in the emulator
# (./soa-emu) against the local game server (./soa-server), which this script starts and stops.
# Both find the game files beside them or in ./game (README.txt).
#
# Usage: ./run-emulator.sh [options]
#   --home DIR         where the emulated phone and the server keep their data
#                      (default ~/.local/share/soa-emulator-370: phone/ and server/)
#   --port N           the game server's port (default 44300); its HTTP/CDN port is N+80
#   --server-log       show soa-server's log on the terminal too (it always goes to HOME/server.log)
#   server options, passed to soa-server (they set the server's rules and state):
#     --new-player (a fresh account: terms, name, tutorial), --seed FILE (seed a NEW server state
#     from this save, a 3.7.0 or offline Game.xml), --enable-events (open the events matching
#     --event-keywords all year), --event-keywords L (default: the summer events), --english (the
#     English files; with soa-emu's --lang en: the English game, as run-emulator-en.sh does),
#     --seed-rng N, --clock "YYYY-MM-DD HH:MM:SS", --start-coins N, --gacha-surprise PCT, --stamina-heal-time S,
#     --galaxy-pass, --restore-tower, --download PATH, --master FILE, --db FILE, --log-packets DIR
#   any other options go to soa-emu, e.g. --fullscreen (./soa-emu --help)
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
. "$here/lib/with-server.sh"
ws_init run-emulator
home=${HOME:-.}/.local/share/soa-emulator-370
port=44300
server_log_to_tty=0
emu_args=()
while [ $# -gt 0 ]; do
  case "$1" in
    -h|--help) sed -n '2,18p' "$0" | sed 's/^# \{0,1\}//'; exit 0;;
    --home) ws_need "$@"; home=$2; shift 2;;
    --port) ws_need "$@"; port=$2; shift 2;;
    --server-log) server_log_to_tty=1; shift;;
    --server|--http) echo "run-emulator: $1 is set by this script (see --port)" >&2; exit 2;;
    *) if ws_server_option "$@"; then shift "$ws_taken"; else emu_args+=("$1"); shift; fi;;
  esac
done
ws_check_port "$port"
http_port=$((port + 80))

mkdir -p "$home/phone" "$home/server"
home=$(cd "$home" && pwd)
echo "== starting soa-server (game 127.0.0.1:$port, http 127.0.0.1:$http_port; data $home/server)"
ws_start_server "$home/server.log" "$server_log_to_tty" "$here/soa-server" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port \
    --data "$home/server" ${ws_srv_args[@]+"${ws_srv_args[@]}"}
ws_wait_ready
echo "== starting soa-emu (phone data $home/phone)"
ws_run_client "$here/soa-emu" --data "$home/phone" --server 127.0.0.1:$port --http 127.0.0.1:$http_port ${emu_args[@]+"${emu_args[@]}"}
