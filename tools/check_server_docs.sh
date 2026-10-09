#!/bin/bash
# RG10 of docs/history/PLAN-readability.md: the local server's documentation checks (section 5), enforcing
# since R19 (a T0 gate: tests/tiers.json `server-docs`).
#   tools/check_server_docs.sh [--evidence REV] [--report] [--server BIN]
# Checks:
#   1. doc comments (tools/server_doc_coverage.py): every registered API's handler has the 2.5 block
#      (API: / Rules: lines and an (a)-(d) label, or `Rules: none (transport)`); every module hook
#      (soa-server --list-hooks) and every server/include/soaserver/ function has a doc comment;
#   2. docs links: every docs/server-rules.md / docs/api.md section quoted or anchored in server/
#      comments resolves (tools/server_evidence.py); since R20 a docs/server-rules.md link is an
#      anchor (docs/server-rules.md#titles), never a quoted title; docs/server-rules.md itself gives
#      every section an explicit anchor and its register is fresh (tools/server_rules_doc.py --check);
#   3. server/API-INDEX.md is fresh (tools/server_index.py --check; needs BIN, default build/server/soa-server),
#      and so is the generated server/src/core/errors.h (tools/gen_error_codes.py --check);
#   4. with --evidence REV: nothing lost against REV (tools/server_evidence.py --against REV):
#      labels, client addresses / symbols / offsets, master tables, agent count, log lines, links
#      (and their number), and the rules doc's evidence (docs/server-rules.md with its history).
#      A commit that deletes code with its labels says so in its message: a line starting
#      "Evidence removed:" (listing what went and why) lets that commit's loss pass, reported; each
#      commit of REV..HEAD that loses evidence needs its own (server_evidence.py --waivers);
#   5. the log lines scripts read (tools/server_log_patterns.txt) are in the LOG* format strings;
#   6. no "agent <name>" history notes in server/ code (describe the rule and its evidence instead);
#   7. no tracked file names a server/ path that doesn't exist (the plans and docs/history/ aside);
#   8. a README.md in server/src and every folder below it;
#   9. the handlers' clock: no clock_now(), time(nullptr) or event_now() read directly in the
#      handlers' code (server/src/api/, core/rewards.cpp, core/stub.cpp; their tests aside): they
#      use their ext::Ctx's now() / event_now(), the clock a test sets (ctx.test). A line may opt
#      out with a `clock-ok:` comment saying why.
# Exit 1 on any finding; --report prints them and exits 0 except for 4 and 5 (lost evidence or log
# lines always fail). --enforce (the default since R19) is still accepted. See server/README.md
# "Comment conventions".
set -uo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo"
rev="" enforce=1 server="$repo/build/server/soa-server"
while [ $# -gt 0 ]; do
  case "$1" in
    --evidence) rev=$2; shift 2 ;;
    --enforce) enforce=1; shift ;;
    --report) enforce=0; shift ;;
    --server) server=$2; shift 2 ;;
    *) echo "usage: $0 [--evidence REV] [--report] [--server BIN]" >&2; exit 2 ;;
  esac
done
findings=0 fail=0
note() { echo "  $*"; }

echo "== 1. doc comments: handlers (the 2.5 block with a label), hooks, include/soaserver functions"
"$repo/tools/py" tools/server_doc_coverage.py --server "$server" | sed 's/^/  /'
[ "${PIPESTATUS[0]}" = 0 ] || findings=$((findings + 1))

echo "== 2. docs links, 5. log lines, 6. agent mentions (tools/server_evidence.py)"
# the verdict is server_evidence.py --check's exit code (0, 10 findings, 11 a log line gone; anything
# else: the tool failed, which fails the check), never a grep of its printed lines
ev=$("$repo/tools/py" tools/server_evidence.py --check); evrc=$?
echo "$ev" | grep -E "^(doc links|log lines|agent mentions|server-rules links quoted|CHECK: )" | sed 's/^/  /'
case $evrc in
  0) ;;
  10) findings=$((findings + 1)) ;;
  *) [ $evrc = 11 ] || note "tools/server_evidence.py --check failed (exit $evrc)"
     findings=$((findings + 1)); fail=1 ;;
esac
"$repo/tools/py" tools/server_rules_doc.py --check | sed 's/^/  /'
[ "${PIPESTATUS[0]}" = 0 ] || findings=$((findings + 1))

echo "== 3. server/API-INDEX.md"
if [ -x "$server" ]; then
  "$repo/tools/py" tools/server_index.py --check --server "$server" | sed 's/^/  /'
  [ "${PIPESTATUS[0]}" = 0 ] || findings=$((findings + 1))
else
  note "no $server: not checked (build soa-server, or pass --server)"
  findings=$((findings + 1))
fi
"$repo/tools/py" tools/gen_error_codes.py --check | sed 's/^/  /'
[ "${PIPESTATUS[0]}" = 0 ] || findings=$((findings + 1))

echo "== 4. evidence"
if [ -n "$rev" ]; then
  # --waivers: a loss passes only when each commit that made one says "Evidence removed:" itself
  "$repo/tools/py" tools/server_evidence.py --against "$rev" --waivers | sed 's/^/  /'
  [ "${PIPESTATUS[0]}" = 0 ] || { findings=$((findings + 1)); fail=1; }
else
  note "(no --evidence REV given)"
fi

echo "== 7. references to server/ paths"
# A path counts as present when a file or folder starts with it (a stem like server/net/ninja/ninja_ref
# names ninja_ref.{h,cpp}). The plans (server/PLAN-*.md name the target layout) and docs/history/
# (the record) are not checked, nor cmake/vcpkg-triplets/ (any edit there changes every vcpkg
# port's ABI hash and rebuilds all dependencies, so its comments keep the paths they had).
missing=$(git ls-files -z -- . ':!server/PLAN-*.md' ':!docs/history' ':!cmake/vcpkg-triplets' | xargs -0 grep -IhoE '(^|[^A-Za-z0-9_./-])server/(src|include|net|app|tests)/[A-Za-z0-9_./-]*[A-Za-z0-9_]' 2>/dev/null |
  sed -E 's/^[^s]*(server\/)/\1/' | sort -u | while read -r p; do
    [ -e "$p" ] || compgen -G "$p*" > /dev/null || echo "$p"
  done)
if [ -n "$missing" ]; then
  note "named but missing: $(echo "$missing" | wc -l)"
  echo "$missing" | head -20 | sed 's/^/    /'
  findings=$((findings + 1))
else
  note "every server/ path named in a tracked file exists"
fi

echo "== 8. READMEs"
nr=0
while read -r d; do
  if [ ! -f "$d/README.md" ]; then note "no README.md in $d"; nr=1; fi
done < <(find server/src -type d)
[ $nr = 0 ] && note "every server/src folder has a README.md" || findings=$((findings + 1))

echo "== 9. the handlers' clock (ext::Ctx::now)"
direct=$(git ls-files -- 'server/src/api/*.cpp' 'server/src/api/*.h' server/src/core/rewards.cpp server/src/core/stub.cpp | grep -v '_tests\.cpp$' |
  xargs grep -nE '(^|[^A-Za-z0-9_.>])(clock_now\(\)|time\((nullptr|NULL|0)\)|event_now\(\))' 2>/dev/null | grep -v 'clock-ok:' || true)
if [ -n "$direct" ]; then
  note "a direct clock read in a handler (use ctx.now() / ctx.event_now()): $(echo "$direct" | wc -l)"
  echo "$direct" | head -20 | sed 's/^/    /'
  findings=$((findings + 1))
else
  note "the handlers read the clock through their ext::Ctx"
fi

echo "== check_server_docs: $findings finding(s)$([ $fail = 1 ] && echo ', evidence or log lines lost')"
[ $fail = 1 ] && exit 1
[ $enforce = 1 ] && [ $findings -gt 0 ] && exit 1
exit 0
