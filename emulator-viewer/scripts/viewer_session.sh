#!/bin/bash
# A session through what the offline 3.8.0 build offers, in the viewer (emulator-viewer/README.md
# "Checks"). Builds nothing.
#
# Usage: emulator-viewer/scripts/viewer_session.sh [soa-viewer binary] [out dir] [extra soa-viewer args...]
#   defaults: build/emulator-viewer/soa-viewer (the repository build: scripts/build.sh); a fresh
#   mktemp dir (kept: the log and screenshots; the phone's data is deleted unless KEEP_DATA=1)
# Env: VIEWER_RECORD=1 records the missing reference screenshots (delete ref/NAME.png to re-record
#   it; check new ones by eye),
#   VIEWER_RMSE (default 0.08), VIEWER_DATA (see viewer_lib.sh).
#
# Starts soa-viewer headless on a fresh phone (no save, no server) and drives it with taps and
# screenshots only, each step waiting until the screen matches its reference (RMSE at 182x324, as
# port/scripts/smoke.py):
#    1. title; NoLoginStart's lookup answered "not found" (offline)
#    2. TAP TO START -> the stand-alone terms prompt (a new player)
#    3. 利用規約 -> the terms' web view (file:///android_asset/kiyaku.html; the runtime has no web
#       view: an empty panel) -> 閉じる
#    4. 同意する -> the data check -> home (home_sa: the local player アナムネシス, rank 1)
#    5. キャラクター -> the character book (every master role) -> a character's detail ->
#       ステータス詳細 -> 閉じる -> 閉じる
#    6. ホーム -> 会話モード (interactive mode) -> お気に入り変更 (the three starter roles) -> 戻る ->
#       2D/3D変更 (the 3D model) -> 2D/3D変更 -> ホーム
#    7. その他 -> コピーライト (web view) -> 閉じる -> 設定 -> グラフィック設定 -> 閉じる ->
#       サウンド設定 -> 閉じる -> 戻る
#    8. ホーム -> ミッション -> the episode select -> Episode 2 -> the scenario library (chapters) ->
#       CHAPTER:10 -> 10-22 -> ストーリー開始 -> the story (a scenario scene) -> スキップ / はい,
#       through its movie (PlayMovie), back to the library
#    9. その他 -> タイトルに戻る -> はい -> the title -> TAP TO START -> home (no terms prompt: the
#       answer was saved)
# Prints PASS / FAIL per milestone and a final PASS / FAIL (exit 0 / 1). Kills only the
# soa-viewer it started.
here=$(cd "$(dirname "$0")" && pwd)
bin=${1:-$here/../../build/emulator-viewer/soa-viewer}
out=${2:-$(mktemp -d "${TMPDIR:-/tmp}/viewer-session.XXXXXX")}
shift $(( $# > 2 ? 2 : $# ))
mkdir -p "$out"
out=$(cd "$out" && pwd)
# shellcheck source=viewer_lib.sh
. "$here/viewer_lib.sh"

FOOT_HOME=60:1240 FOOT_CHARA=183:1230 FOOT_OTHER=300:1230
# Crops (182x324 space) for screens with changing content: home above the mascot's speech
# bubble (Coro speaks a random line now and then), the story's bottom bar (スキップ / オート), a
# dialog's band.
CROP_HOME=182x205+0+0 CROP_STORY=182x28+0+296 CROP_DIALOG=182x80+0+125

start_viewer "$bin" "$@"

# 1.-2. The title and the terms prompt.
reach title 240 || finish
wait_log "NoLoginStart: production-game.so-ana.com not found (offline)" 30 "getaddrinfo(production-game.so-ana.com): the service is gone" || finish
reach terms 60 364:1000 || finish
# 3. 利用規約: the web view's panel.
reach webview-terms 30 364:578 || finish
in_log "ShowWebView(file:///android_asset/kiyaku.html" && pass "terms page requested (ShowWebView kiyaku.html)" || miss "no ShowWebView(kiyaku.html)"
reach terms 30 364:1133 || finish
# 4. 同意する -> the data check -> home.
reach home 180 364:689 "$CROP_HOME" || finish

# 5. The character book, a detail, its status.
reach charbook 60 $FOOT_CHARA || finish
reach chardetail 30 364:600 || finish
reach status 30 163:530 || finish
reach chardetail 30 364:993 || finish
reach charbook 30 364:1073 || finish

# 6. Interactive mode: the favourite list, the 3D model and back.
reach home 60 $FOOT_HOME "$CROP_HOME" || finish
reach talk 30 90:740 || finish
reach favorite 30 $FOOT_CHARA || finish
reach talk 30 100:1120 || finish
reach talk-3d 60 $FOOT_OTHER || finish
reach talk 60 $FOOT_OTHER || finish
reach home 60 $FOOT_HOME "$CROP_HOME" || finish

# 7. The other menu: copyright, settings.
reach other 60 $FOOT_OTHER || finish
reach webview-copyright 30 364:458 || finish
in_log "ShowWebView(file:///android_asset/copyright_android.html" && pass "copyright page requested (ShowWebView)" || miss "no ShowWebView(copyright_android.html)"
reach other 30 364:1133 || finish
reach settings 30 364:347 || finish
reach graphics 30 364:357 || finish
reach settings 30 364:1042 || finish
reach sound 30 364:478 || finish
reach settings 30 364:1042 || finish
reach other 30 100:1120 || finish

# 8. Missions: the scenario library and a story, skipped through its movie.
reach home 60 $FOOT_HOME "$CROP_HOME" || finish
reach episodes 60 90:1085 || finish
reach chapters 30 364:730 || finish
reach chapter10 30 364:557 || finish
reach story-confirm 30 364:350 "$CROP_DIALOG" || finish
reach story 90 515:714 "$CROP_STORY" || finish
# スキップ -> はい, until the library is back (the skip goes on to the story's movie and the
# scenes after it).
end=$(( $(date +%s) + 240 ))
while ! matches chapter10; do
    alive > /dev/null || { miss "story -> library ($(alive))"; finish; }
    [ "$(date +%s)" -lt $end ] || { miss "story skipped -> back to the library (not within 240s)"; finish; }
    ctl tap:115:1240 wait:2500 tap:515:742
    sleep 6
done
pass "story skipped -> back to the library"
in_log "PlayMovie(" && pass "the story's movie played (PlayMovie)" || miss "no PlayMovie"

# 9. Back to the title, and in again: no terms prompt this time.
reach other 60 $FOOT_OTHER || finish
reach to-title 30 364:792 "$CROP_DIALOG" || finish
reach title 120 515:714 || finish
reach home 180 364:1000 "$CROP_HOME" || finish
finish
