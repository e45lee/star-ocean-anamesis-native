// soa-emu: the 3.7.0 online client of STAR OCEAN: anamnesis, as shipped, under the JIT host
// runtime (runtime/). No native replacements, no restore code, no in-process server: the client is the
// shipped work/libSOA-3.7.0.so with the 3.7.0 APK's assets; only the platform layer under it (HLE
// imports, the Java methods, the network glue) is ours: the 3.7.0 platform library
// (platform370/), plus its one native patch that hides master_global.service_stop_day so the
// client runs on the real date. This file maps the command line onto platform370::Config and
// brings the runtime up. emulator/README.md, platform370/README.md.
#include <soa/env.h>
#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <chrono>
#include <cstdio>
#include <string>
#include <vector>

#include "android/ndk.h"
#include "app/host.h"
#include "core/cpu.h"
#include "core/device.h"
#include "core/gdbstub.h"
#include "core/hle.h"
#include "core/loader.h"
#include "core/log.h"
#include "core/profile.h"
#include "core/vfs.h"
#include "jni/jvm.h"
#include "platform370/platform370.h"

using namespace soa;
namespace soa {
void install_traces(LoadedLib& lib);  // core/trace.cpp: SOA_TRACE
}

namespace {

bool exists(const std::string& p) {
    struct stat st;
    return !p.empty() && stat(p.c_str(), &st) == 0;
}
std::string real(const std::string& p) {
    char buf[PATH_MAX];
    return realpath(p.c_str(), buf) ? std::string(buf) : std::string();
}
std::string parent(const std::string& p) {
    size_t s = p.find_last_of('/');
    if (s == std::string::npos) return "";
    return s == 0 ? "/" : p.substr(0, s);
}

// The repo root: --repo, else upwards from the executable (build/emulator/soa-emu), else from the
// working directory: the first directory holding emulator/CMakeLists.txt.
std::string find_repo(const std::string& given) {
    if (!given.empty()) return real(given);
    for (std::string start : {parent(real("/proc/self/exe")), real(".")}) {
        for (std::string d = start; !d.empty(); d = parent(d)) {
            if (exists(d + "/emulator/CMakeLists.txt") && exists(d + "/runtime/CMakeLists.txt")) return d;
            if (d == "/") break;
        }
    }
    return "";
}

// A repo file: in the repo, else (a git worktree, whose work/ links into the main checkout) in
// the main checkout, where untracked files such as apk/*.apk live. "" when neither has it.
std::string repo_file(const std::string& repo, const std::string& rel) {
    if (repo.empty()) return "";
    if (exists(repo + "/" + rel)) return repo + "/" + rel;
    std::string w = real(repo + "/work");
    std::string main = w.empty() ? "" : parent(w);
    if (!main.empty() && main != repo && exists(main + "/" + rel)) return main + "/" + rel;
    return "";
}

// The default device clock: the host's real time. The client's own service-end check
// (master_global.service_stop_day, 2021/06/24 14:30:00) is patched out (platform370's
// patch_370.cpp), so no fake date is needed; --device-clock sets one for tests.
const char* const kDefaultDeviceClock = "host";

void usage() {
    fprintf(stderr,
            "usage: soa-emu [options]\n"
            "Runs the 3.7.0 online client unmodified (pure JIT, no natives). emulator/README.md.\n"
            "  --lib PATH      the client library (default <repo>/work/libSOA-3.7.0.so)\n"
            "  --apk FILE      the APK whose assets the client reads (default\n"
            "                  <repo>/apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk; repeatable, later wins)\n"
            "  --data DIR      the emulated device's data (saves, prefs, downloads; default\n"
            "                  ~/.local/share/soa-emulator-370/phone, beside the port's ~/.local/share/soa-linux;\n"
            "                  never the port's: its cached libSOA.so and save don't belong here)\n"
            "  --download-dir DIR  temporary stand-in for the CDN: serve assets missing from the APK from DIR\n"
            "                  (e.g. work/download-3.7.0); off by default\n"
            "  --download-prefer  with --download-dir: DIR wins over the APK (as soa / soa-viewer)\n"
            "  --repo DIR      the source checkout (default: found from the executable)\n"
            "  --device-clock \"YYYY-MM-DD HH:MM:SS\"|host  the phone's clock (local time) at start; it runs on from\n"
            "                  there (default %s: the host's real time; the client's service-end check is\n"
            "                  patched out, so any date works)\n"
            "  --no-patch      run the client without its native patch (platform370/src/patch_370.cpp): its service-end check\n"
            "                  is live, so on a date after 2021/06/24 14:30 the title shows the service-end notice\n"
            "  --server HOST[:PORT]  the game server: soa-server's --listen (default 127.0.0.1:44300); the client's\n"
            "                  production-game.so-ana.com resolves to HOST and its port 443 becomes PORT\n"
            "  --http HOST:PORT  soa-server's --http (default <server host>:44380): http(s):// URLs to a mapped\n"
            "                  host are fetched there as plain HTTP\n"
            "  --lobby HOST:PORT  where the client's lobby connections (port 4001) go (default: not redirected)\n"
            "  --map-host NAME[=ADDR]  also resolve NAME to ADDR (default the server host); repeatable\n"
            "  --guest-cpus N|host  CPUs the game sees (default 8)\n"
            "  --size WxH      window size (default: portrait 9:16 at 90%% of the desktop height)\n"
            "  --landscape     default to a 16:9 landscape window\n"
            "  --render-size S the game's screen size: 'desktop' (default), 'window' or WxH\n"
            "  --fullscreen    start in (desktop) fullscreen\n"
            "  --font PATH     the on-screen text box's font (default: a system Japanese font; 'none': off)\n"
            "  --headless      don't show the window (it still renders; screenshots and the control FIFO work)\n"
            "  --windowed      show the window (the default; undoes an earlier --headless)\n"
            "  --shot S:PATH   save a screenshot S seconds after start (repeatable; F12 any time)\n"
            "  --do S:ACTION   scripted input S seconds after start (repeatable): tap:X:Y, drag:X1:Y1:X2:Y2,\n"
            "                  wheel:X:Y:DY, back, text:STRING, shot:PATH, quit\n"
            "  --control FIFO  read the same commands, one per line, from a named pipe (control/soactl.py)\n"
            "  --gdb HOST:PORT serve the GDB remote protocol for the guest (gdb-multiarch -x control/gdbinit-soa,\n"
            "                  control/gdbclient.py; runtime/README.md \"Debugging the guest with gdb\")\n"
            "  -v / -vv        verbose / trace logging\n"
            "Diagnostic switches are environment variables (SOA_TRACE, SOA_PROFILE, SOA_WATCHDOG, ...:\n"
            "runtime/README.md \"Environment\"); settings are flags only.\n",
            kDefaultDeviceClock);
}

}  // namespace

int main(int argc, char** argv) {
    std::string gdb_addr;  // --gdb HOST:PORT (core/gdbstub.h)
    env::warn_removed_env("soa-emu", env::kEmu);  // SOA_* settings that are flags now
    signal(SIGPIPE, SIG_IGN);
    app::install_host_hooks();
    std::string lib_path, data_dir, download_dir, repo_arg;
    bool download_prefer = false;
    std::vector<std::string> apks;
    int guest_cpus = 8;
    // The 3.7.0 platform layer: everything on (soa-emu is the 3.7.0 phone, network included).
    platform370::Config p370;
    p370.device_clock = kDefaultDeviceClock;
    app::HostConfig host;
    // "EMULATED" first, so it shows in a truncated taskbar entry too; soa's title has no such tag.
    host.title = "[EMULATED] STAR OCEAN -anamnesis- 3.7.0 online client (soa-emu)";
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        auto next = [&]() -> std::string {
            if (i + 1 >= argc) {
                usage();
                exit(2);
            }
            return argv[++i];
        };
        if (a == "--lib") lib_path = next();
        else if (a == "--apk") apks.push_back(next());
        else if (a == "--data") data_dir = next();
        else if (a == "--download-dir") download_dir = next();
        else if (a == "--download-prefer") download_prefer = true;
        else if (a == "--repo") repo_arg = next();
        else if (a == "--device-clock") p370.device_clock = next();
        else if (a == "--no-patch") p370.patch = false;
        else if (a == "--server" || a == "--http" || a == "--lobby") {
            std::string v = next();
            std::string host = v;
            int port = 0;
            size_t c = v.rfind(':');
            if (c != std::string::npos && v.find(':') == c) host = v.substr(0, c), port = atoi(v.c_str() + c + 1);
            if (host.empty() || (c != std::string::npos && port <= 0) || (a != "--server" && port <= 0)) {
                fprintf(stderr, "%s: expected HOST%s, got \"%s\"\n", a.c_str(), a == "--server" ? "[:PORT]" : ":PORT", v.c_str());
                return 2;
            }
            auto& n = p370.netcfg;
            if (a == "--server") n.server_host = host, n.server_port = port ? port : n.server_port;
            else if (a == "--http") n.http_host = host, n.http_port = port;
            else n.lobby_host = host, n.lobby_port = port;
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
            if (c != "host" && (c.empty() || *end || v < 1 || v > 256)) {
                fprintf(stderr, "--guest-cpus: expected 1..256 or \"host\", got \"%s\"\n", c.c_str());
                return 2;
            }
            guest_cpus = c == "host" ? 0 : (int)v;
        }
        else if (a == "--size") sscanf(next().c_str(), "%dx%d", &host.width, &host.height);
        else if (a == "--landscape") host.landscape = true;
        else if (a == "--render-size") host.render_size = next();
        else if (a == "--font") host.font = next();
        else if (a == "--fullscreen") host.fullscreen = true;
        else if (a == "--headless") host.hidden = true;
        else if (a == "--windowed") host.hidden = false;
        else if (a == "--shot") host.shots.push_back(next());
        else if (a == "--do") host.actions.push_back(next());
        else if (a == "--control") host.control_path = next();
        else if (a == "--gdb") gdb_addr = next();
        else if (a == "-v") g_log_level = LogLevel::Debug;
        else if (a == "-vv") g_log_level = LogLevel::Trace;
        else {
            usage();
            return a == "-h" || a == "--help" ? 0 : 2;
        }
    }

    std::string repo = find_repo(repo_arg);
    if (repo.empty()) LOGW("emu", "the repository wasn't found (give --repo DIR); defaults need it");
    if (lib_path.empty()) {
        lib_path = repo_file(repo, "work/libSOA-3.7.0.so");
        if (lib_path.empty()) fatal("work/libSOA-3.7.0.so not found (give --lib)");
    }
    if (apks.empty()) {
        std::string apk = repo_file(repo, "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk");
        if (apk.empty()) fatal("apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk not found (give --apk)");
        apks.push_back(apk);
    }
    if (data_dir.empty()) {
        // Beside the port's ~/.local/share/soa-linux; scripts/run-emulator-370.sh uses the same phone/.
        const char* h = getenv("HOME");
        data_dir = std::string(h ? h : ".") + "/.local/share/soa-emulator-370/phone";
    }
    mkdir(data_dir.c_str(), 0755);
    LOGI("emu", "3.7.0 client %s, data %s, pure JIT + one native patch (platform370)", lib_path.c_str(), data_dir.c_str());

    // The emulated device: a phone with the 3.7.0 app installed (app_version "3.7.0", the APK's
    // versionName), its clock the host's (or --device-clock), its network redirected to
    // soa-server. platform370::install registers the platform layer with the runtime's
    // extension points, so it comes before hle_init / Vm::init.
    platform370::install(p370);
    {
        auto& n = platform370::net_config();
        LOGI("emu", "network: production-game.so-ana.com -> %s:%d (game), http -> %s:%d%s%s", n.server_host.c_str(), n.server_port,
             (n.http_host.empty() ? n.server_host : n.http_host).c_str(), n.http_port, n.lobby_port ? ", lobby -> " : "",
             n.lobby_port ? (n.lobby_host + ":" + std::to_string(n.lobby_port)).c_str() : "");
        for (auto& [name, addr] : n.hosts) LOGI("emu", "network: %s -> %s", name.c_str(), addr.empty() ? n.server_host.c_str() : addr.c_str());
    }
    device_config().guest_cpus = guest_cpus;
    vfs_init({data_dir});

    auto t0 = std::chrono::steady_clock::now();
    cpu_global_init();
    if (!gdb_addr.empty()) {  // --gdb: the debugger hooks go on before any guest code runs
        std::string err;
        if (!gdb_listen(gdb_addr, &err)) {
            fprintf(stderr, "%s\n", err.c_str());
            return 2;
        }
    }
    hle_init();             // + platform370: fmod, the clock, the network redirect
    jni::Vm::get().init();  // + platform370: the 3.7.0 Java answers, the HTTP client
    LoadedLib* lib = load_library(lib_path);
    // platform370's native patch: before any guest code runs.
    if (platform370::install_patches(*lib) == platform370::PatchStatus::Disabled)
        LOGI("emu", "--no-patch: the client runs unmodified; its service-end check is live");
    install_traces(*lib);  // SOA_TRACE
    profile_init(*lib);    // SOA_COVERAGE / SOA_PROFILE
    app::start_watchdog(); // SOA_WATCHDOG

    auto& am = asset_manager();
    if (!download_dir.empty()) {
        am.set_download_dir(download_dir, download_prefer);
        LOGI("emu", "download dir %s: a temporary stand-in for the CDN (%s the APK)", download_dir.c_str(), download_prefer ? "preferred over" : "fallback for");
    }
    // The 3.7.0 APK is a single APK (no splits, no asset packs); the asset manager indexes the zip.
    for (auto& f : apks)
        if (!am.add_apk(f)) fatal("--apk: cannot open %s", f.c_str());

    run_initializers(*lib);
    LOGI("emu", "library loaded and initialised in %.1f s",
         std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
    app::run(*lib, host);
}
