#!/bin/sh
# キャラクター > マスタリー under the local server (in-process, or soa-server with --target port-server):
# a 師弟 pair formed in 道場1 (TrainMastery), its five trainings (the fifth with the pass medal) to
# 皆伝, then a second boot: the pair kept (GetMasteryInfo), parted (ResetMastery). The state DB is
# planted before boot (two LV70 characters, the trainings' materials, pass medals).
#
# Usage: port/scripts/mastery_session.sh [--target port-inproc|port-server] <soa> <out-dir> <scratch-dir>
# Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/mastery.py (its doc: the steps, the outputs):
# `control/run.py mastery --help`. Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" mastery "$@"
