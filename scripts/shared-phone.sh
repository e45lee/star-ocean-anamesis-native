# The shared pre-downloaded 3.7.0 phone (sourced; POSIX sh, also from bash).
#
# One phone with the 3.7.0 game data downloaded (data/files/download: 26,055 files, 4.0 GB, the
# episode packs EP1-3 included; 24,637 files, 3.3 GB without them) is
# built once by scripts/make-phone-370.sh into work/phone-3.7.0 (SOA_SHARED_PHONE overrides the
# place), stamped (PHONE.txt, files.txt: size, mtime and path of every file; sha256sums.txt) and
# made read-only (chmod -R a-w). A run's phone is then built from it in under a second instead of a
# 4 GB `cp -a` (or a 3-4 minute download): real (writable) directories, a hard link per downloaded
# file (cp -al), and real copies of the two files the client writes in place (port/README.md "The
# shared pre-downloaded phone": the strace of what the client writes, and why hard links and not
# symbolic links). Where a hard link can't be made (another file system) symbolic links are used.
# A run's phone is deleted with a plain rm -rf (its directories are writable); never chmod its
# files: they are the shared inodes.
#
#   shared_phone_dir REPO      the shared phone's directory (whether it exists or not)
#   shared_phone_check DIR     cheap check: DIR is a stamped phone and every file's size and mtime
#                              still match files.txt (exit 1 with a message otherwise)
#   shared_phone_resolve REPO  sets SOA_PHONE for a session script: unset -> the shared phone when
#                              it is built and passes shared_phone_check (else empty: the client
#                              downloads); "none" or empty -> empty (the full download); a
#                              directory -> kept. Exported.
#   shared_phone_link SRC DST  builds the run phone DST (deleted first) from SRC: a stamped phone is
#                              linked (see above); any other phone (e.g. a KEEP_DATA=1 run's) is
#                              copied with cp -a as before, so a writable source is never modified.
#                              Run-specific state is never carried over: data/shared_prefs/Aska.xml
#                              (the local KVS) is deleted; Game.xml, server.sqlite3 etc. come from
#                              SRC only when it is a copied (unstamped) phone.

# Downloaded files the client opens for writing in place on every run (O_RDWR / O_APPEND /
# O_TRUNC on the existing file, not write-new-then-rename): copied, never linked. Paths relative to
# data/files/download. Directories may be given (their whole tree is copied).
SHARED_PHONE_COPY="version.bin manifest"

shared_phone_dir() {
    echo "${SOA_SHARED_PHONE:-${1:?}/work/phone-3.7.0}"
}

shared_phone_check() {
    _d=${1:?}
    [ -f "$_d/PHONE.txt" ] && [ -f "$_d/files.txt" ] || { echo "shared phone: $_d is not a stamped phone (scripts/make-phone-370.sh)"; return 1; }
    _now=$(cd "$_d" && find data -type f -printf '%s %T@ %p\n' | LC_ALL=C sort -k3)
    if [ "$_now" != "$(cat "$_d/files.txt")" ]; then
        echo "shared phone: $_d changed since it was stamped (sizes / mtimes / files differ from files.txt);"
        echo "  scripts/check-phone-370.sh $_d says which files; rebuild it with scripts/make-phone-370.sh"
        return 1
    fi
}

shared_phone_resolve() {
    if [ -z "${SOA_PHONE+set}" ]; then
        _sp=$(shared_phone_dir "$1")
        if [ -d "$_sp/data/files/download" ] && shared_phone_check "$_sp"; then
            SOA_PHONE=$_sp
        else
            [ -d "$_sp" ] && echo "note: not using the shared phone $_sp (see above)" || echo "note: no shared phone at $_sp (scripts/make-phone-370.sh builds it): the client downloads its data"
            SOA_PHONE=
        fi
    elif [ "$SOA_PHONE" = none ]; then
        SOA_PHONE=
    fi
    export SOA_PHONE
}

shared_phone_link() {
    _src=$(cd "${1:?}" && pwd) _dst=${2:?}
    [ -d "$_src/data/files/download" ] || { echo "FAIL: phone $_src has no data/files/download"; return 1; }
    rm -rf "${_dst:?}"
    mkdir -p "$(dirname "$_dst")"
    if [ ! -f "$_src/PHONE.txt" ]; then
        cp -a "$_src" "$_dst" || return 1
    else
        _dl=data/files/download
        mkdir -p "$_dst/data/files" "$_dst/data/shared_prefs" "$_dst/data/cache"
        # Real directories, made writable (cp copies their read-only mode; the client creates files
        # in them: download/temp.sqlite3, the bundles under download/B/, X.tmp before its rename to
        # X), and a hard link per file: the shared, read-only inode. cp -rs (symbolic links) when the
        # run's phone is on another file system: 10x slower, 4 KB per link.
        if ! cp -al "$_src/$_dl" "$_dst/$_dl" 2>/dev/null; then
            rm -rf "${_dst:?}/$_dl"
            cp -rs "$_src/$_dl" "$_dst/$_dl" || return 1
        fi
        find "$_dst/$_dl" -type d -exec chmod u+w {} + || return 1
        for _p in $SHARED_PHONE_COPY; do
            [ -e "$_src/$_dl/$_p" ] || continue
            rm -rf "${_dst:?}/$_dl/$_p"
            cp -r "$_src/$_dl/$_p" "$_dst/$_dl/$_p" || return 1
            chmod -R u+w "$_dst/$_dl/$_p"
        done
    fi
    mkdir -p "$_dst/data/shared_prefs"
    rm -f "$_dst/data/shared_prefs/Aska.xml"
}
