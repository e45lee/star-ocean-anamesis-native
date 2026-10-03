> **History.** The 2026-09-28 plan for porting the 3.8.0 `libSOA.so` to native C++ (it lived at `port/PLAN.md` until 2026-10-01). Superseded by the 3.7.0 rebase and the fresh native rebuild; the current plan is [`port/PLAN.md`](../../port/PLAN.md).

# Plan: porting the rest of libSOA.so to native C++

Status and scope as of 2026-09-28. This is the plan for turning the JIT-hosted port into a native C++ program. Progress is tracked at the bottom.

## Where we are

**At the end of the 2026-09-28 overnight run (15:20):**
- **Native functions:** 15,259 guest functions are replaced by native C++, up from 121. 329 differential self-tests all pass. The screenshot smoke test and the 10-minute scripted session run clean.
- **Profile of the 10-minute session:**
  - native code: 80% of busy time (86.3% of guest+native time);
  - JIT'd ARM64: 13%;
  - HLE: 7%.
  - Busy time for the same session is about half what it was before the run. The biggest single saving was the shader-compiler fix.
- **Coverage of functions that run:** 29% of the executed functions are native (2,654 of 9,105). About 6,500 executed functions are still ARM64, 774 of them lone-`RET` stubs.
- **Transcribed vs readable:** about 1,200 natives are still exact a2c transcriptions (e.g. ShadowCasterCulling, the post-processing chain, list views, the screen classes). The rest are readable C++.
- **What's left:** `REMAINING.md` has the per-family breakdown and the phase-5 roadmap.

**Before the run:**

- **What runs:** `libSOA.so` runs under the dynarmic ARM64 JIT inside a native Linux host. The host provides libc, the Android framework, GLES, audio and input, and the game plays offline end to end.
- **What's native:** 121 guest functions are replaced with C++ and differentially tested (`soa --selftest`):
  - zlib and sqlite3, which now use the host libraries;
  - resolution selection;
  - CHash32, AES and ADLD asset decryption;
  - event-script loading;
  - StringDB text.

## How big the rest is

| | |
|---|---|
| `.text` | 23 MB of ARM64 (0x15e2100 bytes) |
| Exported functions | 25,781 (9.7 MB); the rest are local functions, template instantiations and inlined third-party code |
| Largest exported families (bytes) | Aska::Yayoi 662K (SQLite ORM), CParameterUtility 280K, EventScenario 209K, CUIUtility 205K, CApiNotify 188K, Framework::Cocos 174K, CCharacterObject 141K, CInfoManager 138K, Aska::FilmCurveFilter 120K, NetworkApiCaller 118K, … |
| Bundled third-party | libjpeg (91 fns), libogg/libvorbis (~175), OpenSSL AES, sqlite3 (done), zlib (done), libc++ / libc++abi (677 exported, many more inlined) |

Porting all of this by hand is weeks to months of work, not a night. The plan is ordered so every step leaves a working, faster, more native game, and the JIT keeps running whatever isn't ported yet.

## Method (unchanged, now parallel)

Every change follows the same loop, documented in `src/native/README.md`:

1. **Decompile.** Run `tools/decomp.sh <name> '<regex>'`. It uses a pool of Ghidra project copies, so parallel runs don't fight over the project lock.
2. **Write the C++.** Put it in a new `src/native/<family>.cpp`, registered with `NATIVE_FUNCTION`. Keep guest data layouts wherever guest code still touches the data, using `guest_std.h` for libc++ containers.
3. **Test differentially.** Add `NATIVE_TEST`s that compare the replacement with the original ARM64 code on real game data plus synthetic edge cases. Run them with `soa --selftest <family>`.
4. **Run the smoke test.** `scripts/smoke.sh <soa> <out> work/port-test/smoke-base` boots with the all-characters save and visits the title, home, character list, character detail and "other" menu. It compares screenshots against the baseline, and the game is deterministic under the scripted timeline (RMSE 0 run to run).
5. **Port whole families.** Move a library or class that owns state all at once, and never mix guest and host code over the same state.

**Parallel work:**

- Each agent works in its own git worktree, created with `scripts/agent-worktree.sh <name>`. That's branch `port/<name>`, its own build directory, and shared `work/` and dependencies.
- Agents only add files. Changes to shared files (`guest_std.h`, `cpu.*`, `main.cpp`, `CMakeLists.txt`) are kept small and additive, and called out.
- The integrator (the main session) merges each branch into `linux-port`. It then rebuilds and runs the full self-test plus the smoke test before committing.

## Phases

### Phase 0: infrastructure (done or in progress)

- [x] Ghidra slot pool (`tools/common.sh` `ghidra_run`), for parallel decompiles
- [x] Per-agent worktrees (`scripts/agent-worktree.sh`)
- [x] Deterministic end-to-end smoke test with a screenshot baseline (`scripts/smoke.sh`)
- [x] Profiler (`SOA_PROFILE`, `SOA_COVERAGE`): which guest functions execute in offline play (one-shot entry traps) and sampled guest time with call stacks. Call counts exist only for HLE imports and native replacements. It answers "what actually executes in offline play?", so we can prioritise hot code first and ignore dead code (debug windows, online-only paths).
- [x] Native-coverage report (`scripts/profile_report.py`, `soa --list-native`): the fraction of executed guest functions, and of guest time, that is native. Raw data and reports are in `work/profile/`.

### Phase 1: bundled third-party libraries → host libraries

These are cheap, large, and have well-defined boundaries, the same pattern as zlib and sqlite.

- libjpeg: port the decompress API used by the texture loader, bridging the error-manager and source-manager callbacks.
- libogg/libvorbis: the decoder used by the sound streamer.
- The remaining OpenSSL pieces.
- libc++ / libc++abi out-of-line code:
  - `basic_string`, `vector` / `list` / `__tree` helpers, `to_string`, streams if used;
  - `operator new` / `delete` routed through the Aska memory manager;
  - guest layouts preserved.

### Phase 2: Aska engine foundation (leaf code first)

1. **Math:** vectors, matrices, quaternions, colour and film-curve filters, collision primitives. These are pure functions and ideal for differential tests.
2. **Memory and containers:** `Aska::MemoryManager` (the heap every guest allocation uses), strings, hash and ASON (full reader and writer).
3. **Data:** `Aska::Yayoi`, the SQLite ORM (1,696 functions); master-data parameter access (`CParameterManager` / `CParameterUtility`).
4. **Assets:** file and asset I/O, and the model, animation and scene formats (`AsfHandler`, `AafHandler`, `AofObject`, `DirectAofHandler`, the `TAaf*` animation templates, which have about 15k instantiations).
5. **Scene:** `ObjectManager`, `ShadowManager`, render passes.
6. **Render device** (Aska's GLES layer): once ported, it can target desktop GL/Vulkan directly.

### Phase 3: Framework layer

- `Framework::Cocos` UI nodes and actions, `CUIUtility`, dialogs, sorting, touch, and scene management.
- `CDebugWindows` (594 functions) is debug-only and gets stubbed, not ported.

### Phase 4: game logic

- The offline server: `FakeApiCaller`, `NetworkApiCaller`, `CApiNotify`, `CInfoManager`. Native, this becomes a readable local server.
- User data and saves (`CUserDataUtility`, `LocalKVS`), which the existing `soa_save/` tooling already documents.
- The rest of event scenarios, characters (`CCharacterObject`, `CCharacterData`), home, battle (`CBattle*`, `CFactorManager`), menus, gacha, missions, deep space, multiplayer (offline stubs).

### Phase 5: leaving the JIT

[REMAINING.md](REMAINING.md) inventories what is left (executed guest code by work package, transcribed natives, dead code, JIT blockers) and proposes the ordered phase-5 roadmap.

1. Instrumented runs report every guest function that still executes. The goal is none on normal play paths.
2. Next comes a `--no-jit` build in which executing guest code is a fatal error. Guest `.data` / `.rodata` stay mapped as data (strings, tables, vtables) until they too are replaced.
3. **De-guesting:** replace guest-layout objects (libc++ containers, Aska heaps, vtables) with ordinary C++ classes, subsystem by subsystem, once no guest code touches them.
4. Finally, drop the ELF loader, dynarmic and the bionic and Android HLE layers. What remains is a native game that reads the original assets.

## What the profiler says (2026-09-28, ~20 min of offline play)

`work/profile/report.txt` has the full data. Busy time splits as follows:

| Where | Share of busy time |
|---|---|
| Guest JIT code | 64% |
| HLE: GL, libc, pthreads | 31% |
| Native replacements | 2% |

The work is spread across threads:

| Thread | Share |
|---|---|
| Main | 47% |
| RenderThread | 27% |
| Message-dispatcher workers | 11% |
| ObjectManager worker | 7% |

About 10,800 of the ~103k guest functions ran (10.5%, 3.7 MB of code).

**What this changes about priorities:**
- **Threading primitives come first.** `SimpleMessageDispatcher` spin-waits, `Aska::Event` and `Framework::CMutex` cost about 10% of busy time in guest code, plus about 11% in HLE `pthread_cond_signal` / `sem_post`.
- **Then the per-frame engine core,** about 20%: `ObjectManager`, `ObjectManagerJobDispatcher`, `RenderThread`, `RenderDeviceGL`, `RenderDeviceData`.
- **Master data has the widest executed footprint:** more than 2,000 executed functions across `CMasterParameterBaseSqlite*`, `CParameterProperty*`, `CSimpleSqliteConnector` and `CParameterParser`. Most of it runs at boot.
- **`Framework::Cocos`** (UI): 328 functions executed, 3.7% of busy time.
- **Dead in offline play:** battle (can't be reached offline), gacha, multiplayer, `CDebugWindows`, `FilmCurveFilter`, `Collision`, and nearly all of the `TAaf*` animation templates (51 functions ran). `Aska::Yayoi` is 780 KB, but only 72 of its functions execute.
- **Dead code needs no port.** In phase 5 it is simply never reached. It still needs a policy (trap, or port on demand) in case some path reaches it.

## Scheduling (autonomous run 2026-09-28 00:00 → 16:00)

Work runs in waves of about five parallel agents, one family each, each on its own `port/<name>` branch. After every wave the integrator:

1. merges the branches;
2. runs `soa --selftest` (everything) and `scripts/smoke.sh` against the baseline;
3. commits on `linux-port`;
4. updates the table below;
5. launches the next wave, picking the next hottest families from the profiler.

Wave 1:

1. Profiler and coverage report (infrastructure)
2. libjpeg
3. libogg/libvorbis
4. Aska math
5. libc++ out-of-line functions

Later waves, in order:

1. Aska::MemoryManager + ASON
2. Aska::Yayoi
3. CParameterManager / CParameterUtility
4. Animation (`TAaf*`, `AafHandler`)
5. Model and scene formats
6. FakeApiCaller / offline server
7. `Framework::Cocos`
8. `CUIUtility`
9. EventScenario (rest)

Hot families come first once profiler data exists.

## Progress

| Wave | Family | Functions | Tests | Status |
|---|---|---|---|---|
| — | zlib, sqlite3, CUIUtility res, CHash32/AES/ADLD, event scripts, StringDB | 121 | 12 | merged |
| 1 | libogg/libvorbis public API → host libs (`lib_vorbis.cpp`); PCM within 1 LSB (the host lib is built with -ffast-math) | 106 | 4 | merged |
| 1 | Profiler + coverage (`SOA_PROFILE`, `SOA_COVERAGE`, `profile_report.py`, `--list-native`) | tooling | — | merged |
| 1 | libjpeg: `Aska::JpegUtil` on host IJG libjpeg 9 (bit-identical; bundled 9b now dead) + zstd 1.3.4 → host libzstd (SLZ v7 assets) | 13 | 7 | merged |
| 1 | libc++/libc++abi runtime: strings, shared_ptr refcounts, trees, hash tables, `function::swap`, `dynamic_cast`, guards, CityHash (`libcxx_*.cpp`) | 923 | 21 | merged |
| 1 | Aska/Framework math: vector, quaternion, matrix, random, frustum/collision primitives. Hand-written + `tools/a2c.py` transcription, bit-exact (`aska_math*.cpp`) | 246 | 13 | merged |
| 1 | Threading: `Aska::Event`/`Semaphore`, `Framework::CMutex` (FastCriticalSection), `SimpleMessageDispatcher` get/post, ObjectManager job sync (`sync.cpp`); busy time −10–16%; `SOA_WATCHDOG` | 31 | 11 | merged |
| 1 | Render device: RenderDeviceGL/Data state cache, textures, vertex input, draws, FBOs, shaders; all of RenderState; RenderContext::OnPaint; direct host GL via `GLH()` (`render_device.cpp`); RenderThread busy −8–16% | 90 | 12 | merged |
| 1 | Master data: `CParameterManager` accessors, `CMasterParameterBaseSqlite_*` cache lookups (miss → guest loader), record parsing (`GetParserValue`, all `Deserialize` instances), `CParameterUtility`/`CParameterUI` helpers (`parameter*.cpp`) | ~3,700 | 26 | merged |
| 1 | `Framework::Cocos`: tree search/flags/actions, pre-draw, layout, matrices, draw priority, blend states, timeline animation + easing, `SceneProgress`/`_DrawHierarchy` (`cocos_*.cpp`); Cocos time −46% | 61 | 17 | merged |
| 1 | Assets: ASON deserialize/serialize + work buffers, SLZ container + codecs 5/7, shader-cache LZ, ACSV, AFF helpers, ChaCha20 (`ason.cpp`, `slz.cpp`, …) | 96 | 13 | merged |
| 1 | Models/animation: ~4,700 `TAaf*` controller instantiations (312 code shapes), `AafCalcCommonFunctor`, hierarchy/bone matrices, `AofObject`/`AofHandler`/`DirectAof*` render prep, Asf/Aaf loaders. Exact ARM64→C++ transcription (`tools/a2c.py`), not yet hand-written (`models*.cpp`) | ~5,400 | 7 | merged |
| 1 | Engine heap: `Aska::MemoryManager` (malloc/free/realloc/split/aligned/high, notify), `operator new`/`delete`, STL allocator, `TFixedLengthAllocator` pools (`aska_memory.cpp`); libc++ natives call it directly | 69 | 8 | merged |
| 1 | ObjectManager frame pipeline (`OnPrePaint`, culling, painting lists, prerender/paint), job dispatcher + worker handlers (futex waits instead of busy-waits), all `SimpleMessageDispatcher` post/send variants, `TaskManager` (`objmgr*.cpp`, `smd.cpp`, `taskmgr.cpp`) | 90 | 9 | merged |
| 1 | Event scenes: `CEventScenario::Run` per-frame interpreter, 71/78 command handlers, per-frame object virtuals, typewriter text, backlog; command set documented in notes (`event_runtime.cpp`) | 102 | 8 | merged |
| 1 | Master-data loader (cache-miss path): 163 SQL connectors → msgpack, `EntityObject::Serialize`, `DeserializeMsgPack` ×157, element lifecycle ×791, cache inserts, `tMessage`/`StringDB::GetList` (`parameter_loader.cpp` etc.); loader CPU 4.4% → 0.8% | 1,816 | 16 | merged |
| 1 | Core: cheaper native↔guest crossings (inline register access, allocation-free `guest_call`, `guest_invoke`, direct native→native calls; 2–8× faster crossings), dispatcher wake budget | 0 | 4 | merged |
| 1 | Render pipeline: RenderPass/Manager hit paths, batches, shader constants, render targets, `RenderThread::Render` command loop (hand-written); post-processing/bloom, camera, lights, projectors (a2c) (`render_pass.cpp` etc.); render-thread guest time −69% | 82 | 12 | merged |
| 1 | UI: `CUIUtility` helpers (nodes, text, files, levels, campaigns, settings/KVS, sound), `CTimeUtility`, and screens: home model view (camera), home, title, settings, character list/detail, other menu (`ui_*.cpp`, `screen_*.cpp`, `home_view.cpp`) | ~260 | 20 | merged |
| 1 | Sound engine (`AskaOGG`, `SLVoice`, `AudioSignal`, `SoundManager` per-frame walks, `CSoundManager`) and input (`TouchPanel`, `TouchCallback`, `Pad`, `CPad`) (`audio_*.cpp`, `input_*.cpp`); audio output byte-identical | 152 | 16 | merged |
| 1 | Containers: every `TPoolLegacy`/`TBinaryTree`/`THash`/`TCategorizeHash` instantiation, node keys, `TObjectContainer`, `Aska::Global`, app proxies, playcore (hand-written, 1,209); `TDynamicArray`/`QuickSort`/`TPoolFast`/`THashMap` instantiations and executed Yayoi/camera/misc (a2c, 465) (`containers_*.cpp`) | 1,674 | 12 | merged |
| 1 | Inventory of remaining work (`REMAINING.md`, `scripts/remaining.py`); render-context / render-a2c tests made deterministic | tooling | — | merged |
| 1 | Readability: 4,757 animation-controller / hierarchy / blend / AofObject functions moved from a2c transcriptions to readable C++ templates (`models_anim.cpp`, `models_hier.cpp`), checked 3-way (guest / a2c / hand-written) | (4,757 rewritten) | 4 | merged |
| 1 | Render leftovers: `ShadowManager::ShadowCasterCulling` (a2c), render manager / swap / begin-render, mesh generator, GL buffer handlers, particle draw contexts (`render_manager.cpp`, `render_swap.cpp`, `render_meshgen.cpp`, a2c) | 40 | 8 | merged |
| 1 | Main loop: `CMainTask::Run` frame state, `CFiberKernel` (fibers are task lists; nothing switches context), `CSceneObjectContainer`, `NotifierThread`, `GPUSync`, `CameraFilter`, `PerformanceCounter` (`mainloop.cpp` etc.) | 35 | 8 | merged |
| 1 | Shader cache: `glReleaseShaderCompiler` made a no-op (switchable; Mesa rebuilds its built-ins after each release), cutting boot shader work from ~9 s to ~1.5 s; native offline asset-pack / payment polls (`offline_platform.cpp`) | 4 | 2 | merged |
| 1 | Screens: `CPhase` manager and menu-phase `Progress`, stamina utilities + `CCommon::UpdateStamina` (was the hottest per-frame UI item), `SetSceneTitle`/`IsFooterBadge`/`PlayBGM` (hand-written); `CHome`, `CHomeModelViewManager` talk/input, `CMissionMenu`, `CScenarioLibrary` (a2c, live replay-checked). Also a core fix: `run_jit` returned early on cache-invalidation halts | 71 | 9 | merged |
| 1 | Cocos drawing and input: `DrawSelf` (Image/Sprite/AtlasLabel/Panel/Node), touch dispatch, key frames, setters (hand-written); Label/ProgressBar draw, list/scroll views, particles, sliders, dictionary helpers, event-scene UI (a2c) (`cocos_drawself.cpp`, `cocos_input.cpp`, `cocos_a2c.cpp`, …) | 89 | 11 | merged |
| 1 | Readability 2: 242 transcribed functions rewritten as readable C++, checked 3-way: 211 Aska math (`aska_math_rd_*.cpp`), 25 TaskManager (`taskmgr_rd.cpp`), 6 ObjectManager (`objmgr_rd.cpp`) | (242 rewritten) | 4 | merged |
| 1 | Sound objects: `SoundObject`/`SEControlObject` audio runs incl. 3D downmix, `Sequencer2`, `AudioPlayer` fades, `WavePlayer`, `WaveVoiceBase::AudioKick`, locked queue pops (`audio_soundobj.cpp`); audio output identical | 12 | 1 | merged |
| 1 | Cocos layout loading: `CCocosGuiReader::CreateTree` + 26 `Read_*`, timeline `Play`/`GetHandle`/`MakeKeyFrameLinks` (a2c; trees compared node by node against two guest loads) (`cocos_guireader*.cpp`) | 30 | 1 | merged |
| 1 | Readability 3: ObjectManager `MakePaintingList`, `MultithreadOcclusionCulling`, `OnPaint` rewritten as readable C++ (3-way tests); `ViewFrustumCulling`, `Prerender*`, `OnPostPaint` still transcribed | (3 rewritten) | 3 | merged |

## Known issues

- Self-tests share one booted game. Master-data tests that do about 30k record loads can leave `master_global` unreadable for later tests (a guest quirk); tests that depend on it skip in that state.
- A full `--selftest` run once crashed right after `params/pParameterFromHash-all-records` when reusing a data dir from earlier runs; the next two runs (fresh data dirs) passed 318/318 and 324/324. Not yet reproduced or explained.
- `containers/a2c-camera` fails occasionally in the full self-test ("MakeCameraMatrix round N mismatch", one integer word off by one); it passes alone. Probably reads a frame counter. Not yet root-caused.
- `ui/settings-misc` fails occasionally in the full self-test (`GetEffectAlpha`: the guest's result is garbage, e.g. 3873198338 vs 2); it passes alone. Probably an uninitialised result on some path. Not root-caused.
