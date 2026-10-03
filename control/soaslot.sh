# The game-process slot pool for shell scripts (sourced; POSIX sh, also from bash). control/soaslot.py
# has the pool (N, the directory, the memory gate); this takes a slot for the calling shell.
#
#   soaslot_take NAME   waits for a slot and holds it on file descriptor 9 for the rest of the
#                       shell's life: every process it starts (soa, soa-emu, soa-viewer) inherits
#                       the descriptor, so the slot stays taken while any of them runs, and frees
#                       itself when the last one exits (no release needed; killing works as before).
#                       Exports SOA_SLOT_HELD=1 so that a script it starts doesn't take a second
#                       slot. A no-op with SOA_SLOTS=0 or when SOA_SLOT_HELD is already set.
#                       With SOA_SLOT_SOFTWARE_GL=1 it also exports the variables that put the
#                       clients on Mesa's llvmpipe (soaslot.py SOFTWARE_GL_ENV), held or not.
# One slot per script: the port's session scripts and the emulator's run one client at a time.
soaslot_take() {
    _ss_lib=${SOASLOT_PY:-control/soaslot.py}
    [ -n "${SOA_SLOT_SOFTWARE_GL:-}" ] && [ -f "$_ss_lib" ] && eval "$(python3 "$_ss_lib" gl-env)"  # prints nothing when off
    [ -n "${SOA_SLOT_HELD:-}" ] && return 0
    [ -f "$_ss_lib" ] || { echo "soaslot: $_ss_lib not found (run from the repo root or set SOASLOT_PY)"; return 1; }
    while :; do
        _ss_f=$(python3 "$_ss_lib" pick "${1:-game}") || return 0  # pool off
        exec 9<>"$_ss_f"
        if flock -n 9; then
            printf '%s %s %s %s\n' "$$" "$(date +%s)" "${1:-game}" "$PWD" > "$_ss_f"
            SOA_SLOT_HELD=1; export SOA_SLOT_HELD
            return 0
        fi
        exec 9>&-  # another process took it between the pick and the lock: ask again
    done
}
