// Run options (see options.h).
#include "core/options.h"

#include <cstdlib>
#include <cstring>
#include <ctime>

namespace soa {

namespace {
RunOptions g_options;

const char* env(const char* name) {
    const char* e = getenv(name);
    return e && *e ? e : nullptr;
}
// "1"-style switches: set and not "0".
bool env_on(const char* name) {
    const char* e = env(name);
    return e && strcmp(e, "0") != 0;
}
void str(std::string& field, const char* name) {
    if (field.empty())
        if (const char* e = env(name)) field = e;
}
}  // namespace

const char* const kDefaultEventKeywords = "水着,夏,サマー,!福袋";

const RunOptions& options() { return g_options; }
RunOptions& mutable_options() { return g_options; }

int64_t parse_clock(const std::string& s) {
    struct tm tm = {};
    if (sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) >= 3) {
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        tm.tm_isdst = -1;
        return (int64_t)mktime(&tm);
    }
    // Unix seconds (what the campaign module once read SOA_CLOCK as).
    char* end = nullptr;
    long long v = strtoll(s.c_str(), &end, 10);
    return end && end != s.c_str() && *end == 0 && v > 0 ? (int64_t)v : 0;
}

bool set_clock(ServerOptions& o, const std::string& s) {
    int64_t t = parse_clock(s);
    if (!t) return false;
    o.has_clock = true;
    o.clock = t;
    o.clock_offset = t - (int64_t)time(nullptr);
    return true;
}

void options_from_env(RunOptions& r) {
    str(r.repo_dir, "SOA_REPO");

    ClientOptions& c = r.client;
    str(c.download_dir, "SOA_DOWNLOAD_DIR");
    if (!c.download_prefer) c.download_prefer = env_on("SOA_DOWNLOAD_PREFER");
    if (c.standin_dir.empty() && !c.standin_off)
        if (const char* e = env("SOA_STANDIN_ASSETS")) {
            std::string v = e;
            if (v == "0" || v == "off") c.standin_off = true;
            else c.standin_dir = v;
        }
    str(c.fake_server_dir, "SOA_FAKE_SERVER");
    str(c.fake_server_schema, "SOA_FAKE_SERVER_SCHEMA");
    if (!c.has_guest_cpus)
        if (const char* e = env("SOA_GUEST_CPUS")) {
            c.has_guest_cpus = true;
            c.guest_cpus = strcmp(e, "host") == 0 ? 0 : atoi(e);
        }
    if (!c.memstats)
        if (const char* e = env("SOA_MEMSTATS")) c.memstats = atoi(e);

    ServerOptions& o = r.server;
    if (!o.new_player) o.new_player = env_on("SOA_RESTORE_NEW_PLAYER");
    str(o.db, "SOA_SERVER_DB");
    str(o.game_xml, "SOA_SERVER_GAME_XML");
    str(o.master, "SOA_SERVER_MASTER");
    str(o.seed, "SOA_SERVER_SEED");
    if (!o.has_seed_rng)
        if (const char* e = env("SOA_SERVER_SEED_RNG")) {
            o.has_seed_rng = true;
            o.seed_rng = strtoull(e, nullptr, 0);
        }
    if (!o.has_start_coins)
        if (const char* e = env("SOA_START_COINS")) {
            o.has_start_coins = true;
            o.start_coins = (uint32_t)strtoul(e, nullptr, 0);
        }
    if (!o.has_clock)
        if (const char* e = env("SOA_CLOCK")) set_clock(o, e);
    if (!o.galaxy_pass) o.galaxy_pass = env_on("SOA_GALAXY_PASS");
    if (!o.enable_events) o.enable_events = env_on("SOA_ENABLE_EVENTS");
    str(o.event_keywords, "SOA_EVENT_KEYWORDS");
    if (!o.restore_tower) o.restore_tower = env_on("SOA_RESTORE_TOWER");
    str(o.campaign_master_db, "SOA_MASTER_DB");
    str(o.campaign_seed, "SOA_CAMPAIGN_SEED");
    str(o.fail, "SOA_SERVER_FAIL");
    str(o.log_packets, "SOA_LOG_PACKETS");
    if (!o.surprise) o.surprise = env("SOA_SERVER_SURPRISE") && atoi(env("SOA_SERVER_SURPRISE"));
}

}  // namespace soa
