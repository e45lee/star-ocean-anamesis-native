// Star Ocean: anamnesis desktop host. Loads the Android libSOA.so under an ARM64 JIT and
// drives it like Android's NativeActivity would. The window, input, audio, the activity bring-up
// and the main loop are the runtime's desktop host loop (runtime/include/soaruntime/app/host.h).
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

#include <soa/env.h>
#include <soa/game_files.h>
#include <soa/paths.h>

#include "soaruntime/android/ndk.h"
#include "soaruntime/app/host.h"
#include "soaruntime/android/platform.h"
#include "soaruntime/android/zip.h"
#include "soaruntime/core/cpu.h"
#include "soaruntime/core/device.h"
#include "soaruntime/core/gdbstub.h"
#include "soaruntime/core/hle.h"
#include "soaruntime/core/loader.h"
#include "soaruntime/core/log.h"
#include "core/cli.h"
#include "core/options.h"
#include "core/paths.h"
#include "soaruntime/core/profile.h"
#include "soaruntime/core/vfs.h"
#include "soaruntime/jni/jvm.h"
#include "native/common/lib_check.h"
#include "native/common/live_check.h"
#include "native/common/native.h"
#include "native/common/port_debug.h"
#include "native/common/test.h"
#include "platform370/platform370.h"
#include "soawebview/page.h"
#include "soaserver/config.h"
#include "soaserver/master_source.h"

using namespace soa;
namespace soa {
void install_traces(LoadedLib& lib);
}

namespace {

bool file_exists(const std::string& p) {
    struct stat st;
    return stat(p.c_str(), &st) == 0;
}

}  // namespace

namespace soa::server_port {
void config_from_options(const std::string& data_dir);  // native/api/server_adapters.h
bool start_inproc_cdn(std::string* err);                // native/api/server_cdn.cpp
}

int main(int argc, char** argv) {
    env::warn_removed_env("soa", env::kSoa);  // SOA_* settings that are flags now: one line each
    signal(SIGPIPE, SIG_IGN);
    // The runtime's calls into this frontend (runtime/include/soaruntime/android/platform.h).
    app::install_host_hooks();
    // The command line (core/cli.cpp: the client options and soa-server's server options).
    RunOptions& opt = mutable_options();  // from the command line only
    ServerOptions& srv = opt.server;
    SoaArgs args;
    args.opt = &opt;
    if (int rc = parse_soa_args(argc, argv, args); rc >= 0) return rc;
    if (args.verbose) g_log_level = args.verbose > 1 ? LogLevel::Trace : LogLevel::Debug;
    if (args.list_native) {
        list_native_functions(stdout);
        return 0;
    }
    if (args.apk_dir_given) LOGW("main", "--apk-dir is ignored: the rebased port runs the 3.7.0 APK (--apk FILE)");
    // --natives: all (every registered native), route (the route's and the port's own hooks) or none.
    NativeSet natives = NativeSet::All;
    if (!parse_native_set(args.natives, natives)) {
        fprintf(stderr, "--natives: expected all, route or none, got \"%s\"\n", args.natives.c_str());
        return 2;
    }
    if (std::string err; !check_native_subsystems(args.natives_skip, &err)) {
        fprintf(stderr, "--natives-skip: %s\n", err.c_str());
        return 2;
    }
    for (auto& spec : args.live_checks) {
        std::string err;
        if (!live::parse_live_check(spec, &err)) {
            fprintf(stderr, "--live-check %s: %s\n", spec.c_str(), err.c_str());
            return 2;
        }
    }
    if (!args.live_checks.empty()) {  // switch the named families on (lost in the move to CLI11)
        std::string err;
        if (!live::apply_live_check(&err)) {
            fprintf(stderr, "--live-check: %s\n", err.c_str());
            return 2;
        }
    }
    // A data dir of its own (soa/paths.h): ~/.local/share/soa-linux-370 (the old offline-build port's
    // ~/.local/share/soa-linux holds a cached libSOA.so of that build and its save), on Windows
    // %LOCALAPPDATA%\soa\port-370.
    std::string data_dir = args.data_dir.empty() ? soa::default_data_dir("soa-linux-370", "port-370") : args.data_dir;
    std::string &apk_path = args.apk_path, &lib_path = args.lib_path;
    const bool smoke = args.smoke, selftest = args.selftest;
    // --server: "inproc" (default) or HOST[:PORT].
    const std::string server_mode = args.server_mode.empty() ? "inproc" : args.server_mode;
    // The 3.7.0 platform layer (platform370/README.md); net/http only with --server HOST.
    platform370::Config& p370 = args.p370;
    const std::string& test_filter = args.test_filter;
    app::HostConfig& host = args.host;
    int headless = args.headless;  // -1: not given (headless only for --selftest)
    const std::string& gdb_addr = args.gdb;  // --gdb HOST:PORT (core/gdbstub.h)
    const std::vector<std::string>& server_flags = args.server_flags;  // server options given on the command line (for the --server HOST warning)
    // --server inproc|HOST[:PORT].
    const bool inproc = server_mode == "inproc";
    if (!inproc) {
        if (!server_flags.empty()) {
            std::string l;
            for (auto& f : server_flags) l += (l.empty() ? "" : " ") + f;
            LOGW("main", "server options (%s) have no effect with --server %s: give them to soa-server", l.c_str(), server_mode.c_str());
        }
        // (p370.netcfg's server_host / server_port: core/cli.cpp, as soa-emu --server)
    } else {
        srv.enabled = true;  // the local server on the FakeApiCaller route
        // --lang en also turns the in-process server's English mode on (one knob; --english is
        // ServerConfig::english, server/include/soaserver/cli.h; docs/server-rules.md#english).
        // A remote server (--server) keeps its own setting.
        if (p370.lang == "en") srv.english = true;
    }
    // In-process the client sends no GameRPC (the FakeApiCaller route) and its HTTP goes only to the
    // in-process CDN (net/http are turned on below, with the CDN); with soa-server it talks
    // GameRPC and HTTP.
    p370.net = p370.http = !inproc;

    // The 3.7.0 APK, and the library (cached in the data dir, else the repo's work/ copy).
    if (apk_path.empty()) {
        apk_path = find_repo_file("apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk");
        if (apk_path.empty()) {
            // a release package (README.md "Packaging"): a 3.7.0 APK beside the program or in game/
            std::vector<std::string> notes;
            apk_path = install::find_apk(install::install_dirs(), &notes);
            for (auto& n : notes) LOGW("main", "%s", n.c_str());
            if (apk_path.empty())
                fatal("the 3.7.0 APK wasn't found (--apk FILE, or apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk in the repo); %s",
                      install::missing_hint().c_str());
            LOGI("main", "the 3.7.0 APK %s (found beside the program)", apk_path.c_str());
        }
    }
    if (!file_exists(apk_path)) fatal("--apk: %s not found", apk_path.c_str());
    soa::make_dir_tree(data_dir);
    if (lib_path.empty()) {
        lib_path = data_dir + "/libSOA-3.7.0.so";
        if (!file_exists(lib_path)) {
            LOGI("main", "extracting libSOA.so from %s", apk_path.c_str());
            if (!install::extract_entry(apk_path, install::kLibEntry, lib_path)) {
                lib_path = find_repo_file("work/libSOA-3.7.0.so");
                if (lib_path.empty()) fatal("couldn't extract lib/arm64-v8a/libSOA.so from %s (and work/libSOA-3.7.0.so wasn't found)", apk_path.c_str());
            }
        }
    }
    // The natives and their generated address tables are the 3.7.0 lib's: on another build they
    // would read and write the wrong memory, so they are refused (native/common/lib_check.h).
    if (natives != NativeSet::None || selftest) {
        std::string got;
        if (!native::lib_matches(lib_path, &got)) {
            if (!selftest)
                fatal("%s is not the libSOA.so the natives were made for (sha256 %s, expected the 3.7.0 build's %s): run it "
                      "with --natives none, or regenerate the natives' tables for it (tools/check_generated.py)",
                      lib_path.c_str(), got.empty() ? "unreadable" : got.c_str(), native::expected_lib_sha256());
            LOGW("main", "%s is not the 3.7.0 libSOA.so the natives' tables were made for (sha256 %s): the tests that "
                         "use their addresses will fail", lib_path.c_str(), got.c_str());
        }
    }
    ClientOptions& cl = opt.client;
    std::string& download_dir = cl.download_dir;

    // --server inproc: the local server (top-level server/) on the
    // FakeApiCaller route, plus the 3.7.0 download tree; explicit settings win.
    if (srv.enabled) {
        // Defaults from the repo (core/paths.h), whatever the working directory.
        // Required in-process: the route's client has no CDN to download from.
        if (download_dir.empty()) download_dir = find_repo_file(install::kRepoDownloadZip);
        if (download_dir.empty()) {
            // a release package: a download tree beside the program or in game/ (soa/install.h)
            std::vector<std::string> notes;
            download_dir = install::find_download(install::install_dirs(), &notes);
            for (auto& n : notes) LOGW("main", "%s", n.c_str());
            if (!download_dir.empty()) LOGI("main", "the 3.7.0 download %s (found beside the program)", download_dir.c_str());
        }
        if (download_dir.empty() || !file_exists(download_dir))
            fatal("--server inproc needs the 3.7.0 download: give --download PATH (SOA-3.7.0-canonical-data.zip or an extracted folder; default <repo>/work/SOA-3.7.0-canonical-data.zip, %s); %s",
                  download_dir.empty() ? "not found" : "missing", install::missing_hint().c_str());
        if (cl.standin_dir.empty() && !cl.standin_off) cl.standin_dir = find_repo_file("standin-assets");
        if (srv.db.empty()) srv.db = data_dir + "/server.sqlite3";
        srv.client_save = data_dir + "/data/shared_prefs/Game.xml";  // the last seed fallback (state/seed.h)
        LOGI("main", "server inproc: local server on the FakeApiCaller route, download dir %s", download_dir.c_str());
    } else {
        LOGI("main", "server %s:%d (soa-server over TCP + HTTP; the client's own NetworkApiCaller), no FakeApiCaller route",
             p370.netcfg.server_host.c_str(), p370.netcfg.server_port);
    }
    // The server library's configuration (top-level server/) from the final run options.
    soa::server_port::config_from_options(data_dir);
    server::config().apk = apk_path;
    if (srv.enabled) {
        // The in-process server's master (the CDN serves it, the campaign reads it): --master, the
        // repo's, else decrypted from the download (or the APK) into DATA/master/ (soaserver/master_source.h).
        if (server::master_source::resolve().empty())
            fatal("--server inproc: no 3.7.0 master DB (--master FILE, data/basmaster-3.7.0.sqlite3, or the download's); %s",
                  install::missing_hint().c_str());
    }
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

    // The emulated device (runtime/include/soaruntime/core/device.h): a phone with the 3.7.0 app. platform370
    // registers its pieces with the runtime's extension points and sets app_version ("3.7.0") and
    // the device clock, so it comes before hle_init / Vm::init.
    device_config().guest_cpus = cl.guest_cpus;
    platform370::install(p370);
    vfs_init({data_dir});
    LOGI("main", "3.7.0 client %s, APK %s, data %s, natives: %s", lib_path.c_str(), apk_path.c_str(), data_dir.c_str(),
         selftest ? "none (--selftest)" : native_set_name(natives));

    cpu_global_init();
    if (!gdb_addr.empty()) {  // --gdb: the debugger hooks go on before any guest code runs
        std::string err;
        if (!gdb_listen(gdb_addr, &err)) {
            fprintf(stderr, "%s\n", err.c_str());
            return 2;
        }
    }
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
    // --lang / --voice-lang (platform370 lang_370.cpp, text_370.cpp): with --lang en the CLanguage,
    // CCocosLabel::SetText and DrawSelf hooks; none is a native, so the natives below don't replace them.
    platform370::install_language(*lib);
    // The FakeApiCaller route's hooks only in-process; with --server HOST the client's own
    // NetworkApiCaller runs untouched. (The main image is the 3.7.0 client; no
    // second image is mapped.)
    if (!selftest) install_native_functions(*lib, natives, inproc, args.natives_skip);
    if (selftest) install_test_hooks(*lib);  // test harness hooks (see NATIVE_TEST_HOOK)
    if (!selftest) install_traces(*lib);
    profile_init(*lib);  // SOA_COVERAGE / SOA_PROFILE
    app::start_watchdog();  // SOA_WATCHDOG

    auto& am = asset_manager();
    if (!download_dir.empty()) {
        if (!am.set_download_dir(download_dir, cl.download_prefer)) fatal("--download %s: neither a folder nor a zip", download_dir.c_str());
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

    // ---- window, activity, event loop: the runtime's desktop host loop (runtime/include/soaruntime/app/host.h) ----
    // --headless / --windowed, else headless for --selftest only. The hidden window renders like a
    // shown one (runtime/include/soaruntime/app/host.h: HostConfig::hidden).
    if (headless < 0) headless = selftest;
    host.hidden = headless != 0;
    if (host.hidden) LOGI("main", "headless: the window isn't shown");
    // The render resolution (native/ui/ui_utility.cpp, the port's own hooks): its natives aren't
    // installed with --natives none, --natives-skip ui or in --selftest.
    {
        const ClientOptions& cl = opt.client;
        char note[160];
        const bool skip_ui = std::find(args.natives_skip.begin(), args.natives_skip.end(), "ui") != args.natives_skip.end();
        if (cl.legacy_res || natives == NativeSet::None || skip_ui || selftest)
            snprintf(note, sizeof note, " (the game's own resolution: 720 wide, a 0.75 back buffer, upscaled%s)",
                     cl.legacy_res ? "" : selftest ? "; --selftest: no natives" : skip_ui ? "; --natives-skip ui" : "; --natives none");
        else if (cl.render_scale > 0)
            snprintf(note, sizeof note, " (--render-scale %g: 720 wide, a %gx back buffer)", cl.render_scale, cl.render_scale);
        else
            snprintf(note, sizeof note, " (hi-res: the game renders at this size; --legacy-res for its own)");
        host.size_note = note;
    }
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
            // tests on live game objects). Test-harness switches: environment (port/README.md).
            static const int delay = (int)env::env_int("SOA_SELFTEST_DELAY", 0, 3600, 10);
            static const char* start_file = env::env_str("SOA_SELFTEST_START_FILE");
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
