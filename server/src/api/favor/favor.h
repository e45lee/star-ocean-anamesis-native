#pragma once
// The favorability (bond, 好感度) rules (api/favor/favor.cpp). Port code, not guest behaviour.
// Called from: the player load and the battle status
// (api/player/player_info.cpp), MissionEnd (api/missions/mission_end.cpp), the favor APIs
// (api/favor/favor_api.cpp), and the favor login bonus and event drops (api/daily/,
// api/events/favor_drop.cpp). Every rule carries its source label, also listed in
// docs/server-rules.md "8. Favor":
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// State: table `favor` in the server DB (state/schema.cpp), one row per same_role_id (the client keys its favor map,
// CParameterManager +0x8410 map<u64, CPlayerCharacterFavorInfoElement>, by same_role_id (b)).
#include <cstdint>
#include <string>
#include <vector>

#include "soaserver/ids.h"
#include "soaserver/msgpack.h"
#include "soaserver/server.h"

struct sqlite3;

namespace soa::server::favor {

// Adds the player-load keys: `PlayerCharacterFavorMap` (every owned character's same_role_id with a
// master_favor_schedule row), `RemainingUpdateFavorCountByTap` and
// `RemainingEventDropBonusCountByFavor`.
void add_player_state(sqlite3* st, sqlite3* m, int64_t now, SameRoleId home_same_role_id, Value& data);

// The favor level of `same_role_id` as the server holds it (1 when it has no favor).
u32 level_of(sqlite3* st, sqlite3* m, int64_t now, SameRoleId same_role_id);

// MissionEnd: adds the battle favor for a mission that cost `stamina` to `same_role_id` and
// returns its `MissionResultCharacterFavor` element (CMissionResultCharacterFavorInfo). Nil when
// the character has no favor schedule.
// `rate` multiplies the gain (a type-8 friendship campaign, docs/server-rules.md "Type-8 campaigns").
Value mission_gain(sqlite3* st, sqlite3* m, int64_t now, SameRoleId same_role_id, u32 stamina, double rate = 1.0);

// UpdateFavorByTap's rule: (a) master_global favor_tap_bonus_point (50) points, at most
// favor_tap_bonus_limit (5) taps per character per favor day. Adds UpdateFavorByTapResultInfo
// {same_role_id, favor_level, favor_point, RemainingUpdateFavorCountByTap} to `data`.
void tap(sqlite3* st, sqlite3* m, int64_t now, SameRoleId same_role_id, Value& data);

// UseFavorItem's rule: `count` (capped by the stack held, which is debited) of master item
// `master_item_id` on `same_role_id`, (a) master_favor_item_effect.favor_up_point each. Adds
// UseFavorResultInfo {same_role_id, favor_level, favor_point} to `data`.
void use_item(sqlite3* st, sqlite3* m, int64_t now, u32 master_item_id, u32 count, SameRoleId same_role_id, Value& data);

// The favor event drop bonus (docs/server-rules.md "Event extras"): whether a character's bonus is
// spent for the favor day, today's remaining uses (RemainingEventDropBonusCountByFavor), and
// spending one (stores now as event_drop_at; returns it formatted as added_event_drop_at).
bool event_drop_used_today(sqlite3* st, sqlite3* m, int64_t now, SameRoleId same_role_id);
u32 event_drop_remaining(sqlite3* st, sqlite3* m, int64_t now);
std::string mark_event_drop(sqlite3* st, SameRoleId same_role_id, int64_t now);

// ---- pure rules (unit-tested: api/favor/favor_tests.cpp) ------------------------------------
namespace rules {
// (a)+(b) master_favor_level.next_favor_point is cumulative: level L lasts while
// next[L-1] <= points < next[L] (CHome::GetFavorabilityPointPersent draws the gauge as
// (points - next[L-1]) / (next[L] - next[L-1])). `next[i]` = next_favor_point of level i+1.
u32 level(u32 points, const std::vector<u32>& next, u32 max_level);
// (d) points stop at the threshold of the maximum level (next_favor_point of max_level - 1).
u32 cap_points(u32 points, const std::vector<u32>& next, u32 max_level);
// (d)+(a) the favor day starts at master_global.login_bonus_reset_hour (4): the day index of `t`.
int64_t favor_day(int64_t t, int reset_hour);
}  // namespace rules

}  // namespace soa::server::favor
