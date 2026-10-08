// The info class natives' registration: every info class's exported Initialize and default constructor
// (gen/info_classes.h INFO_INITIALIZERS / INFO_CONSTRUCTORS) bound to TInfo<C>'s member, each with its
// live-check slot. The live check (family `info`, run-both on the object itself): Initialize runs the
// native, then the original on the same object (a second Initialize names and defaults the same and
// inserts nothing new: every key is in the maps already) and the state (info_state: properties, both
// maps relative to the object, the children's) must be what the native left; the constructor the same
// way, on the object's bytes.
#include <cstring>
#include <string>

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
        std::vector<u8> n = info_state(K, obj);
        guest_call(f->orig, {reinterpret_cast<u64>(obj)});
        std::vector<u8> g = info_state(K, obj);
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

template <class C>
bool bind(InfoRole r, const char* sym) {
    Fn* f = new Fn(fam(), sym);  // (lives as long as the process: the registry keeps &f->orig)
    InfoFns<C>::fn[(int)r] = f;
    static const std::string note = std::string("info: ") + InfoTraits<C>::cls.name + " (generic info)";
    HostFn h = r == InfoRole::Initialize ? wrap_method<&TInfo<C>::Initialize>() : wrap_method<&TInfo<C>::Ctor>();
    register_native_function({sym, h, note.c_str(), nullptr, &f->orig, nullptr, "TInfo<C>"});
    return true;
}

#define INFO_BIND_INIT(C, SYM) [[maybe_unused]] const bool NATIVE_CONCAT(info_init_, C) = bind<C>(InfoRole::Initialize, SYM);
INFO_INITIALIZERS(INFO_BIND_INIT)
#undef INFO_BIND_INIT
#define INFO_BIND_CTOR(C, SYM) [[maybe_unused]] const bool NATIVE_CONCAT(info_ctor_, C) = bind<C>(InfoRole::Ctor, SYM);
INFO_CONSTRUCTORS(INFO_BIND_CTOR)
#undef INFO_BIND_CTOR

}  // namespace

}  // namespace soa::native::info
