#!/bin/bash
# Summer demonstration: the unmodified 3.7.0 client in the emulator (soa-emu) against soa-server
# with the summer events enabled, from boot to a summer event battle and a summer gacha 10-draw,
# with numbered screenshots and a contact sheet. Builds nothing.
#
# Usage: emulator/scripts/summer_demo.sh [options] [OUT]
#   OUT               where the screenshots, logs and state dumps go (default
#                     work/test/summer-demonstration); its old *.png, *.log and state-*.txt are
#                     deleted first, other files (README.md) are kept
#   --watch           show the emulator's window (default: headless)
#   --clock C         the date both the server and the phone start at, "YYYY-MM-DD HH:MM:SS"
#                     (default "2026-10-01 12:00:00": a fixed calendar, so the event list's rows and
#                     the seeded draws are the same every run); "host" runs on the real date
#   --emu FILE        soa-emu (default build/emulator/soa-emu)
#   --server FILE     soa-server (default build/server/soa-server)
#   -h, --help        this text
# Env:
#   SOA_PHONE         the phone's game data (scripts/shared-phone.sh): unset -> the run's phone is
#                     hard-linked from the shared pre-downloaded phone work/phone-3.7.0 (when it is
#                     built and unchanged; never modified); "none" -> an empty phone: the client
#                     downloads its 3 GB from soa-server's CDN, with three more screenshots
#                     (download-prompt, download-dialog, download-done); a directory -> copied
#   EMU_DATA=DIR      run on DIR as the phone itself (e.g. a KEEP_SCRATCH=1 run's phone); never
#                     deleted
#   KEEP_SCRATCH=1    keep the scratch dir (the phone, the server state, the packet bodies); its
#                     path is printed
#
# What it does (emulator/README.md "Summer demonstration"):
#   soa-server: a fresh state seeded from data/saves/seed/Game.xml (player LOCAL00001), the CDN
#   from work/download-3.7.0, --enable-events (default keywords 水着,夏,サマー,!福袋), --seed-rng 1,
#   --log-packets; soa-emu pointed at it. Driven with control/soactl.py taps and screenshots; each
#   step waits for its request in soa-server's packet log (or its screen) before going on:
#   1. launch: boot, title (NoLoginStart), TAP TO START (StartBridge, Login), the game data
#      download, the notice board and LOGIN BONUS (control/flowctl.py login-popups), home;
#   2. summer event: イベント (CheckEventRankingResult) -> the 水着イベント2020 board (星の海と夢の渚,
#      event_sww2020_93; found by its beach) -> its first story mc99_565 (MissionTalk, skipped:
#      EndMissionTalk), which unlocks the battle me99_1054 ビーチスポーツ？【初級】 (the board's
#      first battle me99_1053 needs a mission ticket the seeded player lacks) -> single play, no
#      rental, party 1 -> MissionStart -> the battle (the party's AI) -> MissionEnd -> the result
#      pages -> back on the board (CheckEventRankingResult); then home;
#   3. summer gacha: ガチャ (GetGachaInData) -> the first banner, 復刻水着2020① (a summer step-up;
#      checked against the master's gacha name) -> 10連ガチャ -> 決定 (Gacha) -> the summon,
#      the results, home.
#   Then the server's state (tools/server_state.py) before / after: the story and battle cleared,
#   the event coins dropped, the stamina spent, 2,500 coins debited, ten draws recorded; and a
#   contact sheet of all screenshots (tools/contact_sheet.py, OUT/summer-demonstration-grid.png).
# Prints PASS / FAIL per milestone and a final PASS (exit 0) or FAIL (exit 1, with the reason).
# Kills only the processes it started (also on Ctrl-C).
set -u
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../.." && pwd)
usage() { sed -n '2,/^set -u$/p' "$0" | sed '$d' | sed 's/^# \{0,1\}//'; }

emu=$repo/build/emulator/soa-emu srv=$repo/build/server/soa-server
watch=0 clock="2026-10-01 12:00:00" out=
while [ $# -gt 0 ]; do
    case "$1" in
        -h|--help) usage; exit 0;;
        --watch) watch=1; shift;;
        --clock) clock=${2:?--clock needs a value}; shift 2;;
        --emu) emu=${2:?}; shift 2;;
        --server) srv=${2:?}; shift 2;;
        -*) echo "summer_demo: unknown option $1 (--help)" >&2; exit 2;;
        *) [ -z "$out" ] || { echo "summer_demo: one OUT dir only" >&2; exit 2; }; out=$1; shift;;
    esac
done
case "${out:-}" in "") out=$repo/work/test/summer-demonstration;; /*) ;; *) out=$PWD/$out;; esac
soactl="$repo/control/soactl.py" flowctl="$repo/control/flowctl.py"
die() { echo "FAIL: $*"; exit 1; }
[ -x "$emu" ] || die "$emu not built (cmake -S . -B build && cmake --build build --target soa-emu)"
[ -x "$srv" ] || die "$srv not built (cmake --build build --target soa-server)"
command -v convert > /dev/null || die "ImageMagick's convert is needed (screen checks)"
py=$repo/.venv/bin/python
[ -x "$py" ] && "$py" -c 'import PIL' 2>/dev/null || py=python3
"$py" -c 'import PIL' 2>/dev/null || die "Pillow is needed for the contact sheet (.venv/bin/pip install -r requirements.txt)"

# Repo files: here, else in the main checkout work/ links to (a git worktree lacks untracked files).
repo_file() {
    if [ -s "$repo/$1" ] || [ -d "$repo/$1" ]; then echo "$repo/$1"; return; fi
    local main
    main=$(dirname "$(readlink -f "$repo/work")")
    [ -n "$main" ] && { [ -s "$main/$1" ] || [ -d "$main/$1" ]; } && echo "$main/$1"
}
master=$(repo_file data/basmaster-3.7.0.sqlite3)
download=$(repo_file work/download-3.7.0)
seed=$repo/data/saves/seed/Game.xml
[ -n "$master" ] || die "data/basmaster-3.7.0.sqlite3 not found"
[ -n "$download" ] || die "work/download-3.7.0 not found"
[ -s "$seed" ] || die "$seed not found"

mkdir -p "$out" || die "can't create $out"
rm -f "${out:?}"/*.png "${out:?}"/*.log "${out:?}"/*.log.pos "${out:?}"/state-*.txt "${out:?}"/milestones.txt
scratch=$(mktemp -d "${TMPDIR:-/tmp}/summer-demo.XXXXXX")
mkdir -p "$scratch/server" "$scratch/packets"
# The phone: EMU_DATA itself, else linked from the shared pre-downloaded phone (SOA_PHONE), else
# empty (the client downloads). The linked files are the shared phone's inodes: never chmod them;
# the scratch dir is removed with a plain rm -rf.
. "$repo/scripts/shared-phone.sh"
phone=${EMU_DATA:-$scratch/phone}
predownloaded=0
if [ -n "${EMU_DATA:-}" ]; then
    [ -d "$phone/data/files/download/UI" ] && predownloaded=1
else
    shared_phone_resolve "$repo"
    if [ -n "$SOA_PHONE" ]; then
        shared_phone_link "$SOA_PHONE" "$phone" || die "preparing the phone $phone from $SOA_PHONE"
        echo "phone: linked from $SOA_PHONE"
        predownloaded=1
    else
        echo "phone: empty (the client downloads its data)"
    fi
fi
mkdir -p "$phone"
elog=$scratch/emu.log slog=$scratch/server.log plog=$scratch/packets/packets.log fifo=$scratch/fifo
MAX_RSS_KB=$((6 * 1024 * 1024))
read -r game_port http_port < <(python3 -c '
import socket
s = [socket.socket() for _ in range(2)]
for x in s: x.bind(("127.0.0.1", 0))
print(*[x.getsockname()[1] for x in s])')

t0=$(date +%s)
spid= epid= finished=0
cleanup() {
    for p in $epid $spid; do
        kill -0 "$p" 2>/dev/null || continue
        kill "$p" 2>/dev/null
        for _ in 1 2 3 4 5 6 7 8 9 10; do kill -0 "$p" 2>/dev/null || break; sleep 1; done
        kill -9 "$p" 2>/dev/null
    done
    # the logs into OUT (the phone, the server state and the packet bodies stay in the scratch dir)
    cp -f "$elog" "$out/emu.log" 2>/dev/null; cp -f "$slog" "$out/server.log" 2>/dev/null
    cp -f "$plog" "$out/packets.log" 2>/dev/null
    if [ "${KEEP_SCRATCH:-0}" = 1 ]; then echo "scratch kept: $scratch (phone: $phone)"; else rm -rf "${scratch:?}"; fi
}
trap cleanup EXIT
trap 'echo "interrupted"; exit 130' INT TERM

echo "summer_demo: OUT $out; clock ${clock}; soa-emu $(readlink -f "$emu"); soa-server $(readlink -f "$srv")"
clock_srv=() clock_emu=()
if [ "$clock" != host ]; then clock_srv=(--clock "$clock"); clock_emu=(--device-clock "$clock"); fi
timeout -k 10 3600 "$srv" --listen 127.0.0.1:$game_port --http 127.0.0.1:$http_port --data "$scratch/server" \
    --master "$master" --seed "$seed" --download-dir "$download" --log-packets "$scratch/packets" \
    --seed-rng 1 --enable-events "${clock_srv[@]}" > "$slog" 2>&1 &
spid=$!
for _ in $(seq 1 240); do grep -q "^soa-server: game" "$slog" 2>/dev/null && break; kill -0 $spid 2>/dev/null || break; sleep 0.5; done
grep -q "^soa-server: game" "$slog" || die "soa-server didn't start (log: $out/server.log)"
grep -q "enable-events" "$slog" || die "soa-server didn't enable the summer events"
headless=(--headless); [ $watch = 1 ] && headless=()
timeout -k 10 3600 "$emu" --data "$phone" "${headless[@]}" --size 729x1296 --control "$fifo" "${clock_emu[@]}" \
    --server 127.0.0.1:$game_port --http 127.0.0.1:$http_port > "$elog" 2>&1 &
epid=$!

results=() failed=0
pass() { results+=("PASS  $1 ($(( $(date +%s) - t0 ))s)"); echo "PASS  $1 ($(( $(date +%s) - t0 ))s)"; }
miss() { results+=("FAIL  $1"); echo "FAIL  $1"; failed=1; }
state() { python3 "$repo/tools/server_state.py" "$scratch/server/server.sqlite3" > "$out/state-$1.txt" 2>&1; }
finish() {
    [ $finished = 1 ] && return
    finished=1
    python3 "$soactl" --timeout 10 "$fifo" quit > /dev/null 2>&1
    state end
    if grep -qE "Unhandled SIG|\*\*\* host signal" "$elog" 2>/dev/null; then miss "soa-emu crashed (see $out/emu.log)"; fi
    sheet
    echo "---"
    printf '%s\n' "${results[@]}" | tee "$out/milestones.txt"
    echo "screenshots, logs and state dumps in $out"
    if [ $failed = 0 ]; then echo "PASS" | tee -a "$out/milestones.txt"; exit 0; fi
    echo "FAIL" | tee -a "$out/milestones.txt"; exit 1
}
alive() {
    kill -0 $epid 2>/dev/null || return 1
    local rss
    rss=$(ps -o rss= --ppid $epid 2>/dev/null | sort -n | tail -1)
    [ -z "$rss" ] || [ "$rss" -le $MAX_RSS_KB ] || { echo "soa-emu above 6 GB RSS"; return 1; }
}
ctl() { python3 "$soactl" --timeout 120 "$fifo" "$@" > /dev/null 2>&1; }
# wait_for NAME SECONDS CMD...: polls CMD; PASS / FAIL for NAME.
wait_for() {
    local name=$1 limit=$2; shift 2
    local end=$(( $(date +%s) + limit ))
    while ! "$@"; do
        alive || { miss "$name (soa-emu exited)"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "$name (not within ${limit}s)"; return 1; }
        sleep 1
    done
    pass "$name"
}
# tap_until NAME SECONDS X:Y CMD...: taps X:Y every 5 s until CMD succeeds (a tap can be lost
# while a screen fades in).
tap_until() {
    local name=$1 limit=$2 xy=$3; shift 3
    local end=$(( $(date +%s) + limit )) next=0
    while ! "$@"; do
        alive || { miss "$name (soa-emu exited)"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "$name (not within ${limit}s)"; return 1; }
        if [ "$(date +%s)" -ge $next ]; then ctl "tap:$xy"; next=$(( $(date +%s) + 5 )); fi
        sleep 1
    done
    pass "$name"
}
poll() {
    local end=$(( $(date +%s) + $1 )); shift
    while ! "$@"; do
        alive || return 1
        [ "$(date +%s)" -lt $end ] || return 1
        sleep 1
    done
}
in_plog() { grep -q -- "$1" "$plog" 2>/dev/null; }
in_elog() { grep -q -- "$1" "$elog" 2>/dev/null; }
in_slog() { grep -q -- "$1" "$slog" 2>/dev/null; }
count_plog() { grep -c -- "$1" "$plog" 2>/dev/null || true; }
more_than() { [ "$(count_plog "$1")" -gt "$2" ]; }

# Screenshots: shot NAME -> OUT/NN-NAME.png, numbered in order, in the current section (for the
# contact sheet). A frame that is one flat colour (a black or white transition frame) is taken
# again, up to 5 times, 1.5 s apart.
n=0 section=launch
sec_launch=() sec_event=() sec_gacha=()
flat() { [ "$(convert "$1" -colorspace gray -format '%[fx:standard_deviation < 0.015 ? 1 : 0]' info: 2>/dev/null)" = 1 ]; }
shot() {
    n=$((n + 1))
    local f
    f=$(printf '%s/%02d-%s.png' "$out" $n "$1")
    for _ in 1 2 3 4 5; do
        ctl "shot:$f"
        [ -s "$f" ] && ! flat "$f" && break
        sleep 1.5
    done
    [ -s "$f" ] || { miss "screenshot $1 not taken"; return; }
    case $section in launch) sec_launch+=("$f");; event) sec_event+=("$f");; gacha) sec_gacha+=("$f");; esac
}
# keep_shot NAME FILE: a screenshot already taken (to FILE) kept as the next numbered one.
keep_shot() {
    n=$((n + 1))
    local f
    f=$(printf '%s/%02d-%s.png' "$out" $n "$1")
    cp -f "$2" "$f" || { miss "screenshot $1 not kept"; return; }
    case $section in launch) sec_launch+=("$f");; event) sec_event+=("$f");; gacha) sec_gacha+=("$f");; esac
}
sheet() {
    [ ${#sec_launch[@]} -gt 0 ] || return
    local args=("@1. Launch: boot, title, login, popups, home" "${sec_launch[@]}")
    [ ${#sec_event[@]} -gt 0 ] && args+=("@2. Summer event: 水着イベント2020 (event_sww2020_93), story mc99_565 + battle me99_1054" "${sec_event[@]}")
    [ ${#sec_gacha[@]} -gt 0 ] && args+=("@3. Summer gacha: 復刻水着2020① 10-draw" "${sec_gacha[@]}")
    if "$py" "$repo/tools/contact_sheet.py" --cols 6 --tile 360 \
        --title "Summer demo: 3.7.0 client in soa-emu + soa-server --enable-events, $(date +%F)" \
        "${args[@]}" -o "$out/summer-demonstration-grid.png" > "$scratch/sheet.txt" 2>&1; then
        pass "contact sheet ($(cat "$scratch/sheet.txt"))"
    else
        miss "contact sheet ($(tail -1 "$scratch/sheet.txt"))"
    fi
}
# The frame's mean brightness (0..1), and "the beach": the event board of 星の海と夢の渚 is sand
# below the sea (warm: red above blue in the lower middle), the other boards and the event list are
# space (blue above red).
mean() { convert "$1" -colorspace gray -format '%[fx:mean]' info: 2>/dev/null; }
beach() { [ "$(convert "$1" -crop 600x250+60+850 -format '%[fx:mean.r - mean.b > 0.08 ? 1 : 0]' info: 2>/dev/null)" = 1 ]; }
# master lookups (ids of labels, a gacha's name)
mid() { python3 - "$master" "$1" "$2" <<'EOF'
import sqlite3, sys
r = sqlite3.connect(sys.argv[1]).execute(f"select id from {sys.argv[2]} where id_label = ?", (sys.argv[3],)).fetchone()
print(r[0] if r else "")
EOF
}

# ---- 1. launch -------------------------------------------------------------------------------
section=launch
for _ in $(seq 1 60); do [ -p "$fifo" ] && break; alive || break; sleep 0.5; done
[ -p "$fifo" ] || { miss "soa-emu's control FIFO (see $out/emu.log)"; finish; }
sleep 4
shot boot
wait_for "boot -> NoLoginStart -> NoLoginStartRes" 150 in_plog "< NoLoginStartRes" || finish
# The title, or a communication-error dialog over it (seen once: 1002 after the first answer);
# its リトライ is where TAP TO START is, and the title is bright where the dialog is dark.
for i in 1 2 3 4; do
    sleep 5
    ctl "shot:$scratch/title.png"
    awk -v m="$(mean "$scratch/title.png")" 'BEGIN { exit !(m > 0.45) }' && break
    echo "note: an error dialog on the title; リトライ ($i)"
    k=$(count_plog "< NoLoginStartRes")
    ctl tap:364:713
    poll 60 more_than "< NoLoginStartRes" "$k"
done
shot title
tap_until "TAP TO START -> StartBridge -> ResultStart" 120 364:713 in_plog "< ResultStart" || finish
wait_for "Login -> LoginResult" 60 in_plog "< LoginResult" || finish
wait_for "Login's GetPlayerRes (seeded player)" 30 in_plog "< GetPlayerRes .*ends the login request" || finish
gets() { grep -c "I/http: GET" "$elog" 2>/dev/null || true; }
last_gets=-1 stable_since=0
downloads_done() {
    local k
    k=$(gets)
    if [ "$k" != "$last_gets" ]; then last_gets=$k stable_since=$(date +%s); return 1; fi
    in_elog "Android/B/" && [ $(( $(date +%s) - stable_since )) -ge 30 ]
}
if [ $predownloaded = 1 ]; then
    # The client may still fetch what changed (e.g. the master: soa-server's copy differs with the
    # clock); its dialogs' buttons (決定, ダウンロード, 完了) are tapped in turn until home.
    echo "note: the game data is on the phone (SOA_PHONE / EMU_DATA); no full download"
    end=$(( $(date +%s) + 300 )) i=0
    while ! poll 6 in_elog "ShowWebView(http"; do
        alive || { miss "home (soa-emu exited)"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "home (notice board) (not within 300s)"; finish; }
        case $((i % 3)) in 0) ctl tap:364:1043;; 1) ctl tap:515:800;; 2) ctl tap:364:790;; esac
        i=$((i + 1))
    done
    pass "home (notice board)"
else
    sleep 8
    shot download-prompt          # Episodeデータ管理 -> 決定
    tap_until "manifests (version_latest_Bulk.bin)" 120 364:1043 in_elog "manifest/etc2/hi/version_latest_Bulk.bin" || finish
    sleep 5
    shot download-dialog
    tap_until "game data download started (B/...)" 120 515:800 in_elog "I/http: GET .*/Android/B/" || finish
    wait_for "game data download finished" 1500 downloads_done || finish
    shot download-done
    tap_until "完了 -> home (notice board)" 120 364:790 in_elog "ShowWebView(http" || finish
fi
nn=$((n + 1)) nb=$((n + 2)) nh=$((n + 3))
f_notice=$(printf '%s/%02d-notice-board.png' "$out" $nn)
f_bonus=$(printf '%s/%02d-login-bonus.png' "$out" $nb)
f_home=$(printf '%s/%02d-home.png' "$out" $nh)
if python3 "$flowctl" login-popups "$fifo" "$elog" "$f_notice" "$f_bonus" "$f_home" > "$scratch/popups.txt" 2>&1; then
    pass "login popups closed ($(tail -n 1 "$scratch/popups.txt"))"
else
    miss "login popups ($(tail -n 1 "$scratch/popups.txt"))"; finish
fi
for f in "$f_notice" "$f_bonus" "$f_home"; do [ -s "$f" ] && sec_launch+=("$f"); done
[ -s "$f_bonus" ] || echo "note: no LOGIN BONUS popup this time"
n=$nh
state 1-home

# ---- 2. the summer event ---------------------------------------------------------------------
section=event
k=$(count_plog "> CheckEventRankingResult")
tap_until "イベント -> the event menu (CheckEventRankingResult)" 60 90:1085 more_than "> CheckEventRankingResult" "$k" || finish
sleep 6
shot event-list
# The event tab lists the calendar's events (soonest end first), then the enabled summer areas
# (2037/12/31). Two rows show the 星の海と夢の渚 banner; the first is 水着イベント2020
# (event_sww2020_93), whose fresh board opens on its first story mc99_565 (New, at 232:840). Which
# row that is depends on the calendar (fixed by --clock): each row is tried in turn, and is the one
# when it opens a beach board (sand below the sea: warm, where the other boards and the list are
# space) on which 232:840 opens a story popup (the dark band over the still visible sand); else
# 戻る and the next row. The list is never scrolled (a fling leaves it somewhere else).
story=$(mid master_event_mission mc99_565) battle=$(mid master_event_mission me99_1054)
story_popup() {
    awk -v m="$(convert "$1" -crop 729x200+0+560 -colorspace gray -format '%[fx:mean]' info: 2>/dev/null)" \
        -v w="$(convert "$1" -crop 600x120+60+880 -format '%[fx:mean.r - mean.b]' info: 2>/dev/null)" \
        'BEGIN { exit !(m < 0.32 && w > 0.05) }'
}
found=0
for y in 525 680 830 985; do
    ctl "tap:364:$y" wait:7000 "shot:$scratch/board.png"
    if beach "$scratch/board.png"; then
        ctl tap:232:840 wait:3000 "shot:$scratch/story.png"
        if story_popup "$scratch/story.png"; then found=1; break; fi
        echo "note: the row at y=$y opens a beach board without the story at 232:840; 戻る"
    else
        echo "note: the row at y=$y is not a beach board; 戻る"
    fi
    ctl tap:100:1120 wait:5000
done
[ $found = 1 ] && pass "the summer event board (水着イベント2020, 星の海と夢の渚; row at y=$y)" || { miss "no row opened the 水着イベント2020 board"; finish; }
keep_shot summer-event-board "$scratch/board.png"
keep_shot story-detail "$scratch/story.png"
# ストーリー開始 -> MissionTalk of mc99_565.
tap_until "story 星海に現れし渚 (mc99_565) -> MissionTalk" 60 515:715 in_plog "> MissionTalk .* $story " || finish
sleep 10
shot story-scene
ctl tap:115:1240 wait:2000          # スキップ
shot story-skip
k=$(count_plog "> CheckEventRankingResult")
tap_until "story skipped (はい) -> EndMissionTalk" 60 515:742 in_plog "> EndMissionTalk .* $story 1" || finish
wait_for "back on the board (CheckEventRankingResult)" 60 more_than "> CheckEventRankingResult" "$k" || finish
sleep 6
shot board-story-cleared
# The battle it unlocked, me99_1054 (New, right of the cleared story): single play -> no rental
# (選択しない) -> party 1 -> ミッション開始 -> 決定.
ctl tap:685:655 wait:4000
shot mission-detail
ctl tap:364:905 wait:5000
shot rental
ctl tap:620:1120 wait:5000
shot party
ctl tap:364:900 wait:3000
shot start-confirm
tap_until "ビーチスポーツ？【初級】 (me99_1054) -> MissionStart -> MissionStartRes" 60 515:712 in_plog "< MissionStartRes" || finish
in_plog "> MissionStart .* $battle " && pass "MissionStart names me99_1054 ($battle)" || miss "MissionStart is not for me99_1054 ($battle)"
sleep 6
shot battle-loading
for i in 1 2 3 4; do
    poll 8 in_plog "< MissionEndRes" && break
    shot "battle-$i"
done
wait_for "the battle won: MissionEnd (battle log) -> MissionEndRes" 600 in_plog "< MissionEndRes" || finish
in_slog "MissionEnd mission $battle: .*first clear" && pass "server: $(grep -m1 "MissionEnd mission $battle: " "$slog" | sed 's/^I\/server: //')" || miss "server: no first clear of me99_1054"
in_slog "MissionEnd mission $battle: unlocked" && pass "server: $(grep -m1 "MissionEnd mission $battle: unlocked" "$slog" | sed 's/^I\/server: //')" || miss "server: nothing unlocked"
sleep 2
shot battle-won              # the field after the last wave (the Mission Complete banner may have gone)
sleep 5
shot victory
# The Mission Result pages: OK at 510:1040 (the first tap opens the drop chests).
for p in rewards drops exp; do
    ctl tap:510:1040 wait:4000
    shot "result-$p"
done
k=$(count_plog "> CheckEventRankingResult")
tap_until "results -> back on the board (CheckEventRankingResult)" 90 510:1040 more_than "> CheckEventRankingResult" "$k" || finish
sleep 6
shot board-after-clear
state 2-after-battle
# Home (no request: a screenshot).
ctl tap:60:1245 wait:8000
shot home-after-event

# ---- 3. the summer gacha ---------------------------------------------------------------------
section=gacha
tap_until "ガチャ -> GetGachaInData" 60 425:1250 in_plog "< GetGachaInDataRes" || finish
sleep 8
shot gacha-menu
ctl tap:360:320 wait:5000          # the first banner of おすすめガチャ: 復刻水着2020①
shot summer-banner
ctl tap:540:945 wait:2500          # 10連ガチャ (2,500 coins)
shot draw-confirm
tap_until "10-draw: 決定 -> Gacha -> GachaRes" 60 515:800 in_plog "< GachaRes" || finish
gline=$(grep -m1 "^I/server: Gacha [0-9]* (.*draws for" "$slog")
gid=$(echo "$gline" | sed -n 's/^I\/server: Gacha \([0-9]*\) .*/\1/p')
gname=$(python3 - "$master" "${gid:-0}" <<'EOF'
import sqlite3, sys
db = sqlite3.connect(sys.argv[1])
r = db.execute("select (select text_value from master_text t where t.message_id = g.name_message_id limit 1) from master_gacha g where id = ?", (int(sys.argv[2]),)).fetchone()
print(r[0] if r and r[0] else "")
EOF
)
if echo "$gname" | grep -qE "水着|夏|サマー"; then pass "a summer gacha: $gname (${gline#I/server: })"; else miss "the drawn gacha is not a summer one (${gid:-?}: ${gname:-?})"; fi
sleep 4
shot summon-start
ctl tap:364:1190                   # 召喚開始
sleep 3
shot summon-1
sleep 3
shot summon-2
sleep 6
shot summon-reveal
ctl tap:364:650 wait:4000
shot summon-card
ctl tap:577:1199 wait:5000         # ALL SKIP
shot gacha-results
ctl tap:364:1002 wait:4000         # 次へ
shot gacha-results-chips
ctl tap:364:1002 wait:4000         # 閉じる
shot banner-after-draw
ctl tap:60:1245 wait:8000          # ホーム
shot home-end
state 3-after-gacha

# ---- server-side evidence --------------------------------------------------------------------
grep -q "^  mission $story: cleared" "$out/state-2-after-battle.txt" && pass "state: story mc99_565 ($story) cleared" || miss "state: mc99_565 not cleared"
grep -q "^  mission $battle: cleared" "$out/state-2-after-battle.txt" && pass "state: battle me99_1054 ($battle) cleared" || miss "state: me99_1054 not cleared"
grep -q "unlocked mc99_566 (by me99_1054)" "$out/state-2-after-battle.txt" && pass "state: mc99_566 unlocked by me99_1054" || miss "state: mc99_566 not unlocked"
coin() { sed -n 's/^  stock item_coin_291 x\([0-9]*\).*/\1/p' "$1" | head -1; }
e1=$(coin "$out/state-1-home.txt") e2=$(coin "$out/state-2-after-battle.txt")
[ "${e2:-0}" -gt "${e1:-0}" ] && pass "state: event drops: item_coin_291 ${e1:-0} -> $e2" || miss "state: no event drop (item_coin_291 ${e1:-0} -> ${e2:-0})"
st() { sed -n "s/.* $2 \([0-9]*\) .*/\1/p" "$1" | head -1; }
s1=$(st "$out/state-1-home.txt" stamina) s2=$(st "$out/state-2-after-battle.txt" stamina)
[ -n "$s1" ] && [ -n "$s2" ] && [ "$s2" -lt "$s1" ] && pass "state: stamina spent ($s1 -> $s2)" || miss "state: stamina not spent (${s1:-?} -> ${s2:-?})"
c2=$(sed -n 's/.* coins free \([0-9]*\) .*/\1/p' "$out/state-2-after-battle.txt")
c3=$(sed -n 's/.* coins free \([0-9]*\) .*/\1/p' "$out/state-3-after-gacha.txt")
[ -n "$c2" ] && [ -n "$c3" ] && [ $((c2 - c3)) = 2500 ] && pass "state: 2,500 coins debited ($c2 -> $c3)" || miss "state: coins ${c2:-?} -> ${c3:-?} (not -2,500)"
d=$(grep -c "^  gacha .*: " "$out/state-3-after-gacha.txt" || true)
[ "$d" = 10 ] && pass "state: 10 draws recorded ($(grep -c '^  gacha .*(duplicate)' "$out/state-3-after-gacha.txt") duplicates)" || miss "state: $d draws recorded, not 10"
r2=$(sed -n 's/^roster: \([0-9]*\) .*/\1/p' "$out/state-2-after-battle.txt") r3=$(sed -n 's/^roster: \([0-9]*\) .*/\1/p' "$out/state-3-after-gacha.txt")
echo "note: roster $r2 -> $r3 characters"
in_plog "< ProtocolError" && miss "a ProtocolError in the packet log"
finish
