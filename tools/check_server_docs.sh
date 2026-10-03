#!/bin/bash
# RG10 of server/PLAN-readability.md: the local server's documentation checks (section 5).
#   tools/check_server_docs.sh [--evidence REV] [--enforce] [--server BIN]
# Runs, and reports:
#   1. handler doc blocks: how many registered APIs have the 2.5 block (API: / Rules: lines in the
#      comment above the handler) - coverage, reported;
#   2. docs links: every docs/server-rules.md / docs/api.md section quoted or anchored in server/
#      comments resolves (tools/server_evidence.py);
#   3. server/API-INDEX.md is fresh (tools/server_index.py --check; needs BIN, default build/server/soa-server),
#      and so is the generated server/src/core/errors.h (tools/gen_error_codes.py --check);
#   4. with --evidence REV: nothing lost against REV (tools/server_evidence.py --against REV):
#      labels, client addresses / symbols / offsets, master tables, agent count, log lines, links;
#   5. the log lines scripts read (tools/server_log_patterns.txt) are in the LOG* format strings;
#   6. "agent <name>" history notes in server/{src,include,net,app} code: the count (0 at R19);
#   7. no tracked file names a server/ path that doesn't exist (the plans and docs/history/ aside);
#   8. a README.md in server/src and every folder below it.
# Report-only for now (exit 0) except 4, which fails (exit 1) when evidence is lost: it is RG10's
# gate for every step. --enforce makes every finding fail (R19). See server/README.md
# "Comment conventions".
set -uo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo"
rev="" enforce=0 server="$repo/build/server/soa-server"
while [ $# -gt 0 ]; do
  case "$1" in
    --evidence) rev=$2; shift 2 ;;
    --enforce) enforce=1; shift ;;
    --server) server=$2; shift 2 ;;
    *) echo "usage: $0 [--evidence REV] [--enforce] [--server BIN]" >&2; exit 2 ;;
  esac
done
findings=0 fail=0
note() { echo "  $*"; }

echo "== 1. handler doc blocks (server/PLAN-readability.md 2.5)"
python3 - "$repo" <<'EOF'
import os, re, sys
sys.path.insert(0, os.path.join(sys.argv[1], "tools"))
import server_index as si
core, lines = si.core_handlers()
mods = si.module_handlers()
def block_above(lines, at):
    out, i = [], at - 2
    while i >= 0 and lines[i].lstrip().startswith("//"):
        out.append(lines[i]); i -= 1
    return "\n".join(reversed(out))
have = total = 0
seen = set()
for m, (f, line, fn, body, _) in core.items():
    key = (f, line)
    if key in seen: continue
    seen.add(key); total += 1
    b = block_above(si.read(os.path.join(sys.argv[1], f)), line)
    have += ("API:" in b and "Rules:" in b)
for m, (f, line, fn, body) in mods.items():
    key = (f, line)
    if key in seen: continue
    seen.add(key); total += 1
    b = block_above(si.read(os.path.join(sys.argv[1], f)), line)
    have += ("API:" in b and "Rules:" in b)
print("  %d of %d handlers have the API: / Rules: block (reported; enforced from R19)" % (have, total))
sys.exit(0 if have == total else 3)
EOF
[ $? = 3 ] && findings=$((findings + 1))

echo "== 2. docs links, 5. log lines, 6. agent mentions (tools/server_evidence.py)"
ev=$(python3 tools/server_evidence.py)
echo "$ev" | grep -E "^(doc links|log lines|agent mentions)" | sed 's/^/  /'
echo "$ev" | grep -qE "^doc links .*, 0 broken" || findings=$((findings + 1))
echo "$ev" | grep -qE "^log lines ([0-9]+)/\1 present" || { findings=$((findings + 1)); fail=1; }
agents=$(echo "$ev" | sed -n 's/^agent mentions //p')
[ "${agents:-0}" = 0 ] || findings=$((findings + 1))

echo "== 3. server/API-INDEX.md"
if [ -x "$server" ]; then
  python3 tools/server_index.py --check --server "$server" | sed 's/^/  /'
  [ "${PIPESTATUS[0]}" = 0 ] || findings=$((findings + 1))
else
  note "no $server: not checked (build soa-server, or pass --server)"
fi
python3 tools/gen_error_codes.py --check | sed 's/^/  /'
[ "${PIPESTATUS[0]}" = 0 ] || findings=$((findings + 1))

echo "== 4. evidence"
if [ -n "$rev" ]; then
  python3 tools/server_evidence.py --against "$rev" | sed 's/^/  /'
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

echo "== check_server_docs: $findings finding(s)$([ $fail = 1 ] && echo ', evidence or log lines lost')"
[ $fail = 1 ] && exit 1
[ $enforce = 1 ] && [ $findings -gt 0 ] && exit 1
exit 0
