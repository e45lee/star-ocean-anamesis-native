// The kernel's timing leaves (port/decomp/kernel/timing.c, global.c): Aska::PerformanceCounter's
// Mark / Set / AddSet, Framework::CTimeElement::Add, Aska::VSync::GetDt, Aska::Global::GetCPUTime.
//
// Clocks: the guest asks bionic's clock_gettime, which the HLE answers with the host's (the same id
// on Linux; on Windows the ids mapped as runtime/src/hle/libc_win32.cpp's clock_gettime_guest does:
// 0 / 5 realtime, 2 process, 3 thread, the rest monotonic). The natives read the same clocks.
//
// Live checks (--live-check kernel): what reads a clock can't equal the guest bit for bit, so it is
// bracketed instead: the guest original runs on a shadow copy just before and just after the native,
// and the native's value must lie between the two (counters and marks only grow). CTimeElement::Add
// runs on a whole time tree: the native, then the guest on the same nodes put back as they were;
// every node reached must end the same. VSync::GetDt is a getter (its float result compared).
#include <cinttypes>
#include <cmath>
#include <cstring>
#include <ctime>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/arm_float.h"
#include "native/common/native_method.h"
#include "native/kernel/kernel_check.h"
#include "native/kernel/kernel_layout.h"

namespace soa::native::kernel {

namespace {

// bionic's clock_gettime(id) as the HLE answers it: {sec, nsec}.
void guest_clock(int id, s64& sec, s64& nsec) {
#ifdef _WIN32
    clockid_t h = id == 0 || id == 5 ? CLOCK_REALTIME : id == 2 ? CLOCK_PROCESS_CPUTIME_ID : id == 3 ? CLOCK_THREAD_CPUTIME_ID : CLOCK_MONOTONIC;
#else
    clockid_t h = (clockid_t)id;
#endif
    timespec t{};
    clock_gettime(h, &t);
    sec = (s64)t.tv_sec;
    nsec = (s64)t.tv_nsec;
}
constexpr int kClockMonotonic = 1, kClockBoottime = 7;

s64 monotonic_ns() {
    s64 s, ns;
    guest_clock(kClockMonotonic, s, ns);
    return ns + s * 1000000000;
}

// FCVTZS (double -> int32): toward zero, saturating, NaN -> 0.
s32 cvtzs(double d) {
    if (std::isnan(d)) return 0;
    if (d >= 2147483648.0) return INT32_MAX;
    if (d <= -2147483648.0) return INT32_MIN;
    return (s32)d;
}

}  // namespace

// ---- Aska::PerformanceCounter ----

void PerformanceCounter::Mark(s32 i) { m_marks[i] = monotonic_ns(); }

void PerformanceCounter::Set(s32 i) { m_values[i] = cvtzs(m_scale * (double)(monotonic_ns() - m_marks[i])); }

void PerformanceCounter::Set(s32 i, s64 since) {
    s64 s, ns;
    guest_clock(kClockMonotonic, s, ns);
    m_values[i] = cvtzs(m_scale * (double)((ns - since) + s * 1000000000));
}

void PerformanceCounter::AddSet(s32 i) { m_values[i] += cvtzs(m_scale * (double)(monotonic_ns() - m_marks[i])); }

// ---- Aska::Global ----

// Milliseconds of CLOCK_BOOTTIME (id 7; the layout header's first guess, the thread CPU time, was wrong).
s64 Global::GetCPUTime() {
    s64 s, ns;
    guest_clock(kClockBoottime, s, ns);
    return ns / 1000000 + s * 1000;
}

// ---- Aska::VSync ----

float VSync::GetDt(s32 clock) const {
    if ((u32)clock >= (u32)kNumClocks) return 0.0f;
    return armf::mul(m_dt[clock], m_dtScale);
}

// ---- Framework::CTimeElement ----

// The node's dt scaled by its rate (by the interpose rate while interposing; 0 while suspended,
// the suspension counting down meanwhile), added to its time (wrapped past the guest's limit); then
// its next sibling with the same dt (recursively) and its first child with the scaled one. Quirks
// kept: a suspension counts down by dt times the *interpose time* when one is set (not the rate);
// an interposition ending clears it down the first-child chain only. NaN comparisons follow the
// guest's condition codes (b.le / b.hi): a NaN suspension or interpose time counts as not set.
void CTimeElement::Add(float dt_in) {
    static const float kWrapAbove = *reinterpret_cast<const float*>(main_lib()->base + kTimeWrapAbove);  // (.rodata)
    static const float kWrapBy = *reinterpret_cast<const float*>(main_lib()->base + kTimeWrapBy);
    using armf::F;
    CTimeElement* e = this;
    F dt(dt_in);
    while (e) {
        F scaled;
        F suspend(e->m_suspend);
        if (suspend > F(0.0f)) {
            F it(e->m_interposeTime);
            F rate(it > F(0.0f) ? e->m_interposeTime : e->m_rate);
            e->m_suspend = (suspend - dt * rate).v;
            scaled = dt * F(0.0f);
        } else {
            F it(e->m_interposeTime);
            bool interposing = it > F(0.0f);
            F rate(interposing ? e->m_interposeRate : e->m_rate);
            e->m_suspend = 0.0f;
            scaled = dt * rate;
            if (interposing) {
                if (!e->m_interposeStarted) {
                    e->m_interposeStarted = 1;
                } else {
                    F left = it - scaled;
                    e->m_interposeTime = left.v;
                    if (!(left > F(0.0f)) && !std::isnan(left.v)) {  // (b.hi: a NaN keeps interposing)
                        for (CTimeElement* c = e; c; c = c->base.m_firstChild) {
                            c->m_interposeTime = 0.0f;
                            c->m_interposeRate = 0.0f;
                            c->m_interposeStarted = 0;
                        }
                    }
                }
            }
        }
        F time(e->m_time);
        if (time > F(kWrapAbove)) {
            time = time + F(kWrapBy);
            e->m_time = time.v;
        }
        F sum = scaled + time;
        e->m_time = sum.v;
        e->m_dt = (sum - time).v;
        if (e->base.m_nextSibling) e->base.m_nextSibling->Add(dt.v);
        e = e->base.m_firstChild;
        dt = scaled;
    }
}

namespace {

// ---- live checks ----

CheckedFn g_mark("_ZN4Aska18PerformanceCounter4MarkEi"), g_set("_ZN4Aska18PerformanceCounter3SetEi"), g_set2("_ZN4Aska18PerformanceCounter3SetEil"),
    g_addset("_ZN4Aska18PerformanceCounter6AddSetEi"), g_cpu("_ZN4Aska6Global10GetCPUTimeEv"), g_getdt("_ZNK4Aska5VSync5GetDtEi"),
    g_add("_ZN9Framework12CTimeElement3AddEf");

// Mark / Set / AddSet: the guest on a shadow copy before and after the native; the native's mark /
// value must lie between the guest's two.
template <auto M>
void counter_hook(Cpu& c, CheckedFn& f, bool mark) {
    if (!live::check_due(f)) return wrap_method<M>()(c);
    live::CheckScope scope;
    auto* pc = reinterpret_cast<PerformanceCounter*>(c.x(0));
    s32 i = (s32)c.x(1);
    u64 x2 = c.x(2);
    if (i < 0 || i >= PerformanceCounter::kNumCounters) {
        wrap_method<M>()(c);
        return check_result(f, live::Outcome::Skipped, "index out of range");
    }
    struct Shadows {
        alignas(16) u8 b[2][sizeof(PerformanceCounter)];
    };
    auto& sh = live::thread_scratch<Shadows>().b;  // (heap, not static TLS)
    std::memcpy(sh[0], pc, sizeof(PerformanceCounter));
    guest_call(f.orig, {(u64)sh[0], (u64)(u32)i, x2});
    std::memcpy(sh[1], pc, sizeof(PerformanceCounter));
    wrap_method<M>()(c);
    guest_call(f.orig, {(u64)sh[1], (u64)(u32)i, x2});
    auto* lo = reinterpret_cast<PerformanceCounter*>(sh[0]);
    auto* hi = reinterpret_cast<PerformanceCounter*>(sh[1]);
    s64 n = mark ? pc->m_marks[i] : pc->m_values[i];
    s64 a = mark ? lo->m_marks[i] : lo->m_values[i], b = mark ? hi->m_marks[i] : hi->m_values[i];
    if ((a <= n && n <= b) || (b <= n && n <= a)) return check_result(f, live::Outcome::Ok);
    char m[128];
    snprintf(m, sizeof m, "[%d]: native %" PRId64 " outside the guest's %" PRId64 " .. %" PRId64, i, n, a, b);
    check_result(f, live::Outcome::Mismatch, m);
}
void mark_hook(Cpu& c) { counter_hook<&PerformanceCounter::Mark>(c, g_mark, true); }
void set_hook(Cpu& c) { counter_hook<static_cast<void (PerformanceCounter::*)(s32)>(&PerformanceCounter::Set)>(c, g_set, false); }
void set2_hook(Cpu& c) { counter_hook<static_cast<void (PerformanceCounter::*)(s32, s64)>(&PerformanceCounter::Set)>(c, g_set2, false); }
void addset_hook(Cpu& c) { counter_hook<&PerformanceCounter::AddSet>(c, g_addset, false); }

void cpu_hook(Cpu& c) {
    if (!live::check_due(g_cpu)) return c.set_x(0, (u64)Global::GetCPUTime());
    live::CheckScope scope;
    s64 a = (s64)guest_call(g_cpu.orig, std::initializer_list<u64>{});
    s64 n = Global::GetCPUTime();
    s64 b = (s64)guest_call(g_cpu.orig, std::initializer_list<u64>{});
    c.set_x(0, (u64)n);
    if (a <= n && n <= b) return check_result(g_cpu, live::Outcome::Ok);
    char m[96];
    snprintf(m, sizeof m, "native %" PRId64 " outside the guest's %" PRId64 " .. %" PRId64, n, a, b);
    check_result(g_cpu, live::Outcome::Mismatch, m);
}

void getdt_hook(Cpu& c) {
    if (!live::check_due(g_getdt)) return wrap_method<&VSync::GetDt>()(c);
    live::CheckScope scope;
    u64 x0 = c.x(0), x1 = c.x(1);
    wrap_method<&VSync::GetDt>()(c);
    u32 n = (u32)c.v(0).lo;
    GuestArgs ga;
    ga.i(x0).i(x1);
    u32 g = (u32)guest_call(g_getdt.orig, ga).v0.lo;
    if (n == g) return check_result(g_getdt, live::Outcome::Ok);
    // (another thread's UpdateDt in between: rerun both)
    wrap_method<&VSync::GetDt>()(c);
    u32 n2 = (u32)c.v(0).lo;
    u32 g2 = (u32)guest_call(g_getdt.orig, ga).v0.lo;
    if (n2 == g2) return check_result(g_getdt, live::Outcome::Race);
    char m[96];
    snprintf(m, sizeof m, "clock %u: native %08x guest %08x", (u32)x1, n2, g2);
    check_result(g_getdt, live::Outcome::Mismatch, m);
}

// The nodes Add(dt) reaches from `e`: e, its siblings (recursively) and its first children.
void collect(CTimeElement* e, std::vector<CTimeElement*>& out) {
    for (; e && out.size() < 4096; e = e->base.m_firstChild) {
        out.push_back(e);
        if (e->base.m_nextSibling) collect(e->base.m_nextSibling, out);
    }
}

void add_hook(Cpu& c) {
    if (!live::check_due(g_add)) return wrap_method<&CTimeElement::Add>()(c);
    live::CheckScope scope;
    auto* e = reinterpret_cast<CTimeElement*>(c.x(0));
    std::vector<CTimeElement*> nodes;
    collect(e, nodes);
    std::vector<CTimeElement> pre(nodes.size()), native(nodes.size());
    for (size_t k = 0; k < nodes.size(); k++) std::memcpy((void*)&pre[k], nodes[k], sizeof(CTimeElement));
    GuestArgs ga;
    ga.i(c.x(0)).f(c.s(0));
    wrap_method<&CTimeElement::Add>()(c);
    for (size_t k = 0; k < nodes.size(); k++) {
        std::memcpy((void*)&native[k], nodes[k], sizeof(CTimeElement));
        std::memcpy((void*)nodes[k], &pre[k], sizeof(CTimeElement));
    }
    guest_call(g_add.orig, ga);
    for (size_t k = 0; k < nodes.size(); k++) {
        std::string why = live::diff_bytes((const u8*)&native[k], (const u8*)nodes[k], 0, sizeof(CTimeElement));
        if (!why.empty()) return check_result(g_add, live::Outcome::Mismatch, "node " + std::to_string(k) + " " + why);
    }
    check_result(g_add, live::Outcome::Ok);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska18PerformanceCounter4MarkEi", mark_hook, "kernel: PerformanceCounter::Mark", &g_mark.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska18PerformanceCounter3SetEi", set_hook, "kernel: PerformanceCounter::Set", &g_set.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska18PerformanceCounter3SetEil", set2_hook, "kernel: PerformanceCounter::Set(int, long)", &g_set2.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska18PerformanceCounter6AddSetEi", addset_hook, "kernel: PerformanceCounter::AddSet", &g_addset.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska6Global10GetCPUTimeEv", cpu_hook, "kernel: Global::GetCPUTime (CLOCK_BOOTTIME ms)", &g_cpu.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska5VSync5GetDtEi", getdt_hook, "kernel: VSync::GetDt", &g_getdt.orig);
NATIVE_FUNCTION_ORIG("_ZN9Framework12CTimeElement3AddEf", add_hook, "kernel: CTimeElement::Add", &g_add.orig);

}  // namespace soa::native::kernel
