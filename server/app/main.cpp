// soa-server: the local game server on its own (server/README.md). It serves the unmodified 3.7.0
// client over the game's own wire protocol (server/net/: TCP framing, the Ninja cipher, the request
// decoder, the bridge, the HTTP server) and runs the library's and the wire layer's unit tests
// (--selftest) with no game loaded.
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <atomic>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include <soa/env.h>
#include <soa/sock.h>
#include <soa/game_files.h>
#include <soa/install.h>

#include "net/cdn_http.h"
#include "net/game.h"
#include "net/http.h"
#include "net/loop.h"
#include "net/tool.h"
#include "cli.h"
#include "replay.h"
#include "soaserver/cdn.h"
#include <soa/file_tree.h>
#include "soaserver/config.h"
#include "soaserver/master_source.h"
#include "soaserver/ext.h"
#include "soaserver/hooks.h"
#include "soaserver/log.h"
#include "soaserver/testing.h"

namespace {

using soa::server::ServerConfig;

bool is_repo(const std::string& d) {
    struct stat st;
    return stat((d + "/server/CMakeLists.txt").c_str(), &st) == 0 || stat((d + "/port/CMakeLists.txt").c_str(), &st) == 0;
}
// The repo roots, as soa finds them (common soa/install.h repo_roots: --repo; in a development
// build also a checkout upwards from the executable or the working directory, and a worktree's
// main checkout; then the install dirs). A packaged soa-server's data files (data/gacha_pools.sqlite3,
// data/saves/seed/Game.xml, standin-assets/) sit at their repo paths beside it.
soa::install::RepoRoots repo_roots(const std::string& given) {
    soa::install::RepoRoots r = soa::install::repo_roots(given, is_repo);
    if (!r.warning.empty()) fprintf(stderr, "soa-server: %s\n", r.warning.c_str());
    return r;
}

// The client's own server name (docs/online-server.md section 2), as URLs without a port.
constexpr const char* kClientHostUrl = "https://production-game.so-ana.com";
constexpr const char* kClientCdnUrl = "http://production-game.so-ana.com";

bool g_verbose = false;
std::atomic<bool> g_stop{false};
void on_signal(int) { g_stop = true; }
bool log_enabled(soa::server::LogLevel l) { return l >= (g_verbose ? soa::server::LogLevel::Debug : soa::server::LogLevel::Info); }

}  // namespace

int main(int argc, char** argv) {
    soa::env::warn_removed_env("soa-server", soa::env::kServer);  // SOA_* settings that are flags now
    if (argc >= 2 && !strcmp(argv[1], "--wire-tool")) return soa::server::net::wire_tool(argc - 2, argv + 2);
    // The command line (cli.cpp: soa-server's options around the server options it shares with soa,
    // soaserver/cli.h).
    ServerConfig& c = soa::server::config();
    soa::server::app::ServerArgs args;
    args.config = &c;
    if (int rc = soa::server::app::parse_args(argc, argv, args); rc >= 0) return rc;
    g_verbose = args.verbose > 0;
    const std::string &repo = args.repo, &data = args.data, &filter = args.filter, &listen = args.listen, &http = args.http,
                      &bridge_url = args.bridge_url, &log_packets = c.log_packets, &replay_dir = args.replay_dir, &replay_out = args.replay_out;
    std::string download_dir = args.download_dir;
    const bool selftest = args.selftest, cdn_check = args.cdn_check, keep_open_after_error = args.keep_open_after_error, list_apis = args.list_apis,
               list_hooks = args.list_hooks;
    const uint64_t shuffle = args.shuffle;
    const std::vector<std::string>& cdn_paths = args.cdn_paths;
    soa::server::set_log_sink(nullptr, log_enabled);
    const soa::install::RepoRoots roots = repo_roots(repo);
    c.repo_roots = roots.all;
    if (!data.empty()) {
        c.data_root = data;
        if (c.db.empty()) c.db = data + "/server.sqlite3";
    }
    const bool serving = !selftest && !list_apis && !list_hooks && replay_dir.empty();
    if (serving) fprintf(stderr, "soa-server: %s\n", roots.describe().c_str());
    if (serving && download_dir.empty()) {
        // A packaged soa-server (README.md "Packaging"): the download beside the program or in its
        // game/ folder (soa/install.h). A checkout's build dir has none, so there nothing changes.
        std::vector<std::string> notes;
        std::string d = soa::install::find_download(soa::install::install_dirs(), &notes);
        for (auto& n : notes) fprintf(stderr, "soa-server: %s\n", n.c_str());
        if (!d.empty()) {
            download_dir = c.download_dir = d;
            fprintf(stderr, "soa-server: the 3.7.0 download %s (found beside the program)\n", d.c_str());
        }
    }
    // The master: --master, the checkout's, else derived from the game files (soaserver/master_source.h).
    if (serving && soa::server::master_source::resolve().empty()) {
        fprintf(stderr, "soa-server: no 3.7.0 master DB (see above)\n");
        return 1;
    }
    // The asset index the content gates use: what the CDN serves, the download dir and the
    // stand-ins unless --standin-assets off (as soa's AssetManager with --standin-assets).
    if (!download_dir.empty()) soa::server::set_asset_index(soa::server::cdn::asset_index_from_config());
    // A module registering a method or content type twice (server/src/core/modules.cpp) is a startup error.
    auto reg_errors = soa::server::ext::registration_errors();
    for (auto& e : reg_errors) fprintf(stderr, "soa-server: module registry: %s\n", e.c_str());
    if (!reg_errors.empty()) return 1;
    if (list_apis) return soa::server::app::list_apis();
    if (list_hooks) return soa::server::app::list_hooks();
    if (!replay_dir.empty()) {
        if (replay_out.empty()) {
            fprintf(stderr, "soa-server: --replay needs --out OUT\n");
            return 2;
        }
        return soa::server::app::replay(replay_dir, replay_out, g_verbose);
    }
    if (selftest) {
        // The unit tests use their own scratch servers; the live server stays off.
        fprintf(stderr, "soa-server: repo %s\n", c.repo_roots.empty() ? "(not found)" : c.repo_roots[0].c_str());
        auto [ran, failed] = soa::server::testing::run_tests(filter, 1, true, shuffle);
        return failed ? 1 : 0;
    }
    if (!args.english_dump.empty()) {
        // The English tables of --english without the network (docs/server-rules.md#english-derive)
        c.english = true;
        auto o = soa::server::cdn::options_from_config();
        std::string err;
        auto tree = soa::FileTree::open(o.mirror, &err);
        soa::server::cdn::EnglishTables t;
        if (!tree || !soa::server::cdn::english_tables(o, *tree, t, &err)) {
            fprintf(stderr, "soa-server: --english-dump: %s\n", err.c_str());
            return 1;
        }
        return soa::server::cdn::write_english_tables(t, args.english_dump) ? 0 : 1;
    }
    if (cdn_check) {
        // The CDN content without the network (server/README.md "CDN"): what the HTTP server serves.
        auto tree = soa::server::cdn::build_from_config();
        if (!tree) return 1;
        printf("%s\n", tree->summary().c_str());
        for (auto& p : cdn_paths) {
            soa::server::cdn::Response r;
            std::vector<uint8_t> b;
            bool ok = tree->lookup(p, r) && r.read(b);
            printf("%s\t%d\t%zu\t%s\t%s\n", p.c_str(), r.status, b.size(), ok ? soa::server::cdn::sha1_hex(b.data(), b.size()).c_str() : "-",
                   r.content_type.c_str());
        }
        return 0;
    }
    namespace net = soa::server::net;
    std::string game_host, http_host;
    uint16_t game_port = 0, http_port = 0;
    if (!net::parse_host_port(listen, &game_host, &game_port) || !net::parse_host_port(http, &http_host, &http_port)) {
        fprintf(stderr, "soa-server: --listen / --http take HOST:PORT\n");
        return 2;
    }
    c.enabled = true;
    auto backend = net::live_backend();
    net::GameOptions go;
    // The defaults name the client's host without a port (server/README.md "soa-server"): (b) the
    // 3.7.0 URI parser keeps a ":port" in the host name it resolves, so a ported URL fails on the client.
    go.bridge_url = bridge_url.empty() ? std::string(kClientHostUrl) + "/bridge" : bridge_url;
    go.log_dir = log_packets;
    go.close_after_refusal = !keep_open_after_error;
    net::GameServer game(*backend, go);
    net::HttpRouter router;
    router.route("/bridge", game.bridge_handler());
    // The CDN (soaserver/cdn.h): the re-encrypted master, the rebuilt bundles, version.bin and the
    // manifests under <AssetPath>/<r_ver>/Android/; Login points the client at it.
    std::shared_ptr<soa::server::cdn::Tree> cdn;
    if (!download_dir.empty()) {
        if (c.cdn_url.empty()) c.cdn_url = kClientCdnUrl;
        cdn = soa::server::cdn::build_from_config();
        if (cdn) net::mount_cdn(router, cdn);
        else {
            c.cdn_url.clear();
            fprintf(stderr, "soa-server: no CDN content; serving %s as is under /Android/\n", download_dir.c_str());
            router.route("/Android/", net::static_files(download_dir));
        }
    }
    net::Loop loop(game, router);
    std::string err;
    if (!loop.listen_game(game_host, game_port, &err) || !loop.listen_http(http_host, http_port, &err)) {
        fprintf(stderr, "soa-server: %s\n", err.c_str());
        return 1;
    }
    signal(SIGINT, on_signal);
    signal(SIGTERM, on_signal);
    signal(SIGPIPE, SIG_IGN);
    fprintf(stderr, "soa-server: game %s, http %s (bridge %s)%s%s\n", soa::sock::join_host_port(game_host, loop.game_port()).c_str(),
            soa::sock::join_host_port(http_host, loop.http_port()).c_str(), go.bridge_url.c_str(), log_packets.empty() ? "" : ", packets logged to ",
            log_packets.c_str());
    if (cdn)
        fprintf(stderr, "soa-server: CDN %s/download/%s/Android/<name> (%s)\n", c.cdn_url.c_str(), cdn->revision().c_str(), cdn->summary().c_str());
    loop.run(g_stop);
    fprintf(stderr, "soa-server: stopped\n");
    return 0;
}
