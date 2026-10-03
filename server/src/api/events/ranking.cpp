// Event rankings (イベントランキング): the five ranking APIs over master_event_ranking_group /
// master_event_ranking / master_event_ranking_reward, with a local ranking in which the player is
// the only entrant. Port code, not guest behaviour. Rules in docs/server-rules.md "Event rankings";
// labels: (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// Shape (b, CEventRanking / CEventMissionMenu / CEventRankingResult):
//  - a ranking group (master_event_ranking_group) runs opened_at..closed_at; its rankings
//    (master_event_ranking, display_type 0 main / 1 sub) rank the plays of one event mission
//    (master_event_mission_id) by the battle's evaluation value of ranking_type (1 total damage,
//    2 enemies defeated, 3 rush-combo damage, 4 highest hit count, 5 highest single damage,
//    6 clear time in ms; CBattleEvaluationInfo, the same numbering);
//  - closed_at..ranking_closed_at is 集計中; from ranking_closed_at until result_closed_at the
//    result can be received: CheckEventRankingResult on the event menu names the group, then
//    ReceiveEventRankingResult pays each ranking's reward tier (the master_event_ranking_reward row
//    of ranking_reward_group_id = the ranking's id with the smallest required_ranking >= rank).
// The group dates are moved by the calendar's whole years (events::client_years), as the event
// module moves them in the client's copy, and compared with the clock.
#include <algorithm>
#include <string>
#include <vector>

#include "api/events/event_extras.h"  // kMissionTypeEvent
#include "core/log.h"
#include "core/rewards.h"  // grant_with_item_sets
#include "soaserver/events.h"
#include "soaserver/ext.h"
#include "api/social/rental.h"
#include "core/modules.h"

namespace soa::server {

namespace args {
// GetEventRankingInfo(u32 group_id) (b: the argument is a ranking group id). The module's own
// args structs (core/request_args.h holds the core handlers').
struct GetEventRankingInfoArgs {
    u32 group_id = 0;
    static GetEventRankingInfoArgs from(const Request& req) { return {req.ints.empty() ? 0 : (u32)req.ints[0]}; }
};
// ClearNewEventRanking(vector<u32> ranking_ids).
struct ClearNewEventRankingArgs {
    std::vector<u64> ranking_ids;
    static ClearNewEventRankingArgs from(const Request& req) { return {req.vecs.empty() ? std::vector<u64>{} : req.vecs[0]}; }
};
// GetPlayerDetailInfo(u32 player_id).
struct GetPlayerDetailInfoArgs {
    u32 player_id = 0;
    static GetPlayerDetailInfoArgs from(const Request& req) { return {req.ints.empty() ? 0u : (u32)req.ints[0]}; }
};
}  // namespace args

namespace {
using namespace ext;

// (b) ranking_type 6: the clear time in ms (lower is better; 0 is no time).
constexpr u32 kRankingTypeClearTime = 6;
// (d) the player is the only entrant: rank 1 everywhere.
constexpr u32 kOnlyRank = 1;
// (b) EventRankingInfo's party slots party_*1..4.
constexpr int kPartySlots = 4;

// (d) our layout: the best score per ranking, the party that made it, and the groups whose result
// was received; `fresh` = updated since the ranking screen last cleared it (UpdatedEventRankingIdList).
const char* const kSchemaRank = R"(
create table if not exists event_rank_score (ranking_id integer primary key, group_id integer, score integer, roles text,
  created_at integer, fresh integer default 1);
create table if not exists event_rank_received (group_id integer primary key, received_at integer);
)";

struct Group {
    u32 id = 0;
    int64_t opened = 0, closed = 0, ranking_closed = 0, result_closed = 0;
};
// A group's dates as the client sees them (moved by the calendar's whole years).
Group group_dates(Ctx& ctx, const Row& group_row) {
    Group group;
    int years = events::client_years(ctx);
    group.id = (u32)group_row.i("id");
    group.opened = ctx.parse_time(events::shift_years(group_row.s("opened_at"), years));
    group.closed = ctx.parse_time(events::shift_years(group_row.s("closed_at"), years));
    group.ranking_closed = ctx.parse_time(events::shift_years(group_row.s("ranking_closed_at"), years));
    group.result_closed = ctx.parse_time(events::shift_years(group_row.s("result_closed_at"), years));
    return group;
}

// (b) ranking_type 6 (clear time) ranks lower first and 0 is no time; the others rank higher first.
bool better(u32 type, int64_t score, int64_t best) {
    if (type == kRankingTypeClearTime) return score > 0 && (best <= 0 || score < best);
    return score > best;
}

// The party of a win, as stored (the first four roles, "a,b,c,").
std::string party_roles(const MissionInfo& mission) {
    std::string roles;
    for (size_t k = 0; k < mission.roles.size() && k < (size_t)kPartySlots; k++) roles += std::to_string(mission.roles[k]) + ",";
    return roles;
}

// MissionResultExtra hook (a won MissionEnd).
// Rules: docs/server-rules.md "Event rankings"
//   (a) every ranking of the won event mission whose group is open (master_event_ranking.
//       master_event_mission_id, the group's opened_at..closed_at moved by the year shift) keeps
//       the best evaluation value (b: the battle's CBattleEvaluationInfo of the ranking's type);
//       (d) the party is the battle's (its roles, shown as the ranked party).
//   (b) a non-empty UpdatedEventRankingIdList lights the ranking button's badge
//       (MissionUtility::IsUpdateEventRanking); (d) sent when a score improved.
// Adds: UpdatedEventRankingIdList (the rankings improved), when any.
void ranking_mission_result(Ctx& ctx, const MissionInfo& mission, Value& data) {
    if (mission.type != event_extras::kMissionTypeEvent || !mission.evaluation) return;
    int64_t now = ctx.now();  // the clock, against the moved dates
    std::vector<u32> updated;
    ctx.m.q(
        "select r.id as rid, r.ranking_type, g.* from master_event_ranking r join master_event_ranking_group g on g.id = r.ranking_group_id "
        "where r.master_event_mission_id = ?",
        {mission.mission}, [&](const Row& ranking_row) {
            Group group = group_dates(ctx, ranking_row);
            if (!(group.opened <= now && now <= group.closed)) return;
            u32 ranking = (u32)ranking_row.i("rid"), type = (u32)ranking_row.i("ranking_type");
            int64_t score = mission.evaluation((int)type);
            if (score < 0 || (type == kRankingTypeClearTime && score == 0)) return;
            int64_t best = ctx.st.one("select score from event_rank_score where ranking_id = ?", {ranking}, -1);
            if (best >= 0 && !better(type, score, best)) return;
            ctx.st.q("insert or replace into event_rank_score values (?,?,?,?,?,1)", {ranking, group.id, score, party_roles(mission), ctx.now()});
            updated.push_back(ranking);
            LOGI("server", "event ranking %u (type %u): best score %lld", ranking, type, (long long)score);
        });
    if (!updated.empty()) {
        Value list = Value::array();
        for (u32 ranking : updated) list.push(ranking);
        data["UpdatedEventRankingIdList"] = list;
    }
}

// One EventRankingInfo row (b: EventRankingInfo::Initialize): the player's best, rank 1.
Value event_ranking_info(Ctx& ctx, const Row& score_row) {
    u32 player = ctx.player_id();
    Value info = Value::object();
    info["player_id"] = player;
    info["rank"] = kOnlyRank;
    info["rank_ui"] = kOnlyRank;
    info["score"] = (u64)score_row.i("score");
    std::vector<u32> roles;
    std::string stored = score_row.s("roles");
    for (size_t begin = 0; begin < stored.size();) {
        size_t end = stored.find(',', begin);
        if (end == std::string::npos) end = stored.size();
        if (end > begin) roles.push_back((u32)std::stoul(stored.substr(begin, end - begin)));
        begin = end + 1;
    }
    // (b) a slot is the player's own when party_player_idN is the player and _validN is set (the own
    // row); a 0 role hides the slot. (d) every slot of the party is the player's.
    for (int k = 0; k < kPartySlots; k++) {
        std::string slot = std::to_string(k + 1);
        bool filled = k < (int)roles.size();
        info["party_player_id" + slot] = filled ? player : 0u;
        info["party_player_id" + slot + "_valid"] = filled;
        info["party_role_id" + slot] = filled ? roles[k] : 0u;
    }
    info["battle_id"] = 0u;
    info["created_at"] = ctx.fmt_time(score_row.i("created_at"));
    return info;
}

// GetEventRankingInfo(u32 group_id) -> GetEventRankingInfoRes          fid 94456167
// API: docs/api.md#geteventrankinginfo   Rules: docs/server-rules.md "Event rankings"
//
// The ranking screen of a group (CEventRanking: the group running by the client clock, and the
// previous one from the 報酬 tab).
//   (b) GetEventRankingResultInfo {EventRankingInfoListMap / EventRankingTopInfoListMap: {ranking
//       id: [EventRankingInfo]}, EventRankingPlayerInfoMap {player id: {name}}}.
//   (d) the player is the only entrant: one row per ranking played, rank 1; the top list repeats it.
// Answers: the player state with GetEventRankingResultInfo.
std::vector<u8> get_event_ranking_info(Ctx& ctx, const Request& req) {
    const auto args = args::GetEventRankingInfoArgs::from(req);
    Value lists = Value::object();
    ctx.m.q("select id from master_event_ranking where ranking_group_id = ? order by display_type", {args.group_id}, [&](const Row& ranking_row) {
        Value list = Value::array();
        ctx.st.q("select * from event_rank_score where ranking_id = ?", {ranking_row.i("id")},
                 [&](const Row& score_row) { list.push(event_ranking_info(ctx, score_row)); });
        lists[std::to_string(ranking_row.i("id"))] = list;
    });
    Value info = Value::object();
    info["EventRankingInfoListMap"] = lists;
    info["EventRankingTopInfoListMap"] = lists;  // (d) the top list is the same single entrant
    Value players = Value::object();
    Value player = Value::object();
    std::string name;
    ctx.st.q("select name from player", {}, [&](const Row& player_row) { name = player_row.s("name"); });
    player["name"] = name;
    players[std::to_string(ctx.player_id())] = player;
    info["EventRankingPlayerInfoMap"] = players;
    Value data = ctx.base_data();
    data["GetEventRankingResultInfo"] = info;
    LOGI("server", "GetEventRankingInfo %u: %zu rankings", args.group_id, lists.map.size());
    return body(data);
}

// ClearNewEventRanking(vector<u32> ranking_ids) -> ClearNewEventRankingRes   fid cb1a5781
// API: docs/api.md#clearneweventranking   Rules: docs/server-rules.md "Event rankings"
//
// The ranking screen closes (b): its rankings are no longer new.
//   (b)+(d) the badge list is answered empty.
// Answers: the player state with UpdatedEventRankingIdList [].
std::vector<u8> clear_new_event_ranking(Ctx& ctx, const Request& req) {
    const auto args = args::ClearNewEventRankingArgs::from(req);
    for (u64 ranking : args.ranking_ids) ctx.st.q("update event_rank_score set fresh = 0 where ranking_id = ?", {ranking});
    Value data = ctx.base_data();
    data["UpdatedEventRankingIdList"] = Value::array();
    return body(data);
}

// The group whose result is due: (a) ranking_closed_at <= calendar <= result_closed_at, not received
// yet, with a score in one of its rankings (d: no play, no result); the latest such group.
u32 due_group(Ctx& ctx) {
    int64_t now = ctx.now();  // the clock, against the moved dates
    u32 due = 0;
    int64_t due_ranking_closed = 0;
    ctx.m.q("select * from master_event_ranking_group", {}, [&](const Row& group_row) {
        Group group = group_dates(ctx, group_row);
        if (!(group.ranking_closed <= now && now <= group.result_closed)) return;
        if (ctx.st.one("select count(*) from event_rank_received where group_id = ?", {group.id})) return;
        if (!ctx.st.one("select count(*) from event_rank_score where group_id = ?", {group.id})) return;
        if (!due || group.ranking_closed > due_ranking_closed) due = group.id, due_ranking_closed = group.ranking_closed;
    });
    return due;
}
// CheckEventRankingResultInfo (b: {master_event_ranking_group_id, RankingResultInfoList
// [{master_event_ranking_id, score, rank}]}); group 0 when nothing is due (b: the stored info
// persists, so the key is always sent).
Value result_info(Ctx& ctx, u32 group) {
    Value info = Value::object();
    info["master_event_ranking_group_id"] = group;
    Value results = Value::array();
    if (group)
        ctx.st.q("select * from event_rank_score where group_id = ? order by ranking_id", {group}, [&](const Row& score_row) {
            Value result = Value::object();
            result["master_event_ranking_id"] = (u32)score_row.i("ranking_id");
            result["score"] = (u64)score_row.i("score");
            result["rank"] = kOnlyRank;  // (d) the only entrant
            results.push(result);
        });
    info["RankingResultInfoList"] = results;
    return info;
}

// CheckEventRankingResult() -> CheckEventRankingResultRes                fid 83809bfb
// API: docs/api.md#checkeventrankingresult   Rules: docs/server-rules.md "Event rankings"
//
// The event menu asks whether a result is due (CEventMissionMenu::Initialize).
//   (a)+(d) the latest group between ranking_closed_at and result_closed_at, played and not
//       received (due_group); else group 0.
// Answers: the player state with CheckEventRankingResultInfo.
std::vector<u8> check_event_ranking_result(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["CheckEventRankingResultInfo"] = result_info(ctx, due_group(ctx));
    return body(data);
}

// (a) the reward tier of `rank`: the master_event_ranking_reward row of the ranking with the
// smallest required_ranking >= rank (b: CEventRankingResult::Initialize's tier ranges).
struct Reward {
    u32 type = 0, id = 0, num = 0;
};
Reward reward_for(Ctx& ctx, u32 ranking, u32 rank) {
    Reward reward;
    ctx.m.q(
        "select content_type, content_id, num from master_event_ranking_reward where ranking_reward_group_id = ? and required_ranking >= ? "
        "order by required_ranking limit 1",
        {ranking, rank}, [&](const Row& reward_row) {
            reward.type = (u32)reward_row.i("content_type");
            reward.id = (u32)reward_row.i("content_id");
            reward.num = (u32)std::max<int64_t>(1, reward_row.i("num"));
        });
    return reward;
}

// ReceiveEventRankingResult() -> ReceiveEventRankingResultRes            fid 4700c6f7
// API: docs/api.md#receiveeventrankingresult   Rules: docs/server-rules.md "Event rankings"
//
// Pays the due group's rewards (the event menu, when CheckEventRankingResult named a group).
//   (a) each ranking played pays its rank-1 tier (reward_for), item sets expanded; (d) the group
//       is then received (once).
//   (b) the handler applies AddItem / UpdateStackItem, the dialog shows the tiers.
// Answers: the player state with CheckEventRankingResultInfo, StockItem, and AddItem /
// AddCharacter when granted.
std::vector<u8> receive_event_ranking_result(Ctx& ctx, const Request&) {
    u32 group = due_group(ctx);
    Value info = result_info(ctx, group);
    Value items = Value::array(), stocks = Value::array(), characters = Value::array();
    if (group) {
        for (const Value& result : info.find("RankingResultInfoList")->arr) {
            u32 ranking = (u32)result.get_u("master_event_ranking_id");
            Reward reward = reward_for(ctx, ranking, kOnlyRank);
            if (reward.type) grant_with_item_sets(ctx, reward.type, reward.id, reward.num, items, stocks, characters);
            LOGI("server", "ReceiveEventRankingResult: ranking %u rank 1 -> content %u/%u x%u", ranking, reward.type, reward.id, reward.num);
        }
        ctx.st.q("insert or replace into event_rank_received values (?, ?)", {group, ctx.now()});
    }
    Value data = ctx.base_data();
    data["CheckEventRankingResultInfo"] = info;
    if (!items.arr.empty()) data["AddItem"] = items;
    if (!characters.arr.empty()) {
        Value add_character = Value::object();
        for (auto& character : characters.arr) add_character[std::to_string(character.get_u("id"))] = character;
        data["AddCharacter"] = add_character;
    }
    data["StockItem"] = ctx.stock();
    return body(data);
}

// GetPlayerDetailInfo(u32 player_id) -> GetPlayerDetailInfoRes          fid 626e1e5f
// API: docs/api.md#getplayerdetailinfo   Rules: docs/server-rules.md "Event rankings"
//
// Another entrant's detail dialog (CEventRanking::OpenDetailDialog; the reply handler is a plain
// apply).
//   (b) the dialog reads the first SearchResult entry through CParameterUtility::
//       CreateSearchFriendData (CParameterManager+0x6490: CFollowPlayerInfo at +0x90,
//       CFollowPersonInfo at +0x308; tCharaData::InitializeFollow), so SearchResult is
//       {player id: CFollowInfo {order, player, pc}}, the shape of the rental entries.
//   (b) the ranking rows' touch handlers skip the player's own row and own party slots, so the
//       client doesn't send it for the one local entrant; (d) any player id is answered with the
//       player (the only entrant).
// Answers: the player state with SearchResult.
std::vector<u8> get_player_detail_info(Ctx& ctx, const Request& req) {
    const auto args = args::GetPlayerDetailInfoArgs::from(req);
    Value data = ctx.base_data();
    Value search_result = Value::object();
    search_result[std::to_string(ctx.player_id())] = rental::own_follow_entry(ctx);
    data["SearchResult"] = search_result;
    LOGI("server", "GetPlayerDetailInfo %u: the player", args.player_id);
    return body(data);
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_event_ranking() {
    using namespace ext;
    add_schema(kSchemaRank);
    add_mission_result_extra(ranking_mission_result);
    add_api({"GetEventRankingInfo"}, get_event_ranking_info);
    add_api({"ClearNewEventRanking"}, clear_new_event_ranking);
    add_api({"CheckEventRankingResult"}, check_event_ranking_result);
    add_api({"ReceiveEventRankingResult"}, receive_event_ranking_result);
    add_api({"GetPlayerDetailInfo"}, get_player_detail_info);
}

}  // namespace soa::server
