// The local server's core (port code, not guest behaviour): the server object (core/server.h), one
// transaction per request, the refusal path and the dispatcher; the state's meta helpers; the
// public request API of soaserver/server.h (submit, handle, error_code, ...). The handlers are in
// src/api/<domain>/ (ARCHITECTURE.md). Every game rule carries its source label in a comment:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include "core/server.h"

#include <sqlite3.h>
#include <sys/stat.h>

#include <cstdlib>
#include <ctime>
#include <mutex>

#include "api/player/player_info.h"  // base_data: the refusal's answer
#include "core/errors.h"  // the refused commit
#include "core/log.h"
#include "core/request_context.h"
#include "core/response.h"  // ext::body
#include "soaserver/config.h"
#include "soaserver/master_source.h"
#include "soaserver/server.h"
#include "state/seed.h"  // seeding a new state

namespace soa::server {

using Row = ext::Row;
using Arg = ext::Arg;

bool file_exists(const std::string& p) {
    struct stat st;
    return stat(p.c_str(), &st) == 0;
}

// The master file apply_client_master(db, now, ev, master) lends the modules (ext::server_master_path).
const std::string* g_master_override = nullptr;

std::string first_existing(std::initializer_list<std::string> c) {
    for (auto& p : c)
        if (!p.empty() && file_exists(p)) return p;
    return "";
}

using ext::body;  // core/response.cpp

// ---- the server (core/server.h) -------------------------------------------------------------
bool Server::init() {
    if (config().has_clock) set_clock_offset(config().clock_offset);  // --clock
    // --master, the repo's data/basmaster-3.7.0.sqlite3, else derived from the game files (soaserver/master_source.h)
    std::string master = first_existing({master_source::resolve()});
    if (master.empty() || !m.open(master, true)) {
        LOGE("server", "the 3.7.0 master DB (--master, data/basmaster-3.7.0.sqlite3, or one derived from the 3.7.0 download) wasn't found");
        return false;
    }
    std::string path = !config().db.empty() ? config().db : "server.sqlite3";
    u64 seed_rng = config().has_seed_rng ? config().seed_rng : (u64)time(nullptr);
    bool fresh = !file_exists(path);
    if (!open_state(path, seed_rng, "", config().data_root)) return false;
    if (pools.open(config().gacha_pools)) LOGI("server", "gacha pools %s", pools.path().c_str());
    else LOGW("server", "gacha pools (data/gacha_pools.sqlite3) not found; drawing by rarity");
    LOGI("server", "local server state %s (master %s)%s", path.c_str(), master.c_str(), fresh ? ", seeded" : "");
    return true;
}

bool Server::open_state(const std::string& path, u64 seed_rng, const std::string& seed_save, const std::string& data_dir) {
    if (!st.open(path, false)) return false;
    // The schema (state/schema.cpp): every table, at this build's version; a newer file isn't
    // opened (and isn't touched: the journal mode below writes the file).
    if (!state::open_and_migrate(st.h, path, state::kSchemaVersion, m.h, data_dir)) {
        st.close();
        return false;
    }
    st.exec("pragma journal_mode = wal; pragma synchronous = normal;");
    rng.seed(seed_rng);
    // --new-player (the entry flow): start without a player, so
    // the client's Login gets "no account" and it runs the new-player flow (CreatePlayer).
    // (d) With no save to seed from (a packaged build ships none: docs/server-rules.md#seed), a new
    // state starts the same way: a fresh account through the client's own new-player flow, rather
    // than a finished-tutorial player with no characters.
    const bool no_seed = seed_source(seed_save).empty();
    if (no_seed && st.one("select count(*) from player", {}) == 0 && !new_player_mode())
        LOGI("server", "no seed save (--seed, data/saves/seed/Game.xml, or a --game-xml holding a player): starting a fresh account (the new-player flow)");
    if (st.one("select count(*) from player", {}) == 0 && !new_player_mode() && !no_seed) {
        RequestContext rc = new_request();
        ext::Ctx ctx = make_ctx(rc);
        // one transaction: a seed is all there or not at all (PLAN-schema S1)
        st.exec("begin immediate");
        seed(ctx, seed_save);
        // the deferred foreign keys (player.home_uid, party_id) are checked here
        if (!st.exec("commit")) {
            st.exec("rollback");
            LOGE("server", "state DB %s: the seed's transaction was refused (rolled back): not opened", path.c_str());
            st.close();
            return false;
        }
    }
    state::report_master_refs(st.h, m.h);
    return true;
}

RequestContext Server::new_request() const {
    RequestContext rc;
    rc.live = live;
    rc.test_log_value = test_log_value;
    return rc;
}

ext::Ctx Server::make_ctx(RequestContext& rc) {
    ext::Ctx c;
    c.st.h = st.h;
    c.m.h = m.h;
    c.rng = &rng;
    c.request = &rc;
    c.pools = &pools;
    return c;
}

u32 Server::forced_error(const std::string& method) {
    const std::string& s = config().fail;
    if (s.empty() || method.empty()) return 0;
    size_t p = 0;
    while (p < s.size()) {
        size_t q = s.find(',', p);
        std::string e = s.substr(p, q == std::string::npos ? std::string::npos : q - p);
        size_t c = e.find(':');
        if (c != std::string::npos && e.substr(0, c) == method) return (u32)strtoul(e.c_str() + c + 1, nullptr, 10);
        if (q == std::string::npos) break;
        p = q + 1;
    }
    return 0;
}

bool Server::handle(u32 fid, std::vector<u8>& out) {
    auto it = pending.find(fid);
    RequestContext rc = new_request();
    // the request's own battle log, if it carries one (hooks.h)
    if (it != pending.end()) rc.battle_log = it->second.battle_log;
    bool r = handle_request(fid, rc, out);
    if (rc.logged_in) logged_in = true;
    return r;
}

bool Server::handle_request(u32 fid, RequestContext& rc, std::vector<u8>& out) {
    ext::Ctx ctx = make_ctx(rc);
    st.exec("begin");
    auto it = pending.find(fid);
    const char* method = it != pending.end() ? it->second.method.c_str() : "?";
    u32 forced = it != pending.end() ? forced_error(it->second.method) : 0;
    bool ok = forced ? false : dispatch(ctx, fid, out);
    if (forced) rc.refusal = forced;
    if (!rc.refusal) {
        // Extension modules' additions to every answered response (ext::OnResponse), in the
        // request's transaction.
        if (ok && ext::has_response_hooks() && it != pending.end()) {
            Value v = mp_decode(out);
            if (Value* d = v.type == Value::Map ? v.find_mut("data") : nullptr; d && d->type == Value::Map) {
                if (ext::on_response(ctx, it->second, *d)) out = mp_encode(v);
            }
        }
        if (!ok) {
            st.exec("rollback");
            errors[fid] = 0;
            return false;
        }
        if (st.exec("commit")) {
            errors[fid] = 0;
            return true;
        }
        // (d) A commit the state DB refuses (a deferred foreign key violated by the request,
        // PLAN-schema 5 "Risks"; logged by Sql::exec): nothing of the request is kept, and it is
        // refused as the generic 10208.
        LOGE("server", "fid %08x (%s): the state DB refused the commit", fid, method);
        rc.refusal = (u32)ErrorCode::kItemUnusable;
    }
    st.exec("rollback");
    errors[fid] = rc.refusal;
    LOGW("server", "fid %08x (%s): refused with error %u", fid, method, rc.refusal);
    st.exec("begin");
    out = body(base_data(ctx));
    st.exec("commit");
    return true;
}

bool Server::dispatch(ext::Ctx& ctx, u32 fid, std::vector<u8>& out) {
    auto it = pending.find(fid);
    Request r;
    if (it != pending.end()) r = it->second;
    const ext::Handler* h = ext::find(r.method);
    if (!h) return false;
    std::vector<u8> b = (*h)(ctx, r);
    if (b.empty()) return false;
    out = std::move(b);
    return true;
}

namespace {

Server* g_server = nullptr;  // the live server (soa's in-process route, soa-server)

Server* server() {
    if (!g_server) {
        g_server = new Server();
        g_server->ok = g_server->init();
    }
    return g_server->ok ? g_server : nullptr;
}

}  // namespace

bool enabled() { return config().enabled; }  // soa: --server inproc, the default

EventTime event_now() {
    Server* s = g_server && g_server->ok ? g_server : nullptr;
    return s ? event_clock_of(s->m.h) : clock_as_calendar(clock_now());
}
std::string ext::server_master_path() {
    if (g_master_override) return *g_master_override;
    Server* s = g_server && g_server->ok ? g_server : nullptr;
    const char* f = s && s->m.h ? sqlite3_db_filename(s->m.h, "main") : nullptr;
    return f ? f : "";
}
bool ext::with_live_server(const std::function<void(ext::Ctx&)>& fn) {
    if (!enabled()) return false;
    Server* s = server();
    if (!s) return false;
    std::lock_guard<std::mutex> l(s->mu);
    s->st.exec("begin");
    RequestContext rc = s->new_request();
    ext::Ctx c = s->make_ctx(rc);
    fn(c);
    s->st.exec("commit");
    return true;
}

// A request arrived (soa: port/src/native/api/server_adapters.cpp captures FakeApiCaller's
// arguments from the guest registers): it becomes the pending request of its fid.
void submit(const Request& in) {
    if (!enabled()) return;
    Request r = in;
    u32 fid = r.fid;
    std::string args;
    for (u64 v : r.ints) args += " " + std::to_string(v);
    for (auto& s : r.strs) args += " \"" + s + "\"";
    LOGI("server", "request %s (fid %08x):%s", r.method.c_str(), fid, args.c_str());
    if (Server* s = server()) {
        std::lock_guard<std::mutex> l(s->mu);
        s->pending[fid] = std::move(r);
    }
}

// (a)-level data override: the master DB the online server delivered is data. The 3.7.0 DB's
// master_global has service_stop_day = 2021/06/24 14:30:00; 3.7.0 reads it only for its
// service-end check (CTitle::Setup, CPhase_Server::CPhase_Server; docs/client-changes.md
// "Emulator mode"), so the master the server serves has no such row, as in service. (The client
// before the rebase also froze its clock at the row: docs/history/notes-3.8.0.md "Clock frozen at
// the end of service".) Both server modes serve apply_client_master's master from the CDN.
void apply_client_master(sqlite3* db, ServerTime t, EventTime ev, const std::string& server_master) {
    if (sqlite3_table_column_metadata(db, "main", "master_global", "key", nullptr, nullptr, nullptr, nullptr, nullptr) != SQLITE_OK) return;
    char* err = nullptr;
    int r = sqlite3_exec(db, "delete from main.master_global where key = 'service_stop_day'", nullptr, nullptr, &err);
    LOGI("server", "master: dropped master_global.service_stop_day (%s)", r == SQLITE_OK ? "ok" : err ? err : "?");
    sqlite3_free(err);
    const std::string* saved = g_master_override;
    g_master_override = &server_master;
    ext::client_master(db, t, ev);
    g_master_override = saved;
}

bool new_player_mode() { return config().new_player; }
bool logged_in() {
    if (!enabled()) return true;
    Server* s = server();
    if (!s) return true;
    std::lock_guard<std::mutex> l(s->mu);
    return s->logged_in;
}
u32 error_code(u32 fid) {
    if (!enabled() || !g_server || !g_server->ok) return 0;
    std::lock_guard<std::mutex> l(g_server->mu);
    auto it = g_server->errors.find(fid);
    return it == g_server->errors.end() ? 0 : it->second;
}

bool handle(u32 fid, std::vector<u8>& out) {
    if (!enabled()) return false;
    Server* s = server();
    if (!s) return false;
    std::lock_guard<std::mutex> l(s->mu);
    return s->handle(fid, out);
}
bool handle(u32 fid, const std::string&, std::vector<u8>& out) { return handle(fid, out); }

}  // namespace soa::server
