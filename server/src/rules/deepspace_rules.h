#pragma once
// Pure rule functions of deep space (called by api/deepspace/), defined in deepspace_rules.cpp and
// unit-tested in deepspace_rules_tests.cpp (rules/deepspace). Labels as in server.h: (a) master
// data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include <cstdint>

namespace soa::server::rules::deepspace {
using u32 = uint32_t;

// The value of one bonus for a party (b: CDeepSpace::UpdateDeepSpaceMissionBonusList). `count` is
// the number of party members meeting the bonus conditions, or for condition2 = 5 (`battle_power`)
// the sum of their battle power. Below `count_min` the bonus stays at its minimum effect
// `effect_min` (x1.0 in the data); from `count_min` it rises linearly to `effect_max` at
// `count_max`, in steps of one member ((count_max - count_min) / 19 for battle power), rounded down
// to one decimal.
float bonus_value(u32 count, float count_min, float count_max, float effect_min, float effect_max, bool battle_power);

// Quick return (b: CDeepSpaceQuickReturnDialog::Update): the remaining time in whole hours
// (rounded up) x the master_deep_space_time_saving rate of this use gives the quick-return items
// needed; what the owned items don't cover costs kQuickReturnCoinsPerItem coins per item.
constexpr u32 kQuickReturnCoinsPerItem = 10;  // (b) the dialog's price
struct QuickCost {
    u32 items = 0, coins = 0;
};
QuickCost quick_return_cost(int64_t remain_sec, float rate, u32 owned_items);

// Play limits (master_deep_space_mission.limit_type / limit_count; every row leaves them empty
// in the 3.7.0 data, so the rule is generic): (d) limit_type 1 = per day, 2 = per week, with
// limit_count plays in that period; 0 / empty / other types = no limit. The client shows no
// limit (no limit text among its deep space strings) (b).
enum class LimitType : int { kNone = 0, kDaily = 1, kWeekly = 2 };
bool limit_reached(int limit_type, u32 limit_count, u32 daily, u32 weekly);
// (d) the week of the weekly limit starts on Monday at the daily reset hour (04:00,
// master_global login_bonus_reset_hour, as the other daily counters); `day` is the start of t's
// day (day_start, core/time.h).
int64_t week_start(int64_t day);

}  // namespace soa::server::rules::deepspace
