// The runtime's bring-up for the host programs (app/boot.h), once instead of in each main().
#include "soaruntime/app/boot.h"

#include <chrono>
#include <string>

#include "soaruntime/android/ndk.h"
#include "soaruntime/app/host.h"
#include "soaruntime/core/cpu.h"
#include "soaruntime/core/gdbstub.h"
#include "soaruntime/core/hle.h"
#include "soaruntime/core/loader.h"
#include "soaruntime/core/log.h"
#include "soaruntime/core/profile.h"
#include "soaruntime/core/vfs.h"
#include "soaruntime/jni/jvm.h"

namespace soa {
void install_traces(LoadedLib& lib);  // core/trace.cpp: SOA_TRACE
}

namespace soa::app {

LoadedLib* boot(const BootConfig& cfg, std::string* error) {
    std::string err;
    auto fail = [&](std::string msg) -> LoadedLib* {
        if (error) *error = std::move(msg);
        return nullptr;
    };
    vfs_init({cfg.data_dir});

    auto t0 = std::chrono::steady_clock::now();
    cpu_global_init();
    // --gdb: the debugger hooks go on before any guest code runs
    if (!cfg.gdb.empty() && !gdb_listen(cfg.gdb, &err)) return fail(err);
    hle_init();             // + the host's registrars (platform370: fmod, the clock, the network)
    jni::Vm::get().init();  // + the host's Java classes and overrides
    LoadedLib* lib = load_library(cfg.lib_path, &err);
    if (!lib) return fail("can't load the game library: " + err);  // a wrong --lib: an error, not an abort
    if (cfg.after_load) cfg.after_load(*lib);
    if (cfg.traces) install_traces(*lib);  // SOA_TRACE
    profile_init(*lib);                     // SOA_COVERAGE / SOA_PROFILE
    start_watchdog();                       // SOA_WATCHDOG

    auto& am = asset_manager();
    if (!cfg.download_dir.empty()) {
        if (!am.set_download_dir(cfg.download_dir, cfg.download_prefer))
            return fail("--download " + cfg.download_dir + ": neither a folder nor a zip");
        LOGI(cfg.log_tag, "download dir %s (%s the APK)", cfg.download_dir.c_str(), am.download_prefer() ? "preferred over" : "fallback for");
    }
    if (cfg.add_assets && !cfg.add_assets(am, &err)) return fail(err.empty() ? "the host's assets couldn't be added" : err);
    for (auto& f : cfg.apks)
        if (!am.add_apk(f)) return fail("--apk: cannot open " + f);

    run_initializers(*lib);
    LOGI(cfg.log_tag, "library loaded and initialised in %.1f s", std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count());
    return lib;
}

}  // namespace soa::app
