# The server-plus-client launchers' shared half (bash; source it after `set -euo pipefail`):
# soa-server started in the background, waited for, and stopped with the client, also on Ctrl-C.
# Used by scripts/run-emulator-370.sh, scripts/run-port-with-server.sh and the release packages'
# run-emulator.sh / run-port-server.sh (shipped beside them as lib/with-server.sh, tools/package.py).
# The Windows launchers (.ps1) follow the same steps.
#
#   ws_init NAME                 the launcher's name for messages; installs the cleanup traps
#   ws_need "$@"                 exits 2 unless the option $1 has a value
#   ws_server_option "$@"        $1 is one of the server options the launchers pass on to
#                                soa-server: appends it (and its value; a path made absolute from
#                                the caller's directory) to ws_srv_args, sets ws_taken to the
#                                number of arguments used (status 0); else status 1
#   ws_check_port N              exits 2 unless N is a port number
#   ws_start_server LOG TTY SRV ARGS...
#                                SRV ARGS... in the background, its output into LOG (and on the
#                                terminal too when TTY is 1); sets ws_spid
#   ws_wait_ready                until soa-server prints its "ready" line (the first start
#                                decrypts the master and indexes the download: up to a minute;
#                                four at most); exits 1 when it stops first or serves no CDN
#   ws_run_client CLIENT ARGS... the client in the background (so that Ctrl-C or a kill of the
#                                launcher reaches the traps, which stop both); exits with its status
#
# The server's lines read here (tools/server_log_patterns.txt): "soa-server: game ...", then
# "soa-server: CDN ..." when it has a download, then "soa-server: ready".

ws_name=launcher
ws_spid=
ws_cpid=
ws_slog=
ws_taken=0
ws_srv_args=()

ws_cleanup() {
  # (a second Ctrl-C, e.g. the terminal's to the whole group, must not cut the cleanup short)
  trap '' INT TERM HUP
  trap - EXIT
  [ -n "$ws_cpid" ] && kill "$ws_cpid" 2> /dev/null || true
  [ -n "$ws_spid" ] && kill "$ws_spid" 2> /dev/null || true
  # a wedged client can ignore SIGTERM (AGENTS.md "Pitfalls"): a few seconds, then SIGKILL
  local _
  for _ in 1 2 3 4 5 6 7 8 9 10; do
    { [ -n "$ws_cpid" ] && kill -0 "$ws_cpid" 2> /dev/null; } || { [ -n "$ws_spid" ] && kill -0 "$ws_spid" 2> /dev/null; } || break
    sleep 0.5
  done
  [ -n "$ws_cpid" ] && kill -9 "$ws_cpid" 2> /dev/null || true
  [ -n "$ws_spid" ] && kill -9 "$ws_spid" 2> /dev/null || true
  wait 2> /dev/null || true
  ws_cpid= ws_spid=
}

ws_on_signal() {
  trap '' INT TERM HUP  # (the second Ctrl-C a wrapper forwards: ignored before anything else)
  ws_cleanup
  exit 130
}

ws_init() {
  ws_name=$1
  trap ws_cleanup EXIT
  trap ws_on_signal INT TERM HUP
}

ws_need() {
  [ $# -ge 2 ] || { echo "$ws_name: $1 needs a value" >&2; exit 2; }
}

ws_abs() { case $1 in /*) printf '%s' "$1" ;; *) printf '%s' "$PWD/$1" ;; esac; }

ws_server_option() {
  case "$1" in
    --new-player | --galaxy-pass | --enable-events | --restore-tower | --english | --surprise)
      ws_srv_args+=("$1"); ws_taken=1 ;;
    --seed | --download | --download-dir | --master | --db | --log-packets | --campaign-master-db)  # paths
      ws_need "$@"; ws_srv_args+=("$1" "$(ws_abs "$2")"); ws_taken=2 ;;
    --seed-rng | --clock | --start-coins | --stamina-heal-time | --event-keywords | --fail | --campaign-seed)
      ws_need "$@"; ws_srv_args+=("$1" "$2"); ws_taken=2 ;;
    *) return 1 ;;
  esac
}

ws_check_port() {
  case $1 in '' | *[!0-9]*) echo "$ws_name: --port takes a number" >&2; exit 2 ;; esac
  [ "$1" -ge 1 ] && [ "$1" -le 65455 ] || { echo "$ws_name: --port takes 1..65455 (its HTTP port is N+80)" >&2; exit 2; }
}

ws_start_server() {
  ws_slog=$1
  local tty=$2
  shift 2
  : > "$ws_slog"
  if [ "$tty" = 1 ]; then
    "$@" > >(tee -a "$ws_slog") 2>&1 &
  else
    "$@" >> "$ws_slog" 2>&1 &
  fi
  ws_spid=$!
}

ws_wait_ready() {
  local _
  for _ in $(seq 1 480); do
    grep -q "^soa-server: ready" "$ws_slog" 2> /dev/null && break
    kill -0 "$ws_spid" 2> /dev/null || break
    sleep 0.5
  done
  if ! grep -q "^soa-server: ready" "$ws_slog"; then
    echo "$ws_name: soa-server didn't start (see README.txt); log: $ws_slog" >&2
    tail -5 "$ws_slog" >&2
    exit 1
  fi
  # (the CDN line comes before the ready line)
  grep -q "^soa-server: CDN" "$ws_slog" || { echo "$ws_name: soa-server found no 3.7.0 download (see README.txt); log: $ws_slog" >&2; exit 1; }
}

ws_run_client() {
  "$@" &
  ws_cpid=$!
  local rc=0
  wait "$ws_cpid" || rc=$?
  ws_cpid=
  exit $rc
}
