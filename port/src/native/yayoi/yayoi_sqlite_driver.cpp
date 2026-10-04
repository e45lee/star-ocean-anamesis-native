// Aska::Yayoi::SQLiteDriver: one connection and its one live statement, from the Ghidra decompile
// (port/decomp/yayoi/sqlite_driver.c), on the host SQLite (lib_sqlite's boundary: the handles are the
// host objects, databases open on the guest-path VFS so the game's Android paths resolve).
#include <sqlite3.h>

#include <cstring>

#include "core/cpu.h"
#include "native/common/guest_std.h"
#include "native/lib_sqlite/lib_sqlite.h"
#include "native/yayoi/yayoi_layout.h"

namespace soa::native::yayoi {

namespace {
sqlite3* db_of(void* p) { return static_cast<sqlite3*>(p); }
sqlite3_stmt* stmt_of(void* p) { return static_cast<sqlite3_stmt*>(p); }
int exec(void* db, const char* sql) { return sqlite3_exec(db_of(db), sql, nullptr, nullptr, nullptr); }
// sqlite3_open as the game's 3.13.0 does it (READWRITE | CREATE), on the guest-path VFS (lib_sqlite).
int open_db(const char* name, void** out) {
    lib_sqlite::register_guest_vfs();
    sqlite3* db = nullptr;
    int rc = sqlite3_open_v2(name, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, lib_sqlite::guest_vfs_name());
    *out = db;
    return rc;
}
}  // namespace

void SQLiteDriver::Ctor() {
    m_setting = nullptr;
    m_value08 = 0;
    m_lastParams = nullptr;
    m_db = nullptr;
    m_stmt = nullptr;
    m_inTransaction = 0;
    m_beginRequested = 0;
    m_address = nullptr;
    m_queryBuffer = nullptr;
    m_queryBufferSize = 0;
    m_value48 = 0;
    m_buffer50 = nullptr;
    m_buffer50Size = 0;
    m_prepared = 0;
}

void SQLiteDriver::CloseConnection() {
    if (m_inTransaction && exec(m_db, "ROLLBACK;") == SQLITE_OK) m_inTransaction = 0;
    if (m_db) {
        if (m_stmt) {
            sqlite3_finalize(stmt_of(m_stmt));
            m_stmt = nullptr;
        }
        sqlite3_close(db_of(m_db));
        m_db = nullptr;
    }
    m_address = nullptr;
    m_value48 = 0;
}

void SQLiteDriver::Dtor() {
    CloseConnection();
    if (m_queryBuffer) {
        guest::delete_array(m_queryBuffer);
        m_queryBuffer = nullptr;
    }
    if (m_buffer50) {
        guest::delete_array(m_buffer50);
        m_buffer50 = nullptr;
    }
    m_queryBufferSize = 0;
    m_buffer50Size = 0;
}

void SQLiteDriver::Close() { CloseConnection(); }

s64 SQLiteDriver::Open(void* setting) {
    if (!setting) return status::kInvalidArg;
    m_setting = setting;
    return status::kOk;
}

s64 SQLiteDriver::DoOpen(u32 mode, const char*, const DBAddress* address) {
    if (mode == 0) mode = m_inTransaction ? 2 : 0;
    if (!address) {
        // IDriverSetting<SQLiteDriver>'s vtable slot 0 (setting, mode): the address for the mode.
        const u64* vt = *static_cast<const u64* const*>(m_setting);
        address = (const DBAddress*)guest_call(vt[0], {(u64)m_setting, (u64)mode});
    }
    bool open = true;
    if (address == m_address) {
        open = m_db == nullptr;
    } else {
        CloseConnection();
    }
    if (open) {
        m_prepared = 0;
        if (open_db(address->m_path, &m_db) != SQLITE_OK) return status::kOpenFailed;
        m_address = address;
    }
    if (!m_inTransaction && m_beginRequested) {
        m_beginRequested = 0;
        if (exec(m_db, "BEGIN;") != SQLITE_OK) return status::kError;
        m_inTransaction = 1;
    }
    return status::kOk;
}

s64 SQLiteDriver::BeginTransaction() {
    if (m_beginRequested || m_inTransaction) return status::kBusy;
    m_beginRequested = 1;
    return status::kOk;
}

s64 SQLiteDriver::_BeginTransaction() {
    if (m_inTransaction || !m_beginRequested) return status::kOk;
    m_beginRequested = 0;
    if (exec(m_db, "BEGIN;") != SQLITE_OK) return status::kError;
    m_inTransaction = 1;
    return status::kOk;
}

s64 SQLiteDriver::Commit() {
    if (!m_inTransaction) return status::kNotReady;
    if (exec(m_db, "COMMIT;") != SQLITE_OK && exec(m_db, "ROLLBACK;") != SQLITE_OK) return status::kError;
    m_inTransaction = 0;
    return status::kOk;
}

s64 SQLiteDriver::Rollback() {
    if (!m_inTransaction) return status::kNotReady;
    if (exec(m_db, "ROLLBACK;") != SQLITE_OK) return status::kError;
    m_inTransaction = 0;
    return status::kOk;
}

s64 SQLiteDriver::_Prepare(const char* sql, s32* paramCount) {
    if (m_stmt) {
        sqlite3_finalize(stmt_of(m_stmt));
        m_stmt = nullptr;
    }
    m_lastParams = nullptr;
    sqlite3_stmt* st = nullptr;
    int rc = sqlite3_prepare_v2(db_of(m_db), sql, (int)std::strlen(sql), &st, nullptr);
    m_stmt = st;
    if (rc == SQLITE_OK) {
        m_prepared = 1;
        *paramCount = sqlite3_bind_parameter_count(st);
        return status::kOk;
    }
    // A failing prepare closes the database (the message is read and dropped).
    sqlite3_errmsg(db_of(m_db));
    CloseConnection();
    return status::kError;
}

s64 SQLiteDriver::_Execute(const char* sql, const QueryParam* params, u64 n, EntityObject* entity) {
    s32 count = 0;
    s64 st = _Prepare(sql, &count);
    if (st < 0) return st;
    if ((s64)count != (s64)n) return status::kInvalidArg;
    // (_Prepare cleared m_lastParams: only null params skip the binds)
    if (count >= 1 && m_lastParams != params) {
        sqlite3_reset(stmt_of(m_stmt));
        for (s64 i = 0; i < (s64)n; i++)
            if (sqlite3_bind_text(stmt_of(m_stmt), (int)(i + 1), params[i].m_text, params[i].m_length, SQLITE_STATIC) != SQLITE_OK)
                return status::kNotReady;
        m_lastParams = params;
    }
    if (!entity) {
        int rc;
        do rc = sqlite3_step(stmt_of(m_stmt));
        while (rc == SQLITE_BUSY);
        if (rc != SQLITE_ROW) {
            if (rc != SQLITE_DONE) return status::kError;
            sqlite3_reset(stmt_of(m_stmt));
        }
    }
    return status::kOk;
}

s64 SQLiteDriver::Execute(const char* sql, const QueryParam* params, u64 n) { return _Execute(sql, params, n, nullptr); }

s64 SQLiteDriver::Find(const char* sql, const QueryParam* params, u64 n, EntityObject* entity) {
    s64 st = _Execute(sql, params, n, entity);
    if (st < 0) return st;
    entity->Store(m_db, m_stmt);
    return status::kOk;
}

}  // namespace soa::native::yayoi
