// Unit tests of the gear APIs (api/items/gear.cpp), each on a scratch server seeded from the test
// seed save with the 3.7.0 master. Run in --selftest; not differential (the server has no guest
// counterpart).
#include "soaserver/native_test.h"
#include "soaserver/ext.h"
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
// A new weapon item in the state (the core's items table), returns its uid.
u64 add_weapon(Ctx& c, u32 master_item, u32 level = 1) {
    u64 uid = (u64)c.st.one("select ifnull(max(uid), 0) + 1 from items", {});
    c.st.q("insert into items (uid, master_item_id, item_type, level, created_at) values (?,?,1,?,0)", {uid, master_item, level});
    return uid;
}

NATIVE_TEST("items/gear-apis") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        // ---- grants: content type 15 (a gear item) and 98 (gear lottery gear_drop_1)
        Value items, stocks, chars;
        u32 gitem = (u32)c.m.one(
            "select i.id from master_item i join master_gear g on g.id = i.master_gear_id "
            "join master_weapon w on w.master_weapon_kind_id = g.master_weapon_kind_id "
            "join master_item wi on wi.master_weapon_id = w.id and wi.max_gear_slot_num >= 2 "
            "where i.type = 15 and g.add_param_type1 = 1 order by i.id limit 1",
            {});
        c.grant(15, gitem, 2, items, stocks, chars);
        t.expect_eq((u32)c.st.one("select count(*) from gear_items where master_item_id = ?", {gitem}), 2u, "gear granted x2");
        c.grant(98, (u32)c.m.one("select category_id from master_gear_lottery where category_id_label = 'gear_drop_1' limit 1", {}), 1, items, stocks,
                chars);
        t.expect_eq((u32)c.st.one("select count(*) from gear_items", {}), 3u, "gear lottery granted one");
        // ---- GetGearInfo lists them (CGearInfo fields)
        if (call(c, "GetGearInfo", {}).empty()) t.fail("GetGearInfo");
        // ---- AttachGear: a weapon of the gear's kind with 2 slots
        u32 kind =
            (u32)c.m.one("select g.master_weapon_kind_id from master_item i join master_gear g on g.id = i.master_gear_id where i.id = ?", {gitem});
        u32 witem = (u32)c.m.one(
            "select i.id from master_item i join master_weapon w on w.id = i.master_weapon_id "
            "where w.master_weapon_kind_id = ? and i.max_gear_slot_num >= 2 order by i.id limit 1",
            {kind});
        u64 wuid = add_weapon(c, witem);
        c.st.q("update items set limit_break = 5 where uid = ?", {wuid});  // (b) the gears' limit-break condition
        u64 g1 = (u64)c.st.one("select min(uid) from gear_items where master_item_id = ?", {gitem});
        u64 g2 = (u64)c.st.one("select max(uid) from gear_items where master_item_id = ?", {gitem});
        add_fol(c, 100000);
        u32 f0 = fol(c);
        code = 0;
        call(c, "AttachGear", {wuid, g1, 0});
        t.expect_eq(code, 0u, "attach accepted");
        t.expect_eq(fol(c), f0 - 10000, "attach costs attach_gear_coin FOL");
        t.expect_eq((u64)c.st.one("select item_uid from gear_items where uid = ?", {g1}), wuid, "attached");
        // the weapon's Item entry carries AttachedGearInfoList with the gear's master_gear bonus
        Value iv = c.items();
        bool seen = false;
        for (auto& e : iv.arr) {
            const Value* id = e.find("id");
            if (!id || id->u != wuid) continue;
            const Value* a = e.find("AttachedGearInfoList");
            if (!a || a->arr.size() != 1) break;
            const Value* ty = a->arr[0].find("add_param_type1");
            seen = ty && ty->u == 1;
        }
        if (!seen) t.fail("Item.AttachedGearInfoList missing");
        // over the same slot: the old gear is destroyed
        call(c, "AttachGear", {wuid, g2, 0});
        t.expect_eq((u32)c.st.one("select count(*) from gear_items where uid = ?", {g1}), 0u, "overwritten gear destroyed");
        // refused: a weapon below the gear's limit-break condition (master_gear.limit_break_conditions)
        if (c.m.one("select ifnull(g.limit_break_conditions, 0) from master_item i join master_gear g on g.id = i.master_gear_id where i.id = ?",
                    {gitem}) > 0) {
            u64 low = add_weapon(c, witem);
            Value a1, b1, c1;
            c.grant(15, gitem, 1, a1, b1, c1);
            u64 gx = (u64)c.st.one("select max(uid) from gear_items", {});
            code = 0;
            call(c, "AttachGear", {low, gx, 0});
            t.expect_eq(code, 10208u, "limit-break condition");
            c.st.q("delete from gear_items where uid = ?", {gx});
            c.st.q("delete from items where uid = ?", {low});
        }
        // refused: a slot the weapon doesn't have
        code = 0;
        u64 g3 = (u64)c.st.one("select uid from gear_items where master_item_id != ? limit 1", {gitem});
        call(c, "AttachGear", {wuid, g3, 7});
        t.expect_eq(code, 10208u, "no such slot");
        // ---- RemoveGear: needs item_grease
        code = 0;
        call(c, "RemoveGear", {g2});
        t.expect_eq(code, 10206u, "no grease");
        add_stock(c, master_id(c, "item_grease"), 1);
        code = 0;
        call(c, "RemoveGear", {wuid});  // (b) the screen sends the weapon
        t.expect_eq(code, 0u, "remove accepted");
        t.expect_eq(c.st.one("select count(*) from gear_items where uid = ? and item_uid is null and slot = 0", {g2}), (int64_t)1,
                    "detached: in the gear box (item_uid NULL)");
        t.expect_eq(stock_count(c, master_id(c, "item_grease")), 0u, "grease used");
        // ---- SellGear: sale_fol
        u32 f1 = fol(c);
        u32 price = (u32)c.m.one("select sale_fol from master_item where id = ?", {gitem});
        call(c, "SellGear", {}, {{g2}});
        t.expect_eq(fol(c), f1 + price, "sold for sale_fol");
        // ---- GenerateGear: two weapons as materials -> one gear of the base's kind, materials gone
        u64 base = add_weapon(c, witem, 5);
        u64 m1 = add_weapon(c, witem), m2 = add_weapon(c, witem);
        u32 before = (u32)c.st.one("select count(*) from gear_items", {});
        u32 f2 = fol(c);
        code = 0;
        call(c, "GenerateGear", {base, 0}, {{m1, m2}});
        t.expect_eq(code, 0u, "generate accepted");
        t.expect_eq(fol(c), f2 - 10000, "coin_for_generate_gears FOL");
        u32 after = (u32)c.st.one("select count(*) from gear_items", {});
        if (after < before + 1) t.fail("no gear generated");
        t.expect_eq((u32)c.st.one("select count(*) from items where uid in (?,?,?)", {base, m1, m2}), 0u, "base and materials used");
        u64 ng = (u64)c.st.one("select max(uid) from gear_items where type = 0", {});
        u32 ng_item = (u32)c.st.one("select master_item_id from gear_items where uid = ?", {ng});
        t.expect_eq(
            (u32)c.m.one("select g.master_weapon_kind_id from master_item i join master_gear g on g.id = i.master_gear_id where i.id = ?", {ng_item}),
            kind, "generated gear of the base's weapon kind");
        // refused: nothing selected
        code = 0;
        call(c, "GenerateGear", {0, 0}, {{}});
        t.expect_eq(code, 10208u, "nothing to purify");
        // a weapon sold with a gear set in it: the gear goes with it (PLAN-schema S5: the state's
        // ON DELETE CASCADE, the rule gear_info_list applied by hand before)
        u64 sold = add_weapon(c, witem);
        Value a2, b2, c2;
        c.grant(15, gitem, 1, a2, b2, c2);
        u64 gs = (u64)c.st.one("select max(uid) from gear_items", {});
        c.st.q("update gear_items set item_uid = ?, slot = 0 where uid = ?", {sold, gs});
        code = 0;
        call(c, "SellItem", {}, {{sold}});
        t.expect_eq(code, 0u, "the weapon sold");
        t.expect_eq(c.st.one("select count(*) from gear_items where uid = ?", {gs}), (int64_t)0, "its gear gone with it");
        c.st.exec("rollback");
    });
    if (!ran) return;  // no 3.7.0 master or save
}

// The barney chance (api/items/gear.cpp "barney chance"): the mood drawn from the open
// master_gear_barney_chance group by mood_rate is sent as GearBarneyChanceInfo; GenerateGear
// raises the gear a rarity with the mood's mutation_rate and says so in is_barney_chance.
NATIVE_TEST("items/gear-barney-chance") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        auto chance_of = [&](const std::vector<u8>& b, u32& group, u32& type) {
            Value v = mp_decode(b);
            const Value* d = v.find("data");
            const Value* g = d ? d->find("GearBarneyChanceInfo") : nullptr;
            group = g && g->find("barney_chance_group_id") ? (u32)g->get_u("barney_chance_group_id") : 0;
            type = g && g->find("barney_chance_type") ? (u32)g->get_u("barney_chance_type") : 0;
            return g != nullptr;
        };
        // (a) outside every dated group: the undated default group, 70/25/5
        int64_t t0 = c.parse_time("2030-01-01 12:00:00");
        c.test.event_now = [t0] { return t0; };
        u32 def = (u32)c.m.one("select barney_chance_group_id from master_gear_barney_chance where opened_at is null or opened_at = '' limit 1", {});
        u32 n[4] = {0, 0, 0, 0};
        for (int k = 0; k < 300; k++) {
            c.st.q("delete from gear_barney", {});
            u32 g = 0, ty = 0;
            if (!chance_of(call(c, "GetGearInfo", {}), g, ty)) return t.fail("no GearBarneyChanceInfo");
            if (g != def) return t.fail("group %u, want the default %u", g, def);
            if (ty < 1 || ty > 3) return t.fail("type %u", ty);
            n[ty]++;
        }
        if (!(n[1] > n[2] && n[2] > n[3])) t.fail("mood draws %u/%u/%u, want 70/25/5-like", n[1], n[2], n[3]);
        // the mood is kept between requests
        u32 g1 = 0, ty1 = 0, g2 = 0, ty2 = 0;
        chance_of(call(c, "GetGearInfo", {}), g1, ty1);
        chance_of(call(c, "GetGearInfo", {}), g2, ty2);
        t.expect_eq(ty2, ty1, "mood kept");
        // (a) gear_20201126 (2020-11-26 14:30 .. 12-24): type 3 only (mood 100), mutation 100
        int64_t t1 = c.parse_time("2020-12-01 12:00:00");
        c.test.event_now = [t1] { return t1; };
        u32 ev = (u32)c.m.one(
            "select barney_chance_group_id from master_gear_barney_chance where barney_chance_group_id_label = 'gear_20201126' limit 1", {});
        chance_of(call(c, "GetGearInfo", {}), g1, ty1);
        t.expect_eq(g1, ev, "the dated group wins");
        t.expect_eq(ty1, 3u, "its only mood");
        u32 witem = (u32)c.m.one(
            "select i.id from master_item i join master_weapon w on w.id = i.master_weapon_id where i.type = 1 "
            "and i.rarity <= 2 order by i.id limit 1",
            {});
        add_fol(c, 1000000);
        int raised = 0;
        for (int k = 0; k < 5; k++) {
            u64 m1 = add_weapon(c, witem);
            code = 0;
            std::vector<u8> b = call(c, "GenerateGear", {0, 0}, {{m1}});
            t.expect_eq(code, 0u, "generate accepted");
            Value v = mp_decode(b);
            const Value* d = v.find("data");
            const Value* res = d ? d->find("GearGenerationInfoResult") : nullptr;
            if (!res) return t.fail("no GearGenerationInfoResult");
            t.expect_eq(res->find("barney_chance_type") ? (u32)res->get_u("barney_chance_type") : 0u, 3u, "result type");
            bool bc = res->find("is_barney_chance") && res->find("is_barney_chance")->b;
            u32 gitem = 0;  // the purified gear: the AddGearInfoList entry of type 0 (param1 = its item)
            if (const Value* a = res->find("AddGearInfoList"))
                for (auto& [k, g] : a->map)
                    if (g.find("type") && g.get_u("type") == 0 && g.find("param1")) gitem = (u32)g.get_u("param1");
            u32 rar = (u32)c.m.one("select rarity from master_item where id = ?", {gitem});
            if (bc) raised++;
            if (!bc && rar < 5) t.fail("mutation 100 but not raised (rarity %u)", rar);
            if (bc && rar < 2) t.fail("raised to rarity %u", rar);
            u32 g = 0, ty = 0;
            if (!chance_of(b, g, ty) || ty != 3) t.fail("next mood %u", ty);
        }
        if (!raised) t.fail("never raised");
        c.st.exec("rollback");
    });
    if (!ran) return;  // no 3.7.0 master or save
}

// UpdateGearStock: always refused with 11006 (the player's gear_stock is gear_stock_max already;
// the replay corpora api-sweep and items-party), nothing paid.
NATIVE_TEST("gear/update-gear-stock-refused") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        const int64_t coins = c.st.one("select free_coin + pay_coin from player", {});
        Value d = mp_decode(call(c, "UpdateGearStock", {}));
        t.expect_eq(code, 11006u, "refused with kLimitReached");
        t.expect_eq(c.st.one("select free_coin + pay_coin from player", {}), coins, "no coins taken");
        const Value* data = d.find("data");
        t.expect_eq(data && data->find("Player") != nullptr, true, "answers the player state");
    });
    if (!ran) return;  // no 3.7.0 master or save
}

}  // namespace
}  // namespace soa::server
