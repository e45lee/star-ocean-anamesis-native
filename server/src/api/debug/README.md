# api/debug: the debug APIs (stubs)

| File | Module | What |
|---|---|---|
| `debug_stubs.cpp` | `debug_stubs` | the 27 `Debug*` methods (`docs/unimplemented-apis.md` 2.4), each an `ext::add_stub`: answered `{Time}`, nothing changed, every call logged `stub: <Method> ...`. Not in the 3.7.0 client's API table: only a test or a modified client sends them. Rules: docs/server-rules.md#social-stubs |

Tests: `../../core/stub_tests.cpp` (`server/stubs`); the replay corpus `server/tests/replay/stubs`.
