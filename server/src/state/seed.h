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

// The save seed() would read: the first that exists of `explicit_seed`, --seed, real_seed_save() and
// --game-xml; "" when none does.
std::string seed_source(const std::string& explicit_seed = "");

// Seeds the player, roster, party 1 and meta keys from the first save that exists of
// `explicit_seed`, --seed, real_seed_save() and --game-xml.
void seed(ext::Ctx& ctx, const std::string& explicit_seed = "");

}  // namespace soa::server
