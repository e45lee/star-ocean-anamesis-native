// Unit tests of the parties (api/player/party.{h,cpp}): UpdatePartySet's text, as
// PartySetInfo::Serialize() writes it (docs/api.md "UpdatePartySet"). Run in --selftest; not
// differential (the server has no guest counterpart). The handlers run with real arguments in
// the items-party replay corpus (server/tests/replay/).
#include <string>
#include <vector>

#include "api/player/party.h"
#include "api/player/party_set.h"
#include "soaserver/ext.h"
#include "soaserver/native_test.h"

namespace soa::server {
namespace {

NATIVE_TEST("player/party-set-text") {
    // (b) "party_id,icon_id,is_lock/" then "id,party_index,character_id,weapon_item_id,
    // accessory_item_id,skill_id1,skill_id2,skill_id3,assist_character_id/" per member
    PartySetText set;
    if (!parse_party_set_text("2,3,1/7,0,100,200,300,11,12,13,400/8,1,101,0,0,0,0,0,0/", set)) return t.fail("a full set doesn't parse");
    t.expect_eq(set.party_id, 2u, "party id");
    t.expect_eq(set.icon_id, (u64)3, "icon id");
    t.expect_eq(set.is_lock, true, "lock");
    if (set.members.size() != 2) return t.fail("%zu members, want 2", set.members.size());
    const PartySetMember& m0 = set.members[0];
    t.expect_eq(m0.slot, (u64)0, "party_index");
    t.expect_eq(or_zero(m0.character_uid), (u64)100, "character_id");
    t.expect_eq(or_zero(m0.weapon_uid), (u64)200, "weapon_item_id");
    t.expect_eq(or_zero(m0.accessory_uid), (u64)300, "accessory_item_id");
    t.expect_eq(or_zero(m0.skill_id[0]) + or_zero(m0.skill_id[1]) + or_zero(m0.skill_id[2]), 36u, "skill ids");
    t.expect_eq(or_zero(m0.skill_id[2]), 13u, "skill_id3");
    t.expect_eq(or_zero(m0.assist_uid), (u64)400, "assist_character_id");
    // the wire's 0 is none
    t.expect_eq(set.members[1].weapon_uid.has_value() || set.members[1].skill_id[0].has_value() || set.members[1].assist_uid.has_value(), false,
                "0 = none");
    t.expect_eq(set.members[1].slot, (u64)1, "second member's party_index");

    // (d) a member record without all nine fields is skipped; the set still parses
    if (!parse_party_set_text("1,0,0/0,0,5/0,1,6,0,0,0,0,0,0/", set)) return t.fail("a short member record");
    t.expect_eq(set.members.size(), (size_t)1, "short record skipped");
    t.expect_eq(or_zero(set.members[0].character_uid), (u64)6, "the full record kept");
    t.expect_eq(set.is_lock, false, "unlocked");

    // no header with three fields: not parsed (UpdatePartySet answers nothing)
    if (parse_party_set_text("x", set)) t.fail("\"x\" parsed");
    if (parse_party_set_text("", set)) t.fail("empty text parsed");
    if (parse_party_set_text("1,2/", set)) t.fail("a two-field header parsed");

    // the records: a trailing '/' adds no empty record; empty and non-numeric fields read 0
    auto records = party_set_records("1,,x/2/");
    t.expect_eq(records.size(), (size_t)2, "two records");
    t.expect_eq(records[0].size(), (size_t)3, "three fields, one empty");
    if (!parse_party_set_text("1,,x/", set)) return t.fail("empty / non-numeric header fields");
    t.expect_eq(set.icon_id, (u64)0, "empty field = 0");
    t.expect_eq(set.is_lock, false, "non-numeric field = 0");
}

// The party sets in the state (PLAN-schema S6: one party_member table, NULL = none), on a scratch
// server: UpdatePartySet stores owned equipment and assists only and skips a slot outside 0..2;
// a set's weapon counts as equipped (it isn't sold); UpdateParty refuses an id outside
// 1..party_set_max and clears a slot's equipment, skills and assist when its character changes;
// PartySet sends the set's equipment only (a slot without one: 0, not the character's own).
NATIVE_TEST("player/party-members") {
    using namespace ext;
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        auto call = [&](const char* method, std::vector<u64> ints, std::vector<std::string> strs = {}, std::vector<std::vector<u64>> vecs = {}) {
            const Handler* h = find(method);
            if (!h) return Value();
            Request r;
            r.method = method;
            r.ints = std::move(ints);
            r.strs = std::move(strs);
            r.vecs = std::move(vecs);
            std::vector<u8> b = (*h)(c, r);
            return b.empty() ? Value() : mp_decode(b);
        };
        u32 weapon = (u32)c.m.one("select id from master_item where type = 1 and rarity = 3 and sale_fol > 0 order by id limit 1", {});
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        c.grant(1, weapon, 2, items, stocks, chars);
        if (items.arr.size() != 2) return t.fail("granted %zu weapons", items.arr.size());
        u64 w0 = items.arr[0].get_u("id"), w1 = items.arr[1].get_u("id");
        std::vector<u64> owned;
        c.st.q("select uid from roster order by uid limit 3", {}, [&](const Row& r) { owned.push_back((u64)r.i("uid")); });
        if (owned.size() < 3) return t.fail("%zu characters", owned.size());
        auto text = std::to_string(2) + ",4,1/0,0," + std::to_string(owned[0]) + "," + std::to_string(w0) + ",999,11,0,13,999/" + "0,1," +
                    std::to_string(owned[1]) + ",0,0,0,0,0," + std::to_string(owned[2]) + "/0,3," + std::to_string(owned[2]) + ",0,0,0,0,0,0/";
        Value saved = call("UpdatePartySet", {}, {text});
        if (saved.type != Value::Map) return t.fail("UpdatePartySet answered nothing");
        auto member = [&](u32 slot, const char* column) {
            return c.st.one(std::string("select ifnull(") + column + ", -1) from party_member where party_id = 2 and slot = ?", {slot}, -2);
        };
        t.expect_eq(member(0, "weapon_uid"), (int64_t)w0, "an owned weapon stored");
        t.expect_eq(member(0, "accessory_uid"), (int64_t)-1, "an unowned accessory: none");
        t.expect_eq(member(0, "assist_uid"), (int64_t)-1, "an unowned assist: none");
        t.expect_eq(member(0, "skill_id1"), (int64_t)11, "skill 1");
        t.expect_eq(member(0, "skill_id2"), (int64_t)-1, "skill 0: none");
        t.expect_eq(member(1, "assist_uid"), (int64_t)owned[2], "an owned assist stored");
        t.expect_eq(c.st.one("select count(*) from party_member where party_id = 2", {}), (int64_t)2, "slot 3 (the helper's) skipped");
        // the set's weapon is equipped: not sold; the other one is
        call("SellItemArray", {}, {}, {{w0}});
        call("SellItemArray", {}, {}, {{w1}});
        t.expect_eq(c.st.one("select count(*) from items where uid = ?", {w0}), (int64_t)1, "a party set's weapon isn't sold");
        t.expect_eq(c.st.one("select count(*) from items where uid = ?", {w1}), (int64_t)0, "a free weapon is sold");
        // UpdateParty: ids outside 1..party_set_max refused; a changed slot loses the set's equipment
        t.expect_eq(call("UpdateParty", {0, owned[0], 0, 0}).type == Value::Nil, true, "UpdateParty(0) refused");
        t.expect_eq(call("UpdateParty", {11, owned[0], 0, 0}).type == Value::Nil, true, "UpdateParty(11) refused");
        t.expect_eq(c.st.one("select count(*) from party_set where party_id in (0, 11)", {}), (int64_t)0, "no set 0 or 11");
        Value updated = call("UpdateParty", {2, owned[0], owned[2], 0});
        if (updated.type != Value::Map) return t.fail("UpdateParty(2) answered nothing");
        t.expect_eq(member(0, "weapon_uid"), (int64_t)w0, "the same character: the set's weapon kept");
        t.expect_eq(member(0, "skill_id1"), (int64_t)11, "the same character: the skills kept");
        t.expect_eq(member(1, "uid"), (int64_t)owned[2], "slot 1's new character");
        t.expect_eq(member(1, "assist_uid"), (int64_t)-1, "a new character: the assist cleared");
        t.expect_eq(member(2, "uid"), (int64_t)-1, "an empty slot: NULL");
        t.expect_eq(c.st.one("select party_id from player", {}), (int64_t)2, "the current party");
        // PartySet: the set's equipment, not the character's own (a slot without one sends 0)
        c.st.q("update roster set weapon_uid = null where weapon_uid = ?", {w0});
        c.st.q("update roster set weapon_uid = ? where uid = ?", {w0, owned[2]});
        Value sets = party_set_info(c);
        const Value* set2 = sets.find("2");
        const Value* members = set2 ? set2->find("PartySetCharacter") : nullptr;
        if (!members || members->arr.size() != 3) return t.fail("set 2 members");
        t.expect_eq(members->arr[0].get_u("weapon_item_id"), w0, "the set's weapon");
        t.expect_eq(members->arr[1].get_u("character_id"), owned[2], "slot 1's character");
        t.expect_eq(members->arr[1].get_u("weapon_item_id"), (u64)0, "no weapon of the set's: 0 (not the character's own)");
        t.expect_eq(members->arr[2].get_u("character_id"), (u64)0, "an empty slot sends 0");
        c.st.exec("rollback");
    });
    if (!ran) t.fail("no scratch server");
}

}  // namespace
}  // namespace soa::server
