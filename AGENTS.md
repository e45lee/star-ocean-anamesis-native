# AGENTS.md: working on this repository

For anyone (human or AI) about to change this code. It summarizes and links; the linked docs are
the reference. Read this, then the README of the part you touch.

## What this is

A desktop port and reconstruction of *STAR OCEAN: anamnesis* (JP), whose service closed in 2021
([README.md](README.md)). The game's ARM64 `libSOA.so` from the last online client (3.7.0) runs in
an ordinary x86-64 process under the dynarmic JIT, with Android, libc and GL reimplemented around
it, and a local game server we wrote stands in for the lost one. Guest functions are replaced one at
a time by readable C++ ("natives"), each checked against the original. Programs:

- `soa`: the port: the 3.7.0 client, its server in-process (default) or `--server HOST`.
- `soa-server`: the local server on its own, speaking the game's wire protocol and CDN.
- `soa-emu`: the unmodified 3.7.0 client against `soa-server`.
- `soa-viewer`: the unmodified offline build in emulator-viewer/, no server.
- `soa_save`: the Python save editor.

## Repository map

| Path | What |
|---|---|
| [`runtime/`](runtime/README.md) | `libsoaruntime`: ELF loader, JIT CPU, bionic/Android/JNI HLE, EGL/GLES, audio, host loop, GDB stub |
| [`server/`](server/README.md) | `libsoaserver` + `soa-server`: game APIs, player state (SQLite), master data, wire layer (`net/`), CDN. Start with [ARCHITECTURE.md](server/ARCHITECTURE.md) and [API-INDEX.md](server/API-INDEX.md) |
| [`port/`](port/README.md) | `soa`: options, the in-process route, natives ([`port/src/native/`](port/src/native/README.md)), session scripts. Plan: [PLAN.md](port/PLAN.md), [REMAINING.md](port/REMAINING.md), [REBUILD-QUEUE.md](port/REBUILD-QUEUE.md) |
| `port/decomp/` | committed Ghidra decompiles and `symbols.tsv` per native subsystem (data, not built) |
| [`platform370/`](platform370/README.md) | the 3.7.0 platform layer (Java answers, clock, `service_stop_day` patch, network glue) |
| [`emulator/`](emulator/README.md) | `soa-emu`; emulator-only code lives only here |
| [`emulator-viewer/`](emulator-viewer/README.md) | `soa-viewer`, the offline client (the only place it is kept) |
| `common/` | small shared libraries: `soa/env.h`, `zip.h`, `file_tree.h`, `install.h`, `paths.h`, Base64 / prefs XML, sockets, Windows compat (`common/win32/`) |
| `webview/` | the notice board's HTML renderer on litehtml ([docs/webview.md](docs/webview.md)) |
| [`control/`](control/README.md) | driving clients: `soactl.py`, `flowctl.py`, `run.py`, the `soadrive` library, the slot pool, `gdbclient.py` |
| [`tests/`](tests/TIERS.md) | gate tiers (`tiers.json`), `tests/diff/` ([port vs emulator](tests/diff/README.md)), pytest, smoke baselines |
| `tools/` | RE and maintenance tools (Ghidra wrappers, generators, gates, checks); each script's header says how to use it |
| `scripts/` | `build.sh`, `run-*.sh`, Windows staging/launchers, packaging, the shared phone |
| [`docs/`](docs/) | reverse-engineered formats ([notes.md](docs/notes.md)), [api.md](docs/api.md), [server-rules.md](docs/server-rules.md), [client-changes.md](docs/client-changes.md), [environment.md](docs/environment.md), [unimplemented-apis.md](docs/unimplemented-apis.md); finished plans in `docs/history/` |
| [`soa_save/`](soa_save/README.md) | save editor and event-script decoder |
| `data/` | decrypted master DBs, gacha pools, [sanitized test saves](data/saves/README.md) |
| `apk/`, `work/` | game files and local working data: [README.md "Game files"](README.md#game-files) |
| `cmake/`, `vcpkg.json` | dependency setup (vcpkg ports, pinned FetchContent, toolchains, triplets) |
| `standin-assets/` | our made-up images for assets the original CDN lost |

## Setup and build

- Follow [README.md "Setup"](README.md#setup) (apt prerequisites, `.venv` from `requirements.txt`)
  and ["Building"](README.md#building). `scripts/build.sh` bootstraps vcpkg into `.vcpkg/` and
  builds everything into `build/` (`build/port/soa`, `build/server/soa-server`,
  `build/emulator/soa-emu`, `build/emulator-viewer/soa-viewer`, ...). One CMake root; new files under
  the source folders are picked up by globs.
- Windows: a cross build with the distribution's MinGW-w64 GCC (`g++-mingw-w64-x86-64-posix`),
  `scripts/build.sh --windows` into `build-win/`
  ([README.md "Windows"](README.md#windows)). Natives and server code must build there too.
- Third-party tools the scripts look for go in `work/tools/` of the main checkout, never in `$HOME`;
  worktrees reach them through their `work` link.
- Release ZIPs: [README.md "Packaging"](README.md#packaging) (`scripts/package.sh`).
- After a merge rebuild all targets, not just the one you test: a stale `soa-server` fails
  sessions for no reason in the code.

## Running and driving the game

- Launchers and options: [README.md "Running"](README.md#running), [port/README.md](port/README.md)
  "Run options", `--help` of each program. `soa` finds the checkout from its executable
  (`--repo`); a release build (`--release`) never does, only `--repo`
  ([docs/environment.md](docs/environment.md)).
- Drive a running client with `--control FIFO` (or `tcp:HOST:PORT`) and `control/soactl.py`;
  named sessions with `control/run.py SESSION ...` (`--list`), waits with `control/flowctl.py`
  ([control/README.md](control/README.md)). Take a screenshot after each step and check it before
  the next tap: taps during loading or a modal are lost. The window is portrait 9:16 by default
  (the game is a portrait game).
- **Every game client goes through the slot pool**: tests and session scripts take a slot
  themselves; a hand-started client is
  `control/soaslot.py run -- timeout -k 10 N build/port/soa ...`; `control/soaslot.py status` shows
  holders ([control/README.md "The slot pool"](control/README.md)).
- Sessions start from the shared, read-only pre-downloaded phone `work/phone-3.7.0`
  (`SOA_PHONE=none` for a full download; [port/README.md "The shared pre-downloaded phone"](port/README.md)).
- Diagnostics: `SOA_TRACE`, `SOA_PROFILE`, `SOA_COVERAGE`, `SOA_WATCHDOG`, `--memstats`
  ([port/README.md "Profiling"](port/README.md), [runtime/README.md "Environment"](runtime/README.md));
  guest debugging with `--gdb HOST:PORT` (Linux and Windows; breakpoints on natives, `monitor natives`;
  `control/gdbinit-soa` also in a host gdb: `soa-native-break SYMBOL`; runtime/README.md "Debugging the guest
  with gdb").
- Ground truth for rendering questions: the real game on Android (e.g. Waydroid via adb), or the
  unmodified `soa-emu`, before theorizing.

## Testing and gates

Tiers, tests and commands: [tests/TIERS.md](tests/TIERS.md) (generated from `tests/tiers.json`).

```sh
tools/gate.sh T0                     # every commit (~1.5 min): build, unit tests, port selftest, replays, doc/format/schema/no-offline-ref checks, pytest
tools/gate.sh T1 --git-diff main     # per change, before reporting: T0 + what tools/tests_for.py picks
tools/tests_for.py --git-diff main   # what T1 would run, and why
tools/gate.sh T2 --out DIR           # per batch / before merging a batch (~25 min, incl. win:* if build-win/ exists)
```

- Run the cheapest tests that prove the change; T3 only when asked. Items marked KNOWN in
  `tests/tiers.json` don't fail the gate.
- Server changes: add a replay corpus line (`server/tests/replay/`, see its `COVERAGE.md`) rather
  than a session. Pure refactors are proven by byte-identical replays (`tools/server_replay_diff.sh`).
- Emulator checks only when `emulator/`, `platform370/`, `runtime/`, `server/` or the root build
  changed; viewer checks only for `emulator-viewer/`, `runtime/` or the root build.
- A selftest must pass in the full `--selftest` run, not only filtered: restrict stub sessions
  (`StubSession::only`), don't compare uninitialised bytes or state other threads write, and fix
  isolation instead of re-running a test that fails only in the suite.
- Windows tests (`win:*`): use your own stage, never the shared one:
  `scripts/windows-stage.sh --phone --viewer /mnt/c/soa-win-<name>` once, then
  `SOA_WIN_STAGE=/mnt/c/soa-win-<name>`; delete it when done. A stage holds the download as the
  zip only; `scripts/windows-stage.sh --clean DEST` removes old run output (a failing run's is kept).
- Gate on the exit code (`tools/gate.sh T0; rc=$?`), never on a grep of its output.

## Hard rules

- **No real player data.** The local player id is `LOCAL00001`; tests use only the sanitized saves
  in `data/saves/` ([its README](data/saves/README.md)). Never write a real player id, device UUID
  or token into code, tests, docs or commit messages; check with `git grep` before committing.
- **Game files.** Only the files listed in [README.md "Game files"](README.md#game-files) are in git,
  as plain git: no LFS, nothing over 100 MB. Everything else (the offline client's archive, the
  Ghidra projects, `work/`) stays local. Release packages never contain game files (the allow-list
  and scan in `tools/package.py`), with one exact exception, Global's master DB
  `data/basmaster-gl.sqlite3` (the user, 2026-10-07: the source of the official English).
- **Server first.** Restore behaviour by giving the unchanged client the server data it expects.
  Change client code only when no server route exists, and log every such change in
  [docs/client-changes.md](docs/client-changes.md) (symbol, original behaviour, the change, why not
  server-side, the switch). Bit-exact native ports are not changes.
- **Label every server rule** (a) master data, (b) client evidence, (c) outside knowledge or
  (d) assumption, in a code comment and in [docs/server-rules.md](docs/server-rules.md#labels);
  conventions and enforced checks in [server/README.md "Comment conventions"](server/README.md).
  Evidence is never deleted; server-rules links use anchors; `tools/format_server.sh` formats
  `server/`. Use the server's clocks (`now()`, `event_now()`), never `time()`.
- **Don't hard-code which content exists:** decide at runtime from the files present (more may be
  downloaded later).
- **State schema changes are migration steps** in `server/src/state/schema.cpp` (`user_version`
  +1, fresh == migrated, a migrate test; [server/src/state/README.md](server/src/state/README.md),
  [server/PLAN-schema.md](server/PLAN-schema.md)).
- **Dependencies:** prefer a well-known library from vcpkg over hand-rolled parsers and codecs.
  Record every dependency: C/C++ in `vcpkg.json` (or a pinned `FetchContent` in `cmake/deps.cmake`
  when the game needs an exact version), Python in `requirements.txt` with a comment naming its
  users (`tests/test_requirements.py` checks). **Never edit `cmake/vcpkg-triplets/`**: any change
  rebuilds every vcpkg port.
- **Settings are command-line flags**, not environment variables; the environment holds only
  diagnostics and test switches, read through `common/include/soa/env.h`
  ([docs/environment.md](docs/environment.md)).
- **The port is the 3.7.0 client.** References to the offline build stay in the viewer
  (emulator-viewer/) and `docs/history/`; `tools/check_no_380.sh` (in T0) lists the allowed places
  and the per-line marker for deliberate exceptions.
- **Repository hygiene:** never `git add -A` / `git add .` (add by path); never commit symlinks,
  `work/`, `.venv`, `build/` (a pre-commit hook refuses; never `--no-verify`); never modify
  `work/` or `apk/` unless asked; no bare `git stash` (use a WIP commit); don't push: branches
  merge into `main` after T0.
- **Layering:** `server/` must not include `port/` or `runtime/`; `runtime/` must not include
  `port/`, `server/` or `emulator/` (configure-time checks).

## Reverse-engineering workflow

- **Decompile with Ghidra**, not objdump: `tools/decomp.sh OUT 'REGEX'...` (named functions; no
  `^` anchor, the signature starts with the return type; template arguments don't match, use the
  address) and `tools/decomp_at.sh OUT GHIDRA_ADDR...` (Ghidra address = ELF vaddr + 0x100000).
  3.7.0 is the default; scratch output goes to `work/decomp/`. Tools and the MCP server:
  [README.md "Reverse-engineering tools"](README.md#reverse-engineering-tools). Anonymous lambdas:
  find `operator()` through the `std::function` vtable in the caller (slot +0x30).
- **Per-subsystem natives** ([port/src/native/README.md "Per-subsystem workflow"](port/src/native/README.md)):
  `tools/subsystem.py new <s>`; `tools/decomp.sh --into <s>/<topic> ...` (stamped copy in
  `port/decomp/<s>/`, upserts `symbols.tsv`; never run two `--into` on one subsystem at once);
  status in `symbols.tsv`: `decompiled` → `typed` → `native` → `tested` (or `skip`).
- **Types first, classes with methods.** Recover layouts from the decompile into `<s>_layout.h`
  with `static_assert`ed offsets and named padding; port leaves first (values, containers, objects,
  managers). Natives are members bound with `NATIVE_METHOD(sym, &C::M, note)`; no raw
  `*(T*)(p + off)`. No C++ `virtual` in recovered classes: the guest vtable stays guest data
  ([VIRTUALS.md](port/src/native/VIRTUALS.md)). After editing a layout header run
  `tools/subsystem.py export-types <s>` (T0 fails on a stale `types.json`). Only the maintainer
  writes the committed Ghidra project (`tools/ghidra_apply_types.sh`).
- **Readable C++ from the decompile**; no new a2c transcriptions. When a library version changes,
  regenerate (generators, address tables, existing a2c fallbacks) before debugging failures one by
  one.
- **Verify every native**: a differential `NATIVE_TEST` against the guest (in `--selftest` no
  natives are installed, so `t.call` reaches the original) and a live check at 0 mismatches
  (`--live-check FAMILY`). Reproduce guest quirks; note game bugs instead of fixing them.
- **Guest ABI**: AAPCS64; an `int` result defines only w0, a `bool` only the low byte; structs over
  16 bytes, `std::string` and `shared_ptr` returns go through x8. Memory guest code will free comes
  from the guest's allocators (`guest_std.h`). Replace whole families that share state at once.
  Float natives: `-ffp-contract=off` and the AArch64 NaN rules of `native/common/arm_float.h`
  (e.g. [math](port/src/native/math/README.md)).
- Check `soa --list-native` before porting a symbol, and look in `port/src/native/common/` for an
  existing helper (`git merge main` first) before adding one.

## Worktrees and merging

- Parallel work happens in git worktrees: `port/scripts/agent-worktree.sh <name> [base]` (base `main` by
  default) makes `.claude/worktrees/<name>` on `port/<name>`, symlinks `work` and `.venv` from the
  main checkout and builds it. vcpkg is the main checkout's `.vcpkg` (scripts/vcpkg-bootstrap.sh
  finds it through git: no link, no `VCPKG_ROOT`), and the ports come from vcpkg's binary cache:
  a fresh worktree's `scripts/build.sh` (or `--windows`) takes minutes, not the hour a port rebuild
  takes; configure only with `scripts/build.sh` (README.md "Windows": the cache keys). Treat those
  links as read-only shared data; edit only your worktree.
- Commit small, by path, with T0 passing. `git merge main` inside your own worktree is fine.
- Merging a branch: check it carries no symlinks (`git ls-tree -r BRANCH | grep ^120000`), resolve
  conflicts before any other commit (`git diff --name-only --diff-filter=U`), confirm the merge
  happened (`git merge-base --is-ancestor BRANCH HEAD`), rebuild all targets, run T0.
- Two branches must not port the same symbol; assign each family to one owner.

## Pitfalls

- Wrap ad-hoc client runs in `timeout -k 10 N` (a wedged client ignores SIGTERM), but **never wrap
  `control/soaslot.py run` or a gate in an outer `timeout`**: killing the wrapper orphans the client,
  which keeps its slot. Use their own time limits.
- Kill only PIDs you started (from `$!`). Never `pgrep -f` / `pkill -f`: the pattern matches your
  own shell, and other clients share the name. Poll with `kill -0 $PID`.
- Host GPU failures (black shots, `HOST-GPU-FAILURE:`, a crash in the driver, no GLX context) are
  the host's: re-run once, then report as host; or run on llvmpipe
  (`--software-gl`, [docs/testing-software-gl.md](docs/testing-software-gl.md)).
- Keep each client under about 6 GB RSS; `--guest-cpus` (default 8) bounds the guest's worker
  threads and so the JIT contexts.
- `thread_local` only for trivial, constant-initialized values (pointers, integers, flags, enums, POD
  buffers): per-thread objects with a constructor or destructor go through `thread_object<T, Tag>()`
  (`live::thread_scratch<T>()` in live checks), owned by the thread's record and destroyed at its
  `thread_end()` ([runtime/README.md "Per-thread state"](runtime/README.md); T0
  `tools/check_thread_local.py` reads the built objects). No large `static thread_local` buffers
  either: glibc takes static TLS out of every new thread's stack, and guest threads have 256 KiB host
  stacks. An overflow logs `*** stack overflow on thread NAME ...`
  ([runtime/README.md "Crash reports"](runtime/README.md)); new runtime threads start with
  `ThreadScope scope("name")` (crash reports, and their per-thread state ends with them).
- Host-built guest code uses `map_guest_code()` / `unmap_guest_code()`, never plain `mmap`: the
  JIT caches translations by address.
- `port/CMakeLists.txt` sorts native sources by basename (registration order); keep basenames
  unique and check `soa --list-native` is unchanged after moving files.
- Never do blind repository-wide renames (a sed of "emulated" once hit `/storage/emulated/0`).
- A log line a script waits on keeps its exact text (`tools/server_log_patterns.txt`).
- WSL → Windows: SQLite can't lock files on `\\wsl.localhost`; run `.exe` files from a stage on the
  Windows drive; environment variables reach them only through `WSLENV`.
