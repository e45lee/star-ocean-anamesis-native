// Unit tests of the state schema's migrations (state/schema.h, state/state.h; server/PLAN-schema.md
// 4.2). Run in --selftest; not differential (the server has no guest counterpart). They load the
// committed v0 fixture server/tests/fixtures/state-v0.sql (tools/make_state_fixture.py). Test names
// are their seeds (testing.h).
#include <sqlite3.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "core/time.h"  // parse_time_strict (S9)
#include "soaserver/config.h"
#include "soaserver/native_test.h"
#include "state/state.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

using ext::Row;
using ext::Sql;

// A scratch state file under /tmp (and its -wal / -shm / .bak-v<N> files, removed again).
struct TempDb {
    std::string path;
    explicit TempDb(const char* name) : path("/tmp/soa-schema-" + std::to_string(getpid()) + "-" + name + ".sqlite3") { remove_all(); }
    ~TempDb() { remove_all(); }
    void remove_all() {
        for (const char* suffix : {"",         "-wal",
                                   "-shm",     "-journal",
                                   ".bak-v0",  ".bak-v0-journal",
                                   ".bak-v1",  ".bak-v1-journal",
                                   ".bak-v2",  ".bak-v2-journal",
                                   ".bak-v3",  ".bak-v3-journal",
                                   ".bak-v4",  ".bak-v4-journal",
                                   ".bak-v5",  ".bak-v5-journal",
                                   ".bak-v6",  ".bak-v6-journal",
                                   ".bak-v7",  ".bak-v7-journal",
                                   ".bak-v8",  ".bak-v8-journal",
                                   ".bak-v9",  ".bak-v9-journal",
                                   ".bak-v10", ".bak-v10-journal",
                                   ".bak-v11", ".bak-v11-journal"})
            unlink((path + suffix).c_str());
    }
};

// A scratch data dir under /tmp for a step's side files (S12: the campaign's server_campaign.txt
// and its .migrated), removed again.
struct TempDir {
    std::string path;
    explicit TempDir(const char* name) : path("/tmp/soa-schema-" + std::to_string(getpid()) + "-" + name + ".d") {
        remove_all();
        mkdir(path.c_str(), 0755);
    }
    ~TempDir() { remove_all(); }
    void remove_all() {
        for (const char* f : {state::kCampaignFile, state::kCampaignFileMigrated}) unlink((path + "/" + f).c_str());
        rmdir(path.c_str());
    }
    void write(const char* name, const std::string& text) const { std::ofstream(path + "/" + name, std::ios::binary) << text; }
    bool has(const char* name) const { return access((path + "/" + name).c_str(), F_OK) == 0; }
    std::string read(const char* name) const {
        std::ifstream f(path + "/" + name, std::ios::binary);
        return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    }
};

// The fixture's SQL; "" (and the test failed) when it's missing.
std::string fixture_sql(testing::Context& t) {
    std::string p = find_repo_file("server/tests/fixtures/state-v0.sql");
    std::ifstream f(p);
    if (p.empty() || !f) {
        t.fail("server/tests/fixtures/state-v0.sql not found (tools/make_state_fixture.py writes it)");
        return "";
    }
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

// Writes the v0 fixture into a new file at `path`; false (the test failed) when it can't.
bool write_fixture(testing::Context& t, const std::string& path) {
    std::string sql = fixture_sql(t);
    if (sql.empty()) return false;
    Sql db;
    if (!db.open(path, false)) return t.fail("open %s", path.c_str()), false;
    bool ok = db.exec(sql);
    db.close();
    if (!ok) t.fail("the fixture doesn't load");
    return ok;
}

// sqlite_master as "type name tbl_name: sql" lines, sorted (the schema, as a fresh-vs-migrated
// comparison sees it; root pages left out).
std::vector<std::string> schema_of(Sql& db) {
    std::vector<std::string> out;
    db.q("select type, name, tbl_name, ifnull(sql, '') as sql from sqlite_master order by type, name", {},
         [&](const Row& r) { out.push_back(r.s("type") + " " + r.s("name") + " " + r.s("tbl_name") + ": " + r.s("sql")); });
    return out;
}

// Every table's rows as text, sorted (the data a migration without a mapping must keep).
std::map<std::string, std::vector<std::string>> rows_of(Sql& db) {
    std::vector<std::string> tables;
    db.q("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name", {},
         [&](const Row& r) { tables.push_back(r.s("name")); });
    std::map<std::string, std::vector<std::string>> out;
    for (const std::string& table : tables) {
        std::vector<std::string>& rows = out[table];
        sqlite3_stmt* s = nullptr;
        sqlite3_prepare_v2(db.h, ("select * from \"" + table + "\"").c_str(), -1, &s, nullptr);
        while (s && sqlite3_step(s) == SQLITE_ROW) {
            std::string row;
            for (int c = 0; c < sqlite3_column_count(s); c++) {
                const unsigned char* v = sqlite3_column_text(s, c);
                row += std::to_string(sqlite3_column_type(s, c)) + ":" + (v ? (const char*)v : "") + "|";
            }
            rows.push_back(row);
        }
        sqlite3_finalize(s);
        std::sort(rows.begin(), rows.end());
    }
    return out;
}

std::set<std::string> columns_of(Sql& db, const std::string& table) {
    std::set<std::string> out;
    db.q("select name from pragma_table_info(?)", {table}, [&](const Row& r) { out.insert(r.s("name")); });
    return out;
}

int fk_violations(Sql& db) {
    int n = 0;
    db.q("pragma foreign_key_check", {}, [&](const Row&) { n++; });
    return n;
}

// A fresh state and the v0 fixture migrated have the same schema and user_version (PLAN-schema
// 4.1: one path, so a new state and an upgraded one are the same by construction).
NATIVE_TEST("server/schema-fresh-equals-migrated") {
    TempDb fresh("fresh"), old("old");
    Sql a, b;
    if (!a.open(fresh.path, false)) return t.fail("open fresh");
    t.expect_eq(state::user_version(a.h), 0, "a new file is version 0");
    t.expect_eq(state::open_and_migrate(a.h, fresh.path), true, "fresh: migrated");
    if (!write_fixture(t, old.path)) return a.close();
    if (!b.open(old.path, false)) return a.close(), t.fail("open fixture");
    t.expect_eq(state::user_version(b.h), 0, "the fixture is version 0");
    t.expect_eq(state::open_and_migrate(b.h, old.path), true, "fixture: migrated");
    t.expect_eq(state::user_version(a.h), state::kSchemaVersion, "fresh: this build's version");
    t.expect_eq(state::user_version(b.h), state::kSchemaVersion, "fixture: this build's version");
    std::vector<std::string> sa = schema_of(a), sb = schema_of(b);
    if (!t.expect_eq(sa, sb, "fresh and migrated schemas")) {
        std::set<std::string> ia(sa.begin(), sa.end()), ib(sb.begin(), sb.end());
        for (auto& s : sa)
            if (!ib.count(s)) t.fail("only fresh: %s", s.c_str());
        for (auto& s : sb)
            if (!ia.count(s)) t.fail("only migrated: %s", s.c_str());
    }
    t.expect_eq(a.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)53,
                "the 58 baseline tables less the 4 S2 drops, less sphere_meta, plus ds_state (S3), less roster_ext and assist (S4), less party (S6), "
                "less play_ext, plus play_member and ds_ship_member (S7), less present_texts (S8), plus campaign_clear and campaign_last (S12)");
    t.expect_eq(a.one("select count(*) from sqlite_master where type = 'index' and name like 'roster_%'", {}), (int64_t)3,
                "roster's three unique indexes (S4)");
    t.expect_eq(a.one("select count(*) from sqlite_master where type = 'index' and name = 'gear_items_slot'", {}), (int64_t)1,
                "gear_items' slot index (S5)");
    t.expect_eq(a.one("select count(*) from party_set", {}), (int64_t)0, "no player: no party set rows (the seed / CreatePlayer add them)");
    for (const char* gone :
         {"view_flags", "gear", "box_gacha", "planets", "sphere_meta", "roster_ext", "assist", "party", "play_ext", "present_texts"})
        t.expect_eq(a.one("select count(*) from sqlite_master where name = ?", {gone}), (int64_t)0, (std::string(gone) + " not there").c_str());
    t.expect_eq(a.one("select count(*) from sqlite_master where name = 'ds_state'", {}), (int64_t)1, "ds_state there");
    t.expect_eq(a.one("select count(*) from sqlite_master where name = 'wire_device'", {}), (int64_t)1, "wire_device on every route");
    // the new file has no player: nothing to back up
    t.expect_eq(access((fresh.path + ".bak-v0").c_str(), F_OK) != 0, true, "no backup of a new file");
    a.close();
    b.close();
}

// Version 1 (the baseline) on the v0 fixture (migrated to 1 only): no data mapping, so every row stays as it was, the
// dirt included (the later steps clean it); the file is backed up first; foreign keys are on; the
// master references resolve. A table missing a baseline column gets it, with its default.
NATIVE_TEST("server/schema-migrate-v1") {
    TempDb old("v1");
    if (!write_fixture(t, old.path)) return;
    Sql db;
    if (!db.open(old.path, false)) return t.fail("open");
    auto before = rows_of(db);
    t.expect_eq(before.size(), (size_t)58, "the fixture has every table");
    for (auto& [table, rows] : before)
        if (rows.empty()) t.fail("the fixture's %s is empty", table.c_str());
    t.expect_eq(state::open_and_migrate(db.h, old.path, 1), true, "migrated");
    t.expect_eq(state::user_version(db.h), 1, "user_version 1");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    t.expect_eq(rows_of(db) == before, true, "every row kept");
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    if (ext::Sql* m = test_master())
        for (const auto& d : state::check(db.h, m->h)) t.fail("%s", state::describe(d).c_str());
    // the dirt is still there (S1 maps nothing)
    t.expect_eq(db.one("select count(*) from party_set where party_id = 1", {}), (int64_t)0, "party 1 has no party_set row");
    t.expect_eq(db.one("select count(*) from roster_ext where uid not in (select uid from roster)", {}), (int64_t)1, "the orphan roster_ext");
    t.expect_eq(db.one("select count(*) from wire_device where player_id = 0", {}), (int64_t)1, "a device without a player");
    db.close();

    // the backup: the v0 file as it was
    Sql bak;
    if (!bak.open(old.path + ".bak-v0", true)) return t.fail("no %s.bak-v0", old.path.c_str());
    t.expect_eq(state::user_version(bak.h), 0, "the backup is version 0");
    t.expect_eq(rows_of(bak) == before, true, "the backup's rows");
    bak.close();

    // again: already at this version, nothing to do
    Sql again;
    if (!again.open(old.path, false)) return t.fail("reopen");
    unlink((old.path + ".bak-v0").c_str());
    t.expect_eq(state::open_and_migrate(again.h, old.path, 1), true, "a current file opens");
    t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK) != 0, true, "no backup of a current file");
    again.close();

    // the column repair: a legacy table without a baseline column gets it, with the baseline default
    TempDb legacy("repair");
    if (!write_fixture(t, legacy.path)) return;
    Sql l;
    if (!l.open(legacy.path, false)) return t.fail("open legacy");
    l.exec("alter table roster_ext drop column equip_skill3; alter table follow_rental drop column paid");
    t.expect_eq(columns_of(l, "roster_ext").count("equip_skill3"), (size_t)0, "the legacy table lacks the column");
    t.expect_eq(state::open_and_migrate(l.h, legacy.path, 1), true, "repaired");
    t.expect_eq(columns_of(l, "roster_ext").count("equip_skill3"), (size_t)1, "roster_ext.equip_skill3 added");
    t.expect_eq(columns_of(l, "follow_rental").count("paid"), (size_t)1, "follow_rental.paid added");
    t.expect_eq(l.one("select count(*) from roster_ext where equip_skill3 is not 0", {}), (int64_t)0, "with its default 0");
    t.expect_eq(l.one("select count(*) from follow_rental where paid is not 0", {}), (int64_t)0, "not null default 0");
    t.expect_eq(state::user_version(l.h), 1, "repaired: version 1");
    l.close();
}

// Version 2 (PLAN-schema S2: drop the dead) on the v0 fixture: the four dead tables and three
// dead columns are gone, every other row is kept (the three tables' rows less the dropped column),
// and a version 1 file (the path an S1 state takes) is backed up as .bak-v1 first.
NATIVE_TEST("server/schema-migrate-v2") {
    static const std::set<std::string> kDroppedTables = {"view_flags", "gear", "box_gacha", "planets"};
    static const std::map<std::string, std::string> kDroppedColumns = {{"roster", "favor"}, {"mission", "best_rank"}, {"exchange_counts", "shop_id"}};
    // every table's rows as text, without the dropped tables and columns
    auto kept_rows = [](Sql& db) {
        std::map<std::string, std::vector<std::string>> out;
        std::vector<std::string> tables;
        db.q("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name", {},
             [&](const Row& r) { tables.push_back(r.s("name")); });
        for (const std::string& table : tables) {
            if (kDroppedTables.count(table)) continue;
            std::string cols;
            db.q("select name from pragma_table_info(?) order by cid", {table}, [&](const Row& r) {
                auto d = kDroppedColumns.find(table);
                if (d != kDroppedColumns.end() && d->second == r.s("name")) return;
                cols += (cols.empty() ? "\"" : ", \"") + r.s("name") + "\"";
            });
            std::vector<std::string>& rows = out[table];
            sqlite3_stmt* s = nullptr;
            sqlite3_prepare_v2(db.h, ("select " + cols + " from \"" + table + "\"").c_str(), -1, &s, nullptr);
            while (s && sqlite3_step(s) == SQLITE_ROW) {
                std::string row;
                for (int c = 0; c < sqlite3_column_count(s); c++) {
                    const unsigned char* v = sqlite3_column_text(s, c);
                    row += std::to_string(sqlite3_column_type(s, c)) + ":" + (v ? (const char*)v : "") + "|";
                }
                rows.push_back(row);
            }
            sqlite3_finalize(s);
            std::sort(rows.begin(), rows.end());
        }
        return out;
    };
    TempDb old("v2");
    if (!write_fixture(t, old.path)) return;
    Sql db;
    if (!db.open(old.path, false)) return t.fail("open");
    auto before = kept_rows(db);
    for (const std::string& table : kDroppedTables)
        t.expect_eq(db.one("select count(*) from \"" + table + "\"", {}) > 0, true, ("the fixture has rows in " + table).c_str());
    // v0 -> v1, then (as an S1 state upgraded by this build) v1 -> v2
    t.expect_eq(state::open_and_migrate(db.h, old.path, 1), true, "migrated to 1");
    db.close();
    unlink((old.path + ".bak-v0").c_str());
    if (!db.open(old.path, false)) return t.fail("reopen");
    t.expect_eq(state::open_and_migrate(db.h, old.path, 2), true, "migrated to 2");
    t.expect_eq(state::user_version(db.h), 2, "user_version 2");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    for (const std::string& table : kDroppedTables)
        t.expect_eq(db.one("select count(*) from sqlite_master where name = ?", {table}), (int64_t)0, (table + " dropped").c_str());
    for (const auto& [table, column] : kDroppedColumns)
        t.expect_eq(columns_of(db, table).count(column), (size_t)0, (table + "." + column + " dropped").c_str());
    t.expect_eq(kept_rows(db) == before, true, "every other row and column kept");
    t.expect_eq(db.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)54, "54 tables");
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    if (ext::Sql* m = test_master())
        for (const auto& d : state::check(db.h, m->h)) t.fail("%s", state::describe(d).c_str());
    db.close();
    Sql bak;
    if (!bak.open(old.path + ".bak-v1", true)) return t.fail("no %s.bak-v1", old.path.c_str());
    t.expect_eq(state::user_version(bak.h), 1, "the backup is version 1");
    t.expect_eq(bak.one("select count(*) from sqlite_master where name = 'planets'", {}), (int64_t)1, "the backup keeps the v1 tables");
    bak.close();
}

// Version 3 (PLAN-schema S3: keys out of meta, sphere_meta and counters). The fixture has the seed's
// keys (tutorial_status 9, view_status all ones, a selected title, sphere_meta cycle); the test plants
// the rest of S3's cases. (1) v0 -> v3 at once: title '0' (taken off) -> NULL, a dangling
// support_uid -> NULL, the deep-space keys, the popup counter (2 -> 1), the dive's keys; every other
// row is kept (compared with the same file migrated to 2), the keys are gone, sphere_meta dropped.
// (2) v2 -> v3 (an S2 state, backed up as .bak-v2): a selected title and an owned support character
// kept, no deep-space key (no ds_state row), sphere_meta without a dive (dropped).
NATIVE_TEST("server/schema-migrate-v3") {
    // `table`'s rows over the columns `cols` ("a", "b", ...), as text, sorted
    auto rows = [](Sql& db, const std::string& table, const std::string& cols) {
        std::vector<std::string> out;
        sqlite3_stmt* s = nullptr;
        sqlite3_prepare_v2(db.h, ("select " + cols + " from \"" + table + "\"").c_str(), -1, &s, nullptr);
        while (s && sqlite3_step(s) == SQLITE_ROW) {
            std::string row;
            for (int c = 0; c < sqlite3_column_count(s); c++) {
                const unsigned char* v = sqlite3_column_text(s, c);
                row += std::to_string(sqlite3_column_type(s, c)) + ":" + (v ? (const char*)v : "") + "|";
            }
            out.push_back(row);
        }
        sqlite3_finalize(s);
        std::sort(out.begin(), out.end());
        return out;
    };
    auto column_list = [](Sql& db, const std::string& table) {
        std::string cols;
        db.q("select name from pragma_table_info(?) order by cid", {table},
             [&](const Row& r) { cols += (cols.empty() ? "\"" : ", \"") + r.s("name") + "\""; });
        return cols;
    };
    auto keys = [](Sql& db, const char* table) {
        std::set<std::string> out;
        db.q(std::string("select key from ") + table, {}, [&](const Row& r) { out.insert(r.s("key")); });
        return out;
    };
    static const std::set<std::string> kMovedMeta = {"tutorial_status", "view_status",  "view_status2",         "kiyaku_version",
                                                     "title",           "support_uid",  "ds_time_saving_count", "ds_time_saving_day",
                                                     "ds_limit_day",    "ds_limit_week"};

    // ---- (1) v0 -> v3 -------------------------------------------------------------------------------
    const char* kDirt =
        "update meta set value = '0' where key = 'title';"
        "insert into meta (key, value) values ('support_uid', '9999');"  // no such roster uid
        "insert into meta (key, value) values ('kiyaku_version', '20200319');"
        "insert into meta (key, value) values ('ds_time_saving_count', '2');"
        "insert into meta (key, value) values ('ds_time_saving_day', '1790755200');"
        "insert into meta (key, value) values ('ds_limit_day', '1790755200');"
        "insert into meta (key, value) values ('ds_limit_week', '1790582400');"
        "insert into counters (key, value) values ('login_bonus_popup_pending', 2);"
        "insert into sphere_meta (key, value) values ('season_wins', 3), ('end_pending', 1), ('test_enemy_level', 30);";
    TempDb ref_file("v3-ref"), old("v3");
    if (!write_fixture(t, ref_file.path) || !write_fixture(t, old.path)) return;
    Sql ref, db;
    if (!ref.open(ref_file.path, false) || !db.open(old.path, false)) return t.fail("open");
    t.expect_eq(ref.exec(kDirt) && db.exec(kDirt), true, "the S3 dirt planted");
    t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 2), true, "the reference: migrated to 2");
    t.expect_eq(state::open_and_migrate(db.h, old.path, 3), true, "migrated to 3");
    t.expect_eq(state::user_version(db.h), 3, "user_version 3");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK) == 0, true, "the v0 file backed up");
    // every other row kept: each version-2 table's rows over its version-2 columns
    std::vector<std::string> tables;
    ref.q("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name", {},
          [&](const Row& r) { tables.push_back(r.s("name")); });
    for (const std::string& table : tables) {
        if (table == "meta" || table == "counters" || table == "sphere_meta") continue;
        std::string cols = column_list(ref, table);
        if (rows(ref, table, cols) != rows(db, table, cols)) t.fail("%s: rows changed", table.c_str());
    }
    std::set<std::string> meta_kept;
    for (const std::string& k : keys(ref, "meta"))
        if (!kMovedMeta.count(k)) meta_kept.insert(k);
    t.expect_eq(keys(db, "meta"), meta_kept, "meta: the moved keys gone, the rest kept");
    t.expect_eq(meta_kept, std::set<std::string>{"next_char_uid", "next_item_uid", "seed"}, "meta: the uid counters and the seed");
    auto meta_value = [](Sql& d, const std::string& k) {
        std::string v;
        d.q("select value from meta where key = ?", {k}, [&](const Row& r) { v = r.s("value"); });
        return v;
    };
    for (const std::string& k : meta_kept) t.expect_eq(meta_value(db, k), meta_value(ref, k), ("meta " + k + " kept").c_str());
    std::vector<std::string> counters_kept;
    for (const std::string& r : rows(ref, "counters", "key, value"))
        if (r.find("login_bonus_popup_pending") == std::string::npos) counters_kept.push_back(r);
    t.expect_eq(rows(db, "counters", "key, value"), counters_kept, "counters: the popup flag gone, the rest kept");
    t.expect_eq(db.one("select count(*) from sqlite_master where name = 'sphere_meta'", {}), (int64_t)0, "sphere_meta dropped");
    bool player_row = false;
    db.q("select * from player", {}, [&](const Row& p) {
        player_row = true;
        t.expect_eq(p.i("tutorial_status"), (int64_t)9, "tutorial_status");
        t.expect_eq((u64)p.i("view_status"), ~0ull, "view_status: the u64 word's bits (strtoull, not a saturating cast)");
        t.expect_eq((u64)p.i("view_status2"), ~0ull, "view_status2");
        t.expect_eq(p.s("kiyaku_version"), std::string("20200319"), "kiyaku_version");
        t.expect_eq(p.null("title_id"), true, "title '0' -> NULL");
        t.expect_eq(p.null("support_uid"), true, "a dangling support_uid -> NULL");
        t.expect_eq(p.i("time_saving_count"), (int64_t)2, "time_saving_count");
        t.expect_eq(p.i("time_saving_day"), (int64_t)1790755200, "time_saving_day");
        t.expect_eq(p.i("login_bonus_popup_pending"), (int64_t)1, "the popup flag (2 -> 1)");
    });
    t.expect_eq(player_row, true, "the player row");
    t.expect_eq(rows(db, "ds_state", "id, limit_day, limit_week"), std::vector<std::string>{"1:1|1:1790755200|1:1790582400|"}, "ds_state");
    t.expect_eq(rows(db, "sphere", "cycle, season_wins, end_pending, debug_enemy_level"), std::vector<std::string>{"1:1|1:3|1:1|1:30|"},
                "the dive's keys");
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    if (ext::Sql* m = test_master())
        for (const auto& d : state::check(db.h, m->h)) t.fail("%s", state::describe(d).c_str());
    ref.close();
    db.close();

    // ---- (2) v2 -> v3 -------------------------------------------------------------------------------
    TempDb v2("v3-from-v2");
    if (!write_fixture(t, v2.path)) return;
    Sql f;
    if (!f.open(v2.path, false)) return t.fail("open v2");
    t.expect_eq(f.exec("insert into meta (key, value) values ('support_uid', (select min(uid) from roster));"
                       "delete from sphere;"
                       "insert into sphere_meta (key, value) values ('season_wins', 2);"),
                true, "the v2 cases planted");
    int64_t support = f.one("select min(uid) from roster", {});
    t.expect_eq(state::open_and_migrate(f.h, v2.path, 2), true, "migrated to 2");
    f.close();
    unlink((v2.path + ".bak-v0").c_str());
    if (!f.open(v2.path, false)) return t.fail("reopen v2");
    t.expect_eq(state::user_version(f.h), 2, "a version 2 file");
    t.expect_eq(state::open_and_migrate(f.h, v2.path, 3), true, "v2 -> v3");
    t.expect_eq(state::user_version(f.h), 3, "user_version 3");
    f.q("select * from player", {}, [&](const Row& p) {
        t.expect_eq(p.i("title_id"), (int64_t)340997325, "a selected title kept");
        t.expect_eq(p.i("support_uid"), support, "an owned support character kept");
        t.expect_eq(p.s("kiyaku_version"), std::string(), "no kiyaku_version: ''");
        t.expect_eq(p.i("time_saving_count"), (int64_t)0, "no count: 0");
        t.expect_eq(p.null("time_saving_day"), true, "no day: NULL");
        t.expect_eq(p.i("login_bonus_popup_pending"), (int64_t)0, "no popup flag: 0");
    });
    t.expect_eq(f.one("select count(*) from ds_state", {}), (int64_t)0, "no deep-space key: no ds_state row");
    t.expect_eq(f.one("select count(*) from sphere", {}), (int64_t)0, "no dive: sphere_meta's keys dropped, no row made");
    t.expect_eq(f.one("select count(*) from sqlite_master where name = 'sphere_meta'", {}), (int64_t)0, "sphere_meta dropped");
    t.expect_eq(fk_violations(f), 0, "foreign_key_check");
    f.close();
    Sql bak;
    if (!bak.open(v2.path + ".bak-v2", true)) return t.fail("no %s.bak-v2", v2.path.c_str());
    t.expect_eq(state::user_version(bak.h), 2, "the backup is version 2");
    t.expect_eq(bak.one("select count(*) from sphere_meta", {}) > 0, true, "the backup keeps sphere_meta");
    bak.close();
}

// `table`'s rows over the columns `cols` ("a, b, ..."), as text, in the order `cols` lists them
// (sorted).
std::vector<std::string> rows_over(Sql& db, const std::string& table, const std::string& cols, const std::string& where = "") {
    std::vector<std::string> out;
    sqlite3_stmt* s = nullptr;
    sqlite3_prepare_v2(db.h, ("select " + cols + " from \"" + table + "\"" + (where.empty() ? "" : " where " + where)).c_str(), -1, &s, nullptr);
    while (s && sqlite3_step(s) == SQLITE_ROW) {
        std::string row;
        for (int c = 0; c < sqlite3_column_count(s); c++) {
            const unsigned char* v = sqlite3_column_text(s, c);
            row += std::to_string(sqlite3_column_type(s, c)) + ":" + (v ? (const char*)v : "") + "|";
        }
        out.push_back(row);
    }
    sqlite3_finalize(s);
    std::sort(out.begin(), out.end());
    return out;
}

// Version 4 (PLAN-schema S4: the roster). The fixture has S4's dirt (a roster weapon_uid naming a
// missing item, an orphan roster_ext row, an assist pair, player.party_id 1 without a party_set
// row); the test plants the rest. (1) v0 -> v4 at once: roster_ext and assist merged into roster
// (add_*, equip_skillN 0 -> NULL, assist_uid), the orphans dropped, a dangling weapon -> NULL, an
// item two characters wear and an assist two characters have -> kept by the lowest uid, a NULL in a
// not-null column -> 0, the party sets 1..party_set_max added (the saved set 2 kept), every other
// row of every table equal to the same file migrated to 3. (2) v3 -> v4 (a S3 state, backed up as
// .bak-v3, migrated without the master: the default 10 sets): a party_id outside 1..max keeps its
// set (a row added), a dangling home_uid and title_id -> NULL, an owned support character kept.
// (3) a NULL party_id -> 1. foreign_key_check is empty after each.
NATIVE_TEST("server/schema-migrate-v4") {
    ext::Sql* master = test_master();
    sqlite3* m = master ? master->h : nullptr;
    // ---- (1) v0 -> v4 -------------------------------------------------------------------------------
    TempDb ref_file("v4-ref"), old("v4");
    if (!write_fixture(t, ref_file.path) || !write_fixture(t, old.path)) return;
    Sql ref, db;
    if (!ref.open(ref_file.path, false) || !db.open(old.path, false)) return t.fail("open");
    const int64_t r0 = db.one("select min(uid) from roster", {});  // the fixture's roster: r0, r0 + 1, ...
    const int64_t r1 = r0 + 1, r2 = r0 + 2, r3 = r0 + 3, r4 = r0 + 4;
    const int64_t item = db.one("select min(uid) from items", {});
    t.expect_eq(db.one("select count(*) from roster where uid in (?, ?, ?, ?, ?)", {r0, r1, r2, r3, r4}), (int64_t)5, "the fixture's first uids");
    t.expect_eq(db.one("select count(*) from roster where uid = ? and weapon_uid != 0 and weapon_uid not in (select uid from items)", {r1}),
                (int64_t)1, "the fixture's dangling weapon (r1)");
    t.expect_eq(db.one("select count(*) from assist where uid = ? and assist_uid = ?", {r0, r1}), (int64_t)1, "the fixture's assist pair");
    // the S4 dirt, in both files
    for (Sql* d : {&ref, &db}) {
        d->q("update roster_ext set equip_skill1 = 11, equip_skill2 = 0, equip_skill3 = 33 where uid = ?", {r0});
        d->q("update roster set weapon_uid = ? where uid in (?, ?)", {item, r2, r3});  // one item worn twice
        d->q("update roster set accessory_uid = 0 where uid = ?", {r2});
        d->q("insert into assist (uid, assist_uid) values (?, ?)", {r2, r1});    // r1 assists r0 and r2
        d->q("insert into assist (uid, assist_uid) values (?, 9999)", {r3});     // an assist not owned
        d->q("insert into assist (uid, assist_uid) values (9998, ?)", {r0});     // no such character
        d->q("update roster set created_at = null where uid = ?", {r4});         // a NULL in a not-null column
    }
    t.expect_eq(db.one("select count(*) from assist", {}), (int64_t)4, "the S4 dirt planted");
    t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 3, m), true, "the reference: migrated to 3");
    t.expect_eq(state::open_and_migrate(db.h, old.path, 4, m), true, "migrated to 4");
    t.expect_eq(state::user_version(db.h), 4, "user_version 4");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK) == 0, true, "the v0 file backed up");
    // every other table: its rows as they were at version 3
    static const std::set<std::string> kChanged = {"roster", "roster_ext", "assist", "player", "party_set"};
    std::vector<std::string> tables;
    ref.q("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name", {},
          [&](const Row& r) { tables.push_back(r.s("name")); });
    for (const std::string& table : tables) {
        if (kChanged.count(table)) continue;
        if (rows_of(ref)[table] != rows_of(db)[table]) t.fail("%s: rows changed", table.c_str());
    }
    for (const char* gone : {"roster_ext", "assist"})
        t.expect_eq(db.one("select count(*) from sqlite_master where name = ?", {gone}), (int64_t)0, (std::string(gone) + " dropped").c_str());
    t.expect_eq(db.one("select count(*) from sqlite_master where type = 'index' and tbl_name = 'roster' and name like 'roster_%'", {}), (int64_t)3,
                "roster's unique indexes");
    // the player row: unchanged (its references resolve), at its version-3 columns
    t.expect_eq(rows_over(db, "player", "*"), rows_over(ref, "player", "*"), "player kept");
    // the roster: its own columns kept (skillN -> skillN_level; a NULL created_at -> 0)
    t.expect_eq(rows_over(db, "roster", "uid, role_id, level, exp, limit_break, awaken, skill1_level, skill2_level, skill3_level, created_at"),
                rows_over(ref, "roster", "uid, role_id, level, exp, limit_break, awaken, skill1, skill2, skill3, ifnull(created_at, 0)"),
                "roster: every character, its levels kept");
    t.expect_eq(db.one("select created_at from roster where uid = ?", {r4}, -1), (int64_t)0, "a NULL created_at -> 0");
    // roster_ext merged: r0's seeds and skills; everyone else 0 / NULL; the orphan gone
    t.expect_eq(rows_over(db, "roster",
                          "add_hp, add_attack, add_intelligence, add_defence, add_hit, add_guard, add_ap, equip_skill1, equip_skill2, equip_skill3",
                          "uid = " + std::to_string(r0)),
                std::vector<std::string>{"1:5|1:1|1:0|1:0|1:0|1:0|1:0|1:11|5:|1:33|"}, "r0: roster_ext's add_* and skills (0 -> NULL)");
    t.expect_eq(db.one("select count(*) from roster where uid != ? and (add_hp + add_attack + add_intelligence + add_defence + add_hit + add_guard + "
                       "add_ap != 0 or equip_skill1 is not null or equip_skill2 is not null or equip_skill3 is not null)",
                       {r0}),
                (int64_t)0, "no growth elsewhere: 0 / NULL");
    t.expect_eq(db.one("select count(*) from roster where uid = 2114977791", {}), (int64_t)0, "the orphan roster_ext row isn't a character");
    // equipment: 0 -> NULL, dangling -> NULL, worn twice -> the lowest uid
    t.expect_eq(db.one("select count(*) from roster where weapon_uid = 0 or accessory_uid = 0", {}), (int64_t)0, "no 0 sentinel left");
    t.expect_eq(db.one("select count(*) from roster where uid = ? and weapon_uid is null", {r1}), (int64_t)1, "r1's dangling weapon -> NULL");
    t.expect_eq(db.one("select weapon_uid from roster where uid = ?", {r2}), item, "the item worn twice: kept by the lowest uid (r2)");
    t.expect_eq(db.one("select count(*) from roster where uid = ? and weapon_uid is null", {r3}), (int64_t)1, "and taken off r3");
    // assist: the pair kept; r1 assisting a second character, a missing assist, a missing character: gone
    t.expect_eq(db.one("select assist_uid from roster where uid = ?", {r0}), r1, "r0's assist r1 kept");
    t.expect_eq(db.one("select count(*) from roster where uid in (?, ?) and assist_uid is null", {r2, r3}), (int64_t)2,
                "r1 assisting a second character (r2), an assist not owned (r3): NULL");
    t.expect_eq(db.one("select count(*) from roster where assist_uid is not null", {}), (int64_t)1, "one assist pair");
    // the party sets: 1..party_set_max added (icon 0, unlocked), the saved set 2 kept
    u32 max = m ? (u32)ext::Sql{m}.one("select value from master_global where key = 'party_set_max'", {}, 10) : 10;
    t.expect_eq(db.one("select count(*) from party_set", {}), (int64_t)max, "a row per set 1..party_set_max");
    t.expect_eq(db.one("select count(*) from party_set where party_id between 1 and ?", {max}), (int64_t)max, "the sets 1..max");
    t.expect_eq(rows_over(db, "party_set", "party_id, icon_id, is_lock", "party_id in (1, 2)"),
                (std::vector<std::string>{"1:1|1:0|1:0|", "1:2|1:3|1:1|"}), "set 1 added (icon 0, unlocked), set 2 kept");
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    if (m)
        for (const auto& d : state::check(db.h, m)) t.fail("%s", state::describe(d).c_str());
    ref.close();
    db.close();

    // ---- (2) v3 -> v4, without the master ------------------------------------------------------------
    TempDb v3("v4-from-v3");
    if (!write_fixture(t, v3.path)) return;
    Sql f;
    if (!f.open(v3.path, false)) return t.fail("open v3");
    t.expect_eq(state::open_and_migrate(f.h, v3.path, 3), true, "migrated to 3");
    f.close();
    unlink((v3.path + ".bak-v0").c_str());
    if (!f.open(v3.path, false)) return t.fail("reopen v3");
    t.expect_eq(f.exec("pragma foreign_keys = off;"
                       "delete from party_set;"
                       "update player set party_id = 12, home_uid = 9999, title_id = 12345, support_uid = (select min(uid) from roster);"),
                true, "the v3 cases planted");
    int64_t support = f.one("select min(uid) from roster", {});
    t.expect_eq(state::user_version(f.h), 3, "a version 3 file");
    t.expect_eq(state::open_and_migrate(f.h, v3.path, 4), true, "v3 -> v4");
    t.expect_eq(state::user_version(f.h), 4, "user_version 4");
    f.q("select * from player", {}, [&](const Row& p) {
        t.expect_eq(p.i("party_id"), (int64_t)12, "a party id outside 1..max kept");
        t.expect_eq(p.null("home_uid"), true, "a dangling home_uid -> NULL");
        t.expect_eq(p.null("title_id"), true, "a title not owned -> NULL");
        t.expect_eq(p.i("support_uid"), support, "an owned support character kept");
    });
    t.expect_eq(f.one("select count(*) from party_set", {}), (int64_t)11, "the default 10 sets (no master) and set 12");
    t.expect_eq(f.one("select count(*) from party_set where party_id = 12 and icon_id = 0 and is_lock = 0", {}), (int64_t)1, "set 12's row");
    t.expect_eq(fk_violations(f), 0, "foreign_key_check");
    f.close();
    Sql bak;
    if (!bak.open(v3.path + ".bak-v3", true)) return t.fail("no %s.bak-v3", v3.path.c_str());
    t.expect_eq(state::user_version(bak.h), 3, "the backup is version 3");
    t.expect_eq(bak.one("select count(*) from roster_ext", {}) > 0, true, "the backup keeps roster_ext");
    bak.close();

    // ---- (3) a NULL party_id -> 1 --------------------------------------------------------------------
    TempDb nul("v4-null-party");
    if (!write_fixture(t, nul.path)) return;
    Sql g;
    if (!g.open(nul.path, false)) return t.fail("open (3)");
    t.expect_eq(g.exec("update player set party_id = null"), true, "a NULL party_id planted");
    t.expect_eq(state::open_and_migrate(g.h, nul.path, 4, m), true, "v0 -> v4");
    t.expect_eq(g.one("select party_id from player", {}), (int64_t)1, "NULL party_id -> 1");
    t.expect_eq(fk_violations(g), 0, "foreign_key_check");
    g.close();
}

// Version 5 (PLAN-schema S5: items and gear). The fixture has S5's dirt (a gear set in a sold
// weapon, a free gear with item_uid 0); the test plants the rest. (1) v0 -> v5 at once: items
// rebuilt (locked 2 -> 1, a NULL created_at -> 0), gear_items rebuilt (item_uid 0 -> NULL, the
// gear on the missing weapon dropped, a second gear in an occupied slot -> the gear box with slot 0,
// kept by the lowest uid; a free gear keeps its slot; is_new 5 -> 1; a NULL item_uid stays the
// box), every other row of every table equal to the same file migrated to 4. (2) v4 -> v5 (an S4
// state, backed up as .bak-v4, without the master). foreign_key_check is empty after each.
NATIVE_TEST("server/schema-migrate-v5") {
    ext::Sql* master = test_master();
    sqlite3* m = master ? master->h : nullptr;
    // ---- (1) v0 -> v5 -------------------------------------------------------------------------------
    TempDb ref_file("v5-ref"), old("v5");
    if (!write_fixture(t, ref_file.path) || !write_fixture(t, old.path)) return;
    Sql ref, db;
    if (!ref.open(ref_file.path, false) || !db.open(old.path, false)) return t.fail("open");
    const int64_t worn = 2097152004, sold = 2097152029;  // the fixture's weapon with a gear, the sold one
    t.expect_eq(db.one("select count(*) from items where uid = ?", {worn}), (int64_t)1, "the fixture's weapon with a gear");
    t.expect_eq(db.one("select count(*) from items where uid = ?", {sold}), (int64_t)0, "the fixture's sold weapon");
    t.expect_eq(db.one("select count(*) from gear_items where uid = 2081423359 and item_uid = ?", {sold}), (int64_t)1,
                "the fixture's gear on the sold weapon");
    t.expect_eq(db.one("select count(*) from gear_items where uid = 2080374787 and item_uid = 0", {}), (int64_t)1, "the fixture's free gear");
    const int64_t locked = db.one("select min(uid) from items", {}), no_time = db.one("select max(uid) from items", {});
    // the S5 dirt, in both files
    for (Sql* d : {&ref, &db}) {
        d->q("update items set locked = 2 where uid = ?", {locked});
        d->q("update items set created_at = null where uid = ?", {no_time});
        d->q(
            "insert into gear_items (uid, type, master_item_id, param2, item_uid, slot, is_new, created_at) values "
            "(2080374790, 0, 88449980, 0, ?, 0, 0, 1), (2080374791, 0, 88449980, 0, ?, 1, 0, 1), "
            "(2080374792, 0, 88449980, 0, 0, 2, 5, 1), (2080374793, 0, 88449980, 0, null, 0, 1, null)",
            {worn, worn});
    }
    t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 4, m), true, "the reference: migrated to 4");
    t.expect_eq(state::open_and_migrate(db.h, old.path, 5, m), true, "migrated to 5");
    t.expect_eq(state::user_version(db.h), 5, "user_version 5");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK) == 0, true, "the v0 file backed up");
    // every other table: its rows as they were at version 4
    std::vector<std::string> tables;
    ref.q("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name", {},
          [&](const Row& r) { tables.push_back(r.s("name")); });
    auto ref_rows = rows_of(ref), db_rows = rows_of(db);
    for (const std::string& table : tables) {
        if (table == "items" || table == "gear_items") continue;
        if (ref_rows[table] != db_rows[table]) t.fail("%s: rows changed", table.c_str());
    }
    t.expect_eq(db.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)52, "52 tables");
    t.expect_eq(db.one("select count(*) from sqlite_master where name like 'new_%'", {}), (int64_t)0, "no new_X table left");
    t.expect_eq(db.one("select count(*) from sqlite_master where type = 'index' and name = 'gear_items_slot'", {}), (int64_t)1, "the slot index");
    // items: every row kept; locked 2 -> 1, a NULL created_at -> 0
    t.expect_eq(rows_over(db, "items", "uid, master_item_id, item_type, level, exp, limit_break"),
                rows_over(ref, "items", "uid, master_item_id, item_type, level, exp, limit_break"), "items: every item, its fields kept");
    t.expect_eq(db.one("select locked from items where uid = ?", {locked}, -1), (int64_t)1, "locked 2 -> 1");
    t.expect_eq(db.one("select count(*) from items where uid != ? and locked != 0", {locked}), (int64_t)0, "the others unlocked, as they were");
    t.expect_eq(db.one("select created_at from items where uid = ?", {no_time}, -1), (int64_t)0, "a NULL created_at -> 0");
    t.expect_eq(rows_over(db, "items", "uid, created_at", "uid != " + std::to_string(no_time)),
                rows_over(ref, "items", "uid, created_at", "uid != " + std::to_string(no_time)), "created_at kept");
    // gear_items: uid, item_uid, slot, is_new, created_at
    t.expect_eq(rows_over(db, "gear_items", "uid, item_uid, slot, is_new, created_at"),
                (std::vector<std::string>{"1:2080374785|1:2097152004|1:0|1:0|1:1790841550|",  // set in slot 0: kept (the lowest uid)
                                          "1:2080374787|5:|1:0|1:1|1:1790841555|",            // free: item_uid 0 -> NULL
                                          "1:2080374790|5:|1:0|1:0|1:1|",                     // the second gear in slot 0 -> the box
                                          "1:2080374791|1:2097152004|1:1|1:0|1:1|",           // slot 1: kept
                                          "1:2080374792|5:|1:2|1:1|1:1|",                     // free, its slot kept, is_new 5 -> 1
                                          "1:2080374793|5:|1:0|1:1|1:0|"}),                   // NULL: the box; NULL created_at -> 0
                "gear_items mapped; the gear on the sold weapon (2081423359) dropped");
    t.expect_eq(rows_over(db, "gear_items", "uid, type, master_item_id, param2"),
                rows_over(ref, "gear_items", "uid, type, master_item_id, param2", "uid != 2081423359"), "the gears' kinds kept");
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    if (m)
        for (const auto& d : state::check(db.h, m)) t.fail("%s", state::describe(d).c_str());
    ref.close();
    db.close();

    // ---- (2) v4 -> v5, without the master ------------------------------------------------------------
    TempDb v4("v5-from-v4");
    if (!write_fixture(t, v4.path)) return;
    Sql f;
    if (!f.open(v4.path, false)) return t.fail("open v4");
    t.expect_eq(state::open_and_migrate(f.h, v4.path, 4, m), true, "migrated to 4");
    f.close();
    unlink((v4.path + ".bak-v0").c_str());
    if (!f.open(v4.path, false)) return t.fail("reopen v4");
    t.expect_eq(state::user_version(f.h), 4, "a version 4 file");
    int64_t weapons = f.one("select count(*) from items", {});
    t.expect_eq(state::open_and_migrate(f.h, v4.path, 5), true, "v4 -> v5");
    t.expect_eq(state::user_version(f.h), 5, "user_version 5");
    t.expect_eq(f.one("select count(*) from items", {}), weapons, "every item kept");
    t.expect_eq(rows_over(f, "gear_items", "uid, item_uid"), (std::vector<std::string>{"1:2080374785|1:2097152004|", "1:2080374787|5:|"}),
                "the set gear kept, the free one NULL, the one on the sold weapon dropped");
    t.expect_eq(fk_violations(f), 0, "foreign_key_check");
    f.close();
    Sql bak;
    if (!bak.open(v4.path + ".bak-v4", true)) return t.fail("no %s.bak-v4", v4.path.c_str());
    t.expect_eq(state::user_version(bak.h), 4, "the backup is version 4");
    t.expect_eq(bak.one("select count(*) from gear_items where item_uid = 0", {}), (int64_t)1, "the backup keeps the 0 sentinel");
    bak.close();
}

// Version 6 (PLAN-schema S6: parties). The fixture has S6's dirt (set 2's slot 0 names a sold
// weapon; slot 2 is an empty uid 0; every detail is 0); the test plants the rest. (1) v0 -> v6 at
// once: party_member rebuilt from party ⟕ party_member, one row per party row (uid 0 or dangling ->
// NULL, weapon / accessory 0 or not an item -> NULL, skillN -> skill_idN with 0 -> NULL, assist 0
// or dangling -> NULL; a slot without a party_member row: all NULL; a party_member row without a
// party row, a slot outside 0..3 and a set id < 1 dropped), party_set rebuilt (is_lock 5 -> 1, set
// 0 dropped, set 15 that had only party rows gets its row), party gone; every other table equal to
// the same file migrated to 5. (2) v5 -> v6 (backed up as .bak-v5, without the master): a
// player.party_id 0 with its set 0 row (UpdateParty(0) after S4) -> 1. foreign_key_check is empty
// after each.
NATIVE_TEST("server/schema-migrate-v6") {
    ext::Sql* master = test_master();
    sqlite3* m = master ? master->h : nullptr;
    // ---- (1) v0 -> v6 -------------------------------------------------------------------------------
    TempDb ref_file("v6-ref"), old("v6");
    if (!write_fixture(t, ref_file.path) || !write_fixture(t, old.path)) return;
    Sql ref, db;
    if (!ref.open(ref_file.path, false) || !db.open(old.path, false)) return t.fail("open");
    t.expect_eq(db.one("select count(*) from party", {}), (int64_t)4, "the fixture's four party rows");
    t.expect_eq(db.one("select count(*) from party_member where weapon_uid = 2097152029", {}), (int64_t)1, "the fixture's sold weapon in set 2");
    t.expect_eq(db.one("select count(*) from items where uid = 2097152029", {}), (int64_t)0, "(sold)");
    // the S6 dirt, in both files
    for (Sql* d : {&ref, &db})
        d->exec(
            "insert into party (party_id, slot, uid) values (1, 1, 9999), (15, 0, 2113929217), (2, 7, 2113929217), (0, 0, 2113929216);"
            "insert into party_member (party_id, slot, weapon_uid, accessory_uid, skill1, skill2, skill3, assist_uid) values "
            "(2, 7, 2097152004, 0, 1, 1, 1, 0), (3, 0, 2097152004, 0, 1, 1, 1, 0);"
            "update party_member set accessory_uid = 2097152004, skill1 = 21, skill2 = 0, skill3 = 23, assist_uid = 9999 where party_id = 2 and slot = 1;"
            "insert into party_set (party_id, icon_id, is_lock) values (3, 7, 5), (0, 0, 0)");
    t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 5, m), true, "the reference: migrated to 5");
    t.expect_eq(state::open_and_migrate(db.h, old.path, 6, m), true, "migrated to 6");
    t.expect_eq(state::user_version(db.h), 6, "user_version 6");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK) == 0, true, "the v0 file backed up");
    // every other table: its rows as they were at version 5
    std::vector<std::string> tables;
    ref.q("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name", {},
          [&](const Row& r) { tables.push_back(r.s("name")); });
    auto ref_rows = rows_of(ref), db_rows = rows_of(db);
    for (const std::string& table : tables) {
        if (table == "party" || table == "party_member" || table == "party_set") continue;
        if (ref_rows[table] != db_rows[table]) t.fail("%s: rows changed", table.c_str());
    }
    t.expect_eq(db.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)51, "51 tables");
    t.expect_eq(db.one("select count(*) from sqlite_master where name in ('party') or name like 'new_%'", {}), (int64_t)0, "party gone, no new_X");
    // party_member: (party_id, slot, uid, weapon_uid, accessory_uid, skill_id1..3, assist_uid)
    t.expect_eq(rows_over(db, "party_member", "*"),
                (std::vector<std::string>{"1:15|1:0|1:2113929217|5:|5:|5:|5:|5:|5:|",                               // set 15: party rows only
                                          "1:1|1:0|1:2113929218|5:|5:|5:|5:|5:|5:|",                                // all 0 -> NULL
                                          "1:1|1:1|5:|5:|5:|5:|5:|5:|5:|",                                          // dangling uid; no member row
                                          "1:2|1:0|1:2113929216|5:|5:|1:11|1:12|1:13|1:2113929218|",                // the sold weapon -> NULL
                                          "1:2|1:1|1:2113929217|5:|1:2097152004|1:21|5:|1:23|5:|",                  // skill 0, dangling assist
                                          "1:2|1:2|5:|5:|5:|5:|5:|5:|5:|"}),                                        // uid 0 -> NULL
                "party_member mapped; slot 7, set 0 and the member row without a party row dropped");
    // party_set: the saved sets kept, is_lock 5 -> 1, set 0 dropped, set 15 added
    t.expect_eq(rows_over(db, "party_set", "*", "party_id in (0, 2, 3, 15)"),
                (std::vector<std::string>{"1:15|1:0|1:0|", "1:2|1:3|1:1|", "1:3|1:7|1:1|"}), "party_set mapped");
    t.expect_eq(rows_over(db, "party_set", "*", "party_id not in (0, 2, 3, 15)"), rows_over(ref, "party_set", "*", "party_id not in (0, 2, 3, 15)"),
                "the other sets kept");
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    if (m)
        for (const auto& d : state::check(db.h, m)) t.fail("%s", state::describe(d).c_str());
    ref.close();
    db.close();

    // ---- (2) v5 -> v6, without the master: player.party_id 0 -> 1 ------------------------------------
    TempDb v5("v6-from-v5");
    if (!write_fixture(t, v5.path)) return;
    Sql f;
    if (!f.open(v5.path, false)) return t.fail("open v5");
    t.expect_eq(state::open_and_migrate(f.h, v5.path, 5, m), true, "migrated to 5");
    f.close();
    unlink((v5.path + ".bak-v0").c_str());
    if (!f.open(v5.path, false)) return t.fail("reopen v5");
    t.expect_eq(state::user_version(f.h), 5, "a version 5 file");
    // UpdateParty(0) at version 5: set 0's row and party rows, the current party 0
    t.expect_eq(f.exec("pragma foreign_keys = off; insert into party_set (party_id) values (0);"
                       "insert into party (party_id, slot, uid) values (0, 0, 2113929216); update player set party_id = 0"),
                true, "UpdateParty(0) planted");
    t.expect_eq(state::open_and_migrate(f.h, v5.path, 6), true, "v5 -> v6");
    t.expect_eq(state::user_version(f.h), 6, "user_version 6");
    t.expect_eq(f.one("select party_id from player", {}, -1), (int64_t)1, "party_id 0 -> 1");
    t.expect_eq(f.one("select count(*) from party_set where party_id = 0", {}), (int64_t)0, "set 0 dropped");
    t.expect_eq(f.one("select count(*) from party_member where party_id = 0", {}), (int64_t)0, "set 0's member dropped");
    t.expect_eq(f.one("select count(*) from party_member", {}), (int64_t)4, "the fixture's four slots");
    t.expect_eq(fk_violations(f), 0, "foreign_key_check");
    f.close();
    Sql bak;
    if (!bak.open(v5.path + ".bak-v5", true)) return t.fail("no %s.bak-v5", v5.path.c_str());
    t.expect_eq(state::user_version(bak.h), 5, "the backup is version 5");
    t.expect_eq(bak.one("select count(*) from party", {}), (int64_t)5, "the backup keeps party");
    bak.close();
}

// The foreign keys' actions on a migrated state (PLAN-schema 3.1, 4.2; the FKs of versions 4 and 5):
// what a delete or an update of a parent does to each child, and what a dangling write does.
//   roster.weapon_uid / accessory_uid -> items   ON DELETE SET NULL; a dangling write fails at once
//   roster.assist_uid -> roster                  ON DELETE SET NULL; a dangling write fails at once
//   player.home_uid -> roster                    ON DELETE SET NULL; deferred: a dangling write
//                                                fails at commit
//   player.support_uid -> roster                 ON DELETE SET NULL; a dangling write fails at once
//   player.title_id -> titles                    ON DELETE SET NULL; a dangling write fails at once
//   player.party_id -> party_set                 NO ACTION, deferred: deleting the current set (or
//                                                a dangling write) fails at commit
//   gear_items.item_uid -> items                 ON DELETE CASCADE (S5); a dangling write fails at once
//   party_member.party_id -> party_set           ON DELETE CASCADE (S6); a dangling write fails at once
//   party_member.uid / assist_uid -> roster      ON DELETE SET NULL (S6); a dangling write fails at once
//   party_member.weapon_uid / accessory_uid -> items  ON DELETE SET NULL (S6); likewise
//   no ON UPDATE action: changing a referenced key fails (at once, or at commit for a deferred child)
// Plus the unique indexes (one character per item, one assisted character per assist, one gear per
// weapon slot), STRICT and the checks (items.locked, gear_items.is_new, party_set.is_lock 0 / 1;
// party_set.party_id >= 1; party_member.slot 0..3).
// Version 7 (PLAN-schema S7: the battle in progress). (1) v0 -> v7 at once, against the same file
// migrated to 6, with planted cases: play ⟕ play_ext merged (surprise 5 -> 1, helper_kind 7 -> 0,
// a dangling party_id -> NULL, helper_uid / npc_id 0 -> NULL, campaign_lots gone); play.uids ->
// play_member (an owned uid, a mission NPC's 0x7f000001, a gone uid -> both NULL, a non-number
// skipped); ds_ship.uids -> ds_ship_member (a gone uid dropped, an empty item skipped; slot 1..);
// ds_log's rows keep their order as ids (NULL -> 0); every other table's rows equal. (2) v6 -> v7
// without the master (.bak-v6): MissionFailed's leftover (a play_ext without a play) is dropped.
NATIVE_TEST("server/schema-migrate-v7") {
    ext::Sql* master = test_master();
    sqlite3* m = master ? master->h : nullptr;
    // ---- (1) v0 -> v7 -------------------------------------------------------------------------------
    TempDb ref_file("v7-ref"), old("v7");
    if (!write_fixture(t, ref_file.path) || !write_fixture(t, old.path)) return;
    Sql ref, db;
    if (!ref.open(ref_file.path, false) || !db.open(old.path, false)) return t.fail("open");
    const int64_t a = db.one("select min(uid) from roster", {});
    const int64_t b = db.one("select min(uid) from roster where uid > ?", {a});
    const int64_t c = db.one("select min(uid) from roster where uid > ?", {b});
    const int64_t mission = db.one("select mission_id from play", {}), started = db.one("select started_at from play", {});
    t.expect_eq(rows_over(db, "play", "uids"), (std::vector<std::string>{"3:" + std::to_string(a) + "," + std::to_string(b) + ",|"}),
                "the fixture's play: a and b");
    t.expect_eq(rows_over(db, "ds_ship", "ship_id, uids"), (std::vector<std::string>{"1:1|3:" + std::to_string(a) + "," + std::to_string(b) + ",|"}),
                "the fixture's ship 1: a and b");
    // the S7 dirt, in both files
    for (Sql* d : {&ref, &db})
        d->exec("update play set party_id = 15, uids = '" + std::to_string(a) + ",2130706433,9999,x," + std::to_string(b) +
                "';"
                "update play_ext set surprise = 5, helper_kind = 7, helper_uid = 0, npc_id = 0, campaign_lots = 3;"
                "insert into ds_ship (ship_id, area_id, mission_id, bonus_set_id, item_id, uids, started_at, closed_at) "
                "select 2, area_id, mission_id, 0, 0, '9999," +
                std::to_string(c) +
                ",,', started_at, closed_at from ds_ship where ship_id = 1;"
                "insert into ds_log (mission_id, started_at) values (null, null)");
    t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 6, m), true, "the reference: migrated to 6");
    t.expect_eq(state::open_and_migrate(db.h, old.path, 7, m), true, "migrated to 7");
    t.expect_eq(state::user_version(db.h), 7, "user_version 7");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK) == 0, true, "the v0 file backed up");
    // every other table: its rows as they were at version 6
    std::vector<std::string> tables;
    ref.q("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name", {},
          [&](const Row& r) { tables.push_back(r.s("name")); });
    auto ref_rows = rows_of(ref), db_rows = rows_of(db);
    for (const std::string& table : tables) {
        if (table == "play" || table == "play_ext" || table == "ds_ship" || table == "ds_log") continue;
        if (ref_rows[table] != db_rows[table]) t.fail("%s: rows changed", table.c_str());
    }
    t.expect_eq(db.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)52, "52 tables");
    t.expect_eq(db.one("select count(*) from sqlite_master where name in ('play_ext') or name like 'new_%'", {}), (int64_t)0,
                "play_ext gone, no new_X");
    // play: (id, mission_id, mission_type, party_id, started_at, stamina_cost, surprise, helper_kind, helper_uid, npc_id)
    t.expect_eq(rows_over(db, "play", "*"),
                (std::vector<std::string>{"1:1|1:" + std::to_string(mission) + "|1:0|5:|1:" + std::to_string(started) + "|1:5|1:1|1:0|5:|5:|"}),
                "play ⟕ play_ext merged");
    t.expect_eq(columns_of(db, "play").count("campaign_lots") + columns_of(db, "play").count("uids"), (size_t)0, "campaign_lots and uids gone");
    // play_member: (play_id, slot, uid, npc_uid)
    t.expect_eq(rows_over(db, "play_member", "*"),
                (std::vector<std::string>{"1:1|1:0|1:" + std::to_string(a) + "|5:|", "1:1|1:1|5:|1:2130706433|", "1:1|1:2|5:|5:|",
                                          "1:1|1:3|1:" + std::to_string(b) + "|5:|"}),
                "play.uids -> play_member (a, an NPC, a gone uid, b; 'x' skipped)");
    // ds_ship_member: (ship_id, slot, uid)
    t.expect_eq(rows_over(db, "ds_ship_member", "*"),
                (std::vector<std::string>{"1:1|1:1|1:" + std::to_string(a) + "|", "1:1|1:2|1:" + std::to_string(b) + "|",
                                          "1:2|1:2|1:" + std::to_string(c) + "|"}),
                "ds_ship.uids -> ds_ship_member (9999 dropped, the empty item skipped)");
    const std::string ship_cols = "ship_id, area_id, mission_id, bonus_set_id, item_id, started_at, closed_at";
    t.expect_eq(rows_over(db, "ds_ship", ship_cols), rows_over(ref, "ds_ship", ship_cols), "ds_ship's other columns kept");
    t.expect_eq(columns_of(db, "ds_ship").count("uids"), (size_t)0, "ds_ship.uids gone");
    // ds_log: the rows in order as ids, NULL -> 0
    std::vector<std::string> logs = rows_over(ref, "ds_log", "rowid, ifnull(mission_id, 0), ifnull(started_at, 0)");
    t.expect_eq(rows_over(db, "ds_log", "*"), logs, "ds_log: rowid -> id, NULL -> 0");
    t.expect_eq(logs.size(), (size_t)2, "(two departures)");
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    if (m)
        for (const auto& d : state::check(db.h, m)) t.fail("%s", state::describe(d).c_str());
    ref.close();
    db.close();

    // ---- (2) v6 -> v7, without the master: MissionFailed's leftover ---------------------------------
    TempDb v6("v7-from-v6");
    if (!write_fixture(t, v6.path)) return;
    Sql f;
    if (!f.open(v6.path, false)) return t.fail("open v6");
    t.expect_eq(state::open_and_migrate(f.h, v6.path, 6, m), true, "migrated to 6");
    f.close();
    unlink((v6.path + ".bak-v0").c_str());
    if (!f.open(v6.path, false)) return t.fail("reopen v6");
    t.expect_eq(state::user_version(f.h), 6, "a version 6 file");
    // MissionStart (a surprise roll) then MissionFailed at version 6: play deleted, play_ext left
    t.expect_eq(f.exec("update play_ext set surprise = 1, mission_type = 1; delete from play"), true, "MissionFailed planted");
    t.expect_eq(state::open_and_migrate(f.h, v6.path, 7), true, "v6 -> v7");
    t.expect_eq(state::user_version(f.h), 7, "user_version 7");
    t.expect_eq(f.one("select count(*) from play", {}), (int64_t)0, "nothing in progress");
    t.expect_eq(f.one("select count(*) from play_member", {}), (int64_t)0, "no members");
    t.expect_eq(f.one("select count(*) from sqlite_master where name = 'play_ext'", {}), (int64_t)0, "the leftover is gone");
    t.expect_eq(f.one("select count(*) from ds_ship_member", {}), (int64_t)2, "ship 1's crew");
    t.expect_eq(fk_violations(f), 0, "foreign_key_check");
    f.close();
    Sql bak;
    if (!bak.open(v6.path + ".bak-v6", true)) return t.fail("no %s.bak-v6", v6.path.c_str());
    t.expect_eq(state::user_version(bak.h), 6, "the backup is version 6");
    t.expect_eq(bak.one("select count(*) from play_ext", {}), (int64_t)1, "the backup keeps play_ext");
    bak.close();
}

// Version 8 (PLAN-schema S8: presents). (1) v0 -> v8 at once, against the same file migrated to 7,
// with planted cases: present_texts merged as `text` (the fixture's two login-bonus lines; '' ->
// NULL; an orphan line dropped), a wallet type's content_id 0 -> NULL (the fixture's coins; a FOL
// present; a coin present naming 5 keeps it), an item's content_id kept, a NULL num -> 0, the
// AUTOINCREMENT counter kept above max(id); every other table's rows equal. (2) v7 -> v8 without
// the master (.bak-v7).
NATIVE_TEST("server/schema-migrate-v8") {
    ext::Sql* master = test_master();
    sqlite3* m = master ? master->h : nullptr;
    // ---- (1) v0 -> v8 -------------------------------------------------------------------------------
    TempDb ref_file("v8-ref"), old("v8");
    if (!write_fixture(t, ref_file.path) || !write_fixture(t, old.path)) return;
    Sql ref, db;
    if (!ref.open(ref_file.path, false) || !db.open(old.path, false)) return t.fail("open");
    t.expect_eq(rows_over(db, "presents", "id, content_type, content_id"), (std::vector<std::string>{"1:1|1:4|1:0|", "1:2|1:4|1:0|"}),
                "the fixture's presents: two coin presents");
    // the S8 dirt, in both files
    for (Sql* d : {&ref, &db})
        d->exec(
            "insert into presents (id, content_type, content_id, num, reason_type, reason_param, created_at, received_at) values "
            "(3, 1, 1234, 1, 2, 77, 1790841700, 1790841800), (4, 3, 0, null, 3, 5, 1790841701, null), (5, 4, 5, 10, 7, 6, 1790841702, null);"
            "insert into present_texts (id, text) values (3, ''), (99, 'orphan');"
            "update sqlite_sequence set seq = 50 where name = 'presents'");
    t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 7, m), true, "the reference: migrated to 7");
    t.expect_eq(state::open_and_migrate(db.h, old.path, 8, m), true, "migrated to 8");
    t.expect_eq(state::user_version(db.h), 8, "user_version 8");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK) == 0, true, "the v0 file backed up");
    std::vector<std::string> tables;
    ref.q("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name", {},
          [&](const Row& r) { tables.push_back(r.s("name")); });
    auto ref_rows = rows_of(ref), db_rows = rows_of(db);
    for (const std::string& table : tables) {
        if (table == "presents" || table == "present_texts") continue;
        if (ref_rows[table] != db_rows[table]) t.fail("%s: rows changed", table.c_str());
    }
    t.expect_eq(db.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)51, "51 tables");
    t.expect_eq(db.one("select count(*) from sqlite_master where name = 'present_texts' or name like 'new_%'", {}), (int64_t)0,
                "present_texts gone, no new_X");
    // presents: (id, content_type, content_id, num, reason_type, reason_param, text, created_at, received_at)
    t.expect_eq(rows_over(db, "presents", "*"),
                (std::vector<std::string>{"1:1|1:4|5:|1:500|1:1|1:3511586374|3:通常ログインボーナス 1日目|1:1790841480|5:|",
                                          "1:2|1:4|5:|1:250|1:1|1:3511586374|3:通常ログインボーナス 2日目|1:1790841675|5:|",
                                          "1:3|1:1|1:1234|1:1|1:2|1:77|5:|1:1790841700|1:1790841800|", "1:4|1:3|5:|1:0|1:3|1:5|5:|1:1790841701|5:|",
                                          "1:5|1:4|1:5|1:10|1:7|1:6|5:|1:1790841702|5:|"}),
                "presents ⟕ present_texts");
    t.expect_eq(db.one("select seq from sqlite_sequence where name = 'presents'", {}), (int64_t)50, "the AUTOINCREMENT counter kept");
    t.expect_eq(db.exec("insert into presents (content_type, num, reason_type, created_at) values (4, 1, 1, 0)"), true, "a new present");
    t.expect_eq(db.one("select max(id) from presents", {}), (int64_t)51, "its id follows the counter");
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    if (m)
        for (const auto& d : state::check(db.h, m)) t.fail("%s", state::describe(d).c_str());
    ref.close();
    db.close();

    // ---- (2) v7 -> v8, without the master -------------------------------------------------------------
    TempDb v7("v8-from-v7");
    if (!write_fixture(t, v7.path)) return;
    Sql f;
    if (!f.open(v7.path, false)) return t.fail("open v7");
    t.expect_eq(state::open_and_migrate(f.h, v7.path, 7, m), true, "migrated to 7");
    f.close();
    unlink((v7.path + ".bak-v0").c_str());
    if (!f.open(v7.path, false)) return t.fail("reopen v7");
    t.expect_eq(state::user_version(f.h), 7, "a version 7 file");
    t.expect_eq(state::open_and_migrate(f.h, v7.path, 8), true, "v7 -> v8");
    t.expect_eq(state::user_version(f.h), 8, "user_version 8");
    t.expect_eq(f.one("select count(*) from presents where text is not null and content_id is null", {}), (int64_t)2, "the two lines merged");
    t.expect_eq(fk_violations(f), 0, "foreign_key_check");
    f.close();
    Sql bak;
    if (!bak.open(v7.path + ".bak-v7", true)) return t.fail("no %s.bak-v7", v7.path.c_str());
    t.expect_eq(state::user_version(bak.h), 7, "the backup is version 7");
    t.expect_eq(bak.one("select count(*) from present_texts", {}), (int64_t)2, "the backup keeps present_texts");
    bak.close();
}

// Version 9 (PLAN-schema S9: times and booleans). (1) v0 -> v9 at once, against the same file
// migrated to 8, with the fixture's S9 dirt (favor.event_drop_at '' and a time string, tapped_at 0,
// titles.got_at 0, ds_area.last_play) and planted cases (an event_drop_at that isn't a time, NULLs
// in not-null columns, booleans 2 / 3 / 5 / 7 / 9 -> 1, NULL -> 0, premium_pass.last_at 0); the
// twelve rebuilt tables row by row, every other table's rows equal. (2) v8 -> v9 without the
// master (.bak-v8).
NATIVE_TEST("server/schema-migrate-v9") {
    ext::Sql* master = test_master();
    sqlite3* m = master ? master->h : nullptr;
    // ---- (1) v0 -> v9 -------------------------------------------------------------------------------
    TempDb ref_file("v9-ref"), old("v9");
    if (!write_fixture(t, ref_file.path) || !write_fixture(t, old.path)) return;
    Sql ref, db;
    if (!ref.open(ref_file.path, false) || !db.open(old.path, false)) return t.fail("open");
    // the S9 dirt, in both files
    for (Sql* d : {&ref, &db})
        d->exec(
            "insert into favor (same_role_id, point, tap_count, tapped_at, event_drop_at) values (111, null, 2, 0, 'soon');"
            "insert into titles (id, got_at) values (999, 1790841700);"
            "insert into login_bonus (id, day, last_at) values (77, null, 5);"
            "insert into premium_pass (id, granted_at, day, last_at) values (88, 1790841600, 0, 0);"
            "insert into follow_rental (day, count, paid) values (1790668800, 2, 5);"
            "insert into sphere_rental_day (day, season_id, count, paid) values (1790668800, null, null, null);"
            "update ds_area set is_new = 3;"
            "insert into mission (mission_id, cleared, best_rank, play_count, clear_count, first_clear_at) values (4, 2, 0, null, 3, null);"
            "insert into event_rank_score (ranking_id, group_id, score, roles, created_at, fresh) values (5, null, 3, null, null, 7);"
            "update wboss set hunt_new = 2;"
            "insert into sphere_cell (asset_id, floor_level, mission_box_id, mission_id, overwrite_enemy_level, cleared, playing, created_at, "
            "updated_at) values (6, null, null, null, null, 0, 9, null, null);"
            "insert into sphere_rental (follow_player_id, used, updated_at) values (7, null, null)");
    t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 8, m), true, "the reference: migrated to 8");
    t.expect_eq(state::open_and_migrate(db.h, old.path, 9, m), true, "migrated to 9");
    t.expect_eq(state::user_version(db.h), 9, "user_version 9");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK) == 0, true, "the v0 file backed up");
    const std::set<std::string> rebuilt = {"favor",   "titles",  "login_bonus",      "premium_pass", "follow_rental", "sphere_rental_day",
                                           "ds_area", "mission", "event_rank_score", "wboss",        "sphere_cell",   "sphere_rental"};
    std::vector<std::string> tables;
    ref.q("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name", {},
          [&](const Row& r) { tables.push_back(r.s("name")); });
    auto ref_rows = rows_of(ref), db_rows = rows_of(db);
    for (const std::string& table : tables) {
        if (rebuilt.count(table)) continue;
        if (ref_rows[table] != db_rows[table]) t.fail("%s: rows changed", table.c_str());
    }
    t.expect_eq(db.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)51, "51 tables");
    t.expect_eq(db.one("select count(*) from sqlite_master where name like 'new_%'", {}), (int64_t)0, "no new_X");
    for (const std::string& table : rebuilt)
        t.expect_eq(db.one("select count(*) from sqlite_master where name = ? and sql like '%) strict'", {table}), (int64_t)1,
                    (table + " is STRICT").c_str());
    // favor: (same_role_id, point, tap_count, tapped_at, event_drop_at)
    const int64_t drop_at = parse_time_strict("2026-10-01 04:00:00");
    t.expect_eq(drop_at > 0, true, "(the fixture's time string parses)");
    t.expect_eq(rows_over(db, "favor", "*"),
                (std::vector<std::string>{"1:111|1:0|1:2|5:|5:|", "1:3499236629|1:100|1:1|1:1790841600|5:|",
                                          "1:972142624|1:0|1:0|5:|1:" + std::to_string(drop_at) + "|"}),
                "favor: the time string -> seconds, '' and 'soon' -> NULL, tapped_at 0 -> NULL, NULL point -> 0");
    t.expect_eq(db.one("select count(*) from titles where got_at is null", {}), ref.one("select count(*) from titles where got_at = 0", {}),
                "titles.got_at 0 -> NULL");
    t.expect_eq(rows_over(db, "titles", "*", "id = 999"), (std::vector<std::string>{"1:999|1:1790841700|"}), "a title's time kept");
    t.expect_eq(rows_over(db, "login_bonus", "*"), (std::vector<std::string>{"1:3511586374|1:2|1:1790841675|", "1:77|1:0|1:5|"}),
                "login_bonus.day -> day_index (NULL -> 0)");
    t.expect_eq(rows_over(db, "premium_pass", "*"),
                (std::vector<std::string>{"1:1147128996|1:1790841600|1:1|1:1790841600|", "1:88|1:1790841600|1:0|5:|"}),
                "premium_pass.day -> day_index, last_at 0 -> NULL");
    t.expect_eq(rows_over(db, "follow_rental", "*"), (std::vector<std::string>{"1:1790668800|1:2|1:1|", "1:1790755200|1:1|1:0|"}),
                "follow_rental.day -> rental_day, paid 5 -> 1");
    t.expect_eq(rows_over(db, "sphere_rental_day", "*"), (std::vector<std::string>{"1:1790668800|5:|1:0|1:0|", "1:1790755200|1:75957727|1:1|1:0|"}),
                "sphere_rental_day.day -> rental_day, NULL count / paid -> 0");
    t.expect_eq(rows_over(db, "ds_area", "*"), (std::vector<std::string>{"1:3129394740|1:10|1:1|1:1|"}), "ds_area: is_new 3 -> 1, is_last_play");
    t.expect_eq(rows_over(db, "mission", "*", "mission_id = 4"), (std::vector<std::string>{"1:4|1:1|1:0|1:3|5:|"}),
                "mission: cleared 2 -> 1, NULL play_count -> 0");
    t.expect_eq(rows_over(db, "event_rank_score", "*", "ranking_id = 5"), (std::vector<std::string>{"1:5|1:0|1:3|5:|5:|1:1|"}),
                "event_rank_score: fresh 7 -> 1, NULL group -> 0");
    t.expect_eq(db.one("select count(*) from wboss where hunt_new = 1", {}), (int64_t)1, "wboss.hunt_new 2 -> 1");
    t.expect_eq(rows_over(db, "sphere_cell", "*", "asset_id = 6"), (std::vector<std::string>{"1:6|1:0|5:|5:|1:0|1:0|1:1|5:|5:|"}),
                "sphere_cell: playing 9 -> 1, NULLs -> 0");
    t.expect_eq(rows_over(db, "sphere_rental", "*", "follow_player_id = 7"), (std::vector<std::string>{"1:7|1:0|5:|"}),
                "sphere_rental.used NULL -> 0");
    t.expect_eq(columns_of(db, "login_bonus").count("day") + columns_of(db, "premium_pass").count("day") +
                    columns_of(db, "follow_rental").count("day") + columns_of(db, "sphere_rental_day").count("day") +
                    columns_of(db, "ds_area").count("last_play"),
                (size_t)0, "the old names gone");
    // every other column of the rebuilt tables as it was (the columns both versions name alike)
    for (const char* cols_of :
         {"mission: mission_id, clear_count, first_clear_at", "event_rank_score: ranking_id, score, roles, created_at",
          "wboss: boss_id, area_id, wave, n1, n2, n3, a1, a2, a3, required, wave_started_at, last_clear_secs, hunt_until",
          "sphere_cell: asset_id, mission_box_id, mission_id, created_at, updated_at", "sphere_rental: follow_player_id, updated_at"}) {
        std::string spec = cols_of, table = spec.substr(0, spec.find(':')), cols = spec.substr(spec.find(':') + 2);
        t.expect_eq(rows_over(db, table, cols), rows_over(ref, table, cols), (table + "'s other columns kept").c_str());
    }
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    t.expect_eq(db.one("select count(*) from player p join titles x on x.id = p.title_id", {}), db.one("select count(*) from player", {}),
                "player.title_id resolves in the rebuilt titles");
    // (no state::check here: the planted rows' ids are synthetic, not master ids)
    ref.close();
    db.close();

    // ---- (2) v8 -> v9, without the master -------------------------------------------------------------
    TempDb v8("v9-from-v8");
    if (!write_fixture(t, v8.path)) return;
    Sql f;
    if (!f.open(v8.path, false)) return t.fail("open v8");
    t.expect_eq(state::open_and_migrate(f.h, v8.path, 8, m), true, "migrated to 8");
    f.close();
    unlink((v8.path + ".bak-v0").c_str());
    if (!f.open(v8.path, false)) return t.fail("reopen v8");
    t.expect_eq(state::user_version(f.h), 8, "a version 8 file");
    t.expect_eq(state::open_and_migrate(f.h, v8.path, 9), true, "v8 -> v9");
    t.expect_eq(state::user_version(f.h), 9, "user_version 9");
    t.expect_eq(f.one("select event_drop_at from favor where same_role_id = 972142624", {}), drop_at, "the time string -> seconds");
    t.expect_eq(f.one("select count(*) from titles where got_at = 0", {}), (int64_t)0, "no got_at 0 left");
    t.expect_eq(fk_violations(f), 0, "foreign_key_check");
    f.close();
    Sql bak;
    if (!bak.open(v8.path + ".bak-v8", true)) return t.fail("no %s.bak-v8", v8.path.c_str());
    t.expect_eq(state::user_version(bak.h), 8, "the backup is version 8");
    t.expect_eq(bak.one("select count(*) from favor where event_drop_at = '2026-10-01 04:00:00'", {}), (int64_t)1, "the backup keeps the text");
    bak.close();
}

// Version 10 (PLAN-schema S10: the module tables). (1) v0 -> v10 at once, against the same file
// migrated to 9, with the fixture's S10 dirt and planted cases per module group; the rebuilt
// tables row by row, every other table's rows equal (but the CASCADE children the mapping drops
// with their parent: listed). (2) v9 -> v10 without the master (.bak-v9).
NATIVE_TEST("server/schema-migrate-v10") {
    ext::Sql* master = test_master();
    sqlite3* m = master ? master->h : nullptr;
    // ---- (1) v0 -> v10 ------------------------------------------------------------------------------
    TempDb ref_file("v10-ref"), old("v10");
    if (!write_fixture(t, ref_file.path) || !write_fixture(t, old.path)) return;
    Sql ref, db;
    if (!ref.open(ref_file.path, false) || !db.open(old.path, false)) return t.fail("open");
    const std::string area = "3129394740", crew_uid = "2113929216";  // the fixture's explored area, ship 1's first member
    // the S10 dirt, in both files
    for (Sql* d : {&ref, &db})
        t.expect_eq(
            d->exec(
                // deep space: an offer on a ship that doesn't exist (is_new 3, a NULL count, updated_at 0), one of no explored
                // area, one on a ship of no explored area; that ship (with a crew member) and one with NULLs; bonus values of
                // the dropped ship, without a bonus id, without a value
                "insert into ds_offer (mission_id, area_id, bonus_set_id, closed_at, ship_id, is_new, play_count, play_count_daily, "
                "play_count_weekly, updated_at) values (11, " +
                area + ", 5, 1790900000, 77, 3, null, 2, 0, 0), (12, 999, 5, 0, 0, 0, 0, 0, 0, 1), (13, " + area +
                ", 5, 0, 2, 0, 0, 0, 0, 1);"
                "insert into ds_ship (ship_id, area_id, mission_id, bonus_set_id, item_id, uids, started_at, closed_at) values (2, 999, 13, 0, 0, '" +
                crew_uid + ",', 1, 2), (3, " + area +
                ", null, null, 0, '', null, 5);"
                "insert into ds_bonus (ship_id, bonus_id, value) values (2, 1, 2.0), (1, null, 1.0), (3, 4, null);"
                // gacha: a character draw (duplicate 2, NULL rank and costs) and one of a character not owned; the counter
                // above the ids; a step-up row with NULL counts; drawn slots of a box without its box_state row, a slot
                // without a slot id
                "insert into gacha_history (id, gacha_id, at, role_id, uid, rank, duplicate, cost_free, cost_pay) values "
                "(900, 1, 5, 77, " +
                crew_uid +
                ", null, 2, null, null), (901, 1, 5, 77, 12345, 'S', 0, 1, 2);"
                "update sqlite_sequence set seq = 950 where name = 'gacha_history';"
                "insert into stepup (head, try_count, restart_count, next_id) values (66, null, null, null);"
                "insert into box_slots (gacha_id, slot_id, drawn) values (77, 1, 2), (77, 2, null), (78, null, 1);"
                // events: a boss in a big hunt, clears of a boss never met (and without a wave), notified 5, NULL lots
                "insert into wboss (boss_id, area_id, wave, wave_started_at, hunt_until, hunt_new) values (55, 1, 2, 1790841600, 1790900000, 1);"
                "insert into wboss_clear (boss_id, wave, cleared_at, notified) values (55, 1, 1790841700, 5), (4242, 1, 1, 0), (55, null, 1, 0);"
                "insert into favor_drop_play (same_role_id, lots) values (66, null);"
                // shop: NULL counts
                "insert into shop_counts (id, num, period, total) values (67, null, 5, null);"
                "insert into exchange_counts (id, num) values (68, null);"
                // Sphere 211: a NULL count in the dive, a departed character not owned, a box with NULLs and the counter
                // above it, the log emptied with its counter kept, a ranking without a floor
                "update sphere set streak = null;"
                "insert into sphere_departed (uid) values (12345);"
                "insert into sphere_box (id, floor_level, rank) values (5, null, null);"
                "update sqlite_sequence set seq = 99 where name = 'sphere_box';"
                "delete from sphere_log;"
                "update sqlite_sequence set seq = 42 where name = 'sphere_log';"
                "insert into sphere_rank (season_id, floor_level, entered_at) values (69, null, null);"
                // daily: the fixture's favor bonus row has healed_at 0; its lot character not owned
                "update favor_bonus_state set lot_uid = 12345;"
                // the rest: a meta key without a value, NULL counts, an unlock by a mission never played (the fixture's
                // wire_device has player_id 0)
                "insert into meta (key, value) values ('x_key', null);"
                "insert into stock (master_item_id, item_type, count) values (70, null, null);"
                "insert into counters (key, value) values ('x_count', null);"
                "insert into unlocks (mission_id, mission_type, by_mission, at) values (71, null, 4242, null), (72, 1, 0, 5);"),
            true, "the S10 cases planted");
    t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 9, m), true, "the reference: migrated to 9");
    t.expect_eq(state::open_and_migrate(db.h, old.path, 10, m), true, "migrated to 10");
    t.expect_eq(state::user_version(db.h), 10, "user_version 10");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK) == 0, true, "the v0 file backed up");
    // clang-format off
    const std::set<std::string> rebuilt = {
        "ds_ship", "ds_offer", "ds_bonus",
        "gacha_history", "stepup", "box_state", "box_slots",
        "wboss", "wboss_clear", "event_last", "event_rank_received", "favor_drop_play",
        "shop_counts", "exchange_counts", "subscription",
        "sphere", "sphere_departed", "sphere_box", "sphere_rank", "sphere_log",
        "favor_bonus_state",
        "meta", "stock", "counters", "achievements", "gear_barney", "unlocks", "wire_device",
    };
    // clang-format on
    std::vector<std::string> tables;
    ref.q("select name from sqlite_master where type = 'table' and name != 'sqlite_sequence' order by name", {},
          [&](const Row& r) { tables.push_back(r.s("name")); });
    auto ref_rows = rows_of(ref), db_rows = rows_of(db);
    for (const std::string& table : tables) {
        if (rebuilt.count(table) || table == "ds_ship_member") continue;
        if (ref_rows[table] != db_rows[table]) t.fail("%s: rows changed", table.c_str());
    }
    t.expect_eq(db.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)51, "51 tables");
    t.expect_eq(db.one("select count(*) from sqlite_master where name like 'new_%'", {}), (int64_t)0, "no new_X");
    for (const std::string& table : rebuilt)
        t.expect_eq(db.one("select count(*) from sqlite_master where name = ? and sql like '%) strict'", {table}), (int64_t)1,
                    (table + " is STRICT").c_str());
    // deep space
    t.expect_eq(
        rows_over(db, "ds_ship", "*"),
        (std::vector<std::string>{"1:1|1:" + area + "|1:2081363|1:0|1:0|1:1790841600|1:1790845200|", "1:3|1:" + area + "|1:0|5:|1:0|1:0|1:5|"}),
        "ds_ship: a ship of no area dropped, NULLs -> 0, item_id 0 kept");
    t.expect_eq(rows_over(db, "ds_ship_member", "ship_id, slot, uid"), rows_over(ref, "ds_ship_member", "ship_id, slot, uid", "ship_id != 2"),
                "ds_ship_member: the dropped ship's crew gone with it");
    t.expect_eq(ref.one("select count(*) from ds_ship_member where ship_id = 2", {}), (int64_t)1, "(the reference has it)");
    t.expect_eq(
        rows_over(db, "ds_offer", "*"),
        (std::vector<std::string>{"1:11|1:" + area + "|1:5|1:1790900000|5:|1:1|1:0|1:2|1:0|5:|", "1:13|1:" + area + "|1:5|5:|5:|1:0|1:0|1:0|1:0|1:1|",
                                  "1:2081363|1:" + area + "|1:0|5:|1:1|1:0|1:1|1:1|1:1|1:1790841600|"}),
        "ds_offer: closed_at / updated_at 0 -> NULL, ship_id dangling -> NULL, is_new 3 -> 1, no area -> dropped");
    t.expect_eq(rows_over(db, "ds_bonus", "*"), (std::vector<std::string>{"1:1|1:1|2:1.5|", "1:3|1:4|2:0.0|"}),
                "ds_bonus: no ship or no bonus id -> dropped, NULL value -> 0");
    // gacha: (id, gacha_id, at, role_id, character_uid, item_uid, rank, duplicate, cost_free, cost_pay)
    t.expect_eq(rows_over(db, "gacha_history", "*", "id >= 900"),
                (std::vector<std::string>{"1:900|1:1|1:5|1:77|1:" + crew_uid + "|5:|3:|1:1|1:0|1:0|", "1:901|1:1|1:5|1:77|5:|5:|3:S|1:0|1:1|1:2|"}),
                "gacha_history: a character draw's uid -> character_uid (not owned: NULL), duplicate 2 -> 1, NULL rank / costs");
    const int64_t weapon_draws = ref.one("select count(*) from gacha_history where role_id = 0", {});
    t.expect_eq(weapon_draws > 0, true, "(the fixture's draws are weapons)");
    t.expect_eq(db.one("select count(*) from gacha_history where role_id is null and character_uid is null", {}), weapon_draws,
                "a weapon draw: role_id 0 -> NULL, no character");
    t.expect_eq(rows_over(db, "gacha_history", "id, item_uid", "id < 900"),
                rows_over(ref, "gacha_history", "id, case when uid in (select uid from items) then uid end", "id < 900"),
                "its uid -> item_uid, NULL for the sold weapon");
    t.expect_eq(db.one("select count(*) from gacha_history where id < 900 and item_uid is null", {}), (int64_t)14,
                "(14 of the fixture's 30 drawn weapons are gone: sold or used up)");
    t.expect_eq(db.one("select seq from sqlite_sequence where name = 'gacha_history'", {}), (int64_t)950, "the AUTOINCREMENT counter kept");
    t.expect_eq(rows_over(db, "stepup", "*", "head = 66"), (std::vector<std::string>{"1:66|1:0|1:0|5:|"}), "stepup: NULL counts -> 0");
    t.expect_eq(rows_over(db, "box_state", "*", "gacha_id = 77"), (std::vector<std::string>{"1:77|1:0|1:0|"}),
                "box_state: a row for the box its slots name");
    t.expect_eq(rows_over(db, "box_slots", "*", "gacha_id in (77, 78)"), (std::vector<std::string>{"1:77|1:1|1:2|", "1:77|1:2|1:0|"}),
                "box_slots: kept (NULL drawn -> 0), no slot id -> dropped");
    t.expect_eq(rows_over(db, "box_slots", "*", "gacha_id < 77"), rows_over(ref, "box_slots", "*", "gacha_id < 77"), "the fixture's slots kept");
    // events
    t.expect_eq(rows_over(db, "wboss", "boss_id, hunt_until"), (std::vector<std::string>{"1:55|1:1790900000|", "1:959907062|5:|"}),
                "wboss.hunt_until 0 -> NULL (no big hunt), a hunt's end kept");
    const std::string wboss_cols = "boss_id, area_id, wave, n1, n2, n3, a1, a2, a3, required, wave_started_at, last_clear_secs, hunt_new";
    t.expect_eq(rows_over(db, "wboss", wboss_cols), rows_over(ref, "wboss", wboss_cols), "wboss's other columns kept");
    t.expect_eq(rows_over(db, "wboss_clear", "*"), (std::vector<std::string>{"1:55|1:1|1:1790841700|1:1|", "1:959907062|1:1|1:1790841600|1:0|"}),
                "wboss_clear: a boss never met or no wave -> dropped, notified 5 -> 1");
    t.expect_eq(rows_over(db, "favor_drop_play", "*", "same_role_id = 66"), (std::vector<std::string>{"1:66|1:0|"}),
                "favor_drop_play: NULL lots -> 0");
    // shop
    t.expect_eq(rows_over(db, "shop_counts", "*", "id = 67"), (std::vector<std::string>{"1:67|1:0|1:5|1:0|"}), "shop_counts: NULL counts -> 0");
    t.expect_eq(rows_over(db, "exchange_counts", "*", "id = 68"), (std::vector<std::string>{"1:68|1:0|"}), "exchange_counts: NULL num -> 0");
    // Sphere 211
    t.expect_eq(db.one("select streak from sphere where id = 1", {}) == 0 && !db.one("select streak is null from sphere", {}), true,
                "sphere: NULL streak -> 0");
    const std::string sphere_cols =
        "id, season_id, floor_level, asset_group, treasure_total, stamina, stamina_at, revive_count, best_floor, entered_at, clear_asset, "
        "lot_floor_num, reroll_count, prev_season, prev_floor, prev_treasure, prev_rank, cycle, season_wins, end_pending, debug_enemy_level";
    t.expect_eq(rows_over(db, "sphere", sphere_cols), rows_over(ref, "sphere", sphere_cols), "sphere's other columns kept");
    t.expect_eq(rows_over(db, "sphere_departed", "*"), (std::vector<std::string>{"1:2113929217|"}), "sphere_departed: not owned -> dropped");
    t.expect_eq(rows_over(db, "sphere_box", "*"), (std::vector<std::string>{"1:1|1:1|1:1|", "1:5|1:0|1:0|"}), "sphere_box: NULLs -> 0");
    t.expect_eq(db.one("select seq from sqlite_sequence where name = 'sphere_box'", {}), (int64_t)99, "sphere_box's counter kept");
    t.expect_eq(db.one("select count(*) from sphere_log", {}), (int64_t)0, "(the log empty)");
    t.expect_eq(db.one("select seq from sqlite_sequence where name = 'sphere_log'", {}), (int64_t)42, "sphere_log's counter kept without rows");
    t.expect_eq(rows_over(db, "sphere_rank", "*", "season_id = 69"), (std::vector<std::string>{"1:69|1:0|5:|"}), "sphere_rank: NULL floor -> 0");
    // daily: (id, day_at, bonus_id, lot_uid, healed_at)
    t.expect_eq(rows_over(db, "favor_bonus_state", "*"), (std::vector<std::string>{"1:1|1:1790755200|1:0|5:|5:|"}),
                "favor_bonus_state: healed_at 0 -> NULL (never), lot_uid not owned -> NULL, day_at kept");
    // the rest
    t.expect_eq(rows_over(db, "meta", "*", "key = 'x_key'"), (std::vector<std::string>{"3:x_key|3:|"}), "meta: NULL value -> ''");
    t.expect_eq(rows_over(db, "stock", "*", "master_item_id = 70"), (std::vector<std::string>{"1:70|1:0|1:0|"}), "stock: NULLs -> 0");
    t.expect_eq(rows_over(db, "counters", "*", "key = 'x_count'"), (std::vector<std::string>{"3:x_count|1:0|"}), "counters: NULL -> 0");
    t.expect_eq(rows_over(db, "unlocks", "*", "mission_id in (71, 72)"), (std::vector<std::string>{"1:71|1:0|5:|1:0|", "1:72|1:1|5:|1:5|"}),
                "unlocks: by_mission never played or 0 -> NULL, NULLs -> 0");
    t.expect_eq(rows_over(db, "unlocks", "*", "mission_id < 71"), rows_over(ref, "unlocks", "*", "mission_id < 71"), "the fixture's unlock kept");
    t.expect_eq(rows_over(db, "wire_device", "uuid, player_id"), (std::vector<std::string>{"3:00000000-0000-4000-8000-000000000001|5:|"}),
                "wire_device.player_id 0 -> NULL (a device seen before the player)");
    for (const char* table : {"meta", "stock", "counters"}) {
        const std::string other = std::string(table) == "stock" ? "master_item_id != 70" : "key not like 'x_%'";
        t.expect_eq(rows_over(db, table, "*", other), rows_over(ref, table, "*", other), (std::string(table) + "'s rows kept").c_str());
    }
    for (const char* table : {"event_last", "event_rank_received", "subscription", "achievements", "gear_barney"})
        t.expect_eq(rows_over(db, table, "*"), rows_over(ref, table, "*"), (std::string(table) + " copied").c_str());
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    ref.close();
    db.close();

    // ---- (2) v9 -> v10, without the master -------------------------------------------------------------
    TempDb v9("v10-from-v9");
    if (!write_fixture(t, v9.path)) return;
    Sql f;
    if (!f.open(v9.path, false)) return t.fail("open v9");
    t.expect_eq(state::open_and_migrate(f.h, v9.path, 9, m), true, "migrated to 9");
    f.close();
    unlink((v9.path + ".bak-v0").c_str());
    if (!f.open(v9.path, false)) return t.fail("reopen v9");
    t.expect_eq(state::user_version(f.h), 9, "a version 9 file");
    t.expect_eq(state::open_and_migrate(f.h, v9.path, 10), true, "v9 -> v10");
    t.expect_eq(state::user_version(f.h), 10, "user_version 10");
    t.expect_eq(f.one("select count(*) from ds_offer where closed_at is null and ship_id = 1", {}), (int64_t)1, "the offer: no limit, on ship 1");
    t.expect_eq(f.one("select count(*) from favor_bonus_state where healed_at is null and lot_uid is not null", {}), (int64_t)1,
                "the favor bonus: never healed, its character kept");
    t.expect_eq(f.one("select count(*) from wire_device where player_id is null", {}), (int64_t)1, "the device: no player");
    t.expect_eq(fk_violations(f), 0, "foreign_key_check");
    f.close();
    Sql bak;
    if (!bak.open(v9.path + ".bak-v9", true)) return t.fail("no %s.bak-v9", v9.path.c_str());
    t.expect_eq(state::user_version(bak.h), 9, "the backup is version 9");
    t.expect_eq(bak.one("select count(*) from ds_offer where closed_at = 0", {}), (int64_t)1, "the backup keeps the 0");
    bak.close();
}

// Version 11 (PLAN-schema S12): the campaign's progress moves from the data dir's
// server_campaign.txt into campaign_clear / campaign_last. (1) v0 -> v11 with a planted file: read
// as the campaign read it (a repeated clear once, a number cut to 32 bits, a line of another word
// skipped, the last "last" wins, stopped at the first line that isn't "<word> <number>"); the file
// renamed .migrated, unchanged; every other table as the same file at version 10. Without a data
// dir nothing is imported and a file there isn't touched. (2) v10 -> v11: a "last" that isn't a
// clear is dropped; .bak-v10. (3) A step that fails leaves the file where it was. (4) A new state in
// a data dir with a file imports it (a new state and an upgraded one are the same).
NATIVE_TEST("server/schema-migrate-v11") {
    ext::Sql* master = test_master();
    sqlite3* m = master ? master->h : nullptr;
    const char* file = state::kCampaignFile;
    const char* migrated = state::kCampaignFileMigrated;
    // ---- (1) v0 -> v11 ---------------------------------------------------------------------------------
    {
        TempDb ref_file("v11-ref"), old("v11");
        TempDir dir("v11"), other("v11-none");
        if (!write_fixture(t, ref_file.path) || !write_fixture(t, old.path)) return;
        const std::string text = "clear 101\nclear 102\nclear 101\nlast 5\nclear 4294967297\nlast 102\nbogus 7\nclear 103 junk\nclear 999\n";
        dir.write(file, text);
        other.write(file, "clear 1\n");
        Sql ref, db;
        if (!ref.open(ref_file.path, false) || !db.open(old.path, false)) return t.fail("open");
        t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 10, m, other.path), true, "the reference: migrated to 10");
        t.expect_eq(other.has(file) && !other.has(migrated), true, "a step before 11 imports nothing");
        t.expect_eq(state::open_and_migrate(db.h, old.path, 11, m, dir.path), true, "v0 -> v11");
        t.expect_eq(state::user_version(db.h), 11, "user_version 11");
        t.expect_eq(rows_over(db, "campaign_clear", "*"), (std::vector<std::string>{"1:101|", "1:102|", "1:103|", "1:1|"}),
                    "campaign_clear: 101 once, 4294967297 as 1, 103 before the line that stops the read, not 999");
        t.expect_eq(rows_over(db, "campaign_last", "*"), (std::vector<std::string>{"1:1|1:102|"}), "campaign_last: the last 'last' line");
        t.expect_eq(dir.has(file), false, "the file is gone");
        t.expect_eq(dir.read(migrated), text, "kept as server_campaign.txt.migrated, unchanged");
        std::map<std::string, std::vector<std::string>> ra = rows_of(ref), rb = rows_of(db);
        rb.erase("campaign_clear");
        rb.erase("campaign_last");
        t.expect_eq(ra == rb, true, "every other table's rows as at version 10");
        t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK), 0, ".bak-v0");
        t.expect_eq(fk_violations(db), 0, "foreign_key_check");
        // no data dir: no import, the file there untouched
        t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 11, m), true, "the reference: 10 -> 11 without a data dir");
        t.expect_eq(ref.one("select count(*) from campaign_clear", {}) + ref.one("select count(*) from campaign_last", {}), (int64_t)0,
                    "nothing imported");
        t.expect_eq(other.read(file), std::string("clear 1\n"), "the other dir's file untouched");
        ref.close();
        db.close();
    }
    // ---- (2) v10 -> v11, without the master: a last play that isn't a clear --------------------------------
    {
        TempDb v10("v11-from-v10");
        TempDir dir("v11-from-v10");
        if (!write_fixture(t, v10.path)) return;
        Sql f;
        if (!f.open(v10.path, false)) return t.fail("open v10");
        t.expect_eq(state::open_and_migrate(f.h, v10.path, 10, m), true, "migrated to 10");
        f.close();
        unlink((v10.path + ".bak-v0").c_str());
        dir.write(file, "clear 7\nlast 8\n");
        if (!f.open(v10.path, false)) return t.fail("reopen v10");
        t.expect_eq(state::user_version(f.h), 10, "a version 10 file");
        t.expect_eq(state::open_and_migrate(f.h, v10.path, 11, nullptr, dir.path), true, "v10 -> v11");
        t.expect_eq(state::user_version(f.h), 11, "user_version 11");
        t.expect_eq(rows_over(f, "campaign_clear", "*"), (std::vector<std::string>{"1:7|"}), "the clear");
        t.expect_eq(f.one("select count(*) from campaign_last", {}), (int64_t)0, "the last play 8 isn't a clear: dropped");
        t.expect_eq(!dir.has(file) && dir.has(migrated), true, "renamed .migrated");
        t.expect_eq(fk_violations(f), 0, "foreign_key_check");
        f.close();
        Sql bak;
        if (!bak.open(v10.path + ".bak-v10", true)) return t.fail("no %s.bak-v10", v10.path.c_str());
        t.expect_eq(state::user_version(bak.h), 10, "the backup is version 10");
        t.expect_eq(bak.one("select count(*) from sqlite_master where name like 'campaign_%'", {}), (int64_t)0, "the backup has no campaign table");
        bak.close();
    }
    // ---- (3) a failed step leaves the file -----------------------------------------------------------------
    {
        TempDb v10("v11-fails");
        TempDir dir("v11-fails");
        if (!write_fixture(t, v10.path)) return;
        Sql f;
        if (!f.open(v10.path, false)) return t.fail("open");
        t.expect_eq(state::open_and_migrate(f.h, v10.path, 10, m), true, "migrated to 10");
        f.exec("create table campaign_clear (x integer)");  // step 11's create table fails on it
        dir.write(file, "clear 7\n");
        t.expect_eq(state::open_and_migrate(f.h, v10.path, 11, m, dir.path), false, "step 11 fails");
        t.expect_eq(state::user_version(f.h), 10, "still version 10");
        t.expect_eq(dir.has(file) && !dir.has(migrated), true, "the file stays");
        f.close();
    }
    // ---- (4) a new state in a data dir with a file ---------------------------------------------------------
    {
        TempDb fresh("v11-fresh");
        TempDir dir("v11-fresh");
        dir.write(file, "clear 9\nlast 9\n");
        Sql f;
        if (!f.open(fresh.path, false)) return t.fail("open");
        t.expect_eq(state::open_and_migrate(f.h, fresh.path, state::kSchemaVersion, m, dir.path), true, "a new state");
        t.expect_eq(rows_over(f, "campaign_last", "mission_id"), (std::vector<std::string>{"1:9|"}), "imported");
        t.expect_eq(!dir.has(file) && dir.has(migrated), true, "renamed .migrated");
        t.expect_eq(access((fresh.path + ".bak-v0").c_str(), F_OK) != 0, true, "no backup of a new file");
        f.close();
    }
}

// Version 12: player.is_3d_home (Home3DAnd2DSwitching). (1) v0 -> v12: every table's rows as the
// same file at version 11, the player's plus is_3d_home = 1 (the 3D home the server always sent);
// .bak-v0. (2) v11 -> v12 (a planted v11 file, without the master): the player 3D, .bak-v11 at 11
// without the column; the column refuses anything but 0 / 1; a new player gets 1.
NATIVE_TEST("server/schema-migrate-v12") {
    ext::Sql* master = test_master();
    sqlite3* m = master ? master->h : nullptr;
    // ---- (1) v0 -> v12 ---------------------------------------------------------------------------------
    {
        TempDb ref_file("v12-ref"), old("v12");
        if (!write_fixture(t, ref_file.path) || !write_fixture(t, old.path)) return;
        Sql ref, db;
        if (!ref.open(ref_file.path, false) || !db.open(old.path, false)) return t.fail("open");
        t.expect_eq(state::open_and_migrate(ref.h, ref_file.path, 11, m), true, "the reference: migrated to 11");
        t.expect_eq(state::open_and_migrate(db.h, old.path, 12, m), true, "v0 -> v12");
        t.expect_eq(state::user_version(db.h), 12, "user_version 12");
        t.expect_eq(db.one("select count(*) from player", {}) > 0, true, "the fixture has a player");
        t.expect_eq(db.one("select count(*) from player where is_3d_home = 1", {}), db.one("select count(*) from player", {}), "every player 3D");
        std::map<std::string, std::vector<std::string>> ra = rows_of(ref), rb = rows_of(db);
        ra.erase("player");
        rb.erase("player");
        t.expect_eq(ra == rb, true, "every other table's rows as at version 11");
        t.expect_eq(rows_over(db, "player", "id, name, level, home_uid"), rows_over(ref, "player", "id, name, level, home_uid"),
                    "the player's other columns kept");
        t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK), 0, ".bak-v0");
        t.expect_eq(fk_violations(db), 0, "foreign_key_check");
        ref.close();
        db.close();
    }
    // ---- (2) v11 -> v12, without the master ------------------------------------------------------------
    {
        TempDb v11("v12-from-v11");
        if (!write_fixture(t, v11.path)) return;
        Sql f;
        if (!f.open(v11.path, false)) return t.fail("open v11");
        t.expect_eq(state::open_and_migrate(f.h, v11.path, 11, m), true, "migrated to 11");
        f.close();
        unlink((v11.path + ".bak-v0").c_str());
        if (!f.open(v11.path, false)) return t.fail("reopen v11");
        t.expect_eq(state::user_version(f.h), 11, "a version 11 file");
        t.expect_eq(state::open_and_migrate(f.h, v11.path, 12), true, "v11 -> v12");
        t.expect_eq(state::user_version(f.h), 12, "user_version 12");
        t.expect_eq(f.one("select min(is_3d_home) from player", {}), (int64_t)1, "the existing player: 3D");
        t.expect_eq(sqlite3_exec(f.h, "update player set is_3d_home = 2", nullptr, nullptr, nullptr) != SQLITE_OK, true, "is_3d_home is 0 or 1");
        t.expect_eq(sqlite3_exec(f.h, "update player set is_3d_home = 0", nullptr, nullptr, nullptr), SQLITE_OK, "0: the 2D home");
        t.expect_eq(fk_violations(f), 0, "foreign_key_check");
        f.close();
        Sql bak;
        if (!bak.open(v11.path + ".bak-v11", true)) return t.fail("no %s.bak-v11", v11.path.c_str());
        t.expect_eq(state::user_version(bak.h), 11, "the backup is version 11");
        t.expect_eq(bak.one("select count(*) from pragma_table_info('player') where name = 'is_3d_home'", {}), (int64_t)0,
                    "the backup has no is_3d_home");
        bak.close();
    }
}

NATIVE_TEST("server/schema-fk-actions") {
    TempDb file("fk");
    if (!write_fixture(t, file.path)) return;
    Sql db;
    if (!db.open(file.path, false)) return t.fail("open");
    ext::Sql* master = test_master();
    t.expect_eq(state::open_and_migrate(db.h, file.path, state::kSchemaVersion, master ? master->h : nullptr), true, "migrated");
    t.expect_eq(db.one("pragma foreign_keys", {}), (int64_t)1, "foreign keys on");
    // a statement's result: SQLITE_OK, or its extended error code (not logged: failures are expected)
    auto rc = [&](const std::string& sql) {
        int r = sqlite3_exec(db.h, sql.c_str(), nullptr, nullptr, nullptr);
        return r == SQLITE_OK ? SQLITE_OK : sqlite3_extended_errcode(db.h);
    };
    // a transaction of `sql`: the commit's result (rolled back when refused)
    auto txn = [&](const std::string& sql) {
        if (rc("begin immediate") != SQLITE_OK) return -1;
        int r = rc(sql);
        if (r == SQLITE_OK) r = rc("commit");
        if (r != SQLITE_OK) rc("rollback");
        return r;
    };
    const std::string a = std::to_string(db.one("select min(uid) from roster", {}));
    const std::string b = std::to_string(db.one("select min(uid) from roster where uid > ?", {std::stoll(a)}));
    const std::string c = std::to_string(db.one("select min(uid) from roster where uid > ?", {std::stoll(b)}));
    const std::string item1 = std::to_string(db.one("select min(uid) from items", {}));
    const std::string item2 = std::to_string(db.one("select min(uid) from items where uid > ?", {std::stoll(item1)}));
    const std::string title = std::to_string(db.one("select min(id) from titles", {}));
    const std::string gear_set = std::to_string(db.one("select min(uid) from gear_items where item_uid is not null", {}));
    const std::string gear_free = std::to_string(db.one("select min(uid) from gear_items where item_uid is null", {}));
    t.expect_eq(gear_set != "0" && gear_free != "0", true, "a set and a free gear (the fixture's)");
    // the references: a wears item1 and item2, has b as assist; the player's home c, support b, title
    t.expect_eq(rc("update roster set weapon_uid = null, accessory_uid = null, assist_uid = null;"
                   "update roster set weapon_uid = " +
                   item1 + ", accessory_uid = " + item2 + ", assist_uid = " + b + " where uid = " + a +
                   ";"
                   "update player set home_uid = " +
                   c + ", support_uid = " + b + ", title_id = " + title),
                SQLITE_OK, "the references set");
    // set 3's slot 0: a, wearing item1 and item2 in the set, b as its assist
    t.expect_eq(rc("insert into party_member (party_id, slot, uid, weapon_uid, accessory_uid, assist_uid) values (3, 0, " + a + ", " + item1 + ", " +
                   item2 + ", " + b + "), (4, 0, " + b + ", null, null, null)"),
                SQLITE_OK, "set 3's and set 4's members");
    // the free gear set in item1's slot 1 (the other gear stays in its weapon's slot 0)
    t.expect_eq(rc("update gear_items set item_uid = " + item1 + ", slot = 1 where uid = " + gear_free), SQLITE_OK, "a gear set in item1");

    // dangling writes: the immediate ones fail at the statement, the deferred ones at commit
    for (const std::string& sql : {"update roster set weapon_uid = 9999 where uid = " + b, "update roster set accessory_uid = 9999 where uid = " + b,
                                   "update roster set assist_uid = 9999 where uid = " + b, std::string("update player set support_uid = 9999"),
                                   std::string("update player set title_id = 9999"), "update gear_items set item_uid = 9999 where uid = " + gear_set})
        t.expect_eq(rc(sql), SQLITE_CONSTRAINT_FOREIGNKEY, (sql + ": refused at once").c_str());
    for (const std::string& sql : {std::string("update party_member set uid = 9999 where party_id = 3"),
                                   std::string("update party_member set weapon_uid = 9999 where party_id = 3"),
                                   std::string("update party_member set accessory_uid = 9999 where party_id = 3"),
                                   std::string("update party_member set assist_uid = 9999 where party_id = 3"),
                                   std::string("insert into party_member (party_id, slot) values (99, 0)")})
        t.expect_eq(rc(sql), SQLITE_CONSTRAINT_FOREIGNKEY, (sql + ": refused at once").c_str());
    t.expect_eq(rc("insert into party_member (party_id, slot, uid) values (3, 1, null)"), SQLITE_OK, "an empty slot (NULL uid)");
    t.expect_eq(rc("insert into party_member (party_id, slot) values (3, 4)"), SQLITE_CONSTRAINT_CHECK, "slot 4: refused");
    t.expect_eq(rc("insert into party_set (party_id) values (0)"), SQLITE_CONSTRAINT_CHECK, "set 0: refused");
    t.expect_eq(rc("update party_set set is_lock = 2 where party_id = 3"), SQLITE_CONSTRAINT_CHECK, "party_set.is_lock 0 / 1");
    t.expect_eq(rc("update party_member set skill_id1 = 'x' where party_id = 3"), SQLITE_CONSTRAINT_DATATYPE, "STRICT party_member");
    t.expect_eq(rc("update party_set set icon_id = 'x' where party_id = 3"), SQLITE_CONSTRAINT_DATATYPE, "STRICT party_set");
    // S7: the play and its members, a ship's crew, the departures
    t.expect_eq(db.one("select count(*) from play_member where play_id = 1", {}), (int64_t)2, "the fixture's play: a and b");
    t.expect_eq(db.one("select count(*) from ds_ship_member where ship_id = 1", {}), (int64_t)2, "the fixture's ship 1: a and b");
    for (const std::string& sql :
         {std::string("update play_member set uid = 9999 where slot = 0"),
          std::string("insert into play_member (play_id, slot, uid) values (2, 0, null)"), std::string("update play set party_id = 99"),
          std::string("insert into ds_ship_member (ship_id, slot, uid) values (1, 3, 9999)"),
          "insert into ds_ship_member (ship_id, slot, uid) values (99, 1, " + c + ")"})
        t.expect_eq(rc(sql), SQLITE_CONSTRAINT_FOREIGNKEY, (sql + ": refused at once").c_str());
    t.expect_eq(rc("update play_member set npc_uid = 2130706433 where slot = 0"), SQLITE_CONSTRAINT_CHECK, "a member is a character or an NPC");
    t.expect_eq(rc("insert into play_member (slot, uid, npc_uid) values (5, null, 2130706433)"), SQLITE_OK, "an NPC member");
    t.expect_eq(rc("update play set surprise = 2"), SQLITE_CONSTRAINT_CHECK, "play.surprise 0 / 1");
    t.expect_eq(rc("update play set helper_kind = 4"), SQLITE_CONSTRAINT_CHECK, "play.helper_kind 0..3");
    t.expect_eq(rc("insert into ds_ship_member (ship_id, slot, uid) values (1, 9, " + c + ")"), SQLITE_CONSTRAINT_CHECK, "ship slot 9");
    t.expect_eq(rc("insert into ds_ship_member (ship_id, slot, uid) values (1, 3, null)"), SQLITE_CONSTRAINT_NOTNULL,
                "a crew slot names a character");
    t.expect_eq(rc("update play set mission_id = 'x'"), SQLITE_CONSTRAINT_DATATYPE, "STRICT play");
    t.expect_eq(rc("update play_member set slot = 'x' where slot = 5"), SQLITE_CONSTRAINT_DATATYPE, "STRICT play_member");
    t.expect_eq(rc("update ds_ship_member set slot = 'x' where slot = 1"), SQLITE_CONSTRAINT_DATATYPE, "STRICT ds_ship_member");
    t.expect_eq(rc("insert into ds_log (mission_id, started_at) values ('x', 0)"), SQLITE_CONSTRAINT_DATATYPE, "STRICT ds_log");
    t.expect_eq(rc("insert into ds_log (mission_id, started_at) values (1, 0)"), SQLITE_OK, "a departure");
    t.expect_eq(db.one("select id from ds_log where mission_id = 1 and started_at = 0", {}), db.one("select max(id) from ds_log", {}),
                "ds_log: its id, the last");
    t.expect_eq(rc("delete from party_set where party_id = 4"), SQLITE_OK, "set 4 deleted");
    t.expect_eq(db.one("select count(*) from party_member where party_id = 4", {}), (int64_t)0, "ON DELETE CASCADE: its members are gone");
    for (const std::string& sql : {std::string("update player set home_uid = 9999"), std::string("update player set party_id = 99"),
                                   std::string("delete from party_set where party_id = (select party_id from player)")})
        t.expect_eq(txn(sql), SQLITE_CONSTRAINT_FOREIGNKEY, (sql + ": refused at commit").c_str());
    t.expect_eq(txn("update player set home_uid = 9999; update player set home_uid = " + c), SQLITE_OK, "deferred: fixed before commit");
    t.expect_eq(txn("delete from party_set where party_id = 9"), SQLITE_OK, "a set that isn't current can go");
    // no ON UPDATE: a referenced key doesn't change
    t.expect_eq(rc("update roster set uid = 1 where uid = " + b), SQLITE_CONSTRAINT_FOREIGNKEY, "a referenced roster uid: refused at once");
    t.expect_eq(rc("update items set uid = 1 where uid = " + item1), SQLITE_CONSTRAINT_FOREIGNKEY, "a worn item's uid: refused");
    t.expect_eq(txn("update party_set set party_id = 99 where party_id = (select party_id from player)"), SQLITE_CONSTRAINT_FOREIGNKEY,
                "the current set's id: refused at commit");
    // the unique indexes: one character per item, one assisted character per assist
    t.expect_eq(rc("update roster set weapon_uid = " + item1 + " where uid = " + b), SQLITE_CONSTRAINT_UNIQUE, "an item worn twice: refused");
    t.expect_eq(rc("update roster set assist_uid = " + b + " where uid = " + c), SQLITE_CONSTRAINT_UNIQUE, "an assist of two characters: refused");
    t.expect_eq(rc("update gear_items set item_uid = " + item1 + ", slot = 1 where uid = " + gear_set), SQLITE_CONSTRAINT_UNIQUE,
                "two gears in one weapon slot: refused");
    t.expect_eq(rc("update gear_items set item_uid = " + item1 + ", slot = 0 where uid = " + gear_set), SQLITE_OK, "another slot of it: fine");
    t.expect_eq(rc("insert into gear_items (uid, master_item_id, item_uid, slot, created_at) values (1, 1, null, 0, 0), (2, 1, null, 0, 0)"),
                SQLITE_OK, "gears in the box share slot 0");
    t.expect_eq(rc("delete from gear_items where uid in (1, 2)"), SQLITE_OK, "(removed again)");
    // the 0 / 1 checks
    t.expect_eq(rc("update items set locked = 2 where uid = " + item1), SQLITE_CONSTRAINT_CHECK, "items.locked 0 / 1");
    t.expect_eq(rc("update gear_items set is_new = 2 where uid = " + gear_set), SQLITE_CONSTRAINT_CHECK, "gear_items.is_new 0 / 1");
    // STRICT: a value of the wrong type is refused, not stored
    t.expect_eq(rc("update roster set level = 'high' where uid = " + a), SQLITE_CONSTRAINT_DATATYPE, "STRICT roster");
    t.expect_eq(rc("update player set level = 'high'"), SQLITE_CONSTRAINT_DATATYPE, "STRICT player");
    t.expect_eq(rc("update items set level = 'high' where uid = " + item1), SQLITE_CONSTRAINT_DATATYPE, "STRICT items");
    t.expect_eq(rc("update gear_items set slot = 'high' where uid = " + gear_set), SQLITE_CONSTRAINT_DATATYPE, "STRICT gear_items");
    t.expect_eq(rc("update presents set num = 'many'"), SQLITE_CONSTRAINT_DATATYPE, "STRICT presents (S8)");
    // S9: the boolean checks and STRICT on the rebuilt tables; titles is still player.title_id's parent
    for (const std::string& sql : {std::string("update ds_area set is_new = 2"), std::string("update ds_area set is_last_play = 2"),
                                   std::string("update mission set cleared = 2"), std::string("update follow_rental set paid = 2"),
                                   std::string("update sphere_rental_day set paid = 2"), std::string("update event_rank_score set fresh = 2"),
                                   std::string("update wboss set hunt_new = 2"), std::string("update sphere_cell set cleared = 2"),
                                   std::string("update sphere_cell set playing = 2"), std::string("update sphere_rental set used = 2")})
        t.expect_eq(rc(sql), SQLITE_CONSTRAINT_CHECK, (sql + ": refused (S9)").c_str());
    for (const std::string& sql :
         {std::string("update favor set event_drop_at = '2026-10-01 04:00:00'"), std::string("update favor set tapped_at = 'x'"),
          std::string("update titles set got_at = 'x'"), std::string("update login_bonus set day_index = 'x'"),
          std::string("update premium_pass set last_at = 'x'"), std::string("update mission set play_count = 'x'"),
          std::string("update wboss set wave = 'x'"), std::string("update sphere_cell set floor_level = 'x'")})
        t.expect_eq(rc(sql), SQLITE_CONSTRAINT_DATATYPE, (sql + ": STRICT (S9)").c_str());
    t.expect_eq(rc("insert into login_bonus (id, last_at) values (1, 0)"), SQLITE_CONSTRAINT_NOTNULL, "login_bonus.day_index not null (S9)");
    // S10: the module tables' references refused when dangling, their checks and STRICT
    for (const std::string& sql : {std::string("update ds_offer set ship_id = 99"), std::string("update ds_offer set area_id = 99"),
                                   std::string("insert into ds_ship (ship_id, area_id, mission_id, started_at) values (9, 99, 1, 0)"),
                                   std::string("insert into ds_bonus (ship_id, bonus_id, value) values (99, 1, 1.0)")})
        t.expect_eq(rc(sql), SQLITE_CONSTRAINT_FOREIGNKEY, (sql + ": refused at once (S10)").c_str());
    t.expect_eq(rc("insert into sphere_departed (uid) values (9999)"), SQLITE_CONSTRAINT_FOREIGNKEY, "sphere_departed: refused at once (S10)");
    t.expect_eq(rc("update favor_bonus_state set lot_uid = 9999"), SQLITE_CONSTRAINT_FOREIGNKEY, "favor_bonus_state.lot_uid: refused at once (S10)");
    t.expect_eq(rc("update wire_device set player_id = 9999"), SQLITE_CONSTRAINT_FOREIGNKEY, "wire_device.player_id: refused at once (S10)");
    t.expect_eq(rc("update wire_device set player_id = (select id from player)"), SQLITE_OK, "the device: the player's");
    t.expect_eq(txn("insert into unlocks (mission_id, mission_type, by_mission, at) values (73, 1, 4243, 0)"), SQLITE_CONSTRAINT_FOREIGNKEY,
                "an unlock by a mission never played: refused at commit (S10)");
    t.expect_eq(txn("insert into unlocks (mission_id, mission_type, by_mission, at) values (73, 1, 4243, 0);"
                    "insert into mission (mission_id) values (4243)"),
                SQLITE_OK, "deferred: the mission's row before commit (MissionEnd's order, S10)");
    t.expect_eq(rc("delete from mission where mission_id = 4243"), SQLITE_CONSTRAINT_FOREIGNKEY, "a mission that unlocked one: NO ACTION");
    t.expect_eq(rc("insert into meta (key) values ('y')"), SQLITE_CONSTRAINT_NOTNULL, "meta.value not null (S10)");
    t.expect_eq(rc("update gear_barney set id = 2"), SQLITE_CONSTRAINT_CHECK, "gear_barney: one row");
    t.expect_eq(rc("update favor_bonus_state set id = 2"), SQLITE_CONSTRAINT_CHECK, "favor_bonus_state: one row");
    t.expect_eq(rc("insert into gacha_history (gacha_id, at, character_uid, rank) values (1, 0, 9999, 'S')"), SQLITE_CONSTRAINT_FOREIGNKEY,
                "gacha_history.character_uid: refused at once (S10)");
    t.expect_eq(rc("insert into gacha_history (gacha_id, at, item_uid, rank) values (1, 0, 9999, 'S')"), SQLITE_CONSTRAINT_FOREIGNKEY,
                "gacha_history.item_uid: refused at once (S10)");
    t.expect_eq(rc("insert into box_slots (gacha_id, slot_id, drawn) values (9999, 1, 1)"), SQLITE_CONSTRAINT_FOREIGNKEY,
                "box_slots without its box: refused at once (S10)");
    // a boss's clear: deferred, so a first meeting's clear can come before the boss's row (MissionEnd)
    t.expect_eq(txn("insert into wboss_clear (boss_id, wave) values (4242, 1)"), SQLITE_CONSTRAINT_FOREIGNKEY,
                "a clear of a boss never met: refused at commit (S10)");
    t.expect_eq(txn("insert into wboss_clear (boss_id, wave) values (4242, 1); insert into wboss (boss_id, area_id) values (4242, 1)"), SQLITE_OK,
                "deferred: the boss's row before commit (S10)");
    for (const std::string& sql : {std::string("update ds_offer set is_new = 2"), std::string("update gacha_history set duplicate = 2"),
                                   std::string("update wboss_clear set notified = 2")})
        t.expect_eq(rc(sql), SQLITE_CONSTRAINT_CHECK, (sql + ": refused (S10)").c_str());
    for (const std::string& sql : {std::string("update ds_offer set closed_at = 'x'"),
                                   std::string("update ds_ship set started_at = 'x'"),
                                   std::string("update ds_bonus set value = 'x'"),
                                   std::string("update gacha_history set at = 'x'"),
                                   std::string("update stepup set try_count = 'x'"),
                                   std::string("update box_slots set drawn = 'x'"),
                                   std::string("update wboss set hunt_until = 'x'"),
                                   std::string("update wboss_clear set cleared_at = 'x'"),
                                   std::string("update event_last set mission_id = 'x'"),
                                   std::string("update event_rank_received set received_at = 'x'"),
                                   std::string("update favor_drop_play set lots = 'x'"),
                                   std::string("update shop_counts set total = 'x'"),
                                   std::string("update exchange_counts set num = 'x'"),
                                   std::string("update subscription set closed_at = 'x'"),
                                   std::string("update sphere set streak = 'x'"),
                                   std::string("update sphere_box set rank = 'x'"),
                                   std::string("update sphere_rank set floor_level = 'x'"),
                                   std::string("update sphere_log set at = 'x'"),
                                   std::string("update favor_bonus_state set healed_at = 'x'"),
                                   std::string("update stock set count = 'x'"),
                                   std::string("update counters set value = 'x'"),
                                   std::string("update achievements set progress = 'x'"),
                                   std::string("update gear_barney set type = 'x'"),
                                   std::string("update unlocks set at = 'x'"),
                                   std::string("update wire_device set last_seen = 'x'")})
        t.expect_eq(rc(sql), SQLITE_CONSTRAINT_DATATYPE, (sql + ": STRICT (S10)").c_str());
    t.expect_eq(rc("insert into presents (content_type, num, reason_type) values (4, 1, 1)"), SQLITE_CONSTRAINT_NOTNULL,
                "a present has its created_at (S8)");

    // S10, gacha: a box's slots go with it; a drawn character or weapon gone leaves its draw
    t.expect_eq(rc("insert into gacha_history (gacha_id, at, role_id, character_uid, rank) values (1, 0, 1, " + a +
                   ", 'S');"
                   "insert into gacha_history (gacha_id, at, item_uid, rank) values (1, 0, " +
                   item1 + ", 'S')"),
                SQLITE_OK, "a's draw and item1's");
    const int64_t box = db.one("select min(gacha_id) from box_slots", {});
    t.expect_eq(box != 0, true, "the fixture's box has drawn slots");
    t.expect_eq(rc("delete from box_state where gacha_id = " + std::to_string(box)), SQLITE_OK, "the box deleted");
    t.expect_eq(db.one("select count(*) from box_slots where gacha_id = ?", {box}), (int64_t)0, "ON DELETE CASCADE: its slots are gone");
    // S10, events: a boss's clears go with it
    t.expect_eq(db.one("select count(*) from wboss_clear where boss_id = 4242", {}), (int64_t)1, "boss 4242's clear");
    t.expect_eq(rc("delete from wboss where boss_id = 4242"), SQLITE_OK, "boss 4242 deleted");
    t.expect_eq(db.one("select count(*) from wboss_clear where boss_id = 4242", {}), (int64_t)0, "ON DELETE CASCADE: its clears are gone");

    // ON DELETE SET NULL
    t.expect_eq(rc("delete from items where uid = " + item1), SQLITE_OK, "an item deleted");
    t.expect_eq(db.one("select count(*) from gacha_history where item_uid is null and at = 0 and role_id is null", {}), (int64_t)1,
                "gacha_history.item_uid -> NULL (S10)");
    t.expect_eq(db.one("select count(*) from roster where uid = ? and weapon_uid is null and accessory_uid = ?", {std::stoll(a), std::stoll(item2)}),
                (int64_t)1, "its wearer's weapon_uid -> NULL");
    t.expect_eq(db.one("select count(*) from gear_items where uid in (" + gear_set + ", " + gear_free + ")", {}), (int64_t)0,
                "ON DELETE CASCADE: the gears set in it are gone");
    t.expect_eq(
        db.one("select count(*) from party_member where party_id = 3 and slot = 0 and weapon_uid is null and accessory_uid = ?", {std::stoll(item2)}),
        (int64_t)1, "the set's weapon_uid -> NULL");
    t.expect_eq(rc("delete from items where uid = " + item2), SQLITE_OK, "the accessory deleted");
    t.expect_eq(db.one("select count(*) from party_member where party_id = 3 and slot = 0 and accessory_uid is null", {}), (int64_t)1,
                "the set's accessory_uid -> NULL");
    t.expect_eq(db.one("select count(*) from roster where uid = ? and accessory_uid is null", {std::stoll(a)}), (int64_t)1, "accessory_uid -> NULL");
    t.expect_eq(rc("delete from roster where uid = " + b), SQLITE_CONSTRAINT_FOREIGNKEY, "a character out on a ship: refused (NO ACTION)");
    t.expect_eq(db.one("select count(*) from ds_offer where ship_id = 1", {}), (int64_t)1, "the fixture's offer: on ship 1");
    t.expect_eq(db.one("select count(*) from ds_bonus where ship_id = 1", {}), (int64_t)1, "the fixture's ship 1: a bonus value");
    t.expect_eq(rc("delete from ds_ship where ship_id = 1"), SQLITE_OK, "ship 1 deleted");
    t.expect_eq(db.one("select count(*) from ds_ship_member", {}), (int64_t)0, "ON DELETE CASCADE: its crew is gone");
    t.expect_eq(db.one("select count(*) from ds_bonus", {}), (int64_t)0, "ON DELETE CASCADE: its bonus values are gone (S10)");
    t.expect_eq(db.one("select count(*) from ds_offer where ship_id is null", {}), db.one("select count(*) from ds_offer", {}),
                "ON DELETE SET NULL: its offer is on no ship (S10)");
    // S10, deep space: an area's offers and ships go with it
    t.expect_eq(rc("insert into ds_ship (ship_id, area_id, mission_id, started_at) values (5, (select min(area_id) from ds_area), 1, 0);"
                   "insert into ds_bonus (ship_id, bonus_id, value) values (5, 1, 1.0);"
                   "update ds_offer set ship_id = 5"),
                SQLITE_OK, "ship 5 out, the offer on it");
    t.expect_eq(rc("delete from ds_area"), SQLITE_OK, "the area deleted");
    t.expect_eq(
        db.one("select count(*) from ds_offer", {}) + db.one("select count(*) from ds_ship", {}) + db.one("select count(*) from ds_bonus", {}),
        (int64_t)0, "ON DELETE CASCADE: its offers, its ship and the ship's bonus values are gone");
    t.expect_eq(db.one("select count(*) from sphere_departed where uid = ?", {std::stoll(b)}), (int64_t)1, "b departed (the fixture's)");
    t.expect_eq(rc("delete from roster where uid = " + b), SQLITE_OK, "the assist and support character deleted");
    t.expect_eq(db.one("select count(*) from sphere_departed where uid = ?", {std::stoll(b)}), (int64_t)0,
                "ON DELETE CASCADE: b's sortie is gone (S10)");
    t.expect_eq(db.one("select count(*) from play_member where slot = 1 and uid is null", {}), (int64_t)1, "play_member.uid -> NULL (b)");
    t.expect_eq(db.one("select count(*) from roster where uid = ? and assist_uid is null", {std::stoll(a)}), (int64_t)1, "assist_uid -> NULL");
    t.expect_eq(db.one("select count(*) from player where support_uid is null", {}), (int64_t)1, "support_uid -> NULL");
    t.expect_eq(db.one("select count(*) from party_member where party_id = 3 and slot = 0 and assist_uid is null", {}), (int64_t)1,
                "the set's assist_uid -> NULL");
    t.expect_eq(rc("update favor_bonus_state set lot_uid = " + a), SQLITE_OK, "a is the favor bonus's character");
    t.expect_eq(rc("delete from roster where uid = " + a), SQLITE_OK, "set 3's member deleted");
    t.expect_eq(db.one("select count(*) from favor_bonus_state where lot_uid is null", {}), (int64_t)1, "favor_bonus_state.lot_uid -> NULL (S10)");
    t.expect_eq(db.one("select count(*) from gacha_history where character_uid is null and at = 0 and role_id = 1", {}), (int64_t)1,
                "gacha_history.character_uid -> NULL (S10)");
    t.expect_eq(db.one("select count(*) from party_member where party_id = 3 and slot = 0 and uid is null", {}), (int64_t)1,
                "party_member.uid -> NULL (an empty slot)");
    t.expect_eq(txn("delete from roster where uid = " + c), SQLITE_OK, "the home character deleted");
    t.expect_eq(db.one("select count(*) from player where home_uid is null", {}), (int64_t)1,
                "home_uid -> NULL (the deferred FK's action is at once)");
    t.expect_eq(db.one("select count(*) from play_member where slot = 0 and uid is null", {}), (int64_t)1, "play_member.uid -> NULL (a)");
    t.expect_eq(rc("insert into party_set (party_id) values (20); update play set party_id = 20; delete from party_set where party_id = 20"),
                SQLITE_OK, "the play's set deleted");
    t.expect_eq(db.one("select count(*) from play where party_id is null", {}), (int64_t)1, "play.party_id -> NULL");
    t.expect_eq(rc("delete from play"), SQLITE_OK, "the play ended");
    t.expect_eq(db.one("select count(*) from play_member", {}), (int64_t)0, "ON DELETE CASCADE: its members are gone");
    t.expect_eq(rc("delete from titles where id = " + title), SQLITE_OK, "the worn title deleted");
    t.expect_eq(db.one("select count(*) from player where title_id is null", {}), (int64_t)1, "title_id -> NULL");
    // the campaign (S12): the last play is a clear; it goes with it
    t.expect_eq(rc("insert into campaign_last (id, mission_id) values (1, 555)"), SQLITE_CONSTRAINT_FOREIGNKEY,
                "campaign_last refused without its clear");
    t.expect_eq(rc("insert into campaign_clear (mission_id) values (555); insert into campaign_last (id, mission_id) values (1, 555)"), SQLITE_OK,
                "a clear and the last play");
    t.expect_eq(rc("insert into campaign_last (id, mission_id) values (2, 555)"), SQLITE_CONSTRAINT_CHECK, "one last play (id 1)");
    t.expect_eq(rc("insert into campaign_clear (mission_id) values ('x')"), SQLITE_MISMATCH, "campaign_clear is STRICT (its key, the rowid)");
    t.expect_eq(rc("delete from campaign_clear where mission_id = 555"), SQLITE_OK, "the clear deleted");
    t.expect_eq(db.one("select count(*) from campaign_last", {}), (int64_t)0, "ON DELETE CASCADE: the last play is gone (S12)");
    t.expect_eq(txn("delete from player"), SQLITE_OK, "the player deleted");
    t.expect_eq(db.one("select count(*) from wire_device where player_id is null", {}), (int64_t)1, "wire_device.player_id -> NULL (S10)");
    t.expect_eq(fk_violations(db), 0, "foreign_key_check");
    db.close();
}

// A file newer than this build isn't opened, and isn't modified (PLAN-schema 4.1: no
// down-migration; a .bak is the way back).
NATIVE_TEST("server/schema-newer-refused") {
    TempDb newer("newer");
    {
        Sql db;
        if (!db.open(newer.path, false)) return t.fail("open");
        db.exec("create table player (id integer primary key); insert into player (id) values (1); pragma user_version = " +
                std::to_string(state::kSchemaVersion + 1));
        db.close();
    }
    auto bytes = [&] {
        std::ifstream f(newer.path, std::ios::binary);
        return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    };
    std::string before = bytes();
    Sql db;
    if (!db.open(newer.path, false)) return t.fail("reopen");
    t.expect_eq(state::open_and_migrate(db.h, newer.path), false, "refused");
    db.close();
    std::string master, save;
    if (scratch_inputs(master, save)) {
        Server sv;
        if (sv.m.open(master, true)) t.expect_eq(sv.open_state(newer.path, 1, save), false, "the server refuses it");
        t.expect_eq(sv.st.h == nullptr, true, "and holds no handle");
        sv.m.close();
    }
    t.expect_eq(bytes() == before, true, "the file is unchanged");
    t.expect_eq(access((newer.path + "-wal").c_str(), F_OK) != 0, true, "no WAL made");
    t.expect_eq(access((newer.path + ".bak-v0").c_str(), F_OK) != 0, true, "no backup made");
}

}  // namespace
}  // namespace soa::server
