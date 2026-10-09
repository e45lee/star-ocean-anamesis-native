#!/bin/bash
# Does the unmodified 3.7.0 client (soa-emu) fetch the stand-in assets from soa-server's CDN?
# (server/README.md "CDN": the files of standin-assets/ the download lacks become new members,
# one Individual bundle each, I/5374616e/<chash32>.bin, and one Bulk bundle,
# B/5374616e/standins.bin; docs/client-changes.md "Stand-in images".) Builds nothing.
#
# Usage: emulator/scripts/standin_fetch_test.sh [-h|--help] [soa-emu] [soa-server] [out dir]
#   defaults: build/emulator/soa-emu; build/server/soa-server; a fresh mktemp dir (kept: logs,
#   the served manifests, screenshots; the phone copies are deleted unless KEEP_DATA=1)
# Env:
#   EMU_DATA=DIR   a pre-downloaded emulated phone (DIR/data/files/download: a KEEP_DATA=1
#                  emulator_session.sh run's OUT/emu, or any phone the 3.7.0 client filled from
#                  soa-server's or the port's CDN), or the stamped shared phone work/phone-3.7.0
#                  (scripts/shared-phone.sh: hard-linked, writable directories, version.bin and
#                  manifest copied). Never modified; in the run's phone the
#                  stand-ins are removed (below), so the client's data check only fetches them and
#                  what else the phone lacks. Without EMU_DATA each run downloads the whole 3 GB.
#   STANDIN_MODES  the runs (default "on off", in parallel): on = soa-server --standin-assets
#                  standin-assets/ (the repo's), off = --standin-assets off (the negative control)
#   KEEP_DATA=1    keep the phone copies (OUT/<mode>/emu)
#
# Each run starts soa-server (free ports, its own scratch state, the CDN from work/SOA-3.7.0-canonical-data.zip)
# and soa-emu headless pointed at it, and checks:
#   1. served: version.bin and the two manifests, fetched over HTTP from the running server
#      (curl) and decoded: on = every file of standin-assets/ is a version.bin entry, a member of
#      B/5374616e/standins.bin (Bulk) and of its own I/5374616e/<hash>.bin (Individual), with
#      its size; off = none of them, no 5374616e bundle;
#   2. client: NoLoginStart -> TAP TO START -> Login -> the data check (the manifests' GETs) ->
#      ダウンロード / 完了 when a download dialog comes -> home (the notice board's ShowWebView);
#   3. fetched: soa-server's log has one line per HTTP request ('I/net: http GET <target> ->
#      <status> (<bytes>)'): on = 200 GETs of the 5374616e bundle(s); off = none;
#   4. stored: the client unpacks a bundle's members into data/files/download/<name>, each as
#      ADLD + u32 e + 8 zero bytes + the payload (docs/online-server.md §6), i.e. the original
#      .aif: on = every stand-in there byte-identical (cmp) to standin-assets/; off = none there.
# Removing the stand-ins from the phone copy: their files under data/files/download and their
# entries (the members and the 5374616e bundles) in the client's own record of what it has,
# data/files/download/version.bin (a phone filled before the stand-ins existed has neither).
# Prints PASS / FAIL per check and a final PASS / FAIL (exit 0 / 1). Kills only the processes it
# started.
set -u
case "${1:-}" in -h|--help) sed -n '2,/^set -u/p' "$0" | sed '$d; s/^# \{0,1\}//'; exit 0;; esac
mode=
if [ "${1:-}" = --mode ]; then mode=$2; shift 2; fi   # internal: one run
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../.." && pwd)
emu=$(readlink -f "${1:-$repo/build/emulator/soa-emu}")
srv=$(readlink -f "${2:-$repo/build/server/soa-server}")
out=${3:-$(mktemp -d "${TMPDIR:-/tmp}/standin-fetch.XXXXXX")}
out=$(mkdir -p "$out" && cd "$out" && pwd)
standins=$repo/standin-assets
soactl="$repo/control/soactl.py"
[ -x "$emu" ] || { echo "FAIL: $emu not built (cmake --build build --target soa-emu)"; exit 1; }
[ -x "$srv" ] || { echo "FAIL: $srv not built (cmake --build build --target soa-server)"; exit 1; }
[ -d "$standins" ] || { echo "FAIL: no $standins"; exit 1; }
if [ -n "${EMU_DATA:-}" ] && [ ! -d "$EMU_DATA/data/files/download" ]; then
    echo "FAIL: EMU_DATA=$EMU_DATA has no data/files/download"; exit 1
fi

# The parent: one run per mode, in parallel, then the summary.
if [ -z "$mode" ]; then
    echo "binaries: soa-emu $emu, soa-server $srv; phone: ${EMU_DATA:-(none: full download)}; out: $out"
    pids=() modes=()
    for m in ${STANDIN_MODES:-on off}; do
        [ "$m" = on ] || [ "$m" = off ] || { echo "FAIL: STANDIN_MODES: '$m' is not on / off"; exit 1; }
        mkdir -p "$out/$m"
        "$0" --mode "$m" "$emu" "$srv" "$out/$m" > "$out/$m/test.txt" 2>&1 &
        pids+=($!) modes+=("$m")
    done
    trap 'kill "${pids[@]}" 2>/dev/null' INT TERM
    status=0
    for i in "${!pids[@]}"; do
        wait "${pids[$i]}" || status=1
        echo "=== standin-assets ${modes[$i]} ==="
        sed -n '/^---$/,$p' "$out/${modes[$i]}/test.txt" | sed '1d'
    done
    if [ $status = 0 ]; then echo "PASS"; else echo "FAIL"; fi
    exit $status
fi

# One run.
. "$repo/scripts/lib/checkout.sh"  # repo_file DIR REL: here, else in the main checkout (a worktree)
master=$(repo_file "$repo" data/basmaster-3.7.0.sqlite3)
download=$(repo_file "$repo" work/SOA-3.7.0-canonical-data.zip)
[ -n "$master" ] || { echo "FAIL: data/basmaster-3.7.0.sqlite3 not found"; exit 1; }
[ -n "$download" ] || { echo "FAIL: work/SOA-3.7.0-canonical-data.zip not found"; exit 1; }
(cd "$standins" && find . -type f | sed 's|^\./||' | sort) > "$out/standins.txt"

phone=$out/emu
dl=$phone/data/files/download
elog=$out/emu.log slog=$out/server.log fifo=$out/fifo
W=729 H=1296
MAX_RSS_KB=$((6 * 1024 * 1024))
read -r game_port http_port < <("$repo/tools/py" -c '
import socket
s = [socket.socket() for _ in range(2)]
for x in s: x.bind(("127.0.0.1", 0))
print(*[x.getsockname()[1] for x in s])')
t0=$(date +%s)
spid= epid=
cleanup() {
    for p in $epid $spid; do
        kill -0 "$p" 2>/dev/null || continue
        kill "$p" 2>/dev/null
        for _ in 1 2 3 4 5 6 7 8 9 10; do kill -0 "$p" 2>/dev/null || break; sleep 1; done
        kill -9 "$p" 2>/dev/null
    done
    if [ "${KEEP_DATA:-0}" != 1 ] && [ -d "$phone" ]; then rm -rf "${phone:?}"; fi
}
trap cleanup EXIT
trap 'exit 1' INT TERM

results=() failed=0
pass() { results+=("PASS  $1"); echo "PASS  $1 ($(( $(date +%s) - t0 ))s)"; }
miss() { results+=("FAIL  $1"); echo "FAIL  $1"; failed=1; }
finish() {
    [ -p "$fifo" ] && kill -0 "${epid:-0}" 2>/dev/null && "$repo/tools/py" "$soactl" --timeout 10 "$fifo" quit > /dev/null 2>&1
    if grep -qE "Unhandled SIG|\*\*\* host signal" "$elog" 2>/dev/null; then miss "soa-emu crashed (see $elog)"; fi
    echo "---"
    printf '%s\n' "${results[@]}"
    echo "logs: $slog $elog; out: $out"
    if [ $failed = 0 ]; then echo "PASS"; exit 0; fi
    echo "FAIL"; exit 1
}

# The phone: EMU_DATA without the stand-ins, or an empty one. A stamped shared phone
# (scripts/shared-phone.sh, e.g. work/phone-3.7.0) is hard-linked with writable directories and
# real copies of version.bin / manifest (the files rewritten below), any other phone copied.
if [ -n "${EMU_DATA:-}" ]; then
    . "$repo/scripts/shared-phone.sh"
    shared_phone_link "$EMU_DATA" "$phone" > "$out/phone-link.txt" 2>&1 || { miss "phone from EMU_DATA ($(tail -n 1 "$out/phone-link.txt"))"; finish; }
    while read -r rel; do rm -f "$dl/$rel"; done < "$out/standins.txt"
    if ! "$repo/tools/py" - "$dl/version.bin" "$out/standins.txt" > "$out/phone-prep.txt" 2>&1 <<'EOF'
import os, sys, msgpack
path, names = sys.argv[1], set(open(sys.argv[2]).read().split())
v = msgpack.unpackb(open(path, "rb").read(), raw=False, strict_map_key=False)
a = v["assets"]
drop = [k for k in a if k in names or "/5374616e/" in k]
for k in drop: del a[k]
data = msgpack.packb(v, use_bin_type=True)
os.remove(path)  # a new file, never written through a link into EMU_DATA
open(path, "wb").write(data)
print(f"removed {len(drop)} entries from the phone's version.bin: {', '.join(sorted(drop))}")
EOF
    then miss "phone: version.bin ($(tail -n 1 "$out/phone-prep.txt"))"; finish; fi
    echo "phone: $(cat "$out/phone-prep.txt")"
else
    mkdir -p "$phone"
fi

# soa-server.
if [ "$mode" = on ]; then sa=$standins; else sa=off; fi
# The machine-wide game slot pool (control/soaslot.sh): one slot for this script's client, held
# until the script exits; queued here when the machine is full.
SOASLOT_PY="$repo/control/soaslot.py"; . "$repo/control/soaslot.sh"; soaslot_take "standin_fetch_test.sh"
timeout -k 10 2400 "$srv" --listen 127.0.0.1:$game_port --http 127.0.0.1:$http_port --data "$out/server" --master "$master" \
    --download-dir "$download" --standin-assets "$sa" --log-packets "$out/packets" > "$slog" 2>&1 &
spid=$!
# (its "ready" line comes after the game and CDN lines: scripts/lib/with-server.sh)
for _ in $(seq 1 120); do grep -q "^soa-server: ready" "$slog" 2>/dev/null && break; kill -0 $spid 2>/dev/null || break; sleep 0.5; done
grep -q "^soa-server: ready" "$slog" || { miss "soa-server didn't start (log: $slog)"; finish; }
rev=$(sed -n 's|^soa-server: CDN .*/download/\([0-9]*\)/Android/.*|\1|p' "$slog" | head -1)
[ -n "$rev" ] || { miss "soa-server: no CDN line (log: $slog)"; finish; }

# 1. What the server serves: version.bin and the manifests over HTTP.
mkdir -p "$out/served"
base=http://127.0.0.1:$http_port/download/$rev/Android
for f in version.bin manifest/etc2/hi/version_latest_Bulk.bin manifest/etc2/hi/version_latest_Individual.bin; do
    curl -sf -o "$out/served/$(basename "$f")" "$base/$f" || { miss "served: GET $f"; finish; }
done
if check=$("$repo/tools/py" - "$out/served" "$out/standins.txt" "$standins" "$mode" <<'EOF'
import os, sys, msgpack
d, names, src, mode = sys.argv[1], open(sys.argv[2]).read().split(), sys.argv[3], sys.argv[4]
load = lambda f: msgpack.unpackb(open(os.path.join(d, f), "rb").read(), raw=False, strict_map_key=False)["assets"]
ver, bulk, ind = load("version.bin"), load("version_latest_Bulk.bin"), load("version_latest_Individual.bin")
def holders(man, n): return [b for b, m in man.items() if isinstance(m, dict) and n in m]
bad, notes = [], []
for n in names:
    hb, hi = holders(bulk, n), holders(ind, n)
    if mode == "on":
        size = os.path.getsize(os.path.join(src, n))
        if n not in ver or ver[n].get("size") != size: bad.append(f"{n}: version.bin entry {ver.get(n)}")
        if hb != ["B/5374616e/standins.bin"]: bad.append(f"{n}: Bulk bundles {hb}")
        if len(hi) != 1 or not hi[0].startswith("I/5374616e/"): bad.append(f"{n}: Individual bundles {hi}")
        else: notes.append(f"{os.path.basename(n)} in {hi[0]}")
    elif n in ver or hb or hi:
        bad.append(f"{n} listed (version.bin {n in ver}, Bulk {hb}, Individual {hi})")
stan = sorted(b for b in list(bulk) + list(ind) if "/5374616e/" in b)
if mode == "off" and stan: bad.append(f"5374616e bundles listed: {stan}")
if bad: print("; ".join(bad)); sys.exit(1)
if mode == "on": print(f"{len(names)} stand-ins in version.bin, B/5374616e/standins.bin ({len(bulk['B/5374616e/standins.bin']) - 3} members) and " + ", ".join(notes))
else: print(f"none of the {len(names)} stand-ins in version.bin or the manifests, no 5374616e bundle")
EOF
); then pass "served (rev $rev): $check"; else miss "served (rev $rev): $check"; finish; fi
# The client's own requests are the server log's lines after these (check 1's curl GETs of the
# manifests must not count as the client's data check).
slog_base=$(wc -l < "$slog")

# 2. The client.
timeout -k 10 2400 "$emu" --data "$phone" --headless --size ${W}x$H --control "$fifo" \
    --server 127.0.0.1:$game_port --http 127.0.0.1:$http_port > "$elog" 2>&1 &
epid=$!
alive() {
    kill -0 $epid 2>/dev/null || return 1
    local rss
    rss=$(ps -o rss= --ppid $epid 2>/dev/null | sort -n | tail -1)
    [ -z "$rss" ] || [ "$rss" -le $MAX_RSS_KB ] || { echo "soa-emu above 6 GB RSS"; return 1; }
}
ctl() { "$repo/tools/py" "$soactl" --timeout 60 "$fifo" "$@" > /dev/null 2>&1; }
in_plog() { grep -q -- "$1" "$out/packets/packets.log" 2>/dev/null; }
in_elog() { grep -q -- "$1" "$elog" 2>/dev/null; }
in_slog() { tail -n +$((slog_base + 1)) "$slog" 2>/dev/null | grep -q -- "$1"; }
wait_for() {   # NAME SECONDS CMD...
    local name=$1 end=$(( $(date +%s) + $2 )); shift 2
    while ! "$@"; do
        alive || { miss "$name (soa-emu exited)"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "$name (not within $(( end - t0 ))s of the start)"; finish; }
        sleep 1
    done
    pass "$name"
}
tap_until() {   # NAME SECONDS X:Y CMD...: taps X:Y every 4 s until CMD succeeds
    local name=$1 end=$(( $(date +%s) + $2 )) xy=$3 next=0; shift 3
    while ! "$@"; do
        alive || { miss "$name (soa-emu exited)"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "$name (not within $2 s)"; finish; }
        if [ "$(date +%s)" -ge $next ]; then ctl "tap:$xy"; next=$(( $(date +%s) + 4 )); fi
        sleep 1
    done
    pass "$name"
}
http_gets() { grep -c "I/net: http GET" "$slog" 2>/dev/null || true; }
home() { in_elog "ShowWebView(http"; }
bundle_get() { grep -qE "I/net: http GET [^ ]*/Android/[BI]/" "$slog" 2>/dev/null; }

# The title's NoLoginStart (リトライ, the middle of the screen, if the first request was lost),
# TAP TO START, the bridge, Login.
tap_until "title: NoLoginStart -> NoLoginStartRes" 240 364:713 in_plog "< NoLoginStartRes"
sleep 5
ctl "shot:$out/title.png"
tap_until "TAP TO START -> Login -> LoginResult" 180 364:713 in_plog "< LoginResult "
# The data check. An empty phone: the Episode data dialog (Episodeデータ管理) first; its 決定
# starts the client's GETs of version.bin and the manifests.
if [ -z "${EMU_DATA:-}" ]; then
    tap_until "data check (version_latest_Bulk.bin)" 120 364:1043 in_slog "GET [^ ]*/manifest/etc2/hi/version_latest_Bulk.bin"
else
    wait_for "data check (version_latest_Bulk.bin)" 120 in_slog "GET [^ ]*/manifest/etc2/hi/version_latest_Bulk.bin"
fi
# A download dialog (ダウンロード 515:800) when the phone lacks something, else home; an Episode
# data dialog that comes instead (決定 364:1043) is answered too, the two taps in turn. Then the
# bundles until the GETs stop for 20 s, the download's 完了 (364:790), home.
end=$(( $(date +%s) + 120 )) next=$(( $(date +%s) + 8 )) k=0
while ! bundle_get && ! home; do
    alive || { miss "download dialog (soa-emu exited)"; finish; }
    [ "$(date +%s)" -lt $end ] || { miss "data check: neither a download nor home within 120 s"; finish; }
    if [ "$(date +%s)" -ge $next ]; then
        [ -f "$out/download-dialog.png" ] || ctl "shot:$out/download-dialog.png"
        if [ $((k % 2)) = 0 ]; then ctl tap:515:800; else ctl tap:364:1043; fi
        k=$((k + 1)) next=$(( $(date +%s) + 6 ))
    fi
    sleep 1
done
if bundle_get; then
    pass "download dialog -> ダウンロード -> bundle GETs"
    n=-1 since=0 end=$(( $(date +%s) + 1500 ))
    while :; do
        alive || { miss "download (soa-emu exited)"; finish; }
        c=$(http_gets)
        if [ "$c" != "$n" ]; then n=$c since=$(date +%s); fi
        [ $(( $(date +%s) - since )) -ge 20 ] && break
        [ "$(date +%s)" -lt $end ] || { miss "download: GETs still going after 1500 s"; finish; }
        sleep 2
    done
    pass "download finished ($(grep -cE "I/net: http GET [^ ]*/Android/[BI]/" "$slog") bundle GETs)"
    ctl "shot:$out/download-done.png"
    tap_until "完了 -> home (notice board)" 120 364:790 home
else
    pass "home (notice board) without a download"
fi
sleep 5
ctl "shot:$out/home.png"

# 3. The GETs of the stand-in bundles, in soa-server's request log.
grep -E "I/net: http GET [^ ]*/Android/[BI]/5374616e/" "$slog" > "$out/standin-gets.txt"
grep -E "I/net: http GET [^ ]*/Android/[BI]/" "$slog" > "$out/bundle-gets.txt"
if [ "$mode" = on ]; then
    if [ -s "$out/standin-gets.txt" ] && ! grep -qv -- "-> 200 " "$out/standin-gets.txt"; then
        pass "fetched: $(wc -l < "$out/standin-gets.txt") stand-in bundle GET(s), 200: $(sed 's/.*http GET //' "$out/standin-gets.txt" | tr '\n' ';')"
    else
        miss "fetched: no (or a failed) stand-in bundle GET in $slog: $(tr '\n' ';' < "$out/standin-gets.txt")"
    fi
elif [ -s "$out/standin-gets.txt" ]; then
    miss "not fetched: stand-in GETs with --standin-assets off: $(tr '\n' ';' < "$out/standin-gets.txt")"
else
    pass "not fetched: no 5374616e GET ($(wc -l < "$out/bundle-gets.txt") bundle GETs in all)"
fi

# 4. The members on the phone.
same=0 absent=0 differ=()
while read -r rel; do
    if [ ! -e "$dl/$rel" ]; then absent=$((absent + 1))
    elif cmp -s "$dl/$rel" "$standins/$rel"; then same=$((same + 1))
    else differ+=("$rel"); fi
done < "$out/standins.txt"
total=$(wc -l < "$out/standins.txt")
if [ "$mode" = on ]; then
    if [ $same = "$total" ]; then pass "stored: all $total stand-ins in data/files/download byte-identical to standin-assets/"
    else miss "stored: $same of $total identical, $absent absent, differing: ${differ[*]:-none}"; fi
else
    if [ $absent = "$total" ]; then pass "stored: none of the $total stand-ins on the phone"
    else miss "stored: $(( total - absent )) of $total stand-ins on the phone with --standin-assets off"; fi
fi
finish
