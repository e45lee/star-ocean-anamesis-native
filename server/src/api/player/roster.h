#pragma once
// The roster as the client receives it (port code, not guest behaviour): CPersonInfo, one owned
// character, and the `Character` list of every owned character (api/player/roster.cpp).
#include "soaserver/ext.h"

namespace soa::server {

// One owned character (CPersonInfo) from its `roster` row; `owner_player_id` is its player_id key.
Value person_info(ext::Ctx& ctx, const ext::Row& roster_row, u32 owner_player_id);
// Character: every owned character (CPersonInfo), by uid.
Value roster_info(ext::Ctx& ctx);

}  // namespace soa::server
