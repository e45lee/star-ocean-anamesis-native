// Aska::Pad's locked setters and Flip, Framework::CPad::Merge (port/decomp/input/aska.c, framework.c).
//
// Pad's setters and Flip are called every frame by the game thread (CPad::CUnit::Progress,
// CPad::Progress) while the PeripheralManager thread polls the pad: each takes the pad's
// FastCriticalSection, which the guest inlines (an LDAXR / STLXR spin of up to 512 probes, the waiter
// count, the semaphore); nearly all of their guest time was that spin. Here it is sync's
// FastCriticalSection::Enter / Leave on the same words, so the guest code that still takes the lock
// (Pad::GetStatus / UpdateKeyStatus / Release on the peripheral thread) and these natives exclude each
// other (sync/cmutex-contention mixes the two on one lock).
#include <cmath>
#include <cstring>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/loader.h"
#include "native/common/guest_assert.h"
#include "native/common/native_method.h"
#include "native/input/input_check.h"
#include "native/input/input_layout.h"
#include "native/common/gen/common_addresses.h"

namespace soa::native::input {

namespace {

// Pad.cpp's / TSingleton.h's assert strings: input/addresses.txt, common's kStrInstanceNull.

template <typename T>
T* static_at(u64 vaddr) {
    return *reinterpret_cast<T**>(main_lib()->base + vaddr);
}

// |v| as the guest computes it (cneg: wraps at INT_MIN).
inline s32 iabs(s32 v) { return v < 0 ? (s32)(0u - (u32)v) : v; }

// One source's keys into the merge (CPad::Merge does this for every unit and the active pad):
// masks OR'ed, analog values kept when larger in magnitude, triggers when larger.
void merge_keys(CPadMerged& m, const PadKeys& k) {
    m.m_now |= k.m_now;
    m.m_before |= k.m_before;
    m.m_stock |= k.m_stock;
    m.m_single |= k.m_single;
    m.m_release |= k.m_release;
    m.m_repeat |= k.m_repeat;
    m.m_repeatEach |= k.m_repeatEach;
    if (iabs(m.m_lx) < iabs(k.m_lx)) m.m_lx = k.m_lx;
    if (iabs(m.m_ly) < iabs(k.m_ly)) m.m_ly = k.m_ly;
    if (iabs(m.m_rx) < iabs(k.m_rx)) m.m_rx = k.m_rx;
    if (iabs(m.m_ry) < iabs(k.m_ry)) m.m_ry = k.m_ry;
    // fabs + fcmp; b.pl skips the store: an unordered compare (NaN) keeps the merged value, as `<` does.
    if (std::fabs(m.m_lxf) < std::fabs(k.m_lxf)) m.m_lxf = k.m_lxf;
    if (std::fabs(m.m_lyf) < std::fabs(k.m_lyf)) m.m_lyf = k.m_lyf;
    if (std::fabs(m.m_rxf) < std::fabs(k.m_rxf)) m.m_rxf = k.m_rxf;
    if (std::fabs(m.m_ryf) < std::fabs(k.m_ryf)) m.m_ryf = k.m_ryf;
    // ucvtf both sides, fcmp
    if ((float)m.m_lt < (float)k.m_lt) m.m_lt = k.m_lt;
    if ((float)m.m_rt < (float)k.m_rt) m.m_rt = k.m_rt;
}

}  // namespace

// ---- statics read from the guest (Aska::Global, the TSingletons) ----

PeripheralManager* PeripheralManager::Instance() { return static_at<PeripheralManager>(kVaddrPeripheralManager); }
BasePeripheral* PeripheralManager::GetActivePad() {
    PeripheralManager* pm = Instance();
    return pm ? pm->m_pad : nullptr;
}
CPad* CPad::Instance() { return static_at<CPad>(kVaddrCPadInstance); }
CKeyboard* CKeyboard::Instance() { return static_at<CKeyboard>(kVaddrCKeyboardInstance); }

bool CKeyboard::Now(s32 key) const {
    // (Keyboard.cpp's range asserts never fire for the constant CPad::Merge passes)
    return (m_down[(u32)key >> 3] >> (key & 7)) & 1;
}

// ---- Aska::Pad: the setters CPad::CUnit::Progress calls every frame, Flip ----

void Pad::SetAnalogAsDigital(u8 on) {
    base.m_cs.Enter();
    if (t_obs) t_obs->save_pre(this);
    m_analogAsDigital = on & 1;
    if (t_obs) t_obs->save_post(this);
    base.m_cs.Leave();
}

void Pad::SetRepeatThreshold(u8 frames) {
    base.m_cs.Enter();
    if (t_obs) t_obs->save_pre(this);
    m_repeatThreshold = frames;
    if (t_obs) t_obs->save_post(this);
    base.m_cs.Leave();
}

void Pad::SetRepeatInterval(u8 frames) {
    base.m_cs.Enter();
    if (t_obs) t_obs->save_pre(this);
    m_repeatInterval = frames;
    if (t_obs) t_obs->save_post(this);
    base.m_cs.Leave();
}

// Resets the front keys (vtable slot 10: PadDroid's is empty) outside the lock, then swaps the
// buffers under it; the new back buffer starts from the front's m_now (UpdateKeyStatus' "before").
void Pad::Flip() {
    u64 reset = reinterpret_cast<const u64*>(base.vtable)[peripheral_slot::kResetStatus];
    guest_call(reset, {(u64)this});
    base.m_cs.Enter();
    if (t_obs) t_obs->save_pre(this);
    s32 old = m_front;
    m_front = old ^ 1;
    m_keys[old].m_now = m_keys[m_front].m_now;
    if (t_obs) t_obs->save_post(this);
    base.m_cs.Leave();
}

// ---- Framework::CPad::Merge ----

// Every unit's keys (of the TSingleton's CPad, not `this`: the guest reads the units through the
// singleton) and the active Aska pad's front keys merged into m_merged. The guest also reads
// CKeyboard::Now(0x85) and drops the result (a debug key, compiled out).
void CPad::Merge() {
    CPadMerged& m = m_merged;
    // (the guest's inline zeroing covers 0xd4..0x10b but unk_0e)
    m.m_now = m.m_before = m.m_stock = m.m_single = m.m_release = m.m_repeat = m.m_repeatEach = 0;
    m.m_lt = m.m_rt = 0;
    m.m_lx = m.m_ly = m.m_rx = m.m_ry = 0;
    m.m_lxf = m.m_lyf = m.m_rxf = m.m_ryf = 0.0f;
    CKeyboard* kb = CKeyboard::Instance();
    if (!kb) {
        guest_assert(kTSingletonH, 0x23, kStrInstanceNull);
        kb = CKeyboard::Instance();
    }
    (void)kb->Now(0x85);
    CPad* pad = CPad::Instance();
    for (u32 i = 0;; i++) {
        if (!pad) {
            guest_assert(kTSingletonH, 0x23, kStrInstanceNull);
            pad = CPad::Instance();
        }
        if (pad->m_numUnits <= i) break;
        if (!pad->m_units) guest_assert(kPadCpp, 0x9f, kUnitsNull);
        merge_keys(m, pad->m_units[i].m_keys);
        pad = CPad::Instance();
    }
    // (Pad.cpp:0xa0's index assert in the loop is unreachable after the loop's own bound)
    if (auto* active = reinterpret_cast<Pad*>(PeripheralManager::GetActivePad())) merge_keys(m, active->m_keys[active->m_front]);
}

// ---- bindings and live checks (input_check.h) ----

namespace {

CheckedFn g_analog("_ZN4Aska3Pad18SetAnalogAsDigitalEb"), g_threshold("_ZN4Aska3Pad18SetRepeatThresholdEh"),
    g_interval("_ZN4Aska3Pad17SetRepeatIntervalEh"), g_flip("_ZN4Aska3Pad4FlipEv"), g_merge("_ZN9Framework4CPad5MergeEv");

void analog_checked(Cpu& c) { locked_checked<Pad, &Pad::SetAnalogAsDigital>(c, g_analog); }
void threshold_checked(Cpu& c) { locked_checked<Pad, &Pad::SetRepeatThreshold>(c, g_threshold); }
void interval_checked(Cpu& c) { locked_checked<Pad, &Pad::SetRepeatInterval>(c, g_interval); }
void flip_checked(Cpu& c) { locked_checked<Pad, &Pad::Flip>(c, g_flip); }

// Merge writes only m_merged from the units and the active pad, which the game thread (this one)
// owns: the guest original runs on a copy of `this` whose m_merged is poisoned, and must rebuild
// exactly the native's.
void merge_checked(Cpu& c) {
    if (!live::check_due(g_merge)) return wrap_method<&CPad::Merge>()(c);
    live::CheckScope scope;
    auto* self = reinterpret_cast<CPad*>(c.x(0));
    wrap_method<&CPad::Merge>()(c);
    auto* sh = reinterpret_cast<CPad*>(shadow_object());
    std::memcpy((void*)sh, self, sizeof(CPad));
    std::memset((void*)&sh->m_merged, 0xa5, offsetof(CPadMerged, unk_0e));
    std::memset((u8*)&sh->m_merged + offsetof(CPadMerged, m_lt), 0xa5, sizeof(CPadMerged) - offsetof(CPadMerged, m_lt));
    guest_call(g_merge.orig, {(u64)sh});
    constexpr size_t lo = offsetof(CPad, m_merged), hi = lo + sizeof(CPadMerged);
    std::string why = live::diff_bytes((const u8*)self, (const u8*)sh, lo, hi);
    live::check_result(g_merge, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska3Pad18SetAnalogAsDigitalEb", analog_checked, "input: Aska::Pad::SetAnalogAsDigital (sync's FastCriticalSection)", &g_analog.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska3Pad18SetRepeatThresholdEh", threshold_checked, "input: Aska::Pad::SetRepeatThreshold", &g_threshold.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska3Pad17SetRepeatIntervalEh", interval_checked, "input: Aska::Pad::SetRepeatInterval", &g_interval.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska3Pad4FlipEv", flip_checked, "input: Aska::Pad::Flip", &g_flip.orig);
NATIVE_FUNCTION_ORIG("_ZN9Framework4CPad5MergeEv", merge_checked, "input: Framework::CPad::Merge", &g_merge.orig);

}  // namespace soa::native::input
