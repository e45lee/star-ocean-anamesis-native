// The story campaign's lists (api/campaign/campaign.h): what the player can see of Episode 1
// (ActiveMissionList) and of the world map (ActiveWorldMapMissionList, Episodes 2 and 3), and the
// campaign's Player keys. Port code, not guest behaviour. Every rule is labelled with its source
// (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption, here and in
// docs/server-rules.md#campaign.
#include <algorithm>
#include <ctime>
#include <map>
#include <string>
#include <vector>

#include "api/campaign/campaign.h"
#include "soaserver/server.h"  // clock_now

namespace soa::server::campaign {
namespace {

// The listed missions by area (Episode 1) or by cell (the world map), each list in order_id order.
using MissionsBy = std::map<u32, std::vector<const Mission*>>;

// (a) master_* opened_at / closed_at ("YYYY-MM-DD hh:mm:ss", JST in the data; compared as text
// against the current local time, which is exact to the day). Empty = no limit. A variant of
// core/time.h's open_at with its own semantics (a string compare), kept apart on purpose.
bool in_window(const std::string& opened, const std::string& closed) {
    char now[32];
    time_t t = (time_t)clock_now().v;  // the server clock (--clock)
    strftime(now, sizeof now, "%Y-%m-%d %H:%M:%S", localtime(&t));
    if (!opened.empty() && opened > now) return false;
    if (!closed.empty() && closed < now) return false;
    return true;
}

// ---- world map (Episodes 2 and 3) ----
// (a) master_world_map_progress: when the player's progress in an episode reaches `progress` (and
// `unlock_condition_mission_id`, if any, is cleared), the group `unlock_mission_group_id` opens.
// (d) The episode's progress is the highest master_world_map_group_mission.progress among the
// story groups with a cleared mission (0 at the start): the story groups' progress values chain
// the progress rows one after the other in the data.
u32 episode_of_map(const Master& m, u32 map) {
    auto it = m.world_maps.find(map);
    return it == m.world_maps.end() ? 0 : it->second.episode;
}
u32 episode_of(const Master& m, const Mission& mission) {
    auto cell = m.cells.find(mission.cell);
    return cell == m.cells.end() ? 0 : episode_of_map(m, cell->second.map);
}
u32 episode_progress(const Master& m, const State& s, u32 episode) {
    u32 progress = 0;
    for (u32 id : s.cleared) {
        auto it = m.missions.find(id);
        if (it == m.missions.end() || !it->second.cell) continue;
        auto group = m.group_progress.find(it->second.group);
        if (group != m.group_progress.end() && episode_of(m, it->second) == episode) progress = std::max(progress, group->second);
    }
    return progress;
}
bool group_open(const Master& m, const State& s, u32 episode, u32 group) {
    u32 progress = episode_progress(m, s, episode);
    for (const ProgressRow& row : m.progress)
        if (row.group == group && row.episode == episode && row.progress <= progress && (!row.condition || s.cleared.count(row.condition)))
            return true;
    return false;
}
bool world_map_available(const Master& m, const State& s, const Mission& mission) {
    auto cell = m.cells.find(mission.cell);
    if (cell == m.cells.end()) return false;
    auto map = m.world_maps.find(cell->second.map);
    if (map == m.world_maps.end()) return false;
    if (!in_window(map->second.opened, map->second.closed) || !in_window(cell->second.opened, cell->second.closed) ||
        !in_window(mission.opened, mission.closed))
        return false;
    if (!group_open(m, s, map->second.episode, mission.group)) return false;
    if (mission.unlock && !s.cleared.count(mission.unlock)) return false;
    if (mission.visible && !s.cleared.count(mission.visible)) return false;
    return true;
}

bool has_new(const State& s, const std::vector<const Mission*>& missions) {
    for (auto* mission : missions)
        if (!s.cleared.count(mission->id)) return true;
    return false;
}
void sort_by_order(std::vector<const Mission*>& missions) {
    std::sort(missions.begin(), missions.end(), [](const Mission* a, const Mission* b) { return a->order < b->order; });
}

}  // namespace

// (a) A mission is listed when its unlock mission (master_mission.unlock_mission_id) is cleared, or
// it has none, and its visible_mission_id (if any) is cleared, within its date window.
// Only Episode 1 missions (areas planet00..planet10) take part: the Sample / planet98 / planet99
// areas are debug and training content. (d)
bool available(const Master& m, const State& s, const Mission& mission) {
    if (mission.cell) return world_map_available(m, s, mission);
    auto area = m.areas.find(mission.area);
    if (area == m.areas.end()) return false;
    const std::string& area_label = area->second.label;
    if (area_label.rfind("planet", 0) != 0 || area_label.rfind("planet98", 0) == 0 || area_label.rfind("planet99", 0) == 0) return false;
    if (!in_window(area->second.opened, area->second.closed) || !in_window(mission.opened, mission.closed)) return false;
    if (mission.unlock && !s.cleared.count(mission.unlock)) return false;
    if (mission.visible && !s.cleared.count(mission.visible)) return false;
    return true;
}

// ActiveWorldMapMissionList ((b) the info classes; CWorldMapMenu::CollectMaster*FromInfo read
// CParameterManager+0x1e18 / +0x1e70 / +0x1ec0):
//   WorldMap:         {map id: CWorldMapInfo {area_ct, is_new, is_last_play, opened_at, closed_at}}
//   WorldMapCellList: {map id: {cell id: CWorldMapCellInfo {}}}
//   WorldMapMission:  {cell id: [CWorldMapMissionElementInfo {id, is_new, is_clear, is_last_play,
//                      mission_group_id, difficulty, mission_type, scenario_library_id}]}
Value build_world_map_list(const State& s) {
    const Master& m = master();
    MissionsBy by_cell;
    for (auto& [id, mission] : m.missions)
        if (mission.cell && available(m, s, mission) && (!s.wm_episode || episode_of(m, mission) == s.wm_episode))
            by_cell[mission.cell].push_back(&mission);
    std::map<u32, std::vector<u32>> cells_by_map;
    for (auto& [cell, missions] : by_cell) {
        sort_by_order(missions);
        cells_by_map[m.cells.at(cell).map].push_back(cell);
    }
    u32 last_cell = 0;
    if (auto it = m.missions.find(s.last_play); it != m.missions.end()) last_cell = it->second.cell;
    u32 last_map = last_cell ? m.cells.at(last_cell).map : 0;
    Value list = Value::object();
    Value& maps = list["WorldMap"] = Value::object();
    for (auto& [map, cells] : cells_by_map) {
        bool any_new = false;
        for (u32 cell : cells) any_new |= has_new(s, by_cell[cell]);
        const WorldMap& world_map = m.world_maps.at(map);
        Value& info = maps[std::to_string(map)] = Value::object();
        info["area_ct"] = (u64)cells.size();  // (d) the number of listed cells
        info["is_new"] = any_new;
        info["is_last_play"] = map == last_map;
        info["opened_at"] = world_map.opened;
        info["closed_at"] = world_map.closed;
    }
    Value& cell_lists = list["WorldMapCellList"] = Value::object();
    for (auto& [map, cells] : cells_by_map) {
        Value& cell_list = cell_lists[std::to_string(map)] = Value::object();
        for (u32 cell : cells) cell_list[std::to_string(cell)] = Value::object();
    }
    Value& mission_lists = list["WorldMapMission"] = Value::object();
    for (auto& [cell, missions] : by_cell) {
        Value& mission_list = mission_lists[std::to_string(cell)] = Value::array();
        for (auto* mission : missions) {
            bool clear = s.cleared.count(mission->id) != 0;
            Value& element = mission_list.push(Value::object());
            element["id"] = mission->id;
            element["is_new"] = !clear;
            element["is_clear"] = clear;
            element["is_last_play"] = mission->id == s.last_play;
            element["mission_group_id"] = mission->group;
            element["difficulty"] = mission->difficulty;
            element["mission_type"] = mission->type;
            element["scenario_library_id"] = mission->library;
        }
    }
    return list;
}

// Player.world_map_progress (Episode 2, `chapter_1`) and world_map_progress_ep3 (`Episode03`).
Value build_player(const State& s, bool views) {
    const Master& m = master();
    u32 episode2 = 0, episode3 = 0;
    for (auto& [id, world_map] : m.world_maps) {
        if (world_map.episode_label == "chapter_1") episode2 = world_map.episode;
        if (world_map.episode_label == "Episode03") episode3 = world_map.episode;
    }
    Value player = Value::object();
    player["world_map_progress"] = (u64)episode_progress(m, s, episode2);
    player["world_map_progress_ep3"] = (u64)episode_progress(m, s, episode3);
    if (views) {
        // (d) A returning player (--campaign-seed) has seen the menus' one-time tutorials:
        // CPlayerInfo view_status / view_status2 (u64 bit sets read by
        // CParameterUtility::IsTutorialViewStatus, (b)) all set. A new player keeps them clear.
        player["view_status"] = ~0ull;
        player["view_status2"] = ~0ull;
    }
    return player;
}

// ActiveMissionList (the response key CActiveMissionListInfo parses; shapes from the client's info
// classes, (b)):
//   Planet:  {planet id: CPlanetInfo {area_ct, is_new, is_last_play}}
//   Area:    {planet id: {area id: CAreaInfo {mission_ct, is_new, is_last_play, is_start_bighunt}}}
//   Mission: {area id: [CMissionElementInfo {id, is_new, is_clear, is_last_play}]}
// Maps are keyed by the id as a string (InfoBaseNumberMap parses the key with istream >> u64).
Value build_active_mission_list(const State& s) {
    const Master& m = master();
    MissionsBy by_area;
    for (auto& [id, mission] : m.missions)
        if (mission.area && available(m, s, mission)) by_area[mission.area].push_back(&mission);
    std::map<u32, std::vector<u32>> areas_by_planet;
    for (auto& [area, missions] : by_area) {
        sort_by_order(missions);
        areas_by_planet[m.areas.at(area).planet].push_back(area);
    }
    u32 last_area = 0, last_planet = 0;
    if (auto it = m.missions.find(s.last_play); it != m.missions.end()) {
        last_area = it->second.area;
        if (auto area = m.areas.find(last_area); area != m.areas.end()) last_planet = area->second.planet;
    }
    Value list = Value::object();
    Value& planets = list["Planet"] = Value::object();
    for (auto& [planet, areas] : areas_by_planet) {
        bool any_new = false;
        for (u32 area : areas) any_new |= has_new(s, by_area[area]);
        Value& info = planets[std::to_string(planet)] = Value::object();
        info["area_ct"] = (u64)areas.size();  // (d) the number of listed areas
        info["is_new"] = any_new;             // (d) an uncleared mission is listed
        info["is_last_play"] = planet == last_planet;
    }
    Value& area_lists = list["Area"] = Value::object();
    for (auto& [planet, areas] : areas_by_planet) {
        Value& planet_areas = area_lists[std::to_string(planet)] = Value::object();
        for (u32 area : areas) {
            Value& info = planet_areas[std::to_string(area)] = Value::object();
            info["mission_ct"] = (u64)by_area[area].size();  // (d) the number of listed missions
            info["is_new"] = has_new(s, by_area[area]);
            info["is_last_play"] = area == last_area;
            info["is_start_bighunt"] = false;  // (d) no big-hunt event running
        }
    }
    Value& mission_lists = list["Mission"] = Value::object();
    for (auto& [area, missions] : by_area) {
        Value& mission_list = mission_lists[std::to_string(area)] = Value::array();
        for (auto* mission : missions) {
            bool clear = s.cleared.count(mission->id) != 0;
            Value& element = mission_list.push(Value::object());
            element["id"] = mission->id;
            element["is_new"] = !clear;  // (d) new until cleared
            element["is_clear"] = clear;
            element["is_last_play"] = mission->id == s.last_play;
        }
    }
    return list;
}

}  // namespace soa::server::campaign
