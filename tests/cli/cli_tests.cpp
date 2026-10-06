// soa_cli_tests: the five programs' CLI11 command lines (port/src/core/cli.cpp,
// server/app/cli.cpp, emulator/src/cli.cpp, emulator-viewer/src/cli.cpp, webview/tools/cli.cpp)
// against the hand-written
// parsers they replaced (legacy.cpp), table-driven:
//   1. every option name each old parser knew is defined (and nothing else), except the additions
//      and the deliberate removals check_names is given, and every one of them appears in the table
//      below;
//   2. each row's command line parses to the same configuration (every field of the structs the
//      programs act on, dumped as text) and the same outcome (go on / help / error) with both;
//      rows marked `changed` are the deliberate differences (the new outcome is checked, the reason
//      printed).
// Exit status 1 on a failure. T0 (`cli`, tests/tiers.json).
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <fcntl.h>
#include <unistd.h>

#include "legacy.h"

namespace {

int g_failed = 0, g_checks = 0;
void fail(const std::string& m) {
    g_failed++;
    fprintf(stderr, "FAIL  %s\n", m.c_str());
}

// ---- the configurations as text --------------------------------------------------------------
struct Dump {
    std::ostringstream o;
    template <class T>
    Dump& f(const char* k, const T& v) {
        o << k << "=" << v << "\n";
        return *this;
    }
    Dump& f(const char* k, const std::vector<std::string>& v) {
        o << k << "=[";
        for (auto& s : v) o << "<" << s << ">";
        o << "]\n";
        return *this;
    }
};
void dump(Dump& d, const soa::server::ServerConfig& c) {
    d.f("enabled", c.enabled).f("new_player", c.new_player).f("master", c.master).f("apk", c.apk).f("db", c.db).f("seed", c.seed);
    d.f("gacha_pools", c.gacha_pools).f("has_seed_rng", c.has_seed_rng).f("seed_rng", c.seed_rng);
    d.f("start_coins", c.start_coins).f("has_clock", c.has_clock).f("clock", c.clock);  // (clock_offset: now-dependent)
    d.f("galaxy_pass", c.galaxy_pass).f("enable_events", c.enable_events).f("event_keywords", c.event_keywords);
    d.f("restore_tower", c.restore_tower).f("home3d_all", c.home3d_all).f("campaign_master_db", c.campaign_master_db);
    d.f("campaign_seed", c.campaign_seed).f("fail", c.fail).f("surprise", c.surprise).f("log_packets", c.log_packets);
    d.f("repo_roots", c.repo_roots).f("data_root", c.data_root).f("cdn_url", c.cdn_url).f("cdn_revision", c.cdn_revision);
    d.f("download_dir", c.download_dir).f("cdn_standins", c.cdn_standins).f("standin_dir", c.standin_dir).f("cdn_scratch", c.cdn_scratch);
}
void dump(Dump& d, const soa::platform370::Config& p) {
    d.f("app_version", p.app_version).f("java", p.java).f("imports", p.imports).f("clock", p.clock).f("device_clock", p.device_clock);
    d.f("patch", p.patch).f("net", p.net).f("http", p.http);
    auto& n = p.netcfg;
    d.f("server_host", n.server_host).f("server_port", n.server_port).f("http_host", n.http_host).f("http_port", n.http_port);
    d.f("lobby_host", n.lobby_host).f("lobby_port", n.lobby_port);
    for (auto& [k, v] : n.hosts) d.o << "host " << k << "=" << v << "\n";
}
void dump(Dump& d, const soa::app::HostConfig& h) {
    d.f("title", h.title).f("width", h.width).f("height", h.height).f("landscape", h.landscape).f("fullscreen", h.fullscreen);
    d.f("hidden", h.hidden).f("render_size", h.render_size).f("size_note", h.size_note).f("shots", h.shots).f("actions", h.actions);
    d.f("control_path", h.control_path);
}
// the log level the programs set from -v / -vv
int level(int verbose) { return verbose >= 2 ? 2 : verbose; }

std::string dump(const soa::SoaArgs& a) {
    Dump d;
    const soa::RunOptions& o = *a.opt;
    d.f("repo_dir", o.repo_dir);
    auto& c = o.client;
    d.f("download_dir", c.download_dir).f("download_prefer", c.download_prefer).f("standin_dir", c.standin_dir).f("standin_off", c.standin_off);
    d.f("fake_server_schema", c.fake_server_schema).f("guest_cpus", c.guest_cpus).f("memstats", c.memstats);
    dump(d, o.server);
    d.f("data_dir", a.data_dir).f("apk", a.apk_path).f("lib", a.lib_path).f("smoke", a.smoke).f("selftest", a.selftest);
    d.f("list_native", a.list_native).f("test_filter", a.test_filter);
    d.f("natives", a.natives == "all" ? std::string("route") : a.natives);  // (parse_native_set: all = route)
    d.f("server_mode", a.server_mode.empty() ? std::string("inproc") : a.server_mode);
    dump(d, a.p370);
    dump(d, a.host);
    d.f("headless", a.headless).f("gdb", a.gdb).f("log", level(a.verbose)).f("live_checks", a.live_checks);
    std::set<std::string> flags(a.server_flags.begin(), a.server_flags.end());  // (named once each, for a warning)
    d.f("server_flags", std::vector<std::string>(flags.begin(), flags.end()));
    d.f("apk_dir_given", a.apk_dir_given).f("legacy_res", a.legacy_res);
    return d.o.str();
}
std::string dump(const soa::server::app::ServerArgs& a) {
    Dump d;
    dump(d, *a.config);
    d.f("repo", a.repo).f("data", a.data).f("download_dir", a.download_dir).f("filter", a.filter).f("listen", a.listen).f("http", a.http);
    d.f("bridge_url", a.bridge_url).f("selftest", a.selftest).f("cdn_check", a.cdn_check).f("keep_open", a.keep_open_after_error);
    d.f("list_apis", a.list_apis).f("list_hooks", a.list_hooks).f("replay_dir", a.replay_dir).f("replay_out", a.replay_out);
    d.f("shuffle", a.shuffle).f("cdn_paths", a.cdn_paths).f("log", level(a.verbose));
    return d.o.str();
}
std::string dump(const soa::emu::EmuArgs& a) {
    Dump d;
    d.f("lib", a.lib_path).f("data", a.data_dir).f("download", a.download_dir).f("repo", a.repo).f("download_prefer", a.download_prefer);
    d.f("apks", a.apks).f("guest_cpus", a.guest_cpus).f("gdb", a.gdb).f("log", level(a.verbose));
    dump(d, a.p370);
    dump(d, a.host);
    return d.o.str();
}
std::string dump(const soa::viewer::ViewerArgs& a) {
    Dump d;
    d.f("apk_dir", a.apk_dir).f("xapk", a.xapk_path).f("lib", a.lib_path).f("data", a.data_dir).f("repo", a.repo);  // 380-ok: soa-viewer's options
    d.f("download", a.download_dir).f("extra_apks", a.extra_apks).f("download_prefer", a.download_prefer);
    d.f("guest_cpus", a.guest_cpus).f("gdb", a.gdb).f("log", level(a.verbose));
    dump(d, a.host);
    return d.o.str();
}
std::string dump(const soa::webview::RenderArgs& a) {
    Dump d;
    d.f("page", a.page).f("out", a.out).f("url", a.url).f("width", a.width).f("height", a.height).f("zoom", a.zoom);
    d.f("scroll", a.scroll).f("screen", a.screen).f("tap_x", a.tap_x).f("tap_y", a.tap_y);
    for (auto& [prefix, dir] : a.maps) d.o << "map <" << prefix << ">=<" << dir << ">\n";
    return d.o.str();
}

// ---- one program: the new parser and the old one on the same command line ----------------------
// Outcome classes: -1 go on, 0 help, 2 error (the old soa's --server check was a fatal(), 1: an
// error too).
int outcome(int rc) { return rc == 1 ? 2 : rc; }

struct Result {
    int rc;
    std::string config;
};
std::vector<const char*> argv_of(const std::string& prog, const std::vector<std::string>& args) {
    std::vector<const char*> v{prog.c_str()};
    for (auto& a : args) v.push_back(a.c_str());
    return v;
}

// stdout and stderr off while a new parser runs (it prints its help and its errors)
struct Quiet {
    int saved[2];
    Quiet() {
        fflush(stdout);
        fflush(stderr);
#ifdef _WIN32
        int null = open("NUL", O_WRONLY);
#else
        int null = open("/dev/null", O_WRONLY);
#endif
        for (int fd : {1, 2}) saved[fd - 1] = dup(fd), dup2(null, fd);
        close(null);
    }
    ~Quiet() {
        fflush(stdout);
        fflush(stderr);
        for (int fd : {1, 2}) dup2(saved[fd - 1], fd), close(saved[fd - 1]);
    }
};

template <class Args, class New, class Old, class Prep>
std::pair<Result, Result> run_both(const std::string& prog, const std::vector<std::string>& args, New parse_new, Old parse_old, Prep prep) {
    auto v = argv_of(prog, args);
    Args a, b;
    typename Prep::Store sa, sb;
    prep(a, sa);
    prep(b, sb);
    Result rn, ro;
    {
        Quiet q;
        rn.rc = parse_new((int)v.size(), v.data(), a, nullptr);
    }
    ro.rc = parse_old((int)v.size(), v.data(), b);
    rn.config = dump(a);
    ro.config = dump(b);
    return {rn, ro};
}

// Each Args' external storage (soa's RunOptions, soa-server's ServerConfig).
struct SoaPrep {
    struct Store {
        soa::RunOptions opt;
    };
    void operator()(soa::SoaArgs& a, Store& s) const { a.opt = &s.opt; }
};
struct ServerPrep {
    struct Store {
        soa::server::ServerConfig c;
    };
    void operator()(soa::server::app::ServerArgs& a, Store& s) const { a.config = &s.c; }
};
struct NoPrep {
    struct Store {};
    template <class A>
    void operator()(A&, Store&) const {}
};

struct Row {
    std::vector<std::string> args;
    const char* changed = nullptr;  // a deliberate difference: why (the new outcome is `want`)
    int want = -1;                  // with `changed`: the new parser's outcome
};

std::string join(const std::vector<std::string>& v) {
    std::string s;
    for (auto& a : v) s += (s.empty() ? "" : " ") + (a.find(' ') != std::string::npos || a.empty() ? "\"" + a + "\"" : a);
    return s;
}

template <class Args, class New, class Old, class Prep>
void check_program(const std::string& prog, const std::vector<Row>& rows, New parse_new, Old parse_old, Prep prep) {
    int n = 0, changed = 0;
    for (const Row& r : rows) {
        g_checks++;
        auto [rn, ro] = run_both<Args>(prog, r.args, parse_new, parse_old, prep);
        std::string what = prog + " " + join(r.args);
        if (r.changed) {
            changed++;
            if (outcome(rn.rc) != r.want) fail(what + ": new outcome " + std::to_string(rn.rc) + ", want " + std::to_string(r.want));
            else if (outcome(ro.rc) == r.want && (r.want != -1 || rn.config == ro.config))
                fail(what + ": marked changed, but the old parser agrees (drop the mark)");
            else printf("      %s: changed on purpose: %s\n", what.c_str(), r.changed);
            continue;
        }
        n++;
        if (outcome(rn.rc) != outcome(ro.rc)) {
            fail(what + ": outcome new " + std::to_string(rn.rc) + " vs old " + std::to_string(ro.rc));
            continue;
        }
        if (rn.rc == -1 && rn.config != ro.config) {
            std::istringstream a(rn.config), b(ro.config);
            std::string la, lb, diff;
            while (std::getline(a, la) && std::getline(b, lb))
                if (la != lb) diff += "\n        new " + la + "\n        old " + lb;
            fail(what + ": configurations differ:" + diff);
        }
    }
    printf("ok    %s: %d command lines parse as before (%d deliberate differences)\n", prog.c_str(), n, changed);
}

// ---- 1. the option names -----------------------------------------------------------------------
void check_names(const std::string& prog, std::vector<std::string> got, std::vector<std::string> old_list,
                 const std::vector<std::string>& added, const std::vector<std::string>& removed, const std::vector<Row>& rows) {
    g_checks++;
    std::set<std::string> want(old_list.begin(), old_list.end());
    want.erase("-vv");  // (-v counted: -vv is two)
    want.insert(added.begin(), added.end());
    for (auto& r : removed) want.erase(r);  // gone on purpose (their rows are marked `changed`)
    std::set<std::string> have(got.begin(), got.end());
    for (auto& w : want)
        if (!have.count(w)) fail(prog + ": " + w + " (the old parser had it) isn't defined");
    for (auto& h : have)
        if (!want.count(h)) fail(prog + ": " + h + " is defined but neither the old parser's nor a listed addition");
    // every option of the old parser in at least one row
    for (auto& o : old_list) {
        if (o == "-h" || o == "--help") continue;
        bool used = false;
        for (auto& r : rows)
            for (auto& a : r.args) used = used || a == o || a.rfind(o + "=", 0) == 0;
        if (!used) fail(prog + ": " + o + " is in no table row");
    }
    printf("ok    %s: %zu option names (%zu added, %zu removed)\n", prog.c_str(), have.size(), added.size(), removed.size());
}

}  // namespace

int main() {
    using V = std::vector<std::string>;
    // ---- the old parsers' option lists (transcribed from their loops, 3bfa883) ----
    const V soa_old = {"--apk-dir", "--apk", "--server", "--http", "--lobby", "--map-host", "--device-clock", "--no-patch", "--natives",
                       "--lib", "--data", "--size", "--smoke", "--selftest", "--no-native", "--hires", "--legacy-res", "--render-size",
                       "--font", "--fullscreen", "--headless", "--windowed", "--landscape", "--shot", "--do", "--control", "--gdb",
                       "--download-dir", "--download", "--download-prefer", "--fake-server", "--fake-server-schema", "--memstats",
                       "--live-check", "--repo", "--standin-assets", "--restore", "--restore-tower", "--home3d-all", "--clock",
                       "--enable-events", "--galaxy-pass", "--new-player", "--surprise", "--db", "--master", "--gacha-pools", "--seed",
                       "--campaign-master-db", "--campaign-seed", "--fail", "--log-packets", "--seed-rng", "--guest-cpus",
                       "--event-keywords", "--start-coins", "--list-native", "-v", "-vv", "-h", "--help"};
    const V server_old = {"--selftest", "--shuffle", "--replay", "--out", "--list-apis", "--list-hooks", "--repo", "--listen", "--http",
                          "--bridge-url", "--log-packets", "--data", "--db", "--master", "--apk", "--gacha-pools", "--seed",
                          "--seed-rng", "--new-player", "--clock", "--start-coins", "--galaxy-pass", "--enable-events",
                          "--event-keywords", "--restore-tower", "--home3d-all", "--download-dir", "--download", "--cdn-url",
                          "--standin-assets", "--cdn-scratch", "--cdn-check", "--campaign-master-db", "--campaign-seed", "--fail",
                          "--surprise", "--keep-open-after-error", "-v", "-h", "--help"};
    const V emu_old = {"--lib", "--apk", "--data", "--download-dir", "--download", "--download-prefer", "--repo", "--device-clock",
                       "--no-patch", "--server", "--http", "--lobby", "--map-host", "--guest-cpus", "--size", "--landscape",
                       "--render-size", "--font", "--fullscreen", "--headless", "--windowed", "--shot", "--do", "--control", "--gdb",
                       "-v", "-vv", "-h", "--help"};
    const V viewer_old = {"--apk-dir", "--xapk", "--apk", "--download-dir", "--download-prefer", "--lib", "--data", "--repo",  // 380-ok: soa-viewer's options
                          "--guest-cpus", "--size", "--landscape", "--render-size", "--font", "--fullscreen", "--headless", "--windowed",
                          "--shot", "--do", "--control", "--gdb", "-v", "-vv", "-h", "--help"};
    // (soa-webview-render's loop, 61f0c08: no -h / --help; any other word was PAGE or OUT)
    const V render_old = {"--width", "--height", "--zoom", "--scroll", "--screen", "--url", "--map", "--tap"};

    // Options removed on purpose since: --font (2026-10-05; the fonts are built in); soa's
    // --fake-server (2026-10-05; the canned responses were retired, docs/unimplemented-apis.md step 9).
    const V kRemovedFont = {"--font"};
    const V kRemovedSoa = {"--font", "--fake-server"};
    // Options added since: --stamina-heal-time (2026-10-06, both programs' server options; a test
    // switch: tests/diff runs with 0, no stamina regeneration).
    const V kAddedServer = {"--stamina-heal-time"};

    // ---- the rows: every option, its value forms, repeats, order, and the error paths ----
    const std::vector<Row> client_common = {
        {{}},
        {{"--help"}},
        {{"-h"}},
        {{"--data", "/tmp/d"}},
        {{"--data", "a", "--data", "b"}},  // the last wins
        {{"--lib", "/x/libSOA.so"}},
        {{"--repo", "/src"}},
        {{"--guest-cpus", "4"}},
        {{"--guest-cpus", "host"}},
        {{"--guest-cpus", "256"}},
        {{"--guest-cpus", "0"}},
        {{"--guest-cpus", "257"}},
        {{"--guest-cpus", "4x"}},
        {{"--guest-cpus", ""}},
        {{"--guest-cpus"}},
        {{"--size", "729x1296"}},
        {{"--size", "bad"}},
        {{"--landscape"}},
        {{"--render-size", "window"}},
        {{"--render-size", "1080x1920"}},
        {{"--fullscreen"}},
        {{"--font", "/f.ttf"}, "--font is gone: the fonts are built in (cmake/fonts.cmake)", 2},
        {{"--font", "none"}, "--font is gone: the fonts are built in (cmake/fonts.cmake)", 2},
        {{"--headless"}},
        {{"--windowed"}},
        {{"--headless", "--windowed"}},
        {{"--windowed", "--headless"}},
        {{"--shot", "5:/tmp/a.png"}},
        {{"--shot", "5:a.png", "--shot", "9:b.png"}},
        {{"--shot", "5:a.png", "stray"}},
        {{"--do", "3:tap:100:200", "--do", "4:text:日本語 テキスト", "--do", "9:quit"}},
        {{"--control", "/tmp/fifo"}},
        {{"--control", "tcp:127.0.0.1:5555"}},
        {{"--gdb", "127.0.0.1:2345"}},
        {{"-v"}},
        {{"-vv"}},
        {{"--bogus"}},
        {{"stray"}},
        {{"--data"}},
        {{"--data", "--headless"}},  // (a value that looks like an option: taken as the value, as before)
        {{"--do"}},
    };
    // download and the phone's network (soa, soa-emu)
    const std::vector<Row> download = {
        {{"--download-dir", "work/download-3.7.0"}},
        {{"--download", "SOA-3.7.0-canonical-data.zip"}},
        {{"--download", "a", "--download-dir", "b"}},
        {{"--download-prefer"}},
    };
    const std::vector<Row> phone = {
        {{"--device-clock", "2021-05-25 12:00:00"}},
        {{"--device-clock", "host"}},
        {{"--no-patch"}},
        {{"--http", "127.0.0.1:44380"}},
        {{"--http", "Host.Example:80"}},
        {{"--http", "nohost"}},
        {{"--http", ":80"}},
        {{"--http", "h:0"}},
        {{"--http", "h:x"}},
        {{"--lobby", "10.0.0.2:4001"}},
        {{"--lobby", "nolobby"}},
        {{"--map-host", "Example.COM=1.2.3.4", "--map-host", "other.host"}},
        {{"--map-host", "a.b=", "--map-host", "a.b=5.6.7.8"}},
    };
    auto concat = [](std::initializer_list<const std::vector<Row>*> parts) {
        std::vector<Row> out;
        for (auto* p : parts) out.insert(out.end(), p->begin(), p->end());
        return out;
    };

    // soa-server's and soa's server options
    const std::vector<Row> server_opts = {
        {{"--db", "/tmp/s.sqlite3"}},
        {{"--master", "data/basmaster-3.7.0.sqlite3"}},
        {{"--gacha-pools", "data/gacha_pools.sqlite3"}},
        {{"--seed", "data/saves/seed/Game.xml"}},
        {{"--seed-rng", "1"}},
        {{"--seed-rng", "605"}},
        {{"--seed-rng", "0x10"}},
        {{"--seed-rng", "18446744073709551615"}},
        {{"--new-player"}},
        {{"--clock", "2026-10-01 12:00:05"}},
        {{"--clock", "2021-05-25"}},
        {{"--clock", "1621944000"}},
        {{"--clock", "soon"}},
        {{"--start-coins", "0"}},
        {{"--start-coins", "4294967295"}},
        {{"--galaxy-pass"}},
        {{"--enable-events"}},
        {{"--event-keywords", "水着,夏,!福袋"}},
        {{"--restore-tower"}},
        {{"--home3d-all"}},
        {{"--campaign-master-db", "data/basmaster-3.7.0.sqlite3", "--campaign-seed", "mf01_001"}},
        {{"--fail", "MissionStart:9001,GachaDraw:2"}},
        {{"--surprise"}},
        {{"--log-packets", "/tmp/packets"}},
        {{"--standin-assets", "standin-assets"}},
        {{"--standin-assets", "off"}},
        {{"--standin-assets", "0"}},
        // a replay corpus' options (server/tests/replay/seeded/options) as one command line
        {{"--master", "data/basmaster-3.7.0.sqlite3", "--seed", "data/saves/seed/Game.xml", "--seed-rng", "1", "--clock",
          "2026-10-01 12:00:05", "--campaign-seed", "mf01_001", "--download-dir", "work/download-3.7.0"}},
    };

    // ---- soa ----
    const std::vector<Row> soa_only = {
        {{"--apk", "/x/game.apk"}},
        {{"--apk-dir", "work/extracted/xapk"}},  // 380-ok: soa-viewer's options
        {{"--apk-dir"}},
        {{"--server", "inproc"}},
        {{"--server", "127.0.0.1"}},
        {{"--server", "127.0.0.1:44300", "--http", "127.0.0.1:44380", "--map-host", "cdn.example"}},
        {{"--server", "host:0"}},
        {{"--natives", "route"}},
        {{"--natives", "all"}},
        {{"--natives", "none"}},
        {{"--no-native"}},
        {{"--no-native", "--natives", "route"}},
        {{"--natives", "route", "--no-native"}},
        {{"--smoke"}},
        {{"--selftest"}},
        {{"--selftest", "server/"}},
        {{"--selftest", "--headless"}},
        {{"--selftest", "wire/", "--windowed"}},
        {{"--hires"}},
        {{"--legacy-res"}},
        {{"--fake-server-schema", "/tmp/schema.txt"}},
        {{"--fake-server", "port/fakeapi/responses"}, "--fake-server is gone: the canned responses were retired (docs/unimplemented-apis.md step 9)", 2},
        {{"--memstats"}},
        {{"--memstats", "30"}},
        {{"--memstats", "--headless"}},
        {{"--memstats", "0"}},
        {{"--memstats", "86401"}},
        {{"--memstats", "5s"}},
        {{"--live-check", "lib_sqlite"}},
        {{"--live-check", "a,b:every=3:trace", "--live-check", "c:out=/tmp/x"}},
        {{"--restore"}},
        {{"--server", "inproc", "--db", "a.db", "--surprise", "--galaxy-pass"}},
        {{"--server", "10.0.0.1:44300", "--clock", "2021-05-25 12:00:00", "--fail", "X:1"}},
        {{"--start-coins", "-1"}},
        {{"--start-coins", "4294967296"}},
        {{"--start-coins", "x"}},
        {{"--seed-rng", "x"}},
        {{"--seed-rng", ""}},
        {{"--headless", "--data", "/tmp/d", "--size", "810x1440", "--control", "/tmp/f", "--seed-rng", "1", "--clock",
          "2026-10-01 12:00:05", "--log-packets", "/tmp/p", "--download-dir", "work/download-3.7.0", "--list-native"}},
        {{"--list-native"}},
        {{"--server", ""}},  // (an error: the old one after the loop, with fatal())
        {{"--http", "a:b:80"}, "--http / --lobby HOST:PORT are soa-emu's rule in both programs now (platform370/cli.h): a "
                               "value with two ':' is an error (soa took host \"a:b\")", 2},
        {{"-vv", "-v"}, "-v counts: -vv -v is trace (the old loop's last -v / -vv won: debug)", -1},
        {{"--server", "[::1]:44300", "--http", "[::1]:44380"}, "an IPv6 address in brackets, [V6]:PORT (platform370/cli.h; the old "
                                                              "one took host \"[::1]:44300\" and refused the --http)", -1},
    };
    std::vector<Row> soa_rows = concat({&client_common, &download, &phone, &server_opts, &soa_only});

    // ---- soa-server ----
    const std::vector<Row> server_only = {
        {{}},
        {{"--help"}},
        {{"-h"}},
        {{"--listen", "0.0.0.0:44300", "--http", "0.0.0.0:44380"}},
        {{"--listen", "[::1]:44300", "--http", "[::1]:44380"}},
        {{"--bridge-url", "http://127.0.0.1:44380/bridge", "--cdn-url", "http://127.0.0.1:44380"}},
        {{"--cdn-scratch", "/tmp/cdn"}},
        {{"--keep-open-after-error"}},
        {{"--repo", "/src", "--data", "/tmp/sd"}},
        {{"--apk", "/x/game.apk"}},
        {{"--download", "/x/dl"}},
        {{"--download-dir", "/x/dl"}},
        {{"--selftest"}},
        {{"--selftest", "cdn|wire"}},
        {{"--selftest", "-v"}},
        {{"--selftest", "--shuffle", "7"}},
        {{"--shuffle", "0x10"}},
        {{"--replay", "server/tests/replay/seeded", "--out", "/tmp/out", "--seed-rng", "1"}},
        {{"--list-apis"}},
        {{"--list-hooks"}},
        {{"--cdn-check"}},
        {{"--cdn-check", "/download/x/Android/version.bin", "/master"}},
        {{"--cdn-check", "/a", "-v"}},
        {{"-v"}},
        {{"--bogus"}},
        {{"stray"}},
        {{"--db"}},
        {{"--start-coins", "x"}, "--start-coins is soa's rule in both programs now (soaserver/cli.h): a value that isn't "
                                 "a number in 0..4294967295 is an error (soa-server took strtoul's prefix: 0)", 2},
        {{"--start-coins", "-1"}, "as --start-coins x (soa-server wrapped it to 4294967295)", 2},
        {{"--seed-rng", "x"}, "--seed-rng is soa's rule in both programs now: a value that isn't a number is an error "
                              "(soa-server took 0)", 2},
    };
    std::vector<Row> server_rows = concat({&server_opts, &server_only});

    // ---- soa-emu ----
    const std::vector<Row> emu_only = {
        {{"--apk", "a.apk"}},
        {{"--apk", "a.apk", "--apk", "b.apk"}},
        {{"--server", "127.0.0.1"}},
        {{"--server", "127.0.0.1:44301"}},
        {{"--server", "Host:9", "--server", "other"}, "--server given twice: the last one wins whole (the old loop kept the "
                                                       "first one's port when the second had none)", -1},
        {{"--server", ":1"}},
        {{"--server", "h:0"}},
        {{"--server", "a:b:c"}},
        {{"--server", "[::1]:44301"}, "an IPv6 address in brackets, [V6]:PORT (platform370/cli.h; the old one took host "
                                      "\"[::1]:44301\")", -1},
        {{"-vv", "-v"}, "-v counts: -vv -v is trace (the old loop's last -v / -vv won: debug)", -1},
    };
    std::vector<Row> emu_rows = concat({&client_common, &download, &phone, &emu_only});

    // ---- soa-viewer ----
    const std::vector<Row> viewer_only = {
        {{"--xapk", "apk/game.xapk"}},  // 380-ok: soa-viewer's options
        {{"--apk-dir", "work/extracted/xapk"}},  // 380-ok: soa-viewer's options
        {{"--xapk", "a.xapk", "--apk-dir", "d"}},  // (main refuses both); 380-ok: soa-viewer's options
        {{"--apk", "a.apk", "--apk", "b.apk"}},
        {{"--download-dir", "work/download-3.7.0"}},
        {{"--download-dir", "work/download-3.7.0", "--download-prefer"}},
        {{"--download", "work/download-3.7.0"}, "soa-viewer takes --download PATH too, as the other programs (the shared "
                                                 "option; the old loop had only --download-dir)", -1},
        {{"-vv", "-v"}, "-v counts: -vv -v is trace (the old loop's last -v / -vv won: debug)", -1},
    };
    std::vector<Row> viewer_rows = concat({&client_common, &viewer_only});

    // ---- soa-webview-render ----
    const char* kStrictNumber = "a value that isn't a whole number (W / H: at least 1) is an error, as the other programs' "
                                "numbers (the old loop took atoi's prefix, 0 when none: a 0-wide view)";
    const std::vector<Row> render_rows = {
        {{"p.html", "o.png"}},
        {{"-", "o.png"}},  // (stdin)
        {{"p.html", "o.png", "--width", "810", "--height", "1092", "--screen", "--scroll", "3000"}},
        {{"--width", "810", "p.html", "--screen", "o.png", "--height", "1092"}},  // options anywhere
        {{"p.html", "o.png", "--width", "1", "--width", "2"}},                   // the last wins
        {{"p.html", "o.png", "--height", "7", "--height", "8"}},
        {{"p.html", "o.png", "--zoom", "1"}},
        {{"p.html", "o.png", "--zoom", "2.625"}},
        {{"p.html", "o.png", "--zoom", "0"}},  // (the page takes 1)
        {{"p.html", "o.png", "--zoom", "-3.5"}},
        {{"p.html", "o.png", "--scroll", "-5"}},
        {{"p.html", "o.png", "--screen", "--screen"}},
        {{"p.html", "o.png", "--url", "http://soa-local.invalid/notice/index.html"}},
        {{"p.html", "o.png", "--url", "a", "--url", "b"}},
        {{"p.html", "o.png", "--url", "--screen"}},  // (a value that looks like an option: taken as the value, as before)
        {{"p.html", "o.png", "--map", "http://soa-local.invalid/=webroot/"}},
        {{"p.html", "o.png", "--map", "http://a/=x", "--map", "http://b/=y=z", "--map", "=d", "--map", "p="}},
        {{"p.html", "o.png", "--map", "nodir"}},
        {{"p.html", "o.png", "--tap", "360:460"}},
        {{"p.html", "o.png", "--tap", "-1:5"}},
        {{"p.html", "o.png", "--tap", "1:2", "--tap", "3:4"}},
        {{"p.html", "o.png", "--tap", "1"}},
        {{"p.html", "o.png", "--tap", "a:b"}},
        {{}},
        {{"p.html"}},
        {{"p.html", "o.png", "extra"}},
        {{"p.html", "o.png", "--width"}},
        {{"p.html", "o.png", "--map"}},
        {{"p.html", "o.png", "--tap"}},
        {{"--screen"}},
        {{"--help"}, "--help prints the options and exits 0 (the old loop took it as PAGE: usage, 2)", 0},
        {{"-h"}, "as --help", 0},
        {{"p.html", "o.png", "--help"}, "as --help (the old loop took it as a third word: 2)", 0},
        {{"--bogus", "o.png"}, "an unknown option is an error, as in the other programs (the old loop took it as PAGE)", 2},
        {{"p.html", "--bogus"}, "as --bogus o.png (the old loop took it as OUT)", 2},
        {{"p.html", "o.png", "--width", "4x"}, kStrictNumber, 2},
        {{"p.html", "o.png", "--width", "x"}, kStrictNumber, 2},
        {{"p.html", "o.png", "--width", "0"}, kStrictNumber, 2},
        {{"p.html", "o.png", "--height", "-1"}, kStrictNumber, 2},
        {{"p.html", "o.png", "--scroll", ""}},  // (0 both: atoi's, and CLI11's empty value)
        {{"p.html", "o.png", "--width", ""}, kStrictNumber, 2},
        {{"p.html", "o.png", "--zoom", "abc"}, "a --zoom that isn't a number is an error (the old loop took atof's 0: the page's 1)", 2},
        {{"p.html", "o.png", "--tap", "1:2x"}, "--tap X:Y is two whole numbers (the old sscanf took a prefix)", 2},
        {{"p.html", "o.png", "--width=810"}, "--OPTION=VALUE is accepted, as in the other programs (the old loop took it as a "
                                             "third word: 2)", -1},
    };

    // ---- 1. names ----
    {
        std::vector<std::string> names;
        const char* argv[] = {"x"};
        {
            soa::RunOptions o;
            soa::SoaArgs a;
            a.opt = &o;
            soa::parse_soa_args(1, argv, a, &names);
            check_names("soa", names, soa_old, kAddedServer, kRemovedSoa, soa_rows);
        }
        {
            soa::server::ServerConfig c;
            soa::server::app::ServerArgs a;
            a.config = &c;
            soa::server::app::parse_args(1, argv, a, &names);
            check_names("soa-server", names, server_old, kAddedServer, {}, server_rows);
        }
        {
            soa::emu::EmuArgs a;
            soa::emu::parse_args(1, argv, a, &names);
            check_names("soa-emu", names, emu_old, {}, kRemovedFont, emu_rows);
        }
        {
            soa::viewer::ViewerArgs a;
            soa::viewer::parse_args(1, argv, a, &names);
            check_names("soa-viewer", names, viewer_old, {"--download"}, kRemovedFont, viewer_rows);
        }
        {
            soa::webview::RenderArgs a;
            Quiet q;  // (PAGE and OUT are required: an error without them)
            soa::webview::parse_render_args(1, argv, a, &names);
            check_names("soa-webview-render", names, render_old, {"-h", "--help"}, {}, render_rows);
        }
    }

    // ---- 2. the rows ----
    check_program<soa::SoaArgs>("soa", soa_rows, soa::parse_soa_args, legacy::parse_soa, SoaPrep{});
    check_program<soa::server::app::ServerArgs>("soa-server", server_rows, soa::server::app::parse_args, legacy::parse_server, ServerPrep{});
    check_program<soa::emu::EmuArgs>("soa-emu", emu_rows, soa::emu::parse_args, legacy::parse_emu, NoPrep{});
    check_program<soa::viewer::ViewerArgs>("soa-viewer", viewer_rows, soa::viewer::parse_args, legacy::parse_viewer, NoPrep{});
    check_program<soa::webview::RenderArgs>("soa-webview-render", render_rows, soa::webview::parse_render_args, legacy::parse_render,
                                            NoPrep{});

    printf("cli: %s (%d checks, %d failed)\n", g_failed ? "FAIL" : "PASS", g_checks, g_failed);
    return g_failed ? 1 : 0;
}
