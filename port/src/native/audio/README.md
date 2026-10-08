# `audio`: sound and voice: the game's sound engine (Aska::Sound*, Audio*, SLVoice, AskaOGG / AskaADPCM, Sequencer2; Framework::CSound*; CSoundManager, the voice managers)

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/audio/scope.txt`](../../../decomp/audio/scope.txt).
- Decompiles and the function list: [`port/decomp/audio/`](../../../decomp/audio/) (`symbols.tsv`; `tools/decomp.sh --into audio/<topic>`).
- Types: [`audio_layout.h`](audio_layout.h); for Ghidra, `tools/subsystem.py export-types audio` -> `port/decomp/audio/types.json`.
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
