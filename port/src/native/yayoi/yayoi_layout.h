// yayoi_layout.h: the guest data layouts of the `yayoi` subsystem (Aska::Yayoi: network and the SQLite driver).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/yayoi/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types yayoi` turns the structs into port/decomp/yayoi/types.json for Ghidra.
//
// Two parts: the SQLite driver (Aska::Yayoi::SQLiteDriver + EntityObject: every master-data read goes
// through it; the SQLite C API below it is lib_sqlite's boundary, its handles opaque pointers here),
// and the network layer the 3.7.0 client keeps alive offline (NetworkManager, its thread, the asset
// Downloader, URI / IPAddress, the HTTP protocol objects). Most Yayoi methods return an Aska::Status
// (8 bytes) through x8. Proofs: yayoi_layout_test.cpp (`soa --selftest yayoi/`).
#ifndef SOA_NATIVE_YAYOI_LAYOUT_H
#define SOA_NATIVE_YAYOI_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../containers/containers_layout.h"
#include "../memory/memory_layout.h"
#include "../sync/sync_layout.h"

namespace soa::native::yayoi {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// ---- Guest addresses (ELF vaddr; add main_lib()->base) of the statics the classes below use ------
inline constexpr u64 kVaddrNetworkManager = 0x2d74ee0;        // Aska::Global::m_pNetworkManager (NetworkManager*)
inline constexpr u64 kVaddrNetworkAllocator = 0x2d74ed8;      // Aska::Global::m_pNetworkAllocator
inline constexpr u64 kVaddrDownloadContentPath = 0x2d74f08;   // Aska::Global::m_pszDownloadContentPath (char*)

// The `sync` subsystem's classes (native/sync/sync_layout.h) are embedded where the guest embeds them:
// FastCriticalSection (0x90), Thread (0x10), Event (0x68), Semaphore (0x18).
using sync::Event;
using sync::FastCriticalSection;
using sync::Semaphore;
using sync::Thread;

// Aska::Status values the driver returns (through x8), from the decompile.
namespace status {
inline constexpr s64 kOk = 0;
inline constexpr s64 kError = -1;           // a failed sqlite3_prepare_v2 / exec / step
inline constexpr s64 kNoMoreRows = -0x3aa;  // EntityObject::Fetch past the last row (SQLITE_DONE)
inline constexpr s64 kNotReady = -0x3b3;    // no statement (Fetch / Get*), not in a transaction (Commit /
                                            // Rollback), a failed bind (_Execute)
inline constexpr s64 kInvalidArg = -0x3ee;  // a null out pointer, Open(null), _Execute's n != the statement's
                                            // parameter count
inline constexpr s64 kBusy = -0x3ea;        // BeginTransaction while one is requested / running
inline constexpr s64 kOpenFailed = -0x3d5;  // DoOpen: sqlite3_open failed
inline constexpr s64 kNameNotFound = -0x3c8;// Get*(const char* name): no such column
inline constexpr s64 kNoMemory = -0x3bf;    // CreateCacheBuffer
inline constexpr s64 kNull = -0x38f;        // Get*: the value is NULL (SQLITE_NULL)
inline constexpr s64 kStepFailed = -0x400;  // Fetch: another sqlite3_step result
inline constexpr s64 kNotSupported = -0x3ba;// GetTime (both overloads, with an out buffer)
inline constexpr s64 kEmpty = -0x3a4;       // Serialize: no columns or no rows (written to *size)
inline constexpr s64 kBadType = -0x3b8;     // Serialize: a value type outside 1..5, or the statement gone
inline constexpr s64 kNoBuffer = -0x3bd;    // Serialize: no text buffer
}  // namespace status

// ---- The SQLite driver ---------------------------------------------------------------------------
//
// The natives (yayoi_sqlite_driver.cpp, yayoi_entity_object.cpp, yayoi_column_map.cpp) call the host
// SQLite directly: the handles below are the host objects lib_sqlite hands out (lib_sqlite/README.md).
// Members returning an Aska::Status (s64) return it through x8 in the guest (hand-written HostFns in
// yayoi_sqlite_hooks.cpp); the rest by AAPCS64.

// Aska::Yayoi::QueryParam (0x28): one bound value; SQLiteDriver::_Execute binds params[i] as text
// (sqlite3_bind_text(stmt, i + 1, m_text, m_length, SQLITE_STATIC)). The connectors fill the text with
// "%u" keys (docs/notes.md "Master-data loader").
class QueryParam {
public:
    u8 unk_00[0x10];    // 0x00
    const char* m_text; // 0x10
    s32 m_length;       // 0x18: -1 = up to the NUL
    u8 unk_1c[0xc];     // 0x1c
};
static_assert(offsetof(QueryParam, m_text) == 0x10);
static_assert(offsetof(QueryParam, m_length) == 0x18);
static_assert(sizeof(QueryParam) == 0x28);

// Aska::Yayoi::DBAddress: what DoOpen opens (sqlite3_open(m_path)). Only the first word is read.
class DBAddress {
public:
    const char* m_path; // 0x00
};
static_assert(sizeof(DBAddress) == 8);

// Aska::TSharedArray<signed char>: EntityObject::Serialize's x8 result, {buffer (operator new[]), its
// TSharedPointerCode counter}; the connectors (QueryToMsgPack) keep or release it.
struct SharedBytes {
    s8* m_ptr;          // 0x00
    s32* m_counter;     // 0x08
};
static_assert(offsetof(SharedBytes, m_counter) == 0x08);
static_assert(sizeof(SharedBytes) == 0x10);

class EntityObject;

// Aska::Yayoi::SQLiteDriver (0x68): one connection and its one live statement. Layout from the
// constructor (clears 0x00..0x2a, 0x30..0x60), the destructor, Close, DoOpen, Open, _Prepare, _Execute,
// Find, BeginTransaction / _BeginTransaction / Commit / Rollback (port/decomp/yayoi/sqlite_driver.c).
// Users: CStaticTransaction (the master DB, :memory: + ATTACH) and CSqliteTransaction (game's side);
// the 170 SQLiteDriver::BuildQuery<Connector> templates (the `master` side) write m_queryBuffer.
class SQLiteDriver {
public:
    void Ctor();                        // _ZN4Aska5Yayoi12SQLiteDriverC1Ev
    void Dtor();                        // _ZN4Aska5Yayoi12SQLiteDriverD1Ev (ROLLBACK if in a transaction, finalize, close)
    s64 Open(void* setting);            // _ZN4Aska5Yayoi12SQLiteDriver4OpenEPNS0_14IDriverSettingIS1_EE (m_setting)
    s64 DoOpen(u32 mode, const char* name, const DBAddress* address); // _ZN4Aska5Yayoi12SQLiteDriver6DoOpenENS0_6Entity4ModeEPKcPKNS0_9DBAddressE
    void Close();                       // _ZN4Aska5Yayoi12SQLiteDriver5CloseEv
    s64 BeginTransaction();             // _ZN4Aska5Yayoi12SQLiteDriver16BeginTransactionEv (only requests it)
    s64 _BeginTransaction();            // _ZN4Aska5Yayoi12SQLiteDriver17_BeginTransactionEv ("BEGIN;")
    s64 Commit();                       // _ZN4Aska5Yayoi12SQLiteDriver6CommitEv
    s64 Rollback();                     // _ZN4Aska5Yayoi12SQLiteDriver8RollbackEv
    s64 Execute(const char* sql, const QueryParam* params, u64 n);  // _ZN4Aska5Yayoi12SQLiteDriver7ExecuteEPKcPKNS0_10QueryParamEm (_Execute, no entity)
    s64 _Execute(const char* sql, const QueryParam* params, u64 n, EntityObject* entity); // _ZN4Aska5Yayoi12SQLiteDriver8_ExecuteEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE
    s64 Find(const char* sql, const QueryParam* params, u64 n, EntityObject* entity); // _ZN4Aska5Yayoi12SQLiteDriver4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE (_Execute + entity->Store)
    s64 _Prepare(const char* sql, s32* paramCount);  // _ZN4Aska5Yayoi12SQLiteDriver8_PrepareEPKcPi
    // template BuildQuery<Connector>(...): one per master table connector (170), the `master` side

    // Inlined in the guest (Close, the destructor, DoOpen and _Prepare repeat it): ROLLBACK when in a
    // transaction, finalize the statement, close the connection, forget the address.
    void CloseConnection();

    void* m_setting;                    // 0x00: Aska::Yayoi::IDriverSetting<SQLiteDriver>* (Open); its vtable
                                        //       slot 0 (this, mode) gives the DBAddress when DoOpen gets none
    u64 m_value08;                      // 0x08: cleared by the constructor, meaning unknown
    const QueryParam* m_lastParams;     // 0x10: the params bound to m_stmt (_Prepare clears it, _Execute sets it)
    void* m_db;                         // 0x18: sqlite3* (lib_sqlite's host handle)
    void* m_stmt;                       // 0x20: sqlite3_stmt*: the one live statement (_Prepare finalizes the last)
    u8 m_inTransaction;                 // 0x28
    u8 m_beginRequested;                // 0x29: BeginTransaction; the next DoOpen / _BeginTransaction runs "BEGIN;"
    u8 unk_2a[6];                       // 0x2a
    const DBAddress* m_address;         // 0x30: what is open (DoOpen reopens only for another address)
    char* m_queryBuffer;                // 0x38: BuildQuery's buffer (delete[] by the destructor)
    u64 m_queryBufferSize;              // 0x40
    u64 m_value48;                      // 0x48: cleared with m_address on close
    char* m_buffer50;                   // 0x50: a second buffer (delete[] by the destructor)
    u64 m_buffer50Size;                 // 0x58
    u8 m_prepared;                      // 0x60: set by a successful _Prepare (DoOpen clears it)
    u8 unk_61[7];                       // 0x61
};
static_assert(offsetof(SQLiteDriver, m_lastParams) == 0x10);
static_assert(offsetof(SQLiteDriver, m_db) == 0x18);
static_assert(offsetof(SQLiteDriver, m_stmt) == 0x20);
static_assert(offsetof(SQLiteDriver, m_inTransaction) == 0x28);
static_assert(offsetof(SQLiteDriver, m_beginRequested) == 0x29);
static_assert(offsetof(SQLiteDriver, m_address) == 0x30);
static_assert(offsetof(SQLiteDriver, m_queryBuffer) == 0x38);
static_assert(offsetof(SQLiteDriver, m_buffer50) == 0x50);
static_assert(offsetof(SQLiteDriver, m_prepared) == 0x60);
static_assert(sizeof(SQLiteDriver) == 0x68);

// The column-name map of an EntityObject: Aska::THashMap<char const*, int, EntityObject::StringHasher,
// EntityObject::StringEqualTo, TAllocator<TPair<char const* const, int>>>: containers' THashMap table
// (open addressing, buckets {u8 state; TPair<const char*, int>} of 0x18, linear probing (h + i) % count).
// StringHasher = Aska::detail::SpookyHashV2::Hash128(name, strlen(name), seeds 0, 0)'s first word;
// StringEqualTo = strcmp. The keys are SQLite's column-name pointers (valid while the statement lives).
// This instantiation's members are the yayoi family's (their symbols name EntityObject): declared on a
// yayoi class of containers' layout (the containers subsystem owns the generic THashMap).
using ColumnPair = containers::TPair<const char*, s32>;
using ColumnBucket = containers::THashMapBucket<ColumnPair>;
static_assert(sizeof(ColumnBucket) == 0x18);
static_assert(offsetof(ColumnBucket, m_value.first) == 0x08);
static_assert(offsetof(ColumnBucket, m_value.second) == 0x10);

// Aska::THashMapIterator<THashMapBucketArray<...>> of this map: {bucket, buckets begin, buckets end};
// the end iterator has m_bucket == m_end. Insert<It> takes two by value (AAPCS64: by reference).
struct ColumnMapIterator {
    ColumnBucket* m_bucket;     // 0x00
    ColumnBucket* m_begin;      // 0x08
    ColumnBucket* m_end;        // 0x10
};
static_assert(sizeof(ColumnMapIterator) == 0x18);

// Emplace_ / Insert_'s x8 result: TPair<iterator, bool> (inserted: a new key).
struct ColumnMapInsertResult {
    ColumnMapIterator m_it;     // 0x00
    u8 m_inserted;              // 0x18
    u8 unk_19[7];               // 0x19
};
static_assert(offsetof(ColumnMapInsertResult, m_inserted) == 0x18);
static_assert(sizeof(ColumnMapInsertResult) == 0x20);

class ColumnMap {
public:
    void Dtor();                        // _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEED2Ev
    void DtorDelete();                  // ...D0Ev (AlignedFree the buckets, operator delete)
    ColumnMapInsertResult Emplace_(const char* const* key);       // ...8Emplace_ERSA_ (a new key: value left as is)
    ColumnMapInsertResult Insert_(const ColumnPair* pair);        // ...7Insert_ERKSB_
    void Rehash_(u64 count);            // ...7Rehash_Em (a whole temporary map, swapped in)
    void Insert(ColumnMapIterator* first, const ColumnMapIterator* last);  // ...6InsertINS_16THashMapIterator...EEvT_SN_ (Rehash_'s range insert)

    // Inlined in the guest:
    static u64 Hash(const char* key);   // StringHasher
    ColumnBucket* Find(const char* key) const;  // the Get*(name) lookup (end() when missing)
    ColumnBucket* end() const { return table.m_buckets.m_data + table.m_buckets.m_count; }
    void GrowFor(u64 extra);            // operator[]'s growth: Rehash_ when (size + deleted + extra) / maxLoad > count

    containers::THashTable<ColumnPair> table;   // 0x00
};
static_assert(sizeof(ColumnMap) == 0x30);
static_assert(offsetof(ColumnMap, table.m_maxLoadFactor) == 0x0c);
static_assert(offsetof(ColumnMap, table.m_size) == 0x10);
static_assert(offsetof(ColumnMap, table.m_deleted) == 0x14);
static_assert(offsetof(ColumnMap, table.m_buckets.m_data) == 0x20);
static_assert(offsetof(ColumnMap, table.m_buckets.m_count) == 0x28);

// Aska::Yayoi::SQLiteDriver::EntityObject (0x60): a cursor over the driver's statement. Layout from the
// constructor, ~EntityObject, Release / ClearCache / CreateCacheBuffer / GetCacheBuffer, Store, Fetch,
// the Get* accessors and Serialize (port/decomp/yayoi/sqlite_driver.c). The connectors build one on the
// stack per query (CSimpleSqliteConnector::QueryToMsgPack: Find, then Serialize).
// The Get*(int column, ..., row) accessors read column `column` of the current row (`row` is unused);
// the (const char* name, ...) overloads look the name up in m_columns first (kNameNotFound), the way
// the guest's inlined operator[] does: a found name can still grow (rehash) the map.
class EntityObject {
public:
    void Ctor();                        // _ZN4Aska5Yayoi12SQLiteDriver12EntityObjectC1Ev (17 buckets)
    void Dtor();                        // _ZN4Aska5Yayoi12SQLiteDriver12EntityObjectD1Ev
    void Release();                     // _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7ReleaseEv (frees the cache buffer)
    void ClearCache();                  // ...10ClearCacheEv (the same)
    s64 CreateCacheBuffer(u64 size);    // ...17CreateCacheBufferEm (grows m_cache: new[] nothrow)
    u8* GetCacheBuffer(u64* size);      // ...14GetCacheBufferEPm
    s64 Store(void* db, void* stmt);    // ...5StoreEP7sqlite3P12sqlite3_stmt (a new statement: m_numColumns, the name map rebuilt)
    s64 Fetch();                        // ...5FetchEv (sqlite3_step; kNoMoreRows at the end)
    s32 GetType(s32 column, u64 row);   // ...7GetTypeEim (sqlite3_value_type; kNotReady as an int)
    s32 GetType(const char* name, u64 row);  // ...7GetTypeEPKcm
    s32 GetFieldLength(s32 column, s32 row); // ...14GetFieldLengthEii (sqlite3_value_bytes; 0 for NULL)
    s64 GetStringLength(s32 column, u64* length, u64 row);  // ...15GetStringLengthEiPmm (strlen of the text)
    s64 GetTime(s32 column, char* out, u64* size, u64 row); // ...7GetTimeEiPcPmm (kNotSupported)
    s64 GetTime(const char* name, char* out, u64* size, u64 row);
    s64 GetData(s32 column, char* out, u64* size, u64 row); // ...7GetDataEiPcPmm (the blob; *size not checked)
    s64 GetData(const char* name, char* out, u64* size, u64 row);
    s64 GetString(s32 column, char* out, u64* size, u64 row); // ...9GetStringEiPcPmm (__aska_snprintf_s("%s"))
    s64 GetString(const char* name, char* out, u64* size, u64 row);
    s64 GetTinyInt(s32 column, s8* out, u64 row);       // ...10GetTinyIntEiPam (sqlite3_value_int, cut)
    s64 GetTinyInt(const char* name, s8* out, u64 row);
    s64 GetShort(s32 column, s16* out, u64 row);        // ...8GetShortEiPsm
    s64 GetShort(const char* name, s16* out, u64 row);
    s64 GetInteger(s32 column, s32* out, u64 row);      // ...10GetIntegerEiPim
    s64 GetInteger(const char* name, s32* out, u64 row);
    s64 GetLong(s32 column, s64* out, u64 row);         // ...7GetLongEiPlm (sqlite3_value_int64)
    s64 GetLong(const char* name, s64* out, u64 row);
    s64 GetFloat(s32 column, float* out, u64 row);      // ...8GetFloatEiPfm (sqlite3_value_double, narrowed)
    s64 GetFloat(const char* name, float* out, u64 row);
    s64 GetDouble(s32 column, double* out, u64 row);    // ...9GetDoubleEiPdm
    s64 GetDouble(const char* name, double* out, u64 row);
    SharedBytes Serialize(s64* size);   // ...9SerializeEPl (x8: the rows as MessagePack: the yayoi hot spot)
    u64 SerializeCache(u64* size);      // ...14SerializeCacheEPm (returns 0)

    // Inlined in the guest: the name lookup of the Get*(name) overloads (false: kNameNotFound).
    bool ColumnIndex(const char* name, s32* column);

    u64 m_value00;              // 0x00: cleared by the constructor, meaning unknown
    s32 m_numColumns;           // 0x08: sqlite3_column_count (Store)
    u8 unk_0c[4];               // 0x0c
    u8* m_cache;                // 0x10: the cache buffer (CreateCacheBuffer, new[])
    u64 m_cacheSize;            // 0x18
    ColumnMap m_columns;        // 0x20: column name -> index
    void* m_stmt;               // 0x50: sqlite3_stmt* the entity reads (Store)
    void* m_db;                 // 0x58: sqlite3*
};
static_assert(offsetof(EntityObject, m_numColumns) == 0x08);
static_assert(offsetof(EntityObject, m_cache) == 0x10);
static_assert(offsetof(EntityObject, m_columns) == 0x20);
static_assert(offsetof(EntityObject, m_columns.table.m_maxLoadFactor) == 0x2c);
static_assert(offsetof(EntityObject, m_columns.table.m_size) == 0x30);
static_assert(offsetof(EntityObject, m_columns.table.m_buckets.m_data) == 0x40);
static_assert(offsetof(EntityObject, m_columns.table.m_buckets.m_count) == 0x48);
static_assert(offsetof(EntityObject, m_stmt) == 0x50);
static_assert(offsetof(EntityObject, m_db) == 0x58);
static_assert(sizeof(EntityObject) == 0x60);

// ---- Network: addresses and URIs ----------------------------------------------------------------

// Aska::Yayoi::IPAddress (0x88): a socket address (Clear memsets 0x88; the constructor clears the
// first word). Its bytes are a sockaddr_storage-like union (Set(sockaddr const&, len)); not mapped.
class IPAddress {
public:
    void Ctor();                        // _ZN4Aska5Yayoi9IPAddressC2Ev
    void Clear();                       // _ZN4Aska5Yayoi9IPAddress5ClearEv
    u16 GetPort() const;
    void SetPort(u16 port);

    u32 m_family;               // 0x00: 0 = unset (the constructor)
    u8 unk_04[0x84];            // 0x04
};
static_assert(sizeof(IPAddress) == 0x88);

// Aska::Yayoi::URI (0x100: operator new in Downloader::Download, which inlines the constructor:
// m_scheme = 5, memset 0x08..0x68, IPAddress(), m_resolved = 0). Held by Aska::TSharedPointer<URI>.
// Layout from Deserialize (the parts point into the buffer's second half, the work area, or into the
// copied text), DeleteBuffer, Clear (port/decomp/yayoi/network.c).
class URI {
public:
    s64 Deserialize(const char* text, u16 port, u32 family, s8* buffer, u64 size); // _ZN4Aska5Yayoi3URI11DeserializeEPKctNS0_13AddressFamilyEPam
                                        // (buffer 0: MemoryManager::Malloc from Global::m_pNetworkAllocator,
                                        //  size (strlen + 1) * 2 + 10, m_ownsBuffer)
    static u64 CalcBufferSize(const char* text);   // strlen * 2 + 12
    static u64 GetBufferSize(u64 length);           // length * 2 + 10
    void DeleteBuffer();                // _ZN4Aska5Yayoi3URI12DeleteBufferEv
    void Clear();                       // _ZN4Aska5Yayoi3URI5ClearEv

    u32 m_scheme;               // 0x00: 5 after construction (none); Deserialize: 0 for http
    u8 unk_04[4];               // 0x04
    u64 m_length;               // 0x08: strlen(text) + 1
    const char* m_host;         // 0x10
    u64 m_hostLength;           // 0x18
    const char* m_path;         // 0x20: Download takes its tail name as the file name
    u64 m_pathLength;           // 0x28
    const char* m_query;        // 0x30: (its pointer lands in the work area; only the length is reliable)
    u64 m_queryLength;          // 0x38
    const char* m_fragment;     // 0x40
    u64 m_fragmentLength;       // 0x48
    char* m_buffer;             // 0x50: the copied text (owned when m_ownsBuffer)
    char* m_work;               // 0x58: the buffer's second half (the parts are copied there, scheme first)
    u64 m_workSize;             // 0x60: buffer size / 2
    u8 m_ownsBuffer;            // 0x68
    u8 unk_69[7];               // 0x69
    IPAddress m_address;        // 0x70: Socket::ConvertIPAddrNtoB(host) + SetPort(port)
    u8 m_resolved;              // 0xf8: set when the address converted
    u8 unk_f9[7];               // 0xf9
};
static_assert(offsetof(URI, m_length) == 0x08);
static_assert(offsetof(URI, m_host) == 0x10);
static_assert(offsetof(URI, m_path) == 0x20);
static_assert(offsetof(URI, m_query) == 0x30);
static_assert(offsetof(URI, m_fragment) == 0x40);
static_assert(offsetof(URI, m_buffer) == 0x50);
static_assert(offsetof(URI, m_work) == 0x58);
static_assert(offsetof(URI, m_ownsBuffer) == 0x68);
static_assert(offsetof(URI, m_address) == 0x70);
static_assert(offsetof(URI, m_resolved) == 0xf8);
static_assert(sizeof(URI) == 0x100);

using URIPtr = containers::TSharedPointer<URI>;   // Aska::TSharedPointer<Aska::Yayoi::URI>

// Aska::Yayoi::HttpProtocol (0x48 as embedded in DownloadContext at +0x18; layout from its constructor).
class HttpProtocol {
public:
    void Ctor();                        // _ZN4Aska5Yayoi12HttpProtocolC1Ev

    u8 m_flag00;                // 0x00
    u8 unk_01[3];               // 0x01
    u32 m_value04;              // 0x04: 0xf7 after construction
    u64 m_value08;              // 0x08
    u64 m_value10;              // 0x10
    u32 m_value18;              // 0x18: 1 after construction
    u8 m_flag1c;                // 0x1c
    u8 unk_1d[3];               // 0x1d
    u64 m_value20;              // 0x20
    u64 m_value28;              // 0x28
    u8 m_flag30;                // 0x30: 1 after construction
    u8 unk_31[7];               // 0x31
    u64 m_value38;              // 0x38
    u16 m_value40;              // 0x40
    u8 unk_42[6];               // 0x42
};
static_assert(offsetof(HttpProtocol, m_value18) == 0x18);
static_assert(offsetof(HttpProtocol, m_flag30) == 0x30);
static_assert(sizeof(HttpProtocol) == 0x48);

// ---- Network: the downloader ---------------------------------------------------------------------

// Aska::Yayoi::Downloader::DownloadElement (0x338; Init allocates (queueSize + 1) of them): one queued
// download, a link of the Downloader's TList. Layout from its constructor, Reset, Set and
// Downloader::QueryDownloadElement (port/decomp/yayoi/downloader.c).
class DownloadElement {
public:
    void Ctor();                        // _ZN4Aska5Yayoi10Downloader15DownloadElementC1Ev
    void Reset();                       // _ZN4Aska5Yayoi10Downloader15DownloadElement5ResetEv
    s64 Set(u32 id, URIPtr uri, void* notify, const char* path, void* stream, const void* params, u64 n);

    const void* vtable;         // 0x00: _ZTVN4Aska5Yayoi10Downloader15DownloadElementE + 0x10
    DownloadElement* m_prev;    // 0x08: the TList links (QueryDownloadElement walks m_next)
    DownloadElement* m_next;    // 0x10
    u64 m_value18;              // 0x18: cleared by Reset
    u32 m_id;                   // 0x20: the download id (QueryDownloadElement's key)
    u8 unk_24[4];               // 0x24
    void* m_notify;             // 0x28: Aska::INotify* (kernel), cleared by Reset
    URIPtr m_uri;               // 0x30
    char m_path[0x148];         // 0x40: the destination path when it fits (Set: strlen + 1 <= 0x147)
    char* m_longPath;           // 0x188: new[] copy otherwise
    u8 m_stream[0x180];         // 0x190: the own Downloader::DownloadStream (an Aska::FileStream with an
                                //        Aska::File inside: the resource subsystem's classes; vtables at
                                //        +0x190 DownloadStream, +0x198 FileStream, +0x1a0 File)
    void* m_streamInUse;        // 0x310: IDownloadStream* (Set: the caller's or &m_stream)
    void* m_params;             // 0x318: Downloader::UriParam* (a copy in m_paramBuffer)
    u64 m_numParams;            // 0x320
    u8* m_paramBuffer;          // 0x328: new[]
    u8 m_flag330;               // 0x330
    u8 m_flag331;               // 0x331
    u8 unk_332[6];              // 0x332
};
static_assert(offsetof(DownloadElement, m_next) == 0x10);
static_assert(offsetof(DownloadElement, m_id) == 0x20);
static_assert(offsetof(DownloadElement, m_uri) == 0x30);
static_assert(offsetof(DownloadElement, m_path) == 0x40);
static_assert(offsetof(DownloadElement, m_longPath) == 0x188);
static_assert(offsetof(DownloadElement, m_stream) == 0x190);
static_assert(offsetof(DownloadElement, m_streamInUse) == 0x310);
static_assert(offsetof(DownloadElement, m_paramBuffer) == 0x328);
static_assert(sizeof(DownloadElement) == 0x338);

// Aska::Yayoi::Downloader::DownloadStatus (0x160; DownloadContext::GetDownloadStatus copies it out
// under the context's lock). Fields not mapped.
class DownloadStatus {
public:
    u8 m_flag00;                // 0x00: cleared by DownloadContext::Reset
    u8 unk_01[0x15f];
};
static_assert(sizeof(DownloadStatus) == 0x160);

// Aska::Yayoi::Downloader::DownloadContext (0x690; Init allocates (parallel + 1) of them): one running
// download, an HTTP client (THttpClient<TCP, 5> vtable at +0x10) with its HttpProtocol. Layout from its
// constructor, Initialize, Reset, GetDownloadStatus (port/decomp/yayoi/downloader.c).
class DownloadContext {
public:
    void Ctor();                        // _ZN4Aska5Yayoi10Downloader15DownloadContextC1Ev
    bool Initialize();                  // _ZN4Aska5Yayoi10Downloader15DownloadContext10InitializeEv
    void Reset();                       // _ZN4Aska5Yayoi10Downloader15DownloadContext5ResetEv
    void GetDownloadStatus(DownloadStatus* out) const;  // locked copy of m_status
    // StartDownload / FinishDownload / StopDownload / Pause / Resume, the On* client callbacks

    const void* vtable;         // 0x00: _ZTVN4Aska5Yayoi10Downloader15DownloadContextE + 0x10
    u8 unk_08[8];               // 0x08
    const void* m_clientVtable; // 0x10: THttpClient<TCP, 5> (the client base)
    HttpProtocol m_http;        // 0x18
    u8 m_flag60;                // 0x60
    u8 unk_61[7];               // 0x61
    const void* m_recordQueueVtable; // 0x68: TQueue<SSLProtocol::RecordLayer, 10> (the SSL record queue)
    u8 unk_70[0x3f0];           // 0x70: the queue's records and the client state (cleared by the constructor)
    u8 m_initialized460;        // 0x460: Initialize's one-time setup done
    u8 unk_461[7];              // 0x461
    void* m_value468;           // 0x468: &m_flag60 after Initialize
    void* m_value470;           // 0x470: &m_http after Initialize
    u8 unk_478[0x10];           // 0x478
    FastCriticalSection m_cs;   // 0x488: guards m_status
    DownloadStatus m_status;    // 0x518
    u64 m_value678;             // 0x678: cleared by Reset
    u64 m_value680;             // 0x680
    u32 m_value688;             // 0x688
    u8 m_initialized;           // 0x68c: Initialize ran
    u8 unk_68d[3];              // 0x68d
};
static_assert(offsetof(DownloadContext, m_http) == 0x18);
static_assert(offsetof(DownloadContext, m_initialized460) == 0x460);
static_assert(offsetof(DownloadContext, m_cs) == 0x488);
static_assert(offsetof(DownloadContext, m_status) == 0x518);
static_assert(offsetof(DownloadContext, m_initialized) == 0x68c);
static_assert(sizeof(DownloadContext) == 0x690);

// Aska::Yayoi::Downloader (0x680: operator new in NetworkManager::InitializeThreads, then
// Init(parallel, queue) from AppNetworkCommonSettingProxy and SetPath(Global::m_pszDownloadContentPath)).
// Layout from the constructor, Init, SetPath, QueryDownloadElement, Download (port/decomp/yayoi/downloader.c).
// Its worker thread (WorkerThread, a TWorkerThreadBase) runs ThreadHandler; the queues are
// TDynamicQueue<T, false> rings over one new[] block (Init: elements, element ring, finish ring, contexts).
class Downloader {
public:
    void Ctor();                        // _ZN4Aska5Yayoi10DownloaderC1Ev
    s64 Init(s32 parallel, s32 queueSize);   // _ZN4Aska5Yayoi10Downloader4InitEii
    void Term();
    bool SetPath(const char* path);     // _ZN4Aska5Yayoi10Downloader7SetPathEPKc (strlen < 0x104; creates the directory)
    s64 Download(u32 id, const char* url, void* notify, const char* name, const char* dir, const void* params,
                 u64 n, void* stream);  // _ZN4Aska5Yayoi10Downloader8DownloadEjPKcPNS_7INotifyES3_S3_PKNS1_8UriParamEmPNS1_15IDownloadStreamE
    DownloadElement* QueryDownloadElement(u32 id) const;   // locked walk of m_list
    void ThreadHandler();               // _ZN4Aska5Yayoi10Downloader13ThreadHandlerEv (the worker loop)
    // Stop / Pause / Resume / OrFlagDownload / GetDownloadStatus / AcquireFreeDownloadContext / ...

    const void* vtable;                 // 0x00: _ZTVN4Aska5Yayoi10DownloaderE + 0x10
    // Downloader::WorkerThread (0x08..0x98): an Aska::Thread, an Aska::Event and its owner
    Thread m_thread;                    // 0x08: vtable = _ZTVN4Aska5Yayoi10Downloader12WorkerThreadE + 0x10
    u8 unk_18[8];                       // 0x18
    Event m_event;                      // 0x20: Aska::Event (sync)
    u8 m_flag88;                        // 0x88
    u8 m_flag89;                        // 0x89
    u8 unk_8a[6];                       // 0x8a
    Downloader* m_owner;                // 0x90: this
    // Aska::TList<DownloadElement> (0x98..0x3e0): vtable, the sentinel element, the count
    const void* m_listVtable;           // 0x98: _ZTVN4Aska5TListINS_5Yayoi10Downloader15DownloadElementEEE + 0x10
    DownloadElement m_listHead;         // 0xa0: the sentinel (its m_prev / m_next: the list's tail / head)
    u32 m_listCount;                    // 0x3d8
    u8 unk_3dc[4];                      // 0x3dc
    memory::TDynamicQueue<DownloadElement*> m_freeElements;  // 0x3e0: Init fills it with the element block
    memory::TDynamicQueue<DownloadContext*> m_freeContexts;  // 0x400
    memory::TDynamicQueue<u32> m_finished;                   // 0x420: AddDownloadFinishQueue
    FastCriticalSection m_cs;           // 0x440: guards the list and the queues
    FastCriticalSection m_cs2;          // 0x4d0
    char m_path[0x104];                 // 0x560: SetPath (the download content directory)
    u8 unk_664[4];                      // 0x664
    u8* m_storage;                      // 0x668: Init's new[] block
    u32 m_value670;                     // 0x670
    s32 m_parallel;                     // 0x674: contexts (Init's first argument)
    s32 m_queueSize;                    // 0x678: elements (the second)
    u8 unk_67c[4];                      // 0x67c
};
static_assert(offsetof(Downloader, m_event) == 0x20);
static_assert(offsetof(Downloader, m_owner) == 0x90);
static_assert(offsetof(Downloader, m_listVtable) == 0x98);
static_assert(offsetof(Downloader, m_listHead) == 0xa0);
static_assert(offsetof(Downloader, m_listCount) == 0x3d8);
static_assert(offsetof(Downloader, m_freeElements) == 0x3e0);
static_assert(offsetof(Downloader, m_freeContexts) == 0x400);
static_assert(offsetof(Downloader, m_finished) == 0x420);
static_assert(offsetof(Downloader, m_cs) == 0x440);
static_assert(offsetof(Downloader, m_cs2) == 0x4d0);
static_assert(offsetof(Downloader, m_path) == 0x560);
static_assert(offsetof(Downloader, m_storage) == 0x668);
static_assert(offsetof(Downloader, m_parallel) == 0x674);
static_assert(offsetof(Downloader, m_queueSize) == 0x678);
static_assert(sizeof(Downloader) == 0x680);

// ---- Network: the manager and its thread ---------------------------------------------------------

// Aska::Yayoi::NetworkManagerThread (0x58: operator new in NetworkManager::InitializeThreads). An
// Aska::Thread (Handler: wait on m_wakeup, run the TaskManager, NetworkEvent::Run, flush the native
// HTTP requests) with a second interface at +0x18 (DoWakeup / GetThreadID thunks).
class NetworkManagerThread {
public:
    void Ctor();                        // _ZN4Aska5Yayoi20NetworkManagerThreadC1Ev
    bool Init();                        // _ZN4Aska5Yayoi20NetworkManagerThread4InitEv
    void Handler();                     // _ZN4Aska5Yayoi20NetworkManagerThread7HandlerEv
    void Kill();
    void DoWakeup();
    s64 GetThreadID();

    Thread m_thread;            // 0x00: Aska::Thread (sync): vtable = _ZTVN4Aska5Yayoi20NetworkManagerThreadE + 0x10,
                                //       +0x08 the thread id (NetworkManager copies it to m_threadId)
    u8 unk_10[8];               // 0x10
    const void* m_wakeVtable;   // 0x18: the second base: _ZTV... + 0x48
    void* m_taskManager;        // 0x20: Aska::TaskManager* (kernel; operator new 0xff0)
    void* m_event;              // 0x28: Aska::Yayoi::NetworkEvent* (operator new 0x670)
    void* m_httpProcessor;      // 0x30: Aska::Yayoi::NativeHttpRequestProcessor* (operator new 0x8d0)
    Semaphore m_wakeup;         // 0x38: Aska::Semaphore (sync)
    u8 m_quit;                  // 0x50
    u8 unk_51[7];               // 0x51
};
static_assert(offsetof(NetworkManagerThread, m_wakeVtable) == 0x18);
static_assert(offsetof(NetworkManagerThread, m_taskManager) == 0x20);
static_assert(offsetof(NetworkManagerThread, m_event) == 0x28);
static_assert(offsetof(NetworkManagerThread, m_httpProcessor) == 0x30);
static_assert(offsetof(NetworkManagerThread, m_wakeup) == 0x38);
static_assert(offsetof(NetworkManagerThread, m_quit) == 0x50);
static_assert(sizeof(NetworkManagerThread) == 0x58);

using NetworkEventMap = containers::THashMap<s64, void*>;   // THashMap<long, NetworkEvent*>
static_assert(sizeof(NetworkEventMap) == 0x30);

// Aska::Yayoi::NetworkManager (Global::m_pNetworkManager). Layout from the constructor, Initialize,
// InitializeThreads, GetNetworkEvent, RegisterNetworkEvent, RegisterHttpRequestProcessor
// (port/decomp/yayoi/network.c). Size: the last field ends at 0x1b0 (allocated by kernel's Global).
class NetworkManager {
public:
    void Ctor();                        // _ZN4Aska5Yayoi14NetworkManagerC1Ev
    bool Initialize();                  // _ZN4Aska5Yayoi14NetworkManager10InitializeEv (CookieManager, PaymentClient)
    bool InitializeThreads();           // _ZN4Aska5Yayoi14NetworkManager17InitializeThreadsEv (thread + Downloader)
    void* GetNetworkEvent(s64 threadId);// _ZN4Aska5Yayoi14NetworkManager15GetNetworkEventEl (0: m_threadId's)
    bool RegisterNetworkEvent(s64 threadId, void* event);
    bool RegisterHttpRequestProcessor(void* processor);
    // BeginPoll / BeginConnect / AddErrorCallback / AddHttpRequest / RegisterVersatileTask / Kill

    NetworkEventMap m_events;           // 0x00: thread id -> NetworkEvent*
    FastCriticalSection m_cs;           // 0x30: guards m_events
    NetworkManagerThread* m_thread;     // 0xc0
    s64 m_threadId;                     // 0xc8: m_thread's id (GetNetworkEvent(0))
    void* m_paymentClient;              // 0xd0: Aska::Yayoi::PaymentClient* (0x30)
    void* m_httpProcessor;              // 0xd8: NativeHttpRequestProcessor* (RegisterHttpRequestProcessor)
    u8 m_dnsCache[0xc0];                // 0xe0: Aska::Yayoi::DNSCache (constructed in place; not mapped)
    void* m_cookieManager;              // 0x1a0: Aska::Yayoi::CookieManager* (0x6e0)
    Downloader* m_downloader;           // 0x1a8
};
static_assert(offsetof(NetworkManager, m_cs) == 0x30);
static_assert(offsetof(NetworkManager, m_thread) == 0xc0);
static_assert(offsetof(NetworkManager, m_threadId) == 0xc8);
static_assert(offsetof(NetworkManager, m_paymentClient) == 0xd0);
static_assert(offsetof(NetworkManager, m_httpProcessor) == 0xd8);
static_assert(offsetof(NetworkManager, m_dnsCache) == 0xe0);
static_assert(offsetof(NetworkManager, m_cookieManager) == 0x1a0);
static_assert(offsetof(NetworkManager, m_downloader) == 0x1a8);
static_assert(sizeof(NetworkManager) == 0x1b0);

// Aska::Yayoi::NativeHttpClient (0x38: the constructor clears seven words; pooled 32 at a time in
// NativeHttpRequestProcessor's TPoolAtomic): one request handed to the Java side (_doRequest).
class NativeHttpClient {
public:
    void Ctor();                        // _ZN4Aska5Yayoi16NativeHttpClientC1Ev
    void _doRequest();                  // _ZN4Aska5Yayoi16NativeHttpClient10_doRequestEv

    u64 m_words[7];             // 0x00: cleared by the constructor; not mapped
};
static_assert(sizeof(NativeHttpClient) == 0x38);

// Aska::Yayoi::NativeHttpRequestProcessor (0x8d0: operator new in NetworkManagerThread::Init). A
// TQueue<NativeHttpClient*, 32> at 0, a TPoolAtomic<NativeHttpClient, 32> at 0x118, a FastCriticalSection
// at 0x838, a flag at 0x8c8 (constructor).
class NativeHttpRequestProcessor {
public:
    void Ctor();                        // _ZN4Aska5Yayoi26NativeHttpRequestProcessorC1Ev
    s64 Initialize();
    s64 FlushRequests(bool* more);      // _ZN4Aska5Yayoi26NativeHttpRequestProcessor13FlushRequestsEPb

    const void* m_queueVtable;  // 0x00: TQueue<NativeHttpClient*, 32>
    u32 m_queueWrite;           // 0x08: 1 after construction
    u32 m_queueRead;            // 0x0c
    u8 unk_10[0x108];           // 0x10: the queue's slots
    u8 m_pool[0x720];           // 0x118: TPoolAtomic<NativeHttpClient, 32> (containers; not mapped)
    FastCriticalSection m_cs;   // 0x838
    u8 m_flag8c8;               // 0x8c8
    u8 unk_8c9[7];              // 0x8c9
};
static_assert(offsetof(NativeHttpRequestProcessor, m_pool) == 0x118);
static_assert(offsetof(NativeHttpRequestProcessor, m_cs) == 0x838);
static_assert(offsetof(NativeHttpRequestProcessor, m_flag8c8) == 0x8c8);
static_assert(sizeof(NativeHttpRequestProcessor) == 0x8d0);

}  // namespace soa::native::yayoi

#endif  // SOA_NATIVE_YAYOI_LAYOUT_H
