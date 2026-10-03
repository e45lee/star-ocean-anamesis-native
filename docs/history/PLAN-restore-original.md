> **History.** This is the plan for restoring the online game on the 3.8.0-based port (--restore). The port now runs the 3.7.0 client (tag `pre-rebase-370` is the old port); the current plan is [`port/PLAN.md`](../../port/PLAN.md) and the remaining work is [`port/REMAINING.md`](../../port/REMAINING.md).

# Plan: restoring the original game and battle functionality

Written 2026-09-29. The goal: the desktop port plays like the online game did in 3.7.0, the last online version. That means a real title, login and new-player flow, party building, mission select, battles with real rewards and progression, gacha with real rates and currency, shops, login bonuses, achievements and events. All of it runs locally, with no server.

It builds on the port (`PLAN.md`) and on the battle/gacha work (`PLAN-battle-gacha-debug.md`). Today a battle plays and a gacha draw completes, but only on invented data (`SOA_FAKE_SERVER`).

## What we have to work with

| Source | What it gives us |
|---|---|
| `work/libSOA-3.7.0.so` | The online client, the last version before the offline build. |
| `work/extracted/.../libSOA.so` (3.8.0) | The offline client the port runs. All natives are verified against it. |
| `work/download-3.7.0/` | The full 3.7.0 downloadable asset set (8,515 files): battle maps, effects, motions, BGM, voices, scripts. Served with `--download-dir`. |
| `data/basmaster-3.7.0.sqlite3` | The 3.7.0 master DB. Same 176 tables as 3.8.0, plus 27k more text rows. |
| The port's native layers | `FakeApiCaller` (in-process API route), `CApiNotify` (197 of 224 response handlers), the battle state machine, formulas, factors, gacha, and more, all differentially tested. |
| `work/Game-3.7.0.xml` | A real 3.7.0 online save (June 2021), readable with `python -m soa_save dump`. It's a client-side cache, since the account state lived on the server. It still has a player id (`BAS:PlayerID`), the 70 owned roles (`person_master_role_id_N` = CHash32 of the role label), all 10 planets open (`BAS:PlanetOpen_planet01..10`), the last world map and cell played, the last episode and part, `BAS:DownloadEpisodeFlag` = 7, auto-battle on, and UI and sort settings. It serves as the seed and reference for the local server's initial state and progression flags. |
| `docs/notes.md` | The protocol map (API → handler), response schemas (`SOA_FAKE_SERVER_SCHEMA`), and the battle, gacha and factor notes. |

### How 3.7.0 and 3.8.0 differ (measured)
- **Exported functions.** 64,550 in 3.7.0 and 64,704 in 3.8.0.
  - Only 47 exist only in 3.7.0: Android location and GPS, Google Play achievements, a web-view helper, a test class, and `PersonModel::FindPersonInfoFromID`.
  - 201 exist only in 3.8.0: the Play Core asset-pack code.
- **Changed bodies.** 177 functions exist in both builds with different sizes. The offline build gutted functions rather than deleting them:

| Function | 3.7.0 bytes | 3.8.0 bytes |
|---|---|---|
| `CPartyComposition::Progress` | 7,156 | 1,044 |
| `CPartyComposition::Setup` | 4,416 | 608 |
| `CTitle::Setup` | 3,068 | 1,584 |
| `CPlayerInitializeMenu::Initialize` | 3,608 | 2,180 |
| `CMissionMenu::NextPhase` | 1,464 | 640 (no battle-mission start) |
| `CTutorialManager::SetBattleTutorial_UI` | 656 | 4 (stubbed) |
| `CPhase::Switch` | 2,124 | 1,672 |
| `CPhase_Login::Progress` | 4,496 | 4,284 |
| `NetworkApiCaller::BeginBridge` | 536 | 404 |

  - Also changed: the favorability functions (`GetFavorabilityLevel` and friends), `CAdjutantSelect`, `CHome::UpdateBadge` / `Progress` / `Initialize` / `Setup`, `CScenarioLibrary`, `CMissionSelectPart`, the system-settings reset API, local notifications, and sort/filter setup.
  - About 67 functions grew in 3.8.0: offline-only replacements in settings, home and campaign queries.
- **The server is gone for good.** The client talked to `production-game.so-ana.com` over `Aska::Yayoi::GameRPC`, 1,013 exported functions. Nothing of the server's own code exists.
  - Much of its logic is data-driven by the master DB. That includes:
    - `master_mission_drop` (9,453 rows with `rate_weigh`, fixed and surprise drops);
    - `master_common_drop`, `master_campaign_drop`, `master_mission_clear_present` (4,263);
    - `master_gacha` (2,281, with S/A/B/C/D rank rates, costs, bulk bonuses), `master_box_gacha` (11,826), `master_gift_gacha`;
    - `master_player_level`, `master_role_level_max`, `master_character_limit_break`, `master_role_evolution`, the compose tables;
    - `master_login_bonus*`, `master_item_shop`, `master_exchange_shop*`, `master_achievement`;
    - the deep-space and sphere211 reward tables, `master_time_bonus`, `master_campaign`, and more.
  - What remains is formulas and flows the server computed itself (EXP granted, stamina regeneration, rank-up, rewards per evaluation). These have to be reconstructed. The client usually displays or pre-computes them (`CUIUtility` / `CParameterUtility` helpers, battle-evaluation code), which pins most of them down.

## Architecture decisions

1. **Base binary: stay on 3.8.0; bring back 3.7.0 behaviour function by function.**
   - About 16.8k natives are verified against 3.8.0. Many transcribed (a2c) bodies embed 3.8.0 addresses, so switching the base to 3.7.0 would mean re-verifying everything.
   - Instead, each of the ~177 changed functions gets a native implementation of its **3.7.0** behaviour, installed on the 3.8.0 symbol. This works when the data layouts match; that's checked per class, see step 0.
   - The whole set sits behind one opt-in switch, `--restore` / `SOA_RESTORE=1`. Without it the port stays the faithful 3.8.0 offline game.
2. **Server: an in-process local server that replaces the canned responses.**
   - A new module (`server/`) implements every API the client calls (the ~95 `IApiCaller` methods), with real game rules. It is reached through the `FakeApiCaller` route that already works.
   - It keeps its own persistent state: player, roster, items, party, mission progress, gacha history, wallet, bonuses and timestamps. The store is a SQLite file in the data directory, synchronised with the game's own save (`Game.xml`, `soa_save/`).
   - Responses are built in the exact msgpack shapes the handlers parse. `SOA_FAKE_SERVER_SCHEMA` already dumps the key schema.
3. **Network protocol: later, optional.** A `GameRPC`-compatible server, speaking the network protocol, would let the untouched `NetworkApiCaller` path run, and even an Android client pointed at it. It isn't needed for the desktop port, so it's the last phase and depends on how hard the protocol is (encryption, session).
4. **Every rule carries its source.** Each rule the local server applies is documented with where it came from:
   - **(a) master data** — the right answer;
   - **(b) client-side evidence**: code that shows or pre-computes the value;
   - **(c) outside knowledge** of the live game;
   - **(d) invented placeholder.**

   The aim is to drive (d) to zero for everything the player sees.

## Phases

### Phase 0: evidence and tooling
- **Version diff tool** (`tools/verdiff.py`):
  - Compare 3.7.0 and 3.8.0 per function by normalised instruction streams, with addresses and literals abstracted, not just by size. That catches body changes of equal size.
  - Also diff `.rodata` strings and tables, and the vtables.
  - Output: the exact list of behaviour changes, grouped by feature.
- **Dual-load oracle.** Teach the loader to map `libSOA-3.7.0.so` as a second, inert image in `--selftest`, so native "3.7.0 behaviour" code can be tested against the real 3.7.0 function on the same inputs. This is the same differential method as today, with a different reference.
- **Layout check.** For each class a restored function touches, compare the constructor and field offsets between the two builds; the object-size and offset diffs are mechanical. Flag any class whose layout changed.
- **API catalogue** (`docs/api.md`): every `IApiCaller` method with its FunctionID, request parameters (from the `NetworkApiCaller` serialisers), response schema (from `CApiNotify::DeserializeToInfo` and the schema dump), the handler's effects, and the master tables involved.

### Phase 1: client flows, restored (the 3.7.0 behaviour of the changed functions)
In priority order:
1. **Missions:** `CMissionMenu::NextPhase`, `CMissionSelectPart`, the scenario-library hooks, so battle missions can be picked and started from the real UI instead of the `mission:` / `phase:` debug commands.
2. **Party building:** `CPartyComposition` (the full 3.7.0 version: party select, edit, sort, assist), `CAdjutantSelect`, `CUserDataUtility::Load_PartyInfo`.
3. **Title and new player:** `CTitle::Setup`, `CPhase_Login::Progress`, `CPlayerInitializeMenu` (name entry, first character), `NetworkApiCaller::BeginBridge` → local server.
4. **Tutorial:** `CTutorialManager::SetBattleTutorial_UI`, `IsExistMenuVoiceMask`, `ProgressUI`, `CPhase_TutorialNext`.
5. **Home and progression UI:** `CHome` badges and popups, the favorability functions, `CCharacterPictureBook::OpenNotHaveDialog` / `CreateCollectList`, the sort and filter setup, the settings reset API.
6. **Platform features:**
   - Achievements → a local implementation, or no-op with logging.
   - Location / GPS → off: it was a side feature.
   - Local notifications → desktop notifications or no-op.
   - Web views → render the notice / terms pages from the 3.7.0 download where they exist.

**Verification:**
- differential tests against the 3.7.0 oracle;
- screenshots of each restored flow;
- scripted sessions: new player → tutorial battle → home; party edit → mission select → battle → rewards.

#### The story campaign (investigated 2026-09-29; see `docs/notes.md` "The original campaign (3.7.0)")
The campaign's screens (`CPhase_Mission`, `CMissionMenu`, `CWorldMapMenu`, the mission detail, party select and `CStageManager`) are unchanged in 3.8.0. Two client cuts and missing server data keep them out of reach.

Done in `port/campaign` (behind `--restore`):
1. **Client, logged in `docs/client-changes.md`:** the episode tap goes to phase 5 again (one instruction in the `CMissionSelectPart::CreateList` lambda), `CMissionMenu::NextPhase` hands the chosen mission to `CParameterUI` as in 3.7.0, and the end of a story scene reaches the server again (3.7.0's `EndMissionTalk` at the end of `CEventScenario::Exit`) (`port/src/native/restore/restore_campaign.cpp`). The port's fake caller answers `GetWorldMapInfoList`.
2. **Server (`server/src/api_campaign.cpp`):** `ActiveMissionList` from the `master_mission` unlock chains plus a persisted clear set; `ActiveWorldMapMissionList` and `Player.world_map_progress*` from `master_world_map_progress` / group progress (Episodes 2 and 3); clears on `MissionEnd` / `MissionTalk` / `EndMissionTalk` (the server core builds `MissionParameter` and the rewards); party 1 seeded when the player has none; `view_status` for a returning player (`SOA_CAMPAIGN_SEED`). The login data goes out as a `GetPlayer` answer after the save's roster loads. Rules and sources: `docs/server-rules.md`.
3. **Session:** `port/scripts/campaign_session.sh`: title → Episode 1 → planet select → mission map → 1-05 → party → battle → result → 1-05 CLEAR, next story mission New → its scene.

Next steps, in order:
1. **Episodes 2 and 3:** the world map opens and its first story plays; next, the end of the story movies (`m2011_010.mp4`, `m6011_010.mp4`: the port's movie player never reports their end, so the first story of each episode can't finish), then a scripted play-through of the first groups (story, free-battle cells, progress) to check the progress rule.
2. **Real mission rules** with server-core: stamina, EXP and FOL from `master_mission`, drops, first-clear presents (`master_mission_clear_present`), the battle party from `PartySet` and the roster (not the canned `BattleParameter`).
3. **Rental list** (the `レンタルキャラクター` screen is empty): NPC helpers from `master_mission_npc` / the rental tables.
4. **New-player path:** `mc00_010` onwards with the tutorials (needs the tutorial restore: `CTutorialManager` is stubbed in 3.8.0).
5. Merge the progress store into server-core's SQLite state.

### Phase 2: the local server (game rules)
In priority order:
1. **Core state:** player (level, EXP, stamina, currencies), roster, items and storage, party sets, mission progress. It's seeded from the existing save, so the all-characters save keeps working.
2. **Mission start/end with real rules:**
   - stamina cost and regeneration;
   - EXP and FOL (the in-game money) to the player and characters (`master_player_level`, per-role level curves);
   - drops by `rate_weigh` from `master_mission_drop` / `common_drop` / `campaign_drop`, with fixed and surprise drops;
   - first-clear and clear presents;
   - favorability gains;
   - mission unlocks, ranks and evaluation.
3. **Gacha:**
   - banners by date, from `master_gacha` / `gacha_pickup` / `gacha_image`;
   - rank rates and pools, bulk bonuses and guarantees;
   - currency and ticket costs;
   - box gacha from `master_box_gacha` (reset, contents);
   - step-up gacha, gift gacha, and duplicate handling (limit break).
4. **Growth:** limit break, evolution, awakening, compose (items, weapons, accessories, materials), grade-up, sale, stock.
5. **Economy and daily systems:** login bonuses (regular and premium), shops and exchange shops, presents box, achievements and rewards, time bonuses, campaigns.
6. **Other modes:** events and event missions, training, deep space, sphere211 and tower, world map. For time-limited content, a clock override (`SOA_CLOCK=`) lets past events be replayed.
7. **Multiplayer:** replaced by single-player play with NPC or rental partners, using the rental tables.

**Verification:**
- unit tests of each rule against master data;
- data-level checks through `CApiNotify` (the `apinotify_live.sh` pattern: request → player-state dump);
- end-to-end sessions with invariants: stamina never negative, currency conserved, drops within the tables;
- a rules document with each rule's source (a–d).

### Phase 3: battle completeness
- **Port the remaining battle code** by coverage: `CStageManager::Progress`, `CPartyManager::Progress`, `CCharacterObject` (skills, actions, `UpdateSeedCondition`), `CAIAction` / `BehaviorQueue_*`, `CFactorManager::Update` and the conditions, `CNormalCamera`, the `CBattleUIManager` / `CBattleAnime` per-frame bodies, and particles.
- **Real battle inputs:**
  - the party from the party set, with owned characters, weapons, accessories and skills, instead of the invented "RENTAL" party;
  - enemy parties and levels from `master_enemy_*` / `master_mission_enemy_info`;
  - stage data from `master_mission_stage`.
- **Every mission type and boss stage plays:** story, event, training, deep space, sphere211, tower. Also manual control (not just auto), rush combos, assist cut-ins, continue and retire.
- **Verification:**
  - live guest-replay checks (the `SOA_BATTLE_CORE_CHECK` pattern) extended to each ported family;
  - a mission matrix script that plays a sample of every mission type to the result screen, and checks the rewards against the Phase 2 rules.

### Phase 4 (optional): the network protocol
- Reverse-engineer `Aska::Yayoi::GameRPC`: framing, session, any encryption, the FunctionID dispatch.
- Implement a compatible server on top of the Phase 2 rules. Then `NetworkApiCaller` runs unmodified, and an Android device or Waydroid client with the host name redirected could play too.

### Phase 5: fidelity review
- Compare against whatever reference material exists: old screenshots or videos, community wikis, and any saved server traffic.
- Replace remaining (c) and (d) rules where evidence allows.
- Keep the restored behaviour switchable, and keep the offline 3.8.0 behaviour as the default.

## How the work would run
Same model as the previous runs:
- parallel agents in worktrees;
- differential tests plus smoke and session gates;
- the integrator merges into `linux-port`.

Suggested waves:
1. **Wave A:** Phase 0 (verdiff, dual-load oracle, layout check, API catalogue), plus the server state core (Phase 2.1). Agents: `verdiff`, `oracle`, `apicat`, `server-core`.
2. **Wave B:** the Phase 1 mission, party and title flows, plus Phase 2 mission rules and gacha. Agents: `restore-missions`, `restore-party`, `restore-title`, `server-missions`, `server-gacha`.
3. **Wave C:** growth, economy and daily systems, plus the Phase 3 battle ports (stage and party managers, character objects and skills, AI). Agents: `server-growth`, `server-economy`, `battle-stage`, `battle-chars`, `battle-ai`.
4. **Wave D:** the other modes, tutorial, home UI and platform features, plus the mission matrix. Phase 4 comes after.

## Decisions (answered 2026-09-29)

- **Keep changes in the local server emulator whenever possible** (user direction).
  - Prefer making the original client code do the right thing by giving it the server data it expects: responses, player state, flags.
  - Patch or replace client (game) behaviour only when no server-side route exists.
  - Every change to functionality extracted from the original game goes into `docs/client-changes.md`: the symbol, what the 3.8.0 code does, what we changed it to (e.g. "3.7.0 behaviour restored" or "port-specific"), why a server-side fix wasn't possible, and the switch that controls it.
  - Pure native ports that are bit-exact with the guest code are not changes and don't need an entry.
  - This reorders Phase 1: before restoring a gutted 3.7.0 client function, check whether the 3.8.0 code already reaches the feature when the server state is right. Only then restore the 3.7.0 body, and log it.

- **Target: playable, with every assumption documented.** Where no evidence exists, the local server uses a reasonable rule and records it as an assumption: in the code, next to the rule, and in `docs/server-rules.md`, with its source class (a–d) and the reasoning. Anything the player can see that comes from a (c) or (d) rule is listed in one place, so it can be revisited.
- **No captured server traffic exists.** Formats come from the client code (serialisers, `CApiNotify` / `DeserializeToInfo`, the schema dump). Rules come from master data, client-side evidence, and documented assumptions.
- **Seed save:** `work/Game-3.7.0.xml` (see above). The local server can start a player from it: the same roster, planet and episode progress, and settings. Levels, items and currencies aren't in the file and get documented defaults.

## Risks and open questions
- **Server-only formulas.** Some are gone for good (exact EXP per mission, evaluation thresholds, hidden pity). The plan documents every guess as such and prefers client-side evidence.
- **Layout drift.** Layout changes between 3.7.0 and 3.8.0 in touched classes would force rewriting parts of the restored code against 3.8.0 layouts. Phase 0 measures this first.
- **Time-gated content.** Events and campaigns keyed to real dates need the clock override. Some event data may not be in the 3.7.0 download.
- **Multiplayer and social features** (friends, rankings, clans) can only be approximated locally.
- **Resolved questions:** see "Decisions" above. No server traffic exists, and the target is playable with documented assumptions.
