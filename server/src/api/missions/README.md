# api/missions: the missions

| File | Module | What |
|---|---|---|
| `missions.h` | | the domain's types (`MissionType`, `HelperKind`, `CampaignType`, `DropType`, `Campaign`, `Rolled`) and functions: `find_mission`, `campaigns_for`, the battle-log readers, `lottery` / `roll_drops`, `mission_info`, `start_mission` (also `ext::Ctx::core_mission`'s), `play_state` (core_mission's other methods), the handlers |
| `mission_start.cpp` | `mission_start` (core) | **MissionStart** in twelve named steps over one `MissionStart` state: the arguments and the mission row; the cost (stamina, ticket, vanish item, stamina campaigns, a module's override); the checks (10004, 10206); the surprise roll; the stages; the payment; the party (own party, the tutorial's NPC party, the event mission's NPC helper, a rental clone or an own character as member 4); the play record; the answer and `MissionStartExtra` |
| `mission_end.cpp` | `mission_end` (core) | **MissionEnd** in eleven named steps over one `MissionEnd` state: the play it ends; player and character EXP; battle favor (x type-8 campaigns); the drop roll, granted; the first clear's presents and unlocks; the answer (`drop_list_info`, `clear_present_list_info`) and `MissionResultExtra` |
| `drops.cpp` | | the drop roll of a won mission (`roll_drops`): lots, campaign lots and drops, the character bonus, the surprise enemy, common drops, battle evaluation; `lottery` |
| `campaigns.cpp` | | the `master_campaign` rows running for a mission (on the event calendar) |
| `play_state.cpp` | `play_state` (core) | **GetPlayMission**, **MissionFailed**, **MissionTalk** (one answer, `play_mission_answer`), **MissionRestart / MultiMissionRestart**, **GetMissionList** (data.Time) |

| API | Handler | Rules (docs/server-rules.md) |
|---|---|---|
| MissionStart | `mission_start` (`start_mission`) | "2.2 MissionStart", "Server missions", "Rental helpers", "Tutorial battle" |
| MissionEnd | `mission_end` | "2.3 MissionEnd (win)", "2.4 Drops", "2.5 Battle evaluation", "MissionEnd drops", "Type-8 campaigns" |
| GetPlayMission, MissionFailed, MissionTalk | `get_play_mission`, `mission_failed`, `mission_talk` | "Play state", "2.6 Failure, continue, restart" |
| MissionRestart, MultiMissionRestart | `mission_restart` | "2.6 Failure, continue, restart" |
| GetMissionList | `get_mission_list` | "2.1 Opening missions" (the lists are the campaign's and the events') |

- **Hooks into these answers** (`../../core/modules.cpp` order; `soa-server --list-hooks`): `MissionStartExtra` (the favor drop, the world boss) after MissionStart's answer; `MissionResultExtra` (the event ranking, the tower's lists, the world boss) after MissionEnd's; the story campaign adds `ActiveMissionList` around every answer (`../campaign/`, `server::answer`), the events' `OnResponse` their lists and `CampaignInfo`. Modules start and end the core mission through `ext::Ctx::core_mission` (Sphere 211, the event tests).
- **Grants** go through `../../core/rewards.h` (`grant`); the first-clear presents through the `presents` table (reason `ext::kPresentMissionClear`); battle favor through `../favor/favor.h` (`favor::mission_gain`).
- **Pure rules:** `../../rules/mission_rules.{h,cpp}` (the surprise roll, campaign windows and stamina, evaluation ranks, the character bonus caps; tested by `rules/missions`), `rules::weighted_pick`, `rules::add_exp`.
- **State** (`server.sqlite3`; `../../../PLAN-schema.md` section 1): `play` (the one play in progress: mission, party, start, stamina, the party uids as `"uid,uid,"`), `play_ext` (its mission type, surprise roll, helper and kind, NPC id, campaign lots; kept until the next start), `mission` (play / clear counts, first clear), `unlocks`, `presents`; the rental day's count in `follow_rental` (`../social/rental.cpp`). PLAN-schema S7 makes `play` + `play_member` of `play` / `play_ext`.
- **Log lines scripts read** (`tools/server_log_patterns.txt`): `MissionStart party member`, `MissionStart NPC` (tools/compare_tutorial.py), `MissionStart: rental helper ... as member 4` (rental_session.sh), `MissionEnd mission N: player exp` / `: unlocked` / `drops: surprise` (battle, rental and restore_missions sessions).
- **Tests:** `missions_tests.cpp` (`missions/surprise-campaign-evaluation`, `missions/unlock-refusal`); `../../core/server_tests.cpp` (`server/session-invariants`). **Proof:** the replay corpora `server/tests/replay/missions` (every helper kind, restarts, refusals, campaigns, evaluation, the rental bonus), `seeded`, `tutorial`, `event`. **Sessions:** `port/scripts/battle_session.sh`, `restore_missions.sh`, `campaign_session.sh`, `tutorial_session.sh`, `rental_session.sh`.
