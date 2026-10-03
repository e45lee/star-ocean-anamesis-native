#pragma once
// A battle member's status (port code, not guest behaviour): CPersonStatusInfo
// (api/player/person_status.cpp).
#include "soaserver/ext.h"

namespace soa::server {

// The battle status of one party member (CPersonStatusInfo), as the server computed it.
Value person_status_info(ext::Ctx& ctx, u64 uid);

}  // namespace soa::server
