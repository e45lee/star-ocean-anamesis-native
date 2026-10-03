# server-rules.md: the 3.8.0 port's notes (history)

Text moved out of `docs/server-rules.md` on 2026-10-01 (agent no380-docs), when the port had moved to the 3.7.0 client (tag `pre-rebase-370` is the 3.8.0 port). It describes the offline 3.8.0 client the port ran before the rebase and the workarounds the local server or the port needed for it. The current rules are in `docs/server-rules.md`; the library differences are in `libsoa-3.7.0-vs-3.8.0.md`.

## Conventions: the client's clock

  - `NowTime()` returns `master_global.service_stop_day` when that key exists (2021/06/24 14:30:00 in both the 3.7.0 and 3.8.0 DBs), else `BAS::LocalTime()` corrected by the server-time offset (`CServerTime::FixTime`). This is the 3.8.0 build's frozen clock (docs/notes.md "3.7.0 vs 3.8.0", from `verdiff`: 3.7.0's code ignored the key). So in 3.8.0 every client-side time computation (stamina regeneration, remaining times, gacha / event / shop windows) runs at 2021-06-24 14:30, and stamina never regenerates on screen.
  - **Server-side fix, no client change:** serve the client a master DB without the `service_stop_day` row under `--restore` (a data change), and `NowTime()` falls back to local time plus the server offset. (Check the other readers of `service_stop_day` first.)

On 3.7.0 `NowTime` is `CServerTime::FixTime(BAS::LocalTime())` and never reads the row; the served master drops it anyway (the service-end check).

## Server program: the client's frozen clock

- **The client's frozen clock.** The 3.8.0 client's `NowTime` returns `master_global.service_stop_day` while that row exists (see Conventions above).
  - Under `--restore` the server drops the row from the client's in-memory master copy: a data override, no code change. The hook is in the native `lib_sqlite` (`sqlite3_exec` / `sqlite3_prepare_v2`), at the copy's `DETACH` (`server::after_client_master_sql`); it logs `dropped master_global.service_stop_day`.
  - With the row gone, `NowTime` takes 3.8.0's own live path: the device clock plus the `data.Time` offset.
  - **Other readers of the row:** `CTimeUtility::NowTime` and `BAS::LocalTime` (per `verdiff`). The ~30 time helpers go through `NowTime`.

`after_client_master_sql` (the `lib_sqlite` hook) has no caller in the 3.7.0 port; both server modes serve the edited master from the CDN (`apply_client_master`).

## Notes for the server-core implementation

- **The frozen client clock** (conventions): the 3.8.0 client computes stamina and time windows at `service_stop_day`; dropping that `master_global` row from the served DB and sending `data.Time` unfreezes it without touching client code.

## Favor (section 8)

The client shows real levels only with the restored 3.7.0 favor getters (`docs/client-changes.md`, "Favorability"); 3.8.0 reports level 4 for every character with a favor schedule, whatever the server sends.

## Home character (`UpdateHome`)

- **`Player.home_pc_id` is sent as the home character's master role id**, not its uid. The 3.8.0 home (`CHome::GetAdjutant`) reads CParameterManager+0xd08 as a role id: 3.8.0's own `CAdjutantSelect` stored `tCharaData::MasterRollId` there. With a uid there, the home fell back to the default character right after `UpdateHome`. **(b)** The online server sent the uid, which 3.7.0's home code read.

The rule (`home_pc_id` as a role id) is still applied by `server/src/server.cpp`; on 3.7.0 the home reads a uid (`docs/server-rules.md` "Home character").

## Battle status from the client's own computation (`port/src/native/api/server_client_status.cpp`)
| Rule | Label |
|---|---|
| In the game, each party member's `CPersonStatusInfo` stats (hp, attack, intelligence, defence, hit, guard, ap, def_*) are what the client's status screen computes: the server builds a `tCharaData` for the character (`Initialize(uid, true, 0, false)`, as `CDetailDialog_CharaStates::Start` does) and runs `CalcStatus(&status, true)`, i.e. `PersonModel::CalculateParameter` over the client's CPersonInfo: base × rank, seeds (add_*), weapon and accessory at their level (`ItemModel::GetDetail`), their factors and attached gear (`AddItemFacter` / `AddGearFacter`), the role's talents (`MasterTalentModel`), the factor stat effects (`MasterFactorModel::GetParameter`), awakening, the favor AP bonus. The battle then uses the numbers the player saw. | (b) |
| For that the client must hold the same state: the `Character` list now carries `add_hp` .. `add_ap` (the seeds, CPersonInfo fields) and `Item` the attached gear. | (b) |
| Outside the game (unit tests) the server's own formula applies, now with the seeds added to the stats and reported in `add_*`. Factors and talents are only in the in-game path. | (b); fallback (d) |
| Since the server became a library (`server/`, 2026-10-01) the in-game path is the port's `StatusProvider` (`soaserver/hooks.h`, installed by soa). Without one (`soa-server`, no client to ask) the server's own formula applies, as in the unit tests: the behaviour before this rule (`enabled_client_status` effectively off). Mission NPCs are the exception: their model is computed from the master data in both (`rules::npc_status`, "Tutorial battle"; agent t1-tutorial-parity), equal to the client's for every row. | (d); NPCs (b) |
| **Since the rebase's revision 2 (2026-10-01, `port/rebase-370`) soa installs no `StatusProvider` either** (`server_client_status.cpp` was deleted with the natives, and H removed the interface from `soaserver/hooks.h`): in-process the server's own formula applies, exactly as in `soa-server`, so the two server modes and `soa-emu` see the same party statuses (the `tests/diff/` flows). The in-game rows of this section, and the "(b) in the game" NPC replacements of "Tutorial battle" and "Event NPC helpers", describe the 3.8.0 port and are history; mission NPCs come from `rules::npc_status` in both modes. Its last check against the 3.7.0 client model (selftest `server/npc-status-master`, removed with the provider) differed in one row: `master_mission_npc` 409829631 HP 5158 (server) vs 4728 (client); to re-check when the status natives are rebuilt. | (d) |
| Mission NPCs (the tutorial battle's party, `master_mission_npc`) aren't held by the client, so `tCharaData::Initialize` fails for them; their stats and weapon come from the client's NPC model instead: `MasterMissionNpcModel::CalculateParameter(master_mission_npc id)`, what `tCharaData::CalcStatus` runs for an NPC `tCharaData` (see "Tutorial battle"). The server first checks the row with `CParameterUtility::FindMissionNpcWithId`, because the model dereferences it unchecked. Test `server/tutorial-npc-status`. | (b) |
