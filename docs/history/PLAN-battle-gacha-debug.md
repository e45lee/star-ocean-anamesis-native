> **History.** This is the 2026-09-28 battle/gacha/debug plan of the 3.8.0-based port. The port now runs the 3.7.0 client (tag `pre-rebase-370` is the old port); the current plan is [`port/PLAN.md`](../../port/PLAN.md) and the remaining work is [`port/REMAINING.md`](../../port/REMAINING.md).

# Plan: porting battle, gacha and the debug system

Started 2026-09-28 18:45, autonomous run until 24:00. This follows the main plan (`PLAN.md`); see `REMAINING.md` for how these families fit into the whole.

## Why these are different

Everything ported so far was chosen because it **runs** in offline play, and each port was verified two ways:
- differential self-tests;
- the screenshot smoke test and the 10-minute scripted session.

Battle, gacha and the debug windows **never ran** in any profiled session:
- **Battle:** the Mission menu only leads to the scenario library.
- **Gacha:** needs server responses.
- **Debug windows:** not enabled in the release build.

`FakeApiCaller`, the game's built-in offline server, never ran in any flow either.

So step one is **reachability**. We need a scripted way into a battle, a gacha draw and the debug windows in the offline port, because without one we can only test with synthetic inputs. Possible routes, to be investigated:
- **The game's own offline server.** `FakeApiCaller` may already answer battle-start, battle-end and gacha-draw APIs.
- **The debug menu.** `Framework::CDebugMenu` / `CDebugWindows` / `CDebugWindowsScript` often include "start battle X" or "jump to scene" tools, and may be switched on by a flag.
- **Direct phase switches.** `CPhase::Switch` to `CPhase_Battle` / gacha phases, with the parameter records they expect. `CPhase::Switch` is native now (`screen_phase.cpp`).

## Scope (exported functions; there are local helpers besides)

| Area | Families | Functions | Bytes |
|---|---|---|---|
| Battle logic | `CBattle`, `CBattleManager`, `CBattleUtility`, `CBattleLogModel`, `CRushComboManager`, `CBattleRushCombo`, `CBaseDamageObject`, `BattleErrorToExit` | ~400 | ~310K |
| Factors (buffs and debuffs) | `CFactorManager`, `CFactorSeed*` (many one-function seed classes), `CFactorSeedFactory`, `MasterFactorModel`, `CFactorInfoDialog` | ~150 | ~110K |
| Battle presentation | `CBattleUIManager`, `CBattleAnime`, `CBattleTransScene`, `CNowLoadingBattle`, `CArena*` (camera, effects), `CPhase_Battle`, `CPhase_BattleResumeCheck` | ~330 | ~110K |
| Gacha | `CGacha`, `CGachaManager`, `CGachaRatio`, `CGachaBoxDetail`, `CGachaConfirm`, `CGachaShortage`, `CBoxGacha*` | ~260 | ~165K |
| Debug | `Framework::CDebugWindows` (594), `CDebugWindowsScript`, `CDebugPrimitive` / `Manager`, `CDebugMenu`, `CDebugLogConsole`, `CDebugWindows_LogConsole` | ~760 | ~150K |

That's about 1,900 exported functions and 850 KB of code. Battle also drives parts of `CCharacterObject` (256 functions), skills and AI, which will show up once a battle runs.

## Reference data: the 3.7.0 online download

The user provided `work/download-3.7.0/`: the full downloadable data of 3.7.0, the last online version. It has 8,515 files (1.7 GB): the asset tree (battle BGM, motions, effects, characters, weapons, maps, scripts, …) and the master DB. The decrypted DB is in `data/basmaster-3.7.0.sqlite3`; its schema matches offline 3.8.0, with about 27k more text rows.
- It's the source for anything battle and gacha need that the offline APK lacks.
- Serving it to the game (like the game's own downloader would) is an opt-in port option.

## Step zero: the offline server (`FakeApiCaller`) first

Per the user's direction, the port starts with **`FakeApiCaller`**, the game's built-in offline server. It's the natural entry point to battle and gacha:
- `FakeApiCaller` implements the `IApiCaller` interface: 106 exported methods, plus per-call lambdas that are local functions.
- Each call loads a canned MessagePack response (`FakeApi/<name>.msgp`) through `CGameResourceManager::AddDirectFile` / `AddLocalFile` and post-processes it.
- The canned responses include `mission_start` and `mission_end` (entering and leaving a battle), `gacha_pc`, `gacha_ticket` and `gacha_once_item` (gacha draws), the player, party, equipment, item, present and achievement APIs, and a few `Debug_*` entry points (`Debug_OpenMission`, `Debug_Gear`, `Debug_GetFol`, …).
- Responses are applied to the player state by **`CApiNotify`**: 224 functions, 188 KB, the largest game-logic family left.
- The request/response plumbing is shared with `NetworkApiCaller` (217 functions) and `CApiCallerWait`.

**Wave 1** ports and documents this layer and uses it to reach battle and gacha:

| Agent | Work |
|---|---|
| `fakeapi` | Port all of `FakeApiCaller`: every API method, its post-processing lambda, `AddLocalFile`, `BeginBridge`, `Initialize`, `GetApiNotify`. Document the offline protocol in `docs/notes.md`: API → canned file → post-processing → which `CApiNotify` handler. |
| `apinotify` | `CApiNotify`, the response handlers that apply results to the player state (items, characters, party, missions, gacha results, presents, …), plus the shared `CApiCallerWait` / request plumbing the offline path uses. |
| `reach` | Drive the running game through the offline server into a battle (Mission → `mission_start`), a gacha draw (`gacha_pc` / `gacha_ticket`) and the debug windows. Deliverables: `scripts/battle_session.sh`, `gacha_session.sh` and `debug_session.sh`, plus coverage and profiles, so the later waves know exactly what runs. If a route needs a flag or state change the game doesn't provide offline, add it as a clearly marked, switchable port option. |

**Wave 2** (started early, at 20:00, for the parts that don't need a live battle; battle-core follows once `reach` has a route): the battle, factor, gacha and debug agents below, porting what the wave-1 coverage shows, with live verification. Their worktrees (`battle-calc`, `factors`, `battle-core`, `gacha`, `debug`) are already built.

## Method

The loop is the same as for the main port: decompile, write readable C++, run the differential `NATIVE_TEST`s, run the smoke test, merge. Agent worktrees come from `scripts/agent-worktree.sh`, and the integrator merges and gates everything on `linux-port`.

What's specific to this plan:
1. **Reachability first.** One agent finds and scripts routes into battle, gacha and the debug windows, and adds them as scripted sessions: `scripts/battle_session.sh`, `gacha_session.sh`, `debug_session.sh`. It also collects `SOA_COVERAGE` / `SOA_PROFILE` data from them, so porting can follow what actually runs.
2. **Pure logic in parallel, tested synthetically.** Porting of logic that can be tested without reaching the screen starts at once, driven by synthetic inputs and real master data:
   - damage and stat formulas (`CBattleUtility`);
   - factor seeds (`CFactorSeed*`);
   - gacha ratio tables (`CGachaRatio`);
   - the debug-window widgets.
3. **Live verification once reachable.** Screens and state machines get in-frame differential tests (`NATIVE_TEST_HOOK`) and screenshot comparisons against runs with the natives off (`SOA_NO_*` switches).
4. **Readable C++ is the default.** `tools/a2c.py` transcription is allowed only for large FP-heavy bodies, and must be listed as such.
5. **Test hygiene** (learned the hard way today):
   - Every `StubSession` sets `only`.
   - Tests must not depend on test order.
   - Every soa run uses `timeout -k 10`.

## Waves (after step zero)

- **Wave 2:**
  - `battle-calc`: `CBattleUtility`, `CBaseDamageObject`, the damage and stat formulas.
  - `factors`: `CFactorManager`, `CFactorSeed*`, `CFactorSeedFactory`, `MasterFactorModel`.
  - `battle-core`: `CBattleManager`, the `CBattle` state machine, `CBattleLogModel`, rush combo.
  - `gacha`: `CGacha*`, `CBoxGacha*`, the dialogs.
  - `debug`: `Framework::CDebug*`.
- **Wave 3,** if there's time:
  - battle presentation: `CBattleUIManager`, `CBattleAnime`, `CArena*`, transitions;
  - the battle-side `CCharacterObject`, skills and AI.
- **Wrap-up (23:40 → 24:00):** the final full gate and numbers.

## Progress

| Wave | Family | Functions | Tests | Live-verified | Status |
|---|---|---|---|---|---|
| 1 | `FakeApiCaller`, all 95 request methods and lambdas, native (`fakeapi.cpp`). Finding: it's dead code in the shipped build and its canned responses were never shipped. New opt-in `SOA_FAKE_SERVER=DIR` makes it live, with responses generated by `tools/fakeapi_responses.py` (`port/fakeapi/responses`) | 276 | 5 | data-level (gacha_pc adds 10 characters; mission start/end apply) | merged |
| 1 | `CApiNotify`: 158 response handlers (mission chain, gacha draws, items, characters, session) + post-apply helpers, native (`api_notify.cpp`); `DeserializeToInfo` and 35 long handlers still guest | 173 | 12 | no (nothing issues requests yet) | merged |
| 1 | Reachability: `--download-dir` (serves the 3.7.0 assets), control commands `phase:` / `mission:` / `call:` / `debugwin:`, `battle_session.sh` / `gacha_session.sh` / `debug_session.sh`, coverage in `work/profile/{battle,gacha,debug}`. Battle reaches the loading screen, then stops: the party is empty and there's no stage parameter. The gacha screen opens but has no gacha list | tooling | — | — | merged |
| 2 | `CApiNotify` follow-up: `DeserializeToInfo` (a2c) + 15 handlers + present / storage / auto-equip helpers → 197/224 native. Live check (`apinotify_live.sh`, `SOA_FAKE_SERVER_DRIVE`): presents, 5 gacha variants and the mission start/end/restart chain produce identical player state natives on vs off. Also fixed the root cause of `guest_stub: unknown stub` | 25 | 7 | yes (data level, 14 dumps identical) | merged |
| 2 | Battle factors: seed factory (all 13,455 `master_factor_seed` records compared), 88 `SetParam`, 71/74 `CheckSeed`, 8 `OnProgress`, type ids, destructors, `CFactorManager` list management, `MasterFactorModel::GetParam` (`battle_factor*.cpp`) | 406 | 12 | no (no battle with a party yet) | merged |
| 2 | Battle formulas: `ICalculateParameter` (damage, critical, guard, guts, battle RNG), all of `CCharacterData` (HP, AP, stats, gauges, abnormal states), `CBaseDamageObject`, `CBattleUtility` helpers, resource names, BP (`battle_calc.cpp` etc.) | 138 | 26 | no (no battle with a party yet) | merged |
| 2 | **Battle and gacha play through** (opt-in `SOA_FAKE_SERVER` + `SOA_DOWNLOAD_DIR`). Mission mf01_001 plays both stages automatically to the result screens: the party comes from `BattleParameter.PlayerCharacter`, and the stage infos now carry the fields the game needs. The gacha list is served (`gacha_in_data.msgp`) and a 10-draw runs through the summon presentation to the results. Also fixes an a2c stack-argument bug that crashed about half the battle runs | tooling | — | yes (screens) | merged |
| 2 | Debug windows: the `CDebugWindows` core (manager, input frame, message queue, window creation and frames, tabs, controls), log console, debug primitives (`debugwin.cpp`, `debug_logconsole.cpp`, `debug_primitive.cpp`). Finding: the release build has no game-specific debug tools (no battle, scene-jump or cheat menu) | 179 | 10 | yes (screens identical natives on vs off) | merged |
| 2 | Gacha (`gacha.cpp`, `gacha_ui.cpp`): `CGachaManager` (the draw sequence, 25), `CGachaRatio` (19), `CGacha` (11 executed members), `CGachaBoxDetail` (17), the dialogs (23), `CPhase_Gacha` (5); `docs/notes.md` "Gacha". Still guest: `CGachaManager::Progress_Main` / `CheckGachaResult` / `LoadResource`, `CGacha::Progress` / `Setup` / series builders | 100 | 5 | yes: `gacha_session.sh` draw to the result list, natives on vs off | branch `port/gacha` |
| 2 | Battle presentation: the loading screen (`CNowLoadingBase` / `CNowLoadingBattle`), `CArenaCamera`, `CBattleUIManager` (34), `CPauseMenu`, `CBattleTransScene` (`battle_nowloading.cpp`, `battle_camera.cpp`, `battle_ui_manager.cpp`) | 83 | 3 | yes (in-frame on the live loading screen; full battle screenshots natives on vs off) | merged |
| 2 | a2c runtimes: every transcribed-code call path passes stack arguments correctly (shared `a2c_guest_call`); fixes a class of wrong-argument bugs | 0 | 1 | yes (3 battle runs) | merged |
| 2 | Battle control: the `CBattleManager` state machine (83: progress, start, results, counters, rush/trans requests, auto), `CBattleLogModel`, `COrderGaugeManager`, `CAITargetManager`, `CRushComboManager` queries, `CBattle` HUD (`battle_core.cpp` etc.) | 155 | 10 | yes (`SOA_BATTLE_CORE_CHECK`: 1,199 live guest-replay checks, 0 mismatches) | merged |
| 2 | Battle actors: first `CCharacterObject` / `CMovableObject` / `BehaviorQueueContainer` helpers (`battle_actor.cpp`) | 7 | 5 | no | merged |

## End of run (2026-09-28 23:15)

- **Native functions:** 16,799 guest functions are native, up from 15,259 at the start of the evening, so about 1,540 new ones in battle, gacha, debug and the offline server. There are 421 differential self-tests, and all pass.
- **Final gate on `linux-port`:** the full self-test, the smoke test, `battle_session.sh` and `gacha_session.sh` all pass.
- **Battle:** plays through with the opt-in `SOA_FAKE_SERVER=port/fakeapi/responses SOA_DOWNLOAD_DIR=work/download-3.7.0`. Mission mf01_001 goes through the loading screen, two stages of automatic combat and the three result pages, back to home. The live guest-replay check of the battle state machine (`SOA_BATTLE_CORE_CHECK=1`) ran 899 checks with 0 mismatches.
- **Gacha:** the gacha list and banners, the draw confirmation, the summon animation and reveal, and the result list, back to home.
- **Offline server:** `FakeApiCaller` turned out to be dead code in the shipped game, and its canned responses were never shipped. The port brings it to life as an opt-in option, with responses generated from the save and master data. These responses are our own invention and are documented as such.
- **Debug windows:** the core is native. The release build contains no game-specific debug tools.

**Still guest code, and next steps:**
- **Battle:** `CStageManager::Progress`, `CPartyManager::Progress`, `CNormalCamera`, and most of `CCharacterObject` (skills, actions, `UpdateSeedCondition`). Also the `CBattleUIManager` / `CBattleAnime` per-frame bodies, `AIAction` / `BehaviorQueue_*`, and particles.
- **Factors:** the `CFactorManager` update and condition checks.
- **Gacha:** `CGachaManager::Progress_Main`, `CGacha::Progress` / `Setup` / `ProcProduction`.
- **Debug:** `CWindow::UpdateWindow`, the procedures and most controls. Window text doesn't draw.
- **Offline server:** 27 long `CApiNotify` handlers.
- **Generated data needs work:** the party shows as "RENTAL" (it should use owned characters), `mission_end` yields 0 EXP, and the wallet is never debited.
