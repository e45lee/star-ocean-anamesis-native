// The play state: GetPlayMission, MissionFailed, MissionTalk, MissionRestart, GetMissionList
// (api/missions/missions.h). Port code, not guest behaviour.
// Every rule carries its source label, (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption (docs/server-rules.md#server-missions).
#include "api/missions/missions.h"

#include "api/entry/entry.h"          // time_only
#include "api/player/player_info.h"  // base_data
#include "core/errors.h"
#include "core/log.h"
#include "core/request_args.h"
#include "core/server.h"  // event_clock_of
#include "core/wallet.h"
#include "rules/mission_rules.h"

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
// API: docs/api.md#missionrestart   Rules: docs/server-rules.md#failure-continue-restart, docs/server-rules.md#server-missions
//
// Resumes the mission in progress after an interruption (CStageManager::Progress, after
// GetPlayMission.is_play).
//   (b) the request has no arguments, and the client builds the resumed battle's four slots from
//       the answer's BattleParameter.PlayerCharacter as for a MissionStart (CStageManager::Progress,
//       Ghidra 0x13c7820, sends 0x1f96f310 / 0x8c788f39 instead of MissionStart when
//       CParameterUI::GetMissionRestart; CPartyManager::InitializePlayer(ulong*, bool*, int),
//       0x13a1f6c, CreateCharacterInfoByAPI(0..3)): what the restart fights with is the server's;
//   (d) the play record's mission, type, party set and helper start again (start_mission with
//       `restarting`): the recorded helper as MissionStart's arguments (helper index 1; an own
//       character's uid, a rental id or the NPC helper argument by play.helper_kind); no stamina,
//       ticket, play count or rental-day count is taken again, and the stored surprise roll is
//       replayed. (Until 2026-10-03 the restart sent the play's party id as the helper index and no
//       helper ids, so a restarted battle lost its helper: R15's finding.) What the online server
//       did isn't known;
//   nothing in progress: not handled.
// Answers: as MissionStart.
std::vector<u8> mission_restart(ext::Ctx& ctx, const Request&) {
    u32 mission = 0, type = 0, npc_id = 0;
    HelperKind kind = HelperKind::kNone;
    u64 helper_uid = 0;
    ctx.st.q("select mission_id, mission_type, helper_kind, helper_uid, npc_id from play where id = 1", {}, [&](const Row& play_row) {
        mission = (u32)play_row.i("mission_id");
        type = (u32)play_row.i("mission_type");
        kind = HelperKind((u32)play_row.i("helper_kind"));
        helper_uid = (u64)play_row.i("helper_uid");  // NULL: none (0)
        npc_id = (u32)play_row.i("npc_id");
    });
    if (!mission) return {};
    // MissionStart(type, mission, helper index + 1, own helper uid, NPC helper id, rental id, u32)
    const u64 helper_index_plus_1 = kind == HelperKind::kNone ? 0 : 1;
    const u64 own_helper_uid = kind == HelperKind::kOwn ? helper_uid : 0;
    const u64 rental_uid = kind == HelperKind::kRental ? helper_uid : 0;
    Request again{"MissionStart", 0xb7c62bc2, {type, mission, helper_index_plus_1, own_helper_uid, npc_id, rental_uid, 0}, {}, {}};
    return start_mission(ctx, again, nullptr, true);
}

// GetPlayMission() -> GetPlayMissionRes                                            fid 7c1b7a1b
// API: docs/api.md#getplaymission   Rules: docs/server-rules.md#play-state
//
// Whether a mission was interrupted (CPhase_BattleResumeCheck: resume or give up).
//   (b) PlayMission.is_play is 1 while a MissionStart hasn't been ended (MissionEnd / Failed).
// Answers: the player state with PlayMission.
std::vector<u8> get_play_mission(ext::Ctx& ctx, const Request& req) { return play_mission_answer(ctx, req); }

// MissionFailed(u32 mission_type, u32 mission_id) + the battle log -> MissionFailedRes  fid 479604f6
// API: docs/api.md#missionfailed   Rules: docs/server-rules.md#failure-continue-restart, docs/server-rules.md#play-state
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

// MissionLose() -> MissionLoseRes                                                 fid 863bb1ec
// API: docs/api.md#missionlose   Rules: docs/server-rules.md#failure-continue-restart
//
// A lost battle given up (the name's meaning; the 3.7.0 client never sends it).
//   (b) no caller: the FunctionID 0x863bb1ec appears only in the API tables and the callers
//       (NetworkApiCaller::MissionLose, the wire serializer); a lost battle sends MissionFailed
//       (CStageManager::Progress), a training battle nothing;
//   (d) it ends the play as MissionFailed does (no rewards, the stamina stays spent).
// Answers: the player state with PlayMission (nothing in progress).
std::vector<u8> mission_lose(ext::Ctx& ctx, const Request& req) { return mission_failed(ctx, req); }

namespace {

// The continue's price for a mission (b: CPauseMenu::OpenContinue @01dacf90): (a)
// master_global continue_use_coin (CParameterUtility::ContinueUseCoin), times the magnification of
// a running continue campaign (type_id 9): CUIUtility::GetDecMissionContinueCoin (@01ef91c4) is
// asked for every type (model 99) first, then for the mission's type and area
// (mission_rules::continue_campaign_applies); the first match in the rows' order counts (b: the
// client walks its campaign list and returns the first; d: the order is the master's, by id).
// (d) the windows on the event calendar, as the stamina campaigns (campaigns.cpp: the client gets
// them moved by the same years in CampaignInfo).
u32 continue_price(ext::Ctx& ctx, const MissionRef& ref) {
    const u32 base = ctx.global_u32("continue_use_coin", 100);
    const EventTime now = event_clock_of(ctx.m.h);
    for (bool every_type_pass : {true, false}) {
        std::optional<double> magnification;
        ctx.m.q("select * from master_campaign where type_id = 9 order by id", {}, [&](const Row& campaign_row) {
            if (magnification) return;
            if (!mission_rules::campaign_active(campaign_row.s("opened_day"), campaign_row.s("opened_time"), campaign_row.s("closed_day"),
                                                campaign_row.s("closed_time"), (int)campaign_row.i("week_id"), now.v))
                return;
            if (mission_rules::continue_campaign_applies((int)campaign_row.i("master_mission_model_type"), (u32)campaign_row.i("master_area_id"),
                                                         every_type_pass, ref.type, ref.area))
                magnification = campaign_row.f("magnification");
        });
        if (magnification) return mission_rules::continue_price(base, *magnification);
    }
    return base;
}

}  // namespace

// MissionContinue(bool) -> MissionContinueRes                                     fid 755cba3d
// API: docs/api.md#missioncontinue   Rules: docs/server-rules.md#failure-continue-restart
//
// The defeat dialog's answer (CPauseMenu::OpenContinue / ReqeustContinue @01dad704): the party
// revives for coins, or the player gives up.
//   (b) 1 is the dialog's はい ("紋章石%u個を使用することで全員が復活できます", uimsg_battle_continue);
//       0 its いいえ, and OpenContinue sends 0 by itself when the coins don't cover the price or
//       the mission's is_continue is 0 (it never offers the dialog then).
//   (a)+(b) the price: continue_use_coin x a running continue campaign's magnification
//       (continue_price above); (a) free coins first (core/wallet.h), as Sphere 211's continue.
//   (a) only a mission with is_continue 1 (its table's column) continues; (d) else, with nothing
//       in progress or with the coins short, refused (kInvalidOperation 10403 / kCoinsShort 20000).
//   (d) the play stays open across a continue (same mission, party, stamina and surprise roll):
//       the battle goes on and ends with MissionEnd or MissionFailed as before; a 0 changes
//       nothing (the battle's own end follows).
// Answers: the player state (Wallet) and is_mission_continue (whether the party revives).
std::vector<u8> mission_continue(ext::Ctx& ctx, const Request& req) {
    const bool continue_battle = args::MissionContinueArgs::from(req).continue_battle;
    u32 mission = 0, type = 0;
    ctx.st.q("select mission_id, mission_type from play where id = 1", {}, [&](const Row& play_row) {
        mission = (u32)play_row.i("mission_id");
        type = (u32)play_row.i("mission_type");
    });
    Value data = base_data(ctx);
    data["is_mission_continue"] = false;
    if (!continue_battle) {
        // read by port/scripts/simulator_continue_session.sh
        LOGI("server", "MissionContinue: declined (mission %u)", mission);
        return body(data);
    }
    if (!mission) return ext::refuse(ctx, "MissionContinue", "no mission in progress", ErrorCode::kInvalidOperation);
    const MissionRef ref = find_mission(ctx, type, mission);
    if (!ref.found || ctx.m.one("select is_continue from " + ref.table + " where id = ?", {mission}) == 0)
        return ext::refuse(ctx, "MissionContinue", "the mission has no continue (is_continue 0)", ErrorCode::kInvalidOperation);
    const u32 price = continue_price(ctx, ref);
    if (!wallet::spend_coins(ctx.st.h, price)) return ext::refuse(ctx, "MissionContinue", "coins short", ErrorCode::kCoinsShort);
    data = base_data(ctx);  // the wallet after the payment
    data["is_mission_continue"] = true;
    // read by port/scripts/simulator_continue_session.sh
    LOGI("server", "MissionContinue: mission %u continued for %u coins", mission, price);
    return body(data);
}

// MissionTalk(u32 mission_type, u32 mission_id, u32 talk_id, u8 flag) -> MissionTalkRes  fid 816dc8b4
// API: docs/api.md#missiontalk   Rules: docs/server-rules.md#play-state
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
            {ctx.now(), talk.mission});
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
// API: docs/api.md#getmissionlist   Rules: docs/server-rules.md#opening-missions
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
    ext::add_core_api({"MissionLose"}, mission_lose);
    ext::add_core_api({"MissionContinue"}, mission_continue);
    ext::add_core_api({"MissionTalk"}, mission_talk);
    ext::add_core_api({"MissionRestart", "MultiMissionRestart"}, mission_restart);
    ext::add_core_api({"GetMissionList"}, get_mission_list);
}

}  // namespace soa::server
