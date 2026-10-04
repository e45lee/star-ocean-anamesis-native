// soa-viewer's command line on CLI11 (cli.h; the shared rules: common/include/soa/cli.h).
#include "cli.h"

#include <soa/cli.h>

#include "app/cli.h"

namespace soa::viewer {

int parse_args(int argc, const char* const* argv, ViewerArgs& a, std::vector<std::string>* names) {
    CLI::App app{"Runs the offline 3.8.0 client unmodified (pure JIT, no natives, no server). emulator-viewer/README.md.", "soa-viewer"};
    cli::setup_app(app);
    app::HostArgs h;
    h.host = &a.host;
    const std::string files = "Game files", device = "The phone";
    app.add_option("--xapk", a.xapk_path,
                   "the 3.8.0 XAPK, read in place (its APKs aren't unpacked; libSOA.so is extracted into the data dir). Default: "
                   "a *.xapk beside the executable, in its game/ folder or in <repo>/apk/, else --apk-dir's default")
        ->type_name("FILE")
        ->group(files);
    app.add_option("--apk-dir", a.apk_dir,
                   std::string("the XAPK unpacked (tools/extract.sh): ") + kBaseApk +
                       ", assetinstalltime.apk, config.arm64_v8a.apk; optional assetfastfollow.apk / assetondemand1.apk "
                       "(default <repo>/work/extracted/xapk when no XAPK is found)")
        ->type_name("DIR")
        ->group(files);
    cli::add_list(app, "--apk", a.extra_apks, "read assets from FILE too (after the XAPK's; repeatable, later wins)")
        ->type_name("FILE")
        ->group(files);
    cli::add_download(app, a.download_dir,
                      "serve builtin_data/ assets missing from the APKs from DIR, an online asset tree such as "
                      "work/download-3.7.0 (as soa / soa-emu --download); off by default")
        ->type_name("DIR")
        ->group(files);
    cli::add_download_prefer(app, a.download_prefer)->group(files);
    app::add_lib(app, a.lib_path, "the client library (default: extracted from config.arm64_v8a.apk into the data dir)")->group(files);
    app::add_data(app, a.data_dir,
                  "the emulated device's data (saves, prefs, asset packs; default ~/.local/share/soa-viewer-380, like the "
                  "port's ~/.local/share/soa-linux-370; Windows %LOCALAPPDATA%\\soa\\viewer-380; never the port's)")
        ->group(files);
    cli::add_repo(app, a.repo)->group(files);
    app::add_guest_cpus(app, h)->group(device);

    app::add_window_options(app, h);
    app::add_driving_options(app, h);
    cli::add_verbose(app, h.verbose)->group("Driving and testing");
    app.footer(
        "Diagnostic switches are environment variables (SOA_TRACE, SOA_PROFILE, SOA_WATCHDOG, ...: runtime/README.md "
        "\"Environment\"); settings are flags only.");
    cli::note_removed_env(app, env::kViewer);

    if (names) *names = cli::option_names(app);
    int rc = cli::parse(app, argc, argv);
    if (rc >= 0) return rc;
    if (h.headless >= 0) a.host.hidden = h.headless == 1;
    a.guest_cpus = h.guest_cpus;
    a.gdb = h.gdb;
    a.verbose = h.verbose;
    return -1;
}

}  // namespace soa::viewer
