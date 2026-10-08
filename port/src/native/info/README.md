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
| the info classes (`CPlayerInfo`, `CPersonInfo`, ... 187) | each its own | generated: [`gen/info_classes.h`](gen/info_classes.h) ("Info classes" below) | typed, static_asserted |

## Info classes (187, generated)

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
`INFO_CONSTRUCTORS` (30 exported default constructors), `INFO_INITIALIZERS` (182). T0 `generated` reruns it
in `--check` mode.

Left to the guest: `CPlayerInfo::Initialize` (its `name` gets a default text through
`CParameterPropertyBase<53>::CryptString`), `CInfoManager::Initialize` (the manager's own), and the classes
without a layout: `CBattleLogInfo` (members of another kind after its properties), `CPartyInfo`,
`CWorldMapCellInfo` (no object of the class is built where the generator can run it).

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
| `TInfo<C>`: `C::Initialize` (182 classes: [`gen/info_classes.h`](gen/info_classes.h) `INFO_INITIALIZERS`), `C::C()` (C2, 30 classes) | [`info_class.cpp`](info_class.cpp), bound by [`info_class_bind.cpp`](info_class_bind.cpp) | `info/initialize` (every class: the guest's and the native's Initialize on objects built alike, the state compared), `info/constructors` (every exported one, on the same buffer) ([`info_class_test.cpp`](info_class_test.cpp)) | run-both on the object itself: the original after the native (a second Initialize inserts nothing new), `info_state` compared (properties, both maps relative to the object, the children's); the constructor's bytes |

**Live check** (`soa --live-check info[:every=N][:only=..][:out=FILE]`, [`info_family.h`](info_family.h)): Results (battle-gacha, `every=1`, PASS): 200,000 checks, 0 mismatches (IsExist(row) 48,281, Value(row, col)
147,768, DeserializeChild 3,951); an earlier run 201,613 / 0.

## Next (not done)

- The info classes' copy constructors (52 exported), destructors (61), `operator=` (19), move
  constructors (22): the copy copies both maps (`CSTLMap(CSTLMap const&)`, values as they are: they point
  into the source) and each child; the containers' copies copy their elements.
- `InfoBaseArray<T>::DeserializeArray` (59), `IInfoBaseMap<K, T>::DeserializeChild` (88): T's constructor,
  Initialize, DeserializeChild, the copy into the vector / node, ~T.
- `CPlayerInfo::Initialize` (the `CryptString` default), `CInfoManager`'s constructor (every info inlined:
  table-driven from the layouts) and Initialize.
- `CTimeUtility::str2time_t` (AToF, mktime; the tm_isdst quirk), `CParameterManager::Progress`,
  `CInfoManager`'s constructor (every info inlined), `StaminaUtility`.

## Dependencies

- `libcxx`: std::map (tree) layouts; `hash`: CHash32; `params`: the properties (Deserialize through their
  vtables), the string properties' list (gen/params_instantiations.inc); `data_formats`: AMap / AValue.
