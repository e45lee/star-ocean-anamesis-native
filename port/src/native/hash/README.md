# `hash`: Hashes: CHash32, SpookyHash V2, SHA-1, CRC, UTF-8

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/hash/scope.txt`](../../../decomp/hash/scope.txt):
  `Framework::CHash32`, `Aska::Hash`, `Aska::detail::SpookyHashV2`, `Aska::Utf8`, `Framework::CStringHash`
  (the containers subsystem left it to this one; decompiled, not ported yet). The queue's proposal
  (`port/scripts/rebuild_queue.py`) also took the whole `Aska::detail` family (DirectAofPrimitiveImpl,
  AnimationGroup, FontManager, SmallHeap: scene, text and memory code) and `Aska::Cryption` (ChaCha20,
  RSA, BigNumber: crypto, 13 samples); neither scope.txt nor (since this branch) the proposal's `hash`
  line claims them.
- Decompiles and the function list: [`port/decomp/hash/`](../../../decomp/hash/) (`symbols.tsv`; `tools/decomp.sh --into hash/<topic>`).
- Types: [`hash_layout.h`](hash_layout.h); for Ghidra, `tools/subsystem.py export-types hash` -> `port/decomp/hash/types.json`.
- Build settings of its own: none ([`subsystem.cmake`](subsystem.cmake)).

## Types (classes with their methods attached)

| Class | Guest size | Found from (ctor, decompile) | Status |
|---|---|---|---|
| `Framework::CHash32` | 0x10 | its constructors (`chash32.c`): vptr at 0, the hash at 8 | typed, all members native |
| `Aska::detail::SpookyHashV2` | 0x130 | Init / Update / Final (`spooky.c`) = Bob Jenkins' reference class | typed, native |
| `GuestString` = `libcxx::String` (the game's `std::string`) | 0x18 | the libcxx subsystem's layout (`native/libcxx/libcxx_layout.h`) | used by CHash32's string overloads |
| `Aska::Hash`, `Aska::Utf8` | - | free functions (namespaces here; the mangling can't tell a namespace from a class of statics) | native |

**What other subsystems can rely on:** `CHash32::Of(s, n)` / `OfCString(s)` are the game's name hash
(resource, parameter and master ids are these values; `params` calls it 7,930 samples' worth in the
profile); `CHash32` is the 16-byte guest object; `SpookyHashV2` the 0x130-byte state.

## Natives

All are registered through the live-check family `hash` (`hash_family.cpp`, `native/common/live_leaf.h`):
`soa --live-check hash[:every=N]`. Differential tests: `soa --selftest hash/` (random inputs, edge
cases, and real inputs: the 3.7.0 download's paths and file bytes).

| Class::Method (guest symbol) | File | Differential tests | Live check (login, battle, gacha, story) |
|---|---|---|---|
| `CHash32::CHash32()`, `(char const*)`, `(char const*, unsigned long)`, `(std::string const&)`, `(unsigned int)`, `(int)` | `hash_chash32.cpp` | `hash/chash32`, `hash/chash32-numbers` | `(char const*)`: 179M checks, 0 mismatches; the others not called |
| `CHash32::Get`, `operator unsigned int`, `==`, `!=`, `<`, `>` (CHash32 / unsigned / char const* overloads) | `hash_chash32.cpp` | `hash/chash32`, `hash/chash32-numbers` | `Get`, `unsigned int`, both `==`: 573M checks, 0 mismatches; the others not called |
| `CHash32::operator=(char const*)`, `operator=(std::string const&)` | `hash_chash32.cpp` | `hash/chash32` | `(char const*)`: 11M checks, 0 mismatches |
| `SpookyHashV2::Short`, `Hash128` (static) | `hash_spooky.cpp` | `hash/spooky-short` | `Hash128`: 1.7M checks, 0 mismatches (`Short` is reached from it natively) |
| `SpookyHashV2::Init`, `Update`, `Final` | `hash_spooky.cpp` | `hash/spooky-stream` | not called |
| `Aska::Hash::SHA1(char const*, unsigned long, char*, unsigned long, char*, unsigned long)` | `hash_digest.cpp` | `hash/sha1` | 36 checks, 0 mismatches |
| `Aska::Hash::CRC(unsigned char const*, unsigned long, unsigned short*)`, `(…, unsigned int*)` | `hash_digest.cpp` | `hash/crc`, `hash/tables` | not called |
| `Aska::Utf8::GetByteSizeAt_`, `ToUcs4`, `ToUcs2` | `hash_utf8.cpp` | `hash/utf8` | `ToUcs4`: 822K checks, 0 mismatches |

**The final run** (with `math`, every call checked): login 171M checks, battle 193M, gacha 202M,
story 198M: 0 mismatches, 0 races.

31 natives. Left to the guest (`symbols.tsv` status `skip`): the 4-byte destructors (too small to
hook), `SpookyHashV2::Mix` (only called by Hash128 / Update / Final), and `MD5`, the HMACs, `RSA_SHA1`
and the `IStream` variants (not executed in the profiled flows).

## Dependencies

Types: `libcxx::String` (the libcxx subsystem's string layout). Functions: none (level 0). The natives call no other guest code (`CHash32::operator=(nullptr)` calls the guest's
`Framework::gDoAssert` before faulting, as the original does).

## RE notes

- **CHash32** is a table CRC-32 (zlib's table, reflected 0xEDB88320; the guest's copy at vaddr
  0x2863e48) seeded with the string's length (its low 32 bits) and without the final xor; an empty or
  null string hashes to 0. The same function is `soa::chash32` (common/include/soa/chash32.h).
  `CHash32(unsigned int)` and `CHash32(int)` hash the number printed with `"%u"` (so -1 hashes
  "4294967295"). The constructors' C1 / C2 symbols are one function at one address.
- **Quirk:** `operator<(unsigned int const&)` returns `value < hash` and `operator>(unsigned int const&)`
  `hash < value`: the reverse of their names and of the CHash32 overloads. Kept.
- **CRC:** `CRC(…, unsigned short*)` is CRC-16/X-25 (reflected 0x8408, init and final xor 0xffff; table
  at 0x2872808), `CRC(…, unsigned int*)` zlib's CRC-32 (table at 0x2872a08); both write 0 for empty or
  null data and return the CRC's size. The loop counter is 32-bit in the guest (wraps past 4 GiB; not
  reproduced). `hash/tables` compares all three tables with the guest's bytes.
- **SHA1** pads the message in the caller's `work` buffer (it stays there) and needs `outlen >= 20`
  and `worklen >= ((len + 0x41) & ~0x3f) + 0x40`, else returns 0; the digest is big-endian.
- **SpookyHashV2** is Bob Jenkins' V2 reference (public domain) built with unaligned reads allowed
  (no copy to an aligned buffer); `Final` leaves its zero padding in `m_data`.
- **Utf8:** an invalid lead byte (a continuation byte, 0xf8-0xff) is copied as one code unit; a 4-byte
  sequence reads its continuation bytes unchecked (also past a NUL), and `ToUcs2` stores its lead byte.
- **CStringHash** (`port/decomp/hash/cstringhash.c`): a string-interning table (`CSubstance`) built on
  the containers' templates `Aska::THash`, `TBinaryTree` and `TPoolLegacy` instantiated for
  `CStringHash::tElement` (their rows in `symbols.tsv` are `skip` here: containers owns `Aska::T*<>`). Not ported in
  wave 0 (it needs the containers' template natives first).
- **Floating point:** none here. (The whole 3.7.0 lib has no fused multiply-add instruction: see
  `math`'s README.)
- **Guest time** (SOA_PROFILE at 1000 Hz, guest self samples of this scope; the task-5 profile and
  one before / after pair per flow on the same machine and load, `perf.py`-style over
  `port/scripts/profile_report.py`'s tables): task 5's four flows: 9,927 of 359,202 busy samples
  (2.76%; `CHash32::CHash32(char const*)` alone 8,158; the queue's 10,695 / 3.0% included the
  `Aska::detail` classes above). Before -> after: login 2,274 (4.54% of busy) -> 21 guest + 625
  native (`CHash32(char const*)` 403, `SHA1` 181); battle 2,548 (2.59%) -> 19 guest + 684 native.
  The rest of a native call is the trap into the host (`SVC`) and back. `CStringHash` runs (15-20
  functions executed per flow) but is cold (about 5 samples per flow).
