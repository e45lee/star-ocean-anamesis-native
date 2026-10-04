# api/entry: login, new player, tutorial

The APIs the 3.7.0 login and tutorial code (`CPhase_Login`, `CTutorialManager`) sends; the client runs that code unchanged. Public header: `entry.h` (`create_player` for the tests, the Login answer's CDN keys, `time_only`).

| API | Handler (`entry.cpp`) | Answers |
|---|---|---|
| `Login`, `SimpleLogin` | `login` | the whole player state with the CDN keys (`../player/player_info.h` `full_player_state`); without a player error 19001 (`kNoPlayer`): the client's new-player flow |
| `CreatePlayer` | `create_player` (steps `insert_new_player`, `add_starters`) | the new player (level 1, the `Default_Character_1..3` starters in party 1), the whole player state with `a_ver` only |
| `UpdateTutorial` | `update_tutorial` | stores `tutorial_status`; the player state |
| `UpdateView` | `update_view` | stores the UI tutorials' seen bits (`view_status`, `view_status2`); the player state |
| `UpdateKiyakuVersion` | `update_kiyaku_version` | stores the terms version; the player state and `MasterKiyakuVersion` |
| `UpdatePlayerName` | `update_player_name` | stores the name; the player state |
| `GetServerTime` | `get_server_time` | `data.Time` only (`time_only`, also GetMissionList's and a playerless GetPlayer's answer) |

- **Module** `entry` (core): registered with `ext::add_core_api`, first in `src/core/modules.cpp` (the core's APIs register before the modules and don't create the modules' tables; ARCHITECTURE.md "The module registry and its order"). No hooks of its own; the player state it answers carries every `OnPlayerLoad` hook's keys (API-INDEX.md section 2).
- **Login's CDN keys** (`add_cdn_paths`: AssetPath, MasterPath, r_ver, LatestEpisodeVersion, a_ver): soa-server's CDN only; soa in-process sends none.
- **State**: the `player` row (with `tutorial_status`, `view_status`, `view_status2`, `kiyaku_version`: `meta` keys until PLAN-schema S3), the starters' `roster` and `party` rows, the new player's default titles (`titles`, `player.title_id`: `../player/titles.cpp` `new_player_titles`), and the `meta` keys `next_char_uid`, `next_item_uid`.
- **Rules**: docs/server-rules.md#entry (Session and login, New player, Tutorial progress, Terms and name), "Player load", "UI tutorial flags".
- **Tests**: `entry_tests.cpp` (`entry/start-coins`); the replay corpora `tutorial` (the new-player flow) and `api-sweep`.
- **Sessions**: `port/scripts/tutorial_session.sh`, `newplayer_session.sh`; tests/diff's tutorial flow; `emulator/scripts/emulator_session.sh --new-player`.
