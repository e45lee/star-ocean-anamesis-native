// The party sets as the client receives them: PartySetInfo (api/player/party_set.h). Port code,
// not guest behaviour; every rule carries its source label, (a) master data, (b) client-side
// evidence, (c) outside knowledge, (d) assumption (docs/server-rules.md "Party sets").
#include "api/player/party_set.h"

#include <map>

namespace soa::server {

using ext::Row;

namespace {

using PartySets = std::map<u32, Value>;  // party id -> PartySetInfo

// One saved member (PartySetCharacter) of a `party` row: its uid in the slot, and the equipment,
// skills and assist of the set.
Value party_set_character(ext::Ctx& ctx, u32 party_id, const Row& party_row) {
    Value member = Value::object();
    member["party_index"] = (u32)party_row.i("slot");
    member["character_id"] = (u64)party_row.i("uid");
    u64 weapon_uid = 0, accessory_uid = 0, assist_uid = 0;
    u32 skill[3] = {0, 0, 0};
    // (d) the character's own equipment when the set saved none
    ctx.st.q("select weapon_uid, accessory_uid from roster where uid = ?", {party_row.i("uid")}, [&](const Row& roster_row) {
        weapon_uid = (u64)roster_row.i("weapon_uid");
        accessory_uid = (u64)roster_row.i("accessory_uid");
    });
    // What the party screen saved with UpdatePartySet (the member's equipment, skills and
    // assist in this set), when there is a row.
    ctx.st.q("select * from party_member where party_id = ? and slot = ?", {party_id, party_row.i("slot")}, [&](const Row& member_row) {
        weapon_uid = (u64)member_row.i("weapon_uid");
        accessory_uid = (u64)member_row.i("accessory_uid");
        skill[0] = (u32)member_row.i("skill1");
        skill[1] = (u32)member_row.i("skill2");
        skill[2] = (u32)member_row.i("skill3");
        assist_uid = (u64)member_row.i("assist_uid");
    });
    member["weapon_item_id"] = weapon_uid;
    member["accessory_item_id"] = accessory_uid;
    member["skill_id1"] = skill[0];
    member["skill_id2"] = skill[1];
    member["skill_id3"] = skill[2];
    member["assist_character_id"] = assist_uid;
    return member;
}

// The saved sets (step 1): every `party` row, in party and slot order, as its set's member.
PartySets saved_party_sets(ext::Ctx& ctx) {
    PartySets sets;
    ctx.st.q("select * from party order by party_id, slot", {}, [&](const Row& party_row) {
        u32 party_id = (u32)party_row.i("party_id");
        Value& set = sets[party_id];
        if (set.type != Value::Map) {
            set = Value::object();
            set["party_id"] = party_id;
            set["icon_id"] = 0u;     // (d) until the set's party_set row says otherwise
            set["is_lock"] = false;  // (d)
            set["PartySetCharacter"] = Value::array();
        }
        set["PartySetCharacter"].push(party_set_character(ctx, party_id, party_row));
    });
    // (b) the set's icon and lock, as UpdatePartySet stored them (PartySetInfo's serializer)
    ctx.st.q("select * from party_set", {}, [&](const Row& set_row) {
        auto it = sets.find((u32)set_row.i("party_id"));
        if (it == sets.end()) return;
        it->second["icon_id"] = (u32)set_row.i("icon_id");
        it->second["is_lock"] = set_row.i("is_lock") != 0;
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
std::vector<u64> party_member_uids(ext::Ctx& ctx, u32 party_id) {
    std::vector<u64> uids;
    ctx.st.q("select uid from party where party_id = ? and uid != 0 order by slot", {party_id},
             [&](const Row& party_row) { uids.push_back((u64)party_row.i("uid")); });
    return uids;
}

}  // namespace soa::server
