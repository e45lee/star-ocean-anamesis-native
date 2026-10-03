// Sphere 211: the seasons, the dive's season change, and the achievements that move with the
// season (api/sphere211/README.md; declared in dive.h and sphere211.h). Port code, not guest
// behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption. Rules in docs/server-rules.md "Sphere 211".
#include <algorithm>
#include <climits>
#include <string>
#include <vector>

#include "api/sphere211/dive.h"
#include "core/log.h"
#include "core/time.h"

namespace soa::server::sphere211 {

namespace {
Season season_from_row(const Row& season_row) {
    Season season;
    season.id = (u32)season_row.i("id");
    season.index = (u32)season_row.i("season_index");
    season.floor_group = (u32)season_row.i("master_sphere211_floor_group_id");
    season.clear_present_group = (u32)season_row.i("master_sphere211_floor_clear_present_group_id");
    season.ranking_reward = (u32)season_row.i("master_sphere211_ranking_reward_id");
    season.treasure_contents = (u32)season_row.i("master_sphere211_treasure_contents_id");
    season.heal_item = (u32)season_row.i("heal_item_id");
    season.reroll_item = (u32)season_row.i("reroll_item_id");
    season.reroll_num = (u32)std::max<int64_t>(1, season_row.i("reroll_item_num"));
    season.opened_at = season_row.s("opened_at");
    season.closed_at = season_row.s("closed_at");
    return season;
}
}  // namespace

Season season_by_id(Ctx& ctx, u32 season_id) {
    Season season;
    ctx.m.q("select * from master_sphere211 where id = ?", {season_id}, [&](const Row& season_row) { season = season_from_row(season_row); });
    return season;
}

// The season of the event calendar `ev` (server.h event_now: today's date replayed onto the
// service's years, or --clock) and how far its dates must move to be current on the client's
// clock `clock` (the client compares master_sphere211 dates with its own clock, which follows the
// server's data.Time = clock_now: MissionUtility::Sphere211ClosedTime, b):
//  - (a) the season whose opened_at .. closed_at covers `ev`; shift = clock - ev;
//  - (d) before the first season (the replayed calendar maps some days, e.g. Oct 1 - 2, Oct 7, to
//    2019): the same date and time in the next year that reaches the seasons (the 13 seasons span
//    one year, 2020-06-25 .. 2021-06-24), so every day of the year has its season;
//  - (d) in a gap between two seasons (the hour 14:00 .. 15:00 of a change, and the day between
//    the last season's end and the first one's date a year later): the previous season, its
//    window moved forward by whole season lengths until it covers `ev`;
//  - (d) past that (the service ended with season 13 on 2021-06-24): the last season runs on in
//    the same way, each further season length a new `cycle` (a new season for the dive and the
//    ranking).
SeasonPick pick_season(ext::Sql& master, int64_t clock, int64_t ev) {
    struct Window {
        u32 id;
        int64_t opened, closed;
    };
    std::vector<Window> seasons;
    master.q("select id, opened_at, closed_at from master_sphere211 order by opened_at", {}, [&](const Row& season_row) {
        seasons.push_back({(u32)season_row.i("id"), parse_time(season_row.s("opened_at")), parse_time(season_row.s("closed_at"))});
    });
    SeasonPick pick;
    if (seasons.empty()) return pick;
    for (auto& season : seasons)
        if (season.opened <= ev && ev <= season.closed) {
            pick.id = season.id;
            pick.shift = clock - ev;
            return pick;
        }
    if (ev < seasons.front().opened) {
        int64_t next_year = ev;
        for (int n = 0; n < 200 && next_year < seasons.front().opened; n++) next_year = add_years(next_year, 1);
        if (next_year >= seasons.front().opened) return pick_season(master, clock, next_year);
    }
    const Window* latest = &seasons.front();
    for (auto& season : seasons)
        if (season.opened <= ev) latest = &season;
    // the fewest whole periods k that bring the window's end to `ev` or later
    int64_t period = std::max<int64_t>(1, latest->closed - latest->opened + 1);
    int64_t k = std::max<int64_t>(0, (ev - latest->closed + period - 1) / period);
    pick.id = latest->id;
    pick.shift = clock - ev + k * period;
    if (latest == &seasons.back() && ev >= add_years(seasons.front().opened, 1)) pick.cycle = (u32)k;
    return pick;
}

SeasonPick current_pick(Ctx& ctx) { return pick_season(ctx.m, ctx.now(), ctx.event_now()); }
Season current_season(Ctx& ctx) {
    SeasonPick pick = current_pick(ctx);
    Season season = season_by_id(ctx, pick.id);
    season.cycle = pick.cycle;
    season.shift = pick.shift;
    if (pick.shift) {
        season.opened_at = format_time(parse_time(season.opened_at) + pick.shift);
        season.closed_at = format_time(parse_time(season.closed_at) + pick.shift);
    }
    return season;
}

// ClientMaster: the client's master copy gets the same season dates (a data override, server side).
void client_seasons(ext::Sql& db, int64_t clock, int64_t ev) {
    SeasonPick pick = pick_season(db, clock, ev);
    if (!pick.id || !pick.shift) return;
    for (const char* col : {"opened_at", "closed_at", "ranking_opened_at", "ranking_closed_at"}) {
        std::string date;
        db.q(std::string("select ") + col + " as v from master_sphere211 where id = ?", {pick.id},
             [&](const Row& season_row) { date = season_row.s("v"); });
        if (date.empty()) continue;
        db.q(std::string("update master_sphere211 set ") + col + " = ? where id = ?", {format_time(parse_time(date) + pick.shift), pick.id});
    }
    LOGI("server", "Sphere211: season %u, dates moved %lld days in the client's master (event calendar %s, clock %s)", pick.id,
         (long long)(pick.shift / 86400), format_time(ev).c_str(), format_time(clock).c_str());
}

// Loads (and on a new season resets) the dive. (d) A season change (another season, or another
// cycle of the repeated last one) ends the dive (everyone back, the EX sorties' uses too): its boxes are opened into the player's items; its
// result becomes Sphere211EndResult (sent once, see put_state): the best floor, the boxes gathered,
// and rank 1 of the local ranking when a battle was won in it (b: master_text
// uimsg_sphere211_ranking_empty2 "ミッションを1つもクリアしていない場合は、ランキング未参加"; rank 0 =
// not ranked, then the client only says the season has ended), with that rank's ranking reward.
Season load_dive(Ctx& ctx) {
    Season season = current_season(ctx);
    int64_t t = ctx.now();
    if (!ctx.st.one("select count(*) from sphere", {})) {
        ctx.st.q("insert into sphere (id, season_id, floor_level, stamina, stamina_at, entered_at) values (1, ?, 0, ?, ?, ?)",
                 {season.id, stamina_max(ctx), t, t});  // (d) the gauge starts full
        set_sphere_meta(ctx, "cycle", season.cycle);
    }
    u32 dive_season = (u32)ctx.st.one("select season_id from sphere where id = 1", {});
    u32 dive_cycle = (u32)sphere_meta(ctx, "cycle");
    if (dive_season != season.id || dive_cycle != season.cycle) {
        Season old = season_by_id(ctx, dive_season);
        if (old.id) open_boxes(ctx, old, nullptr, nullptr, nullptr, nullptr);
        u32 best = (u32)ctx.st.one("select ifnull(max(floor_level), 0) from sphere_rank where season_id = ?", {dive_season});
        u32 boxes = (u32)ctx.st.one("select treasure_total from sphere where id = 1", {});
        u32 wins = (u32)sphere_meta(ctx, "season_wins");
        u32 rank = old.id && wins ? 1u : 0u;
        if (rank) ranking_reward(ctx, old.id, rank);
        ctx.st.q(
            "update sphere set season_id = ?, floor_level = 0, asset_group = 0, streak = 0, treasure_total = 0, clear_asset = 0, "
            "lot_floor_num = 0, revive_count = 0, prev_season = ?, prev_floor = ?, prev_treasure = ?, prev_rank = ?",
            {season.id, dive_season, best, boxes, rank});
        ctx.st.exec("delete from sphere_cell");
        ctx.st.exec("delete from sphere_departed");
        ctx.st.exec("delete from sphere_rental");
        ctx.st.q("delete from sphere_rank where season_id = ?", {season.id});  // a repeated season ranks anew
        set_sphere_meta(ctx, "cycle", season.cycle);
        set_sphere_meta(ctx, "season_wins", 0);
        set_sphere_meta(ctx, "end_pending", old.id ? 1 : 0);
        LOGI("server", "Sphere211: season %u (cycle %u) -> %u (cycle %u); best floor %u, %u battles won, rank %u", dive_season, dive_cycle, season.id,
             season.cycle, best, wins, rank);
    }
    tick_stamina(ctx);
    return season;
}

// ---- achievements (types 61 / 62) -----------------------------------------------------------
// (a) master_achievement type 61 rows say "スフィア211の N F以上に到達する" (per season: Event_sphere_
// floor_<N>_<season>, the season's window; two rows 211F / 300F run to 2030), type 62 rows
// "スフィア211のミッションを N回クリアする" (スフィア週間チャレンジ, the weekly challenge: 7-day windows,
// Thursday 14:30 .. Thursday 13:59:59; and campaign rows "スフィア２１１を N回クリアする"). (d) Their
// windows are service dates like the seasons', so they move by the current season's shift (the
// replayed calendar: the weekly challenge of the season being replayed runs this week); progress
// counts what the server logged (sphere_log, server clock) while the moved window ran: the battles
// won (type 62; a won Sphere211MissionEnd, b: the achievement's text says ミッションをクリア) and the
// highest floor entered (type 61, the floor reached).
namespace {
enum class AchievementType : int { kFloorReached = 61, kBattlesWon = 62 };  // (a) master_achievement.type

// The moved window [lo, hi] (INT64 bounds when open-ended).
void moved_window(Ctx& ctx, const std::string& opened_at, const std::string& closed_at, int64_t& lo, int64_t& hi) {
    int64_t shift = current_pick(ctx).shift;
    lo = opened_at.empty() ? INT64_MIN : parse_time(opened_at) + shift;
    hi = closed_at.empty() ? INT64_MAX : parse_time(closed_at) + shift;
}
}  // namespace

bool is_achievement_type(int type) { return type == (int)AchievementType::kFloorReached || type == (int)AchievementType::kBattlesWon; }
bool achievement_open(Ctx& ctx, const std::string& opened_at, const std::string& closed_at, std::string* limit_at) {
    int64_t lo, hi;
    moved_window(ctx, opened_at, closed_at, lo, hi);
    if (limit_at) *limit_at = closed_at.empty() ? std::string() : format_time(hi);
    int64_t t = ctx.now();
    return lo <= t && t <= hi;
}
int64_t achievement_progress(Ctx& ctx, int type, const std::string& opened_at, const std::string& closed_at) {
    if (!ctx.st.one("select count(*) from sqlite_master where name = 'sphere_log'", {})) return 0;
    int64_t lo, hi;
    moved_window(ctx, opened_at, closed_at, lo, hi);
    if (type == (int)AchievementType::kBattlesWon)
        return ctx.st.one("select count(*) from sphere_log where kind = ? and at between ? and ?", {(int)LogKind::kWin, lo, hi});
    if (type == (int)AchievementType::kFloorReached)
        return ctx.st.one("select ifnull(max(value), 0) from sphere_log where kind = ? and at between ? and ?", {(int)LogKind::kFloor, lo, hi});
    return 0;
}

}  // namespace soa::server::sphere211
