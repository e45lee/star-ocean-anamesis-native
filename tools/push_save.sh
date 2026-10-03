#!/bin/sh
# Copy a Game.xml into the Waydroid install of the game, backing up the device's prefs first.
# Run with sudo (the app's data dir is owned by its Android uid). Stop the game before running:
#   adb shell am force-stop com.square_enix.android_googleplay.StarOceanj
#   sudo tools/push_save.sh samples/Game_all_characters.xml
set -eu
. "$(dirname "$0")/common.sh"
SRC=$(realpath "$1")
USER_NAME=${SUDO_USER:-$(id -un)}
USER_HOME=$(getent passwd "$USER_NAME" | cut -d: -f6)
PREFS=$USER_HOME/.local/share/waydroid/data/data/$PKG/shared_prefs
BACKUP=$REPO/samples/device_backup/$(date +%Y%m%d-%H%M%S)

[ -f "$PREFS/Game.xml" ] || { echo "no $PREFS/Game.xml (launch the game once first)"; ls -la "$PREFS"; exit 1; }
mkdir -p "$BACKUP"
cp -a "$PREFS/." "$BACKUP/"
chown -R "$USER_NAME:" "$BACKUP"
echo "backed up device prefs to $BACKUP"
# Overwrite in place so the file keeps its owner, mode and SELinux label.
cat "$SRC" > "$PREFS/Game.xml"
ls -laZ "$PREFS"
