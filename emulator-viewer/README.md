# emulator-viewer/: the offline 3.8.0 client, unmodified (`soa-viewer`)

`soa-viewer` runs STAR OCEAN: anamnesis **3.8.0**, the stand-alone build Square Enix shipped when the service ended, exactly as shipped: the `libSOA.so` of the 3.8.0 XAPK under the JIT host runtime (`runtime/`), pure JIT, with the XAPK's own assets. No native replacements, no restore code, no server, nothing from `port/`. The game code is not patched at all; only the platform layer under it is emulated, and the runtime already has all of it but one network answer (below).

It is the 3.8.0 counterpart of `emulator/` (`soa-emu`, the 3.7.0 online client) and a reference for the port (`port/`, `soa`), which runs the 3.7.0 online client's library (another build than this one) with native code and, with the in-process server, the restored online game. Use it to see what the offline build itself does on a screen, or to compare the port against it.

## Building

```sh
scripts/build.sh --target soa-viewer             # from the repository root (README.md "Building"): build/emulator-viewer/soa-viewer
```

`emulator-viewer/CMakeLists.txt` is a subdirectory of the repository's build, added after `runtime/` when `SOA_BUILD_VIEWER` is on (the default); the shared settings and the dependencies (`cmake/deps.cmake`: vcpkg, dynarmic) come from the root `CMakeLists.txt`. `-DSOA_BUILD_PORT=OFF -DSOA_BUILD_SERVER=OFF -DSOA_BUILD_EMULATOR=OFF -DSOA_BUILD_WEBVIEW=OFF -DSOA_BUILD_TOOLS=OFF` builds only `common/`, the runtime and the viewer (the web view and the host tools are on by default). It links the runtime (`soaruntime`, whole archive, so its own extension registers) and the desktop host loop (`soaruntime_app`), like `soa-emu`.

## Running

```sh
scripts/run-viewer-380.sh                          # a window; data in ~/.local/share/soa-viewer-380
build/emulator-viewer/soa-viewer --headless --control /tmp/viewer.fifo     # finds apk/*.xapk
build/emulator-viewer/soa-viewer --xapk apk/STAR+OCEAN+-anamnesis-_3.8.0_APKPure.xapk
control/soactl.py /tmp/viewer.fifo tap:364:1000 wait:3000 shot:/tmp/viewer.png
```

`scripts/run-viewer-380.sh` (README.md "Running") checks the game files (the XAPK in `apk/`, read in place, else the unpacked `work/extracted/xapk`), starts `soa-viewer` and stops it on exit or Ctrl-C; it starts no server, since the viewer needs none ("Network"). `--home DIR` moves the data; other options go to `soa-viewer`.

`soa-viewer --help` lists the options (CLI11, `src/cli.cpp`; the ones it shares with `soa` are defined once: `runtime/include/soaruntime/app/cli.h`, `common/include/soa/cli.h`). A value-taking option given twice: the last one wins (`--apk`, `--shot`, `--do` collect); an error prints one line and exits 2.

| Option | Meaning |
|---|---|
| `--xapk FILE` | The 3.8.0 XAPK as downloaded, read in place: the APKs inside it are zip archives stored uncompressed, so the base APK (`com.square_enix.android_googleplay.StarOceanj.apk`) and the install-time asset pack (`assetinstalltime.apk`) are indexed where they lie in the XAPK (`common/include/soa/zip.h` `open_member`), and `config.arm64_v8a.apk` gives the library. An APK the XAPK stores deflated would be extracted once into `DATA/xapk-cache/`. `assetfastfollow.apk` / `assetondemand1.apk` (or `split_*.apk`), when the XAPK has them, are installed as Play Asset Delivery packs (BGM and talk-scene sounds; the APKPure XAPK lacks them). Default: the first `*.xapk` holding the app beside the executable, in its `game/` folder, or in `<repo>/apk/` (a git worktree: also the main checkout's `apk/`). |
| `--apk-dir DIR` | The XAPK unpacked (`tools/extract.sh`: `work/extracted/xapk`), the same files as separate APKs; the default when no XAPK is found. With an XAPK (`--xapk` or found), an APK the XAPK lacks is read from DIR instead (e.g. `assetfastfollow.apk` / `assetondemand1.apk`, which the APKPure XAPK doesn't carry). Default: the first of the executable's folder, its `game/` folder (all a release build has without `--repo`) and `<repo>/work/extracted/xapk` that holds the APKs (beside an XAPK: any of them; alone: the base APK). |
| `--apk FILE` | Also read assets from FILE, after the XAPK's. Repeatable; a later one wins. |
| `--download PATH` (= `--download-dir PATH`) | Serve `builtin_data/` assets missing from the APKs from PATH, the online game's 3.7.0 download: `work/SOA-3.7.0-canonical-data.zip` (read in place) or an extracted folder: the same option as `soa` and `soa-emu` (`common/include/soa/cli.h`). Off by default. It doesn't fill in the missing Play Asset Delivery packs (`assetfastfollow` / `assetondemand1`), which aren't `builtin_data/`. |
| `--download-prefer` | With `--download`: DIR wins over the APKs (as `soa` and `soa-emu`). |
| `--lib PATH` | The client library. Default: `lib/arm64-v8a/libSOA.so` from `config.arm64_v8a.apk` (in the XAPK or DIR), extracted into the data dir as the package manager installs it, again when the entry's CRC-32 or size differs from the copy's stamp (`DATA/libSOA.so.src`). |
| `--data DIR` | The emulated phone's storage: the save (`data/shared_prefs/`), the extracted library, asset packs, `xapk-cache/`. Default `~/.local/share/soa-viewer-380` (Windows: `%LOCALAPPDATA%\soa\viewer-380`; `common/include/soa/paths.h`), beside the port's `~/.local/share/soa-linux-370`. Never the port's data dir: the port's save and cached library are its own. |
| (window title) | `[EMULATED] STAR OCEAN -anamnesis- 3.8.0 offline client (soa-viewer)`. |
| (app version) | `3.8.0`, the XAPK's versionName (what the client sends in NoLoginStart). |
| `--repo DIR` | The source checkout, for the defaults (`apk/`, `work/extracted/xapk`). Default: found upwards from the executable; in a git worktree, files it lacks are looked up in the main checkout `work/` links to. |
| `--guest-cpus N` / `host` | CPUs the game sees. Default 8. |
| `--headless` / `--windowed` | Don't show the window. It still renders: screenshots and the control FIFO work. `--windowed` (the default) undoes an earlier `--headless`, as in `soa`. |
| `--size WxH`, `--landscape`, `--render-size S`, `--fullscreen` | Window and screen size, as in `soa`. The game picks its own back-buffer size (an 810x1440 screen gives `default framebuffer emulated at 720x1280` in the log), scaled to the window; the port's sharper rendering (its default) is a native, which the viewer doesn't have. |
| `--shot S:PATH`, `--do S:ACTION`, `--control FIFO` | Scripted input and screenshots, as in `soa`: `tap`, `drag`, `wheel`, `back`, `text`, `shot`, `resize`, `fullscreen`, `quit` (`control/soactl.py`). `soa`'s `phase:` / `call:` debug commands need natives and don't exist here. |
| `-v` / `-vv` | Verbose / trace logging. |

Reading the XAPK costs nothing measurable over the unpacked tree (2026-10-04, page cache warm): its 23-entry directory plus the two APKs' directories are indexed in about 0.015 s either way (`game assets indexed from ... in` in the log), libSOA.so is extracted on the first run only, and a start-to-quit run takes 0.82-1.16 s for both, as before minizip-ng. Time to the title in `viewer_boot.sh`: 36 s from the XAPK, 32 s from the tree, run side by side under the same load; Windows 40 s from the XAPK.

Settings are flags only (a `SOA_*` variable that was a setting prints one warning naming its flag; `docs/environment.md`). The runtime's diagnostic switches work too (`SOA_TRACE`, `SOA_PROFILE` / `SOA_COVERAGE`, `SOA_WATCHDOG`, ...): [`runtime/README.md`](../runtime/README.md) "Environment".

## What is viewer-specific

Almost nothing: the runtime was built for exactly this library. Its HLE covers the 3.8.0 import list, and its Java side (`runtime/src/jni/java_android.cpp`, `java_playcore.cpp`) answers every method 3.8.0 calls, including Google's Play Core asset-pack API. So the viewer is a `main.cpp` (the device: app version, data dir, APK list, asset packs, window title) plus one network answer. Compared with `soa-emu`, it needs no extra imports (3.7.0's `fmod`), no extra Java methods (3.8.0 stubbed Play Games, location and notifications itself; docs/history/libsoa-3.7.0-vs-3.8.0.md 2.12), no HTTP client (3.8.0's web pages are local) and no native patch (see "Dates").

### Network (`net_offline.cpp`)
3.8.0 sends one request: the title's `NoLoginStart`, over raw TCP (GameRPC) to `production-game.so-ana.com:443` (docs/history/libsoa-3.7.0-vs-3.8.0.md 2.1). Both possible answers were tried (2026-10-01):

- **No answer** (the shipped behaviour): the name doesn't resolve any more, the request fails, and the client goes on without an error dialog. `CPhase_Server`'s error handler ends the phase quietly once `service_stop_day` has passed, and 3.8.0's clock stands at that moment. A fresh phone then gets the stand-alone new player: the terms prompt, a data check, and home as アナムネシス, rank 1, stamina 10/10, 0 stones, with the three starter roles.
- **An answer from soa-server**, through `soa-emu`'s redirect (`emulator/src/net_370.cpp`, now `platform370/src/net_370.cpp`, compiled into a throwaway viewer build): `NoLoginStartRes` is applied, and home shows a mixture of the server's 3.7.0 player and the offline one: the server's name and 300,000 stones, with rank 1 and stamina 134/1. The offline build doesn't expect an answer, and its save summary only partly overrides it (docs/client-changes.md: "the offline client shows the summary cached in its save").

So the viewer runs **without a server**, as shipped, and soa-server has nothing to add for 3.8.0. To keep that deterministic, `net_offline.cpp` answers every lookup of `so-ana.com` or a name under it with "not found" (Bionic `EAI_NONAME`), without a DNS query. The client then never reaches whoever holds the domain later, or a soa-server on this machine. Other lookups go to the runtime's thunks unchanged. The log shows `getaddrinfo(production-game.so-ana.com): the service is gone; not found (no DNS query)` once per NoLoginStart attempt (twice per title). docs/client-changes.md "Emulator viewer (3.8.0)" lists it.

### Dates
3.8.0 freezes its own game clock: `CTimeUtility::NowTime` / `BAS::LocalTime(true)` return `master_global.service_stop_day` (2021/06/24 14:30:00) when the row is there, as in the APK's master (docs/history/libsoa-3.7.0-vs-3.8.0.md 2.4). Its title lost 3.7.0's service-end notice. The viewer runs on the host's real date with no clock option and no patch, and nothing checks the date in a blocking way. Verified 2026-10-01: title, new player, home, every menu and a story replay work (`viewer_session.sh`).

### Web views
The terms (`利用規約`), copyright and credits pages are local HTML files in the base APK (`file:///android_asset/kiyaku.html`, `copyright_android.html`, ...; `master_global.local_html_*`). The runtime has no web view (`ShowWebView ... not supported` in the log), so the game shows its web-view frame with an empty page and a working 閉じる. The port shows these pages as text only with the in-process server (a game-code wrapper, which the viewer doesn't have).

### Asset packs
The install-time pack (`assetinstalltime.apk`) is indexed like an APK (in place inside the XAPK with `--xapk`). The game also asks Play Core for `assetfastfollow` (BGM) and `assetondemand1` (talk-scene sounds); without their APKs the runtime answers "no such pack" (`W/playcore: fetch(...)`), and those sounds are silent, as on a phone that never fetched them. Put `assetfastfollow.apk` / `assetondemand1.apk` into the `--apk-dir` directory (alone or beside `--xapk`: APKs the XAPK lacks are read from it; in a package, `game/` beside the XAPK does), or into the XAPK, to install them.

## Status (2026-10-01)
Everything the offline build offers works:
- the title (Ver.3.8.0, ゲームサイト / おすすめゲーム buttons);
- the new-player terms prompt with its terms page;
- the data check;
- home (`home_sa`): the favourite character in 2D, or in 3D after 2D/3D変更, and Coro's lines;
- interactive mode (会話モード) and the favourite list (お気に入り変更, the three starter roles);
- the character book: every master role, each detail, status, talents and skills at ★6;
- missions: the episode select, the scenario library (main and sub stories, chapters) and story replay with its movies;
- the other menu: settings (graphics, sound, events, reset), copyright, credits, terms, and back to title.

The game runs at 60 fps; RSS is about 1.3 GB. What is missing comes from the platform: the empty web-view pages, the sounds of the two absent asset packs, and audio on a machine without a sound device.

## Checks

| Script | What it checks |
|---|---|
| `emulator-viewer/scripts/viewer_boot.sh [bin] [out]` | Headless, on a fresh phone: the title, NoLoginStart's lookup answered "not found" with no error dialog, TAP TO START → the terms prompt. About 35 s. |
| `emulator-viewer/scripts/viewer_session.sh [bin] [out]` | Headless, on a fresh phone: the whole offline game through taps and screenshots: title, terms page, home, the character book (detail, status), interactive mode (favourites, 3D), the other menu (copyright, settings: graphics, sound), missions (episodes, the scenario library, a story skipped through its movie), back to title and in again with no terms prompt. Each step waits until the screen matches its reference. About 5 min. |

Both print PASS / FAIL per milestone and overall (exit 0 / 1), kill only the `soa-viewer` they started, and keep their log and screenshots in the out dir (the phone's data is deleted unless `KEEP_DATA=1`). The references are `scripts/ref/*.png` (182x324, compared by RMSE ≤ 0.08 as `port/scripts/smoke.py` does; animated screens compare a crop). `VIEWER_RECORD=1` records missing references: delete one to re-record it, and check it by eye.
