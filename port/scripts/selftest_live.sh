#!/bin/sh
# soa's self-tests on a live screen (home, or 15 s into a battle) instead of the title: the layout tests
# of render / scene / anim on the running game's objects. The session's doc: control/soadrive/sessions/
# selftest_live.py.
# Usage: port/scripts/selftest_live.sh SOA OUT TMP FILTER [--at home|battle]
exec "$(dirname "$0")/../../tools/py" "$(dirname "$0")/../../control/run.py" --target port-server selftest-live "$@"
