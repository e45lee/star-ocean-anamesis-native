#!/bin/sh
# Unpack the XAPK from apk/ into work/extracted (split APKs, libSOA.so, base-APK master DB/params).
# For tools/decomp.sh --v380 and the save editor's master DB (soa_save); optional for the viewer,
# which reads the XAPK in place (soa-viewer --xapk; --apk-dir work/extracted/xapk still works). The
# port doesn't need it (it reads the 3.7.0 APK in place).
set -eu
. "$(dirname "$0")/common.sh"
XAPK=$(ls "$REPO"/apk/*.xapk | head -n1)
E=$WORK/extracted
mkdir -p "$E"
unzip -o -q "$XAPK" -d "$E/xapk"
unzip -o -q "$E/xapk/$PKG.apk" -d "$E/$PKG"
unzip -o -q "$E/xapk/config.arm64_v8a.apk" -d "$E/config.arm64_v8a"
unzip -o -q "$E/xapk/$PKG.apk" 'assets/builtin_data/sqlite/*' 'assets/builtin_data/Parameter/*' -d "$E/base_assets"
echo "extracted to $E"
