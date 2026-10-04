// Unit tests of the rental-helper module (api/social/rental.cpp; --selftest "social/follow"): the
// synthetic rental list on a scratch server seeded from the test seed save, the rental ids, and the
// rental bonus (master_rental_bonus).
#include <set>

#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "soaserver/msgpack.h"
#include "api/social/rental.h"

namespace soa::server {
namespace {
using namespace ext;

NATIVE_TEST("social/follow-rental") {
    t.expect_eq((u64)or_zero(rental::source_uid(rental::id_of(CharacterUid(0x7e00000eull)))), (u64)0x7e00000eull, "rental id round trip");
    t.expect_eq(rental::source_uid(0x7e00000eull).has_value(), false, "a roster uid isn't a rental id");
    t.expect_eq(rental::source_uid(rental::kRentalBit).has_value(), false, "the bit alone names no character");
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        Request lr;
        lr.method = "Login";
        Value d = Value::object();
        player_load(c, lr, d);
        const Value* f = d.find("BattleRental");
        if (!f || f->type != Value::Map || f->map.empty()) {
            t.fail("no BattleRental list");
            return;
        }
        if (f->map.size() > 10) t.fail("%zu rental entries (max 10)", f->map.size());
        std::set<u64> roles;
        u32 prev_level = ~0u;
        for (auto& [key, e] : f->map) {
            const Value* pc = e.find("pc");
            const Value* pl = e.find("player");
            if (!pc || !pl || !e.find("order")) {
                t.fail("entry %s incomplete", key.c_str());
                continue;
            }
            u64 id = pc->get_u("id");
            std::optional<CharacterUid> src = rental::source_uid(id);
            if (!src || !c.st.one("select count(*) from roster where uid = ?", {*src}))
                t.fail("pc id %llx isn't a roster clone", (unsigned long long)id);
            if (std::to_string(pl->get_u("id")) != key) t.fail("key %s != player id", key.c_str());
            if (pc->get_u("player_id") != pl->get_u("id")) t.fail("pc player_id");
            if (!roles.insert(pc->get_u("master_role_id")).second) t.fail("role listed twice");
            u32 lv = (u32)pc->get_u("level");
            if (lv > prev_level) t.fail("not by level");
            prev_level = lv;
            if (pc->get_u("weapon_item_id") && !pc->get_u("weapon_master_item_id")) t.fail("weapon master id missing");
        }
        // Rental bonus: 3 rentals yesterday -> row 3 (a: 400 support medals), once.
        int64_t p0 = c.st.one("select count(*) from presents", {});
        int64_t yday = c.now() - 86400 - 3600;
        c.st.q("insert into follow_rental (rental_day, count) values (?, 3)", {yday});
        d = Value::object();
        player_load(c, lr, d);
        t.expect_eq(c.st.one("select count(*) from presents", {}), p0 + 1, "one rental bonus present");
        u32 want = (u32)c.m.one("select num from master_rental_bonus where id = 3", {});
        t.expect_eq((u32)c.st.one("select num from presents order by id desc limit 1", {}), want, "row 3's num");
        t.expect_eq(d.find("RentalBonus") ? (u32)d.get_u("RentalBonus") : 0u, 3u, "RentalBonus");
        t.expect_eq(d.find("RentalCount") ? (u32)d.get_u("RentalCount") : 0u, 3u, "RentalCount");
        d = Value::object();
        player_load(c, lr, d);
        t.expect_eq(c.st.one("select count(*) from presents", {}), p0 + 1, "paid once");
        // 25 rentals: capped at the last row
        c.st.q("insert into follow_rental (rental_day, count) values (?, 25)", {yday - 86400});
        d = Value::object();
        player_load(c, lr, d);
        u32 last = (u32)c.m.one("select max(id) from master_rental_bonus", {});
        t.expect_eq(d.find("RentalBonus") ? (u32)d.get_u("RentalBonus") : 0u, last, "capped row");
        // today's rentals wait for tomorrow
        c.st.q("insert into follow_rental (rental_day, count) values (?, 2)", {c.now()});
        d = Value::object();
        player_load(c, lr, d);
        if (d.find("RentalBonus")) t.fail("today's rentals paid early");
        // FollowList answers the same list
        Request fr;
        fr.method = "FollowList";
        const Handler* h = find("FollowList");
        if (!h || (*h)(c, fr).empty()) t.fail("FollowList");
        c.st.exec("rollback");
    });
    if (!ran) return;  // no test seed / 3.7.0 master: nothing to test
}

// UpdateSupport and Player.support_pc_id (the character the rental-bonus popup shows): the
// default is the highest-level character; an owned character is kept; others are refused.
NATIVE_TEST("social/follow-support") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        auto support = [&]() -> u64 {
            Value b = c.base_data();
            const Value* p = b.find("Player");
            const Value* s = p ? p->find("support_pc_id") : nullptr;
            return s ? s->u : 0;
        };
        u64 top = (u64)c.st.one("select uid from roster order by level desc, uid limit 1", {});
        u64 low = (u64)c.st.one("select uid from roster order by level, uid desc limit 1", {});
        t.expect_eq(support(), top, "default: the highest-level character");
        const Handler* h = find("UpdateSupport");
        if (!h) {
            c.st.exec("rollback");
            return t.fail("no UpdateSupport handler");
        }
        Request r;
        r.method = "UpdateSupport";
        r.ints = {low};
        std::vector<u8> out = (*h)(c, r);
        if (out.empty()) t.fail("UpdateSupport refused an owned character");
        Value d = mp_decode(out);
        const Value* dd = d.find("data");
        const Value* pl = dd ? dd->find("Player") : nullptr;
        t.expect_eq(pl && pl->find("support_pc_id") ? pl->get_u("support_pc_id") : 0ull, low, "answered Player.support_pc_id");
        t.expect_eq(support(), low, "kept");
        r.ints = {0x7effffffffull};
        t.expect_eq((*h)(c, r).empty(), true, "an unowned character is refused");
        t.expect_eq(support(), low, "unchanged after a refusal");
        c.st.exec("rollback");
    });
    if (!ran) return;
}

}  // namespace
}  // namespace soa::server
