// Unit tests of the parties (api/player/party.{h,cpp}): UpdatePartySet's text, as
// PartySetInfo::Serialize() writes it (docs/api.md "UpdatePartySet"). Run in --selftest; not
// differential (the server has no guest counterpart). The handlers run with real arguments in
// the items-party replay corpus (server/tests/replay/).
#include <string>
#include <vector>

#include "api/player/party.h"
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
    t.expect_eq(m0.character_uid, (u64)100, "character_id");
    t.expect_eq(m0.weapon_uid, (u64)200, "weapon_item_id");
    t.expect_eq(m0.accessory_uid, (u64)300, "accessory_item_id");
    t.expect_eq(m0.skill_id[0] + m0.skill_id[1] + m0.skill_id[2], (u64)36, "skill ids");
    t.expect_eq(m0.skill_id[2], (u64)13, "skill_id3");
    t.expect_eq(m0.assist_uid, (u64)400, "assist_character_id");
    t.expect_eq(set.members[1].slot, (u64)1, "second member's party_index");

    // (d) a member record without all nine fields is skipped; the set still parses
    if (!parse_party_set_text("1,0,0/0,0,5/0,1,6,0,0,0,0,0,0/", set)) return t.fail("a short member record");
    t.expect_eq(set.members.size(), (size_t)1, "short record skipped");
    t.expect_eq(set.members[0].character_uid, (u64)6, "the full record kept");
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

}  // namespace
}  // namespace soa::server
