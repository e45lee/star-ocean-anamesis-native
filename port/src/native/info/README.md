# `info`: the client's info objects and parameter manager (player, roster, missions)

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/info/scope.txt`](../../../decomp/info/scope.txt).
- Decompiles and the function list: [`port/decomp/info/`](../../../decomp/info/) (`symbols.tsv`; `tools/decomp.sh --into info/<topic>`).
- Types: [`info_layout.h`](info_layout.h); for Ghidra, `tools/subsystem.py export-types info` -> `port/decomp/info/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

| Class (guest) | Guest size | Found from | Status |
|---|---|---|---|
| `Framework::CInteroperateParameter` | 0x28 | constructor, Release, Initialize, InitializeCommon, IsExist, ConvertToRow / Column (port/decomp/info/interoperate.c) | typed; 0x20 unknown |
| `NameIndexMap` (std::map<unsigned, unsigned long>) | 0x18 | the row / column hashes | libcxx's tree |
| `InfoBase` | 0x38 | the constructors, Initialize, DeserializeChild (port/decomp/info/person_status.c) | typed (the base) |
| `InfoContainer` (InfoBaseArray<T>, IInfoBaseMap<K, T>, InfoBaseValueArray<T, P>) | 0x50 | the vmi typeinfos (InfoBase, then a CSTLVector / CSTLMap at +0x38), the constructors in CInfoManager's | typed (generic); 210 container classes in the generated header |
| the info classes (`CPlayerInfo`, `CPersonInfo`, ... 186) | each its own | generated: [`gen/info_classes.h`](gen/info_classes.h) ("Info classes" below) | typed, static_asserted |

## Info classes (186, generated)

Every class derived from InfoBase (by its typeinfo: 741 with the containers and templates) is an
InfoBase, its properties (params_layout.h) and its children, embedded: infos, or containers (0x50: an
InfoBase and a CSTLVector or CSTLMap). The constructors are inlined almost everywhere, so
[`tools/gen_infos.py`](../../../../tools/gen_infos.py) reads the layouts from objects the lib builds, under
unicorn ([`tools/uemu.py`](../../../../tools/uemu.py)): CInfoManager's constructor (every info the client
keeps), each exported default constructor, each `InfoBaseArray<T>::DeserializeArray` on a one-element array
(its T on the stack) and each `IInfoBaseMap<K, T>::DeserializeChild` on a one-pair map (its T copied into
the new node). Each object is walked from its vtable (the properties by their vtables, a child by its
class's); every reading of a class must agree. Initialize runs on a probe (every word of the object a fake
vtable that records its calls): its steps must be the one shape the natives implement (per property:
`m_name = key`, `m_named = 1`, at most one store of the default, as wide as the value, then the property
map's `__emplace_unique_key_args(NameHash(), property)`; per child: `pParseName()`, `CHash32` of it, the child
map's `__emplace_unique_impl`, the child's Initialize) and name only the layout's properties and children.
Which children an Initialize registers tells the walk a child from a sibling that follows; a property after
the last one Initialize names is another object's. `NameHash()` is checked to be the hash read (every
`CParameterPropertyBase<N>::NameHash` is `add x0, x0, #0x18` and a tail call of one `ldr w0, [x0, #8]`), so
the natives read `m_name`'s hash. The output: per class a typed layout (child members named by the child
class's `pParseName()`), its property, child and Initialize-step tables, and `INFO_CLASSES`,
`INFO_CONSTRUCTORS` (30 exported default constructors), `INFO_COPIES` (126), `INFO_INITIALIZERS` (181). T0 `generated` reruns it
in `--check` mode.

`CInfoManager` (an InfoBase whose 226 children are every info the client keeps) has no layout (its other
members aren't read); its Initialize's steps are taken as they are (three stores to members of another kind, 43
properties, 226 children: `InfoStep::kStore` besides the property and child steps), so its Initialize is native too.

Left to the guest: `CPlayerInfo::Initialize` (its `name` gets a default text through
`CParameterPropertyBase<53>::CryptString`), and the classes
without a layout: `CBattleLogInfo`, `CCharacterDecoSendInfo` (members of another kind after their properties),
`CPartyInfo`, `CWorldMapCellInfo` (no object of the class is built where the generator can run it).

Containers (the copies, `info_class.cpp`): a vector (InfoBaseArray<T>, InfoBaseValueArray) is copied natively
(`Allocate(bytes, "...STL_Vector.h", 0x20)`, each element's copy) and taken by the move constructor (the three
words; the source's left 0); a map (IInfoBaseMap<K, T>) is copied by the move constructor too (CSTLMap
declares a copy constructor), element by element through the guest's `__emplace_hint_unique_key_args(end(),
key, pair)`; both assignments (the move assignment too) call the guest's `vector::assign(first, last)` /
`__tree::__assign_multi`; the destructor destroys a vector's elements from the last and frees its storage, a
map's nodes by the guest's `__tree::destroy`. The generator names each container's functions and leaves out a
copy whose containers lack one.

Sizes: where the lib's code uses a class's sizeof (a vector's first storage in `InfoBaseArray<T>::DeserializeArray`,
a map node in `IInfoBaseMap<K, T>::DeserializeChild`), it must be where the properties and children end, or more:
then the rest is plain data nothing the generator runs writes (`CPersonStatusInfo`'s last 0x10 bytes, after its
`AddBuffByDeityCharacter` child: its copy constructor copies them as two words), a `m_tail` the copies copy. Each
exported destructor and copy constructor runs on an object built from the layout and may not write past it
(`CCharacterDecoSendInfo`'s destructor deletes an array at +0xc8: left to the guest).

Quirks kept: `CPresentBoxReceiveInfo`'s child at +0x1d8 (`CPresentBoxReceiveDecoInfoList`) is never
initialized nor registered by its Initialize; `AddBuffByDeityCharacter` (a child of `CPersonStatusInfo`)
inherits `UniverseDeityBoostInfo`'s `pParseName`, so the child map keeps only the first of the two (a
unique emplace); a copied info's maps (and m_next) point into the object it was copied from (a dead
temporary for every element a list holds: `InfoBaseArray<T>::DeserializeArray` copies an initialized stack T).

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `CInteroperateParameter::IsExist(row)`, `IsExist(row, col)`, `ConvertToRow`, `ConvertToColumn` (lower_bound in the hash maps), `IsValue` / `IsString` / `Value(row, col)` (ConvertToRow, then the CSV's slot on (row, col + 1)) | [`info_interoperate.cpp`](info_interoperate.cpp) | `info/interoperate` (a table the guest builds from CSV text) | run-both (the result registers) |
| `InfoBase::DeserializeChild` (each key's property gets Deserialize(map); each key's child DeserializeArray / DeserializeChild) | [`info_infobase.cpp`](info_infobase.cpp) | `info/deserialize-child` (CPersonStatusInfo), `info/deserialize-child-children` (its children: an info, a list of infos, a list of values, a number map; the whole state, the elements included) | the original rerun after the native, every property compared (infos without children only: a child's array would be appended twice; the differential test covers them) |
| `TInfo<C>`: `C::Initialize` (182 classes, CInfoManager's included: [`gen/info_classes.h`](gen/info_classes.h) `INFO_INITIALIZERS`), `C::C()` (C2, 30 classes), and (`INFO_COPIES`, 169: every exported one whose containers the natives handle) the copy constructor (54), `~C` (59), `operator=` (19), the move constructor (22), `operator=(&&)` (15) | [`info_class.cpp`](info_class.cpp), bound by [`info_class_bind.cpp`](info_class_bind.cpp) | `info/initialize` (every class: the guest's and the native's Initialize on objects built alike, the state compared), `info/initialize-manager` (two managers from the guest's constructor: the steps' state and every known child's), `info/constructors` (every exported one, on the same buffer), `info/copies` (every copy, move, assignment and destructor on objects with random values, strings and 0-3 elements in each container) ([`info_class_test.cpp`](info_class_test.cpp)) | Initialize, the constructor: run-both on the object itself (a second Initialize inserts nothing new; `info_state` compared: properties, both maps relative to the object, the children's); the copies, moves and assignments: the original on a clone of the target / the source as they were; the destructor: the original on a clone, every byte but the maps' and strings' compared |
| `CTimeUtility::str2time_t` (the separators, the 64-byte copy split in place, each field through the guest's `CSTLStringUtility_Base::AToF` on a std::string temporary and FCVTZS, then the runtime's `mktime` through the lib's mktime@plt: platform370's local time and `--no-dst-fix` apply as to the guest's call; a time asked for with fewer than six fields (the guest reads uninitialised slots) or a text of 64 bytes or more: the original) | [`info_time.cpp`](info_time.cpp) | `info/str2time` (26 texts x the 4 flag pairs) | the original after the native, the results compared |

**Live check** (`soa --live-check info[:every=N][:only=..][:out=FILE]`, [`info_family.h`](info_family.h)): Results
(`every=1`, `only=` the info classes' natives and DeserializeChild, PASS, all 0 mismatches): battle-gacha 15,246 checks
(DeserializeChild 3,945, CAchievementInfo's destructor 4,500 and Initialize 2,700, ...), `session:home` 33,984
(CAchievementInfo's destructor 10,795 and copy 2,283, UniverseAddStatusInfo's copy 2,155, CPersonInfo's destructor
1,050 and copy 977, CPersonStatusInfo's destructor 748, ...), `session:home --lang en` 33,940; with `str2time` and CInfoManager's Initialize: battle-gacha 29,381 (str2time_t 14,203),
`session:home` 84,169 (str2time_t 50,253), `--lang en` 83,325. The copies compare
the two results' pointers as they are (both copies of one source keep the same ones). The CInteroperateParameter lookups (battle-gacha, `every=1`): 200,000 checks, 0 mismatches (IsExist(row) 48,281, Value(row, col)
147,768, DeserializeChild 3,951); an earlier run 201,613 / 0.

## Measurements

Guest self time (`SOA_PROFILE` 1000 Hz, `port/scripts/rebuild_queue.py`, the login + battle flows: before = n-master's
profile at the start of this work, after = this branch at 0e31f81, 2026-10-08): `info` **998 samples (1.1%) -> 306
(0.7%)**; executed functions 783 -> 651, executed bytes 438K -> 248K. By kind (the generic natives' families): the
infos' Initialize 227 -> 11 (CInfoManager's included), copies 83 -> 8, constructors 63 -> 4, destructors 50 -> 9,
assignments 18 -> 0, moves 8 -> 0, `str2time_t` 43 -> 0. What is left: `CInfoManager`'s constructor (32),
`CCharacterData`'s constructor (32), `InfoBaseArray` / `IInfoBaseMap` deserialization (30), `CParameterManager::Progress`
(18), `StaminaUtility::FindGlobalNumberWithKey` (16), `CParameterManager::ClearMasterCache` (11). (The two runs'
guest totals differ, 46,157 and 18,429 samples: other subsystems went native in between.)

## Next (not done)

- The copies of the few infos whose containers lack what the natives need (a map without
  `__emplace_hint_unique_key_args` / `destroy` / `__assign_multi`, a vector without `assign`, an element
  without a layout): 3 symbols.
- `CPlayerInfo::Initialize` (the `CryptString` default); `CInfoManager`'s constructor (32 KB: every info
  inlined, and members of other subsystems: the C2S lists, `CBattleLogInfo`; the infos' part is
  `InfoCode::Ctor` of the layouts, the rest isn't read).
- `InfoBaseArray<T>::DeserializeArray` (59): T is built, initialized and deserialized on the guest's stack and
  copied into the vector, whose element's maps then point into that dead frame (the copy quirk). A native's
  temporary would be host memory, and a later write through those pointers must not land in freed host
  memory: left to the guest until the temporary can live where the guest's did.
  `IInfoBaseMap<K, T>::DeserializeChild` (88) copies a temporary that isn't initialized (empty maps; the
  node's own Initialize registers its own properties, test `info/deserialize-child-children`): no such hazard,
  the next candidate (its tree insert is inline: find, `__construct_node`, `__tree_balance_after_insert`).
- `CCharacterData` (the battle character's data: 141 properties, PropertyValueArrays, Initialize inlined into
  its constructor), `StaminaUtility` (master_global lookups through `ParameterByQuery`, `CryptString`, atoi),
  `CParameterManager::Progress` (its time is in its callees).

## Dependencies

- `libcxx`: std::map (tree) layouts; `hash`: CHash32; `params`: the properties (Deserialize through their
  vtables), the string properties' list (gen/params_instantiations.inc); `data_formats`: AMap / AValue.
