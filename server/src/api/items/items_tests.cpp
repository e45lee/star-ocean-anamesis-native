// Unit tests of the item APIs (api/items/items.cpp), on a scratch server seeded from the test seed
// save with the 3.7.0 master. Run in --selftest; not differential (the server has no guest
// counterpart). Moved from the growth tests (growth/apis); their pure rules are tested in
// rules/growth_rules_tests.cpp.
#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "rules/growth_rules.h"

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

// ItemComposeArray (a copy: the limit break), LockItemArray / SellItemArray / UnlockItemArray,
// SellStackItem, UseHealItem and StaminaHeal.
NATIVE_TEST("items/apis") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        add_fol(c, 10000000);
        // ---- compose, lock, sell
        u32 weapon = (u32)c.m.one("select id from master_item where type = 1 and rarity = 3 and sale_fol > 0 order by id limit 1", {});
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        c.grant(1, weapon, 3, items, stocks, chars);
        std::vector<u64> w;
        for (auto& e : items.arr) w.push_back(e.get_u("id"));
        if (w.size() != 3) return t.fail("granted %zu weapons", w.size());
        u32 f3 = fol(c);
        call(c, "ItemComposeArray", {w[0]}, {{w[1]}});
        // (a) a copy of the same weapon: limit break +1; points from the rule
        t.expect_eq((u32)c.st.one("select limit_break from items where uid = ?", {w[0]}), 1u, "compose limit break");
        u32 pts = (u32)c.st.one("select exp from items where uid = ?", {w[0]});
        if (pts != 2000 && pts != 3000) t.fail("compose points %u", pts);
        t.expect_eq((u32)c.st.one("select count(*) from items where uid = ?", {w[1]}), 0u, "material consumed");
        t.expect_eq(fol(c), f3 - 3000, "compose FOL (rarity 3 use_fol_one)");
        call(c, "LockItemArray", {}, {{w[2]}});
        u32 f4 = fol(c);
        call(c, "SellItemArray", {}, {{w[2]}});
        t.expect_eq(fol(c), f4, "a locked item isn't sold");
        call(c, "UnlockItemArray", {}, {{w[2]}});
        call(c, "SellItemArray", {}, {{w[2]}});
        u32 sale = (u32)c.m.one("select sale_fol from master_item where id = ?", {weapon});
        t.expect_eq(fol(c), f4 + gr::sell_price(sale, 1.0), "sell price at level 1");
        // ---- stack items: SellStackItem
        u32 exp_item = (u32)c.m.one("select id from master_item where id_label like 'item_exp_%' and rarity = 3 order by id limit 1", {});
        add_stock(c, exp_item, 2);
        u32 f5 = fol(c), s5 = stock_count(c, exp_item);
        call(c, "SellStackItem", {exp_item, 1});
        t.expect_eq(stock_count(c, exp_item), s5 - 1, "stack sold");
        t.expect_eq(fol(c), f5 + (u32)c.m.one("select sale_fol from master_item where id = ?", {exp_item}), "stack sale FOL");

        // ---- stamina: heal items and coins
        c.st.q("update player set stamina = 0, stamina_at = ?", {c.now()});
        u32 heal50 = master_id(c, "item_heal_50");
        add_stock(c, heal50, 2);
        call(c, "UseHealItem", {heal50, 2});
        t.expect_eq((u32)c.st.one("select stamina from player", {}), 100u, "two item_heal_50");
        u32 coins = (u32)c.st.one("select free_coin from player", {});
        call(c, "StaminaHeal", {});
        u32 lv = (u32)c.st.one("select level from player", {});
        t.expect_eq((u32)c.st.one("select stamina from player", {}), 100u + c.stamina_max(lv), "coin refill adds the max");
        t.expect_eq((u32)c.st.one("select free_coin from player", {}), coins - 100, "stamina_use_coin");
        c.st.exec("commit");
    });
    if (!ran) return;  // no 3.7.0 master or save
}

// Achievement type 6 (武器を N回上限解放する) counts limit-break raises, one per copy fed
// (CItemStrengtheningPotal::GetAddLimitReleaseWeaponNum), not composes; type 5 counts composes.
NATIVE_TEST("items/limit-break-achievement") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        add_fol(c, 10000000);
        u32 weapon = (u32)c.m.one("select id from master_item where type = 1 and rarity = 3 order by id limit 1", {});
        u32 other = (u32)c.m.one("select id from master_item where type = 1 and rarity = 3 and id <> ? order by id limit 1", {weapon});
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        c.grant(1, weapon, 6, items, stocks, chars);
        c.grant(1, other, 1, items, stocks, chars);
        std::vector<u64> w, o;
        for (auto& e : items.arr) (e.get_u("master_item_id") == weapon ? w : o).push_back(e.get_u("id"));
        if (w.size() != 6 || o.size() != 1) return t.fail("granted %zu + %zu weapons", w.size(), o.size());
        // the type 6 row with the smallest goal that the active list holds (the achievement state)
        int64_t row = 0, goal = 0;
        Value state = achievement_state(c);
        c.m.q("select id, goal_count from master_achievement where type = 6 order by goal_count, id", {}, [&](const Row& r) {
            if (row || !state.find(std::to_string(r.i("id")))) return;
            row = r.i("id");
            goal = r.i("goal_count");
        });
        auto progress = [&]() -> int64_t {
            Value now = achievement_state(c);
            const Value* info = now.find(std::to_string(row));
            return info ? (int64_t)info->get_u("count") : -1;
        };
        // two copies at once: two raises, one compose
        call(c, "ItemComposeArray", {w[0]}, {{w[1], w[2]}});
        t.expect_eq((u32)c.st.one("select limit_break from items where uid = ?", {w[0]}), 2u, "two copies: limit break 2");
        t.expect_eq(counter(c, "weapon_limit_break"), (int64_t)2, "two raises counted");
        t.expect_eq(counter(c, "weapon_boost"), (int64_t)1, "one compose counted");
        if (row) t.expect_eq(progress(), std::min<int64_t>(2, goal), "type 6 progress = the raises");
        // another weapon fed: a boost, no raise
        call(c, "ItemComposeArray", {w[0]}, {{o[0]}});
        t.expect_eq(counter(c, "weapon_limit_break"), (int64_t)2, "no raise without a copy");
        t.expect_eq(counter(c, "weapon_boost"), (int64_t)2, "the compose counted");
        if (row) t.expect_eq(progress(), std::min<int64_t>(2, goal), "type 6 unchanged by a plain compose");
        // at the cap: only the raises applied count
        u32 lb_max = (u32)c.m.one("select max(limit_break) from master_item_limit_break_level_max where type = 1", {});
        c.st.q("update items set limit_break = ? where uid = ?", {lb_max - 1, w[0]});
        call(c, "ItemComposeArray", {w[0]}, {{w[3], w[4]}});
        t.expect_eq((u32)c.st.one("select limit_break from items where uid = ?", {w[0]}), lb_max, "capped");
        t.expect_eq(counter(c, "weapon_limit_break"), (int64_t)3, "one raise up to the cap");
        if (!row) t.fail("no active type 6 achievement to check");
        c.st.exec("rollback");
    });
    if (!ran) return;  // no 3.7.0 master or save
}

}  // namespace
}  // namespace soa::server
