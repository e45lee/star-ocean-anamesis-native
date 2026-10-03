// The favorability (bond, 好感度) rules: levels, points, the daily tap, favor items, the battle
// gain and the event drop bonus's daily use. Port code, not guest behaviour. See favor.h and
// docs/server-rules.md "8. Favor"; every rule carries its source label: (a) master data,
// (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include "api/favor/favor.h"

#include <sqlite3.h>

#include <algorithm>
#include <cstring>
#include <ctime>
#include <functional>
#include <map>
#include <set>

#include "core/log.h"
#include "core/time.h"
#include "master/master.h"

namespace soa::server::favor {

namespace {

// ---- a small SQLite statement wrapper on the raw handles favor.h's callers pass (PLAN-schema S1
// replaces it with the one SQL wrapper) --------------------------------------------------------
struct Q {
    sqlite3_stmt* s = nullptr;
    Q(sqlite3* db, const char* sql) {
        if (sqlite3_prepare_v2(db, sql, -1, &s, nullptr) != SQLITE_OK) {
            LOGE("server", "favor: sql error %s in %s", sqlite3_errmsg(db), sql);
            s = nullptr;
        }
    }
    ~Q() {
        if (s) sqlite3_finalize(s);
    }
    Q& bind(int i, int64_t v) {
        if (s) sqlite3_bind_int64(s, i, v);
        return *this;
    }
    Q& bind(int i, const std::string& v) {
        if (s) sqlite3_bind_text(s, i, v.c_str(), -1, SQLITE_TRANSIENT);
        return *this;
    }
    bool step() { return s && sqlite3_step(s) == SQLITE_ROW; }
    int64_t i(int c) { return sqlite3_column_int64(s, c); }
    std::string t(int c) {
        const unsigned char* p = sqlite3_column_text(s, c);
        return p ? (const char*)p : "";
    }
    bool null(int c) { return sqlite3_column_type(s, c) == SQLITE_NULL; }
    void run() {
        if (s) sqlite3_step(s);
    }
};

// The first column of the first row of `sql` (one optional integer argument), 0 without a row.
int64_t one(sqlite3* db, const char* sql, int64_t arg = 0, bool bind = false) {
    Q q(db, sql);
    if (bind) q.bind(1, arg);
    return q.step() ? q.i(0) : 0;
}

// master_global (a): an empty value reads as the default (master::global_u32_unless_empty).
u32 global_u32(sqlite3* m, const char* key, u32 dflt) { return master::global_u32_unless_empty(m, key, dflt); }

// (a) master_favor_level.next_favor_point, by level id (1..5).
std::vector<u32> thresholds(sqlite3* m) {
    std::vector<u32> next;
    Q q(m, "select id, next_favor_point from master_favor_level order by id");
    while (q.step()) {
        size_t level_id = (size_t)q.i(0);
        if (level_id == 0) continue;
        if (next.size() < level_id) next.resize(level_id, 0);
        next[level_id - 1] = (u32)q.i(1);
    }
    return next;
}

// (a) master_favor_schedule: the character's maximum level (favor_max_level, or
// next_favor_max_level from next_opened_at on). 0 = no schedule: favor isn't enabled for it (the
// client's GetEnableFavorability returns false for it too (b)).
u32 max_level(sqlite3* m, int64_t now, u32 same_role_id) {
    Q q(m, "select favor_max_level, next_favor_max_level, next_opened_at from master_favor_schedule where id = ?");
    q.bind(1, (int64_t)same_role_id);
    if (!q.step()) return 0;
    u32 max = (u32)q.i(0);
    std::string next_opened_at = q.t(2);
    if (q.i(1) > max && !next_opened_at.empty() && parse_time_strict(next_opened_at) <= now) max = (u32)q.i(1);  // (a)+(b) as GetEnableFavorability
    return max;
}

// One character's row of the `favor` table.
struct State {
    u32 point = 0, taps = 0;  // favor points; taps on tapped_at's favor day
    int64_t tapped_at = 0;
    std::string event_drop_at;  // added_event_drop_at, as sent
};
State load(sqlite3* st, u32 same_role_id) {
    State state;
    Q q(st, "select point, tap_count, tapped_at, event_drop_at from favor where same_role_id = ?");
    q.bind(1, (int64_t)same_role_id);
    if (q.step()) {
        state.point = (u32)q.i(0);
        state.taps = (u32)q.i(1);
        state.tapped_at = q.i(2);
        state.event_drop_at = q.t(3);
    }
    return state;
}
void save(sqlite3* st, u32 same_role_id, const State& state) {
    Q q(st,
        "insert into favor (same_role_id, point, tap_count, tapped_at, event_drop_at) values (?,?,?,?,?)"
        " on conflict(same_role_id) do update set point = excluded.point, tap_count = excluded.tap_count, "
        "tapped_at = excluded.tapped_at, event_drop_at = excluded.event_drop_at");
    q.bind(1, (int64_t)same_role_id).bind(2, (int64_t)state.point).bind(3, (int64_t)state.taps).bind(4, state.tapped_at).bind(5, state.event_drop_at);
    q.run();
}

// Today's taps of a character: the count resets at the favor day boundary.
u32 taps_today(sqlite3* m, const State& state, int64_t now) {
    int reset_hour = (int)global_u32(m, "login_bonus_reset_hour", 4);
    return rules::favor_day(state.tapped_at, reset_hour) == rules::favor_day(now, reset_hour) ? state.taps : 0;
}

// The CPlayerCharacterFavorInfoElement of one character (property names from its Initialize (b)).
Value element(sqlite3* m, int64_t now, u32 same_role_id, const State& state, u32 level) {
    Value e = Value::object();
    e["master_role_same_role_id"] = same_role_id;
    e["favor_point"] = state.point;
    e["favor_level"] = level;
    e["added_event_drop_at"] = state.event_drop_at;
    e["favor_up_count_by_tap"] = taps_today(m, state, now);
    e["updated_by_tap_at"] = format_time_or_empty(state.tapped_at);
    return e;
}

// What adding points to a character did: the states and levels before and after; ok = false
// (nothing saved) for a character without favor.
struct Gain {
    State before, after;
    u32 level_before = 1, level_after = 1;
    bool ok = false;
};
Gain add_points(sqlite3* st, sqlite3* m, int64_t now, u32 same_role_id, u32 points) {
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

void schema(sqlite3* st) {
    char* err = nullptr;
    sqlite3_exec(st,
                 "create table if not exists favor (same_role_id integer primary key, point integer default 0, "
                 "tap_count integer default 0, tapped_at integer default 0, event_drop_at text default '')",
                 nullptr, nullptr, &err);
    if (err) {
        LOGE("server", "favor: schema: %s", err);
        sqlite3_free(err);
    }
}

u32 level_of(sqlite3* st, sqlite3* m, int64_t now, u32 same_role_id) {
    u32 max = max_level(m, now, same_role_id);
    if (!max) return 1;
    return rules::level(load(st, same_role_id).point, thresholds(m), max);
}

// ---- the event drop bonus (docs/server-rules.md "Event extras"; api/events/favor_drop.cpp) -------
// (b) a character's bonus is spent for the favor day once added_event_drop_at is set inside it
// (3.7.0 CParameterUtility::GetFavorDropIconImageName: the icon returns after the next
// login_bonus_reset_hour); (a) master_global favor_event_drop_bonus_limit uses a day, (d) counted
// in characters.
bool event_drop_used_today(sqlite3* st, sqlite3* m, int64_t now, u32 same_role_id) {
    std::string at = load(st, same_role_id).event_drop_at;
    if (at.empty()) return false;
    int reset_hour = (int)global_u32(m, "login_bonus_reset_hour", 4);
    return rules::favor_day(parse_time_strict(at), reset_hour) == rules::favor_day(now, reset_hour);
}
u32 event_drop_remaining(sqlite3* st, sqlite3* m, int64_t now) {
    u32 limit = global_u32(m, "favor_event_drop_bonus_limit", 3), used = 0;
    std::vector<u32> same_role_ids;
    {
        Q q(st, "select same_role_id from favor where event_drop_at != ''");
        while (q.step()) same_role_ids.push_back((u32)q.i(0));
    }
    for (u32 same_role_id : same_role_ids)
        if (event_drop_used_today(st, m, now, same_role_id)) used++;
    return limit > used ? limit - used : 0;
}
std::string mark_event_drop(sqlite3* st, u32 same_role_id, int64_t now) {
    State state = load(st, same_role_id);
    state.event_drop_at = format_time_or_empty(now);
    save(st, same_role_id, state);
    return state.event_drop_at;
}

void add_player_state(sqlite3* st, sqlite3* m, int64_t now, u32 home_same_role_id, Value& data) {
    // Every owned character's same_role_id (roster role -> master_role.same_role_id).
    std::set<u32> same_role_ids;
    {
        std::vector<u32> roles;
        Q q(st, "select distinct role_id from roster");
        while (q.step()) roles.push_back((u32)q.i(0));
        for (u32 role : roles) {
            Q role_q(m, "select same_role_id from master_role where id = ?");
            role_q.bind(1, (int64_t)role);
            if (role_q.step()) same_role_ids.insert((u32)role_q.i(0));
        }
    }
    auto next = thresholds(m);
    Value map = Value::object();
    for (u32 same_role_id : same_role_ids) {
        u32 max = max_level(m, now, same_role_id);
        if (!max) continue;  // (a) no schedule: no favor
        State state = load(st, same_role_id);
        map[std::to_string(same_role_id)] = element(m, now, same_role_id, state, rules::level(state.point, next, max));
    }
    data["PlayerCharacterFavorMap"] = map;
    // (a) master_global.favor_tap_bonus_limit taps per character per day; (d) the load reports the
    // home character's remaining count (the client keeps one number, CParameterManager +0xb660,
    // and checks it for the home character's tap, CHome::IsAddFavorPointByTap (b)).
    u32 limit = global_u32(m, "favor_tap_bonus_limit", 5);
    u32 used = home_same_role_id ? taps_today(m, load(st, home_same_role_id), now) : 0;
    data["RemainingUpdateFavorCountByTap"] = limit > used ? limit - used : 0u;
    // (a) master_global.favor_event_drop_bonus_limit less today's uses (the event drop bonus above)
    data["RemainingEventDropBonusCountByFavor"] = event_drop_remaining(st, m, now);
    LOGI("server", "favor: %zu characters in PlayerCharacterFavorMap", map.map.size());
}

Value mission_gain(sqlite3* st, sqlite3* m, int64_t now, u32 same_role_id, u32 stamina, double rate) {
    // (a) master_favor_battle_effect: favor_up_point for the mission's use_stamina, play_type 0
    // (single play; 1 = multiplay host, 2 = guest). (d) a stamina with no row gives the row of
    // the largest use_stamina below it.
    u32 points = 0;
    {
        Q q(m,
            "select favor_up_point from master_favor_battle_effect where play_type = 0 and use_stamina <= ? "
            "order by use_stamina desc limit 1");
        q.bind(1, (int64_t)stamina);
        if (q.step()) points = (u32)q.i(0);
    }
    // (a)+(b) a running type-8 campaign (友好, ×1.5) multiplies the battle favor (api/missions/
    // mission_end.cpp); (d) truncated
    if (rate != 1.0) points = (u32)((double)points * rate);
    Gain gain = add_points(st, m, now, same_role_id, points);
    if (!gain.ok) return Value();
    Value result = Value::object();
    result["id"] = same_role_id;
    result["master_role_same_role_id"] = same_role_id;
    result["before_favor_level"] = gain.level_before;
    result["before_favor_point"] = gain.before.point;
    result["after_favor_level"] = gain.level_after;
    result["after_favor_point"] = gain.after.point;
    result["added_event_drop_at"] = gain.after.event_drop_at;
    // read by port/scripts/restore_favor_session.sh ("favor: mission (stamina N) same_role")
    LOGI("server", "favor: mission (stamina %u) same_role %u +%u: %u -> %u (level %u -> %u)", stamina, same_role_id, points, gain.before.point,
         gain.after.point, gain.level_before, gain.level_after);
    return result;
}

void tap(sqlite3* st, sqlite3* m, int64_t now, u32 same_role_id, Value& data) {
    u32 limit = global_u32(m, "favor_tap_bonus_limit", 5);  // (a) 5 a day
    u32 points = global_u32(m, "favor_tap_bonus_point", 50);  // (a) 50 points a tap
    State state = load(st, same_role_id);
    u32 used = taps_today(m, state, now);
    Value result = Value::object();
    result["same_role_id"] = same_role_id;
    if (used < limit && max_level(m, now, same_role_id)) {
        Gain gain = add_points(st, m, now, same_role_id, points);
        gain.after.taps = used + 1;
        gain.after.tapped_at = now;
        save(st, same_role_id, gain.after);
        used++;
        result["favor_level"] = gain.level_after;
        result["favor_point"] = gain.after.point;
        // read by port/scripts/restore_favor_session.sh ("favor: tap same_role N +50: A -> B (level ...)")
        LOGI("server", "favor: tap same_role %u +%u: %u -> %u (level %u -> %u), %u taps left", same_role_id, points, gain.before.point,
             gain.after.point, gain.level_before, gain.level_after, limit - used);
    } else {
        // (d) past the limit, or a character without favor: nothing changes
        result["favor_level"] = level_of(st, m, now, same_role_id);
        result["favor_point"] = state.point;
    }
    result["RemainingUpdateFavorCountByTap"] = limit > used ? limit - used : 0u;
    data["UpdateFavorByTapResultInfo"] = result;
}

void use_item(sqlite3* st, sqlite3* m, int64_t now, u32 master_item_id, u32 count, u32 same_role_id, Value& data) {
    // (a) master_favor_item_effect: favor_up_point per item; target_type 0 = any character,
    // otherwise only master_role_same_role_id ((d) reading of target_type).
    u32 points_per_item = 0;
    {
        Q q(m, "select favor_up_point, target_type, master_role_same_role_id from master_favor_item_effect where master_item_id = ?");
        q.bind(1, (int64_t)master_item_id);
        if (q.step() && (q.i(1) == 0 || (u32)q.i(2) == same_role_id)) points_per_item = (u32)q.i(0);
    }
    // (d) the count is capped by the stack held; the stack is debited
    u32 have = (u32)one(st, "select count from stock where master_item_id = ?", master_item_id, true);
    count = std::min(count, have);
    Gain gain = add_points(st, m, now, same_role_id, points_per_item * count);
    if (count) {
        Q q(st, "update stock set count = count - ? where master_item_id = ?");
        q.bind(1, (int64_t)count).bind(2, (int64_t)master_item_id);
        q.run();
    }
    Value result = Value::object();
    result["same_role_id"] = same_role_id;
    result["favor_level"] = gain.ok ? gain.level_after : 1u;
    result["favor_point"] = gain.ok ? gain.after.point : 0u;
    data["UseFavorResultInfo"] = result;
    LOGI("server", "favor: item %u x%u on same_role %u: +%u", master_item_id, count, same_role_id, points_per_item * count);
}

}  // namespace soa::server::favor
