# Plan: run the 3.7.0 client unmodified, against an out-of-process server over TCP

> History: this plan is done (phases 1-5; 6 and 7 were optional), and its 3.8.0 comparisons predate the 3.7.0 rebase; the port no longer uses 3.8.0. Current docs: [emulator/README.md](../../emulator/README.md), [port/PLAN.md](../../port/PLAN.md).

Written 2026-09-30. Status: **in progress.** 2026-10-01: phase 3 (the wire layer) is done in `server/net/` (`soa-server`, see below), phase 4 (the CDN) in `server/src/cdn.cpp`, and phase 1 (the client's network glue) in `emulator/src/net_370.cpp` / `http_370.cpp`: the unmodified client reaches home against `soa-server`. Phase 5 (play-test and compare) is done too (agent `e6-end2end`: a campaign battle, a 10-draw and a new player's tutorial end to end, and server-DB parity with `--restore`; `PLAN-execution.md` step 6). Phases 6 and 7 are optional. The approved execution plan is [`PLAN-execution.md`](PLAN-execution.md). It supersedes this document where they differ: the server becomes its own library used by both `--restore` and `soa-server`, `--no-native` already exists, and the HTTP methods live on `AskaActivity`.

## Goal
Run the **3.7.0 online client** (`work/libSOA-3.7.0.so` + the 3.7.0 APK + `work/download-3.7.0`) under the port's emulator, so that it talks to a **separate server process** over real TCP, using the real wire protocol, like the original game talked to `production-game.so-ana.com:443`.

- **The client:** as close to unmodified as possible. Only the platform layers it was built against change: the Android/JNI/Java pieces and the network address. **No guest code patches**, unless one proves unavoidable; each would be logged in `docs/client-changes.md`.
- **The server:** a standalone binary (`soa-server`). It speaks the GameRPC wire protocol, the SQEX BRIDGE handshake and the CDN's HTTP, and it reuses the game rules already written in `port/src/server/`.

### How this differs from today's `--restore`
| | `--restore` (today) | Emulator mode (this plan) |
|---|---|---|
| Client library | 3.8.0 offline build, plus 3.7.0 bodies grafted in by `restore370` | 3.7.0, as shipped |
| Network | none: `FakeApiCaller` methods hooked natively; arguments read from registers | real `NetworkApiCaller` → GameRPC → TCP, bridge over HTTP(S), downloader over HTTP |
| Server | in-process (`port/src/server`, called from hooks) | out of process: `soa-server`, any host and port |
| Client changes | ~20 logged changes (restore370 groups, `service_stop_day`, gacha routing, …) | none to game code; only the HLE/JNI platform layer |
| Speed | ~60% native | pure JIT at first (phase 6 brings natives back) |

**Why it's worth having:**
- It's the faithful configuration: every client-side behaviour is the original's, so it's a reference for the `--restore` mode.
- The server becomes a real network service. It could be shared between machines, which is the only realistic path to multiplayer (lobby on :4001, battle relay).
- It documents the wire protocol by implementing it; today `docs/online-server.md` is reconstructed from the client.

## How easy is it? Short answer
**Moderate: about 2–3 weeks of agent work, or about a week of wall time with 3–4 agents in parallel. One real unknown is the per-message cipher (step 3.3).** Most of the hard parts already exist:

| Needed | Already in the tree |
|---|---|
| Load and run a different `libSOA.so` | `--lib PATH`; the loader already maps 3.7.0 twice: as the test oracle, and as the restore image |
| Sockets | Guest `socket` / `connect` / `send` / `recv` / `select` / `fcntl` / `getaddrinfo` / `gethostbyname` pass through to the host (`runtime/src/hle/libc_misc.cpp`, `libc_stdio.cpp`). The 3.7.0 lib imports exactly these (select-based, no epoll); no TLS on the game RPC |
| Java side | The C++ JVM emulation (`runtime/src/jni/`), currently covering 3.8.0's classes |
| Request layouts | All 193 request wire layouts were measured on the client's own serializers (`docs/api.md` "Wire format", `tools/api_wire.py --gen-inc`, `native/api/wire_test.cpp`) |
| Packet framing | Documented, with addresses (`docs/online-server.md` §3): 24-byte obfuscated header, SHA-1 trailer, ProtocolError packets |
| Response bodies | ASON encoder (`port/src/server/msgpack.h`); the server already builds every `{data, status}` reply |
| Game rules | `port/src/server/` (194 APIs; rules labelled in `docs/server-rules.md`) |
| Assets and master data | `work/download-3.7.0` (complete), `version.bin` (the manifest; see below), master DB decrypted |

**What's genuinely new:**
1. Make the client boot as 3.7.0 with natives off.
2. Implement the Java bridges 3.7.0 needs: HTTP and X509, among others.
3. Point the client at our server.
4. The server-side wire layer: framing, the bridge handshake, the Ninja/sqex envelope.
5. A CDN.
6. Separate `port/src/server` from the client process.

## Phase 0: boot 3.7.0 as the main image (pure JIT)
**Status (2026-10-01): done** (agent E0; `emulator/README.md` "Status"). `soa-emu` (`emulator/`, on `runtime/`, no natives) boots the unmodified 3.7.0 client from the single APK, unextracted, to its network path. With no server, the title's `NoLoginStart` fails name resolution and the communication-error dialog opens: **error 1003** (disconnect), not 1002, because the in-service title connects before "TAP TO START" is shown. What it took:
- the 25 3.7.0-only `AskaActivity` methods (Play Games, achievements, location, `UnScheduleLocalNotification`);
- `fmod`;
- `GetApplicationVersion` = `3.7.0`;
- a **device clock** set before 2021/06/24 14:30. `CTitle::Setup` compares `master_global.service_stop_day` with the device clock and otherwise shows the service-end title and an "update the app" dialog.

No other Java classes were touched before the network: no `HttpClientBridge` / `X509Bridge` calls yet, and no billing, push or SmartBeat. The download tree wasn't needed.

**Goal:** `soa --emulator` (or `--lib work/libSOA-3.7.0.so --apk-dir <3.7.0 APK>`) reaches the title screen.

0.1 **Natives off.** Natives bind by symbol name (`NATIVE_FUNCTION`). On a 3.7.0 image they would replace 3.7.0 functions with 3.8.0 behaviour.
- Worse, the a2c translations embed 3.8.0 addresses, so they would crash.
- Add `--natives none|identical|all` (default `none` in emulator mode).
- `none` keeps only the HLE imports (libc, GL, …), which are below the game.
- Also skip `restore370`, the FakeApiCaller hooks and the stand-in assets overlay.

0.2 **APK and assets.** Extract the 3.7.0 APK (`apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk`: a single APK, not a split XAPK, with no Play Asset Delivery) into `work/extracted/apk-3.7.0/`.
- Teach the asset layer to use a single APK instead of the base + config splits.
- The 3.7.0 base has only 478 assets; the rest comes from the download (phase 4). Until then, `--download-dir work/download-3.7.0` stands in for the CDN.

0.3 **Java/JNI gaps.** 3.7.0's `classes.dex` differs from 3.8.0's.
- 3.7.0 has, for example, `jb.Aska.HttpClientBridge`, `jb.Aska.X509Bridge`, Firebase, billing, SmartBeat and Lobi; 3.8.0 has playcore instead.
- Run with the JVM's unknown-class/method logging and add each missing class to a new `jni/java_370.cpp`. Return values: the ones a real device without those services would return (no push token, no Play Games, billing unavailable).
- Inventory: grep the dex (`tools/` has dex helpers) for the `jb.Aska.*` classes the lib calls through JNI.

0.4 **Saves.** Use a fresh data dir. KVS layout and encryption are the same in both builds; the 3.7.0 client creates its device UUID itself.

**Done when:** the 3.7.0 title screen shows and tapping it fails with **error 1002** (no server). That proves the network path is reached.

**Risk:**
- Low–medium. The pure-JIT 3.8.0 game used to run before any natives existed, so the core is proven.
- The unknown is how much of 3.7.0's Java surface is touched before the title.

## Phase 1: point the client at our server (no guest patches)
**Status (2026-10-01, agent `e1-emu-net`): done** (as step 5 of `PLAN-execution.md`; the files are in `platform370/src/` since P0 of `docs/history/PLAN-rebase-370.md`). `emulator/src/net_370.cpp` maps `production-game.so-ana.com` (and `--map-host` names) to `--server` and moves port 443 / 4001 (`getaddrinfo` / `gethostbyname` / `connect` overrides, with the Bionic-vs-glibc `ai_flags` and `EAI_*` fixes); `emulator/src/http_370.cpp` is a host HTTP/1.1 client behind the `AskaActivity` HTTP methods (the class the native side calls is the activity, not `HttpClientBridge`; `HttpRequest`'s int is the URI's port, not a method). With `soa-server` the unmodified client goes title → bridge → Login → the 3.1 GB data download from soa-server's CDN → home (`emulator/scripts/emulator_session.sh`, `emulator/README.md` "Networking"). It took two soa-server fixes (Login's follow-up GetPlayerRes, `a_ver`; `docs/server-rules.md`) and URLs without a port (`--bridge-url` / `--cdn-url` on the mapped name).

1.1 **Game server address.** The host is a compiled-in string (`g_info` = `production-game.so-ana.com`, port 443, `ServerSelector::pServerAddress`).
- Redirect it at the HLE layer, not in guest code:
  - `getaddrinfo` / `gethostbyname` map configured names to configured addresses.
  - `connect` rewrites the configured `(host, port)` pairs.
- Options: `--server HOST:PORT` (game, default `127.0.0.1:44300`) and `--lobby HOST:PORT`.
- No guest patch is needed and the protocol is unchanged.
- Alternative: override the string through `IServerSelector::OverrideServer`. That needs a call into guest code, so it's a client change, kept as a fallback.

1.2 **HTTP.** The Aska HTTP client goes through Java (`jb.Aska.HttpClientBridge`: `HttpRequest(url, method, body, flag)`, `GetStatusCode`, `GetHttpHeader`, `ReadHttpResponse`, `AbortHttpRequest`), and the bridge handshake and downloader use it.
- Implement it in C++ in `jni/java_370.cpp` on the host: plain HTTP over sockets; TLS via the host's OpenSSL if linked, else HTTP only.
- The same host/port map applies, so `https://<anything>` can be served by our server over plain HTTP. The URL comes from our server's own StartBridge reply anyway.

1.3 **X509Bridge** (`InitX509` / `AddDERX509` / `EvaluateX509`): accept everything. It's only used for TLS, and only toward our own server.

**Done when:** a TCP connection reaches a test listener with a well-formed StartBridge packet (0x3c bytes on the wire).

## Phase 2: separate the server from the client process
`port/src/server` is called in-process from the FakeApiCaller hooks. Split it:

2.1 **Inputs.** Each API handler receives already-decoded typed arguments.
- Today `server::capture` builds them from the guest registers by mangled signature.
- Phase 3's wire decoder builds the same structs from the packet body.
- Introduce a neutral `server::Request` (fid + decoded args) used by both, so `--restore` keeps working unchanged.

2.2 **Client-side hooks that aren't APIs:**
- `ext::ClientMaster` edits the client's master copy: the event-date shift, banner stand-ins, the tower banners, the text rows.
- `ext::OnResponse` and the stand-in assets.

In emulator mode the server can't touch the client's memory, so these move to **what the server serves** (phase 4: a modified master DB on the CDN). That's what the real service did when it changed data.

2.3 **Assets the server checks at run time** (missions hidden if their map is missing, …). They read the client's asset manager today. Give the server its own view of `work/download-3.7.0` (the manifest plus files).

2.4 **Build:** a `soa-server` CMake target (server sources, sqlite, the new net layer; no JIT, no GL). Same `DATA/server.sqlite3` schema and the same options (`--clock`, `--enable-events`, `--start-coins`, the seed).

**Tests:** the existing `server/` unit tests run against the split library. `--restore` sessions stay green, since they use the same handlers.

## Phase 3: the wire layer in `soa-server`
**Status (2026-10-01, agent `s2-wire`): done.** `server/net/` (`libsoanet`, linked into `soa-server`): packets (3.1), the bridge (3.2: ResultStart, `POST /bridge`, UpdateSession, the `wire_device` table), the Ninja envelope (3.3, moved from `emulator/net/` to `server/net/ninja_*`), the generated decoder (3.4: `tools/api_wire.py --gen-decoder` -> `server/net/gen/wire_decode.inc`), replies and ProtocolErrors (3.5), an HTTP server with a static `/Android/` placeholder, and `--log-packets`. Checked against the client's own serializers and receivers under unicorn (`server/tests/ninja/tools/gen_ninja_vectors.py requests|replies`) and by `soa-server --selftest net/` (incl. a loopback session). Not done: the special replies of 3.6 (maintenance, account suspended) and the version answers. Details: `server/README.md` "soa-server and the wire layer", `docs/online-server.md` §9.

3.1 **Framing** (`docs/online-server.md` §3):
- Read the 24-byte header and undo the obfuscation (keyless: timestamp bytes permuted into 0..7, fields XORed with the timestamp).
- Read size + 20 bytes; verify the SHA-1 trailer.
- Replies: same framing, with the reply FunctionID and the same counter. Errors are `ProtocolError` packets (36 bytes: header, i64 status, u32 fid).
- **Test vectors:** run the client's own `GameProtocoledData::Set*` / `Serialize` in a selftest (the port can call 3.7.0 functions: `t.call370`), and check that our decoder reads them back. Then do the reverse with `Deserialize`.

3.2 **Bridge handshake:**
- StartBridge (clear) → reply `kResultStart(token, url, x)` with `url = http://<server>/bridge`.
- The client POSTs `{"UUID","deviceType","nativeToken"}`. Reply with gzipped JSON `{"nativeSessionId","sharedSecurityKey"}`, where the key is 32 random bytes per session.
- Client sends UpdateSession(nativeSessionId) → reply `kResultUpdateSession`. The connection is now bound to the session and key.
- The device UUID becomes the account key: the server maps the UUID to a player. `LOCAL00001` stays the default seeded player; any new UUID goes through 19001 → terms → CreatePlayer, as before.

3.3 **Ninja / sqex envelope. This is the main unknown.**
- Known: 24-byte header (signature `0xABBAABBA` after un-XORing, version, algorithm id), ciphertext, 32-byte trailer (probably SHA-256 / HMAC). The algorithm comes from the envelope's id, chosen by the sender. The key is `sharedSecurityKey`.
- Unknown: which algorithm and mode the **client** picks when it encrypts; how the IV is made; what the trailer is.
- Approach:
  1. Decompile `Aska::Cryption::Ninja` encrypt/decrypt and `sqex::SqexEncryptionCreator` (3.7.0 = 3.8.0 here).
  2. Generate test vectors by calling the client's own encrypt/decrypt on known keys and plaintexts under the port (a selftest, like `wire_test.cpp`).
  3. Implement in the server with standard primitives (OpenSSL: AES-128, Camellia, Blowfish, …; hand-written for the exotic ones only if the client actually picks them).
  4. The server may reply with any algorithm the client can decrypt, so pick the simplest one the client accepts.
- **Fallback if a cipher can't be matched:** run the client's own sqex code inside `soa-server` through a2c translation. The functions are pure (key, buffer → buffer). That's ugly, but bounded.
- Estimate: 1–3 days of decompilation and testing.

3.4 **Request decoding.** Generate the decoder from the measured wire layouts (`tools/api_wire.py --gen-inc`): positional, packed, little-endian; fixed-width strings; counts before elements. That gives one table for 193 requests, decoded into `server::Request`. Check against `wire_test.cpp`'s captured real request bodies.

3.5 **Replies.** The body is a u32 length followed by the ASON blob the server already builds (Login/SimpleLogin carry a fid first). Encrypt (3.3) and frame (3.1).

3.6 **Special replies:**
- `MaintenanceRes`, `AccountSuspendedRes`: not used by default. Add an option to test the client's dialogs.
- `a_ver` / `r_ver` and the asset revision in the request header: answer with the values matching our CDN (`version.bin` `revision` 1471).

**Tests:**
- Unit: framing, envelope and decode round trips against the client's own code.
- Integration: `emulator_session.sh` (phase 5).

## Phase 4: the CDN (assets and master data over HTTP)
The 3.7.0 client downloads everything after login from `data.AssetPath` / `data.MasterPath` (login response) using the downloader. Today the port serves the files directly with `--download-dir`.

4.1 Serve `work/download-3.7.0` over HTTP from `soa-server`:
- `version.bin`, the asset manifest: 26,268 entries (path → SHA-1 "md5", size, encType, episode). The client compares it with what it has and fetches what's missing.
- The per-episode manifests, the assets (`<base>/Android/<file>`) and the master DB (`/download` → `master/`).
- Login returns the base URLs, pointing at `soa-server`'s HTTP port.

4.2 **Master data changes** (the replacement for `ext::ClientMaster`, phase 2.2): the server builds a modified master DB at startup or on change.
- Contents: date-shifted event tables, stand-in banner rows, tower banners, the text rows.
- It then re-encrypts the DB (encType 2; the decryption is in notes.md "the master database", so the reverse can be written and tested against the client's own decrypt).
- It updates `version.bin` with the new hash and size, and bumps `revision`.
- The client then downloads it like a real data update. This is exactly how the live service shipped data changes.

4.3 **Stand-in assets** (the Summer '17 banners, …): add them to the served tree and manifest the same way, instead of the client-side overlay.

4.4 **Option:** `--cdn none` lets the client use a pre-populated data dir (copy the download into its cache) for fast tests.

## Phase 5: play-test and compare
- **`emulator/emulator_session.sh`:** start `soa-server`; start `soa --emulator --server 127.0.0.1:44300`; then run, with `flowctl.py`, through title → bridge → login (seeded player) → home → one campaign battle → 10-draw gacha → back home. PASS lines as in the other sessions. Plus a fresh-player run: 19001 → terms → name entry → tutorial battle.
- **Parity with `--restore`:** run the same scripted session both ways and compare the server databases (`tools/server_state.py`). Any difference is a gap in one of the two modes; record it in `docs/client-changes.md` / `server-rules.md`.
- **Packet log:** `soa-server --log-packets DIR` writes the decoded requests and replies. That's the protocol documentation, measured.
- **Status (2026-10-01, agent `e6-end2end`): done**, with `soa-emu` and `emulator/scripts/emulator_session.sh [--new-player]`; parity in `emulator/README.md` "Parity" (the same state apart from documented differences); the confirmed facts in `docs/online-server.md`.

## Phase 6 (optional): speed, by bringing natives back to 3.7.0
Pure JIT will be noticeably slower than today's port (roughly the speed before the native work; battles playable, loading slower).
- **Readable, symbol-keyed natives** can be enabled for the functions whose bodies are identical in both builds (99.6% of bodies are identical after normalisation; `docs/history/libsoa-3.7.0-vs-3.8.0.md`, `tools/verdiff.py`).
  - `--natives identical` = allowlist from verdiff's identical set ∩ natives that don't hard-code 3.8.0 addresses.
  - Data and vtable addresses must be resolved by symbol, which most readable natives do through `sym()` lookups. Audit the rest.
- **The a2c translations** embed 3.8.0 addresses, so they would have to be regenerated against the 3.7.0 lib (the generators take the lib path) or rewritten readable (Track C). The readable rewrites are the ones that carry over.
- **Live check:** run the shared live-check library on the 3.7.0 image with a 3.7.0 oracle. The guest is the reference, so the same mechanism works unchanged.

## Phase 7 (optional): multiplayer
With a real server on the network, the lobby (`MultiplayRPC::LobbyProtocol`, TCP :4001) and the battle relay (`MO::BattleProtocol`, host:port per room) become implementable. Two clients on two machines could co-op through one `soa-server`. That's a separate plan; the protocols are only named in `docs/online-server.md` so far.

## Client changes this plan would make
| Change | Layer | Why |
|---|---|---|
| Host/port redirect in `getaddrinfo` / `gethostbyname` / `connect` | HLE (platform) | the original server is gone |
| `HttpClientBridge`, `X509Bridge`, and other `jb.Aska.*` / Android classes 3.7.0 calls | JVM emulation (platform) | the port has no Java |
| Billing, push, Play Games, SmartBeat, Lobi: "unavailable" answers | JVM emulation | services gone |
| (fallback only) `IServerSelector::OverrideServer` call | guest call | only if the HLE redirect isn't enough |

No game-logic change is planned; anything that turns out necessary goes into `docs/client-changes.md` with evidence.

## Work breakdown (for agents)
| # | Work | Depends on | Size |
|---|---|---|---|
| E0 | Boot 3.7.0 pure-JIT: `--natives none`, single-APK assets, 3.7.0 Java classes up to the title | none | 2–3 days |
| E1 | HLE host redirect, `HttpClientBridge`, `X509Bridge` | E0 | 1 day |
| E2 | Split the server: `server::Request`, `soa-server` target, own asset view; `--restore` unchanged | none (parallel to E0) | 2–4 days |
| E3 | Wire framing + bridge handshake + request decoder from the wire tables + replies | E2 | 2 days |
| E4 | Ninja/sqex envelope: decompile, client-generated test vectors, server implementation | none (research can start at once) | 1–3 days |
| E5 | CDN: serve download tree, regenerate master DB (re-encrypt) + `version.bin`, stand-ins | E2 | 2 days |
| E6 | `emulator_session.sh`, fresh-player run, parity with `--restore`, packet log | E1, E3, E4, E5 | 2–3 days |
| E7 | (optional) natives on 3.7.0: identical-body allowlist, live check against the 3.7.0 guest | E0 | 1–2 weeks |

**Critical path:** E2 → E3 → E6, with E4 in parallel. The first end-to-end login is about a week out with 3–4 agents.

## Risks
1. **The cipher (E4).** If the client's chosen algorithm or trailer can't be matched, the fallback is running the client's own sqex code in the server. Bounded, but not pretty.
2. **The 3.7.0 Java surface (E0).** Unknown until it runs; usually a long tail of small stubs.
3. **Natives off = slow.** Acceptable for a reference mode; E7 fixes it gradually.
4. **The master-DB re-encryption (E5).** If it can't be reproduced, the CDN serves the original master and the date shift has to come from the server clock instead (send `data.Time` in the 2017–2021 range, which makes the events current without changing the master). This alternative is simpler and may be preferable anyway; decide in E5.
5. **The downloader's behaviour** (resume, hash checks, retries) is only known from the decompile; test it with a large download and a forced failure.
6. **Server-rule parity.** Rules written against the 3.8.0 client plus hooks (e.g. answers given by hooking a client function, not by an API) need a wire-level equivalent. The parity run (E6) finds them.

## Where things would live
- `emulator/`: this plan, `emulator_session.sh`, notes as they come up.
- `server/net/`: framing, envelope, decoder and HTTP for `soa-server` (done; was planned as `port/src/server/net/`).
- `port/src/jni/java_370.cpp`: the 3.7.0 Java classes.
- `port/src/hle/`: the host redirect.
- **Docs:** `docs/online-server.md` gets the measured protocol (confirmed instead of inferred), and `docs/client-changes.md` gets an "Emulator mode" section.
