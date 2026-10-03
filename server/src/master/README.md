# server/src/master: read-only master data

Data the server reads and never writes.

| File | What |
|---|---|
| `master.{h,cpp}` | the shared master lookups (step R6b): `master_global` (`global_str`, `global_u32`, `global_u32_unless_empty` (api/favor/'s reading), `global_f`), the player rank and stamina tables (`player_level_rows`, `stamina_max`, `player_level_max`, `player_next`), role level caps and next EXP (`role_level_cap`, `role_next`), `text(message_id)` (master_text, ja) and the mission tables (`find_mission` -> `MissionRef`). The core's `Server` members and `ext::Ctx` / `ext::global_f` / `ext::text` forward to them |
| `gacha_pools.{h,cpp}` | the reconstructed gacha pools (`port/server-data/gacha_pools.sqlite3`, built by `tools/build_gacha_pools.py`; docs/server-rules.md "4.5 Gacha pools (reconstructed)") |
| `npc_status.cpp` | `rules::npc_status`: the battle status of a mission NPC from the master data, as the client's `MasterMissionNpcModel::CalculateParameter` computes it (docs/server-rules.md "Tutorial battle") |

Tests: `soa-server --selftest "server/npc-status|server/gacha-pools"`.
