#!/bin/sh
# Scripted profiling flow over screens smoke.sh and the other sessions don't visit (729x1296
# window), with SOA_COVERAGE and SOA_PROFILE written into the out dir (port/README.md
# "Profiling"): title -> Login -> the data check -> home (notice board, LOGIN BONUS) -> the mascot's
# line -> その他 (phase 12) -> 設定 (phase 18) -> its six popups (グラフィック, バトル, サウンド, 通知,
# イベント, その他設定: each slider tapped down and up again, scrolled, closed) -> 戻る -> ヘルプ (its
# web view, closed) -> 称号 (the title list, closed) -> キャラクター (phase 11) -> 装備・技・アシスト変更
# -> the list scrolled end to end -> a character's detail -> 戻る -> ショップ (phase 10) -> アイテム
# (phase 9) -> ホーム (phase 4) -> プレゼント (PresentList) -> home.
# Each screen change waits for its log line (phase changes, the server's request lines, the web
# view), then screenshots ($OUT/shots). The slider taps change the client's local settings and
# set them back. Ends with PASS (exit 0) or FAIL (exit 1), when a screen isn't reached or the
# profile isn't written.
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/profile_extra.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Then: port/scripts/profile_report.py <out-dir>
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
export SOA_HEADLESS="${SOA_HEADLESS:-1}"  # soa --headless (no window); SOA_HEADLESS=0 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}"
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
SOA_SERVER_SEED_RNG=${SOA_SERVER_SEED_RNG:-1} SOA_COVERAGE="$OUT" SOA_PROFILE="$OUT" timeout -k 10 2400 "$SOA" --data "$TMP/data" \
  --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
fails=0
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@" > /dev/null; }
# go NAME REGEX -- CMD...: the commands, resent until REGEX is logged; a miss is reported and counted.
go() {
  n=$1; rx=$2; shift 3
  if python3 $FLOW tap-until "$TMP/fifo" "$L" "$rx" 60 20 3 -- "$@" > /dev/null; then echo "ok   $n"; else echo "FAIL $n (no '$rx')"; fails=$((fails + 1)); fi
}
fail() { echo "FAIL: $*"; c quit || true; exit 1; }

# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S"
python3 $FLOW login-popups "$TMP/fifo" "$L" - - $S/02-home.png > /dev/null || fail "the login popups didn't close"
# The mascot (コロ): a line.
c tap:90:900 wait:4000 shot:$S/03-mascot.png

# ---- その他 -> 設定: six popups, each slider row's - then + (the first row at y 350), a scroll, 閉じる
go other 'port_debug: phase 12 ' -- tap:665:1250
c wait:5000 shot:$S/10-other.png
go settings 'port_debug: phase 18 ' -- tap:364:347
c wait:5000 shot:$S/11-settings.png
i=12
for y in 357 468 580 690 803 913; do
  c tap:364:$y wait:4000 shot:$S/$i-settings-popup.png tap:311:350 wait:1500 tap:640:350 wait:1500 \
    drag:364:850:364:350 wait:2500 shot:$S/$i-settings-popup-scrolled.png tap:364:1043 wait:3000
  i=$((i + 1))
done
go settings-back 'port_debug: phase 12 ' -- tap:100:1120
c wait:5000
# ヘルプ: a web view (ShowWebView(http...); not shown on the desktop), closed with 閉じる.
go help 'ShowWebView\(http' -- tap:364:458
c wait:4000 shot:$S/20-help.png
go help-close 'ShowWebView\(\) not supported' -- tap:364:1133
# 称号: the title list, 閉じる.
# (the list the login fetched: no request)
c tap:364:903
c wait:4000 shot:$S/21-titles.png tap:213:1053 wait:3000

# ---- キャラクター -> 装備・技・アシスト変更: the list scrolled to its end and back, a character
go character 'port_debug: phase 11 ' -- tap:180:1250
c wait:5000 tap:364:435 wait:5000 shot:$S/30-charlist.png
c drag:364:950:364:300 wait:1500 drag:364:950:364:300 wait:1500 drag:364:950:364:300 wait:3000 shot:$S/31-charlist-end.png
c drag:364:300:364:950 wait:1500 drag:364:300:364:950 wait:1500 drag:364:300:364:950 wait:3000
c tap:630:465 wait:5000 shot:$S/32-chardetail.png tap:100:1120 wait:4000
# ---- ショップ, アイテム, ホーム, プレゼント
go shop 'port_debug: phase 10 ' -- tap:545:1250
c wait:6000 shot:$S/40-shop.png
go item 'port_debug: phase 9 ' -- tap:300:1250
c wait:5000 shot:$S/41-item.png
go home 'port_debug: phase 4 ' -- tap:60:1250
c wait:6000
go present 'request PresentList' -- tap:668:315
c wait:5000 shot:$S/42-present.png
go present-back 'port_debug: phase 4 ' -- tap:100:1120
c wait:6000 shot:$S/43-home.png profile-dump
c quit || true
wait $pid || true
trap - EXIT

for f in coverage.tsv stacks.folded functions.tsv; do
  [ -s "$OUT/$f" ] || { echo "FAIL: $OUT/$f wasn't written"; fails=$((fails + 1)); }
done
grep -qE 'Unhandled SIG|\*\*\* host signal' "$L" && { echo "FAIL: soa crashed"; fails=$((fails + 1)); }
[ $fails = 0 ] || { echo "FAIL: $fails steps"; exit 1; }
echo "PASS: settings (6 popups), help, titles, the character list and a detail, shop, items, presents; profile in $OUT ($(wc -l < "$OUT/coverage.tsv") functions covered)"
