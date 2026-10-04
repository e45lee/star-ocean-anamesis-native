// The achievements (勲章 / 実績): AchievementActiveList, AchievementReceive,
// AchievementListReceive, AchievementReceiveList, and the `Achievement` key of the full-state
// player responses. Port code, not guest behaviour. Rules: docs/server-rules.md "10. Achievements",
// "Achievements" (under "Growth and economy") and "Favor achievements"; every rule carries its
// source label: (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// Progress isn't stored: it is computed from the server state each time (the counters table,
// the roster, the clears, the modules' tables). Received achievements are the `achievements`
// table; their rewards go to the present box.
#include "api/presents/presents.h"  // present_box_info
#include "api/sphere211/sphere211.h"
#include "core/log.h"
#include "core/modules.h"
#include "soaserver/ext.h"

namespace soa::server {

namespace {
using namespace ext;

// master_achievement.type, the event a row counts: the types the server tracks. (a) the type of
// each row; what it counts is (a)+text, from the rows' name and description texts
// (docs/server-rules.md "10. Achievements" lists every type).
enum class AchievementType : int {
    kCharacterGachaDraws = 1,     // character gacha draws, of gacha target_id or any
    kCharacterBoosts = 2,         // character boosts (強化)
    kEvolutions = 3,              // evolutions, to rarity target_id
    kCharacterLimitBreaks = 4,    // character limit breaks
    kWeaponBoosts = 5,            // 武器を N回強化する
    kWeaponLimitBreaks = 6,       // 武器を N回上限解放する: weapon limit-break raises
    kWeaponGradeUps = 7,          // 武器を N回錬成する
    kMissionClears = 8,           // clears of mission target_id
    kOwnCharacter = 11,           // own character target_id
    kCharacterLevel = 29,         // a character at level N
    kCharacterLimitBreak = 31,    // a character at limit break N
    kExchanges = 34,              // exchange-shop trades
    kPlayerRank = 36,             // player rank reached
    kTitleMissionClears = 37,     // clears of mission target_id (the event title series)
    kAccessoryBoosts = 38,        // アクセサリーを N回強化する
    kDeepSpaceExploration = 44,   // exploration rate of deep-space area target_id
    kDeepSpaceExpeditions = 45,   // deep-space expeditions
    kFavorPoints = 52,            // favor points with same_role_id target_id
    kSphere211Floor = 61,         // Sphere 211: floor reached (api/sphere211/)
    kSphere211Wins = 62,          // Sphere 211: battles won
};

// CAchievementInfo.status: (d) 0 in progress, 1 achieved.
constexpr u32 kStatusInProgress = 0, kStatusAchieved = 1;

// ---- progress ----------------------------------------------------------------------------

// Type 44: the exploration rate of deep-space area `area_id`, in percent (a: target_id_label
// ds_area01_At = master_deep_space_area id_label, goal_count 100, text "探査率１００％";
// (d) rounded down), from the deep space module's ds_area exp / max_exp.
int64_t deep_space_exploration_rate(Ctx& ctx, int64_t area_id) {
    int64_t max = ctx.m.one("select ifnull(max_exp, 0) from master_deep_space_area where id = ?", {area_id});
    int64_t exp = ctx.st.one("select ifnull(max(exp), 0) from ds_area where area_id = ?", {area_id});
    return max > 0 ? exp * 100 / max : 0;
}

// Type 45: deep space expeditions (a: text "ディープスペース探査を N回行う"); (d) a departure
// counts (api/deepspace/deepspace.cpp ds_log). (d) Rows with is_unlimited count every
// expedition; the others (the campaign rows) only those inside their opened_at .. closed_at.
int64_t deep_space_expeditions(Ctx& ctx, const Row& achievement_row) {
    if (!achievement_row.null("is_unlimited") && achievement_row.i("is_unlimited")) return ctx.st.one("select count(*) from ds_log", {});
    std::string opened_at = achievement_row.s("opened_at"), closed_at = achievement_row.s("closed_at");
    int64_t from = opened_at.empty() ? 0 : ctx.parse_time(opened_at), to = closed_at.empty() ? INT64_MAX : ctx.parse_time(closed_at);
    return ctx.st.one("select count(*) from ds_log where started_at >= ? and started_at <= ?", {from, to});
}

// Type 52: favor points with a character: (a) target_id is a same_role_id (target_id_label
// role_cc0035 = master_role.same_role_id_label; it used to be looked up as a role id and never
// matched), the favor module's per-same_role_id points.
int64_t favor_points(Ctx& ctx, int64_t same_role_id) {
    return ctx.st.one("select ifnull(max(point), 0) from favor where same_role_id = ?", {same_role_id});
}

// Progress of one master_achievement row, from the server state (a: the row's type and
// target_id; the meaning of each type is (a)+text, docs/server-rules.md section 10). Types the
// server doesn't track report 0 (d).
int64_t progress(Ctx& ctx, const Row& achievement_row) {
    int type = (int)achievement_row.i("type");
    int64_t target = achievement_row.null("target_id") ? 0 : achievement_row.i("target_id");
    switch ((AchievementType)type) {
        case AchievementType::kCharacterGachaDraws:
            return target ? ctx.st.one("select count(*) from gacha_history where gacha_id = ?", {target})
                          : ctx.st.one("select count(*) from gacha_history", {});
        case AchievementType::kCharacterBoosts:
            return counter(ctx, "boost");
        case AchievementType::kEvolutions:
            return counter(ctx, "evolution_to_" + std::to_string(target ? target : 0)) + (target ? 0 : counter(ctx, "evolution"));
        case AchievementType::kCharacterLimitBreaks:
            return counter(ctx, "limit_break");
        case AchievementType::kWeaponBoosts:
            return counter(ctx, "weapon_boost");
        case AchievementType::kWeaponLimitBreaks:
            // (a) the rows' texts: 武器を N回上限解放する (goal_count 1 .. 1000), and the hint
            // "同じ武器を強化合成すると、上限解放します"; (b) a compose raises the limit break once per
            // copy (CItemStrengtheningPotal::GetAddLimitReleaseWeaponNum), so each raise counts: the
            // `weapon_limit_break` counter of ItemCompose (api/items/items.cpp). Until 2026-10-03
            // this read `weapon_boost`, which every weapon compose counts.
            return counter(ctx, "weapon_limit_break");
        case AchievementType::kWeaponGradeUps:
            return counter(ctx, "weapon_grade_up");
        case AchievementType::kMissionClears:
        case AchievementType::kTitleMissionClears:
            return ctx.st.one("select ifnull(sum(clear_count), 0) from mission where mission_id = ?", {target});
        case AchievementType::kOwnCharacter:
            return ctx.st.one("select count(*) from roster where role_id = ?", {target}) > 0 ? 1 : 0;
        case AchievementType::kCharacterLevel:
            return ctx.st.one("select ifnull(max(level), 0) from roster", {});
        case AchievementType::kCharacterLimitBreak:
            return ctx.st.one("select ifnull(max(limit_break), 0) from roster", {});
        case AchievementType::kExchanges:
            return counter(ctx, "exchange");
        case AchievementType::kPlayerRank:
            return ctx.st.one("select level from player", {});
        case AchievementType::kAccessoryBoosts:
            return counter(ctx, "accessory_boost");
        case AchievementType::kDeepSpaceExploration:
            return deep_space_exploration_rate(ctx, target);
        case AchievementType::kDeepSpaceExpeditions:
            return deep_space_expeditions(ctx, achievement_row);
        case AchievementType::kSphere211Floor:  // the floor reached / battles won in the row's window
        case AchievementType::kSphere211Wins:
            return sphere211::achievement_progress(ctx, type, achievement_row.s("opened_at"), achievement_row.s("closed_at"));
        case AchievementType::kFavorPoints:
            return favor_points(ctx, target);
        default:
            return 0;
    }
}

// ---- the active list ---------------------------------------------------------------------

// Whether achievement `id` has been received (the `achievements` table).
bool received(Ctx& ctx, int64_t id) { return ctx.st.one("select count(*) from achievements where id = ? and received_at is not null", {id}) != 0; }

// The active achievements: (a) default_release rows open at the server clock, plus the
// next_achievement_id of received ones; (d) received rows leave the list.
std::vector<int64_t> active_achievement_ids(Ctx& ctx) {
    std::vector<int64_t> ids;
    ServerTime t = ctx.now();
    std::string now = ctx.fmt_time(t);
    ctx.m.q(
        "select id, opened_at, closed_at from master_achievement where default_release = 1 and type not in (61, 62) and "
        "(closed_at is null or closed_at = '' or closed_at >= ?) and (opened_at is null or opened_at = '' or opened_at <= ?)",
        {now, now}, [&](const Row& achievement_row) { ids.push_back(achievement_row.i("id")); });
    // (d) the Sphere 211 achievements (types 61 / 62) run on the season's moved dates
    // (sphere211::achievement_open, api/sphere211/sphere211.cpp)
    ctx.m.q("select id, opened_at, closed_at from master_achievement where default_release = 1 and type in (61, 62)", {},
            [&](const Row& achievement_row) {
                if (sphere211::achievement_open(ctx, achievement_row.s("opened_at"), achievement_row.s("closed_at"), nullptr))
                    ids.push_back(achievement_row.i("id"));
            });
    ctx.st.q("select id from achievements where received_at is not null", {}, [&](const Row& received_row) {
        int64_t next = ctx.m.one("select next_achievement_id from master_achievement where id = ?", {received_row.i("id")});
        if (next) ids.push_back(next);
    });
    // The starter missions (スターターミッション: (b) the rows with help_addr, which the client's
    // tAchievement::InitializeStarterList takes from this list and shows as the home's "Next
    // Mission" popup): (d) a state seeded from a save (meta 'seed'; the restored rank-87 account,
    // every planet open) had finished them, so they are left out, their rewards not granted again.
    // A player the server created (new-player mode) gets them.
    bool seeded = ctx.st.one("select count(*) from meta where key = 'seed'", {}) > 0;
    std::vector<int64_t> active;
    for (int64_t id : ids) {
        if (seeded && ctx.m.one("select count(*) from master_achievement where id = ? and help_addr is not null", {id})) continue;
        if (!received(ctx, id)) active.push_back(id);
    }
    return active;
}

// The CAchievementInfo of achievement `id`; *goal = whether it is achieved.
Value achievement_info(Ctx& ctx, int64_t id, bool* goal = nullptr) {
    Value info = Value::object();
    ctx.m.q("select * from master_achievement where id = ?", {id}, [&](const Row& achievement_row) {
        int64_t count = progress(ctx, achievement_row), goal_count = achievement_row.i("goal_count");
        bool done = count >= goal_count && goal_count > 0;
        info["id"] = (u32)id;
        info["player_id"] = ctx.player_id().v;
        info["master_achievement_id"] = (u32)id;
        info["count"] = (u32)std::min(count, goal_count);
        info["is_goal"] = done;
        info["status"] = done ? kStatusAchieved : kStatusInProgress;
        std::string limit_at = achievement_row.s("closed_at");
        if (sphere211::is_achievement_type((int)achievement_row.i("type")))
            sphere211::achievement_open(ctx, achievement_row.s("opened_at"), achievement_row.s("closed_at"), &limit_at);
        info["limit_at"] = limit_at;
        if (goal) *goal = done;
    });
    return info;
}

// The `Achievement` state: CAchievementActiveInfoList, every active achievement by its id.
// (b) It is an InfoBaseNumberMap<CAchievementInfo> and must be a map keyed by the id: its
// IInfoBaseMap<u64, CAchievementInfo>::DeserializeArray returns 0 without reading anything, so an
// array (what this sent at first) left the client's list (CParameterManager+0x67c8) empty and the
// 実績 screen (CAchievementMenu, tAchievement::InitializeList) said everything was achieved.
Value achievement_map(Ctx& ctx) {
    Value map = Value::object();
    for (int64_t id : active_achievement_ids(ctx)) map[std::to_string(id)] = achievement_info(ctx, id);
    return map;
}

// OnPlayerLoad hook (runs right after the login bonus's: core/modules.cpp): adds `Achievement`
// to every full-state player response (Login, SimpleLogin, CreatePlayer, GetPlayer, NoLoginStart).
// Rules: docs/server-rules.md "Favor achievements"
//   (b) the client reads the `Achievement` state (CParameterManager+0x67c8) for its
//       favor-achievement popup (CAdjutantSelect -> GetNotReceiveGoaledFavorabilityAchievement ->
//       AchievementListReceive) and the home badge before any screen asks: 3.7.0 sends
//       AchievementActiveList only when the 実績 (kind 1) or 称号 (kind 3) screen opens
//       (port/scripts/home_session.sh checks it).
//   (d) whether the online server put it in these responses too is unknown.
void load_achievements(Ctx& ctx, const Request&, Value& data) { data["Achievement"] = achievement_map(ctx); }

// AchievementActiveList(u32 category) -> AchievementActiveListRes          fid d0b25cb6
// API: docs/api.md#achievementactivelist   Rules: docs/server-rules.md "10. Achievements", docs/server-rules.md#achievements
//
// The active achievements with their progress (CAchievementMenu::Initialize, the 実績 screen,
// sends category 1; CHonorMenu::ProgressList, the 称号 screen, 3).
//   (b)+(d) the category isn't read: every active achievement is answered. (b) The client merges
//   the answer into its one active list (CApiNotify::OnAchievementActiveListRes @014df128 adds
//   each entry to CParameterManager+0x67c8) and each screen picks its rows itself, by the master
//   row's own category (tAchievement::InitializeCategory -> tAchievement::GetCategory @0181ce10:
//   the row's `category` string, normal / daily / weekly, and EVENT); so the whole list shows the
//   same screens. (d) What the online server left out per category can't be seen.
// Answers: the player state with Achievement (achievement_map).
std::vector<u8> achievement_active_list(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["Achievement"] = achievement_map(ctx);
    return body(data);
}

// ---- receiving ---------------------------------------------------------------------------

// Receives one achievement: only an achieved, unreceived one. (a) Its reward (content_type,
// content_id, num) goes to the present box (c), with its CPresentBoxInfo in `added`.
bool receive_achievement(Ctx& ctx, int64_t id, Value& added) {
    bool goal = false;
    achievement_info(ctx, id, &goal);
    if (!goal || received(ctx, id)) return false;
    ctx.m.q("select content_type, content_id, num from master_achievement where id = ?", {id}, [&](const Row& reward) {
        if (reward.i("content_type")) {
            add_present(ctx, (u32)reward.i("content_type"), (u32)reward.i("content_id"), (u32)reward.i("num"), kPresentAchievement, (u32)id);
            Value present = Value::object();
            ctx.st.q("select * from presents where id = ?", {ctx.st.one("select max(id) from presents", {})},
                     [&](const Row& present_row) { present = present_box_info(ctx, present_row); });
            added.push(present);
        }
    });
    ctx.st.q("insert or replace into achievements (id, progress, received_at) values (?, ?, ?)", {id, 0, ctx.now()});
    count(ctx, "achievement_received");
    return true;
}

// The achievements a receive request names.
struct AchievementReceiveArgs {
    std::vector<u64> ids;
    bool all = false;  // AchievementReceiveList(): no argument
    static AchievementReceiveArgs from(const Request& req) {
        AchievementReceiveArgs args;
        if (!req.vecs.empty()) args.ids = req.vecs[0];
        else if (!req.ints.empty()) args.ids.push_back(req.ints[0]);
        else args.all = true;
        return args;
    }
};

// AchievementReceive(u64 id) -> AchievementReceiveRes                     fid 47e9dee6
// AchievementListReceive(vector<u64> ids) -> AchievementListReceiveRes    fid bbc99ccf
// AchievementReceiveList() -> AchievementReceiveListRes                   fid f43a965d
// API: docs/api.md#achievementreceive, docs/api.md#achievementlistreceive, docs/api.md#achievementreceivelist
// Rules: docs/server-rules.md "10. Achievements", docs/server-rules.md#achievements, docs/server-rules.md "Favor achievements"
//
// Receives achievements: each achieved, unreceived one puts its reward in the present box and
// leaves the active list (its next_achievement_id joins it). AchievementListReceive is the
// 一括達成 button and CAdjutantSelect's favor-achievement popup (b).
//   (d) AchievementReceiveList (no caller found in the client) receives everything achieved.
// Answers: the player state with Achievement, AddPresent (the rewards' CPresentBoxInfo),
// ReceiveAchievementId (the last received), IsUpdateAchievement, PresentBoxCount.
std::vector<u8> achievement_receive(Ctx& ctx, const Request& req) {
    auto args = AchievementReceiveArgs::from(req);
    if (args.all) {
        auto active = active_achievement_ids(ctx);
        args.ids.assign(active.begin(), active.end());
    }
    Value added = Value::array();
    int received_count = 0;
    u32 last_received = 0;
    for (u64 id : args.ids)
        if (receive_achievement(ctx, (int64_t)id, added)) {
            received_count++;
            last_received = (u32)id;
        }
    Value data = ctx.base_data();
    data["Achievement"] = achievement_map(ctx);
    if (!added.arr.empty()) data["AddPresent"] = added;
    data["ReceiveAchievementId"] = last_received;
    data["IsUpdateAchievement"] = received_count ? 1u : 0u;
    data["PresentBoxCount"] = (u32)ctx.st.one("select count(*) from presents where received_at is null", {});
    LOGI("server", "%s: %d of %zu received", req.method.c_str(), received_count, args.ids.size());
    return body(data);
}

}  // namespace

Value ext::achievement_state(Ctx& ctx) { return achievement_map(ctx); }

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_achievements() {
    using namespace ext;
    add_player_load(load_achievements);
    add_api({"AchievementActiveList"}, achievement_active_list);
    add_api({"AchievementReceive", "AchievementListReceive", "AchievementReceiveList"}, achievement_receive);
}

}  // namespace soa::server
