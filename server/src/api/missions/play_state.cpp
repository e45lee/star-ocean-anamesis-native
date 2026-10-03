// The play state: GetPlayMission, MissionFailed, MissionTalk, MissionRestart, GetMissionList
// (api/missions/missions.h). Port code, not guest behaviour.
// Every rule carries its source label, (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption (docs/server-rules.md "Server missions").
#include "api/missions/missions.h"

#include "api/entry/entry.h"          // time_only
#include "api/player/player_info.h"  // base_data
#include "core/log.h"
#include "core/request_args.h"

namespace soa::server {

using ext::body;
using ext::Row;

namespace {

// The play state's answer: the player state with PlayMission (CPlayMissionInfo): the mission in
// progress, is_play while a MissionStart hasn't ended.
std::vector<u8> play_mission_answer(ext::Ctx& ctx, const Request& req) {
    Value play_mission = Value::object();
    u32 mission = 0;
    ctx.st.q("select mission_id from play where id = 1", {}, [&](const Row& play_row) { mission = (u32)play_row.i("mission_id"); });
    play_mission["mission_id"] = mission;
    play_mission["is_play"] = mission ? 1u : 0u;
    play_mission["is_expired"] = false;
    play_mission["is_maintenance"] = false;
    Value data = base_data(ctx);
    data["PlayMission"] = play_mission;
    LOGI("server", "%s: mission in progress %u", req.method.c_str(), mission);
    return body(data);
}

}  // namespace

std::vector<PlayMember> play_members(ext::Ctx& ctx) {
    std::vector<PlayMember> members;
    ctx.st.q("select uid, npc_uid from play_member where play_id = 1 order by slot", {},
             [&](const Row& member_row) { members.push_back({member_row.opt<CharacterUid>("uid"), member_row.opt<NpcPartyUid>("npc_uid")}); });
    return members;
}

std::vector<u64> battle_uids(const std::vector<PlayMember>& members) {
    std::vector<u64> uids;
    for (const PlayMember& member : members) {
        if (member.uid) uids.push_back(member.uid->v);
        else if (member.npc_uid) uids.push_back(member.npc_uid->v);
    }
    return uids;
}

// MissionRestart() / MultiMissionRestart() -> MissionRestartRes (as MissionStartRes)     fid 1f96f310
// API: docs/api.md#missionrestart   Rules: docs/server-rules.md "2.6 Failure, continue, restart", "Server missions"
//
// Resumes the mission in progress after an interruption (CStageManager::Progress, after
// GetPlayMission.is_play).
//   (d) the play record's mission and party start again (start_mission with `restarting`): no
//       stamina, ticket or play count is taken again, and the stored surprise roll is replayed;
//   (d) the helper isn't restored: the restart sends the play's party as the third argument (the
//       helper index + 1) and no helper ids, and type 0 (find_mission tries the other tables);
//   nothing in progress: not handled.
// Answers: as MissionStart.
std::vector<u8> mission_restart(ext::Ctx& ctx, const Request&) {
    u32 mission = 0, party = 1;
    ctx.st.q("select mission_id, party_id from play where id = 1", {}, [&](const Row& play_row) {
        mission = (u32)play_row.i("mission_id");
        party = (u32)play_row.i("party_id");
    });
    if (!mission) return {};
    Request again{"MissionStart", 0xb7c62bc2, {0, mission, party, 0, 0, 0, 0}, {}, {}};
    return start_mission(ctx, again, nullptr, true);
}

// GetPlayMission() -> GetPlayMissionRes                                            fid 7c1b7a1b
// API: docs/api.md#getplaymission   Rules: docs/server-rules.md "Play state"
//
// Whether a mission was interrupted (CPhase_BattleResumeCheck: resume or give up).
//   (b) PlayMission.is_play is 1 while a MissionStart hasn't been ended (MissionEnd / Failed).
// Answers: the player state with PlayMission.
std::vector<u8> get_play_mission(ext::Ctx& ctx, const Request& req) { return play_mission_answer(ctx, req); }

// MissionFailed(u32 mission_type, u32 mission_id) + the battle log -> MissionFailedRes  fid 479604f6
// API: docs/api.md#missionfailed   Rules: docs/server-rules.md "2.6 Failure, continue, restart", "Play state"
//
// A lost or retired battle, or an interrupted one given up.
//   (c) no rewards, and the stamina stays spent (docs/api.md); the play record ends, all of it
//       (its members, type, surprise roll and helper: one row since PLAN-schema S7, so a later
//       MissionEnd without a play reads none of them, d).
// Answers: the player state with PlayMission (nothing in progress).
std::vector<u8> mission_failed(ext::Ctx& ctx, const Request& req) {
    ctx.st.q("delete from play", {});  // and its members (ON DELETE CASCADE)
    return play_mission_answer(ctx, req);
}

// MissionTalk(u32 mission_type, u32 mission_id, u32 talk_id, u8 flag) -> MissionTalkRes  fid 816dc8b4
// API: docs/api.md#missiontalk   Rules: docs/server-rules.md "Play state"
//
// A story (talk-only) mission: no battle.
//   (d) it counts as cleared and played (first_clear_at on the first time); a request without a
//       mission only answers.
// Answers: the player state with PlayMission.
std::vector<u8> mission_talk(ext::Ctx& ctx, const Request& req) {
    if (const auto talk = args::MissionTalkArgs::from(req); talk.has_mission) {
        ctx.st.q("insert into mission (mission_id) values (?) on conflict(mission_id) do nothing", {talk.mission});
        ctx.st.q(
            "update mission set cleared = 1, play_count = play_count + 1, clear_count = clear_count + 1, "
            "first_clear_at = ifnull(first_clear_at, ?) where mission_id = ?",
            {clock_now(), talk.mission});
    }
    return play_mission_answer(ctx, req);
}

// The play state's answer for a module (ext::Ctx::core_mission): MissionFailed, MissionTalk, else
// GetPlayMission's.
std::vector<u8> play_state(ext::Ctx& ctx, const Request& req) {
    if (req.method == "MissionFailed") return mission_failed(ctx, req);
    if (req.method == "MissionTalk") return mission_talk(ctx, req);
    return get_play_mission(ctx, req);
}

namespace {
// GetMissionList(int) -> GetMissionListRes                                         fid 57308f4d
// API: docs/api.md#getmissionlist   Rules: docs/server-rules.md "2.1 Opening missions"
//
// The mission select's lists.
//   (d) the core answers data.Time only; the story campaign adds ActiveMissionList
//       (campaign::on_response) and the events ActiveEventMissionList / CampaignInfo (OnResponse
//       of api/events/event_missions.cpp). With a handler, both hosts answer the same body and
//       both get those additions.
// Answers: data.Time.
std::vector<u8> get_mission_list(ext::Ctx& ctx, const Request&) { return time_only(ctx); }
}  // namespace

// The play state's APIs (src/core/modules.cpp: the core's APIs first).
void register_play_state() {
    ext::add_core_api({"GetPlayMission"}, get_play_mission);
    ext::add_core_api({"MissionFailed"}, mission_failed);
    ext::add_core_api({"MissionTalk"}, mission_talk);
    ext::add_core_api({"MissionRestart", "MultiMissionRestart"}, mission_restart);
    ext::add_core_api({"GetMissionList"}, get_mission_list);
}

}  // namespace soa::server
