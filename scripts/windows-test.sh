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
#   native-order   soa.exe --list-native byte-identical to build/port/soa's: the natives, selftests and
#                  test hooks register in the same order (static-initializer order: cmake/init_order.cmake)
# Needs: build-win/ (scripts/build.sh --windows) and the stage's data, once:
#   scripts/windows-stage.sh --phone --viewer     (C:\soa-win; SOA_WIN_STAGE=/mnt/X/DIR elsewhere)
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo"
[ $# -eq 3 ] || { sed -n '2,19p' "$0" | sed 's/^# \{0,1\}//'; exit 2; }
test=$1 out=$2 tmp=$3
stage=${SOA_WIN_STAGE:-/mnt/c/soa-win}
case $test in
  battle-gacha) targets="soa" need="work/download-3.7.0 work/phone-3.7.0/PHONE.txt" ;;
  seeded) targets="soa-emu soa-server" need="work/download-3.7.0 work/libSOA-3.7.0.so work/phone-3.7.0/PHONE.txt" ;;
  viewer-boot) targets="soa-viewer" need="" ;;  # (its game: checked below)
  shard-login) targets="soa soa-emu soa-server" need="work/download-3.7.0 work/libSOA-3.7.0.so work/phone-3.7.0/PHONE.txt" ;;
  native-order) targets="soa" need="" ;;
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
scripts/windows-stage.sh --quick "$stage" > /dev/null
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
  battle-gacha) exec control/run.py battle-gacha build-win/port/soa.exe "$out" "$tmp" ;;
  seeded) exec control/run.py seeded build-win/emulator/soa-emu.exe build-win/server/soa-server.exe "$out" ;;
  viewer-boot) exec emulator-viewer/scripts/viewer_boot.sh build-win/emulator-viewer/soa-viewer.exe "$out" ;;
  shard-login)
    # its three clients take their own slots (the gate's one is the driver's)
    unset SOA_SLOT_HELD
    SOA=$repo/build-win/port/soa.exe SOA_EMU=$repo/build-win/emulator/soa-emu.exe SOA_SERVER=$repo/build-win/server/soa-server.exe \
      exec tests/diff/run.sh login --out "$out" ;;
esac
