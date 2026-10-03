# The rebuild queue (port/PLAN.md task 6)

Measured 2026-10-03 (task 5): the 3.7.0 port with the in-process server (`--server inproc`, the default
natives: only the route's 299 hooks), one profiled run per flow, `SOA_PROFILE` + `SOA_COVERAGE` at 1000 Hz:

| Flow | Script | Wall time | Busy samples | Executed functions |
|---|---|---|---|---|
| login | `port/scripts/rebase_inproc_session.sh` (title, Login, the data check, home, the login popups) | 150 s | 51,069 | 9,258 |
| battle | `port/scripts/battle_session.sh` (the mission menu, mf01_001's battle, the results, home) | 212 s | 93,678 | 13,362 |
| gacha | `port/scripts/gacha_session.sh` (the gacha screen, a 10-draw, the presentation) | 228 s | 93,021 | 11,048 |
| story | `port/scripts/campaign_session.sh` (episode 1 -> mf01_001 cleared -> the story mission mc01_030) | 299 s | 121,434 | 14,348 |

All four PASSed. Together: 359,202 busy samples (samples of guest threads not waiting in a host wait);
**81.4% is guest ARM64 code under the JIT**, 17.7% HLE work (GL mostly), 0.9% native replacements;
14,923 of the 103,939 functions of the table executed (14.4%, 6.1 MB of code).

Regenerate (the raw runs are scratch, not committed; `work/` is read-only for agents):

```sh
for f in login:rebase_inproc_session battle:battle_session gacha:gacha_session story:campaign_session; do
  n=${f%%:*}; SOA_PROFILE=$P/$n SOA_COVERAGE=$P/$n port/scripts/${f#*:}.sh build/port/soa $P/$n-out $P/$n-tmp &
done; wait
port/scripts/rebuild_queue.py --markdown login=$P/login battle=$P/battle gacha=$P/gacha story=$P/story
port/scripts/profile_report.py $P/login $P/battle $P/gacha $P/story     # functions and families
build/port/soa --list-native > $P/natives.txt
port/scripts/remaining.py $P/login $P/battle $P/gacha $P/story --native-list $P/natives.txt   # guest code left, by family and area
```

## How to read it

- **Subsystems** are the folders of the rebuild (`port/src/native/<s>/`, `tools/subsystem.py new`). A function
  belongs to the subsystem whose `port/decomp/<s>/scope.txt` claims it (scaffolded subsystems), else to the one
  `port/scripts/rebuild_queue.py`'s `SUBSYSTEMS` table proposes for its family (class or namespace; a local
  `FUN_` function takes the family of the nearest preceding export). The table is a proposal: an agent that
  scaffolds a subsystem narrows or widens it with its `scope.txt`, and the queue follows.
- **Guest self** is the samples whose leaf is the subsystem's guest code: the JIT time its natives take over.
  Per flow, the share of that flow's busy samples. **Inclusive**: samples with the subsystem anywhere on the stack.
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

| # | Subsystem | Level | Kind | Guest self | login | battle | gacha | story | Inclusive | Executed fns | Executed bytes | What |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 1 | `scene` | 6 | rewrite | 65529 (18.2%) | 16.0% | 16.8% | 20.6% | 18.5% | 37.1% | 459/1032 | 216K | the object manager, AOF models, skinning, the framework's models |
| 2 | `render` | 5 | rewrite | 43478 (12.1%) | 11.5% | 11.3% | 14.1% | 11.4% | 23.5% | 759/1700 | 306K | the GL renderer, shaders, post-processing, cameras |
| 3 | `kernel` | 4 | rewrite | 33854 (9.4%) | 8.3% | 10.7% | 8.7% | 9.5% | 71.1% | 294/804 | 125K | tasks, fibers, the message dispatcher, the app loop |
| 4 | `sync` | 1 | rewrite | 27194 (7.6%) | 10.2% | 7.3% | 7.3% | 6.9% | 97.9% | 42/87 | 4K | mutexes, events, semaphores, threads |
| 5 | `lib_sqlite` | 0 | library | 18213 (5.1%) | 5.1% | 4.9% | 3.8% | 6.2% | 5.2% | 293/797 | 505K | SQLite 3.13.0 |
| 6 | `hash` | 0 | rewrite | 10695 (3.0%) | 4.7% | 2.8% | 3.0% | 2.3% | 3.1% | 61/332 | 14K | CHash32, SpookyHash, CRC, UTF-8 |
| 7 | `memory` | 2 | rewrite | 9867 (2.7%) | 2.8% | 2.9% | 2.4% | 2.9% | 8.0% | 133/426 | 39K | the engine heaps, allocators, handles |
| 8 | `audio` | 5 | rewrite | 9574 (2.7%) | 2.4% | 2.7% | 2.4% | 2.9% | 5.4% | 318/718 | 109K | sound and voice |
| 9 | `cocos` | 6 | track | 6671 (1.9%) | 1.4% | 1.6% | 1.5% | 2.5% | 3.3% | 384/650 | 156K | Framework::Cocos, tri-Ace's UI scene graph |
| 10 | `particles` | 5 | rewrite | 6423 (1.8%) | 1.4% | 2.6% | 1.4% | 1.6% | 2.2% | 224/2439 | 154K | particles |
| 11 | `containers` | 3 | rewrite | 5894 (1.6%) | 1.4% | 1.8% | 1.8% | 1.5% | 5.1% | 790/16057 | 193K | the engine's containers and strings (templates) |
| 12 | `params` | 4 | rewrite | 5487 (1.5%) | 2.4% | 1.5% | 1.5% | 1.2% | 4.9% | 1214/3457 | 128K | the parameter (de)serialization base: CParameterElementBase, CParameterParser, CParameterProperty* |
| 13 | `lib_vorbis` | 0 | library | 4720 (1.3%) | 0.9% | 1.1% | 1.3% | 1.7% | 1.4% | 84/206 | 29K | libVorbis 1.3.5 + libogg |
| 14 | `input` | 4 | rewrite | 4595 (1.3%) | 1.5% | 1.1% | 1.3% | 1.3% | 1.9% | 55/248 | 17K | touch, pad, mouse, keyboard |
| 15 | `resource` | 4 | rewrite | 4547 (1.3%) | 1.4% | 1.2% | 1.5% | 1.1% | 9.9% | 497/1600 | 204K | files, streams, the resource cache, the downloader |
| 16 | `dynamics` | 5 | rewrite | 4004 (1.1%) | 0.8% | 1.4% | 1.0% | 1.1% | 3.0% | 154/672 | 41K | Aska's own dynamics (cloth, joints, collision) |
| 17 | `master` | 5 | rewrite | 3771 (1.0%) | 1.1% | 1.2% | 0.8% | 1.1% | 12.0% | 2538/7030 | 1024K | master data (SQLite tables, StringDB) |
| 18 | `data_formats` | 3 | rewrite | 3613 (1.0%) | 1.6% | 1.0% | 0.9% | 0.9% | 1.3% | 98/1042 | 34K | ASON, ACSV, msgpack |
| 19 | `libcxx` | 0 | library | 3541 (1.0%) | 1.2% | 1.0% | 0.9% | 0.9% | 4.8% | 1442/25097 | 409K | libc++ / libc++abi |
| 20 | `anim` | 5 | rewrite | 3150 (0.9%) | 0.4% | 1.1% | 0.8% | 1.0% | 2.7% | 209/558 | 58K | animation controllers (TAaf*), blending, IK |
| 21 | `math` | 0 | rewrite | 3097 (0.9%) | 0.5% | 1.2% | 0.6% | 1.0% | 1.1% | 119/538 | 49K | vectors, matrices, intersection |
| 22 | `info` | 6 | rewrite | 2242 (0.6%) | 0.7% | 0.6% | 0.5% | 0.7% | 13.5% | 936/3742 | 505K | the client's info objects and parameter manager (player, roster, missions) |
| 23 | `battle` | 7 | rewrite | 2228 (0.6%) | 0.1% | 0.9% | 0.2% | 0.9% | 4.9% | 906/2103 | 588K | battle, arena, characters on the field |
| 24 | `(unassigned)` | - | - | 2222 (0.6%) | 0.7% | 0.6% | 0.6% | 0.6% | 4.1% | 1279/17510 | 442K |  |
| 25 | `lib_crypto` | 0 | library | 1980 (0.6%) | 0.9% | 0.6% | 0.5% | 0.4% | 0.6% | 4/8 | 1K | the bundled OpenSSL pieces |
| 26 | `ui` | 7 | rewrite | 1827 (0.5%) | 0.5% | 0.4% | 0.5% | 0.5% | 6.5% | 1010/9230 | 531K | screens, menus, dialogs, the home and gacha screens |
| 27 | `lib_zstd` | 0 | library | 1257 (0.3%) | 0.2% | 0.4% | 0.3% | 0.4% | 0.4% | 21/321 | 26K | zstd |
| 28 | `game` | 7 | rewrite | 1233 (0.3%) | 0.4% | 0.3% | 0.3% | 0.3% | 17.2% | 203/895 | 77K | the game's phases, transactions, API notifications, the tutorial |
| 29 | `yayoi` | 4 | rewrite | 1168 (0.3%) | 0.5% | 0.3% | 0.3% | 0.3% | 6.1% | 134/2771 | 59K | Aska::Yayoi: network and the SQLite driver |
| 30 | `lib_zlib` | 0 | library | 245 (0.1%) | 0.0% | 0.1% | 0.1% | 0.1% | 0.1% | 2/10 | 2K | zlib 1.2.5 |
| 31 | `event` | 7 | rewrite | 147 (0.0%) | 0.0% | 0.0% | 0.0% | 0.1% | 0.1% | 166/761 | 116K | story scenes (EventScenario) |
| 32 | `lib_jpeg` | 0 | library | 60 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 0.0% | 53/199 | 25K | IJG libjpeg 9b |
| 33 | `text` | 5 | rewrite | 30 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 0.0% | 13/98 | 3K | fonts and text layout |
| 34 | `bullet` | 0 | track | 27 (0.0%) | 0.0% | 0.0% | 0.0% | 0.0% | 0.0% | 21/801 | 4K | Bullet Physics 2.7x (the version pin) |

## Waves (dependency order; hottest first within a wave)

| Wave | Subsystem | Guest self | Depends on (measured calls down, samples) | Same-level calls (co-develop) | Callbacks from it upwards |
|---|---|---|---|---|---|
| 0 | `lib_sqlite` | 5.1% | - | - | - |
| 0 | `hash` | 3.0% | - | - | scene (252), containers (70) |
| 0 | `lib_vorbis` | 1.3% | - | - | audio (73) |
| 0 | `libcxx` | 1.0% | - | - | memory (6655), containers (5400), cocos (1502), info (793) ... |
| 0 | `math` | 0.9% | - | libcxx (78) | memory (306), kernel (116), dynamics (54), scene (51) |
| 0 | `lib_crypto` | 0.6% | - | - | - |
| 0 | `lib_zstd` | 0.3% | - | - | - |
| 0 | `lib_zlib` | 0.1% | - | - | - |
| 0 | `lib_jpeg` | 0.0% | - | - | - |
| 0 | `bullet` | 0.0% | - | - | - |
| 1 | `sync` | 7.6% | - | - | kernel (245500), render (55006), scene (28317), resource (9018) ... |
| 2 | `memory` | 2.7% | sync (18426) | - | containers (302), scene (172) |
| 3 | `containers` | 1.6% | memory (4055), libcxx (1650), math (573), hash (143) | - | yayoi (1099), resource (728), scene (446), kernel (444) ... |
| 3 | `data_formats` | 1.0% | math (172), memory (99) | containers (629) | resource (79) |
| 4 | `kernel` | 9.4% | sync (11870), memory (1384), math (376) | resource (18512), input (5510) | scene (65870), info (34139), ui (16863), battle (14515) ... |
| 4 | `params` | 1.5% | hash (7930), memory (2200), libcxx (1130) | - | info (60) |
| 4 | `input` | 1.3% | sync (1688) | kernel (401) | - |
| 4 | `resource` | 1.3% | libcxx (8427), containers (4597), memory (4494), data_formats (990), sync (731), hash (80) | kernel (3444) | render (4019), info (2029), ui (697), cocos (51) |
| 4 | `yayoi` | 0.3% | lib_sqlite (18226), data_formats (1066), containers (86), memory (74) | resource (1040), kernel (218) | - |
| 5 | `render` | 12.1% | sync (2549), resource (1823), kernel (754), containers (690), math (403), data_formats (203) ... | anim (621), particles (276) | scene (28738) |
| 5 | `audio` | 2.7% | libcxx (1979), params (1477), memory (1265), sync (1131), resource (864), lib_vorbis (809) ... | anim (932), master (146) | ui (63) |
| 5 | `particles` | 1.8% | kernel (928) | render (367) | scene (161) |
| 5 | `dynamics` | 1.1% | kernel (4189), math (1023), sync (311) | anim (179) | scene (1350) |
| 5 | `master` | 1.0% | yayoi (15864), params (15830), memory (4963), data_formats (1555), hash (541), libcxx (263) ... | - | info (886), ui (146), battle (129) |
| 5 | `anim` | 0.9% | containers (2997), kernel (1688), math (236) | render (226), audio (139), particles (138) | scene (876) |
| 5 | `text` | 0.0% | - | - | - |
| 6 | `scene` | 18.2% | render (42545), sync (12889), kernel (4063), anim (3180), resource (1022), hash (999) ... | - | ui (503), battle (155) |
| 6 | `cocos` | 1.9% | libcxx (1910), data_formats (451), memory (333), resource (101), containers (95) | scene (1072), info (387) | ui (1492), event (55) |
| 6 | `info` | 0.6% | master (7058), audio (4341), libcxx (2328), hash (1076), containers (557), resource (460) ... | - | game (27189), ui (2543) |
| 7 | `battle` | 0.6% | scene (5115), master (3734), info (1376), resource (1031), math (649), audio (609) ... | game (7101), ui (161) | - |
| 7 | `ui` | 0.5% | master (9640), info (6275), cocos (1740), scene (1284), audio (963), resource (825) ... | game (15046), battle (648) | - |
| 7 | `game` | 0.3% | master (21916), yayoi (4628), resource (3110), info (3065), anim (411), scene (324) ... | ui (16846), battle (8350) | - |
| 7 | `event` | 0.0% | cocos (88) | - | - |

Hottest unassigned families: (free functions) (1019), ~(before first export) (442), ~(free functions) (20), LocalSetControllerU24_* (14), CWeaponObject (12), LocalSetControllerF32_* (11), Aska::ResourceManager (11), ~ANativeActivity_* (11), CCoinShopCallerWait (11), CTitleLogo (11), CBaseDamageObject (11), ObjectController (11), PersonModel (11), Aska::IDEPrimitiveHeightObject<> (11), CLimitAreaObject (11), CInitializeDialog (10), Aska::Machine (10), Aska::FrameBuffer (10), Aska::JpegUtil (10), LoginBonusModel (9), ~Aska::IDeleteObject (9), Framework::CDirectTexture (9), UniverseAddStatusInfo (9), Aska::AhslConst (9), AttackHitChecker (9)

## The queue

Among subsystems whose types are ready, hottest first (port/PLAN.md task 6):

1. **From day one, independent tracks** (no dependency on the waves): the libraries, `lib_sqlite` first (5.1%:
   the master DB's queries; in the samples `Aska::Yayoi`'s SQLite driver is its only caller), then `lib_vorbis` (1.3%),
   `lib_crypto` (0.6%: `AES_decrypt`), `lib_zstd`, `lib_zlib`, `lib_jpeg`; `libcxx`
   (1.0% self but 25,097 functions: the templates instantiated with the game's allocators call `memory`, so
   they move with `memory`/`containers`); `cocos` (1.9%, its own track); `bullet` (0.0% in these flows: the
   version pin is research, not a hot path).
2. **Wave 0-2, the leaves, small and hot:** `sync` (7.6% in 42 executed functions: `Framework::CMutex::Lock`
   alone is 4.0% and `Unlock` 2.1%, most likely contention spinning in guest atomics, which a host mutex turns into waiting), `hash` (3.0%:
   `Framework::CHash32::CHash32(char const*)` 2.3%), `memory` (2.7%: `Aska::MemoryManager::Malloc` /
   `LocalFree`), `math` (0.9%). Their natives call up into everything (thread entries, `Event::Set` waking
   handlers) only through function pointers, so they need no other subsystem's types.
3. **Wave 3:** `containers` (1.6%; 16,057 functions, mostly templates: port the instantiations that execute)
   and `data_formats` (1.0%: ASON).
4. **Wave 4:** `kernel` (9.4%: `Aska::SimpleMessageDispatcher` 6.5%, `TaskManager`, the fiber kernel; it
   calls every system through tasks, i.e. callbacks), `params` (1.5%), `input` (1.3%), `resource` (1.3%),
   `yayoi` (0.3%, after `lib_sqlite`).
5. **Wave 5, the engine systems:** `render` (12.1%; co-developed with `scene`: the render thread calls the
   objects' `Render`), `audio` (2.7%, after `lib_vorbis`), `particles` (1.8%), `dynamics` (1.1%), `master`
   (1.0% self, 12% inclusive: master-data loads), `anim` (0.9%), `text`.
6. **Wave 6:** `scene` (18.2%, the hottest: `Aska::ObjectManager` 7.0%, `ObjectManagerJobDispatcher` 4.1%,
   `ObjectManagerWorkerThread` 3.6%; needs `render`'s, `anim`'s and `sync`'s types), `info` (0.6%).
7. **Wave 7, the game:** `battle`, `ui`, `game`, `event` (each under 1% self; large: 2,100 / 9,200 / 900 /
   760 functions); they are where the client's behaviour lives, so they come last and are tested by the
   `tests/diff/` flows as much as by differential tests.

The type-recovery agents run a wave ahead: while wave N's code is written, wave N+1's structs (its layout
headers) are recovered, starting with the types the dependency column names.

