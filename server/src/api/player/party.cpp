// The parties: UpdateParty and UpdatePartySet (api/player/party.h). Port code, not
// guest behaviour; every rule carries its source label, (a) master data, (b) client-side
// evidence, (c) outside knowledge, (d) assumption (docs/server-rules.md "Party").
#include "api/player/party.h"

#include <algorithm>
#include <cstdlib>
#include <iterator>

#include "api/items/items.h"          // owns_item
#include "api/player/party_set.h"    // party_set_info, ensure_party_set
#include "api/player/player_info.h"  // base_data
#include "api/player/roster.h"       // owns_character
#include "core/log.h"
#include "core/request_args.h"

namespace soa::server {

using ext::body;

namespace {}  // namespace

// UpdateParty(u32 party_id, u64 uid1, u64 uid2, u64 uid3) -> UpdatePartyRes  fid ef02dd83
// API: docs/api.md#updateparty   Rules: docs/server-rules.md "Party"
//
// Stores a party's three members in slots 0..2. No 3.7.0 caller is known (the party screen saves
// with UpdatePartySet); the request shape is the method's signature (b).
//   (a) party ids 1..master_global.party_set_max; (d) others are not answered (no body: the
//   host's fallback, no error code), with a warning, as UpdatePartySet (PLAN-schema S6: before,
//   any id was stored, 0 included).
//   (d) A uid that isn't an owned character is stored as an empty slot (NULL, sent as 0).
//   (d) A slot whose character changes loses the set's equipment, skills and assist for it (they
//   were the previous character's; the slot then has none, sent as 0, until UpdatePartySet saves
//   it); a slot keeping its character keeps them (PLAN-schema S6: before, they stayed in either
//   case).
//   (d) The party last edited becomes the current one (Player.party_id, which MissionStart uses).
//   The party id defaults to 1 when missing (args::UpdatePartyArgs).
// Answers: the player state, PartyUpdate {party_id, player_character_id1..3} and PartySet.
std::vector<u8> update_party(ext::Ctx& ctx, const Request& req) {
    const auto args = args::UpdatePartyArgs::from(req);
    u32 party_id = args.party_id;
    u32 max = ctx.global_u32("party_set_max", 10);
    if (party_id < 1 || party_id > max) {
        LOGW("server", "UpdateParty: party id %u outside 1..%u", party_id, max);
        return {};
    }
    ensure_party_set(ctx, party_id);  // the members' parent (party_member.party_id -> party_set)
    Value party_update = Value::object();
    party_update["party_id"] = party_id;
    for (int slot = 0; slot < (int)std::size(args.member_uid); slot++) {
        std::optional<CharacterUid> uid = args.member_uid[slot];
        if (!owns_character(ctx, *uid)) uid.reset();  // (d) only owned characters: else an empty slot
        ctx.st.q(
            "insert into party_member (party_id, slot, uid) values (?,?,?)"
            " on conflict(party_id, slot) do update set uid = excluded.uid,"
            " weapon_uid = case when party_member.uid is excluded.uid then party_member.weapon_uid end,"
            " accessory_uid = case when party_member.uid is excluded.uid then party_member.accessory_uid end,"
            " skill_id1 = case when party_member.uid is excluded.uid then party_member.skill_id1 end,"
            " skill_id2 = case when party_member.uid is excluded.uid then party_member.skill_id2 end,"
            " skill_id3 = case when party_member.uid is excluded.uid then party_member.skill_id3 end,"
            " assist_uid = case when party_member.uid is excluded.uid then party_member.assist_uid end",
            {party_id, slot, uid});
        party_update["player_character_id" + std::to_string(slot + 1)] = or_zero(uid);
    }
    ctx.st.q("update player set party_id = ?", {party_id});  // (d) the party last edited is the current one
    Value data = base_data(ctx);
    data["PartyUpdate"] = party_update;
    data["PartySet"] = party_set_info(ctx);
    return body(data);
}

// PartySetInfo::Serialize() text (the wire form, docs/api.md "UpdatePartySet"): "party_id,icon_id,is_lock/"
// then per member "id,party_index,character_id,weapon_item_id,accessory_item_id,skill_id1,skill_id2,skill_id3,
// assist_character_id/" (b: the serializer). Records are split at '/', fields at ','; a field that
// isn't a number reads 0 (strtoull), a missing one 0. Port code, not guest behaviour.
std::vector<std::vector<std::string>> party_set_records(const std::string& text) {
    std::vector<std::vector<std::string>> records;
    size_t record_start = 0;
    while (record_start < text.size()) {
        size_t record_end = text.find('/', record_start);
        if (record_end == std::string::npos) record_end = text.size();
        std::vector<std::string> fields;
        size_t field_start = record_start;
        while (field_start <= record_end) {
            size_t field_end = std::min(text.find(',', field_start), record_end);
            fields.push_back(text.substr(field_start, field_end - field_start));
            field_start = field_end + 1;
        }
        records.push_back(fields);
        record_start = record_end + 1;
    }
    return records;
}

bool parse_party_set_text(const std::string& text, PartySetText& out) {
    auto records = party_set_records(text);
    auto num = [](const std::vector<std::string>& fields, size_t i) -> u64 {
        return i < fields.size() ? strtoull(fields[i].c_str(), nullptr, 10) : 0;
    };
    if (records.empty() || records[0].size() < 3) return false;
    out = PartySetText{};
    out.party_id = (u32)num(records[0], 0);
    out.icon_id = num(records[0], 1);
    out.is_lock = num(records[0], 2) != 0;
    for (size_t k = 1; k < records.size(); k++) {
        const auto& fields = records[k];
        if (fields.size() < 9) continue;  // (d) a short member record is skipped
        PartySetMember member;
        member.slot = num(fields, 1);
        member.character_uid = nonzero<CharacterUid>(num(fields, 2));
        member.weapon_uid = nonzero<ItemUid>(num(fields, 3));
        member.accessory_uid = nonzero<ItemUid>(num(fields, 4));
        for (int k = 0; k < 3; k++) member.skill_id[k] = nonzero<SkillId>((u32)num(fields, 5 + k));
        member.assist_uid = nonzero<CharacterUid>(num(fields, 8));
        out.members.push_back(member);
    }
    return true;
}

// UpdatePartySet(PartySetInfo const&) -> UpdatePartySetRes                fid c119d0d8
// API: docs/api.md#updatepartyset   Rules: docs/server-rules.md "Party sets"
//
// Saves one party set from the party screen (CPartyComposition, when the player leaves the
// member select). Received as PartySetInfo::Serialize() text (parse_party_set_text).
//   (b) client-side evidence: the serializer and CApiNotify::OnUpdatePartySetRes (stores
//   PartySetResult as the party set with that id).
//   (a) party ids 1..master_global.party_set_max; (d) others, and text that doesn't parse, are
//   not answered (no body: the host's fallback, no error code), with a warning.
//   (d) a member must be an owned character, else the slot is stored empty; the weapon and
//   accessory must be owned items and the assist an owned character, else they are stored as
//   none (PLAN-schema S6: they were stored as sent; the skills still are); a record whose
//   party_index is outside 0..3 (the screen's four slots, b) is skipped, as a short one.
//   (b) the set replaces the stored one (the handler replaces the map entry).
//   (d) the saved set becomes the player's current party.
// Answers: the player state, PartySetResult (the saved set) and PartySet (every set).
std::vector<u8> update_party_set(ext::Ctx& ctx, const Request& req) {
    std::string text = args::UpdatePartySetArgs::from(req).text;
    PartySetText set;
    if (!parse_party_set_text(text, set)) {
        LOGW("server", "UpdatePartySet: can't parse \"%s\"", text.c_str());
        return {};
    }
    u32 party_id = set.party_id;
    u32 max = ctx.global_u32("party_set_max", 10);
    if (party_id < 1 || party_id > max) {
        LOGW("server", "UpdatePartySet: party id %u outside 1..%u", party_id, max);
        return {};
    }
    ctx.st.q(
        "insert into party_set (party_id, icon_id, is_lock) values (?,?,?)"
        " on conflict(party_id) do update set icon_id = excluded.icon_id, is_lock = excluded.is_lock",
        {party_id, set.icon_id, set.is_lock ? 1 : 0});
    ctx.st.q("delete from party_member where party_id = ?", {party_id});
    for (auto member : set.members) {
        if (member.slot > 3) continue;  // (d) not one of the four slots
        if (member.character_uid && !owns_character(ctx, *member.character_uid)) member.character_uid.reset();  // (d) only owned
        if (member.weapon_uid && !owns_item(ctx, *member.weapon_uid)) member.weapon_uid.reset();                // (d) characters
        if (member.accessory_uid && !owns_item(ctx, *member.accessory_uid)) member.accessory_uid.reset();       // and items
        if (member.assist_uid && !owns_character(ctx, *member.assist_uid)) member.assist_uid.reset();
        ctx.st.q(
            "insert into party_member (party_id, slot, uid, weapon_uid, accessory_uid, skill_id1, skill_id2, skill_id3, assist_uid) "
            "values (?,?,?,?,?,?,?,?,?)"
            " on conflict(party_id, slot) do update set uid = excluded.uid, weapon_uid = excluded.weapon_uid, "
            "accessory_uid = excluded.accessory_uid, skill_id1 = excluded.skill_id1, skill_id2 = excluded.skill_id2, "
            "skill_id3 = excluded.skill_id3, assist_uid = excluded.assist_uid",
            {party_id, member.slot, member.character_uid, member.weapon_uid, member.accessory_uid, member.skill_id[0], member.skill_id[1],
             member.skill_id[2], member.assist_uid});
    }
    // (d) the saved set becomes the player's current party (Player.party_id, which the party
    // screen opens on (CParameterUtility::GetPatyIndex) and MissionStart uses).
    ctx.st.q("update player set party_id = ?", {party_id});
    Value sets = party_set_info(ctx);
    Value data = base_data(ctx);
    auto it = sets.find(std::to_string(party_id));
    data["PartySetResult"] = it ? *it : Value::object();
    data["PartySet"] = sets;
    LOGI("server", "UpdatePartySet: party %u = %s", party_id, text.c_str());  // read by party_session.sh
    return body(data);
}

// The parties' APIs (src/core/modules.cpp: the core's APIs first).
void register_party() {
    ext::add_core_api({"UpdateParty"}, update_party);
    ext::add_core_api({"UpdatePartySet"}, update_party_set);
}

}  // namespace soa::server
