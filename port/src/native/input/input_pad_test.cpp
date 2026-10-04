// Differential tests of input_pad.cpp: Pad's setters and Flip on private pads built by the guest's
// Pad(short) (guest original on one, the native on a twin), CPad::Merge on the game thread over poked
// unit / pad keys (a test hook on Merge itself). In --selftest natives aren't installed: t.call and
// guest_call reach the guest code.
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstring>
#include <limits>
#include <thread>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/test.h"
#include "native/input/input_check.h"
#include "native/input/input_layout.h"

using namespace soa;
using namespace soa::native::input;

namespace {

// A pad built by the guest's Pad(short) (the abstract base: its vtable's ResetStatus is Pad's own).
struct TestPad {
    alignas(16) u8 storage[sizeof(PadDroid)];
    Pad* pad() { return reinterpret_cast<Pad*>(storage); }
    void build(TestContext& t, s16 deadZone) {
        std::memset(storage, 0, sizeof storage);
        t.call("_ZN4Aska3PadC2Es", {(u64)storage, (u64)(u16)deadZone});
    }
    void destroy(TestContext& t) { t.call("_ZN4Aska19FastCriticalSectionD2Ev", {(u64)&pad()->base.m_cs}); }
};

// The two pads' bytes equal, but the semaphore pointer (each points into its own object).
bool same_pad(TestContext& t, Pad* a, Pad* b, const char* what) {
    std::string why = live::diff_bytes((const u8*)a, (const u8*)b, 0, sizeof(Pad), {{kSemPtrOff, kSemPtrOff + 8}});
    if (!why.empty()) {
        t.fail("%s: %s", what, why.c_str());
        return false;
    }
    u64 ra = a->base.m_cs.m_sem.m_pSem - (u64)a, rb = b->base.m_cs.m_sem.m_pSem - (u64)b;
    return t.expect_eq(ra, rb, "semaphore pointer (relative)");
}

}  // namespace

NATIVE_TEST("input/pad-setters") {
    static TestPad ga, na;
    ga.build(t, 0x80);
    na.build(t, 0x80);
    Pad* g = ga.pad();
    Pad* n = na.pad();
    same_pad(t, g, n, "after construction");
    const u64 values[] = {0, 1, 2, 3, 0x7f, 0x80, 0xfe, 0xff, 0x101, 0x1ff};
    for (u64 v : values) {
        t.call("_ZN4Aska3Pad18SetAnalogAsDigitalEb", {(u64)g, v});
        n->SetAnalogAsDigital((u8)v);
        same_pad(t, g, n, "SetAnalogAsDigital");
        t.call("_ZN4Aska3Pad18SetRepeatThresholdEh", {(u64)g, v});
        n->SetRepeatThreshold((u8)v);
        same_pad(t, g, n, "SetRepeatThreshold");
        t.call("_ZN4Aska3Pad17SetRepeatIntervalEh", {(u64)g, v});
        n->SetRepeatInterval((u8)v);
        same_pad(t, g, n, "SetRepeatInterval");
    }
    for (int i = 0; i < 200; i++) {
        u64 v = t.rand_u64();
        switch (t.rand_int(0, 2)) {
        case 0:
            t.call("_ZN4Aska3Pad18SetAnalogAsDigitalEb", {(u64)g, v});
            n->SetAnalogAsDigital((u8)v);
            break;
        case 1:
            t.call("_ZN4Aska3Pad18SetRepeatThresholdEh", {(u64)g, v});
            n->SetRepeatThreshold((u8)v);
            break;
        default:
            t.call("_ZN4Aska3Pad17SetRepeatIntervalEh", {(u64)g, v});
            n->SetRepeatInterval((u8)v);
            break;
        }
        if (!same_pad(t, g, n, "random setter")) break;
    }
    t.expect_eq(n->base.m_cs.m_lock, FastCriticalSection::kFree, "lock released");
    t.expect_eq(n->base.m_cs.m_waiters, FastCriticalSection::kWaiterBias, "no waiters");
    ga.destroy(t);
    na.destroy(t);
}

// Flip over random double-buffered keys (both fronts), with Pad::ResetStatus (vtable slot 10, the
// guest's) clearing the front before the swap.
NATIVE_TEST("input/pad-flip") {
    static TestPad ga, na;
    ga.build(t, 0x40);
    na.build(t, 0x40);
    Pad* g = ga.pad();
    Pad* n = na.pad();
    for (int i = 0; i < 64; i++) {
        auto keys = t.rand_bytes(sizeof g->m_keys);
        std::memcpy(g->m_keys, keys.data(), keys.size());
        std::memcpy(n->m_keys, keys.data(), keys.size());
        g->m_front = n->m_front = t.rand_int(0, 1);
        g->m_repeatCounter = n->m_repeatCounter = (s16)t.rand_u64();
        t.call("_ZN4Aska3Pad4FlipEv", {(u64)g});
        n->Flip();
        if (!same_pad(t, g, n, "Flip")) break;
        // twice in a row (the front's m_now carried over to the new back buffer)
        t.call("_ZN4Aska3Pad4FlipEv", {(u64)g});
        n->Flip();
        if (!same_pad(t, g, n, "Flip twice")) break;
    }
    ga.destroy(t);
    na.destroy(t);
}

// ---- CPad::Merge on the game thread ----

namespace {

u64 g_merge_orig = 0;
std::atomic<int> g_merge_request{0};  // 1: the test asks for a run in the next Merge
std::atomic<int> g_merge_done{0};
int g_merge_trials = 0, g_merge_bad = 0, g_merge_units = 0;
bool g_merge_pad = false;
std::string g_merge_first;

void fill_keys(std::mt19937_64& rng, PadKeys& k, int trial) {
    k.m_now = (u16)rng();
    k.m_before = (u16)rng();
    k.m_stock = (u16)rng();
    k.m_single = (u16)rng();
    k.m_release = (u16)rng();
    k.m_repeat = (u16)rng();
    k.m_repeatEach = (u16)rng();
    const s16 edge[] = {0, 1, -1, 0x7fff, (s16)0x8000, 0x100, -0x100};
    s16* a[] = {&k.m_lx, &k.m_ly, &k.m_rx, &k.m_ry};
    for (s16* p : a) *p = (trial % 3 == 0) ? edge[rng() % 7] : (s16)rng();
    k.m_lt = (u8)rng();
    k.m_rt = (u8)rng();
    const float fedge[] = {0.0f, -0.0f, 1.0f, -1.0f, 0.5f, -0.75f, std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::infinity()};
    float* f[] = {&k.m_lxf, &k.m_lyf, &k.m_rxf, &k.m_ryf};
    for (float* p : f) *p = (trial % 2 == 0) ? fedge[rng() % 8] : (float)((s64)(rng() % 20001) - 10000) / 10000.0f;
}

// Runs on the game thread inside CPad::Merge: pokes the singleton's units and the active pad's front
// keys, merges them into two private copies of `this` (the guest original, the native), compares,
// puts the keys back and runs the real Merge.
void merge_hook(Cpu& c) {
    auto* self = reinterpret_cast<CPad*>(c.x(0));
    if (g_merge_request.exchange(0) == 1) {
        CPad* inst = CPad::Instance();
        auto* active = reinterpret_cast<Pad*>(PeripheralManager::GetActivePad());
        u32 units = inst && inst->m_units ? inst->m_numUnits : 0;
        if (units > 4) units = 4;
        PadKeys saved_units[4], saved_pad{};
        for (u32 i = 0; i < units; i++) saved_units[i] = inst->m_units[i].m_keys;
        if (active) saved_pad = active->m_keys[active->m_front];
        g_merge_units = (int)units;
        g_merge_pad = active != nullptr;
        std::mt19937_64 rng(0x5eed1234);
        alignas(16) static u8 ga[sizeof(CPad)], na[sizeof(CPad)];
        for (int trial = 0; trial < 64; trial++) {
            for (u32 i = 0; i < units; i++) fill_keys(rng, inst->m_units[i].m_keys, trial);
            if (active) fill_keys(rng, active->m_keys[active->m_front], trial + 1);
            std::memcpy(ga, self, sizeof ga);
            std::memset(ga + offsetof(CPad, m_merged), 0x5a, sizeof(CPadMerged));
            std::memcpy(na, ga, sizeof na);
            guest_call(g_merge_orig, {(u64)ga});
            reinterpret_cast<CPad*>(na)->Merge();
            g_merge_trials++;
            std::string why = live::diff_bytes(na, ga, 0, sizeof(CPad));
            if (!why.empty()) {
                if (!g_merge_bad++) g_merge_first = why + " (trial " + std::to_string(trial) + ")";
            }
        }
        for (u32 i = 0; i < units; i++) inst->m_units[i].m_keys = saved_units[i];
        if (active) active->m_keys[active->m_front] = saved_pad;
        g_merge_done = 1;
    }
    guest_call(g_merge_orig, {(u64)self});
}

}  // namespace

NATIVE_TEST_HOOK("_ZN9Framework4CPad5MergeEv", merge_hook, &g_merge_orig);

NATIVE_TEST("input/pad-merge") {
    g_merge_done = 0;
    g_merge_request = 1;
    for (int i = 0; i < 300 && !g_merge_done; i++) std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if (!t.expect_eq((int)g_merge_done, 1, "CPad::Merge ran on the game thread within 3 s")) {
        g_merge_request = 0;
        return;
    }
    t.expect_eq(g_merge_units >= 1, true, "the CPad singleton has units");
    t.expect_eq(g_merge_pad, true, "an active pad");
    t.expect_eq(g_merge_trials, 64, "trials");
    if (g_merge_bad) t.fail("Merge: %d of %d trials differ, first %s", g_merge_bad, g_merge_trials, g_merge_first.c_str());
}
