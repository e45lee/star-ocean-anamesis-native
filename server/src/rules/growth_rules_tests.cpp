// Unit tests of the pure growth / economy / daily rules (rules/growth_rules.h) against hand values
// (run in --selftest; not differential: the server has no guest counterpart).
#include <ctime>

#include "soaserver/native_test.h"
#include "core/time.h"
#include "rules/growth_rules.h"

namespace soa::server {
namespace {
namespace gr = growth_rules;

NATIVE_TEST("rules/growth") {
    // (b) EXP: count x base x 1.5 on a category match, truncated; big success x1.5
    t.expect_eq(gr::boost_exp(3, 16000, false, 1.5, false, 1.5), 48000u, "plain");
    t.expect_eq(gr::boost_exp(3, 16000, true, 1.5, false, 1.5), 72000u, "category bonus");
    t.expect_eq(gr::boost_exp(1, 1001, true, 1.5, true, 1.5), 2251u, "truncated twice (1501 -> 2251)");
    t.expect_eq(gr::stat_seed_gain(10, 5, 4, 25), 25u, "seed capped");
    t.expect_eq(gr::stat_seed_gain(10, 1, 4, 25), 14u, "seed");
    // (b) GetAddBoostedPoint: (the material's level + 100) x boosted_point / 100, truncated
    t.expect_eq(gr::compose_points(1, 5000), 5050u, "a fresh rarity-4 material: the preview's 5050");
    t.expect_eq(gr::compose_points(1, 2000), 2020u, "a fresh rarity-3 material");
    t.expect_eq(gr::compose_points(1, 10000), 10100u, "a fresh rarity-5 material");
    t.expect_eq(gr::compose_points(10, 5000), 5500u, "a level-10 rarity-4 material");
    t.expect_eq(gr::compose_points(20, 10000), 12000u, "a level-20 rarity-5 material (limit break 5)");
    t.expect_eq(gr::compose_points(1, 250), 252u, "rarity 2: 252.5 truncated");
    t.expect_eq(gr::compose_points(3, 100), 103u, "rarity 1, level 3");
    // (b) _CalcLevel: per level next_level_boosted_point, the rest carried, 0 at the cap
    auto lv = [](gr::ItemLevel l) { return l.level * 100000 + l.points; };
    t.expect_eq(lv(gr::item_level_up(1, 0, 5050, 10000, 10)), 1u * 100000 + 5050, "within the level");
    t.expect_eq(lv(gr::item_level_up(1, 5050, 5050, 10000, 10)), 2u * 100000 + 100, "a level up, 100 carried");
    t.expect_eq(lv(gr::item_level_up(1, 0, 10000, 10000, 10)), 2u * 100000 + 0, "exactly one level");
    t.expect_eq(lv(gr::item_level_up(1, 0, 25250, 5000, 10)), 6u * 100000 + 250, "five levels at once");
    t.expect_eq(lv(gr::item_level_up(9, 4000, 7000, 5000, 10)), 10u * 100000 + 0, "the cap: points 0, the rest lost");
    t.expect_eq(lv(gr::item_level_up(10, 0, 5050, 5000, 10)), 10u * 100000 + 0, "at the cap nothing is added");
    t.expect_eq(lv(gr::item_level_up(10, 0, 5050, 5000, 12)), 11u * 100000 + 50, "a raised cap (limit break 1) levels on");
    t.expect_eq(gr::sell_price(270, 1.2), 324u, "sale rate");
    t.expect_eq(gr::sell_price(25, 1.1), 28u, "rounded (27.5 -> 28)");
    t.expect_eq(gr::heal_points(1, 100, 134), 134u, "item_heal_100 = the max");
    t.expect_eq(gr::heal_points(2, 50, 134), 50u, "item_heal_50");
    t.expect_eq(gr::heal_points(0, 50, 134), 0u, "not a heal type");
    t.expect_eq(gr::next_login_day(0, 28, true), 1u, "first day");
    t.expect_eq(gr::next_login_day(27, 28, true), 28u, "last day");
    t.expect_eq(gr::next_login_day(28, 28, true), 1u, "loops");
    t.expect_eq(gr::next_login_day(7, 7, false), 0u, "finished");
    // the daily reset at 04:00 local time
    struct tm tm = {};
    tm.tm_year = 2021 - 1900;
    tm.tm_mon = 5;
    tm.tm_mday = 10;
    tm.tm_hour = 3;
    tm.tm_min = 59;
    tm.tm_isdst = -1;
    int64_t t359 = (int64_t)mktime(&tm);
    tm.tm_hour = 4;
    tm.tm_min = 0;
    tm.tm_isdst = -1;
    int64_t t400 = (int64_t)mktime(&tm);
    t.expect_eq(day_start(t400, 4), t400, "04:00 starts a day");
    if (day_start(t359, 4) != t400 - 86400) t.fail("03:59 belongs to the previous day");
    // monthly shop periods (reset_type 2, day 1, 00:00:00)
    tm = {};
    tm.tm_year = 2021 - 1900;
    tm.tm_mon = 5;
    tm.tm_mday = 1;
    tm.tm_isdst = -1;
    int64_t june1 = (int64_t)mktime(&tm);
    t.expect_eq(gr::shop_period_start(t400, 2, 1, 0), june1, "period of June 10");
    t.expect_eq(gr::shop_period_start(june1, 2, 1, 0), june1, "period start itself");
    tm.tm_mon = 4;
    tm.tm_isdst = -1;
    t.expect_eq(gr::shop_period_start(june1 - 1, 2, 1, 0), (int64_t)mktime(&tm), "May 31 23:59:59 -> May 1");
    t.expect_eq(gr::shop_period_start(t400, 0, 0, 0), (int64_t)0, "no reset");
}

}  // namespace
}  // namespace soa::server
