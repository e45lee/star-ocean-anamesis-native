#pragma once
// Crash reports that survive a host stack overflow (runtime/README.md "Crash reports").
//
// Every thread the runtime creates calls crash_thread_begin() first (guest threads in the HLE'd
// pthread_create, the main thread in cpu_global_init, the runtime's own std::threads at the top of
// their functions, and any other thread on its first guest code through guest_thread_init). It
// records the thread's name and host stack bounds and makes the fault handlers able to run on a
// thread whose stack is used up:
//   Linux: an alternate signal stack (kCrashAltStack, freed at thread exit); the handlers are
//          installed with SA_ONSTACK (dynarmic's SIGSEGV handler is too, and chains to ours).
//   Windows: SetThreadStackGuarantee(kCrashAltStack), so the vectored handler for
//          EXCEPTION_STACK_OVERFLOW has stack left to run on.
// The fault handlers (core/cpu.cpp) then print
//   "stack overflow on thread NAME (stack N KiB, used ~M KiB)"
// before the usual report (host backtrace, guest pc and registers).
#include <cstddef>
#include <cstdint>

namespace soa {

inline constexpr size_t kCrashAltStack = 64 << 10;

// Sets up the calling thread (idempotent: a later call only renames it). `name` is copied
// (truncated to 31 characters); `guest_entry`, when not 0, is the guest function the thread runs
// (named in the report).
void crash_thread_begin(const char* name, uint64_t guest_entry = 0);
// Renames the calling thread (the guest's prctl(PR_SET_NAME)); sets it up first if needed.
void crash_thread_set_name(const char* name);

// What the fault handlers know about the faulting thread.
struct CrashThread {
    char name[32] = {};
    uintptr_t lo = 0, hi = 0;  // the usable host stack (lo: the lowest usable byte)
    size_t guard = 0;          // the guard region below lo (Linux; 0 when unknown)
    uint64_t guest_entry = 0;
    void* alt = nullptr;  // our alternate signal stack's mapping (Linux), or nullptr
    bool active = false;
};
// The calling thread's record, or nullptr for a thread nobody set up.
const CrashThread* crash_thread();
// Whether a fault at `addr` with stack pointer `sp` ran out of the thread's host stack.
bool crash_is_stack_overflow(const CrashThread& t, uintptr_t addr, uintptr_t sp);
// Prints the overflow headline (and the thread's guest entry) to stderr.
void crash_report_overflow(const CrashThread& t, uintptr_t sp);

}  // namespace soa
