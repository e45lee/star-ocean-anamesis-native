#pragma once
// The state DB's schema as ordered migration steps (server/PLAN-schema.md 3.1, 4.1; port code, not
// guest behaviour). The version is the file's `pragma user_version`; step N takes a file from N-1
// to N, in one transaction (state.cpp open_and_migrate). A fresh DB runs every step from 0, so a
// new state and an upgraded one are the same by construction. Every table of the state is created
// here (none by a module, none lazily): a module that needs a new table or column adds a step.
#include <sqlite3.h>

#include <string>
#include <vector>

namespace soa::server::state {

// The version this build writes and reads; a file with a higher user_version isn't opened.
constexpr int kSchemaVersion = 20;

struct Step {
    int version;                    // user_version after the step
    const char* what;               // one line for the log and the tests
    std::vector<const char*> sql;   // DDL (and data mapping), run in order
    // C++ after the SQL (data mapping, repairs); nullptr: none. False fails the step. `master` is the
    // master DB (read-only; nullptr in the tests that migrate without one: the step's default).
    bool (*fn)(sqlite3* db, sqlite3* master);
    // Imports a side file of the server's data dir into the step's transaction (S12: the campaign's
    // server_campaign.txt), after `fn`; nullptr: none. Runs only when the opener names the data dir
    // (open_and_migrate's `data_dir`, "" = none: the scratch servers and the tests that don't plant
    // one). False fails the step.
    bool (*import)(sqlite3* db, const std::string& data_dir) = nullptr;
    // After the step's commit (with the same `data_dir`): what the import leaves behind (S12 renames
    // the imported file to <file>.migrated). Not run when the step failed, so the file stays.
    void (*committed)(const std::string& data_dir) = nullptr;
};

// The campaign's side file (S12; before version 11 its progress lived there): its name in the data
// dir, and what step 11 renames it to once imported.
constexpr const char* kCampaignFile = "server_campaign.txt";
constexpr const char* kCampaignFileMigrated = "server_campaign.txt.migrated";

// The steps, version 1 .. kSchemaVersion, in order.
const std::vector<Step>& steps();

// Step 1's statements: the baseline schema (today's 58 tables, verbatim). The tests build a
// reference DB from them.
const std::vector<const char*>& baseline_sql();

}  // namespace soa::server::state
