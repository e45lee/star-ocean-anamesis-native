// Unit tests of the growth module's APIs (run in --selftest; not differential: the
// server has no guest counterpart): each API on a scratch server seeded from the test seed save,
// against the 3.7.0 master data. Their pure rules are tested in rules/growth_rules_tests.cpp.
#include <cmath>
#include <ctime>

#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "rules/growth_rules.h"
#include "core/time.h"
#include "core/errors.h"
#include "soaserver/msgpack.h"
#include "testing/reply_shape.h"
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
            const std::vector<u8> evolved = call(c, "EvolutionCharacter", {euid});
            // (no replay corpus evolves a character: the reply's shape pinned here)
            t.expect_eq(data_shape(evolved, "EvolutionResult"),
                        std::string("{use_fol:u UseStockItem:[{master_item_id:u use_count:u}] UpdatePlayerCharacter:{id:u "
                                    "before_master_role_id:u after_master_role_id:u level:u is_rarity_7:u}}"),
                        "EvolutionResult's shape");
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

// EquipAuto (docs/server-rules.md#equip-auto): the strongest owned weapon of the role's kind and
// the strongest accessory that no other character wears (auto_equip_steal false), the empty skill
// slots filled with the role's open skills; the answer's EquipWeaponResult / EquipAccessoryResult /
// UpdateCharacterList; an unknown character is refused.
NATIVE_TEST("growth/equip-auto") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    RequestContext rc = sv.new_request();
    Ctx c = sv.make_ctx(rc);
    // a character whose role's weapon kind has weapons in the master
    u64 uid = 0;
    RoleId role;
    u32 kind = 0;
    c.st.q("select uid, role_id from roster order by uid", {}, [&](const Row& r) {
        if (uid) return;
        const u32 k = (u32)c.m.one("select master_weapon_kind_id from master_role where id = ?", {r.i("role_id")});
        if (c.m.one("select count(*) from master_item i join master_weapon w on w.id = i.master_weapon_id where i.type = 1 and "
                    "w.master_weapon_kind_id = ? and i.attack > 0",
                    {k}) >= 2) {
            uid = (u64)r.i("uid");
            role = r.id<RoleId>("role_id");
            kind = k;
        }
    });
    if (!uid) return t.fail("no character with weapons of its kind");
    const u64 other_chara = (u64)c.st.one("select uid from roster where uid != ? order by uid limit 1", {uid});
    auto weapon_of = [&](const char* order) {
        return (u32)c.m.one(std::string("select i.id from master_item i join master_weapon w on w.id = i.master_weapon_id where i.type = 1 and "
                                        "w.master_weapon_kind_id = ? and i.attack > 0 order by ifnull(i.attack, 0) + ifnull(i.intelligence, 0) ") +
                                order + ", i.id limit 1",
                            {kind});
    };
    const u32 weak = weapon_of("asc"), strong = weapon_of("desc");
    const u32 other_kind = (u32)c.m.one(
        "select i.id from master_item i join master_weapon w on w.id = i.master_weapon_id where i.type = 1 and w.master_weapon_kind_id != ? "
        "order by ifnull(i.attack, 0) + ifnull(i.intelligence, 0) desc limit 1",
        {kind});
    const u32 acc_weak = (u32)c.m.one(
        "select id from master_item where type = 3 order by ifnull(attack, 0) + ifnull(intelligence, 0) + ifnull(defence, 0) + ifnull(hit, 0) + ifnull(guard, 0) asc, id limit 1",
        {});
    const u32 acc_strong = (u32)c.m.one(
        "select id from master_item where type = 3 order by ifnull(attack, 0) + ifnull(intelligence, 0) + ifnull(defence, 0) + ifnull(hit, 0) + ifnull(guard, 0) desc, id limit 1",
        {});
    if (!weak || !strong || weak == strong || !other_kind) return t.fail("no weapons to compare");
    c.st.exec("delete from party_member where weapon_uid is not null or accessory_uid is not null");
    c.st.exec("update roster set weapon_uid = null, accessory_uid = null");
    c.st.exec("delete from items");
    auto grant_one = [&](u32 id) {
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        c.grant(1, id, 1, items, stocks, chars);
        return items.arr.empty() ? (u64)0 : items.arr[0].get_u("id");
    };
    const u64 w_weak = grant_one(weak), w_strong = grant_one(strong), w_other_kind = grant_one(other_kind), a_weak = grant_one(acc_weak),
              a_strong = grant_one(acc_strong);
    (void)w_other_kind;
    // the strongest accessory is worn by another character: not taken (auto_equip_steal false)
    c.st.q("update roster set accessory_uid = ? where uid = ?", {a_strong, other_chara});
    c.st.q("update roster set equip_skill1 = null, equip_skill2 = null, equip_skill3 = null where uid = ?", {uid});
    std::vector<u8> out;
    t.expect_eq(S.call({"EquipAuto", 0x7827ff6a, {uid}, {}, {}}, &out), 0u, "EquipAuto");
    t.expect_eq((u64)c.st.one("select weapon_uid from roster where uid = ?", {uid}), w_strong, "the strongest weapon of the role's kind");
    t.expect_eq((u64)c.st.one("select accessory_uid from roster where uid = ?", {uid}), a_weak, "an accessory nobody wears");
    t.expect_eq((u64)c.st.one("select accessory_uid from roster where uid = ?", {other_chara}), a_strong, "the other character keeps its own");
    Value d = out.empty() ? Value() : mp_decode(out);
    const Value* data = d.find("data");
    const Value* ew = data ? data->find("EquipWeaponResult") : nullptr;
    const Value* ewc = ew ? ew->find("Character") : nullptr;
    const Value* entry = ewc ? ewc->find(std::to_string(uid)) : nullptr;
    t.expect_eq(entry ? entry->get_u("weapon_item_id") : 0, w_strong, "EquipWeaponResult.Character[uid].weapon_item_id");
    const Value* list = data ? data->find("UpdateCharacterList") : nullptr;
    t.expect_eq(list && list->arr.size() == 1 ? list->arr[0].get_u("id") : 0, uid, "UpdateCharacterList: the character");
    // the skills: the role's open skills, in order
    std::vector<u64> open;
    const u32 level = (u32)c.st.one("select level from roster where uid = ?", {uid});
    c.m.q("select * from master_role where id = ?", {role}, [&](const Row& r) {
        for (int k = 1; k <= 5 && open.size() < 3; k++) {
            const std::string n = std::to_string(k);
            if (r.i(("master_skill" + n + "_id").c_str()) && (u32)r.i(("master_skill" + n + "_open_level").c_str()) <= level)
                open.push_back((u64)r.i(("master_skill" + n + "_id").c_str()));
        }
    });
    std::vector<u64> slots;
    c.st.q("select equip_skill1, equip_skill2, equip_skill3 from roster where uid = ?", {uid}, [&](const Row& r) {
        for (int k = 1; k <= 3; k++) {
            const u64 v = (u64)r.i(("equip_skill" + std::to_string(k)).c_str());
            if (v) slots.push_back(v);
        }
    });
    t.expect_eq(slots == open, true, "the empty slots took the open skills");
    // a second call changes nothing (already the best; the skills stay)
    t.expect_eq(S.call({"EquipAuto", 0x7827ff6a, {uid}, {}, {}}), 0u, "again");
    t.expect_eq((u64)c.st.one("select weapon_uid from roster where uid = ?", {uid}), w_strong, "the same weapon");
    (void)w_weak;
    t.expect_eq(S.call({"EquipAuto", 0x7827ff6a, {12345}, {}, {}}), (u32)ErrorCode::kItemUnusable, "an unknown character: refused");
}

}  // namespace
}  // namespace soa::server
