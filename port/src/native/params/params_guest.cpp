// The guest functions the params natives call (params_guest.h).
#include "native/params/params_guest.h"

#include "native/common/guest_std.h"

namespace soa::native::params::g {

u64 sym(const char* mangled) { return guest::sym(mangled); }

void Assert(u64 file_vaddr, int line, u64 msg_vaddr) {
    static const u64 f = sym("_ZN9Framework9gDoAssertEPKciS1_z");
    guest_call(f, {at(file_vaddr), (u64)(u32)line, at(msg_vaddr)});
}

const AValue* AMapGet(const AMap* map, const char* key) {
    static const u64 f = sym("_ZN4Aska4ASON6AValue4AMap4Get_EPKc");
    return (const AValue*)guest_call(f, {(u64)map, (u64)key});
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
    static const u64 f = sym(
        "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE9__grow_"
        "byEmmmmmm");
    guest_call(f, {(u64)s, old_cap, delta_cap, old_sz, n_copy, n_del, n_add});
}
void GrowByAndReplace(String* s, u64 old_cap, u64 delta_cap, u64 old_sz, u64 n_copy, u64 n_del, u64 n_add, const char* p) {
    static const u64 f = sym(
        "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_"
        "by_and_replaceEmmmmmmPKc");
    guest_call(f, {(u64)s, old_cap, delta_cap, old_sz, n_copy, n_del, n_add, (u64)p});
}

void* StlAllocate(u64 n, u64 file_vaddr, u32 line) {
    static const u64 f = sym("_ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj");
    return (void*)guest_call(f, {n, at(file_vaddr), (u64)line});
}
void StlFree(void* p) {
    static const u64 f = sym("_ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv");
    guest_call(f, {(u64)p});
}

}  // namespace soa::native::params::g
