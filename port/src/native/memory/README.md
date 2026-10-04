# `memory`: the engine heaps, allocators, handles

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/memory/scope.txt`](../../../decomp/memory/scope.txt).
- Decompiles and the function list: [`port/decomp/memory/`](../../../decomp/memory/) (`symbols.tsv`; `tools/decomp.sh --into memory/<topic>`).
- Types: [`memory_layout.h`](memory_layout.h); for Ghidra, `tools/subsystem.py export-types memory` -> `port/decomp/memory/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Type recovery a wave ahead of the code (port/REBUILD-QUEUE.md: memory is wave 2). Layouts are proven by
the layout tests in [`memory_layout_test.cpp`](memory_layout_test.cpp) (`soa --selftest memory/`, all 8 pass):
private objects built and driven by the guest's own constructors and methods, or the running game's
objects walked read-only, their fields read through these classes and compared with the guest's
accessors and the invariants the decompile shows.

| Class (guest) | Guest size | Found from | Proven by (memory/layout-...) | Status |
|---|---|---|---|---|
| `MemoryManager` (Aska::MemoryManager) | 0xf0 (operator new) | ctors, InitHeap, Malloc, Remove, ~MemoryManager | `-memory-manager` (private heap: the virtual getters, Malloc / LocalFree, free lists vs srbks), `-live-managers` (the live ring) | typed; FastCriticalSection opaque |
| `MemoryBlock` (Aska::_MemoryBlock) | 0x40 header | Malloc, MallocHigh, LocalFree, LocalRegisterNotify, GetAllocatedManager, GetMemorySize | `-memory-manager` | typed (0x30: the high flag; 0x38: the registered IMemoryNotify*) |
| `MemorySrbk` (MemoryManager::_Srbk) | 0x28 | InitHeap, Malloc | `-memory-manager` (VirtualGetSrbk, run links, free bytes) | typed |
| `MemoryManagerAdapter` | static only | | | typed |
| `MemoryManagerHelper` | 0x28 | ctor, Init, InitMemoryHandleManager, dtor | `-helpers` | typed |
| `CApplicationMemory` (Framework) | 0x28 | ctor, r*/Set* | `-live-managers` (the r* getters on the live singleton) | typed |
| `CAssignedMemoryManagerForSTLAllocator` | statics | Allocate / Free / Attach* | `-live-managers` (pAttached* vs the statics) | typed |
| `IFixedLengthAllocator` | 0x08 (vtable) | the container's calls | `-live-managers` (slots 2, 3, 6, 10) | typed |
| `TFixedLengthAllocator<N>` (N = 16..512) + `FixedLengthBlockHeader` / `TFixedLengthBlock<N>` | 0x48 (operator new in CGame::OnInitialize) | ctor, pAllocate, Free, IsMine, accessors | `-fixed-length-allocator` (private pool), `-live-managers` (the six STL pools) | typed; 0x08..0x17 unknown |
| `TObjectContainer<T>` (Framework) | 0x18 | Initialize, NumElements, rElement | `-live-managers` | typed (moved here from containers: the container's base) |
| `CFixedLengthAllocatorContainer` | 0x18 (operator new) | ctor, Initialize, pAllocate, Free | `-live-managers` | typed |
| `CHandleManager_Base` (Framework) | 0x38 (rounded: the last field ends at 0x34) | ctor, Initialize, Register, Refer, Unregister, dtor | `-handle-manager` (private: Register / Refer / Unregister) | typed |
| `DeleteManager` (Aska) | 0x138 (nm -S Global::m_systemDeleteManager) | Initialize, Clear, AddMain, IsEmpty, dtor | `-delete-manager` (the live system manager's queues) | typed |
| `DeletePointerInfo` (DeleteManager::_DeletePointerInfo) | 0x18 | Initialize, AddMain | `-delete-manager` (array bounds only) | typed; fields from AddMain only |
| `TDynamicQueue<T>` (Aska::TDynamicQueue<T, false>) | 0x20 | DeleteManager's inlined queue code | `-delete-manager` | typed |
| `TSharedPointerCode` + `TSharedPointerCodePool` | 0x42c static (no symbol) | CreateCounter, DeleteCounter | `-shared-pointer-code` | typed |
| `MemoryHandleManager` (Aska) | 0x390 (ctor; no allocation site) | ctor, InitSrbk, GetBlock, IsAllocated, dtor | `-helpers` (ctor: ring fields) | partial: most of 0x009..0x1e7 unknown |
| `BadAllocateRequest` (no guest name) | 0x30 (stack) | Malloc, MallocHigh, AlignedMalloc, AlignedMallocHigh | (the natives' tests) | typed |
| `MappedMemoryManager` (Aska) | 0x468 (operator new in Global::InstantiateMappedMemoryManager) | its ctor (inlines every member's construction), dtor, RemoveHandlerEx (`mapped.c`) | `-mapped-memory-manager` (private: the ctor's eight sizes -> each member's table / pool, PointerManager / TAddressManager Register; the live one vs AppProjectDependentProxy) | typed: seven containers members (TCategorizeHash 0xa0, THash 0x90, TAddressManager 0x90), the CriticalSection opaque |

## Natives

35 natives, one family (they share the heap and pool state; `soa --list-native | grep memory:`). The guest
layout is the state: guest code that stays (Realloc, Split, Move, IsEmpty, MallocHigh, InitHeap, the
MappedMemoryManager, DeleteManager, every header reader) walks and edits the same blocks, so each native
makes the guest's stores in the guest's order (stale links included) under the guest's lock.

| Class::Method (guest symbol) | File | Differential tests | Live check (`--live-check memory`) |
|---|---|---|---|
| `MemoryManager::Malloc` | `memory_heap.cpp` | `memory/heap-differential` (+ `heap-mixed-threads`, `heap-live-check`) | dry run + shadow manager |
| `MemoryManager::AlignedMalloc` | `memory_heap.cpp` | `memory/heap-differential` | dry run + shadow manager |
| `MemoryManager::AlignedMallocHigh` | `memory_heap.cpp` | `memory/heap-differential` (incl. every run-split shape) | dry run + shadow manager |
| `MemoryManager::LocalFree(_MemoryBlock*)` | `memory_heap.cpp` | `memory/heap-differential` (incl. the IMemoryNotify path) | dry run + shadow manager (a block with a notify: skipped) |
| `MemoryManager::LocalFree(void*)` | `memory_heap.cpp` | `memory/heap-differential` | (its callee's) |
| `MemoryManager::IsCreated` | `memory_heap.cpp` | `memory/heap-differential` | getter |
| `MemoryManager::CalcFreeSize(bool)` | `memory_heap.cpp` | `memory/heap-differential` | getter |
| `MemoryManager::CalcFreeSize(long*, long*)` | `memory_heap.cpp` | `memory/heap-differential` | - (no check; 1 call per run) |
| `TFixedLengthAllocator<N>::pAllocate` (N = 16, 32, 64, 128, 192, 256, 512) | `memory_pools.cpp` | `memory/pools-differential` (with / without the CMutex) | under the pool's CMutex: native, state put back, original |
| `TFixedLengthAllocator<N>::Free` (7) | `memory_pools.cpp` | `memory/pools-differential` | same |
| `TFixedLengthAllocator<N>::IsMine` (7) | `memory_pools.cpp` | `memory/pools-differential` | getter |
| `CFixedLengthAllocatorContainer::pAllocate` / `Free` | `memory_pools.cpp` | `memory/pools-container-differential` | the chosen pool's check with the dispatcher's original |
| `CFixedLengthAllocatorContainer::IsMine` | `memory_pools.cpp` | `memory/pools-container-differential` | getter |
| `TObjectContainer<IFixedLengthAllocator*>::NumElements` | `memory_pools.cpp` | `memory/pools-container-differential` | getter |
| `CAssignedMemoryManagerForSTLAllocator::Allocate` / `Free` | `memory_pools.cpp` | `memory/pools-stl-live-check` (the live statics, every call checked) | pool path: as the container's; heap path: skipped here (Malloc / LocalFree check it) |

The tests: private heaps over host buffers (guest constructor + `InitHeap(u8*, u64)`), the same seeded
operation sequence through the guest and the natives from one snapshot, results and every byte of the
managers and heaps compared; the heap bodies count their 23 rare paths (`memory_heap.h` `HeapBranch`)
and `heap-differential` fails unless each ran. `heap-mixed-threads`: 4 native and 4 guest threads on one
heap (the lock protocol). `heap-live-check` / `pools-stl-live-check`: the live check's own code with the
guest symbols as the originals (selftest installs no natives), 0 mismatches required.

The live check (`memory_check.h`): the heap's FastCriticalSection isn't recursive and the guest's
original can't be replayed on the real heap, so with the real lock held the native body runs as a dry
run whose stores are logged (`LoggedStore`), its result, written bytes and the srbk table are recorded and
undone, and the guest's original runs on a shadow of the manager (its bytes with a free lock, a ring of
itself, no bad-allocate notify) over the same heap; the guest's stores stand. The pools' CMutex is
recursive: the check holds it, runs the native, records, puts the bytes back and runs the original.

**Lock:** `memory_lock.{h,cpp}` is the guest's inlined FastCriticalSection enter / leave on the guest's
words (the JIT's exclusive stores are host CAS, so guest and native lockers exclude each other;
`heap-mixed-threads`). It stands in for sync's `FastCriticalSection::Enter / Leave` (n-sync) until both
are on main; then the heap natives call sync's members and `memory_lock.*` goes. The pools' CMutex and
the embedded Semaphore go through the guest symbols (sync's natives once installed).

Not native (cold, or cheaper as guest code): MallocHigh (never runs in the 3.7.0 flows), Realloc / Split /
Move (rare), the 8-20-byte leaves (GetMemorySize, GetAllocatedManager, BlockSize: a native costs more
than the guest's two instructions), TSharedPointerCode (35 samples), DeleteManager::FlushMain /
PostFlushMain (557 samples: next), MemoryHandleManager, the constructors / InitHeap.

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `sync`: Aska::FastCriticalSection (0x90 bytes, embedded in MemoryManager at 0x60, DeleteManager at 0x08,
  MemoryHandleManager at 0x270 / 0x300) and Framework::CMutex (0xb0, the pools' and handle managers'
  mutex pointers). Opaque bytes / `void*` here; once n-sync's layout header is merged, swap
  `u8 m_cs[kFastCriticalSectionSize]` for its class.
- `containers`: Aska::THashMap<u32, u64> behind CHandleManager_Base::m_elements (a `void*` here).
Upwards (callers): everything allocates; `containers` and `libcxx` reach it through
Framework::CSTLAllocator -> CAssignedMemoryManagerForSTLAllocator::Allocate / Free.

## RE notes

- **The heap (Aska::MemoryManager).** First fit over 64 KiB superblocks. InitHeap(size): one operator
  new[](size + 0x10): count = (size + 0xffbe) / 0x10028 superblocks, then the srbk table
  (count * 0x28) after them (m_srbks = m_heap + m_heapSize). Each run of superblocks starts with a
  0x40-byte sentinel block (m_used = 1) heading its free list; blocks are 0x40 header + data, sizes
  16-aligned, Malloc(n) takes (n + 0x4f) & ~0xf and splits unless under 0x50 remains. The first
  allocation in a run splits the run at the next superblock boundary (a new run head). Malloc tries
  every manager of the ring (m_ringNext), then calls m_badAllocNotify (vtable slot 0 with a request
  {manager, size, 4, 0, &retries, result}). All of it under the FastCriticalSection at 0x60 (its lock
  word at 0x98 is what `Aska::MemoryManager::Malloc`'s spinning shows in the profile).
- **The managers at run time.** Global::m_pMemoryManager stays null in 3.7.0's boot;
  Global::GetAvailableMemoryManager returns the mmap'd root heap's manager (a local static at
  vaddr 0x2ccc6a0, 0x1a000000 bytes unless the app says otherwise). CApplicationMemory adds particle,
  sound and network heaps; CAssignedMemoryManagerForSTLAllocator::CreateAndAttach a 0x1c00000-byte STL
  heap. The STL allocator first tries the six fixed-length pools CGame::OnInitialize builds (tags m16,
  m32, m64, m12, m25, m51), each a TFixedLengthAllocator<N> with an index free list.
- **Handles.** CHandleManager_Base: handle = instance id << 32 | serial; the serial skips 0 and the
  reserved range; values in an Aska::THashMap<u32, u64> (open addressing, Thomas Wang's 64-bit hash
  of the serial; see Unregister in handles.c).
- **For the code agent.** Hot: MemoryManager::Malloc (3446 samples), LocalFree (1912), CalcFreeSize
  (684), DeleteManager::PostFlushMain / FlushMain, AlignedMalloc, CFixedLengthAllocatorContainer::
  pAllocate / Free, TFixedLengthAllocator<32/64>::pAllocate / IsMine. Malloc / LocalFree / the pools
  share the heap state with every guest allocation, so they move as one family (port/src/native/
  README.md "Port whole families"); the lock is sync's FastCriticalSection.
- **Unknown:** TFixedLengthAllocator 0x08..0x17, MemoryHandleManager's middle (0x009..0x1e7,
  0x200..0x217, 0x258..0x26f), BadAllocateRequest 0x18 (always 0), MappedMemoryManager's node types
  (MappedMemoryPointer / Relation / Location / Identifier, AUIDNode: only pointers to them here).
