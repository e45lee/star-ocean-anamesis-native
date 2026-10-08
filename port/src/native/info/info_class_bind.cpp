// The info class natives' registration: every info class's exported Initialize and default constructor
// (gen/info_classes.h INFO_INITIALIZERS / INFO_CONSTRUCTORS) bound to TInfo<C>'s member, each with its
// live-check slot. The live check (family `info`, run-both on the object itself): Initialize runs the
// native, then the original on the same object (a second Initialize names and defaults the same and
// inserts nothing new: every key is in the maps already) and the state (info_state: properties, both
// maps relative to the object, the children's) must be what the native left; the constructor the same
// way, on the object's bytes. The copies, moves and assignments: the native on the object, the original
// on a temporary (a copy of the target or the source as they were, by the native copy constructor), the
// states compared (the source's too after a move), the temporaries destroyed; the destructor: the
// original on a copy, every word but the maps' and the strings' compared.
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/info/info_class.h"

namespace soa::native::info {

#define INFO_TRAITS(C)                                               \
    template <>                                                      \
    struct InfoTraits<C> {                                           \
        static constexpr const InfoClass& cls = kInfo_##C;           \
    };
INFO_CLASSES(INFO_TRAITS)
#undef INFO_TRAITS

namespace {

template <class C>
struct InfoFns {
    static inline Fn* fn[(int)InfoRole::kCount] = {};
};

template <class C>
u8* bytes_of(TInfo<C>* t) {
    return reinterpret_cast<u8*>(t);
}

}  // namespace

template <class C>
void TInfo<C>::Initialize() {
    const InfoClass& K = InfoTraits<C>::cls;
    u8* obj = bytes_of(this);
    Fn* f = InfoFns<C>::fn[(int)InfoRole::Initialize];
    if (f && fam().due(*f)) {
        live::RunBothFamily::Scope scope;
        InfoCode::Initialize(K, obj);
        std::vector<u8> n = info_state(K, obj), ns = info_steps_state(K, obj);
        guest_call(f->orig, {reinterpret_cast<u64>(obj)});
        std::vector<u8> g = info_state(K, obj), gs = info_steps_state(K, obj);
        n.insert(n.end(), ns.begin(), ns.end());
        g.insert(g.end(), gs.begin(), gs.end());
        bool ok = n == g;
        fam().result(*f, ok ? Outcome::Ok : Outcome::Mismatch,
                     ok ? "" : std::string(K.name) + ": the state differs after the original's run (" + std::to_string(n.size()) + " / " +
                                   std::to_string(g.size()) + " bytes)");
        return;
    }
    InfoCode::Initialize(K, obj);
}

template <class C>
void TInfo<C>::Ctor() {
    const InfoClass& K = InfoTraits<C>::cls;
    u8* obj = bytes_of(this);
    Fn* f = InfoFns<C>::fn[(int)InfoRole::Ctor];
    if (f && fam().due(*f)) {
        live::RunBothFamily::Scope scope;
        InfoCode::Ctor(K, obj);
        std::vector<u8> n(obj, obj + K.size);
        guest_call(f->orig, {reinterpret_cast<u64>(obj)});
        bool ok = std::memcmp(n.data(), obj, K.size) == 0;
        fam().result(*f, ok ? Outcome::Ok : Outcome::Mismatch,
                     ok ? "" : std::string(K.name) + ": " + live::RunBothFamily::diff_bytes(n.data(), obj, K.size));
        return;
    }
    InfoCode::Ctor(K, obj);
}

namespace {

// A copy of an object of class K for the original to work on: its bytes (the padding included), then the
// native copy constructor (its own maps and strings), then its own vtable back (the object may be of a
// class derived from K: a derived class's operator= and destructor call K's). Destroyed by the native
// destructor unless the original destroyed it.
void clone(const InfoClass& K, u8* to, const u8* from) {
    std::memcpy(to, from, K.size);
    InfoCode::CtorCopy(K, to, from);
    std::memcpy(to, from, 8);
}
struct Temp {
    const InfoClass& K;
    std::vector<u8> b;
    Temp(const InfoClass& k, const u8* from) : K(k), b(k.size) { clone(K, b.data(), from); }
    ~Temp() { InfoCode::Dtor(K, b.data()); }
    u8* p() { return b.data(); }
};

// Where two objects' states first differ: the innermost child (path of offsets) whose own state differs.
std::string where_differs(const InfoClass& K, const u8* a, const u8* b) {
    if (K.kind == InfoKind::kInfo)
        for (const InfoChild& ch : K.children)
            if (info_state_raw(*ch.cls, a + ch.offset) != info_state_raw(*ch.cls, b + ch.offset)) {
                char m[48];
                snprintf(m, sizeof m, "+%#x %s/", ch.offset, ch.cls->name);
                return m + where_differs(*ch.cls, a + ch.offset, b + ch.offset);
            }
    std::vector<u8> x = info_state_raw(K, a), y = info_state_raw(K, b);
    size_t i = 0;
    while (i < x.size() && i < y.size() && x[i] == y[i]) i++;
    char m[96];
    snprintf(m, sizeof m, "state byte %llu of %llu / %llu", (unsigned long long)i, (unsigned long long)x.size(), (unsigned long long)y.size());
    return m;
}

// "" when the states agree, else what differs and where.
std::string state_diff(const InfoClass& K, const u8* n, const u8* g, const char* what, bool maps = true) {
    std::vector<u8> a = maps ? info_state_raw(K, n) : info_state_no_maps(K, n), b = maps ? info_state_raw(K, g) : info_state_no_maps(K, g);
    if (a == b) return "";
    size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) i++;
    char m[160];
    snprintf(m, sizeof m, "%s differs at state byte %llu of %llu / %llu (vtable %#llx)", what, (unsigned long long)i,
             (unsigned long long)a.size(), (unsigned long long)b.size(),
             (unsigned long long)*reinterpret_cast<const u64*>(n));
    return m;
}

void report(Fn& f, const InfoClass& K, bool ok, const char* what) {
    fam().result(f, ok ? Outcome::Ok : Outcome::Mismatch, ok ? "" : std::string(K.name) + ": " + what);
}

}  // namespace

template <class C>
void TInfo<C>::CtorCopy(const TInfo* o) {
    const InfoClass& K = InfoTraits<C>::cls;
    Fn* f = InfoFns<C>::fn[(int)InfoRole::CtorCopy];
    InfoCode::CtorCopy(K, bytes_of(this), reinterpret_cast<const u8*>(o));
    if (f && fam().due(*f)) {
        live::RunBothFamily::Scope scope;
        std::vector<u8> g(K.size);
        guest_call(f->orig, {reinterpret_cast<u64>(g.data()), reinterpret_cast<u64>(o)});
        bool ok = info_state_raw(K, bytes_of(this)) == info_state_raw(K, g.data());
        std::string why = ok ? "" : "the copy differs at " + where_differs(K, bytes_of(this), g.data());
        InfoCode::Dtor(K, g.data());
        report(*f, K, ok, why.c_str());
    }
}

template <class C>
void TInfo<C>::Move(TInfo* o) {
    const InfoClass& K = InfoTraits<C>::cls;
    Fn* f = InfoFns<C>::fn[(int)InfoRole::Move];
    auto* src = reinterpret_cast<u8*>(o);
    if (f && fam().due(*f)) {
        live::RunBothFamily::Scope scope;
        Temp src2(K, src);  // (the source as it was, for the original)
        InfoCode::Move(K, bytes_of(this), src);
        std::vector<u8> g(K.size);
        guest_call(f->orig, {reinterpret_cast<u64>(g.data()), reinterpret_cast<u64>(src2.p())});
        bool ok = info_state_raw(K, bytes_of(this)) == info_state_raw(K, g.data()) && info_state_no_maps(K, src) == info_state_no_maps(K, src2.p());
        InfoCode::Dtor(K, g.data());
        report(*f, K, ok, "the moved object or the source differs");
        return;
    }
    InfoCode::Move(K, bytes_of(this), src);
}

template <class C>
TInfo<C>* TInfo<C>::Assign(const TInfo* o) {
    const InfoClass& K = InfoTraits<C>::cls;
    Fn* f = InfoFns<C>::fn[(int)InfoRole::Assign];
    auto* src = reinterpret_cast<const u8*>(o);
    if (f && fam().due(*f) && src != bytes_of(this)) {
        live::RunBothFamily::Scope scope;
        Temp t(K, bytes_of(this));  // (the target as it was, for the original)
        InfoCode::Assign(K, bytes_of(this), src);
        guest_call(f->orig, {reinterpret_cast<u64>(t.p()), reinterpret_cast<u64>(src)});
        bool ok = info_state_raw(K, bytes_of(this)) == info_state_raw(K, t.p());
        report(*f, K, ok, ok ? "" : ("the assigned object differs at " + where_differs(K, bytes_of(this), t.p())).c_str());
        return this;
    }
    InfoCode::Assign(K, bytes_of(this), src);
    return this;
}

template <class C>
TInfo<C>* TInfo<C>::MoveAssign(TInfo* o) {
    const InfoClass& K = InfoTraits<C>::cls;
    Fn* f = InfoFns<C>::fn[(int)InfoRole::MoveAssign];
    auto* src = reinterpret_cast<u8*>(o);
    if (f && fam().due(*f) && src != bytes_of(this)) {
        live::RunBothFamily::Scope scope;
        Temp t(K, bytes_of(this)), src2(K, src);
        InfoCode::MoveAssign(K, bytes_of(this), src);
        guest_call(f->orig, {reinterpret_cast<u64>(t.p()), reinterpret_cast<u64>(src2.p())});
        std::string why = state_diff(K, bytes_of(this), t.p(), "the assigned object") + state_diff(K, src, src2.p(), " the source", false);
        report(*f, K, why.empty(), why.c_str());
        return this;
    }
    InfoCode::MoveAssign(K, bytes_of(this), src);
    return this;
}

template <class C>
void TInfo<C>::Dtor() {
    const InfoClass& K = InfoTraits<C>::cls;
    Fn* f = InfoFns<C>::fn[(int)InfoRole::Dtor];
    if (f && fam().due(*f)) {
        live::RunBothFamily::Scope scope;
        std::vector<u8> g(K.size);
        clone(K, g.data(), bytes_of(this));  // (a copy for the original to destroy)
        guest_call(f->orig, {reinterpret_cast<u64>(g.data())});
        InfoCode::Dtor(K, bytes_of(this));
        report(*f, K, info_dtor_state(K, bytes_of(this)) == info_dtor_state(K, g.data()), "the destroyed object differs");
        return;
    }
    InfoCode::Dtor(K, bytes_of(this));
}

namespace {

template <class C>
HostFn host_of(InfoRole r) {
    using T = TInfo<C>;
    switch (r) {
        case InfoRole::Initialize: return wrap_method<&T::Initialize>();
        case InfoRole::Ctor: return wrap_method<&T::Ctor>();
        case InfoRole::CtorCopy: return wrap_method<&T::CtorCopy>();
        case InfoRole::Dtor: return wrap_method<&T::Dtor>();
        case InfoRole::Assign: return wrap_method<&T::Assign>();
        case InfoRole::Move: return wrap_method<&T::Move>();
        case InfoRole::MoveAssign: return wrap_method<&T::MoveAssign>();
        case InfoRole::kCount: break;
    }
    return nullptr;
}

template <class C>
bool bind(InfoRole r, const char* sym) {
    Fn* f = new Fn(fam(), sym);  // (lives as long as the process: the registry keeps &f->orig)
    InfoFns<C>::fn[(int)r] = f;
    static const std::string note = std::string("info: ") + InfoTraits<C>::cls.name + " (generic info)";
    register_native_function({sym, host_of<C>(r), note.c_str(), nullptr, &f->orig, nullptr, "TInfo<C>"});
    return true;
}

#define INFO_BIND_INIT(C, SYM) [[maybe_unused]] const bool NATIVE_CONCAT(info_init_, C) = bind<C>(InfoRole::Initialize, SYM);
INFO_INITIALIZERS(INFO_BIND_INIT)
#undef INFO_BIND_INIT
#define INFO_BIND_CTOR(C, SYM) [[maybe_unused]] const bool NATIVE_CONCAT(info_ctor_, C) = bind<C>(InfoRole::Ctor, SYM);
INFO_CONSTRUCTORS(INFO_BIND_CTOR)
#undef INFO_BIND_CTOR
#define INFO_BIND_COPY(C, ROLE, SYM) [[maybe_unused]] const bool NATIVE_CONCAT(info_##ROLE##_, C) = bind<C>(InfoRole::ROLE, SYM);
INFO_COPIES(INFO_BIND_COPY)
#undef INFO_BIND_COPY

}  // namespace

}  // namespace soa::native::info
