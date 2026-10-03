// wrap_method / NATIVE_METHOD (native_method.h): a member function called the way guest code calls
// the guest method (this in x0, then the arguments), through an SVC thunk.
#include <cstddef>

#include "native/common/native_method.h"
#include "native/common/test.h"

namespace soa {
namespace {

class Probe {
public:
    u32 Add(u32 a, float b) const { return m_id + a + (u32)(b * 2.0f); }
    void Set(u32 v, double d, const char* s) {
        m_id = v;
        m_d = d;
        m_s = s;
    }
    float Half() const { return (float)m_id / 2.0f; }

    const void* vtable;  // 0x00
    u32 m_id;            // 0x08
    u8 unk_0c[4];        // 0x0c
    double m_d;          // 0x10
    const char* m_s;     // 0x18
};
static_assert(offsetof(Probe, m_id) == 0x08 && offsetof(Probe, m_d) == 0x10 && sizeof(Probe) == 0x20);

NATIVE_TEST("native/method-binding") {
    static const u64 add = make_thunk("test:Probe::Add", wrap_method<&Probe::Add>());
    static const u64 set = make_thunk("test:Probe::Set", wrap_method<&Probe::Set>());
    static const u64 half = make_thunk("test:Probe::Half", wrap_method<&Probe::Half>());
    Probe p{};
    p.m_id = 40;
    t.expect_eq(guest_invoke<u32>(add, &p, 2u, 1.5f), 45u, "a const member: this in x0, an int in x1, a float in v0");
    guest_invoke<void>(set, &p, 7u, 2.5, "x");
    t.expect_eq(p.m_id == 7 && p.m_d == 2.5 && p.m_s && p.m_s[0] == 'x', true, "a member with int, double and pointer arguments");
    t.expect_eq(guest_invoke<float>(half, &p), 3.5f, "a float result in v0");
}

}  // namespace
}  // namespace soa
