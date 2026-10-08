// Differential tests of the info class natives (info_class.cpp) against the guest's code, for every
// generated class: the exported default constructors (the same buffer, built by each), Initialize (two
// objects built the same way, one initialized by the guest, one by the native: the state must agree).
#include <cstring>
#include <vector>

#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "native/info/info_class.h"
#include "native/libcxx/libcxx_string.h"

namespace soa::native::info {

namespace {

struct Case {
    const InfoClass* cls;
    const char* sym;
};

#define INFO_CASE(C, SYM) {&kInfo_##C, SYM},
constexpr Case kInits[] = {INFO_INITIALIZERS(INFO_CASE)};
constexpr Case kCtors[] = {INFO_CONSTRUCTORS(INFO_CASE)};
#undef INFO_CASE

struct CopyCase {
    const InfoClass* cls;
    InfoRole role;
    const char* sym;
};
#define INFO_COPY_CASE(C, ROLE, SYM) {&kInfo_##C, InfoRole::ROLE, SYM},
constexpr CopyCase kCopies[] = {INFO_COPIES(INFO_COPY_CASE)};
#undef INFO_COPY_CASE

const char* initialize_of(const InfoClass* K) {
    for (const Case& c : kInits)
        if (c.cls == K) return c.sym;
    return nullptr;
}

void fill(TestContext& t, const InfoClass& K, u8* obj);

// A container's body with 0..3 random elements: a vector's in storage of its own (Allocate), a map's
// inserted by the guest's __emplace_hint_unique_key_args (keys 1, 2, 3: copies of a host object).
void fill_container(TestContext& t, const InfoClass& K, u8* obj) {
    auto* c = reinterpret_cast<InfoContainer*>(obj);
    int n = t.rand_int(0, 3);
    if (K.kind == InfoKind::kMap) {
        if (!K.elem || !K.fn_copy) return;
        auto& tree = *reinterpret_cast<libcxx::tree<u8>*>(&c->m_body);
        for (int i = 0; i < n; i++) {
            std::vector<u8> pair(8 + K.elem->size, 0xcc);
            u64 key = i + 1;
            std::memcpy(pair.data(), &key, K.key_size);
            InfoCode::Ctor(*K.elem, pair.data() + 8);
            fill(t, *K.elem, pair.data() + 8);
            t.call(K.fn_copy, {reinterpret_cast<u64>(&tree), reinterpret_cast<u64>(tree.end_node()), reinterpret_cast<u64>(pair.data()),
                               reinterpret_cast<u64>(pair.data())});
            InfoCode::Dtor(*K.elem, pair.data() + 8);
        }
        return;
    }
    if (K.kind == InfoKind::kArray && !K.elem) return;
    u64 stride = K.kind == InfoKind::kValueArray ? 0x30 : K.elem->size;
    if (!n) return;
    u64 p = reinterpret_cast<u64>(guest::stl_alloc(n * stride));
    c->m_body[0] = c->m_body[1] = p;
    c->m_body[2] = p + n * stride;
    for (int i = 0; i < n; i++, c->m_body[1] += stride) {
        auto* e = reinterpret_cast<u8*>(c->m_body[1]);
        if (K.kind == InfoKind::kValueArray) {
            // a CParameterPropertyValue<T, N>: the copy of a value property of a built info (any will do: the
            // copies copy the vtable from the descriptor); here a value property by hand
            std::memset(e, 0, stride);
            char sym[160];
            const char* tc = "jifbhm" + (int)K.elem_prop.kind;
            snprintf(sym, sizeof sym, "_ZTV23CParameterPropertyValueI%cLj%uE18CPropertyConverterE", *tc, K.elem_prop.n);
            *reinterpret_cast<u64*>(e) = t.sym(sym) + 16;
            *reinterpret_cast<u64*>(e + 0x18) = t.sym("_ZTVN9Framework7CHash32E") + 16;
            for (u32 b = 0; b < value_width(K.elem_prop.kind); b++) e[0x28 + b] = (u8)t.rand_u64();
        } else {
            InfoCode::Ctor(*K.elem, e);
            fill(t, *K.elem, e);
        }
    }
}

// An object worth copying: built, initialized (the guest's, when the class has one), every value random,
// every string random text (short or long: from the guest's allocator), the children the same way, the
// containers with a few elements.
void fill(TestContext& t, const InfoClass& K, u8* obj) {
    for (const InfoProp& d : K.props) {
        u8* v = obj + d.offset + 0x28;
        if (d.kind != InfoPropKind::kString) {
            for (u32 i = 0; i < value_width(d.kind); i++) v[i] = (u8)t.rand_u64();
            if (d.kind == InfoPropKind::kBool) v[0] &= 1;
            continue;
        }
        std::string text(t.rand_int(0, 40), 'a');
        for (char& c : text) c = (char)('a' + t.rand_int(0, 25));
        params::String tmp;  // a long representation over host storage: the copy takes the guest's
        tmp.r.l.cap = ((text.size() + 16) & ~u64(15)) | 1;
        tmp.r.l.size = text.size();
        tmp.r.l.data = text.data();
        auto* s = reinterpret_cast<params::String*>(v);
        libcxx::string_destroy(s);
        libcxx::string_copy_construct(s, tmp);
    }
    for (const InfoChild& ch : K.children) {
        if (ch.cls->kind == InfoKind::kInfo) fill(t, *ch.cls, obj + ch.offset);
        else fill_container(t, *ch.cls, obj + ch.offset);
    }
    for (u32 i = 0; i < K.tail; i++) obj[K.size - K.tail + i] = (u8)t.rand_u64();
}

struct Obj {
    const InfoClass& K;
    std::vector<u8> b;
    explicit Obj(const InfoClass& k) : K(k), b(k.size, 0xcc) { InfoCode::Ctor(K, b.data()); }
    Obj(const InfoClass& k, const u8* from) : K(k), b(k.size, 0xcc) { InfoCode::CtorCopy(K, b.data(), from); }
    ~Obj() {
        if (live) InfoCode::Dtor(K, b.data());
    }
    u8* p() { return b.data(); }
    bool live = true;
};

}  // namespace

// Every exported default constructor: the guest's on a 0xcc-filled buffer, then the native's on the
// same buffer filled again: the bytes must agree (the values the constructor leaves alone included).
NATIVE_TEST("info/constructors") {
    int bad = 0;
    for (const Case& c : kCtors) {
        const InfoClass& K = *c.cls;
        std::vector<u8> buf(K.size + 64), guest;
        std::memset(buf.data(), 0xcc, buf.size());
        t.call(c.sym, {reinterpret_cast<u64>(buf.data())});
        guest = buf;
        std::memset(buf.data(), 0xcc, buf.size());
        InfoCode::Ctor(K, buf.data());
        if (buf != guest && bad++ < 8) t.fail("%s: %s", K.name, live::RunBothFamily::diff_bytes(buf.data(), guest.data(), buf.size()).c_str());
    }
}

// CInfoManager's Initialize (no layout: two managers built by the guest's constructor): what the steps
// leave (info_steps_state) and every child's state (the infos the generator knows, found by their offsets
// in the steps) must agree.
NATIVE_TEST("info/initialize-manager") {
    const InfoClass& K = kInfo_CInfoManager;
    constexpr size_t kSize = 0x10000;  // (the manager is 0xb120 bytes in 3.7.0)
    std::vector<u8> a(kSize, 0xcc), b(kSize, 0xcc);
    t.call("_ZN12CInfoManagerC1Ev", {reinterpret_cast<u64>(a.data())});
    t.call("_ZN12CInfoManagerC1Ev", {reinterpret_cast<u64>(b.data())});
    t.call("_ZN12CInfoManager10InitializeEv", {reinterpret_cast<u64>(a.data())});
    InfoCode::Initialize(K, b.data());
    if (info_steps_state(K, a.data()) != info_steps_state(K, b.data())) t.fail("the steps' state differs");
    int children = 0;
    for (const InfoStep& s : K.init) {
        if (s.kind != InfoStep::kChild) continue;
        u64 vt = *reinterpret_cast<const u64*>(a.data() + s.offset);
        for (const Case& c : kInits)
            if (c.cls->name && t.sym(c.cls->ztv) + 16 == vt) {
                children++;
                if (info_state(*c.cls, a.data() + s.offset) != info_state(*c.cls, b.data() + s.offset))
                    t.fail("the child at +%#x (%s) differs", s.offset, c.cls->name);
                break;
            }
    }
    if (children < 50) t.fail("only %d children compared", children);
    t.call("_ZN12CInfoManagerD1Ev", {reinterpret_cast<u64>(a.data())});
    t.call("_ZN12CInfoManagerD1Ev", {reinterpret_cast<u64>(b.data())});
}

// Every Initialize: two objects built by the native constructor (values 0xcc), the guest's Initialize on
// one, the native's on the other; the state (each property's bytes, a string's text, both maps by key
// and the value's offset, the children's: their Initialize runs (the guest's) from both) must agree.
NATIVE_TEST("info/initialize") {
    int bad = 0;
    for (const Case& c : kInits) {
        const InfoClass& K = *c.cls;
        if (&K == &kInfo_CInfoManager) continue;  // (info/initialize-manager)
        std::vector<u8> a(K.size, 0xcc), b(K.size, 0xcc);
        InfoCode::Ctor(K, a.data());
        InfoCode::Ctor(K, b.data());
        std::vector<u8> before = info_state(K, a.data());
        t.call(c.sym, {reinterpret_cast<u64>(a.data())});
        if (info_state(K, a.data()) == before && bad++ < 8) t.fail("%s: the guest's Initialize changed nothing", K.name);
        InfoCode::Initialize(K, b.data());
        if (info_state(K, a.data()) != info_state(K, b.data()) && bad++ < 8) t.fail("%s: the state differs", K.name);
        info_free_maps(K, a.data());
        info_free_maps(K, b.data());
    }
}

}  // namespace soa::native::info

namespace soa::native::info {

// Every copy constructor, move, operator=, move assignment and destructor of the infos without a container
// inside: the guest's and the native's from equal inputs (objects filled with random values and strings;
// a move's source and an assignment's target copied for each side); the results' states (the sources'
// after a move) must agree; a destructor's: every byte but the maps' and the strings'.
NATIVE_TEST("info/copies") {
    int bad = 0;
    for (const CopyCase& c : kCopies) {
        const InfoClass& K = *c.cls;
        Obj a(K), b(K);
        if (const char* init = initialize_of(&K)) t.call(init, {reinterpret_cast<u64>(a.p())});
        fill(t, K, a.p());
        fill(t, K, b.p());
        bool ok = true;
        switch (c.role) {
            case InfoRole::CtorCopy:
            case InfoRole::Move: {
                Obj s1(K, a.p()), s2(K, a.p());
                std::vector<u8> g(K.size, 0xcc), n(K.size, 0xcc);
                t.call(c.sym, {reinterpret_cast<u64>(g.data()), reinterpret_cast<u64>(s1.p())});
                if (c.role == InfoRole::Move) InfoCode::Move(K, n.data(), s2.p());
                else InfoCode::CtorCopy(K, n.data(), s2.p());
                ok = info_state(K, g.data()) == info_state(K, n.data()) && info_state(K, s1.p()) == info_state(K, s2.p());
                InfoCode::Dtor(K, g.data());
                InfoCode::Dtor(K, n.data());
                break;
            }
            case InfoRole::Assign:
            case InfoRole::MoveAssign: {
                Obj t1(K, b.p()), t2(K, b.p()), s1(K, a.p()), s2(K, a.p());
                t.call(c.sym, {reinterpret_cast<u64>(t1.p()), reinterpret_cast<u64>(s1.p())});
                if (c.role == InfoRole::MoveAssign) InfoCode::MoveAssign(K, t2.p(), s2.p());
                else InfoCode::Assign(K, t2.p(), s2.p());
                ok = info_state(K, t1.p()) == info_state(K, t2.p()) && info_state(K, s1.p()) == info_state(K, s2.p());
                break;
            }
            case InfoRole::Dtor: {
                Obj x1(K, a.p()), x2(K, a.p());
                t.call(c.sym, {reinterpret_cast<u64>(x1.p())});
                InfoCode::Dtor(K, x2.p());
                x1.live = x2.live = false;
                ok = info_dtor_state(K, x1.p()) == info_dtor_state(K, x2.p());
                break;
            }
            default: break;
        }
        if (!ok && bad++ < 8) t.fail("%s: %s differs", K.name, c.sym);
    }
}

}  // namespace soa::native::info
