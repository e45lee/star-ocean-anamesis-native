# Native replacements

Code in this directory replaces functions of `libSOA.so` with C++. It's how the port moves from ARM64 code running under the JIT to native code, one verified piece at a time.

**State:** the natives written for the offline build (about 18,000) were deleted in the rebase's revision 2 (2026-10-01; `docs/history/PLAN-rebase-370.md`; git history keeps them) and are being rebuilt for the 3.7.0 client per subsystem (`port/src/native/<subsystem>/`, "Per-subsystem workflow" below), as readable C++ from the Ghidra decompile (`tools/decomp.sh`), hottest families first, each with differential selftests and a live check against the 3.7.0 guest. No new a2c transcriptions. `soa --list-native` prints every registered native; each subsystem's README lists its own, and "What's native now" below the port's own hooks.

## How a replacement works

```cpp
// void CUIUtility::IsResolutionLegacy()  (an illustration; the real one: ui/ui_utility.cpp)
void IsResolutionLegacy(Cpu& c) { c.set_x(0, 0); }
NATIVE_FUNCTION("_ZN10CUIUtility18IsResolutionLegacyEv", IsResolutionLegacy, "note");
```

At startup, `install_native_functions()` looks up each registered mangled symbol and patches the guest function's first instructions to `SVC #n; RET`. Every call to it then lands in the host function, whether it's a direct call, through the PLT, or through a vtable.

The host function receives the guest CPU state:

- **Arguments**: follow AAPCS64. Integer and pointer arguments are in `c.x(0..7)`, floats and doubles in `c.s(i)`/`c.d(i)`, and anything further is on the stack.
- **Results**: go in `c.set_x(0, …)` or `c.set_s(0, …)`/`c.set_d(0, …)`.
- **Signature adapter**: `wrap<&fn>()` builds the `HostFn` automatically when the C signature means the same thing on both sides (e.g. a whole C library swapped for the host's).
- **Memory**: guest memory is identity-mapped, so pointers can be dereferenced directly.
- **Calling guest code**: `guest_call(addr, {args…})` calls back into guest functions that haven't been ported yet. A nested JIT instance runs them on the caller's stack. For float arguments or results use `guest_invoke<R>(addr, args…)` (integers/pointers go to x registers, `float`/`double` to v registers; `R` comes from x0 or v0) or `GuestArgs`. None of these allocate. A call costs about 20-25 ns; when `addr` is itself a native replacement (or an HLE thunk), `guest_call` calls the host function directly (about 10 ns) without entering the JIT (`SOA_DIRECT_CALLS=0` disables that). `core/zz-bench-transitions` in `--selftest` measures these costs.

- **Short functions**: the patch is 8 bytes, so a 4-byte function (a lone `RET` or a tail `B`) would also overwrite the next function's first instruction. The installer leaves such a function as guest code when it's a `RET` or a branch to another replaced function, and warns otherwise.
- **Deferring to the original**: `NATIVE_FUNCTION_ORIG(sym, fn, note, &orig)` stores a trampoline to the original code in `orig`. A replacement can then handle the common case natively and pass the rest (e.g. a cache miss that runs a loader) to the guest. `orig` stays 0 when the replacement isn't installed, as in `--selftest`.

Use `NATIVE_FUNCTION_IF(sym, fn, note, predicate)` for a replacement installed only when its predicate says so. Two groups are not bit-exact replacements but hooks of the port's: `NATIVE_ROUTE_FUNCTION*` marks the in-process route's (`kGroupRoute`: the FakeApiCaller), which `--server HOST` leaves out, and `NATIVE_PORT_FUNCTION_ORIG` / `_IF` / `_ORIG_IF` the port's own behaviour changes (`kGroupPort`: the control commands' `CPhase::Progress` wrapper, the tower opt-in, the resolution, the local web pages; each in `docs/client-changes.md`). A subsystem's natives use neither.

**Which natives run (`soa --natives`):**

| | Installs | For |
|---|---|---|
| `--natives all` (default) | every registered native | normal runs |
| `--natives route` | only `kGroupRoute` and `kGroupPort`: the game's own code all under the JIT, the in-process server, the control commands and the port's options still working | the A/B of a native regression: a bug that goes away with `route` is in a subsystem's natives |
| `--natives-skip SUBSYS[,SUBSYS..]` | with either set: these subsystems' natives (the folder under `native/` of the file that registered them) left to the guest | narrowing it down to a subsystem (then `--live-check SUBSYS` for the function) |
| `--natives none` (`--no-native`) | nothing, not even the route | pure JIT, as `soa-emu` |

The registration records its source file (`register_native_function`'s caller, or `Family::add`'s), so a native belongs to the subsystem whose folder registers it; test `native/registry-groups` checks every native has one and that `common/` registers only the port's own hooks.

**Guest addresses (generated tables):** a native never types a 3.7.0 vaddr. A guest global, a string the guest passes on (an assert's file and message) or a `.rodata` table it needs is an entry of its subsystem's `addresses.txt` (by its dynsym symbol; by its text, exact or a whole string's tail, with `ref FUNC` when it occurs more than once; or, with neither, its vaddr tied to the function whose code references it), and `tools/gen_addresses.py` writes `<s>/gen/<s>_addresses.h` (`inline constexpr std::uint64_t kName` in the subsystem's namespace, what each is, the lib's version and sha256). Add `main_lib()->base`. A name or address used by two subsystems goes in `common/addresses.txt` (namespace `soa::native`); the generator refuses duplicates. Prefer a symbol lookup (`guest::sym`) where code already looks up by name. `tools/gen_addresses.py --refs 0xVADDR` names the functions that reference an address. T0 `generated` (`tools/check_generated.py`) reruns every generator of a built table in `--check` mode (these, `api/gen/fakeapi_tables.inc`, `params/gen/params_instantiations.inc`, `api/gen/wire_table.inc`, `server/net/gen/wire_decode.inc`): commit the regenerated file with the change that needs it.

**The library check:** the tables are the 3.7.0 lib's, so `soa` compares the loaded `libSOA.so`'s sha256 with the one they were generated from (`kLibSha256`, `common/gen/common_addresses.h`; `common/lib_check.*`, test `native/lib-check`) and refuses to start with natives on any other build (`--natives none` runs it; `--selftest` warns). A new build of the lib is a regeneration (AGENTS.md).

**Floating point:** the whole port is compiled with `-ffp-contract=off` (`port/CMakeLists.txt`): a multiply-add is never fused unless the native writes `std::fma`, so the natives round as the guest does on any host compiler (GCC's x86-64 default has no FMA; a `-march` with one, clang's default `-ffp-contract=on` and AArch64 hosts would fuse). Use `native/common/arm_float.h` for the AArch64 NaN rules (e.g. `math/README.md`).

## Verifying replacements

Each replacement should come with a differential test in the same file:

```cpp
NATIVE_TEST("hash/chash32") {
    alignas(16) u8 obj[32] = {};
    t.call("_ZN9Framework7CHash32C1EPKc", {(u64)obj, (u64)"role_cp0303_b04a_6131"});  // original ARM64 code
    u32 guest = (u32)t.call("_ZNK9Framework7CHash323GetEv", {(u64)obj});
    t.expect_eq(guest, server::chash32("role_cp0303_b04a_6131"), "CHash32");
}
```

Run the tests with:

```sh
build/port/soa --selftest [name-filter]
```

In self-test mode the library is loaded without any replacements installed. `t.call()` therefore always reaches the original ARM64 code, and the test compares its results with the native implementation on the same inputs.

### Code that calls GL

Native code calls GL through `GLH(glName, args...)` (`hle/gl_host.h`), never the host library
directly, so it gets the same translations the guest's HLE thunks apply. For tests, a
`glh::Recorder` installed on the thread (`glh::t_rec`) records every GL call made on it, by guest
thunks and native code alike, as text instead of executing it; recorded calls return
`Recorder::result`. Comparing the two recordings is the differential test for GL-issuing code
(the deleted render family's `render_device.cpp` did; see git history).
**Testing code that works on live game state.** The game keeps running on its own threads during `--selftest`, so tests must not touch objects the game is using. For code over live objects (the UI tree, for example), `NATIVE_TEST_HOOK(symbol, fn, &original)` installs a hook before the game starts, so the test body can run on the game's thread at a known point (e.g. between two frames in `CCocosDirector::SceneProgress`): snapshot the objects involved, run the guest function, capture the result, restore the snapshot, run the native function, compare. Callees whose effects a snapshot can't undo can be stubbed by recording hooks (`guest_stub.h`; a stub used in a frame job must be installed from inside it: `stub()` only invalidates the calling thread's idle JIT code), so the two runs are also compared by their call logs. `SOA_SELFTEST_DELAY=S` plus `--do` taps lets the tests run on a busier screen than the title; `SOA_SELFTEST_START_FILE=F` waits until F exists.

### Live checks: native vs guest in a normal run (`live_check.h`)

Families check their natives against the guest originals during a real session (e.g.
`port/scripts/restore_session.sh SOA OUT TMP --live-check FAMILY:out=FILE`, the battle-gacha flow; i.e.
soa's `--live-check`) with the shared harness in `live_check.{h,cpp}`.
Registered families (`soa --live-check bogus` lists them): record / replay `hash`, `math`, `containers`,
`libcxx`, `data_formats` (leaf families, `common/live_leaf.h`); shadow checks `sync`, `input`, `kernel`,
`resource`, `scene`, `restore` (`common/shadow_check.h`; `restore`: `CCocosNode::SearchByName` with
`--restore-tower`, a getter check through `session:tower`); `memory`, `lib_sqlite`, `yayoi_sqlite` (checks
of their own: a shadow manager; the game's databases also opened in the guest's SQLite and every call
repeated there, `lib_sqlite/README.md`); the lockstep families of the other host libraries, `lib_vorbis`,
`lib_zstd`, `lib_zlib`, `lib_jpeg`, `lib_crypto` (`common/lockstep.h`: the same shadow run, shared; each
subsystem's README); and the run-both families `render` and `params` (`common/live_run_both.h`; render's
GL-issuing natives are checked by `gl_run_both`, `render/render_check.h`: the guest original and the native
each run with the thread's GL calls recorded by `glh::Recorder` on a saved copy of the memory they write,
and the call lists and the memory are compared). A new family uses one of these kinds.
A record / replay family is a `live::LeafFamily("tag", every)` (`live_leaf.h`: `LEAF_METHOD` /
`LEAF_FUNCTION` / `LEAF_HOSTFN` per native, with the memory each touches besides `this`), or a
`live::Family` with `Family::add(sym, host_fn, obj_bytes, ret, enabled, label)`; a native's outgoing
calls go through `live::out_call(family(), fn, {args})` (`live_call.h`) or `live::ACall` (floats), so a
check records them and stubs them on the replay (outside a check they are plain guest calls).
Override `add_regions()` to snapshot more than the object at x0 and `unreplayable()` for functions
whose replay can't work. `live::check` is the class `Check` in `live_check.cpp` (snapshot, record,
stub_callees, replay, compare, race_of). Every family is switched on and tuned from the command line by its tag:

    --live-check FAMILY[,FAMILY..][:KEY[=VALUE]..]     (repeatable)

with the keys `every=N` (every n-th call per function; default the family's), `budget=N` (checks
per function at most), `out=FILE` (per-function counts), `only=SUB[|SUB..]` (only the functions
whose symbols contain one of these: the others run unchecked, so the chosen ones are checked also
as nested callees of other natives), `trace` and `dump`; e.g. `--live-check arena:every=4:only=Alloc|Free`.
(These were the `SOA_<FAMILY>_CHECK*` variables; soa warns when one is still set.) The replay rules
(stubs shared by every family and dropped from each JIT level once, lone-B / PLT callees followed,
the replay at the native run's SP with its stack leftovers, freed-block snapshots incl. deleting
destructors, stack-vector elements, never-empty stub sessions, runaway stop, 64 MB cap, race
rerun) are listed at the top of `live_check.cpp`. Families with checks of their own (shadow, lockstep,
run-both) use its switches and some its stubs, `ReplaySession` and `Only`. `live::t_busy`: only one
check at a time per thread, across families. A check's per-thread state (observations, shadows, caches, maps) comes from
`live::thread_scratch<T>()` (`shadow_check.h`; the runtime's `thread_object<T, Tag>()`: on the heap,
owned by the thread's record and destroyed at its end, `runtime/README.md` "Per-thread state"), never a
`thread_local` object: only trivial ones (pointers, integers, flags) are allowed (T0
`tools/check_thread_local.py`), and no big `static thread_local` buffer either: glibc carves static TLS
out of every thread's stack, and 150 KB of them (input's, 2026-10-04) left the game thread too little
of its host stack for the tower menu (`runtime/src/hle/thread.h` `hle_guest_thread_host_stack`,
selftest `runtime/guest-thread-host-stack`).

## What's native now

| File | What |
|---|---|
| `api/fakeapi.cpp` (+ `gen/fakeapi_tables.inc`, generated by `tools/gen_fakeapi_tables.py` from the 3.7.0 lib) | **The in-process route** (`--server inproc`; group `kGroupRoute`, 294 hooks): `FakeApiCaller`, the built-in offline server the shipped game never constructs (`docs/notes.md` "Offline server (FakeApiCaller)"), put in `TSingleton<CApiCaller>` by the `CGame::OnInitialize` hook; its 95 request methods hand each request to the local server library (`api/server_adapters.cpp` `capture`), the status-only / constant methods, the base-class requests the route serves (`UpdatePartySet`, `SetAssist`, `UpdateView`, `EndMissionTalk`, Sphere 211, event rankings), `AddLocalFile`, `Progress`, `IsRequesting`, `Release`, construction and destruction, and the 95 lambda `operator()`s (forwards to `CApiNotify::On*Res`; the login ones build the fake-login ASON). Tests `fakeapi/*` (requests with map dumps, every lambda, `Progress`, lifetime) against the 3.7.0 guest. |
| `api/server_adapters.*`, `api/server_cdn.cpp` | Not natives: the server library's hooks into the port (log sink, the asset index), the route's requests as the wire carries them (`inproc_request`; MissionEnd & co. with the battle log the client's own serializer makes, `client_battle_log.*`), `config_from_options` (core/options.h `ServerOptions` -> `server::ServerConfig`), and the in-process CDN (soa-server's HTTP router as platform370's HTTP backend). Tests `server/*` (`zz_server_guest_test.cpp`, `server_cdn_test.cpp`), `wire/*` (`wire_test.cpp`, the request serializers' layouts, `wire/inproc-parity` the route's requests vs soa-server's decode of the client's packets; table `gen/wire_table.inc` by `tools/api_wire.py --gen-inc`). |
| `common/port_debug.cpp` | Port: a `CPhase::Progress` wrapper that runs the `--control` commands `phase:` / `call:` / `mission:` / `uiset:` / `clock:` / `debugwin:` / `memstats` on the game thread and logs `port_debug: phase N` (what the session scripts wait on). |
| `restore/restore_tower.cpp` | Port, `--restore-tower` only: `CParameterUtility::IsOpenTowerMission` = 1, stand-in `play_plate/0..3` nodes for `CTowerMissionMenu::Setup` (`CCocosNode::SearchByName` native, `ui/cocos_node.*`, test `ui/cocos-search-by-name`, live check `restore`; a wrapper of the guest `SearchByTreeName`), the common-resource scene for `CTowerMissionMenu::Initialize` (`docs/client-changes.md` "Tower"). Flow: `port/scripts/tower_session.sh SOA OUT TMP --live-check restore`. |
| `ui/ui_utility.cpp` | Port, the render resolution (default on): `CUIUtility::IsResolutionLegacy` false (hi-res: the game renders at the game screen's size), or with `--render-scale S` true and `GetDefaultBackBufferScale` S (the 3D's back buffer); nothing with `--legacy-res` (`docs/client-changes.md` "High-resolution rendering"). Test `ui/resolution` (the guest constants, the modes). |
| `ui/webview_local.cpp` | Port, `--server inproc`: `CWebView::OpenView` + `SOAActivity.ShowWebView`: pages the local server hosts (the notice board) shown as text in the popup (`docs/client-changes.md` "Notice board page"). |

The infrastructure: `common/native.*` (the registry, `--natives all|route|none`, `--natives-skip`, `--list-native`), `common/lib_check.*` (the library's sha256 against the tables'), `common/addresses.txt` + `gen/common_addresses.h` (the shared guest addresses), `common/native_method.h` (`NATIVE_METHOD`: a recovered class's member as the native), `common/test.*` (the selftest harness: `NATIVE_TEST`, `NATIVE_TEST_HOOK`), `common/guest_std.*` (guest libc++ strings / lists and the guest's allocators), `common/guest_stub.*` (recording stubs), `common/live_check.*` (live checks: the switches, the record / replay `Check`, `live::Regs` / `ACall` / `out_call` for a native's outgoing calls), `common/live_leaf.h` (leaf families), `common/shadow_check.*` (live checks of natives over shared, stateful objects: the guest original on a shadow, or a getter rerun; families sync, input, resource), `common/guest_assert.*` (`Framework::gDoAssert` with the guest's strings), `common/arm_float.h`, `common/memstats.*` (`--memstats`), `common/core_bench_test.cpp` (guest-call costs).

## Per-subsystem workflow (the native rebuild, port/PLAN.md task 6)

Virtual functions, calls between native subsystems, and the later move to real C++ `virtual`s: [VIRTUALS.md](VIRTUALS.md).

Each subsystem of the rebuild owns two folders and nothing else, so many agents can work at once
(one per subsystem, type recovery a wave ahead) and their branches merge without conflicts
(`control/tests/test_subsystem.py` proves it for two scaffolded subsystems):

| Path | What |
|---|---|
| `port/src/native/<s>/README.md` | scope, the types table, the natives table (its own: no shared list to edit), dependencies, RE notes |
| `port/src/native/<s>/<s>_layout.h` | the recovered guest classes, methods attached, `static_assert`ed (types first) |
| `port/src/native/<s>/subsystem.cmake` | the subsystem's own build settings (a host library, a definition); `port/CMakeLists.txt` includes every one |
| `port/src/native/<s>/addresses.txt` | the guest addresses its natives use; `gen/<s>_addresses.h` is generated from it (`tools/gen_addresses.py`; "Guest addresses" above) |
| `port/src/native/<s>/<s>_*.cpp` | natives and their differential tests (globbed; link order by basename, D8) |
| `port/decomp/<s>/<topic>.c` | stamped Ghidra decompiles the rewrite used (data, not built) |
| `port/decomp/<s>/symbols.tsv` | one row per guest function: vaddr, ghidra, size, symbol, demangled, topic, status (`decompiled` / `typed` / `native` / `tested` / `skip`), note |
| `port/decomp/<s>/scope.txt` | the demangled-name regexes the subsystem owns (the rebuild queue's ranking) |
| `port/decomp/<s>/types.json` | `<s>_layout.h`'s structs for Ghidra (generated) |

The steps:

1. **Scaffold:** `tools/subsystem.py new <s> --title "..." --scope '^CFoo::' ...` (never overwrites).
2. **Decompile into it:** `tools/decomp.sh --into <s>/<topic> '<regex>'...` (the regex runs on Ghidra's
   signature, which starts with the return type: `'CHome::'`, not `'^CHome::'`) or `tools/decomp_at.sh --into <s>/<topic> <ghidra-addr>...`
   writes `port/decomp/<s>/<topic>.c` (header: the lib's sha256, Ghidra's version, the script, every run's
   date and command; per function: vaddr, Ghidra address, size, ELF symbol, lib, date) and upserts the
   functions into `symbols.tsv` (a row's status and note are kept). Without `--into` the tools still write
   scratch output to `work/decomp/`.
3. **Types first, as classes with their methods attached** (port/PLAN.md task 6): `.venv/bin/python
   tools/subsystem.py skeleton <s> [--class C] [--append]` turns the `symbols.tsv` rows into class skeletons
   (grouped by the demangled class: constructors / destructors as `Ctor` / `CtorBase` / `Dtor` / `DtorDelete`
   members, the virtuals in the order of the class's vtable `_ZTV...` read from the lib, the other methods;
   argument types mapped where they are plain, `void*` / `u64` placeholders otherwise; return types from the
   decompile), which `--append` adds to `<s>_layout.h` for the classes not declared yet. Then the fields:
   at the guest offsets, unknown bytes as named padding, a `static_assert` per offset and size. The classes
   stay standard-layout: **no C++ `virtual`** (the object lives in guest memory with the guest's vtable; a
   host vptr would change the layout), the vtable pointer is a field. Then `tools/subsystem.py
   export-types <s>` (clang's record layouts -> `types.json`, with each class's methods for Ghidra's `this`).
   Set the functions' status to `typed`. Run `export-types` before committing a changed layout header or
   `symbols.tsv`: T0's `pytest-control` (`control/tests/test_subsystem.py`) runs `tools/subsystem.py check`,
   which compiles every layout header alone with clang++ and fails on a stale `types.json` (so keep the
   headers to standard C++ that both clang and GCC accept).
4. **Natives are the members:** define `C::Method` in `<s>_*.cpp` and bind it with
   `NATIVE_METHOD(sym, &C::Method, note)` (`common/native_method.h`: `this` from x0, the arguments by
   AAPCS64); a static member or a free function with `NATIVE_FUNCTION(sym, wrap<&C::F>(), note)`; a hand-written
   `HostFn` only where the signature needs it (an x8 struct result). Existing struct + free-function natives
   move to this form when they are ported again. Differential tests (NATIVE_TEST) beside them; list the
   natives in the subsystem README; status `native`, then `tested` once the live check is at 0.
5. **Check:** `tools/subsystem.py check` (files present, `symbols.tsv` well-formed, the layout header compiles on
   its own, `types.json` current; warns when two subsystems claim a scope pattern); `tools/subsystem.py list`
   prints the index of every subsystem (symbols by status, structs, natives).
6. **Ghidra (the integrator, serially, after merging):** `tools/ghidra_apply_types.sh [<s>...]` applies
   `types.json` (data types `/soa/<s>/...`; each class's methods get `this` typed as a pointer to it) and `symbols.tsv` (names for `FUN_` functions, bookmarks
   `soa/<s>`) to the decompile tools' Ghidra project. Agents never write the project.

The folders that predate the scaffolding (`api/`, `common/`, `restore/`, `ui/`) keep their rows in the
table above; scaffolded subsystems list their natives in their own README instead.

## Porting guidelines

- **Decompile first**: the client is 3.7.0, so `tools/decomp.sh <name> '<regex>'` (and `decomp_at.sh`; `--into <subsystem>/<topic>` for the committed, stamped copy: "Per-subsystem workflow" above) decompiles every function matching a demangled-name regex from the 3.7.0 lib, the default, into `work/decomp/<name>.resolved.c` (its Ghidra project pool, `work/ghidra-quick-v370*`; `--v370` is accepted, `--v380` selects the viewer's offline lib). Write readable C++ from it; no new a2c transcriptions (the user, 2026-10-01). `tools/verdiff_decomp.sh` / `verdiff.py` (3.7.0 vs the offline build) are history tools.
- **Keep guest layouts**: data structures shared with guest code must keep the guest's in-memory layout. That includes libc++ (`std::__ndk1`) containers and the `Framework::CSTLAllocator` allocators, until every function touching them is native.
- **Port whole families**: port every entry point of a library or class that owns internal state at once. Mixing guest and host implementations over the same state doesn't work; for example, all of zlib moved together.
- **Transcribing**: `tools/a2c.py` and the `tools/gen_*_a2c.py` generators (goto-structured C++ over a register file, instruction by instruction) are kept as tools only; nothing in the tree uses their output, the live check has no a2c path any more, and new natives are readable code. Floating point: match the guest's fused multiply-adds (`std::fma`) where it fuses, plain mul + add where it doesn't (never fused by the compiler: "Floating point" above; `arm_float.h` has the ARM NaN rules).
- **Hook size**: the patch is 8 bytes (`SVC; RET`); `install_native_functions` skips functions smaller than that (4-byte tail-call trampolines) instead of clobbering the next function.
- **Trampolines to the original** (`NativeFunction::original`): the first two instructions copied, then a branch to entry + 8. When they are PC-relative (ADR / ADRP, B / BL, B.cond, CBZ / CBNZ, TBZ / TBNZ) `make_relocated_trampoline` (`common/trampoline.h`, test `native/relocated-trampoline`) relocates them; only an LDR (literal) there still leaves the native uninstalled (a warning).
- **Host-built guest code** (trampolines, test snippets, fake code pages): allocate it with `map_guest_code()` and free it with `unmap_guest_code()` (`core/cpu.h`), never plain `mmap` / `munmap`. The JIT caches translations by address only, so a page that is unmapped and mapped again keeps running the old code in every JIT that ran it. That was once an intermittent full-`--selftest` SIGSEGV (a page-aligned guest `pc`, `lr = <return-to-host>`): tests unmapped their snippet pages, and a later test's trampoline landed on the same address and ran a stale snippet.
- **Good targets**: leaf functions, pure functions, and whole template families. The `Aska::TAaf*` animation controllers, for instance, are ~15k instantiations of a few templates.
