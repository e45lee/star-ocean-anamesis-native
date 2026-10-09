// The guest functions the params natives call (params_guest.h).
#include "native/params/params_guest.h"

#include "native/common/guest_std.h"
#include "native/common/live_leaf.h"
#include "native/common/native_call.h"
#include "native/memory/memory_callees.h"

namespace soa::native::params::g {

namespace {
// Other subsystems' natives, called as C++ when installed (native_call.h).
using memory::CAssignedMemoryManagerForSTLAllocator;
NativeCallee kAMapGet{"data_formats", "_ZN4Aska4ASON6AValue4AMap4Get_EPKc"};
NativeCallee kGrowBy{"libcxx",
                     "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE9__grow_"
                     "byEmmmmmm",
                     &live::leaf_method<&String::__grow_by>};
NativeCallee kGrowByAndReplace{"libcxx",
                               "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__"
                               "grow_by_and_replaceEmmmmmmPKc",
                               &live::leaf_method<&String::__grow_by_and_replace>};
using memory::kStlAllocateCallee;
using memory::kStlFreeCallee;
}  // namespace

u64 sym(const char* mangled) { return guest::sym(mangled); }

void Assert(u64 file_vaddr, int line, u64 msg_vaddr) {
    static const u64 f = sym("_ZN9Framework9gDoAssertEPKciS1_z");
    guest_call(f, {at(file_vaddr), (u64)(u32)line, at(msg_vaddr)});
}

const AValue* AMapGet(const AMap* map, const char* key) {
    if (kAMapGet.direct()) return const_cast<AMap*>(map)->Get_(key);
    return (const AValue*)guest_call(kAMapGet.addr(), {(u64)map, (u64)key});
}

s32 StringToInt(const char* s) {
    static const u64 f = sym("_Z14StringToNumberIiET_Pc");
    return (s32)guest_call(f, {(u64)s});
}
u32 StringToUInt(const char* s) {
    static const u64 f = sym("_Z14StringToNumberIjET_Pc");
    return (u32)guest_call(f, {(u64)s});
}
s64 StringToLong(const char* s) {
    static const u64 f = sym("_Z14StringToNumberIlET_Pc");
    return (s64)guest_call(f, {(u64)s});
}
u64 StringToULong(const char* s) {
    static const u64 f = sym("_Z14StringToNumberImET_Pc");
    return guest_call(f, {(u64)s});
}
u8 StringToUTiny(const char* s) {
    static const u64 f = sym("_Z14StringToNumberIhET_Pc");
    return (u8)guest_call(f, {(u64)s});
}

void GrowBy(String* s, u64 old_cap, u64 delta_cap, u64 old_sz, u64 n_copy, u64 n_del, u64 n_add) {
    if (kGrowBy.direct()) return s->__grow_by(old_cap, delta_cap, old_sz, n_copy, n_del, n_add);
    guest_call(kGrowBy.addr(), {(u64)s, old_cap, delta_cap, old_sz, n_copy, n_del, n_add});
}
void GrowByAndReplace(String* s, u64 old_cap, u64 delta_cap, u64 old_sz, u64 n_copy, u64 n_del, u64 n_add, const char* p) {
    if (kGrowByAndReplace.direct()) return s->__grow_by_and_replace(old_cap, delta_cap, old_sz, n_copy, n_del, n_add, p);
    guest_call(kGrowByAndReplace.addr(), {(u64)s, old_cap, delta_cap, old_sz, n_copy, n_del, n_add, (u64)p});
}

void* StlAllocate(u64 n, u64 file_vaddr, u32 line) {
    if (kStlAllocateCallee.direct()) return CAssignedMemoryManagerForSTLAllocator::Allocate(n, (const char*)at(file_vaddr), line);
    return (void*)guest_call(kStlAllocateCallee.addr(), {n, at(file_vaddr), (u64)line});
}
void StlFree(void* p) {
    if (kStlFreeCallee.direct()) return CAssignedMemoryManagerForSTLAllocator::Free(p);
    guest_call(kStlFreeCallee.addr(), {(u64)p});
}

}  // namespace soa::native::params::g
