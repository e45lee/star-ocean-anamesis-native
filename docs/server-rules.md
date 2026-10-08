# Local server: game rules

The rules the local server (`server/`, in-process in `soa` or standalone as `soa-server`) applies when it answers the game's API requests. For the requests and response shapes themselves see `docs/api.md`; for the plan see `docs/history/PLAN-restore-original.md`.

**Layout (since 2026-10-04, docs/history/PLAN-readability.md R20).** One section per `server/src/api/<domain>/` folder, after the source labels and the conventions; then the server-wide core (architecture, seed, wire, CDN) and the register. Every section has a stable anchor (`<a id="titles"></a>` above its heading), and code comments link those: `docs/server-rules.md#titles` (`tools/check_server_docs.sh` checks that every link resolves; `tools/server_rules_doc.py --check` that every section has an anchor). The numbered sections (1 to 12) keep their numbers from the layout before, because the text cites them ("2.4", "section 10"). How the sections came to be and who wrote them: `docs/history/server-rules-history.md`.

| Section | Code |
|---|---|
| [Player: state, parties, home](#player) | `server/src/api/player/` |
| [Entry flow: login, new player, tutorial](#entry) | `server/src/api/entry/` |
| [Missions](#missions) | `server/src/api/missions/` |
| [Campaign progression](#campaign) | `server/src/api/campaign/` |
| [Events](#events) | `server/src/api/events/` |
| [Gacha](#gacha) | `server/src/api/gacha/` |
| [Growth](#growth) | `server/src/api/growth/` |
| [Items and gear](#items) | `server/src/api/items/` |
| [Favor](#favor) | `server/src/api/favor/` |
| [Daily: login bonuses](#daily) | `server/src/api/daily/` |
| [Presents and achievements](#presents) | `server/src/api/presents/` |
| [Shops and passes](#shop) | `server/src/api/shop/` |
| [Social: follows and rental helpers](#social) | `server/src/api/social/` |
| [Deep space](#deepspace) | `server/src/api/deepspace/` |
| [Sphere 211](#sphere211) | `server/src/api/sphere211/` |
| [Tower](#tower) | `server/src/api/tower/` |
| [Settings and account](#settings-account) | `server/src/api/settings/` |
| [Server-wide: architecture, seed, wire, CDN](#core) | `server/src/core/`, `server/net/`, `server/src/cdn/` |
| [English mode (`--english`)](#english), [its story files](#english-story), [the derived layer](#english-derive) | `server/src/master/english_text.*`, `server/src/cdn/` |
| [Register of (c) and (d) rules the player can see](#register) | generated from the domains' tables (`tools/server_rules_doc.py`) |

<a id="labels"></a>
## Source labels
Every rule carries one label. Put the same label in a comment next to the code that applies it.
- **(a) master data**: the table and columns decide it. The right answer.
- **(b) client-side evidence**: client code shows, previews or pre-computes the value; the function is named. Also right, as long as the server matches it.
- **(c) outside knowledge**: how the live game behaved, from memory of the game or community sources. Needs checking.
- **(d) assumption**: a reasonable, playable default where no evidence exists, with the reasoning. Listed again in "Register of (c) and (d) rules" at the end, because every (c)/(d) value the player can see should be revisited.

<a id="conventions"></a>
## Conventions
- **The client's clock and how the server sets it** (b: `CTimeUtility::NowTime`, `CServerTime::UpdateServerTimeOffset`, `CTimeUtility::str2time_t`):
  - 3.7.0's `NowTime()` is `CServerTime::FixTime(BAS::LocalTime())`: the device clock corrected by the server-time offset (decompile @01ec5bdc). It doesn't read `master_global.service_stop_day` (2021/06/24 14:30:00 in the 3.7.0 DB); that row's only readers are the service-end check (`CTitle::Setup`, `CPhase_Server::CPhase_Server`: `docs/client-changes.md` "Emulator mode"). The client before the rebase froze its clock at that row: `docs/history/server-rules-3.8.0.md`.
  - **Server-side, no client change:** the master the server's CDN serves has no `service_stop_day` row (`apply_client_master`, both server modes), as in service; platform370's native patch takes the check out on the APK's built-in master.
  - **The offset** comes from `data.Time`: every response's `DeserializeToInfo` calls `UpdateServerTimeOffset`, which parses `data.Time` and, when it differs from the local clock by 60 s or more, stores the difference as the offset. So the server can put its own clock (host time or `--clock`) into the client by sending `data.Time` in its responses.
  - Time strings are `YYYY-MM-DD HH:MM:SS` or `YYYY/MM/DD HH:MM:SS` (both separators parse).
  - The server must use the **same** "now" as the client, or what it grants and what the client shows drift apart.
- **Time.** The server clock (`now()` in server.cpp, `server::clock_now()`, `ext::Ctx::now`) is the host clock, or `--clock "YYYY-MM-DD HH:MM:SS"` when set, running on from there (the plan's clock override for replaying past events; `core/options.h`). All master `opened_at` / `closed_at` strings are JST (`YYYY-MM-DD HH:MM:SS`); the client compares them with its own server-time offset (`CServerTime`, `CTimeUtility::str2time_t`). (a) The server, like the guest (`BAS::LocalTime`, the host's `localtime`), reads and writes these strings in **host local time, treated as JST** (`server/src/core/time.cpp`: `localtime_r` / `mktime`; no time-zone conversion): on a host outside JST the dates fall at local, not Japanese, midnight, consistently on both sides. **(d)**
- **Clock: the event calendar** (`server::event_now()`, `ext::Ctx::event_now`; `server/src/core/clock.cpp`). Dated content (event terms, deep-space missions, the Sphere 211 season) uses it; the wallet, stamina, login and daily counters keep the real `now()`. **(d)** With `--clock` it is the clock. Without, the service's calendar replays year after year: today's month, day and time of day are mapped onto the most recent year in which some `master_event_term` covers that month-day (`opened_day <= Y-MM-DD <= closed_day`, day-level so the year holds for the whole day). The candidate years are the years the table's terms open in (2016-2021 in the 3.7.0 DB), newest first; open-ended terms (closing after the newest of those years, e.g. the 2030-12-31 rows) don't count; Feb 29 only matches leap years. If no year qualifies, the real time. In the 3.7.0 DB every day of the year maps into 2019-2021 (e.g. Jan 3 -> 2021, Jun 25 -> 2020, Oct 1 -> 2019); unit test `server/event-now`. Why: the user chose "replay the calendar" so seasonal events come back on their dates without a `--clock`; nothing about which events exist is hard-coded.
- **The daily reset is 04:00 JST** (host local time, treated as JST, as above): `master_global.login_bonus_reset_hour` = 4, read by `CParameterUtility::LoginBonusResetHour`. Use it for every "per day" counter (login bonus, day-limited gacha, daily achievements, favor tap limits). (a)+(b) for the login bonus; (d) for the other daily counters.
- **Content grants.** A reward is `(content_type, content_id, num)`; the types are in `docs/api.md` "Content types". The server applies each grant to its state and reports it in the response infos the screen reads (`AddItem`, `AddCharacter`, `UpdateStockItem`, `Wallet`, `Player.fol`). Type 99 (item set) expands to its `master_item_set` rows (a).
  - `AddItem` (new weapons and accessories) is a map {uid as a string: CItemInfo} in every answer **(b)**: `CAddItemList` is an `IInfoBaseMap<u64, CItemInfo>` whose `DeserializeArray` (@0163d574) returns 0, so an array is ignored and the items reached the client only with the next full player load; `DeserializeChild` (@0163d57c) reads each entry under its key (`ConvertParserValueToKey` @0163d740: a string or an integer key), and `CApiNotify::AddItem` (@014c207c) adds them to the item list. One helper builds it (`ext::add_items`, `server/src/core/ext.cpp`): the gacha and box gacha, presents, MissionEnd and its extras (`ext::add_drop`, world-boss time bonuses), the shops and exchanges, event ranking rewards, deep space, ItemCompose's unique results and the overflow box's withdraw. (Before agent `server-u-stamps`, every answer but the overflow box's withdraw sent an array.) Tests: `server/add-item-map`; session `add-item` (`port/scripts/add_item_session.sh`: a drawn weapon is in the item list at once and sold, no re-login).
- **Caps.** FOL is capped at `master_global.item_fol_max_num` = 4,200,000,000 (a); stack items at `item_stock_max_num` = 100,000,000 per item (a); weapons / accessories at `Player.item_stock` slots (see "Stocks and wallet"). When a cap would be exceeded the live game sent the overflow to the present box (c); the local server does the same.
- **Randomness.** Use one seeded PRNG per player state, so a session can be replayed (d). Weighted lots ("by `rate_weigh`") pick one row with probability `rate_weigh / sum(rate_weigh)` over the candidate rows (a: the column's name and the per-mission sums, e.g. `mf01_001` weights sum to about 10,000).

<a id="player"></a>
## Player: state, parties, home
Code: `server/src/api/player/` (the player state and its load, parties, assist, the home character, the battle status, the home footer, titles, the notice page).

<a id="player-rank-stamina"></a>
### 1. Player, stamina and player rank

<a id="player-rank"></a>
#### Player rank (調査ランク) and its EXP
- **Level curve:** `master_player_level` (257 rows for levels 1..999): `next_exp` is the EXP needed from this level to the next (level 1: 60, 2: 111, 100: 5,133, 255: 13,038) (a). The player's `exp` is kept **within the current level**: the header shows `next_exp(level) - Player.exp` (b: `CCommon::UpdateMyStatus` → `CUIUtility::GetNextLevelExp(level)`).
- **Levels missing from the table are interpolated** (b: `MasterPlayerLevelModel::GetByCalculatedLevel`): with the nearest rows below (`low`) and above (`high`), `value = low.value + round_half_away((high.value - low.value) / (high.level - low.level) × (level - low.level))`, for both `next_exp` and `stamina`. The server must use the same interpolation.
- **Maximum rank:** `master_global.Player_Rank_max` = 900 (a), read by `CUIUtility::GetMaxLevel()`, which clamps to 999 and defaults to 255 when the key is missing (b). EXP beyond the maximum is dropped (d).
- **EXP sources:** missions (`exp` column of the mission tables), deep-space `player_exp`, Sphere211 `base_exp` × `exp_rate`. (a)
- **Rank up** (`HostPlayer.is_level_up`, `Player.is_level_up`): the result screen says 調査ランクがアップしました / スタミナ上限がアップします / スタミナが加算されます (`uimsg_result_rankup0..2`), so a rank-up raises `stamina_max` to the new level's `master_player_level.stamina` and **adds** stamina. (b: messages). How much is added: the new `stamina_max`, on top of the current stamina (overflow allowed) (c: the live game refilled stamina on rank-up; "加算" = added, not "set").

<a id="stamina"></a>
#### Stamina
- **Maximum:** `master_player_level.stamina` of the player's level (level 1: 10, 50: 120, 100: 140, 255: 200, 999: 300). Sent as `Player.stamina_max`. (a)
- **Regeneration is computed by the client** from `Player.stamina`, `Player.stamina_max` and `Player.stamina_update`, so the server must use the same formula (b: `StaminaUtility::NowStamina` → `CTimeUtility::NowAp(stamina, max, heal_time, str2time_t(stamina_update))`):
  ```
  now_stamina = stamina                                   if stamina > max (overflow is kept, no regen)
              = min(max, stamina + floor((now - stamina_update) / heal_time))   otherwise
  ```
  `heal_time` = `master_global.stamina_heal_time` = 180 s (default 180 when missing, b: `StaminaUtility::StaminaHealTime`).
- **Spending** (MissionStart): compute `now_stamina`, subtract the cost, store the result as `stamina`, and set `stamina_update` = `now - ((now - stamina_update) mod heal_time)` so the partial minute toward the next point is kept (d: matches the client's `OneApRemainSec`; the live server's exact bookkeeping is unknown). When `now_stamina >= max` before spending, set `stamina_update = now` (d).
- **Other stamina types** (b: same functions): type 2 = Sphere211 stamina (maximum `master_global.sphere_stamina_max` = 9, sent as `Sphere211StaminaInfo.stamina_max`, which the client reads at `CParameterManager+0x9c50`; one point per `sphere_stamina_recovery_time` = 17,280 s, client default 14,400); type 1 = tower tries (max 3 = `Tower_Challenge_Count`, no regeneration).
- **Refill with coins** (`StaminaHeal`): costs `master_global.stamina_use_coin` = 100 coins (default 100; b: `StaminaUtility::StaminaUseCoin`) and heals `stamina_max` points (b: `StaminaUtility::StaminaHealPoint(type, nullptr)` = the max, at least 1), added to the current stamina (d: added rather than set, like the items below).
- **Heal items** (`UseHealItem`): `master_item` type 10 (a). Points healed (b: `StaminaUtility::StaminaHealPoint(type, item)`): `heal_type` 1 → `heal_point × stamina_max / 100` (`item_heal_100` = a full refill); `heal_type` 2 or 3 → `heal_point` flat (`item_heal_50/200/300`); anything else 0. Added to the current stamina, overflow allowed (d: the client lets you heal above max; `IsStaminaMaxOver` exists).
- **Owned heal items** listed by the client are stack items of type 10 with `heal_type` 1 or 2 (b: `StaminaUtility::GetHealItems`).
- **Stamina campaigns:** `master_campaign.type_id` 1 (labels `*_sutamina*`, `magnification` 0.5) halve the stamina cost of missions of the campaign's `master_mission_model_type` (0 EP1, 1 event, 3 EP2/EP3, 99 other, -2 all) while it runs (a: labels and values; b: `CUIUtility::IsDecConsumeStamina(missionType)` = `IsCampaignOnMission(1, type)`). Rounding: round up, minimum 1 (d).

<a id="stocks-and-wallet"></a>
#### Stocks and wallet
- Item / gear / follow capacity: start values and expansion (`master_global`: `item_stock_max` 500, `item_stock_up_num` 5, `item_stock_use_coin` 100; `gear_stock_max` 500, `gear_stock_up_num` 5, `gear_stock_use_coin` 100; `follow_default` 30, `follow_max` 300, `follow_up_num` 5, `follow_use_coin` 100). (a) The starting item stock is not in master data: start at `item_stock_max` = 500 (d). So `UpdateItemStock` (buy 5 more slots for 100 coins) is refused with 11006 (d: the code), as `UpdateGearStock` is: the client hides the expansion button once `CParameterUtility::NowItemStockMax` reaches `ItemStockMax` (b: `CItemFrame::Progress` @01b2d454; `ItemStockMax` @0181b990 reads `item_stock_max`, 300 without the row) (agent server-u-missions; `api/items/items.cpp`, test `items/inherit-accessory`).
- **Coins (紋章石):** `Wallet` {free_coin, pay_coin, total_coin}. Spend free coins first, then paid (a: master_text `uimsg_buy_history_explan`, the coin purchase history's note "紋章石を使用する際は無償入手分から先に消費されます", coins are spent from the free ones first; `server/src/core/wallet.h`). Every coin payment follows it: the shops, StaminaHeal, the gacha, a mission's and Sphere 211's continue, deep space's quick return. There is no purchase route in the port (the coin shop closed: `master_global.pay_back_stop` 2022-03-15); coins come from login bonuses, presents, achievements, clear presents and missions (a: those tables grant content type 4). A new player, seeded or created, starts with 300,000 free coins (`--start-coins N`; (d), the user's request).

<a id="player-load"></a>
### Player load (`NoLoginStart`, `Login`, `SimpleLogin`, `GetPlayer`, `CreatePlayer`)
- The whole state goes in one response:
  - `data.Player` (CPlayerInfo fields: id, name, search_id, level, exp, fol, stamina, stamina_max, stamina_update, home_pc_id, party_id, stocks, follow_max, times, is_3d_home);
  - `data.Wallet`;
  - `data.Character` (the roster: CPersonInfo with id, level, exp, limit break, awakening, skills and their levels, rush skill, gauge);
  - `data.PartySet` (map keyed by party id as a string; `PartySetCharacter` entries);
  - `data.StockItem`, `data.Item`.
- 3.7.0's title sends `NoLoginStart` and then `Login`, which loads the player again; both carry the whole state.
- `item_stock` and `gear_stock` are `master_global.item_stock_max` / `gear_stock_max` (500). **(a)** `storage_stock` is 100, plus `master_global.subscription_storage_stock` (400) while the Galaxy Pass runs ([Storage](#storage)). **(b)** + **(a)**
- `follow_max` is `master_global.follow_default`. **(a)**
- `support_pc_id` is the character the player lends (UpdateSupport's, "Rental helpers"); unset or no longer owned, the highest-level character. **(b)** for the key; **(d)** for the fallback.
- `is_3d_home` is the player's 2D / 3D home choice ([Home 2D / 3D](#home-2d-3d)): `player.is_3d_home`, 3D (true) for a player who never chose. **(d)** for the default. `updated_at` is the answer's time. **(d)**
- `Wallet`: `total_coin` = free + paid, `android_coin` = the paid coins. **(d)** The local server has no other store.
- Code: `server/src/api/player/player_info.cpp` (`player_info`, `wallet_info`, `full_player_state`).

<a id="player-stamina-state"></a>
### Stamina in the player state
- **Maximum:** `master_player_level.stamina` for the player's level. **(a)** The table has 257 rows for levels 1..999; the levels without a row are interpolated linearly between the nearest rows, rounded half away from zero. **(b)** `MasterPlayerLevelModel::GetByCalculatedLevel`. `next_exp` is interpolated the same way. The maximum rank is `master_global.Player_Rank_max` (900). **(a)** `CUIUtility::GetMaxLevel` clamps it to 999 and uses 255 without the key. **(b)**
- **Regeneration:** one point per `master_global.stamina_heal_time` seconds (180). A stamina above the maximum (after a level-up) doesn't regenerate, but isn't cut either. **(a)** for the period; **(c)** for the rule shape. (`--stamina-heal-time SECS` replaces the period for tests, 0 stops regeneration: tests/diff runs with 0 so the compared stamina doesn't depend on a run's timing; not a rule.)
- **Mission cost:** `master_mission.use_stamina`, taken at `MissionStart`. **(a)** A start with too little stamina still goes ahead, and stamina stops at 0: never negative. **(d)** The client checks stamina before it asks.
- **Level-up:** the new maximum is **added** to the current stamina; overflow is kept. **(c)** The client's rank-up dialog says スタミナが加算されます ("stamina is added"); see 1 above.

<a id="party"></a>
### Party (`UpdateParty(u32 party, u64 uid1, u64 uid2, u64 uid3)`)
- Stores the three members in slots 0..2. A uid that isn't owned is stored as empty (only owned characters). **(d)** A missing party id is 1.
- **Party ids** 1..`master_global.party_set_max` (10). **(a)** Another id changes nothing and gets no body (the host's fallback, no error code), as `UpdatePartySet`. **(d)** (Until schema version 6 any id was taken, 0 included, and got its `party_set` row; the client's serializer itself refuses an id ≥ 7, docs/api.md "Wire format".)
- A slot whose character changes loses the set's weapon, accessory, skills and assist for it (they were the previous character's): the slot has none until `UpdatePartySet` saves it. A slot keeping its character keeps them. **(d)** (Until schema version 6 they stayed in either case.)
- The party edited becomes the player's current `party_id`, which `MissionStart` uses. **(d)**
- Answers `PartyUpdate` and `PartySet`.
- The request shape comes from the method's signature. No caller was found in 3.7.0 (`docs/api.md` "UpdateParty": the party screen saves with `UpdatePartySet`), so it's untested on screen.

<a id="party-sets"></a>
### Party sets (`UpdatePartySet(PartySetInfo const&)`)
The 3.7.0 party screen saves a party set with `UpdatePartySet` when the player leaves the member select. On the FakeApiCaller route the request arrives as `PartySetInfo::Serialize()` text, the same string `NetworkApiCaller` sent: `party_id,icon_id,is_lock/` and one `id,party_index,character_id,weapon_item_id,accessory_item_id,skill_id1,skill_id2,skill_id3,assist_character_id/` per member (`party_index` 0..2: three members; the screen sends back the members it got, so a fourth record came only from the server's own fourth row, see below). **(b)**
- **Three members; the fourth slot is the helper's:** `CParameterUtility::tPartyData::Initialize(PartySetInfo const*, bool)` (@01832a9c) builds the party's four `tCharaData` from `PartySetCharacter[0..2]` (by position) and resets the fourth (`tPartyData` + 0x8798 = 8 + 3 × 0x2d30), the slot the mission menu fills with the chosen helper (a rental, an own character or an event NPC: "Rental helpers", "NPC helpers"); the party screen shows three members. A set's member past the third is never read by the client. **(b)** So a set holds slots 0..2 (`kPartyMembers`, `server/src/api/player/party_set.h`), `MissionStart` fields only those (plus the helper), and schema version 20 dropped the slot-3 rows earlier states had: the seed wrote the home character and three others, and `UpdatePartySet` kept the record of index 3 the screen sent back, so a fourth character the party screen never showed fought in every battle (and an own helper made it five).
- **Party ids** 1..`master_global.party_set_max` (10). **(a)** A request outside that range, or text without a `party_id,icon_id,is_lock` record, changes nothing and returns no body: the host answers with its fallback, without an error code. **(d)**
- **Members:** each record replaces the set's slot `party_index`; a record without all nine fields, or whose `party_index` is outside 0..2 (the set's three slots, b, above), is skipped (until schema version 20, outside 0..3). A `character_id` that isn't owned is stored as empty. **(d)** The member's weapon, accessory, three skills and assist are stored with the set (table `party_member`, one row per slot), and `icon_id` / `is_lock` with the set (table `party_set`). **(b)** from the serializer. A weapon or accessory that isn't an owned item, or an assist that isn't an owned character, is stored as none; the skills aren't checked. **(d)** (Until schema version 6 they were stored as sent, and a slot index outside 0..3 was kept.)
- **The set's equipment is the member's, not the character's:** `PartySet` sends each slot's `weapon_item_id` / `accessory_item_id` as the set stored them, 0 when it has none, even when the character wears something (`EquipWeapon`). **(b)** the two are separate in the client (`PartySetCharacterInfo` vs `CPersonInfo`); **(d)** that a slot the party screen never saved (the seed's, CreatePlayer's, UpdateParty's) has none. (Until schema version 6 such a slot sent the character's own equipment.) A weapon or accessory a set names counts as equipped: `Item.is_equip` is true and it can't be sold, composed, graded up or used for a gear, as for one a character wears. **(d)**
- **Current party:** the saved set becomes `Player.party_id`, which the party screen opens on (`CParameterUtility::GetPatyIndex`, CParameterManager+0x768) and `MissionStart` takes its members from. **(d)**
- **Response:** `PartySetResult` (the saved set) and `PartySet` (all sets), plus `Player` and `Wallet`. `CApiNotify::OnUpdatePartySetRes` stores `PartySetResult` into the client's party-set map under its id. **(b)**
- **All sets exist:** `PartySet` always carries sets 1..`party_set_max`. A set the player never saved is sent with set 1's members. **(d)** Evidence for why it can't be empty: the client's list code (identical in 3.7.0 and the pre-rebase client, per `verdiff`; the crashes were seen before the rebase) crashes on a set without members (`CUISort::CreateCharaParameterCommon`) or with `character_id` 0 slots (`CPartyMemberSelect`), and the screen pages through the sets it received ("1/10"), so the online server must have sent every set filled. **(b)** What the online server put in a new account's sets 2..10 is unknown.
- **Joinable characters** are the client's rule, not the server's: `tCharaData::IsPartyJoinable` refuses a role whose person is in `master_guest_character` with `unlock_progress` above the player's story progress (CParameterManager+0xca8). With the seed save that's the `tika_release_00` Tika role. **(b)** The server doesn't send story progress yet, so that role stays unselectable.
- Tests: `port/scripts/party_session.sh` (edit set 1 on screen, save, battle; checks the MissionStart members); `player/party-set-text` (the text's parser, `server/src/api/player/party_tests.cpp`); the `items-party` replay corpus.

<a id="assist"></a>
### Assist (`SetAssist(u64 character, u64 assist character)`)
- The equipment screen (装備・技・アシスト変更 → the assist icon) sends it. An assist of 0 removes the character's assist.
- `CApiNotify::OnSetAssistRes` applies `SetAssistResult {character_id, assist_id, old_assist_id}` to the client's characters. A character has one assist, and an assist character assists only one character: it's taken off whoever had it. The server keeps the same pairs (`roster.assist_uid`, unique: the table `assist` before schema version 4). **(b)**
- Both characters must be owned and differ, else nothing changes and the request isn't handled (no body: the host's fallback answer, no error code). **(d)** The level-70 requirement is the client's (the assist list refuses lower levels, and says so). **(b)**
- `Character` entries carry `assist_character_id` and `assisting_character_id` from those pairs, so they survive a restart and reach `MissionStart`'s party status. **(b)** for the keys (`CPersonInfo`).
- Tested on screen with the seed's ★6 characters raised to level 70 in the server DB: Maria ← Karin, shown as ASSIST.

<a id="home-2d-3d"></a>
### Home 2D / 3D (`Home3DAnd2DSwitching(u8 is_3d)`, agent `nier-home`)
- **What the client does (b):** `CHome::Setup` takes `Player.is_3d_home` (CParameterManager+0xd38) as the home's mode. `CHome::GetAdjutant` (@01aebe38) reports whether the home character may be shown in 3D (`!master_person.home3d_disable`); for one that may not (2B, 9S, A2 and 13 more, `docs/home3d.md`), `CHome::Update` (@01aeafa8) forces the 2D home, and `CHome::Progress` sends `Home3DAnd2DSwitching(0)`. The answer's lambda (@01affa10) continues the home with the mode from the answered `is_3d_home`; a failure returns to the title. The 会話モード footer's 2D/3D変更 button sends the other mode.
- **The rule:** the request's mode is stored as sent (any non-zero: 3D) in `player.is_3d_home` (schema version 12) and answered with the player state; every later player load sends it. **(b)** for the request and the key; **(d)** that one flag holds for every home character (the client keeps one).
- **Default:** 3D for a new player and for every player of a state from before version 12 (what the server always sent). **(d)**
- **Route:** in-process the FakeApiCaller's own method only returned a status and queued nothing, so a 2D-only home character left the home empty (no model, no illustration); the port queues it for the local server (`docs/client-changes.md` "`FakeApiCaller::Home3DAnd2DSwitching`").
- Code: `server/src/api/player/home.cpp` (`home3d_and_2d_switching`). Tests: `player/home3d-switching`, `server/schema-migrate-v12`, the `profile` replay corpus (0, GetPlayer, 1, GetPlayer).

<a id="home-character"></a>
### Home character (`UpdateHome(u64 character)`)
- The 3.7.0 お気に入り変更 screen (`CAdjutantSelect`) sends the chosen owned character's id. The server stores it as the player's home character if it's owned; otherwise nothing changes and the request isn't answered (an empty body: the host's fallback, not an error code). **(b)** for the request, **(d)** for the check. Code: `server/src/api/player/home.cpp`.
- **`Player.home_pc_id` is the home character's uid (b)**, in every player response (`Login`, `GetPlayer`, `UpdateHome`'s answer and the rest that carry `data.Player`). 3.7.0's `CHome::GetAdjutant` (@01aebe38) takes CParameterManager+0x8698 when it's set, else +0xd08 (`Player.home_pc_id`), and looks the value up among the owned characters (+0x1178, stride 0xb88) by `CPersonInfo` uid (+0x60; `docs/notes.md` "AddCharacter"). With no match it falls back to party set 1's first member (the PartySet map at +0x1878: the entry whose `party_id` is 1, member 0's `character_id`), so the role id the server sent before (a rule made for the client before the rebase, whose home read a role id; `docs/history/server-rules-3.8.0.md`) always showed the party leader: right after UpdateHome and after a restart. The seed makes the home character party 1's first member, which hid it. Fixed 2026-10-01. Test `player/home-pc-id`.
- **+0x8698** is the favor login bonus's character, i.e. `FavorBonusContetsResultInfo.lot_character_id` **(b)**, by these readings: `CFavorCharacterLoginBonus::Setup` builds its card from it (`tCharaData::Initialize(+0x8698)`); `CPopupManager::CheckStart` case 6 (the favor login bonus popup) opens when it is non-zero and the contents list at +0x8658 is non-empty; `CFavorBonusContetsResultInfo::Initialize` registers its `lot_character_id` property with the value at info+0xb0, which puts the info at +0x85e8 (an inference: the deserializer writes it through that property, so no store names the offset; a scan for direct stores found only the clearers `CHome::Release` / `Progress` / `ResetFavorabilityLoginBonusInfo`). `CHome::IsVisibleReturnCharaButton` shows the "back to the home character" button while it is set and differs from +0xd08. The server sends `lot_character_id` as a uid ("Premium and favor login bonuses"), so with `home_pc_id` a uid too the two compare as the client expects; with the role id the button would have shown even for the home character itself.
- 3.7.0 doesn't read the save's `player_home_pc_roleid` (only the client before the rebase did; "The game's save is not synced"), so on 3.7.0 the home after a restart depends on `Login`'s `home_pc_id` alone. The seed save's `player_home_pc_roleid` still picks the seeded home character (by role; "Seed").
- Seen in soa-emu against soa-server (2026-10-01): お気に入り変更 → a character in party 1's second slot → UpdateHome → quit → boot. With the role id the home kept showing party 1's leader, in the session and after the restart; with the uid it shows the chosen character in both.

<a id="battle-status"></a>
### 3. Battle party status (`CPersonStatusInfo`)
The server builds each party member's battle status, and the client uses it as is (docs/notes.md "Playing a battle and a gacha through"). **The client has the same computation for its status screens: `PersonModel::CalculateParameter(CPersonInfo const&, ...)` → `CParameterUtility::tCharaData::CalcStatus(CPersonStatusInfo*, bool)`.** The in-process server should call that guest function (or its native port) to fill `CPersonStatusInfo`, so the battle uses exactly the stats the status screen shows. (b)
What it does, as far as read (b: `work/decomp/apicat-status.resolved.c`):
- base stat = round_half_away(`master_role.<stat>` × `master_character_common_parameter[level].<stat>` / 100), for hp, attack, intelligence, defence, hit, guard;
- × the `master_rank` row of (role `rank`, `limit_break_count`) / 100 (e.g. `party_03` = 123 → +23%);
- + the character's `add_*` (seed items) and the equipped weapon / accessory stats (`master_item` attack..guard with their compose level), gear, factor and talent effects (`MasterFactorModel::GetParameter`), awakening (`master_awaken`), favor AP bonus (`GetFavorApBonus`); stats below 1 are clamped to 1.
- Skills: `master_role.master_skill1..5_id` opened at `master_skill*_open_level`, the equipped three from `EquipSkill` (a).
- Rush skill, gauge: `master_role.rush_skill1_id`, `rush_gauge_max`, `rush_gauge_use`, or the `master_awaken` row's (a).
- `weapon_id` = the equipped item's `master_weapon_id` (a).
(The early canned-response generator, `tools/fakeapi_responses.py`, used an invented formula; it was retired on 2026-10-05, `docs/history/fake-server-responses.md`.)

<a id="battle-status-additions"></a>
### Battle status additions (`CPersonStatusInfo`)
- **Equipment:** an equipped weapon or accessory (`roster.weapon_uid` / `accessory_uid` → `items`) adds its `master_item` hp, attack, intelligence, defence, hit, guard and ap (a: columns; b: `CalcStatus` adds equipment).
  - The values are the base ones; growth toward `*_max` with the compose level isn't applied (d).
  - The weapon's `master_weapon_id` becomes `weapon_id` (a), and `*_master_item_id`, `*_limit_break_count` and `*_level` are filled.
- **Favor AP:** `master_favor_level.ap_bonus` of the character's favor level is added to the AP (a: column; b: `GetFavorApBonus`; d: on top of the base 100). The favor level is `favor::level_of` for the role's same_role_id (agent restore-favor).
- **Awakening:** with `awaken` > 0, the `master_awaken` row of the role's category at that level replaces the rush skill, its level, factor and gauge (a). Its talents (factors) aren't added (d).
- **Not yet:** factors and talents (`MasterFactorModel::GetParameter`), seeds (`add_*`), element defences. The seeded roster has nothing equipped, so the battle stats of a fresh player are unchanged.

<a id="battle-status-stats"></a>
### Battle status (party members' stats)
| Rule | Label |
|---|---|
| Each party member's `CPersonStatusInfo` stats come from the server's own formula in both server modes (in-process, `soa-server`, and so `soa-emu`): base × rank plus the seeds (`add_*`, also reported in the `Character` list); the `tests/diff/` flows compare the modes. Mission NPCs come from `rules::npc_status` (master data, "Tutorial battle"). Its last check against the 3.7.0 client model (selftest `server/npc-status-master`, since removed) differed in one row, `master_mission_npc` 409829631 HP 5158 (server) vs 4728 (client): a data difference, not a formula one (agent open-issues, 2026-10-01). That selftest's client read the 3.7.0 APK's built-in master, where the NPC's role (`role_cp0306_b04a_5131`) has the talents `factor_oni_101/103/105/107` (passive `factor_oni_107`: HP and attack +10 %); the downloaded 3.7.0 master, which the server uses and its CDN serves to the client, has `factor_wadoramu10_501`, `oni_103`, `wadoramu10_505/503` (passive `wadoramu10_505`: HP +20 %, attack +15 %). Base HP rnd(3256 × 1.32) = 4298: × 1.2 = 5158, × 1.1 = 4728. The server's formula gives 4728 on the APK master's talents too; test `server/npc-status-409829631`. Until the rebase's revision 2 (2026-10-01) the in-game path asked the client's own computation (`StatusProvider`): `docs/history/server-rules-3.8.0.md`. | (d) |

<a id="home"></a>
### 12. Home (`server/src/api/player/home_footer.cpp`)
The 3.7.0 home reads these.
- **`FooterMissionInfo`** on every full-state player response (Login, NoLoginStart, GetPlayer) (d: which responses the 3.7.0 server sent it on isn't known). The client keeps it in CParameterManager (b): `is_open_extra_dungeon` → +0x1a38 (`IsOpenExtraDungeon`), `is_open_event_mission` → +0x1a68 (`IsOpenEventMission`), `is_open_evolution` → +0x1a98 (`IsOpenEvolution`), `is_open_multiplay` → +0x1ac8 (`IsOpenMulti`); `ep1_new_area_count` is the fifth field.
  - `is_open_extra_dungeon` = 1 (d): no master row says when Sphere 211 opened (the lock text only says "clear missions"); the seeded account (rank 87, every planet open) had it. Whether the button then leads in is the client's `MissionUtility::GetExtraDungeonList` (a part in its period), i.e. the sphere211 module's seasons.
  - `is_open_event_mission` = 1 (d): the event list is served (see [Events](#events)).
  - `is_open_evolution` = 1 (d, c: evolution existed from launch).
  - `is_open_multiplay` = 0 (d): no other players.
  - `ep1_new_area_count` = 0 (d): the campaign's "New" marks are in `ActiveMissionList`.
- **Deep space** is not a footer flag: `IsOpenDeepSpace` is true unless the feature-status map (CParameterManager+0x74a8, `PartialMaintenance`) lists `deep_space` as closed (b). The server sends none.
- **Follow menu** (the home's side menu → フォロー; `server/src/api/social/social.cpp`): `Blacklist` and `GetRecentlyPlayedList` answer the player state only, i.e. empty lists (d: no other players); `SearchPlayer` is refused with error 10002, the game's "プレイヤーデータが見つかりません" (b: master_text `error_message_text_10002`; d: that nobody is found). `FollowList` (also the mission helper list) belongs to the rental / NPC-helper rules.
- **Login-bonus popup after the login** (`api/daily/login_bonus.cpp`): a day granted by the title's `NoLoginStart` is reported with `is_received_now` once more on the following `Login` / `SimpleLogin` (d), so the popup the 3.7.0 login arms finds it (the popup condition is (b): `CPopupManager::CheckStart` → `LoginBonusModel::GetList(true)`).

<a id="titles"></a>
### Titles (称号; `server/src/api/player/titles.cpp`)
What the client reads (b): `TitleList` is a plain array of master_title ids (`CTitleList` = `InfoBaseValueArray<u32>`, kept at CParameterManager+0x71d8); `CHonorMenu::SetupTitleData` lists exactly those ids (`SELECT * FROM master_title WHERE id IN (...)`, split into the バトル / シナリオ / 育成 / その他 tabs by `category`), and adds no default titles itself. `Player.title` (+0xed8) is the selected title; the status bar's plate (`CCommon::UpdateMyStatus` → `CParameterUtility::SetPlayerTitle`) shows its `tips_resource` plate and name, and hides the plate for 0. `SetTitle(u32)` (`CHonorMenu::CallApiSetTitle`) expects `Player.title` back; the menu's 外す sends 0.
- **Owned titles:** the `is_default` titles (26 rows, title_other_0001..0026) are every player's **(a)**; the server lists them in `TitleList` **(d)** (without them a new player's list is empty). The others are earned **(a)**: 355 of the 385 rows are `master_achievement` rewards (`content_type` 13); an achievement's reward goes to the present box (section 10), and receiving it grants the title. Four titles no master row awards (title_bring_0010/0014/0015, title_battle_0025) are never granted **(d)**.
- **Grant** (content type 13, `ext::Grant`): the title joins the owned list; one owned already changes nothing **(d)**. The response then carries the whole `TitleList`, `AddTitleList` (the new ids) and, for a present receive, `PresentGetResult.result.Title` [{`master_title_id`}] **(b)**: the keys (docs/api.md, `CPresentBoxReceiveTitleInfo`).
- **Selected title:** kept in `player.title_id` (NULL: none, sent as 0; the meta key `title` before schema version 3); every `Player` carries it (`server/src/api/player/player_info.cpp` `player_info`). A new player (the seed, CreatePlayer) owns the default titles and wears the first default title by `order_id` (title_other_0001, アナムネシスデビュー) **(d)**: 3.7.0's choice for a new player isn't known, and with 0 the plate stays hidden. (Before schema version 3 both were done at the player's first load; the first answer is the same.)
- **`SetTitle(id)`:** an owned id is stored and answered with `Player.title` and `TitleList`; 0 takes the title off **(b)** (the 外す button, the client's "称号を外しました" dialog); an id not owned is refused with error 10208 **(d)**.
- Checked on screen by `port/scripts/home_session.sh` (the その他 tab, a SetTitle, 外す) and by `player/titles`.

<a id="stamps"></a>
### Chat stamps (スタンプ; `SetStampSlot(vector<u32>)`, `server/src/api/player/stamps.cpp`, agent `server-u-stamps`)
What the client reads (b): `StampList` is a plain array of master_stamp ids (`CStampList` = `InfoBaseValueArray<u32>`, CParameterManager+0x70b0); キャラクター > スタンプ編成 (`CStampSelect::Setup` @01e63150) lists exactly those ids (`CMasterParameterStamp::ParameterList` @01e64414: `SELECT * FROM master_stamp WHERE id IN (...)`) and adds no default stamps itself. `StampSlot` is the palette (`CStampSlotInfo` = `InfoBaseValueArray<u32>`, +0x7138): four stamps per page (`Node_2/plate%d/chara3/stamp_1..4`; `CStampSelect::UpdateSelectStamp` @01e65010 reads slot page × 4 + i, 0 is the empty tile `stp_th_stp0`; `IsSelectStamp` @01e6560c walks it in fours), `master_global.stamp_page_max` pages (`CStampSelect::Initialize` @01e62e20; 3 without the key). A palette shorter than that is read past its end; an empty one leaves the screen without slots and `StampUpdate` never sends. `SetStampSlot` (`CStampSelect::StampUpdate` @01e658a4, its request lambda @01e69270) sends the screen's whole palette when it differs from the one it opened with; `CApiNotify::OnSetStampSlotRes` deserializes the answer into those lists.
- **Owned stamps:** the 12 type-1 `master_stamp` rows (order_id 1..12; `master_global.stamp_kind` is 12) are every player's **(a)**: no master row awards one, while 271 of the 278 type-2 rows are rewards (content type 12 in `master_achievement`, `master_login_bonus_contents`, `master_exchange_shop_contents`); the server lists them in `StampList` **(d)** (without them a new player has no stamp). The 7 type-2 stamps no master row awards are never granted **(d)**.
- **Grant** (content type 12, `ext::Grant`) **(a)**: the stamp joins the owned list; one owned already changes nothing, an id not in master_stamp is logged and skipped **(d)**. The response then carries the whole `StampList`, `AddStampList` (the new ids; `CAddStampList` = `InfoBaseValueArray<u32>`) and, for a present receive, `PresentGetResult.result.Stamp` [{`master_stamp_id`}] **(b)** (`CPresentBoxReceiveStampInfo`; port/fakeapi/schema.txt).
- **The palette:** `stamp_page_max` × 4 slots **(a)+(b)**, stored in `stamp_slots` (schema version 19; NULL: an empty slot, sent as 0) and sent as `StampSlot` on every player load and in SetStampSlot's answer. A player who never set it gets the type-1 stamps in `order_id` order from the first slot, the rest empty **(d)**: 3.7.0's first palette isn't known, and an empty one leaves the multiplayer chat's stamps blank until the player arranges them.
- **`SetStampSlot(stamps)`:** stored slot by slot as sent; fewer entries than slots leave the rest empty; a stamp the player doesn't own or more entries than slots is refused with error 10208 and nothing changes **(d)**. Answered with the player state, `StampSlot` and `StampList`.
- In-process the request is a FakeApiCaller request lambda whose answer already goes to `OnSetStampSlotRes` with NetworkApiCaller's FunctionID (`port/src/native/api/gen/fakeapi_tables.inc`), so the local server answers it with no port change.
- Code: `server/src/api/player/stamps.cpp`. Tests: `player/stamps-load`, `player/stamps-set-slot`, `player/stamps-grant`, `server/schema-migrate-v19`, the `profile` replay corpus; session `stamps` (`port/scripts/stamps_session.sh`).

<a id="notice-board"></a>
### Notice board page (お知らせ; `server/src/api/player/notice.cpp`)
(b) The notice board (`CNoticeBoard`, the first popup 3.7.0's login arms, and the side menu's お知らせ) opens `CWebView::OpenView(1)`, whose URL is `WebViewUtility::GetWebInfo(1)`: the value of key `information` in the server's `WebView` list (`CWebViewInfo`: [{`key`, `value`}], CParameterManager+0x6120; the client appends `?<hash>`). The URL goes to `BAS::WebView` → `SOAActivity.ShowWebView`. 3.7.0's server sent its online notice pages' URL (c); they are gone.
- **`WebView`** = [{`information`: `http://soa-local.invalid/notice`}] on every full-state player response **(d)**: the URL of a page the local server hosts itself; `WebView` is a state key.
- **The page** (`server::web_page`, built when the popup opens): the server clock (and the event calendar when it differs), the event areas open now (`events::open_areas`, the list the event menu shows; names from `master_event_area.name_message_id` **(a)**; at most 12 listed), the running login bonuses with the day reached **(a)**, and the number of presents waiting. Plain text, rows wrapped at 48 columns **(d)**; what it lists is the server's choice **(d)**.
- The desktop has no web view: the port shows the page's text in the popup's page area (client change, `docs/client-changes.md` "Notice board page"). Other web pages (help, terms, gacha rates, ...) aren't hosted and stay blank.

<a id="home-mascot"></a>
### Home mascot (`ChangeMascot(u32 master_person_id)`; `server/src/api/player/home.cpp`)
- **What the client does (b):** `CHome` builds the mascot list from `master_home_message` rows of type 3 (`mascot_*`) inside their dates and story-progress range; お気に入り変更 (`CAdjutantSelect`) shows `Button_mascot_change` when two or more are open, `CMascotSelectDialog` names them from `master_person`, and the request lambda (@01913cc8) sends the chosen one's `master_person` id. The client keeps its own copy too (the KVS `HomeMascotID`, `CUIUtility::SetMascot`).
- **The rule:** the id must be a `master_person` id **(a)** (10208 otherwise); the server doesn't re-check the story progress **(d)** (the list is the client's). Stored in `player.mascot_id` (schema version 17) and sent as `Player.mascot_id` from then on; a player who never chose has no key, as before **(d)**.
- **Route:** in-process a status-only method of the fake caller (Status 1, nothing queued); the port now queues it for the local server (`docs/client-changes.md` "Mascot and role").
- Code: `server/src/api/player/home.cpp` (`change_mascot`), `player_info.cpp`. Tests: `player/change-mascot`, `server/schema-migrate-v17`, the `mastery` replay corpus. Not played on screen: the seeded player's story progress opens one mascot, so the button is hidden.

<a id="deco"></a>
### Character decorations (キャラデコ; `server/src/api/player/deco.cpp`)
会話モード > キャラデコ (`CHomeDecoMenu`): the owned decorations (objects, hair colours) set on a character, saved per character. Decompiles: `work/decomp/server-u-mastery-{n,r,t}.resolved.c` (3.7.0).
- **The gate (b):** キャラデコ opens the menu only when `CParameterUtility::tItemData::HasDecoItem` (@01851b88: a u32 of the player state, CParameterManager+0xaf30) isn't 0, else "デコを所持していません"; then it asks GetDecoInfo (the lambda @01afe53c). The key is `NumDecoObject` (confirmed in game: with it sent the menu opens). The server sends it with every response once the player owns a decoration **(d)** (a response hook; left out at 0, the client's default and what it always got).
- **Owned decorations:** content type 17 (`master_deco_object`) and 18 (`master_deco_hair`) grants **(a)** (item sets, achievements, login bonuses: the core's grant path) join `deco_owned`, one of each **(d)** (FavoriteDecoObject names them by master id, so the client keeps one each; a second grant adds nothing). `GetDecoInfo` answers `DecoObject` [CDecoObjectInfo {id, player_id, master_deco_id, is_favorite}] **(b)** and `NumDecoObject`; the id is `0x7b000000` + the row's **(d)**. `tItemData::GetDecoItemList` makes the menu's items from the list (content types 17-19) **(b)**.
- **Favourites:** `FavoriteDecoObject` / `UnFavoriteDecoObject` (vector of master ids) set the flag and answer `FavoriteDecoObjectResult`, a map of the changed CDecoObjectInfo by master id **(b)** (`OnFavoriteDecoObjectRes` merges it); ids not owned are skipped **(d)**.
- **A character's setting:** `SetCharacterDeco`'s argument is the MessagePack of `CCharacterDecoSendInfo` {character_id, hair_id, pose_id, CharacterDecoObject: [CCharacterDecoObjectInfo]} **(b)** (the lambda @015ef218; the wire's blob, in-process the port serializes the same object: `docs/client-changes.md` "SetCharacterDeco"). The list's 決定 sends it. The character must be owned, the hair 0 or an owned hair colour, every object an owned decoration (10208 otherwise) **(b)** (the menu lists the owned ones); the objects are stored as sent with `player_character_id` set **(d)**, `pose_id` as sent **(d)**; it replaces the character's previous setting; no cost limit is checked **(d)**. Answers `CharacterDeco` (copied into the character by `OnSetCharacterDecoRes`) and `DecoObject`.
- **Every load:** `CPersonInfo` carries `hair_id`, `pose_id` and `CharacterDecoObject` for a character with a setting **(b)** (CPersonInfo +0x7d0 / +0x800 / its `CharacterDecoObject` list; names from `CPersonInfo::Initialize`).
- **State (schema version 17):** `deco_owned` (master_deco_id unique, `is_favorite`), `character_deco` (the character's uid, hair, pose, the objects' MessagePack as hex text; cascades with the character).
- Code: `server/src/api/player/deco.cpp`. Tests: `player/deco`, `server/schema-migrate-v17`; the `mastery` replay corpus (none owned: GetDecoInfo, the favourites skipped, SetCharacterDeco refused); the session `mastery` (planted decorations: キャラデコ, a favourite, a decoration set, both kept after a re-login).

<a id="player-register"></a>
### Player-visible (c) and (d) rules (player)

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Player | rank-up adds the new stamina max to the current stamina | (c) | messages say "added"; amount unknown |
| Stamina | partial regen progress kept on spend | (d) | server bookkeeping unknown |
| Stamina | coin refill / heal items add to the current stamina (overflow allowed) | (d) | amounts are (b) |
| Stamina | halved costs round up, minimum 1 | (d) | no evidence |
| Wallet | free coins spent before paid: (a) since R16 (master_text `uimsg_buy_history_explan`, "Stocks and wallet"); was (c) | (a) | |
| Home | ChangeMascot takes any master_person id (the story-progress list is the client's); Player.mascot_id sent only once chosen | (d) | the client keeps HomeMascotID itself |
| Deco | NumDecoObject sent with every response once a decoration is owned | (d) | the client's gate reads it (HasDecoItem) |
| Deco | one of each decoration (a second grant adds nothing); FavoriteDecoObject skips ids not owned | (d) | the favourites name decorations by master id |
| Deco | SetCharacterDeco stores the objects and the pose as sent; no cost limit checked | (d) | the menu shows the cost gauge itself |
| Wallet | new player starts with 300,000 free coins (`--start-coins`), 500 item slots | (d) | the user's request (was 0); the seeded player gets the same coins and 1,000 slots: both (d) |
| Home | Sphere 211, events and evolution open, multiplayer closed (`FooterMissionInfo`) | (d) | 12; the flags' meaning is (b) |
| Home | follow menu: empty lists, player search finds nobody (error 10002) | (d) | 12 |
| Home | follow / block / neighbor calls and 枠拡張 (UpdateFollowMax) are stubs: answered success, nothing stored, no coins spent, each call logged | (d) | [Stubs](#social-stubs); the user's decision (2026-10-04) |
| Player | `is_3d_home` true until the player switches; `updated_at` the answer's time; Wallet `total_coin` = free + paid, `android_coin` = paid | (d) | "Player load"; `storage_stock` (500 before schema version 15, (d)) is (b)+(a) since: [Storage](#storage) |
| Home | the default titles are owned; a player who never chose wears title_other_0001; SetTitle of an unowned id is refused (10208) | (d) | 12 "Titles"; the lists and keys are (b) |
| Home | the notice board shows a local page: clock, open events, login bonus, present count | (d) | 12 "Notice board page"; the `WebView` key is (b) |
| Character | chat stamps: the 12 type-1 stamps are owned; a player who never set the palette has them in slots 1..12 (the rest empty); SetStampSlot of an unowned stamp or too many slots is refused (10208) | (d) | [Chat stamps](#stamps); the lists, the slot layout and the grant's keys are (b), which stamps are rewards (a) |

<a id="entry"></a>
## Entry flow: login, new player, tutorial
The APIs the 3.7.0 login and tutorial code issues; the client runs that code unchanged. Code: `server/src/api/entry/entry.cpp`.

<a id="client-reports"></a>
### The client's reports: `SendErrorLog`, `CbtCertification`
Code: `server/src/api/entry/entry.cpp`.
- **`SendErrorLog(text)`** (the coin shop's and the direct item shop's payment error report, `CCoinShop::SendErrorLog` / `CDirectItemShop::SendErrorLog`): logged as a warning, `SendErrorLog: <text>`; nothing stored; answered `{Time}`. **(b)** `OnSendErrorLogRes` (@014cd0e0) reads nothing back; **(d)** the log is the only place a local server can show it.
- **`CbtCertification(code)`** (the closed beta's certification code, `CClosedBetaDialog::ToRelease`): any code is accepted, nothing stored; answered with the player state. **(a)** `master_global.cbt_end` 2016/11/28: the closed beta is over; **(d)** that any code passes. Before, the in-process route answered it with the canned `update_home.msgp`.
- Tests: the `profile` replay corpus (50, 51), unit test `entry/client-reports`.

<a id="session-and-login"></a>
### Session and login
- **`LoggedIn`** is false until a `Login` / `SimpleLogin` succeeds. **(b)**
  - The 3.7.0 `CPhase_Login` sends `Login` only when `IApiCaller::LoggedIn()` is false (vtable +0x6a0).
  - It's reported through `FakeApiCaller::LoggedIn` with the in-process server.
- **`Login` / `SimpleLogin` with a player:** the whole player state, as `NoLoginStart`. **(b)** The 3.7.0 result lambda moves on to the terms-version check on success.
- **`Login` without a player:** error **19001**, and nothing is applied. **(b)** The result lambda (`CPhase_Login::Progress` lambda #1, 3.7.0 `0x17bff9c`) treats exactly 19001 as "no account" and starts the new-player flow. Any other error returns to the title.
  - The error goes through `FakeApiCaller::IsSuccess` / `IsFailure` / `ErrorCode`, and the answer isn't applied, as `NetworkApiCaller` does with a failed request.
- **`NoLoginStart` / `GetPlayer` without a player:** `data.Time` only. **(d)**
- **`GetMissionList`:** `data.Time`, plus the campaign's `ActiveMissionList` and the events' `ActiveEventMissionList` / `CampaignInfo` (sections "Campaign progression", "Events"). **(d)** (the keys: **(b)** docs/api.md).
- **`GetServerTime`:** `data.Time`. **(b)** (`time_only`, the answer GetMissionList and a playerless `NoLoginStart` / `GetPlayer` share.) `CPhase_SyncServerTime` sends it when `CPhase::CheckSynkServerTime` asks for a resync: on login, and when the 10-minute bucket changes between phase switches.
- **`--new-player`** (port option): the server starts without a player, so the client runs the new-player flow. Without it, the server seeds the 3.7.0 save's player (see "Seed").

<a id="new-player"></a>
### New player (`CreatePlayer(name, uuid)`)
| Value | Rule | Source |
|---|---|---|
| level, EXP, FOL | 1, 0, 0 | (d): the start of the rank table |
| stamina | full: `master_player_level.stamina` of level 1 | (a) max; (d) full |
| coins | 300,000 free (`--start-coins N`, the user's request; was 0), 0 paid | (d) |
| starter characters | `master_global` `Default_Character_1..3` of the 3.7.0 DB (`role_cn0014_b01a_3011`, `role_cn0012_b01a_3073`, `role_cn0017_b01a_3025`), level 1; party 1 = these three; home character = the first | (a) the keys; (c) that the server used them (apicat, docs/api.md "CreatePlayer") |
| search id | `LOCAL` + 5 digits of CHash32(uuid + name); numeric id = CHash32(search id) | (d) |
| name | as sent | (d): the online server's name checks (client errors 10501..10503: the `CreatePlayer` result lambda shows a dialog for them) aren't known |
| tutorial | `tutorial_status` 0, `view_status` / `view_status2` 0 | (b): 0 = no tutorial step done |
| party sets | a `party_set` row per set 1..`party_set_max`, as the seed; the current party is set 1 | (a) the count; (d) |

After `CreatePlayer`, the client calls `CUIUtility::SettingForNewPlayer` and sends `Login` again (state 7). The second `Login` succeeds and sets `LoggedIn`.

<a id="tutorial-progress"></a>
### Tutorial progress
- **`Player.tutorial_status`** is the last tutorial step reached. **(b)**
  - `CParameterUtility::GetTutorialStatus` reads it at `CParameterManager+0xdd8`.
  - `IsTutorialClear` is `status >= CPhase_TutorialNext::LastMemId()`, which is 9.
- **Seeded (3.7.0) player:** `tutorial_status` = 9, the tutorial finished. **(b)** For the value; the 3.7.0 player had finished it.
- **Seeded player's `view_status` / `view_status2`:** all ones, so every UI tutorial counts as seen. **(d)** The save doesn't record them; a player at rank 87 has seen them all.
- **`UpdateTutorial(u64 status)`:** stores `tutorial_status`, and answers `Player`. **(b)** `CTutorialManager::ST_Net_Tutoflag` sends the step and `SetTutorialStatus`es it.
- **`UpdateView(kind, flags)`:** stores `view_status` (kind 0) or `view_status2`, and answers `Player`. **(b)** For the two sets: `CParameterUtility::AddTutorialViewStatus` picks the second set for ids with bits 0x3fc0. **(d)** That the flags replace the stored set.
  - `UpdateView` reaches the server through the FakeApiCaller route (`port/src/native/api/fakeapi.cpp`, `docs/client-changes.md` "`IApiCaller::UpdatePartySet`, `SetAssist` and `UpdateView`").

<a id="tutorial-battle"></a>
### Tutorial battle (`MissionStart` of `ms00_001`)
- A mission with `master_mission_npc` rows is fought by those NPCs instead of the player's party. The tutorial battle `ms00_001` has `tutorial_npc_role0001..3`: roles `role_cp0501_b01a_6011`, `role_cp0303_b01a_6033` and `role_cp0408_b01a_6024` through `master_npc_base_parameter`, at level 60.
  - **(a)** the rows.
  - **(c)** the tutorial battle was played with preset characters.
  - **(d)** that they're sent as `BattleParameter.PlayerCharacter`, with uids `0x7f000000` + order, the stats rules of a roster character (section 3) and no limit break.
  - **(b)** in the game (agent tutorial-dmg, 2026-09-29), each NPC's stats and weapon are then replaced by the client's own NPC status, `MasterMissionNpcModel::CalculateParameter(master_mission_npc id)` (`client_npc_status`, `port/src/native/api/server_client_status.cpp`). That is the function `tCharaData::CalcStatus` runs for an NPC `tCharaData` (`tCharaData::InitializeNPC`, used by the NPC helper list), i.e. `MasterNpcBaseParameterModel::GetCharacterParameter`: round(`master_role` stat × `master_character_common_parameter`[level] / 100) × the role's `master_rank` row, plus **the NPC's weapon `master_npc_base_parameter.master_item_id`** (`MasterItemModel`) with its factors, and the role's talents. `weapon_master_item_id` / `weapon_id` become that weapon (so the NPCs also hold their own weapon models). Before, the weapon was missing: e.g. Fidel's attack was 1,152 instead of 1,281 (see docs/notes.md "Tutorial battle damage").
  - **(b)** the NPCs' skills come from the same model (agent cleanups, 2026-09-30): `GetCharacterParameter` runs `MasterRoleModel::AddSkillInfo(role, level)`, which sets `skill1..3` = `master_role.master_skillN_id` when `master_skillN_open_level` ≤ the NPC's level (else 0) and `skill1..3_level` = 1 always. The server copies `skill1..3` / `skill1..3_level` from the result, and clears `skillN_label` for a closed skill. For `ms00_001` (level 60, every skill opens at 1) that is all three skills at level 1, the same values the roster rule gave. The result has to be read at the members' offsets: `CalculateParameter` returns it through `CPersonStatusInfo(CPersonStatusInfo&&)`, whose property map still points into the moved-from object in the function's (destroyed) stack frame, where the skills already read 0.
  - **(b) soa-server, and soa before the client's model is asked** (agent t1-tutorial-parity, 2026-10-01): the server computes the same NPC model from the master data, `rules::npc_status` (`server/src/master/npc_status.cpp`, `soaserver/npc_status.h`), following the 3.7.0 decompiles of `MasterNpcBaseParameterModel::GetCharacterParameter` / `GetParameter` and `MasterFactorModel::GetParameter` / `CheckFactorSeed` / `GetParam` (`work/decomp/tutorial-dmg-e.resolved.c`, `server-rules-factor.resolved.c`), in the client's single-precision steps:
    - base = rnd(`master_character_common_parameter`[level].stat × (u32 `master_role`.stat / 100)), then rnd(base × `master_rank`[role rank, limit break 0].stat / 100); rnd = ±0.5, truncated;
    - plus the NPC's weapon at level 1, limit break 0: attack / intelligence + `master_item_compose`[rarity].`status_up` × 1 (when non-zero), defence, hit, guard; no HP;
    - the factors: the role's talents 1-6 (`master_talent.master_factor_id`), its hidden factors 1-4, the weapon's factor1 (`factor1_limit_break` = 0) and factor2 / factor3 (limit break ≤ 0); of these the passive ones (`timing` 0) contribute their seeds 1-4 by `elment_type`: 16 (`ChangeParameter`, stat `param1` += `param2` %), 53 (`ExchangeParameter`, the largest `param3` per (from, to); the source stat loses it), 70 (`ChangeParameterFix`, flat), 77 (AP);
    - stat = rnd(stat × (100 + %) / 100) + flat, at least 1; skills as `AddSkillInfo` (open at the level, level 1); AP 100 and the elemental resistances 0 (`CPersonStatusInfo::Initialize`'s; the model leaves them, for every row). Before, soa-server's NPCs kept the roster rule's AP (100 + the favor AP bonus of the NPC's same role), which differed for players with favor and for event NPC helpers.
    - e.g. Fidel 1,152 + 110 (`item_W01Sw_21`) + 19 (rarity-5 `status_up`) = 1,281; the rod NPC's intelligence (1,434 + 120 + 19) × 1.30 (talent `factor0103`: seed 16077, intelligence +30 %) = 2,045.
    - Verified equal to the client's model (stats, AP, resistances, weapon, skills) for **every** `master_mission_npc` row (822, port test `server/npc-status-master`) and against the three tutorial NPCs' values (`server/npc-status-tutorial`, library). In soa the client's model then overwrites it with the same numbers (its log line says `unchanged`).
    - **(b) the 3.7.0 client battles with these values as sent** (agent f2-tutorial-stats, 2026-10-01): in `emulator_session.sh --new-player` the MissionEnd battle log's `PlayerCharacter` stats equal `MissionStartRes`'s `BattleParameter.PlayerCharacter` exactly, with the old roster numbers (a stale soa-server without this rule) and with the model's; the client doesn't recompute the NPCs. soa-server logs `MissionStart NPC <id>: master-data model applied|declined (attack N)` per NPC; test `server/npc-status-tutorial-missionstart` checks the MissionStart response.
    - Before this, soa-server (no client to ask) sent the roster rule: the 3.7.0 emulator's tutorial battle was fought with attack 1,152 / 1,069 and intelligence 762 / 1,434 (its MissionEnd battle log), damage 20-45 % lower than the port's, the battle about 30 % longer (emulator/README.md "Tutorial parity").
  - Without the row (or its role), the roster rule with the first weapon of the role's kind stays. **(d)**
- They're not added to the roster.

<a id="ui-tutorial-flags"></a>
### UI tutorial flags (`UpdateView(ViewFlagType kind, u64 flags)`)
- The screens' UI tutorials (the equipment screen's, for example) end with `CTutorialManager::ST_Net_Tutoflag`, which sends the word that `CParameterUtility::AddTutorialViewStatus` returns (the old word with the tutorial's bit set), with kind = bit index >> 6. **(b)**
- The server stores the word per kind (`player.view_status` / `view_status2`, the u64 word as its int64 bits, sent unsigned; `meta` keys until schema version 3; the unused `view_flags` table was dropped in schema version 2) and sends it as `Player.view_status` (kind 0) / `view_status2` (kind 1). The client reads them at CParameterManager+0xe08 / +0xe38 (`GetTutorialViewStatus`, `IsTutorialViewStatus`). **(b)** Any other kind is stored as `view_status2`. **(d)**
- A new account has seen no UI tutorial. **(d)** The seed save doesn't record them, although the seeded veteran player would have seen them all.
- The main tutorial's `UpdateTutorial` is the entry flow's ("Tutorial progress").

<a id="terms-and-name"></a>
### Terms and name
- **`UpdateKiyakuVersion(version)`:** stores `Player.kiyaku_version`, and answers `MasterKiyakuVersion` {`kiyaku_version` = `master_global.kiyaku_version` (20200319), `update_kiyaku_string` = ""}. **(a)** For the version; **(b)** for the shape (docs/api.md).
- **`UpdatePlayerName(name)`:** stores the name as sent. **(d)**

<a id="entry-register"></a>
### Player-visible (c) and (d) rules (entry flow)

| Rule | Label |
|---|---|
| New player: 300,000 free coins (`--start-coins`), level-1 starters, the name unchecked | (d) |
| Seeded player: every UI tutorial seen | (d) |

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Entry | `NoLoginStart` / `GetPlayer` without a player answer `data.Time` only; `UpdateView` stores any kind but 0 as `view_status2` | (d) | "Entry flow", "UI tutorial flags" |

<a id="missions"></a>
## Missions
Code: `server/src/api/missions/` (MissionStart, MissionEnd, the drop roll, `master_campaign`, the play state) and `server/src/rules/mission_rules.{h,cpp}`.

<a id="missions-rules"></a>
### 2. Missions

The mission tables share one shape: `master_mission` (story, 613), `master_event_mission` (1,803), `master_tower_mission` (450), `master_training_mission` (1), `master_world_map_mission` (1,376). MissionStart's first argument (`Common::MissionType`) selects the table (b: `CStageManager::CallMissionStart`, `CParameterUtility::FindMissionWithId(id, type)`).

<a id="opening-missions"></a>
#### 2.1 Opening missions
- A mission is visible when `visible_mission_id` is cleared (or null), and playable when `unlock_mission_id` is cleared (or null), inside `opened_at`..`closed_at` (a). E.g. `mf01_002` unlocks after `mc01_035`.
- Areas and planets: `master_area.master_planet_id`, `opened_at`/`closed_at`; event areas are gated by `master_event_term` (day ranges with times) and `master_event_weekly` (`week_id`) (a).
- World map (EP story, 3.x): `master_world_map_progress` rows give, per `episode_type_id` and `progress`, the `unlock_condition_mission_id` and the `unlock_mission_group_id` that opens next (a). The seed save's `world_map_progress` and last cell come from `work/Game-3.7.0.xml` (plan).
- The response is `GetMissionList` → `ActiveMissionList` / `ActiveEventMissionList` (docs/api.md). Per mission the server sends `{id, is_new, is_clear, is_last_play}`, per area `{mission_ct, is_new, is_last_play, is_start_bighunt}`, per planet `{area_ct, is_new, is_last_play}` (b: `CMissionElementInfo` / `CAreaInfo` / `CPlanetInfo::Initialize`); the rest of what the mission select shows (names, stamina, recommended level, drops) comes from master data (b: `CParameterUtility::tMissionData` reads the master row). `is_new` = visible and never played (d).

<a id="mission-start"></a>
#### 2.2 MissionStart
0. **Arguments** (b: `CStageManager::CallMissionStart`; `CPhase_Battle::Progress` → `CStageManager::Initialize(mission, u32, u64, u32, u64, type, u32)`, 3.7.0 decompile `work/decomp/campaign-370-c.resolved.c`; the `CParameterUI` fields 3.7.0's `CMissionMenu::NextPhase` fills, as `verdiff` reads it):
   1. mission type (`CParameterUI+0x140`), 2. master mission id (`+0x1a0`),
   3. u32 `CParameterUI+0x1b0` (the helper index + 1),
   4. u64 `+0x1b8` when the helper kind (`+0x1c0`) is 0 (one of the player's own characters? d),
   5. u32 `+0x1b8` when the kind is neither 0 nor 2 (an NPC helper id, d),
   6. u64 `+0x1b8` when the kind is 2 (a rental character),
   7. u32 from `+0x14c` of the mission-kind object for mission kinds 0 and 3, else 0.
   The party itself is not an argument: 3.7.0's menu stores the chosen party indices at `CParameterUI+0x150` / `+0x154` and the party sets are server state, so the server uses the player's current party (`Player.party_id`, set by the party screen through `UpdatePartySet` / `UpdateParty`) (d).
1. **Checks:** the mission is open (2.1); stamina `>=` cost, or the ticket item (`ticket_item_id` × `ticket_num`) is owned when the mission uses a ticket (a); the party is valid. On failure answer with the matching error code (a: `master_text` `error_message_text_<code>`, catalogued in docs/api.md "Appendix: server error codes": e.g. 10004 スタミナが不足しています, 10706 FOLが不足しています, 10404 対象ガチャは期限切れです, 10202 装備アイテム所持枠が不足しています, 10305 プレゼントは期限切れです). Both hosts report the code: soa's FakeApiCaller hooks answer the client's `IsSuccess` / `ErrorCode` with it, soa-server sends a ProtocolError (server/ARCHITECTURE.md "Transactions, refusals and errors"). As built, a locked mission isn't refused (d: "Server missions" below).
2. **Cost:** stamina `use_stamina` (after campaigns, 1), or the ticket; `vanish_item_id` × `vanish_num` is also consumed when set (a: columns; d: when exactly it's consumed — at start).
3. **Surprise enemy:** when `is_surprise_enemy` = 1, roll `surprise_rate` percent (e.g. 10.25) (a); `master_global.surprise_rate` = 10 is the default when the row's rate is null (d). Send `MissionParameter.is_surprise`; the stages with `is_surprise_enemy_stage` are then played, and the surprise drop set applies.
4. **Stages:** every `master_mission_stage` row of the mission, in `order_id`, sent as `MissionParameter.mission_stage` (a; docs/notes.md shows the exact element fields the client needs: `id`, `id_label`, `order_id`, `is_boss`, `stage_bgm` as CHash32, ...).
5. **Drops:** the online server may have rolled them here and sent them in `MissionParameter` (`mission_drop`, `mission_drop_rare`, `common_drop`, `battle_evaluation_drop`: a, the lists are in the MissionStart response schema), but no reader was found: the result screen reads MissionEnd's lists (2.3), and the mission detail's possible-drop list comes from master data (`CParameterUtility::tMissionDropItem::CollectMissionDrop`). **As built** the four lists are empty and MissionEnd rolls and grants the drops (d; `api/missions/drops.cpp`). See 2.4.
6. **Party status:** `BattleParameter.PlayerCharacter` = one `CPersonStatusInfo` per party slot, computed as in section 3.
7. **Enemy levels:** `add_enemy_level` / `overwrite_enemy_level` are 0 for normal missions (d); Sphere211 uses `master_sphere211_overwrite_enemy_level` (a).
8. **State:** remember the in-flight mission (for `GetPlayMission.is_play` and restart), the rolled drops and the stamina spent.

<a id="mission-end"></a>
#### 2.3 MissionEnd (win)
Input: mission id, a u32 flag, and the serialized battle log (`CBattleLogInfo`: `battle_result`, `mission_time`, `damage_total`, `hit_max`, kills, `rush_cooperate`, ...; docs/api.md).
- **The battle log comes with the request** (`Request::battle_log`, `soaserver/battle_log.h`): the `NetworkApiCaller::MissionEnd` request lambda (3.7.0 @015d68bc) serializes `CParameterManager+0x52d8` (`CBattleLogInfo`) as ASON and sends the bytes (b); soa-server takes them from the wire, and in-process the FakeApiCaller route runs the same client serializer (`docs/client-changes.md` "The battle log on the FakeApiCaller route"). Use its `mission_time` for `MissionEndResult.mission_time` and for evaluation (2.5) instead of a constant.
- **Which mission:** the request's id, else the play's (b); an id that is then 0 (no argument and no play) or in none of the mission tables (`master_mission`, `master_event_mission`, `master_world_map_mission`, `master_tower_mission`) **isn't answered** (not handled: nothing granted or recorded), as MissionStart doesn't answer an unknown mission. Until 2026-10-03 it was recorded as mission 0 cleared (found by S0 in the api-sweep corpus; type-8 achievements without a `target_id` then counted it). (b): the client has no MissionEnd row in its error-kind table (`CErrorHandlerWrap::ErrKind`, Ghidra 0x2cc5b70: 140 rows of fid, code, kind), and its handling table (ELF 0x2714360, read by `CErrorHandlerWrap::HndlType`) gives MissionEnd and Sphere211MissionEnd type 0, MissionStart and Sphere211MissionStart 2 (back to the title), everything else 1 (give up). (d): type 0 is read as the resend, which a refusal would only repeat, so no error code; what the online server answered isn't known. A valid id without a play is still answered (the `event-extras` corpus ends a mission whose start was refused). `Sphere211MissionEnd` without a cell (the request's, else the one playing) isn't answered either. Test `missions/end-unknown-mission`.
- **Player EXP:** the mission's `exp` (a). Level-ups as in 1.
- **FOL:** the mission's `fol` (a), times FOL campaigns if any apply to missions (d: no mission-FOL campaign type was identified; types 2/4/5 are compose / boost / evolution FOL discounts).
- **Character EXP:** every party member gets the mission's `pc_exp` (a), levelled with the character curve (5.1). Sent as `MissionResultCharacter` (map uid → before/after level/exp) and `add_characters_exp` (a: schema). Rental / support members get nothing (d).
- **Drops:** grant the rolled drops (2.4).
- **What the result screen lists** (b: `ResultUtility::GetRewardItemList`, reading `CParameterManager+0x600` = the `data` infos):
  - reward type 2, "first clear": `ClearPresentList.free_coin` (as content type 4) and its `item` / `character` / `stock_item` entries, each shown only when it matches a `master_mission_clear_present` row of the mission (so send exactly those rows, and only on the first clear);
  - reward type 0, drops: `DropList`, `CommonDropList`, `RareDropList` (`CMissionResultDropInfo`: `fol`, `free_coin`, `up_fol_rate`, `item[]`, `character[]`, `stock_item[]`, `AddStampList`);
  - reward type 4: the world-boss time-bonus list; the evaluation bonuses come from `BattleEvaluationResultInfoList` (b: `ResultUtility::GetEvaluationBonusList`);
  - items whose id is in the "new" id list are marked NEW.
  So the MissionStart drop lists (`MissionParameter.mission_drop` ...) are not what the result shows: MissionEnd must send the drops in `DropList` & co. (see 2.2 item 5).
- **First-clear presents:** on the **first** clear only, every `master_mission_clear_present` row of the mission (content, num) (a: rows; d: "first clear only" — the table has no repeat flag and the client names it clear present, `CParameterUtility::tMissionDropItem::CollectClearRresent`; `first_Present_View` flags missions that show it before the first clear). Sent in `ClearPresentList`.
- **Clear state:** mark cleared (unlocks follow from 2.1) and send the updated `ActiveMissionList`.
- **Favor:** each party member gains `master_favor_battle_effect.favor_up_point` for the row with `use_stamina` = the mission's stamina cost and `play_type` 0 (single play; 1 host, 2 guest) (a: e.g. 2 stamina → 12 points, 10 → 60, 20 → 119). See 8.
- **Mission character bonus:** `master_mission_character_bonus` (area or mission, `master_role_category_id`, `bonus_count`, `extra_bonus_*`) adds `bonus_count` extra lots and `extra_bonus_num` of `extra_bonus_content_id` per party member of that role category, capped by `master_global.max_character_bonus` = 2 and `max_character_extra_bonus` = 2 (a: columns and caps; d: that the cap is per party).
- **Battle evaluation** (event missions with an `evaluation_group_id`): see 2.5.

<a id="drops"></a>
#### 2.4 Drops
- **Lots:**
  - `lot_drop_count` lots from the mission's `master_mission_drop` rows with `is_fix_drop` = 0 / null and `is_surprise_enemy` = 0 / null, weighted by `rate_weigh` (a).
  - When the surprise enemy appeared: `lot_surprise_drop_count` lots from the rows with `is_surprise_enemy` = 1 (a).
  - `lot_common_drop_count` lots from `master_common_drop` rows of the mission's `common_drop_id` (a). E.g. `mf01_003`: 3 surprise lots, 3 common lots from `common_drop_01`.
  - Every row with `is_fix_drop` = 1 always drops (a: the column name; d: exact semantics).
  - Each lot grants the row's `content_type` / `content_id` / `num` (a).
- **`host_bonus`** rows only drop for the multiplayer host (a: column; irrelevant in single player; d: skip them).
- **Content type 98** (`gear_drop_1..4`) is a gear lottery: pick from `master_gear_lottery` rows of that category (by `rate_weigh`, filtered by weapon kind and rarity) (a: labels match `master_gear_lottery.category_id`; d: the filter).
- **Campaign drops:** while a `master_campaign` of type 0 (labels `Campaign_evo_*_prism`) runs, add `lot_drop_count_add` lots (a); `master_campaign_drop` rows of an active campaign drop by `rate_weigh` too (a: table; d: how many lots — one).
- **Rare drops** (`mission_drop_rare`, `RareDropList`): no column marks rarity; treat the lowest-weight row that dropped as the "rare" one only for display (d).
- **Favor event-drop bonus:** `master_favor_level.event_drop_bonus` (0,0,0,1,2 by favor level) extra event-drop lots in event missions for high-favor party members, limited to `favor_event_drop_bonus_limit` = 3 per day (a: columns; d: exact application).

<a id="battle-evaluation"></a>
#### 2.5 Battle evaluation (戦闘成績ボーナス)
- `master_battle_evaluation` (17 rows): per `evaluation_group_id` (the event mission's column) up to three evaluations, each with an `evaluation_type` and up to five `(rank_N_condition, rank_N_drop_count)` pairs, and a `master_mission_drop_id` naming the drop set (the `master_mission_drop` rows whose `master_mission_id` is that label, e.g. `me99_1113_evalution`) (a).
- **Types** (b: `CParameterUtility::tMissionData::GetEvaluationNumberString`, messages `uimsg_evaluation_condition1..6`): 1 total damage (`damage_total`), 2 enemies defeated, 3 rush-combo total damage (`rush_cooperate`), 4 highest hit count (`hit_max`), 5 highest single damage, 6 clear time (`mission_time`; lower is better, conditions such as 90000 / 120000 / 180000 are in ms = 1:30.00 / 2:00.00 / 3:00.00, shown as `%d:%02d.%02d`).
- **Rule:** for each evaluation, find the best rank whose condition the battle log meets (`>=`, or `<=` for type 6); draw `rank_N_drop_count` lots from its drop set by `rate_weigh`; send `BattleEvaluationResultInfoList` and the drops (a: data; d: that ranks are checked best-first and only the best one pays).
- The battle log values come from the MissionEnd request, so the server trusts the client (d).

<a id="failure-continue-restart"></a>
#### 2.6 Failure, continue, restart
- **MissionFailed / retire:** no rewards, stamina stays spent, the in-flight mission is cleared (c).
- **MissionContinue(bool)** (agent server-u-missions; `api/missions/play_state.cpp`): the defeat dialog of `CPauseMenu` (b: `OpenContinue` @01dacf90, `ReqeustContinue` @01dad704). The はい button sends 1 (b: its lambda @01daf13c), いいえ 0; `OpenContinue` sends 0 by itself, without the dialog, when the wallet doesn't cover the price or the mission's `is_continue` is 0 (b). With 1 the server takes `master_global.continue_use_coin` = 100 coins (a; b: `CParameterUtility::ContinueUseCoin`), free coins first, times the `magnification` (0.5) of a running continue campaign (`type_id` 9, labels `*_Continue_*` / `*_Cont_*`): the client asks `CUIUtility::GetDecMissionContinueCoin` (@01ef91c4) first for model type 99 (every mission type; `Campaign2021_spring_Continue`) and then for the mission's type, checking the area only for an event mission (type 1), and multiplies in float, truncated (b); the first matching row counts (b; d: the order is the master's). The windows are read on the event calendar, as the stamina campaigns (d). Only a mission whose table row has `is_continue` 1 continues (a: 4 story, 6 event, all 450 tower, 90 world-map rows and the simulator have 0); a continue with nothing in progress or for a mission without it is refused with 10403, coins short with 20000 (d: the codes; the client doesn't send it then). The play stays open across a continue: same mission, party, stamina and surprise roll; the battle ends with `MissionEnd` or `MissionFailed` as before (d). A 0 changes nothing. Answers the player state (`Wallet`) and `is_mission_continue` (b: the reply's keys, `docs/api.md`; `OnMissionContinueRes` applies them). In-process the FakeApiCaller's own method only returned a status; the port routes it to the server ("FakeApiCaller route" in `docs/client-changes.md`). Seen in the port (`port/scripts/simulator_continue_session.sh`, both hosts): the defeat dialog "紋章石100個を使用することで全員が復活できます" with the wallet 300000 → 299900 and a countdown (残り時間あと N); はい sends 1 and the party revives; the second dialog shows 299900 → 299800; いいえ asks 本当にリタイアしますか? and はい sends 0 then `MissionFailed`; a battle's time limit (制限時間に達しました。リタイアします) sends 0 then `MissionFailed` too. Tests `missions/continue`, `rules/missions`, the `missions` replay corpus; session `port/scripts/simulator_continue_session.sh` (a lost battle with a test party of one member at HP 10).
- **MissionLose()**: no 3.7.0 caller (b: its FunctionID appears only in the API tables and `NetworkApiCaller::MissionLose`; a lost battle sends `MissionFailed`, a simulator battle nothing). Answered as `MissionFailed`: the play ends, no rewards (d).
- **MissionRestart** / `MultiMissionRestart` (resume after a crash): the request has no arguments, and the client builds the resumed battle's four slots from the answer's `BattleParameter.PlayerCharacter` exactly as for MissionStart, so what the restarted battle fights with is the server's (b: `CStageManager::Progress`, Ghidra 0x13c7820, sends fid 0x1f96f310 / 0x8c788f39 instead of MissionStart when `CParameterUI::GetMissionRestart`; `CPartyManager::InitializePlayer(ulong*, bool*, int)`, 0x13a1f6c, `CreateCharacterInfoByAPI(0..3)`). The play record's mission, mission type, party set and helper start again, with nothing paid (no stamina, ticket, play count, or rental-day count for a rental clone) and the stored surprise roll (d: what the online server did isn't known). The helper is the recorded one (`play.helper_kind`: an own character stays `rental_sub_character_id` and a member, a rental clone member 4, an event mission's NPC helper member 4) (d). Until 2026-10-03 the restart sent the play's party id as the helper index and no helper ids, so the restarted battle lost its helper (a server bug found by PLAN-readability R15; fixed with schema version 7, which keeps the helper with the play). Nothing in progress: not handled. (`api/missions/play_state.cpp`; test `missions/restart-helper`, replay corpus `missions`.)

<a id="mission-start-core"></a>
### MissionStart as the server core built it
- **Arguments:** `(u32 mission type, u32 master mission id, u32, u64, u32, u64, u32)`, from `CStageManager::CallMissionStart`. With the port's `mission:` route the type was 0 or 0xffffffff and the other arguments 0.
- **Mission:** `MissionParameter` from `master_mission`, with `mission_stage` from `master_mission_stage` ordered by `order_id`. `stage_bgm` is sent as the CHash32 of the name. **(a)**; **(b)** for the hash (the client's `CMissionStageInfo` holds a uint).
- **Party:** the player's current party set (`Player.party_id`), else party 1. **(d)**
  - The third argument is the helper index + 1 (`CParameterUI+0x1b0`), not a party. **(b)** (2.2 above)
  - Helpers (support / rental characters) weren't added to the battle at first; now an own character, a rental clone or an event mission's NPC joins as member 4 ("Server missions", "Rental helpers").
- **Battle status** of each member (`BattleParameter.PlayerCharacter`, CPersonStatusInfo):
  - HP, attack, intelligence, defence, hit and guard, as the client's status screen computes them. **(b)** `PersonModel::CalculateParameter` → `tCharaData::CalcStatus` (section 3).
    - base = round_half_away(`master_role.<stat>` × `master_character_common_parameter[level].<stat>` / 100);
    - then × the `master_rank` row of (role rank, limit break) / 100, rounded half away again **(d: the second rounding)**;
    - at least 1.
  - The rush skill level is that `master_rank` row's `rush_level`. **(a)**
  - Not added yet: equipment, seeds, factors, talents, awakening and the favor AP bonus.
  - AP is 100. **(d)** There's no master column for it.
  - Element defences are 0. **(d)**
  - The weapon is the first `master_weapon` of the role's weapon kind. **(d)** Nothing is equipped yet.
  - Skills 1..3 are open when `master_skillN_open_level` ≤ level. **(a)** Skill level 1. **(d)**
  - The rush skill and gauge come from `master_role`. **(a)**
  - `next_exp`: see the character EXP curve below.
  - `favor_level`: see Favor below.
- **Drops:** no pre-rolled drop lists yet (`mission_drop` etc. are empty); the drops are rolled at `MissionEnd`. **(d)** The online server pre-rolled them (docs/api.md).
- Surprise enemies: rolled since "Server missions" (`MissionParameter.is_surprise`); at first `is_surprise` was always false.
- **Bookkeeping:** records the play (mission, party, members, time) and counts it in `mission.play_count`.

<a id="mission-end-core"></a>
### MissionEnd as the server core built it (`MissionEnd(u32 master mission id, u32)`)
- **Player EXP:** `master_mission.exp`. The level goes up through `master_player_level.next_exp`; EXP left over carries into the next level. **(a)** for the amounts; **(c)** for the carry-over.
- **Character EXP:** `master_mission.pc_exp` to every member of the play's party. **(a)**
  - The level cap is `master_role_level_max` for the role's rarity. **(a)** At the cap EXP stays 0. **(d)**
  - **Character EXP curve:** `next_exp(level)` = `(int)(master_role_boosted.exp_rate(rank, rarity) × master_character_common_parameter.next_exp(level) + 0.5)`. **(a)** for the tables; **(b)** for the formula: `PersonModel::GetNextLevelExp(float, rank, rarity)` computes exactly this.
- **FOL:** `master_mission.fol`, capped at `master_global.item_fol_max_num`. **(a)**
- **Drops:**
  - `lot_drop_count` lots from `master_mission_drop` (not the surprise-enemy rows), each picking one row by `rate_weigh`; rows with `is_fix_drop` always drop. **(a)** for the tables; **(d)** for how lots work.
  - Plus `lot_common_drop_count` lots from `master_common_drop` of the mission's `common_drop_id`. **(a)** / **(d)** as above.
  - Picks are with replacement: the same row can drop twice. **(d)**
- **Granting a content** (drops, presents): by `content_type`.
  - 1: a unique item with a fresh uid (`0x7d000000+`).
  - 2: a character; a duplicate raises limit break (see Gacha).
  - 3: FOL.
  - 4: free coins.
  - 5..10 and 16: stack items.

  **(a)** by example (docs/api.md "Content types"). Gear (15), gear lotteries (98), item sets (99), stamps, titles and deco aren't granted yet; they're logged. **(d)** (Since then gear and gear lotteries are granted by `api/items/gear.cpp`, titles (13) by `api/player/titles.cpp`.)
- **Response:** `DropList.item` / `.stock_item` / `.character` and `.fol`, `AddItem` for new unique items, `StockItem` (the whole stack list) when stack items changed, `MissionResultCharacter` (uid → before/after level and EXP), `MissionResultCharacterFavor`, `Player`, `Wallet`, `PresentBoxCount`.
- **Mission time** in `MissionEndResult` is the battle log's `mission_time` (ms). **(b)** `NetworkApiCaller::MissionEnd`'s request lambda serializes `CBattleLogInfo` (`CParameterManager+0x52d8`) at request time and sends it with the request (in-process the route runs the same serializer; 2.3).
- **First clear:** the `master_mission_clear_present` rows go to the present box, with reason 2. **(a)** for the rows; **(d)** for the reason code.
  - They're also listed in `ClearPresentList`: `free_coin`, and `item` / `character` / `stock_item` entries whose `id` is the content id. The result screen marks them 初回クリア. **(b)** `ResultUtility::GetRewardItemList`.
- **Favor:** per same_role_id, see 8 (`server/src/api/favor/favor.cpp`): `master_favor_battle_effect` by the play's stamina, levels from the cumulative `master_favor_level` thresholds capped by `master_favor_schedule`. The roster's `favor` column is no longer used.
- **Mission progress:** `cleared`, `clear_count` and `first_clear_at` are updated. Unlocks are recorded on the first clear ("Server missions", "MissionEnd drops"); the story campaign sends the updated `ActiveMissionList` (`api/campaign/`).
- **Level-up stamina:** see Stamina.

<a id="play-state"></a>
### Play state (`GetPlayMission`, `MissionFailed`, `MissionTalk`)
- `GetPlayMission`: `PlayMission.is_play` is 1 while a `MissionStart` hasn't been ended.
- `MissionFailed` (retire or lose): no rewards, and the stamina stays spent. **(c)** (docs/api.md) The play record ends, all of it: its party, mission type, surprise roll and helper. **(d)** So a later `MissionEnd` with no play in progress (it names its mission) reads type 0 (every mission table is tried), no surprise enemy and no party. (Until schema version 7 MissionFailed left `play_ext` behind, and such a MissionEnd read the failed start's type and surprise roll: a server bug found by PLAN-readability R15, fixed by the merge.)
- `MissionTalk` (a story-only mission): counts as cleared. **(d)**
- All three answer with `Player`, `Wallet` and `PlayMission` (`api/missions/play_state.cpp`; both hosts answer them through the server).

<a id="battle-simulator"></a>
### Battle simulator (`TrainingMissionStart(u32 mission, u32 helper index + 1, u64 own helper uid)`, agent server-u-missions)
- **What the client does (b):** キャラクター > バトルシミュレーター starts mission type 4; `CStageManager::CallMissionStart` (@013ca114) sends `TrainingMissionStart` with MissionStart's mission (+0x54), helper index + 1 (+0x18) and own helper uid (+0x20) (seen: `1642842982 1 0`), and its answer is read like MissionStart's. At the battle's end `CStageManager::Progress` sends neither `MissionEnd` nor `MissionFailed` for type 4, and シミュレーター終了 sends nothing; a loss lets `CPauseMenu::OpenContinue` send `MissionContinue(0)` (the simulator's `is_continue` is 0).
- **The rule:** the mission is the `master_training_mission` row (a: one, `simulator_mission01`, which `master_global.training_mission_id_label` names) with its `master_mission_stage` stages (a: `simulator_mission01_Stage01`); the party is MissionStart's (the player's current party, an own helper as member 4; d as there). No stamina, ticket or vanish item (a: the table has no `use_stamina` column and the row names neither). No play record and no play count (b: nothing would end it; d: so the next login's `GetPlayMission` offers no resume), no rewards (a: the row's `exp`, `pc_exp`, `fol` are 0; d: nothing is granted), and no modules' `MissionStartExtra` (d).
- **Before:** in-process the canned `port/fakeapi/responses/mission_start.msgp` (since retired) answered (another party, STAGE 1/2 of a story mission); over the wire an empty `{Time}`.
- Code: `server/src/api/missions/mission_start.cpp` (`training_mission_start`), `rules/mission_rules` (type 4's table). Tests: `missions/training-start`, the `missions` replay corpus; session `port/scripts/simulator_continue_session.sh`.

<a id="server-missions"></a>
### Server missions: refusals, MissionStart, drops
Code: `server/src/api/missions/` (the handlers) and `server/src/rules/mission_rules.{h,cpp}` (the pure rules, unit-tested). Tests: `rules/missions`, `missions/surprise-campaign-evaluation`, `missions/unlock-refusal`, `gacha/stepup-box`. Live: `port/scripts/restore_missions.sh`. This supersedes the "Not yet" list of the server-core notes (`docs/history/server-rules-history.md`) for these items and the server-core rows "No surprise enemies", "refusing a request without an error code".

<a id="refusals"></a>
#### Refusals and error codes
- A handler refuses a request by setting an error code. `server::handle` then rolls the request's state changes back and records the code for the fid; `server::error_code(fid)` reports it until that fid's next answer.
- The codes are `master_text` `error_message_text_<code>` (a):
  - 10004 スタミナが不足しています: MissionStart with stamina < cost;
  - 10206 アイテムの所持数エラー: MissionStart without the ticket / vanish items, BoxGacha without its event coins, GachaTicket without tickets (d: which code);
  - 20003 紋章石が不足しています: a draw without enough coins (b: the draw's answer lambda @01ad2bb8 takes 20003 to the gacha's coin shop, [Paid currency](#paid-currency); until then 20000, d);
  - 10403 不正なデータ処理です: a step-up step drawn out of order, an empty box, resetting a box that isn't resettable (d);
  - 10208 アイテムは使用できませんでした, the server's generic refusal (d), also for a request the state DB failed: a statement of it failed (a CHECK, foreign key or STRICT type, a misspelt column, `SQLITE_BUSY`), its transaction didn't begin, the DB refused its commit (a deferred foreign key), or its state couldn't be read (a uid counter that isn't a number). Nothing of the request is kept (`server/src/core/server.cpp` `handle_request`; tests `server/sql-failure-refuses-the-request`, `server/corrupt-uid-counter-refuses`). (d) which code: 10208 is ≥ 10000, so the client shows it in its one-button dialog (below); the texts サーバ内部エラー (2001-2011) are below 10000 and what `ErrKind` makes of them wasn't checked. A MissionEnd so refused is resent by the client (its handling type 0, [MissionEnd](#mission-end)), so a failure that repeats needs its statement fixed.
- **How the client shows it** (b: `work/decomp/server-missions-err-*.resolved.c`):
  - The network path hands the code to `ErrorHandler::Handle(fid, Status = code)` (`CApiNotify::OnProtocolError`).
  - `CErrorHandlerWrap`'s callback (`CallBackCore` → `ErrKind`) picks the kind: codes ≥ 10000 without a table row are kind 2. Kind 2 is `OpenDialogCatch`: a one-button dialog with `ErrMessage(code)` = `error_message_text_<code>`.
  - The OK button follows `HndlType(fid)`. `MissionStart` goes back to the title (the guest's own table at ELF 0x271d000). A gacha screen registered through `CErrorHandlerWrap::Auto` gets type 1 (give up), so the dialog just closes.
  - The port does the same on the FakeApiCaller route; see `docs/client-changes.md`.
  - 10404 and 10202 are kind 1 on the gacha fids (a throw callback, no dialog), so the server doesn't use them for draws.
- **Verified in game** (`port/scripts/restore_missions.sh`): the dialog reads スタミナが不足しています。エラー:10004 with a 閉じる button, which returns to the title. The same run shows `mf01_003`'s surprise drops on the result screen (no badges; the 初回クリア rewards badged), the unlock of `mf01_004` and a step-up chain advancing from step 1 to 3.
- **Before any client check:** whether 3.7.0's mission menu checked stamina itself before calling MissionStart isn't known. The port's `mission:` route doesn't, so the server's refusal is what the player sees (d).
- `--fail Method:code[,...]` (port test option) refuses those requests with the given code.

<a id="server-missions-start"></a>
#### MissionStart (server missions)
- **Mission table by type:** 0 `master_mission`, 1 `master_event_mission`, 3 `master_world_map_mission` (b: `FindMissionWithId(id, type)`; a: `master_campaign.master_mission_model_type` uses the same numbers). When the id isn't in that table, the other tables are tried (d: the port's `mission:` route sends type 0 for every mission).
- **Stamina campaigns:** a running `master_campaign` of type 1 (magnification 0.5) whose `master_mission_model_type` is the mission's type (or -2, every type), for the mission's area (or area 0, every area), multiplies the cost: rounded up, at least 1 (a: columns; b: `IsDecConsumeStamina`; d: the rounding).
  - **Campaign windows:** `opened_day opened_time` .. `closed_day closed_time` at the server's clock (a). `week_id` 7 means every day; it is the only value in the data (a). 0..6 is read as a weekday, Sunday 0, as `master_event_weekly` numbers them (d).
- **Checks:**
  - stamina ≥ cost, else refused with 10004 (a: the code);
  - `ticket_item_id` × `ticket_num` and `vanish_item_id` × `vanish_num` owned, else refused with 10206 (a: columns; d: the code). Both are consumed at the start (d), and the response carries `StockItem`.
  - A restart (`MissionRestart`) checks and pays nothing, and a rental clone's restart isn't another rental (d; 2.6).
  - A locked mission (its `unlock_mission_id` not cleared) is **not** refused (d): the server's clear record starts empty for a player seeded from the 3.7.0 save, which has no per-mission progress.
- **Surprise enemy:** when the row's `is_surprise_enemy` is 1, roll `surprise_rate` percent (e.g. `mf01_003` 10.25) (a), or `master_global.surprise_rate` = 10 when the row has none (d). The result goes in `MissionParameter.is_surprise` and is kept for MissionEnd. A restart replays it (d).
  - `--surprise` (port test option) makes every surprise-capable mission meet it.
  - All `master_mission_stage` rows are sent, with their `is_surprise_enemy_stage` flags, as before (d: the client picks the stages).
- **Helpers:** the third argument is the helper index + 1 (b); 0 is no helper. What the other arguments mean is inferred from 3.7.0's `CMissionMenu::NextPhase` (d; docs/api.md).
  - An own character (the u64 fourth argument), owned and not in the party, is appended to `BattleParameter.PlayerCharacter` with its status and named in `rental_sub_character_id` (d).
  - A rental character (the u64 sixth argument) and an NPC helper (the u32 fifth, a `master_npc` id) are recorded (`play.helper_kind` 2 / 3; `play_ext` until schema version 7). (Later: rental clones and event-mission NPC helpers join the battle; see "Rental helpers" and "NPC helpers (`master_mission_npc`)".)
  - `master_rental_bonus` (10 rows of `item_coin_37`, 300..750) is paid by the rental helpers' rule (d: the row whose id is the day's rental count; "Rental helpers").
- **State:** `play` keeps the mission, its type, the party set, the surprise roll and the helper (`helper_kind`, `helper_uid`, `npc_id`), and `play_member` the battle party in order, until MissionEnd, MissionFailed or the next start (one record since schema version 7; the campaign lots aren't kept: MissionEnd reads the campaigns again). **(d)**

<a id="mission-end-drops"></a>
#### MissionEnd drops
All lots pick one row by `rate_weigh`, with replacement (d, as before).
- **Normal:** `lot_drop_count` lots from the mission's `master_mission_drop` rows without `is_surprise_enemy` (a). Rows with `is_fix_drop` always drop (a: column; d: meaning).
- **`host_bonus` rows are skipped** (a: column; d: they're for the multiplayer host). server-core drew them.
- **Surprise enemy:** when it appeared, `lot_surprise_drop_count` lots from the rows with `is_surprise_enemy` = 1 (a). `mf01_003`: 3 lots.
- **Campaign drops:** for each running type-0 campaign (`Campaign_evo_*_prism`, 2017) that applies to the mission (model -2, its area):
  - `lot_drop_count_add` more normal lots (a);
  - one lot from its `master_campaign_drop` rows (a: rows; d: one lot).
  - The type-8 campaigns (`*_yuukou_*`, magnification 1.5 for event areas) multiply the battle favor, not the drops (d: see "Type-8 campaigns").
- **Character bonus:** each party member whose role category has a `master_mission_character_bonus` row for the mission, or for its area when the row names no mission, inside the row's `opened_at`..`closed_at`, adds (a):
  - `bonus_count` more normal lots;
  - `extra_bonus_num` of the extra content.

  The totals are capped by `master_global.max_character_bonus` = 2 and `max_character_extra_bonus` = 2 (a), per party (d).
- **Battle evaluation:** for event missions with an `evaluation_group_id`, each `master_battle_evaluation` row of the group is checked:
  - the battle log value for its type (b: `CBattleLogInfo` names): 1 `damage_total`, 3 `rush_cooperate`, 4 `hit_max`, 6 `mission_time` (met when ≤, and only when not 0);
  - types 2 (enemies defeated) and 5 (highest single damage) have no log field: every type's value comes first from the battle's evaluation array (`BattleEvaluationInfo` in the battle log, b; "Battle evaluation values"), the log field only when the array has none;
  - the best rank met pays `rank_N_drop_count` lots from the drop set, the `master_mission_drop` rows whose `master_mission_id_label` is the row's `master_mission_drop_id_label` (a; d: best rank first, only that one);
  - reached evaluations are listed in `BattleEvaluationResultInfoList` {`master_battle_evaluation_id`} (b: the info class).
- All drops are listed in `DropList` (d: no rare/surprise split for display).
- **`drop_type`** is `Common::MissionDropType`. The result screen turns it into a badge (b: `ResultUtility::GetRewardType` → `GetRewardBadgeIcon`, `work/decomp/server-missions-{rewardtype,badge}.resolved.c`):

  | drop_type | Badge |
  |---|---|
  | 0 | none |
  | 1 | host bonus (`hostb_badge`) |
  | 2 | beginner (`icon_wakaba`, 初心者) |
  | 3 | `kakin_badge` |
  | 4 | favor (`heartb_badge`) |
  | 5 | character bonus (`chara_badge`) |
  | 7 | `ds_plus_badge` |
  | 10 | defeat |
  | 11 | `god_badge` |

  - server-core sent common drops as 2, which showed them as 初心者. They are now 0 (d: the common set has no badge of its own).
  - Character-bonus drops are 5 (b).
  - Normal, surprise, campaign and evaluation drops are 0 (d). The surprise badge (reward type 5) has no `MissionDropType` that maps to it.
- The log line `MissionEnd mission N drops: surprise …, campaign …, character bonus …, evaluation …` shows each source.
- **Unlocks:** on the first clear, the missions of the same table whose `unlock_mission_id` is this mission are recorded in the state's `unlocks` table and logged (a). Example: `mf01_001` → `mc01_030`, `mf01_003` → `mf01_004`.
  - The menus learn about them through `ActiveMissionList`. Agent `campaign`'s server (`server/src/api/campaign/campaign.cpp`, branch `port/campaign`) builds that list from the same rule, adds it to every response and keeps its own clear record. When both are merged, the campaign code should read the server's `mission` / `unlocks` tables, so there's one clear record (d: integration left to the merge).
  - Mission ranks: the only per-mission rank data are the evaluation ranks above; the server keeps no per-mission rank (the never-written `mission.best_rank` was dropped in schema version 2) (d).

<a id="battle-evaluation-values"></a>
### Battle evaluation values (types 2 and 5; `server.cpp` `battle_evaluation_value`)
| Rule | Label |
|---|---|
| `CBattleLogInfo` has no field for evaluation types 2 (enemies defeated) or 5 (highest single damage). The values of all six types are in the battle's evaluation array: `CBattleLogModel::EndMission` appends one `CBattleEvaluationInfo` {type, value} per type to the TArray at CParameterManager+0x5988 (data +0x5990, count +0x59a0, stride 0x70; type u32 at +0x38, value u64 at +0x68), from the log model's counters (1 `AddDamageTotal` sum, 2 `EndBattle` defeated count, 3 rush-combo total, 4 hit max, 5 the largest single `AddDamageTotal`, 6 clear time in ms), and the MissionEnd request sends it as `BattleEvaluationInfo`. The server reads the last entry of each type; without one it falls back to the `CBattleLogInfo` property (types 1, 3, 4, 6). | (b) |
| So evaluation groups with type 2 (e.g. `me99_983`, 50 defeated) and type 5 (`me99_MemLast_07`, 50,000,000 damage) now pay their drops. The server trusts the client's values. | (a) conditions; trust (d) |

<a id="type-8-campaigns"></a>
### Type-8 campaigns (友好, `*_yuukou_*`, ×1.5; `server.cpp` MissionEnd, `favor.cpp`)
| Rule | Label |
|---|---|
| The client queries campaign type 8 only in `MissionUtility::UpdateEventAreaListCampaign`, and only while `CParameterUtility::IsOpenFavorabilityBattle()`: `GetCampaignSituationOnMission(8, …)` / `GetCampaignEvetMissionAreaList(8, …)` put the campaign badge and its value on the matching event area. It multiplies nothing itself. All 97 type-8 rows name an event area and model type 1. | (b), (a) |
| So a running type-8 campaign for the mission's area multiplies the **battle favor** MissionEnd grants (`master_favor_battle_effect.favor_up_point` × `magnification`, truncated). | favor as the target (d, from the favor-battle gate and the name 友好); truncation (d) |
| Other campaign types the client queries: 1 event-area stamina; 2, 3, 6 the item menu (weapon FOL, compose); 4, 7 `CPartyComposition::UpdateCampaign` (character FOL, strengthening); 5 awakening / evolution FOL (`ConsidereCampaignFol(…, 5, …)`). No client query of 0 or 9 was found. | (b) |

<a id="missions-register"></a>
### Player-visible (c) and (d) rules (missions)

From the server-missions work:

| Rule | Label |
|---|---|
| Refusal codes 10206 (items short), 20000 (coins short), 10403 (step order, empty box) | (d) (the texts are (a)) |
| Coins short is 20003 since paid currency (b: the gacha's draw answer opens the coin shop on it, [paid-currency](#paid-currency)) | (b) |
| A locked mission isn't refused | (d) |
| Surprise rate falls back to `master_global.surprise_rate` | (d) |
| Stamina campaign rounding up, minimum 1 | (d) |
| One campaign-drop lot per type-0 campaign; type-8 campaigns: see "Type-8 campaigns" (agent server-rules) | (d) |
| Character bonus capped per party | (d) |
| Evaluation by the battle's evaluation array, else the log field (types 2 and 5 have none); best rank only | (d) |
| Equipment at base stats; favor AP on top of 100 | (d) |
| Step-up: other steps refused; box: resettable any time | (d) |
| Chips per duplicate = chip × chip_rate / 100 | (d) |
| Common drops without a badge (server-core sent the beginner badge) | (d) |
| An own-character helper joins the battle list; an event mission's picked NPC joins as member 4, other NPC ids are only recorded; a rental helper replaces member 4 (see "Rental helpers" below); a restart doesn't restore the helper | (d) |
| MissionContinue: the play stays open across a continue (same mission, party, stamina, surprise roll); refused with 10403 for nothing in progress or a mission without `is_continue`, 20000 coins short; the first matching continue campaign in master order counts (agent server-u-missions) | (d) |
| MissionLose (no 3.7.0 caller) ends the play like MissionFailed | (d) |
| The battle simulator (TrainingMissionStart) fights with the current party, keeps no play record or play count and grants nothing | (d) |

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Missions | drops rolled at MissionStart and repeated at MissionEnd | (d) | the start response carries drop lists; no reader found |
| Missions | first-clear presents only on the first clear | (d) | table has no repeat flag |
| Missions | `is_fix_drop` rows always drop; `host_bonus` rows skipped | (d) | |
| Missions | rare-drop marking for display | (d) | |
| Missions | character bonus cap per party | (d) | |
| Missions | vanish item consumed at start | (d) | |
| Evaluation | best rank only, checked best-first | (d) | |

<a id="campaign"></a>
## Campaign progression (`server/src/api/campaign/campaign.cpp`)

| Rule | Source | Notes |
|---|---|---|
| A mission is listed when its `master_mission.unlock_mission_id` is cleared (or it has none) and its `visible_mission_id` (if any) is cleared. | (a) | The whole Episode 1 chain is in the data. |
| Missions, areas and planets are listed only inside their `opened_at` / `closed_at` windows. | (a) | Compared with the server clock (`--clock`) as text (`server/src/api/campaign/lists.cpp` `in_window`). The client compares them with its own clock, which follows the server's `data.Time` (Conventions); the Episode 1 windows contain it. |
| Only the story areas `planet00_area01` … `planet10_area01` take part; `Sample_*`, `planet98`, `planet99` are left out. | (d) | They look like debug and training content. |
| `ActiveMissionList` shapes: `Planet` by planet id, `Area` by planet id then area id, `Mission` by area id (arrays). | (b) | From the info classes (`InfoBaseNumberMap` / `InfoBaseArray` templates and each `Initialize`). The key of `Mission` isn't read by `GetMissionInfoWithIdW` (it searches every list); the area id is the natural key. |
| `is_clear` = cleared; `is_new` = listed and not cleared; `area_ct` / `mission_ct` = the number of listed areas / missions; `is_last_play` = the planet / area / mission of the last clear; `is_start_bighunt` = false. | (d) | The client shows "New" and "CLEAR" and the clear rate from these. |
| A `MissionEnd` clears the mission it names (its first argument, `MissionEndArgs`), else the one of the last accepted `MissionStart`. | (b) | `MissionEnd(mission id, select part id)` as `CStageManager` sends it; it is only sent for a won mission (a loss sends `MissionFailed` / `MissionLose`). |
| An `EndMissionTalk` (the end of a story scene; 3.7.0's `CEventScenario::Exit`) clears the story mission it names; `MissionTalk` likewise. | (b) | Story missions are `master_mission` / `master_world_map_mission` rows with a `talk_event_id`; other missions are ignored. |
| The clear of a `MissionEnd` / `MissionTalk` is written in the request's own transaction, once it is accepted (the campaign's `OnResponse` hook): a refused one (a handler's refusal, `--fail`, a failed statement) records none. `EndMissionTalk`, which is never refused, records its clear in the live server's own transaction before GetPlayMission's answer. | (d) | Until 2026-10-07 (CR2) the campaign recorded the clear in a transaction of its own before the request was handled, so a refused MissionEnd still counted. Tests `campaign/clear-in-the-request`, `campaign/refused-mission-end-records-no-clear`; replay corpus `campaign-refused`. |
| **World map (Episodes 2 and 3).** A group of `master_world_map_mission` rows opens when a `master_world_map_progress` row for it has `progress` ≤ the episode's progress and its `unlock_condition_mission_id` (if any) is cleared. | (a) | |
| The episode's progress is the highest `master_world_map_group_mission.progress` among story groups with a cleared mission (0 at the start); it is sent as `Player.world_map_progress` (Episode 2) / `world_map_progress_ep3`. | (d) | The story groups' progress values chain the progress rows in the data, so this reproduces the order; exactly when the 3.7.0 server advanced it (first mission of the group or all of them) isn't known. |
| World map missions also need their own `unlock_mission_id` / `visible_mission_id` cleared and their map, cell and date windows open. | (a) | |
| `ActiveWorldMapMissionList`: `WorldMap` {map id: area_ct = listed cells, is_new, is_last_play, opened_at, closed_at}, `WorldMapCellList` {map id: {cell id: {}}}, `WorldMapMission` {cell id: [id, is_new, is_clear, is_last_play, mission_group_id, difficulty, mission_type, scenario_library_id]}, for the episode `GetWorldMapInfoList` asked for. | (b) + (d) | Shapes from the info classes and `CWorldMapMenu::CollectMaster*FromInfo`; the counts and flags as for Episode 1. |
| `MissionStart`'s `MissionParameter`, rewards, stamina and play state come from the server core (above); the campaign adds only its progress keys to the responses. `Player` keys the campaign adds (`world_map_progress*`, `view_status*`) are merged into the server core's `Player`. | — | |
| A new player starts with nothing cleared. `--campaign-seed <mission label>` marks every mission on the unlock chain before it as cleared (a returning player). | (d) | The 3.7.0 save (`work/Game-3.7.0.xml`) doesn't record per-mission progress, only `BAS:PlanetOpen_*`, `BAS:LastPlayPlanet`, the last world map / cell and episode. |
| A returning player (seeded) has seen the menus' one-time tutorials: `Player.view_status` / `view_status2` all ones. | (d) | A new player keeps them clear, so the 3.7.0 tutorials show. |
| Progress persists in the state DB: `campaign_clear` (a row per cleared mission) and `campaign_last` (the last one played, a cleared mission), read from the DB for every answer (no copy in memory: test `campaign/progress-follows-the-state-db`). A seeded chain is saved with the first clear. | — | Separate from the server core's `mission` table (which also records clears). Before schema version 11 (PLAN-schema S12) it was a text file, `<data>/server_campaign.txt` (`clear <mission id>`, `last <mission id>`); opening such a data dir imports the file once and renames it `server_campaign.txt.migrated`. |
| Every response carries the current `ActiveMissionList`; the login data is delivered as a `GetPlayer` answer after the save's roster loads (the server core answers `GetPlayer` with the whole player). | (d) | Which 3.7.0 responses carried it isn't known; the client accepts it in any response. |

**Visible (c)/(d) rules:** the "New" marks and clear rates (is_new / counts) and the absence of tutorials for a seeded player.

<a id="events"></a>
## Events (`server/src/api/events/event_missions.cpp`, `events.h`)
Event missions (`master_event_area` / `_mission`, 168 areas, 1,803 missions) with the in-process server: the home's イベント button → `CPhase_Mission` with mission type 1 → `CEventMissionMenu` (the イベント / 素材 tabs, the area banners, the mission boards and lists) → the mission detail → the helper list → the party → the core `MissionStart` / `MissionEnd`, or a story scene (`CPhase_Event`) whose end clears the mission. The client code is unchanged; everything below is server data. Nothing about which events exist is written anywhere: the lists are computed from the master data, the player's state, the two clocks and the asset files present when the list is built.

<a id="two-clocks"></a>
### Two clocks
- **The client's clock** is `data.Time` (the server clock `now()`: the real time, or `--clock`). The client filters the event areas by it: (b) `MissionUtility::GetEventAreaList(now, 1, ...)` keeps a listed area only while a `master_event_term` row (opened_day opened_time .. closed_day closed_time) or a `master_event_weekly` row (week_id = the weekday, opened_time .. closed_time) covers `now`; `GetEventMissionList` and `CTimeUtility::IsEnableTime` do the same for a mission's `opened_at` / `closed_at`. The campaign badges compare `CampaignInfo.opened_at` / `closed_at` with it (b: `CUIUtility::GetCampaignSituation*`).
- **The event calendar** is `event_now()` (server.h; with `--clock` it is the clock, otherwise today mapped onto the latest service year with an event term that day, (d)).
- **The year shift** (d): `years = year(now) − year(event_now)` (6 on 2026-09-29 without `--clock`, 0 with it). The dated event tables of the client's master copy move by that many years (month, day and time stay; `ext::ClientMaster`, see `docs/client-changes.md`), and every window the server checks is moved the same way and compared with `now`, so both sides agree to the second. Tables moved: `master_event_term` (opened_day, closed_day), `master_event_area`, `master_event_mission`, `master_banner`, `master_banner_replace`, `master_world_boss`, `master_replace_resource` (opened_at, closed_at), `master_campaign` (opened_day, closed_day), `master_event_ranking_group` (opened_at, closed_at, ranking_closed_at, result_closed_at). Other modules with dated event content use `events::client_years()` / `shift_years()` / `window_open()` (events.h) and must not move these tables again.
- **Weekly slots keep the real weekday** (d): `master_event_weekly` has no dates, only `week_id` (0 = Sunday, as its labels say: `sunday_allday_01` …), so the daily material missions follow the weekday of the client's date, not the weekday the replayed day had in the service year.
- Feb 29 of a moved year that isn't a leap year normalises to Mar 1 on both sides (the client's `str2time_t` and the server's `mktime`).

<a id="what-is-listed"></a>
### What is listed (`ActiveEventMissionList`)
| Rule | Label | Evidence / note |
|---|---|---|
| **Shape:** `ActiveEventMissionList` {`EventArea`: {area id: `CAreaInfo` {`mission_ct`, `is_new`, `is_last_play`, `is_start_bighunt`}}, `EventMission`: {area id: [`CMissionElementInfo` {`id`, `is_new`, `is_clear`, `is_last_play`}]}}, keyed by the id as a string. | (b) | `CActiveEventMissionListInfo` (children `EventArea` = `InfoBaseNumberMap<CAreaInfo>` at CParameterManager+0x1d40, `EventMission` = `InfoBaseNumberMap<CMissionInfoList>` at +0x1d90); the classes' `Initialize` keys (`tools/info_fields_emu.py`). |
| **Delivery:** on every full-state player load (`Login`, `NoLoginStart`, `GetPlayer`) and on the answers of `MissionStart`, `MissionEnd`, `MissionFailed`, `MissionTalk`, `MissionRestart`, `GetPlayMission` (the story end), `UpdateHome`, `GetMissionList`. | (b) + (d) | (b): the event menu sends no request (`CPhase_Mission` asks `GetMissionList` only for the story campaign); (d): which responses the 3.7.0 server carried it on. |
| **An area is listed** when its own `opened_at` .. `closed_at` allows, a term or weekly slot covers the client's time **or starts within the next 24 hours**, and at least one of its missions is listed. | (a) + (b) + (d) | (d): the day ahead, so an area that opens later today (e.g. the 19:00 FOL mission) appears without a new request; the client hides it until its time. |
| **A mission is listed** when its window allows, its `unlock_mission_id` and `visible_mission_id` (if any) are cleared, and it is playable (below). | (a) | the same chain rule as the story campaign. |
| **Assets:** a battle mission is playable when every stage's map (`BG/<map>.asf/.aaf/.acf`, after the area's `master_replace_resource` res_type 4 replacement) and every enemy model (`Character/<master_person.asf>.asf` of the stage's `master_enemy_party` members) is present in the APKs, the install-time asset pack or `--download-dir`; a story mission when its script (`Script/<talk_event_id label>.msgp`) and talk file (`Scenario/<talk_message_file>.msgp`) are. Otherwise it isn't offered. | (b) + (d) | (b), seen on screen: a story whose script is missing leaves `CPhase_Event` black for good (event_ill_47 on 2020-09-29); the battle's map and model loads open the files directly and a missing one crashes (the direct-file loads, `docs/notes.md`). Checked through the port's asset lookup at run time and cached per mission; more downloaded files make more missions playable. |
| **A mission that isn't playable doesn't block** what it unlocks (its `unlock_mission_id` / `visible_mission_id` counts as met), so the rest of an event stays reachable. | (d) | |
| `is_clear`: the core's `mission` table (`MissionEnd`, `MissionTalk`, the story end). `is_new`: not cleared. Area `is_new`: an uncleared mission is listed. `mission_ct`: the number listed. `is_last_play`: the event mission (and its area) started or played last. | (d) | |
| `is_start_bighunt` = false unless a module sets it (`events::AreaExtra`, e.g. the world boss module). | (d) | |
| A ticket mission (`ticket_item_id`) is listed like any other; the detail shows the tickets held and `MissionStart` refuses with 10206 when short (the core's rule). | (a) + (b) | |
| **Missing banners and backgrounds:** left as they are. Seen on screen: an area whose `master_banner` image is missing shows an empty banner slot (still tappable, with its time bar); nothing crashes. | (b) | no stand-in images are substituted. |

<a id="other-data"></a>
### Other data
- **`CampaignInfo`** on the player loads (and `GetMissionList`): the `master_campaign` rows whose window (opened_day opened_time .. closed_day closed_time, moved by the year shift) covers the client's time and whose `week_id` is 7 or the client's weekday, as `CCampaignInfo` {`id`, `type_id`, `week_id`, `opened_at`, `closed_at` (client time), `magnification`, `lot_drop_count_add`, `master_area_id`(`_label`), `master_mission_model_type`} (a + b: the class's keys; the badges on the home's イベント button and the event banners, e.g. 友好度上昇率UP, come from it).
- **The core's campaigns** (stamina halving, extra lots, favor) use the event calendar instead of the clock (d), so they match what `CampaignInfo` shows.
- **`EventMaintenanceInfoMap`** = {} on the player loads (d): no event is under maintenance.
- **`FooterMissionInfo.is_open_event_mission`** = 1 (d, `api/player/home_footer.cpp`).

<a id="story-missions"></a>
### Story missions (`talk_event_id`, no stages)
- The detail has 閉じる / ストーリー開始; the scene plays in `CPhase_Event`; at its end the client's `EndMissionTalk` (3.7.0's `CEventScenario::Exit`; in-process through the FakeApiCaller route, `docs/client-changes.md` "`IApiCaller::EndMissionTalk`") reaches `events::end_mission_talk`: the mission is recorded as cleared (play and clear counts), becomes the last played, and on the first clear its `master_mission_clear_present` rows (none in the 3.7.0 data for event stories) go to the present box (a + d). The answer (`GetPlayMission`) carries the new list, so the board shows CLEAR and the next node New.
- 3.7.0 also sends `MissionTalk` at the start of a story (`CMissionMenu::Setup` lambda #34; seen in the 3.7.0 session logs). The event clear is recorded at the scene's end (`EndMissionTalk`), which is enough for the chain (d).

<a id="npc-helpers"></a>
### NPC helpers (`master_mission_npc`)
- (b) `CParameterUtility::CreateRentalListAuto(type, mission)`: when a mission has `master_mission_npc` rows, the helper list (レンタルキャラクター) shows exactly those NPCs instead of the rental list (seen on screen: 斬鬼のネル / 鬼炎のアルベル for me99_1027). So they are **helper candidates**, not the party: the player's party fights, and the NPC the player picks (`MissionStart`'s NPC argument, the `master_npc_base_parameter` id; the `master_mission_npc` id is accepted too) joins as the 4th member, with the stats rules of a roster character of the row's role and level (d, as the tutorial's NPCs). No pick (選択しない): no NPC.
- (b) In the game (agent a4-helpers), the picked NPC's stats, weapon and skills are then replaced by the client's own NPC status, as for the tutorial's NPCs (see "Tutorial battle"): `MasterMissionNpcModel::CalculateParameter(master_mission_npc id)` (`client_npc_status`, `port/src/native/api/server_client_status.cpp`), the function `tCharaData::CalcStatus` runs for the helper list's NPC `tCharaData` (`tCharaData::InitializeNPC`). So the helper fights with its weapon `master_npc_base_parameter.master_item_id` (`weapon_master_item_id` / `weapon_id`), its factors and talents, exactly as the helper list shows it. Before, the weapon was missing (e.g. master_mission_npc 1255989 at level 22: attack 478 without, 982 with the weapon). Test `server/event-npc-helper-status`.
- The tutorial battle (`ms00_001`, the only non-event mission with NPC rows) keeps its preset NPC party (`CPhase_TutorialNext` builds it from the same rows).

<a id="events-tests"></a>
### Tests and session
- Unit tests `events/shift`, `-lists`, `-weekly`, `-asset-gating`, `-clear-chain`, `-campaign-info`, `-npc-helper` (`server/src/api/events/event_missions_tests.cpp`): everything derived from the master data at run time; assets through an injected predicate.
- `port/scripts/events_session.sh <soa> <out> <scratch> [clock]`: home → イベント → 素材 → a daily mission → battle → result → CLEAR; with a clock, also a story event (story → CLEAR → the unlocked battle with an NPC helper → result).

<a id="enabling-events"></a>
### Enabling events by keyword (`--enable-events`; `server/src/api/events/enable_events.{h,cpp}`)
A port option, off by default (the user's request: "enable the summer events/banners, if/when possible"). With `--enable-events`, today's replayed calendar stays as it is and **in addition** every event area and every gacha whose name matches a keyword list is open all year, as far as its assets allow. `--event-keywords "a,b,!c"` (`--event-keywords`) replaces the list; the default is the summer events. Summer is only the default example: any list works (e.g. `--event-keywords "花嫁"` for the wedding events).

| Rule | Label |
|---|---|
| What matches: an area (`master_event_area`) or gacha (`master_gacha`) whose name, `master_text.text_value` of its `name_message_id`, contains at least one plain keyword and none of the `!`-prefixed ones. Nothing about which events exist is written in the code | (a) the names; (d) the method |
| The default list `水着,夏,サマー,!福袋` (swimsuit, summer, "summer"; not the New Year lucky-bag ticket gacha "2018年福袋限定チケットガチャ(花嫁/水着/ハロウィンのみ)", which only names 水着 among its line-up). In the 3.7.0 master it matches **7 event areas**: `event_sum_22` 水着イベント前半, `event_sum_23` 水着イベント後半, `event_sum_49` 【180726】水着前半イベント, `event_sum_50` 【180809】水着後半イベント, `event_sww2019_75` / `_76` 水着イベント2019前半 / 後半, `event_sww2020_93` 水着イベント2020 (夏 and サマー match no area name), and **185 gachas**: the 水着 / 復刻水着2017–2020 step-ups and pick-ups, 水着1–3ピックアップ武器ガチャ, 常夏 / 真夏 character pick-ups, サマーステップアップキャラガチャ, and 30 event box gachas (2020 水着イベント；星の海と夢の渚, サマー・リゾート・スクランブル SIDE:A/B, 常夏イベント) | (a) the names; (d) the choice of keywords |
| A gacha sharing its `banner_id` with a matching gacha counts too (the steps of a step-up and the single / 10-draw variants of one banner share it); the exclusions still apply | (a) the shared banner; (d) |
| An enabled area is listed whatever its `master_event_term` / `master_event_weekly` rows and its own dated window say, and its missions whatever their `opened_at` / `closed_at` say; everything else of "Events" applies unchanged (unlock chains, clears, New, last play) | (d) the user's request |
| **Assets permitting:** a mission is still offered only when `events::mission_playable` (its maps, enemy models, story files present); an area with no playable mission isn't listed. With the download (`--download-dir work/SOA-3.7.0-canonical-data.zip`) all 7 default areas are playable; without the download none is | (d), as "Events" |
| **Gachas:** an enabled gacha is in `GetGachaInData` whatever its `opened_at` / `closed_at`, with the hash window `2016-01-01 00:00:00`..`2037-12-31 23:59:59` (the window its master row gets in the client's copy) | (b) `CGacha::IsEnableHash` needs both windows; (d) |
| **Banner images:** an enabled gacha whose list banner (`master_banner.image` of its `banner_id`, `Image/<image>.aif`) isn't present is **not** opened: the client does cope with a missing banner (no crash), but the list row is an empty frame with only the date, which nobody can pick sensibly (seen on screen). Box gachas too since they are listed (agent stepup-list: the イベントガチャ tab showed empty "ボックス 1" frames); the same check keeps box series without a banner image out of `BoxGachaList` with or without the option. The stand-in overlay (the in-process server's `standin-assets`, port/README.md "Stand-in assets") adds made-up banners for `gacha_pickup_role_0054` / `_0056` (Summer '17) and `gacha_pickup_role_0283` (the NieR:Automata rerun; `--event-keywords NieR` opens exactly that gacha, `emulator/scripts/nier_demo.sh`); soa sees them through its AssetManager (`--standin-assets`), soa-server through its asset index, which holds the download dir and the stand-ins the CDN serves (`cdn::asset_index_from_config`; `--standin-assets off` leaves them out, and those gachas stay shut; test `events/enable-standin-banners`). The check is the same file lookup; nothing names those gachas | (b) on screen; (d) the choice |
| The open window: `2016-01-01`..`2037-12-31 23:59:59` (the client prints "2037/12/31(木)23:59まで"). It ends before 2038 so no 32-bit time or remaining-seconds value overflows | (d) |
| Draws, rates, pools, step-ups and prices are the gacha's own (4.x); the pools' release dates are all before the 2026 clock | (a)+(d) as 4.x |
| **Exchange shops** (アイテム交換所, `master_exchange_shop`): a shop belongs to the enabled events through its currency: the `ex_item_id` of its contents is a coin that the enabled areas' missions drop or give on clear (`master_mission_drop` / `master_mission_clear_present` of their `master_event_mission` rows) and that nothing else gives (no other event area's missions, no story / tower / world-map / training mission, no `master_common_drop` / `master_campaign_drop` row; drop rows of test missions that exist in no mission table are ignored). A shared currency such as the revival coins (復刻コイン, 復刻コイン【滅】: ~90 areas each) links nothing. Nothing names a shop or an event in the code | (a) the drop tables and the shops' currencies; (d) "only these events give it" as the link |
| A coin's shop was re-issued with each rerun under a new id (e.g. コーダル【朱】: `exchange_coral_coin_shop` 2018, `_200722_shop` 2020, `exchange_first_coral_coin_shop` 2021); only the one with the latest `opened_at` (the last run's line-up) is opened, so the list doesn't show the same shop three times | (a) the windows; (d) the choice |
| With the default keywords: **9 shops** (コーダル【朱】 / 【蒼】, マーレゼリアコイン【青】, 海神の真珠, 竜人コイン, ドリンクコースター, 切り分けたスイカ, 人魚バーニィシール, 真夏の朱花 exchanges). An enabled shop is in `ExchangeShopExCount` and `ExshopExchange` accepts its rows whatever its window and the rows' `opened_at` say; prices, limits and contents are the shop's own ("Growth and economy") | (a) + (d) |
| The client's master copy: see `docs/client-changes.md` "Enabled events opened in the client's master copy" | |

The step-ups and the イベントガチャ tab (box gachas) are listed since agent stepup-list ("Step-up and box gacha lists" below: `StepUpGacha` / `BoxGachaList` must be maps, not arrays); the exchange shops since agent a2-shops (on screen, `--enable-events --download-dir work/SOA-3.7.0-canonical-data.zip`: ショップ → アイテム交換所 → イベント lists the summer coin shops (新真夏の朱花 / 新人魚バーニィシール / 新切り分けたスイカ / 新ドリンクコースター / 新海神の真珠 …, "あと99日") next to the calendar's own; 新真夏の朱花交換所 lists its line-up, and one ゴールドハンマー for 300 真夏の朱花 exchanged: 1000 → 700 held, 在庫 10 → 9). Unit tests: `events/enable-keywords`, `events/enable-areas`, `events/enable-exchange-shops` (`server/src/api/events/enable_events_tests.cpp`).

<a id="event-extras"></a>
### Event extras (`server/src/api/events/ranking.cpp`, `api/events/world_boss.cpp`, `api/events/favor_drop.cpp`, `api/shop/shop.cpp`)
Event rankings, world bosses and big hunts, time bonuses, the favor event drop bonus and the exchange shops on the event calendar. The entry into event areas (`ActiveEventMissionList`, the events button, the event tables' date shift in the client's master) is agent `events-core`'s (`api/events/event_missions.cpp`); these modules move the event tables' dates by the same whole years (`events::client_years` / `window_open`) and compare them with the clock, so they agree with the client's copy that module moves. The six requests reach the server through the FakeApiCaller routing in `docs/client-changes.md` ("Event ranking and world-boss requests on the FakeApiCaller route"). MissionStart / MissionEnd additions go through two hooks in `ext.h`: `ext::MissionStartExtra` and `ext::MissionResultExtra` (with `ext::MissionInfo`: the mission, its table / type / area, the party, the battle's `mission_time` and evaluation values; `ext::add_drop` adds a granted drop to `DropList` / `AddItem` / `StockItem`). Unit tests: `events/exchange-shop-calendar`, `events/ranking`, `events/worldboss-waves`, `events/worldboss-time-bonus`, `events/favor-drop` (`server/src/api/events/event_extras_tests.cpp`; events and missions picked from the master by their columns).

<a id="event-rankings"></a>
#### Event rankings (イベントランキング)
Client flow (b): the event menu (`CEventMissionMenu::Initialize`) sends `CheckEventRankingResult`; when its `CheckEventRankingResultInfo.master_event_ranking_group_id` is non-zero, `Progress` sends `ReceiveEventRankingResult` and opens the result dialog (`CEventRankingResult`). The ranking screen (`CEventRanking`) sends `GetEventRankingInfo(group id)` for the group running by its clock (and the previous one from the 報酬 tab) and `ClearNewEventRanking(ranking ids)` on close; `GetPlayerDetailInfo(player id)` only from another entrant's row.

Response keys (b: the classes' `Initialize`): `GetEventRankingResultInfo` {`EventRankingInfoListMap` / `EventRankingTopInfoListMap`: {ranking id: [EventRankingInfo {player_id, rank, rank_ui, score (u64), party_player_id1..4, party_player_id1..4_valid, party_role_id1..4, battle_id, created_at}]}, `EventRankingPlayerInfoMap` {player id: {name}}}; `CheckEventRankingResultInfo` {master_event_ranking_group_id, RankingResultInfoList [{master_event_ranking_id, score, rank}]}; `UpdatedEventRankingIdList` [ranking id] (non-empty lights the ranking badge, `MissionUtility::IsUpdateEventRanking`).

| Rule | Label | Notes |
|---|---|---|
| A ranking (`master_event_ranking`) ranks the wins of its `master_event_mission_id` while its group (`master_event_ranking_group`) runs, `opened_at` ≤ clock ≤ `closed_at` (the dates moved by the calendar's whole years, as in the client's copy). | (a) | Test `events/ranking`. |
| The score is the battle's evaluation value of the ranking's `ranking_type`: 1 total damage, 2 enemies defeated, 3 rush-combo damage, 4 highest hit count, 5 highest single damage, 6 clear time (ms). Higher is better, except type 6: lower, and 0 (not won) is no score. | (b) | `uimsg_evaluation_condition<n>` / `CParameterUtility::tMissionData::GetEvaluationNumberString`; the values are the `CBattleEvaluationInfo` the battle log records (types 1..6, the same numbering). |
| **The player is the only entrant**: rank 1 in every ranking played; the best score is kept with the party of that win (its roles; every slot the player's own, `_valid` set). No play, no row. | (d) | The service's other players are gone. `EventRankingTopInfoListMap` repeats the same row. |
| A win that improves a score sends `UpdatedEventRankingIdList` [ranking id]; `ClearNewEventRanking` answers it empty. | (b) + (d) | (b) the badge; (d) when to light it. |
| The result is due from `ranking_closed_at` to `result_closed_at` (moved dates, clock), once, for the latest group with a score not yet received; otherwise `CheckEventRankingResultInfo` names group 0 (always sent: the client keeps the last one). | (a) + (d) | (a) the dates; (d) once, only when played. |
| The reward of a ranking: the `master_event_ranking_reward` row of `ranking_reward_group_id` = the ranking's id with the smallest `required_ranking` ≥ the rank (rank 1: the top tier), granted by `ReceiveEventRankingResult` (item sets, content type 99, expanded through `master_item_set`), `AddItem` / `StockItem`. | (a) + (b) | (b) `CEventRankingResult::Initialize` shows tier i for ranks (required_{i-1}, required_i]. Some legacy reward rows (e.g. `EvRank02_01b`) name no ranking and are never paid. |
| `GetPlayerDetailInfo(player id)` answers `SearchResult` {player id: CFollowInfo {order 1, player: CFollowPlayerInfo (id, name, level of the player), pc: CFollowPersonInfo (the home character, else the highest-level one, as the rental entries build it)}} for any id: the player is the only entrant. | (b) the dialog reads the first `SearchResult` entry (`CEventRanking::OpenDetailDialog` → `CParameterUtility::CreateSearchFriendData` → `tCharaData::InitializeFollow`, CParameterManager+0x6490); (d) the character shown | (b) The rows' touch handlers skip the player's own row and own party slots (they compare the entry's player id with `PlayerInfo()+0x60`), so the client doesn't send it with one entrant; the answer is there for any other caller. Test `events/player-detail`. |

All ranking groups in the 3.7.0 data belong to `event_god_86`, whose assets are incomplete in the download; the rankings are therefore tested through unit tests only.

<a id="world-bosses"></a>
#### World bosses and big hunts (ワールドボス / 大討伐)
Client flow (b): an event area with `event_type` 1 names a world boss (`event_id` → `master_world_boss`). While the boss's window is open by the client clock, a fresh board open (`CEventMissionBoard::Progress`) sends `GetWorldBossInfo(event area id)` and shows the boss plate (`SetupWorldBossPlate`): the wave (`CWorldBossInfo.wave`, its `master_world_boss_wave` reward), three gauges `num1..3` of the target items (`master_item_id1..3`) against `CT_WorldBossInfo.next_required_num`, and "+N" boxes `add_item1..3_num`. Each entry of `CWorldBossPlayerInfoList` opens a wave-clear dialog (no request, no grant). `start_bigHunt_area_id` (any response) marks the area of a running big hunt: its `is_bighunt` missions are listed (`MissionUtility::GetEventMissionList`, no time check) and the board counts down to `CT_WorldBossInfo.bighunt_closed_at`; the cut-in plays when `CWorldBossPlayerInfo.is_new_open` is set. The client reads nothing of `fast/base/slow_required_num`, `estimated_clear_time`, `wave_calc_length`, `bighunt_time`, `bonus_rate`, `bonus_add_slot_max`: those are server rules.

| Rule | Label | Notes |
|---|---|---|
| A boss is served while its `master_world_boss` window, moved by the calendar's whole years, covers the clock; otherwise `GetWorldBossInfo` answers `world_boss_id` 0 (a plain event board). | (a) + (d) | Test `events/worldboss-waves`. |
| **Single player:** the community totals are the player's own. A wave needs, of each of the three target items, the master's requirement scaled so the boss's first wave needs 1,500 (`kFirstWave`); later waves keep the master's proportion to the first. | (d) | The master's numbers were sized for the whole player base (hotspring wave 1: 3,100,000). The event missions drop 150..650 target coins per lot, so a wave takes a handful of wins per item. |
| The requirement of the next wave: `fast_required_num` when the previous wave cleared within `fast_rate` % of its `estimated_clear_time` (minutes), `slow_required_num` beyond `slow_rate` %, else `base_required_num`. | (a) + (d) | (d) that reading of the columns, on the player's own clear times. |
| The target items a win brings (its `DropList` stack items and time bonuses) fill the gauges; during a big hunt they count `bonus_rate` % more. `add_item1..3_num` is the last win's share. | (a) + (d) | |
| A wave whose three gauges are full clears: its `master_world_boss_wave` content goes to the present box (text `present_message_id`), the clear is listed once in the next `GetWorldBossInfo`'s `CWorldBossPlayerInfoList` (always sent: the client keeps the map), the next wave starts from empty gauges (no carry-over); past the last row the last wave stays full. | (a) + (d) | (b) the dialog grants nothing, so a present. |
| **Big hunt:** a wave clear starts one for `bighunt_time` minutes in the boss's area (`start_bigHunt_area_id`, sent with every player load, MissionStart, MissionEnd and `GetWorldBossInfo`; 0 when none); the cut-in flag `is_new_open` is sent once; MissionStart sends it false (back on the board the client reuses its cached data). | (a) + (d) | (a) the duration; (d) what starts it. |
| `CAreaInfo.is_start_bighunt` of the big hunt's area is set (`events::AreaExtra`). | (d) | The client reads `start_bigHunt_area_id`; kept consistent. |
| `is_received` false, `is_notified` true in `CWorldBossPlayerInfo`. | (d) | (b) the detail dialog adds `is_received` to the wave for the rows it lists. |

<a id="time-bonus"></a>
#### Time bonus (タイムボーナス)
| Rule | Label | Notes |
|---|---|---|
| An event mission with `time_bonus_type_id` pays, on a win, every `master_time_bonus` row of that type whose `time` (seconds) the battle's `mission_time` (ms) is within; granted and listed in `WorldBossMissionTimeBonusDropItemInfoList` [{id, content_type, num}]. | (a) + (b) + (d) | (b) the result screen shows that list as reward type 4 (`ds_time_badge`), the client computes nothing; `CWorldBossConditionDialog` prints `time` as %u:%02u. (d) cumulative rows (every row met, not only the best). Test `events/worldboss-time-bonus`. |

<a id="favor-event-drop-bonus"></a>
#### Favor event drop bonus (好感度イベントドロップ)
(b) The client never computes it: the party screens show a per-character drop icon (3.7.0 `CParameterUtility::GetFavorDropIconImageName`: favor level ≥ 4, `added_event_drop_at` before the day's reset at `login_bonus_reset_hour`, `RemainingEventDropBonusCountByFavor` non-zero), the result screen badges `drop_type` 4 drops with a heart, and `MissionEnd`'s `MissionResultCharacterFavor[same_role_id].added_event_drop_at` is copied into the favor map. `MissionParameter.is_event_drop_by_favor` is read by nothing.

| Rule | Label | Notes |
|---|---|---|
| At MissionStart of a `master_event_mission`, the party's own characters (slot order) whose favor level has an `event_drop_bonus` (`master_favor_level`: 1 at level 4, 2 at level 5) and whose bonus isn't spent today take part, up to the day's remaining uses; `is_event_drop_by_favor` says whether any does. A restart keeps the set. | (a) + (d) | (d) event missions only (like the Galaxy Pass's extra event slot, `subscmsg_gpass_drop_manual`); the limit counts characters. Test `events/favor-drop`. |
| On the win, each of them adds `event_drop_bonus` lots from the mission's own drop rows (non-fixed, non-surprise, no host bonus; by `rate_weigh`) as `drop_type` 4, and its bonus is spent: `added_event_drop_at` = now (sent in its `MissionResultCharacterFavor` entry). | (d) | |
| `RemainingEventDropBonusCountByFavor` = `master_global.favor_event_drop_bonus_limit` (3) less the characters spent since the day's reset (`login_bonus_reset_hour`), on every player load and after a bonus win. | (a) + (d) | Replaces the constant 3 of agent restore-favor. |

<a id="event-exchange-shops"></a>
#### Exchange shops on the event calendar
| Rule | Label | Notes |
|---|---|---|
| An exchange shop (`master_exchange_shop`) is listed (`ExchangeShopExCount`) and exchanges when the clock is inside its window **or** its window moved by the calendar's whole years (`events::client_years`); a contents row's `opened_at` likewise. | (a) + (d) | The event coin shops (e.g. an event's `*_coin_shop`) open with their event. Test `events/exchange-shop-calendar`. |
| The client's master copy moves only the rows that move opens (their contents' `opened_at` too); open-ended rows stay (moved forward they would open late). Agent events-core moves every row of the event tables. | (d) | `docs/client-changes.md` "Event exchange shops moved in the client's master copy". With `--clock` the calendar is the clock and nothing moves. |

<a id="heat-up"></a>
#### Heat-up (ヒートアップ)
Client-only (b): the heat-up tactics order (`COrderGaugeManager::FinishHeatUp` / `FixHeatUpBonus`, `CRushComboManager::GetHeatUpBonus`) reads `master_heat_up_bonus` from the client's master; the server only receives `order_count_heat_up` in the battle log and applies no rule.

<a id="other-modes"></a>
### 11. Other modes (outline)
- **Deep space:** implemented, see [Deep space](#deepspace).
- **Sphere 211:** implemented, see [Sphere 211](#sphere211).
- **Tower:** `master_tower_area` / `_mission`, 3 tries a day (`Tower_Challenge_Count`) (a; d: daily).
- **World boss:** `master_world_boss`, `_wave`, `master_time_bonus` (a).
- **Event ranking:** `master_event_ranking*`; single player → the player is rank 1 (d).
- **Event missions:** implemented, see [Events](#events).
- **Multiplayer, follows, neighbours:** empty lists; rental characters from `master_rental_bonus` / NPCs (d).

<a id="events-register"></a>
### Player-visible (c) and (d) rules (events)

| Rule | Label |
|---|---|
| Past events replay on the service calendar, moved into today's year | (d) |
| Daily material missions follow today's real weekday | (d) |
| Missions without their files are not offered; they don't block what they unlock | (d) |
| The event list is sent a day ahead | (d) |
| New = not cleared | (d) |
| Event stories clear at the end of the scene | (d) |
| Event NPCs are 4th-member helpers | (b) + (d) |
| No event maintenance, no big hunt by default | (d) |

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Clock | without `--clock`, dated content uses today's month-day in the newest service year with an event term that day (`event_now`) | (d) | the user's choice (replay the calendar); `--clock` overrides |
| Modes | event ranking: player is rank 1 | (d) | |

<a id="gacha"></a>
## Gacha
Code: `server/src/api/gacha/` (the draws, GetGachaInData, step-up chains, box gacha, the rate dialog); the reconstructed pools `data/gacha_pools.sqlite3`.

<a id="gacha-rules"></a>
### 4. Gacha

<a id="gacha-open"></a>
#### 4.1 What's open
- A banner is listed when `GetGachaInData.GachaHashMap` has an entry for it whose window contains now, and the master row's own `opened_at`/`closed_at` does too (b: `CGacha::IsEnableHash`). The server sends an entry for every `master_gacha` row open at the (possibly overridden) clock (a).
- In real time (2026) only 29 rows are open (their `closed_at` is far in the future: permanent banners). The last live banners closed on 2021-06-24 (`service_stop_day`), so the full 3.7.0 line-up needs `--clock` in May/June 2021 (a).
- `--enable-events` adds the gachas whose names match a keyword list (default: the summer banners) all year; see "Enabling events by keyword" under "Events".
- `limit_count` (total draws), `day_limit_count` (per day), `stepup_limit_count`, `sale_once_limit_count` / `sale_bulk_limit_count` with `sale_*_interval_day` limit the draws; the counts go in `GachaCount`, `GachaDayLimitCountInfo`, `SaleGachaCount` (a: columns and schema).

<a id="gacha-cost"></a>
#### 4.2 Cost
- **Single draw:** `coin` coins; `is_pay_coin` = 1 means paid coins only (a).
- **Bulk (10) draw:** `bulk_count` draws for `bulk_coin` coins (e.g. 10 for 2,500 or 5,000) (a).
- **Sale:** `is_sale` with `sale_once_coin` / `sale_bulk_coin` in `sale_opened_at`..`sale_closed_at` (`SaleGachaOnce` / `SaleGacha`) (a).
- **Ticket:** `ticket_item_id` × `ticket_num` per draw (`GachaTicket`) (a).
- Debit the wallet and send `Wallet` (the early canned replies didn't, notes).

<a id="gacha-rates"></a>
#### 4.3 Rates and pool
- **Rank rates:** `s_rank_rate`, `a_rank_rate`, `b_rank_rate`, `c_rank_rate`, `d_rank_rate` in percent (e.g. 4 / 2 / 26.1 / 67.9 / 0) (a).
- **Bulk bonus:** when `is_bulk_bonus` = 1, one draw of each bulk draw uses `bonus_s..c_rank_rate` (e.g. 12 / 4 / 84 / 0: a guaranteed B or better) (a: columns; c: the live game's "10th draw guaranteed ★4 or higher").
- **Gacha types** (a: `gacha_type` vs the other columns): 0 character gacha (1,389 rows, 985 of them step-up), 1 weapon gacha (458), 2 box gacha (434, all `is_box` = 1).
- **Ranks → rarity:**
  - character gachas: S and A are ★5 (S the pick-up characters of the banner, A the rest; without pick-ups S the aces, A the other ★5s), B ★4, C ★3 (a+text: the common row is 4 / 2 / 26.1 / 67.9 and banners split the 6 % as 3/3, 4.5/1.5, 5.5/2.5 while B and C stay; titles such as ★5以上1体確定キャラガチャ ("one ★5 or higher guaranteed") have `bonus_s_rank_rate` 100; the rate dialog prints `★5:%.5f%%` per rarity, `gacha_tilte_message_0002`) (c: the live game's ★5 6 %). **Rarity-6 roles are not drawn:** they are evolutions of the rarity-5 role of the same `role_category_id` (`master_role_evolution`), and a banner image shows the rarity-6 form of its rarity-5 pick-up (a; 4.5, R-BASE).
  - weapon gachas: A ★5 (8–8.5 %), B ★4, C ★3, S = the banner's pick-up weapons (a: rates; text: ticket names ★3/★4/★5武器ガチャチケット and the ★4～5 fill tickets' A 29.44 / B 70.56) (d: S).
- **The pool is not in the database.** `master_gacha.table_name` names a server table (`master_gacha_item_old`, `_role`, `_weapon`, `_20210610_valentine2021`, ...) that the client never had: the DB has no `master_gacha_item*` table (a). **It is reconstructed** in `data/gacha_pools.sqlite3`; 4.5 gives the rules, the format, and the server and client sides.
  - The rate dialog (`GetGachaRate` → `GachaRateInfoList`) must show the pools and per-unit rates the server really uses; 4.5 builds both from the same file (b: schema).
  - The pool reconstruction is in the UI-visible register: it is the largest (d) in the gacha.
- **Result:** each draw → `GachaItems` entry {master_role_id / master_item_id, player_character_id / player_item_id, duplication, is_mutation, is_bonus (not sent; (b) `CGachaResultInfo::Initialize` registers it, no visible effect found)}; the client shows the entries in reply order everywhere (summon, reveals, result list; (b), [gacha-presentation.md](gacha-presentation.md#order)); new characters → `AddCharacter` (a map keyed by uid string), new items → `AddItem` (a map keyed by uid string too, (b): [Conventions](#conventions)).
- **Duplicates** (b: `CLimitOverCharacter::CountLimiBreak`, `SetupLimitBreakItem`, `CountCharaChip`, which build the "limit over" result screen from the response):
  - a drawn character counts as a duplicate when the player owns a role of the same `role_category_id` (the same character at any rarity) (b: the screen matches by `CUIUtility::GetCharaCategoryId_FromCharaRoleId`);
  - each duplicate raises the owned character's limit break by one, up to its maximum (5.2). The response sends `LimitBreakCharacter` (map uid → CLimitBreakInfo {master_role_id, before/after_master_role_id, before/after_limit_break_count}); the screen assigns the steps before+1 .. after to the duplicates in draw order (b); the handler syncs the count onto the owned character (notes, `AddLimitBreak`);
  - a duplicate beyond the maximum becomes an item: `LimitBreakItem` (CLimitBreakItemInfo {master_role_id, master_item_id}) (b: shown for duplicates without a limit-break step); which item: `master_role_duplication_item` by the role's rank (rank 1 → `item_limitbreak_01`, 2 → `_02`, 3 → `_03`, 4 → `_03` ×2, 5 → `_06`; the `limitbreak_id` rows for the special roles) (a: table; c: duplicates became limit-break material);
  - character chips: `CharacterChipInfoList` entries (role, chip item, count), the count split evenly over the duplicates of that character (b: `CountCharaChip` divides by the number of duplicates). Chip item = `master_role.universe_chip_item_id` (593 of 737 roles) (a); amount: `master_universe_chip_gacha_exchange` by role rank (`chip` 100, `chip_rate` 5 / 25 / 50 / 50 for ranks 2–5) — read as `chip × chip_rate / 100` per duplicate (d);
  - `duplication` = 1 in the draw's `GachaItems` entry; the duplicate is not added to the roster (a: no second uid is needed; d).
- **`is_mutation`** ("mutation", `master_global.gacha_mutation` = 2): first read as a draw upgraded to a higher-rarity variant. The client shows it as a fake-out of the same unit: it appears at a lower tier (★5: tier 0 or 1 at random), transforms (`eo100_f07b`, SE 0x32) and is revealed again at its real rarity, and it doesn't count toward the draw's opening tier; no rarity changes ((b) `CGachaManager::CheckGachaResult`, `Progress_Main`; [gacha-presentation.md](gacha-presentation.md#selection)). The client doesn't read `gacha_mutation` (a server parameter). Leave 0 (d): the fake-out never plays.
- **Presentation:** which animation plays (tiers by rarity, the stage map by `resource_replace_group_id`, new vs duplicate vs limit-break material) and the assets: [gacha-presentation.md](gacha-presentation.md) (b).
- **Gift gacha:** `master_gift_gacha` rows of the banner (is_bulk 0/1) are granted with each single / bulk draw (a: columns; d: always granted) → `GiftGachaItems`.

<a id="gacha-step-up-box-rules"></a>
#### 4.4 Step-up and box gacha
- **Step-up:** `is_stepup` rows chain through `next_stepup_gacha_id`; `stepup_number` / `stepup_max` give the position; `loop_count` / `reset_type` restart the chain (a). Each draw advances the player's `StepUpGacha` {try_count, restart_count, next_master_gacha_id} (a: schema).
- **Box gacha** (event boxes paid with event coins, e.g. `ticket_item_id` `item_coin_213` × 5 per draw) (a):
  - each `master_gacha` row with `is_box` = 1 is one box; its contents are the `master_box_gacha` rows of that `master_gacha_id`: one row per slot, `box_count` copies of the slot (1 in the data), each granting `content` × `num` (a). `rate_weigh` is 1 everywhere and `is_reset` 0 everywhere (a), so a draw takes a uniformly random remaining slot (c: box gacha = drawing without replacement).
  - boxes chain with `box_gacha_index` 1, 2, 3 and `next_box_gacha_id`; `rest_box_gacha_num` counts the boxes after this one; the last box points to itself and has `is_manual_reset` = 1 (a). So: an empty box moves on to `next_box_gacha_id`; the last box can be reset (`ResetBoxGacha`) at any time, refilling it and counting `reset_count` (c: the live event boxes were resettable from the last box on; d: "any time" rather than "when empty").
  - progress per player: `BoxGachaList` {total_count, reset_count, next_master_gacha_id} and `BoxGacha` (remaining slots) (a: schema).

<a id="gacha-pools"></a>
#### 4.5 Gacha pools (reconstructed)
The live server drew from its `master_gacha_item_*` tables, which neither master DB has (4.3). `tools/build_gacha_pools.py` rebuilds a pool for each of the 2,281 gachas from the 3.7.0 master data and writes **`data/gacha_pools.sqlite3`** (in git, like `data/*.sqlite3`; deterministic for a given master, so the tool can regenerate it). Rebuild with `tools/build_gacha_pools.py [--master data/basmaster-3.7.0.sqlite3] [--report FILE]`; it prints the sanity checks below. The local server reads it through **`server/src/master/gacha_pools.{h,cpp}`**. Every rule carries a code (R-…), stored with its label in the file's `rule` table and in comments of the script. **The release packages' copy** (`tools/package.py`) has `gacha.name` (the master's title text) and `rule.text` emptied, so it carries no game text: **(a)** GetGachaRate then takes each page's title from the master, `master_text` of `master_gacha.name_message_id` with full-width ASCII made half-width (`gacha_pools::name_from_master`, the script's `zen2han`); the test `gacha/pools-name-from-master` checks every gacha's title comes out the same.

**What is drawn (ranks).**

| rank | character gacha (`gacha_type` 0) | weapon gacha (`gacha_type` 1) |
|---|---|---|
| S | the banner's pick-ups; without pick-ups the general aces (★5, rank 4) | the banner's pick-up weapons (46 gachas use S) |
| A | every other general ★5 (on the 10-step PU step-ups: every other general ace); without pick-ups the general ★5 non-aces (rank 3, `common_party`) | the general ★5 weapons, pick-ups included |
| B | ★4 (rarity 4, rank 2, `common_guest`) | ★4 weapons |
| C | ★3 (rarity 3, rank 1, `common_people`) | ★3 weapons |
| D | never (rate 0 in every row) | never |

- A drawn character is the **base role** of its `role_category_id` (its lowest rarity): rarity 6, and rarity 4/5 of ranks 1–2, are evolutions (`master_role_evolution`, rarity n → n+1). The real 3.7.0 save owns only rarity 3/rank 1, 4/2, 5/3, 5/4 and 4 rarity-6 roles (a), and every banner image says "進化や覚醒などを含む、強化が行われる前の状態で出現いたします" (units come before any evolution or awakening) (b).
- The S/A reading comes from the ticket gachas (a): ★4キャラ ticket B 100; ★4～5 S 2.2 / A 3.8 / B 94; ★5キャラ S 2.2 / A 97.8; **★5エースキャラ S 100**, whose text says an ace (エース) is a high-ability character; and the step-up steps titled "PU1体確定" (one pick-up guaranteed) have `bonus_s_rank_rate` 100. The 10-step PU step-ups' images say "★5はエースだけ!" (★5s are aces only) (b), so their A holds no party roles. That A is "the rest" on the other pick-up banners, and the party/ace split on the standard banner, are (d).
- **The general ★5 pool is the permanent line-up** (R-GENERAL): the ★5s offered by the exchange shops that list it (福袋 / GW / 700万DL / 覚醒 / マーレゼリア coin shops, 50+ roles each) or by a ピックアップキャラコイン shop: 70 aces and 15 party / special roles (a). **Every other ★5 is limited** (期間限定) and appears only as a pick-up of a banner that features it: all seasonal costumes (花嫁, 渚, 歌星, 聖夜 …), the 神 series, SRF, event units, collaboration roles (`role_cc*`: Tales of, Persona, NieR, Sakura Wars, Guilty Gear, FFBE, Attack on Titan, Valkyrie Profile, Radiata) and exceed roles (rank 5, picked up by the paid universe-pass banners `gacha_paid_role_*`). The shop split coincides with the costume names (a), and the SO2メモリアル banner image says "ピックアップは期間限定キャラのみ" (pick-ups are limited characters only) over five seasonal SO2 units (b). Units handed out by missions are limited too (d).
- **Weapons:** ★3/★4 = every `master_item` type 1 of that rarity; ★5 = the 229 weapons ever featured by a weapon-gacha image (released at the first featuring gacha) plus a 190-weapon launch set (W01–W17 families, `serial_number` <= 392, no 未定 / コインウェポン) (a+d). The other ~470 rarity-5 weapons (event rewards, `item_weapon_*`) are never drawn (d). A weapon kind released later (whip 2020-06-25, launcher 2019-02-14, scythe 2018-11-15: `master_weapon_kind.opened_at`) joins then (a). Kind-restricted banners draw only their kinds, read from 【…】 or after ":" in the title ('定常武器ガチャ【近接】【ナックル/双剣/剣&鞘/鎌】', '補填武器チケット：杖'); 【遠距離】 alone = range type 2 without 杖/オーブ/本, 紋章武器 = 杖/オーブ/本 (a: titles; d: the two group readings).
- **Release and window** (R-RELEASE-ROLE, R-WINDOW): a pool holds every unit released by the end of the gacha's window (`closed_at`, cut at the service end 2021-06-24 14:30), each row with its `released_at`; **the server draws only units with `released_at` <= its clock**, so a unit released mid-window joins on its release day and a permanent banner (2016 → 2030) grows over the years. The 222 roles dated 2017-05-20 04:00 (the earliest value: older history is collapsed into it) count as released at launch (d).
- **Weights:** equal within a rank (d). The live per-unit rates were shown in the rate dialog, but no copy survives.

**Pick-ups** (the S pool), first match wins; counts are gachas (type 0 / type 1):

| code | source | evidence | gachas |
|---|---|---|---|
| R-PU-PERMANENT | (a)+(d) | table `master_gacha_item_jousetu` (常設, permanent: standard banner, tickets, 定常武器), `_sphere211`, `_galaxy` → no pick-ups; their images are showcases | 7 / 12 |
| R-PU-GROUP | (a) | `master_gacha_pickup` of `gacha_pickup_group_id` | 9 / – |
| R-PU-IMAGE | (a) | `master_gacha_image` content rows (role → base role; weapon items) | 527 / 267 |
| R-PU-NAME | (a)+(d) | names in the title's brackets matched to `master_person` / `master_item` names: 'ピックアップキャラガチャ(花嫁レナ/花嫁イヴリーシュ)', 'ラスウェル確定ガチャ', '(ラティクスorミリー確定)', '(花嫁/水着/ハロウィンのみ)' | 78 / – |
| R-PU-SIBLING | (a)+(d) | the pick-ups of the gachas sharing its `banner_id` (steps of a step-up, single / 10-draw variants), also once more after R-PU-THEME and R-PU-NEW (a rerun under the original's banner: 復刻メイド1) | 221 / – |
| R-PU-BANNERART | (b) | read off the banner images where the master data names nobody: 衣装コンテスト2018 = ヒーローベルダ / ナースフィオーレ, 2019 = 花魁ミュリア / ハンターセリーヌ, 復刻神級1 = 神翼のマリア / 賢神のマスティマ, 2 = 神龍のアシュトン / 神星のレナ / 神翼のフェイト, 3 = 神弓のレイミ / 神導のソフィア; the 2020 maid step-ups and their reruns, メイド1 = メイドのクレア / メイドのネル, メイド2 = 執事のレオン / メイドのソフィア (a digit after メイド is a part number, not a year). **Added** to what the other rules find, from [gacha-verify.md](gacha-verify.md) (featured units in no pool): ホワイトデー限定復刻1 / 2 ("この5キャラをピックアップ!", five units each), イヴリーシュ誕生日記念 (six Evelysse costumes), ステップアップシグムント1–3 (シグムント), EP2 CHAPTER:10 (the six EP2 characters, "…EP2キャラクター6人のみ"; rates S 6 / A 0 (a)), 2018年福袋 (the four 常夏 and three Halloween-2017 units beside the four brides: "11キャラ") | 118 / – |
| R-PU-THEME | (c)+(d), checked (b) | seasonal reruns: '復刻花嫁2020' → the 花嫁/花婿 aces released in 2020; 水着 = 渚/真夏/常夏, アイドル = 歌星, メイド = メイド/執事; 正月 01-01..01-07, xmas/クリスマス 12-01..12-24, ハロウィン 10-20..10-31 (ハロウィンN = 2016+N), バレンタイン 01-25..02-14, costumes only. The banner images of 復刻正月2021, 復刻ハロウィン2020, 復刻クリスマス2020 and 復刻バレンタイン2021 name exactly these units | 260 / – |
| R-PU-RERUN | (d) | other reruns ('復刻SRF'): the pick-ups of earlier banners whose title holds the rerun's key, or both halves of a two-word key (復刻桜花桜雲 → '(桜花のマリア/桜雲のディアス)'); after R-PU-NEW, so it sees every earlier banner's pick-ups | 30 / – |
| R-PU-SERIES | (a)+(b)+(c) | 'SO4キャラピックアップガチャ', 'スターオーシャン5発売日記念…' ('スターオーシャン発売日' = SO1): that game's cast among the general ★5s, party included (b: the SO5 image, "スターオーシャン5★5キャラが10連で1体確定", shows nine base characters, which is what this gives); 'SO3メモリアル…': the cast's limited aces (b: the SO2メモリアル image). Cast by `master_person` label cp01..cp05 = SO1..SO5 (c; cp00 are anamnesis originals) | 32 / – |
| R-PU-NEW | (d) | a pick-up banner (not a rerun) still without evidence: the ★5s released on its opening day | 6 / 6 |
| none | | standard-like banners (DL / CM / anniversary / weekend-free / "★5以上確定" / step-ups without names), weapon banners without images | 108 / 185 |

A pick-up released after its banner opened (but before it closed) is drawn from its release on (R-PU-RELEASE, 6 cases). If a rank with a rate had no pool, S and A would fall back to each other (R-EMPTY); it never triggers.

**The file** (`meta.format` = 1):
- `gacha(gacha_id, id_label, name, gacha_type, kind, opened_at, closed_at, banner_id, pickup_source, kind_filter, is_bulk_bonus, bulk_count, is_stepup, stepup_number, next_stepup_gacha_id)`: one row per `master_gacha` row; `kind` role / weapon / box; the last five are copies of `master_gacha`.
- `gacha_rank(gacha_id, rank, rate, bonus_rate, set_id, rule)`: rank S..D, the master rates (percent; `bonus_rate` 0 unless `is_bulk_bonus`), the pool, and the rule codes that built it. `set_id` is null when both rates are 0.
- `pool_set(set_id, content_type, content_id, weight, released_at)`: the units (content type 2 role, 1 item, as in the master tables); pools are shared between gachas (512 sets, 27,165 rows).
- `pool_set_info(set_id, size, description)`, `gacha_pickup(gacha_id, content_type, content_id, source)`, `rule(code, source, text)`, `meta(key, value)`.
- Box gachas (`gacha_type` 2) have `gacha` rows only: their contents are `master_box_gacha` (4.4).

**Server side** (`soa::server::gacha_pools::Pools`, for the draws (`gacha`) and `GetGachaRate` (`get_gacha_rate`) in `server/src/api/gacha/`):
- `open()` finds the file (`--gacha-pools FILE` on soa / soa-server, else `data/gacha_pools.sqlite3` in the checkout), rejecting a file that isn't a pool file (e.g. an old git-lfs pointer).
- `draw(gacha_id, bonus, now, r1, r2, rank, unit)`: rank by the master rates (the bonus rates for the bonus draw of a bulk draw), skipping ranks with nothing released at `now` (d), then a unit by weight among those released at `now`. `now` is the server clock as "YYYY-MM-DD HH:MM:SS" (the clock that `GetGachaInData` uses).
- `units()`, `all_units()`, `rank_weights()`, `gacha()`, `id_of()` for anything else.
- `rate_info(gacha_id, now)` → the `GachaRateInfoList` entries (one per step of a step-up, following `next_stepup_gacha_id`; the last step loops back to step 1 in 167 of 168 chains (a)), each with `rate_lines()`.
- Test `server/gacha-pools` (in `--selftest`): the standard banner's rank frequencies over 20,000 draws, its ace pool growing between 2018 and 2021, the rate rows adding up to 100 % (and again in the bonus slot), and that every non-box gacha draws and has rate rows at the end of its window.

**Client side: the rate dialog can show exactly these pools** (b, from `CGachaRatio::CreateRatioList` / `ListItemUpdate` and the `CGachaRateInfo` / `CGachaRateContentInfo` `Initialize` key tables):
- `GetGachaRate` (fid `d6bcb49d`) answers `data.GachaRateInfoList`: an array of `CGachaRateInfo` (0x1a8 bytes) {`id` (+0x60), `title` (+0x90), `introduction_msg`, `bonus_msg`, `stepup_number` (+0x150), `GachaRateContentInfoList` (vector at +0x190)}, stored at `CParameterManager+0x5058`. `CGachaRatio::SearchRatioInfo(step)` takes the first entry for a normal gacha and the entry whose **`stepup_number`** equals the current step for a step-up (docs/notes.md calls +0x150 "the gacha id"; the key table says `stepup_number`).
- Each content row (`CGachaRateContentInfo`, 0x188 bytes) is {`type` (+0x60), `message_id` (+0x90), `content_id` (+0xd0), `percentage` (+0x100, a string), `direct_message` (+0x140), `order_id`}. `type`: 1 separator line; 2 text line; 3 section title (text = `direct_message`, else `message_id`); 4 character (`content_id` = role: the client looks up the person's name, the role's rarity icon, class icon and weapon icon itself); 5 item with rarity icon (weapons); 8 item without it; 6 / 7 open and close a block of rows that the client sorts before listing. Unit rows show `percentage` verbatim.
- `rate_lines()` emits: 3 "レアリティー別提供割合" (`gacha_tilte_message_0001`), 2 "★5:x%" / "★4:x%" / "★3:x%" (0002–0004), 1, 3 "一般提供割合" (0010), then per rarity 3 "★5提供割合 x%" (0005–0007), 6, one 4/5 row per unit with `"%.5f%%"` (0009's format), 7; and for `is_bulk_bonus` gachas the same under 3 "10連ガチャ特典枠" (0008) with the bonus rates. All numbers are computed from the same `rank_weights()` / `units()` as `draw()`, so **what the player sees is what is drawn**, including the clock filter. The row layout is (d): only the message texts survive, not a live response.
- `GetGachaRate` answers `rate_info()`'s pages when the pools file is there (`server/src/api/gacha/rates.cpp`), and the player state only without it (d). Replayed by the `economy` corpus; the dialog itself not checked in a live run.

**Sanity checks** (the script's report, 3.7.0 master):
- every pick-up unit is in its gacha's pool: 0 missing;
- ranks with a rate > 0 and an empty pool: 0 (R-EMPTY fallback used: 0);
- pool units released after their gacha closed: 0; units released after their gacha opened: 1,731 in 241 gachas (they join on their release day, R-WINDOW); pick-ups among them: 6 (R-PU-RELEASE);
- pool sizes (units at the end of the window):

| gacha type | gachas | S | A | B | C |
|---|---|---|---|---|---|
| 0 character | 1,389 | 1–70 (mean 6) | 14–85 (mean 61) | 18 | 18–34 |
| 1 weapon | 458 | 2–5 (46 gachas) | 22–419 (mean 233) | 5–51 | 4–50 |
| 2 box | 434 | `master_box_gacha` (11,826 slots) | | | |

- At the June 2021 clock (2021-06-10 15:00) 219 character, 16 weapon and 34 box gachas are open; all character banners but the standard, ticket, sphere211, galaxy and お詫び ones have pick-ups.

**Open questions** (all (d) above; better evidence would replace them): the per-unit weights; the party/ace split of the standard banner; which rarity-5 weapons beyond the featured and launch sets were drawable (no exchange shop lists a weapon line-up); release dates before May 2017. The 556 extracted banner images (`work/gacha-banners/`) name the pick-ups of most banners: reading more of them (as done for R-PU-BANNERART and to check R-PU-THEME) is the cheapest way to firm up the rest.

**Rules** (the script's `RULES`, also in the file's `rule` table):

| code | source | rule |
|---|---|---|
| R-TYPE | (a) | gacha_type 0 draws characters (roles), 1 weapons (master_item type 1), 2 is a box gacha whose contents are master_box_gacha (not rebuilt here; the server uses master_box_gacha directly). |
| R-BASE | (a+b) | A drawn character is the base role of its role_category_id: the lowest-rarity member. Rarity 6 (and 4/5 of rank 1-2) roles are evolutions (master_role_evolution: rarity n -> n+1 for FOL and items), never drawn. The real 3.7.0 save owns rarity 3/rank 1, 4/2, 5/3 and 5/4 roles plus 4 rarity-6 roles (a); the banner images say '進化や覚醒などを含む、強化が行われる前の状態で出現いたします' (units come before any evolution or awakening) (b). |
| R-RANK-ROLE | (a) | Character ranks: C = rarity 3 (rank 1, limitbreak common_people), B = rarity 4 (rank 2, common_guest), S and A = rarity 5. Evidence: the ticket gachas' rates and names - ★4キャラ (B 100), ★4～5キャラ (S 2.2 / A 3.8 / B 94), ★5キャラ (S 2.2 / A 97.8), ★5エースキャラ (S 100); rate headings gacha_tilte_message_0002..0004 are ★5/★4/★3. |
| R-SA-PICKUP | (a+d) | On a banner with featured (pick-up) characters, S = the pick-up characters and A = every other ★5 in the general pool. Evidence: step-up steps named 'PU1体確定' (one pick-up guaranteed) have bonus_s_rank_rate 100 (a); that A is 'the rest' is (d). |
| R-SA-ACEONLY | (b) | On the '10連10ステップ目PU1体確定' step-ups A holds the general aces only (no party roles): their banner images say '★5はエースだけ!' (e.g. 20200917_chara_PU_001, 20210610_chara_PU_003). |
| R-SA-NOPICKUP | (a+d) | On a banner without pick-ups, S = the ace ★5s (rank 4, limitbreak common_ace) and A = the other ★5s (rank 3, common_party). Evidence: the ★5エース ticket is S 100 %, its text says an ace is a high-ability character, and the plain ★5 ticket is S 2.2 / A 97.8 (a); the split for the standard banner (S 2.2 / A 3.8) is (d). |
| R-GENERAL | (a+b) | The general ★5 pool is the permanent line-up: the ★5 roles offered by the exchange shops that list it (福袋 / GW / 700万DL / 覚醒 / マーレゼリア coin shops, >= 50 roles each) or by a ピックアップキャラコイン shop (a new unit's coin): 70 aces and 15 party roles in their base forms (a). Every other ★5 - all seasonal costumes (花嫁, 渚, 歌星, 聖夜 ...), the 神 series, SRF, event units - is limited (期間限定): pick-up only. The split coincides with the costume names (a), and the SO2メモリアル banner image says 'ピックアップは期間限定キャラのみ' over five seasonal SO2 units (b). |
| R-LIMITED | (c+d) | Limited characters are never in a general pool, only as pick-ups of a banner that features them: the not-general ★5s (R-GENERAL), collaboration roles (id_label role_cc*: Tales of, Persona, NieR, Sakura Wars, Guilty Gear, FFBE, Attack on Titan, Valkyrie Profile, Radiata...) (c: collab units were limited to collab banners), exceed roles (rank 5, sold through the paid 'universe pass' banners gacha_paid_role_*) (a: those banners pick them up) and the units handed out by missions (master_mission_clear_present, master_mission_drop) (d). |
| R-RELEASE-ROLE | (a+d) | A role is released at master_role.opened_at and withdrawn at closed_at (a). The 222 roles dated 2017-05-20 04:00 (the earliest value; the older history is collapsed into it) count as released at launch (d). Rows with id_label not starting role_c (check_*, cp*) and roles withdrawn at 2017-05-20 05:00, an hour after that epoch ('※ダミーホームテスト狼アンリ', 'ティニーク(狼版)', 'アイドル子ティカ'), are test rows and excluded (a). |
| R-WINDOW | (a+d) | A gacha's pool holds every unit released by the end of its window (closed_at, cut at the service end 2021-06-24 14:30), each with its release time (pool_set.released_at); the server draws only units with released_at <= its clock, so a unit released mid-window joins the pool on its release day and a permanent banner grows over the years (a: dates; d: live pools grew the same way). |
| R-PU-PERMANENT | (a+d) | Gachas drawing from the permanent tables (table_name master_gacha_item_jousetu = 常設 'permanent': the standard キャラガチャ, the ★3..★5 / ★5エース tickets, the 定常武器 gachas; _sphere211; _galaxy) have no pick-ups: their master_gacha_image rows are showcases (a: table names, the tickets' fixed rates; d: showcase reading). |
| R-PU-GROUP | (a) | Pick-ups from master_gacha_pickup via master_gacha.gacha_pickup_group_id. |
| R-PU-IMAGE | (a) | Pick-ups from master_gacha_image rows of the gacha: content_type 2 = role (shown in its rarity-6 form; mapped to the base role, R-BASE), 1 = weapon item, 0 = role or item by id. |
| R-PU-NAME | (a+d) | Pick-ups from the banner title (master_text of name_message_id): names in brackets (e.g. 'ピックアップキャラガチャ(花嫁レナ/花嫁イヴリーシュ)') matched to master_person names (roles) or master_item names (weapons); a character name matches that person's ★5 base roles released by the close of the banner (d: the matching). |
| R-PU-SERIES | (a+b+c) | A banner named after a game ('SO4キャラピックアップガチャ', 'スターオーシャン5発売日記念...', 'SO3メモリアル...'; 'スターオーシャン発売日' = SO1) without named characters picks up that game's cast: its general ★5s (aces and party), or for a メモリアル banner its limited (seasonal) aces (b: the SO5 banner image 'スターオーシャン5★5キャラが10連で1体確定' shows the base cast, the SO2メモリアル image says 'ピックアップは期間限定キャラのみ'). The cast is master_person id_label cp01xx..cp05xx = SO1..SO5 (a: labels; c: the casts, e.g. cp05 = Fidel, Miki of SO5, cp04 = Edge, Reimi of SO4; cp00 are anamnesis originals). |
| R-PU-SIBLING | (a+d) | A gacha without own evidence takes the pick-ups of the gachas sharing its banner_id (the steps of a step-up and the single/10-draw variants of one banner) (a: shared banner; d: same pick-ups); applied to their own evidence first and again after R-PU-THEME and R-PU-NEW (a rerun under the original's banner_id, e.g. 復刻メイド1). |
| R-PU-RERUN | (d) | A rerun (復刻) banner without own evidence takes the pick-ups of the earlier banners whose title contains its event key (e.g. 復刻花嫁2020 -> banners titled with 花嫁2020), or both halves of a two-word key (復刻桜花桜雲 -> 'ピックアップキャラガチャ(桜花のマリア/桜雲のディアス)'). Applied after R-PU-NEW and a second R-PU-SIBLING pass, so it sees every earlier banner's pick-ups. |
| R-PU-ROLEPICK | (a+d) | 'ロールピックアップ' banners naming a class (アタッカー, ディフェンダー, シューター, キャスター, ヒーラー) pick up every general-pool ace of that master_role.category_type. |
| R-PU-THEME | (c+d) | A seasonal rerun without other evidence ('復刻花嫁2020', '復刻正月2021', '復刻ハロウィン1', '復刻神級(2)') picks up the aces of that event: units whose names carry the costume word (花嫁/花婿, 渚/真夏/常夏, 歌星 for アイドル, メイド/執事) released in that year, or units released in the event's window (正月 01-01..01-07, xmas/クリスマス 12-01..12-24, ハロウィン 10-20..10-31, バレンタイン 01-25..02-14, costumes only: not a plain *_b01a character; ハロウィンN = the N-th Halloween, 2016+N) (c: the seasonal events and their costume names; d: the windows). Checked against the banner images of 復刻正月2021, 復刻ハロウィン2020, 復刻クリスマス2020 and 復刻バレンタイン2021: all four match (b). |
| R-PU-BANNERART | (b) | Pick-ups read off the banner images where the master data names none: the 衣装コンテスト 2018 step-ups show ★5ヒーローベルダ / ★5ナースフィオーレ (20200917_chara_PU_001), the 2019 ones ★5花魁ミュリア / ★5ハンターセリーヌ (20200903_chara_002); 復刻神級1 神翼のマリア / 賢神のマスティマ, 2 神龍のアシュトン / 神星のレナ / 神翼のフェイト, 3 神弓のレイミ / 神導のソフィア (20210603_chara_PU_006, _007, 20210610_chara_PU_005); the 2020 maid step-ups メイド1 = メイドのクレア / メイドのネル, メイド2 = 執事のレオン / メイドのソフィア (20201008_chara_PU_003, _004; also their 復刻 reruns). Added to what the other rules found (tools/gacha_verify.py, docs/gacha-verify.md): ホワイトデー限定復刻1/2 (five units each, 'この5キャラをピックアップ!'), イヴリーシュ誕生日記念 (six Evelysse costumes), ステップアップシグムント1-3 (シグムント), EP2 CHAPTER:10 (six EP2 characters with マスティマ; its rates S 6 / A 0 (a)), 2018年福袋 (the 4 常夏 and 3 Halloween-2017 units next to the brides: '11キャラ'). |
| R-PU-NEW | (d) | A pick-up banner (not a rerun) still without evidence picks up the ★5 roles (weapons) released on its opening day (master_role.opened_at's date = the gacha's). |
| R-PU-RELEASE | (d) | A pick-up unit released after the banner opened but before it closed counts as released by the banner (it is added to the S pool, never to the general pools). |
| R-RANK-WEAPON | (a) | Weapon ranks: A = rarity 5, B = rarity 4, C = rarity 3. Evidence: ★3/★4/★5武器 tickets are C/B/A 100 %; the ★4～5 fill tickets are A 29.44 / B 70.56. |
| R-S-WEAPON | (a+d) | Weapon S (used by a few step-ups with bonus_s_rank_rate 100) = the banner's pick-up weapons; A = the general ★5 pool including those pick-ups (d: uniform within A). |
| R-W5-POOL | (a+d) | The general ★5 weapon pool: the weapons ever featured by a weapon gacha image (master_gacha_image content_type 1; released = the first featuring gacha's opened_at) (a), plus the launch set: rarity-5 weapons of the W01..W17 families with serial_number <= 392, excluding placeholders (未定) and coin-shop weapons (コインウェポン) (d: the launch set). Other rarity-5 weapons (event rewards, item_weapon_*) are not drawn (d). |
| R-W34-POOL | (a+d) | ★3 and ★4 weapon pools: every master_item type 1 of that rarity (51 and 52 rows) (a), released at their weapon kind's opened_at (master_weapon_kind.opened_at, e.g. whip 2020-06-25) (a) or at launch (d). |
| R-KIND | (a+d) | Weapon banners restricted by kind in their title ('定常武器ガチャ【近接】【ナックル/双剣/剣&鞘/鎌】', '補填武器チケット：杖', 'gacha_pickup_weapon_sword_*') draw only those kinds; 【遠距離】 alone = range-type 2 without the magic kinds; 紋章武器 = 杖/オーブ/本 (a: titles; d: the two group readings). |
| R-WEIGHT | (d) | Within a rank, every unit has the same weight (the live per-unit rates are unknown; the rate dialog showed them, but no copy survives). |
| R-EMPTY | (d) | A rank with rate > 0 whose pool would be empty falls back: S -> the A pool, A -> the S pool (recorded in gacha_rank.rule). |

<a id="gacha-core"></a>
### Gacha as the server core built it
- **`GetGachaInData`:** `GachaHashMap` lists every `master_gacha` row whose `opened_at` ≤ now ≤ `closed_at` (29 rows at the real 2026 date; more with `--clock`). **(a)** Each has one `GachaHashList` entry: hash = the gacha id in hex. **(d)** The client only echoes it back with the draw. Plus `Wallet` and `Player`.
- **Price and count:**
  - `GachaOnce` is 1 draw for `coin`;
  - `Gacha` is `bulk_count` draws for `bulk_coin`;
  - `SaleGachaOnce` / `SaleGacha` use `sale_once_coin` / `sale_bulk_coin` when set;
  - `GachaTicket` takes `ticket_num` × draws of the `ticket_item_id` stack item.

  **(a)** The draw count for `GachaTicket` is its second argument. **(d)**
- **Currency:** free coins are spent first, then paid. **(a)** (master_text `uimsg_buy_history_explan`, "Stocks and wallet"). Rows with `is_pay_coin` take only paid coins. **(a)** Without enough currency the draw returns no items and debits nothing. **(d)**
- **Rank per draw:** by `s/a/b/c/d_rank_rate`. The last draw of a bulk draw uses the `bonus_*_rank_rate` columns when `is_bulk_bonus` is set. **(a)** for the rates; **(d)** for which draw gets the bonus.
- **Pool:** the reconstructed pools of 4.5 (`data/gacha_pools.sqlite3`, `gacha_pools::Pools::draw` at the server clock) decide the rank and the unit. Weapons become unique items (`AddItem`, `GachaItems.player_item_id`).
  - `GetGachaRate` answers `GachaRateInfoList` from `Pools::rate_info`, so the rate dialog shows what is drawn.
  - Without the pools file, the fallback is the server's own rarity pools (`draw_role`). Their method is **(d)**, following 4.3 above:
  - S and A: ★5 and up = rarity 5 and 6, role ranks 3..5. S draws from the banner's `master_gacha_pickup` group when it has one. **(a)+(c)**
  - B: rarity 4. C and D: rarity 3. **(b)+(a)** `gacha_role_0001`'s 10-draw bonus rates are C 0 / B 84, and its banner says 10連で★4以上のキャラが1体確定!.
  - Only roles already released (`opened_at` ≤ the server's clock); the whole rarity when none fits. **(d)** The banners' own `opened_at` is too early for the permanent ones: `gacha_role_0001` opened 2016-01-01.
  - Only characters, no weapons, even for weapon banners. **(d)**
- **Duplicates:**
  - A drawn role is a duplicate when the player owns a role of the same `role_category_id`. **(b)** `CLimitOverCharacter`.
  - The owned character's limit break goes up by one, up to its maximum: the number of `master_rank` rows of its rank minus one (3 / 5 / 10 / 10 / 10). **(b)** `CalcMasterRole2LimitBreakMax`
  - Response: `LimitBreakCharacter`, a map uid → {id, master_role_id, before/after_master_role_id, before/after_limit_break_count}. **(b)**
  - Beyond the maximum, the `master_role_duplication_item` material (by `limitbreak_id`, else by rank) is added to the stack items and listed in `LimitBreakItem`. **(a)+(c)**
  - The result says `duplication` 1. **(c)** for duplicates becoming limit breaks; **(a)** for the cap.
- **New characters:** level 1, uid `0x7e100000+`, in `AddCharacter` (map keyed by uid as a string).
- **History:** every draw goes into `gacha_history` (gacha, role, the drawn character's or weapon's uid, rank, duplicate, the coins spent; a weapon draw has no role).

<a id="gacha-step-up-box"></a>
### Gacha: step-up and box
- **Step-up** (a: `is_stepup`, `stepup_number`, `next_stepup_gacha_id`; the last step points back to step 1):
  - A chain is the gacha ids linked by `next_stepup_gacha_id`, ordered by `stepup_number`, keyed by its step 1 (d).
  - Only the chain's current step can be drawn; another step is refused with 10403 (d).
  - Each draw advances the chain: the state's `stepup` table {try_count, restart_count, next_id}. Drawing the last step goes back to step 1 and counts a restart (a: the loop link; d: the count).
  - The draw's response carries `UpdateStepUpGacha` and `StepUpGacha`, and `GetGachaInData` carries `StepUpGacha`: {`player_id`, `master_gacha_id`, `try_count`, `is_close`, `restart_count`, `next_master_gacha_id`} (a: the schema), **a map keyed by step id**, one entry per step of every chain open at the clock (see "Step-up and box gacha lists" below; the earlier array was ignored by the client).
  - `GachaHashMap` still lists every open step (d). `stepup_limit_count`, `loop_count` and `reset_type`: see [Step-up gacha state](#step-up-state) (agent server-rules).
- **Box gacha** (4.4):
  - `BoxGacha(gacha, count)`: `count` draws, capped by the slots left, each costing `ticket_item_id` × `ticket_num` (a). Each draw takes a uniformly random remaining copy (c: without replacement; a: `rate_weigh` is 1 everywhere) and grants its `content_type` / `content_id` × `num` as a drop is granted.
  - The response carries:
    - `BoxGachaItems` {`master_box_gacha_id`, `content_id`, `content_type`, `duplication` 0};
    - `UpdateBoxGacha`, the box's slots, a map keyed by `master_box_gacha_id` {`player_id`, `master_gacha_id`, `master_box_gacha_id`, `max_box_count`, `box_num` = copies left (b), `order_id`, `content_id`, `content_type`, `num`, `is_maintenance`} (b: `CBoxGachaInfo::Initialize`);
    - `UpdateBoxGachaList` {`total_count`, `reset_count`, `next_master_gacha_id`: the box itself, or `next_box_gacha_id` once it's empty (a)};
    - `StockItem` and `AddItem` / `AddCharacter`.
  - `ResetBoxGacha(gacha)`: only a box with `is_manual_reset` (a); at any time (d); it refills the slots and counts `reset_count`. Other boxes are refused with 10403 (d).
  - `GetBoxGacha`: `BoxGachaList` for every box series open at the server clock, and `BoxGacha` with the current boxes' slots. `GetGachaInData` carries `BoxGachaList` too (the イベントガチャ tab). Shapes: "Step-up and box gacha lists" below.
  - The series' last box ("∞", `next_box_gacha_id` = itself or none) refills by itself once emptied, counted as a reset: the box banners say "∞ボックスは繰り返し召喚できます" (b), and an emptied box (`box_num` 0) drops out of the client's list, so it couldn't be reset any more (b: `CGacha::RemoveInactiveBox`; d: the refill).
- **Character chips for duplicates** (4.3). On a gacha with `universe_chip_flg` = 1 (a: 956 rows), each duplicate adds chips of the role's `universe_chip_item_id` to the stack items (a).
  - The amount is `chip × chip_rate / 100` of the `master_universe_chip_gacha_exchange` row for the role's rank: 5 / 25 / 50 / 50 for ranks 2–5 (d: the reading of the columns).
  - The draw's response carries `CharacterChipInfoList`, a map uid → {`id`, `master_role_id`, `master_item_id`, `num` = the chips for that character in this draw}, and `StockItem`.
  - (b) `CharacterChipInfo` derives from `CLimitBreakItemInfo`, whose `Initialize` (@0x150364c) registers `id`, `master_role_id`, `master_item_id` and `num`. `CLimitOverCharacter::CountCharaChip` reads the map at `CParameterManager+0x6210` and splits `num` evenly over that character's duplicates.

<a id="step-up-state"></a>
### Step-up gacha state (`server.cpp` `stepup_value`, the draw)
| Rule | Label |
|---|---|
| CStepUpGachaInfo is {`player_id`, `master_gacha_id`, `try_count`, `is_close`, `restart_count`, `next_master_gacha_id`}. `CGacha::FirstCreateNormalAndStepup` lists, for every entry without `is_close`, the master row whose id is its `master_gacha_id`, and `CGacha::CheckSeriesData` lets it be drawn while `try_count` < that row's `stepup_limit_count`. So `master_gacha_id` is the chain's **current step** and `try_count` the draws made on it. (The earlier server sent step 1 and the chain's total draws: the client would have shown step 1 and closed it after one draw.) | (b) |
| A step is drawn `stepup_limit_count` times (1 in every 3.7.0 step-up row) before the chain moves to `next_stepup_gacha_id`; after the last step the chain returns to step 1 and counts a restart (`restart_count`). `next_master_gacha_id` = the current step's `next_stepup_gacha_id`. | (a)+(b) |
| `is_close` when the current row has a `loop_count` and that many restarts are done; a closed chain is refused (10403). No 3.7.0 step-up row sets `loop_count` or `reset_type`, so chains loop without end and never reset. The only rows with `reset_type` (5) are the pass gachas (`gacha_galaxy_role`, the universe-pass ones), which need a subscription the port can't sell. | column meaning (d); data (a) |

<a id="gacha-draws"></a>
### Single and bulk draws of `Gacha`
| Rule | Label |
|---|---|
| `Gacha(id, hash, n)`: n = 1 is the single draw (`coin`, 1 unit), n = 0 the bulk draw (`bulk_coin`, `bulk_count` units). `CGacha::RequestGacha` passes 1 when the selected button (`CGacha+0x2d4`) is the single one, where the sale variant is `SaleGachaOnce`, and 0 otherwise (`SaleGacha`). The server used to draw every `Gacha` as the bulk one, so 1回ガチャ cost and drew a 10-draw. Test `gacha/stepup-box`. | (b) |

<a id="gacha-lists"></a>
### Step-up and box gacha lists (`server.cpp` `stepup_value`, `box_list_value`, `box_value`)
No step-up and no box gacha was ever listed on the gacha screen, at any clock and with or without `--enable-events`: the server sent `StepUpGacha`, `BoxGachaList` and `BoxGacha` as **arrays**, and these are `IInfoBaseMap<u64, …>` infos, whose `DeserializeArray` does nothing (docs/ason.md). `CGacha::FirstCreateNormalAndStepup` lists a step-up row only through the `StepUpGacha` map (CParameterManager+0x7408) and `CGacha::AddListBoxSeries` (the イベントガチャ tab) a box only through the `BoxGachaList` map (+0x7278), so both stayed empty.

| Rule | Label |
|---|---|
| `StepUpGacha` / `UpdateStepUpGacha` / `BoxGachaList` / `UpdateBoxGachaList` / `BoxGacha` / `UpdateBoxGacha` are maps keyed by id (the id as a string). | (b) `IInfoBaseMap::DeserializeArray` is empty; `InfoBaseNumberMap<…>::ConvertParserValueToKey` |
| **One entry per step** (key = `master_gacha_id` = the step's gacha id): `CApiNotify::UpdateStepUpGacha` merges by key and copies `try_count`, `is_close`, `restart_count`, `next_master_gacha_id` but never `master_gacha_id`, so a key can't move from step to step. The current step is open, the chain's other steps `is_close` = true (`FirstCreateNormalAndStepup` skips `is_close` == 1), so each chain shows its current step ("ステップ n/10"). | (b); the closed siblings (d) |
| Every chain whose current step is open at the clock is sent, an untouched one at step 1 with `try_count` 0; the draw's `UpdateStepUpGacha` carries that chain's steps. | (b) nothing lists a chain without an entry; defaults (d) |
| **One entry per box** (key = `master_gacha_id` = the box): `CApiNotify::UpdateBoxGacha` merges `UpdateBoxGachaList` by key without copying `master_gacha_id`. A series (the `default_release` = 1 box, then `next_box_gacha_id`) lists its boxes up to the current one (the first with copies left, or the last); the emptied ones `is_close` = true, so the list moves on to ボックス 2 after BOX COMPLETE. | (a) the chain; (b) the merge and `AddListBoxSeries` (`is_close` == 0 and `box_num` != 0) |
| `CBoxGachaListInfo.box_num` = the copies left in the box: `CGacha::CreateBoxData` keeps it for the box screen, which shows it as ボックス残数 and offers 10連ガチャ only with 10 or more left; `RemoveInactiveBox` drops a box with `box_num` 0. `is_reset` = `is_manual_reset`. | (b) (seen on screen: box_num 1 showed ボックス残数 1 and no 10-draw) ; `is_reset` (d) |
| `CBoxGachaInfo.box_num` = a slot's copies left (the only field `UpdateBoxGacha` merges); `order_id` and `num` from `master_box_gacha`. `BoxGachaItems` entries {`id` = the draw's index (d), `master_box_gacha_id`, `content_id`, `content_type`, `num`, `duplication`}: the result list shows "×num" (it showed ×0 without it). | (b) the Initialize functions; (a) the columns |
| A box series whose banner image isn't present isn't listed (`enable_events::gacha_shown`). | (b)+(d), as the enabled gachas |

Tests: `gacha/stepup-box` (map shape, one open step per chain, an untouched chain at step 1, box series listing and the move to box 2, the ∞ box refill). Seen on screen with `--enable-events` (step-ups on the おすすめ / キャラ tabs, a 10-draw moving 復刻水着2020① from ステップ 1/10 to 2/10, the 星の海と夢の渚 box drawn to BOX COMPLETE and listed as ボックス 2) and with `--clock "2020-08-10 12:00:00"` alone (水着2020① / 復刻兎耳 / 復刻水着2019 step-ups and the 星の海と夢の渚 box with their real end dates).

<a id="gacha-register"></a>
### Player-visible (c) and (d) rules (gacha)

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Gacha | rank S/A = ★5 (S pick-up, else ace), B ★4, C ★3; weapons A ★5, S pick-up | (a)+(d) | ticket rates and titles fit; the S/A split without pick-ups is inferred (4.5) |
| Gacha | the pools (server tables `master_gacha_item_*` are missing): reconstructed per gacha | (a)–(d) per rule | 4.5: pick-ups from images / titles / themes, general pools by release date, equal weights within a rank (d) |
| Gacha | duplicate over the max → `master_role_duplication_item`; chip amount | (c)/(d) | the matching and limit-break steps are (b) |
| Gacha | box draw without replacement; last box resettable any time | (c)/(d) | |
| Gacha | gift gacha always granted; `is_mutation` 0 | (d) | |

<a id="growth"></a>
## Growth
Code: `server/src/api/growth/` (BoostCharacter … EquipSkill) and `server/src/rules/growth_rules.{h,cpp}`.

<a id="growth-rules"></a>
### 5. Growth

<a id="character-exp"></a>
#### 5.1 Character EXP and level
- **Curve:** EXP to the next level = `int(master_character_common_parameter[level].next_exp × master_role_boosted(rank, rarity).exp_rate + 0.5)` (b: `PersonModel::GetNextLevelExp(level, rank, rarity)`). `exp` is kept within the level (b: the strengthen screen shows `next - exp`).
- **Level cap:** the character's own cap from the server (`CPersonInfo` +0x1690, the limit-break result's level cap) or else `master_role_level_max` by rarity (3: 40, 4: 50, 5: 60, 6: 70) (b: `tCharaData::LevelMax`, `CMasterCache::tLevelMaxCache::Get`). Rarity 7 = rarity 6's cap plus the levels opened on the universe board (`master_universe_board`) (b, partly read). EXP at the cap is discarded (d).
- **Boost with EXP items** (`BoostCharacter(uid, item, count)`), as the client previews it (b: `CPartyStrengthening::GetStrengtheningItemReflection`):
  - EXP gained = `floor(count × item.base_boosted_point × (1.5 if item.role_category_type == the character's category else 1.0))` (`item_exp_*`: 1,000..16,000 per item; `item_exp_all_*` have no category);
  - FOL = `count × master_role_boosted(rank, rarity).use_fol_one` (b: `MasterRoleUseFolOne`), times a type-4 campaign's `magnification` (0.5) (a: campaign labels `*_kyara_FOL*`; b: `CharacterUtility::ConsidereCampaignFol`).
  - **Big success:** `master_global.pc_boosted_up_rate` = 11.5 (% chance) and `pc_boosted_bonus_rate` = 1.5 (EXP multiplier), `pc_boosted_role_category_bonus_rate` = 1.5 (the category bonus above) (a: keys; d: that up_rate is the percent chance). Type-7 campaigns (`*_kyouka`, 1.48–3.0) multiply the chance (a: labels; d: what they multiply). Result: `BoostedCharacterResult.is_big_success`.
- **Seeds** (`AddStatusCharacter(uid, item, count)`): each `item_seed_*` adds its own stat column of `master_item` (attack / intelligence / defence / hit / guard / ap 1, hp 5) to the character's `add_<stat>`, capped at `master_role.<stat>_add_max` (a: the seed rows; b: `CPartyStrengthening::GetParameterAddItemReflection` previews `current + value × count`, capped at the role's maximum). FOL: `master_global.add_status_fol_<stat>` per use (hp 1,500, attack..guard 7,500, ap 500,000) (a: keys; d: per seed used rather than per point). Result: `CharacterAddStatusResult` (before/after add_*, use_fol, new_fol).

<a id="limit-break"></a>
#### 5.2 Limit break
- **Maximum** by role rank = number of `master_rank` rows of that rank minus one (people 3, guest 5, party / ace / exceed 10) (b: `CParameterUtility::CalcMasterRole2LimitBreakMax`; matches `master_character_limit_break.target_limitbreak_max`).
- **FOL** for the next step = `master_rank(rank, limit_break = current + 1).use_fol` (b: `tCharaData::LimitBreakNeedFol`).
- **Items:** the item passed with the request, `master_item_limit_break.<people|guest|party|ace>` copies of it by role rank 1–4 (e.g. `item_limitbreak_01`: 1 / 5 / 25 / 50) (b: `tCharaData::LimitBreakNeedItemNum`), or `master_character_limit_break` rows of the role's `limitbreak_id` for the special ones (`child_tika`, `bow_crawd`, `common_exceed`) (a).
- **Effect:** `limit_break_count` + 1 → stats from `master_rank` (section 3) (b). The level cap doesn't change (d: the client reads the cap from the rarity unless the server overrides it).

<a id="evolution"></a>
#### 5.3 Evolution
- `master_role_evolution` by (role `rank`, `rarity`, `category_type`): `use_fol` and up to four (item, num) pairs (a). The evolved role is the role with the same `role_category_id` and the next higher rarity (b: `CUIUtility::MaxEvolution(role)` looks for a `master_role` row with the same `role_category_id_label` and a higher `rarity`; the evolution cost is `CParameterUtility::FindRoleEvolution(rank, rarity, category_type)`). The response carries `EvolutionResult.UpdatePlayerCharacter` {before/after master_role_id, level} (a: schema); **requires the character at its level cap** and enough items and FOL (b: `CPartyCompositionEvolution` enables the button only when every item count, the FOL and `level >= tCharaData::LevelMax()` are met); the evolved character starts again at level 1, EXP 0, under the next rarity's cap `LevelMax(rarity + 1)` (b: the evolution screen previews the evolved form at "LV 1/<new cap>", and after the result the client says `uimsg_next_strongth` 進化したため、レベルが1になりました; "Fixes found on the growth screens"). FOL campaigns of type 5 halve the cost (a).
- ★7 evolution (`IsRare7_Evolution`) uses the `Ac_*_6-7` rows (a).

<a id="awakening"></a>
#### 5.4 Awakening, skills, mastery, universe
- **Awakening:** `master_item_awaken` (awaken_id, awaken_level → items, `use_fol`) and `master_awaken` (per `role_category_id` and level: rush skill, talents, skills) (a).
- **Mastery:** `master_mastery_step` (type, step → required item, count, FOL) (a). What the server does with it: [Mastery](#mastery).
- **Universe board:** `master_universe_board` (cells: open level, status bonus, talent, `chip_num`), `master_universe_talent`; reset costs `reset_universe_board_item` × 1 (a).

<a id="growth-and-economy"></a>
### Growth and economy: what the extension modules implement
The growth, item, shop and daily-system APIs, as the local server applies them. Code: `server/src/api/growth/growth.cpp`, `api/items/items.cpp`, `api/shop/shop.cpp`, `api/daily/login_bonus.cpp`; the pure rules are in `server/src/rules/growth_rules.{h,cpp}`. Each rule carries its label in a code comment too. Sections 1, 5, 7, 9 and 10 are the evidence; this is what the code does with it.

<a id="character-growth"></a>
#### Character growth
- **BoostCharacter(uid, item, count)**: EXP = floor(count × `master_item.base_boosted_point` × 1.5 when the item's `role_category_type` is the role's `category_type`) (b: `CPartyStrengthening::GetStrengtheningItemReflection`; a: `pc_boosted_role_category_bonus_rate`). The role's EXP curve (`next_exp` × `master_role_boosted.exp_rate`) and level cap (b); EXP at the cap dropped (d). FOL = count × `master_role_boosted(rank, rarity).use_fol_one` (b). Big success: a `pc_boosted_up_rate` % chance (a: key; d: its meaning) multiplies the EXP by `pc_boosted_bonus_rate`, truncated (d). FOL campaigns (type 4) aren't applied (d). Answers `BoostedCharacterResult` {uid: {id, before/after level and exp, is_big_success}}, `StockItem`, `Player`.
- **LimitBreakCharacter(uid, item)** and `_Legacy`: the maximum is the `master_rank` rows of the role's rank − 1 (b). Items: the `master_character_limit_break` row of the role's `limitbreak_id` for that item and the current limit break (`target_limitbreak_min` ≤ lb < `target_limitbreak_max`) gives `item_num` (a); without one, `master_item_limit_break`'s column for the rank (b: `tCharaData::LimitBreakNeedItemNum`). FOL = `master_rank(rank, lb + 1).use_fol` (b). The level cap stays the rarity's (d). Answers `LimitBreakCharacter` {uid: CLimitBreakInfo}, `StockItem`.
- **EvolutionCharacter(uid)**: the character must be at its level cap (b). The new role: same `role_category_id_label`, the next higher rarity (b: `CUIUtility::MaxEvolution`). Cost: `master_role_evolution(rank, rarity, category_type)`: `use_fol` and up to four items (a+b). The level goes back to 1 (b; agent server-rules, see "Fixes found on the growth screens"; server-growth kept it). Answers `EvolutionResult` {use_fol, UseStockItem, UpdatePlayerCharacter {id, before/after master_role_id, level, is_rarity_7}}.
- **UpdateAwakenLevel(uid, level)**: one step at a time (d); cost `master_item_awaken(role's awaken_id, level)`: up to three items and `use_fol` (a). Answers `AwakenResult` with `UpdateCharacter`.
- **AddStatusCharacter(uid, seed, count)**: the seed's own stat column of `master_item` (a) × count, capped at `master_role.<stat>_add_max` (a+b: `GetParameterAddItemReflection`). FOL `add_status_fol_<stat>` per seed (a: key; d: per seed). Answers `CharacterAddStatusResult` (CPersonAddStatusResultInfo's fields) plus use_fol / new_fol (d: names). The raised stats are in `Character` (`add_*`) and added to the battle status (`person_status_info`, `server/src/api/player/person_status.cpp`) as the client's status computation adds them (b: `PersonModel::CalculateParameter`).
- **EquipWeapon / EquipAccessory(uid, item uid)**: only owned items of the kind (`master_item.type` 1 / 3) (a); an item moves from its previous owner (d). Answers `EquipWeaponResult` / `EquipAccessoryResult` {Character: {uid: {id, weapon_item_id / accessory_item_id}}, Item: {uid: {id}}}. **EquipSkill(uid, s1, s2, s3)** stores the slots and answers `UpdateCharacter`.

<a id="equip-auto"></a>
#### Auto-equip (`EquipAuto(u64 character)`, the equipment screen's 自動設定; agent server-u-missions)
- **Who picks (b):** the server. The request is the character's uid only, and `CApiNotify::ApplyAutoEquipResult` (@014d0444) copies the answer's `EquipWeaponResult` / `EquipAccessoryResult` (the characters' weapon and accessory, the items), `SetAssistResultList` (character_id, assist_id, old_assist_id) and `UpdateCharacterList` (the skill slots) into the client's roster.
- **Options (a):** `master_config` `auto_equip_steal` false (`uimsg_auto_equipment_config_text`: with it, other characters' equipment and assists are taken), `auto_equip_skill` true (`uimsg_auto_equipment_skill_config_text`: the skills are set), `auto_equip_assist` true. The player's own value wins when stored (`UpdateConfig`, [Settings](#settings); `settings::config_on`), else these defaults.
- **The choice (d):** the weapon is the owned weapon of the role's kind (`master_role` / `master_weapon` `master_weapon_kind_id`, a) with the highest attack + intelligence at its level (each `master_item` stat linear from the stat to `<stat>_max` over the rarity's `level_max`; most weapons have no `_max`, so their base stat), the accessory the one with the highest attack + intelligence + defence + hit + guard; an item another character wears isn't taken (the steal option off); ties keep the lower uid; nothing fitting leaves the slot as it is. With `auto_equip_skill` the empty skill slots take the role's open skills (`master_skillN_id` with `master_skillN_open_level` ≤ the level, a) not equipped yet, in order; equipped skills stay. The assist isn't changed (`SetAssistResultList` empty): what the online server chose isn't known.
- Seen on screen: 自動設定's confirmation says 所持している装備、スキル、アシストからおすすめの装備、スキル、アシストに変更します (the server's recommendation); after it the screen shows the server's weapon, accessory and skills.
- Code: `server/src/api/growth/growth.cpp` (`equip_auto`). Tests: `growth/equip-auto`, the `items-party` replay corpus; session `port/scripts/equipment_session.sh`.

<a id="growth-verification"></a>
#### Verification
- Refusals use the core's error path (agent server-missions): the handler sets a client error code, the request is rolled back and the client shows `error_message_text_<code>`: 10206 items short, 10204 locked / equipped items, 10710 FOL short (growth) / 11001 (items) (d: which FOL code), 20000 coins short (the item shop's exchange: 20003, b: its answer lambda @01b5eea4 opens the coin shop on it, [Paid currency](#paid-currency)), 11006 limit reached / sold out, 11002 not at the level cap, 17001 exchange closed, 10208 otherwise (b: the texts; d: the choice).
- Unit tests: `rules/growth` (every pure rule, hand values), `growth/apis` (Boost, LimitBreak, Evolution, AddStatus on a scratch server seeded from the 3.7.0 save, with refusals), `items/apis` (Compose, Lock, Sell, SellStackItem, UseHealItem, StaminaHeal, the same way), `shop/item-shop-and-exchange` (item-shop purchase, sold out, new period; exchange), `daily/login-bonus` (login bonus day 1, no second grant, day 2), `presents/achievement-chain` (achievement chain receive).
- In the client (`--server inproc`, screenshots): the LOGIN BONUS popup at home on day 1, the present received (紋章石 +500); the item shop (`phase:0xa` → アイテムショップ) buys a monthly set for 5,000 紋章石 and shows the row sold out; the exchange (アイテム交換所 → 武器) lists the permanent coin shops with the coins held and exchanges a weapon.
- The growth screens (CPartyComposition's strengthening, limit break, evolution, weapon custom) are the 3.7.0 client's own (footer キャラクター, アイテム); `port/scripts/growth_session.sh` plays them on screen and checks the server's log for each request and its effect (verified on 3.7.0 in P5a, 2026-10-01). `growth_drive.sh`, which issued the requests through a FakeApiCaller drive hook while the offline UI lacked the screens, was removed with the hook.

<a id="growth-screen-fixes"></a>
### Fixes found on the growth screens (`port/scripts/growth_session.sh`)
| Rule | Label |
|---|---|
| **Evolution resets the level to 1** (exp 0): the evolution screen previews the evolved form at "LV 1/70", and after the result the client says `uimsg_next_strongth` 進化したため、レベルが1になりました. The server kept the level (its result screen then showed 60/70). | (b) |
| **LimitBreakCharacter's second argument is the `master_character_limit_break` row id** the screen offers (e.g. `type_party_l`), not the item id; the row gives the item and its count. The server refused every limit break from the screen with 10208. An item id is still accepted. | (b) (the request seen in game) |
| **AttachGear** needs the weapon's limit break ≥ the gear's `master_gear.limit_break_conditions` (the list shows it as セット条件; the screen refuses with 武器の上限解放が必要です) and at least as many weapon slots as the gear has bonuses (`tItemData::GearSlotCount`: a gear's non-zero `add_param_type` count, a weapon's `max_gear_slot_num` capped at 3). | (a)+(b) |
| `Player.gear_num` (CPlayerInfo +0x978, `NowGearItemCount`, the ギア所持 count) = the free gears. | (b); attached not counted (d) |

<a id="mastery"></a>
### Mastery (マスタリー, 師弟; `server/src/api/growth/mastery.cpp`)
キャラクター > マスタリー: three 道場, each training one 師匠 / 弟子 pair through five trainings (each a choice of three cards); after the fifth (皆伝) the 弟子 inherits a talent of its 師匠 and the pair moves to the 皆伝 list. Decompiles: `work/decomp/server-u-mastery-*.resolved.c` (3.7.0).
- **What the client keeps (b):** `CPlayerCharacterMasteryInfo` (`Initialize` @014f772c): `character_id` (the 弟子, the map's key), `player_id`, `parent_character_id` (the 師匠), `dojo_no` (an inline name `port/fakeapi/fields.txt` misses), `master_mastery_step_type_id`, `master_mastery_step_1..5_option_no`, `created_at`, `updated_at`. `CMasteryTop::UpdateList` (@01b95450) shows the rows of the player's `player_id`: fewer than five cleared trainings in 道場 `dojo_no` (1-3), the others in the 皆伝 list with their `updated_at`. `CUpdateCharacterMasteryInfo` adds `mastery_talent_id` and `parent_master_role_id`; `OnTrainMasteryRes` (@014e8ba0) merges each element of `UpdateCharacterMasteryInfoArray` into the map and copies those two into the 弟子's `CPersonInfo`; `OnResetMasteryRes` (@014e9958) erases each element's `character_id` and zeroes them.
- **Who (b):** `tCharaData::InitializeMastery` (@01822340): a role with a mastery type is a 師匠 (trainer), the others can be 弟子; a 弟子 counts its cleared trainings (non-zero option_no), and a non-zero parent role in its `CPersonInfo` counts as all five, so the two `CPersonInfo` keys are 0 until 皆伝. `uimsg_mastery_Warning_01`: both at **LV70** and the **same ロール** (`master_role.category_type` 1-5, which the five mastery types match one to one (a)). The pair's type is the 師匠 role's `master_mastery_step_type_id` (a).
- **The requests (b):** `TrainMastery(弟子, 師匠, u8, u32 type, u8 step, u8 option)`: the selection screen's lambda (@01ba2880) pairs with step 0, option 0 and the dojo index + 1; the training dialog's (`StartTraining`, @01b939e8) sends the 弟子's cleared trainings + 1 and (`マスタリーパスメダルを使う` ? 4 : 1) + the card's index. `ResetMastery(u64, u64)` comes 師匠 first from the selection screen (@01ba4910) and in the 皆伝 dialog's order (@01b94244); the server finds the pair either way.
- **Pairing:** both owned and distinct, the 師匠's role has the request's type and the 弟子's none, the same category, both LV70 (11002 otherwise), dojo 1-3 (10208 otherwise). **(b)** A character already in a pair (either side, training or 皆伝) leaves it first (`uimsg_mastary_dialog4` "現在の師弟関係を解消して、新たな師弟関係を結びますか"). **(b)** Another pair still training in that dojo refuses (10208). **(d)** (the screen pairs only in an empty dojo)
- **A training:** only the pair's next one (10208). Cards 1-3 cost `master_mastery_step` (type, step, option_no) `required_master_item_id` × `required_num` and `required_fol` **(a)**; the pass medal (option 4-6) costs `master_global.mastery_training_pass_item_id` × `mastery_training_pass_required_num` and no FOL **(a)+(b)** (`CMasteryTrainingConfirmationDialog::Setup` enables that button on the medal count alone), and stores the chosen card **(d)**. Items short 10206, FOL short 10710.
- **皆伝 (the fifth):** `master_global.mastery_reward_master_item_id` × `mastery_reward_num` to the stock (`MasteryRewardInfo` {master_item_id, num}) **(a)+(b)** (`CMasteryTrainingAllClearDialog`'s gift line, `uimsg_mastary_dialog11`). The 弟子 inherits `parent_master_role_id` = the 師匠's current role and `mastery_talent_id` = the talent in the 師匠 role's `master_role.mastery_talent_slot` **(a)**; when the 師匠's awakening row (`master_awaken` of its category at its awaken level, the row `tTalentDataSet::Create` gets) sets that slot, its talent replaces the role's **(a)+(d)** (e.g. role_cp0022_b01a_6191's slot 5 changes at awakening 5). Both are computed from the stored pair, so they follow the 師匠's later growth **(d)**; `CPersonInfo` sends them for a graduated 弟子 only, `CPersonStatusInfo` always (0 otherwise).
- **Awakening a 師匠:** `UpdateAwakenLevel`'s `AwakenResult.update_child_id` / `update_child_mastery_talent_id` are the graduated 弟子 and its talent now (b: `OnUpdateAwakenLevelRes` @014e2d90 sets that character's `CPersonInfo` `mastery_talent_id`); 0 / 0 without one **(d)** (sent whenever there is one).
- **Parting (`ResetMastery`):** the pair's row goes, with the trainings and the inherited talent **(b)** (`uimsg_mastary_dialog2`); nothing paid comes back **(d)**. Answers the parted pair (its `character_id` is what the client erases). No such pair: 10208.
- **State:** table `mastery` (schema version 17): the 弟子 `uid` (key), `master_uid` (unique: one pair each), `dojo_no` 1-3, `type_id` (a `master_mastery_step.type_id`), `step1..5` (the card cleared, 0 not yet), the times; both characters cascade.
- Code: `server/src/api/growth/mastery.cpp`. Tests: `growth/mastery-pairing`, `growth/mastery-training`, `growth/mastery-awakening`, `server/schema-migrate-v17`; the `mastery` replay corpus; the session `mastery` (`port/scripts/mastery_session.sh`).

<a id="role-change"></a>
### Role change (`ChangeRole(u64 character, u32 master_role_id)`; `server/src/api/growth/growth.cpp`)
- **What the client does (b):** 装備・技・アシスト変更 shows ロール選択 for a character of a person with `master_role_change` rows (`uimsg_evolution_role_change_description`: "このキャラクターは進化した為 ... ロールを変更できるようになります"); `CRoleSelect` lists the five role types and its request lambda (@01c72678) sends the character and the chosen role; `OnChangeRoleRes` copies `UpdateCharacter` into the character.
- **The rule:** the new role has a `master_role_change` row whose `person_id` is the character's role's `master_person_id` and whose `rarity` is the character's, inside the row's `opened_at` / `closed_at` when set **(a)**; another role, or its own, is refused (10208). The set skills are reset **(b)** (`uimsg_evolution_role_change_done`: "セットしたスキルが初期化されます"): `roster.equip_skill1..3` and **(d)** the character's skills in every party set (`PartySet` answered when one changed). Level, EXP, skill levels, limit break, awakening and equipment stay **(d)**.
- **Mastery:** a graduated 弟子 whose new role type isn't its 師匠's keeps the pair, but its talent stops counting (`uimsg_evolution_role_change_confirm`: "伝授されているタレントが無効になります ... ロールを戻すと再度タレントが有効になります") **(b)**: `CPersonStatusInfo.mastery_talent_id` is 0 then ([Mastery](#mastery)).
- **Route:** in-process a status-only method (Status 0); the port queues it for the local server (`docs/client-changes.md` "Mascot and role").
- Code: `change_role`. Tests: `growth/change-role`, the `mastery` replay corpus; the session `mastery` (cp0010_b01a_6165 ヒーラー -> アタッカー, kept after a re-login).

<a id="growth-register"></a>
### Player-visible (c) and (d) rules (growth and economy)

From the growth and economy modules (items, shops, login bonus and achievements too):

| Rule | Label |
|---|---|
| NEW badges ([NEW badges](#new-badges)): what is gained from now on is new until viewed; the seed's and an older state's characters and items are not; a stack item is new only when its first stack arrives | (d) |
| Big success: `*_up_rate` is a percent chance, × `*_bonus_rate` | (d) |
| FOL campaigns (types 2, 4, 5) and big-success campaigns (6, 7) not applied | (d) |
| Seed FOL per seed | (d) |
| Limit break keeps the level cap | (d) |
| Awakening one level at a time | (d) |
| Compose: locked / equipped materials refused (the points per level and each material's gain are (b) since 2026-10-06: [Compose points](#compose-points)) | (d) |
| Grade-up: the base becomes the new weapon at level 1 | (d) |
| An equipped item moves from its previous owner | (d) |
| Auto-equip (EquipAuto): the strongest weapon of the role's kind and accessory by summed base stats, no item taken from another character, the empty skill slots filled with open skills, the assist unchanged; the master_config defaults stand for the player's settings (agent server-u-missions) | (d) |
| Accessory inheritance (InheritAccessory): a locked or equipped material refused as for compose; the material's limit break kept with the inheritance (agent server-u-missions) | (d) |
| UpdateItemStock is refused with 11006: the stock starts at item_stock_max | (d) |
| Heals add to the current stamina (overflow kept) | (d) |
| Shop / exchange / login / achievement grants: shop and exchange straight to the inventory; login bonus and achievements to the present box | (c)/(d) |
| Item-shop `limit_count` 0 = unlimited; non-monthly rows never reset; `reset_at` = the next reset; `num_total` = all-time purchases | (d) |
| Exchange count keys: contents id | (d) |
| Login-bonus day at 04:00 local time; `is_received_now` only in the granting response; present `reason_type` 1 / achievement 3 | (d) |
| `Player.tutorial_status` 9 for the seeded account | (d) |
| Achievement status values; untracked types report 0; received rows leave the list | (d) |
| Mastery: a dojo with a pair still training refuses another pair | (d) |
| Mastery: the pass medal stores the card it was used on | (d) |
| Mastery: an awakening's talent in the mastery slot replaces the role's; the inheritance follows the master's later growth | (d) |
| Mastery: parting returns nothing paid | (d) |
| ChangeRole resets the character's skills in the party sets too; level, skills' levels, equipment kept | (d) |

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Growth | big-success chance 11.5 %, ×1.5 | (d) | key names only |
| Growth | seed FOL per seed used | (d) | amounts are (a)/(b) |
| Growth | limit break leaves the level cap | (d) | |

<a id="items"></a>
## Items and gear
Code: `server/src/api/items/` (compose, grade up, sell, lock, heal items; gear).

<a id="weapons-and-accessories"></a>
### 5.5 Weapons and accessories
- **Compose** (`ItemCompose(base, materials)`): each material adds `(material.level + 100) × boosted_point / 100` of the material's rarity in the base's compose table, summed; the base levels by `next_level_boosted_point` with the rest carried and 0 at the cap (b; the full rule with its addresses: [Compose points](#compose-points)). (Until 2026-10-06 this read `(material.boosted_point + 100) × master_item_compose[material rarity].boosted_point / 100`, from `GetAddBoostedPoint` "as far as read", taking the `+0x120` field of the material's `CItemInfo` for `boosted_point` by a property order `id, player_id, master_item_id, item_type, boosted_point, limit_break_count` that misses `level`; and the level followed from cumulative points (d).) Levels from `master_item_compose` (weapons) / `master_item_accessory_compose` (accessories): per rarity `level_max` 10, `next_level_boosted_point` per level, `use_fol_one` per material (a). Big success: `weapon_compose_up_rate` 11.5 %, `weapon_compose_bonus_rate` 1.5 (a; d: meaning as for characters); a type-6 campaign (`*_gousei`, 3.0) multiplies it (a). Type-2 campaigns halve the FOL (a).
- **Limit break** of a weapon by feeding the same weapon: raises `limit_break_count` and the level cap per `master_item_limit_break_level_max` (limit break 1..5 → cap 12..20) (a).
- **Limit-break items** ("hammers", …ハンマー：上限解放素材; マジカルスレッド for accessories) raise it too, one raise each, like a copy (b: `CItemStrengtheningPotal::GetAddLimitReleaseWeaponNum` @01b899d8 / `GetAddLimitReleaseAccessoryNum` @01b89b70 count a material of the base's item id, else a limit-break item). A limit-break item is a strengthening material (b: `CParameterUtility::IsStrengMaterialWithMaster` @0180a2d0 → `CMasterCache::IsStrengMaterial` @01692f9c: its `master_weapon` kind's label contains `W99St`) whose id is a `master_weapon_limit_break.item_id` (184 rows) or `master_accessory_limit_break.item_id` (1 row) (b: `IsLimitBrealItem` @01b8975c, `IsAccessoryLimitBrealItem` @01b897bc; a: all 185 are W99St items). Which base it fits (b: `CItemStrengtheningList::IsAvailableLimitBreak` @01b746fc, `IsAvailableAccessoryLimitBreak` @01b75a4c):
  - a weapon row **with** `weapon_type_id` (the 8 generic hammers: 片手剣, 銃, ナックル, 剣＆鞘, ダガー, 弓 by `master_weapon_kind`, and オール / マジカル with `weapon_type_id_label` `ALL`): the base's `master_weapon.master_weapon_kind_id` equals it, or the label is `ALL`. The row's `limitbreak_type_id` isn't read on this path, so a generic hammer fits every weapon of its kind, event families included (W01SwR etc. are other kinds);
  - a weapon row **without** one (the ~176 family hammers, e.g. 翠錨ハンマー `type_2020natu2`): its `limitbreak_type_id` equals the base's `master_item.limitbreak_type_id` (families can span kinds: `type_nier` is W01Sw and W13Th);
  - the accessory row: `limitbreak_type_id` set and `accessory_type_id_label` `ALL` (the one row, so マジカルスレッド fits every accessory), else that type equals the base's.
  The material list never offers one that doesn't fit (b: `CreateWeaponList` / `CreateAccessoryList` skip it before listing), so the server refuses such a compose with 10208 (d: the code). The item is consumed and adds boosted points like any material (b: `GetAddBoostedPoint` makes no exception); past the cap it raises nothing (the client warns first: `WarningLimitbreak` @01b8a810 at current + raises ≥ 6).
- **Grade up** (`ItemGradeUp`): `master_item_grade_up` by rarity: `grade_up_num` = 5 materials and `use_fol`; the new item is drawn from `master_item_grade_up_list` (same rarity and weapon kind) by `rate_weigh` (a).
- **Sell:** price = `round(master_item.sale_fol × master_item_sale_rate[level].sale_rate)` for weapons (item kind 1; `sale_rate` 1.0 at level 1, +0.1 per level), else `sale_fol` (b: `CParameterUtility::tItemData::SellingPrice`). Stack items: `sale_fol` × count (a).
- **Material compose:** `master_material_compose`: up to five (item, num) → `result_item_id` × `result_item_num`, `use_fol` (a).
- **Gear:** `master_gear*`, `master_global.coin_for_generate_gears` 10,000, `attach_gear_coin` 10,000, `extraction_facter_1..3` (a). Implemented by agent server-rules: see "Server rules added by agent `server-rules`" (now [Gear](#gear) and the domains' sections; the heading: `docs/history/server-rules-history.md`).

<a id="new-badges"></a>
### NEW badges (`ClearNewCharacter`, `ClearNewItem`, `ClearNewStackItem`)
Code: `server/src/api/items/new_flags.cpp`; the flags `roster.is_new`, `items.is_new`, `stock.is_new` (schema step 13).

| Rule | Source | Notes |
|---|---|---|
| The player state's `Character` (`CPersonInfo`), `Item` (`CItemInfo`) and `StockItem` (`CStackItemInfo`) entries carry `is_new` (u32 0 / 1): the client's NEW badge. | (b) | `CPersonInfo::Initialize` (@014f9bf0) registers `is_new`, a u32 at +0x400; `CItemInfo` and `CStackItemInfo` list `is_new` among their fields. Only the player's own Character list carries it (not the battle status or the rental clones). |
| A character, weapon / accessory or stack item gained is new: every row added to `roster`, `items` or `stock` (a draw, a drop, a present, a shop) starts new; a gacha's or reward's `AddCharacter` entry for a new character says `is_new` 1 too. | (d) | The server never sent the flag before, so the client showed no badge; when the online game set it isn't known. |
| A stack item is new only when its first stack arrives (its `stock` row is created); more of an item held, or held before at 0, isn't new again. | (d) | |
| What the seed save holds, the new player's starters, and every row of a state from before step 13 are not new. | (d) | The seed restores a player who had seen them; existing rows had no badge. |
| `ClearNewCharacter(uids)`: clears the owned characters named and answers `UpdateCharacterList` [{`id`, `is_new`: 0}]; unknown uids are skipped. | (b) + (d) | (b): `OnClearNewCharacterRes` (@014d2ef8) copies each entry's `is_new` (its `CUpdateCharacterInfo` +0x2a0; keys `id`, `is_new` from `CUpdateCharacterInfo::Initialize` @0163f48c) into the Character of that id. (d): the ownership check. |
| `ClearNewItem(uids)`: clears the owned items named and answers `ItemClearNewList` [uid...]. | (b) + (d) | (b): `OnClearNewItemRes` (@014d28a8) reads a list of u32 ids and sets the Item's `is_new` (+0x240) to 0. |
| `ClearNewStackItem(master item ids)`: clears the held stack items named and answers `StackItemClearNewList` [id...]. | (b) + (d) | (b): `OnClearNewStackItemRes` (@014d2bd0) reads a list of u32 master item ids and sets the StockItem's `is_new` (+0x120) to 0. |

Tests: `items/new-badges`, `server/schema-migrate-new-badges`; the `badges` replay corpus (a character draw, the flags in GetPlayer, the three ClearNew* with owned and unknown ids).

<a id="items-and-stamina"></a>
### Items and stamina
- **ItemCompose(Array)(base, materials)**: each material adds (its level + 100) × `master_item_compose` (weapons) / `_accessory_compose` (accessories) `.boosted_point` of the material's rarity / 100 (b: [Compose points](#compose-points); before 2026-10-06 the server read the material's boosted points for its level: 5,000 for a fresh ★4 material where the screen previews 5,050). A copy of the base's own item raises its limit break, up to the last `master_item_limit_break_level_max` row (a); so does a limit-break item that fits the base, one raise each, and one that doesn't fit is refused (10208) (b; see 5.5). The level and the points within it as `ItemModel::_CalcLevel` (b: [Compose points](#compose-points)), capped at `level_max` or the limit break's `level_max` (a). (Before 2026-10-06: level = 1 + cumulative points / `next_level_boosted_point` (d), the points stopping at the cap level (d).) FOL = `use_fol_one` of each material's rarity, summed (a; b: the strengthening screen's 必要FOL, `CItemStrengtheningPotal::InitializePotal` @01b856ac, sums per material the `tItemComposeParam` (`CreateItemComposeList` @01b83aa0: the base's table) whose rarity is the material's master rarity, the match `GetAddBoostedPoint` makes; until 2026-10-06 the server charged the base's rarity: 10,000 for a rarity-5 base where the screen showed 6,000 for a rarity-4 material). The screen also applies a running type-2 FOL campaign (`CUIUtility::GetCampaignSituation(2)` @01ef94a4, with the universe pass's); the server doesn't (d, as for every FOL campaign). Big success `weapon_compose_up_rate` % → × `weapon_compose_bonus_rate` (a: keys; d: meaning). Locked or equipped materials refuse the request (d). Answers `ComposeResult` and `Item`.

<a id="compose-points"></a>
#### Compose points: what the strengthening screen previews (b)
The strengthening screen (`CItemStrengtheningPotal`) previews a compose as 強化ポイント `current/next` and the level it reaches; the server grants exactly that (since 2026-10-06, agent compose-points).
- **Per material** (`CItemStrengtheningPotal::GetAddBoostedPoint` @01b891c8): for each material (`+0x218[i]`, `+0x268` of them) the sum adds `(CItemInfo+0x120 + 100) × param[2] / 100` (32-bit, the division unsigned, truncated per material) for the `tItemComposeParam` whose `param[0]` is the material's master rarity (`CMasterParameterItemElement+0x118`). `+0x120` is the material's **`level`**: `CItemInfo::Initialize` @014f8e50 registers the properties `id` (+0x60), `player_id` (+0x90), `master_item_id` (+0xc0), `item_type` (+0xf0), `level` (+0x120, default 1), `boosted_point` (+0x150), `limit_break_count` (+0x180), `is_equip`, `is_lock`, `num`, `is_new`. The material's own `boosted_point` is not read; there is no same-item, same-kind or same-type bonus and no campaign in it.
- **The table** (`CreateItemComposeList` @01b83aa0): the base's type picks `CParameterUtility::CollectItemCompose` (weapons, `master_item_compose`) or `CollectItemAccessoryCompose` (`+0x20c` set: accessories, `master_item_accessory_compose`); each row gives `tItemComposeParam` {rarity (+0xa8), next_level_boosted_point (+0x108), boosted_point (+0x138), use_fol_one (+0x198)} (a: the two tables have the same rarity → boosted_point 100 / 250 / 2,000 / 5,000 / 10,000).
- **So**, per material: ★1 101, ★2 252, ★3 2,020, ★4 5,050, ★5 10,100 at level 1; a level-10 ★4 adds 5,500, a level-20 ★5 (limit break 5) 12,000.
- **The base** (`InitializePotal` @01b856ac): the label shows `base.boosted_point + Σ` over `GetNextPoint` (@01b89100: `next_level_boosted_point` of the base's rarity), or `---/---` at the level cap (`CParameterUtility::WeaponLevelMax` @018253a0); the level preview is `ItemModel::_CalcLevel(copy, level, boosted_point, Σ)` (@017c5484) on a copy whose limit break includes this compose's raises (capped at 5): while the level is not the cap, the points plus the gain reaching `next_level_boosted_point` (the accessory table for `item_type` 3, the weapon table for 1) make a level and the rest carries on; at the cap (`ItemModel::GetMaxLevel` @017c53ec: without a limit break `MasterItemComposeModel::GetByRarity`'s `level_max`, the **weapon** table even for an accessory, else `MasterItemLimitBreakLevelMaxModel::GetByLimitBreakCount`'s, by the count alone; the server reads the item type's table and rows, which give the same values in 3.7.0 (a)) the points are 0 and the rest is lost. So `CItemInfo.boosted_point` is the points **within** the level; the server keeps that in `items.exp` (schema version 21 converted the points since level 1 it kept before).
- **Not in the preview:** a big success (`weapon_compose_up_rate` / `weapon_compose_bonus_rate`, the server's (d) above) can't be previewed; it multiplies the sum. The screen's only campaign is type 2 on the FOL (`CUIUtility::GetCampaignSituation(2)` just before the FOL label, `ShowFolMagnificationBadge`); no campaign touches the points. The server applies no FOL campaign (d: no evidence of what the old server did; see the register).
- Tests: `rules/growth` (the formula and the level-up by hand values), `items/compose-points` (★3 / ★4 / ★5, a levelled material carrying points, several materials and a level up, weapon and accessory, the cap, a big success), `server/schema-migrate-v21`; replay corpus `compose-points`.

- **ItemGradeUp(Array)(base, materials)**: `master_item_grade_up[base rarity]`: exactly `grade_up_num` materials and `use_fol` (a). The new weapon is drawn from `master_item_grade_up_list` rows of the base's rarity and weapon kind, open by the clock, by `rate_weigh` (a). The base becomes the new weapon at level 1 without limit break (d). Answers `GradeUpResult` and `Item`.
- **MaterialCompose(id, times)**: `master_material_compose`: up to five (item, num) and `use_fol` → `result_item_id` × `result_item_num`, per time (a).
- **SellItem(Array)(uids)**: weapons `round(sale_fol × master_item_sale_rate[level].sale_rate)`, others `sale_fol` (b: `tItemData::SellingPrice`); locked or equipped items refuse (d). **SellStackItem(item, n)**: `sale_fol` × n (a). **SellGear** is the gear module's (`api/items/gear.cpp`, "Gear" below). Answers `SellResult` {total_fol, master_item_id, num, item_ids, StockItem}.
- **LockItem / UnlockItem(Array)(uids)**: the lock flag, sent as `Item.is_lock`.
- **UseHealItem(item, n)**: `master_item` type 10 (a); points `StaminaHealPoint`: heal_type 1 → heal_point % of the maximum, 2 / 3 → heal_point (b), × n.
- **StaminaHeal()**: `stamina_use_coin` = 100 coins (a+b), free coins first (a: "Stocks and wallet"); heals the maximum (b).
- Healed stamina is added to the current stamina, overflow allowed; the regeneration clock restarts when it reaches the maximum (d).

<a id="accessory-inheritance"></a>
### Accessory inheritance (`InheritAccessory(u64 base, u64 lost)`, ファクター継承; agent server-u-missions)
- **What the client does (b):** an inheritance accessory (＜INHERIT＞, `cp0003_tutorial_inheritance_001`: it takes in another accessory's factor) has `master_item.max_inheritance_num` (a: 21 accessories, all 2). `CUIUtility::CheckInheriteType` (@01ed0bec) is 1 when that is non-zero and the item's `InheritItemInfo.inherited_master_item_id` (CItemInfo+0x248+0x60) is 0, 2 once it is set, so the client tests the number for non-zero only; with 1 the strengthening screen sends `InheritAccessory(base, the first material)` instead of `ItemCompose` (`CItemStrengtheningPotal::SetStrengtheningExec` @01b89d08, request lambda @01b8dc5c). `CApiNotify::OnInheritAccessoryRes` (@014cb410) applies `InheritResultInfo` {base_player_item_id, lost_master_item_id, lost_player_item_id, lost_item_limit_break_count}: the base's InheritItemInfo takes the lost item's master id and limit break and the lost item leaves the list; `ComposeResult`'s after level / boosted points / limit break are copied to the base.
- **Seen on screen (b, the strengthening screen in the port):** the material list greys out the other inheritance accessories; with an ordinary material chosen the screen previews a compose (強化ポイント 5050/10000, 必要FOL 6000) and the factor to be taken in (新たに解放されるファクター); the confirmation says 強化合成時に素材のアクセサリーのファクターが継承され … 一度合成するとファクターを変更できません; the result shows the inherited factor under the base's own.
- **The rule:** the base must be an owned accessory that can inherit and hasn't (b: `CheckInheriteType`, the dialog's 一度合成すると…: one inheritance per accessory), the lost one another owned accessory that isn't an inheritance one (b: greyed out). The rest is ItemCompose's with that one material (b: the preview and the dialog; the same code, `compose`): its boosted points, FOL, big success and limit break, counted as `accessory_boost` too; locked or equipped materials refused (d, as for compose). The material is used up, and `items.inherited_master_item_id` / `inherited_limit_break` (schema version 16) keep what the base took in. Every load's `Item` carries `InheritItemInfo` {inherited_master_item_id, inherited_master_item_limit_break_count} for such an item (b: `InheritItemInfo::pParseName`, its fields), and only for it. Counted for achievement type 58 (`accessory_inherit`; a: "アクセサリーにファクターを N回継承させる"). Refusals: 10208 for a base that can't inherit or a lost item that isn't another ordinary owned accessory, else the compose's (10204 locked or equipped, 11001 FOL) (d: the codes).
- **Before:** in-process the FakeApiCaller's method only returned a status: the screen showed the result and the lost accessory came back on the next load; over the wire `{Time}` only.
- Code: `server/src/api/items/items.cpp` (`inherit_accessory`), `api/player/player_info.cpp` (`item_info_list`). Tests: `items/inherit-accessory`, `server/schema-migrate-v16`, the `items-party` replay corpus (an inheritance accessory and an ordinary one from the fixed drops of me99_875 / me99_341); session `port/scripts/equipment_session.sh`.

<a id="gear"></a>
### Gear (ギア, 武器カスタム; `api/items/gear.cpp`)
**Client structures** (b: the decompiled `Initialize` bodies and `CApiNotify` handlers):
- `GearInfoList` (CParameterManager+0x8c98) = map<gear uid, CGearInfo {`type`, `param1`, `param2`, `player_item_id`, `slot_index`, `is_new`}>. It holds every owned gear, attached or not; the gear lists show the ones with `player_item_id` 0 (`tItemData::CreateGearList`).
  - `type` 0 = a gear item: `param1` = its `master_item` id (type 15, with `master_gear_id`).
  - `type` ≠ 0 = a gear made from a weapon's factor: `param1` = the weapon's item, `param2` = the factor slot 1..3 (`tItemData::SetGearItem(u32, u32)`, which shows it as `master_global.weapon_gear_item`). The server uses `type` 1 (d).
- `AddGearInfoList` (+0x8ce8, same shape) is merged into `GearInfoList`; `UpdateGearList` (+0x8d38, gear uids) names gear taken out of it (DeleteGear / SellGear; ClearNewGear clears `is_new`; RemoveGear detaches); `UpdateAttachedGearInfoList` (+0x8d88) = map<weapon uid, [CAttachedGearInfo]>.
- A weapon's gears are the child `AttachedGearInfoList` of its `CItemInfo` (+0x2e0): CAttachedGearInfo {`type`, `param1`, `param2`, `gear_id`, `add_param_type1..3`, `value1..3`}. The weapon's stats add `value_k` to stat `add_param_type_k`: 1 attack, 2 intelligence, 3 defence, 4 hit, 5 guard; 6 = a factor, which takes two slots (`tItemData::SetGearList`, `SetGearItem`). The server sends it on every weapon with gear in `Item` (an `ext::ItemExtra` hook).

**Rules:**
| Rule | Label |
|---|---|
| Content type 15 grants one gear of that `master_item` per unit; type 98 draws from the `master_gear_lottery` category (`gear_drop_1..5`) open at the clock, by `rate_weigh`. The gear stock cap isn't checked for grants. | (a); cap (d) |
| An attached gear's bonuses are its `master_gear.add_param_type1..3` / `add_param1..3`; a weapon-factor gear carries the weapon's `factor<slot>_id` as bonus type 6. | (a); factor gear (d) |
| `GetGearInfo`, and every full-state player response, send the whole `GearInfoList`. The client refetches it when it opens the gear screens (`CCustomGear::Setup`, `CItemPossessionList::Setup`), so grants elsewhere only change the state. | (b) |
| **AttachGear(weapon, gear, slot):** a free gear, a weapon with `master_item.max_gear_slot_num` > slot (0-based), and the same weapon kind (tutorial `cp0003_tutorial_180` 同じ武器種のギア). A gear already in the slot is destroyed (`uimsg_gear_set_dialog2`, `cp0003_tutorial_181`). Cost `attach_gear_coin` = 10,000 **FOL**. Answers `AddGearInfoList` (the gear, now attached), `UpdateGearList` (the destroyed one), `UpdateAttachedGearInfoList`, `Item`. | slot/kind/destroy (a)+(b); FOL (d: the key says coin, but the only gear shortage text is `uimsg_gear_fol_shortage`); slot base (d) |
| **RemoveGear(weapon):** one `gear_remove_gear_item` (`item_grease`, ウェルチ特製グリス) per request (the dialog's 必要数 1), the gears go back to the free list (`OnRemoveGearRes` zeroes `player_item_id` / `slot_index`; `uimsg_gear_slot_remove_success` ギアを入手しました). The screen sends the **weapon's** uid; all its gears come off. A gear's uid is accepted too: that gear comes off. Re-verified in game by `growth_session.sh` (agent a4-helpers, 2026-09-30: "RemoveGear: 1 gear(s) off weapon", the grease used, the gear back in the list). | (a)+(b); a gear's uid (d) |
| **SellGear(uids):** free gears only, `master_item.sale_fol` each (the `weapon_gear_item`'s for factor gears). Answers `SellResult` and `UpdateGearList`. | (a); attached refused (d) |
| **UpdateGearStock:** `gear_stock_max` is the **maximum** (b: `CParameterUtility::MaxGearFrame`, default 300), +`gear_stock_up_num` for `gear_stock_use_coin` 紋章石 (b: `uimsg_gear_extension_confimation`). The core already sends `Player.gear_stock` = the maximum, so the request is refused (11006). | (a)+(b); start capacity (d) |
| **GenerateGear(base weapon, carrot, materials) (ギア精製):** up to five materials (gears or weapons, `item_image1..5`), at least one item selected (`cp0003_tutorial_186`); locked / equipped weapons refused (`uimsg_gear_weapon_lock`); the carrot is optional (`uimsg_gear_create_item`) and must be a `gear_extract_factor1..3_item`. Cost `coin_for_generate_gears` 10,000 FOL (b: `UpdatePurificationMenu` compares the FOL with the cost; d: flat). | (a)+(b) |
| Rank value = `(int)((Σ material rarity × 0.01 + 1.0) × (base attack + base intelligence)) + rare_factor_for_normal_gear (30) × Σ material rarity`; the `master_gear_probability` row with the largest `rank_threshold` below it gives the rarity rates `rank1..5_rate` (percent) (b: `CCustomGear::UpdatePurificationPlate` builds exactly this query and shows these rates as the 完成ギア期待値). Below every threshold: the lowest row. | (b); fallback (d) |
| The base weapon's attack / intelligence at its level: `master_item.attack`..`attack_max` linearly over levels 1..`level_max` of its rarity. | (d) (the client's `ItemModel::GetDetail` wasn't read) |
| The gear: `master_gear_lottery` `gear_purification_<rarity>` of the base weapon's kind (without a base: the first material's kind), open at the clock, by `rate_weigh`. | (a); no-base kind (d) |
| Factor extraction from the base weapon: chance `min(p × Σ rarity × 0.01 + p, 100)` % (b: same function). `p` = `extraction_facter_<n>` for n = min(limit break, 2) + 1 (d: the client indexes a rate list by the base's limit break; that the list is these keys in order is assumed). Extractable slots: `factorN_id` set, `factorN_limit_break` ≤ the limit break, `factorN_lock` = 0 (a; b: `uimsg_gear_create_item_warning`). The carrot N picks slot N (a+b: `cp0003_tutorial_188`), else a uniform slot (d). The factor gear comes **in addition** to the gear (d). | (b)/(a)/(d) |
| The base weapon and all materials are used up (b: `uimsg_gear_create_warning` 素材にした武器やギアは失われます; d: the base too). Gear set in a weapon that is gone (sold, a compose or grade-up material, a purification's base or material) goes with it: the state's `gear_items.item_uid` → `items` ON DELETE CASCADE (PLAN-schema S5; before S5 the gear list deleted such gear when it was next built). | (b); base, orphan gear (d) |
| **Barney chance** (バーニィチャンス, agent a4-helpers; `api/items/gear.cpp` "barney chance"): `master_gear_barney_chance` holds groups of three rows, one per `barney_chance_type` 1..3 (normal / good / excellent), each with a `mood_rate` and a `mutation_rate`. In every group the three `mood_rate`s sum to 100 (the undated `default` group 70/25/5; event groups e.g. 0/0/100) and the `mutation_rate`s rise with the type (10/30/60; `gear_20201126` 100). | (a) |
| What the client shows (3.7.0): the purification menu's icon `Image_chance1` = `icon_chance1..3.png` from CParameterManager+0x91c0 = **`GearBarneyChanceInfo.barney_chance_type`** (one step higher when a selected material has the flag at tItemData+0x22d) (`CCustomGear::UpdatePurificationMenu`); after `GenerateGear`, when **`GearGenerationInfoResult.is_barney_chance`** (+0x8ef0) is set, the gear cut-in (`CCustomGearCutIn`) starts at the first new gear's rarity − 1 and plays its rank-up. So `is_barney_chance` means "this gear was raised a rarity". Neither rate is read by the client. | (b) (`work/decomp/a4-helpers-gearui`, `-cutincaller`, `-cutin`) |
| The open group: the dated group whose `opened_at`..`closed_at` holds the event clock, else the undated `default` group. The **mood** (the chance type) is drawn from it by `mood_rate`, kept (table `gear_barney`) until the next `GenerateGear` or until another group opens, and sent as `GearBarneyChanceInfo` {`barney_chance_group_id`, `barney_chance_type`} with every full-state response, `GetGearInfo` and `GenerateGear`. | dates (a); mood as a weighted draw, when it's redrawn, where it's sent (d) |
| A generation raises the drawn gear a rarity (a new draw from `gear_purification_<rarity + 1>`, when there is one, below rarity 5) with the current mood's `mutation_rate` percent; the result's `is_barney_chance` says whether it did, `barney_chance_type` is the mood used; then the next mood is drawn. Test `items/gear-barney-chance`. Seen in game (agent a4-helpers, `growth_session.sh`): with the default group the purification menu shows the plain Barney (type 1, "…"); with `--clock "2020-12-01 12:00:00"` (`gear_20201126`) it shows the sparkling バーニィチャンス! icon (type 3), and the purification's cut-in plays the raise (rarity 1 → ★2). | (d) for the reading of `mutation_rate`; the display (b) |
| Answer: `GearGenerationInfoResult` {`is_barney_chance`, `use_master_item_id` = the carrot, `barney_chance_type`, `AddGearInfoList`, `CDeleteItemList` (the weapon uids), `UpdateGearList` (the material gears)}, plus top-level `AddGearInfoList`, `UpdateGearList`, `Item`, `StockItem`. | fields (b); `CDeleteItemList` shape (d) |
| Refusal codes: 10208 bad arguments / slot / kind, 10204 locked or equipped, 10206 no grease / carrot, 10710 FOL short, 11006 stock at maximum. | (d) (the texts are (a)) |

<a id="storage"></a>
## Storage: the equipment storage and the overflow box
Code: `server/src/api/storage/` (`storage.cpp`: the equipment storage 装備倉庫; `one_time.cpp`: the overflow box 一時保管庫). The item menu's 装備倉庫にしまう / 取り出す / 売却 and 一時保管庫から取り出す screens (`CItemStorage`). State (schema version 15): `items.stored_at` (NULL: in the inventory; else the deposit time) and `one_time_storage` (one row per master item: `num`, `is_new`, `updated_at`).

<a id="storage-client"></a>
### What the client keeps (b)
- `StorageItem` / `OneTimeStorageItem`: arrays of `CStorageItemInfo` (CItemInfo's keys plus `update_at_time`, a u64 number: `CStorageItemInfo::Initialize` @014ff30c, `CParameterParser::GetValue<unsigned long>`). `UpdateStorageItem` / `UpdateOneTimeStorageItem`: maps {key: CStorageItemInfo} (`IInfoBaseMap<u64, CStorageItemInfo>`: an array isn't read, `DeserializeArray` @0166be20 returns 0; the key a number or a numeric string). `UpdateStorageLockList`, `OneTimeStorageItemClearNewList`, `AddOneTimeStorageInfo`: arrays of u32.
- Deposit / withdraw / sell answers are applied by `CApiNotify::AddStorage` (@014d437c: the entries join the storage list and leave the item list, by id) and `DeleteStorage(bool)` (@014d4864: back to the item list, or (sale) just out of the storage). The overflow box's withdraw answers by `DeleteOneTimeStorage` (@014d4e44: the entry with the same **master_item_id** is removed when its `num` is 0, else gets the new `num`, `is_new`, `update_at_time`) and `AddItem` (@014c207c).
- So the overflow box holds **one entry per master item with a count**; its ids (WithdrawItemFromOneTimeStorage's `id`, the Bulk ids, ClearNew's ids) are master item ids (`CItemStorage::Progress` @01f43efc sends the entries' master ids).
- `AddItem` is a map {uid: CItemInfo} (`CAddItemList`, `IInfoBaseMap<u64, CItemInfo>`: its `DeserializeArray` @0163d574 returns 0). The overflow box's withdraw sent it so first; since agent `server-u-stamps` every answer does ([Conventions](#conventions), `ext::add_items`).

<a id="storage-rules"></a>
### Rules
| Rule | Label |
|---|---|
| `Player.storage_stock` = 100 (`CItemStorage::GetStartStorageItemCount` @01f4623c; `GetMaxStorageItemCount` @01f45f50 reads `storage_stock`, CParameterManager+0x948; the screen shows the rest as `+N`, `GetExtendStorageItemCount`) + `master_global.subscription_storage_stock` (400) while a pass with `master_subscription` type 2 runs (the Galaxy Pass: `subscmsg_gpass_warehouse_title` 倉庫装備所持数＋４００個). Kept so by the user's decision (2026-10-05): the evidence-based 100, +400 with the Galaxy Pass (`--galaxy-pass`), not the earlier assumed 500. | (b) + (a) |
| **DepositItem(uids):** items of the inventory only; an equipped one (a character's or a party set's) is refused with 10203 (b: the deposit list leaves them out, `CItemStorage::GetAllItemList` @01f409a4 skips `is_equip` and the party sets' items; a: the text 装備中のアイテムが含まれています). A locked item may be deposited and keeps its lock (b: `AddStorage` copies the whole CItemInfo). More than `storage_stock` stored is refused with 10211 (a: 倉庫枠が不足しています; b: the client's own check, `uimsg_equipstorage_itemmax_error`). | (b) + (a) |
| **WithdrawItemFromStorage(uids):** more than `item_stock` in the inventory is refused with 10202 (a: 装備アイテム所持枠が不足しています; b: `uimsg_equipstorage_out_itemmax_error`). A storage over its slots (a pass that ended) still lets items out and be sold (a: `subscmsg_gpass_warehouse_manual`). | (a) + (b) |
| **SellItemsFromStorage(uids):** each pays what `SellItem` pays (b: `tItemData::SellingPrice`, one function: `stored_item_sale_fol`); a locked one is refused with 10204, as in the inventory. Answers `UpdateStorageItem` and `SellResult` as SellItem's. | (b); the lock (d) |
| **Lock / UnlockStorageItem(uids):** the item's own lock (`items.locked`); answered as `UpdateStorageLockList` (the uids as u32: `OnLockStorageItemRes` @014d58d0 compares them with the u64 id; the local uids fit in 32 bits). Uids not in the storage change nothing. | (b); unknown uids (d) |
| A stored item isn't in the inventory: not in `Item`, not equippable, composable or sellable through the inventory's APIs (a: `cp0003_tutorial_151` 装備倉庫の中に入っている武器やアクセサリーの装備や強化はできない). | (a) |
| **Filling the overflow box:** a weapon or accessory that a grant (presents, drops, the shops, the exchange: the core's `grant`) or a gacha draw (`draw_weapon`, box gacha) would add to a **full** inventory (equipment count + 1 > `item_stock`: `CItemNumWarning::IsWarningDraw` @01b42884) goes to the box instead (a: `cp0003_tutorial_160`, `uimsg_gacha_wapon_itemmax`, `uimsg_itemexchange_wapon_itemmax`, `uimsg_pshop_wapon_itemmax`: equipment beyond the slots goes to the box). The client lets a weapon gacha run on a full inventory while the box is open (`CGacha::IsNumWarning` @01ab6e54) and lets a present / a mission start at exactly full (`CPresentbox::IsNumWarning` @01e0cd14 warns only when over). The answer lists each unit's master id in `AddOneTimeStorageInfo` (top level, and in `PresentGetResult.result`); a gacha's `GachaItems` entry for it has `player_item_id` 0. | (b) + (a); the answer's shape (d) |
| The player's その他設定 options (`master_config` `is_one_time_storage`: gacha draws, `is_one_time_storage_except_gacha`: the rest; `CUIUtility::IsOneTimeStorageEnable` @01eea5f8 / `IsOneTimeStorageExceptGachaEnable` @01eea8e0) send every piece of equipment of that source to the box while on, room in the inventory or not (`storage::to_one_time_storage` reads them with `settings::config_on`, [Settings](#settings)). Test `storage/one-time-options`. | (b) |
| **GetOneTimeStorageInfo:** one entry per row: `id` = the master item id (the entries have no uid), level 1, unboosted, unlocked, `num`, `is_new`, `update_at_time` = the row's last change in seconds, **unique per row** (one second after the latest when two would be equal: `CItemStorage::ItemInfo`'s constructor @01f46244 puts it where the other lists keep the uid and `CUISort::SortFilter_Weapon<CItemStorage::ItemInfo>` @01f438ac finds entries by it). | (b); the values (d) |
| **Withdraw / BulkWithdrawItemFromOneTimeStorage(ids, counts):** a count of 0 or more than held, or an id not held: 10206; an id twice counts together; more than `item_stock` in the inventory: 10202 (b: `uimsg_equipstorage_out_itemmax_error`). Each unit becomes a new owned item (level 1; content type 1, drop type 0). Answers `UpdateOneTimeStorageItem` {master id: the entry with the count left, 0 when gone} and `AddItem` {uid: CItemInfo}. | (b); codes and the new items' values (d) |
| **ClearNewOneTimeStorageItem(ids):** clears `is_new` of the entries held; answers `OneTimeStorageItemClearNewList` with them. | (b) |

Tests: `storage/deposit-withdraw`, `storage/sell-lock`, `storage/stock-caps`, `storage/one-time` (`server/src/api/storage/storage_tests.cpp`), `server/schema-migrate-v15`; the `storage` replay corpus (50 weapon draws fill the inventory, a draw into the box, every API with its refusals); session `storage` (`port/scripts/storage_session.sh`, in-process and `--target port-server`: deposit, withdraw, sell, a present's weapon into the box on a full inventory, the box listed and its badge cleared, then after a re-login the storage and the box still hold their items and the box's weapon is taken out).

<a id="storage-register"></a>
### Player-visible (c) and (d) rules (storage)

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Storage | a locked stored item can't be sold (10204) | (d) | as in the inventory; the client's sale list wasn't read |
| Overflow box | a present / drop / shop / exchange / gacha weapon on a full inventory goes to the box; the gacha's result entry has no item id (`player_item_id` 0); the present receipt dialog doesn't mention the box | (d) | the answer's shape; the client's messages for the box (`uimsg_gacha_wapon_itemmax` ...) aren't shown yet: which key they read wasn't found |
| Overflow box | withdrawn items are new level-1 items; refusals 10206 (count) / 10202 (slots) | (d) | the box keeps no item's state |

<a id="favor"></a>
## Favor
Code: `server/src/api/favor/` (the favorability rules; UpdateFavorByTap, UseFavorItem).

<a id="favor-rules"></a>
### 8. Favor (affinity, 好感度)
Implemented in `server/src/api/favor/favor.{h,cpp}` (agent `restore-favor`), called from `server.cpp` at the player load, the battle status, MissionEnd and the favor APIs. The 3.7.0 client's own favor getters show the levels the server sends (the client before the rebase didn't: `docs/history/server-rules-3.8.0.md`).

<a id="favor-state"></a>
#### State
- One row per **same_role_id** in the server table `favor` (`same_role_id`, `point`, `tap_count`, `tapped_at`, `event_drop_at`; the two times are seconds on the server clock, NULL for never, formatted at the boundary: `event_drop_at` was the sent text, `''` for never, and `tapped_at` 0 for never, until schema version 9). The client keys its favor map by same_role_id: `CParameterManager`+0x8410, `map<u64, CPlayerCharacterFavorInfoElement>`, and the favor results of MissionEnd / UpdateFavorByTap / UseFavorItem are written into it by that id. **(b)** So every version of a character (all roles with the same `master_role.same_role_id`) shares one favor. **(b)**
- Seed: no favor, 0 points for everyone. **(d)** The 3.7.0 save has no favor data.
- Only characters with a `master_favor_schedule` row (id = same_role_id; 96 rows, 95 same roles in `master_role`) have favor. **(a)** The client's `CParameterUtility::GetEnableFavorability` makes the same test. **(b)**

<a id="favor-levels"></a>
#### Levels
- **Thresholds:** `master_favor_level.next_favor_point` of level L is the **cumulative** point total needed for level L+1: 10,000 / 30,000 / 60,000 / 90,000 / 99,999,999. **(a)** for the values. **(b)** for reading them as cumulative: `CHome::GetFavorabilityPointPersent` draws the home gauge as `points / next[1]` at level 1 and `(points - next[L-1]) / (next[L] - next[L-1])` above.
- **Level** = 1 + the number of thresholds reached, capped at the character's maximum. **(a)+(b)**
- **Maximum:** `master_favor_schedule.favor_max_level` (4 for every row), or `next_favor_max_level` (5) from `next_opened_at` on (always empty in 3.7.0). **(a)** Same rule as `GetEnableFavorability`. **(b)**
- **Points stop** at the threshold of the maximum level (60,000 while the maximum is 4). **(d)** Nothing shows points past the maximum: the home gauge is empty at the maximum level. **(b)**

<a id="favor-gains"></a>
#### Gains
- **Battle** (MissionEnd): every party member with favor gains `master_favor_battle_effect.favor_up_point` of the row with `play_type` 0 (single play; 1 = multiplay host, 2 = guest) and `use_stamina` = the stamina the MissionStart took (2 → 12, 10 → 60, 20 → 119). **(a)** A stamina with no row uses the largest `use_stamina` below it. **(d)** (every value 0..300 in use has a row.) A same role present twice in the party gains once. **(d)**
- **Home tap** (`UpdateFavorByTap(u32 same_role_id)`, sent by `CHome::UpdateFavorPointByTap` when the home character is tapped): `master_global.favor_tap_bonus_point` = 50 points. **(a)** At most `favor_tap_bonus_limit` = 5 taps per character per day. **(a)** for the numbers; **(b)** for "per character": the favor element has its own `favor_up_count_by_tap` and `updated_by_tap_at`.
  - The day starts at `master_global.login_bonus_reset_hour` (04:00) in the server's local time, like the other daily counters (see Conventions). **(d)** for applying it to taps.
  - A tap past the limit, or on a character without favor, changes nothing and answers the current level and points. **(d)**
- **Favor items** (`UseFavorItem(u32 master_item_id, u32 count, u32 same_role_id)`): `master_favor_item_effect.favor_up_point` per item. **(a)** `target_type` 0 works on any character; otherwise only on the row's `master_role_same_role_id`. **(d)** for that reading of `target_type`. The count is capped by the stack held; the stack is debited. **(d)**
- The favor login bonus (`master_favor_bonus`, `StaminaHealByFavor`) is in `api/daily/premium_and_favor_bonus.cpp` ("Premium and favor login bonuses") and the favor event drops (`added_event_drop_at`, `RemainingEventDropBonusCountByFavor` consumed) in `api/events/favor_drop.cpp` / `favor.cpp` ("Event extras"); tests `daily/premium-favor-bonus`, `events/favor-drop`.

<a id="favor-responses"></a>
#### Responses
- **Player load** (`NoLoginStart`, `Login`, `GetPlayer`, ...):
  - `PlayerCharacterFavorMap`: a map keyed by same_role_id (as a string) of `CPlayerCharacterFavorInfoElement` {`master_role_same_role_id`, `favor_point`, `favor_level`, `added_event_drop_at`, `favor_up_count_by_tap` (today's), `updated_by_tap_at`}, one per owned character with favor (37 for the 3.7.0 seed). **(b)** for the shape: property names from the class's `Initialize`, map shape as the other `...Map` infos.
  - `RemainingUpdateFavorCountByTap`: the taps left today for the **home** character. **(d)** The client keeps one number (`CParameterManager`+0xb660) and needs it non-zero to send a tap (`CHome::IsAddFavorPointByTap`). **(b)**
  - `RemainingEventDropBonusCountByFavor` = `master_global.favor_event_drop_bonus_limit` (3). **(a)** for the value, less today's favor event drops ("Event extras"; agent events-extras). The client needs it non-zero to show the party screens' favor drop icon (`GetFavorDropIconImageName`). **(b)**
- **MissionEnd:** `MissionResultCharacterFavor`, keyed by same_role_id: {`id`, `master_role_same_role_id`, `before_favor_level`, `before_favor_point`, `after_favor_level`, `after_favor_point`, `added_event_drop_at`}. `CApiNotify::OnMissionEnd` copies the after values into the favor map. **(b)**
- **UpdateFavorByTap:** `UpdateFavorByTapResultInfo` {`same_role_id`, `favor_level`, `favor_point`, `RemainingUpdateFavorCountByTap`}; the handler writes them into the favor map and +0xb660. **(b)**
- **UseFavorItem:** `UseFavorResultInfo` {`same_role_id`, `favor_level`, `favor_point`} and `StockItem` (the whole stack list). **(b)** for the result keys; **(d)** for sending the whole list.
- **Battle status** (`BattleParameter.PlayerCharacter[].favor_level`): the member's favor level. **(b)** for the key.

<a id="favor-effects"></a>
#### Effects (client-side, from the master data)
`master_favor_level.assist_cut_in_rate`, `ap_bonus` (read by `GetFavorApBonus`, levels 4 and 5) and `event_drop_bonus` **(a)**; the client applies them from the favor level it reads. The favor AP bonus isn't added to the server's battle status yet.

<a id="favor-achievements"></a>
### Favor achievements (`api/presents/achievements.cpp`, `api/favor/favor_api.cpp`)
| Rule | Label |
|---|---|
| `GetNotReceiveGoaledFavorabilityAchievement` isn't an API: it is the client helper `CParameterUtility::GetNotReceiveGoaledFavorabilityAchievement`. It walks the `Achievement` state (CParameterManager+0x67c8) for entries with `is_goal`, `status` not 2 / 3 and a `limit_at` not past, keeps the type-52 ones (`GetParameterListFromAchievementIDAndType(52)`) and builds the reward popups. `CAdjutantSelect::Progress` (the adjutant select) then sends `AchievementListReceive` with their ids; `CHome::UpdateBadge` counts them for the home badge. Neither sends `AchievementActiveList`. | (b) |
| So the server sends the `Achievement` state with every full-state player response and with the responses that change favor (MissionEnd, UpdateFavorByTap, UseFavorItem). | (b); which responses (d) |
| Type 52 (`Favor_role_<person>_NN`, 368 rows): `target_id` is a **same_role_id** (`target_id_label` = `master_role.same_role_id_label`); progress = the favor points of that same_role_id, goal 10,000 / 30,000 / 60,000. The earlier code looked it up as a role id and never matched. `limit_at` = `closed_at` (2030-12-13). | (a) |

<a id="favor-register"></a>
### Player-visible (c) and (d) rules (favor)

| Rule | Label |
|---|---|
| Favor: seed 0 points; points stop at the max level's threshold; the tap day starts at 04:00 local; the load's tap count is the home character's; favor item `target_type` reading | (d) (agent restore-favor, section 8) |

<a id="daily"></a>
## Daily: login bonuses
Code: `server/src/api/daily/` (login bonus, premium and favor login bonuses, StaminaHealByFavor).

<a id="login-bonus"></a>
### 7. Login bonus
- **Daily trigger:** the first request after the 04:00 JST reset (1: conventions) counts a login day (b: `LoginBonusResetHour`).
- **How the client shows it** (b: `CPopupManager::CheckStart`, `LoginBonusModel::GetList(true)`): on entering home, the popups are checked in order — notice board (once a day, local KVS), premium login bonus (`PremiumLoginBonus` entries with the received flag), the premium pass ending, **login bonus**, two favor popups, guide information, ... The login-bonus popup opens when `data.LoginBonus` (CLoginBonusInfo {`master_login_bonus_id`, `current_idx`, `is_received_now`}) has an entry with `is_received_now` set whose master row is open (`LoginBonusModel::EnableParameter`); the page shown is `current_idx` (b: `CLoginBonusOperater::GetCurrentIndex`). `LoginBonus` is not reset between responses (api.md "Player state"), so send `is_received_now` = true only in the response that grants the day's bonus, and false afterwards (d). Send it in the first home response of the day: on 3.7.0 the title's NoLoginStart grants the day and the Login right after it reports it again (`api/daily/login_bonus.cpp`) (d). The Other menu reopens the popup (`COtherMenu::RequestLoginBonus`) (b).
- **Which bonuses:** every `master_login_bonus` row open now (a). The permanent one is `login_bonus` (`is_loop` = 1, 28 days: coins 500/250, heal items, FOL 50,000, gacha tickets, `item_limitbreak_03`, ...) (a). Event bonuses (`is_loop` = 0) stop after their last `order_idx` (a).
- **Day index:** `current_idx` advances by one per login day, wrapping to 1 after the last `order_idx` when `is_loop` (a: columns; c: SOA's login bonuses counted login days, not calendar days).
- **Reward:** the `master_login_bonus_contents` row with `order_idx` = the day, sent to the present box (c).
- **Premium login bonus** (`master_premium_login_bonus*`): tied to a purchased pass (content type 11); off unless the player owns the pass (d). Implemented in `api/daily/premium_and_favor_bonus.cpp` (see [Premium and favor login bonuses](#premium-and-favor-bonuses)).
- **Favor login bonus:** `master_favor_bonus` / `_contents`, limited by `favor_login_bonus_limit` = 5 (a); see 8. Implemented in `api/daily/premium_and_favor_bonus.cpp` (see [Premium and favor login bonuses](#premium-and-favor-bonuses)).
- **Implemented** by agent server-growth's `server/src/api/daily/login_bonus.cpp` (agent restore-home's parallel `home.cpp` was dropped at the merge; its description below matches the rules both used). `PresentBoxCount` is sent on every player load (`server/src/api/player/player_info.cpp`):
  - Every `master_login_bonus` row open at the server's clock (a). On the first player load of a login day (the day starts at `master_global.login_bonus_reset_hour` = 4, local time: (a) + (b) `CParameterUtility::LoginBonusResetHour`), its next page is granted: page = last granted + 1, wrapping to 1 after the last `order_idx` when `is_loop`, none after the last page otherwise (a)+(c). State: table `login_bonus` (id, day = last page granted, last_at).
  - The page's `master_login_bonus_contents` rows go to the present box with `reason_type` 1 and the line "<name> N日目" (`Present_box_1`; see [Present box lines](#present-box-lines)).
  - `LoginBonus` lists every open bonus that has granted a page: `{master_login_bonus_id, current_idx = the page, is_received_now}`; `is_received_now` is true only in the granting response (d). `current_idx` as the 1-based `order_idx` is (d). `IsLoginBonus` = a page was granted in this response (d).
  - `PresentBoxCount` = the unreceived presents (b: the present badge, `CParameterUtility::GetPresentCount`).
  - **The popup checks are the client's.** `CPopupManager::CheckStart` only checks the popup kinds whose bit is set in its flags (+0x3c); 3.7.0's `CPhase_Login::Progress` sets them (`CPopupManager::AddPopup()`, bits 0x7b) after the login when the tutorial is cleared. The server only sends the data. (b)

<a id="login-bonus-modules"></a>
### Login bonus as the growth and economy modules built it
- On a full-state player response, each `master_login_bonus` open at the server clock (a) advances one day the first time after the daily reset at `login_bonus_reset_hour` = 04:00, local time (a+b; d: local time, as the core's clock). The day's `master_login_bonus_contents` row (`order_idx` = the day) goes to the present box with `reason_type` 1, `reason_param` = the bonus id (c: the box; d: the reason values, after master_text `Present_box_1` = "%s %d日目"; the box still shows the line `free_text_message_id` for it, so the text lookup isn't understood yet). Looping bonuses restart at day 1 after the last `order_idx`; others stop (a+c).
- `LoginBonus` lists the open bonuses with a day: {`master_login_bonus_id`, `current_idx`, `is_received_now`}; `is_received_now` only in the response that granted the day (b: the popup condition; d: only then).
- **The popup.** 3.7.0's login arms the popup checks itself (`CPopupManager::AddPopup()`); the server only sends `LoginBonus`. The popup shows the day's reward; receiving it in the present box credits it (verified: 紋章石 10,000 → 10,500 on day 1).
- **Player.tutorial_status = 9** when no other module set it: (b) `CParameterUtility::IsTutorialClear` = `tutorial_status` ≥ `CPhase_TutorialNext::LastMemId()` = 9, and the popups only open past the tutorial; (d) the seeded rank-87 account has finished it.
- The premium login bonus needs a purchased pass: not granted (d). The favor login bonus: "Premium and favor login bonuses" below.

<a id="premium-and-favor-bonuses"></a>
### Premium and favor login bonuses (`api/daily/premium_and_favor_bonus.cpp`)
| Rule | Label |
|---|---|
| **Premium login bonus pass:** content type 11, `content_id` = the `master_premium_login_bonus` row. It was sold in `master_direct_item_shop` (`pshop_ploginbonus_001`), which the port can't sell, so the bonus is **off unless the state holds a pass**: a type-11 grant (e.g. a present) records one (table `premium_pass`). | (a); off by default (d) |
| With a pass whose master row is open at the clock, each login day (after the 04:00 reset, as the login bonus) grants the next page of `master_premium_login_bonus_contents` (`order_idx`, 14 pages) to the present box, line `Present_box_6` "プレミアムログインボーナス N日目". It doesn't loop (the table has no `is_loop`). | (a); no loop (d) |
| `PremiumLoginBonus` lists the passes with a page: CPremiumLoginBonusInfo {`player_id`, `master_premium_login_bonus_id`, `current_idx`, `created_at`, `updated_at`, `is_updated`, `is_next`}. The home popup (`CPopupManager::CheckStart` case 1) shows the entries with `is_updated` (`PremiumLoginBonusModel::GetList`), so `is_updated` is true only in the granting response. `is_next` = false. | fields and popup (b); `is_next` (d) |
| **Favor login bonus** (フレンドリープレゼント): `master_favor_bonus` tiers need `required_count` characters (by `same_role_id`) at favor level ≥ `required_min_master_favor_level` (4); the open tier with the largest `required_count` the player meets applies (from 2019-03-29 on: 1..30 and 100 characters → 1..3 presents, 10..100 stamina). | columns (a); largest tier (d) |
| Once per login day it draws `present_count` lots from the open `master_favor_bonus_contents` by `rate_weigh` into the present box, line `Present_favor_1` "<name>のフレンドリープレゼント", naming a random qualifying character, sent as `FavorBonusContetsResultInfo` {`lot_character_id` = its uid, `FavorBonusContetsInfoList` [the drawn `master_favor_bonus_contents` ids]}. **The list is u32 ids (b):** `CFavorBonusContetsInfoList` is an `InfoBaseValueArray<u32>` (its vtable's `DeserializeArray` / `Initialize`), `CFavorCharacterLoginBonus::Setup` looks the ids up with `CMasterParameterFavorBonusContents::ParameterByIDList`, and `CPopupManager::CheckStart` case 6 opens the popup only when the list (CParameterManager+0x8658) is non-empty. Until 2026-10-02 the server sent {content_type, content_id, num} objects, which left it empty: the lot character visited the home but the popup never opened. Seen on screen since (agent open-issues): "アンヌのフレンドリープレゼント! GRDシード ×3" after the notice board; `control/flowctl.py login-popups` closes it. | lot fields (b: schema, list type); once a day, the named character (d) |
| **StaminaHealByFavor():** once per day, the tier's `stamina_recovery_value` is added to the stamina (overflow kept, the regeneration clock restarts at the maximum as for the other heals); `IsHealedByFavor` says whether it did. `Player.favor_bonus_received_at` / `stamina_update_by_favor` report the last bonus / heal. | value (a); once a day, the Player times (d) |
| `master_global.favor_login_bonus_limit` (5) is a **server-side key**: the client never reads it (its string is in neither the 3.7.0 nor the 3.8.0 library <!-- 380-ok: evidence from both libraries -->; nor are `favor_tap_bonus_limit` / `favor_event_drop_bonus_limit`), and `CFavorCharacterLoginBonus::Setup` lists one character's lots however many there are. Read like its siblings (5 taps a day, 3 event-drop bonuses a day) as a per-day cap: at most that many favor-login-bonus lots a day (`min(present_count, limit)`). With the 3.7.0 tiers (`present_count` 0..3, once a day) it never binds. With the seed save nobody has favor yet, so the favor bonus starts once characters reach level 4. | key and value (a); not client-read (b); the reading (d) |
| The home popups of `CPopupManager::CheckStart` cases 4 and 5 (CParameterManager+0xb4a0/+0xb4d0, +0xb500/+0xb530) are the **rental bonus** (`RentalBonus` / `RentalCount`) and the **Sphere 211 rental bonus** (`Sphere211RentalBonus` / `Sphere211RentalCount`), not favor popups; the favor login bonus popup is case 6 (`CFavorCharacterLoginBonus`, the list at +0x8658). See "Rental helpers". | (b) |

<a id="daily-register"></a>
### Player-visible (c) and (d) rules (login bonuses)

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Login | `LoginBonus` sent in the first home response of the day, `is_received_now` only then | (d) | the popup condition is (b) |
| Login | rewards go to the present box; day index counts login days | (c) | |
| Login | a bonus day granted by `NoLoginStart` is received-now again on the next `Login` | (d) | 12; lets the 3.7.0 login's popup show it |

<a id="presents"></a>
## Presents and achievements
Code: `server/src/api/presents/` (PresentList, GetPresent(Array), the present texts, achievements).

<a id="presents-rules"></a>
### 6. Presents
- The present box holds `CPresentBoxInfo` {content, num, reason_type, reason_param, message, deadline_at}. Deadline = received + `present_deadline_day` = 30 days (a: key; d: expired presents are dropped). At most `present_list_limit` = 100 listed and `present_receive_limit` = 10 received per request (a).
- Receiving applies the grant (1: content grants) and returns the **whole remaining box** in `PresentGetResult.add` (b: `ApplyGetPresent` replaces the box with it; notes).
- Rewards that go to the box: login bonuses, achievements, rank rewards, overflow from caps (c).

<a id="present-list"></a>
### Presents (`PresentList`)
- `PresentBox` lists the unreceived presents: id, content type and id, num, reason, and an empty deadline.
- **Receiving** (`GetPresent(u64 id, ...)` / `GetPresentArray(vector<u64>)`): each unreceived present's content is granted as a drop is, and marked received.
  - Answers `PresentGetResult`: `get` = the ids received; `add` = the whole box left, since `CApiNotify::ApplyGetPresent` refills the box from it; `result.fol` / `free_coin` = what was gained.
  - Also `AddItem`, `StockItem` and `AddCharacter` when they changed.
  - For `GetPresent` only the first id is read (its varargs aren't captured). **(d)**

<a id="present-box-lines"></a>
### Present box lines (`present_texts.cpp`)
| Rule | Label |
|---|---|
| The box shows each present's `free_text_message_id` **string** verbatim as its line: `CPresentbox::CreateAllPresentList` copies it (CPresentBoxInfo +0x1f0) into PresentParameter+0x68 and the list cell sets it as the label text. `reason_type` / `reason_param` are never read, and the client has no `Present_box*` key. So the server sends the finished line (it used to send 0, an empty line). | (b) |
| The lines use the master_text templates: login bonus `Present_box_1` "%s %d日目" (bonus name, day; stored when granted), mission first clear `Present_box_2` "%sより" (mission name), achievement `Present_box_3` "%s" (achievement name), premium login bonus `Present_box_6` "%s %d日目", favor bonus `Present_favor_1` "%sのフレンドリープレゼント" (the character's `master_person` name), anything else `Present_box_99` 運営からのプレゼント. | templates (a); which template per reason (d) |
| `reason_type` numbers are the server's own: 1 login bonus, 2 mission clear, 3 achievement, 6 premium login bonus, 7 favor bonus (`ext.h` `PresentReason`). A stored line (the present's `text` column; table `present_texts` until schema version 8) wins over the one built from the reason. | (d) |

<a id="core-response-fixes"></a>
### Fixes to the core's responses (server.cpp)
- **Presents' `deadline_at`** = created + `present_deadline_day` (30) days (a). (b) `CPresentbox::CreateAllPresentList` lists only presents whose deadline isn't past, and an empty string parses as 0, so the core's presents were hidden.
- **`StockItem.num`** = the count held. (b) CStackItemInfo's fields are master_item_id, **num**, item_type, sort_name_idx, is_new, use_count, player_id; the shops and exchanges show `num` as 所持数. `use_count` is still sent as before.
- **`Item`** also carries `level`, `is_lock`, `is_equip` and `num` = 1 (b: CItemInfo's fields).

<a id="achievements"></a>
### 10. Achievements (勲章 / 実績)
- `master_achievement` (5,628) and `master_achievement_secret` (174): `type` (the event counted: e.g. 8 clear mission `target_id`, 11 own character, 16 ..., 24/25 event items, 52 favor level ...), `target_id`, `goal_count`, `is_count_reset`, `default_release` (active from the start), `next_achievement_id` (chain), `open_mission_id`, `daily_pattern_id` / `weekly_pattern_id` (daily / weekly ones reset), reward (`content_type`, `content_id`, `num`), `opened_at` / `closed_at` (a).
- **Types**, pinned from each type's name texts (`name_message_id` → `master_text`) and `target_id` (a+text; the counted quantity is `goal_count`):

| type | rows | counts | target_id |
|---|---|---|---|
| 1 | 15 | character gacha draws | gacha label |
| 2 | 13 | character boosts (強化) | – |
| 3 | 13 | evolutions (to rarity target) | rarity |
| 4 | 7 | character limit breaks | – |
| 5 | 35 | weapon boosts | – |
| 6 / 7 | 37 / 17 | weapon limit-break raises (武器を N回上限解放する; one per copy or fitting limit-break item fed, see "Achievements" under "Growth and economy") / alchemy (grade-up, 錬成) | – |
| 8 | 1,785 | clears of mission `target_id` | mission label |
| 9 | 12 | all missions of an area cleared (踏破) | area label |
| 11 | 232 | own / obtain character chips | chip or role label |
| 12 / 13 | 43 / 42 | hits in one battle / total hits | – |
| 14 | 34 | rush-combo chain length | – |
| 16 | 94 | multiplayer wins | `all` or mission |
| 17 | 69 | FOL obtained | – |
| 18 | 5 | players followed | – |
| 19 | 25 | daily achievements completed | pattern |
| 24 | 183 | clears of an event mission group | event label |
| 25 | 1,484 | event items collected (daily challenges) | item label |
| 26 | 5 | box gacha draws | box gacha label |
| 29 / 30 / 31 / 32 | 5 / 1 / 2 / 3 | a character at level N / rarity N / limit break N; a weapon at level N | – |
| 34 | 45 | exchange-shop trades | – |
| 35 | 3 | weapon gacha draws | – |
| 36 | 85 | player rank reached (調査ランク) | – |
| 37 | 235 | clears (event title series) | mission label |
| 38 / 39 | 21 / 6 | accessory boosts / crafts | – |
| 40 | 8 | seed (status) boosts of stat `target_id` | stat index |
| 44 / 45 | 13 / 17 | deep-space exploration rate / expeditions | area label |
| 46 | 34 | story chapter cleared | mission label |
| 48 | 2 | rush assists | – |
| 49 | 2 | role changes | person label |
| 51 | 13 | gears owned | – |
| 52 | 368 | favor points with a character | role label |
| 53 | 12 | characters at favor level `target_id` | favor level |
| 55 | 17 | orders activated (stamp) | order type |
| 58 | 3 | accessory inheritances | – |
| 59 | 45 | damage in an evaluated battle | evaluation label |
| 61 / 62 | 151 / 337 | Sphere211 floor reached / weekly challenge | – |
| 69 | 1 | ★7 evolution | rarity |
| others | ≤ 7 each | anniversary quiz events (4周年記念トレジャーハント) | – |
- Progress is counted by the server as events happen (mission clear, level up, gacha, ...) and sent in `Achievement` / `UpdatedAchievement`; receiving (`AchievementReceive`) grants the reward to the present box and activates `next_achievement_id` (a: columns and schema; c: rewards went to the present box).

<a id="achievements-modules"></a>
### Achievements as the growth and economy modules built them
- **Active list** (`AchievementActiveList(category)`; (b)+(d) the category isn't read, every active achievement is answered: (b) the client merges the answer into its one list (`CApiNotify::OnAchievementActiveListRes` @014df128, CParameterManager+0x67c8) and each screen picks its rows by the master row's own category (`tAchievement::InitializeCategory` → `tAchievement::GetCategory` @0181ce10), so the whole list shows the same screens; (d) what the online server left out per category can't be seen): `master_achievement` rows with `default_release` open at the clock, plus the `next_achievement_id` of received ones; received rows leave the list (a; d: leaving). Each as CAchievementInfo {id, player_id, master_achievement_id, limit_at = closed_at, status (d: 0 in progress, 1 achieved), count (capped at goal_count), is_goal} (b: field names).
- **Progress** is computed from the server state (a: `type`, `target_id`, `goal_count`): 1 gacha draws (of the gacha, or all), 2 boosts, 3 evolutions to the rarity, 4 limit breaks, 5 weapon boosts, 6 weapon limit-break raises (below), 7 grade-ups, 8 and 37 clears of the mission, 11 owns the role, 29 highest character level, 31 highest limit break, 34 exchanges, 36 player rank, 38 accessory boosts, 58 accessory inheritances (`InheritAccessory`), 44 / 45 deep space exploration rate / expeditions (see "Deep space"), 52 favor points of the role's same_role_id. Other types report 0 (d).
- **Type 6, weapon limit breaks** (`weapon_limit_break` counter; fixed 2026-10-03, found by R16): (a) the 37 rows' texts say 武器を N回上限解放する (goal 1 .. 1000) and the hint 同じ武器を強化合成すると、上限解放します; (b) one `ItemCompose` raises the limit break once per qualifying material (`CItemStrengtheningPotal::GetAddLimitReleaseWeaponNum` @01b899d8 adds 1 per material of the base's item id or a limit-break item; `WarningLimitbreak` @01b8a810 warns when the current limit break plus that sum reaches 6; (a) the cap, `master_item_limit_break_level_max`'s highest `limit_break`, is 5). So each raise the server applies counts one (`lb_after - lb_before`, nothing past the cap); accessories count `accessory_limit_break` (no achievement reads it yet). Until then type 6 read `weapon_boost`, which every weapon compose counts, so it completed on any compose. Test `items/limit-break-achievement`. The limit-break items ("hammers": `master_weapon_limit_break` / `master_accessory_limit_break`, matched as in 5.5) raise and count the same way since 2026-10-03 (agent srv-hammers; until then ItemCompose only raised for a copy); test `items/limit-break-items`, replay corpus `hammers`.
- **`Achievement` is a map keyed by the id** (b): the client's `CAchievementActiveInfoList` is an `InfoBaseNumberMap<CAchievementInfo>` whose `DeserializeArray` returns 0 without reading, so the array the server sent until agent a6-deepspace left the client's list (CParameterManager+0x67c8) empty: the 実績 screen (`CAchievementMenu`, `tAchievement::InitializeList`, reached from the deep space screen's 実績 button) said every category was achieved, and the favor-achievement popups had nothing to read. The screen lists the rows whose `master_achievement_id` the map holds and that the master query `platform IS NULL AND help_addr IS NULL AND content_type IS NOT 13` keeps (title rewards are the 称号 menu's), split into イベント / 日替わり / 週替わり / その他 by `tAchievement::GetCategory`. Checked on screen by `deepspace_session.sh` (the expedition achievements achieved, 一括達成 → `AchievementListReceive` → the present box).
- **Starter missions** (スターターミッション: the 39 rows with `help_addr`, which `tAchievement::InitializeStarterList` takes from the `Achievement` map for the home's "Next Mission" popup (b)): a state seeded from a save (meta `seed`: the restored rank-87 account, every planet open) had finished them, so they are left out of the list and their rewards aren't granted again (d). A player the server created (new-player mode) gets them. Without this, the working map made the popup open over home at every return.
- **Receiving** (`AchievementReceive(id)`, `AchievementListReceive(ids)`, `AchievementReceiveList()` = all achieved (d)): only achieved, unreceived rows; the reward (`content_type`, `content_id`, `num`) goes to the present box with `reason_type` 3 (c; d: the reason). Answers `Achievement`, `AddPresent`, `ReceiveAchievementId`, `IsUpdateAchievement`, `PresentBoxCount`. Checked by the unit tests and on screen: the home side menu's 実績 (`port/scripts/home_session.sh`, `26-achievements`; it sends `AchievementActiveList(1)`, the 称号 screen `AchievementActiveList(3)`) and the deep space screen's 実績 (`deepspace_session.sh`, 一括達成).

<a id="presents-register"></a>
### Player-visible (c) and (d) rules (presents and achievements)

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Presents | expired presents dropped after 30 days | (d) | |
| Achievements | a state seeded from a save has the starter missions (help_addr rows) done; they aren't listed | (d) | section 10; else the "Next Mission" popup covers home |

<a id="shop"></a>
## Shops and passes
Code: `server/src/api/shop/` (item shop, exchange, subscriptions).

<a id="shops"></a>
### 9. Shops
- **Item shop** (`ExItemShop`, `master_item_shop`, 293 rows): `price` in coins for `content` × `num` (almost all item sets, type 99) (a: columns; b: in 紋章石, the screen's 必要紋章石, "Shops" below). `limit_count` per period; the client shows `limit_count - num_total` as the remaining count and disables the row at 0 (b: `ItemShopUtility::ItemSetInfo::GetRemain` / `IsEnable`), and hides it outside `opened_at`..`closed_at` (b: `IsWithinDayEnableEmpty`). `reset_type` 2 (10 rows, all `reset_param` 1, `reset_time` 00:00:00) = a **monthly** reset on day `reset_param` at `reset_time`, `loop_count` being the number of months until `closed_at` (a, inferred: rows opened 2019-08-01 / 2020-03-01 / 2020-09-01 have `loop_count` 136 / 129 / 124, i.e. months to December 2030). `interval_day`, when set, = a reset every N days (a: column; d: meaning). Counters go in `ItemShopInfo` {limit_count, num_total, loop_count}.
- **Exchange shops** (`ExshopExchange`, `master_exchange_shop` 1,001 / `_contents` 11,547): pay `ex_num` of `ex_item_id` (event coins, medals) per `num` × content; `ex_limit` caps the total per row (0 = unlimited) (a). `exchange_item_max` = 50 per request (a). Counts in `ExchangeShopExCount`.
- **Direct item shop / coin list / deposits:** the coin shop sells 紋章石 for nothing (the user's decision): [Paid currency](#paid-currency). The direct item shop (premium shop) lists nothing.

<a id="shops-modules"></a>
### Shops as the growth and economy modules built them
- **The item shop list** (b: `CItemShop::CreateItemSetList`): the shop shows the master rows whose ids are in the owned `ItemShopInfoList`; a row missing from it counts as sold out. So the server sends every `master_item_shop` row open at its clock (a: `opened_at` / `closed_at`), in every full-state response and after each purchase. With the host clock (2026) those are the ten monthly `reset_type` 2 rows (until 2030); `--clock` in the service years shows the event rows.
- **CItemShopInfo** (b, same function; `GetRemain` / `IsEnable`): `limit_count` is the count **still available** this period (the client shows master `limit_count` − it as bought); `reset_at` (parsed with `str2time_t`) is shown as the deadline (交換可能期限): the next reset (d for the value). `num_total`: purchases ever (d). The price is in 紋章石 (b: the screen's 紋章石と様々なアイテムを交換します and 必要紋章石).
- **ExItemShop(id)**: open and not sold out (b); `price` coins (a), free first (a: "Stocks and wallet"); `limit_count` 0 = unlimited (d). `reset_type` 2 = monthly on day `reset_param` at `reset_time` (a, inferred, section 9); other rows never reset (d). The content (item sets, type 99, expanded through `master_item_set`) goes straight into the inventory (d). Answers `ItemShopInfo`, `ItemShopInfoList`, `AddItem`, `StockItem`.
- **The exchange shop list** (b: `CShop::Progress` after `CUIUtility::CollectMasterItemExchangeShop`): only the master exchange shops open by the clock whose id is a key of `ExchangeShopExCount` (`CExchangeShopExCountInfoCategoryMap`, `CParameterManager+0x60d0`) are listed. So the server sends every open shop, each with its contents: shop id → contents id → {`ex_count`} (b: the shop keys and `ex_count`, the element's one field; d: the contents-id keys). With the host clock: the permanent weapon-coin shops, the chip shop and the treasured-weapon shop.
- **ExshopExchange(contents id, n)**: the shop and row open (a); n ≤ `exchange_item_max` (a); `ex_limit` caps the total, 0 = unlimited (a); pays `ex_num` × n of `ex_item_id` and grants the content × n (a). Answers `ExchangeResult` {master_exchange_shop_id, ex_item_id, num, AddFreeCoin}, `ExchangeShopExCount`, `AddItem` / `AddCharacter`, `StockItem`.

<a id="paid-currency"></a>
### Paid currency: the coin shop (`server/src/api/shop/coins.cpp`)
The user's decision (2026-10-04, `docs/unimplemented-apis.md` "Decisions"): buying 紋章石 works locally and costs nothing. The store side is the platform's (`platform370/src/java_370.cpp`, `docs/client-changes.md` "In-app billing").
- **How the client buys (b)**, `CPaymentManager` (`Progress_Purchase` @015f8224): `CoinDepositCreate(1, product id, "user_id")` → the answer's `CoinDeposit.deposit_trans_id` (CParameterManager+0x6e78) → the store's purchase (the trans id as its payload) → `VerifyReceipt_` (@015f91b0) sends `CoinDepositAndroidUpdate(trans id, Base64(purchase data), signature)` → on success the store's purchase is consumed. The products are `CoinList` (`CCoinInfoList`, CParameterManager+0x6e00): `CPaymentManager::Init_` (@015f87fc) registers each `product_id` with the store at the end of the login (`CPhase_Login::Progress` state 0xe) and fails (−0x3fd, the coin shop's error dialog) when the list is empty; `CCoinShop::StateCoinShopCore` (@019780b4) lists the products the store knows that have a `CCoinInfo`.
- **`CoinList` on every full player load** (Login, GetPlayer, NoLoginStart): **(b)** no 3.7.0 code sends `CoinList` while `Init_` needs the products at login; **(d)** the player load carries them. `CoinList()` answers the same list.
- **The products (a)+(d)**: `master_text` `coin_name_NNN` / `coin_title_NNN` / `coin_description_NNN` are the products' labels (**b**: `CCoinShop::tInfo::Initialize` @0197874c shows `name_label` / `title_label` / `description_label` through `GetSystemMessage`); the 2019-10-01 set (`coin_title_20191001_NNN`, `coin_description__20191001_NNN`) is the one sold last (**d**). A product's stones come from its description, `※<paid>個＋おまけ<bonus>個` (**a**). Sold: the NNN with the three 2019-10-01 labels whose name has neither 限定 nor ＋ (**d**: the limited and bonus sets' 2019-10-01 descriptions don't describe their names, e.g. 008 is named an S set but described as 3,060 + 3,060): 001..007 (S 120, M 490 + 10, L 980 + 80, LL 2,080 + 370, メガ 3,060 + 940, ギガ 4,900 + 2,310, テラ 10,000 + 6,550).
- **`CCoinInfo` (b**: the keys `CCoinInfo::Initialize` @01659284 registers): `id` (the NNN), `product_id` (**d**: `soa.local.coin_NNN`, the real store ids aren't recorded; under the 64 bytes `Init_` copies), `coin` (paid), `free_coin` (bonus), `yen` (**d**: = the paid count; the descriptions' paid counts are the store's price points; `tInfo::Price` @0197b024 shows it), `order_id` = id, `icon_id` (`itm_th_001NN`, 1..3: **d** 1 for 001-002, 2 for 003-004, 3 above), the three labels; `opened_at` / `closed_at` / `bought_at` "" (**b**: `IsTimeOverCoinSale` @01ef76c8 checks only a non-empty window; `IsSoldOutCoinSale` @01ef77e8 counts a product with `bought_at` and `interval_day` 0 sold out), `limit_count` / `limit_num` / `interval_day` / `bonus_type` / `bonus_id` / `sale_type` / `starter_limit_day` 0, `is_once` / `is_view_closed_at` false (**d**: no product has a limit, a window or a bonus, so there is no first-purchase bonus or purchase count to honour; **b**: `StateCoinShopCore` lists only `bonus_type` 0).
- **`CoinDepositCreate(platform, product, user)`**: a pending `coin_deposit` row (product, platform, time); answers the player state with `CoinDeposit {deposit_trans_id}` (**b**). The trans id is the row's (**d**). A product not sold: refused with 10208 (**d**, the generic refusal).
- **`CoinDepositAndroidUpdate(trans, receipt, signature)`** (and `CoinDepositIOSUpdate` / `CoinDepositAmazonUpdate`, answered the same, **d**): the product's paid stones to `player.pay_coin`, its bonus to `player.free_coin` (**a**: `uimsg_buy_history_explan`, おまけ分は無償入手分; the wallet keeps them apart, `core/wallet.h`); the row records the completion time and the stones. **(d)** No receipt validation: the receipt and signature are logged, not checked. **(d)** A deposit already completed answers the same without crediting again (the store retries a purchase whose answer it lost); an unknown trans id: 10208. Answers the player state (`Wallet`), `PurchasedItemInfo {bonus_type 0, name_label, title_label}` (**b**: `CPurchasedItemInfo`) and `CoinList`.
- **Birth year and month:** the coin shop sends `GetBirthYearMonth` first (`CCoinShop::ToShop` @01977a9c); the settings module refuses it with 10009 until one is entered (`#settings`, [account](#account)). **(b)** Checked end to end (2026-10-06, session `coins`, both hosts): `ToShop`'s result lambda (@0197c2f8) gets (false, 10009) with no generic error dialog first (in-process too: the served status-only call's refusal reaches it through the FakeApiCaller route's `IsSuccess` / `ErrorCode`) and shows the client's birth dialog (紋章石やアイテムを購入するためには、生年月を登録する必要があります… with 登録する, then a confirmation 以下の生年月で登録します); 登録する sends `UpdateBirthYearMonth`, and the coin shop opens. After a re-login the stored month is answered and the dialog isn't asked again. **(d)** no age-based spending limit (a local game has no reason to limit spending; Decisions).
- **How a player reaches the coin shop (b)**: the 3.7.0 client stopped selling 紋章石. The shop menu has no 紋章石 entry (`CShop::Setup` lists item shop .. stamina heal), the header has no ＋, and every coins-short check made with the client's own count answers 紋章石の販売は停止しています (`uimsg_stone_not_buy_end_dialog`: `CGachaShortage::OpenShortage` @01ae01d8 calls `CDialogManager::OpenBuyEndDialog` for coins unconditionally; the item shop's check runs while `CParameterUtility::IsEnableEmptyAndExpiredCheck` @0183bc14, a constant 1). The coin shop (`CCoinShop::StateStart`) is opened only by: the item shop's exchange **refused by the server with 20003** (@01b5eea4 → `OpenCoinShopDialog` → 紋章石を購入する), the gacha's draw refused with 20003 (@01ad2bb8 → CGacha state 30), a home guide popup with `target_content_type` 4 (`CGuideInformation::Progress` @01c67408; none in `master_guide_information`) and a banner link to shop mode 4 (none in `master_banner`). So the server refuses a coins-short exchange or draw with **20003** (**b**; it was 20000, **d**), and the coin shop opens whenever the client thought the coins were enough and the server's were not. **The user's decision (2026-10-05): the sale-stopped dialog opens the coin shop.** platform370 patches `CDialogManager::OpenBuyEndDialog` (@01dca8bc) to call the client's own `OpenCoinShopDialog(0, ...)` (@01dbc618), so every coins-short moment the client detects itself (a gacha draw, an item-shop exchange, the stamina heal, the gear-frame extension) opens the coin shop (`docs/client-changes.md` "Emulator mode"; `--no-patch` turns it off). The 20003 refusals stay (b).
- **The premium shop: `DirectItemShopList`** answers an empty `DirectItemShopInfoList` (**d**): `CDirectItemShop` buys a row through `CPaymentManager::Purchase(int)`, i.e. a store product, and `master_direct_item_shop` names the sets but no product or price; the 3.7.0 shop menu has no premium-shop entry and 購入情報 shows its passes as 販売終了.
- Tests: `shop/coins`, `server/schema-migrate-coin-deposit`, the `coins` replay corpus; session `coins` (port/scripts/coins_session.sh, both targets): a player with 50 stones, a single gacha draw (500) opens the coin shop, the L set bought, kept after a re-login.

<a id="passes"></a>
### Passes (subscriptions; `server/src/api/shop/subscription.cpp`)
| Rule | Label |
|---|---|
| Content type 20 is a pass: `content_id` = a `master_subscription_plan`, `num` = the days it runs (30 for the Galaxy Pass `pshop_galaxypass_001`, 14 for the character passes; `master_direct_item_shop`, `master_item_set`). A grant while the plan still runs extends it by `num` days, else it runs from now. The port sells no pass (the direct item shop was real money), so passes come only from such a grant, or from `--galaxy-pass`. | (a) the rows + (d) `num` as days, extending |
| `--galaxy-pass` (port option, the user's choice; off by default): the Galaxy Pass (the `master_direct_item_shop` type-20 product whose plan has `is_galaxypass`) is granted whenever a full player load finds it not running, as an auto-renewed pass would be. | (d); (b) the feature name `auto_renewable_subscriptions` |
| `Subscription` {type: {master_subscription_type_id, opened_at, closed_at}}, one entry per `master_subscription` type of the recorded plans (the later `closed_at` when two plans give a type), and `SubscriptionPlan` {plan id: {master_subscription_plan_id, updated_at, opened_at, closed_at}}, on every full-state player response and (`Subscription`) on `DeepSpaceActiveList`. A type is on while `closed_at` is after the clock. | keys and fields (b) (`EnableSubscriptionType` reads the map at CParameterManager+0x9600 and compares the entry's `closed_at`, SubscriptionInfo +0xd0, with `NowTime`); which responses (d) |
| Of the Galaxy Pass's types (1 event-drop slot, 2 storage +`subscription_storage_stock`, 3 deep space ships, 5 character gacha), only type 3 has server rules; the client shows the others' effects (e.g. the storage size) without server-side counterparts. `GetSubscriptionHistory` (the パス購入履歴 dialog) isn't answered. | (d) not done |

<a id="shop-register"></a>
### Player-visible (c) and (d) rules (shops)

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Shops | item shop `reset_type` 2 = monthly, `interval_day` = every N days | (a) inferred / (d) | |
| Shops | the coin shop sells the 2019-10-01 regular 紋章石 sets 001..007 of `master_text` for nothing; paid stones to the paid coins, the おまけ to the free coins; the price shown = the paid count | (a)+(d) | [paid-currency](#paid-currency); session `coins` |
| Shops | no receipt validation; a completed purchase isn't credited twice | (d) | `shop/coins` |
| Shops | the premium shop (DirectItemShopList) lists nothing | (d) | no store product or price in `master_direct_item_shop` |

<a id="social"></a>
## Social: follows and rental helpers
Code: `server/src/api/social/`. The follow menu's lists (Blacklist, GetRecentlyPlayedList, SearchPlayer): [12. Home](#home).

<a id="rental-helpers"></a>
### Rental helpers (`server/src/api/social/rental.cpp`)

How the 3.7.0 client builds the helper list (**b**, from `CMissionMenu::CreateRentalCharactorList` → `CParameterUtility::CreateRentalListAuto` / `CreateRentalList`):
- A mission with `master_mission_npc` rows (the tutorial `ms00_001` and 358 event missions) lists those NPCs. That list comes from master data alone; the server serves nothing for it.
- Every other mission lists the entries of **`BattleRental`** (`CBattleRentalInfoList`, `CParameterManager+0x62c8`, its map at `+0x6300`). Entries whose player is in `BlacklistID` (`+0x6638`) are skipped, and those in `FollowID` (`+0x6350`) are flagged as followed. The offsets come from the live schema dump (`--fake-server-schema`).
- An entry is a `CFollowInfo` {`order`, `player`: `CFollowPlayerInfo`, `pc`: `CFollowPersonInfo`}. The child names are the classes' `pParseName`. The map is keyed by the id as a string, like the other `...Map` infos.
- No request is sent when the list opens. The client shows whatever `BattleRental` it last received.

| Rule | Source | Notes |
|---|---|---|
| `BattleRental` goes out with every full-state player response (`Login`, `GetPlayMission` …). | (d) | Which 3.7.0 response carried it isn't known. The client accepts it in any response. |
| The rental list is a set of **clones of the player's own roster**: the 10 highest-level characters, one per role, ties broken by uid. | (d) | A local server has no other players. The count of 10 is an assumption. |
| Each clone is lent by a synthetic player with id `0x7d000000 + order`. The player carries the player's own name and level, `last_login_at` = now, `follow_status` 0, and is neither blocked, a rookie nor a subscriber. | (d) | |
| `pc` = the roster character as the server core reports it (`Character` fields), plus `player_id` and the equipment's `weapon_/accessory_master_item_id`, `_level` and `_limit_break_count`. `id` = the roster uid with bit 40 set (`rental.h`). | (b) + (d) | The field names come from `CFollowPersonInfo::Initialize` and `fields.txt`, and `InitializeRental` reads the master item ids. The id encoding is ours. |
| **`MissionStart` with a rental.** The client sends the chosen rental's id as the 4th argument (the u64 MissionStartArgs calls `own_helper_uid`, seen live). The server accepts it in either u64 argument. The clone's battle status (`person_status_info` of the source uid, `id` = the rental id) **replaces party member 4**, or is appended when the party has fewer than four members. | (b) + (d) | (b): the party screen shows the helper in slot 4 (`tPartyData` +0x8798 = 8 + 3 × 0x2d30), and `CPartyManager::InitializePlayer` builds exactly four slots. Verified on screen: the 4th card in the party select, the battle and the result EXP page. |
| Missions with `master_mission_npc` rows keep the core's rule (the NPCs are the party), so no rental is used there. | — | See "Tutorial battle". In event missions those rows are the helper list instead: see "NPC helpers (`master_mission_npc`)". |
| **`FollowList`** answers `Follow` (the same entries), and empty `FollowPlayerList`, `FollowID` and `MutualFollowID`. | (b) keys (docs/api.md) + (d) empty | Nobody is followed on a local server. |
| **Rental bonus.** `master_rental_bonus` rows {id 1..10, `rental_bonus_1`, `item_coin_37` サポートメダル, 300..750} pay the medals "you get when a character you set for rental is rented". Per `uimsg_sphere211_getting_rental_bonus`, it pays daily by the number of rentals the day before. | (a) | The texts are from `master_text`. |
| The row whose **id = that day's rental count** pays, capped at the last row. | (d) + (b) | (b): `CUIUtility::GetMasterRentalBonus(id)` looks rows up by id. |
| The rentals counted are **the player's own rentals of the clones**, counted per rental day by `MissionStart` in the server table `follow_rental` (`rental_day`: the day's start), where the day starts at `login_bonus_reset_hour`. Each earlier day still unpaid pays once, into the present box (reason type 3), on the next full-state player response. `RentalCount` / `RentalBonus` carry the last paid day's count and row id. | (d) | Nobody else rents the player's characters. |
| **The `CRentalBonus` popup** (レンタルボーナス獲得！) opens on the home after the login-bonus popup when `RentalBonus` (CParameterManager+0xb4a0) and `RentalCount` (+0xb4d0) are both non-zero. Its bit (4) is armed by 3.7.0's login (`CPopupManager::AddPopup()`, mask 0x7b), so no server call is needed; the server only sends the two values on the day's first player response. The popup shows `uimsg_rentalbonus_num` "%u人" + "からレンタルされました。", the paying row's content (`CUIUtility::GetMasterRentalBonus(RentalBonus)`: サポートメダル×300 for row 1), `uimsg_rentalbonus_explan` (the present box), and the card of `Player.support_pc_id`. Seen in game (agent a4-helpers, 2026-09-30): a rental on 2026-09-30, then a boot with `--clock "2026-10-01 12:00:00"`: notice board → LOGIN BONUS → the rental-bonus popup. | (b) | `CPopupManager::CheckStart` case 4 / `Create(4)` / `CRentalBonus::Setup`, decompiled from 3.7.0 (`work/decomp/a4-helpers-popup.resolved.c`); the offsets match the schema's key order (`RentalBonus` #560, `RentalCount` #561, 0x30 apart). |
| **`Player.support_pc_id`** = the character the player lends (a uid: `CRentalBonus::Setup` builds its card with `tCharaData::Initialize(CParameterManager+0xba8)`). **`UpdateSupport(u64 character)`** (the character dialog's レンタル button, `uimsg_ch_dialog_rental`) sets it and answers `Player`; the character must be owned, else refused (no body). Unset, or no longer owned: the highest-level character (ties by uid), the first of the rental list's lenders. Stored as `player.support_uid` (NULL: unset; `meta.support_uid` before schema version 3). | request and key (b: docs/api.md, `OnUpdateSupportRes`); uid (b); owned check, default (d) | `api/social/rental.cpp`, `server/src/api/player/player_info.cpp` `player_info`. Test `social/follow-support`. |

<a id="social-stubs"></a>
### Stubs: the social calls and the debug APIs (`ext::add_stub`)

The user's decisions (2026-10-04, `docs/unimplemented-apis.md` "Decisions"): the social calls of a server without other players and the developers' debug APIs are answered as stubs, and every stub logs each call. Real friends belong to the multiplayer server (`server/PLAN-multiplayer-code.md` MC7), which replaces these stubs.

| Rule | Source | Notes |
|---|---|---|
| A stub is a registered handler (`soa-server --list-apis` names its file) built by one helper, `ext::add_stub` (`server/src/core/stub.cpp`): it stores nothing and answers success, `data` = `{Time}` (plus what its registration adds; none today). | (d) | `{Time}` is what the wire answered for these methods before (the in-process route an empty map), and the client carried on with both (`docs/unimplemented-apis.md` section 1). |
| Every call logs one warning, `stub: <Method> (fid <fid>) called; answered success, nothing stored (docs/unimplemented-apis.md)`, then the request's arguments in short form (integers, strings cut at 32 bytes, a vector's length and first four values). | (d) | Every call, not only the first: these calls are rare, so the log stays readable. |
| **Social** (`server/src/api/social/social.cpp`): `FollowAdd`, `FollowRemove`, `BlacklistAdd`, `BlacklistRemove`, `UpdateFollowMax`, `NeighborList`, `NeighborRegist`, `LocationRegist`. The follow and block lists stay empty (the follow menu reloads them: `FollowList`, `Blacklist`); `UpdateFollowMax` spends no coins and `follow_max` stays `master_global.follow_default`; no location is kept (also the privacy-safe choice). | (d) | Mission helpers still come from the rental clones ([Rental helpers](#rental-helpers)), which don't depend on follows. |
| **Debug** (`server/src/api/debug/debug_stubs.cpp`): the 27 `Debug*` methods answer success and change nothing, also the ones whose names promise items or currency (`DebugGetCoin`, `DebugGetItem`). | (d) | Not in the 3.7.0 client's API table (`docs/unimplemented-apis.md` 2.4): only a test or a modified client sends them. |

Tests: `server/stubs` (`server/src/core/stub_tests.cpp`: each stub answers `Time` with status 0 and the state is unchanged); the `stubs` replay corpus (each once, then GetPlayer).

<a id="deepspace"></a>
## Deep space (`server/src/api/deepspace/deepspace.cpp`)
The expedition mode ("ディープスペース探査", `CPhase_DeepSpace` = phase 6). The client code is unchanged from 3.7.0; the module answers its five APIs. Unit tests `rules/deepspace` (`server/src/rules/deepspace_rules_tests.cpp`), `deepspace/expedition`, `deepspace/extras` (pass ships, play limits, achievements; `server/src/api/deepspace/deepspace_tests.cpp`), `shop/subscription`; replay corpus `server/tests/replay/deepspace`; session `port/scripts/deepspace_session.sh` (runs with `--galaxy-pass`: two expeditions out at once, the second on a pass ship; the 実績 screen and 一括達成).

<a id="deepspace-requests"></a>
### Requests as the client sends them (b: the captured requests)
- `DeepSpaceActiveList()` (queued on the FakeApiCaller route with the in-process server, see `docs/client-changes.md`).
- `DeepSpaceAutoMemberSelect(u32 bonus_set_id, u32 bonus_id)`: the offer's bonus set and the bonus the player tapped on the party screen. (The API table's "area, mission" reading was wrong.)
- `DeepSpaceMissionStart(u32 mission_id, u32 item, vector<u64> uids)`: `item` is the master item id of the bonus item chosen in `CDeepSpaceItemSelectDialog` (0 = none). The area is the mission's.
- `DeepSpaceMissionEnd(u32 ship_id)`, `DeepSpaceMissionEndNow(u32 ship_id)`.

<a id="deepspace-responses"></a>
### Response shapes (b)
From the info classes' `Initialize` and the handlers. A number map replaces the client's whole map (`IInfoBaseMap::DeserializeChild` clears it first), so every response sends full lists.
- `DeepSpaceAreaList` {area id: `CDeepSpaceAreaInfo`} = master_area_id, current_exp, max_exp, ship_in_progress_num, ship_complete_num, is_last_play, is_rare_mission, is_new, `DeepSpaceMissionList` {mission id: `CDeepSpaceMissionInfo` = master_mission_id, bonus_set_id, ship_id, closed_at, count_weekly_at, updated_at, is_new, play_count_daily, play_count_weekly, play_count}. An area missing from the list shows as "？？？？？" (`CDeepSpace::GetDeepSpaceAreaList`); a mission missing from its area's list isn't shown (`GetDeepSpaceMissionList`).
- `DeepSpaceActiveShipInfoList` / `DeepSpaceEndShipInfoList` {ship id: `CDeepSpaceShipInfo` = ship_id, master_area_id, master_mission_id, bonus_set_id, item_id, started_at, closed_at}. A mission whose offer's ship_id is in the Active map shows 進行中 with its remaining time and 今すぐ帰還; in the End map, 帰還済, and tapping it sends `DeepSpaceMissionEnd` (`CDeepSpace::SetupPartySelect`).
- `characters` {uid: character_id, ship_id, ship_slot}: the characters out on ships; ship_slot is the party position 1..8 (`CDeepSpaceProgressDialog::Open` looks up slots 1..8).
- `DeepSpaceBonusAllApplyInfoList` / `UpdateDeepSpaceBonusAllApplyInfoList` {ship id: {bonus id: {bonus: float}}}: a dispatched ship's bonus values, which the client shows instead of its own estimate (`UpdateDeepSpaceMissionBonusList`).
- `AutoSelectedResult`: an array of uids (`InfoBaseValueArray<u64>`).
- MissionStart also sends `DeepSpaceShip` (the handler inserts it into the Active map) and `DeepSpaceArea` (merged into the list).
- MissionEnd: `DeepSpaceShip` (the handler erases it from both ship maps), `DeepMissionPlayer` (level, exp, stamina, stamina_max, fol, is_level_up, tower_try_count, time_saving_use_count, stamina_update; copied into the player), `add_characters_exp` {uid: character_id, add_exp, before_level, before_exp, after_level, after_exp, order_id} (`CDeepSpaceResult::Setup` shows the members by order_id 0..7; the handler stores after_level / after_exp), `CContentInfoMap` {n: `CDropContentInfo` = content_id, content_type, num, is_new, master_item_id, bonus_category, is_rare_bonus, is_add_bonus, is_hit_bonus, is_rare_hit_bonus} (the result's reward items, `CDeepSpaceResult::GetRewardItemList`), `AddItem`, `StockItem`.
- MissionEndNow: `DeepSpaceShip` (the handler moves it into the End map), `DeepMissionPlayer`, the ship lists, `StockItem`.

<a id="deepspace-clocks"></a>
### Clocks
- **Expedition timers** (a ship's started_at / closed_at, a rare offer's limit, the quick-return price and its daily count) use the server clock `now()` (`clock_now`), so `--clock` and the control command `clock:+SECONDS` fast-forward them.
- **Dated master rows only the server reads** (bonus sets, drop items, bonus items) use the event calendar `event_now()`.
- **Dated rows the client also filters by its own clock** (data.Time = the server clock): areas and missions must be open by **both** clocks, or the server would offer what the client hides (b: `GetDeepSpaceAreaList`, `GetDeepSpaceMissionList`). The ship count uses the server clock only (b: `CUIUtility::GetMaxShipCount`). The date checks sit in `calendar()` / `open_by_both_clocks()` (`server/src/api/deepspace/state.cpp`).

<a id="deepspace-rules"></a>
### Rules
| Rule | Label | Notes |
|---|---|---|
| An area opens when its `opened_at` / `closed_at` window holds; one with `is_required` also needs every `required_areaN_id`'s exploration rate (current_exp / max_exp, in %) to reach `required_exp_rateN`. | (a) + (d) | (d): all listed conditions are needed. |
| An area is offered only when its image `Image/etc2/<resource>.aif` is found through the port's asset lookup (APKs, then `--download-dir`), checked at runtime. | (d) | No list of areas in the code; more downloaded assets open more areas. Outside the game (unit tests) every area counts as present. |
| A newly opened area that needed other areas is `is_new` once (the next `DeepSpaceActiveList`). | (d) | |
| Every normal mission (`rare_type_id` empty) of an opened area inside its window is always on offer. | (a) + (d) | |
| Each offer has one bonus set, picked by `rate_weigh` among the `master_deep_space_bonus_set` rows of the mission's `bonus_set_type_id` open by the calendar; rolled when the mission is offered and again after each expedition. | (a) + (d) | |
| Ships: the number of `master_deep_space_ship` rows with `use_type` 1 open by the clock whose `required_num` the player's total limit-break count reaches (the client's "艦数" and "NEXT pt"). Ships are numbered 1..N. | (b) `CUIUtility::GetMaxShipCount` + (d) numbering | When the count grows, the client itself opens `CDeepSpaceShipIncrementDialog` ("累計 N pt達成により同時に探査できる艦数が増えました", compared with its local KVS `BAS:DeepSpaceShipCount`); the dialog calls no API. |
| **Subscription ships:** while the player's pass gives `master_subscription` type 3 (the Galaxy Pass, `subscmsg_gpass_deepspace_title` "ディープスペース探査艦＋２隻"), `master_global.subscription_deepspace_ship` (2) more ships, numbered after the limit-break ones. | (a) + (b) + (d) numbering | (b): `CDeepSpace::Setup` reads the key, `SetupAfterConnection` adds it to the 艦数 shown (in the pass colour) and `GetUnusedShipCount` to the ships that may depart, both only when `EnableSubscriptionType(3)` (the `Subscription` state, see "Passes" below). The `use_type` 3 rows (ship_charging_01/02) are read by no client code. |
| The pass runs out while a pass ship is out: the ship still comes back and is collected, but no ship departs beyond the remaining count. | (a) the pass text `subscmsg_gpass_deepspace_manual` "探査に出発中に有効期限が切れた場合、帰還は可能で再出発ができません" | MissionEnd doesn't look at the count. |
| **Coin ships** (`use_type` 2: ship_coin_01..03, `required_num` 500 / 1000 / 1500) aren't counted or sold. | (b) | No client code reads them (the only query of `master_deep_space_ship` is `GetMaxShipCount`'s `WHERE use_type=?` with 1, in 3.7.0) and no client API buys a ship, so a server-side coin ship would be one the client never lets depart (`GetUnusedShipCount`). |
| A ship is busy from MissionStart until MissionEnd collects it (Active while out, End once back). | (b) `CUIUtility::GetUnusedShipCount` | |
| MissionStart: 1..8 owned characters, none out on a ship, none twice; the mission on offer and not on a ship; a free ship. Otherwise refused with 10208 (a bonus item not owned: 10206). | (b) "%d / ８" + (d) codes | |
| Expedition time = `master_deep_space_mission.time` minutes. | (a) + (b) | The confirmation shows 探査時間:30分 for time 30. |
| Bonus values: condition1 1 = the role (`master_role.category_type`) equals param1, 2 = the weapon kind (`master_weapon_kind_id_label`) equals param1, 3 = anyone; condition2 1 = level ≥ param2, 3 = limit break ≥ param2, 4 = awaken level ≥ param2, 5 = sum of battle power, others = anyone. Below `bonus_condition_param_min` the value is `bonus_effect_param_min`; from it, linear to `bonus_effect_param_max` at `_max` in steps of one member (battle power: (max − min) / 19), rounded down to 0.1. | (b) `CDeepSpace::tBonusInfo::IsApplyCharacter`, `UpdateDeepSpaceMissionBonusList` | condition2 2 ("all parameters at maximum") is taken as level ≥ param2 (d). category_type as the role is (d) (the areas' labels At/De/Sh/Ca/He fit 1..5). |
| Battle power per character ≈ 3.86 × level × (1 + 0.03 × limit break). | (d) | The client's CalcBP needs the full status; fitted to the client's own sum on screen for the seed save (8 characters of levels 50..60: 1701). |
| A bonus item: `master_deep_space_bonus_item` of that master item, open by the calendar; one is used per expedition; type 2 multiplies every bonus by `value`, type 1 adds the bonus `param1_id` at `value`. | (a) + (d) | The multiplier is the client's (b); the use-up and type-1 value are (d). |
| AutoMemberSelect: the free characters meeting the tapped bonus's conditions first (by battle power for a battle-power bonus, else by level), then the others by level; up to 8. | (d) | The screen's hint says it prefers the characters that strengthen that bonus. |
| MissionEnd refused (10208) before the ship is back. | (d) | |
| Rewards: `player_exp` to the player rank (a level-up adds the new stamina maximum, as MissionEnd), `fol`, `character_exp` to each member, `exp` to the area's exploration up to `max_exp`. | (a) | |
| Drops: `drop_count` lots from `drop_type_id` (`master_deep_space_drop_item` open by the calendar, by `rate_weigh`); each lot comes from `rare_drop_type_id` instead with `rare_drop_rate` % (× the rare-drop bonuses). | (a) + (d) | Lot semantics (d). |
| Bonus effects: 1 "レア探査ポイント発見率アップ" multiplies the rare-mission rate by the value; 2 "レアアイテム発見率アップ" the rare-drop rate; 3 "＋N追加アイテム発見率" adds `bonus_effect_param1` lots with `bonus_effect_param2` % × value; 4 "X発見率アップ" draws one lot from the drop table named `bonus_effect_param1` (`drop_type_id_label`) with `bonus_effect_param3` % × value. | (c) + (d) | From the effect names in master_text `name_ds_bonus_*`; `bonus_effect_param4..6` unused. |
| Result marks: bonus_category 1 for an effect-4 lot, 2 for an effect-3 lot, 3 for a rare-table lot. | (d) | |
| Rare missions: after an expedition, with `rare_mission_rate` % (× the rare-point bonuses), one mission whose `rare_type_id` is the finished mission's `rare_mission_type_id`, in the same area, open by both clocks and not already offered, is offered by `rate_weigh` for `rare_limit_time` minutes. A rare offer is used up by its expedition. | (a) + (d) | |
| Quick return (今すぐ帰還): hours left (rounded up) × `master_deep_space_time_saving.rate` of today's use number + 1 (capped at the last row) = quick-return items (`master_global.deep_space_quick_return_item`) needed; the items the player lacks cost 10 coins each (free coins first). It only brings the ship home (End); MissionEnd gives the rewards. | (b) `CDeepSpaceQuickReturnDialog::Update`, `OnDeepSpaceMissionEndNowRes` + (a) free coins first ("Stocks and wallet") | |
| Quick returns per day count from `login_bonus_reset_hour` (04:00); sent as `Player.time_saving_use_count` and `DeepMissionPlayer.time_saving_use_count`. | (d) | |
| **Play limits:** `master_deep_space_mission.limit_type` 1 = per day, 2 = per week, with `limit_count` departures in that period; empty / 0 / other types = none. A departure (MissionStart) counts in the offer's `play_count_daily` / `play_count_weekly`, which restart at 04:00 (`login_bonus_reset_hour`) and on Monday 04:00. | (a) columns + (d) the meanings, the period starts, counting departures | Every 3.7.0 row leaves both columns empty, so nothing is limited with today's data; the rule applies to data that has them. The client shows no limit (b: no limit text among its deep space strings). Test `deepspace/extras` (a temp copy of the table with limits). |
| A mission at its limit is left out of its area's `DeepSpaceMissionList` until the period restarts (unless it is on a ship), and MissionStart refuses it (10208). `count_weekly_at` = the week's start for a weekly-limited mission, else "". | (b) a mission missing from the list isn't shown + (d) | |
| **Achievements** (`api/presents/achievements.cpp` progress): type 44 = the exploration rate of the area `target_id` (`master_deep_space_area` id; `exp` × 100 / `max_exp`, rounded down; goal 100 "探査率１００％"); type 45 = expeditions ("ディープスペース探査を N回行う"). | (a) texts and columns + (d) rounding | |
| A departure counts as an expedition, at its time (state table `ds_log`). Type-45 rows with `is_unlimited` (the ac_ind / title rows) count every expedition; the campaign rows (no `is_unlimited`) only those inside their `opened_at` .. `closed_at`. | (d) | The campaign rows are only active in their windows anyway (by the server clock). |

<a id="deepspace-state"></a>
### State (`server.sqlite3`)
`ds_area` (exploration exp, is_new, last play), `ds_offer` (the areas' mission lists, with the play counts), `ds_ship` (ships out or back) with `ds_ship_member` (each ship's crew, slot 1..8 as the client's `ship_slot`; the `ds_ship.uids` text before schema version 7), `ds_bonus` (a ship's bonus values), `ds_log` (every departure: its id, mission, time; for the achievements); the day's quick-return count in the `player` row (`time_saving_count`, `time_saving_day`), the play-limit periods in `ds_state` (`limit_day`, `limit_week`) (`meta` keys `ds_*` before schema version 3). The passes are in `subscription` (`api/shop/subscription.cpp`).

<a id="deepspace-not-done"></a>
### Not done
- Coin-bought ships: no client route (see the rule above).
- `LimitBreakCharacter` in MissionEnd: no deep-space drop grants a character in the 3.7.0 data.
- The Galaxy Pass's other types (drop slot, storage, gacha) and `GetSubscriptionHistory`.

<a id="deepspace-register"></a>
### Player-visible (c) and (d) rules (deep space)

| Rule | Label |
|---|---|
| Area image present on disk | (d) |
| All normal missions always offered; bonus set re-rolled after each expedition | (d) |
| Ship numbering (pass ships after the limit-break ones); no coin ships (b) | (d) |
| Pass `num` read as days; `--galaxy-pass` renews the Galaxy Pass | (d) |
| Play limits: type 1 day / 2 week, departures counted, periods from 04:00 / Monday 04:00, a mission at its limit hidden (no 3.7.0 row has limits) | (d) |
| Achievements: a departure is an expedition; campaign rows count only their window; exploration rate rounded down | (d) |
| Auto member select order | (d) |
| Battle power approximation | (d) |
| Bonus effects 1–4 (rates, extra lots) | (c)/(d) |
| Rare-table and rare-mission lot semantics; result marks | (d) |
| Quick returns counted per day from 04:00 | (d) |
| Quick returns: free coins first (master_text `uimsg_buy_history_explan`, "Stocks and wallet"); was (d) | (a) |
| Refusal codes 10208 / 10206 | (d) |

<a id="sphere211"></a>
## Sphere 211 (`server/src/api/sphere211/sphere211.cpp`)
The extra dungeon ("スフィア211", `CPhase_Mission` with mission type 5, the `CSphere*` screens). The client code is unchanged from 3.7.0; the module answers its 13 APIs, which reach the local server through the FakeApiCaller routing in `docs/client-changes.md` ("The Sphere 211 requests on the FakeApiCaller route"). Its battles are `master_event_mission` rows played through the core `MissionStart` / `MissionEnd` (`ext::Ctx::core_mission` with an `ext::MissionOverride`). Entry: the restored 3.7.0 home's スフィア211 button (or the control command `uiset:0x140:5 phase:5`). Unit tests `sphere211/season`, `/lottery`, `/stamina`, `/dive`, `/rental`, `/achievements`, `/items`, `/ex-sorties` (`server/src/api/sphere211/sphere211_tests.cpp`); replay corpus `server/tests/replay/sphere211`; the code by topic in `server/src/api/sphere211/README.md`; sessions `port/scripts/sphere211_session.sh` (the dive; with the rental bonus popup, a rental, the heal ticket and the reroll; seed 605 since the favor login bonus draws at the login) and `port/scripts/sphere211_continue_session.sh` (a lost battle continued and retired).

<a id="sphere211-requests"></a>
### Requests as the client sends them (b: the captured requests, `sphere211_session.sh`)
- `GetSphere211Info()`: when the board opens (phase 5).
- `Sphere211AutoMemberSelect(1, cell asset id, 0)`: 自動編成 on the party screen.
- `Sphere211MissionStart(1, cell asset id, uid, uid, uid, uid4, owner player id)`: three party members, the 4th (rental) slot's character and its owner (the player's own id when the slot holds an own character; a rented character's rental id and its lender's player id, seen in game: `... 1101625557006 2097152001`). The first argument was 1 on floor 1 (CStageManager+0x68; its meaning is not known, (d) ignored).
- `Sphere211MissionEnd(1, cell asset id)`, `Sphere211MissionFailed(u32, u32)`, `Sphere211MissionContinue(u32, u32, bool)`: CStageManager+0x68 / +0x6c as MissionStart's first two.
- `Sphere211FloorClear(goal asset id)`: the goal (目標地点) → 次のフロアへ → 決定.
- `Sphere211SelectedFloor(n)`: the floor chosen in the floor select, as the offset from the current floor (1 = the next floor) (b: 1 when 2F was chosen from 1F).
- `ReturnSphere211()`: 帰還 → 帰還.
- `Sphere211StaminaHeal()`: the S stamina ＋ → the season's ticket → 決定 (the dialog shows 8 / 9 → 9 / 9 for a 1-point ticket).
- `Sphere211MissionContinue(1, cell asset id, 1)`: the defeat dialog's はい ("紋章石100個を使用することで全員が復活できます"); the bool is 0 for its いいえ and for the decline `CPauseMenu::OpenContinue` (@01dacf90) sends by itself when the coins don't cover the price (b: `CPauseMenu::ReqeustContinue` @01dad704 sends `Sphere211MissionContinue` for mission type 5 with the bool it sends `MissionContinue` for the others). `Sphere211MissionFailed(1, cell asset id)`: also the pause menu's ミッションリタイア → はい.
- `Sphere211UseRerollItem()`: the floor select's 再設定 → 決定.
- Not seen in the session (signatures from `docs/api.md`): `GetSphere211RankingInfo(bool)`, `Sphere211EquipAuto(u32, u32, vector<u64>)`.

<a id="sphere211-responses"></a>
### Response keys (b: the info classes' `Initialize`, `port/fakeapi/fields.txt`)
Every response carries the whole dive state (the maps replace the client's): `Sphere211CurrentId`, `Sphere211NeedsReset` 0, `Sphere211FloorInfo` {floor_level, mission_clear_streak}, `Sphere211FloorAssetInfoMap` {asset id: player_id, floor_level, master_sphere211_asset_id, master_sphere211_mission_box_id, overwrite_enemy_level, is_cleared, is_playing, can_play, is_new, created_at, updated_at} (`can_play` is the property whose CHash32 is 0x5730cc2a; the board offers a battle only then), `Sphere211StaminaInfo` {stamina, stamina_max, stamina_update}, `Sphere211TreasureInfo` {num, total_num}, `Sphere211CharacterInfoMap` {uid: player_character_id} (the characters that have sortied), `Sphere211FloorClearInfo` {floor_level, master_sphere211_asset_id, lot_floor_num}, `Sphere211EndResult` {previous_season_id, rank, floor_num, treasure_num}, `Player.sphere211_revive_count`. Per request:
- AutoMemberSelect: `Sphere211AutoMemberSelectResultInfo`, an array of uids (b: its typeinfo sits with `InfoBaseValueArray<u64>`'s, like deep space's `AutoSelectedResult`; the party screen fills its four slots from it, seen on screen).
- MissionStart: the core MissionStart's `MissionParameter` (with the enemy level), `PlayMission`, `BattleParameter`.
- MissionEnd: the core MissionEnd's result keys plus `Sphere211TreasureDropInfoList` [{type, num}] (b: `ResultUtility::GetRewardType(Common::Sphere211DropType)` badges type 1 `badge_clear.png` (連続クリア), 2 `badge_boss.png` (ボス撃破), 3 `badge_rareenemy.png`; other types no badge; `CSphereFloorClear` reads type 4 as the floor-clear boxes).
- FloorClear: `Sphere211FloorClearResultInfo` {clear_present_id, clear_present_content_type, clear_present_num}, `Sphere211TreasureDropInfoList` [{type 4, num}], `StockItem`.
- ReturnSphere211: `Sphere211TreasureResultLotInfoMap` {0..4: {lot_num}} and `Sphere211TreasureResultInfoMap` {0..4: [{content_id, content_type, num}]}, keyed 0 = D .. 4 = S (b: `CSphereBoxResult` shows key 4 as S and 3 as A), `StockItem`, `Item` / `Character` when granted.
- RankingInfo: `Sphere211RankingInfoMap` / `Sphere211RankingTopInfoMap` {player id: {player_id, floor_level, entered_at, rank}}.
- Every Sphere 211 answer also carries the rental slot (agent a5-sphere): `Sphere211RentalCharacterInfoMap` {lender id: {player_id, follow_player_id, is_used, updated_at}}, `Sphere211RentalCharacterDetailInfoMap` {lender id: CFollowInfo {order, player, pc}}, `FollowID` [lender ids], `Sphere211FollowFloorInfoList` [{player_id, floor_level, follow_status}]; and the `Achievement` state. (b) field names: the info classes' `Initialize` (`tools/info_fields_emu.py`); the map offsets (CParameterManager+0xa008 / +0xa058) from the live schema dump.
- The full player load also carries `Sphere211RentalBonus` / `Sphere211RentalCount` on the day a Sphere 211 rental bonus is paid.

<a id="sphere211-rules"></a>
### Rules
| Rule | Label | Notes |
|---|---|---|
| **Season:** the `master_sphere211` row whose `opened_at` .. `closed_at` covers the event calendar (`event_now()`: `--clock`, or today's date replayed onto the service years). | (a) | The client checks the same dates against its own clock (data.Time = the server clock), so the served season's dates are moved by (clock − calendar) in the client's master copy (`ext::ClientMaster`, docs/client-changes.md). |
| **Past the last season** (the service ended with season 13, 2021-06-10 .. 06-24): the last season runs on, its window moved forward by the fewest whole season lengths that bring it over the calendar; the same shift goes into the client's master. Each further season length is a new **cycle**, a new season for the dive and the ranking. In the one-hour gaps between seasons (13:59:59 .. 15:00), and in the day between the last season's end and the first one's date a year later, the previous season is moved on the same way (no new cycle). | (d) | Without it the mode is "現在、開催期間外です" for good. Test `sphere211/season`. |
| **Before the first season** (the replayed calendar maps Oct 1 - 2 and Oct 7 to 2019, before the first season of 2020-06-25): the season of the same date and time a year later (the 13 seasons span one year), moved by the same shift. | (d) | Before (agent a5-sphere) those days served season 1 moved into the future: "outside the season" and a spurious season change 4 → 1 → 4. Test `sphere211/season`. |
| `Sphere211CurrentId` is also sent with every full player load (Login, NoLoginStart, ...), and `FooterMissionInfo.is_open_extra_dungeon` = 1. | (b) + (d) | (b): the extra-dungeon menu (`MissionUtility` part info of type 5) shows the season as out of its period until `Sphere211CurrentId` (CParameterManager+0xaff0) names it; the footer flag sets CParameterManager+0x1a38 (`IsOpenExtraDungeon`). (d): open for this account (see 12). |
| **A season change ends the dive:** its unopened boxes are opened into the player's items, its best floor and boxes become `Sphere211EndResult`, and a new dive starts. The rank is 1 (the local ranking has one player) when a battle was won in that season, else 0 (not ranked). | (d) + (b) | The client's end-of-season dialog (uimsg_sphere211_return_dialog2) says the previous season's data is analysed; uimsg_sphere211_ranking_empty2: "ミッションを1つもクリアしていない場合は、ランキング未参加". |
| **`Sphere211EndResult` is sent once** (until a `GetSphere211Info` carried it), zeros afterwards. | (b) + (d) | (b) `CSphereMissionMenu::Progress` state 4, whenever the board opens: rank ≠ 0 opens the ranking-result dialog (`CDialogManager::OpenSphere211RankingResult`), else previous_season_id ≠ 0 shows uimsg_sphere211_season_has_finished3 "前回のランキングは終了しました。新しいシーズンが始まりました。"; (d) once, so it isn't shown at every visit. |
| **Season ranking reward:** at the season change, for rank ≥ 1, the season's `master_sphere211_ranking_reward` row with the smallest `required_ranking` ≥ the rank (rank 1: the `_1` row, an item set, content type 99, expanded through `master_item_set`), granted straight into the items; `StockItem` / `Item` go with the end result. The last season has no group (`master_sphere211_ranking_reward_id` empty): the group of the latest season before it (also written into the client's master copy). | (a) + (b) + (d) | (a) the rows and sets; (b) `CSphereRankingResult::Initialize` shows the tier whose range holds the rank (from `previous_season_id`'s row), and uimsg_sphere211_ranking_result "ランキング報酬が所持アイテムに追加されました" (no present box); (d) the fallback group. Test `sphere211/season`. |
| **Dive:** the first `GetSphere211Info` of a dive enters floor 1. 帰還 keeps the dive on its floor; only a season change starts over. | (d) | (b): with no cells the menu says the season has finished (`MissionUtility::GetEventMissionList` type 5). |
| **Floor row:** the season's `master_sphere211_floor` row of that level; above the table's last level, the last row. | (a) + (b) | (b): `MissionUtility::Sphere211FloorData` extends the list with the highest level. |
| **Floor map:** one `master_sphere211_floor_asset` template lotted from the floor's `asset_box_group_id` by `weight`; every row of the template is a cell. | (a) | Test `sphere211/lottery` (same seed, same floors). |
| **Cell battle:** a `master_sphere211_mission_box` row of the cell's `mission_box_group_id` whose `type` is the cell's `lottery_type`, lotted by `rate`. | (a) | The column pairs 1/2/4/6 match. |
| **Missing maps:** a mission is lotted only when every stage's battle map (`BG/<master_map_id_label>.asf/.aaf/.acf`, with the texture subdirectories) is found through the port's asset lookup (APKs, `--download-dir`), decided at run time. When none of the box group's rows is playable: a playable row of the same type from any box; when nothing is playable: the unfiltered lot (logged). | (d) | More downloaded assets make more missions playable; no list of names in the code. Outside the game (no asset source) every mission counts as playable. Test `sphere211/lottery` (an injected asset predicate). |
| **Enemy level:** the cell's `overwrite_enemy_level_group_id` lotted by `rate` (`master_sphere211_overwrite_enemy_level`), else the floor's `base_enemy_level` + the cell's `add_enemy_level`, sent as `MissionParameter.overwrite_enemy_level`. | (a) + (d) | (d): their sum. |
| **Playable cells (`can_play`):** the start cell (no `parent_cell_N_id`) and every uncleared cell with a cleared neighbour (`parent_cell_1..4_id`, which list both directions). `is_new`: playable and not cleared. | (c) + (d) | The goal cell has no battle; it becomes playable the same way and leads to FloorClear. Test `sphere211/dive`. |
| **Sphere stamina:** its own gauge, maximum `master_global.sphere_stamina_max` (9), one point per `sphere_stamina_recovery_time` (17,280 s) on the server clock, regenerating like AP; a new dive starts full. | (a) + (d) | (d): starts full, the partial period is kept. Test `sphere211/stamina` (`set_server_clock`). |
| **MissionStart:** costs the floor's `use_stamina` from the sphere gauge (not AP; error 10004 when short); the three party members and the 4th slot (an own character, played as the core's own helper, or a rented character, below) fight; the cell is marked playing and the party as departed. | (a) + (b) + (d) | (b): the 4th slot is the rental slot, filled from own characters too; (d): the refusal code. |
| **The rental slot:** the lenders are the synthetic rental players of `api/social/rental.cpp` (clones of the player's own characters, `rental::follow_map`), all followed (`FollowID`) and on the player's floor (`Sphere211FollowFloorInfoList`). Each lends once per floor (`is_used`); after 3 rentals on a floor every lender is used; a new floor lends again. A rental in `Sphere211MissionStart` (a rental id whose roster character exists, lent by a listed, unused lender, rentals left) plays as the core's rental helper (the clone of that character); it doesn't depart. Otherwise refused (10208). | (a) + (b) + (d) | (b) `CParameterUtility::CreateSphere211RentalList`: the entries of `Sphere211RentalCharacterInfoMap` without `is_used`, whose `follow_player_id` is in `FollowID` and not in `BlacklistID`, built from the `Sphere211RentalCharacterDetailInfoMap` entry whose `pc.player_id` matches (`tCharaData::InitializeRental`), sorted by `updated_at`; the board shows them as the followee icons (`UpdateBadgeAndFollowee`). (a) master_text cp0003_tutorial_sphere211_007: followed players on the same floor lend "１フロアにつき合計３回まで". (d) no other players, so the clones; once per lender; the refusal code. Seen in game: the rental list after シングルプレイ開始, the lender in slot 4 kept by 自動編成. Test `sphere211/rental`. |
| **Sphere 211 rental bonus:** the Sphere 211 rentals are counted per rental day (from `login_bonus_reset_hour`, with the season). On the next full player load after that day, the season's `master_sphere211_rental_bonus` row with the highest `rental_count` at or below the day's count (5 → the season's reroll ticket × 1) goes to the present box (line: its `present_message_id` text "スフィア211レンタルボーナス"), and `Sphere211RentalBonus` = the row id, `Sphere211RentalCount` = the count are sent. Paid once per day; a day below every row's count pays nothing. | (a) + (b) + (d) | (a) the rows; (b) `CPopupManager::CheckStart` case 5 opens `CSphereRentalBonus` when both are non-zero (armed by 3.7.0's login, `AddPopup()` mask 0x7b); `CSphereRentalBonus::Setup` looks the row up by id and formats uimsg_sphere211_getting_rental_bonus "前日、%u人のユーザーがあなたをレンタルしました ... あなたのフォロワーから%sが%u個届いています"; `MissionUtility::Sphere211RentalBonusItem(count)` picks the row by `rental_count` ≤ count; (d) the player's own rentals are what is counted (nobody else rents), and the present box ("届いています"). Seen in game. Test `sphere211/rental`. |
| **Departed characters** can't sortie again until 帰還. | (b) | uimsg_sphere211_return_dialog "帰還をすることで全てのキャラが再度出撃できるようになり"; the menu counts them (出撃数). |
| **EX characters** (`master_role.rank` 5): a sortie with an own EX character in any of the four slots uses one of `master_global.max_revive_count` (3) uses, counted in `sphere.revive_count` and sent as `Player.sphere211_revive_count`; only the EX character(s) depart, their companions don't; 帰還 (and a season change) gives the uses back; with no use left the sortie is a plain one: everyone departs and no use is counted (**(d), a rule we couldn't reverse engineer**: the client's dialog shows 残り 0 回 and doesn't stop the start, and what the online server did isn't known; refusing would send the player back to the title, since Sphere211MissionStart's error handling type is 2; the user's choice, 2026-10-03). Added 2026-10-03 (agent srv-bugfix-1; found by R18a). | (a) + (b) + (d) | (b) `CParameterUtility::IsRoleDeity` (@01820c3c) is rank == 5; `CSphereMissionDetail::NextPhase` (@01c1989c) checks the four slots' own characters (`tCharaData::Type()` 0, never a rental) and with an EX character opens `CDialogManager::OpenSphere211SallyDialogWithDeity` with `max_revive_count` minus CParameterManager+0xf48 (`CPlayerInfo`+0x910, the field `CPlayerInfo::Initialize` registers as `sphere211_revive_count`; `UpdateMissionStartPlayerInfo` takes it from the start's answer); `CApiNotify::OnReturnSphere211Res` (@014e343c) zeroes +0xf48 at 帰還. (a) uimsg_sphere211_mission_start_with_deity: "EXキャラクターと一緒に出撃したキャラクターは、ミッションクリア時に「出撃済み」になりません。ただし、EXキャラクターは「出撃済み」となります。使用可能回数　残り　%d 回 ※使用可能回数は帰還することで回復します。" (d): the EX character departs at the start like every sortie (the text says "on a clear"), one use per sortie however many EX characters it has, and the refusal and its code (the client's dialog says 残り 0 回 but doesn't stop the start: `CSallyDialog::OpenSphere211MissionStartWithDeity` is a plain yes / no, and `CSphereMissionDetail::IsEnableMissionStart` doesn't read the count). The seeded roster has no EX character, so no session shows the dialog; test `sphere211/ex-sorties`. |
| **AutoMemberSelect:** the 4 strongest characters that haven't sortied: by level, then rarity (`master_role.rarity`), then limit break. | (d) | |
| **MissionEnd:** the core MissionEnd of the event mission (EXP, FOL, drops, first-clear presents, (a)); the cell is cleared; the clear streak grows. Without a cell (the request's, else the one playing) it isn't answered (as the core MissionEnd of an unknown mission, "2.3 MissionEnd (win)"). | (a) + (b) + (d) | |
| **Treasure boxes of a battle:** the floor's `treasure_num`, + `boss_add_treasure_num` on a boss cell (`lottery_type` 2), + `rare_add_treasure_num` on a rare cell (`lottery_type` 4 or 6), + the streak bonus (`master_sphere211_treasure_streak_bonus`: the highest row whose id (streak) is reached). Sent as drop types 0 (the battle's own, no badge), 1 (streak), 2 (boss), 3 (rare). | (a) + (b) + (d) | (a): counts; (b): the badges, the board's "10連でドロップ数+1" hint matches the row id 10; (d): which lottery types are boss / rare, and type 0. |
| **Lost or retired battle** (`Sphere211MissionFailed`): the cell stays uncleared and playable, the stamina stays spent, the clear streak resets; the core MissionFailed ends the play record. | (c) + (d) | |
| **Continue** (`Sphere211MissionContinue`, the bool 1): `master_global.continue_use_coin` (100) coins times a running continue campaign's magnification (`master_campaign` type 9 for every mission type, model 99, or type 5: none in 3.7.0; the first in the master's order, on the event calendar, as MissionContinue's), free coins first; error 20000 when short, 10403 with no battle in progress (no play record); every Sphere 211 battle can continue (`OpenContinue` checks the mission's `is_continue` only for a type other than 5); the battle goes on. **Declined** (the bool 0): the run ends as a failure, as `Sphere211MissionFailed` (the play record ends, the streak resets, the cell stays uncleared and playable, the stamina stays spent), `is_mission_continue` false, nothing paid; the client then sends `Sphere211MissionFailed` with the battle log, as for any lost battle (b: seen in the session `sphere211-continue`, the decline `OpenContinue` sends by itself with no coins), which finds the run ended already. (Until 2026-10-06 the bool was ignored: a decline was charged and the battle went on.) | (a) + (b) + (d) | (b) the defeat dialog "紋章石100個を使用することで全員が復活できます" with 300000 → 299900 (seen in game); (a) free coins first ("Stocks and wallet"); (d) the code. Until agent a5-sphere it was free. (b) the bool and the price: `CPauseMenu::ReqeustContinue` @01dad704, `OpenContinue` @01dacf90 (`GetDecMissionContinueCoin(99, 0)`, then the mission's type). Test `sphere211/dive` (continued, declined, はい without a battle); replay corpus `sphere211-continue`. |
| **FloorClear:** the floor's clear present (`master_sphere211_floor_clear_present` of the season's group, the highest `level` at or below the floor), `floor_clear_treasure_num` more boxes, and the next-floor count `lot_floor_num`. | (a) + (d) | (d): the highest level row at or below. |
| **Next-floor count (warp access):** the highest `master_sphere211_floor_transfer_level` open now whose `required_treasure` the dive's gathered boxes reach; its rate group's `floor_num` lotted by `weight`; at least 1. | (a) + (b) + (d) | (b): `MissionUtility::Sphere211WarpAccessLevelAndExp`, `GetSphere211TransferRateId`; (d): at least 1. |
| **SelectedFloor(n):** the floor n above the current one (the n-th entry of the offered list), clamped to 1 .. `lot_floor_num`; a new floor is lotted. | (b) + (d) | (b): the request's value was 1 when 2F was chosen on 1F; (d): the clamp. |
| **Reroll** (`Sphere211UseRerollItem`): the season's `reroll_item_id` × `reroll_item_num` re-lots `lot_floor_num`; error 10206 when short. | (a) + (d) | |
| **Stamina heal** (`Sphere211StaminaHeal`): one of the season's `heal_item_id` adds its `master_item.heal_point` (1), capped at the maximum; error 10206 when short. | (a) + (b) + (d) | (a) heal_point 1, the item text "スフィア・スタミナを1回復できるチケット"; (b) the dialog: 現在のスタミナ 8 / 9 → 回復後 9 / 9 (seen in game; until agent a5-sphere the server refilled to the maximum); (d) the cap and the code. Test `sphere211/items`. |
| **Achievements (types 61 / 62):** type 61 "スフィア211の N F以上に到達する" (per season) and type 62 "スフィア211のミッションを N回クリアする" (スフィア週間チャレンジ, the weekly challenge: 7-day windows from Thursday 14:30; and campaign rows) are active while their window, moved by the current season's shift, covers the server clock; `limit_at` = the moved `closed_at`. Progress: the highest floor entered (61) / the Sphere 211 battles won (62) while the moved window ran, from the dive's log. The Sphere 211 answers carry the `Achievement` state. | (a) + (b) + (d) | (a) the rows, texts, windows; (b) the board's 実績 button shows `CParameterUtility::NumGetAchievement()` over the `Achievement` state; (d) the windows move with the season, "won" = a `Sphere211MissionEnd`. The other types keep the real clock (`api/daily/login_bonus.cpp`). Seen in game (after agent a6-deepspace made `Achievement` an id-keyed map): the board's 実績 → イベント lists スフィア週間チャレンジ 5 / 10 / 15 / 20 回 with 残り時間 あと1日 (the replayed week ends Thursday 13:59), 週替わり lists 週替：スフィア211を15回クリア (`sphere211_continue_session.sh`). Test `sphere211/achievements`. |
| **Test hook (port, not a game rule):** `sphere.debug_enemy_level` (the `sphere_meta` key `test_enemy_level` before schema version 3), when a script writes it into the state DB, overrides the enemy level of the next starts (`sphere211_continue_session.sh` loses a battle with 250; `sphere211_session.sh` sets every enemy to 30, since the client's unseeded battles sometimes lost the level-65 cell or the level-90 boss; both set it back to NULL afterwards). The server never sets it. | — | |
| **帰還 (ReturnSphere211):** the gathered boxes are analysed: each box's rank lotted with the current floor's `master_sphere211_treasure` s..d weights, then opened: one row of that rank's `master_sphere211_treasure_contents` common drop (`master_common_drop`, by `rate_weigh`), granted to the player. Every departed character comes back; the clear streak resets; the dive stays on its floor; nothing is charged. | (a) + (b) + (d) | (b): the return dialog shows the current floor's rates and says the streak bonus resets, and "出撃したキャラクターが帰還しました"; (d): ranks lotted at 帰還 rather than when found, granted directly. |
| **Ranking** (`GetSphere211RankingInfo`): a local ranking of one player, the season's best floor, rank 1. | (d) | |
| **EquipAuto:** answered with the state; the client keeps its own equipment. | (d) | |

<a id="sphere211-state"></a>
### State (`server.sqlite3`)
`sphere` (one row: season, floor, map template, streak, gathered-box total, sphere stamina, the floor-clear info, the previous season's result), `sphere_cell` (the current floor's cells: box, mission, enemy level, cleared, playing), `sphere_departed` (uids out until 帰還), `sphere.revive_count` (the EX sorties since 帰還), `sphere_box` (unopened boxes, their rank once lotted), `sphere_rank` (best floor per season; a new cycle starts it over). Added by agent a5-sphere: `sphere.cycle`, `season_wins`, `end_pending`, `debug_enemy_level` (the season's cycle, its battles won, whether the end result is still to be shown, the test hook; the key-value table `sphere_meta` before schema version 3), `sphere_rental` (the floor's lenders that lent), `sphere_rental_day` (Sphere 211 rentals per rental day, season, paid), `sphere_log` (battles won and floors entered, server clock, for the achievements).

<a id="sphere211-not-done"></a>
### Not done
- `GetSphere211RankingInfo`'s `Sphere211RankingDetailInfoMap` and the ranking screens (not driven by the session).
- The rental bonus counts only the player's own rentals; `Sphere211FollowFloorInfoList` puts every lender on the player's floor.

<a id="sphere211-register"></a>
### Player-visible (c) and (d) rules (Sphere 211)

| Rule | Label |
|---|---|
| The last season repeats after the service's end (dates moved) | (d) |
| Missions with missing maps are never lotted | (d) |
| The dive starts on floor 1; 帰還 keeps the floor | (d) |
| Start cell and neighbours of cleared cells are playable | (c)/(d) |
| Which cells count as boss / rare for the extra boxes; the battle's own boxes carry no badge | (d) |
| Ranks lotted at 帰還; boxes granted directly | (d) |
| Continue costs 100 coins (times a continue campaign); a declined continue ends the battle as failed; retire keeps the stamina spent | (a)/(d) |
| The rental slot lends clones of the player's own characters, once per lender and 3 per floor | (d) |
| The Sphere 211 rental bonus counts the player's own rentals | (d) |
| A season's ranking rank is 1 when a battle was won in it; the repeated last season pays season 12's rewards | (d) |
| Days before the first season play the season of the same date a year later | (d) |
| Sphere 211 achievements run on the season's moved dates | (d) |
| An EX character departs at the start (its companions never); one use per EX sortie; with the 3 uses spent an EX sortie is a plain one (everyone departs, nothing counted), not refused | (d) |
| Auto party order | (d) |
| Local ranking rank 1 | (d) |
| Refusal codes 10004 / 10206 / 10208 / 20000 | (d) |

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| Sphere 211 | past the last season (13, closed 2021-06-24) the last season repeats, its dates moved by whole season lengths (also in the client's master) | (d) | "Sphere 211"; without it the mode is "outside the season" for good |
| Sphere 211 | a missing battle map skips the mission (cell battles are lotted among playable missions only; nothing playable: the unfiltered lot) | (d) | "Sphere 211"; decided from the files at run time |
| Sphere 211 | a dive starts on floor 1; 帰還 keeps the floor; a new season starts a new dive | (d) | "Sphere 211" |
| Sphere 211 | an EX-character sortie with no use left (3 spent) is accepted as a plain sortie: everyone departs, no use counted | (d) | a rule we couldn't reverse engineer: the client doesn't stop it (its dialog says 残り 0 回) and the online server's answer is unknown; a refusal would send the player to the title (error handling type 2); the user's choice 2026-10-03. "Sphere 211", test `sphere211/ex-sorties` |
| Sphere 211 | the start cell and the uncleared neighbours of cleared cells are playable (`can_play`) | (c)+(d) | "Sphere 211" |
| Sphere 211 | treasure: the battle's boxes + boss extra (lottery type 2) + rare extra (4 / 6) + streak bonus; ranks lotted at 帰還 with the current floor's weights | (a)+(d) | "Sphere 211"; the counts are (a), which cells count as boss / rare is (d) |
| Sphere 211 | continue after a defeat costs 100 coins (continue_use_coin, times a continue campaign); declining it ends the battle as failed, as retire; retire resets the streak, the stamina stays spent | (a)+(d) | "Sphere 211" |
| Sphere 211 | the rental slot lends clones of the player's own characters (once per lender, 3 per floor); their rentals count for the Sphere 211 rental bonus | (d) | "Sphere 211" |
| Sphere 211 | season end: rank 1 of a one-player ranking when a battle was won, with that rank's reward; the end result shown once | (d) | "Sphere 211" |
| Sphere 211 | auto party: the 4 strongest characters that haven't sortied (level, rarity, limit break) | (d) | "Sphere 211" |
| Sphere 211 | local ranking: the player is rank 1; season end result rank 1 | (d) | "Sphere 211" |

<a id="tower"></a>
## Tower (試練の遺跡; opt-in `--restore-tower`; `server/src/api/tower/tower.cpp`)
The tower was closed in 3.7.0 (`CParameterUtility::IsOpenTowerMission` returned 0). The opt-in opens it on the client (docs/client-changes.md "The tower (試練の遺跡) opened", "Tower banner rows added to the client's master copy"; docs/notes.md "Tower layout") and this module serves its data. Entry: home → スフィア211 → 試練の遺跡. Its battles are `master_tower_mission` rows played through the core `MissionStart` / `MissionEnd` (Common::MissionType 2). Unit tests `tower/banner`, `tower/client-master`, `tower/lists` (`server/src/api/tower/tower_tests.cpp`); session `port/scripts/tower_session.sh`.

- **Lists** (with every full player load, and again in a tower battle's `MissionEnd`): `ActiveTowerMissionList` {`TowerArea`: {area id: {mission_ct, is_new, is_last_play}}, `TowerMission`: {area id: [{id, is_new, is_clear, is_last_play}]}}, `TowerSchedule` [{opened_at, closed_at}], `Player.tower_try_count`.
  - (b) the shape: the event lists' (`ActiveEventMissionList`); `MissionUtility::GetEventAreaList` type 2 walks the `TowerArea` map (CParameterManager+0x1c68) by area id and reads each area from `master_tower_area`; seen working in game.
  - (a) an area is listed while its `opened_at`..`closed_at` covers the event calendar (`server::event_now`; `--clock` aware). In the 3.7.0 master only `tower_01`..`05` (呪い, 封印, マヒ, 凍結, 毒) run past 2021 (until 2030).
  - (b)+(d) only areas the client will show: `tAreaInfo`'s constructor drops an area whose `master_banner_id` has no `master_banner` row, so an area is listed only when its banner row exists or a stand-in row can be made (below).
  - (a) a floor (mission) is listed when it has no `unlock_mission_id` or that mission is cleared; (d) a floor whose battle maps or enemy models are missing is left out (`events::mission_playable`, decided from the files at run time).
  - (d) `is_new` until cleared; an area's `is_new` when any listed floor is; `is_last_play` of a floor = the mission of the last `MissionStart`; the area's `is_last_play` false.
  - (d) the lists are refreshed in the `MissionEnd` of a tower battle, so the floor a clear unlocks is listed at once (when the online server refreshed them isn't known).
  - (a) `Player.tower_try_count` = `master_global` `Tower_Challenge_Count` (3). (d) not counted down: every floor can be played any number of times. The client's tries (`StaminaUtility::NowStamina(1)`, CParameterManager+0xc48) show 3/3 on the extra-dungeon banner.
- **Stand-in banners** (client master copy, `tower::client_banners`): (a) `master_tower_area` names `banner801`..`banner805` for `tower_01`..`05`, which the 3.7.0 `master_banner` lacks; (a) the 16 surviving tower banner rows show `banner_TrialSpace_<the area's tower number, 3 digits>` (with `_002` for some); (d) a missing row is made with the first of `banner_TrialSpace_NNN`, `_NNN_002`, `_NNN_001` whose image the port can load (the 3.7.0 download has `banner_TrialSpace_001`..`005`), the area's dates and no URL. No loadable image, no row, and the area isn't listed.
- **Rewards:** the core `MissionEnd` (master drops: the first-clear coin reward, the tower coins); (d) nothing tower-specific (no ranking, no coin exchange; the ランキング / イベントメニュー buttons are the event menu's, not served).

<a id="settings-account"></a>
## Settings and account
Code: `server/src/api/settings/` (the options, the birth month, the read marks, the story library; docs/unimplemented-apis.md part 3 step 3.3). Tests `settings/config`, `settings/birth-year-month`, `settings/read-marks`, `settings/scenario-library`, `server/schema-migrate-v14`; the `profile` and `campaign` replay corpora; session `port/scripts/settings_session.sh` (in-process and `--server`).

<a id="settings"></a>
### Options (`GetConfig`, `UpdateConfig(u32 master_config_id, s8 const* value, u32 type)`, `ResetConfig`)
- **What the client reads (b):** `ConfigInfoList` [`ConfigInfo` {`master_config_id`, `value`, `type`}] (CConfigInfoList, CParameterManager+0x9480, replaced whole by a response that carries it). `CUIUtility::IsConfigListCheck` (@01eea65c) finds an option by CHash32 of its `master_config.id_label` and reads it as on when the value is `"true"`; an option not in the list is the caller's default (off for the one-time storage options). Its readers are not only the settings screen: CItemNumWarning, CPresentbox::IsNumWarning, CMissionMenu::StateCheckPlayStart, CTradeMenu, MissionUtility::GetItemNumWarningType (the one-time storage options), IsAutoEquipSkill / IsAutoEquipSteal(Party), IsGalaxyPassIconShow. `CApiNotify::OnUpdateConfigRes` (@014d89a0) puts the answered `ConfigInfo` into the list (replacing the entry with its id or appending it), so UpdateConfig's answer must carry it.
- **The options:** every `master_config` row (7) **(a)**; `master_config.id` = CHash32(`id_label`) for every row **(a)**, which is how the client names them (`is_one_time_storage` = 4025152546, その他設定's 一時保管庫設定). A row's value is the player's (table `config`, schema version 14) or else the master's default (`master_config.value` / `type`) **(a)**.
- **UpdateConfig** stores the value string and type as sent **(b)** (the client's "true" / "false"); an id `master_config` doesn't have is refused with 10403 **(d)** (the client sends only master ids). Answer: the player state and `ConfigInfo`.
- **ResetConfig** (初期設定に戻す) deletes the player's rows: every option back to the master's default **(a)**. Answer: the player state and `ConfigInfoList`.
- **GetConfig** answers the player state and `ConfigInfoList`. `Option` (COptionInfo: frame rate, volumes) isn't sent **(d)**: the client keeps those settings itself, and a response without the key leaves its copy unchanged.
- **The player load** (Login, GetPlayer, ...) carries `ConfigInfoList` too **(b)**: only the settings screen sends GetConfig, so without it an option changed before a restart would read as off (and the master's "true" defaults as off) until the settings screen is opened.
- **For other modules:** `settings::config_on(ctx, label or id)` (`api/settings/config.h`; `kOneTimeStorage`, `kOneTimeStorageExceptGacha`): on when the value is exactly "true" **(b)**. The screen's texts **(b)**: 一時保管庫設定 on sends equipment drawn from the gacha to the one-time storage; ガチャ以外で入手した装備アイテムを一時保管庫に送る does the same for equipment obtained otherwise.

<a id="account"></a>
### Birth month, read marks, guide popups (`Get/UpdateBirthYearMonth`, `ReadExpirationInfo`, `SendGuideInformation`)
- **GetBirthYearMonth:** `Birth` {`year`, `month`} once entered **(b)** (CBirthInfo); never entered: refused with 10009 (誕生年月が確認できません。) **(b)**, the one code on which its result lambda (@019587d8, BirthDialogUtility::RequestGetAge) opens the birth dialog.
- **UpdateBirthYearMonth:** the request is the string `"%u-%02u"` (CNetworkUtility::BirthYearMonthNumber2String @015f7c60, char[8]) **(b)**; the client's ranges, year 1900..2100 and month 1..12 (BirthYearMonthString2Number @015f7cc0) **(b)**, are the columns' checks; anything else refused with 10403 **(d)**. Stored as entered in `player.birth_year` / `birth_month` (schema version 14), entering again replaces it **(d)**. Answer: the player state and `Birth`.
- **No age limit (d):** the birth month isn't checked against anything: a local game has no monthly spending limit for minors (docs/unimplemented-apis.md, Decisions).
- **ReadExpirationInfo(ids)** (期限情報, `CTermInfoUI::Progress` @01c8a19c: the ids it shows): ids not in `master_expiration_information` are logged **(a)**; nothing is stored and `ExpirationInfoList` isn't answered **(d)**: the local server keeps no expiration state (no response carries it), so a read mark has nothing to change.
- **SendGuideInformation(id)** (`CGuideInformation::Progress`, a guide's link followed): `GuideInformationInfoList` is the list of guide ids the popup shows (CParameterManager+0x89c8; `CGuideInformationUtility::GetGuideInformationData` @01c64328) **(b)**; the local server shows no guide popups **(d)** (they announced the service's dated campaigns and shop items; no player load sends one), so the answer's list is empty and nothing is stored.
- **UpdateSession** isn't the library's: the wire layer answers it in the bridge handshake (`server/net/game.cpp`), and in-process its only caller (`BridgeNotify::OnReceive`) never runs (no bridge on the FakeApiCaller) **(b)**.

<a id="scenario-library"></a>
### シナリオライブラリ (`GetScenarioLibraryInfoList(u32 episode_type_id)`)
- **What the client reads (b):** `WorldMapScenarioLibraryInfoList`, a plain array of u32 (InfoBaseValueArray, CParameterManager+0x1f08) that `CScenarioLibrary::CreateStoryListFromInfo` (@01c74ef0) reads as mission ids: `master_mission` ids for Episode 1's library, `master_world_map_mission` ids otherwise (it keeps mission_type 1 and 2); it groups them by `master_scenario_library_id` into the chapters. The request's argument is the episode type of the planet select it was opened from (CParameterUI+0x14c; Episode 1's planet select sends 2693101203, `chapter_0`).
- **The rule:** the player's cleared missions (the core's `mission` with `cleared = 1` and the story campaign's `campaign_clear`) whose chapter (`master_scenario_library_id`) has `master_scenario_library.episode_type_id` = the argument **(a)**; the library replays the story of cleared missions **(c)**.
- A `--campaign-seed` chain lives in the campaign's memory until its first clear saves it, so the library lists it only from then on **(d)** (the library reads the state DB, not the campaign module's memory).

<a id="settings-register"></a>
### Player-visible (c) and (d) rules (settings and account)

| Rule | Label |
|---|---|
| The birth month isn't used for a spending limit; it is stored as entered and can be entered again | (d) |
| No guide popups (お知らせ guides) are shown; following one stores nothing | (d) |
| 期限情報's read marks aren't stored (the server keeps no expiration state) | (d) |
| シナリオライブラリ lists the story of cleared missions | (c) |

<a id="core"></a>
## Server-wide: architecture, seed, wire, CDN
What no single domain owns: the in-process route and the state, the extension registry, the seed, soa-server's wire layer and CDN.

<a id="architecture"></a>
### Architecture
- **Route.** With the in-process server, the port brings up `FakeApiCaller` as the API caller (the FakeApiCaller route, on with `--server inproc`), and `--download-dir` defaults to `work/SOA-3.7.0-canonical-data.zip`.
  - The FakeApiCaller request hooks pass each method's arguments to `server_port::capture`, port/src/native/api/server_adapters.cpp, which keeps the request until it is answered. Arguments are read from x1..x7 by the mangled signature: integers, `s8 const*` strings, `CSTLVector<u64/u32>` references.
  - `ServeProgress` answers each request through `server::answer` (the library's one request lifecycle, as soa-server's wire uses it). An API the server has no handler for is answered `{}` and logged `no handler: <Method>` (until 2026-10-05 it came from the static files of `--fake-server`, `port/fakeapi/responses`: `docs/history/fake-server-responses.md`).
  - With `--server HOST`, none of this runs: the client's own NetworkApiCaller talks to soa-server.
- **State.** A SQLite file, `DATA/server.sqlite3` (`--db`). Tables:
  - `player`: id, search id, name, level, exp, fol, stamina and its timestamp, free and paid coins, home character, party;
  - `roster`: uid, role, level, exp, limit break, awakening, skill levels, the equipped skills, the seeds' `add_*`, equipped weapon and accessory, the assist (favor isn't a roster column: it lives in `favor`, section 8);
  - `favor`: per same_role_id favor points and today's taps (section 8);
  - `items` (unique items: weapons, accessories), `stock` (stack items);
  - `party_set` (a row per set 1..`party_set_max`: icon, lock), `party_member` (a set's slots: the member, and the set's equipment, skills and assist for it; `party` until schema version 6);
  - `mission` (cleared, play and clear counts, first clear), `play` (the mission in progress: its mission and type, party set, start, stamina, surprise roll and helper; `play_ext` held the type, surprise and helper until schema version 7), `play_member` (its battle party in order: an owned character's uid, or a mission NPC's battle uid; the `play.uids` text until schema version 7);
  - `gacha_history` (a draw: the gacha, the role and the drawn character's or weapon's uid, the rank, the coins);
  - `presents` (with each present's box line, `text`; `present_texts` until schema version 8), `login_bonus`, `achievements`, `meta` (the uid counters and the seed path only, since schema version 3).

  The modules' tables (favor, gear, growth, shops, Sphere 211, deep space, events, …) and the schema's versions are `server/src/state/` (`schema.cpp`; `docs/history/PLAN-schema.md`); how a state is opened, migrated and checked is `server/src/state/README.md` (every session's and tests/diff run's end state is checked there too: foreign keys, master references, the schema version; tests/TIERS.md "The permanent gates"). Schema version 2 (PLAN-schema S2) dropped what nothing read: `roster.favor`, `mission.best_rank`, `exchange_counts.shop_id` and the tables `view_flags`, `gear`, `box_gacha` and `planets`. Schema version 3 (S3) moved the keys of `meta`, `sphere_meta` and `counters` that were structured state into columns: `player.tutorial_status`, `view_status`, `view_status2` (the u64 words as their int64 bits), `kiyaku_version`, `title_id`, `support_uid`, `time_saving_count`, `time_saving_day`, `login_bonus_popup_pending`; the table `ds_state` (deep space's play-limit periods); `sphere.cycle`, `season_wins`, `end_pending`, `debug_enemy_level` (`sphere_meta` dropped). Schema version 4 (S4) merged `roster_ext` (the seeds' `add_*`, the equipped skills) and `assist` into `roster` (`skill1..3` became `skill1..3_level`), rebuilt `roster` and `player` as STRICT tables with the state's first foreign keys (`roster.weapon_uid` / `accessory_uid` → `items`, `roster.assist_uid` → `roster`, `player.home_uid` / `support_uid` → `roster`, `player.title_id` → `titles`, `player.party_id` → `party_set`), and gave every player the `party_set` rows 1..`party_set_max`. "None" is NULL in those columns (it was 0); the replies still send 0. Schema version 5 (S5) rebuilt `items` and `gear_items` STRICT, with `gear_items.item_uid` NULL for the gear box and → `items` ON DELETE CASCADE. Schema version 6 (S6) merged `party` into `party_member` (one row per slot: the member's `uid`, and the set's `weapon_uid`, `accessory_uid`, `skill_id1..3` (were `skill1..3`), `assist_uid`; NULL for none) and rebuilt `party_set` and `party_member` STRICT with `party_member.party_id` → `party_set` ON DELETE CASCADE and its character and item references ON DELETE SET NULL. Schema version 7 (S7) merged `play_ext` into `play` (one row: what MissionFailed deletes is all of it; `campaign_lots`, never read, dropped), moved the battle party from the `play.uids` text to `play_member` rows (`uid` → `roster` ON DELETE SET NULL, `npc_uid` for a mission NPC, the rows → `play` ON DELETE CASCADE; `play.party_id` → `party_set` ON DELETE SET NULL), a deep-space ship's crew from `ds_ship.uids` to `ds_ship_member` rows (slot 1..8; → `ds_ship` ON DELETE CASCADE, → `roster` NO ACTION: a character out on a ship can't be deleted), and gave `ds_log` its id (all STRICT). Schema version 8 (S8) merged `present_texts` into `presents` (the stored box line is the present's `text`; NULL: built from the reason) and rebuilt `presents` STRICT, with a wallet present's `content_id` (content type 3 FOL, 4 free coins: no content) NULL instead of 0 (the replies still send 0). Schema version 9 (S9) applied the time and boolean conventions (`docs/history/PLAN-schema.md` 3.1): `favor.event_drop_at` is seconds (it was the formatted text), `favor.tapped_at`, `titles.got_at` and `premium_pass.last_at` are NULL for never (they were 0), the login bonuses' page counters are `day_index` (`login_bonus.day`, `premium_pass.day`), the rental days' starts `rental_day` (`follow_rental.day`, `sphere_rental_day.day`), deep space's `ds_area.last_play` is `is_last_play`, and the booleans of `mission`, `ds_area`, `follow_rental`, `sphere_rental_day`, `event_rank_score`, `wboss`, `sphere_cell` and `sphere_rental` are checked 0 / 1; those twelve tables are STRICT. Schema version 10 (S10) rebuilt the rest, the modules' tables and the core's last ones, so every table is STRICT: deep space's `ds_offer` / `ds_ship` (→ `ds_area` ON DELETE CASCADE) and `ds_bonus` (→ `ds_ship` CASCADE), `ds_offer.ship_id` → `ds_ship` SET NULL; `gacha_history`'s uid split into `character_uid` / `item_uid` (→ `roster` / `items` SET NULL; a weapon draw's `role_id` NULL), `box_slots` → `box_state` CASCADE; `wboss_clear` → `wboss` CASCADE (deferred); `sphere_departed` → `roster` CASCADE; `favor_bonus_state.lot_uid` → `roster` SET NULL; `unlocks.by_mission` → `mission` (deferred); `wire_device.player_id` → `player` SET NULL. The 0s that meant none or never are NULL there (`ds_offer.closed_at` / `ship_id` / `updated_at`, `wboss.hunt_until`, `favor_bonus_state.day_at` / `healed_at`, `wire_device.player_id`); the replies send what they sent. Schema version 11 (S12) moved the story campaign's progress into the state DB: `campaign_clear` and `campaign_last` (→ `campaign_clear` ON DELETE CASCADE), imported from the data dir's `server_campaign.txt` ("Campaign progression"). Schema version 12 added `player.is_3d_home` (0 / 1, default 1: the home's 2D / 3D mode, `Home3DAnd2DSwitching`; [Home 2D / 3D](#home-2d-3d)). Schema version 13 added `is_new` to `roster`, `items` and `stock` (the NEW badges, [NEW badges](#new-badges)); schema version 14 added the table `config` (the options the player changed, by `master_config` id) and `player.birth_year` / `birth_month` (NULL: never entered; [Settings and account](#settings-account)). Schema version 15 added `items.stored_at` (the equipment storage) and the table `one_time_storage` (the overflow box; [Storage](#storage)). Schema version 17 added the tables `stamps` and `stamp_slots` (the chat stamps; [Chat stamps](#stamps)).

  `tools/server_state.py DATA/server.sqlite3` prints it.
- **Clock.** `--clock "YYYY-MM-DD HH:MM:SS"` starts the server's clock at that time, so past banners can be replayed. Times are local time strings.
  - Every response carries `data.Time`, the server's clock. **(b)** `CServerTime::UpdateServerTimeOffset` parses it after each response and keeps its difference from the device clock, so the client's `CTimeUtility::NowTime` follows the server.
  - The client computes the stamina it shows from that clock: `StaminaUtility::NowStamina` = `stamina` + (NowTime − `stamina_update`) / heal time, up to the maximum.
- **`service_stop_day`.** The master the server's CDN serves has no `master_global.service_stop_day` row (`apply_client_master`, applied by `server/src/cdn/served_master.cpp`; both server modes), as in service. 3.7.0 reads the row only for its service-end check (Conventions above; the APK's built-in master is handled by platform370's patch, `docs/client-changes.md` "Emulator mode"). The handling before the rebase (the frozen clock, the `lib_sqlite` hook): `docs/history/server-rules-3.8.0.md`.
<a id="master-source"></a>
- **Master DB (a startup rule; `soaserver/master_source.h`, `server/src/cdn/master_source.cpp`).** The first that exists: `--master` (a file); `data/basmaster-3.7.0.sqlite3` in the checkout (found through the `work` link from a worktree); else **derived from the user's game files**: the 3.7.0 download's `sqlite/basmaster.sqlite3` (`--download` / `--download-dir`, else the checkout's `work/SOA-3.7.0-canonical-data.zip`, else a download in the install dirs (the program's folder and its `game/`, `common/include/soa/install.h`; zips: `common/include/soa/game_files.h`); `SOA-3.7.0-canonical-data.zip` read in place, or an extracted folder, `common/include/soa/file_tree.h`) decrypted with the client's own ADLD code (`common/include/soa/adld.h`, key from the name `sqlite/basmaster.sqlite3`) into `DATA/master/basmaster-3.7.0-download-<SHA-1 of the encrypted file, 12 digits>.sqlite3` (soa: its data dir; soa-server: `--data`, else its default data dir `~/.local/share/soa-server-370` / `%LOCALAPPDATA%\soa\server-370`), once, and reused while the source's hash is the same. **(a)** The decryption is byte-identical to the committed `data/basmaster-3.7.0.sqlite3` (SHA-1 `ca6131f2…`; tests `cdn/master-source`, `cdn/master-source-resolve`). Last resort (read with `soa_zip` by the server itself; an embedder hook, `set_zip_reader`, of the first version is gone): the APK's built-in `assets/builtin_data/sqlite/basmaster.sqlite3` (a stored entry, the same ADLD key), logged as a warning: **(d)** it is older than the download's (the app's build-time master), so content added later is missing from it; neither program runs its server without a download anyway (soa's `--server inproc` needs one; soa-server serves no CDN without one). The result is `config().master`, which the server, the CDN's served master and the campaign module (after `--campaign-master-db`) all read. Why: the decrypted master is the game's own content, so the release packages (README.md "Packaging") don't ship it.

<a id="extension-modules"></a>
### Extension modules
- **Extension registry** (`server/{include/soaserver/ext.h,src/core/ext.cpp}`). server.cpp's dispatcher asks `ext::find(method)` for methods it doesn't answer itself; a module registers handlers with `ext::add_api({"Method", ...}, fn)` from its `register_<module>()` function (`server/src/core/modules.cpp` calls those in one fixed order). `ext::add_player_load` (OnPlayerLoad) adds keys to the full-state player responses (`NoLoginStart`, `Login`, `GetPlayer` ...). The modules' tables are the state module's (`server/src/state/schema.cpp`, created when the state DB opens). A handler gets an `ext::Ctx`: the state and master DBs (inside the request's transaction), the server clock, and the core's own `base_data`, `grant`, roster / stock / item lists, EXP curves and caps.
- **Module tables** (in `DATA/server.sqlite3`): the seed-raised stats `add_*` and the equipped skills are `roster` columns (the growth module's `roster_ext` table until schema version 4), `shop_counts` (item-shop purchases per row: this period, the period start, all time), `exchange_counts` (exchanges per contents row), `counters` (event counts for achievements: boosts, limit breaks, evolutions, weapon / accessory boosts, grade-ups, exchanges, seeds). The core's `login_bonus` and `achievements` tables hold the login days and received achievements.
- **Refusals.** A request the rules refuse (not enough materials, FOL or coins, locked or equipped items, sold out, over a limit) changes nothing; it goes through the core's error path with a client error code (see [Verification](#growth-verification) for the codes) and the client shows its own error dialog.
- **Response shapes.** The owned lists that changed are sent whole (`StockItem`, `Item`), as the core does. The per-API result infos carry the field names of their `Initialize` (b); `tools/fakeapi_fields.py` finds most, and the short ones the compiler builds inline (`id`, `num`, `count`, `status` ...) were read from the decompiled `Initialize` bodies.

<a id="seed"></a>
### Seed (first run)
The seed is the first save that exists of `--seed FILE` (`--seed` counts on a state's first run only: an existing state keeps its player; (d) a `--seed` file that holds no player — no `player_name` or `person_size`, e.g. the client's settings-only Game.xml — is warned about and skipped: the user, 2026-10-04), the committed sanitized 3.7.0 save `data/saves/seed/Game.xml` (found from the executable's location, `port/src/core/paths.h`; a release build looks only in `--repo DIR` and the install dirs, so a package, even unzipped inside a checkout, has none unless the user puts one at `<package>/data/saves/seed/Game.xml`: the user, 2026-10-07), and, in soa's in-process server, the client's own `DATA/data/shared_prefs/Game.xml` (`ServerConfig::client_save`; no option: `--seed` names any other save) when it holds a player (`player_name` or `person_size`, the keys the seed reads) (`server/src/state/seed.cpp` `seed_source`, `save_holds_player`). (b)+(d): on a fresh data dir the client writes its own Game.xml at its first start (its settings only: `BAS:EffectAlpha`, `BAS:VoiceLanguage`, `BAS:PlayerName` 0, ...; 9 keys) before its first request opens the server's state; seeding from that made a nameless player with no characters (found by the package's first run, 2026-10-04). **With none of them** (a packaged build ships no seed save: the user, 2026-10-04), a new state gets no player, the same as `--new-player`: the client's Login finds no account and it runs its own new-player flow (the tutorial, its starter characters; `CreatePlayer`) — (d), rather than seeding a finished-tutorial player with no characters and no party, which the client can't use.

**Test seed.** The scratch-server selftests (`--selftest "server/"`) seed from the committed synthetic `server/tests/fixtures/test-seed.xml` instead, so they run in a fresh checkout with no real save. It holds no real account data: `BAS:PlayerID` `LOCAL00001`, the made-up name "Tessa", level 60, FOL 250,000, all 10 planets open, and 38 roles picked mechanically from the 3.7.0 master (the lowest ids per rarity: 12 ★3, 10 ★4, 12 ★5, 4 ★6; home = the first ★5). `tools/make_test_seed.py` regenerates it. Tests read their expectations from the seed file, not from constants.

| Value | Rule | Source |
|---|---|---|
| player search id, name, level, EXP, FOL | `BAS:PlayerID`, `player_name`, `player_level`, `player_exp`, `player_fol` from the save (name, level, EXP and FOL, e.g. Fayt, 87, 1048, 1,675,605). The search id is **not** copied: the save's `BAS:PlayerID` is a real account's id, so the local player always gets the sanitized `LOCAL00001` (d) | seed save |
| numeric player id | CHash32 of the search id | (d) |
| stamina | full: `master_player_level.stamina` of the level (134 at 87; levels without a row interpolated, see Stamina) | (a)+(b) max; (d) full |
| free coins | 300,000 (`--start-coins N`) | (d): the user's request (was 10,000); the save has no wallet. Only a new state gets it: an existing `DATA/server.sqlite3` keeps its balance; delete that file (the whole local server state) to reseed |
| paid coins | 0 | (d) |
| roster | `person_master_role_id_N` (master_role ids), duplicates dropped, only ids in `master_role` (74 from the 3.7.0 save); uid `0x7e000000+N` | seed save; uid scheme (d) |
| character level | the rarity's cap (`master_role_level_max`) minus 10 (rarity 6: 60), EXP 0 | cap (a); level (d): not in the save, chosen so progression shows |
| skills, limit break, awakening, favor, equipment | skill level 1, limit break 0, awakening 0, favor 0, nothing equipped | (d) |
| items, stack items, gear | none | (d) |
| home character | `player_home_pc_roleid` | seed save |
| party 1 | the home character, then the two highest-rarity other characters (roster order among equals): three members, the client's fourth slot being the helper's (b: "Party sets"; until schema version 20, three others); parties 2..10 empty | (d) |
| party sets | a `party_set` row per set 1..`master_global.party_set_max` (10): icon 0, unlocked (what `PartySet` sends for a set without one); the current party is set 1 | (a) the count; (d) the defaults |
| planets | not stored (the seed wrote the save's `BAS:PlanetOpen_*` flags into a `planets` table nothing read, dropped in schema version 2): the open planets are the campaign's `ActiveMissionList` | (d) |

<a id="seeding-from-a-save"></a>
### Seeding from a save (3.7.0 or 3.8.0) <!-- 380-ok: a 3.8.0 save is a supported seed -->
- **(b)** A new state is seeded from a local-KVS `Game.xml`: `soa --seed`, `soa-server --seed`, default `data/saves/seed/Game.xml`. The summary keys are the same in the 3.7.0 online save and the 3.8.0 offline save (which adds `BAS:StandAlone*` keys): `player_level`, `player_fol`, `player_name`, `person_master_role_id_N`. The test is `server/seed-from-380-save`. <!-- 380-ok: a 3.8.0 save is a supported seed -->
- **(d)** What a save doesn't hold (per-character EXP, favor, limit breaks, items) starts at the server's defaults.
- **(d)** The save's `BAS:PlayerID` is never copied: the local player is `LOCAL00001`.
- **(d)** Only a fresh state is seeded; an existing `server.sqlite3` keeps its player.

<a id="wire-layer"></a>
### soa-server: the wire layer (`server/net/`)
How `soa-server` behaves on the wire where the client doesn't say what the real server did. The
format itself is the client's (docs/online-server.md §3-4, all confirmed); these are the server's
choices. Code: `server/net/game.cpp`, `wire.cpp`.

| Rule | Source |
|---|---|
| **Device → player.** Every device UUID the bridge sees gets the state DB's one player (the seeded `LOCAL00001`, or the one `CreatePlayer` made); the `wire_device` table records uuid, player, device type, first and last seen. With no player yet (`soa-server --new-player` on a fresh state) a device has none: its Login is refused with 19001 and the client runs the new-player flow; `CreatePlayer` then binds it. How the real server bound UUIDs (and re-bound them through SQEX BRIDGE's data transfer) is unknown | (d) |
| **Session values.** nativeToken: 48 hex characters; nativeSessionId: 32 hex characters (UpdateSession sends it in a `char[32]`); sharedSecurityKey: 64 hex characters, so it is printable, longer than the 32 bytes the client's KeyStore takes, and never starts with a NUL; ResultStart's third value: empty (the client copies it into 8 bytes and never reads it) | (b) the field sizes and the key rules; (d) the values |
| **Bridge reply.** The body is the gzip stream of the JSON, without a `Content-Encoding` header (BridgeNotify::OnReceive gunzips the body itself; an HTTP layer honouring the header would hand it plain JSON) | (b) the gunzip; (d) the header |
| **Reply cipher.** Every encrypted reply uses AES-128 with random r2 and salt (the client decrypts any of the ten algorithms the envelope names) | (b) |
| **Reply counter.** The request's header counter is echoed in its reply | (d): who sets the counter and whether the client checks it is [unknown] |
| **Refusals.** A request the server refuses (`error_code` != 0) is answered with a ProtocolError (status = the error code, the request's FunctionID), which the client shows as `error_message_text_<code>`. Wire-level failures (SHA-1 mismatch, unknown FunctionID, an envelope that doesn't decrypt, an encrypted request before UpdateSession, a body that doesn't decode, an unknown session id) are ProtocolErrors with status 1002, the client's generic communication error | (b) the ProtocolError path; (d) 1002 |
| **Unimplemented APIs.** A request the server has no handler for is answered `{"data": {"Time"}, "status": 0}` (logged), so the screen continues; soa falls back to FakeApiCaller's static files instead | (d) |
| **LoginResult's FunctionID word** is the request's (Login `a01c67ef`, SimpleLogin `447fafb8`): `CApiNotify::OnLoginResult` only uses it to map a deserialize failure to an error code | (b) the use; (d) the value |
| **Login ends with a GetPlayerRes.** A LoginResult / SimpleLoginResult is followed, on the same connection and with the same counter, by a GetPlayerRes carrying the same body. `CApiNotify::OnLoginResult` (3.7.0 @014be668) applies the body but never ends the request (no EndRequest, no `ErrorHandler::Success`, no API-watchdog stop; `CApiNotify::ResetErrorCode` has no caller), while every `On<Api>Res` ends whichever request is in flight; with a LoginResult alone the 3.7.0 client (soa-emu) waited until the 60 s watchdog failed the login with 1002. The developers' `FakeApiCaller::Login` answers Login through `OnGetPlayerRes` with `FakeApi/player_get.msgp`. What the real server sent after its LoginResult is unknown (agent `e1-emu-net`; `server/net/game.cpp`) | (b) the handlers and the fake; (d) the follow-up message and its body |
| **a_ver.** soa-server's Login carries `a_ver` = `master_global.a_ver_android` (3.7.0), with the CDN keys (only when a CDN is configured, so soa's in-process responses are unchanged). After a successful reply (all but a few session fids) `CErrorHandlerWrap::CallBackCore` (3.7.0 @01586b20) looks for `BAS::GetApplicationVersion()` in the client's `a_ver` property and otherwise opens the "update the app" dialog (`OpenDialogAppVer`), which soa-emu showed right after the login. The property keeps the value for the later replies (agent `e1-emu-net`; `server/src/api/entry/entry.cpp` `add_cdn_paths`) | (a) the value; (b) the check |
| **Wire-only arguments.** Login's device UUID, push token and advertising id, and the DeviceType of NoLoginStart / CreatePlayer / MissionContinue, aren't passed to the server's handlers (the IApiCaller methods don't take them); they are in the packet log | (b) |
| **Default URLs on the client's host name** (agent `e6-end2end`). ResultStart's bridge URL defaults to `https://production-game.so-ana.com/bridge` and Login's CDN base to `http://production-game.so-ana.com` (`--bridge-url` / `--cdn-url` override them). The 3.7.0 URI parser (`Aska::Yayoi::URI::Deserialize`) keeps a URL's `:port` in the host name it resolves, so a URL with a port can't work on the client; the client must map that name to `--http` (soa-emu does) | (b) the parser; (d) the default |
| **LoginResult's root `Player`** (agent `e6-end2end`; `server/net/game.cpp` `login_result_body`). The LoginResult / SimpleLoginResult body is the library's Login answer plus a top-level `"Player": {"Id", "Level", "Name"}`. `CApiNotify::OnLoginResult` (3.7.0 @014be668) hands the body's root map to `CParameterManager::Deserialize`; its legacy `CParameterPlayer` (pParseName "Player" @017f84d4) reads `root["Player"]` into `{Id u32, Token u32, Level u32, Role s32, PersonID u32, Weapon u32, Name}` (`CParameterPlayerElement::Initialize` @017f81b8) and only then sets its deserialized byte (+0x178). `CApiNotify::LoggedIn` (@014bb174) is that byte and `Id != 0`, and every API after the login checks `LoggedIn` first (`NetworkApiCaller::GetMissionList` @015b9c90 and the rest; vtable +0x6a0). Without it soa-emu failed them locally with 1002 (`DisconnectDialog(-0x3b3)`), never sending them. The `data` map is never read by `OnLoginResult`: the GetPlayerRes that follows applies it. `Id` is also the RequestHeader's `+0` and `Token` its `+4` | (b) the reader, the check; (d) Id = the player's numeric id, Level / Name the player's, Token / Role / PersonID / Weapon not sent (defaults -1, 0, 0, 0) |
| **Reconnects continue the session** (agent `e6-end2end`; `handle_packet`). The client opens a connection per request and closes it after the reply; while logged in, its next request reconnects and is sent encrypted with the session key, with no StartBridge or UpdateSession (`CApiNotify::OnDisconnect` / `OnError`, @014bb314 / @014bb1fc, keep the bridged flag +0x4d0 while `LoggedIn`). An encrypted request on a connection without a session is decrypted with each session's key, newest first; the envelope's keyed trailer rejects every other key (`ninja` `kErrMac`), and the connection is bound to the session that decrypts it (logged "rebound to session"). Without a match it is the ProtocolError 1002 as before | (b) the reconnect (soa-emu's packet logs: GetServerTime, GetMissionList ... each on a new connection); (d) how the real server found the session (the RequestHeader that names the player is inside the ciphertext) |
| **A ProtocolError ends the connection** (agent `e6-end2end`; `on_data`). After sending a ProtocolError soa-server closes the connection. The client handles the error on its main thread and closes the socket there (`Socket::Close`: `close(fd)`, then `fd = -1`), while its network thread is in `Socket::Poll` (3.7.0 @0220dd98), which re-reads the fd after `select` returns and indexes the fd_set with it; with the connection left open the two raced, `fd = -1` made the index a top-byte-tagged address (`x21 + 0x1ffffffffffffff8`), and soa-emu crashed (2 of 3 runs, and 2 of 2 before; 0 of 3 with the close). An ARM64 phone ignores the top byte (Top Byte Ignore) and reads a stack word instead, so the race was harmless there (emulator/README.md "Error replies and the tagged-address crash"). Since agent `r2-runtime-fixes` the runtime emulates TBI and soa-emu survives the race without the close too; the close stays the default, and the hidden `--keep-open-after-error` turns it off (a test switch) | (b) the client's handling and the race; (d) that the real server closed after a ProtocolError |
| **CreatePlayer carries `a_ver`** (`server/src/api/entry/entry.cpp` `create_player`). `CreatePlayerRes` is a successful reply that `CErrorHandlerWrap::CallBackCore` checks `a_ver` on, and a new player's client has had no Login reply yet: without it soa-emu showed the "update the app" dialog right after CreatePlayer. Only `a_ver` (when a CDN is configured, as for Login): the CDN keys come with the Login the client sends next, which then starts the game data download as on a seeded login (the S3 open question: nothing else is needed after CreatePlayer) | (a) the value; (b) the check |
| **The story campaign on the wire** (agent `e6-end2end`; `LiveBackend`). soa-server calls the campaign module as soa's FakeApiCaller route does (`port/src/native/api/fakeapi.cpp`): `campaign::on_request` after every `submit`, and `campaign::on_response` on every delivered body, including the `{data: {Time}}` stand-in of an API without a handler (soa adds it to the `{}` it answers then). So `GetMissionList` gets the campaign's `ActiveMissionList`, as with the in-process server; before, soa-server's mission select listed no missions. `--campaign-seed` works as `--campaign-seed` | the campaign's own rules (section "Campaign progression", `server/src/api/campaign/campaign.cpp`) |
| **EndMissionTalk** (agent `e6-end2end`). 3.7.0's `EventScenario::CEventScenario::Exit` sends `EndMissionTalk(type, mission, flag, u32)` when a story mission's scene ends, and `CApiNotify::OnEndMissionTalkRes` applies the answer. The library has no EndMissionTalk API: `server::answer` (`server/src/core/lifecycle.cpp`) applies the request's effect (`events::end_mission_talk`, else `campaign::end_mission_talk`) and answers with GetPlayMission's body and the campaign's data, for both hosts (soa's FakeApiCaller route queues the request like the other served base-class methods since CR2, 2026-10-07; before, its hook did the same itself, and before the rebase's revision 2 `port/src/native/restore/restore_campaign.cpp` did) | (b) the request and its handler; the clears: the campaign's / events' rules |

<a id="cdn"></a>
### soa-server: the CDN (`server/src/cdn/`, `soaserver/cdn.h`)
What `soa-server` serves the 3.7.0 downloader (`CGameResourceDownloader`; the protocol is in docs/online-server.md §6). Built once at startup from `--download-dir` (`work/SOA-3.7.0-canonical-data.zip`, read in place, or a folder) and the 3.7.0 master.

| Rule | Source |
|---|---|
| **The served master is the client master edits.** `sqlite/basmaster.sqlite3` is `data/basmaster-3.7.0.sqlite3` with exactly the overrides soa applies to the client's in-memory master with the in-process server (`apply_client_master`: `service_stop_day` dropped, the dated event tables moved by the event calendar's whole years, the 3.7.0 texts, tower stand-in banners with `--restore-tower`, exchange-shop windows, the Sphere 211 season dates and ranking groups), applied once with the clock of the server's start (the server clock; the event calendar replayed on this master, or the clock itself under `--clock`). Each override keeps the label of its own rule (sections above). A server running across the day the calendar's year mapping changes keeps the start's shift until restarted | the overrides: their own labels; applying them at startup: (d) |
| **Packing.** The master is VACUUMed and ADLD-packed as encType 2: AES-128-CBC with the key of CHash32("sqlite/basmaster.sqlite3") and the DCNE v1 header; `encrypt(decrypt(x))` gives the 3.7.0 file byte for byte (test `cdn/adld-reencrypt-3.7.0`) | (b) |
| **version.bin.** The 3.7.0 file with `revision` + 1 (1471 → 1472), a new `version` id, the master's entry (`md5` = SHA-1 of the plaintext, `size` = the ADLD file's size, `time` = the start time), the 234 bundle entries' `md5` (= their Individual bundle's), and the stand-ins' entries (`parentHash` = CHash32 of the member's Individual bundle name, which is what the 3.7.0 entries hold) | (b) the fields' meanings (checked on the 3.7.0 data); (d) the time and the id |
| **Login.** `AssetPath` = `<cdn_url>/download`, `r_ver` = the served revision, `MasterPath` = `<cdn_url>/master`; `cdn_url` = `--cdn-url`, default `http://production-game.so-ana.com` (the client's host name, mapped to `--http` by the client; "Default URLs on the client's host name" above). Only soa-server sends them (soa's in-process responses are unchanged) | (b) AssetPath and r_ver (`CInfoManager::GetDownloadURL` = "%s/%s/" of the two, `GetResourceVersion` = r_ver, `SetServerAssetRevision`); (d) MasterPath (no 3.7.0 reader found) |
| **Episode data: `LatestEpisodeVersion`** (agent `episode-data`, 2026-10-02; `server/src/api/entry/entry.cpp` `add_episode_version`). Login carries `LatestEpisodeVersion` = `master_global.latest_episode_version` (3), with the CDN keys. It is the number of episode packs (`version_latest_ep1..3`, `download/EP1..3`) the client knows of: `CInfoManager::Initialize` (3.7.0 @015135b4) registers the top-level property at CInfoManager+0xb0f0, i.e. CParameterManager+0xb6f0 (the CInfoManager is CParameterManager+0x600), and that u32 is the episode count every episode-data reader uses: `CParameterUI::tEpisodeData::Initialize` / `GetEpisodeMax` (Episodeデータ管理's rows, `CDownloadEpisodeSelectDialog::Initialize`), `CParameterUtility::IsEpisodeDataStatusDownload` / `Delete`, and `CGameResourceDownloader::UpdateEpisodeDataMaxSize` (downloader+0x278, set by `CPhase_DataDownload::Initialize`), which `Progress_Setup` loops over for `version_latest_ep%d.version` / `.bin` and `LoadLocalKVSEpisodeUpdateFlag` for the packs to keep. Without it (before 2026-10-02) the count was 0: Episodeデータ管理 listed nothing and the data phase never fetched an episode pack, so Episodes 2 and 3 couldn't be played. Which packs the client then downloads is its own local KVS: `BAS:DownloadEpisodeFlag` (bit n-1 = Episode n downloaded or chosen; a fresh KVS has 0; the committed client save `data/saves/client/Game.xml` has 7, Episodes 1-3, which on a phone without the packs fetches all three, ~705 MB, at the first data phase and makes ミッション open Episode 2's map, so the port's sessions install it with 0 through `phone370_client_save` unless `SOA_EPISODE_PACKS=1`) and `BAS:DownloadEpisodeChangeStatusFlag` (the episode list's はい / Episodeデータ管理's choices, downloaded after the next TAP TO START). Sent only with the CDN keys: without a CDN there is no pack to fetch. Test `cdn/login-paths`; sessions `port/scripts/episode_movie_session.sh 2` / `3` | (a) the value; (b) the key, its readers and what 0 does; (d) sending it only with the CDN keys, and on Login only (whether the real server sent it on other replies is unknown) |
| **Bundles.** Every bundle of the manifests is rebuilt from the download's unpacked members: `\0ISF` image, header {magic, 0x20130304, count, 0}, entries {name offset, payload offset, payload length, 0}, names packed, payloads 32-aligned, the whole padded to 32. A member's payload is its stored file minus the 16-byte ADLD header when its `e` is set (the client writes `ADLD`, `e`, 8 zeros, then the payload). The manifests' bundle `md5` / `size` are those of our bundles, since the 3.7.0 bundles aren't in the download and two of their header words are unknown (the sizes of ours match theirs up to the final padding, test `cdn/bundle-layout`) | (b) the format the client reads, the SHA-1 check (`CDownloadStream::Close` → `CryptBufferSHA1`, compared in `CDownloadNode::Handler`), the member write (`UnpackNotify::Handler`); (d) the zero words and paddings |
| **Version ids.** Bulk, Individual, version.bin and `version.version` share one new id; ep1-3 get their own new ids; `.version` = `version:<id>\r\ntotalSize:<sum of the members' sizes>\r\n`, as in 3.7.0 | (b) the format; (d) the ids (any value different from 3.7.0's) |
| **Stand-ins.** `standin-assets/<rel>` files the download lacks are served as new members: one Individual bundle each (`I/5374616e/<CHash32 hex>.bin`) and one Bulk bundle (`B/5374616e/standins.bin`); a real asset of the same name wins. On by default (`--standin-assets off` drops them); they are made-up art (docs/client-changes.md, port/README.md "Stand-in assets") | (d) |
| **Paths.** `…/Android/<name>` with any prefix (the client's is `/download/<r_ver>/`), and `/master/<rev>/<name>` (the client's "download/" → "master/" swap of master nodes: its flag is never set in 3.7.0) answer the same tree; `<name>` is version.bin, `manifest/etc2/hi/…` (the only format the download has), a bundle, or a file of the download (the client never asks for single files; served for tools) | (b) the URL; (d) the rest |

<a id="english"></a>
### English mode (`--english`; `server/src/master/english_text.*`, `server/src/cdn/served_master.cpp`, `server/src/cdn/tree.cpp`)
The plan is docs/PLAN-english.md (option C, steps C2, C1, E6); the findings are docs/english.md. Off by default: without `--english` the server, its CDN and its replies are byte for byte what they were (test `cdn/lang-members`; the replay corpora).

| Rule | Source |
|---|---|
| **The English text table.** The full table is built at every start (below, [the derivation](#english-derive)): our own rows, `data/english/master-en.tsv` (machine, human and reviewed rows and the client strings, finished and checked by `tools/english_text.py`; `--english-text FILE` instead), merged with the layer derived from Global's master. Both are looked up like the other repo files (`find_repo_file`, so a release package's `data/` too). Form: a header `message_id\tja_sha1\ten\tsource`, one row per message_id; `en` is served as is (a line break is the two characters `\n`, as in the master). Without a CDN build (a replay, a test) the server's own texts use `--english-text`'s rows alone. Missing Global master or font: a warning; no `-en` files are served and the server's texts stay Japanese | (d) the files and their form (fixed by the English plan's interfaces) |
| **The matching rule.** A row's English replaces a Japanese text only when the SHA-1 of that Japanese (the served master's row; for the server's own texts, the server master's) equals the row's `ja_sha1`; otherwise the Japanese stays (a **stale** row, counted in the log line `english master: ...`). A row with an empty `ja_sha1` is a new message id: inserted into the `-en` master when the master has no row of that id. No row is ever deleted (a missing row shows its message id on screen: docs/english.md 3.4) | (d) the rule; (b) why never delete (`StringDB::GetNativeString` returns the key on a miss) |
| **`-en` members on the CDN, only with `--english`** (PLAN-english Q11). The CDN's stand-in step takes more roots: after `standin-assets`, any further member roots, then the generated root `<cdn scratch>/lang-en`; each file there the download lacks becomes a new member exactly as a stand-in does: a version.bin entry, an Individual bundle `I/5374616e/<CHash32 hex>.bin`, a member of the Bulk bundle `B/5374616e/standins.bin`, new version ids (revision + 1 as always). A name an earlier root has is not added again. A client with `CLanguage::Current` = en loads `<name>-en.<ext>` before `<name>.<ext>`; every client fetches every new member at its data check, Japanese ones too (about 36 MB for the master) | (b) `CGameResourceManager::FileExistLanguage` (ELF 0x17f8634: `name-<Current>.ext`, then `name.ext`) and the data check (docs/english.md 6.3); (d) serving them only with `--english`, the generated root |
| **The English master** `sqlite/basmaster-en.sqlite3`: a copy of the served master **after** every `ClientMaster` hook (event dates, `service_stop_day`, Sphere 211, shops, tower banners; experiment 3 of docs/english.md 6.5 showed the wrong event badge of a master without them), with the table's English in the `text_value` of the `ja_` rows it matches (id = CHash32("ja_" + message_id) unchanged), new rows for new ids (id CHash32("ja_" + message_id), `lang` ja, `data_type` package, `category_id_label` system, `category_id` CHash32("system") as the master's own rows, `serial_number` the next free one, `text_kana` NULL), VACUUMed, ADLD-AES (encType 2) keyed by its own name. Built at every start from the table (deterministic: two builds are byte-identical, so the CDN's ids stay put); the old file is removed first, so a start without the table serves none. The server's own rules keep reading the Japanese master (`kDefaultEventKeywords` matches Japanese text) | (a) Global's official English where the table's `source` is `official` (docs/basmaster-gl.md); (b) StringDB reads only `ja_` rows by id (docs/english.md 6.2) and a `-en` master needs no client change beyond `CLanguage` (6.6); (d) our rows (memory, template, machine, human) and the inserted rows' columns |
| **English UI art** (E9, PLAN-english Q4). With `--english`, `english_art::build` (`server/src/english_art/`) applies the recipes of `standin-assets-en/recipes/` to the user's own download: each recipe's scene (`UI/etc2/<name>.csf`) gets its Japanese labels covered and the English drawn in the game's own font, written as `UI/etc2/<name>-en.csf` into the generated root, so it is served as a `-en` member like the English master. Cached by recipe, source, font and generator outside the root; a recipe that fails leaves its scene Japanese (the client's per-file fallback). No game art is in git or in packages: only the recipes | (b) the client probes the scene, not the atlas (`UI/etc2/home.csf -> UI/etc2/home-en.csf`, docs/english.md 8); (d) the art is ours, the English wording from Global's `uimsg` rows where Global had the screen |
| **The server's own texts follow `--english`** (E6). The present lines it composes (`format_present` of `Present_box_1` / `_2` / `_3` / `_6`, `Present_favor_1`, and the names in them; the world boss's and Sphere 211 rental's present texts) take each template and name through `ext::display_text`: the English of the table when it matches the server master's Japanese (the rule above), else the Japanese. A line is stored when granted, so lines granted before keep their language. The gacha rate dialog's headings (`gacha_tilte_message_0001` / `0002`–`0004` / `0005`–`0007` / `0008` / `0010`, which the server composes) take the English only when its printf conversions equal the Japanese one's (the server fills them). The notice page's own words are English (`<html lang="en">`, "Notices", "Events now on", "Login bonuses", "Present box"); its event and bonus names come from the table | (a) the templates' message ids; (d) the English wording of the page, using the table for the server's texts, the printf check |
| **The gacha rate dialog's title follows `--english`.** `GachaRateInfoList.title` (the pools' gacha name, Japanese) is the English of the gacha's `master_gacha.name_message_id` row when the table translates the master's Japanese of it (`gacha_pools::display_title`, the served table: official Global names such as "Character Draw" too), else the pools' Japanese | (a) `master_gacha.name_message_id`; (d) the title is the name's English |

<a id="english-story"></a>
### English story files (`--english`; `server/src/cdn/story_en.cpp`, PLAN-english C3)

| Rule | Source |
|---|---|
| **The story tables.** Built at every start like the master's: per story file the derived official lines with our rows of `data/english/story-en/TS_xxxx.tsv` (beside an explicit `--english-text`: its directory's `story-en/`) merged on top, in the English text table's form; `en` with `\n` for a line break | (d) the files (the English plan's interface) |
| **What is generated.** For each `Scenario/TS_xxxx.msgp` the download lists with a table, `Scenario/TS_xxxx-en.msgp` in the generated root: the same rows in the same order (ids, message ids, `lang` ja, every other key and its encoding unchanged: the 3.7.0 story files decode and encode byte for byte), English in the `text_value` of each row whose Japanese matches the row's `ja_sha1` (the SHA-1 of the file's text with real newlines, or of its `\n` form), `\n` turned into a real newline; ADLD XOR (encType 1) keyed by the `-en` name. Deterministic; the old `-en` story files are removed at every start. It becomes a member as the English master does (version.bin, `I/5374616e/<CHash32>.bin`, the Bulk bundle) | (b) the story file's form and packing, `CEventScenario::ParseMessage` reads `text_value` by message id, `FileExistLanguage` takes `TS_xxxx-en.msgp` before `TS_xxxx.msgp` for a client with `CLanguage::Current` = en (docs/english.md 1.2, 6.3); (d) the rest |
| **Only complete files** (PLAN-english Q12). A file is served only when every Japanese line (kana or kanji) gets English; otherwise none, logged (`english story ...: N of M Japanese lines without English: not served`), and the client plays the Japanese file. A line whose English has a tag other than `<player>`, `<fontcolor=…>`, `<fontsize=…>`, `</font>` (spaces inside a tag ignored) counts as without English | (b) `ParseMessage` (ELF 0x142fcc8) knows those tags; an unknown one most likely null-dereferences (docs/english.md 1.2, 3.3); (d) the whole-file rule (the user's Q12) |
| **Episode packs.** The story files of Episodes 1–3 (`TS_1040`–`TS_1100`, `TS_2010`–`TS_2110`, `TS_6010`–`TS_6060`) live in the episode bundles, but their `-en` files are ordinary new members (Individual + Bulk), like every generated file: the client's data check fetches every new Individual member it lacks, whatever its language and episode flags (docs/english.md 6.3: 106 GETs on the shared phone), so an `-en` story file is on the phone before its scene; were it not, `AddDirectFile` on status 1–2 asks `CGameResourceDownloader::RequestDownload` for it | (b) the data check and `AddDirectFile` (docs/english.md 6.3); (d) not putting them in the episode bundles |

<a id="english-derive"></a>
### English mode: the derived layer (`server/src/master/english_derive.*`, `server/src/cdn/english_tables.cpp`)
The official, memory and template English is not stored: the server derives it at every start under `--english` (about 1 s), from Global's master `data/basmaster-gl.sqlite3` (logged: `english derive: Global master PATH`), the JP 3.7.0 master, the download's font (`Font/etc2/font.fpk`) and its story files, exactly as `tools/english_text.py derive` does (docs/english.md 7.9, the specification; where it and the code differ, the code is right). `soa-server --english-dump DIR` writes the resulting tables; `tests/test_english_derive.py` compares them byte for byte with `english_text.py derive`'s.

| Rule | Source |
|---|---|
| **Official by id.** Global's `en` row of the same message_id when it is English (no kana or kanji, not a copy of Global's `ja`, no Global-only token `<NUM`, `<STR`, `<INSERT`, `</INSERT`, `<EMDASH>`, `[G]`… ), has the same printf conversions as Global's `ja` in the same order, and Global's `ja` equals the JP text (for a story line: with Global's `\n` as newlines). A master row also matches when the two Japanese texts differ only in white space (tab, newline or `\n`, space, U+00A0, U+3000) and some text is left (rule id-ws: Global's `ja` often doubles a line break or drops a trailing U+3000; 57 rows, and 5 E3 rows) | (a) Global's text; (d) the five filters (docs/english.md 1.4) and id-ws (docs/english.md 7.9) |
| **E3.** A Global row whose only problem is a token: `<EMDASH>` → ―, `<INSERT n>one/many</INSERT>` → the plural form, `<NUM n>` / `<STR n>` → the JP row's n-th printf conversion when the tokens use each conversion once, in order (a reordered row stays a gap: no positional printf); a literal % of a printf row doubled | (a) Global's text; (d) the rewrite |
| **Memory.** A JP row (with kana or kanji) without official English takes the English of an identical official Japanese text (exact memory), else of one that differs from it only in white space as above (memory-ws, 83 rows), else of one that differs only in its numbers (template memory: NFKC, numbers as placeholders, each Japanese number once in the English, no month names or ordinals; "1 times" → "1 time"); among equal texts the most frequent English, then the smallest string | (d) |
| **Finishing and checks.** Folded to the font's glyphs (é → e, — → ―, curly quotes → straight, ™ dropped, NFKD for the rest, else `?`); a % of a printf row doubled; a derived master row whose Japanese has line breaks but whose English has none re-broken at spaces to max(the Japanese's widest line, 200 px); story lines stripped and re-broken to 480 px (`<player>` counted as 120 px), or, for a line over the message window's 4 lines, at 128 n − 32 px for the fewest n lines that hold it (the width the client's font scale gives n lines, E13: docs/english.md 7.13). A candidate is served only when its printf conversions equal the Japanese's (no bare %, no positional), its tags equal them (labels: a subset with balanced `<font>`; story lines: only `<player>`, `<fontcolor=…>`, `<fontsize=…>`, `</font>`, balanced), it has no kana or kanji, every glyph is in the font and no Global token is left | (b) the font's glyphs and advances (docs/english.md 3.1), the story parser's tags (3.3), the window's 4 lines and line height (CEventScenarioMessageWindow::Show, 7.13); (d) the rest |
| **Precedence.** Per message_id: our human / reviewed row (when its `ja_sha1` is the current Japanese's) > the derived candidate that passes > our machine row > the Japanese. Our rows of message_ids the JP master lacks (empty `ja_sha1`) are inserted. The same per story line | (d) (docs/english.md 7.6) |
| **Unicode.** NFKC / NFKD and the character classes (`\d` = Nd, `\s`, word characters) are utf8proc's (Unicode 16; Python's unicodedata is 15.0: equal on this data, the test checks) | (d) |

<a id="core-register"></a>
### Player-visible (c) and (d) rules (server core)

These come from the server core. Revisit them when evidence turns up.

| Rule | Label |
|---|---|
| Seed: 300,000 free coins (`--start-coins`, the user's request), character levels (cap − 10), skill level 1, nothing equipped, no items | (d) |
| `--english`: a row's English is used only for the exact Japanese it translates (`ja_sha1`); otherwise the Japanese stays, so English and Japanese mix ([English mode](#english)) | (d) |
| `--english`: the notice page's own English wording; a rate heading keeps its Japanese unless the English has the same printf conversions ([English mode](#english)) | (d) |
| Party 1 = home character + two highest-rarity characters; MissionStart uses the current party | (d) |
| Party sets never saved carry set 1's members; the last saved set becomes the current party | (d) |
| Battle stats: common curve × role % / 100, AP 100, no element defences, default weapon | (d) |
| Drop lots: `lot_drop_count` weighted picks with replacement, fixed drops always | (d) |
| Second rounding of the rank multiplier in battle stats | (d) |
| Gacha pools: 4.5's reconstruction; the fallback without the pools file is by rarity (S/A ★5+, B ★4, C ★3), characters only | (d) |
| Duplicate → +1 limit break | (c) |
| Free coins spent before paid: (a) since R16 (master_text `uimsg_buy_history_explan`, "Stocks and wallet"); was (d) | (a) |
| No surprise enemies | (d) |

From the register before R20 (with the area and how to check):

| Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|
| All | refusing a request without an error code on the FakeApiCaller route | (d) | the codes are (a); the route can't report them yet |

<a id="register"></a>
## Register of (c) and (d) rules the player can see
Every (c) / (d) value the player can see, to revisit when evidence turns up: the rows of every domain's "Player-visible (c) and (d) rules" tables, in the order of this doc. Generated by `tools/server_rules_doc.py --write` (edit the domain's table, not this one); T0's `server-docs` check fails while it is stale.

<!-- register: generated by tools/server_rules_doc.py --write from the domains' "Player-visible (c) and (d) rules" tables; do not edit -->
| Section | Area | Rule | Label | Why it's needed / how to check |
|---|---|---|---|---|
| [player](#player-register) | Player | rank-up adds the new stamina max to the current stamina | (c) | messages say "added"; amount unknown |
| [player](#player-register) | Stamina | partial regen progress kept on spend | (d) | server bookkeeping unknown |
| [player](#player-register) | Stamina | coin refill / heal items add to the current stamina (overflow allowed) | (d) | amounts are (b) |
| [player](#player-register) | Stamina | halved costs round up, minimum 1 | (d) | no evidence |
| [player](#player-register) | Wallet | free coins spent before paid: (a) since R16 (master_text `uimsg_buy_history_explan`, "Stocks and wallet"); was (c) | (a) |  |
| [player](#player-register) | Home | ChangeMascot takes any master_person id (the story-progress list is the client's); Player.mascot_id sent only once chosen | (d) | the client keeps HomeMascotID itself |
| [player](#player-register) | Deco | NumDecoObject sent with every response once a decoration is owned | (d) | the client's gate reads it (HasDecoItem) |
| [player](#player-register) | Deco | one of each decoration (a second grant adds nothing); FavoriteDecoObject skips ids not owned | (d) | the favourites name decorations by master id |
| [player](#player-register) | Deco | SetCharacterDeco stores the objects and the pose as sent; no cost limit checked | (d) | the menu shows the cost gauge itself |
| [player](#player-register) | Wallet | new player starts with 300,000 free coins (`--start-coins`), 500 item slots | (d) | the user's request (was 0); the seeded player gets the same coins and 1,000 slots: both (d) |
| [player](#player-register) | Home | Sphere 211, events and evolution open, multiplayer closed (`FooterMissionInfo`) | (d) | 12; the flags' meaning is (b) |
| [player](#player-register) | Home | follow menu: empty lists, player search finds nobody (error 10002) | (d) | 12 |
| [player](#player-register) | Home | follow / block / neighbor calls and 枠拡張 (UpdateFollowMax) are stubs: answered success, nothing stored, no coins spent, each call logged | (d) | [Stubs](#social-stubs); the user's decision (2026-10-04) |
| [player](#player-register) | Player | `is_3d_home` true until the player switches; `updated_at` the answer's time; Wallet `total_coin` = free + paid, `android_coin` = paid | (d) | "Player load"; `storage_stock` (500 before schema version 15, (d)) is (b)+(a) since: [Storage](#storage) |
| [player](#player-register) | Home | the default titles are owned; a player who never chose wears title_other_0001; SetTitle of an unowned id is refused (10208) | (d) | 12 "Titles"; the lists and keys are (b) |
| [player](#player-register) | Home | the notice board shows a local page: clock, open events, login bonus, present count | (d) | 12 "Notice board page"; the `WebView` key is (b) |
| [player](#player-register) | Character | chat stamps: the 12 type-1 stamps are owned; a player who never set the palette has them in slots 1..12 (the rest empty); SetStampSlot of an unowned stamp or too many slots is refused (10208) | (d) | [Chat stamps](#stamps); the lists, the slot layout and the grant's keys are (b), which stamps are rewards (a) |
| [entry](#entry-register) |  | New player: 300,000 free coins (`--start-coins`), level-1 starters, the name unchecked | (d) |  |
| [entry](#entry-register) |  | Seeded player: every UI tutorial seen | (d) |  |
| [entry](#entry-register) | Entry | `NoLoginStart` / `GetPlayer` without a player answer `data.Time` only; `UpdateView` stores any kind but 0 as `view_status2` | (d) | "Entry flow", "UI tutorial flags" |
| [missions](#missions-register) |  | Refusal codes 10206 (items short), 20000 (coins short), 10403 (step order, empty box) | (d) (the texts are (a)) |  |
| [missions](#missions-register) |  | Coins short is 20003 since paid currency (b: the gacha's draw answer opens the coin shop on it, [paid-currency](#paid-currency)) | (b) |  |
| [missions](#missions-register) |  | A locked mission isn't refused | (d) |  |
| [missions](#missions-register) |  | Surprise rate falls back to `master_global.surprise_rate` | (d) |  |
| [missions](#missions-register) |  | Stamina campaign rounding up, minimum 1 | (d) |  |
| [missions](#missions-register) |  | One campaign-drop lot per type-0 campaign; type-8 campaigns: see "Type-8 campaigns" (agent server-rules) | (d) |  |
| [missions](#missions-register) |  | Character bonus capped per party | (d) |  |
| [missions](#missions-register) |  | Evaluation by the battle's evaluation array, else the log field (types 2 and 5 have none); best rank only | (d) |  |
| [missions](#missions-register) |  | Equipment at base stats; favor AP on top of 100 | (d) |  |
| [missions](#missions-register) |  | Step-up: other steps refused; box: resettable any time | (d) |  |
| [missions](#missions-register) |  | Chips per duplicate = chip × chip_rate / 100 | (d) |  |
| [missions](#missions-register) |  | Common drops without a badge (server-core sent the beginner badge) | (d) |  |
| [missions](#missions-register) |  | An own-character helper joins the battle list; an event mission's picked NPC joins as member 4, other NPC ids are only recorded; a rental helper replaces member 4 (see "Rental helpers" below); a restart doesn't restore the helper | (d) |  |
| [missions](#missions-register) |  | MissionContinue: the play stays open across a continue (same mission, party, stamina, surprise roll); refused with 10403 for nothing in progress or a mission without `is_continue`, 20000 coins short; the first matching continue campaign in master order counts (agent server-u-missions) | (d) |  |
| [missions](#missions-register) |  | MissionLose (no 3.7.0 caller) ends the play like MissionFailed | (d) |  |
| [missions](#missions-register) |  | The battle simulator (TrainingMissionStart) fights with the current party, keeps no play record or play count and grants nothing | (d) |  |
| [missions](#missions-register) | Missions | drops rolled at MissionStart and repeated at MissionEnd | (d) | the start response carries drop lists; no reader found |
| [missions](#missions-register) | Missions | first-clear presents only on the first clear | (d) | table has no repeat flag |
| [missions](#missions-register) | Missions | `is_fix_drop` rows always drop; `host_bonus` rows skipped | (d) |  |
| [missions](#missions-register) | Missions | rare-drop marking for display | (d) |  |
| [missions](#missions-register) | Missions | character bonus cap per party | (d) |  |
| [missions](#missions-register) | Missions | vanish item consumed at start | (d) |  |
| [missions](#missions-register) | Evaluation | best rank only, checked best-first | (d) |  |
| [events](#events-register) |  | Past events replay on the service calendar, moved into today's year | (d) |  |
| [events](#events-register) |  | Daily material missions follow today's real weekday | (d) |  |
| [events](#events-register) |  | Missions without their files are not offered; they don't block what they unlock | (d) |  |
| [events](#events-register) |  | The event list is sent a day ahead | (d) |  |
| [events](#events-register) |  | New = not cleared | (d) |  |
| [events](#events-register) |  | Event stories clear at the end of the scene | (d) |  |
| [events](#events-register) |  | Event NPCs are 4th-member helpers | (b) + (d) |  |
| [events](#events-register) |  | No event maintenance, no big hunt by default | (d) |  |
| [events](#events-register) | Clock | without `--clock`, dated content uses today's month-day in the newest service year with an event term that day (`event_now`) | (d) | the user's choice (replay the calendar); `--clock` overrides |
| [events](#events-register) | Modes | event ranking: player is rank 1 | (d) |  |
| [gacha](#gacha-register) | Gacha | rank S/A = ★5 (S pick-up, else ace), B ★4, C ★3; weapons A ★5, S pick-up | (a)+(d) | ticket rates and titles fit; the S/A split without pick-ups is inferred (4.5) |
| [gacha](#gacha-register) | Gacha | the pools (server tables `master_gacha_item_*` are missing): reconstructed per gacha | (a)–(d) per rule | 4.5: pick-ups from images / titles / themes, general pools by release date, equal weights within a rank (d) |
| [gacha](#gacha-register) | Gacha | duplicate over the max → `master_role_duplication_item`; chip amount | (c)/(d) | the matching and limit-break steps are (b) |
| [gacha](#gacha-register) | Gacha | box draw without replacement; last box resettable any time | (c)/(d) |  |
| [gacha](#gacha-register) | Gacha | gift gacha always granted; `is_mutation` 0 | (d) |  |
| [growth](#growth-register) |  | NEW badges ([NEW badges](#new-badges)): what is gained from now on is new until viewed; the seed's and an older state's characters and items are not; a stack item is new only when its first stack arrives | (d) |  |
| [growth](#growth-register) |  | Big success: `*_up_rate` is a percent chance, × `*_bonus_rate` | (d) |  |
| [growth](#growth-register) |  | FOL campaigns (types 2, 4, 5) and big-success campaigns (6, 7) not applied | (d) |  |
| [growth](#growth-register) |  | Seed FOL per seed | (d) |  |
| [growth](#growth-register) |  | Limit break keeps the level cap | (d) |  |
| [growth](#growth-register) |  | Awakening one level at a time | (d) |  |
| [growth](#growth-register) |  | Compose: locked / equipped materials refused (the points per level and each material's gain are (b) since 2026-10-06: [Compose points](#compose-points)) | (d) |  |
| [growth](#growth-register) |  | Grade-up: the base becomes the new weapon at level 1 | (d) |  |
| [growth](#growth-register) |  | An equipped item moves from its previous owner | (d) |  |
| [growth](#growth-register) |  | Auto-equip (EquipAuto): the strongest weapon of the role's kind and accessory by summed base stats, no item taken from another character, the empty skill slots filled with open skills, the assist unchanged; the master_config defaults stand for the player's settings (agent server-u-missions) | (d) |  |
| [growth](#growth-register) |  | Accessory inheritance (InheritAccessory): a locked or equipped material refused as for compose; the material's limit break kept with the inheritance (agent server-u-missions) | (d) |  |
| [growth](#growth-register) |  | UpdateItemStock is refused with 11006: the stock starts at item_stock_max | (d) |  |
| [growth](#growth-register) |  | Heals add to the current stamina (overflow kept) | (d) |  |
| [growth](#growth-register) |  | Shop / exchange / login / achievement grants: shop and exchange straight to the inventory; login bonus and achievements to the present box | (c)/(d) |  |
| [growth](#growth-register) |  | Item-shop `limit_count` 0 = unlimited; non-monthly rows never reset; `reset_at` = the next reset; `num_total` = all-time purchases | (d) |  |
| [growth](#growth-register) |  | Exchange count keys: contents id | (d) |  |
| [growth](#growth-register) |  | Login-bonus day at 04:00 local time; `is_received_now` only in the granting response; present `reason_type` 1 / achievement 3 | (d) |  |
| [growth](#growth-register) |  | `Player.tutorial_status` 9 for the seeded account | (d) |  |
| [growth](#growth-register) |  | Achievement status values; untracked types report 0; received rows leave the list | (d) |  |
| [growth](#growth-register) |  | Mastery: a dojo with a pair still training refuses another pair | (d) |  |
| [growth](#growth-register) |  | Mastery: the pass medal stores the card it was used on | (d) |  |
| [growth](#growth-register) |  | Mastery: an awakening's talent in the mastery slot replaces the role's; the inheritance follows the master's later growth | (d) |  |
| [growth](#growth-register) |  | Mastery: parting returns nothing paid | (d) |  |
| [growth](#growth-register) |  | ChangeRole resets the character's skills in the party sets too; level, skills' levels, equipment kept | (d) |  |
| [growth](#growth-register) | Growth | big-success chance 11.5 %, ×1.5 | (d) | key names only |
| [growth](#growth-register) | Growth | seed FOL per seed used | (d) | amounts are (a)/(b) |
| [growth](#growth-register) | Growth | limit break leaves the level cap | (d) |  |
| [storage](#storage-register) | Storage | a locked stored item can't be sold (10204) | (d) | as in the inventory; the client's sale list wasn't read |
| [storage](#storage-register) | Overflow box | a present / drop / shop / exchange / gacha weapon on a full inventory goes to the box; the gacha's result entry has no item id (`player_item_id` 0); the present receipt dialog doesn't mention the box | (d) | the answer's shape; the client's messages for the box (`uimsg_gacha_wapon_itemmax` ...) aren't shown yet: which key they read wasn't found |
| [storage](#storage-register) | Overflow box | withdrawn items are new level-1 items; refusals 10206 (count) / 10202 (slots) | (d) | the box keeps no item's state |
| [favor](#favor-register) |  | Favor: seed 0 points; points stop at the max level's threshold; the tap day starts at 04:00 local; the load's tap count is the home character's; favor item `target_type` reading | (d) (agent restore-favor, section 8) |  |
| [daily](#daily-register) | Login | `LoginBonus` sent in the first home response of the day, `is_received_now` only then | (d) | the popup condition is (b) |
| [daily](#daily-register) | Login | rewards go to the present box; day index counts login days | (c) |  |
| [daily](#daily-register) | Login | a bonus day granted by `NoLoginStart` is received-now again on the next `Login` | (d) | 12; lets the 3.7.0 login's popup show it |
| [presents](#presents-register) | Presents | expired presents dropped after 30 days | (d) |  |
| [presents](#presents-register) | Achievements | a state seeded from a save has the starter missions (help_addr rows) done; they aren't listed | (d) | section 10; else the "Next Mission" popup covers home |
| [shop](#shop-register) | Shops | item shop `reset_type` 2 = monthly, `interval_day` = every N days | (a) inferred / (d) |  |
| [shop](#shop-register) | Shops | the coin shop sells the 2019-10-01 regular 紋章石 sets 001..007 of `master_text` for nothing; paid stones to the paid coins, the おまけ to the free coins; the price shown = the paid count | (a)+(d) | [paid-currency](#paid-currency); session `coins` |
| [shop](#shop-register) | Shops | no receipt validation; a completed purchase isn't credited twice | (d) | `shop/coins` |
| [shop](#shop-register) | Shops | the premium shop (DirectItemShopList) lists nothing | (d) | no store product or price in `master_direct_item_shop` |
| [deepspace](#deepspace-register) |  | Area image present on disk | (d) |  |
| [deepspace](#deepspace-register) |  | All normal missions always offered; bonus set re-rolled after each expedition | (d) |  |
| [deepspace](#deepspace-register) |  | Ship numbering (pass ships after the limit-break ones); no coin ships (b) | (d) |  |
| [deepspace](#deepspace-register) |  | Pass `num` read as days; `--galaxy-pass` renews the Galaxy Pass | (d) |  |
| [deepspace](#deepspace-register) |  | Play limits: type 1 day / 2 week, departures counted, periods from 04:00 / Monday 04:00, a mission at its limit hidden (no 3.7.0 row has limits) | (d) |  |
| [deepspace](#deepspace-register) |  | Achievements: a departure is an expedition; campaign rows count only their window; exploration rate rounded down | (d) |  |
| [deepspace](#deepspace-register) |  | Auto member select order | (d) |  |
| [deepspace](#deepspace-register) |  | Battle power approximation | (d) |  |
| [deepspace](#deepspace-register) |  | Bonus effects 1–4 (rates, extra lots) | (c)/(d) |  |
| [deepspace](#deepspace-register) |  | Rare-table and rare-mission lot semantics; result marks | (d) |  |
| [deepspace](#deepspace-register) |  | Quick returns counted per day from 04:00 | (d) |  |
| [deepspace](#deepspace-register) |  | Quick returns: free coins first (master_text `uimsg_buy_history_explan`, "Stocks and wallet"); was (d) | (a) |  |
| [deepspace](#deepspace-register) |  | Refusal codes 10208 / 10206 | (d) |  |
| [sphere211](#sphere211-register) |  | The last season repeats after the service's end (dates moved) | (d) |  |
| [sphere211](#sphere211-register) |  | Missions with missing maps are never lotted | (d) |  |
| [sphere211](#sphere211-register) |  | The dive starts on floor 1; 帰還 keeps the floor | (d) |  |
| [sphere211](#sphere211-register) |  | Start cell and neighbours of cleared cells are playable | (c)/(d) |  |
| [sphere211](#sphere211-register) |  | Which cells count as boss / rare for the extra boxes; the battle's own boxes carry no badge | (d) |  |
| [sphere211](#sphere211-register) |  | Ranks lotted at 帰還; boxes granted directly | (d) |  |
| [sphere211](#sphere211-register) |  | Continue costs 100 coins (times a continue campaign); a declined continue ends the battle as failed; retire keeps the stamina spent | (a)/(d) |  |
| [sphere211](#sphere211-register) |  | The rental slot lends clones of the player's own characters, once per lender and 3 per floor | (d) |  |
| [sphere211](#sphere211-register) |  | The Sphere 211 rental bonus counts the player's own rentals | (d) |  |
| [sphere211](#sphere211-register) |  | A season's ranking rank is 1 when a battle was won in it; the repeated last season pays season 12's rewards | (d) |  |
| [sphere211](#sphere211-register) |  | Days before the first season play the season of the same date a year later | (d) |  |
| [sphere211](#sphere211-register) |  | Sphere 211 achievements run on the season's moved dates | (d) |  |
| [sphere211](#sphere211-register) |  | An EX character departs at the start (its companions never); one use per EX sortie; with the 3 uses spent an EX sortie is a plain one (everyone departs, nothing counted), not refused | (d) |  |
| [sphere211](#sphere211-register) |  | Auto party order | (d) |  |
| [sphere211](#sphere211-register) |  | Local ranking rank 1 | (d) |  |
| [sphere211](#sphere211-register) |  | Refusal codes 10004 / 10206 / 10208 / 20000 | (d) |  |
| [sphere211](#sphere211-register) | Sphere 211 | past the last season (13, closed 2021-06-24) the last season repeats, its dates moved by whole season lengths (also in the client's master) | (d) | "Sphere 211"; without it the mode is "outside the season" for good |
| [sphere211](#sphere211-register) | Sphere 211 | a missing battle map skips the mission (cell battles are lotted among playable missions only; nothing playable: the unfiltered lot) | (d) | "Sphere 211"; decided from the files at run time |
| [sphere211](#sphere211-register) | Sphere 211 | a dive starts on floor 1; 帰還 keeps the floor; a new season starts a new dive | (d) | "Sphere 211" |
| [sphere211](#sphere211-register) | Sphere 211 | an EX-character sortie with no use left (3 spent) is accepted as a plain sortie: everyone departs, no use counted | (d) | a rule we couldn't reverse engineer: the client doesn't stop it (its dialog says 残り 0 回) and the online server's answer is unknown; a refusal would send the player to the title (error handling type 2); the user's choice 2026-10-03. "Sphere 211", test `sphere211/ex-sorties` |
| [sphere211](#sphere211-register) | Sphere 211 | the start cell and the uncleared neighbours of cleared cells are playable (`can_play`) | (c)+(d) | "Sphere 211" |
| [sphere211](#sphere211-register) | Sphere 211 | treasure: the battle's boxes + boss extra (lottery type 2) + rare extra (4 / 6) + streak bonus; ranks lotted at 帰還 with the current floor's weights | (a)+(d) | "Sphere 211"; the counts are (a), which cells count as boss / rare is (d) |
| [sphere211](#sphere211-register) | Sphere 211 | continue after a defeat costs 100 coins (continue_use_coin, times a continue campaign); declining it ends the battle as failed, as retire; retire resets the streak, the stamina stays spent | (a)+(d) | "Sphere 211" |
| [sphere211](#sphere211-register) | Sphere 211 | the rental slot lends clones of the player's own characters (once per lender, 3 per floor); their rentals count for the Sphere 211 rental bonus | (d) | "Sphere 211" |
| [sphere211](#sphere211-register) | Sphere 211 | season end: rank 1 of a one-player ranking when a battle was won, with that rank's reward; the end result shown once | (d) | "Sphere 211" |
| [sphere211](#sphere211-register) | Sphere 211 | auto party: the 4 strongest characters that haven't sortied (level, rarity, limit break) | (d) | "Sphere 211" |
| [sphere211](#sphere211-register) | Sphere 211 | local ranking: the player is rank 1; season end result rank 1 | (d) | "Sphere 211" |
| [settings-account](#settings-register) |  | The birth month isn't used for a spending limit; it is stored as entered and can be entered again | (d) |  |
| [settings-account](#settings-register) |  | No guide popups (お知らせ guides) are shown; following one stores nothing | (d) |  |
| [settings-account](#settings-register) |  | 期限情報's read marks aren't stored (the server keeps no expiration state) | (d) |  |
| [settings-account](#settings-register) |  | シナリオライブラリ lists the story of cleared missions | (c) |  |
| [core](#core-register) |  | Seed: 300,000 free coins (`--start-coins`, the user's request), character levels (cap − 10), skill level 1, nothing equipped, no items | (d) |  |
| [core](#core-register) |  | `--english`: a row's English is used only for the exact Japanese it translates (`ja_sha1`); otherwise the Japanese stays, so English and Japanese mix ([English mode](#english)) | (d) |  |
| [core](#core-register) |  | `--english`: the notice page's own English wording; a rate heading keeps its Japanese unless the English has the same printf conversions ([English mode](#english)) | (d) |  |
| [core](#core-register) |  | Party 1 = home character + two highest-rarity characters; MissionStart uses the current party | (d) |  |
| [core](#core-register) |  | Party sets never saved carry set 1's members; the last saved set becomes the current party | (d) |  |
| [core](#core-register) |  | Battle stats: common curve × role % / 100, AP 100, no element defences, default weapon | (d) |  |
| [core](#core-register) |  | Drop lots: `lot_drop_count` weighted picks with replacement, fixed drops always | (d) |  |
| [core](#core-register) |  | Second rounding of the rank multiplier in battle stats | (d) |  |
| [core](#core-register) |  | Gacha pools: 4.5's reconstruction; the fallback without the pools file is by rarity (S/A ★5+, B ★4, C ★3), characters only | (d) |  |
| [core](#core-register) |  | Duplicate → +1 limit break | (c) |  |
| [core](#core-register) |  | Free coins spent before paid: (a) since R16 (master_text `uimsg_buy_history_explan`, "Stocks and wallet"); was (d) | (a) |  |
| [core](#core-register) |  | No surprise enemies | (d) |  |
| [core](#core-register) | All | refusing a request without an error code on the FakeApiCaller route | (d) | the codes are (a); the route can't report them yet |
<!-- /register -->
