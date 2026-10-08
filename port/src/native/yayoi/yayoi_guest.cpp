// The guest functions the SQLite driver's natives call (yayoi_guest.h).
#include "native/yayoi/yayoi_guest.h"

#include <vector>

#include "core/loader.h"
#include "native/common/native_call.h"
#include "native/common/test.h"
#include "native/data_formats/data_formats_layout.h"

namespace soa::native::yayoi::gfn {

namespace {
using data_formats::ASON;
using data_formats::AValue;

// data_formats' natives, called as C++ when installed (native_call.h).
NativeCallee kMakeArray{"data_formats", "_ZN4Aska4ASON16MakeAValue_ArrayEPNS0_6AValueEj"};
NativeCallee kMakeMap{"data_formats", "_ZN4Aska4ASON14MakeAValue_MapEPNS0_6AValueEj"};
NativeCallee kMalloc{"data_formats", "_ZN4Aska4ASON6MallocEm"};

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
    if (kMakeArray.direct()) return static_cast<ASON*>(ason)->MakeAValue_Array(static_cast<AValue*>(value), n).code;
    return call_status(kMakeArray.addr(), {(u64)ason, (u64)value, (u64)n});
}
s64 ason_make_map(void* ason, void* value, u32 n) {
    if (kMakeMap.direct()) return static_cast<ASON*>(ason)->MakeAValue_Map(static_cast<AValue*>(value), n).code;
    return call_status(kMakeMap.addr(), {(u64)ason, (u64)value, (u64)n});
}
void* ason_malloc(void* ason, u64 n) {
    if (kMalloc.direct()) return static_cast<ASON*>(ason)->Malloc(n);
    return (void*)guest_call(kMalloc.addr(), {(u64)ason, n});
}
s64 ason_calc_serialized_size(const void* ason) {
    static const u64 fn = guest::sym("_ZNK4Aska4ASON18CalcSerializedSizeEv");
    return (s64)guest_call(fn, {(u64)ason});
}
s64 ason_serialize(const void* ason, void* out, u64 size) {
    static const u64 fn = guest::sym("_ZNK4Aska4ASON9SerializeEPvm");
    return (s64)guest_call(fn, {(u64)ason, (u64)out, size});
}


// The direct path's glue (native_call.h): the same ASON built through the guest entries (the guest's
// code in --selftest) and through the natives as C++ (kMalloc / kMakeArray / kMakeMap switched on for
// the test) must end with the same statuses, allocation offsets and work-buffer bookkeeping.
NATIVE_TEST("yayoi/direct-ason-calls") {
    using namespace soa::native::yayoi::gfn;
    struct Trace {
        std::vector<s64> v;
    };
    auto build = [&](bool direct) {
        kMalloc.set_direct_for_test(direct);
        kMakeArray.set_direct_for_test(direct);
        kMakeMap.set_direct_for_test(direct);
        Trace tr;
        alignas(16) ASON a;
        ason_ctor(&a);
        tr.v.push_back(ason_init(&a, 0x2000, true));
        tr.v.push_back(ason_make_array(&a, &a.m_root, 3));
        const u64 sizes[] = {1, 7, 0x40, 0x1000, 0x1800, 3, 0x900, 0x3000, 5};
        for (u64 n : sizes) {
            const s8* p = static_cast<const s8*>(ason_malloc(&a, n));
            const data_formats::ASON_WorkBufferContext* w = a.m_currentWork;
            tr.v.push_back(p ? p - w->m_buffer : -1);
            tr.v.push_back((s64)w->m_used);
            tr.v.push_back((s64)a.m_workIndex);
        }
        alignas(16) AValue v{};
        tr.v.push_back(ason_make_map(&a, &v, 4));
        tr.v.push_back((s64)a.m_currentWork->m_used);
        ason_dtor(&a);
        kMalloc.set_direct_for_test(false);
        kMakeArray.set_direct_for_test(false);
        kMakeMap.set_direct_for_test(false);
        return tr.v;
    };
    std::vector<s64> guest = build(false), native = build(true);
    t.expect_eq(guest.size(), native.size(), "trace length");
    for (size_t i = 0; i < guest.size() && i < native.size(); i++)
        if (guest[i] != native[i]) t.fail("step %zu: guest %lld, native as C++ %lld", i, (long long)guest[i], (long long)native[i]);
}

}  // namespace soa::native::yayoi::gfn
