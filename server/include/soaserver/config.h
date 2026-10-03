#pragma once
// The local server's configuration (library code). The server reads nothing else: the port (soa)
// fills it from its run options (soa::options(), port/src/native/api/server_adapters.cpp) before
// the game starts, soa-server from its own command line (server/app/main.cpp, the same option
// names). Tests change fields of config() directly and restore them.
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

namespace soa::server {

// The default --event-keywords: the summer (swimsuit) events and banners; see
// docs/server-rules.md "Enabling events by keyword" for what it matches.
extern const char* const kDefaultEventKeywords;

struct ServerConfig {
    // ---- the server -----------------------------------------------------------------------------
    bool enabled = false;          // the server answers (soa: --server inproc, the default)
    bool new_player = false;       // start without a player (SOA_RESTORE_NEW_PLAYER=1)
    std::string master;            // the 3.7.0 master DB (SOA_SERVER_MASTER; "" = data/basmaster-3.7.0.sqlite3 in the repo)
    std::string db;                // the state DB (SOA_SERVER_DB; "" = server.sqlite3 in the working directory)
    std::string seed;              // the save a new state is seeded from (SOA_SERVER_SEED)
    std::string game_xml;          // the client's Game.xml, the last seed fallback (SOA_SERVER_GAME_XML)
    std::string gacha_pools;  // --gacha-pools: the reconstructed gacha pools ("" = SOA_GACHA_POOLS, else data/gacha_pools.sqlite3 in the repo)
    bool has_seed_rng = false;  // a fixed RNG seed (SOA_SERVER_SEED_RNG), else the time
    uint64_t seed_rng = 0;
    // Free coins a new local player starts with (--start-coins; docs/server-rules.md "Seed").
    uint32_t start_coins = 300000;

    // ---- clock (--clock "YYYY-MM-DD HH:MM:SS"): the server clock starts there and runs on.
    // clock_offset = requested time - the real time when the option was read.
    bool has_clock = false;
    int64_t clock = 0;
    int64_t clock_offset = 0;

    // ---- modules --------------------------------------------------------------------------------
    bool galaxy_pass = false;  // --galaxy-pass (api/shop/subscription.cpp)
    bool enable_events = false;  // --enable-events (enable_events.h)
    std::string event_keywords;  // --event-keywords; "" = kDefaultEventKeywords
    bool restore_tower = false;  // --restore-tower (api/tower/tower.cpp)
    std::string campaign_master_db;  // SOA_MASTER_DB: the campaign module's master DB
    std::string campaign_seed;  // SOA_CAMPAIGN_SEED=<mission label>

    // ---- test hooks -----------------------------------------------------------------------------
    std::string fail;  // SOA_SERVER_FAIL="Method:code[,Method:code]"
    bool surprise = false;  // SOA_SERVER_SURPRISE=1: force surprise missions

    // ---- files ----------------------------------------------------------------------------------
    // The source checkouts repo files (master DBs, seed saves, port/server-data) are looked up in,
    // in order (find_repo_file); empty = relative to the working directory.
    std::vector<std::string> repo_roots;
    // The directory of the server's own side files (api/campaign/campaign.cpp: server_campaign.txt); the
    // port passes its data dir (the client's --data).
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
