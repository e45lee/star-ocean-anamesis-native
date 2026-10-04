// The lockstep live check of host-library families (lockstep.h).
#include "native/common/lockstep.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "core/log.h"

namespace soa::live {

u64 Lockstep::shadow(u64 key, size_t bytes) {
    std::lock_guard lk(m_);
    auto it = shadows_.find(key);
    if (it != shadows_.end()) return it->second.first;
    u64 b = (u64)(uintptr_t)calloc(1, bytes < 16 ? 16 : bytes);
    shadows_[key] = {b, bytes};
    blocks_[b] = key;
    return b;
}
u64 Lockstep::find(u64 key) {
    std::lock_guard lk(m_);
    auto it = shadows_.find(key);
    return it == shadows_.end() ? 0 : it->second.first;
}
void Lockstep::drop(u64 key) {
    std::lock_guard lk(m_);
    auto it = shadows_.find(key);
    if (it == shadows_.end()) return;
    blocks_.erase(it->second.first);
    free((void*)(uintptr_t)it->second.first);
    shadows_.erase(it);
}
bool Lockstep::is_shadow(u64 p) {
    if (!p) return false;
    std::lock_guard lk(m_);
    return blocks_.count(p) != 0;
}

void Lockstep::count(const char* fn, bool good) {
    {
        std::lock_guard lk(m_);
        Counts& c = per_fn_[fn];
        c.checks++;
        if (!good) c.bad++;
    }
    u64 n = ++stats.checks;
    if (good) stats.ok++;
    else stats.bad++;
    s64 now = (s64)time(nullptr), l = last_write_.load(std::memory_order_relaxed);
    bool timed = !out_path.empty() && now - l >= 10 && last_write_.compare_exchange_strong(l, now);
    if (n % 1000 == 0)
        LOGI(log_tag.c_str(), "%llu checks: %llu ok, %llu mismatches", (unsigned long long)n, (unsigned long long)stats.ok.load(),
             (unsigned long long)stats.bad.load());
    if (timed || n % 1000 == 0) write_summary();
}
void Lockstep::ok(const char* fn) { count(fn, true); }
void Lockstep::bad(const char* fn, const char* fmt, ...) {
    if (logged_.fetch_add(1) < 20) {
        char buf[512];
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, sizeof buf, fmt, ap);
        va_end(ap);
        LOGE(log_tag.c_str(), "mismatch in %s: %s", fn, buf);
    }
    count(fn, false);
}
void Lockstep::write_summary() {
    if (out_path.empty()) return;
    std::lock_guard lk(m_);
    if (FILE* f = fopen(out_path.c_str(), "w")) {
        fprintf(f, "%llu checks: %llu ok, %llu mismatches\n", (unsigned long long)stats.checks.load(), (unsigned long long)stats.ok.load(),
                (unsigned long long)stats.bad.load());
        for (auto& [fn, c] : per_fn_) fprintf(f, "%-40s checks %8llu bad %llu\n", fn.c_str(), (unsigned long long)c.checks, (unsigned long long)c.bad);
        fclose(f);
    }
}

void forward_to_original(Cpu& c, u64 orig) {
    GuestArgs a;
    for (int i = 0; i < 8; i++) a.i(c.x(i));
    for (int i = 0; i < 8; i++) a.vecs.push_back(c.v(i));
    a.x8 = c.x(8);
    GuestResult r = guest_call(orig, a);
    c.set_x(0, r.x0);
    c.set_x(1, r.x1);
    c.set_v(0, r.v0);
}

}  // namespace soa::live
