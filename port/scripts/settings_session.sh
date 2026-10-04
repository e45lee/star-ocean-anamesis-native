#!/bin/sh
# The options the server keeps (その他設定: 一時保管庫設定 on, kept over a restart, 初期設定に戻す) and
# シナリオライブラリ (Episode 1's planted clears listed). OUT/shots, OUT/log.txt, OUT/log-2.txt.
#
# Usage: port/scripts/settings_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/settings.py (its doc: the steps, the checks):
# `control/run.py settings --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec python3 "$(dirname "$0")/../../control/run.py" settings "$@"
