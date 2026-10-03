# Shared steps of the port's session scripts on the 3.7.0 client (sourced; POSIX sh).
#
# The 3.7.0 client checks its game data against the server's CDN after Login and, on an empty
# phone, downloads it first (about 3 GB, 1,032 GETs from the in-process CDN: 3-4 minutes, plus two
# dialogs). Sessions start from a pre-downloaded phone instead, and the client only checks its
# manifests (Bulk, Individual, ep1-3) and downloads what the phone lacks, e.g. a master the server
# edited for the run's options (the episode packs only when the client save asks for them:
# phone370_client_save; port/README.md "The shared pre-downloaded phone"). SOA_PHONE picks it
# (scripts/shared-phone.sh, resolved when this file is sourced):
#   unset           the shared phone work/phone-3.7.0 (scripts/make-phone-370.sh builds it once),
#                   linked: real directories, a hard link per downloaded file, copies of the two
#                   files the client writes in place; under a second instead of a 3 GB copy. When
#                   it isn't built (or fails its cheap check), the client downloads.
#   none (or empty) no phone: the client downloads all of its data (the test of the download)
#   DIR             that phone (e.g. a KEEP_DATA=1 emulator/scripts/emulator_session.sh run's
#                   OUT/emu): copied with cp -a (never modified), or linked if it is stamped
#
#   phone370_prepare DATA     DATA = the run's phone (or an empty dir); the local KVS (Aska.xml:
#                             version, crc, device UUID) is deleted: the 3.7.0 client makes its own.
#                             Copy the client save into DATA/data/shared_prefs/ afterwards.
#   phone370_client_save DIR  installs the committed client save (data/saves/client/Game.xml) as
#                             DIR/Game.xml (DIR = the phone's data/shared_prefs) with
#                             BAS:DownloadEpisodeFlag 0: no episode pack on the client's books, so a
#                             session is the same whether the phone carries the packs or not, and
#                             doesn't fetch them (the save's 7, Episodes 1-3, would download ~705 MB
#                             at the first data phase on a phone without them, and make ミッション open
#                             Episode 2's map). SOA_EPISODE_PACKS=1 keeps the save's flag.
#   phone370_title FIFO LOG   wait for the title (phase 1 + 3 s)
#   phone370_login FIFO LOG [SHOTDIR]
#                             TAP TO START until Login is sent, then phone370_data until home
#                             (phase 4). Exit 1 on a step that isn't reached.
#   phone370_episode_list FIFO LOG [X [Y]]
#                             home's ミッション (X:Y, default 270:1085) -> the episode list (phase 8).
#                             When the last episode played has its data on the phone (the
#                             committed client save: Episode 2, and the packs come with the first
#                             data phase), ミッション opens that episode's map instead (phase 5):
#                             Ep選択 (655:485 on a world map, else 655:375: Episode 1's planet
#                             select) -> the list. Exit status 1 when the list isn't reached.
#   phone370_data FIFO LOG [SHOTDIR [UNTIL]]
#                             after a Login: the data check (SOA_PHONE) or the download with its
#                             dialogs, until the log matches UNTIL (default home, 'port_debug:
#                             phase 4 '; a new player: 'port_debug: phase 3 ', the opening scene).
#
# phone370_prepare also takes the script's game slot (control/soaslot.sh: the machine-wide pool;
# held until the script exits, so parallel sessions queue instead of overloading the machine).
# Needs control/soactl.py and control/flowctl.py (run from the repo root).
. scripts/shared-phone.sh
shared_phone_resolve "$PWD"
. control/soaslot.sh

phone370_prepare() {
    soaslot_take "${0##*/}"
    rm -rf "${1:?}"
    if [ -n "${SOA_PHONE:-}" ]; then
        shared_phone_link "$SOA_PHONE" "$1" || { echo "FAIL: preparing the phone $1 from SOA_PHONE=$SOA_PHONE"; exit 1; }
    else
        mkdir -p "$1"
    fi
    mkdir -p "$1/data/shared_prefs"
    rm -f "$1/data/shared_prefs/Aska.xml"
}

phone370_title() {
    python3 control/flowctl.py wait-log "$2" 'port_debug: phase 1 ' 300 || { echo "FAIL: no title (phase 1)"; exit 1; }
    python3 control/soactl.py --timeout 400 "$1" wait:3000
}

phone370_login() {
    _f=$1; _l=$2; _s=${3:-}
    # TAP TO START -> Login (a tap during the title's fade-in is sometimes dropped).
    python3 control/flowctl.py tap-until "$_f" "$_l" 'request Login ' 90 10 6 -- tap:364:1000 || { echo "FAIL: no Login after TAP TO START"; exit 1; }
    phone370_data "$_f" "$_l" "$_s"
}

phone370_data() {
    _f=$1; _l=$2; _s=${3:-}; _u=${4:-'port_debug: phase 4 '}
    if [ -n "${SOA_PHONE:-}" ]; then
        python3 control/flowctl.py wait-log "$_l" 'version_latest_Bulk' 120 || { echo "FAIL: no data check"; exit 1; }
        if ! python3 control/flowctl.py wait-log "$_l" "$_u" 60 > /dev/null 2>&1; then
            # A download dialog after all: data the phone lacks, e.g. the master the server edited
            # for this run's options (--restore-tower's banner rows: 35 MB). ダウンロード (515:800),
            # then 完了 (364:790); both spots are empty on the other dialog.
            [ -n "$_s" ] && python3 control/soactl.py --timeout 400 "$_f" shot:"$_s/00-download-dialog.png"
            python3 control/flowctl.py tap-until "$_f" "$_l" "$_u" 300 10 30 -- tap:515:800 wait:3000 tap:364:790 ||
                { echo "FAIL: no '$_u' after the data check"; exit 1; }
        fi
    else
        # CPhase_DataDownload (phase 19): the episode data is missing (決定 364:1043), then the
        # download dialog (ダウンロード 515:800), the bundles, 完了 (364:790).
        python3 control/flowctl.py wait-log "$_l" 'port_debug: phase 19 ' 120 || { echo "FAIL: no data download phase"; exit 1; }
        python3 control/flowctl.py tap-until "$_f" "$_l" 'version_latest_Bulk' 120 8 10 -- wait:3000 tap:364:1043 || { echo "FAIL: no manifest check"; exit 1; }
        python3 control/flowctl.py tap-until "$_f" "$_l" 'I/http: GET .*/Android/B/' 120 10 10 -- tap:515:800 || { echo "FAIL: the download didn't start"; exit 1; }
        _last=-1; _same=0
        while [ $_same -lt 30 ]; do  # the downloads stop: no new GET for 30 s
            _n=$(grep -c 'I/http: GET' "$_l" || true)
            if [ "$_n" = "$_last" ]; then _same=$((_same + 1)); else _same=0; _last=$_n; fi
            sleep 1
        done
        [ -n "$_s" ] && python3 control/soactl.py --timeout 400 "$_f" shot:"$_s/00-download-done.png"
        python3 control/flowctl.py tap-until "$_f" "$_l" "$_u" 120 8 10 -- tap:364:790 || { echo "FAIL: no '$_u' after the download"; exit 1; }
    fi
}

phone370_episode_list() {
    _f=$1; _l=$2; _x=${3:-270}; _y=${4:-1085}
    python3 control/flowctl.py tap-until "$_f" "$_l" 'port_debug: phase (5|8) ' 60 20 3 -- tap:$_x:$_y || return 1
    [ "$(grep -o 'port_debug: phase [58] ' "$_l" | tail -n 1)" = 'port_debug: phase 8 ' ] && return 0
    # phase 5: the last episode's map. Ep選択 is at 655:485 on a world map (Episodes 2, 3), at
    # 655:375 on Episode 1's planet select (where 655:485 is on the planet: harmless). The log
    # can't tell them apart in time (the server's lines are buffered, the phase lines aren't).
    python3 control/soactl.py --timeout 400 "$_f" wait:5000 > /dev/null
    python3 control/flowctl.py tap-until "$_f" "$_l" 'port_debug: phase 8 ' 12 12 1 -- tap:655:485 > /dev/null 2>&1 ||
        python3 control/flowctl.py tap-until "$_f" "$_l" 'port_debug: phase 8 ' 60 20 3 -- tap:655:375
}

phone370_client_save() {
    mkdir -p "$1"
    if [ "${SOA_EPISODE_PACKS:-0}" = 1 ]; then
        cp data/saves/client/Game.xml "$1/Game.xml"
    else
        .venv/bin/python -m soa_save set --type u32 data/saves/client/Game.xml BAS:DownloadEpisodeFlag 0 -o "$1/Game.xml" > /dev/null
    fi
}
