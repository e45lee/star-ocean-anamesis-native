#pragma once
// Seeding: a new state DB gets its player from a save (the game's Game.xml; state/kvs.h). Port
// code, not guest behaviour; the rules are in docs/server-rules.md#seed. The state tables
// themselves are core/server.cpp's schema() until PLAN-schema S1 moves them into state/.
#include <string>

#include "soaserver/ext.h"

namespace soa::server {

// (d) The sanitized search id every seeded or new local player gets (docs/server-rules.md#seed).
constexpr const char* kLocalPlayerId = "LOCAL00001";

// The runtime seed save: data/saves/seed/Game.xml in the checkout, "" when it's missing.
std::string real_seed_save();

// Whether the save at `path` holds a player: its player_name or characters (person_size), the keys
// seed() reads.
bool save_holds_player(const std::string& path);

// The save seed() would read: the first that exists of `explicit_seed`, --seed and real_seed_save(),
// else config().client_save (soa's in-process server: its client's own Game.xml; no option) when it
// holds a player (save_holds_player: the client writes its own Game.xml, settings only, at its first
// start); "" when none does.
std::string seed_source(const std::string& explicit_seed = "");

// Seeds the player, roster, party 1 and meta keys from seed_source(explicit_seed).
void seed(ext::Ctx& ctx, const std::string& explicit_seed = "");

}  // namespace soa::server
