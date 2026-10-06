# emulator/: the 3.7.0 online client, unmodified (`soa-emu`)

`soa-emu` runs the last online build of STAR OCEAN: anamnesis, `work/libSOA-3.7.0.so`, as shipped: pure JIT, no restore code, no in-process server. It reads its assets from the single 3.7.0 APK. Only the platform layer under the game belongs to the emulator: the Android imports (HLE) and the Java methods the client calls through JNI. The game code is unmodified but for **two native patches**: the client's own "has the service ended?" check is taken out, so it runs on the real date ("The date and `service_stop_day`" below), and the sale-stopped dialog (紋章石の販売は停止しています) opens the coin shop instead (the user's decision, 2026-10-05; `docs/client-changes.md` "Emulator mode"); `--no-patch` runs it without both.

It is a separate program from the port (`port/`, the `soa` binary, which runs the same 3.7.0 client with natives and its in-process server). Both are built on the JIT host runtime, `runtime/` (`runtime/README.md`). The 3.7.0 platform layer (the Java answers, `fmod`, the device clock, the patch, the network glue) is a library of its own, `platform370/` (`platform370/README.md`), so that the port can use it too (P1 of `docs/history/PLAN-rebase-370.md`). The emulator plugs into the runtime only through its extension points and `platform370`, and links nothing from `port/`.

Plans (done, now history): [`docs/history/PLAN-execution.md`](../docs/history/PLAN-execution.md) (the approved steps; this was steps 2 and 5) and [`docs/history/PLAN-emulator.md`](../docs/history/PLAN-emulator.md) (background).

## Building

```sh
scripts/build.sh --target soa-emu            # from the repository root (README.md "Building"): build/emulator/soa-emu
```

`emulator/CMakeLists.txt` is a subdirectory of the repository's build, added after `runtime/`; the shared settings and the dependencies (vcpkg, dynarmic by `FetchContent`: `cmake/deps.cmake`, README.md "Setup") come from the root `CMakeLists.txt`. `scripts/build.sh` sets up vcpkg the first time. `-DSOA_BUILD_PORT=OFF -DSOA_BUILD_SERVER=OFF` builds only the runtime, `platform370` and the emulator (`SOA_BUILD_EMULATOR` needs `SOA_BUILD_PLATFORM370`). It links `soaplatform370` (`platform370/`), the runtime (`soaruntime`, whole archive) and its desktop host loop (`soaruntime_app`: the SDL window, input, audio, the control FIFO and the activity bring-up, shared with `soa`).

## Running

```sh
build/emulator/soa-emu                       # a window; data in ~/.local/share/soa-emulator-370/phone
build/emulator/soa-emu --headless --control /tmp/emu.fifo
control/soactl.py /tmp/emu.fifo tap:364:713 wait:3000 shot:/tmp/emu.png
```

`soa-emu --help` lists the options (CLI11, `src/cli.cpp`; the ones it shares with `soa` are defined once: `runtime/src/app/cli.h`, `platform370/include/platform370/cli.h`, `common/include/soa/cli.h`). A value-taking option given twice: the last one wins (`--apk`, `--shot`, `--do`, `--map-host` collect); an error prints one line and exits 2.

| Option | Meaning |
|---|---|
| `--lib PATH` | The client library. Default: `<repo>/work/libSOA-3.7.0.so`. |
| `--apk FILE` | The APK whose assets the client reads. Default: `<repo>/apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk`. It isn't extracted: the runtime's asset manager indexes any zip. Repeatable; a later APK wins. |
| `--data DIR` | The emulated phone's storage: saves, SharedPreferences, downloads. Default: `~/.local/share/soa-emulator-370/phone` (Windows: `%LOCALAPPDATA%\soa\emulator-370\phone`; `common/include/soa/paths.h`), beside the port's `~/.local/share/soa-linux-370` (`scripts/run-emulator-370.sh` keeps the server beside it in `server/`). Never point it at a port data dir: it holds that port's cached `libSOA.so` and save. |
| `--download-dir DIR` | A temporary stand-in for the CDN: assets missing from the APK are served from DIR (e.g. `work/download-3.7.0`). Off by default. The boot to the network path doesn't need it. |
| `--download-prefer` | With `--download-dir`: DIR wins over the APK (as `soa` and `soa-viewer`). |
| `--server HOST[:PORT]` | The game server, soa-server's `--listen`. Default `127.0.0.1:44300`. The client's `production-game.so-ana.com` resolves to HOST, and its port 443 becomes PORT. See "Networking". |
| `--http HOST:PORT` | soa-server's `--http`. Default `<server host>:44380`. `http://` and `https://` URLs to a mapped host are fetched there, as plain HTTP. |
| `--lobby HOST:PORT` | Where the client's lobby connections (port 4001) go. Default: not redirected. |
| `--map-host NAME[=ADDR]` | Also resolve NAME to ADDR (default: the server host). Repeatable. |
| `--device-clock "YYYY-MM-DD HH:MM:SS"` / `host` | The phone's clock (local time) at start; it runs on from there. Default `host`: the host's real time. A test option; see "The date and `service_stop_day`". |
| `--no-patch` | Run the client without its native patch (`platform370/src/patch_370.cpp`): the service-end check is live, so on the real date the title shows the service-end notice and "TAP TO START" asks to update the app. For comparison runs. |
| (window title) | `[EMULATED] STAR OCEAN -anamnesis- 3.7.0 online client (soa-emu)`, so it can't be mistaken for the port's `soa` window. |
| `--repo DIR` | The source checkout, for the defaults. Default: found upwards from the executable. In a git worktree, files the worktree lacks (the APK) are also looked up in the main checkout that `work/` links to. |
| `--guest-cpus N` / `host` | CPUs the game sees. Default 8. |
| `--headless` / `--windowed` | Don't show the window. It still renders: screenshots and the control FIFO work. `--windowed` (the default) undoes an earlier `--headless`, as in `soa`. |
| `--size WxH`, `--landscape`, `--render-size S`, `--fullscreen` | Window and game-screen size, as in `soa`. |
| `--shot S:PATH`, `--do S:ACTION`, `--control FIFO` | Scripted input and screenshots, as in `soa`. The commands are `tap`, `drag`, `wheel`, `back`, `text`, `shot`, `resize`, `fullscreen`, `quit`; `control/soactl.py` drives the FIFO. `soa`'s `phase:` / `call:` / `uiset:` debug commands need natives and don't exist here. |
| `-v` / `-vv` | Verbose / trace logging. |

Settings are flags only (a `SOA_*` variable that was a setting prints one warning naming its flag; `docs/environment.md`). The runtime's diagnostic switches work too (`SOA_TRACE`, `SOA_PROFILE` / `SOA_COVERAGE`, `SOA_WATCHDOG`, ...): [`runtime/README.md`](../runtime/README.md) "Environment".

## What is emulator-specific
Only `emulator/src/main.cpp`. The platform layer it runs the client on moved to `platform370/` (2026-10-01, P0 of `docs/history/PLAN-rebase-370.md`; `git log --follow` keeps the `*_370.cpp` files' history), so the port can share it. `platform370::install` registers its pieces through the runtime's extension points. `docs/client-changes.md` "Emulator mode" lists the same answers for the change log.

| File | What | Extension point |
|---|---|---|
| `emulator/src/main.cpp` | Command line → `platform370::Config` (every piece on; `--server` / `--http` / `--lobby` / `--map-host` → `netcfg`, `--device-clock`, `--no-patch`); the single 3.7.0 APK and the library; its own data dir; the runtime bring-up: `platform370::install` before `hle_init`, `platform370::install_patches` after `load_library` | `device_config()`, `asset_manager().add_apk`, `app::run` |
| `platform370/src/java_370.cpp` (was `emulator/src/`) | The `AskaActivity` methods only 3.7.0 calls, answered like a phone without those services (below) | `jni::add_class_installer`, `Vm::def` |
| `platform370/src/hle_370.cpp` (was `emulator/src/`) | The import 3.7.0 needs that the runtime lacks (`fmod`), and the optional device clock (`--device-clock`) | `hle_add_registrar`, `Hle::override_fn` |
| `platform370/src/patch_370.cpp` (was `emulator/src/`) | The native patches: `CParameterUtility::FindGlobalStringWithKey` answers `service_stop_day` with `""` (below); `CDialogManager::OpenBuyEndDialog` opens the coin shop (`docs/client-changes.md` "Emulator mode") | `hook_guest_function`, `make_original_trampoline` (`core/cpu.h`), after `load_library` |
| `platform370/src/net_370.cpp` (was `emulator/src/`) | The network redirect: `getaddrinfo` / `gethostbyname` / `connect` (and their Bionic-vs-glibc fixes) | `hle_add_registrar`, `Hle::override_fn` (delegating to the runtime's thunks) |
| `platform370/src/http_370.cpp` (was `emulator/src/`) | The HTTP client behind the `AskaActivity` HTTP methods | `jni::add_class_installer`, `Vm::override_method` |
| `platform370/include/platform370/platform370.h`, `platform370/src/platform370.cpp`, `internal.h` (was `emulator/src/emu.h`) | The library's API: `Config`, `install`, `install_patches`, `net_config` (`platform370/README.md` "API") | |

`app_version = "3.7.0"` (`SOAActivity.GetApplicationVersion`) is `platform370::Config`'s default, set by `install`. The library's log lines are tagged `p370` (the patch and the clock); the network and HTTP lines keep `net` and `http`.

### The Java methods (`java_370.cpp`)
3.7.0 calls 25 `jb.Aska.AskaActivity` methods that the offline build (which the runtime's Java side was written for) doesn't.

**How the list was found.** The strings in `work/libSOA-3.7.0.so` that the offline build lacks give the names. Each name was paired with the signature string loaded next to it at its `GetMethodID` call site (the `Platform::Android::*` wrappers at 0x1e38c04–0x1e39fb4): an `adrp`/`add` scan of the code for references to the name, then the `(…)…` string referenced within the next instructions.

| Methods | Signatures | Answer |
|---|---|---|
| `ConnectPlayServices` | `()V` | Logged. The sign-in is attempted and fails. |
| `IsConnectedGooglePlayServices` | `()Z` | false |
| `IsLoginFailedGooglePlayServices` | `()Z` | false until `ConnectPlayServices` was called, then true |
| `SetReportAchievementTarget`, `ReportAchievement`, `ResetAchievements`, `ShowAchievements` | `(Ljava/lang/String;)V`, `(I)V`, `()V`, `()V` | ignored |
| `IsShowingAchievements`, `IsLoadedAchievements`, `IsAchievementUnlocked`, `IsExistAchievement` | `()Z`, `()Z`, `(Ljava/lang/String;)Z` ×2 | false |
| `NumAchievements`, `GetAchievementCurrentStep` | `()I`, `(Ljava/lang/String;)I` | 0 |
| `GetAchievementId` | `(I)Ljava/lang/String;` | `""` |
| `StartLocationCapture`, `StopLocationCapture` | `()V` | A capture finishes at once, unsuccessfully. |
| `IsUpdateLocation` | `()Z` | true after a capture was started (it has finished), else false |
| `IsSucceedLocation`, `IsRequestLocationPermission` | `()Z` | false |
| `GetLocationErrorCode` | `()I` | 1 after a capture, else 0 |
| `GetLocationX`, `GetLocationY` | `()D` | 0.0 |
| `OpenLocationSetting`, `OpenApplicationSettings`, `UnScheduleLocalNotification` | `()V` | ignored |

The exact values a real phone without Play Games or location returned aren't recorded anywhere we have. These are the natural "not available" answers of each signature: assumption (d).

The HTTP methods (`HttpRequest`, `GetStatusCode`, `GetHttpHeader`, `ReadHttpResponse`, `AbortHttpRequest`, `SetHttpUserAgent`, `CloseHttpRequest`, `SetHttpProxy`) are `http_370.cpp`'s: see "Networking".

The in-app billing methods (`CanPurchaseDevice`, `RequestProduct`, `PurchaseProduct`, `GetPurchaseProductResult`, `ConsumeProduct`, `ReverifyProduct`; the coin shop's store) are a local store that completes every purchase for nothing, in `java_370.cpp`'s `install_billing`: `docs/client-changes.md` "In-app billing" (the contract from the APK's `InAppBilling`).

### The imports (`hle_370.cpp`)
The undefined dynamic symbols (`readelf --dyn-syms -W`, `UND`) of 3.7.0 and the offline build differ by one: 3.7.0 imports `fmod`. It is bound to the host's `fmod`, which is exact IEEE, like bionic's. Every other 3.7.0 import is one the offline build has too, and the runtime binds all of them: the loader reports no unresolved import.

### The date and `service_stop_day` (`patch_370.cpp`)
soa-emu runs on the host's real date. The client would refuse it by itself: its master DB says when the service ended, `master_global.service_stop_day` = `2021/06/24 14:30:00`, and the client compares that with the device clock before it talks to any server. The APK's built-in master has the row, and the first boot reads that one. One native patch takes the check out (agent `e7-realtime`, 2026-10-01).

**Every reader of the row.** The key string `"service_stop_day"` (ELF 0x27652ac) has two references in `work/libSOA-3.7.0.so` (an `adrp`/`add` scan of `.text`), both passing it to `CParameterUtility::FindGlobalStringWithKey`. No code uses the key's id (0x25cf21e2) as an immediate or a literal; no other code reads `cbt_end` (2016/11/28) either.

| Site (ELF address) | What it does with the row |
|---|---|
| `CTitle::Setup` 0x1d83d9c–0x1d83ec8 | `str2time_t(value) <= CTimeUtility::NowTimeTrue()` (the device clock, without the server offset) sets `CTitle+0x91d`, "the service has ended"; then `pay_back_stop` (2022/03/15 23:59:59) `>= now` sets `+0x91e`, "refunds are open". `+0x91d` makes the title show the notice 「本サービスは2021/06/24に終了いたしました。…」 (with the refund lines while `+0x91e`) and "TAP TO START" open 「アプリの最新バージョンがリリースされています。アップデートをお願いします。」 instead of logging in. |
| `CPhase_Server::CPhase_Server` 0x17c3774–0x17c37f0 | stores `str2time_t(value)` at `+0x30`. The error handler of the phase's first request (the `std::function` lambda at 0x17c459c; 0x17c47b8–0x17c47cc) then checks `stop != 0 && stop <= NowTimeTrue()`: if so it ends the phase quietly (state 10, back to the title) instead of opening the communication-error dialog with its リトライ. |

Both read the value as a string and **skip their check when it is empty** (`cbz` on the string's size at 0x1d83df4 and 0x17c37c8): what the client does with a master that has no such row, as in service.

**The patch.** No function answers "has the service ended?" by itself: the check is inlined in both callers. The getter they share is small and whole: `CParameterUtility::FindGlobalStringWithKey(std::string const&)` (ELF 0x1716640, 0x58 bytes; 12 functions, 17 calls). soa-emu hooks it with a host function: for the key `service_stop_day` it returns `""` (24 zero bytes in x8's string, as the original's not-found path at 0x1716658 writes), and for every other key it runs the original guest code through a trampoline. So the check never runs, at both sites, on any date; every other key reads the master as before.
- **Mechanism:** the runtime's guest-function hook (`core/cpu.h`: `make_original_trampoline`, `hook_guest_function`; `runtime/README.md` "Guest function hooks"), the one the port's native replacements use. `main.cpp` installs it (`platform370::install_patches`) right after `load_library`, before `run_initializers`, so no JIT has translated the function yet. The two original entry instructions (`sub sp, sp, #0x20; stp x19, x30, [sp, #0x10]`) are checked first: another library isn't patched (warning).
- **Why the getter and not an instruction patch:** two inlined sites (three branches, two flag stores) would need instruction edits; the getter is one whole function, and its answer, "no such row", is the state the client already handles. It matches soa-server's data side: the master it serves drops the row (`apply_client_master`), and the port's in-process server drops it from the port's client master (`docs/client-changes.md` "Data overrides"). The patch covers what the server can't reach, the APK's built-in master.
- **The log** shows `patch: CParameterUtility::FindGlobalStringWithKey hooked at 0x1716640`, and each read: `patch: master_global.service_stop_day read (from 0x17c37a4)` (CPhase_Server), `(from 0x1d83dd0)` (CTitle::Setup).
- **Verified:** `emulator_boot.sh` (no server) on the real date: PASS with the patch (the 1003 dialog and its retry, as before); with `--no-patch` the title shows the service-end notice instead and the check FAILs, like the old `--device-clock host`.

**The rest of the client on a 2026 date.** Everything else dated is the server's: `GetServerTime` / `data.Time` give the client its offset (`CServerTime::FixTime`), about 0 now that both run on the real clock, and soa-server serves the master with its event, shop and campaign dates year-shifted to the current year (`docs/server-rules.md` "Events", "Two clocks"). `CTimeUtility::NowTimeTrue` (the clock without the offset) has two more callers, `CFriendMenu::CFriendMenu` and the `CPhase_Server` lambda above. The flows run on the real date are in "Checks".

**`--device-clock`** is now a test option: the guest's wall clock (`time`, `gettimeofday`, `clock_gettime` and `syscall(clock_gettime)` on `CLOCK_REALTIME`, `_COARSE` and `_ALARM`) runs at a fixed offset from the host's; the monotonic clocks are untouched. Its default, `host`, is offset 0. Before the patch the default was `2021-06-23 12:00:00`, a day before the service ended.

## Networking (step 5: `net_370.cpp`, `http_370.cpp`)
The client talks to two kinds of server, both through the platform layer:
- **The game server**: raw TCP (no TLS) to `production-game.so-ana.com:443`, through Bionic's `getaddrinfo` and `connect` (`docs/online-server.md` §2). The lobby is the same host, port 4001.
- **HTTP(S)**: the bridge POST and the downloader. The native client (`Aska::Yayoi::NativeHttpClient`) hands each request to Java, `jb.Aska.AskaActivity`'s HTTP methods.

### The address redirect (`net_370.cpp`)
Like a phone whose hosts file points the game's names at another machine:
- **Name lookups.** `getaddrinfo` / `gethostbyname` of `production-game.so-ana.com`, or of a `--map-host` name, resolve to `--server`'s host (or the `NAME=ADDR` address). Every other name goes to the runtime's thunk unchanged. The log shows `getaddrinfo(production-game.so-ana.com, ) -> 127.0.0.1 (mapped)`.
- **Connections.** `connect` to an address a mapped name resolved to (or `--server`'s / a `--map-host` literal address): port 443 becomes `--server`'s port; port 4001 becomes `--lobby` (when given). Other connections are unchanged. The log shows `connect(fd N): port 443 -> 127.0.0.1:44300 (redirected)`.
- **Bionic-vs-glibc fixes**, done in the override (the runtime's thunk passes these through as they are):
  - the hints' `ai_flags`: Bionic `AI_NUMERICSERV` 0x8 / `AI_ALL` 0x100 / `AI_ADDRCONFIG` 0x400 / `AI_V4MAPPED` 0x800 become glibc's 0x400 / 0x10 / 0x20 / 0x8 for the call, and back in the results (`AI_PASSIVE`, `AI_CANONNAME`, `AI_NUMERICHOST` agree; Bionic's `AI_V4MAPPED_CFG` has no glibc bit and is dropped);
  - the `EAI_*` results: glibc's negative codes become Bionic's positive ones (`EAI_NONAME` -2 → 8, `EAI_AGAIN` -3 → 2, ...).
  - `sockaddr_in` / `sockaddr_in6` and `hostent` have the same layout in both, as does everything else on the socket path (the runtime's `fd_set`, `FIONBIO`, `O_NONBLOCK`, errno).

**URLs can't carry a port.** The client's URI parser (`Aska::Yayoi::URI::Deserialize`, given a default port) keeps a URL's `:port` in the host name it resolves, so `http://127.0.0.1:44380/bridge` makes it look up `"127.0.0.1:44380"`, which fails (on a phone too: the service's URLs had no port). soa-emu logs a warning when it sees such a lookup. The server must hand out URLs on a mapped name without a port, and the HTTP client then sends them to `--http`. These are soa-server's defaults (`--bridge-url https://production-game.so-ana.com/bridge`, `--cdn-url http://production-game.so-ana.com`), so `soa-server --listen A --http B` and `soa-emu --server A --http B` work together as they are.

### The HTTP client (`http_370.cpp`)
A host HTTP/1.1 client behind the `AskaActivity` methods the native side calls. Their semantics come from `NativeHttpClient::_doRequest` (3.7.0 @026a4f40, `tools/decomp.sh --v370`). It runs one request at a time on its network thread, blocking:

| Method | Signature | What the native side does with it | soa-emu |
|---|---|---|---|
| `SetHttpUserAgent` | `(Ljava/lang/String;)Ljava/lang/Boolean;` | called first when a user agent is set | kept for the `User-Agent` header (until then `Dalvik/2.1.0 (Linux; U; Android 9)`, (d)) |
| `HttpRequest` | `(Ljava/lang/String;ILjava/lang/String;Z)I` | the full URL (a GET's parameters appended after `?`), the URI's port, the POST content (`MakeParamString`: SetContent's bytes), `true` for POST; a result < 1 is "unexpected error" | connects, sends the request (`Connection: close`; a POST with `Content-Type: application/x-www-form-urlencoded`, HttpURLConnection's default, (d)), reads the response head; returns 1, or 0 on failure |
| `GetHttpHeader` | `()Ljava/lang/String;` | parsed by `HttpProtocol::ParseHeader`, which starts the native parser in its header-field state: the string must be the `Name: value` lines only, `\r\n`-terminated, **without the status line** (a line without `:` ends the header); null = "response header is nothing" | the response's header fields, without `Transfer-Encoding` / `Connection`, with `Content-Length` = the body's length |
| `GetStatusCode` | `()I` | stored as the response's status | the status line's code |
| `ReadHttpResponse` | `([B)I` | in a loop: `n` ≥ 0 bytes in the buffer go to `ParseMessageBody`; < 0 = the end of the body. The buffer is `GetTcpReceiveSize()` bytes | the next part of the body, streamed from the connection for a `Content-Length` body (bundles run to hundreds of MB); a chunked or connection-delimited body is read whole in `HttpRequest` and decoded; -1 at the end |
| `AbortHttpRequest` | `()Ljava/lang/Boolean;` | called when the request was cancelled while reading | closes the connection |
| `CloseHttpRequest`, `SetHttpProxy` | `()V`, `(ILjava/lang/String;)V` | | close; the proxy is ignored (logged) |

**Where requests go.** A URL whose host is mapped goes to `--http` as plain HTTP, also for `https://` (soa-server has no TLS). `https://` to `--server`'s or `--http`'s own address is plain HTTP too. Other `http://` URLs are fetched as they are; other `https://` URLs fail with a warning (no TLS here; the original services are gone). No `Accept-Encoding` is sent and `Content-Encoding` is passed through: the native side gunzips by itself where it expects gzip (the bridge reply).

Each request is logged: `I/http: GET http://production-game.so-ana.com/download/1472/Android/B/1115774b/b9a9e011.bin -> 127.0.0.1:44380: 200, 36216928 bytes`.

### What an end-to-end run does (2026-10-01)
`emulator/scripts/emulator_session.sh` (below) against `soa-server`. (These runs were on the device clock of the time, 2021-06-23; since agent `e7-realtime` the same flows run on the real date, "Checks".)
1. Title: `NoLoginStart` → `NoLoginStartRes` (sent by the title before "TAP TO START" shows).
2. TAP TO START: `StartBridge` → `ResultStart` (the bridge URL) → `POST https://production-game.so-ana.com/bridge` → `UpdateSession` → `ResultUpdateSession` → `Login` → `LoginResult` + `GetPlayerRes`.
3. 「Episodeデータ管理」 (episode data deleted by a cache clear) → 決定 → the downloader reads `manifest/etc2/hi/version_latest_{Bulk,Individual}.{version,bin}`.
4. 「ゲームデータをダウンロードをします … 必要容量:3138MB」 → ダウンロード: 1,028 bundles `B/…` (3.1 GB; including the served master's bundle `B/1115774b/b9a9e011.bin`), in about 3 minutes.
5. 「ゲームデータのダウンロードを完了致しました。」 → 完了 → **home**: the notice board (an empty web view: `ShowWebView` isn't supported in soa-emu), then the LOGIN BONUS popup over the home screen of the seeded player (Fayt, rank 87).

Two server gaps showed up on the way and were fixed in soa-server (`docs/server-rules.md` "soa-server: the wire layer"):
- `CApiNotify::OnLoginResult` never ends the login request, so a `LoginResult` alone left the client waiting until the 60 s API watchdog failed it with **1002**. soa-server now follows it with a `GetPlayerRes`, as the developers' `FakeApiCaller::Login` does.
- With no `a_ver` in the replies, `CErrorHandlerWrap::CallBackCore` opened the "update the app" dialog after the login. soa-server's Login now carries `a_ver` = `master_global.a_ver_android`.

**After home (step 6, agent `e6-end2end`).** The same script goes on, and a `--new-player` run plays the entry flow:
6. The login popups: the notice board's 閉じる, the LOGIN BONUS's 閉じる (`flowctl.py login-popups`, which reads soa-emu's `ShowWebView` lines as it reads soa's).
7. ミッション → `GetMissionList` → planet Mere → 1-05 (`mf01_001`) → single play → no rental → party 1 → 決定 → `MissionStart` → the battle (the party's AI wins it: `mission_time` 2.6-9.3 s in the runs) → `MissionEnd` with its battle log (`MissionEnd-battle_log.msgp` in the packet log; soa-server decodes `mission_time`, the defeated enemies and the evaluations, and its MissionEnd log shows the same time) → the Mission Result pages → the mission map (1-05 CLEAR, mc01_030 New) → ホーム.
8. ガチャ → `GetGachaInData` → the first recommended banner → 10連ガチャ → 決定 → `SaleGacha` → the summon, the reveals, the result list → ホーム. 紋章石 300,000 → 297,500 in the server's state, ten draws recorded.
9. `--new-player`: `Login` → ProtocolError **19001** → the terms (同意する) → the name (the keyboard; `text:`) → 決定 → `CreatePlayer` → `Login` (now with the CDN keys) → the download dialog (no episode dialog on a new phone) → the 3.1 GB download → 完了 → the opening scene (`MissionTalk` / `EndMissionTalk`, `UpdateTutorial` 1-3), the battle tutorial `ms00_001` (`MissionStart` / `MissionEnd` with the three NPCs), the mission-menu step (`UpdateTutorial` 4-6), home (`UpdateTutorial` 7) and the home tutorial (`UpdateTutorial` 9).

Every request after the login goes out on a **new connection** (the client closes its game connection after each reply) **without a new bridge**: the client stays bridged while logged in and sends the request encrypted with the session key. The gaps this showed were all fixed in soa-server (`docs/server-rules.md` "soa-server: the wire layer", agent `e6-end2end`):
- **`LoggedIn` was false after the login**, so the client refused every later API itself with **1002** (`DisconnectDialog(-0x3b3)`, nothing sent; the first one is ミッション's `GetMissionList`). `CApiNotify::LoggedIn` reads the legacy `CParameterPlayer`, which `OnLoginResult` fills from a **top-level `Player`** map (`{Id, ...}`) of the LoginResult body, not from `data`. soa-server's LoginResult now carries it.
- **The reconnect had no session:** soa-server refused it (1002) and expected an `UpdateSession` first. It now binds such a connection to the session whose key decrypts the request.
- **soa-server's mission select listed no missions:** the story campaign module (`ActiveMissionList`, the mission progress) was only wired into soa's FakeApiCaller route. soa-server now calls it the same way, and answers `EndMissionTalk` (3.7.0's end of a story scene) as soa does.
- **Every ProtocolError crashed soa-emu** (below, "Error replies and the tagged-address crash"); soa-server now closes the connection after one. The cause, TBI, has since been fixed in the runtime.
- **CreatePlayer opened the "update the app" dialog:** `CreatePlayerRes` now carries `a_ver` too. The download after CreatePlayer needs nothing more: the Login that follows carries the CDN keys (the S3 open question).

### The lost first request (1 run in 8-16, fixed): a JNI reference read as a boolean
**Symptom (before the fix).** On a fresh data dir the title's first connection opens but `NoLoginStart` is never sent; the title ends in the 1003 dialog, and its リトライ sends it (the session script taps it).

**Cause (agent `e6-end2end`, 2026-10-01): not the network.** `NetworkApiCaller::NoLoginStart` calls `BAS::GetUUIDConsistently` (3.7.0 @01f3509c). On a fresh data dir no UUID is stored yet, so it creates one and saves it with `LocalKVS::SetBinaryAndroid` (@02028328), which calls the Java method `SetSharedPreferences(String,String,byte[])`, returning a `java.lang.Boolean`. The client then tests **the low byte of the returned reference**, not the Boolean's value:
```
ELF 0x1f28470  tbnz x21, #63, ...   ; the call failed
ELF 0x1f28474  ldrb w8, [sp, #8]    ; low byte of the 8-byte jobject
ELF 0x1f28478  cbnz w8, ok
ELF 0x1f2847c  mov  x8, #-1         ; "false": status -1
```
On a phone a local reference always has a non-zero low byte (ART's reference-kind tag bits), so the bug never shows. The runtime's JNI references are raw `Object*` (`runtime/src/jni/java_android.cpp`, `R(Object*)`), and `Vm::boolean()` allocates each Boolean with `new`: a 16-byte-aligned pointer has a zero low byte about 1 time in 16. The save then counts as failed, the UUID comes back null and `NoLoginStart` goes to `DisconnectDialog` without sending; the Java side did store the UUID, so the retry reads it and sends.

**Evidence.** Socket traces (thread ids, `select` sets, `getsockopt`, `send`) of good and bad runs are identical up to `SO_ERROR` = 0; in a bad run the client never calls `TARPCPeer::RPCSend`. A run with hooks on the `NoLoginStart` path caught `GetUUIDConsistently` returning null, followed by `DisconnectDialog`. Forcing the reference's low byte to zero failed 3 runs of 3, forcing it non-zero passed 16 of 16; unmodified, 1 of 13 (untraced) and 1 of 10 (traced) failed. The socket layer was ruled out: `select` / `connect` / `send` / `getsockopt` pass through to the host, errno is per thread, the non-blocking flags are translated, the atomics are CAS-backed, and the client's queues are mutex-protected.

**Fixed in the runtime (agent `r2-runtime-fixes`, 2026-10-01).** Every handle the JNI layer gives the guest now has a non-zero low byte, as ART's do: `Object` (strings, arrays, classes, instances, boxes), `Method` (jmethodID) and `Field` (jfieldID) are allocated through `TaggedAlloc` (`runtime/src/jni/jvm.h`), at 8 (mod 16) past a 16-aligned block (`runtime/README.md` "Platform fidelity"). This is a platform-fidelity fix, not a client change; `soa` gets it too.
- **Tests:** the runtime test `jni/references-low-byte` checks 256 of each handle kind, including `SetSharedPreferences`' Boolean read the guest's way. With the offset removed it finds 383 of 6,656 handles with a zero low byte.
- **Sessions:** `emulator_session.sh` with `NO_RETRY=1` (no リトライ fallback) sent `NoLoginStart` by itself at 22-24 s in every run, each with a new UUID:
  - 21 seeded runs of 21: 9 full sessions (1 on a fresh phone, 8 with `FRESH_KVS=1` on its data) and 12 `SESSION_PLAY=0` runs with `FRESH_KVS=1`;
  - 2 `--new-player` runs on a fresh phone.

  Before the fix, about 1 run in 8-16 lost the request. At 1 in 16, 23 clean runs in a row had a probability of (15/16)^23 ≈ 0.23. The deterministic evidence is the test, which reads every handle.

The fallback stays in the script (without `NO_RETRY=1`) for runs that meet a real network error.

### Error replies and the tagged-address crash (fixed)
**Symptom (before the fix).** Any ProtocolError (Login's 19001 for a new player, a refused request) crashed soa-emu a few seconds later: `Unhandled SIGSEGV`, host frame `CpuCallbacks::MemoryRead64`, fault address `(nil)`, guest pc in `Aska::Yayoi::Socket::Poll` (3.7.0 ELF 0x220dd98) just after its `select`.

**Cause: Top Byte Ignore, which the JIT didn't emulate.** The client handles the error on its main thread and closes the socket there (`Socket::Close` @0x220d61c: `close(fd)`, then stores `fd = -1`), while its network thread is inside `Socket::Poll`, which re-reads the fd after `select` returns and indexes the returned `fd_set` with it (`ldrsw x8, [x20]; lsr x8, x8, #3; and x8, x8, #0x1ffffffffffffff8; ldr x9, [x21, x8]`). With `fd = -1` the address is `x21 + 0x1ffffffffffffff8`. On an ARM64 phone Linux enables TBI for user space, bits 56-63 of a data address are ignored, and the load reads the stack word at `x21 - 8`: harmless. Under dynarmic the address is used as it is: a non-canonical x86-64 address (#GP, reported as fault address 0). The race is real on the phone too; only its outcome differs.

**The first workaround (server side).** soa-server closes the connection after a ProtocolError (`docs/server-rules.md` "A ProtocolError ends the connection"): the network thread then sees the end of the connection and closes the socket itself, before the main thread does. New-player Login with 19001: 0 crashes in 3 runs (2 of 3, and 2 of 2, without).

**Fixed in the runtime (agent `r2-runtime-fixes`, 2026-10-01): TBI is emulated.** The JIT's memory callbacks clear the top byte of every data address: reads, writes, exclusive reads and writes, CAS and DC ZVA (`runtime/src/core/cpu.cpp` `CpuCallbacks::tbi`; `runtime/README.md` "Platform fidelity"). Instruction fetches are unchanged.
- **Why the callbacks are enough:** dynarmic's fastmem faults on the tagged address, and its signal handler, keyed on the host RIP, falls back to these callbacks. That is why the crash's host frame was `MemoryRead64`. The fastmem path is unchanged.
- **Test:** the runtime test `cpu/tbi-tagged-data-addresses` runs guest loads, stores and exclusives through tagged addresses, including the 0x20 tag of `Poll`'s address. Without the mask it crashes as soa-emu did.
- **Sessions:** with soa-server's close-after-ProtocolError turned off (the hidden `--keep-open-after-error`; `SERVER_ARGS=--keep-open-after-error emulator_session.sh --new-player`), 3 `--new-player` runs of 3 passed through the 19001 to the end of the tutorial with no crash. In each, the ProtocolError's connection was left open. The server test `net/close-after-refusal` checks the switch itself. Before the fix, 2 of 3 runs crashed without the close.

soa-server still closes the connection after a ProtocolError by default. That is a server choice (`docs/server-rules.md`), and soa-emu no longer depends on it.

## Status (2026-10-01)
**Phase 0 / step 2 is done.** The unmodified 3.7.0 client boots to its network path under pure JIT, with no server. `emulator/scripts/emulator_boot.sh` checks it; it prints PASS or FAIL.

**What happens:**
1. The client runs splash → caution screen → title phase.
2. The title phase sends `NoLoginStart` at once (`docs/api.md`; an `SOA_TRACE` run stopped inside `NetworkApiCaller::NoLoginStart` at that moment). It resolves `production-game.so-ana.com`, which no longer exists. (Since step 5, soa-emu maps the name to `--server`; with no server listening there the connection is refused instead, with the same outcome.)
3. That fails, and the communication-error dialog opens: 「通信エラーが発生しました。電波の良い場所でプレイしてください。エラー:1003」, with リトライ.
4. Retry tries again and fails the same way (it resolves the name again; once a lookup succeeded, it reconnects to the address it has).

**Why 1003, not 1002.** The plan expected the title, then a tap, then 1002. In practice:
- With the client in service, the title connects by itself before "TAP TO START" is ever shown.
- An unresolvable host (or a refused connection) is a disconnect (`CApiNotify::OnDisconnect` → 1003; `docs/online-server.md` "Errors and status codes").
- A real phone offline, or today, would show the same.

**With `--no-patch` on the real date** (before the patch: `--device-clock host`): the title does show (Ver.3.7.0, the service-end notice), because `CPhase_Server`'s error handler ends the phase quietly once the service has ended. Tapping gives the update dialog.

**No warnings.** There are no JVM or HLE warnings up to here: no `jni: unknown method`, no unresolved import. The only warnings are the runtime's usual refused `popen("getprop …")`, and no audio device in headless runs.

**Assets.** `--download-dir` wasn't needed: the 478-asset APK has everything up to the title.

**Timings** (pure JIT, this machine; `emulator_boot.sh`):

| Step | Time |
|---|---|
| Library load and initialisers | 0.2 s |
| Network path (the title's `NoLoginStart`) | about 18 s after start, most of it the timed splash screens |
| Error dialog | under 1 s later |
| Retry, back to the dialog | about 2 s |
| With `--no-patch`: the title visible | about 20 s after start |

The title runs at 60 fps.

**Step 5 (the network glue) is done:** with `soa-server` the client reaches home (above, "Networking").

**Step 6 (end to end) is done (agent `e6-end2end`, 2026-10-01):** the unmodified 3.7.0 client plays the seeded player's login popups, a campaign battle (1-05) and a 10-draw, and a new player's whole entry flow and tutorial, against `soa-server` (above, "After home"; `emulator_session.sh`, "Checks"). The server DB after the seeded flow equals the port's (`--server inproc`) apart from the documented differences ("Parity"). The two runtime defects it found (the JNI reference low byte, TBI) are fixed in `runtime/` (agent `r2-runtime-fixes`; "The lost first request", "Error replies and the tagged-address crash").

## Parity with the in-process server (step 6)
The same seeded flow both ways, then the two server databases compared (agent `e6-end2end`, 2026-10-01):
- **Port:** `port/scripts/restore_session.sh build/port/soa OUT TMP --campaign-seed mf01_001` (login, popups, mf01_001 through the `mission:` / `phase:` route, the results, the 10-draw of the first recommended banner, home; `--seed-rng 1`).
- **Emulator:** `emulator/scripts/emulator_session.sh` (the same steps through the real UI: ミッション → planet Mere → 1-05, the same banner; `--seed-rng 1 --campaign-seed mf01_001`).
- **Compared:** `tools/server_state.py` of both (`state-3-after-gacha.txt`), and every table of both `server.sqlite3` row by row with the time columns masked, plus `server_campaign.txt` (the campaign's progress then; in the state DB since PLAN-schema S12).

**Result: the same state.** `server_state.py`'s summaries are identical: rank 87 with EXP 1072, FOL 1,675,965, stamina 132, coins 300,000 → 297,500, party 1's four members at EXP 150, the drops (`item_W99St_01`, `item_W02Ro_04`, `item_W17Bo_10`, three chip stacks), mf01_001 cleared once, mc01_030 unlocked, the ten draws (same roles, same ranks, same uids), four presents. Every table matches row for row except:

| Difference | Why | Kind |
|---|---|---|
| `meta.seed`: the path of the seed save | the two runs read `samples/Game.xml` from different checkouts (the worktree's and the main one) | expected (environment) |
| `wire_device`: one row in the emulator's DB, none in the port's | soa-server records the device UUID the bridge saw; the port's in-process server has no bridge (`docs/server-rules.md` "Device → player") | expected (documented emulator-only rule) |
| the masked times (`*_at`, `at`, `stamina_at`, login bonus days) | wall-clock | expected (time) |

The requests differ, not the state: the emulator also sends `GetServerTime` (phase changes), `GetMissionList` (twice) and its own `GetGachaInData`, and it reconnects per request; none of them changes the state. With `--seed-rng 1` both modes draw the same gacha results and drops, so the randomness doesn't show either. The new-player flow is compared in "Tutorial parity" below.

Gaps found on the way (all fixed in soa-server; "After home" above): `LoggedIn` (the LoginResult's root `Player`), the reconnect, the campaign data and `EndMissionTalk` (soa-server lacked soa's campaign hooks: before the fix its mission select was empty, a real gap of the emulator mode), the crash on error replies, `a_ver` with CreatePlayer.

## Tutorial parity (agent `t1-tutorial-parity`, 2026-10-01)
The new-player flow from a fresh start, both ways, compared step by step:
- **Port:** `port/scripts/tutorial_session.sh build/port/soa OUT TMP`: `soa`, an empty data dir, `--new-player`.
- **Emulator:** `emulator/scripts/emulator_session.sh --new-player`: the unmodified 3.7.0 client against `soa-server --new-player`, a new phone (the 3.1 GB download included).
- **The same milestones:** both scripts end with `tools/compare_tutorial.py check {port|emu} OUT`, which reads **`tests/tutorial_milestones.txt`**: the 22 game requests both must send in order (normalized: the arguments both transports carry), and the three party members' stats in the battle tutorial. Both print `PASS  tutorial milestones`.
- **The report:** `tools/compare_tutorial.py compare PORT_OUT EMU_OUT --montage DIR` compares two runs: the request sequences (every one-sided request classified), the battle (party, enemies, mission time, every hit's damage: both runs trace `CCharacterObject::OnDamage` with `SOA_TRACE`), the screenshots (an RMSE per milestone pair and a montage, the per-round tutorial frames aligned) and both `server.sqlite3` (every table, row by row, times masked). It ends with `PASS parity` when no difference is left unexplained.

**The flow both take** (screens and requests, identical in order): title → `NoLoginStart` → TAP TO START → `Login` → 19001 → the terms (同意する) → the name (the keyboard) → `CreatePlayer("Claire")` → `Login` → (the emulator only: the download dialogs and the 3.1 GB download) → the opening scene mc00_010 (`MissionTalk`, its choices, `EndMissionTalk`) → `UpdateTutorial(1)` → mc00_015 → `UpdateTutorial(2)` → the battle tutorial ms00_001: two stages, the three NPCs, the tutorial dialogs (move, attack, skills, RUSH) → `MissionStart` / `MissionEnd` → `UpdateTutorial(3)` → mc00_025 → `UpdateTutorial(4)` → planet Mere's map, 1-01 (ここをタップ) → `UpdateTutorial(5)` → the story of 1-01 (`MissionTalk` mc01_010, skipped) → `UpdateTutorial(6)` → "summoned companions" → ホーム → `UpdateTutorial(7)` → the home tutorial (プレゼント, ガチャ) → `UpdateTutorial(9)` → the notice board. Up to the notice board, no popup or dialog appears in one run and not the other.

**Found and fixed: the battle tutorial's party (server side).** soa asks the client's own NPC model (`MasterMissionNpcModel::CalculateParameter`) for the stats of the three NPCs; soa-server has no client to ask and sent the roster rule, without the NPCs' weapons, weapon factors and talents. So the 3.7.0 client fought the tutorial with Fidel's attack 1,152 instead of 1,281, the gun NPC's 1,069 / 762 instead of 1,208 / 898 and the rod NPC's intelligence 1,434 instead of 2,045 (its MissionEnd battle log's `PlayerCharacter`), its hits were 20-45 % weaker and the battle about 30 % longer. soa-server now computes the same model from the master data, `rules::npc_status` (`server/src/master/npc_status.cpp`; `docs/server-rules.md` "Tutorial battle"), equal to the client's for all 822 `master_mission_npc` rows (port test `server/npc-status-master`). After the fix both runs fight with the same stats, the port's 7781/1281/755/960/551/397, 6859/1208/898/832/616/451, 5989/749/2045/653/516/407.

**Re-checked: the party-stats FAIL after the platform370 merge (agent `f2-tutorial-stats`, 2026-10-01) was a stale `soa-server`, not the spec.** Two `--new-player` runs on `linux-port` (before and after `3a1a062`) failed the three `battle party member` lines with the old numbers (attack 1,152 / 1,069, intelligence 762 / 1,434). Their `MissionStartRes` (`packets/16-MissionStartRes.msgp`) already carried those numbers, `weapon_master_item_id` 0 and the roster rule's `weapon_id`, i.e. `rules::npc_status` never ran; and the client's MissionEnd battle log repeated them exactly, so **the 3.7.0 client fights with `BattleParameter.PlayerCharacter` as sent** (it doesn't recompute the NPCs; label (b)). The battle itself follows the sent numbers, not only the log: with the roster numbers the emulator's hits were 20-45 % weaker than the port's and the battle about 30 % longer; with the model's, the strongest hit is 3,440 vs the port's 3,430 and 110 of 111 emulator hits are a port hit × a cancel level. Their `server.log`s name the main checkout's `data/gacha_pools.sqlite3`, which soa-server finds upwards from its own executable: the runs used the main checkout's `build/server/soa-server`, built at 10:23, before `port/t1-tutorial-parity` (with `rules::npc_status`) was merged at 10:35; that binary has no `rules::npc_status` symbol. With a current build, the same script passes: soa-server logs `MissionStart NPC <id>: master-data model applied (attack 1281)` for each NPC, the battle log has 7781/1281/755/960/551/397, 6859/1208/898/832/616/451, 5989/749/2045/653/516/407, and `tools/compare_tutorial.py compare` reports `unexplained differences: 0`. The spec `tests/tutorial_milestones.txt` is unchanged: its values are the 3.7.0 client's own `MasterMissionNpcModel::CalculateParameter` (port test `server/npc-status-master`, all 822 rows). `emulator_session.sh` now prints which binaries it runs and warns when `soa-server` is older than the checkout's `server/` sources; the server test `server/npc-status-tutorial-missionstart` checks the MissionStart response itself (not only the library function).

**The report of the two runs after the fix** (`tutorial_session.sh` PASS, `emulator_session.sh --new-player` PASS, 25 milestones each):

| Compared | Result |
|---|---|
| Milestones (`tests/tutorial_milestones.txt`) | 22/22 requests in order, 3/3 party members, both |
| Behavioural requests | identical: the same 22 requests with the same arguments, in the same order |
| One-sided requests | emulator: `StartBridge` ×2, `UpdateSession` ×2 (the bridge; soa's server is in-process), `GetMissionList` ×2 (the emulator's mission menu asked for the list, the then-offline port's didn't; with the in-process server the same `ActiveMissionList` comes with every response; read-only), `GetServerTime` ×2 in both, at different steps (`CPhase_SyncServerTime`: the 10-minute bucket) |
| Arguments not compared | `NoLoginStart`'s version (the build; it differed while the port ran the offline build), `Login`'s and `CreatePlayer`'s UUIDs (soa's route doesn't capture them), `EndMissionTalk`'s type / flag / world-map id (soa delivers it from `CEventScenario::Exit` with the mission id, the only one the server reads; `docs/client-changes.md`), `MissionEnd`'s battle log (soa reads it in-process) |
| Battle party | identical (above) |
| Enemies | the same master rows (stage 1 `cm128_b01c` ×2 + `cm142_b01d`, stage 2 `cm142_b01d`; level 120 from `recommend_level`): the emulator's battle log lists 2 + 2 of the two kinds, the port's damage log their stats (HP 11,504 / 32,559) |
| Damage (`OnDamage`) | strongest hit (the special attack) 3,435 vs 3,436; 116 of the emulator's 118 hits are one of the port's hits (final / cancel) at a cancel level 1 / 1.5 / 2 (3 %). The hit mix differs with the taps' timing (96 vs 118 hits, mission time 106 s vs 134 s): which attacks, which combo step. The inputs are equal: party stats, `master_enemy_*` rows (identical in the 3.7.0 and offline DBs), and no battle-calc function changed between 3.7.0 and the offline build (`work/verdiff/changed.tsv`) |
| Screens | terms 0.009, name 0.008, opening 0.10 (text animation), mission map 0.011, companions 0.013, home tutorial 0.010 / 0.010: the same. 34 of the port's 51 tutorial-round frames have an emulator frame within 0.05 (45×80 grey); the rest are the battle, where the frames depend on timing |
| Server state | every table equal, row for row, except `wire_device` (the emulator's bridge device; expected) and the masked player id / search id (CHash32 of the device UUID and the name) and times |

**Expected screen differences (explained, not fixed):**
- **The title** (RMSE 0.72, at the time; gone since the port runs the 3.7.0 client): the port showed the offline build's title: its APK's `UI/etc2/title_ep3.csf` / `title_logo.csf` (the offline title art; the 3.7.0 APK and the download have the "The Leash Code" art), its version string, and its `CTitle::Setup` without 3.7.0's ムービー再生 / ゲームデータ引き継ぎ / キャッシュクリア / お知らせ buttons.
- **The notice board after the tutorial** (0.19): soa shows the local server's page (`native/ui/webview_local.cpp`); soa-emu has no web view, so the board is empty.
- **The download** (emulator only): soa reads the download tree directly.

## Checks

```sh
emulator/scripts/emulator_boot.sh [build/emulator/soa-emu] [out-dir] [extra soa-emu args]
```

The script:
1. builds nothing;
2. runs `soa-emu --headless` in a scratch data dir;
3. waits for the client's server lookup and the error dialog (detected from a screenshot), then taps リトライ and waits for both again;
4. prints PASS or FAIL;
5. kills only the process it started, and keeps the log and the screenshots in the out dir.

```sh
emulator/scripts/emulator_session.sh [--new-player] [soa-emu] [soa-server] [out-dir]
```

The end-to-end session ("What an end-to-end run does"). It:
1. builds nothing; picks two free ports;
2. starts `soa-server` with its own scratch state, `--log-packets`, the CDN from `work/download-3.7.0`, `--seed-rng 1`, and `--campaign-seed mf01_001` (so the campaign's 1-05, restore_session.sh's battle, is open on the mission map) or `--new-player`; its default bridge / CDN URLs are on `production-game.so-ana.com`; then `soa-emu --headless` pointed at it;
3. drives the client with `control/soactl.py` (taps and screenshots: soa-emu has no `phase:` / `call:` commands, so the taps are the port's restore / campaign / newplayer sessions', at the same 729x1296 window), resending a tap until its effect shows in a log;
4. prints PASS or FAIL per milestone, from soa-server's packet log, soa-emu's log, the screenshots and the server's state DB (`tools/server_state.py`, dumped to `state-*.txt`):
   - seeded: NoLoginStart, StartBridge, the bridge POST, UpdateSession, Login and its GetPlayerRes, the manifests, the bundle download, the master bundle, home, the login popups, GetMissionList, MissionStart, MissionEnd, the battle log as the server decoded it (`mission_time` = the server's, enemies, evaluations), mf01_001 cleared, the results back to the map, GetGachaInData, SaleGacha, coins debited, ten draws recorded;
   - `--new-player`: Login → 19001, terms → the keyboard, CreatePlayer with the name, the Login with the CDN keys, the download, the opening scene, `UpdateTutorial` 1-3, the battle tutorial's MissionStart / MissionEnd, `UpdateTutorial` 4, 6, 7, 9, the new player in the server's state, and the milestones of `tests/tutorial_milestones.txt` ("Tutorial parity");
   - and FAIL if soa-emu crashed or a ProtocolError was sent (other than the new player's 19001);
5. kills only the processes it started, keeps the logs, the packet log, the screenshots and the state dumps, and deletes the emulated phone's 3 GB download unless `KEEP_DATA=1`.

A seeded run takes about 7 minutes, a new-player run about 14 (the download is about 3 of them, the tutorial about 9). Without `EMU_DATA`, `OUT/emu` is linked from the shared pre-downloaded phone `work/phone-3.7.0` when it is built (`scripts/make-phone-370.sh`; hard links plus copies of the files the client writes in place, under a second; `port/README.md` "The shared pre-downloaded phone") and the download steps are skipped; `SOA_PHONE=none` runs the full download on an empty phone (the downloader's test), `SOA_PHONE=DIR` starts from that phone (linked if stamped, else copied). `EMU_DATA=DIR` runs on that emulated phone itself, in place (a `KEEP_DATA=1` run's `OUT/emu`; never deleted) and skips the download; `SESSION_PLAY=0` stops the seeded run at home.
- `NO_RETRY=1` turns off the リトライ fallback for the title's first request, so a lost `NoLoginStart` is a FAIL.
- `FRESH_KVS=1` deletes the phone's local KVS (`data/shared_prefs/Aska.xml`: version, crc and the device UUID) first. With `EMU_DATA`, a run then creates a new UUID, as a fresh phone does, without downloading again.
- `SERVER_ARGS` adds soa-server arguments, e.g. `--keep-open-after-error`.

```sh
EMU_DATA=<pre-downloaded phone> emulator/scripts/standin_fetch_test.sh [soa-emu] [soa-server] [out-dir]
```

Does the client fetch the stand-in assets (`standin-assets/`, server/README.md "CDN") from soa-server's CDN? Two runs in parallel, `--standin-assets standin-assets/` and `--standin-assets off` (the negative control), each on a copy of `EMU_DATA` (a stamped shared phone such as `work/phone-3.7.0` is hard-linked, `scripts/shared-phone.sh`) with the stand-ins removed (their files and their entries in the phone's `data/files/download/version.bin`; without `EMU_DATA` the whole 3 GB is downloaded). It checks the served version.bin and manifests (curl, decoded), the client's data check → download dialog → home, soa-server's `I/net: http GET` lines for the `I/5374616e/` / `B/5374616e/` bundles, and the six files in `data/files/download/Image/etc2/` byte-identical to `standin-assets/` (`cmp`; the client stores each member as the whole `.aif`); off: nothing listed, fetched or stored. About 70 s. 2026-10-01: PASS (on: 6 GETs of the Individual bundles `I/5374616e/<hash>.bin`, all 200, 6 files identical; off: no download, nothing fetched). 2026-10-04: an empty phone's Episode data dialog (Episodeデータ管理) is answered (決定): the data-check wait counts only the client's own GETs (it had matched the script's own curl of the manifests, so on an empty phone the dialog was never answered and no run without `EMU_DATA` had passed); PASS on and off with a full download (1,028 / 1,027 bundle GETs) and with `EMU_DATA=work/phone-3.7.0`.

```sh
emulator/scripts/lang_fetch_test.sh [soa-emu] [soa-server] [out-dir]   # EN_TABLE, EMU_DATA, EMU_LANG, KEEP_DATA
```

Does the unmodified client fetch the English master (`sqlite/basmaster-en.sqlite3`, docs/server-rules.md#english) from soa-server's CDN only? One run of `soa-server --english` (the table `data/english/master-en.tsv`, or `EN_TABLE`) and soa-emu on the shared phone `work/phone-3.7.0` (hard-linked, the `-en` entry removed from its version.bin): the served version.bin entry (encType 2, its Individual bundle `I/5374616e/<CHash32>.bin`), the client's data check → download → home, the 200 GET of that bundle in soa-server's log, the stored file byte-identical to the served one; `OUT/home.png`, `home2.png`. soa-emu gets `--lang en` when it has the option (`EMU_LANG`), and then the home shows the English master's text. About 3 min. 2026-10-07 (agent `en-server`, llvmpipe, soa-emu without `--lang`): PASS: `I/5374616e/1bc76693.bin` fetched (35.9 MB, 200) and stored byte for byte, the home Japanese (the client doesn't ask for `-en` files without the switch).

`emulator_boot.sh` points `--server` at a free port, so it checks the no-server path whatever else runs.

**On the real date (agent `e7-realtime`, 2026-10-01, default `--device-clock host`, the native patch on):**
- `emulator_boot.sh`: PASS (network path 19.3 s, the 1003 dialog, its retry). The log shows the patch answering `CPhase_Server`'s read (`from 0x17c37a4`). With `--no-patch`: FAIL, as expected: the title with the service-end notice instead of the dialog.
- `emulator_session.sh` (seeded): PASS, every milestone: the in-service title (no notice; both reads, `from 0x17c37a4` and `from 0x1d83dd0`, answered `""`), login, the 3.1 GB download, home, the login popups (notice, LOGIN BONUS ×1), 1-05 with its battle log (`mission_time` 8,220 ms, 8 enemies), mf01_001 cleared, the 10-draw with coins 300,000 → 297,500; 13 game requests, 1,032 HTTP GETs, 0 warnings. soa-server moved the client's dated event tables by +7 years (event calendar 2019-10-01 for the clock 2026-10-01).
- `emulator_session.sh --new-player`: PASS, every milestone: 19001 → terms → name → CreatePlayer → Login with the CDN keys → the download → the opening scene → `UpdateTutorial` 1-3, the battle tutorial, `UpdateTutorial` 4, 6, 7, 9 (cleared at 836 s), the new player in the server's state.

`emulator_session.sh` ignores empty repo files (a `sqlite3 data/basmaster-3.7.0.sqlite3` in a worktree creates an empty one, which hid the main checkout's master: the server then served an empty master, no `a_ver`, and the client asked to update the app after the login).

### Summer demonstration (`summer_demo.sh`)

```sh
emulator/scripts/summer_demo.sh [--watch] [--clock "YYYY-MM-DD HH:MM:SS"|host] [OUT]
```

A screenshot tour of the unmodified client with the summer events on (agent `summer-demo`, 2026-10-01): `soa-server --enable-events` (the default keywords `水着,夏,サマー,!福袋`, `docs/server-rules.md` "Enabling events by keyword"), a fresh state seeded from `data/saves/seed/Game.xml`, `--seed-rng 1`, and both clocks fixed at 2026-10-01 12:00:00 by default (the event list's rows and the draws are then the same every run; `--clock host` uses the real date). It plays:
1. **launch:** boot, title, TAP TO START → Login, the 3 GB download, the notice board and LOGIN BONUS, home;
2. **a summer event:** イベント → the 水着イベント2020 board (星の海と夢の渚, `event_sww2020_93`; the row is found by its beach and its first story) → the story mc99_565 (skipped) → the battle it unlocks, me99_1054 ビーチスポーツ？【初級】 (single play, no rental, party 1; the board's other open battle, me99_1053, needs a mission ticket the seeded player lacks) → the result pages (the event coin `item_coin_291` drops) → back on the board, then home;
3. **a summer gacha:** ガチャ → 復刻水着2020① (`gacha_pickup_role_1211`, a step-up) → 10連ガチャ (2,500 coins) → the summon → the results → home.

Each step waits for its request in soa-server's packet log (CheckEventRankingResult, MissionTalk / EndMissionTalk, MissionStart / MissionEnd, GetGachaInData, Gacha) or for its screen, and the server's state is checked at the end (story and battle cleared, mc99_566 unlocked, event coins 0 → 80, stamina 134 → 130, coins 300,000 → 297,500, ten draws). It writes numbered screenshots (`NN-name.png`, a flat black/white frame is retaken), `summer-demonstration-grid.png` (a contact sheet by `tools/contact_sheet.py`, Pillow from `requirements.txt`), `milestones.txt`, `state-*.txt` and the logs to OUT (default `work/test/summer-demonstration`, whose README describes a run); the phone is hard-linked from the shared pre-downloaded phone `work/phone-3.7.0` (`scripts/shared-phone.sh`; `SOA_PHONE=none` downloads the 3 GB instead and adds three download screenshots, `EMU_DATA=DIR` runs on DIR) and goes, with the server state, to a scratch dir that is deleted (`KEEP_SCRATCH=1` keeps it). About 5 minutes on the shared phone, 8 with the download. PASS twice on 2026-10-01 on the shared phone (and twice with the download before the shared phone was merged).

### NieR demonstration (`nier_demo.sh`)

```sh
emulator/scripts/nier_demo.sh [--watch] [--clock "YYYY-MM-DD HH:MM:SS"|host] [--seed-rng N] [--max-pulls N] [OUT]
```

The same kind of tour for the NieR:Automata collaboration (agent `nier-demo`, 2026-10-01): `soa-server --enable-events --event-keywords NieR`, which opens exactly one gacha, the rerun `gacha_pickup_role_0283` 復刻NieR:Automataピックアップキャラガチャ (pick-ups ２Ｂ `role_cc0015_b01a_5551`, ９Ｓ `role_cc0016_b01a_5563`, Ａ２ `role_cc0017_b01a_5572`). Its list banner (`20200227_chara_002`) and pick-up panels (`pickup_img_chara_0015..0017`) were deleted from the online data, so the banner gate would keep it shut; the stand-ins in `standin-assets/Image/etc2/` (`tools/make_standin_banners.py`: "STAND-IN" tag, the title, the names, the characters' chip portraits and full-figure art from the download) open it, and the client fetches them from soa-server's CDN at login. Fresh state from `data/saves/seed/Game.xml` (300,000 coins, no NieR character), `--seed-rng 1`, both clocks at 2026-10-01 12:00:00. It plays:
1. **launch:** as the summer demo (boot, title, login, notice board, LOGIN BONUS, home);
2. **the gacha:** ガチャ → おすすめガチャ, whose first row is the stand-in banner (checked by its colour) → the banner page with the stand-in panels (2B, then 9S and A2 as the page rotates them);
3. **pulls:** 10連ガチャ (5,000 coins) → the confirmation checked before 決定 (`flowctl.py gacha-confirm`: 決定's spot is on the rotating pick-up panels, where a tap opens a character detail) → 決定 (`Gacha`), repeated until a draw is `role_cc0015/16/17_*`: each pull's ten draws are read in draw order from the server's state (`tools/server_state.py`) into `pulls.txt`; on the pull with a NieR character the summon is tapped through to each NieR card (the reveal shows figure 1, card 1, figure 2, … one tap each) and the rest skipped; at most `--max-pulls` (30) pulls, then FAIL;
4. the character list (キャラクター → ステータス強化, by rarity), home.

Checks: the one gacha opened, the banner and panel on screen, every `Gacha` request for `gacha_pickup_role_0283`, ten draws of it per pull, 5,000 coins per pull, and the NieR role new in the roster (`roster-*.txt`, `roster-diff.txt`: new uids and limit breaks). With the defaults the first 10-draw has Ａ２ (draw 2) and ９Ｓ (draw 7): one pull, every run. `--seed-rng 2 --max-pulls 3` exercises the loop (three pulls without one, then the FAIL). Output in OUT (default `work/test/nier-demonstration`, whose README describes a run) with `nier-demonstration-grid.png`; about 4 minutes on the shared phone. PASS twice in a row on 2026-10-01. 2026-10-06, after the gacha pool update of 2026-10-05 (`gacha_pickup_role_0283`'s pick-ups and pools unchanged, so the same draws): PASS on every run, twice with the confirmation check.

`emulator/tests/` holds the Ninja cipher reference and its vector check (`ninja_check.sh`, agent E4).
