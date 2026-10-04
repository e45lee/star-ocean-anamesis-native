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

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

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
- `sync` (not merged): FastCriticalSection (Downloader 0x440 / 0x4d0, DownloadContext 0x488,
  NetworkManager 0x30, NativeHttpRequestProcessor 0x838), Thread / Event / Semaphore in the worker
  threads: opaque sized arrays (`kFastCriticalSectionSize` ...), swap in sync's classes when merged.
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
family (SQLiteDriver + EntityObject: 67 functions, all decompiled in sqlite_driver.c) is small and
self-contained: port it as one family against the host SQLite directly (lib_sqlite's README), keeping
the statuses, the truncations and the column-map semantics (duplicate names: the last index wins).
