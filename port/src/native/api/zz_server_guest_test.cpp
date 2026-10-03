// The server tests that need the port (port code): the booted client, the port's asset manager and
// run options. The server library's own tests
// (top-level server/) run after the port's in `soa --selftest` and alone in `soa-server
// --selftest`. Registered after the battle zz_* tests, where they ran when the server was part of
// port/src (they were port/src/server/{client_status,event_clock_test,event_tests,server}.cpp).
#include <sqlite3.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "android/ndk.h"
#include "core/cpu.h"
#include "core/log.h"
#include "core/options.h"
#include "core/paths.h"
#include "native/api/server_adapters.h"
#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "soaserver/events.h"
#include "soaserver/ext.h"
#include "soaserver/scratch.h"
#include "soaserver/server.h"

namespace soa::server_port {
namespace {

using server::Request;
using server::Value;
namespace ext = server::ext;
namespace events = server::events;
namespace rules = server::rules;
using server::mp_decode;

int64_t local(int y, int mo, int d, int h = 12, int mi = 0, int s = 0) {
    struct tm tm = {};
    tm.tm_year = y - 1900;
    tm.tm_mon = mo - 1;
    tm.tm_mday = d;
    tm.tm_hour = h;
    tm.tm_min = mi;
    tm.tm_sec = s;
    tm.tm_isdst = -1;
    return (int64_t)mktime(&tm);
}

// ---- the port's run options ------------------------------------------------------------------
NATIVE_TEST("server/options") {
    t.expect_eq(parse_clock("2021-05-25 12:00:00"), local(2021, 5, 25, 12), "date and time");
    t.expect_eq(parse_clock("2021-05-25"), local(2021, 5, 25, 0), "date only");
    t.expect_eq(parse_clock("1621944000"), (int64_t)1621944000, "Unix seconds");
    t.expect_eq(parse_clock("soon"), (int64_t)0, "unparsable");
    ServerOptions o;
    if (!set_clock(o, "2019-10-01 04:00:00") || !o.has_clock) t.fail("set_clock");
    int64_t off = local(2019, 10, 1, 4) - (int64_t)time(nullptr);
    if (o.clock_offset > off + 5 || o.clock_offset < off - 5) t.fail("clock offset");
}

// The port keeps game and run state in RunOptions, never in the environment: no setenv in port/src
// (checked over the sources when they're next to the build).
NATIVE_TEST("server/no-setenv-state") {
    std::filesystem::path src;
    if (std::string p = find_repo_file("port/src/core/options.h"); !p.empty()) src = repo_path("port/src");
    if (src.empty()) {
        LOGW("selftest", "server/no-setenv-state: port/src not found; skipped");
        return;
    }
    const std::string needle = std::string("set") + "env(";  // (spelled so this file doesn't match)
    int files = 0;
    for (auto& e : std::filesystem::recursive_directory_iterator(src)) {
        auto ext = e.path().extension();
        if (ext != ".cpp" && ext != ".h" && ext != ".inc") continue;
        files++;
        std::ifstream f(e.path());
        std::string line;
        for (int n = 1; std::getline(f, line); n++) {
            size_t p = line.find(needle);
            if (p == std::string::npos) continue;
            size_t c = line.find("//");
            if (c != std::string::npos && c < p) continue;  // a comment
            t.fail("%s:%d: setenv (use core/options.h RunOptions): %s", e.path().c_str(), n, line.c_str());
        }
    }
    if (!files) t.fail("no sources scanned");
}

// ---- the port's asset lookup (server_adapters.cpp AssetManagerIndex) ---------------------------
// The asset lookup (events::asset_exists, shared with Sphere 211) sees the install-time asset
// pack (assetpack/...) as well as builtin_data/ (APKs and --download-dir).
NATIVE_TEST("server/event-asset-lookup") {
    AssetManager& am = asset_manager();
    if (am.file_count() == 0) return;  // no APKs loaded
    t.expect_eq(events::asset_exists("Script/__no_such_script__.msgp"), false, "a missing file");
    auto pack = am.list_files("assetpack/Script");
    if (!pack.empty()) t.expect_eq(events::asset_exists("Script/" + pack.front()), true, "an install-time pack script");
    auto bg = am.list_files("builtin_data/BG");
    if (!bg.empty()) t.expect_eq(events::asset_exists("BG/" + bg.front()), true, "a builtin_data file");
    if (pack.empty() && bg.empty()) fprintf(stderr, "    (no assetpack/Script or builtin_data/BG files; nothing to look up)\n");
}

// The stand-in overlay (--standin-assets) makes a file present for the lookup, but never shadows
// an asset the APKs have (real assets win).
NATIVE_TEST("server/standin-assets") {
    AssetManager& am = asset_manager();
    if (am.file_count() == 0) return;  // no APKs loaded
    char tmpl[] = "/tmp/soa-standin-XXXXXX";
    if (!mkdtemp(tmpl)) return;
    std::string dir = tmpl, saved = am.standin_dir();
    auto put = [&](const std::string& rel) {
        std::string path = dir + "/" + rel;
        for (size_t p = dir.size() + 1; (p = path.find('/', p)) != std::string::npos; p++) mkdir(path.substr(0, p).c_str(), 0755);
        if (FILE* f = fopen(path.c_str(), "wb")) fclose(f);
        return path;
    };
    std::vector<std::string> made = {put("Image/etc2/__standin_probe__.aif")};
    auto bg = am.list_files("builtin_data/BG");
    if (!bg.empty()) made.push_back(put("BG/" + bg.front()));
    t.expect_eq(events::asset_exists("Image/__standin_probe__.aif"), false, "absent without the overlay");
    am.set_standin_dir(dir);
    t.expect_eq(events::asset_exists("Image/__standin_probe__.aif"), true, "present through the overlay");
    std::string host;
    t.expect_eq(am.find_download("builtin_data/Image/etc2/__standin_probe__.aif", host) && host == made[0], true, "opened from the overlay");
    if (!bg.empty()) {
        bool shadowed = am.find_download("builtin_data/BG/" + bg.front(), host) && host.compare(0, dir.size(), dir) == 0;
        t.expect_eq(shadowed, false, "an APK asset is not served from the overlay");
    }
    am.set_standin_dir(saved);
    for (auto it = made.rbegin(); it != made.rend(); ++it) unlink(it->c_str());
    for (const char* d : {"/Image/etc2", "/Image", "/BG", ""}) rmdir((dir + d).c_str());
}

}  // namespace
}  // namespace soa::server_port
