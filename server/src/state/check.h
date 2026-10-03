#pragma once
// The state's references into the master DB, checked (server/PLAN-schema.md S0; port code, not
// guest behaviour). SQLite can't enforce them: the master is another file, read-only, replaced per
// version. So the check is report-only: a dangling id is reported, never fixed or refused (a
// master can change under a saved state). S1 runs it when the state is opened (LOGW per dangling
// reference); S11 exports it (soa-server --check-state). Today only the test
// server/schema-integrity (check_tests.cpp) calls it.
#include <sqlite3.h>

#include <cstdint>
#include <string>
#include <vector>

namespace soa::server::state {

// One state column holding master ids: the "m:" rows of PLAN-schema 1.6 (tools/schema_inventory.py
// RELS, which S11 makes the one list). `master_tables` is one table or several separated by '|'
// (the id is in one of them: the mission id spaces). `zero_is_none`: 0 means "none", not an id.
struct MasterRef {
    const char* table;
    const char* column;
    const char* master_tables;
    const char* master_column;
    bool zero_is_none;
};
const std::vector<MasterRef>& master_refs();

// A reference whose ids aren't in the master: the distinct ids, ascending.
struct Dangling {
    MasterRef ref;
    std::vector<int64_t> ids;
};

// Every master_refs() row whose state table exists (the modules create theirs lazily until S1),
// checked against `master`; NULL is never an id. Returns the references with dangling ids (empty:
// all resolve). A master table missing from `master` makes its references dangling.
std::vector<Dangling> check(sqlite3* st, sqlite3* master);

// "table.column -> master_tables.master_column: N dangling (id, id, ...)" for a log line or a test.
std::string describe(const Dangling& d);

}  // namespace soa::server::state
