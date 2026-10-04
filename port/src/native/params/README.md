# `params`: the parameter (de)serialization base: CParameterElementBase, CParameterParser, CParameterProperty*

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/params/scope.txt`](../../../decomp/params/scope.txt).
- Decompiles and the function list: [`port/decomp/params/`](../../../decomp/params/) (`symbols.tsv`; `tools/decomp.sh --into params/<topic>`).
- Types: [`params_layout.h`](params_layout.h); for Ghidra, `tools/subsystem.py export-types params` -> `port/decomp/params/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Type recovery a wave ahead of the code (port/REBUILD-QUEUE.md: params is wave 4); no natives yet. Every
layout is proven by a layout selftest in [`params_layout_test.cpp`](params_layout_test.cpp)
(`soa --selftest params/`, 3 tests, all pass, also in the full run): a private `CParameterPlayer` built
and deserialized by the guest from a msgpack document the test writes, private properties of each
value type deserialized by their guest instantiations, and the running game's `CocosCommonResource`
parameter walked read-only (13 elements at the selftest point). The guest's class hierarchy uses
data-carrying bases, nested as the first member `base` (as in containers_layout.h).

| Class (guest) | Guest size | Found from | Proven by (params/layout-...) | Status |
|---|---|---|---|---|
| `IParameterProperty` | 0x10 | ElementBase::AddProperty / Deserialize / PrintC; `_ZTV18IParameterProperty` | `-player` (m_next chain in AddProperty's order; slots 0-4 = the instantiation's CompareName x2, NameHash, Deserialize, PrintC) | typed |
| `CParameterPropertyBase<N>` | 0x28 | the inlined ctors in the elements' ctors, Initialize, CompareName, NameHash, CryptString | `-player`, `-live-cocos-common-resource` (m_named, m_name = guest CHash32(name), guest NameHash / CompareName on it) | typed |
| `CParameterPropertyValue<T, N, Conv>` (T = u32, s32, float, bool, u64, u8; Conv = CPropertyConverter / ...Radian) | 0x30 | Deserialize (value at +0x28), Initialize's defaults | `-player` (u32, s32), `-property-values` (float, bool, u8, u64, radian, s32; only sizeof(T) bytes written; a missing key leaves it) | typed |
| `CParameterPropertyString<N>` (S = the game's std::string) | 0x40 | Deserialize (CryptString into +0x28), the dtors | `-player` (a long name, stored XOR 42), `-live-cocos-common-resource` (keys XOR 30) | typed |
| `CPropertyConverter`, `CPropertyConverterRadian` | tags | the Radian instantiation's Deserialize | `-property-values` (v * pi / 180 in float) | typed |
| `CParameterParser` | static only | port/decomp/params/parser.c | `-player` (GetParserValue(hash) = &pair.value, 0 when absent) | typed |
| `CParameterElementBase` | 0x10 | ctor, AddProperty, Deserialize, PrintC | `-player` (vtable slots 0 / 1, m_first, the AddProperty quirk) | typed |
| `CParameterBase` | 0x08 | ctor, Find, pGetRoot, the derived ctors | `-player` (slots 2-6 on CParameterPlayer's vtable; pGetRoot, Find, pParseName) | typed |
| `CParameterPlayerElement` | 0x170 | ctor, Initialize, dtor, CParameterPlayer::CopyForMultiplay | `-player` (every property's vtable, name, default and value) | typed (example of a concrete element) |
| `CParameterPlayer` | 0x180 | ctor, Deserialize, pParameter, Initialize | `-player` (m_valid, pParameter = &m_element) | typed (example of a concrete parameter) |
| `CParameterCocosCommonResourceElement` | 0xd0 | ctor, Initialize, dtor, DeserializeParameter | `-live-cocos-common-resource` (vtable, list, names, the key) | typed |
| `CParameterCocosCommonResource` | 0x30 | ctor, Release, dtor, rParameter, Deserialize | `-live-cocos-common-resource` (unordered_map nodes: count = size, mlf 1.0, rParameter) | typed |
| `CHash32Ref` (= hash_layout.h's `Framework::CHash32`) | 0x10 | | through every m_name above | hash's class |

The `using` aliases at the end of the property section are the instantiations exported to Ghidra
(`port/decomp/params/types.json`).

## Natives

1,208 natives, one live-check family `params` (`soa --list-native | grep params:`): the parameter base
(`CParameterElementBase`, `CParameterBase`), the whole parser and every property instantiation of the lib,
bound from [`gen/params_instantiations.inc`](gen/params_instantiations.inc) (`tools/gen_params_instantiations.py`:
the dynamic symbols, each row's code checked: the value Deserialize calls its T's `GetValue<T>`,
CryptString XORs with N & 0xff, a string Deserialize calls its N's CryptString).

| Class::Method (guest symbol) | File | Differential tests | Live check (four flows) |
|---|---|---|---|
| `CParameterElementBase::Deserialize` | `params_element.cpp` | `params/element-deserialize` (random elements / maps), `params/corpus` (the flows' recorded inputs) | 503K checks, 0 mismatches |
| `CParameterElementBase::AddProperty` (the self-link quirk kept) | `params_element.cpp` | `params/element-addproperty` | 10.8M, 0 |
| `CParameterBase::pGetRoot`, `Find` | `params_element.cpp` | `params/base-getroot` | `pGetRoot` 46K, 0 (`Find` not called) |
| `CParameterParser::GetParserValue`, `GetValue(AValue const*)` | `params_parser.cpp` | `params/parser-by-hash` (also through the key-hash cache), `params/parser-double-and-string` | `only=CParameterParser` below |
| the 8 typed getters by hash (`GetValueString`, `Float`, `Int`, `UInt`, `Long`, `ULong`, `Bool`, `UTiny`) and the 8 `GetValue<T>(map, unsigned)` (T = float, int, unsigned, long, unsigned long, bool, unsigned char, char*) | `params_parser.cpp` | `params/parser-by-hash` (every kind, the conversions' edges) | `only=CParameterParser` below |
| the 8 typed getters by key, `GetValue<bool>` / `GetValue<unsigned char>(map, char const*)` | `params_parser.cpp` | `params/parser-by-key` (also the dropped messages' allocations) | `GetValueUInt` 321K, `GetValueString` 181K, 0 |
| `GetValue<std::string>` by hash and by key (x8) | `params_parser.cpp` | `params/parser-double-and-string` | `only=CParameterParser` below |
| `CParameterPropertyValue<T, N, Conv>::Deserialize` (786: T = unsigned 290, float 204 + radian 23, bool 127, unsigned long 63, int 54, unsigned char 25) | `params_property.cpp` | `params/property-values` (every instantiation x every edge value) | 6.8M, 0 |
| `CParameterPropertyString<std::string, N>::Deserialize` (194) | `params_property.cpp` | `params/property-strings` (every instantiation) | 1.9M, 0 |
| `CParameterPropertyBase<N>::CryptString<std::string>` (194) | `params_property.cpp` | `params/property-cryptstring` (every instantiation; growth, aliasing) | 439K, 0 |

Left to the guest (`symbols.tsv` status `skip`): `StringToNumber<T>` (an `istringstream`; the getters call
it for a string value), `NameHash` / `CompareName` (8-72 bytes; the natives read `m_name` of a bound vtable),
the empty `PrintC`s, the 4-byte `GetValue<T>(map, char const*)` tail branches (they land on the typed
natives). Constructors, destructors and `Initialize` of the concrete elements and parameters are typed,
not ported (the next wave's: they are the master / info classes' code).

**The n^2 lookup.** `CParameterElementBase::Deserialize` hashes the map's keys once (`KeyHashes`,
`params_parser.h`, allocation-free up to 64 keys) and lends them through a thread-local to the
`GetParserValue` calls its properties make on the same map; it reads each bound property's name once
(no `NameHash` call per key and property) and matches with a scan (<= 16 properties) or a sorted index.
The calls are the guest's in the guest's order: the first property of a name gets the key, every pair
with a string key and its C string is a call (duplicate keys too), a key of hash 0 ("" or no C string)
matches an unnamed property. A list with a property that isn't a bound instantiation, or the self link,
takes the guest's walk literally (NameHash and Deserialize through the vtable for each pair; the
self-linked list then spins as the guest does).

**Live check** (`soa --live-check params[:every=N][:budget=N][:only=..][:out=FILE][:dump]`,
`params_check.h`; a run-both family, `native/common/live_run_both.h`): the native runs for real, then the
original (the hook's trampoline): the getters on the same arguments (x0, and x1 for the 16-byte pairs); a
value property on its object as it was (the 0x30 bytes compared); CryptString, a string property and
`GetValue<std::string>` on a private copy of the destination string (same capacity: the growth calls are
the same), compared by representation; `ElementBase::Deserialize` by its sequence of property calls (the
original runs with the property natives recording instead of deserializing); `AddProperty` on a private
copy of the chain. Nested natives run unchecked inside a check, so each layer is checked with `only=`.
Results (2026-10-04, the four flows of port/REBUILD-QUEUE.md, `every=1`, each PASS, 0 mismatches, 0 races,
0 skipped): the whole family (only the outermost natives checked): 12.4M checks; `only=` the properties,
CryptString, AddProperty and CParameterBase: 20.5M; `only=CParameterParser`: 11.1M (`GetValue<unsigned>` 4.9M, `GetParserValue` and `GetValue<std::string>` 1.9M each (inside the elements' Deserialize: through the key-hash cache), `GetValue<float>` 773K, `<int>` 552K, `<bool>` 482K, `GetValueUInt(key)` 319K, `GetValueString(key)` 181K, `<unsigned char>` 22K, `<unsigned long>` 14K). Windows (soa.exe, the battle-gacha session, `every=4`): 2.0M checks, 0 mismatches. Not called in the flows: the other by-key getters, `GetValue(AValue const*)`, `Find`, the by-hash typed wrappers (the tests cover them).

## Tests

`soa --selftest params/` (14 tests, natives called directly against the guest's code): the parser on every
ASON kind and the conversions' edges (NaN, infinities, out-of-range doubles, 2^32, 2^64, strings
`StringToNumber` parses or not, no C string, an empty key, duplicate keys, keys over 12 characters); every
property instantiation; random elements and property lists; and `params/corpus`, the recorded inputs of
`CParameterElementBase::Deserialize`: `soa --live-check params:dump:out=FILE` writes every distinct input
(the element's properties with their offsets, vtables, names, values and strings, and the whole map) to
`FILE.corpus` (`params_corpus.h`); the test rebuilds each record twice in host memory and deserializes one
copy with the guest's code and one with the natives, comparing every property. The four flows recorded
479,537 distinct inputs (67 element classes, ~2 GB); all of them pass (`SOA_PARAMS_CORPUS=DIR` adds a
directory of recordings: 479,878 records with the sample, 0 mismatches, 29 s; no recorded list was self-linked). [`testdata/flows.corpus`](testdata/flows.corpus) is the committed
sample: 2 records per class and property-list shape per flow (`tools/params_corpus_sample.py`; 341 records,
66 classes, 1.3 MB; the "Player" parameter left out).

## Measurements

Guest self time (`SOA_PROFILE` at 1000 Hz, `port/scripts/rebuild_queue.py`, the four flows of
port/REBUILD-QUEUE.md, 2026-10-04): before (main a1d2854) params was 12,594 of 313,337 busy samples, **4.0%**
(`CParameterElementBase::Deserialize` 5,744, `GetParserValue` 5,599, CryptString 457, the value
Deserializes 308, string Deserializes 276, AddProperty 260; plus ~1,700 samples of the native `CHash32` it
called); after (this branch merged with main), **98 samples, 0.03%** (what is left: the concrete
elements' constructors / Initialize, typed only). The natives in its place take ~1,100 samples
(`ElementBase::Deserialize` 726, `pGetRoot` 98, CryptString ~130, AddProperty 69): about a tenth of the
guest time. Busy samples of the four flows 313,337 -> 301,961 (main also gained other natives between the
runs; fps not measured: the sessions pace the battle).

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges:
hash 7,930, memory 2,200, libcxx 1,130 samples):
- `data_formats`: the parser's input is an `Aska::ASON` map (`AMap`, `AValue`, `ASON_Pair`): included.
- `libcxx`: string properties hold the game's `std::string` (`libcxx::String`), CocosCommonResource an
  `unordered_map` (`libcxx::hash_table`): included.
- `hash`: every property name is a `Framework::CHash32`; `CHash32Ref` is hash_layout.h's class
  ({vtable, u32 m_hash}, 0x10). Nearly
  all of params' inclusive time beyond its own is `CHash32::CHash32(char const*)`.
- `memory`: string values and map nodes come from the STL allocator (`CAssignedMemoryManagerForSTLAllocator`).
Upwards (callers; interfaces only): `info`'s `CParameterManager` keeps a `std::list<CParameterBase*>`
at +0x68 (AddParameter) and calls vtable slot 4 (`Deserialize`) on each; its getters return the parts
(`pParameterPlayer` +0x40, `pParameterCocosCommonResource` +0x50, `pParameterUI` +0x58). `master`'s
`CMasterParameter*Element`s and `info`'s `InfoBaseValueArray` / `PropertyValueArray` build on the
properties and elements.

## RE notes

- **Properties.** An element (`CParameterElementBase`) embeds its properties as members; their
  constructors are inlined into the element's constructor (vtable, `m_next = 0`, `m_named = 0`,
  `CHash32()`); the element's `Initialize` (vtable slot 0) names each (`CHash32::operator=(char const*)`,
  `m_named = 1`), writes its default and links it with `AddProperty`. `Deserialize` walks the map's pairs:
  for each string key it builds `CHash32(key)` and gives the map to the first property whose `NameHash()`
  matches; that property's `Deserialize` then looks its own hash up again with
  `CParameterParser::GetValue<T>(map, hash)` -> `GetParserValue`, which hashes every key again until it
  matches. So a map of n keys costs about n^2 / 2 string hashes: this is the hot path (below).
- **N is an XOR key, not a name id.** `CParameterPropertyBase<N>::CryptString` (static) writes
  `src[i] ^ (N & 0xff)` byte by byte (via `__grow_by` as the string grows); string properties are stored
  obfuscated and read back through `CryptString` (e.g. `CParameterPlayer::CopyForMultiplay`). Numeric
  properties don't use it. 333 values of N, 786 `CParameterPropertyValue` and 194 `CParameterPropertyString`
  instantiations, all the same code modulo N and T.
- **The parser's kinds.** `GetValue<int>` (and the other integers) accept ASON kinds 2 / 3 (the low 32 bits),
  4 (the double converted) and 5 (a string parsed with `StringToNumber<T>`); other kinds return
  `{0, false}`. Results come back as `std::pair<T, bool>` in x0 (found flag at bit 32 for 4-byte T, bit 8
  for bool / u8); the string one through x8. Lookups by hash need the ASON's C strings
  (`ASON::Init(size, true)`); by name they use `AMap::Get_(char const*)`.
- **The parser's kinds, per getter** (the disassembly's conversions; `params/parser-*` runs them all): Float
  takes 2 (ucvtf: one rounding from u64), 3 (scvtf), 4 (fcvt), 5 (`atof`, the host's through the HLE); Int
  2 / 3 (low 32 bits), 4 (fcvtzs w: saturating, NaN 0), 5 (`StringToNumber<int>`); UInt the same with fcvtzu
  w, and by hash also 1 (a bool) — the by-key one doesn't take 1; Long / ULong 2 / 3 (64 bits), 4 (fcvtzs /
  fcvtzu x), 5; Bool = UInt's value, found only for 0 and 1; UTiny 2 / 3 (the low byte), 4 (fcvtzs w, then
  `(x | 0x100) & 0xffff`: the "found" byte is bits 8-15 of the int, or 1), 5; String: any kind but nil whose
  8 bytes at +0x10 aren't 0 (for an array, map or binary value that is its count as a "C string": the
  guest's `GetValue<std::string>` faults on it in strlen). A string value without its C string is not
  found. The by-key getters build "not found " / "not match " + key in a stack string and drop it (a log
  compiled out): for a key over 12 characters that allocates and frees an STL block (`__grow_by_and_replace`),
  which the natives do the same way.
- **Radian converter:** `(float)v * 3.14159274f / 180.0f`, a multiply then a divide (no FMA).
- **AddProperty quirk:** the walk compares every property but the last, so adding the last one again links
  it to itself. `CParameterPlayer::Deserialize` calls `Initialize` every time, so after a second
  Deserialize of the same object the Name property's `m_next` points to itself, and the element's
  `Deserialize` would then spin forever on a key that matches none of the seven names (a key that matches
  stops the walk). `params/layout-player` shows the self-link after a second Initialize. Whether the game
  ever deserializes one Player part twice is not checked; a native must keep the behaviour either way.
- **CParameterBase** has no data: `pParseName` (slot 3, pure) names the part's key in the parameter
  document; `pGetRoot` (slot 6) = `AMap::Get_(map, pParseName())`; the parts' `Deserialize` (slot 4)
  take the root map.
- **CocosCommonResource** keys its `unordered_map<std::string, Element>` by each element's
  `processing_priority` string (decrypted; the field name is the game's), the other two being
  `distnation_name` / `souce_name` (sic).

## Unknowns / not covered

- `CParameterUI` (35 executed functions: the UI's state, episodes, mission menu, multiplayer cache; a
  784-byte constructor), `CParameterDownload`, `CParameterSound*` (audio's scope) and the other concrete
  `CParameterX` classes: not recovered; they follow the Player / CocosCommonResource pattern.
- `Parameter::` (SignalParameter, PersonalParameter, AttackDataParameter, AttackParameter: copy
  constructors / assignments of battle data structs) is in this scope by the queue's proposal but is
  battle data, not the (de)serialization base; not recovered here; suggest moving it to `battle`.
- `CParameterPropertyBase<N>::m_named`'s readers (only Initialize writes it; nothing read it in the
  decompiles seen).
- The parser's `GetValue<char*>` / string conversions in detail (`StringToNumber<T>`).

## For the code agent

Hot (self samples over login + battle + gacha + story, 293,654 busy; params 4,283 = 1.5% self):
- `CParameterElementBase::Deserialize` 1,762 self / 15,538 inclusive, `CParameterParser::GetParserValue`
  1,301 / 8,386: the n^2 hashing above (most inclusive time is `CHash32::CHash32(char const*)`). One
  native family: ElementBase::Deserialize + GetParserValue + the 18 `GetValue<T>` (+ the 16 typed
  `GetValue*` wrappers). A native must keep the result (first matching property per key, last write wins)
  but can hash each key once.
- `CParameterElementBase::AddProperty` 274 (with its quirk), `CParameterBase::pGetRoot` 32.
- `CParameterPropertyBase<N>::CryptString` (194 instantiations, ~300 samples together; 288-292 bytes
  each, `__grow_by` per byte), `CParameterPropertyValue<T, N, Conv>::Deserialize` (786, 76-104 bytes each):
  template families; bind every instantiation from the symbol table (N from the mangled name).
