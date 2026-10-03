# Notes on the removed natives' switches (moved from docs/notes.md)

> **History.** Moved here from [`docs/notes.md`](../notes.md) on 2026-10-03 (branch `port/env-flags`, the environment cleanup): the parts of the notes that describe the offline build's native replacements and the verification runs made with their switches (`SOA_NO_APINOTIFY_NATIVE`, `SOA_NO_BATTLE_CALC_NATIVE`, `SOA_NO_BATTLE_CORE_NATIVE`, `SOA_NO_BATTLE_UI_NATIVE`, `SOA_NO_DEBUGWIN_NATIVE`, `SOA_NATIVE_AUDIO`, `SOA_NATIVE_INPUT`, `SOA_PARAM_DUMP`, `SOA_BATTLE_CORE_CHECK`, `SOA_BATTLE_DAMAGE_LOG`). Those natives and their switches no longer exist (the rebase's revision 2, [`PLAN-rebase-370.md`](PLAN-rebase-370.md)); the text is kept as written, as the record of what was verified and how. Other environment variables named here may be gone too: [`docs/environment.md`](../environment.md) lists the current ones (e.g. `SOA_FAKE_SERVER` is `soa --fake-server` now, `SOA_RESTORE_NEW_PLAYER` `--new-player`). The rest of the notes stays current in `docs/notes.md`.

## From "Battle flow"

**Live check** (`SOA_BATTLE_CORE_CHECK=1`): each frame one of the native `Progress_BattleMain`, `Progress_LocalBattleNormal` and `CAITargetManager::Progress` (in turn) runs with its outgoing calls recorded (with the object's bytes after each), then the guest original replays against those recordings (the callees' side effects happen once) and must make the same calls with the same arguments and leave the same bytes; the controlled character's target handle (+0x618) is put back for the replay too. Frames calling something outside `battle_core_callees.inc` (the boss camera's and lambdas' virtual calls) are skipped. On `mf01_001` with the fake server, a whole battle (both stages, stage ends, result state) matched: 1,498 checked frames of `Progress_BattleMain`, 0 mismatches, 2 skipped. Before the linux-port merge of the a2c stack-argument fix, most runs died at the stage 1 -> 2 switch with `unimplemented instruction` at `Aska::WavePlayer::~WavePlayer()+0xb8`, with and without the battle natives.

## From "Master-data loader (the cache miss path)"

- **Whole-run check**: `SOA_PARAM_DUMP` dumps of every master cache after the smoke session are identical with the loader natives on and off, except for run-to-run noise that also differs between two runs of the same build (the 10-entry text cache and the random home-screen voice) and the uninitialised members.

## From "Sound engine"

- **Verification**: runs with `SOA_AUDIO_DUMP` compare title (BGM and voice) and story-scene output with `SOA_NATIVE_AUDIO=0` and `=1`. The dumps are identical over their common length; the lengths differ only by how long each run lasted.

## From "Input (verification)"

  - Live A/B sessions (character list scrolling, character detail, the home 3D interactive mode with wheel pinch and drags) give the same screens with `SOA_NATIVE_INPUT=0` and `=1`. Drag inertia depends on event timing, which varies from run to run in both modes.

## From "API response handling (CApiNotify): Port status and Live check"

### Port status

Native in `port/src/native/api/api_notify.cpp` (+ `api_notify_a2c.cpp`, `api_notify_live.cpp`): 198 functions (197 of the 224 `CApiNotify` exports + `CParameterManager::Deserialize`):
- **`DeserializeToInfo`: transcribed** by `tools/a2c.py` (`tools/gen_apinotify_a2c.py` → `api_notify_a2c.cpp`), not hand-written: 7.6 KB of inlined container constructors / destructors. Its calls are guest calls (`models_gcall` / `models_icall`), so natively replaced callees still run natively.
- **172 response handlers** as readable C++:
  - the 157 table handlers: plain apply, apply + post-apply steps, and 42 with inline code (the 30 above plus `UpdateName`, `EquipWeapon`, `EquipAccessory`, `SellItem`, `ItemCompose`, `SellGear`, `UseFavorItem`, `UniverseReset`, `(Un)FavoriteDecoObject`, `SetCharacterDeco`, `BoostCharacter`; and `LimitBreakCharacterRes_Legacy`, the same as the current one);
  - the 8 acknowledge-only debug handlers;
  - the mission chain: `OnMissionStart`, `OnMissionEnd`, the four `*Res`, and `OnSphere211MissionEndRes`.
- **Post-apply helpers:** `AddItem`, `AddCharacter`, `AddLimitBreak`, `UpdateStackItem`, `UpdateBoxGacha`, `UpdateStepUpGacha`, `ApplyGetPresent`, `ApplyAutoEquipResult`, `AddPresentBox`, `AddStorage`, `DeleteStorage(bool)`, `DeleteOneTimeStorage`, `DeleteGear`.
  - Reproduced: the inlined copy constructors and destructors of `CStackItemInfo` / `CDecoObjectInfo` / `CStorageItemInfo`, `CDecoObjectInfo::operator=`, the inlined `vector::erase` / `clear` of items, storage, presents and character decos, the id-value emplaces, and the unused stack copies (InfoBase maps copied and destroyed, string temporaries).
  - Called: the out-of-line pieces (`CItemInfo(const&)` / `operator=(&&)` / `~CItemInfo`, `CPresentBoxInfo` and `CCharacterDecoObjectInfo` likewise, map copy / destroy / erase / `__assign_multi`, `__push_back_slow_path`, `__construct_node`).
- **Session bookkeeping:** `InitErrorCode`, `ResetErrorCode` (the handlers' `EndRequest`, native as `end_request`), `_SetErrorCode`, `LoggedIn`, `OnError`, `OnDisconnect`, `OnProtocolError`, `OnResultUpdateSession`, `SetBridgeSessionUUID`, `OnLoginResult`, `OnSimpleLoginResult`, and `CParameterManager::Deserialize`.

Still guest code (27):
- the constructor and destructor (C1/C2, D1/D2), `OnResultStart` (network only: HTTP request setup);
- 22 handlers with long inline code: DeepSpaceMissionStart / End / EndNow, InheritAccessory, ItemGradeUp, AttachGear / RemoveGear / GenerateGear, UpdateConfig (inlined string assignment), FollowList / Add / Remove, BlacklistAdd / Remove, Sphere211FloorClear, AcquireUniverse, SetDeity, Train / ResetMastery, `OnMaintenanceRes` / `OnPartialMaintenanceRes` / `OnAccountSuspendedRes`.

`SOA_NO_APINOTIFY_NATIVE=1` turns all of them off.

Guest quirks found:
- `OnUpdateNameRes` dereferences `CParameterPlayer::pParameter()` unchecked; with no `Player` parameter (offline, no login) it crashes (guest and native alike), so the live check doesn't request `UpdatePlayerName`.
- `AddPresentBox` / `OnSellItemRes` / `OnBoostCharacterRes`: with the `CParameterManager` singleton missing, the guest asserts and then runs into the code folded after it (`UpdateBoxGacha`'s body / `OnSellStackItemRes` / `OnEvolutionCharacterRes`). `AddPresentBox`'s case is reproduced; the others aren't (they can't happen once the manager exists).
- `OnUniverseResetRes` reads the key of the board map's first node before clearing it; with the map empty that's the end node's `+0x20`, i.e. `CParameterManager+0xa480` (reproduced).
- `SetBridgeSessionUUID` calls `raise(SIGTRAP)` for a UUID of 37+ characters; the native version raises on the host (unreachable with real UUIDs).
- Property padding: `CParameterPropertyValue`'s flag byte, hash and u32 values are followed by padding the guest never writes, so identical states differ there between runs (the dump masks it).

Tests `apinotify/*`:
- `handlers`, `mission-chain`, `session`: synthetic `CApiNotify` objects, every callee stubbed; call order, arguments and bytes compared (`session` also covers `OnProtocolError` and `OnResultUpdateSession`, with a fake `std::function` callback);
- `inline`, `mission-end`, `add-character`, `add-item`, `update-stack-item`, `gacha-progress`, `limit-break-sync`, `apply-get-present`, `sphere211-mission-end`, `storage`, `auto-equip`, `gear-uuid`: synthetic containers (maps as node chains, vectors as blocks, valid `InfoBase` objects with empty maps) spliced into the live `CParameterManager` and restored after each run;
- `login`, `pm-deserialize`: real MessagePack bodies parsed by ASON;
- `deserialize-to-info`: the transcription against the guest on the live `CParameterManager` with the generated offline-server responses (`port/fakeapi/responses/*.msgp`, run from `port/`) and small / malformed bodies, guest → native → guest; the Status and the player-state dump must match after each run, and the gacha dump must differ from the `{}` one.

### Live check

`port/scripts/apinotify_live.sh OUTDIR [ENV=VALUE...]` runs the whole offline server path: soa boots with `SOA_FAKE_SERVER=port/fakeapi/responses` (`FAKE_DIR=` overrides) and the port test hook **`SOA_FAKE_SERVER_DRIVE=FILE`** (`api_notify_live.cpp`, off by default):
- once per served `FakeApiCaller::Progress` (game thread), the lines of FILE are queued and FILE is removed; one command runs at a time, only when no request is in flight;
- `req:<Method>` queues `FakeApiCaller::<Method>`'s request exactly as the game would (the native request methods ignore their arguments; `fakeapi::request_by_name`);
- `dump:PATH` writes `player_state_dump()`: the owned and per-response vectors (characters, items, stack items, storage, present box, gacha results, …) with element bytes, the result / owned maps with keys (and values for new items / characters, mission results, character favor), and the whole `CParameterManager`, pointers normalised (`pm+off`, `L+off`, `P` for heap) and property padding masked;
- `infos:PATH` lists the registered response infos and the `data` root's children with their `CParameterManager` offsets (e.g. `AddCharacter` at `+0x4b18`, its map at `+0x4b50`);
- `log:TEXT`.

The script drives: PresentList, GetPresent, Gacha, GachaOnce, GachaTicket, BoxGacha, SaleGacha, MissionStart, MissionEnd, MissionRestart, MissionEnd, GetPlayer, then SellItem, ItemCompose, EquipWeapon / Accessory, AchievementReceive, EquipAuto, (Un)FavoriteDecoObject, SetCharacterDeco, BoostCharacter, UseFavorItem, LimitBreakCharacter_Legacy (those with no generated file get `{}`), with a dump after each step of the first part and one at the end. The storage requests and SellGear can't be driven: `FakeApiCaller` only returns a Status for them (no lambda, no handler call).

**Result (2026-09-28):** natives on vs `SOA_NO_APINOTIFY_NATIVE=1`: all 14 dumps identical. The dumps show the flows working: the box holds 5 presents, then 3 after GetPresent; each gacha adds its draws to the roster (10 → 11 → 21 → 31 → 41; the same file served twice adds the same uids again) and fills the 10 results; mission end adds the stack item, the per-character result and a character-favor entry, and writes the fol / mission time.

## From "Tutorial battle damage (the setup)"

The battle tutorial of the new-player flow (`--server inproc`, `SOA_RESTORE_NEW_PLAYER=1`, a brand-new `--data` dir: no `Game.xml`, no `server.sqlite3`), played by `port/scripts/newplayer_session.sh`. Damage was logged with `SOA_BATTLE_DAMAGE_LOG=1` (a read-only diagnostic in the native `ICalculateParameter::Damage` / `IsCritical`, `battle_calc.cpp`: both characters' six stats, the attack's id / power / type / flags, the attribute and cancel rates, the result) and `SOA_TRACE` on `CCharacterObject::OnDamage` (the value the hit applies and the HUD shows, truncated to int).

## From "Tutorial battle damage (tutorial-specific code)"

- In all runs (native, and guest with `SOA_NO_BATTLE_CALC_NATIVE=1 SOA_NO_BATTLE_CORE_NATIVE=1`), **the enemies never attack** in the scripted session, so there are no enemy damage numbers to check.

## From "Tutorial battle damage (native vs guest)"

**Native vs guest.**
- `--selftest "battle/"`: 40/40 pass.
- A live `SOA_BATTLE_CORE_CHECK=1` run of the tutorial battle: 5,400 frames, 0 mismatches.
- The guest run (battle calc and core natives off) gives the same value ranges.
- The native damage code is not the cause.

## From "Battle presentation (verification)"

Verification: `port/scripts/selftest_battle.sh` drives a `--selftest` run to the live loading screen (no server needed; the control commands run from a test hook on the guest `CPhase::Progress`) and runs `battle-ui/*` there: 571 in-frame guest-vs-native cases over the screen object and every node of its four scenes, with animations, tips, stage icons and player panels as recording stubs. Screenshots of the full `battle_session.sh` (fake server, two stages, results, back home) with `SOA_NO_BATTLE_UI_NATIVE=1` and without match except for the randomly chosen tip and live battle timing (enemy positions, which special attack is announced); the result pages and the home screen afterwards are identical.

## From "Debug windows"

**Native in the port** (`debugwin.cpp`, `debug_logconsole.cpp`; `SOA_NO_DEBUGWIN_NATIVE=1` turns them off): the `CDebugWindows` free functions, `CManager` (including window creation with the inlined `CWindow` / `CTabWindow` constructors), `CMouseCursor`, `CMessageQueue` with `CWindowBase::GetMessage` / `SendWindowMessage`, the `CWindowBase` methods that don't build sprites (control table, names, rect, z order, frame `Put`s), `CDebugLogConsole` and the `CDebugWindows_LogConsole` glue, `CDebugPrimitive::CBase` / `CLine` / `CGrid`, `CDebugPrimitiveManager`'s constructor, `Reset`, `SetTextColor` and `AddLine` / `AddSphere` / `AddLinesSphere` / `AddBox`, `CWindow::Update` / `IsPause` / `Position`, `CTabWindow::Update` / `Position`, `CControl` / `CButton::Owner`, `CColorRect::Update`, and the `CDebugWindowsScript` singleton and `IsAvailableCharacter` (words are separated by tab, LF, CR and space). `CWindow::UpdateWindow` (the frame layout), the `Procedure`s, `CControlContainer`, most controls, the script compiler and the other primitive shapes are still guest code.
