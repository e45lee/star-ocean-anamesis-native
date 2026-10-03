# api/deepspace: deep space expeditions

The expedition mode ("ディープスペース探査", `CPhase_DeepSpace` = phase 6). The client code is unchanged from 3.7.0; the module (`deepspace`) answers its five APIs.

| File | What |
|---|---|
| `deepspace.cpp` | the five handlers, each with its doc block (signature, fid, rules with their labels, refusal codes, answer), MissionStart's and MissionEnd's named steps (`find_offer`, `party_refusal`, `free_ship`, `take_bonus_item`, `set_ship_bonuses`; `load_ship`, `pay_quick_return`, `grant_player`, `grant_character_exp`, `grant_drops`, `renew_offer`, `roll_rare_offer`), `register_deepspace()` |
| `deepspace.h` | what the module's files share (namespace `deepspace`, internal) |
| `deepspace_args.h` | the request arguments by name (`args::DeepSpaceMissionStartArgs`, ...) |
| `state.cpp` | the two clocks, the areas (`area_unlocked`, `area_assets`), the offers (`refresh_offers`, `roll_bonus_set`, the play-limit periods), the ships (`max_ships`: limit-break and pass ships), the day's quick returns, and the answer values named after the client classes (`area_info` CDeepSpaceAreaInfo, `ship_info` CDeepSpaceShipInfo, `deep_mission_player`, ...) |
| `bonuses.cpp` | the party's bonus conditions (`member`, `applies`: `CDeepSpace::tBonusInfo::IsApplyCharacter`) and values (`party_bonuses`), the free characters |
| `rewards.cpp` | MissionEnd's drops and the bonus effects on them (`roll_rewards`) |
| `deepspace_tests.cpp` | `deepspace/expedition` (offer, departure, refusals, rewards, quick return, an area opening), `deepspace/extras` (pass ships, play limits, achievements types 44 / 45) |

| API | Handler | Rules (docs/server-rules.md) |
|---|---|---|
| DeepSpaceActiveList | `deep_space_active_list` | "Deep space" |
| DeepSpaceAutoMemberSelect | `deep_space_auto_member_select` | "Deep space" |
| DeepSpaceMissionStart | `deep_space_mission_start` | "Deep space" |
| DeepSpaceMissionEnd | `deep_space_mission_end` | "Deep space" |
| DeepSpaceMissionEndNow | `deep_space_mission_end_now` | "Deep space" |

- **Hooks:** none; the module registers its tables and its APIs (`register_deepspace`, in `core/modules.cpp`'s order). Other modules read its state: the achievements (`../presents/achievements.cpp`: `ds_area` for type 44, `ds_log` for type 45), the player load (`Player.time_saving_use_count` from `meta`, `../player/player_info.cpp`); the pass state it reads is `../shop/subscription.cpp`'s.
- **Pure rules:** `../../rules/deepspace_rules.{h,cpp}` (`rules::deepspace`: `bonus_value`, `quick_return_cost`, `limit_reached`, `week_start`; tested by `rules/deepspace`).
- **The area images** (`area_assets`, state.cpp): an area is offered only when its `Image/etc2/<resource>.aif` is in the host's `AssetIndex`, on a live server only. It is **not** the one asset gate of `../../core/assets.h` (decided in R18, `server/PLAN-readability.md` R6g): the gate also accepts the texture-quality and `assetpack/` variants, follows the tests' override and passes everything without an asset source, while the module's unit tests run non-live with every area present. On the 3.7.0 data the two predicates agree (the 13 area images are only at `Image/etc2/`, in the download).
- **State** (`server.sqlite3`; the tables are `../../state/schema.cpp`'s, PLAN-schema S1; their keys and FKs are S10's): `ds_area` (exploration exp, is_new, last play), `ds_offer` (the areas' offers with their play counts), `ds_ship` (ships out or back; members as a "uid,uid,..." text), `ds_bonus` (a ship's bonus values), `ds_log` (every departure); `player.time_saving_day` / `time_saving_count` (the day's quick returns), `ds_state` (`limit_day` / `limit_week`: the play-limit periods; `meta` keys until PLAN-schema S3).
- **Clocks:** expedition timers on the server clock, master rows only the server reads on the event calendar, areas and missions on both (deepspace.h).
- **Proof and sessions:** the replay corpus `server/tests/replay/deepspace` (every API, accepted and refused, quick returns, a rare offer); `port/scripts/deepspace_session.sh` (runs with `--galaxy-pass`: two expeditions out at once, the second on a pass ship; the 実績 screen and 一括達成; it reads the "DeepSpaceActiveList: ... (2 by the pass)" line).
