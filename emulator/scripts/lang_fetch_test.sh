#!/bin/bash
# Does the unmodified 3.7.0 client (soa-emu) fetch the English master from soa-server's CDN only?
# (docs/PLAN-english.md C1/C2, docs/server-rules.md#english: with --english the CDN carries the new
# member sqlite/basmaster-en.sqlite3, the served master with the English text table's English, in
# its own Individual bundle I/5374616e/<chash32>.bin and the Bulk bundle.) The stand-in pattern of
# emulator/scripts/standin_fetch_test.sh, for the -en master. Builds nothing.
#
# Usage: emulator/scripts/lang_fetch_test.sh [-h|--help] [soa-emu] [soa-server] [out dir]
#   defaults: build/emulator/soa-emu; build/server/soa-server; a fresh mktemp dir (kept: logs, the
#   served version.bin, screenshots; the phone copy is deleted unless KEEP_DATA=1)
# Env:
#   EN_TABLE=FILE  the English text table soa-server gets (--english-text; default
#                  data/english/master-en.tsv, else work/english/en-server/master-en.tsv)
#   EMU_DATA=DIR   a pre-downloaded phone (default the shared phone work/phone-3.7.0; hard-linked,
#                  never modified); its record of the -en master, if any, is removed first, so the
#                  data check must fetch it
#   EMU_LANG=ja|en soa-emu's --lang (default en when soa-emu has the option, else none: then only
#                  the CDN half is proven, the client stays Japanese)
#   KEEP_DATA=1    keep the phone copy (OUT/emu)
#
# It starts soa-server --english (free ports, its own scratch state, the CDN from
# work/download-3.7.0) and soa-emu headless pointed at it, and checks:
#   1. served: version.bin over HTTP lists sqlite/basmaster-en.sqlite3 (encType 2) with its
#      Individual bundle I/5374616e/<chash32>.bin;
#   2. client: NoLoginStart -> TAP TO START -> Login -> the data check -> ダウンロード / 完了 -> home;
#   3. fetched: soa-server's request log has a 200 GET of that bundle;
#   4. stored: data/files/download/sqlite/basmaster-en.sqlite3 on the phone is the served file
#      byte for byte (ADLD header + payload, as the client writes a member).
# The home screenshot (OUT/home.png) shows the English header with --lang en (a visual check).
# Prints PASS / FAIL per check and a final PASS / FAIL (exit 0 / 1). Kills only what it started.
set -u
case "${1:-}" in -h|--help) sed -n '2,/^set -u/p' "$0" | sed '$d; s/^# \{0,1\}//'; exit 0;; esac
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../.." && pwd)
emu=$(readlink -f "${1:-$repo/build/emulator/soa-emu}")
srv=$(readlink -f "${2:-$repo/build/server/soa-server}")
out=${3:-$(mktemp -d "${TMPDIR:-/tmp}/lang-fetch.XXXXXX")}
out=$(mkdir -p "$out" && cd "$out" && pwd)
soactl="$repo/control/soactl.py"
member=sqlite/basmaster-en.sqlite3
[ -x "$emu" ] || { echo "FAIL: $emu not built"; exit 1; }
[ -x "$srv" ] || { echo "FAIL: $srv not built"; exit 1; }
repo_file() {   # a repo file here, else in the main checkout work/ links to (a worktree)
    if [ -e "$repo/$1" ]; then echo "$repo/$1"; return; fi
    local main
    main=$(dirname "$(readlink -f "$repo/work")")
    [ -n "$main" ] && [ -e "$main/$1" ] && echo "$main/$1"
}
master=$(repo_file data/basmaster-3.7.0.sqlite3)
download=$(repo_file work/download-3.7.0)
table=${EN_TABLE:-$(repo_file data/english/master-en.tsv)}
[ -n "$table" ] || table=$(repo_file work/english/en-server/master-en.tsv)
phone_src=${EMU_DATA:-$(repo_file work/phone-3.7.0)}
[ -n "$master" ] || { echo "FAIL: data/basmaster-3.7.0.sqlite3 not found"; exit 1; }
[ -n "$download" ] || { echo "FAIL: work/download-3.7.0 not found"; exit 1; }
[ -n "$table" ] && [ -s "$table" ] || { echo "FAIL: no English text table (EN_TABLE)"; exit 1; }
[ -n "$phone_src" ] && [ -d "$phone_src/data/files/download" ] || { echo "FAIL: no phone (EMU_DATA)"; exit 1; }
if [ -z "${EMU_LANG+x}" ]; then
    if "$emu" --help 2>&1 | grep -q -- "--lang"; then EMU_LANG=en; else EMU_LANG=; fi
fi
lang_args=()
[ -n "$EMU_LANG" ] && lang_args=(--lang "$EMU_LANG")
echo "binaries: soa-emu $emu, soa-server $srv; table: $table; phone: $phone_src; client --lang: ${EMU_LANG:-(none)}; out: $out"

phone=$out/emu
dl=$phone/data/files/download
elog=$out/emu.log slog=$out/server.log fifo=$out/fifo
W=729 H=1296
read -r game_port http_port < <(python3 -c '
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
    [ -p "$fifo" ] && kill -0 "${epid:-0}" 2>/dev/null && python3 "$soactl" --timeout 10 "$fifo" quit > /dev/null 2>&1
    if grep -qE "Unhandled SIG|\*\*\* host signal" "$elog" 2>/dev/null; then miss "soa-emu crashed (see $elog)"; fi
    echo "---"
    printf '%s\n' "${results[@]}"
    echo "logs: $slog $elog; out: $out"
    if [ $failed = 0 ]; then echo "PASS"; exit 0; fi
    echo "FAIL"; exit 1
}

# The phone: the shared phone hard-linked, without any -en master the phone may record.
. "$repo/scripts/shared-phone.sh"
shared_phone_link "$phone_src" "$phone" > "$out/phone-link.txt" 2>&1 || { miss "phone ($(tail -n 1 "$out/phone-link.txt"))"; finish; }
rm -f "$dl/$member"
python3 - "$dl/version.bin" "$member" > "$out/phone-prep.txt" 2>&1 <<'EOF' || { miss "phone: version.bin"; finish; }
import os, sys, msgpack
path, name = sys.argv[1], sys.argv[2]
v = msgpack.unpackb(open(path, "rb").read(), raw=False, strict_map_key=False)
had = v["assets"].pop(name, None) is not None
data = msgpack.packb(v, use_bin_type=True)
os.remove(path)  # a new file, never written through a link into the shared phone
open(path, "wb").write(data)
print(f"phone: {name} {'removed from' if had else 'not in'} its version.bin")
EOF
cat "$out/phone-prep.txt"

# soa-server --english.
SOASLOT_PY="$repo/control/soaslot.py"; . "$repo/control/soaslot.sh"; soaslot_take "lang_fetch_test.sh"
timeout -k 10 2400 "$srv" --listen 127.0.0.1:$game_port --http 127.0.0.1:$http_port --data "$out/server" --master "$master" \
    --download-dir "$download" --english --english-text "$table" --log-packets "$out/packets" > "$slog" 2>&1 &
spid=$!
for _ in $(seq 1 240); do grep -q "^soa-server: game" "$slog" 2>/dev/null && break; kill -0 $spid 2>/dev/null || break; sleep 0.5; done
grep -q "^soa-server: game" "$slog" || { miss "soa-server didn't start (log: $slog)"; finish; }
rev=$(sed -n 's|^soa-server: CDN .*/download/\([0-9]*\)/Android/.*|\1|p' "$slog" | head -1)
[ -n "$rev" ] || { miss "soa-server: no CDN line (log: $slog)"; finish; }
grep "english master" "$slog" | sed 's/^/  /'

# 1. served
mkdir -p "$out/served"
base=http://127.0.0.1:$http_port/download/$rev/Android
curl -sf -o "$out/served/version.bin" "$base/version.bin" || { miss "served: GET version.bin"; finish; }
curl -sf -o "$out/served/basmaster-en.sqlite3" "$base/$member" || { miss "served: GET $member"; finish; }
bundle=$(python3 - "$out/served/version.bin" "$member" <<'EOF'
import sys, msgpack
sys.path.insert(0, sys.path[0])
v = msgpack.unpackb(open(sys.argv[1], "rb").read(), raw=False, strict_map_key=False)["assets"]
e = v.get(sys.argv[2])
if not e or e.get("encType") != 2: sys.exit(1)
# parentHash = CHash32 of its Individual bundle's name: find it among the 5374616e bundles
print(e["parentHash"])
EOF
) || { miss "served: no $member entry (encType 2) in version.bin"; finish; }
ind=$(python3 -c "
import sys; sys.path.insert(0, '$repo')
from soa_save.adld import chash32
print('I/5374616e/%08x.bin' % chash32(b'$member'))")
want=$(python3 -c "
import sys; sys.path.insert(0, '$repo')
from soa_save.adld import chash32
print(chash32(b'$ind'))")
[ "$bundle" = "$want" ] && pass "served (rev $rev): $member in version.bin, bundle $ind ($(stat -c %s "$out/served/basmaster-en.sqlite3") bytes)" \
    || { miss "served: parentHash $bundle, want CHash32($ind) = $want"; finish; }
slog_base=$(wc -l < "$slog")

# 2. the client
timeout -k 10 2400 "$emu" --data "$phone" --headless --size ${W}x$H --control "$fifo" "${lang_args[@]}" \
    --server 127.0.0.1:$game_port --http 127.0.0.1:$http_port > "$elog" 2>&1 &
epid=$!
alive() { kill -0 $epid 2>/dev/null; }
ctl() { python3 "$soactl" --timeout 60 "$fifo" "$@" > /dev/null 2>&1; }
in_plog() { grep -q -- "$1" "$out/packets/packets.log" 2>/dev/null; }
in_elog() { grep -q -- "$1" "$elog" 2>/dev/null; }
in_slog() { tail -n +$((slog_base + 1)) "$slog" 2>/dev/null | grep -q -- "$1"; }
wait_for() {
    local name=$1 end=$(( $(date +%s) + $2 )); shift 2
    while ! "$@"; do
        alive || { miss "$name (soa-emu exited)"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "$name (not within $2 s)"; finish; }
        sleep 1
    done
    pass "$name"
}
tap_until() {
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
tap_until "title: NoLoginStart -> NoLoginStartRes" 240 364:713 in_plog "< NoLoginStartRes"
sleep 5
ctl "shot:$out/title.png"
tap_until "TAP TO START -> Login -> LoginResult" 180 364:713 in_plog "< LoginResult "
wait_for "data check (version_latest_Individual.bin)" 120 in_slog "GET [^ ]*/manifest/etc2/hi/version_latest_Individual.bin"
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
sleep 8
ctl "shot:$out/home.png"
# the notice board closed (its 閉じる), then the home itself
ctl "tap:364:1180"
sleep 6
ctl "shot:$out/home2.png"

# 3. fetched
grep -E "I/net: http GET [^ ]*/Android/$ind" "$slog" > "$out/en-gets.txt"
if [ -s "$out/en-gets.txt" ] && ! grep -qv -- "-> 200 " "$out/en-gets.txt"; then
    pass "fetched: $(sed 's/.*http GET //' "$out/en-gets.txt" | tr '\n' ';')"
else
    miss "fetched: no (or a failed) GET of $ind in $slog"
fi
# 4. stored
if cmp -s "$dl/$member" "$out/served/basmaster-en.sqlite3"; then pass "stored: $dl/$member is the served file byte for byte"
else miss "stored: $dl/$member missing or different"; fi
finish
