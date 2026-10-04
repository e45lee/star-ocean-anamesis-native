// Unit tests of the mastery APIs (api/growth/mastery.cpp; docs/server-rules.md#mastery), on a
// scratch server seeded from the test seed save against the 3.7.0 master data.
#include <string>
#include <vector>

#include "api/growth/mastery.h"
#include "api/player/person_status.h"
#include "api/player/roster.h"
#include "master/master.h"
#include "soaserver/ext.h"
#include "soaserver/native_test.h"

namespace soa::server {
namespace {
using namespace ext;

std::vector<u8> call(Ctx& c, const char* method, std::vector<u64> ints) {
    const Handler* h = find(method);
    if (!h) return {};
    Request r;
    r.method = method;
    r.ints = std::move(ints);
    return (*h)(c, r);
}

// data.<key> of a reply (Nil when missing).
Value data_of(const std::vector<u8>& b, const char* key) {
    if (b.empty()) return Value();
    Value v = mp_decode(b);
    const Value* d = v.find("data");
    const Value* k = d ? d->find(key) : nullptr;
    return k ? *k : Value();
}

u64 field(const Value& v, const char* key) {
    const Value* f = v.find(key);
    return f ? (f->type == Value::Int ? (u64)f->i : f->u) : ~0ull;
}

u32 item_id(Ctx& c, const std::string& label) { return (u32)c.m.one("select id from master_item where id_label = ?", {label}); }

// Three owned LV70 characters, their roles planted: a master-type role (the first role with a
// mastery type, rarity 6), a role of its category without one, and a role of another category.
struct Cast {
    u64 master = 0, disciple = 0, other_category = 0;
    u32 type_id = 0, master_role = 0;
};

Cast cast(Ctx& c) {
    Cast k;
    std::vector<u64> uids;
    c.st.q("select uid from roster order by uid limit 3", {}, [&](const Row& r) { uids.push_back((u64)r.i("uid")); });
    if (uids.size() < 3) return k;
    u32 cat = 0, disciple_role = 0, other_role = 0;
    c.m.q(
        "select id, category_type, master_mastery_step_type_id from master_role where master_mastery_step_type_id is not null and rarity = 6 "
        "and id_label like 'role_%' order by id limit 1",
        {}, [&](const Row& r) {
            k.master_role = (u32)r.i("id");
            cat = (u32)r.i("category_type");
            k.type_id = (u32)r.i("master_mastery_step_type_id");
        });
    disciple_role = (u32)c.m.one(
        "select id from master_role where master_mastery_step_type_id is null and category_type = ? and rarity = 6 and id_label like 'role_%' "
        "order by id limit 1",
        {cat});
    other_role =
        (u32)c.m.one("select id from master_role where category_type <> ? and rarity = 6 and id_label like 'role_%' order by id limit 1", {cat});
    if (!k.master_role || !disciple_role || !other_role) return k;
    k.master = uids[0];
    k.disciple = uids[1];
    k.other_category = uids[2];
    c.st.q("update roster set role_id = ?, level = 70, awaken = 0 where uid = ?", {k.master_role, k.master});
    c.st.q("update roster set role_id = ?, level = 70 where uid = ?", {disciple_role, k.disciple});
    c.st.q("update roster set role_id = ?, level = 70 where uid = ?", {other_role, k.other_category});
    return k;
}

NATIVE_TEST("growth/mastery-pairing") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        Cast k = cast(c);
        if (!k.master || !k.disciple || !k.other_category) return t.fail("no master-type role in the master");
        auto pairs = [&] { return c.st.one("select count(*) from mastery", {}); };
        auto refused = [&](std::vector<u64> ints, u32 want, const char* why) {
            code = 0;
            call(c, "TrainMastery", ints);
            t.expect_eq(code, want, why);
            t.expect_eq(pairs(), (int64_t)0, "refused: nothing stored");
        };
        refused({k.disciple, k.disciple, 1, k.type_id, 0, 0}, 10208u, "the same character twice");
        refused({k.master, k.disciple, 1, k.type_id, 0, 0}, 10208u, "a disciple without a mastery type can't be the master");
        refused({k.disciple, k.master, 1, k.type_id + 1, 0, 0}, 10208u, "another mastery type");
        refused({k.other_category, k.master, 1, k.type_id, 0, 0}, 10208u, "another category");
        refused({k.disciple, k.master, 0, k.type_id, 0, 0}, 10208u, "dojo 0");
        refused({k.disciple, k.master, 4, k.type_id, 0, 0}, 10208u, "dojo 4");
        c.st.q("update roster set level = 69 where uid = ?", {k.disciple});
        refused({k.disciple, k.master, 1, k.type_id, 0, 0}, 11002u, "below LV70");
        c.st.q("update roster set level = 70 where uid = ?", {k.disciple});
        // ---- accepted: the pair, in its reply and in GetMasteryInfo
        code = 0;
        std::vector<u8> b = call(c, "TrainMastery", {k.disciple, k.master, 2, k.type_id, 0, 0});
        t.expect_eq(code, 0u, "paired");
        Value list = data_of(b, "UpdateCharacterMasteryInfoArray");
        t.expect_eq(list.arr.size(), (size_t)1, "one element");
        if (list.arr.size() == 1) {
            const Value& e = list.arr[0];
            t.expect_eq(field(e, "character_id"), k.disciple, "character_id: the disciple");
            t.expect_eq(field(e, "parent_character_id"), k.master, "parent_character_id: the master");
            t.expect_eq(field(e, "dojo_no"), (u64)2, "dojo_no");
            t.expect_eq(field(e, "master_mastery_step_type_id"), (u64)k.type_id, "type");
            t.expect_eq(field(e, "master_mastery_step_1_option_no"), (u64)0, "no training yet");
            t.expect_eq(field(e, "mastery_talent_id"), (u64)0, "no talent before 皆伝");
            t.expect_eq(field(e, "parent_master_role_id"), (u64)0, "no parent role before 皆伝");
            t.expect_eq(field(e, "player_id"), (u64)c.player_id().v, "player_id: the player's");
        }
        Value map = data_of(call(c, "GetMasteryInfo", {}), "PlayerCharacterMasteryInfoMap");
        const Value* entry = map.find(std::to_string(k.disciple).c_str());
        t.expect_eq(entry != nullptr, true, "GetMasteryInfo keys the pair by the disciple");
        // ---- a busy dojo refuses another pair; pairing one of the two again parts the old pair
        u64 third = (u64)c.st.one("select uid from roster where uid not in (?, ?, ?) order by uid limit 1", {k.master, k.disciple, k.other_category});
        c.st.q("insert into mastery (uid, master_uid, dojo_no, type_id, created_at, updated_at) values (?, ?, 1, ?, 0, 0)",
               {third, k.other_category, k.type_id});
        code = 0;
        call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, 0, 0});
        t.expect_eq(code, 10208u, "dojo 1 busy");
        c.st.q("delete from mastery where uid = ?", {third});
        code = 0;
        call(c, "TrainMastery", {k.disciple, k.master, 3, k.type_id, 0, 0});
        t.expect_eq(code, 0u, "paired again in dojo 3");
        t.expect_eq(pairs(), (int64_t)1, "the old pair parted");
        t.expect_eq(c.st.one("select dojo_no from mastery where uid = ?", {k.disciple}), (int64_t)3, "in dojo 3");
        c.st.exec("commit");
    });
    if (!ran) return;
}

NATIVE_TEST("growth/mastery-training") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        Cast k = cast(c);
        if (!k.master || !k.disciple) return t.fail("no master-type role in the master");
        call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, 0, 0});
        // ---- not the next training, unknown pair, no such option
        code = 0;
        call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, 2, 1});
        t.expect_eq(code, 10208u, "step 2 before step 1");
        code = 0;
        call(c, "TrainMastery", {k.master, k.disciple, 1, k.type_id, 1, 1});
        t.expect_eq(code, 10208u, "the pair the wrong way round");
        code = 0;
        call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, 1, 7});
        t.expect_eq(code, 10208u, "option 7");
        // ---- step 1 option 1: (a) master_mastery_step's item and FOL; refused when short
        u32 item = 0, num = 0, need_fol = 0;
        c.m.q("select * from master_mastery_step where type_id = ? and step = 1 and option_no = 1", {k.type_id}, [&](const Row& r) {
            item = (u32)r.i("required_master_item_id");
            num = (u32)r.i("required_num");
            need_fol = (u32)r.i("required_fol");
        });
        add_stock(c, item, -(int64_t)stock_count(c, item));
        code = 0;
        call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, 1, 1});
        t.expect_eq(code, 10206u, "items short");
        add_stock(c, item, num);
        add_fol(c, -(int64_t)fol(c));
        code = 0;
        call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, 1, 1});
        t.expect_eq(code, 10710u, "FOL short");
        t.expect_eq(stock_count(c, item), num, "refused: items kept");
        add_fol(c, 10000000);
        u32 f0 = fol(c);
        code = 0;
        std::vector<u8> b = call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, 1, 1});
        t.expect_eq(code, 0u, "step 1 accepted");
        t.expect_eq(stock_count(c, item), 0u, "the step's items taken");
        t.expect_eq(fol(c), f0 - need_fol, "the step's FOL taken");
        t.expect_eq(c.st.one("select step1 from mastery where uid = ?", {k.disciple}), (int64_t)1, "step 1 option 1 stored");
        Value upd = data_of(b, "UpdateStockItem");
        t.expect_eq(upd.arr.size(), (size_t)1, "UpdateStockItem: the step's item");
        t.expect_eq(data_of(b, "MasteryRewardInfo").type == Value::Nil, true, "no reward before the fifth");
        // ---- steps 2-4 with the pass medal (option 4-6: the medal, no FOL), step 5 option 3
        u32 medal = item_id(c, master::global_str(c.m.h, "mastery_training_pass_item_id"));
        u32 medal_num = c.global_u32("mastery_training_pass_required_num", 1);
        add_stock(c, medal, 3 * medal_num);
        for (u32 step = 2; step <= 4; step++) {
            u32 f1 = fol(c);
            code = 0;
            call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, step, 3 + 2});
            t.expect_eq(code, 0u, "a medal training accepted");
            t.expect_eq(fol(c), f1, "the medal costs no FOL");
            t.expect_eq(c.st.one(("select step" + std::to_string(step) + " from mastery where uid = ?").c_str(), {k.disciple}), (int64_t)2,
                        "the medal's card (option 2) stored");
        }
        t.expect_eq(stock_count(c, medal), 0u, "three medals used");
        t.expect_eq(mastery_inheritance(c, CharacterUid(k.disciple)).graduated, false, "four trainings: no 皆伝");
        c.m.q("select * from master_mastery_step where type_id = ? and step = 5 and option_no = 3", {k.type_id}, [&](const Row& r) {
            item = (u32)r.i("required_master_item_id");
            num = (u32)r.i("required_num");
        });
        add_stock(c, item, num);
        u32 reward = item_id(c, master::global_str(c.m.h, "mastery_reward_master_item_id"));
        u32 reward_num = c.global_u32("mastery_reward_num", 1);
        u32 r0 = stock_count(c, reward);
        code = 0;
        b = call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, 5, 3});
        t.expect_eq(code, 0u, "step 5 accepted");
        Value gift = data_of(b, "MasteryRewardInfo");
        t.expect_eq(field(gift, "master_item_id"), (u64)reward, "the 皆伝 gift (a: master_global)");
        t.expect_eq(field(gift, "num"), (u64)reward_num, "the gift's count");
        t.expect_eq(stock_count(c, reward), r0 + reward_num - (reward == item ? num : 0), "the gift in the stock");
        // ---- 皆伝: the inheritance in the reply, CPersonInfo and CPersonStatusInfo
        u32 talent = mastery_talent_of(c, RoleId(k.master_role), (u32)c.st.one("select awaken from roster where uid = ?", {k.master}));
        Value list = data_of(b, "UpdateCharacterMasteryInfoArray");
        if (list.arr.size() == 1) {
            t.expect_eq(field(list.arr[0], "parent_master_role_id"), (u64)k.master_role, "the master's role inherited");
            t.expect_eq(field(list.arr[0], "mastery_talent_id"), (u64)talent, "the master's talent inherited");
        } else t.fail("UpdateCharacterMasteryInfoArray");
        bool seen = false;
        c.st.q("select * from roster where uid = ?", {k.disciple}, [&](const Row& row) {
            Value info = person_info(c, row, c.player_id());
            seen = field(info, "parent_master_role_id") == k.master_role && field(info, "mastery_talent_id") == talent;
        });
        t.expect_eq(seen, true, "CPersonInfo carries the inheritance");
        t.expect_eq(field(person_status_info(c, k.disciple), "mastery_talent_id"), (u64)talent, "CPersonStatusInfo carries the talent");
        c.st.q("select * from roster where uid = ?", {k.master}, [&](const Row& row) {
            t.expect_eq(person_info(c, row, c.player_id()).find("mastery_talent_id") == nullptr, true, "the master's CPersonInfo has no talent");
        });
        code = 0;
        call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, 6, 1});
        t.expect_eq(code, 10208u, "no sixth training");
        // ---- ResetMastery: either order; the pair goes and so does the inheritance
        code = 0;
        call(c, "ResetMastery", {k.disciple, 12345});
        t.expect_eq(code, 10208u, "no such pair");
        code = 0;
        b = call(c, "ResetMastery", {k.master, k.disciple});
        t.expect_eq(code, 0u, "parted (master first)");
        list = data_of(b, "UpdateCharacterMasteryInfoArray");
        t.expect_eq(list.arr.size() == 1 && field(list.arr[0], "character_id") == k.disciple, true, "the parted pair's key");
        t.expect_eq(c.st.one("select count(*) from mastery", {}), (int64_t)0, "no pair left");
        t.expect_eq(mastery_inheritance(c, CharacterUid(k.disciple)).graduated, false, "the talent lost");
        call(c, "TrainMastery", {k.disciple, k.master, 1, k.type_id, 0, 0});
        code = 0;
        call(c, "ResetMastery", {k.disciple, k.master});
        t.expect_eq(code, 0u, "parted (disciple first)");
        c.st.exec("commit");
    });
    if (!ran) return;
}

// The inherited talent follows the master's awakening: master_awaken's talent in the role's
// mastery_talent_slot replaces the role's (role_cp0022_b01a_6191: slot 5, changed at awakening 5),
// and UpdateAwakenLevel reports it as update_child_mastery_talent_id.
NATIVE_TEST("growth/mastery-awakening") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        RoleId role((u32)c.m.one("select id from master_role where id_label = 'role_cp0022_b01a_6191'", {}));
        if (!role.v) return;  // not in this master
        u32 slot = (u32)c.m.one("select mastery_talent_slot from master_role where id = ?", {role});
        std::string column = "master_talent" + std::to_string(slot) + "_id";
        u32 base = (u32)c.m.one("select " + column + " from master_role where id = ?", {role});
        u32 awakened = (u32)c.m.one("select a." + column +
                                        " from master_awaken a join master_role r on r.role_category_id = a.role_category_id "
                                        "where r.id = ? and a.awaken_level = 5",
                                    {role});
        t.expect_eq(mastery_talent_of(c, role, 0), base, "no awakening: the role's talent");
        t.expect_eq(mastery_talent_of(c, role, 5), awakened, "awakening 5: master_awaken's");
        t.expect_eq(base != awakened && awakened != 0, true, "the master data changes it");
        // a graduated pair whose master awakens 4 -> 5
        Cast k = cast(c);
        if (!k.disciple) return t.fail("no disciple");
        c.st.q("update roster set role_id = ?, awaken = 4 where uid = ?", {role, k.master});
        c.st.q(
            "insert into mastery (uid, master_uid, dojo_no, type_id, step1, step2, step3, step4, step5, created_at, updated_at) "
            "values (?, ?, 1, ?, 1, 1, 1, 1, 1, 0, 0)",
            {k.disciple, k.master, k.type_id});
        t.expect_eq(mastery_inheritance(c, CharacterUid(k.disciple)).mastery_talent_id, mastery_talent_of(c, role, 4), "inherited at awakening 4");
        std::string awaken_id;
        c.m.q("select awaken_id from master_role where id = ?", {role}, [&](const Row& r) { awaken_id = r.s("awaken_id"); });
        c.m.q("select * from master_item_awaken where awaken_id = ? and awaken_level = 5", {awaken_id}, [&](const Row& r) {
            for (int s = 1; s <= 3; s++) {
                std::string id = "master_item" + std::to_string(s) + "_id", n = "item" + std::to_string(s) + "_num";
                if (r.i(id.c_str())) add_stock(c, (u32)r.i(id.c_str()), r.i(n.c_str()));
            }
        });
        add_fol(c, 100000000);
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        std::vector<u8> b = call(c, "UpdateAwakenLevel", {k.master, 5});
        t.expect_eq(code, 0u, "awakened");
        Value result = data_of(b, "AwakenResult");
        t.expect_eq(field(result, "update_child_id"), k.disciple, "update_child_id: the disciple");
        t.expect_eq(field(result, "update_child_mastery_talent_id"), (u64)awakened, "the new talent");
        c.st.exec("commit");
    });
    if (!ran) return;
}

}  // namespace
}  // namespace soa::server
