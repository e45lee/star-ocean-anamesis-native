// Run-both live checks: the family's switches, counters and counts file (live_run_both.h).
#include "native/common/live_run_both.h"

#include <cstdio>
#include <ctime>

#include "core/log.h"

namespace soa::live {

RunBothFamily::Fn::Fn(RunBothFamily& fam, const char* s) : sym(s) {
    std::lock_guard lk(fam.m_);
    fam.fns_.push_back(this);
}

RunBothFamily::RunBothFamily(const char* tag, int every) : fam_(tag, every, false) {}

bool RunBothFamily::due_slow(Fn& f) {
    if (t_busy || !f.orig || !fam_.only.match(f.sym)) return false;
    if (fam_.budget && f.checks >= (u64)fam_.budget) return false;
    return f.calls.fetch_add(1, std::memory_order_relaxed) % (u64)fam_.every == 0;
}

void RunBothFamily::result(Fn& f, Outcome o, const std::string& why) {
    auto& s = fam_.stats;
    f.checks++;
    s.checks++;
    switch (o) {
    case Outcome::Ok:
        f.ok++, s.ok++;
        break;
    case Outcome::Mismatch:
        f.bad++, s.bad++;
        if (f.bad <= 5) LOGE(fam_.log_tag.c_str(), "MISMATCH %s: %s", f.sym, why.c_str());
        break;
    case Outcome::Skipped:
        f.skipped++, s.skipped++;
        if (f.skipped <= 2 && !why.empty()) LOGI(fam_.log_tag.c_str(), "skipped %s: %s", f.sym, why.c_str());
        break;
    case Outcome::Race:
        f.races++, s.races++;
        break;
    }
    totals();
}

std::string RunBothFamily::diff_bytes(const void* native, const void* guest, size_t n) {
    const u8* a = (const u8*)native;
    const u8* b = (const u8*)guest;
    for (size_t i = 0; i < n; i++) {
        if (a[i] == b[i]) continue;
        char m[96];
        snprintf(m, sizeof m, "+0x%zx: native %02x guest %02x", i, a[i], b[i]);
        return m;
    }
    return {};
}

void RunBothFamily::summary_file() {
    if (fam_.out_path.empty()) return;
    FILE* f = fopen(fam_.out_path.c_str(), "w");
    if (!f) return;
    auto& s = fam_.stats;
    fprintf(f, "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races\n", (unsigned long long)s.checks.load(),
            (unsigned long long)s.ok.load(), (unsigned long long)s.bad.load(), (unsigned long long)s.skipped.load(),
            (unsigned long long)s.races.load());
    std::lock_guard lk(m_);
    for (Fn* p : fns_) {
        if (!p->checks) continue;
        fprintf(f, "%s\tchecks %llu ok %llu bad %llu skipped %llu races %llu\n", p->sym, (unsigned long long)p->checks.load(),
                (unsigned long long)p->ok.load(), (unsigned long long)p->bad.load(), (unsigned long long)p->skipped.load(),
                (unsigned long long)p->races.load());
    }
    fclose(f);
}

void RunBothFamily::totals() {
    auto& s = fam_.stats;
    u64 n = s.checks;
    if (n % 100000) {
        // (the counts file also every 10 s: a session ends with a kill)
        s64 now = (s64)time(nullptr), l = last_file_.load(std::memory_order_relaxed);
        if (fam_.out_path.empty() || now - l < 10 || !last_file_.compare_exchange_strong(l, now)) return;
        std::lock_guard lk(file_m_);
        summary_file();
        return;
    }
    summary_file();
    LOGI(fam_.log_tag.c_str(), "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races", (unsigned long long)n,
         (unsigned long long)s.ok.load(), (unsigned long long)s.bad.load(), (unsigned long long)s.skipped.load(),
         (unsigned long long)s.races.load());
}

}  // namespace soa::live
