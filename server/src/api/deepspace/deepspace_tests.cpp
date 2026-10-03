// Unit tests of the deep space module (api/deepspace/; --selftest "deepspace/") on a scratch server
// seeded from the test seed save: an expedition from offer to rewards, the quick return, an area
// opening; the pass ships, the play limits and the deep space achievements. Not differential (the
// server has no guest counterpart). The pure rules are tested in rules/deepspace_rules_tests.cpp.
#include <cmath>
#include <string>
#include <vector>

#include "api/deepspace/deepspace.h"
#include "rules/deepspace_rules.h"
#include "soaserver/ext.h"
#include "soaserver/native_test.h"
#include "testing/module_test.h"

namespace soa::server {
namespace {
using namespace ext;
using module_test::call;
using namespace deepspace;
namespace dr = rules::deepspace;

NATIVE_TEST("deepspace/expedition") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        int64_t base = c.parse_time("2020-06-01 12:00:00"), clock = base;
        c.test.now = [&] { return clock; };
        c.test.event_now = [&] { return clock; };
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        // the areas without requirements open, with their normal missions on offer
        if (call(c, "DeepSpaceActiveList", {}).empty()) return t.fail("DeepSpaceActiveList");
        u32 open = (u32)c.st.one("select count(*) from ds_area", {});
        t.expect_eq(open, (u32)c.m.one("select count(*) from master_deep_space_area where ifnull(is_required, 0) = 0", {}), "starting areas");
        u32 area = (u32)c.m.one("select id from master_deep_space_area where ifnull(is_required, 0) = 0 order by order_id limit 1", {});
        u32 mission = (u32)c.st.one("select o.mission_id from ds_offer o where o.area_id = ? order by o.mission_id limit 1", {area});
        if (!mission) return t.fail("no offer in area %u", area);
        int64_t minutes = c.m.one("select time from master_deep_space_mission where id = ?", {mission});
        // a ship: the seed save's limit breaks give at least one
        c.st.q("update roster set limit_break = 10", {});
        std::vector<u64> party;
        c.st.q("select uid from roster order by uid limit 3", {}, [&](const Row& r) { party.push_back((u64)r.i("uid")); });
        // auto select proposes free characters
        u32 set = (u32)c.st.one("select bonus_set_id from ds_offer where mission_id = ?", {mission});
        u32 b1 = (u32)c.m.one("select bonus1_id from master_deep_space_bonus_set where id = ?", {set});
        call(c, "DeepSpaceAutoMemberSelect", {set, b1});
        code = 0;
        call(c, "DeepSpaceMissionStart", {mission, 0}, {party});
        t.expect_eq(code, 0u, "start accepted");
        t.expect_eq((u32)c.st.one("select count(*) from ds_ship", {}), 1u, "one ship out");
        t.expect_eq(c.st.one("select closed_at - started_at from ds_ship", {}), minutes * 60, "time in minutes");
        // the same characters can't go twice
        u32 other = (u32)c.st.one("select mission_id from ds_offer where area_id = ? and ship_id = 0 limit 1", {area});
        code = 0;
        call(c, "DeepSpaceMissionStart", {other, 0}, {{party[0]}});
        t.expect_eq(code, 10208u, "busy member refused");
        // not back yet: MissionEnd refused, nothing changes
        u32 lv0 = (u32)c.st.one("select level from player", {});
        u32 exp0 = (u32)c.st.one("select exp from player", {});
        u32 fol0 = fol(c);
        u32 ship = (u32)c.st.one("select ship_id from ds_ship", {});
        clock = base + minutes * 60 - 10;
        code = 0;
        call(c, "DeepSpaceMissionEnd", {ship});
        t.expect_eq(code, 10208u, "early end refused");
        t.expect_eq((u32)c.st.one("select count(*) from ds_ship", {}), 1u, "still out");
        // back: rewards
        clock = base + minutes * 60 + 1;
        code = 0;
        u32 cexp = (u32)c.m.one("select character_exp from master_deep_space_mission where id = ?", {mission});
        u32 e_before = (u32)c.st.one("select exp from roster where uid = ?", {party[0]});
        u32 l_before = (u32)c.st.one("select level from roster where uid = ?", {party[0]});
        auto out = call(c, "DeepSpaceMissionEnd", {ship});
        t.expect_eq(code, 0u, "end accepted");
        t.expect_eq((u32)c.st.one("select count(*) from ds_ship", {}), 0u, "ship collected");
        t.expect_eq(fol(c), fol0 + (u32)c.m.one("select fol from master_deep_space_mission where id = ?", {mission}), "FOL");
        u32 lv1 = (u32)c.st.one("select level from player", {}), exp1 = (u32)c.st.one("select exp from player", {});
        if (lv1 == lv0 && exp1 <= exp0 && lv0 < c.player_level_max()) t.fail("no player EXP (%u/%u -> %u/%u)", lv0, exp0, lv1, exp1);
        RoleId role = c.st.one_id<RoleId>("select role_id from roster where uid = ?", {party[0]});
        auto want = rules::add_exp(l_before, e_before, cexp, c.role_next(role), c.role_level_cap(role));
        t.expect_eq((u32)c.st.one("select exp from roster where uid = ?", {party[0]}), want.second, "character EXP");
        t.expect_eq(area_exp(c, area), (u32)c.m.one("select exp from master_deep_space_mission where id = ?", {mission}), "area exp");
        // quick return: a new expedition returned at once with coins / items
        clock += 10;
        u32 m2 = (u32)c.st.one("select mission_id from ds_offer where area_id = ? and ship_id = 0 order by mission_id desc limit 1", {area});
        c.st.q("update player set free_coin = 1000", {});
        code = 0;
        call(c, "DeepSpaceMissionStart", {m2, 0}, {party});
        t.expect_eq(code, 0u, "second start");
        ship = (u32)c.st.one("select ship_id from ds_ship", {});
        code = 0;
        call(c, "DeepSpaceMissionEndNow", {ship});
        t.expect_eq(code, 0u, "quick return");
        t.expect_eq(c.st.one("select closed_at <= ? from ds_ship", {clock}), (int64_t)1, "back now");
        if (c.st.one("select free_coin from player", {}) >= 1000) t.fail("quick return was free");
        u32 fol1 = fol(c);
        code = 0;
        call(c, "DeepSpaceMissionEnd", {ship});
        t.expect_eq(code, 0u, "collected after the quick return");
        t.expect_eq((u32)c.st.one("select count(*) from ds_ship", {}), 0u, "ship collected");
        t.expect_eq(fol(c), fol1 + (u32)c.m.one("select fol from master_deep_space_mission where id = ?", {m2}), "rewards at MissionEnd");
        t.expect_eq(c.st.one("select time_saving_count from player", {}), (int64_t)1, "use counted");
        // (a) an area needing others opens once their exploration rates reach required_exp_rateN
        u32 locked = 0, r1 = 0, r2 = 0;
        double p1 = 0, p2 = 0;
        c.m.q("select * from master_deep_space_area where is_required = 1 and required_area3_id is null order by order_id limit 1", {},
              [&](const Row& a) {
                  locked = (u32)a.i("id");
                  r1 = (u32)a.i("required_area1_id");
                  r2 = (u32)a.i("required_area2_id");
                  p1 = a.f("required_exp_rate1");
                  p2 = a.f("required_exp_rate2");
              });
        if (!locked) return t.fail("no area with requirements");
        call(c, "DeepSpaceActiveList", {});
        t.expect_eq((u32)c.st.one("select count(*) from ds_area where area_id = ?", {locked}), 0u, "locked at first");
        u32 max1 = (u32)c.m.one("select max_exp from master_deep_space_area where id = ?", {r1});
        u32 max2 = (u32)c.m.one("select max_exp from master_deep_space_area where id = ?", {r2});
        c.st.q(
            "insert into ds_area (area_id, exp) values (?, ?)"
            " on conflict(area_id) do update set exp = excluded.exp, is_new = excluded.is_new, "
            "is_last_play = excluded.is_last_play",
            {r1, (u32)std::ceil(max1 * p1 / 100)});
        c.st.q(
            "insert into ds_area (area_id, exp) values (?, ?)"
            " on conflict(area_id) do update set exp = excluded.exp, is_new = excluded.is_new, "
            "is_last_play = excluded.is_last_play",
            {r2, (u32)std::ceil(max2 * p2 / 100) - 1});
        call(c, "DeepSpaceActiveList", {});
        t.expect_eq((u32)c.st.one("select count(*) from ds_area where area_id = ?", {locked}), 0u, "one condition short");
        c.st.q("update ds_area set exp = exp + 1 where area_id = ?", {r2});
        call(c, "DeepSpaceActiveList", {});
        t.expect_eq((u32)c.st.one("select count(*) from ds_area where area_id = ?", {locked}), 1u, "opened");
        t.expect_eq((u32)c.st.one("select count(*) from ds_offer where area_id = ?", {locked}) > 0, true, "its missions offered");
    });
    if (!ran) return;  // needs the 3.7.0 master and save
}

// Subscription ships, play limits and the deep space achievements.
NATIVE_TEST("deepspace/extras") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        int64_t base = c.parse_time("2020-06-01 12:00:00"), clock = base;
        c.test.now = [&] { return clock; };
        c.test.event_now = [&] { return clock; };
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        call(c, "DeepSpaceActiveList", {});
        // ---- ships: limit breaks give one ship; the pass adds master_global subscription_deepspace_ship
        c.st.q("update roster set limit_break = 0", {});
        t.expect_eq(max_ships(c, clock), 1u, "one ship without limit breaks (required_num 0)");
        u32 plan = (u32)c.m.one("select id from master_subscription_plan where id_label = 'pshop_galaxypass_001'", {});
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        // (a) content type 20, 30 days, through the registered grant (api/shop/subscription.cpp) with
        // this test's clock (the core's c.grant makes its own context on the real clock)
        const GrantFn* g20 = find_grant(20);
        if (!g20) return t.fail("no content type 20 grant");
        (*g20)(c, plan, 30, items, stocks, chars);
        u32 extra = c.global_u32("subscription_deepspace_ship", 0);
        t.expect_eq(extra, 2u, "master_global subscription_deepspace_ship");
        t.expect_eq(max_ships(c, clock), 1u + extra, "the pass adds its ships");
        std::vector<u64> uids;
        c.st.q("select uid from roster order by uid limit 3", {}, [&](const Row& r) { uids.push_back((u64)r.i("uid")); });
        if (uids.size() < 3) return t.fail("seed roster too small");
        std::vector<u32> missions;
        c.st.q("select mission_id from ds_offer where ship_id = 0 order by area_id, mission_id limit 4", {},
               [&](const Row& r) { missions.push_back((u32)r.i("mission_id")); });
        if (missions.size() < 4) return t.fail("fewer than 4 offers");
        for (int k = 0; k < 3; k++) {
            code = 0;
            call(c, "DeepSpaceMissionStart", {missions[k], 0}, {{uids[k]}});
            t.expect_eq(code, 0u, ("start on ship " + std::to_string(k + 1)).c_str());
        }
        t.expect_eq((u32)c.st.one("select max(ship_id) from ds_ship", {}), 3u, "ships 1..3");
        // the pass runs out: the ships out still come back, none departs beyond the limit-break ship
        clock = base + 31 * 86400;
        t.expect_eq(max_ships(c, clock), 1u, "the pass ran out");
        code = 0;
        call(c, "DeepSpaceMissionEnd", {3});
        t.expect_eq(code, 0u, "a pass ship still comes back");
        code = 0;
        call(c, "DeepSpaceMissionStart", {missions[3], 0}, {{uids[2]}});
        t.expect_eq(code, 10208u, "no free ship once the pass ran out");
        for (u32 s : {1u, 2u}) call(c, "DeepSpaceMissionEnd", {s});
        t.expect_eq((u32)c.st.one("select count(*) from ds_ship", {}), 0u, "all collected");
        // ---- achievements: type 45 counts departures, type 44 the area's exploration rate
        u32 ac45 = (u32)c.m.one("select id from master_achievement where id_label = 'ac_ind_ds_00'", {});
        u32 ac44 = (u32)c.m.one("select id from master_achievement where type = 44 order by order_id limit 1", {});
        u32 area44 = (u32)c.m.one("select target_id from master_achievement where id = ?", {ac44});
        auto count_of = [&](u32 id) -> int64_t {
            for (auto& [k, e] : achievement_state(c).map) {
                const Value* m = e.find("master_achievement_id");
                const Value* n = e.find("count");
                if (m && n && m->u == id) return (int64_t)n->u;
            }
            return -1;
        };
        t.expect_eq(count_of(ac45), (int64_t)1, "type 45: the expeditions (goal 1: capped)");
        t.expect_eq(c.st.one("select count(*) from ds_log", {}), (int64_t)3, "three departures logged");
        u32 max = (u32)c.m.one("select max_exp from master_deep_space_area where id = ?", {area44});
        c.st.q(
            "insert into ds_area (area_id, exp) values (?, ?)"
            " on conflict(area_id) do update set exp = excluded.exp, is_new = excluded.is_new, "
            "is_last_play = excluded.is_last_play",
            {area44, max / 2});
        t.expect_eq(count_of(ac44), (int64_t)(max / 2 * 100 / max), "type 44: the exploration rate");
        c.st.q("update ds_area set exp = ? where area_id = ?", {max, area44});
        t.expect_eq(count_of(ac44), (int64_t)100, "type 44: 100 %");
        // ---- play limits (the 3.7.0 data has none: a temp copy of the table sets them)
        c.m.exec("create temp table master_deep_space_mission as select * from main.master_deep_space_mission");
        u32 lm = missions[0], wm = missions[1];
        c.m.q("update temp.master_deep_space_mission set limit_type = 1, limit_count = 1 where id = ?", {lm});
        c.m.q("update temp.master_deep_space_mission set limit_type = 2, limit_count = 2 where id = ?", {wm});
        clock = base + 40 * 86400 + 3600;  // a new day and week for the counts
        auto listed = [&](u32 mission) {
            call(c, "DeepSpaceActiveList", {});
            u32 area = (u32)c.st.one("select area_id from ds_offer where mission_id = ?", {mission});
            bool found = false;
            for (auto& a : areas(c))
                if (a.id == area) found = area_info(c, a, clock)["DeepSpaceMissionList"].find(std::to_string(mission)) != nullptr;
            return found;
        };
        auto run = [&](u32 mission) {
            code = 0;
            call(c, "DeepSpaceMissionStart", {mission, 0}, {{uids[0]}});
            u32 got = code;
            if (!got) {
                clock += 9 * 3600;  // the longest expedition is 8 h
                u32 ship = (u32)c.st.one("select ship_id from ds_ship where mission_id = ?", {mission});
                call(c, "DeepSpaceMissionEnd", {ship});
            }
            return got;
        };
        t.expect_eq(listed(lm), true, "daily-limited mission listed");
        t.expect_eq(run(lm), 0u, "first play of the day");
        t.expect_eq(listed(lm), false, "hidden at its daily limit");
        t.expect_eq(run(lm), 10208u, "second play of the day refused");
        clock = limit_day(c, clock) + 86400 + 60;  // the next day, after 04:00
        t.expect_eq(listed(lm), true, "listed again the next day");
        t.expect_eq(run(wm), 0u, "weekly 1");
        t.expect_eq(run(wm), 0u, "weekly 2");
        t.expect_eq(run(wm), 10208u, "weekly 3 refused");
        clock = dr::week_start(limit_day(c, clock)) + 7 * 86400 + 60;
        t.expect_eq(run(wm), 0u, "the next week");
        c.m.exec("drop table temp.master_deep_space_mission");
        // a campaign row (no is_unlimited) counts only the expeditions inside its window:
        // Event_ac_2020Swm_02_43, 2020-08-20 14:30 .. 2020-09-10 13:59:59
        u32 swm = (u32)c.m.one("select id from master_achievement where id_label = 'Event_ac_2020Swm_02_43'", {});
        clock = c.parse_time("2020-08-25 12:00:00");
        t.expect_eq(count_of(swm), (int64_t)0, "campaign row: none in its window yet");
        t.expect_eq(run(missions[2]), 0u, "an expedition in the window");
        t.expect_eq(count_of(swm), (int64_t)1, "campaign row: counted");
    });
    if (!ran) return;  // needs the 3.7.0 master and save
}

}  // namespace
}  // namespace soa::server
