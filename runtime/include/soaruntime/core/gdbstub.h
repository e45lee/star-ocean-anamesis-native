#pragma once
// A GDB remote-serial-protocol stub for the GUEST (AArch64) running on the JIT (runtime/README.md
// "Debugging the guest with gdb"). `--gdb HOST:PORT` on soa / soa-emu / soa-viewer calls gdb_listen():
// gdb-multiarch (or control/gdbclient.py) can then attach to the running client, stop every guest
// thread, read and write registers and memory, set breakpoints, single-step and continue; the
// client keeps running after the debugger detaches. Off by default; when off, the JIT's hot path
// is unchanged (one predictable branch per guest_call and per host-function call).
//
// All-stop: a stop halts every guest CPU at its next block boundary (dynarmic HaltExecution with
// kGdbHalt); a thread that is in a host function (an HLE import, a native) is stopped as far as gdb
// is concerned and parks when it returns to guest code. Breakpoints are BRK instructions written
// over the guest code (and hidden from memory reads); the JIT's translations of the word are
// invalidated in every thread. Single-step runs one instruction with dynarmic's Step() on the
// thread's own JIT. A breakpoint on a native (a guest function replaced by host code) stops the
// thread before the native runs (gdb_call_native). Linux and Windows (sockets through soa/sock.h).
#include <string>

#include "soaruntime/core/cpu.h"

namespace soa {

// Starts the stub's server thread on HOST:PORT (also "[IPV6]:PORT", ":PORT" / "PORT": 127.0.0.1;
// port 0 picks a free one, see gdb_port()) and turns the debugger hooks on. Call it once, before
// guest code runs. Returns false (and sets *err) when the address doesn't parse or can't be bound.
bool gdb_listen(const std::string& host_port, std::string* err = nullptr);
// The bound TCP port (0 before gdb_listen).
int gdb_port();
// Detaches any debugger (breakpoints removed, guest resumed) and stops the server (tests).
void gdb_shutdown();

// Stop signals as the GDB remote protocol numbers them (gdb's own numbering: Linux's, except BUS),
// on every host.
constexpr int kGdbSigInt = 2, kGdbSigIll = 4, kGdbSigTrap = 5, kGdbSigAbrt = 6, kGdbSigFpe = 8, kGdbSigBus = 10,
              kGdbSigSegv = 11;

// ---- hooks for core/cpu.cpp ----
extern bool g_gdb_enabled;                 // set by gdb_listen, before guest code runs
constexpr u32 kGdbHalt = 0x08000000;       // Dynarmic::HaltReason::UserDefined4
// True while a debugger holds the guest stopped (checked when a thread enters the JIT).
bool gdb_stopped();
// The calling guest thread's JIT returned with kGdbHalt (or it entered while stopped): park here
// until the debugger resumes or steps this thread. Clears kGdbHalt on `c` before returning.
void gdb_park(Cpu& c);
// A BRK at `pc` raised by the JIT: true when it is one of the debugger's breakpoints (the world is
// then being stopped; the caller resets the PC to `pc`).
bool gdb_breakpoint_hit(Cpu& c, u64 pc);
// A fatal guest fault (a host fault in guest context: a signal on Linux, an unhandled exception on
// Windows; an unimplemented instruction; a guest exception): an attached debugger gets the stop
// (`gdb_sig`, one of the kGdbSig* above) and the thread waits until it continues or detaches; then
// the caller goes on to crash as before.
void gdb_fault(Cpu* c, int gdb_sig);

// Breakpoints on natives (a guest entry replaced by hook_guest_function: its first word is the
// hook's SVC, so no BRK goes there). True while the debugger has at least one: then CallSVC and the
// direct host call run a hooked function through gdb_call_native instead of calling it.
bool gdb_native_breakpoints();
// Runs `fn`, the native behind the hooked guest entry `hook`, on `c` (PC = hook + 4, the guest's
// arguments in its registers). With a breakpoint at `hook`, the world stops first, reported at
// `hook` (swbreak) with the arguments as the native will see them; continuing runs the native, a
// step runs all of it and stops at hook + 4 (the hook's RET), a PC moved by the debugger skips it.
// `in_jit`: called from the JIT (CallSVC), so a stop after the native parks when the JIT returns;
// false for a direct host call (no JIT to return to: the thread waits here).
void gdb_call_native(Cpu& c, u64 hook, HostFn fn, bool in_jit);

// ---- for tests (soaruntime_tests --gdb-demo; runtime/tests/gdbstub_test.cpp) ----
// Called by a guest thread on its way to park (its JIT returned with kGdbHalt, or a step ran a native
// and it goes back to its JIT), just before (null: nothing).
// --slow-park sleeps there, widening the moment between the JIT's return and the park.
extern void (*g_gdb_before_park)();
// Stops the guest the next time a thread reaches `addr` (a temporary breakpoint, removed again) and
// waits until that thread has parked there, as if a debugger had stopped it: the next debugger to
// attach finds it stopped at `addr`. False when no thread got there within `timeout_ms`. Guest code
// only: on a native's entry (a hooked function) it times out (those breakpoints stop only an attached debugger).
bool gdb_stop_at(u64 addr, int timeout_ms);

}  // namespace soa
