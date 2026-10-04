// The guest functions the SQLite driver's natives call (yayoi_guest.h).
#include "native/yayoi/yayoi_guest.h"

#include "core/loader.h"

namespace soa::native::yayoi::gfn {

namespace {
// A guest call whose Aska::Status comes back through x8.
s64 call_status(u64 fn, std::initializer_list<u64> args) {
    s64 st = 0;
    GuestArgs a;
    for (u64 v : args) a.i(v);
    a.sret(&st);
    guest_call(fn, a);
    return st;
}
}  // namespace

void ason_ctor(void* ason) {
    static const u64 fn = guest::sym("_ZN4Aska4ASONC1Ev");
    guest_call(fn, {(u64)ason});
}
void ason_dtor(void* ason) {
    static const u64 fn = guest::sym("_ZN4Aska4ASOND1Ev");
    guest_call(fn, {(u64)ason});
}
s64 ason_init(void* ason, u32 work_size, bool keep_cstrings) {
    static const u64 fn = guest::sym("_ZN4Aska4ASON4InitEjb");
    return (s64)guest_call(fn, {(u64)ason, (u64)work_size, (u64)keep_cstrings});
}
s64 ason_make_array(void* ason, void* value, u32 n) {
    static const u64 fn = guest::sym("_ZN4Aska4ASON16MakeAValue_ArrayEPNS0_6AValueEj");
    return call_status(fn, {(u64)ason, (u64)value, (u64)n});
}
s64 ason_make_map(void* ason, void* value, u32 n) {
    static const u64 fn = guest::sym("_ZN4Aska4ASON14MakeAValue_MapEPNS0_6AValueEj");
    return call_status(fn, {(u64)ason, (u64)value, (u64)n});
}
void* ason_malloc(void* ason, u64 n) {
    static const u64 fn = guest::sym("_ZN4Aska4ASON6MallocEm");
    return (void*)guest_call(fn, {(u64)ason, n});
}
s64 ason_calc_serialized_size(const void* ason) {
    static const u64 fn = guest::sym("_ZNK4Aska4ASON18CalcSerializedSizeEv");
    return (s64)guest_call(fn, {(u64)ason});
}
s64 ason_serialize(const void* ason, void* out, u64 size) {
    static const u64 fn = guest::sym("_ZNK4Aska4ASON9SerializeEPvm");
    return (s64)guest_call(fn, {(u64)ason, (u64)out, size});
}

}  // namespace soa::native::yayoi::gfn
