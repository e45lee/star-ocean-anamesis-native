// Differential tests of the info class natives (info_class.cpp) against the guest's code, for every
// generated class: the exported default constructors (the same buffer, built by each), Initialize (two
// objects built the same way, one initialized by the guest, one by the native: the state must agree).
#include <cstring>
#include <vector>

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

// An object worth copying: built, initialized (the guest's, when the class has one), every value random,
// every string random text (short or long: from the guest's allocator), the children the same way.
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
    for (const InfoChild& ch : K.children)
        if (ch.cls->kind == InfoKind::kInfo) fill(t, *ch.cls, obj + ch.offset);
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

// Every Initialize: two objects built by the native constructor (values 0xcc), the guest's Initialize on
// one, the native's on the other; the state (each property's bytes, a string's text, both maps by key
// and the value's offset, the children's: their Initialize runs (the guest's) from both) must agree.
NATIVE_TEST("info/initialize") {
    int bad = 0;
    for (const Case& c : kInits) {
        const InfoClass& K = *c.cls;
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
