// Opening the state DB at this build's schema version, and the meta table's helpers (state/state.h;
// server/PLAN-schema.md 4.1). Port code, not guest behaviour.
#include "state/state.h"

#include <string>
#include <vector>

#include "core/log.h"

namespace soa::server::state {

namespace {

// Runs `sql`; false (logged with `what`) when it fails.
bool exec(sqlite3* db, const std::string& sql, const char* what) {
    char* err = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err) == SQLITE_OK) return true;
    LOGE("server", "state schema: %s: %s", what, err ? err : sqlite3_errmsg(db));
    sqlite3_free(err);
    return false;
}

// Whether the file has a player row (quietly false when it has no player table yet).
bool has_player_row(sqlite3* db) {
    sqlite3_stmt* s = nullptr;
    if (sqlite3_prepare_v2(db, "select count(*) from player", -1, &s, nullptr) != SQLITE_OK) {
        sqlite3_finalize(s);
        return false;
    }
    bool any = sqlite3_step(s) == SQLITE_ROW && sqlite3_column_int64(s, 0) > 0;
    sqlite3_finalize(s);
    return any;
}

// A copy of the whole DB at `to` (sqlite3_backup; an existing file there is replaced).
bool backup(sqlite3* db, const std::string& to) {
    sqlite3* dst = nullptr;
    if (sqlite3_open(to.c_str(), &dst) != SQLITE_OK) {
        LOGE("server", "state schema: can't write the backup %s: %s", to.c_str(), dst ? sqlite3_errmsg(dst) : "?");
        sqlite3_close(dst);
        return false;
    }
    sqlite3_backup* b = sqlite3_backup_init(dst, "main", db, "main");
    int rc = b ? sqlite3_backup_step(b, -1) : sqlite3_errcode(dst);
    if (b) sqlite3_backup_finish(b);
    bool ok = rc == SQLITE_DONE;
    if (!ok) LOGE("server", "state schema: the backup %s failed: %s", to.c_str(), sqlite3_errmsg(dst));
    sqlite3_close(dst);
    return ok;
}

// `pragma foreign_key_check`: one "table rowid -> parent" line per violating row.
std::vector<std::string> foreign_key_violations(sqlite3* db) {
    std::vector<std::string> out;
    sqlite3_stmt* s = nullptr;
    if (sqlite3_prepare_v2(db, "pragma foreign_key_check", -1, &s, nullptr) != SQLITE_OK) {
        out.push_back(std::string("pragma foreign_key_check: ") + sqlite3_errmsg(db));
        return out;
    }
    while (sqlite3_step(s) == SQLITE_ROW) {
        auto text = [&](int k) { return sqlite3_column_type(s, k) == SQLITE_NULL ? std::string("?") : (const char*)sqlite3_column_text(s, k); };
        out.push_back(text(0) + " rowid " + text(1) + " -> " + text(2));
    }
    sqlite3_finalize(s);
    return out;
}

}  // namespace

int user_version(sqlite3* db) {
    sqlite3_stmt* s = nullptr;
    int v = 0;
    if (sqlite3_prepare_v2(db, "pragma user_version", -1, &s, nullptr) == SQLITE_OK && sqlite3_step(s) == SQLITE_ROW) v = sqlite3_column_int(s, 0);
    sqlite3_finalize(s);
    return v;
}

bool open_and_migrate(sqlite3* db, const std::string& path, int target, sqlite3* master) {
    int version = user_version(db);
    if (version > kSchemaVersion) {
        LOGE("server",
             "state DB %s is schema version %d, newer than this build's %d: not opened (there is no down-migration; a %s.bak-v<N> "
             "copy is an older version)",
             path.c_str(), version, kSchemaVersion, path.c_str());
        return false;
    }
    if (version < target && has_player_row(db)) {
        std::string copy = path + ".bak-v" + std::to_string(version);
        if (!backup(db, copy)) return false;
        LOGI("server", "state DB %s: schema version %d -> %d (the version %d file kept as %s)", path.c_str(), version, target, version, copy.c_str());
    }
    // (outside any transaction: the pragma is a no-op inside one)
    if (!exec(db, "pragma foreign_keys = off", "pragma foreign_keys = off")) return false;
    for (const Step& step : steps()) {
        if (step.version <= version || step.version > target) continue;
        if (!exec(db, "begin immediate", "begin")) return false;
        bool ok = true;
        for (const char* sql : step.sql) ok = ok && exec(db, sql, step.what);
        if (ok && step.fn) ok = step.fn(db, master);
        if (ok) {
            for (const std::string& v : foreign_key_violations(db)) {
                LOGE("server", "state schema: version %d: foreign key violation: %s", step.version, v.c_str());
                ok = false;
            }
        }
        ok = ok && exec(db, "pragma user_version = " + std::to_string(step.version), "pragma user_version");
        ok = ok && exec(db, "commit", "commit");
        if (!ok) {
            sqlite3_exec(db, "rollback", nullptr, nullptr, nullptr);
            LOGE("server", "state DB %s: the step to schema version %d (%s) failed: not opened (the file stays at version %d)", path.c_str(),
                 step.version, step.what, version);
            return false;
        }
        version = step.version;
    }
    // every connection, every open, before the first request's transaction
    return exec(db, "pragma foreign_keys = on", "pragma foreign_keys = on");
}

size_t report_master_refs(sqlite3* st, sqlite3* master) {
    std::vector<Dangling> dangling = check(st, master);
    for (const Dangling& d : dangling) LOGW("server", "state DB: a reference into the master doesn't resolve: %s", describe(d).c_str());
    return dangling.size();
}

}  // namespace soa::server::state

namespace soa::server {

using ext::Row;

u64 next_uid(ext::Ctx& ctx, const char* key) {
    u64 v = (u64)std::stoull(meta(ctx, key, "0"));
    ctx.st.q("insert or replace into meta (key, value) values (?, ?)", {key, std::to_string(v + 1)});
    return v;
}
std::string meta(ext::Ctx& ctx, const char* key, const char* dflt) {
    std::string v = dflt;
    ctx.st.q("select value from meta where key = ?", {key}, [&](const Row& r) { v = r.s("value"); });
    return v;
}

bool has_player(ext::Ctx& ctx) { return ctx.st.one("select count(*) from player", {}) > 0; }

}  // namespace soa::server
