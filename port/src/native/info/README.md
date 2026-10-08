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
| `InfoBase` | 0x38 | the constructors, Initialize, DeserializeChild (port/decomp/info/person_status.c) | typed (the base); the 143 derived info classes not yet |

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `CInteroperateParameter::IsExist(row)`, `IsExist(row, col)`, `ConvertToRow`, `ConvertToColumn` (lower_bound in the hash maps), `IsValue` / `IsString` / `Value(row, col)` (ConvertToRow, then the CSV's slot on (row, col + 1)) | [`info_interoperate.cpp`](info_interoperate.cpp) | `info/interoperate` (a table the guest builds from CSV text) | run-both (the result registers) |
| `InfoBase::DeserializeChild` (each key's property gets Deserialize(map); each key's child DeserializeArray / DeserializeChild) | [`info_infobase.cpp`](info_infobase.cpp) | `info/deserialize-child` (CPersonStatusInfo) | the original rerun after the native, every property compared (infos without children only: a child's array would be appended twice) |

**Live check** (`soa --live-check info[:every=N][:only=..][:out=FILE]`, [`info_family.h`](info_family.h)): Results (battle-gacha, `every=1`, PASS): 200,000 checks, 0 mismatches (IsExist(row) 48,281, Value(row, col)
147,768, DeserializeChild 3,951); an earlier run 201,613 / 0.

## Next (not done)

- The info classes (`C*Info`: 143 with Initialize, 46 copy constructors, 29 constructors): like the master
  elements, properties after the base, but `Initialize` puts each property in `m_properties` by its
  NameHash (`__tree::__emplace_unique_key_args<unsigned, unsigned, IParameterProperty*&>`, an out-of-line
  libc++ function) and children in `m_children`; the copy constructors copy the maps. A generator in the
  manner of `tools/gen_master_elements.py` (hooking that emplace) fits them.
- `CTimeUtility::str2time_t` (AToF, mktime; the tm_isdst quirk), `CParameterManager::Progress`,
  `CInfoManager`'s constructor (every info inlined), `StaminaUtility`.

## Dependencies

- `libcxx`: std::map (tree) layouts; `hash`: CHash32; `params`: the properties (Deserialize through their
  vtables), the string properties' list (gen/params_instantiations.inc); `data_formats`: AMap / AValue.
