#!/bin/sh
# Episode 2 / 3 opening stories (the in-process local server): title -> home -> Mission -> the episode list ->
# Episode 2 (or 3) -> world map STORY point -> 1-01 -> ストーリー開始 -> オート (auto) -> the
# scene plays its opening movie (m2011_010.mp4 / m6011_010.mp4, the latter from the download
# set) -> the movie must report its end (MovieFinished) -> the scene ends (EndMissionTalk).
#
# The episode's own data (the pack EP<n>: 396 MB for Episode 2, 239 MB for Episode 3) is on the
# shared phone since 2026-10-02 (scripts/make-phone-370.sh with SOA_EPISODE_PACKS=1), but the
# run's client save decides whether the client counts it as downloaded; the client gets it from
# the in-process CDN through its own flow (the server sends Login's LatestEpisodeVersion;
# docs/server-rules.md "Episode data"). SOA_EPISODE_PACKS picks how:
#   0 (default)    the "ask" flow: the client's books have no episode (phone370_client_save: the
#                  save's BAS:DownloadEpisodeFlag 0): the episode list's tap says "このEpisodeを遊ぶにはデータのダウンロードが必要です",
#                  はい goes back to the title ("画面をタップするとEpisodeデータのダウンロードが開始
#                  できます", 閉じる), TAP TO START -> the data phase downloads version_latest_ep<n>
#                  and its bundles only (ダウンロード, 完了) -> home again. The client downloads the
#                  whole pack (its books say none) even when the phone has its files: "必要容量:396MB",
#                  the 165 bundles of EP2 fetched and extracted again (over the run phone's hard
#                  links, by rename: the shared phone is untouched); only the manifest
#                  version_latest_ep<n>.bin isn't fetched again (its .version matches the phone's).
#   1              the "save" flow: the committed save as it is (BAS:DownloadEpisodeFlag 7, Episodes 1-3): the first
#                  data phase after Login downloads all three packs; on a phone that has them (the
#                  shared phone) it only checks their manifests' .version, no download.
# Either way the run checks the GET of version_latest_ep<n>.bin (.version when the phone has the
# pack), the GETs of Android/EP<n>/ (except in the save flow on a phone with the pack), that
# data/files/download/EP<n> exists, and shows その他 -> Episodeデータ管理 (screenshot 05-episode-data).
#
# Ends with PASS (exit 0) or FAIL (exit 1).
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/episode_movie_session.sh <soa> <out-dir> <scratch-dir> [2|3]   (from any directory)
# Runs as a returning player (--campaign-seed CAMPAIGN_SEED, default mf01_001; see campaign_session.sh).
set -eu
SOA=$1; OUT=$2; TMP=$3; EP=${4:-2}
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
HEADLESS=--headless; [ "${WATCH:-0}" != 1 ] || HEADLESS=--windowed  # soa --headless (no window); WATCH=1 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos"
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
if [ "${SOA_EPISODE_PACKS:-0}" = 1 ]; then FLOW_EP=save; else FLOW_EP=ask; fi
# A phone that carries the pack (the shared phone since 2026-10-02): no manifest .bin GET, and in
# the save flow no bundle GET either (the ask flow downloads the pack again).
had_pack=0; [ -d "$TMP/data/data/files/download/EP$EP" ] && had_pack=1
fetch=1; [ "$FLOW_EP" = save ] && [ $had_pack = 1 ] && fetch=0
# The episode's manifest: fetched (.bin) when the phone lacks the pack; with the pack on the phone
# the data phase only GETs version_latest_ep<n>.version (it matches the phone's).
if [ $had_pack = 1 ]; then EPGET="version_latest_ep$EP\.(bin|version)"; else EPGET="version_latest_ep$EP\.bin"; fi
CAMPAIGN_SEED=${CAMPAIGN_SEED:-mf01_001}
timeout -k 10 2400 "$SOA" $HEADLESS --campaign-seed "$CAMPAIGN_SEED" --data "$TMP/data" --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }

fail() { echo "FAIL: $*"; c quit || true; exit 1; }
# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S"
# The notice board and the LOGIN BONUS popup.
python3 $FLOW login-popups "$TMP/fifo" "$L" - - $S/02-home.png || fail "the login popups didn't close"
if [ "$EP" = 3 ]; then Y=470; else Y=730; fi
# ミッション (the 3.7.0 home's second button, as in campaign_session.sh) -> the episode list (Episode 3
# on top, Episode 2 below; phone370_episode_list: via Ep選択 when ミッション opens the map of the last
# episode played, which it does once that episode's data is there).
episode_list() {
  phone370_episode_list "$TMP/fifo" "$L" ${HOME_MISSION_X:-270} 1085 || fail "ミッション didn't open the episode list"
  c wait:6000 shot:$S/$1
}
if [ "$FLOW_EP" = ask ]; then
  # The episode's data isn't there: its tap asks to go back to the title for the download.
  episode_list 03-episodes-before.png
  ! grep -q "GET .*Android/EP$EP/" "$L" || fail "Episode $EP's data was fetched before it was asked for"
  c tap:364:$Y wait:3000 shot:$S/03-download-needed.png
  python3 $FLOW tap-until "$TMP/fifo" "$L" 'port_debug: phase 1 ' 60 10 3 -- tap:515:800 || fail "はい didn't go back to the title"
  # "画面をタップするとEpisodeデータのダウンロードが開始できます。" (閉じる 364:713), TAP TO START
  # (no Login: the client is logged in), the data phase: the episode's download dialog
  # (ダウンロード 515:800), its bundles, 完了 (364:790), home.
  c wait:4000 shot:$S/03-title-dialog.png tap:364:713 wait:3000
  python3 $FLOW tap-until "$TMP/fifo" "$L" "GET .*$EPGET" 90 10 6 -- tap:364:1000 || fail "TAP TO START didn't fetch version_latest_ep$EP"
  python3 $FLOW tap-until "$TMP/fifo" "$L" "GET .*/Android/EP$EP/" 60 10 6 -- wait:3000 tap:515:800 || fail "Episode $EP's download didn't start"
fi
# The episode pack's download (the data phase after Login in the save flow, after TAP TO START in
# the ask flow): its manifest and bundles; done when no GET is logged for 20 s.
i=0
until [ $fetch = 0 ] || grep -q "GET .*/Android/EP$EP/" "$L"; do
  i=$((i + 1)); [ $i -lt 120 ] || fail "no Episode $EP bundle fetched"
  sleep 1
done
_last=-1; _same=0
while [ $_same -lt 20 ]; do
  _n=$(grep -c 'I/http: GET' "$L" || true)
  if [ "$_n" = "$_last" ]; then _same=$((_same + 1)); else _same=0; _last=$_n; fi
  sleep 1
done
grep -Eq "GET .*$EPGET" "$L" || fail "no version_latest_ep$EP ($EPGET)"
echo "episode $EP: $(grep -c "GET .*/Android/EP$EP/" "$L") bundles of Android/EP$EP/ fetched ($FLOW_EP flow)"
[ -d "$TMP/data/data/files/download/EP$EP" ] || fail "no data/files/download/EP$EP after the download"
if [ "$FLOW_EP" = ask ]; then
  c shot:$S/04-download-done.png
  # 完了 (364:790).
  python3 $FLOW tap-until "$TMP/fifo" "$L" 'port_debug: phase 4 ' 180 10 15 -- tap:364:790 || fail "完了 didn't go home"
  python3 $FLOW login-popups "$TMP/fifo" "$L" - - - || fail "the login popups didn't close (after the download)"
fi
# その他 (665:1250) -> scroll -> Episodeデータ管理 (364:595): the episodes and their state; 閉じる.
c tap:665:1250 wait:5000 drag:364:900:364:300:800 wait:2000 drag:364:900:364:300:800 wait:2000 \
  tap:364:595 wait:3000 shot:$S/05-episode-data.png tap:215:1043 wait:2000
# ホーム (60:1240): back home for ミッション.
python3 $FLOW tap-until "$TMP/fifo" "$L" 'port_debug: phase 4 ' 60 15 4 -- tap:60:1240 || fail "ホーム didn't go home"
c wait:3000
episode_list 06-episodes.png
c tap:364:$Y
logw 'campaign: GetWorldMapInfoList'
c wait:8000 shot:$S/07-worldmap.png
# The STORY point (Episode 2 in the middle of the map, Episode 3 left of it) -> 1-01 -> story start.
if [ "$EP" = 3 ]; then c tap:240:650; else c tap:360:640; fi
c wait:4000 tap:364:410 wait:4000 shot:$S/08-mission.png tap:515:714
logw 'port_debug: phase 3 '
# Auto mode until the movie; the scene loads a few seconds after the phase change.
# Auto mode, then fast-forward (as newplayer_session.sh does).
c wait:20000 shot:$S/09-scene.png tap:614:1240 wait:1000 tap:115:45
# (No taps from here on: a tap while the movie plays skips it.)
i=0
while ! grep -q 'PlayMovie(' "$L"; do
  i=$((i + 1)); [ $i -lt 150 ] || fail "no movie"
  sleep 5
done
logw 'movie: playing' 30 || fail "the movie didn't start"
c wait:5000 shot:$S/10-movie.png
# The movie (124 s / 89 s) must end by itself, then the scene continues to its end.
logw 'movie: ended' 300 || fail "the movie didn't end"
c wait:3000 shot:$S/11-after-movie.png
logw 'EndMissionTalk' 300 || fail "the scene didn't end (no EndMissionTalk)"
logw 'story scene played' 30
c wait:8000 shot:$S/12-worldmap.png
c quit
wait $pid || true
trap - EXIT
grep -q 'request EndMissionTalk' "$L" || { echo "FAIL: no EndMissionTalk"; exit 1; }
echo "PASS: episode $EP: the opening movie played to its end, the scene done (EndMissionTalk)"
