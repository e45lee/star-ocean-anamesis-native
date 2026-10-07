// Shadow checks: the family switch, counters, the getter check (shadow_check.h).
#include "native/common/shadow_check.h"

#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <ctime>

#include "core/log.h"

namespace soa::live {

namespace {
thread_local bool t_in_check = false;
}  // namespace

ShadowFamily::ShadowFamily(const char* tag_, int every_) : Family(tag_, every_) {}

void ShadowFamily::add_fn(ShadowFn* f) {
    std::lock_guard lk(m_);
    fns_.push_back(f);
}

void ShadowFamily::write_counts() {
    if (out_path.empty()) return;
    FILE* f = fopen(out_path.c_str(), "w");
    if (!f) return;
    fprintf(f, "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races\n", (unsigned long long)stats.checks.load(), (unsigned long long)stats.ok.load(),
            (unsigned long long)stats.bad.load(), (unsigned long long)stats.skipped.load(), (unsigned long long)stats.races.load());
    std::lock_guard lk(m_);
    for (ShadowFn* p : fns_) {
        if (!p->checks) continue;
        fprintf(f, "%-60.60s checks %6llu ok %6llu bad %llu skipped %llu races %llu\n", p->sym, (unsigned long long)p->checks.load(), (unsigned long long)p->ok.load(),
                (unsigned long long)p->bad.load(), (unsigned long long)p->skipped.load(), (unsigned long long)p->races.load());
    }
    fclose(f);
}

void ShadowFamily::totals() {
    u64 n = stats.checks;
    if (n % 1000) {
        // (the counts file also every 10 s: a session ends with a kill)
        static std::atomic<s64> last{0};
        static std::mutex m;
        s64 now = (s64)time(nullptr), l = last.load(std::memory_order_relaxed);
        if (out_path.empty() || now - l < 10 || !last.compare_exchange_strong(l, now)) return;
        std::lock_guard lk(m);
        write_counts();
        return;
    }
    write_counts();
    LOGI(log_tag.c_str(), "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races", (unsigned long long)n, (unsigned long long)stats.ok.load(),
         (unsigned long long)stats.bad.load(), (unsigned long long)stats.skipped.load(), (unsigned long long)stats.races.load());
}

ShadowFn::ShadowFn(ShadowFamily& f, const char* s) : sym(s), fam(f) { f.add_fn(this); }

bool check_due(ShadowFn& f) {
    if (__builtin_expect(!f.fam.on.load(std::memory_order_relaxed), 1)) return false;
    if (t_in_check || t_busy || !f.orig || !f.fam.only.match(f.sym)) return false;
    if (f.fam.budget && f.checks >= (u64)f.fam.budget) return false;
    return f.calls.fetch_add(1, std::memory_order_relaxed) % (u64)f.fam.every == 0;
}

CheckScope::CheckScope() { t_in_check = t_busy = true; }
CheckScope::~CheckScope() { t_in_check = t_busy = false; }

void check_result(ShadowFn& f, Outcome o, const std::string& why) {
    auto& s = f.fam.stats;
    f.checks++;
    s.checks++;
    switch (o) {
    case Outcome::Ok:
        f.ok++, s.ok++;
        break;
    case Outcome::Mismatch:
        f.bad++, s.bad++;
        if (f.bad <= 5) LOGE(f.fam.log_tag.c_str(), "MISMATCH %s: %s", f.sym, why.c_str());
        break;
    case Outcome::Skipped:
        f.skipped++, s.skipped++;
        if (f.skipped <= 2 && !why.empty()) LOGI(f.fam.log_tag.c_str(), "skipped %s: %s", f.sym, why.c_str());
        break;
    case Outcome::Race:
        f.races++, s.races++;
        break;
    }
    f.fam.totals();
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

void check_getter(Cpu& c, ShadowFn& f, HostFn native, u64 mask, int out_reg, size_t out_bytes) {
    CheckScope scope;
    u64 x[8];
    for (int i = 0; i < 8; i++) x[i] = c.x(i);
    u8* out = out_reg >= 0 ? (u8*)x[out_reg] : nullptr;
    std::vector<u8> mine(out ? out_bytes : 0);
    auto run_both = [&](u64& got, u64& want, bool& out_same) {
        for (int i = 0; i < 8; i++) c.set_x(i, x[i]);
        native(c);
        got = c.x(0) & mask;
        if (out) std::memcpy(mine.data(), out, out_bytes);
        want = guest_call(f.orig, {x[0], x[1], x[2], x[3]}) & mask;
        out_same = !out || std::memcmp(mine.data(), out, out_bytes) == 0;
        if (out) std::memcpy(out, mine.data(), out_bytes);  // (the native's result stands)
        c.set_x(0, got);
    };
    u64 got, want;
    bool out_same;
    run_both(got, want, out_same);
    if (got == want && out_same) return check_result(f, Outcome::Ok);
    // Rerun both: a value another thread changed in between doesn't reproduce.
    run_both(got, want, out_same);
    if (got == want && out_same) return check_result(f, Outcome::Race);
    char m[128];
    snprintf(m, sizeof m, "this %#" PRIx64 ": native %#" PRIx64 " guest %#" PRIx64 "%s", x[0], got, want, out_same ? "" : " (out-parameter differs)");
    check_result(f, Outcome::Mismatch, m);
}

}  // namespace soa::live
