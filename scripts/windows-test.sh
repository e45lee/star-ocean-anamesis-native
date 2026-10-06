#!/bin/bash
# A gate test against the Windows build (tests/tiers.json win:*; README.md "Windows"; port/PLAN.md
# 5b): the incremental Windows build of the programs it runs, the tracked files restaged
# (scripts/windows-stage.sh --quick; the .exe files are refreshed by control/soadrive/winhost.py),
# then the same session or script as on Linux with the .exe files, run from WSL through interop.
#
# Usage: scripts/windows-test.sh TEST OUT TMP
#   battle-gacha   the port's restore session (port/scripts/restore_session.sh): soa.exe in process
#   seeded         the emulator's session (emulator/scripts/emulator_session.sh): soa-emu.exe + soa-server.exe
#   viewer-boot    the viewer's boot (emulator-viewer/scripts/viewer_boot.sh): soa-viewer.exe
#   shard-login    the tests/diff shard `login` on the three Windows targets (soa-emu.exe +
#                  soa-server.exe, soa.exe --server + soa-server.exe, soa.exe in process); OUT/login/report.txt
#   runtime-tests  soaruntime_tests.exe (the runtime's tests, the GDB stub's incl.), exit status 0
#   native-order   soa.exe --list-native byte-identical to build/port/soa's: the natives, selftests and
#                  test hooks register in the same order (static-initializer order: cmake/init_order.cmake)
# Needs: build-win/ (scripts/build.sh --windows) and the stage's data, once:
#   scripts/windows-stage.sh --phone --viewer     (C:\soa-win; SOA_WIN_STAGE=/mnt/X/DIR elsewhere)
# A run's phones and server state on the Windows drive (STAGE/run/soadrive/..., linked from OUT / TMP:
# control/soadrive/winhost.py local_dir) are removed when it passes and kept when it fails;
# scripts/windows-stage.sh --clean removes what is left.
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo"
[ $# -eq 3 ] || { sed -n '2,20p' "$0" | sed 's/^# \{0,1\}//'; exit 2; }
test=$1 out=$2 tmp=$3
stage=${SOA_WIN_STAGE:-/mnt/c/soa-win}
case $test in
  battle-gacha) targets="soa" need="work/SOA-3.7.0-canonical-data.zip work/phone-3.7.0/PHONE.txt" ;;
  seeded) targets="soa-emu soa-server" need="work/SOA-3.7.0-canonical-data.zip work/libSOA-3.7.0.so work/phone-3.7.0/PHONE.txt" ;;
  viewer-boot) targets="soa-viewer" need="" ;;  # (its game: checked below)
  shard-login) targets="soa soa-emu soa-server" need="work/SOA-3.7.0-canonical-data.zip work/libSOA-3.7.0.so work/phone-3.7.0/PHONE.txt" ;;
  native-order) targets="soa" need="" ;;
  runtime-tests) targets="soaruntime_tests" need="" ;;
  *) echo "windows-test: unknown test $test" >&2; exit 2 ;;
esac
[ -f build-win/CMakeCache.txt ] || { echo "FAIL: no build-win/ (scripts/build.sh --windows)"; exit 1; }
for n in $need; do
  [ -e "$stage/$n" ] || { echo "FAIL: $stage/$n isn't staged (scripts/windows-stage.sh --phone --viewer)"; exit 1; }
done
if [ "$test" = viewer-boot ] && ! ls "$stage"/apk/*.xapk > /dev/null 2>&1 && [ ! -e "$stage/work/extracted/xapk" ]; then  # 380-ok: soa-viewer's game
  echo "FAIL: soa-viewer's game isn't staged in $stage/apk (scripts/windows-stage.sh --viewer)"; exit 1
fi
mkdir -p "$out"
# shellcheck disable=SC2086
scripts/build.sh --windows --target $targets > "$out/build-win.log" 2>&1 ||
  { tail -20 "$out/build-win.log"; echo "FAIL: the Windows build (see $out/build-win.log)"; exit 1; }
scripts/windows-stage.sh --quick "$stage" > "$out/stage.log" 2>&1 ||
  { tail -20 "$out/stage.log"; echo "FAIL: staging into $stage (see $out/stage.log)"; exit 1; }
# The run's dirs on the Windows drive: the targets of the links under OUT / TMP into STAGE/run/
cleanup_run() {
  local root l t n=0
  root=$(realpath -m "$stage/run")
  while IFS= read -r -d '' l; do
    t=$(readlink -f "$l") || continue
    case $t in "$root"/*) rm -rf "$t"; rm -f "$l"; n=$((n + 1)) ;; esac
  done < <(find "$out" "$tmp" -type l -print0 2> /dev/null)
  [ "$n" = 0 ] || echo "(removed this run's $n dir(s) under $root)"
}
case $test in
  native-order)
    [ -x build/port/soa ] || { echo "FAIL: no build/port/soa (scripts/build.sh)"; exit 1; }
    build/port/soa --list-native > "$out/linux.txt" 2> /dev/null
    (cd "$stage" && ./build-win/port/soa.exe --list-native 2> /dev/null) | tr -d '\r' > "$out/windows.txt"
    [ -s "$out/linux.txt" ] || { echo "FAIL: build/port/soa --list-native printed nothing"; exit 1; }
    if ! cmp -s "$out/linux.txt" "$out/windows.txt"; then
      diff "$out/linux.txt" "$out/windows.txt" | head -20
      echo "FAIL: soa.exe --list-native differs from Linux's ($out/{linux,windows}.txt): registration order (cmake/init_order.cmake)"
      exit 1
    fi
    echo "PASS: soa.exe --list-native == Linux's ($(wc -l < "$out/linux.txt") natives, same order)" ;;
  runtime-tests)
    # (run in the stage; its scratch files go to the Windows temp dir. The exit status covers the
    # exit: nothing per-thread runs after the static destructors, runtime/src/core/thread_record.h.)
    rc=0
    (cd "$stage" && timeout -k 10 600 ./build-win/runtime/soaruntime_tests.exe) > "$out/soaruntime_tests.log" 2>&1 || rc=$?
    grep -a "^FAIL" "$out/soaruntime_tests.log" | head -20
    if [ "$rc" != 0 ]; then
      tail -5 "$out/soaruntime_tests.log"
      echo "FAIL: soaruntime_tests.exe exited $rc ($out/soaruntime_tests.log)"
      exit 1
    fi
    echo "PASS: soaruntime_tests.exe ($(grep -ac '^ok' "$out/soaruntime_tests.log") checks)" ;;
  battle-gacha|seeded|viewer-boot|shard-login)
    rc=0
    case $test in
      battle-gacha) control/run.py battle-gacha build-win/port/soa.exe "$out" "$tmp" || rc=$? ;;
      seeded) control/run.py seeded build-win/emulator/soa-emu.exe build-win/server/soa-server.exe "$out" || rc=$? ;;
      viewer-boot) emulator-viewer/scripts/viewer_boot.sh build-win/emulator-viewer/soa-viewer.exe "$out" || rc=$? ;;
      shard-login)
        # its three clients take their own slots (the gate's one is the driver's)
        (unset SOA_SLOT_HELD
         SOA=$repo/build-win/port/soa.exe SOA_EMU=$repo/build-win/emulator/soa-emu.exe SOA_SERVER=$repo/build-win/server/soa-server.exe \
           exec tests/diff/run.sh login --out "$out") || rc=$? ;;
    esac
    # passed: its dirs on the Windows drive go (kept for a failure: scripts/windows-stage.sh --clean)
    if [ "$rc" = 0 ]; then cleanup_run; else echo "(kept this run's dirs under $stage/run for the failure)"; fi
    exit "$rc" ;;
esac
