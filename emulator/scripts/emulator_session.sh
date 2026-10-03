#!/bin/bash
# End-to-end session of the 3.7.0 emulator against soa-server (emulator/README.md "Networking",
# "Checks"). Builds nothing.
#
# Usage: emulator/scripts/emulator_session.sh [--new-player] [soa-emu] [soa-server] [out dir]
#   defaults: build/emulator/soa-emu; build/server/soa-server (the repository build: cmake -S . -B build);
#   a fresh mktemp dir (kept: logs, screenshots, the packet log, the server's state dumps; the
#   emulated phone's 3 GB of downloaded data is deleted at the end unless KEEP_DATA=1)
# Env:
#   EMU_DATA=DIR   use DIR as the emulated phone (e.g. a KEEP_DATA=1 run's OUT/emu, whose game data
#                  is downloaded already, so the download steps are skipped); never deleted
#   SOA_PHONE      without EMU_DATA: unset -> OUT/emu is linked from the shared pre-downloaded
#                  phone work/phone-3.7.0 (scripts/shared-phone.sh; scripts/make-phone-370.sh builds
#                  it; under a second, no download steps) when it is built, else empty (the client
#                  downloads); none (or empty) -> an empty phone: the full download; DIR -> OUT/emu
#                  from DIR (linked if it is stamped, else copied)
#   SESSION_PLAY=0 stop at home (the seeded run's step 9; no popups, battle or gacha)
#   NEWPLAYER_NAME the new player's name (default Claire)
#   NO_RETRY=1     no リトライ fallback for the title's first request: FAIL if NoLoginStart isn't
#                  answered by itself (emulator/README.md "The lost first request", fixed in the
#                  runtime)
#   FRESH_KVS=1    delete the phone's local KVS (data/shared_prefs/Aska.xml: its version, crc and
#                  device UUID) first, so that the title creates and saves a new UUID as on a
#                  fresh phone (the path of "The lost first request") while EMU_DATA's game data
#                  is kept
#   SERVER_ARGS    extra soa-server arguments, e.g. --keep-open-after-error (soa-server keeps the
#                  connection open after a ProtocolError; emulator/README.md "Error replies and
#                  the tagged-address crash")
#
# Starts soa-server (its own scratch state, free ports, --log-packets, the CDN from
# work/download-3.7.0, --seed-rng 1) and soa-emu headless pointed at it, drives the client with
# control/soactl.py (taps and screenshots only: soa-emu has no natives, so no phase: / call:
# commands; the tap coordinates are the port's restore / campaign / newplayer sessions', the same
# 3.7.0 UI at the same 729x1296 window) and checks each milestone in soa-server's packet log, the
# emulator's log, the screenshots and the server's state DB (tools/server_state.py).
#
# The seeded run (the LOCAL00001 player; soa-server --campaign-seed mf01_001, so that the
# campaign's 1-05 (mf01_001), the battle of port/scripts/restore_session.sh, is open on the mission
# map, as port/scripts/campaign_session.sh plays it):
#    1. NoLoginStart          the title's pre-login request, answered (NoLoginStartRes)
#    2. StartBridge           after TAP TO START
#    3. bridge POST           the client's HTTP POST to the bridge URL (soa-server: /bridge)
#    4. UpdateSession         the session the bridge issued
#    5. Login                 answered with LoginResult (+ the GetPlayerRes that ends the request)
#    6. manifests             the downloader's manifest/etc2/hi/version_latest_* through HTTP
#    7. game data download    the bundles (B/...), until the downloads stop
#    8. master bundle         the served master's bundle (B/1115774b/b9a9e011.bin)
#    9. home                  the home screen's notice board (ShowWebView) after 完了
#   10. login popups          the notice board and the LOGIN BONUS closed (flowctl.py login-popups)
#   11. mission select        ミッション -> GetMissionList (the client is logged in: its later
#                             requests reconnect with the session key)
#   12. MissionStart          planet Mere -> 1-05 -> single play -> no rental -> party 1 -> 決定
#   13. MissionEnd            the battle (the party's AI) ends; the battle log the server decoded
#                             (mission_time, defeated enemies, evaluations) and the clear
#   14. results -> map        the Mission Result pages (OK) until the mission map (GetMissionList)
#   15. gacha screen          footer ガチャ -> GetGachaInData
#   16. 10-draw               the first recommended banner's 10連ガチャ -> 決定 -> SaleGacha;
#                             coins debited and the draw recorded in the server's state
#   17. home                  the presentation and the result list, then ホーム
# The --new-player run (soa-server --new-player: a fresh state with no player):
#    1. NoLoginStart; TAP TO START -> bridge -> Login -> ProtocolError 19001 (no player)
#    2. terms (同意する) -> name entry (the keyboard) -> 決定 -> CreatePlayer(name) -> Login
#    3. the game data download (as above) -> 完了
#    4. the tutorial: the opening scenes (MissionTalk / EndMissionTalk, UpdateTutorial 1-3), the
#       battle tutorial ms00_001 (MissionStart / MissionEnd), the mission-menu step (UpdateTutorial
#       4-6), home (UpdateTutorial 7) and the home tutorial (UpdateTutorial 9)
#    5. the milestones of tests/tutorial_milestones.txt (tools/compare_tutorial.py check emu), the
#       same list port/scripts/tutorial_session.sh checks; every hit's damage is traced
#       (SOA_TRACE on CCharacterObject::OnDamage) and a screenshot is kept per tutorial round
#       (tutorial-NNN.png) for tools/compare_tutorial.py compare
# Prints PASS / FAIL per milestone and a final PASS / FAIL (exit 0 / 1). Kills only the processes
# it started.
set -u
mode=seeded
if [ "${1:-}" = --new-player ]; then mode=newplayer; shift; fi
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../.." && pwd)
emu=${1:-$repo/build/emulator/soa-emu}
srv=${2:-$repo/build/server/soa-server}
out=${3:-$(mktemp -d "${TMPDIR:-/tmp}/emulator-session.XXXXXX")}
soactl="$repo/control/soactl.py"
flowctl="$repo/control/flowctl.py"
[ -x "$emu" ] || { echo "FAIL: $emu not built (cmake -S . -B build && cmake --build build --target soa-emu)"; exit 1; }
[ -x "$srv" ] || { echo "FAIL: soa-server not built (cmake -S . -B build && cmake --build build --target soa-server)"; exit 1; }
# Which binaries run, and a warning when soa-server is older than this checkout's server sources:
# a stale build (e.g. the main checkout's, built before a server change was merged) answers with
# the old rules (emulator/README.md "Tutorial parity": the 2026-10-01 party-stats failure).
echo "binaries: soa-emu $(readlink -f "$emu"), soa-server $(readlink -f "$srv")"
if [ -n "$(find "$repo/server" -name '*.cpp' -newer "$srv" -print -quit 2>/dev/null; find "$repo/server" -name '*.h' -newer "$srv" -print -quit 2>/dev/null)" ]; then
    echo "WARNING: $srv is older than sources under $repo/server: rebuild it (cmake --build build --target soa-server)"
fi

# Repo files: here, else in the main checkout work/ links to (a git worktree lacks untracked files).
# Empty files don't count (e.g. one `sqlite3 data/basmaster-3.7.0.sqlite3` created in a worktree).
repo_file() {
    if [ -s "$repo/$1" ]; then echo "$repo/$1"; return; fi
    local main
    main=$(dirname "$(readlink -f "$repo/work")")
    [ -n "$main" ] && [ -s "$main/$1" ] && echo "$main/$1"
}
master=$(repo_file data/basmaster-3.7.0.sqlite3)
download=$(repo_file work/download-3.7.0)
[ -n "$master" ] || { echo "FAIL: data/basmaster-3.7.0.sqlite3 not found"; exit 1; }
[ -n "$download" ] || { echo "FAIL: work/download-3.7.0 not found"; exit 1; }

mkdir -p "$out/server" "$out/packets"
. "$repo/scripts/shared-phone.sh"
phone=${EMU_DATA:-$out/emu}
predownloaded=0
if [ -n "${EMU_DATA:-}" ]; then
    predownloaded=1
else
    shared_phone_resolve "$repo"
    if [ -n "$SOA_PHONE" ]; then
        t_link=$(date +%s%N)
        shared_phone_link "$SOA_PHONE" "$phone" || { echo "FAIL: preparing the phone $phone from $SOA_PHONE"; exit 1; }
        echo "phone: $phone from $SOA_PHONE ($(( ($(date +%s%N) - t_link) / 1000000 )) ms)"
        predownloaded=1
    fi
fi
mkdir -p "$phone"
if [ "${FRESH_KVS:-0}" = 1 ]; then rm -f "$phone/data/shared_prefs/Aska.xml"; fi
elog=$out/emu.log slog=$out/server.log plog=$out/packets/packets.log fifo=$out/fifo
W=729 H=1296            # the window; tap coordinates are window pixels
MAX_RSS_KB=$((6 * 1024 * 1024))
read -r game_port http_port < <(python3 -c '
import socket
s = [socket.socket() for _ in range(2)]
for x in s: x.bind(("127.0.0.1", 0))
print(*[x.getsockname()[1] for x in s])')

t0=$(date +%s%N)
elapsed() { awk -v a="$t0" -v b="$(date +%s%N)" 'BEGIN { printf "%.0f", (b - a) / 1e9 }'; }
spid= epid=
cleanup() {
    for p in $epid $spid; do
        kill -0 "$p" 2>/dev/null || continue
        kill "$p" 2>/dev/null
        for _ in 1 2 3 4 5 6 7 8 9 10; do kill -0 "$p" 2>/dev/null || break; sleep 1; done
        kill -9 "$p" 2>/dev/null
    done
    if [ -z "${EMU_DATA:-}" ] && [ "${KEEP_DATA:-0}" != 1 ] && [ -d "$out/emu/data" ]; then rm -rf "${out:?}/emu/data"; fi
}
trap cleanup EXIT

# The game server. Its default bridge and CDN URLs are on the client's own host name, without a
# port (the client's URI parser can't resolve "host:port"; emulator/README.md "Networking");
# soa-emu maps that name to --server / --http. --seed-rng 1 as restore_session.sh's
# SOA_SERVER_SEED_RNG=1 (the parity run, emulator/README.md "Parity").
srv_args=(--seed-rng 1)
if [ $mode = newplayer ]; then srv_args+=(--new-player); else srv_args+=(--campaign-seed mf01_001); fi
# shellcheck disable=SC2206
[ -n "${SERVER_ARGS:-}" ] && srv_args+=($SERVER_ARGS)
timeout -k 10 3000 "$srv" --listen 127.0.0.1:$game_port --http 127.0.0.1:$http_port --data "$out/server" --master "$master" \
    --download-dir "$download" --log-packets "$out/packets" "${srv_args[@]}" > "$slog" 2>&1 &
spid=$!
for _ in $(seq 1 120); do grep -q "^soa-server: game" "$slog" 2>/dev/null && break; kill -0 $spid 2>/dev/null || break; sleep 0.5; done
grep -q "^soa-server: game" "$slog" || { echo "FAIL: soa-server didn't start (log: $slog)"; exit 1; }

# --new-player: every hit's damage in the log (SOA_TRACE on CCharacterObject::OnDamage, its s0),
# for the tutorial parity report (tools/compare_tutorial.py; port/scripts/tutorial_session.sh traces
# the same function).
emu_env=()
if [ $mode = newplayer ]; then
    emu_env=(SOA_TRACE=_ZN16CCharacterObject8OnDamageERKN24IAttackCollisionCallback23CallbackArgument_DamageEfb)
fi
env "${emu_env[@]}" timeout -k 10 3000 "$emu" --data "$phone" --headless --size ${W}x$H --control "$fifo" \
    --server 127.0.0.1:$game_port --http 127.0.0.1:$http_port > "$elog" 2>&1 &
epid=$!

results=() failed=0
pass() { results+=("PASS  $1 ($(elapsed)s)"); echo "PASS  $1 ($(elapsed)s)"; }
miss() { results+=("FAIL  $1"); echo "FAIL  $1"; failed=1; }
state() { python3 "$repo/tools/server_state.py" "$out/server/server.sqlite3" > "$out/state-$1.txt" 2>&1; }
finish() {
    python3 "$soactl" --timeout 10 "$fifo" quit > /dev/null 2>&1
    state end
    if grep -qE "Unhandled SIG|\*\*\* host signal" "$elog" 2>/dev/null; then miss "soa-emu crashed (see $elog)"; fi
    echo "---"
    printf '%s\n' "${results[@]}"
    echo "logs: $elog $slog $plog; screenshots and state dumps in $out"
    if [ $failed = 0 ]; then echo "PASS"; exit 0; fi
    echo "FAIL"; exit 1
}
alive() {
    kill -0 $epid 2>/dev/null || return 1
    local rss
    rss=$(ps -o rss= --ppid $epid 2>/dev/null | sort -n | tail -1)
    [ -z "$rss" ] || [ "$rss" -le $MAX_RSS_KB ] || { echo "soa-emu above 6 GB RSS"; return 1; }
}
ctl() { python3 "$soactl" --timeout 60 "$fifo" "$@" > /dev/null 2>&1; }
shot() { ctl "shot:$out/$1.png"; }
# wait_for NAME SECONDS CMD...: polls CMD; records PASS / FAIL for NAME.
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
# tap_until NAME SECONDS X:Y CMD...: taps X:Y every 4 s until CMD succeeds (a tap can be lost
# while a screen fades in).
tap_until() {
    local name=$1 limit=$2 xy=$3; shift 3
    local end=$(( $(date +%s) + limit )) next=0
    while ! "$@"; do
        alive || { miss "$name (soa-emu exited)"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "$name (not within ${limit}s)"; return 1; }
        if [ "$(date +%s)" -ge $next ]; then ctl "tap:$xy"; next=$(( $(date +%s) + 4 )); fi
        sleep 1
    done
    pass "$name"
}
in_plog() { grep -q -- "$1" "$plog" 2>/dev/null; }
in_elog() { grep -q -- "$1" "$elog" 2>/dev/null; }
count_plog() { grep -c -- "$1" "$plog" 2>/dev/null || true; }
# more_than PATTERN N: the packet log has more than N lines matching PATTERN.
more_than() { [ "$(count_plog "$1")" -gt "$2" ]; }
gets() { grep -c "I/http: GET" "$elog" 2>/dev/null || true; }
# The downloads have stopped: no new GET for 30 s (and at least one bundle fetched).
last_gets=-1 stable_since=0
downloads_done() {
    local n
    n=$(gets)
    if [ "$n" != "$last_gets" ]; then last_gets=$n stable_since=$(date +%s); return 1; fi
    in_elog "Android/B/" && [ $(( $(date +%s) - stable_since )) -ge 30 ]
}
# poll SECONDS CMD...: polls CMD without recording a milestone; 0 when it succeeded.
poll() {
    local end=$(( $(date +%s) + $1 )); shift
    while ! "$@"; do
        alive || return 1
        [ "$(date +%s)" -lt $end ] || return 1
        sleep 1
    done
}
# The game data download after a Login with the CDN keys: the dialogs, the bundles, 完了.
# $1: the tap for the first dialog's button before the download dialog ("" when there is none).
download() {
    if [ -n "$1" ]; then
        tap_until "manifests (version_latest_Bulk.bin)" 120 "$1" in_elog "manifest/etc2/hi/version_latest_Bulk.bin" || finish
        sleep 5
    else
        wait_for "manifests (version_latest_Bulk.bin)" 60 in_elog "manifest/etc2/hi/version_latest_Bulk.bin" || finish
        sleep 8
    fi
    shot download-dialog
    # The download dialog -> ダウンロード; the bundles, until they stop.
    tap_until "game data download started (B/...)" 120 515:800 in_elog "I/http: GET .*/Android/B/" || finish
    wait_for "game data download finished" 1200 downloads_done || finish
    shot download-done
    if in_elog "/Android/B/1115774b/b9a9e011.bin"; then pass "master bundle (B/1115774b/b9a9e011.bin)"; else miss "master bundle (B/1115774b/b9a9e011.bin) not requested"; fi
}
# The data is on the phone already (EMU_DATA, or the shared phone): no download dialogs come.
data_on_phone() { [ $predownloaded = 1 ] && [ -d "$phone/data/files/download/UI" ]; }

# 1. The title's NoLoginStart, answered. Before the runtime's JNI fix, 1 run in 8-16 opened the
#    first connection but sent nothing (emulator/README.md "The lost first request") and showed
#    the 1003 dialog, whose リトライ (the middle of the screen) sends it. The fallback is kept for
#    a real network error; NO_RETRY=1 makes a lost first request a FAIL.
if poll 150 in_plog "< NoLoginStartRes"; then
    pass "NoLoginStart -> NoLoginStartRes"
elif [ "${NO_RETRY:-0}" = 1 ]; then
    miss "NoLoginStart -> NoLoginStartRes (NO_RETRY=1: not sent by itself)"
    finish
else
    echo "note: no NoLoginStart yet; tapping リトライ"
    tap_until "NoLoginStart -> NoLoginStartRes (after リトライ)" 120 364:713 in_plog "< NoLoginStartRes" || finish
fi
sleep 5
shot title
# 2.-5. TAP TO START (the middle of the title; the same spot is リトライ on an error dialog).
tap_until "StartBridge -> ResultStart" 120 364:713 in_plog "< ResultStart" || finish
wait_for "bridge POST (/bridge)" 60 in_plog "bridge: UUID=" || finish
wait_for "UpdateSession -> ResultUpdateSession" 60 in_plog "< ResultUpdateSession" || finish

if [ $mode = newplayer ]; then
    name=${NEWPLAYER_NAME:-Claire}
    wait_for "Login -> ProtocolError 19001 (no player)" 60 in_plog "< ProtocolError .*status=19001" || finish
    sleep 3
    shot terms
    # The terms dialog's 同意する (364:689), then the name dialog's field (364:647) until the client
    # opens its keyboard (the dialog fades in; a tap during the fade is dropped). soactl returns
    # once the commands are queued, so each round waits for them (and the keyboard) itself.
    end=$(( $(date +%s) + 90 ))
    while ! in_elog "StartKeyboardActivity("; do
        alive || { miss "name entry (soa-emu exited)"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "terms -> name entry (no keyboard within 90s)"; finish; }
        ctl tap:364:689 wait:2500 tap:364:647
        poll 6 in_elog "StartKeyboardActivity(" && break
    done
    pass "terms (同意する) -> name entry (keyboard)"
    # While the keyboard is open the game renders no frames: the text first, then a screenshot.
    ctl wait:500 "text:$name" wait:1500 "shot:$out/name-typed.png"
    tap_until "決定 -> CreatePlayer -> CreatePlayerRes" 60 364:790 in_plog "< CreatePlayerRes" || finish
    in_plog "> CreatePlayer .*\"$name\"" && pass "CreatePlayer carries the name \"$name\"" || miss "CreatePlayer without the name \"$name\""
    wait_for "Login -> LoginResult (the new player, the CDN keys)" 60 in_plog "< LoginResult .*AssetPath" || finish
    if data_on_phone; then
        # A small download may still come (stand-ins added since the phone was built): its
        # dialogs' buttons (決定, ダウンロード, 完了) in turn until the opening scene, as for home below.
        end=$(( $(date +%s) + 300 )) i=0
        while ! poll 6 in_plog "> MissionTalk"; do
            alive || { miss "the opening scene (soa-emu exited)"; finish; }
            [ "$(date +%s)" -lt $end ] || { miss "the opening scene (MissionTalk) (not within 300s)"; finish; }
            case $((i % 3)) in 0) ctl tap:364:1043;; 1) ctl tap:515:800;; 2) ctl tap:364:790;; esac
            i=$((i + 1))
        done
    else
        download ""
        tap_until "完了 -> the opening scene (MissionTalk)" 120 364:790 in_plog "> MissionTalk" || finish
    fi
    wait_for "the opening scene (MissionTalk)" 120 in_plog "> MissionTalk" || finish
    # The tutorial (port/scripts/newplayer_session.sh's taps): auto mode and fast-forward, then
    # rounds of taps: the first choice of a SelectMenu (364:506 / 364:562), the battle tutorial's
    # dialog buttons (次へ 527:1090 / 527:785, 閉じる 527:697), RUSH (175:890), the enemy area
    # (440:430) and the three skill buttons, until the mission-menu step (UpdateTutorial 4).
    ctl wait:15000 "shot:$out/opening.png" tap:612:1240 wait:1000 tap:115:45 wait:1000
    i=0
    while [ $i -lt "${NEWPLAYER_STEPS:-150}" ] && ! in_plog "> UpdateTutorial .*args: 4$"; do
        alive || { miss "tutorial (soa-emu exited)"; finish; }
        ctl wait:6000 "shot:$out/tutorial-$(printf %03d $i).png"
        ctl tap:364:506 wait:400 tap:364:562 wait:400 tap:527:1090 wait:400 tap:527:785 wait:400 tap:527:697 wait:400 \
            tap:175:890 wait:300 tap:440:430 wait:300 tap:650:1005 wait:300 tap:505:1075 wait:300 tap:450:1215
        i=$((i + 1))
    done
    for k in 1 2 3; do in_plog "> UpdateTutorial .*args: $k$" && pass "UpdateTutorial($k)" || miss "UpdateTutorial($k) not sent"; done
    in_plog "< MissionStartRes" && pass "battle tutorial: MissionStart -> MissionStartRes" || miss "battle tutorial: no MissionStart"
    in_plog "< MissionEndRes" && pass "battle tutorial: MissionEnd (battle log) -> MissionEndRes" || miss "battle tutorial: no MissionEnd"
    wait_for "UpdateTutorial(4) (the mission menu)" 30 in_plog "> UpdateTutorial .*args: 4$" || finish
    # The mission-menu step: planet Mere's map, 1-01 (ここをタップ) -> ストーリー開始 -> the story,
    # skipped (スキップ -> はい) -> UpdateTutorial(6) -> "summoned companions" 次へ -> ホーム.
    ctl wait:10000 "shot:$out/tutorial-map.png" tap:360:640 wait:3000 tap:515:714
    ctl wait:20000 tap:115:1240 wait:2000 tap:515:742
    wait_for "UpdateTutorial(6) (the story of 1-01)" 180 in_plog "> UpdateTutorial .*args: 6$" || finish
    ctl wait:8000 "shot:$out/tutorial-companions.png" tap:527:1090 wait:3000 tap:60:1240
    wait_for "UpdateTutorial(7) (home)" 120 in_plog "> UpdateTutorial .*args: 7$" || finish
    # The home tutorial: the present box (次へ), then the gacha button (閉じる) -> UpdateTutorial(9).
    ctl wait:8000 "shot:$out/home-tutorial.png" tap:525:1085 wait:3000 "shot:$out/home-tutorial-gacha.png" tap:525:1090
    wait_for "UpdateTutorial(9) (the tutorial cleared)" 90 in_plog "> UpdateTutorial .*args: 9$" || finish
    ctl wait:8000
    shot home
    state newplayer
    grep -q "^player LOCAL[0-9]* ($name," "$out/state-newplayer.txt" && pass "server state: the new player \"$name\"" || miss "server state: no player \"$name\""
    in_plog "< ProtocolError .*status=1[0-9][0-9][0-9] " && miss "a communication-error ProtocolError (packet log)"
    # The shared milestone list (tests/tutorial_milestones.txt; the port's tutorial_session.sh checks
    # the same): the requests in order and the battle party's stats (the MissionEnd battle log).
    if python3 "$repo/tools/compare_tutorial.py" check emu "$out" --name "$name" > "$out/milestones.txt" 2>&1; then
        pass "tutorial milestones ($(grep -c '^PASS  ' "$out/milestones.txt") of tests/tutorial_milestones.txt)"
    else
        miss "tutorial milestones: $(grep '^FAIL  ' "$out/milestones.txt" | head -3 | tr '\n' ';')"
    fi
    finish
fi

# 5. Login.
wait_for "Login -> LoginResult (decoded)" 60 in_plog "< LoginResult .* data{" || finish
wait_for "Login's GetPlayerRes" 30 in_plog "< GetPlayerRes .*ends the login request" || finish
sleep 8
shot after-login
# 6.-8. "Episode data management" -> 決定; the downloader; 完了.
if data_on_phone; then
    echo "note: the game data is on the phone (EMU_DATA / SOA_PHONE); no download"
else
    download 364:1043
fi
# 9. -> home: the notice board opens (ShowWebView).
if data_on_phone; then
    # The client may still fetch what the phone lacks (e.g. stand-in assets added since the phone
    # was built, or a master that differs with the clock): a small download dialog. Its buttons
    # (決定, ダウンロード, 完了) are tapped in turn until home, as summer_demo.sh / nier_demo.sh do.
    end=$(( $(date +%s) + 300 )) i=0
    while ! poll 6 in_elog "ShowWebView(http"; do
        alive || { miss "home (soa-emu exited)"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "home (notice board) (not within 300s)"; finish; }
        case $((i % 3)) in 0) ctl tap:364:1043;; 1) ctl tap:515:800;; 2) ctl tap:364:790;; esac
        i=$((i + 1))
    done
    pass "home (notice board)"
else
    tap_until "home (notice board)" 120 364:790 in_elog "ShowWebView(http" || finish
fi
if [ "${SESSION_PLAY:-1}" = 0 ]; then
    sleep 5
    shot home-notice
    ctl tap:364:1133
    sleep 10
    shot home
    finish
fi

# 10. The login popups: the notice board's 閉じる (until its web view closes), then the LOGIN
#     BONUS popup's 閉じる while a screenshot shows it (flowctl.py login-popups; the emulator's
#     log has the same ShowWebView lines as soa's).
if python3 "$flowctl" login-popups "$fifo" "$elog" "$out/notice.png" "$out/login-bonus.png" "$out/home.png" > "$out/popups.txt" 2>&1; then
    pass "login popups closed ($(tail -n 1 "$out/popups.txt"))"
else
    miss "login popups ($(tail -n 1 "$out/popups.txt"))"; finish
fi
state 1-home

# 11. ミッション -> the planet select (GetMissionList: the campaign's ActiveMissionList).
missions=$(count_plog "> GetMissionList")
tap_until "ミッション -> GetMissionList" 60 270:1085 more_than "< GetMissionListRes" "$missions" || finish
# 12. planet Mere (the next planet) -> 出撃 -> the mission map -> 1-05 (mf01_001, New) -> シングル
#     プレイ開始 -> no rental (選択しない) -> party 1 -> ミッション開始 -> 決定 (campaign_session.sh).
#     The client opens the planet select, or the map of the planet last played when it has one
#     (a phone that played before, EMU_DATA): the planet select's 出撃 button is the bright disc
#     at 587:795 (a grey mean of 0.65 in its 120x60 crop, the map's 0.25).
ctl wait:6000 "shot:$out/planets.png"
bright=$(convert "$out/planets.png" -crop 120x60+527+750 -colorspace gray -format '%[fx:mean > 0.45 ? 1 : 0]' info: 2>/dev/null)
if [ "$bright" = 1 ]; then
    ctl tap:660:520 wait:3000 tap:587:795 wait:7000
else
    echo "note: the mission map of the planet last played (no planet select)"
fi
shot mission-map
ctl tap:363:665 wait:4000 "shot:$out/mission-detail.png" tap:364:905 wait:5000 tap:620:1120 wait:5000 "shot:$out/party.png"
ctl tap:364:900 wait:3000 "shot:$out/start-confirm.png"
tap_until "1-05 -> MissionStart -> MissionStartRes" 60 515:712 in_plog "< MissionStartRes" || finish
# 13. The battle: the party's AI fights it; MissionEnd carries the battle log.
ctl wait:15000 "shot:$out/battle.png"
wait_for "MissionEnd (battle log) -> MissionEndRes" 600 in_plog "< MissionEndRes" || finish
blog=$(ls -t "$out"/packets/*-MissionEnd-battle_log.msgp 2>/dev/null | head -1)
if [ -n "$blog" ] && check=$(python3 - "$blog" "$slog" <<'EOF'
import re, sys, msgpack
log = msgpack.unpackb(open(sys.argv[1], "rb").read(), raw=False, strict_map_key=False)
t = log.get("mission_time", 0)
enemies = sum(e.get("num", 0) for e in log.get("DefeatedEnemyInfo", []))
evals = len(log.get("BattleEvaluationInfo", []))
srv = open(sys.argv[2], errors="replace").read()
m = re.findall(r"MissionEnd mission \d+: .* time (\d+) ms", srv)
ok = not log.get("is_defeat", True) and t > 0 and enemies > 0 and evals > 0 and m and int(m[-1]) == t
print(f"mission_time {t} ms, {enemies} enemies defeated, {evals} evaluations, server time {m[-1] if m else '-'} ms")
sys.exit(0 if ok else 1)
EOF
); then pass "battle log decoded by the server ($check)"; else miss "battle log (${check:-no MissionEnd battle_log in the packet log})"; fi
state 2-after-battle
grep -q "mission mf01_001: cleared" "$out/state-2-after-battle.txt" && pass "server state: mf01_001 cleared" || miss "server state: mf01_001 not cleared"
# 14. The Mission Result pages (OK at the same spot) until the mission map (GetMissionList).
missions=$(count_plog "< GetMissionListRes")
ctl wait:3000 "shot:$out/result.png"
tap_until "results -> the mission map (GetMissionList)" 90 510:1040 more_than "< GetMissionListRes" "$missions" || finish
ctl wait:4000 "shot:$out/map-after-clear.png" tap:60:1245 wait:8000 "shot:$out/home-after-battle.png"

# 15. Footer ガチャ -> GetGachaInData; the recommended tab, the first banner, 10連ガチャ.
tap_until "ガチャ -> GetGachaInData" 60 425:1250 in_plog "< GetGachaInDataRes" || finish
ctl wait:10000 "shot:$out/gacha.png" tap:100:175 wait:3000 tap:360:320 wait:4000 "shot:$out/gacha-detail.png" tap:540:945 wait:2500 "shot:$out/gacha-confirm.png"
# 16. 決定 -> SaleGacha; the presentation (召喚開始, two reveals, ALL SKIP), the result list (次へ,
#     閉じる), then ホーム (restore_session.sh's taps).
tap_until "10-draw: 決定 -> SaleGacha -> SaleGachaRes" 60 515:800 in_plog "< SaleGachaRes" || finish
ctl wait:6000 "shot:$out/summon.png" tap:364:1190 wait:12000 tap:364:650 wait:4000 tap:364:650 wait:4000 tap:577:1199 wait:5000 "shot:$out/gacha-result.png"
ctl tap:364:1002 wait:4000 tap:364:1002 wait:3000 "shot:$out/gacha-result-closed.png"
state 3-after-gacha
c2=$(sed -n 's/.* coins free \([0-9]*\) .*/\1/p' "$out/state-2-after-battle.txt")
c3=$(sed -n 's/.* coins free \([0-9]*\) .*/\1/p' "$out/state-3-after-gacha.txt")
if [ -n "$c2" ] && [ -n "$c3" ] && [ "$c3" -lt "$c2" ]; then pass "coins debited ($c2 -> $c3)"; else miss "no coins debited (${c2:-?} -> ${c3:-?})"; fi
n=$(grep -c '^  gacha ' "$out/state-3-after-gacha.txt" || true)
[ "$n" = 10 ] && pass "server state: 10 draws recorded" || miss "server state: $n draws recorded, not 10"
# 17. ホーム.
ctl tap:60:1245 wait:8000
shot home-end
in_plog "< ProtocolError" && miss "a ProtocolError in the packet log"
warnings=$(grep -c '^W/jni\|^W/loader\|^W/http' "$elog" || true)
echo "requests: $(grep -c ' > ' "$plog") game, $(gets) HTTP GET; JVM/HLE/HTTP warnings: $warnings"
finish
