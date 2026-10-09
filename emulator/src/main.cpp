// soa-emu: the 3.7.0 online client of STAR OCEAN: anamnesis, as shipped, under the JIT host
// runtime (runtime/). No native replacements, no restore code, no in-process server: the client is the
// shipped work/libSOA-3.7.0.so with the 3.7.0 APK's assets; only the platform layer under it (HLE
// imports, the Java methods, the network glue) is ours: the 3.7.0 platform library
// (platform370/), plus its one native patch that hides master_global.service_stop_day so the
// client runs on the real date. This file maps the command line onto platform370::Config and
// brings the runtime up. emulator/README.md, platform370/README.md.
#include <soa/env.h>
#include <soa/game_files.h>
#include <soa/paths.h>
#include <soa/install.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <chrono>
#include <cstdio>
#include <string>
#include <vector>

#include "soaruntime/android/ndk.h"
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
#include "platform370/platform370.h"
#include "cli.h"

using namespace soa;

namespace {

bool exists(const std::string& p) {
    struct stat st;
    return !p.empty() && stat(p.c_str(), &st) == 0;
}

// The source checkouts searched for repo files (apk/, work/libSOA-3.7.0.so): the repo root and, in
// a git worktree whose work/ links into it, the main checkout (where untracked files such as
// apk/*.apk live). common soa/install.h repo_roots: --repo; in a development build also upwards
// from the executable (build/emulator/soa-emu) or the working directory; a release build never
// searches for a checkout around it. Empty when there is none.
std::vector<std::string> find_checkouts(const std::string& given) {
    soa::install::RepoRoots r = soa::install::repo_roots(given);  // (install::is_checkout)
    if (!r.warning.empty()) LOGW("emu", "%s", r.warning.c_str());
    std::vector<std::string> v;
    if (!r.root.empty()) {
        LOGI("emu", "%s", r.describe().c_str());
        v.push_back(r.root);
        if (!r.main_checkout.empty()) v.push_back(r.main_checkout);
    }
    return v;
}

}  // namespace

int main(int argc, char** argv) {
    std::string gdb_addr;  // --gdb HOST:PORT (core/gdbstub.h; app::boot)
    env::warn_removed_env("soa-emu", env::kEmu);  // SOA_* settings that are flags now
    signal(SIGPIPE, SIG_IGN);
    app::install_host_hooks();
    // The command line (cli.cpp: the runtime programs' shared options, the 3.7.0 phone's, soa-emu's).
    emu::EmuArgs args;
    // "EMULATED" first, so it shows in a truncated taskbar entry too; soa's title has no such tag.
    args.host.title = "[EMULATED] STAR OCEAN -anamnesis- 3.7.0 online client (soa-emu)";
    if (int rc = emu::parse_args(argc, argv, args); rc >= 0) return rc;
    if (args.verbose) g_log_level = args.verbose > 1 ? LogLevel::Trace : LogLevel::Debug;
    gdb_addr = args.gdb;
    std::string &lib_path = args.lib_path, &data_dir = args.data_dir, &download_dir = args.download_dir, &repo_arg = args.repo;
    const bool download_prefer = args.download_prefer;
    std::vector<std::string>& apks = args.apks;
    const int guest_cpus = args.guest_cpus;
    platform370::Config& p370 = args.p370;
    app::HostConfig& host = args.host;

    const std::vector<std::string> repo = find_checkouts(repo_arg);
    if (repo.empty())
        LOGI("emu", "%s: the game files are looked up beside the program (README.txt)",
             soa::install::kReleasePackage ? "release build: no source checkout is searched (only --repo DIR)" : "no source checkout");
    if (apks.empty()) {
        std::string apk = soa::install::find_in_roots(repo, "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk");
        if (apk.empty()) {
            // a release package (README.md "Packaging"): a 3.7.0 APK beside the program or in game/
            std::vector<std::string> notes;
            apk = soa::install::find_apk(soa::install::install_dirs(), &notes);
            for (auto& n : notes) LOGW("emu", "%s", n.c_str());
            if (apk.empty()) fatal("the 3.7.0 APK wasn't found (give --apk); %s", soa::install::missing_hint().c_str());
            LOGI("emu", "the 3.7.0 APK %s (found beside the program)", apk.c_str());
        }
        apks.push_back(apk);
    }
    // Beside the port's (soa/paths.h): ~/.local/share/soa-emulator-370/phone, on Windows
    // %LOCALAPPDATA%\soa\emulator-370\phone; scripts/run-emulator-370.sh (and the Windows
    // launcher) use the same phone/.
    if (data_dir.empty()) data_dir = soa::default_data_dir("soa-emulator-370/phone", "emulator-370\\phone");
    soa::make_dir_tree(data_dir);
    if (lib_path.empty()) {
        lib_path = soa::install::find_in_roots(repo, "work/libSOA-3.7.0.so");
        if (lib_path.empty()) {
            // the APK's own lib/arm64-v8a/libSOA.so, extracted once into the data dir (as soa does)
            lib_path = data_dir + "/libSOA-3.7.0.so";
            if (!exists(lib_path)) {
                LOGI("emu", "extracting %s from %s", soa::install::kLibEntry, apks[0].c_str());
                if (!soa::install::extract_entry(apks[0], soa::install::kLibEntry, lib_path))
                    fatal("couldn't extract %s from %s (give --lib)", soa::install::kLibEntry, apks[0].c_str());
            }
        }
    }
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

    // The runtime's bring-up (runtime/include/soaruntime/app/boot.h).
    app::BootConfig boot;
    boot.log_tag = "emu";
    boot.data_dir = data_dir;
    boot.lib_path = lib_path;
    boot.gdb = gdb_addr;
    boot.download_dir = download_dir;
    boot.download_prefer = download_prefer;
    boot.apks = apks;  // the 3.7.0 APK is a single APK (no splits, no asset packs)
    boot.after_load = [](LoadedLib& lib) {
        // platform370's native patch: before any guest code runs.
        if (platform370::install_patches(lib) == platform370::PatchStatus::Disabled)
            LOGI("emu", "--no-patch: no native patches; the client's service-end check is live%s",
                 platform370::local_time() ? " (local time keeps daylight saving: --no-dst-fix for the shipped reading)" : "");
        platform370::install_language(lib);  // --lang / --voice-lang
    };
    std::string boot_error;
    LoadedLib* lib = app::boot(boot, &boot_error);
    if (!lib) {
        fprintf(stderr, "soa-emu: %s\n", boot_error.c_str());
        return 2;
    }
    app::run(*lib, host);
}
