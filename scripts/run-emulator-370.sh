#!/bin/bash
# Runs the 3.7.0 online client, unmodified, in the emulator (build/emulator/soa-emu) against the
# local game server (build/server/soa-server), which this script starts and stops.
#
# Usage: scripts/run-emulator-370.sh [options]
#   --home DIR         where the emulated phone and the server keep their data
#                      (default ~/.local/share/soa-emulator-370: phone/ and server/, beside the
#                      port's ~/.local/share/soa-linux)
#   --new-player       start the server without a player (a fresh account: terms, name, tutorial)
#   --seed FILE        seed a NEW server state from this save (a 3.7.0 or offline-game Game.xml, e.g. your
#                      offline game's shared_prefs/Game.xml; default data/saves/seed/Game.xml);
#                      an existing state in --home keeps its player
#   --enable-events    open the events matching --event-keywords all year (as the port)
#   --event-keywords L names to match (default: the summer events)
#   --port N           the game server's port (default 44300); its HTTP/CDN port is N+80
#   --server-log       show soa-server's log on the terminal instead of DIR/server.log
#   any other options go to soa-emu, e.g. --fullscreen, --size 729x1296 (soa-emu --help)
#
# The first start downloads the game data (about 3 GB) from the local server into the phone's data.
# Needs: scripts/build.sh, apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk, work/libSOA-3.7.0.so,
# work/SOA-3.7.0-canonical-data.zip and data/basmaster-3.7.0.sqlite3 (README.md, "Game files").
set -euo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
emu=$repo/build/emulator/soa-emu
srv=$repo/build/server/soa-server

home=${HOME:-.}/.local/share/soa-emulator-370
port=44300
server_log_to_tty=0
srv_args=() emu_args=()
while [ $# -gt 0 ]; do
  case "$1" in
    -h|--help) sed -n '2,23p' "$0" | sed 's/^# \{0,1\}//'; exit 0;;
    --home) home=$2; shift 2;;
    --port) port=$2; shift 2;;
    --new-player|--enable-events) srv_args+=("$1"); shift;;
    --event-keywords|--seed) srv_args+=("$1" "$2"); shift 2;;
    --server-log) server_log_to_tty=1; shift;;
    *) emu_args+=("$1"); shift;;
  esac
done
http_port=$((port + 80))

for f in "$emu" "$srv"; do
  [ -x "$f" ] || { echo "run-emulator-370: $f isn't built; run scripts/build.sh first" >&2; exit 1; }
done
for f in work/libSOA-3.7.0.so "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk" data/basmaster-3.7.0.sqlite3; do
  [ -s "$repo/$f" ] || { echo "run-emulator-370: $f is missing; see README.md" >&2; exit 1; }
done
[ -f "$repo/work/SOA-3.7.0-canonical-data.zip" ] || { echo "run-emulator-370: work/SOA-3.7.0-canonical-data.zip (the 3.7.0 download) is missing; see README.md" >&2; exit 1; }

mkdir -p "$home/phone" "$home/server"
slog=$home/server.log
echo "== starting soa-server (game 127.0.0.1:$port, http 127.0.0.1:$http_port; data $home/server)"
if [ $server_log_to_tty = 1 ]; then
  "$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port --data "$home/server" \
      --download-dir "$repo/work/SOA-3.7.0-canonical-data.zip" "${srv_args[@]}" > >(tee "$slog") 2>&1 &
else
  "$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port --data "$home/server" \
      --download-dir "$repo/work/SOA-3.7.0-canonical-data.zip" "${srv_args[@]}" > "$slog" 2>&1 &
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

# Wait until it listens (the first start builds the CDN, a few seconds).
for _ in $(seq 1 240); do
  grep -q "^soa-server: game" "$slog" 2>/dev/null && break
  kill -0 "$spid" 2>/dev/null || { echo "run-emulator-370: soa-server exited; log: $slog" >&2; tail -5 "$slog" >&2; exit 1; }
  sleep 0.5
done
grep -q "^soa-server: game" "$slog" || { echo "run-emulator-370: soa-server didn't start; log: $slog" >&2; exit 1; }

echo "== starting soa-emu (phone data $home/phone)"
# In the background so Ctrl-C / a kill of this script reaches the trap, which stops both.
"$emu" --data "$home/phone" --server 127.0.0.1:$port --http 127.0.0.1:$http_port "${emu_args[@]}" &
epid=$!
wait "$epid"
