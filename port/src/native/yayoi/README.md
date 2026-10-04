# `yayoi`: Aska::Yayoi: network and the SQLite driver

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/yayoi/scope.txt`](../../../decomp/yayoi/scope.txt).
- Decompiles and the function list: [`port/decomp/yayoi/`](../../../decomp/yayoi/) (`symbols.tsv`; `tools/decomp.sh --into yayoi/<topic>`).
- Types: [`yayoi_layout.h`](yayoi_layout.h); for Ghidra, `tools/subsystem.py export-types yayoi` -> `port/decomp/yayoi/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Type recovery a wave ahead of the code (port/REBUILD-QUEUE.md: yayoi is wave 4). Layouts are proven by
[`yayoi_layout_test.cpp`](yayoi_layout_test.cpp) (`soa --selftest yayoi/`, 3 tests, all pass). Scope:
what executes in the profiled flows (132 of 2,744 functions); the driver first, then the network objects
the offline client keeps running.

| Class (guest) | Guest size | Found from | Proven by (yayoi/layout-...) | Status |
|---|---|---|---|---|
| `SQLiteDriver` | 0x68 (ctor clears 0x00..0x60) | ctor, dtor, Close, Open, DoOpen, _Prepare, _Execute, Find, Begin/_Begin/Commit/Rollback | `-sqlite-driver` (private, `:memory:`: DoOpen / reopen, DDL, the transaction flags and their statuses, 3 INSERTs bound through QueryParam, m_lastParams, the param-count check, Close, the destructor) | typed; 0x08, 0x48, the 0x50 buffer's use unknown |
| `EntityObject` (SQLiteDriver::EntityObject) + `ColumnMap` (THashMap<const char*, int>) | 0x60 | ctor (17 buckets), dtor, Store, Fetch, Get*, the cache buffer, Serialize | `-sqlite-driver` (Find: m_stmt / m_db / m_numColumns; every column name in the map at its index (an alias too); Fetch x3 + past the end; GetInteger by index and by name, GetString, GetType; unknown name, null out; Create/Get/ClearCacheBuffer; the dtor frees the buckets) | typed; 0x00 unknown |
| `QueryParam` / `DBAddress` | 0x28 / 8 (first word) | _Execute's bind loop / DoOpen | `-sqlite-driver` | typed (the rest of QueryParam unknown) |
| `URI` | 0x100 (operator new in Downloader::Download) | Download's inlined ctor, Deserialize, DeleteBuffer, Clear | `-uri` (private, caller buffer: scheme, length, host / path / fragment with lengths, query length, the buffer halves, the converted address' port, DeleteBuffer) | typed |
| `IPAddress` | 0x88 (Clear memsets 0x88) | ctor, Clear, Get/SetPort | `-uri` (GetPort) | partly: the sockaddr bytes not mapped |
| `HttpProtocol` | 0x48 (embedded at DownloadContext + 0x18) | ctor | `-live-network` (DownloadContext::Initialize's &m_http) | typed from the ctor; meanings unknown |
| `Downloader` | 0x680 (operator new in NetworkManager::InitializeThreads) | ctor, Init, SetPath, QueryDownloadElement, Download | `-live-network` (vtables of itself / its WorkerThread / TList / sentinel / the three TDynamicQueues, m_owner, m_path = Global::m_pszDownloadContentPath, the ring capacities = Init's sizes + 1, Init's block: the free-element ring into the element block at stride 0x338, the contexts at stride 0x690 after it, QueryDownloadElement) | typed; 0x18, 0x664, 0x670 unknown |
| `DownloadElement` | 0x338 | ctor, Reset, Set, QueryDownloadElement | `-live-network` (stride, the sentinel's vtable) | partly: the embedded DownloadStream (0x190..0x30f) opaque (resource's FileStream / File) |
| `DownloadContext` + `DownloadStatus` | 0x690 / 0x160 | ctor (and Init's inlined copy), Initialize, Reset, GetDownloadStatus | `-live-network` (every context: vtable, client vtable, GetDownloadStatus = m_status under m_cs) | partly: 0x70..0x45f (the SSL record queue, client state), DownloadStatus' fields |
| `NetworkManager` + `NetworkEventMap` | 0x1b0 (last field ends there; kernel's Global allocates it) | ctor, Initialize, InitializeThreads, GetNetworkEvent, RegisterNetworkEvent, RegisterHttpRequestProcessor | `-live-network` (m_events vtable, m_thread, m_threadId = the thread's id, GetNetworkEvent(0) = the thread's event, m_httpProcessor, m_downloader) | typed; DNSCache (0xe0..0x19f) opaque |
| `NetworkManagerThread` | 0x58 (operator new) | ctor, Init, Handler | `-live-network` (both vtables, m_quit, m_taskManager, m_event, m_httpProcessor) | typed |
| `NativeHttpRequestProcessor` | 0x8d0 (operator new) | ctor | `-live-network` (the queue vtable) | partly: the queue slots and the client pool opaque |
| `NativeHttpClient` | 0x38 | ctor | - | words only |
| HttpProtocoledData, NetworkEvent (0x670), DNSCache, CookieManager (0x6e0), PaymentClient (0x30), Socket, TCP, THttpClient<TCP, 5>, TPeer, SSL | | | | not recovered (decompiles of HttpProtocoledData / HttpProtocol in http.c) |

## Natives: the SQLite driver (family `yayoi_sqlite`, 51 functions)

`Aska::Yayoi::SQLiteDriver`, its `EntityObject` and the column map's `THashMap<char const*, int,
StringHasher, StringEqualTo>` members, as members of the classes in [`yayoi_layout.h`](yayoi_layout.h),
calling the **host SQLite directly** (lib_sqlite's boundary: the handles are the host objects; databases
open on lib_sqlite's guest-path VFS so `ATTACH '<android path>'` resolves). Files:
[`yayoi_sqlite_driver.cpp`](yayoi_sqlite_driver.cpp) (SQLiteDriver), [`yayoi_entity_object.cpp`](yayoi_entity_object.cpp)
(EntityObject, Serialize), [`yayoi_column_map.cpp`](yayoi_column_map.cpp) (the map),
[`yayoi_sqlite_hooks.cpp`](yayoi_sqlite_hooks.cpp) (the HostFns: Status / struct results through x8, the
registration table), [`yayoi_sqlite_live.cpp`](yayoi_sqlite_live.cpp) (the live check),
[`yayoi_guest.cpp`](yayoi_guest.cpp) (the guest functions still called: memory's AlignedMalloc / Free,
TSharedPointerCode's counters, data_formats' ASON). `soa --list-native | grep "yayoi:"`.

| Class::Method | Notes | Live check (4 flows) |
|---|---|---|
| `SQLiteDriver::SQLiteDriver` / `~SQLiteDriver` / `Open` / `DoOpen` / `Close` | DoOpen: `m_setting`'s vtable slot 0 (guest call) when no address; reopens only for another address; "BEGIN;" when requested | 8 / 4 / 8 / 1,218 / 4 |
| `BeginTransaction` / `_BeginTransaction` / `Commit` / `Rollback` | the flags and statuses of the decompile | - / - / - / 4 |
| `Execute` / `_Execute` / `Find` / `_Prepare` | `_Prepare` clears `m_lastParams` (so only null params skip the binds); a failing prepare closes the database; no entity: one step | 1,440 / - / 2,367 / - |
| `EntityObject::EntityObject` / `~EntityObject` / `Release` / `ClearCache` / `CreateCacheBuffer` / `GetCacheBuffer` / `SerializeCache` | the map's constructor inlined (17 buckets from AlignedMalloc) | 2,370 / 2,367 / - |
| `Store` / `Fetch` | Store rebuilds the map only for another statement pointer (a reused entity keeps stale keys when SQLite reuses the address: the game makes one per query) | - (inside Find) / 1,416 |
| `GetType` (index, name) / `GetFieldLength` / `GetStringLength` / `GetTime` x2 / `GetData` x2 / `GetString` x2 / `GetTinyInt`, `GetShort`, `GetInteger`, `GetLong`, `GetFloat`, `GetDouble` (index, name) | by name: the inlined find, then operator[] (a found name can still rehash); `GetString` = `__aska_snprintf_s(out, *size, -1, "%s")` (-1 when it doesn't fit; an exact fit returns *size); `GetData` doesn't check *size | GetType(int) 1,408, GetString(int) 1,408, the rest not called |
| `Serialize` | the rows as MessagePack through a guest ASON (Init(rows * cols * 0x80, min 0x2000, C strings), MakeAValue_Array / _Map, ASON::Malloc per string, CalcSerializedSize, Serialize into `new[]`); INTEGER -> signed int from `sqlite3_value_int` (32 bits), FLOAT -> double, TEXT and BLOB -> string, NULL -> nil | 2,359 |
| `THashMap<char const*, int>`: `~THashMap` (D2, D0), `Emplace_`, `Insert_`, `Rehash_`, `Insert<THashMapIterator>` | growth: `FCVTPU((size + deleted + n) / maxLoad)` (rounded up) > count -> `Rehash_(2x + 1)`; Rehash_'s temporary takes this load only when > 0 (a NaN keeps 0.75: the guest's B.PL) | called only inside the family (and its shadow) |

Not bound: `Aska::Yayoi::EntityCache` (19 functions: only its 12-byte constructor and a RET destructor
run, from the connectors; a trap would cost more than the JIT's three stores) and
`ConnectionSet::~ConnectionSet` (a 4-byte RET). symbols.tsv: `skip`.

**Deviations** (none observable by the game): Serialize's index -> name table is host memory, zeroed
(the guest's is an uninitialised 64-entry stack array, or for > 64 columns a `MemoryManager::Malloc`
block of `Global::m_pNetworkAllocator` freed with `operator delete[]`: a mismatched free; in --selftest
a second such allocation never returns); a duplicate column name therefore gives a nil key where the
guest reads garbage; a text value is copied straight from `sqlite3_value_text` (the guest goes through
a 0x100-byte buffer regrown from the network allocator: the same bytes); ASON::Malloc running out of
memory gives `kNoMemory` (the guest returns size 0 with an uninitialised counter register).

**Differential tests** (`soa --selftest yayoi/`; the guest's functions, on the guest's SQLite 3.13.0,
vs thunks of the HostFns on the host SQLite, each side on its own objects; logs of every status,
value and object state compared, Serialize byte for byte; [`yayoi_sqlite_test_util.h`](yayoi_sqlite_test_util.h)):
- `yayoi/sqlite-driver-master` ([`yayoi_sqlite_driver_test.cpp`](yayoi_sqlite_driver_test.cpp)): the 3.7.0
  master loaded the game's way through the driver (DoOpen :memory:, ATTACH, CStaticTransaction::Progress's
  table walk, create table ... as select, DETACH), then every table whole and lib_sqlite's corpus of the
  game's queries (lib_sqlite_master.h, 3 fills per template): Find + Serialize, then a row walk with the
  typed getters by index (and by name every 7th / 97th row). 3,996 queries, 813,771 rows, 3,506
  serialized (322 MB of MessagePack): equal; ~37 s.
- `yayoi/sqlite-driver-edges` ([`yayoi_sqlite_edges_test.cpp`](yayoi_sqlite_edges_test.cpp)): a fresh
  entity, the cache buffer, Open / DoOpen through an IDriverSetting, the transaction flags, parameter
  counts, null params, a failing prepare, every getter on INTEGER (> 32 bits) / REAL / TEXT (empty, 300 B,
  70 KB, UTF-8) / BLOB / NULL by index and by name with truncating buffers, a duplicate name, Serialize
  on long texts, > 64 columns and no rows.
- `yayoi/column-map` ([`yayoi_column_map_test.cpp`](yayoi_column_map_test.cpp)): Emplace_ into a full
  table, Insert_, deleted buckets, Rehash_ (to 37, 5, 0 buckets; load -1, NaN), the range Insert, D2, D0.
- `yayoi/live-check` ([`yayoi_sqlite_live_test.cpp`](yayoi_sqlite_live_test.cpp)): the shadow run itself.

**Live check** (`soa --live-check yayoi_sqlite[:out=FILE]`, [`yayoi_sqlite_live.h`](yayoi_sqlite_live.h)):
a shadow run. Every SQLiteDriver / EntityObject the game constructs gets a shadow driven by the guest's
own code (the trampolines); each call is repeated on the shadow (the family's objects and out-buffers
swapped for the shadow's) and the status / result, the out-values (bytes), Serialize's MessagePack and
the objects' states (every field, every map bucket with its key text) must match. The shadow driver
opens its own connection through lib_sqlite's natives; inside a shadow call the guest's calls to the
family run the originals. Results (2026-10-04, the four flows of port/REBUILD-QUEUE.md, each PASS):
**0 mismatches in 16,381 checks, 0 skipped** (login 2,067, gacha 3,249, battle 5,065, story 6,000; every
database opened was `:memory:`). With the family native, nothing calls the guest's `sqlite3_*` any more
outside a shadow, so lib_sqlite's own live check sees no calls (it shadows the shadow if both are on:
don't combine them).

**Guest time** (`SOA_PROFILE` 1000 Hz, login and battle side by side, main df7dfdf vs this branch
merged with it): `yayoi` guest self 749 -> 196 samples (login 0.8% -> 0.2%, battle 0.5% -> 0.1%; what remains is
the network code); the driver inclusive (SQLiteDriver anywhere on the stack) 1,086 -> 944 (login) and
1,877 -> 1,617 (battle), -13%, now 77% / 85% native self (host SQLite and the natives; the rest is the
guest ASON calls); `QueryToMsgPack` inclusive 804 -> 653 / 1,598 -> 1,317 (-19%); the master load
(`CStaticTransaction` inclusive, ms) 3,963 -> 3,816 / 4,339 -> 3,834 (the ATTACH and table copies are
host SQLite work either way); busy samples login 38,513 -> 38,941 (noise), battle 85,020 -> 82,290 (-3%).
What Serialize still spends in guest code is data_formats' ASON (one MakeAValue_Map per row, two
ASON::Malloc per string): a native ASON (data_formats) is the next step for this path.


## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `lib_sqlite` (18,226 samples before its natives): the driver is the only caller of the SQLite C API
  (port/src/native/lib_sqlite/README.md: 20 functions, now host SQLite natives). `sqlite3*` /
  `sqlite3_stmt*` stay opaque pointers here (`m_db`, `m_stmt`); confirmed: +0x18 db, +0x20 the one live
  statement, `EntityObject::Store` keeps `sqlite3_column_name`'s pointers as the map's keys.
- `containers`: `Aska::THashMap` (the EntityObject column map, the NetworkManager event map),
  `Aska::TSharedPointer<URI>`; TList / TPoolAtomic / TQueue embedded as opaque bytes.
- `memory`: `Aska::TDynamicQueue<T, false>` (the Downloader's three rings); MemoryManagerAdapter::
  AlignedMalloc (the maps' buckets), MemoryManager::Malloc (URI buffers from Global::m_pNetworkAllocator).
- `hash`: SpookyHashV2::Hash128 (the column map's StringHasher).
- `sync`: FastCriticalSection (Downloader 0x440 / 0x4d0, DownloadContext 0x488, NetworkManager 0x30,
  NativeHttpRequestProcessor 0x838), Thread / Event / Semaphore in the worker threads: sync_layout.h's
  classes embedded.
- `kernel` (sibling, opaque here): Aska::INotify* (DownloadElement::m_notify), Aska::TaskManager*
  (NetworkManagerThread::m_taskManager), Aska::Global (m_pNetworkManager, m_pNetworkAllocator,
  m_pszDownloadContentPath).
- `resource` (sibling, opaque here): DownloadStream / Aska::FileStream / Aska::File inside DownloadElement
  (+0x190), Aska::File::DoesExist / CreateDirectory (SetPath, Download).
Upwards: `master` (the CSimpleSqliteConnector<...> per table: BuildQuery, QueryToResultObject,
QueryToMsgPack), `resource` (CGameResourceDownloader drives the Downloader), `game` (GameRPC).

## RE notes

- **Driver protocol** (docs/notes.md "Master-data loader"): `Find` = `_Execute` (`_Prepare`: finalize the
  old statement, `sqlite3_prepare_v2`, `m_prepared`, the parameter count must equal n (else -0x3ee); bind
  each QueryParam as text with SQLITE_STATIC unless the same params are already bound; no entity: step
  through SQLITE_BUSY) then `EntityObject::Store` (a new statement: column count, the name map rebuilt;
  the name pointers are SQLite's). A failing prepare *closes the database* (after ROLLBACK).
- **Statuses** (x8): 0, -1, -0x3aa no more rows, -0x3b3 not ready (no statement / not in a transaction /
  a bind failed), -0x3ee invalid argument / parameter count, -0x3ea busy, -0x3d5 open failed, -0x3c8 no
  such column (also URI::Deserialize's failed address conversion), -0x3bf no memory, -0x38f NULL value,
  -0x400 step failed (`yayoi_layout.h` `status::`).
- **Getters truncate**: `GetInteger` is `sqlite3_value_int` (32-bit), `GetString` copies through
  `__aska_snprintf_s("%s")` (cut at a NUL); NULL values give -0x38f.
- **Network at run time** (offline): NetworkManager::InitializeThreads makes the NetworkManagerThread
  (priority 0x80, stack 0x80000: wakes on its semaphore, runs its TaskManager, NetworkEvent::Run,
  NativeHttpRequestProcessor::FlushRequests) and the Downloader (Init(parallel, queue) from
  AppNetworkCommonSettingProxy; SetPath(Global::m_pszDownloadContentPath)). The Downloader's Init block
  is one new[]: (queue + 1) raw DownloadElements (built when queued; the free ring holds their
  addresses), the element ring, the finish ring, (parallel + 1) DownloadContexts (constructed in place).
- **URI quirk**: a URL with an explicit `:port` fails `Socket::ConvertIPAddrNtoB` (-0x3c8) in the
  selftest; the query's pointer lands in the work area while its length is right.

## Unknowns

SQLiteDriver 0x08 / 0x48 / 0x50 buffer; EntityObject 0x00; QueryParam 0x00..0x0f, 0x1c..; IPAddress's
bytes; DownloadElement's stream part and 0x18; DownloadContext 0x08, 0x70..0x45f, 0x478; DownloadStatus;
Downloader 0x18, 0x88 / 0x89 flags, 0x670; NetworkManager's DNSCache; NativeHttpRequestProcessor's queue /
pool; HttpProtocol's fields' meaning; HttpProtocoledData, NetworkEvent, the THttpClient / TPeer templates.

## For the code agent

Hot (self / inclusive samples over the four profiled flows, before lib_sqlite went native):
`SQLiteDriver::EntityObject::Serialize` 754 / 13,251 (the rows -> MessagePack for every master-data
miss: the yayoi hot spot; with lib_sqlite native its callees are host SQLite), `EntityObject::Store`
11 / 55, `SQLiteDriver::_Prepare` 3 / 757, `DoOpen` 6 / 51, the 170 `SQLiteDriver::BuildQuery<Connector>`
instantiations (~5 each; per-connector templates: the `master` side), `NativeHttpClient::_doRequest`
23 / 170, `THttpClient<TCP, 5>::CreateRequest` 13, `Downloader::ThreadHandler` 7 / 1,121. The driver
family is native (above, 2026-10-04); what is left of yayoi's guest time is the network code. The
driver's callers (`master`: the 170 BuildQuery<Connector> and the connectors' QueryToMsgPack /
QueryToResultObject) and Serialize's ASON calls (data_formats) are the next targets on this path.
