# server/src/master: read-only master data

Data the server reads and never writes.

| File | What |
|---|---|
| `master.{h,cpp}` | the shared master lookups (step R6b): `master_global` (`global_str`, `global_u32`, `global_u32_unless_empty` (api/favor/'s reading), `global_f`), the player rank and stamina tables (`player_level_rows`, `stamina_max`, `player_level_max`, `player_next`), role level caps and next EXP (`role_level_cap`, `role_next`), `text(message_id)` (master_text, ja) and the mission tables (`find_mission` -> `MissionRef`). The core's `Server` members and `ext::Ctx` / `ext::global_f` / `ext::text` forward to them |
| `gacha_pools.{h,cpp}` | the reconstructed gacha pools (`data/gacha_pools.sqlite3`, built by `tools/build_gacha_pools.py`; docs/server-rules.md#gacha-pools) |
| `english_text.{h,cpp}` | the English text table of `--english` (`data/english/master-en.tsv`): `load`, `table()`, the matching rule `match` (a row's English for exactly the Japanese it translates), `display` (the server's own texts: `ext::display_text`, the gacha rate headings); the CDN's `make_english_master` applies the same rule (docs/server-rules.md#english) |
| `english_derive.{h,cpp}` | the derived layer of `--english` (official by id, E3, exact and template memory; folding, re-breaking, the checks; the merge with our rows): tools/english_text.py `derive` in C++ (docs/server-rules.md#english-derive; utf8proc for Unicode) |
| `npc_status.cpp` | `rules::npc_status`: the battle status of a mission NPC from the master data, as the client's `MasterMissionNpcModel::CalculateParameter` computes it (docs/server-rules.md#tutorial-battle) |

Tests: `soa-server --selftest "server/npc-status|server/gacha-pools|server/english-text|server/english-derive"`; `tests/test_english_derive.py` compares the derivation with the Python tool's.
