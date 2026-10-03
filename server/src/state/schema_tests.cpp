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
        for (const char* suffix : {"", "-wal", "-shm", "-journal", ".bak-v0", ".bak-v0-journal"}) unlink((path + suffix).c_str());
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
    t.expect_eq(a.one("select count(*) from sqlite_master where type = 'table' and name != 'sqlite_sequence'", {}), (int64_t)58,
                "the 58 baseline tables");
    t.expect_eq(a.one("select count(*) from sqlite_master where name = 'wire_device'", {}), (int64_t)1, "wire_device on every route");
    // the new file has no player: nothing to back up
    t.expect_eq(access((fresh.path + ".bak-v0").c_str(), F_OK) != 0, true, "no backup of a new file");
    a.close();
    b.close();
}

// Version 1 (the baseline) on the v0 fixture: no data mapping, so every row stays as it was, the
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
    t.expect_eq(state::open_and_migrate(db.h, old.path), true, "migrated");
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
    t.expect_eq(state::open_and_migrate(again.h, old.path), true, "a current file opens");
    t.expect_eq(access((old.path + ".bak-v0").c_str(), F_OK) != 0, true, "no backup of a current file");
    again.close();

    // the column repair: a legacy table without a baseline column gets it, with the baseline default
    TempDb legacy("repair");
    if (!write_fixture(t, legacy.path)) return;
    Sql l;
    if (!l.open(legacy.path, false)) return t.fail("open legacy");
    l.exec("alter table roster_ext drop column equip_skill3; alter table follow_rental drop column paid");
    t.expect_eq(columns_of(l, "roster_ext").count("equip_skill3"), (size_t)0, "the legacy table lacks the column");
    t.expect_eq(state::open_and_migrate(l.h, legacy.path), true, "repaired");
    t.expect_eq(columns_of(l, "roster_ext").count("equip_skill3"), (size_t)1, "roster_ext.equip_skill3 added");
    t.expect_eq(columns_of(l, "follow_rental").count("paid"), (size_t)1, "follow_rental.paid added");
    t.expect_eq(l.one("select count(*) from roster_ext where equip_skill3 is not 0", {}), (int64_t)0, "with its default 0");
    t.expect_eq(l.one("select count(*) from follow_rental where paid is not 0", {}), (int64_t)0, "not null default 0");
    t.expect_eq(state::user_version(l.h), 1, "repaired: version 1");
    l.close();
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
