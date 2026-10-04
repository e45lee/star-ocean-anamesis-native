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
    alignas(16) static thread_local u8 buf[sizeof(TouchPanel)];
    std::memset(buf, 0, sizeof buf);
    return buf;
}

}  // namespace soa::native::input
