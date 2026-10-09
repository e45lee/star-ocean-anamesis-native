#!/bin/bash
# Runs the desktop port (build/port/soa) with its own network code against the local game server
# (build/server/soa-server), which this script starts and stops: the port's --server HOST mode,
# the same setup as scripts/run-emulator-370.sh with soa in place of soa-emu.
#
# Usage: scripts/run-port-with-server.sh [options]   (from any directory)
#   --home DIR         where the port's phone and the server keep their data
#                      (default ~/.local/share/soa-port-server-370: phone/ and server/)
#   --port N           the game server's port (default 44310); its HTTP/CDN port is N+80
#   --server-log       show soa-server's log on the terminal too (it always goes to DIR/server.log)
#   server options, passed to soa-server (they set the server's rules and state, as soa's own):
#     --new-player, --seed FILE, --seed-rng N, --clock "YYYY-MM-DD HH:MM:SS", --start-coins N, --gacha-surprise PCT,
#     --stamina-heal-time S, --galaxy-pass, --enable-events, --event-keywords L, --restore-tower,
#     --english, --master FILE, --db FILE, --log-packets DIR, --fail M:CODE[,..], --surprise,
#     --campaign-master-db FILE, --campaign-seed LABEL
#   any other options go to soa, e.g. --fullscreen, --size 729x1296, --headless (soa --help)
#
# The first start downloads the game data (about 3 GB) from the local server into the phone's data.
# Ctrl-C (or the game window closing) stops both programs.
# Needs: scripts/build.sh, apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk, work/SOA-3.7.0-canonical-data.zip and
# data/basmaster-3.7.0.sqlite3 (README.md, "Game files").
set -euo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
. "$repo/scripts/lib/with-server.sh"
ws_init run-port-with-server
soa=$repo/build/port/soa
srv=$repo/build/server/soa-server
home=${HOME:-.}/.local/share/soa-port-server-370
port=44310
server_log_to_tty=0
soa_args=()
while [ $# -gt 0 ]; do
  case "$1" in
    -h|--help) sed -n '2,21p' "$0" | sed 's/^# \{0,1\}//'; exit 0;;
    --home) ws_need "$@"; home=$2; shift 2;;
    --port) ws_need "$@"; port=$2; shift 2;;
    --server-log) server_log_to_tty=1; shift;;
    --server|--http) echo "run-port-with-server: $1 is set by this script (see --port)" >&2; exit 2;;
    *) if ws_server_option "$@"; then shift "$ws_taken"; else soa_args+=("$1"); shift; fi;;
  esac
done
ws_check_port "$port"
http_port=$((port + 80))

for f in "$soa" "$srv"; do
  [ -x "$f" ] || { echo "run-port-with-server: $f isn't built; run scripts/build.sh first" >&2; exit 1; }
done
for f in "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk" data/basmaster-3.7.0.sqlite3; do
  [ -s "$repo/$f" ] || { echo "run-port-with-server: $f is missing; see README.md" >&2; exit 1; }
done
[ -f "$repo/work/SOA-3.7.0-canonical-data.zip" ] || { echo "run-port-with-server: work/SOA-3.7.0-canonical-data.zip (the 3.7.0 download) is missing; see README.md" >&2; exit 1; }

mkdir -p "$home/phone" "$home/server"
home=$(cd "$home" && pwd)
cd "$repo"  # soa and soa-server find the master DB and the seeds from the checkout
echo "== starting soa-server (game 127.0.0.1:$port, http 127.0.0.1:$http_port; data $home/server)"
ws_start_server "$home/server.log" "$server_log_to_tty" "$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port \
    --data "$home/server" --download-dir "$repo/work/SOA-3.7.0-canonical-data.zip" ${ws_srv_args[@]+"${ws_srv_args[@]}"}
ws_wait_ready
echo "== starting soa --server 127.0.0.1:$port (phone data $home/phone)"
ws_run_client "$soa" --data "$home/phone" --server 127.0.0.1:$port --http 127.0.0.1:$http_port ${soa_args[@]+"${soa_args[@]}"}
