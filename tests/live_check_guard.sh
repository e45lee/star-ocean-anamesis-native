#!/bin/sh
# Guards soa's --live-check against breaking silently (it once parsed its spec and switched nothing
# on: 721e212 .. d0c44e5, a day of live checks that checked nothing).
#   1. `--live-check nosuchfamily` must fail at start (exit non-zero, "no family").
#   2. A short headless run with `--live-check kernel:every=1:out=FILE` (the kernel family fires from
#      the first frames: the dispatcher, TaskManager, PerformanceCounter) must leave FILE with
#      checks > 0 and 0 mismatches, and no MISMATCH line in the log.
# Usage: tests/live_check_guard.sh <soa> <out-dir> <scratch-dir>   (from the repository root)
# "PASS live_check_guard" or "FAIL live_check_guard: ..." (exit 1).
set -u
soa=${1:?usage: tests/live_check_guard.sh <soa> <out-dir> <scratch-dir>}
out=${2:?out-dir}
tmp=${3:?scratch-dir}
mkdir -p "$out" "$tmp/data"
fail() {
  echo "FAIL live_check_guard: $*"
  exit 1
}

# (Bounded: a soa that accepts it would boot the game, without a slot.)
timeout -k 5 20 "$soa" --headless --live-check nosuchfamily > "$out/unknown.log" 2>&1
rc=$?
[ "$rc" -ne 0 ] && [ "$rc" -ne 124 ] || fail "--live-check nosuchfamily didn't fail at start (exit $rc, $out/unknown.log)"
grep -q 'no family "nosuchfamily"' "$out/unknown.log" || fail "--live-check nosuchfamily: no 'no family' error ($out/unknown.log)"

counts="$out/kernel-counts.txt"
rm -f "$counts"
python3 control/soaslot.py run -- timeout -k 10 120 "$soa" --headless --data "$tmp/data" \
  --live-check "kernel:every=1:out=$counts" --do 10:quit > "$out/log.txt" 2>&1
rc=$?
[ "$rc" -eq 0 ] || fail "soa exited $rc ($out/log.txt)"
[ -s "$counts" ] || fail "no counts file: --live-check switched nothing on ($out/log.txt)"
# First line: "N checks: N ok, M mismatches, S skipped, R races"
set -- $(head -1 "$counts")
checks=${1:-0}
mismatches=${5:-x}
[ "$checks" -gt 0 ] 2>/dev/null || fail "0 kernel checks ($counts)"
[ "$mismatches" = 0 ] || fail "kernel mismatches: $(head -1 "$counts")"
grep -q "MISMATCH" "$out/log.txt" && fail "a MISMATCH line in $out/log.txt"
echo "PASS live_check_guard ($(head -1 "$counts"))"
