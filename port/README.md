# STAR OCEAN: anamnesis for desktop Linux

This port runs the game natively on x86-64 Linux: **the 3.7.0 online client** (the last online version, from its APK), with the game server in-process or as `soa-server` (next section). It doesn't emulate Android: `libSOA.so` is loaded into an ordinary Linux process, and a small host provides everything around it:

- **CPU**: the game's ARM64 code runs under the [dynarmic](https://github.com/lioncash/dynarmic) JIT. Guest memory is identity-mapped, so guest pointers are host pointers.
- **libc**: bionic libc, libm and pthreads are implemented on top of glibc (`runtime/src/hle/`).
- **Android framework**: the NDK APIs (`runtime/src/android/`) and the Java side (`runtime/src/jni/`) are reimplemented:
  - native-activity lifecycle, looper, input queue
  - assets, read straight from the APKs
  - SharedPreferences
  - movie player, on FFmpeg's libraries (linked in)
  - text entry
- **Graphics**: SDL2 owns the window and the OpenGL ES contexts (X11 or Wayland, whichever SDL picks; `SDL_VIDEODRIVER` chooses). The game's EGL calls are emulated over them (`runtime/src/hle/egl.cpp`, `runtime/README.md` "Graphics") and its GLES calls go to the host's Mesa. Android's buffer scaling is emulated with an offscreen framebuffer, letterboxed into a resizable window. The guest's `glReleaseShaderCompiler` after every shader compile is dropped: on Mesa it discards the GLSL built-ins, making the next compile and link about 10x slower (about 9 s of render-thread time per boot). `SOA_GL_RELEASE_SHADER_COMPILER=1` passes it through. Two more host-driver workarounds (`runtime/src/hle/gles.cpp`), both leaving the rendered texels and buffer contents unchanged:
  - **sRGB ETC2 textures** (`GL_COMPRESSED_SRGB8_ETC2`, `..._SRGB8_ALPHA8_ETC2_EAC`, `..._SRGB8_PUNCHTHROUGH_ALPHA1_ETC2`) are decoded by the port (`runtime/src/hle/etc2.cpp`) and uploaded as `GL_SRGB8_ALPHA8`. Mesa d3d12 has no ETC2, and its CPU decode of the sRGB variants is about 70x slower than of the linear ones (650 ms for one 1024x1024 level). They were ~20% of busy time in `restore_session.sh`. The selftest `hle/etc2-vs-host` compares the decode texel for texel with the driver's. `SOA_GL_HOST_SRGB_ETC2=1` hands them to the driver again.
  - **Buffer updates:** the engine's vertex/index buffer `Update` maps a range write-only and then overwrites all of it. Those maps (only those, flagged by `render_rd.cpp` through `glh::t_map_overwrites`) get `GL_MAP_INVALIDATE_RANGE_BIT`, so the driver doesn't wait for the GPU. `SOA_GL_MAP_INVALIDATE=0` turns it off.
- **Audio**: OpenSL ES buffer queues are mixed into SDL2 audio. When no device pulls (none opened, or its callback stalls for 250 ms, as WSLg's PulseAudio sometimes does), a null sink in `main.cpp` pulls in real time and discards the samples: the game only learns that a sound ended from its buffers being played, so without it every SE, voice and stream stayed "playing" (e.g. `CEventScenario::IsEnd` waited forever for a scene's SEs).

That host is two parts. The JIT host runtime, everything that runs an Android `libSOA.so` (loader, JIT CPU, HLE, JVM, NDK, movies), is the library `runtime/` (`libsoaruntime`; `runtime/README.md`), shared with other host programs. The port (`port/src/`) is `main.cpp` (the SDL window, input, audio device and the run options) plus the native replacements and the local server.

The game talks to its game server through `NetworkApiCaller`. The service is gone, so the port brings its own: the local server library (`server/`), in-process through the client's dormant built-in fake server (`FakeApiCaller`; `docs/notes.md` "Offline server (FakeApiCaller)") or as `soa-server` over the client's own network code.

## The port: the 3.7.0 client, the route, the port's features

**Plan:** [`PLAN.md`](PLAN.md); **what is left:** [`REMAINING.md`](REMAINING.md).

The port runs the unmodified **3.7.0** client (`docs/history/PLAN-rebase-370.md`; progress in `docs/history/REBASE-370.md`). **Its native replacements were dumped on 2026-10-01** (the plan's revision 2): the families written for the offline build (about 18,000 natives) are gone, and are being rebuilt for 3.7.0 as readable C++ from the Ghidra decompile, hottest first, each with differential tests and a live check (`src/native/README.md`). What runs natively: the port's own hooks (the in-process server route, the debug control commands, the tower opt-in, the resolution, the local notice board) and the rebuilt subsystems' natives (`src/native/<subsystem>/README.md`; `soa --list-native` lists every one). Everything else is the guest's ARM64 code under the JIT.

```sh
build/port/soa                                   # --server inproc: the local server in-process; data in ~/.local/share/soa-linux-370
build/port/soa --server 127.0.0.1:44300 --http 127.0.0.1:44380   # against a running soa-server
```

- **Client files:** the library is `lib/arm64-v8a/libSOA.so` of the 3.7.0 APK (`apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk`, `--apk FILE`), extracted once into `DATA/libSOA-3.7.0.so` (else `work/libSOA-3.7.0.so`; `--lib PATH` overrides). The APK list is that single APK: no asset packs, no Play Core. `--apk-dir` is ignored with a warning (old scripts).
- **Data dir:** default `~/.local/share/soa-linux-370` (Windows: `%LOCALAPPDATA%\soa\port-370`; `common/include/soa/paths.h`), a new one, so the pre-rebase port's `~/.local/share/soa-linux` (its cached offline-build `libSOA.so` and save) never mixes in.
- **Platform:** `soa` links `platform370/` (`platform370/README.md`): `platform370::install` before `hle_init` (the 25 Java answers, `fmod`, the device clock, `app_version` "3.7.0"), `install_patches` (the `service_stop_day` patch) and `install_language` (`--lang`, `--voice-lang`) before the natives. `--device-clock`, `--no-patch`, `--no-dst-fix`, `--lang`, `--voice-lang` as in `soa-emu`.
- **`--server inproc` (default):** the local server library answers in-process through the FakeApiCaller route (`src/native/api/fakeapi.cpp`, its table generated for 3.7.0 by `tools/gen_fakeapi_tables.py`). The client's own `CGame::OnInitialize` still builds its `NetworkApiCaller`; the route's hook then puts a `FakeApiCaller` in `TSingleton<CApiCaller>`. The server's **CDN runs in-process too** (`src/native/api/server_cdn.cpp`): the library's CDN tree from `--download-dir` (required in this mode; default `work/SOA-3.7.0-canonical-data.zip`, read in place, or an extracted folder) plus the stand-ins, mounted on soa-server's own HTTP router (`net::mount_cdn`), which is platform370's **HTTP backend** (`platform370::set_http_backend`). **No sockets in-process:** each of the client's HTTP requests to `production-game.so-ana.com` is a call to `HttpRouter::handle`, its body streamed. Login carries the CDN keys (`AssetPath`, `MasterPath`, `r_ver`) and `LatestEpisodeVersion` (3: the episode packs; docs/server-rules.md#cdn), and the client downloads or checks its game data from it as `soa-emu` does from `soa-server`. An empty data dir downloads the 3.8 GB once (about 3-4 minutes: 1,446 GETs, the episode packs EP1-3 included when the client save has them, as the committed one does); a data dir with the data checks five manifests (Bulk, Individual, ep1-3) and fetches the packs it is missing. The server computes party and NPC statuses with its own master-data rules, as `soa-server` does (no client status provider since revision 2).
- **`--server HOST[:PORT]`:** no FakeApiCaller hooks: the client's own `NetworkApiCaller` talks GameRPC to soa-server's `--listen` and HTTP to `--http HOST:PORT` (default `<host>:44380`) through platform370's network glue (`--lobby`, `--map-host` as in `soa-emu`). The data download is real, from soa-server's CDN. `--download-dir` is off unless given. The local server library isn't used; server options given to `soa` then only log a warning (give them to `soa-server`, which takes the same flags).
- **Natives: `--natives all|route|none`, default `all`:** `all` installs every registered native; `route` only the FakeApiCaller hooks (left out with `--server HOST`) and the port's own hooks (the `CPhase::Progress` wrapper of the control commands and of the `port_debug: phase N` log lines the scripts wait on, `src/native/common/port_debug.cpp`; the tower opt-in, `--restore-tower`; the resolution; the notice board's local page), so the game's own code all runs under the JIT while the sessions still work: the A/B for a native regression, narrowed with `--natives-skip SUBSYS[,SUBSYS..]` (whole subsystems left to the guest); `none` (`--no-native`) nothing. Natives are refused on any `libSOA.so` but the 3.7.0 build their address tables were generated from (its sha256; `--natives none` runs any lib): `src/native/README.md` "Guest addresses".
- **Saves:** the committed client save `data/saves/client/Game.xml` (an offline-game KVS) is read by 3.7.0 as it is; the local KVS (`Aska.xml`) is left to the client to create. `--seed FILE` seeds a new server state from a save.
- **Gates:** `port/scripts/rebase_inproc_session.sh` (in-process: title, Login, the data check or download, home, the login popups; `SOA_PHONE=none` for the full download) and `port/scripts/rebase_server_diff.sh [PHONE]` (soa `--server` and `soa-emu` run `emulator_session.sh`'s seeded flow to home against fresh soa-servers with `--seed-rng 1`; `tools/compare_packets.py` requires their request sequences to be equal). `emulator/scripts/emulator_session.sh` runs with `build/port/soa` as its client as well. The smoke test and every session script run on the 3.7.0 port and start from the shared pre-downloaded phone by default (P5a; "Tests and session scripts" below).
- **Selftest:** `build/port/soa --selftest` boots the 3.7.0 guest with no natives installed and runs the runtime's tests, the route's (`fakeapi/*`, `wire/*`), the port's server tests (`server/*`) and the server library's; the run's summary line gives the current count.

### The shared pre-downloaded phone

The 3.7.0 client downloads its game data (3.1 GB, 24,637 files under `data/files/download`; 4.0 GB, 26,055 files with the episode packs EP1-3) on an empty phone: 3-4 minutes and two dialogs per run. The session scripts (`port/scripts/phone370.sh`, `rebase_inproc_session.sh`, `rebase_server_diff.sh`, `emulator/scripts/emulator_session.sh`) instead start from **one shared phone, `work/phone-3.7.0`**, built once and linked into each run's data dir (`scripts/shared-phone.sh`):

- **Build it:** `scripts/make-phone-370.sh [soa]` runs `rebase_inproc_session.sh` with `SOA_PHONE=none` (the default in-process server, to home), keeps only `data/files/download` (no `Aska.xml` / `Game.xml`, `server.sqlite3`, shader cache or `download/temp.sqlite3`), stamps it (`PHONE.txt`; `files.txt`: size, mtime and path of every file; `sha256sums.txt`) and makes it read-only (`chmod -R a-w`). `--from PHONE` takes the data from an existing phone instead of downloading; `--out DIR` (or `SOA_SHARED_PHONE=DIR`, which also makes the sessions use it) builds another place. Rebuild it when the CDN data, the master the server serves or the client version changes. **Rebuilding while sessions run on it:** build into `--out work/phone-3.7.0.new`, check it (`scripts/check-phone-370.sh work/phone-3.7.0.new`), then `mv work/phone-3.7.0 work/phone-3.7.0.old && mv work/phone-3.7.0.new work/phone-3.7.0`: running sessions keep their hard-linked inodes, new ones link the new phone; delete `.old` later (`find work/phone-3.7.0.old -type d -exec chmod u+w {} +`, then `rm -rf`; never `chmod` its files, they are the inodes other run phones share).
- **The episode packs EP1-3 are on the phone** (rebuilt 2026-10-02 with `SOA_EPISODE_PACKS=1 scripts/make-phone-370.sh`: the download session keeps the committed save's `BAS:DownloadEpisodeFlag` 7, so the client fetches the three packs too; 1,446 GETs, 261 s): **26,055 files, 4,006,672,570 bytes (3.8 GiB)** against 24,637 / 3.3 GB without them (`PHONE.txt` says `episode packs: EP1 EP2 EP3`). The packs add 1,418 files (TalkScene, Image, BG, Sound voices, 6 manifests), extracted into the common tree; `download/EP<n>/` keep only the empty bundle directories, as `B/` does. The phone built before 2026-10-02 had none (the server didn't send `LatestEpisodeVersion` then). The sessions don't depend on them: `phone370_client_save` gives the run's client save `BAS:DownloadEpisodeFlag` 0, so the client's books have no episode whatever the phone holds, and its data check only GETs the three `version_latest_ep<n>.version` (they match the phone's); the flows are the same as on the phone without packs. `episode_movie_session.sh` (flag 0, the "ask" flow) still has the client download its episode again ("必要容量:396MB", every bundle fetched and extracted, renamed over the run phone's links; only the manifest `.bin` isn't fetched); with `SOA_EPISODE_PACKS=1` (flag 7, the "save" flow) the client finds the packs and downloads nothing. With an episode's data on the client's books, home's ミッション opens the map of the last episode played (`BAS:LastInEpisodeID`; Episode 2 in the committed save) instead of the episode list; `phone370_episode_list` goes on to the list through Ep選択.
- **Check it:** every session checks sizes and mtimes against `files.txt` (0.15 s) and falls back to the download, with a message, when it doesn't match; `scripts/check-phone-370.sh` verifies every sha256, that no file was added or removed and that nothing is writable (under a second when cached).
- **`SOA_PHONE`:** unset = the shared phone (if built); `none` or empty = an empty phone, the full download (the one test of the downloader: `SOA_PHONE=none port/scripts/rebase_inproc_session.sh`, or `make-phone-370.sh` itself); `DIR` = that phone, linked if it is stamped, else copied with `cp -a` as before (e.g. a `KEEP_DATA=1` emulator run's `OUT/emu`).
- **A run's phone:** real, writable directories; a **hard link** per file (`cp -al`), the shared read-only inode; and real copies of `download/version.bin` and `download/manifest/` (12 MB). About 0.6-0.7 s and 14 MB per run with the packs (26,055 links; 0.9 s measured on the phone without them), against 3.9 s (warm page cache) and 3.2 GB for `cp -a`. Where a hard link can't be made (another file system) it uses symbolic links (`cp -rs`: about 9 s and 100 MB of link blocks for the 24,637 links).

**How the client writes its phone** (strace of a full-download `rebase_inproc_session.sh` and of a pre-downloaded `soa-emu` session to home, 2026-10-01; `-e trace=%file,getdents64,ftruncate`):

| Files | How they are written | In the run's phone |
|---|---|---|
| every extracted asset (`BG/`, `Motion/`, `Image/`, ...: 24,600 files) and the master `sqlite/basmaster.sqlite3` | `X.tmp` opened `O_RDWR\|O_CREAT\|O_TRUNC`, written, `rename(X.tmp, X)`: never in place; on a pre-downloaded phone only `access(F_OK)` / `stat` and `O_RDONLY` opens | hard link (a re-download, e.g. the master `--restore-tower` edits, renames a new file over the link) |
| `download/version.bin` | opened in place, `O_RDWR\|O_CREAT\|O_APPEND` then `O_RDWR` on every data check, `O_RDWR\|O_CREAT\|O_TRUNC` after a download | copy |
| `download/manifest/etc2/hi/*.bin`, `version.version` | in place, `O_RDWR\|O_CREAT\|O_APPEND` / `O_RDWR\|O_CREAT\|O_TRUNC` on every data check; `version_latest_*.version` via `.tmp` + `unlink` + `rename` | copy |
| `download/temp.sqlite3` | the decrypted master, created on every run (`O_RDWR\|O_CREAT\|O_TRUNC`) in `download/` and unlinked | (new file in a real directory) |
| `download/B/**/*.bin` | the bundles, created then unlinked after extraction (`B/` keeps empty directories) | (real directories) |
| `shared_prefs/{Game,Aska}.xml` | `X.tmp` + `rename` | not shared |
| `files/AHSLLinkedBinaryDiskCacheGLES3` | the shader cache, in place (`O_RDWR\|O_CREAT\|O_APPEND`) | not shared |

The client's only directory walk of the phone is the guest's `fts_open` (the HLE `fts_walk` uses `lstat`, so a symbolic link would be `FTS_SL`, not a file); it walks `download/` and `manifest/` only on the download path, before the bundles exist. Hard links avoid that question (they are regular files to `lstat`, `readdir` `d_type` and `stat`) and make any in-place write to shared data fail loudly with `EACCES` (the inode is read-only), while the client's write-new-then-rename and delete+create only replace the run's own directory entry. No runtime change was needed.

## Native code

Any guest function can be replaced with C++ by its symbol (`src/native/`, `NATIVE_FUNCTION(...)`): its entry is patched to trap into the host. The port moves from JIT-executed ARM64 to native code one function at a time this way, with each replacement checked against the original (see `src/native/README.md`). Since the rebase's revision 2 the families are being rebuilt from scratch for 3.7.0 (readable C++ from Ghidra, no new a2c translations); `src/native/README.md` "What's native now" lists what exists.

## Profiling: what runs, and what is native

Two environment variables record which guest code actually runs, to pick porting targets (`runtime/src/core/profile.cpp`):

| Variable | Records | Cost |
|---|---|---|
| `SOA_COVERAGE=DIR` | every guest function executed at least once (`coverage.tsv`, with the time of first use) | a one-shot trap on each of the ~103k function entries; each removes itself on first use, so there is no steady-state overhead |
| `SOA_PROFILE=DIR` | sampled call stacks of every guest thread (`stacks.folded`, flamegraph format); `SOA_PROFILE_HZ` sets the rate (default 1000) | ~2% of one core for the sampler thread; the game runs normally |
| `SOA_PROFILE_HOST=1` (with `SOA_PROFILE`) | the host PC of threads inside native replacements (`host.tsv`): `port/scripts/host_profile.py DIR --soa build/port/soa` gives self time per C++ function (per native) | a SIGPROF per sample of a thread in native code |

Both write into `DIR` (normally the same one), along with `functions.tsv` (the function table), `calls.tsv` (call counts of HLE imports and native replacements) and `meta.txt`. The files are rewritten every 10 s, on `kill -USR1`, on the `profile-dump` control command and on exit.

- **Function table.** `.dynsym` only names exported functions. Local ones are found from BL targets, relative relocations into `.text` (vtables), `.eh_frame_hdr` and ADRP+ADD address loads, and named `FUN_<ghidra address>`.
- **Stacks.** The library has no frame pointers, so stacks are unwound from each function's prologue (frame size and where x30 is saved). Time spent in host code is attributed to `[hle]<import>` or `[native]<symbol>` leaf frames, below the guest caller.
- **Natives calling natives.** A native that reaches another through `guest_call` (the direct path, `run_direct` in `runtime/src/core/cpu.cpp`, or through the JIT) gives `[native]A;[native]B`: B's time is B's, and native (2,636 such samples in a battle run of 2026-10-08, e.g. `AudioSignalNotify::Handler` -> `SLVoice::AudioSignal`). Guest code a native calls is `[native]A;guest`, and an original body a native runs under its own hook (`NATIVE_FUNCTION_ORIG`, callee hooks) `[native]A;A`: both are guest code, correctly. A native called as a C++ member has no frame of its own: its time is the caller's `[native]A` (native, but under A's subsystem); `SOA_PROFILE_HOST=1` + `port/scripts/host_profile.py DIR --by-subsystem` splits native time by the C++ code's subsystem. A sample taken while the JIT stands on a hooked entry, before its SVC, names the hooked function as guest code (18 of 5.5M samples in that run). `port/scripts/rebuild_queue.py` counts guest self (guest leaves only) and native self (`[native]` leaves) per subsystem separately (`tests/test_rebuild_queue.py`).

Native replacements that block (the `sync.cpp` Event/Semaphore/lock waits) mark the blocking part with `ProfNativeWait`, so it is reported as the idle pseudo-import `native_wait` rather than native work.

`SOA_WATCHDOG=SECONDS` logs `E/watchdog` and prints every guest thread's stack when no frame has been presented for that long (after the first frame); with `SOA_PROFILE` set the stacks are complete. Use it to diagnose hangs and deadlocks.

`soa --list-native` prints the registered native replacements. `port/scripts/profile_report.py DIR [DIR...]` merges runs and prints:

- where the time goes (guest JIT code, native code, HLE work, HLE waits);
- the top functions by self and inclusive time;
- families (`Aska::Yayoi`, `CUIUtility`, `std::__ndk1`, …) by time and by executed functions, with executed/total functions and bytes;
- native coverage;
- large families that never ran.

```sh
SOA_COVERAGE=work/profile/smoke SOA_PROFILE=work/profile/smoke port/scripts/smoke.sh build/port/soa /tmp/smoke
port/scripts/profile_report.py work/profile/smoke > work/profile/report.txt
```

## Memory diagnostics

`--memstats` logs a snapshot (`I/memstats`) at every `CPhase` change, and `--memstats S` also logs one every S seconds. The `--control` command `memstats[:TAG]` logs one on demand (`port/src/native/common/memstats.cpp`). Each snapshot has:
- RSS and host threads by name;
- guest CPU contexts, grouped by each thread's guest entry function, with the nesting levels each thread holds;
- the dynarmic code caches' RSS;
- `mallinfo2`;
- the guest engine heap;
- the largest mappings.

What a context costs: every host thread keeps one guest CPU context, a dynarmic JIT, per `guest_call` nesting level it has reached, until the thread exits (`runtime/src/core/cpu.cpp` `ThreadState`). Each context holds about 4 MB of JIT code plus about 5 MB of block metadata in host malloc. dynarmic's 16 MB fast-dispatch table would add more, but the port gives its pages back when it creates the JIT (`release_fast_dispatch_table`). Contexts grow with nesting depth, not with time.

PLAN-next D7 measured this on `sphere211_session.sh`:
- **Before** (the guest saw 32 host CPUs): 62 engine workers; the dynamics workers reached 4-6 levels each. The run went from 95 contexts / 2.6 GB at home to 230 contexts / 6.4 GB after four battles.
- **After** (8 guest CPUs, so 14 workers, and the fast-dispatch tables released): the full session passes at 56 contexts / 0.7 GB at boot, 91 / 1.9 GB after the first battle and 102 / 2.3 GB at the end (6 battles and floor 2). Each later battle adds 0-6 contexts, about 70 MB, as threads reach new depths.

## Environment: diagnostics and test switches

Settings are command-line flags (`soa --help`). The environment carries only diagnostics and the
test harness's switches, read with one rule (`common/include/soa/env.h`): a switch is off when unset,
empty, `0`, `false`, `no` or `off` (any case) and on otherwise; a number out of its range (or not a
number) is warned about and its default used. A variable that was a setting prints one line naming
its flag ("... is gone: use --clock") and is ignored: the table of removed variables and their flags
is in `docs/environment.md`.

The runtime's switches (the same in soa, soa-emu and soa-viewer: `SOA_TRACE`, `SOA_COVERAGE`,
`SOA_PROFILE`, `SOA_PROFILE_HZ`, `SOA_PROFILE_HOST`, `SOA_WATCHDOG`, `SOA_AUDIO_DUMP`, `SOA_TRACE_RT`,
the `SOA_GL_*` escape hatches, `SOA_OFFSCREEN_PRESENT`, `SOA_DIRECT_CALLS`) are listed in
[`runtime/README.md`](../runtime/README.md) "Environment"; "Profiling" above shows them at work.
soa's own:

| Variable | Effect |
|---|---|
| `SOA_SELFTEST_DELAY=S` | `--selftest` waits S seconds (0..3600, default 10) after the memory and parameter managers exist |
| `SOA_SELFTEST_START_FILE=F` | `--selftest` waits until file F exists instead (drive the game to a scene through `--control` first) |
| `SOA_SELFTEST_SKIP=a,b` | tests left out by exact name (`port/scripts/selftest_resilient.sh` sets it after a crash) |
| `SOA_SELFTEST_REPEAT=N` | run each matching test N times (1..10000), the port's and the server library's |
| `SOA_AAF_EVAL_DUMP=DIR` | the live selftest `anim/aaf-eval-dump` records the guest's keyframe values there (`DIR/<n>.aafeval`), for `tools/aafdump --verify DIR` (docs/notes.md "Animations (AAF) for tools") |
| `SOA_TEST_HOOKS_SKIP=sym,..\|all` | test hooks (`NATIVE_TEST_HOOK`) not installed, to find one that breaks the boot |
| `SOA_PARAMS_CORPUS=DIR` | the params self-tests also replay the recorded corpus in DIR (`native/params/README.md` "Tests") |
| `SOA_YAYOI_TEST_TRACE=1` | the yayoi SQLite self-tests print each log line as they make it |
| `SOA_STUB_TRACE=1` | print each call a recording stub answers (`native/common/guest_stub.cpp`) |
| `SOA_WIRE_DUMP=FILE` | the wire self-tests append their dumps to FILE (`tools/api_wire.py`) |
| `SOA_NOTICE_HTML_DUMP=FILE` | the self-test `player/notice` writes the notice page's HTML there (also `soa-server --selftest player/notice`; `docs/webview.md`) |
| `SOA_TEST_TALK_IDS=id,..` | with `--lang en` (platform370, also soa-emu): each new line on the home's speech box shows the master text of the next of these message ids instead (in turn), for shots of chosen lines (`docs/client-changes.md` "The home's speech box") |
| `SOA_TEST_STORY_TEXTS=FILE` | with `--lang en` (platform370, also soa-emu): each message the story window shows is replaced by the next line of FILE (`\n` in a line is a line break; in turn), for shots of chosen story lines (`docs/client-changes.md` "The story message window") |
| `SOA_WEBVIEW_DUMP_CSS=FILE` | the web view appends each stylesheet as litehtml gets it (also soa-webview-render) |

In no build: `SOA_ASKA_MATH_OFF` / `SOA_ASKA_MATH_SKIP` (groups and symbols left to the guest, for
bisecting) exist only in what tools/gen_aska_math_a2c.py would emit; the a2c generators are kept as
tools, and nothing in the tree uses their output (`src/native/README.md`). Host variables: `HOME` (the default `--data`), `TZ` (the local time `--clock` and
`--device-clock` are read in; with `HOME` and `TMPDIR` the only host variables the guest's `getenv`
sees), and SDL's own: `SDL_VIDEODRIVER`, `SDL_AUDIODRIVER` (`dummy` / `disk`), and any `SDL_*` hint.
The runtime sets two hints at normal priority (`SDL_HINT_VIDEO_X11_FORCE_EGL`,
`SDL_HINT_IME_SUPPORT_EXTENDED_TEXT`), so the environment can override them; leave
`SDL_VIDEO_X11_FORCE_EGL` alone (the EGL emulation assumes SDL's X11 contexts are EGL ones).

## Building

The dependencies come from vcpkg (`vcpkg.json`) and CMake `FetchContent` (dynarmic, IJG libjpeg 9); the system provides a C++20 compiler, CMake, Mesa's libEGL/libGLESv2 and the X11/Wayland/PulseAudio headers SDL2 builds against (the root `README.md`, "Setup", lists the `apt install` lines):

```sh
scripts/build.sh                    # from anywhere: vcpkg into .vcpkg/ if missing, configure build/, build everything
cmake --build build -j8 --target soa   # afterwards, one target
```

The repository's `CMakeLists.txt` is the only build root (the root `README.md`, "Building"). It picks vcpkg's toolchain, defines the shared settings (the C++ standard, the build type), includes `cmake/deps.cmake` (the dependencies' imported targets: `ZLIB::ZLIB`, `unofficial::sqlite3::sqlite3`, `OpenSSL::Crypto`, `soa::SDL2`, `soa::EGL`, `soa::GLESv2`, `soa::jpeg9`, ..., and dynarmic), then adds `runtime/`, `server/`, `port/` and `emulator/`. `port/CMakeLists.txt` builds `build/port/soa`: the runtime's objects (`libsoaruntime`, `runtime/README.md`) are linked first, ahead of `port/src`, and the local server library (`libsoaserver`, `server/README.md`) is linked whole after them, so the static-initializer order (native and selftest registration) is what it was when everything was in `port/src`. The same build gives `build/server/soa-server`, `build/emulator/soa-emu` and `build/runtime/soaruntime_tests` (the runtime's extension-point tests: run it directly; it needs no game files).

## Running

You need the 3.7.0 APK (`apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk`) and, for `--server inproc`, the 3.7.0 download (`work/SOA-3.7.0-canonical-data.zip`, read in place); both are found from the repo:

```sh
build/port/soa                      # in-process server (--server inproc)
build/port/soa --server 127.0.0.1   # against a running soa-server (scripts/run-emulator-370.sh starts one)
```

`soa --help` lists the options in two groups, as `core/options.h` holds them (`ClientOptions`, `ServerOptions`): **client options** are about the 3.7.0 client and its emulated phone; **server options** are the local server's rules and state, used only with `--server inproc` (with `--server HOST` they belong to `soa-server`, which takes the same flags; `soa` warns and ignores them). The command line is CLI11's (`src/core/cli.cpp`): the options `soa` shares with the other programs are defined once (`common/include/soa/cli.h`: the rules, `--repo`, `--download`, `--standin-assets`, `-v`; `runtime/include/soaruntime/app/cli.h`: the window and the driving options, `--guest-cpus`, `--gdb`; `platform370/include/platform370/cli.h`: `--device-clock`, `--no-patch`, `--no-dst-fix`, `--lang`, `--voice-lang`, `--http`, `--lobby`, `--map-host`; `server/include/soaserver/cli.h`: the server options, `soa-server`'s too). A value-taking option given twice: the last one wins (`--shot`, `--do`, `--map-host`, `--live-check` collect); any error prints one line and exits 2. `soa --help` notes which removed `SOA_*` variable each flag replaced. `build/tests/cli/soa_cli_tests` checks every option against the parser this replaced.

**General**

| Option | |
|---|---|
| `-h`, `--help` | The options |
| `--repo DIR` | The source checkout that repo files are read from. By default it is found from the executable: `/proc/self/exe` is `build/port/soa`, so the root is two levels up. The first directory upwards that is a checkout (the root `CMakeLists.txt` and `common/CMakeLists.txt`: `soa::install::is_checkout`, the same for every program) wins; failing that, the working directory is searched the same way. |
| `-v`, `-vv` | Debug / trace logging |

**Client options**

| Option | |
|---|---|
| `--apk FILE`, `--lib PATH` | The 3.7.0 APK (default `<repo>/apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk`) and its `libSOA.so` (default: extracted once into `DATA/libSOA-3.7.0.so`) |
| `--data DIR` | The phone's data dir: game data, saves, and in-process the server's state (default `~/.local/share/soa-linux-370`; Windows `%LOCALAPPDATA%\soa\port-370`) |
| `--download PATH` (= `--download-dir`) | The client's asset fallback: `builtin_data/<rel>` assets the APK lacks from `<rel>` of the online game's 3.7.0 download (the zip, read in place, or an extracted folder); `--download-prefer` makes it win over the APK. Required with `--server inproc`, whose CDN serves it (default `work/SOA-3.7.0-canonical-data.zip`); off by default with `--server HOST`. |
| `--standin-assets DIR\|off` | Made-up **stand-in** files for `builtin_data/<rel>` assets that no real source has, after the APK and `--download-dir` (see "Stand-in assets"); `--server inproc` defaults it to `standin-assets` and its CDN serves them (`off` / `0` = none). |
| `--device-clock "YYYY-MM-DD HH:MM:SS"\|host`, `--no-patch`, `--no-dst-fix` | The phone's clock; no `service_stop_day` patch; times read as standard time, as shipped (platform370; `docs/client-changes.md` "Local time: daylight saving") |
| `--lang ja\|en` | The client's language (platform370, `docs/client-changes.md` "English mode"): `ja` (default) runs it as shipped; `en` sets its `CLanguage::Current` to en, so every file is tried as `name-en.ext` first (an English master, story and art from a server with `--english`); its hard-coded Japanese strings show new `port_en_*` master text and long lines break at spaces. With the in-process server it is to turn the server's English mode on too |
| `--voice-lang ja\|keep` | `ja` (default): `BAS:VoiceLanguage` = 0 in the phone's `Game.xml` before the client starts (the Japanese voice packs, no `-en` probe); `keep`: the save's value |
| `--guest-cpus N\|host` | The CPU count the game sees (default 8); see "Memory diagnostics" |
| `--natives all\|route\|none`, `--no-native` | Native replacements: `all` (default) = every registered one; `route` = only the in-process route's and the port's own hooks (the game's code under the JIT: the A/B for a native regression); `none` = pure JIT |
| `--natives-skip SUBSYS[,SUBSYS..]` | Leave these subsystems' natives (`src/native/<SUBSYS>/`) to the guest |
| `--http HOST:PORT`, `--lobby HOST:PORT`, `--map-host NAME[=ADDR]` | With `--server HOST`: soa-server's HTTP address (default `<host>:44380`), where lobby connections go, extra host names to resolve |
| `--size WxH`, `--landscape` | Initial window size. Default: portrait 9:16 at 90% of the desktop height (the game is a portrait phone game). `--landscape`: 16:9 instead. |
| `--render-size S` | The game screen: `desktop` (default: the window's aspect ratio, scaled up to fill the desktop), `window` (the initial window size) or `WxH`. The game draws its UI and 3D at this size (hi-res, the default; e.g. 810x1440 for a 729x1296 window on a 2560x1440 desktop), and the frontend scales it into the window. The test harness passes `window` so the pixels drawn don't depend on the host's monitor. |
| `--legacy-res` | The game's own resolution, as shipped: the UI at 720x1280 and the 3D scene in a 0.75 back buffer (540x960 on a 9:16 screen), scaled up, whatever `--render-size` (`docs/client-changes.md` "High-resolution rendering"). Also the case with `--natives none` and in `--selftest` (no natives) |
| `--render-scale S` | The UI at the game's 720x1280 and the 3D scene at S x 720x1280 (0.25..3; 1 = 720x1280, 1.5 = 1080x1920) whatever the window; excludes `--legacy-res` (which is 0.75). `--hires` is accepted and does nothing (hi-res is the default) |
| `--fullscreen` | Start in desktop fullscreen |
| `--headless` / `--windowed` | `--headless`: don't show the window. It is the runtime's hidden host window (`app::HostConfig::hidden`, as in `soa-emu --headless`): it still renders at the same `--size` / `--render-size`, so screenshots, `--do` and `--control` work and the frames are the same. `--selftest` is headless unless `--windowed`. |
| `--shot S:PATH`, `--do S:CMD`, `--control FIFO` | Scripted screenshots and input (see `soa --help`). Drive a `--control` instance with `control/soactl.py FIFO tap:X:Y wait:MS wheel:X:Y:DY shot:PATH ...`; the port's own commands are in "Control commands". |
| `--selftest [F]`, `--smoke`, `--list-native` | The self-tests (tests matching F), a quick library check, the native list |
| `--fake-server-schema FILE` | A dump of the response key schema at `CGame::OnInitialize` (`docs/api.md`; `--server inproc` only). The route's canned responses and their `--fake-server DIR` were retired on 2026-10-05 (`docs/history/fake-server-responses.md`): a request the local server has no handler for is answered `{}` and logged `no handler` |
| `--memstats [S]` | Memory snapshots in the log at every phase change, and every S seconds (see "Memory diagnostics") |
| `--live-check FAMILY[,..][:KEY[=VALUE]..]` | Check a native family against the guest during the run (`src/native/README.md` "Live checks"; families: `lib_sqlite`) |

**Server options** (the same flags as `soa-server`; only with `--server inproc`)

| Option | |
|---|---|
| `--server inproc\|HOST[:PORT]` | The game server: in-process (default) or `soa-server` (`--listen`, default port 44300). |
| `--db FILE`, `--master FILE`, `--gacha-pools FILE`, `--seed FILE`, `--seed-rng N`, `--new-player` | The state DB (default `DATA/server.sqlite3`), the 3.7.0 master DB, the reconstructed gacha pools (default `data/gacha_pools.sqlite3`), the save a new state is seeded from (3.7.0 or offline-game `Game.xml`; an existing state keeps its player; without one, after the repository's seed save, the client's own `DATA/data/shared_prefs/Game.xml` when it holds a player), a fixed RNG seed, no player (the new-player tutorial) |
| `--clock "YYYY-MM-DD HH:MM:SS"` | The server's clock starts there and runs on; without it event terms replay the calendar |
| `--start-coins N`, `--galaxy-pass` | Free coins of a new local player (default 300000); the Galaxy Pass, renewed when it runs out |
| `--enable-events`, `--event-keywords "a,b,!c"` | Also open, all year, every event area and gacha banner whose name matches the keywords (default the summer events `水着,夏,サマー,!福袋`), assets permitting |
| `--home3d-all` | Debug: clears `master_person.home3d_disable` in the client's master copy, so the 2D-only characters (2B, 9S, A2 and the other collab characters) get the 3D home (`docs/home3d.md`) |
| `--restore-tower` | Opens the tower (試練の遺跡), which 3.7.0 had closed: the server serves its areas and the client's tower hooks (`src/native/restore/restore_tower.cpp`) open the menu (`docs/client-changes.md` "Tower") |
| `--campaign-master-db FILE`, `--campaign-seed LABEL`, `--fail M:CODE[,..]`, `--surprise` | The campaign module's master DB and test seed, failing requests, forced surprise missions (test hooks) |
| `--log-packets DIR` | Every request and reply of the in-process route in `DIR/packets.log`, in soa-server `--log-packets`' form (the reply bodies and battle logs as `DIR/<n>-<name>.msgp`; `src/native/api/packet_log.h`); `tests/diff` compares it with soa-server's |

Controls:

| Input | Action |
|---|---|
| Mouse | Touch |
| Mouse wheel | Pinch zoom (up = spread fingers / zoom in, down = pinch / zoom out), centred on the cursor. Works in the 3D model viewer and pinchable UI; the home screen itself has no pinch zoom in the game. |
| Esc / Backspace | Android Back |
| F11 | Fullscreen |
| F12 | Screenshot, saved to the data directory |

When the game asks for text (e.g. a name), type it: a text box at the bottom of the game image shows it (and so does the window title), with a counter against the field's maximum. Left / Right / Home / End move the cursor, Backspace / Delete delete, Ctrl+V pastes (cut to the field's maximum and, in a numeric field, to digits), an IME composes in the box (its candidate window opens next to it). Enter confirms and Esc cancels. The box needs a font with Japanese glyphs (README.md, "Setup"; `--font PATH` picks one, `--font none` turns the box off). A click or Esc skips a movie.

## Run options

Every option that changes what a run does lives in one typed struct, `RunOptions` (`port/src/core/options.h`): `repo_dir`, `ClientOptions client` and `ServerOptions server`. `main` fills it once, before the game starts, from the command line (`core/cli.cpp`): settings are flags only (the `SOA_*` variables that were settings print one warning line naming their flag and are ignored; `docs/environment.md`), and the port never `setenv()`s game or run state (T0 `env-access`, `tools/check_env_access.py`: no environment access outside `soa/env.h`). Code reads them through `options()`. The window, the data dir, `--natives` and the control / test flags stay in `main`.

**`ClientOptions`**

| Command line | Field |
|---|---|
| `--download-dir DIR`, `--download-prefer` | `download_dir`, `download_prefer` |
| `--standin-assets DIR\|off` (inproc: `standin-assets`; `0` / `off` = none) | `standin_dir`, `standin_off` |
| `--fake-server-schema FILE` | `fake_server_schema` (the FakeApiCaller route; on with `--server inproc`) |
| `--guest-cpus N\|host` (default 8) | `guest_cpus` (0 = host) |
| `--memstats [S]` | `memstats` (1 = at every phase change, S > 1 also every S seconds) |

**`ServerOptions`**: `server::ServerConfig` itself (`server/include/soaserver/config.h`), its flags defined once for `soa` and `soa-server` (`server/include/soaserver/cli.h`). `config_from_options` (`src/native/api/server_adapters.cpp`) copies it into `server::config()` with the CDN's source from `ClientOptions` (`download_dir`, `standin_dir` / `standin_off`), the repo roots and the data dir.

| Command line (= `soa-server`'s) | Field |
|---|---|
| `--server inproc` | `enabled` |
| `--new-player` | `new_player` |
| `--db FILE` (inproc: `DATA/server.sqlite3`) | `db` |
| `--master FILE` | `master` |
| `--gacha-pools FILE` | `gacha_pools` |
| `--seed FILE` | `seed` |
| (no option; inproc: `DATA/data/shared_prefs/Game.xml`) | `client_save` |
| `--seed-rng N` | `has_seed_rng`, `seed_rng` |
| `--start-coins N` (default 300000) | `start_coins`: free coins (紋章石) of a new local player; an existing state keeps its balance |
| `--clock "YYYY-MM-DD HH:MM:SS"` | `has_clock`, `clock`, `clock_offset` |
| `--galaxy-pass` | `galaxy_pass`: the local player holds the Galaxy Pass (`pshop_galaxypass_001`), granted again whenever a player load finds it expired (`docs/server-rules.md` "Deep space") |
| `--enable-events`, `--event-keywords "a,b,!c"` | `enable_events`, `event_keywords` (empty = `kDefaultEventKeywords`; `docs/server-rules.md` "Enabling events by keyword") |
| `--restore-tower` | `restore_tower` |
| `--home3d-all` (debug) | `home3d_all`: the client's master copy offers the 3D home for every character (`docs/home3d.md`) |
| `--campaign-master-db FILE`, `--campaign-seed LABEL` | `campaign_master_db`, `campaign_seed` |
| `--fail M:CODE[,..]`, `--surprise` (test hooks) | `fail`, `surprise` |
| `--log-packets DIR` | `log_packets` (soa: `packet_log::open`; soa-server: its wire layer's log) |

The local server is the library in the top-level `server/` (`server/README.md`). It reads no run options itself: `main` calls `config_from_options` once the options are final.

The local server has two clocks (`docs/server-rules.md` "Time" and "Clock"): `clock_now()` (real time, or `--clock`) for the wallet, stamina and daily counters, and `event_now()` for dated content, which without `--clock` replays the service's calendar (today's month-day in the newest year 2016-2021 with an event term that day).

## Stand-in assets

Some content in the 3.7.0 master data refers to images that no longer exist anywhere: the online server had removed them before the last download, and the APKs never had them (e.g. the 2017 swimsuit pick-up gachas' banners). `standin-assets/` is an overlay of **made-up** replacements, laid out like the game's logical paths (`Image/etc2/<name>.aif` for `builtin_data/Image/etc2/<name>.aif`).

- **Lookup order:** the APKs, then `--download-dir`, then the overlay (`AssetManager::find_download`, `runtime/src/android/ndk.cpp`). A file in the overlay is used only when no real source has that asset, so real assets always win, even with `--download-prefer`. The same lookup serves the client's `AAssetManager_open` / directory listings and the local server's asset checks (`events::asset_exists`: event maps, Sphere 211, deep space, and `--enable-events`' banner gating), so content becomes visible exactly when its files are present. Nothing in the code names the content.
- **Switch:** on with `--server inproc` (default dir `standin-assets`; the in-process CDN serves them too), `--standin-assets DIR|off`. Listed in `docs/client-changes.md` as a data override: these are not the original art.
- **Contents today:** the Summer '17 pick-up gachas `gacha_pickup_role_0054` (常夏のミキ / 常夏のミュリア, `banner303`) and `gacha_pickup_role_0056` (常夏のレイミ / 常夏のソフィア, `banner310`): their list banners `banner_gacha_pickup_role_0054` / `_0056` (512×128) and pick-up panels `pickup_img_chara_1707_002`, `_003`, `_005`, `_006` (1024×512), all ETC2 RGBA8 like the real ones. With `--enable-events` both gachas are listed and can be drawn (their pools are in `data/gacha_pools.sqlite3`). Also the NieR:Automata rerun `gacha_pickup_role_0283` (２Ｂ / ９Ｓ / Ａ２, `banner_20200227_1002`): its list banner `20200227_chara_002` (512×128) and pick-up panels `pickup_img_chara_0015` / `_0016` / `_0017` (1024×512), opened by `--enable-events --event-keywords NieR` (`emulator/scripts/nier_demo.sh`).
- **Regenerating / adding more:** `tools/make_standin_banners.py [gacha id_label ...]` (needs Pillow, numpy and zstandard, e.g. in a scratch venv: `python3 -m venv /tmp/v && /tmp/v/bin/pip install pillow numpy zstandard`, and the IPAex Gothic font). For each gacha it draws every referenced banner / pick-up image that no real source has: a summer beach gradient, the pick-up names from the gacha title (`master_text`), rarity and role type, the dates, the characters' universe-chip portraits (`Image/etc2/u_chip_<cp>.aif` from the download) and a "STAND-IN" tag. It encodes them to the game's format (ETC2 RGBA8 into the AIF container of a real image of the same kind, with fresh GUIDs and a distinct texture id: the image header's +0x10 u32, by which the client caches textures, so two files sharing it show the same picture; then SLZ codec 5 and ADLD XOR, the inverse of `tools/aif2png`) and checks each file by decoding it again. Output is deterministic.

## Control commands

Port-only commands for `--control` (none is game behaviour), besides the shared ones (`tap:`, `drag:X1:Y1:X2:Y2[:MS]`, `wheel:`, `back`, `text:`, `type:`, `compose:`, `key:`, `shot:`, `wait:`, `quit`; `control/README.md`; the text-entry ones: `runtime/README.md`, "Text entry"):

| Command | What it does |
|---|---|
| `phase:N` | Switch to phase `N` from the game thread, as a menu button does (a menu phase closes its screen with `+0x20 = N`; others go through `CPhase::RequestSwitch`). `0xf` Battle, `0x11` Gacha, `5` Mission, `6` Deep space, `9` Item, `0xa` Shop, `0xe` Presentbox. Each phase change is logged as `I/port_debug: phase N`, which the scripts wait on. |
| `mission:LABEL` | The mission `CPhase_Battle` starts (`CParameterUI+0x1a0 = CHash32(LABEL)`), e.g. `mission:mf01_001 phase:0xf`: a battle without the mission map's UI (MissionStart / MissionEnd to the local server). |
| `call:SYMBOL[:ARG...]` | `guest_call` on the game thread; an `ARG` is an integer, `s=TEXT` (guest C string) or `f=FLOAT`. The result is logged (`I/port_debug: call SYMBOL -> X`). |
| `debugwin:W:H` | `CDebugWindows::Initialize` once, then `CDebugWindows::Progress` every frame, so `call:` can open the framework's debug windows (`CreateNewWindow`, `CreateTabWindow`, ...), which the release build never creates. |
| `clock:+SECONDS` | Moves the in-process local server's clock forward (`server::set_server_clock`), e.g. to bring deep-space expeditions home; the client follows with the next response's `data.Time`. |
| `uiset:OFF:VAL` | Writes the u32 `CParameterUI + OFF` = `VAL` from the game thread (port tooling). `uiset:0x140:5 phase:5` opens the mission menu on the extra dungeon (Sphere 211) without the home button; `2` is the tower. |
| `memstats[:TAG]` | A memory snapshot (`I/memstats`; "Memory diagnostics"). |

They run from the port's `CPhase::Progress` wrapper (`src/native/common/port_debug.cpp`), so they need the natives (`--natives route`, the default), not `--natives none` or `--selftest`.

## Tests and session scripts

**Which tests to run (tests/TIERS.md):** `tools/gate.sh T0` on every commit (the build and the fast checks, about a minute); `tools/gate.sh T1 --git-diff main` per change (T0, then what `tools/tests_for.py` picks for the changed paths: the replay corpora, the cheapest tests/diff shards and sessions that exercise the touched APIs; docs-only changes pick nothing); `tools/gate.sh T2` before reporting a batch (the full tests/diff, the broad session set, smoke, the emulator and viewer gates). `tools/tests_for.py PATH...` prints the selection and why. Every game client runs under the machine-wide slot pool (control/README.md "The slot pool"), so parallel runs queue instead of slowing each other down.

Every session script is a thin wrapper over a named session of the shared driver library (`control/run.py SESSION`, the sessions in `control/soadrive/sessions/`; control/README.md "soadrive"): it drives `soa` through `--control`, runs headless (`--headless`; `WATCH=1` in the script's environment passes `--windowed` and shows the window), fixes the server's RNG with `--seed-rng` (`SEED_RNG` overrides the script's seed), takes `<soa> <out-dir> <scratch-dir>` (the smoke test: `<soa> <out-dir> [baseline-dir]`) from any directory, and ends with a PASS or FAIL line and a matching exit status (`--target T` as the first argument runs a session against another program where it supports one: `control/run.py --list`). The sessions run the 3.7.0 client with the in-process local server (the default `--server inproc`, with `--log-packets <out-dir>/packets`) and check milestones in the packet log (`> Name` / `< NameRes`, as tests/diff), in the log (phase changes, the server's request lines; read with the same `LOG.pos` cursor `control/flowctl.py wait-log` keeps), in the server's state (`tools/server_state.py`, or SQL on `<scratch-dir>/data/server.sqlite3`) and in screenshots (`<out-dir>/shots`).

**The phone:** each session starts from the shared pre-downloaded phone (`work/phone-3.7.0`, linked into the run's data dir by `scripts/shared-phone.sh`; "The shared pre-downloaded phone" above). `SOA_PHONE=DIR` picks another phone, `SOA_PHONE=none` an empty one (the client downloads its 3 GB from the in-process CDN first, 4 GB with the episode packs: 3-4 minutes more). The client checks its manifests (Bulk, Individual and the episode packs ep1-3), and downloads what the phone lacks, e.g. the master the server edited for the run's options or clock (a 35 MB dialog the sessions answer). The sessions install the client save with its `BAS:DownloadEpisodeFlag` (7 = Episodes 1-3) cleared to 0 (`soadrive/targets.py` `session_client_save`, as `phone370_client_save` does for the remaining shell scripts), so they never fetch the episode packs (the shared phone carries them since 2026-10-02; with flag 0 the client ignores them); `SOA_EPISODE_PACKS=1` keeps the 7 (the client then downloads EP1-3, ~705 MB, 408 bundles, at its first data phase on a phone without them: the same dialog; on the shared phone it finds them and downloads nothing).

```sh
port/scripts/smoke.sh build/port/soa /tmp/smoke tests/smoke-base
port/scripts/battle_session.sh build/port/soa /tmp/battle /tmp/battle-tmp
control/run.py --list                       # the sessions, their targets and wrappers
```

**The steps every session shares** (`control/soadrive/flows/launch.py`, the same flow tests/diff runs on every target): the title (NoLoginStart answered; a communication-error dialog's リトライ), TAP TO START until `> Login`, the data check (the manifests, and the data dialog's buttons when the phone lacks something) or the full download, home (the notice board's web view); then `soadrive/popups.py` closes the notice board and the LOGIN BONUS popup (`flowctl.py login-popups` is its CLI). Taps that gate a phase change are resent until the expected log line appears (`Run.tap_log`, flowctl's tap-until: the game drops taps during fades and busy frames). The sessions are independent and can run in parallel (separate out and scratch dirs; about 2 GB RSS each); each takes a game slot for its lifetime and waits for one when the machine is full (control/README.md "The slot pool"). The shell scripts not converted (smoke, the debug-window sessions, `profile_extra.sh`, `smoke_vs_emu.sh`) still use `port/scripts/phone370.sh`.

| Script | What it checks | Time |
|---|---|---|
| `smoke.sh` (`smoke.py`) | title -> home -> キャラクター -> 装備・技・アシスト変更 (the character list) -> a character's detail -> 戻る -> ホーム -> その他, each screen matched against the baseline (below) | 4 min |
| `rebase_inproc_session.sh` | the in-process boot: title, Login, the data check or download, home, the login popups, the LOCAL00001 player | 3 min |
| `restore_session.sh` | home, a battle, a 10-draw, the server state after each | |
| `home_session.sh` | every home button (main, side, footer) by the phase or request it leads to | |
| `events_session.sh`, `tower_session.sh` (`--restore-tower`) | event missions; the tower's floor list, a floor's battle, the next floor unlocked | |
| `newplayer_session.sh`, `tutorial_session.sh` | a new player (`--new-player`): terms, name, CreatePlayer, the tutorial and its milestones (`tests/tutorial_milestones.txt`) | |
| `battle_session.sh` | ミッション (the episode list), `mission:mf01_001 phase:0xf`, MissionStart, the battle, MissionEnd, the result pages, home; the player's EXP in the server state | 3 min |
| `badges_session.sh [--target port-server]` | a 10-draw, キャラクター > 装備・技・アシスト変更 with the new characters' NEW badges, 戻る -> ClearNewCharacter (cleared in the server state and on screen), a second boot: still cleared | 5 min |
| `coins_session.sh [--target port-server]` | paid currency: a player with 50 stones, a single gacha draw: the sale-stopped dialog (platform370's patch) opens the coin shop -> the birth dialog (10009): 登録する (UpdateBirthYearMonth) -> the L set bought (CoinDepositCreate, the local store, CoinDepositAndroidUpdate: 980 paid + 80 free), home, a second boot: still there | 5 min |
| `gacha_session.sh` | the footer's ガチャ (GetGachaInData), its tabs, a 10-draw (SaleGacha), the presentation and the result; the coins debited in the server state | 3 min |
| `campaign_session.sh` | Episode 1 -> planet Mere -> 1-05 (mf01_001) through the mission map's UI, its battle, then the story mission it unlocks (mc01_030) played | 4 min |
| `party_session.sh` | the character menu's party sets 1 and 2 edited (UpdatePartySet), the home character (UpdateHome), a battle whose MissionStart takes set 2 | 4 min |
| `rental_session.sh` | a rental helper picked for 1-05 and fought as member 4; a second boot a day later (`--clock`): the rental bonus paid and its popup | 6 min |
| `growth_session.sh` | status strengthening to the level cap, evolution to ★6, limit break, weapon custom (a gear set, taken off, purified); the materials are written into the state DB before boot | 5 min |
| `deepspace_session.sh` (`--galaxy-pass`) | deep-space expeditions: started, returned (`clock:+1900`), collected, a quick return, two ships at once, the achievements' rewards | 5 min |
| `sphere211_session.sh` | Sphere 211 from the home button (`--seed-rng 605`: the map its taps are for): five battles with a rental, 帰還, the boss, floor 1 cleared, the reroll, floor 2, 帰還 | 17 min |
| `sphere211_continue_session.sh` | a lost Sphere 211 battle continued (100 coins) and retired, the stamina healed, the achievements | 7 min |
| `restore_favor_session.sh` | favor points set in the state DB between two boots; two taps on the home character (UpdateFavorByTap, level 1 -> 2), a battle's favor | 5 min |
| `restore_missions.sh` (`--clock 2021-05-25`) | a surprise-enemy battle (`--surprise`: its drops, the next mission unlocked), two steps of the step-up gacha gacha_pickup_role_1011 through the gacha screen, MissionStart refused at stamina 0 (the 10004 dialog) | 7 min |
| `episode_movie_session.sh [2\|3]` | Episode 2's (or 3's) pack downloaded through the client's own flow (episode list -> はい -> title -> TAP TO START -> the data phase: `version_latest_ep<n>` and its bundles; `SOA_EPISODE_PACKS=1`: the committed save's flag, at the login; on the shared phone, which carries the packs, the ask flow fetches the pack's bundles again and the save flow none), Episodeデータ管理, then the opening story through the world map: its movie plays to its end, EndMissionTalk | 7-8 min |
| `debug_session.sh`, `debug_input_session.sh` | the framework's debug windows (`debugwin:`, `call:`): created, dragged, tapped, activated in turn, closed; checked by the windows' ids and screenshot regions | 2 min |
| `profile_extra.sh` | a profiling flow over screens the others don't visit (the settings' six popups, help, titles, the character list end to end, a detail, shop, items, presents), each by its phase or request; `SOA_COVERAGE` / `SOA_PROFILE` into the out dir | 5 min |

**`episode_movie_session.sh` was blocked until 2026-10-02 (agent episode-data):** the server never sent Login's `LatestEpisodeVersion`, so the 3.7.0 client's episode count (CParameterManager+0xb6f0) was 0: Episodeデータ管理 listed nothing, the episode list's はい went back to the title but the data phase only checked `version_latest_Bulk` / `_Individual`. With the key (`master_global.latest_episode_version` = 3) the client lists EP1-3 and downloads a pack when asked (docs/server-rules.md#cdn); no client change. The script now has the client download the pack itself (by default the run's save has `BAS:DownloadEpisodeFlag` 0, so the pack is fetched only after the episode list's はい; `SOA_EPISODE_PACKS=1`: the save's 7, all three packs at the login).

**`tests/diff/run.sh [FLOW...]`: the port against the emulator** ([`tests/diff/README.md`](../tests/diff/README.md)). Three flows (`seeded`: login, popups, a campaign battle, a 10-draw, home; `tutorial`: the new player to home; `event`: the summer event's story and battle with `--enable-events`) run on three targets, `emu` (soa-emu + soa-server, the reference), `port-server` (`soa --server` + soa-server) and `port-inproc` (`soa`, the in-process server, with `--log-packets DIR`: the route's requests and replies in soa-server's packet-log form), each against a fresh state with the same seed, RNG seed and clock, driven by the same taps and milestones. Each port target is compared with the emulator: the packet logs (`tools/compare_packets.py`), the server state at the end (every table, times masked), the milestone screenshots by RMSE; `OUT/<flow>/report.txt`, exit 1 on a difference. All flows and targets run at once, bounded by the slot pool (the full flows: about 17 minutes, was 30 run one flow at a time). It's the regression gate for the rebuilt natives (PLAN.md task 6). **Shards** (`tests/diff/run.sh login battle gacha tutorial-entry tutorial-scene tutorial-battle tutorial-home`, or `shards`) are 2-5 minute parts of the flows, the tutorial's stages started from a prepared server state, compared the same way: the per-change gate that `tools/tests_for.py` picks from.

`port/scripts/coverage_diff.py RUN` ranks the families a run executes that the smoke and profiling sessions don't. `port/scripts/selftest_resilient.sh` runs the full `--selftest` past crashing tests.

**Removed with the natives (P5a, 2026-10-01):** `apinotify_live.sh` (it compared the native CApiNotify handlers with the guest's through a FakeApiCaller drive hook; both are gone), `growth_drive.sh` (the same drive hook; `growth_session.sh` reaches the growth APIs through the real screens, which the offline build lacked), `selftest_battle.sh`, `selftest_home.py` and `selftest_screens.py` (they ran the live selftests of the dumped natives, `battle-ui/`, `models/` and `screen/a2c-live`, on a live screen; and in `--selftest` no natives are installed, so there is no in-process server route, no phase log and no control commands: the client can't get past the title). `SOA_SELFTEST_START_FILE` (the selftests start once that file exists) stays in `main.cpp` for the rebuilt natives' live tests.

### The smoke baselines

`smoke.py` compares each screen with `tests/smoke-base/NN-name.png` (committed since 2026-10-03; ImageMagick RMSE on a 182x324 copy, at most 0.08, and 0.12 for the home screens: the home character animates and the mascot says a random line). The run is otherwise deterministic: the shared phone, the committed client save, the local server seeded from `data/saves/seed/Game.xml` with `--seed-rng 1` and its clock at `SMOKE_CLOCK` (default 2026-09-30 12:00:00, so the stamina, the login bonus day and the open events are the same every run). The way from the title to home is driven by log lines (the notice board and the LOGIN BONUS popup between them aren't compared); the screens from home on are. Without a baseline argument the run's screenshots become a new baseline.

- **The 3.7.0 baselines** (2026-10-01, P5a) were made that way from `build/port/soa` (the 3.7.0 client, `--natives route`) and checked with `port/scripts/smoke_vs_emu.sh OUT`, which drives `soa-emu` (the same client with no natives, against `soa-server` with the same seed, RNG seed and clock) through the same screens with the same taps. Every screen matches. soa-emu's RMSE against the baseline (two runs): 01-title 0.025 / 0.019, 02-home 0.109 / 0.116, 03-charmenu 0, 04-charlist 0, 05-chardetail 0.011, 06-closed 0, 07-home 0.097 / 0.119, 08-other 0.039 / 0.032 (the title's TAP TO START blinks; the home character's pose and the mascot's line differ). Four smoke runs against them: 01-title 0.014-0.018, 02-home 0.084-0.111, 03-charmenu 0-0.021, 04-charlist 0, 05-chardetail 0.010-0.012, 06-closed 0, 07-home 0.030-0.090, 08-other 0.031.
- **The offline port's baselines** (its title -> character list -> detail -> other flow) are kept in `work/port-test/smoke-base-380/` (380-ok: the pre-rebase baselines' directory).

How far battle, gacha and the debug windows got on the pre-rebase port (offline build, 2026-09-28) is in [`docs/history/notes-3.8.0.md`](../docs/history/notes-3.8.0.md) "From port/README.md".

## Saves

Saves are Android SharedPreferences files in the same format as on the phone: `<data>/data/shared_prefs/Game.xml` and `Aska.xml`. The save editor in `soa_save/` works on them unchanged. To bring a phone save over, copy the phone's `Game.xml`/`Aska.xml` there. You can also use a generated one such as `saves/Game_all_characters.xml`.

## Known limitations

- **Sound** that the APK lacks (most BGM, the talk-scene sounds) is in the 3.7.0 download, which the client fetches from the local server's CDN like any game data.
- Web views (news, terms text) and external links aren't shown; they're only logged. The notice board is the exception: the local server's page is drawn as HTML over the game by the web view (libsoawebview, litehtml; drag or wheel scrolls, a tap follows a link), or as text in the popup when no font is found (`docs/webview.md`, which has the plan for the rest).
- The game lays out its UI and allocates its render targets once, at startup (phones never resize). A window resized to a different aspect ratio is letterboxed; restart to render at a new aspect ratio.
- Linux desktops only: X11 or Wayland, through SDL2. SDL2 prefers X11 when both are there (XWayland); `SDL_VIDEODRIVER=wayland` runs natively on Wayland. Headless runs under Wayland present offscreen (`runtime/README.md`, "Graphics").
