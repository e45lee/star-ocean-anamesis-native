// Sphere 211: the floors, their cells and battles, the warp to the next floor and the sphere
// stamina (api/sphere211/README.md; declared in dive.h and sphere211.h). Port code, not guest
// behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption. Rules in docs/server-rules.md#sphere211.
#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "api/sphere211/dive.h"
#include "core/assets.h"
#include "core/log.h"
#include "core/time.h"

namespace soa::server::sphere211 {

// ---- assets --------------------------------------------------------------------------------
// Whether the game can load an asset "<rel>" (e.g. "BG/bm0012_b01a.aaf"): in the APKs or the
// download dir (--download-dir), with the quality subdirectories the game uses for textures
// (etc2/, etc2/hi/). Decided at run time: more downloaded assets make more missions playable.
// The one asset gate (core/assets.h): the port's asset lookup shared with the event module
// (builtin_data/ in the APKs and the download dir, and the install-time asset pack, with the
// texture quality subdirectories), and the tests' override. Whether no asset source is known at all
// (unit tests without the game's APKs): then the availability check is skipped rather than
// rejecting everything. The mission verdicts are valid for one override (assets::generation).
namespace {
std::map<u32, bool>& playable_cache() {
    static std::map<u32, bool> verdicts;
    static uint64_t generation = 0;
    if (generation != assets::generation()) {
        verdicts.clear();
        generation = assets::generation();
    }
    return verdicts;
}
}  // namespace

void set_asset_check(AssetCheck fn) { assets::set_override(std::move(fn)); }
// A mission is playable when every battle map of its stages (master_mission_stage.master_map_id
// label -> BG/<map>.asf/.aaf/.acf) is present. (Enemy models were all present in the 3.7.0
// download; the map files are what the downloads lack.)
bool mission_playable(Ctx& ctx, u32 mission_id) {
    if (!assets::has_override() && assets::no_source()) return true;
    auto& cache = playable_cache();
    auto cached = cache.find(mission_id);
    if (cached != cache.end()) return cached->second;
    bool playable = true;
    int stages = 0;
    ctx.m.q("select master_map_id_label from master_mission_stage where master_mission_id = ?", {mission_id}, [&](const Row& stage_row) {
        stages++;
        std::string map = stage_row.s("master_map_id_label");
        if (map.empty()) return;
        for (const char* suffix : {"asf", "aaf", "acf"}) {
            std::string rel = "BG/" + map + "." + suffix;
            if (!assets::available(rel)) playable = false;
        }
    });
    if (!stages) playable = false;
    cache[mission_id] = playable;
    return playable;
}

// ---- floors ------------------------------------------------------------------------------
// The floor row of `level` in the season's floor group (a); above the table's last level the last
// row repeats (b: MissionUtility::Sphere211FloorData extends the list with the highest level).
Floor floor_row(Ctx& ctx, const Season& season, u32 level) {
    Floor floor;
    auto fill = [&](const Row& floor_row) {
        floor.id = (u32)floor_row.i("id");
        floor.level = level;
        floor.use_stamina = (u32)floor_row.i("use_stamina");
        floor.base_enemy_level = (u32)floor_row.i("base_enemy_level");
        floor.asset_box_group = (u32)floor_row.i("asset_box_group_id");
        floor.treasure_id = (u32)floor_row.i("treasure_id");
        floor.treasure_num = (u32)floor_row.i("treasure_num");
        floor.floor_clear_treasure_num = (u32)floor_row.i("floor_clear_treasure_num");
        floor.boss_add = (u32)floor_row.i("boss_add_treasure_num");
        floor.rare_add = (u32)floor_row.i("rare_add_treasure_num");
    };
    if (!ctx.m.q("select * from master_sphere211_floor where floor_group_id = ? and level = ?", {season.floor_group, level}, fill))
        ctx.m.q("select * from master_sphere211_floor where floor_group_id = ? and level <= ? order by level desc limit 1",
                {season.floor_group, level}, fill);
    return floor;
}

namespace {
// A cell's battle: a master_sphere211_mission_box row of the cell's box group whose `type` is the
// cell's lottery_type (a: the column pairs 1/2/4/6 match), weighted by `rate` (a), among the
// missions whose maps are available (the rule of this port: decided by the files present).
// (d) When none of the group's rows is playable: any playable row of the same type in the
// season's boxes; when nothing at all is playable, the unfiltered lot (logged).
// Returns (mission box id, mission id); (0, 0) when the group has no row.
std::pair<u32, u32> lot_mission(Ctx& ctx, u32 box_group, u32 type) {
    std::vector<std::pair<u32, std::pair<u32, u32>>> rows, all;
    ctx.m.q("select id, rate, master_mission_id from master_sphere211_mission_box where mission_box_group_id = ? and type = ?", {box_group, type},
            [&](const Row& box_row) {
                std::pair<u32, u32> box{(u32)box_row.i("id"), (u32)box_row.i("master_mission_id")};
                all.push_back({(u32)std::max<int64_t>(1, box_row.i("rate")), box});
                if (mission_playable(ctx, box.second)) rows.push_back(all.back());
            });
    if (rows.empty()) {
        ctx.m.q("select id, rate, master_mission_id from master_sphere211_mission_box where type = ? order by id", {type}, [&](const Row& box_row) {
            std::pair<u32, u32> box{(u32)box_row.i("id"), (u32)box_row.i("master_mission_id")};
            if (mission_playable(ctx, box.second)) rows.push_back({(u32)std::max<int64_t>(1, box_row.i("rate")), box});
        });
        if (!rows.empty()) LOGW("server", "Sphere211: box group %u type %u has no playable mission; using another box's", box_group, type);
    }
    if (rows.empty()) {
        rows = all;
        if (!rows.empty()) LOGW("server", "Sphere211: no playable mission of type %u at all; lotting unavailable ones", type);
    }
    int k = weighted_index(ctx, rows);
    return k < 0 ? std::pair<u32, u32>{0, 0} : rows[k].second;
}

// (a) the cell's overwrite_enemy_level_group_id lotted by rate; 0 when it has none.
u32 lot_enemy_level(Ctx& ctx, const Row& asset_row) {
    if (asset_row.null("overwrite_enemy_level_group_id") || !asset_row.i("overwrite_enemy_level_group_id")) return 0;
    std::vector<std::pair<u32, u32>> levels;
    ctx.m.q("select rate, enemy_level from master_sphere211_overwrite_enemy_level where overwrite_enemy_level_group_id = ?",
            {asset_row.i("overwrite_enemy_level_group_id")},
            [&](const Row& level_row) { levels.push_back({(u32)level_row.i("rate"), (u32)level_row.i("enemy_level")}); });
    int k = weighted_index(ctx, levels);
    return k >= 0 ? levels[k].second : 0;
}
}  // namespace

// Generates floor `level`: (a) one asset template lotted from the floor's asset box by weight,
// its cells, each with a lotted battle and (a) an enemy level from its overwrite group (by rate).
void enter_floor(Ctx& ctx, const Season& season, u32 level) {
    Floor floor = floor_row(ctx, season, level);
    std::vector<std::pair<u32, u32>> templates;
    ctx.m.q("select weight, asset_id from master_sphere211_floor_asset_box where asset_group_id = ?", {floor.asset_box_group},
            [&](const Row& box_row) { templates.push_back({(u32)box_row.i("weight"), (u32)box_row.i("asset_id")}); });
    int k = weighted_index(ctx, templates);
    u32 group = k < 0 ? 0 : templates[k].second;
    ctx.st.exec("delete from sphere_cell");
    ServerTime t = ctx.now();
    int cells = 0;
    ctx.m.q("select * from master_sphere211_floor_asset where floor_group_id = ?", {group}, [&](const Row& asset_row) {
        u32 asset_id = (u32)asset_row.i("id");
        u32 box_id = 0, mission_id = 0;
        if (!asset_row.null("mission_box_group_id") && asset_row.i("mission_box_group_id")) {
            auto [box, mission] = lot_mission(ctx, (u32)asset_row.i("mission_box_group_id"), (u32)asset_row.i("lottery_type"));
            box_id = box;
            mission_id = mission;
        }
        u32 enemy_level = lot_enemy_level(ctx, asset_row);
        ctx.st.q(
            "insert into sphere_cell (asset_id, floor_level, mission_box_id, mission_id, overwrite_enemy_level, created_at, updated_at) "
            "values (?,?,?,?,?,?,?)",
            {asset_id, level, box_id, mission_id, enemy_level, t, t});
        cells++;
    });
    ctx.st.q("update sphere set floor_level = ?, asset_group = ?, clear_asset = 0, lot_floor_num = 0, entered_at = ?", {level, group, t});
    ctx.st.q(
        "insert into sphere_rank (season_id, floor_level, entered_at) values (?, ?, ?) "
        "on conflict(season_id) do update set floor_level = max(floor_level, excluded.floor_level), "
        "entered_at = case when excluded.floor_level > floor_level then excluded.entered_at else entered_at end",
        {season.id, level, t});
    log_event(ctx, LogKind::kFloor, level);
    // (a) the rental slot: "1フロアにつき合計３回" (master_text cp0003_tutorial_sphere211_007), so a
    // new floor lends again (d: every lender afresh)
    ctx.st.exec("delete from sphere_rental");
    // read by port/scripts/sphere211_session.sh, sphere211_continue_session.sh (the floor-1 map)
    LOGI("server", "Sphere211: floor %u (floor row %u), map %u with %d cells", level, floor.id, group, cells);
}

// The warp access (b: MissionUtility::Sphere211WarpAccessLevelAndExp / GetSphere211TransferRateId):
// (a) the highest master_sphere211_floor_transfer_level open now whose required_treasure the
// season's gathered boxes reach, and its rate group's floor_num lotted by weight.
u32 lot_floor_num(Ctx& ctx, u32 treasure_total) {
    ServerTime t = ctx.now();
    u32 group = 0, best = 0;
    ctx.m.q("select * from master_sphere211_floor_transfer_level order by transfer_level", {}, [&](const Row& level_row) {
        if (!open_at(level_row.s("opened_at"), level_row.s("closed_at"), t)) return;
        if ((u32)level_row.i("required_treasure") <= treasure_total && (u32)level_row.i("transfer_level") >= best) {
            best = (u32)level_row.i("transfer_level");
            group = (u32)level_row.i("floor_transfer_rate_group_id");
        }
    });
    std::vector<std::pair<u32, u32>> rates;
    ctx.m.q("select weight, floor_num from master_sphere211_floor_transfer_rate where transfer_rate_group_id = ?", {group},
            [&](const Row& rate_row) { rates.push_back({(u32)rate_row.i("weight"), (u32)rate_row.i("floor_num")}); });
    int k = weighted_index(ctx, rates);
    return k < 0 ? 1 : std::max<u32>(1, rates[k].second);  // (d) at least the next floor
}

// A dive at floor 0 (new, or after a return) starts on floor 1 (d; b: the menu needs the floor's
// cells, MissionUtility::GetEventMissionList type 5 lists them, and with none it says the season
// has finished; the warp (転移) to deeper floors is offered when a floor is cleared).
void start_dive_if_idle(Ctx& ctx, const Season& season) {
    u32 floor = (u32)ctx.st.one("select floor_level from sphere where id = 1", {});
    u32 clear_asset = (u32)ctx.st.one("select clear_asset from sphere where id = 1", {});
    if (floor || clear_asset) return;
    enter_floor(ctx, season, 1);
}

// Finds the cell a request names: (b) Sphere211MissionStart / End / Failed / Continue send
// CStageManager+0x68 / +0x6c: 1 and the cell's asset id in the captured requests (the first's
// meaning isn't known); either argument is matched against asset and mission ids. Else the cell
// being played.
bool find_cell(Ctx& ctx, const Request& req, u32& asset_id, u32& mission_id) {
    asset_id = mission_id = 0;
    for (size_t k = 0; k < std::min<size_t>(2, req.ints.size()) && !asset_id; k++) {
        u32 id = (u32)req.ints[k];
        ctx.st.q("select asset_id, mission_id from sphere_cell where asset_id = ? or (mission_id = ? and cleared = 0) order by playing desc limit 1",
                 {id, id}, [&](const Row& cell_row) {
                     asset_id = (u32)cell_row.i("asset_id");
                     mission_id = (u32)cell_row.i("mission_id");
                 });
    }
    if (!asset_id)
        ctx.st.q("select asset_id, mission_id from sphere_cell where playing = 1 limit 1", {}, [&](const Row& cell_row) {
            asset_id = (u32)cell_row.i("asset_id");
            mission_id = (u32)cell_row.i("mission_id");
        });
    return asset_id != 0;
}

// ---- stamina -------------------------------------------------------------------------------
// (a) master_global sphere_stamina_max (9) and sphere_stamina_recovery_time (17280 s a point);
// the gauge regenerates like AP (rules::regen_stamina) and starts full (d).
u32 stamina_max(Ctx& ctx) { return ctx.global_u32("sphere_stamina_max", 9); }
namespace {
u32 stamina_period(Ctx& ctx) { return std::max<u32>(1, ctx.global_u32("sphere_stamina_recovery_time", 17280)); }
}  // namespace
void tick_stamina(Ctx& ctx) {
    u32 stamina = 0;
    ServerTime stamina_at;
    ctx.st.q("select stamina, stamina_at from sphere where id = 1", {}, [&](const Row& sphere_row) {
        stamina = (u32)sphere_row.i("stamina");
        stamina_at = sphere_row.time("stamina_at");
    });
    ServerTime t = ctx.now();
    if (t <= stamina_at) return;
    auto [regenerated, carry] = rules::regen_stamina(stamina, stamina_max(ctx), (u64)(t - stamina_at), stamina_period(ctx));
    ctx.st.q("update sphere set stamina = ?, stamina_at = ?", {regenerated, t - (int64_t)carry});
}

}  // namespace soa::server::sphere211
