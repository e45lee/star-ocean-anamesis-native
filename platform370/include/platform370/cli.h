#pragma once
// The 3.7.0 phone's options (soa and soa-emu): the device clock, the native patch and the network
// redirect, into platform370::Config. Header-only on CLI11 (common/include/soa/cli.h).
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>

#include <soa/cli.h>

#include "platform370/platform370.h"

namespace soa::platform370 {

// "HOST[:PORT]": the host and the port (0 when none). A value with more than one ':' is all host
// (no port). false when the host is empty or a port is given and isn't positive.
inline bool split_host_port(const std::string& v, std::string* host, int* port) {
    *host = v;
    *port = 0;
    size_t c = v.rfind(':');
    if (c != std::string::npos && v.find(':') == c) *host = v.substr(0, c), *port = atoi(v.c_str() + c + 1);
    return !host->empty() && (c == std::string::npos || *port > 0);
}

// --server HOST[:PORT] (soa-emu; soa's --server takes "inproc" too): the game server.
inline void set_server(NetConfig& n, const std::string& v) {
    std::string host;
    int port = 0;
    if (!split_host_port(v, &host, &port)) cli::bad_value("--server", "expected HOST[:PORT], got \"" + v + "\"");
    n.server_host = host;
    if (port) n.server_port = port;
}

// --device-clock, --no-patch.
inline void add_device_options(CLI::App& app, Config& cfg, const std::string& group) {
    app.add_option("--device-clock", cfg.device_clock,
                   "the phone's clock (local time) at start; it runs on from there (default host: the host's real time; the "
                   "client's service-end check is patched out, so any date works)")
        ->type_name("\"YYYY-MM-DD HH:MM:SS\"|host")
        ->group(group);
    app.add_flag_callback("--no-patch", [&cfg] { cfg.patch = false; },
                          "run the client without its native patch (platform370/src/patch_370.cpp): its service-end check is "
                          "live, so on a date after 2021/06/24 14:30 the title shows the service-end notice")
        ->group(group);
}

// --http, --lobby, --map-host: where the client's connections go (with soa-server).
inline void add_network_options(CLI::App& app, Config& cfg, const std::string& group) {
    NetConfig& n = cfg.netcfg;
    auto host_port = [&app, &n, &group](const char* name, std::string NetConfig::*host, int NetConfig::*port, const char* desc) {
        app.add_option_function<std::string>(
               name,
               [&n, name, host, port](const std::string& v) {
                   std::string h;
                   int p = 0;
                   if (!split_host_port(v, &h, &p) || p <= 0) cli::bad_value(name, "expected HOST:PORT, got \"" + v + "\"");
                   n.*host = h, n.*port = p;
               },
               desc)
            ->type_name("HOST:PORT")
            ->group(group);
    };
    host_port("--http", &NetConfig::http_host, &NetConfig::http_port,
              "soa-server's --http (default <server host>:44380): http(s):// URLs to a mapped host are fetched there as "
              "plain HTTP");
    host_port("--lobby", &NetConfig::lobby_host, &NetConfig::lobby_port,
              "where the client's lobby connections (port 4001) go (default: not redirected)");
    app.add_option_function<std::vector<std::string>>(
           "--map-host",
           [&n](const std::vector<std::string>& all) {
               for (const std::string& v : all) {
                   size_t eq = v.find('=');
                   std::string name = v.substr(0, eq);
                   for (auto& ch : name) ch = (char)tolower((unsigned char)ch);
                   n.hosts[name] = eq == std::string::npos ? "" : v.substr(eq + 1);
               }
           },
           "also resolve NAME to ADDR (default the server host); repeatable")
        ->type_name("NAME[=ADDR]")
        ->allow_extra_args(false)
        ->multi_option_policy(CLI::MultiOptionPolicy::TakeAll)
        ->group(group);
}

}  // namespace soa::platform370
