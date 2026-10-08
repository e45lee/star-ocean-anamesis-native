// The guest functions the info natives call (info_guest.h).
#include "native/info/info_guest.h"

#include "native/common/guest_std.h"

namespace soa::native::info::g {

u64 sym(const char* mangled) { return guest::sym(mangled); }

void Assert(u64 file_vaddr, int line, u64 msg_vaddr) {
    static const u64 f = sym("_ZN9Framework9gDoAssertEPKciS1_z");
    guest_call(f, {at(file_vaddr), (u64)(u32)line, at(msg_vaddr)});
}

u64 vcall(const void* obj, u32 slot, std::initializer_list<u64> rest) {
    u64 a[8] = {(u64)obj};
    size_t n = 1;
    for (u64 v : rest) a[n++] = v;
    return guest_call_raw(slot_of(obj, slot), a, n, nullptr, 0, 0).x0;
}

}  // namespace soa::native::info::g
