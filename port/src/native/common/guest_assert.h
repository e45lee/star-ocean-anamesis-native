#pragma once
// Framework::gDoAssert(file, line, format, ...) called from natives that keep the guest's asserts,
// with the guest's own .rodata strings: `file` and `format` are ELF vaddrs of the lib (a Ghidra
// decompile's UNK_ / DAT_ address minus 0x100000), up to two format arguments (variadic: x3, x4).
// The shipped build's gDoAssert reports and returns, so the native goes on as the guest does.
#include "soaruntime/core/cpu.h"

namespace soa::native {

void guest_assert(u64 file_vaddr, int line, u64 format_vaddr, u64 a0 = 0, u64 a1 = 0);

}  // namespace soa::native
