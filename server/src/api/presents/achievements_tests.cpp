// Unit tests of the achievements (achievements.cpp), on a scratch server seeded from the test seed save
// (--selftest; not differential: the server has no guest counterpart).
#include <algorithm>

#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "soaserver/msgpack.h"
#include "testing/module_test.h"

namespace soa::server {
namespace {
using namespace ext;
using module_test::call;
using module_test::master_id;
using module_test::player_load_data;

NATIVE_TEST("presents/favor-achievements") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        // (a) a type-52 achievement (favor points with a role) of an owned character's same_role_id
        int64_t ach = 0;
        u32 same = 0, goal = 0;
        c.m.q(
            "select a.id, a.goal_count, a.target_id as same_role_id from master_achievement a "
            "where a.type = 52 and a.default_release = 1 order by a.goal_count, a.id",
            {}, [&](const Row& a) {
                if (ach) return;
                ach = a.i("id");
                goal = (u32)a.i("goal_count");
                same = (u32)a.i("same_role_id");
            });
        if (!ach) {
            t.fail("no default type-52 achievement");
            c.st.exec("rollback");
            return;
        }
        c.st.q(
            "insert into favor (same_role_id, point) values (?, ?)"
            " on conflict(same_role_id) do update set point = excluded.point, tap_count = excluded.tap_count, "
            "tapped_at = excluded.tapped_at, event_drop_at = excluded.event_drop_at",
            {same, goal});
        Value d = player_load_data(c);
        const Value* list = d.find("Achievement");
        bool goal_seen = false;
        if (list)
            for (auto& [k, e] : list->map)  // a map keyed by the id (api/presents/achievements.cpp achievement_map)
                if ((int64_t)e.get_u("master_achievement_id") == ach) goal_seen = e.find("is_goal")->b && !e.find("limit_at")->s.empty();
        if (!goal_seen) t.fail("player load: favor achievement %lld not reported as goal with a limit_at", (long long)ach);
        // receiving it (AchievementListReceive, as CAdjutantSelect sends it) puts the reward in the box
        int64_t n0 = c.st.one("select count(*) from presents", {});
        call(c, "AchievementListReceive", {}, {{(u64)ach}});
        t.expect_eq(c.st.one("select count(*) from presents", {}), n0 + 1, "reward present");
        c.st.exec("rollback");
    });
    if (!ran) return;
}

// An achievement chain: the player-rank achievements ac_ind_rank_01 (rank 110) and its next:
// not received before the goal, the reward in the present box once, the next one active after
// it. Was part of server/economy-apis.
NATIVE_TEST("presents/achievement-chain") {
    with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        // ---- achievements: the permanent player-rank chain (ac_ind_rank_01 = rank 110)
        u32 ach = master_id(c, "ac_ind_rank_01", "master_achievement");
        u32 nxt = (u32)c.m.one("select next_achievement_id from master_achievement where id = ?", {ach});
        if (ach && nxt) {
            c.st.q("update player set level = 109", {});
            call(c, "AchievementReceive", {ach});
            t.expect_eq(c.st.one("select count(*) from achievements where id = ?", {ach}), (int64_t)0, "rank 109: not reached");
            c.st.q("update player set level = 110", {});
            int64_t q0 = c.st.one("select count(*) from presents", {});
            call(c, "AchievementReceive", {ach});
            t.expect_eq((u32)c.st.one("select count(*) from achievements where id = ? and received_at is not null", {ach}), 1u, "received");
            t.expect_eq(c.st.one("select count(*) from presents", {}), q0 + 1, "reward in the present box");
            call(c, "AchievementReceive", {ach});
            t.expect_eq(c.st.one("select count(*) from presents", {}), q0 + 1, "not twice");
            // (a) next_achievement_id becomes active; the received one leaves the list
            auto b = call(c, "AchievementActiveList", {0});
            if (b.empty()) t.fail("AchievementActiveList");
            // received rows are gone and the chain's next row is in: check through a second
            // receive of the next one (rank 120 not reached)
            call(c, "AchievementReceive", {nxt});
            t.expect_eq(c.st.one("select count(*) from achievements where id = ?", {nxt}), (int64_t)0, "rank 120 not reached");
            c.st.q("update player set level = 120", {});
            call(c, "AchievementReceive", {nxt});
            t.expect_eq(c.st.one("select count(*) from achievements where id = ?", {nxt}), (int64_t)1, "rank 120 received");
        } else {
            t.fail("no ac_ind_rank_01 chain");
        }
        c.st.exec("commit");
    });
}

}  // namespace
}  // namespace soa::server
