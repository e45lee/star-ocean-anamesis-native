#pragma once
// The `math` subsystem's live-check family (--live-check math) and the float helpers its natives
// share. Every native is registered through the family (native/common/live_leaf.h), so a normal run
// can compare each with the guest original.
//
// Floating point: the 3.7.0 lib has no fused multiply-add instruction at all (fmadd / fmla: 0 in
// its disassembly), so every product is rounded before it is added: plain * and + here, compiled
// with -ffp-contract=off (subsystem.cmake). The natives compute in armf::F (native/common/
// arm_float.h): float with AArch64's NaN rules (the default NaN 0x7fc00000, operand order), so
// they stay bit-exact when a NaN appears. Branches follow the guest's condition codes, not
// Ghidra's C (which reads them as ordered compares): after FCMP a, b an unordered compare takes
// `lt`, `le`, `hi`, `pl`/`hs`, `ne` and skips `gt`, `ge`, `mi`, `ls`, `eq`; write `b.ls x` as
// `if (a <= b) goto x` and `b.lt x` as `if (!(a >= b)) goto x`.
#include <cmath>

#include "native/common/arm_float.h"
#include "native/common/live_leaf.h"
#include "native/math/math_constants.h"

namespace soa::native::math {

live::LeafFamily& family();

using F = armf::F;
// FSQRT, then the guest's fallback: a NaN result calls libm's sqrtf (the HLE thunk: the host's
// sqrtf), which for any input is the host's own sqrtf result.
inline F Sqrt(F x) { return F(::sqrtf(x.v)); }
inline F Max(F a, F b) { return F(armf::max(a.v, b.v)); }
inline F Abs(F a) { return F(std::fabs(a.v)); }  // FABS: the sign bit only
inline float f(F a) { return a.v; }

}  // namespace soa::native::math
