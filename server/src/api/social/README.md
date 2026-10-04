# api/social: follows, rental helpers and the follow menu

| File | Module | What |
|---|---|---|
| `rental.{h,cpp}` | `follow` | **FollowList** (`follow_list`), **UpdateSupport** (`update_support`, `UpdateSupportArgs`), the synthetic rental list (`rental::follow_map`: CFollowInfo {order, `follow_player_info`, `follow_person_info`}; `BattleRental` on every full player state, `OnPlayerLoad` `load_follow`), rental ids (`rental.h`: roster uid with bit 40), the rental bonus (`rental_bonus`, paid on the player load; table `follow_rental`, counted by MissionStart), GetPlayerDetailInfo's own entry (`rental::own_follow_entry`, `../events/ranking.cpp`). Sphere 211 lends the same list. Rules: docs/server-rules.md#rental-helpers. Log line read by `rental_session.sh`: `rental bonus: N rentals on day`. Session: `port/scripts/rental_session.sh` |
| `social.cpp` | `social` | the follow menu's lists on a server without other players: Blacklist and GetRecentlyPlayedList answer the player state (empty lists), SearchPlayer is refused with 10002 (`kPlayerNotFound`). Rules: docs/server-rules.md#home (Follow menu). Session: `port/scripts/home_session.sh` (the side menu) |

Tests: `rental_tests.cpp` (`social/follow-rental`, `social/follow-support`); the replay corpus `server/tests/replay/missions` (the rental list, the rental bonus over three days, FollowList, UpdateSupport); the follow-menu APIs are in the replay's `api-sweep` corpus. No tables of their own besides rental's (state/README.md once PLAN-schema S1 lands).
