#!/bin/bash
# The full (or filtered) soa --selftest, carried past tests that crash or hang the process: after a
# crash the run is restarted with SOA_SELFTEST_SKIP = the crashing test plus every test already
# done, until the runner reaches its summary. For the 3.7.0 rebase, where many natives still carried
# the old lib's constants (docs/history/REBASE-370.md "P1"; docs/history/rebase-370/selftest-p1.tsv was made this way, two
# filters in parallel).
#
# Usage: port/scripts/selftest_resilient.sh OUT [FILTER]   (from any directory)
# Env: SOA (default build/port/soa), PER_RUN_TIMEOUT (seconds per boot, default 1800), MAX_RUNS (100).
# Writes OUT/log-N.txt per boot and OUT/results.txt: "ok|FAIL|CRASH|TIMEOUT <test>" per test.
set -u
out=${1:?usage: selftest_resilient.sh OUT [FILTER]}; filter=${2:-}
repo=$(cd "$(dirname "$0")/../.." && pwd)
soa=${SOA:-$repo/build/port/soa}
mkdir -p "$out"; : > "$out/results.txt"
# The machine-wide game slot pool (control/soaslot.sh): one slot for the boots, held until the end.
SOASLOT_PY="$repo/control/soaslot.py"; . "$repo/control/soaslot.sh"; soaslot_take selftest_resilient.sh
skip="" n=0
while [ $n -lt "${MAX_RUNS:-100}" ]; do
    n=$((n + 1)); rm -rf "${out:?}/data"; mkdir -p "$out/data"
    SOA_SELFTEST_SKIP="$skip" nice timeout -k 10 "${PER_RUN_TIMEOUT:-1800}" "$soa" --repo "$repo" --data "$out/data" \
        --selftest $filter > "$out/log-$n.txt" 2>&1
    rc=$?
    grep -E '^(ok  |FAIL|skip)  ' "$out/log-$n.txt" | awk '{print $1, $2}' >> "$out/results.txt"
    if grep -q 'native tests passed' "$out/log-$n.txt"; then
        echo "done after $n boots: $(grep 'native tests passed' "$out/log-$n.txt")"
        awk '{print $1}' "$out/results.txt" | sort | uniq -c
        rm -rf "${out:?}/data"
        # Pass only when every test passed: a crashed test (CRASH / TIMEOUT, carried past) or a FAIL fails
        # the run (until 2026-10-04 this exited 0 whenever the last boot finished, hiding a "260/261").
        # A skip (a test whose input, e.g. work/download-3.7.0, is absent) is not a failure.
        if grep -qvE '^(ok|skip) ' "$out/results.txt"; then
            echo "FAIL: $(grep -vcE '^(ok|skip) ' "$out/results.txt") test(s) did not pass:"; grep -vE '^(ok|skip) ' "$out/results.txt"
            exit 1
        fi
        exit 0
    fi
    last=$(grep '^run   ' "$out/log-$n.txt" | tail -1 | awk '{print $2}')
    [ -n "$last" ] || { echo "boot $n: died before any test (rc=$rc; $out/log-$n.txt)"; exit 1; }
    if [ $rc = 124 ] || [ $rc = 137 ]; then echo "TIMEOUT $last" >> "$out/results.txt"; else echo "CRASH $last" >> "$out/results.txt"; fi
    echo "boot $n: rc=$rc in $last"
    done_names=$(grep -E '^(ok  |FAIL|skip)  ' "$out/log-$n.txt" | awk '{print $2}' | paste -sd, -)
    skip="${skip:+$skip,}$last${done_names:+,$done_names}"
done
echo "gave up after $n boots"; exit 1
