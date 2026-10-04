# How the online game server worked

STAR OCEAN: anamnesis (JP) talked to Square Enix / tri-Ace servers until the service closed in June 2021. No traffic was ever captured, so this document rebuilds the online side from the client:
- `work/libSOA-3.7.0.so`: the last online build;
- the offline build's `libSOA.so` (the viewer's, `emulator-viewer/`);
- the 3.7.0 APK's Java side (`classes.dex`, `AndroidManifest.xml`);
- the 3.7.0 download set (`work/download-3.7.0`);
- the master DB (`data/basmaster-3.7.0.sqlite3`).

Written 2026-09-29 by agent `api-server-doc`.

It covers the parts of the server that the existing docs don't: transport, wire format, session and security. For the other parts it links to them:
- [`docs/api.md`](api.md): the 194 APIs, with their arguments, response keys, FunctionIDs, response basics and player-state lifetimes. Its [Wire format](api.md#wire-format) section is the byte-level companion of section 3 below: the request encoding measured on all 193 serializers, reply framing, ASON, annotated examples; each API entry has a generated **Wire** line (request layout + reply FunctionID).
- [`docs/ason.md`](ason.md): ASON, the engine's MessagePack used by reply bodies and request payloads (battle log, deco): encoding, object model, key hashing, id-keyed maps, the request-side serializer.
- [`docs/notes.md`](notes.md): "Offline server (FakeApiCaller)", "API response handling (CApiNotify)"; the offline build's changes: [`docs/history/notes-3.8.0.md`](history/notes-3.8.0.md).
- [`docs/server-rules.md`](server-rules.md): the game rules that **our** local server applies.

This document is about the **real** server. Section 9 maps each piece onto our emulator.

**Confidence labels** on every claim:
- **[confirmed]**: read from decompiled or disassembled code, strings or data. It hasn't been run against a live server.
- **[inferred]**: follows from names, call structure or data, but the code wasn't followed all the way.
- **[unknown]**: not recoverable from the client.

**Addresses** are Ghidra addresses in the **3.7.0** lib (ELF vaddr + 0x100000), unless marked as the offline build's. The decompiles are in `work/decomp/api-server-doc-*.resolved.c`: `net1`, `net2`, `proto`, `bridge`, `ninja`, `dl`, `login`, `misc` and `mp`. Rebuild them with `tools/decomp.sh --v370`.

## Overview

```
                          ┌──────────────────────── game client (libSOA.so) ───────────────────────┐
 screens / CPhase_* ──►  IApiCaller (TSingleton<CApiCaller>)                                        │
   poll IsRequesting /     = NetworkApiCaller  (FakeApiCaller, NoApiCaller: dev/unused stubs)       │
   IsSuccess / ErrorCode     │ SetRetry(fid, closure) → BeginBridge(cb) → PresendApiCall(fid)       │
                             ▼                                                                      │
                  GameRPC::Cli::GameProtocolProxy::Send<Api>(RequestHeader, args…)                  │
                  GameProtocoledData::Set<Api>  (positional binary, body encrypted by the           │
                             │                    Ninja / sqex cipher with the bridge session key)  │
                             ▼                                                                      │
                  TARPCPeer → TPeer<TCP, GameProtocol>  ── network thread (NetworkManager) ──┐      │
                             ▲                                                               │      │
   CApiNotify::On<Api>Res ◄──┘ DispatchNotify → GameProtocolNotifyMT (main-thread queue)     │      │
   ASON (msgpack) → CParameterManager::Deserialize → data.* infos                            │      │
└────────────────────────────────────────────────────────────────────────────────────────────┼──────┘
                                                                                             │
  raw TCP, port 443 (no TLS)  ◄──────────────────────────────────────────────────────────────┘
  production-game.so-ana.com          "game server": all 194 APIs + StartBridge / UpdateSession
        │ StartBridge result gives a bridge URL + token
        ▼
  HTTPS POST {"UUID","deviceType","nativeToken"} (Java HttpURLConnection) → "SQEX BRIDGE" endpoint
        ◄── gzip JSON {"nativeSessionId","sharedSecurityKey"} → key into the cipher, UpdateSession

  TCP :4001 on the lobby host (by default the same host)   MultiplayRPC::LobbyProtocol (rooms, automatch)
  TCP host:port handed out per room                         MO::BattleProtocol (co-op battle relay)
  HTTP(S) CDN at data.AssetPath / MasterPath (from login)   Downloader: version.bin, manifests, assets, master DB
  http://production-cache.webview.so-ana.com/…              notices / banners in WebViews (URLs in master_banner)
  Google Play Billing / Amazon IAP → receipts → CoinDeposit*Update (server-side receipt check)
  Firebase Cloud Messaging (push), Google Play Games, SmartBeat (crash logs), Lobi (community)
```

## 1. Architecture

### API callers
There are three implementations of the `IApiCaller` interface. **[confirmed]**
- **`NetworkApiCaller`**: the only one the game constructs. `CGame::OnInitialize` news it and swaps in `CApiCaller`'s vtable (notes: "Offline server (FakeApiCaller)").
  - The constructor @015b7684 embeds a `TARPCPeer<GameProtocolProxy>` (`TPeer<TCP, …>` at +0x30), a `CApiNotify` at +0x7b0 and a `CNetworkUtility`.
- **`FakeApiCaller`**: a developer stub that serves canned `FakeApi/*.msgp` files. Nothing constructs it (notes).
- **`NoApiCaller`**: every method is an empty stub. `NoApiCaller::NoApiCaller()` has no callers and no address references in either build (`tools/callers.py`, `tools/xref_got.py`). It's probably a headless or test build's caller. **[confirmed / inferred]**

### Layers
**[confirmed]** from the template instantiations in the dynamic symbol table:

| Layer | Class | Role |
|---|---|---|
| Game API | `NetworkApiCaller::<Api>` | Registers a retry closure (`CErrorHandlerWrap::SetRetry(fid, fn)`), checks `LoggedIn` and runs `BeginBridge(lambda)`. The lambda calls `PresendApiCall(fid)`, then `GameProtocolProxy::Send<Api>`. |
| RPC proxy | `Aska::Yayoi::GameRPC::Cli::GameProtocolProxy` | `Send<Api>(RequestHeader const&, args…)`, `DispatchNotify`, `DelegateMainThread`. |
| Serialisation | `Aska::Yayoi::GameRPC::GameProtocoledData` | `Set<Api>` / `Get<Api>` / `Set<Api>Res` / `Get<Api>Res`. 786 exported functions, each taking an `Aska::Cryption::Ninja*`. |
| Protocol | `Aska::Yayoi::GameRPC::GameProtocol` | `Serialize` / `Deserialize`, `CheckRecast`, `CheckTime`, `GetFunctionName`. |
| Peer | `Aska::Yayoi::TARPCPeer<GameProtocolProxy>` over `TPeer<TCP, TProtocolSuite<GameProtocol, NoProtocol<1>, NoProtocol<2>>, true>` | Send queue (`TPriorityQueue<SendingContext>`), connect, `UpdateDNS`, keep-alive. |
| Sockets / threads | `Aska::Yayoi::NetworkManager`, `NetworkManagerThread`, `NetworkEvent` (`RequestConnect` / `RequestPoll`), `Socket`, `TCP` | Non-blocking sockets polled on a network thread. |

- The same stack is instantiated twice more: for `MultiplayRPC::LobbyProtocol` (lobby) and for `MO::BattleProtocol` (co-op battle).
- A fourth suite, `TProtocolSuite<HttpProtocol, SSLProtocol, NoProtocol<2>>`, serves HTTP(S). It's used for the bridge handshake and the downloader.

### A call, end to end
Using `MissionEnd` @015ba170 as the example. **[confirmed]** unless marked.
1. **Retry closure and login check.** `SetRetry(0x8312a64c, closure)` stores a closure that re-issues the call. Then `LoggedIn()` (vtable +0x6a0) is checked. If it's false, `DisconnectDialog(-0x3b3, fid)` shows and the call stops.
2. **`BeginBridge(lambda)`** @015b964c (vtable +0x38).
   - **Already bridged** (+0xc80 set): 3.7.0 copies the player id into the caller and runs the lambda at once.
   - **Otherwise:**
     1. It stores the lambda.
     2. It enables TCP keep-alive: 30 s idle, 2 s interval, 5 probes (`Socket::SetKeepAlive(1, 30, 2, 5)`).
     3. It reads the device UUID (`BAS::GetUUID`) and records it with `CApiNotify::SetBridgeSessionUUID`.
     4. It sends `StartBridge` (fid `d4053e85`, header only).
     5. The lambda runs later, once the session exists (section 4).
   - The offline build dropped the "already bridged" shortcut (docs/history/notes-3.8.0.md).
3. **`PresendApiCall(fid, …)`** @015b7e48 builds the `RequestHeader`, 16 bytes at `NetworkApiCaller+0xdbc`:
   - `+0`: the player id (`CParameterPlayer` +0x38, the `Player.Id` the server issued);
   - `+4`: the `Token` of the same parameter set (+0x68). `CParameterPlayerElement::Initialize` @017f81b8 names the set's fields: `Id` (+0x38), `Token` (+0x68), `Level`, `Role`, `PersonID`, `Weapon`, `Name`; the LoginResult's top-level `Player` map fills them (section 4, Login). What the real server put in `Token` is **[unknown]** (soa-server sends none: -1). **[confirmed: the field]**
   - `+8`: a **request id** = `CHash32(sprintf("%u_%u_%llu_%u", player id, fid, time(), …))`. It's kept for a retry (flag +0xdcc), so a retried request carries the same id. The server could use it to de-duplicate retries. **[confirmed code; purpose inferred]**
   - `+0xe`: the client's **asset revision** as a u16. It's `CGameResourceDownloader::GetLocalAssetevision()` parsed as a number: `revision` in `version.bin`, e.g. 1471.
   - It also calls `TARPCPeer::UpdateDNS`, reports the player id to SmartBeat (`_SmartBeat::SetUserID`), and starts the **60-second API watchdog** (`CAPIWatcher::StartCheckTimeout(60000)`).
   - **Only one request can be in flight.** A second one asserts "This Function is requesting. fid:0x%X %s" (`CApiNotify::InitErrorCode` @014be860 refuses while +0x518 is set).
4. **`GameProtocolProxy::SendMissionEnd`**:
   1. `GameProtocoledData::SetMissionEnd` @0153d840 lays out the body: header, mission id, the ASON battle log (length + bytes), the u32. It encrypts it (section 3) and writes the packet header with flag byte `0x80`.
   2. `TProtocolSuite::CreateBuffer(len + 0x14)` reserves room for the SHA-1 trailer.
   3. `TARPCPeer::RPCSend` @01247f80 queues it (`TPriorityQueue::Put`). It connects if needed (`TCP::Create`, `NetworkEvent::RequestConnect`) and sends on the network thread.
5. **Receive.**
   1. `TARPCPeer::OnReceive` @01244110 calls `GameProtocolProxy::DispatchNotify` on the network thread. It decodes the packet and picks the `IGameProtocolNotify` (= `CApiNotify`) callback.
   2. Status `-0x3c7` means "must run on the main thread". `DelegateMainThread` then queues it on `GameProtocolNotifyMT` (a `TImportanceQueue<NotifyInfo, 1950>` run as a main-thread task).
6. **`CApiNotify::On<Api>Res(s8* data, u32& size)`** parses the decrypted body as ASON (the engine's MessagePack) and applies it through `CParameterManager::Deserialize`. Details in notes "API response handling (CApiNotify)" and api.md "Request and response basics".
7. **`EndRequest`** clears the in-flight slot (fid +0xcc0, `7b1a9377` = none; error +0xcc4; busy +0xcc8). The screen sees `IsRequesting` go false and `IsSuccess` / `ErrorCode` (@015d49f4, @015d4a60) report the outcome.

**Timeouts.** `CAPIWatcher::Run` @01592564 fires `OnError(-0x3c6, "System timeout.")` when a request is older than the limit set by `StartCheckTimeout` (60 000 ms from `PresendApiCall`). **[confirmed]**

**Throttling.** `GameProtocol::CheckRecast(fid, seconds)` @0150fadc keeps a last-sent time per fid. Only `Debug_OpenMission` (`717cc46f`) is actually rate-limited. `CheckTime` is a stub returning 0. **[confirmed]**

## 2. Transport

### Hosts, ports and URLs

| What | Value | Evidence | Confidence |
|---|---|---|---|
| Environment name | `[sqex]production`, the only one compiled in | `g_info` (3.7.0 vaddr 0x2bc6920, 24 bytes) = {0, "[sqex]production", "production-game.so-ana.com"}; the same strings are in the offline build | confirmed |
| Game server host | `production-game.so-ana.com` | `ServerSelector::pServerAddress` @015fa1b8 returns an override string, else `g_info+0x10` | confirmed |
| Game server port | **443, raw TCP without TLS** | `Login` @015b87e8 and `NoLoginStart` @015cc0b4 call `URI::Deserialize(host, 0x1bb, …)`. The GameRPC peer is `TPeer<TCP, TProtocolSuite<GameProtocol, NoProtocol, NoProtocol>>`, with no `SSLProtocol` layer (the HTTP suite has one) | confirmed |
| Lobby host / port | `ServerSelector::pServerAddressLobby()` (lobby override, else the game host), port **4001** | `CMultiPlay3::Server_InitializeCommon` @01d07f4c → `CMultiplayManager::Initialize(host, 0xfa1, notify)` → `InitMatchingClient` @015a3c34 (TCP, keep-alive 1/5/6) | confirmed |
| Battle relay | host:port per room | `CMultiplayManager::InitBattleRPCClient(host, port)` @015a7568 is called from the room-info callbacks (`std::function<void(RoomInfo&)>`), so the lobby hands out the address (keep-alive 20/2/3) | inferred |
| Overrides | `IServerSelector::OverrideServer` / `SetLobbyServer` | Only caller: code near `CPhase_Server::ToClose` (a server-select phase). The response also carries `LobbyPath`, `LobbyProxyPath/Port` and `BattleProxyPath/Port` (`port/fakeapi/schema.txt`); their readers weren't traced | inferred |
| Bridge endpoint | URL from the game server's StartBridge reply, port 443 | `CApiNotify::OnResultStart(token, url, x)` @014beb60 → `THttpClient<TCP,5>::CreateRequest(url, 0x1bb)`. With a default port given, `URI::Deserialize` keeps a URL's `:port` in the host it resolves (soa-emu saw `getaddrinfo("127.0.0.1:44380")`), so the service's URLs had no port | confirmed (the URL itself: unknown) |
| Asset / master CDN | `data.AssetPath` + `data.r_ver` (Login): every URL is `<AssetPath>/<r_ver>/Android/<name>`; `data.MasterPath` has no reader found | `CInfoManager::GetDownloadURL` @01614ab0 (`"%s/%s/"` of AssetPath and r_ver) → `SetDownloadDataServer`; `CDownloadNode::StartDownload` @018df0b4 adds `"Android/"` + the node name (its `download/` → `master/` swap is never enabled in 3.7.0) | confirmed (3.7.0 decompile; section 6) |
| Episode packs | `data.LatestEpisodeVersion` (Login; u32, the number of episode packs: 3 = `master_global.latest_episode_version`) | `CInfoManager::Initialize` @015135b4 registers it at CInfoManager+0xb0f0 = CParameterManager+0xb6f0, the episode count of `tEpisodeData::GetEpisodeMax`, `IsEpisodeDataStatusDownload` and `CGameResourceDownloader::UpdateEpisodeDataMaxSize` (+0x278: `Progress_Setup`'s loop over `version_latest_ep%d.version` / `.bin`). With 0 no pack is listed or fetched | confirmed (3.7.0 decompile; run: the port and soa-emu download EP2 / EP3) |
| WebViews (notices, banners) | `http://production-cache.webview.so-ana.com/information/detail/<id>.html` | 1,721 `master_banner.url` and 52 `master_banner_replace.url` rows. Response infos `WebView`, `CommonWebView` and `CInformationSiteInfo` carry more | confirmed (data) |
| Other sites | `sqex-bridge.jp` (recommended games), `cache.sqex-bridge.jp/guest/information/75414` (refund notice), `support.jp.square-enix.com` (refund form), store URLs | `master_global` keys `title_button_osusume_game`, `pay_back_*`, `store_url_*` | confirmed (data) |
| Community | `https://web.lobi.co/game/soa/`, `lobi://game_community?gameId=soa` | lib strings, `BAS::LaunchLobi` | confirmed |

### HTTP(S)
- **The Aska HTTP client is a front end over Java.** **[confirmed]**
  1. `THttpClient<TCP,5>::InvokeRequests` → `NetworkEvent::AddHttpRequest` → `NativeHttpRequestProcessor::AddRequest`.
  2. `NativeHttpClient::_doRequest` @026a4f40 calls the Java bridge `jb.Aska.HttpClientBridge` over JNI: `SetHttpUserAgent(String)`, `HttpRequest(String url, int method, String body, boolean)`, `GetHttpHeader()`, `GetStatusCode()`, `ReadHttpResponse(byte[])`, `AbortHttpRequest()`.
  3. The dex shows `java.net.HttpURLConnection`, `setConnectTimeout` and `setReadTimeout`.
- **TLS and certificate pinning.** TLS is Android's own, through `HttpURLConnection`. **[inferred]**
  - The native side also has a complete TLS implementation (`Aska::Yayoi::SSLProtocol::SSLConnection`, `RecordLayer`, `Aska::Encode::X509`).
  - A Java helper `jb.Aska.X509Bridge` (`InitX509`, `AddDERX509`, `EvaluateX509`, `TrustManagerFactory`, `checkServerTrusted`) validates certificates against the system trust store.
  - No pinned certificate, public-key hash or pin list was found in the lib, the dex or the master data. **[inferred: no pinning]**
- **Headers.** `HttpProtocol::MakeHeader` @023068a4 writes `Host:`, `User-Agent:`, `Content-Length:`, `Content-Type:` and cookies (`CookieManager`). `HttpProtocol::SetUserAgent` @023067c8 stores it. **The user-agent string itself: [unknown]**. It's set at runtime, and no UA literal was found.
- **Compression.** `HttpProtocoledData::ParseContentEncoding` @02309ec0 recognises `gzip`. The bridge reply is gunzipped explicitly (`AskaUncompressGzipStrict` in `BridgeNotify::OnReceive` @014eec24). **[confirmed]**
- **Timeout values** for the Java connection: **[unknown]**. They're in `HttpClientBridge`, which wasn't disassembled.

### Maintenance and version checks
- **Special replies.** Beside the normal `<Api>Res`, the protocol has three replies the server can send in place of one. They're unencrypted, and each has its own handler. **[confirmed]** Which requests could get them is **[inferred]**: any.
  - `kMaintenanceRes` → `CApiNotify::OnMaintenanceRes(u32 mode, blob)`;
  - `kPartialMaintenanceRes` → `OnPartialMaintenanceRes(u32, blob)`;
  - `kAccountSuspendedRes` → `OnAccountSuspendedRes(u8, blob)`, which shows `uimsg_account_ban` 「不正行為を確認したため、アカウントのご利用を停止しております。」 (account suspended for cheating).
- **Responses carry the maintenance state.** **[confirmed schema; semantics inferred]**
  - Global: `MainteMode` (u32), `MainteAnnounce`, `MaintenanceMessage`.
  - Per feature: `PartialMaintenance`, `GachaMaintenanceInfoMap`, `EventMaintenanceInfoMap`, `ExchangeMaintenanceInfoMap`, `WorldMapMaintenanceInfoMap`.
  - Also the server build: `ServerBuildInfo` {`BuildNumber`, `BuildScmRevision`, `BuildScmURL`}.
  - `CGacha::GetMaintenanceType(fid)` @01ab8fc0 maps gacha fids to maintenance categories.
- **Version checks.**
  - The client sends its asset revision in every request header (section 1).
  - Master data holds the expected app versions: `master_global.a_ver_android` / `a_ver_ios` / `a_ver_amazon` = `3.7.0`.
  - Responses carry `a_ver` / `r_ver`.
  - `CErrorHandlerWrap::OpenDialogAppVer` and `OpenDialogResVer` are the two outcomes: "a new app version, update from the store" (`error_message_text_10000000`) and "updated data, back to title" (`10000001`, also `1013`). **[confirmed dialogs; which code triggers which: inferred]**
- **Maintenance errors.** `1004` ただいまメンテナンス中です, `1012` (event maintenance, back to title). **[confirmed texts]**

## 3. Wire format (game RPC)

### Packets on the TCP stream
**[confirmed]** from `_write_header` @0151015c, `SetStartBridge` @01531f30, `SetProtocolError` @0150ff78, `SetMissionEnd` @0153d840 and `GameProtocol::Serialize` @0150d248.

```
+0   24-byte packet header (obfuscated, see below)
       logical fields: u32 size (24 + body, without the SHA-1) | u32 FunctionID | u32 counter | u8 flags | 3 zero bytes
       flags 0x80 = body encrypted (every Set* with a Ninja* sets it; the clear ones send 0)
+24  body: RequestHeader (16 bytes) + the API's positional arguments, or the response blob
     … encrypted as a whole when flags & 0x80 (sqex envelope, below)
end  20-byte SHA-1 of everything before it (GameProtocol::Serialize appends it: *out_len = len + 0x14)
```

- **Framing.** Length-prefixed: the first logical u32 is the packet size **without** the 20-byte SHA-1 trailer; the receiver reads size + 20 bytes (`GameProtocoledData::Deserialize`, offline build @01513d20). For example, StartBridge is `0x28` = 24 header + 16 RequestHeader, 0x3c bytes on the wire. **[confirmed, run in the `wire/` selftest]**
- **Counter.** The third logical u32 is copied from GameProtocoledData+0x34, which the peer fills; who sets it and whether the server checks it wasn't traced. **[unknown]** (soa-server echoes the request's counter in its reply.)
- **FunctionID placement.** The FunctionID is the second logical u32.
  - Every request has its own FunctionID; so does each reply.
  - The names come in pairs in the RPC name table: `kLogin` / `kLoginResult`, `kCreatePlayer` / `kCreatePlayerRes`, `kStartBridge` / `kResultStart`, `kUpdateSession` / `kResultUpdateSession`, …, with `kInvalid` and `kError` first. 455 names in all (strings in the lib).
  - The client's IDs for the requests are in api.md.
- **Header obfuscation.**
  1. The client reads `clock_gettime(CLOCK_MONOTONIC)` in nanoseconds.
  2. The 16 field bytes are XORed byte-wise with the 8 timestamp bytes.
  3. They're moved to header bytes 8..23.
  4. Bytes 0..7 carry the timestamp itself, byte-permuted (timestamp bytes 6, 4, 3, 0, 7, 1, 2, 5).
  - It's a keyless scramble: anyone can undo it. **[confirmed, run]**: the client's `Deserialize` accepts packets soa-server scrambles this way, and soa-server reads the client's (section 9).
- **Integrity.** A plain **SHA-1** over the whole packet is appended (`Aska::Hash::SHA1`, not HMAC). It detects corruption, not forgery. The receiver **does check it**: `GameProtocoledData::Deserialize` hashes the first size bytes and fails the packet with -0x3b8 on a mismatch, as it does for an unknown FunctionID. **[confirmed: code, and run in the `wire/reply-roundtrip` selftest with a corrupted trailer]**
- **Argument serialisation.**
  - Positional and typed, with no key names.
  - Packed, no alignment padding, little-endian: u8/s8 1 byte, u32/int/float/DeviceType 4, u64 8. A (pointer, count) pair goes as u32 count + elements (count first). A string with a length argument goes as u32 length + bytes.
  - A string **without** a length argument is a **fixed-width field** (`memcpy` of N bytes, not zero-padded): 36 for the Login/CreatePlayer UUID, 33 for gacha hashes, 191 for names, 16 in NoLoginStart, ….
  - Example: `GetLogin` @0151034c parses Login as RequestHeader(16) + 36-byte string + u32 len + bytes + u32 len + bytes + u8.
  - Some serializers range-check arguments and refuse (-0x3bd) before sending: empty strings, DeviceType > 99, mission type ≥ 4, party index ≥ 7, some counts.
  - All 193 request layouts were measured on the client's serializers (identical in 3.7.0 and the offline build) and are in api.md "[Wire format](api.md#wire-format)" and each entry's **Wire** line. **[confirmed, run]**
- **Response body.** After decryption it's a u32 length + an **ASON (MessagePack) blob** (ASON, the engine's MessagePack: [ason.md](ason.md)). Login and SimpleLogin results carry a FunctionID first (`GetLoginResult` @01510544: fid, length, bytes).
  - The blob is the `{"data": {…}, "status": n}` map (plus top-level parameter sets) described in api.md "Request and response basics".
  - `CApiNotify::OnLoginResult` @014be668 feeds it to `ASON::DeserializeBinary` → `CParameterManager::Deserialize`. **[confirmed]**
- **Pushes.** The lobby and battle protocols have server-initiated messages (`kStampPush`, `kMissionStartPush`, `kMissionEndPush`, `kExitRoomPush`, `kRSSIPush`, `kDisconnectNodePush`, `kForceWinBattleStagePush`). The game RPC has none; it's request/response only. **[confirmed names; inferred for game RPC]**

### Encryption ("Ninja")
**[confirmed, run]** The format below is implemented in [`server/net/ninja/ninja_ref.h`](../server/net/ninja/ninja_ref.h) (pure C++ + OpenSSL libcrypto) and checked against the client's own ARM64 code. `server/tests/ninja/tools/ninja_client.py` runs that code under unicorn; `gen_ninja_vectors.py` and `soa-server --selftest net/ninja-vectors` (or `server/tests/ninja/ninja_check.sh`) hold the checks. Results, identical on the offline and the 3.7.0 libs:
- **Client to reference:** 700/700 client envelopes reproduced byte-for-byte and decrypted. They cover all ten algorithms, both IV generators, 7 parameter values, 2 keys and lengths 1..1000.
- **Reference to client:** 160/160 reference envelopes decrypted by the client. The client refused every tampered byte and a wrong key.
- **Whole packets:**
  - 40 client `SetSetTitle` requests were decrypted by the reference.
  - Reference-encrypted `GachaRes` replies in all ten algorithms were accepted by the client's `Deserialize` + `GetGachaRes`.
  - Without flag 0x80 the same replies were refused with -0x3eb.

Addresses in this subsection are Ghidra addresses (ELF vaddr + 0x100000) in the offline build's lib, where it was first read. The code is identical in 3.7.0, but the sqex block sits 0x24dc higher there (`sqex::IsValidSignature` is @0123be20 in the offline build and @0123e2fc in 3.7.0).

- **Objects.**
  - `Aska::Cryption::Ninja` lives at `TPeer<…GameProtocol…>+0x20` (TPeer ctor @015db738). Its parts:

    | Offset | What |
    |---|---|
    | +0 | `KeyStore` (32 bytes + terminator) |
    | +0x28 | `AllocatorForNinja` (`new[]` / `delete[]`) |
    | +0x30 | The message generator: Yarrow-like, with SHA-256 pools and an AES counter generator. It is seeded with `time() ^ thread id`, and every draw adds `time()` entropy (@0123b8a0). |
    | +0x428 | `sqex::SqexEncryptionCreator` |

  - Every encrypted `Set<Api>` / `Set<Api>Res` calls the helper @0153928c (`ninja, plain, len, out, cap`):
    1. It draws r1 and r2 from the message generator.
    2. It creates the algorithm `table@027e3164[r1 % 96]` with parameter r2 (@0123c314).
    3. It encrypts.
  - Every `Get<Api>` / `Get<Api>Res` creates the algorithm named in the envelope (@0123c6b4) and decrypts (@0123c0f4).
- **Key.**
  - The bridge's `sharedSecurityKey` is a JSON **string**. `BridgeNotify::OnReceive` passes its raw characters to `SetSharedSecurityKey` (vtable +0x6c8) = `KeyStore::Set` @01226e30, which copies **exactly 32 bytes** and a terminator.
  - `KeyStore::Get` @01226e20 returns null when byte 0 is 0. Encrypted calls then fail with `-0x3b3`.
  - So the server must issue a string of at least 32 printable characters. Its first 32 bytes are the session key K.
  - The block ciphers use K[0..16), except Blowfish, which uses all 32 bytes. The trailer uses all 32.
- **Algorithms.**
  - The client picks one at random for **every message**, and all ten occur. The weights below are entries in the 96-slot table.
  - In 200 messages run through the helper, all ten appeared.
  - The server must therefore decrypt all ten. It may reply with any of them; `ninja_ref` uses AES-128 as the simplest.

  | id | algorithm | block | weight /96 | Notes (vs. the standard cipher) |
  |---|---|---|---|---|
  | `0x01e6ac1b` | SEED | 16 | 14 | **The key schedule differs:** the key words are read little-endian, and odd round keys use G(K1 **+** K3 + KC). |
  | `0x021d4314` | AES-128 | 16 | 12 | Standard |
  | `0x03478caf` | Blowfish (256-bit key) | 8 | 7 | The key is read as little-endian words (each 4-byte group reversed vs. standard) |
  | `0x048a4dfe` | CAST-128 | 8 | 2 | Standard block. **The chaining state is the previous ciphertext with its two words swapped.** |
  | `0x052e3a67` | Camellia-128 | 16 | 7 | Standard (OpenSSL's own code inside the lib) |
  | `0x07fedca9` | Serpent-128 | 16 | 4 | Standard (NESSIE byte order) |
  | `0x08a723ab` | Twofish-128 | 16 | 14 | **Not standard:** the MDS column-2 table is built wrongly (@01235ee8), so the ciphertext differs from the spec |
  | `0x0951fad3` | IDEA | 8 | 9 | Standard |
  | `0x0a325482` | MARS | 16 | 17 | **The key schedule is the original 1998 MARS**, not the tweaked final one, and it has a few literal quirks (`ninja_mars.cpp`) |
  | `0x0b46b571` | MISTY1 | 8 | 10 | Standard |

  - OpenSSL 3 provides AES, Camellia, Blowfish, CAST5 and SEED. `ninja_ref` uses its block functions; for SEED it computes its own key schedule.
  - IDEA (Ubuntu builds OpenSSL without it), MARS, MISTY1, Serpent and Twofish are written out in `server/net/ninja/ninja_<name>.cpp`. They were ported from the client and checked against it.
- **Envelope** = header (24 bytes) | body | trailer (32 bytes).

  The header fields are scattered over bytes 0..23 (written @01226ec4, read @0122786c / @012278f8 / @01227950 / @012279cc). The notation:
  - `S` is the salt. The client uses `low32(output buffer address) + r2`; any value works.
  - `M' = bswap32(first output of MT19937 seeded with r2)`.
  - `A' = bswap32(alg)`, `R' = bswap32(r2)`.
  - Rotations are by `S & 31`.

  | Bytes (in order, LSB first) | Content |
  |---|---|
  | 0, 6, 12, 18 | `S` |
  | 5, 11, 17, 23 | `rotr(0xbaabbaab ^ S, S)`. Signature check: `bswap32(S ^ rotl(x, S)) == 0xabbaabba` |
  | 1, 7, 13, 19 | `rotl(0x11010000 ^ S, S)`. Version check: `bswap32(S ^ rotr(x, S)) == 0x111` |
  | 3, 9, 15, 21 | `M' ^ A'` |
  | 8, 14, 2, 20 | `~M'` bytes 0, 1, 2, 3 |
  | 4, 10, 16, 22 | `R'` bytes 0..3 XOR `M'` bytes 3, 2, 1, 0 |

  So `alg = bswap32(~(b3^b8) | ~(b9^b14)<<8 | ~(b15^b2)<<16 | ~(b21^b20)<<24)` and `r2 = bswap32(~(b4^b20) | ~(b10^b2)<<8 | ~(b16^b14)<<16 | ~(b22^b8)<<24)`, byte-wise.
- **Body** (each class's Encrypt / Decrypt, e.g. AES @01227e24 / @012280a0):
  1. **IV generator.** The IV generator is XorShift128 when `(r2 + alg) & 1 == 0` and MT19937 otherwise (table @027e3060, @0123add0). It is reseeded with r2 for every message.
     - MT19937 is the standard `init_genrand(r2)`.
     - XorShift128 is seeded with `x = f(r2), y = f(x)+1, z = f(y)+2, w = f(z)+3`, where `f(s) = (s ^ s>>30) * 0x6c078965`. Its step is `t = x ^ x<<11; w' = t ^ t>>8 ^ w ^ w>>19`.
  2. **Draws.** In this order:
     1. `n = next()`.
     2. Skip `(n & k) + 1` outputs, where `k` = 0x3f for Serpent, 0x1f for MARS and Twofish, and 0xf otherwise.
     3. The IV is `next()` × block/4 words.
     4. The length mask is `next()`.
  3. **Body layout.** The body is `BE32(len ^ mask)`, followed by the plaintext padded with **0xff** bytes up to a multiple of the block size (no padding when it's already aligned; @0123c268), encrypted in CBC.
     - In the 16-byte classes and in IDEA and MISTY1, the chaining state starts as the IV words stored **little-endian**.
     - In Blowfish and CAST, the block is two big-endian words XORed with the IV words.
     - Body length = 4 + roundup(len, block).
- **Trailer** (@01227238 / @01227014). The digest is `D = SHA256((K ^ 0x36)[32] ‖ SHA256((K ^ 0x5c)[32] ‖ header ‖ body))`.
  - This is HMAC-like, with the pads swapped and a 32-byte key block.
  - Each BE32 word of D is rotated by `S & 31`, right when `S & 1 == 0` and left otherwise, and stored BE32.
- **Decrypt order** (@0123c0f4):
  1. Signature.
  2. Algorithm id matches the object.
  3. Trailer.
  4. Version.
  5. CBC decrypt, which needs `body ≥ 4 + block` and `(body − 4) % block == 0`. The plaintext length is the decoded first word; the client doesn't check it against the body.
  - Any modified byte fails the trailer check, and `Get<Api>Res` returns **-0x3b8**. The error table @0281caa0 maps errors 1..6 to -0x3bf, -1, -0x3b8, -0x3b9, -0x3ee and -1.
  - An algorithm id that isn't one of the ten makes the client dereference a null object, so never send one.
- **Packet integration.** **[confirmed, run]**
  - **Requests.** An encrypted request is `24-byte packet header (flags 0x80) | envelope | SHA-1`. The envelope's plaintext is the request body: RequestHeader + arguments, `docs/api.md` "Wire format".
  - **Replies.** An encrypted reply must look the same, and **flags 0x80 is required**:
    - `GameProtocoledData::Deserialize` (@01513d20, `AllocateBuffer` @01516758) only reserves room for the plaintext (`size + ((size + 0x94) & ~0x7f | 0x20) + 0x34`) when the flag is set.
    - `Get<Api>Res` copies the plaintext after the packet in that buffer and fails with -0x3eb when it doesn't fit.
    - `Get<Api>Res` decrypts any non-empty body whatever the flag, so replies to encrypted calls must always be encrypted.
  - The reply plaintext is the usual `u32 length + ASON blob`.
- **Not encrypted.** 12 of the 390 `GameProtocoledData::Set*` functions take no `Ninja*`, so their messages go out in the clear. **[confirmed, run]** The `gen_ninja_vectors.py packets` check counts them, and runs `EquipAccessoryRes` to confirm flags 0 and a plaintext body.
  - The session setup: `StartBridge`, `ResultStart` (so the bridge URL and token travel in the clear), `UpdateSession`, `ResultUpdateSession`.
  - `NoLoginStart` and its reply.
  - `ProtocolError`.
  - The special replies `MaintenanceRes`, `PartialMaintenanceRes`, `AccountSuspendedRes`.
  - Two oddities: `EquipAccessoryRes` and `CoinDepositAndroidUpdateRes`.
  - The other 378 messages are encrypted.
- **No request signing** beyond this: no HMAC over the arguments, and no nonce apart from the request-id hash and the header timestamp. **[inferred]** The envelope trailer authenticates each message with the session key, but nothing stops a replay within a session.
- **Server recipe.** `ninja::decrypt(K, envelope)` for every encrypted request. For each reply: `ninja::encrypt(K, ninja::kAES128, r2, salt, body)`, where r2 and salt are any values, then set packet flags 0x80 and append the SHA-1.
- **Checks.**
  - `soa-server --selftest net/ninja-vectors` (or `server/tests/ninja/ninja_check.sh`): the reference against `server/tests/ninja/ninja_vectors.txt`.
  - `.venv/bin/python server/tests/ninja/tools/gen_ninja_vectors.py {gen|ref2client|packets|choose|requests|replies}`. These need `work/` (the lib). `SOA_LIB=work/libSOA-3.7.0.so` runs them on 3.7.0. `requests` and `replies` check soa-server's wire layer against the client (section 9).

### Errors and status codes
- **Protocol errors.** The server reports a failed call as a **ProtocolError** packet (fid `05aed673`), not as an HTTP-style status. **[confirmed]**
  - The packet carries the failing FunctionID and an `Aska::Status` (`GameProtocoledData::Get/SetProtocolError` @0150ff20 / @0150ff78: 36 bytes = header + i64 status + u32 fid).
  - `CApiNotify::OnProtocolError` @014bafe8 turns the status into an API error code with `CNetworkUtility::AskaStatus2ApiErrorCode` @015f6768:
    - positive statuses pass through, and those are the server's codes (10004, 20000, 19001, …);
    - transport statuses map to 1002 / 1003;
    - Login's `-0x3c8` maps to 1002.
  - It then calls `ErrorHandler::Handle(fid, status)` @01581974, which opens the dialog with `error_message_text_<code>` (`ErrorCode::CreateErrorMessage`).
  - The code is stored for `ErrorCode(fid)` (`CApiNotify+0x514`).
- **The `status` key in a successful body** goes to `CParameterManager+0xb728`. No caller checks it (docs/client-changes.md). **[confirmed]**
- **Client-side codes:**
  - 1001: request in flight (`InitErrorCode` sets 0x3e9);
  - 1002: generic communication error;
  - 1003: disconnect (`CApiNotify::OnDisconnect` @014bb314);
  - 1004: maintenance;
  - 1005: disconnected by the server;
  - 1006 (0x3ee, no `master_text` row): `OnResultUpdateSession` and `BridgeNotify::OnReceive` set it when the session completes while a request other than StartBridge, UpdateSession, CreatePlayer or CbtCertification is pending, and then restart the call. **[meaning inferred]**
  - 8000x: communication or version errors.
  - [confirmed codes; the meanings are from `master_text`]
- **Server codes** (10001+): the 137 `error_message_text_*` rows in `master_text`. They're catalogued in [api.md "Appendix: server error codes"](api.md#appendix-server-error-codes) and used by [server-rules.md#refusals](server-rules.md#refusals).
  - Special: **19001** is "no player for this device". The 3.7.0 Login result lambda treats exactly this code as "start the new-player flow". **[confirmed, see server/src/api/entry/entry.cpp `login`]**
- **Retry.** Every method registers a closure, and `CErrorHandlerWrap` offers retry, back to title or give up (`ToRetry` / `ToTitle` / `ToGiveup`, `IsBusyRetry`). A retry re-sends with the same request id (section 1). **[confirmed]**

## 4. Session and authentication

### Identities
| Identity | Where it comes from | Evidence | Confidence |
|---|---|---|---|
| **Device UUID** (the credential) | A random 36-char UUID (`Aska::AUID::Generate` → `ToString`) created once and stored under the local-KVS key `uuid` (SharedPreferences, ChaCha20-encrypted like the rest of the save; README). `BAS::GetUUIDConsistently` creates it on first use | `BAS::CreateUUID` @01f34f84, `GetUUIDConsistently` @01f3509c, `GetUUID` @01f352c0 | confirmed |
| **Player id** | `Player.Id` (u32) issued by the server, kept in `CParameterPlayer` (+0x38) and saved encrypted under `BAS:PlayerID` | `CUIUtility::SetLocalKVSPlayerID` @01ee61dc; `GetStringKVSPlayerID` @01ee6704 prefixes it with a system message for the title / refund screens | confirmed. That this is the ID shown on the title screen (a u32 prints as up to 10 digits): inferred |
| Device type | `2` on Android (`BAS::GetDeviceType` @01f35350); sent with NoLoginStart, CreatePlayer and the bridge JSON | | confirmed; iOS = 1: inferred |
| Terminal id | `BAS::GetSqexBridgeTerminalId` @01f35380 = the Google advertising id | | confirmed |
| Push token | `BAS::GetDeviceToken` → `Platform::Android::GetDeviceToken_Android` (Firebase token); sent in Login | | confirmed |

**No password or OAuth.** Possession of the device UUID *is* the account.
- Moving to a new device went through **SQEX BRIDGE**, Square Enix's account-linking service: `uimsg_databackup_confirm` 「一度『SQEX BRIDGE』に登録しておけば … データを引き継ぎ」.
- The in-game データバックアップ menu opens it in a web view (docs/client-changes.md).
- How the bridge re-associated a UUID with an existing player on the server: **[unknown]**. It happened in the web flow.

### Flows
**[confirmed]** unless marked.
1. **Start of a session.** `Login()` @015b87e8 (and `SimpleLogin`, `NoLoginStart`, `CreatePlayer`):
   1. It resolves `production-game.so-ana.com:443` (`_InitURI` @015b7714 → `TARPCPeer::Initialize`).
   2. It makes sure the UUID exists.
   3. It runs `BeginBridge` with a callback that performs `_Login`.
2. **Bridge handshake** (`BeginBridge` @015b964c):
   1. **Game server:** `StartBridge(RequestHeader)` goes out in the clear.
   2. **Reply `kResultStart`** (clear; body = fixed `char[1024]` token, `char[128]` URL, `char[8]` x: measured on `SetResultStart`, and the client's `GetResultStart` reads soa-server's) → `CApiNotify::OnResultStart(token, url, x)` @014beb60. It **POSTs** `{"UUID":"%s","deviceType":"%d","nativeToken":"%s"}` to `url` over HTTPS (port 443 unless the URL names one), where `nativeToken` is the token the game server just issued. The body sent includes the string's NUL (`SetContent(buf, len + 1)`).
   3. The third value is printed (`"%s"`) into 8 bytes at `CApiNotify+0x508`. **[meaning unknown]**
   4. **The bridge replies** with gzip JSON. `BridgeNotify::OnReceive` @014eec24 reads `nativeSessionId` and `sharedSecurityKey`:
      - `SetSharedSecurityKey(sharedSecurityKey)` (vtable +0x6c8) arms the cipher: the first 32 characters of the JSON string become the session key (§3 "Encryption (Ninja)");
      - `UpdateSession(nativeSessionId)` (vtable +0x6d0, @015b9874, fid `ea04f3fd`) tells the game server which bridge session this TCP connection belongs to.
   5. **`kResultUpdateSession`** → `CApiNotify::OnResultUpdateSession` @014be9c4 marks the session bridged (+0x4d0) and runs the stored callback: the pending request goes out.
   - So the game server delegated authentication to a separate bridge service, which gave both sides the same session key.
3. **`_Login(fid)`** @015b850c asserts "BRIDGE isn't connected" if the handshake hasn't happened. It sends `Login` / `SimpleLogin` with:
   - the RequestHeader;
   - a 36-byte id field, sent as the placeholder `aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa` (`BAS::GetUUID` is read just before but not copied in): the device UUID travels in the bridge JSON and in `CreatePlayer`, not in Login. **[confirmed, run]** (soa-server's packet log of the unmodified client: every Login carries the placeholder; CreatePlayer carries the device UUID);
   - the push token;
   - the advertising id (all-zero UUID `00000000-0000-…` when unavailable);
   - a flag "advertising id present".
   - The reply (`kLoginResult`) carries the whole player state and the session parameters: `GameID`, `AssetPath`, `MasterPath`, `a_ver`, `r_ver`, maintenance keys and `Time` (api.md "Login").
   - `CApiNotify::OnLoginResult` @014be668 only applies the body: unlike every `On<Api>Res` it doesn't end the request (no EndRequest, no `ErrorHandler::Success`, no API-watchdog stop), so something else must have; with a LoginResult alone the client fails the login after 60 s (1002). soa-server follows it with a GetPlayerRes (`docs/server-rules.md`). **[confirmed: the handler; inferred: what followed]**
   - `OnLoginResult` gives the body's **root** map to `CParameterManager::Deserialize`, not the `data` map the `On<Api>Res` handlers read (`DeserializeToInfo`). The root's `Player` map fills the legacy `CParameterPlayer` (`Id`, `Token`, ...; pParseName "Player" @017f84d4), and `CApiNotify::LoggedIn` @014bb174 (its deserialized flag +0x178 and `Id` != 0) gates every later API: `NetworkApiCaller::<Api>` checks `LoggedIn` (vtable +0x6a0) first and otherwise shows `DisconnectDialog(-0x3b3)` (1002) without sending. So the real LoginResult had a top-level `Player` with a non-zero `Id`. **[confirmed, run]**: without it the unmodified client refused `GetMissionList` locally; with soa-server's root `Player` `{Id, Level, Name}` every later API went out.
   - After a successful reply the client looks for its app version in the `a_ver` it was sent (`CErrorHandlerWrap::CallBackCore` @01586b20) and otherwise asks to update the app. **[confirmed, run]**: also after `CreatePlayerRes`, which a new player's client gets before any Login reply.
4. **New player.**
   - `CPhase_Login::Progress` @018be944 (3.7.0 state machine): Login → error 19001 → terms (`UpdateKiyakuVersion`, `master_global.kiyaku_version` = 20200319) → name entry → `CreatePlayer(name, uuid)` (wire adds DeviceType and a string) → Login again.
   - Then the download setting, `SaveToLocalKVS`, `SetLocalKVSPlayerID`, `CPaymentManager::Initialize` and `GamerServiceManager` (Google Play Games).
   - (Our restore runs this 3.7.0 body: docs/client-changes.md.)
5. **Other entry points.**
   - `NoLoginStart(uuid)` @015cc0b4 (fid `95804837`): connects to the same host and sends UUID + DeviceType without a bridge. In 3.7.0 it's the pre-login call of `CPhase_Server`. In the offline build it's the game's only request.
   - `SimpleLogin` (fid `447fafb8`) is used by the refund flow after service end (`CTitle::PayBackConnect` @01e85004).
   - `CbtCertification` checked closed-beta serials (13001 / 13002, beta ended `master_global.cbt_end` 2016-11-28).
6. **Connections, expiry and re-login.**
   - **One connection per request.** The client closes its game connection after each reply and connects again for the next request. **[confirmed, run]** (soa-server's packet logs: NoLoginStart on connection 1, the bridge and Login on 2, then GetServerTime, GetMissionList, MissionStart, MissionEnd, ... each on a new connection.)
   - When the connection drops, `OnDisconnect` / `OnError` clear the bridged flag unless the player is logged in (`CApiNotify::OnError` @014bb1fc, `OnDisconnect` @014bb314).
   - So a logged-in client's next request goes out at once on the new connection, **encrypted with the session key, with no StartBridge or UpdateSession**. **[confirmed, run]** The server has to find the session of such a connection; how the real one did is **[unknown]** (the RequestHeader naming the player is inside the ciphertext). soa-server tries its sessions' keys (`docs/server-rules.md` "Reconnects continue the session").
   - Before the login (no player yet: NoLoginStart, Login → 19001, CreatePlayer) the flag is cleared, and the next call runs `BeginBridge` again: a new session and key. **[confirmed, run]** (the new-player flow: a second StartBridge / UpdateSession before CreatePlayer.)
   - The 3.7.0 phase list has `CPhase_Relogin` and `CPhase_SyncServerTime` (`GetServerTime`, with a DNS-cache flush), which the offline build removed (docs/history/notes-3.8.0.md).
   - How long a bridge session lived on the server: **[unknown]**.
7. **`EndBridge`** @015b9864 just terminates the TCP peer (`TPeer::RequestTerm`). **[confirmed]**

## 5. State model: what the server decided

| Area | Real server | Client | Evidence |
|---|---|---|---|
| Player, roster, items, wallet, presents | **Authoritative.** Every change is a request; responses send deltas (`AddItem`, `AddCharacter`, `UpdateStockItem`, `LimitBreakCharacter`, `AddPresent`) or whole lists (`Character`, `Item`, `StockItem` replace) | Applies them (api.md "Player state and response lifetimes") | confirmed |
| Battle | Starts it (`MissionStart` stamina cost, stage list, pre-rolled drops, and the party's **battle status, precomputed by the server**: `BattleParameter.PlayerCharacter` = `CPersonStatusInfo`, which the client never builds; notes "Playing a battle and a gacha through"). Ends it: EXP, FOL, drops, first-clear presents, evaluation rewards | **Simulates the whole battle locally** and reports a battle log: `MissionEnd` sends the ASON `CBattleLogInfo` (≤ 4096 bytes: result, times, damage, hits, rush, continues, autoplay …) plus the evaluation array. The log also carries the party's full status (`PlayerCharacter`, `CPersonStatusInfo`), a `PlayerCharacterCheat` list, the stage's and the defeated enemies (`StageEnemyInfo`, `DefeatedEnemyInfo`) and per-player `CPlayerLogInfo` (api.md "Wire format", MissionEnd example) | confirmed |
| Gacha | Draws server-side; the client shows `GachaItems`. Gacha lists are keyed by `GachaHashMap` hashes the client echoes back (`SaleGacha(id, hash)`) | Presentation only | confirmed |
| Status display | Also computes statuses (for the battle party) | `CalcStatus` / `PersonModel::CalculateParameter` for the menus | confirmed (both exist) |
| Stamina | Stores `stamina`, `stamina_max`, `stamina_update` | Regenerates the display itself (`StaminaUtility::NowStamina` → `CTimeUtility::NowAp`), so both sides must share the formula | confirmed (server-rules "Stamina") |
| Time | `data.Time` in responses; `GetServerTime` | `CServerTime::UpdateServerTimeOffset` @015fa2fc keeps an offset when off by ≥ 60 s | confirmed |
| Co-op battles | Lobby (rooms, automatch) plus a relay; the host's client runs the enemies and sends snapshots (`PackCharacterParameterEnemy`, `SendAIParameter`) | Host / guest roles in `CMultiplayManager` | inferred |

**Anti-cheat hints.**
- **In-memory obfuscation.** Sensitive values are kept encrypted in memory: `CParameterPropertyBase<N>::CryptString` on the player and session properties and on the server time. **[confirmed]**
- **Transport.** The transport is encrypted per session and scrambled (section 3).
- **Battle logs.** There's no sign of a battle replay or signature. The log is plain values inside the encrypted body, so the server could only sanity-check them (for example, a clear time against the stage). What it actually checked: **[unknown]**.
- **Bans.** The server could suspend an account: the `AccountSuspendedRes` reply (section 2) shows 「不正行為を確認したため、アカウントのご利用を停止しております。」 **[confirmed]**
- **Misbehaviour codes.** Code 10205 / 10403 / 1060x / 190xx 不正なデータ処理です ("invalid data processing") shows that the server rejected inconsistent requests. **[confirmed texts]**
- **"Judgment".** `IsJudgment` and `JudgmentUrl` exist in the response schema. **[meaning unknown]**
- **Packer.** The 3.7.0 APK ships a Java code protector: `lib/arm64-v8a/lib__57d5__.so` plus an encrypted `assets/57d5/data1.dat`. The app's own activities (`SOAActivity` etc.) aren't in the plain `classes.dex`. **[confirmed; the packer is unidentified]**

## 6. Asset and master-data delivery
**[confirmed]** from `work/download-3.7.0` and `CGameResourceDownloader`, unless marked.
- **`version.bin`** (MessagePack) = {`appliversion`: 3223089, `version`: 32-hex id, `revision`: `"1471"`, `assets`: 26,268 entries}.
  - Each entry: {`md5` (actually 40 hex = SHA-1), `size`, `time`, `parentHash`, `flags`, `encType`, `ep_data`, `meta`}.
  - `encType` 1 = ADLD XOR asset (notes "Asset encryption (ADLD)"); 2 = the AES master DB `sqlite/basmaster.sqlite3`.
- **Manifests** under `manifest/<texture format>/<quality>/`, e.g. `manifest/etc2/hi/`:
  - `version.version` holds the version id;
  - `version_latest_{Bulk,Individual,ep1,ep2,ep3}.{bin,version}`: `.version` = `version:<id>` / `totalSize:<bytes>` (3,289,533,049 for the full set); `.bin` = {`version`, `toolversion` "1.2.0", `assets`: bundle → member files};
  - `B/<hash>/<hash>.bin` bundles for bulk download; `EP1`..`EP3` bundles for the per-episode data.
  - The downloader strings match: `version_latest_Bulk.bin`, `version_latest_ep%d.bin`, `downloadfilelist.tmp`, `buildin_varsion.bin`, `toolversion`.
- **URLs.** **[confirmed, 3.7.0 decompile]** `CDownloadNode::StartDownload` @018df0b4 = `<base>` + `Android/` + `<node name>`.
  - `<base>` = `CGameResourceDownloader` +0x220, set by `SetDownloadDataServer(CInfoManager::GetDownloadURL())` in `CPhase_DataDownload::Progress`; `GetDownloadURL` @01614ab0 = `"%s/%s/"` of `CInfoManager` +0xaaf0 (property 543, the Login key **`AssetPath`**) and +0xac90 (property 551, **`r_ver`**). So every URL is `<AssetPath>/<r_ver>/Android/<name>`.
  - For a node whose byte +0x110 is set, `download/` in the base is replaced by `master/` and `Android/` is not added. Nothing in 3.7.0 sets that byte (only zeros are stored, `CDownloadNode` ctor and `Progress_Setup`), so the swap is dead code. `MasterPath` has no reader we found.
  - `r_ver` is also the server's asset revision: `CInfoManager::GetResourceVersion` (r_ver) goes to `SetServerAssetRevision` @018ddfe4, which flags a change (+0x155) when it differs from the last one; the client then fetches `version.bin` and the manifests again (`Progress_Setup`).
  - Node names: `version.bin`, `manifest/<format>/<quality>/version.version` and `version_latest_*.{bin,version}`, and **bundles**: the client never downloads single assets. `CVerifyTask::ProgressManifestCheck` walks a manifest's bundles (`I/<h>/<h>.bin` in Individual, `B/<h>/<h>.bin` in Bulk, `EP<n>/…/<h>.bin` in the episode manifests), and requests a bundle when one of its members is missing locally.
  - The host names of the CDN: **[unknown]**. They weren't in the client and came from the server.
- **Bundles** **[confirmed]**: a `Framework::FileStream::tImage` (`\0ISF`): u32 magic 0x46534900, u32 version (≤ 0x20130304), u32 count, u32 [unused by the client]; then count entries of 4 u32 {name offset, payload offset, payload length, [unused]}, offsets from the bundle start.
  - The downloaded bundle's SHA-1 (`CDownloadStream::Close` → `BAS::CryptBufferSHA1`) must equal the manifest's bundle `md5`, else error -935 (`CDownloadNode::Handler`).
  - Each member is written as `ADLD`, u32 `e`, 8 zero bytes, then the payload (no header when `e` = 0) (`UnpackNotify::Handler`), so a payload is the stored asset minus its ADLD header.
  - The manifests' sizes fit names packed after the entries, payloads 32-byte aligned and the total padded to 32 (about 20% of the 3.7.0 bundles are not end-padded). The unused words and padding bytes are unknown: no rebuilt bundle reproduced a 3.7.0 bundle hash.
- **Manifest fields** **[confirmed]**: bundle → {member → {`size` = the plaintext size, `md5` = SHA-1 of the plaintext, `meta`, `p` = the bundle name without `.bin`, `e` = encType, `ep_data`}, `md5` = the bundle's SHA-1, `size` = the bundle's size, `meta`}.
  - In `version.bin`, `size` is the stored (ADLD) file's size, `md5` the plaintext's SHA-1, `parentHash` = CHash32 of the member's Individual bundle name (e.g. `I/c160c701/acb04180.bin`). The 234 `flags` 1 entries are Individual bundles themselves (`md5` = the bundle's, `size` 0).
  - `ProgressLocalFileCheck` compares a local file's size and mtime with the entry.
- **Transport.** It goes through `Aska::Yayoi::Downloader`: worker thread, `DownloadContext` pool, pause / resume, the same Java HTTP path (gzip-aware).
  - Files are verified by size and hash (`CVerifyTask::InitializeManifestCheck`), with a journal (`CJournalFileWriter`) for resuming.
- **Detecting updates.**
  - The client sends its revision in every request.
  - `CGameResourceDownloader::SetServerAssetRevision` @018ddfe4 records the server's revision and flags a change (+0x155).
  - The game then returns to the data-download phase (`CPhase_DataDownload`; "更新されたデータがあります" 1013 / 10000001). **[inferred for the trigger]** **[confirmed, run]** for the login: a Login carrying `AssetPath` and `r_ver` 1472 (the APK's data is 1471) makes the client read `manifest/etc2/hi/version_latest_*` and offer the 3,138 MB download; on a phone that has it, only the `.version` files are read. A new player's `CreatePlayer` needs no CDN keys: the Login that follows carries them.
- **The master DB** is downloaded like any asset, but encrypted (`encType` 2). `CStaticTransaction::Progress` decrypts it into memory (notes "Master DB load").
- **What soa-server serves** (`server/src/cdn/`: `tree.cpp`, `bundle.cpp`, `served_master.cpp`; server/README.md "CDN"; rules and labels in server-rules.md#cdn). The 3.7.0 download (work/download-3.7.0) holds every member of every bundle, unpacked: 24,625 members in 23,990 Individual and 1,027 Bulk bundles, plus 1,408 in the episode manifests.
  - soa-server rebuilds each bundle on request and lists our bundles' SHA-1 and size in the manifests it serves.
  - The master is the 3.7.0 one plus the client-master overrides, re-packed (`encrypt(decrypt(x))` reproduces the 3.7.0 file byte for byte).
  - `version.bin` gets revision 1472 and new version ids.
  - Login sends `AssetPath` = `http://production-game.so-ana.com/download` (`--cdn-url`; the client can't take a URL with a port, so the client maps the name to soa-server's `--http`) and `r_ver` = `1472`.
  - The client then requests, e.g.:
    - `http://production-game.so-ana.com/download/1472/Android/version.bin`
    - `…/Android/manifest/etc2/hi/version.version`, `…/version_latest_{Bulk,Individual,ep1,ep2,ep3}.{bin,version}`
    - the master's bundles `…/Android/I/86c7aec3/3a05a888.bin` (Individual) and `…/Android/B/1115774b/b9a9e011.bin` (Bulk)
    - any other bundle of the manifests (`…/Android/I/c160c701/72580769.bin`, …)
    - the stand-ins' `…/Android/I/5374616e/<h>.bin` and `…/Android/B/5374616e/standins.bin`.

## 7. Other online services
- **Payments.** **[confirmed]**
  - Google Play Billing (`Aska::Yayoi::GooglePlayClient`, `jb.Aska.InAppBilling`, `com.android.vending.BILLING`) and Amazon IAP (`com.amazon.device.iap.ResponseReceiver`, `com.amazon.android.Kiwi`). An iOS path exists in the API (`CoinDepositIOSUpdate`).
  - `CPaymentManager::VerifyReceipt_` @015f91b0 base64-encodes the store receipt and sends it with its signature through the API caller (vtable +0x370, the `CoinDeposit*Update` family). **The game server verified the receipt** and credited `pay_coin`.
  - Failures were reported with `SendErrorLog`.
  - Age limits (Japanese spending caps for minors): `GetBirthYearMonth` / `UpdateBirthYearMonth`.
- **Push notifications.**
  - Firebase Cloud Messaging: `SOAFirebaseMessagingService`, `com.google.firebase.MESSAGING_EVENT`. The token goes to the server in Login. **[confirmed]**
  - Local notifications (`SOAActivity$LocalNotificationReceiver`, `BAS::ScheduleLocalNotification`) for stamina and similar, client-side. **[confirmed]**
- **Multiplayer.** **[confirmed transport]**
  - **Superseded by [multiplayer.md](multiplayer.md)** (2026-10-02), which corrects this list: the room messages (`EnterRoom`, `ExitRoom`, `UpdatePlayerList`, `ChangePublicRoom`, `StartMultiplay`) are BattleProtocol messages on the relay, neither protocol has the SHA-1 trailer or Ninja, and in co-op MissionStart / MissionEnd go through the relay (`MissionStartPush` / `MissionEndPush`).
  - It uses **its own TCP protocols, not Photon or any SDK**:
    - `MultiplayRPC::LobbyProtocol` on the lobby host, port 4001: `EnterLobby`, `CreateRoom`, `GetRoomList`, `UpdateRoomInfo`, `CloseRoom`, `Automatch`, `EnterRoom`, `ExitRoom`, `UpdatePlayerList`, `ChangePublicRoom`, `StartMultiplay`.
    - `MO::BattleProtocol` to a per-room relay: `StartBattleStage`, `FinishBattleStage`, `Snapshot`, `Message`, `Packet`, `AIParameter`, `Stamp`, `StartRushCombo` / `Sync*`, `MissionContinue`, `MissionEnd`, `RequestProxy`, `Reconnect`, the pushes listed in section 3.
  - `UDP` and UPnP code ("For Aska" port mapping) is linked but has no multiplayer instantiation. All three RPC peers are `TPeer<TCP, …>`.
  - The API server still ran the missions (`MissionStart` / `MultiMissionRestart` / `MissionEnd`, and the host bonus in the drop tables).
- **Social** (follow, blacklist, neighbours, player search, rental helpers): ordinary game-server APIs (api.md "Social"). Location check-in (`LocationRegist`, `NeighborList`) uses the location permissions. **[confirmed]**
- **Rankings.** Event and Sphere 211 rankings are game-server APIs (`GetEventRankingInfo`, `GetSphere211RankingInfo`). Google Play Games leaderboards and achievements run in parallel (`BAS::ReportScore`, `ReportAchievement`, `ShowLeaderboard`; `play-services-games`). **[confirmed]**
- **Web views.** Notices, banners, terms and help pages are HTML from `production-cache.webview.so-ana.com` and Square Enix support (section 2) in `BAS::WebView`. The notice board opens once a day from the login popups (docs/client-changes.md). **[confirmed]**
- **Analytics and logging.**
  - SmartBeat crash and log reporting: `_SmartBeat::Initialize`, `SendLog`, `LeaveBreadcrumb`, `SetUserID` = player id. **[confirmed]**
  - Firebase core and Google ads / ads-identifier libraries (the advertising id is the bridge terminal id). **[confirmed]**
  - `SendErrorLog` (API) for payment errors. **[confirmed]**
  - No other analytics SDK was found in the plain dex. The protected part may hold more. **[unknown]**

## 8. What we cannot know
- The **server code and database**: how rules were evaluated, balance tables not in the master DB, drop pre-rolls, gacha RNG, anti-cheat thresholds, rate limits.
- The **bridge endpoint URL** and its protocol beyond the one request and reply seen. Also how SQEX BRIDGE data transfer re-bound a UUID to a player.
- Which of the ten envelope ciphers the **real server** replied with. The envelope's layout and all ten ciphers are confirmed (§3 "Encryption (Ninja)"), and the client accepts any of them, so it doesn't matter to a server.
- The **CDN hosts** and path layout behind `AssetPath` / `MasterPath`, and the lobby / battle relay addresses in production (`LobbyPath`, `*ProxyPath/Port`).
- The Java side's **HTTP timeouts and user agent** (in `jb.Aska.HttpClientBridge`, and possibly in the packed code).
- Server-sent values that no client code reads (`IsJudgment`, `JudgmentUrl`, the third `OnResultStart` value).
- Anything after 3.7.0 on the server side, and exactly which keys each response contained (api.md lists the minimum the client consumes).

## 9. How our local server maps onto this
There are two ways to run our server (`server/`, rules in [server-rules.md](server-rules.md)):
- **In-process** (`soa`): the port replaces the network stack at the **API-method level**; it isn't wire-compatible (first table).
- **Out of process** (`soa-server`, 2026-10-01): a standalone server that **speaks the wire protocol** of sections 3-4 to the unmodified 3.7.0 client (second table; `server/README.md` "soa-server and the wire layer").

### In-process (`--server inproc`)
| Real piece | Our emulator | Where |
|---|---|---|
| `NetworkApiCaller` + GameRPC + TCP 443 + Ninja cipher | Not used. The port constructs `FakeApiCaller` instead and hooks its methods natively; `server_port::capture`, port/src/native/api/server_adapters.cpp reads each method's arguments from the registers (by mangled signature) | `port/src/native/api/fakeapi.cpp`, notes "Offline server (FakeApiCaller)" |
| Bridge handshake, `sharedSecurityKey`, `UpdateSession` | None. `FakeApiCaller::BeginBridge` / `EndBridge` return success, and `LoggedIn` reports the local server's own session flag (set after a Login) | `fakeapi.cpp` (`kLoggedIn`) |
| Device UUID / `Player.Id` | One local player in `DATA/server.sqlite3`, seeded from `work/Game-3.7.0.xml`, or none with `--new-player` | `server/src/state/seed.cpp` |
| Login / 19001 / CreatePlayer / terms | Same codes and order: no player → 19001 → the restored 3.7.0 `CPhase_Login` runs terms, name entry and `CreatePlayer` | `server/src/api/entry/entry.cpp` `login`; docs/client-changes.md |
| Response bodies (ASON `{data, status}`) | Same format, encoded by `server/include/soaserver/msgpack.h` and fed to the same `CApiNotify::On<Api>Res` handlers | `server.cpp`, `ext.h` |
| ProtocolError → `ErrorCode(fid)` → dialog | `server::error_code(fid)` is reported through the port's `FakeApiCaller::IsSuccess` / `IsFailure` / `ErrorCode` hooks; the same `error_message_text_<code>` dialogs appear | docs/client-changes.md "error codes"; server-rules "Refusals and error codes" |
| Server clock / `data.Time` | Every response carries `data.Time` from the server clock (`--clock`, event calendar replay) | server-rules "Conventions" |
| Server-side rules (drops, gacha, growth, EXP…) | Re-implemented from master data and client evidence, each labelled (a)–(d) | server-rules.md |
| CDN / downloader | soa: no download; `--download-dir work/download-3.7.0` serves the 3.7.0 files through the asset lookup, and the offline master DB gets the client-master overrides in memory with the in-process server. soa-server: an HTTP CDN of rebuilt bundles, manifests, `version.bin` and the re-packed 3.7.0 master with the same overrides (section 6) | port/README.md; server/README.md "CDN" |
| Maintenance / version checks | Not emulated: no maintenance keys; the asset revision in the header doesn't exist on this route | — |
| Multiplayer lobby / relay | Not emulated. `FooterMissionInfo.is_open_multiplay` = 0; rental helpers are NPC stand-ins | server-rules "Social" |
| Payments, push, SmartBeat, Play Games, WebViews | Not emulated. No payments (d); the port has no WebView | server-rules, docs/history/REMAINING.md |

### Out of process (`soa-server`)
The same library answers; `server/net/` is the wire layer. Its own choices, where the client doesn't tell what the real server did, are labelled in [server-rules.md#wire-layer](server-rules.md).

| Real piece | soa-server | Where |
|---|---|---|
| TCP 443, packets (scrambled header, SHA-1 trailer) | `--listen HOST:PORT` (default 127.0.0.1:44300); the same packets, SHA-1 checked, the request's counter echoed | `server/net/wire.cpp`, `loop.cpp` |
| Ninja envelope | All ten algorithms decrypted; replies in AES-128 with flags 0x80; the 12 clear messages in the clear | `server/net/ninja/ninja_*.cpp` |
| StartBridge / ResultStart / bridge POST / UpdateSession | ResultStart(token, `https://production-game.so-ana.com/bridge`, ""); `POST /bridge` on `--http` (default 127.0.0.1:44380) answers gzip `{"nativeSessionId","sharedSecurityKey"}`; UpdateSession binds the connection to the session key; a logged-in client's reconnect is bound to the session whose key decrypts its request | `server/net/game.cpp` |
| Device UUID → player | The state DB's one player for every device (`wire_device` table); none on a fresh `--new-player` state (Login → 19001 → new-player flow) | `game.cpp` `map_device` |
| Request bodies | Decoded by the measured layouts (`docs/api-wire.txt` → `server/net/gen/wire_decode.inc`) into the same `server::Request` soa builds; the MissionEnd battle log becomes `Request::battle_log` | `server/net/wire.cpp` |
| Replies | `<Name>Res` = u32 length + MessagePack (LoginResult: fid + length + MessagePack); refusals are ProtocolError(status = the error code) | `game.cpp` |
| CDN | Rebuilt bundles, manifests, `version.bin` and the re-packed master from `--download-dir` (section 6) | `server/src/cdn/` (`tree.cpp`, `bundle.cpp`, `served_master.cpp`), `server/net/cdn_http.h` |
| Maintenance, multiplayer, payments | Not emulated | — |

**Checked against the client's own code** (unicorn, `server/tests/ninja/tools/gen_ninja_vectors.py`):
- `requests`: 11 request packets serialized by the client's `Set<Api>` + Ninja (Login, GetPlayer, SetTitle, MissionStart, MissionEnd with a battle log, GachaOnce, LockItem, CreatePlayer, StartBridge, UpdateSession, NoLoginStart) are accepted by the client's own `Deserialize` and decoded by soa-server to the expected arguments (`soa-server --selftest net/client-requests`, vectors in `server/tests/net/client_requests.txt`).
- `replies`: soa-server's reply packets (GetPlayerRes, MissionStartRes, MissionEndRes, GachaOnceRes, LoginResult, the clear NoLoginStartRes and EquipAccessoryRes, ResultStart, ResultUpdateSession, ProtocolError) are accepted by the client's `Deserialize` and read back unchanged by its `Get<Api>Res`, `GetLoginResult`, `GetResultStart`, `GetResultUpdateSession` and `GetProtocolError`.
- A live run (`soa-server --log-packets DIR` + `soa-server --wire-tool session HOST:PORT`): bridge, Login (158 KB LoginResult), GetPlayer, GetServerTime.
- **The unmodified 3.7.0 client** (`soa-emu`, `emulator/scripts/emulator_session.sh`, 2026-10-01, agent `e6-end2end`): its packet logs show the seeded flow (NoLoginStart, the bridge, Login + GetPlayerRes, the CDN download, GetServerTime, GetMissionList, MissionStart, MissionEnd with a 3.7 KB ASON battle log that soa-server decodes — `mission_time`, `DefeatedEnemyInfo`, `BattleEvaluationInfo`, the party's `PlayerCharacter` statuses —, GetGachaInData, SaleGacha) and the new-player flow (Login → 19001, StartBridge again, CreatePlayer with the device UUID and the name, Login, MissionTalk / EndMissionTalk, UpdateTutorial 1-9, the tutorial's MissionStart / MissionEnd). The client's envelope ciphers vary per message (all ten seen: AES128, Blowfish, Camellia128, CAST128, IDEA, MARS, MISTY1, SEED, Serpent, Twofish). **[confirmed, run]**
