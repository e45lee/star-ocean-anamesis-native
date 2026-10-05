// The hand-written command-line loops the CLI11 parsers replaced (port/src/main.cpp,
// server/app/main.cpp, emulator/src/main.cpp, emulator-viewer/src/main.cpp as of 3bfa883), kept
// as the reference cli_tests.cpp compares the new parsers with. Copied as they were; the only
// edits make them testable: they fill the new parsers' Args structs, `usage(); exit(2)` / `return
// 2` became `return 2` (0 for -h / --help), and actions taken in the loop (--list-native's list,
// --apk-dir's and --legacy-res' warnings, the --natives / --live-check checks of port code) are
// recorded instead. Test code: nothing here is built into a program.
#include "legacy.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <soa/cli.h>

namespace legacy {

namespace {
struct Exit {
    int rc;
};
// soa's set_clock (port/src/core/options.cpp, and the server library's: the same rule).
bool old_set_clock(soa::server::ServerConfig& o, const std::string& s) {
    int64_t t = soa::cli::parse_clock(s);
    if (!t) return false;
    o.has_clock = true;
    o.clock = t;
    o.clock_offset = t - (int64_t)time(nullptr);
    return true;
}
}  // namespace

int parse_soa(int argc, const char* const* argv, soa::SoaArgs& r) {
    using namespace soa;
    RunOptions& opt = *r.opt;
    ServerOptions& srv = opt.server;
    auto& p370 = r.p370;
    auto& host = r.host;
    std::string& server_mode = r.server_mode;
    bool server_given = false;
    try {
        for (int i = 1; i < argc; i++) {
            std::string a = argv[i];
            auto next = [&]() -> std::string {
                if (i + 1 >= argc) throw Exit{2};
                return argv[++i];
            };
            if (a == "--apk-dir") {
                next();
                r.apk_dir_given = true;
            }
            else if (a == "--apk") r.apk_path = next();
            else if (a == "--server") server_mode = next(), server_given = true;
            else if (a == "--http" || a == "--lobby") {
                std::string v = next();
                size_t c = v.rfind(':');
                int port = c == std::string::npos ? 0 : atoi(v.c_str() + c + 1);
                if (c == std::string::npos || c == 0 || port <= 0) return 2;
                auto& n = p370.netcfg;
                if (a == "--http") n.http_host = v.substr(0, c), n.http_port = port;
                else n.lobby_host = v.substr(0, c), n.lobby_port = port;
            }
            else if (a == "--map-host") {
                std::string v = next();
                size_t eq = v.find('=');
                std::string name = v.substr(0, eq);
                for (auto& ch : name) ch = (char)tolower((unsigned char)ch);
                p370.netcfg.hosts[name] = eq == std::string::npos ? "" : v.substr(eq + 1);
            }
            else if (a == "--device-clock") p370.device_clock = next();
            else if (a == "--no-patch") p370.patch = false;
            else if (a == "--natives") {
                std::string v = next();
                if (v != "route" && v != "all" && v != "none") return 2;  // (parse_native_set)
                r.natives = v;
            }
            else if (a == "--lib") r.lib_path = next();
            else if (a == "--data") r.data_dir = next();
            else if (a == "--size") sscanf(next().c_str(), "%dx%d", &host.width, &host.height);
            else if (a == "--smoke") r.smoke = true;
            else if (a == "--selftest") {
                r.selftest = true;
                if (i + 1 < argc && argv[i + 1][0] != '-') r.test_filter = argv[++i];
            }
            else if (a == "--no-native") r.natives = "none";
            else if (a == "--hires") {}
            else if (a == "--legacy-res") r.legacy_res = true;
            else if (a == "--render-size") host.render_size = next();
            else if (a == "--font") next();  // (HostConfig::font is gone, 2026-10-05: the value is dropped)
            else if (a == "--fullscreen") host.fullscreen = true;
            else if (a == "--headless") r.headless = 1;
            else if (a == "--windowed") r.headless = 0;
            else if (a == "--landscape") host.landscape = true;
            else if (a == "--shot") host.shots.push_back(next());
            else if (a == "--do") host.actions.push_back(next());
            else if (a == "--control") host.control_path = next();
            else if (a == "--gdb") r.gdb = next();
            else if (a == "--download-dir" || a == "--download") opt.client.download_dir = next();
            else if (a == "--download-prefer") opt.client.download_prefer = true;
            else if (a == "--fake-server") opt.client.fake_server_dir = next();
            else if (a == "--fake-server-schema") opt.client.fake_server_schema = next();
            else if (a == "--memstats") {
                opt.client.memstats = 1;
                if (i + 1 < argc && argv[i + 1][0] != '-') {
                    std::string c = argv[++i];
                    char* end = nullptr;
                    long v = strtol(c.c_str(), &end, 10);
                    if (c.empty() || *end || v < 1 || v > 86400) return 2;
                    opt.client.memstats = (int)v;
                }
            }
            else if (a == "--live-check") r.live_checks.push_back(next());  // (parse_live_check: main)
            else if (a == "--repo") opt.repo_dir = next();
            else if (a == "--standin-assets") {
                std::string d = next();
                if (d == "off" || d == "0") opt.client.standin_off = true;
                else opt.client.standin_dir = d;
            }
            else if (a == "--restore") return 2;
            else if (a == "--restore-tower") srv.restore_tower = true, r.server_flags.push_back(a);
            else if (a == "--home3d-all") srv.home3d_all = true, r.server_flags.push_back(a);
            else if (a == "--clock") {
                std::string c = next();
                if (!old_set_clock(srv, c)) return 2;
                r.server_flags.push_back(a);
            }
            else if (a == "--enable-events") srv.enable_events = true, r.server_flags.push_back(a);
            else if (a == "--galaxy-pass") srv.galaxy_pass = true, r.server_flags.push_back(a);
            else if (a == "--new-player") srv.new_player = true, r.server_flags.push_back(a);
            else if (a == "--surprise") srv.surprise = true, r.server_flags.push_back(a);
            else if (a == "--db") srv.db = next(), r.server_flags.push_back(a);
            else if (a == "--master") srv.master = next(), r.server_flags.push_back(a);
            else if (a == "--gacha-pools") srv.gacha_pools = next(), r.server_flags.push_back(a);
            else if (a == "--seed") srv.seed = next(), r.server_flags.push_back(a);
            else if (a == "--game-xml") srv.game_xml = next(), r.server_flags.push_back(a);
            else if (a == "--campaign-master-db") srv.campaign_master_db = next(), r.server_flags.push_back(a);
            else if (a == "--campaign-seed") srv.campaign_seed = next(), r.server_flags.push_back(a);
            else if (a == "--fail") srv.fail = next(), r.server_flags.push_back(a);
            else if (a == "--log-packets") srv.log_packets = next(), r.server_flags.push_back(a);
            else if (a == "--seed-rng") {
                std::string c = next();
                char* end = nullptr;
                unsigned long long v = strtoull(c.c_str(), &end, 0);
                if (c.empty() || *end) return 2;
                srv.has_seed_rng = true, srv.seed_rng = v;
                r.server_flags.push_back(a);
            }
            else if (a == "--guest-cpus") {
                std::string c = next();
                char* end = nullptr;
                long v = strtol(c.c_str(), &end, 10);
                if (c != "host" && (c.empty() || *end || v < 1 || v > 256)) return 2;
                opt.client.guest_cpus = c == "host" ? 0 : (int)v;
            }
            else if (a == "--event-keywords") srv.event_keywords = next(), r.server_flags.push_back(a);
            else if (a == "--start-coins") {
                std::string c = next();
                char* end = nullptr;
                unsigned long long v = strtoull(c.c_str(), &end, 10);
                if (c.empty() || *end || c[0] == '-' || v > 0xffffffffULL) return 2;
                srv.start_coins = (uint32_t)v;
                r.server_flags.push_back(a);
            }
            else if (a == "--list-native") {
                r.list_native = true;  // (printed the list and exited 0)
                return -1;
            }
            else if (a == "-v") r.verbose = 1;
            else if (a == "-vv") r.verbose = 2;
            else return a == "-h" || a == "--help" ? 0 : 2;
        }
    } catch (Exit e) {
        return e.rc;
    }
    // (after the loop: --server HOST[:PORT], checked by main with fatal())
    if (server_given && server_mode != "inproc") {
        std::string h = server_mode;
        int port = 0;
        size_t c = h.rfind(':');
        if (c != std::string::npos && h.find(':') == c) port = atoi(h.c_str() + c + 1), h = h.substr(0, c);
        if (h.empty() || (c != std::string::npos && port <= 0)) return 1;
        p370.netcfg.server_host = h;
        if (port) p370.netcfg.server_port = port;
    }
    return -1;
}

int parse_server(int argc, const char* const* argv, soa::server::app::ServerArgs& r) {
    soa::server::ServerConfig& c = *r.config;
    try {
        for (int i = 1; i < argc; i++) {
            std::string a = argv[i];
            auto next = [&]() -> std::string {
                if (i + 1 >= argc) throw Exit{2};
                return argv[++i];
            };
            if (a == "--selftest") {
                r.selftest = true;
                if (i + 1 < argc && argv[i + 1][0] != '-') r.filter = argv[++i];
            } else if (a == "--shuffle") r.shuffle = strtoull(next().c_str(), nullptr, 0);
            else if (a == "--replay") r.replay_dir = next();
            else if (a == "--out") r.replay_out = next();
            else if (a == "--list-apis") r.list_apis = true;
            else if (a == "--list-hooks") r.list_hooks = true;
            else if (a == "--repo") r.repo = next();
            else if (a == "--listen") r.listen = next();
            else if (a == "--http") r.http = next();
            else if (a == "--bridge-url") r.bridge_url = next();
            else if (a == "--log-packets") c.log_packets = next();
            else if (a == "--data") r.data = next();
            else if (a == "--db") c.db = next();
            else if (a == "--master") c.master = next();
            else if (a == "--apk") c.apk = next();
            else if (a == "--gacha-pools") c.gacha_pools = next();
            else if (a == "--seed") c.seed = next();
            else if (a == "--game-xml") c.game_xml = next();
            else if (a == "--seed-rng") c.has_seed_rng = true, c.seed_rng = strtoull(next().c_str(), nullptr, 0);
            else if (a == "--new-player") c.new_player = true;
            else if (a == "--clock") {
                std::string v = next();
                if (!old_set_clock(c, v)) return 2;
            } else if (a == "--start-coins") c.start_coins = (uint32_t)strtoul(next().c_str(), nullptr, 10);
            else if (a == "--galaxy-pass") c.galaxy_pass = true;
            else if (a == "--enable-events") c.enable_events = true;
            else if (a == "--event-keywords") c.event_keywords = next();
            else if (a == "--restore-tower") c.restore_tower = true;
            else if (a == "--home3d-all") c.home3d_all = true;
            else if (a == "--download-dir" || a == "--download") r.download_dir = c.download_dir = next();
            else if (a == "--cdn-url") c.cdn_url = next();
            else if (a == "--standin-assets") {
                std::string v = next();
                if (v == "off" || v == "0") c.cdn_standins = false;
                else c.standin_dir = v;
            } else if (a == "--cdn-scratch") c.cdn_scratch = next();
            else if (a == "--cdn-check") {
                r.cdn_check = true;
                while (i + 1 < argc && argv[i + 1][0] != '-') r.cdn_paths.push_back(argv[++i]);
            } else if (a == "--campaign-master-db") c.campaign_master_db = next();
            else if (a == "--campaign-seed") c.campaign_seed = next();
            else if (a == "--fail") c.fail = next();
            else if (a == "--surprise") c.surprise = true;
            else if (a == "--keep-open-after-error") r.keep_open_after_error = true;
            else if (a == "-v") r.verbose = 1;
            else return a == "-h" || a == "--help" ? 0 : 2;
        }
    } catch (Exit e) {
        return e.rc;
    }
    return -1;
}

int parse_emu(int argc, const char* const* argv, soa::emu::EmuArgs& r) {
    auto& p370 = r.p370;
    auto& host = r.host;
    p370.device_clock = soa::emu::kDefaultDeviceClock;
    try {
        for (int i = 1; i < argc; i++) {
            std::string a = argv[i];
            auto next = [&]() -> std::string {
                if (i + 1 >= argc) throw Exit{2};
                return argv[++i];
            };
            if (a == "--lib") r.lib_path = next();
            else if (a == "--apk") r.apks.push_back(next());
            else if (a == "--data") r.data_dir = next();
            else if (a == "--download-dir" || a == "--download") r.download_dir = next();
            else if (a == "--download-prefer") r.download_prefer = true;
            else if (a == "--repo") r.repo = next();
            else if (a == "--device-clock") p370.device_clock = next();
            else if (a == "--no-patch") p370.patch = false;
            else if (a == "--server" || a == "--http" || a == "--lobby") {
                std::string v = next();
                std::string h = v;
                int port = 0;
                size_t c = v.rfind(':');
                if (c != std::string::npos && v.find(':') == c) h = v.substr(0, c), port = atoi(v.c_str() + c + 1);
                if (h.empty() || (c != std::string::npos && port <= 0) || (a != "--server" && port <= 0)) return 2;
                auto& n = p370.netcfg;
                if (a == "--server") n.server_host = h, n.server_port = port ? port : n.server_port;
                else if (a == "--http") n.http_host = h, n.http_port = port;
                else n.lobby_host = h, n.lobby_port = port;
            }
            else if (a == "--map-host") {
                std::string v = next();
                size_t eq = v.find('=');
                std::string name = v.substr(0, eq);
                for (auto& ch : name) ch = (char)tolower((unsigned char)ch);
                p370.netcfg.hosts[name] = eq == std::string::npos ? "" : v.substr(eq + 1);
            }
            else if (a == "--guest-cpus") {
                std::string c = next();
                char* end = nullptr;
                long v = strtol(c.c_str(), &end, 10);
                if (c != "host" && (c.empty() || *end || v < 1 || v > 256)) return 2;
                r.guest_cpus = c == "host" ? 0 : (int)v;
            }
            else if (a == "--size") sscanf(next().c_str(), "%dx%d", &host.width, &host.height);
            else if (a == "--landscape") host.landscape = true;
            else if (a == "--render-size") host.render_size = next();
            else if (a == "--font") next();  // (HostConfig::font is gone, 2026-10-05: the value is dropped)
            else if (a == "--fullscreen") host.fullscreen = true;
            else if (a == "--headless") host.hidden = true;
            else if (a == "--windowed") host.hidden = false;
            else if (a == "--shot") host.shots.push_back(next());
            else if (a == "--do") host.actions.push_back(next());
            else if (a == "--control") host.control_path = next();
            else if (a == "--gdb") r.gdb = next();
            else if (a == "-v") r.verbose = 1;
            else if (a == "-vv") r.verbose = 2;
            else return a == "-h" || a == "--help" ? 0 : 2;
        }
    } catch (Exit e) {
        return e.rc;
    }
    return -1;
}

int parse_viewer(int argc, const char* const* argv, soa::viewer::ViewerArgs& r) {
    auto& host = r.host;
    try {
        for (int i = 1; i < argc; i++) {
            std::string a = argv[i];
            auto next = [&]() -> std::string {
                if (i + 1 >= argc) throw Exit{2};
                return argv[++i];
            };
            if (a == "--apk-dir") r.apk_dir = next();
            else if (a == "--xapk") r.xapk_path = next();  // 380-ok: soa-viewer's options
            else if (a == "--apk") r.extra_apks.push_back(next());
            else if (a == "--download-dir") r.download_dir = next();
            else if (a == "--download-prefer") r.download_prefer = true;
            else if (a == "--lib") r.lib_path = next();
            else if (a == "--data") r.data_dir = next();
            else if (a == "--repo") r.repo = next();
            else if (a == "--guest-cpus") {
                std::string c = next();
                char* end = nullptr;
                long v = strtol(c.c_str(), &end, 10);
                if (c != "host" && (c.empty() || *end || v < 1 || v > 256)) return 2;
                r.guest_cpus = c == "host" ? 0 : (int)v;
            }
            else if (a == "--size") sscanf(next().c_str(), "%dx%d", &host.width, &host.height);
            else if (a == "--landscape") host.landscape = true;
            else if (a == "--render-size") host.render_size = next();
            else if (a == "--font") next();  // (HostConfig::font is gone, 2026-10-05: the value is dropped)
            else if (a == "--fullscreen") host.fullscreen = true;
            else if (a == "--headless") host.hidden = true;
            else if (a == "--windowed") host.hidden = false;
            else if (a == "--shot") host.shots.push_back(next());
            else if (a == "--do") host.actions.push_back(next());
            else if (a == "--control") host.control_path = next();
            else if (a == "--gdb") r.gdb = next();
            else if (a == "-v") r.verbose = 1;
            else if (a == "-vv") r.verbose = 2;
            else return a == "-h" || a == "--help" ? 0 : 2;
        }
    } catch (Exit e) {
        return e.rc;
    }
    return -1;
}

}  // namespace legacy
