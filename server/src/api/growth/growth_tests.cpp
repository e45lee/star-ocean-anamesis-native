// Unit tests of the growth module's APIs (run in --selftest; not differential: the
// server has no guest counterpart): each API on a scratch server seeded from the test seed save,
// against the 3.7.0 master data. Their pure rules are tested in rules/growth_rules_tests.cpp.
#include <cmath>
#include <ctime>

#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "rules/growth_rules.h"
#include "core/time.h"

namespace soa::server {
namespace {
using namespace ext;
namespace gr = growth_rules;

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

NATIVE_TEST("growth/apis") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        // ---- BoostCharacter: EXP by the rule, items and FOL debited
        u64 uid = (u64)c.st.one("select uid from roster where level > 1 order by uid limit 1", {});
        RoleId role = c.st.one_id<RoleId>("select role_id from roster where uid = ?", {uid});
        u32 cat = (u32)c.m.one("select category_type from master_role where id = ?", {role});
        u32 rank = (u32)c.m.one("select rank from master_role where id = ?", {role});
        u32 rar = (u32)c.m.one("select rarity from master_role where id = ?", {role});
        c.st.q("update roster set level = 1, exp = 0 where uid = ?", {uid});
        u32 exp_item = (u32)c.m.one("select id from master_item where id_label like 'item_exp_%' and role_category_type = ? and rarity = 3", {cat});
        add_stock(c, exp_item, 5);
        add_fol(c, 10000000);
        u32 f0 = fol(c);
        if (call(c, "BoostCharacter", {uid, exp_item, 3}).empty()) t.fail("BoostCharacter");
        u32 one = (u32)c.m.one("select use_fol_one from master_role_boosted where rank = ? and rarity = ?", {rank, rar});
        t.expect_eq(fol(c), f0 - 3 * one, "boost FOL");
        t.expect_eq(stock_count(c, exp_item), 2u, "boost items");
        u32 base = (u32)c.m.one("select base_boosted_point from master_item where id = ?", {exp_item});
        u32 g1 = gr::boost_exp(3, base, true, 1.5, false, 1.5), g2 = gr::boost_exp(3, base, true, 1.5, true, 1.5);
        auto next = c.role_next(role);
        auto e1 = rules::add_exp(1, 0, g1, next, c.role_level_cap(role)), e2 = rules::add_exp(1, 0, g2, next, c.role_level_cap(role));
        std::pair<u32, u32> got{(u32)c.st.one("select level from roster where uid = ?", {uid}),
                                (u32)c.st.one("select exp from roster where uid = ?", {uid})};
        if (got != e1 && got != e2)
            t.fail("boost result %u/%u, want %u/%u or %u/%u", got.first, got.second, e1.first, e1.second, e2.first, e2.second);
        t.expect_eq(counter(c, "boost"), (int64_t)1, "boost counted");
        // refused: not enough items, nothing changes, error 10206 (the client's dialog)
        u32 f1 = fol(c), code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        call(c, "BoostCharacter", {uid, exp_item, 3});
        t.expect_eq(code, 10206u, "refusal code");
        t.expect_eq(fol(c), f1, "refused boost keeps FOL");
        t.expect_eq(stock_count(c, exp_item), 2u, "refused boost keeps items");

        // ---- LimitBreakCharacter: (a) master_character_limit_break items, (b) master_rank FOL
        u32 lbi = master_id(c, "item_limitbreak_03");
        c.st.q("update roster set limit_break = 0 where uid = ?", {uid});
        int64_t need = c.m.one(
            "select item_num from master_character_limit_break where limitbreak_id = (select limitbreak_id from master_role where id = ?) "
            "and item_id = ?",
            {role, lbi}, -1);
        if (need > 0) {
            add_stock(c, lbi, need);
            u32 f2 = fol(c), s2 = stock_count(c, lbi);
            call(c, "LimitBreakCharacter", {uid, lbi});
            t.expect_eq((u32)c.st.one("select limit_break from roster where uid = ?", {uid}), 1u, "limit break +1");
            t.expect_eq(stock_count(c, lbi), s2 - (u32)need, "limit-break items");
            t.expect_eq(fol(c), f2 - (u32)c.m.one("select use_fol from master_rank where rank = ? and limit_break = 1", {rank}), "limit-break FOL");
            // (b) as the limit-break screen sends it: the master_character_limit_break row id
            int64_t row = c.m.one(
                "select id from master_character_limit_break where limitbreak_id = (select limitbreak_id from master_role "
                "where id = ?) and item_id = ?",
                {role, lbi}, 0);
            add_stock(c, lbi, need);
            call(c, "LimitBreakCharacter", {uid, (u64)row});
            t.expect_eq((u32)c.st.one("select limit_break from roster where uid = ?", {uid}), 2u, "limit break by row id");
            c.st.q("update roster set limit_break = 1 where uid = ?", {uid});
        } else {
            t.fail("no limit-break row for role %u", role.v);
        }

        // ---- EvolutionCharacter: a ★5 with a ★6 of its category, at its cap, gets the ★6 role
        u64 euid = 0;
        u32 erole = 0;
        c.st.q("select uid, role_id from roster order by uid", {}, [&](const Row& r) {
            if (euid) return;
            u32 ro = (u32)r.i("role_id");
            if (c.m.one("select count(*) from master_role a join master_role b on b.role_category_id_label = a.role_category_id_label "
                        "and b.rarity > a.rarity where a.id = ? and a.rarity = 5",
                        {ro})) {
                euid = (u64)r.i("uid");
                erole = ro;
            }
        });
        if (euid) {
            u32 cap = c.role_level_cap(RoleId(erole));
            c.st.q("update roster set level = ? where uid = ?", {cap, euid});
            c.m.q(
                "select * from master_role_evolution where rank = (select rank from master_role where id = ?) and rarity = 5 and "
                "category_type = (select category_type from master_role where id = ?)",
                {erole, erole}, [&](const Row& e) {
                    for (int k = 1; k <= 4; k++) {
                        std::string id = "master_item" + std::to_string(k) + "_id", num = "item" + std::to_string(k) + "_num";
                        if (e.i(id.c_str())) add_stock(c, (u32)e.i(id.c_str()), e.i(num.c_str()));
                    }
                });
            call(c, "EvolutionCharacter", {euid});
            u32 after = (u32)c.st.one("select role_id from roster where uid = ?", {euid});
            t.expect_eq((u32)c.m.one("select rarity from master_role where id = ?", {after}), 6u, "evolved to rarity 6");
            // (b) back to level 1 (uimsg_next_strongth: the client's text says the level restarts)
            t.expect_eq((u32)c.st.one("select level from roster where uid = ?", {euid}), 1u, "level 1 after evolution");
            if (c.role_level_cap(RoleId(after)) <= cap) t.fail("the cap didn't rise");
        } else {
            t.fail("no ★5 with a ★6 evolution in the roster");
        }

        // ---- AddStatusCharacter: a seed raises its stat, capped
        u32 seed = master_id(c, "item_seed_11");  // hp 5
        add_stock(c, seed, 3);
        call(c, "AddStatusCharacter", {uid, seed, 3});
        u32 hp_max = (u32)c.m.one("select hp_add_max from master_role where id = ?", {role});
        t.expect_eq((u32)c.st.one("select add_hp from roster where uid = ?", {uid}), std::min(15u, hp_max), "seed hp");
        c.st.exec("commit");
    });
    if (!ran) return;  // no 3.7.0 master or save
}

}  // namespace
}  // namespace soa::server
