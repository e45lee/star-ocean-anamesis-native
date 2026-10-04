#pragma once
// A mission NPC's battle status (CPersonStatusInfo) from the master data, as the client's NPC
// model computes it (library code). docs/server-rules.md "Tutorial
// battle". soa and soa-server both use this; the port test server/npc-status-master compares it
// with the client's own model.
#include <cstdint>

#include "soaserver/msgpack.h"

struct sqlite3;

namespace soa::server::rules {

// Overwrites the stats (hp, attack, intelligence, defence, hit, guard), the weapon
// (weapon_master_item_id, weapon_id) and the skills (skill1..3, skill1..3_level) of `e` with
// master_mission_npc `mission_npc_id`'s. False (e unchanged) when the row or its role is missing.
bool npc_status(sqlite3* master, uint32_t mission_npc_id, Value& e);

}  // namespace soa::server::rules
