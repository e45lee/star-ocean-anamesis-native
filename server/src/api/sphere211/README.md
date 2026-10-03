# api/sphere211: Sphere 211

The extra dungeon of 3.7.0 ("スフィア211", `CPhase_Mission` with mission type 5, the `CSphere*` screens). The client code is unchanged from 3.7.0; the module (`sphere211`) answers its 13 APIs, whose battles are `master_event_mission` rows played through the core MissionStart / MissionEnd (`ext::Ctx::core_mission` with an `ext::MissionOverride`).

| File | What |
|---|---|
| `sphere211.cpp` | the 13 handlers, each with its doc block (signature, fid, rules with their labels, refusal codes, answer), the player-load hook (`load_sphere211`), the tables (`kSchemaSphere`, `kSchemaSphereExtra`), `register_sphere211()` |
| `sphere211.h` | what other modules and the tests reach: `pick_season`, the asset override (`set_asset_check`, `mission_playable`), the achievements of types 61 / 62 (`api/presents/achievements.cpp` asks) |
| `dive.h` | what the module's files share (namespace `sphere211`, internal) |
| `sphere211_args.h` | the request arguments by name (`args::Sphere211MissionStartArgs`, ...) |
| `season.cpp` | the seasons (`pick_season`: the event calendar, the gaps, the repeated last season and its cycles), the client master's moved dates (`client_seasons`, `ClientMaster`), the dive's load and season change (`load_dive`), the achievements' moved windows |
| `floors.cpp` | the floors (`floor_row`), the playable missions (`mission_playable`, on the one asset gate `core/assets.h`), the cell lottery (`enter_floor`, `lot_mission`), the warp access (`lot_floor_num`), the request's cell (`find_cell`), the sphere stamina |
| `rewards.cpp` | the treasure boxes: gathered (`add_boxes`), ranked (`lot_ranks`), opened (`open_boxes`); item sets (`grant_content`) |
| `ranking.cpp` | the season ranking: the reward groups (`ranking_group_of`, `client_ranking_groups`, `ClientMaster`), the reward (`ranking_reward`), the local ranking map |
| `rental.cpp` | the rental slot (`put_rental`, `rental_available`, `record_rental`) and the Sphere 211 rental bonus (`rental_bonus`) |
| `state.cpp` | the dive state every answer carries (`put_state`: floor, cells and `can_play`, stamina, boxes, departed characters, the season-end result, the rental slot, `Achievement`), `sphere_meta`, the log, the RNG |
| `sphere211_tests.cpp` | `sphere211/season`, `/lottery`, `/stamina`, `/dive`, `/rental`, `/achievements`, `/items` |

| API | Handler |
|---|---|
| GetSphere211Info | `get_sphere211_info` |
| Sphere211SelectedFloor | `sphere211_selected_floor` |
| Sphere211MissionStart | `sphere211_mission_start` (+ `own_party`, `enemy_level`) |
| Sphere211MissionEnd | `sphere211_mission_end` |
| Sphere211MissionFailed | `sphere211_mission_failed` |
| Sphere211MissionContinue | `sphere211_mission_continue` |
| Sphere211FloorClear | `sphere211_floor_clear` |
| Sphere211UseRerollItem | `sphere211_use_reroll_item` |
| Sphere211StaminaHeal | `sphere211_stamina_heal` |
| ReturnSphere211 | `return_sphere211` |
| GetSphere211RankingInfo | `get_sphere211_ranking_info` |
| Sphere211AutoMemberSelect | `sphere211_auto_member_select` |
| Sphere211EquipAuto | `sphere211_equip_auto` |

Rules: docs/server-rules.md "Sphere 211" (every API).

- **Hooks and their order** (`../../core/modules.cpp`; `soa-server --list-hooks`): two `ClientMaster` overrides (`client_seasons`, `client_ranking_groups`: the served master's season dates and the last season's ranking group) and one `OnPlayerLoad` (`load_sphere211`: `FooterMissionInfo.is_open_extra_dungeon`, `Sphere211CurrentId`, the rental bonus), in `register_sphere211()`'s order.
- **State** (`server.sqlite3`; PLAN-schema S10): `sphere` (one row: season, floor, map template, streak, gathered-box total, sphere stamina, the floor-clear info, the previous season's result; `revive_count`: below), `sphere_cell` (the current floor's cells), `sphere_departed` (uids out until 帰還), `sphere_box` (unopened boxes), `sphere_rank` (best floor per season), `sphere_meta` (keyed values: `cycle`, `season_wins`, `end_pending`, the port's test hook `test_enemy_level`), `sphere_rental` (the floor's lenders that lent), `sphere_rental_day` (rentals per rental day), `sphere_log` (battles won and floors entered, for the achievements).
- **`sphere.revive_count`** (found in R18, a rules gap, not changed): the client's `Player.sphere211_revive_count` counts the sorties with an EX character (role rank 5) since the last 帰還, and the sally dialog shows `master_global.max_revive_count` (3) minus it ("使用可能回数 残り %d 回"); the text also says an EX character's companions don't become 出撃済み on a clear while the EX character does. The server neither counts these sorties nor applies that departed rule, so the dialog always says 3 left (state.cpp `put_state`; `server/PLAN-schema.md` F1).
- **Clocks:** the season on the event calendar, moved to the client's clock (season.cpp); the sphere stamina, the rental days and the achievement log on the server clock.
- **Proof and sessions:** the replay corpus `server/tests/replay/sphere211` (a dive on floor 1: every API, refusals, a season change; the playable missions follow `--download-dir`); `port/scripts/sphere211_session.sh` (the dive, the rental, the heal ticket, the reroll; it reads the "Sphere211: floor 1 (floor row N), map M" and "Sphere211MissionEnd: ... streak 4" lines) and `sphere211_continue_session.sh` (a lost battle continued and retired; "Sphere211MissionContinue: 100 coins", "Sphere211MissionFailed: streak reset", "Sphere211StaminaHeal: sphere stamina 8 -> 9", "Sphere211 rental bonus: 5 rentals").
