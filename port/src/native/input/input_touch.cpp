// Aska::TouchPanel::CopyMessages and ResetStatus (port/decomp/input/aska.c).
//
// The touch path (runtime/README.md "Scripted taps"): the Java side queues motion events in
// TouchPanel::m_queueSystemTouchData, the PeripheralManager thread turns them into m_data
// (GetDeviceData, guest code, every 8 ms, under m_criGlobal and the panel's lock), and the game
// thread's CTouchPanel::Progress copies one frame's messages out with CopyMessages and clears them
// with CTouchPanel::Reset -> ResetStatus. These two are the guest's code but for the inlined
// FastCriticalSection (sync's Enter / Leave on the same words): which messages a frame sees is decided
// by the same locks in the same order, so the scripted taps' pacing (it counts the guest's queue reads)
// is unchanged.
#include <cstring>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/native_method.h"
#include "native/input/input_check.h"
#include "native/input/input_layout.h"

namespace soa::native::input {

FastCriticalSection* TouchPanel::CriGlobal() { return reinterpret_cast<FastCriticalSection*>(main_lib()->base + kVaddrTouchCriGlobal); }

// The frame's messages into `out` (n * 0x98 bytes), n returned; m_data stays (ResetStatus clears it).
// Takes m_criGlobal, then the panel's lock; releases m_criGlobal first, as the guest does.
s32 TouchPanel::CopyMessages(TouchData* out) {
    FastCriticalSection* global = CriGlobal();
    global->Enter();
    base.m_cs.Enter();
    if (t_obs) t_obs->save_pre(this);
    s32 n = m_numData;
    std::memcpy(out, m_data, (size_t)(s64)n * sizeof(TouchData));
    global->Leave();
    base.m_cs.Leave();
    return n;
}

void TouchPanel::ResetStatus() {
    base.m_cs.Enter();
    if (t_obs) t_obs->save_pre(this);
    m_numData = 0;
    if (t_obs) t_obs->save_post(this);
    base.m_cs.Leave();
}

// ---- bindings and live checks (input_check.h) ----

namespace {

CheckedFn g_copy("_ZN4Aska10TouchPanel12CopyMessagesEPNS_9TouchDataE"), g_reset("_ZN4Aska10TouchPanel11ResetStatusEv");

void reset_checked(Cpu& c) { locked_checked<TouchPanel, &TouchPanel::ResetStatus>(c, g_reset); }

// CopyMessages: the guest original on a shadow of the panel as the native saw it (it takes the real
// m_criGlobal, then the shadow's lock) into a scratch buffer: the count, the copied messages and the
// (unchanged) panel must match the native's.
void copy_checked(Cpu& c) {
    if (!live::check_due(g_copy)) return wrap_method<&TouchPanel::CopyMessages>()(c);
    live::CheckScope scope;
    static thread_local Observation obs;
    obs.have_pre = false;
    auto* out = reinterpret_cast<const u8*>(c.x(1));
    t_obs = &obs;
    wrap_method<&TouchPanel::CopyMessages>()(c);
    t_obs = nullptr;
    s32 n = (s32)c.x(0);
    if (!obs.have_pre) return live::check_result(g_copy, live::Outcome::Skipped, "no observation");
    constexpr int kMaxMessages = 64;
    if (n < 0 || n > kMaxMessages) return live::check_result(g_copy, live::Outcome::Skipped, "message count out of range");
    auto* sh = reinterpret_cast<TouchPanel*>(shadow_object());
    std::memcpy((void*)sh, obs.pre, sizeof(TouchPanel));
    sh->base.m_cs.m_lock = FastCriticalSection::kFree;
    sync::make_shadow_lock(sh->base.m_cs);
    alignas(16) static thread_local TouchData scratch[kMaxMessages];
    std::memset(scratch, 0xa5, sizeof scratch);
    s32 n_guest = (s32)guest_call(g_copy.orig, {(u64)sh, (u64)scratch});
    std::string why;
    if (n_guest != n) why = "count: native " + std::to_string(n) + " guest " + std::to_string(n_guest);
    if (why.empty()) why = live::diff_bytes(out, (const u8*)scratch, 0, (size_t)n * sizeof(TouchData));
    if (why.empty())
        why = live::diff_bytes(obs.pre, (const u8*)sh, 0, sizeof(TouchPanel), {{kLockWordOff, kLockWordOff + 8}, {kSemPtrOff, kSemPtrOff + 8}});
    sync::release_shadow_lock(sh->base.m_cs);
    live::check_result(g_copy, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska10TouchPanel12CopyMessagesEPNS_9TouchDataE", copy_checked,
                     "input: Aska::TouchPanel::CopyMessages (m_criGlobal + the panel's lock: sync's FastCriticalSection)", &g_copy.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska10TouchPanel11ResetStatusEv", reset_checked, "input: Aska::TouchPanel::ResetStatus", &g_reset.orig);

}  // namespace soa::native::input
