// soa-emu's command line on CLI11 (cli.h; the shared rules: common/include/soa/cli.h).
#include "cli.h"

#include <soa/cli.h>

#include "soaruntime/app/cli.h"
#include "platform370/cli.h"

namespace soa::emu {

int parse_args(int argc, const char* const* argv, EmuArgs& a, std::vector<std::string>* names) {
    CLI::App app{"Runs the 3.7.0 online client unmodified (pure JIT, no natives). emulator/README.md.", "soa-emu"};
    cli::setup_app(app);
    a.p370.device_clock = kDefaultDeviceClock;
    app::HostArgs h;
    h.host = &a.host;
    const std::string files = "Game files", device = "The phone", net = "Network (soa-server)";
    app::add_lib(app, a.lib_path,
                 "the client library (default <repo>/work/libSOA-3.7.0.so, else the APK's lib/arm64-v8a/libSOA.so, extracted "
                 "once into DATA/libSOA-3.7.0.so)")
        ->group(files);
    cli::add_list(app, "--apk", a.apks,
                  "the APK whose assets the client reads (default <repo>/apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk, else a "
                  "3.7.0 APK beside the program or in its game/ folder: a release package, README.txt); repeatable, later wins")
        ->type_name("FILE")
        ->group(files);
    app::add_data(app, a.data_dir,
                  "the emulated device's data (saves, prefs, downloads; default ~/.local/share/soa-emulator-370/phone, beside "
                  "the port's ~/.local/share/soa-linux-370; Windows %LOCALAPPDATA%\\soa\\emulator-370\\phone; never the port's: "
                  "its cached libSOA.so and save don't belong here)")
        ->group(files);
    cli::add_download(app, a.download_dir,
                      "temporary stand-in for the CDN: serve assets missing from the APK from the 3.7.0 download (the zip "
                      "work/SOA-3.7.0-canonical-data.zip, read in place, or an extracted folder); off by default (soa-server's CDN serves them)")
        ->group(files);
    cli::add_download_prefer(app, a.download_prefer)->group(files);
    cli::add_repo(app, a.repo)->group(files);

    platform370::add_device_options(app, a.p370, device);
    app::add_guest_cpus(app, h)->group(device);

    app.add_option_function<std::string>(
           "--server", [&a](const std::string& v) { platform370::set_server(a.p370.netcfg, v); },
           "the game server: soa-server's --listen (default 127.0.0.1:44300); the client's production-game.so-ana.com "
           "resolves to HOST and its port 443 becomes PORT")
        ->type_name("HOST[:PORT]")
        ->group(net);
    platform370::add_network_options(app, a.p370, net);

    app::add_window_options(app, h);
    app::add_driving_options(app, h);
    cli::add_verbose(app, h.verbose)->group("Driving and testing");
    app.footer(
        "Diagnostic switches are environment variables (SOA_TRACE, SOA_PROFILE, SOA_WATCHDOG, ...: runtime/README.md "
        "\"Environment\"); settings are flags only.");
    cli::note_removed_env(app, env::kEmu);

    if (names) *names = cli::option_names(app);
    int rc = cli::parse(app, argc, argv);
    if (rc >= 0) return rc;
    if (h.headless >= 0) a.host.hidden = h.headless == 1;
    a.guest_cpus = h.guest_cpus;
    a.gdb = h.gdb;
    a.verbose = h.verbose;
    return -1;
}

}  // namespace soa::emu
