#!/bin/sh
# Scripted route into the gacha (729x1296 window), for coverage/profiling and as a gacha check:
# title -> Login -> home -> the footer's ガチャ (GetGachaInData) -> the four tabs -> おすすめガチャ's first
# banner -> 10連ガチャ -> 決定 (SaleGacha) -> the presentation -> the result list -> ホーム; the server
# state before and after the draw (the coins debited, the draws recorded).
#
# Usage: port/scripts/gacha_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1; SOA_COVERAGE / SOA_PROFILE pass through.
# The session is control/soadrive/sessions/gacha.py (its doc: the steps, the environment, the outputs):
# `control/run.py gacha --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" gacha "$@"
