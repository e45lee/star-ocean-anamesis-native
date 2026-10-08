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

void String::init(std::string_view s) {
    init();
    size_t n = s.size();
    if (n < 23) {
        raw[0] = (unsigned char)(n << 1);
        std::memcpy(raw + 1, s.data(), n);
        raw[1 + n] = 0;
        return;
    }
    // libc++: allocation = round_up(n + 1, 16); stored capacity word = allocation | 1.
    u64 alloc = (n + 16) & ~15ull;
    char* p = (char*)stl_alloc(alloc);
    if (!p) fatal("guest string allocation of %" PRIu64 " bytes failed", alloc);
    std::memcpy(p, s.data(), n);
    p[n] = 0;
    u64 cap = alloc | 1, size = n, ptr = (u64)p;
    std::memcpy(raw, &cap, 8);
    std::memcpy(raw + 8, &size, 8);
    std::memcpy(raw + 16, &ptr, 8);
}

void String::destroy() {
    if (is_long()) stl_free((void*)data());
    init();
}

void String::assign(std::string_view s) {
    // s may alias our own buffer: copy first.
    std::string copy(s);
    destroy();
    init(copy);
}

void StringList::push_back(std::string_view s) {
    auto* n = (Node*)stl_alloc(sizeof(Node));
    if (!n) fatal("guest list node allocation failed");
    n->value.init(s);
    n->next = (u64)this;
    n->prev = prev;
    ((Node*)prev)->next = (u64)n;  // prev is the sentinel itself when empty (its 'next' field)
    prev = (u64)n;
    count++;
}

}  // namespace soa::guest
