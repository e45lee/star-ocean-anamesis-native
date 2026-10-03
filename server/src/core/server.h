#pragma once
// The server object and the core's internals its other files use (port code, not guest
// behaviour): files, the state's meta table and the core's reading of one(). The object's request
// lifecycle and dispatcher are defined in core/server.cpp (ARCHITECTURE.md); the tests' scratch
// servers are testing/scratch.h's. The meta helpers move to state/ with PLAN-schema S1.
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

namespace soa::server {

bool file_exists(const std::string& p);
// The first of `c` that names an existing file, "" when none does.
std::string first_existing(std::initializer_list<std::string> c);

// ---- the state's meta table (key -> text; PLAN-schema S1 moves these to state/) ------------
std::string meta(ext::Ctx& ctx, const char* key, const char* dflt);
void set_meta(ext::Ctx& ctx, const char* key, const std::string& v);
// The meta counter `key`'s value, counted up (uids of new characters and items).
u64 next_uid(ext::Ctx& ctx, const char* key);
bool has_player(ext::Ctx& ctx);

// The core's former Db::one on any handle: `dflt` when there is no row, but a NULL value reads
// as 0 (ext::Sql::one reads a NULL as `dflt`). Kept at the five core sites whose default isn't 0
// (server/PLAN-readability.md 1.5; PLAN-schema S1 and the domain steps R11 / R15 decide each).
int64_t one_null_as_zero(ext::Sql& db, const std::string& sql, std::initializer_list<ext::Arg> args, int64_t dflt);

// ---- the server clock (core/clock.cpp; clock_now / set_server_clock are server.h's) --------
// --clock's offset from the real time (Server::init, from config()).
void set_clock_offset(int64_t offset);
// The replayed event calendar's reading of the master `m` (server.h event_now): the clock when one
// is set (--clock, tests), else today mapped onto the latest service year with an event term that
// day, (d).
int64_t event_clock_of(sqlite3* m);

// ---- the server object --------------------------------------------------------------------
// The core opens its two databases as Db, which keeps the core's former reading of one(): a NULL
// value reads as 0 (ext::Sql::one reads it as the default). The handlers use ext::Sql on their
// ext::Ctx.
class Db : public ext::Sql {
public:
    // Opens the DB at `path` (read-only: `ro`); false (logged) when it can't.
    bool open(const std::string& path, bool ro);
    int64_t one(const std::string& sql, std::initializer_list<ext::Arg> args, int64_t dflt = 0) { return one_null_as_zero(*this, sql, args, dflt); }
};

// The long-lived server: the two DB handles, the gacha pools, the RNG, the requests waiting for
// their answer and the last answer's error codes. A request's own state is its RequestContext;
// every handler gets the same ext::Ctx (make_ctx).
struct Server {
    std::mutex mu;
    Db st, m;  // state, master
    gacha_pools::Pools pools;  // reconstructed gacha pools (port/server-data/gacha_pools.sqlite3)
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
    // Opens (creating and seeding when new) the state DB; the master must be open.
    bool open_state(const std::string& path, u64 seed_rng, const std::string& seed_save);
    // The core's state tables (create table if not exists; PLAN-schema S1 moves them to state/).
    void schema();

    // A request's fresh state, and the context its handlers get.
    RequestContext new_request() const;
    ext::Ctx make_ctx(RequestContext& rc);

    // SOA_SERVER_FAIL="Method:code[,Method:code]" (port test option): refuse those requests.
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
