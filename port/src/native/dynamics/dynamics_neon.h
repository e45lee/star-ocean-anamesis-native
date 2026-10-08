#pragma once
// AArch64's reciprocal estimate / step instructions (FRECPE, FRSQRTE, FRECPS, FRSQRTS: single
// precision, FPCR = 0), as the guest's ADM solver uses them on NEON lanes: the ARM pseudocode, as
// dynarmic's JIT computes them (safe optimizations only: runtime/src/core/cpu.cpp), so the natives
// match the guest bit for bit, NaNs and denormals included (test dynamics/neon runs the
// instructions themselves). The step functions are fused (2 - a * b, (3 - a * b) / 2, one rounding).
namespace soa::native::dynamics::neon {

float frecpe(float x);
float frsqrte(float x);
float frecps(float a, float b);
float frsqrts(float a, float b);

}  // namespace soa::native::dynamics::neon
