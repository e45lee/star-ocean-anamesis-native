#!/bin/bash
# Drives two held mp_client.sh clients (729x1296 window coordinates) through a co-op mission and
# screenshots both at the same moments into SHOTS/.
# Usage: mp_drive.sh HOST_OUT GUEST_OUT SHOTS [STEP...]
#   steps (default: all, in order):
#     host-room   host: マルチプレイ開始 -> ルームを作成 -> party 決定 -> 募集開始 -> confirm
#     guest-join  guest: マルチプレイ開始 -> ルームに参加 -> ルームを全検索 -> the room's first FREE slot
#     battle      host: バトル開始 -> 出撃する; both: a screenshot every 1.8 s for ~55 s
# The waits are generous: a tap during a screen transition is lost, and a lost tap leaves the
# client on another screen (check the screenshots).
set -u
host=${1:?HOST_OUT}; guest=${2:?GUEST_OUT}; shots=${3:?SHOTS}; shift 3
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../../.." && pwd)
soactl=$repo/control/soactl.py
mkdir -p "$shots"
ctl() { local o=$1; shift; python3 "$soactl" --timeout 180 "$o/fifo" "$@" > /dev/null 2>&1; }
both() { ctl "$host" "shot:$shots/$1-host.png" & ctl "$guest" "shot:$shots/$1-guest.png"; wait; }
steps=${*:-host-room guest-join battle}
for step in $steps; do
    case $step in
    host-room)
        ctl "$host" tap:527:905 wait:7000 "shot:$shots/h1-multiplay-menu.png" tap:364:527 wait:9000 \
            "shot:$shots/h2-party.png" tap:364:900 wait:12000 "shot:$shots/h3-create-room.png" \
            tap:527:948 wait:5000 "shot:$shots/h4-confirm.png" tap:515:800 wait:9000
        both room-alone ;;
    guest-join)
        ctl "$guest" tap:527:905 wait:7000 tap:364:648 wait:9000 "shot:$shots/g1-party.png" \
            tap:364:905 wait:8000 "shot:$shots/g2-room-list.png" tap:284:497 wait:9000
        both room ;;
    battle)
        ctl "$host" tap:140:948 wait:3500 "shot:$shots/h5-fill-dialog.png"
        hc="tap:515:800" gc=""
        for i in $(seq -w 1 30); do hc="$hc wait:1800 shot:$shots/b$i-host.png"; gc="$gc wait:1800 shot:$shots/b$i-guest.png"; done
        # shellcheck disable=SC2086
        ctl "$host" $hc & ctl "$guest" $gc; wait ;;
    *) echo "unknown step $step"; exit 1 ;;
    esac
done
