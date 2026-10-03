// Unit tests of the pure rules of soaserver/server.h `rules::` (rules/rules.cpp): weighted_pick,
// add_exp, interpolate_level, regen_stamina. Run in --selftest; not differential (the server has
// no guest counterpart): the rules against hand values. The domains' rules are tested beside
// them (gear_rules_tests.cpp, growth_rules_tests.cpp, ...).
#include <algorithm>
#include <cmath>

#include "soaserver/native_test.h"
#include "master/master.h"
#include "testing/scratch.h"  // test_master
#include "soaserver/ext.h"
#include "api/favor/favor.h"
#include "soaserver/msgpack.h"

namespace soa::server {

namespace {
using namespace ext;

std::vector<u8> call(Ctx& c, const char* method, std::vector<u64> ints, std::vector<std::vector<u64>> vecs = {}) {
    const Handler* h = find(method);
    if (!h) return {};
    Request r;
    r.method = method;
    r.ints = std::move(ints);
    r.vecs = std::move(vecs);
    return (*h)(c, r);
}
u32 master_id(Ctx& c, const char* label, const char* table = "master_item") {
    return (u32)c.m.one(std::string("select id from ") + table + " where id_label = ?", {label});
}

// ---- rules:: (rules/rules.cpp; the tests were core/server.cpp's) ------------------------

NATIVE_TEST("server/weighted-pick") {
    std::vector<u32> w = {227, 0, 333, 83};
    t.expect_eq(rules::weighted_pick(w, 0), 0, "first");
    t.expect_eq(rules::weighted_pick(w, 226), 0, "end of first");
    t.expect_eq(rules::weighted_pick(w, 227), 2, "zero weight skipped");
    t.expect_eq(rules::weighted_pick(w, 559), 2, "end of third");
    t.expect_eq(rules::weighted_pick(w, 560), 3, "last");
    // frequencies follow the weights
    std::vector<int> hits(4);
    u64 sum = 643;
    for (int k = 0; k < 64300; k++) hits[rules::weighted_pick(w, t.rand_u64() % sum)]++;
    if (hits[1] != 0 || std::abs(hits[0] - 22700) > 1200 || std::abs(hits[2] - 33300) > 1200 || std::abs(hits[3] - 8300) > 900)
        t.fail("weighted frequencies %d %d %d %d", hits[0], hits[1], hits[2], hits[3]);
}

NATIVE_TEST("server/add-exp") {
    std::vector<u32> next = {0, 10, 20, 30, 0};  // level 4 is the table's end
    auto r = rules::add_exp(1, 5, 4, next, 4);
    t.expect_eq(r, std::make_pair(1u, 9u), "no level-up");
    r = rules::add_exp(1, 5, 5, next, 4);
    t.expect_eq(r, std::make_pair(2u, 0u), "exact level-up");
    r = rules::add_exp(1, 0, 35, next, 4);
    t.expect_eq(r, std::make_pair(3u, 5u), "two levels");
    r = rules::add_exp(1, 0, 1000, next, 4);
    t.expect_eq(r, std::make_pair(4u, 0u), "capped by the table");
    r = rules::add_exp(1, 0, 1000, next, 2);
    t.expect_eq(r, std::make_pair(2u, 0u), "capped by the level cap");
    Db* m = test_master();
    if (!m) return;  // no 3.7.0 master DB: the table checks are skipped
    // (a) the player's EXP curve: level 87 with 1048 EXP + mf01_001's 24 EXP stays at 87
    std::vector<u32> pn(1, 0);
    m->q("select level, next_exp from master_player_level order by level", {}, [&](const Row& x) {
        if (pn.size() <= (size_t)x.i("level")) pn.resize(x.i("level") + 1, 0);
        pn[x.i("level")] = (u32)x.i("next_exp");
    });
    u32 n87 = pn.size() > 87 ? pn[87] : 0;
    if (n87 <= 1072) t.fail("master_player_level 87 next_exp %u", n87);
    r = rules::add_exp(87, 1048, 24, pn, (u32)pn.size() - 1);
    t.expect_eq(r, std::make_pair(87u, 1072u), "player 87 + 24");
    r = rules::add_exp(87, 1048, n87 - 1048, pn, (u32)pn.size() - 1);
    t.expect_eq(r, std::make_pair(88u, 0u), "player level-up");
    // (a) the character common curve: level 1 next_exp is 129
    t.expect_eq((u32)m->one("select next_exp from master_character_common_parameter where level = 1", {}), 129u, "common next_exp");
}

NATIVE_TEST("server/level-interpolation") {
    std::vector<std::pair<u32, u32>> rows = {{1, 60}, {2, 111}, {255, 13038}, {300, 13500}};
    t.expect_eq(rules::interpolate_level(rows, 2), 111u, "exact row");
    t.expect_eq(rules::interpolate_level(rows, 256), 13038u + (u32)rules::round_half_away(462.0 / 45.0), "interpolated");
    t.expect_eq(rules::interpolate_level(rows, 999), 13500u, "above the table");
    t.expect_eq(rules::round_half_away(2.5), 3.0, "half up");
    t.expect_eq(rules::round_half_away(-2.5), -3.0, "half away");
    Db* m = test_master();
    if (!m) return;
    std::vector<std::pair<u32, u32>> st;
    m->q("select level, stamina from master_player_level order by level", {},
         [&](const Row& x) { st.emplace_back((u32)x.i("level"), (u32)x.i("stamina")); });
    t.expect_eq(rules::interpolate_level(st, 87), 134u, "stamina at 87 (a row)");
    u32 s255 = rules::interpolate_level(st, 255), s999 = rules::interpolate_level(st, 999);
    t.expect_eq(s255, 200u, "stamina at 255");
    t.expect_eq(s999, 300u, "stamina at 999");
    u32 s600 = rules::interpolate_level(st, 600);
    if (s600 < s255 || s600 > s999) t.fail("stamina at 600: %u", s600);
}

NATIVE_TEST("server/stamina") {
    auto r = rules::regen_stamina(10, 134, 180 * 5 + 7, 180);
    t.expect_eq(r, std::make_pair(15u, (u64)7), "5 points and 7 s carried");
    r = rules::regen_stamina(130, 134, 180 * 50, 180);
    t.expect_eq(r, std::make_pair(134u, (u64)0), "capped");
    r = rules::regen_stamina(140, 134, 180 * 50, 180);
    t.expect_eq(r, std::make_pair(140u, (u64)0), "over max isn't cut");
    Db* m = test_master();
    if (!m) return;
    t.expect_eq(master::global_str(m->h, "stamina_heal_time"), std::string("180"), "master_global stamina_heal_time");
    t.expect_eq((u32)m->one("select stamina from master_player_level where level = 87", {}), 134u, "stamina max at 87");
}

}  // namespace
}  // namespace soa::server
