#pragma once
// The a2c register file: the ARM64 registers as a plain struct, for code that calls out of native
// C++ with a full guest register set and records those calls (live_check.h: Family::gcall,
// ACall). tools/a2c.py's transcriptions ran on it too; none are left since the rebase's revision 2
// (docs/history/PLAN-rebase-370.md), and new natives are readable C++ (native/README.md), but the live
// check keeps the register-file interface (its record / replay works on A64).
#include <cstdint>

#include "core/cpu.h"

namespace soa::a2c {

struct V4 {
    float f[4];
};
struct A64 {
    std::uint64_t x[32];  // x[31] = the body's SP
    V4 v[32];
    std::uint32_t nzcv;
};
// A body on the register file (a transcribed function, or a readable one with that interface).
using Body = void (*)(A64&);

// A guest call with x0-x7, v0-v7, x8 and the body's stack slots (from r.x[31]) taken from the
// register file; x0/x1 and v0-v3 come back. A target that is itself a native replacement is
// called directly on the current CPU.
void a2c_gcall(A64& r, std::uint64_t target);
// Guest hook: runs a body on the guest's registers and stack (x0/x1, v0-v3 go back).
void a2c_run_hook(Cpu& c, Body body);

}  // namespace soa::a2c
