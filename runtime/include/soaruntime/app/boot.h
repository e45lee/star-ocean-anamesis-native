#pragma once
// The runtime's bring-up, the same in every host program (soa, soa-emu, soa-viewer): the guest
// filesystem, the JIT, the debugger, the HLE imports and the JVM, the game library, the
// diagnostics (SOA_TRACE, SOA_PROFILE / SOA_COVERAGE, SOA_WATCHDOG), the assets and the library's
// initializers. A host sets up what is its own first (device_config(), platform370::install: both
// before hle_init), plugs its steps into the hooks, and then hands the library to app::run:
//
//   app::install_host_hooks();
//   ... device_config(), platform370::install(cfg) ...
//   std::string err;
//   LoadedLib* lib = app::boot(cfg, &err);
//   if (!lib) { fprintf(stderr, "PROGRAM: %s\n", err.c_str()); return 2; }
//   app::run(*lib, host);
#include <functional>
#include <string>
#include <vector>

namespace soa {
struct LoadedLib;
class AssetManager;

namespace app {

struct BootConfig {
    const char* log_tag = "main";  // the tag of boot's log lines
    std::string data_dir;          // the phone's data directory: the guest filesystem's root (vfs_init)
    std::string lib_path;          // the game library (load_library)
    std::string gdb;               // --gdb HOST:PORT: the debugger listens before any guest code runs ("" = off)
    std::string download_dir;      // --download: the download tree (AssetManager::set_download_dir; "" = none)
    bool download_prefer = false;  // --download-prefer
    std::vector<std::string> apks; // APKs added to the assets after add_assets' (AssetManager::add_apk)
    bool traces = true;            // SOA_TRACE's hooks (core/trace.cpp)

    // Hooks (optional), in bring-up order:
    // after the library is loaded, before any of its code runs: native patches, the port's natives
    std::function<void(LoadedLib& lib)> after_load;
    // the host's own assets (archives, the stand-in overlay), after the download tree and before
    // `apks`; false: boot fails with `*error` (when the hook set it)
    std::function<bool(AssetManager& am, std::string* error)> add_assets;
};

// Brings the runtime up and runs the library's initializers: vfs_init, cpu_global_init, the gdb
// stub (--gdb), hle_init, the JVM, load_library, after_load, the traces, profile_init,
// start_watchdog, the download tree, add_assets, the APKs, run_initializers. The library, or
// nullptr when a step failed (the debugger can't listen, the library isn't a loadable AArch64
// library, the download tree or an APK can't be opened, add_assets failed), with `*error` saying
// why; the host reports it and exits.
LoadedLib* boot(const BootConfig& cfg, std::string* error);

}  // namespace app
}  // namespace soa
