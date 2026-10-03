#!/bin/sh
# The restored 3.7.0 home (the in-process local server; restore370 groups home, common, othermenu):
# boot -> notice board -> LOGIN BONUS -> the home, then every home button, each checked by the
# phase it switches to or the server request it sends (log lines), with a screenshot per screen:
#   main buttons   イベント (phase 5, the event list: is_open_event_mission 1 and the areas the
#                  event module serves, server/src/api/events/event_missions.cpp),
#                  ミッション (phase 8, episode list), スフィア211 (phase 5, the Sphere 211 board:
#                  is_open_extra_dungeon 1 and the season the sphere211 module serves),
#                  ディープスペース探査 (phase 6, CPhase_DeepSpace);
#   side buttons   ≡ menu -> お知らせ (the local notice page), フォロー (phase 13, FollowList / Blacklist; player search -> error 10002),
#                  称号 (the list, SetTitle, 外す); プレゼント (phase 14, PresentList); 実績 (AchievementActiveList); オススメ!
#                  (phase 28); 情報保存; the stamina "+";
#   footer         キャラクター (11), アイテム (9), ガチャ (17, GetGachaInData), ショップ (10), その他
#                  (12, the 3.7.0 other menu), ホーム (4).
# When HOME_REF names a directory of reference screenshots (same file names, e.g. from Waydroid or
# a 3.7.0 device), each shot is compared with ImageMagick (RMSE on a small copy) and reported.
# Exit status 1 if a destination isn't reached.
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/home_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
export SOA_HEADLESS="${SOA_HEADLESS:-1}"  # soa --headless (no window); SOA_HEADLESS=0 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py; REF=work/port-test/smoke-base
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos"
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
SOA_SERVER_SEED_RNG=${SOA_SERVER_SEED_RNG:-1} timeout -k 10 1800 "$SOA" --data "$TMP/data" \
  --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
fails=0
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
screen() { python3 $FLOW wait-screen "$TMP/fifo" "$S/$1.png" "$REF/$2.png" "${3:-180}"; }
# check NAME REGEX [TIMEOUT]: the destination's log line; a miss is reported and counted.
check() {
  if python3 $FLOW wait-log "$L" "$2" "${3:-60}" > /dev/null; then echo "ok   $1"; else echo "FAIL $1 (no '$2')"; fails=$((fails + 1)); fi
}
# checkt NAME REGEX TIMEOUT EVERY TRIES -- CMD...: the commands, resent until REGEX is logged
# (flowctl.py tap-until: for taps the game drops under load); a miss is reported and counted.
checkt() {
  n=$1; shift
  if python3 $FLOW tap-until "$TMP/fifo" "$L" "$@" > /dev/null; then echo "ok   $n"; else echo "FAIL $n (no '$1')"; fails=$((fails + 1)); fi
}
home() { checkt "$1 -> home" 'port_debug: phase 4 ' 30 15 2 -- tap:60:1250; c wait:5000; }

# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S" && echo "ok   login"
# The notice board, then the LOGIN BONUS popup (flowctl.py login-popups taps 閉じる until each is gone).
python3 $FLOW login-popups "$TMP/fifo" "$L" $S/02-notice.png $S/03-login-bonus.png $S/04-home.png || { echo "FAIL login popups"; fails=$((fails + 1)); }

# ---- main buttons ----------------------------------------------------------------------------
checkt event 'port_debug: phase 5 ' 60 20 3 -- tap:95:1085
c wait:6000 shot:$S/10-event.png
home event
# ミッション -> the episode list (phone370_episode_list: via Ep選択 when it opens the last episode's map)
if phone370_episode_list "$TMP/fifo" "$L" > /dev/null; then echo "ok   mission"; else echo "FAIL mission (no 'port_debug: phase 8 ')"; fails=$((fails + 1)); fi
c wait:5000 shot:$S/11-mission.png
home mission
checkt sphere211 'request GetSphere211Info' 60 20 3 -- tap:455:1085
c wait:6000 shot:$S/12-sphere211.png
home sphere211
checkt deepspace 'port_debug: phase 6 ' 60 20 3 -- tap:635:1085
c wait:8000 shot:$S/13-deepspace.png
home deepspace

# ---- side buttons ----------------------------------------------------------------------------
c tap:668:200 wait:2000 shot:$S/20-menu.png tap:445:200; check follow 'request Blacklist'
c wait:4000 shot:$S/21-follow.png tap:364:537 wait:3000 tap:327:610 wait:1500 text:1234567890 wait:1000 tap:532:610
check follow-search 'SearchPlayer refused'
c wait:4000 shot:$S/22-follow-search.png tap:364:710 wait:2000 tap:364:738 wait:4000 shot:$S/23-recent.png
c tap:100:1120 wait:3000 tap:100:1120; check follow-back 'port_debug: phase 4 ' 30
# 称号: the title list (TitleList: the default titles under その他, server/src/api/player/titles.cpp); a tap on
# the second one sets it (SetTitle; the status bar's plate follows), 外す takes it off (SetTitle 0).
c wait:5000 tap:668:200 wait:2000 tap:555:200 wait:4000 shot:$S/24-titles.png tap:590:303 wait:2000 shot:$S/24a-titles-other.png
checkt set-title 'I/server: SetTitle [1-9]' 30 10 2 -- tap:364:600
c wait:3000 shot:$S/24b-title-set.png tap:364:800 wait:2000
checkt remove-title 'I/server: SetTitle 0$' 30 10 2 -- tap:515:1053
c wait:3000 shot:$S/24c-title-removed.png tap:364:800 wait:2000 tap:213:1053 wait:2000
# お知らせ: the notice board from the menu shows the local server's page (server/src/api/player/notice.cpp):
# drawn by the web view ("webview: page http..."; native/ui/webview_page_view.cpp), or as text in the popup
# when it can't ("webview: local page shown"; native/ui/webview_local.cpp), as the login's notice board did.
# (the ≡ menu may still be open after the title list: resent, the pair opens it the second time)
checkt notice 'webview: (local page shown|page http)' 40 12 3 -- tap:668:200 wait:2000 tap:335:200
c wait:4000 shot:$S/24d-notice.png tap:364:1133 wait:3000
c tap:668:315; check present 'request PresentList'
c wait:4000 shot:$S/25-present.png tap:100:1120; check present-back 'port_debug: phase 4 ' 30
c wait:5000 tap:668:425; check achievements 'request AchievementActiveList'
c wait:4000 shot:$S/26-achievements.png tap:213:1050 wait:2000
c tap:668:535; check recommended 'port_debug: phase 28 '
c wait:4000 shot:$S/27-recommended.png tap:100:1120; check recommended-back 'port_debug: phase 4 ' 30
c wait:5000 tap:668:645 wait:3000 shot:$S/28-datasave.png tap:364:800 wait:2000
c tap:303:70 wait:3000 shot:$S/29-stamina.png tap:364:800 wait:2000

# ---- footer ----------------------------------------------------------------------------------
checkt character 'port_debug: phase 11 ' 60 20 3 -- tap:180:1250
c wait:6000 shot:$S/30-character.png
home character
checkt item 'port_debug: phase 9 ' 60 20 3 -- tap:300:1250
c wait:5000 shot:$S/31-item.png
home item
checkt gacha 'request GetGachaInData' 60 20 3 -- tap:425:1250
c wait:8000 shot:$S/32-gacha.png
home gacha
checkt shop 'port_debug: phase 10 ' 60 20 3 -- tap:545:1250
c wait:5000 shot:$S/33-shop.png
home shop
checkt other 'port_debug: phase 12 ' 60 20 3 -- tap:665:1250
c wait:5000 shot:$S/34-other.png drag:364:900:364:500 wait:2000 shot:$S/35-other-2.png drag:364:900:364:500 wait:2000 shot:$S/36-other-3.png
home other
c wait:3000 shot:$S/40-home.png
c quit || true
wait $pid || true
trap - EXIT

# Contact sheet, and the optional comparison with reference shots.
montage "$S"/*.png -tile 8x -geometry 182x324+2+2 "$OUT/strip.png" 2>/dev/null || true
if [ -n "${HOME_REF:-}" ]; then
  for f in "$S"/*.png; do
    r=$HOME_REF/$(basename "$f")
    [ -f "$r" ] || continue
    m=$(compare -metric RMSE -resize 182x324 "$f" "$r" null: 2>&1 | sed 's/.*(\(.*\))/\1/')
    echo "ref  $(basename "$f") rmse=$m"
  done
fi
if [ $fails = 0 ]; then echo "PASS: every home destination reached"; else echo "FAIL: $fails destinations missed"; exit 1; fi
