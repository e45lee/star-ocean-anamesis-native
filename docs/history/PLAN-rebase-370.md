> **History.** This is the plan the 3.7.0 rebase was carried out under, with its revisions layered as they happened. The rebase merged into `linux-port` on 2026-10-01 (e5cdcbc; the 3.8.0 port is the tag `pre-rebase-370`). The current plan is [`port/PLAN.md`](../../port/PLAN.md).

# Plan: rebase the port on 3.7.0 (approved 2026-10-01)

## Revision 2 (the user, 2026-10-01): natives start fresh
**The existing natives are dumped on `port/rebase-370`** (only there; `linux-port` keeps the working 3.8.0 port and its natives until the rebase merges; git history keeps everything). The P2 plan below (re-porting about 18,000 natives family by family to 3.7.0) is **cancelled**. P2-e was stopped. Its tools-only changes (lib-agnostic generators, the a2c veneer fix, the inventory fix) are kept; its regenerated outputs and remaps are not.

**What survives the dump** (everything else under `port/src/native/` is deleted):
- **the in-process route:** the FakeApiCaller hooks with their generated table, the server adapters and the in-process CDN;
- **the test and check infrastructure:** the native registry, the selftest harness, the live-check library, guest-call helpers, `arm_float` and math helpers;
- **the generators and a2c tooling,** as tools only;
- **the port-only features:** the tower (`restore_tower`), stand-in assets, the local notice-board webview, the debug control commands.

**The new merge bar replaces decision 7: correctness only.** `port/rebase-370` merges into `linux-port` once the 3.7.0 port is correct with the remaining hooks:
- both server modes reach home;
- all sessions pass;
- the `tests/diff/` flows equal `soa-emu`'s.

**Merge timing (the user, 2026-10-01):** merge `port/rebase-370` into `linux-port` as soon as the dump step (R3) reports, without waiting for P3, P4 or P5; those continue on `linux-port`. The last 3.8.0-based `linux-port` head before the merge is tagged `pre-rebase-370` for reference.

**Afterwards:** natives are rebuilt fresh, as ongoing work on `linux-port`:
- **readable C++ from the Ghidra decompile,** with **no new a2c translations**;
- hottest families first, by a fresh profile;
- each with differential tests and live checks against the 3.7.0 guest.

**Order for the rebuild (the user, 2026-10-01): types first, so natives use classes/structs, not raw memory reads and writes.**
- **Recover the data layout before the code that uses it.** For each class or struct a family touches:
  - define it as a C++ struct, field names and types from the Ghidra decompile: constructors, accessors, vtables, the game's own debug/assert strings;
  - `static_assert` every offset and the size;
  - keep it in one header per subsystem (e.g. `native/<sub>/<sub>_layout.h`).
- **Order by type dependency, leaves first:**
  1. plain data and value types (vectors, matrices, ids, small records);
  2. the containers the game uses (`TDynamicArray`, `THashMap`, `std::` containers);
  3. the objects built from them (parameters, characters, scene and UI nodes);
  4. the managers and phases that own those objects.

  A native is written only once the types it reads and writes exist, so its body uses `obj->m_hp`, never `*(u32*)(obj + 0x1a0)`.
- **Where a type is only partly known:** name the known fields; keep the unknown bytes as explicit `pad_0x1a4[…]` members (still `static_assert`ed), not as offset arithmetic in code. Rename them as they're understood.
- **Keep Ghidra in sync:** apply the same structs as data types in the committed Ghidra project (`ghidra/`), so later decompiles show field names. The header and the Ghidra types are updated together.
- **Profile order still matters,** within this: among the families whose types are ready, the hottest go first. If a hot family needs a type nobody has defined yet, define that type first. Don't fall back to raw offsets.

**Code organization (the user, 2026-10-01): practise good software-engineering organization in the rebuilt natives.** The old tree grew by accretion: flat folders, grab-bag files, raw offsets, generated and hand-written code mixed. The rebuild is organized deliberately:
- **One subsystem per folder** under `port/src/native/` (the `port/src/README.md` map), each with a short `README.md`: what it covers, its public header(s), its switches and tests.
- **Files by responsibility, named after what they contain:** one class or one cohesive group per file (`battle/character_object.cpp`, not `battle_misc2.cpp`). Headers declare, sources define.
- **A clear public interface per subsystem:** other subsystems include only its public header. Its `*_layout.h` types are shared deliberately, not reached into.
- **Types first** (above): structs and classes with typed fields, no offset arithmetic in code.
- **Tests next to the code they test** (`*_test.cpp` in the same folder); the shared harness stays in `native/common/`.
- **Generated code separate and marked:** `gen/` subfolders with a header naming the generator. Never hand-edited.
- **Reverse-engineering material per subsystem** (below): notes in the subsystem's `README.md`, decompiles as data in `port/decomp/<subsystem>/`, not scattered in `work/`.
- **Consistent naming and style** matching the surrounding code; no copy-paste between subsystems (shared helpers go to `native/common/`).
- **Small, reviewable commits** per subsystem or class, by path.

**Where reverse-engineering work is stored (the user, 2026-10-01):** code and data apart, both per subsystem.

```
port/src/native/<subsystem>/      CODE (compiled)
  README.md                       the subsystem: what it covers, its public header, switches, tests,
                                  and the RE notes (what each class/function does, call flow, open
                                  questions, naming decisions), linking to its decompiles
  <subsystem>_layout.h            recovered structs/classes (types first; static_asserted offsets)
  *.cpp / *.h / *_test.cpp        the readable natives and their differential tests

port/decomp/<subsystem>/          DATA (never compiled; clearly not source)
  <topic>.c                       Ghidra decompiles the rewrite used (tools/decomp.sh output, stamped
                                  with the lib path, sha256 and Ghidra version)
  symbols.tsv                     the subsystem's functions/data: symbol, 3.7.0 address, size,
                                  status (guest / native / rewritten), owner
```

- **The same subsystem names** in both trees (the `port/src/README.md` map: battle, render, models, ui/cocos, ui/screen, params, engine, containers, audio, event, gacha, …). A folder is created when its first function is reverse-engineered.
- **Tooling:**
  - `tools/decomp.sh` / `tools/decomp_at.sh` get an `--into <subsystem>[/<topic>]` option that writes the resolved, stamped decompile to `port/decomp/<subsystem>/<topic>.c`.
  - Without it they keep writing to `work/decomp/` (scratch).
- **Struct definitions** go into `<subsystem>_layout.h` **and** the committed Ghidra project's data types, together.
- **Decompiles are data, not code:**
  - `port/decomp/` is outside `port/src/`, so the build's source globs never see it;
  - regenerate a decompile rather than hand-edit it;
  - the understanding goes into the subsystem's `README.md` and its readable code.
- **Size:**
  - keep only the decompiles a rewrite actually used (whole-binary dumps stay in `work/`);
  - copy useful files from `work/decomp/` (573 files, 84 MB) into `port/decomp/<subsystem>/` when that subsystem is worked on, not in bulk;
  - if `port/decomp/` grows large, track `*.c` there with git LFS like the Ghidra project.

**Note for the rebuild (the user, 2026-10-01): call native libraries instead of decompiling well-known ones.** For code the game links statically from well-known libraries, try **calling the host library**, supplied through vcpkg (D11), at a clean boundary, rather than decompiling or translating its ARM64 code.

- **Libraries found in 3.7.0's `libSOA.so`** (from its version strings):

  | Library | Version in the game |
  |---|---|
  | zlib | 1.2.5 ("deflate 1.2.5 … Jean-loup Gailly and Mark Adler") |
  | IJG libjpeg | 9b ("9b 17-Jan-2016") |
  | SQLite | 3.13.0 |
  | libVorbis | 1.3.5 (+ libogg) |
  | zstd | (version string present) |
  | libc++ / libc++abi | NDK |

- **Starting point:** the pre-dump port already did this for most of them: `port/src/native/libs/lib_{zlib,zstd,sqlite,jpeg,vorbis}.cpp` and `libcxx_*.cpp`, recoverable from the `pre-rebase-370` tag. They show the pattern and the pitfalls:
  - **Choose the boundary where the game's data is opaque or plain.** SQLite's handles are opaque, so they can be host objects. libjpeg is bridged at `Aska::JpegUtil`'s five entry points, not the raw `jpeg_*` API, whose structs the guest sees.
  - **Bridge what crosses:**
    - guest structs (e.g. zlib's `z_stream` is guest-visible);
    - callbacks into guest code (SQLite exec callbacks, bind destructors);
    - Android paths to host paths;
    - allocators, error handling (`longjmp` vs return codes).
  - **Match versions where bytes matter:**
    - **IJG 9**, not libjpeg-turbo, for bit-identical decoding: built via `FetchContent` (D11);
    - zlib *inflate* is exact across versions, but *deflate* output can differ by version and level, so check whether the game compares deflated bytes;
    - Vorbis float decoding may differ slightly; set the test tolerance against the guest.
- **Verification:** like any native, differential tests against the 3.7.0 guest's own copy of the library, plus live checks.
- **Where it doesn't fit:** decompile with Ghidra (readable C++), as for the game's own code. Libraries with no vcpkg port, or where version-exact output can't be had, are candidates.
- **Bullet Physics is in the game too:** about 627 exported functions (`btDiscreteDynamicsWorld`, `btRigidBody`, `btSequentialImpulseConstraintSolver`, `btQuantizedBvh`/`btDbvt`, hinge / cone-twist / 6-DoF constraints). It has no version string and no `btGetVersion`.
  - **Its API fingerprint says 2.7x, before 2.80; most likely 2.77–2.79:**
    - Collision algorithms take raw `btCollisionObject*`; 2.80 switched to `btCollisionObjectWrapper*`.
    - `rayTestSingle` takes a non-const object.
    - `solveGroupCacheFriendlySetup` still takes `btStackAlloc*`.
    - `getOrInitSolverBody(btCollisionObject&)` has no time step.
    - Nothing from 2.81 on is present. The 2.76+ solver refactor is present.
  - **vcpkg only has `bullet3` 3.25:** a different API and different physics, so it **can't be the host library** for bit-exact results.
  - **Options:** the matching 2.7x source via `FetchContent`, built like IJG libjpeg 9, only if the exact release is pinned and outputs match the guest; otherwise a Ghidra rewrite with Bullet 2.7x's source as the reference.
  - **Also to trace:** what the game uses Bullet for. Not the battle's projectiles: `CBulletObject` is a game class that only shares the name.
  - **Queued task "Bullet version pin"** (small, when natives are rebuilt):
    1. Build Bullet 2.76, 2.77, 2.78 and 2.79 with the NDK clang for arm64.
    2. Compare against the game: function sizes, and object layouts read from the game's constructors (`sizeof(btRigidBody)`, `btCollisionObject` field offsets).
    3. Pick the release that matches, then decide host build vs Ghidra rewrite.
    - **Toolchains, fetched 2026-10-01 into `work/toolchains/` (untracked):**
      - **NDK r16b** (`Android clang version 5.0.300080`): matches the game's main compiler string.
      - **NDK r11c** (`clang version 3.8.243773`): matches the game's second compiler string, probably a prebuilt static library, possibly Bullet itself. Try both.
      - **Setup:** the old clangs need `libncurses.so.5`. `work/toolchains/compat-lib/` has symlinks to the system `.so.6` libraries; run with `LD_LIBRARY_PATH=work/toolchains/compat-lib`.
      - (NDK r12b was also tried: clang `3.8.256229`, no match; deleted.)
- **Named exception: `Framework::Cocos` is not cocos2d-x.** The game has no `cocos2d::` symbols and no cocos2d-x version string. Its UI layer is tri-Ace's own cocos2d-x-like framework, about 1,311 `Framework::Cocos` symbols (`CCocosNode`, `CCocosScene`, `CCocosDirector`, `CCocosGuiReader`, `CCocosTimelineAnimation`, …).
  - **Why it can't link real cocos2d-x:**
    - Game code uses its objects' fields at fixed offsets.
    - The layouts are converted Cocos Studio designs: `.csf` = ADLD + SLZ + an ISF container of MessagePack node trees.
    - It draws through the game's own Aska renderer.
  - **So it's rewritten readable from the Ghidra decompile,** with **cocos2d-x / Cocos Studio sources as a reference only** (node and anchor semantics, the timeline, the `tweenfunc` easing curves, the GUI reader's property names), for faster understanding and better names. Its arithmetic must still match the guest bit for bit.


**P3, P4 and P5 still apply.** P3's restore370 and oracle removal is now largely done by the dump.

✅ **The dump is done (agent `r3-dump-natives`, 2026-10-01, on `port/rebase-370`):** 358 files / 681,290 lines deleted; 301 natives remain (the route, the `CPhase::Progress` wrapper, the tower, the notice board); both server modes reach home, the six sessions pass, selftest 95/95. Details and gates: `docs/history/REBASE-370.md` "Revision 2".

## Context
The port (`soa`) runs the **3.8.0** offline build and grafts 3.7.0 behaviour back onto it:
- `restore370` (3.7.0 bodies on 3.8.0 symbols);
- client-master edits;
- offline-clock fixes;
- `home_sa` handling.

Meanwhile the unmodified **3.7.0** client already runs end to end in `soa-emu` on the shared `runtime/` against `soa-server`. The user wants:
- the port rebased on 3.7.0, using only the 3.7.0 APK;
- all references to 3.8.0 and its XAPK removed from the port;
- the 3.8.0-era docs moved to `docs/history/`;
- `emulator-viewer/` keeping 3.8.0;
- the 3.7.0 platform patches pulled into a new `platform370/` library;
- the port supporting both an in-process server (patched FakeApiCaller route) and the out-of-process `soa-server` over TCP and HTTP, so port-versus-emulator differential tests become possible.

**State** (`linux-port`, 2026-10-01): one top-level build (`build/port/soa`, `build/server/soa-server`, `build/emulator/soa-emu`, `build/emulator-viewer/soa-viewer`), with dependencies in `deps/` and `third_party/`. Tests run headless. Sanitized saves are in `data/saves/`. The tutorial milestone spec (`tests/tutorial_milestones.txt`) and `tools/compare_tutorial.py` exist. Data lives under `~/.local/share/soa-*`.

## Why it's feasible
- **Most natives carry over:** 101,765 of 102,184 function bodies are identical after normalisation (`work/verdiff`, `docs/history/libsoa-3.7.0-vs-3.8.0.md`), and symbol-bound natives keep working where the body is unchanged.
- **The platform is proven:** the 3.7.0 platform layer works in `soa-emu`: the Java answers, `fmod`, the `service_stop_day` patch, the real clock, the redirect, the HTTP client, the JNI reference tagging and TBI.
- **The tests follow the guest automatically:** every differential selftest and live check compares a native with the guest code it replaces, so with a 3.7.0 guest they check against 3.7.0 as they stand.

## What changes (from today's `--list-native` and `work/verdiff`)
| Item | Count | Action |
|---|---|---|
| Symbol-bound natives on identical bodies | ~17,900 | keep; re-verified against the 3.7.0 guest |
| Natives on functions whose body changed | 48 | drop (the 3.7.0 guest runs) or port the 3.7.0 behaviour, decided per function from `tools/decomp.sh --v370` |
| Address-bound natives (`@0x…`) | 96 | remap by symbol (`translate_symbol_addr`, the verdiff address map) |
| a2c translations with 3.8.0 constants | ~2,640 bodies, 14 files | regenerate with `tools/gen_*_a2c.py` against 3.7.0 |
| Generated tables (`containers_tables.inc`, `parameter_*.inc`, `fakeapi_tables.inc`, `wire_table.inc`, `battle_factor_ids.inc`, `libcxx_hash_table.inc`, `api_notify_table.inc`, `infobase_table.inc`, `models_anim_tab.inc`) | ~11 | regenerate from 3.7.0 (each file names its generator) |
| Layout differences (`work/verdiff/layout.tsv`) | 54 | check the `*_layout.h` structs (`static_assert`ed) |
| `restore370` and `restore370_statics.inc` | module | delete |
| 3.8.0 / XAPK references in port code, tools and docs | ~89 code, ~18 docs | update; history docs move to `docs/history/` |

## Phases
### P0, in parallel: inventory, and the `platform370/` extraction
- **Inventory: `tools/rebase_inventory.py` writes `docs/history/REBASE-370.md`.** It classifies every native: identical / changed / address-bound / a2c / generated table / layout-dependent. It also covers every `docs/client-changes.md` entry and every server rule that exists only for 3.8.0.
  - Plus 3.7.0 coverage from `soa-emu` sessions: the functions the port never ran under 3.8.0, such as `CPhase_Relogin`, `CPhase_SyncServerTime` and the downloader.
- **`platform370/`:** a top-level static library in the root build. It moves out of `emulator/src/`:
  - `java_370.cpp`, `hle_370.cpp`, `patch_370.cpp`;
  - the device clock;
  - `net_370.cpp`, `http_370.cpp`.

  It registers through the runtime extension points. `soa-emu` links it.
  - **Gate:** `soa-emu` is unchanged: `emulator_boot.sh`, a seeded and a `--new-player` `emulator_session.sh`, and the `--log-packets` sequence identical.

### P1: the port loads 3.7.0, natives off, both server modes (branch `port/rebase-370`)
- **Client files:** the library comes from the 3.7.0 APK (`lib/arm64-v8a/libSOA.so`, cached in the data dir like today). The APK list is the 3.7.0 APK only, with no asset packs or playcore. `app_version` is "3.7.0".
- **Downloaded data:** required; `--download-dir` defaults to `work/download-3.7.0`.
- **Platform:** `soa` links `platform370/`.
- **Server modes:**
  - **`--server inproc` (default):** the FakeApiCaller hooks with the server library, as today. First check that 3.7.0's `CGame::OnInitialize` / FakeApiCaller path matches `native/api/fakeapi.cpp`.
    - **No sockets in-process (P1b, branch `port/p1b-inproc-nosocket`, done):** the in-process CDN is no longer a loopback HTTP server; soa-server's router is platform370's in-memory HTTP backend (`platform370::set_http_backend`), the bodies streamed from files and bundles. Same GETs (2 on a downloaded phone, 1,032 on an empty one); `soa` owns no TCP socket.
  - **`--server HOST:PORT`:** no FakeApiCaller hooks. 3.7.0's own `NetworkApiCaller` talks GameRPC and HTTP to `soa-server` through `platform370/`.
  - **The data download is real** (decision 5): the client downloads from `soa-server`'s CDN exactly as the emulator does.
  - **Tests share a downloaded phone:** a cached, pre-downloaded data dir, like `emulator_session.sh`'s `EMU_DATA` plus `FRESH_KVS=1`, so they don't fetch 3 GB every run. Only one test exercises the full download.
- **Gates, with `--no-native` except the hooks the mode needs:**
  - in-process, reaching home;
  - out-of-process against `soa-server`, reaching home, with a packet log equal to `soa-emu`'s for the same flow.

### P2: natives on 3.7.0 (same branch)
1. Regenerate all a2c translations and generated tables from 3.7.0, reviewing the diffs.
2. Remap the 96 address-bound natives.
3. Decide the 48 natives on changed functions.
4. Check the 54 layout differences.
5. Enable family by family, with the existing switches. Each family needs its differential selftests against the 3.7.0 guest and its live check at 0 mismatches over the restore, events and home sessions.

**Parallel agents, split by family:**
- models and containers;
- battle;
- UI, params and infobase;
- render, particles, dynamics, arena and objbase;
- generated tables and address remaps.

### P3: remove what only existed for 3.8.0
- **Restore code:** `restore370` with its tests and `tools/restore370_audit.py`; `home_sa` handling; the offline-clock fixes; client-master edits the 3.7.0 client doesn't need. Each one is checked against the emulator's behaviour first.
- **The 3.7.0 oracle** (`t.call370`, `SOA_ORACLE_370`) is removed. Its tests compare against the live guest.
- **The 3.8.0 offline mode is gone.** `scripts/run-port.sh` loses `--offline` and gains `--server HOST:PORT`. A new `scripts/run-port-with-server.sh` starts `soa-server` like `run-emulator-370.sh`.
- **Re-audit `docs/client-changes.md` and `docs/server-rules.md`.** Expected to stay: the FakeApiCaller route, error-code reporting, the `service_stop_day` patch (shared via `platform370/`), the stand-ins, the tower.

### P4: references and docs
- **Tools:** default to the 3.7.0 lib. That covers `tools/decomp.sh`, `callers.py`, `a2c.py`, the generators and `verdiff.py` (kept only for history).
- **Paths:** drop `work/extracted/xapk`, `config.arm64_v8a`, `assetinstalltime` and the playcore paths from the port. They stay only in `emulator-viewer/` and `scripts/run-viewer-380.sh`.
- **Move to `docs/history/`,** each with a one-line note:
  - `docs/history/libsoa-3.7.0-vs-3.8.0.md`;
  - `docs/history/AUDIT-9-30.md`;
  - `docs/history/PLAN-next.md`, `PLAN-restore-original.md`;
  - the `REMAINING.md` history;
  - the 3.8.0 sections of `docs/notes.md`.

  Links are updated.
- **Other 3.8.0 files stay where they are** (decision 6): the committed `data/basmaster-3.8.0.sqlite3` and the 3.8.0 Ghidra project, for the viewer and history. The port and its tools just stop using them.
- **Living docs** describe the 3.7.0 port only: root `README.md` ("Running", "Game files"), `port/README.md`, `port/src/README.md`, `runtime/`, `server/` and `emulator/` READMEs.

### P5: tests, baselines, differential tests
- **Smoke baselines:** regenerated from the 3.7.0 port after checking each screen against `soa-emu`'s screenshots. They stay **untracked in `work/port-test/smoke-base`**, as today (decision 8). The old 3.8.0 baselines are kept beside them as `smoke-base-380/` until the merge.
- **Sessions:** re-check every session's coordinates and milestones. They already drive 3.7.0 layouts under `--restore`.
- **`--list-native`:** a new baseline, with a changelog (the 48, the 96, the regenerated a2c).
- **New `tests/diff/`:** each flow runs in `soa-emu` and in `soa --server`, against fresh `soa-server`s with the same seed (`data/saves/seed/Game.xml`, `--seed-rng 1`). Flows: seeded login/popups/battle/10-draw, the new-player tutorial (`tests/tutorial_milestones.txt`), an event mission.
  - **Compared:** packet logs (ordered requests and arguments, minus transport and timing), `tools/server_state.py` with times masked, and milestone screenshots by RMSE. This extends `tools/compare_tutorial.py`.
- **Final gate:** all of the above, headless.

## Side item: pre-seed the server with a 3.8.0 save (the user, 2026-10-01)
✅ **Done 2026-10-01 (6dfaac0, on linux-port):** `soa --seed FILE`, `run-emulator-370.sh --seed`, the selftest `server/seed-from-380-save`, README "Bringing your own save over", and `server-rules.md` "Seeding from a save".
**It already works at the server level** (checked 2026-10-01). `soa-server --seed FILE` (and `soa`'s `SOA_SERVER_SEED`) reads any local-KVS `Game.xml`, 3.8.0 offline saves included: they carry the same summary keys plus 3.8.0's `BAS:StandAlone*` keys. Seeding from the committed 3.8.0 save `data/saves/client/Game.xml` gave:
- player `LOCAL00001` "Fayt", level 87, FOL 1,675,605;
- all 276 characters;
- party 1.

**What a 3.8.0 save can't carry:** the KVS only stores a summary. The roster's role ids, player level, FOL and name come across; per-character EXP, favor and limit breaks don't exist in it and start at the server's defaults. That is the same as seeding from a 3.7.0 save; label (d) in `docs/server-rules.md`.

**Still to do** (small; any time, not blocked by the rebase):
- A `--seed FILE` option on `soa` (today only `SOA_SERVER_SEED`), `scripts/run-port.sh`, `scripts/run-emulator-370.sh` (passes it to `soa-server`) and `scripts/run-port-with-server.sh` (P3).
  - It applies to a **new** server state. An existing `server.sqlite3` keeps its player; document "use a fresh `--home`/`--data`".
- A `soa-server` selftest that seeds from `data/saves/client/Game.xml` (the committed, sanitized 3.8.0 save) and checks level, FOL, name and roster count.
- Docs: the root `README.md` "Running" (how to bring your 3.8.0 save over: copy the offline game's `shared_prefs/Game.xml`, then `--seed` it); `server/README.md`; `docs/server-rules.md` (what carries over).
- Possibly the save's `BAS:PlayerID`: don't copy it (the server always uses `LOCAL00001`; sanitize rule).

## Queued follow-up D11: dependencies through vcpkg + CMake (the user, 2026-10-01)
**Slot:** after P1b and P2-e merge into `port/rebase-370`, before P2-a..d start. One agent on `linux-port`; the rebase branch then merges `linux-port`.

**Decisions:**
- **vcpkg** (manifest mode, a `vcpkg.json` in the repo) is the source of dependencies on **both Linux and Windows**. **No source-build fallback** and no `apt-get download` sysroot.
- **The two dependencies vcpkg doesn't have** (checked 2026-10-01 against `microsoft/vcpkg` `ports/`) are fetched by CMake `FetchContent`, pinned (URL + hash):
  - **dynarmic:** today's commit;
  - **IJG libjpeg 9:** the jpeg-9 source tarball, built as a static library with a small CMake file of ours.
  - vcpkg only has `libjpeg-turbo`, whose DCT scaling differs from the game's 9b. Bit-exact decoding needs IJG 9.
  - This also drops the host `libjpeg.so.9` requirement and the unused libjpeg-turbo headers.
- **From vcpkg:** `boost-headers` (for dynarmic), `zlib`, `sqlite3`, `zstd`, `libogg`, `libvorbis`, `sdl2`, `openssl`, `egl-registry`, `opengl-registry`, and on Windows later `angle` (EGL/GLES over Direct3D 11).
- **Linux system pieces vcpkg can't replace:** the GPU driver's EGL/GLES runtime (Mesa), and the X11/Wayland/ALSA/PulseAudio development headers that vcpkg's `sdl2` port expects from the system. Document them as `apt install` prerequisites.
- **Retire:** `scripts/fetch-deps.sh`, `deps/` and `third_party/`. Keep the `port/deps` and `port/third_party` compatibility links until no worktree uses them. `scripts/build.sh` = configure with the vcpkg toolchain + build.

**Gate:**
- Configure and build from a clean checkout with no `deps/` or `third_party/`.
- `soa`'s `--list-native` is identical; compile flags compared.
- Full selftest, including the `lib_jpeg` tests (the decoder becomes our own static 9e build); smoke; restore; `soa-server --selftest`; `emulator_boot.sh`; `viewer_boot.sh`.

## Later: a native Windows runner (not started)
After the rebase merges. Cross-compile with MinGW-w64 (clang) in the same CMake build, with vcpkg dependencies (D11) and ANGLE for EGL/GLES.

**Work:**
- the HLE libc layer (289 import thunks: files, Winsock, time, threads);
- guest memory (`VirtualAlloc`) and the JIT's fault handling (vectored exceptions instead of `SIGSEGV`);
- an audit of about 1,800 uses of `long` in native code, which is 64-bit on Linux but 32-bit on Windows. The audit can land on `linux-port` early, since it's harmless there.

The runtime tests run under Wine for CI. **Estimate:** 2–3 weeks of agent work.

## Order
1. P0: two agents.
2. P1: one agent.
3. P2: about five agents.
4. P3 and P4: two agents.
5. P5: the integrator.

All of it happens on `port/rebase-370`. `linux-port` keeps the working 3.8.0-based port until the merge.

**Merge bar (decision 7): full parity first.** The branch merges into `linux-port` only when every native family that was on under 3.8.0 is back on under 3.7.0, at 0 live-check mismatches. Performance must not regress (smoke wall time and a `SOA_PROFILE` comparison with the 3.8.0 port), and every test and `tests/diff/` flow must be green.

## Risks
- **The a2c regeneration** touches about 2,640 bodies. Each family must reach 0 live-check mismatches again.
- **3.7.0-only paths** (online phases, the downloader) start as guest code. That's slower, but correct.
- **Selftests built on 3.8.0 specifics** (oracle, restore370) are removed or rewritten, so the selftest count changes.
- **Performance dips** while families are off.

## Verification
- **P0:** `soa-emu` unchanged after the `platform370/` extraction: the sessions PASS and the packet sequence is identical.
- **P1:** home in both server modes with natives off. The packet log equals `soa-emu`'s.
- **P2:** per family, the differential selftests plus live checks at 0 mismatches. Full `soa --selftest`.
- **Final:** the merge bar above, plus smoke, all sessions headless, `tests/diff/` flows equal between `soa` and `soa-emu`, `soa-server --selftest`, the viewer's `viewer_boot.sh`, and no 3.8.0 reference outside `emulator-viewer/` and `docs/history/` (a grep check in the gate).

## Decisions so far (the user, 2026-10-01)
1. The 3.8.0 docs move to `docs/history/`.
2. `emulator-viewer/` keeps 3.8.0.
3. A new `platform370/` library holds the 3.7.0 platform patches.
4. The port supports both server modes, for port-versus-emulator differential tests.
5. Out-of-process mode downloads for real from `soa-server`'s CDN. Tests reuse a pre-downloaded phone.
6. `data/basmaster-3.8.0.sqlite3` and the 3.8.0 Ghidra project stay, for the viewer and history.
7. The merge bar is full parity: every family back on, at 0 mismatches, with no performance regression.
8. Smoke baselines stay untracked in `work/port-test/smoke-base`.
