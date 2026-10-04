// soa-server's command line on CLI11 (cli.h; the shared rules: common/include/soa/cli.h).
#include "cli.h"

#include <soa/cli.h>

#include "soaserver/cli.h"

namespace soa::server::app {

int parse_args(int argc, const char* const* argv, ServerArgs& a, std::vector<std::string>* names) {
    CLI::App app{
        "The local game server: serves the unmodified 3.7.0 client over the game's own wire protocol "
        "(server/README.md). Also: soa-server --wire-tool CMD ... (server/tests/ninja/tools; --wire-tool help).",
        "soa-server"};
    cli::setup_app(app);
    ServerConfig& c = *a.config;
    const std::string serve = "Serving", tools = "Tests and tools", files = "Game files";
    app.add_option("--listen", a.listen, "the game server's TCP port (the client's is 443)")
        ->type_name("HOST:PORT")
        ->default_str("127.0.0.1:44300")
        ->group(serve);
    app.add_option("--http", a.http, "the HTTP server: /bridge and the CDN")->type_name("HOST:PORT")->default_str("127.0.0.1:44380")->group(serve);
    app.add_option("--bridge-url", a.bridge_url, "the bridge URL sent in ResultStart")
        ->type_name("URL")
        ->default_str("https://production-game.so-ana.com/bridge")
        ->group(serve);
    app.add_option("--cdn-url", c.cdn_url, "the CDN base Login sends (AssetPath = URL/download, MasterPath, r_ver)")
        ->type_name("URL")
        ->default_str("http://production-game.so-ana.com")
        ->group(serve);
    app.add_option("--cdn-scratch", c.cdn_scratch, "where the served master and the bundle-hash cache go (default DATA/cdn)")
        ->type_name("DIR")
        ->group(serve);
    app.add_flag("--keep-open-after-error", a.keep_open_after_error)->group("");  // hidden: a test switch (net/game.h)

    cli::add_repo(app, a.repo)->group(files);
    app.add_option("--data", a.data, "the server's data dir (state DB default DIR/server.sqlite3, side files)")->type_name("DIR")->group(files);
    app.add_option("--apk", c.apk,
                   "the 3.7.0 APK: its built-in (older) master is the last resort without a download (default: apk/ in the "
                   "checkout, else beside the program)")
        ->type_name("FILE")
        ->group(files);
    cli::add_download(app, a.download_dir,
                      "the 3.7.0 download: a folder (work/download-3.7.0) or SOA-3.7.0-canonical-data.zip, read in place; content "
                      "is gated on it (as soa --download) and the CDN serves it (server/README.md \"CDN\"); default: none, except "
                      "a packaged soa-server's: a download folder or zip beside the program or in its game/ folder (README.txt)")
        ->group(files);
    bool standins_off = false;
    cli::add_standin_assets(app, c.standin_dir, standins_off,
                            "stand-in assets the CDN adds and content is gated on (default standin-assets; off / 0 = none)")
        ->group(files);

    server::add_server_options(app, c, "DATA/server.sqlite3, without --data ./server.sqlite3", "");

    app.add_option("--selftest", a.filter,
                   "run the server library's and the wire layer's unit tests (no game needed); FILTER is a substring, \"a|b\" "
                   "matches either; exit status 1 when one fails")
        ->type_name("[FILTER]")
        ->expected(0, 1)
        ->group(tools);
    app.add_option_function<std::string>(
           "--shuffle", [&a](const std::string& v) { a.shuffle = strtoull(v.c_str(), nullptr, 0); },
           "with --selftest: run the tests in an order shuffled with seed N")
        ->type_name("N")
        ->group(tools);
    app.add_option("--replay", a.replay_dir,
                   "replay the recorded requests DIR/requests.txt with the server options given (the corpus's DIR/options) "
                   "into --out OUT: replies, error codes, end state, log (server/tests/replay/README.md; "
                   "tools/server_replay_diff.sh)")
        ->type_name("DIR")
        ->group(tools);
    app.add_option("--out", a.replay_out, "with --replay: the output dir")->type_name("OUT")->group(tools);
    app.add_flag("--list-apis", a.list_apis, "every method and what answers it (core, a module file, - none)")->group(tools);
    app.add_flag("--list-hooks", a.list_hooks, "every module hook in its run order (kind, module, file:line, detail)")->group(tools);
    app.add_option("--cdn-check", a.cdn_paths, "build the CDN content, print it and the answers for PATHs (URL paths), exit")
        ->type_name("[PATH..]")
        ->expected(0, -1)
        ->group(tools);
    cli::add_verbose(app, a.verbose, "debug log")->group(tools);

    app.footer(
        "The default URLs name the client's own host, without a port: the 3.7.0 client's URI parser can't resolve "
        "\"host:port\". The client must map production-game.so-ana.com to this machine and send those URLs to --http as "
        "plain HTTP (soa-emu does: --server / --http). A client that takes ported URLs can use --bridge-url "
        "http://<--http>/bridge --cdn-url http://<--http> instead.\n"
        "Settings are flags only; the environment variables that were settings print a warning (docs/environment.md).");
    cli::note_removed_env(app, env::kServer);

    if (names) *names = cli::option_names(app);
    int rc = cli::parse(app, argc, argv);
    if (rc >= 0) return rc;
    a.selftest = app.count("--selftest") > 0;
    a.cdn_check = app.count("--cdn-check") > 0;
    std::erase(a.cdn_paths, std::string());  // (a bare --cdn-check)
    c.download_dir = a.download_dir;
    if (standins_off) c.cdn_standins = false;
    return -1;
}

}  // namespace soa::server::app
