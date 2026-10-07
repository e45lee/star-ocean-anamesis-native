# server/include/soaserver: the server library's public headers

What the port (`port/src/native/api/*`, `common/test.cpp`, `ui/webview_local.cpp`), soa-server (`../app`, `../net`) and the tests include. These paths are an interface: `server/PLAN-readability.md` keeps them while the sources behind them move. The table in [../../README.md](../../README.md) "API" says what each declares; the request flow is in [../../ARCHITECTURE.md](../../ARCHITECTURE.md).

| Header | For |
|---|---|
| `server.h` | the request API (`Request`, `submit`, `handle`, `error_code`), the clocks (`clock_now` a `ServerTime`, `event_now` / `event_time` an `EventTime`, `clock_as_calendar`, `set_server_clock`, the test seam `set_clock_source`), `format_time` of either, `apply_client_master`, `web_page`, the pure `rules::` |
| `config.h` | `ServerConfig` / `config()`: everything the server is configured with |
| `ext.h` | the module-writer API: registrations (`add_api`, `add_player_load`, `add_response_hook`, `add_grant`, `add_item_extra`, the mission extras, `add_client_master`; `hook_order`, `registration_errors`), `Ctx` (what every handler gets: the DBs, the RNG, the request's state and the server's services as member functions), the SQLite wrapper's names `Sql` / `Row` / `Arg` (`sql.h`), shared state helpers, present texts, `refuse` and its codes; `api_sources` (`soa-server --list-apis`), `add_core_api` (the core's registrations) |
| `sql.h` | the one SQLite wrapper (`sql::Row`, `Arg`, `Sql`, `one_null_as_zero`; defined in `src/state/sql.cpp`); typed ids read as `row.id<T>` / `row.opt<T>` (NULL = none), bound as `Arg`, `one_id<T>` / `one_opt<T>`; server-clock times read as `row.time` / `row.opt<ServerTime>` (NULL = never), `one_time`, bound as `Arg` (no `EventTime` overload: the event calendar is never stored) |
| `ids.h` | the typed ids (`CharacterUid`, `ItemUid`, `PlayerId`, `RoleId`, `SameRoleId`, `MasterItemId`, `MissionId`, `GachaId`, `TitleId`, `AreaId`, `SkillId`; PLAN-readability R12): no implicit conversion between kinds; `or_zero` / `nonzero` between an optional reference and the wire's 0 |
| `times.h` | the time value types (PLAN-readability R17): `ServerTime` (the server clock, every stored time) and `EventTime` (the event calendar); no mixing, no implicit number in or out; a time plus seconds, two times of one clock subtract to seconds; formatted at the boundary (`format_time`, `Ctx::fmt_time`) |
| `msgpack.h` | `Value` and its encoder / decoder (response bodies; msgpack-cxx underneath, `src/core/msgpack.cpp`) |
| `battle_log.h` | the battle log a MissionEnd carries |
| `hooks.h` | what the server asks its host: the asset index |
| `log.h` | the log sink |
| `events.h`, `api_campaign.h` | the event and story-campaign entry points the hosts call |
| `cdn.h` | the CDN content (ADLD packing: common/include/soa/adld.h) |
| `npc_status.h` | mission NPC status from the master data |
| `testing.h`, `native_test.h`, `scratch.h` | the test registry and runner, the `NATIVE_TEST` spelling, a scratch server for tests outside the library |

Every function here has a doc comment (the comment above it or above its group of declarations; constructors, destructors and operators are covered by their class's): enforced since R19 (`tools/check_server_docs.sh`, `tools/server_doc_coverage.py`).
