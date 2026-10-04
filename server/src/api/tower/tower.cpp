// Local server (--restore-tower, opt-in): the tower (試練の遺跡). 3.7.0 had it closed;
// the opt-in opens it on the client (native/restore/restore_tower.cpp, docs/client-changes.md "Tower") and
// this module lists its areas and missions. Labels: (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption.
#include "api/tower/tower.h"

#include <cstdio>
#include <cstdlib>
#include <set>
#include <vector>

#include "api/missions/missions.h"  // MissionType
#include "core/log.h"
#include "core/time.h"
#include "soaserver/config.h"
#include "soaserver/events.h"
#include "core/modules.h"

namespace soa::server::tower {
using namespace ext;

// ---- the areas' banners -------------------------------------------------------------------
// The client lists a tower area only when its master_banner_id names a master_banner row (b:
// MissionUtility::tAreaInfo's constructor zeroes the area id when the id isn't among
// CUIUtility::CollectMasterBanner's rows, and GetEventAreaList drops it). 3.7.0's master_banner
// no longer has banner801..banner805, the banners of the five permanent areas tower_01..05 (a:
// master_tower_area still names them), while their images Image/banner_TrialSpace_001..005.aif
// are in the 3.7.0 download. The 16 surviving tower banner rows all show
// banner_TrialSpace_<the area's tower number, 3 digits>[_002] (a), so (d) a missing banner row is
// stood in with the first of banner_TrialSpace_NNN, _NNN_002, _NNN_001 whose image the port can
// load (decided at run time from the asset sources); no image, no row (the area stays hidden).
std::string standin_banner_image(const std::string& area_label) {
    size_t underscore = area_label.rfind('_');
    if (underscore == std::string::npos) return "";
    int tower_number = atoi(area_label.c_str() + underscore + 1);
    if (tower_number <= 0) return "";
    char base[64];
    snprintf(base, sizeof base, "banner_TrialSpace_%03d", tower_number);
    for (const char* suffix : {"", "_002", "_001"}) {
        std::string image = std::string(base) + suffix;
        if (events::asset_available("Image/" + image + ".aif")) return image;
    }
    return "";
}

bool area_banner_ok(Sql& master, const Row& area_row) {
    u32 banner = (u32)area_row.i("master_banner_id");
    if (!banner) return false;  // (b) no banner id: the constructor's other path needs a banner too
    if (master.one("select count(*) from master_banner where id = ?", {banner})) return true;
    return !standin_banner_image(area_row.s("id_label")).empty();
}

int client_banners(Sql& client_master) {
    struct StandIn {
        u32 banner_id;
        std::string label, image, opened_at, closed_at;
    };
    std::vector<StandIn> stand_ins;
    client_master.q(
        "select a.id_label, a.master_banner_id, a.master_banner_id_label, a.opened_at, a.closed_at from master_tower_area a "
        "where coalesce(a.master_banner_id, 0) != 0 and not exists (select 1 from master_banner b where b.id = a.master_banner_id)",
        {}, [&](const Row& area_row) {
            std::string image = standin_banner_image(area_row.s("id_label"));
            if (!image.empty())
                stand_ins.push_back({(u32)area_row.i("master_banner_id"), area_row.s("master_banner_id_label"), image, area_row.s("opened_at"),
                                     area_row.s("closed_at")});
        });
    for (auto& stand_in : stand_ins) {
        client_master.q(
            "insert into master_banner (id, id_label, order_id, url, image, is_home, opened_at, closed_at) values (?, ?, 0, '', ?, 0, ?, ?)",
            {stand_in.banner_id, stand_in.label, stand_in.image, stand_in.opened_at, stand_in.closed_at});
        LOGI("server", "tower: stand-in banner %s (%s) in the client's master", stand_in.label.c_str(),
             stand_in.image.c_str());  // read by tower_session.sh
    }
    return (int)stand_ins.size();
}

// ---- tower (opt-in: --restore-tower) ----------------------------------------------
// 3.7.0 had the tower closed (CParameterUtility::IsOpenTowerMission returned 0, b); the opt-in
// opens it on the client (docs/client-changes.md "Tower") and the server lists its areas and
// missions with every full player load. Its battles are the core MissionStart / MissionEnd of
// master_tower_mission rows (Common::MissionType 2, b: MasterMissionModel::GetFromMissionID).
//   ActiveTowerMissionList {TowerArea: {area id: {mission_ct, is_new, is_last_play}},
//                           TowerMission: {area id: [{id, is_new, is_clear, is_last_play}]}}
//   (b: the shape of the event lists, ActiveEventMissionList; MissionUtility::GetEventAreaList
//   type 2 walks the TowerArea map, CParameterManager+0x1c68, by area id; seen working in game),
//   TowerSchedule [{opened_at, closed_at}].
// Rules (docs/server-rules.md#tower): (a) the areas whose opened_at .. closed_at covers the
// event calendar (tower_01..05 run until 2030); (b)+(d) only areas whose banner the client finds
// (area_banner_ok); (a) a mission is listed when it has no unlock_mission_id or that mission is
// cleared; (d) missions whose battle maps are missing are left out (the files decide, at run
// time); (a) master_global Tower_Challenge_Count as Player.tower_try_count, (d) not counted down.
namespace {

// The listed floors (missions) of one area: CMissionElementInfo {id, is_new, is_clear,
// is_last_play}, in order_id order; `any_new` when one is new.
Value area_floors(Ctx& ctx, u32 area_id, const std::set<u32>& cleared, u32 last_played, bool& any_new) {
    Value floors = Value::array();
    any_new = false;
    ctx.m.q("select id, unlock_mission_id from master_tower_mission where master_tower_area_id = ? order by order_id", {area_id},
            [&](const Row& mission_row) {
                u32 mission = (u32)mission_row.i("id"), unlocked_by = (u32)mission_row.i("unlock_mission_id");
                if (unlocked_by && !cleared.count(unlocked_by)) return;
                if (!events::mission_playable(ctx.m, mission)) return;
                bool clear = cleared.count(mission) != 0;
                Value floor = Value::object();
                floor["id"] = mission;
                floor["is_new"] = !clear;  // (d) new until cleared
                floor["is_clear"] = clear;
                floor["is_last_play"] = mission == last_played;
                any_new |= !clear;
                floors.push(floor);
            });
    return floors;
}

}  // namespace

void lists(Ctx& ctx, Value& data) {
    EventTime now = ctx.event_now();  // dated content only the server decides: the event calendar
    std::set<u32> cleared;
    ctx.st.q("select mission_id from mission where cleared = 1", {},
             [&](const Row& mission_row) { cleared.insert((u32)mission_row.i("mission_id")); });
    u32 last_played = (u32)ctx.st.one("select mission_id from play where id = 1", {}, 0);
    Value areas = Value::object(), missions = Value::object(), schedule = Value::array();
    int area_count = 0, mission_count = 0;
    ctx.m.q("select * from master_tower_area order by order_id", {}, [&](const Row& area_row) {
        std::string opened_at = area_row.s("opened_at"), closed_at = area_row.s("closed_at");
        if (!open_at(opened_at, closed_at, now)) return;
        if (!area_banner_ok(ctx.m, area_row)) return;  // (b)+(d) the client wouldn't show it
        u32 area_id = (u32)area_row.i("id");
        bool any_new = false;
        Value floors = area_floors(ctx, area_id, cleared, last_played, any_new);
        if (floors.arr.empty()) return;
        Value area = Value::object();
        area["mission_ct"] = (u32)floors.arr.size();
        area["is_new"] = any_new;
        area["is_last_play"] = false;
        areas[std::to_string(area_id)] = area;
        mission_count += (int)floors.arr.size();
        missions[std::to_string(area_id)] = floors;
        Value term = Value::object();
        term["opened_at"] = opened_at;
        term["closed_at"] = closed_at;
        schedule.push(term);
        area_count++;
    });
    Value active = Value::object();
    active["TowerArea"] = areas;
    active["TowerMission"] = missions;
    data["ActiveTowerMissionList"] = active;
    data["TowerSchedule"] = schedule;
    if (data.find("Player")) data["Player"]["tower_try_count"] = ctx.global_u32("Tower_Challenge_Count", 3);
    LOGI("server", "tower: %d areas, %d missions listed", area_count, mission_count);  // read by tower_session.sh
}

namespace {

// OnPlayerLoad (with --restore-tower): ActiveTowerMissionList, TowerSchedule and
// Player.tower_try_count on every full player state (lists above).
void load_tower(Ctx& ctx, const Request&, Value& data) {
    if (config().restore_tower) lists(ctx, data);
}

// MissionResultExtra (with --restore-tower): a tower battle's MissionEnd reports the lists again,
// so a cleared floor unlocks the next one at once (d: when the online server refreshed them isn't
// known).
void tower_mission_result(Ctx& ctx, const MissionInfo& info, Value& data) {
    if (config().restore_tower && MissionType(info.type) == MissionType::kTower) lists(ctx, data);
}

// ClientMaster (with --restore-tower): the client's master copy gets the stand-in banner rows (a
// data override, server side; client_banners above).
void client_tower_banners(Sql& client_master, ServerTime, EventTime) {
    if (config().restore_tower) client_banners(client_master);
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_tower() {
    using namespace ext;
    add_player_load(load_tower);
    add_mission_result_extra(tower_mission_result);
    add_client_master(client_tower_banners);
}

}  // namespace soa::server::tower
