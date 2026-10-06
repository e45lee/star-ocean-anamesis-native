// Layout tests for yayoi_layout.h (port/PLAN.md task 6, types first): the recovered classes read
// against real guest objects. A private SQLiteDriver + EntityObject run a small :memory: database
// through the guest's own driver (the guest SQLite in --selftest, natives off); the running game's
// NetworkManager, its thread and the Downloader are walked read-only.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/test.h"
#include "native/yayoi/yayoi_layout.h"

using namespace soa;
using namespace soa::native::yayoi;

namespace {

template <typename T>
T* instance(u64 vaddr) {
    return *reinterpret_cast<T**>(main_lib()->base + vaddr);
}
u64 vtable_of(TestContext& t, const char* ztv) { return t.sym(ztv) + 0x10; }

// A guest call returning an Aska::Status through x8.
s64 call_status(TestContext& t, const char* name, std::initializer_list<u64> args) {
    s64 st = 0x5a5a5a5a;
    GuestArgs a;
    for (u64 v : args) a.i(v);
    a.sret(&st);
    t.call(name, a);
    return st;
}

const char* kExecute = "_ZN4Aska5Yayoi12SQLiteDriver8_ExecuteEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE";
const char* kFind = "_ZN4Aska5Yayoi12SQLiteDriver4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE";

// The column index the guest's name map holds for `name`, walking the buckets through ColumnMap.
int column_of(const EntityObject& eo, const char* name, int* found) {
    const auto& b = eo.m_columns.table.m_buckets;
    *found = 0;
    int idx = -1;
    for (u64 i = 0; i < b.m_count; i++)
        if (b.m_data[i].m_state == 1 && std::strcmp(b.m_data[i].m_value.first, name) == 0) {
            ++*found;
            idx = b.m_data[i].m_value.second;
        }
    return idx;
}

}  // namespace

// A private SQLiteDriver on :memory: driven by the guest: DoOpen, _Execute (DDL, binds), the
// transaction flags, Find into a private EntityObject, Fetch / Get*, the column-name map, the cache
// buffer, and the destructors. Every field read through SQLiteDriver / EntityObject / QueryParam.
NATIVE_TEST("yayoi/layout-sqlite-driver") {
    alignas(16) static u8 dstore[sizeof(SQLiteDriver)];
    alignas(16) static u8 estore[sizeof(EntityObject)];
    std::memset(dstore, 0xa5, sizeof dstore);
    std::memset(estore, 0xa5, sizeof estore);
    auto* drv = reinterpret_cast<SQLiteDriver*>(dstore);
    auto* eo = reinterpret_cast<EntityObject*>(estore);
    const u64 d = (u64)drv;
    t.call("_ZN4Aska5Yayoi12SQLiteDriverC1Ev", {d});
    t.expect_eq(drv->m_db, (void*)nullptr, "ctor: m_db");
    t.expect_eq(drv->m_stmt, (void*)nullptr, "ctor: m_stmt");
    t.expect_eq(drv->m_address, (const DBAddress*)nullptr, "ctor: m_address");
    t.expect_eq(drv->m_prepared, (u8)0, "ctor: m_prepared");
    t.expect_eq(dstore[0x61], (u8)0xa5, "ctor stops at 0x61");

    static DBAddress addr{":memory:"};
    s64 st = call_status(t, "_ZN4Aska5Yayoi12SQLiteDriver6DoOpenENS0_6Entity4ModeEPKcPKNS0_9DBAddressE", {d, 1, 0, (u64)&addr});
    if (!t.expect_eq(st, status::kOk, "DoOpen")) return;
    t.expect_eq(drv->m_db != nullptr, true, "DoOpen: m_db");
    t.expect_eq(drv->m_address, (const DBAddress*)&addr, "DoOpen: m_address");
    // Reopening the same address keeps the connection.
    void* db = drv->m_db;
    st = call_status(t, "_ZN4Aska5Yayoi12SQLiteDriver6DoOpenENS0_6Entity4ModeEPKcPKNS0_9DBAddressE", {d, 1, 0, (u64)&addr});
    t.expect_eq(drv->m_db, db, "DoOpen same address: same db");

    st = call_status(t, kExecute, {d, (u64)"CREATE TABLE t(id INTEGER, name TEXT, v REAL, n INTEGER)", 0, 0, 0});
    t.expect_eq(st, status::kOk, "CREATE TABLE");
    t.expect_eq(drv->m_prepared, (u8)1, "_Prepare sets m_prepared");
    t.expect_eq(drv->m_stmt != nullptr, true, "the live statement");
    t.expect_eq(drv->m_lastParams, (const QueryParam*)nullptr, "no params bound");

    // The transaction flags.
    t.expect_eq(call_status(t, "_ZN4Aska5Yayoi12SQLiteDriver16BeginTransactionEv", {d}), status::kOk, "BeginTransaction");
    t.expect_eq(drv->m_beginRequested, (u8)1, "BeginTransaction requests");
    t.expect_eq(drv->m_inTransaction, (u8)0, "not yet in a transaction");
    t.expect_eq(call_status(t, "_ZN4Aska5Yayoi12SQLiteDriver16BeginTransactionEv", {d}), status::kBusy, "BeginTransaction twice");
    t.expect_eq(call_status(t, "_ZN4Aska5Yayoi12SQLiteDriver17_BeginTransactionEv", {d}), status::kOk, "_BeginTransaction");
    t.expect_eq(drv->m_inTransaction, (u8)1, "in a transaction");
    t.expect_eq(drv->m_beginRequested, (u8)0, "request consumed");

    // Rows bound through QueryParam (text binds; the column affinity converts).
    static QueryParam p[4];
    static const char* rows[3][4] = {{"7", "alpha", "1.5", "70"}, {"8", "beta", "2.25", "80"}, {"9", "gamma", "-3", "90"}};
    for (auto& r : rows) {
        std::memset(p, 0, sizeof p);
        for (int i = 0; i < 4; i++) {
            p[i].m_text = r[i];
            p[i].m_length = (s32)std::strlen(r[i]);
        }
        st = call_status(t, kExecute, {d, (u64)"INSERT INTO t VALUES(?, ?, ?, ?)", (u64)p, 4, 0});
        t.expect_eq(st, status::kOk, "INSERT");
        t.expect_eq(drv->m_lastParams, (const QueryParam*)p, "m_lastParams = the bound params");
    }
    st = call_status(t, kExecute, {d, (u64)"INSERT INTO t VALUES(?, ?, ?, ?)", (u64)p, 3, 0});
    t.expect_eq(st, status::kInvalidArg, "_Execute: wrong parameter count");
    t.expect_eq(call_status(t, "_ZN4Aska5Yayoi12SQLiteDriver6CommitEv", {d}), status::kOk, "Commit");
    t.expect_eq(drv->m_inTransaction, (u8)0, "Commit ends the transaction");
    t.expect_eq(call_status(t, "_ZN4Aska5Yayoi12SQLiteDriver8RollbackEv", {d}), status::kNotReady, "Rollback outside");

    // Find into a private EntityObject.
    t.call("_ZN4Aska5Yayoi12SQLiteDriver12EntityObjectC1Ev", {(u64)eo});
    t.expect_eq((u64)eo->m_columns.table.vtable,
                vtable_of(t, "_ZTVN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEEE"),
                "EntityObject: the name map's vtable");
    t.expect_eq(eo->m_columns.table.m_buckets.m_count, (u64)0x11, "17 buckets");
    t.expect_eq(eo->m_columns.table.m_maxLoadFactor, 0.75f, "max load 0.75");
    t.expect_eq(eo->m_stmt, (void*)nullptr, "no statement yet");
    std::memset(p, 0, sizeof p);
    p[0].m_text = "7";
    p[0].m_length = 1;
    st = call_status(t, kFind, {d, (u64)"SELECT id, name, v, n AS count FROM t WHERE id >= ? ORDER BY id", (u64)p, 1, (u64)eo});
    if (!t.expect_eq(st, status::kOk, "Find")) return;
    t.expect_eq(eo->m_stmt, drv->m_stmt, "Store: m_stmt = the driver's statement");
    t.expect_eq(eo->m_db, drv->m_db, "Store: m_db");
    t.expect_eq(eo->m_numColumns, (s32)4, "Store: 4 columns");
    t.expect_eq(eo->m_columns.table.m_size, (u32)4, "4 names in the map");
    static const char* names[4] = {"id", "name", "v", "count"};
    for (int i = 0; i < 4; i++) {
        int found = 0;
        t.expect_eq(column_of(*eo, names[i], &found), i, "name -> index");
        t.expect_eq(found, 1, "each name once");
    }
    const char* kGetInt = "_ZN4Aska5Yayoi12SQLiteDriver12EntityObject10GetIntegerEiPim";
    const char* kGetIntByName = "_ZN4Aska5Yayoi12SQLiteDriver12EntityObject10GetIntegerEPKcPim";
    const char* kGetString = "_ZN4Aska5Yayoi12SQLiteDriver12EntityObject9GetStringEiPcPmm";
    const char* kGetType = "_ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetTypeEim";
    const char* kFetch = "_ZN4Aska5Yayoi12SQLiteDriver12EntityObject5FetchEv";
    for (int r = 0; r < 3; r++) {
        if (!t.expect_eq(call_status(t, kFetch, {(u64)eo}), status::kOk, "Fetch a row")) break;
        s32 id = -1, cnt = -1;
        t.expect_eq(call_status(t, kGetInt, {(u64)eo, 0, (u64)&id, 0}), status::kOk, "GetInteger(0)");
        t.expect_eq(id, (s32)std::atoi(rows[r][0]), "id");
        t.expect_eq(call_status(t, kGetIntByName, {(u64)eo, (u64)"count", (u64)&cnt, 0}), status::kOk, "GetInteger(\"count\")");
        t.expect_eq(cnt, (s32)std::atoi(rows[r][3]), "count by name");
        char buf[64] = {};
        u64 size = sizeof buf;
        t.expect_eq(call_status(t, kGetString, {(u64)eo, 1, (u64)buf, (u64)&size, 0}), status::kOk, "GetString(1)");
        t.expect_eq(std::string(buf), std::string(rows[r][1]), "name");
        t.expect_eq((s32)t.call(kGetType, {(u64)eo, 1, 0}), (s32)3, "GetType(1) = SQLITE_TEXT");
        t.expect_eq((s32)t.call(kGetType, {(u64)eo, 2, 0}), (s32)2, "GetType(2) = SQLITE_FLOAT");
    }
    t.expect_eq(call_status(t, kFetch, {(u64)eo}), status::kNoMoreRows, "Fetch past the end");
    s32 dummy = 0;
    t.expect_eq(call_status(t, kGetIntByName, {(u64)eo, (u64)"nope", (u64)&dummy, 0}), status::kNameNotFound, "unknown name");
    t.expect_eq(call_status(t, kGetInt, {(u64)eo, 0, 0, 0}), status::kInvalidArg, "null out");
    // The cache buffer.
    t.expect_eq(call_status(t, "_ZN4Aska5Yayoi12SQLiteDriver12EntityObject17CreateCacheBufferEm", {(u64)eo, 0x40}), status::kOk,
                "CreateCacheBuffer");
    t.expect_eq(eo->m_cacheSize, (u64)0x40, "m_cacheSize");
    u64 csize = 0;
    t.expect_eq(t.call("_ZN4Aska5Yayoi12SQLiteDriver12EntityObject14GetCacheBufferEPm", {(u64)eo, (u64)&csize}), (u64)eo->m_cache,
                "GetCacheBuffer = m_cache");
    t.expect_eq(csize, (u64)0x40, "GetCacheBuffer size");
    t.call("_ZN4Aska5Yayoi12SQLiteDriver12EntityObject10ClearCacheEv", {(u64)eo});
    t.expect_eq(eo->m_cache, (u8*)nullptr, "ClearCache");
    t.expect_eq(eo->m_cacheSize, (u64)0, "ClearCache: size");
    // Teardown.
    t.call("_ZN4Aska5Yayoi12SQLiteDriver12EntityObjectD1Ev", {(u64)eo});
    t.expect_eq(eo->m_columns.table.m_buckets.m_data == nullptr, true,
                "~EntityObject frees the buckets");
    t.call("_ZN4Aska5Yayoi12SQLiteDriver5CloseEv", {d});
    t.expect_eq(drv->m_db, (void*)nullptr, "Close: m_db");
    t.expect_eq(drv->m_stmt, (void*)nullptr, "Close: m_stmt");
    t.expect_eq(drv->m_address, (const DBAddress*)nullptr, "Close: m_address");
    t.call("_ZN4Aska5Yayoi12SQLiteDriverD1Ev", {d});
}

// Aska::Yayoi::URI on a private object with a caller buffer: Deserialize's parts read through URI.
// (A URL with an explicit ":port" fails ConvertIPAddrNtoB in this build: status -0x3c8; the game's
// URLs carry none.)
NATIVE_TEST("yayoi/layout-uri") {
    alignas(16) static u8 ustore[sizeof(URI)];
    alignas(16) static s8 buf[256];
    std::memset(ustore, 0, sizeof ustore);
    auto* uri = reinterpret_cast<URI*>(ustore);
    t.call("_ZN4Aska5Yayoi9IPAddressC2Ev", {(u64)&uri->m_address});
    const char* text = "http://127.0.0.1/dir/file.bin?x=1#frag";
    s64 st = call_status(t, "_ZN4Aska5Yayoi3URI11DeserializeEPKctNS0_13AddressFamilyEPam", {(u64)uri, (u64)text, 0x50, 0, (u64)buf, sizeof buf});
    if (!t.expect_eq(st, status::kOk, "Deserialize")) return;
    t.expect_eq(uri->m_scheme, (u32)0, "m_scheme (http)");
    t.expect_eq(uri->m_length, (u64)std::strlen(text) + 1, "m_length");
    t.expect_eq(uri->m_buffer, (char*)buf, "m_buffer = the caller's");
    t.expect_eq(uri->m_work, (char*)buf + sizeof buf / 2, "m_work = the buffer's second half");
    t.expect_eq(uri->m_workSize, (u64)sizeof buf / 2, "m_workSize");
    t.expect_eq(uri->m_ownsBuffer, (u8)0, "not owned");
    t.expect_eq(std::string(uri->m_buffer), std::string(text), "the text copied into the buffer");
    t.expect_eq(std::string(uri->m_work), std::string("http"), "the scheme at the work area's start");
    t.expect_eq(std::string(uri->m_host, uri->m_hostLength), std::string("127.0.0.1"), "m_host / m_hostLength");
    t.expect_eq(std::string(uri->m_host), std::string("127.0.0.1"), "m_host terminated");
    t.expect_eq(std::string(uri->m_path, uri->m_pathLength), std::string("/dir/file.bin"), "m_path / m_pathLength");
    t.expect_eq(uri->m_queryLength, (u64)3, "m_queryLength (\"x=1\")");
    t.expect_eq(std::string(uri->m_fragment, uri->m_fragmentLength), std::string("frag"), "m_fragment / m_fragmentLength");
    t.expect_eq(uri->m_resolved, (u8)1, "m_resolved (the address converted)");
    t.expect_eq((u16)t.call("_ZNK4Aska5Yayoi9IPAddress7GetPortEv", {(u64)&uri->m_address}), (u16)0x50, "the address' port");
    t.call("_ZN4Aska5Yayoi3URI12DeleteBufferEv", {(u64)uri});
    t.expect_eq(uri->m_buffer, (char*)nullptr, "DeleteBuffer: m_buffer");
}

// The running game's network objects, read-only.
NATIVE_TEST("yayoi/layout-live-network") {
    auto* nm = instance<NetworkManager>(kVaddrNetworkManager);
    if (!t.expect_eq(nm != nullptr, true, "Global::m_pNetworkManager")) return;
    t.expect_eq((u64)nm->m_events.table.vtable,
                vtable_of(t, "_ZTVN4Aska8THashMapIlPNS_5Yayoi12NetworkEventENS_7THasherIlEENS_8TEqualToIlEENS_10TAllocatorINS_5TPairIKlS3_EEEEEE"),
                "m_events vtable");
    NetworkManagerThread* th = nm->m_thread;
    if (t.expect_eq(th != nullptr, true, "m_thread")) {
        const u64 vt = t.sym("_ZTVN4Aska5Yayoi20NetworkManagerThreadE");
        t.expect_eq((u64)th->m_thread.vtable, vt + 0x10, "thread vtable");
        t.expect_eq((u64)th->m_wakeVtable, vt + 0x48, "second base vtable (+0x48)");
        t.expect_eq((u64)nm->m_threadId, th->m_thread.m_thread, "m_threadId = the thread's id");
        t.expect_eq(th->m_quit, (u8)0, "thread running");
        t.expect_eq(th->m_taskManager != nullptr, true, "the thread's TaskManager");
        t.expect_eq(t.call("_ZN4Aska5Yayoi14NetworkManager15GetNetworkEventEl", {(u64)nm, 0}), (u64)th->m_event,
                    "GetNetworkEvent(0) = the thread's NetworkEvent");
        t.expect_eq(nm->m_httpProcessor, th->m_httpProcessor, "the HTTP processor registered");
        auto* hp = reinterpret_cast<const NativeHttpRequestProcessor*>(th->m_httpProcessor);
        if (hp)
            t.expect_eq((u64)hp->m_queueVtable,
                        vtable_of(t, "_ZTVN4Aska6TQueueIPNS_5Yayoi16NativeHttpClientELi32EEE"), "processor's queue vtable");
    }
    Downloader* dl = nm->m_downloader;
    if (!t.expect_eq(dl != nullptr, true, "m_downloader")) return;
    t.expect_eq((u64)dl->vtable, vtable_of(t, "_ZTVN4Aska5Yayoi10DownloaderE"), "Downloader vtable");
    t.expect_eq((u64)dl->m_thread.vtable, vtable_of(t, "_ZTVN4Aska5Yayoi10Downloader12WorkerThreadE"),
                "WorkerThread vtable");
    t.expect_eq(dl->m_owner, dl, "m_owner");
    t.expect_eq((u64)dl->m_listVtable, vtable_of(t, "_ZTVN4Aska5TListINS_5Yayoi10Downloader15DownloadElementEEE"), "TList vtable");
    t.expect_eq((u64)dl->m_listHead.vtable, vtable_of(t, "_ZTVN4Aska5Yayoi10Downloader15DownloadElementE"), "sentinel vtable");
    t.expect_eq((u64)dl->m_freeElements.vtable, vtable_of(t, "_ZTVN4Aska13TDynamicQueueIPNS_5Yayoi10Downloader15DownloadElementELb0EEE"),
                "element queue vtable");
    t.expect_eq((u64)dl->m_freeContexts.vtable, vtable_of(t, "_ZTVN4Aska13TDynamicQueueIPNS_5Yayoi10Downloader15DownloadContextELb0EEE"),
                "context queue vtable");
    t.expect_eq((u64)dl->m_finished.vtable, vtable_of(t, "_ZTVN4Aska13TDynamicQueueIjLb0EEE"), "finish queue vtable");
    const char* path = instance<const char>(kVaddrDownloadContentPath);
    if (path) t.expect_eq(std::string(dl->m_path), std::string(path), "m_path = Global::m_pszDownloadContentPath");
    t.expect_eq(dl->m_parallel > 0 && dl->m_queueSize > 0, true, "Init's sizes");
    t.expect_eq(dl->m_freeElements.m_capacity, (u32)(dl->m_queueSize + 1), "element ring capacity = queue + 1");
    t.expect_eq(dl->m_freeContexts.m_capacity, (u32)(dl->m_parallel + 1), "context ring capacity = parallel + 1");
    // Init's block: elements, the element ring, the finish ring, the contexts (sizes from the classes).
    const u64 q = (u64)dl->m_queueSize + 1, n = (u64)dl->m_parallel + 1;
    u8* base = dl->m_storage;
    t.expect_eq((u64)dl->m_freeElements.m_items, (u64)(base + q * sizeof(DownloadElement)), "element ring after the elements");
    // The element block is raw memory (Init only puts its addresses in the free ring; an element is
    // built when queued): each free slot points into it at a 0x338 stride. Only the ring's live
    // slots, m_read + 1 up to m_write: Init starts at write 1 / read 0 and never writes slot 0 (the
    // slot the reader holds back), and the block is operator new[] memory, not cleared (the host
    // malloc's leftovers: zero on Linux by chance, a stale value on Windows).
    const auto& fe = dl->m_freeElements;
    t.expect_eq(fe.m_write < fe.m_capacity && fe.m_read < fe.m_capacity, true, "element ring indices in range");
    u32 live = 0;
    for (u32 i = (fe.m_read + 1) % fe.m_capacity; i != fe.m_write && live < fe.m_capacity; i = (i + 1) % fe.m_capacity, live++) {
        u64 off = (u64)fe.m_items[i] - (u64)base;
        t.expect_eq(off < q * sizeof(DownloadElement) && off % sizeof(DownloadElement) == 0, true,
                    "free element slot -> the element block, stride 0x338");
    }
    t.expect_eq(live <= (u32)dl->m_queueSize, true, "free elements <= the queue size");
    auto* ctx = reinterpret_cast<DownloadContext*>(base + q * (sizeof(DownloadElement) + 8 + 4));
    for (u64 i = 0; i < n; i++) {
        t.expect_eq((u64)ctx[i].vtable, vtable_of(t, "_ZTVN4Aska5Yayoi10Downloader15DownloadContextE"), "context vtable (stride 0x690)");
        t.expect_eq((u64)ctx[i].m_clientVtable, vtable_of(t, "_ZTVN4Aska5Yayoi11THttpClientINS0_3TCPELi5EEE"), "context client vtable");
        static DownloadStatus s;
        t.call("_ZNK4Aska5Yayoi10Downloader15DownloadContext17GetDownloadStatusEPNS1_14DownloadStatusE", {(u64)&ctx[i], (u64)&s});
        t.expect_eq(std::memcmp(&s, &ctx[i].m_status, sizeof s), 0, "GetDownloadStatus copies m_status");
    }
    t.expect_eq(t.call("_ZNK4Aska5Yayoi10Downloader20QueryDownloadElementEj", {(u64)dl, 0xfffffff0u}), (u64)0, "no such download");
}
