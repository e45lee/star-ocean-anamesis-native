#pragma once
// soa-emu's command line (cli.cpp): the runtime programs' shared options (runtime/src/app/cli.h),
// the 3.7.0 phone's (platform370/cli.h) and its own. main.cpp acts on the result.
#include <string>
#include <vector>

#include "app/host.h"
#include "platform370/platform370.h"

namespace soa::emu {

// The default device clock: the host's real time. The client's own service-end check
// (master_global.service_stop_day, 2021/06/24 14:30:00) is patched out (platform370's
// patch_370.cpp), so no fake date is needed; --device-clock sets one for tests.
inline constexpr const char* kDefaultDeviceClock = "host";

struct EmuArgs {
    std::string lib_path, data_dir, download_dir, repo;
    bool download_prefer = false;
    std::vector<std::string> apks;  // --apk, repeatable (later wins)
    platform370::Config p370;       // everything on (soa-emu is the 3.7.0 phone, network included)
    app::HostConfig host;
    int guest_cpus = 8;
    std::string gdb;
    int verbose = 0;
};

// -1: go on; else the exit status (0 after --help, 2 after an error, which it printed). `names`:
// every option name it defines (tests/cli).
int parse_args(int argc, const char* const* argv, EmuArgs& a, std::vector<std::string>* names = nullptr);

}  // namespace soa::emu
