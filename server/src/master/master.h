#pragma once
// Typed lookups into the 3.7.0 master data (read-only; port code, not guest behaviour). One copy of
// each lookup the core and the modules share: master_global values, the player-level and role
// level tables, texts and the mission tables. Each takes the master DB handle (the server's, or a
// module's Ctx::m.h). The rules they serve carry their labels here: (a) master data, (b)
// client-side evidence.
#include <sqlite3.h>

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "soaserver/ids.h"
#include "soaserver/server.h"

namespace soa::server::master {

// ---- master_global (a) ----------------------------------------------------------------------
// The value of `key`, "" when there is no row (or its value is NULL).
std::string global_str(sqlite3* m, const char* key);
// The value as an unsigned integer (strtoul); `dflt` when there is no row. A row whose value is
// empty reads as 0 (the core's reading; no 3.7.0 row is empty).
u32 global_u32(sqlite3* m, const char* key, u32 dflt);
// The same, but an empty value also reads as `dflt` (api/favor/'s reading).
u32 global_u32_unless_empty(sqlite3* m, const char* key, u32 dflt);
// The value as a double (e.g. "11.5"); `dflt` when there is no row.
double global_f(sqlite3* m, const char* key, double dflt);

// ---- player rank and stamina ----------------------------------------------------------------
// (a) master_player_level (257 rows for levels 1..999): the (level, `column`) rows, by level;
// (b) levels without a row are interpolated (MasterPlayerLevelModel::GetByCalculatedLevel,
// rules::interpolate_level).
std::vector<std::pair<u32, u32>> player_level_rows(sqlite3* m, const char* column);
// The stamina maximum at a player level (master_player_level.stamina, interpolated).
u32 stamina_max(sqlite3* m, u32 level);
// (a) master_global.Player_Rank_max (900); (b) CUIUtility::GetMaxLevel clamps it to 999 and
// uses 255 without the key.
u32 player_level_max(sqlite3* m);
// (a) master_player_level.next_exp, indexed by level up to the maximum rank, (b) with the
// missing levels interpolated.
std::vector<u32> player_next(sqlite3* m);

// ---- roles ----------------------------------------------------------------------------------
// (a) master_role_level_max by the role's rarity: 40 when the role has no row; a NULL level_max
// reads as 0 (the core's Db::one reading, kept until PLAN-schema S1 / R11 look at it).
u32 role_level_cap(sqlite3* m, RoleId role);
// (a) master_character_common_parameter.next_exp x (b) master_role_boosted.exp_rate for the
// role's rank and rarity, rounded (PersonModel::GetNextLevelExp(float rate, rank, rarity):
// (int)(rate * base + 0.5)), indexed by level.
std::vector<u32> role_next(sqlite3* m, RoleId role);

// ---- texts ----------------------------------------------------------------------------------
// master_text (lang ja) of a message id; "" when missing.
std::string text(sqlite3* m, const std::string& message_id);

// ---- missions -------------------------------------------------------------------------------
// A mission's master row: its table, Common::MissionType (0 story, 1 event, 2 tower, 3 world map)
// and area.
struct MissionRef {
    std::string table;
    u32 type = 0, area = 0;
    bool found = false;
};
// The mission row of `type` ((b) Common::MissionType selects the table), else (d) the story
// table and the others in turn (the port's debug route sends type 0 for every mission).
MissionRef find_mission(sqlite3* m, u32 type, u32 mission);

}  // namespace soa::server::master
