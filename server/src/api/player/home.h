#pragma once
// The home character (port code, not guest behaviour): UpdateHome (api/player/home.cpp;
// docs/server-rules.md#home-character).
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

// UpdateHome(u64 character_uid): the home character (its doc block is in home.cpp). Public for the tests.
std::vector<u8> update_home(ext::Ctx& ctx, const Request& req);

// Home3DAnd2DSwitching(u8 is_3d): the player's 2D / 3D home (its doc block is in home.cpp).
std::vector<u8> home3d_and_2d_switching(ext::Ctx& ctx, const Request& req);

// ChangeMascot(u32 master_person_id): the home's mascot (its doc block is in home.cpp).
std::vector<u8> change_mascot(ext::Ctx& ctx, const Request& req);

// --home3d-all (a debug option; docs/home3d.md "Forcing the 3D home"): clears
// master_person.home3d_disable in the client's master copy (an ext::ClientMaster data override),
// so the client offers its 3D home for every character. Returns the number of persons changed.
int enable_home3d(ext::Sql& client_master);
// The ClientMaster hook: enable_home3d when config().home3d_all is set.
void client_home3d_all(ext::Sql& client_master, ServerTime now, EventTime event_now);

}  // namespace soa::server
