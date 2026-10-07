// Differential tests of the timing leaves (kernel_timing.cpp).
#include <cmath>
#include <cstring>
#include <vector>

#include "core/cpu.h"
#include "native/common/arm_float.h"
#include "native/common/test.h"
#include "native/kernel/kernel_layout.h"

using namespace soa;
using namespace soa::native::kernel;

namespace {
float rand_float(TestContext& t) {
    switch (t.rand_int(0, 9)) {
    case 0: return 0.0f;
    case 1: return -0.0f;
    case 2: return std::nanf("");
    case 3: return armf::from_bits(0x7f800001u);  // a signalling NaN
    case 4: return -1.0f / (t.rand_int(1, 8));
    case 5: return 1e30f;
    default: return (float)t.rand_int(0, 1000) / 64.0f;
    }
}
}  // namespace

// CTimeElement::Add over trees of 7 nodes (random parents through the guest's AddChild), random
// rates, suspensions, interpositions (started or not) and times near the wrap, NaNs included: the
// guest on one copy, the native on the other, every field equal bit for bit after each Add.
NATIVE_TEST("kernel/time-element-add") {
    constexpr int kNodes = 7;
    alignas(16) static CTimeElement g[kNodes], n[kNodes];
    const float wrap = *reinterpret_cast<const float*>(main_lib()->base + kTimeWrapAbove);
    for (int round = 0; round < 300; round++) {
        for (int i = 0; i < kNodes; i++) t.call("_ZN9Framework12CTimeElementC2Ev", {(u64)&g[i]});
        for (int i = 1; i < kNodes; i++) t.call("_ZN9Framework12CTimeElement8AddChildEPS0_", {(u64)&g[t.rand_int(0, i - 1)], (u64)&g[i]});
        for (int i = 0; i < kNodes; i++) {
            CTimeElement& e = g[i];
            if (t.rand_int(0, 2) == 0) e.m_rate = rand_float(t);
            if (t.rand_int(0, 3) == 0) e.m_suspend = rand_float(t);
            if (t.rand_int(0, 2) == 0) {
                e.m_interposeTime = rand_float(t);
                e.m_interposeRate = rand_float(t);
                e.m_interposeStarted = (u8)t.rand_int(0, 1);
            }
            e.m_time = t.rand_int(0, 4) ? rand_float(t) : wrap * (t.rand_int(0, 1) ? 1.0f : 1.0001f);
        }
        // the copy, its links pointing into itself
        std::memcpy((void*)n, (const void*)g, sizeof g);
        auto map = [&](CTimeElement* p) { return p ? &n[p - g] : nullptr; };
        for (int i = 0; i < kNodes; i++) {
            n[i].base.m_parent = map(g[i].base.m_parent);
            n[i].base.m_nextSibling = map(g[i].base.m_nextSibling);
            n[i].base.m_firstChild = map(g[i].base.m_firstChild);
        }
        for (int step = 0; step < 4; step++) {
            float dt = rand_float(t);
            guest_invoke<void>(t.sym("_ZN9Framework12CTimeElement3AddEf"), (u64)&g[0], dt);
            n[0].Add(dt);
            for (int i = 0; i < kNodes; i++)
                if (std::memcmp((const u8*)&g[i] + 0x28, (const u8*)&n[i] + 0x28, sizeof(CTimeElement) - 0x28)) {
                    t.fail("round %d step %d node %d: time %08x/%08x dt %08x/%08x suspend %08x/%08x interpose %08x/%08x", round, step, i,
                           armf::bits(g[i].m_time), armf::bits(n[i].m_time), armf::bits(g[i].m_dt), armf::bits(n[i].m_dt), armf::bits(g[i].m_suspend),
                           armf::bits(n[i].m_suspend), armf::bits(g[i].m_interposeTime), armf::bits(n[i].m_interposeTime));
                    return;
                }
        }
    }
}

// VSync::GetDt on a private copy of the live VSync with random dt values and scales (NaNs included),
// every clock index and some out of range.
NATIVE_TEST("kernel/vsync-getdt") {
    auto* live = *reinterpret_cast<VSync**>(main_lib()->base + kVaddrGlobalVSync);
    if (!t.expect_eq(live != nullptr, true, "Global::m_pVSync")) return;
    alignas(16) static VSync v;
    std::memcpy((void*)&v, live, sizeof v);
    for (int k = 0; k < 500; k++) {
        for (float& d : v.m_dt) d = rand_float(t);
        v.m_dtScale = rand_float(t);
        s32 clock = t.rand_int(-2, 8);
        float g = guest_invoke<float>(t.sym("_ZNK4Aska5VSync5GetDtEi"), (u64)&v, (u64)(u32)clock);
        float n = v.GetDt(clock);
        if (!t.expect_eq(armf::bits(g), armf::bits(n), "GetDt")) return;
    }
}

// The clock readers: the native's value between two guest calls (the clocks only grow), on a
// private PerformanceCounter (a copy of the live one).
NATIVE_TEST("kernel/clock-readers") {
    for (int k = 0; k < 50; k++) {
        s64 a = (s64)t.call("_ZN4Aska6Global10GetCPUTimeEv", {});
        s64 n = Global::GetCPUTime();
        s64 b = (s64)t.call("_ZN4Aska6Global10GetCPUTimeEv", {});
        if (!t.expect_eq(a <= n && n <= b, true, "GetCPUTime between the guest's")) return;
    }
    auto* live = *reinterpret_cast<PerformanceCounter**>(main_lib()->base + kVaddrGlobalPerformanceCounter);
    if (!t.expect_eq(live != nullptr, true, "Global::m_pPerformanceCounter")) return;
    alignas(16) static PerformanceCounter g1, nn, g2;
    std::memcpy((void*)&g1, live, sizeof g1);
    for (int k = 0; k < 50; k++) {
        s32 i = t.rand_int(0, PerformanceCounter::kNumCounters - 1);
        s64 since = g1.m_marks[i] - t.rand_int(0, 1000000);
        int op = t.rand_int(0, 3);
        std::memcpy((void*)&nn, &g1, sizeof nn);
        std::memcpy((void*)&g2, &g1, sizeof g2);
        const char* sym[4] = {"_ZN4Aska18PerformanceCounter4MarkEi", "_ZN4Aska18PerformanceCounter3SetEi", "_ZN4Aska18PerformanceCounter3SetEil",
                              "_ZN4Aska18PerformanceCounter6AddSetEi"};
        t.call(sym[op], {(u64)&g1, (u64)i, (u64)since});
        switch (op) {
        case 0: nn.Mark(i); break;
        case 1: nn.Set(i); break;
        case 2: nn.Set(i, since); break;
        default: nn.AddSet(i); break;
        }
        t.call(sym[op], {(u64)&g2, (u64)i, (u64)since});
        s64 lo = op == 0 ? g1.m_marks[i] : g1.m_values[i], mid = op == 0 ? nn.m_marks[i] : nn.m_values[i], hi = op == 0 ? g2.m_marks[i] : g2.m_values[i];
        if (!t.expect_eq(lo <= mid && mid <= hi, true, sym[op])) return;
        std::memcpy((void*)&g1, &nn, sizeof g1);
    }
}
