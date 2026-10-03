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
# Needs: build-win/ (scripts/build.sh --windows) and the stage's data, once:
#   scripts/windows-stage.sh --phone --viewer     (C:\soa-win; SOA_WIN_STAGE=/mnt/X/DIR elsewhere)
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo"
[ $# -eq 3 ] || { sed -n '2,15p' "$0" | sed 's/^# \{0,1\}//'; exit 2; }
test=$1 out=$2 tmp=$3
stage=${SOA_WIN_STAGE:-/mnt/c/soa-win}
case $test in
  battle-gacha) targets="soa" need="work/download-3.7.0 work/phone-3.7.0/PHONE.txt" ;;
  seeded) targets="soa-emu soa-server" need="work/download-3.7.0 work/libSOA-3.7.0.so work/phone-3.7.0/PHONE.txt" ;;
  viewer-boot) targets="soa-viewer" need="work/extracted/xapk" ;;
  *) echo "windows-test: unknown test $test" >&2; exit 2 ;;
esac
[ -f build-win/CMakeCache.txt ] || { echo "FAIL: no build-win/ (scripts/build.sh --windows)"; exit 1; }
for n in $need; do
  [ -e "$stage/$n" ] || { echo "FAIL: $stage/$n isn't staged (scripts/windows-stage.sh --phone --viewer)"; exit 1; }
done
# shellcheck disable=SC2086
mkdir -p "$out"
scripts/build.sh --windows --target $targets > "$out/build-win.log" 2>&1 ||
  { tail -20 "$out/build-win.log"; echo "FAIL: the Windows build (see $out/build-win.log)"; exit 1; }
scripts/windows-stage.sh --quick "$stage" > /dev/null
case $test in
  battle-gacha) exec control/run.py battle-gacha build-win/port/soa.exe "$out" "$tmp" ;;
  seeded) exec control/run.py seeded build-win/emulator/soa-emu.exe build-win/server/soa-server.exe "$out" ;;
  viewer-boot) exec emulator-viewer/scripts/viewer_boot.sh build-win/emulator-viewer/soa-viewer.exe "$out" ;;
esac
