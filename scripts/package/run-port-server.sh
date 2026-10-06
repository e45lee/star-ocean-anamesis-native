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
#     --new-player, --seed FILE, --seed-rng N, --clock "YYYY-MM-DD HH:MM:SS", --start-coins N,
#     --galaxy-pass, --enable-events, --event-keywords L, --restore-tower, --download PATH,
#     --master FILE, --log-packets DIR
#   any other options go to soa, e.g. --fullscreen, --size 729x1296, --apk FILE (./soa --help)
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
soa=$here/soa
srv=$here/soa-server
data=${HOME:-.}/.local/share/soa-linux-370
port=44310
server_log_to_tty=0
srv_args=() soa_args=()
abs() { case $1 in /*) printf '%s' "$1";; *) printf '%s' "$PWD/$1";; esac; }
need() { [ $# -ge 2 ] || { echo "run-port-server: $1 needs a value" >&2; exit 2; }; }
while [ $# -gt 0 ]; do
  case "$1" in
    -h|--help) sed -n '2,17p' "$0" | sed 's/^# \{0,1\}//'; exit 0;;
    --data) need "$@"; data=$2; shift 2;;
    --port) need "$@"; port=$2; shift 2;;
    --server-log) server_log_to_tty=1; shift;;
    --new-player|--galaxy-pass|--enable-events|--restore-tower) srv_args+=("$1"); shift;;
    --seed|--download|--download-dir|--master|--log-packets)  # paths: from the caller's directory
      need "$@"; srv_args+=("$1" "$(abs "$2")"); shift 2;;
    --seed-rng|--clock|--start-coins|--event-keywords) need "$@"; srv_args+=("$1" "$2"); shift 2;;
    --server|--http) echo "run-port-server: $1 is set by this script (see --port)" >&2; exit 2;;
    *) soa_args+=("$1"); shift;;
  esac
done
case $port in ''|*[!0-9]*) echo "run-port-server: --port takes a number" >&2; exit 2;; esac
http_port=$((port + 80))

mkdir -p "$data/server"
data=$(cd "$data" && pwd)
slog=$data/server.log
spid= cpid=
cleanup() {
  # (a second Ctrl-C, e.g. the terminal's to the whole group, must not cut the cleanup short)
  trap '' INT TERM HUP
  trap - EXIT
  [ -n "$cpid" ] && kill "$cpid" 2>/dev/null || true
  [ -n "$spid" ] && kill "$spid" 2>/dev/null || true
  # a wedged soa can ignore SIGTERM: a few seconds, then SIGKILL
  for _ in 1 2 3 4 5 6 7 8 9 10; do
    { [ -n "$cpid" ] && kill -0 "$cpid" 2>/dev/null; } || { [ -n "$spid" ] && kill -0 "$spid" 2>/dev/null; } || break
    sleep 0.5
  done
  [ -n "$cpid" ] && kill -9 "$cpid" 2>/dev/null || true
  [ -n "$spid" ] && kill -9 "$spid" 2>/dev/null || true
  wait 2>/dev/null || true
  cpid= spid=
}
trap cleanup EXIT
# Ctrl-C reaches this script twice when a wrapper (timeout, a terminal) forwards it too: the
# handler ignores the second one before anything else
on_signal() { trap '' INT TERM HUP; cleanup; exit 130; }
trap on_signal INT TERM HUP

# --seed: a new server state takes the player of the phone's save, as soa's in-process server does
# with the same data dir (a save without a player, the client's first settings-only one, is skipped
# with a warning); a --seed among the user's options comes later and wins
: > "$slog"
if [ $server_log_to_tty = 1 ]; then
  "$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port --data "$data/server" \
      --seed "$data/data/shared_prefs/Game.xml" ${srv_args[@]+"${srv_args[@]}"} > >(tee -a "$slog") 2>&1 &
else
  "$srv" --listen 127.0.0.1:$port --http 127.0.0.1:$http_port --data "$data/server" \
      --seed "$data/data/shared_prefs/Game.xml" ${srv_args[@]+"${srv_args[@]}"} >> "$slog" 2>&1 &
fi
spid=$!
echo "== soa-server (pid $spid): game 127.0.0.1:$port, http 127.0.0.1:$http_port; state $data/server, log $slog"

# Wait until it listens (the first start decrypts the master and indexes the download: up to a minute).
for _ in $(seq 1 480); do
  grep -q "^soa-server: game" "$slog" 2>/dev/null && break
  kill -0 "$spid" 2>/dev/null || { echo "run-port-server: soa-server exited (see README.txt); log: $slog" >&2; tail -5 "$slog" >&2; exit 1; }
  sleep 0.5
done
grep -q "^soa-server: game" "$slog" || { echo "run-port-server: soa-server didn't start; log: $slog" >&2; exit 1; }
sleep 0.2  # (its CDN line follows the game line)
grep -q "^soa-server: CDN" "$slog" || { echo "run-port-server: soa-server found no 3.7.0 download (see README.txt); log: $slog" >&2; exit 1; }

# In the background so that Ctrl-C or a kill of this script reaches the trap, which stops both.
"$soa" --data "$data" --server 127.0.0.1:$port --http 127.0.0.1:$http_port ${soa_args[@]+"${soa_args[@]}"} &
cpid=$!
echo "== soa (pid $cpid) --server 127.0.0.1:$port; data $data"
set +e
wait "$cpid"
rc=$?
cpid=
exit $rc
