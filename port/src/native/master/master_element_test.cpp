// Differential tests of the element natives (master_element.cpp) against the guest's code, for every
// generated element class (gen/master_elements.h): the guest's method on one element, the native on
// a twin (same bytes, its long strings in storage of their own), compared byte for byte (strings by
// representation, pointers into each run's own elements mapped onto each other).
//   master/elements-ctor-init: the exported default constructor (else the native's on both), then
//     Initialize (names, flags, defaults, the AddProperty list), on 0xa5-filled memory;
//   master/elements-copy-assign-dtor: random values and strings (empty, short, 22, 23, long; a
//     destination of every capacity), the copy constructor, operator= (also onto itself), the
//     destructor; the deleting destructor on an operator new block.
#include <cstring>
#include <string>
#include <vector>

#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "native/libcxx/libcxx_string.h"
#include "native/master/master_element.h"
#include "native/master/master_guest.h"
#include "native/params/params_check.h"

namespace soa::native::master {

namespace {

struct Elem {
    std::vector<u64> w;
    explicit Elem(u32 size, u8 fill) : w((size + 7) / 8) { std::memset(w.data(), fill, w.size() * 8); }
    u8* p() { return reinterpret_cast<u8*>(w.data()); }
};

// A string of `len` random letters into `s` (an empty or freed one): long ones from the STL allocator.
void make_string(TestContext& t, String& s, u64 len, u64 extra_cap = 0) {
    std::memset(&s, 0, sizeof s);
    char* to;
    if (len < 23 && !extra_cap) {
        s.r.s.head.size = (u8)(len << 1);
        to = (char*)&s.r.s.data[0];
    } else {
        u64 alloc = (len + extra_cap + 16) & ~u64(15);
        to = (char*)g::StringAllocate(alloc);
        s.r.l.cap = alloc | 1;
        s.r.l.size = len;
        s.r.l.data = to;
    }
    for (u64 i = 0; i < len; i++) to[i] = (char)('a' + t.rand_int(0, 25));
    to[len] = 0;
}
u64 rand_len(TestContext& t) {
    static const u64 kLens[] = {0, 1, 5, 21, 22, 23, 24, 40, 100, 300};
    return kLens[t.rand_int(0, 9)];
}

// Maps the 8-byte words of `b` that point into [ra, ra + size) onto [rb, ...) (for the comparison).
std::string compare(const ElementInfo& I, const u8* a, const u8* b, const u8* ra, const u8* rb, bool dead) {
    for (u32 i = 0; i < I.size;) {
        const ElementProp* sp = nullptr;
        for (const ElementProp& d : I.props)
            if (d.kind == PropKind::kString && i == d.offset + offsetof(AnyStringProperty, m_value)) sp = &d;
        if (sp) {
            const auto& x = string_property(a, *sp)->m_value;
            const auto& y = string_property(b, *sp)->m_value;
            std::string why;
            if (dead && x.is_long() && y.is_long()) {
                if (x.r.l.cap != y.r.l.cap || x.r.l.size != y.r.l.size) why = "long string words";
            } else {
                why = params::diff_strings(x, y);
            }
            if (!why.empty()) return "string at +" + std::to_string(sp->offset) + ": " + why;
            i += sizeof(String);
            continue;
        }
        if (i % 8 == 0 && i + 8 <= I.size) {
            u64 x, y;
            std::memcpy(&x, a + i, 8);
            std::memcpy(&y, b + i, 8);
            if (x >= (u64)ra && x < (u64)ra + I.size) x = x - (u64)ra + (u64)rb;
            if (x != y) {
                char m[96];
                snprintf(m, sizeof m, "+%#x: guest %#llx native %#llx", i, (unsigned long long)x, (unsigned long long)y);
                return m;
            }
            i += 8;
            continue;
        }
        if (a[i] != b[i]) return "+" + std::to_string(i);
        i++;
    }
    return {};
}

void free_strings(const ElementInfo& I, u8* obj) {
    for (const ElementProp& d : I.props)
        if (d.kind == PropKind::kString) libcxx::string_destroy(&string_property(obj, d)->m_value);
}

const char* method(std::span<const ElementMethod> ms, const char* role) {
    for (const ElementMethod& m : ms)
        if (!std::strcmp(m.role, role)) return m.symbol;
    return nullptr;
}

// Random values and strings into two twins.
void fill_random(TestContext& t, const ElementInfo& I, u8* a, u8* b) {
    for (const ElementProp& d : I.props) {
        if (d.kind == PropKind::kString) {
            u64 len = rand_len(t);
            make_string(t, string_property(a, d)->m_value, len);
            params::copy_string(string_property(b, d)->m_value, string_property(a, d)->m_value);
        } else {
            u64 v = t.rand_u64();
            std::memcpy(value_bytes(a, d), &v, value_width(d.kind));
            std::memcpy(value_bytes(b, d), &v, value_width(d.kind));
        }
        property(a, d)->m_named = (bool)t.rand_int(0, 1);
        property(b, d)->m_named = property(a, d)->m_named;
        property(a, d)->m_name.m_hash = property(b, d)->m_name.m_hash = (u32)t.rand_u64();
    }
}

template <class E>
void ctor_init(TestContext& t) {
    const ElementInfo& I = element_info<E>();
    auto ms = ElementTraits<E>::methods;
    Elem a(I.size, 0xa5), b(I.size, 0xa5);
    if (const char* c = method(ms, "Ctor")) {
        guest_call(t.sym(c), {(u64)a.p()});
    } else {
        ElementCode::Ctor(I, a.p());
    }
    ElementCode::Ctor(I, b.p());
    std::string why = compare(I, a.p(), b.p(), a.p(), b.p(), false);
    if (!why.empty()) t.fail("%s ctor: %s", I.cls, why.c_str());
    guest_call(t.sym(method(ms, "Initialize")), {(u64)a.p()});
    reinterpret_cast<TElement<E>*>(b.p())->Initialize();
    why = compare(I, a.p(), b.p(), a.p(), b.p(), false);
    if (!why.empty()) t.fail("%s Initialize: %s", I.cls, why.c_str());
    // a second Initialize on the linked element (AddProperty finds them in the list)
    guest_call(t.sym(method(ms, "Initialize")), {(u64)a.p()});
    reinterpret_cast<TElement<E>*>(b.p())->Initialize();
    why = compare(I, a.p(), b.p(), a.p(), b.p(), false);
    if (!why.empty()) t.fail("%s Initialize again: %s", I.cls, why.c_str());
}

template <class E>
void copy_assign_dtor(TestContext& t) {
    const ElementInfo& I = element_info<E>();
    auto ms = ElementTraits<E>::methods;
    const char* copy = method(ms, "CtorCopy");
    const char* assign = method(ms, "Assign");
    for (int round = 0; round < 3; round++) {
        Elem sa(I.size, 0), sb(I.size, 0);
        ElementCode::Ctor(I, sa.p());
        ElementCode::Ctor(I, sb.p());
        ElementCode::Initialize(I, sa.p());
        ElementCode::Initialize(I, sb.p());
        fill_random(t, I, sa.p(), sb.p());
        if (copy) {
            Elem a(I.size, 0x5a), b(I.size, 0x5a);
            guest_call(t.sym(copy), {(u64)a.p(), (u64)sa.p()});
            reinterpret_cast<TElement<E>*>(b.p())->CtorCopy(reinterpret_cast<TElement<E>*>(sb.p()));
            std::string why = compare(I, a.p(), b.p(), sa.p(), sb.p(), false);
            if (!why.empty()) t.fail("%s copy constructor: %s", I.cls, why.c_str());
            free_strings(I, a.p());
            free_strings(I, b.p());
        }
        if (assign) {
            Elem a(I.size, 0), b(I.size, 0);
            ElementCode::Ctor(I, a.p());
            ElementCode::Ctor(I, b.p());
            for (const ElementProp& d : I.props)  // destinations of every kind and capacity
                if (d.kind == PropKind::kString) {
                    u64 len = rand_len(t), extra = t.rand_int(0, 2) ? 0 : (u64)t.rand_int(0, 200);
                    make_string(t, string_property(a.p(), d)->m_value, len, extra);
                    params::copy_string(string_property(b.p(), d)->m_value, string_property(a.p(), d)->m_value);
                }
            u64 ra = guest_call(t.sym(assign), {(u64)a.p(), (u64)sa.p()});
            auto* rb = reinterpret_cast<TElement<E>*>(b.p())->Assign(reinterpret_cast<TElement<E>*>(sb.p()));
            if (ra != (u64)a.p() || (u8*)rb != b.p()) t.fail("%s operator=: result", I.cls);
            std::string why = compare(I, a.p(), b.p(), sa.p(), sb.p(), false);
            if (!why.empty()) t.fail("%s operator=: %s", I.cls, why.c_str());
            guest_call(t.sym(assign), {(u64)a.p(), (u64)a.p()});
            reinterpret_cast<TElement<E>*>(b.p())->Assign(reinterpret_cast<TElement<E>*>(b.p()));
            why = compare(I, a.p(), b.p(), sa.p(), sb.p(), false);  // (the lists still run through the sources)
            if (!why.empty()) t.fail("%s operator= itself: %s", I.cls, why.c_str());
            guest_call(t.sym(method(ms, "Dtor")), {(u64)a.p()});
            reinterpret_cast<TElement<E>*>(b.p())->Dtor();
            why = compare(I, a.p(), b.p(), sa.p(), sb.p(), true);
            if (!why.empty()) t.fail("%s destructor (assigned): %s", I.cls, why.c_str());
        }
        guest_call(t.sym(method(ms, "Dtor")), {(u64)sa.p()});
        reinterpret_cast<TElement<E>*>(sb.p())->Dtor();
        std::string why = compare(I, sa.p(), sb.p(), sa.p(), sb.p(), true);
        if (!why.empty()) t.fail("%s destructor: %s", I.cls, why.c_str());
    }
    // the deleting destructor on an operator new block (it frees the block: nothing left to compare)
    if (const char* d0 = method(ms, "DtorDelete")) {
        (void)d0;
        u8* p = (u8*)guest_call(t.sym("_Znwm"), {(u64)I.size});
        ElementCode::Ctor(I, p);
        ElementCode::Initialize(I, p);
        for (const ElementProp& d : I.props)
            if (d.kind == PropKind::kString) make_string(t, string_property(p, d)->m_value, 40);
        reinterpret_cast<TElement<E>*>(p)->DtorDelete();
    }
}

}  // namespace

NATIVE_TEST("master/elements-ctor-init") {
#define MASTER_T(C, ZTV) ctor_init<C>(t);
    MASTER_ELEMENTS(MASTER_T)
#undef MASTER_T
}

NATIVE_TEST("master/elements-copy-assign-dtor") {
#define MASTER_T(C, ZTV) copy_assign_dtor<C>(t);
    MASTER_ELEMENTS(MASTER_T)
#undef MASTER_T
}

}  // namespace soa::native::master
