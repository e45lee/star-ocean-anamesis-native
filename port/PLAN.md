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
| **5** | **Rebuild tooling, together with the control-script consolidation** (`control/PLAN-consolidate.md`, incl. the runtime's GDB stub) | below | 🔄 2026-10-03: decomp --into, scaffolding, the GDB stub (`--gdb`) and the fresh profile running (agent rebuild-tooling); the consolidation (soadrive, flows, thin wrappers) after the env→flags cleanup lands |
| **5b** | **W: native Windows runner** (the user, 2026-10-02: before N) | below | 🔄 phase 1 started early (2026-10-03, to speed things up; the user): the MinGW cross build, soa-server.exe and the runtime tests on the host via WSL interop, the `long` audit (agent win-runner) |
| **4c** | **Multiplayer state: the schema for several players** (`server/PLAN-multiplayer-schema.md`, steps M1…) | that plan | ⏳ plan being written (agent mp-schema); runs **strictly after 4b's S0–S12** (the user, 2026-10-03) |
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
- **Smoke:** new baselines (screenshots) from the 3.7.0 port, checked screen by screen against `soa-emu`'s. They stay untracked in `work/port-test/smoke-base`; the pre-rebase ones are kept beside them.
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
- **`tools/decomp.sh` / `decomp_at.sh --into <subsystem>[/<topic>]`** write stamped decompiles to `port/decomp/<subsystem>/<topic>.c`. Without it they write scratch output to `work/decomp/`.
- **Per-subsystem scaffolding:** `port/src/native/<subsystem>/README.md` + `<subsystem>_layout.h`, and `port/decomp/<subsystem>/symbols.tsv`.
- **A fresh profile of the 3.7.0 port (in-process server)** (`SOA_PROFILE` / `SOA_COVERAGE`, `port/scripts/profile_report.py`, `remaining.py`) to rank subsystems by guest time. The output is the rebuild queue.

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
  - mirror the structs as data types in the committed Ghidra project.
- **Among subsystems whose types are ready, hottest first** (the profile from 5).
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
