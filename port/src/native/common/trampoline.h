#pragma once
// A trampoline to a hooked guest function's original code whose first two instructions are
// PC-relative (core/cpu.h make_original_trampoline refuses those): the two instructions relocated,
// then a branch to the rest of the function (entry + 8). Relocated: ADR / ADRP (the address loaded
// from a literal), B / BL (an absolute branch through x16), B.cond / CBZ / CBNZ / TBZ / TBNZ (the
// same test, branching to an absolute-branch stub). LDR (literal) isn't: 0. x16 (IP0) is clobbered,
// as a veneer may at any call. Call it before the entry is patched.
#include "soaruntime/core/cpu.h"

namespace soa {

// make_original_trampoline when it can, else the relocating one; 0 when neither can.
u64 make_relocated_trampoline(u64 guest_addr);

}  // namespace soa
