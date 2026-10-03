#!/bin/sh
# Runs the desktop port (build/port/soa): the 3.7.0 client.
#
# Usage: scripts/run-port.sh [soa options...]
#   default    the local server built into soa (--server inproc); state in the data dir's
#              server.sqlite3, data in ~/.local/share/soa-linux-370
#   --server HOST[:PORT]  play against a running soa-server instead (scripts/run-emulator-370.sh
#              starts one); add --http HOST:PORT if its HTTP port isn't 44380
# soa's options come in two groups (build/port/soa --help):
#   client options  the client and its emulated phone: --data DIR, --fullscreen, --size WxH,
#                   --device-clock, --guest-cpus, --download-dir, ...
#   server options  the local server's rules and state, soa-server's own flags: --seed FILE,
#                   --new-player, --clock "2019-08-01 12:00:00", --enable-events, --start-coins N,
#                   --galaxy-pass, --restore-tower, ... (only with --server inproc; with --server
#                   HOST give them to soa-server)
#
# Needs: scripts/build.sh, the 3.7.0 APK in apk/, and for the in-process server the 3.7.0 download
# in work/download-3.7.0 and data/basmaster-3.7.0.sqlite3 (README.md, "Game files").
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
soa=$repo/build/port/soa

case "${1:-}" in -h|--help) sed -n '2,18p' "$0" | sed 's/^# \{0,1\}//'; exit 0;; esac
[ "${1:-}" = "--offline" ] && { echo "run-port: --offline is gone: the port runs the 3.7.0 client (docs/history/PLAN-rebase-370.md)" >&2; exit 2; }

[ -x "$soa" ] || { echo "run-port: $soa isn't built; run scripts/build.sh first" >&2; exit 1; }
inproc=1
for a in "$@"; do
  case $a in --server) inproc=0;; esac
done
for a in "$@"; do  # --server inproc is still in-process
  [ "$a" = inproc ] && inproc=1
done
if [ $inproc = 1 ]; then
  [ -d "$repo/work/download-3.7.0" ] || { echo "run-port: work/download-3.7.0 (the 3.7.0 download) is missing; see README.md" >&2; exit 1; }
  [ -s "$repo/data/basmaster-3.7.0.sqlite3" ] || { echo "run-port: data/basmaster-3.7.0.sqlite3 is missing; see README.md" >&2; exit 1; }
fi
exec "$soa" "$@"
