#!/usr/bin/env bash
# The static-recompilation prototype (docs/PLAN-recomp.md, "The prototype"): build the
# translator, translate the sample functions (functions.txt) to C++, compile them at -O1 / -O2
# (time and .o size), build the differential harness and run it against the JIT.
#
#   tools/recomp-proto/build.sh [OUT]          (default OUT: work-local scratch /tmp/recomp-proto)
#   tools/recomp-proto/build.sh OUT stats      also translate every function of the lib (IR stats)
#
# Needs a built tree (scripts/build.sh: build/_deps/dynarmic-*, build/runtime/libsoaruntime.a)
# and work/libSOA-3.7.0.so. Linux only; not part of the CMake build or of any gate.
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../.." && pwd)
out=${1:-/tmp/recomp-proto}
mkdir -p "$out"
B=$repo/build
D=$B/_deps/dynarmic-src
DB=$B/_deps/dynarmic-build
LIB=$repo/work/libSOA-3.7.0.so
CXX=${CXX:-g++}
DYN_INC="-I$D/src -I$D/externals/mcl/include -I$D/externals/fmt/include -I$D/externals/robin-map/include -isystem $B/vcpkg_installed/x64-linux/include"
DYN_LIBS="$DB/src/dynarmic/libdynarmic.a $DB/externals/mcl/src/libmcl.a $DB/externals/fmt/libfmt.a $DB/externals/zydis/libZydis.a $DB/externals/zydis/zycore/libZycore.a"

echo "== translator"
$CXX -std=c++20 -O1 $DYN_INC "$here/recomp_gen.cpp" $DYN_LIBS -o "$out/recomp_gen"

if [ "${2:-}" = stats ]; then
  fns=${RECOMP_FUNCTIONS_TSV:-$repo/work/rebase/cov-emu-seeded/prof/functions.tsv}
  echo "== stats over $fns"
  /usr/bin/time -f "%e s, %M KB" "$out/recomp_gen" stats "$LIB" "$fns" > "$out/stats.tsv"
  head -20 "$out/stats.tsv"
fi

echo "== translate (the register file in memory: gen.cpp; in locals: gen-locals.cpp)"
"$out/recomp_gen" emit "$LIB" "$here/functions.txt" "$out/gen.cpp"
"$out/recomp_gen" emit "$LIB" "$here/functions.txt" "$out/gen-locals.cpp" --locals 2>/dev/null
wc -l "$out/gen.cpp" "$out/gen-locals.cpp"

echo "== compile the generated code"
FLAGS="-std=c++20 -ffp-contract=off -fno-strict-aliasing -mcx16 -I$here -I$D/src -I$D/externals/mcl/include -I$D/externals/fmt/include"
for g in gen gen-locals; do
  for o in O0 O1 O2; do
    s=$(date +%s.%N)
    $CXX $FLAGS -$o -c "$out/$g.cpp" -o "$out/$g.$o.o"
    e=$(date +%s.%N)
    printf '%s\t%s\t%.2f s\t%s bytes .text\n' "$g" "$o" "$(echo "$e - $s" | bc)" "$(size -A "$out/$g.$o.o" | awk '$1==".text"{print $2}')"
  done
done

echo "== harness"
RT_INC="-I$repo/runtime/include -I$repo/runtime/src -I$repo/common/include"
V=$B/vcpkg_installed/x64-linux/lib
for g in gen gen-locals; do
$CXX $FLAGS -O2 -g $RT_INC -I$out "$here/harness.cpp" "$out/$g.O2.o" \
  -Wl,--whole-archive "$B/runtime/libsoaruntime.a" -Wl,--no-whole-archive \
  "$B/common/libsoa_gamefiles.a" "$V/libCLI11.a" "$B/common/libsoa_zip.a" "$V/libminizip-ng.a" "$V/libz.a" \
  "$B/common/libsoa_codec.a" "$V/libzstd.a" "$V/libcrypto.a" "$V/libpugixml.a" \
  "$V/libavformat.a" "$V/libavcodec.a" "$V/libswresample.a" "$V/libavutil.a" \
  $DYN_LIBS "$V/libz.a" "$B/common/libsoa_compat.a" \
  /usr/lib/x86_64-linux-gnu/libEGL.so /usr/lib/x86_64-linux-gnu/libGLESv2.so -lm -latomic -lrt -lpthread -ldl -o "$out/harness-$g"
done
for g in gen gen-locals; do
  echo "== run ($g)"
  "$out/harness-$g" "$LIB" "$here/functions.txt" > "$out/harness-$g.txt" || true
  grep -v $'\t0\t$' "$out/harness-$g.txt"
done
