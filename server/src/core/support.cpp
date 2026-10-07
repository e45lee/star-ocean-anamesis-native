// The server library's platform-neutral support (library code): configuration, log sink, the
// asset index (soaserver/hooks.h), CHash32.
#include <sys/stat.h>

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <mutex>

#include <soa/file_tree.h>

#include "soaserver/chash32.h"
#include "soaserver/config.h"
#include "soaserver/hooks.h"
#include "soaserver/log.h"
#include "core/time.h"

namespace soa::server {

// ---- configuration ---------------------------------------------------------------------------

ServerConfig& config() {
    static ServerConfig c;
    return c;
}

namespace {
bool exists(const std::string& p) {
    struct stat st;
    return !p.empty() && stat(p.c_str(), &st) == 0;
}
}  // namespace

std::string find_repo_file(std::initializer_list<const char*> rels) {
    const auto& all = config().repo_roots;
    for (const char* rel : rels) {
        if (all.empty()) {
            if (exists(rel)) return rel;
            continue;
        }
        for (auto& r : all) {
            std::string p = r + "/" + rel;
            if (exists(p)) return p;
        }
    }
    return "";
}

std::string find_repo_file(const std::string& rel) { return find_repo_file({rel.c_str()}); }

// ---- log -------------------------------------------------------------------------------------
namespace {
std::mutex g_log_mu;
void default_write(LogLevel lvl, const char* tag, const char* msg) {
    static const char* names[] = {"T", "D", "I", "W", "E"};
    std::lock_guard<std::mutex> l(g_log_mu);
    fprintf(stderr, "%s/%s: %s\n", names[(int)lvl], tag, msg);
}
bool default_enabled(LogLevel lvl) { return lvl >= LogLevel::Info; }
struct Sink {
    LogWriteFn write = default_write;
    LogEnabledFn enabled = default_enabled;
};
Sink& sink() {
    static Sink s;
    return s;
}
}  // namespace

void set_log_sink(LogWriteFn write, LogEnabledFn enabled) {
    sink().write = write ? write : default_write;
    sink().enabled = enabled ? enabled : default_enabled;
}

bool log_enabled(LogLevel level) { return sink().enabled(level); }

void log_write(LogLevel level, const char* tag, const char* fmt, ...) {
    char buf[4096];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    sink().write(level, tag, buf);
}

// ---- the asset index (hooks.h) -------------------------------------------------------------
namespace {
std::shared_ptr<const AssetIndex>& g_assets() {
    static std::shared_ptr<const AssetIndex> p;
    return p;
}

struct NoAssets : AssetIndex {
    bool exists(const std::string&) const override { return false; }
    bool empty() const override { return true; }
};

struct DirAssets : AssetIndex {
    std::vector<std::shared_ptr<const FileTree>> dirs;  // folders or zips (the download: soa/file_tree.h)
    bool exists(const std::string& name) const override {
        // "builtin_data/<rel>" -> <dir>/<rel> (a regular file), as the port's --download-dir
        static const char kBuiltin[] = "builtin_data/";
        std::string n = name;
        while (!n.empty() && n[0] == '/') n.erase(0, 1);
        if (n.compare(0, sizeof(kBuiltin) - 1, kBuiltin) != 0) return false;
        std::string rel = n.substr(sizeof(kBuiltin) - 1);
        if (rel.empty() || rel.find("..") != std::string::npos) return false;
        for (auto& d : dirs)
            if (d->exists(rel)) return true;
        return false;
    }
    bool empty() const override { return dirs.empty(); }
};
}  // namespace

std::shared_ptr<const AssetIndex> set_asset_index(std::shared_ptr<const AssetIndex> index) {
    std::swap(g_assets(), index);
    return index;
}
const AssetIndex& asset_index() {
    static const NoAssets none;
    const auto& p = g_assets();
    return p ? *p : none;
}
std::shared_ptr<const AssetIndex> dir_asset_index(std::vector<std::string> dirs) {
    auto d = std::make_shared<DirAssets>();
    for (auto& x : dirs)
        if (!x.empty())
            if (auto t = FileTree::open(x)) d->dirs.push_back(std::move(t));
    return d;
}

// ---- CHash32 ---------------------------------------------------------------------------------
namespace {
const uint32_t* crc_table() {
    static uint32_t t[256];
    static bool init = [] {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t c = i;
            for (int k = 0; k < 8; k++) c = (c & 1) ? (c >> 1) ^ 0xEDB88320u : c >> 1;
            t[i] = c;
        }
        return true;
    }();
    (void)init;
    return t;
}
}  // namespace

uint32_t chash32(const void* data, size_t len) {
    const uint32_t* t = crc_table();
    const auto* p = (const unsigned char*)data;
    uint32_t c = (uint32_t)len;
    if (len == 0) return 0;
    for (size_t i = 0; i < len; i++) c = t[(c ^ p[i]) & 0xff] ^ (c >> 8);
    return c;
}
uint32_t chash32(const char* s) { return s ? chash32(s, strlen(s)) : 0; }

}  // namespace soa::server
