#pragma once
// The parties (port code, not guest behaviour): UpdateParty, UpdatePartySet (api/player/party.cpp).
// SetAssist is api/player/assist.cpp's, UpdateHome api/player/home.h's.
#include <optional>
#include <string>
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

std::vector<u8> update_party(ext::Ctx& ctx, const Request& req);
std::vector<u8> update_party_set(ext::Ctx& ctx, const Request& req);

// A party set as UpdatePartySet sends it (PartySetInfo / PartySetCharacterInfo, b: the
// serializer; docs/api.md "UpdatePartySet"). The member uids are the client's `*_id` keys
// (character_id, weapon_item_id, ...), which carry owned uids; the wire's 0 ("none") is nullopt.
struct PartySetMember {
    u64 slot = 0;  // party_index
    std::optional<CharacterUid> character_uid;
    std::optional<ItemUid> weapon_uid, accessory_uid;
    std::optional<SkillId> skill_id[3];  // master skill ids
    std::optional<CharacterUid> assist_uid;
};
struct PartySetText {
    u32 party_id = 0;
    u64 icon_id = 0;
    bool is_lock = false;
    std::vector<PartySetMember> members;  // the member records with all nine fields
};
// The '/'-separated records of PartySetInfo::Serialize() text, each its ','-separated fields.
std::vector<std::vector<std::string>> party_set_records(const std::string& text);
// Parses the text: false when there is no header record with at least three fields.
bool parse_party_set_text(const std::string& text, PartySetText& out);

}  // namespace soa::server
