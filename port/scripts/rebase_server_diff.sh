#!/bin/bash
# The out-of-process gate of the 3.7.0 rebase (docs/history/PLAN-rebase-370.md P1): the port's 3.7.0 client
# (soa --server HOST:PORT, natives route: no FakeApiCaller route, its own NetworkApiCaller) and the
# unmodified client (soa-emu) play the same scripted flow against fresh soa-servers with the same
# seed, and the requests they send must be equal.
#
# Usage: port/scripts/rebase_server_diff.sh [PHONE [out-dir]]
#   PHONE   a phone with the game data downloaded already: default (or "shared") the shared phone
#           work/phone-3.7.0 (scripts/make-phone-370.sh), linked for each client
#           (scripts/shared-phone.sh); else e.g. a KEEP_DATA=1 emulator/scripts/emulator_session.sh
#           run's OUT/emu, copied for each client (3 GB). Never modified; each client's phone gets a
#           fresh local KVS (FRESH_KVS=1: a new device UUID).
#   out-dir default: a fresh mktemp dir; OUT/emu-run and OUT/soa-run are emulator_session.sh's out dirs.
# Env: SOA, SOA_EMU, SOA_SERVER (default build/port/soa, build/emulator/soa-emu, build/server/soa-server);
#      KEEP_PHONES=1 keeps the two phone copies.
#
# The flow is emulator/scripts/emulator_session.sh's seeded one with SESSION_PLAY=0: soa-server
# --seed-rng 1 --campaign-seed mf01_001 (the LOCAL00001 player), the title's NoLoginStart, TAP TO
# START, the bridge, Login, the downloader's check (the data is on the phone), home (the notice
# board). Both runs must PASS, then tools/compare_packets.py compares soa-server's two packet logs
# (method, FunctionID and arguments of every request, every reply's name / data keys / status;
# times, ciphers, UUIDs, session keys and tokens masked) and the clients' HTTP GETs. Prints PASS /
# FAIL; runs one client at a time; kills only what it started (emulator_session.sh does).
set -u
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../.." && pwd)
. "$repo/scripts/shared-phone.sh"
phone=${1:-shared}
[ "$phone" = shared ] && phone=$(shared_phone_dir "$repo")
out=${2:-$(mktemp -d "${TMPDIR:-/tmp}/rebase-server-diff.XXXXXX")}
soa=${SOA:-$repo/build/port/soa}
emu=${SOA_EMU:-$repo/build/emulator/soa-emu}
srv=${SOA_SERVER:-$repo/build/server/soa-server}
[ -d "$phone/data/files/download" ] || { echo "FAIL: $phone has no downloaded game data (data/files/download)"; exit 1; }
mkdir -p "$out"
rc=0
for c in emu soa; do
    bin=$emu; [ $c = soa ] && bin=$soa
    run=$out/$c-run copy=$out/$c-phone
    rm -rf "${copy:?}" "${run:?}"
    shared_phone_link "$phone" "$copy" || { echo "FAIL: copying $phone"; exit 1; }
    echo "== $c: $bin"
    SESSION_PLAY=0 EMU_DATA=$copy FRESH_KVS=1 "$repo/emulator/scripts/emulator_session.sh" "$bin" "$srv" "$run" > "$out/$c-session.txt" 2>&1
    s=$?
    tail -3 "$out/$c-session.txt"
    [ $s = 0 ] || { echo "FAIL: the $c session failed (see $out/$c-session.txt)"; rc=1; }
    [ "${KEEP_PHONES:-0}" = 1 ] || rm -rf "${copy:?}"
done
[ $rc = 0 ] || { echo "FAIL"; exit 1; }
echo "== packets: soa-emu vs soa --server"
python3 "$repo/tools/compare_packets.py" --labels soa-emu soa "$out/emu-run/packets/packets.log" "$out/soa-run/packets/packets.log" \
    --client-logs "$out/emu-run/emu.log" "$out/soa-run/emu.log" | tee "$out/compare.txt"
grep -q '^PASS' "$out/compare.txt" && { echo "PASS (out: $out)"; exit 0; }
echo "FAIL (out: $out)"; exit 1
