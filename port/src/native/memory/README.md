# `memory`: the engine heaps, allocators, handles

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/memory/scope.txt`](../../../decomp/memory/scope.txt).
- Decompiles and the function list: [`port/decomp/memory/`](../../../decomp/memory/) (`symbols.tsv`; `tools/decomp.sh --into memory/<topic>`).
- Types: [`memory_layout.h`](memory_layout.h); for Ghidra, `tools/subsystem.py export-types memory` -> `port/decomp/memory/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

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
