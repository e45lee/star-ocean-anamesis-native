# The rebuild queue (port/PLAN.md task 6)

Measured 2026-10-08, after N's Wave A (main at 76aba2f: audio, particles, dynamics and info merged), the same
way as the first measurement (2026-10-03, task 5, below): the 3.7.0 port with the in-process server (`--server
inproc`) and the default natives (all of them: 5,375 resolved, 1,876 called in these flows), one profiled run per
flow, `SOA_PROFILE` + `SOA_COVERAGE` at 1000 Hz, on a machine loaded by other agents' runs:

| Flow | Script | Wall time | Busy samples | Executed guest functions |
|---|---|---|---|---|
| login | `port/scripts/rebase_inproc_session.sh` (title, Login, the data check, home, the login popups) | 138 s | 53,913 | 6,972 |
| battle | `port/scripts/battle_session.sh` (the mission menu, mf01_001's battle, the results, home) | 230 s | 112,153 | 10,135 |
| gacha | `port/scripts/gacha_session.sh` (the gacha screen, a 10-draw, the presentation) | 225 s | 82,169 | 8,225 |
| story | `port/scripts/campaign_session.sh` (episode 1 -> mf01_001 cleared -> the story mission mc01_030) | 337 s | 135,326 | 11,041 |

All four PASSed. ("Executed guest functions" leaves out natives: a hooked entry isn't armed for coverage.)

## After Wave A

Where the busy time goes (samples of guest threads not waiting in a host wait):

| | login | battle | gacha | story | all |
|---|---|---|---|---|---|
| busy samples | 53,913 | 112,153 | 82,169 | 135,326 | 383,561 |
| guest code (JIT) | 28.6% | 32.2% | 32.5% | 35.9% | 33.1% |
| natives | 47.9% | 47.0% | 48.9% | 46.6% | 47.4% |
| HLE work (GL, libc, ...) | 23.5% | 20.8% | 18.6% | 17.4% | 19.5% |
| other (truncated stacks) | 0.0% | 0.0% | 0.0% | 0.0% | 0.0% |

- **Guest code is a third of the busy time now (33.1%), from 81.4% on 2026-10-03**; natives are 47.4% (from 0.9%),
  HLE work 19.5% (17.7%: GL, the shader cache's `glLinkProgram` / `glCompressedTexImage2D`, `access` / `fts_open`).
  1,876 of the 13,325 executed functions are native (14.1%), but they hold 58.9% of the non-HLE time.
- **The guest code left** is mostly the renderer and the scene graph: `render` 9.9% (`RenderContext::OnPaint`,
  `RenderThread::Render`, `PostProcessCombinerTBR`, `RenderDeviceGL`, `Camera`, `LightManager`, `RenderPass`,
  `RenderTargetManagerGL`, `HierarchicalObjectContainer`), `scene` 6.3% (`Aska::ObjectManager` 2.8%: the culling,
  `MakePaintingList`, `OnPre/PostPaint`; `AofObject`, `AofHandler`, `DirectAofHandler`, the `CDirectAof*Renderer`s), then `kernel`
  2.1% (`TaskManager::OwnersKickTask`, the dispatcher's worker `Handler`, `CFiberKernel::Progress`), `cocos` 2.0%
  (`Framework::Cocos`), `libcxx` 1.4% (`std::__ndk1`, and 0.7% of `Framework::Cocos` its scope claims: the std::function / string
  instantiations), `audio` 1.4% (`AskaOGG::Decode_Pcmout`, `SoundObject::RequestGet`,
  `AudioPlayer::GetMessage`, `SoundManager::SoundProcessSync`), `anim` 1.2% (`TAafNormalController<>`),
  `resource` 1.2% (`CGameResourceDownloader`), unassigned 1.2% (`Aska::detail`, `Collision` and
  `_HO_sub_FindIntersectPointMainFunc<>`: collision, unclaimed by any scope). Everything else is under 1% each.
- **The biggest natives are host wake-ups, not ported work:** `kernel` 13.5% native (`SimpleMessageDispatcher::
  PostMessage` 7.4%, `ResumeWorkerThread` 1.8%) and `sync` 8.9% (`Semaphore::Signal` 6.4%, `Event::Set` 2.2%).
  A `SOA_PROFILE_HOST=1` battle run puts 70% of the natives' host samples outside the soa binary (libc and the
  kernel: futex wake-ups) and 86% outside any `soa::native::<s>` namespace. That cost (a host thread woken per
  message) is a host-side tuning question for `sync` / `kernel`, not a porting one. Next: `render`'s
  `DrawIndexedPrimitive` 4.0% (with the GL it calls under HLE), `yayoi`'s `EntityObject::Serialize` 2.6% (host
  SQLite), the route 3.5% (`FakeApiCaller::Progress` / `LoggedIn`: the in-process server's work and waits).
- **Wave A's subsystems:** `audio` 2.7% -> 1.4% guest self (6,180 native samples), `particles` 1.8% -> 0.7% (4,300),
  `dynamics` 1.1% -> 0.3% (2,138), `info` 0.6% -> 0.5% self (its weight was inclusive: 13.5% -> 5.9%). The guest
  bodies still run under render's callee hooks (`LastMinuteDrawCommands_Textures`, `SetShaderProgramUniform`) are
  1,108 samples of render's guest self.

Regenerate (the raw runs are scratch, not committed; `work/` is read-only for agents):

```sh
for f in login:rebase_inproc_session battle:battle_session gacha:gacha_session story:campaign_session; do
  n=${f%%:*}; SOA_PROFILE=$P/$n SOA_COVERAGE=$P/$n port/scripts/${f#*:}.sh build/port/soa $P/$n-out $P/$n-tmp &
done; wait
build/port/soa --list-native > $P/natives.txt
port/scripts/rebuild_queue.py --markdown login=$P/login battle=$P/battle gacha=$P/gacha story=$P/story --native-list $P/natives.txt
port/scripts/profile_report.py $P/login $P/battle $P/gacha $P/story --native-list $P/natives.txt   # functions and families
port/scripts/remaining.py $P/login $P/battle $P/gacha $P/story --native-list $P/natives.txt   # guest code left, by family and area
```

The first measurement (2026-10-03, task 5; only the route's 299 hooks native): login 150 s, battle 212 s, gacha
228 s, story 299 s; 359,202 busy samples, 81.4% guest code, 17.7% HLE, 0.9% natives; 14,923 of the 103,939
functions executed (14.4%, 6.1 MB of code). Its ranking is in git history (this file before 2026-10-08).

## How to read it

- **Subsystems** are the folders of the rebuild (`port/src/native/<s>/`, `tools/subsystem.py new`). A function
  belongs to the subsystem whose `port/decomp/<s>/scope.txt` claims it (scaffolded subsystems), else to the one
  `port/scripts/rebuild_queue.py`'s `SUBSYSTEMS` table proposes for its family (class or namespace; a local
  `FUN_` function takes the family of the nearest preceding export). The table is a proposal: an agent that
  scaffolds a subsystem narrows or widens it with its `scope.txt`, and the queue follows.
- **Guest self** is the samples whose leaf is the subsystem's guest code: the JIT time its natives take over.
  Natives never count here. Per flow, the share of that flow's busy samples. **Native self** is the samples whose
  leaf is one of the subsystem's natives (`[native]<symbol>`, the subsystem of the guest function it replaces).
  A native that calls another native through `guest_call` gives `[native]A;[native]B` (B's time is B's); one called
  as a C++ member has no frame of its own, so its time stays with the caller (`SOA_PROFILE_HOST=1` +
  `port/scripts/host_profile.py DIR --by-subsystem` splits it by C++ code; port/README.md "Profiling").
  Original bodies a native runs under its own hook (`NATIVE_FUNCTION_ORIG`, render's callee hooks) are guest code
  and counted as such (the line under the ranking). `(route)` is FakeApiCaller, the in-process server's route:
  the port's own code, not a rebuild target. **Inclusive**: samples with the subsystem's guest code anywhere on
  the stack.
- **Level** is the layer (leaves first): 0 values and the bundled libraries, 1 sync, 2 memory, 3 containers and
  formats, 4 the kernel, I/O, input, network and the parameter base, 5 the engine systems and master data, 6 the
  scene graph, the UI toolkit and the client's info objects, 7 the game.
- **Dependencies** are measured from the sampled stacks: a call from a subsystem to one of a lower level is a
  dependency (it uses the callee's functions and, mostly, its types: start it after the callee's types land);
  calls within a level mean the two are co-developed (shared types: agree on the layout header first); calls
  upwards are callbacks (thread entries, tasks, virtual handlers): the lower subsystem's natives call those through
  `guest_call` / the vtable and need only the interface, not the types. Edges under 50 samples are dropped;
  calls the sampler never saw are missing, so a subsystem's README adds what its decompiles show.

## Ranking by guest time

| # | Subsystem | Level | Kind | Guest self | login | battle | gacha | story | Native self | Inclusive | Executed fns | Executed bytes | What |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 1 | `render` | 5 | rewrite | 38077 (9.9%) | 8.9% | 9.5% | 10.2% | 10.6% | 31738 (8.3%) | 35.9% | 768/1794 | 299K | the GL renderer, shaders, post-processing, cameras |
| 2 | `scene` | 6 | rewrite | 24222 (6.3%) | 5.3% | 5.9% | 6.7% | 6.8% | 1556 (0.4%) | 31.5% | 397/952 | 196K | the object manager, AOF models, skinning, the framework's models |
| 3 | `kernel` | 4 | rewrite | 8231 (2.1%) | 2.1% | 2.1% | 2.1% | 2.2% | 51941 (13.5%) | 64.3% | 255/814 | 81K | tasks, fibers, the message dispatcher, the app loop |
| 4 | `cocos` | 6 | track | 7485 (2.0%) | 1.5% | 1.5% | 2.0% | 2.5% | - | 3.7% | 330/574 | 129K | Framework::Cocos, tri-Ace's UI scene graph |
| 5 | `libcxx` | 0 | library | 5529 (1.4%) | 1.2% | 1.3% | 1.3% | 1.7% | 504 (0.1%) | 6.1% | 1407/25871 | 430K | libc++ / libc++abi |
| 6 | `audio` | 5 | rewrite | 5274 (1.4%) | 1.1% | 1.3% | 1.4% | 1.5% | 6180 (1.6%) | 4.1% | 289/734 | 95K | sound and voice |
| 7 | `(unassigned)` | - | - | 4722 (1.2%) | 1.0% | 1.3% | 1.0% | 1.4% | 50 (0.0%) | 4.7% | 1251/17337 | 427K |  |
| 8 | `anim` | 5 | rewrite | 4644 (1.2%) | 0.6% | 1.7% | 0.7% | 1.4% | - | 3.3% | 579/14161 | 142K | animation controllers (TAaf*), blending, IK |
| 9 | `resource` | 4 | rewrite | 4574 (1.2%) | 1.4% | 1.2% | 1.3% | 1.1% | 784 (0.2%) | 11.6% | 486/1588 | 194K | files, streams, the resource cache, the downloader |
| 10 | `battle` | 7 | rewrite | 3380 (0.9%) | 0.2% | 1.3% | 0.3% | 1.2% | - | 5.8% | 860/2072 | 545K | battle, arena, characters on the field |
| 11 | `containers` | 3 | rewrite | 3161 (0.8%) | 0.8% | 0.8% | 0.9% | 0.8% | 1237 (0.3%) | 3.8% | 387/2454 | 122K | the engine's containers and strings (templates) |
| 12 | `ui` | 7 | rewrite | 2801 (0.7%) | 0.7% | 0.6% | 0.9% | 0.7% | - | 5.7% | 938/9065 | 483K | screens, menus, dialogs, the home and gacha screens |
| 13 | `particles` | 5 | rewrite | 2670 (0.7%) | 0.3% | 0.9% | 0.4% | 0.9% | 4300 (1.1%) | 1.0% | 206/2439 | 150K | particles |
| 14 | `input` | 4 | rewrite | 2456 (0.6%) | 0.7% | 0.5% | 0.7% | 0.7% | 493 (0.1%) | 0.9% | 52/277 | 13K | touch, pad, mouse, keyboard |
| 15 | `memory` | 2 | rewrite | 2249 (0.6%) | 0.6% | 0.5% | 0.7% | 0.5% | 4728 (1.2%) | 0.8% | 97/437 | 27K | the engine heaps, allocators, handles |
| 16 | `info` | 6 | rewrite | 2075 (0.5%) | 0.6% | 0.4% | 0.7% | 0.5% | 943 (0.2%) | 5.9% | 841/3902 | 328K | the client's info objects and parameter manager (player, roster, missions) |
| 17 | `game` | 7 | rewrite | 1370 (0.4%) | 0.4% | 0.3% | 0.4% | 0.4% | 487 (0.1%) | 13.3% | 206/889 | 78K | the game's phases, transactions, API notifications, the tutorial |
| 18 | `dynamics` | 5 | rewrite | 1081 (0.3%) | 0.2% | 0.3% | 0.2% | 0.3% | 2138 (0.6%) | 4.6% | 129/695 | 28K | Aska's own dynamics (cloth, joints, collision) |
| 19 | `master` | 5 | rewrite | 858 (0.2%) | 0.2% | 0.2% | 0.2% | 0.2% | 2604 (0.7%) | 0.8% | 1304/7015 | 155K | master data (SQLite tables, StringDB) |
| 20 | `data_formats` | 3 | rewrite | 836 (0.2%) | 0.3% | 0.2% | 0.2% | 0.2% | 2726 (0.7%) | 2.4% | 118/1105 | 42K | ASON, ACSV, msgpack |
| 21 | `yayoi` | 4 | rewrite | 517 (0.1%) | 0.2% | 0.1% | 0.2% | 0.1% | 13192 (3.4%) | 0.9% | 136/2747 | 60K | Aska::Yayoi: network and the SQLite driver |
| 22 | `event` | 7 | rewrite | 258 (0.1%) | 0.0% | 0.0% | 0.0% | 0.2% | - | 0.1% | 163/755 | 115K | story scenes (EventScenario) |
| 23 | `params` | 4 | rewrite | 125 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 579 (0.2%) | 0.1% | 142/3088 | 18K | the parameter (de)serialization base: CParameterElementBase, CParameterParser, CParameterProperty* |
| 24 | `math` | 0 | rewrite | 119 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 807 (0.2%) | 0.0% | 45/189 | 13K | vectors, matrices, intersection |
| 25 | `bullet` | 0 | track | 67 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | - | 0.0% | 31/932 | 7K | Bullet Physics 2.75, modified (stays on the guest: unused by 3.7.0 content) |
| 26 | `text` | 5 | rewrite | 40 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | - | 0.0% | 13/98 | 3K | fonts and text layout |
| 27 | `hash` | 0 | rewrite | 27 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 2772 (0.7%) | 0.0% | 15/74 | 1K | CHash32, SpookyHash, CRC, UTF-8 |
| 28 | `sync` | 1 | rewrite | 20 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 34063 (8.9%) | 99.4% | 8/80 | 0K | mutexes, events, semaphores, threads |
| 29 | `(route)` | - | - | 0 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 13380 (3.5%) | 0.0% | 0/185 | 0K |  |
| 30 | `lib_vorbis` | 0 | library | 0 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 1844 (0.5%) | 0.0% | 0/225 | 0K | libVorbis 1.3.5 + libogg |
| 31 | `lib_crypto` | 0 | library | 0 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 1494 (0.4%) | 0.0% | 1/8 | 0K | the bundled OpenSSL pieces |
| 32 | `lib_zstd` | 0 | library | 0 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 950 (0.2%) | 0.0% | 0/339 | 0K | zstd |
| 33 | `lib_zlib` | 0 | library | 0 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 294 (0.1%) | 0.0% | 0/38 | 0K | zlib 1.2.5 |
| 34 | `lib_jpeg` | 0 | library | 0 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 59 (0.0%) | 0.0% | 0/209 | 0K | IJG libjpeg 9b |
| 35 | `lib_sqlite` | 0 | library | 0 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | - | 0.0% | 0/797 | 0K | SQLite 3.13.0 |

Guest self includes 1212 samples (0.3%) of original bodies run under their own native's hook (NATIVE_FUNCTION_ORIG trampolines, callee hooks): render 1108, game 89, libcxx 15.

## Waves (dependency order; hottest first within a wave)

| Wave | Subsystem | Guest self | Depends on (measured calls down, samples) | Same-level calls (co-develop) | Callbacks from it upwards |
|---|---|---|---|---|---|
| 0 | `libcxx` | 1.4% | - | - | containers (6169), cocos (1901), kernel (1461), info (691) ... |
| 0 | `math` | 0.0% | - | - | - |
| 0 | `bullet` | 0.0% | - | - | - |
| 0 | `hash` | 0.0% | - | - | - |
| 0 | `lib_vorbis` | 0.0% | - | - | - |
| 0 | `lib_crypto` | 0.0% | - | - | - |
| 0 | `lib_zstd` | 0.0% | - | - | - |
| 0 | `lib_zlib` | 0.0% | - | - | - |
| 0 | `lib_jpeg` | 0.0% | - | - | - |
| 0 | `lib_sqlite` | 0.0% | - | - | - |
| 1 | `sync` | 0.0% | - | - | kernel (242500), render (116516), resource (11195), audio (6193) ... |
| 2 | `memory` | 0.6% | - | - | containers (283), scene (266), resource (51) |
| 3 | `containers` | 0.8% | memory (61) | - | yayoi (2618), resource (532), info (123), render (100) |
| 3 | `data_formats` | 0.2% | libcxx (355) | - | cocos (585), info (184) |
| 4 | `kernel` | 2.1% | memory (2281), containers (63), bullet (60) | resource (24789), input (2161), yayoi (69) | scene (50598), battle (20311), ui (16904), dynamics (15211) ... |
| 4 | `resource` | 1.2% | libcxx (7714), data_formats (6237), containers (3165), memory (311) | kernel (4388), yayoi (79) | info (2920), render (895), ui (719) |
| 4 | `input` | 0.6% | - | kernel (136) | - |
| 4 | `yayoi` | 0.1% | containers (210) | resource (2439), kernel (275) | - |
| 4 | `params` | 0.0% | - | - | - |
| 5 | `render` | 9.9% | resource (1152), containers (544), kernel (408), data_formats (274), memory (126), math (54) | particles (410) | scene (55585) |
| 5 | `audio` | 1.4% | resource (885), libcxx (818) | master (54) | ui (95) |
| 5 | `anim` | 1.2% | kernel (102), hash (50) | render (942), particles (177) | scene (778) |
| 5 | `particles` | 0.7% | - | render (545) | - |
| 5 | `dynamics` | 0.3% | kernel (182) | anim (330), render (103) | scene (1310) |
| 5 | `master` | 0.2% | libcxx (80), resource (80), data_formats (76) | - | info (510), battle (69) |
| 5 | `text` | 0.0% | - | - | - |
| 6 | `scene` | 6.3% | render (64440), anim (7298), resource (700), kernel (592), containers (356), particles (321) ... | - | ui (563), battle (243) |
| 6 | `cocos` | 2.0% | libcxx (4650), data_formats (918), render (78), containers (54) | scene (1323), info (70) | ui (1186), event (65) |
| 6 | `info` | 0.5% | libcxx (2946), master (2352), audio (1478), data_formats (397), resource (381), containers (247) ... | - | game (8068), ui (286) |
| 7 | `battle` | 0.9% | scene (9316), info (924), resource (740), libcxx (653), anim (539), master (280) ... | game (13917), ui (186) | - |
| 7 | `ui` | 0.7% | libcxx (4872), info (4828), scene (1755), cocos (1469), audio (1061), resource (970) ... | game (14917), battle (415) | - |
| 7 | `game` | 0.4% | resource (2981), info (2396), data_formats (843), scene (798), anim (381), libcxx (240) ... | ui (14695), battle (13861) | - |
| 7 | `event` | 0.1% | cocos (66) | - | - |

Hottest unassigned families: (free functions) (1205), Aska::detail (1100), ~(before first export) (635), Collision (226), Aska::_HO_sub_FindIntersectPointMainFunc<> (159), Aska::Collision (131), Aska::_HO_Config<> (70), ~Aska::_HO_sub_FindIntersectPointMainFunc<> (68), NormalVisitor (32), Aska::PixelFormat (29), CLanguage (23), Aska::ResourceManager (22), Aska::TriListComp (22), CBaseDamageObject (22), LocalSetControllerF32_* (21), Framework::CDirectTexture (21), LocalSetControllerU24_* (21), CTitleLogo (20), CInitializeDialog (20), Aska::ArrayThreadSafe (18), CHaveCommon (18), CWeaponObject (18), Aska::PixelFormatBase (17), CCoinShopCallerWait (17), Aska::Cryption (17)

## The queue

**Rule (the user, 2026-10-04): don't port code the local server can't run.** A function, class or
subsystem is ported only when the local server (`server/`) serves the feature that executes it, so the
code can be exercised end to end, differential-tested against the guest and live-checked through a real
flow. Code only reachable through features the server doesn't implement stays guest code until it does —
namely **multiplayer** (co-op battles, the bridge's live sessions, rooms/matching, friends and other real
players: [`server/PLAN-multiplayer-schema.md`](../server/PLAN-multiplayer-schema.md), the code plan
`server/PLAN-multiplayer-code.md`), and likewise the stubbed online-only features
([`docs/unimplemented-apis.md`](../docs/unimplemented-apis.md) 2.2: social, paid-shop flows until task U
lands). When a wave's candidate list includes such functions (coverage shows them unexecuted, or only
reached from those screens), leave them out and note them in the subsystem's README as "waits for
<feature>".

### Up to Wave A (done 2026-10-08)

Mostly native now (native self above guest self in the ranking): the leaves and the libraries (`sync`, `hash`,
`math`, `memory`, `data_formats`, `params`, `yayoi` + host SQLite, `master`, `lib_vorbis`, `lib_crypto`,
`lib_zstd`, `lib_zlib`, `lib_jpeg`), `kernel`'s dispatcher, and Wave A's last round: `audio`, `particles`,
`dynamics`, `info`. What they left on the guest is in the ranking above and in each subsystem's README.

### Wave B (proposed 2026-10-08, from the measurement above)

Hottest first; every family named runs in the four flows the local server serves (the rule above: no
multiplayer, no stubbed online-only screens). At most five agents at once.

1. **`render` (9.9%) and `scene` (6.3%), co-developed** (level 5 and 6; render -> scene is the strongest
   callback edge, 55,585 samples, and scene -> render the strongest dependency, 64,440): render's frame
   (`RenderThread::Render`, `RenderContext::OnPaint`, `RenderContextBase`, `RenderPass`, `RenderManagerBase`,
   `RenderTargetManagerGL`, `PostProcessCombinerTBR`, `Camera`, `LightManager`, `HierarchicalObjectContainer`, the
   rest of `RenderDeviceGL` / `RenderDeviceData`), and scene's `ObjectManager` (culling, painting lists,
   Pre/PostPaint, Prerender), `AofObject` / `AofHandler` / `DirectAofHandler`, the `CDirectAof*Renderer`s,
   `ModifierManager`, `SkinMatrices`. Two agents; agree the shared layout headers
   (RenderableObject, HierarchicalObject, RenderContext) first.
2. **`kernel`'s rest (2.1%) and the wake-up cost (`kernel` 13.5% + `sync` 8.9% native):**
   `TaskManager::OwnersKickTask`, the dispatcher worker's `Handler`, `CFiberKernel::Progress`, the `Aska`
   free functions (`MatrixCalcFunc`); and on the host side, fewer futex wake-ups per message
   (`PostMessage` -> `ResumeWorkerThread` -> `Semaphore::Signal`): measure with `SOA_PROFILE_HOST=1` first.
3. **`cocos` (2.0%, its own track; level 6):** `Framework::Cocos` (`CCocosNode::ActionByActionTag`, the action
   and node updates: 334 of 504 functions run).
4. **`anim` (1.2%, level 5):** `TAafNormalController<>` and the animation controllers (579 of 14,161 executed:
   port the instantiations that run, as particles did with a generated instantiation list).
5. **Small fillers, as agents free up (level 3-4, all under 1.2%):** `resource` (`CGameResourceDownloader`),
   `libcxx` (the instantiations with the game's allocators), `containers`, `input`, `memory`'s
   `DeleteManager`; and assign the unassigned collision code (`Collision`, `Aska::Collision`,
   `_HO_sub_FindIntersectPointMainFunc<>`, `_HO_Config<>`: 0.6%) to `dynamics`' or `math`'s scope.

`audio`'s and `info`'s rest stays with their Wave A owners. **Wave C** is the game layer (level 7): `battle`
(0.9%; not `CMultiplayObject` and the co-op paths), `ui` (0.7%), `game` (0.4%), `event` (0.1%), tested by
the `tests/diff/` flows as much as by differential tests.

The type-recovery agents run a wave ahead: while wave N's code is written, wave N+1's structs (its layout
headers) are recovered, starting with the types the dependency column names.
