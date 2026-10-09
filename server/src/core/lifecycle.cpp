// The request lifecycle (soaserver/server.h answer): one for both hosts. Port code, not guest
// behaviour. soa's FakeApiCaller route (port/src/native/api/fakeapi.cpp) and soa-server's wire
// (net/game.cpp) deliver every request through answer(); before step R9 of
// docs/history/PLAN-readability.md each host wired the story campaign and EndMissionTalk itself.
#include <vector>

#include "core/log.h"
#include "soaserver/api_campaign.h"
#include "soaserver/events.h"
#include "soaserver/fids.h"
#include "soaserver/server.h"

namespace soa::server {

namespace {

// The story campaign's additions to an answer (soa-server's wire route): ActiveMissionList on every
// reply, the campaign's Player / ActiveWorldMapMissionList on the mission replies, the party
// fallback (docs/server-rules.md#campaign). Without them soa-server's mission
// select had no missions (GetMissionList is answered by the campaign alone).
void campaign_reply(const Request& r, std::vector<u8>& body) {
    std::vector<char> b(body.begin(), body.end());
    if (campaign::on_response(r.fid, r.method, b)) body.assign(b.begin(), b.end());
}

// EndMissionTalk(type, mission id, flag, u32): the end of a story mission's scene. (b) 3.7.0's EventScenario::CEventScenario::Exit sends it (CErrorHandlerWrap::Auto,
// fid 1d00a78c) and CApiNotify::OnEndMissionTalkRes applies the answer (a plain apply, the same
// body as OnGetPlayMissionRes: @014c0d68, @014cd380). No API answers it: the scene's effect
// (end_mission_talk), then the GetPlayMission answer with the campaign's data. Both hosts send it
// here like any other request (soa's FakeApiCaller route queues it since CR2). False when
// GetPlayMission isn't answered (EndMissionTalk then goes the ordinary way). Rules and labels: the
// campaign's and the events' (docs/server-rules.md).
bool answer_end_mission_talk(const Request& r, Reply& reply) {
    u32 mission = r.ints.size() > 1 ? (u32)r.ints[1] : 0;
    if (mission) end_mission_talk(mission);
    Request gp{"GetPlayMission", fids::kGetPlayMission, {}, {}, {}};
    submit(gp);
    reply.body.clear();
    if (!handle(gp.fid, reply.body)) return false;
    reply.handled = true;
    reply.error_code = error_code(gp.fid);
    if (!reply.error_code) campaign_reply(gp, reply.body);
    return true;
}

}  // namespace

void end_mission_talk(u32 mission) {
    if (!events::end_mission_talk(mission)) campaign::end_mission_talk(mission);
}

Reply answer(const Request& r, const Fallback& fallback) {
    Reply reply;
    submit(r);  // the pending request, and its log line (scripts read "request <Method>")
    if (r.method == "EndMissionTalk" && answer_end_mission_talk(r, reply)) return reply;
    reply = Reply();
    campaign::on_request(r);
    if (!handle(r.fid, reply.body)) {
        // no handler: the host's answer ({} in soa, {data: {Time}} in soa-server), with the
        // campaign's data. Logged in both hosts (docs/unimplemented-apis.md "Stub logging");
        // GetWorldMapInfoList is the campaign's (its data is the answer), not a missing handler.
        if (!r.method.empty() && r.method != "GetWorldMapInfoList")
            LOGW("server",
                 "no handler: %s (fid %08x); answered with the host's fallback, nothing stored "
                 "(docs/unimplemented-apis.md)",
                 r.method.c_str(), r.fid);
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
