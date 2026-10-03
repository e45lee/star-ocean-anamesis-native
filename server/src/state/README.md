# server/src/state: the player state

The state DB (`server.sqlite3`): its schema and how a file is brought to it, what fills a new one, the checks on it, and the one SQLite wrapper every handler uses. This is the state module of `../../PLAN-schema.md` (3.1; step S1 made it). Every table of the state is created here when the DB opens: no module creates its own, none is made lazily, and no handler asks whether a table exists.

| File | What |
|---|---|
| `schema.{h,cpp}` | the schema as ordered migration steps (`kSchemaVersion`, `steps()`): step N takes a file from version N-1 to N. Step 1 is the baseline, the 58 tables as the server created them before S1, verbatim (`baseline_sql()`), plus the column repair (a baseline column a legacy table lacks is added with its default). Step 2 (S2) drops the dead: `roster.favor`, `mission.best_rank`, `exchange_counts.shop_id`, the tables `view_flags`, `gear`, `box_gacha`, `planets` (54 tables). Step 3 (S3) moves the keys that were structured state out of `meta`, `sphere_meta` and `counters`: nine `player` columns, the table `ds_state`, four `sphere` columns; `sphere_meta` dropped (54 tables; `move_keys` maps the values). Step 4 (S4) is the roster: `roster_ext` and `assist` merged into `roster`, and `roster` and `player` rebuilt STRICT with the state's first foreign keys and `roster`'s three unique indexes; the party sets 1..`party_set_max` get their rows (52 tables; `rebuild_roster_and_player` maps the rows; the foreign keys and their actions are listed above `kRoster`) |
| `state.{h,cpp}` | `open_and_migrate` (below), `user_version`, `report_master_refs` (the master-reference check at open), and the `meta` table's helpers `meta` / `next_uid` / `has_player` (`meta` holds `next_char_uid`, `next_item_uid` and `seed` only) (core/server.h includes this header) |
| `check.{h,cpp}` | the master-reference check (`state::check`, PLAN-schema S0): every state column that holds master ids (`master_refs()`, PLAN-schema 1.6's `m:` rows) resolved against the master; report-only (a dangling id is returned and logged, nothing is fixed) |
| `sql.cpp` | the one SQLite wrapper, `sql::Row` / `Arg` / `Sql` and `one_null_as_zero` (declared in the public `../../include/soaserver/sql.h`; the handlers see them as `ext::Row` / `Arg` / `Sql`) |
| `kvs.{h,cpp}` | the Game.xml codec: the game's Aska::LocalKVS SharedPreferences files (`read_kvs`, `read_kvs_ordered`, `write_kvs`, `kv_u32`, `kv_str`; the layout is the client's, `soa_save/kvs.py` documents it) |
| `seed.{h,cpp}` | seeding a new state from a save: the player (with the tutorial and view words), roster, party 1, the party sets 1..`party_set_max`, the default titles and meta keys (`seed`, `real_seed_save`, `kLocalPlayerId`; docs/server-rules.md "Seed") |

## Opening a state DB

`Server::open_state` (`../core/server.cpp`) is the one read-write open of the state, for both hosts (soa in-process, soa-server) and the tests' scratch servers:

1. `state::open_and_migrate(db, path, kSchemaVersion, master)` (the master gives a step the values it maps with: S4's `party_set_max`):
   - the file's version is `pragma user_version` (0 for a file from before S1, or a new one);
   - **a version newer than this build's is refused**: the server doesn't open it and the file isn't touched (LOGE). There is no down-migration; going back to an older build means restoring a `.bak` copy;
   - an older file that has a player is first copied to `<path>.bak-v<version>` (`sqlite3_backup`; LOGI `state DB …: schema version N -> M`);
   - with `foreign_keys` off, each missing step runs in its own `begin immediate` transaction: its SQL, its C++ (data mapping, repairs), `pragma foreign_key_check` (any row: rollback, LOGE, not opened), `pragma user_version = N`, commit. A failure leaves the file at the last good version;
   - then `pragma foreign_keys = on`.
2. `journal_mode = wal`.
3. A state without a player is seeded (`seed`, in one `begin immediate … commit`), unless the new-player mode wants none. The commit checks the deferred foreign keys (`player.home_uid`, `party_id`); a seed it refuses is rolled back and the file isn't opened.
4. `state::report_master_refs`: `state::check` against the master, one LOGW per dangling reference (report-only: a master can change under a saved state).

A new file runs every step from version 0, so a new state and an upgraded one are the same (the test `server/schema-fresh-equals-migrated`). A module that needs a new table or column adds a step to `schema.cpp` (a table rebuild follows PLAN-schema 4.1's procedure).

The session scripts that write a state directly (Python `sqlite3`) also switch `foreign_keys` on; the tools open it read-only.

## Tests

`schema_tests.cpp`: `server/schema-fresh-equals-migrated`, `server/schema-migrate-v1`, `server/schema-migrate-v2`, `server/schema-migrate-v3` and `server/schema-migrate-v4` (each migrates only to its version, `open_and_migrate`'s `target`; on the committed v0 fixture `../../tests/fixtures/state-v0.sql`, written by `tools/make_state_fixture.py`: every table has rows, plus the dirt the later steps clean; v3 plants S3's key cases itself and also migrates a version 2 file; v4 plants S4's roster cases and also migrates a version 3 file without the master; each checks `foreign_key_check`), `server/schema-fk-actions` (what deleting or updating each parent does to its children, the dangling writes refused at once or at commit, the unique indexes, STRICT), `server/schema-newer-refused`; `check_tests.cpp` (`server/schema-integrity`: a scratch server's state is at this version with every table and foreign keys on, its seeded state violates no foreign key, and no foreign key is violated and its master references resolve after representative calls); `../api/entry/entry_tests.cpp` `entry/create-player-references` (CreatePlayer's transaction commits with its deferred foreign keys); `tools/schema_inventory.py --check STATE` is the same check for a session's end state (PLAN-schema G9); `sql_tests.cpp` (`server/sql-typed-ids`: the typed ids' binding and reading, NULL as none; the kinds don't convert), `kvs_tests.cpp` (`server/kvs-roundtrip`), `seed_tests.cpp` (`server/seed-from-380-save`); `../core/server_tests.cpp` seeds a whole session. The uid scheme of owned objects (`kRosterUid0`, `kNewCharUid0`, `kItemUid0`) is `../core/ids.h`.
