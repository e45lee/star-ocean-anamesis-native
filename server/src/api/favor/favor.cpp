// The favorability (bond, 好感度) rules: levels, points, the daily tap, favor items, the battle
// gain and the event drop bonus's daily use. Port code, not guest behaviour. See favor.h and
// docs/server-rules.md#favor-rules; every rule carries its source label: (a) master data,
// (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include "api/favor/favor.h"

#include <sqlite3.h>

#include <algorithm>
#include <cstring>
#include <ctime>
#include <functional>
#include <map>
#include <optional>
#include <set>

#include "core/log.h"
#include "core/time.h"
#include "core/wallet.h"  // stock_count, take_stock
#include "master/master.h"
#include "soaserver/sql.h"

namespace soa::server::favor {

namespace {

// The handles favor.h's callers pass, through the one SQL wrapper (soaserver/sql.h). A NULL
// value reads as 0 / "" (Row), and a lookup by key reads its one row.
using sql::Arg;
using sql::Row;
using sql::Sql;

// master_global (a): an empty value reads as the default (master::global_u32_unless_empty).
u32 global_u32(sqlite3* m, const char* key, u32 dflt) { return master::global_u32_unless_empty(m, key, dflt); }

// (a) master_favor_level.next_favor_point, by level id (1..5).
std::vector<u32> thresholds(sqlite3* m) {
    std::vector<u32> next;
    Sql{m}.q("select id, next_favor_point from master_favor_level order by id", {}, [&](const Row& level_row) {
        size_t level_id = (size_t)level_row.i("id");
        if (level_id == 0) return;
        if (next.size() < level_id) next.resize(level_id, 0);
        next[level_id - 1] = (u32)level_row.i("next_favor_point");
    });
    return next;
}

// (a) master_favor_schedule: the character's maximum level (favor_max_level, or
// next_favor_max_level from next_opened_at on). 0 = no schedule: favor isn't enabled for it (the
// client's GetEnableFavorability returns false for it too (b)).
u32 max_level(sqlite3* m, ServerTime now, SameRoleId same_role_id) {
    u32 max = 0;
    Sql{m}.q("select favor_max_level, next_favor_max_level, next_opened_at from master_favor_schedule where id = ?", {same_role_id},
             [&](const Row& schedule_row) {
                 max = (u32)schedule_row.i("favor_max_level");
                 std::string next_opened_at = schedule_row.s("next_opened_at");
                 int64_t next_max = schedule_row.i("next_favor_max_level");
                 // the master's date against the server clock (the client's own reading, (b))
                 if (next_max > max && !next_opened_at.empty() && parse_time_strict(next_opened_at) <= now.v)
                     max = (u32)next_max;  // (a)+(b) as GetEnableFavorability
             });
    return max;
}

// One character's row of the `favor` table. The times are seconds on the server clock, NULL
// (nullopt) for never (PLAN-schema 3.1, S9); the responses format them at the boundary
// (format_time_or_empty: "" for never, as the client's empty time).
struct State {
    u32 point = 0, taps = 0;  // favor points; taps on tapped_at's favor day
    std::optional<ServerTime> tapped_at;  // the last tap that counted
    std::optional<ServerTime> event_drop_at;  // added_event_drop_at: the event drop bonus last spent
};
std::string format_time_or_never(const std::optional<ServerTime>& t) { return format_time_or_empty(t ? t->v : 0); }
State load(sqlite3* st, SameRoleId same_role_id) {
    State state;
    Sql{st}.q("select point, tap_count, tapped_at, event_drop_at from favor where same_role_id = ?", {same_role_id}, [&](const Row& favor_row) {
        state.point = (u32)favor_row.i("point");
        state.taps = (u32)favor_row.i("tap_count");
        state.tapped_at = favor_row.opt<ServerTime>("tapped_at");
        state.event_drop_at = favor_row.opt<ServerTime>("event_drop_at");
    });
    return state;
}
void save(sqlite3* st, SameRoleId same_role_id, const State& state) {
    Sql{st}.q(
        "insert into favor (same_role_id, point, tap_count, tapped_at, event_drop_at) values (?,?,?,?,?)"
        " on conflict(same_role_id) do update set point = excluded.point, tap_count = excluded.tap_count, "
        "tapped_at = excluded.tapped_at, event_drop_at = excluded.event_drop_at",
        {same_role_id, state.point, state.taps, state.tapped_at, state.event_drop_at});
}

// Today's taps of a character: the count resets at the favor day boundary (never tapped: none).
u32 taps_today(sqlite3* m, const State& state, ServerTime now) {
    int reset_hour = (int)global_u32(m, "login_bonus_reset_hour", 4);
    return rules::favor_day(state.tapped_at.value_or(ServerTime(0)).v, reset_hour) == rules::favor_day(now.v, reset_hour) ? state.taps : 0;
}

// The CPlayerCharacterFavorInfoElement of one character (property names from its Initialize (b)).
Value element(sqlite3* m, ServerTime now, SameRoleId same_role_id, const State& state, u32 level) {
    Value e = Value::object();
    e["master_role_same_role_id"] = same_role_id.v;
    e["favor_point"] = state.point;
    e["favor_level"] = level;
    e["added_event_drop_at"] = format_time_or_never(state.event_drop_at);
    e["favor_up_count_by_tap"] = taps_today(m, state, now);
    e["updated_by_tap_at"] = format_time_or_never(state.tapped_at);
    return e;
}

// What adding points to a character did: the states and levels before and after; ok = false
// (nothing saved) for a character without favor.
struct Gain {
    State before, after;
    u32 level_before = 1, level_after = 1;
    bool ok = false;
};
Gain add_points(sqlite3* st, sqlite3* m, ServerTime now, SameRoleId same_role_id, u32 points) {
    Gain gain;
    u32 max = max_level(m, now, same_role_id);
    if (!max) return gain;
    auto next = thresholds(m);
    gain.before = load(st, same_role_id);
    gain.after = gain.before;
    gain.after.point = rules::cap_points((u32)std::min<uint64_t>((uint64_t)gain.before.point + points, 0xffffffffu), next, max);
    gain.level_before = rules::level(gain.before.point, next, max);
    gain.level_after = rules::level(gain.after.point, next, max);
    save(st, same_role_id, gain.after);
    gain.ok = true;
    return gain;
}

}  // namespace

namespace rules {

u32 level(u32 points, const std::vector<u32>& next, u32 max_level) {
    u32 lv = 1;
    for (size_t i = 0; i < next.size(); i++)
        if (next[i] > 0 && points >= next[i]) lv = (u32)i + 2;
    if (max_level && lv > max_level) lv = max_level;
    return lv;
}

u32 cap_points(u32 points, const std::vector<u32>& next, u32 max_level) {
    if (max_level >= 2 && max_level - 2 < next.size() && next[max_level - 2] > 0) return std::min(points, next[max_level - 2]);
    return points;
}

int64_t favor_day(int64_t t, int reset_hour) {
    if (t <= 0) return -1;
    time_t tt = (time_t)(t - (int64_t)reset_hour * 3600);
    struct tm tm {};
    localtime_r(&tt, &tm);
    return (int64_t)(tm.tm_year + 1900) * 1000 + tm.tm_yday;
}

}  // namespace rules

u32 level_of(sqlite3* st, sqlite3* m, ServerTime now, SameRoleId same_role_id) {
    u32 max = max_level(m, now, same_role_id);
    if (!max) return 1;
    return rules::level(load(st, same_role_id).point, thresholds(m), max);
}

// ---- the event drop bonus (docs/server-rules.md#event-extras; api/events/favor_drop.cpp) -------
// (b) a character's bonus is spent for the favor day once added_event_drop_at is set inside it
// (3.7.0 CParameterUtility::GetFavorDropIconImageName: the icon returns after the next
// login_bonus_reset_hour); (a) master_global favor_event_drop_bonus_limit uses a day, (d) counted
// in characters.
bool event_drop_used_today(sqlite3* st, sqlite3* m, ServerTime now, SameRoleId same_role_id) {
    std::optional<ServerTime> at = load(st, same_role_id).event_drop_at;
    if (!at) return false;
    int reset_hour = (int)global_u32(m, "login_bonus_reset_hour", 4);
    return rules::favor_day(at->v, reset_hour) == rules::favor_day(now.v, reset_hour);
}
u32 event_drop_remaining(sqlite3* st, sqlite3* m, ServerTime now) {
    u32 limit = global_u32(m, "favor_event_drop_bonus_limit", 3), used = 0;
    std::vector<SameRoleId> same_role_ids;
    Sql{st}.q("select same_role_id from favor where event_drop_at is not null", {},
              [&](const Row& favor_row) { same_role_ids.push_back(favor_row.id<SameRoleId>("same_role_id")); });
    for (SameRoleId same_role_id : same_role_ids)
        if (event_drop_used_today(st, m, now, same_role_id)) used++;
    return limit > used ? limit - used : 0;
}
std::string mark_event_drop(sqlite3* st, SameRoleId same_role_id, ServerTime now) {
    State state = load(st, same_role_id);
    state.event_drop_at = now;
    save(st, same_role_id, state);
    return format_time_or_never(state.event_drop_at);
}

void add_player_state(sqlite3* st, sqlite3* m, ServerTime now, SameRoleId home_same_role_id, Value& data) {
    // Every owned character's same_role_id (roster role -> master_role.same_role_id).
    std::set<SameRoleId> same_role_ids;
    {
        std::vector<u32> roles;
        Sql{st}.q("select distinct role_id from roster", {}, [&](const Row& roster_row) { roles.push_back((u32)roster_row.i("role_id")); });
        for (u32 role : roles)
            Sql{m}.q("select same_role_id from master_role where id = ?", {role},
                     [&](const Row& role_row) { same_role_ids.insert(role_row.id<SameRoleId>("same_role_id")); });
    }
    auto next = thresholds(m);
    Value map = Value::object();
    for (SameRoleId same_role_id : same_role_ids) {
        u32 max = max_level(m, now, same_role_id);
        if (!max) continue;  // (a) no schedule: no favor
        State state = load(st, same_role_id);
        map[std::to_string(same_role_id.v)] = element(m, now, same_role_id, state, rules::level(state.point, next, max));
    }
    data["PlayerCharacterFavorMap"] = map;
    // (a) master_global.favor_tap_bonus_limit taps per character per day; (d) the load reports the
    // home character's remaining count (the client keeps one number, CParameterManager +0xb660,
    // and checks it for the home character's tap, CHome::IsAddFavorPointByTap (b)).
    u32 limit = global_u32(m, "favor_tap_bonus_limit", 5);
    u32 used = home_same_role_id.v ? taps_today(m, load(st, home_same_role_id), now) : 0;
    data["RemainingUpdateFavorCountByTap"] = limit > used ? limit - used : 0u;
    // (a) master_global.favor_event_drop_bonus_limit less today's uses (the event drop bonus above)
    data["RemainingEventDropBonusCountByFavor"] = event_drop_remaining(st, m, now);
    LOGI("server", "favor: %zu characters in PlayerCharacterFavorMap", map.map.size());
}

Value mission_gain(sqlite3* st, sqlite3* m, ServerTime now, SameRoleId same_role_id, u32 stamina, double rate) {
    // (a) master_favor_battle_effect: favor_up_point for the mission's use_stamina, play_type 0
    // (single play; 1 = multiplay host, 2 = guest). (d) a stamina with no row gives the row of
    // the largest use_stamina below it.
    u32 points = 0;
    Sql{m}.q(
        "select favor_up_point from master_favor_battle_effect where play_type = 0 and use_stamina <= ? "
        "order by use_stamina desc limit 1",
        {stamina}, [&](const Row& effect_row) { points = (u32)effect_row.i("favor_up_point"); });
    // (a)+(b) a running type-8 campaign (友好, ×1.5) multiplies the battle favor (api/missions/
    // mission_end.cpp); (d) truncated
    if (rate != 1.0) points = (u32)((double)points * rate);
    Gain gain = add_points(st, m, now, same_role_id, points);
    if (!gain.ok) return Value();
    Value result = Value::object();
    result["id"] = same_role_id.v;
    result["master_role_same_role_id"] = same_role_id.v;
    result["before_favor_level"] = gain.level_before;
    result["before_favor_point"] = gain.before.point;
    result["after_favor_level"] = gain.level_after;
    result["after_favor_point"] = gain.after.point;
    result["added_event_drop_at"] = format_time_or_never(gain.after.event_drop_at);
    // read by port/scripts/restore_favor_session.sh ("favor: mission (stamina N) same_role")
    LOGI("server", "favor: mission (stamina %u) same_role %u +%u: %u -> %u (level %u -> %u)", stamina, same_role_id.v, points, gain.before.point,
         gain.after.point, gain.level_before, gain.level_after);
    return result;
}

void tap(sqlite3* st, sqlite3* m, ServerTime now, SameRoleId same_role_id, Value& data) {
    u32 limit = global_u32(m, "favor_tap_bonus_limit", 5);  // (a) 5 a day
    u32 points = global_u32(m, "favor_tap_bonus_point", 50);  // (a) 50 points a tap
    State state = load(st, same_role_id);
    u32 used = taps_today(m, state, now);
    Value result = Value::object();
    result["same_role_id"] = same_role_id.v;
    if (used < limit && max_level(m, now, same_role_id)) {
        Gain gain = add_points(st, m, now, same_role_id, points);
        gain.after.taps = used + 1;
        gain.after.tapped_at = now;
        save(st, same_role_id, gain.after);
        used++;
        result["favor_level"] = gain.level_after;
        result["favor_point"] = gain.after.point;
        // read by port/scripts/restore_favor_session.sh ("favor: tap same_role N +50: A -> B (level ...)")
        LOGI("server", "favor: tap same_role %u +%u: %u -> %u (level %u -> %u), %u taps left", same_role_id.v, points, gain.before.point,
             gain.after.point, gain.level_before, gain.level_after, limit - used);
    } else {
        // (d) past the limit, or a character without favor: nothing changes
        result["favor_level"] = level_of(st, m, now, same_role_id);
        result["favor_point"] = state.point;
    }
    result["RemainingUpdateFavorCountByTap"] = limit > used ? limit - used : 0u;
    data["UpdateFavorByTapResultInfo"] = result;
}

void use_item(sqlite3* st, sqlite3* m, ServerTime now, u32 master_item_id, u32 count, SameRoleId same_role_id, Value& data) {
    // (a) master_favor_item_effect: favor_up_point per item; target_type 0 = any character,
    // otherwise only master_role_same_role_id ((d) reading of target_type).
    u32 points_per_item = 0;
    bool first = true;  // the item's first effect row only
    Sql{m}.q("select favor_up_point, target_type, master_role_same_role_id from master_favor_item_effect where master_item_id = ?", {master_item_id},
             [&](const Row& effect_row) {
                 if (!first) return;
                 first = false;
                 if (effect_row.i("target_type") == 0 || effect_row.id<SameRoleId>("master_role_same_role_id") == same_role_id)
                     points_per_item = (u32)effect_row.i("favor_up_point");
             });
    // (d) the count is capped by the stack held; the stack is debited
    u32 have = wallet::stock_count(st, master_item_id);
    count = std::min(count, have);
    Gain gain = add_points(st, m, now, same_role_id, points_per_item * count);
    if (count) wallet::take_stock(st, master_item_id, count);
    Value result = Value::object();
    result["same_role_id"] = same_role_id.v;
    result["favor_level"] = gain.ok ? gain.level_after : 1u;
    result["favor_point"] = gain.ok ? gain.after.point : 0u;
    data["UseFavorResultInfo"] = result;
    LOGI("server", "favor: item %u x%u on same_role %u: +%u", master_item_id, count, same_role_id.v, points_per_item * count);
}

}  // namespace soa::server::favor
