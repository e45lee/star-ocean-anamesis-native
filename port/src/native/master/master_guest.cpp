// The guest functions the master natives call (master_guest.h).
#include "native/master/master_guest.h"

#include "native/common/gen/common_addresses.h"
#include "native/common/guest_std.h"
#include "native/common/live_call.h"
#include "native/master/master_family.h"
#include "native/memory/memory_callees.h"

namespace soa::native::master::g {

u64 sym(const char* mangled) { return guest::sym(mangled); }

void* StringAllocate(u64 n) {
    using memory::kStlAllocateCallee;
    if (kStlAllocateCallee.direct())
        return memory::CAssignedMemoryManagerForSTLAllocator::Allocate(n, (const char*)at(native::kStrStlStringH), 0x1c);
    return (void*)live::out_call(family(), kStlAllocateCallee.addr(), {n, at(native::kStrStlStringH), 0x1c});
}

void StlFree(void* p) {
    if (memory::kStlFreeCallee.direct()) return memory::CAssignedMemoryManagerForSTLAllocator::Free(p);
    live::out_call(family(), memory::kStlFreeCallee.addr(), {(u64)p});
}

void OperatorDelete(void* p) {
    static const u64 f = sym("_ZdlPv");
    live::out_call(family(), f, {(u64)p});
}

void Assert(u64 file_vaddr, int line, u64 msg_vaddr) {
    static const u64 f = sym("_ZN9Framework9gDoAssertEPKciS1_z");
    live::out_call(family(), f, {at(file_vaddr), (u64)(u32)line, at(msg_vaddr)});
}

}  // namespace soa::native::master::g

namespace soa::native::master {
void g_operator_delete(void* p) { g::OperatorDelete(p); }
}  // namespace soa::native::master
