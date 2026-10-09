#pragma once
// The prototype's run-time support for recompiled guest code (docs/PLAN-recomp.md, "The
// prototype"): the register file, and one inline function per dynarmic IR opcode the sample uses
// (recomp_gen.cpp prints every IR instruction as `rc::<Opcode>(s, args...)`). Semantics follow
// dynarmic's x64 backend, which the JIT runs today, with FPCR = 0 (the guest never writes FPCR):
// no flush-to-zero, no default NaN, round to nearest even. Floating-point NaN rules are the
// AArch64 ones (port/src/native/common/arm_float.h); conversions with a rounding mode call
// dynarmic's own software FP library (common/fp/op), so they are exact by construction.
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstring>

#include "dynarmic/common/fp/fpcr.h"
#include "dynarmic/common/fp/fpsr.h"
#include "dynarmic/common/fp/op/FPToFixed.h"
#include "dynarmic/common/fp/rounding_mode.h"

namespace rc {
namespace types {
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;
}  // namespace types
using namespace types;

struct U128 {
    u64 lo, hi;
};

// The guest register file. (The plan's design gives it A64JitState's layout so the runtime's
// Cpu can point at it; the prototype only needs the fields.)
struct St {
    u64 x[31];
    u64 sp;
    u64 pc;
    u32 nzcv;  // AArch64 order: N bit 31, Z 30, C 29, V 28
    bool check_bit;
    alignas(16) U128 v[32];
    u64 tpidr;
};

extern u64 lib_base;
using Fn = void (*)(St&);
struct Entry {
    u64 vaddr;
    Fn fn;
    const char* name;
};
// A call to guest address `target` (absolute): recompiled code, or the fallback (the JIT).
void call(St& s, u64 target);

// ---- flags
template <typename T>
struct WithFlags {
    T v;
    bool c, o;
    u32 nzcv;
};
inline u32 nzcv_of(bool n, bool z, bool c, bool v) { return (u32)n << 31 | (u32)z << 30 | (u32)c << 29 | (u32)v << 28; }
inline bool cond(const St& s, int c) {
    bool n = s.nzcv >> 31 & 1, z = s.nzcv >> 30 & 1, cf = s.nzcv >> 29 & 1, v = s.nzcv >> 28 & 1;
    bool r;
    switch (c >> 1) {
    case 0: r = z; break;
    case 1: r = cf; break;
    case 2: r = n; break;
    case 3: r = v; break;
    case 4: r = cf && !z; break;
    case 5: r = n == v; break;
    case 6: r = n == v && !z; break;
    default: return true;  // AL, NV
    }
    return (c & 1) ? !r : r;
}

// ---- context
inline u64 GetX(St& s, int r) { return s.x[r]; }
inline u32 GetW(St& s, int r) { return (u32)s.x[r]; }
inline void SetX(St& s, int r, u64 v) { s.x[r] = v; }
inline void SetW(St& s, int r, u32 v) { s.x[r] = v; }
inline u64 GetSP(St& s) { return s.sp; }
inline void SetSP(St& s, u64 v) { s.sp = v; }
inline void SetPC(St& s, u64 v) { s.pc = v; }
inline U128 GetS(St& s, int r) { return {s.v[r].lo & 0xffffffffu, 0}; }
inline U128 GetD(St& s, int r) { return {s.v[r].lo, 0}; }
inline U128 GetQ(St& s, int r) { return s.v[r]; }
inline void SetS(St& s, int r, U128 v) { s.v[r] = {v.lo & 0xffffffffu, 0}; }
inline void SetD(St& s, int r, U128 v) { s.v[r] = {v.lo, 0}; }
inline void SetQ(St& s, int r, U128 v) { s.v[r] = v; }
inline void SetNZCV(St& s, u32 nzcv) { s.nzcv = nzcv; }
inline u32 GetNZCVRaw(St& s) { return s.nzcv; }
inline void SetNZCVRaw(St& s, u32 v) { s.nzcv = v & 0xf0000000u; }
inline void SetCheckBit(St& s, bool b) { s.check_bit = b; }
inline u64 GetTPIDR(St& s) { return s.tpidr; }
inline u32 NZCVFromPackedFlags(St&, u32 v) { return v & 0xf0000000u; }

// ---- memory (guest memory is identity-mapped; the first argument is the instruction's location)
template <typename T>
inline T rd(u64 a) {
    T v;
    std::memcpy(&v, (const void*)a, sizeof(T));
    return v;
}
template <typename T>
inline void wr(u64 a, T v) {
    std::memcpy((void*)a, &v, sizeof(T));
}
inline u8 ReadMemory8(St&, u64, u64 a, int) { return rd<u8>(a); }
inline u16 ReadMemory16(St&, u64, u64 a, int) { return rd<u16>(a); }
inline u32 ReadMemory32(St&, u64, u64 a, int) { return rd<u32>(a); }
inline u64 ReadMemory64(St&, u64, u64 a, int) { return rd<u64>(a); }
inline U128 ReadMemory128(St&, u64, u64 a, int) { return rd<U128>(a); }
inline void WriteMemory8(St&, u64, u64 a, u8 v, int) { wr(a, v); }
inline void WriteMemory16(St&, u64, u64 a, u16 v, int) { wr(a, v); }
inline void WriteMemory32(St&, u64, u64 a, u32 v, int) { wr(a, v); }
inline void WriteMemory64(St&, u64, u64 a, u64 v, int) { wr(a, v); }
inline void WriteMemory128(St&, u64, u64 a, U128 v, int) { wr(a, v); }

// ---- integer
template <typename T>
inline WithFlags<T> add_f(T a, T b, bool cin) {
    using S = std::make_signed_t<T>;
    T r = a + b + (T)cin;
    bool c = cin ? r <= a : r < a;
    bool o = ((S)((a ^ r) & (b ^ r))) < 0;
    return {r, c, o, nzcv_of((S)r < 0, r == 0, c, o)};
}
inline u32 Add32(St&, u32 a, u32 b, bool c) { return a + b + c; }
inline u64 Add64(St&, u64 a, u64 b, bool c) { return a + b + c; }
inline WithFlags<u32> Add32_f(St&, u32 a, u32 b, bool c) { return add_f<u32>(a, b, c); }
inline WithFlags<u64> Add64_f(St&, u64 a, u64 b, bool c) { return add_f<u64>(a, b, c); }
inline u32 Sub32(St&, u32 a, u32 b, bool c) { return a + ~b + c; }
inline u64 Sub64(St&, u64 a, u64 b, bool c) { return a + ~b + c; }
inline WithFlags<u32> Sub32_f(St&, u32 a, u32 b, bool c) { return add_f<u32>(a, ~b, c); }
inline WithFlags<u64> Sub64_f(St&, u64 a, u64 b, bool c) { return add_f<u64>(a, ~b, c); }
template <typename T>
inline WithFlags<T> logic_f(T r) {
    return {r, false, false, nzcv_of((std::make_signed_t<T>)r < 0, r == 0, false, false)};
}
inline u32 And32(St&, u32 a, u32 b) { return a & b; }
inline u64 And64(St&, u64 a, u64 b) { return a & b; }
inline WithFlags<u32> And32_f(St&, u32 a, u32 b) { return logic_f<u32>(a & b); }
inline WithFlags<u64> And64_f(St&, u64 a, u64 b) { return logic_f<u64>(a & b); }
inline u32 AndNot32(St&, u32 a, u32 b) { return a & ~b; }
inline u64 AndNot64(St&, u64 a, u64 b) { return a & ~b; }
inline u32 Eor32(St&, u32 a, u32 b) { return a ^ b; }
inline u64 Eor64(St&, u64 a, u64 b) { return a ^ b; }
inline u32 Or32(St&, u32 a, u32 b) { return a | b; }
inline u64 Or64(St&, u64 a, u64 b) { return a | b; }
inline u32 Not32(St&, u32 a) { return ~a; }
inline u64 Not64(St&, u64 a) { return ~a; }
inline u64 Mul64(St&, u64 a, u64 b) { return a * b; }
inline u32 Mul32(St&, u32 a, u32 b) { return a * b; }
inline u64 UnsignedMultiplyHigh64(St&, u64 a, u64 b) { return (u64)(((unsigned __int128)a * b) >> 64); }
inline u64 SignedMultiplyHigh64(St&, u64 a, u64 b) { return (u64)(((__int128)(s64)a * (s64)b) >> 64); }
inline u32 LogicalShiftLeft32(St&, u32 a, u8 n, bool) { return n >= 32 ? 0 : a << n; }
inline u64 LogicalShiftLeft64(St&, u64 a, u8 n) { return n >= 64 ? 0 : a << n; }
inline u32 LogicalShiftRight32(St&, u32 a, u8 n, bool) { return n >= 32 ? 0 : a >> n; }
inline u64 LogicalShiftRight64(St&, u64 a, u8 n) { return n >= 64 ? 0 : a >> n; }
inline u32 ArithmeticShiftRight32(St&, u32 a, u8 n, bool) { return (u32)((s32)a >> (n >= 31 ? 31 : n)); }
inline u64 ArithmeticShiftRight64(St&, u64 a, u8 n) { return (u64)((s64)a >> (n >= 63 ? 63 : n)); }
inline u64 ArithmeticShiftRightMasked64(St&, u64 a, u64 n) { return (u64)((s64)a >> (n & 63)); }
inline u64 LogicalShiftLeftMasked64(St&, u64 a, u64 n) { return a << (n & 63); }
inline u64 LogicalShiftRightMasked64(St&, u64 a, u64 n) { return a >> (n & 63); }
inline u32 RotateRight32(St&, u32 a, u8 n, bool) { return std::rotr(a, n & 31); }
inline u64 RotateRight64(St&, u64 a, u8 n) { return std::rotr(a, n & 63); }
inline u32 ExtractRegister32(St&, u32 a, u32 b, u8 lsb) { return lsb == 0 ? a : (a >> lsb) | (b << (32 - lsb)); }
inline u64 ExtractRegister64(St&, u64 a, u64 b, u8 lsb) { return lsb == 0 ? a : (a >> lsb) | (b << (64 - lsb)); }
inline u32 ReplicateBit32(St&, u32 a, u8 bit) { return (a >> bit & 1) ? ~0u : 0u; }
inline u64 ReplicateBit64(St&, u64 a, u8 bit) { return (a >> bit & 1) ? ~0ull : 0ull; }
inline bool TestBit(St&, u64 a, u8 bit) { return (a >> bit) & 1; }
inline bool IsZero32(St&, u32 a) { return a == 0; }
inline bool IsZero64(St&, u64 a) { return a == 0; }
inline u32 ByteReverseWord(St&, u32 a) { return __builtin_bswap32(a); }
inline u64 ByteReverseDual(St&, u64 a) { return __builtin_bswap64(a); }
inline u8 LeastSignificantByte(St&, u32 a) { return (u8)a; }
inline u16 LeastSignificantHalf(St&, u32 a) { return (u16)a; }
inline u32 LeastSignificantWord(St&, u64 a) { return (u32)a; }
inline u32 ZeroExtendByteToWord(St&, u8 a) { return a; }
inline u32 ZeroExtendHalfToWord(St&, u16 a) { return a; }
inline u64 ZeroExtendWordToLong(St&, u32 a) { return a; }
inline u64 ZeroExtendByteToLong(St&, u8 a) { return a; }
inline u64 ZeroExtendHalfToLong(St&, u16 a) { return a; }
inline U128 ZeroExtendLongToQuad(St&, u64 a) { return {a, 0}; }
inline u32 SignExtendByteToWord(St&, u8 a) { return (u32)(s32)(s8)a; }
inline u32 SignExtendHalfToWord(St&, u16 a) { return (u32)(s32)(s16)a; }
inline u64 SignExtendWordToLong(St&, u32 a) { return (u64)(s64)(s32)a; }
inline u64 SignExtendByteToLong(St&, u8 a) { return (u64)(s64)(s8)a; }
inline u64 SignExtendHalfToLong(St&, u16 a) { return (u64)(s64)(s16)a; }
inline u32 ConditionalSelect32(St& s, int c, u32 a, u32 b) { return cond(s, c) ? a : b; }
inline u64 ConditionalSelect64(St& s, int c, u64 a, u64 b) { return cond(s, c) ? a : b; }
inline u32 ConditionalSelectNZCV(St& s, int c, u32 a, u32 b) { return cond(s, c) ? a : b; }

// ---- scalar floating point (single precision, FPCR = 0)
inline float f32(u32 b) { return std::bit_cast<float>(b); }
inline u32 b32(float f) { return std::bit_cast<u32>(f); }
inline bool is_nan32(u32 a) { return (a & 0x7fffffffu) > 0x7f800000u; }
inline bool is_snan32(u32 a) { return is_nan32(a) && !(a & 0x00400000u); }
// AArch64 NaN propagation for a two-operand op whose host result is a NaN (out of line: rare).
[[gnu::cold, gnu::noinline]] inline u32 nan2_slow(u32 a, u32 b) {
    if (is_snan32(a)) return a | 0x00400000u;
    if (is_snan32(b)) return b | 0x00400000u;
    if (is_nan32(a)) return a;
    if (is_nan32(b)) return b;
    return 0x7fc00000u;  // the default NaN (an invalid operation)
}
inline u32 nan2(u32 a, u32 b, float r) {
    if (!std::isnan(r)) [[likely]]
        return b32(r);
    return nan2_slow(a, b);
}
inline u32 FPAdd32(St&, u32 a, u32 b) { return nan2(a, b, f32(a) + f32(b)); }
inline u32 FPSub32(St&, u32 a, u32 b) { return nan2(a, b, f32(a) - f32(b)); }
inline u32 FPMul32(St&, u32 a, u32 b) { return nan2(a, b, f32(a) * f32(b)); }
inline u32 FPDiv32(St&, u32 a, u32 b) { return nan2(a, b, f32(a) / f32(b)); }
inline u32 FPMulAdd32(St&, u32 acc, u32 a, u32 b) {  // acc + a * b, fused
    if (is_nan32(acc) || is_nan32(a) || is_nan32(b)) {
        // (AArch64 FPProcessNaNs3: sNaNs first in operand order acc, a, b, then qNaNs; inf*0 + qNaN = default NaN)
        if (is_snan32(acc)) return acc | 0x00400000u;
        if (is_snan32(a)) return a | 0x00400000u;
        if (is_snan32(b)) return b | 0x00400000u;
        bool inf_zero = ((a & 0x7fffffffu) == 0x7f800000u && (b & 0x7fffffffu) == 0) || ((b & 0x7fffffffu) == 0x7f800000u && (a & 0x7fffffffu) == 0);
        if (inf_zero) return 0x7fc00000u;
        if (is_nan32(acc)) return acc;
        if (is_nan32(a)) return a;
        return b;
    }
    float r = std::fma(f32(a), f32(b), f32(acc));
    return std::isnan(r) ? 0x7fc00000u : b32(r);
}
inline u32 FPSqrt32(St&, u32 a) {
    if (is_nan32(a)) return a | 0x00400000u;
    float r = std::sqrt(f32(a));
    return std::isnan(r) ? 0x7fc00000u : b32(r);
}
inline u32 FPAbs32(St&, u32 a) { return a & 0x7fffffffu; }
inline u32 FPNeg32(St&, u32 a) { return a ^ 0x80000000u; }
inline u32 FPMax32(St&, u32 a, u32 b) {
    if (is_nan32(a) || is_nan32(b)) return nan2(a, b, NAN);
    if ((a & 0x7fffffffu) == 0 && (b & 0x7fffffffu) == 0) return a & b;  // max(+0, -0) = +0
    return f32(a) > f32(b) ? a : b;
}
inline u32 FPMin32(St&, u32 a, u32 b) {
    if (is_nan32(a) || is_nan32(b)) return nan2(a, b, NAN);
    if ((a & 0x7fffffffu) == 0 && (b & 0x7fffffffu) == 0) return a | b;  // min(+0, -0) = -0
    return f32(a) < f32(b) ? a : b;
}
inline u32 FPCompare32(St&, u32 a, u32 b, bool) {
    float x = f32(a), y = f32(b);
    if (std::isnan(x) || std::isnan(y)) return 0x30000000u;  // C V
    if (x == y) return 0x60000000u;                          // Z C
    if (x < y) return 0x80000000u;                           // N
    return 0x20000000u;                                      // C
}
inline u32 FPSingleToFixedS32(St&, u32 a, u8 fbits, u8 rounding) {
    Dynarmic::FP::FPSR fpsr;
    return (u32)Dynarmic::FP::FPToFixed<u32>(32, a, fbits, false, Dynarmic::FP::FPCR{0}, (Dynarmic::FP::RoundingMode)rounding, fpsr);
}
inline u32 FPSingleToFixedU32(St&, u32 a, u8 fbits, u8 rounding) {
    Dynarmic::FP::FPSR fpsr;
    return (u32)Dynarmic::FP::FPToFixed<u32>(32, a, fbits, true, Dynarmic::FP::FPCR{0}, (Dynarmic::FP::RoundingMode)rounding, fpsr);
}
inline u32 FPFixedS32ToSingle(St&, u32 a, u8 fbits, u8 rounding) {
    // (round to nearest only, as the host's default; the sample uses fbits 0 and ToNearest)
    float r = (float)(s32)a;
    if (fbits) r = r / (float)(1ull << fbits);
    (void)rounding;
    return b32(r);
}

// ---- vectors (lanes of 32 bits; U128 lo = lanes 0-1)
inline u32 lane(U128 v, int i) {
    u32 l[4];
    std::memcpy(l, &v, 16);
    return l[i & 3];
}
inline void set_lane(U128& v, int i, u32 x) {
    u32 l[4];
    std::memcpy(l, &v, 16);
    l[i & 3] = x;
    std::memcpy(&v, l, 16);
}
template <typename F>
inline U128 map2(U128 a, U128 b, F f) {
    u32 x[4], y[4], r[4];
    std::memcpy(x, &a, 16);
    std::memcpy(y, &b, 16);
    for (int i = 0; i < 4; i++) r[i] = f(x[i], y[i]);
    U128 o;
    std::memcpy(&o, r, 16);
    return o;
}
// Four float lanes at once on the host's SIMD unit; any NaN lane redoes the vector with the
// AArch64 NaN rules lane by lane (as dynarmic's backend does).
typedef float v4f __attribute__((vector_size(16)));
typedef int v4i __attribute__((vector_size(16)));
template <typename Op, typename Slow>
inline U128 vec2(U128 a, U128 b, Op op, Slow slow) {
    v4f x, y;
    std::memcpy(&x, &a, 16);
    std::memcpy(&y, &b, 16);
    v4f r = op(x, y);
    v4i nan = r != r;
    U128 o;
    if (__builtin_expect((nan[0] | nan[1] | nan[2] | nan[3]) != 0, 0)) return map2(a, b, slow);
    std::memcpy(&o, &r, 16);
    return o;
}
inline U128 FPVectorAdd32(St& s, U128 a, U128 b, bool) {
    return vec2(a, b, [](v4f x, v4f y) { return x + y; }, [&](u32 x, u32 y) { return FPAdd32(s, x, y); });
}
inline U128 FPVectorSub32(St& s, U128 a, U128 b, bool) {
    return vec2(a, b, [](v4f x, v4f y) { return x - y; }, [&](u32 x, u32 y) { return FPSub32(s, x, y); });
}
inline U128 FPVectorMul32(St& s, U128 a, U128 b, bool) {
    return vec2(a, b, [](v4f x, v4f y) { return x * y; }, [&](u32 x, u32 y) { return FPMul32(s, x, y); });
}
inline U128 FPVectorMax32(St& s, U128 a, U128 b, bool) { return map2(a, b, [&](u32 x, u32 y) { return FPMax32(s, x, y); }); }
inline U128 FPVectorMin32(St& s, U128 a, U128 b, bool) { return map2(a, b, [&](u32 x, u32 y) { return FPMin32(s, x, y); }); }
inline U128 FPVectorGreater32(St&, U128 a, U128 b, bool) {
    return map2(a, b, [](u32 x, u32 y) { return f32(x) > f32(y) ? ~0u : 0u; });
}
inline U128 FPVectorAbs32(St&, U128 a) { return {a.lo & 0x7fffffff7fffffffull, a.hi & 0x7fffffff7fffffffull}; }
inline U128 FPVectorPairedAddLower32(St& s, U128 a, U128 b, bool) {
    U128 r{0, 0};
    set_lane(r, 0, FPAdd32(s, lane(a, 0), lane(a, 1)));
    set_lane(r, 1, FPAdd32(s, lane(b, 0), lane(b, 1)));
    return r;
}
inline U128 VectorAnd(St&, U128 a, U128 b) { return {a.lo & b.lo, a.hi & b.hi}; }
inline U128 VectorOr(St&, U128 a, U128 b) { return {a.lo | b.lo, a.hi | b.hi}; }
inline U128 VectorEor(St&, U128 a, U128 b) { return {a.lo ^ b.lo, a.hi ^ b.hi}; }
inline U128 VectorNot(St&, U128 a) { return {~a.lo, ~a.hi}; }
inline U128 VectorZeroUpper(St&, U128 a) { return {a.lo, 0}; }
inline U128 VectorBroadcast64(St&, u64 a) { return {a, a}; }
inline U128 VectorBroadcast32(St&, u32 a) { u64 w = (u64)a << 32 | a; return {w, w}; }
inline U128 VectorBroadcastElement32(St&, U128 a, u8 i) { u64 w = (u64)lane(a, i) << 32 | lane(a, i); return {w, w}; }
inline U128 VectorBroadcastElementLower32(St&, U128 a, u8 i) { u64 w = (u64)lane(a, i) << 32 | lane(a, i); return {w, 0}; }
inline u32 VectorGetElement32(St&, U128 a, u8 i) { return lane(a, i); }
inline u64 VectorGetElement64(St&, U128 a, u8 i) { return i ? a.hi : a.lo; }
inline U128 VectorSetElement32(St&, U128 a, u8 i, u32 x) { set_lane(a, i, x); return a; }
inline U128 VectorSetElement64(St&, U128 a, u8 i, u64 x) { (i ? a.hi : a.lo) = x; return a; }
inline U128 VectorReverseElementsInLongGroups32(St&, U128 a) { return {std::rotl(a.lo, 32), std::rotl(a.hi, 32)}; }
inline U128 VectorExtract(St&, U128 a, U128 b, u8 pos) {  // (b:a) >> pos bits
    unsigned __int128 lo = (unsigned __int128)a.hi << 64 | a.lo, hi = (unsigned __int128)b.hi << 64 | b.lo;
    unsigned __int128 r = pos == 0 ? lo : (lo >> pos) | (hi << (128 - pos));
    return {(u64)r, (u64)(r >> 64)};
}

}  // namespace rc
