// Framework::gDoAssert from natives (guest_assert.h).
#include "native/common/guest_assert.h"

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/loader.h"
#include "native/common/guest_std.h"

namespace soa::native {

void guest_assert(u64 file_vaddr, int line, u64 format_vaddr, u64 a0, u64 a1) {
    static const u64 fn = guest::sym("_ZN9Framework9gDoAssertEPKciS1_z");
    u64 base = main_lib()->base;
    guest_call(fn, {base + file_vaddr, (u64)line, base + format_vaddr, a0, a1});
}

}  // namespace soa::native
