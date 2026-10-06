// Unit tests of the pure mission rules (rules/mission_rules.h) against hand values: the tables,
// the surprise roll, campaign windows and stamina, evaluation ranks, the character bonus caps, the
// step-up and box gacha picks (run in --selftest; not differential: the server has no guest
// counterpart).
#include <cmath>
#include <ctime>
#include <string>
#include <vector>

#include "rules/mission_rules.h"
#include "soaserver/native_test.h"

namespace soa::server::mission_rules {
namespace {

NATIVE_TEST("rules/missions") {
    t.expect_eq(std::string(mission_table(0)), std::string("master_mission"), "story table");
    t.expect_eq(std::string(mission_table(1)), std::string("master_event_mission"), "event table");
    t.expect_eq(std::string(mission_table(4)), std::string("master_training_mission"), "the battle simulator's table");
    t.expect_eq(std::string(mission_table(7)), std::string(""), "unknown type");
    // surprise: 10.25 % of the draws
    t.expect_eq(roll_percent(10.25, 102499), true, "just inside");
    t.expect_eq(roll_percent(10.25, 102500), false, "just outside");
    t.expect_eq(roll_percent(0, 0), false, "zero rate");
    int hits = 0;
    for (int k = 0; k < 100000; k++) hits += roll_percent(10.25, t.rand_u64());
    if (std::abs(hits - 10250) > 600) t.fail("surprise frequency %d / 100000", hits);
    // campaigns
    struct tm tm = {};
    tm.tm_year = 2021 - 1900, tm.tm_mon = 4, tm.tm_mday = 1, tm.tm_hour = 12, tm.tm_isdst = -1;
    int64_t may1 = (int64_t)mktime(&tm);
    t.expect_eq(campaign_active("2021-04-22", "14:30:00", "2021-06-24", "13:59:59", 7, may1), true, "inside");
    t.expect_eq(campaign_active("2021-04-22", "14:30:00", "2021-06-24", "13:59:59", 7, may1 + 60 * 86400), false, "after");
    t.expect_eq(campaign_active("2021-04-22", "14:30:00", "2021-06-24", "13:59:59", 6, may1), true, "Saturday 2021-05-01");
    t.expect_eq(campaign_active("2021-04-22", "14:30:00", "2021-06-24", "13:59:59", 0, may1), false, "not Sunday");
    t.expect_eq(campaign_applies(-2, 0, 1, 99), true, "all types");
    t.expect_eq(campaign_applies(3, 0, 1, 99), false, "other type");
    t.expect_eq(campaign_applies(1, 99, 1, 99), true, "its area");
    t.expect_eq(campaign_applies(1, 98, 1, 99), false, "other area");
    // continue campaigns (b: CUIUtility::GetDecMissionContinueCoin): model 99 in the first pass
    // only; the mission's type in the second, the area only for event missions
    t.expect_eq(continue_campaign_applies(99, 0, true, 0, 5), true, "every type: first pass");
    t.expect_eq(continue_campaign_applies(99, 0, false, 0, 5), false, "every type: not in the type pass");
    t.expect_eq(continue_campaign_applies(0, 0, true, 0, 5), false, "a type's row: not in the first pass");
    t.expect_eq(continue_campaign_applies(0, 7, false, 0, 5), true, "story: the area isn't checked");
    t.expect_eq(continue_campaign_applies(1, 7, false, 1, 5), false, "event: another area");
    t.expect_eq(continue_campaign_applies(1, 5, false, 1, 5), true, "event: its area");
    t.expect_eq(continue_campaign_applies(1, 0, false, 1, 5), true, "event: every area");
    t.expect_eq(continue_campaign_applies(3, 0, false, 1, 5), false, "another type");
    t.expect_eq(continue_price(100, 0.5), 50u, "half price");
    t.expect_eq(continue_price(101, 0.5), 50u, "truncated");
    t.expect_eq(campaign_stamina(15, 0.5), 8u, "half, rounded up");
    t.expect_eq(campaign_stamina(1, 0.5), 1u, "at least 1");
    t.expect_eq(campaign_stamina(0, 0.5), 0u, "free stays free");
    // evaluation
    std::vector<u64> dmg = {600000000, 300000000, 100000000, 0, 0};
    t.expect_eq(evaluation_rank(1, dmg, 350000000), 2, "rank 2");
    t.expect_eq(evaluation_rank(1, dmg, 99999999), 0, "no rank");
    std::vector<u64> tm6 = {60000, 90000, 120000, 0, 0};
    t.expect_eq(evaluation_rank(6, tm6, 59000), 1, "fast clear");
    t.expect_eq(evaluation_rank(6, tm6, 100000), 3, "slow clear");
    t.expect_eq(evaluation_rank(6, tm6, 0), 0, "no time");
    // character bonus caps
    auto cb = character_bonus({{1, 0}, {1, 1}, {1, 2}}, 2, 2);
    t.expect_eq(cb.lots, 2u, "lots capped");
    t.expect_eq(cb.extra, 2u, "extra capped");
    // step-up chain of 3: 1 -> 2 -> 3 -> 1 (restart)
    std::vector<u32> steps = {11, 12, 13};
    t.expect_eq(stepup_index(steps, 0), 0, "not started");
    t.expect_eq(stepup_index(steps, 13), 2, "at step 3");
    t.expect_eq(stepup_advance(steps, 0), std::make_pair(1, 0u), "to step 2");
    t.expect_eq(stepup_advance(steps, 2), std::make_pair(0, 1u), "loop");
    // box: draws without replacement empty the box exactly
    std::vector<u32> box = {1, 3, 0, 2};
    std::vector<u32> got(4);
    for (int k = 0; k < 6; k++) {
        int i = box_pick(box, t.rand_u64());
        if (i < 0 || box[i] == 0) return t.fail("picked an empty slot");
        box[i]--;
        got[i]++;
    }
    t.expect_eq(box_pick(box, 0), -1, "empty box");
    t.expect_eq(got, std::vector<u32>({1, 3, 0, 2}), "every copy once");
}

}  // namespace
}  // namespace soa::server::mission_rules
