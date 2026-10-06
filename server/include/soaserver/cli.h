#pragma once
// The local server's options, one flag per ServerConfig field (soaserver/config.h): soa (with
// --server inproc) and soa-server take the same ones, defined here once. Header-only on CLI11
// (common/include/soa/cli.h). The programs add their own around them: the files' defaults
// (--db) and soa-server's network and CDN flags.
#include <cstdint>
#include <ctime>
#include <string>
#include <vector>

#include <soa/cli.h>

#include "soaserver/config.h"

namespace soa::server {

// The group the server options are listed under in --help (soa: whether one was given, for its
// --server HOST warning).
inline const char* const kServerOptionsGroup = "Server (the local server's rules and state)";

// Adds the server options, filling `c`. `db_default` describes the program's default for --db in
// the help.
inline void add_server_options(CLI::App& app, ServerConfig& c, const std::string& db_default, const std::string& group = kServerOptionsGroup) {
    auto file = [&](const char* name, std::string& to, const std::string& desc) { app.add_option(name, to, desc)->type_name("FILE")->group(group); };
    file("--db", c.db, "the state DB (default " + db_default + ")");
    file("--master", c.master,
         "the 3.7.0 master DB (default data/basmaster-3.7.0.sqlite3 in the checkout, else decrypted once from the download's "
         "sqlite/basmaster.sqlite3 into DATA/master/; server/README.md \"The master DB\")");
    file("--gacha-pools", c.gacha_pools, "the reconstructed gacha pools (default data/gacha_pools.sqlite3)");
    file("--seed", c.seed, "the save a new state is seeded from, e.g. a 3.7.0 or offline Game.xml; an existing state DB keeps its player");
    app.add_option_function<std::string>(
           "--seed-rng",
           [&c](const std::string& v) {
               uint64_t n = 0;
               if (!cli::parse_u64(v, 0, &n)) cli::bad_value("--seed-rng", "expected a number, got \"" + v + "\"");
               c.has_seed_rng = true, c.seed_rng = n;
           },
           "fixed RNG seed (default the time)")
        ->type_name("N")
        ->group(group);
    app.add_flag("--new-player", c.new_player, "start without a player: the new-player tutorial")->group(group);
    app.add_option_function<std::string>(
           "--clock",
           [&c](const std::string& v) {
               int64_t t = cli::parse_clock(v);
               if (!t) cli::bad_value("--clock", "expected \"YYYY-MM-DD HH:MM:SS\", got \"" + v + "\"");
               c.has_clock = true, c.clock = t, c.clock_offset = t - (int64_t)time(nullptr);
           },
           "the server's clock starts at that time and runs on; without it, event terms replay the calendar "
           "(server::event_now)")
        ->type_name("\"YYYY-MM-DD HH:MM:SS\"")
        ->group(group);
    app.add_option_function<std::string>(
           "--start-coins",
           [&c](const std::string& v) {
               uint64_t n = 0;  // (not strtoul: a 32-bit long on Windows)
               if (!cli::parse_u64(v, 10, &n) || v[0] == '-' || n > 0xffffffffULL)
                   cli::bad_value("--start-coins", "expected a number, got \"" + v + "\"");
               c.start_coins = (uint32_t)n;
           },
           "free coins a new local player starts with; an existing state DB keeps its balance")
        ->type_name("N")
        ->default_str("300000")
        ->group(group);
    app.add_flag("--galaxy-pass", c.galaxy_pass, "the local player has the Galaxy Pass, renewed when it runs out (+2 deep space ships)")
        ->group(group);
    app.add_flag("--enable-events", c.enable_events,
                 "also open, all year, every event area and gacha banner whose name matches --event-keywords, assets permitting")
        ->group(group);
    app.add_option("--event-keywords", c.event_keywords,
                   std::string("names to match, a comma list (\"!\" excludes); default: the summer events \"") + kDefaultEventKeywords + "\"")
        ->type_name("\"a,b,!c\"")
        ->group(group);
    app.add_flag("--restore-tower", c.restore_tower,
                 "open the tower mode, which 3.7.0 had closed: the server serves it (and soa's tower hooks open the menu)")
        ->group(group);
    app.add_flag("--home3d-all", c.home3d_all,
                 "debug: the client's master copy offers the 3D home for every character, also the ones 3.7.0 shows in 2D "
                 "only (master_person.home3d_disable; docs/home3d.md)")
        ->group(group);
    file("--campaign-master-db", c.campaign_master_db, "the campaign module's master DB (test hook)");
    app.add_option("--campaign-seed", c.campaign_seed, "seed the campaign progress up to a mission (test hook)")->type_name("LABEL")->group(group);
    app.add_option("--fail", c.fail, "force error replies (test hook)")->type_name("M:CODE[,..]")->group(group);
    app.add_flag("--surprise", c.surprise, "force surprise missions (test hook)")->group(group);
    app.add_option("--log-packets", c.log_packets,
                   "log every request and reply (DIR/packets.log, the reply bodies and battle logs as DIR/<n>-<name>.*; "
                   "soa's in-process route and soa-server write the same form, tests/diff compares them)")
        ->type_name("DIR")
        ->group(group);
}

// The server options given on the command line (their long names), for soa's --server HOST warning.
inline std::vector<std::string> server_options_given(const CLI::App& app, const std::string& group = kServerOptionsGroup) {
    std::vector<std::string> out;
    for (const CLI::Option* o : app.get_options())
        if (o->get_group() == group && o->count() > 0 && !o->get_lnames().empty() && o->get_lnames()[0] != "server")
            out.push_back("--" + o->get_lnames()[0]);
    return out;
}

}  // namespace soa::server
