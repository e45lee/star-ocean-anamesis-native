# `memory`: the engine heaps, allocators, handles

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/memory/scope.txt`](../../../decomp/memory/scope.txt).
- Decompiles and the function list: [`port/decomp/memory/`](../../../decomp/memory/) (`symbols.tsv`; `tools/decomp.sh --into memory/<topic>`).
- Types: [`memory_layout.h`](memory_layout.h); for Ghidra, `tools/subsystem.py export-types memory` -> `port/decomp/memory/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Type recovery a wave ahead of the code (port/REBUILD-QUEUE.md: memory is wave 2). Layouts are proven by
the layout tests in [`memory_layout_test.cpp`](memory_layout_test.cpp) (`soa --selftest memory/`, all 7 pass):
private objects built and driven by the guest's own constructors and methods, or the running game's
objects walked read-only, their fields read through these classes and compared with the guest's
accessors and the invariants the decompile shows.

| Class (guest) | Guest size | Found from | Proven by (memory/layout-...) | Status |
|---|---|---|---|---|
| `MemoryManager` (Aska::MemoryManager) | 0xf0 (operator new) | ctors, InitHeap, Malloc, Remove, ~MemoryManager | `-memory-manager` (private heap: the virtual getters, Malloc / LocalFree, free lists vs srbks), `-live-managers` (the live ring) | typed; FastCriticalSection opaque |
| `MemoryBlock` (Aska::_MemoryBlock) | 0x40 header | Malloc, LocalFree, GetAllocatedManager, GetMemorySize | `-memory-manager` | typed; 0x30 / 0x38 meaning unknown |
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
| Aska::MappedMemoryManager (0x468, operator new in Global::InstantiateMappedMemoryManager) | | | | not recovered (the AFF mapping tables; resource's side) |

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

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
- **Unknown:** MemoryBlock 0x30 and 0x38 (written 0 on allocation), TFixedLengthAllocator 0x08..0x17,
  MemoryHandleManager's middle (0x009..0x1e7, 0x200..0x217, 0x258..0x26f), MappedMemoryManager
  (not recovered), the bad-allocate request struct's fields beyond the decompile.
