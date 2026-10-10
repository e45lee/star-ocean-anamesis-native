# Code review, 2026-10-10

A correctness review of the whole codebase. It looked for bugs: crashes, memory safety, wrong results,
input that isn't trusted, races and resource leaks. It did not look at design; for that, see
[code-review-2026-10-06.md](code-review-2026-10-06.md). Most findings were fixed in the same branch. The rest
are listed under [Open findings](#open-findings) for the user to pick.

- **Commit reviewed:** `0fb2e80` (main). The fixes are commits `90d9412`..`b063b82` on
  `claude/kind-turing-e2h324`. Every `file:line` under "Open findings" refers to `b063b82`.
- **Areas:** four area reviews: `server/`; `common/` + `runtime/` + `webview/` + `platform370/`; `port/src`
  (hand-written code and `native/common/`, plus a sample of the subsystems); the Python code (`tools/`,
  `control/`, `soa_save/`, `tests/`). Each finding was confirmed by reading its callers. Findings that could
  not be traced to a real caller or input were dropped.
- **How it was tested:** the full build was not available: the session's network refused vcpkg's GitHub
  downloads, so `tools/gate.sh T0` was not run.
  - **Instead:**
    - pytest `tests` and `control/tests`;
    - `tools/format_server.sh --check`, `tools/check_no_380.sh`, `tools/check_env_access.py`;
    - standalone builds of the affected sources against apt's msgpack-cxx and zstd headers;
    - syntax-only compiles of every changed C++ file with the Linux g++ and the MinGW g++.
  - **Bugs reproduced on `0fb2e80`** before the fix, and shown fixed after:
    - the MessagePack stack overflow (a segfault);
    - both `aska_image` overflows (AddressSanitizer);
    - the `gdbclient` timeout and the `--for` path selection (pytest).
  - **Still to run:** T0, and the `win:*` tests for the Windows changes, before merging.

Ratings: **Impact** H/M/L. **Effort** S (hours), M (a day or two).

## Fixed

| Area | Finding | Impact | Test |
|---|---|---|---|
| server | `mp_decode` had no depth limit. `from_object`, `pack` and `~Value` recurse once per level, so a battle-log blob of about 100k nested arrays (`0x91…`) overflowed the loop thread's stack and killed `soa-server`. Any peer can open a session without credentials. Now nesting deeper than 256 levels decodes as Nil. | H | `server/src/core/server_tests.cpp` (msgpack case); reproduced standalone |
| server | Tokens, session ids and session keys came from `mt19937_64` (`random_hex`). Its state can be recovered from its output. They now come from `RAND_bytes`. With `--seed`, the values are the same as before. | M | — |
| server | After a ProtocolError, `Loop::on_readable` kept feeding the bytes that followed to `on_data`. They are now read and dropped. | L | — |
| common | `isf_repack`: a first payload offset inside the entry table made the rebuilt table be written past the end of `out` (a heap overflow). | M | `common/tests/aska_image_tests.cpp`; ASan |
| common | `find_data` (AIF): a `ffub` chunk in the last 16 bytes was read past the end (`buff + 0x10`). The `rdda` loop was not bounded either. | M | same |
| common | `ZipArchive::data_offset_of` returned `base_` when the entry's local header couldn't be read, so `FileTree::locate` pointed the CDN at the zip's first bytes. It now returns 0, and `locate` fails. | M | — |
| runtime | `SharedPrefs::save` renamed a partly written temp file over the old prefs. It now keeps the old file. | L | — |
| runtime | `ALooper_pollAll` tested the callback's `int` result as 64 bits. It now reads w0 only (AAPCS64). | L | — |
| platform370 (Windows) | `th_gethostbyname` read the bionic result with Winsock's `hostent`, whose fields are shorts. `h_length` read 0, so a `--server` host name was never mapped. | M | — |
| runtime (Windows) | `net_win32` socket options: `SO_LINGER` was copied as-is although bionic uses two ints and Winsock two u_shorts; it is now converted in both directions. Linux `TCP_KEEPIDLE/INTVL/CNT` and `IP_TOS` were passed unchanged, so they became Winsock's `TCP_MAXSEG/MAXRT/STDURG` and `IP_OPTIONS`; they are now mapped to Winsock's numbers. A timeout under 1 ms became 0, which means none; it now rounds up. | M | — |
| port | `port_debug` `call:SYMBOL` used `guest::sym`, which ends the game on an unknown symbol, so the warning branch never ran. `mission:` and `uiset:` called `pParameterUI` with a null `this` before the manager existed. | M | — |
| port | `--log-packets`: every waiting request's reply took the latest sequence number, so replies were misnumbered and could overwrite each other's files. | L | — |
| tools | `gate.sh T1 --for ./PATH` (or an absolute path) matched no rule, so T1 passed on T0 alone. `tests_for.repo_paths` now normalizes the paths for both callers. | H | `control/tests/test_gate.py` |
| tools | `tests_for.changed_paths` ignored a failing `git diff` (e.g. a mistyped `--git-diff REV`) and treated it as "nothing changed". | H | same |
| tools | `tests_for --regen` / `--check` without `soa-server` crashed with FileNotFoundError instead of printing its message. | L | — |
| tools | `gate.py`'s signal handler took the non-reentrant `PLOCK`, which the main thread can hold while it starts a process: Ctrl-C could deadlock. `PLOCK` is now an RLock. | L | — |
| tests/diff | `run_flow` stored a 3-tuple when `prepare` failed, so `--expect-fail` raised IndexError. | M | `control/tests/test_difftest.py` |
| control | `gdbclient.cont()` without a timeout gave up after the constructor's 30 s, and a `cont(timeout=X)` left X in place for later calls. | M | `control/tests/test_gdbclient.py` (a fake stub) |
| control | Slot files were created 0644 under the usual umask, in a 1777 directory, so a second user got PermissionError. They are now 0666. | M | `control/tests/test_soaslot.py` |
| soa_save | `set` without `--type` on a u32 whose top byte is 0 inferred `str` and wrote a string over it. It now asks for `--type`. | M | `tests/test_saves.py` |
| tests | `test_mt_runner_strips_speaker` raised StopIteration instead of skipping when there are no Script files. Also: `re.split`'s positional `maxsplit` is deprecated in 3.13 and gave 132k warnings per run. | L | — |

## Open findings

### O1. Windows: non-ASCII paths (Impact M-H, Effort S-M)

On MinGW, `std::filesystem::path::string()` returns UTF-8, and `path(std::string)` decodes the bytes as UTF-8.
The CRT and the `*A` Win32 calls read the same bytes in the ANSI code page.
- **Where:**
  - `common/src/posix_compat_win32.cpp:178` (`exe_path_win32`);
  - `CreateFileA` in `common/src/zip.cpp:40` and `runtime/src/core/host_mem.cpp:44`;
  - `stat` / `fopen` in `common/src/file_tree.cpp`; `_mkdir` in `common/include/soa/paths.h`.
- **Effect:**
  - A release unzipped under `C:\Users\José\` finds its APK through std::filesystem, then fails to open it.
  - An ANSI argument with a byte that isn't valid UTF-8 makes `fs::path` throw, which ends in
    `std::terminate`.
- **Proposed fix:** embed a manifest with `<activeCodePage>UTF-8</activeCodePage>` in every `.exe`.
- **Test:** a `win:*` run from a stage whose path is not ASCII.

### O2. server: trial decryption is a CPU amplifier (Impact M, Effort S)

- **Where:** `GameServer::session_by_key` (`server/net/game.cpp:368`).
- **Cost:** an encrypted packet on a connection with no session is tried against every session's key, up to
  `kMaxSessions` = 256. Each try (`keyed_digest`, `server/net/ninja/ninja_ref.cpp:105`) copies and SHA-256s
  the body, which can be up to `kMaxPacket` = 4 MiB. All of it runs under `Loop::lock_`, which the HTTP thread
  needs too.
- **Proposed fix:** trial-decrypt only small bodies (real requests are a few KB). Or narrow the candidates
  by the RequestHeader's player id. Hash without the copy (EVP update).
- **Related:** `prune_sessions` evicts the oldest unbound sessions once there are more than 256. A real
  client is unbound between its requests, so a flood of bridges logs it out.

### O3. server: the battle-log size isn't checked on the wire (Impact L, Effort S)

- **Where:** `server/net/wire.cpp:249`. The port enforces `kMaxBattleLog` (0x1000) only on the client side
  (`port/src/native/api/client_battle_log.cpp`). The wire decoder takes a blob of any size up to `kMaxPacket`.
- **Proposed fix:** refuse a battle-log blob over `kMaxBattleLog`. The depth limit above already removes the
  crash; this is defence in depth.

### O4. port: live checks compare only w0 of pointer results (Impact M, Effort M)

- **Where:** `RetKind` (`port/src/native/common/live_check.h:147`) has no 64-bit integer kind, and `kAll`
  also compares v0. So natives that return pointers are registered as `kInt`, and
  `port/src/native/common/live_check.cpp:960` compares `(u32)x0`.
- **Effect:** a wrong upper half passes the check. Examples:
  - `TPoolFast::Scoop`, `TObjectContainer::rElement`;
  - `basic_string::replace`, `__shared_weak_count::lock`;
  - `CHash32::operator=`, `CSTLStringUtility::ReplaceSelf`.
- **Proposed fix:** a `kPtr` kind that compares the full x0, keeping the stack-address equivalence, and
  re-register the pointer and `u64` natives with it.

### O5. port: per-thread scratch buffers leak (Impact L, Effort S)

- **Where:** `thread_local Scratch` in `port/src/native/lib_zstd/lib_zstd_api.cpp:62` and
  `port/src/native/lib_zlib/lib_zlib_api.cpp:98`.
- **Problem:** `Scratch` owns a `malloc`'d buffer and has no destructor, so the buffer leaks when its thread
  ends. This is used only under `--live-check lib_zstd` / `lib_zlib`.
- **Proposed fix:** a destructor, and `live::thread_scratch<Scratch>()` (AGENTS.md "Pitfalls").

### O6. port: `CHash32::Assign` passes host strings to the guest's assert (Impact L, Effort S)

- **Where:** `port/src/native/hash/hash_chash32.cpp:85-86`.
- **Problem:** it hands host `.rodata` pointers to `gDoAssert` through a plain `guest_call`. That goes past
  `addresses.txt` and `live::out_call`.
- **Proposed fix:** add the two strings to `port/src/native/hash/addresses.txt` and call through
  `live::out_call`.

### O7. Windows: `O_NONBLOCK` on a guest pipe is ignored (Impact L-M, Effort S)

- **Where:** `fcntl` F_SETFL is accepted and does nothing (`runtime/src/hle/libc_win32.cpp:631`).
  `hostfd::read` blocks on an empty pipe (`runtime/src/core/host_fd.cpp:200`). A read of 0 bytes blocks too,
  where Linux returns 0.
- **Effect:** a guest that drains a non-blocking pipe until EAGAIN hangs on Windows.
- **Proposed fix:** keep a non-blocking flag on each `Fd`, and return EAGAIN when it is set.

### O8. Windows: `pread` moves the file position (Impact L, Effort S)

- **Where:** `common/src/posix_compat_win32.cpp:90`. On a synchronous handle, `ReadFile` with an
  OVERLAPPED offset updates the file pointer. That contradicts `common/win32/posix_compat.h:66`.
- **Effect:** none today, because the callers only use `pread`.
- **Proposed fix:** save and restore the position, or correct the comment.

### O9. control: `soaslot.sh` treats any `pick` failure as "pool off" (Impact L, Effort S)

- **Where:** `control/soaslot.sh:19` (`|| return 0`).
- **Effect:** a broken `.venv` (`tools/py` exits 127), or an exception in `soaslot.py`, runs the client
  outside the pool without saying so.
- **Proposed fix:** a distinct exit code for "pool off / already held". Any other failure prints an error
  and returns 1.

### O10. port: aliased natives and the trampoline (latent, Impact L)

- **Where:** `install_native_functions` (`port/src/native/common/native.cpp`).
- **Problem:** when several registrations share an address (C1/C2 aliases), only the first one seen builds
  the trampoline. A later `NATIVE_FUNCTION_ORIG` alias would get `*orig == 0`. No current registration does
  this.
- **Proposed fix:** build the trampoline whenever any registration for the address asks for an original.
