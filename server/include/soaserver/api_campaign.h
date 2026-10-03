#pragma once
// The local server's story campaign (restore run; port code, not guest
// behaviour). It keeps the player's campaign progress (cleared missions, last mission played) and
// gives the unchanged client the data the 3.7.0 server sent for it:
//   - ActiveMissionList {Planet, Area, Mission}: the Episode 1 planets, areas and missions the player
//     can see, with is_clear / is_new / is_last_play (CParameterManager+0x1be0.., read by
//     CMissionMenu and CParameterUtility::GetMissionInfoWithId);
//   - the world map's ActiveWorldMapMissionList and Player.world_map_progress* (Episodes 2 and 3);
//   - progress on MissionEnd (a won battle mission), MissionTalk and EndMissionTalk (a story scene
//     played).
// MissionStart's MissionParameter is the server core's (api/missions/). The internals:
// server/src/api/campaign/campaign.h.
// Every rule is labelled with its source (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption, here and in docs/server-rules.md.
#include <cstdint>
#include <string>
#include <vector>

#include "soaserver/server.h"

namespace soa::server::campaign {

bool enabled();  // config().enabled (soa: --server inproc, the default)

// A request method was called (the same Request the server gets; server::answer calls it for
// every request, before the server handles it).
void on_request(const Request& r);

// Adjusts the response body (msgpack {"data": {...}, "status": n}) about to be delivered for
// FunctionID `fid` (`name`: the request's method, for the log). Returns true if it changed it.
// server::answer calls it for every accepted or unhandled answer.
bool on_response(uint32_t fid, const std::string& name, std::vector<char>& body);

// EndMissionTalk(mission id): the story scene of a story mission has ended (3.7.0's
// CEventScenario::Exit sends it; server::end_mission_talk passes it on when no event module's story
// mission takes it). Clears the mission if it is a story mission ((b) master talk_event_id).
void end_mission_talk(uint32_t mission);

// For tests and tools: the ActiveMissionList value (msgpack) for the current progress.
std::vector<uint8_t> active_mission_list_msgpack();

}  // namespace soa::server::campaign
