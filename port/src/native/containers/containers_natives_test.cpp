// Differential tests of the `containers` natives against the 3.7.0 guest (--selftest containers/):
// the guest functions run as ARM64 code (natives aren't installed in --selftest), the natives on the
// same inputs (random, plus the shapes the game uses).
#include <cstring>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/containers/containers_layout.h"
#include "native/containers/containers_object_container.h"

namespace soa::native::containers {
namespace {

std::string rand_text(TestContext& t, size_t maxlen) {
    std::string s((size_t)t.rand_int(0, (int)maxlen), ' ');
    for (auto& c : s) c = (char)t.rand_int(1, 255);
    return s;
}

NATIVE_TEST("containers/utf8-to-multibyte") {
    constexpr const char* kSym = "_ZN4Aska13StringUtility15Utf8ToMultiByteEPKcPcj";
    for (int k = 0; k < 400; k++) {
        std::string s = k % 5 == 0 ? std::string("Character/cp0303/role_cp0303_b04a_6131.aif") : rand_text(t, k % 3 ? 40 : 300);
        int mode = t.rand_int(0, 4);  // 0: size query, 1: copy with a cap, 2: null dst + cap, 3: dst + cap 0, 4: exact cap
        u32 cap = mode == 1 ? (u32)t.rand_int(1, 400) : mode == 2 ? 5 : mode == 4 ? (u32)s.size() + 1 : 0;
        bool dst = mode == 1 || mode == 3 || mode == 4;
        std::vector<char> g(512, '\x5a'), n(512, '\x5a');
        u32 rg = (u32)t.call(kSym, {(u64)s.c_str(), dst ? (u64)g.data() : 0, cap});
        u32 rn = (u32)StringUtility::Utf8ToMultiByte(s.c_str(), dst ? n.data() : nullptr, cap);
        if (rg != rn || g != n) {
            t.fail("case %d (mode %d, len %zu, cap %u): guest %#x native %#x%s", k, mode, s.size(), cap, rg, rn, g != n ? ", bytes differ" : "");
            return;
        }
    }
}

// The accessors of the four executed TObjectContainer instantiations on containers with the guest's
// vtable (slot 4 = the instantiation's own NumElements).
template <typename T>
void objc_case(TestContext& t, const char* mangled) {
    using C = memory::TObjectContainer<T>;
    std::string m = mangled;
    std::string vt = "_ZTVN9Framework16TObjectContainer" + m + "E";
    std::string num = "_ZNK9Framework16TObjectContainer" + m + "11NumElementsEv";
    std::string r = "_ZN9Framework16TObjectContainer" + m + "8rElementEm";
    std::string cr = "_ZNK9Framework16TObjectContainer" + m + "9crElementEm";
    std::vector<u8> storage(64 * sizeof(T));
    for (int k = 0; k < 30; k++) {
        C c{};
        c.vtable = (const void*)(t.sym(vt.c_str()) + 0x10);
        c.m_count = (u64)t.rand_int(1, 64);
        c.m_elements = reinterpret_cast<T*>(storage.data());
        u64 i = (u64)t.rand_int(0, (int)c.m_count - 1);
        u64 gn = t.call(num.c_str(), {(u64)&c}), gr = t.call(r.c_str(), {(u64)&c, i}), gcr = t.call(cr.c_str(), {(u64)&c, i});
        u64 nn = c.NumElements(), nr = (u64)c.rElement(i), ncr = (u64)c.crElement(i);
        if (gn != nn || gr != nr || gcr != ncr) {
            t.fail("%s: count %llu i %llu: guest %llu %#llx %#llx native %llu %#llx %#llx", mangled, (unsigned long long)c.m_count, (unsigned long long)i,
                   (unsigned long long)gn, (unsigned long long)gr, (unsigned long long)gcr, (unsigned long long)nn, (unsigned long long)nr, (unsigned long long)ncr);
            return;
        }
    }
}

NATIVE_TEST("containers/object-container") {
    objc_case<memory::SoundElement>(t, "INS_6CSound8CElementEE");
    objc_case<memory::CollisionShapeGroup>(t, "IN9Collision19CollisionShapeGroupEE");
    objc_case<memory::IFixedLengthAllocatorRef*>(t, "IPNS_21IFixedLengthAllocatorEE");
    objc_case<memory::BehaviorQueueRef*>(t, "IP13BehaviorQueueE");
}

}  // namespace
}  // namespace soa::native::containers

