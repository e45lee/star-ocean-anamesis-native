// The state DB's schema: the migration steps (state/schema.h; server/PLAN-schema.md 3.1, 4.1). Port
// code, not guest behaviour. Nothing else lives here: the steps' SQL and their data mappings.
//
// Step 1 is the baseline: the 58 `create table if not exists` statements the server ran before
// PLAN-schema S1 (the core's Server::schema(), favor::schema, the modules' ext::add_schema and
// soa-server's map_device), verbatim, so on a state written before S1 it creates only what is
// missing, and the stored `sqlite_master.sql` of every table is the text it always was. It then
// adds any baseline column a legacy file lacks (repair_columns): a `create table if not exists`
// never changed an existing table, so a state from before a column was added would miss it.
#include "state/schema.h"

#include <iterator>
#include <set>
#include <string>
#include <vector>

#include "core/log.h"

namespace soa::server::state {

namespace {

// ---- step 1: the baseline (verbatim; the owner each statement came from) -------------------

// The core (core/server.cpp Server::schema()).
const char* const kCore = R"(
create table if not exists meta (key text primary key, value text);
create table if not exists player (id integer primary key, search_id text, name text, level integer, exp integer,
  fol integer, stamina integer, stamina_at integer, free_coin integer, pay_coin integer, home_uid integer,
  party_id integer, created_at integer, last_login_at integer);
create table if not exists roster (uid integer primary key, role_id integer, level integer, exp integer,
  limit_break integer default 0, awaken integer default 0, skill1 integer default 1, skill2 integer default 1,
  skill3 integer default 1, weapon_uid integer default 0, accessory_uid integer default 0, favor integer default 0,
  created_at integer);
create table if not exists items (uid integer primary key, master_item_id integer, item_type integer,
  level integer default 1, exp integer default 0, limit_break integer default 0, locked integer default 0, created_at integer);
create table if not exists stock (master_item_id integer primary key, item_type integer, count integer);
create table if not exists gear (uid integer primary key, master_gear_id integer, data text);
create table if not exists party (party_id integer, slot integer, uid integer, primary key (party_id, slot));
create table if not exists mission (mission_id integer primary key, cleared integer default 0, best_rank integer default 0,
  play_count integer default 0, clear_count integer default 0, first_clear_at integer);
create table if not exists play (id integer primary key check (id = 1), mission_id integer, party_id integer,
  started_at integer, stamina_cost integer, uids text);
create table if not exists gacha_history (id integer primary key autoincrement, gacha_id integer, at integer,
  role_id integer, uid integer, rank text, duplicate integer, cost_free integer, cost_pay integer);
create table if not exists box_gacha (gacha_id integer primary key, box_index integer, reset_count integer, drawn text);
create table if not exists presents (id integer primary key autoincrement, content_type integer, content_id integer,
  num integer, reason_type integer, reason_param integer, created_at integer, received_at integer);
create table if not exists login_bonus (id integer primary key, day integer, last_at integer);
create table if not exists achievements (id integer primary key, progress integer, received_at integer);
create table if not exists planets (label text primary key, open integer);
create table if not exists assist (uid integer primary key, assist_uid integer);
create table if not exists view_flags (kind integer primary key, flags integer);
create table if not exists party_set (party_id integer primary key, icon_id integer default 0, is_lock integer default 0);
create table if not exists party_member (party_id integer, slot integer, weapon_uid integer, accessory_uid integer,
  skill1 integer, skill2 integer, skill3 integer, assist_uid integer, primary key (party_id, slot));
create table if not exists play_ext (id integer primary key check (id = 1), mission_type integer, surprise integer,
  helper_uid integer, helper_kind integer, npc_id integer, campaign_lots integer);
create table if not exists unlocks (mission_id integer primary key, mission_type integer, by_mission integer, at integer);
create table if not exists stepup (head integer primary key, try_count integer, restart_count integer, next_id integer);
create table if not exists box_state (gacha_id integer primary key, total_count integer default 0, reset_count integer default 0);
create table if not exists box_slots (gacha_id integer, slot_id integer, drawn integer, primary key (gacha_id, slot_id));
)";

// Favor per same role (api/favor/favor.cpp; formerly favor::schema).
const char* const kFavor =
    "create table if not exists favor (same_role_id integer primary key, point integer default 0, "
    "tap_count integer default 0, tapped_at integer default 0, event_drop_at text default '')";

// The modules' tables, in their former registration order (core/modules.cpp; each was the module's
// ext::add_schema).

// api/daily/premium_and_favor_bonus.cpp: the premium login-bonus passes and the favor login bonus.
const char* const kDaily =
    "create table if not exists premium_pass (id integer primary key, granted_at integer, day integer default 0, last_at integer default 0);"
    "create table if not exists favor_bonus_state (id integer primary key check (id = 1), day_at integer, bonus_id integer, "
    "lot_uid integer, healed_at integer default 0)";

// api/deepspace/: (d) our layout (PLAN-schema S10): explored areas, the offers with their play
// counts, the ships out or back with their members (uids as "uid,uid,..."), a ship's bonus values,
// every departure.
const char* const kDeepSpace =
    "create table if not exists ds_area (area_id integer primary key, exp integer default 0, is_new integer default 0, "
    "last_play integer default 0);"
    "create table if not exists ds_offer (mission_id integer primary key, area_id integer, bonus_set_id integer, closed_at integer default 0, "
    "ship_id integer default 0, is_new integer default 0, play_count integer default 0, play_count_daily integer default 0, "
    "play_count_weekly integer default 0, updated_at integer default 0);"
    "create table if not exists ds_ship (ship_id integer primary key, area_id integer, mission_id integer, bonus_set_id integer, "
    "item_id integer default 0, uids text, started_at integer, closed_at integer);"
    "create table if not exists ds_bonus (ship_id integer, bonus_id integer, value real, primary key (ship_id, bonus_id));"
    "create table if not exists ds_log (mission_id integer, started_at integer);";

// api/events/event_missions.cpp: (d) our state: the last event mission started (is_last_play).
// Clears are the core's `mission` table (MissionEnd / MissionTalk / end_mission_talk).
const char* const kEvent = "create table if not exists event_last (id integer primary key check (id = 1), mission_id integer, area_id integer)";

// api/events/ranking.cpp: (d) our layout: the best score per ranking, the party that made it, and
// the groups whose result was received; `fresh` = updated since the ranking screen last cleared it
// (UpdatedEventRankingIdList).
const char* const kEventRanking = R"(
create table if not exists event_rank_score (ranking_id integer primary key, group_id integer, score integer, roles text,
  created_at integer, fresh integer default 1);
create table if not exists event_rank_received (group_id integer primary key, received_at integer);
)";

// api/events/favor_drop.cpp: (d) the characters whose bonus the current play uses (same_role_id,
// bonus lots).
const char* const kFavorDrop = "create table if not exists favor_drop_play (same_role_id integer primary key, lots integer);";

// api/social/rental.cpp: rentals the player took, per rental day (the daily reset), and whether
// the bonus was paid.
const char* const kFollow =
    "create table if not exists follow_rental (day integer primary key, count integer not null default 0,"
    " paid integer not null default 0)";

// api/items/gear.cpp: the owned gears; the current barney chance (Barney's "mood"): the group it
// was drawn from and its type.
const char* const kGear =
    "create table if not exists gear_items (uid integer primary key, type integer default 0, master_item_id integer, "
    "param2 integer default 0, item_uid integer default 0, slot integer default 0, is_new integer default 1, created_at integer);"
    "create table if not exists gear_barney (id integer primary key check (id = 1), group_id integer, type integer)";

// api/growth/growth.cpp: roster_ext, what growth adds to an owned character (one row per
// character, created on its first seed or skill change): the seed-raised stats add_* and the
// equipped skills (PLAN-schema S4 merges it into roster).
const char* const kGrowth =
    "create table if not exists roster_ext (uid integer primary key, add_hp integer default 0, add_attack integer default 0, "
    "add_intelligence integer default 0, add_defence integer default 0, add_hit integer default 0, add_guard integer default 0, "
    "add_ap integer default 0, equip_skill1 integer default 0, equip_skill2 integer default 0, equip_skill3 integer default 0)";

// api/shop/shop.cpp: (d) our state: the item-shop counts per row (this period's, the period, ever)
// and the exchange counts per contents row.
const char* const kShop =
    "create table if not exists shop_counts (id integer primary key, num integer, period integer, total integer default 0);"
    "create table if not exists exchange_counts (id integer primary key, shop_id integer, num integer);";

// api/sphere211/: (d) our layout: one dive per player; the cells of the current floor; the
// characters that sortied on this floor; the boxes gathered in this dive; the local ranking's best
// floors.
const char* const kSphere = R"(
create table if not exists sphere (id integer primary key check (id = 1), season_id integer, floor_level integer default 0,
  asset_group integer default 0, streak integer default 0, treasure_total integer default 0, stamina integer, stamina_at integer,
  revive_count integer default 0, best_floor integer default 0, entered_at integer, clear_asset integer default 0,
  lot_floor_num integer default 0, reroll_count integer default 0, prev_season integer default 0, prev_floor integer default 0,
  prev_treasure integer default 0, prev_rank integer default 0);
create table if not exists sphere_cell (asset_id integer primary key, floor_level integer, mission_box_id integer, mission_id integer,
  overwrite_enemy_level integer default 0, cleared integer default 0, playing integer default 0, created_at integer, updated_at integer);
create table if not exists sphere_departed (uid integer primary key);
create table if not exists sphere_box (id integer primary key autoincrement, floor_level integer, rank integer);
create table if not exists sphere_rank (season_id integer primary key, floor_level integer, entered_at integer);
)";
// (d) For the rental slot, the Sphere 211 rental bonus, the achievements and the season end: small
// keyed values (sphere_meta: the season's cycle, its battles won, whether the season-end result is
// still to be shown); the rental slot's lenders of the current floor and whether each was rented;
// the Sphere 211 rentals per rental day; a log of battles won (kind 1) and floors entered (kind 2,
// value = the floor) on the server clock, for the achievements.
const char* const kSphereExtra = R"(
create table if not exists sphere_meta (key text primary key, value integer);
create table if not exists sphere_rental (follow_player_id integer primary key, used integer default 0, updated_at integer);
create table if not exists sphere_rental_day (day integer primary key, season_id integer, count integer default 0, paid integer default 0);
create table if not exists sphere_log (id integer primary key autoincrement, kind integer, value integer, at integer);
)";

// api/shop/subscription.cpp: (d) our state: one row per plan the player has (its window and last
// grant).
const char* const kSubscription =
    "create table if not exists subscription (plan_id integer primary key, opened_at integer, closed_at integer, "
    "updated_at integer)";

// api/player/titles.cpp: the titles the player owns.
const char* const kTitles = "create table if not exists titles (id integer primary key, got_at integer)";

// api/events/world_boss.cpp: (d) our layout: one row per world boss the player met.
const char* const kWorldBoss = R"(
create table if not exists wboss (boss_id integer primary key, area_id integer, wave integer default 1, n1 integer default 0,
  n2 integer default 0, n3 integer default 0, a1 integer default 0, a2 integer default 0, a3 integer default 0,
  required integer default 0, wave_started_at integer, last_clear_secs integer default 0, hunt_until integer default 0,
  hunt_new integer default 0);
create table if not exists wboss_clear (boss_id integer, wave integer, cleared_at integer, notified integer default 0,
  primary key (boss_id, wave));
)";

// core/ext.cpp: the event counters of the achievements (ext::count / counter).
const char* const kCounters = "create table if not exists counters (key text primary key, value integer)";

// api/presents/present_texts.cpp: a present's line in the box (ext::add_present's text).
const char* const kPresentTexts = "create table if not exists present_texts (id integer primary key, text text)";

// soa-server's record of the bridge's device UUIDs (net/game.cpp map_device; formerly created there
// on every bridge, so the in-process route never had it: it exists on both routes now, empty
// in-process).
const char* const kWireDevice =
    "create table if not exists wire_device (uuid text primary key, player_id integer, device_type integer, "
    "first_seen integer, last_seen integer)";

// The columns of `table` in `db`: name -> (declared type, not null, default SQL text or "").
struct Column {
    std::string type, dflt;
    bool not_null = false;
    int order = 0;
};
std::vector<std::pair<std::string, Column>> columns(sqlite3* db, const std::string& table) {
    std::vector<std::pair<std::string, Column>> out;
    sqlite3_stmt* s = nullptr;
    if (sqlite3_prepare_v2(db, ("pragma table_info(\"" + table + "\")").c_str(), -1, &s, nullptr) != SQLITE_OK) return out;
    while (sqlite3_step(s) == SQLITE_ROW) {
        Column c;
        c.order = sqlite3_column_int(s, 0);
        auto text = [&](int k) { return sqlite3_column_type(s, k) == SQLITE_NULL ? std::string() : (const char*)sqlite3_column_text(s, k); };
        c.type = text(2);
        c.not_null = sqlite3_column_int(s, 3) != 0;
        c.dflt = text(4);
        out.emplace_back(text(1), c);
    }
    sqlite3_finalize(s);
    return out;
}

// Step 1's repair: a baseline column a table of the file lacks is added with its baseline type and
// default (`alter table add column`; LOGW per column). The reference is the baseline built in a
// scratch in-memory DB, so the columns come from the same statements, not a second listing.
bool repair_columns(sqlite3* db) {
    sqlite3* ref = nullptr;
    if (sqlite3_open(":memory:", &ref) != SQLITE_OK) {
        sqlite3_close(ref);
        return false;
    }
    bool ok = true;
    for (const char* sql : baseline_sql()) {
        char* err = nullptr;
        if (sqlite3_exec(ref, sql, nullptr, nullptr, &err) != SQLITE_OK) {
            LOGE("server", "state schema: the baseline doesn't build: %s", err ? err : "?");
            sqlite3_free(err);
            ok = false;
        }
    }
    std::vector<std::string> tables;
    sqlite3_stmt* s = nullptr;
    sqlite3_prepare_v2(ref, "select name from sqlite_master where type = 'table' and name not like 'sqlite_%' order by name", -1, &s, nullptr);
    while (s && sqlite3_step(s) == SQLITE_ROW) tables.emplace_back((const char*)sqlite3_column_text(s, 0));
    sqlite3_finalize(s);
    for (const std::string& table : tables) {
        std::set<std::string> have;
        for (auto& [name, col] : columns(db, table)) have.insert(name);
        for (auto& [name, col] : columns(ref, table)) {
            if (have.count(name)) continue;
            std::string alter = "alter table \"" + table + "\" add column \"" + name + "\" " + col.type;
            if (col.not_null) alter += " not null";
            if (!col.dflt.empty()) alter += " default " + col.dflt;
            char* err = nullptr;
            if (sqlite3_exec(db, alter.c_str(), nullptr, nullptr, &err) != SQLITE_OK) {
                LOGE("server", "state schema: can't add the missing column %s.%s: %s", table.c_str(), name.c_str(), err ? err : "?");
                sqlite3_free(err);
                ok = false;
                continue;
            }
            LOGW("server", "state schema: added the missing column %s.%s (%s)", table.c_str(), name.c_str(), alter.c_str());
        }
    }
    sqlite3_close(ref);
    return ok;
}

// ---- step 2: drop the dead (PLAN-schema S2, finding F1) ---------------------------------------
// What nothing reads: roster.favor (favor lives per same role in `favor`), mission.best_rank (no
// per-mission rank: docs/server-rules.md "Missions"), exchange_counts.shop_id (the contents row
// names its shop in the master), and the tables nothing uses: view_flags (UpdateView keeps the
// words in meta view_status / view_status2), gear (gear_items), box_gacha (box_state /
// box_slots) and planets (written by the seed, never read: the open planets are the campaign's
// ActiveMissionList). `drop column` (SQLite 3.35+) since no key, index or reference names them.
const char* const kDropDead[] = {
    "alter table roster drop column favor",
    "alter table mission drop column best_rank",
    "alter table exchange_counts drop column shop_id",
    "drop table view_flags",
    "drop table gear",
    "drop table box_gacha",
    "drop table planets",
};

}  // namespace

const std::vector<const char*>& baseline_sql() {
    static const std::vector<const char*> sql = {kCore,   kFavor,     kDaily,    kDeepSpace,    kEvent,     kEventRanking, kFavorDrop,
                                                 kFollow, kGear,      kGrowth,   kShop,         kSphere,    kSphereExtra,  kSubscription,
                                                 kTitles, kWorldBoss, kCounters, kPresentTexts, kWireDevice};
    return sql;
}

const std::vector<Step>& steps() {
    static const std::vector<Step> s = {
        {1, "the baseline (the 58 tables as before PLAN-schema S1), plus missing columns", baseline_sql(), repair_columns},
        {2, "drop the dead tables and columns (PLAN-schema S2)", {std::begin(kDropDead), std::end(kDropDead)}, nullptr},
    };
    return s;
}

}  // namespace soa::server::state
