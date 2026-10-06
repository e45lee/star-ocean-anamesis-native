#!/bin/sh
# The original (3.7.0) story campaign, restored (the in-process local server), through the real UI:
# home -> ミッション -> Episode 1 -> planet Mere -> the mission map -> 1-05 (mf01_001) -> single play ->
# no rental -> party 1 -> the battle (MissionStart / MissionEnd) -> the results -> the map: 1-05 CLEAR,
# mc01_030 unlocked -> its story scene (skipped; MissionTalk). --campaign-seed mf01_001.
#
# Usage: port/scripts/campaign_session.sh <soa> <out-dir> <scratch-dir> [soa flags...]   (from any directory)
# Env: CAMPAIGN_SEED, CAMPAIGN_MASTER_DB, HOME_MISSION_X, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/campaign.py (its doc: the steps, the environment, the outputs):
# `control/run.py campaign --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" campaign "$@"
