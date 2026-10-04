// The port's side of the server library (see server_adapters.h). Port code, not guest behaviour.
#include "native/api/server_adapters.h"

#include <cstring>
#include <map>
#include <memory>

#include "android/ndk.h"
#include "core/cpu.h"
#include "core/log.h"
#include "core/options.h"
#include "core/paths.h"
#include "native/api/client_battle_log.h"
#include "native/api/packet_log.h"
#include "native/common/guest_std.h"
#include "soaserver/battle_log.h"
#include "soaserver/config.h"
#include "soaserver/hooks.h"
#include "soaserver/log.h"

namespace soa::server_port {

namespace {

// ---- log -------------------------------------------------------------------------------------
void log_sink(server::LogLevel lvl, const char* tag, const char* msg) { log_write((LogLevel)(int)lvl, tag, "%s", msg); }
bool log_on(server::LogLevel lvl) { return g_log_level <= (LogLevel)(int)lvl; }
static_assert((int)server::LogLevel::Trace == (int)LogLevel::Trace && (int)server::LogLevel::Error == (int)LogLevel::Error);

// (No StatusProvider since the rebase's revision 2, and no other guest-reading hooks since H
// (port/PLAN.md task 7): the server takes the client's data from the requests, as soa-server
// does; the battle log comes with the request, made by the client's own serializer (inproc_request).)

// ---- asset files ---------------------------------------------------------------------------
// The port's asset lookup: the APKs (find), then --download-dir and the stand-in overlay
// (find_download).
struct AssetManagerIndex : server::AssetIndex {
    bool exists(const std::string& name) const override {
        AssetManager::Found f;
        AssetManager::Download dl;
        return asset_manager().find(name, f) || asset_manager().find_download(name, dl);
    }
    bool empty() const override { return asset_manager().file_count() == 0; }
};

// Installed before main() (the library keeps them in function-local statics, so the order of
// static initializers doesn't matter).
bool g_installed = [] {
    server::set_log_sink(log_sink, log_on);
    server::set_asset_index(std::make_shared<AssetManagerIndex>());
    return true;
}();

}  // namespace

void config_from_options(const std::string& data_dir) {
    // ServerOptions is the ServerConfig (core/options.h): the flags, then the files this run found.
    const ServerOptions& o = options().server;
    server::ServerConfig& c = server::config();
    c = o;
    c.repo_roots = repo_roots();
    c.data_root = data_dir;  // vfs_init's root (the CDN's scratch dir; an old server_campaign.txt, imported once)
    // The CDN's source (server_cdn.cpp, --server inproc): the client's download tree and stand-ins,
    // as soa-server's --download-dir / --standin-assets.
    const ClientOptions& cl = options().client;
    c.download_dir = cl.download_dir;
    c.cdn_standins = !cl.standin_off;
    c.standin_dir = cl.standin_dir;
    // --log-packets DIR: the in-process route's packet log (packet_log.h)
    packet_log::open(o.log_packets);
}

server::Request capture_from_guest(const char* mangled, uint32_t fid, const uint64_t* x) {
    server::Request r;
    r.fid = fid;
    const char* p = mangled + strlen("_ZN13FakeApiCaller");
    char* e;
    unsigned long n = strtoul(p, &e, 10);
    r.method.assign(e, n);
    p = e + n;
    if (*p == 'E') p++;
    int reg = 1;
    while (*p && reg < 8) {
        if (!strncmp(p, "PKa", 3)) {
            const char* s = (const char*)x[reg++];
            r.strs.push_back(s ? s : "");
            p += 3;
        } else if (!strncmp(p, "RKN9Framework10CSTLVectorI", 26)) {
            char t = p[26];
            const u64* v = (const u64*)x[reg++];
            std::vector<u64> out;
            if (v) {
                if (t == 'm')
                    for (const u64* q = (const u64*)v[0]; q < (const u64*)v[1]; q++) out.push_back(*q);
                else
                    for (const u32* q = (const u32*)v[0]; q < (const u32*)v[1]; q++) out.push_back(*q);
            }
            r.vecs.push_back(out);
            p += 26 + 3;  // "mEE" / "jEE"
        } else if (strchr("jmhiabtsyxl", *p)) {
            // only the argument's own bits (AAPCS64 leaves the rest of the register undefined),
            // zero-extended as the wire decoder does
            u64 v = x[reg++];
            if (strchr("ji", *p)) v = (u32)v;
            else if (strchr("hab", *p)) v = (u8)v;
            else if (strchr("ts", *p)) v = (u16)v;
            r.ints.push_back(v);
            p++;
        } else {
            break;  // v (none), f, z
        }
    }
    return r;
}

server::Request inproc_request(const char* mangled, uint32_t fid, const uint64_t* x) {
    server::Request r = capture_from_guest(mangled, fid, x);
    if (!server::carries_battle_log(r.method)) {
        packet_log::request(r, {});
        return r;
    }
    std::vector<u8> blob;
    s64 size = 0;
    if (!client_battle_log(&blob, &size)) {
        packet_log::request(r, {});
        // (b) the 3.7.0 client sends no request at all then; the FakeApiCaller route can't leave a
        // request unanswered, so it goes without a log (docs/client-changes.md, the FakeApiCaller
        // route's battle log)
        LOGW("server", "%s: the client's battle log can't be sent (size %ld, at most %zu): no log", r.method.c_str(), (long)size,
             server::kMaxBattleLog);
        return r;
    }
    r.battle_log = server::parse_battle_log(blob.data(), blob.size());
    packet_log::request(r, blob);
    LOGI("server", "%s: battle log %zu bytes (the client's serializer), mission_time %u", r.method.c_str(), blob.size(),
         r.battle_log ? r.battle_log->prop_u32("mission_time", 0) : 0u);
    return r;
}

namespace {
std::map<uint32_t, server::Request>& kept() {
    static std::map<uint32_t, server::Request> m;
    return m;
}
}  // namespace
void remember(server::Request r) {
    uint32_t fid = r.fid;
    kept()[fid] = std::move(r);
}
server::Request take(uint32_t fid) {
    auto it = kept().find(fid);
    if (it == kept().end()) {
        server::Request r;
        r.fid = fid;
        return r;
    }
    server::Request r = std::move(it->second);
    kept().erase(it);
    return r;
}

void capture(const char* mangled, uint32_t fid, const uint64_t* x) {
    if (!server::enabled()) return;
    remember(inproc_request(mangled, fid, x));
}

}  // namespace soa::server_port
