# server/include/soaserver: the server library's public headers

What the port (`port/src/native/api/*`, `common/test.cpp`, `ui/webview_local.cpp`), soa-server (`../app`, `../net`) and the tests include. These paths are an interface: `server/PLAN-readability.md` keeps them while the sources behind them move. The table in [../../README.md](../../README.md) "API" says what each declares; the request flow is in [../../ARCHITECTURE.md](../../ARCHITECTURE.md).

| Header | For |
|---|---|
| `server.h` | the request API (`Request`, `submit`, `handle`, `error_code`), the clocks (`clock_now`, `event_now`, `set_server_clock`, the test seam `set_clock_source`), `apply_client_master`, `web_page`, the pure `rules::` |
| `config.h` | `ServerConfig` / `config()`: everything the server is configured with |
| `ext.h` | the module-writer API: registrations (`add_api`, `add_player_load`, `add_response_hook`, `add_grant`, `add_item_extra`, the mission extras, `add_client_master`; `hook_order`, `registration_errors`), `Ctx` (what every handler gets: the DBs, the RNG, the request's state and the server's services as member functions), the SQLite wrapper's names `Sql` / `Row` / `Arg` (`sql.h`), shared state helpers, present texts, `refuse` and its codes; `api_sources` (`soa-server --list-apis`), `add_core_api` (the core's registrations) |
| `sql.h` | the one SQLite wrapper (`sql::Row`, `Arg`, `Sql`, `one_null_as_zero`; defined in `src/state/sql.cpp`); typed ids read as `row.id<T>` / `row.opt<T>` (NULL = none), bound as `Arg`, `one_id<T>` / `one_opt<T>` |
| `ids.h` | the typed ids (`CharacterUid`, `ItemUid`, `PlayerId`, `RoleId`, `SameRoleId`, `MasterItemId`, `MissionId`, `GachaId`, `TitleId`, `AreaId`, `SkillId`; PLAN-readability R12): no implicit conversion between kinds; `or_zero` / `nonzero` between an optional reference and the wire's 0 |
| `msgpack.h` | `Value` and its encoder / decoder (response bodies) |
| `battle_log.h` | the battle log a MissionEnd carries |
| `hooks.h` | what the server asks its host: the asset index |
| `log.h` | the log sink |
| `events.h`, `api_campaign.h` | the event and story-campaign entry points the hosts call |
| `cdn.h`, `adld.h` | the CDN content and ADLD packing |
| `chash32.h` | the game's `Framework::CHash32` |
| `npc_status.h` | mission NPC status from the master data |
| `testing.h`, `native_test.h`, `scratch.h` | the test registry and runner, the `NATIVE_TEST` spelling, a scratch server for tests outside the library |

Every function here gets a doc comment (section 2.6 of the plan); the check is report-only until R19 (`tools/check_server_docs.sh`).
