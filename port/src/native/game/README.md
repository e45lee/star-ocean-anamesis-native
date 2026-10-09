# `game`: the game's phases (CPhase and its phase classes)

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/game/scope.txt`](../../../decomp/game/scope.txt).
- Decompiles and the function list: [`port/decomp/game/`](../../../decomp/game/) (`symbols.tsv`; `tools/decomp.sh --into game/<topic>`).
- Types: [`game_layout.h`](game_layout.h); for Ghidra, `tools/subsystem.py export-types game` -> `port/decomp/game/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

| Class | Guest size | Found from (ctor, decompile) | Status |
|---|---|---|---|
| `CPhase` (the phase manager, a CFiberUnit) | partial (0x50..) | the constructor, Switch, RequestSwitch, Progress (`port/decomp/game/phase.c`) | typed |
| `CBase` (`CPhase::CBase`: a phase; slot constants) | 8 + the derived class's | its vtable, CPhase_Home's | typed |
| `CPhase_Base` (the menu phases' base; `m_screenUiId` is the derived menu phase's first field) | 0x24 + | its constructor, CPhase_Home's constructor and Progress | typed |

No natives: the port's `CPhase::Progress` wrapper (`common/port_debug.cpp`, the control commands `phase:N` and
the `port_debug: phase N` log lines) reads these types.

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
kernel (`CFiberUnit`).

## RE notes
