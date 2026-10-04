#pragma once
// The story campaign's internals (api/campaign/; the public API is soaserver/api_campaign.h): the
// master data it reads (master_data.cpp), the player's progress (progress.cpp), the lists it
// builds (lists.cpp) and the response splice (campaign.cpp). Port code, not guest behaviour; rules
// in docs/server-rules.md#campaign, labels (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption.
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "soaserver/api_campaign.h"
#include "soaserver/msgpack.h"

namespace soa::server::campaign {

// ---- master data (master_data.cpp) ------------------------------------------------------------
// A master_mission row (Episode 1) or a master_world_map_mission row (Episodes 2 and 3: cell != 0,
// area = 0).
struct Mission {
    u32 id = 0;
    std::string label;
    u32 area = 0;
    u32 order = 0;
    u32 unlock = 0;   // unlock_mission_id (0: none)
    u32 visible = 0;  // visible_mission_id (0: none)
    u32 stamina = 0;
    std::string opened, closed;
    bool talk = false;  // has a talk_event_id: a story scene (MissionTalk), not a battle
    // World map missions only:
    u32 cell = 0, group = 0, difficulty = 0, type = 0, library = 0;
};
struct WorldMap {  // master_world_map
    u32 id = 0, episode = 0, order = 0;
    std::string label, episode_label, opened, closed;
};
struct Cell {  // master_world_map_cell
    u32 id = 0, map = 0;
    std::string label, opened, closed;
};
struct ProgressRow {  // master_world_map_progress
    u32 episode = 0, progress = 0, condition = 0, group = 0;
};
struct Area {  // master_area
    u32 id = 0, planet = 0, order = 0;
    std::string label, opened, closed;
};
struct Planet {  // master_planet
    u32 id = 0, order = 0;
    std::string label;
};
struct Stage {  // master_mission_stage
    u32 id = 0, serial = 0, order = 0, layout = 0, enemy_party = 0, map = 0;
    bool boss = false, surprise = false;
    std::string label, layout_label, map_label, bgm;
};
// The campaign's master tables, loaded once (master()).
struct Master {
    bool loaded = false;
    std::map<u32, Mission> missions;
    std::map<u32, Area> areas;
    std::map<u32, Planet> planets;
    std::map<u32, std::vector<Stage>> stages;  // by mission id, in order_id order
    std::map<u32, WorldMap> world_maps;
    std::map<u32, Cell> cells;
    std::map<u32, u32> group_progress;  // master_world_map_group_mission.progress (story groups)
    std::vector<ProgressRow> progress;
};
// The master data, loaded on first use from the server's master DB (open_master: --campaign-master-db,
// else the 3.7.0 DB, else the offline build's).
const Master& master();

// ---- the player's progress (progress.cpp) -----------------------------------------------------
struct State {
    bool loaded = false;
    std::set<u32> cleared;
    u32 last_play = 0;
    u32 playing = 0;     // the mission of the last MissionStart
    bool seeded = false;      // --campaign-seed: a returning player
    u32 wm_episode = 0;  // the episode of the last GetWorldMapInfoList (0: all)
};
// The progress, loaded from the state DB (campaign_clear, campaign_last; PLAN-schema S12) on first
// use (and seeded); callers hold the campaign's lock (lock()). The campaign reads and writes the
// DB through ext::with_live_server, so the lock order is the campaign's, then the server's: it
// runs around a request (core/lifecycle.cpp), never inside a handler.
State& state();
std::mutex& lock();
// Records a clear (first clear or again) as the last play and saves the progress (the state DB, in
// its own transaction); logs `why` and what the clear unlocks.
void clear_mission(State& state, u32 id, const char* why);

// ---- the lists (lists.cpp) --------------------------------------------------------------------
// Whether a mission is listed for this progress (Episode 1 or the world map).
bool available(const Master& master, const State& state, const Mission& mission);
// ActiveWorldMapMissionList {WorldMap, WorldMapCellList, WorldMapMission}.
Value build_world_map_list(const State& state);
// The campaign's Player keys (world_map_progress, world_map_progress_ep3; with `views`, the
// returning player's view_status / view_status2).
Value build_player(const State& state, bool views);
// ActiveMissionList {Planet, Area, Mission}.
Value build_active_mission_list(const State& state);

// ---- the response splice (campaign.cpp) -------------------------------------------------------
// Merges two maps: the entries of `base` whose keys `over` lacks, then `over`'s entries. `over`
// unchanged if either isn't a map.
Value merge_maps(const Value& base, const Value& over);
// Rewrites root = {..., "data": {entries...}, ...} so that data holds `add` (splice rules in
// campaign.cpp). False if the root isn't of that shape.
bool splice_data(Value& root, const std::vector<std::pair<std::string, Value>>& add);
// The body as a Value: false when it isn't one msgpack value that encodes back to the same bytes.
bool decode_body(const std::vector<char>& body, Value& out);

}  // namespace soa::server::campaign
