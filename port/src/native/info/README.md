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

Left to the guest: `CPlayerInfo::Initialize` (its `name` gets a default text through
`CParameterPropertyBase<53>::CryptString`), `CInfoManager::Initialize` (the manager's own), and the classes
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
temporary for every element a list or map holds: `InfoBaseArray<T>::DeserializeArray` copies a stack T).

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `CInteroperateParameter::IsExist(row)`, `IsExist(row, col)`, `ConvertToRow`, `ConvertToColumn` (lower_bound in the hash maps), `IsValue` / `IsString` / `Value(row, col)` (ConvertToRow, then the CSV's slot on (row, col + 1)) | [`info_interoperate.cpp`](info_interoperate.cpp) | `info/interoperate` (a table the guest builds from CSV text) | run-both (the result registers) |
| `InfoBase::DeserializeChild` (each key's property gets Deserialize(map); each key's child DeserializeArray / DeserializeChild) | [`info_infobase.cpp`](info_infobase.cpp) | `info/deserialize-child` (CPersonStatusInfo), `info/deserialize-child-children` (its children: an info, a list of infos, a list of values, a number map; the whole state, the elements included) | the original rerun after the native, every property compared (infos without children only: a child's array would be appended twice; the differential test covers them) |
| `TInfo<C>`: `C::Initialize` (181 classes: [`gen/info_classes.h`](gen/info_classes.h) `INFO_INITIALIZERS`), `C::C()` (C2, 30 classes), and (`INFO_COPIES`, 169: every exported one whose containers the natives handle) the copy constructor (54), `~C` (59), `operator=` (19), the move constructor (22), `operator=(&&)` (15) | [`info_class.cpp`](info_class.cpp), bound by [`info_class_bind.cpp`](info_class_bind.cpp) | `info/initialize` (every class: the guest's and the native's Initialize on objects built alike, the state compared), `info/constructors` (every exported one, on the same buffer), `info/copies` (every copy, move, assignment and destructor on objects with random values, strings and 0-3 elements in each container) ([`info_class_test.cpp`](info_class_test.cpp)) | Initialize, the constructor: run-both on the object itself (a second Initialize inserts nothing new; `info_state` compared: properties, both maps relative to the object, the children's); the copies, moves and assignments: the original on a clone of the target / the source as they were; the destructor: the original on a clone, every byte but the maps' and strings' compared |

**Live check** (`soa --live-check info[:every=N][:only=..][:out=FILE]`, [`info_family.h`](info_family.h)): Results
(`every=1`, `only=` the info classes' natives and DeserializeChild, PASS, all 0 mismatches): battle-gacha 15,246 checks
(DeserializeChild 3,945, CAchievementInfo's destructor 4,500 and Initialize 2,700, ...), `session:home` 33,984
(CAchievementInfo's destructor 10,795 and copy 2,283, UniverseAddStatusInfo's copy 2,155, CPersonInfo's destructor
1,050 and copy 977, CPersonStatusInfo's destructor 748, ...), `session:home --lang en` 33,940. The copies compare
the two results' pointers as they are (both copies of one source keep the same ones). The CInteroperateParameter lookups (battle-gacha, `every=1`): 200,000 checks, 0 mismatches (IsExist(row) 48,281, Value(row, col)
147,768, DeserializeChild 3,951); an earlier run 201,613 / 0.

## Next (not done)

- The copies of the few infos whose containers lack what the natives need (a map without
  `__emplace_hint_unique_key_args` / `destroy` / `__assign_multi`, a vector without `assign`, an element
  without a layout): 3 symbols.
- `InfoBaseArray<T>::DeserializeArray` (59), `IInfoBaseMap<K, T>::DeserializeChild` (88): T's constructor,
  Initialize, DeserializeChild, the copy into the vector / node, ~T.
- `CPlayerInfo::Initialize` (the `CryptString` default), `CInfoManager`'s constructor (every info inlined:
  table-driven from the layouts) and Initialize.
- `CTimeUtility::str2time_t` (AToF, mktime; the tm_isdst quirk), `CParameterManager::Progress`,
  `CInfoManager`'s constructor (every info inlined), `StaminaUtility`.

## Dependencies

- `libcxx`: std::map (tree) layouts; `hash`: CHash32; `params`: the properties (Deserialize through their
  vtables), the string properties' list (gen/params_instantiations.inc); `data_formats`: AMap / AValue.
