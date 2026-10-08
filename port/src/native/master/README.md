# `master`: master data: the SQLite connectors, the master parameter tables, StringDB, CMasterManager / CMasterCache

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/master/scope.txt`](../../../decomp/master/scope.txt)
  (`CSimpleSqliteConnector<...>`, `CMaster*` but not `CMastery*` (the mastery UI), `StringDB*`).
- Decompiles and the function list: [`port/decomp/master/`](../../../decomp/master/) (`symbols.tsv`; `tools/decomp.sh --into master/<topic>`).
- Types: [`master_layout.h`](master_layout.h) and the generated [`gen/master_elements.h`](gen/master_elements.h);
  for Ghidra, `tools/subsystem.py export-types master` -> `port/decomp/master/types.json`.
- Build settings of its own: none.

## How the master data is read (RE notes)

A table of the master (`basmaster.sqlite3`, copied into an in-memory database by `CStaticTransaction`)
is read through three layers, each a template over the table:
- `CSimpleSqliteConnector<MasterDB::CX, TEntity_Slave<SQLiteDriver, CX, NoCache>>` (170): the SQL. Its
  `CLocalEntity<CX>::GetQuery(int)` statics hold the table's queries (`__TABLE_NAME__` replaced by
  `SQLiteDriver::BuildQuery<CLocalEntity>`, yayoi's scope) and `GetPrimaryKeies()` its keys;
  `QueryToMsgPack` runs one (under `CStaticTransaction`'s mutex) and serializes the rows
  (`EntityObject::Serialize`, yayoi) as MessagePack.
- `CMasterParameterBaseSqlite_Simple<T>` (159) / `_Category<T>` (7): the caches (an unordered_map of
  `shared_ptr<T>` per use) and the lookups (`pParameterFromHash(id)`, `ParameterByQuery`), each miss a
  query whose MessagePack `DeserializeMsgPack<T>` turns into elements. The game builds these objects ad
  hoc (construct, Initialize: a new connector, one lookup, destroy), so a lookup usually runs the
  whole path.
- The element `T` (`CMasterParameterItemElement`, `StringDBEelement`, ...): one row, a
  `CParameterElementBase` with a property per column (params_layout.h), deserialized by params.

`StringDB` (`master_text`) is a `_Simple<StringDBEelement>`: `GetNativeString(id)` looks up
`CHash32("ja_" + id)` (the prefix is hard-coded: the English mode serves English in the `ja_` rows of
`basmaster-en.sqlite3`, docs/client-changes.md "English mode"; platform370's text hooks read it back
through `StringDB::Get`).

## Elements (160 classes, generated)

The element classes differ only in their property lists, and their default constructors are inlined
into the templates, so the layouts are generated: [`tools/gen_master_elements.py`](../../../../tools/gen_master_elements.py)
reads each class three ways that must agree (the inlined constructor's vtable stores, statically; the
destructor and `Initialize` run under unicorn on an element built from it, [`tools/uemu.py`](../../../../tools/uemu.py):
the lib with its relocations applied; the exported C2 constructor too where there is one) and writes
[`gen/master_elements.h`](gen/master_elements.h): per class a typed layout (the properties as
`params::CParameterPropertyValue<T, N, Conv>` / `CParameterPropertyString<N>` members named after their
keys, `static_assert`ed), the property table (offset, kind, N, key, AddProperty position, default) and
the exported methods. T0 `generated` reruns it in `--check` mode.

Left to the guest (`UNFIT` in the generator): `CMasterParameterHome3DMapElement`, `...LanguageElement`,
`...RoleDuplicationItemElement`, `CMasterSphere211FloorAssetBoxElement`, `...OverwriteEnemyLevelElement`
(constructed only in a local function of `DeserializeParameter`) and `CMasterParameterWorldMapMissionElement`
(0x10..0xd80 built by a loop).

Quirks kept: four properties are declared but never named nor linked by `Initialize`
(`CMasterDeepSpaceBonusElement` +0x40, `CMasterParameterEventWeeklyElement` +0x40,
`CMasterParameterFactorElement` +0x470, `CMasterHome3DElement` +0x320: link -1 in the table); the copy constructor and
`operator=` copy `m_first` and every `m_next` as they are, so a copy's property list runs through the
source's properties.

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `TElement<E>`: `E::Initialize` (160), `E::E()` (C2 / C1, where exported), `E::E(E const&)`, `E::operator=`, `~E` (D2 / D1), `~E` (D0): 800 symbols | [`master_element.cpp`](master_element.cpp), bound by [`master_element_bind.cpp`](master_element_bind.cpp) | `master/elements-ctor-init`, `master/elements-copy-assign-dtor` ([`master_element_test.cpp`](master_element_test.cpp): every class) | below |

`Initialize`: per named property in AddProperty order, `m_name = CHash32(key)` (a key of 23 bytes or more
is a long `std::string` temporary: allocated and freed around the call, as the guest does), `m_named = 1`,
the default, `AddProperty` (params' native). The constructor, the copy constructor (strings through
libcxx's `string_copy_construct`), `operator=` (libc++'s inlined assign: in place, else
`__grow_by_and_replace`) and the destructor (each string's vtable, its storage freed, the base vtable;
`~CHash32` is a RET) as described in `master_layout.h`.

**Live check** (`soa --live-check master[:every=N][:only=..][:out=FILE]`, [`master_family.h`](master_family.h),
[`master_element_check.cpp`](master_element_check.cpp)): a run-both family. Ctor / Initialize / the copy
constructor run the native, put the element's bytes back and run the original on the element itself
(the copy's strings compared by representation, the original's freed); `operator=` and the destructor
run the original on a private copy (long strings in storage of their own, same capacity). The deleting
destructor isn't checked (the original would delete its copy).

## Dependencies

- `params`: the element base and the properties (`params_layout.h`), `CParameterElementBase::AddProperty`
  (called directly), the check's string helpers (`params_check.h`).
- `hash`: `CHash32::Assign` (the key hash).
- `libcxx`: the game string (`string_copy_construct`, `__grow_by_and_replace`).
- `memory` (guest): the STL allocator, operator delete (`master_guest.cpp`, through `live::out_call`).
- `yayoi`: the SQLite driver the connectors use; its `SQLiteDriver::BuildQuery<CLocalEntity<...>>`
  instantiations (170) are in yayoi's scope though only the connectors call them.
