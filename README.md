# Star Ocean: Anamnesis reverse engineering and save editor

Tools and notes for *STAR OCEAN: anamnesis* (JP, `com.square_enix.android_googleplay.StarOceanj`), whose Japanese service closed in June 2021: a desktop port of the last online client (3.7.0) with a local game server, the same client unmodified in an emulator, a viewer for the offline build (`emulator-viewer/`), and a save editor.

- `docs/notes.md`: the reverse-engineered formats:
  - the save files (`Aska.xml`, `Game.xml`: ChaCha20-encrypted SharedPreferences)
  - the `ADLD` asset container
  - the AES-encrypted master database
  - how IDs are derived (`CHash32`)
- `docs/online-server.md`: how the online game server (shut down in 2021) worked, reconstructed from the client: hosts, the TCP RPC protocol and its encryption, the SQEX BRIDGE session handshake, asset delivery, multiplayer and payments.
- `docs/history/`: finished plans and comparisons, e.g. [`docs/history/libsoa-3.7.0-vs-3.8.0.md`](docs/history/libsoa-3.7.0-vs-3.8.0.md), what the offline build changed against 3.7.0.
- `docs/environment.md`: the environment rule (settings are command-line flags; the environment holds diagnostics and test switches only), the removed `SOA_*` settings and their flags, and the variables the programs and scripts still read.
- `docs/home3d.md`: the 3D home character: when the client shows a model or a 2D illustration (`master_person.home3d_disable`; the NieR:Automata collab is 2D only), the Home3D parameters, motions, lines and voices; `--home3d-all`.
- `docs/api.md`: every API the client calls, with the wire format of each request and reply. `docs/ason.md`: ASON, the engine's MessagePack (reply bodies, request payloads). `docs/server-rules.md`: the game rules the port's local server applies. `docs/unimplemented-apis.md`: the APIs it doesn't implement yet (current limitations) and the plan for them.
- `soa_save/`: Python library and CLI for reading, editing and writing saves, and for decoding the event scripts ([`soa_save/README.md`](soa_save/README.md)).
- `tools/`: helpers used for the reverse engineering: Ghidra headless scripts, ELF/PLT resolver, xref/caller scanners, unicorn emulator harness.
- `apk/`: the 3.7.0 APK, and the offline build's XAPK for the viewer (`emulator-viewer/`) and the save editor (the 3.7.0 APK is in git; the XAPK, over GitHub's 100 MB limit, is local only: "Game files").
- `standin-assets/`: made-up **stand-in** images (marked "STAND-IN") for assets the online server had deleted, e.g. lost gacha banners; `tools/make_standin_banners.py` makes them, and the CDN of `soa-server` and of the port's in-process server serves them (`--standin-assets DIR|off`).

## Setup

```sh
# the game files aren't in git: put them in place first ("Game files" below)
python3 -m venv .venv && .venv/bin/pip install -r requirements.txt
tools/extract.sh          # unpack the XAPK into work/extracted: decomp.sh --v380 and Waydroid; optional for the viewer (emulator-viewer/), which reads the XAPK in place
```

### Build dependencies

The C++ dependencies come from **vcpkg** in manifest mode (`vcpkg.json`, pinned by its
`builtin-baseline`): Boost (headers, for dynarmic), zlib, SQLite, zstd, libogg, libvorbis, SDL2 (X11 and
Wayland video), OpenSSL, FreeType, litehtml, stb (PNG writing, the web view), pugixml (SharedPreferences
XML: `common/`'s `soa_codec`), minizip-ng (zlib only: the ZIP reader `soa_zip`, `common/include/soa/zip.h`)
and the Khronos EGL/GLES headers. All are built from source by vcpkg, as static
libraries (`cmake/vcpkg-triplets/x64-linux.cmake`: release only), on the first configure, into
`build/vcpkg_installed/`; vcpkg's binary cache (`~/.cache/vcpkg/archives`) makes later configures,
other build dirs and worktrees fast. Three libraries come from CMake
`FetchContent` instead, pinned by URL and SHA-256, into `build/_deps/` (`cmake/deps.cmake`):
- **dynarmic** (the ARM64 JIT) at `lioncash/dynarmic` commit `a41c380`;
- **IJG libjpeg 9b**, the game's version, built static by `cmake/libjpeg9/` (target `soa::jpeg9`):
  vcpkg has only libjpeg-turbo, which isn't bit-exact with IJG's. Used by the `lib_jpeg` natives
  (`port/src/native/lib_jpeg/`) and `tools/aif2png`;
- **zstd 1.3.4**, the game's version, built static by `cmake/zstd134/` (target `soa::zstd134`): the
  `lib_zstd` natives (`port/src/native/lib_zstd/`) match the game's results byte for byte, errors
  included, which vcpkg's zstd 1.5 doesn't (vcpkg's stays for `tools/aif2png`).

**SQLite is pinned to 3.45.1** (`overrides` in `vcpkg.json`) and built with the compile options of
Ubuntu 24.04's `libsqlite3` (the triplet file), the library the server linked before vcpkg. The
server's served master is a `VACUUM`ed copy whose bytes depend on both (the version number in the
header; `SQLITE_SECURE_DELETE` zeroes freed space), its SHA-1 feeds the CDN's version ids, and a
pre-downloaded phone (`SOA_PHONE`) skips the data check only while those ids match. Changing the
SQLite version or options therefore makes every saved phone download the data again.

**vcpkg itself:** `$VCPKG_ROOT` if set, else `.vcpkg/` in the repository (untracked):
`scripts/vcpkg-bootstrap.sh` clones `github.com/microsoft/vcpkg` there at the `builtin-baseline`
commit and runs its bootstrap (`scripts/build.sh` does this). The root `CMakeLists.txt` finds the
toolchain file from the same places, so a plain `cmake -S . -B build` works once vcpkg is there.
Worktrees made by `port/scripts/agent-worktree.sh` share the main checkout's `.vcpkg` by symlink.

**Linux prerequisites** vcpkg can't replace (Ubuntu 24.04 names; CMake 3.28 or newer, which 24.04 ships):

```sh
# build tools (vcpkg needs curl, zip, unzip, tar, git and pkg-config (pkgconf on 24.04); it downloads its own ninja and CMake if needed)
sudo apt install build-essential cmake git curl zip unzip tar pkg-config perl python3 autoconf automake libtool
# nasm: the x86-64 assembly of vcpkg's ffmpeg port (the movie player's H.264 / AAC decoders); vcpkg fetches it only on Windows hosts
sudo apt install nasm
# optional, faster builds: scripts/build.sh configures with Ninja and compiles through ccache when they are installed
sudo apt install ninja-build ccache
# SDL2's X11 and Wayland video and PulseAudio audio (vcpkg builds SDL2 against the system's headers; it loads the
# X11, Wayland and PulseAudio libraries at run time, so either window system works; libdecor-0-dev is optional:
# window decorations under Wayland compositors that want client-side ones)
sudo apt install libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxss-dev libxfixes-dev libpulse-dev
sudo apt install libwayland-dev libxkbcommon-dev libegl-dev libdecor-0-dev
# EGL / GLES 2 at run time (Mesa): SDL creates the GLES contexts through EGL, on X11 or Wayland
sudo apt install libegl1 libgles2 libegl-mesa0 libgl1-mesa-dri
# a font with Japanese glyphs for the text box shown while the game asks for text (a name): any one of
# fonts-ipaexfont-gothic / fonts-noto-cjk / fonts-droid-fallback, or --font PATH; fontconfig's
# fc-match finds others. Without one the text shows in the window title only.
sudo apt install fonts-ipaexfont-gothic fontconfig
```

**Sound:** vcpkg's SDL2 here has the PulseAudio backend (plus sndio/OSS), not ALSA or PipeWire
(the system SDL2 had both). PipeWire desktops serve it through `pipewire-pulse`; a machine with
neither runs silently (the port's null sink). Adding sdl2's `alsa` feature to `vcpkg.json` builds
vcpkg's alsa-lib, which also needs `autoconf-archive` from apt.

## Building

The C++ parts share one CMake build, rooted at `CMakeLists.txt`:

| Part | What | Output |
|---|---|---|
| `runtime/` | the JIT host runtime: ELF loader, dynarmic CPU, Android HLE, JVM, host loop (`runtime/README.md`) | `build/runtime/soaruntime_tests` |
| `server/` | the local game server library and its standalone binary (`server/README.md`) | `build/server/soa-server` |
| `port/` | the desktop port of the 3.7.0 client (`port/README.md`) | `build/port/soa` |
| `platform370/` | the 3.7.0 platform layer: Java answers, `fmod`, device clock, the `service_stop_day` patch, network glue (`platform370/README.md`); used by `soa-emu` | `build/platform370/libsoaplatform370.a` |
| `emulator/` | the unmodified 3.7.0 online client (`emulator/README.md`) | `build/emulator/soa-emu` |
| `emulator-viewer/` | the unmodified offline 3.8.0 client (`emulator-viewer/README.md`) | `build/emulator-viewer/soa-viewer` |

```sh
scripts/build.sh                    # vcpkg (bootstrapped into .vcpkg/ if missing), configure, build everything
# or by hand, once vcpkg is there (scripts/vcpkg-bootstrap.sh, or $VCPKG_ROOT):
cmake -S . -B build                 # RelWithDebInfo unless -DCMAKE_BUILD_TYPE=...; the first one builds the vcpkg ports
cmake --build build -j8             # everything
cmake --build build -j8 --target soa        # one part: soa, soa-server, soa-emu, soa-viewer, soaruntime_tests or aif2png
```

The root `CMakeLists.txt` picks vcpkg's toolchain file (`$VCPKG_ROOT`, else `.vcpkg/`; an explicit
`-DCMAKE_TOOLCHAIN_FILE` wins), holds the shared settings (C++20, the build type), includes
`cmake/deps.cmake` (the dependencies' imported targets; "Build dependencies" above), then adds
`runtime/`, `platform370/`, `server/`, `port/`, `emulator/`, `emulator-viewer/` and `tools/aif2png`.
A build dir configured before vcpkg (with `deps/` and `third_party/`, now retired) can't switch
toolchains: delete it and configure again. vcpkg builds its ports with `VCPKG_MAX_CONCURRENCY` jobs
(8 unless set). Parts can be left out at configure
time with `-DSOA_BUILD_PORT=OFF`, `-DSOA_BUILD_EMULATOR=OFF`, `-DSOA_BUILD_VIEWER=OFF`,
`-DSOA_BUILD_SERVER=OFF` or `-DSOA_BUILD_PLATFORM370=OFF` (the port needs the server library, so
`SOA_BUILD_SERVER=OFF` needs `SOA_BUILD_PORT=OFF` too; the emulator needs platform370, so
`SOA_BUILD_PLATFORM370=OFF` needs `SOA_BUILD_EMULATOR=OFF`).

### Windows

A cross build from Linux (or WSL) with **llvm-mingw** (clang, libc++, the UCRT) into `build-win/`
(`port/PLAN.md` 5b, "W"): every part, as `.exe` files (`soa.exe`, `soa-server.exe`, `soa-emu.exe`,
`soa-viewer.exe`, the tests and tools). Checked on Windows (from WSL, through interop):
`soa-server.exe --selftest`, `soaruntime_tests.exe`, `soa.exe --selftest`, and the gate tests
`win:battle-gacha` (the port's restore session, in process), `win:seeded` (`soa-emu.exe` against
`soa-server.exe`: login, battle, gacha), `win:viewer-boot` and `win:shard-login` (the tests/diff
shard on the three Windows targets) (`port/PLAN.md` 5b, "As built").

```sh
# once: llvm-mingw (any recent ucrt ubuntu-x86_64 release of github.com/mstorsjo/llvm-mingw)
curl -LO https://github.com/mstorsjo/llvm-mingw/releases/download/20260922/llvm-mingw-20260922-ucrt-ubuntu-22.04-x86_64.tar.xz
tar -C ~/tools -xf llvm-mingw-20260922-ucrt-ubuntu-22.04-x86_64.tar.xz
ln -sfn ~/tools/llvm-mingw-20260922-ucrt-ubuntu-22.04-x86_64 ~/tools/llvm-mingw   # or set SOA_LLVM_MINGW
scripts/build.sh --windows                              # build-win/: everything
scripts/build.sh --windows --target soa-server          # one part
```

- `--windows` configures `build-win/` with vcpkg's toolchain chainloading
  `cmake/toolchains/llvm-mingw-x64.cmake`, the triplet `x64-mingw-static`
  (`cmake/vcpkg-triplets/x64-mingw-static.cmake`: static, release only, the same sqlite3 options as
  Linux so the served master and the CDN ids don't depend on the platform) and the vcpkg feature
  `angle` (ANGLE: EGL / GLES on Windows). The first configure builds every port for MinGW (about an
  hour, then cached; a change to the triplet file rebuilds them all). The `.exe` files are static:
  only Windows' own DLLs.
- In a git worktree set `VCPKG_ROOT` to the main checkout's `.vcpkg` (as for `build/`), or
  `scripts/vcpkg-bootstrap.sh` clones another vcpkg.
- What our code needs from Windows that MinGW lacks is in `common/` (`soa_compat`):
  `common/win32/posix_compat.h` is force-included into the server's and the runtime's sources (the
  POSIX spellings: `mkdir` with a mode, `realpath`, `rename` that replaces, `pread`, `strptime`,
  ...), `soa/sock.h` the host sockets. The runtime's guest-facing differences (bionic is LP64 with
  a 32-bit `wchar_t`, Linux constants and struct layouts) are in `runtime/src/hle/libc_win32.cpp`
  and `net_win32.cpp`.

From WSL the `.exe` files run directly (interop), but not in place: SQLite can't lock files on
`\\wsl.localhost\...` ("database is locked"), a worktree's `work/` link isn't followed there, and
the tests' `/tmp` is `\tmp` on the current drive. `scripts/windows-stage.sh` copies the tracked
files, the `work/` data the programs read and the `.exe` files to `C:\soa-win` (incremental; the
first copy of the 3.7.0 download takes about 10 minutes):

```sh
scripts/windows-stage.sh                                # -> /mnt/c/soa-win (C:\soa-win)
cd /mnt/c/soa-win && ./build-win/server/soa-server.exe --selftest
cd /mnt/c/soa-win && ./build-win/runtime/soaruntime_tests.exe
cd /mnt/c/soa-win && ./build-win/port/soa.exe --data run/soa-data --selftest
# the emulator against the server (pick free ports; a window opens unless --headless)
cd /mnt/c/soa-win && ./build-win/server/soa-server.exe --listen 127.0.0.1:39300 --http 127.0.0.1:39380 \
    --data run/server --download-dir work/download-3.7.0 &
cd /mnt/c/soa-win && ./build-win/emulator/soa-emu.exe --data run/phone --server 127.0.0.1:39300 --http 127.0.0.1:39380
```

**Playing on Windows:** the launchers in `scripts/windows/` are the `scripts/run-*.sh` twins, run from
the checkout (or the stage `C:\soa-win`) in `cmd.exe` or PowerShell, saves under `%LOCALAPPDATA%`:

| Launcher | Runs |
|---|---|
| `scripts\windows\run-port.cmd [soa options]` | the port: the 3.7.0 client with its in-process server (saves: `%LOCALAPPDATA%\soa\port-370` unless `--data`) |
| `scripts\windows\run-emulator-370.cmd [options]` | the 3.7.0 client in the emulator against `soa-server.exe`, which it starts and stops (`run-emulator-370.ps1`; `%LOCALAPPDATA%\soa\emulator-370`: `phone\`, `server\`, `server.log`; `--new-player`, `--enable-events`, `--port`, `--home`) |
| `scripts\windows\run-viewer-380.cmd [soa-viewer options]` | the offline 3.8.0 client in the viewer (saves: `%LOCALAPPDATA%\soa\viewer-380`; needs `work\extracted\xapk`) |

The programs' own default data dirs on Windows are these (`common/include/soa/paths.h`; on Linux
`~/.local/share/...`, as below); `--data DIR` overrides them. Builds before 2026-10-03 put them under
`<the launch directory>\.local\share\` (`soa-linux-370`, `soa-emulator-370\phone`, `soa-viewer-380`):
they aren't moved automatically; to keep such a save, move the directory while the program isn't
running, e.g. `move .local\share\soa-linux-370 "%LOCALAPPDATA%\soa\port-370"` (create
`%LOCALAPPDATA%\soa` first), or keep using it with `--data`.

**The control channel:** `--control NAME` is a named pipe on Windows (`\\.\pipe\NAME`:
`cmd.exe /c "echo tap:405:1000> \\.\pipe\NAME"`); `--control tcp:127.0.0.1:PORT` (both platforms; PORT 0:
any, logged as `I/control: listening on tcp:...`) is what the drivers use from WSL, whose mirrored
networking shares 127.0.0.1 with Windows (`networkingMode=Mirrored` in `.wslconfig`):
`control/soactl.py --windows-paths tcp:127.0.0.1:PORT tap:364:1000 shot:/tmp/a.png`.

**Tests on Windows from WSL** (`control/soadrive/winhost.py`): a session given a `.exe` runs the
staged copy from `C:\soa-win` (refreshed from `build-win/` when newer), with Windows paths, the TCP
control channel, the phone and the server's state on the Windows drive (linked back into the run's
dirs) and the shared pre-downloaded phone hard-linked there by `scripts/windows/link-phone.ps1`
(seconds; `cp -al` through WSL takes about ten minutes). Once: `scripts/windows-stage.sh --phone
--viewer` (the shared phone, 4 GB, and the soa-viewer package). Then:

```sh
scripts/windows-test.sh battle-gacha OUT TMP     # = tools/gate.sh win:battle-gacha (T2; SKIP without build-win/)
scripts/windows-test.sh seeded OUT TMP           # win:seeded
scripts/windows-test.sh viewer-boot OUT TMP      # win:viewer-boot
scripts/windows-test.sh shard-login OUT TMP      # win:shard-login: tests/diff's login, every target a .exe
SOA=$PWD/build-win/port/soa.exe SOA_EMU=$PWD/build-win/emulator/soa-emu.exe \
  SOA_SERVER=$PWD/build-win/server/soa-server.exe tests/diff/run.sh FLOW --out OUT   # any flow
control/run.py battle-gacha build-win/port/soa.exe OUT TMP     # any session, given the .exe files
control/run.py seeded build-win/emulator/soa-emu.exe build-win/server/soa-server.exe OUT
emulator-viewer/scripts/viewer_boot.sh build-win/emulator-viewer/soa-viewer.exe OUT
```

The stage is one per machine: two checkouts running Windows tests at once would test each other's
files and `.exe` files; give each its own: `scripts/windows-stage.sh --phone --viewer
/mnt/c/soa-win-NAME` once, then `SOA_WIN_STAGE=/mnt/c/soa-win-NAME` for its tests.

Windows ports: in mirrored networking a port WSL has bound (even briefly, to test it) stays refused
to Windows for a while, and WSL's ephemeral range is reserved for WSL; the drivers give Windows
programs port 0 (the control channel) or untested ports below that range (`soa-server.exe`, retried
when refused). Environment variables reach a `.exe` only through `WSLENV` (soadrive adds the
client's).

On a Windows machine, clone the repository and run the same `.exe` files from there.

## Running

`scripts/build.sh` sets up vcpkg (first time only) and builds everything. Then:

| Script | Runs |
|---|---|
| `scripts/run-port.sh` | the desktop port: the 3.7.0 client against the local server built into it (`--server inproc`), or `--server HOST[:PORT]` against a running soa-server. Other options go to `soa`, in two groups (`build/port/soa --help`): client options (`--fullscreen`, `--data DIR`, ...) and server options, soa-server's own flags (`--enable-events`, `--new-player`, `--seed FILE`, ...). Saves: `~/.local/share/soa-linux-370` unless `--data`. |
| `scripts/run-emulator-370.sh` | the original 3.7.0 online client, unmodified, in the emulator, against `soa-server` over TCP, which the script starts and stops. Data: `~/.local/share/soa-emulator-370/` (`phone/`, `server/`, `server.log`). Options: `--new-player`, `--enable-events`, `--event-keywords`, `--port`, `--home DIR`; others go to `soa-emu`. The first start downloads about 3 GB of game data from the local server. |
| `scripts/run-viewer-380.sh` | the offline 3.8.0 client, unmodified, in the viewer (`emulator-viewer/`, `soa-viewer`): the game as shipped after the service ended. No server: its one request goes unanswered, as on a phone today. Data: `~/.local/share/soa-viewer-380` (like the port's `~/.local/share/soa-linux`). Options: `--data DIR`; others go to `soa-viewer`, e.g. `--fullscreen`. |

Each script has `--help` and works from any directory.

**Bringing your own save over:**
- `--seed FILE` (port and `run-emulator-370.sh`) seeds a **new** local server state from a game save: a 3.7.0 or an offline-game `Game.xml`, e.g. the offline game's `shared_prefs/Game.xml` copied from your phone.
- **What carries over:** the player's level, FOL and name, and the characters you own.
- **What doesn't:** per-character EXP, favor and limit breaks aren't in a save, so they start at the defaults. The save's player id isn't used either; the local player is always `LOCAL00001`.
- **Use a fresh data folder** (`--data`, `--home`): an existing server state keeps its player.

### Game files
The scripts check for these and say which is missing. **In git** (plain git, no LFS; each under GitHub's 100 MB limit): the 3.7.0 APK, the three master DBs in `data/` and `data/gacha_pools.sqlite3`. **Local only** (too big for GitHub, or derived): the 3.8.0 XAPK, the Ghidra quick projects, and everything under `work/`. A checksummed copy of all of them is in `work/backup-lfs/`. <!-- 380-ok: names the viewer's XAPK -->

| File | Used by |
|---|---|
| `apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk` (the APKPure download) and `work/libSOA-3.7.0.so` (its `lib/arm64-v8a/libSOA.so`; the port also extracts it into its data dir) | the port; the 3.7.0 emulator |
| `work/download-3.7.0/` (the full 3.7.0 download; or `work/SOA-3.7.0-canonical-data.zip`, the same tree zipped, read in place with `--download`) and `data/basmaster-3.7.0.sqlite3` (its master DB, decrypted; without it the programs decrypt the download's into their data dir at startup: `docs/server-rules.md#master-source`) | the port's in-process server (its CDN and master data); the 3.7.0 emulator's server and CDN |
| `work/extracted/xapk/` (the offline XAPK, unpacked by `tools/extract.sh`) | optional for the viewer (`emulator-viewer/`, `soa-viewer --apk-dir`; it reads the XAPK in place when it finds one); `decomp.sh --v380` |
| `apk/STAR+OCEAN+-anamnesis-_3.8.0_APKPure.xapk` (the APKPure download) | the viewer (`soa-viewer` reads it in place: `--xapk FILE`, or found in `apk/` or beside the executable), the save editor, `decomp.sh --v380` | <!-- 380-ok: the viewer's game file -->
| `data/basmaster-3.8.0.sqlite3`, `data/basmaster-gl.sqlite3` (decrypted master DBs: the offline build's, the Global service's last) | the save editor; comparisons (`docs/basmaster-gl.md`) | <!-- 380-ok: the viewer's game file -->
| `data/version-3.7.0.bin` (in git; a copy of `work/download-3.7.0/version.bin`: the original CDN's index of the 3.7.0 download, revision 1471, 26,268 assets, MessagePack; the server's CDN serves a rebuilt revision 1472) | the reference for checking a download (`tools/check_download.py`) and for the CDN's rebuild |
| `data/gacha_pools.sqlite3` (the reconstructed gacha pools, made by `tools/build_gacha_pools.py`) | the local server's gacha draws (`docs/server-rules.md` 4.3) |
| `ghidra/quick-v370/`, `ghidra/quick/` (Ghidra quick projects; imported by `tools/common.sh` when missing) | `tools/decomp.sh`, `scripts/ghidra-mcp.sh` |

**Verifying the download.** `.venv/bin/python tools/check_download.py work/download-3.7.0` checks the folder against its own manifests and `version.bin`: every listed member present, its size and SHA-1 (of the ADLD-decrypted plaintext, as the manifests record it), the ADLD header against `e`, `parentHash`, the `.version` ids and totalSizes, duplicates and unlisted extra files, and `version.bin` against the canonical `data/version-3.7.0.bin`. It prints a summary per manifest and PASS / FAIL (exit 0 / 1); `--quick` checks existence, sizes and headers only, `--manifest ep1` one manifest, `--json OUT` every finding. The same layout is a client's storage, so it also checks a phone's `data/files/download` (e.g. `work/phone-3.7.0/data/files/download`, whose `version.bin` is the client's own revision-1472 record: reported as a note). On the 3.7.0 download: PASS with one warning, `Sound/TS_C121_Common_SE.spk`, which `version.bin` lists and no manifest does; about 5 s with the files in the page cache (`--quick` 2 s).

**Unpacking a download archive.** `.venv/bin/python tools/unpack_download.py ARCHIVE.zip DEST [--sha256 ARCHIVE.zip.sha256]` extracts a zip of the download tree into DEST (the tree at the zip's top level, as in `SOA-3.7.0-canonical-data.zip`, or inside one top folder, which is stripped; Windows `:Zone.Identifier` files are skipped), checks the archive against its `.sha256` first if given, then runs the same check as `check_download.py` on DEST. Exit 0 = complete.

## Packaging

`scripts/package.sh` (`tools/package.py`) builds the release ZIPs, for Linux and Windows (both unless
`--linux` / `--windows`; into `dist/` unless `--out DIR`; `--no-build` packages the existing builds):

| ZIP | Holds |
|---|---|
| `soa-port-<V>-<platform>.zip` | `soa` (the port, its server in-process), `run-port.sh` / `run-port.cmd` |
| `soa-emulator-<V>-<platform>.zip` | `soa-emu` (the unmodified 3.7.0 client), `soa-server` (its server; runs alone too), `run-emulator.sh` / `run-emulator.cmd` + `.ps1` (start the server, then the client) |
| `soa-<V>-<platform>-debug-symbols.zip` | the programs' debug info (line tables), stripped from the binaries |

`<V>` is the commit date and hash; `<platform>` `linux-x64` or `windows-x64`.

- **Optimized:** `scripts/build.sh [--windows] --release` builds `build-release/` (`build-win-release/`):
  `CMAKE_BUILD_TYPE=Release` (`-O3`, `NDEBUG`) plus `-g1`, soa / soa-server / soa-emu only; no
  `-march` and no `-ffast-math` (the natives are bit-exact only with x86-64's default code). No LTO.
  On Linux libstdc++ and libgcc are linked statically: the binaries need glibc 2.39 (the build
  host's, Ubuntu 24.04), `libEGL.so.1` and `libGLESv2.so.2`; SDL loads X11 / Wayland / PulseAudio
  at run time; ffmpeg runs the movies. The Windows `.exe` files are static (Windows' DLLs only;
  `ffmpeg.exe` beside them or on PATH for the movies).
- **What goes in** (an allow-list in `tools/package.py`): the binaries, the launchers, `README.txt`
  (from `scripts/package/README.txt.in`, one template for the four packages: per program, which game
  files it needs, where to put them, the lookup order, the flags, the data dirs, the first run, the
  messages when something is missing), `LICENSE.txt`, `THIRD-PARTY-NOTICES.txt` (the copyright files
  of the vcpkg ports linked, dynarmic and its x86-64 externals, IJG libjpeg 9, zstd 1.3.4),
  `BUILD-INFO.txt`, and only data we made: `data/gacha_pools.sqlite3` **with the game's text
  removed** (`gacha.name`, `rule.text`; the server takes the titles from the master,
  `docs/server-rules.md#gacha-pools`), `data/saves/seed/Game.xml` (the default seed player, sanitized:
  `data/saves/README.md`) and `standin-assets/` (our images).
- **What never goes in:** any game file: the APKs, the download, the master DBs
  (`data/basmaster-*.sqlite3` are decryptions of the game's own), `version.bin`, `libSOA.so`,
  `port/fakeapi/responses`, decompiles. Before a zip is written every file must be on the allow-list
  and pass a game-file scan (the ADLD magic, the game's asset extensions, an ARM64 ELF, a zip, a
  SQLite file with `master_*` tables or gacha titles, the names `basmaster` / `version*.bin` /
  `libSOA`); the stand-ins pass only as files tracked in git under `standin-assets/` that the download
  doesn't have. A violation fails the run and writes no zip (`tests/test_package.py` checks the check).
- **The game files at run time:** the programs look for them where they are stored
  (`common/include/soa/install.h`, `game_files.h`): flags first (`--apk`, `--download` (=
  `--download-dir`), `--master`), then the source checkout (developers), then **the program's own
  folder and its `game/` subfolder**: the 3.7.0 APK is any top-level `*.apk` whose libSOA.so is
  3.7.0's; the download is a folder holding `version.bin`, `manifest/` and `sqlite/basmaster.sqlite3`
  (any name), or `SOA-3.7.0-canonical-data.zip` (or another zip holding that tree) **read in place
  without extracting it** (`common/include/soa/file_tree.h`: stored entries served as ranges of the
  zip, by the CDN, the asset fallback and the movie player). The master DB is decrypted from the
  download on the first run into the data dir (`docs/server-rules.md#master-source`); libSOA.so is
  taken from the APK. A missing file stops the program with a message naming it and pointing to
  `README.txt`.
- **Checking a package:** unzip it outside the checkout, put the game files as its README.txt says,
  and run a session on it: `SOA_PACKAGE_DIR=<the unpacked folder>` makes `control/run.py` run the
  package's programs from their folder, with no `--master` / `--download-dir` / `--seed` (e.g.
  `SOA_PACKAGE_DIR=$P control/run.py gacha $P/soa OUT TMP`; for the emulator `--target emu` with
  `SOA_EMU=$P/soa-emu`; for `.exe` files unpack on a Windows drive and set `SOA_WIN_STAGE` to your
  stage). `DOWNLOAD_B=work/SOA-3.7.0-canonical-data.zip tools/server_cdn_check.sh BIN BIN` proves the
  CDN serves the same bytes from the zip as from the folder.

## Reverse-engineering tools

- **Ghidra** (12.1.2, snap at `/snap/ghidra/current/ghidra`): `tools/decomp.sh` / `tools/decomp_at.sh` decompile from the quick projects (`ghidra/quick-v370`, local, not in git; re-imported by `tools/common.sh` when missing) through a pool of working copies in `work/ghidra-quick-v370*`. Ghidra refuses project paths with a component starting with `.`.
- **PyGhidra**, in `.venv`, from Ghidra's own wheels (`requirements.txt` says how): `pyghidra.start()` with `GHIDRA_INSTALL_DIR` set.
- **Ghidra over MCP for Claude Code**: `scripts/ghidra-mcp.sh` serves the 3.7.0 project with [pyghidra-mcp](https://github.com/clearbluejar/pyghidra-mcp) (through `uvx`), headless, on its own working copy `work/ghidra-mcp-v370` (so its analysis, renames and types never touch the committed project). `.mcp.json` registers it as the project's `ghidra-v370` server; Claude Code asks once to approve it. Before first use run `scripts/ghidra-mcp.sh --analyze` once (Ghidra's full auto-analysis plus pyghidra-mcp's indexes; the tools refuse until it's done). One server at a time can have the copy open.
- **jadx** (the APK's Java), **lief**, **keystone**, **capstone**, **unicorn**, and the system tools in "Setup" (gdb-multiarch, clang tools, strace, …).

## Save editor and event scripts

`soa_save/` edits the offline game's saves (`dump`, `set`, `roster`, `unlock-all`), pushes them to a phone or Waydroid, and decodes the event scripts: [`soa_save/README.md`](soa_save/README.md).

## Tests

`tools/check_no_380.sh` checks that no reference to the offline build is left outside the viewer and `docs/history/` (it lists what may keep one).

`.venv/bin/python -m pytest tests`. They use the sanitized saves committed in `data/saves/` (`data/saves/README.md`); your own saves stay in the ignored `samples/`.

The port's tests (`build/port/soa --selftest`, `port/scripts/smoke.sh`, the `port/scripts/*_session.sh` sessions; `port/README.md`) and the emulator's (`emulator/scripts/`) run headless: the game renders into a hidden window, so no window opens, but they still need an X display. `WATCH=1` shows the port's window while a script runs (the scripts pass `--windowed` instead of `--headless`); `soa --headless` / `--windowed` choose by hand. The session scripts of both start from the shared pre-downloaded 3.7.0 phone `work/phone-3.7.0` (build it once with `scripts/make-phone-370.sh`, verify it with `scripts/check-phone-370.sh`; `SOA_PHONE=none` runs the full download instead; `port/README.md` "The shared pre-downloaded phone").

## Credits

English character names come from the [Star Ocean Wiki](https://starocean.fandom.com/wiki/Star_Ocean:_Anamnesis_playable_characters) (CC BY-SA). A copy is in `docs/wiki/`.
