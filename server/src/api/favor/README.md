# api/favor: favorability (好感度)

| File | Module | What |
|---|---|---|
| `favor.{h,cpp}` | | the favor rules: levels and points (`favor::rules`), the player-load keys (`add_player_state`), the battle gain (`mission_gain`), the tap (`tap`), favor items (`use_item`), the event drop bonus's daily use. Called by the schema (`../../core/server.cpp`), the player load and the battle status (`../player/player_info.cpp`), MissionEnd (`../missions/mission_end.cpp`), the favor login bonus (`../daily/`), the favor drops (`../events/favor_drop.cpp`) and the APIs below |
| `favor_api.cpp` | `favor` (core) | **UpdateFavorByTap**, **UseFavorItem** on the player state, with the favor achievements (`ext::achievement_state`) |

The core's APIs register with `ext::add_core_api`, before the modules. `favor.cpp` reads and writes through a small SQLite wrapper of its own on raw handles (its callers pass `sqlite3*`); PLAN-schema S1 replaces it with the one SQL wrapper.

**State**: `favor` (one row per same_role_id: point, tap_count, tapped_at, event_drop_at; `favor::schema`, created with the core's tables).

**Rules**: docs/server-rules.md "8. Favor" (State, Levels, Gains, Responses), "Favor achievements", "Type-8 campaigns", "Event extras" (the event drop bonus).

**Tests**: `favor_tests.cpp` (`favor/favor-rules`, `favor/friendship-campaign`); `../daily/daily_tests.cpp` (the favor login bonus), `../presents/achievements_tests.cpp` (type-52 achievements), `../events/event_extras_tests.cpp` `events/favor-drop`. **Session**: `port/scripts/restore_favor_session.sh` (two taps, level 1 -> 2, battle favor; reads the `favor: tap same_role` and `favor: mission (stamina` log lines).
