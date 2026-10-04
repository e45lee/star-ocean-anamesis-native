#!/bin/bash
# The CDN's byte-identical proof (server/PLAN-readability.md R18; the replay of RG4 builds no CDN):
# runs `soa-server --cdn-check` with two builds over every path the CDN serves (2,000 paths per run,
# so the runs split the same way whatever the arguments) and compares what
# they answer (status, size, SHA-1, content type per path) and their logs (times and the scratch
# dir masked), with the stand-ins on and off, each from an empty scratch dir and again with the
# bundle-hash cache it wrote (the cache's reuse path). The process's time() is frozen (an
# LD_PRELOAD shim built here with cc): version.bin's "time" entries are the server clock (--clock
# plus the seconds since the start), which would otherwise differ between two runs.
#   tools/server_cdn_check.sh BIN_A BIN_B [OUT_DIR]
# The paths: version.bin, the manifests (.bin, .version) of manifest/etc2/hi, version.version, the
# served master (both URL forms), every bundle the download's manifests name, the stand-in bundles
# and files, and one missing name. Needs work/download-3.7.0 and data/basmaster-3.7.0.sqlite3.
# Exit 0 identical, 1 different (the differences are printed).
# DOWNLOAD_A / DOWNLOAD_B (default work/download-3.7.0): the download each side serves, a folder or
# the zip (SOA-3.7.0-canonical-data.zip, read in place): BIN_A = BIN_B with DOWNLOAD_B=the zip proves
# the CDN serves the same bytes from either (README.md "Packaging"); the paths are masked in the output.
set -uo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo"
[ $# -ge 2 ] || { sed -n '2,10p' "$0" | sed 's/^# \{0,1\}//'; exit 2; }
a=$1 b=$2 out=${3:-$(mktemp -d /tmp/server-cdn-check.XXXXXX)}
mkdir -p "$out"
paths="$out/paths.txt"
"$repo/.venv/bin/python" - > "$paths" <<'PY'
import os, msgpack
def chash32(s):
    t = []
    for i in range(256):
        c = i
        for _ in range(8): c = (c >> 1) ^ 0xEDB88320 if c & 1 else c >> 1
        t.append(c)
    b = s.encode(); c = len(b)
    for x in b: c = t[(c ^ x) & 0xff] ^ (c >> 8)
    return c
fixed = ["version.bin", "manifest/etc2/hi/version.version", "sqlite/basmaster.sqlite3", "nonexistent.bin"]
names = set()
for m in ["Bulk", "Individual", "ep1", "ep2", "ep3"]:
    fixed += ["manifest/etc2/hi/version_latest_%s.bin" % m, "manifest/etc2/hi/version_latest_%s.version" % m]
    v = msgpack.unpackb(open("work/download-3.7.0/manifest/etc2/hi/version_latest_%s.bin" % m, "rb").read(), raw=False, strict_map_key=False)
    names.update(v["assets"].keys())
names.add("B/5374616e/standins.bin")
for root, dirs, files in os.walk("standin-assets"):
    for f in files:
        rel = os.path.relpath(os.path.join(root, f), "standin-assets")
        names.add(rel)
        names.add("I/5374616e/%08x.bin" % chash32(rel))
for p in fixed: print("Android/" + p)
print("master/1/sqlite/basmaster.sqlite3")
for n in sorted(names): print("Android/" + n)
PY
shim="$out/frozen_time.so"
printf '#include <time.h>\ntime_t time(time_t* t) { if (t) *t = 1790856005; return 1790856005; }\n' > "$out/frozen_time.c"
cc -shared -fPIC -o "$shim" "$out/frozen_time.c" || { echo "cannot build the time shim"; exit 2; }
# run BIN TAG EXTRA...: two passes on one fresh scratch dir (cold, then the hash cache)
run() {
  local bin=$1 tag=$2 dl=$3; shift 3
  local s; s=$(mktemp -d /tmp/server-cdn-check-scratch.XXXXXX)
  for pass in cold warm; do
    LD_PRELOAD="$shim" xargs -n 2000 -a "$paths" -d '\n' "$bin" --master data/basmaster-3.7.0.sqlite3 --download-dir "$dl" \
      --clock "2026-10-01 12:00:05" --cdn-scratch "$s" "$@" --cdn-check > "$out/$tag.$pass.raw.txt" 2> "$out/$tag.$pass.raw.log"
    sed -E "s#$s#SCRATCH#g; s#$dl#DOWNLOAD#g; s/[0-9]{2}:[0-9]{2}:[0-9]{2}(\.[0-9]+)?//g" "$out/$tag.$pass.raw.log" > "$out/$tag.$pass.log"
    sed -E "s#$dl#DOWNLOAD#g" "$out/$tag.$pass.raw.txt" > "$out/$tag.$pass.txt"
  done
  rm -rf "${s:?}"
}
fail=0
for mode in on off; do
  extra=(); [ "$mode" = off ] && extra=(--standin-assets off)
  run "$a" "a-$mode" "${DOWNLOAD_A:-work/download-3.7.0}" "${extra[@]}"
  run "$b" "b-$mode" "${DOWNLOAD_B:-work/download-3.7.0}" "${extra[@]}"
  for pass in cold warm; do
    for kind in txt log; do
      if ! diff -q "$out/a-$mode.$pass.$kind" "$out/b-$mode.$pass.$kind" > /dev/null; then
        echo "DIFF  stand-ins $mode, $pass, $kind:"; diff "$out/a-$mode.$pass.$kind" "$out/b-$mode.$pass.$kind" | head -20; fail=1
      fi
    done
  done
  n=$(grep -vc '^CDN:' "$out/a-$mode.cold.txt"); served=$(awk -F'\t' '$2==200' "$out/a-$mode.cold.txt" | wc -l)
  echo "stand-ins $mode: $n paths ($served served), cold and warm: $([ $fail = 0 ] && echo identical || echo DIFFERENT)"
done
[ $fail = 0 ] && echo "PASS: identical ($out)" || echo "FAIL: different ($out)"
exit $fail
