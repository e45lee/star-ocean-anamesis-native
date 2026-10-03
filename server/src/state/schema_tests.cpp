// Unit tests of the state schema's migrations (state/schema.h, state/state.h; server/PLAN-schema.md
// 4.2). Run in --selftest; not differential (the server has no guest counterpart). They load the
// committed v0 fixture server/tests/fixtures/state-v0.sql (tools/make_state_fixture.py). Test names
// are their seeds (testing.h).
#include <sqlite3.h>
#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

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
        for (const char* suffix : {"", "-wal", "-shm", "-journal", ".bak-v0", ".bak-v0-journal", ".bak-v1", ".bak-v1-journal", ".bak-v2",
                                   ".bak-v2-journal", ".bak-v3", ".bak-v3-journal"})
            unlink((path + suffix).c_str());
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
    t.expect_eq(a.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)52,
                "the 58 baseline tables less the 4 S2 drops, less sphere_meta, plus ds_state (S3), less roster_ext and assist (S4)");
    t.expect_eq(a.one("select count(*) from sqlite_master where type = 'index' and name like 'roster_%'", {}), (int64_t)3,
                "roster's three unique indexes (S4)");
    t.expect_eq(a.one("select count(*) from party_set", {}), (int64_t)0, "no player: no party set rows (the seed / CreatePlayer add them)");
    for (const char* gone : {"view_flags", "gear", "box_gacha", "planets", "sphere_meta", "roster_ext", "assist"})
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
    t.expect_eq(state::open_and_migrate(f.h, v3.path), true, "v3 -> v4");
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

// The foreign keys' actions on a migrated state (PLAN-schema 3.1, 4.2; the FKs of version 4): what a
// delete or an update of a parent does to each child, and what a dangling write does.
//   roster.weapon_uid / accessory_uid -> items   ON DELETE SET NULL; a dangling write fails at once
//   roster.assist_uid -> roster                  ON DELETE SET NULL; a dangling write fails at once
//   player.home_uid -> roster                    ON DELETE SET NULL; deferred: a dangling write
//                                                fails at commit
//   player.support_uid -> roster                 ON DELETE SET NULL; a dangling write fails at once
//   player.title_id -> titles                    ON DELETE SET NULL; a dangling write fails at once
//   player.party_id -> party_set                 NO ACTION, deferred: deleting the current set (or
//                                                a dangling write) fails at commit
//   no ON UPDATE action: changing a referenced key fails (at once, or at commit for a deferred child)
// Plus the unique indexes (one character per item, one assisted character per assist) and STRICT.
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
    // the references: a wears item1 and item2, has b as assist; the player's home c, support b, title
    t.expect_eq(rc("update roster set weapon_uid = null, accessory_uid = null, assist_uid = null;"
                   "update roster set weapon_uid = " +
                   item1 + ", accessory_uid = " + item2 + ", assist_uid = " + b + " where uid = " + a +
                   ";"
                   "update player set home_uid = " +
                   c + ", support_uid = " + b + ", title_id = " + title),
                SQLITE_OK, "the references set");

    // dangling writes: the immediate ones fail at the statement, the deferred ones at commit
    for (const std::string& sql : {"update roster set weapon_uid = 9999 where uid = " + b, "update roster set accessory_uid = 9999 where uid = " + b,
                                   "update roster set assist_uid = 9999 where uid = " + b, std::string("update player set support_uid = 9999"),
                                   std::string("update player set title_id = 9999")})
        t.expect_eq(rc(sql), SQLITE_CONSTRAINT_FOREIGNKEY, (sql + ": refused at once").c_str());
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
    // STRICT: a value of the wrong type is refused, not stored
    t.expect_eq(rc("update roster set level = 'high' where uid = " + a), SQLITE_CONSTRAINT_DATATYPE, "STRICT roster");
    t.expect_eq(rc("update player set level = 'high'"), SQLITE_CONSTRAINT_DATATYPE, "STRICT player");

    // ON DELETE SET NULL
    t.expect_eq(rc("delete from items where uid = " + item1), SQLITE_OK, "an item deleted");
    t.expect_eq(db.one("select count(*) from roster where uid = ? and weapon_uid is null and accessory_uid = ?", {std::stoll(a), std::stoll(item2)}),
                (int64_t)1, "its wearer's weapon_uid -> NULL");
    t.expect_eq(rc("delete from items where uid = " + item2), SQLITE_OK, "the accessory deleted");
    t.expect_eq(db.one("select count(*) from roster where uid = ? and accessory_uid is null", {std::stoll(a)}), (int64_t)1, "accessory_uid -> NULL");
    t.expect_eq(rc("delete from roster where uid = " + b), SQLITE_OK, "the assist and support character deleted");
    t.expect_eq(db.one("select count(*) from roster where uid = ? and assist_uid is null", {std::stoll(a)}), (int64_t)1, "assist_uid -> NULL");
    t.expect_eq(db.one("select count(*) from player where support_uid is null", {}), (int64_t)1, "support_uid -> NULL");
    t.expect_eq(txn("delete from roster where uid = " + c), SQLITE_OK, "the home character deleted");
    t.expect_eq(db.one("select count(*) from player where home_uid is null", {}), (int64_t)1,
                "home_uid -> NULL (the deferred FK's action is at once)");
    t.expect_eq(rc("delete from titles where id = " + title), SQLITE_OK, "the worn title deleted");
    t.expect_eq(db.one("select count(*) from player where title_id is null", {}), (int64_t)1, "title_id -> NULL");
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
