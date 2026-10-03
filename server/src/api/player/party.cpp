// The parties: UpdateParty and UpdatePartySet (api/player/party.h). Port code, not
// guest behaviour; every rule carries its source label, (a) master data, (b) client-side
// evidence, (c) outside knowledge, (d) assumption (docs/server-rules.md "Party").
#include "api/player/party.h"

#include <algorithm>
#include <cstdlib>
#include <iterator>

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
//   (d) A uid that isn't an owned character is stored as an empty slot (0).
//   (d) The party last edited becomes the current one (Player.party_id, which MissionStart uses).
//   The party id defaults to 1 when missing (args::UpdatePartyArgs).
// Answers: the player state, PartyUpdate {party_id, player_character_id1..3} and PartySet.
std::vector<u8> update_party(ext::Ctx& ctx, const Request& req) {
    const auto args = args::UpdatePartyArgs::from(req);
    u32 party_id = args.party_id;
    Value party_update = Value::object();
    party_update["party_id"] = party_id;
    for (int slot = 0; slot < (int)std::size(args.member_uid); slot++) {
        CharacterUid uid = args.member_uid[slot];
        if (!owns_character(ctx, uid)) uid = CharacterUid(0);  // (d) only owned characters (party's 0: empty, until S6)
        ctx.st.q(
            "insert into party (party_id, slot, uid) values (?,?,?)"
            " on conflict(party_id, slot) do update set uid = excluded.uid",
            {party_id, slot, uid});
        party_update["player_character_id" + std::to_string(slot + 1)] = uid.v;
    }
    ensure_party_set(ctx, party_id);  // (d) any id: its party_set row (player.party_id's parent, PLAN-schema S4)
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
        out.members.push_back(
            {num(fields, 1), num(fields, 2), num(fields, 3), num(fields, 4), {num(fields, 5), num(fields, 6), num(fields, 7)}, num(fields, 8)});
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
//   (d) a member must be an owned character, else the slot is stored empty; the weapon,
//   accessory, skills and assist are stored as sent (not checked against the roster).
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
    ctx.st.q("delete from party where party_id = ?", {party_id});
    ctx.st.q("delete from party_member where party_id = ?", {party_id});
    for (const auto& member : set.members) {
        u64 uid = member.character_uid;  // (party / party_member stay plain, 0 = empty: PLAN-schema S6)
        if (uid && !owns_character(ctx, CharacterUid(uid))) uid = 0;  // only owned characters (d)
        ctx.st.q(
            "insert into party (party_id, slot, uid) values (?,?,?)"
            " on conflict(party_id, slot) do update set uid = excluded.uid",
            {party_id, member.slot, uid});
        ctx.st.q(
            "insert into party_member (party_id, slot, weapon_uid, accessory_uid, skill1, skill2, skill3, assist_uid) "
            "values (?,?,?,?,?,?,?,?)"
            " on conflict(party_id, slot) do update set weapon_uid = excluded.weapon_uid, "
            "accessory_uid = excluded.accessory_uid, skill1 = excluded.skill1, skill2 = excluded.skill2, "
            "skill3 = excluded.skill3, assist_uid = excluded.assist_uid",
            {party_id, member.slot, member.weapon_uid, member.accessory_uid, member.skill_id[0], member.skill_id[1], member.skill_id[2],
             member.assist_uid});
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
