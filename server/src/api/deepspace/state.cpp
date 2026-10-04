// Deep space: the areas, the offers, the ships and the values the answers carry (api/deepspace/
// README.md; declared in deepspace.h). Port code, not guest behaviour; every rule carries its
// source label, (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
// Rules in docs/server-rules.md "Deep space".
//
// Response shapes (b), from the client's info classes (port/fakeapi/fields.txt, schema.txt and
// the Initialize functions of the classes):
//   DeepSpaceAreaList      {area id: CDeepSpaceAreaInfo}  master_area_id, current_exp, max_exp,
//                          ship_in_progress_num, ship_complete_num, is_last_play, is_rare_mission,
//                          is_new, DeepSpaceMissionList {mission id: CDeepSpaceMissionInfo}
//   CDeepSpaceMissionInfo  master_mission_id, bonus_set_id, ship_id, closed_at, count_weekly_at,
//                          updated_at, is_new, play_count_daily, play_count_weekly, play_count
//   DeepSpaceActiveShipInfoList / DeepSpaceEndShipInfoList {ship id: CDeepSpaceShipInfo}
//                          ship_id, master_area_id, master_mission_id, bonus_set_id, item_id,
//                          started_at, closed_at
//   characters             {uid: CDeepSpaceCharacterInfo} character_id, ship_id, ship_slot
//   DeepSpaceBonusAllApplyInfoList / UpdateDeepSpaceBonusAllApplyInfoList
//                          {ship id: {bonus id: {bonus: float}}}
//   DeepMissionPlayer      level, exp, stamina, stamina_max, fol, is_level_up, tower_try_count,
//                          time_saving_use_count, stamina_update
// A number map in a response replaces the client's whole map (b: IInfoBaseMap::DeserializeChild
// clears it first), so every response sends the full lists it carries.
#include <string>
#include <vector>

#include "api/deepspace/deepspace.h"
#include "core/time.h"
#include "rules/deepspace_rules.h"
#include "soaserver/hooks.h"

namespace soa::server::deepspace {

namespace dr = rules::deepspace;

// ---- clocks ----------------------------------------------------------------------------------
// open_at (core/time.h): (a) a dated master row's opened_at / closed_at window, tested on the clock
// its argument's type names. The two clocks: deepspace.h.
EventTime calendar(Ctx& ctx) { return ctx.event_now(); }
bool open_by_both_clocks(Ctx& ctx, const std::string& opened_at, const std::string& closed_at) {
    return open_at(opened_at, closed_at, calendar(ctx)) && open_at(opened_at, closed_at, ctx.now());
}

namespace {

// Whether the area's images are on disk (the port's asset lookup: the APKs, then --download-dir).
// The areas the player can open are decided at runtime from the files present, never from a list:
// (d) an area whose image (master_deep_space_area.resource, Image/etc2/<resource>.aif, the name
// the client builds from it) is missing isn't offered. Outside the game (unit tests) there's no
// asset lookup and every area counts as present.
// Not the one asset gate (core/assets.h; server/PLAN-readability.md R6g, decided in R18): this asks
// the AssetIndex (soaserver/hooks.h) for the one exact name and only on a live server, where the
// gate's assets::available() also accepts the texture-quality and assetpack/ variants, follows the
// tests' override (the events and Sphere 211 tests' predicates on BG/ names) and counts every asset
// present when the host has no asset source. On the 3.7.0 data the two agree (the 13 area images
// exist only as Image/etc2/<resource>.aif, in the download), so the choice changes no answer.
bool area_assets(Ctx& ctx, const std::string& resource) {
    if (!ctx.live()) return true;
    if (resource.empty()) return false;
    return asset_index().exists("builtin_data/Image/etc2/" + resource + ".aif");
}

// (a) required_areaN_id / required_exp_rateN: an area with is_required opens when each required
// area's exploration rate (current_exp / max_exp, in percent; b: the client's "探査率") reaches
// the rate. (d) all the listed conditions are needed. (a) opened_at / closed_at by the clock.
// Plus the runtime asset check above.
bool area_unlocked(Ctx& ctx, const Area& area, const std::vector<Area>& all) {
    if (!open_by_both_clocks(ctx, area.opened_at, area.closed_at) || !area_assets(ctx, area.resource)) return false;
    if (!area.required) return true;
    for (auto& [required_id, rate] : area.requirements) {
        u32 max_exp = 0;
        for (auto& other : all)
            if (other.id == required_id) max_exp = other.max_exp;
        if (!max_exp || 100.0 * area_exp(ctx, required_id) / max_exp < rate) return false;
    }
    return true;
}

// The play-limit periods: (d) the offers' play_count_daily restart at the daily reset (04:00),
// play_count_weekly at the week's start (rules::deepspace::week_start). The period starts are kept
// in ds_state (limit_day, limit_week; NULL or no row: none yet, read as 0).
void restart_limit_periods(Ctx& ctx, ServerTime t) {
    ServerTime day = limit_day(ctx, t), week(dr::week_start(day.v));
    if (ctx.st.one_time("select limit_day from ds_state where id = 1", {}) != day) {
        ctx.st.q("update ds_offer set play_count_daily = 0", {});
        ctx.st.q("insert into ds_state (id, limit_day) values (1, ?) on conflict(id) do update set limit_day = excluded.limit_day", {day});
    }
    if (ctx.st.one_time("select limit_week from ds_state where id = 1", {}) != week) {
        ctx.st.q("update ds_offer set play_count_weekly = 0", {});
        ctx.st.q("insert into ds_state (id, limit_week) values (1, ?) on conflict(id) do update set limit_week = excluded.limit_week", {week});
    }
}

// (a) master_deep_space_mission rows: normal missions have no rare_type_id; (d) every normal
// mission of an opened area open by the clock is always offered.
void offer_normal_missions(Ctx& ctx, const Area& area, ServerTime t) {
    ctx.m.q(
        "select id, bonus_set_type_id, opened_at, closed_at from master_deep_space_mission where master_deep_area_id = ? and "
        "ifnull(rare_type_id, 0) = 0 order by order_id",
        {area.id}, [&](const Row& mission_row) {
            if (!open_by_both_clocks(ctx, mission_row.s("opened_at"), mission_row.s("closed_at"))) return;
            if (ctx.st.one("select count(*) from ds_offer where mission_id = ?", {mission_row.i("id")})) return;
            ctx.st.q("insert into ds_offer (mission_id, area_id, bonus_set_id, updated_at) values (?,?,?,?)",  // closed_at NULL: no limit
                     {mission_row.i("id"), area.id, roll_bonus_set(ctx, (u32)mission_row.i("bonus_set_type_id")), t});
        });
}

// Offers that ran out and aren't on a ship: (a) a rare offer's rare_limit_time, (a) a mission
// whose closed_at passed.
void drop_expired_offers(Ctx& ctx, ServerTime t) {
    std::vector<u32> gone;
    ctx.st.q("select mission_id, closed_at from ds_offer where ship_id is null", {}, [&](const Row& offer_row) {
        const std::optional<ServerTime> closed = offer_row.opt<ServerTime>("closed_at");  // NULL: no limit
        bool open = !(closed && *closed < t);
        ctx.m.q("select opened_at, closed_at from master_deep_space_mission where id = ?", {offer_row.i("mission_id")},
                [&](const Row& mission_row) { open = open && open_by_both_clocks(ctx, mission_row.s("opened_at"), mission_row.s("closed_at")); });
        if (!open) gone.push_back((u32)offer_row.i("mission_id"));
    });
    for (u32 mission_id : gone) ctx.st.q("delete from ds_offer where mission_id = ?", {mission_id});
}

}  // namespace

// ---- areas and offers ------------------------------------------------------------------------
std::vector<Area> areas(Ctx& ctx) {
    std::vector<Area> list;
    ctx.m.q("select * from master_deep_space_area order by order_id", {}, [&](const Row& area_row) {
        Area area;
        area.id = (u32)area_row.i("id");
        area.label = area_row.s("id_label");
        area.resource = area_row.s("resource");
        area.max_exp = (u32)area_row.i("max_exp");
        area.required = area_row.i("is_required") != 0;
        for (int k = 1; k <= 5; k++) {
            std::string area_col = "required_area" + std::to_string(k) + "_id", rate_col = "required_exp_rate" + std::to_string(k);
            if (!area_row.null(area_col.c_str()) && area_row.i(area_col.c_str()))
                area.requirements.emplace_back((u32)area_row.i(area_col.c_str()), area_row.f(rate_col.c_str()));
        }
        area.opened_at = area_row.s("opened_at");
        area.closed_at = area_row.s("closed_at");
        list.push_back(area);
    });
    return list;
}
u32 area_exp(Ctx& ctx, u32 area_id) { return (u32)ctx.st.one("select exp from ds_area where area_id = ?", {area_id}); }

void refresh_offers(Ctx& ctx, ServerTime t) {
    restart_limit_periods(ctx, t);
    auto all = areas(ctx);
    for (auto& area : all) {
        if (!area_unlocked(ctx, area, all)) continue;
        // (d) a newly opened area that needed other areas is flagged is_new once.
        ctx.st.q("insert into ds_area (area_id, exp, is_new) values (?, 0, ?) on conflict(area_id) do nothing", {area.id, area.required ? 1 : 0});
        offer_normal_missions(ctx, area, t);
    }
    drop_expired_offers(ctx, t);
}

// (a) master_deep_space_bonus_set rows of the mission's bonus_set_type_id, open by the clock,
// picked by rate_weigh. (d) one set per offer, rolled when the mission is offered.
u32 roll_bonus_set(Ctx& ctx, u32 set_type) {
    std::vector<u32> ids, weights;
    ctx.m.q("select id, rate_weigh, opened_at, closed_at from master_deep_space_bonus_set where bonus_set_type_id = ? order by order_id, id",
            {set_type}, [&](const Row& set_row) {
                if (!open_at(set_row.s("opened_at"), set_row.s("closed_at"), calendar(ctx)) || set_row.i("rate_weigh") <= 0) return;
                ids.push_back((u32)set_row.i("id"));
                weights.push_back((u32)set_row.i("rate_weigh"));
            });
    u64 sum = 0;
    for (u32 w : weights) sum += w;
    if (!sum) return 0;
    return ids[rules::weighted_pick(weights, (*ctx.rng)() % sum)];
}

ServerTime limit_day(Ctx& ctx, ServerTime t) { return day_start(t, (int)ctx.global_u32("login_bonus_reset_hour", 4)); }

// rules::deepspace::limit_reached with (a) the mission's limit_type / limit_count.
bool at_limit(Ctx& ctx, const Row& offer_row) {
    bool hit = false;
    ctx.m.q("select limit_type, limit_count from master_deep_space_mission where id = ?", {offer_row.i("mission_id")}, [&](const Row& mission_row) {
        int limit_type = mission_row.null("limit_type") ? 0 : (int)mission_row.i("limit_type");
        u32 limit_count = mission_row.null("limit_count") ? 0 : (u32)mission_row.i("limit_count");
        hit = dr::limit_reached(limit_type, limit_count, (u32)offer_row.i("play_count_daily"), (u32)offer_row.i("play_count_weekly"));
    });
    return hit;
}

// ---- ships -------------------------------------------------------------------------------------
// (b) CUIUtility::GetMaxShipCount: the master_deep_space_ship rows with use_type 1 open by the
// clock whose required_num the player's total limit-break count reaches. (d) the ships are
// numbered 1..that count.
// Subscription ships (b): with the pass's type 3 on (CParameterUtility::EnableSubscriptionType(3),
// the `Subscription` state; api/shop/subscription.cpp) the client adds master_global
// subscription_deepspace_ship (2, (a)) ships: CDeepSpace::Setup reads it into CDeepSpace+0x3f0,
// SetupAfterConnection adds it to the count shown, GetUnusedShipCount (GetMaxShipCount(.., true))
// to the ships it lets depart. They are numbered after the limit-break ships (d). (a) the pass's
// text (subscmsg_gpass_deepspace_manual): when it runs out while a ship is out, the ship still
// comes back (MissionEnd doesn't look at the count) but can't depart again.
// Coin ships (use_type 2) and the use_type 3 rows: (b) no client code reads them (the only query
// of master_deep_space_ship is GetMaxShipCount's "WHERE use_type=?" with 1, in 3.7.0 and the offline build),
// and no client API buys a ship (CDeepSpaceShipIncrementDialog only tells that the limit-break
// count opened a ship), so they aren't counted: a server-side coin ship would be one the client
// never lets depart.
namespace {
constexpr int kShipUseLimitBreak = 1;           // (b) master_deep_space_ship.use_type GetMaxShipCount counts
constexpr u32 kSubscriptionTypeDeepSpace = 3;  // (b) EnableSubscriptionType(3): the pass's ships
u32 limit_break_ships(Ctx& ctx, ServerTime t) {
    u32 limit_breaks = (u32)ctx.st.one("select ifnull(sum(limit_break), 0) from roster", {});
    u32 ships = 0;
    ctx.m.q("select required_num, opened_at, closed_at from master_deep_space_ship where use_type = ?", {kShipUseLimitBreak},
            [&](const Row& ship_row) {
                if (open_at(ship_row.s("opened_at"), ship_row.s("closed_at"), t) && (u32)ship_row.i("required_num") <= limit_breaks) ships++;
            });
    return ships;
}
}  // namespace
u32 subscription_ships(Ctx& ctx, ServerTime t) {
    return ext::subscription_active(ctx, kSubscriptionTypeDeepSpace, t) ? ctx.global_u32("subscription_deepspace_ship", 2) : 0;
}
u32 max_ships(Ctx& ctx, ServerTime t) { return limit_break_ships(ctx, t) + subscription_ships(ctx, t); }

std::vector<CharacterUid> ship_members(Ctx& ctx, u32 ship_id) {
    std::vector<CharacterUid> members;
    ctx.st.q("select uid from ds_ship_member where ship_id = ? order by slot", {ship_id},
             [&](const Row& member_row) { members.push_back(member_row.id<CharacterUid>("uid")); });
    return members;
}

// Quick returns used today: (d) a day from master_global login_bonus_reset_hour (4:00), like the
// other daily counters. Kept in the player row (time_saving_count, time_saving_day; Player.time_saving_use_count reads it).
u32 time_saving_count(Ctx& ctx, ServerTime t) {
    ServerTime day = day_start(t, (int)ctx.global_u32("login_bonus_reset_hour", 4));
    ServerTime counted_day = ctx.st.one_time("select time_saving_day from player", {});  // NULL: never counted (0)
    if (counted_day != day) ctx.st.q("update player set time_saving_day = ?, time_saving_count = 0", {day});
    return (u32)ctx.st.one("select time_saving_count from player", {});
}

// ---- the answers' values -----------------------------------------------------------------------
namespace {
// CDeepSpaceMissionInfo of an offer (a ds_offer row).
Value mission_info(Ctx& ctx, const Row& offer_row) {
    Value info = Value::object();
    info["master_mission_id"] = (u32)offer_row.i("mission_id");
    info["bonus_set_id"] = (u32)offer_row.i("bonus_set_id");
    info["ship_id"] = (u32)offer_row.i("ship_id");  // NULL (not on a ship): 0
    const std::optional<ServerTime> closed = offer_row.opt<ServerTime>("closed_at");
    info["closed_at"] = closed ? ctx.fmt_time(*closed) : std::string("");  // (b) "" = no limit
    // (d) the start of the week the weekly count runs in (rules::deepspace::week_start), for a
    // mission with a weekly limit; "" otherwise (all of the 3.7.0 data).
    int limit_type = (int)ctx.m.one("select ifnull(limit_type, 0) from master_deep_space_mission where id = ?", {offer_row.i("mission_id")});
    info["count_weekly_at"] = limit_type == (int)dr::LimitType::kWeekly ? ctx.fmt_time(dr::week_start(limit_day(ctx, ctx.now()).v)) : std::string("");
    // NULL (never: only a row from before PLAN-schema S10 can lack it) formats as the time 0, as
    // its 0 did
    info["updated_at"] = ctx.fmt_time(offer_row.opt<ServerTime>("updated_at").value_or(ServerTime(0)));
    info["is_new"] = offer_row.i("is_new") != 0;
    info["play_count_daily"] = (u32)offer_row.i("play_count_daily");
    info["play_count_weekly"] = (u32)offer_row.i("play_count_weekly");
    info["play_count"] = (u32)offer_row.i("play_count");
    return info;
}
}  // namespace

Value area_info(Ctx& ctx, const Area& area, ServerTime t) {
    Value info = Value::object();
    info["master_area_id"] = area.id;
    info["current_exp"] = area_exp(ctx, area.id);
    info["max_exp"] = area.max_exp;
    // (d) ships of the area still out / back and waiting to be collected
    info["ship_in_progress_num"] = (u32)ctx.st.one("select count(*) from ds_ship where area_id = ? and closed_at > ?", {area.id, t});
    info["ship_complete_num"] = (u32)ctx.st.one("select count(*) from ds_ship where area_id = ? and closed_at <= ?", {area.id, t});
    info["is_last_play"] = ctx.st.one("select is_last_play from ds_area where area_id = ?", {area.id}) != 0;
    info["is_rare_mission"] =
        ctx.st.one("select count(*) from ds_offer where area_id = ? and closed_at is not null and ship_id is null", {area.id}) != 0;
    info["is_new"] = ctx.st.one("select is_new from ds_area where area_id = ?", {area.id}) != 0;
    Value missions = Value::object();
    // (d) an offer at its play limit is left out until its period restarts (b: a mission missing
    // from the list isn't shown, GetDeepSpaceMissionList), unless it is on a ship.
    ctx.st.q("select * from ds_offer where area_id = ? order by mission_id", {area.id}, [&](const Row& offer_row) {
        if (offer_row.null("ship_id") && at_limit(ctx, offer_row)) return;
        missions[std::to_string(offer_row.i("mission_id"))] = mission_info(ctx, offer_row);
    });
    info["DeepSpaceMissionList"] = missions;
    return info;
}
void put_area_info(Ctx& ctx, Value& data, u32 area_id, ServerTime t) {
    for (auto& area : areas(ctx))
        if (area.id == area_id) data["DeepSpaceArea"] = area_info(ctx, area, t);
}
Value area_list(Ctx& ctx, ServerTime t) {
    Value list = Value::object();
    auto all = areas(ctx);
    for (auto& area : all)
        if (ctx.st.one("select count(*) from ds_area where area_id = ?", {area.id}) && area_unlocked(ctx, area, all))
            list[std::to_string(area.id)] = area_info(ctx, area, t);
    return list;
}

Value ship_info(Ctx& ctx, const Row& ship_row) {
    Value info = Value::object();
    info["ship_id"] = (u32)ship_row.i("ship_id");
    info["master_area_id"] = (u32)ship_row.i("area_id");
    info["master_mission_id"] = (u32)ship_row.i("mission_id");
    info["bonus_set_id"] = (u32)ship_row.i("bonus_set_id");
    info["item_id"] = (u32)ship_row.i("item_id");
    info["started_at"] = ctx.fmt_time(ship_row.time("started_at"));
    info["closed_at"] = ctx.fmt_time(ship_row.time("closed_at"));
    return info;
}
// (b) CUIUtility::GetUnusedShipCount counts both maps: a ship is busy until MissionEnd collects
// it. Active = still out, End = back (closed_at reached) and waiting for MissionEnd.
Value ship_list(Ctx& ctx, ServerTime t, bool ended) {
    Value list = Value::object();
    ctx.st.q(std::string("select * from ds_ship where closed_at ") + (ended ? "<= ?" : "> ?") + " order by ship_id", {t},
             [&](const Row& ship_row) { list[std::to_string(ship_row.i("ship_id"))] = ship_info(ctx, ship_row); });
    return list;
}
Value ship_info_of(Ctx& ctx, u32 ship_id) {
    Value info;
    ctx.st.q("select * from ds_ship where ship_id = ?", {ship_id}, [&](const Row& ship_row) { info = ship_info(ctx, ship_row); });
    return info;
}

Value character_map(Ctx& ctx) {
    Value map = Value::object();
    ctx.st.q("select ship_id, slot, uid from ds_ship_member order by ship_id, slot", {}, [&](const Row& member_row) {
        const CharacterUid uid = member_row.id<CharacterUid>("uid");
        Value info = Value::object();
        info["character_id"] = uid.v;
        info["ship_id"] = (u32)member_row.i("ship_id");
        info["ship_slot"] = (u32)member_row.i("slot");  // (b) 1..8 (CDeepSpaceProgressDialog::Open looks up slots 1..8)
        map[std::to_string(uid.v)] = info;
    });
    return map;
}

Value bonus_apply_list(Ctx& ctx, int64_t only_ship) {
    Value list = Value::object();
    ctx.st.q("select ship_id, bonus_id, value from ds_bonus order by ship_id, bonus_id", {}, [&](const Row& bonus_row) {
        if (only_ship >= 0 && bonus_row.i("ship_id") != only_ship) return;
        std::string ship_key = std::to_string(bonus_row.i("ship_id"));
        if (!list.find(ship_key)) list[ship_key] = Value::object();
        Value entry = Value::object();
        entry["bonus"] = bonus_row.f("value");
        list[ship_key][std::to_string(bonus_row.i("bonus_id"))] = entry;
    });
    return list;
}

// DeepMissionPlayer (b: DeepMissionEndResultPlayerInfo; the MissionEnd handler copies it into
// the player, time_saving_use_count included).
Value deep_mission_player(Ctx& ctx, ServerTime t, bool level_up) {
    Value player = Value::object();
    ctx.st.q("select * from player", {}, [&](const Row& player_row) {
        player["level"] = (u32)player_row.i("level");
        player["exp"] = (u32)player_row.i("exp");
        player["stamina"] = (u32)player_row.i("stamina");
        player["stamina_max"] = ctx.stamina_max((u32)player_row.i("level"));
        player["fol"] = (u32)player_row.i("fol");
        player["is_level_up"] = level_up;
        player["tower_try_count"] = 0u;  // (d) deep space has no tower tries
        player["time_saving_use_count"] = time_saving_count(ctx, t);
        player["stamina_update"] = ctx.fmt_time(player_row.time("stamina_at"));
    });
    return player;
}

}  // namespace soa::server::deepspace
