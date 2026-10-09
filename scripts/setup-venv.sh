#!/bin/bash
# The Python environment (README.md "Setup"): .venv with requirements.txt, and soa-checkout.pth,
# which makes the checkout's code importable (soa_save, control/: soadrive and soaslot / soactl /
# flowctl / gdbclient, tools/, port/scripts/) without any sys.path edits in the scripts.
#
#   scripts/setup-venv.sh          create .venv if missing, install requirements.txt, write the .pth
#   scripts/setup-venv.sh --pth    only (re)write the .pth into an existing .venv
#
# Everything runs it through tools/py (the shebangs, the shell scripts, tests/tiers.json).
# Not `pip install -e .`: an editable install records absolute paths, and a worktree's .venv is a
# link to the main checkout's, so every worktree would import the main checkout's code. The .pth's
# lines are relative to the site-packages folder, which Python names by the .venv path it was
# started from (not the link's target), so each checkout resolves them to itself.
set -euo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo"
pth_only=0
case ${1:-} in
    --pth) pth_only=1 ;;
    "") ;;
    *) echo "usage: scripts/setup-venv.sh [--pth]" >&2; exit 2 ;;
esac
if [ "$pth_only" = 0 ]; then
    [ -x .venv/bin/python ] || python3 -m venv .venv
    .venv/bin/pip install -r requirements.txt
fi
[ -x .venv/bin/python ] || { echo "setup-venv.sh: no .venv (run it without --pth)" >&2; exit 1; }
.venv/bin/python -I - "$repo" <<'PY'
import os, sys, sysconfig
repo = os.path.abspath(sys.argv[1])
site = os.path.abspath(sysconfig.get_path("purelib"))
venv = os.path.join(repo, ".venv")
if os.path.commonpath([site, venv]) != venv:
    sys.exit(f"setup-venv.sh: site-packages {site} is not inside {venv}")
lines = []
for d in ("", "control", "tools", "port/scripts"):
    target = os.path.join(repo, d) if d else repo
    rel = os.path.relpath(target, site)
    if os.path.abspath(os.path.join(site, rel)) != os.path.abspath(target) or not os.path.isdir(target):
        sys.exit(f"setup-venv.sh: {target} doesn't resolve from {site}")
    lines.append(rel)
with open(os.path.join(site, "soa-checkout.pth"), "w") as f:
    f.write("\n".join(lines) + "\n")
print(f"setup-venv.sh: {os.path.join(site, 'soa-checkout.pth')}: " + ", ".join(lines))
PY
