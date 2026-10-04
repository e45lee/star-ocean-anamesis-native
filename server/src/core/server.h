#pragma once
// The server object and the core's internals its other files use (port code, not guest
// behaviour): files and the clock. The object's request lifecycle and dispatcher are defined in
// core/server.cpp (ARCHITECTURE.md); the tests' scratch servers are testing/scratch.h's. The
// state DB's schema and its meta helpers are the state module's (state/state.h, included here).
#include <sqlite3.h>

#include <initializer_list>
#include <map>
#include <mutex>
#include <random>
#include <string>
#include <vector>

#include "core/request_context.h"
#include "master/gacha_pools.h"
#include "soaserver/ext.h"
#include "state/state.h"  // meta, next_uid, has_player (the state module)

namespace soa::server {

bool file_exists(const std::string& p);
// The first of `c` that names an existing file, "" when none does.
std::string first_existing(std::initializer_list<std::string> c);

// ---- the server clock (core/clock.cpp; clock_now / set_server_clock are server.h's) --------
// --clock's offset from the real time (Server::init, from config()).
void set_clock_offset(int64_t offset);
// The replayed event calendar's reading of the master `m` (server.h event_now): the clock when one
// is set (--clock, tests), else today mapped onto the latest service year with an event term that
// day, (d).
EventTime event_clock_of(sqlite3* m);

// ---- the server object --------------------------------------------------------------------
// The long-lived server: the two DB handles, the gacha pools, the RNG, the requests waiting for
// their answer and the last answer's error codes. A request's own state is its RequestContext;
// every handler gets the same ext::Ctx (make_ctx).
struct Server {
    std::mutex mu;
    ext::Sql st, m;  // state, master (Sql::open; ScratchServer closes its own)
    gacha_pools::Pools pools;  // reconstructed gacha pools (data/gacha_pools.sqlite3)
    bool ok = false;
    std::mt19937_64 rng;
    std::map<u32, Request> pending;  // fid -> the last captured request
    std::map<u32, u32> errors;       // fid -> the code of its last answer (0 accepted)
    bool logged_in = false;          // FakeApiCaller::LoggedIn in-process: after a Login
    // The requests' RequestContext::live / test_log_value: false / the tests' value in the unit
    // tests' scratch servers.
    bool live = true;
    u64 test_log_value = 0;

    // Opens the master, the state DB (seeding a new one) and the gacha pools as config() says
    // (the live server).
    bool init();
    // Opens the state DB at this build's schema version (state::open_and_migrate: false for a file
    // newer than the build), seeds it when it has no player (one transaction), and reports its
    // references into the master (state::report_master_refs); the master must be open. `data_dir`:
    // the data dir whose side files a migration imports (the live server's config().data_root: the
    // campaign's server_campaign.txt, PLAN-schema S12); "" none (scratch servers).
    bool open_state(const std::string& path, u64 seed_rng, const std::string& seed_save, const std::string& data_dir = "");

    // A request's fresh state, and the context its handlers get.
    RequestContext new_request() const;
    ext::Ctx make_ctx(RequestContext& rc);

    // --fail "Method:code[,Method:code]" (a test option): refuse those requests.
    u32 forced_error(const std::string& method);

    // One transaction per request: a response and the state it reports are written together.
    bool handle(u32 fid, std::vector<u8>& out);
    // Refusals: a handler sets the request's refusal to the error code (master_text
    // error_message_text_<code>) and returns any body; handle_request then rolls the request back
    // and answers the player state only, and error_code(fid) reports the code to the FakeApiCaller hooks.
    bool handle_request(u32 fid, RequestContext& rc, std::vector<u8>& out);
    // The registered handler of the request's method (ext::find; src/core/modules.cpp registers the
    // core's APIs first, then the modules'). False: no handler, or an empty body (not handled).
    bool dispatch(ext::Ctx& ctx, u32 fid, std::vector<u8>& out);
};

}  // namespace soa::server
