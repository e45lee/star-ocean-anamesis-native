// The lockstep live check of host-library families (lockstep.h).
#include "native/common/lockstep.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "soaruntime/core/log.h"

namespace soa::live {

u64 Lockstep::shadow(u64 key, size_t bytes) {
    std::lock_guard lk(m_);
    auto it = shadows_.find(key);
    if (it != shadows_.end()) return it->second.first;
    u64 b = (u64)(uintptr_t)calloc(1, bytes < 16 ? 16 : bytes);
    shadows_[key] = {b, bytes};
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
    if (it->second.second) free((void*)(uintptr_t)it->second.first);
    shadows_.erase(it);
}
void Lockstep::adopt(u64 key, u64 block) {
    std::lock_guard lk(m_);
    if (auto it = shadows_.find(key); it != shadows_.end() && it->second.second) free((void*)(uintptr_t)it->second.first);
    shadows_[key] = {block, 0};
}
u64 Lockstep::release(u64 key) {
    std::lock_guard lk(m_);
    auto it = shadows_.find(key);
    if (it == shadows_.end()) return 0;
    u64 b = it->second.first;
    shadows_.erase(it);
    return b;
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
    if (timed || n % 1000 == 0 || n < 200) write_summary();  // (the first ones each: rare functions end up in it)
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

namespace {
thread_local int t_shadow = 0;  // > 0: this thread runs the guest library for a shadow
}
u64 shadow_call(u64 fn, std::initializer_list<u64> args) {
    ++t_shadow;
    u64 r = guest_call(fn, args);
    --t_shadow;
    return r;
}
bool in_shadow_run() { return t_shadow > 0; }

}  // namespace soa::live
