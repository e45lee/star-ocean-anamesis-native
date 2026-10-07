#pragma once
// soa-server's command line (cli.cpp): its own options (the network, the CDN, the tools) around
// the server options it shares with soa (soaserver/cli.h). main.cpp acts on the result.
#include <cstdint>
#include <string>
#include <vector>

#include "soaserver/config.h"

namespace soa::server::app {

struct ServerArgs {
    ServerConfig* config = nullptr;  // where the server options go (main: config())
    std::string repo, data, download_dir, filter;
    std::string listen = "127.0.0.1:44300", http = "127.0.0.1:44380", bridge_url;
    bool selftest = false, cdn_check = false, keep_open_after_error = false, list_apis = false, list_hooks = false;
    std::string replay_dir, replay_out;
    std::string english_dump;  // --english-dump DIR
    uint64_t shuffle = 0;
    std::vector<std::string> cdn_paths;
    int verbose = 0;  // -v
};

// Parses soa-server's command line (not --wire-tool, which main hands on first). -1: go on; else
// the exit status (0 after --help, 2 after an error, which it printed). `names`: every option name
// it defines (tests/cli).
int parse_args(int argc, const char* const* argv, ServerArgs& a, std::vector<std::string>* names = nullptr);

}  // namespace soa::server::app
