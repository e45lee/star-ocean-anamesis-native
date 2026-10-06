// Unit tests of the master-reference check (state/check.h). Run in --selftest; not differential
// (the server has no guest counterpart). Test names are their seeds (testing.h).
#include <string>
#include <vector>

#include "state/check.h"
#include "state/state.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

using ext::Row;

// server/PLAN-schema.md 4.2 / S0 / S1: the server's state is at this build's schema version with
// every table and foreign keys on; the seeded state violates no foreign key (S4: the party sets
// 1..party_set_max, the home character); after a scratch server's representative calls, no foreign
// key is violated and every reference into the master resolves; a planted dangling id is reported,
// a 0 "none" sentinel isn't.
NATIVE_TEST("server/schema-integrity") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;  // needs the 3.7.0 master and the test seed (the test failed)
    Server& sv = S.sv;
    S.set_clock("2021-05-25 12:00:00");
    t.expect_eq(state::user_version(sv.st.h), state::kSchemaVersion, "the state is at this build's version");
    t.expect_eq(sv.st.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    t.expect_eq(sv.st.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)55,
                "every table exists before the first request");
    int seeded_fk_rows = 0;
    sv.st.q("pragma foreign_key_check", {}, [&](const Row&) { seeded_fk_rows++; });
    t.expect_eq(seeded_fk_rows, 0, "the seeded state: foreign_key_check");
    t.expect_eq(sv.st.one("select count(*) from party_set", {}), sv.st.one("select count(*) from party_set where party_id between 1 and 10", {}),
                "the seeded party sets are 1..party_set_max");
    t.expect_eq(sv.st.one("select count(*) from party_set", {}), (int64_t)10, "party_set_max (10) sets seeded");
    t.expect_eq(sv.st.one("select count(*) from player p join roster r on r.uid = p.home_uid", {}), (int64_t)1, "the home character");
    sv.st.q("update player set free_coin = 100000", {});
    u32 mission = S.id("master_mission", "mf01_001");
    u32 gacha = S.id("master_gacha", "gacha_pickup_role_1011");
    t.expect_eq(S.call(Request{"Login", 0xa01c67ef, {}, {}, {}}), 0u, "Login");
    t.expect_eq(S.call(Request{"MissionStart", 0xb7c62bc2, {0, mission, 0, 0, 0, 0, 0}, {}, {}}), 0u, "MissionStart");
    t.expect_eq(S.call(Request{"MissionEnd", 0x8312a64c, {mission, 0}, {}, {}}), 0u, "MissionEnd");
    t.expect_eq(S.call(Request{"Gacha", 0xa0a1940b, {gacha}, {"x"}, {}}), 0u, "Gacha");
    t.expect_eq(S.call(Request{"GetPlayer", 0x9a056905, {}, {}, {}}), 0u, "GetPlayer");
    t.expect_eq((u32)sv.st.one("select count(*) from gacha_history", {}) > 0, true, "the draw is recorded");
    t.expect_eq((u32)sv.st.one("select count(*) from mission", {}) > 0, true, "the mission is recorded");

    int fk_rows = 0;
    sv.st.q("pragma foreign_key_check", {}, [&](const Row&) { fk_rows++; });
    t.expect_eq(fk_rows, 0, "foreign_key_check");
    auto dangling = state::check(sv.st.h, sv.m.h);
    for (const auto& d : dangling) t.fail("%s", state::describe(d).c_str());

    // a role id, an item id and a campaign mission id the master doesn't have are reported; a weapon
    // draw's role_id (NULL) isn't
    int64_t bad_role = 7, bad_item = 11;
    t.expect_eq(sv.m.one("select count(*) from master_role where id = ?", {bad_role}), (int64_t)0, "7 is no role id");
    t.expect_eq(sv.m.one("select count(*) from master_item where id = ?", {bad_item}), (int64_t)0, "11 is no item id");
    sv.st.q("insert into roster (uid, role_id, level, exp, created_at) values (?, ?, 1, 0, 0)", {0x7e7fffffll, bad_role});
    sv.st.q("insert into items (uid, master_item_id, item_type, created_at) values (?, ?, 1, 0)", {0x7d7fffffll, bad_item});
    sv.st.q("update gacha_history set role_id = null where id = (select min(id) from gacha_history)", {});
    // the campaign's clears (S12): an Episode 1 mission and a world map mission resolve, 13 doesn't
    int64_t bad_mission = 13, world_map_mission = sv.m.one("select min(id) from master_world_map_mission", {});
    t.expect_eq(sv.m.one("select count(*) from master_mission where id = ?", {bad_mission}) +
                    sv.m.one("select count(*) from master_world_map_mission where id = ?", {bad_mission}),
                (int64_t)0, "13 is no campaign mission id");
    sv.st.q("insert into campaign_clear (mission_id) values (?), (?), (?)", {(int64_t)mission, world_map_mission, bad_mission});
    dangling = state::check(sv.st.h, sv.m.h);
    t.expect_eq(dangling.size(), (size_t)3, "three references dangle");
    if (dangling.size() == 3) {
        t.expect_eq(std::string(dangling[2].ref.table) + "." + dangling[2].ref.column, std::string("campaign_clear.mission_id"), "the campaign's");
        t.expect_eq(dangling[2].ids, std::vector<int64_t>{bad_mission}, "its id");
        t.expect_eq(std::string(dangling[0].ref.table) + "." + dangling[0].ref.column, std::string("roster.role_id"), "the roster's");
        t.expect_eq(dangling[0].ids, std::vector<int64_t>{bad_role}, "its id");
        t.expect_eq(std::string(dangling[1].ref.table) + "." + dangling[1].ref.column, std::string("items.master_item_id"), "the item's");
        t.expect_eq(dangling[1].ids, std::vector<int64_t>{bad_item}, "its id");
        t.expect_eq(state::describe(dangling[0]), std::string("roster.role_id -> master_role.id: 1 dangling (7)"), "describe");
    }
}

}  // namespace
}  // namespace soa::server
