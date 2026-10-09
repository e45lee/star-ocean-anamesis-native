#pragma once
// AAPCS64 argument marshalling for HLE thunks.
//
// wrap<&host_fn>() generates a HostFn that pulls arguments from guest registers/stack
// according to host_fn's C signature and stores the result back. Only valid when the
// argument and result types have the same representation on bionic/arm64 and on the host.
#include <cstring>
#include <tuple>
#include <type_traits>

#include "soaruntime/core/cpu.h"

namespace soa {

// Sequential argument reader following AAPCS64 rules for non-variadic (and Linux variadic)
// calls: integers/pointers in x0-x7, floats in v0-v7, then 8-byte stack slots.
class ArgReader {
public:
    explicit ArgReader(Cpu& c, int first_int = 0, int first_fp = 0) : c_(c), ni_(first_int), nf_(first_fp), stack_(c.sp()) {}

    u64 next_int() {
        if (ni_ < 8) return c_.x(ni_++);
        return stack_next();
    }
    double next_double() {
        if (nf_ < 8) return c_.d(nf_++);
        u64 b = stack_next();
        double d;
        std::memcpy(&d, &b, 8);
        return d;
    }
    float next_float() {
        if (nf_ < 8) return c_.s(nf_++);
        u64 b = stack_next();
        float f;
        u32 lo = (u32)b;
        std::memcpy(&f, &lo, 4);
        return f;
    }
    V128 next_v128() {
        if (nf_ < 8) return c_.v(nf_++);
        stack_ = (stack_ + 15) & ~15ull;
        V128 r{((u64*)stack_)[0], ((u64*)stack_)[1]};
        stack_ += 16;
        return r;
    }
    template <typename T>
    T next() {
        if constexpr (std::is_same_v<T, float>) return next_float();
        else if constexpr (std::is_same_v<T, double>) return next_double();
        else if constexpr (std::is_pointer_v<T>) return reinterpret_cast<T>(next_int());
        else if constexpr (std::is_same_v<T, bool>) return (next_int() & 0xff) != 0;
        else return static_cast<T>(next_int());
    }

private:
    u64 stack_next() {
        u64 v = *(u64*)stack_;
        stack_ += 8;
        return v;
    }
    Cpu& c_;
    int ni_, nf_;
    u64 stack_;
};

template <typename T>
inline void set_result(Cpu& c, T v) {
    if constexpr (std::is_same_v<T, float>) c.set_s(0, v);
    else if constexpr (std::is_same_v<T, double>) c.set_d(0, v);
    else if constexpr (std::is_pointer_v<T>) c.set_x(0, (u64)(uintptr_t)v);
    else if constexpr (std::is_signed_v<T>) c.set_x(0, (u64)(s64)v);
    else c.set_x(0, (u64)v);
}

void missing_slot_call(Cpu& c);

template <typename>
struct FnTraits;
template <typename R, typename... A>
struct FnTraits<R (*)(A...)> {
    using Ret = R;
    using Args = std::tuple<A...>;
};
template <typename R, typename... A>
struct FnTraits<R (*)(A...) noexcept> {
    using Ret = R;
    using Args = std::tuple<A...>;
};

template <auto F>
void wrapped(Cpu& c) {
    using Tr = FnTraits<decltype(F)>;
    ArgReader rd(c);
    // Braced init guarantees left-to-right evaluation of the reads.
    auto args = std::apply([&](auto... dummy) { return std::tuple<decltype(dummy)...>{rd.next<decltype(dummy)>()...}; }, typename Tr::Args{});
    if constexpr (std::is_void_v<typename Tr::Ret>) {
        std::apply(F, args);
    } else {
        set_result(c, std::apply(F, args));
    }
}

template <auto F>
constexpr HostFn wrap() { return &wrapped<F>; }

// Like wrap(), but calls through a function-pointer variable resolved at runtime.
template <auto* Slot>
void wrapped_slot(Cpu& c) {
    using Tr = FnTraits<std::remove_pointer_t<decltype(Slot)>>;
    auto fn = *Slot;
    if (!fn) {
        missing_slot_call(c);
        return;
    }
    ArgReader rd(c);
    auto args = std::apply([&](auto... dummy) { return std::tuple<decltype(dummy)...>{rd.next<decltype(dummy)>()...}; }, typename Tr::Args{});
    if constexpr (std::is_void_v<typename Tr::Ret>) {
        std::apply(fn, args);
    } else {
        set_result(c, std::apply(fn, args));
    }
}
void missing_slot_call(Cpu& c);

// Helpers for hand-written thunks.
template <typename T = u64>
inline T arg(Cpu& c, int i) {
    return (T)(c.x(i));
}
inline const char* arg_str(Cpu& c, int i) { return (const char*)c.x(i); }
inline void ret(Cpu& c, u64 v) { c.set_x(0, v); }
inline void ret_ptr(Cpu& c, const void* p) { c.set_x(0, (u64)(uintptr_t)p); }

}  // namespace soa
