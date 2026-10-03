#pragma once
// The state DB (server.sqlite3): opening it at this build's schema version, and the meta table's
// helpers (server/PLAN-schema.md 3.1, 4.1). Port code, not guest behaviour. The schema's steps are
// state/schema.h; the check of its references into the master is state/check.h.
#include <sqlite3.h>

#include <string>

#include "soaserver/ext.h"
#include "state/check.h"
#include "state/schema.h"

namespace soa::server::state {

// The file's `pragma user_version` (0 for a file from before PLAN-schema S1, or a new one).
int user_version(sqlite3* db);

// Brings the state DB `db` (opened read-write from `path`) to kSchemaVersion, as PLAN-schema 4.1
// says, and switches its foreign keys on. Returns false (logged; the caller doesn't use the file)
// when:
//   - its user_version is newer than this build's (the file isn't modified: an older binary can't
//     read a newer schema; there is no down-migration, a .bak is the way back);
//   - the backup or a step fails (the file stays at the last good version).
// An older file that has a player is first copied to `<path>.bak-v<version>` (sqlite3_backup).
// Each step runs in its own `begin immediate` transaction and commits only when `pragma
// foreign_key_check` is empty. Must be called outside any transaction.
bool open_and_migrate(sqlite3* db, const std::string& path);

// Runs state::check (the master references; check.h) and logs each dangling reference (LOGW).
// Report-only: a master can change under a saved state. The number of dangling references.
size_t report_master_refs(sqlite3* st, sqlite3* master);

}  // namespace soa::server::state

namespace soa::server {

// ---- the meta table (key -> text) ----------------------------------------------------------
std::string meta(ext::Ctx& ctx, const char* key, const char* dflt);
void set_meta(ext::Ctx& ctx, const char* key, const std::string& v);
// The meta counter `key`'s value, counted up (uids of new characters and items).
u64 next_uid(ext::Ctx& ctx, const char* key);
bool has_player(ext::Ctx& ctx);

}  // namespace soa::server
