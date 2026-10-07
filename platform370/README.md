# platform370/: the 3.7.0 platform layer (libsoaplatform370)

What the 3.7.0 online client (`work/libSOA-3.7.0.so`) needs from the platform under it that the JIT host runtime (`runtime/`, built for the offline build's import and Java lists) doesn't give. The game code stays as shipped, except for one native patch (the service-end check). Everything here plugs into the runtime through its extension points (`runtime/README.md`), so the runtime is unchanged.

**Users:**
- **`soa-emu`** (`emulator/`) links it today, with every piece on.
- **`soa`** (the port) links it since P1 of `docs/history/PLAN-rebase-370.md` (branch `port/rebase-370`): `port/src/main.cpp`.

It was moved out of `emulator/src/` (P0 of that plan). `git log --follow` keeps the five `*_370.cpp` files' history; `src/internal.h` replaces `emulator/src/emu.h`, whose settings became the public `Config`.

## What's in it

| File | What | Extension point | Switch (`Config`) |
|---|---|---|---|
| `include/platform370/platform370.h` | The public API (below) | | |
| `src/platform370.cpp` | `install()`: registers the enabled pieces, sets `app_version` and the device clock | `hle_add_registrar`, `jni::add_class_installer`, `device_config()` | |
| `src/java_370.cpp` | The 25 `jb.Aska.AskaActivity` methods only 3.7.0 calls (Play Games, achievements, location, notifications), answered like a phone without those services (`emulator/README.md` "The Java methods"), and the 6 in-app billing methods (the coin shop's store), answered by a local store that completes every purchase for nothing (`docs/client-changes.md` "In-app billing") | `Vm::def` | `java` |
| `src/hle_370.cpp` | The import 3.7.0 has and the runtime lacks (`fmod`); the device clock: `time`, `gettimeofday`, `clock_gettime`, `syscall(clock_gettime)` on the realtime clocks, at an offset from the host's (0 by default) | `Hle::override_fn` | `imports`; `clock`, `device_clock` |
| `src/patch_370.cpp` | The native patches: `CParameterUtility::FindGlobalStringWithKey` answers `service_stop_day` with `""`, so the client runs on the real date (`emulator/README.md` "The date and `service_stop_day`"); `CDialogManager::OpenBuyEndDialog` opens the coin shop instead of the sale-stopped dialog (the user's decision; `docs/client-changes.md` "Emulator mode") | `make_original_trampoline`, `hook_guest_function` (`core/cpu.h`) | `patch` |
| `src/lang_370.cpp` | The language (`docs/client-changes.md` "English mode"; `docs/PLAN-english.md` B1, B7): with `lang` "en", `CLanguage::CLanguage` is hooked and sets `Current` to en (every file tried as `name-en.ext` first); with `voice_lang` "ja" (default), `BAS:VoiceLanguage` = 0 is written into the phone's `Game.xml` before the client starts. With `lang` "ja" nothing is hooked | `make_original_trampoline`, `hook_guest_function`; the runtime's `SharedPrefs` | `lang`, `voice_lang` |
| `src/text_370.cpp` | `--lang en`'s text (`docs/PLAN-english.md` E10): `CCocosLabel::SetText` is hooked so the client's hard-coded Japanese strings show the English of new `port_en_*` master text ids (`data/english/client-strings.tsv`; the Japanese stays when the master has no such row); `CCocosLabel::DrawSelf` is hooked to break a line that is wider than the label's box (or the screen) at spaces, measured with the client's own `CalcStringRect`. Not installed with `lang` "ja" | `make_original_trampoline`, `hook_guest_function` | `lang` |
| `src/net_370.cpp` | The network redirect: `getaddrinfo` / `gethostbyname` / `connect`. `production-game.so-ana.com` and mapped names resolve to the server host, and port 443 / 4001 go to the server / lobby port. On the way, Bionic's `ai_flags` and `EAI_*` codes are translated to and from glibc's (`emulator/README.md` "Networking") | `Hle::override_fn`, delegating to the runtime's thunks | `net`, `netcfg` |
| `src/http_370.cpp` | The host HTTP/1.1 client behind the `AskaActivity` HTTP methods (`HttpRequest`, `GetHttpHeader`, `ReadHttpResponse`, ...). URLs to a mapped host go to the installed `HttpBackend` in memory, else to `netcfg.http_*` as plain HTTP | `Vm::override_method` | `http` (reads `netcfg` and `set_http_backend`) |
| `src/internal.h` | The pieces' install functions, for `platform370.cpp` | | |

`docs/client-changes.md` "Emulator mode" lists every answer and the patch for the change log.

## API (`#include "platform370/platform370.h"`, namespace `soa::platform370`)

```cpp
platform370::Config cfg;                // every piece on by default
cfg.netcfg.server_host = "127.0.0.1";   // soa-server's --listen
cfg.netcfg.server_port = 44300;
cfg.netcfg.http_port = 44380;           // soa-server's --http (http_host "" = server_host)
cfg.netcfg.hosts["cdn.example"] = "";   // more names to map ("" = server_host); keys lower case
cfg.device_clock = "host";              // or "YYYY-MM-DD HH:MM:SS" (local time)
cfg.patch = true;                       // false = soa-emu --no-patch
cfg.lang = "ja";                        // or "en" (--lang); cfg.voice_lang = "ja" or "keep" (--voice-lang)
platform370::install(cfg);              // before hle_init() and jni::Vm::get().init()
...
PatchStatus s = platform370::install_patches(*lib);  // after load_library, before run_initializers
platform370::install_language(*lib);                 // after install_patches (and vfs_init), before run_initializers
```

- **`Config`:**
  - `app_version`: what `GetApplicationVersion` answers. Default `"3.7.0"`; `""` leaves `device_config()` alone.
  - Pieces: `java`, `imports`, `clock`, `patch`, `net`, `http`, all on by default.
  - `lang`: `"ja"` (default, the client as shipped) or `"en"`; `voice_lang`: `"ja"` (default, `BAS:VoiceLanguage` = 0) or `"keep"`. `install()` calls `fatal()` on other values.
  - `device_clock`: `"host"` (default) or a start date. A date needs `clock`; `install()` calls `fatal()` on a malformed one.
  - `netcfg`: server, HTTP and lobby host and port, and `hosts` (the `--map-host` names).
- **`install(cfg)`:** call once, before the runtime's `hle_init()` and `Vm::init()`. Their registrars run at the end of those calls. It also sets `device_config().app_version` and the clock offset, which is measured from `install()`.
- **`install_patches(lib)`:** returns `Hooked`, `Disabled` (`patch` off) or `NotFound` (the library's `FindGlobalStringWithKey` isn't 3.7.0's, e.g. the offline build's, or another hook is already on it; nothing is patched and a warning is logged).
- **`install_language(lib)`:** the language settings: with `lang` "en" the `CLanguage` hook and `text_370.cpp`'s `CCocosLabel::SetText` / `DrawSelf` hooks, with `voice_lang` "ja" the `Game.xml` write. Call after `vfs_init` (it writes the phone's `shared_prefs/Game.xml`) and `install_patches`, before any guest code runs; its hooks are no natives, so a host's natives don't replace them. `language()` and `language_hooks()` report what it did (the port's `platform370/lang` selftest).
- **`hides_global_key(key)`:** the patch's rule (true for `service_stop_day` while `patch` is on), for a host that replaces `FindGlobalStringWithKey` itself.
- **`net_config()` / `mapped_address(name)`:** the network settings in force, and where a name resolves to (`""` if not mapped).
- **`set_http_backend(backend)` / `http_backend()`:** the HTTP backend (below); `nullptr` (the default) = sockets.

### The HTTP backend (in-memory HTTP)

By default the HTTP client opens a TCP connection per request. A host whose server runs in its own process installs an `HttpBackend` instead (`soa --server inproc`: `port/src/native/api/server_cdn.cpp`, the adapter onto `soa-server`'s `HttpRouter`). Then every request whose URL host is mapped (`mapped_address(host) != ""`: `production-game.so-ana.com` and `netcfg.hosts`) is a call, with no socket; other `http://` URLs still go over sockets. platform370 doesn't know the server: the interface is its own (`platform370.h`), so the include check holds.

```cpp
struct MyBackend : platform370::HttpBackend {
    bool handle(const platform370::HttpBackendRequest& req, platform370::HttpBackendResponse& resp) override {
        // req: method, url, host, target (path?query), headers (Host, User-Agent, Connection;
        //      Content-Type / Content-Length for a POST), body
        resp.status = 200;
        resp.headers = {{"Content-Type", "application/octet-stream"}};
        resp.length = size;                    // the body's length (the client's Content-Length)
        resp.body = ...;                       // the body in memory, and/or
        resp.reader = std::make_unique<R>();   // an HttpBodyReader for the rest: read(buf, n) > 0, 0 at the end, < 0 error
        return true;                           // false = like a failed connection (HttpRequest returns 0)
    }
};
platform370::set_http_backend(new MyBackend);  // before or after install(); must outlive the requests
```

- **What the client sees** is what the socket path gives it: `GetStatusCode` the status; `GetHttpHeader` the fields without a status line, minus `Content-Length` / `Transfer-Encoding` / `Connection`, plus `Content-Length: <length>`; `ReadHttpResponse` `body`, then the reader's bytes up to `length`, then `-1`. A reader that ends early (0 or < 0) ends the body there (logged; the client's size / SHA-1 checks catch it).
- **Streaming:** `ReadHttpResponse` asks the reader for at most its buffer's size (the client's `GetTcpReceiveSize`), so a file-backed body is never held whole: the bundles run to hundreds of MB.
- **Threads:** `handle` and the reader run on the client's network thread(s) (one exchange per calling thread, as with sockets); `handle` must be thread-safe. `AbortHttpRequest` / `CloseHttpRequest` drop the reader.
- **Log:** `I/http: GET <url> -> in-process: <status>, <length> bytes (head in N ms)`, the same `I/http: GET <url>` prefix as the socket path's (`port/scripts/rebase_inproc_session.sh` counts them).

**Registration order** (the order soa-emu had when each file registered itself from a static initializer):
- at the end of `hle_init()`: `fmod`, then the clock overrides, then the network overrides;
- at the end of `Vm::init()`: the HTTP methods, then the Java answers.

They come after anything the host registered from static initializers, so platform370's overrides win over the host's for the same import or method. Each override delegates to the binding it replaced.

**Logs:** tag `p370` for `install` and the patch. The network and HTTP lines keep their tags `net` and `http`, which `emulator/scripts/*.sh` grep, e.g. `I/net: getaddrinfo(production-game.so-ana.com, ...) -> ... (mapped)`, `I/net: connect(fd N): port 443 -> ...` and `I/http: GET ...`.

**No includes from `port/`, `server/` or `emulator/`:** `platform370/CMakeLists.txt` checks at configure time that every quoted `#include` names a file in `platform370/` or `runtime/src`.

## Building

`platform370/CMakeLists.txt` is a subdirectory of the repository's build, added after `runtime/` when the port or the emulator is built (`SOA_BUILD_PORT`, `SOA_BUILD_EMULATOR`: both link it).

- **Target:** `soaplatform370`, a static library. Its public include dir is `platform370/include`, and it links `soaruntime_iface`.
- **Linking:** nothing in it registers itself from a static initializer; `install()` does the registering. So it links as a plain library, not whole-archive.

```sh
cmake --build build -j8 --target soaplatform370   # -> build/platform370/libsoaplatform370.a
```

## Hosts with natives (the port, P1)

`soa-emu` installs no natives. A host that does (`soa`: `install_native_functions`, the `FakeApiCaller` hooks) brings the runtime up in this order:

```
platform370::install(cfg);              // before hle_init / Vm::init
hle_init(); jni::Vm::get().init();
lib = load_library(...);
platform370::install_patches(*lib);     // first guest-function hook on the library
platform370::install_language(*lib);    // --lang / --voice-lang
install_native_functions(*lib);         // the host's natives, incl. the FakeApiCaller hooks
run_initializers(*lib);
```

**Which pieces each server mode needs:**
- **In-process server** (`--server inproc`: the `FakeApiCaller` route, answered by the server library in the same process): no GameRPC leaves the process, but the 3.7.0 client still needs a CDN for its game data: Login must carry `AssetPath` / `MasterPath` / `r_ver`, or the client never mounts its download storage (P1 finding: the home was the missing-texture checkerboard). So `soa` installs the server library's CDN as the **HTTP backend** (`port/src/native/api/server_cdn.cpp`: `soa-server`'s `HttpRouter` with the CDN mounted, called in memory; no socket, no listening port, no thread) and turns `net` and `http` **on**: the client resolves `production-game.so-ana.com` (`getaddrinfo`) before each HTTP request, so the name mapping is needed, and the mapping is also what sends a URL to the backend. `netcfg.server_port` and `http_port` are 0: a stray GameRPC `connect` to port 443 isn't redirected (`127.0.0.1:443`, refused like a network error), so it can't reach a `soa-server` listening on the default 44300. Everything else stays on.
- **Out-of-process server** (`--server HOST:PORT`: 3.7.0's own `NetworkApiCaller` against `soa-server`, with no `FakeApiCaller` hooks): everything on, with `netcfg` pointing at `soa-server`'s `--listen` / `--http`, as in `soa-emu`.

**Conflicts to settle in P1:**
- **`CParameterUtility::FindGlobalStringWithKey` is one of the port's natives** (`soa --list-native`). Both the native and the patch hook the function's entry, so only one of them can have it:
  - natives after the patch: the native overwrites the patch's hook, and `service_stop_day` is visible again;
  - the patch after the natives: it finds the native's stub instead of 3.7.0's prologue, returns `NotFound` and patches nothing.
  
  So with natives on, the native must apply the rule itself: return `""` when `platform370::hides_global_key(key)`. Or the host leaves that native out while `patch` is on. With `--no-native`, `install_patches` works as in `soa-emu`.
  
  **Settled (P1):** `soa` calls `install_patches` before `install_native_functions`. No native replaces `FindGlobalStringWithKey` today, so the patch has the function with any `--natives`; a native of it must answer a hidden key with the not-found string itself.
- **`app_version`:** `install` sets "3.7.0"; a host must not set it again afterwards (or pass `app_version = ""` and set it itself). `soa` doesn't set it (P1).
- **The port's own JVM overrides** (e.g. `webview_local.cpp`'s `ShowWebView`, from a static initializer) run before platform370's. platform370 touches only `AskaActivity` methods, so they don't overlap today.
- **The port's in-process mode needs the name mapping and the HTTP client, not sockets** (since P1: the CDN; since branch `port/p1b-inproc-nosocket`: in memory through the HTTP backend, where it was a loopback port before).
