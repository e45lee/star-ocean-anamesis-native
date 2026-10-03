// Star Ocean: anamnesis desktop host. Loads the Android libSOA.so under an ARM64 JIT and
// drives it like Android's NativeActivity would. The window, input, audio, the activity bring-up
// and the main loop are the runtime's desktop host loop (runtime/src/app/host.h).
//
// The client is the 3.7.0 online build, from the 3.7.0 APK, on the 3.7.0 platform layer
// (platform370/), with two server modes: --server inproc (the default; the local server library
// answers through the FakeApiCaller route) and --server HOST[:PORT] (the client's own
// NetworkApiCaller talks to soa-server over TCP and HTTP). The natives are the route's hooks and
// the port's own; the families are being rebuilt (docs/history/PLAN-rebase-370.md revision 2). Options:
// client and server groups (core/options.h, `soa --help`).
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cmath>
#include <chrono>
#include <functional>
#include <mutex>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include <thread>

#include "android/ndk.h"
#include "app/host.h"
#include "android/platform.h"
#include "core/cpu.h"
#include "core/device.h"
#include "core/hle.h"
#include "core/loader.h"
#include "core/log.h"
#include "core/options.h"
#include "core/paths.h"
#include "core/profile.h"
#include "core/vfs.h"
#include "jni/jvm.h"
#include "native/common/native.h"
#include "native/common/port_debug.h"
#include "native/common/test.h"
#include "platform370/platform370.h"

using namespace soa;
namespace soa {
void install_traces(LoadedLib& lib);
}

namespace {

bool extract_lib(const std::string& apk, const std::string& out) {
    ZipArchive z;
    if (!z.open(apk)) return false;
    auto* e = z.find("lib/arm64-v8a/libSOA.so");
    if (!e) return false;
    std::vector<uint8_t> data;
    if (!z.extract(*e, data)) return false;
    std::ofstream o(out, std::ios::binary);
    o.write((const char*)data.data(), data.size());
    return o.good();
}

bool file_exists(const std::string& p) {
    struct stat st;
    return stat(p.c_str(), &st) == 0;
}

void usage() {
    fprintf(stderr,
            "usage: soa [options]\n"
            "The 3.7.0 client on the desktop (port/README.md), with the game server in-process (--server inproc,\n"
            "the default) or soa-server (--server HOST[:PORT]).\n"
            "\n"
            "General:\n"
            "  -h, --help      this text\n"
            "  --repo DIR      the source checkout to read repo files from (master DBs, seed saves, gacha pools,\n"
            "                  fakeapi responses, work/...; env SOA_REPO); default: found from the executable\n"
            "  -v / -vv        verbose / trace logging\n"
            "\n"
            "Client options (the 3.7.0 client and its emulated phone):\n"
            "  --apk FILE      the 3.7.0 APK (default <repo>/apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk)\n"
            "  --lib PATH      the libSOA.so (default: lib/arm64-v8a/libSOA.so of the APK, extracted once into\n"
            "                  DATA/libSOA-3.7.0.so; else <repo>/work/libSOA-3.7.0.so)\n"
            "  --data DIR      the phone's data dir: game data, saves, and in-process the server's state\n"
            "                  (default ~/.local/share/soa-linux-370)\n"
            "  --download-dir DIR  the client's asset fallback for builtin_data/ files the APK lacks (the online\n"
            "                  game's downloaded tree; env SOA_DOWNLOAD_DIR, SOA_DOWNLOAD_PREFER=1). Required with\n"
            "                  --server inproc, whose CDN serves it too (default <repo>/work/download-3.7.0); off by\n"
            "                  default with --server HOST, whose client downloads from soa-server's CDN\n"
            "  --standin-assets DIR|off  made-up stand-in files (e.g. lost gacha banners) for builtin_data/ assets\n"
            "                  that neither the APK nor --download-dir have; --server inproc defaults it to\n"
            "                  standin-assets and its CDN serves them (env SOA_STANDIN_ASSETS; off / 0 = none)\n"
            "  --device-clock \"YYYY-MM-DD HH:MM:SS\"|host  the phone's clock (default host; platform370)\n"
            "  --no-patch      no service_stop_day patch (platform370/src/patch_370.cpp)\n"
            "  --guest-cpus N|host  CPUs the game sees (sysconf, /sys/devices/system/cpu/present; default 8, an\n"
            "                  octa-core phone); the engine starts N - 2 dynamics and N resource workers\n"
            "                  (env SOA_GUEST_CPUS)\n"
            "  --natives route|none  native replacements (env SOA_NATIVES; default route: every registered one,\n"
            "                  i.e. the in-process route's FakeApiCaller hooks (not with --server HOST) and the\n"
            "                  port's own hooks; \"all\" is a synonym). none = --no-native\n"
            "  --no-native     the same as --natives none\n"
            "  --http HOST:PORT  (--server HOST) soa-server's --http (default <server host>:44380)\n"
            "  --lobby HOST:PORT (--server HOST) where the client's lobby connections (port 4001) go\n"
            "  --map-host NAME[=ADDR]  (--server HOST) also resolve NAME to ADDR (default the server host)\n"
            "  Window:\n"
            "  --size WxH      window size (default: portrait 9:16 at 90%% of the desktop height)\n"
            "  --landscape     default to a 16:9 landscape window (the game is designed for portrait)\n"
            "  --render-size S the window's surface: 'desktop' (default: the window's aspect ratio scaled to fill the\n"
            "                  desktop, so resizing/fullscreen stays sharp), 'window' (the initial window size) or WxH\n"
            "  --fullscreen    start in (desktop) fullscreen\n"
            "  --font PATH     the on-screen text box's font (env SOA_FONT; default: a system Japanese font; 'none': off)\n"
            "  --headless      don't show the window; it still renders at the same size, so screenshots, --shot/--do\n"
            "                  and --control work the same (env SOA_HEADLESS=1; --selftest is headless by default)\n"
            "  --windowed      show the window even with SOA_HEADLESS=1 or --selftest (env SOA_HEADLESS=0)\n"
            "  --hires, --legacy-res  no effect (the game renders at its own resolution)\n"
            "  Driving and testing:\n"
            "  --shot S:PATH   save a screenshot S seconds after start (repeatable; F12 saves one any time)\n"
            "  --do S:ACTION   scripted input S seconds after start (repeatable): tap:X:Y, drag:X1:Y1:X2:Y2,\n"
            "                  wheel:X:Y:DY (pinch), back, text:STRING, shot:PATH, quit\n"
            "  --control FIFO  read the same commands, one per line, from a named pipe (plus the port's\n"
            "                  phase:/call:/mission:/uiset:/clock:/debugwin:/memstats commands, port_debug.cpp)\n"
            "  --selftest [F]  the self-tests (tests matching F) on the booted game, no natives installed\n"
            "  --smoke         load the library, run a quick self-test and exit\n"
            "  --list-native   print the native replacements (symbol, note) and exit\n"
            "  --apk-dir DIR   ignored (kept for old scripts; the port runs the 3.7.0 APK, --apk)\n"
            "\n"
            "Server options (the local server's rules and state; only with --server inproc: with --server HOST\n"
            "give them to soa-server, which takes the same flags):\n"
            "  --server inproc|HOST[:PORT]  the game server. inproc (default): the local server library answers\n"
            "                  in-process through the FakeApiCaller route, its CDN in memory (state in\n"
            "                  DATA/server.sqlite3); HOST[:PORT]: the client's own NetworkApiCaller talks to\n"
            "                  soa-server's --listen (default port 44300), production-game.so-ana.com resolving to\n"
            "                  HOST (platform370's network glue)\n"
            "  --db FILE       the state DB (default DATA/server.sqlite3; env SOA_SERVER_DB)\n"
            "  --master FILE   the 3.7.0 master DB (default data/basmaster-3.7.0.sqlite3; env SOA_SERVER_MASTER)\n"
            "  --seed FILE     the save a new state is seeded from, e.g. a 3.7.0 or offline Game.xml; an existing\n"
            "                  state DB keeps its player (env SOA_SERVER_SEED)\n"
            "  --game-xml FILE the last seed fallback (default DATA/data/shared_prefs/Game.xml; env SOA_SERVER_GAME_XML)\n"
            "  --seed-rng N    fixed RNG seed (default the time; env SOA_SERVER_SEED_RNG)\n"
            "  --new-player    start without a player: the new-player tutorial (env SOA_RESTORE_NEW_PLAYER=1)\n"
            "  --clock \"YYYY-MM-DD HH:MM:SS\"  the server's clock starts at that time and runs on (env SOA_CLOCK);\n"
            "                  without it, event terms replay the calendar (server::event_now)\n"
            "  --start-coins N free coins a new local player starts with (default 300000; env SOA_START_COINS);\n"
            "                  an existing state DB keeps its balance\n"
            "  --galaxy-pass   the local player has the Galaxy Pass, renewed when it runs out (+2 deep space\n"
            "                  ships; env SOA_GALAXY_PASS=1)\n"
            "  --enable-events also open, all year, every event area and gacha banner whose name matches\n"
            "                  --event-keywords, assets permitting (env SOA_ENABLE_EVENTS=1)\n"
            "  --event-keywords \"a,b,!c\"  names to match (\"!\" excludes); default: the summer events\n"
            "                  \"水着,夏,サマー,!福袋\" (env SOA_EVENT_KEYWORDS)\n"
            "  --restore-tower open the tower mode, which 3.7.0 had closed: the server serves it and the client's\n"
            "                  tower hooks open the menu (env SOA_RESTORE_TOWER=1)\n"
            "  --campaign-master-db FILE, --campaign-seed LABEL, --fail M:CODE[,..], --surprise  (env SOA_MASTER_DB,\n"
            "                  SOA_CAMPAIGN_SEED, SOA_SERVER_FAIL, SOA_SERVER_SURPRISE=1)\n"
            "  --log-packets DIR  log every request and reply as soa-server --log-packets does (DIR/packets.log,\n"
            "                  the reply bodies and battle logs as DIR/<n>-<name>.*; env SOA_LOG_PACKETS)\n");
}

}  // namespace

namespace soa::server_port {
void config_from_options(const std::string& data_dir);  // native/api/server_adapters.h
bool start_inproc_cdn(std::string* err);                // native/api/server_cdn.cpp
}

int main(int argc, char** argv) {
    signal(SIGPIPE, SIG_IGN);
    const char* home = getenv("HOME");
    // A data dir of its own: the old offline-build port's ~/.local/share/soa-linux holds a cached
    // libSOA.so of that build and its save.
    std::string data_dir = std::string(home ? home : ".") + "/.local/share/soa-linux-370";
    std::string apk_path, lib_path;
    bool smoke = false, selftest = false;
    // --natives (SOA_NATIVES): route (every registered native) or none.
    NativeSet natives = NativeSet::Route;
    bool natives_given = false;
    // --server: "inproc" (default) or HOST[:PORT].
    std::string server_mode;
    bool server_given = false;
    // The 3.7.0 platform layer (platform370/README.md); net/http only with --server HOST.
    platform370::Config p370;
    std::string test_filter;
    int width = 0, height = 0;  // default: portrait, sized from the desktop
    bool landscape = false;
    std::string render_size = "desktop";
    std::string font;  // --font
    bool fullscreen = false;
    int headless = -1;  // -1: not given (SOA_HEADLESS, else headless only for --selftest)
    std::vector<std::string> shots, actions;
    std::string control_path;
    RunOptions& opt = mutable_options();  // CLI first, then the SOA_* env vars as fallback inputs
    ServerOptions& srv = opt.server;
    std::vector<std::string> server_flags;  // server options given on the command line (for the --server HOST warning)
    // The runtime's calls into this frontend (runtime/src/android/platform.h).
    app::install_host_hooks();
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        auto next = [&]() -> std::string {
            if (i + 1 >= argc) {
                usage();
                exit(2);
            }
            return argv[++i];
        };
        if (a == "--apk-dir") {
            next();
            LOGW("main", "--apk-dir is ignored: the rebased port runs the 3.7.0 APK (--apk FILE)");
        }
        else if (a == "--apk") apk_path = next();
        else if (a == "--server") server_mode = next(), server_given = true;
        else if (a == "--http" || a == "--lobby") {
            std::string v = next();
            size_t c = v.rfind(':');
            int port = c == std::string::npos ? 0 : atoi(v.c_str() + c + 1);
            if (c == std::string::npos || c == 0 || port <= 0) {
                fprintf(stderr, "%s: expected HOST:PORT, got \"%s\"\n", a.c_str(), v.c_str());
                return 2;
            }
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
            if (!parse_native_set(v, natives)) {
                fprintf(stderr, "--natives: expected route or none, got \"%s\"\n", v.c_str());
                return 2;
            }
            natives_given = true;
        }
        else if (a == "--lib") lib_path = next();
        else if (a == "--data") data_dir = next();
        else if (a == "--size") sscanf(next().c_str(), "%dx%d", &width, &height);
        else if (a == "--smoke") smoke = true;
        else if (a == "--selftest") {
            selftest = true;
            if (i + 1 < argc && argv[i + 1][0] != '-') test_filter = argv[++i];
        }
        else if (a == "--no-native") natives = NativeSet::None, natives_given = true;
        else if (a == "--hires") {}  // no effect (kept for compatibility; see usage)
        else if (a == "--legacy-res") LOGW("main", "--legacy-res has no effect: the game renders at its own resolution (no --hires natives since the rebase's revision 2)");
        else if (a == "--render-size") render_size = next();
        else if (a == "--font") font = next();
        else if (a == "--fullscreen") fullscreen = true;
        else if (a == "--headless") headless = 1;
        else if (a == "--windowed") headless = 0;
        else if (a == "--landscape") landscape = true;
        else if (a == "--shot") shots.push_back(next() );
        else if (a == "--do") actions.push_back(next());
        else if (a == "--control") control_path = next();
        else if (a == "--download-dir") opt.client.download_dir = next();
        else if (a == "--repo") opt.repo_dir = next();
        else if (a == "--standin-assets") {
            std::string d = next();
            if (d == "off" || d == "0") opt.client.standin_off = true;
            else opt.client.standin_dir = d;
        }
        // ---- server options (soa-server's flags; core/options.h ServerOptions) ----
        else if (a == "--restore") {
            fprintf(stderr, "soa: --restore is gone: the in-process server is the default (--server inproc)\n");
            return 2;
        }
        else if (a == "--restore-tower") srv.restore_tower = true, server_flags.push_back(a);
        else if (a == "--clock") {
            std::string c = next();
            if (!set_clock(srv, c)) {
                fprintf(stderr, "--clock: expected \"YYYY-MM-DD HH:MM:SS\", got \"%s\"\n", c.c_str());
                return 2;
            }
            server_flags.push_back(a);
        }
        else if (a == "--enable-events") srv.enable_events = true, server_flags.push_back(a);
        else if (a == "--galaxy-pass") srv.galaxy_pass = true, server_flags.push_back(a);
        else if (a == "--new-player") srv.new_player = true, server_flags.push_back(a);
        else if (a == "--surprise") srv.surprise = true, server_flags.push_back(a);
        else if (a == "--db") srv.db = next(), server_flags.push_back(a);
        else if (a == "--master") srv.master = next(), server_flags.push_back(a);
        else if (a == "--seed") srv.seed = next(), server_flags.push_back(a);
        else if (a == "--game-xml") srv.game_xml = next(), server_flags.push_back(a);
        else if (a == "--campaign-master-db") srv.campaign_master_db = next(), server_flags.push_back(a);
        else if (a == "--campaign-seed") srv.campaign_seed = next(), server_flags.push_back(a);
        else if (a == "--fail") srv.fail = next(), server_flags.push_back(a);
        else if (a == "--log-packets") srv.log_packets = next(), server_flags.push_back(a);
        else if (a == "--seed-rng") {
            std::string c = next();
            char* end = nullptr;
            unsigned long long v = strtoull(c.c_str(), &end, 0);
            if (c.empty() || *end) {
                fprintf(stderr, "--seed-rng: expected a number, got \"%s\"\n", c.c_str());
                return 2;
            }
            srv.has_seed_rng = true, srv.seed_rng = v;
            server_flags.push_back(a);
        }
        else if (a == "--guest-cpus") {
            std::string c = next();
            char* end = nullptr;
            long v = strtol(c.c_str(), &end, 10);
            if (c != "host" && (c.empty() || *end || v < 1 || v > 256)) {
                fprintf(stderr, "--guest-cpus: expected 1..256 or \"host\", got \"%s\"\n", c.c_str());
                return 2;
            }
            opt.client.has_guest_cpus = true;
            opt.client.guest_cpus = c == "host" ? 0 : (int)v;
        }
        else if (a == "--event-keywords") srv.event_keywords = next(), server_flags.push_back(a);
        else if (a == "--start-coins") {
            std::string c = next();
            char* end = nullptr;
            unsigned long v = strtoul(c.c_str(), &end, 10);
            if (c.empty() || *end || v > 0xffffffffUL) {
                fprintf(stderr, "--start-coins: expected a number, got \"%s\"\n", c.c_str());
                return 2;
            }
            srv.has_start_coins = true;
            srv.start_coins = (uint32_t)v;
            server_flags.push_back(a);
        }
        else if (a == "--list-native") {
            list_native_functions(stdout);
            return 0;
        }
        else if (a == "-v") g_log_level = LogLevel::Debug;
        else if (a == "-vv") g_log_level = LogLevel::Trace;
        else {
            usage();
            return a == "-h" || a == "--help" ? 0 : 2;
        }
    }
    options_from_env(opt);
    if (getenv("SOA_RESTORE")) LOGW("main", "SOA_RESTORE is gone and ignored: the in-process server is the default (--server inproc)");
    if (!natives_given) {
        if (const char* e = getenv("SOA_NATIVES"); e && *e && !parse_native_set(e, natives)) fatal("SOA_NATIVES: expected route or none, got \"%s\"", e);
    }
    // --server inproc|HOST[:PORT].
    if (!server_given) server_mode = "inproc";
    const bool inproc = server_mode == "inproc";
    if (!inproc) {
        if (!server_flags.empty()) {
            std::string l;
            for (auto& f : server_flags) l += (l.empty() ? "" : " ") + f;
            LOGW("main", "server options (%s) have no effect with --server %s: give them to soa-server", l.c_str(), server_mode.c_str());
        }
        std::string host = server_mode;
        int port = 0;
        size_t c = host.rfind(':');
        if (c != std::string::npos && host.find(':') == c) port = atoi(host.c_str() + c + 1), host = host.substr(0, c);
        if (host.empty() || (c != std::string::npos && port <= 0)) fatal("--server: expected inproc or HOST[:PORT], got \"%s\"", server_mode.c_str());
        p370.netcfg.server_host = host;
        if (port) p370.netcfg.server_port = port;
    } else {
        srv.enabled = true;  // the local server on the FakeApiCaller route
    }
    // In-process the client sends no GameRPC (the FakeApiCaller route) and its HTTP goes only to the
    // in-process CDN (net/http are turned on below, with the CDN); with soa-server it talks
    // GameRPC and HTTP.
    p370.net = p370.http = !inproc;

    // The 3.7.0 APK, and the library (cached in the data dir, else the repo's work/ copy).
    if (apk_path.empty()) {
        apk_path = find_repo_file("apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk");
        if (apk_path.empty()) {
            usage();
            fatal("--apk not given and apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk (in the repo) wasn't found");
        }
    }
    if (!file_exists(apk_path)) fatal("--apk: %s not found", apk_path.c_str());
    mkdir(data_dir.c_str(), 0755);
    if (lib_path.empty()) {
        lib_path = data_dir + "/libSOA-3.7.0.so";
        if (!file_exists(lib_path)) {
            LOGI("main", "extracting libSOA.so from %s", apk_path.c_str());
            if (!extract_lib(apk_path, lib_path)) {
                unlink(lib_path.c_str());
                lib_path = find_repo_file("work/libSOA-3.7.0.so");
                if (lib_path.empty()) fatal("couldn't extract lib/arm64-v8a/libSOA.so from %s (and work/libSOA-3.7.0.so wasn't found)", apk_path.c_str());
            }
        }
    }
    ClientOptions& cl = opt.client;
    std::string& download_dir = cl.download_dir;

    // --server inproc: the local server (top-level server/) on the
    // FakeApiCaller route, plus the 3.7.0 download tree; explicit settings win.
    if (srv.enabled) {
        // Defaults from the repo (core/paths.h), whatever the working directory.
        if (cl.fake_server_dir.empty()) {
            std::string d = find_repo_file("port/fakeapi/responses");
            cl.fake_server_dir = d.empty() ? "." : d;
        }
        // Required in-process: the route's client has no CDN to download from.
        if (download_dir.empty()) download_dir = find_repo_file("work/download-3.7.0");
        if (download_dir.empty() || !file_exists(download_dir))
            fatal("--server inproc needs the 3.7.0 download tree: give --download-dir DIR (default <repo>/work/download-3.7.0, %s)",
                  download_dir.empty() ? "not found" : "missing");
        if (cl.standin_dir.empty() && !cl.standin_off) cl.standin_dir = find_repo_file("standin-assets");
        if (srv.db.empty()) srv.db = data_dir + "/server.sqlite3";
        if (srv.game_xml.empty()) srv.game_xml = data_dir + "/data/shared_prefs/Game.xml";
        LOGI("main", "server inproc: local server on the FakeApiCaller route, fake server dir %s, download dir %s", cl.fake_server_dir.c_str(),
             download_dir.c_str());
    } else {
        LOGI("main", "server %s:%d (soa-server over TCP + HTTP; the client's own NetworkApiCaller), no FakeApiCaller route",
             p370.netcfg.server_host.c_str(), p370.netcfg.server_port);
    }
    // The server library's configuration (top-level server/) from the final run options.
    soa::server_port::config_from_options(data_dir);
    if (srv.enabled) {
        // The in-process server's CDN (native/api/server_cdn.cpp): Login sends the CDN keys and the
        // client downloads (or checks) its game data from it through platform370's HTTP client, as
        // from soa-server's, but in memory: the CDN's router is platform370's HTTP backend, and no
        // socket is opened. Without it the 3.7.0 client never mounts its download storage.
        std::string what;
        if (!soa::server_port::start_inproc_cdn(&what)) fatal("--server inproc: the local server's CDN didn't start: %s", what.c_str());
        // The client resolves production-game.so-ana.com before each HTTP request (getaddrinfo),
        // and the HTTP client hands requests to mapped hosts to the backend, so the name mapping
        // is on too. No GameRPC connection is expected in-process: server_port 0 leaves a stray
        // connect to port 443 unredirected (127.0.0.1:443, refused like a network error) instead
        // of sending it to a soa-server that may listen on the default 44300. http_port isn't
        // used (the backend answers mapped hosts).
        p370.net = p370.http = true;
        p370.netcfg.server_host = p370.netcfg.http_host = "127.0.0.1";
        p370.netcfg.server_port = p370.netcfg.http_port = 0;
        LOGI("main", "server inproc: CDN in-process (no sockets): %s", what.c_str());
    }

    // The emulated device (runtime/src/core/device.h): a phone with the 3.7.0 app. platform370
    // registers its pieces with the runtime's extension points and sets app_version ("3.7.0") and
    // the device clock, so it comes before hle_init / Vm::init.
    device_config().guest_cpus = cl.guest_cpus;
    platform370::install(p370);
    vfs_init({data_dir});
    LOGI("main", "3.7.0 client %s, APK %s, data %s, natives: %s", lib_path.c_str(), apk_path.c_str(), data_dir.c_str(),
         selftest ? "none (--selftest)" : native_set_name(natives));

    cpu_global_init();
    hle_init();
    auto& vm = jni::Vm::get();
    vm.init();
    LoadedLib* lib = load_library(lib_path);
    // platform370's native patch (service_stop_day), before any native hook.
    switch (platform370::install_patches(*lib)) {
        case platform370::PatchStatus::Hooked: break;
        case platform370::PatchStatus::Disabled: LOGI("main", "--no-patch: the client's service-end check is live"); break;
        case platform370::PatchStatus::NotFound: LOGW("main", "platform370's service_stop_day patch found no 3.7.0 FindGlobalStringWithKey"); break;
    }
    // The FakeApiCaller route's hooks only in-process; with --server HOST the client's own
    // NetworkApiCaller runs untouched. (The main image is the 3.7.0 client; no
    // second image is mapped.)
    if (!selftest) install_native_functions(*lib, natives, inproc);
    if (selftest) install_test_hooks(*lib);  // test harness hooks (see NATIVE_TEST_HOOK)
    if (!selftest) install_traces(*lib);
    profile_init(*lib);  // SOA_COVERAGE / SOA_PROFILE
    app::start_watchdog();  // SOA_WATCHDOG

    auto& am = asset_manager();
    if (!download_dir.empty()) {
        am.set_download_dir(download_dir, cl.download_prefer);
        LOGI("main", "download dir %s (%s the APK)", download_dir.c_str(), am.download_prefer() ? "preferred over" : "fallback for");
    }
    if (!cl.standin_off && !cl.standin_dir.empty()) {
        am.set_standin_dir(cl.standin_dir);
        LOGI("main", "stand-in assets %s (after the APK and the download dir)", cl.standin_dir.c_str());
    }
    // The 3.7.0 APK is a single APK (no splits, no asset packs, no Play Core); the asset manager
    // indexes the zip.
    if (!am.add_apk(apk_path)) fatal("--apk: cannot open %s", apk_path.c_str());

    run_initializers(*lib);
    // --selftest boots the game without native replacements and runs the differential tests
    // once the game's memory manager exists (many guest functions allocate through it); see
    // the main loop.
    if (smoke) {
        u64 ctor = lib->sym("_ZN9Framework7CHash32C1EPKc");
        u64 get = lib->sym("_ZNK9Framework7CHash323GetEv");
        alignas(16) u8 obj[32] = {};
        guest_call(ctor, {(u64)obj, (u64) "role_cp0303_b04a_6131"});
        u32 h = (u32)guest_call(get, {(u64)obj});
        printf("smoke: CHash32 = %u (%s)\n", h, h == 813289606u ? "ok" : "MISMATCH");
        return h == 813289606u ? 0 : 1;
    }

    // ---- window, activity, event loop: the runtime's desktop host loop (runtime/src/app/host.h) ----
    app::HostConfig host;
    host.width = width, host.height = height;
    host.landscape = landscape;
    host.fullscreen = fullscreen;
    // --headless / --windowed, else SOA_HEADLESS=1/0, else headless for --selftest only. The hidden
    // window renders like a shown one (runtime/src/app/host.h: HostConfig::hidden).
    if (headless < 0) {
        const char* e = getenv("SOA_HEADLESS");
        headless = e && *e ? atoi(e) != 0 : selftest;
    }
    host.hidden = headless != 0;
    if (host.hidden) LOGI("main", "headless: the window isn't shown");
    host.render_size = render_size;
    host.font = font;
    host.size_note = " (the game's own resolution: 720 wide, a 0.75 back buffer, upscaled)";
    host.shots = shots;
    host.actions = actions;
    host.control_path = control_path;
    host.command = [](const std::string& cmd) { return native::port_debug::command(cmd); };  // phase:N, call:SYM[:ARGS], debugwin:W:H
    host.tick = [&] {
        if (selftest) {
            // Wait for the memory manager and the parameter manager (text database), then give
            // the game a few seconds to finish booting.
            static u64 get_mm = lib->sym("_ZN4Aska6Global25GetAvailableMemoryManagerEv");
            static u64 pm = lib->sym("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE");
            static auto ready_since = std::chrono::steady_clock::time_point{};
            bool ready = guest_call(get_mm, {}) != 0 && *(u64*)pm != 0;
            if (ready && ready_since == std::chrono::steady_clock::time_point{}) ready_since = std::chrono::steady_clock::now();
            // SOA_SELFTEST_DELAY=S waits S seconds instead of 10; SOA_SELFTEST_START_FILE=F waits
            // until file F exists (e.g. to drive the game to a scene through --control first, for
            // tests on live game objects).
            static const int delay = getenv("SOA_SELFTEST_DELAY") ? atoi(getenv("SOA_SELFTEST_DELAY")) : 10;
            static const char* start_file = getenv("SOA_SELFTEST_START_FILE");
            bool go = start_file ? access(start_file, F_OK) == 0 : std::chrono::steady_clock::now() - ready_since > std::chrono::seconds(delay);
            if (ready && go) {
                int failed = run_native_tests(*lib, test_filter);
                fflush(stderr);
                _exit(failed ? 1 : 0);
            }
        }
    };
    app::run(*lib, host);
}
