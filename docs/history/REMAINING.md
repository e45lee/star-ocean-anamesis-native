> **History.** This is the 3.8.0-era status/remaining-work document (last updated 2026-10-01 before the rebase); the fresh one is port/REMAINING.md. The port now runs the 3.7.0 client (tag `pre-rebase-370` is the old port); the current plan is [`port/PLAN.md`](../../port/PLAN.md) and the remaining work is [`port/REMAINING.md`](../../port/REMAINING.md).

# What's left before the port is a native C++ game

## Status update: 2026-09-30 morning (`linux-port` after the overnight run)

The detailed inventory of 2026-09-28 follows this section. It still holds for the *default* game (the offline 3.8.0 behaviour), with the counts below updated. This section adds what has been done since and what is left, including the new `--restore` work (the original 3.7.0 online game, played locally).

### Numbers (fresh profiles, 2026-09-29)

| Measure | Default game (smoke run) | `--restore` session (boot, battle, results) |
|---|---|---|
| Native replacements registered | 16,789–16,802 (was 14,997) | same |
| Native share of guest + native busy time | **79.3%** | **71.9%** |
| Guest JIT share of all busy time | 16.5% | 20.8% |
| Executed functions that are native | 2,419 of 8,043 (30.1%) | 3,275 of 11,447 (28.6%) |

`--restore` runs about 3,400 more guest functions than the default game: battle, particles and cloth, character actions, result screens and the local server's flows. That's why its native share is lower.

### Done since the 2026-09-28 inventory

- **Battle, gacha, debug and the offline server.**
  - About 1,540 new natives (`PLAN-battle-gacha-debug.md`): `FakeApiCaller`; `CApiNotify` (197 of 224); the battle state machine, formulas, factors and presentation; the gacha manager and dialogs; the debug-window core.
  - A real battle and gacha draw play through with the opt-in fake server and the 3.7.0 download.
- **Restoring the original game** (`PLAN-restore-original.md`; all behind `--restore`):
  - **The local server emulator** (`server/`). It has persistent state and every rule is labelled by source in `docs/server-rules.md`. It covers:
    - login and player;
    - missions: stamina, EXP, FOL, weighted, surprise, campaign and evaluation drops, and unlocks;
    - gacha: reconstructed pools, currency, step-up and box gacha, chips;
    - growth, items, shops and exchanges, login bonus, achievements, favorability, party sets, assist, the home character;
    - error dialogs;
    - the frozen clock, fixed.
  - **Client restores, all logged in `docs/client-changes.md`:**
    - the Episode 1 story campaign from the real UI;
    - party building, character sort and filter, the home-character select;
    - title, login, new player and the battle tutorial;
    - favorability;
    - the picture book.
- **Infrastructure.**
  - The 3.7.0 test oracle (`t.call370`), the version diff (`tools/verdiff.py`), the restore image (`native/restore/restore370.cpp`: exact and pattern groups), and gacha banner extraction (`tools/extract_banners.py`).
  - The Ghidra quick projects are committed (`ghidra/`, LFS).

### What's left

**Day run of 2026-09-29 (09:30–18:00; plan `~/.claude/plans/fluttering-weaving-peacock.md`).** Merged into `linux-port`:
- **flaky** (5bdaa51): the intermittent selftest SIGSEGV was stale JIT code for freed/remapped guest code pages. Fixed by `invalidate_guest_code` / `map_guest_code` / `unmap_guest_code` (`core/cpu.h`).
- **livetests** (c7eb63e): the remaining one-off selftest failures (`containers/a2c-camera`, `render/state-setters`, `render-a2c/live`, `models/hierarchy-live`) were tests reading live state. They are now deterministic, and `SOA_SELFTEST_REPEAT=N` repeats tests.
- **config-cleanup** (9582f55): typed `RunOptions` (`core/options.h`, `soa::options()`). Env vars are inputs only, and no `setenv` of game or run state remains (a selftest checks this). It also adds `--clock`, `server::event_now()` (today's month and day replayed onto the newest year with open event terms, label d), and fixes the campaign `in_window` clock bug.
- **home370**: the 3.7.0 home (restore370 groups `home`, `common` footer, `othermenu`) and `FooterMissionInfo` (`server/api_home.cpp`).
  - Buttons: events (locked, `is_open_event_mission` = 0 until the events plan), missions, Sphere 211, deep space.
  - The side menu, the 3.7.0 footer (gacha and shop reachable), and the full その他 list.
  - The popup mask 0x7b with the login bonus working. `home_session.sh`.
- **gaps-core**:
  - Episode 2/3 opening movies end: audio paced by the wall clock, plus the `movie_playing` start race (`episode_movie_session.sh`).
  - The new-player crash is gone; `newplayer_session.sh` reaches home.
  - Rental helpers (`server/api_follow.cpp`, `BattleRental` roster clones, rental bonus; `rental_session.sh`).
- **server-rules**: gear (`api_gear.cpp`), premium and favor login bonuses (`api_daily.cpp`), present-box texts, evaluation types 2/5, step-up state, battle status from the client's own `CalcStatus` (factors, talents, seeds, gear), type-8 campaigns (×1.5 favor), favor achievements. Also growth-screen fixes and `growth_session.sh`.
- **deepspace**: deep space restored (`server/api_deepspace.cpp`, all 5 APIs).
  - Areas, auto-select, expeditions on the server clock, collect, quick return and area unlocks work on screen.
  - `clock:+SECONDS` control command; `deepspace_session.sh`.
- **sphere211**: Sphere 211 restored (`server/api_sphere211.cpp`, the 13 APIs).
  - The season comes from `event_now()`; past the last season the latest one repeats, with its dates shifted into the client's master (label d).
  - Floors and cells, stamina, continue and retire, floor clear, floor select, 帰還 with treasure all work on screen.
  - Missions whose map files are missing are skipped at runtime.
- **Inventory**: `tools/event_coverage.py` generates `docs/restore-inventory.md`, covering events (FULL, PLAYABLE, BROKEN), Sphere 211, the tower and banners, plus a per-event guide with English notes from `docs/event-notes.tsv`. Nothing is hard-coded; rerun it after downloading more assets.

Final gate on the merged tree (bf299a6 + script fixes, 17:10–17:49):
- full `--selftest` 471/471; smoke PASS;
- `restore`, `campaign`, `party`, `home`, `newplayer` (to `UpdateTutorial(7)` / home) and `rental` sessions pass. `rental_session.sh` needed the 3.7.0 home: it now closes the LOGIN BONUS popup and taps ミッション at x 270.
- `deepspace_session.sh` failed on the merged tree. The cause was the script (fixed in dc81817): it never closed the 3.7.0 LOGIN BONUS popup. `phase:6` bypassed the popup, and its 閉じる button then took the result page's OK tap. It now passes twice; deep space itself was fine.
- `restore_session.sh` ends with the gacha result (閉じる) still showing in its last shot instead of home. The script has no PASS/FAIL line, so this goes unnoticed. Tap timing or flow at its gacha ending; worth a look.

**Overnight run of 2026-09-29/30 (20:30–07:00; plan `~/.claude/plans/fluttering-weaving-peacock.md`).** Merged into `linux-port`:
- **Events** (events-core, events-extras):
  - `ActiveEventMissionList`, and the event dates in the client's master moved forward in whole years onto the replayed calendar.
  - Runtime gating: maps, enemy models and story scripts. Nothing is listed by name. See `docs/restore-inventory.md`.
  - The events button is open. Event stories clear.
  - `CampaignInfo`, and campaigns on the event calendar.
  - Local single-entrant rankings; world boss, big hunt and time bonus; favor event drops; exchange shops on the calendar.
  - `events_session.sh`.
- **Tutorial damage** (tutorial-dmg, cleanups):
  - The NPC party's stats, weapons, factors, talents and skills come from the client's own NPC model. Damage was 20–45 % low before.
  - `SOA_BATTLE_DAMAGE_LOG=1`.
- **Docs:** per-API wire format in `docs/api.md`, plus `docs/ason.md` and the `wire/` selftests.
- **Native code** (live record/replay checks, 0 mismatches on what is registered):

  | Family | Native now |
  |---|---|
  | Hair/cloth dynamics | 96 transcribed, 52 entries |
  | Particle simulation | 181 functions, some readable |
  | Particle rendering | 33 functions |
  | `CCharacterObject` | many more, in `battle_charobj*` |
  | `CArena` / effects / collision | 171 functions |
  | Animation / object base layer | 91 verified |
  | InfoBase deserializers | 361 |
  | `Aska::Sequencer2` notes | all |
  | `CMissionMenu::Initialize` | 1 |

- **Audio:** a null sink drains the OpenSL queues when no device pulls. Sounds now end, and the scene-end StopSE workaround is gone.
- **Test infrastructure:**
  - Session scripts resend phase-changing taps and close the login popups reliably. The popups were the real cause of the load-dependent session failures.
  - `restore_session.sh` prints PASS/FAIL.
  - Server tests fail loudly without data.
  - A memory watchdog runs during agent runs: a leaking live check once reached 29 GB.
- **Privacy:** the local player is always `LOCAL00001`, never the save's real `BAS:PlayerID`. The old id stays in already-pushed history (the user chose a forward fix).

Final gate (2026-09-30):
- on 6630dc6, all branches merged: full `--selftest` 534/534, `smoke.sh` PASS, `restore_session.sh` PASS;
- on 6555267 (all but the last arena batch): campaign, party, newplayer, home, deepspace, rental and events sessions PASS.

**Profile after the overnight run** (`work/profile/restore-20260930/`, `restore_session.sh`, SOA_PROFILE):

| Share of busy time | 2026-09-29 evening | 2026-09-30 morning |
|---|---|---|
| guest JIT | 15.1% | 10.3% |
| native replacements | 52.9% | 65.3% |
| HLE imports | 31.9% | 24.2% |
| native / (guest + native) | 77.8% | 86.4% |

17,816 native replacements are registered (was 16,798).

**1. Test infrastructure.**
- Flaky tests (D3, done): `ui/settings-misc` compared heap garbage past a short stored value (now masked); `event/interpreter-fuzz`, `battle/manager-progress` and `screen/a2c-live` failed only before the JIT-invalidation fixes and the shared live check.
- A committed synthetic seed save (with a sanitized id) would let the server tests run in fresh checkouts.

**2. `--restore` gaps left.**
- **Events:** 35 events lack a battle map or enemy model, and 66 lack some story scripts. Story missions without scripts aren't offered, so battles gated behind them stay locked. Rankings are only unit-tested: every ranking group is in `event_god_86`, whose assets are incomplete. `GetPlayerDetailInfo` answers the player state only.
- **Tower:** off in 3.7.0 too (`IsOpenTowerMission` returns 0). The opt-in (`--restore-tower`) is **unmerged**: WIP on `port/sphere211-tower-wip` (868401b) and `port/tower-wip2` (09f0176). The downloaded `eventmission_top.csf` lacks the tower's nodes (`play_plate/0-3`, `panel/banner_0/1`, `page_icon_*`, `btn_restart_old`), so the tower menu shows no floor list. It needs the original layout or rebuilt UI nodes; stand-ins must be capped per numbered name, or `CTowerMissionMenu` loops forever.
- **Sphere 211:**
  - Stamina heal, reroll, pause-menu continue and ranking screens are unit-tested only.
  - The rental slot and weekly challenge / achievements aren't served.
- **Deep space:** coin-bought and subscription ships, achievements, daily and weekly limits.
- **Helpers:** the NPC weapon for event NPC helpers, and the `CRentalBonus` popup.
- **Home:** titles are served (defaults + achievement rewards) and the notice board shows the local server's page; the achievement-earned titles of a seeded player aren't pre-granted (they come through the 実績 rewards). The episode-select UI hints of 3.7.0's `CMissionSelectPart` aren't restored.
- **Server rules:** barney-chance effects, the favor-login-bonus limit key; gear removal in game was fixed but not re-verified.
- **Other modes:** world map and multiplayer (NPC stand-in).
- **Documented assumptions to revisit:** the `docs/server-rules.md` registers.
- **Seed:** `samples/Game.xml` (the 3.8.0 save; its id is never copied). The 3.7.0 save would be preferred if restored.

**3. Guest code on the `--restore` paths** (take a new profile; the 2026-09-29 profile predates tonight):
- `CArena`: the hand-written Progress functions, pending the arena follow-up (see its branch).
- `CAnimationBlendContainer::PlayAnimation` / `ProgressBlend` / `ProgressFrame` and 68 more objbase functions: transcribed, but unverified. They run with `SOA_OBJBASE_ALL=1`, which crashed once at home.
- `Callback_EndPostProgress`: a rare position difference, unexplained.
- One particle `RenderProcedure` instantiation: a 1-byte difference at +0x1ac. Four render bodies were never reached by a check.
- `GetVelocityByAet`: needs `fcvtmu` in a2c.
- `CPartyManager` and the remaining battle glue.

**4. Readability.** About 1,300 natives are still exact a2c transcriptions (estimate):
- models (643 symbols);
- ObjectManager `ViewFrustumCulling` / `Prerender*` / `OnPostPaint`;
- render (post-processing, camera, lights, shadows);
- containers (465);
- Cocos (list views, labels, GUI reader);
- screens (27);
- `CApiNotify::DeserializeToInfo`.

**5. Leaving the JIT.** Unchanged: see section 4 below. Phase 5 hasn't started.

---

## Inventory of 2026-09-28

Inventory as of 2026-09-28, taken on `linux-port` after the containers merge (commit `2cb034c`, 14,997 native replacements resolved). It is the input for planning phase 5 of [the 2026-09-28 plan](PLAN-native-port-2026-09-28.md). Every number below comes from the runs described in "Data"; `port/scripts/remaining.py` regenerates the tables.

## Headline numbers

| Measure | Value |
|---|---|
| Busy time in native replacements | **78.1%** (the figure includes host GL calls made from inside natives) |
| Busy time in guest JIT code | **15.5%** |
| Busy time in HLE imports called from guest code | 6.4% |
| Native share of guest + native busy time | **83.4%** (140,598 / 168,501 samples) |
| Executed functions that are native | **2,564 of 9,490 (27.0%)**. This is a lower bound: call counts only see natives that guest code calls, so a native reached only from other natives isn't counted. |
| Executed functions that are still guest code | **6,926** (2.4 MB). Of these, 774 are lone-`RET` stubs that are already complete (section 1d), which leaves **6,152** real ones. |
| Natives as a share of the whole function table | 14,997 of 103,123 entries (14.5%) |
| Natives transcribed by a2c vs hand-written | **6,148 transcribed** (about 1,420 distinct bodies) vs **8,849 hand-written** or generated from reverse-engineered layouts |
| Function table entries that never ran and aren't native | 81,200 (15.3 MB), 7,687 of them lone-`RET` stubs |

**What the numbers mean:**
- Time is no longer the problem. Guest code is about a sixth of busy time, and no single guest function exceeds 0.45% (the hottest is `DroidLoop`, 778 of 179,992 busy samples).
- What remains is breadth: 6.9k executed functions spread over 1,079 families, most of them cold. 4,171 of them (60%, 411 KB) never showed up in a single profiler sample.
- Past those, 81k functions never run at all.

Shares are stable across the three runs:

| Run | Wall time | Guest | Native | HLE | Executed | Native executed |
|---|---|---|---|---|---|---|
| smoke | 86 s | 12.5% | 77.5% | 10.0% | 7,454 | 29.4% |
| long session | 478 s | 16.0% | 78.1% | 5.9% | 9,182 | 27.5% |
| extra flow | 604 s | 15.7% | 78.2% | 6.0% | 8,643 | 27.5% |

## Data

All runs used the build above, natives installed, and `SOA_PROFILE` + `SOA_COVERAGE`. Busy time is sampled at 1 kHz on every guest thread, 179,992 busy samples in total.

- **smoke** (`port/scripts/smoke.sh`): title → home → character list → detail → other menu. It passed against the baseline (RMSE ≤ 0.0714).
- **long session** (`work/profile/session.sh`), about 8 minutes:
  - Episode 1, then scenario library ch.6, stories 6-31 and 6-29 on auto;
  - the character encyclopedia, detail, and the status and skill popups;
  - home, interactive 3D mode with touches;
  - the other menu and settings.
- **extra flow** (`port/scripts/profile_extra.sh`, new), 10 minutes. It covers what the other two don't:
  - all three settings sub-screens (graphics, sound, event), with slider taps, scrolling and close;
  - copyright, credits and terms of use. These three pages are WebViews and render empty in the port.
  - Episode 3, the (empty) sub-story tab, and story 2-18 with backlog, fast-forward and skip;
  - the character list scrolled end to end, another character's talent and ability popups;
  - "back to title", a restart from the title, and the home mascot's line.

  It uses fixed waits, so check its screenshots. On a loaded machine the first navigation can land during the data check.

Regenerate with:

```sh
soa --list-native > native.tsv
port/scripts/remaining.py RUN1 RUN2 RUN3 --native-list native.tsv --tsv guest-exec.tsv
port/scripts/profile_report.py RUN1 RUN2 RUN3 --native-list native.tsv
```

- `--tsv` writes one row per still-guest executed function: offset, size, self and inclusive samples, first run at boot, family, name.
- The coverage traps are armed only on entries that aren't native. Executed natives come from `calls.tsv`.
- "Boot" means first run before the title screen, which is the first `CTitle*` function's first-hit time in each run.
- Local functions are assigned to the family of the preceding export. That is a hint, not a certainty.

## 1. Executed functions that are still guest code

### By work package

Families are grouped into work packages by `remaining.py` (`PACKAGES`), sorted by guest self time.

- **Self:** guest self samples.
- **Boot:** functions first run before the title screen.
- **Unsampled:** functions with no profiler sample, not even inclusive.
- **<8B:** functions shorter than 8 bytes, which can't be hooked.
- **Estimate:** in agent-waves, calibrated on wave 1. Hand-written ports ran at about 60-260 functions per agent per wave (Cocos 61, render 82-90, event 102, sound and input 152, UI 260). Generated or transcribed ports ran at hundreds to thousands (containers: 1,500).

| Package | Fns | Bytes | Self (%busy) | Boot | Unsampled | <8B | Flags | Estimate | Main families / notes |
|---|---|---|---|---|---|---|---|---|---|
| Main loop, threads, timing | 327 | 86K | 3.6% | 147 | 195 | 59 | hot, boot | 3 | `DroidLoop`, `Framework::CApplication` (`CMainTask::Run`), `CFiberKernel::Progress`, `Aska::PeripheralManager` / `Sequencer2` / `VSync` / `WaitVSync` / `NotifierThread` / `PerformanceCounter` / `Thread`, `CPhase*`. Every guest thread's `Handler` is here, so this package is the precondition for running without the JIT. |
| Render remainder (device, targets, passes, shadows, post-processing) | 523 | 189K | 2.6% | 327 | 228 | 29 | hot | 5 | `Aska::RenderThread::Handler`, `RenderDeviceGL` (50 still guest, including `SwapBuffers_RenderThreadContext`), `_RenderDeviceGL`, `RenderManagerBase::BeginRender`, `RenderTargetManagerGL`, `ShadowManager*` (render3 has it), `PostProcessCombinerTBR`, `OpticalPhenomenon`, `CameraFilter` |
| Cocos UI framework + UI managers | 485 | 194K | 2.2% | 138 | 199 | 33 | hot | 5 | `Framework::Cocos` (305 fns: `CCocosImage` / `CCocosLabel::DrawSelf`, …), `CUIObject::PreProgress`, `CUIManager`, `CDialog*`, `CFaderView_Color` |
| Sound and voice remainder | 252 | 81K | 1.7% | 73 | 96 | 1 | hot | 3 | `Aska::SoundObject::RequestGet`, `AudioPlayer::GetMessage`, `MultiMediaStream`, `WavePlayer`, `SEControlObject`, `Audio3DObject`, `CMenuVoiceManager`, `CUIVoiceManager` |
| Resources, files, streams, memory | 545 | 178K | 1.0% | 380 | 259 | 31 | boot-heavy | 4 | `Aska::AHSLCacheManagerV2`, `LIBLManager::CopyTexture` (hot), `CGameResourceManager`, `Framework::CResourceManager` / `CSTLStringUtility_Base<>` / `CFileLoader`, `MappedMemoryManager`, `Decompress*` |
| Platform, store and download polling | 238 | 67K | 0.9% | 107 | 123 | 35 | hot, boot | 2 (stubs) | `CGameAssetPackManager::Progress_Download` (polled every frame), `AssetPackLocation_*`, `CPaymentManager` (hot poll), `CDownloadingBar`, `CGameResourceDownloader`, `CWebView`, `NetworkApiCaller` ctor. Offline these should become explicit stubs, not ports. |
| Screens and menus | 762 | 406K | 0.7% | 6 | 488 | 199 | cold | 7 | `CCommon`, `CSystemSettingMenu` (199 fns, 83 of them < 8 B), `CHome`, `CMissionMenu`, `CHomeModelViewManager`, `StaminaUtility`, `COtherMenu`, `CScenarioLibrary`, `CCharacterPictureBook`, `CDetailDialog*` |
| libc++ template instances | 742 | 191K | 0.6% | 168 | 526 | 158 | tiny-heavy | 3 (generator) | `std::__ndk1` instances not yet covered by the 921 libc++ natives: vectors, trees and `function` of game types |
| Particles, effects, dynamics | 248 | 66K | 0.5% | 37 | 128 | 6 | hot | 3 | `Aska::ArticulatedDynamicsManager*` (hair and cloth), `ParticleRenderableBase`, `IParticleEmitter`, `ParticleManager`, `Framework::CEffectManager` |
| Scene objects, models, animation | 311 | 103K | 0.5% | 19 | 149 | 12 | hot | 3 | `CSceneObjectContainer::Progress`, `Framework::CAnimationBlendContainer` / `CAnimationModel` / `CCamera`, `CArena`, `CThingObject`, `CCharacterObject` (27K), `PersonModel` |
| Master data, parameters, user info | 1,625 | 502K | 0.5% | 771 | 1,263 | 432 | cold, boot | 4 (generator) | the `CSimpleSqliteConnector<>` and `CMasterParameterBaseSqlite_*<>` instances the loader generator doesn't cover yet (many are lone-`RET` / tail-branch stubs), `CParameterUtility` (68K), `CMasterManager` (37K), `CInfoManager` (59K), `C*Info` |
| Event scenario remainder | 144 | 102K | 0.3% | 0 | 77 | 13 | cold | 2 | `EventScenario` handlers still in guest code: 7 of the 78 commands, plus scene setup and teardown |
| Locals before the first export | 150 | 174K | 0.1% | 150 | 31 | 0 | boot | 2 | Static constructors (`.init_array` has 151 entries) and early runtime code, all run at load. Mostly data initialisation: move it into C++ static data. |
| Textures, pixel formats, image decode | 115 | 53K | 0.1% | 56 | 44 | 2 | | 1-2 | `Aska::TextureManager`, `IPixelFormatGL`, `DecodeTextureQueue`, `DecodeJpegObject` |
| Other | 459 | 41K | 0.1% | 358 | 365 | 31 | init | 1 | `ANativeActivity_*` / `android_*` (native app glue), `Framework::CPad`, `CDelayDelete`, small leftovers |
| **Total** | **6,926** | **2.4M** | **15.5%** | 2,737 | 4,171 | 1,041 | | **~50** | |

At about five parallel agents per wave, this is roughly 10 waves of wave-1-style work to make every executed function native. The generator-shaped packages (libc++, master data) and the stubs are the cheap part.

### (a) Hot families

- 69 families have ≥ 100 guest self samples (≥ 0.056% of busy time).
- Together they are 1,972 functions and 910 KB, and 11.5% of busy time (74% of what is still guest).
- The top 20 by self time:
  - `Framework::Cocos` 1.5%;
  - `std::__ndk1` 0.6%;
  - free functions (`DroidLoop`) 0.5%;
  - `Framework::CApplication` 0.4%;
  - `Framework::CFiberKernel` 0.3%;
  - `Aska::PeripheralManager` 0.3%;
  - `Aska::Sequencer2` 0.3%;
  - `Aska::SoundObject` 0.3%;
  - `Aska::RenderThread` 0.3%;
  - `Aska::VSync` 0.3%;
  - `EventScenario` 0.3%;
  - `Aska::RenderManagerBase` 0.2%;
  - `Aska::RenderDeviceGL` 0.2%;
  - `Aska::NotifierThread` 0.2%;
  - `CGameAssetPackManager` 0.2%;
  - `Aska::Thread` 0.2%;
  - `CSceneObjectContainer` 0.2%;
  - `CUIObject` 0.2%;
  - `CCommon` 0.2%;
  - `Aska::AudioPlayer` 0.2%.
- 26 of the hot families (245 functions, 3.2% of busy time) are loops or threads started at boot: the thread handlers, VSync / WaitVSync, the peripheral and notifier threads, and the asset-pack / payment polls.
- Hot and unowned after wave 1 (flagged by the containers agent): `NotifierThread::Notify`, `GPUSync::Notify`, `LIBLManager::CopyTexture`, `CFiberKernel::Progress`, `CMainTask::Run`, `CSceneObjectContainer::Progress`, `Aska::CameraFilter`. `ShadowManager` is owned by render3.

### (b) Init-only code

- 2,737 executed functions (888 KB) first run before the title screen.
- 466 families (889 functions, 198 KB, 0.7% of busy time) run only at boot and never get hot. Examples: `CPlayerInfo`, `Aska::LocalKVS`, `Aska::ResourceManager`, `Framework::CCSV`, `Aska::AHSLDatabase<>`, `Aska::DecompressStream`, `sqex`, `CBattleLogInfo`, `CDirectItemShopInfo`.
- Porting this code gains no speed. It matters only for leaving the JIT.
- Much of it only deserialises canned data (`C*Info` from the FakeApi responses) or sets up singletons. Rewrite it data-first: parse the canned responses in C++ and build the objects directly.

### (c) Tiny wrappers

- 1,928 executed functions are 16 bytes or less (14 KB).
- 275 families consist mostly of such functions: getters, setters, `this`-adjusting thunks and one-line forwarders. They account for 0.0% of time.
- They are cheap to port in bulk (a table-driven generator from the disassembly, as `CParameterPropertyBase::NameHash` / `CompareName` were done). Better still, they disappear when their callers become native.

### (d) Too small to hook (< 8 bytes)

- 1,041 executed functions are shorter than 8 bytes. `native.cpp` refuses them because the SVC+RET patch doesn't fit.
- **774 are lone `RET`s:**
  - families: `std::__ndk1` 128, `IInfoBaseMap<>` / `InfoBaseArray<>` / `InfoBaseValueArray<>::Initialize`, `CSystemSettingMenu` 83, `CSimpleSqliteConnector<>` 82, `CMissionMenu`, `TBinaryNode` Init/Term/destructors, `App*Proxy` setters;
  - they do nothing, so they are complete as they are, and the installer skips them on purpose;
  - they inflate the executed-guest count, so they are counted separately above;
  - the `--no-jit` build maps them to a host no-op.
- **267 are tail branches (`b <target>`)**, 170 of them in `CSimpleSqliteConnector<>`. Each goes native together with its target. The installer already leaves one alone when its target is native.
- For the `--no-jit` build, derive a table of host equivalents keyed by guest address mechanically: `ret` → no-op, `b X` → call X. The a2c-transcribed callers need this table too.

## 2. Transcribed natives to rewrite as readable C++

These bodies are exact ARM64 → C++ transcriptions (`tools/a2c.py`, `tools/gen_*_a2c.py`). They are bit-exact and fast, but not readable, and they still assume the guest image:

- they keep an ARM64 register file (`A64& r`);
- they call guest code by address, directly or through `.plt` stubs;
- they call through guest vtables (`models_icall`);
- they load `.rodata` / `.got` / `.bss` by guest address.

They are the largest block of code that can't survive dropping the ELF image.

| Family | Natives | Distinct bodies | Source (lines) | Called from guest code in these runs | Notes |
|---|---|---|---|---|---|
| Models / animation (`models (a2c)`) | 672 | 672 | `models_a2c.cpp` 116k + `models_a2c_insn.cpp` 80k | 110 | `TAaf*` controllers, `AafCalcCommonFunctor`, hierarchy and bone matrices, `AofObject` / `DirectAof*` render prep, Asf/Aaf loaders |
| Models, same code (`models (a2c, same code)`) | 4,728 | (shares the 672 above) | — | 1 | `TAaf*` template instances whose machine code is identical to a primary body |
| Containers / Yayoi / Global (`containers_a2c.cpp`, merged today) | 444 | 444 | 46.5k | 258 | `TDynamicArray` / `TArrayIterator` inserts, `Algo::QuickSort`, `TPoolFast`, `THashMap`, executed `Yayoi` / camera / misc. The 901 node-container natives (`TBinaryTree` / `THash` / `TCategorizeHash`) and `TPoolLegacy` (165) are table-driven hand-written C++, not transcriptions. |
| Aska math (`aska_math_a2c.cpp`) | 212 | ~212 | 34k | (part of 26 math natives called) | Matrix / Matrix34 operations, `MatrixCalcFunc`, `ToColor`. The other 37 math natives in `aska_math.cpp` are hand-written. |
| Render pipeline (`render (a2c)`) | 48 | 48 | `render_a2c.cpp` 11k | 34 | post-processing / bloom, camera, lights, projectors, queue producers |
| ObjectManager (`objmgr_a2c.cpp`) | 13 | 13 | 11k shared with the next two | — | `ViewFrustumCulling`, `MakePaintingList(+Post)`, `TOMQuickSort`, `Prerender*`, occlusion culling |
| SimpleMessageDispatcher (transcribed) | 6 | 6 | (objmgr_a2c) | — | `PostMultiMessages` ×4, `PostSyncMessages` ×2 |
| TaskManager (`taskmgr.cpp`) | 25 | 25 | (objmgr_a2c) | 14 | task list, level, barrier, end-notify, merge |
| **Total** | **6,148** | **~1,420** | **~299k lines** (81% of `port/src/native`) | | |

- **What they depend on:**
  - 1,402 direct calls to 455 distinct `.text` targets. 344 of those targets are still guest code, and 194 of those executed in these runs.
  - 2,141 calls through 586 `.plt` stubs. That covers imports, plus exported functions, which this shared object calls through the PLT.
  - 1,524 indirect calls through guest vtables or function pointers.
  - 3,110 guest data addresses: 1,568 into `.got`, 1,477 into `.rodata` and 58 into `.data` / `.bss` / `.data.rel.ro`.
  - The containers agent notes that a2c doesn't handle double precision or jump tables yet.
- **Not transcriptions:** `acsv.cpp` (ACSV tables) is hand-written, although the task list named it. The ~7,600 master-data natives (`parameter_*.inc`, `libcxx_hash_table.inc`) are generated from reverse-engineered layouts by hand-written generic C++, and so is `containers_tables.inc`. They are readable and need no rewrite, only de-guesting (section 4).
- **Rewrite order:**
  1. the transcriptions that run every frame: ObjectManager, TaskManager and SMD (44), `render (a2c)` (48), the executed container bodies (258 called), the executed model bodies (about 110);
  2. math, which is small and pure, so the existing differential tests can hold it bit-exact;
  3. the 4,728 same-code model instances. These are rewritten once, as C++ templates over the ~312 controller shapes, instead of per instance. The container instances are done the same way, as templates over the element type.

  Readable versions can reuse the current transcriptions as the differential-test oracle.

## 3. Never-executed code

81,200 functions (15.3 MB) never ran in the three flows and are not native; 7,687 of them are lone-`RET` stubs. `remaining.py` sorts them into areas by family name, first match wins:

| Area | Fns | Bytes | Largest families | Recommendation |
|---|---|---|---|---|
| Engine (other `Aska::*`) | 12,307 | 4.4M | `ParticleEmitter<>` 1.6M (template instances), `Yayoi` 789K, `ParticleObject<>` 473K, `FilmCurveFilter` 123K, `Collision` 121K | Trap. Port on demand: particle templates as they appear in executed effects, `FilmCurveFilter` if a scene enables it. `Yayoi` is the online RPC/ORM layer, so trap it. |
| libc++ / libc++abi | 23,264 | 2.5M | `std::__ndk1` 2.4M of instances, `cxa_*` 147K (demangler, exceptions) | Trap. They disappear with their callers. Exception unwinding isn't used on offline paths. |
| Third-party C | 2,128 | 1.4M | `sqlite3_*` 836K, `ZSTD_*` 182K, `jpeg_*` / `jinit_*` 98K, `HUF_*` 31K, `bt*` (Bullet) 21K+ | Already dead: the host libraries replace their entry points (sqlite, zstd, jpeg, vorbis, zlib). Delete them, nothing to port. Bullet (`bt*`) is different: its world is built at boot (21 constructor and setup functions ran) but never stepped in these flows. Keep its setup, or drop it if nothing reads the world. |
| UI screens / menus (other) | 7,729 | 1.3M | `CUIUtility` 144K, `CCharacterObject` 108K, `CDialogManager` 93K, `CUIManager` 75K, `CMissionMenu` 73K, `EventScenario` 63K | Trap, and port when a reachable screen needs them. Methods of classes that are already partly executed (the screens above) are the most likely to be reached next. |
| Battle | 3,329 | 1.0M | `CBattleUtility` 106K, `CBattle` 101K, `MissionUtility` 70K, `CBattleManager` 51K, `CResult` 51K, `CPauseMenu` 37K | Trap. Battle can't be reached offline: three battle master tables (AI, Signal, AttackAction) are missing from the offline DB, and missions play their stories only. Making battle playable is a separate project (server responses plus the battle data). |
| Party / items / growth menus | 4,366 | 895K | `CCustomGear`, `CLimitOverCharacter`, `CItemStrengthening*`, `CPartyComposition*` | Trap. They exist in the offline build's menus but need server-side state changes (FakeApi). Port when the menu is enabled. |
| Master data / parameters | 5,444 | 724K | `CParameterUtility` 227K, `IInfoBaseMap<>` 76K, `CSimpleSqliteConnector<>` 67K, `InfoBaseArray<>` 57K | Generate. These are template instances of the patterns already ported (loader, cache, lookups), so extend the generators and cover the rest mechanically. |
| Online services / network | 3,167 | 685K | `CApiNotify` 182K, `NetworkApiCaller` 114K, `CGameResourceDownloader` 83K, `CInfoManager` 22K, `CLoginBonus` 21K | Replace with an explicit offline server. `FakeApiCaller` (188 fns, 16K) didn't run in any flow, because the scenario library and browsing make no API calls. Port it together with the `C*Info` parsers when a flow needs it. `NetworkApiCaller` is a stub that fails loudly. |
| Other game code | 2,948 | 649K | `CPresentbox` 30K, `CGuideInformation` 19K, `LocalSetControllerU24_*`, `CTimeUtility` 18K | Trap. |
| Gacha / shop / payment | 3,118 | 618K | `CGacha` 119K, `CShop` 55K, `ItemShopUtility` 45K, `CCoinShop` 28K | Trap (online purchases). `CPaymentManager`'s executed poll becomes a stub. |
| Animation templates (`TAaf*`, Aaf) | 8,810 | 354K | `TAafNormalController<>` 79K, `TAafFrameSortController<>` 65K, `TAafController<>` 49K | Mostly covered: the ~4.7k natives are shape-matched, and the rest are further instances. Handle them with the templated rewrite (section 2). |
| Deep space / events / campaigns | 650 | 301K | `CDeepSpace` 72K, `CUniverse*`, `CTowerMissionMenu`, `CEventMissionMenu` | Trap (online events). |
| Multiplayer / social | 1,492 | 285K | `CMultiPlay3` 75K, `CFriendMenu` 72K, `CMultiplayManager`, `CFollow*` | Trap. Offline play has no multiplayer. |
| Framework (other) | 1,548 | 186K | `Framework::Cocos` 42K (unused node types and actions), `CMessageManager`, `CSoundManager` | Trap. Port Cocos node types when a screen uses them. |
| Debug | 900 | 165K | `CDebugWindows` 100K, `CDebugWindowsScript`, `CDebugPrimitive*`, `CTest_*` | Stub as no-ops (12 small debug functions did run at boot: registration) and never port. |

**Trap policy:**
- In the `--no-jit` build, every remaining guest entry becomes a fatal "unported guest function <name>". Lone `RET`s become no-ops. Build it from `functions.tsv` plus the name table.
- The JIT build keeps running them. A `SOA_GUEST_REPORT` mode (coverage limited to non-native entries, already available) lists which unported functions a new flow reaches.
- **What offline play needs:**
  - boot, title, home (2D and 3D), the scenario library for every episode, the character encyclopedia and its popups, and the settings menus. All of this ran in these flows.
  - the FakeApi-driven flows the offline build exposes (mission select, story clear, login-bonus / present box if reachable). These did not run here.
- Battle, gacha, shops, multiplayer, events and friends aren't needed. Neither are the online downloader and the WebView pages. Note that copyright, credits and terms render empty in the port, because the HLE has no WebView.

## 4. Leaving the JIT: what blocks it

### 4.1 Execution: guest code still on every path

- Every guest thread starts in guest code: `AskaMainThread`, `RenderThread`, the SMD workers, the ObjectManager worker, sound, notifier and peripheral threads, `AHSLCacheManagerV2`, `DecompressThread`. Their `Handler`s and the main loop (`DroidLoop`, `CApplication::CMainTask::Run`, `CFiberKernel::Progress`) are in the main-loop package.
- Natives still call guest code:
  - hand-written natives name 311 guest functions that are not native, and 223 of them ran;
  - they have about 970 call sites of `guest_call` / `ncall` into guest code, the most in `event_runtime`, `parameter_loader`, `libcxx_string`, `render_device`, `home_view` and the audio files;
  - a2c bodies call 344 still-guest `.text` targets plus 586 `.plt` stubs (section 2).
- The 267 tail-branch stubs under 8 bytes are reachable only through their callers (section 1d).

### 4.2 Guest-layout dependencies

Guest and native code share these objects, so their layout is frozen until the last guest user is gone:

- **libc++ containers and strings.**
  - 921 libc++ natives implement the guest's own `std::__ndk1` layouts: strings, trees, hash tables, `function`, `shared_ptr` refcounts.
  - `guest_std.h` helpers (`guest::String`, `StringList`) are used in 38 native files.
  - Game objects embed these containers, so a native class can't switch to host `std::` types while any guest method, or any a2c body, touches the object.
- **Aska containers.** `TBinaryTree` / `THash` / `TCategorizeHash` / `TPool*` / `TDynamicArray` / `THashMap` are now native (containers merge) but keep guest node and pool layouts, for the same reason.
- **The Aska heap.**
  - `Aska::MemoryManager` is native (`aska_memory.cpp`) but manages guest-layout arenas: block headers, free lists, `TFixedLengthAllocator` pools, the STL allocator.
  - Everything guest code allocates, and everything natives allocate for guest code, lives there. 35 native files call the guest allocators (`stl_alloc`, `new_array_nothrow`, guest `operator new`).
  - This heap can move to host `malloc` only when no guest code frees native-allocated memory, or the reverse.
- **Game object layouts.** Natives read and write game objects by offset: `at<T>(obj, 0x…)` throughout `render_*`, `objmgr`, `screen_*`, `event_runtime`, `parameter_*`. De-guesting means turning each such layout into a C++ struct, subsystem by subsystem, once its guest methods are all native.
- **Globals and singletons.** Natives name guest data symbols:
  - 181 weak `TSingleton<…>::m_pInstance` objects;
  - 44 `.bss` globals (`g_pRenderDev`, `Global::m_p*`, `GlobalShaderConstant::*`, …);
  - 8 `.data` and 2 `.rodata` objects.

  All of them live in the mapped ELF image.

### 4.3 Data still read from the guest image

- **`.rodata` (2.6 MB).**
  - Hand-written natives read about 42 tables by address: shader-constant index tables, easing curves, the event-script command table and so on (`render_context`, `render_device` (17), `event_runtime` (10), `input_touch`, `parameter_ui`, `ui_*`).
  - a2c bodies form 1,477 `.rodata` addresses.
  - Strings: format strings, file names and SQL are read from the image by natives that call guest code with them.
  - Each table needs extracting into C++ (a generator from the ELF, as `gen_*_a2c.py` already locates them) with a test that compares against the image.
- **Vtables (`.data.rel.ro`, 2.0 MB).**
  - 6,075 exported vtables.
  - Natives name 473 of them. The master-data element constructors and the container tables install guest vtables into objects that guest code later calls virtually. `EventScenario`, ACSV and CHash32 objects use them too.
  - Natives dispatch virtual calls through guest vtables: about 500 source lines in hand-written natives touch vtables (`at<u64>(at<u64>(obj,0),slot)`), plus the 1,524 a2c indirect-call sites.
  - A class can move to real C++ virtuals only when every caller of those slots is native.
- **RTTI.**
  - `__dynamic_cast` is native (`libcxx_rtti.cpp`) but walks the guest's `__class_type_info` data.
  - Guest code calls it from 92 sites in 39 functions: item and party menus, battle UI, `CArena::ReleaseOldEffect`, `std::function::target` / `swap`.
  - `std::function::target_type` compares guest `type_info` pointers.
  - Once the callers are native, these become `dynamic_cast` on C++ types, or explicit type tags.
- **`.got` (28k entries), relocations, static constructors.**
  - a2c bodies form 1,568 GOT addresses, so they rely on the loader's relocation pass.
  - 151 `.init_array` constructors (the 150 "before first export" functions, 174K) initialise globals at load.
- **`.data` / `.bss` state** (0.15 MB + 1.6 MB): engine globals, singletons, pools. It moves with the subsystems that own it.

### 4.4 HLE layers to turn into direct host code

- **Scope.** `libSOA.so` imports 416 symbols from 8 libraries. Guest code called 164 of them in the first set of runs, plus JNI functions and OpenSLES interface methods.

  | Library | Imported | Used |
  |---|---|---|
  | libc | 202 | 59 |
  | pthreads / semaphores | 38 | 24 |
  | libm | 23 | 10 |
  | libdl | 5 | 4 |
  | liblog | 1 | 0 |
  | GLESv2 | 86 | 25 from guest code |
  | EGL | 17 | 16 |
  | OpenSLES | 8 | 1 import plus the interface vtables |
  | libandroid | 34 | 24 |

  Only the libandroid imports are genuinely Android-specific: `AAsset*`, `ALooper*`, `ANativeWindow*`, `AConfiguration*`, input.
- **JNI.** An emulated JVM (`port/src/jni`, about 1,500 lines) serves about 100 Java methods: `AskaActivity` / `SOAActivity`, the Android framework bits, Play Core. The guest reaches it through the JNIEnv table (`GetMethodID`, `Call*MethodV`, `RegisterNatives`, …).
- **Size.** The HLE is about 4,900 lines: `hle/` 2.8k (libc, stdio, threads, libm, EGL/GLES, OpenSLES), `android/` 0.9k (NDK, prefs, zip), `jni/` 1.5k.
- **Once no guest code calls them:**
  - libc and libm become plain host calls;
  - pthreads become `std::thread` / host pthreads (the Aska thread wrappers are small);
  - GL is already called directly by the native render device (`GLH()`);
  - OpenSLES becomes SDL audio;
  - `AAsset` / `ALooper` / `ANativeWindow` become the port's VFS and SDL window;
  - the JNI Java methods become ordinary C++ functions in a platform layer, called directly.
- **Cost.** Busy time in HLE from guest code is only 6.4%. Removing the HLE is a code-structure goal, not a performance one.

## 5. Phase 5 roadmap (ordered)

1. **Measurement and guard rails.** Rerun `remaining.py` on the three flows after every wave.
   - Add a `--guest-report` mode: coverage of non-native entries only, printed at exit, so each wave shows exactly which unported functions a flow still reaches.
   - Extend the scripted flows to the FakeApi-driven screens (mission select → story clear, present box, login bonus). No flow here exercised the offline server.
2. **Offline stubs for platform, store and online polling** (0.9% of busy time, 238 functions).
   - Replace `CGameAssetPackManager::Progress_Download` (polled every frame), `AssetPackLocation_*`, `CPaymentManager`, the download bars, `CWebView` and `NetworkApiCaller` with explicit native offline implementations.
   - Cheap, and it removes whole families.
3. **Main loop and threads** (3.6%, 327 functions).
   - Port the thread `Handler`s, `DroidLoop` / `CApplication` / `CFiberKernel`, VSync / GPUSync / WaitVSync, `Sequencer2`, `NotifierThread`, `PeripheralManager`, `PerformanceCounter` and `Aska::Thread`.
   - After this step every thread starts in native code, which is the precondition for `--no-jit`.
4. **Per-frame engine remainder.** Render remainder (2.6%, 523), sound remainder (1.7%, 252), resources (1.0%, 545), particles and dynamics (0.5%, 248), scene objects and animation (0.5%, 311), textures (115).
   - At the same time, rewrite the per-frame a2c transcriptions (ObjectManager / TaskManager / SMD 44, render 48, the executed container and model bodies) as readable C++, with the transcriptions as the test oracle.
5. **UI.** The Cocos framework remainder (2.2%, 485) and the screens actually reached (762, 406K: settings, missions / scenario library, home, character screens, other menu), plus the event-scenario remainder (144). Screen-by-screen, as in wave 1.
6. **Generators for the long tail.**
   - The master-data template instances left (1,625), libc++ instances (742), and the tiny getters.
   - The host-equivalent table for the 1,041 functions under 8 bytes: 774 no-ops and 267 tail branches.
7. **Boot and init.**
   - The 150 static constructors and 2,737 boot-first functions: resource managers, `C*Info` parsers, LocalKVS, `CStaticTransaction`.
   - Rewrite them data-first: parse the canned FakeApi responses and the master DB directly into C++ objects.
8. **`--no-jit` build.** Any guest entry is fatal, except the lone-`RET` no-ops. The dead areas of section 3 trap with their names, and debug gets no-op stubs.
   - Guest `.rodata` / `.data.rel.ro` / `.data` / `.bss` stay mapped as data. Only execution leaves the JIT.
   - Target: the smoke test and the two longer flows pass with zero guest instructions executed.
9. **De-guesting data, subsystem by subsystem** (in the order the subsystems became fully native):
   1. rewrite the remaining transcriptions (models `TAaf*` as templates over the ~312 shapes; containers as templates over the element type; math);
   2. turn offset-based object access into C++ structs;
   3. move libc++-layout and Aska containers to host types;
   4. move guest vtables to C++ virtuals and RTTI walks to `dynamic_cast` / type tags;
   5. extract `.rodata` tables into C++ with image-comparison tests;
   6. turn singletons and `.bss` globals into C++ statics;
   7. last, move the Aska heap to host allocation.
10. **Drop the emulator.** Remove the HLE layers (libc, pthreads, EGL/GLES, OpenSLES, libandroid, JNI) in favour of direct host calls and the SDL platform layer. Then remove the ELF loader, relocations and dynarmic. What remains reads only the original assets.

Steps 2-7 are roughly 50 agent-waves of wave-1-style work (about 10 waves of 5 agents), plus about 15-20 agent-waves for rewriting the transcriptions. Steps 8-10 depend on how much layout sharing is left once execution is native.

## Side findings from these runs

- **`RenderDeviceData::CompileShaderProgramCache` costs 13.6% of busy time.** It is native and called once per frame (62,408 calls in about 20 minutes), making it the largest single cost in the profile. It is probably a per-frame program-cache check that calls host GL, and worth a look.
- **The Cocos UI and the asset-pack / payment polling are the largest remaining guest hot spots,** but no guest function exceeds 0.45% of busy time.
- **WebViews render empty.** The copyright, credits and terms pages open but show nothing.
- **Flaky tests fixed on this branch:**
  - `render-context/synthetic`: the uploaded `GlobalShaderConstant::m_vHDRTransform` is rewritten by the render thread. It now passes 7 of 7 full self-test runs.
  - `render-a2c/live`: the `PostProcessCombinerTBR +0x1ed7` bit 2 is toggled by the main thread every frame. This failed 1 run in 5 before the fix.
