#pragma once
// Run options (port code): what this run of soa was asked to do. main() fills them once, before
// the game starts, from the command line (settings are flags only: the SOA_* variables that were
// settings print a warning, common/include/soa/env.h; the port never setenv()s game or run state).
// Everything else reads them through options(). See port/README.md "Run options". The flags are
// defined in core/cli.cpp (soa's command line; the server's with soaserver/cli.h).
//
// Two groups, as in `soa --help`:
//   - ClientOptions: the 3.7.0 client and its emulated phone (asset sources, the device, the
//     in-process route's test switches, diagnostics);
//   - ServerOptions: the local server's rules and state, used only with --server inproc (with
//     --server HOST they belong to soa-server): server::ServerConfig itself, with soa-server's flags.
// The window, the data dir, --natives and the control/test flags stay in main().
#include <cstdint>
#include <string>

#include "soaserver/config.h"

namespace soa {

struct ClientOptions {
    // Assets the client loads besides the APK (the asset manager's fallbacks). With --server inproc
    // the in-process CDN serves the same two trees (config_from_options copies them, as soa-server's
    // --download-dir / --standin-assets).
    std::string download_dir;         // --download-dir
    bool download_prefer = false;     // --download-prefer: the download tree wins over the APK
    // Stand-in asset overlay (--standin-assets DIR; "off" or "0" = none):
    // made-up files for assets that no source has (e.g. lost gacha banners), searched after the
    // APK and the download dir. --server inproc defaults it to standin-assets.
    std::string standin_dir;
    bool standin_off = false;         // --standin-assets off

    // The FakeApiCaller route (native/api/fakeapi.cpp; on with --server inproc): a diagnostic dump.
    std::string fake_server_schema;   // --fake-server-schema FILE: dump the response schema there

    // ---- the emulated device ------------------------------------------------------------------
    // CPUs the guest sees (--guest-cpus N|host; 0 = the host's count): sysconf
    // (_SC_NPROCESSORS_*) and /sys/devices/system/cpu/{present,possible} (android_getCpuCount).
    // The engine sizes its worker pools from it (Aska::DynamicsWorker: N - 2 threads,
    // ResourceHandlerCreator: N), and every guest thread costs guest CPU contexts (core/cpu.cpp),
    // so a 32-core host would run 62 workers where the phones the game was made for ran 14.
    // Default 8, an octa-core phone (PLAN-next D7).
    int guest_cpus = 8;

    // ---- diagnostics ---------------------------------------------------------------------------
    // --memstats: a memory snapshot (native/common/memstats.cpp) at every phase change; --memstats S
    // (S > 1) also every S seconds. 0 = off.
    int memstats = 0;
};

// The local server's options: the server library's configuration itself (soaserver/config.h), one
// flag per field, defined once for soa and soa-server (soaserver/cli.h). enabled is --server inproc
// (the default; false with --server HOST). main() copies it into server::config() with the
// files the run found (native/api/server_adapters.cpp config_from_options).
using ServerOptions = server::ServerConfig;

struct RunOptions {
    // The source checkout the repo files (master DBs, seed saves, server/tests/fixtures, ...) are read
    // from (--repo DIR); empty = found from the executable (core/paths.h).
    std::string repo_dir;
    ClientOptions client;
    ServerOptions server;
};

// The default --event-keywords (docs/server-rules.md#enabling-events).
using server::kDefaultEventKeywords;

// The options of this run (read-only after main filled them).
const RunOptions& options();
// main() (and tests that need a different configuration) only.
RunOptions& mutable_options();

// --clock values: "YYYY-MM-DD[ HH:MM:SS]" (local time) or Unix seconds (the server library's).
using server::parse_clock;
using server::set_clock;

}  // namespace soa
