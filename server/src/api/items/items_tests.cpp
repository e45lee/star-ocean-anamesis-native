// Unit tests of the item APIs (api/items/items.cpp), on a scratch server seeded from the test seed
// save with the 3.7.0 master. Run in --selftest; not differential (the server has no guest
// counterpart). Moved from the growth tests (growth/apis); their pure rules are tested in
// rules/growth_rules_tests.cpp.
#include <cmath>
#include <random>

#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "soaserver/msgpack.h"
#include "core/errors.h"
#include "rules/growth_rules.h"
#include "testing/scratch.h"

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
        // (a) a copy of the same weapon: limit break +1; (b) points from the rule: (1 + 100) x 2000
        // / 100 = 2020 (3030 on a big success) against next_level_boosted_point 2000: level 2
        t.expect_eq((u32)c.st.one("select limit_break from items where uid = ?", {w[0]}), 1u, "compose limit break");
        u32 pts = (u32)c.st.one("select exp from items where uid = ?", {w[0]});
        if (pts != 20 && pts != 1030) t.fail("compose points within level 2: %u", pts);
        t.expect_eq((u32)c.st.one("select level from items where uid = ?", {w[0]}), 2u, "compose level");
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

// ItemCompose's FOL is use_fol_one of each material's rarity, summed (the strengthening screen's
// 必要FOL, CItemStrengtheningPotal::InitializePotal), not of the base's: a rarity-5 base fed a
// rarity-4 and a rarity-1 weapon costs 6000 + 500; an accessory base reads the accessory table.
NATIVE_TEST("items/compose-fol") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        add_fol(c, 10000000);
        auto grant_one = [&](u32 type, u32 rarity) -> u64 {
            // not a strengthening material (a hammer that doesn't fit would be refused)
            u32 id = (u32)c.m.one(
                "select i.id from master_item i left join master_weapon w on w.id = i.master_weapon_id left join master_weapon_kind k "
                "on k.id = w.master_weapon_kind_id where i.type = ? and i.rarity = ? and instr(ifnull(k.id_label, ''), 'W99St') = 0 "
                "order by i.id limit 1",
                {type, rarity});
            Value items = Value::array(), stocks = Value::array(), chars = Value::array();
            c.grant(1, id, 1, items, stocks, chars);  // content type 1: an item
            return items.arr.empty() ? 0 : items.arr[0].get_u("id");
        };
        auto use_fol = [&](const char* table, u32 rarity) {
            return (u32)c.m.one(std::string("select use_fol_one from ") + table + " where rarity = ?", {rarity});
        };
        u64 base = grant_one(1, 5), m4 = grant_one(1, 4), m1 = grant_one(1, 1);
        if (!base || !m4 || !m1) return t.fail("weapons not granted");
        u32 f0 = fol(c);
        call(c, "ItemCompose", {base}, {{m4, m1}});
        t.expect_eq(f0 - fol(c), use_fol("master_item_compose", 4) + use_fol("master_item_compose", 1), "weapon: the materials' rarities");
        t.expect_eq(use_fol("master_item_compose", 4) + use_fol("master_item_compose", 1), 6500u, "6000 + 500 (the 3.7.0 master)");
        u64 abase = grant_one(3, 5), a4 = grant_one(3, 4);
        if (!abase || !a4) return t.fail("accessories not granted");
        u32 f1 = fol(c);
        call(c, "ItemCompose", {abase}, {{a4}});
        t.expect_eq(f1 - fol(c), use_fol("master_item_accessory_compose", 4), "accessory: the material's rarity");
        c.st.exec("rollback");
    });
    if (!ran) return;  // no 3.7.0 master or save
}

// ItemCompose grants the strengthening screen's preview (docs/server-rules.md#items-and-stamina):
// each material adds (its level + 100) x boosted_point of its rarity / 100
// (CItemStrengtheningPotal::GetAddBoostedPoint), whatever boosted points it carries itself; the base
// levels per ItemModel::_CalcLevel (the points within the level, 0 at the cap). The test's rng is
// stepped past a big success before each compose (the preview never shows one), and one compose is
// a big success on purpose.
NATIVE_TEST("items/compose-points") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        add_fol(c, 100000000);
        const double up = global_f(c, "weapon_compose_up_rate", 11.5) * 100.0;
        // the next compose's big-success draw (items.cpp compose: the one rng draw)
        auto next_big = [&] {
            std::mt19937_64 peek = *c.rng;
            return (double)(peek() % 10000) < up;
        };
        auto no_big = [&] {
            while (next_big()) (*c.rng)();
        };
        auto grant_one = [&](u32 type, u32 rarity, u32 skip = 0) -> u64 {
            // not a strengthening material (a hammer that doesn't fit would be refused)
            u32 id = (u32)c.m.one(
                "select i.id from master_item i left join master_weapon w on w.id = i.master_weapon_id left join master_weapon_kind k "
                "on k.id = w.master_weapon_kind_id where i.type = ? and i.rarity = ? and instr(ifnull(k.id_label, ''), 'W99St') = 0 "
                "order by i.id limit 1 offset ?",
                {type, rarity, skip});
            Value items = Value::array(), stocks = Value::array(), chars = Value::array();
            c.grant(1, id, 1, items, stocks, chars);  // content type 1: an item
            return items.arr.empty() ? 0 : items.arr[0].get_u("id");
        };
        auto bp = [&](const char* table, u32 rarity) {
            return (u32)c.m.one(std::string("select boosted_point from ") + table + " where rarity = ?", {rarity});
        };
        auto level_points = [&](u64 uid) { return (u32)c.st.one("select level * 1000000 + exp from items where uid = ?", {uid}); };
        // the ComposeResult of a compose of `materials` into `base`
        auto compose = [&](u64 base, std::vector<u64> materials) {
            std::vector<u8> out = call(c, "ItemCompose", {base}, {materials});
            Value d = out.empty() ? Value() : mp_decode(out);
            const Value* data = d.find("data");
            const Value* cr = data ? data->find("ComposeResult") : nullptr;
            return cr ? *cr : Value();
        };
        t.expect_eq(bp("master_item_compose", 4), 5000u, "the 3.7.0 master: rarity 4 boosted_point 5000");

        // a fresh rarity-4 material into a rarity-5 weapon: the preview's 5050 / 10000
        u64 base = grant_one(1, 5), m4 = grant_one(1, 4), m3 = grant_one(1, 3), m5 = grant_one(1, 5, 1);
        if (!base || !m4 || !m3 || !m5) return t.fail("weapons not granted");
        no_big();
        Value cr = compose(base, {m4});
        t.expect_eq((u32)cr.get_u("after_boosted_point"), 5050u, "★4 level 1: (1 + 100) x 5000 / 100 = 5050");
        t.expect_eq((u32)cr.get_u("after_level"), 1u, "still level 1 (next 10000)");
        t.expect_eq(level_points(base), 1u * 1000000 + 5050, "stored");
        // ★3 and ★5 together: 2020 + 10100, past 10000: level 2 with 5050 + 12120 - 10000
        no_big();
        cr = compose(base, {m3, m5});
        t.expect_eq((u32)cr.get_u("before_boosted_point"), 5050u, "before: the points within level 1");
        t.expect_eq((u32)cr.get_u("after_level"), 2u, "several materials: a level up");
        t.expect_eq((u32)cr.get_u("after_boosted_point"), 5050u + 2020 + 10100 - 10000, "the rest carried into level 2");
        t.expect_eq(level_points(base), 2u * 1000000 + 7170, "stored");

        // a levelled material that carries boosted points: its level counts, its points don't
        u64 base2 = grant_one(1, 5, 2), lv = grant_one(1, 4, 1);
        if (!base2 || !lv) return t.fail("weapons not granted");
        c.st.q("update items set level = 7, exp = 4321 where uid = ?", {lv});
        no_big();
        cr = compose(base2, {lv});
        t.expect_eq((u32)cr.get_u("after_boosted_point"), 5350u, "★4 level 7: (7 + 100) x 5000 / 100 = 5350; its 4321 points ignored");

        // an accessory base reads the accessory table (the same boosted_point in 3.7.0)
        u64 abase = grant_one(3, 5), a4 = grant_one(3, 4);
        if (!abase || !a4) return t.fail("accessories not granted");
        no_big();
        cr = compose(abase, {a4});
        t.expect_eq((u32)cr.get_u("after_boosted_point"), bp("master_item_accessory_compose", 4) * 101 / 100, "accessory: ★4 level 1");

        // the cap: a level-9 weapon (cap 10) gains a level and keeps 0, the rest is lost
        u64 base3 = grant_one(1, 4, 2), big = grant_one(1, 5, 3), more = grant_one(1, 1);
        if (!base3 || !big || !more) return t.fail("weapons not granted");
        c.st.q("update items set level = 9, exp = 4000 where uid = ?", {base3});
        no_big();
        cr = compose(base3, {big});
        t.expect_eq((u32)cr.get_u("after_level"), 10u, "the cap reached");
        t.expect_eq((u32)cr.get_u("after_boosted_point"), 0u, "0 points at the cap");
        no_big();
        cr = compose(base3, {more});
        t.expect_eq(level_points(base3), 10u * 1000000, "at the cap nothing is added");

        // a big success: x weapon_compose_bonus_rate, truncated (the preview doesn't show it)
        u64 base4 = grant_one(1, 5, 4), m4b = grant_one(1, 4, 2);
        if (!base4 || !m4b) return t.fail("weapons not granted");
        while (!next_big()) (*c.rng)();
        cr = compose(base4, {m4b});
        const Value* is_big = cr.find("is_big_success");
        t.expect_eq(is_big && is_big->b, true, "a big success");
        t.expect_eq((u32)cr.get_u("after_boosted_point"), (u32)std::floor(5050 * global_f(c, "weapon_compose_bonus_rate", 1.5)), "5050 x 1.5 = 7575");
        c.st.exec("rollback");
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

// Limit-break items ("hammers", master_weapon_limit_break / master_accessory_limit_break) fed to
// ItemCompose (CItemStrengtheningList::IsAvailableLimitBreak, GetAddLimitReleaseWeaponNum): a
// generic hammer on its weapon kind (also a family weapon of that kind), ALL on any weapon, a
// family hammer on its family, the thread on an accessory; one that doesn't fit is refused and
// nothing changes; raises stop at the cap but the hammer is still consumed.
NATIVE_TEST("items/limit-break-items") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        add_fol(c, 100000000);
        auto weapon_of_kind = [&](const char* kind) {
            return (u32)c.m.one(
                "select i.id from master_item i join master_weapon w on w.id = i.master_weapon_id join master_weapon_kind k on "
                "k.id = w.master_weapon_kind_id where i.type = 1 and i.rarity = 3 and k.id_label = ? and i.limitbreak_type_id is null "
                "order by i.id limit 1",
                {std::string(kind)});
        };
        u32 sword = weapon_of_kind("W01Sw"), bow = weapon_of_kind("W07Bw");
        u32 nier_sword = master_id(c, "item_W01Sw_48");
        u32 sword_hammer = master_id(c, "item_weapon_limit_break_04"), all_hammer = master_id(c, "item_weapon_limit_break_35");
        u32 nier_hammer = master_id(c, "item_weapon_limit_break_34"), thread = master_id(c, "item_acce_limit_break_01");
        u32 accessory = (u32)c.m.one("select id from master_item where type = 3 and rarity = 3 order by id limit 1", {});
        if (!sword || !bow || !nier_sword || !sword_hammer || !all_hammer || !nier_hammer || !thread || !accessory)
            return t.fail("master rows missing");
        auto grant = [&](u32 item, u32 n) {
            Value items = Value::array(), stocks = Value::array(), chars = Value::array();
            c.grant(1, item, n, items, stocks, chars);
            std::vector<u64> uids;
            for (auto& e : items.arr) uids.push_back(e.get_u("id"));
            if (uids.size() != n) t.fail("granted %zu of item %u", uids.size(), item);
            return uids;
        };
        auto lb = [&](u64 uid) { return (u32)c.st.one("select limit_break from items where uid = ?", {uid}); };
        auto owned = [&](u64 uid) { return c.st.one("select count(*) from items where uid = ?", {uid}) != 0; };
        u64 s = grant(sword, 1)[0], b = grant(bow, 1)[0], n = grant(nier_sword, 1)[0], a = grant(accessory, 1)[0];
        auto sh = grant(sword_hammer, 3), ah = grant(all_hammer, 2), nh = grant(nier_hammer, 2), th = grant(thread, 1);
        if (t.failures()) return;
        // generic hammer on a weapon of its kind: one raise, consumed, counted
        int64_t raises = counter(c, "weapon_limit_break");
        call(c, "ItemComposeArray", {s}, {{sh[0]}});
        t.expect_eq(lb(s), 1u, "片手剣ハンマー on a sword");
        t.expect_eq(!owned(sh[0]), true, "the hammer is consumed");
        t.expect_eq(counter(c, "weapon_limit_break"), raises + 1, "the raise counted (type 6)");
        // the same generic hammer on a family weapon of that kind (W01Sw, type_nier)
        call(c, "ItemComposeArray", {n}, {{sh[1]}});
        t.expect_eq(lb(n), 1u, "片手剣ハンマー on a NieR sword");
        // a family hammer on its family; ALL on a bow
        call(c, "ItemComposeArray", {n}, {{nh[0]}});
        t.expect_eq(lb(n), 2u, "NieR hammer on a NieR sword");
        call(c, "ItemComposeArray", {b}, {{ah[0]}});
        t.expect_eq(lb(b), 1u, "マジカルハンマー (ALL) on a bow");
        // the thread on an accessory
        call(c, "ItemComposeArray", {a}, {{th[0]}});
        t.expect_eq(lb(a), 1u, "マジカルスレッド on an accessory");
        t.expect_eq(counter(c, "accessory_limit_break"), (int64_t)1, "the accessory raise counted");
        // hammers that don't fit: refused, nothing consumed or charged
        u32 f = fol(c);
        call(c, "ItemComposeArray", {b}, {{sh[2]}});
        call(c, "ItemComposeArray", {s}, {{nh[1]}});
        t.expect_eq(lb(b), 1u, "片手剣ハンマー on a bow: no raise");
        t.expect_eq(lb(s), 1u, "NieR hammer on a plain sword: no raise");
        t.expect_eq(owned(sh[2]) && owned(nh[1]), true, "refused hammers kept");
        t.expect_eq(fol(c), f, "refused composes cost nothing");
        // at the cap: the hammer is consumed, no raise counted
        u32 lb_max = (u32)c.m.one("select max(limit_break) from master_item_limit_break_level_max where type = 1", {});
        c.st.q("update items set limit_break = ? where uid = ?", {lb_max, b});
        raises = counter(c, "weapon_limit_break");
        call(c, "ItemComposeArray", {b}, {{ah[1]}});
        t.expect_eq(lb(b), lb_max, "capped");
        t.expect_eq(!owned(ah[1]), true, "consumed at the cap");
        t.expect_eq(counter(c, "weapon_limit_break"), raises, "no raise past the cap");
        c.st.exec("rollback");
    });
    if (!ran) return;  // no 3.7.0 master or save
}

// InheritAccessory (docs/server-rules.md#accessory-inheritance): a compose of an inheritance
// accessory (master_item.max_inheritance_num) that also takes in its ordinary material's master item
// and limit break, once; the material is used up, the base gains its points and the FOL is paid; the
// answer's InheritResultInfo / ComposeResult, and the Item list's InheritItemInfo (on this and every
// later load); counted for achievement type 58. A base that can't inherit, a second inheritance,
// the base itself, another inheritance accessory and a locked accessory are refused.
// UpdateItemStock is refused at item_stock_max.
NATIVE_TEST("items/inherit-accessory") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    RequestContext rc = sv.new_request();
    Ctx c = sv.make_ctx(rc);
    const u32 inherit = (u32)c.m.one("select id from master_item where type = 3 and max_inheritance_num > 0 order by id limit 1", {});
    const u32 plain =
        (u32)c.m.one("select id from master_item where type = 3 and max_inheritance_num is null and rarity = 3 order by id limit 1", {});
    if (!inherit || !plain) return t.fail("no accessories in the master");
    auto grant_one = [&](u32 id) {
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        c.grant(1, id, 1, items, stocks, chars);
        return items.arr.empty() ? (u64)0 : items.arr[0].get_u("id");
    };
    const u32 inherit2 =
        (u32)c.m.one("select id from master_item where type = 3 and max_inheritance_num > 0 and id != ? order by id limit 1", {inherit});
    const u64 base = grant_one(inherit), lost = grant_one(plain), other = grant_one(plain), plain_base = grant_one(plain),
              base2 = grant_one(inherit2);
    if (!base || !lost || !other || !plain_base || !base2) return t.fail("granting accessories");
    add_fol(c, 10000000);
    const u32 fol0 = fol(c);
    c.st.q("update items set limit_break = 2 where uid = ?", {lost});
    t.expect_eq(S.call({"InheritAccessory", 0xd9feb3e8, {plain_base, lost}, {}, {}}), (u32)ErrorCode::kItemUnusable,
                "(a) max_inheritance_num 0: refused");
    t.expect_eq(S.call({"InheritAccessory", 0xd9feb3e8, {base, base}, {}, {}}), (u32)ErrorCode::kItemUnusable, "the base itself: refused");
    t.expect_eq(S.call({"InheritAccessory", 0xd9feb3e8, {base, base2}, {}, {}}), (u32)ErrorCode::kItemUnusable,
                "(b) another inheritance accessory: refused");
    c.st.q("update items set locked = 1 where uid = ?", {lost});
    t.expect_eq(S.call({"InheritAccessory", 0xd9feb3e8, {base, lost}, {}, {}}), (u32)ErrorCode::kLockedItem, "a locked one: refused");
    c.st.q("update items set locked = 0 where uid = ?", {lost});
    std::vector<u8> out;
    t.expect_eq(S.call({"InheritAccessory", 0xd9feb3e8, {base, lost}, {}, {}}, &out), 0u, "inherited");
    Value d = out.empty() ? Value() : mp_decode(out);
    const Value* data = d.find("data");
    const Value* r = data ? data->find("InheritResultInfo") : nullptr;
    t.expect_eq(r ? r->get_u("base_player_item_id") : 0, base, "InheritResultInfo.base_player_item_id");
    t.expect_eq(r ? r->get_u("lost_master_item_id") : 0, (u64)plain, "lost_master_item_id");
    t.expect_eq(r ? r->get_u("lost_player_item_id") : 0, lost, "lost_player_item_id");
    t.expect_eq(r ? r->get_u("lost_item_limit_break_count") : 9, (u64)2, "lost_item_limit_break_count");
    const Value* cr = data ? data->find("ComposeResult") : nullptr;
    t.expect_eq(cr && cr->get_u("after_boosted_point") > cr->get_u("before_boosted_point"), true, "(b) the base gains the compose's points");
    t.expect_eq((u32)c.st.one("select exp from items where uid = ?", {base}), cr ? (u32)cr->get_u("after_boosted_point") : 0u, "stored");
    t.expect_eq(fol(c) < fol0, true, "(b) the compose's FOL paid");
    t.expect_eq((u32)c.st.one("select count(*) from items where uid = ?", {lost}), 0u, "the lost accessory is gone");
    t.expect_eq((u32)c.st.one("select inherited_master_item_id from items where uid = ?", {base}), plain, "stored");
    t.expect_eq((u32)c.st.one("select inherited_limit_break from items where uid = ?", {base}), 2u, "its limit break stored");
    auto inherit_info = [&](const Value& list, u64 uid) -> const Value* {
        for (const Value& item : list.arr)
            if (item.get_u("id") == uid) return item.find("InheritItemInfo");
        return nullptr;
    };
    const Value items = c.items();
    const Value* info = inherit_info(items, base);
    t.expect_eq(info ? info->get_u("inherited_master_item_id") : 0, (u64)plain, "Item[base].InheritItemInfo on a load");
    t.expect_eq(info ? info->get_u("inherited_master_item_limit_break_count") : 0, (u64)2, "and its limit break");
    t.expect_eq(inherit_info(items, other) == nullptr, true, "other items carry none");
    t.expect_eq(counter(c, "accessory_inherit"), (int64_t)1, "counted (achievement type 58)");
    t.expect_eq(S.call({"InheritAccessory", 0xd9feb3e8, {base, other}, {}, {}}), (u32)ErrorCode::kItemUnusable, "(b) a second inheritance: refused");
    t.expect_eq((u32)c.st.one("select count(*) from items where uid = ?", {other}), 1u, "nothing taken");
    // UpdateItemStock: Player.item_stock is item_stock_max already
    t.expect_eq(S.call({"UpdateItemStock", 0xcf39cc5c, {}, {}, {}}), (u32)ErrorCode::kLimitReached, "UpdateItemStock refused at the max");
}

// ItemGradeUpArray and MaterialCompose's refusals (the replay corpora api-sweep and items-party
// refuse them): no base weapon 10208; an unknown recipe 10208, too few materials 10206.
NATIVE_TEST("items/grade-up-and-material-compose-refusals") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        call(c, "ItemGradeUpArray", {}, {{}});
        t.expect_eq(code, 10208u, "ItemGradeUpArray without a base weapon");
        code = 0;
        u32 accessory = (u32)c.m.one("select id from master_item where type = 3 order by id limit 1", {});
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        c.grant(1, accessory, 1, items, stocks, chars);
        call(c, "ItemGradeUpArray", {items.arr.at(0).get_u("id")}, {{}});
        t.expect_eq(code, 10208u, "ItemGradeUpArray on an accessory");
        code = 0;
        call(c, "MaterialCompose", {0xfffffff0u, 1});
        t.expect_eq(code, 10208u, "MaterialCompose of an unknown recipe");
        code = 0;
        u32 recipe = (u32)c.m.one("select id from master_material_compose where master_item1_id > 0 and item1_num > 0 order by id limit 1", {});
        if (!recipe) return t.fail("no master_material_compose row");
        u32 item1 = (u32)c.m.one("select master_item1_id from master_material_compose where id = ?", {recipe});
        c.st.q("delete from stock where master_item_id = ?", {item1});
        call(c, "MaterialCompose", {recipe, 1});
        t.expect_eq(code, 10206u, "MaterialCompose without its materials");
    });
    if (!ran) return;  // no 3.7.0 master or save
}

}  // namespace
}  // namespace soa::server
