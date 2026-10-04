#pragma once
// soa-viewer's command line (cli.cpp): the runtime programs' shared options (runtime/src/app/cli.h)
// and its own. main.cpp acts on the result.
#include <string>
#include <vector>

#include "app/host.h"

namespace soa::viewer {

inline constexpr const char* kBaseApk = "com.square_enix.android_googleplay.StarOceanj.apk";

struct ViewerArgs {
    std::string apk_dir, xapk_path, lib_path, data_dir, repo, download_dir;
    std::vector<std::string> extra_apks;  // --apk, repeatable (later wins)
    bool download_prefer = false;
    app::HostConfig host;
    int guest_cpus = 8;
    std::string gdb;
    int verbose = 0;
};

// -1: go on; else the exit status (0 after --help, 2 after an error, which it printed). `names`:
// every option name it defines (tests/cli).
int parse_args(int argc, const char* const* argv, ViewerArgs& a, std::vector<std::string>* names = nullptr);

}  // namespace soa::viewer
