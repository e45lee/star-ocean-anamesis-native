// The game string's out-of-line growth helpers: basic_string<char, char_traits<char>,
// Framework::CSTLAllocator<char, CSTLStringAllocatorInf>>::reserve / __grow_by /
// __grow_by_and_replace / replace(pos, n1, s, n2) (libcxx_layout.h; port/decomp/libcxx/string.c).
// libc++ 6.0's algorithms (r16b's <string>) over the NDK layout; storage from
// Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(n, "STL_String.h", 0x1c) / Free, called
// through live::out_call (a live check records them), with the allocator's asserts.
#include <cstring>

#include "soaruntime/core/loader.h"
#include "native/common/live_call.h"
#include "native/libcxx/libcxx_family.h"
#include "native/libcxx/libcxx_layout.h"
#include "native/libcxx/libcxx_string.h"
#include "native/memory/memory_callees.h"
#include "native/common/gen/common_addresses.h"

namespace soa::native::libcxx {

namespace {

using Str = basic_string<char>;
constexpr u64 kShortCap = 22;  // characters a short string holds

u64 guest(u64 vaddr) { return main_lib()->base + vaddr; }

void do_assert(u32 line, u64 msg) {
    static const u64 fn = main_lib()->sym("_ZN9Framework9gDoAssertEPKciS1_z");
    live::out_call(family(), fn, {guest(kStrStlAllocatorH), line, guest(msg)});
}
char* allocate(u64 bytes) {
    using memory::kStlAllocateCallee;
    auto* p = kStlAllocateCallee.direct()
                  ? (char*)memory::CAssignedMemoryManagerForSTLAllocator::Allocate(bytes, (const char*)guest(kStrStlStringH), 0x1c)
                  : (char*)live::out_call(family(), kStlAllocateCallee.addr(), {bytes, guest(kStrStlStringH), 0x1c});
    if (!p) do_assert(0xbe, kStrAllocatedMemoryIsNull);
    return p;
}
void deallocate(char* p) {
    if (memory::kStlFreeCallee.direct()) return memory::CAssignedMemoryManagerForSTLAllocator::Free(p);
    live::out_call(family(), memory::kStlFreeCallee.addr(), {(u64)p});
}

char* mutable_data(Str* s) { return s->is_long() ? s->r.l.data : (char*)&s->r.s.data[0]; }

// The allocation for a string growing from old_cap by delta: max(2 * old_cap, old_cap + delta)
// characters plus the NUL, at least 23 bytes, else rounded up to 16.
u64 grown_allocation(u64 old_cap, u64 delta) {
    if (old_cap >= 0x7fffffffffffffe7ull) return 0xffffffffffffffefull;
    u64 c = 2 * old_cap;
    if (c <= old_cap + delta) c = old_cap + delta;
    if (c < 0x17) return 0x17;
    c = (c + 0x10) & ~u64(0xf);
    if (c == 0) do_assert(0xbb, kStrNumElementsIsZero);
    return c;
}

}  // namespace

// New storage for old_cap + delta characters: the first n_copy characters, a gap of n_add, then the
// rest after n_del removed ones (the caller fills the gap and sets the size).
template <>
void Str::__grow_by(u64 old_cap, u64 delta_cap, u64 old_sz, u64 n_copy, u64 n_del, u64 n_add) {
    char* old = mutable_data(this);
    u64 alloc = grown_allocation(old_cap, delta_cap);
    char* p = allocate(alloc);
    if (n_copy) std::memcpy(p, old, n_copy);
    u64 sec = old_sz - n_del - n_copy;
    if (sec) std::memcpy(p + n_copy + n_add, old + n_copy + n_del, sec);
    if (old_cap != kShortCap) deallocate(old);
    r.l.data = p;
    r.l.cap = alloc | 1;
}

// The same, with s's n_add characters in the gap, the size set and the NUL written.
template <>
void Str::__grow_by_and_replace(u64 old_cap, u64 delta_cap, u64 old_sz, u64 n_copy, u64 n_del, u64 n_add, const char* s) {
    char* old = mutable_data(this);
    u64 alloc = grown_allocation(old_cap, delta_cap);
    char* p = allocate(alloc);
    if (n_copy) std::memcpy(p, old, n_copy);
    if (n_add) std::memcpy(p + n_copy, s, n_add);
    u64 sec = old_sz - n_del - n_copy;
    if (sec) std::memcpy(p + n_copy + n_add, old + n_copy + n_del, sec);
    if (old_cap != kShortCap) deallocate(old);
    u64 sz = old_sz - n_del + n_add;
    r.l.cap = alloc | 1;
    r.l.size = sz;
    r.l.data = p;
    p[sz] = 0;
}

// replace(pos, n1, s, n2) (pos <= size: the caller checked): in place when it fits (s may point into
// the string), else through __grow_by_and_replace.
template <>
Str* Str::replace(u64 pos, u64 n1, const char* s, u64 n2) {
    u64 sz = size(), cap = capacity();
    if (n1 > sz - pos) n1 = sz - pos;
    if (cap - sz + n1 < n2) {
        __grow_by_and_replace(cap, sz - n1 + n2 - cap, sz, pos, n1, n2, s);
        return this;
    }
    char* p = mutable_data(this);
    if (n1 != n2) {
        u64 n_move = sz - pos - n1;
        if (n_move) {
            if (n1 > n2) {
                if (n2) std::memmove(p + pos, s, n2);
                std::memmove(p + pos + n2, p + pos + n1, n_move);
                goto finish;
            }
            if (p + pos < s && s < p + sz) {
                if (p + pos + n1 <= s) {
                    s += n2 - n1;
                } else {  // s starts inside the replaced part
                    if (n1) std::memmove(p + pos, s, n1);
                    pos += n1;
                    s += n2;
                    n2 -= n1;
                    n1 = 0;
                }
            }
            std::memmove(p + pos + n2, p + pos + n1, n_move);
        }
    }
    if (n2) std::memmove(p + pos, s, n2);
finish:
    sz += n2 - n1;
    if (is_long()) r.l.size = sz;
    else r.s.head.size = (u8)(sz << 1);
    p[sz] = 0;
    return this;
}

// reserve(n): the capacity __recommend(max(n, size)) gives (22 short, else 16k - 1), moving the
// characters to new storage (or back into the short form).
template <>
void Str::reserve(u64 n) {
    u64 cap = capacity(), sz = size();
    u64 want = n < sz ? sz : n;
    want = want < 0x17 ? kShortCap : ((want + 0x10) & ~u64(0xf)) - 1;
    if (want == cap) return;
    bool was_long, now_long;
    char *to, *from;
    if (want == kShortCap) {
        was_long = true, now_long = false;
        from = r.l.data;
        to = (char*)&r.s.data[0];
    } else {
        if (want + 1 == 0) do_assert(0xbb, kStrNumElementsIsZero);
        to = allocate(want + 1);
        if (!to && want <= cap) return;  // (the guest's assert path: nothing changes)
        now_long = true;
        was_long = is_long();
        from = mutable_data(this);
    }
    u64 n_copy = size() + 1;
    if (n_copy) std::memcpy(to, from, n_copy);
    if (was_long) deallocate(from);
    if (now_long) {
        r.l.cap = (want + 1) | 1;
        r.l.size = sz;
        r.l.data = to;
    } else {
        r.s.head.size = (u8)(sz << 1);
    }
}

Str* string_replace(Str* self, u64 pos, u64 n1, const char* s, u64 n2) { return self->replace(pos, n1, s, n2); }

void string_copy_construct(Str* self, const Str& src) {
    std::memset(self, 0, sizeof *self);
    if (!src.is_long()) {
        *self = src;
        return;
    }
    u64 n = src.r.l.size;
    const char* from = src.r.l.data;
    char* to;
    if (n < 0x17) {
        self->r.s.head.size = (u8)(n << 1);
        to = (char*)&self->r.s.data[0];
    } else {
        u64 alloc = (n + 0x10) & ~u64(0xf);
        if (alloc == 0) do_assert(0xbb, kStrNumElementsIsZero);
        to = allocate(alloc);
        self->r.l.cap = alloc | 1;
        self->r.l.size = n;
        self->r.l.data = to;
    }
    if (n) std::memcpy(to, from, n);
    to[n] = 0;
}

void string_destroy(Str* self) {
    if (self->is_long()) deallocate(self->r.l.data);
}

// ---- natives ----

#define STR_SYM(m) "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE" m
using live::kInt;
using live::kVoid;
LEAF_METHOD(family(), STR_SYM("9__grow_byEmmmmmm"), &Str::__grow_by, sizeof(Str), kVoid, "std::string::__grow_by", {});
LEAF_METHOD(family(), STR_SYM("21__grow_by_and_replaceEmmmmmmPKc"), &Str::__grow_by_and_replace, sizeof(Str), kVoid, "std::string::__grow_by_and_replace", {});
LEAF_METHOD(family(), STR_SYM("7replaceEmmPKcm"), &Str::replace, sizeof(Str), kInt, "std::string::replace(pos, n1, s, n2)", {});
LEAF_METHOD(family(), STR_SYM("7reserveEm"), &Str::reserve, sizeof(Str), kVoid, "std::string::reserve", {});
#undef STR_SYM

}  // namespace soa::native::libcxx
