# `resource`: files, streams, the resource cache, the downloader

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/resource/scope.txt`](../../../decomp/resource/scope.txt).
- Decompiles and the function list: [`port/decomp/resource/`](../../../decomp/resource/) (`symbols.tsv`; `tools/decomp.sh --into resource/<topic>`).
- Types: [`resource_layout.h`](resource_layout.h); for Ghidra, `tools/subsystem.py export-types resource` -> `port/decomp/resource/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Type recovery only (task 6, wave 4, a wave ahead of the code agents): no natives. Every layout marked
"proven" is checked at runtime by a `resource/layout-*` selftest in
[`resource_layout_test.cpp`](resource_layout_test.cpp) (`build/port/soa --selftest resource/`): a private
object built by the guest's constructor (or the vtable + zeroes of its inlined constructor) and driven by
the guest's own methods, or the running game's object walked read-only (CResourceManager under its own
lock), its fields read through these classes and compared with the guest's accessors.

| Class (guest) | Guest size | Found from (decompile) | Proof (resource/layout-...) |
|---|---|---|---|
| `File` (Aska::File) | 0x18 | Open / Close / Read / Seek / GetFileSizeL, CFileLoader's ctor | `-streams` (a scratch file: Open wb+, Write, GetFileSizeL, Close), `-file-loader` |
| `IStream` (Aska::IStream) | 0x08 (vtable) | the stream vtables | slots used through every stream test |
| `FileStream` | 0x30 | Open / Read / Tell / IsEnd / SetLastError / dtor | `-streams` (missing-file status in m_lastError, m_swapBytes and the swapped words, Tell, GetTotalSize, Close) |
| `StaticStream` | 0x50 | Open / Read / Write / Seek / Tell / Lock / Unlock / IsEnd / dtor | `-streams` (fields after Open / Read / Lock / Unlock / SetLastError / a short read) |
| `MultiMediaStream` (+ `MultiMediaLoopParam`) | >= 0x90 (not confirmed) | Open_ / Close / Tell / GetTotalSize / IsEnd | `-streams` (Open over a StaticStream, with and without a loop; SetLastError forwarding; Close) |
| `BaseReadDevice` | 0x250 (DirectReadDevice) | InitializeSub / Initialize / GetRequest; FileReadManager | `-read-devices` (the live devices: ids, priorities, the request pool / ring / notifies arithmetic, active flag, thread) |
| `FileReadManager` | 0x278 | AddDevice / GetDevice / GetDeviceByIndex / IsEmpty / dtor | `-read-devices` (Global::m_pFileReadManager: m_direct's vtable, m_devices vs GetDeviceByIndex / GetDevice) |
| `DecompressQueue` | 0xa0 | ctor, GetSize | `-read-devices` (Global::m_pDecompressQueue: m_running, m_thread's vtable) |
| `CFileLoader` (Framework) | 0xc0 | ctor, Initialize, InitializeByDirectFile, Release, Handler, accessors | `-file-loader` (a private element: ctor fields, DummySize, EnableDirectLoad, a direct load of a scratch file through the FileReadManager: names, path, buffer, size, hash (FileNameHash through x8), Release), `-resource-manager` (live elements) |
| `CResourceElement` (+ `tMemoryDescription`, `tMappingImage`, `CFinishNotify`) | 0x150 (gpInstantiate; _Aif / _Lua 0x158) | ctor, _Initialize, Release, PhaseLoadingFinish, SwapDecompressBuffer, accessors | `-file-loader` (ctor: both vtables, the notify, type / phase), `-resource-manager` (every live element: Type / Phase / FileNumber / IsLoading / Size / the notify's owner) |
| `tElement` (CResourceManager::tElement) | 0x10 | Initialize, the counters | `-resource-manager` (ReferenceCounter / UniqueBitFlag, pSearch / pSearchByDirectPath = &node->value) |
| `CResourceManager` (Framework) | 0xf0 (operator new in CMainTask::Run) | ctor, Initialize, Run, Add, pSearch, Num, NumLoading | `-resource-manager` (CMainTask::rResourceManager = CMainTask + 0x60, vtable, m_isInitialized, the list vs Num / crResourceElementByIndex / NumLoading, the Task's level vs GetDefaultLevel) |
| `CGameResourceManager` | 0x70 (last field) | ctor, dtor, SearchFileMap, IsLoading | `-resource-manager` (pSubstance / cpSubstance, the file map's used buckets = m_size, SearchFileMap miss) |
| `CGameResourceDownloader` | 0x5e8 (last field) | ctor, the Is* / Num* accessors | `-resource-manager` (the TArray / ASON vtables, IsIdele / IsModeDownload / IsErrorStatus / IsReadyDownload(Flag) / NumDownloading vs the fields); the CFiberUnit base (kernel) opaque |
| `LocalKVS` (+ `ChaCha20State`) | 0x188 (CGameLocalKVS's operator new) | Init / SetKVSName / SetCipher / GetBinary | `-local-kvs` (a private store: Init, SetCipher with a key / nonce; Global::m_pLocalKVS) |
| `CGameLocalKVS` | 0x20 (last field) | ctor, pSubstance, Result, dtor | `-local-kvs` (the singleton: pSubstance / Result, the "Game" store encrypted) |
| `AHSLDatabase<T>` (+ `AHSLTagBucket`, `AHSLNode<T>`, `AHSLEntry<T>`) | 0x17098 | GetData, GetNodeCount, GetNodeDirect, AHSLCacheManagerV2's ctor | `-ahsl-libl` (the live L1: GetNodeCount = m_count for all 512 nodes, GetNodeDirect, GetData(key) = the entry, the bucket = the key's first 9 bits) |
| `AHSLCacheManagerV2` | members to 0x30b60 (the live AofAhslManager is larger) | ctor, Init, Tick | `-ahsl-libl` (m_l1Heap's MemoryManager vtable and heap size, m_targetConsole = s_eTC, m_frame advancing) |
| `ShaderLinkManager` (Aska) | 0x30e78 (InstantiateShaderLinkManager) | InstantiateShaderLinkManager | `-ahsl-libl` (vtable; the AofAhslManager at +8) |
| `LIBLManager` | >= 0x930 (not confirmed) | dtor, CopyTexture, Initialize | `-ahsl-libl` (sub-object vtables at 0x620 / 0x670 / 0x678 / 0x8e8 / 0x910; skipped while Global::m_pLIBLManager is null) |
| `ResourceReadyQueue` | >= 0x248 (not confirmed) | ctor, Init | `-read-devices` (vtables at 0xb0 / 0x100 / 0x138, the work buffer, 0x21c) |

Other subsystems' classes are held as sized bytes with the class named in the comment (the headers aren't
merged yet): sync's FastCriticalSection (0x90), CMutex (0xb0), Event (0x68), CriticalSection (0x28); hash's
CHash32 (`CHash32Bytes`, 0x10); kernel's Aska::Task (`TaskBytes` 0x28 / CResourceManager's inline bytes:
data size 0x27, a derived class's first byte at +0x27) and Framework::CFiberUnit (0x40). The merged
memory / containers / libcxx / data_formats classes are embedded directly (MemoryManager, THashMap,
TStaticString, TArray, TPoolLegacy, TSharedPointer, String, list, vector, ASON).

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `libcxx` (8,427 samples), `containers` (4,597), `memory` (4,494), `data_formats` (990): embedded as their
  classes (String / list / vector in CFileLoader / CResourceManager / CResourceElement; THashMap<u32,
  TStaticString<256>> in CGameResourceManager; TArray / ASON in the downloader; MemoryManager in the shader
  cache; TPoolLegacy in LIBLManager; TSharedPointer in the streams and the ready queue).
- `sync` (731): FastCriticalSection (BaseReadDevice 0x18 / 0xa8, DecompressQueue 0x08, AHSLDatabase 0x00,
  AHSLCacheManagerV2, LIBLManager 0x590), CMutex (CResourceManager 0x40, the downloader 0x170), Event,
  CriticalSection, Thread (BaseReadDevice / ResourceReadyQueue / AHSLCacheManagerV2 bases: vtable + m_thread).
  **Swap the `u8 m_x[kFastCriticalSectionSize]` etc. for n-sync's classes once sync_layout.h is merged.**
- `hash` (80): CHash32 in CFileLoader (+0xa0) and CGameResourceManager::SearchFileMap's key.
- `kernel` (co-developed, 3,444 samples resource -> kernel): Aska::Task is the base of CResourceManager (at 0)
  and CResourceElement (at +0xc0), LIBLManager's update task (+0x8e8); Framework::CFiberUnit is the
  downloader's base; Framework::CApplication::CMainTask owns the CResourceManager (+0x60,
  CMainTask::rResourceManager). Aska::INotify: CFileLoader (slot 0 Handler) and CResourceElement::CFinishNotify
  are notifies. Held opaque here: swap `TaskBytes` / `task_08` / `fiberUnit` for kernel_layout.h's classes
  at the merge (CResourceManager::m_isInitialized lives in Task's tail padding at +0x27).
- Upwards (callbacks, interfaces only): `render` (the shader cache's ShaderCache / ShaderDiskCache are opaque,
  LIBLManager's textures), `info`, `ui` (CDownloadingBar / CDownloadProgressBar: in scope, not typed).

## RE notes

- **The load path.** `CResourceManager::Add*` -> `tElement::Initialize` -> `CResourceElement::gpInstantiate(type)`
  (operator new of the subclass) -> vtable slot 7 / 8 (`Initialize` / `InitializeByDirectFile`) ->
  `_Initialize` (phase 1, `TaskManager::Add` of the element's Task part) -> `CFileLoader::Initialize*`:
  buffer = new[] / gMAllocHigh(size + dummy, align), `FileReadManager::Read(..., notify = the loader)`; the
  reader thread calls `CFileLoader::Handler` (decrypt through the static `m_DecryptFunction` std::function,
  m_isLoading = 0); the element's `Handler` runs `PhaseLoadingFinish`: a compressed buffer
  (`DecompressBase::IsCompressed`) goes to `Global::m_pDecompressQueue` with the CFinishNotify (phase 3; the
  notify swaps the buffer), else phase 4; `Run` (the Task) expands and ends at phase 9 (`Done`).
  `CResourceManager::Run` hands elements that are done and unreferenced to `CDelayDelete::AddTask(element + 0xc0)`.
- **Direct files.** m_fileNumber -2; the name kept in m_directRelativeName, read from m_directPath = folder +
  name (the folder: EnableDirectLoad's, else `gpDefalutDirectLoadRootFolder`); the asset-manager evaluation
  function (a static std::function, CGame::OnInitialize's lambda at vaddr 0x114af04, `IsAssetManagerPath`)
  decides APK asset vs file: a path with "/download/" in it is a file, the rest goes to the AAssetManager
  (so `layout-file-loader` writes its scratch file under `<Global::m_pszDownloadContentPath>download/`).
- **Status codes** (Aska::Status): -0x3bc not ready, -0x3c1 short read / range, -0x3c0 open failed, -0x3bd bad
  argument (LocalKVS::Init / SetKVSName).
- **LocalKVS** encrypts keys and values with ChaCha20 (`Aska::Cryption::TChaCha20<false>` in place at +0x100);
  without a key it derives one from `Machine::GetUniqueID` (or the MAC address) XORed into built-in strings.
- **The shader cache.** `AHSLDatabase<T, 9>`: 512 buckets by the key's first 9 bits, one-byte tags then a
  memcmp of the key from byte 2; L1 (compiled ShaderCache) at +0x30, L2 (ShaderDiskCache) at +0x198b8, the L1
  heap a private 3 MB MemoryManager. Global::m_pShaderLinkManager is a ShaderLinkManager whose AofAhslManager
  (the AHSLCacheManagerV2) is at +8. The AHSL / LIBL classes are render-side in purpose; they are typed here
  because the scope claims them (render's type agent may take them over).

## Unknowns

- MultiMediaStream: size, 0x08..0x3f (but +0x10 / +0x14), 0x78 / 0x88 / 0x8c meanings.
- BaseReadDevice: the request queue at 0x140 (a ReadRequestList; only its emptiness test read), 0x248;
  ReadRequest (0x58) and DecompressNotify (0x20) not typed; DirectReadDevice / DiscReadDevice's own fields.
- CFileLoader 0x0c, 0xb0 (set 1); CResourceElement 0xf0 / 0xf8 / 0x118, tMappingImage 0x08 / 0x28 (no live
  element had mapping images to check); StaticStream's two owned arrays (which Open variant sets them).
- CGameResourceManager 0x10..0x1f; the downloader beyond the accessors (CDownloadNode, CVerifyTask,
  CJournalFileWriter, the progress state machine's fields).
- AHSLCacheManagerV2 between the named members (the file-cache header at 0x17490, the key work area at
  0x174b0, the background-compile queue); LIBLManager below 0x590; ResourceReadyQueue's EvItem / TEventQueue.
- Not recovered: DiscReadStream, StreamingStream (+ WorkerThread, BufferingNotify), DecompressThread's own
  layout (beyond the ring words GetSize reads), DecodeTextureQueue / DecodeJpegObject, MappedResourceFilter,
  CPhase_DataDownload, CGameDataDownload*, CDownloadingBar / CDownloadProgressBar, CAssetInfo, Aska::ResourceManager.

## For the code agent

Hot guest functions (self samples over the four profiled flows, port/REBUILD-QUEUE.md; 3,289 self in all):
`LIBLManager::CopyTexture` 427, `CResourceManager::Run` 356 (incl. 533), `AHSLCacheManagerV2::SearchBindedVS` 117,
`AHSLCacheManagerV2::Init` 104, `AHSLDatabase<ShaderCache, 9>::GetData` 101, `CResourceManager::IsReadyDirectFile`
95 (263), `CGameResourceDownloader::Progress` 79 (incl. 6,571), `LocalKVS::GetBinary` 76, `CVerifyTask::
ProgressLocalFileCheck` 72, `AHSLCacheManagerV2::SearchOrCompile` 66, `MultiMediaStream::IsBufferingReady` 65,
`CPhase_DataDownload::Progress` 57, `MultiMediaStream::IsBufferingEnd` 50, `StreamingStream::IsReady` 49,
`BaseReadDevice::Read` 43, `AHSLDatabase<ShaderDiskCache, 9>::SetData` 41, `CGameResourceManager::ReplaceFileName` 36,
`AHSLDatabase<ShaderDiskCache, 9>::GetData` 36, `BaseReadDevice::Handler` 33 (2,776), `CFileLoader::pFileName` 31,
`BaseReadDevice::GetRequest` 29, `StaticStream::Tell` 28.
Good first natives over these classes: the CResourceManager list walks (`IsReadyDirectFile`, `pSearch*`,
`NumLoading`, `IsLoading`, `crResourceElement*`: under m_mutex, i.e. sync's CMutex natives first), the
AHSLDatabase lookups (`GetData`, both instantiations: the FastCriticalSection from sync), the StaticStream /
MultiMediaStream leaves (`Tell`, `IsReady`, `IsBufferingReady`, `IsBufferingEnd`, `Lock` / `Unlock`), the
CFileLoader / CResourceElement accessors. `LIBLManager::CopyTexture` (3.2 KB, under its FastCriticalSection)
is render-heavy; `CGameResourceDownloader::Progress*` is large (Progress_Setup 21 KB) and mostly waits.
