#include "native/common/guest_std.h"

#include <cinttypes>

#include "core/loader.h"
#include "core/log.h"
#include "native/memory/memory_callees.h"

namespace soa::guest {

namespace {
// memory's natives, called as C++ when installed (native/common/native_call.h).
using native::memory::CAssignedMemoryManagerForSTLAllocator;
using native::memory::kStlAllocateCallee;
using native::memory::kStlFreeCallee;
}  // namespace

u64 sym(const char* mangled) {
    u64 a = main_lib()->sym(mangled);
    if (!a) fatal("guest symbol %s not found", mangled);
    return a;
}

// The game's own allocators (the STL allocator: memory's natives, else the guest's).
void* stl_alloc(size_t n) {
    static const char* file = "native";
    if (kStlAllocateCallee.direct()) return CAssignedMemoryManagerForSTLAllocator::Allocate(n, file, 0);
    return (void*)guest_call(kStlAllocateCallee.addr(), {(u64)n, (u64)file, 0});
}

void stl_free(void* p) {
    if (kStlFreeCallee.direct()) return CAssignedMemoryManagerForSTLAllocator::Free(p);
    guest_call(kStlFreeCallee.addr(), {(u64)p});
}

void* new_array_nothrow(size_t n) {
    static const u64 fn = sym("_ZnamRKSt9nothrow_t");
    static const u64 nothrow = 0;  // std::nothrow_t (empty; only its address is passed)
    return (void*)guest_call(fn, {(u64)n, (u64)&nothrow});
}

void delete_array(void* p) {
    static const u64 fn = sym("_ZdaPv");
    guest_call(fn, {(u64)p});
}

}  // namespace soa::guest

// libcxx_layout.h's host-side string helpers allocate from the game's STL allocator.
namespace soa::native::libcxx {

void* host_string_alloc(u64 bytes) {
    void* p = guest::stl_alloc(bytes);
    if (!p) fatal("guest string allocation of %" PRIu64 " bytes failed", bytes);
    return p;
}

void host_string_free(void* p) { guest::stl_free(p); }

}  // namespace soa::native::libcxx
