// Sphere 211: the dive state every answer carries, the module's keyed values, its log and its RNG
// (api/sphere211/README.md; declared in dive.h). Port code, not guest behaviour; every rule carries
// its source label, (a) master data, (b) client-side evidence, (c) outside knowledge,
// (d) assumption. Rules in docs/server-rules.md "Sphere 211".
#include <map>
#include <set>
#include <string>

#include "api/sphere211/dive.h"

namespace soa::server::sphere211 {

// ---- small keyed values, the log, the RNG ------------------------------------------------------
int64_t sphere_meta(Ctx& ctx, const char* key, int64_t dflt) {
    return ctx.st.one("select ifnull((select value from sphere_meta where key = ?), ?)", {key, dflt});
}
void set_sphere_meta(Ctx& ctx, const char* key, int64_t value) {
    ctx.st.q("insert or replace into sphere_meta (key, value) values (?, ?)", {key, value});
}
void log_event(Ctx& ctx, LogKind kind, u32 value) {
    ctx.st.q("insert into sphere_log (kind, value, at) values (?, ?, ?)", {(int)kind, value, ctx.now()});
}
u64 next_random(Ctx& ctx) { return (*ctx.rng)(); }

// ---- the dive state ------------------------------------------------------------------------------
namespace {

// The `sphere` row (one per player): the dive.
struct DiveRow {
    u32 floor = 0, streak = 0, treasure_total = 0, stamina = 0, revive_count = 0, clear_asset = 0, lot_floor_num = 0;
    u32 prev_season = 0, prev_floor = 0, prev_treasure = 0, prev_rank = 0;
    int64_t stamina_at = 0;
};
DiveRow read_dive(Ctx& ctx) {
    DiveRow dive;
    ctx.st.q("select * from sphere where id = 1", {}, [&](const Row& sphere_row) {
        dive.floor = (u32)sphere_row.i("floor_level");
        dive.streak = (u32)sphere_row.i("streak");
        dive.treasure_total = (u32)sphere_row.i("treasure_total");
        dive.stamina = (u32)sphere_row.i("stamina");
        dive.stamina_at = sphere_row.i("stamina_at");
        dive.revive_count = (u32)sphere_row.i("revive_count");
        dive.clear_asset = (u32)sphere_row.i("clear_asset");
        dive.lot_floor_num = (u32)sphere_row.i("lot_floor_num");
        dive.prev_season = (u32)sphere_row.i("prev_season");
        dive.prev_floor = (u32)sphere_row.i("prev_floor");
        dive.prev_treasure = (u32)sphere_row.i("prev_treasure");
        dive.prev_rank = (u32)sphere_row.i("prev_rank");
    });
    return dive;
}

// Sphere211FloorAssetInfoMap: the floor's cells (b: the map is read by MissionUtility::
// GetEventMissionList type 5: the asset id and mission box id of each entry).
// can_play (the name found by its CHash32 0x5730cc2a in the class's property map; the menu
// offers a battle only then, b): (c)+(d) the start cell (no neighbours listed) and every
// uncleared cell with a cleared neighbour (master_sphere211_floor_asset parent_cell_1..4, a:
// the rows list both directions). is_new: (d) playable and not cleared yet.
Value floor_cells(Ctx& ctx, u32 player_id) {
    std::set<u32> cleared;
    ctx.st.q("select asset_id from sphere_cell where cleared = 1", {}, [&](const Row& cell_row) { cleared.insert((u32)cell_row.i("asset_id")); });
    std::map<u32, bool> playable;
    ctx.st.q("select asset_id, cleared from sphere_cell", {}, [&](const Row& cell_row) {
        u32 asset_id = (u32)cell_row.i("asset_id");
        bool open = false, has_neighbours = false;
        ctx.m.q("select parent_cell_1_id, parent_cell_2_id, parent_cell_3_id, parent_cell_4_id from master_sphere211_floor_asset where id = ?",
                {asset_id}, [&](const Row& asset_row) {
                    for (const char* col : {"parent_cell_1_id", "parent_cell_2_id", "parent_cell_3_id", "parent_cell_4_id"})
                        if (u32 neighbour = (u32)asset_row.i(col)) {
                            has_neighbours = true;
                            if (cleared.count(neighbour)) open = true;
                        }
                });
        playable[asset_id] = !cell_row.i("cleared") && (open || !has_neighbours);
    });
    Value cells = Value::object();
    ctx.st.q("select * from sphere_cell order by asset_id", {}, [&](const Row& cell_row) {
        Value info = Value::object();
        info["player_id"] = player_id;
        info["floor_level"] = (u32)cell_row.i("floor_level");
        info["master_sphere211_asset_id"] = (u32)cell_row.i("asset_id");
        info["master_sphere211_mission_box_id"] = (u32)cell_row.i("mission_box_id");
        info["overwrite_enemy_level"] = (u32)cell_row.i("overwrite_enemy_level");
        info["is_cleared"] = cell_row.i("cleared") != 0;
        info["is_playing"] = cell_row.i("playing") != 0;
        info["can_play"] = playable[(u32)cell_row.i("asset_id")];
        info["is_new"] = playable[(u32)cell_row.i("asset_id")];
        info["updated_at"] = ctx.fmt_time(cell_row.i("updated_at"));
        info["created_at"] = ctx.fmt_time(cell_row.i("created_at"));
        cells[std::to_string((u32)cell_row.i("asset_id"))] = info;
    });
    return cells;
}

// Sphere211EndResult (b: CSphereMissionMenu::Progress, when the board opens: rank != 0 opens
// the ranking-result dialog (CSphereRankingResult: the season, the rank and its reward),
// else previous_season_id != 0 says uimsg_sphere211_season_has_finished3 "新しいシーズンが始まり
// ました"; the client keeps the values until it leaves the menu). (d) So the result is sent
// until a GetSphere211Info has carried it (end_pending), zeros afterwards, so the dialog opens
// once per season end.
void put_end_result(Ctx& ctx, const DiveRow& dive, Value& data) {
    bool pending = sphere_meta(ctx, "end_pending") != 0;
    Value result = Value::object();
    result["previous_season_id"] = pending ? dive.prev_season : 0u;
    result["rank"] = pending ? dive.prev_rank : 0u;
    result["floor_num"] = pending ? dive.prev_floor : 0u;
    result["treasure_num"] = pending ? dive.prev_treasure : 0u;
    data["Sphere211EndResult"] = result;
    if (pending && dive.prev_rank) {  // the ranking reward went into the items (load_dive)
        data["StockItem"] = ctx.stock();
        data["Item"] = ctx.items();
    }
}

}  // namespace

// The keys CApiNotify applies (b: the info classes' fields, port/fakeapi/fields.txt). Maps are
// keyed by the id as a string.
void put_state(Ctx& ctx, const Season& season, Value& data) {
    DiveRow dive = read_dive(ctx);
    u32 player_id = ctx.player_id();
    data["Sphere211CurrentId"] = season.id;
    data["Sphere211NeedsReset"] = 0u;  // (d)
    Value floor_info = Value::object();
    floor_info["floor_level"] = dive.floor;
    floor_info["mission_clear_streak"] = dive.streak;
    data["Sphere211FloorInfo"] = floor_info;
    data["Sphere211FloorAssetInfoMap"] = floor_cells(ctx, player_id);
    Value stamina = Value::object();
    stamina["stamina"] = dive.stamina;
    stamina["stamina_max"] = stamina_max(ctx);
    stamina["stamina_update"] = ctx.fmt_time(dive.stamina_at);
    data["Sphere211StaminaInfo"] = stamina;
    Value treasure = Value::object();
    treasure["num"] = (u32)ctx.st.one("select count(*) from sphere_box", {});
    treasure["total_num"] = dive.treasure_total;
    data["Sphere211TreasureInfo"] = treasure;
    Value departed = Value::object();
    ctx.st.q("select uid from sphere_departed order by uid", {}, [&](const Row& departed_row) {
        Value info = Value::object();
        info["player_character_id"] = (u64)departed_row.i("uid");
        departed[std::to_string((u64)departed_row.i("uid"))] = info;
    });
    data["Sphere211CharacterInfoMap"] = departed;
    Value floor_clear = Value::object();
    floor_clear["floor_level"] = dive.floor;
    floor_clear["master_sphere211_asset_id"] = dive.clear_asset;
    floor_clear["lot_floor_num"] = dive.lot_floor_num;
    data["Sphere211FloorClearInfo"] = floor_clear;
    put_end_result(ctx, dive, data);
    // Player.sphere211_revive_count (CPlayerInfo+0x910 = CParameterManager+0xf48): (b) the sorties
    // with an EX character (role rank 5, CParameterUtility::IsRoleDeity) since the last 帰還;
    // CSphereMissionDetail::NextPhase shows master_global max_revive_count (3, a) minus
    // it as uimsg_sphere211_mission_start_with_deity "使用可能回数 残り %d 回" ("※使用可能回数は帰還
    // することで回復します"). Not counted yet (a rules gap found in R18, PLAN-schema F1): the column
    // is never written, so the dialog always says 3 left.
    if (Value* player = data.find("Player") ? &data["Player"] : nullptr) (*player)["sphere211_revive_count"] = dive.revive_count;
    put_rental(ctx, dive.floor, data);
    // (b) the board's 勲章 button shows CParameterUtility::NumGetAchievement(), a count over the
    // `Achievement` state; the Sphere 211 achievements (types 61 / 62) move with the dive.
    data["Achievement"] = ext::achievement_state(ctx);
}
Value dive_state(Ctx& ctx, const Season& season) {
    Value data = ctx.base_data();
    put_state(ctx, season, data);
    return data;
}

}  // namespace soa::server::sphere211
