#!/bin/sh
# Event missions, restored (the in-process local server), from the title through the real UI: イベント ->
# 素材 tab -> the day's EXP material mission -> its battle -> the result pages -> CLEAR and the next
# mission New; with a known clock also a story event (2020-05-29 15:00:00: 滅びの星に鬼が舞う, its story
# and the battle with an event NPC helper; 2021-06-10 15:00:00: 夢追い少女と銀河の歌星's story).
# Ends with "events_session: PASS" or "events_session: FAIL (N)" (exit 1).
#
# Usage: port/scripts/events_session.sh <soa> <out-dir> <scratch-dir> [clock "YYYY-MM-DD HH:MM:SS"]
# Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
# The session is control/soadrive/sessions/events.py (its doc: the steps, the environment, the outputs):
# `control/run.py events --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" events "$@"
