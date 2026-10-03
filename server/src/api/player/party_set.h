#pragma once
// The party sets as the client receives them (port code, not guest behaviour): PartySetInfo, and
// the members of one party (api/player/party_set.cpp).
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

Value party_set_info(ext::Ctx& ctx);  // PartySet: every party set, by id
// The owned uids of party `party_id`, in slot order.
std::vector<u64> party_member_uids(ext::Ctx& ctx, u32 party_id);

}  // namespace soa::server
