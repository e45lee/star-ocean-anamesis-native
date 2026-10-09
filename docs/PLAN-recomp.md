# Plan: static recompilation of libSOA.so (getting rid of the JIT)

**Status: plan; the user's decisions of 2026-10-08 are recorded below ("Decisions"); stays a plan until the user starts P0** (written 2026-10-08 by agent recomp-plan; nothing else here is
decided). It answers the user's question of 2026-10-08, "how many more waves before we can get rid
of the JIT?": hand-porting alone never gets there, because the long tail is too long (below), so
this plan proposes to **translate every guest function of `libSOA.so` into generated C++ ahead of
time, with the hand-written natives as overrides on top**. The numbers marked *measured* come from
the prototype in [`tools/recomp-proto/`](../tools/recomp-proto/build.sh) ("The prototype" below)
or from the lib itself; *estimated* numbers are extrapolations from them.

## Decisions (the user, 2026-10-08)

The open questions of 8, answered; the status stays "plan" until the user starts P0.

| # | Question | Decision |
|---|---|---|
| D1 | Release packages and the game-files rule | **An explicit exception:** releases ship the recompiled binaries, like the Global master DB exception (`data/basmaster-gl.sqlite3`). When it ships, AGENTS.md's "Game files" rule and `tools/package.py`'s allow-list / scan get the matching line (the recompiled `soa` binaries by name, nothing else of the translation: no generated sources) |
| D2 | Generated code in git or at build | **Generated at build time**, not committed (`build/recomp/`) |
| D3 | Build budget | **Cold code in a separately cached library**, keyed by the lib's and the translator's hashes (so native work never rebuilds it); hot code built with the program |
| D4 | The waves | **Pause new Wave B/C subsystems until P1** (Wave B is on hold already) |
| D5 | The JIT after P4 | **dynarmic stays as a debug-only reference** (`--engine jit`); P4 makes it optional at run time, it doesn't remove it |
| D6 | `soa-emu` | **Stays on the JIT** as the unmodified reference client (what `tests/diff/` compares against) |
| D7 | Binary size | **~95-110 MB larger binaries are acceptable** |
| D8 | The prototype | **Kept in `tools/recomp-proto/`**, with the gap sweep committed |

## 0. Why hand-porting can't remove the JIT

- **The long tail** (*measured*, [`port/REBUILD-QUEUE.md`](../port/REBUILD-QUEUE.md) and the
  prototype's whole-lib pass): the lib has **103,939 functions** (the profiler's own discovery:
  exports, BL targets, relocations, `.eh_frame`, ADRP+ADD), **5.66 M instructions** in a 22.9 MB
  `.text`. The four served flows execute 13,325 of them (14.4% when measured on 2026-10-03), and
  after Wave A 1,876 are native. Each new screen, event or error path runs functions no flow has run.
- **What the waves can't reach:** template instantiations by the thousand (`TAaf*`: 14,161, 579
  executed), libc++ (25,871), virtual calls and function pointers (44,858 indirect call sites),
  code only multiplayer or unserved features reach (which the "don't port what the server can't
  run" rule keeps on the guest by design), and code paths no test runs.
- So with natives alone the JIT stays as the fallback forever. Static recompilation covers all
  103,939 functions mechanically and leaves the natives for what they are good at: readable code
  where we want it, and speed where it pays.

## 1. Goal and end state

### The layers

```
  natives (port/src/native/<s>/)        hand-written C++, readable; installed ones win (as today)
  ------------------------------------------------------------------------------------------
  recomp/ (generated)                    one C++ function per guest function (all 103,939),
                                         over the guest register file; direct calls between them
  ------------------------------------------------------------------------------------------
  runtime/ minus the JIT                 the loader (data, relocations, the GOT), guest memory
                                         identity-mapped as today, HLE (bionic over glibc / the
                                         Windows CRT, EGL/GLES, OpenSL ES, JNI, Android NDK),
                                         threads, the GDB stub, crash reports, the profiler
```

- **Guest memory stays identity-mapped** and the lib's image (data, `.rodata`, `.data.rel.ro`,
  relocated GOT and vtables) is still loaded by the runtime's loader: vtables, function pointers
  and return addresses keep holding **guest addresses**, which the dispatch table (3) maps to host
  functions. The guest's code bytes stay mapped too (read-only data the game reads in a few places;
  nobody executes them).
- **The register file** (x0-x30, sp, nzcv, v0-v31, tpidr) is a per-thread struct whose registers
  are laid out like dynarmic's `A64JitState` (`reg[31], sp, pc`, then `vec[64]`), so `Cpu`'s
  pointers (`st_`, `vec_`) can point at it: every `HostFn(Cpu&)` (natives, HLE thunks),
  `guest_call`, `NATIVE_METHOD` and the GDB stub's register view work unchanged. The flags differ:
  `A64JitState::cpsr_nzcv` is in x86 flag order (`NZCV::FromX64`), the recompiled code keeps AArch64
  order, so `Cpu`'s `nzcv_` users (the GDB stub's `cpsr`) get an accessor that converts per engine.
- **HLE is unchanged:** imports are resolved at load time exactly as now; a call to an import's PLT
  stub becomes a direct call of its host function.

### What the JIT becomes

1. **Transition:** `soa --engine jit|recomp|mixed` (default `jit` until P3). `mixed` runs the
   recompiled functions that exist and enters the JIT for any address without one (the dispatch
   table's miss path), so a partial translation is usable from day one. In `mixed`, **every
   recompiled function's guest entry is hooked** (`SVC; RET`, as a native's is today), so JIT code
   that reaches it (a caller still under the JIT, a vtable call) runs the recompiled function and
   not the original bytes; otherwise the "no JIT entry" counter of P2 could never reach 0 and the
   recomp-vs-JIT checks would compare the JIT with itself.
2. **After P3:** `recomp` is the default; the JIT stays as a **debug-only reference** (`--engine
   jit`, the differential tests' second opinion), kept for good (D5).
3. **P4 (D5):** dynarmic stays, as the debug-only reference `--engine jit`; the default
   paths no longer touch it (no JIT state per thread, no fastmem handling unless `--engine jit`).
   Its *frontend* (decoder + IR) is also the translator's build-time dependency (D2).

### What it buys

- **No run-time code generation:** no 256 MB code caches per guest context (today a context costs
  ~22 MB, 230 contexts after four battles: `runtime/src/core/cpu.cpp`), no translation stalls, no
  W^X / `mmap(PROT_EXEC)` concerns, no fastmem fault handling; works under any OS policy that
  forbids JIT pages.
- **Full coverage:** every function is host code, executed or not.
- **Debuggability:** a host debugger, host profilers (`perf`, VTune) and sanitizers see real
  symbols (`f_1f88b50` = `Aska::Hash::CRC`, with the guest address in the name); a crash
  backtrace is a host backtrace through named functions.
- **Speed** (*measured*, prototype, 6 functions; the JIT figure includes guest_call's ~20-25 ns
  entry): 1.0-3.5x per call over the JIT on the same inputs (float code 1.6-3.5x, integer loops
  1.0-1.4x), before any optimization beyond the C++ compiler's. The game is 33.1% guest code after
  Wave A, so the end-to-end gain is bounded; it isn't the main reason.
- **The natives get cheaper to call:** a native calling the guest, or guest code calling a native,
  is a C++ call (no 20-25 ns JIT entry, no SVC).

### What it costs

- **A translator to write and keep** (~250 IR opcodes' semantics in C++; 121 done in the prototype).
- **Build size and time** (*estimated*, 5): ~22 M lines of generated C++, ~95 MB of x86-64
  `.text` at `-O1`, ~45-70 CPU-minutes per full compile; a few minutes on this machine's 32 cores.
- **Exactness work** in the corners the JIT got for free: exceptions/unwinding (2.5), indirect
  jumps (2.4), the exclusive monitor (2.3).
- **Binary distribution:** the generated code is a translation of the game's code, and so is a
  `soa` binary compiled from it: under the hard rule "release packages never contain game files"
  it ships under an explicit exception (D1), as the Global master DB does.

## 2. The translator

### 2.1 Recommendation: generate C++ from dynarmic's IR

**Recommended: a C++ translator (`tools/recomp/`) that runs dynarmic's own A64 frontend
(`A64::Translate`) on each basic block, applies dynarmic's IR passes (get/set elimination,
constant propagation, dead code), and prints the IR as C++**, one inline function per opcode in a
hand-written header (`recomp_rt.h`). Reasons, all measured on this lib:

- **Decoding is already proven:** the JIT runs this decoder on the game today. Translating all
  103,939 functions found **no** instruction it can't decode (0 `UnallocatedEncoding`; 419 `BRK`s,
  the game's traps), in 18 s on one core. Coverage of that pass: the blocks reachable by direct
  control flow from each entry cover **88.4%** of the functions' 22.63 MB (jump-table case bodies
  aren't followed, since a `BR` block names no successor); with a gap sweep (every uncovered address
  inside a function becomes a block start, `--sweep`) **96.7%**, still with no undecodable
  instruction; the only `Interpret` terminals (128) are zero padding inside two functions' bounds, and
  the rest of the uncovered 3.3% is padding of that kind. The production translator recovers jump
  tables (2.4) and keeps the sweep as the backstop.
- **The reference is the same semantics:** the JIT and the recompiled code start from the same IR,
  so a mismatch is a bug in one opcode's C++ (or in the x64 backend), never a decoding difference.
  Flags, extends, shifts and conditions arrive as explicit IR (`GetNZCVFromOp`, `ConditionalSelect`)
  instead of being re-derived per mnemonic.
- **A small surface:** the whole lib uses **250 distinct opcodes**; the top 20 are 85.3% of the
  13.0 M IR instructions, the top 50 98.0%, the top 100 99.8%. The prototype implements 121.
- **The hard floating-point ops come for free:** dynarmic's `common/fp/op` is a software
  implementation of FPToFixed, FPRoundInt, FPRecipEstimate (FRECPE, 75 sites), FPRSqrtEstimate
  (FRSQRTE, 203 sites), the step-fused ops; the generated code calls them. The game never fuses a
  multiply-add (0 `fmadd` / `fmla`) and never writes FPCR (0 `msr`), so everything else is plain
  IEEE single/double arithmetic plus the AArch64 NaN rules (as `port/src/native/common/arm_float.h`).

**Alternatives considered:**

| Approach | Verdict |
|---|---|
| **A direct ARM64 -> C++ translator** (our own decoder, or capstone like the old `tools/a2c.py`) | Readable output, but re-implements decode and semantics for ~400 mnemonics × arrangements: the bug surface dynarmic already covers. `a2c.py` (1,457 lines) covered only the math subset with regex over capstone text. Keep it as history. |
| **remill / McSema** ([remill](https://trailofbits.com/tools/remill/): AArch64 to LLVM bitcode, semantics written in C++; [McSema](https://blog.trailofbits.com/2018/01/23/heavy-lifting-with-mcsema-2-0/)) | Good semantics, but LLVM bitcode, not C++: an LLVM toolchain in the build (and for MinGW), no hand-editable output, and its own CFG recovery to trust. McSema is unmaintained. |
| **Ghidra P-code -> C** | Ghidra's AArch64 SLEIGH leaves many NEON instructions as opaque `CALLOTHER`s; fine for reading, not for bit-exact execution. Ghidra stays our function-boundary and naming source. |
| **RetDec and other decompilers** | Not bit-exact by design (types guessed, flags dropped). |
| **N64Recomp / XenonRecomp** ([N64Recomp](https://github.com/N64Recomp/N64Recomp), [XenonRecomp](https://cdn.jsdelivr.net/gh/hedge-dev/XenonRecomp@main/README.md)) | Other ISAs (MIPS, PowerPC), so not reusable code, but **the model we follow**: one C/C++ function per guest function over a context struct, jump tables found statically and emitted as `switch`es, indirect calls through a lookup from guest address to host function. (A project named "rexglue" from the brief couldn't be verified and isn't relied on.) |

### 2.2 Input and function boundaries

- **Input:** the ELF (`work/libSOA-3.7.0.so`, sha256-checked as the natives' tables are), its
  `.dynsym` / `.rela.plt`, and a function list: the union of the profiler's discovery (above),
  Ghidra's function boundaries (`port/decomp/*/symbols.tsv`, the project), and `.eh_frame` FDEs.
- **Blocks:** from each entry, recursive descent over dynarmic's block terminals inside the
  function's bounds; a block stops at the next known block start, so no code is duplicated.
  *Measured* (with the gap sweep): 1,243,895 blocks, 14.4 M IR instructions after the passes (2.6
  per covered guest instruction); without it 1,168,582 blocks and 13.0 M.
- **Ghidra's (or our) mistakes degrade to tail calls, never to miscompiles:** a direct branch out
  of a function's bounds becomes "call the dispatch entry for that address, then return"; falling
  off the end of a function becomes the same for the next address. A function entry nobody found
  (a target reached only through a computed address) is a **dispatch miss**, which during the
  transition goes to the JIT and is logged (`W/recomp: no function at 0x...`), and later to an
  on-demand translation at build time (the miss list is an input of the next generation).
  *Measured:* 25,496 direct branches leave their function (tail calls and boundary splits).

### 2.3 Per-instruction semantics

- **Registers:** a per-thread `St` (the register file above). Generated code reads and writes it
  through the inline ops; the prototype also tried copying used registers into C++ locals
  (`--locals`): **no gain** at `-O2` (188 KB vs 196 KB of code, the same speed), so the plain
  struct stays.
- **Flags:** NZCV in AArch64 order; an op whose flags are read returns `{value, c, o, nzcv}` and
  the pseudo-ops read the fields; dead fields vanish when the compiler inlines.
- **Memory:** plain host loads and stores (`memcpy` of the access size; unaligned is fine on
  x86-64). **TBI** (the top byte ignored, `runtime/README.md` "Platform fidelity"): the JIT gets it
  from its fault path; recompiled code would crash on a tagged address. Option A: mask every
  address (one `and` per access; measure); option B: a SIGSEGV/vectored handler that recognizes a
  non-canonical address in recompiled code, which can't resume mid-instruction in C++, so **A**,
  unless measurements say otherwise.
- **Exclusives and barriers** (*measured:* 8,712 32-bit and 465 64-bit LDXR/STXR pairs, 2,032
  DMBs, 1,968 CLREX): a per-thread monitor `{address, value}`; STXR is a host
  `compare_exchange_strong` of the recorded value (what dynarmic's global monitor does: the same
  ABA exposure as today), DMB a `std::atomic_thread_fence(seq_cst)`, acquire/release loads and
  stores `std::atomic_ref` with the matching order. (Pattern-matching LDXR/op/STXR loops into one
  host atomic is an optimization for later.)
- **System registers:** TPIDR_EL0 (359 reads) is the thread's TLS block (a field of `St`, set by
  the HLE `pthread_create` as now); CNTVCT/CNTFRQ, DCZID, CTR as the JIT's config; FPCR/FPSR reads
  (6/5) return the constant FPCR 0 and an FPSR (whether any code depends on its cumulative
  exception bits is to be checked in P0: likely only libm's `fetestexcept`-style code).
- **Floating point:** FPCR = 0 everywhere, so: host SSE arithmetic, then the AArch64 NaN rules on
  the rare NaN result (an out-of-line slow path; vector ops check the four lanes at once on the host
  SIMD unit and redo the vector lane by lane on a NaN, as dynarmic's backend does); conversions,
  rounding and estimates through dynarmic's software FP library. Build with `-ffp-contract=off`
  (as the port).
- **`BRK #1`** (419, the game's traps): the crash-report path with the guest address.
- **Self-modifying / runtime-built code:** the game builds none (no `mprotect` import and no
  cache-maintenance instruction in the lib: 0 `DC` / `IC`). Our own host-built guest code (`map_guest_code`: trampolines,
  test snippets) disappears: trampolines to originals become calls of the original's recompiled
  function (3); tests that assemble snippets keep the JIT until P4 or are rewritten.

### 2.4 Calls, returns and the stack

- **Direct calls** (*measured:* 296,689 BLs): 264,042 go through the PLT to a function **the lib
  defines itself**, 10,666 straight into `.text`, 21,981 through the PLT to one of 376 imports. The
  translator resolves a PLT stub's `R_AARCH64_JUMP_SLOT` symbol statically: the lib's own
  function -> a direct C++ call of its recompiled function (or of the dispatch entry, so a native
  override still wins: 3); an import -> a direct call of its HLE host function.
- **Returns:** `RET` is a C++ `return`; the caller continues at the label after its call. The
  guest stack is still the guest's (generated code stores x29/x30 to it as the ARM code does), so
  frame-pointer walks, `__builtin_return_address` uses and the unwinder see the same frames.
  A `RET` to an address other than the caller's return label (hand-written assembly, longjmp-like
  code) is detected in debug builds (`pc != expected` -> trap); none expected (no
  `setjmp`/`longjmp` import in the lib).
- **Indirect calls** (44,858 BLRs: virtual calls, `std::function`, callbacks): through the
  dispatch table (3).
- **Indirect jumps** (7,332 BRs inside functions): switch tables or computed tail calls. The
  translator recovers jump tables statically (the ADRP/ADD/LDR(B|H|SW)/ADD/BR idiom; bounds from the
  preceding CMP/B.HI) and emits a `switch` over the case labels; anything else, or a target outside
  the table, takes the default branch: a block start of this function -> its label (the
  prototype emits a `switch` over all block starts), else a tail call through the dispatch table.
- **Tail calls** (`B` to another function): a call through the dispatch entry, then `return`.
  Deep tail-call chains are rare in compiled C++ (no unbounded host-stack growth was seen in the
  sample); `[[clang::musttail]]` is not available in GCC, so keep an eye on recursion depth.
- **Variadic functions** need nothing special: the guest's `va_list` handling is guest code over
  the guest stack, translated like the rest; variadic **imports** (`snprintf`, ...) are HLE as now.
- **Stack arguments** are on the guest stack, as the guest code put them (the prototype's
  SpookyHash `Mix` takes 13 arguments, 5 on the stack, and matches).

### 2.5 Exceptions and unwinding

*Measured:* the lib links its own libc++abi and libunwind (`__cxa_throw`, `_Unwind_RaiseException`
are defined in it). 194 `__cxa_throw` call sites, 94 rethrows; 3,686 FDEs; **395 functions** have
landing pads (they call `_Unwind_Resume`), 373 of them in `std::__ndk1` (iostreams, locale,
strings) and a handful of game classes (`Aska::IParticleObject`, `IParticleEmitter`). Game code
mostly has no unwind info, so a throw that reaches a game frame ends in `std::terminate` on the
phone too.

- **The unwinder is guest code** and keeps working: it reads the guest stack and `.eh_frame`, both
  unchanged. What changes is the last step, `__libunwind_Registers_arm64_jumpto` (restore the
  registers, branch into the middle of a function): in recompiled code that becomes a host
  non-local exit (a C++ exception `GuestResume{pc, sp}` thrown from the jumpto's replacement and
  caught in the recompiled function whose frame matches `sp`) and a re-entry at the landing pad's
  label (each of the 395 functions gets a "resume at pc" entry: a `switch` over its landing pads).
- **Is it needed at all?** *Measured:* a login session (`port/scripts/rebase_inproc_session.sh`,
  PASS, title to the login popups with the data check) with `SOA_TRACE` on `__cxa_throw`,
  `_Unwind_RaiseException`, `__cxa_begin_catch` and `__cxa_rethrow` logged **no call of any of
  them**. So P1 can treat a throw as fatal with a clear message (`E/recomp: C++ exception thrown at
  ...`), P2 measures the other three flows the same way, and the resume mechanism is P2's last item
  (needed for correctness of unserved paths, e.g. `std::stoi` on bad input, not for the flows).

### 2.6 What the generated code looks like

```cpp
// _ZN4Aska6Matrix9TranslateEPKNS_6VectorE (0x1f3a868, 228 bytes)
void f_1f3a868(rc::St& s) {
  const u64 LIB = rc::lib_base;
L_1f3a868: {
  auto t1 = rc::GetX(s, 1);
  auto t2 = rc::ReadMemory32(s, (LIB + 0x1f3a868ull), t1, 0);
  ...
  auto t9 = rc::FPMul32(s, t4, t7);
  ...
  rc::SetPC(s, rc::GetX(s, 30));
  return;  // RET
}
}
```

Not meant to be read (the natives are the readable layer), but every block keeps its guest
address in its label and every memory access its instruction's address (for crash reports and the
GDB stub, 4). The production translator adds the disassembly as a comment per instruction.

## 3. The dispatch table and the natives

- **One table, guest address -> host function**, built at startup from the generated table (all
  recompiled functions) and then patched by `install_native_functions()`: an installed native
  replaces its entry (today it patches the guest entry with `SVC; RET`; under recomp it writes the
  table, and the guest bytes stay untouched). Lookup: a perfect hash or a sorted array of the
  ~104k entries (the prototype: binary search); XenonRecomp's trick of a flat array indexed by
  `(addr - base) / 4` costs 5.7 M entries × 8 B = 45 MB of mostly-zero virtual memory, cheap
  with lazy pages and the fastest; pick by measurement.
- **Direct calls bind once:** a direct BL to a function that has a native goes through the table
  (one indirect call); a BL to one without a native is a direct C++ call, decided at startup by a
  per-callee function pointer (the generated code calls `rc_slot[i]`, which install points at the
  native or the recompiled function). That is `NativeCallee` (`port/src/native/common/native_call.h`)
  generalized to every call: [CALLS.md](../port/src/native/CALLS.md)'s guest calls all become C++
  calls, and `guest_call(addr, ...)` becomes "set up the registers, look up, call".
- **`--natives` keeps its meaning:** `all` / `route` / `none` / `--natives-skip SUBSYS` choose
  which table entries the natives overwrite; a skipped subsystem runs its recompiled code (no JIT
  needed for the A/B of a native regression).
- **Originals:** `NATIVE_FUNCTION_ORIG`'s trampoline becomes the recompiled original
  (`rc_orig(addr)`), so no relocated-trampoline code (`common/trampoline.h`) and no "can't hook a
  4-byte function" rule.
- **Live checks** (`common/live_check.*`) compare the native against "the original": under recomp
  that is the recompiled function, called directly; the record/replay, shadow, lockstep and
  run-both families keep their logic. During the transition a second family kind, **recomp vs
  JIT** (`--live-check recomp:only=...`), runs a recompiled function and the JIT on snapshots, the
  same way the prototype's harness does, in real sessions.
- **`--selftest`:** `t.call(sym)` reaches the original, i.e. the recompiled function (no natives
  installed, as today); with `--engine jit` it reaches the JIT, so P2's selftest runs both and the
  NATIVE_TESTs double as recomp tests.

## 4. Threads and runtime changes

- **Guest threads are host threads running C++:** the HLE `pthread_create` gives a thread a guest
  stack, a TLS block and an `St`, and calls the entry's recompiled function. Gone: the per-thread,
  per-nesting-level JIT instances (`ThreadState`'s pool, the processor-id allocator, the 16 MB
  fast-dispatch tables, `release_fast_dispatch_table`), `guest_call`'s nested JIT levels and
  512-byte stack offset, `HaltExecution`, the fastmem fault handling in the crash path, the
  `invalidate_guest_code*` family and `map_guest_code` (2.3). `guest_call` stays as an API (natives
  and tests use it), implemented as a table call on the thread's `St`.
- **The profiler** (`SOA_PROFILE`): it samples guest PCs from the JIT state today. Under recomp,
  host PCs are mapped back by a generated table (host function -> guest function); `perf` works
  out of the box. `SOA_COVERAGE` becomes an opt-in instrumentation build (a counter per function),
  or is computed from `perf` samples.
- **The GDB stub:** registers come from the thread's `St` (synchronized at block boundaries, as
  with the JIT; the generated code keeps the register file in memory, so it's exact at calls).
  Breakpoints on function entries are a table flag checked by the dispatch path and by a generated
  per-function prologue in debug builds (`if (rc_bp[i]) rc_break(s, addr)`); breakpoints on
  arbitrary instructions and single-stepping need a **debug translation** (a check before every
  guest instruction, `-O0`), built as a second binary or kept to the JIT until P4. Watchpoints stay
  unsupported. The host-gdb side (`soa-native-break`) gains `soa-recomp-break ADDR`.
- **Crash reports:** a fault in recompiled code is an ordinary host fault; the report maps the host
  PC to the guest function and, via the block labels' address map, to the guest instruction
  (a generated line table: host offset -> guest address).
- **Windows:** nothing JIT-specific left: no `RtlAddFunctionTable` for JIT code, no fastmem SEH.

## 5. Build and size

*Measured* on the prototype's two samples (GCC 13, this machine, loaded by other agents' runs):

| Sample | Functions | Guest bytes | C++ lines | `-O0` .text | `-O1` .text | `-O2` .text | `-O1` compile | `-O2` compile |
|---|---|---|---|---|---|---|---|---|
| hash + math (FP-heavy, run and checked) | 83 | 34,360 | 37,972 | 1.24 MB (36x) | 273 KB (7.9x) | 188 KB (5.5x) | 7.8 s | 12.1 s |
| random functions of the whole lib (compiled only) | 3,723 | 656,560 | 569,464 | 13.3 MB (20x), 47 s | 2.42 MB (3.7x) | 2.42 MB (3.7x) | 71 s (1.8 GB RSS) | 110 s |

The random sample is 4,000 functions drawn from all 103,939 (seed 7) minus the 277 that use an
opcode the prototype doesn't implement yet (mostly vector code), so it leans slightly towards
integer code.

*Estimated* for the whole lib (22.63 MB in functions, 34.5x the random sample; the sample was
translated without the gap sweep, which adds 10% IR over the lib, so the figures are scaled by 1.1):
**~22 M lines of C++, ~95 MB of `.text` at `-O1`, ~45 CPU-minutes at `-O1`, ~70 at `-O2`** (about
2-4 minutes on 32 cores when split into a few hundred translation units; the compiler needs ~1.8 GB
per 570k-line unit, so units of ~50k lines). Tables (dispatch, line tables) add a few MB.

- **Translation units:** one file per ~200 KB of guest code in address order (~110 files of
  ~50k lines), so neighbouring functions (one class's methods, one template's instantiations) share
  a unit and a change of the translator rebuilds everything anyway.
- **Optimization levels:** hot code (the executed set from the four flows' coverage, 14.4% of the
  functions) at `-O2`; cold code at `-O1` or `-Os` (*measured* on the random sample: `-Os` 2.32 MB
  in 83 s, about `-O1`'s size; `-O0` is 5x bigger, 13.3 MB in 47 s: no). Debug info: *measured*, `-g1` makes
  the random sample's object 6x bigger (4.0 MB -> 24.9 MB, compile 71 -> 81 s), so the generated
  code gets none by default (the guest-address line table of 4 serves crash reports) and `-g1`
  with split DWARF on request.
- **Generated at build time, not committed** (D2): the lib is in git (the APK),
  the translator is ~1-2k lines of C++ linking dynarmic's frontend, and translating takes 18 s, so
  the build regenerates `build/recomp/*.cpp` whenever the lib or the translator changes ("prefer
  regeneration"). That also keeps a 20 M-line translation of the game's code out of the repository.
  T0's `generated` check doesn't need it (nothing committed); a T0 check runs the translator over the
  whole lib in `stats` mode (no undecodable instruction, no unimplemented opcode).
- **Windows (MinGW GCC):** the generated code is plain C++20 plus `__int128` and GCC vector
  extensions, both available; objects with more than 32k sections need `-Wa,-mbig-obj`. The
  cross-build doubles the compile time per release.
- **Incremental work:** the natives are unaffected (they override at run time); a translator change
  regenerates everything (minutes), so translator work is batched.

## 6. Verification

- **Per-function differential tests, generated:** for every recompiled function a harness test like
  the prototype's (random registers and memory, special float values, the JIT as the reference;
  compare result registers and every byte of the memory the arguments point at). Argument kinds
  come from the demangled signature (pointers to regions, lengths, indices, floats), with a
  per-function override file for the ones that need sane inputs. Runs as a sharded tier (T2) while
  the JIT exists. *Measured* in the prototype: 83 functions × 2,000 runs, **0 mismatches**; with
  five deliberately injected bugs it found four (NaN operand order: 56 functions failed; FPCMP's
  unordered flags: 20; an ADD carry: 4; the default NaN: 48) and **missed one** (FMAX of +0 / -0:
  random inputs rarely hit both zeros), so the generator must also emit **edge-value cases per
  opcode** (an opcode-level test of `recomp_rt.h` against the JIT running single instructions:
  every opcode × a corpus of special values), not only random function inputs.
- **The existing live checks and selftests**, retargeted (3): the natives' NATIVE_TESTs pass with
  recomp as "the original".
- **Recomp vs JIT live checks** in the four flows and `tests/diff/` while both engines exist.
- **Sessions and gates:** the T1/T2 sessions with `--engine recomp` (P1: login; P2: all), the
  Windows `win:*` runs, `tests/diff/` (recomp vs `soa-emu`'s unmodified JIT client: the strongest
  end-to-end check, since `soa-emu` keeps the JIT).
- **Code no flow runs** (85% of the functions): covered by the generated per-function tests (the
  only practical check), by opcode-level tests, and by construction (the same IR as the JIT). Leaf
  and pure functions test well; functions over game objects need the snapshot hooks the live checks
  use, so their coverage is the flows'.

## 7. Phases

| Phase | Content | Exit criteria | Estimate (agent-days) | Parallelism |
|---|---|---|---|---|
| **P0** | The translator as a real tool (`tools/recomp/`, from the prototype): all ~250 opcodes in `recomp_rt.h`, jump-table recovery (plus the gap sweep), PLT resolution, exclusives, TPIDR; the opcode-level tests; CMake target generating `build/recomp/` for a chosen function list | All opcodes implemented; every byte of every function covered by a block or known padding; the opcode tests at 0 mismatches against the JIT; hash and math (plus 2-3 more leaf subsystems) pass their NATIVE_TESTs with recompiled originals | 6-10 | 2-3 agents (opcode families: integer/flags, scalar FP, vector, memory/atomics) |
| **P1** | `--engine mixed`: the runtime's dispatch table, `St` shared with `Cpu`, guest threads starting in recompiled code, the JIT on a dispatch miss; translate the login flow's executed functions | `rebase_inproc_session` PASS with `--engine mixed` and those functions recompiled; recomp-vs-JIT live checks at 0 over login; profiler and crash reports map host PCs to guest functions | 8-12 | 3 agents (runtime dispatch + threads; profiler/crash/GDB; translator fixes) |
| **P2** | All 103,939 functions translated; per-function generated tests (sharded); exceptions (2.5); the four flows, `tests/diff/`, Windows | Every session in T1/T2 passes with `--engine recomp` and **no** JIT entry in a run (a counter that must stay 0); generated tests at 0 mismatches; Windows stage passes | 10-15 | 4-5 agents (test generator; exceptions; flows; Windows; build splitting) |
| **P3** | `recomp` the default; JIT `--engine jit` debug-only; the GDB stub on recomp (entry breakpoints, debug translation) | A batch of normal work (T2 twice) green on recomp; release packages built with recomp | 4-6 | 2 agents |
| **P4** | The JIT only behind `--engine jit` (D5): no JIT state, `map_guest_code` or fastmem handling on the default paths; `soa-emu` stays on the JIT (D6); the package exception (D1) in AGENTS.md and `tools/package.py`; the cold-code cache (D3) | `soa` runs every T0-T2 test without creating a JIT; `--engine jit` still passes T0; release packages built with recomp | 2-4 | 1-2 agents |

Total *estimated*: ~30-47 agent-days, i.e. with 3-5 agents in parallel roughly 2-3 weeks of
calendar time, P0-P1 being the critical path.

### Risks and mitigations

| Risk | Mitigation |
|---|---|
| The x64 backend and the C++ semantics disagree in a corner (NaN payloads, saturation) and the JIT is the one that's wrong | The opcode tests compare against the JIT **and**, where they disagree, against dynarmic's software FP library and the ARM ARM; a real-device check (Waydroid, `memory: waydroid-reference`) settles it |
| Compile time / memory blow up (a 2,336-byte function became 17.8 KB of host code) | Unit splitting, `-O1` for cold code, `-fno-` flags that cost time without speed (measure `-fno-tree-pta`, `-fno-gcse` on the generated units) |
| Missing function entries (computed jumps into code Ghidra and our discovery didn't find) | The dispatch-miss log in P1-P2 (with the JIT as fallback) feeds the function list; after P4 a miss is a fatal error with the address |
| Exceptions turn out to be thrown and caught through game frames | 2.5's resume mechanism; the 395 landing-pad functions are known |
| Atomics: a guest spin loop with LDXR/STXR relying on the monitor clearing on context switch | Value-based CAS (as the JIT); WFE/SEV as host yields |
| Generated code distributed by mistake | It's under `build/` only; `tools/package.py`'s scan refuses the generated sources; only the recompiled binaries are allowed, by name (D1) |

### What happens to the hand-porting waves

- **Wave B/C as planned for speed:** much of their speed motive moves to recomp (render's and
  scene's guest code gets the same 1.5-3x the prototype shows, without porting). What still pays:
  - **readability and debuggability of the code we change** (the in-process route, the restore
    work, the English text paths, anything the server-first rule makes us touch);
  - **algorithmic wins the translation can't make:** the host-side wake-up cost (`kernel` 13.5% +
    `sync` 8.9% native, mostly futex wake-ups), GL batching in `render`, host libraries at clean
    boundaries (SQLite, zlib, ...: already done);
  - **families the 1:1 translation keeps slow:** NEON-heavy code where the NaN slow paths and lane
    loops dominate (skinning, particles).
- **Decided (D4):** new Wave B/C subsystems are paused until P1 measures recomp end to end; then re-rank Wave B/C by "readable code we want"
  rather than by guest time.

## 8. Open questions for the user

Answered on 2026-10-08: "Decisions" at the top (D1-D7). The questions were: release packages and
the game-files rule; generated code in git or at build; the JIT's future; the build budget;
`soa-emu`; pausing the waves; binary size.

## The prototype (`tools/recomp-proto/`, kept)

Linux-only, not part of the CMake build or of any gate: `tools/recomp-proto/build.sh [OUT] [stats]`
(default OUT `/tmp/recomp-proto`; needs a built tree and `work/libSOA-3.7.0.so`).

| File | What |
|---|---|
| `recomp_gen.cpp` | the translator: dynarmic's `A64::Translate` per block, its IR passes, C++ out; `stats` mode over the whole lib; `emit [--locals]` for a function list; `--only-ops FILE` for size samples, `--sweep` the gap sweep (2.1) |
| `recomp_rt.h` | the register file and 121 opcodes' semantics (FPCR 0, AArch64 NaN rules, dynarmic's FPToFixed) |
| `harness.cpp` | loads the lib with the runtime (no natives), runs each function under the JIT and recompiled on the same random inputs, compares registers and memory; then times both |
| `functions.txt` | the 83 sample functions (17 hash, 66 math; 69 leaves, 14 with calls to imports or each other) and their argument kinds |

### Facts measured

- **Whole lib, `stats` mode** (18 s, 77 MB; direct control flow from each entry, covering 88.4%
  of the 22.63 MB): 103,939 functions, 1,168,582 blocks, 13,044,962 IR instructions; 250 distinct
  opcodes; 0 undecodable; calls: 296,689 direct (264,042 via the PLT to the lib's own functions,
  21,981 to 376 imports, 10,666 straight), 44,858 indirect; 85,661 returns; 7,332 indirect jumps;
  25,496 direct branches leaving a function; 419 BRK. With `--sweep` (96.7% covered):
  1,243,895 blocks, 14,370,250 IR instructions, 251 opcodes, 310,972 direct and 47,293 indirect
  calls, 7,524 indirect jumps, 128 `Interpret` terminals (zero padding).
- **Correctness:** 83 functions, 166,000 runs, 0 mismatches (both emit modes); 11,296 calls fell
  back to the JIT (imports: `memcpy`, `memset`, `strlen`, `sqrtf` through their PLT stubs).
  Injected bugs: 4 of 5 found (above). One harness bug found and fixed on the way (the JIT's vector
  registers keep the previous call's values when fewer than eight are passed).
- **Speed** (best of 9 rounds of 5,000 calls, ns per call; the JIT's includes the guest_call entry):

  | Function | JIT | recomp | |
  |---|---|---|---|
  | `Aska::Hash::CRC` (u32, 256 bytes) | 576 | 416 | 1.4x |
  | `SpookyHashV2::Update` (256 bytes; `memcpy` via the JIT fallback) | 151 | 154 | 1.0x |
  | `Aska::Matrix::Mul` | 143 | 67 | 2.1x |
  | `Aska::Matrix::Invert` | 251 | 154 | 1.6x |
  | `Aska::Matrix::ApplyVector` | 78 | 24 | 3.3x |
  | `Aska::Box::IsIntersected` | 85 | 24 | 3.5x |

- **Size and compile time:** the table in 5.
