// The pure deep space rules (rules/deepspace_rules.h): the bonus curve, the quick-return price,
// the play limits and their week. No DB, no request; unit-tested in deepspace_rules_tests.cpp.
// Their caller: api/deepspace/. Port code, not guest behaviour; every rule carries its source
// label, (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include "rules/deepspace_rules.h"

#include <cmath>
#include <ctime>

#include <soa/local_time.h>

namespace soa::server::rules::deepspace {

float bonus_value(u32 count, float count_min, float count_max, float effect_min, float effect_max, bool battle_power) {
    float value = effect_min;
    if (count_min <= (float)count) {
        float step = battle_power ? (count_max - count_min) / 19.0f : 1.0f;
        float span = (count_max - count_min) + step;
        float fraction = 1.0f;
        if (span != 0.0f) {
            float f = (((float)count - count_min) + step) / span;
            fraction = f < 0.0f ? 0.0f : std::fmin(f, 1.0f);
        }
        value = (float)(int)((effect_min + (effect_max - effect_min) * fraction) * 10.0f) * 0.1f;
    }
    return value;
}

QuickCost quick_return_cost(int64_t remain_sec, float rate, u32 owned_items) {
    QuickCost cost;
    uint64_t hours = remain_sec > 0 ? (uint64_t)(remain_sec / 3600 + (remain_sec % 3600 ? 1 : 0)) : 0;
    u32 need = (u32)(rate * (float)hours);
    if (need <= owned_items) {
        cost.items = need;
    } else {
        cost.items = owned_items;
        cost.coins = (need - owned_items) * kQuickReturnCoinsPerItem;
    }
    return cost;
}

bool limit_reached(int limit_type, u32 limit_count, u32 daily, u32 weekly) {
    if (!limit_count) return false;
    if (limit_type == (int)LimitType::kDaily) return daily >= limit_count;
    if (limit_type == (int)LimitType::kWeekly) return weekly >= limit_count;
    return false;
}

int64_t week_start(int64_t day) {
    time_t tt = (time_t)day;
    struct tm tm;
    localtime_r(&tt, &tm);
    int back = (tm.tm_wday + 6) % 7;  // days since Monday
    tm.tm_mday -= back;
    return soa::mktime_local(&tm);
}

}  // namespace soa::server::rules::deepspace
