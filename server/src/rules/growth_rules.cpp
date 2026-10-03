// The pure growth / economy / daily rules (rules/growth_rules.h): character growth, item compose
// and sale, stamina heals, the item shop's periods and the login-bonus days. No DB, no request;
// unit-tested in growth_rules_tests.cpp. Their callers: api/growth/growth.cpp, api/items/items.cpp,
// api/shop/shop.cpp, api/daily/login_bonus.cpp. Port code, not guest behaviour; every rule carries
// its source label, (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include "rules/growth_rules.h"

#include <algorithm>
#include <cmath>
#include <ctime>

namespace soa::server::growth_rules {

// ---- character growth (api/growth/)

u32 boost_exp(u32 count, u32 base_boosted_point, bool same_category, double category_rate, bool big_success, double big_rate) {
    // (b) CPartyStrengthening::GetStrengtheningItemReflection: count x base_boosted_point x
    // (pc_boosted_role_category_bonus_rate when the item's role_category_type is the role's
    // category_type), truncated. (d) a big success multiplies the result by
    // pc_boosted_bonus_rate, truncated again.
    double e = std::floor((double)count * (double)base_boosted_point * (same_category ? category_rate : 1.0));
    if (big_success) e = std::floor(e * big_rate);
    return (u32)std::min(e, 4294967295.0);
}

u32 stat_seed_gain(u32 current, u32 per_seed, u32 count, u32 add_max) {
    // (b) CPartyStrengthening::GetParameterAddItemReflection: current + value x count, capped at
    // the role's <stat>_add_max
    u64 v = (u64)current + (u64)per_seed * count;
    return (u32)std::min<u64>(v, add_max);
}

// ---- items and stamina (api/items/)

u32 compose_points(u32 material_points, u32 rarity_boosted_point) {
    // (b) CItemStrengtheningPotal::GetAddBoostedPoint (as far as read)
    return (u32)(((u64)material_points + 100) * rarity_boosted_point / 100);
}
u32 item_level(u32 points, u32 next, u32 cap) {
    // (a) next_level_boosted_point per level; (d) the same amount for every level (cumulative)
    if (!next) return 1;
    return (u32)std::min<u64>(cap ? cap : 1, 1 + (u64)points / next);
}
u32 sell_price(u32 sale_fol, double sale_rate) {
    // (b) CParameterUtility::tItemData::SellingPrice
    return (u32)std::lround((double)sale_fol * sale_rate);
}
u32 heal_points(int heal_type, u32 heal_point, u32 stamina_max) {
    // (b) StaminaUtility::StaminaHealPoint(type, item)
    if (heal_type == 1) return (u32)((u64)heal_point * stamina_max / 100);
    if (heal_type == 2 || heal_type == 3) return heal_point;
    return 0;
}

// ---- the item shop (api/shop/)

int64_t shop_period_start(int64_t t, int reset_type, int param, int time_of_day) {
    // (a) reset_type 2 rows (reset_param 1, reset_time 00:00:00, loop_count = the months to
    // closed_at): a monthly reset on day `param` at `time_of_day`
    if (reset_type != 2) return 0;
    time_t tt = (time_t)t;
    struct tm tm;
    localtime_r(&tt, &tm);
    struct tm s = tm;
    s.tm_mday = std::max(1, param);
    s.tm_hour = time_of_day / 3600;
    s.tm_min = time_of_day / 60 % 60;
    s.tm_sec = time_of_day % 60;
    s.tm_isdst = -1;
    int64_t start = (int64_t)mktime(&s);
    if (start > t) {
        s = tm;
        s.tm_mon -= 1;
        s.tm_mday = std::max(1, param);
        s.tm_hour = time_of_day / 3600;
        s.tm_min = time_of_day / 60 % 60;
        s.tm_sec = time_of_day % 60;
        s.tm_isdst = -1;
        start = (int64_t)mktime(&s);
    }
    return start;
}

// ---- the login bonus (api/daily/)

u32 next_login_day(u32 cur, u32 last, bool loop) {
    // (a) is_loop and order_idx; (c) one step per login day
    if (!last) return 0;
    if (cur < last) return cur + 1;
    return loop ? 1 : 0;
}

}  // namespace soa::server::growth_rules
