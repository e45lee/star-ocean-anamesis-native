// World bosses, big hunts and time bonuses: GetWorldBossInfo over master_world_boss /
// master_world_boss_wave, played single-player; the time-bonus drops of master_time_bonus on
// event-mission results. Port code, not guest behaviour. Rules in docs/server-rules.md "World
// bosses and big hunts", "Time bonus"; labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// Shape (b, CEventMissionBoard / CWorldBossDetailDialog / MissionUtility / ResultUtility):
//  - an event area with event_type 1 names a world boss (event_id); while the boss's window is
//    open, a fresh board open sends GetWorldBossInfo(area id) and shows the boss plate: the wave,
//    three collection gauges (num1..3 of the target items against next_required_num), "+N" boxes
//    (add_item1..3_num) and the wave's reward;
//  - CWorldBossPlayerInfoList lists cleared waves; the board opens one clear dialog per entry after
//    GetWorldBossInfo (no grant: the reward is the server's, here a present);
//  - start_bigHunt_area_id names the area of a running big hunt: its is_bighunt missions are listed
//    (GetEventMissionList) and the board counts down to CT_WorldBossInfo.bighunt_closed_at; the
//    cut-in plays when CWorldBossPlayerInfo.is_new_open is set;
//  - WorldBossMissionTimeBonusDropItemInfoList on a MissionEnd shows time-bonus rewards (reward
//    type 4, ds_time_badge); the client never computes them.
// Single player (d): the community totals are the player's own, the wave requirement is the
// master's scaled to one player (kFirstWave).
#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "core/log.h"
#include "api/events/event_extras.h"
#include "soaserver/events.h"
#include "soaserver/ext.h"
#include "core/modules.h"

namespace soa::server {

namespace args {
// GetWorldBossInfo(u32 event_area_id) (b: the argument is master_event_area.id). The module's own
// args struct (core/request_args.h holds the core handlers').
struct GetWorldBossInfoArgs {
    u32 area_id = 0;
    static GetWorldBossInfoArgs from(const Request& req) { return {req.ints.empty() ? 0 : (u32)req.ints[0]}; }
};
}  // namespace args

namespace {
using namespace ext;
using event_extras::kMissionTypeEvent;

// (a)+(b) master_event_area.event_type 1: the area's event_id is a master_world_boss row.
constexpr int64_t kEventTypeWorldBoss = 1;

// (d) one player's share of a wave: the master's requirement (sized for the whole player base)
// scaled so the boss's first wave needs kFirstWave of each target item (about three to five wins of
// the missions dropping it: they drop 150..650 per lot); later waves keep the master's proportions
// to the first (hotspring: wave 1 3,100,000 -> 1,500, wave 2 5,780,000 -> 2,797).
constexpr u64 kFirstWave = 1500;

struct Boss {
    u32 id = 0, items[3] = {0, 0, 0};
    u32 bonus_rate = 0, bighunt_minutes = 0;
    std::string opened, closed;
};
bool find_boss(Ctx& ctx, u32 id, Boss& boss) {
    bool ok = false;
    ctx.m.q("select * from master_world_boss where id = ?", {id}, [&](const Row& row) {
        ok = true;
        boss.id = id;
        boss.items[0] = (u32)row.i("target_item1_id");
        boss.items[1] = (u32)row.i("target_item2_id");
        boss.items[2] = (u32)row.i("target_item3_id");
        boss.bonus_rate = (u32)row.i("bonus_rate");
        boss.bighunt_minutes = (u32)row.i("bighunt_time");
        boss.opened = row.s("opened_at");
        boss.closed = row.s("closed_at");
    });
    return ok;
}
// (a)+(b) the boss of an event area: event_type 1 and event_id a master_world_boss row, open while
// its window, moved by the calendar's whole years as the event module moves it in the client's
// copy (events::client_years / window_open), covers the clock.
bool area_boss(Ctx& ctx, u32 area, Boss& boss) {
    u32 id = 0;
    ctx.m.q("select event_type, event_id from master_event_area where id = ?", {area}, [&](const Row& row) {
        if (row.i("event_type") == kEventTypeWorldBoss) id = (u32)row.i("event_id");
    });
    if (!id || !find_boss(ctx, id, boss)) return false;
    return events::window_open(boss.opened, boss.closed, events::client_years(ctx), ctx.now());
}

struct Wave {
    bool found = false;
    u32 wave = 0, estimated = 0, fast_rate = 0, slow_rate = 0, type = 0, id = 0, num = 0;
    u64 fast = 0, base = 0, slow = 0;
    std::string message;
};
Wave wave_of(Ctx& ctx, u32 boss, u32 wave) {
    Wave info;
    ctx.m.q("select * from master_world_boss_wave where world_boss_event_id = ? and wave = ?", {boss, wave}, [&](const Row& row) {
        info.found = true;
        info.wave = wave;
        info.estimated = (u32)row.i("estimated_clear_time");
        info.fast_rate = (u32)row.i("fast_rate");
        info.slow_rate = (u32)row.i("slow_rate");
        info.fast = (u64)row.i("fast_required_num");
        info.base = (u64)row.i("base_required_num");
        info.slow = (u64)row.i("slow_required_num");
        info.type = (u32)row.i("content_type");
        info.id = (u32)row.i("content_id");
        info.num = (u32)row.i("content_num");
        info.message = row.s("present_message_id");
    });
    return info;
}
// (a) the wave's requirement: fast_required_num when the previous wave cleared within fast_rate % of
// its estimated_clear_time (minutes), slow_required_num beyond slow_rate %, else base (d: that
// reading of the columns, on the player's own clear times); (d) one player's share.
u64 requirement(const Wave& info, const Wave& prev, int64_t last_clear_secs, u64 first_base) {
    u64 need = info.base;
    if (prev.found && last_clear_secs > 0 && prev.estimated) {
        int64_t est = (int64_t)prev.estimated * 60;
        if (last_clear_secs * 100 <= est * prev.fast_rate) need = info.fast;
        else if (last_clear_secs * 100 >= est * prev.slow_rate) need = info.slow;
    }
    if (!first_base) first_base = std::max<u64>(1, info.base);
    return std::max<u64>(1, (u64)(((unsigned __int128)need * kFirstWave + first_base - 1) / first_base));
}

struct State {
    u32 area = 0, wave = 1;
    u64 n[3] = {0, 0, 0}, a[3] = {0, 0, 0}, required = 0;
    ServerTime started;      // the wave's start
    int64_t last_clear = 0;  // the last wave's duration (seconds)
    std::optional<ServerTime> hunt_until;  // the big hunt's end; none: no big hunt (NULL; 0 before PLAN-schema S10)
    bool hunt_new = false;
};
State load(Ctx& ctx, const Boss& boss, u32 area) {
    State state;
    bool have = false;
    ctx.st.q("select * from wboss where boss_id = ?", {boss.id}, [&](const Row& row) {
        have = true;
        state.area = (u32)row.i("area_id");
        state.wave = (u32)row.i("wave");
        state.n[0] = (u64)row.i("n1"), state.n[1] = (u64)row.i("n2"), state.n[2] = (u64)row.i("n3");
        state.a[0] = (u64)row.i("a1"), state.a[1] = (u64)row.i("a2"), state.a[2] = (u64)row.i("a3");
        state.required = (u64)row.i("required");
        state.started = row.time("wave_started_at");
        state.last_clear = row.i("last_clear_secs");
        state.hunt_until = row.opt<ServerTime>("hunt_until");
        state.hunt_new = row.i("hunt_new") != 0;
    });
    if (!have) {  // (d) the first meeting starts wave 1
        state.area = area;
        state.started = ctx.now();
        Wave first = wave_of(ctx, boss.id, 1);
        state.required = requirement(first, Wave{}, 0, first.base);
    }
    if (area) state.area = area;
    return state;
}
void save(Ctx& ctx, const Boss& boss, const State& state) {
    ctx.st.q(
        "insert into wboss (boss_id, area_id, wave, n1, n2, n3, a1, a2, a3, required, wave_started_at, last_clear_secs, hunt_until, "
        "hunt_new) values (?,?,?,?,?,?,?,?,?,?,?,?,?,?)"
        " on conflict(boss_id) do update set area_id = excluded.area_id, wave = excluded.wave, "
        "n1 = excluded.n1, n2 = excluded.n2, n3 = excluded.n3, a1 = excluded.a1, a2 = excluded.a2, "
        "a3 = excluded.a3, required = excluded.required, wave_started_at = excluded.wave_started_at, "
        "last_clear_secs = excluded.last_clear_secs, hunt_until = excluded.hunt_until, "
        "hunt_new = excluded.hunt_new",
        {boss.id, state.area, state.wave, state.n[0], state.n[1], state.n[2], state.a[0], state.a[1], state.a[2], state.required, state.started,
         state.last_clear, state.hunt_until, state.hunt_new ? 1 : 0});
}
bool hunting(Ctx& ctx, const State& state) { return state.hunt_until && ctx.now() <= *state.hunt_until; }

// Adds the player's target items to the gauges; a wave whose three gauges are full clears: (d) its
// reward goes to the present box (master_world_boss_wave content, present_message_id's text), a big
// hunt of bighunt_time minutes (a) starts in the boss's area, the next wave (a: its row) starts
// from empty gauges; past the last row the last wave stays, full.
void contribute(Ctx& ctx, const Boss& boss, State& state, const u64 add[3]) {
    for (int k = 0; k < 3; k++) {
        state.n[k] += add[k];
        state.a[k] = add[k];
    }
    while (state.n[0] >= state.required && state.n[1] >= state.required && state.n[2] >= state.required) {
        Wave info = wave_of(ctx, boss.id, state.wave);
        if (!info.found) break;
        if (ctx.st.one("select count(*) from wboss_clear where boss_id = ? and wave = ?", {boss.id, state.wave})) break;  // the last wave, done
        ctx.st.q("insert into wboss_clear (boss_id, wave, cleared_at, notified) values (?,?,?,0)", {boss.id, state.wave, ctx.now()});
        if (info.type) add_present(ctx, info.type, info.id, std::max<u32>(1, info.num), kPresentMissionClear, 0, text(ctx.m, info.message));
        state.hunt_until = ctx.now() + (int64_t)boss.bighunt_minutes * 60;
        state.hunt_new = true;
        state.last_clear = ctx.now() - state.started;
        LOGI("server", "world boss %u: wave %u cleared (%lld s); big hunt in area %u until %s", boss.id, state.wave, (long long)state.last_clear,
             state.area, ctx.fmt_time(*state.hunt_until).c_str());
        Wave next = wave_of(ctx, boss.id, state.wave + 1);
        if (!next.found) break;
        state.wave++;
        state.started = ctx.now();
        for (int k = 0; k < 3; k++) state.n[k] = 0;  // (d) no carry-over
        state.required = requirement(next, info, state.last_clear, wave_of(ctx, boss.id, 1).base);
    }
}

// The plate: CWorldBossInfo (community gauges; here the player's), CT_WorldBossInfo (the wave's
// requirement, big hunt window) (b: field names from their Initialize).
void put_boss(Ctx& ctx, const Boss& boss, const State& state, Value& data, bool with_list) {
    Value info = Value::object();
    info["world_boss_id"] = boss.id;
    for (int k = 0; k < 3; k++) {
        std::string n = std::to_string(k + 1);
        info["master_item_id" + n] = boss.items[k];
        info["num" + n] = state.n[k];
    }
    info["wave"] = state.wave;
    data["CWorldBossInfo"] = info;
    Value timing = Value::object();
    timing["world_boss_id"] = boss.id;
    timing["wave"] = state.wave;
    timing["wave_started_at"] = ctx.fmt_time(state.started);
    timing["wave_clear_time"] = (u32)std::max<int64_t>(0, state.last_clear);
    bool hunt = hunting(ctx, state);
    timing["bighunt_started_at"] = hunt ? ctx.fmt_time(*state.hunt_until - (int64_t)boss.bighunt_minutes * 60) : std::string("");
    // (b) the board counts down to it (client clock = the server clock)
    timing["bighunt_closed_at"] = hunt ? ctx.fmt_time(*state.hunt_until) : std::string("");
    timing["next_required_num"] = state.required;
    for (int k = 0; k < 3; k++) timing["add_item" + std::to_string(k + 1) + "_num"] = (u32)state.a[k];  // (d) the last win's share
    data["CT_WorldBossInfo"] = timing;
    Value player_info = info;
    player_info["is_received"] = false;  // (b) the detail dialog adds it to the wave: never
    player_info["is_notified"] = true;
    player_info["is_new_open"] = with_list && hunt && state.hunt_new;  // (b) the cut-in, once
    data["CWorldBossPlayerInfo"] = player_info;
    data["start_bigHunt_area_id"] = hunt ? state.area : 0u;
    if (with_list) {
        // (b) one clear dialog per entry after GetWorldBossInfo; the map persists in the client, so
        // (d) each clear is listed once and the key is always sent.
        Value list = Value::object();
        ctx.st.q("select wave from wboss_clear where boss_id = ? and notified = 0 order by wave", {boss.id}, [&](const Row& row) {
            Value entry = info;
            entry["wave"] = (u32)row.i("wave");
            entry["is_received"] = true;
            entry["is_notified"] = false;
            entry["is_new_open"] = false;
            list[std::to_string(row.i("wave"))] = entry;
        });
        ctx.st.q("update wboss_clear set notified = 1 where boss_id = ?", {boss.id});
        data["CWorldBossPlayerInfoList"] = list;
    }
}
// The running big hunt's area over every boss (0 when none): start_bigHunt_area_id. (A boss
// without one has hunt_until NULL, which no time passes.)
u32 hunt_area(Ctx& ctx) {
    u32 area = 0;
    ctx.st.q("select area_id, hunt_until from wboss where hunt_until >= ?", {ctx.now()}, [&](const Row& row) { area = (u32)row.i("area_id"); });
    return area;
}

// GetWorldBossInfo(u32 event_area_id) -> GetWorldBossInfoRes            fid 86d6a220
// API: docs/api.md#getworldbossinfo   Rules: docs/server-rules.md "World bosses and big hunts"
//
// The boss plate of an event board (CEventMissionBoard::Progress sends it on a fresh board open).
//   (a)+(d) the area's boss (event_type 1) while its window, moved by the year shift, covers the
//       clock; else (b) world_boss_id 0: no plate, a plain event board (the previous boss's data
//       is replaced).
//   (d) single player: the gauges are the player's own; the first meeting starts wave 1.
//   (b) CWorldBossPlayerInfoList: one clear dialog per entry, (d) each clear listed once; the
//       cut-in (is_new_open) once.
// Answers: the player state with CWorldBossInfo, CT_WorldBossInfo, CWorldBossPlayerInfo,
// CWorldBossPlayerInfoList and start_bigHunt_area_id.
std::vector<u8> get_world_boss_info(Ctx& ctx, const Request& req) {
    const auto args = args::GetWorldBossInfoArgs::from(req);
    u32 area = args.area_id;
    Value data = ctx.base_data();
    Boss boss;
    if (!area_boss(ctx, area, boss)) {
        Value no_boss = Value::object();
        no_boss["world_boss_id"] = 0u;
        data["CWorldBossInfo"] = no_boss;
        data["CT_WorldBossInfo"] = no_boss;
        data["CWorldBossPlayerInfoList"] = Value::object();
        data["start_bigHunt_area_id"] = hunt_area(ctx);
        return body(data);
    }
    State state = load(ctx, boss, area);
    put_boss(ctx, boss, state, data, true);
    state.hunt_new = false;
    save(ctx, boss, state);
    LOGI("server", "GetWorldBossInfo area %u: boss %u wave %u, %llu/%llu/%llu of %llu%s", area, boss.id, state.wave, (unsigned long long)state.n[0],
         (unsigned long long)state.n[1], (unsigned long long)state.n[2], (unsigned long long)state.required, hunting(ctx, state) ? ", big hunt" : "");
    return body(data);
}

// AreaExtra hook (each listed event area's CAreaInfo, events::add_area_extra).
// Rules: docs/server-rules.md "World bosses and big hunts"
//   (d) the event list's CAreaInfo.is_start_bighunt follows start_bigHunt_area_id (b: the client
//       reads the latter; the flag is kept consistent).
// Sets: is_start_bighunt of the big hunt's area.
void big_hunt_area_extra(Ctx& ctx, u32 area, Value& info) {
    u32 hunt = hunt_area(ctx);
    if (hunt && hunt == area) info["is_start_bighunt"] = true;
}

// OnPlayerLoad hook (Login, GetPlayer, NoLoginStart's full player state).
// Rules: docs/server-rules.md "World bosses and big hunts"
//   (b) the area list and the mission list read start_bigHunt_area_id from any response.
// Adds: start_bigHunt_area_id (the running big hunt's area, 0 when none).
void load_world_boss(Ctx& ctx, const Request&, Value& data) { data["start_bigHunt_area_id"] = hunt_area(ctx); }

// MissionStartExtra hook (MissionStart).
// Rules: docs/server-rules.md "World bosses and big hunts"
//   (b) start_bigHunt_area_id from any response; (b) back on the board the cached
//       CWorldBossPlayerInfo would replay the cut-in, so (d) a boss area's start sends is_new_open
//       false.
// Adds: start_bigHunt_area_id; CWorldBossPlayerInfo {world_boss_id, is_new_open} for a boss area.
void world_boss_mission_start(Ctx& ctx, const MissionInfo& mission, Value&, Value& data) {
    data["start_bigHunt_area_id"] = hunt_area(ctx);
    Boss boss;
    if (mission.type == kMissionTypeEvent && area_boss(ctx, mission.area, boss)) {
        Value player_info = Value::object();
        player_info["world_boss_id"] = boss.id;
        player_info["is_new_open"] = false;
        data["CWorldBossPlayerInfo"] = player_info;
    }
}

// Time bonus (a: master_event_mission.time_bonus_type_id -> master_time_bonus rows, `time` in
// seconds, b: CWorldBossConditionDialog prints it %u:%02u): (d) every row whose time the win's
// mission_time (ms) is within; granted, and listed in WorldBossMissionTimeBonusDropItemInfoList
// (b: {id, content_type, num}, shown with the time badge).
void time_bonus(Ctx& ctx, const MissionInfo& mission, Value& data) {
    if (mission.type != kMissionTypeEvent || !mission.mission_time) return;
    int64_t type = ctx.m.one("select time_bonus_type_id from master_event_mission where id = ?", {mission.mission}, 0);
    if (!type) return;
    Value list = Value::array();
    Value items = Value::array(), stocks = Value::array(), characters = Value::array();
    ctx.m.q("select * from master_time_bonus where type_id = ? order by order_id", {type}, [&](const Row& bonus_row) {
        if ((u64)mission.mission_time > (u64)bonus_row.i("time") * 1000) return;
        u32 content_type = (u32)bonus_row.i("content_type"), id = (u32)bonus_row.i("content_id");
        u32 num = (u32)std::max<int64_t>(1, bonus_row.i("content_num"));
        ctx.grant(content_type, id, num, items, stocks, characters);
        Value entry = Value::object();
        entry["id"] = id;
        entry["content_type"] = content_type;
        entry["num"] = num;
        list.push(entry);
    });
    if (list.arr.empty()) return;
    data["WorldBossMissionTimeBonusDropItemInfoList"] = list;
    if (!items.arr.empty()) {
        Value& add_item = data["AddItem"];
        if (add_item.type != Value::Arr) add_item = Value::array();
        for (auto& item : items.arr) add_item.push(item);
    }
    data["StockItem"] = ctx.stock();
    LOGI("server", "MissionEnd mission %u: %zu time bonuses (%u ms)", mission.mission, list.arr.size(), mission.mission_time);
}

// The target items a result brought (DropList stack items and the time bonuses).
void target_items(const Boss& boss, const Value& data, u64 out[3]) {
    auto count = [&](const Value* list, const char* num_key) {
        if (!list) return;
        for (const Value& entry : list->arr) {
            const Value* id = entry.find("id");
            const Value* num = entry.find(num_key);
            if (!id || !num) continue;
            for (int k = 0; k < 3; k++)
                if (boss.items[k] && id->u == boss.items[k]) out[k] += num->u;
        }
    };
    if (const Value* drop_list = data.find("DropList")) count(drop_list->find("stock_item"), "num");
    count(data.find("WorldBossMissionTimeBonusDropItemInfoList"), "num");
}

// MissionResultExtra hook (a won MissionEnd), in a fixed order: the favor drops
// (favor_drop.cpp), the time bonuses, then the world boss (event_extras.h).
// Rules: docs/server-rules.md "World bosses and big hunts", "Time bonus", "Favor event drop bonus"
//   (a)+(d) the target items the win brought fill the gauges (contribute), (a) bonus_rate % more
//       during a big hunt (d: on the contribution); a full wave clears (its reward a present).
// Adds: (the favor drop's and the time bonus's keys), start_bigHunt_area_id, and for a boss area
// CWorldBossInfo, CT_WorldBossInfo, CWorldBossPlayerInfo.
void world_boss_mission_result(Ctx& ctx, const MissionInfo& mission, Value& data) {
    event_extras::favor_result(ctx, mission, data);
    time_bonus(ctx, mission, data);
    data["start_bigHunt_area_id"] = hunt_area(ctx);
    Boss boss;
    if (mission.type != kMissionTypeEvent || !area_boss(ctx, mission.area, boss)) return;
    State state = load(ctx, boss, mission.area);
    u64 add[3] = {0, 0, 0};
    target_items(boss, data, add);
    if (hunting(ctx, state))
        for (u64& x : add) x = x * (100 + boss.bonus_rate) / 100;
    contribute(ctx, boss, state, add);
    put_boss(ctx, boss, state, data, false);
    save(ctx, boss, state);
    LOGI("server", "world boss %u: +%llu/%llu/%llu -> wave %u %llu/%llu/%llu of %llu", boss.id, (unsigned long long)add[0],
         (unsigned long long)add[1], (unsigned long long)add[2], state.wave, (unsigned long long)state.n[0], (unsigned long long)state.n[1],
         (unsigned long long)state.n[2], (unsigned long long)state.required);
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_worldboss() {
    using namespace ext;
    add_api({"GetWorldBossInfo"}, get_world_boss_info);
    events::add_area_extra(big_hunt_area_extra);
    add_player_load(load_world_boss);
    add_mission_start_extra(world_boss_mission_start);
    add_mission_result_extra(world_boss_mission_result);
}

}  // namespace soa::server
