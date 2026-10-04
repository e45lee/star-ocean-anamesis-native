// Unit tests of the premium and favor login bonuses and StaminaHealByFavor
// (premium_and_favor_bonus.cpp), on a scratch server seeded from the test seed save
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

NATIVE_TEST("daily/premium-favor-bonus") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        int64_t t0 = c.now().v;
        // ---- premium: off without a pass
        Value d = player_load_data(c);
        const Value* pl = d.find("PremiumLoginBonus");
        if (!pl || !pl->arr.empty()) t.fail("no pass: PremiumLoginBonus should be empty");
        // a pass (content type 11) of the open-ended premiumlogin_bonus_2020_02
        u32 pass = master_id(c, "premiumlogin_bonus_2020_02", "master_premium_login_bonus");
        Value a, b, e;
        c.grant(11, pass, 1, a, b, e);
        int64_t n0 = c.st.one("select count(*) from presents", {});
        d = player_load_data(c);
        pl = d.find("PremiumLoginBonus");
        if (!pl || pl->arr.size() != 1) {
            t.fail("PremiumLoginBonus after a pass");
        } else {
            t.expect_eq(pl->arr[0].find("current_idx")->u, (uint64_t)1, "day 1");
            if (!pl->arr[0].find("is_updated")->b) t.fail("is_updated on the granting load");
        }
        int64_t day1 =
            c.m.one("select count(*) from master_premium_login_bonus_contents where master_premium_login_bonus_id = ? and order_idx = 1", {pass});
        t.expect_eq(c.st.one("select count(*) from presents", {}) - n0, day1, "day-1 presents");
        std::string line;
        c.st.q("select text from presents where reason_type = 6", {}, [&](const Row& r) { line = r.s("text"); });
        t.expect_eq(line, std::string("プレミアムログインボーナス 1日目"), "premium present line");
        // same day: no second page
        d = player_load_data(c);
        t.expect_eq(d.find("PremiumLoginBonus")->arr[0].find("current_idx")->u, (uint64_t)1, "still day 1");
        if (d.find("PremiumLoginBonus")->arr[0].find("is_updated")->b) t.fail("is_updated only once");

        // ---- favor bonus: nobody at favor level 4 -> nothing
        c.st.q("delete from favor", {});
        d = player_load_data(c);
        if (d.find("FavorBonusContetsResultInfo")) t.fail("favor bonus without level-4 characters");
        // two characters with a favor schedule at level 4 (60000 points, (a) master_favor_level)
        std::vector<u32> sames;
        c.st.q("select distinct r.same_role_id s from roster o join master_role r on r.id = o.role_id", {}, [&](const Row&) {});
        c.st.q("select role_id from roster order by uid", {}, [&](const Row& r) {
            u32 same = (u32)c.m.one("select same_role_id from master_role where id = ?", {r.i("role_id")});
            if (sames.size() < 2 && c.m.one("select favor_max_level from master_favor_schedule where id = ?", {same}) >= 4 &&
                std::find(sames.begin(), sames.end(), same) == sames.end())
                sames.push_back(same);
        });
        if (sames.size() < 2) {
            t.fail("no characters with a favor schedule");
            c.st.exec("rollback");
            return;
        }
        for (u32 s : sames)
            c.st.q(
                "insert into favor (same_role_id, point) values (?, 60000)"
                " on conflict(same_role_id) do update set point = excluded.point, tap_count = excluded.tap_count, "
                "tapped_at = excluded.tapped_at, event_drop_at = excluded.event_drop_at",
                {s});
        // the Player keys of the favor bonus: "" while never (PLAN-schema S10: NULL, 0 before), the
        // time once done
        auto player_key = [&](const Value& data, const char* key) {
            const Value* player = data.find("Player");
            const Value* v = player ? player->find(key) : nullptr;
            return v ? v->s : std::string("<none>");
        };
        // a heal before any favor bonus (the heal makes the row; the bonus's day stays never)
        c.st.q("delete from favor_bonus_state", {});
        c.st.q("update player set stamina_at = ?", {t0});
        call(c, "StaminaHealByFavor", {});
        t.expect_eq(c.st.one("select count(*) from favor_bonus_state where day_at is null and healed_at is not null", {}), (int64_t)1,
                    "the heal's row: the bonus day NULL (never)");
        c.st.q("delete from favor_bonus_state where day_at is null", {});
        int64_t n1 = c.st.one("select count(*) from presents", {});
        // The bonus is granted during the load, stamped with the clock then: read it between two reads of the
        // clock (the wall clock may tick over a second during the load; comparing with one later read flaked).
        const auto before = c.now();
        d = player_load_data(c);
        const auto after = c.now();
        const std::string got = player_key(d, "favor_bonus_received_at");
        const std::string want = got == c.fmt_time(after) ? c.fmt_time(after) : c.fmt_time(before);
        t.expect_eq(got, want, "favor_bonus_received_at: the bonus's time (the load's clock)");
        t.expect_eq(player_key(d, "stamina_update_by_favor"), std::string(""), "stamina_update_by_favor: never");
        t.expect_eq(c.st.one("select count(*) from favor_bonus_state where healed_at is null and lot_uid in (select uid from roster)", {}),
                    (int64_t)1, "the bonus's row: an owned lot character, never healed");
        const Value* fb = d.find("FavorBonusContetsResultInfo");
        if (!fb) {
            t.fail("favor bonus with two level-4 characters");
        } else {
            // (a) favor_bonus_0002: 2 characters -> present_count 1, stamina 12
            const Value* lots = fb->find("FavorBonusContetsInfoList");
            t.expect_eq(lots ? lots->arr.size() : 0, (size_t)1, "one lot");
            t.expect_eq(c.st.one("select count(*) from presents", {}) - n1, (int64_t)1, "one favor present");
            // (b) the list is u32 master_favor_bonus_contents ids (InfoBaseValueArray<u32>), the
            // drawn row: its content is the present granted
            if (lots && lots->arr.size() == 1) {
                const Value& id = lots->arr[0];
                t.expect_eq((int)id.type, (int)Value::UInt, "a u32 id, not an object");
                bool same = false;
                c.m.q("select content_type, content_id, num from master_favor_bonus_contents where id = ?", {(u32)id.u}, [&](const Row& k) {
                    same = c.st.one(
                               "select count(*) from presents where content_type = ? and content_id = ? and num = ? and created_at > 0 "
                               "order by rowid desc limit 1",
                               {(u32)k.i("content_type"), (u32)k.i("content_id"), (u32)k.i("num")}) > 0;
                });
                t.expect_eq(same, true, "the id's master_favor_bonus_contents row is the present granted");
            }
        }
        d = player_load_data(c);
        if (d.find("FavorBonusContetsResultInfo")) t.fail("favor bonus once a day");
        // StaminaHealByFavor: +12 once a day
        u32 s0 = (u32)c.st.one("select stamina from player", {});
        c.st.q("update player set stamina_at = ?", {t0});
        std::vector<u8> r1 = call(c, "StaminaHealByFavor", {});
        u32 s1 = (u32)c.st.one("select stamina from player", {});
        if (s1 < s0 + 12) t.fail("StaminaHealByFavor %u -> %u, want +12", s0, s1);
        call(c, "StaminaHealByFavor", {});
        t.expect_eq((u32)c.st.one("select stamina from player", {}), s1, "heal once a day");
        c.st.exec("rollback");
    });
    if (!ran) return;
}

// The login bonus: day 1 on the first player load of the day (is_received_now, a present),
// no second grant the same day, day 2 the next day. Was part of server/economy-apis.
NATIVE_TEST("daily/login-bonus") {
    with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        // ---- login bonus: once per day, into the present box
        Request lr;
        lr.method = "NoLoginStart";
        int64_t p0 = c.st.one("select count(*) from presents", {});
        Value d = Value::object();
        player_load(c, lr, d);
        u32 lb = master_id(c, "login_bonus", "master_login_bonus");
        t.expect_eq((u32)c.st.one("select day_index from login_bonus where id = ?", {lb}), 1u, "day 1");
        const Value* list = d.find("LoginBonus");
        bool received = false;
        if (list)
            for (auto& e : list->arr)
                if (e.get_u("master_login_bonus_id") == lb) received = e.find("is_received_now")->b;
        if (!received) t.fail("is_received_now not set on the first login of the day");
        int64_t p1 = c.st.one("select count(*) from presents", {});
        if (p1 != p0 + 1) t.fail("presents %lld -> %lld", (long long)p0, (long long)p1);
        t.expect_eq((u32)c.st.one("select content_type from presents order by id desc limit 1", {}), 4u, "day 1 = coins (login_bonus_01)");
        d = Value::object();
        player_load(c, lr, d);
        t.expect_eq(c.st.one("select count(*) from presents", {}), p1, "no second bonus the same day");
        list = d.find("LoginBonus");
        if (list)
            for (auto& e : list->arr)
                if (e.get_u("master_login_bonus_id") == lb && e.find("is_received_now")->b) t.fail("is_received_now twice");
        c.st.q("update login_bonus set last_at = last_at - 86400", {});
        d = Value::object();
        player_load(c, lr, d);
        t.expect_eq((u32)c.st.one("select day_index from login_bonus where id = ?", {lb}), 2u, "day 2 the next day");
        c.st.exec("commit");
    });
}

}  // namespace
}  // namespace soa::server
