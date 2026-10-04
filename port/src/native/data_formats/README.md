# `data_formats`: ASON, ACSV, msgpack

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/data_formats/scope.txt`](../../../decomp/data_formats/scope.txt).
- Decompiles and the function list: [`port/decomp/data_formats/`](../../../decomp/data_formats/) (`symbols.tsv`; `tools/decomp.sh --into data_formats/<topic>`).
- Types: [`data_formats_layout.h`](data_formats_layout.h); for Ghidra, `tools/subsystem.py export-types data_formats` -> `port/decomp/data_formats/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Proven: the offsets are read on objects the guest's own code built and compared with the guest's
accessors or with the input it parsed, in `data_formats_layout_test.cpp` (`soa --selftest data_formats/`,
6 tests, all passing). "Partly" lists the fields still named padding.

| Class (guest) | Guest size | Found from (ctor, decompile) | Status / proof |
|---|---|---|---|
| `ASON` (`Aska::ASON`) | 0x90 | ctor, Init, InitMemory, Term, ClearRoot, Malloc, TemporaryMalloc/Free, DeserializeBinary; the client's lambdas keep it on the stack (0x90) | proven (`layout-ason-object`: vtables, the work blocks, Malloc's bump and growth, m_workIndex, m_temp, m_status, Term); `unk_40` unknown |
| `AValue` (`Aska::ASON::AValue`) | 0x20 | SetString, Get, AMap::Get_, MakeAValue_*, UnpackMessagePack | proven (`layout-ason-values`, `layout-ason-build`: every kind 0-9 read back from parsed msgpack; `AValue::Get`'s copy; m_dataWork / m_cstrWork) |
| `AMap` / `AArray` (`AValue::AMap` / `AArray`, the body at AValue + 8) | 0x10 | MakeAValue_Map / _Array, AMap::Get_ | proven (guest `AMap::Get_(char const*)` and `Get_(AValue const*)` return `&m_pairs[i].value` for every key) |
| `ASON_Pair` (a map entry) | 0x40 | MakeAValue_Map (n * 0x40), Get_ (pair + 0x20) | proven (as above) |
| `ASON_StringBody` / `ASON_BinaryBody` / `ASON_ValueBody` | 0x10 | SetString, AMap::Get_ cases 5, 8, 9 | proven (string, bin, ext type / size / data) |
| `ASON_WorkBufferContext` (`Aska::ASON::WorkBufferContext`) | 0x20 | InitMemory, Malloc, Term | proven (`layout-ason-object`) |
| `TDynamicArrayWorkBuffer` (`Aska::TDynamicArray<ASON::WorkBufferContext, ...>`) | 0x20 | ctor, InitMemory (reserve 4), Term | proven (vtable, begin / end / capacity) |
| `ASON_MessagePackContext` (`Aska::ASON::MessagePackContext`) | 0xa30 | DeserializeBinary (memset 0xa30, root = frame 0), UnpackMessagePack<true> | partly: m_scratch / m_pending / m_pendingLength / m_depth / the 32 frames of 0x50; a frame's bytes 0x20-0x50 except the work stamp at +0x28 unknown; not exercised by a test (stack-only object) |
| `_AsonSerializer` | 0x218 | the inlined ctor in `AsonSerializer::Serialize<CBattleLogInfo>`, Increment, Serialize_Key / _Value / _StartObject / _EndObject / _StartArray | proven (`layout-ason-serializer`: a stub on `Serialize_Key` checks vtable, m_ason, the TStack capacities, m_level / m_indices / m_map and that the key lands in `m_map->m_pairs[m_indices[m_level]]`, over the live battle log's 27 keys); `unk_00c` unknown |
| `AsonSerializer_Prepare` | 0x88 | the same inlined ctor, Increment, Serialize_Value, Serialize_EndObject | proven (`layout-ason-serializer`: a stub on `Serialize_EndObject` checks vtable, m_depth, m_levels, m_counts and the pops it makes) |
| `TStack<T, 10>` (`Aska::TStack<T, 10>`) | 0x40 (u32), 0x68 (pointers) | the inlined ctors, Increment's grow path | proven through the two serializers (capacity 10, top) |
| `TArrayU32` (`Aska::TArray<unsigned int, false>`) | 0x38 | the inlined ctors, Increment (`Resize(m_size + 1)`) | partly: m_data, m_size, m_minCapacity proven; `unk_10` / `unk_20` / `unk_30` unknown |
| `ACSV` (`Aska::ACSV`) | 0xe8 | ctor (memset 0x78 at 0x70), Init, InitMemory, AllocateMemory, Term, GetValue; CACSV's accessors | proven (`layout-acsv`: NumRows / NumColumns, the column types, every cell's value through `CACSV::Value` / `String` / `IsBlank` and `ACSV::GetValue`'s raw copy, the work memories, Term) |
| `ACSV_AValue` / `ACSV_WorkMemory` (`Aska::ACSV::AValue`, the work memory slots) | 0x10 / 0x20 | GetValue, CACSV::String, InitMemory | proven (as above) |
| `TBitArrayU32` (`Aska::TBitArray<unsigned int, false>`) | 0x28 | ACSV ctor, InitMemory | proven (vtable; the blank bit of every cell == `CACSV::IsBlank`); `unk_08` unknown |
| `CACSV` (`Framework::CACSV`) | 0xf8 | ctor, Parse, NumRows / NumColumns, Value, String, Release | proven (`layout-acsv`); `unk_f0` (0 after construction) unknown |
| `CCSV` (`Framework::CCSV`) | 0x30 | ctor, Initialize, ~CCSV, NumRows, NumElements, Element, Separator, Quote | proven (`layout-ccsv`: separator / quote writes, the rows vector, `Element` == `&rows[r][i]`, `ElementSafe` falls back to `&m_empty`) |
| `tElement` (`Framework::CCSV::tElement`) | 0x10 | ctors, Delete, Type / Value / String | proven (`layout-ccsv`: Type, Value, String per cell, both string forms) |
| `StlVector<T>` (a guest `std::__ndk1::vector`) | 0x18 | CCSV::NumRows / NumElements | proven (`layout-ccsv`) |
| `Status` (`Aska::Status`) | 8 | every Status-returning method (x8) | proven (`layout-ason-build`: MakeAValue_Map / SetString's x8 results) |

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `containers` (629 samples, same level): `Aska::TStack`, `TArray`, `TDynamicArray`, `TBitArray` are embedded
  in ASON / ACSV / the serializers: data_formats_layout.h includes containers_layout.h and names the
  instantiations (`TStack<T, 10>`, `TArrayU32`, `TDynamicArrayWorkBuffer`, `TBitArrayU32`); its static_asserts
  check the embedding offsets.
- `libcxx`: CCSV's rows are a guest `std::__ndk1::vector` (`StlVector` = libcxx_layout.h's `vector`) and its strings `basic_string` with
  `Framework::CSTLAllocator` (`native/common/guest_std.h` `guest::String`); CACSV::String returns one through x8.
- `memory` (99 samples): ASON's blocks are `operator new[]` (nothrow), its block table
  `MemoryManagerAdapter::AlignedMalloc`; CCSV's strings come from `CFixedLengthAllocatorContainer` (the STL allocator).
- `math` (172 samples): number formatting / parsing in the text forms.
- Upwards: `resource`, `yayoi`, `master`, `cocos` (`CCocosGuiReader::Read_*` walk ASON values), the client's
  API layer (`AsonSerializer::Serialize<T>` for each request; port/src/native/api/client_battle_log.cpp).

## RE notes

**ASON** is Aska's msgpack document. A value (`AValue`, 0x20 bytes) is a kind (0 nil, 1 bool, 2 uint, 3
negative int, 4 float (float32 is widened to double), 5 string, 6 array, 7 map, 8 bin, 9 ext) and a 16-byte
body at +8, plus a string's length at +0x18 and two u16 work-buffer stamps at +0x1c / +0x1e (which block
of the bump allocator holds the string's bytes / C string; Copy / Move / RelocateAValueRef use them to
rebase pointers). Strings are stored without a terminator; when the ASON was `Init(size, true)`
(`m_keepCStrings`, the 2nd argument) each string also gets a terminated copy at body + 8, which
`AMap::Get_(char const*)` needs: it compares keys with strcmp on that copy, so a document read without
C strings finds no key by name. Maps are arrays of (key, value) pairs searched linearly; `AMap` is the
body at AValue + 8, so `AMap::Get_`'s `this` is `&value.m_body.map`.

Memory: `Init(size)` new[]s one block of `size` bytes (at least 0x2000, else -0x3bd), the first 0x200
of it reserved as `m_temp` (TemporaryMalloc's scratch). `Malloc` bumps the current block (4-aligned);
when it doesn't fit it adds a block of `m_totalWorkSize` bytes (doubling) and bumps `m_workIndex`.
Nothing is freed until Term / ClearRoot / a new Deserialize (which drop all blocks but the first).

`DeserializeBinary` runs `UnpackMessagePack<false>` (scanning: counts the roots) then
`UnpackMessagePack<true>` (building); several concatenated roots become an array root with
`m_multiRoot` set. Both take a `MessagePackContext` (0xa30 bytes on the stack): the token being read,
the resumable state, and a stack of 32 frames (so documents nest at most 32 deep).

Errors are `Aska::Status` codes: -0x3bd (0xfffffffffffffc43) bad argument, -0x3bf no memory, -0x3bc not
initialized; most methods return them through x8 (the struct-return register), and store them in
`m_status` too.

**The client's serializer**: `AsonSerializer::Serialize<T>(ASON&, T&, u32 version, u64 workSize, bool)`
runs `T::Accept` twice over `_Serializer<SerializerImpl>` objects: `AsonSerializer_Prepare` counts each
object's members into a TArray (in visiting order), `_AsonSerializer` then allocates exactly that many
pairs per object (MakeAValue_Map(count)) and fills them (`Serialize_Key` writes the key of pair
`m_indices[m_level]`, `Serialize_Value` its value and advances the index). The serializer objects live
on Serialize<T>'s stack; their constructors are inlined there.

**ACSV** is Aska's typed table: per column a type (0 blank, 1 bool, 2 s8, 3 u8, 4 s16, 5 u16, 6 s32,
7 u32, 8 s64, 9 u64, 10 float, 11 double, 12 string), per cell a 16-byte value (strings as pointer +
length into the source text, not terminated), and a blank bit per cell. Cells are row-major
(`column + numColumns * row`). `CACSV::Parse` counts the columns / lines, `ACSV::Init(columns, rows, 3)`
and `DeserializeText` infer the narrowest type per column (`UnpackTextType`; "1e3" reads as a string).
**CCSV** is the plain alternative: a vector of rows of `tElement` (blank / double / a heap guest
std::string from the fixed-length STL allocator).

Unknown / not recovered: `Aska::JsonParser` (ASON's text form, `DeserializeText` / `SerializeText`;
not executed in the profiled flows), `ASON::Key` (GetValue / SetValue's key path), msgpack / picojson
(the lib has no such symbols: ASON is its own msgpack implementation), the MessagePackContext frame's
middle bytes, `ASON::unk_40`, `TArray`'s other words (the containers subsystem's).

Tooling note: `tools/decomp.sh --into` runs in parallel into the same subsystem race on symbols.tsv
(each run rewrites it; one run's rows were lost and redone); run them one after another.
