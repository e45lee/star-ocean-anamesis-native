// Unit tests of the item APIs (api/items/items.cpp), on a scratch server seeded from the test seed
// save with the 3.7.0 master. Run in --selftest; not differential (the server has no guest
// counterpart). Moved from the growth tests (growth/apis); their pure rules are tested in
// rules/growth_rules_tests.cpp.
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

}  // namespace
}  // namespace soa::server
