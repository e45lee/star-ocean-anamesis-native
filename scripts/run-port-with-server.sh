#!/bin/bash
# Runs the desktop port (build/port/soa) with its own network code against the local game server
# (build/server/soa-server), which this script starts and stops: the port's --server HOST mode,
# the same setup as scripts/run-emulator-370.sh with soa in place of soa-emu.
#
# Usage: scripts/run-port-with-server.sh [options]   (from any directory)
#   --home DIR         where the port's phone and the server keep their data
#                      (default ~/.local/share/soa-port-server-370: phone/ and server/)
#   --port N           the game server's port (default 44310); its HTTP/CDN port is N+80
#   --server-log       show soa-server's log on the terminal instead of DIR/server.log
#   --log-packets DIR  soa-server logs every request and reply into DIR
#   server options, passed to soa-server (they set the server's rules and state, as soa's own):
#     --new-player, --seed FILE, --seed-rng N, --clock "YYYY-MM-DD HH:MM:SS", --start-coins N,
#     --galaxy-pass, --enable-events, --event-keywords L, --restore-tower, --master FILE,
#     --db FILE, --game-xml FILE, --fail M:CODE[,..], --surprise, --campaign-master-db FILE,
#     --campaign-seed LABEL
#   any other options go to soa, e.g. --fullscreen, --size 729x1296, --headless (soa --help)
#
# The first start downloads the game data (about 3 GB) from the local server into the phone's data.
# Ctrl-C (or the game window closing) stops both programs.
# Needs: scripts/build.sh, apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk, work/download-3.7.0 and
# data/basmaster-3.7.0.sqlite3 (README.md, "Game files").
set -euo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
soa=$repo/build/port/soa
srv=$repo/build/server/soa-server

home=${HOME:-.}/.local/share/soa-port-server-370
port=44310
server_log_to_tty=0
srv_args=() soa_args=()
while [ $# -gt 0 ]; do
  case "$1" in
    -h|--help) sed -n '2,22p' "$0" | sed 's/^# \{0,1\}//'; exit 0;;
    --home) home=$2; shift 2;;
    --port) port=$2; shift 2;;
    --server-log) server_log_to_tty=1; shift;;
    --new-player|--galaxy-pass|--enable-events|--restore-tower|--surprise) srv_args+=("$1"); shift;;
    --log-packets|--seed|--master|--db|--game-xml|--campaign-master-db)  # paths: from the caller's directory
      [ $# -ge 2 ] || { echo "run-port-with-server: $1 needs a value" >&2; exit 2; }
      case $2 in /*) v=$2;; *) v=$PWD/$2;; esac
      srv_args+=("$1" "$v"); shift 2;;
    --seed-rng|--clock|--start-coins|--event-keywords|--fail|--campaign-seed)
      [ $# -ge 2 ] || { echo "run-port-with-server: $1 needs a value" >&2; exit 2; }
      srv_args+=("$1" "$2"); shift 2;;
    --server|--http) echo "run-port-with-server: $1 is set by this script (see --port)" >&2; exit 2;;
    *) soa_args+=("$1"); shift;;
  esac
done
http_port=$((port + 80))

for f in "$soa" "$srv"; do
  [ -x "$f" ] || { echo "run-port-with-server: $f isn't built; run scripts/build.sh first" >&2; exit 1; }
done
for f in "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk" data/basmaster-3.7.0.sqlite3; do
  [ -s "$repo/$f" ] || { echo "run-port-with-server: $f is missing; see README.md" >&2; exit 1; }
done
[ -d "$repo/work/download-3.7.0" ] || { echo "run-port-with-server: work/download-3.7.0 is missing; see README.md" >&2; exit 1; }

mkdir -p "$home/phone" "$home/server"
home=$(cd "$home" && pwd)
slog=$home/server.log
spid= cpid=
cleanup() {
  trap - EXIT INT TERM
  [ -n "$cpid" ] && kill "$cpid" 2>/dev/null || true
  [ -n "$spid" ] && kill "$spid" 2>/dev/null || true
  # soa can ignore SIGTERM when its main loop is wedged: give both a few seconds, then SIGKILL
  for _ in 1 2 3 4 5 6 7 8 9 10; do
    { [ -n "$cpid" ] && kill -0 "$cpid" 2>/dev/null; } || { [ -n "$spid" ] && kill -0 "$spid" 2>/dev/null; } || break
    sleep 0.5
  done
  [ -n "$cpid" ] && kill -9 "$cpid" 2>/dev/null || true
  [ -n "$spid" ] && kill -9 "$spid" 2>/dev/null || true
  wait 2>/dev/null || true
}
trap cleanup EXIT
trap 'exit 130' INT TERM

cd "$repo"  # soa and soa-server find the master DB and the seeds from the checkout
echo "== starting soa-server (game 127.0.0.1:$port, http 127.0.0.1:$http_port; data $home/server)"
if [ $server_log_to_tty = 1 ]; then
  "$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port --data "$home/server" \
      --download-dir "$repo/work/download-3.7.0" ${srv_args[@]+"${srv_args[@]}"} > >(tee "$slog") 2>&1 &
else
  "$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port --data "$home/server" \
      --download-dir "$repo/work/download-3.7.0" ${srv_args[@]+"${srv_args[@]}"} > "$slog" 2>&1 &
fi
spid=$!

# Wait until it listens (the first start builds the CDN, a few seconds).
for _ in $(seq 1 240); do
  grep -q "^soa-server: game" "$slog" 2>/dev/null && break
  kill -0 "$spid" 2>/dev/null || { echo "run-port-with-server: soa-server exited; log: $slog" >&2; tail -5 "$slog" >&2; exit 1; }
  sleep 0.5
done
grep -q "^soa-server: game" "$slog" || { echo "run-port-with-server: soa-server didn't start; log: $slog" >&2; exit 1; }

echo "== starting soa --server 127.0.0.1:$port (phone data $home/phone)"
# In the background so Ctrl-C / a kill of this script reaches the trap, which stops both.
"$soa" --data "$home/phone" --server 127.0.0.1:$port --http 127.0.0.1:$http_port ${soa_args[@]+"${soa_args[@]}"} &
cpid=$!
wait "$cpid"
