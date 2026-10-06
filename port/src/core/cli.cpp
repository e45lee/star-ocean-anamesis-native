// soa's command line on CLI11 (core/cli.h; the shared rules: common/include/soa/cli.h). Groups as
// in `soa --help`: general, client (game files, the phone, the window, driving and testing,
// diagnostics), server.
#include "core/cli.h"

#include <soa/cli.h>

#include "app/cli.h"
#include "platform370/cli.h"
#include "soaserver/cli.h"

namespace soa {

int parse_soa_args(int argc, const char* const* argv, SoaArgs& a, std::vector<std::string>* names) {
    CLI::App app{"The 3.7.0 client on the desktop (port/README.md), with the game server in-process (--server inproc, the "
                 "default) or soa-server (--server HOST[:PORT]).",
                 "soa"};
    cli::setup_app(app);
    RunOptions& opt = *a.opt;
    ClientOptions& cl = opt.client;
    app::HostArgs h;
    h.host = &a.host;
    const std::string general = "General", files = "Client: game files", device = "Client: the phone",
                      drive = "Client: driving and testing", diag = "Client: diagnostics";

    cli::add_repo(app, opt.repo_dir)->group(general);
    cli::add_verbose(app, h.verbose)->group(general);

    app.add_option("--apk", a.apk_path,
                   "the 3.7.0 APK (default <repo>/apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk, else a 3.7.0 APK beside the "
                   "program or in its game/ folder: a release package, README.txt)")
        ->type_name("FILE")
        ->group(files);
    app::add_lib(app, a.lib_path,
                 "the libSOA.so (default: lib/arm64-v8a/libSOA.so of the APK, extracted once into DATA/libSOA-3.7.0.so; else "
                 "<repo>/work/libSOA-3.7.0.so)")
        ->group(files);
    app::add_data(app, a.data_dir,
                  "the phone's data dir: game data, saves, and in-process the server's state (default "
                  "~/.local/share/soa-linux-370; Windows %LOCALAPPDATA%\\soa\\port-370)")
        ->group(files);
    cli::add_download(app, cl.download_dir,
                      "the 3.7.0 download (the online game's downloaded tree): a folder, or the zip SOA-3.7.0-canonical-data.zip "
                      "read in place; the client's asset fallback for builtin_data/ files the APK lacks. Required with --server "
                      "inproc, whose CDN serves it too (default <repo>/work/download-3.7.0, else a download folder or zip beside "
                      "the program or in its game/ folder); off by default with --server HOST, whose client downloads from "
                      "soa-server's CDN")
        ->group(files);
    cli::add_download_prefer(app, cl.download_prefer)->group(files);
    cli::add_standin_assets(app, cl.standin_dir, cl.standin_off,
                            "made-up stand-in files (e.g. lost gacha banners) for builtin_data/ assets that neither the APK nor "
                            "--download have; --server inproc defaults it to standin-assets and its CDN serves them (off / 0 = "
                            "none)")
        ->group(files);

    platform370::add_device_options(app, a.p370, device);
    app::add_guest_cpus(app, h)->group(device);
    app.add_option("--natives", a.natives,
                   "native replacements: route (every registered one, i.e. the in-process route's FakeApiCaller hooks (not "
                   "with --server HOST) and the port's own hooks; \"all\" is a synonym) or none (pure JIT)")
        ->type_name("route|none")
        ->default_str("route")
        ->trigger_on_parse()
        ->group(device);
    cli::add_ordered_flag(app, "--no-native", [&a] { a.natives = "none"; }, "the same as --natives none")->group(device);
    platform370::add_network_options(app, a.p370, device + " (with --server HOST)");

    app::add_window_options(app, h, "Client: window");
    app.add_flag("--hires")->description("no effect (the game renders at its own resolution)")->group("Client: window");
    app.add_flag("--legacy-res", a.legacy_res, "no effect (the game renders at its own resolution)")->group("Client: window");

    app::add_driving_options(app, h, drive);
    app.add_option("--selftest", a.test_filter, "the self-tests (tests matching F) on the booted game, no natives installed; headless")
        ->type_name("[F]")
        ->expected(0, 1)
        ->group(drive);
    app.add_flag("--smoke", a.smoke, "load the library, run a quick self-test and exit")->group(drive);
    app.add_flag("--list-native", a.list_native, "print the native replacements (symbol, note) and exit")->group(drive);
    app.add_option_function<std::string>(
           "--apk-dir", [&a](const std::string&) { a.apk_dir_given = true; },
           "ignored (kept for old scripts; the port runs the 3.7.0 APK, --apk)")
        ->type_name("DIR")
        ->group(drive);

    app.add_option("--fake-server-schema", cl.fake_server_schema, "write the response key schema there at CGame::OnInitialize")
        ->type_name("FILE")
        ->group(diag);
    app.add_option_function<std::string>(
           "--memstats",
           [&cl](const std::string& v) {
               long s = 1;
               if (!v.empty() && !cli::parse_long_in(v, 1, 86400, &s))
                   cli::bad_value("--memstats", "expected seconds 1..86400, got \"" + v + "\"");
               cl.memstats = (int)s;
           },
           "a memory snapshot in the log at every phase change; with S (> 1) also every S seconds (control \"memstats\" "
           "takes one on demand)")
        ->type_name("[S]")
        ->expected(0, 1)
        ->group(diag);
    cli::add_list(app, "--live-check", a.live_checks,
                  "check a native family against the guest in the run (port/src/native/README.md \"Live checks\"; no family is "
                  "registered now)")
        ->type_name("FAMILY[,FAMILY..][:KEY[=VALUE]..]")
        ->group(diag);

    // ---- server options (soa-server's flags; only with --server inproc) ----
    const std::string server = server::kServerOptionsGroup;
    app.add_option_function<std::string>(
           "--server",
           [&a](const std::string& v) {
               a.server_mode = v;
               if (v == "inproc") return;
               std::string host;
               int port = 0;
               if (!platform370::split_host_port(v, &host, &port)) cli::bad_value("--server", "expected inproc or HOST[:PORT], got \"" + v + "\"");
               a.p370.netcfg.server_host = host;
               if (port) a.p370.netcfg.server_port = port;
           },
                   "the game server. inproc (default): the local server library answers in-process through the FakeApiCaller "
                   "route, its CDN in memory (state in DATA/server.sqlite3); HOST[:PORT]: the client's own NetworkApiCaller "
                   "talks to soa-server's --listen (default port 44300), production-game.so-ana.com resolving to HOST "
                   "(platform370's network glue). The options below apply only with inproc: give them to soa-server otherwise")
        ->type_name("inproc|HOST[:PORT]")
        ->group(server);
    server::add_server_options(app, opt.server, "DATA/server.sqlite3");
    app.add_flag_callback("--restore", [] { cli::bad_value("--restore", "gone: the in-process server is the default (--server inproc)"); })
        ->group("");

    app.footer(
        "Diagnostic and test switches are environment variables (SOA_TRACE, SOA_PROFILE, SOA_WATCHDOG, SOA_SELFTEST_*, ...: "
        "port/README.md \"Environment\"); settings are flags only.");
    cli::note_removed_env(app, env::kSoa);

    if (names) *names = cli::option_names(app);
    int rc = cli::parse(app, argc, argv);
    if (rc >= 0) return rc;
    a.selftest = app.count("--selftest") > 0;
    if (app.count("--memstats") && !cl.memstats) cl.memstats = 1;
    a.headless = h.headless;
    cl.guest_cpus = h.guest_cpus;
    a.gdb = h.gdb;
    a.verbose = h.verbose;
    a.server_flags = server::server_options_given(app);
    return -1;
}

}  // namespace soa
