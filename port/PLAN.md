# Plan (current)

Written 2026-10-01, after the 3.7.0 rebase merged into `linux-port` (e5cdcbc). The rebase's own plan, with its revisions, is [`docs/history/PLAN-rebase-370.md`](../docs/history/PLAN-rebase-370.md); its inventory is [`docs/history/REBASE-370.md`](../docs/history/REBASE-370.md). Earlier plans and status documents are in `docs/history/`. What is left, in one list: [`REMAINING.md`](REMAINING.md).

## Where things stand
- **The port (`soa`) runs the 3.7.0 client:** the library and the single APK from the 3.7.0 APK, plus the 3.7.0 download. Two server modes:
  - `--server inproc` (default): the FakeApiCaller route into the server library, with the CDN served in memory (no sockets);
  - `--server HOST[:PORT]`: the client's own network code against `soa-server`.
- **Natives start fresh:** the old ~18,000 were dumped. 301 remain: the in-process route, the phase observer, the tower, the notice-board webview. The pre-rebase port (the offline build) with all its natives is the tag `pre-rebase-370` (19a08b5).
- **Programs:** `soa` (port), `soa-server`, `soa-emu` (3.7.0 emulator), `soa-viewer` (3.8.0 viewer). Libraries: `runtime/`, `server/`, `platform370/`. One CMake build at the root.
- **Green on `linux-port`:**
  - `soa --selftest` 96/96, `soa-server --selftest` 87/87;
  - in-process to home, including the full 1,032-file download;
  - the restore, events, home, tower, newplayer and tutorial sessions;
  - the out-of-process packets equal `soa-emu`'s;
  - the emulator and viewer boots.

## Tasks, in order
| # | Task | Scope | Status |
|---|---|---|---|
| **1** | **D11: dependencies through vcpkg** | below | ✅ done (b2f05d3) |
| **2** | **P5a: the test baseline on 3.7.0** | below | ✅ done (22d4682) |
| **2b** | **Faster test setup: a shared, linked pre-downloaded 3.7.0 phone** | below | ✅ done (45b5403) |
| **3** | **P5b: `tests/diff/`, port-vs-emulator differential flows** | below | ✅ done (32ff1d9; `tests/diff/README.md`) |
| **4** | **P3 + P4: offline-build cleanup and references** | below | ✅ done (25fd054, 7940bac; `tools/check_no_380.sh` strict since e229364) |
| **4b** | **Server code: readability, then the database schema** (`server/PLAN-readability.md` R0-R20, then `server/PLAN-schema.md` S0-S12; R12/R17 after S4/S9) | the two plans | 🔄 resumed 2026-10-03: readability phase 1 done (R0-R11, R13-R16, R18; 67db9de); next on resume: one full tests/diff over the phase, then schema S0-S12, then R12, R17, R19 |
| **5** | **Rebuild tooling, together with the control-script consolidation** (`control/PLAN-consolidate.md`, incl. the runtime's GDB stub) | below | ✅ done 2026-10-03: decomp --into, per-subsystem scaffolding (classes + methods), the GDB stub, the rebuild queue (port/REBUILD-QUEUE.md); the consolidation (control/soadrive, run.py, thin wrappers, fail fast) |
| **5b** | **W: native Windows runner** (the user, 2026-10-02: before N) | below | 🔄 phase 1 ✅ (2026-10-03: every program builds, soa.exe --selftest and soa-server.exe --selftest pass on Windows, soa-emu.exe logs in); phase 2 ✅ (2026-10-03: the TCP control channel, soadrive on Windows, the restore session, the emulator's seeded session, the viewer's boot and the tests/diff shard login pass on Windows (gate `win:*`), the launchers); left: Wine CI, a real Windows machine, the other sessions and shards there |
| **6** | **N: rebuild the natives** | below | ⏳ ongoing after 5b |
| **7** | **H: trim the server hooks** | below | ✅ done with P3 (25fd054) |

### 1. D11: dependencies through vcpkg
- **vcpkg in manifest mode** (`vcpkg.json`) on Linux and Windows. **No source-build fallback.**
  - Ports: `boost-headers`, `zlib`, `sqlite3`, `zstd`, `libogg`, `libvorbis`, `sdl2`, `openssl`, `egl-registry`, `opengl-registry`; later `angle` on Windows.
- **CMake `FetchContent`, pinned (URL + hash),** for what vcpkg lacks:
  - dynarmic, at today's commit;
  - IJG libjpeg 9, built static with our own small CMake file. vcpkg only has libjpeg-turbo, which isn't bit-exact with the game's 9b.
- **Linux prerequisites vcpkg can't replace,** documented as `apt install`: Mesa EGL/GLES, and the X11/Wayland/ALSA/PulseAudio dev headers that `sdl2` needs.
- **Retire:** `scripts/fetch-deps.sh`, `deps/`, `third_party/` (done; the `port/deps` / `port/third_party` links are deleted; the root `deps/` and `third_party/` stay on disk until no worktree builds with them). `scripts/build.sh` = configure with the vcpkg toolchain + build.
- **Gate:**
  - a clean-checkout build with no `deps/` or `third_party/`;
  - `--list-native` identical;
  - full selftests;
  - in-process to home, the restore session, `soa-server --selftest`;
  - emulator and viewer boots (D11 changes the root build).

### 2. P5a: the test baseline on 3.7.0
- **Smoke:** new baselines (screenshots) from the 3.7.0 port, checked screen by screen against `soa-emu`'s. They are committed in `tests/smoke-base/` (since 2026-10-03; were untracked in work/port-test/); the pre-rebase ones stay local (untracked; see port/README.md).
- **Adapt the session scripts not yet on 3.7.0:** battle, gacha, campaign, party, rental, growth, deepspace, sphere211 (+continue), debug, debug_input, episode_movie, restore_favor, restore_missions, apinotify_live, profile_extra, `selftest_*`. Use the `SOA_PHONE` pre-downloaded phone (`port/scripts/phone370.sh`), log-line waits, and tap flows where they relied on deleted debug natives. Delete scripts whose purpose went with the dump, with a note.
- **Gate:** every adapted script passes twice, headless, run in parallel.

### 2b. Faster test setup (before P5b)
- **One shared pre-downloaded 3.7.0 phone,** built once in a fixed place, used by default by the port, emulator and demo scripts. Today each `SOA_PHONE` run copies ~3 GB, and without it the client downloads everything again (3-4 min).
- **Linked, not copied:** symlinks to the shared download data. First check how the runtime writes downloads: files the client may write in place are copied, read-only data is linked.
- **Gate:** the sessions pass, and the shared phone is unchanged after a run (checksums).
- **Done (port/fast-phone):** `work/phone-3.7.0` (`scripts/make-phone-370.sh`, `check-phone-370.sh`, `shared-phone.sh`); hard links, not symlinks (the strace: only `version.bin` and `manifest/` are written in place, everything else write-new-then-rename; `port/README.md` "The shared pre-downloaded phone"). Prepare 0.9 s / 14 MB per run vs 3.9 s / 3.2 GB for `cp -a`.

### 3. P5b: `tests/diff/` (port vs emulator)
- **Each flow runs twice:** once in `soa-emu` and once in `soa --server`, each against a fresh `soa-server` with the same seed (`data/saves/seed/Game.xml`, `--seed-rng 1`).
- **Flows:** seeded login/popups/battle/10-draw; the new-player tutorial (`tests/tutorial_milestones.txt`); an event mission.
- **Compared:**
  - packet logs (ordered requests and arguments, minus transport and timing; `tools/compare_packets.py`);
  - `tools/server_state.py` with times masked;
  - milestone screenshots by RMSE (extend `tools/compare_tutorial.py`).
- **Use:** the regression gate for every native rebuilt in 6.
- **Done (port/p5b-tests-diff, 2026-10-02):** `tests/diff/run.sh [FLOW...] [--target emu,port-server,port-inproc]`: the flows `seeded`, `tutorial` and `event` on three targets (soa-emu + soa-server, `soa --server` + soa-server, the in-process `soa`), each fresh with the same seed, `--seed-rng 1` and `--clock`; compared with the emulator on the packet logs (the in-process route got `soa --log-packets`, soa-server's form), the server state at the end and the milestone screenshots; `OUT/<flow>/report.txt`. Gate: two full runs PASS in a row (about 28 minutes each: seeded ~7.5, tutorial ~14, event ~7 min, targets in parallel); an injected `--start-coins` difference FAILs. Found and fixed: `GetMissionList` was never sent on the FakeApiCaller route (`docs/client-changes.md`) and had no server handler (`docs/server-rules.md`).

### 4. P3 + P4: offline-build cleanup and references
- **P3:**
  - re-audit `docs/client-changes.md` and `docs/server-rules.md` for entries that only existed for the offline build (the inventory lists 22 client changes to delete);
  - remove leftovers: the unused `comma_listed` and its test, and the `InGameHooks` login-bonus popup if decision 1 drops it;
  - `scripts/run-port-with-server.sh`, which starts `soa-server` like `run-emulator-370.sh`.
- **P4:**
  - 3.8.0 references (1,107 lines in 130 files) leave port code, tools and living docs; they stay only in `emulator-viewer/` and its run script;
  - tools default to the 3.7.0 lib;
  - history docs move to `docs/history/`, each with a one-line note: `docs/history/libsoa-3.7.0-vs-3.8.0.md` and the offline-build sections of `docs/notes.md` (now `docs/history/notes-3.8.0.md`) (the stale `port/*.md` files already moved on 2026-10-01);
  - `data/basmaster-3.8.0.sqlite3` and the offline build's Ghidra project stay, for the viewer (`emulator-viewer/`) and history.
- **Gate:** a grep check that no 3.8.0 reference remains outside `emulator-viewer/` and `docs/history/`.

### 5. Rebuild tooling, with the control-script consolidation
- **The consolidation (the user, 2026-10-03: approved, done together with this task):** `control/PLAN-consolidate.md`'s steps: the shared driver library `control/soadrive/` (seeded by `tests/diff/diffdrive/` and the faster-tests work: slot pool, shards, `tools/tests_for.py`, `tools/gate.sh` tiers), the named flows for both targets (port and emulator), the session scripts as thin wrappers, and step 7, **a GDB remote stub for the guest in the runtime** (`--gdb HOST:PORT`, attachable from soadrive to read guest state at a milestone — what the native rebuild uses to compare natives with the guest). It starts after the faster-tests branch merges (they touch the same scripts).
- **`tools/decomp.sh` / `decomp_at.sh --into <subsystem>[/<topic>]`** write stamped decompiles to `port/decomp/<subsystem>/<topic>.c`. Without it they write scratch output to `work/decomp/`. ✅ (2026-10-03; `tools/decomp_stamp.py`)
- **The GDB stub** (`control/PLAN-consolidate.md` step 7) ✅ (2026-10-03): `--gdb HOST:PORT` on soa / soa-emu / soa-viewer, `control/gdbclient.py` for tests, `control/gdbinit-soa`; runtime/README.md "Debugging the guest with gdb". Attaching it from `soadrive` is part of the consolidation.
- **Per-subsystem scaffolding:** `port/src/native/<subsystem>/README.md` + `<subsystem>_layout.h`, and `port/decomp/<subsystem>/symbols.tsv`. ✅ (2026-10-03) `tools/subsystem.py new|list|check|skeleton|export-types` (`skeleton`: the class declarations from `symbols.tsv`, methods attached, virtuals in vtable order; members bound with `NATIVE_METHOD`, `native/common/native_method.h`), a `subsystem.cmake` per subsystem, `scope.txt`, `types.json` for Ghidra (`tools/ghidra_apply_types.sh`, the integrator, serially); no shared file per subsystem (`control/tests/test_subsystem.py`); the workflow: `port/src/native/README.md` "Per-subsystem workflow".
- **A fresh profile of the 3.7.0 port (in-process server)** (`SOA_PROFILE` / `SOA_COVERAGE`, `port/scripts/profile_report.py`, `remaining.py`) to rank subsystems by guest time. The output is the rebuild queue. ✅ (2026-10-03) [`REBUILD-QUEUE.md`](REBUILD-QUEUE.md): login, battle, gacha and a story flow; per subsystem its guest time, level and measured dependencies, the waves (`port/scripts/rebuild_queue.py`).

### 5b. W: native Windows runner (before N)
- **Scope (the user, 2026-10-02): all three programs run natively on Windows: the port (`soa.exe`), the 3.7.0 emulator (`soa-emu.exe`) and the 3.8.0 viewer (`soa-viewer.exe`),** plus `soa-server.exe`, since the emulator needs it. They share `runtime/` and `platform370/`, so most of the work is common; each program's own code (the port's natives and in-process server, the emulator's networking to `soa-server`, the viewer's offline XAPK path) gets its Windows check too.
- **Done when:** each of the four builds on Windows (MinGW-w64 clang + vcpkg) and passes its existing checks there:
  - `soa --selftest`, `soa-server --selftest` and the runtime tests;
  - the port's restore session, the emulator's boot and seeded session, and the viewer's boot, headless;
  - first under Wine in CI, then once on real Windows;
  - plus the user-facing launchers (`scripts/run-*.sh` equivalents as `.cmd`/PowerShell, or documented commands).
- **Build:** MinGW-w64 (clang) in the same CMake build, dependencies through vcpkg (D11), ANGLE for EGL/GLES.
- **Port:** the HLE libc layer (289 import thunks: files, Winsock, time, threads) and guest memory / fault handling (`VirtualAlloc`, vectored exceptions).
- **Audit** the uses of `long` (64-bit on Linux, 32-bit on Windows); harmless on Linux, so it can land early.
- **CI:** the runtime tests under Wine.
- **Head start:** the window and GL contexts are SDL's since `port/sdl-egl` (the guest's EGL is emulated over SDL's GLES contexts, no X11), so on Windows the same code runs on SDL's Windows video backend with ANGLE providing GLES; vcpkg already has every dependency (D11).
- **Why before N:** natives written after W are tested on both platforms from the start, and W's `long` audit and libc-layer port touch code N would otherwise grow on top of.
- **As built, phase 1 (port/win-runner, 2026-10-03):** README.md "Windows" has the commands.
  - **Build:** `scripts/build.sh --windows` → `build-win/`: llvm-mingw (clang 23, libc++, UCRT; `~/tools/llvm-mingw` or `$SOA_LLVM_MINGW`) through `cmake/toolchains/llvm-mingw-x64.cmake` chainloaded by vcpkg; a new overlay triplet `cmake/vcpkg-triplets/x64-mingw-static.cmake` (release only, Linux's sqlite3 options, litehtml's missing `<cstdlib>`; `x64-linux.cmake` untouched; **every edit of it rebuilds all MinGW ports, about an hour**); the vcpkg feature `angle`. Every part builds: `soa.exe`, `soa-server.exe`, `soa-emu.exe`, `soa-viewer.exe`, the tests, `aif2png.exe`, `soa-webview-render.exe`; static `.exe` files.
  - **Checked on Windows** (run from WSL through interop, staged by `scripts/windows-stage.sh` into `C:\soa-win`: SQLite can't lock over `\\wsl.localhost`, a worktree's `work/` link isn't followed): `soa-server.exe --selftest` 107/107; `soaruntime_tests.exe` PASS; `soa_env_tests.exe` all passed; `soa.exe --selftest` 120/120 (the game boots in process); `soa.exe` and `soa-emu.exe` render the title through ANGLE (Direct3D 11, ~40 fps headless); `soa-emu.exe` against `soa-server.exe` connects through the net redirect, NoLoginStart, StartBridge over HTTP, Login, and shows the Episode data screen (tapped through `--control` as a named pipe).
  - **Not run on Windows yet:** the sessions (restore, the emulator's seeded session: they need `control/soactl.py` to write a named pipe instead of a FIFO), the full data download, tests/diff, smoke, `soa-viewer.exe` (needs `work/extracted` staged), Wine (not installed here; the runtime tests under Wine for CI are still to do), a real Windows machine (only WSL interop).
  - **Where the platform code is:** `common/` (`soa_compat`, linked by the server, the runtime, the web view): `soa/sock.h` host TCP sockets (server/net, platform370's HTTP client); `common/win32/posix_compat.h`, force-included into those targets on Windows, `#define`s the POSIX names MinGW lacks onto `soa_*` functions (`realpath` with `/` and `/proc/self/exe`, `rename` that replaces, `pread`, `strptime`, `setenv`, `gettid`, `lstat`=`stat`, `getuid`, `malloc_usable_size`, `mkdir` with a mode) plus binary stdio (`binmode.o`), NOMINMAX / WIN32_LEAN_AND_MEAN / `_FILE_OFFSET_BITS=64`. Runtime: `core/host_mem` (VirtualAlloc, file mappings, `mapped`), `core/host_fd` (on Windows the guest's descriptor table: CRT files, Winsock sockets, in-process pipes / eventfds, poll), `core/elf64.h`, `hle/libc_win32.cpp` (64-bit `long`, UTF-32 `wchar_t`, one C locale, bionic's `tm` / `timeval` / `timespec`, sysconf, futex over WaitOnAddress, open flags, mmap / mremap anonymous), `hle/net_win32.cpp` (BSD sockets over Winsock: constants, options, errno, hostent, select), `hle/guest_errno.h`. GL: SDL loads EGL from the `.exe`, which exports the static ANGLE's EGL (`runtime/src/app/egl_exports_win32.def`). dynarmic's bundled fmt / mcl need three Windows-only fixes for clang 23 + libc++ (`cmake/deps.cmake`, `cmake/dynarmic-win/`). `jni/jvm.h` TaggedAlloc is 256-aligned under libc++ (its `std::function` is 16-aligned). Diagnostic: `SOA_FAULT_LOG=1` logs every first-chance fault (module offsets, guest pc).
  - **Known gaps (Windows):** `popen` (refused, as on Linux), `swprintf` / `guest_wformat` (host `wchar_t` is 16-bit: unported), `sscanf` / `fscanf` hand the guest's format to the host (a `%ld` writes 32 bits on Windows), mmap only anonymous and `munmap` only of whole mappings, `rand()`'s RAND_MAX is 32767, CRT errno values above 34 not all translated, `select` only for descriptors < 1024 (the table keeps them small), wide ctype ASCII only, no file nanoseconds or symlinks, no SOA_PROFILE_HOST host sampling or SIGUSR1 dump, no GDB stub (`--gdb` refuses; its test is skipped), `--start-coins` (port/src/main.cpp) parses with `strtoul`, which saturates at 2^32-1 there (a `long` audit leftover in option parsing, left to env-flags' area), IPv6 guest addresses aren't redirected by platform370's net map (IPv4 is).
  - **Next:** `control/soactl.py` and the session scripts on a named pipe (or a TCP control port) so the restore / seeded sessions run against the `.exe` files; stage `work/extracted` for the viewer; the runtime tests under Wine in CI; the gaps above as the sessions hit them (the "unimplemented import" thunk and `SOA_FAULT_LOG` name them).
- **As built, phase 2 (port/win-phase2, 2026-10-03):** README.md "Windows" has the commands.
  - **Passing on Windows** (from WSL through interop, the stage `C:\soa-win`): `win:battle-gacha` (the port's restore session, `soa.exe` in process: login, popups, mf01_001 cleared, a 10-draw debited 300000 -> 297500), `win:seeded` (`soa-emu.exe` against `soa-server.exe`: every milestone, the battle log decoded by the server, the draw in the state), `win:viewer-boot` (title, the offline NoLoginStart, terms), `win:shard-login` (the tests/diff shard `login` with all three targets Windows programs: packets, end state and screenshots as on Linux); the launchers `scripts\windows\run-port.cmd`, `run-emulator-370.cmd` (+ `.ps1`: starts and stops `soa-server.exe`), `run-viewer-380.cmd` reach the title. Linux T0 green throughout.
  - **The control channel:** `--control tcp:HOST:PORT` (runtime/src/app/host.cpp, both platforms; port 0 logs the one it took); the Linux FIFO and the Windows named pipe stay. WSL's mirrored networking shares 127.0.0.1, so soadrive on Linux drives a Windows client over it (`fifo.py`; `soactl.py tcp:...`).
  - **soadrive on Windows** (`control/soadrive/winhost.py`): a `.exe` binary makes the run a Windows run: the staged programs (refreshed from `build-win/` when newer; a running one is never replaced: the new build goes beside it), the stage's data, Windows paths, the phone and the server's state dir on the Windows drive (`STAGE/run/soadrive/`, linked back into the run's dirs: SQLite can't lock over `\\wsl.localhost`), the shared phone (staged by `scripts/windows-stage.sh --phone`, files.txt re-stamped: the drive keeps whole-second mtimes) hard-linked by `scripts/windows/link-phone.ps1` (CreateHardLink: ~30 s with the stamp check, where `cp -al` through drvfs took ~10 min), state dumps from a snapshot of the DB + WAL, ANGLE's D3D11 device loss labelled as a host GPU failure. The slot pool and the fail-fast checks apply unchanged. `viewer_lib.sh` does the same for `soa-viewer.exe` (`--viewer` stages the XAPK).
  - **Mirrored-networking ports:** a port bound in WSL (even to test it) stays refused to Windows for a while, and WSL's ephemeral range (ip_local_port_range) is reserved for WSL; Windows programs get port 0 (control) or untested ports below that range (`soa-server.exe`, retried on WSAEADDRINUSE).
  - **Gaps fixed:** `fopen` of a directory for reading (the client's check of its download dir before the data check; the CRT refuses: a NUL stream stands in), `sscanf`/`fscanf` `%ld` (-> `%lld` on LLP64), `rand()` (glibc's TYPE_3 generator on Windows: RAND_MAX 0x7fffffff and glibc's generator; the sequence matches Linux's while nothing host-side calls `rand()` in between, since on Linux the guest shares glibc's state with the host code), `--start-coins` (`strtoull`).
  - **Default data dirs** (the user, 2026-10-03): `%LOCALAPPDATA%\soa\port-370`, `emulator-370\phone`, `viewer-380` on Windows (`common/include/soa/paths.h`; Linux unchanged); before, a missing HOME put them under the launch dir's `.local\share\` (not migrated: README.md "Windows").
  - **Gate:** `tests/tiers.json` `win:battle-gacha`, `win:seeded`, `win:viewer-boot`, `win:shard-login` (T2, kind `platform`: never picked by tests_for.py; `requires: build-win/CMakeCache.txt`, else SKIP: tools/gate.py's new `requires`), all through `scripts/windows-test.sh TEST OUT TMP` (the incremental Windows build of what it runs, `windows-stage.sh --quick`, the Linux session with the `.exe` files).
  - **One stage per checkout at a time:** `C:\soa-win` is shared by every worktree; `windows-test.sh` restages the tracked files and `staged_binary` replaces an idle staged `.exe`, so two worktrees running `win:*` at once test mixed trees. Use `SOA_WIN_STAGE=/mnt/c/soa-win-NAME` per worktree (its own `--phone --viewer` staging: ~10 min, 4 GB of copies). `staged_binary`'s fallback for a running `.exe` (a sibling `NAME.<mtime>-<size>.exe`) was never exercised.
  - **Enabling `win:*` in T2 on main:** the main checkout has no `build-win/` (the tests SKIP): `scripts/build.sh --windows` (minutes with the vcpkg binary cache; the first configure without it about an hour), then `scripts/windows-stage.sh --phone --viewer` once (~10 min).
  - **Still open (Windows):** the full data download through the in-process CDN (the sessions use the shared phone; not needed by these flows), the other tests/diff shards and flows on the Windows targets (any should run as `login` does: `SOA=...exe SOA_EMU=... SOA_SERVER=... tests/diff/run.sh FLOW`), the other sessions (those that open the server's DB themselves: party, favor, missions, deepspace, tower, the Sphere ones, tutorial, need winhost's snapshot too), Wine CI, a real Windows machine; the phase-1 gaps not hit by these flows: `swprintf` (16-bit host `wchar_t`), file-backed mmap / partial munmap, errno values above 34, IPv6 guest addresses in platform370's net map; `Proc`'s 6 GB RSS cap can't see a `.exe` (only its interop process); headless frame rate ~33-45 fps on this machine (60 on Linux), no step timed out on it.

### 6. N: rebuild the natives
**Parallelism (the user, 2026-10-03: "parallelize as much as reasonably possible"; N still starts after all of W):**
- **Many agents at once, one per subsystem** (worktree off `main`, its own `port/src/native/<subsystem>/` and `port/decomp/<subsystem>/`), as many as the machine carries: the slot pool's 12 clients and the memory gate bound the test runs, not the agent count.
- **Pipelined by stage:** type-recovery agents (structs + `static_assert`s + Ghidra types) run a wave ahead of the code agents for the same subsystem, so a subsystem's code starts as soon as its leaf types land; leaf subsystems (values, containers) and independent ones run side by side.
- **Independent tracks from day one:** the library boundaries (zlib, IJG libjpeg, SQLite, libVorbis/ogg, zstd, libc++: host libraries via vcpkg / `FetchContent`), the Bullet version pin, and `Framework::Cocos`, each its own agent.
- **No shared hot files:** each subsystem registers its natives and sources through its own CMake fragment / registration file (task 5's scaffolding makes these per subsystem), so parallel branches don't conflict on one list; `native/common/` changes go through small separate commits merged first.
- **Ghidra:** agents don't write the committed Ghidra project concurrently; each exports its types/names as a per-subsystem script or archive under `port/decomp/<subsystem>/`, and the integrator applies them to the project serially.
- **Gates:** `tools/gate.sh T0` per commit; per subsystem its differential tests, the live check at 0 mismatches (`--live-check`), and `T1 --git-diff main`; T2 once per wave of merges. The integrator merges continuously (T0 on the merged `main`, then pushes).
**How:**
- **Readable C++ from the Ghidra decompile; no new a2c translations.** Regenerating the existing a2c files as a reference or fallback is still allowed.
- **Types first:**
  - recover each class or struct as a C++ struct with `static_assert`ed offsets before porting the code that uses it;
  - order leaves first: values, then containers, then objects, then managers and phases;
  - unknown bytes become named padding, never offset arithmetic;
  - **classes with their methods attached, not structs + free functions** (the user, 2026-10-03): the guest's `Class::Method` becomes a member of the recovered class (constructors, virtuals in vtable order, statics as static members); when porting makes it possible, existing struct + free-function natives are rewritten that way;
  - mirror the structs as data types in the committed Ghidra project.
- **Among subsystems whose types are ready, hottest first** (the profile from 5: [`REBUILD-QUEUE.md`](REBUILD-QUEUE.md), the ranking and the dependency waves).
- **Every native gets** differential tests against the 3.7.0 guest and a live check at 0 mismatches. The `tests/diff/` flows stay green.

**Code organization:**
- one subsystem per folder, with a `README.md` (including the RE notes) and a public header;
- files by responsibility, named for what they contain;
- tests next to the code; generated code in `gen/`; shared helpers in `native/common/`;
- small commits by path.

**Reverse-engineering storage:**
- code in `port/src/native/<subsystem>/`;
- decompiles and `symbols.tsv` as data in `port/decomp/<subsystem>/` (only what a rewrite used).

**Well-known libraries: call the host library (vcpkg) at a clean boundary instead of decompiling:**
- **The game's copies:** zlib 1.2.5, IJG libjpeg 9b (via `FetchContent`, bit-exact), SQLite 3.13.0, libVorbis 1.3.5 + libogg, zstd, libc++.
- **Starting point:** the pre-dump `libs/lib_*.cpp` and `libcxx_*.cpp`, recoverable from `pre-rebase-370`.
- **Boundaries where data is opaque or plain** (SQLite handles; `Aska::JpegUtil`, not `jpeg_*`).
- **Bridge what crosses:** structs, callbacks, paths, allocators.
- **Version-match where bytes matter.**
- **Per library (agreed with the user, 2026-10-03; shares from `port/REBUILD-QUEUE.md`):**
  - **Host library at the boundary, wave 0, one agent each:** SQLite 3.13.0 (5.1%; vcpkg's newer SQLite, compared with the guest because a newer planner can order rows differently without `ORDER BY`; pin 3.13.0 via `FetchContent` if it does), libVorbis + ogg (1.3%; callbacks through `guest_call`), zstd (0.3%), zlib 1.2.5 (0.1%; decompression identical, compression bytes may differ: matters only where the game stores or compares them; on Windows `z_stream`'s `uLong` fields are 32-bit, so a layout shim), IJG libjpeg 9b (`FetchContent`, bit-exact; boundary `Aska::JpegUtil`), the OpenSSL pieces (0.6%, 4 functions). About 7.4% of guest time without decompiling.
  - **libc++ is not hostable:** guest code inlines its templates and embeds `std::string` and containers using the NDK's layout, so the hot out-of-line helpers become small natives against that layout.
  - **Bullet:** the version-pin task below decides.
  - **Hashes** (`hash`, 3.0%): SpookyHash / CRC rewritten from their reference implementations, checked bit-exact against the guest; CHash32 from the decompile.

**Exceptions:**
- **`Framework::Cocos` is tri-Ace's own cocos2d-x-like UI**, not cocos2d-x: no `cocos2d::` symbols, objects used at fixed offsets, converted `.csf` layouts, drawn through Aska. It's rewritten from Ghidra, with cocos2d-x / Cocos Studio sources as a reference only.
- **Bullet Physics 2.7x** (before 2.80, likely 2.77–2.79) is in the game. vcpkg's `bullet3` 3.25 isn't bit-exact.
  - **Task "Bullet version pin":**
    1. build 2.76–2.79 with NDK r16b and r11c (`work/toolchains/`, `LD_LIBRARY_PATH=work/toolchains/compat-lib`);
    2. compare function sizes and object layouts with the game's;
    3. then choose a `FetchContent` host build or a Ghidra rewrite.
  - Also trace what the game uses Bullet for.

**Open items carried over from the rebase:**
- ~~Tutorial party check~~ and ~~the NPC status mismatch~~: resolved without the natives (agent open-issues, 2026-10-02; `port/REMAINING.md` "Open issues").
- **`--hires` / `--legacy-res`** do nothing until the render natives return.
- **Leads from the stopped P2-e** for the render and `ui` subsystems: a render-family boot crash ending in `CParameterUtility::tCharaData::RoleOrRookieIconFile`, and a `ui`-family title hang around the `CUIUtility` settings getters.

### 7. H: trim the server hooks (notes: [`docs/server-hooks-review.md`](../docs/server-hooks-review.md))
**The direction is decided:** keep the in-process route as a FakeApiCaller override or native shim, have it produce what the 3.7.0 wire carries, and drop the guest-reading hooks.

**Already done by the dump:** `StatusProvider` (the server uses its own stat rules), `end_mission_talk`, the `restore370` checks.

**Decided (the user, 2026-10-01), done now with P3:**
- **`BattleLog`:** the FakeApiCaller overrides for MissionEnd, MissionFailed, Sphere211MissionEnd and Sphere211MissionFailed build the battle-log blob with the client's own serializer, as the 3.7.0 bridge lambda does (@015d68bc): `AsonSerializer::Serialize<CBattleLogInfo>(ason, CParameterManager+0x52d8, 0, 0x4000, 1)`, then `ASON::Serialize`, with the ≤ 0x1000 limit. The blob is attached as `Request::battle_log` and parsed by `soa-server`'s wire parser. The guest-reading `BattleLog` implementation goes.
- **`InGameHooks` are dropped entirely:**
  - the login-bonus popup (3.7.0 builds it from the response);
  - the tutorial-cleared fallback (server state is authoritative);
  - `client_party_set`.
- **`apply_client_master`'s `sqlite3_exec` hook:** already gone with the dump (`libs/lib_sqlite.cpp`). The in-process CDN serves the edited master.

**Proof:** a per-API check that the override's `Request` equals what `soa-server` decodes from the 3.7.0 client's packet.

## Future work (not queued; needs the user's review)
- **Multiplayer state: the schema for several players** ([`server/PLAN-multiplayer-schema.md`](../server/PLAN-multiplayer-schema.md), steps M1…): a plan only, written for review (agent mp-schema, 2026-10-03). Not a task until the user has reviewed it and queued it; if queued, it starts only after 4b's S0–S12 have landed.

## Working rules
- **Branches:** commits go on `main` (since 2026-10-03; until then on `linux-port`, which was squash-merged into main as one commit on 2026-10-03); each agent gets a worktree on `port/<name>` off main, merged back into main.
- **Gates:**
  - rebuild ALL targets after a merge;
  - run independent gate tasks in parallel (up to 6 game processes, at least 8 GB free, separate folders and ports);
  - run emulator checks only when `emulator/`, `platform370/`, `runtime/`, `server/` or the root build changed, and viewer checks only when `emulator-viewer/`, `runtime/` or the root build changed.
- **Server-first:** client changes are logged in `docs/client-changes.md`; server rules are labelled (a)–(d) in `docs/server-rules.md`.
- **Prefer regenerating over investigating; prefer Ghidra over raw a2c.**
- **Data:** the sanitized player id `LOCAL00001` and the committed test saves in `data/saves/`. Never write real ids anywhere.
- **Hygiene:** tests run headless; kill only PIDs you started; never modify `work/` without being asked.

## Decisions
**Resolved (2026-10-01):**
1. **H:** `BattleLog` comes from the override's serialized blob; the `InGameHooks` are dropped; the client-master hook was already gone; H is done now, with P3.
2. **Order:** D11 and P5a in parallel, with P3+H and P4 alongside.

**Made (2026-10-01):**
- Offline-build docs move to `docs/history/`, and the viewer (`emulator-viewer/`) keeps the offline build.
- `platform370/` is a library.
- Both server modes, for diff tests.
- Real CDN download, with a shared phone for tests.
- The offline build's master DB and Ghidra project kept.
- Smoke baselines stay in `work/`.
- Natives dumped and rebuilt fresh.
- Merge bar: correctness only. Merged right after the dump.
- vcpkg with no source fallback.
- Prefer regeneration and Ghidra.
- Options grouped into client and server.
- Types first.
- Code organization.
- Decompiles in `port/decomp/`.
- Host libraries for well-known code.
