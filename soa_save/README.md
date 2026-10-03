# soa_save: save editor and event-script decoder

Python library and CLI for the saves of *STAR OCEAN: anamnesis* and for its event scripts. It works on the **offline game** (3.8.0), the build still installed on phones since the service ended: its saves, the master DB in its XAPK (`apk/`, local, not in git) and the scripts in its install-time asset pack. The desktop port (`port/`) runs the 3.7.0 client and doesn't need any of it. Setup: `README.md` "Setup".

## Editing a save

Saves live on the device at `/data/data/com.square_enix.android_googleplay.StarOceanj/shared_prefs/{Aska,Game}.xml`.

```sh
.venv/bin/python -m soa_save dump Game.xml                 # decrypted key/value listing (--json for JSON)
.venv/bin/python -m soa_save set Game.xml player_fol 9999999   # in place, keeps Game.xml.bak
.venv/bin/python -m soa_save roster Game.xml               # party with Japanese + English names
.venv/bin/python -m soa_save unlock-all Game.xml -o Game_all.xml --player-id AAAAAAAAAA
```

`saves/Game_all_characters.xml` is a ready-made example: 276 characters (every playable variant whose model ships offline, at top rarity) with the generic player ID `AAAAAAAAAA`.

`roster` and `unlock-all` read the decrypted master database at `data/basmaster-3.8.0.sqlite3` (local, not in git; named for the game version it came from). If it is missing, they decrypt it again from the XAPK.

### Waydroid

To use Waydroid, you need:

- ARM translation (`libndk_translation`)
- this machine's adb key added to `~/.local/share/waydroid/data/misc/adb/adb_keys`

Install all the splits together:

```sh
cd work/extracted/xapk
adb install-multiple -r com.square_enix.android_googleplay.StarOceanj.apk config.arm64_v8a.apk \
    config.ja.apk config.en.apk config.xxxhdpi.apk assetinstalltime.apk
```

Then stop the game and push a save (this backs up the device's prefs to `samples/device_backup/`):

```sh
adb shell am force-stop com.square_enix.android_googleplay.StarOceanj
sudo tools/push_save.sh Game_all.xml
```

## Decoding event scripts

The story/event scripts (`Script/*.msgp`) and their dialogue (`Scenario/TS_*.msgp`) are ADLD-wrapped MessagePack in the install-time asset pack. `soa_save.script` decodes them:

```sh
.venv/bin/python -m soa_save.script extract -o work/scripts   # all 486 files from the XAPK -> .json + readable .txt
.venv/bin/python -m soa_save.script list Script/1000_010.msgp # readable listing: command names, dialogue, speakers, menus
.venv/bin/python -m soa_save.script json Script/1000_010.msgp # decoded MessagePack as JSON
.venv/bin/python -m soa_save.script decrypt FILE... -o OUT    # strip ADLD only (any asset; name taken from the path)
.venv/bin/python -m soa_save.script encrypt plain.msgp --name Script/1000_010.msgp -o 1000_010.msgp
```

`extract --format raw,json,txt` picks the outputs. The key depends on the asset's path under `assetpack/` (or `builtin_data/`); pass `--name` when a file's location doesn't show it. `encrypt` produces byte-identical files, so edited scripts can go back into the pack.
