// The 3.7.0 platform's HLE additions (platform370/README.md), registered by platform370::install
// through the runtime's extension point (hle_add_registrar); imports are bound when the library is
// loaded.
//
// 1. Imports of work/libSOA-3.7.0.so that the runtime's HLE (built for the offline build's import
//    list) lacks. The import lists (readelf --dyn-syms -W, UND) of 3.7.0 and the offline build
//    differ by one symbol: 3.7.0 imports fmod (libm). Everything else 3.7.0 imports, the offline
//    build imports too.
// 2. The device clock (Config::device_clock), an option for tests (soa-emu --device-clock): the wall
//    clock the guest reads (time, gettimeofday, clock_gettime and syscall(clock_gettime) on the
//    CLOCK_REALTIME clocks) runs at a fixed offset from the host's. The offset is 0 by default:
//    the client runs on the real date, since its service-end check (master_global.
//    service_stop_day against CTimeUtility::NowTimeTrue) is patched out (patch_370.cpp). The
//    monotonic clocks are untouched.
// 3. Local time, daylight saving included (Config::local_time; docs/client-changes.md "Local time:
//    daylight saving"): the guest's mktime reads every wall time as the local time in force then,
//    whatever tm_isdst the caller set (soa::mktime_local's rule, common/include/soa/local_time.h, the
//    one the server uses). The client sets tm_isdst = 0 (CTimeUtility::str2time_t, the copy of it
//    inlined in CHomeUtility::GetHomeParameter, CPassPurchaseHistoryDialog::CreateHistoryList) or
//    copies it from localtime of another instant (CTimeUtility::CompDay / TodayStart,
//    CUIUtility::IsGachaSaleDayOnImplementation), so in a zone with daylight saving it read every
//    time string as standard time, an hour late in summer. Off (--no-dst-fix): mktime as bionic's.
#include <math.h>
#include <sys/time.h>
#include <time.h>

#include <atomic>
#include <cstring>

#include <soa/local_time.h>

#include "soaruntime/core/hle.h"
#include "soaruntime/core/log.h"
#include "internal.h"

namespace soa::platform370::detail {
namespace {

using D2 = double (*)(double, double);

std::atomic<s64> g_offset{0};  // device clock - host clock, seconds
std::atomic<bool> g_local_time{true};

HostFn g_time, g_gettimeofday, g_clock_gettime, g_syscall, g_mktime;

bool is_realtime(u64 clk) {
    // Linux / bionic clock ids: CLOCK_REALTIME 0, CLOCK_REALTIME_COARSE 5, CLOCK_REALTIME_ALARM 8
    return clk == 0 || clk == 5 || clk == 8;
}

void th_time(Cpu& c) {
    u64 out = c.x(0);
    g_time(c);
    s64 off = g_offset.load(std::memory_order_relaxed);
    if (!off || (s64)c.x(0) == -1) return;
    s64 t = (s64)c.x(0) + off;
    c.set_x(0, (u64)t);
    if (out) *(s64*)out = t;
}

// (the guest's timeval / timespec start with a 64-bit tv_sec: written as such, not through the
// host's struct, whose tv_sec is 32-bit in a Windows timeval)
void th_gettimeofday(Cpu& c) {
    u64 tv = c.x(0);
    g_gettimeofday(c);
    if ((s32)c.x(0) == 0 && tv) *(s64*)tv += g_offset.load(std::memory_order_relaxed);
}

void th_clock_gettime(Cpu& c) {
    u64 clk = c.x(0), ts = c.x(1);
    g_clock_gettime(c);
    if ((s32)c.x(0) == 0 && ts && is_realtime(clk)) *(s64*)ts += g_offset.load(std::memory_order_relaxed);
}

void th_syscall(Cpu& c) {
    u64 nr = c.x(0), clk = c.x(1), ts = c.x(2);
    g_syscall(c);
    if (nr == 113 /* arm64 clock_gettime */ && (s64)c.x(0) == 0 && ts && is_realtime(clk))
        *(s64*)ts += g_offset.load(std::memory_order_relaxed);
}

// mktime(struct tm*), bionic's struct tm (56 bytes; tm_isdst at +0x20). The runtime's mktime (glibc's
// on the guest's struct; msvcrt's _mktime64 through a copy on Windows) runs for both readings
// (tm_isdst 0, 1) on the caller's fields, then once more for the one soa::pick_local_reading takes,
// so the struct comes back normalised as by that call.
constexpr size_t kTmSize = 56, kTmIsdst = 0x20;
void th_mktime(Cpu& c) {
    u64 p = c.x(0);
    if (!p || !g_local_time.load(std::memory_order_relaxed)) return g_mktime(c);
    unsigned char in[kTmSize];
    std::memcpy(in, (const void*)p, kTmSize);
    auto reading = [&](s32 isdst, s32* isdst_out) {
        std::memcpy((void*)p, in, kTmSize);
        std::memcpy((void*)(p + kTmIsdst), &isdst, 4);
        c.set_x(0, p);
        g_mktime(c);
        std::memcpy(isdst_out, (const void*)(p + kTmIsdst), 4);
        return (s64)c.x(0);
    };
    s32 d0, d1;
    s64 t0 = reading(0, &d0);
    s64 t1 = reading(1, &d1);
    if (soa::pick_local_reading(t0, d0, t1, d1) == 0) reading(0, &d0);
}

}  // namespace

void install_imports(Hle& h) {
    // bionic's fmod and glibc's are both the exact IEEE remainder of truncation: same results.
    HLE_WRAP_T(h, "fmod", D2, ::fmod);
}

void install_clock(Hle& h) {
    g_time = h.override_fn("time", th_time);
    g_gettimeofday = h.override_fn("gettimeofday", th_gettimeofday);
    g_clock_gettime = h.override_fn("clock_gettime", th_clock_gettime);
    g_syscall = h.override_fn("syscall", th_syscall);
    g_mktime = h.override_fn("mktime", th_mktime);
    if (!g_time || !g_gettimeofday || !g_clock_gettime || !g_syscall || !g_mktime) fatal("platform370: the runtime's time imports are missing");
}

void set_device_clock(std::int64_t offset_seconds) { g_offset = offset_seconds; }

}  // namespace soa::platform370::detail

namespace soa::platform370 {

void set_local_time(bool on) { detail::g_local_time = on; }
bool local_time() { return detail::g_local_time.load(); }

}  // namespace soa::platform370
