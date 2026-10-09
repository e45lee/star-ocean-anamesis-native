# `api`: the API callers: FakeApiCaller (the in-process route) and the request notifications

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/api/scope.txt`](../../../decomp/api/scope.txt).
- Decompiles and the function list: [`port/decomp/api/`](../../../decomp/api/) (`symbols.tsv`; `tools/decomp.sh --into api/<topic>`).
- Types: [`api_layout.h`](api_layout.h); for Ghidra, `tools/subsystem.py export-types api` -> `port/decomp/api/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

| Class | Guest size | Found from (ctor, decompile) | Status |
|---|---|---|---|

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
none yet.

## RE notes
