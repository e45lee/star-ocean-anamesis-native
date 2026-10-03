#include <math.h>

#include "core/hle.h"

namespace soa {

using D1 = double (*)(double);
using D2 = double (*)(double, double);
using F1 = float (*)(float);
using F2 = float (*)(float, float);

void register_libm(Hle& h) {
    HLE_WRAP_T(h, "acos", D1, ::acos);
    HLE_WRAP_T(h, "atan", D1, ::atan);
    HLE_WRAP_T(h, "cos", D1, ::cos);
    HLE_WRAP_T(h, "sin", D1, ::sin);
    HLE_WRAP_T(h, "exp", D1, ::exp);
    HLE_WRAP_T(h, "log", D1, ::log);
    HLE_WRAP_T(h, "sqrt", D1, ::sqrt);
    HLE_WRAP_T(h, "pow", D2, ::pow);
    HLE_WRAP_T(h, "acosf", F1, ::acosf);
    HLE_WRAP_T(h, "asinf", F1, ::asinf);
    HLE_WRAP_T(h, "atanf", F1, ::atanf);
    HLE_WRAP_T(h, "cosf", F1, ::cosf);
    HLE_WRAP_T(h, "sinf", F1, ::sinf);
    HLE_WRAP_T(h, "tanf", F1, ::tanf);
    HLE_WRAP_T(h, "expf", F1, ::expf);
    HLE_WRAP_T(h, "exp2f", F1, ::exp2f);
    HLE_WRAP_T(h, "logf", F1, ::logf);
    HLE_WRAP_T(h, "log10f", F1, ::log10f);
    HLE_WRAP_T(h, "sqrtf", F1, ::sqrtf);
    HLE_WRAP_T(h, "atan2f", F2, ::atan2f);
    HLE_WRAP_T(h, "fmodf", F2, ::fmodf);
    HLE_WRAP_T(h, "powf", F2, ::powf);
    h.fn("ldexp", [](Cpu& c) { c.set_d(0, ::ldexp(c.d(0), (int)c.x(0))); });
    h.fn("__isfinitef", [](Cpu& c) { c.set_x(0, isfinite(c.s(0)) ? 1 : 0); });
    h.fn("__isnanf", [](Cpu& c) { c.set_x(0, isnan(c.s(0)) ? 1 : 0); });
}

}  // namespace soa
