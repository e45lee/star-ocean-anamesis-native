#pragma once
// The party sets as the client receives them (port code, not guest behaviour): PartySetInfo, and
// the members of one party (api/player/party_set.cpp).
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

// (b) A party set's members: slots 0..2. CParameterUtility::tPartyData::Initialize(PartySetInfo
// const*, bool) (@01832a9c) builds the party's four tCharaData from PartySetCharacter[0..2] (by
// position) and resets the fourth (tPartyData + 0x8798 = 8 + 3 x 0x2d30), the helper's slot,
// which the mission menu fills with the chosen helper (rental, own or NPC); the party screen
// shows three members. A set's member past the third is never read by the client.
constexpr u32 kPartyMembers = 3;

Value party_set_info(ext::Ctx& ctx);  // PartySet: every party set, by id
// A new player's party_set rows: one per set 1..master_global.party_set_max (icon 0, unlocked),
// the parents of player.party_id (PLAN-schema S4). Seed and CreatePlayer, in their transaction.
void add_party_sets(ext::Ctx& ctx);
// The party_set row of `party_id` (icon 0, unlocked) when it has none: UpdateParty takes any id,
// and player.party_id must name a set (PLAN-schema S4).
void ensure_party_set(ext::Ctx& ctx, u32 party_id);
// The owned uids of party `party_id`, in slot order (party_member.uid of slots 0..2,
// kPartyMembers; its empty slots, NULL, left out).
std::vector<CharacterUid> party_member_uids(ext::Ctx& ctx, u32 party_id);

}  // namespace soa::server
