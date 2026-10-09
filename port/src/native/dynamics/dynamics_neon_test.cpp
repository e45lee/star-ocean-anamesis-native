// dynamics_neon.h against the instructions themselves: FRECPE / FRSQRTE / FRECPS / FRSQRTS in a
// guest code page, run by the JIT, over every exponent with many fractions, both signs, NaNs,
// infinities, zeros and denormals, and step operands whose product is near 2 / 3 (cancellation,
// ties); compared bit for bit.
#include <cstring>

#include "soaruntime/core/cpu.h"
#include "native/common/test.h"
#include "native/dynamics/dynamics_neon.h"

namespace soa::native::dynamics {

namespace {

using u32 = std::uint32_t;

float from(u32 u) {
    float x;
    std::memcpy(&x, &u, 4);
    return x;
}
u32 bits(float f) {
    u32 u;
    std::memcpy(&u, &f, 4);
    return u;
}

// The four instructions, each followed by RET (a page mapped once for the process).
const u32* code() {
    static const u32* c = [] {
        auto* p = (u32*)map_guest_code(4096);
        const u32 prog[] = {
            0x5ea1d800, 0xd65f03c0,  // frecpe s0, s0; ret
            0x7ea1d800, 0xd65f03c0,  // frsqrte s0, s0; ret
            0x5e21fc00, 0xd65f03c0,  // frecps s0, s0, s1; ret
            0x5ea1fc00, 0xd65f03c0,  // frsqrts s0, s0, s1; ret
        };
        std::memcpy(p, prog, sizeof prog);
        return (const u32*)p;
    }();
    return c;
}

// A float with every exponent field over the run: sign, exponent and fraction from the case number
// and the RNG, NaNs (quiet and signalling, payloads) included.
u32 sweep(TestContext& t, int k) {
    u32 sign = (u32)(k & 1) << 31;
    u32 exp = (u32)((k >> 1) & 0xff);
    u32 frac;
    switch ((k >> 9) % 4) {
    case 0: frac = (u32)t.rand_int(0, 0x7fffff); break;
    case 1: frac = (u32)t.rand_int(0, 255) << 15; break;            // the estimate's input bits only
    case 2: frac = ((u32)t.rand_int(0, 255) << 15) | 0x7fff; break; // with every bit below them set
    default: frac = (u32)1 << t.rand_int(0, 22); break;             // one bit (denormals' normalization)
    }
    return sign | exp << 23 | frac;
}

}  // namespace

NATIVE_TEST("dynamics/neon") {
    const u64 base = (u64)code();
    int bad_e = 0, bad_r = 0, bad_ps = 0, bad_rs = 0;
    for (int k = 0; k < 400000; k++) {
        float x = from(sweep(t, k));
        float g = guest_invoke<float>(base, x), n = neon::frecpe(x);
        if (bits(g) != bits(n) && bad_e++ < 5) t.fail("frecpe(%08x): guest %08x, native %08x", bits(x), bits(g), bits(n));
        g = guest_invoke<float>(base + 8, x), n = neon::frsqrte(x);
        if (bits(g) != bits(n) && bad_r++ < 5) t.fail("frsqrte(%08x): guest %08x, native %08x", bits(x), bits(g), bits(n));
    }
    for (int k = 0; k < 400000; k++) {
        float a, b;
        if (k % 3 == 0) {  // random bit patterns, both operands from the sweep
            a = from(sweep(t, t.rand_int(0, 1 << 30)));
            b = from(sweep(t, t.rand_int(0, 1 << 30)));
        } else {  // a * b near 2 or 3, a few ulps either way
            a = std::ldexp(1.0f + (float)t.rand_int(0, 1 << 22) / (1 << 22), t.rand_int(-60, 60)) * (t.rand_int(0, 1) ? 1 : -1);
            float c = k % 3 == 1 ? 2.0f : 3.0f;
            b = c / a;
            u32 ub = bits(b) + (u32)t.rand_int(-3, 3);
            b = from(ub);
            if (t.rand_int(0, 1)) std::swap(a, b);
        }
        float g = guest_invoke<float>(base + 16, a, b), n = neon::frecps(a, b);
        if (bits(g) != bits(n) && bad_ps++ < 5) t.fail("frecps(%08x, %08x): guest %08x, native %08x", bits(a), bits(b), bits(g), bits(n));
        g = guest_invoke<float>(base + 24, a, b), n = neon::frsqrts(a, b);
        if (bits(g) != bits(n) && bad_rs++ < 5) t.fail("frsqrts(%08x, %08x): guest %08x, native %08x", bits(a), bits(b), bits(g), bits(n));
    }
    if (bad_e + bad_r + bad_ps + bad_rs)
        t.fail("mismatches: frecpe %d, frsqrte %d, frecps %d, frsqrts %d", bad_e, bad_r, bad_ps, bad_rs);
}

}  // namespace soa::native::dynamics
