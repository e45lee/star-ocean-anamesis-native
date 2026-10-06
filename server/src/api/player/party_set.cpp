// The party sets as the client receives them: PartySetInfo (api/player/party_set.h). Port code,
// not guest behaviour; every rule carries its source label, (a) master data, (b) client-side
// evidence, (c) outside knowledge, (d) assumption (docs/server-rules.md#party-sets).
#include "api/player/party_set.h"

#include <map>

namespace soa::server {

using ext::Row;

namespace {

using PartySets = std::map<u32, Value>;  // party id -> PartySetInfo

// One saved member (PartySetCharacter) of a `party_member` row: its uid in the slot, and the
// equipment, skills and assist of the set (NULL: none, sent as 0). (b) The equipment is the set's
// for the member (PartySetCharacterInfo's weapon_item_id / accessory_item_id), not the character's
// own (CPersonInfo's, EquipWeapon): a slot the party screen never saved (the seed's, CreatePlayer's,
// UpdateParty's) has none. (PLAN-schema S6: before, such a slot sent the character's own, d.)
Value party_set_character(const Row& member_row) {
    Value member = Value::object();
    member["party_index"] = (u32)member_row.i("slot");
    member["character_id"] = or_zero(member_row.opt<CharacterUid>("uid"));  // NULL: an empty slot
    member["weapon_item_id"] = or_zero(member_row.opt<ItemUid>("weapon_uid"));
    member["accessory_item_id"] = or_zero(member_row.opt<ItemUid>("accessory_uid"));
    member["skill_id1"] = or_zero(member_row.opt<SkillId>("skill_id1"));
    member["skill_id2"] = or_zero(member_row.opt<SkillId>("skill_id2"));
    member["skill_id3"] = or_zero(member_row.opt<SkillId>("skill_id3"));
    member["assist_character_id"] = or_zero(member_row.opt<CharacterUid>("assist_uid"));
    return member;
}

// The saved sets (step 1): every `party_member` row, in party and slot order, as its set's member,
// with the set's icon and lock (b: as UpdatePartySet stored them, PartySetInfo's serializer). A
// set is sent when it has members (its party_set row alone, icon 0 and unlocked for a set never
// saved, doesn't make it saved: fill_unsaved_sets).
PartySets saved_party_sets(ext::Ctx& ctx) {
    PartySets sets;
    ctx.st.q("select m.*, s.icon_id, s.is_lock from party_member m join party_set s on s.party_id = m.party_id order by m.party_id, m.slot", {},
             [&](const Row& member_row) {
                 u32 party_id = (u32)member_row.i("party_id");
                 Value& set = sets[party_id];
                 if (set.type != Value::Map) {
                     set = Value::object();
                     set["party_id"] = party_id;
                     set["icon_id"] = (u32)member_row.i("icon_id");
                     set["is_lock"] = member_row.i("is_lock") != 0;
                     set["PartySetCharacter"] = Value::array();
                 }
                 set["PartySetCharacter"].push(party_set_character(member_row));
             });
    return sets;
}

// The sets never saved (step 2).
// (d) every party set 1..master_global.party_set_max (a) exists: the party screen pages
// through the sets it received ("1/10"). A set never saved gets the members of set 1:
// sets without members, or with empty (character_id 0) slots, crash the client's list code
// (CUISort::CreateCharaParameterCommon, CPartyMemberSelect), so the online server must
// have kept every set filled.
void fill_unsaved_sets(ext::Ctx& ctx, PartySets& sets) {
    if (!sets.count(1)) return;
    for (u32 party_id = 2, max = ctx.global_u32("party_set_max", 10); party_id <= max; party_id++) {
        if (sets.count(party_id)) continue;
        Value set = sets[1];
        set["party_id"] = party_id;
        set["icon_id"] = 0u;
        set["is_lock"] = false;
        sets[party_id] = set;
    }
}

}  // namespace

// PartySet: every party set (PartySetInfo, with its PartySetCharacter members), keyed by the party
// id as a string (b: the client's party-set map, CParameterManager+0x1878).
Value party_set_info(ext::Ctx& ctx) {
    PartySets sets = saved_party_sets(ctx);
    fill_unsaved_sets(ctx, sets);
    Value party_set = Value::object();
    for (auto& [party_id, set] : sets) party_set[std::to_string(party_id)] = set;
    return party_set;
}

// (a) the sets 1..master_global.party_set_max (the party screen pages through them); (d) a row
// with icon 0, unlocked: what PartySet sends for a set without one (saved_party_sets), so the
// rows change no reply.
void add_party_sets(ext::Ctx& ctx) {
    for (u32 party_id = 1, max = ctx.global_u32("party_set_max", 10); party_id <= max; party_id++) ensure_party_set(ctx, party_id);
}

void ensure_party_set(ext::Ctx& ctx, u32 party_id) {
    ctx.st.q("insert into party_set (party_id) values (?) on conflict(party_id) do nothing", {party_id});
}

// The owned uids of party `party_id`, in slot order (its empty slots left out).
std::vector<CharacterUid> party_member_uids(ext::Ctx& ctx, u32 party_id) {
    std::vector<CharacterUid> uids;
    ctx.st.q("select uid from party_member where party_id = ? and slot < ? and uid is not null order by slot", {party_id, kPartyMembers},
             [&](const Row& member_row) { uids.push_back(member_row.id<CharacterUid>("uid")); });
    return uids;
}

}  // namespace soa::server
