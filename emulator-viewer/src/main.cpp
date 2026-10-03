// soa-viewer: the offline 3.8.0 client of STAR OCEAN: anamnesis, as shipped, under the JIT host
// runtime (runtime/). No native replacements, no restore code, no server: the client is the
// shipped libSOA.so of the 3.8.0 XAPK (config.arm64_v8a.apk) with the XAPK's assets (base APK +
// the install-time asset pack). The runtime was built for this build's imports and Java methods
// (incl. Play Asset Delivery: jni/java_playcore.cpp), so the viewer adds only one platform
// answer: the dead service's host names don't resolve (net_offline.cpp). emulator-viewer/README.md.
#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <chrono>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "android/ndk.h"
#include "android/platform.h"
#include "android/zip.h"
#include "app/host.h"
#include "core/cpu.h"
#include "core/device.h"
#include "core/hle.h"
#include "core/loader.h"
#include "core/log.h"
#include "core/profile.h"
#include "core/vfs.h"
#include "jni/jvm.h"

using namespace soa;
namespace soa {
void install_traces(LoadedLib& lib);  // core/trace.cpp: SOA_TRACE
}

namespace {

const char* const kBaseApk = "com.square_enix.android_googleplay.StarOceanj.apk";

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

// The repo root: --repo, else upwards from the executable (build/emulator-viewer/soa-viewer), else
// from the working directory: the first directory holding emulator-viewer/CMakeLists.txt.
std::string find_repo(const std::string& given) {
    if (!given.empty()) return real(given);
    for (std::string start : {parent(real("/proc/self/exe")), real(".")}) {
        for (std::string d = start; !d.empty(); d = parent(d)) {
            if (exists(d + "/emulator-viewer/CMakeLists.txt") && exists(d + "/runtime/CMakeLists.txt")) return d;
            if (d == "/") break;
        }
    }
    return "";
}

// A repo file: in the repo, else (a git worktree, whose work/ links into the main checkout) in
// the main checkout. "" when neither has it.
std::string repo_file(const std::string& repo, const std::string& rel) {
    if (repo.empty()) return "";
    if (exists(repo + "/" + rel)) return repo + "/" + rel;
    std::string w = real(repo + "/work");
    std::string main = w.empty() ? "" : parent(w);
    if (!main.empty() && main != repo && exists(main + "/" + rel)) return main + "/" + rel;
    return "";
}

// The client library: lib/arm64-v8a/libSOA.so of config.arm64_v8a.apk, extracted into the
// viewer's data dir (re-extracted when its size differs from the APK's entry), as the package
// manager installs it. The port keeps its own copy in its own data dir; they are never shared.
std::string extract_lib(const std::string& apk, const std::string& out) {
    ZipArchive z;
    if (!z.open(apk)) fatal("cannot open %s", apk.c_str());
    auto* e = z.find("lib/arm64-v8a/libSOA.so");
    if (!e) fatal("%s has no lib/arm64-v8a/libSOA.so", apk.c_str());
    struct stat st;
    if (stat(out.c_str(), &st) == 0 && (u64)st.st_size == e->size) return out;
    LOGI("viewer", "extracting libSOA.so from %s", apk.c_str());
    std::vector<uint8_t> data;
    if (!z.extract(*e, data)) fatal("cannot extract libSOA.so from %s", apk.c_str());
    std::string tmp = out + ".tmp";
    std::ofstream o(tmp, std::ios::binary);
    o.write((const char*)data.data(), data.size());
    o.close();
    if (!o.good() || rename(tmp.c_str(), out.c_str()) != 0) fatal("cannot write %s", out.c_str());
    return out;
}

// A Play Asset Delivery pack given as a split APK (fast-follow / on-demand packs; the APKPure
// XAPK has only the install-time one): its assets/ go to <files>/assetpacks/<name>/assets, the
// STORAGE_FILES layout Play Core gives such packs (docs/notes.md "Asset packs"). Files already
// there with the right size are kept.
bool install_asset_pack(const std::string& apk, const std::string& name) {
    ZipArchive z;
    if (!z.open(apk)) return false;
    std::string root = host_path((guest_internal_dir() + "/assetpacks/" + name).c_str());
    size_t n = 0, copied = 0;
    for (auto& [path, e] : z.entries()) {
        if (path.compare(0, 7, "assets/") != 0 || path.back() == '/') continue;
        n++;
        std::string out = root + "/" + path;
        struct stat st;
        if (stat(out.c_str(), &st) == 0 && (u64)st.st_size == e.size) continue;
        make_dirs(out.substr(0, out.rfind('/')));
        std::vector<uint8_t> data;
        if (!z.extract(e, data)) continue;
        std::ofstream(out, std::ios::binary).write((const char*)data.data(), data.size());
        copied++;
    }
    LOGI("viewer", "asset pack %s: %zu files (%zu newly extracted) from %s", name.c_str(), n, copied, apk.c_str());
    return n > 0;
}

void usage() {
    fprintf(stderr,
            "usage: soa-viewer [options]\n"
            "Runs the offline 3.8.0 client unmodified (pure JIT, no natives, no server). emulator-viewer/README.md.\n"
            "  --apk-dir DIR   the unpacked 3.8.0 XAPK: %s, assetinstalltime.apk,\n"
            "                  config.arm64_v8a.apk; optional assetfastfollow.apk / assetondemand1.apk\n"
            "                  (default <repo>/work/extracted/xapk)\n"
            "  --apk FILE      read assets from FILE too (after the XAPK's; repeatable, later wins)\n"
            "  --download-dir DIR  serve builtin_data/ assets missing from the APKs from DIR, an online\n"
            "                  asset tree such as work/download-3.7.0 (as soa / soa-emu --download-dir;\n"
            "                  env SOA_DOWNLOAD_DIR); off by default\n"
            "  --download-prefer  with --download-dir: DIR wins over the APKs (env SOA_DOWNLOAD_PREFER=1)\n"
            "  --lib PATH      the client library (default: extracted from DIR/config.arm64_v8a.apk into the data dir)\n"
            "  --data DIR      the emulated device's data (saves, prefs, asset packs; default\n"
            "                  ~/.local/share/soa-viewer-380, like the port's ~/.local/share/soa-linux;\n"
            "                  never the port's)\n"
            "  --repo DIR      the source checkout (default: found from the executable)\n"
            "  --guest-cpus N|host  CPUs the game sees (default 8)\n"
            "  --size WxH      window size (default: portrait 9:16 at 90%% of the desktop height)\n"
            "  --landscape     default to a 16:9 landscape window\n"
            "  --render-size S the game's screen size: 'desktop' (default), 'window' or WxH\n"
            "  --fullscreen    start in (desktop) fullscreen\n"
            "  --font PATH     the on-screen text box's font (env SOA_FONT; default: a system Japanese font; 'none': off)\n"
            "  --headless      don't show the window (it still renders; screenshots and the control FIFO work)\n"
            "  --shot S:PATH   save a screenshot S seconds after start (repeatable; F12 any time)\n"
            "  --do S:ACTION   scripted input S seconds after start (repeatable): tap:X:Y, drag:X1:Y1:X2:Y2,\n"
            "                  wheel:X:Y:DY, back, text:STRING, shot:PATH, quit\n"
            "  --control FIFO  read the same commands, one per line, from a named pipe (control/soactl.py)\n"
            "  -v / -vv        verbose / trace logging\n",
            kBaseApk);
}

}  // namespace

int main(int argc, char** argv) {
    signal(SIGPIPE, SIG_IGN);
    app::install_host_hooks();
    std::string apk_dir, lib_path, data_dir, repo_arg;
    std::vector<std::string> extra_apks;
    std::string download_dir;
    bool download_prefer = false;
    int guest_cpus = 8;
    app::HostConfig host;
    // "EMULATED" first, so it shows in a truncated taskbar entry too; soa's title has no such tag.
    host.title = "[EMULATED] STAR OCEAN -anamnesis- 3.8.0 offline client (soa-viewer)";
    host.size_note = " (the game's own resolution: no natives)";
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        auto next = [&]() -> std::string {
            if (i + 1 >= argc) {
                usage();
                exit(2);
            }
            return argv[++i];
        };
        if (a == "--apk-dir") apk_dir = next();
        else if (a == "--apk") extra_apks.push_back(next());
        else if (a == "--download-dir") download_dir = next();
        else if (a == "--download-prefer") download_prefer = true;
        else if (a == "--lib") lib_path = next();
        else if (a == "--data") data_dir = next();
        else if (a == "--repo") repo_arg = next();
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
        else if (a == "--shot") host.shots.push_back(next());
        else if (a == "--do") host.actions.push_back(next());
        else if (a == "--control") host.control_path = next();
        else if (a == "-v") g_log_level = LogLevel::Debug;
        else if (a == "-vv") g_log_level = LogLevel::Trace;
        else {
            usage();
            return a == "-h" || a == "--help" ? 0 : 2;
        }
    }

    std::string repo = find_repo(repo_arg);
    if (repo.empty()) LOGW("viewer", "the repository wasn't found (give --repo DIR); defaults need it");
    if (apk_dir.empty()) {
        std::string base = repo_file(repo, std::string("work/extracted/xapk/") + kBaseApk);
        if (base.empty()) fatal("work/extracted/xapk/%s not found (give --apk-dir)", kBaseApk);
        apk_dir = parent(base);
    }
    for (const char* f : {kBaseApk, "assetinstalltime.apk"})
        if (!exists(apk_dir + "/" + f)) fatal("--apk-dir %s: %s is missing", apk_dir.c_str(), f);
    if (data_dir.empty()) {
        // Beside the port's ~/.local/share/soa-linux (port/src/main.cpp).
        const char* h = getenv("HOME");
        data_dir = std::string(h ? h : ".") + "/.local/share/soa-viewer-380";
    }
    make_dirs(data_dir);
    if (lib_path.empty()) lib_path = extract_lib(apk_dir + "/config.arm64_v8a.apk", data_dir + "/libSOA.so");
    LOGI("viewer", "3.8.0 client %s, XAPK %s, data %s: pure JIT, unmodified", lib_path.c_str(), apk_dir.c_str(), data_dir.c_str());

    // The emulated device: a phone with the 3.8.0 app installed (the base APK, the arm64 split and
    // the install-time asset pack), its clock the host's: the client freezes its own game clock at
    // master_global.service_stop_day (emulator-viewer/README.md "Dates").
    device_config().guest_cpus = guest_cpus;
    device_config().app_version = "3.8.0";  // the XAPK's versionName
    vfs_init({data_dir});

    auto t0 = std::chrono::steady_clock::now();
    cpu_global_init();
    hle_init();             // + net_offline.cpp
    jni::Vm::get().init();  // the runtime's Java side, incl. playcore (jni/java_playcore.cpp)
    LoadedLib* lib = load_library(lib_path);
    install_traces(*lib);   // SOA_TRACE
    profile_init(*lib);     // SOA_COVERAGE / SOA_PROFILE
    app::start_watchdog();  // SOA_WATCHDOG

    auto& am = asset_manager();
    if (!am.add_apk(apk_dir + "/" + kBaseApk)) fatal("cannot open %s/%s", apk_dir.c_str(), kBaseApk);
    if (!am.add_apk(apk_dir + "/assetinstalltime.apk")) fatal("cannot open %s/assetinstalltime.apk", apk_dir.c_str());
    // Fast-follow / on-demand packs aren't in the APKPure XAPK (their BGM and talk-scene sounds
    // are missing then, as on a phone that never fetched them), but can be supplied as split APKs.
    for (const char* pack : {"assetfastfollow", "assetondemand1"}) {
        for (std::string f : {apk_dir + "/" + pack + ".apk", apk_dir + "/split_" + pack + ".apk"}) {
            if (exists(f) && install_asset_pack(f, pack)) {
                platform_add_asset_pack(pack);
                break;
            }
        }
        if (!platform_has_asset_pack(pack)) LOGI("viewer", "asset pack %s not present (%s.apk); its sounds are missing", pack, pack);
    }
    for (auto& f : extra_apks)
        if (!am.add_apk(f)) fatal("--apk: cannot open %s", f.c_str());
    // The same option as soa / soa-emu (runtime AssetManager::set_download_dir); a flag wins over the env.
    if (download_dir.empty())
        if (const char* e = getenv("SOA_DOWNLOAD_DIR"); e && *e) download_dir = e;
    if (!download_prefer)
        if (const char* e = getenv("SOA_DOWNLOAD_PREFER"); e && *e && strcmp(e, "0") != 0) download_prefer = true;
    if (!download_dir.empty()) {
        if (!exists(download_dir)) fatal("--download-dir %s: no such directory", download_dir.c_str());
        am.set_download_dir(download_dir, download_prefer);
        LOGI("viewer", "download dir %s: serves assets %s the APKs", download_dir.c_str(), download_prefer ? "before" : "missing from");
    }

    run_initializers(*lib);
    LOGI("viewer", "library loaded and initialised in %.1f s",
         std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
    app::run(*lib, host);
}
