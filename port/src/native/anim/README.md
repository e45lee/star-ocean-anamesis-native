# `anim`: animation controllers (TAaf*), blending, IK

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/anim/scope.txt`](../../../decomp/anim/scope.txt).
- Decompiles and the function list: [`port/decomp/anim/`](../../../decomp/anim/) (`symbols.tsv`; `tools/decomp.sh --into anim/<topic>`).
- Types: [`anim_layout.h`](anim_layout.h); for Ghidra, `tools/subsystem.py export-types anim` -> `port/decomp/anim/types.json`.
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
