// Unit tests of the pure deep space rules (rules/deepspace_rules.h) against hand values (run in
// --selftest; not differential: the server has no guest counterpart).
#include <cmath>
#include <ctime>

#include "soaserver/native_test.h"
#include "rules/deepspace_rules.h"

namespace soa::server {
namespace {
namespace dr = rules::deepspace;

NATIVE_TEST("rules/deepspace") {
    // (b) the client's bonus curve: below the minimum x emin; one member over the minimum of a
    // 1..4 range is 2/4 of the way; the top reaches emax.
    t.expect_eq(dr::bonus_value(0, 1, 4, 1, 3, false), 1.0f, "below the minimum");
    t.expect_eq(std::fabs(dr::bonus_value(1, 1, 4, 1, 3, false) - 1.5f) < 1e-4f, true, "1 of 1..4");
    t.expect_eq(std::fabs(dr::bonus_value(4, 1, 4, 1, 3, false) - 3.0f) < 1e-4f, true, "4 of 1..4");
    t.expect_eq(std::fabs(dr::bonus_value(9, 1, 4, 1, 3, false) - 3.0f) < 1e-4f, true, "clamped");
    // quick return: 2h01m left at rate 3 = 9 items; 4 owned -> 4 items + 50 coins
    auto q = dr::quick_return_cost(2 * 3600 + 60, 3.0f, 4);
    t.expect_eq(q.items, 4u, "items used");
    t.expect_eq(q.coins, 50u, "coins for the rest");
    auto q2 = dr::quick_return_cost(1800, 1.0f, 10);
    t.expect_eq(q2.items, 1u, "half an hour counts as one");
    t.expect_eq(q2.coins, 0u, "no coins");
    // (d) play limits: 1 = per day, 2 = per week, no count = none, unknown types = none
    t.expect_eq(dr::limit_reached(1, 2, 1, 5), false, "daily 1 of 2");
    t.expect_eq(dr::limit_reached(1, 2, 2, 0), true, "daily 2 of 2");
    t.expect_eq(dr::limit_reached(2, 3, 9, 2), false, "weekly 2 of 3");
    t.expect_eq(dr::limit_reached(2, 3, 0, 3), true, "weekly 3 of 3");
    t.expect_eq(dr::limit_reached(0, 0, 9, 9), false, "no limit");
    t.expect_eq(dr::limit_reached(1, 0, 9, 9), false, "no count");
    t.expect_eq(dr::limit_reached(7, 1, 9, 9), false, "unknown type");
    // (d) the week starts on Monday at the daily reset: Wed 2020-06-03 04:00 -> Mon 2020-06-01 04:00
    struct tm tm = {};
    tm.tm_year = 120, tm.tm_mon = 5, tm.tm_mday = 3, tm.tm_hour = 4, tm.tm_isdst = -1;
    int64_t wed = (int64_t)mktime(&tm);
    tm = {};
    tm.tm_year = 120, tm.tm_mon = 5, tm.tm_mday = 1, tm.tm_hour = 4, tm.tm_isdst = -1;
    int64_t mon = (int64_t)mktime(&tm);
    t.expect_eq(dr::week_start(wed), mon, "Wednesday -> Monday");
    t.expect_eq(dr::week_start(mon), mon, "Monday stays");
    tm = {};
    tm.tm_year = 120, tm.tm_mon = 5, tm.tm_mday = 7, tm.tm_hour = 4, tm.tm_isdst = -1;
    t.expect_eq(dr::week_start((int64_t)mktime(&tm)), mon, "Sunday -> the Monday before");
}

}  // namespace
}  // namespace soa::server
