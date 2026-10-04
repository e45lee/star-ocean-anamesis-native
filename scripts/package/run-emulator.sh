#!/bin/bash
# Release package launcher (Linux): runs the original 3.7.0 client, unmodified, in the emulator
# (./soa-emu) against the local game server (./soa-server), which this script starts and stops.
# Both find the game files beside them or in ./game (README.txt).
#
# Usage: ./run-emulator.sh [options]
#   --home DIR         where the emulated phone and the server keep their data
#                      (default ~/.local/share/soa-emulator-370: phone/ and server/)
#   --new-player       start the server without a player (a fresh account: terms, name, tutorial)
#   --seed FILE        seed a NEW server state from this save (a 3.7.0 or offline Game.xml)
#   --enable-events    open the events matching --event-keywords all year
#   --event-keywords L names to match (default: the summer events)
#   --port N           the game server's port (default 44300); its HTTP/CDN port is N+80
#   --server-log       show soa-server's log on the terminal instead of HOME/server.log
#   any other options go to soa-emu, e.g. --fullscreen (./soa-emu --help)
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
emu=$here/soa-emu
srv=$here/soa-server
home=${HOME:-.}/.local/share/soa-emulator-370
port=44300
server_log_to_tty=0
srv_args=() emu_args=()
while [ $# -gt 0 ]; do
  case "$1" in
    -h|--help) sed -n '2,17p' "$0" | sed 's/^# \{0,1\}//'; exit 0;;
    --home) home=$2; shift 2;;
    --port) port=$2; shift 2;;
    --new-player|--enable-events) srv_args+=("$1"); shift;;
    --event-keywords|--seed) srv_args+=("$1" "$2"); shift 2;;
    --server-log) server_log_to_tty=1; shift;;
    *) emu_args+=("$1"); shift;;
  esac
done
http_port=$((port + 80))

mkdir -p "$home/phone" "$home/server"
slog=$home/server.log
echo "== starting soa-server (game 127.0.0.1:$port, http 127.0.0.1:$http_port; data $home/server)"
if [ $server_log_to_tty = 1 ]; then
  "$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port --data "$home/server" ${srv_args[@]+"${srv_args[@]}"} > >(tee "$slog") 2>&1 &
else
  "$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port --data "$home/server" ${srv_args[@]+"${srv_args[@]}"} > "$slog" 2>&1 &
fi
spid=$!
epid=
cleanup() {
  [ -n "$epid" ] && kill "$epid" 2>/dev/null || true
  kill "$spid" 2>/dev/null || true
  wait 2>/dev/null || true
}
trap cleanup EXIT
trap 'exit 130' INT TERM

# Wait until it listens (the first start decrypts the master and builds the CDN: up to a minute).
for _ in $(seq 1 480); do
  grep -q "^soa-server: game" "$slog" 2>/dev/null && break
  kill -0 "$spid" 2>/dev/null || { echo "run-emulator: soa-server exited (see README.txt); log: $slog" >&2; tail -5 "$slog" >&2; exit 1; }
  sleep 0.5
done
grep -q "^soa-server: game" "$slog" || { echo "run-emulator: soa-server didn't start; log: $slog" >&2; exit 1; }
grep -q "^soa-server: CDN" "$slog" || { echo "run-emulator: soa-server found no 3.7.0 download (see README.txt); log: $slog" >&2; exit 1; }

echo "== starting soa-emu (phone data $home/phone)"
"$emu" --data "$home/phone" --server 127.0.0.1:$port --http 127.0.0.1:$http_port ${emu_args[@]+"${emu_args[@]}"} &
epid=$!
wait "$epid"
