# Plan: server library + the 3.7.0 emulator (out-of-process server over TCP)

> History: every step of this plan is done; the port no longer uses 3.8.0. Current docs: [emulator/README.md](../../emulator/README.md), [server/README.md](../../server/README.md), [port/PLAN.md](../../port/PLAN.md).

Approved by the user 2026-09-30; revised the same day (see "Revision"). `PLAN-emulator.md` has the background. Step 0 (worktree cleanup) is done: 63 removed, ~198 GB freed.

## Revision (2026-09-30, the user's decisions after approval)
- **Directories:**
  - The emulator lives in a top-level **`emulator/`** directory (the plan docs move there from `emulator/`).
  - The port must **not** be modified for the emulator. The first S1/E0 attempts edited `port/` and were rolled back.
- **Shared libraries:** extracting them from the port is allowed, as code moves plus adapters, with behaviour unchanged and gated:
  - **`server/`** (top level): `libsoaserver`, with the `soa-server` binary and its wire layer;
  - **`runtime/`** (top level): `libsoaruntime`, the JIT host: `core/`, `hle/`, `jni/`, `android/`, `frontend/`.
- **`port/`:** keeps `main.cpp`, `native/` and the port-only tests, and links both libraries.
- **`emulator/`:** the client `soa-emu`. It links `runtime/` only and talks to `soa-server` over TCP.
  - Everything specific to the emulator lives in `emulator/`: the 3.7.0 Java methods, the socket redirect, the HTTP client, the single-APK/3.7.0 mode, sessions and docs.
  - It plugs into the runtime through extension points (JVM class/method registration, HLE thunk override, asset-manager APK list). It doesn't edit port code.
- **Build:**
  - `port/CMakeLists.txt` stays the port's build root (`port/build/soa` unchanged for scripts). It adds `../runtime` and `../server` as subdirectories.
  - `emulator/CMakeLists.txt` adds `../runtime` (and `../server` for `soa-server`).
  - Dependencies stay in `port/deps` and `port/third_party`, referenced by path.
- **Order:**
  1. **R1 (runtime extraction) and S1 (server extraction), in parallel.** Their file ownership is disjoint; CMake and `main.cpp` conflicts are resolved at merge.
  2. Then **E0** (boot 3.7.0) in `emulator/`, on `runtime/`.
  3. Then the wire/CDN/net steps as below, all in `server/` or `emulator/`.
- Sections below that say `port/server/`, `jni/java_370.cpp` or HLE edits in `port/` are superseded by this layout.

## Context
**What the user asked:**
- Go over the plan for the 3.7.0 emulator (`docs/history/PLAN-emulator.md`).
- Reuse as much of the existing server code as possible.
- Move the server out of the port into its **own library**, used by both:
  - the in-memory port (`--restore`, FakeApiCaller hooks);
  - the out-of-process 3.7.0 emulator (the unmodified 3.7.0 client, talking TCP to a `soa-server` binary).
- **First:** clean up the old worktrees.

**State:**
- `linux-port` is at a1f70fe. D8 is done: `port/src/native/` has subsystem folders.
- The server is in `port/src/server/` (51 files, ~18k lines) and is compiled into `soa`.
- Its tests are `NATIVE_TEST`s under `soa --selftest`.

**Standing rules:**
- Commits go on `linux-port`, never `main`. Each agent works in a worktree on a `port/<name>` branch.
- Merge through `tmp/merge.sh` and the gate.
- Kill only PIDs you started. Watch memory. Never touch `work/`.
- Log every client change in `docs/client-changes.md`.
- Labelled server rules (a)–(d).
- Nothing hard-coded about which assets exist.
- Use the sanitised player id `LOCAL00001`.

## Step 0: clean up the old worktrees (first)
The worktrees take 206 GB in `.claude/worktrees/` (67 of them).
1. **Recheck each one.** For each worktree, check:
   - its branch is fully merged into `linux-port` (`git rev-list --count linux-port..<branch>` = 0);
   - no tracked changes (`git status --untracked-files=no` is empty);
   - its untracked entries are only my symlinks (`work`, `.venv`, `port/deps`, `port/third_party`), `samples/Game.xml`, `port/build*`, `port/build.log`, or the known stray 37 MB `data/basmaster-3.7.0.sqlite3` copies.
2. **Keep:** anything that fails the check. Known: `campaign` (1 unmerged commit), `script-decoder` (branch `worktree-script-decoder`, not one of mine), and `particles-sim` (1 uncommitted file, documented as unverified).
3. **Remove each one that passes:**
   1. `unlink` its four symlinks (never `rm -r` through them).
   2. Verify `work/download-3.7.0`, `.venv/bin`, `port/deps` and `port/third_party` are still intact in the main checkout.
   3. `git worktree remove --force <path>`.
   4. Keep the branch.
4. Then `git worktree prune`. Report the space freed and the list kept.

## Step 1: the server becomes its own library (`port/server/` → `libsoaserver`)
### Layout
- **Move** `port/src/server/` to `port/server/` (its own tree, outside `port/src/`):
  - `port/server/src/`: rules, APIs, msgpack;
  - `port/server/tests/`;
  - `port/server/include/soaserver/`: the public headers `server.h`, `ext.h`, `msgpack.h`.
- **CMake:** `add_library(soaserver STATIC …)` with its own `GLOB` and OpenSSL + sqlite linked. `soa` links it. A new `soa-server` executable links it too (step 3).
- **Link order:** `soa` must still register natives and tests in the same order. Server tests register through the library, so check that `soa --selftest` order and `--list-native` are unchanged (or document the new order once).

### Cut the five couplings to the client (found by exploration)
Each gets an interface in the library, implemented by the port in-process (the current behaviour) and by `soa-server` standalone.

1. **Platform glue** (`core/log.h`, `core/options.h`, `core/paths.h`, `core/vfs.h`):
   - logging becomes a callback;
   - a `ServerConfig` struct holds the server's own fields (master, db, seed, clock, `start_coins`, events, tower, galaxy pass, campaign …). The port fills it from `soa::options()`; `soa-server` fills it from its own command line (the same flag names);
   - `find_repo_file` becomes a `ServerConfig::repo` root;
   - `chash32` moves into the library: a pure function, used today from `native/engine/asset_decrypt.h`.
2. **Argument capture:** `server::capture` reads guest registers and memory.
   - Split it: the library takes a neutral `server::Request` (already the struct at `server.h:23-29`: method, fid, ints, strs, vecs).
   - The port keeps a `capture_from_guest()` adapter in `port/src/native/api/`.
   - The wire decoder (step 3) produces the same struct.
   - A per-API shim drops or uses the wire-only arguments: MissionEnd's battle log, the DeviceType on NoLoginStart and CreatePlayer.
3. **Guest reads inside rules:**
   - `battle_log_u32` / `battle_evaluation_value` (`server.cpp:344-384`) become a `BattleLog` view. In-process it reads guest memory as now. Over the wire it's parsed from MissionEnd's `blob` argument (format: docs/api.md, the MissionEnd wire line).
   - `client_status.cpp`: it calls the guest `CalcStatus`. It stays an optional in-process `StatusProvider`. Standalone, the server's own stat rules apply (`enabled_client_status` = false). That is the pre-client-status behaviour; document it as such.
   - `api_bonus.cpp` popup/tutorial guest calls (`:140-149`) and `api_campaign.cpp` roster reads: move behind an `InGameHooks` interface, a no-op standalone.
4. **`ClientMaster`** (edits to the client's in-memory master copy, triggered from the guest `sqlite3_exec` hook):
   - The library exposes `apply_client_master(sqlite3* db)`, which runs on **any** master DB: the same SQL hooks (date shift, texts, tower banners, shop, Sphere 211).
   - In-process: called from `lib_sqlite.cpp` as now.
   - Standalone: run on a copy of the 3.7.0 master that `soa-server` builds, re-encrypts and serves (step 4).
5. **Asset checks** (`android/ndk.h` `AssetManager::find/find_download`): replace with an `AssetIndex` interface.
   - In-process: an adapter over the port's `AssetManager`.
   - Standalone: a filesystem index over the download dir and the APK zips. Only names are queried, never contents.
   - The existing `events::set_asset_check` / `sphere211::set_asset_check` hooks are the seam.

### Tests
- **Library tests** (most of them use a scratch server with `in_game=false`) move with the library. They're driven by a small `soa-server --selftest` harness that has `NATIVE_TEST`'s API, so files don't change, and are also run by `soa --selftest`.
- **Tests that need the guest** stay in the port: `client-status`, `tutorial-npc-status`, `event-npc-helper-status`, and the asset-manager event tests.

**Gate:**
- `soa --selftest` passes, with the same count.
- `soa-server --selftest` passes.
- Smoke, plus the restore, events, home, tower and newplayer sessions. `--restore` behaviour must be unchanged: compare `tools/server_state.py` dumps of a restore session before and after.

## Step 2: boot 3.7.0 as the main image (pure JIT)
**Status (2026-10-01): done**, as `emulator/` + `runtime/` (not as a `soa --emulator` mode; see the Revision). See `emulator/README.md` "Status": the network path is reached, with error 1003 from the title's `NoLoginStart`, and a device clock before the service end is needed. The desktop host loop moved from `port/src/main.cpp` to `runtime/src/app/` (target `soaruntime_app`), so `soa` and `soa-emu` share it. The exploration notes below are kept as written.

**Exploration findings:**
- 3.7.0 has never been booted as the main image.
- Most of it already works with existing pieces:
  - `--no-native` (`main.cpp:731`) skips `install_native_functions` entirely. That includes the FakeApiCaller hooks and the address-bound and a2c natives, which would corrupt 3.7.0 because they carry 3.8.0 constants.
  - `--lib` skips extracting the lib.
  - The asset manager indexes any zip.
- **`--emulator` mode** = `--lib work/libSOA-3.7.0.so --no-native`, no `--restore` (so no restore370 and no stand-in overlay), plus the 3.7.0 APK. Fixes:
  - **APK names are hard-coded** (`main.cpp:867-868`). Accept the single 3.7.0 APK (`apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk`) and skip `assetinstalltime.apk` and the asset packs. No extraction needed.
  - **Data dir:** use its own data dir (`emulator-data/`) so the cached 3.8.0 `libSOA.so` is never reused.
- **Java:**
  - The 3.7.0 surface is the 3.8.0 one minus playcore. The HTTP methods are on `AskaActivity` itself: `SetHttpUserAgent`, `HttpRequest`, `GetStatusCode`, `GetHttpHeader`, `ReadHttpResponse`, `AbortHttpRequest`, `SetHttpProxy`. There's no separate `HttpClientBridge` or `X509Bridge` in the lib's JNI use.
  - Add the 3.7.0-only methods to `jni/java_android.cpp` (or a `java_370.cpp` registered in emulator mode), answering like a device without those services:
    - Play Games: `ConnectPlayServices`, `IsConnectedGooglePlayServices`, `IsLoginFailedGooglePlayServices`;
    - the 11 `*Achievement*` methods;
    - the location methods: `Start/StopLocationCapture`, `IsUpdateLocation`, `GetLocationX/Y`, …;
    - `UnScheduleLocalNotification`.
  - `GetApplicationVersion` must return `"3.7.0"` in emulator mode (`java_android.cpp:147`).
  - Unknown methods already return 0 with a warning, so boot can proceed while the list is filled in from the warnings.
- **Debug control:** the `phase:`, `call:` and `uiset:` commands need natives. Sessions use `tap`, `drag` and `shot` plus screenshots and the server's packet log instead.
- **Done when:** the 3.7.0 title screen shows; with no server, tapping gives error 1002.

## Step 3: `soa-server`, the wire layer (reusing the library)
- **New code:** `port/server/net/` + `port/server/main.cpp`.
- **Packets:**
  - a select/poll loop on TCP;
  - framing: the 24-byte header de-obfuscation, size + SHA-1 trailer via OpenSSL `SHA1`;
  - ProtocolError packets for refusals: `server::error_code`, status as the code.
- **Requests:** a decoder generated from `docs/api-wire.txt` (one measured layout per request: `hdr`, `u8/u32/u64/f32`, `str[N]`, `blob`, `vec64/vec32`, `dev`) plus the fids in `port/src/native/api/gen/wire_table.inc`. The `.inc` alone is ambiguous: `S` is either `str[N]` or a blob, and on the wire the counts come first. A new `tools/api_wire.py --gen-decoder` writes `port/server/net/gen/wire_decode.inc`. Output: `server::Request`.
- **Replies:** `server::handle()` gives the msgpack as today. Prefix u32 len (Login/SimpleLogin: fid + len), then encrypt and frame.
- **Bridge:** StartBridge → `ResultStart(token, url=http://<server>/bridge, x)`. The HTTP POST is answered with gzip JSON `{nativeSessionId, sharedSecurityKey}`. UpdateSession binds the connection to that session. The device UUID maps to a player; `LOCAL00001` is the default seed.
- **Ninja/sqex envelope:** decompiles exist (`work/decomp/api-server-doc-ninja*.c`, `-proto`). Test vectors come from calling the client's own encrypt/decrypt in a port selftest (like `wire_test.cpp`). Implement with OpenSSL. Fallback: a2c-translate the client's cipher functions into the server.
- **Tests:**
  - framing and decoder round trips against `wire_test`'s captured bodies;
  - envelope vectors;
  - a loopback test (the port's `wire_test` serializers → socket → `soa-server`).

## Step 4: CDN in `soa-server`
- **HTTP:** a small HTTP/1.1 server on a second port. `Android/<x>` maps to `<download-dir>/<x>`, plus `version.bin`, manifests and `master/`.
- **Master data:**
  1. At startup, copy `data/basmaster-3.7.0.sqlite3`.
  2. Run `apply_client_master` on the copy.
  3. Re-encrypt it with ADLD AES (`port/src/native/engine/asset_decrypt.cpp` has the decrypt half; move the ADLD code into the library and add the encrypt half).
  4. Update `version.bin` (hash, size, revision + 1).
- **Stand-in assets** (the Summer '17 banners, …) are added to the served tree and manifest.
- **Login** returns `AssetPath` / `MasterPath` pointing at this HTTP server.

## Step 5: client network glue (no guest patches)
- **Address redirect, at name resolution** (the original domains no longer resolve):
  - custom `th_getaddrinfo` (`hle/libc_misc.cpp:153`) and `gethostbyname` thunks map `production-game.so-ana.com` (and any `--map-host NAME=ADDR`) to `--server HOST`;
  - a `connect` thunk rewrites port 443 to `--server`'s port.
- **Fix existing HLE bugs on the way:** `addrinfo` hint `ai_flags` aren't translated (Bionic vs glibc: `AI_NUMERICSERV` 0x8/0x400, `AI_ADDRCONFIG` 0x400/0x20, `AI_V4MAPPED` 0x800/0x8, `AI_ALL` 0x100/0x10), and neither are the `EAI_*` return codes (Bionic positive, glibc negative). Everything else in the socket path (`sockaddr`, `fd_set`, `FIONBIO`, errno, `O_NONBLOCK` via `fcntl`) is already correct.
- **HTTP:** a real host HTTP/1.1 client behind `AskaActivity.HttpRequest` / `GetStatusCode` / `GetHttpHeader` / `ReadHttpResponse` / `AbortHttpRequest` / `SetHttpUserAgent`. Today they're refused as offline (`java_android.cpp:124-132`). It covers the bridge POST and the downloader (both go through this path; confirmed with `tools/callers.py`). `https://` URLs to mapped hosts are served as plain HTTP by `soa-server`.
- **Docs:** logged in `docs/client-changes.md` "Emulator mode" (platform layer only; no guest-code patches).

## Step 6: end to end
- **`emulator/emulator_session.sh`:** start `soa-server`, then `soa --emulator --server 127.0.0.1:PORT`. Run title → bridge → login (seeded) → home → battle → 10-draw → home, and a fresh-player run (19001 → terms → name → tutorial).
- **Parity:** run the same flow under `--restore` and diff the server DBs (`tools/server_state.py`).
- **Docs:** `soa-server --log-packets DIR` → `docs/online-server.md`, which moves from inferred to confirmed.

**Status (2026-10-01, agent `e6-end2end`): done.** `emulator/scripts/emulator_session.sh` plays, against `soa-server` with `soa-emu` (not `soa --emulator`, see the Revision): title → bridge → login → the 3.1 GB download → home → the login popups → mission select → 1-05 (mf01_001) → the battle → MissionEnd with the decoded battle log → results → home → a 10-draw (coins debited) → home; and with `--new-player`: 19001 → terms → name → CreatePlayer → Login → download → the tutorial (opening scenes, the battle tutorial, the mission-menu step, home, the home tutorial: `UpdateTutorial(9)`). Both PASS (twice). Parity: the server DB after the seeded flow equals `restore_session.sh`'s row for row, apart from the seed path, the device table and the times (`emulator/README.md` "Parity"). Server gaps found and fixed in `server/` (`docs/server-rules.md` "soa-server: the wire layer"): the LoginResult's root `Player` (the client's `LoggedIn`), session reconnects, the campaign hooks and `EndMissionTalk`, closing after a ProtocolError, `a_ver` with CreatePlayer, the URL defaults. Two runtime defects are written up with proposed patches, not applied (`emulator/README.md` "Networking": the JNI reference low byte behind the 1-in-8 lost first request, and the JIT's missing Top Byte Ignore). `docs/online-server.md` gained the packet-log-confirmed facts.

## Orchestration
1. **Integrator, first:** step 0 (worktree cleanup).
2. **Wave E1, in parallel:**
   - **S1 server-lib** (step 1). Owns `port/src/server` → `port/server` and the adapters in `native/api`, `libs/lib_sqlite.cpp`, `android`.
   - **E0 client-boot** (step 2). Owns `main.cpp` mode switches, `android/` single APK, `jni/java_370.cpp`. Disjoint files.
   - **E4 cipher research.** Decompile and selftest vectors only; no server code yet.
3. **Wave E2,** after S1 merges:
   - **S2 wire + bridge** (step 3);
   - **S3 CDN + master re-encryption** (step 4);
   - **E1 client net glue** (step 5, after E0).
4. **Then E6:** end to end (step 6).
5. **Merging:** each through `merge.sh`, plus a gate on `linux-port` (full selftest, smoke, restore/events/home/tower sessions), plus `soa-server --selftest` once it exists.

## Verification
- **After step 1:**
  - `soa` behaviour is unchanged: same selftest count and order, same `--list-native`, sessions PASS, `server_state.py` diff of a restore session is empty.
  - `soa-server --selftest` passes on its own, with no guest library loaded.
- **After steps 2–5:** `emulator_session.sh` PASS. `--log-packets` shows a bridge, a login, at least 10 APIs, an encrypted MissionEnd and a master download.
- **Parity:** the server DB after the emulator flow equals the one after the same `--restore` flow, apart from documented differences.
