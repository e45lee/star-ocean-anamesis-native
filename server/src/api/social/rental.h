#pragma once
// Rental helpers (api/social/rental.cpp): the ids of the synthetic rental characters.
// (d) The rental list is made of clones of the player's own roster; a clone's id is the roster
// uid with bit 40 set, so MissionStart can find the character the player picked.
#include <cstdint>

#include "soaserver/ext.h"

namespace soa::server::rental {

constexpr uint64_t kRentalBit = 1ull << 40;
inline uint64_t id_of(uint64_t roster_uid) { return roster_uid | kRentalBit; }
// The roster uid behind a rental id, or 0 for an id that isn't one of ours.
inline uint64_t source_uid(uint64_t rental_id) { return (rental_id & kRentalBit) ? rental_id & ~kRentalBit : 0; }

// The player as a CFollowInfo {order, player: CFollowPlayerInfo, pc: CFollowPersonInfo} (the
// shape of the rental entries): the player's id, name and level, and (d) the home character, else
// the highest-level one. GetPlayerDetailInfo answers it as the SearchResult entry.
Value own_follow_entry(ext::Ctx& ctx);

// The synthetic rental players as the `BattleRental` / `Follow` map sends them: {player id (as a
// string): CFollowInfo {order, player, pc}} (api/social/rental.cpp). The Sphere 211 rental slot lends the
// same characters (api/sphere211/sphere211.cpp).
Value follow_map(ext::Ctx& ctx);

}  // namespace soa::server::rental
