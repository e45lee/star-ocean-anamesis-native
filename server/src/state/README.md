# server/src/state: the player state

The state DB (`server.sqlite3`) and what fills it. Today it holds the Game.xml codec and seeding (moved out of `../core/server.cpp` by step R8 of `../../PLAN-readability.md`). `../../PLAN-schema.md` S1 makes this the state module: the schema (today `Server::schema()` in `../core/server.cpp` and the modules' `ext::add_schema` calls), the `meta` helpers (`meta` / `set_meta` / `next_uid`, declared in `../core/server.h`) and the one SQL wrapper move here then.

| File | What |
|---|---|
| `kvs.{h,cpp}` | the Game.xml codec: the game's Aska::LocalKVS SharedPreferences files (`read_kvs`, `read_kvs_ordered`, `write_kvs`, `kv_u32`, `kv_str`; the layout is the client's, `soa_save/kvs.py` documents it) |
| `check.{h,cpp}` | the master-reference check (`state::check`, PLAN-schema S0): every state column that holds master ids (`master_refs()`, PLAN-schema 1.6's `m:` rows) resolved against the master; report-only (a dangling id is returned, nothing is fixed). Only its test calls it until S1 runs it at open |
| `seed.{h,cpp}` | seeding a new state from a save: the player, roster, party 1, planets and meta keys (`seed`, `real_seed_save`, `kLocalPlayerId`; docs/server-rules.md "Seed") |

The uid scheme of owned objects (`kRosterUid0`, `kNewCharUid0`, `kItemUid0`) is `../core/ids.h`. Tests: `kvs_tests.cpp` (`server/kvs-roundtrip`), `seed_tests.cpp` (`server/seed-from-380-save`), `check_tests.cpp` (`server/schema-integrity`); `../core/server_tests.cpp` seeds a whole session.
