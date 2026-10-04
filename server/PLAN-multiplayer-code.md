# Plan: a multi-user server (the code)

Status: **plan for review only, not queued (future work).** Written 2026-10-04 by agent `mp-code` (branch `port/mp-code`, off main 6970e2c); no code changes. port/PLAN.md lists it under "Future work (not queued; needs the user's review)".

**The question** (the user, 2026-10-04): built on the multiplayer schema, what code changes make soa-server a server for several real players?

- **The schema is not repeated here.** [PLAN-multiplayer-schema.md](PLAN-multiplayer-schema.md) (route B, decided: one state DB for all players) has the tables and keys, steps **M1–M7**. This plan names those steps where it needs them. It covers everything else: identity, the request lifecycle, concurrency, shared state, social features, co-op, operations and tests.
- **Other inputs:**
  - the wire layer, [net/README.md](net/README.md);
  - the request lifecycle, [ARCHITECTURE.md](ARCHITECTURE.md);
  - the co-op study, [docs/multiplayer.md](../docs/multiplayer.md) and [docs/multiplayer/HANDOFF.md](../docs/multiplayer/HANDOFF.md);
  - the client's session, [docs/online-server.md](../docs/online-server.md) §4;
  - task U, which stubs the social APIs and defers them to multiplayer: [docs/unimplemented-apis.md](../docs/unimplemented-apis.md) part 3, "Decisions".
- **Labels** follow [docs/server-rules.md#labels](../docs/server-rules.md#labels): **(a)** master data, **(b)** client evidence, **(c)** outside knowledge, **(d)** assumption. A [confirmed] or [run] line of docs/multiplayer.md counts as (b), as in the schema plan. Addresses are Ghidra addresses in the 3.7.0 lib (ELF vaddr + 0x100000).
  - The decompiles read for this plan: `work/decomp/mpcode-presend.resolved.c` (`NetworkApiCaller::PresendApiCall` @015b7e48, `NetworkApiCaller::_Login` @015b850c). Rebuild them with `tools/decomp.sh mpcode-presend 'PresendApiCall' 'NetworkApiCaller::_Login'`.
  - Other client facts are cited from the docs that hold their evidence.
- **Names.** Three plans number their steps:
  - this plan: **MC1…**;
  - the schema plan: **M1…M7**;
  - docs/multiplayer.md's co-op stages, also called M1–M4. Here they are **"co-op stage 1–4"**.

---

## 0. Overview

**Today soa-server is single-player by construction.** Not only in its schema (the schema plan's 1.1); the code assumes one player too:

| Where | The single-player assumption |
|---|---|
| `net/game.cpp` `map_device` | every device UUID gets `select id from player limit 1` |
| `src/core/server.h` `Server` | `pending[fid]`, `errors[fid]` and `logged_in` are one per server. A request is submitted by fid, then handled by fid (`server::answer` → `submit` → `handle`), so two clients sending the same method interleave on one map entry |
| `src/api/player/player_info.cpp:133` `player_id` | `ctx.player_id()` is `select id from player`: there is no request player |
| `src/api/campaign/progress.cpp` | `g_state` caches one player's story progress in process memory |
| `src/api/events/event_missions.cpp` `end_mission_talk`, `src/api/player/notice.cpp` `web_page` / `web_document` | `ext::with_live_server` runs outside a request, so it has no player |
| `net/game.cpp` `GameServer::sessions_` | sessions never expire. A reconnect tries every session's key (O(sessions) decryptions) |
| `net/game.cpp` `handle_packet` | the RequestHeader's player id is decoded (`Decoded::header`) but never checked |
| `src/api/social/social.cpp`, `rental.cpp` | no other players: empty lists, SearchPlayer refused, rental clones of the player's own roster |
| `src/api/player/home_footer.cpp` | `is_open_multiplay` = false |

**The shape of the change:**

1. **A caller per request.**
   - A request carries its **caller**: the client session it came from, and through it the player.
   - soa-server makes one caller per bridge session (device UUID → `wire_device` → player). The in-process route makes exactly one, for the local account.
   - `server::answer`, `Server::handle` and `ext::Ctx` take the player from the caller, never from `select id from player`.
2. **Per-session request state.** The per-server request state (`pending`, `errors`, `logged_in`) moves into the session.
3. **Every query scoped by player.** Schema M3 adds the static lint. This plan adds a dynamic check with SQLite's authorizer, so an unscoped statement fails the selftests and replays.
4. **Concurrency stays simple.** One process owns the state file, with one SQLite connection, one writer and one transaction per request, under the existing `Server::mu`. Measured request costs (section 3) say this serves a LAN's players with room to spare. The network loop keeps the relay's forwarding off the DB.
5. **Cross-player features become real:**
   - follows, blacklist, search, recently played, real rental lenders (replacing task U's stubs);
   - rankings across players, the shared world boss;
   - co-op battles: the lobby and relay of docs/multiplayer.md, running each member's MissionStart / MissionEnd under that member's caller.
6. **Operations for a self-hosted LAN server:**
   - an admin CLI (players, devices, backups);
   - per-player logging, session expiry, basic limits;
   - no TLS: the client's protocol has none, and the platform layer maps the client's hard-coded hosts.

**The steps** (section 9 has each one's proof, effort and risks):

| Step | What | Depends on |
|---|---|---|
| MC1 | Client sessions: per-session request state; `answer(Request, Session&)`; the in-process route as one session | — (a refactor; can land before S12) |
| MC2 | The caller's player: `Ctx::player` from the session; the RequestHeader cross-check; session retirement; the replay's `device` lines | MC1; it is schema section 6's "request → player" |
| MC3 | Module globals per player: the campaign cache, `with_live_server` callers, the notice page, per-player RNG streams | MC2 |
| MC4 | The scope check at run time: an SQLite authorizer that flags a per-player table touched without its player key | MC2, M1; runs beside M3 |
| MC5 | Several players: CreatePlayer for a new device, search ids, the account policy, `soa --player` | M2, M3, MC2–MC4 |
| MC6 | Operations: the admin CLI, backups, the single-writer lock, per-player logs, limits, the load test | MC5 |
| MC7 | Social: follow, blacklist, search, profile, recently played, real rental lenders | M4, task U step 8, MC5 |
| MC8 | Shared state: rankings across players, the shared world boss, the lender's rental bonus | M6, MC7 |
| MC9 | The co-op wire: lobby and relay listeners in soa-server (co-op stages 1–2) | MC2 (runs beside M1–M3 with canned bodies) |
| MC10 | The co-op API: per-member MissionStart / MissionEnd through `answer`, battle records, rewards (co-op stage 3) | M5, MC5, MC9 |
| MC11 | Tests across players: two-player replay corpora, multi-client sessions, the concurrency test in the gates | grows with MC2, MC5, MC7, MC10 |

```
 MC1 ─► MC2 ─► MC3                       (single-player safe: replays byte-identical)
          │      │
 S0…S12 ─► M1 ─► MC4 ─► M2 ─► M3 ─► MC5 ─► MC6
                                     ├─► M4 ─► MC7 ─► M6 ─► MC8
                                     └─► M5 ─► MC10
 MC2 ─► MC9 (lobby + relay, canned bodies) ───────┘
 MC11: a test part of every step from MC2 on
```

---

## 1. Accounts and identity

### 1.1 What the 3.7.0 client sends

| Identity | On the wire | Label |
|---|---|---|
| **Device UUID** (the credential) | A random 36-character UUID made once and kept in the local KVS (`BAS::CreateUUID` @01f34f84, `GetUUID` @01f352c0). It reaches the server in three places: the bridge POST `{"UUID","deviceType","nativeToken"}`, **CreatePlayer**(name, uuid), and the relay's **MissionEnd** (multiplayer.md 1.8). There is no password; holding the UUID *is* the account | (b) docs/online-server.md §4 "Identities" |
| **Login's id field** | `_Login` @015b850c reads `BAS::GetUUID()` but sends the placeholder `aaaaaaaa-…`. Login also carries the push token and the advertising id (all zeros without one) | (b) [confirmed, run] online-server.md §4 flow 3 |
| **NoLoginStart** | a `char[16]` field (not the 36-character UUID) and the DeviceType, **in the clear and before any bridge session** | (b) docs/api.md#nologinstart |
| **The session** | StartBridge → ResultStart(token, URL) → the bridge POST → `nativeSessionId` + `sharedSecurityKey` → UpdateSession(session id). Every encrypted request is Ninja-encrypted with the session key. A logged-in client reconnects for each request with no new handshake (net/README.md, online-server.md §4 flow 6) | (b) |
| **RequestHeader** (16 bytes, inside the ciphertext) | `PresendApiCall` @015b7e48 fills it. **+0** = `CParameterPlayer+0x38`, the numeric player id the LoginResult's root `Player.Id` set, **only while `LoggedIn`** (vtable +0x6a0), else 0. **+4** = `CParameterPlayer+0x68`. **+8** = the request id, `CHash32("%u_%u_%llu_%u")` of (player id, fid, `time(0)`, a counter); it is **kept, not regenerated, when the call is a retry** (+0xdcc set and an id present). +0xe = the asset revision | (b) this plan's decompile; docs/api.md "Wire format" |
| **Numeric player id in co-op** | PlayerDetailInfo+0x6c in EnterRoom. Two clients with the same id both drive every character (multiplayer.md 1.7) | (b) [run] |
| **Search id** | `CPlayerInfo.search_id` (port/fakeapi/fields.txt:96); `SearchPlayer(char[191])` looks it up | (b) |
| **Account transfer** | Through SQEX BRIDGE's web pages: web view types 4 `bridge_user` and 0xe `bridge_backup`, with `{UUID}` substituted (docs/webview.md, "Every view type"). The service is gone, and how it re-bound a UUID to a player is unknown. **No GameRPC method transfers an account**: none of the 199 methods in docs/api-wire.txt does | (b) the pages; (c) the dead service |

### 1.2 Design

- **A player is identified by its device's binding** (schema M2: `wire_device.uuid` → `player_id`).
  - The bridge POST is the only authenticated point: its UUID comes with a token the server issued on that connection.
  - `GameServer::Session` gains `player_id`, resolved at the bridge (`record_device` → `map_device`).
  - CreatePlayer re-resolves it: CreatePlayer is the request that makes the device's player.
  - A request's caller is its connection's session; the session gives the player.
- **The RequestHeader is a cross-check, not the credential.**
  - After the login, the header's +0 must equal the session's numeric player id. A mismatch is refused with 1002 and logged (d; Q4). The header sits inside the session's ciphertext, so only the device holding the key can write it. A mismatch means a bug, or a client that logged in to another account on the same session.
  - Before the login it is 0 (b), and nothing is checked.
  - `Decoded::header` is parsed today and dropped. MC2 carries it in `Request`, as a `header_player` and a `request_id`.
- **Login.** It has no usable id field (b), so Login answers the **session's** player. A session whose device has no player gets 19001 (the client's new-player flow, docs/server-rules.md#session-and-login).
- **NoLoginStart** comes before any session (b). It gets the playerless answer, `data.Time` (d). The Login that follows loads the full state.
  - Today NoLoginStart sends the one player's state. **The trigger is the state, not a flag:** while the state DB holds at most one player, NoLoginStart keeps answering that player's full state, so today's games and every replay are unchanged. Once it holds two or more, NoLoginStart answers `data.Time` only.
  - The `tutorial` and `seeded` sessions prove the client doesn't need the full body there (MC5).
- **CreatePlayer(name, uuid)** makes a new player bound to the uuid (schema M2's code part).
  - The wire's uuid must equal the session's (d): a client can't create an account for another device.
  - A device that already has a player gets its Login answered, so its client never sends CreatePlayer (b: the new-player flow starts only on 19001). A CreatePlayer from such a device is refused (d; Q1 has the policy for unknown devices).
- **Reconnects.** A reconnect is bound to its session by trying the session keys, newest first (today's rule, net/game.cpp).
  - With several players this costs one AES-MAC check per live session per reconnect. That is cheap at LAN sizes (a trial is a MAC over one small body).
  - **Sessions are retired by supersession** (MC2, (d)). When a device bridges again, its older sessions are dropped. A session unused for 7 days is also dropped. `tokens_` is already dropped when its connection closes.
    - A short idle expiry would break a logged-in client. `CApiNotify::OnDisconnect` / `OnError` (@014bb314 / @014bb1fc) keep the bridged flag while `LoggedIn` holds (b, online-server.md §4 flow 6). So such a client keeps sending with the old key: it would get 1002 until the player went back to the title.
  - The header's player id then confirms that the key's session is the right one.
- **Search ids** (schema M2 proposes `LOCAL` + 5 digits of a hash).
  - **Recommended instead (Q2): sequential `LOCAL00001`, `LOCAL00002`, … in creation order**, unique by construction.
  - The numeric id stays CHash32(search id) (docs/server-rules.md#new-player). It is rehashed only on a collision with another player or with the synthetic lender range `0x7d000000..` (schema M2).
  - The first player keeps `LOCAL00001`, so existing states and the replays don't change.
- **Sanitization rules kept.**
  - No real player id, UUID or token in code, tests, docs or logs that get committed.
  - The seed's `BAS:PlayerID` is never copied (docs/server-rules.md#seed).
  - Fixtures use `LOCAL00001` / `LOCAL00002` and the synthetic numeric id 1000000002 (docs/multiplayer/prototype).
  - Packet logs and captures stay in `work/`. Device UUIDs in committed test data are made up (`00000000-0000-4000-8000-00000000000N`).
  - The repo seed is a real player's save (the user, 2026-10-04, the noseed merge). It may seed **only** the first player of a state, as today. Further players come from the new-player flow or from the admin CLI's `import-save` of the user's own save (MC6).
- **Account transfer** (moving to another device) is an **admin operation**: `bind-device UUID SEARCH_ID` (MC6).
  - The `bridge_user` / `bridge_backup` pages stay "the service has ended" pages (docs/webview.md 2).
  - An in-game transfer page with a code is possible later, once the web view's forms work (Q3).

### 1.3 The in-process route (`soa`, `--server inproc`)

- **No bridge and no UUID**, except in CreatePlayer (FakeApiCaller passes `(name, uuid)`, b). It stays **one local account**: MC1 makes it one session whose player is the state's **first player**, or `--player SEARCH_ID` (schema Q2).
- **Several players in the file:** a multi-player state opened by `soa` serves that one player. The others are untouched, and the M3 / MC4 checks guarantee it.
- **Co-op** stays a soa-server feature (multiplayer.md 4(d)).
- **One writer process.** soa and soa-server must not write one file at once. MC6 enforces it with an advisory owner lock (the schema plan only documents it).

---

## 2. The request lifecycle per player

### 2.1 The session object (MC1)

A new `server::ClientSession` (in `include/soaserver/server.h`) holds what is per client today but sits on `Server`:

- the pending request (the in-process two-phase capture: FakeApiCaller captures a request, and `ServeProgress` answers it later);
- `errors[fid]`, which FakeApiCaller's `IsSuccess` / `ErrorCode` hooks read after the reply;
- `logged_in` (FakeApiCaller's `LoggedIn`);
- from MC2, the player id;
- from MC6, the log tag.

Lifecycle and wiring:

- `Reply answer(Session&, const Request&, const Fallback&)` replaces `answer(Request, Fallback)`.
  - `Server::handle` takes the Request itself on this path; `pending[fid]` remains only inside the in-process session.
  - The old signatures stay for one merge wave, forwarding to the default session (ARCHITECTURE.md's habit, as with `handle(fid, file, out)`).
- **soa-server.** `GameServer::Session` owns a `ClientSession`. `LiveBackend::call(r, out)` becomes `call(session, r, out)`.
- **soa.** `port/src/native/api/fakeapi.cpp` uses one static session; `server_adapters.cpp` keeps capturing into it. `server::logged_in()` and `server::error_code(fid)` read that session.
- **The replay** (`app/replay.cpp`) uses one session per device (MC2's `device` lines).

### 2.2 The caller's player (MC2)

- `Server::make_ctx(rc, session)` sets `ext::Ctx::player` (a `PlayerId` field), and `ctx.player_id()` returns it.
  - `src/api/player/player_info.cpp` `player_id` becomes the field read. Its 32 `select … from player` reads get `where id = ?` in M3.
- A playerless request has player 0 (the new-player phase, NoLoginStart). Handlers that write per-player tables already guard that phase (schema M1, "The playerless phase").
- `RequestContext::logged_in` is set by Login as today, and copied into the session, not into `Server`.
- **The story campaign and EndMissionTalk** run around the request in `answer` (`campaign::on_request` / `on_response`, `end_mission_talk`). They take the session too (MC3), so they act for the caller's player.

### 2.3 Every query scoped by player (M3 + MC4)

- **Static (schema M3).** `tools/schema_inventory.py --lint` gets a rule: a statement that names a per-player table must name `player_id` (or `id` for `player`). Exceptions are listed per function with a reason: the shared tables, and the cross-player reads of M4–M6 and MC7–MC10.
- **Dynamic (MC4), new here.** In test runs (the selftests, the replays, and the session gates' soa-server), `ext::Sql` installs an `sqlite3_set_authorizer` callback while a request is handled.
  - SQLite reports every column a statement reads (`SQLITE_READ`, which includes the `where` and `join` columns), and every table it inserts into, updates or deletes from.
  - A statement that touches a per-player table (the classification from schema M1 / `state::check`'s `RELS`) without reading that table's `player_id` is recorded with the statement's text.
  - The run fails, unless the statement's call site declared itself cross-player with an `ext::cross_player("why")` scope guard. That guard is the code twin of the lint's exception list.
  - Inserts are covered by M1's `NOT NULL` and the lint's column lists.
  - Switched by a test switch (`SOA_SQL_SCOPE_CHECK=1`, read through `common/include/soa/env.h`); never on in a live server.
- **Isolation tests** (schema M3: `server/mp-isolation`, `server/mp-integrity` on the two-player fixture) prove what the two checks don't see: a correctly scoped statement that binds the *wrong* player.

### 2.4 Module globals (MC3)

| Global | Change |
|---|---|
| `api/campaign/progress.cpp` `g_state` (one player's progress, cached) | Cache keyed by player id (`std::map<PlayerId, State>` under the existing lock), or no cache: since S12 the progress is two small tables, read per request. **Recommended: no cache**, measured against the `campaign` corpus. `--campaign-seed` seeds the first player only (d) |
| `events::end_mission_talk` / `campaign::end_mission_talk` (`ext::with_live_server`) | Take the session's player: `with_live_server(session, fn)` |
| `notice.cpp` `web_page` / `web_document` (an HTTP GET, which carries no session) | The `WebView` URL list is per player state. Each player's `information` URL names the player in the path, e.g. `/webview/information/<search id>` (d: the client appends `?md5`; check first what `GetWebInfo` replaces in the `information` value, docs/webview.md). The page is built for that player; an unknown id gets the server-wide part |
| `Server::rng` (one `mt19937_64`, `--seed-rng`) | Per-player streams: a player's engine is seeded from (seed, player id). The first player keeps exactly today's seed, so every corpus stays byte-identical. With several players a replay is deterministic whatever the interleaving (Q8) |
| `net/game.cpp` `with_state` (the device table) | None needed: shared table |
| the clock, the event calendar, the client master, the gacha pools, the master caches (`enable_events.cpp`, `event_missions.cpp`) | Server-wide by design (section 4) |

---

## 3. Concurrency

### 3.1 Today

- **The game port** is one poll loop on one thread (`net/loop.cpp` `Loop::run_once`). It decodes each packet, calls the backend synchronously and queues the reply.
- **The HTTP port** (`net/http_server.cpp`) is cpp-httplib with its own threads. Each handler takes `Loop::lock_` (`HttpServer(router, &lock_)`), so the bridge, the CDN and the game connections take turns.
- **The library** takes `Server::mu` in `submit`, `handle`, `error_code`, `logged_in` and `with_live_server` (`src/core/server.cpp`). `submit` and `handle` lock separately, so another thread could slip in between. Today nothing does, because only the loop thread calls them.
- **SQLite:** one connection, `journal_mode = wal`, `synchronous = normal` (`src/core/server.cpp:75`), no `busy_timeout`. One transaction per request (`Server::handle_request`). Tools read with `mode=ro`.
- **The CDN waits on the game loop.** `HttpServer` takes `Loop::lock_` for **every** handler (`net/http_server.cpp`), static asset downloads included. Yet `cdn::Tree::lookup` only reads, and is documented thread-safe (`include/soaserver/cdn.h`). Several clients downloading assets at start-up (about 100 s each from the shared phone, more from scratch) would hold up game packets for the duration of each file.
- **Lock order today:** `Loop::lock_`, then `Server::mu` (the bridge handler → `record_device` → `with_live_server`). Nothing takes them the other way round.

### 3.2 Measured cost (2026-10-04, main 6970e2c, this machine)

| Replay (`soa-server --replay`, start-up and seeding included) | Requests | Wall time | Per request |
|---|---|---|---|
| `seeded` (Login, a battle, a 10-draw) | 10 | 0.79 s | (start-up dominated) |
| `api-sweep` (every method once) | 106 | 3.77 s | ~30 ms |
| `missions` (MissionStart / End heavy) | 90 | 5.58 s | ~55 ms |

- These are upper bounds: the replay also writes every reply and the state dump.
- A playing client sends a request every few seconds at most, and battles last tens of seconds. **One writer at about 20–30 requests/s is about 100 active players' worth of load.** That is far above a LAN server's.

### 3.3 Design

- **One writer, one connection, one transaction per request; no per-player locks.**
  - `Server::mu` already serializes requests. Per-player serialization would only let two players' requests run at once, and SQLite allows one writer anyway. Nearly every request writes (the stamina tick, `last_login_at`, counters).
  - **Recommended: keep the global mutex** (d). Revisit only if the load test (MC6) misses its targets.
  - `submit` + `handle` become one locked call on the soa-server path (MC1 removes the fid map there).
- **Transaction boundaries** stay one per request: a refusal rolls back only that request, and the commit carries the reply's state.
  - Cross-player writes inside one request are one transaction: FollowAdd writes the follower's row, the rental log writes the lender's count.
  - **Co-op** (MC10) follows schema section 6: StartMultiplay writes the shared `coop_battle` rows in one transaction, then each member's MissionStart in that member's own request transaction, with no transaction spanning players. A refusal for one member (stamina) doesn't undo the others. The relay marks that slot not present (`present[i] = 0`, multiplayer.md 1.8, (b)), and the battle goes on without it (d).
- **Busy handling.**
  - The server's own connection never waits on itself.
  - SQLITE_BUSY can come only from another process: a tool writing, a backup, or a second server, which MC6's lock prevents. The server sets `busy_timeout` = 2000 ms (d). A request that still gets BUSY is refused with 1002 and logged, and nothing is half-written.
  - The read-only tools set their own `busy_timeout`.
- **The relay never waits on the DB.**
  - Lobby and relay sockets join the same poll set (`Loop`), as GameServer's do. Forwarding (Snapshot, Message, AIParameter, Stamp, the barriers) touches only memory.
  - Only MissionStart, MissionEnd and MissionContinue call `answer`. Done synchronously, they hold the loop for one request (≤ 100 ms), which is well inside the client's tolerances: the 300 ms flush, and the spinner after 2.5 s with nothing received (multiplayer.md 1.7, (b)).
  - **If** the load test shows forwarding stalls over the target, MC9 moves `answer` calls onto **one DB worker thread**: the loop posts the Request and an eventfd wakes it with the reply. The worker is still the only writer.
- **Only `/bridge` takes the loop's lock** (MC6). The bridge touches `GameServer`'s token and session maps; the CDN routes and static files don't take it. cpp-httplib's threads then serve downloads in parallel with the game port. The CDN's served-master build happens once at start-up, before listening.
- **Lock order** (documented in `net/loop.h` and ARCHITECTURE.md, checked by a debug assertion): `Loop::lock_` → `GameServer`'s session map → `Server::mu`. Code holding `Server::mu` never takes the other two.

### 3.4 Performance targets (d; the load test of MC6 checks them)

| Measure | Target |
|---|---|
| Concurrent players | **8 logged in, 4 in one co-op room** (the LAN case), without design limits below ~50 |
| API request, server time | p95 ≤ 100 ms, p99 ≤ 250 ms (Login and GetPlayer, the full player state, included) at 8 players sending a request every 2 s |
| Relay forwarding latency added by the server | p99 ≤ 20 ms while API requests are served |
| SQLITE_BUSY in the server | 0 |
| Memory per session | ≤ 1 MB (sessions, keys, the pending request) |

---

## 4. Shared and global state

| State | Scope | Change |
|---|---|---|
| **Server clock** (`clock_now`, `--clock`) and **event calendar** (`event_now`) | server-wide | None. Every player lives on one clock: event terms, the Sphere 211 season, daily resets. A per-player clock is not supported (d; Q9) |
| **Client master** (the CDN's served master: `apply_client_master`, `--enable-events`, the tower banners) | server-wide | None: one CDN for all clients |
| **Gacha pools, master caches** | read-only | None |
| **Gacha state** (step-up, box, limited counts, history) | per player | Schema M1; scoped in M3 |
| **Events** (open windows, NPC helpers, time bonus) | server-wide rules over per-player state | Scoped in M3 |
| **Event rankings** | **cross-player** | MC8 (schema M6): `GetEventRankingInfo` ranks every player's best score (type 6 ascending, (b)); `EventRankingPlayerInfoMap` names each listed player; `GetPlayerDetailInfo(u32)` answers any player's profile (today only one's). The ranking rewards (`CheckEventRankingResult` / `ReceiveEventRankingResult`) pay by the real rank (a: the reward tiers) |
| **Sphere 211** | season server-wide (the calendar), dives per player, ranking cross-player | MC8: the season ranking ranks `sphere_rank` across players; `Sphere211FollowFloorInfo` reads the followed players' floors (needs MC7) |
| **World boss** | **shared** gauges, per-player shares | MC8 (schema M6's `wboss_shared`): a co-op or solo win adds to the shared gauges in the winner's transaction. The wave requirement scales with the players who contributed (schema Q5, (d)) |
| **Rental helpers** | cross-player | MC7 lists real lenders; MC8 counts the lender's rentals and pays the lender's bonus (schema M6 `rental_log`, (a) `master_rental_bonus`) |
| **uid allocators** | server-wide | Schema M2 |
| **The device table** | shared | Schema M2 |

---

## 5. Social features (deferred by task U)

- **Task U step 8** registers explicit stub handlers for FollowAdd, FollowRemove, UpdateFollowMax, BlacklistAdd, BlacklistRemove and the neighbor APIs. They answer success, store nothing and log each call (docs/unimplemented-apis.md "Decisions").
- **MC7 replaces the bodies of those handlers**, and of the existing `social.cpp` ones. It changes no registration, so there is no duplicate-registration error (ARCHITECTURE.md "Duplicates are errors"), and `--list-apis` keeps the file.
- Tables: schema M4.

| API | Answer (MC7) | Evidence |
|---|---|---|
| `FollowList` → `Follow`, `FollowPlayerList`, `FollowID`, `MutualFollowID` | The caller's follows. `CFollowPlayerListElementInfo` {player_id, last_login_at, master_role_id, is_follower} is read from the other players' `player` rows (a cross-player read, declared). FollowList is also the mission helper list today (`rental.cpp`): the helper part stays, now with real lenders first | (b) docs/api.md#followlist, fields.txt:46 |
| `FollowAdd(u32)` → `AddFollow`, `AddMutualFollowID` / `FollowRemove(u32)` | Insert or delete one follow. Mutual = both directions. Caps: `follow_max` (per player, default `follow_default` 30) and `follower_max` 20 on the target, (a). The refusal codes for a full list are (d) until the step reads the client's follow dialogs | (b) keys; (a) caps |
| `UpdateRelationShip(4 × vector<u32>)` | Follow add / remove and block add / remove, applied in one transaction | (b) docs/api.md#updaterelationship |
| `Blacklist` / `BlacklistAdd` / `BlacklistRemove` | The caller's block list, `block_max` 50 (a). Blocking also removes the follow both ways (d) | (b) |
| `SearchPlayer(char[191] search id)` → `SearchResult` | Look the search id up. Not found: 10002 `kPlayerNotFound`, as today (b: the client's dialog). Finding yourself: the client's own case [unknown]; answer the result (d) | (b) |
| `GetPlayerDetailInfo(u32)` | Any player's profile (CFollowInfo), not only the caller's | (b) |
| `GetRecentlyPlayedList` → `RecentlyPlayedDetail` | Co-op partners from `recently_played` (written by MC10), `recently_played_list_length` 30 (a) | (b); (d) "played with" = a co-op battle |
| `UpdateFollowMax` | +`follow_up_num` (5) for `follow_use_coin` (100), up to `follow_max` 300 (a) | (a)+(b) |
| `UpdateSupport(u64)` | Unchanged (already per player); its character is the one the player lends | (b) |
| **Rental / assist helpers** (MissionStart's `BattleRental`, Sphere 211's rentals) | Real players' support characters: followed first, then recently played, then the rest. Blacklisted players are skipped (b: docs/server-rules.md#rental-helpers). The synthetic clones fill the list only when there are too few real lenders (schema Q3) | (a)+(b); (d) the order |
| **Friend codes** | The search id is the friend code: the player's own is shown in the follow menu (`CPlayerInfo.search_id`, (b)), and SearchPlayer takes it. Sequential `LOCAL0000N` ids (Q2) are short enough to read out | (b) |
| `NeighborList` / `NeighborRegist` / `LocationRegist` (GPS) | Stay task U's stubs: location features are out of scope (the port has no GPS; schema 1.2) | (d) |
| Friend gauge | Not served: a dead feature in 3.7.0 (schema Q8, (b)) | (b) |

Tests: schema M4's `social/*` tests on the two-player fixture, plus a two-player replay corpus (section 8): A searches B, follows, B follows back (mutual), A blocks C, and the rental list shows B's support character.

---

## 6. Co-op battles

- **The 3.7.0 client has them.** `FooterMissionInfo.is_open_multiplay` turns on the multi buttons. The lobby (port 4001) and the relay carry the room and the battle, and the relay runs MissionStart and MissionEnd per player. Everything is in docs/multiplayer.md (b, [run] with two unmodified clients and the Python prototype).
- **They are in scope.** The co-op study planned the wire work (HANDOFF.md "Recommended implementation order" 1–3, 6), and this plan doesn't repeat it. This plan adds:
  - **MC9, the listeners in soa-server.**
    - `net/lobby.{h,cpp}` and `net/relay.{h,cpp}` on `Loop` (same poll set, section 3.3).
    - `--lobby-listen`, `--relay-listen`, `--relay-host` (the address written into RoomInfo+0x42a: a literal IP the clients can reach, (b) multiplayer.md §2).
    - The FID tables generated next to `tools/api_wire.py` into `net/gen/`; ChaCha20 for the five 0x80 messages.
    - **`--multiplay`** (off by default) sets `is_open_multiplay` in `home_footer.cpp` (schema Q4: per server).
    - Co-op stages 1–2 (rooms, battle sync) can run with canned bodies before M1–M3.
  - **The relay's identity (MC9).** The relay has no authentication (b).
    - A relay connection is bound at EnterRoom to PDI+0x6c's player id. It is accepted only for a player with a live game session from the **same peer address** (d).
    - MissionEnd's UUID must map (`wire_device`) to that player (d). A mismatch is a ProtocolError.
    - This keeps one LAN client from crediting another's account. It is not security against a hostile network (section 7).
  - **MC10, the co-op API through `answer`.** The relay builds a `Request` and calls `answer(session_of(member), request)` for each member, so every member's MissionStart / MissionEnd runs under that member's caller, with all the scoping above:
    - MissionStart, with the mission from RoomCondition+0x14 (b);
    - MissionEnd, with the member's battle log;
    - MissionContinue (the host);
    - MissionFailed comes from the host over GameRPC (b);
    - `MultiMissionRestart` is answered like MissionRestart for that player (d).
    - The co-op party (PlayerCharacter[4] with owner ids, (b) [run]) is a cross-player read of each owner's statuses (declared).
    - Records (schema M5), the recently-played rows, and the reward rules: `Multi_Player_Number_N` (a), no host bonus (a), guests' stamina (d), in docs/server-rules.md.
- **The in-process port** stays out of co-op (section 1.3; multiplayer.md 4(d)): a `soa` that wants co-op runs with `--server HOST --lobby …`.
- **Out of scope:** the phantom guest (multiplayer.md 4(c1)), RSSIPush, Reconnect (never sent by 3.7.0, (b)), host migration (none in the client, (b)).

---

## 7. Administration and operations

- **Running a multi-user server.** `soa-server --listen 0.0.0.0:44300 --http 0.0.0.0:44380 [--multiplay --lobby-listen … --relay-listen … --relay-host <LAN IP>]`.
  - A new state with no seed save starts without players (docs/server-rules.md#seed). Each new device runs the client's new-player flow (Q1: open or closed registration).
- **Clients.** The 3.7.0 client hard-codes `production-game.so-ana.com:443` (raw TCP with the Ninja cipher, no TLS) and `<lobby host>:4001`. It fetches the bridge and CDN URLs that soa-server hands out; those can't carry a port (emulator/README.md "Networking", (b)).
  - soa (`--server HOST`) and soa-emu map the host through platform370 (`platform370/src/net_370.cpp`: `--server`, `--http`, `--lobby`, `--map-host`). They send `https://` to a mapped host as plain HTTP. That is how users point clients at a server, and it needs nothing new.
  - **There is no TLS anywhere**: the game port never had it, and the platform downgrades the bridge to HTTP. So this is a **trusted-LAN / self-hosted server**: sessions, keys and battle logs cross the network readable to anyone on it.
  - Unmodified Android phones (hosts override, an `https://` bridge URL needing a trusted certificate) are out of scope (Q7).
- **The admin CLI (MC6).** `soa-server --admin CMD …`, on the CLI library of the queued `libs-cli` task. It runs on the state file with the server **stopped**; MC6's owner lock refuses it while a server holds the file. `backup` is the exception: it works online.

  | Command | What |
  |---|---|
  | `list-players` | search id, numeric id, name, level, created / last login, bound devices |
  | `create-player --name N [--device UUID]` | a new player through CreatePlayer's code (the starters), optionally bound |
  | `import-save Game.xml [--device UUID]` | a new player seeded from the user's own save (the seed code: `BAS:PlayerID` never copied; a fresh `LOCAL0000N`) |
  | `delete-player SEARCH_ID` | deletes the `player` row. The FKs cascade (schema Q7); `wire_device` rows get NULL, co-op records keep the battle with the member NULL |
  | `bind-device UUID SEARCH_ID` / `unbind-device UUID` | account transfer (section 1.2) and recovery |
  | `backup FILE` | `VACUUM INTO FILE`, consistent while the server runs (a WAL reader); restore = stop, copy, start |
  | `check` | `state::check` (S11's `--check-state`) plus schema M1's cross-owner queries |

- **Migrations on a live multi-user DB.** Unchanged in mechanism: the server migrates at open, after a `.bak-v<N>` copy (`src/state/README.md`). Route B migrates every player at once. Two operational rules (d):
  1. Upgrade with the server stopped. MC6's owner lock prevents a second binary from migrating a file in use.
  2. Rehearse on a copy first (`soa-server --admin backup`, then open the copy with the new build and `--admin check`). There is no down-migration: a failed upgrade is restored from `.bak-v<N>`.
- **Per-player logging.**
  - Each request's log lines get the caller as a **suffix**, ` [LOCAL00002]`. A prefix would change lines that scripts wait on: `tools/server_log_patterns.txt` anchors `^I/server: request`.
  - The packet log gets the search id per connection.
  - Single-player runs log no suffix, so RG4's tier-1 lines stay identical.
- **Limits and abuse basics** (d; LAN-sized defaults, flags to change them):
  - at most 16 connections per peer address;
  - one CreatePlayer per device, and at most `--max-players` players;
  - the packet size limit the reader already enforces (`kBadSize`);
  - sessions retired by supersession or after 7 days unused (section 1.2);
  - bridge tokens are single-use (today);
  - the relay binding of section 6;
  - an unknown or failing peer gets ProtocolErrors and closed connections, as today.
- **Retries.** The RequestHeader's request id is **kept on a retry** (b, `PresendApiCall` @015b7e48). The session remembers its last ((fid, request id) → reply). A retried request with the same key is answered with the stored reply instead of being applied twice (d). This matters more on a LAN than on loopback: a lost reply must not mean a double gacha draw.
  - **Only logged-in requests count.** In `PresendApiCall`'s not-`LoggedIn` branch the client zeroes the header's +0 and +0xe and skips the request-id block, so a pre-login request carries a stale id (b). Without a guard, CreatePlayer could be answered with a cached Login reply. The cache is consulted only when the header's player id is non-zero, and it is keyed with the fid.
- **Owner lock.** `<db>.lock` with the owner's PID and host, taken at open by soa and soa-server (an advisory `flock`; Windows: `LockFileEx` on the shared Winsock / compat layer). The read-only tools don't take it.

---

## 8. Testing

- **Replay corpora per player (MC2, MC11).** The replay format (`requests.txt`: `wire <n> <t> <Api> <hex>` / `req …`) has no caller. It gains one directive line:
  - `device <uuid>`: the requests that follow come from that device's session (its bridge binding is made like `record_device`'s).
  - A corpus with no `device` line is one default device bound to the state's player, so every existing corpus replays byte-identically.
  - `errors.txt` and the replies get the device's index where there is more than one.
  - New corpora: `two-players` (A and B created through CreatePlayer, interleaved missions and draws, then each one's `GetPlayer`), `social` (MC7), `rankings` (MC8), and `coop` (MC10: the relay's per-member MissionStart / MissionEnd entry points called directly, no sockets).
- **Isolation and scoping.**
  - Schema M3's `server/mp-isolation` and `server/mp-integrity`.
  - MC4's authorizer check over every selftest and every corpus.
  - `tools/schema_inventory.py --lint` in T0.
- **Concurrency.**
  - **`net/mp-load`** (a soa-server selftest; MC6): the poll loop on a thread with a scratch state, and N wire clients (`net/client.cpp`, as the loopback test uses) on N threads. Each bridges with its own UUID, creates its player, and sends M requests (GetPlayer, MissionStart / MissionEnd with a recorded battle log, GachaOnce) in parallel. It asserts:
    - every LoginResult's root `Player.Id` is its own;
    - no reply names another player's uid;
    - each player's end state equals a sequential run's;
    - zero BUSY;
    - the latency percentiles against section 3.4's targets, reported and gated at 3× the target, because machines vary.
    - It runs in T1 for `server/net` changes and T2 always.
  - **The same-method race (MC1):** two clients send the same method interleaved, and each gets its own answer. This fails today by construction (`pending[fid]`).
  - **A ThreadSanitizer build** of the loop test, once (T3), when MC9 adds the relay.
- **Multi-client sessions** (game clients through the slot pool, at most 3 game processes):
  - `emulator/scripts/two_players_session.sh` (MC5): one soa-server, two soa-emu with different devices. Both run the new-player flow and play 1-05; the server state shows two players, each credited only in its own rows (`tools/server_state.py --player`, schema M7).
  - `emulator/scripts/multiplay_session.sh` (MC10, co-op stage 3): from the prototype's `mp_client.sh` / `mp_drive.sh`. Two soa-emu create and join a room, play, and both get their own result. A variant kills the guest mid-battle.
  - One `soa --server HOST` + one soa-emu pair, so the port's network route is covered too (co-op stage 4).
- **The single-player gates stay as they are.** The default game, the smoke test, the replay corpora and `tests/diff` are byte-identical through MC1–MC4. From MC5 on the default single-device run is too: one device, one player.

---

## 9. The steps

Effort is agent time: **S** ≤ half a day, **M** 1–2 days, **L** 3 or more. Every step: T0 per commit, T1 per change, RG4 (`tools/server_replay_diff.sh`) on every corpus, server docs updated (ARCHITECTURE.md, net/README.md, docs/server-rules.md with labels).

### MC1: client sessions

- **What:**
  - `server::ClientSession` (pending, errors, logged_in);
  - `answer(Session&, Request, Fallback)`, and `Server::handle` taking the Request on the soa-server path;
  - `GameServer::Session` owns one, and `LiveBackend::call` takes it;
  - FakeApiCaller uses one static session;
  - the replay uses one.
  - `submit` + `handle` under one lock.
- **Depends on:** nothing; it can land before S12.
- **Proof:**
  - every corpus byte-identical;
  - `net/` loopback with two connections sending the same method interleaved (a new test that fails on main);
  - `wire/inproc-parity` and the port's `server/` selftests;
  - the `seeded` and `tutorial` sessions in both hosts.
- **Effort:** M.
- **Risks:** the in-process two-phase capture (capture now, answer at `ServeProgress`) must keep its fid lookup inside its one session; the EndMissionTalk path's internal `submit` of GetPlayMission must use the same session.

### MC2: the caller's player

- **What:**
  - `GameServer::Session::player_id` (resolved at the bridge and at CreatePlayer);
  - `Ctx::player` and `ctx.player_id()` from the session;
  - `Request` carries `header_player` and `request_id`;
  - the header cross-check after login (refuse with 1002);
  - NoLoginStart playerless once the state holds more than one player;
  - session retirement (supersession, 7 days idle);
  - the replay's `device` lines;
  - `make_ctx(rc, session)`.
- **Depends on:** MC1. It is schema section 6's request → player work, which comes before M1.
- **Proof:**
  - corpora byte-identical;
  - new `net/` tests: a header with another player's id is refused, a device's new bridge retires its older session, and two devices on a one-player state both get that player (today's behaviour, kept);
  - the session gates.
- **Effort:** M.
- **Risks:**
  - The header's +0 for a seeded state: the LoginResult's root `Player.Id` is the player's numeric id, so a client logged in before the change (a cached id) still matches.
  - NoLoginStart's playerless answer must not break the title screen: check it with the `seeded` session before switching.

### MC3: module globals per player

- **What:**
  - the campaign progress without a process cache (or keyed by player);
  - `with_live_server(session, …)` for `end_mission_talk`;
  - per-player notice URLs;
  - per-player RNG streams (the first player keeps today's seed).
- **Depends on:** MC2.
- **Proof:**
  - corpora byte-identical (the `campaign`, `event`, `tutorial` corpora especially);
  - a unit test with two scratch players' campaign progress after M1 (until then, a test that the cache is gone);
  - `campaign` corpus timing within 10% of before.
- **Effort:** S–M.
- **Risks:** the campaign's lock and `with_live_server`'s `Server::mu` order: `progress.cpp` says "callers hold the campaign's lock, never the server's". Keep that order, or drop the campaign lock with the cache.

### MC4: the scope check at run time

- **What:**
  - the authorizer callback in `ext::Sql` (test switch `SOA_SQL_SCOPE_CHECK`);
  - the per-player table set from `RELS` (M1's classification);
  - `ext::cross_player("why")` scope guards at the declared cross-player reads;
  - on in the selftests, the replay gate and the session gates' soa-server.
- **Depends on:** M1 (the tables need `player_id`). It lands with M3 (the scoping it checks): M3's domain commits switch it on per domain.
- **Proof:** a planted unscoped `select count(*) from presents` fails the selftest with the statement text; after M3, every corpus and selftest runs clean.
- **Effort:** M.
- **Risks:**
  - `SQLITE_READ` callbacks come at prepare time, so a statement cached by `ext::Sql` must be checked when first prepared per call site, not per execution.
  - Views and triggers (none today) would need the same classification.

### MC5: several players

- **What:**
  - schema M2's code part: CreatePlayer makes a new player bound to its uuid; the wire uuid must equal the session's; a bound device's CreatePlayer refused;
  - sequential search ids (Q2);
  - `--accounts open|closed` and `--max-players` (Q1);
  - `soa --player SEARCH_ID` (in-process: which account; default the first);
  - `tools/server_state.py --player` (schema M7).
- **Depends on:** M2, M3 (no second real player before M3 passes, schema 8), MC2–MC4.
- **Proof:**
  - the `two-players` corpus;
  - `two_players_session.sh` (two soa-emu, two new players, 1-05 each);
  - `mp-isolation`;
  - the single-player gates unchanged.
- **Effort:** M.
- **Risks:**
  - A state that already has `wire_device` rows for several UUIDs (the user's own devices) binds them all to the first player at M2 (schema M2's mapping). That is right for one person with two devices; the admin CLI separates them if wanted.
  - The client caches `BAS:PlayerID` per device. A device rebound to another player must log in again (the title screen).

### MC6: operations

- **What:**
  - the admin CLI (section 7);
  - the owner lock;
  - `busy_timeout`;
  - per-player log suffixes;
  - the CDN routes off `Loop::lock_` (only `/bridge` keeps it);
  - connection and player limits;
  - the retry cache (request id → reply);
  - the lock-order assertion;
  - `net/mp-load`.
- **Depends on:** MC5.
- **Proof:**
  - `net/mp-load` within its gate;
  - admin commands tested on a scratch state (create, import a test save, bind, delete with cascade, backup during a running loop test);
  - a second soa-server on the same file refuses to start;
  - a retried request (same request id) is not applied twice.
- **Effort:** M.
- **Risks:** the CLI library (task `libs-cli`) not landed yet: use the existing option parser and move later. Windows file locking (`LockFileEx`) and WSL's `\\wsl.localhost` (no SQLite locks there, AGENTS.md).

### MC7: social

- **What:** section 5. The handler bodies in `api/social/` replace task U's stubs and the empty lists.
- **Depends on:** M4, task U step 8 (the stubs registered), MC5.
- **Proof:**
  - schema M4's tests;
  - the `social` corpus;
  - a session: two soa-emu, A searches `LOCAL00002`, follows; B sees the follower and follows back; the room filter 相互フォロー then finds the room once MC10 lands;
  - `tools/unhandled_apis.py --summary` unchanged (the stubs were handlers already).
- **Effort:** M–L.
- **Risks:**
  - The refusal codes for full lists and self-follow are (d) until the client's follow dialogs are read.
  - The rental list mixes real and synthetic lenders (schema Q3).

### MC8: shared state

- **What:** rankings across players (events, Sphere 211, its follow floors), the shared world boss, the rental log and the lender's bonus (schema M6).
- **Depends on:** M6, MC7.
- **Proof:** schema M6's tests; the `rankings` corpus (two players' scores, the rank order, the detail dialog of the other player); the world boss gauges summed over two players.
- **Effort:** M.
- **Risks:** the world boss scaling rule (schema Q5) is (d) and visible to players; label it in the register of docs/server-rules.md.

### MC9: the co-op wire

- **What:**
  - lobby and relay listeners on `Loop` (HANDOFF.md steps 1–3, 6);
  - `--multiplay`;
  - the relay's identity binding (section 6);
  - MissionStart / MissionEnd answered with canned per-member bodies until MC10.
- **Depends on:** MC2 (distinct sessions). It can run beside M1–M3.
- **Proof:**
  - the codec selftests against the client's own `Set*` / `Get*` (differential, as `wire_test.cpp`);
  - ChaCha20 vectors;
  - the relay state machine tests;
  - co-op stages 1–2's session (two soa-emu, one soa-server: room, start, barriers, both results);
  - the relay forwarding latency in `net/mp-load` (a third client pair in a room).
- **Effort:** L.
- **Risks:** multiplayer.md 3.4: rush-combo arbitration unknown; the stamp picker crash in soa-emu; 3–4 players untested.

### MC10: the co-op API

- **What:**
  - per-member MissionStart / MissionEnd / MissionContinue through `answer` under each member's session;
  - battle records (M5), recently played;
  - MultiMissionRestart;
  - the reward rules.
- **Depends on:** M5, MC5, MC9.
- **Proof:**
  - the `coop` corpus;
  - `multiplay_session.sh` (co-op stage 3): both players credited in their own rows, `ended_at` set, a repeated MissionEnd refused;
  - the ownership trace (HOST / GUEST tags);
  - the guest-killed variant.
- **Effort:** L.
- **Risks:** the PlayerCharacter[4] filler rule (HANDOFF.md "Open questions") and the guests' stamina are (d); the owner-id copy into CCharacterObject+0x1068 is inferred, not traced (HANDOFF.md).

### MC11: tests across players

- **What:**
  - the replay `device` lines (with MC2);
  - the two-player fixture (schema M3);
  - the corpora of sections 5–6;
  - the sessions of section 8 in `tests/tiers.json` (T2; the co-op session T3 until stable);
  - `tools/replay_coverage.py` counting each API's two-player coverage.
- **Depends on:** spread over MC2, MC5, MC7, MC10.
- **Effort:** M in total.
- **Risks:** timing of two GUIs (multiplayer.md 3.4: lost taps; generous waits and screenshots after each step).

### Risks across the plan

- **The largest is M3's scoping and MC4's check,** not the wire. One missed `player_id` leaks or corrupts another player's rows. Static lint + dynamic authorizer + isolation tests are the three nets. The rule from the schema plan stands: **no second real player before M3 passes**.
- **Two plans, one order.** The schema plan waits for S12; MC1–MC3 don't. Landing MC1–MC3 early keeps them small (single-player, byte-identical) and makes M1's commits mechanical.
- **No TLS** (section 7) limits this to trusted networks. It is a property of the client's protocol, not something the server can fix.

---

## 10. Open questions for the user

| # | Question | Recommendation |
|---|---|---|
| **Q1** | Account creation: may any new device create an account (open registration), or only devices an admin bound or created? | `--accounts open` by default (a LAN server's users are the owner's friends), `--accounts closed` refuses a CreatePlayer from an unknown device (d: 19001 → the new-player flow → a refused CreatePlayer, error code to pick from the client's texts), plus `--max-players` |
| **Q2** | Search ids: sequential `LOCAL0000N` or schema M2's `LOCAL` + 5 digits of a hash? | Sequential: unique without collision handling, deterministic in tests, short to read out as a friend code. The numeric id stays CHash32(search id) |
| **Q3** | Moving an account to another device: the admin CLI only, or also an in-game page behind 引き継ぎ (`bridge_user`) with a transfer code? | The admin CLI (`bind-device`) first; an in-game page only after the web view's forms work (docs/webview.md) |
| **Q4** | A RequestHeader player id that doesn't match the session's player after login: refuse or only log? | Refuse with 1002 and log (a client on the wrong account must not write to another's state) |
| **Q5** | The in-process `soa` on a multi-player state: which player (schema Q2)? And enforce the single-writer lock? | `--player SEARCH_ID`, default the first player; yes, an owner lock file (MC6) |
| **Q6** | Size target: how many players should one server support? | 8 logged in and 4 in a room (the LAN case), with no design limit below ~50; the global mutex stays until the load test says otherwise |
| **Q7** | Unmodified Android phones as clients (a hosts override, an `https://` bridge needing a trusted certificate, cleartext HTTP)? | Out of scope: soa and soa-emu are the supported clients (both map the hosts already) |
| **Q8** | Per-player RNG streams (`--seed-rng`), so multi-player replays are deterministic whatever the interleaving? | Yes, with the first player keeping today's stream (every existing corpus byte-identical) |
| **Q9** | One server clock for every player (`--clock`, events, seasons, daily resets)? | Yes: per-player clocks would break shared rankings and the world boss |
| **Q10** | Retries: store each session's last reply by (fid, request id) and answer a retry with it? | Yes (b: the client keeps the request id on a retry), only for logged-in requests (a pre-login header carries a stale id, (b)); one reply per session, not a history |
| **Q11** | The schema plan's open Q3–Q9 (synthetic rentals as fill-up, multiplay per server, world boss scaling, `coop_battle_id` checked not declared, player deletion, friend gauge, follow caps) | Unchanged; this plan assumes their recommendations |
