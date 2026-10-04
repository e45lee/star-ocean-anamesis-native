#pragma once
// The local server's configuration (library code): every setting the server has. The port (soa)
// fills it from its command line (soa::options(), port/src/native/api/server_adapters.cpp) before
// the game starts, soa-server from its own (server/app/cli.cpp); both define the flags with
// soaserver/cli.h, one flag per field. The library reads
// no setting from the environment; its one environment variable is a self-test dump
// (SOA_NOTICE_HTML_DUMP, docs/environment.md). Tests change fields of config() directly and
// restore them.
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

namespace soa::server {

// The default --event-keywords: the summer (swimsuit) events and banners; see
// docs/server-rules.md#enabling-events for what it matches.
inline constexpr const char* kDefaultEventKeywords = "水着,夏,サマー,!福袋";

struct ServerConfig {
    // ---- the server -----------------------------------------------------------------------------
    bool enabled = false;          // the server answers (soa: --server inproc, the default)
    bool new_player = false;       // --new-player: start without a player
    std::string master;            // --master: the 3.7.0 master DB ("" = soaserver/master_source.h's rule, which sets it)
    std::string apk;               // the 3.7.0 APK (soa's --apk, soa-server's --apk): the master's last-resort source
    std::string db;                // --db: the state DB ("" = server.sqlite3 in the working directory)
    std::string seed;              // --seed: the save a new state is seeded from
    std::string game_xml;          // --game-xml: the client's Game.xml, the last seed fallback
    std::string gacha_pools;       // --gacha-pools: the reconstructed gacha pools ("" = data/gacha_pools.sqlite3 in the repo)
    bool has_seed_rng = false;     // --seed-rng: a fixed RNG seed, else the time
    uint64_t seed_rng = 0;
    // Free coins a new local player starts with (--start-coins; docs/server-rules.md#seed).
    uint32_t start_coins = 300000;

    // ---- clock (--clock "YYYY-MM-DD HH:MM:SS"): the server clock starts there and runs on.
    // clock_offset = requested time - the real time when the option was read.
    bool has_clock = false;
    int64_t clock = 0;
    int64_t clock_offset = 0;

    // ---- modules --------------------------------------------------------------------------------
    bool galaxy_pass = false;      // --galaxy-pass (api/shop/subscription.cpp)
    bool enable_events = false;    // --enable-events (enable_events.h)
    std::string event_keywords;    // --event-keywords; "" = kDefaultEventKeywords
    bool restore_tower = false;    // --restore-tower (api/tower/tower.cpp)
    bool home3d_all = false;       // --home3d-all: the 3D home for every character (api/player/home.cpp; debug)
    std::string campaign_master_db;  // --campaign-master-db: the campaign module's master DB
    std::string campaign_seed;       // --campaign-seed <mission label>

    // ---- test hooks -----------------------------------------------------------------------------
    std::string fail;              // --fail "Method:code[,Method:code]"
    bool surprise = false;         // --surprise: force surprise missions
    // --log-packets DIR: every request and reply logged there (soa-server's wire layer, net/game.h;
    // soa's in-process route, port/src/native/api/packet_log.h; tests/diff compares the two)
    std::string log_packets;

    // ---- files ----------------------------------------------------------------------------------
    // The source checkouts repo files (master DBs, seed saves, server/tests/fixtures) are looked up in,
    // in order (find_repo_file); empty = relative to the working directory.
    std::vector<std::string> repo_roots;
    // The server's data dir (the CDN's scratch files; a server_campaign.txt there from before the
    // state DB's version 11 is imported by its step, PLAN-schema S12); the port passes its data dir
    // (the client's --data).
    std::string data_root;

    // ---- CDN (soa-server only; soaserver/cdn.h) ----------------------------------------------
    // The HTTP base the client downloads from, "http://HOST:PORT" (soa-server --cdn-url). When set,
    // Login / SimpleLogin answer AssetPath = cdn_url + "/download", MasterPath = cdn_url + "/master"
    // and r_ver = cdn_revision (docs/online-server.md section 6); empty (soa) = not sent.
    std::string cdn_url;
    std::string cdn_revision;  // the served version.bin's revision (cdn::Tree::build sets it)
    std::string download_dir;  // the 3.7.0 download tree served (--download-dir)
    bool cdn_standins = true;  // serve the stand-in assets too (--standin-assets DIR|off)
    std::string standin_dir;  // "" = the repo's standin-assets
    std::string cdn_scratch;  // where the served master and the bundle-hash cache go ("" = data_root, else /tmp)
};

// The configuration in force (mutable: the embedder fills it, tests change it).
ServerConfig& config();

// The first existing path among `rels` (repo-relative), searched in every config().repo_roots
// root in order of the candidates (all roots for the first candidate, then the next); with no
// roots, relative to the working directory. "" when none exists.
std::string find_repo_file(std::initializer_list<const char*> rels);
std::string find_repo_file(const std::string& rel);

// "YYYY-MM-DD[ HH:MM:SS]" (local time), or a plain integer (Unix seconds). 0 when unparsable.
int64_t parse_clock(const std::string& s);
// Sets c.clock / clock_offset from a --clock value; false when unparsable.
bool set_clock(ServerConfig& c, const std::string& s);

}  // namespace soa::server
