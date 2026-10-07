# Shared settings for the shell tools. Source it: . "$(dirname "$0")/common.sh"
REPO=$(cd "$(dirname "$0")/.." && pwd)
WORK=$(cd "$REPO/work" && pwd -P)
GHIDRA_HOME=${GHIDRA_HOME:-/snap/ghidra/current/ghidra}
PYTHON=${PYTHON:-$REPO/.venv/bin/python}
PKG=com.square_enix.android_googleplay.StarOceanj

# Which libSOA build the Ghidra tools work on. Default: the 3.7.0 client the port runs
# (work/libSOA-3.7.0.so, project pool work/ghidra-quick-v370*). `--v380` as the first argument of (380-ok)
# decomp.sh / decomp_at.sh (or SOA_V380=1) selects the offline build the viewer runs, for the (380-ok)
# viewer and the history (its project pool work/ghidra-quick*; 380-ok). `--v370` / SOA_V370=1 is
# still accepted and is the default. SOA_LIB is exported so elfinfo.py / resolve_decomp.py
# resolve names against the same file.
if [ "${SOA_V380:-0}" = 1 ]; then  # 380-ok: the viewer's lib
  GHIDRA_QUICK=$WORK/ghidra-quick
  GHIDRA_TRACKED=$REPO/ghidra/quick
  SOA_LIB=$WORK/extracted/config.arm64_v8a/lib/arm64-v8a/libSOA.so  # the viewer's lib (380-ok)
  GHIDRA_PROG=libSOA.so
else
  GHIDRA_QUICK=$WORK/ghidra-quick-v370
  GHIDRA_TRACKED=$REPO/ghidra/quick-v370
  SOA_LIB=$WORK/libSOA-3.7.0.so
  GHIDRA_PROG=libSOA-3.7.0.so
fi
export SOA_LIB

# The quick projects are kept under ghidra/ (local, not in git since 2026-10-03), so they survive a
# lost work/ pool. ghidra_project_ready: make $GHIDRA_QUICK usable, restoring it from that copy, or
# importing it (and saving a copy to ghidra/) when neither exists.
ghidra_project_ready() {
  [ -e "$GHIDRA_QUICK/quick.rep" ] && return 0
  mkdir -p "$WORK/ghidra"
  if [ -e "$GHIDRA_TRACKED/quick.rep" ]; then
    rm -rf "${GHIDRA_QUICK:?}.tmp"; cp -r "$GHIDRA_TRACKED" "$GHIDRA_QUICK.tmp" && mv "$GHIDRA_QUICK.tmp" "$GHIDRA_QUICK"
    return 0
  fi
  mkdir -p "$GHIDRA_QUICK"
  "$GHIDRA_HOME/support/analyzeHeadless" "$GHIDRA_QUICK" quick -import "$SOA_LIB" -noanalysis > "$WORK/ghidra/$(basename "$GHIDRA_QUICK")-import.log" 2>&1
  mkdir -p "$(dirname "$GHIDRA_TRACKED")"; rm -rf "${GHIDRA_TRACKED:?}"; cp -r "$GHIDRA_QUICK" "$GHIDRA_TRACKED"
  echo "imported a new Ghidra project; a copy is kept in $GHIDRA_TRACKED" >&2
}

# Ghidra locks a project while a headless run has it open, so concurrent decompiles each take
# one of several copies of the quick project ($GHIDRA_QUICK, $GHIDRA_QUICK-N).
# Usage: ghidra_run <project-dir-var-name> <command...> — runs the command with the variable
# set to a free copy, holding its lock for the duration.
GHIDRA_SLOTS=${GHIDRA_SLOTS:-6}
ghidra_run() {
  _var=$1; shift
  while :; do
    _i=0
    while [ $_i -lt "$GHIDRA_SLOTS" ]; do
      _p=$GHIDRA_QUICK; [ $_i -gt 0 ] && _p=$GHIDRA_QUICK-$_i
      if [ $_i -gt 0 ] && [ ! -e "$_p/quick.rep" ]; then
        ( flock 8; [ -e "$_p/quick.rep" ] || { rm -rf "$_p.tmp"; cp -r "$GHIDRA_QUICK" "$_p.tmp" && mv "$_p.tmp" "$_p"; } ) 8>"$GHIDRA_QUICK.copy.lock"
      fi
      if exec 9>"$_p.slot.lock" && flock -n 9; then
        eval "$_var=\$_p"; "$@"; _rc=$?; flock -u 9; return $_rc
      fi
      _i=$((_i+1))
    done
    sleep 2
  done
}
