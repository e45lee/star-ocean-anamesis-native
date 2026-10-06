#pragma once
// printf/scanf formatting for guest varargs (register-passed or AArch64 va_list).
#include <string>
#include <vector>

#include "core/abi.h"

#ifdef _WIN32
#define WIN_HOST true
#else
#define WIN_HOST false
#endif

namespace soa {

class VaSource {
public:
    virtual ~VaSource() = default;
    virtual u64 next_int() = 0;
    virtual double next_double() = 0;
    virtual V128 next_quad() = 0;  // long double (binary128)
};

// Variadic arguments following named ones in registers/stack.
class RegVa final : public VaSource {
public:
    RegVa(Cpu& c, int named_ints, int named_fps = 0) : rd_(c, named_ints, named_fps) {}
    u64 next_int() override { return rd_.next_int(); }
    double next_double() override { return rd_.next_double(); }
    V128 next_quad() override { return rd_.next_v128(); }

private:
    ArgReader rd_;
};

// AArch64 va_list (struct { void* stack; void* gr_top; void* vr_top; int gr_offs; int vr_offs; }).
class GuestVaList final : public VaSource {
public:
    explicit GuestVaList(u64 ap) {
        const u64* p = (const u64*)ap;
        stack_ = p[0];
        gr_top_ = p[1];
        vr_top_ = p[2];
        gr_offs_ = ((const s32*)ap)[6];
        vr_offs_ = ((const s32*)ap)[7];
    }
    u64 next_int() override {
        if (gr_offs_ < 0) {
            u64 v = *(u64*)(gr_top_ + gr_offs_);
            gr_offs_ += 8;
            return v;
        }
        u64 v = *(u64*)stack_;
        stack_ += 8;
        return v;
    }
    double next_double() override {
        double d;
        if (vr_offs_ < 0) {
            std::memcpy(&d, (void*)(vr_top_ + vr_offs_), 8);
            vr_offs_ += 16;
        } else {
            std::memcpy(&d, (void*)stack_, 8);
            stack_ += 8;
        }
        return d;
    }
    V128 next_quad() override {
        V128 v;
        if (vr_offs_ < 0) {
            std::memcpy(&v, (void*)(vr_top_ + vr_offs_), 16);
            vr_offs_ += 16;
        } else {
            stack_ = (stack_ + 15) & ~15ull;
            std::memcpy(&v, (void*)stack_, 16);
            stack_ += 16;
        }
        return v;
    }

private:
    u64 stack_, gr_top_, vr_top_;
    s32 gr_offs_, vr_offs_;
};

std::string guest_format(const char* fmt, VaSource& va);
std::wstring guest_wformat(const wchar_t* fmt, VaSource& va);
// Collects the pointer arguments of a scanf format (at most 32).
std::vector<u64> scanf_args(const char* fmt, VaSource& va);
// The guest's scanf format for the host's scanf: the guest's `long` is 64-bit (LP64); on Windows
// (LLP64) an `l` integer conversion (%ld %li %lo %lu %lx %lX %ln) becomes `ll`, and so do `z`, `j`
// and `t` (64-bit on both, spelled `ll` for every CRT). Unchanged elsewhere (`win`: force the
// translation, for the tests on Linux). Not translated: `%ls` / `%lc` / `%l[` (the guest's wchar_t
// is 32-bit, Windows' 16-bit; the game doesn't scan wide strings) and `%Lf` (the guest's long double
// is binary128, the host's x87 80-bit on both hosts).
std::string host_scanf_format(const char* fmt, bool win = WIN_HOST);
// The guest's rand(): bionic's RAND_MAX is 0x7fffffff. Linux: the host's (glibc: the same
// TYPE_3 additive generator, seed 1). Windows, whose rand() is 15-bit: that generator here (the
// same sequence as Linux's while no host code there calls rand() in between: on Linux the guest
// shares glibc's state with the host). glibc_random: the generator itself; reset: back to seed 1,
// returning 0.
s32 guest_rand();
s32 glibc_random(bool reset = false);

}  // namespace soa
