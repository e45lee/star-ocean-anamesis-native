#pragma once
// Run options (port code): what this run of soa was asked to do. main() fills them once, before
// the game starts, from the command line first and then from the SOA_* environment variables,
// which are fallback *inputs* only (session scripts set them; the port never setenv()s game or run
// state). Everything else reads them through options(). See port/README.md "Run options".
//
// Two groups, as in `soa --help`:
//   - ClientOptions: the 3.7.0 client and its emulated phone (asset sources, the device, the
//     in-process route's test switches, diagnostics);
//   - ServerOptions: the local server's rules and state, used only with --server inproc (with
//     --server HOST they belong to soa-server). They map 1:1 onto server::ServerConfig
//     (native/api/server_adapters.cpp config_from_options) and their flags are soa-server's.
// The window, the data dir, --natives and the control/test flags stay in main().
#include <cstdint>
#include <string>

namespace soa {

struct ClientOptions {
    // Assets the client loads besides the APK (the asset manager's fallbacks). With --server inproc
    // the in-process CDN serves the same two trees (config_from_options copies them, as soa-server's
    // --download-dir / --standin-assets).
    std::string download_dir;         // --download-dir / SOA_DOWNLOAD_DIR
    bool download_prefer = false;     // SOA_DOWNLOAD_PREFER=1: the download tree wins over the APK
    // Stand-in asset overlay (--standin-assets DIR / SOA_STANDIN_ASSETS; "off" or "0" = none):
    // made-up files for assets that no source has (e.g. lost gacha banners), searched after the
    // APK and the download dir. --server inproc defaults it to standin-assets.
    std::string standin_dir;
    bool standin_off = false;         // --standin-assets off / SOA_STANDIN_ASSETS=0

    // The FakeApiCaller route (native/api/fakeapi.cpp): canned responses dir; --server inproc
    // defaults it to port/fakeapi/responses.
    std::string fake_server_dir;      // SOA_FAKE_SERVER
    std::string fake_server_schema;   // SOA_FAKE_SERVER_SCHEMA: dump the response schema there

    // ---- the emulated device ------------------------------------------------------------------
    // CPUs the guest sees (--guest-cpus N|host / SOA_GUEST_CPUS; 0 = the host's count): sysconf
    // (_SC_NPROCESSORS_*) and /sys/devices/system/cpu/{present,possible} (android_getCpuCount).
    // The engine sizes its worker pools from it (Aska::DynamicsWorker: N - 2 threads,
    // ResourceHandlerCreator: N), and every guest thread costs guest CPU contexts (core/cpu.cpp),
    // so a 32-core host would run 62 workers where the phones the game was made for ran 14.
    // Default 8, an octa-core phone (PLAN-next D7).
    int guest_cpus = 8;
    bool has_guest_cpus = false;      // set by the command line

    // ---- diagnostics ---------------------------------------------------------------------------
    // SOA_MEMSTATS=1: a memory snapshot (native/common/memstats.cpp) at every phase change; =S (> 1)
    // also every S seconds.
    int memstats = 0;
};

// The local server's options, one field per server::ServerConfig field (soaserver/config.h) and
// one flag per soa-server flag (server/app/main.cpp).
struct ServerOptions {
    // --server inproc (the default): the local server answers in-process (ServerConfig::enabled).
    // False with --server HOST.
    bool enabled = false;
    bool new_player = false;          // --new-player / SOA_RESTORE_NEW_PLAYER=1: start without a player
    std::string master;               // --master / SOA_SERVER_MASTER: the 3.7.0 master DB
    std::string gacha_pools;          // --gacha-pools / SOA_GACHA_POOLS: the reconstructed gacha pools
    std::string db;                   // --db / SOA_SERVER_DB (inproc default <data>/server.sqlite3)
    std::string seed;                 // --seed / SOA_SERVER_SEED: the save a new state is seeded from
    std::string game_xml;             // --game-xml / SOA_SERVER_GAME_XML (inproc default <data>/.../Game.xml)
    bool has_seed_rng = false;        // --seed-rng / SOA_SERVER_SEED_RNG: fixed RNG seed (else the time)
    uint64_t seed_rng = 0;
    // Free coins (紋章石) a new local player starts with, seeded or created (--start-coins /
    // SOA_START_COINS; the user's choice, docs/server-rules.md "Seed").
    bool has_start_coins = false;
    uint32_t start_coins = 300000;

    // ---- clock (--clock / SOA_CLOCK "YYYY-MM-DD HH:MM:SS"): the server clock starts there and
    // runs on. clock_offset = requested time - the real time when the options were filled.
    bool has_clock = false;
    int64_t clock = 0;
    int64_t clock_offset = 0;

    // ---- modules --------------------------------------------------------------------------------
    // The Galaxy Pass as if bought and auto-renewed (--galaxy-pass / SOA_GALAXY_PASS=1; the pass
    // can't be bought in the port): +2 deep space ships etc. (server/src/api/shop/subscription.cpp).
    bool galaxy_pass = false;
    // Enabling events by keyword (--enable-events / SOA_ENABLE_EVENTS=1; server/src/api/events/enable_events.h):
    // besides the replayed calendar, every event area and gacha whose name matches event_keywords
    // (--event-keywords / SOA_EVENT_KEYWORDS, a comma list; "!word" excludes; empty = the default
    // kDefaultEventKeywords, the summer events) is open all year, assets permitting.
    bool enable_events = false;
    std::string event_keywords;
    // --restore-tower / SOA_RESTORE_TOWER=1: serve the tower's areas (server/src/api/tower/tower.cpp); in soa
    // the client's tower hooks (native/restore/restore_tower.cpp) open the menu. Off by default.
    bool restore_tower = false;
    std::string campaign_master_db;   // --campaign-master-db / SOA_MASTER_DB: the campaign module's master DB
    std::string campaign_seed;        // --campaign-seed / SOA_CAMPAIGN_SEED=<mission label>

    // ---- test hooks -----------------------------------------------------------------------------
    std::string fail;                 // --fail / SOA_SERVER_FAIL="Method:code[,Method:code]"
    bool surprise = false;            // --surprise / SOA_SERVER_SURPRISE=1: force surprise missions
    // --log-packets DIR / SOA_LOG_PACKETS: the in-process route's packet log, DIR/packets.log in
    // soa-server --log-packets' form (native/api/packet_log.h; tests/diff compares the two)
    std::string log_packets;
};

struct RunOptions {
    // The source checkout the repo files (master DBs, seed saves, port/server-data, ...) are read
    // from (--repo DIR / SOA_REPO); empty = found from the executable (core/paths.h).
    std::string repo_dir;
    ClientOptions client;
    ServerOptions server;
};

// The default --event-keywords: the summer (swimsuit) events and banners; see
// docs/server-rules.md "Enabling events by keyword" for what it matches.
extern const char* const kDefaultEventKeywords;

// The options of this run (read-only after main filled them).
const RunOptions& options();
// main() (and tests that need a different configuration) only.
RunOptions& mutable_options();

// Fills every field the command line left at its default from the SOA_* environment variables
// (fields the command line set are kept: the command line wins).
void options_from_env(RunOptions& o);

// "YYYY-MM-DD[ HH:MM:SS]" (local time), or a plain integer (Unix seconds). 0 when unparsable.
int64_t parse_clock(const std::string& s);
// Sets o.clock / clock_offset from a --clock / SOA_CLOCK value; false when unparsable.
bool set_clock(ServerOptions& o, const std::string& s);

}  // namespace soa
