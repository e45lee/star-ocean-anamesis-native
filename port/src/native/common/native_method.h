#pragma once
// Natives as members of the recovered classes (port/PLAN.md task 6: classes with their methods
// attached, not structs + free functions).
//
//   class CFoo { public: u32 GetId() const; void SetPos(float x, float y); ... };  // <s>_layout.h
//   u32 CFoo::GetId() const { return m_id; }
//   NATIVE_METHOD("_ZNK4CFoo5GetIdEv", &CFoo::GetId, "CFoo::GetId");
//
// wrap_method<&C::M>() is the HostFn for a guest member function: `this` from x0, the arguments
// after it by AAPCS64 (abi.h's ArgReader: integers / pointers in x1-x7, floats in v0-v7, then the
// stack), the result to x0 / v0. The object is the guest's own (identity-mapped memory), so the
// class must have the guest's layout: standard-layout, no C++ virtual (the guest's vtable pointer
// is a field). Static members and free functions keep NATIVE_FUNCTION(sym, wrap<&C::F>(), note).
// A member returning a struct through x8 or taking one by value isn't covered: write that HostFn
// by hand.
#include <tuple>
#include <type_traits>

#include "soaruntime/core/abi.h"
#include "native/common/native.h"

namespace soa {

template <typename>
struct MethodTraits;
template <typename R, typename C, typename... A>
struct MethodTraits<R (C::*)(A...)> {
    using Ret = R;
    using Class = C;
    using Args = std::tuple<A...>;
};
template <typename R, typename C, typename... A>
struct MethodTraits<R (C::*)(A...) const> {
    using Ret = R;
    using Class = const C;
    using Args = std::tuple<A...>;
};

template <auto M>
void wrapped_method(Cpu& c) {
    using Tr = MethodTraits<decltype(M)>;
    auto* self = reinterpret_cast<typename Tr::Class*>(c.x(0));
    ArgReader rd(c, 1, 0);
    auto args = std::apply([&](auto... dummy) { return std::tuple<decltype(dummy)...>{rd.next<decltype(dummy)>()...}; }, typename Tr::Args{});
    auto call = [&](auto... a) { return (self->*M)(a...); };
    if constexpr (std::is_void_v<typename Tr::Ret>) {
        std::apply(call, args);
    } else {
        set_result(c, std::apply(call, args));
    }
}

template <auto M>
constexpr HostFn wrap_method() { return &wrapped_method<M>; }

}  // namespace soa

// A guest member function replaced by a member of the recovered class.
#define NATIVE_METHOD(sym, method, note) NATIVE_REGISTER(sym, ::soa::wrap_method<method>(), note, nullptr, nullptr, nullptr, #method)
#define NATIVE_METHOD_IF(sym, method, note, cond) NATIVE_REGISTER(sym, ::soa::wrap_method<method>(), note, cond, nullptr, nullptr, #method)
// A member of the in-process route's own classes (group kGroupRoute, as NATIVE_ROUTE_FUNCTION).
#define NATIVE_ROUTE_METHOD(sym, method, note) \
    NATIVE_REGISTER(sym, ::soa::wrap_method<method>(), note, nullptr, nullptr, ::soa::kGroupRoute, #method)
