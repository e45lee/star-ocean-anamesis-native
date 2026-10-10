# Readability review, 2026-10-10

An organization and readability review of the whole codebase. This review proposes changes only; it made none.
It does two things:
- checks how far the follow-ups of [code-review-2026-10-06.md](code-review-2026-10-06.md) (CR1–CR10) have got;
- adds the readability problems that review did not list.

The correctness findings of the same day are in [code-review-2026-10-10.md](code-review-2026-10-10.md).

- **Commit reviewed:** main `7016c92`. Every `file:line` refers to that commit.
- **Method:**
  - Five reviews: the status of CR1–CR10; `server/`; `runtime/` + `common/` + `webview/` + `platform370/` +
    `emulator/` + `emulator-viewer/`; `port/src`; Python, shell and CMake.
  - Tools: lizard (complexity and duplication), vulture, ruff, and grep counts, all from a scratch venv.
    `requirements.txt` is unchanged.
  - Every finding was confirmed by reading the code. Generated code, `port/decomp/` and third-party code are
    left out.
  - Nothing was built: the session's network refused the vcpkg downloads. The proofs named below are
    therefore still to run.
- **Ratings:** **Effort** is S (hours), M (a day or two) or L (several days). **Risk** is the risk of the change.
  Every batch says how to prove it safe.

## 1. Status of the 2026-10-06 follow-ups

| Batch | Status | Evidence / what is left |
|---|---|---|
| CR1 gate integrity | Done | `tools/gate.py` deletes the stale summary and checks exit codes; `check_server_docs.sh` and `selftest_resilient.sh` decide on exit codes |
| CR2 server state | Done | Failed SQL rolls the request back and refuses it with 10208 (`server/src/core/server.cpp:153-191`); `Server::transact` checks begin and commit |
| CR3 runtime threads, Windows libc | Done | JNI `MethodImpl` is an atomic `shared_ptr`; the class map and the warned set are locked; `core/linux_errno.cpp` exists |
| CR4 codecs, checkout, launchers | Done; small leftovers (L1) | One C++ implementation each of CHash32, ADLD and SLZ (`common/`), and one Python each (`soa_save/`) |
| CR5 natives framework | Done | `-ffp-contract=off` covers the whole port; 17 `addresses.txt`; live-check's largest function is CCN 33 (was 129) |
| CR6 build hygiene | Done | `cmake/flags.cmake`, `soa_check_includes` |
| CR7 docs sweep | Done; one stale doc | `port/REMAINING.md:5` still says "301 natives" |
| CR8 Python | Mostly done; leftovers (L2) | `sys.path.insert` down from 81 to 23 |
| CR9 condition waits | Done for sessions and flows | About 62 commented `wait:N` remain in `control/`; about 57 fixed sleeps remain in tiered shell scripts (L3) |
| CR10 structural | Partly done | Done: R4–R6, S4–S6 (server rewards), P4–P6. Open: R7 (the `host.cpp` split) and R6's `_exit(0)` (`runtime/src/app/host.cpp:1042`) |

**Leftovers in the "done" batches:**
- **L1 (from CR4):**
  - `tools/server_cdn_check.sh:27-40` has a fourth CHash32, written in a Python heredoc.
  - `find_db` is defined twice: `tools/extract_banners.py:55` and `tools/make_standin_banners.py:418`.
  - `WSAStartup` is called in 3 places: `common/src/sock.cpp:47`, `runtime/src/hle/libc_misc.cpp:190` and `runtime/src/hle/net_win32.cpp:37`.
  - `webview/tools/render.cpp:92` writes its own PNG instead of calling `soa::png_write`.
- **L2 (from CR8):**
  - 18 driver settings are read from environment variables (`CAMPAIGN_SEED`, `FLOW_MAX_RMSE`, `NEWPLAYER_NAME`, …), against the rule that settings are flags.
  - `targets.Run.start` is CCN 94 over 214 lines.
  - Screenshots are written in place, and `control/soadrive/fifo.py` polls their mtime with a 0.2 s sleep.
  - The two KVS codecs have no shared test vectors.
  - `.venv/bin/python` is still called directly in `control/soadrive/targets.py:865`, `tools/common.sh:5` and `port/scripts/phone370.sh:121`.
- **L3 (from CR9):** the shell scripts with fixed sleeps are `profile_extra.sh` (17), `nier_demo.sh` (11), `debug_session.sh` (9), `debug_input_session.sh` (9), `smoke_vs_emu.sh` (7) and `phone370.sh` (4).
- **L4 (from R4):** four mutable globals are still declared in public headers: `g_log_level`, `g_prof_enabled`, `g_gdb_enabled` and `t_map_overwrites`.

## 2. Proposed batches

The batches are ordered by value for the effort. Batches RB1–RB7 are small, low-risk changes that each fit in
one commit or a few. RB8–RB13 are larger. In each table, **where** is a path with a count or `file:line`, and
**change** is what to do.

### RB1. Dead code and stale docs (S, risk none–L)

| Where | Change |
|---|---|
| Server: `handle(fid, file, out)` (`server/include/soaserver/server.h:109-111`, `server/src/core/server.cpp:355`) | Delete. It was "kept for one merge wave" since R9 and has 0 callers. |
| Server: `Pools::all_units` (`server/src/master/gacha_pools.h:97`), `Scratch::inputs_missing` (`server/include/soaserver/scratch.h:25`) | Delete; both are unused. |
| Port: `fbits` (`port/src/native/particles/particles_world.cpp:22`), `ElementDeserializeEntry` (`params/params_element.cpp:250`, "for the tests", but no test uses it), `ACall::fcall` (`common/live_check.h:239`) | Delete; all unused. |
| Runtime: `g_atexit_mutex` (`runtime/src/hle/libc.cpp:145`) | Delete; unused. |
| Runtime: `arg<T>()` (`runtime/include/soaruntime/core/abi.h:128`) has 0 users, yet runtime/README.md "HLE imports" tells authors to use it. About 340 thunks read raw `c.x(i)`. | Either use it in new and touched thunks, or delete it and fix the README. |
| Docs | `port/REMAINING.md:5` ("301 natives"). runtime/README.md: "will link platform370", "x86-64 Linux" and "soaruntime_app for soa and soa-emu" (the viewer uses it too). platform370/README.md:3 ("the offline build's import lists"). `server/src/README.md:9` (the SQLite wrapper is in `state/sql.cpp`). `server/README.md:29` ("the core APIs" moved to `api/` in R8). |

**Proof:** T0, and `soa --list-native` unchanged.

### RB2. Server naming and small shared helpers (S, risk none)

| Where | Change |
|---|---|
| `ErrorCode::kItemUnusable` (10208, "the server's generic refusal", `server/src/core/errors.h:17`) is used about 110 times, mostly where nothing is about items | Have `tools/gen_error_codes.py` emit an alias `kRefused = 10208`; use it wherever the meaning is generic. |
| `select count(*) from presents where received_at is null` is written out in 8 handlers besides `presents.cpp` | One `unreceived_presents(ctx)`, next to `add_present`. |
| `social/rental.cpp:142` `kReasonRentalBonus = 3` | Use `ext::kPresentAchievement`. |
| `ext::Sql master{ctx.m.h}` copies of the handle (`presents.cpp:24`, `gacha.cpp:42`, `box.cpp:125`, `player_info.cpp:166`) | Use `ctx.m`. |

**Proof:** byte-identical replays (`tools/server_replay_diff.sh`), T0 `generated`.

### RB3. One ETC2/EAC decoder (S–M, risk L)

`runtime/src/hle/etc2.cpp` (170 lines) and `common/src/aska_image.cpp:203-340` each carry the same spec tables
(C.10, C.14, C.16) and the same block decoder.
- **Change:** keep one decoder in `common/`, as `soa/etc2.h`. Start from the runtime's, which cites the
  spec. Have `aska::decode_block` call it.
- **Proof:** the selftest `hle/etc2-vs-host`, `aska_image_tests`, the english_art selftests, and `aif2png`
  output byte-identical over the download.

### RB4. Leftovers L1 and L4 (S, risk L)

- **L1 changes:**
  - `server_cdn_check.sh` calls `soa_save.adld.chash32` through `tools/py`.
  - One `find_db`.
  - One `soa::sock::startup()`.
  - `render.cpp` calls `soa::png_write`.
- **L4 change:** the four globals become accessor functions.
- **Proof:** T0, `server_cdn_check.sh` listing the same paths, and the Windows build.

### RB5. Find your way around `tools/` (S, risk L)

| Where | Change |
|---|---|
| 169 tracked files, 97 of them top-level scripts, with no index; the groups show only in name prefixes (26 `gen_*`, 11 `server_*`, 7 `check_*`) | Generate `tools/README.md` from each script's first docstring line, grouped by prefix, with libraries marked. Add a pytest that every script has a header and an index entry. |
| 8 scripts with no usage line; 20 headers that say `.venv/bin/python tools/X.py` | Add usage lines; write `tools/X.py`, which runs through `tools/py`. |
| Five self-described "History tools" (`verdiff.py`, `verdiff_index.py`, `verdiff_decomp.sh`, `restore370_audit.py`, `rebase_inventory.py`; 3,352 lines). `restore370_audit.py --emit` targets a file that no longer exists. They need 5 exceptions in `tools/check_no_380.sh`. | Move them to `tools/history/`, which needs one exception. |

**Proof:** `check_no_380.sh`, pytest, T0.

### RB6. Port: use the helpers that already exist (S each, risk L)

| Where | Change |
|---|---|
| `info/info_map.cpp:51-56` declares its own `InfoMapTree`; raw `+0x20` / `+0x28` reads; the successor walk is copied 3× (`info_infobase.cpp:112`, `info_map.cpp:147`, `info_class.cpp:51`) | Use `libcxx::tree<pair<K,T>>` and `tree_next` (`libcxx/libcxx_layout.h:230`). |
| Raw property offsets in `info_infobase.cpp:103-110`, `master/master_compare.cpp:27-32` and `info_class.cpp:232`, and the `p += 0x28` walk in `master_simple.cpp:261` | Cast to `CParameterPropertyBase/Value` (`params_layout.h:97-162`) and `yayoi::QueryParam` (`yayoi_layout.h:84-93`). |
| Five copies of `guest_assert`: `sync_mutex.cpp:50`, `info_guest.cpp:14`, `params_guest.cpp:29`, `memory_pools.cpp:30,67` | Call `common/guest_assert`. |
| `guest_call` to other subsystems' natives: `audio/audio_3d.cpp:31,55,94,117` → math; `info_guest.cpp:26-41` and `info_map.cpp:65` → memory. CALLS.md's reason for waiting expired when that work merged on 2026-10-08. | Use `NativeCallee` / `memory::kStlAllocateCallee`, and update CALLS.md. |
| `math/math_constants.h:8-43`: 16 hard-coded rodata vaddrs | Move them to `math/addresses.txt` (`at 0x… f32 ref SYMBOL`). |

**Proof:** the affected selftests, `--live-check info,master,params,math` at 0 mismatches, and `soa --list-native` unchanged.

### RB7. Runtime file organization (S each, risk L)

| Where | Change |
|---|---|
| `runtime/src/hle/gles.cpp:188-578`: about 390 of its 945 lines are the `SOA_GL_*_DUMP/PROBE` diagnostics (`draw_probe` alone is CCN 47) | Move them to `hle/gles_capture.cpp`. |
| Logging (`g_log_level`, `log_write`, `fatal`) is defined in `core/hle.cpp:12-37` | Move it to `core/log.cpp`. |
| Two mkdir-p implementations: `core/vfs.cpp:77` (logs every component at INFO) and `soa::make_dir_tree`. The viewer has its own `is_dir` / `parent` (`emulator-viewer/src/main.cpp:54-62`). | `make_dirs` calls `make_dir_tree`; the viewer uses `install::`. |
| sysconf and syscall dispatch written twice with bare numbers (`libc_misc.cpp:53-99`, `libc_win32.cpp:463-579`) | `hle/bionic_abi.h` with named constants; one dispatcher. |
| `emulator/src/main.cpp:78-82` and the viewer copy every `args.` field into locals (left over from before CLI11). About 9 unused includes in emu. User errors call `fatal()` (viewer ×8, emu ×2). | Use `args.x`; prune the includes; print and return 2. |

**Proof:** runtime tests, the selftest, and builds on Linux and Windows. For gles: one `SOA_GL_DRAW_DUMP` run diffed before and after.

### RB8. Server request plumbing (M, risk L)

- **Refusals:**
  - Of 148 `refuse` / `refusef` calls, 81 name the method by hand. Two name the wrong method:
    `items.cpp:206` (ItemCompose for ItemComposeArray) and `items.cpp:308-337` (ItemGradeUp for
    ItemGradeUpArray).
  - The two functions also take their arguments in different orders.
  - **Change:** store the method in `RequestContext`, then `refuse(ctx, code, why)` and `refusef(ctx, code, fmt, …)`.
  - The log changes only for the two Array variants.
- **Arguments are read four ways:** hand-written structs in `core/request_args.h` (23), generated structs
  in `api/gen/request_args.h` (17, the only ones checked against the wire), the deepspace / sphere211
  structs (7), and file-local structs with hand indexing (21 in 11 files).
  - **Change:** move them all into `request_args.txt`.
  - `gear.cpp:382,596` decide by argument count, which needs a small generator feature.
- **"Can afford, then pay"** is repeated at about 12 sites (growth, mastery, items, gear).
  - **Change:** promote `growth.cpp`'s `ItemCost` / `take_cost_items` (lines 83-109) to `core/wallet`, keeping
    each site's reason text.
- **Weighted draws:**
  - Five hand-written loops sit beside `rules::weighted_pick`: `gear.cpp:177,266,719`, `favor_drop.cpp:88`
    and `premium_and_favor_bonus.cpp:197`.
  - Five hand-written percent rolls: `growth.cpp:214`, `items.cpp:258`, `gear.cpp:748,784` and `gacha.cpp:243`.
  - **Change:** `ext::draw_weighted` and `ext::chance_bp`. Each must draw exactly one RNG value, and only when
    the sum is above 0, so the RNG sequence stays the same.
- **`include/soaserver/ext.h` (313 lines)** mixes the module API with services that modules implement:
  achievements, subscriptions and present texts.
  - **Change:** move those to their modules' headers, and keep `ext.h` to the registry and `Ctx`.

**Proof:** seeded replays byte-identical, the server selftest, T0 `generated`, and `server_doc_coverage` clean.

### RB9. Port: one guest-access header (M, risk L)

This extends P8 of the 2026-10-06 review; the problem has grown since.
- **The helpers, copied per subsystem:**
  - 12 local vaddr→pointer helpers (`at`, `guest`, `Str`, `global`, `guest_at`, `guest_var`, `fconst`);
  - 10 vtable-slot helpers;
  - 6 `vcall` helpers;
  - 8 copies of the test helper `vtable_of` (P8 counted 2);
  - `sym("_ZTV…") + 0x10` 50 times (P8 counted 27);
  - near-identical `g::` namespaces in info, master and params.
- **The STL allocator fallback:** `if (kStlAllocateCallee.direct()) … else guest_call/out_call` is written 5
  times (`common/guest_std.cpp:27`, `params_guest.cpp:70`, `master_guest.cpp:15`, `master_hash.cpp:23`,
  `libcxx_string.cpp:31`).
- **Change:**
  - `native/common/guest_access.h` with `guest_global<T>`, `rodata<T>`, `vtable_of`, `vslot`, `vcall` and a
    cached `ztv(sym)`;
  - `stl_allocate` / `stl_free` in `memory_callees.h`, with the out-call policy as a parameter;
  - migrate one subsystem per commit.
- **Proof:** the full `--selftest`, `--live-check` on each touched family at 0 mismatches, and
  `soa --list-native` unchanged.

### RB10. The hosts (M, risk L–M)

- **Finish R7 (`runtime/src/app/host.cpp`, 1,043 lines):**
  - `app::run` is 228 lines at CCN 74. Split the file into window/input, the control channel, scripted
    actions and the main loop.
  - `app::run` returns an exit code instead of calling `_exit(0)`.
- **One 3.7.0 install lookup:**
  - `port/src/main.cpp:151-176` and `emulator/src/main.cpp:88-117` each look for the APK and the library,
    and they have drifted: the library precedence is reversed between them.
  - Both spell out the APK name, although `install::kApk370Name` exists.
  - **Change:** one `install::resolve_370(roots, data_dir, &apk, &lib, &err)`.
- **Port `main()`:** 279 lines at CCN 78. Split out named steps: server mode, library, natives set, data dir.
- **Proof:** `soaruntime_tests`, `tests/cli`, the selftest, a T1 session each on soa, soa-emu and soa-viewer
  (from a checkout and from a release stage), and the `win:*` tests.

### RB11. Split the largest functions (M each, risk L; when next touched)

Each is a commented pipeline or a dispatcher whose pieces can be named.

| Function | Size | Split into | Proof |
|---|---|---|---|
| `gltf::write` (`tools/asf2gltf/gltf_writer.cpp`) | 1,003 lines, CCN 459: the largest in our C++ | node, mesh, skin, animation and material emitters | glTF output byte-identical, `tests/test_gltf_viewer.py` |
| `server/src/state/schema.cpp` | 2,138 lines | one file per migration step (`state/migrations/`) | fresh == migrated test, replays, `schema_inventory` |
| `Session::handle` (`runtime/src/core/gdbstub.cpp:527`) | CCN 89 | one handler per packet | `gdbstub_test`, `control/tests/test_gdbclient.py` |
| `format_impl` (`runtime/src/hle/format.cpp:63`) and `strftime_c89_format` (`:383`) | CCN 78 and 76 | one handler per conversion | the HLE format selftests |
| `load_image` (`runtime/src/core/loader.cpp:129`) | 170 lines, CCN 80 | segments, dynamic, exports, relocate, init | `loader/rejects-bad-files`, selftest |
| `maybe_wrap` (`platform370/src/text_370.cpp:898`) | CCN 89; the file is 1,316 lines with five features | a pure, unit-tested `choose_fit`; the file split by feature; `text::` internals out of `platform370.h` | `platform370/lang`, `lang_test.cpp`, English-mode shots |
| Live-check harnesses: `yayoi_sqlite_live.cpp:224` (CCN 93), `scene_check.cpp:143` (80), `particles_world.cpp:288` (51), `kernel_dispatcher_check.cpp:333` (50) | — | snapshot / run / compare; one `diff_bytes` (3 copies today) | same live-check counts |
| `server/app/main.cpp` `main` | CCN 45 | `run_english_dump`, `run_cdn_check`, `serve` | `tests/cli`, replays |
| Python: `schema_inventory.main` (CCN 177; also the state check every session runs), `check_download.check` (113), `remaining.py` (96), `profile_report.py` (83), `rebase_inventory.py` (397) | — | split by section; argparse subcommands; the state check as its own module | `--update` byte-identical, pytest |
| `tests/cli/legacy.cpp` (`parse_soa` CCN 107): the old parsers kept as a test oracle, which feature commits still edit | — | golden expectations in `cli_tests.cpp`; delete legacy.cpp | `tests/cli` |

### RB12. The Python driver layer (M, risk L–M)

- **`packets.log` is parsed 4 ways:** `compare_packets.py:63`, `server_replay_record.py:40`,
  `compare_tutorial.py:99` and `tests_for.py:133`. Its format (`server/net/packet_log.h`) is missing from
  `tools/server_log_patterns.txt`.
  - **Change:** one `packetlog` reader, tested on lines the server writes, and add the format to the
    patterns list.
- **29 session wrapper scripts:** the `port/scripts/*_session.sh` files are each 9–14 lines that run
  `control/run.py NAME`.
  - Five have different names from their sessions (e.g. `restore_session` runs battle-gacha).
  - `tests_for` links a test to its session only through these wrappers, so the two tiers that call
    `run.py` directly are matched against `run.py`'s text.
  - **Change:** have `tiers.json` call `control/run.py NAME`, have `tests_for` map by session name, and
    remove the wrappers.
- **The emulator's bash test library:** `nier_demo.sh` (529 lines), `standin_fetch_test.sh`,
  `lang_fetch_test.sh` and `emulator_boot.sh` copy 11 helper functions between them, and each waits for the
  server itself.
  - **Change:** make them soadrive sessions with `TARGETS = ("emu",)`, as `summer_demo` already is. As a
    fallback, share one `emulator/scripts/lib.sh`.
- **`control/flowctl.py`:**
  - It parses positional optional numbers (`tap-until F L RE 90 10 6`).
  - Usage errors exit 1, the same status as a timeout.
  - **Change:** argparse subcommands with `--timeout`, `--every` and `--tries`, accepting the old form for
    now; exit 2 on usage errors.
- **Leftovers L2 and L3:**
  - the 18 driver environment variables become options;
  - `Run.start` becomes one strategy per target;
  - screenshots are written to a temp file and renamed, and `fifo.py` waits for the rename;
  - the shell scripts with fixed sleeps move onto sessions or `flowctl` waits.
- **Proof:** pytest-control, `tests_for` giving the same selection on sample paths, T1, and the emu tiers
  before and after.

### RB13. The server's English pipeline in one place (M–L, risk L)

- **Where it is now:** about 3.8k lines over `master/english_derive.cpp` (1,091 lines),
  `master/english_text.cpp`, `cdn/english_tables.cpp`, `cdn/story_en.cpp`, `make_english_master` in
  `cdn/served_master.cpp`, and `english_art/`. `server/src/README.md` describes `master/` as read-only
  master data.
- **The longest functions:**
  - `english_art/build.cpp` `build()`: 179 lines, CCN 61;
  - `labels.cpp` `Walker::object`: CCN 58;
  - `english_derive.cpp` `derive`: CCN 46.
- **Change:** one `server/src/english/` folder, and `build()` split along its commented phases.
- **Proof:** the english_art and cdn selftests, and `tests/test_english_derive.py`. It does not affect replays.

## 3. Patterns to keep

These worked and are the template for new code:
- **Server:**
  - one explicit module order (pinned by `server/module-order`, printed by `--list-hooks` / `--list-apis`);
  - generated, checked reply and argument types (`api/gen/`, T0 `generated`);
  - one request lifecycle: a fresh `RequestContext`, one transaction, one refusal path;
  - (a)–(d) labels enforced by `check_server_docs.sh`.
- **Runtime:**
  - `app::boot(BootConfig)` with its hooks, so the three hosts differ only in what they hook;
  - the extension points (`hle_add_registrar`, `override_fn`, `add_class_installer`, `override_method`),
    through which platform370 plugs in with no runtime changes;
  - header comments that cite their evidence (spec tables, guest addresses).
- **Port:**
  - `addresses.txt` → `gen/<s>_addresses.h`, resolved by symbol, stamped with the library's sha256, and with
    each constant's user recorded;
  - `NativeCallee`, with call sites classified in CALLS.md and checked by `native/direct-callees`;
  - complete layout headers (anim, data_formats, input, scene, sync, yayoi, math, hash);
  - kernel's dispatcher as the worked example of virtual dispatch.
- **Python and build:**
  - `tools/py` with `tests/test_python_env.py`;
  - soadrive sessions with explicit `TARGETS` (0.27% duplication across 39 sessions);
  - commented CMake, with flags as interface targets and the layering enforced by `soa_check_includes`.

## 4. Suggested order

1. **RB1, RB2, RB4.** Mechanical changes, provable by byte-identical replays and T0. One commit each.
2. **RB3, RB5, RB6, RB7.** Each is small and independent.
3. **RB8 and RB9.** Most of the value is here; they have the most call sites.
   - Commit them in pieces: one helper, or one subsystem, per commit.
   - Run replays or live checks after each piece.
4. **RB10, RB12, RB13.** RB10 and RB12 change how programs and tests are run, so they need T1 and the
   Windows tiers.
5. **RB11.** Split each function when its file is next changed for another reason.

Nothing here is queued: the user picks which batches become tasks.
