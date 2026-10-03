// The one asset gate (core/assets.h; port code, not guest behaviour).
#include "core/assets.h"

#include <atomic>
#include <mutex>

#include "soaserver/hooks.h"

namespace soa::server::assets {

namespace {
std::mutex g_mu;
Check& override_fn() {
    static Check f;
    return f;
}
std::atomic<uint64_t> g_generation{0};
}  // namespace

void set_override(Check fn) {
    std::lock_guard<std::mutex> l(g_mu);
    override_fn() = std::move(fn);
    g_generation++;
}
bool has_override() {
    std::lock_guard<std::mutex> l(g_mu);
    return (bool)override_fn();
}
uint64_t generation() { return g_generation.load(); }

bool no_source() { return asset_index().empty(); }

bool found(const std::string& rel) {
    const AssetIndex& am = asset_index();
    size_t slash = rel.rfind('/');
    std::string dir = slash == std::string::npos ? "" : rel.substr(0, slash + 1), file = rel.substr(slash + 1);
    for (const char* sub : {"", "etc2/", "etc2/hi/"})
        for (const char* root : {"builtin_data/", "assetpack/"}) {
            std::string name = root + dir + sub + file;
            if (am.exists(name)) return true;
        }
    return false;
}

bool available(const std::string& rel) {
    Check check;
    {
        std::lock_guard<std::mutex> l(g_mu);
        check = override_fn();
    }
    if (check) return check(rel);
    if (no_source()) return true;
    return found(rel);
}

}  // namespace soa::server::assets
