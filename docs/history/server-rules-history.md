# docs/server-rules.md: history

What `docs/server-rules.md` said about its own making, moved here when it was re-headed by domain (server/PLAN-readability.md R20, 2026-10-04). The rules themselves are all in `docs/server-rules.md`; the evidence check (`tools/server_evidence.py`, T0's `server-docs`) counts this file with it, so nothing moved here is lost. Links to the current sections use their anchors.

## Origin

Written 2026-09-29 by agent `apicat` as the skeleton for `server-core` and the Wave B/C server agents. Master data is the 3.7.0 DB (`data/basmaster-3.7.0.sqlite3`); the queries were run against it.

## Who wrote which section

The section headings named the agent that wrote them. Each old heading, and where its text is now:

- "12. Home (agent home370, `server/src/api/player/home_footer.cpp`)" -> [#home](../server-rules.md#home)
- "Titles (称号; agent a3-home, `server/src/api/player/titles.cpp`)" -> [#titles](../server-rules.md#titles)
- "Notice board page (お知らせ; agent a3-home, `server/src/api/player/notice.cpp`)" -> [#notice-board](../server-rules.md#notice-board)
- "Server core: what `server/` implements (agent `server-core`)" -> below (moved here)
- "Party sets (`UpdatePartySet(PartySetInfo const&)`, agent `restore-party`)" -> [#party-sets](../server-rules.md#party-sets)
- "Assist (`SetAssist(u64 character, u64 assist character)`, agent `restore-party`)" -> [#assist](../server-rules.md#assist)
- "UI tutorial flags (`UpdateView(ViewFlagType kind, u64 flags)`, agent `restore-party`)" -> [#ui-tutorial-flags](../server-rules.md#ui-tutorial-flags)
- "Home character (`UpdateHome(u64 character)`, agent `restore-party`)" -> [#home-character](../server-rules.md#home-character)
- "Entry flow: login, new player, tutorial (agent `restore-title`)" -> [#entry](../server-rules.md#entry)
- "soa-server: the wire layer (agent `s2-wire`; `server/net/`)" -> [#wire-layer](../server-rules.md#wire-layer)
- "soa-server: the CDN (agent `s3-cdn`; `server/src/cdn/`, `soaserver/cdn.h`)" -> [#cdn](../server-rules.md#cdn)
- "Growth and economy: what the extension modules implement (agent `server-growth`)" -> [#growth-and-economy](../server-rules.md#growth-and-economy)
- "Player-visible (c) and (d) rules (agent server-growth)" -> [#growth-register](../server-rules.md#growth-register)
- "Server missions: what agent `server-missions` added" -> [#server-missions](../server-rules.md#server-missions)
- "Campaign progression (agent `campaign`; `server/src/api/campaign/campaign.cpp`)" -> [#campaign](../server-rules.md#campaign)
- "Rental helpers (agent `gaps-core`; `server/src/api/social/rental.cpp`)" -> [#rental-helpers](../server-rules.md#rental-helpers)
- "Server rules added by agent `server-rules` (2026-09-29)" -> below (moved here)
- "Single and bulk draws of `Gacha` (agent `stepup-list`)" -> [#gacha-draws](../server-rules.md#gacha-draws)
- "Step-up and box gacha lists (agent `stepup-list`; `server.cpp` `stepup_value`, `box_list_value`, `box_value`)" -> [#gacha-lists](../server-rules.md#gacha-lists)
- "Deep space (agent `deepspace`; `server/src/api/deepspace/deepspace.cpp`)" -> [#deepspace](../server-rules.md#deepspace)
- "Sphere 211 (agents `sphere211`, `sphere211b`; `server/src/api/sphere211/sphere211.cpp`)" -> [#sphere211](../server-rules.md#sphere211)
- "Tower (試練の遺跡; opt-in `--restore-tower`, agent `a11-tower`; `server/src/api/tower/tower.cpp`)" -> [#tower](../server-rules.md#tower)
- "Events (agent `events-core`; `server/src/api/events/event_missions.cpp`, `events.h`)" -> [#events](../server-rules.md#events)
- "Event extras (agent `events-extras`; `server/src/api/events/ranking.cpp`, `api/events/world_boss.cpp`, `api/events/favor_drop.cpp`, `api/shop/shop.cpp`)" -> [#event-extras](../server-rules.md#event-extras)

## Notes for the server-core implementation (as of its commit 9792e87)
Where the evidence above pins down something the first implementation assumed. Each item names the section.
- **Battle status** (3): the client's formula rounds half away from zero (not floor) and multiplies by the `master_rank` row of (rank, limit break); AP, element defences, equipment, factors and favor AP also come from it. Calling the guest `PersonModel::CalculateParameter` / `tCharaData::CalcStatus` gives the exact values.
- **Mission time and battle log** (2.3): the request carries the serialized `CBattleLogInfo` (`CParameterManager+0x52d8`); no need for a constant.
- **MissionStart's third argument** (2.2): the helper (support) index + 1 (b), not a party; the party comes from the player's state.
- **The client clock** (conventions): 3.7.0's `NowTime` follows the `data.Time` every response carries; nothing else is needed (the frozen clock of the client before the rebase: `docs/history/server-rules-3.8.0.md`).
- **Favor per battle** (2.3, 8): `master_favor_battle_effect` by stamina cost (a) rather than a flat +100.
- **Stamina** (1): partial regeneration progress, the refill / item amounts (b), the halving campaigns (a).
- **Player level table** (1): levels missing from `master_player_level` are interpolated (b); a plain row lookup breaks above level 255.
- **Gacha** (4.3, 4.5): draw from `data/gacha_pools.sqlite3` through `server/gacha_pools.h` (S/A by pick-up, rarity 6 never drawn, weapon banners draw weapons, units only from their release time), and answer `GetGachaRate` from the same file; box gacha rules (4.4).
- **Surprise enemies and drops** (2.2, 2.3, 2.4): `surprise_rate` per mission (a); the result screen lists `DropList` / `CommonDropList` / `RareDropList` / `ClearPresentList`, and shows a first-clear item only when it matches a `master_mission_clear_present` row (b).
- **Stocks** (1): the master data gives 500 for item / gear stock (`item_stock_max`, `gear_stock_max`).

**Status in server-core (2026-09-29, 02:00).** Done:
- battle status (rounding, `master_rank`);
- mission time from the battle log;
- MissionStart's party from `Player.party_id`;
- the clock (`service_stop_day` dropped + `data.Time`);
- favor from `master_favor_battle_effect`;
- the player level interpolation;
- stocks (500);
- gacha from the reconstructed pools, with duplicates via `role_category_id` + `LimitBreakCharacter` / `LimitBreakItem`;
- the result screen's drop list.

Not yet:
- surprise enemies and surprise / campaign / character-bonus drops;
- mission unlocks (`ActiveMissionList`);
- equipment and factors in the battle status;
- chips for duplicates;
- step-up / box gacha;
- error codes on the FakeApiCaller route.

## Server core: what `server/` implements (agent `server-core`)
The implementation's own rules, as the code applies them, with labels. Where they differ from the sections above, the sections above are the evidence; the "Notes for the server-core implementation" list says which have been brought in line.

## The game's save is not synced (removed 2026-10-01)
The game's save keeps a summary of the player (`player_name`, `player_level`, `player_exp`, `player_fol`, `player_stamina_max`, `player_home_pc_roleid`, `person_size`, `person_master_role_id_N`; `CUserDataUtility::Save_PlayerInfo` / `Save_PartyInfo`). The client before the rebase read it back at boot and showed it over the boot response, so the server used to write its own state into it before every boot (`sync_save`). **3.7.0 never reads it back (b):** the only functions that read those keys from the local KVS are `CUserDataUtility::Load_PlayerInfo` and `Load_PartyInfo` (string xrefs in `libSOA-3.7.0.so`), both called only from `CUserDataUtility::LoadFromLocalKVS` (@01f5a788), which has no caller: no BL/B, no address taken (ADRP/ADD), no pointer in any table or relocation. The 3.7.0 client takes the summary from `Login`'s `data.Player` and the roster from the responses only, so the sync was dead and is gone (agent open-issues). The server still *reads* the client's `Game.xml` as the last seed fallback ("Seed").

## Status of the new-player flow (2026-09-29)
Verified on screen (`port/scripts/newplayer_session.sh`):
- title;
- `Login` → 19001;
- terms and name entry;
- `CreatePlayer`, then `Login`;
- the opening scene `mc00_010`, with its choices;
- `UpdateTutorial(1)`, then `mc00_015`;
- `UpdateTutorial(2)`, then the battle tutorial `ms00_001`. That's two stages with the three NPCs, the 3.7.0 tutorial dialogs (move, attack, skills, RUSH combo), and `MissionEnd`;
- `UpdateTutorial(3)`, then `mc00_025`;
- `UpdateTutorial(4)`: the mission-menu step (re-verified 2026-09-29, agent gaps-core). Planet Mere's map shows 1-01 惑星メーア with ここをタップ, then ストーリー開始 and the story. `UpdateTutorial(6)` follows, then "I summoned companions" 次へ, then ホーム. **Home is reached** with `UpdateTutorial(7)`.

**The old crash is gone.** At `UpdateTutorial(4)` the game used to crash in `CMissionMenu::SetLastPlayPlanetNow` (fault at 0x40). In tutorial mode, 3.7.0's `CreatePlanetList` keeps only the tutorial planet and the first planet (`tMissionData::GetTutorialPlanetId` / `GetFirstPlanetId`) out of `CParameterUtility::CollectEffectivePlanet()`, then selects index 1. `SetLastPlayPlanetNow` reads element 1 of that list, and with an empty list (no `ActiveMissionList.Planet` from the server) it read address 0x40. The campaign server now sends `ActiveMissionList` with every response, and by this step the tutorial's story clears (`MissionTalk` / `MissionEnd` of mc00_010 … mc00_025) have opened planet Mere's first mission. So both planets are listed, and no server change was needed. `port/scripts/newplayer_session.sh` now plays this step through to home.
- **After home (re-checked 2026-09-30, agent a3-home): the 3.7.0 home tutorial runs**, with no further change. 3.7.0's `CHome::Initialize` sees tutorial memId 8 (`CPhase_TutorialNext`'s table: 7 → phase 5, 8 → home, 9 = `LastMemId`) and starts two UI steps: the プレゼント button highlighted with cp0002_tutorial_010 (次へ), then the footer ガチャ with cp0002_tutorial_011 (閉じる). When the set ends, the `CTutorialManager::StateInit` state-6 lambda sends **`UpdateTutorial(9)`**; no `UpdateTutorial(8)` is ever sent (8 is only the in-memory home step). `IsTutorialClear` is then true, and the popups the login armed open (the notice board). **(b)** There is no tutorial gacha (no API, master row or global key): the text only points at the normal gacha button. The server needs nothing new: `UpdateTutorial` stores any value, and the one-time UI tutorials that follow reach it as `UpdateView` (the FakeApiCaller route, `docs/client-changes.md`). `newplayer_session.sh` and `tutorial_session.sh` play it to `UpdateTutorial(9)`.
  - Off this path, 3.7.0's episode select (`CMissionSelectPart`, phase 8: the mission map's Ep選択) has its own one-time hints: `Initialize` calls `CTutorialManager::CheckViewStart(8, …)`, whose lambda starts UI tutorials 22 (0x16), 58 (0x3a) and, while EP3 is open (`IsOpenEP3`), 59 (0x3b) (`GetViewTutorial`: those ids at view 8, unless `IsTutorialViewStatus` has them). **Verified on screen (agent open-issues, 2026-10-02):** the tutorial's new player booted again (with the home's own hints marked seen in `view_status`) → ミッション → Ep選択: ここはエピソード選択メニューね… (22), then the episode-download hint (58); 閉じる sends `UpdateView(0, flags | 1<<22)` and the server stores it. Before the rebase `CMissionSelectPart` wasn't restored, so these hints never showed. Nothing for the server to do.

## Server rules added by agent `server-rules` (2026-09-29)
Code: `server/src/api/items/gear.cpp` (gear) and the modules named below; tests `server/src/rules/rules_tests.cpp` (...), and for the gear `server/src/api/items/gear_tests.cpp` (`items/gear-apis`, `items/gear-barney-chance`) and `server/src/rules/gear_rules_tests.cpp` (`items/gear-rules`). The scratch-server tests seed from the committed synthetic `port/server-data/test-seed.xml` (see "Seed") and need the 3.7.0 master DB; without either the test fails with a message naming the missing file. Decompiles: `work/decomp/server-rules-*.resolved.c`.
