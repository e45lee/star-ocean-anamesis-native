// The live check of the input natives: the family, the observations, the shadow (input_check.h).
#include "native/input/input_check.h"

namespace soa::native::input {

live::ShadowFamily& family() {
    static live::ShadowFamily f("input", 16);
    return f;
}
namespace {
[[maybe_unused]] live::ShadowFamily& g_family = family();  // (registered at start-up)
}  // namespace

thread_local Observation* t_obs = nullptr;

u8* shadow_object() {
    struct Shadow {
        alignas(16) u8 buf[sizeof(TouchPanel)];
    };
    u8* buf = live::thread_scratch<Shadow>().buf;
    std::memset(buf, 0, sizeof(Shadow::buf));
    return buf;
}

}  // namespace soa::native::input
