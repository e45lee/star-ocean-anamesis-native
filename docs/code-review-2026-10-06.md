# Code review, 2026-10-06

A software-engineering review of the whole codebase: C++ in `common/`, `runtime/`, `port/`, `server/`,
`emulator/`, `emulator-viewer/`, `platform370/` and `webview/`; Python in `tools/`, `control/`, `soa_save/` and
`tests/`; CMake and scripts. It covers common code and design smells, not the game's behaviour.

- **Commit reviewed:** `9df7884` (main, 2026-10-06). Every `file:line` in this document refers to that commit.
  An english-exec agent was changing code in parallel, so lines may have moved since.
- **Scope:** this is a review only. Nothing was refactored. The user picks the follow-ups (see the plan at the end).
- **Method:**
  - Five area reviews (runtime + common + webview; port; server; build + cross-library; Python + tests),
    then a consolidation.
  - Tools:
    - a scratch build with `-Wextra` on top of the targets' `-Wall`;
    - lizard (function length, CCN, `-Eduplicate`);
    - ruff, vulture, pylint `symilar`;
    - `-Wunused-*` syntax-only passes;
    - git grep counts.
  - The tools ran from a scratch venv, `work/tools/review-venv`. `requirements.txt` is unchanged because no
    committed check uses them.
  - **Every finding was confirmed by reading the code.** There are no tool-only findings. The quoted lines of
    the top-ranked findings were re-read at `9df7884` during consolidation.

Ratings: **Impact** H/M/L. **Effort** S (hours), M (a day or two for one agent), L (several days or several
agents). **Risk** is the risk of the fix.

## Executive summary

The codebase is in better shape than its size (about 165k lines of our own code) suggests:

- **Layering:** `server/` and `runtime/` include nothing above them, and configure-time checks enforce it.
- **Shared libraries:** each has one implementation (ZIP on minizip-ng, Base64, prefs XML, PNG).
- **Warnings:** `-Wall` is on everywhere and the `-Wextra` build is almost clean (166 warnings, nearly all
  `-Wmissing-field-initializers` in test aggregates and GCC `std::optional` false positives).
- **Server:** the readability plan left short handlers, typed ids and clocks, and bound SQL only.
- **Natives:** no C++ `virtual` in recovered classes, few raw offsets in the scaffolded subsystems, and a
  differential `NATIVE_TEST` in every subsystem.

The problems that matter cluster in five places:

1. **Errors that pass silently where correctness is at stake.**
   - Failed SQL in a server request is logged, and the request is still committed and answered as a success.
   - The gate decides the tests/diff verdict from a `summary.txt` that may be stale, ignoring the exit code.
   - Several gate scripts grep output instead of checking exit codes.
2. **Concurrency in the runtime's JNI layer.** Method tables are `std::map`s read without the lock that
   their writers hold, and an unlocked static `std::set` is written on every call to an unimplemented method.
3. **Copies of one rule in several places.**
   - Game codecs: SLZ in 5 copies, ADLD XOR in 4+, CHash32 in 3.
   - The second server clock in the CDN.
   - "Where is the checkout", in 4 programs and about 10 scripts.
   - Seven drifting server-plus-client launchers.
   - The item, stock and FOL write paths in server handlers.
4. **Port native infrastructure that has not caught up with the rebuild.**
   - The docs and `--natives` help still describe "301 route natives". `soa --list-native` prints 1,944.
   - About 91 hard-coded 3.7.0 addresses (46 of them exported symbols), with no check that the loaded
     library is the one they belong to.
   - Dead a2c-body machinery in the most complex function of the port (`live::check`, CCN 129).
   - `-ffp-contract=off` covers only two subsystems.
5. **The Python driver layer.**
   - 686 fixed `wait:N` sleeps against 27 condition waits in the sessions; this is the main source of
     slowness and flakes.
   - Two interpreters (system `python3` and `.venv`), with re-exec workarounds, and 81 `sys.path.insert`s.
   - About 7,000 lines of unused a2c generators.

None of this blocks Wave A. Batches B1–B3 below are cheap and protect everything that follows: the gate,
server-state integrity and runtime thread safety. B5 makes the natives framework honest before N's Wave A
builds on it.

## Top 10

| # | Finding | Area | Impact | Effort | Risk |
|---|---|---|---|---|---|
| 1 | [S1](#s1) A failed SQL statement inside a request still commits and answers success; `with_live_server` never checks begin/commit | server | H | S–M | M |
| 2 | [R1](#r1) JNI method tables read and written across guest threads without a common lock | runtime | H | S | L |
| 3 | [T1](#t1) `gate.py`: tests/diff verdict from a possibly stale `summary.txt`, exit code ignored; Ctrl-C leaves queued tests starting clients | tools | H | S | L |
| 4 | [X1](#x1) Game codecs copied across libraries and tools (SLZ ×5, ADLD ×4+, CHash32 ×3) | cross | H | M | L |
| 5 | [P1](#p1) Natives docs and `--natives` describe the pre-rebuild port (301 vs 1,944 rows); no A/B switch for the subsystem natives | port | H | S–M | L |
| 6 | [P2](#p2) ~91 hard-coded 3.7.0 vaddrs (46 are exported symbols, several copied between files); the loaded library is never checked | port | H | M | L–M |
| 7 | [T2](#t2) `tests_for.py` runs no shard when the comparison tools change; `compare_packets.py` has no test and no negative control | tools | H | S–M | L |
| 8 | [S2](#s2) Story-campaign progress is written in its own transaction before the request runs, and cached in a never-invalidated global | server | M–H | M | M |
| 9 | [T3](#t3) Sessions wait with 686 fixed sleeps and only 27 condition waits | control | H | L | M |
| 10 | [B1](#b1) `-ffp-contract=off` only on `math_*` and `input_*`; bit-exactness of the other float natives relies on the default `-march` | build | M–H | S | L |

---

## Findings by area

### Server (`server/`)

<a id="s1"></a>
#### S1. Failed SQL is logged, and the request still commits as a success (H, S–M, risk M)

**Where:**
- [server/src/state/sql.cpp:42-71](../server/src/state/sql.cpp#L42): `Sql::exec` and `Sql::q`.
- `server/include/soaserver/sql.h:73`: "Errors are logged … not returned".
- [server/src/core/server.cpp:147-184](../server/src/core/server.cpp#L147): `handle_request`.
- [server.cpp:226-236](../server/src/core/server.cpp#L226): `ext::with_live_server`.

**What:**
- When prepare or step fails, `q` logs it and returns the row count (0). A failed UPDATE therefore looks the
  same as one that matched no rows.
- `handle_request` commits unless `rc.refusal` is set. The only SQL failure it catches is a COMMIT refused by
  a deferred foreign key, which it turns into 10208.
- These failures all commit whatever part of the request ran before them, and the reply says the request
  succeeded:
  - a STRICT type mismatch;
  - a CHECK or immediate foreign-key violation;
  - `SQLITE_BUSY`;
  - a misspelt column in a concatenated name (`growth.cpp:451`, `mastery.cpp:324`).
- `with_live_server` runs `begin; fn; commit` without checking either. A failed commit leaves the
  transaction open, and every later `begin` in `handle_request` then fails silently.

**Why it matters:** the "one transaction per request" contract in `server/ARCHITECTURE.md` is the
server's main integrity guarantee, and this breaks it without a trace in the reply.

**Fix:**
- Count statement errors on the `Sql` handle that the request's `Ctx` uses, or set a flag on
  `RequestContext`.
- In `handle_request`, check the count before commit and route an error to the existing rollback + 10208
  path, logging the statement.
- Check `begin` and `commit` in `with_live_server` and roll back on failure.
- Add one unit test that forces a CHECK violation inside a handler.
- Prove the change with byte-identical replays (`tools/server_replay_diff.sh`).

<a id="s2"></a>
#### S2. Campaign progress is written outside the request transaction (M–H, M, risk M)

**Where:**
- [server/src/core/lifecycle.cpp:51-57](../server/src/core/lifecycle.cpp#L51): `answer()` calls
  `campaign::on_request(r)` before `handle()`.
- [server/src/api/campaign/progress.cpp:17-71](../server/src/api/campaign/progress.cpp#L17): `g_state`,
  and `save_state()` through `with_live_server`.
- `campaign.cpp:62-80,110-140`.
- `api/settings/scenario_library.cpp:53`.

**What:**
- On MissionEnd and MissionTalk, the campaign records the clear in a separate transaction before the
  handler runs. A MissionEnd the server then refuses (10208, `--fail`, a refused commit) still counts as
  a campaign clear.
- Progress is cached in a global `g_state` that is loaded once and never invalidated. It goes stale across
  CreatePlayer / new-player and across selftest scratch servers.
- Clears live in both `mission` and `campaign_clear`; `scenario_library.cpp` reads them with a `union`.
- `mission_arg(req, 7)` guesses the mission id by scanning ints for a value that is a master mission id,
  although `core/request_args.h:105-127` has exact `MissionStartArgs`, `MissionEndArgs` and
  `MissionTalkArgs`.
- `with_live_server` takes the server's non-recursive `mu`, so calling it from a handler would deadlock.
  Only convention prevents this.

**Fix:**
- Move the request-side updates into a hook inside the request's transaction (the existing
  `ext::OnResponse` path), applied only when the request is not refused.
- Read progress from the DB instead of the global, and use the args structs.
- Assert `with_live_server` is not re-entered on the handler thread.

<a id="s3"></a>
#### S3. A second server clock in the CDN, and `--clock` handled in three places (M, S, risk L)

**Where:**
- [server/src/cdn/files.cpp:82-85](../server/src/cdn/files.cpp#L82):
  `server_time() { return time(nullptr) + (c.has_clock ? c.clock_offset : 0); }`.
  `cdn/tree.cpp:147` and `cdn/served_master.cpp:31` use it.
- `offset = t - time(nullptr)` is computed in `include/soaserver/cli.h:47` (an inline lambda instead of
  `set_clock`), `core/support.cpp:60` and `core/clock.cpp:28`.
- `parse_clock` exists twice with the same body: `common/include/soa/cli.h:99` and `core/time.cpp:34`.
- `served_master.cpp:32` decides the event clock from `config().has_clock`, while `clock.cpp:31` decides
  it from `g_clock_offset`.

**What:**
- `files::server_time()` ignores `set_clock_source` (the replay and test seam) and later
  `set_server_clock` calls (the port's `clock:+N`).
- The two event-clock decisions differ once `clock:+N` has been used.

**Why it matters:** this is the duplication `clock_now()` was introduced to prevent. It is latent today
(replay builds no CDN).

**Fix:**
- Replace `files::server_time()` with `clock_now().v`.
- Have the CLI lambda call `set_clock`.
- Make one `parse_clock` call the other.
- Use `event_clock_of` in `served_master`.

<a id="s4"></a>
#### S4. Item, stock, FOL and item-set writes bypass their helpers (M, S, risk L–M)

**Where:**
- [api/gacha/gacha.cpp:236-246](../server/src/api/gacha/gacha.cpp#L236): `draw_weapon` re-implements
  `core/rewards.cpp:67-80` `new_item` (same INSERT and CItemInfo, without content_type / drop_type).
- [api/favor/favor.cpp:292](../server/src/api/favor/favor.cpp#L292):
  `update stock set count = count - ?` bypasses `wallet::add_stock`, its clamp and its (a) label, and uses
  an ad-hoc `Sql{st}`.
- [api/missions/mission_end.cpp:109-110](../server/src/api/missions/mission_end.cpp#L109): FOL added
  inline as `min(fol + ?, ?)`, with its own `4200000000u` default. The (a) label lives only in
  `wallet.cpp:51`.
- `api/sphere211/rewards.cpp:22-30` `grant_content` is a third item-set expander, next to
  `core/rewards.cpp:144` `grant_with_item_sets`. PLAN-readability R18 flagged it.
- Neither item-set expander guards against a self-referencing `master_item_set`.

**Fix:**
- Route every write through `rewards::new_item`, `wallet::add_stock(-n)`, `wallet::add_fol` and
  `grant_with_item_sets`.
- Add a depth guard to the item-set expansion.
- Prove the change with replays.

<a id="s5"></a>
#### S5. Content types are raw integers; the `ContentType` and `Grant` steps of PLAN-readability 2.3 never landed (M, M, risk L)

**Where:**
- `core/rewards.cpp:24-45`: `d.type == 1/2/3/4`, `(d.type >= 5 && d.type <= 10) || d.type == 16`.
- `core/ext.cpp:167-168,252`.
- 14 `kContent*` constants in 11 files under different names, several of them duplicated:
  - item set 99 in `core/rewards.h:12` and `sphere211/rewards.cpp:16`;
  - item 1 in `gacha.cpp:33` and `mission_end.cpp:24`;
  - free coin 4 in `rewards.h:11` and `mission_end.cpp:24`.
- `ext.h:140` and `rewards.cpp:144` keep the `(type, id, num, Value& items, Value& stocks, Value& chars)`
  signature.

**Fix:** one `enum class ContentType : u32` in `core/ids.h`, labelled from docs/api.md "Content types",
used everywhere. Then the `Grant` / `Granted` structs from the plan.

#### S6. Smaller server items

- **Long functions:**
  - [master/npc_status.cpp:32](../server/src/master/npc_status.cpp#L32) `rules::npc_status`: 132 lines,
    CCN 51, one-letter row names, raw factor types 16/53/70/77. This breaks plan 2.2 and 2.5; no R step
    covered it.
  - `net/game.cpp:287` `handle_packet`: CCN 28.
  - `net/wire.cpp:187` `decode_request`: CCN 38.
- **Hand-rolled parsing in the wire layer:**
  - `net/game.cpp:102-123` `json_string_field` searches substrings: it matches a key inside a value and
    doesn't handle `\uXXXX`. It is used for bridge requests and, through `net/client.cpp:217`, replies.
  - `json_escape` is duplicated in `net/game.cpp:47` and `platform370/src/java_370.cpp:57`.
  - `net/http.cpp:66` `url_decode` maps `+` to a space in paths.
  - CDN paths are decoded twice (`cdn/tree.cpp:75-96` decodes again). The `..` check runs after the second
    decode, so this is not a traversal hole.
  - Fix: nlohmann-json from vcpkg (header-only), one decode.
- **Hard-coded FunctionIDs:**
  - `0xb7c62bc2` (MissionStart) in `campaign.cpp:66`, `mission_start.cpp:547`, `play_state.cpp:92` and
    `sphere211.cpp:48`.
  - `0x7c1b7a1b` in `lifecycle.cpp:16` and `campaign.cpp:65`.
  - Fix: have `tools/api_wire.py` emit a `fids.h`.
- **`std::stoull` / `stoul` in handlers can throw:** `state.cpp:135`, `ranking.cpp:140`, `rental.cpp:43`.
  Nothing catches it, so soa-server would terminate. Use `from_chars`.
- **41 direct `clock_now()` calls inside handlers** ignore the `ctx.test.now` a test sets, e.g.
  `gacha.cpp:116`, `rewards.cpp:70,113` and six in `mission_start.cpp`. Use `ctx.now()`.
- **Global state:**
  - `server()` (`server.cpp:202-210`) creates `g_server` lazily without synchronisation. Use `call_once`.
  - `GameServer::sessions_` (`net/game.h:108`) is never pruned, and each reconnect trial-decrypts against
    all sessions.
  - `campaign/lists.cpp:27` calls the non-reentrant `localtime`.
- **Deprecated OpenSSL low-level APIs:** `AES_set_*_key` (`cdn/adld.cpp:43,52`,
  `net/ninja/ninja_ciphers_ossl.cpp:24`) and `SHA1()` (`net/wire.cpp:74,86`). The CDN already uses EVP.
- **A gap in the "no agent mentions" check:** `tools/server_evidence.py:48` misses a mention wrapped across
  comment lines (`core/lifecycle.cpp:27-28`).
- **`item_info_list(ctx, const std::string& where)`** (`player_info.cpp:162`) takes a raw SQL fragment.
  The only caller passes a number, so it is not injectable, but it should take a bound argument.
- **Six APIs are only refused in the replay corpus and never named in a unit test:**
  `EquipAccessory`, `ItemGradeUpArray`, `MaterialCompose`, `SearchPlayer`, `UpdateGearStock`,
  `AchievementReceiveList`.
- **Time zone:** `docs/server-rules.md:45,47` says master times and the 04:00 reset are JST. The code uses
  host local time, as the guest does. The behaviour is consistent; the docs should say "host local time,
  treated as JST".

### Runtime, common, webview

<a id="r1"></a>
#### R1. JNI method tables race between guest threads (H, S, risk L)

**Where:** [runtime/src/jni/jvm.cpp](../runtime/src/jni/jvm.cpp):
- `def` :124-135 and `override_method` :138-152 (under `Vm::m_`);
- `find_method` :165-180 (under `m_`, inserts placeholders);
- `invoke` :319-321 (no lock);
- `call_thunk` :372-381 (no lock).

**What:**
- `call_thunk`'s virtual dispatch calls `k->methods.find(key)` with no lock, while `find_method` inserts
  into the same `std::map` under `m_`.
- `invoke` calls `m->impl(...)`, a `std::function`, which `def` / `override_method` reassign under `m_`.
  `jvm.h` says `override_method` "also works after the game started".
- `invoke` keeps `static std::set<Method*> warned` with no lock. The similar set at :391 does take a
  mutex.

**Why it matters:**
- Concurrent map insert and find, and a `std::function` assigned while it is called, are undefined
  behaviour.
- The game resolves and calls Java methods from several threads.
- A failure here would be a rare crash that looks like a guest bug.

**Fix:**
- Lock the `warned` set, or share one `warn_once(Method*)` helper.
- Take `m_` (or a `shared_mutex` read lock) for the dispatch lookup.
- Swap `impl` atomically (`std::shared_ptr<const Impl>` with an atomic load), or allow `def` and overrides
  only before `Vm::init` returns and assert it.

<a id="r2"></a>
#### R2. Windows: the guest reads host errno; translation is opt-in per call site (M, M, risk M)

**Where:**
- [runtime/src/hle/libc.cpp:124](../runtime/src/hle/libc.cpp#L124):
  `void th_errno(Cpu& c) { ret_ptr(c, &errno); }`.
- `hle/guest_errno.h`, and the `guest_errno` calls in `libc_win32.cpp`.
- `net_win32.cpp:41-76` (`linux_errno`).

**What:**
- The guest gets the CRT's errno. MinGW numbers everything above 34 differently from Linux.
- Only `libc_win32.cpp` calls `guest_errno()`, at 8 call sites. These leak host values:
  - `th_mmap` (`ENOSYS`, :91);
  - `mbrtowc` (`EILSEQ`, :251-277);
  - `th_popen` (`libc_stdio.cpp:79`);
  - `hle_sem_*` (`libc_thread.cpp:446-452`; `hle/thread.h` promises guest values);
  - the CRT calls behind `th_stat` and `th_rmdir`.
- Two hand-written Linux errno tables overlap (`guest_errno`, `linux_errno`).

**Fix:**
- On Windows, keep a per-thread guest errno (a trivial `thread_local int`) that `__errno` returns, set
  through one `set_guest_errno(host)`.
- Merge the tables into one `linux_errno.h`.

<a id="r3"></a>
#### R3. Small HLE concurrency defects (L–M, S, risk L)

- **Windows futex BITSET** ([libc_win32.cpp:524-547](../runtime/src/hle/libc_win32.cpp#L524)):
  - `FUTEX_WAIT_BITSET`'s absolute CLOCK_MONOTONIC deadline is used as a relative timeout. The code
    comments it ("rarely used"), but if the guest uses it, the wait lasts up to ~24 days.
  - `FUTEX_WAKE` always returns 1.
  - Every `WaitOnAddress` failure is reported as ETIMEDOUT.
  - The `prctl` block is copied between the two `th_syscall` dispatchers (`libc_misc.cpp:66-93`,
    `libc_win32.cpp:549-585`).
- **`pthread_once` busy-waits** (`libc_thread.cpp:237`: `while (o->load() != 2) sched_yield();`) for as
  long as another thread's guest initializer runs. Use `std::atomic::wait` / `notify_all`.
- **Semaphores are keyed by guest address** (`libc_thread.cpp:311-335`). A `sem_t` freed without
  `sem_destroy` and reused at the same address inherits the old host semaphore and its count. Document the
  assumption, or stamp a magic word into the guest `sem_t`.
- **Movie pacing polls** with `sleep_for(2ms)` (`frontend/movie.cpp:85,113`). Use `wait_until` with a
  condition variable.

<a id="r4"></a>
#### R4. No public/private boundary in the runtime; prefix collision with the port's `core/` (M, M–L, risk L–M)

**Where:**
- `runtime/CMakeLists.txt`: `soaruntime_iface` exports all of `runtime/src`.
- The port includes 24 distinct runtime headers (e.g. `core/cpu.h` ×83, `core/loader.h` ×41).
- 9 `extern` mutable globals or TLS variables are declared in headers: `g_log_level`, `t_hook_filter`,
  `g_prof_*`, `g_gdb_enabled`, `t_record`, `t_rec`, `t_map_overwrites`.

**What:**
- `port/src/core/` (paths.h, options.h, cli.h) and `runtime/src/core/` (cpu.h, log.h, …) share one
  include prefix, so `#include "core/X.h"` resolves by include-path order.
- A future `port/src/core/log.h` would silently shadow the runtime's.
- `server/src/core/log.h` already carries a warning about exactly this.

**Fix:**
- Move the API headers to `runtime/include/soaruntime/` and keep the rest private.
- Rename the port's `core/` folder.
- Replace the header globals with accessors.

(CR10, 2026-10-08: the 23 headers the runtime's users include, and the one `.inc` they include, moved to
`runtime/include/soaruntime/<folder>/` (`#include "soaruntime/core/cpu.h"`); `runtime/src` is an include
dir of the runtime's own targets only (`soaruntime_private`), and every user's `soa_check_includes` allows
`runtime/include` alone. With the `soaruntime/` prefix the port's `core/` can no longer shadow a runtime
header, so it keeps its name. `.text` byte-identical for soa, soa-emu, soa-viewer and soa-server, Linux
and Windows. The header globals are unchanged.)

<a id="r5"></a>
#### R5. The bring-up sequence is copied into three hosts (M, S–M, risk L)

**Where:** `port/src/main.cpp:232-320`, `emulator/src/main.cpp:136-169`, `emulator-viewer/src/main.cpp:256-306`.

**What:** each host repeats the same ~15 steps in the same order: device, vfs, cpu, gdb, hle, Vm, load,
traces/profile/watchdog, download dir, APKs, initializers, `app::run`.
- The viewer ignores the return value of `set_download_dir` (:299); the other two `fatal()`.

**Fix:** `app::boot(BootConfig&)`, with hooks after HLE, after load (platform370 patches, natives) and
before init.

(CR10, 2026-10-08: `app::boot(BootConfig, &error)` in `runtime/include/soaruntime/app/boot.h`, used by all three
hosts, with hooks `after_load` and `add_assets`; a failed step (gdb, the library, the download tree, an
APK) returns the reason and the host exits 2. The viewer's `set_download_dir` result had already been
checked since the review.)

<a id="r6"></a>
#### R6. Library code that ends the process (L–M, S, risk L)

- `runtime/src/core/loader.cpp:94-206` calls `fatal()` (`abort()`) on a bad or non-AArch64 ELF. A wrong
  `--lib` therefore dumps core instead of reporting an error. Return an error instead.
  (CR10, 2026-10-08: `load_library(path, &error)` returns nullptr and the reason, with bounds checks on
  the headers and tables; test `loader/rejects-bad-files`.)
- `app/host.cpp:1042`: `app::run` ends with `_exit(0)`, so no host can run shutdown code after the loop.
  The in-process server relies on SQLite having committed already. Return an exit code, or add an
  `on_quit` hook.
- `platform370` has 6 `fatal()` calls on install paths. `--device-clock` parse errors belong in the CLI.

#### R7. Smaller runtime, common and webview items

- **`common/win32/posix_compat.h:74-82`** is force-included into every target that links `soa_compat`.
  It macro-renames common identifiers (`#define rename soa_rename`, `lstat`, `pread`, `gettid`, …), which
  also rewrites member functions and `std::filesystem::rename`.
  - Its comments name a `cmake/win32.cmake` and a `posix_compat.cpp` that don't exist.
  - `common/include/soa/install.h:35-42` includes `<windows.h>` in a public header, against
    posix_compat.h's own rule.
  - Fix: keep a macro for `rename` alone, and declare the missing functions under their real names.
- **Viewer-only code in the shared runtime:** `runtime/src/jni/java_playcore.cpp` (the Play Core classes) <!-- 380-ok: names the file under review -->
  is installed unconditionally (`jvm.cpp:742`). `platform_add_asset_pack` is used only by the viewer.
  `jni::add_class_installer` exists for exactly this case. Move both to `emulator-viewer/` and drop the
  three `check_no_380.sh` allow-list entries. Verify first whether 3.7.0 uses the `java.util` part.
- **Long functions:**
  - `gdbstub.cpp:526` `Session::handle`: CCN 89.
  - `hle/format.cpp:63` `format_impl`: CCN 78.
  - `app/host.cpp:816` `app::run`: 201 lines, CCN 74.
  - `app/host.cpp` (1,043 lines) mixes window, audio, input, control channel, scripted actions and the
    main loop.
- **`webview/src/css_simplify.cpp`** is 515 lines of Tailwind-v4 rewriting carried from another
  project. None of this game's pages use `oklch`, `@layer` or `--tw-`. Trim it, or mark it as a deliberate
  upstream copy.
- **Duplicated code in the area:**
  - `webview/tools/render.cpp:92` calls `stbi_write_png` directly; `soa::png_write` exists.
  - `libc_stdio.cpp:155-176` repeats a 32-argument `sscanf` call three times.
  - `WSAStartup` appears in three places (`common/src/sock.cpp:47`, `hle/libc_misc.cpp:183`,
    `hle/net_win32.cpp:34`); `soa::sock::startup()` exists.
- **Doc drift:**
  - `app/host.h:9-10` says `soaruntime_app` is used by soa and soa-emu; soa-viewer uses it too.
  - The runtime README's link list omits ffmpeg, OpenSSL and `soa_gamefiles`.
  - `libc_win32.cpp:12-13` says sockets are missing, but `net_win32.cpp` implements them.
- **`soa_env`** is an INTERFACE grab-bag (env, paths, install, fonts, cli) that links CLI11 into every
  library.
- **`Cpu::locate_jit_state`** (`cpu.cpp:437-488`) finds dynarmic's private `A64JitState` by scanning
  heap memory. It fails loudly, but a two-line patch to the pinned dynarmic exposing the state pointers
  would replace the scan.

### Port (`port/`)

<a id="p1"></a>
#### P1. Docs and `--natives` describe the pre-rebuild port (H, S–M, risk L)

**Where (the stale text):**
- [port/README.md:26](../port/README.md#L26): "only what the port itself needs … 301 rows".
- [port/PLAN.md:9](../port/PLAN.md#L9): "301 remain".
- `port/src/native/README.md:5` and the "What's native now" table (:102-110).
- `port/src/README.md`, whose native table lists common, api, restore and ui only.
- [port/src/native/common/native.h:36-44](../port/src/native/common/native.h#L36): "there are no other
  natives".
- `port/src/core/cli.cpp:59-60` (`--natives` help).
- `port/CMakeLists.txt:54-63`: "nothing uses them yet", although the lib_vorbis, lib_jpeg and lib_zstd
  natives use them.

**What:**
- `soa --list-native` prints **1,944** rows across 22 subsystems.
- `NativeSet` is only `Route` (everything) or `None` (nothing, including the route).
- There is no way to run in-process with the subsystem natives off. That is the A/B a native regression
  needs, and N's waves will need it constantly.

**Fix:**
- `--natives all|route|none`, where `route` means kGroupRoute plus the port's own hooks. Optionally add
  `--natives-skip SUBSYS,...`.
- Rewrite the stale text.
- Stop hard-coding the count in prose.

<a id="p2"></a>
#### P2. Hard-coded 3.7.0 addresses, partly duplicated, with no library check (H, M, risk L–M)

**Where:**
- 91 `constexpr u64 kX = 0x…` and 15 inline `base + 0x…`, in:
  - `kernel/kernel_layout.h:44-55`, `memory/memory_layout.h:31-40`, `render_layout.h` (14),
    `input_layout.h` (10);
  - string vaddrs in `params/params_guest.h:16-28`, `memory/memory_pools.cpp:24-32`,
    `resource/resource_manager.cpp:29-33`, `input/input_pad.cpp:25-28` and
    `containers/containers_object_container.cpp:28-31`;
  - `api/fakeapi.cpp:115,342-349,519`.
- **46 of them have a dynsym name.** Checked with nm on the 3.7.0 library; for example,
  `kVaddrGlobalMemoryManager` is `_ZN4Aska6Global16m_pMemoryManagerE`.
- **Several are copied between files:**
  - `0x26db1f8` in `memory_pools.cpp:25` and `containers_object_container.cpp:31`;
  - `0x26daf21` in `input_pad.cpp:28` and `fakeapi.cpp:115`.

**What:**
- `--lib PATH` accepts any library, and nothing compares it with the sha256 that the gen/ headers record.
- A missing symbol fails loudly (`guest::sym` calls `fatal`), but a wrong vaddr silently reads or writes
  the wrong memory.
- This also works against the "regenerate address tables" rule.

**Fix:**
- Resolve the exported addresses through `guest::sym`, cached.
- Generate one stamped address table for the rest (strings found by content, rodata tables).
- Check the library's sha256 or build-id at load, and refuse natives on a mismatch.

<a id="p3"></a>
#### P3. Dead a2c-body machinery in the live-check core (M–H, M, risk M)

**Where:**
- `port/src/native/common/live_check.h:46-49,230-330`: `Body`, `Entry::body`,
  `Family::add(…, Body, …)`, `add_test`, `gcall_sret`, `own_bodies`, `undo_note` / `StoreLog`,
  `sret_marked`.
- [live_check.cpp:933-1297](../port/src/native/common/live_check.cpp#L933): `live::check`, 322 NLOC,
  CCN 129, the most complex function in the port.
- `common/a2c_regs.{h,cpp}`.
- `runtime/src/core/cpu.h:249`: `a2c_guest_call`.

**What:**
- Every `Family::add` passes a null body.
- Outside live_check, `add_test`, `own_bodies`, `gcall_sret` and `undo_note` have no callers.
- The header comments name deleted families (arena, objbase, battle).
- `port/src/native/README.md:65,85,112` and `port/README.md:79` still describe a2c bodies.

**Fix:**
- Delete the Body paths. Keep `ACall` and `gcall_n`, which containers, data_formats and libcxx use.
- Rename the register file to `live::Regs`.
- Split `check()` into record, replay and compare.
- Re-run every family's live check to 0 mismatches.

<a id="p4"></a>
#### P4. Registration and live-check glue reinvented per subsystem (M, L, risk M)

**What:**
- `NATIVE_METHOD` is the documented form, but only 46 registrations use it.
- The rest use about ten other idioms, because each subsystem wires its live check into its own hook:
  - `NATIVE_FUNCTION_ORIG` 96, `LEAF_*` 77, `DF_HOSTFN` 19, `SCENE_NATIVE` 17;
  - `Hook<M>` in `kernel_dispatcher_check.cpp:460`;
  - the `FnInfo` table in `yayoi_sqlite_hooks.cpp:34-167`;
  - five identical `for (const Bound& b : kBound) register_native_function(...)` loops (`lib_zlib_api.cpp:211`,
    `lib_jpeg_api.cpp:217`, `lib_zstd_api.cpp:161`, `lib_vorbis_api.cpp:453`, `lib_crypto_api.cpp:107`).
- About 4,000 lines of `*_check` / `*_live` / `*_family` code sit in the subsystems.

**Fix:**
- `NATIVE_METHOD_CHECKED(sym, &C::M, Policy)`, with the family's policy (leaf, run-both, shadow, lockstep)
  as a template parameter.
- A shared `register_bound(table, note)`.
- Migrate one subsystem at a time, as part of N.

<a id="p5"></a>
#### P5. fakeapi: a hand-rolled std::map, raw offsets, a copied lambda search (M, M, risk M)

**Where:** [port/src/native/api/fakeapi.cpp](../port/src/native/api/fakeapi.cpp), 1,646 lines.

**What:**
- A hand-written std::map tree implementation: `tree_next`, `lower_bound`, `tree_destroy`, and the node
  insert in `AddLocalFile` (:120-201).
- A `std::function` destroy (:100-105).
- 153 raw `at<T>(p, off)` accesses.
- The "find the GetGachaRate lambda" loop, copied three times (:734-748, :764-772, :791-799).
- Two parallel models of the guest's libc++:
  - `common/guest_std.h:28-77` (`guest::String`, `StringList`; 45 files);
  - `libcxx/libcxx_layout.h:86-385` (`basic_string`, `list`, `tree`, `function`).

**Fix:**
- An `api/api_layout.h` for FakeApiCaller.
- Use `libcxx::tree` / `function`.
- One `any_request_lambda()` helper.
- Make `guest::String` an alias of `libcxx::basic_string<char>`.

<a id="p6"></a>
#### P6. Pre-scaffold files still use raw offsets and unnamed vtable slots (M, M, risk L)

- `common/port_debug.cpp:64-88`: phase-manager fields at +0x38, +0x40, +0x20, +0x24 and +0x1a0.
- `ui/webview_local.cpp:49,57,69-70`: vtable +0x58 and +0x28; floats at +0x9c, +0xa0 and +0x84.
- `common/memstats.cpp:172`: `*(u64*)(mm + 0x28)` is `memory::MemoryManager::m_heapSize`, which is
  already recovered.
- Magic slot indices with no `kSlot` constant (VIRTUALS.md 1.5): `lib_jpeg_util.cpp:70-75`,
  `memory_heap.cpp:623,676`, `yayoi_sqlite_driver.cpp:87`.
- `api/`, `ui/`, `restore/` and `common/` have no `symbols.tsv` or layout header.

<a id="p7"></a>
#### P7. The port re-implements a server lifecycle rule (M, S–M, risk M)

**Where:**
- [port/src/native/api/fakeapi.cpp:1104-1114](../port/src/native/api/fakeapi.cpp#L1104)
  (`h_end_mission_talk`) calls these itself: `server::submit`, `server::end_mission_talk`,
  `packet_log::answer_as`, `queue_request("GetPlayMission")`.
- `server/src/core/lifecycle.cpp:33-44` `answer_end_mission_talk` is what `server::answer` does for
  soa-server.
- `api/packet_log.cpp` copies the log-line format of `server/net/game.cpp` by hand.

**Fix:**
- Queue EndMissionTalk like the other base methods and let `server::answer` produce the reply.
- Export one packet-log formatter.

This touches the server hooks, which task H decided on. Check with the user before changing it.

#### P8. Smaller port items

- **getenv outside soa/env.h:**
  - `render/render_test_util.cpp:95` (`SOA_SELFTEST_START_FILE`; `main.cpp` reads it through `env_str`);
  - `params/params_natives_test.cpp:646` (`SOA_PARAMS_CORPUS`);
  - `yayoi/yayoi_sqlite_test_util.h:66` (`SOA_YAYOI_TEST_TRACE`).
  - The last two are undocumented in docs/environment.md.
  - The only lint is the selftest `server/no-setenv-state`, which checks setenv only and needs a booted
    game. Move a getenv/setenv lint into a T0 tools check.
- **No freshness check for generated headers:** `api/gen/fakeapi_tables.inc`, `api/gen/wire_table.inc` and
  `params/gen/params_instantiations.inc` record the library sha256, but no T0 step reruns their generators.
  Add `--check` modes, as `types.json` already has.
- **Stale leftovers:**
  - `common/test.cpp:56-66` `kRebaseSkippedHooks` names hooks from a deleted file, so the documented
    `SOA_TEST_HOOKS_ALL` does nothing.
  - `fakeapi.cpp:1126` refers to a deleted `restore370.cpp`.
  - `port/scripts/soactl.py` and `flowctl.py` are forwarding stubs that no file in the repository calls.
  - `unofficial::sqlite3` is linked three times.
- **Timing-based tests:**
  - `resource_layout_test.cpp:463` sleeps 200 ms, then expects the frame counter to have advanced.
  - `resource_layout_test.cpp:242` and `input_pad_test.cpp:190` poll with sleeps.
- **Coverage gaps (heuristic):** natives whose mangled name appears in no test:
  - sync: the C2/D2 constructor and destructor variants;
  - render: 7 state setters;
  - yayoi: `SQLiteDriver::Open` / `Execute`;
  - `restore_tower` and `webview_local` have no `NATIVE_TEST` at all.
  - `symbols.tsv` status lags behind: yayoi has 51 `native` and 0 `tested`; sync has 34 and 11.
- **Boilerplate:**
  - every `<s>_layout.h` repeats the u8…s64 typedefs (most of lizard's duplicate blocks);
  - about 27 ad-hoc `sym("_ZTV…") + 0x10`;
  - two copies each of the test helpers `vtable_of` and `instance<T>`.
  - Fix: a `native/common/layout_base.h`.
- **Big functions:**
  - `main()`: 187 NLOC, CCN 70;
  - `ASON::UnpackMessagePack`: CCN 119;
  - `wire_test.cpp`: a 350-NLOC test.
  - Natives mirror the guest's structure for bit-exactness. A long native is a smell only if a readable
    restructuring stays bit-exact, so don't split them for length alone.

### Build and cross-library

<a id="x1"></a>
#### X1. Game codecs copied across libraries and tools (H, M, risk L)

**Where:**
- **SLZ decoders (5):**
  - [tools/aif2png/aif2png.cpp:70-100](../tools/aif2png/aif2png.cpp#L70)
  - `port/src/native/common/test_assets.cpp:56` (`slz_chunks`)
  - `tools/missing_assets/presence.py:138` (`_unwrap_slz`)
  - `tools/make_standin_banners.py:74-110` (plus an encoder)
  - `port/decomp/bullet/pin/scan_rb.py`
- **ADLD XOR:**
  - C++, canonical: soa-server's `cdn/adld.cpp` (`soaserver/adld.h`; since CR4 `common/src/adld.cpp`).
  - C++ copy: `aif2png.cpp:55-67`, with its own CHash32 and CRC table at :38-52.
  - Python, canonical: `soa_save/adld.py`. It decodes a byte at a time, which is why the copies exist.
  - Python copies: `presence.py:127`, `make_standin_banners.py:69`, and a numpy one in `check_download.py`.
  - Hand-rolled encoders in `tests/test_adld.py:56`, `test_check_download.py:24` and
    `test_missing_assets.py:39`.
  - `check_download.py` imports the private `soa_save.adld._digits16`.
- **CHash32 in C++ (3):** `soaserver/chash32.h`, `aif2png`, and the `hash` native. The native is
  legitimately separate.

**What:**
- Each format rule exists in each copy: codec 0/5/7, the "size 0 = stored chunk" rule, chained SLZ.
- A fix lands in one copy and not the others. aif2png already rejects chained SLZ and AES; the Python
  copies differ in codec-7 support.

**Fix:**
- C++: move `chash32` and ADLD (XOR and AES) into `common/` `soa_codec`, which already links OpenSSL, and
  add an SLZ decoder there on zlib and zstd. The server, aif2png and the port's test helper link it.
- Python: add `soa_save/slz.py`, make `adld.encode` public, and give `adld.decode` a numpy fast path. The
  tools and tests import these.

<a id="x2"></a>
#### X2. "Where is the checkout" coded per program and per script (H, S–M, risk L)

**Where:**
- **The C++ programs:**
  - `port/src/core/paths.cpp:20` checks `port/CMakeLists.txt`.
  - `server/app/main.cpp:41-44` checks `server/` or `port/CMakeLists.txt`.
  - `emulator/src/main.cpp:55` and `emulator-viewer/src/main.cpp:66` check their own folders plus
    `runtime/`.
  - Each has its own `exists()` and `find_checkouts` wrapper around `install::repo_roots`.
  - `find_repo_file` is copied in [port/src/core/paths.cpp:51-66](../port/src/core/paths.cpp#L51) and
    [server/src/core/support.cpp:36-51](../server/src/core/support.cpp#L36); the copies differ in one line.
    `install::find_in_roots` already exists.
- **Shell and Python:** the main checkout is found three ways in about 10 files:
  - `git --git-common-dir` (`build.sh`, `vcpkg-bootstrap.sh`, `build_gacha_pools.py`, `extract_banners.py`,
    `make_standin_banners.py`);
  - `readlink -f work` (`windows-stage.sh`, `control/soadrive/proc.py`);
  - `os.path.islink(work)` (`server_replay_record.py`).
  - `extract_banners.find_db` and `make_standin_banners.find_db` are byte-identical.

**Fix:**
- `install::is_checkout(dir)` and `install::find_file(roots, {rels...})`, used by all four programs.
- One `main_checkout` helper for shell (`tools/common.sh`) and one for Python.

<a id="x3"></a>
#### X3. Seven server-plus-client launchers that have drifted (M–H, M, risk L)

**Where:**
- Bash: `scripts/run-emulator-370.sh`, `scripts/run-port-with-server.sh`, `scripts/package/run-emulator.sh`,
  `scripts/package/run-port-server.sh`.
- PowerShell: three `.ps1` twins.
- More copies in `control/soadrive/targets.py` and the test scripts.

**What has drifted:**
- **Cleanup:**
  - `package/run-port-server.sh:47-71` handles a second Ctrl-C and escalates to SIGKILL.
  - `run-port-with-server.sh` escalates to SIGKILL but has no double-signal guard.
  - `run-emulator-370.sh:65-70` and `package/run-emulator.sh:46-51` send SIGTERM only, which a wedged
    client ignores (AGENTS.md).
- **Arguments:** `run-emulator-370.sh:36-38` reads `$2` with no arity check (under `set -u` the user gets
  "unbound variable") and expands `"${srv_args[@]}"` unguarded.
- **Wait loop:** 240 vs 480 iterations.
- **CDN check race:** `package/run-emulator.sh:61` checks the CDN line right after the game line. The server
  prints the CDN line second (`server/app/main.cpp:184,188`), so this can fail.
- **Help text:** `run-emulator-370.sh` says the data is in `~/.local/share/soa-linux`; everything else says
  `soa-linux-370`.
- **Log patterns:** the lines 14 scripts wait on (`soa-server: game`, `soa-server: CDN`) are not in
  `tools/server_log_patterns.txt`.

**Fix:**
- One sourced `scripts/lib/with-server.sh`, modelled on `package/run-port-server.sh`, and one `.ps1` module,
  shipped in the packages too.
- A single "ready" line from the server.
- Add both patterns to the patterns file.

<a id="b1"></a>
#### B1. `-ffp-contract=off` only where a subsystem opts in (M–H, S, risk L)

**Where:** `port/src/native/math/subsystem.cmake:11`, `port/src/native/input/subsystem.cmake:11`.

**What:**
- `arm_float.h` is used in kernel/ and params/ as well, and render, scene, anim and bullet do float work.
- Their bit-exactness holds only because GCC's default x86-64 target has no FMA.
- Any `-march`, clang (whose default is `-ffp-contract=on`) or an AArch64 host would fuse multiply-adds
  silently.

**Fix:** `target_compile_options(soa PRIVATE -ffp-contract=off)` once, which costs nothing on the
baseline. Drop the per-subsystem lines.

<a id="b2"></a>
#### B2. Compile flags copied per target and drifting; layering checks narrower than AGENTS.md (M, S–M, risk L)

**Flag lists:**
- 15 `target_compile_options` lists in 7 variants of
  `-Wall -Wno-unused-parameter [-Wno-unused-function] [-fno-strict-aliasing] [-mcx16]`.
- `soa_env_tests`, `soa_zip_tests` and `soa_gamefiles_tests` get no warning flags at all.
- `tools/movie_check` compiles `runtime/src/frontend/movie_decoder.cpp` a second time with different flags.
- `soa` repeats defines and links it already inherits.
- `_WIN32_WINNT` is defined on two targets.
- Fix: `cmake/flags.cmake` with INTERFACE targets `soa_warnings` and `soa_guest_code`, and a small
  `soaruntime_movie` library.

**Layering checks:**
- Three hand-written loops (`runtime/CMakeLists.txt:46-60`, `platform370/CMakeLists.txt:20-33`,
  `server/CMakeLists.txt:8-17`).
- The server's loop doesn't reject `../` includes, and its prefix list omits `app/`, `platform370/` and
  `soawebview/`.
- None of the three looks at `<...>` includes.
- Nothing checks `common/` (must include nothing of the repository), `webview/`, or "emulator code only
  in emulator/".
- Each target's include path is a backstop, so the practical risk is low.
- Fix: one `soa_check_includes(DIR ALLOW...)` function applied to every library.

<a id="b3"></a>
#### B3. Leftovers of the earlier llvm-mingw Windows toolchain (M, S, risk L–M)

**Where:** [cmake/deps.cmake:84-92](../cmake/deps.cmake#L84), `if(WIN32 AND TARGET fmt)`.

**What:**
- `FMT_CONSTEVAL=` turns fmt's compile-time format checks off.
- A libc++-only `__std_stream` stub and a "clang 23" mcl fix are force-included into dynarmic.
- The Windows build is MinGW-w64 GCC now, so the block is probably dead and costs GCC its format checks.
- 13 other comments still name llvm-mingw, e.g. `server/net/use_httplib.h:3-5` and README "Windows".

**Fix:** guard the block with `CMAKE_CXX_COMPILER_ID MATCHES Clang`, or delete it once a `build-win`
configure without it succeeds. Update the comments.

<a id="b4"></a>
#### B4. `tools/check_no_380.sh`: both too broad and blind in places (M, S–M, risk L)

- **Whole-file exemptions where a marker would do:** `runtime/src/jni/jvm.cpp` (1 hit in 746 lines),
  `jvm.h` (1) and `tests/test_script.py` (3). New references in these files pass silently.
- **The line filter** passes any line that merely names the viewer.
- **The regex misses** `v380` / `SOA_V380` (`tools/common.sh:9-14`, `decomp.sh`, `decomp_at.sh`, <!-- 380-ok: names the pattern under review -->
  `ghidra_apply_types.sh`).
- **The `PENDING` mechanism** has been empty since 2026-10-01.
- **`git grep … || true`** turns a git error into a pass.
- **Real leftovers:**
  - `server/src/api/campaign/master_data.cpp:45` still falls back to the offline master DB at run time,
    behind a marker. It is dead in practice, because `master_source::resolve()` comes first.
  - `port/src/native/README.md:5,72` and `yayoi/README.md:16` still describe the port in its old,
    pre-rebase state.
  - `emulator-viewer/README.md:7` says the port "runs the same library", which is no longer true.
  - `tools/extract.sh` belongs in `emulator-viewer/scripts/`.

<a id="b5"></a>
#### B5. Hand-written HTTP/1.1 client and duplicate socket helpers (M, S–M, risk M)

- **The HTTP client:** [platform370/src/http_370.cpp](../platform370/src/http_370.cpp) is 460 lines.
  - `exchange()` at :247 is 116 NLOC with CCN 47.
  - It hand-writes the request, parses the head and decodes chunked bodies itself, although cpp-httplib is
    already a dependency.
  - `g_user_agent` (:86) is written at :379 and read at :215 and :283 without synchronisation.
- **`connect_to` / `send_all`** are copied in `http_370.cpp:115-152` and `server/net/client.cpp:19-58`, and
  the copies behave differently: all addresses with a non-blocking timeout, versus the first address only,
  IPv4-only.
- **Fix:**
  - Add `soa::sock::connect_tcp` and `send_all` to `common/sock.h`. This is cheap.
  - Consider httplib's streaming client for `http_370`. It must keep `HttpURLConnection`'s observable
    behaviour, hence the medium risk.

#### B6. Smaller build items

- **`cmake/deps.cmake:94-114`** FetchContents jpeg9 and zstd 1.3.4 even for a server-only build. Guard
  them with `SOA_BUILD_PORT OR SOA_BUILD_TOOLS`. vcpkg also installs every port (ffmpeg, SDL2) for a
  server-only build; manifest features could fix that.
- **Options:**
  - `SOA_BUILD_RUNTIME` has no remaining purpose (the bring-up is over).
  - `SOA_BUILD_PLATFORM370` can be OFF only when both PORT and EMULATOR are OFF; derive it.
  - `VCPKG_MAX_CONCURRENCY` gets a default in two places.
- **Boilerplate:** 18 of the 22 `subsystem.cmake` files are 8 identical comment lines. The glob could skip
  missing files.
- **`scripts/build.sh`:**
  - `--release` is recognised only after `--windows`, so `--release --windows` passes `--windows` on to
    `cmake --build`.
  - The final "done" line always lists every program.
- **`run-port.sh:30-35`** doesn't recognise `--server=HOST`.

### Python, control and tests

<a id="t1"></a>
#### T1. `gate.py`: stale tests/diff verdicts, and Ctrl-C doesn't stop queued tests (H, S, risk L)

**Where:**
- [tools/gate.py:94-121](../tools/gate.py#L94) (`run_diff`).
- [gate.py:185-215](../tools/gate.py#L185) (`stop` and the executor).
- `tests/diff/difftest.py:150`.

**What:**
- **The tests/diff verdict:**
  - `run_diff` stores `rc` but never uses it.
  - `ok` comes only from regex matches of `PASS <flow>` lines in `OUT/tests-diff/summary.txt`.
  - `difftest.py` writes that file only at the end, and nothing deletes it first.
  - So with a reused `--out` (TIERS.md suggests `--out /tmp/gate-t2`), a difftest that crashes at import,
    is killed at the 4-hour limit, or dies before writing still reports the previous run's PASS.
- **Interrupting the gate:**
  - `stop()` SIGTERMs the running process groups and calls `sys.exit(130)` from inside
    `with ThreadPoolExecutor`.
  - Leaving the block calls `shutdown(wait=True)` without `cancel_futures`, so futures that hadn't started
    still run.
  - Game tests blocked in `soaslot.acquire()` (a `sleep(2)` loop) aren't in `PROCS`; they start a client as
    soon as a slot frees.

**Why it matters:** a stale PASS defeats T2. An interrupted gate keeps taking machine-wide slots.

**Fix:**
- Delete `summary.txt` before the run, and require `rc == 0` (or `rc == 1` with per-flow FAIL lines).
- Add a cancel `Event` that `run_test` checks before `acquire` and `run_cmd`, give `soaslot.acquire` a
  cancel predicate, and call `ex.shutdown(cancel_futures=True)`.

<a id="t2"></a>
#### T2. Test selection ignores the comparison tools; the comparison itself is untested (H, S–M, risk L)

**Where:** [tools/tests_for.py:300-302](../tools/tests_for.py#L300): everything under `tools/` except
`tools/server_*` counts as "tooling (T0 only)".

**What:**
- **Tools the drivers call at run time, and get no shard when they change:**
  - `tools/compare_packets.py`, the packet comparison behind every tests/diff verdict
    (`tests/diff/compare.py:16`);
  - `tools/schema_inventory.py --check --strict`, the G9 end-state check of every run
    (`control/soadrive/targets.py:889`);
  - `compare_tutorial.py`, `make_test_seed.py`, `contact_sheet.py`.
  - `soa_save/` gets "no rule".
- **`compare_packets.py`** has no unit test, reports PASS on two empty packet logs, and no tier runs the
  `--inject` deliberate-difference check. A comparison that always passed would go unnoticed.
- **tests/diff can drop runs without failing:**
  - `difftest.py:90` silently drops a target whose `Run(...)` raised.
  - `compare.py:63-66` skips every comparison when the emulator's reference run is absent.

**Fix:**
- Add the driver tools to `DRIVERS`, or derive them by scanning `control/` for `tools/*.py`.
- A pytest for `compare_packets`, with a minimum-entries guard.
- A negative control in T1/T2: `tests/diff/run.sh login --inject port-inproc:--start-coins 1000` must FAIL.
- FAIL on a missing target or reference.

<a id="t3"></a>
#### T3. Sessions wait on fixed sleeps, not conditions (H, L, risk M)

**Where:** `control/soadrive/sessions/*.py`, `flows/*.py`.

**What:**
- There are 686 `"wait:NNNN"` commands and 27 waits on the screen or the log.
- Unconditional wait per file: `mastery.py` 182 s, `home.py` 134 s, `flows/tutorial.py` 89 s.
- A typical sequence (`growth.py:95-132`):
  `c("tap:630:330", "wait:4000", s.shot_cmd(...), "tap:364:540", "wait:3000")`, and `"wait:11000"` at :109.

**Why it matters:**
- Under load the guesses are too short, a tap lands on the wrong screen and the session fails; this is the
  20-client failure that control/README.md itself records.
- When the machine is idle, the same guesses waste minutes.

**Fix:**
- Follow `flows/mission.py` `start_mission`: after each navigation tap, wait for a predicate (a
  `port_debug: phase N` log line, a `popups.is_*` fingerprint, `screens.settled_shot`).
- Add `tap_to_phase` and `tap_to_screen` helpers to `sessions/common.py`.
- Convert the worst sessions first.

<a id="t4"></a>
#### T4. Gate scripts that read output instead of exit codes, or fail open (M, S–M, risk L)

- **`tools/check_server_docs.sh:48-57`** ignores `server_evidence.py`'s exit status and greps stdout.
  `[ "${agents:-0}" = 0 ]` passes if the line is renamed or missing.
- **`check_server_docs.sh:74-76`:** a single `Evidence removed:` line in REV..HEAD waives every evidence
  loss in a multi-commit range.
- **`port/scripts/selftest_resilient.sh:24-35`** decides from grepped summary lines and ignores the final
  boot's `rc`, so a crash after the summary passes.
- **`tools/check_thread_local.py:99-105`** skips missing programs; it passes with `nprog == 0`.
- **`tools/tests_for.py:63-75`:** `--regen` with a broken server writes an impact map with zero APIs.

**Fix:**
- Exit codes or `--json` from `server_evidence.py`.
- Require `rc == 0` on the last selftest boot.
- Fail on `nprog == 0` and on an empty API list.

<a id="t5"></a>
#### T5. Two interpreters, no packaging, copied helpers (M–H, M, risk M)

**Two interpreters:**
- Session wrappers and `tiers.json` checks run the system `python3`; pytest and `requirements.txt` use
  `.venv`.
- The workarounds this causes:
  - re-execs into `.venv` (`targets.py:193,849`, `summer_demo.py:109`, `server_replay_record.py:72-76`);
  - an `nm -D` fallback in `soadrive/gdb.py:74`;
  - guarded lazy imports.

**No packaging:**
- 81 `sys.path.insert` calls in 72 files, about 50 repo-root definitions in 3 spellings.
- No `pyproject.toml`, `conftest.py` or pytest config; unpinned requirements.

**Copied helpers that have drifted:**
- `TIME_COL` in `tools/compare_tutorial.py:229` ("as control/soadrive/state.py") lacks `_until$|^expire`,
  so expiry columns produce false differences.
- Screenshot RMSE is copied three times, each shelling out to ImageMagick (`screens.py:25`, `smoke.py:56`,
  `compare_tutorial.py:212`). The error values differ (1.0 vs None), and ImageMagick is an undeclared
  system dependency, while Pillow and numpy are already requirements.
- `free_ports` is copied twice (`proc.py:24`, `winhost.py:135`). Both race the server's bind; only Windows
  retries.
- 15 sessions open the master DB read-only and never close it.

**Fix:**
- One interpreter (a `tools/py` shim, or `.venv/bin/python` everywhere).
- A `pyproject.toml` that installs `soa_save`, `soadrive` and a small shared `soatools` (repo root, master
  DB, codecs, rmse) in editable mode.
- A pytest config, and pinned versions or a constraints file.
- Then delete the workarounds.

<a id="t6"></a>
#### T6. Unused a2c generator suite and a stale inventory, about 7,000 lines (M, S, risk L)

**What:**
- `port/src/native/README.md:177` already says the a2c generators are "kept as tools only; nothing in the
  tree uses their output".
- The unused code:
  - `tools/a2c.py`, 1,457 lines (`translate()`: 1,110 NLOC, CCN 612);
  - 14 `tools/gen_*_a2c.py`, `gen_{loader,parameter,containers}_tables.py`;
  - `tools/*_funcs.txt`, `objbase_verified.txt`, `models_readable.py`.
- `tools/rebase_inventory.py:392-416` lists about 30 generated files, and 27 of them no longer exist.
- AGENTS.md still says to "regenerate (… existing a2c fallbacks)".

**Fix:** the user decides whether to delete them or move them under `docs/history/`. Either way, fix the
inventory table and the AGENTS.md wording.

#### T7. Smaller Python and test items

- **`Run.stop()`** ([control/soadrive/targets.py:526-529](../control/soadrive/targets.py#L526)) sends
  `quit` and waits 15 s even when the client is known dead or the FIFO has no reader.
  - That costs 25 s per failing run.
  - It is 25 s of T0's ~45 s pytest-control step (measured: `test_a_host_gpu_failure_is_named…`).
  - Fix: skip the quit when `self.death` is set, or when nobody is listening on the FIFO.
- **`control/tests/test_soaslot.py`:**
  - :19-38 asserts after fixed `sleep(1)` and `sleep(0.8)`;
  - :39-48 pops `SOA_SLOTS` and `SOA_SLOT_DIR` from the user's environment.
  - Fix: poll with a deadline, and use `monkeypatch`.
- **Screenshot completion** is detected by mtime plus `sleep(0.2)` (`control/soadrive/fifo.py:81-85`),
  because `common/src/png.cpp:40-47` writes in place. Write to a temporary file and rename it.
- **Doc counts that drifted:**
  - `control/README.md:88` says `N = 12 (DEFAULT_SLOTS)` and `tests/TIERS.md:9,158` say "12 slots";
    `control/soaslot.py:59` has 15.
  - `TIERS.md:7` gives the selftest boot as 92 s; `tiers.json` has 70.
  - `soa_save/README.md:3` says the port doesn't need soa_save; the drivers use it.
- **Ruff, real but minor:** 14 unused imports, 2 unused variables, 2 `if False` ternaries, 3 swallowed
  exceptions (`soadrive/gdb.py:83`, `soa_save/script.py:152`, `server_replay_record.py:93`).
  - `gdb.py:33-43` reports any ImportError as "not in this checkout".
- **About 40 environment knobs** in the drivers (`NEWPLAYER_NAME`, `CAMPAIGN_SEED`, `FLOW_MAX_RMSE`, …),
  against "settings as flags". Move them to argparse options.
- **`targets.Run.start`** is 186 NLOC with CCN 99 (3 targets × Linux/Windows × launcher). Split it into a
  strategy per target.
- **`tests/test_kvs.py:73` and `test_script.py:32`** skip in every worktree, because their input lives
  only in the main checkout. Agents' T0 runs never execute them.
- **Two KVS codecs** (`soa_save/kvs.py`, `server/src/state/kvs.cpp`) have no shared test vectors.

### Documentation that contradicts the code

Collected from all areas. Each fix is small.

- **The natives count (P1)** and the a2c references (P3, T6).
- **Server counts:**
  - `server/ARCHITECTURE.md:11-12,56,99` gives 40 + 125 methods and 32 + 78 registrations.
    `API-INDEX.md` says 187 (44 + 143).
  - `server/README.md:342` says 91 tests; there are 172 `NATIVE_TEST`s.
  - `server/README.md:88` says 93 unhandled APIs; unimplemented-apis.md says 12.
  - `ARCHITECTURE.md:118` says 54 tables; the state README says 59.
  - Fix: generate the numbers or drop them (`tools/server_index.py`, `check_server_docs.sh`).
- **soanet:** `server/README.md:32` and `net/README.md` say soanet is linked by soa-server only. The port
  links it (`port/CMakeLists.txt:67`) and includes `net/wire.h`. Its PUBLIC include dir is all of
  `server/`.
- **Finished plans still in `server/`:**
  - `server/PLAN-readability.md:3` says "in progress" but its summary says "All done".
  - `server/PLAN-schema.md:5` says "plan only" at schema v21.
  - AGENTS.md says finished plans go to `docs/history/`.
  - (CR7, 2026-10-07: both moved to `docs/history/`, with `control/PLAN-consolidate.md`.)
- **README.md build sections:**
  - the vcpkg list omits ffmpeg, msgpack, cpp-httplib and cli11;
  - the subdirectory list omits common/, webview/, tests/cli and tools/movie_check;
  - the options list omits WEBVIEW, TOOLS and RUNTIME;
  - "Packaging" lists two zips, but `tools/package.py:68` builds three kinds;
  - posix_compat is force-included into every target that links `soa_compat`, not only "the server's and
    the runtime's".
- **"Builds only X" claims** in `emulator/README.md`, `emulator-viewer/README.md` and `server/README.md:38`
  are false while VIEWER, WEBVIEW and TOOLS default ON.
- **platform370:**
  - `platform370/CMakeLists.txt:3` and `platform370.h:20` say "soa will link it"; it already does.
  - `platform370/README.md:122` cites a removed `h_find_global_string`.
  - "one" vs "two" native patches between `platform370/README.md` and `emulator/README.md`.
- **The `vcpkg.json` `$comment`:**
  - it says the fonts come from the system; they are built in;
  - it says four programs; there are five;
  - it omits zstd 1.3.4 from the FetchContent list;
  - its `--windows` sentence is stale.

## What's in good shape

- **Layering:**
  - `server/` and `runtime/` include nothing above them. Configure-time checks enforce this, and narrow
    include paths back it up.
  - The port reaches the server only through `server/include/soaserver/`.
  - `common/` includes only itself.
- **One implementation per library concern:** ZIP (minizip-ng), Base64 (OpenSSL EVP), prefs XML (pugixml)
  and PNG (stb). Each has unit tests, and the server, runtime, viewer and tools all use them.
- **Warning hygiene:**
  - `-Wall` on every main target.
  - The `-Wextra` scratch build produced 166 warnings, almost all in tests or GCC false positives.
  - The runtime passes `-Wunused-function` and `-Wunused-variable` with 0 hits.
  - No `catch(...)` in the runtime.
- **The server after the readability and schema plans:**
  - short handlers (none in lizard's top 10) and 0.56% duplication;
  - typed ids and `ServerTime` / `EventTime`;
  - bound SQL only; no user value is ever interpolated;
  - STRICT tables with foreign keys;
  - versioned migrations with fresh == migrated tests;
  - (a)–(d) labels enforced in T0;
  - 170 of 187 APIs covered by accepted replay corpora, with byte-identical replay diffs for refactors.
- **The natives:**
  - no C++ `virtual` in recovered classes, and vtables kept as guest data per VIRTUALS.md;
  - `static_assert`ed layouts and very few raw offsets in the scaffolded subsystems;
  - 236 differential `NATIVE_TEST`s, with a test in every subsystem;
  - a deterministic, documented registration order.
- **Settings and environment:** one `RunOptions` per program, CLI11 everywhere with a T0 test, and
  `soa/env.h` with a table of removed variables. Only 4 raw `SOA_*` getenvs remain, all diagnostics or
  test switches.
- **Per-thread state:** the `thread_local` policy is enforced (`check_thread_local.py`), with `ThreadRecord`
  ownership and stack-overflow and crash reports per thread.
- **The test infrastructure:**
  - `tiers.json` is the single source, and the TIERS.md table is generated from it;
  - test selection runs from an impact map that has its own tests;
  - the slot pool uses flock (no stale locks), with a memory floor;
  - fail-fast `Run.alive()` names the cause;
  - the G9 end-state check runs on every session;
  - `test_requirements.py` keeps `requirements.txt` complete;
  - every pytest test asserts something.
- **Build reproducibility:**
  - the `SOA_BUILD_SH` configure gate;
  - the fixed Windows PATH for the vcpkg cache keys;
  - FetchContent pinned by SHA-256;
  - the MinGW constructor order handled explicitly and gated;
  - the package allow-list and game-file scan.

## Metrics (at `9df7884`)

**Size (our code):**

| Area | Lines | Note |
|---|---|---|
| `port/src` | 52k | 41.5k NLOC |
| `server/` | 45k | |
| `tools/` | 26k | |
| `runtime/` | 19k | |
| `control/` | 10k | |
| `common/` | 3k | |
| `webview/` | 2k | |
| `platform370/` + `emulator/` + `emulator-viewer/` | 3.5k | |
| `tests/` + `soa_save/` | 3.4k | |

**Largest files:**
- `server/src/state/schema_tests.cpp` 2,351
- `schema.cpp` 2,138
- `render_layout.h` 1,761
- `fakeapi.cpp` 1,646
- `tools/rebase_inventory.py` 1,576
- `tools/a2c.py` 1,457
- `live_check.cpp` 1,300
- `cpu.cpp` 1,157
- `host.cpp` 1,043

**Most complex functions (CCN; production code, tests excluded):**
- `a2c.translate` 612
- `rebase_inventory.main` 400
- `schema_inventory.main` 177
- `live::check` 129
- `verdiff.main` 127
- `ASON::UnpackMessagePack` 119
- `targets.Run.start` 99
- `gdbstub Session::handle` 89
- `format_impl` 78
- `app::run` 74
- `rules::npc_status` 51

**Duplicate code:** lizard reports 0.56% duplication in `server/`; pylint symilar reports 0.32% in the
Python code (most of it in the unused generators). Most of the copies listed in this review are
reimplementations with different code, which a textual duplication finder can't see.

**Other counts:**
- Raw `SOA_*` getenvs outside `soa/env.h`: 4.
- `fatal` / `abort` / `_exit` in non-test runtime code: about 40, mostly emulator invariants.
- Fixed `wait:N` in sessions: 686, against 27 condition waits.
- `sys.path.insert` in Python: 81.

## Proposed follow-up plan

These are batches that could become agent tasks, in the suggested order. None is queued: the user picks.
They are additive to the existing plan:
- Task H already decided the server hooks, so [P7](#p7) is a question for the user rather than a batch.
- Anything that rewrites natives' code belongs to N.
- B5 is the natives *framework* only, and is suggested before Wave A so the waves build on it.

| # | Batch | Findings | Effort | Why this position |
|---|---|---|---|---|
| **CR1** | **Gate integrity** | [T1](#t1), [T2](#t2), [T4](#t4), T7 (`Run.stop`, `test_soaslot`, slot-count docs) | S–M | Every later batch is proven by the gate; a stale PASS or a fail-open check undermines all of them. Pure tooling, no game code. |
| **CR2** | **Server state integrity** | [S1](#s1), [S2](#s2), [S3](#s3), S6 (`stoull`, `ctx.now()`, `call_once`) | M | Silent partial writes corrupt saves. Proven by replays plus new unit tests; one server agent. |
| **CR3** | **Runtime thread safety and Windows libc** | [R1](#r1), [R3](#r3), [R2](#r2) | M | Undefined behaviour under the JIT's threads; small and local. R2 needs the Windows tests (`win:*`). |
| **CR4** | **Shared codecs and checkout lookup** | [X1](#x1), [X2](#x2), [X3](#x3), [B5](#b5) socket helpers | M | Shrinks the surface N and the tools work on; lands in `common/` and `soa_save/` first, then the callers switch. |
| **CR5** | **Natives framework before Wave A** | [P1](#p1), [P2](#p2), [P3](#p3), [B1](#b1), P8 (`--check` for gen/, getenv lint, `kRebaseSkippedHooks`) | M | Wave A will add hundreds of natives; it needs the `--natives` A/B, a library check, a single address table and FMA-safe flags first. P3 simplifies `live::check`, which every wave uses. |
| **CR6** | **Build hygiene** | [B2](#b2), [B3](#b3), [B4](#b4), B6, R7 (`posix_compat` macros, viewer-only Play Core classes to `emulator-viewer/`) | S–M | Independent of the others; needs a `build-win` run. |
| **CR7** | **Docs sweep** | the "Documentation" list, finished server plans to `docs/history/`, generated counts | S | Cheap; best right after CR4–CR6, which change some of the same text. |
| **CR8** | **Python packaging and shared helpers** | [T5](#t5), [T6](#t6) (the user decides delete vs history), T7 leftovers | M | After CR1 (the gate scripts move) and CR4 (the Python codecs land in `soa_save/`). |
| **CR9** | **Condition waits in sessions** | [T3](#t3) | L | One session per commit, the worst first; can run in the background alongside N, using few slots. |
| **CR10** | **Structural splits (opportunistic)** | [R4](#r4), [R5](#r5), [R6](#r6), R7 (`host.cpp`), [S4](#s4), [S5](#s5), S6 (`npc_status`, wire JSON), [P4](#p4)–[P6](#p6) | L | Valuable, but none is urgent. P4–P6 fit into N's subsystem work (fakeapi with the api subsystem); R4's header move is mechanical and conflicts with every open branch, so do it when few branches are open. |

Questions for the user:

1. **P7:** should the port's `h_end_mission_talk` go through `server::answer` (task H's area)?
2. **T6:** delete the a2c generators, or move them to history?
3. **R7 / B4:** move the Play Core classes and `tools/extract.sh` into `emulator-viewer/`?
