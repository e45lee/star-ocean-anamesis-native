// The element natives' registration: every exported method of every generated element class
// (gen/master_elements.h kEMethods) bound to TElement<E>'s member, each with its live-check slot.
#include <cstring>

#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/master/master_element.h"

namespace soa::native::master {

namespace {

template <class E>
HostFn host_of(ElementRole r) {
    using T = TElement<E>;
    switch (r) {
        case ElementRole::Initialize: return wrap_method<&T::Initialize>();
        case ElementRole::Ctor: return wrap_method<&T::Ctor>();
        case ElementRole::CtorCopy: return wrap_method<&T::CtorCopy>();
        case ElementRole::Assign: return wrap_method<&T::Assign>();
        case ElementRole::Dtor: return wrap_method<&T::Dtor>();
        case ElementRole::DtorDelete: return wrap_method<&T::DtorDelete>();
        case ElementRole::kCount: break;
    }
    return nullptr;
}

ElementRole role_of(const char* s) {
    static const char* const kNames[] = {"Initialize", "Ctor", "CtorCopy", "Assign", "Dtor", "DtorDelete"};
    for (int i = 0; i < (int)ElementRole::kCount; i++)
        if (!std::strcmp(s, kNames[i])) return (ElementRole)i;
    return ElementRole::kCount;
}

template <class E>
bool bind() {
    for (const ElementMethod& m : ElementTraits<E>::methods) {
        ElementRole r = role_of(m.role);
        if (r == ElementRole::kCount) continue;
        Fn* f = new Fn(fam(), m.symbol);  // (lives as long as the process: the registry keeps &f->orig)
        if (!ElementFns<E>::fn[(int)r]) ElementFns<E>::fn[(int)r] = f;
        static const std::string note = std::string("master: ") + ElementTraits<E>::name + " (generic element)";
        register_native_function({m.symbol, host_of<E>(r), note.c_str(), nullptr, &f->orig, nullptr, "TElement<E>"});
    }
    return true;
}

#define MASTER_BIND(C, ZTV) [[maybe_unused]] const bool NATIVE_CONCAT(master_bind_, C) = bind<C>();
MASTER_ELEMENTS(MASTER_BIND)
#undef MASTER_BIND

}  // namespace

}  // namespace soa::native::master
