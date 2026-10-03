#pragma once
// The party sets as the client receives them (port code, not guest behaviour): PartySetInfo, and
// the members of one party (api/player/party_set.cpp).
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

Value party_set_info(ext::Ctx& ctx);  // PartySet: every party set, by id
// A new player's party_set rows: one per set 1..master_global.party_set_max (icon 0, unlocked),
// the parents of player.party_id (PLAN-schema S4). Seed and CreatePlayer, in their transaction.
void add_party_sets(ext::Ctx& ctx);
// The party_set row of `party_id` (icon 0, unlocked) when it has none: UpdateParty takes any id,
// and player.party_id must name a set (PLAN-schema S4).
void ensure_party_set(ext::Ctx& ctx, u32 party_id);
// The owned uids of party `party_id`, in slot order (party_member.uid; its empty slots, NULL,
// left out).
std::vector<CharacterUid> party_member_uids(ext::Ctx& ctx, u32 party_id);

}  // namespace soa::server
