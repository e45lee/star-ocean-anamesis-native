# Plan: make the local server readable and documented

Status: in progress. Written 2026-10-02 (agent `server-readability-plan`, off `linux-port` 2488055); R0–R5, R6a–h, R7, R8, R9, R10, R11, R13, R14, R15, R16 and R18a (deep space, Sphere 211, cdn/) done (each step's "Done" note in 4.3 says what was built and how it was proven). The assessment (section 1) describes the code as it was at 2488055.

**Scope.** The server library and its programs in `server/` (`src/`, `include/soaserver/`, `net/`, `app/`, `tests/`), plus the places outside `server/` that name its files or call it: `port/src/native/api/{fakeapi,server_adapters,server_cdn,zz_server_guest_test}.cpp`, `port/src/native/restore/restore_campaign.cpp`, `tools/schema_inventory.py`, `docs/server-rules.md`, `docs/api.md`. The goal: a human who has never seen the code can find where a rule is implemented, read a handler top to bottom, and change it without breaking the other host. **No game behaviour changes**: every step is proven byte-identical on the wire and in the state (section 4.1).

**The other plan.** `server/PLAN-schema.md` (the state DB: one schema module `server/src/state/`, versioned migrations, foreign keys; steps S0–S11) owns the state schema and the DB access layer. This plan doesn't redo any of it. It says where its own steps (R0–R20) go before, after or with S0–S11 (section 4.2), and its target layout puts `state/` where PLAN-schema puts it.

**Trigger.** About 25,000 lines in 100 files, written by about 20 agents one after another. `server.cpp` alone is 3,818 lines: one `struct Server` of 2,627 lines (server.cpp:364–2990) with 85 member functions, 24 API handlers and an if-chain dispatcher. The rules are well commented, with 1,219 source labels (a)–(d) and 115 client addresses as evidence. But the structure is history-shaped (files named after agents' tasks), the same helpers exist in up to seven copies, and nothing maps "API X" or "rule Y" to a place in the code.

**Summary of the findings** (section 1):

- **Two handler shapes.** Core handlers are `Server` members that read hidden per-request members (`refuse`, `restarting`, `mission_ov`, `in_game`). Module handlers take `(ext::Ctx&, const Request&)`, where `Ctx` is 19 `std::function`s the core lends. server.cpp can't be split until the two become one shape.
- **Hidden ordering.** The modules register from static initializers in **source-basename order** (server/CMakeLists.txt:20–31). 14 `OnPlayerLoad`, 2 `OnResponse`, 5 `ClientMaster` and 5 mission-extra hooks run in that order. Responses keep map insertion order, so renaming a file can change reply bytes.
- **Duplicates.** Two SQLite wrappers, two response envelopes, two scratch servers. 5 `fmt_local` and 5 `parse_*` time helpers, 6 "day start" variants and 4 identical `open_at`. 5 copies of "spend free coins first", 3 asset-gating paths, and a second hand-written msgpack codec in `api_campaign.cpp`.
- **Magic numbers.** About 95 refusal sites use a raw error code. One code has a name (`kErrNoPlayer`, server.cpp:1257). Content types, mission types, helper kinds and uid bases are literals too.
- **Names.** `c` is a `Ctx` 267 times and also a `Row` 5 times. `r` is a `Request` 80 times and a `Row` 154 times. `m` is the master DB and also a `Row` 22 times (shadowing). Request arguments are positional (`r.ints[k]` 87 times); their meaning is only in comments.
- **Comments.** The labels are rich, but 77 "agent X" history notes sit in the code, plus some stale notes (canned files, `in_game` "no guest", `restore:` log prefixes, an unused `file` parameter). The labels drift: "free coins first" is (c) in one place and (d) in two. 4 of 23 quoted doc-section links point at headings that don't exist.
- **Finding rule X.** `growth_rules.h` is implemented in 4 different `api_*.cpp` files. The pure rules live in 5 places. `docs/server-rules.md` is ordered by agent history ("Server rules added by agent server-rules"), not by domain. There is no API → handler index.

**The steps** (section 4):

- **Groundwork, no game code:** R0 proof harness (byte-identical replay) and evidence manifest → R1 docs, READMEs, API index, the docs check → R2 `.clang-format`.
- **With PLAN-schema's first steps:** S0 → R3 one format-only commit → R4 explicit module order → R5 file moves into domain folders → S1 (+ one SQL wrapper).
- **Shared helpers and the split:** R6 shared helpers (time, master lookups, named error codes, responses, wallet, request arguments, asset gate, campaign msgpack) → R7 one handler shape → R8 split server.cpp by domain → R9 one request lifecycle for both hosts.
- **Per domain, each cleanup just before its schema step:** R10 player + S3, R11 roster + S4, R12 typed ids, R13 items/gear + S5, R14 parties + S6, R15 missions + S7, R16 presents + S8, S9 + R17 time types, R18 modules + S10.
- **Last:** S11 + R19 permanent gates. R20 (re-heading `docs/server-rules.md` by domain) is later.

---

## 1. Assessment

Measured on 2488055 with `wc -l`, grep, a brace-matching function sizer and a comment-only label counter. The scratch scripts are reproduced as `tools/server_evidence.py` in R0. Line numbers are as of that commit.

### 1.1 Size and shape

| Area | Files | Lines | Biggest |
|---|---|---|---|
| `src/` | 43 | 15,144 | server.cpp 3,818; api_deepspace.cpp 1,223; api_sphere211.cpp 1,199; api_campaign.cpp 869; cdn.cpp 781; api_gear.cpp 646 |
| `include/soaserver/` | 16 | 1,261 | ext.h 245; msgpack.h 190; cdn.h 159 |
| `net/` (+ `gen/`) | 24 | 4,197 | game.cpp 520; wire.cpp 373; ninja_ciphers_ossl.cpp 336 |
| `app/` | 1 | 276 | main.cpp (`main` 149 lines) |
| `tests/` (+ `net/`, `ninja/`) | 17 C++ + data and Python tools | 4,560 C++ | sphere211_tests.cpp 721; cdn_tests.cpp 485 |

- **Functions.** 53 functions or test bodies are over 50 lines, 15 over 100:
  - `api_mission_start` 275 (server.cpp:1309);
  - `cdn::Tree::build` 272 (cdn.cpp:414);
  - `api_mission_end` 218 (server.cpp:1843);
  - `api_gacha` 202 (server.cpp:2449);
  - deep space `mission_end` 183 (api_deepspace.cpp:748);
  - gear `generate` 154 (api_gear.cpp:475);
  - soa-server's `main` 149;
  - `npc_status` 131 (npc_status.cpp:32);
  - `GameServer::handle_packet` 131 (net/game.cpp:338);
  - `person_status` 116 (server.cpp:808);
  - `decode_request` 116 (net/wire.cpp:181);
  - sphere 211 `put_state` 106 (api_sphere211.cpp:607).
- **The core is one object.** `struct Server` (server.cpp:364–2990) holds:
  - the two DB handles;
  - the RNG;
  - the pending requests;
  - seeding;
  - every master lookup;
  - the player/roster/party/items response builders;
  - 24 handlers (entry flow, party, missions, drops, gacha, step-up, box, presents, play state);
  - the transaction;
  - the dispatcher.

  The pure rules (`rules::`, server.cpp:43–86), the Game.xml KVS codec (server.cpp:212–335), the clock (server.cpp:187–210) and 14 unit tests (server.cpp:3092–3818) share the file.
- **The test suite today:** `build/server/soa-server --selftest` runs 90/90 in 38 s (this worktree, `scripts/build.sh --target soa-server` in 72 s).

### 1.2 How a request flows today

```
 soa (in-process)                                   soa-server (out of process)
 FakeApiCaller hook (port/src/native/api)           net/loop.cpp poll loop -> net/game.cpp handle_packet
   server_adapters.cpp: guest registers -> Request    Ninja decrypt -> net/wire.cpp decode_request -> Request
   fakeapi.cpp:619  server::submit(r)                 LiveBackend::call (game.cpp:62):
   fakeapi.cpp:620  campaign::on_request(r)             EndMissionTalk? -> events / campaign, then GetPlayMission
   fakeapi.cpp:418  server::handle(fid, file, out)      submit(r); campaign::on_request(r); handle(fid, "", out)
   fakeapi.cpp:420  server::error_code(fid)             error_code(fid); campaign_reply -> campaign::on_response
   fakeapi.cpp:452  campaign::on_response(...)        reply: <Name>Res, AES, LoginResult + GetPlayerRes
             \                                         /
              v                                       v
   server.cpp:3033 submit()     pending[fid] = Request              (global Server, one mutex)
   server.cpp:3082 handle()  -> Server::handle (2886): set g_request_log (battle log)
                             -> handle_request (2895): "begin"; forced_error (--fail)
                             -> dispatch (2925): 37 methods by if-chain, else ext::find(method) (57 registrations, 69 methods)
                                  core handler: Server member, reads refuse / restarting / mission_ov / in_game
                                  module handler: (ext::Ctx&, Request) -> Ctx = 19 std::function into Server (2824)
                             -> refuse != 0: "rollback", errors[fid] = code, body = {Time, Player, Wallet}
                             -> ext::on_response hooks (decode, add keys, re-encode), "commit"
```

What a reader has to discover by themselves:

- **The request lifecycle is split between the library and its two hosts.** The campaign's `on_request` / `on_response` and the `EndMissionTalk` special case are wired twice: fakeapi.cpp:418–452/619–620/693 and net/game.cpp:30–85, each with a comment saying it mirrors the other. `handle()`'s `file` parameter (server.h:86–88, "the canned file name") is passed through three functions and never read (server.cpp:2886–2925). soa-server passes `""`, the scratch server `"x.msgp"`.
- **The story campaign is a parallel architecture.** `api_campaign.cpp`:
  - keeps its own state in a text file `<data>/server_campaign.txt` (api_campaign.cpp:365–420), outside the state DB and outside PLAN-schema's scope;
  - opens its own master (`open_master`, :271);
  - edits response bytes with its own msgpack reader/writer (:34–200) instead of `Value`;
  - is called by the hosts, not by the dispatcher.

### 1.3 The `ext::` module mechanism

ext.h (245 lines) is the module API, with static registration objects. Counted by grep, `^(ext::)?<Kind> name(`:

| Kind | Registrations | Files |
|---|---|---|
| `Api` (method → handler) | 57 (69 methods) | 13 `api_*.cpp` |
| `OnPlayerLoad` (keys on Login / GetPlayer / NoLoginStart) | 14 | 13 |
| `Schema` (lazy `create table`) | 16 | 15 (removed by PLAN-schema S1) |
| `Grant` (content types the core can't grant) | 5 | 4 |
| `ClientMaster` (the served master's overrides) | 5 | 4 |
| `MissionStartExtra` / `MissionResultExtra` | 2 / 3 | 3 |
| `OnResponse` (every response) | 2 | api_event.cpp, api_title.cpp |
| `ItemExtra`, `events::AreaExtra` | 1 / 1 | api_gear.cpp, api_worldboss.cpp |

- **Order is implicit.** The vectors fill in static-initializer order. server/CMakeLists.txt:20–31 sorts `src/*.cpp` and `tests/*.cpp` by **basename** to make that order "the order of the file names", and soa-server links the archive whole. `OnPlayerLoad` hooks add keys to one `Value` map, and `mp_encode` writes maps in insertion order (msgpack.h), so their order is visible in the reply bytes. `event_extras.h` already works around one ordering dependency by hand ("run in one fixed order by api_worldboss.cpp's ext::MissionResultExtra"). Also, `file(GLOB … src/*.cpp)` is not recursive: a file moved into a subfolder silently drops out of the library.
- **`Ctx` is a bag of lambdas.** ext.h:70–97: `now`, `event_now`, `fmt_time`, `parse_time`, `base_data`, `roster`, `stock`, `items`, `player_id`, `role_next`, `role_level_cap`, `stamina_max`, `tick_stamina`, `global_u32`, `player_next`, `player_level_max`, `grant`, `core_mission`, `set_error`. Each is a lambda into `Server` (server.cpp:2824–2861), so "go to definition" lands in a lambda. `core_mission` re-enters the core MissionStart/MissionEnd through a member pointer `mission_ov` (server.cpp:1259, 2849–2858).
- **Hidden per-request state on the long-lived object.** `refuse` (server.cpp:2867), `restarting` (:1258), `mission_ov` (:1259), `logged_in` (:1256), `in_game` (:1828), `test_log_value`, and the global `g_request_log` (:342). api_title.cpp:37 keeps `g_added` between a `Grant` and an `OnResponse` of the same request.

### 1.4 Types the code passes around

- `Value` (msgpack.h:14) is a fat tagged struct (all of `b`, `i`, `u`, `f`, `s`, `arr`, `map` present). `find()` is const-only, so code writes `const_cast<Value*>(d.find("Player"))` (3 sites). It reads `find("x")->u` without a null check 28 times.
- `Request` (server.h:30) carries `ints`, `strs` and `vecs` positionally. Handlers decode them with `r.ints.size() > k ? r.ints[k] : dflt` (58 times; 87 `r.ints[k]`). The names are in docs/api.md's **Request** line and in a comment, if anywhere. Some defaults aren't 0 (`UpdateParty`'s party id defaults to 1, server.cpp:1136).
- Ids are bare `u32`/`u64`. A character's uid, a role id, a same-role id, an item uid, a master item id, a mission id and a "helper id" that is any of three things (MissionStart's helper arguments, server.cpp:1311–1316) are all integers. The client's own names add to it: `character_id` and `weapon_item_id` are **uids**, `id` is a uid in `Character` but a master id in `StockItem` (server.cpp:769). The internal names should still say which is which.
- The battle log reaches handlers through a global (`g_request_log`) and `in_game` flags. `in_game` is documented as "no guest CParameterManager" (ext.h:73, server.cpp:1828). Since H (2026-10-01) it means "use the request's battle log rather than the test value".

### 1.5 Duplicated code

| What | Copies (file:line) |
|---|---|
| SQLite wrapper `Row` / `Arg` / query | server.cpp:91–180 (`Db`) and ext.h:27–55 + ext.cpp:12–73 (`Sql`). **Not identical:** `Db::one` returns 0 for a NULL value, `Sql::one` the default. That matters at the server.cpp call sites with a non-zero default: server.cpp:542, 1420, 1642, 1787, 1790, 2479 |
| Response envelope `body()` | server.cpp:947 and ext.cpp:215 |
| Scratch test server | `ext::with_scratch_server` (server.cpp:3316) and `ScratchServer` (server.cpp:3347) |
| Format a local time | `fmt_time` server.cpp:194; `fmt_local` favor.cpp:65 (returns "" for t ≤ 0), api_event.cpp:43, api_sphere211.cpp:172, net/game.cpp:88 |
| Parse a local time | `parse_time` server.cpp:202; `parse_local` api_event.cpp:51, api_sphere211.cpp:180, favor.cpp:59 (strict `strptime`); `parse_clock` support.cpp:51 (also epoch seconds); `local_time` mission_rules.cpp:29 (day + time) |
| Start of the reset day | `growth_rules::day_start` (api_bonus.cpp:24); `day_start(Ctx&)` api_follow.cpp:143; `favor_day` favor.cpp:180 (a day number); `today` api_daily.cpp:25; `limit_day` api_deepspace.cpp:209; `rental_day` api_sphere211.cpp:568 |
| Date window open | `open_at` ×4, identical: api_bonus.cpp:46, api_daily.cpp:22, api_shop.cpp:50, api_deepspace.cpp:118. Variants: `in_window` api_campaign.cpp:424 (string compare), `events::window_open` api_event.cpp:107 (year shift), `gacha_open` server.cpp:2069, `achievement_open` (sphere211.h:38), `open_client` api_deepspace.cpp:130 |
| Spend coins, free first | server.cpp:2488–2497, api_shop.cpp:153, api_items.cpp:339, api_sphere211.cpp:984, api_deepspace.cpp:784. The label is "(d)" at server.cpp:2472 and api_deepspace.cpp:784, "(c)" at api_items.cpp:339 and in docs/server-rules.md "Stocks and wallet" |
| `master_global` reads | `global_u32` through `Ctx` (46 calls), `ext::global_f` (7), favor.cpp's `global_str` / own u32, 15 raw `from master_global` queries in 6 files |
| "Does the table exist yet" probes | 9 `sqlite_master` checks (removed by PLAN-schema S1) |
| msgpack | msgpack.h (`Value`, `mp_encode`/`mp_decode`) and api_campaign.cpp:34–200 (`Mp`, `mp_skip`, `splice_data`, `merge_maps`) |
| Asset gating | `AssetIndex` (hooks.h), `events::set_asset_check` / `asset_exists` (api_event.cpp:116–125), `sphere211::set_asset_check` (api_sphere211.cpp:96–135), `asset_index()` read directly (api_deepspace.cpp:143) |
| Pure "rules" namespaces | `rules::` (server.cpp:43, declared in the *public* server.h:100–117), `growth_rules` (declared growth_rules.h, **defined in api_items.cpp:14, api_bonus.cpp:15, api_shop.cpp:16, api_growth.cpp:14**), `mission_rules`, `deepspace_rules` (inside api_deepspace.cpp:47), `gear_rules` (api_gear.cpp:641) |

### 1.6 Naming

- **One-letter names carry most of the meaning.**
  - `c` is the `Ctx` (267 parameters) but a `Row` in 5 lambdas (server.cpp:719, 814, 1298, 1893, 1937).
  - `r` is the `Request` (80) and a `Row` (154). In `api_mission_start` the row is `mr`, `s`, `n` while `r` stays the request.
  - `m` is the master DB (`m.q` 309 times) and a `Row` in 22 lambdas. One of them, server.cpp:725, is inside `party_set_value`, where the outer `m` is the master DB.
  - `st` is the state DB (626 uses), `d` the response data.
  - Other short names: `mp` MissionParameter, `pc` PlayerCharacter, `bp` BattleParameter, `pm` PlayMission, `us` the uid list, `xs` / `xm`, `flv`, `iuid`, `mth`, `ov`, `fc`.
- **ids vs uids vs labels.** The state uses `uid` for owned objects and `*_id` for master ids (PLAN-schema 3.1 keeps that). The code mixes them: `helper_own` / `helper_rental` are uids, `helper_npc` is a `master_mission_npc` *or* `master_npc` id (server.cpp:1458). `id_label` strings appear as `label`, `l`, `ol`. Wire keys can't change (the client reads them). Variables and functions can.
- **Function names describe the response shape, not the client class.** `player_value`, `person_value`, `person_status`, `items_value` etc. build `CPlayerInfo`, `CPersonInfo`, `CPersonStatusInfo`, `CItemInfo`. Only some comments say so.
- **Files are named for the task that wrote them.** `api_bonus.cpp` (login bonus + achievements), `api_daily.cpp` (premium pass + favor login bonus), `api_home.cpp` (footer flags + social stubs), `api_follow.cpp` (rental helpers), `support.cpp` (config + log + asset index + CHash32), `event_extras.h`, `growth_rules.h` (also shops and login bonus).

### 1.7 Comments

Counted in comment text only (`(x)`, `(x:` and `; x:` forms). Code tokens like `calendar(c)` are excluded.

| | (a) | (b) | (c) | (d) | client addresses `@xxxxxxxx` | `+0x` offsets |
|---|---|---|---|---|---|---|
| all of `server/` | 347 | 395 | 55 | 422 | 115 (incl. 88 cipher constants in `net/ninja_*`) | 81 in `src/` + `include/` |
| server.cpp | 83 | 89 | 8 | 88 | 3 | |
| api_deepspace.cpp / api_sphere211.cpp | 32 / 28 | 31 / 35 | 3 / 5 | 37 / 38 | | |

- **Good.**
  - Most rules carry a label next to the code.
  - The client function or offset is named as evidence ("CHome::GetAdjutant (@01aebe38) takes CParameterManager+0x8698", server.cpp:601–606).
  - Every file starts with a header comment.
  - 66 comments link `docs/server-rules.md` sections.
  - `ext::PresentReason` (ext.h:224) is the model for a named enum with its evidence.
- **Agent history.**
  - 77 "agent X" mentions in code (33 in server.cpp; 22 distinct agents, e.g. "agent server-rules" 13, "agent events-extras" 10). They say *who and when*, not *what or why*, e.g. "(agent server-growth: the compose level and the lock flag)", server.cpp:796.
  - docs/server-rules.md has 73 more, and several of its headings are agent sections: "Server rules added by agent `server-rules` (2026-09-29)", "Server missions: what agent `server-missions` added".
- **Stale.**
  - The `restore:` log prefixes (server.cpp:382–391): `--restore` is gone and nothing greps them.
  - The "canned file" / "static files of --fake-server" wording (server.h:86–88, api_campaign.h:26–27, server.cpp:2953 "FakeApiCaller maps these to gacha_pc.msgp").
  - `in_game` "no guest CParameterManager" (ext.h:73, server.cpp:1828).
  - favor.h:2 "A separate module so it can be merged next to server.cpp".
  - History notes in live code: server.cpp:2940 "Before (agent p5b-tests-diff) it had no handler…".
  - server/README.md "86 today: 72 library, 14 wire layer" (90 now).
- **Label drift.** The same rule is labelled differently in different places: "free coins first" (1.5). docs/server-rules.md calls (c) "outside knowledge". Some file headers repeat the legend in other words.
- **Broken links.** 4 of the 23 distinct quoted section titles have no matching heading: "Banner images", "Episode data", "Favorability", "Rental helpers (agent gaps-core)" (the heading has backticks and more text).

### 1.8 Magic numbers

- **Error codes.**
  - About 95 refusal sites. With `ext::refuse(c, …, CODE)`: 10208 (50), 10206 (14), 10710 (7), 10204 (7), 11006 (5), 20000 (4), 11001 (3), 17001 (2), 11002, 10004, 10002. With `refuse = CODE` in server.cpp: 10004, 10206, 10403 ×3.
  - One named constant: `kErrNoPlayer = 19001` (server.cpp:1257).
  - The meanings are the client's `master_text error_message_text_<code>`: 137 codes in the 3.7.0 master. E.g. 10206 アイテムの所持数エラーが発生しました, 10208 アイテムは使用できませんでした, 10403 不正なデータ処理です. **10710 and 11001 both read FOLが不足しています.** Which one the live server sent is a (d) decision (ext.h:239), so they must stay two names.
- **uid bases.** `kRosterUid0` / `kNewCharUid0` / `kItemUid0` are named (server.cpp:360–362). The NPC party uid base `0x7f000000` / `0x7f000001` is a literal 6 times (server.cpp:1433–1485). `kItemUid0`'s value is repeated in api_gear.cpp:32.
- **Domain enums as integers.**
  - Content types (`d.type == 1..4`, `5..10 || 16`, server.cpp:1705–1740; 33 `type == N` tests in `src/`).
  - Mission type 0–3 (server.cpp:1275–1279).
  - Helper kinds 1–3 (server.cpp:1524–1547).
  - Drop types.
  - Achievement types 61/62.
- **Kept as evidence, not "magic".** The client's struct offsets in comments (`CParameterManager+0x1a38`, 81 `+0x` in comments). These are the RE trail and stay. The cipher constants in `net/ninja_*` are data.

### 1.9 Public headers

- `server.h` mixes four things: the request API (`Request`, `submit`, `handle`, `error_code`), the clocks, the notice board's `web_page`, and the pure `rules::` (only server.cpp and the tests use them).
- `ext.h` is the module-writer API (registries, `Ctx`), a SQLite wrapper, a dozen state helpers, the present texts and the refusal convention. The port includes it only for zz_server_guest_test.cpp.
- `events.h` and `sphere211.h` export test hooks (`set_asset_check`) next to rules.
- `api_campaign.h` describes "the fake server's canned file".
- What the port uses: `server.h`, `msgpack.h`, `config.h`, `battle_log.h`, `events.h`, `chash32.h`, `cdn.h`, `testing.h`, `scratch.h`, `log.h`, `hooks.h`, `ext.h`, `api_campaign.h` (port/src/native/api/*, common/test.cpp, ui/webview_local.cpp). Those paths are an interface; R5 keeps them.

### 1.10 Tests

- **Location.** 26 tests live at the end of `src/` files (14 in server.cpp, 3 in api_deepspace.cpp, …) and 64 in `tests/`. The port's rule is "tests next to the code" (port/PLAN.md "Code organization"); neither place follows it consistently.
- **Seeds.** They come from test names (testing.h `seed_for`), so moving a test doesn't change its inputs. Run order is link order.
- **Naming.** 69 tests are named `server/…`, whatever their domain.
- **The port's side.** The server tests that need the game are the port's (port/src/native/api/zz_server_guest_test.cpp).
- **What's missing.** No test pins the module hook order, and no test covers "every registered API answers".

### 1.11 "Where is rule X implemented?"

The paths a reader has to know today:

- An API is either in server.cpp's if-chain (37 methods) or in an `Api` registration in one of 13 files. A few live only in the hosts (`EndMissionTalk`) or in the campaign (`GetWorldMapInfoList`, `ActiveMissionList` splices).
- Its response may be changed by:
  - 14 `OnPlayerLoad` hooks;
  - 2 `OnResponse` hooks;
  - mission extras;
  - the campaign's byte splicer.

  None of these is visible from the handler.
- A rule's text is in `docs/server-rules.md`. Its 1,570 lines are partly by topic (sections 1–12) and partly by agent (from "Notes for the server-core implementation" on). Code links to it by quoted title, and 4 links are broken.
- Pure rules are split over 5 places (1.5). `growth_rules` has one header and 4 implementing files.

### 1.12 Interfaces a refactor must not move silently

- **The public API and header paths** (1.9). Port call sites: fakeapi.cpp:418/420/452/619/620/693/982–984, server_adapters.cpp:160, zz_server_guest_test.cpp.
- **The server's log lines** that scripts match:
  - `request X (fid` (UpdateTutorial, MissionStart/End, NoLoginStart, EndMissionTalk, AchievementActiveList);
  - `refused with error` (12 scripts);
  - `MissionEnd mission N: unlocked …`, `MissionEnd mission N: player exp`, `MissionEnd mission N drops: surprise yes`;
  - `MissionStart: rental helper .* as member 4`, `MissionStart party member 0: uid`;
  - `MissionStart NPC … [hp … grd …]` (tools/compare_tutorial.py);
  - `Gacha N (… draws for`, `GetGachaInData: .* gachas open`;
  - `Sphere211MissionEnd: .*streak 4`, `server: tower: N areas`;
  - `seeding from`, `I/server: Deep…`.
- **26 files outside `server/`** name `server/src/*.cpp` paths (docs, tools, port sources).
- **`tools/schema_inventory.py`** hard-codes `SERVER_DIRS`, `OTHER_DB = server/src/gacha_pools.cpp`, `endswith("api_sphere211.cpp")` and `endswith("server.cpp")` (lines 38–43, 483–488).
- **The CMake basename order** (1.3).

---

## 2. Target structure

### 2.1 Layout

The domains follow docs/api.md's API groups, so the catalogue, the code and the rules doc share one vocabulary.

```
server/
  README.md            what the library is, how to build / run / test, the layout (this tree), links
  ARCHITECTURE.md      request flow (diagram below), transactions and refusals, clocks, the module
                       registry and its order, the two hosts, where state and master data live
  API-INDEX.md         generated: API -> handler -> hooks -> rules section -> docs/api.md -> tests
  PLAN-schema.md, PLAN-readability.md
  include/soaserver/   the public API (paths unchanged; contents narrowed, see 2.3)
  src/
    README.md
    core/              the server object, the request lifecycle, the module registry
      server.{h,cpp}       init, open, one transaction per request, dispatch through the registry
      request_context.h    per-request state (refusal, battle log, mission override, restart)
      context.{h,cpp}      Ctx: the services a handler gets (2.3), not std::function lambdas
      registry.{h,cpp}     Api / hooks registration with explicit order (R4); was ext.cpp
      modules.cpp          the one ordered list of every module's registrations
      lifecycle.cpp        answer(Request): submit + campaign + EndMissionTalk + handle (R9)
      clock.{h,cpp}        server clock, event calendar (was event_clock.cpp), test clock seam
      time.{h,cpp}         format / parse / day start / windows (the 1.5 copies)
      ids.h                typed ids and domain enums (2.3)
      errors.h             named error codes (generated, 2.4)
      response.{h,cpp}     the envelope, player-state answers, refusals
      request_args.h       named argument readers
      battle_log.cpp, config.cpp, log.{h,cpp}, asset_index.cpp, chash32.cpp   (support.cpp split)
    state/             PLAN-schema S1's module (schema.cpp, state.h, README.md), plus:
      sql.{h,cpp}          the one Row / Arg / Sql (both 1.5 copies, at S1)
      seed.{h,cpp}, kvs.{h,cpp}   seeding and the Game.xml (Aska::LocalKVS) codec
    master/            read-only master data
      master.{h,cpp}       typed lookups: global_u32/f/str, level tables, role caps/next EXP, text(), mission tables
      gacha_pools.{h,cpp}, npc_status.cpp
    rules/             pure functions over values, unit-tested beside them
      rules.{h,cpp} (was server.h rules::), growth_rules.{h,cpp} (one file), mission_rules.*, deepspace_rules.*,
      gear_rules.*, *_tests.cpp
    api/<domain>/      handlers + their hooks + their tests; one README per domain naming its APIs and rules sections
      entry/        Login, SimpleLogin, CreatePlayer, UpdateTutorial, UpdateView, UpdateKiyakuVersion, UpdatePlayerName, GetServerTime, NoLoginStart
      player/       GetPlayer + the player load, UpdateParty, UpdatePartySet, SetAssist, UpdateHome, titles, home footer, notice page
      missions/     MissionStart, MissionEnd, drops / lottery, campaigns (master_campaign), GetPlayMission, MissionFailed/Talk/Restart, GetMissionList
      campaign/     the story campaign (ActiveMissionList, world map), on Value instead of its byte splicer (R6h)
      events/       event missions, enable-events, ranking, world boss, favor drop, event extras
      deepspace/, sphere211/, tower/
      growth/       BoostCharacter … EquipSkill
      items/        compose, grade up, sell, lock, heal items, stamina heal; gear/
      gacha/        Gacha*, SaleGacha*, GachaTicket, GetGachaInData, GetGachaRate, step-up, box
      shop/         item shop, exchange, subscriptions (passes)
      presents/     PresentList, GetPresent(Array), present texts, achievements
      daily/        login bonus, premium pass, favor login bonus, StaminaHealByFavor
      favor/        UpdateFavorByTap, UseFavorItem, favor levels
      social/       FollowList, UpdateSupport (rental helpers), Blacklist, SearchPlayer, GetRecentlyPlayedList
    cdn/               cdn.cpp (split: served master, bundles, version.bin / manifests), adld.cpp
    testing/           testing.cpp, scratch.cpp (the one scratch server), replay.cpp (R0)
  net/                 the wire layer, unchanged in role; ninja_*.cpp -> net/ninja/; game.cpp loses the campaign wiring (R9)
  app/                 soa-server's main (option parsing split from main())
  tests/               cross-cutting only: net/, ninja/, replay/ corpora, fixtures/ (PLAN-schema's state-v0.sql)
```

**File map (today → target).** Step R5 moves whole files. R6–R8 split the multi-topic ones.

| Today | Target |
|---|---|
| server.cpp | core/server.cpp (init, `handle`, dispatch), core/context.cpp (`ext_ctx`), state/seed.cpp + state/kvs.cpp (Game.xml codec, seeding), state/sql.cpp (with S1), master/master.cpp (lookups), rules/rules.cpp (`rules::`), api/entry/*.cpp, api/player/{player_info,party,home}.cpp, api/missions/{mission_start,mission_end,drops,campaigns,play_state}.cpp, core/rewards.cpp (`grant`, `add_character`), api/gacha/{gacha,stepup,box,rates}.cpp, api/presents/presents.cpp, api/favor/favor_api.cpp (the favor branch of dispatch), testing/scratch.cpp, and its 14 tests beside the domain they test |
| ext.cpp, ext.h | core/registry.cpp, core/response.cpp, state helpers → state/, wallet → core/wallet.cpp; `include/soaserver/ext.h` keeps what the port's test uses (`Sql`, `Ctx`, `with_scratch_server`) |
| support.cpp | core/config.cpp, core/log.cpp, core/asset_index.cpp, core/chash32.cpp |
| testing.cpp, server_log.h, battle_log.cpp, event_clock.cpp | testing/testing.cpp, core/log.h, core/battle_log.cpp, core/clock.cpp |
| adld.cpp, cdn.cpp | cdn/ |
| gacha_pools.*, npc_status.cpp | master/ |
| mission_rules.*, growth_rules.h (+ the 4 `namespace growth_rules` blocks) | rules/ |
| api_bonus.cpp | api/daily/login_bonus.cpp + api/presents/achievements.cpp |
| api_daily.cpp | api/daily/premium_and_favor_bonus.cpp |
| api_campaign.cpp | api/campaign/ |
| api_deepspace.cpp | api/deepspace/{deepspace.cpp, rewards.cpp, state.cpp, deepspace_tests.cpp}; `deepspace_rules` → rules/ |
| api_event.cpp, api_event_ranking.cpp, api_worldboss.cpp, api_favor_drop.cpp, enable_events.*, event_extras.h | api/events/{event_missions, ranking, world_boss, favor_drop, enable_events}.cpp, events/event_extras.h |
| api_follow.cpp, rental.h | api/social/rental.{h,cpp} |
| api_home.cpp | api/player/home_footer.cpp + api/social/social.cpp |
| api_title.cpp, api_notice.cpp | api/player/titles.cpp, api/player/notice.cpp |
| api_gear.cpp, api_items.cpp | api/items/gear.cpp (+ `gear_rules` → rules/), api/items/items.cpp |
| api_growth.cpp, api_shop.cpp, api_subscription.cpp | api/growth/growth.cpp, api/shop/shop.cpp, api/shop/subscription.cpp |
| api_sphere211.cpp, sphere211.h | api/sphere211/{season, floors, rewards, ranking}.cpp, sphere211.h |
| api_tower.cpp, tower.h | api/tower/ |
| favor.*, present_texts.cpp | api/favor/favor.*, api/presents/present_texts.cpp |
| tests/*_tests.cpp | beside their domain (e.g. tests/sphere211_tests.cpp → api/sphere211/sphere211_tests.cpp); tests/net, tests/ninja stay |
| net/ninja_*.cpp, ninja_ref.*, ninja_ciphers.h | net/ninja/ |

### 2.2 Naming conventions

- **Files** are snake_case and named for their contents. No `api_` prefix inside `api/`. One responsibility per file; no grab-bag files (`support.cpp`, `api_bonus.cpp`).
- **Handlers** are named after the API: `mission_start`, `set_title`. The response builders are named after the client class they fill:
  - `player_info()` (CPlayerInfo);
  - `person_info()` (CPersonInfo);
  - `person_status_info()` (CPersonStatusInfo);
  - `item_info()` (CItemInfo);
  - `stack_item_info()` (CStackItemInfo);
  - `party_set_info()` (PartySetInfo).

  Each has a one-line comment naming the class and where the client reads it.
- **Variables.**
  - `ctx` (the `Ctx`), `req` (the `Request`), `args` (its decoded arguments).
  - `ctx.state` / `ctx.master` instead of `c.st` / `c.m`.
  - A row is named for its table: `mission_row`, `role_row`, `stage_row`. Never `r`, `c` or `m`.
  - `data` for the response's data map.
  - Abbreviations are expanded (1.6 list). Loop indices and the conventional `i`, `k` are fine.
- **Ids.** `*_uid` = an owned object (character, item); `*_id` = a master row id; `*_label` = an `id_label` string; `same_role_id`, `mission_type` and `content_type` as the master names them. The wire keys keep the client's names; a comment notes where a key named `*_id` carries a uid.
- **Constants** are `kCamelCase` and **enums** are `enum class` with the master/client value. Each constant carries its evidence label in a comment.
- **Rules namespaces:** `rules::<domain>` (`rules::growth`, `rules::missions`), pure functions only, no DB.

### 2.3 Type vocabulary (`core/ids.h`, `core/time.h`, `core/response.h`, `core/request_args.h`)

- **Typed ids.** A small `template <class Tag, class Rep> struct Id { Rep v; explicit …; operator<=> }` with:
  - `PlayerId` (u32, CHash32 of the search id);
  - `CharacterUid`, `ItemUid` (u64);
  - `RoleId`, `SameRoleId`, `MasterItemId`, `MissionId`, `GachaId`, `TitleId`, `AreaId` (u32).

  `Row::uid<CharacterUid>("uid")`-style accessors and `Arg` overloads keep the SQL call sites short. No implicit conversion between kinds: passing a `RoleId` where a `CharacterUid` is expected doesn't compile. Introduced after PLAN-schema S4, which makes "none" a NULL rather than 0 (R12). As built: `soaserver/ids.h`, `row.id<T>` / `row.opt<T>` (R12's note in 4.3).
- **Domain enums** from the master data and docs/api.md:
  - `ContentType` (1 item … 99 item set; docs/api.md "Content types");
  - `MissionType` (0 story, 1 event, 2 tower, 3 world map);
  - `DropType`;
  - `HelperKind` (own, rental, NPC);
  - `PresentReason` (exists);
  - `AchievementType`.

  The NPC party uids become `kNpcPartyUid0`.
- **Time.**
  - `core/time.h`: `format_time` / `parse_time`, with explicit variants where today's copies differ. favor.cpp's empty-for-0 formatter and strict parser stay distinct functions with names saying so; behaviour doesn't change.
  - `day_start(t, reset_hour)`.
  - `struct Window { opened, closed; bool contains(t) const; }` (empty = open-ended), the one `open_at`.
  - After PLAN-schema S9 (INTEGER `*_at` everywhere), R17 adds `ServerTime` and `EventTime` value types, so the two clocks can't be mixed. (S9 done: what R17 can rely on, the stored times and their remaining 0 sentinels, is PLAN-schema S9's as-built note, "What R17 can rely on from version 9".) The event-calendar vs server-clock choice is a frequent source of (d) comments today (api_deepspace.cpp:119–129). As built: `soaserver/times.h`, `row.time` / `row.opt<ServerTime>`, no `Arg` from an `EventTime`, `Window::contains` only on a typed time (R17's note in 4.3).
- **Rewards.** `struct Grant { ContentType type; u32 id; u32 num; DropType drop; }` and `struct Granted { Value items, stocks, characters; }` replace the `(u32 type, u32 id, u32 num, Value& items, Value& stocks, Value& chars)` signature (ext.h:91, 119). The core's `grant()` and the `ext::Grant` registry become one `rewards::grant(ctx, Grant, Granted&)`. `core/wallet.h` holds `spend_coins(ctx, price, paid_only)` (the five copies), `add_fol`, `add_free_coins` and `add_stock`, each with its one label.
- **Requests.** `core/request_args.h`: a per-API args struct parsed at the top of the handler, e.g. `struct MissionStartArgs { MissionType type; MissionId mission; u32 helper_index_plus_1; CharacterUid own_helper; u32 npc_helper_id; u64 rental_id; }` with `static from(const Request&)`. It has today's defaults (1 for UpdateParty's party). The field names come from docs/api.md's **Request** line. A missing argument logs at the same level as today (none).
- **Responses.**
  - `Response` (the body bytes) built by `ok(Value data)`, `with_player_state(ctx)` (today's `base_data()`: `{Time, Player, Wallet}`) and `ctx.refuse(ErrorCode, why)`.
  - One `body()`.
  - `Value::find_mut` replaces `const_cast`, and `Value::get_u(key, dflt)` replaces unchecked `find(k)->u`.

### 2.4 Error handling

- **`core/errors.h`** is generated by `tools/gen_error_codes.py` from `data/basmaster-3.7.0.sqlite3` `master_text` (`message_id like 'error_message_text_%'`, lang ja; 137 codes). It holds `enum class ErrorCode : u32` with a hand-chosen name per code the server uses, and the client's text as the comment. Unused codes are listed in a comment table, not as enumerators. Example:

  ```cpp
  enum class ErrorCode : u32 {
      kPlayerNotFound   = 10002,  // プレイヤーデータが見つかりません。
      kStaminaShort     = 10004,  // スタミナが不足しています。
      kLockedItem       = 10204,  // ロック中のアイテムが含まれています。
      kItemCountError   = 10206,  // アイテムの所持数エラーが発生しました。
      kItemUnusable     = 10208,  // アイテムは使用できませんでした。 (d) the server's generic refusal
      kInvalidOperation = 10403,  // 不正なデータ処理です。
      kFolShort         = 10710,  // FOLが不足しています。 (d) which of the FOL codes: ext.h "refuse"
      kFolShortGrowth   = 11001,  // FOLが不足しています。
      kLevelCap         = 11002,  // レベル上限です。
      kLimitReached     = 11006,  // 上限に達しています。
      kExchangeExpired  = 17001,  // アイテムの交換期限が切れています。
      kNoPlayer         = 19001,  // 不正なデータ処理です。 (b) Login's lambda: "no account yet"
      kCoinsShort       = 20000,  // 紋章石が不足しています。
  };
  ```
- **One refusal path.** `return ctx.refuse(ErrorCode::kItemCountError, "ticket short");` logs `"<Method> refused: <why> (error N)"` (the same line as today's `ext::refuse`), rolls back, and answers the player state. The core's `refuse = N; return body(base_data());` pairs (server.cpp:1369–1374, 2365–2369, 2426, 2482) become that call. Their log line differs today ("MissionStart: stamina %u < cost %u: refused"); R6c keeps each existing text (1.12) by passing it as `why`, or keeps the old format where a script reads it.
- **Who answers what.** `handle_request` owns the contract (ARCHITECTURE.md):
  - a refusal rolls back and answers `{Time, Player, Wallet}` with the code;
  - "not handled" means no body (the host's fallback);
  - a handler never throws.

### 2.5 How a handler reads

The template every handler follows after its domain's cleanup step (the example is today's api_title.cpp:91–105 rewritten; the behaviour is the same):

```cpp
// SetTitle(u32 master_title_id) -> SetTitleRes                     fid 4332363c
// API: docs/api.md#settitle   Rules: docs/server-rules.md#titles
//
// Selects the title the status bar's plate shows.
//   (b) CHonorMenu::CallApiSetTitle sends it; CHonorMenu::UpdateTitleData expects Player.title
//       back (it marks the list entry equal to CParameterManager+0xed8).
//   (d) An id the player doesn't own is refused with kItemUnusable (10208, the generic refusal).
//   (d) 0 takes the title off: CHonorMenu's remove button (ChangeRemoveButtonActive) is the only
//       sender of 0.
// Answers: the player state with Player.title, and TitleList.
Response set_title(Ctx& ctx, const Request& req) {
    const auto args = SetTitleArgs::from(req);  // { TitleId title; }
    ensure_default_titles(ctx);
    if (args.title && !owns_title(ctx, args.title))
        return ctx.refuse(ErrorCode::kItemUnusable, "title not owned");
    select_title(ctx, args.title);
    Value data = player_state(ctx);
    set_player_title(data, args.title);
    data["TitleList"] = title_list(ctx);
    LOGI("server", "SetTitle %u", args.title.v);  // read by home_session.sh
    return ok(std::move(data));
}
SOA_API({"SetTitle"}, set_title);  // registers it (a list: e.g. {"LockItem", "LockItemArray", ...}); the index records file and line
```

The rules:

- The doc comment's first line is the method signature, the reply and the fid. Then the `API:` and `Rules:` links, a sentence of purpose, every rule with its label, and what it answers.
- The body reads as numbered steps. Anything over about 60 lines is split into named steps. `mission_start` becomes:
  1. `resolve_mission`;
  2. `cost_and_checks`;
  3. `roll_surprise`;
  4. `stage_list`;
  5. `pay`;
  6. `battle_party` (own party / tutorial NPCs / event NPC helper / rental / own helper);
  7. `record_play`;
  8. `mission_start_response`.
- A log line a script reads carries a `// read by <script>` comment.
- Hooks that add keys to this API's response are listed in its domain README and in API-INDEX.md.

### 2.6 Documentation

- **`server/ARCHITECTURE.md`** has the request-flow diagram (mermaid, with the ASCII of 1.2 updated as a fallback):

  ```mermaid
  flowchart LR
    subgraph hosts
      A[soa: FakeApiCaller hook<br/>server_adapters.cpp] --> L
      B[soa-server: net/game.cpp<br/>Ninja + decode_request] --> L
    end
    L["core/lifecycle.cpp answer(Request)<br/>EndMissionTalk, campaign hooks"] --> H["core/server.cpp handle()<br/>begin; RequestContext"]
    H --> R{"core/registry<br/>find(method)"}
    R --> API["api/&lt;domain&gt;/handler<br/>(Ctx&, Request) -> Response"]
    API --> S[(state/ sql: server.sqlite3)]
    API --> M[(master/: basmaster-3.7.0)]
    API --> RU[rules/: pure functions]
    H --> X["hooks in order (modules.cpp):<br/>OnPlayerLoad, OnResponse, mission extras"]
    H --> E{"refused?"}
    E -- yes --> RB[rollback + player state + error code]
    E -- no --> C[commit + body]
  ```

  It also covers the transaction and refusal contract (2.4), the two clocks (server clock vs event calendar), the module registry and its explicit order, where state and master data live (pointing at state/README.md from PLAN-schema), what the hosts own (wire and FakeApiCaller) and what the library owns.
- **A README per folder** (`src/`, each `src/<dir>/`, each `api/<domain>/`, `net/`, `tests/`). It says:
  - what the folder holds and its public header;
  - its APIs, its hooks with their order slots, and its state tables (linking state/README.md);
  - its rules sections, its tests, and the sessions that exercise it.
- **Doc comments.** Every public function in `include/soaserver/` and every `core/` / `master/` / `rules/` header function gets one. Every handler and hook gets the 2.5 block. Every rule keeps or gains its (a)–(d) label.
- **Links from code to docs** use anchors (`docs/server-rules.md#titles`), checked by `tools/check_server_docs.sh`. The quoted-title form (`docs/server-rules.md "Titles"`) is accepted until R20.
- **`server/API-INDEX.md`** is the "where is X" index, generated by `tools/server_index.py`:
  1. **API table:** method · fid · handler file:function · the hooks that touch its response · `Rules:` link · docs/api.md anchor · tests that call it.
  2. **Rule-section table:** each `docs/server-rules.md` heading → the code locations whose `Rules:` / labels link it.
  3. **Hook order table** (modules.cpp).

  The handler data comes from the registry itself (`soa-server --list-apis`, R1; `SOA_API` records `__FILE__` / `__LINE__` from R7 on), the rest from the doc comments.

---

## 3. Comment cleanup policy

- **Keep** (verbatim or moved with its code):
  - every (a)–(d) label;
  - every client symbol (`CHonorMenu::UpdateTitleData`), address (`@01aebe38`) and offset (`CParameterManager+0xed8`);
  - every master table / column named as the source;
  - every "why" (the reasoning of a (d));
  - test-data provenance;
  - `380-ok` markers.
- **Rewrite** agent-history notes into what/why, keeping their evidence:
  - "(agent server-growth: the compose level and the lock flag)" → "(the compose level and the lock flag: api/items/)";
  - "Entry flow (agent restore-title): …" → "Entry flow: …".

  The agent's name goes. `git log -S` finds who wrote it, and docs/history/ keeps the narrative. This applies to code; in docs, headings name the domain, and attributions move to docs/history/ or a single "History" note.
- **Remove** what describes code that no longer exists:
  - canned files;
  - `--fake-server` static files as the fallback (server.h:86–88);
  - "no guest CParameterManager";
  - "Before (agent …) it had no handler";
  - the `restore:` log prefix;
  - "merged next to server.cpp".

  Each removal is listed in its commit message.
- **Fix drift.** When one rule has different labels in different places, the code comment and docs/server-rules.md are made to agree in the domain's cleanup step. The commit message gives the evidence for the label kept. Example: "free coins first" — docs say (c), two code sites (d).
- **Unlabelled rules.** A domain step adds a label to every response value the server chooses that has none. Example: `p["storage_stock"] = 500u; // (d)` is labelled, but `p["is_3d_home"] = true;` (server.cpp:632) isn't. New (c)/(d) labels go into docs/server-rules.md "Register of (c) and (d) rules" too.

**How to verify that nothing is lost.** `tools/server_evidence.py` (R0) prints a manifest for the tree. Each R step runs it on the parent and the child commit; `tools/check_server_docs.sh --evidence PARENT` compares the two:

| Item | Compared as | Must |
|---|---|---|
| labels (a)/(b)/(c)/(d) in comments, per domain | counts | not decrease, unless the commit message lists each removed label with its code (deleted code) |
| client addresses `@[0-9a-f]{7,8}` (outside `net/ninja*`) | set of tokens | be equal (moved files are fine) |
| client symbols `\b[A-Z]\w+::\w+` in comments | set | be ⊇ the parent's |
| `+0x[0-9a-f]+` offsets in comments | multiset | be ⊇ |
| master tables `master_\w+` in comments | set | be ⊇ |
| `docs/server-rules.md` links | each resolves to a heading or anchor | all resolve |
| "agent [a-z0-9-]+" in `server/` code | count | not increase; 0 at R19 |
| the log-line patterns of 1.12 | each found in a `LOG*` format string | all present |

---

## 4. Steps

### 4.1 Gates and the proof of no behaviour change

| Gate | What | Notes |
|---|---|---|
| **RG1 build** | `scripts/build.sh` (all targets: the port links the library) | |
| **RG2 server selftest** | `build/server/soa-server --selftest` | 90/90 on 2488055, 38 s; the count only grows |
| **RG3 port selftest** | `soa --selftest "server/"` (zz_server_guest_test.cpp); one full `soa --selftest` per merge wave | brief: ~20 min full |
| **RG4 replay** | `tools/server_replay_diff.sh build-parent build-child`: every corpus (R0) replayed by both binaries: **reply bodies, error codes and the end state (`sqlite3 .dump`, rows sorted) byte-identical**. The server log in two tiers (timestamps and tmp paths masked): lines matching the 1.12 interface patterns byte-identical; any other log difference empty **or listed in the commit message** | the proof for every R step |
| **RG5 tests/diff** | `tests/diff/run.sh` (3 flows × 3 targets, ~28 min) PASS | |
| **RG6 emulator** | `emulator/scripts/emulator_session.sh` seeded and `--new-player` PASS | the brief's gate scope: `server/` changed |
| **RG7 sessions** | the `port/scripts/*_session.sh` of the step's domain (table in 4.3) | |
| **RG8 smoke** | `port/scripts/smoke.sh` | |
| **RG9 offline-build refs** | `tools/check_no_380.sh` | |
| **RG10 docs** | `tools/check_server_docs.sh` (from R1): links, index fresh, READMEs, evidence manifest vs parent (section 3), no new agent mentions, the log patterns | |
| **RG11 inventory** | `tools/schema_inventory.py` output equal to the parent's except `file:line` attributions (normalized) | until PLAN-schema retires it |

**Declared log differences.** These change log text on purpose and say so in their commit messages:
- `ext::refuse`'s "`<Method> refused: <why> (error N)`" line on the core's refusals, next to `handle_request`'s "refused with error" line (server.cpp:2905; the latter is the one scripts read, and it is unchanged). Planned for R6c; **deferred to R7** (the one handler shape), so R6 stayed byte-identical in the log too (R6c/R6d notes). **Done in R7b**: the core's own reason lines became the `why` of that one line (e.g. "MissionStart refused: stamina 3 < cost 10 (error 10004)"); in the corpora only the tutorial's Login 19001 shows it.
- The `restore:` prefix goes (R10, server.cpp:382–391). **Done in R10d** (core/server.cpp `Server::init`, four lines; two per corpus in the replay log).
- R9 removes net/game.cpp's own time formatting.

**Why replay, not only tests/diff.** tests/diff compares the port with the emulator under masks (times, a running clock), so it can't show that a refactor is byte-for-byte neutral. RG4 runs the *same* request sequences on two builds of the server with a frozen clock and a fixed RNG seed, and diffs everything the server emits. It runs in seconds, needs no game, and catches reordered map keys (1.3), changed log text and changed SQL effects. **The clock follows the recording:** each request runs at the time `packets.log` recorded for it (through the R0 clock seam), not at one frozen instant. So stamina regenerates, rental and login days roll over, and a deep-space expedition's `closed_at` arrives, exactly as in the recorded session, and the replay stays deterministic. The `api-sweep` corpus carries synthetic times that cross a 04:00 reset.

The corpora (R0):

- the packet logs of the three tests/diff flows on the `emu` target (`soa-server --log-packets`: every request body is kept as `<n>-<Request>.bin` and decoded with `net::decode_request`, battle log included);
- the in-process packet logs (`soa --log-packets`) of the domain sessions: growth, party, deepspace, sphere211 (+ continue), rental, tower, events, campaign, gacha, restore_favor;
- `api-sweep`: a generated corpus that calls every registered method once with arguments drawn from the scratch state. It is the coverage floor; `--list-apis` tells which methods it misses.

Corpora are committed under `server/tests/replay/<name>/` as text (`requests.txt`: method, fid, ints, strs, vecs, battle log as hex). `tools/server_replay_record.py` converts a packet-log dir and **refuses any file that contains a player id other than `LOCAL00001`** (the sanitize rule).

A step whose RG4 isn't byte-identical is not a refactor. Either it is fixed, or the difference is the step's declared purpose, written in the commit message with the diff; that is only allowed for the S steps (PLAN-schema G4).

### 4.2 Order, interleaved with PLAN-schema

```
R0 -> R1 -> R2 -> S0 -> R3 -> R4 -> R5 -> S1 -> R6a..h -> R7 -> R8 -> R9 -> S2
   -> R10 -> S3 -> R11 -> S4 -> R12 -> R13 -> S5 -> R14 -> S6 -> R15 -> S7 -> R16 -> S8
   -> S9 -> R17 -> R18 -> S10 -> S11 + R19 -> (later) R20
```

- **As executed (2026-10-02, the integrator's order):** the readability steps run first (R0, R1, R2, R3, R4, R5, R6a–h, R7, R8, R9, then the domain cleanups R10, R11, R13, R14, R15, R16, R18), then PLAN-schema S0–S12, then R12 (after S4), R17 (after S9), S11 + R19. So R3 formats before S0, and a step whose text assumes an S step does today's part and leaves the S part for phase 2 (noted at the step).
- **R0–R2 first.** They add tools and docs only, so they can land while S0 is in review.
- **S0 before R3–R5.** S0 rewrites the 64 positional inserts and the REPLACEs in place. Formatting or moving those files first would turn S0 into a rebase of every line it touches.
- **R4 before R5.** Renames are only safe once hook order no longer depends on file names.
- **R5 before S1**, so S1 creates `state/` inside the final tree and removes the 13 `ensure_schema` call sites from files already at their final paths. **S1 before R6–R8:** S1 moves `schema()` and `meta`/`set_meta`/`next_uid` out of server.cpp (~150 lines) and deletes the 8 `sqlite_master` probes, so the split starts from a smaller file with no lazy-schema calls. The one SQL wrapper (1.5) is done *with* S1, since it is the same code. This plan specifies only the NULL-semantics trap: the six call sites at server.cpp:542, 1420, 1642, 1787, 1790, 2479 keep `Db::one`'s "NULL → 0" through an explicitly named accessor, until R11/R15 look at each.
- **Domain cleanups go right before their schema step:** R10 → S3, R11 → S4, R13 → S5, R14 → S6, R15 → S7, R16 → S8, R18 → S10. The cleanup is byte-identical (RG4); the schema step that follows is then a small diff on readable code.
- **R12 (typed ids) after S4,** because S4 makes "no character" a NULL instead of 0, and the id types encode that (`std::optional<CharacterUid>` at the reference columns). **R17 (time types) after S9,** because S9 makes every stored time an INTEGER `*_at`.
- **S11 and R19 together:** both make their checks permanent gates.
- **After R9 the domain steps are independent folders.** They can run as parallel agents in their own worktrees, merged one at a time, each re-running RG4 on the merged parent (docs/merge-gating-lessons: the selftest stays green at every merge).

### 4.3 The steps

Each step is its own commit (or the few listed), on a branch off `linux-port`, committed by path. A step is merged when its gates pass. "Byte-identical" means RG4.

**R0: the proof harness and the evidence manifest** (tools + test-only seams; no rule code).
- `core/clock` test seam: `set_clock_source(fn)` (default `time(nullptr)`), so a replay can freeze the server clock. It is additive: `--clock` behaves as before.
- `soa-server --replay DIR --out OUT [--seed-rng N]`: a scratch state from `--seed` (default the test seed), each request through `submit` / `handle` / `error_code`, the clock set to the request's recorded time (4.1). It writes `OUT/<n>-<Method>.msgp`, `OUT/errors.txt`, `OUT/state.sql`, `OUT/server.log`.
- `tools/server_replay_record.py` (packet-log dir → `requests.txt`, LOCAL00001 check) and `tools/server_replay_diff.sh`.
- The corpora of 4.1, recorded on 2488055.
- `tools/server_evidence.py` (the 1.7 / section 3 manifest) and `soa-server --list-apis` (method → "core" / registering file).
- `soa-server --selftest --shuffle SEED`: runs the tests in a shuffled order, to find order dependencies before tests move.
- Gate: RG1, RG2, RG9; the replay of each corpus is stable (two runs of one binary are identical).
- **Done (2026-10-02, branch `port/srv-r0-r2`).** As built:
  - The corpora are `seeded`, `tutorial`, `event` (tests/diff's flows, `emu` target, recorded on 2eaaaf6) and the generated `api-sweep` (106 methods, no arguments). Each request is stored as the client's plaintext body (`wire` lines), decoded again at replay by `net::decode_request`, so the replay also covers the wire decoder. The replay drives `net::live_backend()` (soa-server's path: campaign hooks and `EndMissionTalk` included); replayed bodies equal the recorded ones byte for byte except Login's `r_ver` (no CDN is built in a replay). `server/tests/replay/README.md`.
  - **Deferred:** the in-process domain sessions' corpora (growth, party, deepspace, ...). `soa --log-packets` logs the arguments as text, not the request bodies; recording them needs the port's packet log to write each request (`server_replay_record.py` refuses such logs).
  - Extra: `tools/server_build_at.sh REV|. DIR` builds one revision's soa-server alone (server-only configure reusing `build/vcpkg_installed`, ~45 s), so RG4 needs no second full build; the log-line patterns of 1.12 are one list, `tools/server_log_patterns.txt`, shared by the replay's tier-1 comparison and the evidence check.
  - Measured with `tools/server_evidence.py` on 2eaaaf6: labels (a) 347 (b) 395 (c) 55 (d) 422 (as 1.7; the forms are "(x)", "(x:", "; x:" and ", x:"); client addresses 16 in comments and strings outside `net/ninja*`, 95 cipher constants there; 93 `+0x` offsets in comments (all of `server/`); 77 agent mentions; **7** broken section links (1.7's four, plus "CDN", "Gear (agent server-rules)" and "Premium and favor login bonuses (agent server-rules)", which name no heading's start).

**R1: documentation, no code.**
- `server/ARCHITECTURE.md` (2.6, describing *today's* files; updated by each later step).
- READMEs for `src/`, `net/`, `tests/`, `include/soaserver/`.
- `tools/server_index.py` + `server/API-INDEX.md` (from `--list-apis` and docs/api.md).
- The 4 broken section links fixed; server/README.md's test count; a "Comment conventions" section in server/README.md (sections 2.2, 2.5, 3).
- `tools/check_server_docs.sh` (links, index freshness, READMEs present, evidence vs parent; doc coverage is *reported*, not enforced).
- Gate: RG10, RG9.
- **Done (2026-10-02).** The broken links were seven, not four (R0's note): all fixed, in code comments and docs/api.md ("Banner images" and "Episode data" are table rows, now linked as `"Section", "Row"`). Also fixed: `net/gen/wire_decode.inc`'s header (and its generator `tools/api_wire.py`) named a `server/net/wire_decode.cpp` that doesn't exist (`wire.cpp` includes it). `tools/check_server_docs.sh` landed with R2 (the integrator's split). API-INDEX.md's handler lines come from the sources (the if-chain and the `ext::Api` lines) until R7's `SOA_API` records them.

**R2: `.clang-format`.**
- Added at `server/.clang-format`, matching today's style: Google base, `IndentWidth: 4`, `ColumnLimit: 150`, `AllowShortIfStatementsOnASingleLine: AllIfsAndElse`, `AllowShortLoopsOnASingleLine`, `AllowShortFunctionsOnASingleLine: All`, `AlignTrailingComments: Leave`, `BreakStringLiterals: false` (SQL literals stay whole), `ReflowComments: false`, `SortIncludes: Never` (the config is section 5).
- `net/ninja_*` and `net/gen/` carry `// clang-format off` regions or are excluded (cipher tables).
- `tools/format_server.sh [--check]`.
- No file is reformatted yet. Gate: RG1.
- **Done (2026-10-02)** with the system clang-format **18.1.3** (Ubuntu; installed by the user, so the tools use it instead of a pip wheel): the section 5 config unchanged; re-measured on R1: **964 changed lines in 62 of 93 files** (23,930 lines; 49 of them in R0's new replay.cpp), against 23.1.2's 915 in 89. Of the variants tried, `AllowShortIfStatementsOnASingleLine: AllIfsAndElse` gives the smallest diff (WithoutElse 1,086, OnlyFirstIf 1,055, Never 2,404). `net/ninja_*` and `net/gen/` are excluded by `server/.clang-format-ignore` (clang-format 18 honours it) and by the script. `tools/format_server.sh` refuses a clang-format other than major 18. `tools/check_server_docs.sh` (report-only; lost evidence and log lines fail) landed here rather than in R1.

**S0** (PLAN-schema).

**R3: one format-only commit.**
- `tools/format_server.sh` over `server/` (measured: 915 changed lines in 89 files of 23,361; mostly re-wrapped long calls and the lambdas' single-line bodies).
- `.git-blame-ignore-revs` gets the commit.
- Gate: RG1, RG2, RG4 (the binary's behaviour; object code changes only by `__LINE__`), RG11.
- **Done (2026-10-02), before S0** (the integrator's order, below 4.2: the readability steps first, then PLAN-schema; S0 rewrites the inserts on the formatted code). 62 files, 964 lines replaced by 1,318; outside string literals and comments only whitespace changed (checked token by token; `server_log.h`'s two macros gained line continuations); literals and comments byte-identical. RG4 identical on the four corpora; evidence: nothing lost; RG11: equal except file:line attributions, after the prep commit that lets `tools/schema_inventory.py` splice a run-time name across a line break (one roster reader in growth_tests.cpp became two sites because a line holding two queries was split: an attribution).

**R4: explicit module order.**
- `core/registry` stores each registration with an order key.
- `modules.cpp` holds one list, `register_all()`, that calls each module's `register_<module>()` in **today's basename order**. Static registration objects become functions; linking whole archives remains only for the tests. `register_all()` runs once inside the library (the first `Server::init()` and the scratch servers), so neither host changes.
- Moving tests (R5, R8 step 10, R10–R18) changes their **run order** (link order). Seeds don't change (by name), but the brief warns that a test can leave shared state behind (e.g. `master_global` unreadable). Such steps run RG2 twice, and once with a reversed order (`--selftest` gets a `--shuffle SEED` option in R0).
- A test `server/module-order` compares the hook order (`OnPlayerLoad`, `OnResponse`, `ClientMaster`, mission extras, `Grant`, `ItemExtra`) with a committed list.
- Registering one method twice is a startup error. Today the later file silently wins, and core methods shadow modules.
- Gate: RG1, RG2, RG4, RG6.
- **Done (2026-10-02, branch `port/srv-r4-r5`).** As built:
  - The static registration objects (`ext::Api reg(...)`, `OnPlayerLoad`, `Schema`, ..., `events::AreaExtra`) are gone; registration is a call, `ext::add_api({...}, fn)`, `add_player_load`, `add_response_hook`, `add_schema`, `add_grant`, `add_item_extra`, `add_client_master`, `add_mission_start_extra`, `add_mission_result_extra`, `events::add_area_extra`, made from one `register_<module>()` at the end of each module file, in the file's former declaration order. The registry is still `ext.cpp` (it moves to `core/registry` with R5/R7); the list is `src/modules.{h,cpp}` (20 modules: the 18 `api_*` files with registrations, `ext.cpp`'s `counters` table and `present_texts.cpp`'s table; module names are their own identifiers, not file names). The inline lambdas became named functions in place (bodies unchanged), e.g. `get_sphere211_info`, `load_titles`, `grant_gear_lottery`; the two one-line DeepSpaceMissionEnd(Now) lambdas and favor_drop's MissionStartExtra stay inline in the register function. Schema strings became `kSchema*` constants.
  - `register_all()` runs under `std::call_once` from every reader of the registry (`ext::find`, `api_sources`, `player_load`, `on_response`, `has_response_hooks`, `ensure_schema`, `find_grant`, `item_extra`, the mission extras, `client_master`, the event area list, `hook_order`), not from `Server::init()`: the CDN build's `client_master` can run before any server exists. Neither host changed.
  - Duplicates: a method registered twice, a module method the core answers (`core_methods`), or a content type granted twice is logged, `ext::registration_errors()` lists it and the first registration stays; soa-server exits 1 at startup and `server/module-order` fails on one. None exist.
  - `soa-server --list-hooks` prints every hook in run order (kind, module, file:line, detail); `tools/server_index.py` builds API-INDEX.md section 2 from it (its `link_order()` / `HOOK_RE` source parsing is gone; `API_RE` reads `add_api(...)`). The test `server/module-order` (`tests/module_order_tests.cpp`) pins the order per kind. Before committing, the new order was checked against the parent's API-INDEX.md section 2 (every kind identical).
  - Linking stays whole-archive (the tests still register statically); the CMake basename sort now orders only the tests (R5 drops it).
  - **Proof.** RG4 identical on the four corpora vs ea4b054; `--list-apis` identical. **The rename proof:** `git mv server/src/api_bonus.cpp server/src/zz_bonus.cpp` (its two player-load hooks would sort last). On ea4b054 that rename changes 11 replies of the corpora (api-sweep Login, CreatePlayer, GetPlayer, NoLoginStart, SimpleLogin; event and seeded NoLoginStart, Login; tutorial CreatePlayer, Login: LoginBonus / Achievement move after the other modules' keys) and the log order. On R4 the same rename replays identical. RG11: equal except file:line and function attributions (the lambdas' registration objects are named functions now). Evidence: nothing lost (one more `master_` mention: modules.h's comment). RG2 91/91, also `--shuffle 7`.

**R5: moves into the target folders** (whole files only, `git mv`; includes, CMake and references updated; 4 commits: `net/ninja/`; `core/`+`testing/`+`cdn/`+`master/`+`rules/` small files; `api/<domain>/` for `api_*.cpp`; tests beside their code).
- CMake: `GLOB_RECURSE` in the same commit as the first move. The basename sort goes (order is R4's now).
- Updated in the same commit:
  - the 26 external files that name `server/src/…`;
  - `tools/schema_inventory.py` (`SERVER_DIRS`, `OTHER_DB`, the `endswith` names);
  - docs/server-rules.md, docs/api.md, server/README.md, API-INDEX.md;
  - `check_server_docs.sh`'s path check, which flags any reference to a path that no longer exists.
- `include/soaserver/*` paths don't move.
- Gate: RG1–RG4, RG6, RG9–RG11.
- **Done (2026-10-02, branch `port/srv-r4-r5`), in the plan's 4 commits.** As built:
  1. `net/ninja/` (+ README). CMake: `GLOB_RECURSE` for `src/` and `net/`, the basename sort gone (tests now run in path order); the configure-time include guard accepts an include naming a file under `server/src` (`core/` shares a name with the port's).
  2. `core/` (`server.cpp`, `ext.cpp`, `modules.{h,cpp}`, `support.cpp`, `battle_log.cpp`, `server_log.h` → `log.h`, `event_clock.cpp` → `clock.cpp`), `testing/testing.cpp`, `cdn/{cdn,adld}.cpp`, `master/{gacha_pools.{h,cpp},npc_status.cpp}`, `rules/{mission_rules.{h,cpp},growth_rules.h}`.
  3. `api/<domain>/`: `daily/{login_bonus, premium_and_favor_bonus}`, `campaign/campaign`, `deepspace/deepspace`, `events/{event_missions, ranking, world_boss, favor_drop, enable_events.{h,cpp}, event_extras.h}`, `social/rental.{h,cpp}` (was api_follow + rental.h), `player/{home_footer, titles, notice}`, `items/{gear, items}`, `growth/growth`, `shop/{shop, subscription}`, `sphere211/sphere211.{h,cpp}`, `tower/tower.{h,cpp}`, `favor/favor.{h,cpp}`, `presents/present_texts`.
  4. The tests beside their code: `tests/*_tests.cpp` → `cdn/cdn_tests`, `core/{clock_tests, modules_tests}`, `master/npc_status_tests`, `rules/rules_tests`, `api/events/{enable_events, event_extras, event_missions}_tests`, `api/social/rental_tests`, `api/growth/growth_tests`, `api/sphere211/sphere211_tests`, `api/tower/tower_tests`. `tests/` keeps `net/`, `ninja/`, `replay/`. Test names (the seeds) are unchanged.
  - **Whole files only**, so the multi-topic files keep their content under the name of their main target, and their split stays with its step: `api/daily/login_bonus.cpp` still holds the achievements (R16 → `api/presents/achievements.cpp`), `api/player/home_footer.cpp` the social stubs (R10 → `api/social/`), `core/ext.cpp` the registry, the SQL wrapper and the state helpers (R6/R7), `core/support.cpp` config/log/asset index/CHash32 (R6), and the core handlers stay in `core/server.cpp` (R8). `growth_rules.h` is in `rules/` while its four definitions stay in their module files (R6). No `state/` yet (S1).
  - Internal includes are src-relative (`"core/log.h"`, `"api/events/enable_events.h"`; the library's `-I server/src`); the port includes none of them. References were rewritten mechanically: `server/src/<old>` and `src/<old>` everywhere, a renamed file's bare name in docs and in C++ **comments only** (no string literal touched: the log lines and test names are the same), plus the stale `server/api_<x>.cpp` form in port comments and scripts. `cmake/vcpkg-triplets/x64-linux.cmake` keeps its comment naming `server/src/cdn.cpp`: any edit to a triplet changes every vcpkg port's ABI hash and rebuilds all dependencies (it did once here); `tools/check_server_docs.sh`'s path check skips that folder.
  - Tools: `tools/server_index.py` walks `src/` recursively and finds the core in `core/server.cpp`; `tools/schema_inventory.py`'s `OTHER_DB` and `endswith` follow the moves, and a `*_tests.cpp` beside the code counts as a test file as `server/tests/` did; `tools/format_server.sh`, `.clang-format-ignore` and `tools/server_evidence.py` know `net/ninja/`. PLAN-schema.md's inventory snapshot keeps the old paths (a note there says so).
  - **Proof per commit:** RG4 identical vs ea4b054 (4 corpora); `--list-apis` identical but for the registering file, `--list-hooks` order unchanged; RG2 91/91 twice and with `--shuffle` (11, 13, 17, 19); RG11 equal once file:line, function and file-name attributions and row order are normalized; evidence: nothing lost; format check clean; API-INDEX.md regenerated; no missing `server/` path; a README in every `src/` folder.

**S1** (PLAN-schema), with the one SQL wrapper `state/sql.{h,cpp}` (1.5), keeping the six NULL-semantics call sites as they are. `ext::Sql` stays as an alias in `include/soaserver/ext.h` for the port's test.

**R6: shared helpers**, one commit per letter, each byte-identical and each replacing every copy at once:
- **a. `core/time`:** format and parse variants, `day_start`, `Window`. The 4 `open_at`, 5 `fmt_local` and the parse copies go (1.5).
- **b. `master/master`:** `global_u32/f/str`, level tables, role cap / next EXP, `text(message_id)`, mission table lookup (`find_mission`). The raw `master_global` queries go.
- **c. `core/errors.h`:** generated (2.4), every literal code replaced. Refusal log texts unchanged (1.12).
- **d. `core/response`:** one `body()`, `with_player_state`, `refuse`, `Value::find_mut` / `get_u`.
- **e. `core/wallet`:** `spend_coins` (5 copies), `add_fol`, `add_stock`, `add_free_coins`. The label drift (1.7) is recorded for R16/R18, not changed here.
- **f. `core/request_args`:** args structs for the core handlers. Modules get theirs in their domain step.
- **g. One asset gate:** `AssetIndex` plus one test override. `events::set_asset_check` and `sphere211::set_asset_check` forward to it (the port test uses the first).
- **h. The campaign on `Value`:** api/campaign's byte splicer (`Mp`, `splice_data`, `merge_maps`) replaced by `mp_decode` → merge → `mp_encode`. This is the riskiest: integer widths and key order must come out the same. RG4 plus `server/campaign-splice` and tests/diff's seeded flow.

Gate per letter: RG1–RG4, RG10. Plus RG5 for c, h; RG6 for h; RG7 `campaign_session.sh`, `restore_missions.sh` for h.
- **As built (2026-10-03, branch `port/srv-r6`, off 88df715; one commit per letter, each RG4-identical on the four corpora vs 88df715, evidence: nothing lost, format clean).** The one SQL wrapper is not part of R6: it is S1's (above), so it waits for phase 2 (the integrator's order); R6 adds no SQL code and leaves the six "NULL reads as 0" sites in `core/server.cpp` on `Db::one`. **Done in PLAN-schema S1a** (2026-10-03): the one wrapper is `soaserver/sql.h` / `state/sql.cpp` (public, since the port's test uses `ext::Sql`), `Db` is gone (PLAN-schema S1's as-built note).
  - **a.** `core/time.{h,cpp}`: `format_time` (declared public in `soaserver/server.h`, so `net/game.cpp`'s copy went now rather than with R9), `format_time_or_empty` (favor's: "" for t ≤ 0), `parse_time` (the lenient `sscanf` one), `parse_time_strict` (favor's `strptime`), `parse_time_or_epoch` (`config.h` `parse_clock` now forwards to it), `parse_day_and_time` (was `mission_rules` `local_time`), `day_start(t, reset_hour)`, `add_years`, `year_of`, `Window` / `open_at(opened_at, closed_at, t)`. Gone: server.cpp's `fmt_time` / `parse_time`, the `fmt_local` / `parse_local` of event_missions, sphere211, favor and net/game.cpp, sphere211's `add_years`, event_missions' `year_of`, `growth_rules::day_start` (login_bonus.cpp), rental's `day_start(Ctx&)`, sphere211's `rental_day` body (now a one-line `day_start` call), the four `open_at(Ctx&, ...)` (login_bonus, premium_and_favor_bonus, shop, deepspace), and the inline windows of `gacha_open`, tower, notice and sphere211's floor-transfer lookup (same semantics: both ends inclusive, empty = open). Kept as variants with their own semantics: `favor_day` (a day *index*, -1 for t ≤ 0), `events::window_open` (year shift), `in_window` (campaign, string compare), `achievement_open`, deepspace `open_client` (both clocks; now two `open_at` calls), notice's `date(t, fmt)` (other formats), the tests' private helpers. `Ctx::fmt_time` / `parse_time` stay (R7 reshapes `Ctx`); they call the new functions. New test `server/time-variants` pins how the variants differ (92 tests).
  - **b.** `master/master.{h,cpp}` (on `ext::Sql` over the master handle): `global_str`, `global_u32` (the core's reading: an empty value is 0), `global_u32_unless_empty` (api/favor/'s reading: empty = the default; no 3.7.0 `master_global` value is empty, so the two agree on the data, but they stay two names), `global_f`, `player_level_rows`, `stamina_max`, `player_level_max`, `player_next`, `role_level_cap`, `role_next`, `text`, `find_mission` / `MissionRef`. The `Server` members of the same names, `ext::global_f` and `ext::text` forward to them (the `Ctx` lambdas are unchanged until R7). The raw `select value from master_global` queries went: server.cpp (`latest_episode_version`, `a_ver_android`, `Default_Character_<k>`, `kiyaku_version`, one test), gear.cpp (3), deepspace.cpp (1), favor.cpp's own `global_str` / `global_u32` (and its `Q`-based query). **NULL semantics kept:** `role_level_cap` was a `Db::one` with default 40 (one of 1.5's six sites): it is now a query whose row callback reads `Row::i` (a NULL `level_max` still reads 0, no row still 40), commented as such. Only side effect off the replay: a missing `master_global` table now logs `sql prepare: ...` from favor's lookups instead of `favor: sql error ...`.
  - **c.** `core/errors.h` is generated by `tools/gen_error_codes.py` (the name table is in the script, each with the label of why that code; the client's text as the comment; the 124 unused codes as a comment table; `--check` is wired into `tools/check_server_docs.sh`). Every refusal code literal in the library's code is a name now: the 95 `ext::refuse(..., N)` calls in 8 module files (through an `ext::refuse(..., ErrorCode)` overload in errors.h, so `ext.h`'s public `u32` signature is unchanged for the port), the core's 7 `refuse = N` sites and `kErrNoPlayer` (gone; `ErrorCode::kNoPlayer`). **Not changed:** every log text (the core's refusals still log only their own lines and `handle_request`'s "refused with error"; adding `ext::refuse`'s line to them belongs to the one refusal path, R6d/R7), the codes in comments, and the tests' expected codes (`t.expect_eq(code, 10206u, ...)`, 20 sites): they pin the number the client receives, so they stay numbers on purpose.
  - **d.** `core/response.{h,cpp}`: the one `ext::body` (ext.cpp's; server.cpp's static `body` now forwards to it, byte-for-byte the same encoder), `ext::with_player_state(Ctx&)` (`body(c.base_data())`; home_footer and rental use it) and `ext::refuse` (moved from ext.cpp). The core: `Server::with_player_state()` (5 `return body(base_data())`) and `Server::refused(ErrorCode)` (5 `refuse = N; return body(base_data());` pairs; the two inside the gacha lambda, which set `d` rather than return, stay explicit). No log line added: the core's refusals still log their own reason lines (the plan's declared R6c difference, `ext::refuse`'s line on the core's refusals, is left to R7's one handler shape, so this step stays byte-identical in the log too). `msgpack.h`: `Value::find_mut(k)` (the 3 `const_cast<Value*>(x.find(k))`) and `Value::get_u(k, dflt = 0)` (every unchecked `find(k)->u` in library and test code, and the `find(k) ? find(k)->u : d` forms; a missing key now reads `dflt` where it crashed before).
  - **e.** `core/wallet.{h,cpp}` (namespace `wallet`, on the state / master handles): `coins`, `split(have, price, paid_only)`, `covers`, `take`, `spend_coins`, `add_free_coins`, `fol`, `add_fol`, `stock_count`, `add_stock`. The five "free coins first" copies are one: shop (ExItemShop), items (StaminaHeal) and sphere211 (continue) call `spend_coins`; deep space's quick return and the core gacha keep their order (deep space takes its items between the check and the payment; the gacha checks tickets too and logs the coins it saw) through `coins` / `covers` / `split` / `take`. The core's `grant()` FOL (type 3) and coin (type 4) branches call `add_fol` / `add_free_coins`: its FOL update gains `add_fol`'s floor at 0 (`max(0, min(fol + n, cap))` for `min(fol + n, cap)`; n is unsigned, so the same values). `ext::fol` / `add_fol` / `stock_count` / `add_stock` forward to it. **Not merged:** the core's own stock writes (the grant's and MissionEnd's `count + excluded.count`, the ticket takes `count - ?`): they don't cap or floor, so they aren't `add_stock`; recorded for R13. **Label drift recorded, not changed** (section 3 / 6): "free coins first" is (c) at shop, StaminaHeal and Sphere 211's continue (and docs/server-rules.md "Stocks and wallet"), (d) at the gacha and deep space's quick return; `wallet::split`'s comment lists both, for R16 / R18 to make one.
  - **f.** `core/request_args.h` (namespace `args`; `int_at(r, k, dflt)`, `str_at(r, k)`): `CreatePlayerArgs`, `UpdateTutorialArgs`, `UpdateViewArgs`, `UpdateKiyakuVersionArgs`, `UpdatePlayerNameArgs`, `UpdatePartyArgs` (party 1 by default), `UpdatePartySetArgs`, `SetAssistArgs`, `UpdateHomeArgs`, `MissionStartArgs`, `MissionEndArgs`, `MissionTalkArgs` (`has_mission`: the old `ints.size() > 1` test), `BoxGachaArgs` (count ≥ 1, 1 when missing), `GachaIdArgs` (ResetBoxGacha, GetGachaRate), `GachaArgs` (the Gacha family and GachaTicket: `n`, the second integer), `GetPresentArgs` (the vector, else the one id). Every positional read in the core handlers (`r.ints` / `r.strs` / `r.vecs`; 0 left outside `submit`'s log line) goes through them; widths and casts as before. The handlers keep their local names (`helper_arg`, `helper_own` ...) until R10–R15 rename them. The core methods without arguments (Login, GetPlayer, GetServerTime, GetMissionList, GetPlayMission, MissionFailed, MissionRestart, GetGachaInData, GetBoxGacha, PresentList) have none; the favor branch's arguments are api/favor/'s (R16).
  - **g.** `core/assets.{h,cpp}`: `available(rel)` (the override, else true without any asset source, else `found`), `found(rel)` (was `events::asset_exists`: the `AssetIndex` under `builtin_data/` and `assetpack/`, with `etc2/` and `etc2/hi/`), `no_source`, `set_override` / `has_override`, `generation()`. `events::set_asset_check` and `sphere211::set_asset_check` are now the **one** override (both public names kept: the port's test and the module tests use them); the two modules' mission-verdict caches start over when its generation changes (before, each setter cleared only its own cache, and Sphere 211 never saw the events' predicate). Off the tests nothing is ever overridden, so the gates answer as before; the selftest passes in link order and shuffled (7, 11). `events::asset_exists` / `asset_available` forward to `found` / `available`. **Not merged:** deep space's `area_assets` asks the `AssetIndex` for one exact name (`builtin_data/Image/etc2/<resource>.aif`) and only in the game (`in_game`), so it isn't the gate's predicate (no `assetpack/`, no other quality folder, no override): moving it onto the gate could offer areas the game can't draw, so it stays for R18, commented as such.
  - **h.** api/campaign on `Value`: `Mp`, `mp_skip`, `mp_map_header`, `mp_str_at` and the byte-level `merge_maps` / `splice_data` are gone. The builders (`build_world_map_list`, `build_player`, `build_active_mission_list`) return `Value` (the same keys in the same order; `Mp`'s size classes are `mp_encode`'s for every size below 65,536, so the bytes are the same); `splice_data(Value& root, add)` / `merge_maps(Value, Value)` keep the order rule (the kept `data` entries in order, then the additions in order; a map merged into an existing map: the old entries the new one lacks, then the new ones). `on_response` decodes the body (`decode_body`: it must be one value that `mp_encode` writes back byte for byte), splices and encodes. **The one behaviour difference:** a body that isn't in the encoder's canonical form (or is malformed) is now left alone with the existing "unexpected response shape" warning, where the byte splicer would have spliced around it; no such body exists: every reply of the four corpora (308) and every `port/fakeapi/responses/*.msgp` (10, the in-process fallback) round-trips byte for byte. **Proof:** a temporary differential test (not committed) ran the old builders and splicer against the new ones in one binary: 400 random campaign states (cleared sets, last play, seeded, world-map episode) x the three builders (both `build_player` forms), and 19,260 splices of the old vs new path over 321 bodies (the 308 replay replies, the 10 fake-server files, `{}`, empty, a non-map): 0 differ. `server/campaign-splice` is now on `Value` with more cases (replacement order, a non-map value replacing a map, a missing `data`, a non-canonical and a truncated body). `active_mission_list_msgpack()` (public) is `mp_encode` of the builder.
  - **The batch's expensive gates (once, on R6h):** `tests/diff/run.sh` all flows: seeded and event PASS; tutorial failed on all three targets alike at the data dialogs (the clients at 2-9 fps while two of this batch's port sessions and another agent's emulator ran alongside; the server had answered every request, and RG4's tutorial corpus is identical), then PASS when rerun alone. `emulator/scripts/emulator_session.sh` seeded PASS (coins debited 300000 -> 297500). `campaign_session.sh` PASS. `restore_missions.sh` PASS (two step-up steps, 300000 -> 292500 coins, the 10004 dialog) on the second run; the first missed its tap on the step-up banner under the same load (no Gacha request was sent). `soa --selftest "server/"` 76/76. RG11: `tools/schema_inventory.py` gives the same tables and columns as 88df715; only function attributions move (`wallet.cpp` `take` / `coins` / `add_fol` / `add_free_coins`, `master.cpp`).

**R7: one handler shape.**
- `RequestContext` carries `refusal`, the battle log (instead of `g_request_log`), `mission_override`, `restarting` and `test_log_value`. `in_game` is renamed to say what it is ("use the request's battle log").
- `Ctx` becomes a class whose members are services: `state`, `master`, `clock`, `player`, `roster`, `rewards`, `wallet`, `refuse`. They are real functions, so "go to definition" works; no `std::function` lambdas.
- Every core handler becomes `Response h(Ctx&, const Request&)`. `core_mission` becomes a direct call with an explicit override argument.
- api_title.cpp's `g_added` moves into `RequestContext`.
- Gate: RG1–RG6.
- **Done (2026-10-03, branch `port/srv-r7-r9`, off 99338a0), in two commits.** As built:
  - **R7a.** `src/core/request_context.h`: `RequestContext` {`refusal`, `battle_log` (was `g_request_log`), `live` (was `in_game`: a live server, whose battle values come from the request's battle log and whose deep space asks the asset index), `test_log_value`, `logged_in` (Login's flag; `Server::handle` copies it to the server's `logged_in()` after the request), `titles_added` (was api/player/titles.cpp's `g_added`)}. `Server::handle` makes a fresh one per request, `with_live_server` and the scratch servers one per run. **Deviation:** `mission_override` and `restarting` are not context fields but explicit arguments of `start_mission(ctx, r, override, restarting)` (the core mission is the only reader); `ext::Ctx::core_mission` and MissionRestart pass them.
  - `ext::Ctx` keeps its flat member names (`c.now()`, `c.base_data()`, `c.grant(...)`, `c.st`, `c.m`), now **member functions** defined in one file (core/context.cpp since R8.11) instead of `std::function` lambdas, plus `request` and `pools`. **Deviation:** not grouped into service objects (`ctx.clock.now()`, `ctx.player...`): that would rewrite ~1,000 module call sites that the domain steps (R10–R18, with the `c` → `ctx` rename of 2.2) touch anyway; the grouping is left to them. Tests set `ctx.test.now` / `event_now` (fixed clocks) and `ctx.test.on_refuse` (an observer) instead of assigning the lambdas; `c.in_game` is `c.live()`; `Scratch::set_in_game` is `set_live`.
  - Every core handler is a free function `(ext::Ctx&, const Request&)`; the core's helpers too (their bodies unchanged; `st` / `m` became `ctx.st` / `ctx.m`, which are `ext::Sql`). The core's `Db::one` read a NULL as 0 where `ext::Sql::one` reads the default: the five sites with a non-zero default keep it through `one_null_as_zero` (core/server.h; S1 / R11 / R15 decide each, 1.5). **Decided in PLAN-schema S1a:** all five keep the named read, each commented at its site (the data never holds a NULL there); it is the one wrapper's function now (`soaserver/sql.h`). `core_mission` reports a refusal raised during its own call (production never has one before it).
  - **R7b** (the declared log difference of 4.1, deferred from R6c): the core's refusals go through `ext::refuse` / the new `ext::refusef` (printf-style reason; core/response.h) like the modules'; the core's own reason lines became the `why` of "`<Method> refused: <why> (error N)`". RG4: only the tutorial corpus's Login 19001 line differs (I → W, the new text); "refused with error" unchanged.
  - Proof per commit: RG4 identical vs 99338a0 (R7b: the one declared line), `soa-server --selftest` 92/92 (also `--shuffle`), `soa --selftest "server/"` 76/76, evidence: nothing lost, format clean, RG11 the same tables and columns.

**R8: split server.cpp** (one commit per destination, in this order):
1. `rules/` and `state/kvs` + `state/seed`. `server.h` keeps declaring `rules::` (or includes `rules/rules.h` through a public `soaserver/rules.h`): the port's zz_server_guest_test.cpp:37 uses `server::rules`;
2. `api/entry`;
3. `api/player` (player/party/home and the info builders);
4. `api/missions` (start, end, drops, campaigns, play state);
5. `core/rewards`;
6. `api/gacha` (+ step-up, box, rates);
7. `api/presents`;
8. `api/favor`'s dispatch branch;
9. `testing/scratch` (one scratch server instead of two);
10. the tests beside their domains.

The dispatcher's if-chain becomes `SOA_API` registrations. Its two conditional routes become explicit:

- `GetServerTime` / no-player `GetPlayer` / `NoLoginStart` → time only;
- `GetGachaRate` with/without pools.

Core methods register first, so today's precedence (core before modules) is kept. `--list-apis` must list the same 106 methods before and after. Functions over ~80 lines are split into named steps (2.5): `api_mission_start` 275, `api_mission_end` 218, `api_gacha` 202, `person_status` 116.

Gate: RG1–RG8, RG10, RG11; RG7 `restore_session.sh`, `battle_session.sh`, `gacha_session.sh`, `tutorial_session.sh`, `party_session.sh`.

- **Done (2026-10-03, branch `port/srv-r7-r9`), one commit per destination, each RG4-identical vs the R7b commit (four corpora, log included), `--list-apis` the same 106 methods and fids, `soa-server --selftest` 92/92, evidence: nothing lost, format clean.** As built:
  1. **R8.1** `rules/rules.cpp` (`rules::`; `soaserver/server.h` still declares them), `state/kvs.{h,cpp}` (the Game.xml codec), `state/seed.{h,cpp}` (`seed`, `real_seed_save`, `kLocalPlayerId`), `core/ids.h` (the uid scheme), `core/server.h` (internal: `file_exists`, `first_existing`, the meta helpers, `one_null_as_zero`, `event_clock_of`). **For S1:** `Server::schema()` and `meta` / `set_meta` / `next_uid` / `has_player` stay defined in `core/server.cpp` (declared in `core/server.h`); S1 moves them into `state/`. `tools/schema_inventory.py` reads the meta helper calls in every file that includes `core/server.h`.
  2. **R8.2** `api/entry/entry.{h,cpp}`. The if-chain becomes registrations domain by domain: **`ext::add_core_api`** (ext.h) registers the core's APIs, first in `core/modules.cpp`'s list; unlike a module's API, `ext::ensure_schema` doesn't run before a core handler, as before (with it, the api-sweep's Login answered `Player.gear_num`, which `player_value` sends only once the gear table exists; PLAN-schema S1 makes the schema eager and drops the difference). **Done in PLAN-schema S1b:** the exception and `is_core_api` are gone (`add_core_api` stays a plain registration, the index's core marker); every fresh state's first player load now carries `gear_num: 0`, as soa-server's wire route always did (its bridge made the tables before Login): a declared reply difference, listed in PLAN-schema S1's as-built note.
  3. **R8.3** `api/player/{player_info,party}.{h,cpp}`, `api/player/home.cpp`. GetPlayer / NoLoginStart: one handler that answers data.Time without a player.
  4. **R8.4** `api/missions/` (`missions.h`; `mission_start`, `mission_end`, `drops`, `campaigns`, `play_state`.cpp); `core/rewards.h` (Drop, Added).
  5. **R8.5** `core/rewards.cpp` (`grant`, `add_character`).
  6. **R8.6** `api/gacha/` (`gacha.h`; `gacha`, `stepup`, `box`, `rates`.cpp); GetGachaRate's two routes are one handler.
  7. **R8.7** `api/presents/presents.{h,cpp}`.
  8. **R8.8** `api/favor/favor_api.cpp`. The if-chain is gone: `Server::dispatch` is `ext::find`; `ext::core_methods()` is gone (a module registering a core method is a duplicate: the core registers first); `--list-apis` names every method's registering file.
  9. **R8.9** `testing/scratch.{h,cpp}`: one `ScratchServer` (options: the gacha pools; the run's `--fail` / surprise options off) behind the library tests, `ext::with_scratch_server` and `testing::Scratch`. `core/server.h` declares `struct Server` and `Db`; `tools/server_index.py` reads registrations only.
  10. **R8.10** the 14 tests beside their domains (`rules/rules_tests.cpp`, `state/{kvs,seed}_tests.cpp`, `api/missions/missions_tests.cpp`, `api/gacha/gacha_tests.cpp`, `api/entry/entry_tests.cpp`, `api/player/player_tests.cpp`, `core/server_tests.cpp`); names unchanged; RG2 twice and with `--shuffle`.
  11. **R8.11** (extra) `core/context.cpp` (the `ext::Ctx` services) and the server clock in `core/clock.cpp`.
  12. **R8.12** the four long functions as named steps over a state struct (each step's body verbatim, binding the fields it uses): `start_mission` (12 steps), `api_mission_end` (11), `api_gacha` (5 + 2), `person_status` (4); the longest step is 80 lines.
  - `core/server.cpp` is 440 lines: the server object, the dispatcher, the meta helpers, the public request API. **Not done here:** the `SOA_API` macro of 2.5 (`ext::add_core_api` / `add_api` in each domain's `register_<name>()` keep R4's explicit order; the index reads the registrations); renaming `api_*` handlers after their API (2.2) is the domain steps'. The batch's expensive gates ran once, after R9 (below).

**R9: one request lifecycle for both hosts.**
- `server::answer(const Request&) -> Reply { body, error_code, handled }` in `core/lifecycle.cpp`. It contains the campaign's `on_request` / `on_response` and `EndMissionTalk` (today in fakeapi.cpp and net/game.cpp:30–85, 1.2).
- `handle()`'s dead `file` parameter goes. Old signatures stay as thin wrappers for one merge wave.
- **Port-side edits:** fakeapi.cpp:418/420/452/619/620/693 and restore_campaign.cpp call `answer`. net/game.cpp's `LiveBackend` shrinks to `answer` + transport; its `fmt_local` goes.
- Gate: RG1–RG8, wire/inproc-parity (port test), RG5 on all three targets (both hosts' replies).
- **Done (2026-10-03, branch `port/srv-r7-r9`).** As built:
  - `src/core/lifecycle.cpp`: `server::answer(const Request&, const Fallback&) -> Reply {body, error_code, handled}` and `server::end_mission_talk(mission)` (events, else the story campaign), declared in `soaserver/server.h`. `answer` is soa-server's former `LiveBackend::call` order exactly: EndMissionTalk -> the scene's effect, then GetPlayMission's answer with the campaign's data; else `submit`, `campaign::on_request`, `handle`; not handled -> the host's `fallback()` body; accepted or not handled -> `campaign::on_response`. The fallback is the host's: soa-server's `{data: {Time}}`, soa's file of its fake-server directory (or `{}`).
  - `handle(fid, out)` without `file`; `handle(fid, file, out)` stays as a wrapper for one merge wave. `Server::handle` / `handle_request` / `dispatch` lost it too.
  - **soa-server**: `net/game.cpp`'s `LiveBackend::call` is `answer` + the `{Time}` fallback + `kNotHandled`; its `campaign_reply` and `end_mission_talk` are gone.
  - **soa (port glue, the expensive gates' reason)**: the FakeApiCaller hooks keep the request (`server_port::remember`, `take`; `capture` = `inproc_request` + `remember`) instead of submitting it, and `ServeProgress` answers each queue entry with `server::answer(take(fid), file fallback)`; the GetWorldMapInfoList hook keeps its request instead of calling `campaign::on_request`. `h_end_mission_talk` calls `server::end_mission_talk` and still submits the EndMissionTalk request itself (its "request EndMissionTalk" line, read by `episode_movie_session.sh`) before queueing GetPlayMission (FakeApiCaller has no EndMissionTalk entry to answer). `restore_campaign.cpp` no longer exists (its EndMissionTalk hook became fakeapi.cpp's before this step).
  - **Port-side differences (tier 2, the port's log only):** a request's "request X (fid ...)" line and the campaign's `on_request` now come when Progress answers it (a frame after the client made it), in the queue's order, as on soa-server's wire; GetWorldMapInfoList gets a "request" line (it is submitted like the others now); "fid ... from the local server (N bytes)" counts the body with the campaign's data; the campaign's "unexpected response shape" warning names the method, not the canned file. A queue entry without a kept request logs a warning (none expected: every queueing hook keeps one).
  - Proof: RG4 identical vs b754465 (four corpora, log included: the event and tutorial corpora carry EndMissionTalk), `soa-server --selftest` 92/92, the port's `server/`, `wire/` and `fakeapi/` selftests, then the batch's expensive gates.
- **The R7–R9 batch's expensive gates (once, on the R9 commit, run one at a time):** `tests/diff/run.sh` all flows PASS (seeded, tutorial, event; emu / port-server / port-inproc); `port/scripts/restore_session.sh` PASS (battle cleared, 10-draw 300000 -> 297500); `port/scripts/events_session.sh` with clock 2020-05-29 15:00:00 PASS (daily mission, the story scene's EndMissionTalk, the battle with the event NPC helper); `emulator/scripts/emulator_session.sh` seeded PASS; full `soa --selftest` 102/102; the port's `server/` 76/76, `wire/` 7/7 (wire/inproc-parity), `fakeapi/` 5/5.

**S2** (PLAN-schema: drop the dead tables; the seed's `planets` insert is in `state/seed.cpp` now).

**Per-domain cleanups (R10–R18).** Each does, for its folder:

- the naming of 2.2;
- args structs;
- the 2.5 doc block on every handler and hook;
- named constants and enums for its literals;
- comment cleanup (section 3) and label drift fixed in code and docs together;
- the domain README;
- its tests beside it, renamed `<domain>/…` (test names are seeds: renaming changes the seed, so RG2 is rerun twice for flakiness);
- functions over ~60 lines split.

All of it byte-identical (RG4). Each is followed by its schema step:

| Step | Domain (folders) | Then | RG7 sessions |
|---|---|---|---|
| R10 | entry + player (login, new player, tutorial, player info, home, titles, notice, footer) | S3 (meta keys → `player` columns) | `tutorial_session.sh`, `newplayer_session.sh`, `home_session.sh`, emulator `--new-player` |
| R11 | roster, party set builders, assist, growth | S4 (the roster merge) | `growth_session.sh`, `party_session.sh`, `restore_favor_session.sh` |
| R12 | typed ids across `core/`, `state/`, `api/` (2.3), in 3–4 commits by folder | — | all RG7 sessions once |
| R13 | items, gear | S5 | `growth_session.sh` |
| R14 | parties (UpdateParty, UpdatePartySet) | S6 | `party_session.sh`, `battle_session.sh`, `restore_missions.sh` |
| R15 | missions (start/end/drops/campaigns/play), tower, rental helpers | S7 (`play` + `play_member`) | `battle_session.sh`, `restore_missions.sh`, `campaign_session.sh`, `tower_session.sh`, `rental_session.sh`, `deepspace_session.sh` |
| R16 | presents, achievements, login bonus, daily, favor | S8 (presents) | `restore_session.sh`, `events_session.sh`, `restore_favor_session.sh` |
| — | — | S9 (times and booleans) | per PLAN-schema |
| R17 | time types `ServerTime` / `EventTime` (2.3) | — | `events_session.sh`, `sphere211_session.sh`, `deepspace_session.sh` |
| R18 | deep space, Sphere 211, events (missions, ranking, world boss, favor drop, enable-events), gacha box / step-up, shop, subscription, campaign; `cdn/` split (`Tree::build` 272 lines) | S10 (module tables) | `deepspace_session.sh`, `sphere211_session.sh`, `sphere211_continue_session.sh`, `events_session.sh`, `gacha_session.sh`, `campaign_session.sh` |

Gate for each: RG1–RG4, RG6, RG8, RG10, RG11 and the sessions listed; RG5 once per pair (cleanup + schema step).

- **R10 done (2026-10-03, branch `port/srv-r10`, off 487e3f6; run in parallel with R11, R13–R14 and R16, so it touched only its own functions in shared folders), four commits, each RG4-identical vs 487e3f6 on the four corpora (R10d: the declared log lines only), `soa-server --selftest` 92/92 plain and `--shuffle 7` / `13`, evidence: nothing lost, format clean, `check_no_380` PASS, API-INDEX.md regenerated.** As built:
  - **R10a** the social stubs (Blacklist, GetRecentlyPlayedList, SearchPlayer) → `api/social/social.cpp`, module `social`, registered right after `home` in `core/modules.{h,cpp}` (no hook moved: `--list-hooks` and the replies unchanged; `--list-apis` differs only in the three methods' file). The footer's `OnPlayerLoad` gets the 2.5 block.
  - **R10b** `api/entry/`: handlers named after their APIs (`login`, `create_player`, `update_tutorial`, `update_view`, `update_kiyaku_version`, `update_player_name`, `get_server_time`), all with the 2.5 block; `create_player` as named steps (`insert_new_player`, `add_starters`); `kStarterCharacters`, `kStarterPartyId`, `kSearchIdFormat` / `kSearchIdModulo`; `api_time_only` → `time_only` (its one other caller, `api/missions/play_state.cpp`, updated). `api/player/player_info`: **only the player's own builders**: `player_value` → `player_info` (CPlayerInfo; steps `support_uid`, `add_stock_caps`, `add_meta_state`; key order unchanged), `wallet_value` → `wallet_info`, `api_player(ctx, r, bool login, bool create)` → `full_player_state(ctx, req, CdnKeys)`, `api_get_player` → `get_player`. `base_data`, `tick_stamina`, `player_id`, `home_same_role` keep their names (called from other domains and `ext::Ctx`). `tools/server_index.py` attributes the `OnPlayerLoad` hooks through `full_player_state(`.
  - **R10c** `update_home` in its own `api/player/home.h` (one line left `party.h`); titles: 2.5 blocks on SetTitle and its three hooks, `args::SetTitleArgs` **beside the module** (`titles.cpp`, not `core/request_args.h`: the modules' args structs stay in their domains), `kContentTypeTitle`; notice: 2.5 block on its hook, `kPageColumns`, `kMaxListedAreas`, `notice_page` as named steps. `// read by <script>` on the CreatePlayer, UpdateHome and SetTitle log lines.
  - **Left for R11 / R13 (their builders, in this folder):** the roster, party set and battle status builders (R11 moved them to `roster`, `party_set`, `person_status` and `assist.cpp`; merged into this branch before its final gates, `full_player_state` calls `roster_info` / `party_set_info`); `stock_value`, `items_value` (R13), with their "agent" mentions; `party.{h,cpp}` (R14).
  - **Label drift fixed** (code and docs/server-rules.md together): a playerless NoLoginStart / GetPlayer answering data.Time is (d) (two code comments said (b)); CreatePlayer's level 1 / EXP 0 is (d) (code said (a)); docs: UpdateView stores any kind but 0 as `view_status2` (docs said "refused"), the stale "UpdateTutorial not handled yet", "New player: no coins", "events closed" in the footer row. New (d) labels and register rows: `is_3d_home`, `updated_at`, `storage_stock`, `total_coin` / `android_coin`.
  - **Tests renamed** to their domain (new seeds): `entry/start-coins` (was `server/enable-events-start-coins`), `player/home-pc-id`, `player/home-footer`, `player/titles`, `player/notice`. They no longer match the port's `soa --selftest "server/"` filter (RG3); the full `soa --selftest` and `soa-server --selftest` run them.
  - **Behaviour noted, not changed** (section 6): UpdateHome with an unowned uid answers nothing (an empty body: the host's fallback) instead of a refusal with an error code.
  - **For S3:** the `meta` keys the player load reads (`tutorial_status`, `view_status`, `view_status2`, `kiyaku_version` written by api/entry; `title` by titles.cpp; `support_uid` by api/social/rental.cpp; `ds_time_saving_count` by api/deepspace) are read in one place now, `player_info`'s `add_meta_state` and `support_uid`; `titles.cpp`'s `selected_title` **writes** meta `title` (the first default title) on its first read, so S3's `'0' → NULL` mapping must keep "never chosen" distinct from "taken off" (0); `create_player` still writes `meta` `next_char_uid` / `next_item_uid` and the three entry keys, and inserts `player` positionally (14 values: S0's); the two `sqlite_master` probes in `player_info.cpp` (`gear_items`, `roster_ext`) are S1's.
  - **Merged with linux-port twice before the final gates** (R11 afeec13, R16 f182d32): RG4 vs the merged parent on the five corpora (growth included): bodies, codes and state identical, the log only R10d's lines; `soa-server --selftest` 94/94 (plain, `--shuffle 7`, `13`).
  - **The step's sessions (once, at the end, one at a time):** `port/scripts/tutorial_session.sh` PASS (CreatePlayer "Claire", ms00_001 109 hits, home, UpdateTutorial 9, 25 milestones) and `newplayer_session.sh` PASS (both on R10d before the merges); `home_session.sh` PASS (every home destination; on the R11 merge); `emulator/scripts/emulator_session.sh --new-player` PASS (UpdateTutorial 7 / 9, the new player, 25 milestones; on the R11 merge). tests/diff left to the integrator.
- **R11 done (2026-10-03, branch `port/srv-r11`, off 487e3f6; in parallel with R10, R13–R14 and R16), seven commits, each RG4-identical vs 487e3f6 (log included), `soa-server --selftest` 92/92 (also `--shuffle`), evidence: nothing lost, format clean, API-INDEX.md regenerated.** As built:
  - **prep: a `growth` replay corpus** (`server/tests/replay/growth`, 32 hand-written `req` lines on the seeded state). The api-sweep calls every method without arguments and no flow grows a character, so RG4 had replayed the growth handlers and SetAssist only as refusals. It buys materials from four item-shop sets, then calls every growth API (accepted and refused), SetAssist (moved, removed, refused), UpdateParty, GetPlayer and MissionStart (the `Character` / `PartySet` / `CPersonStatusInfo` builders on a grown party). It is RG4's proof for this step and the next domain steps.
  - **a. `rules/growth_rules.cpp`:** the four `namespace growth_rules` blocks (growth.cpp, items.cpp, shop.cpp, login_bonus.cpp) moved verbatim into one file, with the test (`rules/growth_rules_tests.cpp`). **Deviation:** the namespace keeps its name; `rules::growth` (2.2) would rewrite the call sites in R13's, R16's and R18's files, so each of those steps (or R12) renames its own.
  - **b. The roster builders in their own files** (moved verbatim, renamed after the client class, 2.2): `person_info` + `roster_info` (`api/player/roster.{h,cpp}`, were `person_value` / `roster_value`), `party_set_info` + `party_member_uids` (`api/player/party_set.{h,cpp}`, were `party_set_value` / `party_uids`), `person_status_info` and its four steps (`api/player/person_status.{h,cpp}`, was `person_status`), SetAssist (`api/player/assist.cpp`, `register_assist()` right after `register_party()` in `core/modules.cpp`, so the API order is the same). Callers renamed: `player_info.cpp` `api_player` (2 lines), `party.cpp` (2 lines; R14's handlers), `mission_start.cpp`, `core/context.cpp`. `player_info.{h,cpp}` keeps the player / wallet / stock / item builders (R10's and R13's).
  - **c. `api/growth/`:** args structs in `api/growth/growth_args.h` (beside the module; `core/request_args.h` stays the core's), handlers named after their API, the 2.5 block on all seven, `kWeaponItemType` / `kAccessoryItemType` / `kLimitBreakColumnOfRank` / `kSeedStats`, the named steps `limit_break_items`, `read_item_cost` / `take_cost_items` (evolution's and awakening's cost), comments (agent notes → what/why; labels added).
  - **d. The builders and SetAssist readable:** names (rows for their tables), `party_set_info` as `party_set_character` / `saved_party_sets` / `fill_unsaved_sets`, the duplicated `favor_level` assignment gone, SetAssist's 2.5 block; `api/player/README.md` rows for the new files.
  - **e. Label drift fixed in docs/server-rules.md** (the code is the evidence): 5.3 said evolution keeps the level (b/c); the server resets it to 1 (b, "Fixes found on the growth screens"). "Character growth" and its register row said the seeds aren't in the battle status (d); `person_status_info` adds them (b). "Assist": a refused pair isn't handled (no body) (d).
  - **f. Tests renamed:** `server/growth-apis` → `growth/apis`, `server/growth-rules` → `rules/growth` (RG2 twice, `--shuffle` 7, 11, 13). **Left:** `server/economy-apis` (shop, exchange, login bonus, achievements: R16 / R18) and the items half of `growth/apis` (compose, lock, sell, heal items: R13 splits it out); both in `api/growth/growth_tests.cpp`. **For RG3:** `soa --selftest "server/"` no longer selects the renamed domain tests; the filter becomes `"server/|growth/|rules/"` (each domain step adds its prefix) or the full selftest.
  - **Shared files touched** (minimal, for the merge): `api/items/items.cpp`, `api/shop/shop.cpp`, `api/daily/login_bonus.cpp` (their `growth_rules` block removed, nothing else), `api/player/player_info.{h,cpp}` (the moved builders removed, two call sites renamed), `api/player/party.{h,cpp}` (SetAssist removed, `party_set_value` → `party_set_info` twice), `api/missions/mission_start.cpp`, `core/context.cpp`, `core/modules.{h,cpp}` (`register_assist`), `api/player/README.md`, `server/src/README.md`, `server/tests/replay/README.md`.
  - **Found, not changed:** docs/api.md's AddStatusCharacter **Request** line says `u32 status kind`, `u32 amount`; the server reads a seed item id and a count (as `growth/apis` and the screen's preview do); recorded in `growth_args.h`. No `one_null_as_zero` site is in R11's domain (they are missions', gacha's and rewards').
  - **The step's sessions (once, on the last commit, one at a time):** `port/scripts/growth_session.sh` PASS (strengthening to the cap, evolution to ★6, limit break, gear set / removed / purified), `party_session.sh` PASS (set 2 saved, the battle uses it), `restore_favor_session.sh` PASS; `soa --selftest "server/|growth/|rules/"` 76/76. tests/diff left to the integrator.
  - **For S4** (PLAN-schema S4 lists them under "The code S4 touches"): the `roster_ext` upserts and reads (growth.cpp, `person_info`, `seed_stats`, with their `sqlite_master` probes), the `assist` table (`set_assist`, `person_info`), and every "none = 0" item / assist uid read (`person_info`, `party_set_character`, `equipment_stats`, `equip_item`, `update_character_info`).
- **R16 done (2026-10-03, branch `port/srv-r16`, off 487e3f6), in 8 commits, each RG4-identical vs 487e3f6 (four corpora, log included), `soa-server --selftest` 92/92 (link order and `--shuffle` 7 / 11 after the test moves), evidence: nothing lost (but R16f's declared labels), format clean, check_no_380 PASS.** As built:
  - **R16a** the achievements left `api/daily/login_bonus.cpp` for `api/presents/achievements.cpp` (verbatim), as two modules `login_bonus` and `achievements` where `bonus` was in `core/modules.cpp` (same hook order; `server/module-order`'s list updated).
  - **R16b** presents and achievements on the 2.5 template: handlers named after their API (`present_list`, `get_present`, `achievement_active_list`, `achievement_receive`), the doc block on every handler and hook, `present_box_info` (CPresentBoxInfo, built once instead of three times), `AchievementType`, `kStatusInProgress` / `kStatusAchieved`, `AchievementReceiveArgs`, `progress()` split.
  - `tools/schema_inventory.py` reads `count(ctx, ...)` and ternary keys (RG11 stays equal; see the counters finding below).
  - **R16c** the daily bonuses: `login_bonus` split (`default_tutorial_status`: a player rule, kept in this hook because it runs first; `grant_next_page`), premium / favor bonus helpers (`grant_premium_page`, `FavorTier`, `FavorLot`, `favor_lot_pool`, `favor_lot_line`), `kContentPremiumPass`. `growth_rules::next_login_day` was left in place; R11 moved it to `rules/growth_rules.cpp` (merged here).
  - **R16d** the favor APIs are two handlers (`update_favor_by_tap`, `use_favor_item`, with `UpdateFavorByTapArgs` / `UseFavorItemArgs` in `api/favor/`; 27 core registrations, the same 37 methods); `favor::handle` became `favor::tap` / `favor::use_item`; the other `favor.h` functions keep their signatures (other domains call them). favor.cpp's private SQLite wrapper stays for S1.
  - **R16e** the tests beside their code, renamed (seeds change): `presents/present-texts`, `presents/favor-achievements`, `daily/premium-favor-bonus`, `favor/favor-rules`, `favor/friendship-campaign`; new `testing/module_test.h` (call, master_id, player_load_data). `soa --selftest "server/"` no longer selects these five. After merging R11: `server/economy-apis` (growth_tests.cpp) lost its login-bonus and achievement parts to `daily/login-bonus` and `presents/achievement-chain` (bodies unchanged; new seeds); it keeps the shop and exchange (R18's). rules_tests.cpp's header comment still lists them (left for R13, which empties the same file).
  - **R16f** the R6e label drift: "free coins first" is **(a)**, master_text `uimsg_buy_history_explan` ("紋章石を使用する際は無償入手分から先に消費されます", key in the 3.7.0 library), in `core/wallet.h`, shop, gacha, deep space, Sphere 211 and docs/server-rules.md together; 2 (c) and 3 (d) labels became (a) (listed in the commit). **Left for R13:** `api/items/items.cpp:344` (StaminaHeal) still says "(c) free coins first".
  - **R16g** the READMEs; docs/server-rules.md "10. Achievements": type 6 is weapon limit breaks by its texts.
  - **Findings, reported, not fixed:** (1) PLAN-schema's "`accessory_boost` / `weapon_boost` never written" is a false positive: ItemCompose writes them (`count(c, base.type == 3 ? "accessory_boost" : "weapon_boost")`, items.cpp), which the inventory's regex missed (PLAN-schema F1 row corrected). (2) A real rules gap next to it: achievement type 6 (37 rows, "武器を N回上限解放する", weapon limit breaks) is counted with `weapon_boost`, i.e. every weapon compose, so it completes too early; a fix would count limit-break raises in ItemCompose (R13's file) and read that counter (done 2026-10-03, agent srv-bugfix-1: `weapon_limit_break`). (3) AchievementActiveList's category isn't read (d, documented; the client filters by the rows' own category, so it stays).
  - **For S8:** PLAN-schema S8's note "After R16" lists what the presents merge touches now.
  - **The step's sessions (once, at the end, one at a time):** `port/scripts/restore_session.sh` PASS (battle cleared, 10-draw 300000 -> 297500, present box 4); `events_session.sh` with clock 2020-05-29 15:00:00 PASS; `restore_favor_session.sh` PASS (taps 9900 -> 10000, level 1 -> 2; battle favor), rerun PASS after merging linux-port (R11). The port's selftest with `--selftest "server/|presents/|daily/|favor/|growth/|rules/"` (the filter is `|`-separated substrings): 78/78. After the merge: RG4 identical vs afeec13 on the five corpora (growth included), `soa-server --selftest` 94/94 (and `--shuffle 3`).
- **R13 done (2026-10-03, branch `port/srv-r13-r14`, off 487e3f6; run in parallel with R10, R11, R16).** As built:
  - **R13a** the core's stack-item writes that R6e left (the grant's and `add_character`'s upserts in `core/rewards.cpp`, the gacha's chips, the gacha's / box gacha's / MissionStart's ticket and vanish takes) go through `ext::add_stock` (= `wallet::add_stock`). **Declared semantic difference** (in no corpus): a grant now stops at `master_global.item_stock_max_num` (100,000,000), (a), as every module's grant did; the takes are unchanged (each is checked against the count first, so the row exists and the floor is never reached).
  - **Prep:** a hand-written replay corpus `server/tests/replay/items-party` (40 `req` lines): RG4's other corpora reach the item, gear and party handlers only without arguments. It makes 30 weapons with three weapon-gacha 10-draws on the seeded state, then calls the item, gear and party APIs with real arguments (23 accepted, 15 refused, 2 not handled). Not covered by it: RemoveGear's accepted path (no grease in the seeded state), MaterialCompose / UseHealItem / SellStackItem accepted (no stack items); the unit tests cover those.
  - **R13b** `api/items/items.cpp`: handlers named after their APIs, `ctx` / `req` / named rows, args structs in the module (not `core/request_args.h`, which the parallel steps also edit), the 2.5 block on every handler, named constants (`api/items/items.h`: `item_type::`, `uid_list`, `item_equipped`), ItemCompose's answer as its own step. The four `growth_rules` item definitions stayed in items.cpp; R11 (merged first) moved them into `rules/growth_rules.cpp`, which the merge kept.
  - **R13c** `api/items/gear.cpp`: the same, plus builders named after the client classes (`gear_info`, `gear_info_list`, `attached_gear_info(_list)`, `barney_chance_info`), a doc comment on every hook, GenerateGear (154 lines) as eight named steps over a `Generation` struct (each step's code in its old order: the RNG draws come in the same sequence), the formulas in `rules/gear_rules.{h,cpp}`. Tests beside the code and renamed (new seeds): `items/gear-rules` (`rules/gear_rules_tests.cpp`), `items/gear-apis`, `items/gear-barney-chance` (`api/items/gear_tests.cpp`).
  - **Docs (R13d):** docs/server-rules.md: "Items and stamina" said SellGear isn't implemented (it is gear.cpp's); the "Gear" table's RemoveGear row said one grease per gear (d) where the code takes one per request, (b) from the dialog's 必要数 1, and accepts a gear uid (d): the row now says what the code does; the gear test names. `api/items/README.md`, `rules/README.md`, `src/README.md`, API-INDEX.md.
  - **Proof per commit:** RG4 identical vs 487e3f6 on the five corpora (log included); `soa-server --selftest` 92/92, twice more and `--shuffle 7` / `13`; evidence: nothing lost (agent mentions 71 → 68); format clean; `check_no_380` PASS. The session: `growth_session.sh` (below, with R14's).
  - **Tests after the merge with R11:** the items half of `growth/apis` (compose, lock, sell, stack sale, heal items, StaminaHeal) is its own test now, `items/apis` (`api/items/items_tests.cpp`; it adds its own FOL and EXP item, which it took from the growth half before). `server/economy-apis` (shop, exchange, login bonus, achievements) stays in `api/growth/growth_tests.cpp` for R16 / R18.
  - **After the merges with R16 and R10 (their handoffs):** **R13f** StaminaHeal's "free coins first" is (a), as R16 labelled the rule (core/wallet.h, master_text `uimsg_buy_history_explan`; declared: two (c) labels became (a)); `rules/rules_tests.cpp`'s header names what is left there. **R13g** player_info.cpp's `stock_value` / `items_value` are `stack_item_info_list` / `item_info_list` (2.2), their agent notes rewritten, `Item.is_equip` through `item_equipped`; one token per caller (missions, presents, favor, gacha, `core/context.cpp`). Each RG4-identical vs linux-port 4e52a11.
  - **The steps' sessions (R13 + R14, one at a time; on the R11 merge and again on the final tree after the R16 / R10 merge):** `growth_session.sh` PASS (strengthening, evolution, limit break, gear set / taken off with grease / purified, rank value 150), `party_session.sh` PASS (the saved set reaches MissionStart), `battle_session.sh` PASS, `restore_missions.sh` PASS (surprise battle, two step-up steps 300000 -> 292500, the 10004 dialog); `soa --selftest "server/|growth/|rules/|items/|player/"` 72/72.
  - **Left for later:** `ErrorCode::kFolShortGrowth` (11001) is used only by items.cpp: `kFolShortItems` would say so (`tools/gen_error_codes.py`, a shared file).
- **R14 done (2026-10-03, branch `port/srv-r13-r14`, after R13).** As built:
  - **R14a** `api/player/party.cpp`'s UpdateParty and UpdatePartySet only (SetAssist and the party set builders are R11's: after the merge with R11, `api/player/assist.cpp` and `party_set.{h,cpp}` `party_set_info`, which the handlers call): `update_party` / `update_party_set`, the 2.5 block on both, the labels made true (UpdateParty's "only owned characters" had none, (d) now; UpdatePartySet's refused id said "(d: status only, no change)" where the handler answers nothing: no body, so the host's fallback, without an error code), the owned-character query as one helper. UpdatePartySet's text is parsed by a named step, `party_set_records` (the split, unchanged) and `parse_party_set_text` → `PartySetText` / `PartySetMember` (party.h), bound to the same statements with the same types. Args: `args::UpdatePartyArgs` / `UpdatePartySetArgs` (R6f's, unchanged). New test `player/party-set-text` (`api/player/party_tests.cpp`; the plan's names: `<domain>/…`, the domain folder is `player`).
  - **R14b** docs/server-rules.md "Party" / "Party sets" (the (d) label, the not-answered cases, the skipped short member record, the tests), `api/player/README.md`'s party row only (R10 and R11 edit the rest), API-INDEX.md; PLAN-schema S6: what the merge must decide (UpdateParty writes `party` only, so a slot's stored equipment stays when its character changes; UpdatePartySet checks only `character_id`).
  - **Proof:** RG4 identical vs 487e3f6 on the five corpora (items-party has UpdateParty with an unowned uid and without arguments, UpdatePartySet with a set, an id out of range, unparsable text and a short member record); `soa-server --selftest` 93/93, twice more and `--shuffle 7` / `13`; evidence: nothing lost; format clean; `check_no_380` PASS.
- **R15 done (2026-10-03, branch `port/srv-r15`, off 13b2367; merged linux-port 4e52a11 (R10) after R15a and 26baaf5 (R13–R14) before the sessions), a prep commit and eight steps, each RG4-identical vs its parent (13b2367, then 4e52a11) on the seven corpora (the merge: vs 26baaf5 on eight, items-party included) (log included), `soa-server --selftest` 94/94 (also `--shuffle 7`; 11 and 13 after the test renames), evidence: nothing lost, format clean, `check_no_380` PASS, API-INDEX.md regenerated.** As built:
  - **prep: two hand-written replay corpora** (`server/tests/replay/missions`, 73 requests; `server/tests/replay/tower`, 12 with `--restore-tower`), because the flows start missions only with no helper and the tutorial's NPC party, and the api-sweep calls the rest without arguments. `missions` runs at 2017 and 2021 times (the campaigns' windows): every helper kind (own, own already in the party, a rental clone in the 4th and the 6th argument, a foreign rental id, a story NPC id, the event NPC helper by both ids and a wrong one), restarts, MissionFailed / GetPlayMission / MissionTalk / GetMissionList, refusals 10004 and 10206, an unknown mission, the surprise roll, the prism, stamina and 友好 campaigns, the character bonus, battle evaluation (one `wire` MissionEnd: the `event` flow's battle log with the mission id replaced), FollowList, UpdateSupport, the rental bonus over three rental days. Both replay identically on 13b2367 twice.
  - **a. MissionStart:** the domain's enums in `missions.h` (`MissionType`, `HelperKind`, `CampaignType`, `DropType`; `Campaign`'s fields named for their columns); `mission_start.cpp`'s R8.12 state struct with named fields instead of the per-step `auto& x = s.x` aliases; `kNpcPartyUid0`; the NPC and helper steps split (no function of the domain is over 40 lines now); the handler `mission_start` with the 2.5 block. `tools/server_index.py` matches the MissionStart / MissionEnd hooks by name in `api/missions/` (deep space's handlers have the same names).
  - **b. MissionEnd:** the same treatment; `split_play_uids` is the one reader of the play record's `"uid,uid,"` (the EXP loop's own parser needed the trailing comma, which the record always has); the answer's `drop_list_info` / `clear_present_list_info`; the present reason `ext::kPresentMissionClear`; the handler `mission_end`.
  - **c. drops, campaigns, play state:** `roll_drops` as named steps in the RNG's order; `lottery` takes a `DropType`; GetPlayMission, MissionFailed and MissionTalk are three handlers (three `add_core_api` calls in the old order: 29 core registrations, the same 37 methods, `--list-apis` unchanged), `play_state()` is `ext::Ctx::core_mission`'s.
  - **d. tower**, **e. rental:** names (`ctx`, rows for their table, the CFollow* builders), the floors as their own step, `UpdateSupportArgs` (in `rental.cpp`, the module's only positional read), the 2.5 block on FollowList / UpdateSupport and a doc comment on every hook.
  - **f. Tests renamed** (seeds change): `missions/surprise-campaign-evaluation`, `missions/unlock-refusal`, `tower/banner`, `tower/client-master`, `tower/lists`, `social/follow-rental`, `social/follow-support`, and `rules/missions` (moved from `rules/mission_rules.cpp` into `rules/mission_rules_tests.cpp`). **For RG3:** the port's filter adds `missions/|tower/|social/` (`rules/` is R11's).
  - **g. Docs** (label drift, the code as the evidence): 2.2 (error codes are reported on both routes; the drop lists are empty, MissionEnd rolls), 2.6 (what MissionRestart does), the "Server core" lines on helpers, surprise and unlocks, "Server missions" (the rental bonus is paid, type-8 campaigns multiply favor, evaluation types 2 and 5 come from the evaluation array; the register rows), "Play state", "Rental helpers"; the READMEs of api/missions, api/tower and api/social's rental row.
  - **Deviations:** the mission args structs stay in `core/request_args.h` (shared with R10 / R14; moving them is a pure deletion for later). `one_null_as_zero`'s two mission sites keep the NULL-as-0 read, decided and commented: `party_id` (NULL reads 0, which has no members, so party 1, as the default would give) and `role_category_id` (master_role has no NULL in 3.7.0). `mission_rules::mission_table` keeps its integer switch (rules/ doesn't include api/).
  - **Found, not changed (documented):** MissionRestart sends the play's party id as the third argument (the helper index + 1) and no helper ids, so a restarted battle loses its helper (seen in the missions corpus; d, docs 2.6). `play_ext`'s `helper_uid`, `helper_kind`, `helper_npc`, `campaign_lots` are written and never read; MissionFailed deletes `play` but not `play_ext` (both for S7, PLAN-schema "After R15"). **Fixed in S7** (PLAN-schema S7 "As built"): the merge makes MissionFailed end the whole record; MissionRestart replays the recorded helper (its own commit), which makes `helper_uid` / `helper_kind` / `npc_id` read; `campaign_lots` dropped.
  - **Shared files touched** (minimal): `core/context.cpp` (`core_mission` calls `mission_end` / `play_state`), `core/server_tests.cpp` (two handler names), `tools/server_index.py`, `server/ARCHITECTURE.md` (the registration count), `docs/server-rules.md`, `server/tests/replay/README.md`.
  - **The step's sessions (once, after merging 26baaf5, one at a time):** `port/scripts/battle_session.sh` PASS (mf01_001 fought, result pages), `restore_missions.sh` PASS (surprise battle and drops, mf01_004 unlocked, the step-up steps 300000 -> 292500, the 10004 dialog), `campaign_session.sh` PASS (mf01_001 cleared, mc01_030 played), `tower_session.sh` PASS (ma99_101 cleared), `rental_session.sh` PASS (the rental as member 4, the bonus paid the next day with its popup), `deepspace_session.sh` PASS. The port's `--selftest "server/|missions/|tower/|social/|rules/"` 62/62. tests/diff left to the integrator.
- **R18, events / gacha / shop / campaign done (2026-10-03, branch `port/srv-r18b`, off 4e52a11; R18 split in two: agent srv-r18a has deep space, Sphere 211 and the `cdn/` split; merged linux-port 26baaf5 (R13–R14) after the events step and dc4649c (R15) before the final gates), a prep commit and four steps, each RG4-identical vs its parent (4e52a11, then 26baaf5, then dc4649c) on every corpus (seven, then eight with items-party, then ten with missions and tower; log included), `--list-apis` / `--list-hooks` the same, `soa-server --selftest` 94/94 → 96/96 (twice and `--shuffle` 7, 11, 13, 17, 19 after the test moves), evidence: nothing lost (one declared (c) → (b)), format clean, `check_no_380` PASS, schema inventory the same tables and columns, API-INDEX.md regenerated.** As built:
  - **prep: two hand-written replay corpora** (`server/tests/replay/economy`, 46 requests, `--galaxy-pass`; `server/tests/replay/event-extras`, 17), because the api-sweep calls the shop, exchange, box / step-up gacha, GachaTicket and the event extras without arguments and no flow reaches them. `economy`: at 2016-06-01 the item shop's 2016 sample rows (`shop_item_set_base_sample_00008`: 10,000 pumpkin coins and 100,000 cookie box tickets for 10 coins; `_00006`: role gacha tickets) to their limit and refused, GachaTicket; at 2020-10-25 GetGachaInData, a step-up chain in order and out of order, single / bulk / sale / weapon draws, GetGachaRate, the cookies box series drawn to its last box (it refills; ResetBoxGacha refused and accepted), the pumpkin exchange shop (accepted, over the limit, over `exchange_item_max`, items short, closed, unknown). `event-extras`: a world boss area (spring_89, me99_999: time bonuses, the gauges) and an event ranking (me99_1113: scored, the badge list, due, paid, the player detail); the battles are the `event` corpus's me99_1054 MissionStart / MissionEnd bodies with the mission id replaced (a little-endian u32).
  - **gacha:** handlers named after their APIs (`get_gacha_in_data`, `gacha`, `box_gacha`, `reset_box_gacha`, `get_box_gacha`, `get_gacha_rate`), builders after the client class (`stepup_gacha_info`, `box_gacha_info`, `box_gacha_list_info`, `gacha_rate_info`), the 2.5 block on each; the draw's R8.12 steps take the `GachaDraw` directly (the alias blocks gone) plus `record_history`, `add_limit_break`, `add_chips`, `advance_stepup`; BoxGacha as `box_ticket` / `draw_slots` / `refill_last_box`; `kContentTypeItem`, `kRankLetters`, the loop guards. The two-`rng()`-call expression of the pool draw is kept verbatim (argument evaluation order). Tests `gacha/stepup-box`, `gacha/enable-events`.
  - **shop:** handlers named after their APIs, `args::ExItemShopArgs` / `ExshopExchangeArgs` beside the module (the exchange count keeps "a missing or a present 0 is 1"), ExItemShop / ExshopExchange as `buy_item_shop_row` / `exchange_refusal` / `exchange_data` over a `Refusal {why, code}`; the hooks' blocks. **One item-set expansion:** shop.cpp's and ranking.cpp's copies are `core/rewards.h` `grant_with_item_sets` (appended; `kContentTypeFreeCoin`, `kContentTypeItemSet`; the same calls in the same order). Sphere 211 (R18a's) keeps a third copy; it can switch to it. `subscription.{h,cpp}`: namespace `subscription` with a header so its test sits beside it. Tests: `server/economy-apis`'s shop and exchange part and `server/subscription` → `api/shop/shop_tests.cpp` as `shop/item-shop-and-exchange` and `shop/subscription` (on `testing/module_test.h`).
  - **events:** `event_missions.cpp`'s long functions as named steps (`map_replacements` / `battle_files` / `story_playable`, `term_covers` / `weekly_covers`, `event_progress` / `list_area_missions`, `area_info` / `mission_list`), `kListAheadSeconds`, `kDatedTables`; ranking's and world boss's handlers with the 2.5 block and their args structs (`GetEventRankingInfoArgs`, `ClearNewEventRankingArgs`, `GetPlayerDetailInfoArgs`, `GetWorldBossInfoArgs`); every hook (OnPlayerLoad, OnResponse, ClientMaster, AreaExtra, MissionStartExtra, MissionResultExtra) with its block; `kMissionTypeEvent` (event_extras.h, 5 sites), `kEventTypeWorldBoss`, `kRankingTypeClearTime`, `kDropTypeFavorEvent`; `enable_events::client_master` as `open_areas` / `open_gachas` / `open_banners` / `open_exchange_shops`. favor_drop.cpp only names and its block (no corpus enters its lots loop; `events/favor-drop` is its proof). `soaserver/events.h`'s declarations unchanged (parameter names and comments only). Tests renamed `events/...` (17). `event_response_keys` keeps its own `ints.size() > 1` guard.
  - **campaign:** the 732-line `campaign.cpp` is five files over an internal `api/campaign/campaign.h` (the public `soaserver/api_campaign.h` unchanged but its comment): `master_data.cpp` (its own SQLite reads, one loader per table group), `progress.cpp` (the text file, `seed_progress`, `clear_mission`), `lists.cpp` (`available`, the builders; `in_window` stays its own string-compare variant), `campaign.cpp` (the hooks, `campaign_keys`, the splice on `Value`), `campaign_tests.cpp` (`campaign/unlock-chain`, `campaign/splice`). Stale comments gone (restore_campaign.cpp, canned files, the MissionParameter bullet).
  - **Label drift fixed** (code and docs together): the item shop's price in 紋章石 was (c) in the code and section 9, (b) in "Shops" (the screen's 必要紋章石): (b) everywhere. Docs only: GetGachaRate "not answered yet" (it is, rates.cpp); "Campaign progression"'s clock (the server clock, not "--clock seconds"), MissionEnd's mission argument, and two stale rows (the campaign's "party of three", "missing drops and stamina": the core's now). The 11 agent notes in these folders rewritten (0 left).
  - **Shared files touched** (minimal): `core/rewards.{h,cpp}` (`grant_with_item_sets` appended), `core/server_tests.cpp` (`gacha` was `api_gacha`), `api/growth/growth_tests.cpp` and its README row (the economy test left), `docs/server-rules.md` (incl. one test name in the deep space section: `shop/subscription`), `api/favor/README.md`, `port/REMAINING.md` (test names), `server/src/README.md`, `server/ARCHITECTURE.md`, `core/README.md`, `server/tests/replay/README.md`.
  - **For S10** (PLAN-schema S10's note "After R18"): the module tables of these domains and their "no row reads as 0" sites; the box FK's insert order.
  - **Not done here:** the PLAN's 2.2 `SOA_API` macro (the domains keep R4's explicit `register_*`); `subscription_active` / `subscription_state` keep their `ext::` names (deep space calls them). **For RG3:** the port's filter adds `gacha/|shop/|events/|campaign/`.
- **R18a done (2026-10-03, branch `port/srv-r18a`, off 4e52a11; deep space, Sphere 211 and `cdn/`; run in parallel with R18b (events, gacha box / step-up, shop, subscription, campaign) and R13–R15), four commits, each RG4-identical (bodies, codes, state and log) vs 4e52a11; after merging linux-port twice (R13–R14 26baaf5, R15 dc4649c) identical vs dc4649c on the ten corpora (missions and tower included); `soa-server --selftest` 94/94 (96/96 after the merges) twice and `--shuffle`; evidence: nothing lost (3 agent mentions fewer); format clean; check_no_380 PASS; API-INDEX.md regenerated.** As built:
  - **prep: two replay corpora,** since the api-sweep reached these APIs only as refusals: `deepspace` (41 hand-written `req` lines on the seeded options: offers, auto select, departures accepted and refused (party size, not on offer, member twice / unknown / busy, no free ship, a bonus item not owned / out of its window), an early MissionEnd, quick returns in coins across the 04:00 reset, MissionEnd's rewards, a rare offer played and used up) and `sphere211` (32: a dive on floor 1 with an own helper, the rental slot, continue, retire, the rare and boss cells' boxes, items refused, the floor clear and the next-floor select, ranking, 帰還, the next day's GetPlayer and a season change 40 days later). Replayed twice by 4e52a11's soa-server: identical. The Sphere 211 corpus's lots depend on the maps in `--download-dir` (deterministic on one download tree).
  - **R18a-1 deep space** (`api/deepspace/`): `deepspace.cpp` the five handlers named after their APIs with the 2.5 block (the two MissionEnd lambdas became `deep_space_mission_end` / `_now`), MissionStart and MissionEnd (183 lines) as named steps; `state.cpp` (clocks, areas, offers, ships, the answer values named after the client classes), `bonuses.cpp` (the bonus conditions: `Who` / `Needs`), `rewards.cpp` (`BonusEffect`, `BonusCategory`), `deepspace.h` (internal, namespace `deepspace`), `deepspace_args.h`; `deepspace_rules` → `rules/deepspace_rules.{h,cpp}` as `rules::deepspace` (`LimitType`, `kQuickReturnCoinsPerItem`). **`area_assets` (R6g) decided:** it stays its own predicate (the exact `Image/etc2/<resource>.aif` in the AssetIndex, on a live server only), not the one gate's `assets::available` (texture-quality and `assetpack/` variants, the tests' override, everything passes without a source); on the 3.7.0 data both agree (the 13 area images are only at `Image/etc2/`, in the download); commented in state.cpp and the README. Tests: `rules/deepspace`, `deepspace/expedition`, `deepspace/extras` (were `server/deepspace-*`).
  - **R18a-2 Sphere 211** (`api/sphere211/`, the plan's split): `sphere211.cpp` (the 13 handlers with the 2.5 block, the player-load hook, the tables), `season.cpp` (seasons, `load_dive`, the achievements' moved windows), `floors.cpp` (floors, playable missions, the cell lottery, the warp, the stamina), `rewards.cpp` (boxes), `ranking.cpp` (reward groups, the reward, the local ranking), `rental.cpp` (the rental slot and bonus), `state.cpp` (`put_state` (106 lines) as `read_dive` / `floor_cells` / `put_end_result`; `sphere_meta` / `set_sphere_meta`, renamed from `meta` / `set_meta`, which the core also has), `dive.h` (internal), `sphere211_args.h`; `sphere211.h` unchanged for its users. Named: the core fids and mission type, `DropType`, `LotteryType`, `LogKind`, `AchievementType`, `kRankD`. The dead `max_floor` went. Tests `sphere211/{season,lottery,stamina,dive,rental,achievements,items}` (were `server/sphere211-*`). `tools/schema_inventory.py` reads the renamed `sphere_meta` helpers in every `api/sphere211/` file; RG11: the same tables, columns and keys, one declared difference (`sphere.entered_at` now listed as written and never read, which is true: the old "read" was the inventory's same-file guess from `sphere_rank.entered_at`).
  - **`sphere.revive_count` (PLAN-schema F1): a bug (a rules gap), reported, not changed.** Decompiled from 3.7.0: `Player.sphere211_revive_count` (CPlayerInfo+0x910 = CParameterManager+0xf48) counts the sorties with an EX character (`master_role.rank` 5, `CParameterUtility::IsRoleDeity`) since the last 帰還; `CSphereMissionDetail::NextPhase` shows `master_global.max_revive_count` (3) minus it in `OpenSphere211SallyDialogWithDeity` (`uimsg_sphere211_mission_start_with_deity`: "使用可能回数 残り %d 回", recovered by 帰還; an EX character's companions don't become 出撃済み on a clear, the EX character does). The server never counts and departs every member, so the dialog always says 3 left. Documented in state.cpp, the README, docs/server-rules.md "Sphere 211" ("Not done") and PLAN-schema F1.
  - **R18a-3 `cdn/`:** `cdn.cpp` split into `tree.cpp` (`Tree::build` (272 lines) as the steps of `TreeBuilder`, a friend of `Tree`: `read_version_bin`, `serve_master`, `add_standins`, `read_manifests`, `collect_bundles`, `hash_bundles`, `renew_ids`, `write_version_bin`; `lookup`; the `*_from_config` functions), `bundle.cpp` (the ISF image, `Response`), `served_master.cpp` (`make_served_master`), `files.{h,cpp}` (internal helpers). `soaserver/cdn.h` gained one private line (`friend struct TreeBuilder;`). **Proof:** the new `tools/server_cdn_check.sh BIN_A BIN_B` (the replay builds no CDN): `--cdn-check` over every path the CDN serves (version.bin, the five manifests' `.bin` / `.version`, version.version, the master both ways, the 25,436 bundles, the stand-ins' bundles and files, a missing name), stand-ins on and off, from an empty scratch and again from the bundle-hash cache, logs masked, `time()` frozen (version.bin's `time` is the clock plus the seconds since the start: two runs differ by a second now and then): identical vs 26baaf5 and vs dc4649c (25,461 paths; 25,460 / 25,439 served). `vcpkg.json`'s `$comment` names `served_master.cpp` (as R5 renamed it there); the triplet's comment is left.
  - **For S10:** PLAN-schema S10's note "After R18a" (where the deep space and Sphere 211 tables are read and written now, `ds_ship.uids`, the 0-as-none columns, the `meta` / `sphere_meta` keys, the two `sqlite_master` probes, the written-never-read columns).
  - **Shared files touched:** `soaserver/cdn.h` (the friend line), `testing/module_test.h` and `testing/README.md` (comments: deep space's tests use it now), `tools/schema_inventory.py` (the sphere_meta regex), `server/src/README.md`, `rules/README.md`, `server/README.md`, `server/ARCHITECTURE.md` (file names), docs (`server-rules.md` Deep space / Sphere 211 / CDN, `client-changes.md`, `online-server.md`, `basmaster-gl.md`), `vcpkg.json` (`$comment` only). No `core/` code.
  - **For RG3:** the port's selftest filter for these domains is `"server/|deepspace/|sphere211/|rules/|cdn/"`: 62/62 (with R15's `missions/|tower/|social/` for the whole set).
  - **The step's sessions (once, at the end, one at a time):** `port/scripts/deepspace_session.sh` PASS (two expeditions, a quick return, a Galaxy Pass ship; on the R13–R14 merge), `sphere211_session.sh` PASS (the rental bonus popup, four battles with a rental, 帰還, the boss, floor 1 cleared, the reroll, floor 2, 帰還), `sphere211_continue_session.sh` PASS (continued for 100 coins, retired, healed), `emulator/scripts/standin_fetch_test.sh` PASS on and off (the stand-in bundle fetched and stored byte-identical; none with `--standin-assets off`), run with `EMU_DATA` = a writable copy of `work/phone-3.7.0`: on an empty phone the client stops at the Episode data dialog, which the script doesn't answer (both modes alike; not this step's). tests/diff left to the integrator.
- **R12 done (2026-10-03, branch `port/srv-r12`, off 565f04c (S4); main 7e2b21e merged before the final gates), a corpus commit and four steps, each RG4-identical vs 565f04c on every corpus (bodies, codes, state and log), and the merge identical vs 7e2b21e (14 corpora); `soa-server --selftest` 111/111, `soa --selftest` 127/127; T0 every step; of T1's selection (8 tests/diff shards and 6 sessions: core headers changed) only `replay-parent`, the selftests and `shard:login` ran, as a pure refactor's proof is the byte-identical replay.** As built:
  - **R12a `soaserver/ids.h`** (public, not `core/ids.h`: `ext.h` and `sql.h` use the types; `core/ids.h` keeps the uid scheme's plain constants): `template <class Tag, class Rep> struct Id { Rep v; explicit Id(Rep); operator<=> }` and `std::hash`; the kinds `CharacterUid`, `ItemUid` (u64), `PlayerId`, `RoleId`, `SameRoleId`, `MasterItemId`, `MissionId`, `GachaId`, `TitleId`, `AreaId`, `SkillId` (u32; `SkillId` added for `roster.equip_skill1..3`). No conversion between kinds or from / to a number except explicitly (`CharacterUid(n)`, `.v`; static_asserts in `state/sql_tests.cpp`). `or_zero(optional)` is the wire's "0 = none", `nonzero<T>(n)` reads a request's 0 as none. `sql::Row::id<T>(col)` (NULL reads as id 0, as `i()`), `Row::opt<T>(col)` (NULL = none), `Sql::one_id<T>` / `one_opt<T>`, `Arg` from an id or an optional one (empty binds NULL). **Deviation:** the accessor is `row.id<T>` / `row.opt<T>`, not `row.uid<T>` (2.3), since it reads master ids too. Test `server/sql-typed-ids`.
  - **Corpus:** `items-party` +6 requests (EquipWeapon moving a weapon between characters, the previous owner's slot emptied; EquipAccessory with a weapon, refused; EquipWeapon 0; GetPlayer), so R12b's equip path with a previous owner is replayed; COVERAGE.md regenerated.
  - **R12b the S4 columns as optionals:** `roster.weapon_uid` / `accessory_uid` (`std::optional<ItemUid>`), `roster.assist_uid`, `player.home_uid` / `support_uid` (`std::optional<CharacterUid>`), `player.title_id` (`std::optional<TitleId>`), `roster.equip_skill1..3` (`std::optional<SkillId>`) read with `opt` / `one_opt` and written from optionals (none binds NULL: `select_title` and EquipWeapon / EquipAccessory's take-off are one statement now, same state). `owns_character(ctx, CharacterUid)` (`api/player/roster.h`) replaces the `select count(*) from roster where uid = ?` copies of home, assist, growth, UpdateSupport, the support default, the party checks and the rental helpers; four stay on purpose, on the mixed-kind lists S7 types (MissionStart's own helper, Sphere 211's party slots and slot 4, deep space's member check), and `state/schema.cpp`'s migration keeps its own. Typed args: SetAssist (`assist_uid` optional), UpdateHome, UpdateSupport, SetTitle (`std::optional<TitleId>`), the growth APIs (`growth_args.h`; EquipItem's item optional). EquipSkill's three skills stay the request's u64s bound through `nullif(?, 0)` ("stored as they came": a `SkillId` would truncate). The seed and CreatePlayer build `CharacterUid(kRosterUid0 + i)`; `request_context.h`'s `titles_added` is `std::vector<TitleId>`.
  - **R12c owned uids across folders:** `next_character_uid` / `next_item_uid` (`state/state.h`, over `next_uid`), `Added.uid` (`core/rewards.h`), the granted and drawn items and characters (rewards, gacha), `ext::ItemExtraFn` / `item_extra` take an `ItemUid`, the items module's `Item` / `find_item` / `item_uid_list` / ItemCompose and ItemGradeUp args, `item_equipped(ItemUid)`, UpdateParty's members, `rental::id_of(CharacterUid)` and `rental::source_uid` → `std::optional<CharacterUid>` (none also for the bit alone, as before: 0).
  - **R12d master ids:** `PlayerId` (`player_id(ctx)`, `ext::Ctx::player_id()`, `person_info`'s owner, the presents; wire-only locals take `.v`), `RoleId` (`master::role_level_cap` / `role_next` and `Ctx`'s, `add_character`, growth's `Character` and EvolutionCharacter's next role, MissionEnd's and deep space's character EXP, the battle status, the seed's roles), `SameRoleId` (`favor.h`'s API and `favor.cpp`, `home_same_role`, MissionEnd's battle favor, the favor event drop, the favor login bonus tier; id 0 stays the favor module's "none": `favor` isn't an S4 table).
  - **Plain still, by design (each switches with its S step):** `party` / `party_member` uids and equipment (0 = empty: **S6**; `party.h`'s `PartySetMember`, `party_set.cpp`'s set values; **done in S6:** `party_member.uid` (`party` merged in) and its `weapon_uid` / `accessory_uid` / `skill_id1..3` / `assist_uid` read as `std::optional<CharacterUid / ItemUid / SkillId>` (NULL = none), `PartySetMember`'s fields are those optionals (`nonzero<T>` from the text), UpdateParty's slots `std::optional<CharacterUid>`, `party_member_uids` returns `CharacterUid`s (MissionStart's battle list takes `.v`: it mixes NPC and rental members, S7)); `gear_items.item_uid` (0 = the gear box) and the gear uids, and gear.cpp's weapon lookups whose arguments are a weapon or a gear uid (**S5**; **done in S5:** `gear_items.item_uid` is `std::optional<ItemUid>` (NULL = the gear box), the gear uids `GearUid` (new in `soaserver/ids.h`), the weapon lookups, AttachGear's and GenerateGear's base `ItemUid`, `Gear::id` / `Weapon::id` / the items module's `Item::id` `MasterItemId`; RemoveGear's argument and GenerateGear's materials (a gear or a weapon uid) stay numbers until looked up); the play and ship uid lists (`play.uids`, `ds_ship.uids`, `MissionInfo::uids`, `mission_info`, deep space's `Member.uid` / `free_characters` / `parse_uids`) and the request uid lists that mix owned, rental and NPC members (MissionStart's 4th / 6th arguments, `person_status_info(u64)`, which also builds the event NPC's `kNpcPartyUid0 + 1`, Sphere 211's party slots and slot 4) (**S7**; **done in S7:** `play_member.uid` reads as `std::optional<CharacterUid>` and `npc_uid` as `std::optional<NpcPartyUid>` (new in `soaserver/ids.h`: a mission NPC's battle uid) through `PlayMember` / `play_members` (missions.h), `ds_ship_member.uid` and `ship_members` as `CharacterUid` (`parse_uids` gone); plain by design and documented: `play.helper_uid` (its kind is `helper_kind`), `play.npc_id`, the battle list `party_uids` / `MissionInfo::uids` / `battle_uids` and the request lists, which mix owned, NPC and rental uids as the client's do); `gacha_history.uid` (an item's or a character's uid) and `favor_bonus_state.lot_uid` (**S10**; **done in S10:** `gacha_history.uid` split into `character_uid` / `item_uid`, written from `optional<CharacterUid>` / `optional<ItemUid>` with `optional<RoleId>` (NULL for a weapon draw); `favor_bonus_state.lot_uid` a `CharacterUid` reference). Rental ids stay plain numbers (they travel in those lists).
  - **Declared, not adopted yet:** `MasterItemId` (adopted in S5 for the items and gear modules' own `Item` / `Weapon` / `Gear` structs only), `MissionId`, `GachaId`, `AreaId`: the stock / wallet helpers, the missions module's mission ids, the gacha module's ids and the area ids are u32 throughout their domains; typing them is a domain-wide rewrite each, left for a later touch of those domains (R15's / R18's files), not done here.
  - **Gates:** RG4 per step vs 565f04c and after the merge vs 7e2b21e; `tools/gate.sh T0` per commit (build, both selftests, every corpus twice, docs / format / schema / evidence / no-380 checks, the impact map); T1's `replay-parent` and `shard:login` once. Not run: the other tests/diff shards and the RG7 sessions T1 selects (the replay covers every API whose code changed: SetAssist, SetTitle, UpdateHome, UpdateSupport, the growth and item APIs, gacha draws, MissionStart / MissionEnd, deep space, Sphere 211, the favor APIs); the Windows build (ids.h uses only `<cstdint>` types; log lines cast to `unsigned long long`).

**R17 (time value types, after S9).**
- **R17 done (2026-10-04, branch `port/srv-r17`, off 669ac6e (S0–S9, R12)), three steps, each RG4-identical vs 669ac6e on every corpus (14: bodies, codes, state and log); `soa-server --selftest` 120/120; T0 every step; of T1's selection only `replay-parent`, the selftests, `replay` and the plan's R17 sessions (`events`, `sphere211`, `deepspace`) ran, as a pure refactor's proof is the byte-identical replay.** As built:
  - **R17a `soaserver/times.h`** (public beside `ids.h`, not `core/time.h`: `sql.h`, `server.h` and `ext.h` use the types): `template <class Tag> struct Time { int64_t v; explicit Time(int64_t); operator<=> }`, moved by seconds (`t + 60`, `t - 60`), two times of one clock subtract to seconds; `ServerTime` (the server clock: every stored time, the wire's data.Time) and `EventTime` (the event calendar). No conversion between the clocks or from / to a number except explicitly (`ServerTime(n)`, `.v`; static_asserts and concepts in `state/sql_tests.cpp`). `sql::Row::time(col)` (NULL or missing reads as ServerTime(0), as `i()`), `row.opt<ServerTime>` (NULL = never; R12's template), `Sql::one_time`, `Arg` from a `ServerTime` or an optional one (empty binds NULL); **no `Arg` from an `EventTime`**: the event calendar can't be stored (static_assert). `format_time` / `Ctx::fmt_time` of either, `day_start(ServerTime, hour)`. Test `server/sql-time-types`.
  - **R17b the clocks typed:** `clock_now()` / `Ctx::now()` → `ServerTime`; `event_now()` / `Ctx::event_now()` / `event_clock_of` → `EventTime`; `event_time(master, ServerTime)` → `EventTime` (the mapping); `clock_as_calendar(ServerTime)` (server.h) is the one unmapped conversion (--clock, no live server, no qualifying year). `ext::ClientMasterFn`, `ext::client_master`, `apply_client_master` take `(ServerTime now, EventTime event_now)`. The call sites: events (`year_shift(ServerTime, EventTime)`, `window_open`, `area_scheduled`, `open_areas`, `active_event_mission_list`, `campaign_info`; master dates moved by the year shift are on the client's clock, so `ServerTime`: the term / weekly / campaign windows, ranking's `Group`), world boss (`started`, `hunt_until` ServerTime, `last_clear` a duration), Sphere 211 (`pick_season(master, ServerTime, EventTime)`: the season windows are `EventTime`s, `shift = clock.v - ev.v` is where the two clocks meet, commented; the moved achievement windows, rental days and the sphere stamina `ServerTime`), deep space (`calendar()` an `EventTime`, every timer, play-limit day and the ship count `ServerTime`), the tower (`EventTime`), story campaigns (`EventTime`), favor (`favor.h`'s API takes `ServerTime`; `State.tapped_at` / `event_drop_at` are `std::optional<ServerTime>` bound directly, the module's `time_or_never` / `time_arg` gone), the daily, premium and favor login bonuses, subscriptions (`subscription_active`, `grant_plan`, `keep_galaxy_pass`), the item shop (`shop_period` a `ServerTime`), gacha windows, CreatePlayer, the seed, `net/game.cpp` `map_device`, the CDN's served master, and the port's `clock:+N` debug command (`port_debug.cpp`: `.v` into `set_server_clock`).
  - **R17c the stored times at the boundary:** the formatted columns read with `row.time` (player, subscription, deep space's offers and ships, event and Sphere 211 rankings, Sphere 211's cells, the presents' deadline); deep space's type-45 expedition window is `ServerTime` (against `ds_log.started_at`). `Window::contains` / `open_at` exist only on a `ServerTime` or an `EventTime` (the `int64_t` overload is gone), so every window test names its clock.
  - **The (d) clock comments made explicit, behaviour unchanged:** `deepspace.h`'s clocks block (the former api_deepspace.cpp:119–129) says it with the types: `calendar()` returns an `EventTime`, `open_by_both_clocks` tests the window with an `EventTime` and a `ServerTime` (the overloads choose the clock); `events.h` and `Ctx::now` / `event_now` likewise.
  - **Plain on purpose:** the master's own dates (`parse_time` → raw seconds, compared through `Window` or wrapped where a moved date is on the client's clock); the pure rules (`growth_rules::shop_period_start`, `favor::rules::favor_day`, `mission_rules::campaign_active`, `rules::deepspace::week_start`, `rules::regen_stamina`) take `.v`; durations stay `int64_t` (`wboss.last_clear_secs`, regeneration carry, `kListAheadSeconds`); `events::shift_time` (raw, the tests' helper); `ext::Ctx::test.now` / `event_now` (seconds sources, wrapped by `now()` / `event_now()`), `set_server_clock`, `set_clock_offset`, `ClockSource` and `make_served_master`'s `now` (configuration, 0 = default); the notice page's `format_local` takes `.v`; `state/schema.cpp`'s migrations.
  - **The 0 sentinels (S10):** `ds_offer.closed_at` / `updated_at`, `wboss.hunt_until`, `favor_bonus_state.healed_at` read as `ServerTime` with `.v` tested and a comment pointing at S10. Found on the way: `favor_bonus_state.day_at` also holds 0 for "never" (StaminaHealByFavor inserts the row with `day_at` 0; `favor_player_keys` sends "" for it), so S10's NULL mapping should take it too. **Done in S10:** all five are NULL for none / never and read as `std::optional<ServerTime>` (`ds_offer.updated_at` formats NULL as the time 0, as its 0 did; the favor keys send `""` for never).
  - **Gates:** RG4 (`tools/server_replay_diff.sh`) per step vs 669ac6e: identical on the 14 corpora; `tools/gate.sh T0` per commit (KNOWN `pytest-soa-save` only); then `replay-parent` (vs main), `server-selftest`, `soa-selftest`, `replay`, `session:events`, `session:deepspace`, `session:sphere211`: all PASS (`/home/fish/.claude/jobs/ac4802d9/tmp/srv-r17-T1`). T1's own selection for the diff (8 tests/diff shards and `flow:event`, smoke, the three emulator gates, `session:deepspace` / `home` / `gacha` / `favor`) was not run beyond that: no reply, code, log or state changes, and the port side is one `.v`.

**S11 + R19: permanent gates.**
- `tools/check_server_docs.sh` becomes enforcing:
  - every registered API has the 2.5 block (signature line, `API:`, `Rules:`, at least one label or an explicit `Rules: none (transport)`);
  - every hook has a doc comment;
  - every `include/soaserver/` function has a doc comment;
  - links resolve; API-INDEX.md is fresh;
  - 0 agent mentions in `server/` code;
  - the evidence manifest doesn't shrink.
- `tools/format_server.sh --check`.
- Both are wired into the session scripts' common preamble next to PLAN-schema's `--check-state`, and into the merge gate (docs/merge-gating-lessons).

**R20 (later): `docs/server-rules.md` by domain.**
- One section per `api/<domain>` with stable explicit anchors (`<a id="titles"></a>`).
- The agent-named sections are merged into their domains; the history moves to `docs/history/server-rules-history.md`.
- The "Register of (c) and (d) rules" is kept and regenerated from the labels.
- The 66 code links move to anchors (RG10 proves none is lost). It is late because every domain step touches that file, and re-heading earlier would conflict with all of them.

---

## 5. Tooling

- **Formatting.**
  - `server/.clang-format`:

    ```yaml
    BasedOnStyle: Google
    IndentWidth: 4
    ColumnLimit: 150
    AccessModifierOffset: -4
    AllowShortIfStatementsOnASingleLine: AllIfsAndElse
    AllowShortLoopsOnASingleLine: true
    AllowShortFunctionsOnASingleLine: All
    AllowShortBlocksOnASingleLine: Empty
    AllowShortLambdasOnASingleLine: All
    DerivePointerAlignment: false
    PointerAlignment: Left
    SortIncludes: Never
    IncludeBlocks: Preserve
    ReflowComments: false
    BreakStringLiterals: false
    AlignTrailingComments:
      Kind: Leave
    SpacesBeforeTrailingComments: 2
    FixNamespaceComments: true
    NamespaceIndentation: None
    KeepEmptyLinesAtTheStartOfBlocks: false
    ```

  - Measured with clang-format 23.1.2 (pip wheel installed into a scratch `--target` dir; no system package, `.venv` untouched): 915 changed lines in 89 files (23,361 lines, `net/ninja_*` excluded). Re-measured for R2 with the system's 18.1.3, the version the tools now pin: 964 lines in 62 of 93 files (R2's note). It needs `BreakStringLiterals: false`, or it splits SQL literals mid-word ("… a.awaken_level " "= ?").
  - `tools/format_server.sh` uses `CLANG_FORMAT`, else `clang-format` from `PATH`. It pins the major version it was measured with (18: the system's 18.1.3; R2's note) and refuses another one (a different version formats differently).
- **clang-tidy** (optional, report-only).
  - Needs `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON`; no `compile_commands.json` exists today. `tools/tidy_server.sh` configures a separate `build-tidy/` with it.
  - Checks:
    - `bugprone-*` (minus `bugprone-easily-swappable-parameters`);
    - `readability-function-size` (`LineThreshold: 80`, a warning list for the per-domain steps);
    - `readability-identifier-length` (`MinimumVariableNameLength: 2`, ignoring `i|k|n|t`; the 1.6 `c`/`r`/`m` names);
    - `misc-unused-parameters`;
    - `performance-unnecessary-value-param`;
    - `modernize-use-nullptr`;
    - `readability-else-after-return` off (the house style).
  - Its findings feed the domain steps; it isn't a gate.
- **Doc coverage and docs checks:** `tools/check_server_docs.sh`, report mode from R1, enforcing from R19. It runs:
  1. `soa-server --list-apis` against the 2.5 blocks (a regex over the comment directly above each `SOA_API`'s function);
  2. every `docs/server-rules.md` / `docs/api.md` link from `server/` against the headings and anchors;
  3. `tools/server_index.py --check` (API-INDEX.md fresh);
  4. `tools/server_evidence.py --against <rev>` (section 3);
  5. the frozen log-line patterns (1.12) present in `LOG*` format strings;
  6. no `agent [a-z0-9-]+` in `server/{src,include,net,app}`;
  7. no reference to a missing `server/` path anywhere in the repo;
  8. a `README.md` in every `server/src/**` folder.
- **Generators:** `tools/gen_error_codes.py` (2.4), `tools/server_index.py` (2.6), `tools/server_replay_record.py` (4.1). Generated files carry a "do not edit" header (as `net/gen/wire_decode.inc` does).

---

## 6. Out of scope / later

- **Behaviour changes.** Bugs and label disagreements found while cleaning up are reported (a list in each step's commit message, then to the domain's owner) and fixed in their own commits with their own gates, not inside a refactor step. Known so far:
  - "free coins first" (c) vs (d);
  - docs/api.md's MissionStart says the drops are "pre-rolled" (the lists are sent empty, server.cpp:1406–1409);
  - PLAN-schema's rules gaps (section 6 there).
  - UpdateHome with an unowned or 0 uid returns an empty body ("not handled": the host's fallback answers) rather than a refusal with an error code (api/player/home.cpp; found in R10).
- **The wire format, response keys and the client's names.** They are fixed by the 3.7.0 client. Only internal names change.
- **The state schema and migrations.** That is PLAN-schema's scope. This plan only places its steps.
- **`server_campaign.txt`** (the campaign's progress in a text file, 1.2). This plan moves the campaign onto `Value` and the common registry (R6h, R18) but keeps its file. Folding it into the state DB is a schema change, proposed to PLAN-schema as a follow-up (an S12: `campaign_clear`, `campaign_last` tables, migrated from the file once). **Done (PLAN-schema S12, schema version 11):** the two tables, the file imported by step 11 and renamed `.migrated`; the campaign reads and writes the DB (`api/campaign/progress.cpp`).
- **The `net/` cipher implementations** (`ninja_*`): verified by 700 vectors, data-like. They move to `net/ninja/` and get a README, nothing else.
- **Multi-player, performance, an ORM or query builder** instead of SQL strings. The SQL stays readable SQL.
- **Reorganising docs/api.md** (it is generated in part by `tools/api_wire.py` and keyed by API already). Its "Server:" lines will point at API-INDEX.md.
- **The port's FakeApiCaller code** beyond the R9 call-site change.
