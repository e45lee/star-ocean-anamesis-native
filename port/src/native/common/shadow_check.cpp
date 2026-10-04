// Shadow-replay live checks: the switch, counters and comparison helpers (shadow_check.h).
#include "native/common/shadow_check.h"

#include <cinttypes>
#include <cstdlib>
#include <ctime>
#include <map>
#include <mutex>
#include <vector>

#include "core/log.h"

namespace soa::live {

namespace {
std::mutex g_fns_m;
std::map<const ShadowFamily*, std::vector<CheckedFn*>>& checked_fns() {
    static std::map<const ShadowFamily*, std::vector<CheckedFn*>> m;
    return m;
}
thread_local bool t_in_check = false;

void totals(ShadowFamily& sf) {
    auto& s = sf.fam.stats;
    u64 n = s.checks;
    if (n % 1000) {
        // (the counts file also every 10 s: a session ends with a kill)
        static std::atomic<s64> last{0};
        static std::mutex m;
        s64 now = (s64)time(nullptr), l = last.load(std::memory_order_relaxed);
        if (sf.fam.out_path.empty() || now - l < 10 || !last.compare_exchange_strong(l, now)) return;
        std::lock_guard lk(m);
        sf.summary_file();
        return;
    }
    sf.summary_file();
    LOGI(sf.fam.log_tag.c_str(), "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races", (unsigned long long)n, (unsigned long long)s.ok.load(),
         (unsigned long long)s.bad.load(), (unsigned long long)s.skipped.load(), (unsigned long long)s.races.load());
}
}  // namespace

ShadowFamily::ShadowFamily(const char* tag, int every) : fam(tag, every, false) {}

void ShadowFamily::summary_file() {
    if (fam.out_path.empty()) return;
    FILE* f = fopen(fam.out_path.c_str(), "w");
    if (!f) return;
    auto& s = fam.stats;
    fprintf(f, "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races\n", (unsigned long long)s.checks.load(), (unsigned long long)s.ok.load(),
            (unsigned long long)s.bad.load(), (unsigned long long)s.skipped.load(), (unsigned long long)s.races.load());
    std::lock_guard lk(g_fns_m);
    for (CheckedFn* p : checked_fns()[this]) {
        if (!p->checks) continue;
        fprintf(f, "%-60.60s checks %6llu ok %6llu bad %llu skipped %llu races %llu\n", p->sym, (unsigned long long)p->checks.load(), (unsigned long long)p->ok.load(),
                (unsigned long long)p->bad.load(), (unsigned long long)p->skipped.load(), (unsigned long long)p->races.load());
    }
    fclose(f);
}

CheckedFn::CheckedFn(ShadowFamily& f, const char* s) : family(&f), sym(s) {
    std::lock_guard lk(g_fns_m);
    checked_fns()[&f].push_back(this);
}

bool check_due(CheckedFn& f) {
    Family& fam = f.family->fam;
    if (__builtin_expect(!fam.on.load(std::memory_order_relaxed), 1)) return false;
    if (t_in_check || t_busy || !f.orig || !fam.only.match(f.sym)) return false;
    if (fam.budget && f.checks >= (u64)fam.budget) return false;
    return f.calls.fetch_add(1, std::memory_order_relaxed) % (u64)fam.every == 0;
}

CheckScope::CheckScope() { t_in_check = t_busy = true; }
CheckScope::~CheckScope() { t_in_check = t_busy = false; }
bool in_shadow_check() { return t_in_check; }

void check_result(CheckedFn& f, Outcome o, const std::string& why) {
    Family& fam = f.family->fam;
    auto& s = fam.stats;
    f.checks++;
    s.checks++;
    switch (o) {
    case Outcome::Ok:
        f.ok++, s.ok++;
        break;
    case Outcome::Mismatch:
        f.bad++, s.bad++;
        if (f.bad <= 5) LOGE(fam.log_tag.c_str(), "MISMATCH %s: %s", f.sym, why.c_str());
        break;
    case Outcome::Skipped:
        f.skipped++, s.skipped++;
        if (f.skipped <= 2 && !why.empty()) LOGI(fam.log_tag.c_str(), "skipped %s: %s", f.sym, why.c_str());
        break;
    case Outcome::Race:
        f.races++, s.races++;
        break;
    }
    totals(*f.family);
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

}  // namespace soa::live
