// lib_sqlite_master.h: test support for the differential tests that run the game's queries on the 3.7.0
// master (lib_sqlite_test.cpp, yayoi_sqlite_driver_test.cpp): the master staged at an Android path, the
// query corpus. Implemented in lib_sqlite_master.cpp.
#pragma once

#include <sqlite3.h>

#include <map>
#include <set>
#include <string>
#include <vector>

#include "native/common/test.h"

namespace soa::native::lib_sqlite {

// The 3.7.0 master (data/basmaster-3.7.0.sqlite3) copied to guest_internal_dir()/PID-file_name (one
// per process: the data directory is shared); returns the guest (Android) path, *host_copy the host
// file. "" (and a failure) without the master.
std::string stage_master(TestContext& t, std::string* host_copy, const char* file_name);

// One query of the corpus: SQL with '?' placeholders and their values (bound as text).
struct Query {
    std::string sql;
    std::vector<std::string> params;
};

// Helper database (the host SQLite on the master file directly): the tables' columns and values to
// instantiate the templates with.
struct Master {
    sqlite3* db = nullptr;
    std::map<std::string, std::set<std::string>> columns;
    ~Master() {
        if (db) sqlite3_close(db);
    }
    bool open(const std::string& path) {
        if (sqlite3_open_v2(path.c_str(), &db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) return false;
        for (auto& tb : strings("SELECT name FROM sqlite_master WHERE type='table'"))
            for (auto& c : strings("SELECT name FROM pragma_table_info('" + tb + "')")) columns[tb].insert(c);
        return true;
    }
    std::vector<std::string> strings(const std::string& sql) {
        std::vector<std::string> v;
        sqlite3_stmt* st = nullptr;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &st, nullptr) != SQLITE_OK) return v;
        while (sqlite3_step(st) == SQLITE_ROW) {
            const unsigned char* s = sqlite3_column_text(st, 0);
            v.push_back(s ? (const char*)s : "");
        }
        sqlite3_finalize(st);
        return v;
    }
    // Rows of the given columns: up to n, spread over the table (plus the value tuples' SQL literals).
    std::vector<std::vector<std::string>> samples(const std::string& tb, const std::vector<std::string>& cols, size_t n, bool literal) {
        std::string list;
        for (auto& c : cols) list += (list.empty() ? "" : ", ") + std::string(literal ? "quote(" : "") + "`" + c + "`" + (literal ? ")" : "");
        std::string where;
        for (auto& c : cols) where += (where.empty() ? " WHERE " : " AND ") + std::string("`") + c + "` IS NOT NULL";
        std::vector<std::vector<std::string>> all;
        sqlite3_stmt* st = nullptr;
        std::string sql = "SELECT DISTINCT " + list + " FROM `" + tb + "`" + where;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &st, nullptr) != SQLITE_OK) return all;
        while (sqlite3_step(st) == SQLITE_ROW) {
            std::vector<std::string> r;
            for (size_t k = 0; k < cols.size(); k++) {
                const unsigned char* s = sqlite3_column_text(st, (int)k);
                r.push_back(s ? (const char*)s : "");
            }
            all.push_back(std::move(r));
        }
        sqlite3_finalize(st);
        if (all.size() <= n) return all;
        std::vector<std::vector<std::string>> out;
        for (size_t k = 0; k < n; k++) out.push_back(all[k * all.size() / n]);
        return out;
    }
};

// The game's query strings: every NUL-terminated "SELECT * FROM ..." in the 3.7.0 lib.
std::vector<std::string> lib_queries(TestContext& t);
// The whole corpus: the lib's templates, plus every table's "SELECT * FROM t" and "... WHERE id=?",
// each template instantiated with up to n tuples of the master's values plus one matching nothing.
std::vector<Query> corpus(TestContext& t, Master& m, size_t n);

}  // namespace soa::native::lib_sqlite
