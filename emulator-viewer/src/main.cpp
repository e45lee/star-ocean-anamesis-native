// soa-viewer: the offline 3.8.0 client of STAR OCEAN: anamnesis, as shipped, under the JIT host
// runtime (runtime/). No native replacements, no restore code, no server: the client is the
// shipped libSOA.so of the 3.8.0 XAPK (config.arm64_v8a.apk) with the XAPK's assets (base APK +
// the install-time asset pack). The runtime was built for this build's imports and Java methods
// (incl. Play Asset Delivery: jni/java_playcore.cpp), so the viewer adds only one platform
// answer: the dead service's host names don't resolve (net_offline.cpp). emulator-viewer/README.md.
#include <soa/env.h>
#include <soa/install.h>
#include <soa/paths.h>
#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iterator>
#include <memory>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "soaruntime/android/ndk.h"
#include "soaruntime/android/platform.h"
#include "soaruntime/android/zip.h"
#include "soaruntime/app/boot.h"
#include "soaruntime/app/host.h"
#include "soaruntime/core/cpu.h"
#include "soaruntime/core/device.h"
#include "soaruntime/core/gdbstub.h"
#include "soaruntime/core/hle.h"
#include "soaruntime/core/loader.h"
#include "soaruntime/core/log.h"
#include "soaruntime/core/profile.h"
#include "soaruntime/core/vfs.h"
#include "soaruntime/jni/jvm.h"
#include "cli.h"

using namespace soa;

namespace {

using viewer::kBaseApk;

bool exists(const std::string& p) {
    struct stat st;
    return !p.empty() && stat(p.c_str(), &st) == 0;
}
bool is_dir(const std::string& p) {
    struct stat st;
    return !p.empty() && stat(p.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}
std::string parent(const std::string& p) {
    size_t s = p.find_last_of('/');
    if (s == std::string::npos) return "";
    return s == 0 ? "/" : p.substr(0, s);
}

// The source checkouts searched for repo files (apk/, work/extracted/xapk): the repo root and, in a
// git worktree whose work/ links into it, the main checkout (which holds the untracked XAPK).
// common soa/install.h repo_roots: --repo; in a development build also upwards from the executable
// (build/emulator-viewer/soa-viewer) or the working directory; a release build never searches for
// a checkout around it. Empty when there is none.
std::vector<std::string> find_checkouts(const std::string& given) {
    soa::install::RepoRoots r = soa::install::repo_roots(given);  // (install::is_checkout)
    if (!r.warning.empty()) LOGW("viewer", "%s", r.warning.c_str());
    std::vector<std::string> v;
    if (!r.root.empty()) {
        LOGI("viewer", "%s", r.describe().c_str());
        v.push_back(r.root);
        if (!r.main_checkout.empty()) v.push_back(r.main_checkout);
    }
    return v;
}

// The game package: the 3.8.0 XAPK read in place (--xapk FILE, or one found: find_xapk), the XAPK
// unpacked into a directory (--apk-dir DIR, tools/extract.sh), or both: an APK the XAPK lacks (e.g.
// the fast-follow / on-demand asset packs the APKPure XAPK doesn't carry) is then taken from the
// directory. Its APKs (the base APK, the arm64 split, the asset packs) open as zip archives either way.
struct GamePackage {
    std::string xapk_path, dir;            // either or both
    std::unique_ptr<ZipArchive> xapk;      // --xapk: the outer archive
    std::string cache;                     // --xapk: <data>/xapk-cache, for a member stored deflated

    bool in_xapk(const std::string& apk) const { return xapk && xapk->find(apk) != nullptr; }
    bool in_dir(const std::string& apk) const { return !dir.empty() && exists(dir + "/" + apk); }
    std::string where() const {
        if (!xapk) return "dir " + dir;
        return dir.empty() ? "XAPK " + xapk_path : "XAPK " + xapk_path + " (else dir " + dir + ")";
    }
    bool has(const std::string& apk) const { return in_xapk(apk) || in_dir(apk); }
    std::string describe(const std::string& apk) const {
        return in_xapk(apk) || (xapk && !in_dir(apk)) ? xapk_path + ":" + apk : dir + "/" + apk;
    }
    // The APK `apk`, nullptr when the package hasn't it: the XAPK's member first, else the
    // directory's file. An XAPK's stored member is read in place (the APKPure XAPK stores every
    // APK); a deflated one is extracted once into the cache (again when its CRC-32 or size changes).
    std::unique_ptr<ZipArchive> open(const std::string& apk) const {
        auto z = std::make_unique<ZipArchive>();
        if (!in_xapk(apk)) return in_dir(apk) && z->open(dir + "/" + apk) ? std::move(z) : nullptr;
        const ZipArchive::Entry* e = xapk->find(apk);
        if (z->open_member(*xapk, apk)) return z;
        std::string out = cache + "/" + apk;
        if (!fresh(out, *e)) {
            LOGI("viewer", "extracting %s from the XAPK (stored deflated) into %s", apk.c_str(), cache.c_str());
            if (!extract_to(*xapk, *e, out)) fatal("cannot extract %s from %s", apk.c_str(), xapk_path.c_str());
        }
        return z->open(out) ? std::move(z) : nullptr;
    }

    // A file extracted from an archive entry is current when its stamp (OUT.src: the entry's
    // CRC-32 and size) matches and its size is right.
    static std::string stamp_of(const ZipArchive::Entry& e) {
        char b[64];
        snprintf(b, sizeof b, "crc32 %08x size %llu\n", e.crc, (unsigned long long)e.size);
        return b;
    }
    static bool fresh(const std::string& out, const ZipArchive::Entry& e) {
        struct stat st;
        if (stat(out.c_str(), &st) != 0 || (u64)st.st_size != e.size) return false;
        std::ifstream f(out + ".src");
        std::string have((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        return have == stamp_of(e);
    }
    static bool extract_to(const ZipArchive& z, const ZipArchive::Entry& e, const std::string& out) {
        std::vector<uint8_t> data;
        if (!z.extract(e, data)) return false;
        make_dirs(parent(out));
        std::string tmp = out + ".tmp";
        std::ofstream o(tmp, std::ios::binary);
        o.write((const char*)data.data(), data.size());
        o.close();
        if (!o.good() || rename(tmp.c_str(), out.c_str()) != 0) return false;
        std::ofstream(out + ".src") << stamp_of(e);
        return true;
    }
};

// The client library: lib/arm64-v8a/libSOA.so of config.arm64_v8a.apk, extracted into the
// viewer's data dir (again when the entry's CRC-32 or size differs from the copy's stamp,
// libSOA.so.src), as the package manager installs it. The port keeps its own copy in its own data
// dir; they are never shared.
std::string extract_lib(const GamePackage& pkg, const std::string& out) {
    auto z = pkg.open("config.arm64_v8a.apk");
    if (!z) fatal("%s is missing", pkg.describe("config.arm64_v8a.apk").c_str());
    auto* e = z->find("lib/arm64-v8a/libSOA.so");
    if (!e) fatal("%s has no lib/arm64-v8a/libSOA.so", pkg.describe("config.arm64_v8a.apk").c_str());
    if (GamePackage::fresh(out, *e)) return out;
    LOGI("viewer", "extracting libSOA.so from %s", pkg.describe("config.arm64_v8a.apk").c_str());
    if (!GamePackage::extract_to(*z, *e, out)) fatal("cannot extract libSOA.so into %s", out.c_str());
    return out;
}

// A Play Asset Delivery pack given as a split APK (fast-follow / on-demand packs; the APKPure
// XAPK has only the install-time one): its assets/ go to <files>/assetpacks/<name>/assets, the
// STORAGE_FILES layout Play Core gives such packs (docs/notes.md "Asset packs"). Files already
// there with the right size are kept.
bool install_asset_pack(const ZipArchive& z, const std::string& from, const std::string& name) {
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
    LOGI("viewer", "asset pack %s: %zu files (%zu newly extracted) from %s", name.c_str(), n, copied, from.c_str());
    return n > 0;
}

// An XAPK that holds the 3.8.0 app (its base APK and arm64 split).
bool is_game_xapk(const std::string& path) {
    ZipArchive z;
    return z.open(path) && z.find(kBaseApk) && z.find("config.arm64_v8a.apk");
}

// The XAPK when no --xapk / --apk-dir names the game: the first *.xapk holding the app in the
// install dirs (the executable's folder and its game/ subfolder: common/include/soa/install.h, the
// lookup all four programs share), then the checkouts' apk/ (find_checkouts: none in a release build
// without --repo).
std::string find_xapk(const std::vector<std::string>& repo) {
    std::vector<std::string> dirs = soa::install::install_dirs();
    for (auto& r : repo) dirs.push_back(r + "/apk");
    for (auto& f : soa::install::files_with_ext(dirs, ".xapk"))
        if (is_game_xapk(f)) return f;
    return "";
}

}  // namespace

int main(int argc, char** argv) {
    std::string gdb_addr;  // --gdb HOST:PORT (core/gdbstub.h)
    env::warn_removed_env("soa-viewer", env::kViewer);  // SOA_* settings that are flags now
    signal(SIGPIPE, SIG_IGN);
    app::install_host_hooks();
    // The command line (cli.cpp: the runtime programs' shared options and soa-viewer's).
    viewer::ViewerArgs args;
    // "EMULATED" first, so it shows in a truncated taskbar entry too; soa's title has no such tag.
    args.host.title = "[EMULATED] STAR OCEAN -anamnesis- 3.8.0 offline client (soa-viewer)";
    args.host.size_note = " (the game's own resolution: no natives)";
    if (int rc = viewer::parse_args(argc, argv, args); rc >= 0) return rc;
    if (args.verbose) g_log_level = args.verbose > 1 ? LogLevel::Trace : LogLevel::Debug;
    gdb_addr = args.gdb;
    std::string &apk_dir = args.apk_dir, &xapk_path = args.xapk_path, &lib_path = args.lib_path, &data_dir = args.data_dir,
                &repo_arg = args.repo, &download_dir = args.download_dir;
    const std::vector<std::string>& extra_apks = args.extra_apks;
    const bool download_prefer = args.download_prefer;
    const int guest_cpus = args.guest_cpus;
    app::HostConfig& host = args.host;

    const std::vector<std::string> repo = find_checkouts(repo_arg);
    if (repo.empty())
        LOGI("viewer", "%s: the XAPK is looked up beside the program (README.txt)",
             soa::install::kReleasePackage ? "release build: no source checkout is searched (only --repo DIR)" : "no source checkout");
    // Beside the port's (soa/paths.h): ~/.local/share/soa-viewer-380, on Windows %LOCALAPPDATA%\soa\viewer-380.
    if (data_dir.empty()) data_dir = soa::default_data_dir("soa-viewer-380", "viewer-380");
    make_dirs(data_dir);
    // The game: --xapk and/or --apk-dir, else an XAPK found (find_xapk), else the unpacked one in
    // work/. With an XAPK, the unpacked one (--apk-dir, default work/extracted/xapk when present)
    // supplies the APKs the XAPK lacks.
    const bool apk_dir_given = !apk_dir.empty();
    if (apk_dir.empty() && xapk_path.empty()) xapk_path = find_xapk(repo);
    if (apk_dir.empty()) {
        std::string base = soa::install::find_in_roots(repo, std::string("work/extracted/xapk/") + kBaseApk);
        if (!base.empty()) apk_dir = parent(base);
        if (xapk_path.empty()) {
            if (base.empty())
                fatal("the 3.8.0 XAPK wasn't found: give --xapk FILE (or put the *.xapk in %s/%s, beside soa-viewer, or in the "
                      "repository's apk/: see README.txt), or --apk-dir DIR (tools/extract.sh)",
                      soa::install::exe_dir().c_str(), soa::install::kGameSubdir);
        }
    }
    if (apk_dir_given && !is_dir(apk_dir)) fatal("--apk-dir %s: not a directory", apk_dir.c_str());
    GamePackage pkg;
    pkg.dir = apk_dir;
    if (!xapk_path.empty()) {
        pkg.xapk_path = xapk_path;
        pkg.xapk = std::make_unique<ZipArchive>();
        if (!pkg.xapk->open(xapk_path)) fatal("--xapk %s: not a zip archive", xapk_path.c_str());
        pkg.cache = data_dir + "/xapk-cache";
    }
    for (const char* f : {kBaseApk, "assetinstalltime.apk", "config.arm64_v8a.apk"})
        if (!pkg.has(f)) fatal("%s: %s is missing", pkg.where().c_str(), f);
    if (lib_path.empty()) lib_path = extract_lib(pkg, data_dir + "/libSOA.so");
    LOGI("viewer", "3.8.0 client %s, game from %s, data %s: pure JIT, unmodified", lib_path.c_str(), pkg.where().c_str(), data_dir.c_str());

    // The emulated device: a phone with the 3.8.0 app installed (the base APK, the arm64 split and
    // the install-time asset pack), its clock the host's: the client freezes its own game clock at
    // master_global.service_stop_day (emulator-viewer/README.md "Dates").
    device_config().guest_cpus = guest_cpus;
    device_config().app_version = "3.8.0";  // the XAPK's versionName

    // The runtime's bring-up (runtime/include/soaruntime/app/boot.h); the runtime's Java side
    // includes playcore (jni/java_playcore.cpp).
    app::BootConfig boot;
    boot.log_tag = "viewer";
    boot.data_dir = data_dir;
    boot.lib_path = lib_path;
    boot.gdb = gdb_addr;
    boot.download_dir = download_dir;  // the same option as soa / soa-emu: serves assets missing from the APKs
    boot.download_prefer = download_prefer;
    boot.apks = extra_apks;
    boot.add_assets = [&](AssetManager& am, std::string* error) {
        auto t_pkg = std::chrono::steady_clock::now();
        for (const char* f : {kBaseApk, "assetinstalltime.apk"}) {
            auto z = pkg.open(f);
            if (!z || !am.add_zip(std::move(z), pkg.describe(f))) {
                *error = "cannot open " + pkg.describe(f);
                return false;
            }
        }
        // Fast-follow / on-demand packs aren't in the APKPure XAPK (their BGM and talk-scene sounds
        // are missing then, as on a phone that never fetched them), but can be supplied as split APKs.
        for (const char* pack : {"assetfastfollow", "assetondemand1"}) {
            for (std::string f : {std::string(pack) + ".apk", std::string("split_") + pack + ".apk"}) {
                auto z = pkg.has(f) ? pkg.open(f) : nullptr;
                if (z && install_asset_pack(*z, pkg.describe(f), pack)) {
                    platform_add_asset_pack(pack);
                    break;
                }
            }
            if (!platform_has_asset_pack(pack)) LOGI("viewer", "asset pack %s not present (%s.apk); its sounds are missing", pack, pack);
        }
        LOGI("viewer", "game assets indexed from %s in %.3f s", pkg.where().c_str(),
             std::chrono::duration<double>(std::chrono::steady_clock::now() - t_pkg).count());
        return true;
    };
    std::string boot_error;
    LoadedLib* lib = app::boot(boot, &boot_error);
    if (!lib) {
        fprintf(stderr, "soa-viewer: %s\n", boot_error.c_str());
        return 2;
    }
    app::run(*lib, host);
}
