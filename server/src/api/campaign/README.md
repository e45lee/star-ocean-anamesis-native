# api/campaign: the story campaign

Public header `soaserver/api_campaign.h` (`campaign::enabled`, `on_request`, `on_response`, `end_mission_talk`, `active_mission_list_msgpack`); internal header `campaign.h`.

| File | What |
|---|---|
| `campaign.cpp` | the hooks around each request, called by `server::answer` (`core/lifecycle.cpp`) for both hosts, not by the dispatcher: `on_request` (the progress a MissionStart / MissionEnd / MissionTalk / GetWorldMapInfoList implies), `end_mission_talk` (a story scene's end), `on_response` (`campaign_keys`: Player, ActiveWorldMapMissionList, ActiveMissionList spliced into the body); the splice on `Value` (`decode_body`, `splice_data`, `merge_maps`: a body that doesn't encode back to the same bytes is left alone) |
| `master_data.cpp` | the campaign's master tables, read once by its own SQLite handle (`open_master`: SOA_MASTER_DB, else the 3.7.0 DB, else the offline build's): `load_missions`, `load_areas_and_planets`, `load_stages`, `load_world_map` |
| `progress.cpp` | the player's progress (`State`: cleared missions, the last play, the episode asked for) in `<data>/server_campaign.txt`, outside the state DB; `SOA_CAMPAIGN_SEED` (`seed_progress`); `clear_mission` |
| `lists.cpp` | what is listed: `available` (Episode 1: the unlock chain, the story areas, the windows; the world map: `world_map_available`, `group_open`, `episode_progress`), `build_active_mission_list` (ActiveMissionList), `build_world_map_list` (ActiveWorldMapMissionList), `build_player` (Player.world_map_progress*, a seeded player's view_status*); `in_window` (a string compare: a variant of `core/time.h` `open_at`, kept apart) |
| `campaign_tests.cpp` | `campaign/unlock-chain` (the Episode 1 chain against the master data), `campaign/splice` (the splice's order and refusal rules on bytes) |

**Not a module:** no `register_*`, no `Api`; the campaign is called around each request, and its keys come after every hook's. **State:** the text file above (PLAN-schema S12 folds it into the state DB; `server/PLAN-readability.md` section 6).

**Rules**: docs/server-rules.md "Campaign progression". **Proof and sessions**: every replay corpus (the campaign runs on every request; `seeded` with `--campaign-seed mf01_001`, the `tutorial`'s scenes); `port/scripts/campaign_session.sh`, `restore_missions.sh`.
