#pragma once
// Pure rule functions of the growth / economy / daily modules (called by api/growth/growth.cpp,
// api/items/items.cpp, api/shop/shop.cpp, api/daily/login_bonus.cpp), defined in growth_rules.cpp and
// unit-tested in growth_rules_tests.cpp. Labels as in server.h.
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace soa::server::growth_rules {
using u32 = uint32_t;
using u64 = uint64_t;

// EXP from `count` EXP items of `base_boosted_point` (x category_rate when the item's category
// matches the character's; x big_rate on a big success), truncated.
u32 boost_exp(u32 count, u32 base_boosted_point, bool same_category, double category_rate, bool big_success, double big_rate);
// A seed-raised stat: current + per_seed x count, capped at add_max.
u32 stat_seed_gain(u32 current, u32 per_seed, u32 count, u32 add_max);

// Boosted points a compose material adds: (the material's level + 100) x the material rarity's
// boosted_point (in the base's compose table) / 100. The material's own boosted points don't count.
u32 compose_points(u32 material_level, u32 rarity_boosted_point);
// A weapon / accessory's level and its boosted points within that level (CItemInfo's `level`,
// `boosted_point`).
struct ItemLevel {
    u32 level = 1, points = 0;
};
// `add` boosted points fed to an item at `level` with `points` within it: each
// `next_level_boosted_point` is a level; at `level_max` the points are 0 and the rest is lost.
ItemLevel item_level_up(u32 level, u32 points, u32 add, u32 next_level_boosted_point, u32 level_max);
// Selling price of a weapon / accessory: round(sale_fol x sale_rate[level]).
u32 sell_price(u32 sale_fol, double sale_rate);
// Stamina points one heal item restores: heal_type 1 = heal_point % of the maximum, 2 / 3 =
// heal_point, else 0.
u32 heal_points(int heal_type, u32 heal_point, u32 stamina_max);

// The login-bonus day after `current_idx` (0 = never received) of a bonus whose last order_idx is
// `last`: +1, back to 1 after the last day when it loops, 0 (finished) otherwise.
u32 next_login_day(u32 current_idx, u32 last, bool loop);
// Item-shop period start for reset_type 2 (monthly on day `param` at `time_of_day` seconds): the
// latest such instant <= t. 0 for other reset types (no reset).
int64_t shop_period_start(int64_t t, int reset_type, int param, int time_of_day);

}  // namespace soa::server::growth_rules
