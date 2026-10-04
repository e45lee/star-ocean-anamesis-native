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

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>

#include "core/log.h"
#include "core/time.h"      // parse_time_strict (S9: favor.event_drop_at)
#include "master/master.h"  // global_u32 (party_set_max)

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
bool repair_columns(sqlite3* db, sqlite3*) {
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

// ---- step 3: keys out of meta, sphere_meta and counters (PLAN-schema S3, finding F4) -----------
// The player's fields that lived as meta keys become player columns (the table is rebuilt STRICT,
// with its foreign keys, in S4); deep space's two period starts get their singleton table; the
// dive's keyed values (sphere_meta) become columns of the one `sphere` row; the login bonus's
// popup flag leaves counters. kKeysOut is the DDL; move_keys (below) maps the values and then
// deletes the keys and drops sphere_meta.
const char* const kKeysOut[] = {
    // Player.tutorial_status, view_status / view_status2 (u64 bit sets stored as their int64
    // bits), kiyaku_version, title (the selected master_title id; NULL: none), support_pc_id (an
    // owned uid; NULL: unset), time_saving_use_count and its day, the login bonus's popup flag
    "alter table player add column tutorial_status integer not null default 0",
    "alter table player add column view_status integer not null default 0",
    "alter table player add column view_status2 integer not null default 0",
    "alter table player add column kiyaku_version text not null default ''",
    "alter table player add column title_id integer",
    "alter table player add column support_uid integer",
    "alter table player add column time_saving_count integer not null default 0",
    "alter table player add column time_saving_day integer",
    "alter table player add column login_bonus_popup_pending integer not null default 0 check (login_bonus_popup_pending in (0, 1))",
    // api/deepspace/: the start of the daily and the weekly play-limit period the offers' counts are of
    "create table ds_state (id integer primary key check (id = 1), limit_day integer, limit_week integer) strict",
    // api/sphere211/: the season's cycle the dive is of, its battles won, whether the season-end
    // result is still to be sent, and the port's test hook (session scripts only: the enemy
    // level of every start; NULL: off)
    "alter table sphere add column cycle integer not null default 0",
    "alter table sphere add column season_wins integer not null default 0",
    "alter table sphere add column end_pending integer not null default 0 check (end_pending in (0, 1))",
    "alter table sphere add column debug_enemy_level integer",
};

// One statement with its arguments (an int64, a text or NULL); false (logged) when it fails.
struct Bound {
    enum { I, S, N } t = N;
    int64_t i = 0;
    std::string s;
    static Bound integer(int64_t v) { return {I, v, {}}; }
    static Bound text(std::string v) { return {S, 0, std::move(v)}; }
    static Bound null() { return {}; }
};
bool run(sqlite3* db, const char* sql, const std::vector<Bound>& args = {}) {
    sqlite3_stmt* s = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &s, nullptr) != SQLITE_OK) {
        LOGE("server", "state schema: migration: %s: %s", sql, sqlite3_errmsg(db));
        sqlite3_finalize(s);
        return false;
    }
    for (size_t k = 0; k < args.size(); k++) {
        int n = (int)k + 1;
        if (args[k].t == Bound::I) sqlite3_bind_int64(s, n, args[k].i);
        else if (args[k].t == Bound::S) sqlite3_bind_text(s, n, args[k].s.c_str(), -1, SQLITE_TRANSIENT);
        else sqlite3_bind_null(s, n);
    }
    int rc;
    while ((rc = sqlite3_step(s)) == SQLITE_ROW) {}
    sqlite3_finalize(s);
    if (rc != SQLITE_DONE) LOGE("server", "state schema: migration: %s: %s", sql, sqlite3_errmsg(db));
    return rc == SQLITE_DONE;
}

// A key-value table's rows (key -> its value as text).
std::map<std::string, std::string> key_values(sqlite3* db, const char* sql) {
    std::map<std::string, std::string> out;
    sqlite3_stmt* s = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &s, nullptr) == SQLITE_OK)
        while (sqlite3_step(s) == SQLITE_ROW) {
            const unsigned char* v = sqlite3_column_text(s, 1);
            out[(const char*)sqlite3_column_text(s, 0)] = v ? (const char*)v : "";
        }
    sqlite3_finalize(s);
    return out;
}

// The first column of the first row of `sql` (bound to `arg` when given); 0 without a row.
int64_t count_of(sqlite3* db, const char* sql, std::optional<int64_t> arg = std::nullopt) {
    sqlite3_stmt* s = nullptr;
    int64_t n = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &s, nullptr) == SQLITE_OK) {
        if (arg) sqlite3_bind_int64(s, 1, *arg);
        if (sqlite3_step(s) == SQLITE_ROW) n = sqlite3_column_int64(s, 0);
    }
    sqlite3_finalize(s);
    return n;
}

// A key's value as a number: the u64 the readers parsed it as (std::stoull), stored as its int64
// bits (PLAN-schema 4.1: `cast(value as integer)` saturates at 2^63, so view_status's all-ones
// word is converted here). Absent or not a number: nullopt.
std::optional<int64_t> number(const std::map<std::string, std::string>& kv, const char* key) {
    auto it = kv.find(key);
    if (it == kv.end() || it->second.empty()) return std::nullopt;
    const char* p = it->second.c_str();
    char* end = nullptr;
    errno = 0;
    unsigned long long v = *p == '-' ? (unsigned long long)std::strtoll(p, &end, 10) : std::strtoull(p, &end, 10);
    if (errno || *end) {
        LOGW("server", "migrate v3: %s = '%s' isn't a number: dropped", key, p);
        return std::nullopt;
    }
    return (int64_t)v;
}

Bound value_or(const std::optional<int64_t>& v, int64_t dflt) { return Bound::integer(v ? *v : dflt); }
Bound value_or_null(const std::optional<int64_t>& v) { return v ? Bound::integer(*v) : Bound::null(); }

// Step 3's data mapping (PLAN-schema S3): the keys' values into the new columns, then the keys go.
//   meta tutorial_status, view_status, view_status2, kiyaku_version, ds_time_saving_count ->
//     player's columns (absent: the column's default, which is what the readers read for an
//     absent key: 0 / "");
//   meta title -> player.title_id: '0' (taken off) -> NULL, as is absent (never chosen; only a
//     player never loaded has no key: the first load stored the default);
//   meta support_uid -> player.support_uid: 0 or not an owned uid -> NULL (both read as "unset");
//   meta ds_time_saving_day -> player.time_saving_day (absent -> NULL, read as 0 as before);
//   meta ds_limit_day / ds_limit_week -> ds_state (a row only when either key exists);
//   counters login_bonus_popup_pending -> player.login_bonus_popup_pending (value > 0, the
//     reader's test -> 1);
//   sphere_meta cycle, season_wins, end_pending (!= 0 -> 1), test_enemy_level (0: off -> NULL)
//     -> the sphere row's columns. Without a sphere row there is no dive for them to belong to
//     (load_dive creates the row with the season's cycle): dropped, logged.
bool move_keys(sqlite3* db, sqlite3*) {
    auto meta = key_values(db, "select key, value from meta");
    auto sphere_meta = key_values(db, "select key, value from sphere_meta");
    auto counters = key_values(db, "select key, value from counters where key = 'login_bonus_popup_pending'");
    bool has_player = count_of(db, "select count(*) from player") > 0;

    std::optional<int64_t> title = number(meta, "title");
    if (title && *title == 0) title.reset();
    std::optional<int64_t> support = number(meta, "support_uid");
    if (support && (*support == 0 || !count_of(db, "select count(*) from roster where uid = ?", *support))) {
        if (*support) LOGW("server", "migrate v3: player.support_uid: 1 dangling -> NULL");
        support.reset();
    }
    std::optional<int64_t> popup = number(counters, "login_bonus_popup_pending");
    auto kiyaku = meta.find("kiyaku_version");
    bool ok = run(db,
                  "update player set tutorial_status = ?, view_status = ?, view_status2 = ?, kiyaku_version = ?, title_id = ?, "
                  "support_uid = ?, time_saving_count = ?, time_saving_day = ?, login_bonus_popup_pending = ?",
                  {value_or(number(meta, "tutorial_status"), 0), value_or(number(meta, "view_status"), 0), value_or(number(meta, "view_status2"), 0),
                   Bound::text(kiyaku == meta.end() ? "" : kiyaku->second), value_or_null(title), value_or_null(support),
                   value_or(number(meta, "ds_time_saving_count"), 0), value_or_null(number(meta, "ds_time_saving_day")),
                   Bound::integer(popup && *popup > 0 ? 1 : 0)});
    static const char* const kPlayerKeys[] = {"tutorial_status", "view_status", "view_status2",         "kiyaku_version",
                                              "title",           "support_uid", "ds_time_saving_count", "ds_time_saving_day"};
    if (!has_player) {
        size_t n = 0;
        for (const char* k : kPlayerKeys) n += meta.count(k);
        n += counters.size();
        if (n) LOGW("server", "migrate v3: %zu player keys without a player row: dropped", n);
    }
    std::optional<int64_t> limit_day = number(meta, "ds_limit_day"), limit_week = number(meta, "ds_limit_week");
    if (ok && (limit_day || limit_week))
        ok = run(db, "insert into ds_state (id, limit_day, limit_week) values (1, ?, ?)", {value_or_null(limit_day), value_or_null(limit_week)});
    if (ok && !sphere_meta.empty()) {
        if (count_of(db, "select count(*) from sphere where id = 1")) {
            std::optional<int64_t> end_pending = number(sphere_meta, "end_pending"), enemy_level = number(sphere_meta, "test_enemy_level");
            if (enemy_level && *enemy_level == 0) enemy_level.reset();
            ok = run(db, "update sphere set cycle = ?, season_wins = ?, end_pending = ?, debug_enemy_level = ? where id = 1",
                     {value_or(number(sphere_meta, "cycle"), 0), value_or(number(sphere_meta, "season_wins"), 0),
                      Bound::integer(end_pending && *end_pending ? 1 : 0), value_or_null(enemy_level)});
        } else {
            LOGW("server", "migrate v3: %zu sphere_meta keys without a sphere row (no dive): dropped", sphere_meta.size());
        }
    }
    ok = ok && run(db,
                   "delete from meta where key in ('tutorial_status', 'view_status', 'view_status2', 'kiyaku_version', 'title', 'support_uid', "
                   "'ds_time_saving_count', 'ds_time_saving_day', 'ds_limit_day', 'ds_limit_week')");
    ok = ok && run(db, "drop table sphere_meta");
    ok = ok && run(db, "delete from counters where key = 'login_bonus_popup_pending'");
    return ok;
}

// ---- step 4: the roster (PLAN-schema S4, findings F2, F3, F5) ----------------------------------
// One row per owned character: roster_ext (the seeds' add_* and the equipped skills, a table of
// its own only because the growth module couldn't add columns) and assist (a 1:1 relation on the
// roster) merge into roster, which is rebuilt STRICT with its foreign keys and the three unique
// indexes (one character per equipped item, one assisted character per assist); skill1..3 are
// renamed skill1..3_level (they are levels; party_member.skill1..3 are skill ids). player is
// rebuilt STRICT in the same step, since roster is its parent: home_uid, support_uid, title_id and
// party_id become declared references. "None" is NULL in every reference column (0 before). The
// tables are created as new_X, filled by rebuild_roster_and_player (below), and renamed X after
// the old X is dropped (PLAN-schema 4.1: the old table is dropped, never renamed away).
//
// The foreign keys and their actions (PLAN-schema 3.1):
//   roster.weapon_uid, accessory_uid -> items.uid   ON DELETE SET NULL (immediate)
//   roster.assist_uid                -> roster.uid  ON DELETE SET NULL (immediate)
//   player.home_uid                  -> roster.uid  ON DELETE SET NULL, deferred (seed / CreatePlayer
//                                                   write the player before the roster)
//   player.party_id                  -> party_set.party_id  NO ACTION, deferred (the sets are
//                                                   seeded in the player's transaction)
//   player.title_id                  -> titles.id   ON DELETE SET NULL (immediate)
//   player.support_uid               -> roster.uid  ON DELETE SET NULL (immediate)
// No ON UPDATE action: a parent key never changes (uids and ids are allocated once).
const char* const kRoster[] = {
    // CPersonInfo (b): the character's levels and growth, its equipment (owned items), its assist
    R"(create table new_roster (
  uid integer primary key,
  role_id integer not null,
  level integer not null, exp integer not null default 0,
  limit_break integer not null default 0, awaken integer not null default 0,
  skill1_level integer not null default 1, skill2_level integer not null default 1, skill3_level integer not null default 1,
  equip_skill1 integer, equip_skill2 integer, equip_skill3 integer,
  add_hp integer not null default 0, add_attack integer not null default 0, add_intelligence integer not null default 0,
  add_defence integer not null default 0, add_hit integer not null default 0, add_guard integer not null default 0,
  add_ap integer not null default 0,
  weapon_uid integer references items(uid) on delete set null,
  accessory_uid integer references items(uid) on delete set null,
  assist_uid integer references roster(uid) on delete set null,
  created_at integer not null
) strict)",
    // CPlayerInfo (b): the one player of the file
    R"(create table new_player (
  id integer primary key,
  search_id text not null unique,
  name text not null,
  level integer not null, exp integer not null, fol integer not null,
  stamina integer not null, stamina_at integer not null,
  free_coin integer not null default 0, pay_coin integer not null default 0,
  home_uid integer references roster(uid) on delete set null deferrable initially deferred,
  party_id integer not null default 1 references party_set(party_id) deferrable initially deferred,
  created_at integer not null, last_login_at integer,
  tutorial_status integer not null default 0,
  view_status integer not null default 0,
  view_status2 integer not null default 0,
  kiyaku_version text not null default '',
  title_id integer references titles(id) on delete set null,
  support_uid integer references roster(uid) on delete set null,
  time_saving_count integer not null default 0,
  time_saving_day integer,
  login_bonus_popup_pending integer not null default 0 check (login_bonus_popup_pending in (0, 1))
) strict)",
};

// The indexes of the rebuilt roster (created after the rename).
const char* const kRosterIndexes[] = {
    "create unique index roster_weapon on roster(weapon_uid) where weapon_uid is not null",
    "create unique index roster_accessory on roster(accessory_uid) where accessory_uid is not null",
    "create unique index roster_assist on roster(assist_uid) where assist_uid is not null",
};

// LOGW "migrate v<version>: <what>: N <how>" when the count of `sql` is non-zero.
void log_count(sqlite3* db, const char* sql, const char* what, const char* how, int version = 4) {
    if (int64_t n = count_of(db, sql)) LOGW("server", "migrate v%d: %s: %lld %s", version, what, (long long)n, how);
}

// Step 4's data mapping (PLAN-schema S4), with the conventions of 4.1 (0 -> NULL; a dangling
// reference -> its declared action: NULL for SET NULL, dropped for a CASCADE child; each logged):
//   roster ⟕ roster_ext ⟕ assist -> new_roster:
//     skill1..3 -> skill1..3_level; roster_ext's add_* (no row: 0) and equip_skill1..3 (0 -> NULL);
//     weapon_uid / accessory_uid 0 -> NULL, not an item -> NULL, an item two characters wear ->
//       kept by the lowest uid (the unique index);
//     assist.assist_uid where both are owned (and differ), an assist two characters have -> kept
//       by the lowest uid;
//     a roster_ext or assist row of no character -> dropped;
//     a NULL in a not-null column -> 0 (what the readers read for it).
//   player -> new_player: home_uid 0 or not owned -> NULL; title_id not an owned title -> NULL;
//     support_uid not owned -> NULL; party_id NULL or < 1 -> 1; NULLs in not-null columns -> 0 / ''.
//   party_set: with a player, a row per set 1..master_global.party_set_max (icon 0, unlocked:
//     what PartySet sends for a set without one) and for the player's party_id (UpdateParty takes
//     any id), so player.party_id has its parent. A file without a player gets them at its
//     creation (seed / CreatePlayer).
bool rebuild_roster_and_player(sqlite3* db, sqlite3* master) {
    bool has_player = count_of(db, "select count(*) from player") > 0;
    // the counts, for the log (before anything changes)
    log_count(db, "select count(*) from roster where weapon_uid != 0 and weapon_uid not in (select uid from items)", "roster.weapon_uid",
              "dangling -> NULL");
    log_count(db, "select count(*) from roster where accessory_uid != 0 and accessory_uid not in (select uid from items)", "roster.accessory_uid",
              "dangling -> NULL");
    log_count(db,
              "select count(*) from roster r where weapon_uid in (select uid from items) and "
              "exists (select 1 from roster o where o.weapon_uid = r.weapon_uid and o.uid < r.uid)",
              "roster.weapon_uid", "worn by a second character -> NULL (kept by the lowest uid)");
    log_count(db,
              "select count(*) from roster r where accessory_uid in (select uid from items) and "
              "exists (select 1 from roster o where o.accessory_uid = r.accessory_uid and o.uid < r.uid)",
              "roster.accessory_uid", "worn by a second character -> NULL (kept by the lowest uid)");
    log_count(db, "select count(*) from roster_ext where uid not in (select uid from roster)", "roster_ext.uid", "dangling -> dropped");
    log_count(db, "select count(*) from assist where uid not in (select uid from roster)", "assist.uid", "dangling -> dropped");
    log_count(db, "select count(*) from assist where uid in (select uid from roster) and assist_uid not in (select uid from roster)",
              "assist.assist_uid", "dangling -> NULL");
    log_count(db, "select count(*) from assist where uid = assist_uid", "assist.assist_uid", "the character itself -> NULL");
    log_count(
        db,
        "select count(*) from assist a where uid in (select uid from roster) and assist_uid in (select uid from roster) and "
        "exists (select 1 from assist o where o.assist_uid = a.assist_uid and o.uid < a.uid and o.uid != o.assist_uid and o.uid in (select uid from roster))",
        "assist.assist_uid", "assisting a second character -> NULL (kept by the lowest uid)");
    log_count(db, "select count(*) from player where home_uid != 0 and home_uid not in (select uid from roster)", "player.home_uid",
              "dangling -> NULL");
    log_count(db, "select count(*) from player where title_id is not null and title_id not in (select id from titles)", "player.title_id",
              "dangling -> NULL");
    log_count(db, "select count(*) from player where support_uid is not null and support_uid not in (select uid from roster)", "player.support_uid",
              "dangling -> NULL");
    log_count(db, "select count(*) from player where party_id is null or party_id < 1", "player.party_id", "none -> 1");

    // the roster: owned items only, each worn by one character; assists of owned characters only,
    // each assisting one character
    bool ok = run(db, R"(
insert into new_roster (uid, role_id, level, exp, limit_break, awaken, skill1_level, skill2_level, skill3_level,
  equip_skill1, equip_skill2, equip_skill3, add_hp, add_attack, add_intelligence, add_defence, add_hit, add_guard, add_ap,
  weapon_uid, accessory_uid, assist_uid, created_at)
select r.uid, ifnull(r.role_id, 0), ifnull(r.level, 0), ifnull(r.exp, 0), ifnull(r.limit_break, 0), ifnull(r.awaken, 0),
  ifnull(r.skill1, 0), ifnull(r.skill2, 0), ifnull(r.skill3, 0),
  nullif(e.equip_skill1, 0), nullif(e.equip_skill2, 0), nullif(e.equip_skill3, 0),
  ifnull(e.add_hp, 0), ifnull(e.add_attack, 0), ifnull(e.add_intelligence, 0), ifnull(e.add_defence, 0), ifnull(e.add_hit, 0),
  ifnull(e.add_guard, 0), ifnull(e.add_ap, 0),
  case when r.weapon_uid in (select uid from items)
        and not exists (select 1 from roster o where o.weapon_uid = r.weapon_uid and o.uid < r.uid) then r.weapon_uid end,
  case when r.accessory_uid in (select uid from items)
        and not exists (select 1 from roster o where o.accessory_uid = r.accessory_uid and o.uid < r.uid) then r.accessory_uid end,
  case when a.assist_uid in (select uid from roster) and a.assist_uid != r.uid
        and not exists (select 1 from assist o where o.assist_uid = a.assist_uid and o.uid < a.uid and o.uid != o.assist_uid and o.uid in (select uid from roster))
       then a.assist_uid end,
  ifnull(r.created_at, 0)
from roster r left join roster_ext e on e.uid = r.uid left join assist a on a.uid = r.uid)");
    // the player's sets (before the player, whose party_id names one)
    if (ok && has_player) {
        u32 max = master ? master::global_u32(master, "party_set_max", 10) : 10;  // (a) master_global party_set_max
        if (!master) LOGW("server", "migrate v4: no master DB: the party sets 1..%u", max);
        for (u32 party_id = 1; ok && party_id <= max; party_id++)
            ok = run(db, "insert into party_set (party_id) values (?) on conflict(party_id) do nothing", {Bound::integer(party_id)});
        ok = ok && run(db,
                       "insert into party_set (party_id) select party_id from player where party_id >= 1 "
                       "on conflict(party_id) do nothing");
    }
    ok = ok && run(db, R"(
insert into new_player (id, search_id, name, level, exp, fol, stamina, stamina_at, free_coin, pay_coin, home_uid, party_id,
  created_at, last_login_at, tutorial_status, view_status, view_status2, kiyaku_version, title_id, support_uid,
  time_saving_count, time_saving_day, login_bonus_popup_pending)
select id, ifnull(search_id, ''), ifnull(name, ''), ifnull(level, 0), ifnull(exp, 0), ifnull(fol, 0), ifnull(stamina, 0),
  ifnull(stamina_at, 0), ifnull(free_coin, 0), ifnull(pay_coin, 0),
  case when home_uid in (select uid from roster) then home_uid end,
  case when party_id >= 1 then party_id else 1 end,
  ifnull(created_at, 0), last_login_at, tutorial_status, view_status, view_status2, kiyaku_version,
  case when title_id in (select id from titles) then title_id end,
  case when support_uid in (select uid from roster) then support_uid end,
  time_saving_count, time_saving_day, login_bonus_popup_pending
from player)");
    for (const char* sql : {"drop table roster", "drop table roster_ext", "drop table assist", "alter table new_roster rename to roster",
                            "drop table player", "alter table new_player rename to player"})
        ok = ok && run(db, sql);
    for (const char* sql : kRosterIndexes) ok = ok && run(db, sql);
    return ok;
}

// ---- step 5: items and gear (PLAN-schema S5, findings F2, F3) ----------------------------------
// The owned weapons and accessories (items) and the owned gears (gear_items) are rebuilt STRICT:
// items gets its `locked` check, gear_items its reference to the weapon it is set in (NULL: in the
// gear box; 0 before) with ON DELETE CASCADE, its `is_new` check and one gear per weapon slot (the
// unique index). The cascade is the rule the gear module applied by hand at every gear list read
// before (gear.cpp gear_info_list: `delete from gear_items where item_uid != 0 and item_uid not in
// (select uid from items)`): (d) gear set in a weapon that is gone (sold, used as a material, the
// base of a GenerateGear) goes with it, now at the weapon's delete. As in step 4 the tables are
// created as new_X (gear_items' reference names the final `items`), filled by rebuild_items_and_gear
// and renamed X after the old X is dropped; roster's weapon_uid / accessory_uid references keep
// naming `items`, which is the new table after the rename.
//
// The foreign key and its action (PLAN-schema 3.1):
//   gear_items.item_uid -> items.uid   ON DELETE CASCADE (immediate)
// No ON UPDATE action: an item's uid never changes.
const char* const kItemsGear[] = {
    // CItemInfo (b): an owned weapon or accessory
    R"(create table new_items (
  uid integer primary key,
  master_item_id integer not null,
  item_type integer not null, level integer not null default 1, exp integer not null default 0,
  limit_break integer not null default 0,
  locked integer not null default 0 check (locked in (0, 1)),
  created_at integer not null
) strict)",
    // CGearInfo (b): an owned gear, in the gear box (item_uid NULL) or set in a weapon's slot
    R"(create table new_gear_items (
  uid integer primary key,
  type integer not null default 0,
  master_item_id integer not null,
  param2 integer not null default 0,
  item_uid integer references items(uid) on delete cascade,
  slot integer not null default 0,
  is_new integer not null default 1 check (is_new in (0, 1)),
  created_at integer not null
) strict)",
};

// The index of the rebuilt gear_items (created after the rename): one gear per weapon slot.
const char* const kGearIndexes[] = {
    "create unique index gear_items_slot on gear_items(item_uid, slot) where item_uid is not null",
};

// Step 5's data mapping (PLAN-schema S5), with the conventions of 4.1:
//   items -> new_items: a NULL in a not-null column -> 0 (what the readers read for it); locked
//     not 0 -> 1 (the readers test `locked != 0`).
//   gear_items -> new_gear_items: item_uid 0 -> NULL (the gear box); item_uid naming no item ->
//     the row dropped (the CASCADE child: the rule gear_info_list applied at the next read); a
//     second gear in an occupied weapon slot -> the gear box (item_uid NULL, slot 0, as RemoveGear
//     leaves a gear), the slot kept by the lowest uid; is_new not 0 -> 1 (read as `is_new != 0`);
//     a NULL in a not-null column -> 0.
bool rebuild_items_and_gear(sqlite3* db, sqlite3*) {
    // the counts, for the log (before anything changes)
    log_count(db, "select count(*) from items where locked is not null and locked not in (0, 1)", "items.locked", "not 0 / 1 -> 1", 5);
    log_count(db, "select count(*) from gear_items where item_uid != 0 and item_uid not in (select uid from items)", "gear_items.item_uid",
              "dangling -> dropped", 5);
    log_count(db,
              "select count(*) from gear_items g where item_uid in (select uid from items) and "
              "exists (select 1 from gear_items o where o.item_uid = g.item_uid and ifnull(o.slot, 0) = ifnull(g.slot, 0) and o.uid < g.uid)",
              "gear_items.item_uid", "a second gear in a weapon slot -> the gear box (kept by the lowest uid)", 5);
    log_count(db, "select count(*) from gear_items where is_new is not null and is_new not in (0, 1)", "gear_items.is_new", "not 0 / 1 -> 1", 5);

    bool ok = run(db, R"(
insert into new_items (uid, master_item_id, item_type, level, exp, limit_break, locked, created_at)
select uid, ifnull(master_item_id, 0), ifnull(item_type, 0), ifnull(level, 0), ifnull(exp, 0), ifnull(limit_break, 0),
  case when ifnull(locked, 0) != 0 then 1 else 0 end, ifnull(created_at, 0)
from items)");
    ok = ok && run(db, R"(
insert into new_gear_items (uid, type, master_item_id, param2, item_uid, slot, is_new, created_at)
select g.uid, ifnull(g.type, 0), ifnull(g.master_item_id, 0), ifnull(g.param2, 0),
  case when g.item_uid != 0 and exists (select 1 from gear_items o where o.item_uid = g.item_uid and ifnull(o.slot, 0) = ifnull(g.slot, 0) and o.uid < g.uid) then null
       else nullif(g.item_uid, 0) end,
  case when g.item_uid != 0 and exists (select 1 from gear_items o where o.item_uid = g.item_uid and ifnull(o.slot, 0) = ifnull(g.slot, 0) and o.uid < g.uid) then 0
       else ifnull(g.slot, 0) end,
  case when ifnull(g.is_new, 0) != 0 then 1 else 0 end, ifnull(g.created_at, 0)
from gear_items g where ifnull(g.item_uid, 0) = 0 or g.item_uid in (select uid from items))");
    for (const char* sql :
         {"drop table gear_items", "drop table items", "alter table new_items rename to items", "alter table new_gear_items rename to gear_items"})
        ok = ok && run(db, sql);
    for (const char* sql : kGearIndexes) ok = ok && run(db, sql);
    return ok;
}

// ---- step 6: parties (PLAN-schema S6, findings F2, F3) -----------------------------------------
// A party set's members were two tables with one key: `party` (party_id, slot, uid: written by the
// seed, CreatePlayer, UpdateParty and UpdatePartySet) and `party_member` (the slot's equipment,
// skills and assist: written by UpdatePartySet only). They are one table now, `party_member`, with
// the member's uid; `party` is gone. `party_set` (the set's icon and lock) is rebuilt STRICT with
// its checks (3.2): a set id is >= 1, a slot is 0..3 (the client's four).
//
// The foreign keys and their actions (PLAN-schema 3.1):
//   party_member.party_id      -> party_set.party_id  ON DELETE CASCADE (the set's members)
//   party_member.uid           -> roster.uid          ON DELETE SET NULL (an empty slot)
//   party_member.weapon_uid    -> items.uid           ON DELETE SET NULL (the member's equipment in
//   party_member.accessory_uid -> items.uid           ON DELETE SET NULL  the set: none)
//   party_member.assist_uid    -> roster.uid          ON DELETE SET NULL
// All immediate (every writer writes the set before its members). No ON UPDATE action: a parent key
// never changes. player.party_id keeps naming `party_set` (step 4's deferred NO ACTION), which is
// the new table after the rename.
const char* const kParty[] = {
    // PartySetInfo (b): a party set's own fields
    R"(create table new_party_set (
  party_id integer primary key check (party_id >= 1),
  icon_id integer not null default 0,
  is_lock integer not null default 0 check (is_lock in (0, 1))
) strict)",
    // PartySetCharacterInfo (b): one slot of a set: its character, and the character's equipment,
    // skills (master skill ids) and assist in this set; NULL: none (the equipment: the
    // character's own, party_set.cpp)
    R"(create table new_party_member (
  party_id integer not null references party_set(party_id) on delete cascade,
  slot integer not null check (slot between 0 and 3),
  uid integer references roster(uid) on delete set null,
  weapon_uid integer references items(uid) on delete set null,
  accessory_uid integer references items(uid) on delete set null,
  skill_id1 integer, skill_id2 integer, skill_id3 integer,
  assist_uid integer references roster(uid) on delete set null,
  primary key (party_id, slot)
) strict)",
};

// Step 6's data mapping (PLAN-schema S6), with the conventions of 4.1 (each case logged with its
// count):
//   party_set -> new_party_set: a set id < 1 (UpdateParty took any id) -> dropped, with its members;
//     icon_id NULL -> 0, is_lock not 0 -> 1 (read as `!= 0`); a set that has `party` rows but no
//     party_set row (UpdateParty's sets before step 4 gave the current one a row) -> a row (icon 0,
//     unlocked: what PartySet sent for it).
//   player.party_id < 1 -> 1 (UpdateParty(0) made set 0 current; set 1 exists for every player).
//   party ⟕ party_member -> new_party_member, one row per `party` row (a party_member row without
//     one -> dropped: nothing read it): uid 0 or not an owned character -> NULL (an empty slot);
//     weapon_uid / accessory_uid 0 or not an owned item (sold, composed) -> NULL; skill1..3 ->
//     skill_id1..3, 0 -> NULL; assist_uid 0 or not an owned character -> NULL; a slot outside 0..3
//     (UpdatePartySet stored any party_index) or a set id < 1 -> dropped. A slot without a
//     party_member row (the seed's, CreatePlayer's, UpdateParty's) has NULL equipment, skills and
//     assist.
bool rebuild_parties(sqlite3* db, sqlite3*) {
    // the counts, for the log (before anything changes)
    log_count(db, "select count(*) from party_set where party_id is null or party_id < 1", "party_set.party_id", "< 1 -> dropped", 6);
    log_count(db, "select count(*) from party_set where is_lock is not null and is_lock not in (0, 1)", "party_set.is_lock", "not 0 / 1 -> 1", 6);
    log_count(db, "select count(distinct party_id) from party where party_id >= 1 and party_id not in (select party_id from party_set)",
              "party.party_id", "a set without a party_set row -> its row", 6);
    log_count(db, "select count(*) from player where party_id < 1", "player.party_id", "< 1 -> 1", 6);
    log_count(db, "select count(*) from party where party_id is null or party_id < 1 or slot is null or slot not between 0 and 3", "party.slot",
              "a set id < 1 or a slot outside 0..3 -> dropped", 6);
    log_count(db, "select count(*) from party_member m where not exists (select 1 from party p where p.party_id = m.party_id and p.slot = m.slot)",
              "party_member", "no party row -> dropped", 6);
    log_count(db, "select count(*) from party where uid != 0 and uid not in (select uid from roster)", "party_member.uid", "dangling -> NULL", 6);
    log_count(db, "select count(*) from party_member where weapon_uid != 0 and weapon_uid not in (select uid from items)", "party_member.weapon_uid",
              "dangling -> NULL", 6);
    log_count(db, "select count(*) from party_member where accessory_uid != 0 and accessory_uid not in (select uid from items)",
              "party_member.accessory_uid", "dangling -> NULL", 6);
    log_count(db, "select count(*) from party_member where assist_uid != 0 and assist_uid not in (select uid from roster)", "party_member.assist_uid",
              "dangling -> NULL", 6);

    bool ok = run(db, R"(
insert into new_party_set (party_id, icon_id, is_lock)
select party_id, ifnull(icon_id, 0), case when ifnull(is_lock, 0) != 0 then 1 else 0 end
from party_set where party_id >= 1)");
    ok = ok && run(db, R"(
insert into new_party_set (party_id)
select distinct party_id from party where party_id >= 1 and party_id not in (select party_id from party_set))");
    ok = ok && run(db, "update player set party_id = 1 where party_id < 1");
    ok = ok && run(db, "insert into new_party_set (party_id) select party_id from player where true on conflict(party_id) do nothing");
    ok = ok && run(db, R"(
insert into new_party_member (party_id, slot, uid, weapon_uid, accessory_uid, skill_id1, skill_id2, skill_id3, assist_uid)
select p.party_id, p.slot,
  case when p.uid in (select uid from roster) then p.uid end,
  case when m.weapon_uid in (select uid from items) then m.weapon_uid end,
  case when m.accessory_uid in (select uid from items) then m.accessory_uid end,
  nullif(m.skill1, 0), nullif(m.skill2, 0), nullif(m.skill3, 0),
  case when m.assist_uid in (select uid from roster) then m.assist_uid end
from party p left join party_member m on m.party_id = p.party_id and m.slot = p.slot
where p.party_id >= 1 and p.slot between 0 and 3)");
    for (const char* sql : {"drop table party_member", "drop table party", "drop table party_set", "alter table new_party_set rename to party_set",
                            "alter table new_party_member rename to party_member"})
        ok = ok && run(db, sql);
    return ok;
}

// ---- step 7: the battle in progress (PLAN-schema S7, findings F2, F3) --------------------------
// The play record was two singletons written together (`play`: the mission, party, start and the
// party's uids as a "uid,uid," text; `play_ext`: the mission type, the surprise roll and the
// helper) but not always deleted together (MissionFailed deleted `play` only, so a MissionEnd
// without a play read the last start's type and surprise roll). They are one row now, `play`, and
// the party is `play_member` rows: an owned character's uid (checkable: a roster reference), or a
// mission NPC's battle uid (0x7f000000 + 1 + its order, the tutorial's NPC party). Deleting the
// play deletes its members. play_ext.campaign_lots was written and never read (MissionEnd reads the
// campaigns again): dropped. helper_uid / helper_kind / npc_id are kept: MissionRestart replays the
// helper from them. Deep space's ships keep their crew the same way (`ds_ship.uids` text ->
// `ds_ship_member` rows, slot 1..8 as the client's ship_slot), and `ds_log` gets its id (3.2).
//
// The foreign keys and their actions (PLAN-schema 3.1):
//   play.party_id            -> party_set.party_id  ON DELETE SET NULL (MissionRestart: the
//                                                   player's current party then)
//   play_member.play_id      -> play.id             ON DELETE CASCADE (the play's members)
//   play_member.uid          -> roster.uid          ON DELETE SET NULL (a member gone)
//   ds_ship_member.ship_id   -> ds_ship.ship_id     ON DELETE CASCADE (the ship's crew)
//   ds_ship_member.uid       -> roster.uid          NO ACTION (a character out on a ship can't go)
// All immediate (every writer writes the parent first). No ON UPDATE action.
const char* const kPlay[] = {
    // CPlayMissionInfo (b) and what MissionStart decided (d): the mission in progress
    R"(create table new_play (
  id integer primary key check (id = 1),
  mission_id integer not null,
  mission_type integer not null default 0,
  party_id integer references party_set(party_id) on delete set null,
  started_at integer not null,
  stamina_cost integer not null default 0,
  surprise integer not null default 0 check (surprise in (0, 1)),
  helper_kind integer not null default 0 check (helper_kind between 0 and 3),
  helper_uid integer,
  npc_id integer
) strict)",
    // BattleParameter.PlayerCharacter (b), in order (slot 0..): an owned character or a mission
    // NPC, never both; both NULL: a character gone since (SET NULL)
    R"(create table play_member (
  play_id integer not null default 1 references play(id) on delete cascade,
  slot integer not null check (slot >= 0),
  uid integer references roster(uid) on delete set null,
  npc_uid integer check (npc_uid is null or uid is null),
  primary key (play_id, slot)
) strict)",
    // CDeepSpaceCharacterInfo (b): a ship's crew, ship_slot 1..8 (CDeepSpaceProgressDialog::Open)
    R"(create table ds_ship_member (
  ship_id integer not null references ds_ship(ship_id) on delete cascade,
  slot integer not null check (slot between 1 and 8),
  uid integer not null references roster(uid),
  primary key (ship_id, slot)
) strict)",
    // every departure (api/presents/achievements.cpp counts them)
    R"(create table new_ds_log (
  id integer primary key autoincrement,
  mission_id integer not null,
  started_at integer not null
) strict)",
};

// The numbers of a "uid,uid," list in order (empty items skipped); `bad` counts the items that
// aren't numbers (skipped too: the readers' std::stoull threw on them).
std::vector<int64_t> uid_list(const std::string& text, int64_t& bad) {
    std::vector<int64_t> out;
    for (size_t begin = 0; begin < text.size();) {
        size_t end = text.find(',', begin);
        if (end == std::string::npos) end = text.size();
        if (end > begin) {
            std::string item = text.substr(begin, end - begin);
            char* stop = nullptr;
            errno = 0;
            unsigned long long v = std::strtoull(item.c_str(), &stop, 10);
            if (errno || *stop || item[0] == '-') bad++;
            else out.push_back((int64_t)v);
        }
        begin = end + 1;
    }
    return out;
}

// Rows of `sql` as (int64 key, text) pairs.
std::vector<std::pair<int64_t, std::string>> keyed_texts(sqlite3* db, const char* sql) {
    std::vector<std::pair<int64_t, std::string>> out;
    sqlite3_stmt* s = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &s, nullptr) == SQLITE_OK)
        while (sqlite3_step(s) == SQLITE_ROW) {
            const unsigned char* v = sqlite3_column_text(s, 1);
            out.push_back({sqlite3_column_int64(s, 0), v ? (const char*)v : ""});
        }
    sqlite3_finalize(s);
    return out;
}

// The battle uids the server gives mission NPCs (api/missions/mission_start.cpp kNpcPartyUid0 + 1
// + their order; master_mission_npc has a few rows per mission).
constexpr int64_t kNpcPartyUidFirst = 0x7f000001, kNpcPartyUidLast = 0x7f0000ff;

// Step 7's data mapping (PLAN-schema S7), with the conventions of 4.1 (each case logged with its
// count):
//   play ⟕ play_ext -> new_play (the one row, id 1): a play without a mission (mission_id NULL or
//     0: nothing in progress, GetPlayMission's reading) -> dropped, and so is a play_ext without a
//     play (MissionFailed's leftover: nothing reads it now); mission_type / surprise /
//     helper_kind from play_ext (none: 0, what the readers read); surprise not 0 -> 1;
//     helper_kind outside 0..3 -> 0; party_id not a party set -> NULL; started_at / stamina_cost
//     NULL -> 0; helper_uid / npc_id 0 -> NULL; campaign_lots dropped (never read).
//   play.uids -> play_member, the k-th item at slot k: a roster uid -> uid; else 0x7f000001 ..
//     0x7f0000ff -> npc_uid (a mission NPC); else (a character gone) a row with both NULL, as
//     ON DELETE SET NULL leaves it; an item that isn't a number -> skipped.
//   ds_ship.uids -> ds_ship_member, the k-th item at slot k + 1: a roster uid -> a row; else (gone,
//     or past slot 8) -> dropped (uid is NOT NULL); not a number -> skipped. Then the column goes.
//   ds_log -> new_ds_log: id = the row's rowid (the departures' order), mission_id / started_at
//     NULL -> 0.
bool rebuild_play(sqlite3* db, sqlite3*) {
    // the counts, for the log (before anything changes)
    log_count(db, "select count(*) from play where ifnull(mission_id, 0) = 0", "play.mission_id", "none -> dropped (nothing in progress)", 7);
    log_count(db, "select count(*) from play_ext where id not in (select id from play where ifnull(mission_id, 0) != 0)", "play_ext",
              "no play -> dropped", 7);
    log_count(db, "select count(*) from play where party_id is not null and party_id not in (select party_id from party_set)", "play.party_id",
              "dangling -> NULL", 7);
    log_count(db, "select count(*) from play_ext where helper_kind is not null and helper_kind not between 0 and 3", "play.helper_kind",
              "outside 0..3 -> 0", 7);
    log_count(db, "select count(*) from ds_log where mission_id is null or started_at is null", "ds_log", "NULL -> 0", 7);

    bool ok = run(db, R"(
insert into new_play (id, mission_id, mission_type, party_id, started_at, stamina_cost, surprise, helper_kind, helper_uid, npc_id)
select 1, p.mission_id, ifnull(e.mission_type, 0),
  case when p.party_id in (select party_id from party_set) then p.party_id end,
  ifnull(p.started_at, 0), ifnull(p.stamina_cost, 0),
  case when ifnull(e.surprise, 0) != 0 then 1 else 0 end,
  case when e.helper_kind between 0 and 3 then e.helper_kind else 0 end,
  nullif(e.helper_uid, 0), nullif(e.npc_id, 0)
from play p left join play_ext e on e.id = p.id
where p.id = 1 and ifnull(p.mission_id, 0) != 0)");

    // the play's party
    int64_t bad = 0, gone = 0, npcs = 0;
    for (auto& [id, text] : keyed_texts(db, "select id, uids from play where id = 1 and ifnull(mission_id, 0) != 0")) {
        std::vector<int64_t> uids = uid_list(text, bad);
        for (size_t k = 0; ok && k < uids.size(); k++) {
            const int64_t uid = uids[k];
            const bool owned = count_of(db, "select count(*) from roster where uid = ?", uid) != 0;
            const bool npc = !owned && uid >= kNpcPartyUidFirst && uid <= kNpcPartyUidLast;
            if (!owned && !npc) gone++;
            if (npc) npcs++;
            ok = run(db, "insert into play_member (play_id, slot, uid, npc_uid) values (1, ?, ?, ?)",
                     {Bound::integer((int64_t)k), owned ? Bound::integer(uid) : Bound::null(), npc ? Bound::integer(uid) : Bound::null()});
        }
    }
    if (npcs) LOGI("server", "migrate v7: play_member.npc_uid: %lld mission NPCs", (long long)npcs);
    if (gone) LOGW("server", "migrate v7: play_member.uid: %lld dangling -> NULL", (long long)gone);
    if (bad) LOGW("server", "migrate v7: play.uids: %lld items not a number -> skipped", (long long)bad);

    // the ships' crews
    bad = gone = 0;
    for (auto& [ship_id, text] : keyed_texts(db, "select ship_id, uids from ds_ship order by ship_id")) {
        std::vector<int64_t> uids = uid_list(text, bad);
        for (size_t k = 0; ok && k < uids.size(); k++) {
            if (k >= 8 || !count_of(db, "select count(*) from roster where uid = ?", uids[k])) {
                gone++;
                continue;
            }
            ok = run(db, "insert into ds_ship_member (ship_id, slot, uid) values (?, ?, ?)",
                     {Bound::integer(ship_id), Bound::integer((int64_t)k + 1), Bound::integer(uids[k])});
        }
    }
    if (gone) LOGW("server", "migrate v7: ds_ship_member.uid: %lld dangling or past slot 8 -> dropped", (long long)gone);
    if (bad) LOGW("server", "migrate v7: ds_ship.uids: %lld items not a number -> skipped", (long long)bad);

    ok =
        ok &&
        run(db,
            "insert into new_ds_log (id, mission_id, started_at) select rowid, ifnull(mission_id, 0), ifnull(started_at, 0) from ds_log order by rowid");
    for (const char* sql : {"drop table play_ext", "drop table play", "drop table ds_log", "alter table new_play rename to play",
                            "alter table new_ds_log rename to ds_log", "alter table ds_ship drop column uids"})
        ok = ok && run(db, sql);
    return ok;
}

// ---- step 8: presents (PLAN-schema S8, finding F3) ---------------------------------------------
// A present's box line was a table of its own (`present_texts`, keyed by the present's id, written
// by ext::add_present only when it had a line: the module couldn't add a column to the core's
// table). It is the present's `text` column now (NULL: built from the reason when the box is
// read); `present_texts` is gone. `presents` is rebuilt STRICT (3.2): the wallet types (content
// type 3 FOL, 4 free coins: docs/api.md "Content types") name no content, so their content_id 0 is
// NULL ("none" is NULL, 3.1; the readers read it as 0). No foreign key: content_id is a master
// reference of the type's table (polymorphic), and nothing references a present.
const char* const kPresents[] = {
    // CPresentBoxInfo (b): a present in the box (received_at NULL) or received; its line
    // (free_text_message_id) when stored
    R"(create table new_presents (
  id integer primary key autoincrement,
  content_type integer not null,
  content_id integer,
  num integer not null,
  reason_type integer not null,
  reason_param integer,
  text text,
  created_at integer not null,
  received_at integer
) strict)",
};

// Step 8's data mapping (PLAN-schema S8), with the conventions of 4.1 (each case logged with its
// count):
//   presents ⟕ present_texts -> new_presents: text from present_texts ('' -> NULL: the reader
//     built the line for an empty one, as for none); content_id of a wallet type (3, 4) 0 ->
//     NULL; a NULL in a not-null column (content_type, num, reason_type, created_at) -> 0 (what
//     the readers read); a present_texts row without a present -> dropped (nothing read it). The
//     AUTOINCREMENT counter is kept (sqlite_sequence: a present's id is never reused).
bool rebuild_presents(sqlite3* db, sqlite3*) {
    // the counts, for the log (before anything changes)
    log_count(db, "select count(*) from present_texts where id not in (select id from presents)", "present_texts", "no present -> dropped", 8);
    log_count(db, "select count(*) from presents where content_type in (3, 4) and content_id = 0", "presents.content_id",
              "0 of a wallet type -> NULL", 8);
    log_count(db, "select count(*) from presents where content_type is null or num is null or reason_type is null or created_at is null", "presents",
              "NULL in a not-null column -> 0", 8);
    const int64_t seq = count_of(db, "select ifnull(max(seq), 0) from sqlite_sequence where name = 'presents'");

    bool ok = run(db, R"(
insert into new_presents (id, content_type, content_id, num, reason_type, reason_param, text, created_at, received_at)
select p.id, ifnull(p.content_type, 0),
  case when p.content_type in (3, 4) then nullif(p.content_id, 0) else p.content_id end,
  ifnull(p.num, 0), ifnull(p.reason_type, 0), p.reason_param, nullif(t.text, ''), ifnull(p.created_at, 0), p.received_at
from presents p left join present_texts t on t.id = p.id order by p.id)");
    for (const char* sql : {"drop table present_texts", "drop table presents", "alter table new_presents rename to presents"})
        ok = ok && run(db, sql);
    // the counter: at least the old one (the inserts set it to the largest id)
    if (ok && seq) ok = run(db, "update sqlite_sequence set seq = max(seq, ?) where name = 'presents'", {Bound::integer(seq)});
    return ok;
}

// ---- step 9: times and booleans (PLAN-schema S9, finding F5) -----------------------------------
// The conventions of 3.1 on the tables that still broke them: a time is an INTEGER of unix seconds
// on the server clock and NULL is "never" (favor.event_drop_at was a formatted local-time text, ''
// for never; favor.tapped_at, titles.got_at and premium_pass.last_at used 0); a counter is
// `day_index` and a reset day's start `*_day` (login_bonus.day / premium_pass.day were counters,
// follow_rental.day / sphere_rental_day.day day starts); a boolean keeps its name, `is_*` where it
// had none (ds_area.last_play -> is_last_play), and is `integer not null default 0 check (x in
// (0, 1))`. A CHECK needs a rebuild, so each table below is rebuilt into its 3.2 form (STRICT), less
// what S10 adds: the tables S10 rebuilds for their foreign keys get their boolean CHECKs there
// (ds_offer.is_new, gacha_history.duplicate, wboss_clear.notified), and the 0 sentinels S10 maps
// stay (wboss.hunt_until, ds_offer.closed_at; favor_bonus_state.healed_at with its lot_uid FK).
// `titles` is a parent (player.title_id): new_titles is renamed to titles after the old one is
// dropped (4.1), so the reference resolves to the new table. No new foreign key.
const char* const kTimesBooleans[] = {
    // CPlayerCharacterFavorInfoElement (b): favor_point, favor_up_count_by_tap on the favor day of
    // updated_by_tap_at, added_event_drop_at; the times NULL: never
    R"(create table new_favor (
  same_role_id integer primary key,
  point integer not null default 0,
  tap_count integer not null default 0,
  tapped_at integer,
  event_drop_at integer
) strict)",
    // the owned titles (TitleList (b)); got_at NULL: a default title, owned from the start
    R"(create table new_titles (
  id integer primary key,
  got_at integer
) strict)",
    // CLoginBonusInfo.current_idx (b): the last page granted, and when
    R"(create table new_login_bonus (
  id integer primary key,
  day_index integer not null,
  last_at integer
) strict)",
    // CPremiumLoginBonusInfo.current_idx (b) of a pass the player holds; last_at NULL: no page yet
    R"(create table new_premium_pass (
  id integer primary key,
  granted_at integer not null,
  day_index integer not null default 0,
  last_at integer
) strict)",
    // the rentals taken per rental day (its start), and whether that day's bonus was paid
    R"(create table new_follow_rental (
  rental_day integer primary key,
  count integer not null default 0,
  paid integer not null default 0 check (paid in (0, 1))
) strict)",
    // Sphere 211's rentals per rental day (its start), and whether that day's bonus was paid
    R"(create table new_sphere_rental_day (
  rental_day integer primary key,
  season_id integer,
  count integer not null default 0,
  paid integer not null default 0 check (paid in (0, 1))
) strict)",
    // CDeepSpaceAreaInfo (b): exp, is_new, is_last_play
    R"(create table new_ds_area (
  area_id integer primary key,
  exp integer not null default 0,
  is_new integer not null default 0 check (is_new in (0, 1)),
  is_last_play integer not null default 0 check (is_last_play in (0, 1))
) strict)",
    // the missions played: cleared (is_clear (b)), the counts, the first clear
    R"(create table new_mission (
  mission_id integer primary key,
  cleared integer not null default 0 check (cleared in (0, 1)),
  play_count integer not null default 0,
  clear_count integer not null default 0,
  first_clear_at integer
) strict)",
    // an event ranking's best score and its party; fresh: updated since the screen last cleared it
    R"(create table new_event_rank_score (
  ranking_id integer primary key,
  group_id integer not null,
  score integer not null,
  roles text,
  created_at integer,
  fresh integer not null default 1 check (fresh in (0, 1))
) strict)",
    // a world boss the player met (columns as before; hunt_until 0 = no big hunt until S10)
    R"(create table new_wboss (
  boss_id integer primary key,
  area_id integer,
  wave integer default 1,
  n1 integer default 0, n2 integer default 0, n3 integer default 0,
  a1 integer default 0, a2 integer default 0, a3 integer default 0,
  required integer default 0,
  wave_started_at integer,
  last_clear_secs integer default 0,
  hunt_until integer default 0,
  hunt_new integer not null default 0 check (hunt_new in (0, 1))
) strict)",
    // a cell of the current Sphere 211 floor
    R"(create table new_sphere_cell (
  asset_id integer primary key,
  floor_level integer not null,
  mission_box_id integer,
  mission_id integer,
  overwrite_enemy_level integer not null default 0,
  cleared integer not null default 0 check (cleared in (0, 1)),
  playing integer not null default 0 check (playing in (0, 1)),
  created_at integer,
  updated_at integer
) strict)",
    // a lender of the current floor's rental slot, and whether it was rented
    R"(create table new_sphere_rental (
  follow_player_id integer primary key,
  used integer not null default 0 check (used in (0, 1)),
  updated_at integer
) strict)",
};

// The tables step 9 rebuilds, in kTimesBooleans' order.
const char* const kTimesBooleansTables[] = {"favor",   "titles",  "login_bonus",      "premium_pass", "follow_rental", "sphere_rental_day",
                                            "ds_area", "mission", "event_rank_score", "wboss",        "sphere_cell",   "sphere_rental"};

// Step 9's data mapping (PLAN-schema S9), with the conventions of 4.1 (each case logged with its
// count): a boolean not 0 / 1 -> 1, NULL -> 0 (the readers test `!= 0`); a NULL in a not-null
// column -> 0 (what the readers read);
//   favor: event_drop_at '' (or NULL) -> NULL, a time string -> its seconds (parse_time_strict, the
//     reader's parse: local time), one that doesn't parse -> NULL (the reader read it as never: no
//     favor day); tapped_at 0 -> NULL;
//   titles.got_at 0 -> NULL (the default titles);
//   login_bonus.day / premium_pass.day -> day_index; premium_pass.last_at 0 -> NULL (no page yet);
//   follow_rental.day / sphere_rental_day.day -> rental_day;
//   ds_area.last_play -> is_last_play.
// Every other column is copied as it is.
bool rebuild_times_and_booleans(sqlite3* db, sqlite3*) {
    // the counts, for the log (before anything changes)
    struct Bool {
        const char *table, *column;
    };
    for (const Bool& b : {Bool{"follow_rental", "paid"}, Bool{"sphere_rental_day", "paid"}, Bool{"ds_area", "is_new"}, Bool{"ds_area", "last_play"},
                          Bool{"mission", "cleared"}, Bool{"event_rank_score", "fresh"}, Bool{"wboss", "hunt_new"}, Bool{"sphere_cell", "cleared"},
                          Bool{"sphere_cell", "playing"}, Bool{"sphere_rental", "used"}}) {
        const std::string what = std::string(b.table) + "." + b.column;
        log_count(db, ("select count(*) from " + std::string(b.table) + " where " + b.column + " is null or " + b.column + " not in (0, 1)").c_str(),
                  what.c_str(), "NULL -> 0, not 0 / 1 -> 1", 9);
    }
    log_count(db, "select count(*) from favor where tapped_at = 0", "favor.tapped_at", "0 -> NULL (never)", 9);
    log_count(db, "select count(*) from titles where got_at = 0", "titles.got_at", "0 -> NULL", 9);
    log_count(db, "select count(*) from premium_pass where last_at = 0", "premium_pass.last_at", "0 -> NULL (no page yet)", 9);

    // favor.event_drop_at: text -> seconds, in C++ (the server's own parse of what it formatted)
    int64_t times = 0;
    std::vector<std::pair<int64_t, int64_t>> drop_at;  // same_role_id -> seconds
    for (auto& [same_role_id, text] : keyed_texts(db, "select same_role_id, event_drop_at from favor where ifnull(event_drop_at, '') != ''")) {
        if (int64_t t = parse_time_strict(text); t > 0) {
            drop_at.emplace_back(same_role_id, t);
            times++;
        } else {
            LOGW("server", "migrate v9: favor.event_drop_at = '%s' (same_role_id %lld) isn't a time: -> NULL", text.c_str(), (long long)same_role_id);
        }
    }
    if (times) LOGI("server", "migrate v9: favor.event_drop_at: %lld times -> seconds", (long long)times);

    bool ok = run(db, R"(
insert into new_favor (same_role_id, point, tap_count, tapped_at, event_drop_at)
select same_role_id, ifnull(point, 0), ifnull(tap_count, 0), nullif(tapped_at, 0), null from favor)");
    for (size_t k = 0; ok && k < drop_at.size(); k++)
        ok = run(db, "update new_favor set event_drop_at = ? where same_role_id = ?",
                 {Bound::integer(drop_at[k].second), Bound::integer(drop_at[k].first)});
    ok = ok && run(db, "insert into new_titles (id, got_at) select id, nullif(got_at, 0) from titles");
    ok = ok && run(db, "insert into new_login_bonus (id, day_index, last_at) select id, ifnull(day, 0), last_at from login_bonus");
    ok = ok && run(db, R"(
insert into new_premium_pass (id, granted_at, day_index, last_at)
select id, ifnull(granted_at, 0), ifnull(day, 0), nullif(last_at, 0) from premium_pass)");
    ok = ok && run(db, R"(
insert into new_follow_rental (rental_day, count, paid)
select day, ifnull(count, 0), case when ifnull(paid, 0) != 0 then 1 else 0 end from follow_rental)");
    ok = ok && run(db, R"(
insert into new_sphere_rental_day (rental_day, season_id, count, paid)
select day, season_id, ifnull(count, 0), case when ifnull(paid, 0) != 0 then 1 else 0 end from sphere_rental_day)");
    ok = ok && run(db, R"(
insert into new_ds_area (area_id, exp, is_new, is_last_play)
select area_id, ifnull(exp, 0), case when ifnull(is_new, 0) != 0 then 1 else 0 end, case when ifnull(last_play, 0) != 0 then 1 else 0 end
from ds_area)");
    ok = ok && run(db, R"(
insert into new_mission (mission_id, cleared, play_count, clear_count, first_clear_at)
select mission_id, case when ifnull(cleared, 0) != 0 then 1 else 0 end, ifnull(play_count, 0), ifnull(clear_count, 0), first_clear_at
from mission)");
    ok = ok && run(db, R"(
insert into new_event_rank_score (ranking_id, group_id, score, roles, created_at, fresh)
select ranking_id, ifnull(group_id, 0), ifnull(score, 0), roles, created_at, case when ifnull(fresh, 0) != 0 then 1 else 0 end
from event_rank_score)");
    ok = ok && run(db, R"(
insert into new_wboss (boss_id, area_id, wave, n1, n2, n3, a1, a2, a3, required, wave_started_at, last_clear_secs, hunt_until, hunt_new)
select boss_id, area_id, wave, n1, n2, n3, a1, a2, a3, required, wave_started_at, last_clear_secs, hunt_until,
  case when ifnull(hunt_new, 0) != 0 then 1 else 0 end
from wboss)");
    ok = ok && run(db, R"(
insert into new_sphere_cell (asset_id, floor_level, mission_box_id, mission_id, overwrite_enemy_level, cleared, playing, created_at, updated_at)
select asset_id, ifnull(floor_level, 0), mission_box_id, mission_id, ifnull(overwrite_enemy_level, 0),
  case when ifnull(cleared, 0) != 0 then 1 else 0 end, case when ifnull(playing, 0) != 0 then 1 else 0 end, created_at, updated_at
from sphere_cell)");
    ok = ok && run(db, R"(
insert into new_sphere_rental (follow_player_id, used, updated_at)
select follow_player_id, case when ifnull(used, 0) != 0 then 1 else 0 end, updated_at from sphere_rental)");
    for (const char* table : kTimesBooleansTables) {
        ok = ok && run(db, ("drop table " + std::string(table)).c_str());
        ok = ok && run(db, ("alter table new_" + std::string(table) + " rename to " + table).c_str());
    }
    return ok;
}

// ---- step 10: the module tables (PLAN-schema S10, findings F5, F6) -----------------------------
// The tables the modules made for themselves, rebuilt into their 3.2 form (STRICT, 3.2's not-null
// columns and defaults, the boolean checks S9 left to this step) with the foreign keys between
// them, one module group at a time (each group's DDL in kModules, its mapping in its rebuild_*
// function below; all of them one step, version 10). The conventions of 3.1 and 4.1: "none" and
// "never" are NULL (the 0 sentinels go), a dangling reference takes its declared action (NULL for
// SET NULL, the row dropped for a CASCADE child), a NULL in a not-null column is what the readers
// read for it (0), each case logged with its count. As in the earlier steps the tables are created
// as new_X and renamed X after the old X is dropped (4.1), so every reference names the final
// table.
//
// The foreign keys and their actions (PLAN-schema 3.1), by group:
//   deep space:
//     ds_offer.area_id   -> ds_area.area_id  ON DELETE CASCADE (an area's offers)
//     ds_offer.ship_id   -> ds_ship.ship_id  ON DELETE SET NULL (NULL: not on a ship; 0 before)
//     ds_ship.area_id    -> ds_area.area_id  ON DELETE CASCADE (an area's ships)
//     ds_bonus.ship_id   -> ds_ship.ship_id  ON DELETE CASCADE (a ship's bonus values)
//   gacha:
//     gacha_history.character_uid -> roster.uid  ON DELETE SET NULL (the drawn character)
//     gacha_history.item_uid      -> items.uid   ON DELETE SET NULL (the drawn weapon; NULL once
//                                                sold or used up)
//     box_slots.gacha_id          -> box_state.gacha_id  ON DELETE CASCADE (a box's drawn slots;
//                                                BoxGacha writes the box_state row first)
//   daily bonuses:
//     favor_bonus_state.lot_uid -> roster.uid  ON DELETE SET NULL (the favor bonus's character)
//   Sphere 211:
//     sphere_departed.uid -> roster.uid  ON DELETE CASCADE (a character gone has no sortie)
//   the rest (the core's and soa-server's):
//     unlocks.by_mission    -> mission.mission_id  NO ACTION, deferred (MissionEnd records what a
//                                                 first clear unlocks before its mission row)
//     wire_device.player_id -> player.id           ON DELETE SET NULL (NULL: a device seen before
//                                                 the player existed; 0 before)
//   events:
//     wboss_clear.boss_id -> wboss.boss_id  ON DELETE CASCADE, deferred (a boss's cleared waves;
//                                           MissionEnd's contribute() records a clear before
//                                           save() writes a boss met for the first time)
// All immediate (every writer writes the parent first). No ON UPDATE action: a parent key never
// changes. (ds_ship_member.ship_id -> ds_ship is S7's; it names the new ds_ship after the rename.)
const char* const kModules[] = {
    // ---- deep space (api/deepspace/) ----
    // CDeepSpaceShipInfo (b): a ship out or back, until MissionEnd collects it; bonus_set_id /
    // item_id are master references, 0 = none as the wire sends them
    R"(create table new_ds_ship (
  ship_id integer primary key,
  area_id integer not null references ds_area(area_id) on delete cascade,
  mission_id integer not null,
  bonus_set_id integer,
  item_id integer,
  started_at integer not null,
  closed_at integer
) strict)",
    // CDeepSpaceMissionInfo (b): a mission on offer; closed_at NULL: no limit (a rare offer has
    // one); ship_id NULL: not on a ship; updated_at NULL: never (a row from before S10)
    R"(create table new_ds_offer (
  mission_id integer primary key,
  area_id integer not null references ds_area(area_id) on delete cascade,
  bonus_set_id integer,
  closed_at integer,
  ship_id integer references ds_ship(ship_id) on delete set null,
  is_new integer not null default 0 check (is_new in (0, 1)),
  play_count integer not null default 0,
  play_count_daily integer not null default 0,
  play_count_weekly integer not null default 0,
  updated_at integer
) strict)",
    // DeepSpaceBonusAllApplyInfoList (b): a ship's bonus values
    R"(create table new_ds_bonus (
  ship_id integer not null references ds_ship(ship_id) on delete cascade,
  bonus_id integer not null,
  value real not null,
  primary key (ship_id, bonus_id)
) strict)",
    // ---- gacha (api/gacha/) ----
    // a drawn unit (d: our record; the achievements count draws per gacha): the character
    // (role_id, character_uid) or, for a weapon draw (role_id NULL), the item (item_uid); the
    // whole draw's coins on its first unit
    R"(create table new_gacha_history (
  id integer primary key autoincrement,
  gacha_id integer not null,
  at integer not null,
  role_id integer,
  character_uid integer references roster(uid) on delete set null,
  item_uid integer references items(uid) on delete set null,
  rank text not null,
  duplicate integer not null default 0 check (duplicate in (0, 1)),
  cost_free integer not null default 0,
  cost_pay integer not null default 0
) strict)",
    // CStepupGachaInfo (b): a step-up chain's progress (no row: step 1)
    R"(create table new_stepup (
  head integer primary key,
  try_count integer not null default 0,
  restart_count integer not null default 0,
  next_id integer
) strict)",
    // CBoxGachaInfo (b): a box's draws and resets (no row: none)
    R"(create table new_box_state (
  gacha_id integer primary key,
  total_count integer not null default 0,
  reset_count integer not null default 0
) strict)",
    // CBoxGachaDetailInfo (b): the copies drawn of a box's slot (no row: none)
    R"(create table new_box_slots (
  gacha_id integer not null references box_state(gacha_id) on delete cascade,
  slot_id integer not null,
  drawn integer not null default 0,
  primary key (gacha_id, slot_id)
) strict)",
    // ---- events (api/events/) ----
    // a world boss the player met (CWorldBossInfo / CT_WorldBossInfo (b)); columns as S9 left them
    // but hunt_until: the big hunt's end, NULL: none (0 before)
    R"(create table new_wboss (
  boss_id integer primary key,
  area_id integer,
  wave integer default 1,
  n1 integer default 0, n2 integer default 0, n3 integer default 0,
  a1 integer default 0, a2 integer default 0, a3 integer default 0,
  required integer default 0,
  wave_started_at integer,
  last_clear_secs integer default 0,
  hunt_until integer,
  hunt_new integer not null default 0 check (hunt_new in (0, 1))
) strict)",
    // a cleared wave (CWorldBossPlayerInfoList (b)); notified: listed once
    R"(create table new_wboss_clear (
  boss_id integer not null references wboss(boss_id) on delete cascade deferrable initially deferred,
  wave integer not null,
  cleared_at integer,
  notified integer not null default 0 check (notified in (0, 1)),
  primary key (boss_id, wave)
) strict)",
    // the last event mission started (is_last_play (b))
    R"(create table new_event_last (
  id integer primary key check (id = 1),
  mission_id integer,
  area_id integer
) strict)",
    // an event ranking group whose result was received
    R"(create table new_event_rank_received (
  group_id integer primary key,
  received_at integer
) strict)",
    // the characters whose favor event-drop bonus the current play uses (same_role_id, its lots)
    R"(create table new_favor_drop_play (
  same_role_id integer primary key,
  lots integer not null
) strict)",
    // ---- shop (api/shop/) ----
    // CItemShopInfo (b): an item-shop row's count this period, the period's start, the count ever
    // (no row: none)
    R"(create table new_shop_counts (
  id integer primary key,
  num integer not null,
  period integer,
  total integer not null default 0
) strict)",
    // ExchangeShopExCount (b): a contents row's count exchanged (no row: none)
    R"(create table new_exchange_counts (
  id integer primary key,
  num integer not null
) strict)",
    // Subscription (b): a pass the player has, its window and last grant
    R"(create table new_subscription (
  plan_id integer primary key,
  opened_at integer,
  closed_at integer,
  updated_at integer
) strict)",
    // ---- Sphere 211 (api/sphere211/) ----
    // the dive (one row; CSphere211Info / Player.sphere211_* (b)), with the keys that were
    // sphere_meta's until S3 (cycle, season_wins, end_pending, debug_enemy_level: the port's test
    // hook, NULL: off)
    R"(create table new_sphere (
  id integer primary key check (id = 1),
  season_id integer,
  floor_level integer not null default 0,
  asset_group integer not null default 0,
  streak integer not null default 0,
  treasure_total integer not null default 0,
  stamina integer,
  stamina_at integer,
  revive_count integer not null default 0,
  best_floor integer not null default 0,
  entered_at integer,
  clear_asset integer not null default 0,
  lot_floor_num integer not null default 0,
  reroll_count integer not null default 0,
  prev_season integer not null default 0,
  prev_floor integer not null default 0,
  prev_treasure integer not null default 0,
  prev_rank integer not null default 0,
  cycle integer not null default 0,
  season_wins integer not null default 0,
  end_pending integer not null default 0 check (end_pending in (0, 1)),
  debug_enemy_level integer
) strict)",
    // a character that sortied in this dive (出撃済み (b), until 帰還)
    R"(create table new_sphere_departed (
  uid integer primary key references roster(uid) on delete cascade
) strict)",
    // a box gathered in this dive; rank -1 until 帰還 rolls it
    R"(create table new_sphere_box (
  id integer primary key autoincrement,
  floor_level integer not null,
  rank integer not null
) strict)",
    // the local ranking: a season's best floor
    R"(create table new_sphere_rank (
  season_id integer primary key,
  floor_level integer not null,
  entered_at integer
) strict)",
    // the achievements' log: a battle won (kind 1) or a floor entered (kind 2, value = the floor)
    R"(create table new_sphere_log (
  id integer primary key autoincrement,
  kind integer not null,
  value integer,
  at integer not null
) strict)",
    // ---- daily bonuses (api/daily/) ----
    // the favor login bonus (one row): the day it was last drawn (day_at, NULL: never), its tier
    // (master_favor_bonus) and lot character, the last favor stamina heal (healed_at, NULL: never);
    // Player.favor_bonus_received_at / stamina_update_by_favor (b)
    R"(create table new_favor_bonus_state (
  id integer primary key check (id = 1),
  day_at integer,
  bonus_id integer,
  lot_uid integer references roster(uid) on delete set null,
  healed_at integer
) strict)",
    // ---- the rest: the core's tables and soa-server's ----
    // the state's bookkeeping: next_char_uid, next_item_uid, seed (state/state.h)
    R"(create table new_meta (
  key text primary key,
  value text not null
) strict)",
    // StackItemInfo (b): a stack item's count (no row: none)
    R"(create table new_stock (
  master_item_id integer primary key,
  item_type integer not null,
  count integer not null default 0
) strict)",
    // the achievements' action counts (ext::count)
    R"(create table new_counters (
  key text primary key,
  value integer not null
) strict)",
    // CAchievementInfo (b): an achievement's progress and when it was received
    R"(create table new_achievements (
  id integer primary key,
  progress integer,
  received_at integer
) strict)",
    // the current barney chance (Barney's mood, api/items/gear.cpp): its group and type
    R"(create table new_gear_barney (
  id integer primary key check (id = 1),
  group_id integer,
  type integer
) strict)",
    // a mission a first clear unlocked (the menus list them through ActiveMissionList)
    R"(create table new_unlocks (
  mission_id integer primary key,
  mission_type integer not null,
  by_mission integer references mission(mission_id) deferrable initially deferred,
  at integer not null
) strict)",
    // soa-server's record of the bridge's device UUIDs (net/game.cpp map_device)
    R"(create table new_wire_device (
  uuid text primary key,
  player_id integer references player(id) on delete set null,
  device_type integer,
  first_seen integer,
  last_seen integer
) strict)",
};

// The tables step 10 rebuilds (new_X -> X), in kModules' order.
// clang-format off
const char* const kModuleTables[] = {
    "ds_ship", "ds_offer", "ds_bonus",
    "gacha_history", "stepup", "box_state", "box_slots",
    "wboss", "wboss_clear", "event_last", "event_rank_received", "favor_drop_play",
    "shop_counts", "exchange_counts", "subscription",
    "sphere", "sphere_departed", "sphere_box", "sphere_rank", "sphere_log",
    "favor_bonus_state",
    "meta", "stock", "counters", "achievements", "gear_barney", "unlocks", "wire_device",
};
// clang-format on

// The AUTOINCREMENT counter of a table rebuilt from `table` (sqlite_sequence): the old one, -1
// when it has none. The insert into new_X sets the new table's to its largest id (and leaves a 0
// when it copies no row); keep_sequence puts the old one back over it after the rename (an id is
// never reused, also when the old rows are gone: sphere_box after 帰還), and when the old table had
// none, it takes the empty copy's 0 away again (a fresh state keeps no counter until its first row).
int64_t sequence_of(sqlite3* db, const char* table) {
    return count_of(db, ("select ifnull((select seq from sqlite_sequence where name = '" + std::string(table) + "'), -1)").c_str());
}
bool keep_sequence(sqlite3* db, const char* table, int64_t seq) {
    const std::string name = table;
    if (seq < 0) return run(db, ("delete from sqlite_sequence where name = '" + name + "' and seq = 0").c_str());
    if (count_of(db, ("select count(*) from sqlite_sequence where name = '" + name + "'").c_str()))
        return run(db, ("update sqlite_sequence set seq = max(seq, ?) where name = '" + name + "'").c_str(), {Bound::integer(seq)});
    return run(db, ("insert into sqlite_sequence (name, seq) values ('" + name + "', ?)").c_str(), {Bound::integer(seq)});
}

// Deep space (PLAN-schema S10):
//   ds_ship -> new_ds_ship: a ship of no explored area (area_id NULL or not in ds_area) -> dropped
//     with its crew (ds_ship_member, S7's CASCADE child) and its bonus values; mission_id /
//     started_at NULL -> 0;
//   ds_offer -> new_ds_offer: an offer of no explored area -> dropped; closed_at 0 -> NULL (no
//     limit), ship_id 0 or not a ship -> NULL (not on a ship: on offer again), updated_at 0 ->
//     NULL; is_new not 0 -> 1; NULL counts -> 0;
//   ds_bonus -> new_ds_bonus: a row of no ship, or without a bonus id -> dropped; value NULL -> 0.
bool rebuild_deep_space(sqlite3* db) {
    // the counts, for the log (before anything changes)
    log_count(db, "select count(*) from ds_ship where area_id is null or area_id not in (select area_id from ds_area)", "ds_ship.area_id",
              "dangling -> dropped (with its crew and bonus values)", 10);
    log_count(db, "select count(*) from ds_ship where mission_id is null or started_at is null", "ds_ship", "NULL in a not-null column -> 0", 10);
    log_count(db, "select count(*) from ds_offer where area_id is null or area_id not in (select area_id from ds_area)", "ds_offer.area_id",
              "dangling -> dropped", 10);
    log_count(db, "select count(*) from ds_offer where closed_at = 0", "ds_offer.closed_at", "0 -> NULL (no limit)", 10);
    log_count(db, "select count(*) from ds_offer where updated_at = 0", "ds_offer.updated_at", "0 -> NULL (never)", 10);
    log_count(db, "select count(*) from ds_offer where ship_id = 0", "ds_offer.ship_id", "0 -> NULL (not on a ship)", 10);
    log_count(db,
              "select count(*) from ds_offer where ship_id != 0 and ship_id not in "
              "(select ship_id from ds_ship where area_id in (select area_id from ds_area))",
              "ds_offer.ship_id", "dangling -> NULL", 10);
    log_count(db, "select count(*) from ds_offer where is_new is null or is_new not in (0, 1)", "ds_offer.is_new", "NULL -> 0, not 0 / 1 -> 1", 10);
    log_count(db,
              "select count(*) from ds_bonus where bonus_id is null or ship_id is null or ship_id not in "
              "(select ship_id from ds_ship where area_id in (select area_id from ds_area))",
              "ds_bonus", "no ship or no bonus id -> dropped", 10);

    bool ok = run(db, R"(
insert into new_ds_ship (ship_id, area_id, mission_id, bonus_set_id, item_id, started_at, closed_at)
select ship_id, area_id, ifnull(mission_id, 0), bonus_set_id, item_id, ifnull(started_at, 0), closed_at
from ds_ship where area_id in (select area_id from ds_area))");
    ok = ok && run(db, "delete from ds_ship_member where ship_id not in (select ship_id from new_ds_ship)");
    ok = ok && run(db, R"(
insert into new_ds_offer (mission_id, area_id, bonus_set_id, closed_at, ship_id, is_new, play_count, play_count_daily, play_count_weekly,
  updated_at)
select mission_id, area_id, bonus_set_id, nullif(closed_at, 0),
  case when ship_id in (select ship_id from new_ds_ship) then ship_id end,
  case when ifnull(is_new, 0) != 0 then 1 else 0 end, ifnull(play_count, 0), ifnull(play_count_daily, 0), ifnull(play_count_weekly, 0),
  nullif(updated_at, 0)
from ds_offer where area_id in (select area_id from ds_area))");
    ok = ok && run(db, R"(
insert into new_ds_bonus (ship_id, bonus_id, value)
select ship_id, bonus_id, ifnull(value, 0) from ds_bonus where bonus_id is not null and ship_id in (select ship_id from new_ds_ship))");
    return ok;
}

// Gacha (PLAN-schema S10):
//   gacha_history -> new_gacha_history: uid -> character_uid when role_id isn't 0 (a character
//     draw) or item_uid when it is (a weapon draw), NULL when that character or item isn't owned
//     (any more: a weapon sold or used up); role_id 0 -> NULL; duplicate not 0 / 1 -> 1, NULL
//     -> 0; a NULL in a not-null column -> 0 ('' for rank); the AUTOINCREMENT counter kept;
//   stepup, box_state: NULL counts -> 0;
//   box_slots: a slot of a box without a box_state row -> the box's row (0 draws, 0 resets: what
//     the readers read for no row), so the drawn slots stay drawn; a row without a gacha or slot
//     id -> dropped; drawn NULL -> 0.
bool rebuild_gacha(sqlite3* db) {
    // the counts, for the log (before anything changes)
    log_count(db, "select count(*) from gacha_history where role_id = 0", "gacha_history.role_id", "0 -> NULL (a weapon draw)", 10);
    log_count(db, "select count(*) from gacha_history where ifnull(role_id, 0) != 0", "gacha_history.uid", "-> character_uid", 10);
    log_count(db, "select count(*) from gacha_history where ifnull(role_id, 0) = 0", "gacha_history.uid", "-> item_uid", 10);
    log_count(db, "select count(*) from gacha_history where ifnull(role_id, 0) != 0 and uid not in (select uid from roster)",
              "gacha_history.character_uid", "not owned -> NULL", 10);
    log_count(db, "select count(*) from gacha_history where ifnull(role_id, 0) = 0 and uid not in (select uid from items)", "gacha_history.item_uid",
              "not owned (sold, used up) -> NULL", 10);
    log_count(db, "select count(*) from gacha_history where duplicate is null or duplicate not in (0, 1)", "gacha_history.duplicate",
              "NULL -> 0, not 0 / 1 -> 1", 10);
    log_count(db, "select count(distinct gacha_id) from box_slots where gacha_id is not null and gacha_id not in (select gacha_id from box_state)",
              "box_slots.gacha_id", "a box without a box_state row -> its row", 10);
    log_count(db, "select count(*) from box_slots where gacha_id is null or slot_id is null", "box_slots", "no gacha or slot id -> dropped", 10);

    bool ok = run(db, R"(
insert into new_gacha_history (id, gacha_id, at, role_id, character_uid, item_uid, rank, duplicate, cost_free, cost_pay)
select id, ifnull(gacha_id, 0), ifnull(at, 0), nullif(role_id, 0),
  case when ifnull(role_id, 0) != 0 and uid in (select uid from roster) then uid end,
  case when ifnull(role_id, 0) = 0 and uid in (select uid from items) then uid end,
  ifnull(rank, ''), case when ifnull(duplicate, 0) != 0 then 1 else 0 end, ifnull(cost_free, 0), ifnull(cost_pay, 0)
from gacha_history order by id)");
    ok = ok && run(db, R"(
insert into new_stepup (head, try_count, restart_count, next_id)
select head, ifnull(try_count, 0), ifnull(restart_count, 0), next_id from stepup)");
    ok = ok && run(db, R"(
insert into new_box_state (gacha_id, total_count, reset_count)
select gacha_id, ifnull(total_count, 0), ifnull(reset_count, 0) from box_state)");
    ok = ok && run(db, R"(
insert into new_box_state (gacha_id)
select distinct gacha_id from box_slots where gacha_id is not null and gacha_id not in (select gacha_id from box_state))");
    ok = ok && run(db, R"(
insert into new_box_slots (gacha_id, slot_id, drawn)
select gacha_id, slot_id, ifnull(drawn, 0) from box_slots where gacha_id is not null and slot_id is not null)");
    return ok;
}

// Events (PLAN-schema S10):
//   wboss: hunt_until 0 -> NULL (no big hunt); every other column copied;
//   wboss_clear: a clear of a boss without its wboss row, or without a wave -> dropped (the
//     CASCADE child); notified not 0 / 1 -> 1, NULL -> 0;
//   event_last, event_rank_received: copied;
//   favor_drop_play: lots NULL -> 0.
bool rebuild_events(sqlite3* db) {
    // the counts, for the log (before anything changes)
    log_count(db, "select count(*) from wboss where hunt_until = 0", "wboss.hunt_until", "0 -> NULL (no big hunt)", 10);
    log_count(db, "select count(*) from wboss_clear where wave is null or boss_id is null or boss_id not in (select boss_id from wboss)",
              "wboss_clear", "no boss or no wave -> dropped", 10);
    log_count(db, "select count(*) from wboss_clear where notified is null or notified not in (0, 1)", "wboss_clear.notified",
              "NULL -> 0, not 0 / 1 -> 1", 10);
    log_count(db, "select count(*) from favor_drop_play where lots is null", "favor_drop_play.lots", "NULL -> 0", 10);

    bool ok = run(db, R"(
insert into new_wboss (boss_id, area_id, wave, n1, n2, n3, a1, a2, a3, required, wave_started_at, last_clear_secs, hunt_until, hunt_new)
select boss_id, area_id, wave, n1, n2, n3, a1, a2, a3, required, wave_started_at, last_clear_secs, nullif(hunt_until, 0), hunt_new
from wboss)");
    ok = ok && run(db, R"(
insert into new_wboss_clear (boss_id, wave, cleared_at, notified)
select boss_id, wave, cleared_at, case when ifnull(notified, 0) != 0 then 1 else 0 end
from wboss_clear where wave is not null and boss_id in (select boss_id from wboss))");
    ok = ok && run(db, "insert into new_event_last (id, mission_id, area_id) select id, mission_id, area_id from event_last");
    ok = ok && run(db, "insert into new_event_rank_received (group_id, received_at) select group_id, received_at from event_rank_received");
    ok = ok && run(db, "insert into new_favor_drop_play (same_role_id, lots) select same_role_id, ifnull(lots, 0) from favor_drop_play");
    return ok;
}

// Shop (PLAN-schema S10): shop_counts / exchange_counts NULL counts -> 0 (what the readers read);
// subscription copied.
bool rebuild_shop(sqlite3* db) {
    log_count(db, "select count(*) from shop_counts where num is null or total is null", "shop_counts", "NULL count -> 0", 10);
    log_count(db, "select count(*) from exchange_counts where num is null", "exchange_counts.num", "NULL -> 0", 10);
    bool ok = run(db, "insert into new_shop_counts (id, num, period, total) select id, ifnull(num, 0), period, ifnull(total, 0) from shop_counts");
    ok = ok && run(db, "insert into new_exchange_counts (id, num) select id, ifnull(num, 0) from exchange_counts");
    ok = ok && run(db,
                   "insert into new_subscription (plan_id, opened_at, closed_at, updated_at) select plan_id, opened_at, closed_at, updated_at "
                   "from subscription");
    return ok;
}

// Sphere 211 (PLAN-schema S10):
//   sphere: a NULL in a not-null column -> 0 (what the readers read), end_pending not 0 / 1 -> 1;
//   sphere_departed: a character not owned -> dropped (the CASCADE child);
//   sphere_box, sphere_rank, sphere_log: a NULL in a not-null column -> 0; the AUTOINCREMENT
//     counters kept (rebuild_modules).
bool rebuild_sphere(sqlite3* db) {
    log_count(db,
              "select count(*) from sphere where floor_level is null or asset_group is null or streak is null or treasure_total is null or "
              "revive_count is null or best_floor is null or clear_asset is null or lot_floor_num is null or reroll_count is null or "
              "prev_season is null or prev_floor is null or prev_treasure is null or prev_rank is null",
              "sphere", "NULL in a not-null column -> 0", 10);
    log_count(db, "select count(*) from sphere_departed where uid is null or uid not in (select uid from roster)", "sphere_departed.uid",
              "not owned -> dropped", 10);
    log_count(db, "select count(*) from sphere_box where floor_level is null or rank is null", "sphere_box", "NULL -> 0", 10);
    log_count(db, "select count(*) from sphere_rank where floor_level is null", "sphere_rank.floor_level", "NULL -> 0", 10);
    log_count(db, "select count(*) from sphere_log where kind is null or at is null", "sphere_log", "NULL -> 0", 10);
    bool ok = run(db, R"(
insert into new_sphere (id, season_id, floor_level, asset_group, streak, treasure_total, stamina, stamina_at, revive_count, best_floor,
  entered_at, clear_asset, lot_floor_num, reroll_count, prev_season, prev_floor, prev_treasure, prev_rank, cycle, season_wins, end_pending,
  debug_enemy_level)
select id, season_id, ifnull(floor_level, 0), ifnull(asset_group, 0), ifnull(streak, 0), ifnull(treasure_total, 0), stamina, stamina_at,
  ifnull(revive_count, 0), ifnull(best_floor, 0), entered_at, ifnull(clear_asset, 0), ifnull(lot_floor_num, 0), ifnull(reroll_count, 0),
  ifnull(prev_season, 0), ifnull(prev_floor, 0), ifnull(prev_treasure, 0), ifnull(prev_rank, 0), cycle, season_wins,
  case when end_pending != 0 then 1 else 0 end, debug_enemy_level
from sphere)");
    ok = ok && run(db, "insert into new_sphere_departed (uid) select uid from sphere_departed where uid in (select uid from roster)");
    ok = ok &&
         run(db, "insert into new_sphere_box (id, floor_level, rank) select id, ifnull(floor_level, 0), ifnull(rank, 0) from sphere_box order by id");
    ok =
        ok &&
        run(db,
            "insert into new_sphere_rank (season_id, floor_level, entered_at) select season_id, ifnull(floor_level, 0), entered_at from sphere_rank");
    ok = ok &&
         run(db, "insert into new_sphere_log (id, kind, value, at) select id, ifnull(kind, 0), value, ifnull(at, 0) from sphere_log order by id");
    return ok;
}

// Daily bonuses (PLAN-schema S10): favor_bonus_state.day_at / healed_at 0 -> NULL (never: the
// heal's row started day_at at 0, and healed_at defaulted to 0); lot_uid 0 or not owned -> NULL.
bool rebuild_daily(sqlite3* db) {
    log_count(db, "select count(*) from favor_bonus_state where day_at = 0", "favor_bonus_state.day_at", "0 -> NULL (never)", 10);
    log_count(db, "select count(*) from favor_bonus_state where healed_at = 0", "favor_bonus_state.healed_at", "0 -> NULL (never)", 10);
    log_count(db, "select count(*) from favor_bonus_state where lot_uid != 0 and lot_uid not in (select uid from roster)",
              "favor_bonus_state.lot_uid", "dangling -> NULL", 10);
    return run(db, R"(
insert into new_favor_bonus_state (id, day_at, bonus_id, lot_uid, healed_at)
select id, nullif(day_at, 0), bonus_id, case when lot_uid in (select uid from roster) then lot_uid end, nullif(healed_at, 0)
from favor_bonus_state)");
}

// The rest (PLAN-schema S10):
//   meta: value NULL -> '' (what meta() reads);
//   stock: item_type / count NULL -> 0;
//   counters: value NULL -> 0;
//   achievements, gear_barney: copied;
//   unlocks: by_mission 0 or not a mission played -> NULL (nothing reads it but the tools: the
//     record of who unlocked it); mission_type / at NULL -> 0;
//   wire_device: player_id 0 or not the player -> NULL.
bool rebuild_rest(sqlite3* db) {
    log_count(db, "select count(*) from meta where value is null", "meta.value", "NULL -> ''", 10);
    log_count(db, "select count(*) from stock where item_type is null or count is null", "stock", "NULL -> 0", 10);
    log_count(db, "select count(*) from counters where value is null", "counters.value", "NULL -> 0", 10);
    log_count(db, "select count(*) from unlocks where by_mission = 0", "unlocks.by_mission", "0 -> NULL", 10);
    log_count(db, "select count(*) from unlocks where by_mission != 0 and by_mission not in (select mission_id from mission)", "unlocks.by_mission",
              "dangling -> NULL", 10);
    log_count(db, "select count(*) from unlocks where mission_type is null or at is null", "unlocks", "NULL -> 0", 10);
    log_count(db, "select count(*) from wire_device where player_id = 0", "wire_device.player_id", "0 -> NULL (no player yet)", 10);
    log_count(db, "select count(*) from wire_device where player_id != 0 and player_id not in (select id from player)", "wire_device.player_id",
              "dangling -> NULL", 10);
    bool ok = run(db, "insert into new_meta (key, value) select key, ifnull(value, '') from meta");
    ok = ok &&
         run(db, "insert into new_stock (master_item_id, item_type, count) select master_item_id, ifnull(item_type, 0), ifnull(count, 0) from stock");
    ok = ok && run(db, "insert into new_counters (key, value) select key, ifnull(value, 0) from counters");
    ok = ok && run(db, "insert into new_achievements (id, progress, received_at) select id, progress, received_at from achievements");
    ok = ok && run(db, "insert into new_gear_barney (id, group_id, type) select id, group_id, type from gear_barney");
    ok = ok && run(db, R"(
insert into new_unlocks (mission_id, mission_type, by_mission, at)
select mission_id, ifnull(mission_type, 0), case when by_mission in (select mission_id from mission) then by_mission end, ifnull(at, 0)
from unlocks)");
    ok = ok && run(db, R"(
insert into new_wire_device (uuid, player_id, device_type, first_seen, last_seen)
select uuid, case when player_id in (select id from player) then player_id end, device_type, first_seen, last_seen from wire_device)");
    return ok;
}

// Step 10's data mapping (PLAN-schema S10): each group's rows into its new tables (the functions
// above), then the old tables go and the new ones take their names; the AUTOINCREMENT counters
// are kept.
bool rebuild_modules(sqlite3* db, sqlite3*) {
    std::vector<std::pair<const char*, int64_t>> counters;
    for (const char* table : {"gacha_history", "sphere_box", "sphere_log"}) counters.emplace_back(table, sequence_of(db, table));
    bool ok = rebuild_deep_space(db) && rebuild_gacha(db) && rebuild_events(db) && rebuild_shop(db) && rebuild_sphere(db) && rebuild_daily(db) &&
              rebuild_rest(db);
    for (const char* table : kModuleTables) ok = ok && run(db, ("drop table " + std::string(table)).c_str());
    for (const char* table : kModuleTables) ok = ok && run(db, ("alter table new_" + std::string(table) + " rename to " + table).c_str());
    for (auto& [table, seq] : counters) ok = ok && keep_sequence(db, table, seq);
    return ok;
}

// ---- step 11: the story campaign's progress (PLAN-schema S12) ------------------------------
//
// Until version 11 the campaign (api/campaign/progress.cpp) kept its progress in a text file of
// the data dir, <data>/server_campaign.txt: "clear <mission id>" per cleared mission and
// "last <mission id>" for the last one played. Two tables hold it now:
//   campaign_clear: one row per cleared mission (a master_mission or master_world_map_mission id:
//     a master reference, state::check's, not a foreign key);
//   campaign_last: the last mission played (one row, id 1; no row: none), a cleared mission:
//     mission_id -> campaign_clear ON DELETE CASCADE (the last play goes with its clear; a
//     clear is written before it, clear_mission's order).
const char* const kCampaign[] = {
    "create table campaign_clear (mission_id integer primary key) strict",
    "create table campaign_last (id integer primary key check (id = 1), "
    "mission_id integer not null references campaign_clear(mission_id) on delete cascade) strict",
};

// Step 11's import: the data dir's server_campaign.txt, read as the campaign read it (the same
// fscanf loop: it stops at the first line that isn't "<word> <number>"; a number is cut to 32
// bits; a repeated clear counts once; the last "last" line wins; "last 0" is none). Unknown
// mission ids are kept (state::check reports them; the master isn't used). A "last" that isn't
// among the clears (clear_mission records the clear first, so only an edited file has one) is
// dropped (LOGW). No file: nothing (a state that never played the campaign, or a new data dir).
bool import_campaign(sqlite3* db, const std::string& data_dir) {
    std::string path = data_dir + "/" + kCampaignFile;
    FILE* f = fopen(path.c_str(), "r");
    if (!f) return true;
    std::set<uint32_t> cleared;
    uint32_t last = 0;
    char word[32];
    unsigned long value;
    while (fscanf(f, "%31s %lu", word, &value) == 2) {
        if (!strcmp(word, "clear")) cleared.insert((uint32_t)value);
        else if (!strcmp(word, "last")) last = (uint32_t)value;
    }
    fclose(f);
    bool ok = true;
    for (uint32_t id : cleared) ok = ok && run(db, "insert into campaign_clear (mission_id) values (?)", {Bound::integer(id)});
    if (last && !cleared.count(last)) {
        LOGW("server", "migrate v11: campaign_last: the last play %u isn't a cleared mission: dropped", last);
        last = 0;
    }
    if (last) ok = ok && run(db, "insert into campaign_last (id, mission_id) values (1, ?)", {Bound::integer(last)});
    LOGI("server", "migrate v11: %s: %zu cleared missions%s imported", path.c_str(), cleared.size(), last ? " and the last play" : "");
    return ok;
}

// After step 11's commit: the imported file becomes <file>.migrated (kept: with the .bak-v10 copy
// of the state it is the way back to an older build); a stale file is never imported twice.
void retire_campaign_file(const std::string& data_dir) {
    std::string path = data_dir + "/" + kCampaignFile, to = data_dir + "/" + kCampaignFileMigrated;
    if (FILE* f = fopen(path.c_str(), "r")) fclose(f);
    else return;
    if (rename(path.c_str(), to.c_str()) == 0) LOGI("server", "migrate v11: %s imported into the state DB, kept as %s", path.c_str(), to.c_str());
    else
        LOGW("server", "migrate v11: %s imported into the state DB, but it can't be renamed to %s (it is ignored from now on)", path.c_str(),
             to.c_str());
}

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
        {3, "keys out of meta, sphere_meta and counters (PLAN-schema S3)", {std::begin(kKeysOut), std::end(kKeysOut)}, move_keys},
        {4,
         "the roster: roster_ext and assist merged, roster and player rebuilt with their foreign keys (PLAN-schema S4)",
         {std::begin(kRoster), std::end(kRoster)},
         rebuild_roster_and_player},
        {5,
         "items and gear: items and gear_items rebuilt STRICT, gear set in a weapon references it (PLAN-schema S5)",
         {std::begin(kItemsGear), std::end(kItemsGear)},
         rebuild_items_and_gear},
        {6,
         "parties: party merged into party_member, party_set and party_member rebuilt with their foreign keys (PLAN-schema S6)",
         {std::begin(kParty), std::end(kParty)},
         rebuild_parties},
        {7,
         "the battle in progress: play_ext merged into play, the party as play_member rows, a ship's crew as ds_ship_member rows, "
         "ds_log with its id (PLAN-schema S7)",
         {std::begin(kPlay), std::end(kPlay)},
         rebuild_play},
        {8,
         "presents: present_texts merged into presents (text), presents rebuilt STRICT, a wallet present's content_id NULL (PLAN-schema S8)",
         {std::begin(kPresents), std::end(kPresents)},
         rebuild_presents},
        {9,
         "times and booleans: favor's times as seconds (NULL: never), day counters day_index, rental days rental_day, "
         "ds_area.is_last_play, the boolean checks; twelve tables rebuilt STRICT (PLAN-schema S9)",
         {std::begin(kTimesBooleans), std::end(kTimesBooleans)},
         rebuild_times_and_booleans},
        {10,
         "the module tables: rebuilt STRICT with their foreign keys and checks, the 0 sentinels NULL (PLAN-schema S10)",
         {std::begin(kModules), std::end(kModules)},
         rebuild_modules},
        {11,
         "the story campaign's progress: campaign_clear and campaign_last, imported from the data dir's server_campaign.txt (PLAN-schema S12)",
         {std::begin(kCampaign), std::end(kCampaign)},
         nullptr,
         import_campaign,
         retire_campaign_file},
    };
    return s;
}

}  // namespace soa::server::state
