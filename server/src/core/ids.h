#pragma once
// The server's uid scheme for owned objects (port code, not guest behaviour; docs/server-rules.md
// "Seed"). The typed ids (CharacterUid, ItemUid, ...: PLAN-readability R12) are soaserver/ids.h;
// these stay plain numbers, the first of a range (`CharacterUid(kRosterUid0 + i)`).
#include "soaserver/ids.h"
#include "soaserver/server.h"

namespace soa::server {

constexpr u64 kRosterUid0 = 0x7e000000;  // (d) uid scheme: seeded roster 0x7e000000+N (as the generator)
constexpr u64 kNewCharUid0 = 0x7e100000;  // (d) characters gained later
constexpr u64 kItemUid0 = 0x7d000000;     // (d) unique items (weapons, accessories)

}  // namespace soa::server
