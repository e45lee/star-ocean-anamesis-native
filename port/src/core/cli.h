#pragma once
// soa's command line (cli.cpp): the client options (the runtime programs' shared ones,
// runtime/include/soaruntime/app/cli.h; the 3.7.0 phone's, platform370/cli.h; soa's own) and the server options
// (soaserver/cli.h, soa-server's). Run options go into RunOptions (core/options.h); main() acts on
// the rest.
#include <string>
#include <vector>

#include "soaruntime/app/host.h"
#include "core/options.h"
#include "platform370/platform370.h"

namespace soa {

struct SoaArgs {
    RunOptions* opt = nullptr;  // where the run options go (main: mutable_options())
    std::string data_dir;       // "" = the default (soa/paths.h)
    std::string apk_path, lib_path;
    bool smoke = false, selftest = false, list_native = false;
    std::string test_filter;          // --selftest F
    std::string natives = "all";      // --natives all|route|none (--no-native = none); main checks the word
    std::vector<std::string> natives_skip;  // --natives-skip SUBSYS[,SUBSYS..] (main checks the names)
    std::string server_mode;          // --server inproc|HOST[:PORT] ("" = not given: inproc)
    platform370::Config p370;         // the 3.7.0 platform layer (net/http only with --server HOST)
    app::HostConfig host;
    int headless = -1;                // --headless 1 / --windowed 0; -1: headless only for --selftest
    std::string gdb;                  // --gdb HOST:PORT
    int verbose = 0;                  // -v / -vv
    std::vector<std::string> live_checks;   // --live-check SPEC, each (main parses them)
    std::vector<std::string> server_flags;  // the server options given (--server HOST warns about them)
    bool apk_dir_given = false;       // --apk-dir (ignored, with a warning)
};

// -1: go on; else the exit status (0 after --help, 2 after an error, which it printed). `names`:
// every option name it defines (tests/cli).
int parse_soa_args(int argc, const char* const* argv, SoaArgs& a, std::vector<std::string>* names = nullptr);

}  // namespace soa
