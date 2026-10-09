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
| `FakeApiCaller` | 0x580 (0x60 + CApiNotify) | the constructor, destructors, Release, Progress, IsRequesting, AddLocalFile (`port/decomp/api/fakeapi.c`) | native (the route) |
| `Info` (`FakeApiCaller::Info`), `InfoMap` / `InfoNode` (`map<FunctionID, Info>`: node 0x80) | 0x50 | `Info::Info`, Progress | typed |
| `RequestLambda` (a request method's `[this]` lambda: `libcxx::func<FakeApiCaller*>`) | 0x10 | the request methods, the lambdas' `operator()` | typed |
| `CApiNotify` (partial: `m_fid` 0x510, `m_errorCode` 0x514, `m_pending` 0x518) | not pinned (0x520 as recovered) | the constructor, OnProtocolError (`notify.c`) | typed |

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `FakeApiCaller` (everything but the lone RETs: the request methods, the lambdas, the status-only / constant methods, AddLocalFile, Progress, IsRequesting, Release, construction, destruction) and the base-class requests the route serves | `fakeapi.cpp` (group `kGroupRoute`: the in-process route, `port/src/native/README.md`) | `fakeapi/requests`, `trivial`, `lambdas`, `progress`, `serve-no-handler`, `lifetime`, `slots` | none: the game never constructs a FakeApiCaller (the route's behaviour is proven by tests/diff and the sessions) |

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
libcxx (the map, the string, std::function and `libcxx_function.h`), kernel (`CFiberUnit`), data_formats (the
fake login's ASON, `Status`), info (InfoBase, the parameter manager for `--fake-server-schema`), resource
(`CResourceElement::kSlotPImage`).

## RE notes
