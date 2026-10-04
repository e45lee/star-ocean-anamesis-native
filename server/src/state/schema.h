#pragma once
// The state DB's schema as ordered migration steps (server/PLAN-schema.md 3.1, 4.1; port code, not
// guest behaviour). The version is the file's `pragma user_version`; step N takes a file from N-1
// to N, in one transaction (state.cpp open_and_migrate). A fresh DB runs every step from 0, so a
// new state and an upgraded one are the same by construction. Every table of the state is created
// here (none by a module, none lazily): a module that needs a new table or column adds a step.
#include <sqlite3.h>

#include <vector>

namespace soa::server::state {

// The version this build writes and reads; a file with a higher user_version isn't opened.
constexpr int kSchemaVersion = 9;

struct Step {
    int version;                    // user_version after the step
    const char* what;               // one line for the log and the tests
    std::vector<const char*> sql;   // DDL (and data mapping), run in order
    // C++ after the SQL (data mapping, repairs); nullptr: none. False fails the step. `master` is the
    // master DB (read-only; nullptr in the tests that migrate without one: the step's default).
    bool (*fn)(sqlite3* db, sqlite3* master);
};

// The steps, version 1 .. kSchemaVersion, in order.
const std::vector<Step>& steps();

// Step 1's statements: the baseline schema (today's 58 tables, verbatim). The tests build a
// reference DB from them.
const std::vector<const char*>& baseline_sql();

}  // namespace soa::server::state
