#pragma once
// The runtime programs' shared options (soa, soa-emu, soa-viewer): the window and the scripted
// driving (into app::HostConfig), the device's CPU count, the guest debugger and the log level.
// Header-only on CLI11 (common/include/soa/cli.h has the rules every program shares).
#include <cstdio>
#include <string>

#include <soa/cli.h>

#include "app/host.h"

namespace soa::app {

// What the shared options fill besides the HostConfig.
struct HostArgs {
    HostConfig* host = nullptr;
    // --headless / --windowed: -1 not given (the program's default), 1 headless, 0 windowed; the
    // last one given wins.
    int headless = -1;
    int guest_cpus = 8;   // --guest-cpus N|host (0 = host)
    std::string gdb;      // --gdb HOST:PORT
    int verbose = 0;      // -v count: 1 debug, 2 trace
};

// The data dir, library and checkout are per program (their defaults differ): --data DIR.
inline CLI::Option* add_data(CLI::App& app, std::string& to, const std::string& desc) {
    return app.add_option("--data", to, desc)->type_name("DIR");
}
// --lib PATH: the client library.
inline CLI::Option* add_lib(CLI::App& app, std::string& to, const std::string& desc) {
    return app.add_option("--lib", to, desc)->type_name("PATH");
}

// --guest-cpus N|host.
inline CLI::Option* add_guest_cpus(CLI::App& app, HostArgs& a) {
    return app
        .add_option_function<std::string>(
            "--guest-cpus", [&a](const std::string& v) { a.guest_cpus = cli::parse_guest_cpus(v); },
            "CPUs the game sees (sysconf, /sys/devices/system/cpu/present; an octa-core phone by default); the engine "
            "starts N - 2 dynamics and N resource workers")
        ->type_name("N|host")
        ->default_str("8");
}

// The window: --size, --landscape, --render-size, --fullscreen, --font, --headless, --windowed.
inline void add_window_options(CLI::App& app, HostArgs& a, const std::string& group = "Window") {
    HostConfig& h = *a.host;
    app.add_option_function<std::string>(
           "--size", [&h](const std::string& v) { sscanf(v.c_str(), "%dx%d", &h.width, &h.height); },
           "window size (default: portrait 9:16 at 90% of the desktop height)")
        ->type_name("WxH")
        ->group(group);
    app.add_flag("--landscape", h.landscape, "default to a 16:9 landscape window (the game is designed for portrait)")->group(group);
    app.add_option("--render-size", h.render_size,
                   "the window's surface: 'desktop' (the window's aspect ratio scaled to fill the desktop, so resizing "
                   "and fullscreen stay sharp), 'window' (the initial window size) or WxH")
        ->type_name("S")
        ->default_str("desktop")
        ->group(group);
    app.add_flag("--fullscreen", h.fullscreen, "start in (desktop) fullscreen")->group(group);
    app.add_option("--font", h.font, "the on-screen text box's font, a Japanese one (default: a system Japanese font; 'none': no text box)")
        ->type_name("PATH")
        ->group(group);
    cli::add_ordered_flag(app, "--headless", [&a] { a.headless = 1; },
                          "don't show the window; it still renders at the same size, so screenshots, --shot / --do and "
                          "--control work the same")
        ->group(group);
    cli::add_ordered_flag(app, "--windowed", [&a] { a.headless = 0; }, "show the window (the default; undoes an earlier --headless)")
        ->group(group);
}

// Scripted driving and the debugger: --shot, --do, --control, --gdb.
inline void add_driving_options(CLI::App& app, HostArgs& a, const std::string& group = "Driving and testing") {
    HostConfig& h = *a.host;
    cli::add_list(app, "--shot", h.shots, "save a screenshot S seconds after start (repeatable; F12 saves one any time)")
        ->type_name("S:PATH")
        ->group(group);
    cli::add_list(app, "--do", h.actions,
                  "scripted input S seconds after start (repeatable): tap:X:Y, drag:X1:Y1:X2:Y2, wheel:X:Y:DY (pinch), back, "
                  "text:STRING, shot:PATH, quit")
        ->type_name("S:ACTION")
        ->group(group);
    app.add_option("--control", h.control_path,
                   "read the same commands, one per line, from a named pipe (control/soactl.py; Windows: \\\\.\\pipe\\NAME); "
                   "tcp:HOST:PORT: from TCP connections")
        ->type_name("FIFO")
        ->group(group);
    app.add_option("--gdb", a.gdb,
                   "serve the GDB remote protocol for the guest (gdb-multiarch -x control/gdbinit-soa, control/gdbclient.py; "
                   "runtime/README.md \"Debugging the guest with gdb\")")
        ->type_name("HOST:PORT")
        ->group(group);
}

}  // namespace soa::app
