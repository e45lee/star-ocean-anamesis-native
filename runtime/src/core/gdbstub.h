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
// thread's own JIT.
#include <string>

#include "core/cpu.h"

namespace soa {

// Starts the stub's server thread on HOST:PORT (also ":PORT" / "PORT": 127.0.0.1; port 0 picks a
// free one, see gdb_port()) and turns the debugger hooks on. Call it once, before guest code runs.
// Returns false (and sets *err) when the address doesn't parse or can't be bound.
bool gdb_listen(const std::string& host_port, std::string* err = nullptr);
// The bound TCP port (0 before gdb_listen).
int gdb_port();
// Detaches any debugger (breakpoints removed, guest resumed) and stops the server (tests).
void gdb_shutdown();

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
// A fatal guest fault (host signal in guest context, an unimplemented instruction, a guest
// exception): an attached debugger gets the stop (signal `signo`) and the thread waits until it
// continues or detaches; then the caller goes on to crash as before.
void gdb_fault(Cpu* c, int signo);

}  // namespace soa
