// Aska::Yayoi::SQLiteDriver::EntityObject: a cursor over the driver's statement (the name map, the
// typed getters, the cache buffer) and Serialize, the rows as MessagePack through an Aska::ASON (the
// master-data path: every CSimpleSqliteConnector::QueryToMsgPack). From the Ghidra decompile
// (port/decomp/yayoi/sqlite_driver.c), on the host SQLite.
#include <sqlite3.h>

#include <cstdio>
#include <cstring>
#include <vector>

#include "native/common/guest_std.h"
#include "native/data_formats/data_formats_layout.h"
#include "native/yayoi/yayoi_guest.h"
#include "native/yayoi/yayoi_layout.h"
#include "native/yayoi/yayoi_sqlite.h"

namespace soa::native::yayoi {

namespace {
constexpr u8 kUsed = 1, kDeleted = 2;
sqlite3_stmt* stmt_of(void* p) { return static_cast<sqlite3_stmt*>(p); }
sqlite3_value* value_of(void* stmt, s32 column) { return sqlite3_column_value(stmt_of(stmt), column); }
}  // namespace

// ---- construction, the cache buffer ----

void EntityObject::Ctor() {
    m_value00 = 0;
    m_numColumns = 0;
    m_cache = nullptr;
    m_cacheSize = 0;
    // the map, as THashMap's constructor (inlined): vtable, load 0.75, empty, 17 buckets
    m_columns.table.vtable = column_map_vtable();
    m_columns.table.m_maxLoadFactor = 0.75f;
    m_columns.table.m_size = 0;
    m_columns.table.m_deleted = 0;
    auto* b = (ColumnBucket*)gfn::aligned_malloc(17 * sizeof(ColumnBucket), 8);
    m_columns.table.m_buckets.m_data = b;
    m_columns.table.m_buckets.m_count = b ? 17 : 0;
    if (b)
        for (int i = 0; i < 17; i++) b[i].m_state = 0;
    m_stmt = nullptr;
    m_db = nullptr;
}

void EntityObject::Release() {
    if (m_cache) {
        guest::delete_array(m_cache);
        m_cache = nullptr;
    }
    m_cacheSize = 0;
}

void EntityObject::ClearCache() { Release(); }

void EntityObject::Dtor() {
    Release();
    m_columns.Dtor();
}

s64 EntityObject::CreateCacheBuffer(u64 size) {
    if (m_cacheSize >= size) return status::kOk;
    if (m_cache) {
        guest::delete_array(m_cache);
        m_cache = nullptr;
    }
    m_cache = (u8*)guest::new_array_nothrow(size);
    if (!m_cache) return status::kNoMemory;
    m_cacheSize = size;
    return status::kOk;
}

u8* EntityObject::GetCacheBuffer(u64* size) {
    *size = m_cacheSize;
    return m_cache;
}

u64 EntityObject::SerializeCache(u64*) { return 0; }

// ---- the statement ----

s64 EntityObject::Store(void* db, void* stmt) {
    if (m_stmt != stmt) {
        m_stmt = stmt;
        m_numColumns = sqlite3_column_count(stmt_of(stmt));
        // a new statement: every name out of the map (the buckets kept), then the new names in order
        // (a duplicate name keeps the last index)
        ColumnBucket* b = m_columns.table.m_buckets.m_data;
        if (b && m_columns.table.m_buckets.m_count)
            for (u64 i = 0; i < m_columns.table.m_buckets.m_count; i++) {
                if (b[i].m_state == kUsed) {
                    m_columns.table.m_size--;
                    b[i].m_state = 0;
                } else if (b[i].m_state == kDeleted) {
                    m_columns.table.m_deleted--;
                    b[i].m_state = 0;
                }
            }
        m_columns.table.m_size = 0;
        m_columns.table.m_deleted = 0;
        for (s32 i = 0; i < m_numColumns; i++) {
            const char* name = sqlite3_column_name(stmt_of(m_stmt), i);
            m_columns.GrowFor(1);
            ColumnMapInsertResult r = m_columns.Emplace_(&name);
            r.m_it.m_bucket->m_value.second = i;
        }
    }
    if (m_db != db) m_db = db;
    return status::kOk;
}

s64 EntityObject::Fetch() {
    if (!m_stmt) return status::kNotReady;
    for (;;) {
        int rc = sqlite3_step(stmt_of(m_stmt));
        if (rc == SQLITE_ROW) return status::kOk;
        if (rc == SQLITE_DONE) return status::kNoMoreRows;
        if (rc > SQLITE_ROW || (rc != SQLITE_BUSY && rc != SQLITE_ERROR)) return status::kStepFailed;
        if (rc == SQLITE_ERROR) return status::kError;
        // SQLITE_BUSY: again
    }
}

// The Get*(name) lookup, as the guest inlines THashMap::operator[] after a find: a missing name is
// kNameNotFound; a found one goes through operator[] (which may grow the map first).
bool EntityObject::ColumnIndex(const char* name, s32* column) {
    if (m_columns.Find(name) == m_columns.end()) return false;
    m_columns.GrowFor(1);
    ColumnMapInsertResult r = m_columns.Emplace_(&name);
    *column = r.m_it.m_bucket->m_value.second;
    return true;
}

// ---- the getters ----

namespace {
// The typed getters' common shape: no out pointer, no statement, a NULL value; else `read`.
template <typename T, typename Read>
s64 get_value(void* stmt, s32 column, T* out, Read read) {
    if (!out) return status::kInvalidArg;
    if (!stmt) return status::kNotReady;
    sqlite3_value* v = value_of(stmt, column);
    if (sqlite3_value_type(v) == SQLITE_NULL) return status::kNull;
    *out = read(v);
    return status::kOk;
}
}  // namespace

s32 EntityObject::GetType(s32 column, u64) {
    if (!m_stmt) return (s32)status::kNotReady;
    return sqlite3_value_type(value_of(m_stmt, column));
}

s32 EntityObject::GetType(const char* name, u64 row) {
    s32 column;
    if (!ColumnIndex(name, &column)) return (s32)status::kNameNotFound;
    return GetType(column, row);
}

s32 EntityObject::GetFieldLength(s32 column, s32) {
    if (!m_stmt) return 0;
    sqlite3_value* v = value_of(m_stmt, column);
    if (sqlite3_value_type(v) == SQLITE_NULL) return 0;
    sqlite3_value_blob(v);
    return sqlite3_value_bytes(v);
}

s64 EntityObject::GetStringLength(s32 column, u64* length, u64) {
    return get_value(m_stmt, column, length, [](sqlite3_value* v) { return (u64)std::strlen((const char*)sqlite3_value_text(v)); });
}

s64 EntityObject::GetTime(s32, char* out, u64*, u64) { return out ? status::kNotSupported : status::kInvalidArg; }

s64 EntityObject::GetTime(const char* name, char* out, u64* size, u64 row) {
    s32 column;
    if (!ColumnIndex(name, &column)) return status::kNameNotFound;
    return GetTime(column, out, size, row);
}

s64 EntityObject::GetData(s32 column, char* out, u64* size, u64) {
    if (!out) return status::kInvalidArg;
    if (!m_stmt) return status::kNotReady;
    sqlite3_value* v = value_of(m_stmt, column);
    if (sqlite3_value_type(v) == SQLITE_NULL) return status::kNull;
    const void* blob = sqlite3_value_blob(v);
    int n = sqlite3_value_bytes(v);
    std::memcpy(out, blob, (size_t)(s64)n);  // (the guest doesn't check *size)
    *size = (u64)(s64)n;
    return status::kOk;
}

s64 EntityObject::GetData(const char* name, char* out, u64* size, u64 row) {
    s32 column;
    if (!ColumnIndex(name, &column)) return status::kNameNotFound;
    return GetData(column, out, size, row);
}

s64 EntityObject::GetString(s32 column, char* out, u64* size, u64) {
    if (!out) return status::kInvalidArg;
    if (!m_stmt) return status::kNotReady;
    sqlite3_value* v = value_of(m_stmt, column);
    if (sqlite3_value_type(v) == SQLITE_NULL) return status::kNull;
    const char* text = (const char*)sqlite3_value_text(v);
    // __aska_snprintf_s(out, *size, -1, "%s", text): vsnprintf, -1 when it failed or didn't fit
    // (a text of exactly *size characters is cut by one and still returns *size)
    u64 cap = *size;
    int r = std::snprintf(out, cap, "%s", text);
    if (r < 0 || cap < (u64)(s64)r) r = -1;
    *size = (u64)(s64)r;
    return status::kOk;
}

s64 EntityObject::GetString(const char* name, char* out, u64* size, u64 row) {
    s32 column;
    if (!ColumnIndex(name, &column)) return status::kNameNotFound;
    return GetString(column, out, size, row);
}

#define SOA_YAYOI_GETTER(Name, T, read)                                                          \
    s64 EntityObject::Name(s32 column, T* out, u64) { return get_value(m_stmt, column, out, read); } \
    s64 EntityObject::Name(const char* name, T* out, u64 row) {                                \
        s32 column;                                                                            \
        if (!ColumnIndex(name, &column)) return status::kNameNotFound;                         \
        return Name(column, out, row);                                                         \
    }
SOA_YAYOI_GETTER(GetTinyInt, s8, [](sqlite3_value* v) { return (s8)sqlite3_value_int(v); })
SOA_YAYOI_GETTER(GetShort, s16, [](sqlite3_value* v) { return (s16)sqlite3_value_int(v); })
SOA_YAYOI_GETTER(GetInteger, s32, [](sqlite3_value* v) { return (s32)sqlite3_value_int(v); })
SOA_YAYOI_GETTER(GetLong, s64, [](sqlite3_value* v) { return (s64)sqlite3_value_int64(v); })
SOA_YAYOI_GETTER(GetFloat, float, [](sqlite3_value* v) { return (float)sqlite3_value_double(v); })
SOA_YAYOI_GETTER(GetDouble, double, [](sqlite3_value* v) { return sqlite3_value_double(v); })
#undef SOA_YAYOI_GETTER

// ---- Serialize: the rows as MessagePack ----

namespace {
using data_formats::ASON;
using data_formats::AValue;
using data_formats::ASON_Pair;

// A string AValue, as Serialize writes the keys and the text values (AValue::SetString inlined): the
// bytes (not terminated) and, the ASON keeping C strings, a terminated copy, both from ASON::Malloc,
// each stamped with the work block it went into. An empty string has no data and both stamps 0xffff.
// False when an allocation failed (the value is then partly written, as in the guest).
bool set_string(ASON* a, AValue* v, const char* s) {
    u32 len = (u32)std::strlen(s);
    v->m_kind = AValue::kString;
    if (len == 0) {
        v->m_body.str.m_cstr = nullptr;
        v->m_length = 0;
        v->m_dataWork = 0xffff;
        v->m_cstrWork = 0xffff;
        v->m_body.str.m_data = nullptr;
        return true;
    }
    char* data = (char*)gfn::ason_malloc(a, len);
    v->m_body.str.m_data = data;
    if (!data) return false;
    v->m_dataWork = a->m_workIndex;
    std::memcpy(data, s, len);
    v->m_length = len;
    if (!a->m_keepCStrings) {
        v->m_body.str.m_cstr = nullptr;
        v->m_cstrWork = 0xffff;
        return true;
    }
    char* cstr = (char*)gfn::ason_malloc(a, (u64)(u32)(len + 1));
    v->m_body.str.m_cstr = cstr;
    if (!cstr) return false;
    v->m_cstrWork = a->m_workIndex;
    std::memcpy(cstr, s, len);
    cstr[len] = 0;
    return true;
}
}  // namespace

// Every row of the statement (stepped from the start) as an array of maps {column name: value}, one
// MessagePack buffer: INTEGER -> a signed int (sqlite3_value_int: 32 bits), FLOAT -> a double, TEXT and
// BLOB -> a string (sqlite3_value_text), NULL -> nil. *size gets the byte count (or a status < 0); the
// result is the buffer with its shared counter (1), {0, 0} on failure.
//
// The table of names (index -> name) is the native's own: the guest's is a 64-entry stack array, or
// for more columns a MemoryManager::Malloc block of Global::m_pNetworkAllocator freed with operator
// delete[] (a mismatched free: in --selftest a second such Serialize then waits forever in
// MemoryManager::Malloc), invisible outside Serialize.
// Guest details kept: the rows are counted by stepping first (then reset); the ASON's work size is
// rows * columns * 0x80 in 32 bits (at least 0x2000), Init keeps C strings; the column names come from
// the map, so a duplicate name leaves an index without a key. Not kept: the guest's table of names
// (index -> name) is uninitialised stack / heap memory, so such an index reads garbage there; here it
// is null and the key stays nil. The guest reads a text value through a 0x100-byte buffer that it
// regrows from the network allocator when the text doesn't fit (__aska_snprintf_s "%s"): the bytes are
// sqlite3_value_text's either way, so the native copies them directly. Out of memory in ASON::Malloc
// for a text value: the guest returns size 0 with an uninitialised counter register; here *size is
// kNoMemory and the result empty.
SharedBytes EntityObject::Serialize(s64* size) {
    SharedBytes out{nullptr, nullptr};
    if (!size) return out;
    u32 ncols = (u32)m_numColumns;
    sqlite3_reset(stmt_of(m_stmt));
    u64 rows = 0;
    if (!m_stmt) {
        sqlite3_reset(nullptr);
    } else {
        for (;;) {
            int rc;
            do rc = sqlite3_step(stmt_of(m_stmt));
            while (rc == SQLITE_BUSY);
            if (rc != SQLITE_ROW) break;
            rows++;
        }
        sqlite3_reset(stmt_of(m_stmt));
    }
    if (ncols == 0 || rows == 0) {
        *size = status::kEmpty;
        return out;
    }

    alignas(16) ASON ason;
    gfn::ason_ctor(&ason);
    s64 st = status::kOk;
    s64 written = 0;
    s8* buffer = nullptr;
    s32* counter = nullptr;

    // index -> column name, from the map (host memory: see above)
    std::vector<const char*> names(ncols, nullptr);
    if (st >= 0 && m_columns.table.m_size != 0) {
        ColumnBucket* b = m_columns.table.m_buckets.m_data;
        ColumnBucket* e = m_columns.end();
        // (an index past the columns, which Store never makes, would write past the table in the guest)
        for (; b != e; ++b)
            if (b->m_state == kUsed && (u32)b->m_value.second < ncols) names[b->m_value.second] = b->m_value.first;
    }

    if (st >= 0) {
        u32 work = (u32)rows * ncols * 0x80;
        if (work < 0x2001) work = 0x2000;
        st = gfn::ason_init(&ason, work, true);
        if (st >= 0) st = gfn::ason_make_array(&ason, &ason.m_root, (u32)rows);
        for (u64 r = 0; st >= 0 && r < rows; r++) {
            if (m_stmt) {
                int rc;
                do rc = sqlite3_step(stmt_of(m_stmt));
                while (rc == SQLITE_BUSY);
            }
            AValue* row = (u32)r < ason.m_root.m_body.array.m_count ? &ason.m_root.m_body.array.m_elements[(u32)r] : nullptr;
            st = gfn::ason_make_map(&ason, row, ncols);
            for (u64 c = 0; st >= 0 && c < (u64)(s64)(s32)ncols; c++) {
                ASON_Pair* pair = (u32)c < row->m_body.map.m_count ? &row->m_body.map.m_pairs[(u32)c] : nullptr;
                if (names[c]) set_string(&ason, &pair->key, names[c]);
                if (!m_stmt) {
                    st = status::kBadType;
                    break;
                }
                AValue* value = &pair->value;
                int type = sqlite3_value_type(value_of(m_stmt, (s32)c));
                if (type == SQLITE_INTEGER || type == SQLITE_FLOAT) {
                    sqlite3_value* v = value_of(m_stmt, (s32)c);
                    if (sqlite3_value_type(v) == SQLITE_NULL) {
                        st = status::kNull;
                    } else if (type == SQLITE_INTEGER) {
                        value->m_kind = AValue::kSInt;
                        value->m_body.s = (s64)sqlite3_value_int(v);
                    } else {
                        value->m_kind = AValue::kFloat;
                        value->m_body.d = sqlite3_value_double(v);
                    }
                } else if (type == SQLITE_TEXT || type == SQLITE_BLOB) {
                    sqlite3_value* v = value_of(m_stmt, (s32)c);
                    const char* text = (const char*)sqlite3_value_text(v);
                    if (!set_string(&ason, value, text ? text : "")) st = status::kNoMemory;
                } else if (type != SQLITE_NULL) {
                    st = status::kBadType;
                }
            }
        }
    }

    if (st >= 0) {
        s64 n = gfn::ason_calc_serialized_size(&ason);
        if (n >= 0) {
            buffer = (s8*)guest::new_array_nothrow((u64)n);
            if (!buffer) {
                st = status::kNoMemory;
            } else {
                written = gfn::ason_serialize(&ason, buffer, (u64)n);
                if (written < 0) {
                    guest::delete_array(buffer);
                    buffer = nullptr;
                    written = 0;
                } else {
                    // (a failed counter leaves the buffer unowned and the result empty, as in the guest)
                    counter = gfn::create_counter(0);
                    if (counter) {
                        *counter += 1;  // the result's reference (the guest's +2 for its two copies, -1 at the end)
                        out = {buffer, counter};
                    }
                }
            }
        }
    }
    gfn::ason_dtor(&ason);
    *size = st >= 0 ? written : st;
    return out;
}

}  // namespace soa::native::yayoi
