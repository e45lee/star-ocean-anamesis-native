#!/bin/sh
# The growth screens (the in-process local server): strengthening to the level cap (BoostCharacter),
# evolution to ★6 (EvolutionCharacter), limit break (LimitBreakCharacter), weapon custom: a gear set
# (AttachGear), taken off with grease (RemoveGear), gear purified (GenerateGear). The materials are
# written into the server's state DB before boot. GROWTH_KEEP=1 leaves the game running.
#
# Usage: port/scripts/growth_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: GROWTH_KEEP, SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
# The session is control/soadrive/sessions/growth.py (its doc: the steps, the environment, the outputs):
# `control/run.py growth --help`; `--target T` as the first argument runs it against another program
# when the session supports it (control/run.py --list). Exit 0 = PASS, 1 = FAIL.
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" growth "$@"
