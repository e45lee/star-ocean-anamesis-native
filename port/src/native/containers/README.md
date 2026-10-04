# `containers`: the engine's containers and strings (templates)

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/containers/scope.txt`](../../../decomp/containers/scope.txt).
- Decompiles and the function list: [`port/decomp/containers/`](../../../decomp/containers/) (`symbols.tsv`; `tools/decomp.sh --into containers/<topic>`).
- Types: [`containers_layout.h`](containers_layout.h); for Ghidra, `tools/subsystem.py export-types containers` -> `port/decomp/containers/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Natives: see "Natives" below (live-check family `containers`, `containers_family.h`). Every layout marked
"proven" is checked at runtime by a `containers/layout-*` selftest in
[`containers_layout_test.cpp`](containers_layout_test.cpp): the guest's own code (its constructor, or
the constructor it inlines, then its methods) builds and fills a real object, and the host reads it
through the recovered class (`build/port/soa --selftest containers/`). Templates are declared as
class templates; the `using` aliases name the instantiations that are static_asserted and exported
to `types.json`.

| Class | Guest size | Found from (ctor, decompile) | Status |
|---|---|---|---|
| `Framework::TStaticString<N>` | N | `Set` (16, 32), `operator+=` (256) | proven: `layout-tstaticstring` |
| `Aska::StringUtility`, `Aska::PathUtil`, `Framework::CSTLStringUtility_Base<S>` | - | static helpers only | declared (statics) |
| `Aska::THashMap<K, V>` (+ `THashTable`, `THashMapBucket`, `THashMapBucketArray`, `TPair`) | 0x30 | `operator[]`, `Rehash_` (its stack temporary), `CHandleManager_Base::Initialize` | proven: `layout-thashmap` (u32 -> u64; the hash function too) |
| `Aska::THashSet<K>` | 0x30 | `Insert<>`, dtors | same table as THashMap; bucket {state, K} from `Insert` (not run) |
| `Aska::TBitArray<W>` | 0x28 | `Alloc`, the TPoolLegacy / TPoolFast dtors | proven: `layout-tbitarray` |
| `Aska::TPoolLegacy<T>` | 0x50 | `SecurePool`, `MappedMemoryManager`'s inlined construction | proven: `layout-taddressmanager` |
| `Aska::TBinaryNode<N>`, `Aska::AddressNode` | 0x28 + N | `GetKey`, `AllocNode`, `FreeNode`, `AddressNode::SetKey` / `Compare` | proven: `layout-taddressmanager` |
| `Aska::TBinaryTree<T>`, `THash<T>`, `TAddressManager<T>` | 0x90 | `AllocNode`, `FreeNode`, `FreeTable`, `Regist`, `Register`, `CalcHashValue`, the inlined construction | proven: `layout-taddressmanager` |
| `Aska::TCategorizeHash<T>` | 0xa0? | `Regist`, `Search`, `GetNext` | fields from the decompile; size not confirmed; not run |
| `Aska::TPoolFast<T>` | 0x48 | `SecurePool`, `Scoop`, dtors | proven: `layout-tpoolfast` |
| `Aska::TPoolFast<T, true>` (`TPoolFastLocked<T>`) | 0xd8 | `SecurePool` (+0xd0 owned), `Scoop` / `Sink` (the lock at +0x40: lock word +0x78, semaphore +0xb8) | proven by `containers/pool-fast-locked` (the guest's SecurePool / Scoop / Sink on it) |
| `Aska::TArray<T, B>` | 0x38 | `Resize`, dtors, the constructor inlined in `MasterNpcBaseParameterModel::GetParameter` | proven: `layout-tarray` |
| `Aska::TDynamicArray<T, A>` | 0x20 | `Insert_`, `Reserve`, dtors | proven: `layout-tdynamicarray` |
| `Aska::TStack<T, N>` | 8 + N*sizeof(T) + 0x10 | dtors, `CopyElement` | proven: `layout-tstack` |
| `Aska::TList<T>`, `Aska::LinkElement` | 0x28?, 0x18 | `Add`, `Delete` | proven: `layout-tlist` (size not confirmed) |
| `Aska::RingBuffer` | 0x38? | `Open`, `Reset`, `Close`, `Push*` / `Pop*` / `PrivatePeep*` | proven: `layout-ringbuffer` (size not confirmed) |
| `Framework::THierarchy<T>` | (base of T) | `DetachSelf`, `AddChild` | proven: `layout-thierarchy` |
| `Aska::TSharedPointer<T>` | 0x10 | `Release`, `RingBuffer::Open` | from the decompile |
| `Aska::TDelegate<T>` | 0x20 | `operator()` | from the decompile |
| `Framework::CSTLMap<K, V>` | 0x18 | the copy constructor | libc++'s `std::map` (the libcxx subsystem's layout) |
| `Aska::TPriorityQueue`, `TMultipleBuffer`, `TPoolHandler`, `TPoolAtomic*`, `TOMQuickSort`, `TArrayQuickSort` | - | | not recovered (notes at the end of the header) |

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `Aska::StringUtility::Utf8ToMultiByte` | `containers_string_utility.cpp` | `containers/utf8-to-multibyte` (random strings, every argument combination) | `containers`: 0 mismatches (login; since UnpackValue_str is native no guest code calls it in these flows) |
| `Framework::TObjectContainer<T>::NumElements` / `rElement` / `crElement` for T = `CSound::CElement`, `Collision::CollisionShapeGroup`, `IFixedLengthAllocator*`, `BehaviorQueue*` (12) | `containers_object_container.cpp` (+ `.h`: the instantiations) | `containers/object-container` (the guest's vtables, random counts / indices) | `containers`: 0 mismatches (login, battle, gacha, story) |

| `Aska::THashMap<std::string, CAssetInfo, Hasher_CSTLString>::Find_` (x8 iterator) | `containers_hash_map.cpp` | `containers/hash-map-find-asset` (hand-built tables: used / deleted / empty buckets, short and long keys, collisions, absent keys) | `containers`: 0 mismatches (4 flows) |
| `TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Descend` / `Ascend` | `containers_quick_sort.cpp` | `containers/tom-quick-sort` (random keys with many ties, random ranges: the exact order) | `containers`: 0 mismatches (4 flows; their PC-relative prologues need main's relocating trampoline, merged 2026-10-04) |
| `Framework::CSTLStringUtility_Base<std::string>::ReplaceSelf` / `Replace` (x8) | `containers_stl_string_utility.cpp` | `containers/stl-string-replace` (guest-built strings, 0..n matches, growing / shrinking, null flag) | `containers`: 0 mismatches (4 flows) |

| `Aska::TPoolFast<unsigned char[90], true>::Scoop(int)` / `Sink(T*, int)` (class `TPoolFastLocked<T>`: TPoolFast with sync's FastCriticalSection at +0x40, Enter / Leave around the bit search) | `containers_pool.cpp` | `containers/pool-fast-locked` (two guest-built pools, random scoops of 0..80 and sinks: slots, bit words, cursor, count, the lock words) | `containers`: 0 mismatches (4 flows) |

`TDynamicArray<T>::InsertFill` (`containers_dynamic_array.h`: `Insert_<TUninitializedFillN<T>>`) is a
template for other subsystems' natives (data_formats' ASON::Malloc); not bound on its own.
Find_ hashes with the hash subsystem's `hash::CHash32::Of`.

`TObjectContainer` is memory's class (`memory_layout.h`, memory's `scope.txt`); its accessors are bound
here because the containers code task took them (the hottest of the container code). Their
`symbols.tsv` rows: `port/decomp/containers/object_container.c` (the client's instantiations) and
memory's `stl_allocator.c` (`IFixedLengthAllocator*`, left untouched there).

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `memory`: storage comes from `Aska::MemoryManagerAdapter::AlignedMalloc` / `AlignedFree` (THashMap,
  THashSet, TDynamicArray), `operator new[]` / `delete[]` (TArray, the pools, TBitArray, the tree
  tables), `Framework::CAssignedMemoryManagerForSTLAllocator` (TStaticString's temporaries),
  `Aska::TSharedPointerCode` (TSharedPointer counters). `Framework::TObjectContainer` is memory's.
- `libcxx`: `CSTLMap` is `std::__ndk1::map`; `CSTLStringUtility_Base` works on the CSTL `basic_string`.
- `hash`: `Framework::CStringHash` is the hash subsystem's (left out of this scope).
- `sync`: `TPriorityQueue` holds an `Aska::CriticalSection` at +0x08.

## RE notes

Scope narrowed from the queue's proposal (`port/scripts/rebuild_queue.py` SUBSYSTEMS): `Aska::TAaf*`
(anim), `TTextCompositor` (text), `TEvent*` (kernel), `TWorkerThreadBase`, `TSoundDynamicQueue`,
`TDirectAif*` / `TTexture*` / `TEffectResourceManager` (render) and `Framework::CStringHash` (hash)
are left out; `Aska::AddressNode` (the TAddressManager node) is in. `Framework::TObjectContainer` is
in `memory`.

- **THashMap / THashSet** are open-addressing tables, not chained: buckets `{u8 state; value}` (0
  empty, 1 used, 2 deleted), linear probing `(h + i) % count`, h = Thomas Wang's 64-bit integer mix
  for integer keys (`HashInt` in the header; checked against the guest by `layout-thashmap`). They
  grow before inserting when `(size + deleted + 1) / maxLoad > count` to `2 * that + 1` buckets
  (maxLoad 0.75). Rehash_ builds a whole temporary map on the stack and swaps it in.
- **The legacy family** TPoolLegacy -> TBinaryTree -> THash -> TAddressManager / TCategorizeHash: a pool
  of nodes with a used-bit array (a full pool falls back to `operator new`), a bucket table of
  unbalanced binary search trees (node +0x18 left when `Compare(key) < 0`, +0x20 right), and a list of
  every node in allocation order (+0x08 prev, +0x10 next; tree head +0x70, tail +0x78). THash's
  CalcHashValue is FNV-1a over a C string; TAddressManager's folds the 8 key bytes
  (`h = (h % size) * 8 + byte`). A table of size 1 uses the inline slot at +0x68.
- **The guest's class hierarchy uses data-carrying bases**; the header nests the base as the first
  member `base` (standard layout), so `a.base.base.m_table` reads TAddressManager -> THash ->
  TBinaryTree's field.
- **RingBuffer** is a FIFO: PushFront writes at +0x20, PopBack reads at +0x28 (both move up); the
  other two move the positions down. PushBack on an empty buffer returns 0 (no room below 0).
- **TArray** grows to 2n (first allocation max(n, m_minCapacity = 8)); `layout-tarray` checks the
  capacity sequence 8, 18, 38.
- Unknown: TArray +0x20 (cleared with the size), TPoolLegacy +0x08, TBitArray +0x08, TPoolFast +0x40,
  THierarchy +0x20; the sizes of TCategorizeHash, TList and RingBuffer (no constructor read).
