#!/bin/bash
# Runs the 3.7.0 online client, unmodified, in the emulator (build/emulator/soa-emu) against the
# local game server (build/server/soa-server), which this script starts and stops.
#
# Usage: scripts/run-emulator-370.sh [options]   (from any directory)
#   --home DIR         where the emulated phone and the server keep their data
#                      (default ~/.local/share/soa-emulator-370: phone/ and server/, beside the
#                      port's ~/.local/share/soa-linux-370)
#   --port N           the game server's port (default 44300); its HTTP/CDN port is N+80
#   --server-log       show soa-server's log on the terminal too (it always goes to DIR/server.log)
#   server options, passed to soa-server (they set the server's rules and state):
#     --new-player (a fresh account: terms, name, tutorial), --seed FILE (seed a NEW server state
#     from this save, a 3.7.0 or offline-game Game.xml; default data/saves/seed/Game.xml; an
#     existing state in --home keeps its player), --enable-events (open the events matching
#     --event-keywords all year, as the port), --event-keywords L (default: the summer events),
#     --seed-rng N, --clock "YYYY-MM-DD HH:MM:SS", --start-coins N, --stamina-heal-time S,
#     --galaxy-pass, --restore-tower, --english, --master FILE, --db FILE, --log-packets DIR,
#     --fail M:CODE[,..], --surprise, --campaign-master-db FILE, --campaign-seed LABEL
#   any other options go to soa-emu, e.g. --fullscreen, --size 729x1296 (soa-emu --help)
#
# The first start downloads the game data (about 3 GB) from the local server into the phone's data.
# Needs: scripts/build.sh, apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk, work/libSOA-3.7.0.so,
# work/SOA-3.7.0-canonical-data.zip and data/basmaster-3.7.0.sqlite3 (README.md, "Game files").
set -euo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
. "$repo/scripts/lib/with-server.sh"
ws_init run-emulator-370
emu=$repo/build/emulator/soa-emu
srv=$repo/build/server/soa-server
home=${HOME:-.}/.local/share/soa-emulator-370
port=44300
server_log_to_tty=0
emu_args=()
while [ $# -gt 0 ]; do
  case "$1" in
    -h|--help) sed -n '2,23p' "$0" | sed 's/^# \{0,1\}//'; exit 0;;
    --home) ws_need "$@"; home=$2; shift 2;;
    --port) ws_need "$@"; port=$2; shift 2;;
    --server-log) server_log_to_tty=1; shift;;
    --server|--http) echo "run-emulator-370: $1 is set by this script (see --port)" >&2; exit 2;;
    *) if ws_server_option "$@"; then shift "$ws_taken"; else emu_args+=("$1"); shift; fi;;
  esac
done
ws_check_port "$port"
http_port=$((port + 80))

for f in "$emu" "$srv"; do
  [ -x "$f" ] || { echo "run-emulator-370: $f isn't built; run scripts/build.sh first" >&2; exit 1; }
done
for f in work/libSOA-3.7.0.so "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk" data/basmaster-3.7.0.sqlite3; do
  [ -s "$repo/$f" ] || { echo "run-emulator-370: $f is missing; see README.md" >&2; exit 1; }
done
[ -f "$repo/work/SOA-3.7.0-canonical-data.zip" ] || { echo "run-emulator-370: work/SOA-3.7.0-canonical-data.zip (the 3.7.0 download) is missing; see README.md" >&2; exit 1; }

mkdir -p "$home/phone" "$home/server"
home=$(cd "$home" && pwd)
echo "== starting soa-server (game 127.0.0.1:$port, http 127.0.0.1:$http_port; data $home/server)"
ws_start_server "$home/server.log" "$server_log_to_tty" "$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port \
    --data "$home/server" --download-dir "$repo/work/SOA-3.7.0-canonical-data.zip" ${ws_srv_args[@]+"${ws_srv_args[@]}"}
ws_wait_ready
echo "== starting soa-emu (phone data $home/phone)"
ws_run_client "$emu" --data "$home/phone" --server 127.0.0.1:$port --http 127.0.0.1:$http_port ${emu_args[@]+"${emu_args[@]}"}
