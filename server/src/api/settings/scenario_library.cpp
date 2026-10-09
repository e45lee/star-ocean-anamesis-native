// シナリオライブラリ, the story library on the planet select (api/settings/README.md). Port code, not
// guest behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption. Rules in docs/server-rules.md#scenario-library.
//
// What the client reads (b):
//  - `WorldMapScenarioLibraryInfoList`: an InfoBaseValueArray<u32> (its vtable's DeserializeArray),
//    kept in CParameterManager+0x1f08 (0x30-byte CParameterPropertyValue elements, the value at
//    +0x28).
//  - CScenarioLibrary::CreateStoryListFromInfo (@01c74ef0) reads those values as mission ids:
//    master_mission ids for Episode 1's library (CMasterParameterMission::ParameterFromMasterIDList,
//    when CScenarioLibrary+0x2d8 is 0), else master_world_map_mission ids
//    (CMasterParameterWorldMapMission::ParameterFromMasterIDList; it keeps the story missions,
//    mission_type 1 and 2). It groups them by the mission's master_scenario_library_id and lists
//    those master_scenario_library rows as the chapters; a chapter's scenes are its listed missions.
//  - CScenarioLibrary::Progress sends GetScenarioLibraryInfoList(CParameterUI+0x14c), the episode
//    type of the planet the library was opened from; on success CScenarioLibrary::RequestReadyAll.
//
// State: none of its own: the story progress the server keeps (the core's `mission` clears and the
// story campaign's `campaign_clear`).
#include <set>
#include <string>
#include <vector>

#include "api/gen/reply_types.h"  // to_array
#include "api/gen/request_args.h"  // the requests' arguments
#include "api/settings/settings.h"
#include "core/log.h"
#include "core/modules.h"
#include "soaserver/ext.h"

namespace soa::server {

namespace settings {

namespace {

using ext::Row;

// The cleared missions the library lists for this episode type, in id order.
//   (c) The library replays the story of the missions the player has cleared.
//   (a) A mission's chapter is its master_scenario_library_id (master_world_map_mission's, and
//       master_mission's for Episode 1), the chapter's episode its master_scenario_library
//       .episode_type_id; a cleared mission without a chapter isn't listed.
//   The clears: the core's `mission` rows with cleared = 1 and the story campaign's campaign_clear.
std::vector<u32> library_missions(ext::Ctx& ctx, u32 episode_type_id) {
    std::set<u32> cleared;
    ctx.st.q("select mission_id from mission where cleared = 1 union select mission_id from campaign_clear", {},
             [&](const Row& r) { cleared.insert((u32)r.i("mission_id")); });
    std::vector<u32> out;
    for (u32 mission : cleared) {
        const int64_t n = ctx.m.one(
            "select count(*) from ("
            "select master_scenario_library_id as l from master_world_map_mission where id = ? "
            "union all select master_scenario_library_id from master_mission where id = ?) m "
            "join master_scenario_library s on s.id = m.l where s.episode_type_id = ?",
            {mission, mission, episode_type_id});
        if (n > 0) out.push_back(mission);
    }
    return out;
}

// GetScenarioLibraryInfoList(u32 episode_type_id) -> GetScenarioLibraryInfoListRes  fid e08c972e
// API: docs/api.md#getscenariolibraryinfolist
// Rules: docs/server-rules.md#scenario-library
//
// The chapters and scenes シナリオライブラリ lists (CScenarioLibrary).
//   (b) The answer is a list of mission ids the client groups into chapters (above).
//   (c)(a) The player's cleared missions of that episode type that belong to a chapter
//       (library_missions).
// Answers: the player state and WorldMapScenarioLibraryInfoList.
std::vector<u8> get_scenario_library_info_list(ext::Ctx& ctx, const Request& req) {
    const auto a = args::GetScenarioLibraryInfoListArgs::from(req);
    const std::vector<u32> missions = library_missions(ctx, a.episode_type_id);
    LOGI("server", "GetScenarioLibraryInfoList %u: %zu cleared story missions", a.episode_type_id, missions.size());
    Value data = ctx.base_data();
    data["WorldMapScenarioLibraryInfoList"] = infos::to_array(missions);  // (CWorldMapScenarioLibraryInfoList: u32 values)
    return ext::body(data);
}

}  // namespace

void register_scenario_library() { ext::add_api({"GetScenarioLibraryInfoList"}, get_scenario_library_info_list); }

}  // namespace settings

}  // namespace soa::server
