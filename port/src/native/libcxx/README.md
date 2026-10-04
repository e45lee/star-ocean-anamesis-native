# `libcxx`: the NDK libc++ (std::__ndk1) layouts and out-of-line helpers

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/libcxx/scope.txt`](../../../decomp/libcxx/scope.txt).
- Decompiles and the function list: [`port/decomp/libcxx/`](../../../decomp/libcxx/) (`symbols.tsv`; `tools/decomp.sh --into libcxx/<topic>`).
- Types: [`libcxx_layout.h`](libcxx_layout.h); for Ghidra, `tools/subsystem.py export-types libcxx` -> `port/decomp/libcxx/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

This is the type part of the libc++ library track (port/PLAN.md task 6, "Per library": libc++ is not
hostable; the game inlines its templates and embeds `std::__ndk1` objects in its own classes, so later
natives work against the NDK layout and the hot out-of-line helpers become small natives against it).
Every layout here is proven on real guest code by `libcxx_layout_test.cpp` (`soa --selftest libcxx/`).
Natives: the shared_ptr control blocks' counters (below); live-check family `libcxx` (`--live-check libcxx`,
`libcxx_family.h`).

**The NDK's libc++ is r16b's (libc++ 6.0, `_LIBCPP_VERSION` 6000, `_LIBCPP_ABI_VERSION` 1)**, not r11c's
(1101): the lib instantiates `__libcpp_string_gets_noexcept_iterator` (in r16b's `<string>`, absent from
r11c's), and both use the `__ndk1` namespace. ABI 1 means the classic string layout (no
`_LIBCPP_ABI_ALTERNATE_STRING_LAYOUT`) and no `__value_func` in `std::function` (libc++ 8+). The headers:
`work/toolchains/android-ndk-r16b/sources/cxx-stl/llvm-libc++/include`.

## Types (classes with their methods attached)

All in `libcxx_layout.h`, namespace `soa::native::libcxx`; class templates flattened (no bases), allocator
not a parameter (the game's allocators are empty, see RE notes). Proof = a `NATIVE_TEST` in
`libcxx_layout_test.cpp` that runs the guest's own out-of-line members on objects laid out with these
structs and reads the result back through the fields (all 7 pass).

| Type | Guest size | Layout | Proof (test: guest code run) |
|---|---|---|---|
| `basic_string<C>` (`string_rep` / `string_long_rep` / `string_short_rep`) | 0x18 | long {cap\|1, size, data}; short {size<<1, chars[23]} | `libcxx/layout-string`: the game string's `insert(pos, char const*)` (short, then long), `replace`, `reserve`, `~basic_string`; NUL, capacity word odd, allocation a multiple of 16; same reads as `guest::String` |
| `vector<T>` | 0x18 | begin, end, end_cap | `libcxx/layout-vector`: `vector<String>::__push_back_slow_path<String&&>` 9x: size, capacity 1,2,4,8,16 (2x growth), elements |
| `list<T>`, `list_node<T>` | 0x18; node 0x10 + T | sentinel {prev, next}, size; node {prev, next, value} | `libcxx/layout-list`: `list<String>::emplace_back<char const*&>` 4x, walk both ways (and through `guest::StringList`), `remove(String const&)` back to empty |
| `tree<V>` (map / set), `tree_node<V>`, `tree_node_base` | 0x18; node 0x20 + V | begin_node, root (= end node's left), size; node {left, right, parent, is_black, value@0x20} | `libcxx/layout-tree`: `__tree<value_type<unsigned, IParameterProperty*>>::__emplace_unique_key_args` 300 random keys (runs `__tree_balance_after_insert`): size, in-order keys/values, begin_node = leftmost, root's parent = end node, parent links, red-black invariants; `__tree::destroy` |
| `hash_table<V>` (unordered_map / set), `hash_node<V>` | 0x28; node 0x10 + V | buckets, bucket_count, first, size, max_load_factor; node {next, hash, value} | `libcxx/layout-hash`: `unordered_map<unsigned, bool>::operator[]` 400 random keys (rehashes): returned reference = node value, hash = key, size, load factor, one list through all nodes, bucket[b] = the node before b's first, empty buckets null |
| `shared_count`, `shared_weak_count`, `shared_ptr_emplace<T>`, `shared_ptr_pointer<P>`, `shared_ptr<T>` / `weak_ptr<T>`, `unique_ptr<T>` | 0x10 / 0x18 / 0x18+T / 0x20 / 0x10 / 8 | {vtable, shared_owners, shared_weak_owners}; emplace value @0x18 | `libcxx/layout-shared-ptr`: `__add_shared`, `__add_weak`, `lock` (live and expired), `__release_shared`, `__release_weak` (both classes); `__shared_ptr_emplace<StringDBEelement, BAS_STLAllocator>`'s vtable slots 0, 1, 2, 4 = its D2, D0, `__on_zero_shared`, `__on_zero_shared_weak`. `shared_ptr` / `unique_ptr` themselves: NDK header only |
| `function`, `func<F>`, `function_base` (+ slot constants) | 0x30 (align 16); `func<function>` 0x40 | buf[32] (aligned_storage<24> has align 16), `__f_` @0x20; `__func` {vtable, F at its alignment} | `libcxx/layout-function`: `__func<function<void(bool,long)>,...>`'s vtable, all 9 slots by symbol (operator() = slot 6, +0x30); `__clone(__base*)` copies a wrapped function whose `__f_` is a heap `__func` (follows +0x30, calls slot 2 `__clone()`, which `operator new(0x40)`s), and an empty one; the copy freed by slot 5 |
| `deque<T>` | 0x30 | `__map_` split_buffer {first, begin, end, end_cap}, start, size | NDK header only (no guest object checked) |
| `pair<A, B>` | | first, second | through map / unordered_map values above |

The `using X = T<...>;` aliases at the end of the header are the instantiations exported to Ghidra
(`port/decomp/libcxx/types.json`): `String`, `VectorString`, `ListString`, `MapU32U64` (also `map<unsigned,
T*>`), `MapStringString`, `UMapU32U64`, `UMapU32Bool`, `UMapStringPtr`, the shared_ptr blocks, `FuncFunction`, ...

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `__shared_count::__add_shared` / `__release_shared`, `__shared_weak_count::__add_shared` / `__add_weak` / `__release_shared` / `__release_weak` / `lock` (7) | `libcxx_shared_count.cpp` | `libcxx/shared-count`, `libcxx/shared-weak-count` (random operation sequences on two blocks with a counting fake vtable: counts, results, slot 2 / 4 callbacks) | `libcxx`: 0 mismatches (login → home, gacha, story; `__add_weak`, `__release_weak`, `lock` not reached) |

| `basic_string<char, ..., CSTLAllocator>::__grow_by`, `__grow_by_and_replace`, `replace(pos, n1, s, n2)`, `reserve` (4) | `libcxx_string.cpp` (+ `libcxx_string.h`: replace, the inlined copy constructor / destructor for other natives) | `libcxx/string-replace-reserve` (random replaces incl. sources inside the string, reserves up and down), `libcxx/string-grow-by` | `libcxx`: 0 mismatches (login, battle, gacha, story) |

The counters are host atomics on the guest words (the JIT's exclusive store is a compare-and-swap,
runtime/src/core/cpu.cpp, so they interleave with the guest's inlined LDXR / STXR increments); the
zero-count callbacks (`__on_zero_shared`, `__on_zero_shared_weak`) are guest calls through the block's
vtable (`live::out_call`, so the live check records and replays them).

**Live-checking the counters in a multithreaded flow is unsafe:** a check's replay rewinds the control
block (its region) while other threads may change the same counts, and a lost increment / decrement
frees a block early. The battle flow with the counters checked crashed in the heap
(`MemoryManager::Malloc`); without them (`--live-check libcxx:only=basic_string`) it passes. Check the
counters only where they are mostly single-threaded (login, gacha, story above), or not at all.

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
`memory` (every `Framework::CSTLAllocator` instantiation allocates through
`Framework::CAssignedMemoryManagerForSTLAllocator::Allocate` / `Free`; the queue measured libcxx -> memory
6,655 samples). Users: nearly every subsystem embeds these types (containers, cocos, info, resource, ...).

## RE notes

- **Allocators.** `Framework::CSTLAllocator<T, Inf>` is empty: every instantiation decompiled here
  (string, vector, list, map, unordered_map nodes and buckets) calls
  `Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(size, file, line)` and `::Free(p)` directly, so a
  native frees guest STL memory with `guest::stl_free` (native/common/guest_std.h). `std::allocator` (regex,
  streams, `std::function`'s heap `__func`) uses `operator new` / `delete`.
- **Strings:** allocation = round_up(n + 1, 16) (`__recommend`), stored capacity word = allocation | 1;
  short strings hold up to 22 characters. `guest::String` / `guest::StringList` (common/guest_std.h) are the
  same objects (static_asserted in the test).
- **Copy, not move:** `vector<String>::__push_back_slow_path<String&&>` copies the source string (allocates
  a new buffer for a long one) instead of moving it: CSTLAllocator's `construct` takes `const T&`, most likely.
  A native that pushes strings must copy too (or the guest's source string keeps its buffer, as it does).
- **Counts are owners - 1** in the shared_ptr control blocks; `__release_shared` calls slot 2 when the
  count drops from 0 and then slot 4 when the weak count does (port/decomp/libcxx/shared_ptr.c). The
  counters use LDXR/STXR loops (atomic): natives need `__atomic` RMW on the same words.
- **unordered_map growth:** `operator[]` inserts when size + 1 > bucket_count * max_load_factor with
  rehash(max(2n + !pow2(n) (n > 2: 1), ceil((size + 1) / mlf))); `__rehash` picks a power of two or
  `__next_prime` (hash.c). std::hash<unsigned> is the identity; std::hash<string> is
  `__murmur2_or_cityhash<unsigned long, 64>` (0x1352ff8, not decompiled yet).

## Unknowns / not covered

- `__shared_ptr_emplace<T, A>` with the game's own allocators (`ParameterAllocator`, `BAS_STLAllocator`):
  the header assumes an empty allocator (value at 0x18); not checked on a live block.
- `deque`, `shared_ptr` / `unique_ptr` objects themselves, `basic_stringbuf` / `basic_istream` / `regex`
  (executed in the profile, from the standard library's own code): layouts from the NDK header only or
  not recovered (regex and the streams are opaque; nothing in the game embeds them in its classes as far
  as the profile shows).
- The out-of-line helpers are typed (`symbols.tsv` status `typed`), not native: `__shared_count` /
  `__shared_weak_count` (1,479 self samples, 0.4% of busy samples together, atomics) are the hottest candidates for the code
  agent, then the `__hash_table::find` / `__tree::find` instantiations (per-instantiation code: port the
  executed ones over these templates).
