#!/bin/sh
# Episode 2 / 3 opening stories (the in-process local server): the episode pack downloaded through the
# client's own flow (SOA_EPISODE_PACKS=0: the "ask" flow, 1: the save's), その他 -> Episodeデータ管理,
# then the episode's world map -> 1-01 -> the opening movie played to its end (MovieFinished) -> the scene
# ends (EndMissionTalk).
#
# Usage: port/scripts/episode_movie_session.sh <soa> <out-dir> <scratch-dir> [2|3]   (from any directory)
# Env: CAMPAIGN_SEED, HOME_MISSION_X, SOA_EPISODE_PACKS, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/episode_movie.py (its doc: the steps, the environment, the outputs):
# `control/run.py episode-movie --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" episode-movie "$@"
