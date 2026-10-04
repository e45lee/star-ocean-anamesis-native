#pragma once
// Player titles (port code, not guest behaviour): what the player's creation calls
// (api/player/titles.cpp; docs/server-rules.md#titles).
#include "soaserver/ext.h"

namespace soa::server {

// A new player's titles (the seed, CreatePlayer): the default titles owned and the first one worn.
void new_player_titles(ext::Ctx& ctx);

}  // namespace soa::server
