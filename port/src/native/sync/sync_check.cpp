// The live check of the sync natives: the family and the shadow buffers (sync_check.h; the switch,
// counters and comparison helpers are common/shadow_check.h's).
#include "native/sync/sync_check.h"

#include <cstring>

namespace soa::native::sync {

live::ShadowFamily& family() {
    static live::ShadowFamily f("sync", 16);
    return f;
}
namespace {
[[maybe_unused]] live::ShadowFamily& g_registered = family();  // (registered before --live-check is applied)
}

thread_local Observation* t_obs = nullptr;

u8* shadow_buffer(int slot) {
    constexpr size_t kSize = 0x100;
    static_assert(sizeof(CMutex) <= kSize && sizeof(Event) <= kSize);
    alignas(16) static thread_local u8 buf[2][kSize];
    std::memset(buf[slot], 0, kSize);
    return buf[slot];
}

}  // namespace soa::native::sync
