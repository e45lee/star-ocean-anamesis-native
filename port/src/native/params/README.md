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
| `CHash32Ref` (stand-in for hash's `Framework::CHash32`) | 0x10 | | through every m_name above | stand-in until hash merges |

The `using` aliases at the end of the property section are the instantiations exported to Ghidra
(`port/decomp/params/types.json`).

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges:
hash 7,930, memory 2,200, libcxx 1,130 samples):
- `data_formats`: the parser's input is an `Aska::ASON` map (`AMap`, `AValue`, `ASON_Pair`): included.
- `libcxx`: string properties hold the game's `std::string` (`libcxx::String`), CocosCommonResource an
  `unordered_map` (`libcxx::hash_table`): included.
- `hash`: every property name is a `Framework::CHash32`; not merged yet, so `CHash32Ref` stands in with
  the same bytes ({vtable, u32 m_hash}, 0x10; port/n-hash-math's class). Swap it once hash merges. Nearly
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
