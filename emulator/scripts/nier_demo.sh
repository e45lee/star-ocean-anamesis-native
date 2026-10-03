#!/bin/bash
# NieR demonstration: the unmodified 3.7.0 client in the emulator (soa-emu) against soa-server
# with the NieR:Automata rerun gacha opened (its lost banner art replaced by the stand-ins of
# standin-assets/), from boot to the gacha list, the NieR banner page and 10-draws until a NieR
# character (2B, 9S or A2) is drawn, with numbered screenshots and a contact sheet. Builds nothing.
#
# Usage: emulator/scripts/nier_demo.sh [options] [OUT]
#   OUT               where the screenshots, logs and state dumps go (default
#                     work/test/nier-demonstration); its old *.png, *.log, state-*.txt and
#                     roster-*.txt are deleted first, other files (README.md) are kept
#   --watch           show the emulator's window (default: headless)
#   --clock C         the date both the server and the phone start at, "YYYY-MM-DD HH:MM:SS"
#                     (default "2026-10-01 12:00:00": with --seed-rng 1 the draws, and so the
#                     number of pulls, are the same every run); "host" runs on the real date
#   --seed-rng N      soa-server's RNG seed (default 1: the first 10-draw has A2 and 9S; other
#                     seeds exercise the loop over pulls without a NieR character)
#   --max-pulls N     give up (FAIL) after N 10-draws without a NieR character (default 30:
#                     150,000 of the seeded 300,000 coins)
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
# What it does (emulator/README.md "NieR demonstration"):
#   soa-server: a fresh state seeded from data/saves/seed/Game.xml (player LOCAL00001, 300,000
#   coins), the CDN from work/download-3.7.0 plus the stand-ins of standin-assets/ (the list banner
#   20200227_chara_002 and the pick-up panels pickup_img_chara_0015..0017, made by
#   tools/make_standin_banners.py), --enable-events --event-keywords NieR (opens exactly one gacha:
#   gacha_pickup_role_0283 復刻NieR:Automataピックアップキャラガチャ; its banner gate sees the
#   stand-ins), --seed-rng 1, --log-packets; soa-emu pointed at it. Driven with control/soactl.py
#   taps and screenshots; each step waits for its request in soa-server's packet log:
#   1. launch: boot, title (NoLoginStart), TAP TO START (StartBridge, Login), the notice board and
#      LOGIN BONUS (control/flowctl.py login-popups), home (the client also fetches the stand-ins
#      the shared phone lacks: their Individual bundles I/5374616e/...);
#   2. the NieR gacha: ガチャ (GetGachaInData) -> the list with the stand-in banner -> the banner
#      page (the stand-in pick-up panels of 2B, 9S and A2: the page rotates them);
#   3. pulls: 10連ガチャ (5,000 coins) -> 決定 (Gacha) until a draw is role_cc0015/16/17 (2B / 9S /
#      A2): each pull's ten draws are read from the server's state (tools/server_state.py, in draw
#      order); on the pull that has one, the summon is tapped through to the first NieR card (its
#      3D reveal and its card) before ALL SKIP; the results of every pull; at most --max-pulls;
#   4. the character list (キャラクター -> ステータス強化, by rarity: the new ★5s), then home.
#   Then the server's state before / after: the roster diff (the NieR role), coins -5,000 per pull,
#   ten draws per pull of gacha_pickup_role_0283; and a contact sheet of all screenshots
#   (tools/contact_sheet.py, OUT/nier-demonstration-grid.png).
# Prints PASS / FAIL per milestone and a final PASS (exit 0) or FAIL (exit 1, with the reason).
# Kills only the processes it started (also on Ctrl-C).
set -u
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../.." && pwd)
usage() { sed -n '2,/^set -u$/p' "$0" | sed '$d' | sed 's/^# \{0,1\}//'; }

emu=$repo/build/emulator/soa-emu srv=$repo/build/server/soa-server
watch=0 clock="2026-10-01 12:00:00" out= max_pulls=30 seed_rng=1
while [ $# -gt 0 ]; do
    case "$1" in
        -h|--help) usage; exit 0;;
        --watch) watch=1; shift;;
        --clock) clock=${2:?--clock needs a value}; shift 2;;
        --max-pulls) max_pulls=${2:?--max-pulls needs a value}; shift 2;;
        --seed-rng) seed_rng=${2:?--seed-rng needs a value}; shift 2;;
        --emu) emu=${2:?}; shift 2;;
        --server) srv=${2:?}; shift 2;;
        -*) echo "nier_demo: unknown option $1 (--help)" >&2; exit 2;;
        *) [ -z "$out" ] || { echo "nier_demo: one OUT dir only" >&2; exit 2; }; out=$1; shift;;
    esac
done
case "${out:-}" in "") out=$repo/work/test/nier-demonstration;; /*) ;; *) out=$PWD/$out;; esac
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
standins=$repo/standin-assets
[ -n "$master" ] || die "data/basmaster-3.7.0.sqlite3 not found"
[ -n "$download" ] || die "work/download-3.7.0 not found"
[ -s "$seed" ] || die "$seed not found"
for f in 20200227_chara_002 pickup_img_chara_0015 pickup_img_chara_0016 pickup_img_chara_0017; do
    [ -s "$standins/Image/etc2/$f.aif" ] || die "stand-in $standins/Image/etc2/$f.aif missing (tools/make_standin_banners.py)"
done

mkdir -p "$out" || die "can't create $out"
rm -f "${out:?}"/*.png "${out:?}"/*.log "${out:?}"/*.log.pos "${out:?}"/state-*.txt "${out:?}"/roster-*.txt "${out:?}"/milestones.txt \
    "${out:?}"/pulls.txt
scratch=$(mktemp -d "${TMPDIR:-/tmp}/nier-demo.XXXXXX")
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

echo "nier_demo: OUT $out; clock ${clock}; seed-rng $seed_rng; max pulls $max_pulls; soa-emu $(readlink -f "$emu"); soa-server $(readlink -f "$srv")"
clock_srv=() clock_emu=()
if [ "$clock" != host ]; then clock_srv=(--clock "$clock"); clock_emu=(--device-clock "$clock"); fi
timeout -k 10 3600 "$srv" --listen 127.0.0.1:$game_port --http 127.0.0.1:$http_port --data "$scratch/server" \
    --master "$master" --seed "$seed" --download-dir "$download" --standin-assets "$standins" \
    --log-packets "$scratch/packets" --seed-rng "$seed_rng" --enable-events --event-keywords NieR "${clock_srv[@]}" > "$slog" 2>&1 &
spid=$!
for _ in $(seq 1 240); do grep -q "^soa-server: game" "$slog" 2>/dev/null && break; kill -0 $spid 2>/dev/null || break; sleep 0.5; done
grep -q "^soa-server: game" "$slog" || die "soa-server didn't start (log: $out/server.log)"
grep -q 'enable-events ("NieR"): .* 1 gachas' "$slog" || die "soa-server didn't open exactly one NieR gacha ($(grep -m1 'enable-events' "$slog"))"
headless=(--headless); [ $watch = 1 ] && headless=()
timeout -k 10 3600 "$emu" --data "$phone" "${headless[@]}" --size 729x1296 --control "$fifo" "${clock_emu[@]}" \
    --server 127.0.0.1:$game_port --http 127.0.0.1:$http_port > "$elog" 2>&1 &
epid=$!

results=() failed=0
pass() { results+=("PASS  $1 ($(( $(date +%s) - t0 ))s)"); echo "PASS  $1 ($(( $(date +%s) - t0 ))s)"; }
miss() { results+=("FAIL  $1"); echo "FAIL  $1"; failed=1; }
state() { python3 "$repo/tools/server_state.py" "$scratch/server/server.sqlite3" --db "$master" > "$out/state-$1.txt" 2>&1; }
# roster NAME: the server's roster (uid, role label, level, limit break) -> OUT/roster-NAME.txt
roster() { python3 - "$scratch/server/server.sqlite3" "$master" > "$out/roster-$1.txt" 2>&1 <<'EOF'
import sqlite3, sys
st = sqlite3.connect("file:%s?mode=ro" % sys.argv[1], uri=True)
m = sqlite3.connect("file:%s?mode=ro" % sys.argv[2], uri=True)
for uid, role, lv, lb in st.execute("select uid, role_id, level, limit_break from roster order by uid"):
    r = m.execute("select r.id_label, r.rarity, (select text_value from master_text where message_id = "
                  "substr(r.id_label, 6, 11) || '_message') from master_role r where r.id = ?", (role,)).fetchone()
    lab, rar, name = r if r else (str(role), 0, "")
    print("%#x %s ★%s %s level %d limit break %d" % (uid, lab, rar, name or "", lv, lb))
EOF
}
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
sec_launch=() sec_gacha=() sec_pulls=() sec_roster=()
flat() { [ "$(convert "$1" -colorspace gray -format '%[fx:standard_deviation < 0.015 ? 1 : 0]' info: 2>/dev/null)" = 1 ]; }
add_sec() {
    case $section in launch) sec_launch+=("$1");; gacha) sec_gacha+=("$1");; pulls) sec_pulls+=("$1");; roster) sec_roster+=("$1");; esac
}
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
    add_sec "$f"
}
sheet() {
    [ ${#sec_launch[@]} -gt 0 ] || return
    local args=("@1. Launch: boot, title, login, popups, home" "${sec_launch[@]}")
    [ ${#sec_gacha[@]} -gt 0 ] && args+=("@2. The NieR gacha (gacha_pickup_role_0283): the list and the banner page, stand-in art" "${sec_gacha[@]}")
    [ ${#sec_pulls[@]} -gt 0 ] && args+=("@3. 10-draws until 2B / 9S / A2" "${sec_pulls[@]}")
    [ ${#sec_roster[@]} -gt 0 ] && args+=("@4. The character list, home" "${sec_roster[@]}")
    if "$py" "$repo/tools/contact_sheet.py" --cols 6 --tile 360 \
        --title "NieR demo: 3.7.0 client in soa-emu + soa-server --enable-events --event-keywords NieR, $(date +%F)" \
        "${args[@]}" -o "$out/nier-demonstration-grid.png" > "$scratch/sheet.txt" 2>&1; then
        pass "contact sheet ($(cat "$scratch/sheet.txt"))"
    else
        miss "contact sheet ($(tail -1 "$scratch/sheet.txt"))"
    fi
}
# The frame's mean brightness (0..1).
mean() { convert "$1" -colorspace gray -format '%[fx:mean]' info: 2>/dev/null; }
# The gacha's master id.
gacha_label=gacha_pickup_role_0283
gacha_id=$(python3 - "$master" "$gacha_label" <<'EOF'
import sqlite3, sys
r = sqlite3.connect(sys.argv[1]).execute("select id from master_gacha where id_label = ?", (sys.argv[2],)).fetchone()
print(r[0] if r else "")
EOF
)
[ -n "$gacha_id" ] || die "no master_gacha $gacha_label"

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

roster 1-home
c0=$(sed -n 's/.* coins free \([0-9]*\) .*/\1/p' "$out/state-1-home.txt")
nier0=$(grep -cE " role_cc001[567]_" "$out/roster-1-home.txt" || true)
echo "note: at home: $(grep -c . "$out/roster-1-home.txt") characters ($nier0 NieR), ${c0:-?} free coins"

# keep_shot NAME FILE: a screenshot already taken (to FILE) kept as the next numbered one.
keep_shot() {
    n=$((n + 1))
    local f
    f=$(printf '%s/%02d-%s.png' "$out" $n "$1")
    cp -f "$2" "$f" || { miss "screenshot $1 not kept"; return; }
    add_sec "$f"
}
# rmse A B [CROP]: ImageMagick's normalized RMSE of two screenshots (or of the same crop of both).
rmse() {
    local a=$1 b=$2
    if [ -n "${3:-}" ]; then
        convert "$1" -crop "$3" +repage "$scratch/rmse-a.png" && convert "$2" -crop "$3" +repage "$scratch/rmse-b.png"
        a=$scratch/rmse-a.png b=$scratch/rmse-b.png
    fi
    compare -metric RMSE "$a" "$b" null: 2>&1 | sed -n 's/.*(\(.*\)).*/\1/p'
}
below() { awk -v v="${1:-1}" -v t="$2" 'BEGIN { exit !(v < t) }'; }
# The banner page's buttons (1回ガチャ / 10連ガチャ, the end date): the same on every visit.
BUTTONS=729x150+0+880
# The stand-in list banner and pick-up panels: the beige of the automata theme (warm grey: bright,
# red a bit above blue), where the real banners around them are blue / colourful.
beige() { [ "$(convert "$1" -crop "$2" -format '%[fx:mean > 0.55 && mean.r - mean.b > 0.03 && mean.r - mean.b < 0.2 ? 1 : 0]' info: 2>/dev/null)" = 1 ]; }

# ---- 2. the NieR gacha: the list and the banner page --------------------------------------------
section=gacha
tap_until "ガチャ -> GetGachaInData" 60 425:1250 in_plog "< GetGachaInDataRes" || finish
in_slog "GetGachaInData: .* gachas open" && echo "note: server: $(grep -m1 'GetGachaInData: .* gachas open' "$slog" | sed 's/^I\/server: //')"
sleep 8
shot gacha-list
# おすすめガチャ lists the enabled gacha first (its end date, 2037/12/31, is the latest): the
# stand-in banner 20200227_chara_002 is the first row.
beige "$out/$(printf '%02d' $n)-gacha-list.png" 180x80+435+270 && pass "the gacha list's first row is the NieR stand-in banner" \
    || miss "the gacha list's first row is not the NieR stand-in banner (see $(printf '%02d' $n)-gacha-list.png)"
ctl tap:360:310 wait:5000
shot nier-banner-page
page=$out/$(printf '%02d' $n)-nier-banner-page.png
beige "$page" 300x300+400+400 && pass "the NieR banner page: the stand-in pick-up panel" || miss "the banner page shows no stand-in panel"
cp -f "$page" "$scratch/banner-page.png"
# The page rotates its three panels (2B 1/3, 9S 2/3, A2 3/3) by itself: keep the next two that
# differ from those kept.
kept=("$page") k=0
for _ in $(seq 1 12); do
    [ ${#kept[@]} -ge 3 ] && break
    sleep 2
    ctl "shot:$scratch/panel.png"
    new=1
    for f in "${kept[@]}"; do below "$(rmse "$scratch/panel.png" "$f" 729x500+0+370)" 0.12 && new=0; done
    if [ $new = 1 ] && beige "$scratch/panel.png" 300x300+400+400; then
        k=$((k + 1))
        keep_shot "nier-banner-panel-$((k + 1))" "$scratch/panel.png"
        kept+=("$out/$(printf '%02d' $n)-nier-banner-panel-$((k + 1)).png")
    fi
done
echo "note: ${#kept[@]} pick-up panels seen on the banner page"
on_banner_page() {
    ctl "shot:$scratch/now.png"
    below "$(rmse "$scratch/now.png" "$scratch/banner-page.png" $BUTTONS)" 0.15
}
on_banner_page && pass "the banner page's buttons (1回ガチャ ×500, 10連ガチャ ×5000)" || miss "the banner page's buttons not found"

# ---- 3. 10-draws until a NieR character ---------------------------------------------------------
section=pulls
pull=0 got= gidx=0
: > "$out/pulls.txt"
while [ $pull -lt "$max_pulls" ]; do
    pull=$((pull + 1))
    k=$(count_plog "< GachaRes")
    ctl tap:540:945 wait:2500          # 10連ガチャ
    [ $pull = 1 ] && shot draw-confirm
    tap_until "pull $pull: 10連ガチャ -> 決定 -> Gacha -> GachaRes" 60 515:800 more_than "< GachaRes" "$k" || finish
    in_plog "> Gacha .* args: $gacha_id " || miss "pull $pull: the Gacha request is not for $gacha_label ($gacha_id)"
    state "pull-$pull"
    rows=$(grep "^  gacha " "$out/state-pull-$pull.txt" | tail -n 10)
    total=$(grep -c "^  gacha " "$out/state-pull-$pull.txt" || true)
    others=$(grep "^  gacha " "$out/state-pull-$pull.txt" | grep -vc "^  gacha $gacha_label: " || true)
    [ "$total" = $((pull * 10)) ] && [ "$others" = 0 ] || miss "pull $pull: $total draws recorded ($others not of $gacha_label), not $((pull * 10))"
    # the draws of this pull that are 2B / 9S / A2 (1..10; the reveal shows them in this order)
    js=$(echo "$rows" | grep -nE " role_cc001[567]_" | cut -d: -f1 | tr '\n' ' ')
    j=${js%% *}
    {
        echo "pull $pull (Gacha $gacha_id, 10 draws):"
        echo "$rows" | sed 's/^  gacha [^:]*: /  /'
    } >> "$out/pulls.txt"
    sleep 4
    if [ -n "$j" ]; then
        role_of() { echo "$rows" | sed -n "${1}p" | sed -n 's/.* \(role_cc001[567]_[a-z0-9_]*\) .*/\1/p'; }
        got=$(role_of "$j")
        for i in $js; do pass "pull $pull: a NieR character: draw $i of 10 is $(role_of "$i")"; done
        shot "pull-$pull-summon-start"
        ctl tap:364:1190               # 召喚開始
        sleep 14
        shot "pull-$pull-summon-reveal"  # the first card's 3D figure
        # The reveal goes figure 1, card 1, figure 2, card 2, ... one tap each: card i's figure is
        # on screen after 2(i-1) taps. Each NieR draw: its figure and its card.
        pos=1                          # the figure of draw $pos is on screen
        for i in $js; do
            for _ in $(seq 1 $((2 * (i - pos)))); do ctl tap:364:650 wait:4000; done
            shot "pull-$pull-draw-$i-reveal"
            ctl tap:364:650 wait:4000
            shot "pull-$pull-draw-$i-card"
            pos=$((i + 1))
            ctl tap:364:650 wait:4000  # on to the next figure (after card 10: the results)
        done
        if [ "$pos" -le 10 ]; then ctl tap:577:1199; fi   # ALL SKIP the rest
    else
        echo "note: pull $pull: no NieR character ($(echo "$rows" | awk '{print $3}' | sort | uniq -c | tr -s ' ' | tr '\n' ' '))"
        ctl tap:364:1190               # 召喚開始
        sleep 4
        ctl tap:577:1199               # ALL SKIP
    fi
    sleep 6
    shot "pull-$pull-results"
    # 閉じる (and a キャラチップ page for maxed duplicates) until the banner page is back
    end=$(( $(date +%s) + 60 ))
    until on_banner_page; do
        alive || { miss "pull $pull: back on the banner page (soa-emu exited)"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "pull $pull: back on the banner page (not within 60s)"; finish; }
        ctl tap:364:1002 wait:3500
    done
    [ -n "$got" ] && break
done
if [ -n "$got" ]; then
    pass "NieR character obtained after $pull pull(s) ($((pull * 10)) draws): $got"
else
    miss "no NieR character in $pull pulls (--max-pulls $max_pulls)"
fi
shot banner-after-pulls
roster 2-after-pulls

# ---- 4. the character list, home ----------------------------------------------------------------
section=roster
ctl tap:180:1250 wait:6000         # キャラクター
ctl tap:364:542 wait:5000          # ステータス強化: the character list (by rarity)
ctl "shot:$scratch/list.png"
# the seeded player has no enhancement materials: a 必要な素材がありません popup over the list
if below "$(convert "$scratch/list.png" -crop 729x150+0+560 -colorspace gray -format '%[fx:mean]' info: 2>/dev/null)" 0.25; then
    ctl tap:364:712 wait:2500      # 閉じる
fi
shot character-list
ctl tap:100:1120 wait:3000         # 戻る
ctl tap:60:1245 wait:8000          # ホーム
shot home-end
state end-pre
roster end

# ---- server-side evidence -----------------------------------------------------------------------
in_slog "Gacha $gacha_id ($gacha_label): 10 draws for 5000 free" && pass "server: $(grep -m1 "Gacha $gacha_id ($gacha_label)" "$slog" | sed 's/^I\/server: //')" \
    || miss "server: no 10-draw of $gacha_label"
c1=$(sed -n 's/.* coins free \([0-9]*\) .*/\1/p' "$out/state-end-pre.txt")
[ -n "$c0" ] && [ -n "$c1" ] && [ $((c0 - c1)) = $((pull * 5000)) ] && pass "state: $((pull * 5000)) coins debited for $pull pull(s) ($c0 -> $c1)" \
    || miss "state: coins ${c0:-?} -> ${c1:-?} (not -$((pull * 5000)))"
# new characters: uids not in the roster at home (the others drawn were limit breaks of owned ones)
newroles=$(awk 'NR == FNR { had[$1] = 1; next } !($1 in had)' "$out/roster-1-home.txt" "$out/roster-end.txt")
echo "$newroles" | sed 's/^/  new: /'
echo "$newroles" | sed 's/^/new: /' > "$out/roster-diff.txt"
awk 'NR == FNR { had[$1] = $0; next } ($1 in had) && had[$1] != $0 { print "changed: " had[$1] " -> " $0 }' \
    "$out/roster-1-home.txt" "$out/roster-end.txt" >> "$out/roster-diff.txt"
nier1=$(grep -cE " role_cc001[567]_" "$out/roster-end.txt" || true)
if [ -n "$got" ] && echo "$newroles" | grep -q " $got "; then
    pass "state: the roster has the new NieR role: $(echo "$newroles" | grep " $got " | head -n 1) (NieR roles $nier0 -> $nier1)"
else
    miss "state: no new NieR role in the roster (NieR roles $nier0 -> ${nier1:-?})"
fi
echo "note: roster $(grep -c . "$out/roster-1-home.txt") -> $(grep -c . "$out/roster-end.txt") characters"
in_plog "< ProtocolError" && miss "a ProtocolError in the packet log"
finish
