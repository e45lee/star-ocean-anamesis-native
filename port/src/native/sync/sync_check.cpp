// The live check of the sync natives: the family, the observations, shadows (sync_check.h).
#include "native/sync/sync_check.h"

#include "soaruntime/hle/thread.h"

namespace soa::native::sync {

live::ShadowFamily& family() {
    static live::ShadowFamily f("sync", 16);
    return f;
}
namespace {
// (registered at start-up, before --live-check is applied, even if no CheckedFn is constructed first)
[[maybe_unused]] live::ShadowFamily& g_family = family();
}  // namespace

thread_local Observation* t_obs = nullptr;

u8* shadow_buffer(int slot) {
    constexpr size_t kSize = 0x100;
    static_assert(sizeof(CMutex) <= kSize && sizeof(Event) <= kSize);
    alignas(16) static thread_local u8 buf[2][kSize];
    std::memset(buf[slot], 0, kSize);
    return buf[slot];
}

void make_shadow_lock(FastCriticalSection& cs, s32 waiters) {
    cs.m_waiters = waiters;
    Semaphore& s = cs.m_sem;
    if (s.m_pSem) {
        s.m_pSem = (u64)s.m_sem;
        hle_host_sem_init(s.m_pSem, 0);
    }
}

void release_shadow_lock(FastCriticalSection& cs) {
    if (u64 p = cs.m_sem.m_pSem) hle_host_sem_destroy(p);
}

}  // namespace soa::native::sync
