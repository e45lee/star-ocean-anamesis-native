#!/bin/sh
# The restored 3.7.0 home (the in-process local server): every home button, each checked by the phase
# it switches to or the request it sends: イベント, ミッション, スフィア211 (GetSphere211Info), ディープスペース;
# the ≡ menu (フォロー, 称号 SetTitle, お知らせ), プレゼント (PresentList), 実績 (AchievementActiveList),
# オススメ!, 情報保存, stamina +; the footer (キャラクター, アイテム, ガチャ GetGachaInData, ショップ, その他).
# HOME_REF=DIR compares each shot with a reference; OUT/strip.png. Exit 1 if a destination is missed.
#
# Usage: port/scripts/home_session.sh <soa> <out-dir> <scratch-dir> [soa flags...]   (from any directory)
# Env: HOME_REF, SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/home.py (its doc: the steps, the environment, the outputs):
# `control/run.py home --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" home "$@"
