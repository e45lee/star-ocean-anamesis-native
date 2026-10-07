#pragma once
// Live-checked natives for leaf functions (pure computations over the object at x0 and pointer
// arguments: hashes, vector / matrix math). A LeafFamily is a live::Family (live_check.h) whose
// natives are registered with the memory each one reads or writes besides `this`, so the
// --live-check run compares those bytes too (heap out-parameters aren't snapshotted otherwise;
// stack ones are, kBuf bytes each).
//
//   live::LeafFamily& fam();   // a function-local static: natives in several files share it
//   LEAF_METHOD(fam(), "_ZNK4Aska6Matrix9CalcEulerEPNS_6VectorE14EnumRotateType", &Matrix::CalcEuler,
//               sizeof(Matrix), live::kVoid, "Aska::Matrix::CalcEuler", {live::out(1, sizeof(Vector))});
//   LEAF_FUNCTION(fam(), sym, &Hash::CRC32, live::kInt, "Aska::Hash::CRC", {live::out(2, 4)});
//
// The member / function is wrapped by AAPCS64 like NATIVE_METHOD / wrap<>, and reference
// parameters (`const CVector&`) are taken as the pointer the guest passes. A member returning a
// struct through x8 isn't covered (write that HostFn by hand and use LEAF_HOSTFN).
#include <initializer_list>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "core/abi.h"
#include "native/common/live_check.h"
#include "native/common/native.h"

namespace soa::live {

// One region a native touches besides the object at x0: `bytes` at the pointer in x<reg>, or,
// when `len_reg` >= 0, x<len_reg> * `scale` + `extra` bytes (at most `cap`); a null pointer adds
// nothing.
struct Arg {
    int reg = 0;
    u32 bytes = 0;
    int len_reg = -1;
    u32 scale = 1, extra = 0, cap = 0x10000;
};
inline Arg out(int reg, u32 bytes) { return Arg{reg, bytes}; }
inline Arg out_len(int reg, int len_reg, u32 scale = 1, u32 extra = 0, u32 cap = 0x10000) {
    return Arg{reg, 0, len_reg, scale, extra, cap};
}

class LeafFamily : public Family {
public:
    LeafFamily(const char* tag, int every) : Family(tag, every) {}
    int add_leaf(const char* sym, HostFn fn, u32 obj_bytes, RetKind ret, const char* label, std::initializer_list<Arg> args,
                 const char* file = __builtin_FILE()) {
        int n = add(sym, fn, obj_bytes, ret, nullptr, label, file);
        if (n >= 0) {
            if ((size_t)n >= args_.size()) args_.resize(n + 1);
            args_[n].assign(args.begin(), args.end());
        }
        return n;
    }
    void add_regions(const Entry& e, const u64 x[9], bool, Regions& r) override {
        int n = (int)(&e - &entry(0));
        if (n < 0 || (size_t)n >= args_.size()) return;
        for (const Arg& a : args_[n]) {
            u64 p = x[a.reg];
            if (!p) continue;
            u64 len = a.len_reg >= 0 ? x[a.len_reg] * a.scale + a.extra : a.bytes;
            if (len > a.cap) len = a.cap;
            bool dup = false;
            for (auto& [q, m] : r.r) dup |= q == p && m >= len;
            if (len && !dup) r.add(p, (u32)len);
        }
    }

private:
    std::vector<std::vector<Arg>> args_;  // by entry index
};

// ---- AAPCS64 wrappers that also take reference parameters (as the guest's pointer) ----

template <typename T>
struct LeafArg {
    using Reg = T;
    static T get(Reg r) { return r; }
};
template <typename T>
struct LeafArg<T&> {
    using Reg = T*;
    static T& get(Reg r) { return *r; }
};

template <typename>
struct LeafTraits;
template <typename R, typename C, typename... A>
struct LeafTraits<R (C::*)(A...)> {
    using Ret = R;
    using Self = C;
    using Regs = std::tuple<typename LeafArg<A>::Reg...>;
    template <auto M, typename Tup, size_t... I>
    static R call(C* self, Tup& t, std::index_sequence<I...>) {
        return (self->*M)(LeafArg<A>::get(std::get<I>(t))...);
    }
};
template <typename R, typename C, typename... A>
struct LeafTraits<R (C::*)(A...) const> {
    using Ret = R;
    using Self = const C;
    using Regs = std::tuple<typename LeafArg<A>::Reg...>;
    template <auto M, typename Tup, size_t... I>
    static R call(const C* self, Tup& t, std::index_sequence<I...>) {
        return (self->*M)(LeafArg<A>::get(std::get<I>(t))...);
    }
};
template <typename R, typename... A>
struct LeafTraits<R (*)(A...)> {
    using Ret = R;
    using Regs = std::tuple<typename LeafArg<A>::Reg...>;
    template <auto F, typename Tup, size_t... I>
    static R call(Tup& t, std::index_sequence<I...>) {
        return F(LeafArg<A>::get(std::get<I>(t))...);
    }
};

template <auto M>
void leaf_method(Cpu& c) {
    using Tr = LeafTraits<decltype(M)>;
    auto* self = reinterpret_cast<typename Tr::Self*>(c.x(0));
    ArgReader rd(c, 1, 0);
    auto regs = std::apply([&](auto... d) { return typename Tr::Regs{rd.next<decltype(d)>()...}; }, typename Tr::Regs{});
    constexpr size_t n = std::tuple_size_v<typename Tr::Regs>;
    if constexpr (std::is_void_v<typename Tr::Ret>) Tr::template call<M>(self, regs, std::make_index_sequence<n>{});
    else set_result(c, Tr::template call<M>(self, regs, std::make_index_sequence<n>{}));
}

template <auto F>
void leaf_function(Cpu& c) {
    using Tr = LeafTraits<decltype(F)>;
    ArgReader rd(c, 0, 0);
    auto regs = std::apply([&](auto... d) { return typename Tr::Regs{rd.next<decltype(d)>()...}; }, typename Tr::Regs{});
    constexpr size_t n = std::tuple_size_v<typename Tr::Regs>;
    if constexpr (std::is_void_v<typename Tr::Ret>) Tr::template call<F>(regs, std::make_index_sequence<n>{});
    else set_result(c, Tr::template call<F>(regs, std::make_index_sequence<n>{}));
}

}  // namespace soa::live

// A guest member function replaced by a member of the recovered class, live-checked by `fam`.
#define LEAF_METHOD(fam, sym, method, obj_bytes, ret, note, ...) \
    static int NATIVE_CONCAT(leaf_reg_, __LINE__) = (fam).add_leaf(sym, &::soa::live::leaf_method<method>, obj_bytes, ret, note, __VA_ARGS__)
// A static member / free function (no `this`).
#define LEAF_FUNCTION(fam, sym, fn, ret, note, ...) \
    static int NATIVE_CONCAT(leaf_reg_, __LINE__) = (fam).add_leaf(sym, &::soa::live::leaf_function<fn>, 0, ret, note, __VA_ARGS__)
// A hand-written HostFn.
#define LEAF_HOSTFN(fam, sym, hostfn, obj_bytes, ret, note, ...) \
    static int NATIVE_CONCAT(leaf_reg_, __LINE__) = (fam).add_leaf(sym, hostfn, obj_bytes, ret, note, __VA_ARGS__)
