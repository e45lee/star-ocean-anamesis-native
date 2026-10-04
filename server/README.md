# server/: the local game server (libsoaserver, soa-server)

The local server emulator for STAR OCEAN: anamnesis, as a library: the game APIs, the player state
(SQLite) and the 3.7.0 master data. It is our code, not guest behaviour; every rule it applies is
labelled (a) master data, (b) client-side evidence, (c) outside knowledge or (d) assumption, in the
code and in `docs/server-rules.md`.

Two programs use it:
- **`soa`** (the port, `port/`) runs it in-process (`--server inproc`, the default): the FakeApiCaller hooks hand it
  each request and deliver its responses (`port/src/native/api/fakeapi.cpp`).
- **`soa-server`** (`app/main.cpp`) runs it standalone, out of process, for the unmodified 3.7.0
  client: it speaks the game's own wire protocol (`net/`: TCP packets, the Ninja cipher, the request
  decoder, the SQEX BRIDGE handshake, an HTTP server), see "soa-server and the wire layer" below. It
  also runs the library's and the wire layer's unit tests (`--selftest`).

The library includes nothing from `port/` or `runtime/` (CMake checks this at configure time).

**Start here:** [ARCHITECTURE.md](ARCHITECTURE.md) (how a request becomes a reply, the module registry
and its order, clocks, where state lives), [API-INDEX.md](API-INDEX.md) (generated: every API, its
handler, hooks, rules sections and tests), the folder READMEs (`src/`, `include/soaserver/`, `net/`,
`tests/`), and "Comment conventions" below. `PLAN-readability.md` and `PLAN-schema.md` are the plans
for the code's structure and the state schema.

## Layout

| Path | What |
|---|---|
| `include/soaserver/` | The public headers (below) |
| `src/` | The server ([src/README.md](src/README.md) by domain): `core/` (`server.cpp`: the server object, the core APIs, the dispatcher; `request_context.h` a request's own state; `ext.cpp` the module registry; `modules.cpp` the module order; `clock.cpp` the event calendar; `support.cpp` config, log, asset index, CHash32; the shared helpers of R6: `time` (local times, reset day, windows), `errors.h` (named refusal codes, generated), `response` (envelope, player-state answer, refusal), `wallet` (coins, FOL, stack items), `request_args.h` (the core handlers' arguments), `assets` (the one asset gate)), `api/<domain>/` the extension modules (registered through `ext.h`; one folder per API group), `rules/` (`rules::`, `mission_rules`, `growth_rules`), `state/` (the Game.xml codec, seeding), `master/` (`master`: the shared master lookups; `gacha_pools`, `npc_status`), `cdn/`, `testing/` (the test registry) |
| `tests/` | The cross-cutting tests: `tests/net/`, `tests/ninja/` (below) and `tests/replay/` the replay corpora (RG4). The library's unit tests live beside their code in `src/` (`*_tests.cpp`, or at the end of a source file) |
| `app/` | `soa-server`'s command line; `replay.cpp` (`--replay`, `--list-apis`, `--list-hooks`) |
| `net/` | the wire layer (`libsoanet`, linked by `soa-server` only): `wire.*` packets, decoder, battle log, reply bodies; `ninja/` the cipher; `game.*` sessions and the bridge; `http.*`; `loop.*` the sockets; `client.*` a wire client (tests, `--wire-tool session`); `tool.*` `--wire-tool`; `gen/wire_decode.inc` (generated) |
| `tests/net/`, `tests/ninja/` | the wire layer's selftests (compiled into `soa-server`, not `soa`): `client_requests.txt` and `ninja_vectors.txt` are the client's own packets and envelopes; `tests/ninja/tools/` the unicorn harness that runs the client's code to make them, `tests/ninja/ninja_check.*` a stand-alone cipher CLI |

Build: part of the repository's build (`cmake -S . -B build && cmake --build build`, README.md
"Building"): `build/server/libsoaserver.a`, `build/server/libsoanet.a` and `build/server/soa-server`
(`cmake --build build --target soa-server` for the server alone; `-DSOA_BUILD_PORT=OFF
-DSOA_BUILD_EMULATOR=OFF -DSOA_BUILD_VIEWER=OFF -DSOA_BUILD_PLATFORM370=OFF` configures only the server, without dynarmic, the runtime, SDL2 or EGL). It needs
SQLite and OpenSSL's libcrypto (and zlib for `soa-server`), static from vcpkg
(`unofficial::sqlite3::sqlite3`, `OpenSSL::Crypto`, `ZLIB::ZLIB`; `cmake/deps.cmake`), and `soa_codec`
(`common/`: Base64 and the Game.xml SharedPreferences XML, on OpenSSL and pugixml). Link it whole (`$<LINK_LIBRARY:WHOLE_ARCHIVE,soaserver>`):
the tests register from static initializers. The modules register from their `register_<module>()`
functions, in the one order of `src/core/modules.cpp` (ARCHITECTURE.md "The module registry and its order").

## Comment conventions

How the server's code is commented (server/PLAN-readability.md sections 2.2, 2.5 and 3 are the full
policy; `tools/server_evidence.py` checks that no evidence is lost).

- **Every rule carries its source label** next to the code: **(a)** master data (name the table and
  column), **(b)** client-side evidence (name the client function, with its address `@xxxxxxxx` or
  the struct offset `CParameterManager+0x…` it reads), **(c)** outside knowledge, **(d)** an
  assumption (say why). The same rule has the same label in the code and in `docs/server-rules.md`;
  player-visible (c) / (d) rules are also listed in its "Register of (c) and (d) rules".
- **Evidence is never deleted:** labels, client symbols, addresses, offsets, master table names,
  test-data provenance and `380-ok` markers move with their code.
- **Say what and why, not who.** No "agent X" notes in code (`git log -S` finds the author;
  docs/history/ keeps the narrative): describe the rule and its evidence instead. Enforced
  (`tools/check_server_docs.sh`: 0 since R19).
- **Remove what describes code that no longer exists** (canned files, removed options), and say so
  in the commit message.
- **Link the docs** by anchor: `docs/server-rules.md#titles`, the explicit `<a id="titles"></a>` above
  a section of that doc (one section per `api/<domain>`; `tools/server_rules_doc.py --anchors` lists
  them). A quoted title (`docs/server-rules.md "Titles"`) is no longer accepted (R20), and a link
  that doesn't resolve fails `tools/check_server_docs.sh`. A new (c) / (d) rule the player sees gets
  a row in its domain's "Player-visible (c) and (d) rules" table; `tools/server_rules_doc.py
  --write` regenerates the register from those tables.
- **A log line a script reads** (`tools/server_log_patterns.txt`) keeps its text exactly; mark it
  `// read by <script>` when you touch it.
- **Handlers** get a doc block: the method signature and reply, the `API:` / `Rules:` links, a
  sentence of purpose, each rule with its label, and what the answer carries (the template:
  PLAN-readability.md 2.5). Response builders say which client class they fill (`CPlayerInfo` ...).
- **Formatting** is `server/.clang-format` (today's style, measured): `tools/format_server.sh`
  formats, `--check` lists what isn't formatted. It needs clang-format 18 (the system one; set
  `CLANG_FORMAT` for another binary). The Ninja cipher tables and the generated decoder table are
  left alone (`server/.clang-format-ignore`).
- **Checks (enforced since R19; T0's `server-docs` and `server-format`, tests/TIERS.md):**
  `tools/check_server_docs.sh [--evidence REV]` fails on any finding: a handler without the 2.5
  block (with a label, or `Rules: none (transport)`), a hook or an `include/soaserver/` function
  without a doc comment (`tools/server_doc_coverage.py`), a broken docs link, a stale API-INDEX.md
  or errors.h, an "agent" note, a missing server/ path or README, evidence lost against REV (T0
  passes `--evidence` the parent; a commit that deletes labelled code says so with a line starting
  `Evidence removed:` in its message). `tools/format_server.sh --check` fails on any unformatted
  file. `--report` prints the findings without failing (lost evidence and log lines still fail).

## API

Not every method has a handler yet: [`../docs/unimplemented-apis.md`](../docs/unimplemented-apis.md) lists the 93 that don't, what the client gets for each today, and the plan (`tools/unhandled_apis.py` regenerates the list).

| Header | What |
|---|---|
| `server.h` | `Request` (method, fid, ints, strs, vecs, optional battle log); `answer(Request, fallback)` (the request lifecycle both hosts use: EndMissionTalk, the story campaign, `submit` / `handle(fid, out)` / `error_code(fid)`; a `Reply` {body, error_code, handled}), `end_mission_talk(mission)`; `enabled()`; clocks `clock_now()` / `set_server_clock()` / `event_now()`, the test seam `set_clock_source()`; `logged_in()`, `new_player_mode()`, `web_page(url)`; `apply_client_master(db, now, event_now, master)`; the pure `rules::` |
| `config.h` | `ServerConfig` / `config()`: everything the server is configured with (below); `find_repo_file`; `parse_clock` / `set_clock`; `kDefaultEventKeywords` |
| `hooks.h` | What the server asks its host: `AssetIndex` (below) |
| `battle_log.h` | `BattleLog` (the ASON battle log MissionEnd & co. carry: `ason()`, `prop_u32`, `evaluation`), `parse_battle_log`, `carries_battle_log` |
| `log.h` | `set_log_sink(write, enabled)`: where the server's log lines go (default stderr, `I/server: ...`) |
| `ext.h` | Extension modules: the registration functions (`add_api`, `add_player_load`, `add_response_hook`, `add_grant`, `add_item_extra`, `add_mission_start_extra`, `add_mission_result_extra`, `add_client_master`), `hook_order`; `Ctx`; shared state helpers |
| `events.h`, `api_campaign.h` | The event and campaign modules' entry points the port calls (`events::end_mission_talk`, `campaign::on_request` / `on_response` / `end_mission_talk`) |
| `msgpack.h` | `Value`, `mp_encode` / `mp_decode` (the response bodies) |
| `chash32.h` | `chash32`: the game's `Framework::CHash32` (the port's CHash32 natives use it too) |
| `adld.h` | ADLD packing: `decrypt` / `encrypt` (XOR, AES + DCNE), `Encrypt::CEncryptAES128`'s functions (the port's natives and the ADLD callback use them) |
| `cdn.h` | The CDN content: `cdn::Tree::build(Options)` / `build_from_config()`, `Tree::lookup(url_path, Response&)`, the bundle (`bundle_bytes`, `bundle_sha1`) and served-master (`make_served_master`) pieces |
| `testing.h`, `native_test.h`, `scratch.h` | The unit-test registry (`NATIVE_TEST`, the port's spelling), its runner, and a scratch server for tests outside the library |

### Configuration (`ServerConfig`)

`enabled`, `new_player`, `master`, `db`, `seed`, `game_xml`, `has_seed_rng` / `seed_rng`,
`start_coins`, `has_clock` / `clock` / `clock_offset`, `galaxy_pass`, `enable_events`,
`event_keywords`, `restore_tower`, `home3d_all`, `campaign_master_db`, `campaign_seed`, `fail`, `surprise`,
`repo_roots` (where `data/basmaster-3.7.0.sqlite3`, the seed saves and `port/server-data` are found),
`data_root` (the data dir: the CDN's scratch files; a `server_campaign.txt` there from before the state DB's version 11 is imported once, PLAN-schema S12).

- **soa** fills it from its run options (`soa::options()`, `port/README.md` "Run options") in
  `server_port::config_from_options` (`port/src/native/api/server_adapters.cpp`), called by `main` once
  the options are final.
- **soa-server** fills it from its command line, with the same flags as soa's server options
  (`--db`, `--master`, `--gacha-pools`, `--seed`, `--game-xml`, `--seed-rng`, `--new-player`,
  `--clock`, `--start-coins`, `--galaxy-pass`, `--enable-events`, `--event-keywords`,
  `--restore-tower`, `--home3d-all`, `--campaign-master-db`, `--campaign-seed`, `--fail`, `--surprise`,
  `--download-dir`, `--standin-assets`, `--repo`) plus its own `--data` (the state DB's directory).
  `soa-server --help` lists them. The events defaults are soa's too: `--event-keywords` defaults to
  the summer events (`kDefaultEventKeywords`, "水着,夏,サマー,!福袋").
- **Neither reads a setting from the environment.** A `SOA_*` variable that was one prints one line naming
  its flag and is ignored
  (`common/include/soa/env.h`, `docs/environment.md`). The library's only environment variable is
  a self-test dump, `SOA_NOTICE_HTML_DUMP=FILE` (`player/notice` writes the notice page's HTML there).

### The host interface (`hooks.h`)

The server learns everything about the client from the requests, as the 3.7.0 wire carries them (H,
`docs/server-hooks-review.md`): soa's FakeApiCaller route builds the same `Request` soa-server's wire
decoder does, battle log included. The one question left for the host is which asset files exist.
(Until H, 2026-10-01, `hooks.h` also had `BattleLog` as a guest-reading hook, `StatusProvider` and
`InGameHooks`: the login-bonus popup request, the tutorial-cleared fallback and the campaign's
party fallback.)

| Interface | Used for | soa | Default (soa-server) |
|---|---|---|---|
| `AssetIndex` (`exists`, `empty`) | gating content on its files (event maps, Sphere 211, deep space areas, tower banners, `--enable-events` banners) | the AssetManager: APKs, `--download-dir`, stand-ins (`find`, then `find_download`) | `cdn::asset_index_from_config()`: `dir_asset_index({--download-dir, the stand-ins})`, the files the CDN serves (`--standin-assets off` leaves the stand-ins out; `builtin_data/<rel>` files only; no APK index yet); none (empty) = nothing gated |

### Requests

A request is a neutral `Request` (method name, FunctionID, its integer, string and vector arguments
in order, and the battle log of MissionEnd, MissionFailed, Sphere211MissionEnd and
Sphere211MissionFailed). soa builds it from the guest registers of the FakeApiCaller method
(`server_port::inproc_request`: the arguments by the method's mangled signature, the battle log from
the client's own serializer) and calls `submit()`; the wire decoder (`net/wire.cpp`) builds the same
struct (port test `wire/inproc-parity` compares the two). `handle(fid, ...)` then answers the pending request of that
fid in one transaction (refusals roll back and set `error_code(fid)`).

### The state DB and its upgrades

The player state is one SQLite file (`--db`; soa-server's default `--data DIR/server.sqlite3`, soa's
`DATA/server.sqlite3`), its schema versioned by `pragma user_version` (`src/state/README.md`). Opening an
older file upgrades it in place, step by step, after copying it to `<file>.bak-v<old version>`; a
file newer than the build is refused and left untouched. **There is no down-migration**: to go back
to an older build, restore the `.bak-v<N>` copy that build wrote.

### The client's master copy

`apply_client_master(db, now, event_now, server_master)` applies the server's master-data overrides
to a master DB: it drops `master_global.service_stop_day` and runs the modules' `ext::ClientMaster`
hooks (date shifts of the event tables, Sphere 211 seasons, shop windows, tower banners) with the
given server clock and event calendar. Both server modes' CDNs (soa-server's, and soa's in-process
one) run it on the copy of the 3.7.0 master they serve; the client downloads that copy.

## soa-server and the wire layer

```sh
build/server/soa-server [--listen 127.0.0.1:44300] [--http 127.0.0.1:44380] [--data DIR] [--download-dir DIR] \
    [--log-packets DIR] [--new-player] [the library options: --clock, --start-coins, --galaxy-pass ...]
```

- **`--listen HOST:PORT`**: the game server (the client's `production-game.so-ana.com:443`, raw TCP).
- **`--http HOST:PORT`**: the HTTP server: `POST /bridge` (the SQEX BRIDGE stand-in) and, with
  `--download-dir`, the CDN (below) under `/download/`, `/master/` and `/Android/`
  (`net/cdn_http.h`; if the CDN can't be built, the download is served as is under `/Android/`).
  `--bridge-url` overrides the URL sent to the client (default `https://production-game.so-ana.com/bridge`).
- **`--cdn-url URL`**: the base Login sends (`AssetPath` = URL/download, `MasterPath` = URL/master,
  `r_ver` = the served revision); default `http://production-game.so-ana.com`.
- **The default URLs name the client's own host, without a port**: the 3.7.0 client's URI parser keeps
  a URL's `:port` in the host name it resolves, so a URL with a port can't work. A client must map
  `production-game.so-ana.com` to this machine and send those URLs to `--http` as plain HTTP; soa-emu
  does (`--server` / `--http`, emulator/README.md "Networking"). For a client that takes ported URLs:
  `--bridge-url http://<--http>/bridge --cdn-url http://<--http>`. `--standin-assets DIR|off` (default
  `standin-assets`), `--cdn-scratch DIR` (the served master and the bundle-hash cache; default
  `DATA/cdn`), `--cdn-check [PATH...]` (build the CDN, print it and the answers for URL paths, exit).
- **`--log-packets DIR`**: `DIR/packets.log`, one line per message (connection, sequence number,
  name, FunctionID, cipher, sizes, the decoded arguments, the reply's `data` keys and status), and
  every body: `<n>-<Request>.bin` (plaintext), `<n>-<Reply>.msgp`, `<n>-MissionEnd-battle_log.msgp`
  (and `<n>-LoginResult-sent.msgp`, the LoginResult as sent, with its root `Player`).
- **`--new-player`**: a fresh state starts with no player, so the client's Login gets 19001 and runs
  the new-player flow (terms, name, `CreatePlayer`). Without it the state is seeded with the
  `LOCAL00001` player, which every device gets (`docs/server-rules.md` "soa-server: the wire layer").
- **`--wire-tool CMD`**: `reply` (the MessagePack as hex, or `@FILE` for a body too long for an
  argument) / `start` / `update-session` / `error` build reply packets,
  `decode` reads a request packet, `session HOST:PORT [UUID] [HTTP]` runs a client session (bridge,
  Login, GetPlayer, GetServerTime) against a running server; a bridge URL on
  `production-game.so-ana.com` is POSTed to HTTP (default HOST:44380).

**What happens on a connection** (the client side: `docs/online-server.md` §3-4):
1. Every packet is `header(24, scrambled) | body | SHA-1`; `net::PacketReader` checks the SHA-1 (a
   mismatch is answered with a ProtocolError) and `net::encode_packet` builds replies (the request's
   counter echoed, the header scrambled with our CLOCK_MONOTONIC).
2. **StartBridge** (clear) -> **ResultStart** (clear: `char[1024]` token, `char[128]` URL, `char[8]`).
3. The client POSTs `{"UUID","deviceType","nativeToken"}` to the URL; `/bridge` answers with the gzip
   of `{"nativeSessionId": 32 hex, "sharedSecurityKey": 64 hex}` and records the device
   (`wire_device` table in the state DB).
4. **UpdateSession**(session id) -> **ResultUpdateSession**: the connection now uses the session's key
   (its first 32 characters are the Ninja key).
5. Every other request: Ninja-decrypted (any of the ten algorithms), decoded by its layout
   (`net::decode_request`) into the same `server::Request` soa captures from FakeApiCaller, answered by
   `submit` / `handle` / `error_code`, and sent back as `<Name>Res` (u32 length + MessagePack; Login /
   SimpleLogin: fid + length + MessagePack), AES-128-encrypted unless the reply is one of the clear
   ones. The LoginResult body also carries a top-level `Player` `{Id, Level, Name}`: the client's
   `CApiNotify::OnLoginResult` reads that (its legacy `CParameterPlayer`, which `LoggedIn` checks
   before every later API), not `data`.
6. **Reconnects.** The client opens a connection per request and closes it after the reply; while
   logged in it reconnects and sends the next request encrypted, with no StartBridge or
   UpdateSession. An encrypted request on a connection without a session is bound to the session
   whose key decrypts it (newest first; the envelope's keyed trailer rejects the others).
7. **After a ProtocolError** the connection is closed (the client's network thread then closes the
   socket itself; `docs/server-rules.md` "A ProtocolError ends the connection"). The hidden
   test switch `--keep-open-after-error` keeps it open (soa-emu no longer needs the close: the
   runtime emulates Top Byte Ignore).
8. **The story campaign** is called as soa's FakeApiCaller route calls it: `campaign::on_request`
   after every request, `campaign::on_response` on every reply body (`ActiveMissionList` ...), and
   `EndMissionTalk` (3.7.0's end of a story scene, which the library has no API for) runs the
   events' / campaign's `end_mission_talk` and is answered with the GetPlayMission body, as soa does. A refusal (`error_code` != 0) is a **ProtocolError** (status = the error code, the failing
   fid), which the client turns into `error_message_text_<code>`. A LoginResult / SimpleLoginResult is followed
   by a GetPlayerRes with the same body: the client's `OnLoginResult` doesn't end the request, an
   `On<Api>Res` does (`docs/server-rules.md` "Login ends with a GetPlayerRes"). A request the server has no
   handler for gets `{"data": {"Time"}, "status": 0}` (logged).

**The decoder.** `tools/api_wire.py --gen-decoder server/net/gen/wire_decode.inc` (needs `work/`'s
lib) writes the table: per request its measured layout (`docs/api-wire.txt`), the server method
(the serializer's name except `UpdateName` -> `UpdatePlayerName`), whether it is encrypted, and its
reply (fid, encrypted, body kind). Arguments map positionally: integers (u8 ... u64; f32 as its bits)
-> `ints`, `str[N]` (up to the first NUL) and blobs -> `strs`, vectors -> `vecs`. The shims
(`wire.cpp`): the battle log of MissionEnd / MissionFailed / Sphere211MissionEnd /
Sphere211MissionFailed becomes `Request::battle_log` (`soaserver/battle_log.h`'s parser, the one
soa's route uses too: a `BattleLog` over the ASON map, `prop_u32(name)`, `evaluation(type)` = the last
`BattleEvaluationInfo` score of the type); the
DeviceType of NoLoginStart / CreatePlayer / MissionContinue is dropped (kept in `Decoded` and the
packet log); CreatePlayer's strings are reordered to the method's `(name, uuid)`; Login and
SimpleLogin keep no arguments (the method takes none).

**Ground truth.** `tests/ninja/tools/gen_ninja_vectors.py` runs the client's own code under unicorn
(needs `work/`'s lib): `requests` serializes 11 requests (Login, GetPlayer, SetTitle, MissionStart,
MissionEnd with a battle log, GachaOnce, LockItem, CreatePlayer, StartBridge, UpdateSession,
NoLoginStart) with the client's `Set<Api>` and Ninja into `tests/net/client_requests.txt`, which the
selftest decodes; `replies` feeds packets built by `soa-server --wire-tool` (GetPlayerRes,
MissionStartRes, MissionEndRes, GachaOnceRes, NoLoginStartRes, EquipAccessoryRes, LoginResult,
ResultStart, ResultUpdateSession, ProtocolError) to the client's `Deserialize` and `Get*` readers,
which accept all ten.

## CDN (`cdn.h`, `src/cdn/`)

What the 3.7.0 downloader gets (protocol: `docs/online-server.md` §6; rules and labels:
`docs/server-rules.md` "soa-server: the CDN"). Every URL the client builds is
`<AssetPath>/<r_ver>/Android/<name>`, and Login sends `AssetPath` = `http://<--http>/download` and
`r_ver` = the served revision, so the client asks for e.g.
`http://127.0.0.1:44380/download/1472/Android/version.bin`.

**In-process too (the rebased port, `port/rebase-370`):** `soa --server inproc` builds the same tree
from its `--download-dir` and serves it with this directory's `net/` HTTP router (`mount_cdn`), called
in memory as platform370's HTTP backend: no socket, no port, no thread (`port/src/native/api/server_cdn.cpp`;
"The router in memory" below), and sets `cdn_url`, so the in-process Login carries the CDN keys like soa-server's. The 3.7.0 client
needs them to mount its download storage (`port/README.md` "Rebase (in progress)").

`cdn::Tree::build` (once at startup; about 3 s warm, the bundle hashes cached in
`<scratch>/cdn-bundles.cache`):
1. **The master**: `data/basmaster-3.7.0.sqlite3` (`--master`) copied to
   `<scratch>/basmaster-served.sqlite3`, given `apply_client_master` (the same overrides soa's
   in-process client master gets), VACUUMed, ADLD-AES packed (`adld.h`) as
   `<scratch>/basmaster-served.adld`.
2. **Stand-ins**: the files of `standin-assets` the download lacks become new members, one
   Individual bundle each and one Bulk bundle.
3. **Bundles**: the client only downloads bundles (`\0ISF` images of member payloads, checked by
   SHA-1). The download holds their members unpacked, so every bundle of the manifests
   (`manifest/etc2/hi/version_latest_{Bulk,Individual,ep1,ep2,ep3}.bin`) is rebuilt from them, on
   request; the served manifests carry our bundles' SHA-1 and size.
4. **version.bin and the manifests**: revision + 1 (1472), new version ids, the master's and
   stand-ins' entries, re-encoded (`msgpack.h`; decode -> encode of the 3.7.0 version.bin is byte
   for byte).

`Tree::lookup(url_path, Response&, stream = false)` answers `…/Android/<name>` (any prefix) and
`/master/<rev>/<name>`: version.bin, `manifest/etc2/hi/*`, a bundle (built in memory, or with
`stream` its members as `Response::bundle`), the served master (`sqlite/basmaster.sqlite3`), a
stand-in, or a file of the download; `Response` holds the bytes, a file path or the bundle, and the
content type. `Response::open()` reads any of them in pieces (`cdn::Reader`: a file or a bundle's
members are read as asked for, never held whole). `lookup` only reads the tree: it is thread-safe.
No sockets: soa-server mounts it with `net::mount_cdn`.

### The router in memory (`net/http.h`)

`HttpRouter::handle(const HttpRequest&, HttpResponse&)` is the whole answer to one request, with no
connection: soa-server's poll loop calls it per parsed request, and the port's in-process server
(`soa --server inproc`, `port/src/native/api/server_cdn.cpp`) calls it directly, with the router
`mount_cdn` set up (the same handlers), as platform370's HTTP backend: no socket, no port.
- **`make_request(method, target, headers, body)`** builds the request as `HttpParser` does from the
  wire (the parser uses it): the URL-decoded `path` and the `query` from `target`.
- **`HttpResponse::stream`** (`HttpBodyStream`: `size()`, `read(buf, n)` > 0 / 0 at the end / < 0
  error): a body read in pieces instead of `body`. The CDN's handler streams files and bundles;
  `content_length()` is the body's length either way. An in-memory caller reads the stream as it
  goes; the poll loop calls `materialize()` (the stream read into `body`; a failed read is a 500)
  and sends what it sent before, byte for byte.
- `net/cdn-in-memory` (with `net/cdn-loopback`'s synthetic tree) checks the in-memory answers,
  streamed in small pieces, against `Tree::lookup` and the loop's materialized bodies.

```sh
build/server/soa-server --download-dir work/download-3.7.0 --cdn-check \
    /download/1472/Android/version.bin /download/1472/Android/I/86c7aec3/3a05a888.bin
```

## Tests

The library's unit tests (beside their code in `src/`) use scratch servers (a state DB under `/tmp` seeded from the committed
synthetic `port/server-data/test-seed.xml`, with `data/basmaster-3.7.0.sqlite3`) and need no game:

```sh
build/server/soa-server --selftest            # all (91 today: 70 server/, 7 cdn/, 14 net/)
build/server/soa-server --selftest "server/sphere211"
build/server/soa-server --selftest "net/"     # the wire layer only
build/server/soa-server --selftest --shuffle 7   # all, in an order shuffled with seed 7 (order dependencies)
```

**The replay proof** (`tests/replay/README.md`): `soa-server <options> --replay DIR --out OUT` runs a
recorded request sequence through the library as soa-server's connection would (at the recorded
times, through the clock-source seam) and writes every reply, error code, the end state and the log;
`tools/server_replay_diff.sh PARENT CHILD` does that with two builds over every corpus and compares
(`tools/server_build_at.sh REV DIR` builds a revision's soa-server alone). A refactor of the server
must come out identical. `soa-server --list-apis` lists every method with what answers it, `--list-hooks` every module hook in its run order.
`tools/server_evidence.py [--against REV]` counts the rule labels, client addresses, symbols,
offsets, master tables and docs links in the comments (nothing may be lost).

The wire layer's tests (`net/...`, only in soa-server): header scramble against docs/api.md's
measured packet, packet round trips (a corrupted SHA-1 or body refused, a bad size), decoder round
trips for all 193 layouts (encode -> decode -> compare, truncated / trailing bytes refused), the
client's own request packets (`client-requests`), the battle log, reply bodies, HTTP parsing and
routing, gzip and the bridge JSON, the 700 Ninja vectors (`net/ninja-vectors`), and `net/loopback`:
the poll loop on a thread with a scratch server, a client doing StartBridge -> HTTP bridge ->
UpdateSession -> Login (the root `Player.Id`) -> GetPlayer -> MissionStart -> MissionEnd (its battle
log's `mission_time` comes back in `MissionEndResult`) -> a refused BoxGacha (ProtocolError 10206,
then the connection closes) -> a reconnect that continues the session -> a corrupted packet -> an
unimplemented API.
`net/cdn-loopback` fetches version.bin, the served master, a manifest and a bundle from a mounted
`cdn::Tree` over loopback.

The CDN's tests (`cdn/...`, library): ADLD round trips; byte-identical re-encryption of the 3.7.0
master and an XOR asset; version.bin decode -> encode identity; the bundle layout against every
3.7.0 Individual and Bulk bundle size; the served master (overrides applied: `service_stop_day` gone,
event terms moved by whole years, 66,945 texts); a synthetic download built into a tree end to end
(bundle SHA-1s, members as the client writes them, version.bin entries, stand-ins, paths, the hash
cache); Login's `AssetPath` / `MasterPath` / `r_ver`. The 3.7.0 ones read `work/download-3.7.0` and
`data/basmaster-3.7.0.sqlite3` from the repo.

`soa --selftest` runs them too, after the port's own tests, with the same seeds and output (they ran
last when the server was `port/src/server`). The server tests that need the game or the port
(`server/client-status`, `server/tutorial-npc-status`, `server/npc-status-master` (the library's
master-data NPC model, `soaserver/npc_status.h`, against the client's own for all 822
`master_mission_npc` rows), `server/event-npc-helper-status`,
`server/event-asset-lookup`, `server/standin-assets`, `server/options`, `server/no-setenv-state`)
are the port's: `port/src/native/api/zz_server_guest_test.cpp`.
