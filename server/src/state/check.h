#pragma once
// The state's references into the master DB, checked (server/PLAN-schema.md S0; port code, not
// guest behaviour). SQLite can't enforce them: the master is another file, read-only, replaced per
// version. So the check is report-only: a dangling id is reported, never fixed or refused (a
// master can change under a saved state). The server runs it when the state is opened
// (state::report_master_refs: LOGW per dangling reference, PLAN-schema S1). The same check on a
// run's end state is tools/schema_inventory.py --check --strict (PLAN-schema S11: every session and
// tests/diff run), over the same list (below). The test server/schema-integrity (check_tests.cpp)
// checks it.
#include <sqlite3.h>

#include <cstdint>
#include <string>
#include <vector>

namespace soa::server::state {

// One state column holding master ids: the "m:" rows of PLAN-schema 1.6. The one list: tools/
// schema_inventory.py's RELS `m:` rows must equal master_refs() (its plain run, T0, fails otherwise). `master_tables` is one table or several separated by '|'
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

// Every master_refs() row (the state is migrated: every table exists), checked against `master`; NULL is never an id. Returns the references with dangling ids (empty:
// all resolve). A master table missing from `master` makes its references dangling.
std::vector<Dangling> check(sqlite3* st, sqlite3* master);

// "table.column -> master_tables.master_column: N dangling (id, id, ...)" for a log line or a test.
std::string describe(const Dangling& d);

}  // namespace soa::server::state
