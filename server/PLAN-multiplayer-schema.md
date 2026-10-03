# Plan: the state schema for multiplayer

Status: **plan for review only, not queued (future work); if queued, starts only after S12 (the user, 2026-10-03)**. That is, only after all of [PLAN-schema.md](PLAN-schema.md)'s S0–S12, plus R12, R17 and S11 + R19, have landed. Written 2026-10-03 by agent `mp-schema` (branch `port/mp-schema`, off main 8cb4ed2); no code changes. port/PLAN.md lists it under "Future work (not queued; needs the user's review)".

- **Starting point:** PLAN-schema's final schema (its 3.2, version N, plus S12's campaign tables), not today's. Nothing in S3–S12 changes for multiplayer. Where an S step's design makes an M step costlier, the M step says so as a **known cost** (section 4).
- **Other inputs:** the multiplayer study ([docs/multiplayer.md](../docs/multiplayer.md), [docs/multiplayer/HANDOFF.md](../docs/multiplayer/HANDOFF.md)) and port/PLAN.md's "Future work" note.

**The question** (the user): "For the database schema, after the schema fixes land, what changes need to happen to support multiplayer?"

**Labels**, as defined in [docs/server-rules.md](../docs/server-rules.md): **(a)** master data, **(b)** client-side evidence (the 3.7.0 client: decompiles, the info classes' fields in `port/fakeapi/fields.txt`, captures), **(c)** outside knowledge, **(d)** assumption. A [confirmed] or [run] line of docs/multiplayer.md counts as (b).

---

## 0. Summary

- **What multiplayer needs from persistent state** (section 1):
  - several real players with their devices;
  - follows, mutual follows, blacklists and a recently-played list;
  - a record of each co-op battle (its id appears in the event rankings, its members in the recently-played list);
  - rentals of real players' characters, and the lender's rental bonus;
  - rankings across players (event rankings, Sphere 211);
  - a world boss shared by all players.

  Rooms, slots, barriers, the relay's forwarding and stamps stay in memory. The friend gauge is a dead feature in 3.7.0 (no caller reads it, (b)) and gets no table.
- **Two routes** (section 2, open question Q1):
  - **B**: one state DB with a `player_id` on every per-player table;
  - **A**: one state file per player plus a small shared hub DB.

  **Recommended: B.** The client's multiplayer surface is mostly cross-player reads (follows, rentals, rankings, co-op parties, follow floors), and under B those are joins with foreign keys and one atomic commit.
- **The M steps (route B):**

  | Step | What |
  |---|---|
  | M1 | the per-player keys: every per-player table rebuilt with `player_id` and its per-player key, in four domain sub-steps M1a–M1d |
  | M2 | players, devices and one server-wide uid allocator |
  | M3 | every statement scoped to the request's player, with a lint gate and two-player isolation tests |
  | M4 | the social tables |
  | M5 | co-op battle records |
  | M6 | rankings, rentals and the world boss across players |
  | M7 | tools, fixtures and the session scripts |
- **The known cost of the ordering** (section 4): after S12 every per-player table has been rebuilt once (S4–S10 make them all `STRICT`). Adding a `NOT NULL` foreign-key column or changing a primary key needs a rebuild (SQLite facts, section 2.3, tested), so **M1 rebuilds about 50 tables a second time**.
  - On the code side: about 113 write sites bind `player_id`, and about 45 `on conflict` targets change.
  - Four reference choices of 3.2 can't survive a per-player key and change in M1:
    - `player.title_id` and `ds_offer.ship_id`: SET NULL → NO ACTION;
    - `player.party_id`: becomes composite;
    - the `id = 1` singletons: keyed by player instead.
  - None needs a third rebuild: M1 also adds the nullable columns M5 and M6 will need.
- **Non-schema prerequisites that shape the schema** (section 6):
  - the request→player resolution (`Ctx` gets the request's player, from the device);
  - per-connection request state instead of the server-global `pending[fid]` / `logged_in`;
  - one process owns the file, under the existing `Server::mu`.

---

## 1. What multiplayer needs from persistent state

### 1.1 The starting point (after S12)

The local server stays single-player by construction through S12. PLAN-schema 3.1: "One player per DB (… no `player_id` columns)".

- **One `player` row.** `player.id` = CHash32(search id), `LOCAL00001` (state/seed.cpp `kLocalPlayerId`). This id is the client's numeric player id (b: CPlayerInfo, the co-op owner id PlayerDetailInfo+0x6c, docs/multiplayer.md 1.6/1.7).
  - The reads of the player row have no `where`: 32 today, e.g. api/player/player_info.cpp:132 `player_id` = `select id from player`.
  - soa-server binds **every** device to it: net/game.cpp:131 `map_device`: `select id from player limit 1`.
- **Singleton rows `id integer primary key check (id = 1)`** (3.2): `play` (after S7 merges `play_ext`), `sphere`, `ds_state`, `favor_bonus_state`, `gear_barney`, `event_last`, and S12's campaign singleton if it has one. They are read and written with `where id = 1` (about 40 sites today, sphere211 the most).
- **`meta`** keeps only bookkeeping after S3: the uid allocators `next_char_uid` / `next_item_uid`, and `seed`.
  - **Seed and CreatePlayer reset both allocators** (state/seed.cpp:89-90, api/entry/entry.cpp:135-136) and write fixed roster uids `kRosterUid0 + i` (core/ids.h). A second player created this way would collide with the first's uids.
- **Synthetic other players.**
  - The rental list clones the player's own roster, lent by synthetic players `0x7d000000 + order` (api/social/rental.cpp; docs/server-rules.md "Rental helpers", (d)).
  - The event ranking and the Sphere 211 ranking have one entrant (d).
  - The world boss's "community totals" are the player's own (d).
  - The follow menu answers empty lists, and SearchPlayer is refused (api/social/social.cpp, (d)).
  - `FooterMissionInfo.is_open_multiplay` = 0 (api/player/home_footer.cpp, (d): no other players).
- **The campaign's progress** is in the state DB after S12 (`campaign_clear`, `campaign_last`). Before S12 it is a text file in the data root, which every player would share.
- **The SQL** (main 8cb4ed2): about 443 state-DB calls in 46 files (non-test; `grep '\.st\.(q|one|exec)'`): 113 insert sites, 186 update/delete sites, about 45 `on conflict` clauses, and the rest reads. None names a player. S3–S12 move code but don't change this shape.

### 1.2 What is needed, by feature

| Feature | Client evidence | What must persist | Label |
|---|---|---|---|
| **Players and devices** | The bridge and Login / SimpleLogin / NoLoginStart carry the device UUID (docs/api.md "Session and login"). CreatePlayer(name, uuid) creates the account. The relay's MissionEnd carries the UUID and DeviceType (multiplayer.md 1.8) | `player` rows (one per account); the device→player binding (`wire_device`, today without a real binding); `player.search_id` unique (SearchPlayer looks it up) | (b) the keys; (d) one player per device UUID, no account linking |
| **Distinct numeric player ids** | The client decides who owns a battle character by `PlayerCharacter[i].player_id` and the host by slot 0. Two clients with the same id both drive every character (multiplayer.md 1.7, run 4) | `player.id` stays CHash32(search id), unique per player. **The existing player keeps its id.** "Player 1" below means the first row, not id 1 | (b) |
| **Follows / mutual follows** | `FollowList` → `Follow`, `FollowPlayerList`, `FollowID`, `MutualFollowID`. `FollowAdd(u32 player id)` → `AddFollow`, `AddMutualFollowID`. `FollowRemove`, `UpdateRelationShip` (four id lists). `CFollowPlayerListElementInfo` {player_id, last_login_at, master_role_id, **is_follower**}. The room filter 相互フォロー限定 (multiplayer.md 1.2) | a directed follow relation; "mutual" = both directions; `player.follow_max` (raised by `UpdateFollowMax`) | (b) keys and fields (docs/api.md "Social", fields.txt:46); (a) `follow_default` 30, `follow_max` 300, `follower_max` 20, `follow_up_num` 5, `follow_use_coin` 100 |
| **Blacklist** | `Blacklist` → `Blacklist`, `BlacklistPlayerList`, `BlacklistID`. `BlacklistAdd` / `BlacklistRemove(u32 player id)`. The rental list skips players in `BlacklistID` (docs/server-rules.md "Rental helpers") | a directed block relation | (b); (a) `block_max` 50 |
| **Recently played** | `GetRecentlyPlayedList` → `RecentlyPlayedDetail` (CContactList). `CFollowPlayerInfo.played_with_at` (fields.txt:45) | who played with whom and when, from co-op battles | (b) keys; (a) `recently_played_list_length` 30; (d) a co-op battle is what counts as "played with" |
| **Search / profile** | `SearchPlayer(search id)` → `SearchResult`. `GetPlayerDetailInfo(u32 player id)` → `SearchResult` {player id: CFollowInfo} | nothing new: reads of another player's `player` and `roster` | (b) |
| **Rooms, lobby, relay** | The lobby (CreateRoom, GetRoomList, Automatch, CloseRoom) and the relay's room and battle messages (multiplayer.md 1.4/1.5, 3.1/3.2). The relay has no authentication | **nothing**: rooms, slots, ready flags, barriers and the forwarding live in memory, as HANDOFF.md says; the client re-creates a room after a disconnect (there is no Reconnect, (b)) | (b) the protocol; (d) no persistence |
| **Co-op mission plays** | The relay runs MissionStart for every player (MissionStartPush) and MissionEnd per player from each player's own battle log, identified by UUID (MissionEndPush). MissionFailed comes from the host only. MultiMissionRestart resumes an interrupted co-op mission after an app restart (multiplayer.md 1.8). `MissionParameter.multi_player_count` | per player: the ordinary `play` row, plus a link to a shared **co-op battle** record (mission, host, members by slot with player id and leader uid) that MultiMissionRestart and the per-player MissionEnd find | (b) the flow; (d) the record's shape |
| **Battle id** | `EventRankingInfo` {player_id, party_player_id1..4, party_player_id1..4_valid, party_role_id1..4, **battle_id**, created_at} (fields.txt:131) | a battle id shared by the members of one co-op battle; the ranking row keeps the party's player ids | (b) |
| **Rewards** | Per player, from its own battle log (b). `Multi_Player_Number_2/3/4` = 1 / 1.5 / 2 (a), presumably a reward multiplier (inferred in multiplayer.md 1.8). `host_bonus` columns are 0 or NULL everywhere (a) | nothing shared: each player's MissionEnd credits only that player's rows. The co-op record notes per member that its MissionEnd ran, so a repeated relay MissionEnd isn't credited twice | (a) + (d) |
| **Rentals of real players** | `BattleRental` entries are CFollowInfo {order, CFollowPlayerInfo, CFollowPersonInfo (player_id, master_role_id, the equipment, add_*, awaken, rush skill, favor_level, …)} (fields.txt:44-45). `Player.support_pc_id` is the character a player lends. The rental bonus pays "by the number of rentals the day before" (`uimsg_sphere211_getting_rental_bonus`, (a) `master_rental_bonus`). `Sphere211RentalCharacterInfo` {player_id, **follow_player_id**, updated_at} (fields.txt:147) | a **lender** player id and uid on each rental (MissionStart's helper, Sphere 211's rentals); the lender's per-day rental count (counted when *another* player rents its character) | (a) + (b); (d) which players are listed (followed first, then recent, then anyone) |
| **Event rankings** | `GetEventRankingInfo` → `EventRankingInfoListMap` / `EventRankingTopInfoListMap` {ranking id: [EventRankingInfo]} and `EventRankingPlayerInfoMap` {player id: {name}} (docs/server-rules.md "Event extras") | each player's best score per ranking, with the battle's party (player id and role per slot) and battle id. The rank is computed across players when read | (b) |
| **Sphere 211 ranking and follow floors** | `Sphere211RankingInfoMap` / `Sphere211RankingTopInfoMap` {player id: {player_id, floor_level, entered_at, rank}}; `Sphere211FollowFloorInfo` {player_id, floor_level, follow_status}; `CFollowPlayerInfo.sphere211_floor_level` / `sphere211_previous_floor_level` (fields.txt:45, 145-146) | each player's season best (`sphere_rank`); the followed players' current floors (a read of their `sphere` row) | (b) |
| **World boss** | Gauges `num1..3` against `next_required_num`; per player: the wave-clear dialogs (`CWorldBossPlayerInfo.is_received` / `is_notified` / `is_new_open`) and the last win's share `add_item1..3_num` (docs/api.md GetWorldBossInfo, (b)). The master sized the waves for the whole player base (hotspring wave 1: 3,100,000, (a)) | the boss's community state (wave, gauges, wave start, big hunt) **shared**; the per-player part (last share, clears seen, cut-in seen) per player | (a) + (b); (d) the requirement scaling with N local players |
| **Stamps** | `StampList` / `StampSlot` are owned state; `SetStampSlot`; in a room, `Stamp` / `StampPush` over the relay (multiplayer.md 1.5) | the relay's stamps: nothing. Owned stamps are per-player state, but the server doesn't serve `StampList` today (no `Stamp` in server/src) | (b); (d) out of scope here, a plain per-player table when someone serves them |
| **Friend gauge** | `FriendGauge` / `AddFriendGauge` / `FriendGaugeUpdate` are parsed (`CFriendGaugeInfo` {player_id, target_player_id, master_id, reward_index}), and `master_friend_gauge` has 1 row with 10 contents (a). But `FriendGaugeModel::GetById` @016c11a8 has **0 callers** (`tools/callers.py`, this study; decompile `work/decomp/mp-schema-fg.resolved.c`) | **nothing**: the client never shows it | (b) a dead feature in 3.7.0 |
| **Neighbors / check-in (GPS)** | `NeighborList` / `NeighborRegist` / `LocationRegist` (docs/api.md) | out of scope (location features; the port has no GPS) | (d) |
| **Everything else** | the per-player state of PLAN-schema 3.2 | unchanged, keyed by player | — |

### 1.3 Ephemeral vs persisted

| In memory (soa-server process) | Persisted (state DB) |
|---|---|
| rooms and their ids, conditions (public/private, comment, recruited roles), the members' PlayerDetailInfo, slots, ready flags | players, devices |
| the relay's connections, barriers, rush-combo arbitration, the Snapshot / Message / AIParameter forwarding, stamps sent in a room | follows, blacklist, recently-played |
| bridge sessions and keys (`net/game.cpp` `sessions_`, `tokens_`), per-connection `logged_in` | the co-op battle record and its members (battle id, mission, host, per-member state) |
| the pending request per connection (section 6) | each player's `play`, linked to its co-op battle |
| | rental records with the lender, and the lender's per-day counts |
| | ranking scores with the party's player ids; Sphere 211 bests |
| | the world boss's shared state and the per-player part |

A co-op battle record is written at StartMultiplay and kept: the ranking's `battle_id` and the recently-played list read it after the room is gone. It isn't a room record.

---

## 2. The two routes

### 2.1 Route A: one state file per player

Each player's state is a post-S12 file, schema unchanged. A session→file map picks the file per request, and a small shared DB (`hub.sqlite3`) holds `player_index(id, search_id, file)`, devices, follows, blacklist, recently-played, co-op battles, ranking entries and the world boss's shared totals.

- **+** The SQL sites and the per-file migration stay as they are. Isolation holds by construction. The tools keep reading one player's file. No second rebuild.
- **+** The first co-op milestone (multiplayer.md M1–M3: two players in one battle, each credited) needs almost nothing else. That is why HANDOFF.md and port/REMAINING.md call it "the cheapest route".
- **−** Every cross-player feature reads another player's file:
  - the rental list (CFollowPersonInfo is a full battle status of the lender's character);
  - co-op MissionStart (PlayerCharacter[4] with each owner's statuses);
  - GetPlayerDetailInfo, SearchPlayer;
  - the follow lists (name, level, last login, support character);
  - Sphere 211 follow floors.

  So the server opens or `ATTACH`es other players' files read-only per request, or keeps a denormalized "profile" projection in the hub that every request touching player or roster must refresh.
- **−** No foreign key can cross files: a follow of a deleted player, or a ranking row's party player, is checked by `state::check`, not declared.
- **−** Atomicity across files is lost in WAL mode. SQLite commits attached databases atomically only with a rollback journal, and the server runs `journal_mode = wal` (state/README.md). A MissionEnd that credits the player's file and writes the hub's ranking row can half-commit.
- **−** Each file migrates on its own open; a player who doesn't log in stays on an old version until it does.

### 2.2 Route B: one state DB, `player_id` on every per-player table

- **+** Cross-player features are joins: follows, the rental list, rankings across players, co-op party composition, world boss totals.
- **+** Foreign keys cross players: a follow references `player(id)`, a co-op member references a player and a roster uid.
- **+** One transaction per request, one file, one migration path.
- **−** M1 rebuilds every per-player table a second time (section 4: the known cost of running after S12).
- **−** Every statement must be scoped to the request's player: about 443 sites (M3). A missed `where player_id = ?` leaks or corrupts another player's rows. Hence M3's lint gate and isolation tests.
- **−** The tools, tests/diff's state comparison and the session scripts read a file with several players (M7).

### 2.3 SQLite facts that constrain the design (tested 2026-10-03, Python sqlite3 3.45.1, the vcpkg version)

1. **`ALTER TABLE … ADD COLUMN player_id integer not null default <id> references player(id)` is refused** on a table with rows: "Cannot add a REFERENCES column with non-NULL default value". A nullable FK column can be added, but `NOT NULL` and a new primary key both need a rebuild.
   - Plain columns without a reference (`player.follow_max`, a counter, a nullable `coop_battle_id` checked by `state::check`) can always be added by `ALTER`.
   - **Only keys and references force M1's rebuild.**
2. **A composite foreign key with `ON DELETE SET NULL` sets every child column of the key to NULL.** With `foreign key (player_id, weapon_uid) references items(player_id, uid) on delete set null` and `player_id NOT NULL`, deleting the item fails: "NOT NULL constraint failed: roster.player_id".
   - So a "points at" reference into a parent with a per-player key can't be a composite FK with SET NULL. That covers equipment, home, assist and support as well as 3.2's `ds_offer.ship_id` and `player.title_id`.
   - Composite FKs with `CASCADE` or `NO ACTION` work, and they make a cross-player reference impossible: `insert into roster (2, 7, 200)` with item 200 owned by player 8 fails with "FOREIGN KEY constraint failed".
3. **UPSERT on a view is refused** ("cannot UPSERT a view"). So per-request temp views that scope the unqualified table names to one player can't serve the writes, which S0 made upserts. The scoping is explicit SQL (M3).

### 2.4 Recommendation

**Route B** (Q1). The client's multiplayer surface is much more than co-op battles:

- the room filter by mutual follows;
- recently-played, with `played_with_at`;
- rentals of real players, with full battle statuses;
- rankings that name the co-op party's players and the battle id;
- Sphere 211 follow floors;
- a shared world boss.

Under route A each of these needs the hub plus reads of other players' files, with no foreign keys and no atomic commit. Under route B they are ordinary rows.

B's price is M1's second rebuild and M3's scoping. Both are mechanical and gated: M1 changes keys and copies every row; M3 is checked by a lint rule and isolation tests.

If the user wants only two-player co-op battles soon and nothing social, route A is cheaper: section 7 lists what changes then. Going A first and B later would migrate everyone's data twice, so pick one.

---

## 3. Conventions for route B

These extend PLAN-schema 3.1. From M1 on they replace its line "One player per DB (as today: `player` has one row; no `player_id` columns)".

1. **Three kinds of table.**
   - **Shared (server-wide):**
     - `meta`, with the uid allocators (made server-wide in M2) and `seed`;
     - `wire_device` (the device→player binding);
     - the social relations and the co-op battle records (M4, M5), which reference players;
     - the world boss's community part (M6).
   - **Per-player, keyed by an allocated id** (`roster.uid`, `items.uid`, `gear_items.uid`, the `autoincrement` ids of `presents`, `gacha_history`, `ds_log`, `sphere_box`, `sphere_log`):
     - the primary key stays;
     - the table gains `player_id integer not null references player(id) on delete cascade` and an index `(player_id)`;
     - the parents of composite references (`roster`, `items`) also gain `unique (player_id, uid)` (fact 2: the target of a composite CASCADE / NO ACTION FK).
   - **Per-player, keyed by a master id or a small per-player number:** the primary key becomes `(player_id, <3.2's key>)`. These are:
     - by master id: `stock`, `favor`, `favor_drop_play`, `mission`, `unlocks`, `titles`, `achievements`, `login_bonus`, `premium_pass`, `subscription`, `counters`, `shop_counts`, `exchange_counts`, `stepup`, `box_state`, `box_slots`, `ds_area`, `ds_offer`, `ds_bonus`, `sphere_cell`, `sphere_rank`, `sphere_rental`, `sphere_rental_day`, `follow_rental`, `event_rank_score`, `event_rank_received`, `wboss`, `wboss_clear`, S12's `campaign_clear`;
     - by a small per-player number: `party_set` and `party_member` (sets 1..max), `ds_ship` (ships 1..3: `ds_ship.ship_id` is the client's `ship_id`, (b) api/deepspace/state.cpp), `ds_ship_member`, `play_member` (slot).
   - **Per-player singletons** (`play`, `sphere`, `ds_state`, `event_last`, `favor_bonus_state`, `gear_barney`, S12's `campaign_last` if it's a singleton): `id integer primary key check (id = 1)` becomes `player_id integer primary key references player(id) on delete cascade`.
2. **uids are unique across the server.** One allocator in the shared `meta` serves every player.
   - Single-column FKs to `roster(uid)` / `items(uid)` keep working with `SET NULL` (fact 2).
   - A rental id (roster uid with bit 40, api/social/rental.h) still identifies the lender's character.
   - A co-op `PlayerCharacter` list never holds two characters with one uid. Run 4 of the study had colliding uid spaces and still worked ((b) [run]), so this is a convenience (d), not a client requirement.
3. **Same-owner is an invariant.** Each "points at" reference must point at a row of the same player.
   - `state::check` gains a cross-owner query per reference, e.g. `select r.uid from roster r join items i on i.uid = r.weapon_uid where i.player_id != r.player_id`. It runs in `server/schema-integrity` and the session gates (G9).
   - The handlers already check ownership before writing (`owned_character`, `find_item`); M3 makes those checks player-scoped.
4. **References between per-player rows.** Parts use the composite key with CASCADE; checked links use it with NO ACTION, deferred:
   - `party_member (player_id, party_id) → party_set`;
   - `player (id, party_id) → party_set (player_id, party_id)`;
   - `ds_offer (player_id, area_id) → ds_area`;
   - `ds_ship (player_id, area_id) → ds_area`;
   - `ds_bonus (player_id, ship_id) → ds_ship`;
   - `ds_ship_member (player_id, ship_id) → ds_ship`;
   - `box_slots (player_id, gacha_id) → box_state`;
   - `wboss_clear (player_id, boss_id) → wboss`;
   - `unlocks (player_id, by_mission) → mission`.

   3.2's two **SET NULL** references into parents that get a per-player key become **NO ACTION**:
   - `player.title_id → titles (player_id, id)`: titles are never deleted, so NO ACTION changes nothing;
   - `ds_offer.ship_id → ds_ship (player_id, ship_id)`: mission end already clears the offer's `ship_id` (`renew_offer`, api/deepspace/deepspace.cpp:435) before it deletes the ship (:500). The alternative is a global surrogate key on `ds_ship`; the recommendation is NO ACTION.
5. **The existing player is the first row.**
   - M1 fills `player_id = (select id from player)` in every per-player table.
   - A state without a player (the new-player mode before CreatePlayer) has no per-player rows to fill. M1 deletes any orphan row it finds, with a LOGW per table (PLAN-schema 4.1's "dangling → declared action"). `titles` and `gear_barney` are re-created on demand (`ensure_defaults`, `barney_current`).
6. **Writes name `player_id` from M1.**
   - Every insert binds `ctx.player_id()` (it exists: core/context.cpp:25).
   - Every `on conflict(<pk>)` names the new key.
   - **Reads, updates and deletes are scoped in M3.** With one player per DB an unscoped read is still correct, so M1's and M2's replay gates (RG4) stay meaningful.
7. **Uniqueness.** `player.search_id unique` (3.2 has it). `wire_device.uuid` stays the key; a device belongs to at most one player.

---

## 4. Known costs: what the post-S12 schema makes M1 change

The S steps proceed as written (the user). This table lists, per S step, what its final design leaves for M1, so whoever runs M1 knows which rebuild is a second one and why. Counts are `grep` on main 8cb4ed2 and **include the tests' write sites** (e.g. `favor`'s 5 are 1 in api/favor plus 4 in tests): the tests bind `player_id` too.

| S step | What it leaves after S12 | What M1 changes (cost) |
|---|---|---|
| **S3** | `ds_state` created `id … check (id = 1)`; `sphere`'s new columns | `ds_state`, `sphere` keyed `player_id` (convention 1). 2 `ds_state` writers, about 25 `sphere … where id = 1` sites (M3 scopes them) |
| **S4** | `roster` and `player` rebuilt; `player.party_id → party_set(party_id)` single-column, deferred; `player.title_id → titles` SET NULL; `party_set` keyed `party_id` | **Second rebuild** of `roster` (+ `player_id`, `unique (player_id, uid)`) and `player`: `party_id` becomes the composite `(id, party_id) → party_set (player_id, party_id)`; `title_id` becomes NO ACTION (fact 2). Roster write sites: seed, CreatePlayer's `add_starters`, `add_character`, and MissionStart's `temp.roster` NPC rows (which name every column, so they copy `player_id`) |
| **S5** | `items`, `gear_items` rebuilt | **Second rebuild**: `player_id` (+ `unique (player_id, uid)` on `items`). items 4 write sites, gear_items 1 |
| **S6** | `party_member` keyed `(party_id, slot)`, `party_set` keyed `party_id` | **Second rebuild** of both: `(player_id, party_id[, slot])`, the composite cascade. UpdatePartySet 1 site, seed / CreatePlayer; `party_session.sh` |
| **S7** | `play` (+ `play_ext`'s fields) `id = 1`; `play_member (slot)`; `ds_ship_member`; `ds_log` with an id. S7 may keep or drop `play_ext.helper_*` (it offers both) | **Second rebuild**: `play` keyed `player_id`, `play_member (player_id, slot)`, `ds_ship_member (player_id, ship_id, slot)`, `ds_log.player_id`. **M1's `play` also adds** `helper_player_id` / `helper_uid` (if S7 dropped them) and a nullable `coop_battle_id`, so M5 / M6 need no third rebuild. `record_play` 1 site |
| **S8** | `presents` with `text` | **Second rebuild**: `presents.player_id` + index. 2 write sites (`ext::add_present`, `api_get_present`) |
| **S9** | `favor`, `titles`, `login_bonus`, `premium_pass`, `follow_rental`, `sphere_rental_day`, `ds_area`, `mission`, … rebuilt with CHECKs and renames | **Second rebuild** with `(player_id, <key>)`. Write sites: favor 5 (+ `restore_favor_session.sh`), titles 2, login_bonus 1, premium_pass 1, follow_rental 4, sphere_rental_day 1, ds_area 4, mission 5. About 12 `on conflict` targets |
| **S10** | the module tables `STRICT` with FKs; `ds_offer.ship_id → ds_ship` SET NULL; `wboss` / `wboss_clear` per boss; `event_rank_score.roles` as typed columns or a child table; `gacha_history` split uids; singletons `favor_bonus_state`, `gear_barney`, `event_last` `id = 1` | **Second rebuild** of each (convention 1). `ds_offer.ship_id` becomes NO ACTION (fact 2). **M1's `event_rank_score` also adds** `party_player_id1..4` and `battle_id` (nullable) beside the roles, matching `EventRankingInfo` (b), so M6 doesn't rebuild it. `wboss` / `wboss_clear` become per player; M6 adds the shared part as new tables (no third rebuild). About 30 write sites and about 15 `on conflict` targets in deepspace, sphere211, gacha (box, step-up), shop, events and daily; the sphere211 / deepspace session scripts |
| **S11** | `state::check` / `--check-state` | M1 extends `RELS` / `state::check` with the per-player classification and the cross-owner queries (convention 3) |
| **S12** | `campaign_clear`, `campaign_last` (single-player) | **Second rebuild**: `(player_id, mission_id)` / keyed `player_id`. 2 functions in api/campaign/progress.cpp |
| **S0** (upserts) | every parent written with `on conflict(<pk>)` | about 45 `on conflict` targets change with the keys above (counted in the rows) |

**Not a second rebuild:**

- `meta` (shared);
- `wire_device` (already has `player_id`);
- columns that only need adding: `player.follow_max`, `coop_battle_id`, the ranking's party ids. These are nullable or defaulted with no FK, so `ALTER` is enough, but M1 adds them in its rebuilds anyway.

**What a different S design would have saved** (recorded, not proposed; the user has decided the order): had S3–S12 created their tables with `player_id` and the per-player keys, M1 would not exist. The schema cost of multiplayer would have been one extra column per rebuild that happens anyway.

---

## 5. The M steps (after S12)

- **Versions** continue after S12's (v11 if S11 stays version-less).
- **Commits:** each step is its own commit, or a few.
- **Gates:** PLAN-schema section 5 (G1–G9) and the memory's gate tiers.
- **Names:** docs/multiplayer.md has its own staged plan, also called M1–M4 (lobby and relay). Where both appear together, this plan's steps are **"M-schema N"**. docs/multiplayer.md's M1 needs M-schema 1–3, and its M3 (real rewards) needs M-schema 5.

### M1: the per-player keys (route B's second rebuild), in four sub-steps

- **Schema:** convention 1 applied to every per-player table, with PLAN-schema 4.1's rebuild procedure under `foreign_keys = off`, per table:
  1. `create new_X` with `player_id` and the new key;
  2. `insert into new_X (player_id, cols…) select (select id from player), cols… from X`;
  3. `drop X`;
  4. `alter table new_X rename to X`;
  5. recreate X's indexes;
  6. `foreign_key_check`.
- **Four sub-steps**, each its own version and transaction.
  - **Each group is closed under the references whose parent key changes.** These are 3.2's FKs into `party_set`, `titles`, `mission`, `ds_area`, `ds_ship`, `box_state` and `wboss`. A child and its parent must be rebuilt in the same sub-step. Between sub-steps, a single-column FK to a column that is no longer unique on its own makes `pragma foreign_key_check` fail: "foreign key mismatch" (tested, 3.45.1).
  - The references to `roster`, `items`, `presents` and `player(id)` keep their parent key, so they may cross groups.
  - The groups:
    - **M1a core:** `player`, `titles` (`player.title_id`), `party_set`, `party_member`, `play`, `play_member` (`play.party_id`), `roster`, `items`, `stock`, `gear_items`, `gear_barney`.
    - **M1b missions:** `mission`, `unlocks`, `event_last`, `campaign_clear`, `campaign_last`.
    - **M1c economy:** `gacha_history`, `stepup`, `box_state`, `box_slots`, `presents`, `login_bonus`, `premium_pass`, `subscription`, `favor_bonus_state`, `follow_rental`, `achievements`, `counters`, `shop_counts`, `exchange_counts`, `favor`, `favor_drop_play`.
    - **M1d modules:** `ds_*`, `sphere*`, `wboss`, `wboss_clear`, `event_rank_*`.
- **Code:** convention 6 for the group's tables, in the same commit. Each insert binds `ctx.player_id()`, and each `on conflict` names the new key. The S0 lint (`schema_inventory.py --lint`) already forces column lists, so the new column can't be skipped silently: a missing bind fails with `NOT NULL constraint failed` in the selftests' seeding and the replay.
- **The playerless phase.** Before CreatePlayer (the new-player flow) `ctx.player_id()` is 0, so a write to a per-player table fails on its FK although the bind is right.
  - Such writes exist: api/player/titles.cpp:116 already returns early without a player, because the player-load hooks run on a playerless NoLoginStart.
  - Each sub-step's gate therefore includes the `tutorial` replay corpus and `emulator/scripts/emulator_session.sh --new-player` (PLAN-schema G6), the only flows with a playerless phase.
  - A handler that writes a per-player table before CreatePlayer gains the titles.cpp guard, or its refusal is declared. When RG4 goes red on the tutorial corpus, look there first.
- **Tests:**
  - `server/schema-migrate-vM1a..d` on the v0 fixture migrated through S12: every row keeps its values and gains the one player's id; `foreign_key_check` empty; `state::check` clean.
  - `server/schema-fk-actions` extended: deleting a player cascades everything; a cross-player `party_member` insert fails on the composite FK.
- **RG4** declared difference: each table of the sub-step gains a `player_id` column with the one player's id in every row. Bodies, codes and the log are identical.
- **Size:** the largest M step. About 50 tables, 113 write sites and 45 `on conflict` targets, in four commits. It is mechanical: the new DDL is 3.2's plus one column and a key, and the data mapping is the same copy for every table.

### M2: players, devices and one uid allocator

- **Schema:**
  - `wire_device` is the binding. `player_id` NULL means not bound yet: the new-player flow before CreatePlayer.
  - `player` gains plain columns by ALTER:
    - `follow_max integer not null default 30` ((a) `follow_default`; `UpdateFollowMax` raises it by `follow_up_num`);
    - `is_open_multiplay`, if Q4 picks per-player opening (else a server flag).
  - `meta`'s `next_char_uid` / `next_item_uid` are declared server-wide. `seed` stays the "seeded" marker of the first player.
- **Data mapping:**
  - none for the player's rows;
  - every existing `wire_device` row binds to the one player (as `map_device` did);
  - a `.bak-v<N>` copy as usual.
- **Code:**
  - `map_device` (net/game.cpp:130) looks the device up instead of `select id from player limit 1`. An unbound device gets no player, so its Login answers 19001 and the client runs CreatePlayer.
  - **CreatePlayer(name, uuid) creates a new player** bound to the uuid instead of replacing the one (api/entry/entry.cpp). It allocates its starters from the server-wide `next_char_uid` instead of `kRosterUid0 + k`, and **stops resetting the allocators** (entry.cpp:135-136).
  - `seed` (state/seed.cpp) does the same for any player after the first. The first keeps `kRosterUid0 + i`, so the existing player's uids don't change.
  - `search_id`: `LOCAL` + 5 digits of CHash32(uuid + name) (docs/server-rules.md "New player", (d)).
    - On a unique-index collision, rehash with a counter (d).
    - A numeric id inside the synthetic lender range `0x7d000000..+N` is also rehashed (d), so a real player can't be mistaken for a synthetic lender.
  - **`ext::Ctx` gets the request's player** (section 6): `ctx.player_id()` returns a field, not `select id from player`.
- **Tests:**
  - `server/mp-create-second-player`: two uuids → two players with distinct ids, search ids and uids; `foreign_key_check` empty; the first player's rows unchanged.
  - `server/schema-migrate-vM2`.
  - The replay corpora unchanged: one device, one player.

### M3: every statement scoped to its player

- **Schema:** none.
- **Code:** every read, update and delete of a per-player table gets `player_id = ?` with `ctx.player_id()`. That is about 443 calls in 46 files, done domain by domain like PLAN-readability's R steps (player, missions, gacha, items, growth, presents, daily, shop, deepspace, sphere211, events, social, campaign). Specific traps:
  - **`where id = 1`** on singletons → `where player_id = ?` (about 40 sites, sphere211 the most).
  - **`create temp table roster as select * from main.roster`** (api/missions/mission_start.cpp, the NPC party) copies every player's roster: add `where player_id = ?`.
  - **Aggregates without a key** (`select count(*) from gacha_history`, `from ds_log`, `from presents`, the achievements' `progress()`, `select max(...)`) count every player's rows.
  - **`select … from player`** (32 sites) → `where id = ?`. The wallet (core/wallet.cpp) and the stamina tick are the core's.
  - **Ownership checks** (`owned_character`, `find_item`, `item_equipped`, `find_gear`) must compare the owner, or another player's uid passes.
  - **`ext::with_live_server`** (net/game.cpp:41) and the response hooks run without a request player. Each must take one, or say why it needs none.
- **The gate that keeps it scoped:** `tools/schema_inventory.py --lint` gains a rule.
  - A statement that names a per-player table (convention 1, from `RELS`) must name `player_id` (or `id` for `player`) in its `where` / `join` / insert column list.
  - Exceptions are listed by function, with a reason: the shared tables, and the cross-player reads of M4–M6.
  - Joined literals are already parsed (S0c).
- **Tests:**
  - **The two-player fixture** `server/tests/fixtures/state-mp.sql`: players LOCAL00001 and LOCAL00002 (synthetic numeric id 1000000002, as in `docs/multiplayer/prototype/make_player2.sh`), each with rows in every per-player table. Written by `tools/make_state_fixture.py --players 2`. No real ids (the LOCAL rule).
  - **`server/mp-isolation`:**
    - every request of the replay's `api-sweep` corpus (all registered methods) runs as player A on the fixture;
    - `dump(B)` (every per-player table `where player_id = B`, plus B's `player` row) is byte-identical before and after;
    - no A response names a uid or id of B;
    - then the same with A and B swapped.

    The test lists the methods it ran, so a new method without a request in the corpus shows up.
  - **`server/mp-integrity`:** after the isolation run, `foreign_key_check` is empty and `state::check`'s cross-owner queries return nothing.
  - The replay corpora stay byte-identical (one player).

### M4: the social tables

- **Schema** (new, shared, all `STRICT`):

  ```sql
  create table follow (
    player_id integer not null references player(id) on delete cascade,
    target_id integer not null references player(id) on delete cascade,
    created_at integer not null,
    primary key (player_id, target_id), check (player_id != target_id)) strict;
  create index follow_target on follow(target_id);          -- followers, MutualFollowID
  create table blacklist (
    player_id integer not null references player(id) on delete cascade,
    target_id integer not null references player(id) on delete cascade,
    created_at integer not null,
    primary key (player_id, target_id), check (player_id != target_id)) strict;
  create table recently_played (
    player_id integer not null references player(id) on delete cascade,
    target_id integer not null references player(id) on delete cascade,
    played_with_at integer not null,
    battle_id integer,                       -- a coop_battle id once M5 lands (checked by state::check: Q6)
    primary key (player_id, target_id)) strict;
  ```

  - A mutual follow is both rows (b: `MutualFollowID` is derived; no request makes it).
  - The caps are rules, not constraints: `follow_max` / `follower_max` (a), `block_max` (a) and `recently_played_list_length` (a), applied by the handlers (Q9).
- **Code:**
  - api/social: FollowAdd / FollowRemove / FollowList / UpdateRelationShip / Blacklist* / SearchPlayer (by `search_id`) / GetPlayerDetailInfo / GetRecentlyPlayedList / UpdateFollowMax answer from the tables.
  - The rental list (`rental::follow_map`) lists real players' support characters (`player.support_uid`): followed players first, then recently played, then others; blacklisted players are skipped. The synthetic clones fill up to the list size only when Q3 says so.
  - `FollowList`'s `FollowPlayerList` reads other players' `player` / `roster` rows: documented cross-player reads (M3 lint exceptions).
- **Tests:** `social/follow-mutual`, `social/blacklist`, `social/search` and `social/rental-real-lender` on the two-player fixture; an isolation run still passes.

### M5: co-op battle records

- **Schema:**

  ```sql
  create table coop_battle (
    id integer primary key autoincrement,      -- the client's battle_id (EventRankingInfo, (b))
    mission_id integer not null, mission_type integer not null,   -- m:
    host_id integer references player(id) on delete set null,
    player_count integer not null check (player_count between 1 and 4),
    started_at integer not null, ended_at integer) strict;
  create table coop_member (
    battle_id integer not null references coop_battle(id) on delete cascade,
    slot integer not null check (slot between 0 and 3),           -- 0 = host (b)
    player_id integer references player(id) on delete set null,
    leader_uid integer references roster(uid) on delete set null,
    present integer not null default 1 check (present in (0,1)), -- DisconnectNodePush
    ended_at integer,                                             -- its MissionEnd ran (no double credit)
    primary key (battle_id, slot)) strict;
  ```

  `play.coop_battle_id` (added by M1) and `recently_played.battle_id` stay undeclared and are checked by `state::check`. Declaring them would rebuild `play` a third time (Q6).
- **Code:**
  - The relay's StartMultiplay creates the battle and its members in one transaction (the shared rows). Then it runs each player's MissionStart in that player's own request transaction, which writes its `play` with `coop_battle_id`.
  - The battle's characters: PlayerCharacter[4] = the members' leaders, each with its owner's `player_id`, then fillers from the host's and guests' parties (multiplayer.md 3.3). Their statuses come from each owner's rows: a cross-player read, and a lint exception.
  - MissionEnd per uuid → device → player → its `play` → its `coop_member.ended_at`. A second MissionEnd for the same member is refused (d).
  - MultiMissionRestart = MissionRestart for that player's `play` (d).
  - Each member's `recently_played` rows are upserted at the end.
  - The rewards are rules, not schema: `Multi_Player_Number_N` (a) as a multiplier in docs/server-rules.md, no host bonus (a), guests' stamina (d).
- **Tests:**
  - `missions/coop-start-end`: two players on the fixture; one battle, two plays; each credited only in its own rows; `ended_at` set; a repeated MissionEnd refused.
  - `missions/coop-restart`.

### M6: rankings, rentals and the world boss across players

- **Event ranking:** no new table. M1 gave `event_rank_score` the key `(player_id, ranking_id)`, the party's player ids and `battle_id`.
  - `GetEventRankingInfo` ranks across players (`order by score`; type 6 ascending, (b)).
  - `EventRankingPlayerInfoMap` names every listed player.
  - A co-op win writes each member's row with the same `battle_id` and the party's ids.
- **Sphere 211:**
  - the ranking ranks `sphere_rank` across players;
  - `Sphere211FollowFloorInfo` reads the followed players' `sphere.floor_level`;
  - `sphere_rental.follow_player_id` holds real lender ids (M1's key `(player_id, follow_player_id)` fits).
- **Rentals:** a new shared table `rental_log (id autoincrement, renter_id, lender_id, uid, kind (mission / sphere), at)`, written by MissionStart / Sphere211MissionStart with `play.helper_player_id`.
  - The lender's daily count (`follow_rental (player_id = lender, rental_day)`) comes from it.
  - The rental bonus pays the **lender** on its next load ((a) `master_rental_bonus`, (b) the popup; (d) a synthetic lender pays nobody).
- **World boss:** the shared part goes into new tables:
  - `wboss_shared (boss_id primary key, wave, n1..n3, required, wave_started_at, last_clear_secs, hunt_until, hunt_area_id)`;
  - `wboss_shared_clear (boss_id, wave, cleared_at)`.

  M1's per-player `wboss` keeps its per-player columns (`a1..a3`, `hunt_new`), and `wboss_clear` its per-player `notified`. The shared columns of the per-player `wboss` are no longer read; drop them with `alter table drop column`, which needs no rebuild (no FK or index names them). The mapping copies the one player's values into the shared rows. The requirement scaling (docs/server-rules.md: the first wave needs 1,500, (d)) becomes a rule over the number of players (Q5).
- **Tests:** `events/ranking-two-players`, `sphere211/ranking-two-players`, `social/rental-bonus-lender`, `events/worldboss-shared`.

### M7: tools, fixtures, scripts

- `tools/server_state.py --player ID` (default: the first player).
- `tests/diff/diffdrive/state.py` compares per player.
- The session scripts' SQL is scoped by `player_id` (PLAN-schema 1.5's consumer list).
- `tools/make_state_fixture.py --players N`. The replay gains a two-player corpus once docs/multiplayer.md's M1 session exists (`emulator/scripts/multiplay_session.sh`).
- `tools/schema_inventory.py` shows the per-player / shared classification in the inventory.

---

## 6. Non-schema prerequisites (only as far as they shape the schema)

- **Request → player.**
  - soa-server: connection → bridge session → uuid (the bridge POST, the Login / NoLoginStart arguments) → `wire_device` → `player_id`.
  - The relay: no authentication ((b) multiplayer.md 1.7). A relay connection is bound by the PlayerDetailInfo+0x6c id of its EnterRoom, accepted only for a player with a live game session (d). The MissionEnd's uuid is checked against it.
  - The in-process route (`soa`, FakeApiCaller) has no uuid: it serves the first player (d; Q2).
  - `Server::make_ctx` sets `Ctx::player`.
  - **Schema consequence:** the device binding is the only identity table. There is no password or account table, because the client sends none (b).
- **Server-global request state.** `Server::pending[fid]` (core/server.cpp:233; `submit` and `handle` lock separately) and `Server::logged_in` (server.cpp:125/256) are one per server.
  - Two clients sending the same method at once would cross.
  - They become per connection (soa-server) and per session (relay).
  - **No schema consequence**, but M2 can't be exercised by two clients until this is fixed.
- **Concurrency on one SQLite file.**
  - One soa-server process owns the file; the tools open it read-only (`mode=ro`).
  - Every request already runs under `Server::mu` in one transaction (`begin` … `commit`), so writers are serialized. With ≤ 4 players that is enough (d): the relay's 300 ms ticks forward without touching the DB.
  - The relay's MissionStart for N players is N transactions, plus one for the shared co-op rows (M5). No transaction spans players: a refusal for one player doesn't undo the others.
  - Two processes writing one file (soa in-process and soa-server on the same `server.sqlite3`) stays unsupported: documented, not enforced.
  - **Schema consequence:** none (no lock tables, no version columns).
- **The lobby and relay servers** keep rooms in memory (section 1.3). **Schema consequence:** only `coop_battle` / `coop_member` (M5).

---

## 7. If the user picks route A instead

- **Schema of each player's file:** the post-S12 schema, unchanged. No M1. S12 already puts the campaign in the file.
- **New:** `hub.sqlite3`, holding:
  - `player_index (id primary key, search_id unique, file, created_at, last_login_at, support_uid, name, level)`: a profile projection, refreshed by an `OnResponse` hook when `player` / `roster` changed;
  - devices;
  - `follow`, `blacklist`, `recently_played`;
  - `coop_battle` / `coop_member`, `rental_log`;
  - the ranking entries (copies of each player's best with its party) and `sphere_rank_shared`;
  - the world boss's shared rows.
- **Code:**
  - a session→backend map (one `Server` per file, or one `Server` that swaps `ctx.st`);
  - cross-player reads by `ATTACH … ?mode=ro` of the other player's file;
  - the M4–M6 handlers against the hub.

  The allocators stay per file, so uids collide across players, which the client tolerated in run 4 ((b) [run]).
- **Tests:** isolation is structural. The hub needs its own `foreign_key_check` gates. The hub ↔ file consistency (a follow of a missing file) goes through `state::check`.

---

## 8. Order and dependencies

```
PLAN-schema S3 … S12 (+ R12, R17, S11 + R19)        unchanged (the user)
        │
        ▼
 section 6: Ctx player, per-connection pending / logged_in
        │
        ▼
 M1a → M1b → M1c → M1d → M2 → M3 → M4 → M5 → M6 → M7
                          │         │         │
 docs/multiplayer.md:     │         │         └── their M3 (real rewards) needs M-schema 5
 wire, lobby, relay ──────┴─────────┘ their M1–M2 (rooms, battle sync with canned bodies) run in parallel
```

- M1 needs S12 landed: every per-player table exists in its final shape, so it is rebuilt only once more.
- M2 needs M1 (a second player's rows need `player_id`) and section 6's request→player work.
- M3 needs M2: two players can exist, so isolation is testable. **No second real player before M3 passes.** M2's test creates one only in a scratch server.
- The lobby and relay can be built in parallel with M1–M3 (docs/multiplayer.md's M1–M2, with canned bodies). Their M3 (real rewards) needs M-schema 5.
- M4 and M6 are independent of the battle track: a two-player follow / rental / ranking works without co-op.

**Gates:**

- PLAN-schema section 5 per step (G1–G9).
- From M3 on, `server/mp-isolation` and `server/mp-integrity` join the cheap tier (they are scratch-server selftests).
- The default single-player game, the smoke test and the replay corpora stay byte-identical through M2–M3. M1 declares only its added column.
- Multiplayer stays off unless the server is started with it (HANDOFF.md 6).

---

## 9. Open questions for the user

| # | Question | Recommendation |
|---|---|---|
| **Q1** | Route B (one DB, `player_id` everywhere) or route A (one file per player + a shared hub)? | **B** (section 2.4). Its price is M1's second rebuild (section 4) and M3's scoping. If only two-player co-op is wanted and nothing social, A is cheaper. Don't do A first and B later (two data migrations) |
| **Q2** | Which player does the in-process port (`soa --server inproc`, no uuid) serve once a state has several? | The first player (lowest `created_at`), with an optional `--player SEARCH_ID` later. Co-op stays a soa-server feature (docs/multiplayer.md 4(d)) |
| **Q3** | Keep the synthetic rental clones (the player's own roster) once real players exist? | Keep them as a fill-up when fewer than 10 real lenders are available (d), so a lone player still has helpers. Label the mix in docs/server-rules.md |
| **Q4** | Is multiplayer opened per server (`--multiplay`) or per player (a `player` column)? | Per server, off by default (HANDOFF.md 6): no column. `is_open_multiplay` also needs `view_status` bit 4 for the tutorial (b), which the player's own flags already carry |
| **Q5** | The world boss with several local players: keep the single-player wave size (first wave 1,500) or scale it by the number of players? | Scale by the players who contributed in the boss's window, capped at 4 (d). Keep 1,500 per player as the base, so a lone player's game is unchanged |
| **Q6** | `play.coop_battle_id` and `recently_played.battle_id`: declare their FKs (a third rebuild of `play`) or check them in `state::check`? | Check them (no rebuild). `play` is a one-row-per-player scratch table, deleted at MissionEnd |
| **Q7** | Is a player ever deleted (`Debug_DeletePlayer` exists, developer server only)? | No handler deletes players, but the FKs cascade on `player`, so a manual delete or a future handler leaves no orphans. Not served |
| **Q8** | The friend gauge (`CFriendGaugeInfo`, `master_friend_gauge`): implement? | No: `FriendGaugeModel::GetById` has no callers in 3.7.0 (b). The client parses the keys but never shows them |
| **Q9** | Should the follow caps (`follow_max` 300, `follower_max` 20, `block_max` 50) apply locally? | Apply the master's caps (a). The refusal codes are (d) until someone reads the client's follow dialogs for them. A local server with ≤ 4 players never reaches them anyway |
