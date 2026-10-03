#pragma once
// The home character (port code, not guest behaviour): UpdateHome (api/player/home.cpp;
// docs/server-rules.md "Home character").
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

// UpdateHome(u64 character_uid): the home character (its doc block is in home.cpp). Public for the tests.
std::vector<u8> update_home(ext::Ctx& ctx, const Request& req);

}  // namespace soa::server
