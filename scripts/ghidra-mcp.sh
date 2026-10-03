#!/bin/sh
# Serves the 3.7.0 client's Ghidra project (libSOA-3.7.0.so) over MCP with pyghidra-mcp
# (https://github.com/clearbluejar/pyghidra-mcp, run through uvx), for Claude Code: .mcp.json
# registers it as the project's "ghidra-v370" server (stdio).
#
# The server opens its own working copy of the project, work/ghidra-mcp-v370/, made from the
# local ghidra/quick-v370 (not in git) the first time, so the analysis, renames and types it saves
# never touch the committed project or the tools/decomp.sh pool (work/ghidra-quick-v370*). Run
# --analyze once first (below). Only one server can have the copy open (a lock); a second one exits
# with a message.
#
# Usage: scripts/ghidra-mcp.sh [--fresh] [--analyze] [pyghidra-mcp options...]   (default: stdio)
#   --fresh     delete the working copy first (start again from the committed project)
#   --analyze   once, before first use: Ghidra's full auto-analysis of the program plus pyghidra-mcp's
#               code and string indexes, saved in the working copy, then exit (the committed project
#               is a quick import without analysis, and the MCP tools refuse until it's done; this
#               takes a while for the 46 MB library). Later starts reuse it.
# Ghidra always runs headless here (--no-gui).
#   e.g. scripts/ghidra-mcp.sh -t streamable-http -p 8765   to serve over HTTP instead
# Env: GHIDRA_INSTALL_DIR (default /snap/ghidra/current/ghidra), SOA_GHIDRA_MCP_PROJECT (the
# working copy's directory). Needs uvx and Ghidra 12.1.2+; see README.md "Reverse-engineering tools".
#
# stdout is the MCP channel: everything this script says goes to stderr.
set -eu
case "${1:-}" in -h|--help) sed -n '2,23p' "$0" | sed 's/^# \{0,1\}//'; exit 0;; esac
repo=$(cd "$(dirname "$0")/.." && pwd)
# work/ may be a symlink (agent worktrees); Ghidra refuses paths with a component starting with
# "." (the worktrees live under .claude/), so use the real path.
work=$(cd -P "$repo/work" 2>/dev/null && pwd) || { echo "ghidra-mcp: $repo/work not found" >&2; exit 1; }
proj=${SOA_GHIDRA_MCP_PROJECT:-$work/ghidra-mcp-v370}
tracked=$repo/ghidra/quick-v370
export GHIDRA_INSTALL_DIR="${GHIDRA_INSTALL_DIR:-/snap/ghidra/current/ghidra}"
command -v uvx > /dev/null 2>&1 || { echo "ghidra-mcp: uvx not found (pyghidra-mcp runs through uvx)" >&2; exit 1; }
[ -d "$GHIDRA_INSTALL_DIR/Ghidra" ] || { echo "ghidra-mcp: no Ghidra at $GHIDRA_INSTALL_DIR (set GHIDRA_INSTALL_DIR)" >&2; exit 1; }

if [ "${1:-}" = --fresh ]; then shift; rm -rf "${proj:?}"; fi
analyze=0
if [ "${1:-}" = --analyze ]; then shift; analyze=1; fi
if [ ! -e "$proj/quick.gpr" ]; then
    [ -e "$tracked/quick.gpr" ] || { echo "ghidra-mcp: $tracked missing (run tools/decomp.sh once to import the project; README \"Game files\")" >&2; exit 1; }
    echo "ghidra-mcp: making the working copy $proj from $tracked" >&2
    rm -rf "${proj:?}.tmp"
    cp -r "$tracked" "$proj.tmp" && mv "$proj.tmp" "$proj"
fi

# One server per working copy (Ghidra locks an open project; a second opener fails obscurely).
exec 9> "$proj.lock"
flock -n 9 || { echo "ghidra-mcp: another server has $proj open (lock $proj.lock)" >&2; exit 1; }

cd "$proj"   # pyghidra-mcp's relative defaults (e.g. its symbols dir) land in the copy, not the repo
if [ $analyze = 1 ]; then
    echo "ghidra-mcp: analysing $proj (headless; the server exits when it's done)" >&2
    # stdin at EOF: the stdio server stops right after its start-up, i.e. after the analysis.
    exec uvx pyghidra-mcp --no-gui --project-path "$proj/quick.gpr" --force-analysis --wait-for-analysis "$@" < /dev/null
fi
exec uvx pyghidra-mcp --no-gui --project-path "$proj/quick.gpr" "$@"
