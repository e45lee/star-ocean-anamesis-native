// The live check of the sync natives: the family switch, counters, shadows (sync_check.h).
#include "native/sync/sync_check.h"

#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <vector>

#include "core/log.h"
#include "native/common/live_check.h"

namespace soa::native::sync {

namespace {
// The family: --live-check sync switches it on and sets every= / budget= / only= / out=. Its
// record / replay machinery isn't used (sync_check.h); its stats are the totals.
live::Family g_family("sync", 16, false);

std::vector<CheckedFn*>& checked_fns() {
    static std::vector<CheckedFn*> v;
    return v;
}
std::mutex g_fns_m;
thread_local bool t_in_check = false;

void summary_file() {
    if (g_family.out_path.empty()) return;
    FILE* f = fopen(g_family.out_path.c_str(), "w");
    if (!f) return;
    auto& s = g_family.stats;
    fprintf(f, "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races\n", (unsigned long long)s.checks.load(), (unsigned long long)s.ok.load(),
            (unsigned long long)s.bad.load(), (unsigned long long)s.skipped.load(), (unsigned long long)s.races.load());
    std::lock_guard lk(g_fns_m);
    for (CheckedFn* p : checked_fns()) {
        if (!p->checks) continue;
        fprintf(f, "%-60.60s checks %6llu ok %6llu bad %llu skipped %llu races %llu\n", p->sym, (unsigned long long)p->checks.load(), (unsigned long long)p->ok.load(),
                (unsigned long long)p->bad.load(), (unsigned long long)p->skipped.load(), (unsigned long long)p->races.load());
    }
    fclose(f);
}

void totals() {
    auto& s = g_family.stats;
    u64 n = s.checks;
    if (n % 1000) {
        // (the counts file also every 10 s: a session ends with a kill)
        static std::atomic<s64> last{0};
        static std::mutex m;
        s64 now = (s64)time(nullptr), l = last.load(std::memory_order_relaxed);
        if (g_family.out_path.empty() || now - l < 10 || !last.compare_exchange_strong(l, now)) return;
        std::lock_guard lk(m);
        summary_file();
        return;
    }
    summary_file();
    LOGI(g_family.log_tag.c_str(), "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races", (unsigned long long)n, (unsigned long long)s.ok.load(),
         (unsigned long long)s.bad.load(), (unsigned long long)s.skipped.load(), (unsigned long long)s.races.load());
}
}  // namespace

thread_local Observation* t_obs = nullptr;

CheckedFn::CheckedFn(const char* s) : sym(s) {
    std::lock_guard lk(g_fns_m);
    checked_fns().push_back(this);
}

bool check_due(CheckedFn& f) {
    if (__builtin_expect(!g_family.on.load(std::memory_order_relaxed), 1)) return false;
    if (t_in_check || live::t_busy || !f.orig || !g_family.only.match(f.sym)) return false;
    if (g_family.budget && f.checks >= (u64)g_family.budget) return false;
    return f.calls.fetch_add(1, std::memory_order_relaxed) % (u64)g_family.every == 0;
}

CheckScope::CheckScope() { t_in_check = live::t_busy = true; }
CheckScope::~CheckScope() { t_in_check = live::t_busy = false; }

void check_result(CheckedFn& f, Outcome o, const std::string& why) {
    auto& s = g_family.stats;
    f.checks++;
    s.checks++;
    switch (o) {
    case Outcome::Ok:
        f.ok++, s.ok++;
        break;
    case Outcome::Mismatch:
        f.bad++, s.bad++;
        if (f.bad <= 5) LOGE(g_family.log_tag.c_str(), "MISMATCH %s: %s", f.sym, why.c_str());
        break;
    case Outcome::Skipped:
        f.skipped++, s.skipped++;
        if (f.skipped <= 2 && !why.empty()) LOGI(g_family.log_tag.c_str(), "skipped %s: %s", f.sym, why.c_str());
        break;
    case Outcome::Race:
        f.races++, s.races++;
        break;
    }
    totals();
}

u8* shadow_buffer(int slot) {
    constexpr size_t kSize = 0x100;
    static_assert(sizeof(CMutex) <= kSize && sizeof(Event) <= kSize);
    alignas(16) static thread_local u8 buf[2][kSize];
    std::memset(buf[slot], 0, kSize);
    return buf[slot];
}

std::string diff_bytes(const u8* a, const u8* b, size_t from, size_t to, std::initializer_list<std::pair<size_t, size_t>> skip) {
    for (size_t i = from; i < to; i++) {
        bool skipped = false;
        for (auto& [lo, hi] : skip)
            if (i >= lo && i < hi) skipped = true;
        if (skipped || a[i] == b[i]) continue;
        char m[96];
        snprintf(m, sizeof m, "+0x%zx: native %02x guest %02x", i, a[i], b[i]);
        return m;
    }
    return {};
}

void check_getter(Cpu& c, CheckedFn& f, HostFn native, u64 mask) {
    CheckScope scope;
    u64 x[8];
    for (int i = 0; i < 8; i++) x[i] = c.x(i);
    native(c);
    u64 got = c.x(0) & mask;
    u64 want = guest_call(f.orig, {x[0], x[1], x[2], x[3]}) & mask;
    if (got == want) return check_result(f, Outcome::Ok);
    // Rerun both: a value another thread changed in between doesn't reproduce.
    for (int i = 0; i < 8; i++) c.set_x(i, x[i]);
    native(c);
    u64 got2 = c.x(0) & mask;
    u64 want2 = guest_call(f.orig, {x[0], x[1], x[2], x[3]}) & mask;
    c.set_x(0, got2);
    if (got2 == want2) return check_result(f, Outcome::Race);
    char m[96];
    snprintf(m, sizeof m, "this %#" PRIx64 ": native %#" PRIx64 " guest %#" PRIx64, x[0], got2, want2);
    check_result(f, Outcome::Mismatch, m);
}

}  // namespace soa::native::sync
