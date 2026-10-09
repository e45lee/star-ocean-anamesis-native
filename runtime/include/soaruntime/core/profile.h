#pragma once
// Guest profiler and coverage recorder (see the "Profiling" section of port/README.md).
//
//   SOA_COVERAGE=DIR  record every guest function that executes at least once (one-shot entry
//                     traps that remove themselves on first use: no steady-state overhead)
//   SOA_PROFILE=DIR   sample every guest thread's call stack (SOA_PROFILE_HZ, default 1000)
//   SOA_PROFILE_HOST=1  also sample the host PC of threads inside native replacements (host.tsv;
//                     port/scripts/host_profile.py: self time per C++ function / transcribed body)
//
// Both write into DIR: functions.tsv (the function table), coverage.tsv, stacks.folded
// (flamegraph "folded" format), calls.tsv (call counts of HLE and native functions) and
// meta.txt. Outputs are rewritten every 10 s, on SIGUSR1, on the "profile-dump" control
// command and at exit. port/scripts/profile_report.py turns them into a report.
#include <cstdio>

#include "soaruntime/core/loader.h"

namespace soa {

// Reads the environment and, if asked to, installs the coverage traps and starts the sampler.
// Call after native replacements and traces are installed and before any guest code runs.
void profile_init(LoadedLib& lib);
// Writes the current results (no-op when profiling is off). Safe to call from any thread.
void profile_dump();
bool profile_active();
// Prints every guest thread's current call stack (needs SOA_PROFILE; threads blocked in host code
// show their full stack, threads running guest code only the levels below). For hang diagnosis.
void profile_print_thread_stacks(FILE* out);

}  // namespace soa
