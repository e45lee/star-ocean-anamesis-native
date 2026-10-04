#pragma once
// Sphere 211 (api/sphere211/README.md): what the module's files share. Internal to the module (the
// handlers in sphere211.cpp; season.cpp, floors.cpp, rewards.cpp, ranking.cpp, rental.cpp and
// state.cpp) and its tests; the APIs themselves are reached through ext::find("Sphere211...").
// The parts other modules and the tests reach are in sphere211.h. Labels: (a) master data,
// (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include <string>
#include <utility>
#include <vector>

#include "api/sphere211/sphere211.h"
#include "soaserver/ext.h"

namespace soa::server::sphere211 {

using ext::Ctx;
using ext::Row;

// ---- the log, the RNG (state.cpp) ----------------------------------------------------------------
// (The dive's season cycle, its battles won, whether the season-end result is still to be shown
// and the port's test hook are columns of the `sphere` row: cycle, season_wins, end_pending,
// debug_enemy_level; the key-value table sphere_meta until PLAN-schema S3.)
// sphere_log kinds: a battle won (value 1) and a floor entered (value = the floor), on the server
// clock, for the achievements (types 62 / 61) and the season's ranking entry.
enum class LogKind : int { kWin = 1, kFloor = 2 };
void log_event(Ctx& ctx, LogKind kind, u32 value);
u64 next_random(Ctx& ctx);
// A weighted pick over (weight, value) rows: the index, -1 when empty or all weights are 0.
template <class T>
int weighted_index(Ctx& ctx, const std::vector<std::pair<u32, T>>& rows) {
    u64 sum = 0;
    for (auto& row : rows) sum += row.first;
    if (!sum) return -1;
    u64 x = next_random(ctx) % sum;
    for (size_t k = 0; k < rows.size(); k++) {
        if (x < rows[k].first) return (int)k;
        x -= rows[k].first;
    }
    return (int)rows.size() - 1;
}

// ---- seasons (season.cpp) ------------------------------------------------------------------
// A master_sphere211 row (a), with how far its dates moved (pick_season).
struct Season {
    u32 id = 0, index = 0, floor_group = 0, clear_present_group = 0, ranking_reward = 0, treasure_contents = 0;
    u32 heal_item = 0, reroll_item = 0, reroll_num = 1;
    std::string opened_at, closed_at;
    u32 cycle = 0;      // the repetition past the service's end (pick_season)
    int64_t shift = 0;  // how far the dates moved (pick_season)
};
Season season_by_id(Ctx& ctx, u32 season_id);
SeasonPick current_pick(Ctx& ctx);
Season current_season(Ctx& ctx);
// ClientMaster: the client's master copy gets the current season's moved dates.
void client_seasons(ext::Sql& db, ServerTime clock, EventTime ev);
// Loads the dive (a new player's, or a new season's: the old one ends) and ticks the stamina.
Season load_dive(Ctx& ctx);

// ---- floors, cells and the sphere stamina (floors.cpp) ---------------------------------------
// A master_sphere211_floor row (a) for a level.
struct Floor {
    u32 id = 0, level = 0, use_stamina = 1, base_enemy_level = 0, asset_box_group = 0, treasure_id = 0;
    u32 treasure_num = 1, floor_clear_treasure_num = 0, boss_add = 0, rare_add = 0;
};
Floor floor_row(Ctx& ctx, const Season& season, u32 level);
// master_sphere211_floor_asset.lottery_type (a: the cell's battle box type); which are boss and
// rare cells is (d).
enum class LotteryType : u32 { kNormal = 1, kBoss = 2, kRare = 4, kRareAlt = 6 };
void enter_floor(Ctx& ctx, const Season& season, u32 level);
// The next-floor count of the warp access (at least 1).
u32 lot_floor_num(Ctx& ctx, u32 treasure_total);
void start_dive_if_idle(Ctx& ctx, const Season& season);
// The cell a battle request names (asset id and mission id); false when none.
bool find_cell(Ctx& ctx, const Request& req, u32& asset_id, u32& mission_id);
u32 stamina_max(Ctx& ctx);
void tick_stamina(Ctx& ctx);

// ---- treasure boxes (rewards.cpp) -------------------------------------------------------------
// Grants a content, expanding (a) item sets (content type 99).
void grant_content(Ctx& ctx, u32 type, u32 id, u32 num, Value& items, Value& stocks, Value& characters);
void add_boxes(Ctx& ctx, const Floor& floor, u32 count);
void lot_ranks(Ctx& ctx, const Season& season);
// Opens the dive's boxes into the player's items; `result` (when given) gets
// Sphere211TreasureResultInfoMap's entries; null outputs are discarded.
void open_boxes(Ctx& ctx, const Season& season, Value* items, Value* stocks, Value* characters, Value* result);

// ---- the season ranking (ranking.cpp) ----------------------------------------------------------
u32 ranking_group_of(ext::Sql& master, u32 season_id);
// ClientMaster: the last season's ranking reward group in the client's master copy.
void client_ranking_groups(ext::Sql& db, ServerTime, EventTime);
void ranking_reward(Ctx& ctx, u32 season_id, u32 rank);
// Sphere211RankingInfoMap: the local ranking of one player.
Value ranking_info_map(Ctx& ctx, const Season& season);

// ---- the rental slot and the rental bonus (rental.cpp) ---------------------------------------
constexpr u32 kRentalsPerFloor = 3;  // (a) cp0003_tutorial_sphere211_007 "１フロアにつき合計３回"
void put_rental(Ctx& ctx, u32 floor, Value& data);
// Whether `lender` may lend the rental character `rental_id` on this floor.
bool rental_available(Ctx& ctx, u32 lender, u64 rental_id);
// A rental made at t: the lender has lent on this floor; the day's count for the rental bonus.
void record_rental(Ctx& ctx, const Season& season, u32 lender, ServerTime t);
void rental_bonus(Ctx& ctx, Value& data);

// ---- the dive state in every answer (state.cpp) ------------------------------------------------
void put_state(Ctx& ctx, const Season& season, Value& data);
// The player state plus put_state.
Value dive_state(Ctx& ctx, const Season& season);

}  // namespace soa::server::sphere211
