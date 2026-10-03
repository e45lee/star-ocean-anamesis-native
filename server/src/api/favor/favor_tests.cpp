// Unit tests of the favor rules (favor.h): the pure rules against hand values, and the battle
// gain on a scratch server seeded from the test seed save (--selftest; not differential: the
// server has no guest counterpart).
#include <ctime>

#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "api/favor/favor.h"

namespace soa::server::favor {
namespace {
using namespace ext;

NATIVE_TEST("favor/favor-rules") {
    // the 3.7.0 master_favor_level thresholds (cumulative, (a)+(b))
    const std::vector<u32> next = {10000, 30000, 60000, 90000, 99999999};
    t.expect_eq(rules::level(0, next, 4), 1u, "0 points");
    t.expect_eq(rules::level(9999, next, 4), 1u, "just below level 2");
    t.expect_eq(rules::level(10000, next, 4), 2u, "level 2");
    t.expect_eq(rules::level(59999, next, 4), 3u, "level 3");
    t.expect_eq(rules::level(60000, next, 4), 4u, "level 4");
    t.expect_eq(rules::level(95000, next, 4), 4u, "capped at the schedule's max");
    t.expect_eq(rules::level(95000, next, 5), 5u, "level 5 when the max is 5");
    t.expect_eq(rules::cap_points(70000, next, 4), 60000u, "points stop at the max level's threshold");
    t.expect_eq(rules::cap_points(5000, next, 4), 5000u, "below the cap");
    t.expect_eq(rules::cap_points(99999999, next, 5), 90000u, "max 5");
    // favor day: 03:59 and 04:00 are different days with reset hour 4
    struct tm a {};
    a.tm_year = 121;
    a.tm_mon = 5;
    a.tm_mday = 20;
    a.tm_hour = 3;
    a.tm_min = 59;
    a.tm_isdst = -1;
    int64_t t1 = mktime(&a);
    t.expect_eq(rules::favor_day(t1, 4) + 1, rules::favor_day(t1 + 60, 4), "reset at 04:00");
    t.expect_eq(rules::favor_day(t1 + 60, 4), rules::favor_day(t1 + 60 + 23 * 3600, 4), "same day until 03:59");
}

NATIVE_TEST("favor/friendship-campaign") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        const SameRoleId same = c.m.one_id<SameRoleId>("select id from master_favor_schedule where favor_max_level >= 4 order by id limit 1", {});
        if (!same.v) {
            t.fail("no favor schedule");
            c.st.exec("rollback");
            return;
        }
        u32 base = (u32)c.m.one(
            "select favor_up_point from master_favor_battle_effect where play_type = 0 and use_stamina <= 10 order by use_stamina desc limit 1", {});
        c.st.q("delete from favor", {});
        favor::mission_gain(c.st.h, c.m.h, c.now(), same, 10);
        t.expect_eq((u32)c.st.one("select point from favor where same_role_id = ?", {same}), base, "plain battle favor");
        favor::mission_gain(c.st.h, c.m.h, c.now(), same, 10, 1.5);
        t.expect_eq((u32)c.st.one("select point from favor where same_role_id = ?", {same}), base + (u32)(base * 1.5), "x1.5 (type-8 campaign)");
        c.st.exec("rollback");
    });
    if (!ran) return;
}

}  // namespace
}  // namespace soa::server::favor
