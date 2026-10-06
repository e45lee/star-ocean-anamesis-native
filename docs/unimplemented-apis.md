# Unimplemented server APIs (current limitations)

What the local server (`server/`, used by `soa`, `soa-server` and `soa-emu`) does **not** implement
yet, what the game does when it calls one of those methods today, and the plan for implementing the
ones play needs (part 3). Snapshot of 2026-10-04.

Regenerate the lists with:

```
.venv/bin/python tools/unhandled_apis.py --summary   # counts
.venv/bin/python tools/unhandled_apis.py             # method, FunctionID, in-process behaviour
```

Each method's request and reply format is in [`api.md`](api.md) (its `### Method` section); the rules
the server applies to the implemented ones are in [`server-rules.md`](server-rules.md).

## 1. Summary

The wire knows **199 methods**; the server has handlers for **180** (35 of them stubs: section 2.5). Of the **19 without a handler**:

| Kind | Count | What happens in-process (`soa`, the default) |
|---|---|---|
| **Empty reply** | 1 | The client's request names a reply file (`FakeApi/<file>.msgp`); the in-process route looks it up in its fallback folder `port/fakeapi/responses/`, which doesn't have it, and answers an empty map `{}` (logged as "missing; answering {}"). Nothing is stored. |
| **Canned reply** | 0 | None left: `TrainingMissionStart` (it got `mission_start.msgp`) and `CbtCertification` (`update_home.msgp`) are answered now; the files of `port/fakeapi/responses/` are reached by nothing (step 9 retires them). |
| **No reply** | 8 | The offline build only stores a status and never sends a reply. Nothing reaches the server and nothing is stored; the screen carries on as if the call had succeeded, with no data (step 1 below: none of the screens checked hangs). |
| **Not callable** | 10 | Not in the 3.7.0 client's API table (removed features). Only a modified client or a test can send them. |

Over the network (`soa-server`, `soa-emu`, `soa --server HOST`), every unhandled method gets an
**empty success reply** (only `data.Time`), whatever its kind: the client carries on with empty data
(an empty list, an unchanged screen) and nothing is stored.

**Checked (part 3 step 1, 2026-10-04): no screen hangs; they show empty or wrong data, and every
change is lost.** Why nothing hangs: the screens send these calls through
`CErrorHandlerWrap::Auto(fid, callback)`, whose `Progress` (@01584900) calls the callback as soon as
`IsRequesting(fid)` is false, with `IsSuccess(fid)`. A status-only method queues nothing, so the
callback runs on the next frame with success (FakeApiCaller's `IsSuccess` is the constant 1) and no
reply data; over the wire the client gets `{data: {Time}}` and does the same. The one exception was
`Home3DAnd2DSwitching`, whose screen (`CHome::Progress`) waits for its own flag set by the reply
(fixed: schema v12, `docs/home3d.md`). Sessions: in-process (I) and `soa --server` (S), the seeded
player, screens opened by hand through `--control`.

| Screen (method) | Seen | What happens |
|---|---|---|
| アイテム > 装備倉庫にしまう / 取り出す / 売却 (`GetStorageInfo`) | I, S | opens; the storage is empty (倉庫装備所持 0/500). **Done** (step 3.1, schema v15): see 3.1 below |
| アイテム > 一時保管庫から取り出す (`GetOneTimeStorageInfo`) | I | opens; empty. **Done** (step 3.1) |
| `DepositItem`, `WithdrawItemFromStorage`, `SellItemsFromStorage`, `Lock`/`UnlockStorageItem` | decompile | the screen takes the call as done; nothing moves on the server, so the item is back after a reload (the seeded player has no loose weapons to move; the storage session plants some) |
| 設定 > その他設定 / バトル設定 (`GetConfig`, `UpdateConfig`) | I, S | opens with the master defaults; a toggled option (一時保管庫設定) is **lost at once**: reopened, it is off again (S: `UpdateConfig(4025152546, "true", 4)` answered with `Time` only). **Fixed (step 3.3):** kept, also over a restart; 初期設定に戻す resets |
| 初期設定に戻す (`ResetConfig`) | decompile | same pattern |
| キャラクター > マスタリー (`GetMasteryInfo`, `{}` in-process) | I | opens; all three 道場 EMPTY; the master selection lists characters. **Done (step 3.4):** the pairs, trainings, 皆伝 and parting are the server's (`server/src/api/growth/mastery.cpp`, below) |
| 惑星選択 > シナリオライブラリ (`GetScenarioLibraryInfoList`) | S | opens; メインストーリー / サブストーリー with no chapters. **Fixed (step 3.3):** the cleared missions' chapters |
| キャラクター > バトルシミュレーター (`TrainingMissionStart`, canned `mission_start.msgp`) | I | **Fixed (step 3.2).** Was **wrong data**: the battle starts with the canned reply's party and stages (other characters, STAGE 1/2), not the chosen party; シミュレーター終了 returns to the character menu (no `MissionLose`) |
| 会話モード > キャラデコ (`GetDecoInfo`) | I | "デコを所持していません" (no request: the client's deco list is empty for the seeded player). **Done (step 3.5):** the gate is `NumDecoObject`; the owned decorations, favourites and each character's setting are the server's (`server/src/api/player/deco.cpp`) |
| `MissionContinue`, `MissionLose` (`CPauseMenu::ReqeustContinue` @01dad704 -> `Auto`) | decompile | not reproduced (losing needs a long battle); the continue would go ahead with no stones taken on the server. **Done** (step 3.2): the continue's coins and campaigns; `MissionLose` has no 3.7.0 caller ([server-rules 2.6](server-rules.md#failure-continue-restart)) |
| Paid currency (`CoinList`, `CoinDeposit*`, `Get`/`UpdateBirthYearMonth`) | I, S | no entry point found on the shop or gacha screens with 300000 stones (step 7 finds the opener) |
| `InheritAccessory`, `EquipAuto`, `UpdateItemStock`, the `ClearNew*`, `ReadExpirationInfo`, `SendGuideInformation`, `SetStampSlot` | callers (`CItemStrengtheningPotal`, `CTermInfoUI`, `CGuideInformation`, `CStampSelect`) | the same `Auto` pattern: no hang, the change isn't stored (`ChangeMascot` and `ChangeRole`, from `CAdjutantSelect` / `CRoleSelect`, were the same: done in step 3.5) |

Priority (play impact): storage and the overflow box (empty screens, lost moves), missions (the
simulator's wrong battle, continues), settings (lost at once; one of them routes items to the
overflow box), equipment and mastery, home and decorations, badges, paid currency, the stubs.
In-process, the status-only methods logged nothing at all; they now log `no handler: <Method>`
(below, "Stub logging").

### Where the fallback replies come from: `port/fakeapi/`

Not from the game. The 3.7.0 offline build's request lambdas each name a reply file
(`FakeApi/<name>.msgp`), but the APK ships none; the port's in-process route serves them from
`port/fakeapi/responses/` (`--fake-server DIR`, `port/src/native/api/fakeapi.cpp`) **only when the
local server has no handler**. That folder holds 10 replies generated early in the port by
`tools/fakeapi_responses.py` (player_get, mission_start/end, present_get_all/item, update_home and four
gacha ones, each with a readable `json/` copy). Every one of those methods has a real handler now,
so the files are reached only by the "canned" method above. `port/fakeapi/fields.txt` and
`schema.txt` are reverse-engineering references (the reply fields each client info class reads;
the reply schema by CHash32 key) that server code cites as evidence; they are not served. Part 3
replaces the fallback with explicit stubs, after which `responses/` can go.

## 2. The methods

★ = no reply in-process (may hang the screen that calls it). "{}" = an empty map in-process;
"canned" = the named fallback file from `port/fakeapi/responses/`.

### 2.1 Likely to affect normal play

| Feature | Method | In-process | Notes |
|---|---|---|---|
| **Settings and account** | [SetStampSlot](api.md#setstampslot) | {} | chat stamp slots (the options, the birth month, the read marks and the scenario library: done, step 3.3) |

### 2.2 Online-only features

Not needed for single-player play. The social calls are stubs now (2.5).

| Feature | Methods | In-process |
|---|---|---|
| **Paid currency and shop** | [CoinList](api.md#coinlist), [CoinDepositCreate](api.md#coindepositcreate), [CoinDepositAndroidUpdate](api.md#coindepositandroidupdate), [CoinDepositIOSUpdate](api.md#coindepositiosupdate), [CoinDepositAmazonUpdate](api.md#coindepositamazonupdate), [DirectItemShopList](api.md#directitemshoplist) | ★ |

### 2.3 Answered another way

- [GetWorldMapInfoList](api.md#getworldmapinfolist) (★ in the offline build) and
  [EndMissionTalk](api.md#endmissiontalk) have no handler, but are answered with the story
  campaign's data (`server/src/core/lifecycle.cpp`, `server/src/api/campaign/`), and in-process by
  the port's own hooks (`port/src/native/api/fakeapi.cpp`). They work.
- [UpdateSession](api.md#updatesession) has no library handler: it is the session handshake's last
  step, which soa-server's wire layer answers itself (`server/net/game.cpp`, before the library
  sees a request); in-process its only caller (`BridgeNotify::OnReceive`) never runs, since the
  FakeApiCaller opens no bridge. Nothing to implement (step 3.3).

### 2.4 Not callable by the 3.7.0 client (10 without a handler)

- **"Universe" features:** `AcquireUniverse`, `ExchangingUniverseCurrency`,
  `GetUniverseBoardIdList`, `UniverseReset`.
- **Others:** `EquipAutoParty`, `GetSubscriptionHistory`, `SetDeity`, `StartBridge`,
  `UpdateRelationship`, and `EndMissionTalk` (answered, 2.3).
- The 27 debug APIs are stubs now (2.5).

### 2.5 Stubs (step 8, done 2026-10-04)

Answered success with `{Time}`, nothing stored, every call logged `stub: <Method> ...`
(`ext::add_stub`; [`server-rules.md#social-stubs`](server-rules.md#social-stubs)):

- **Social (8):** [FollowAdd](api.md#followadd), [FollowRemove](api.md#followremove),
  [UpdateFollowMax](api.md#updatefollowmax), [BlacklistAdd](api.md#blacklistadd),
  [BlacklistRemove](api.md#blacklistremove), [NeighborList](api.md#neighborlist),
  [NeighborRegist](api.md#neighborregist), [LocationRegist](api.md#locationregist)
  (`server/src/api/social/social.cpp`; replaced by the multiplayer server's MC7,
  `server/PLAN-multiplayer-code.md`).
- **Debug (27):** `DebugBarneyChance`, `DebugCharacterBoost`, `DebugCreatePlayer`,
  `DebugDeepBonus`, `DebugDeepBonusRareMission`, `DebugDeepMissionDrop`, `DebugDeletePlayer`,
  `DebugFavorLoginBonus`, `DebugGacha`, `DebugGachaMutation`, `DebugGear`, `DebugGearDrop`,
  `DebugGetCharacter`, `DebugGetCoin`, `DebugGetFol`, `DebugGetItem`, `DebugGradeUpCharacter`,
  `DebugItemBoost`, `DebugLotDeity`, `DebugMissionDrop`, `DebugOpenMission`,
  `DebugSphere211LotAsset`, `DebugSphere211LotEnemyLevel`, `DebugSphere211LotFloorNum`,
  `DebugSphere211LotMission`, `DebugSphere211TreasureBox`, `DebugTowerMax`
  (`server/src/api/debug/debug_stubs.cpp`; not callable by the 3.7.0 client).

Server-runnable screens (the rebuild queue's rule, `port/REBUILD-QUEUE.md`: code the local server
can't run isn't ported): the follow menu's add / remove / block buttons and the follow-slot
extension now get an answer from the local server in both hosts (the lists stay empty).

## 3. Plan: implementing them (queued: task U in `port/PLAN.md`)

Server-first ([`server-rules.md`](server-rules.md)): every behaviour goes into the local server, with
its rule labelled by evidence; a client change only where the server can't do it, logged in
[`client-changes.md`](client-changes.md). One feature group per step, each landing on its own.

### Step 1: find what actually breaks (done 2026-10-04: section 1, "Checked")

For each method in 2.1: open the screen that calls it in a session
(`control/run.py`, in-process and with `--server HOST`), and record whether it **hangs**, shows
**empty or wrong data**, or **loses the change** on the next login. Use the decompile to find the call
sites and whether each waits for the reply (`CApiNotify::On<Method>Res`, the screen's `Progress`
state). Result: a table in this document replacing "not checked yet", and a priority order.

### Step 2: the reply shapes and the rules

For each method of a group: its request fields and reply fields from `api.md` (the wire format is
already recovered for all 199), the client code that reads the reply (`OnXRes` → the parameter
classes it fills), and the rule: what is stored, what is checked (costs, limits, ownership),
which errors exist (`master_error` / the client's error handling). Label each rule
(a) seen in a capture, (b) read from the client, (c) assumed — as `server-rules.md` does. Where the
master DB holds the numbers (storage size, mastery costs, continue prices), read them from it.

### Step 3: implement, one group at a time

A module per group under `server/src/api/<area>/`, following `server/README.md` (handler, state
tables, rules section). New state goes through the state module's migrations
(`user_version` +1 per group, the planted-old-version migration test, fresh == migrated,
`tools/schema_inventory.py`). Suggested order, play impact first:

1. **Storage and one-time storage** (10 methods; **done**, schema version 15: `items.stored_at`, `one_time_storage`; `server/src/api/storage/`, [`server-rules.md#storage`](server-rules.md#storage); the assumptions below): an `inventory_storage` table (items, stack counts,
   locks, "new" flags); deposit/withdraw/sell/lock rules; the overflow box filled where the server
   already gives items (presents, drops, gacha) when the inventory is full — check how the client
   decides "full" and match it.
2. **Missions: `MissionContinue`, `MissionLose`, `TrainingMissionStart`:** continue costs and limits
   from the master, the mission's state kept open across a continue; training missions give no
   rewards (check). **Done** (step 3.2: schema version 16 for the inheritance; the assumptions below).
3. **Settings and account (done, 2026-10-04: `server/src/api/settings/`, schema version 14,
   docs/server-rules.md#settings-account, session `settings`):** `GetConfig`/`UpdateConfig`/`ResetConfig`
   (store the options; `ConfigInfoList` also on every player load), `Get/UpdateBirthYearMonth`,
   `ReadExpirationInfo`, `SendGuideInformation`, `GetScenarioLibraryInfoList` (from the story progress
   the server already keeps); `UpdateSession` needs none (2.3). Assumptions below.
4. **Equipment and mastery:** `EquipAuto` (the client's or the server's choice — check which side
   picks), `InheritAccessory`, `UpdateItemStock`, `GetMasteryInfo`/`TrainMastery`/`ResetMastery`.
   The equipment part is **done** (agent server-u-missions: the server picks; the assumptions below).
5. **Home and decorations:** `ChangeMascot`, `ChangeRole`, the deco methods
   (`Home3DAnd2DSwitching` is already being done).
6. **"New" badges (done 2026-10-04):** the three `ClearNew*` (flags on the stored characters and items).
   Found: the server never sent `is_new`, so no badge ever showed (not "never cleared"). Now
   `roster` / `items` / `stock` keep `is_new` (schema step 13), what is gained later is new until
   viewed, and the three methods clear it ([`server-rules.md#new-badges`](server-rules.md#new-badges)).
   Assumptions (d): what the seed and an older state hold is not new; a stack item is new only when
   its first stack arrives. Server-runnable screens: the character, item, weapon / accessory and
   stack lists' NEW badges (both hosts; in-process these were already answered, with `{}`).
7. **Paid currency (decided: allow):** `CoinList`, `DirectItemShopList` and the `CoinDeposit*`
   purchase flow complete without payment and credit what the product gives (see Decisions).
8. **Stubs (decided; done 2026-10-04, section 2.5):** social (2.2) and the debug APIs (2.4) answer
   success through explicit stub handlers, each logged when called (see Decisions).
9. **Retire the canned responses** (the user asked, 2026-10-04; they are no longer needed): once
   steps 3–8 give every callable method a handler or stub, nothing reaches the file fallback. Remove
   `port/fakeapi/responses/` (10 files + `json/`), `tools/fakeapi_responses.py`,
   `tools/fakeapi_msgp.py`, the `--fake-server DIR` option and the file lookup in
   `port/src/native/api/fakeapi.cpp` (a method with no handler then answers `{}` and logs
   `no handler`). **Keep:** the FakeApiCaller route itself (`--server inproc` turns it on; it is how
   the in-process server is wired), `--fake-server-schema FILE` (an RE dump), and
   `port/fakeapi/fields.txt` / `schema.txt` (evidence the server code cites). Move the historical
   notes (`docs/notes.md` "the fake server, live", "Generated responses") to `docs/history/`, keep
   `SOA_FAKE_SERVER` in the removed-variables table pointing at the removal, and update
   `port/README.md`, `server/ARCHITECTURE.md` and `docs/client-changes.md`.

### Proof per group

- A unit test per handler and per rule (`server/src/api/<area>/*_tests.cpp`).
- A replay corpus line per method (request → reply), so later refactors keep the bytes.
- A session per screen: the action works, the screen doesn't hang, and the change survives a
  re-login (`control/run.py`, in-process and out-of-process); `tests/diff` equal between the port and
  `soa-emu`.
- `docs/server-rules.md` gains the group's rules; this document's tables shrink;
  `tools/unhandled_apis.py --summary` goes down.

### Decisions (the user, 2026-10-04)

- **Paid currency: allow.** Buying stones works locally and costs nothing.
- **Social: stub, and defer to multiplayer.** Follow, blacklist and neighbor calls get success
  replies with empty lists; real friends belong to the multiplayer schema plan
  ([`../server/PLAN-multiplayer-schema.md`](../server/PLAN-multiplayer-schema.md)).
- **Debug APIs: stub.** Each is a handler that returns success and does nothing.
- **Every stub logs when it is called.**

### Behaviour for the decisions, and the assumptions behind it

Assumptions are labelled (c) in `server-rules.md`, as every unproven rule is; a step that finds
evidence against one replaces it and records why.

**Stub logging.**
- A stub is a registered handler (so `--list-apis` shows it, with the file it lives in), built from
  one shared helper so every stub behaves the same.
- Each call logs one line at warning level, e.g. `stub: FollowAdd (fid 1b2c3d4e) called; answered
  success, nothing stored (docs/unimplemented-apis.md)`, with the request's fields in a short form.
  Every call is logged, not just the first (assumption: these calls are rare, so the log stays
  readable; a per-method count can be added if one turns out to be chatty).
- Methods still without a handler or stub (until their step lands) log the same way, as
  `no handler: <Method>`, in both hosts (`soa-server` and in-process), instead of answering silently.
- **Done (2026-10-04):** `ext::add_stub` (`server/src/core/stub.cpp`) logs
  `stub: <Method> (fid <fid>) called; answered success, nothing stored (docs/unimplemented-apis.md); <args>`;
  the library logs `no handler: <Method> (fid <fid>); answered with the host's fallback, nothing
  stored` for a request no handler answers (`server/src/core/lifecycle.cpp`; GetWorldMapInfoList,
  which the campaign answers, excepted), and in-process a status-only FakeApiCaller call logs
  `no handler: <Method> (status only, not served in-process: ...)` (`port/src/native/api/fakeapi.cpp`;
  nothing reaches the server for those).

**Paid currency (assumptions, all (c) until checked against the client in step 2).**
- `CoinList` lists the products from the master's coin/product table, as the store would; prices are
  shown but never charged.
- `CoinDepositCreate` creates a pending purchase (an id the client echoes back) and the platform
  update call (`CoinDepositAndroidUpdate`, which the port's Android client sends; the iOS and Amazon
  ones are answered the same way) **completes it immediately**: the product's stones are credited
  as **paid stones**, kept separate from free stones the way the player's currencies already are,
  and a purchase record is stored (product, amount, time) so the history is real.
- No receipt validation: the platform receipt the client sends is ignored.
- `GetBirthYearMonth` / `UpdateBirthYearMonth` store what the player enters; age-based monthly
  spending limits are **not** enforced (assumption: a local game has no reason to limit spending).
- First-purchase bonuses or limited-purchase counts in the product data are honoured if the master
  defines them (each product's limit counted from the purchase records).
- `DirectItemShopList` (items bought directly with paid currency) lists the master's products;
  buying goes through the existing shop purchase handling where it applies.

**Social stubs.**
- `FollowAdd` / `FollowRemove` / `BlacklistAdd` / `BlacklistRemove` / `UpdateFollowMax`: success,
  nothing stored; the follow list stays empty (assumption: the client reloads the list from the
  server, so an "added" friend just doesn't appear — checked in step 1).
- `NeighborList`: an empty list; `NeighborRegist` / `LocationRegist`: success, nothing stored (the
  location is never stored, which is also the privacy-safe choice).
- **As implemented:** every social stub answers `{Time}` only, with no list key: an absent list is
  the empty list the client had before (the wire answered `{Time}` and the in-process route `{}`, and
  the screens carried on, section 1). Assumption (d), recorded in `server-rules.md#social-stubs`.
- Helpers for missions keep coming from the existing rental/assist handling, which doesn't depend on
  follows.

**Debug stubs.**
- All 27 `Debug*` methods answer success with an empty reply and change nothing — even the ones
  whose names promise items or currency (`DebugGetCoin`, `DebugGetItem`). The 3.7.0 client can't
  send them; only tests or a modified client could.

**Settings and account (step 3.3; each (d) in docs/server-rules.md#settings-account).**
- The options: an id `master_config` doesn't have is refused (10403): the client sends only master
  ids. `GetConfig` doesn't send `Option` (COptionInfo: frame rate, volumes): the client keeps those
  settings itself, and leaving the key out leaves its copy as it was.
- The birth month: stored as entered and replaceable by entering it again (the client asks only
  while GetBirthYearMonth is refused); a string outside the client's own ranges is refused (10403;
  the client never sends one). Age-based monthly spending limits are **not** enforced (Decisions:
  a local game has no reason to limit spending).
- `ReadExpirationInfo` stores nothing and answers no `ExpirationInfoList`: the local server keeps no
  expiration state (no response sends one), so a read mark has nothing to change on the client.
- `SendGuideInformation` stores nothing and answers an empty `GuideInformationInfoList`: the local
  server shows no guide popups (the online ones announced the service's dated campaigns and shop
  items; the client shows the guides that list names, and no player load sends one).
- `GetScenarioLibraryInfoList` lists the cleared story missions (the core's `mission` clears and
  `campaign_clear`) of the episode type asked for: (c) the library replays the story of cleared
  missions. A `--campaign-seed` chain is listed only once its first clear has saved it (the
  library reads the state DB).
- `UpdateSession`: no handler (2.3).
- In-process, the eight methods are served through `kServedStatusOnly` (docs/client-changes.md);
  `UpdateBirthYearMonth`'s arguments are sent as NetworkApiCaller sends them ("YYYY-MM").

**Storage and the overflow box (step 3.1, done).** The rules and their evidence are
[`server-rules.md#storage`](server-rules.md#storage); what had to be assumed, and why:
- A stored item stays an `items` row (`stored_at` set) instead of moving to a table of its own: its
  gear, lock and the history's references stay intact, and every inventory API ignores it (the
  client's equivalent: the item leaves the item list). Not observable by the player.
- `update_at_time` is the deposit time / the box row's last change in seconds since the epoch (the
  client reads a number and only sorts by it); the box's are kept unique per row because the box
  screen tells its entries apart by it.
- The box entry's `id` is its master item id (the client never reads it; it matches entries by
  master id).
- A locked stored item can't be sold (10204), as in the inventory.
- Refusal codes chosen from the client's texts: 10203 (equipped), 10211 (storage full), 10202 (no
  room in the inventory), 10206 (more than the box holds), 10403 (an item not where the request
  says).
- An overflowed gacha weapon's `GachaItems` entry has `player_item_id` 0 and its history row no
  uid. The client's "sent to the box" messages (`uimsg_gacha_wapon_itemmax` ...) are chosen by code
  not traced (the reader of `AddOneTimeStorageInfo` wasn't found), so they may not show; the item
  is in the box either way.
- Items taken out of the box are new level-1 items (the box keeps no item state), content type 1,
  drop type 0.
- `storage_stock` is no longer the assumed 500 but 100 + 400 with the Galaxy Pass (client and master
  evidence); without `--galaxy-pass` a player now has 100 storage slots. **The user's decision
  (2026-10-05): keep it so** (100, +400 with the Galaxy Pass).
- The その他設定 options that send equipment to the box always (is_one_time_storage for the
  gacha's, is_one_time_storage_except_gacha for the rest) are read by `storage::to_one_time_storage`
  from the settings step's stored options (`settings::config_on`).

**Mastery (step 3.4, done: `server/src/api/growth/mastery.cpp`, docs/server-rules.md#mastery).** No
port change: the three are "empty" methods, answered in-process by the registered handlers. Read
from the client: the request shapes (pairing is `TrainMastery` with step 0), the reply keys
(`dojo_no` is missing from `port/fakeapi/fields.txt`), LV70 and the same role, the pass medal's
cost, the 皆伝 gift, the inheritance in `CPersonInfo` and `UpdateAwakenLevel`'s child update. The
assumptions, each (d) in the code and in server-rules.md:
- A dojo with a pair still training refuses another pair (the selection screen pairs only in an
  empty dojo, so the client never asks).
- A training done with the pass medal stores the card it was used on (the client shows only the
  count of cleared trainings).
- The talent a 弟子 inherits is the 師匠's in its role's `mastery_talent_slot`, from its awakening's
  `master_awaken` row when that row sets the slot (the master data changes it at awakening 5 for
  some roles; the client's own fallback reads the 師匠's talent list the same way); it and the
  parent role follow the 師匠's later growth (computed from the stored pair, not snapshotted), and
  `UpdateAwakenLevel` reports the 弟子's talent whenever the awakened character has one.
- Parting returns nothing paid (the dialog offers nothing back).

**Mascot and role (step 3.5, done: `server/src/api/player/home.cpp` `change_mascot`,
`server/src/api/growth/growth.cpp` `change_role`; docs/server-rules.md#home-mascot, #role-change).**
Both were status-only; two `kServedStatusOnly` rows route them in-process (docs/client-changes.md
"Mascot and role"). Assumptions, (d) in the code and in server-rules.md:
- ChangeMascot takes any `master_person` id: the mascot list (type-3 `master_home_message` rows
  the story progress opens) is the client's, and the client keeps its own copy (KVS
  `HomeMascotID`); `Player.mascot_id` is sent only once a mascot was chosen (no key before, as the
  server always did).
- ChangeRole resets the character's set skills in the party sets too (the client says the set
  skills are reset; the sets hold their own copies), and keeps level, skill levels, limit break,
  awakening and equipment (the dialog mentions only the skills).
- Decorations (`server/src/api/player/deco.cpp`, docs/server-rules.md#deco): `NumDecoObject` is the
  gate the client checks (confirmed in game) and comes with every response once one is owned; one of
  each decoration (the favourites name them by master id); a character's objects and pose are
  stored as the client sent them, with no cost limit (the menu shows the gauge); ids not owned are
  skipped by the favourites. The present box's receive result doesn't list a decoration it gave
  (the grant hook can't add to it); the menu still shows it, since the client asks GetDecoInfo.
  SetCharacterDeco's payload needed a port change in-process (docs/client-changes.md
  "SetCharacterDeco"): the client's own serializer makes the bytes NetworkApiCaller sends.
- Not played on screen: the mascot change (the seeded player's progress opens one mascot, so the
  button is hidden); unit test and replay corpus only.

**The remaining groups (steps 1–6).** Their rules come from the decompile and the master (step 2),
not from guesses; where something can only be assumed (e.g. a value the client never shows), the
step records it here and in `server-rules.md` as (c).

**Missions and equipment (steps 3.2 and 3.4's equipment; agent server-u-missions).** Evidence in
[`server-rules.md`](server-rules.md) ([2.6](server-rules.md#failure-continue-restart),
[Battle simulator](server-rules.md#battle-simulator), [Auto-equip](server-rules.md#equip-auto),
[Accessory inheritance](server-rules.md#accessory-inheritance),
[Stocks and wallet](server-rules.md#stocks-and-wallet)); what had to be assumed, and why:
- `MissionContinue`: the play stays open across a continue (same mission, party, stamina, surprise
  roll), since the battle goes on and the client ends it later with `MissionEnd` / `MissionFailed`
  as for any battle. A continue with nothing in progress or for a mission without `is_continue` is
  refused with 10403, coins short with 20000: the client never sends either (it declines by itself),
  so the codes are only the server's choice. When several continue campaigns run, the first in the
  master's order counts (the client takes the first in its own list, whose order wasn't read).
  The campaign windows are read on the event calendar, as the stamina campaigns are.
- `MissionLose`: no 3.7.0 caller, so it is answered as `MissionFailed` (the play ends, nothing given).
- `TrainingMissionStart`: no play record and no play count, because nothing ends a simulator battle
  on the server (the client sends neither `MissionEnd` nor `MissionFailed` for type 4): a record
  would make the next login offer to resume it. Nothing is granted (the row's EXP and FOL are 0;
  there is no end request to grant at). The party is MissionStart's current party (the simulator's
  own party screen saves the party as the mission menu does; seen on screen in the session).
- `EquipAuto`: the online server's choice isn't known. The server takes the owned weapon of the
  role's kind with the highest attack + intelligence and the accessory with the highest sum of its
  five stats (base stats over the level, as `gear.cpp` already estimates weapons), never an item
  another character wears (`auto_equip_steal` is false by default), fills only the empty skill
  slots with the role's open skills (so a player's chosen skills stay), and leaves the assist alone
  (no rule for picking an assist could be found). The `master_config` defaults stand for the
  player's settings until `UpdateConfig` stores them (the settings group; the parent wires them at
  merge).
- `InheritAccessory`: seen on the strengthening screen, it is a compose that also takes in the
  material's factor, once, from an ordinary accessory (the other inheritance accessories are
  greyed out); assumed: a locked or equipped material is refused as for any compose, and the
  material's limit break is kept as `inherited_master_item_limit_break_count` (the client sends it
  back as the lost item's; what it changes wasn't read).
- `UpdateItemStock`: refused with 11006, as `UpdateGearStock`: the stock starts at the maximum
  `item_stock_max` (the starting capacity isn't in the master), where the client hides the button.
