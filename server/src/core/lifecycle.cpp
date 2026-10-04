// The request lifecycle (soaserver/server.h answer): one for both hosts. Port code, not guest
// behaviour. soa's FakeApiCaller route (port/src/native/api/fakeapi.cpp) and soa-server's wire
// (net/game.cpp) deliver every request through answer(); before step R9 of
// server/PLAN-readability.md each host wired the story campaign and EndMissionTalk itself.
#include <vector>

#include "soaserver/api_campaign.h"
#include "soaserver/events.h"
#include "soaserver/server.h"

namespace soa::server {

namespace {

constexpr u32 kFidGetPlayMission = 0x7c1b7a1b;

// The story campaign's additions to an answer (soa-server's wire route): ActiveMissionList on every
// reply, the campaign's Player / ActiveWorldMapMissionList on the mission replies, the party
// fallback (docs/server-rules.md "Campaign progression"). Without them soa-server's mission
// select had no missions (GetMissionList is answered by the campaign alone).
void campaign_reply(const Request& r, std::vector<u8>& body) {
    std::vector<char> b(body.begin(), body.end());
    if (campaign::on_response(r.fid, r.method, b)) body.assign(b.begin(), b.end());
}

// EndMissionTalk(type, mission id, flag, u32): the end of a story mission's scene (agent
// e6-end2end). (b) 3.7.0's EventScenario::CEventScenario::Exit sends it (CErrorHandlerWrap::Auto,
// fid 1d00a78c) and CApiNotify::OnEndMissionTalkRes applies the answer (a plain apply). No API
// answers it: the scene's effect (end_mission_talk), then the GetPlayMission answer with the
// campaign's data. False when GetPlayMission isn't answered (EndMissionTalk then goes the
// ordinary way). Rules and labels: the campaign's and the events' (docs/server-rules.md).
bool answer_end_mission_talk(const Request& r, Reply& reply) {
    u32 mission = r.ints.size() > 1 ? (u32)r.ints[1] : 0;
    if (mission) end_mission_talk(mission);
    Request gp{"GetPlayMission", kFidGetPlayMission, {}, {}, {}};
    submit(gp);
    reply.body.clear();
    if (!handle(gp.fid, reply.body)) return false;
    campaign_reply(gp, reply.body);
    reply.handled = true;
    return true;
}

}  // namespace

void end_mission_talk(u32 mission) {
    if (!events::end_mission_talk(mission)) campaign::end_mission_talk(mission);
}

Reply answer(const Request& r, const Fallback& fallback) {
    Reply reply;
    if (r.method == "EndMissionTalk" && answer_end_mission_talk(r, reply)) return reply;
    reply = Reply();
    submit(r);
    campaign::on_request(r);
    if (!handle(r.fid, reply.body)) {
        // no handler: the host's answer, with the campaign's data (as soa adds it to the file it
        // falls back to)
        reply.body = fallback ? fallback() : std::vector<u8>();
        campaign_reply(r, reply.body);
        return reply;
    }
    reply.handled = true;
    reply.error_code = error_code(r.fid);
    if (!reply.error_code) campaign_reply(r, reply.body);
    return reply;
}

}  // namespace soa::server
