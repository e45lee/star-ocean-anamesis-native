// The tables' natives: every CMasterParameterBaseSqlite_Simple<E> method and DeserializeMsgPack<E> the
// generator lists for an element (gen/master_elements.h kETable) bound to TSimple<E>'s member.
#include <cstring>
#include <string>

#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/master/master_simple.h"

namespace soa::native::master {

namespace {

// The two members returning a shared_ptr through x8.
template <class E>
void h_from_hash(Cpu& c) {
    reinterpret_cast<const TSimple<E>*>(c.x(0))->pParameterFromHash(reinterpret_cast<SharedPtr*>(c.x(8)), (u32)c.x(1));
}
template <class E>
void h_by_query(Cpu& c) {
    reinterpret_cast<const TSimple<E>*>(c.x(0))->ParameterByQuery(reinterpret_cast<SharedPtr*>(c.x(8)),
                                                                  reinterpret_cast<const char*>(c.x(1)),
                                                                  reinterpret_cast<void*>(c.x(2)), (u32)c.x(3));
}

template <class E>
HostFn host_of(const char* role) {
    using T = TSimple<E>;
    std::string r = role;
    if (r == "pParameterFromHash") return &h_from_hash<E>;
    if (r == "ParameterByQuery") return &h_by_query<E>;
    if (r == "ParameterByQueryMap") return wrap_method<&T::ParameterByQueryMap>();
    if (r == "MakeCacheKey") return wrap_method<&T::MakeCacheKey>();
    if (r == "InsertCustomizeCache") return wrap_method<&T::InsertCustomizeCache>();
    if (r == "ClearCache") return wrap_method<&T::ClearCache>();
    if (r == "SetStoreAllCacheSize") return wrap_method<&T::SetStoreAllCacheSize>();
    if (r == "Initialize") return wrap_method<&T::Initialize>();
    if (r == "Dtor") return wrap_method<&T::Dtor>();
    if (r == "Deserialize") return wrap_method<&T::Deserialize>();
    if (r == "ReleaseParameter") return wrap_method<&T::ReleaseParameter>();
    if (r == "DeserializeParameter") return wrap_method<&T::DeserializeParameter>();
    if (r == "DeserializeMsgPack") return wrap_method<&T::DeserializeMsgPack>();
    return nullptr;
}

template <class E>
bool bind() {
    for (const ElementMethod& m : ElementTraits<E>::table) {
        if (!m.role) continue;
        HostFn h = host_of<E>(m.role);
        if (!h) continue;
        static const std::string note = std::string("master: CMasterParameterBaseSqlite_Simple<") + ElementTraits<E>::name + "> (generic table)";
        Fn* f = new Fn(fam(), m.symbol);  // (lives as long as the process: the registry keeps &f->orig)
        SimpleRole r = simple_role(m.role);
        if (r != SimpleRole::kCount && !SimpleFns<E>::fn[(int)r]) SimpleFns<E>::fn[(int)r] = f;
        register_native_function({m.symbol, h, note.c_str(), nullptr, &f->orig, nullptr, "TSimple<E>"});
    }
    return true;
}

#define MASTER_BIND(C, ZTV) [[maybe_unused]] const bool NATIVE_CONCAT(master_simple_bind_, C) = bind<C>();
MASTER_ELEMENTS(MASTER_BIND)
#undef MASTER_BIND

}  // namespace

}  // namespace soa::native::master
