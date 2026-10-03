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

#include "api/favor/favor.h"         // favor::schema
#include "api/player/player_info.h"  // base_data: the refusal's answer
#include "core/log.h"
#include "core/request_context.h"
#include "core/response.h"  // ext::body
#include "soaserver/config.h"
#include "soaserver/server.h"
#include "state/seed.h"  // seeding a new state

namespace soa::server {

// ---- SQLite helpers ------------------------------------------------------------------------
// The handlers use ext::Sql (ext.h) on the request's ext::Ctx; the server object's Db is
// core/server.h's.
using Row = ext::Row;
using Arg = ext::Arg;

int64_t one_null_as_zero(ext::Sql& db, const std::string& sql, std::initializer_list<Arg> args, int64_t dflt) {
    int64_t v = dflt;
    db.q(sql, args, [&](const Row& r) { v = r.v.begin()->second ? sqlite3_value_int64(r.v.begin()->second) : dflt; });
    return v;
}

bool Db::open(const std::string& path, bool ro) {
    int fl = ro ? SQLITE_OPEN_READONLY : (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    if (sqlite3_open_v2(path.c_str(), &h, fl, nullptr) != SQLITE_OK) {
        LOGE("server", "can't open %s: %s", path.c_str(), h ? sqlite3_errmsg(h) : "?");
        if (h) sqlite3_close(h);
        h = nullptr;
        return false;
    }
    return true;
}

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

// ---- the state's meta table (core/server.h; PLAN-schema S1 moves these to state/) ----------
using ext::body;  // core/response.cpp

u64 next_uid(ext::Ctx& ctx, const char* key) {
    u64 v = (u64)std::stoull(meta(ctx, key, "0"));
    ctx.st.q("insert or replace into meta values (?, ?)", {key, std::to_string(v + 1)});
    return v;
}
std::string meta(ext::Ctx& ctx, const char* key, const char* dflt) {
    std::string v = dflt;
    ctx.st.q("select value from meta where key = ?", {key}, [&](const Row& r) { v = r.s("value"); });
    return v;
}

void set_meta(ext::Ctx& ctx, const char* key, const std::string& v) { ctx.st.q("insert or replace into meta values (?, ?)", {key, v}); }
bool has_player(ext::Ctx& ctx) { return ctx.st.one("select count(*) from player", {}) > 0; }

// ---- the server (core/server.h) -------------------------------------------------------------
bool Server::init() {
    if (config().has_clock) set_clock_offset(config().clock_offset);  // --clock / SOA_CLOCK
    std::string master = first_existing({config().master, find_repo_file("data/basmaster-3.7.0.sqlite3")});
    if (master.empty() || !m.open(master, true)) {
        LOGE("server", "the 3.7.0 master DB (data/basmaster-3.7.0.sqlite3, or SOA_SERVER_MASTER) wasn't found");
        return false;
    }
    std::string path = !config().db.empty() ? config().db : "server.sqlite3";
    u64 seed_rng = config().has_seed_rng ? config().seed_rng : (u64)time(nullptr);
    bool fresh = !file_exists(path);
    if (!open_state(path, seed_rng, "")) return false;
    if (pools.open()) LOGI("server", "gacha pools %s", pools.path().c_str());
    else LOGW("server", "gacha pools (port/server-data/gacha_pools.sqlite3) not found; drawing by rarity");
    LOGI("server", "local server state %s (master %s)%s", path.c_str(), master.c_str(), fresh ? ", seeded" : "");
    return true;
}

bool Server::open_state(const std::string& path, u64 seed_rng, const std::string& seed_save) {
    bool fresh = !file_exists(path);
    if (!st.open(path, false)) return false;
    st.exec("pragma journal_mode = wal; pragma synchronous = normal;");
    schema();
    rng.seed(seed_rng);
    // SOA_RESTORE_NEW_PLAYER=1 (entry flow, agent restore-title): start without a player, so
    // the client's Login gets "no account" and it runs the new-player flow (CreatePlayer).
    if ((fresh || st.one("select count(*) from player", {}) == 0) && !new_player_mode()) {
        RequestContext rc = new_request();
        ext::Ctx ctx = make_ctx(rc);
        seed(ctx, seed_save);
    }
    return true;
}

void Server::schema() {
    st.exec(R"(
create table if not exists meta (key text primary key, value text);
create table if not exists player (id integer primary key, search_id text, name text, level integer, exp integer,
  fol integer, stamina integer, stamina_at integer, free_coin integer, pay_coin integer, home_uid integer,
  party_id integer, created_at integer, last_login_at integer);
create table if not exists roster (uid integer primary key, role_id integer, level integer, exp integer,
  limit_break integer default 0, awaken integer default 0, skill1 integer default 1, skill2 integer default 1,
  skill3 integer default 1, weapon_uid integer default 0, accessory_uid integer default 0, favor integer default 0,
  created_at integer);
create table if not exists items (uid integer primary key, master_item_id integer, item_type integer,
  level integer default 1, exp integer default 0, limit_break integer default 0, locked integer default 0, created_at integer);
create table if not exists stock (master_item_id integer primary key, item_type integer, count integer);
create table if not exists gear (uid integer primary key, master_gear_id integer, data text);
create table if not exists party (party_id integer, slot integer, uid integer, primary key (party_id, slot));
create table if not exists mission (mission_id integer primary key, cleared integer default 0, best_rank integer default 0,
  play_count integer default 0, clear_count integer default 0, first_clear_at integer);
create table if not exists play (id integer primary key check (id = 1), mission_id integer, party_id integer,
  started_at integer, stamina_cost integer, uids text);
create table if not exists gacha_history (id integer primary key autoincrement, gacha_id integer, at integer,
  role_id integer, uid integer, rank text, duplicate integer, cost_free integer, cost_pay integer);
create table if not exists box_gacha (gacha_id integer primary key, box_index integer, reset_count integer, drawn text);
create table if not exists presents (id integer primary key autoincrement, content_type integer, content_id integer,
  num integer, reason_type integer, reason_param integer, created_at integer, received_at integer);
create table if not exists login_bonus (id integer primary key, day integer, last_at integer);
create table if not exists achievements (id integer primary key, progress integer, received_at integer);
create table if not exists planets (label text primary key, open integer);
create table if not exists assist (uid integer primary key, assist_uid integer);
create table if not exists view_flags (kind integer primary key, flags integer);
create table if not exists party_set (party_id integer primary key, icon_id integer default 0, is_lock integer default 0);
create table if not exists party_member (party_id integer, slot integer, weapon_uid integer, accessory_uid integer,
  skill1 integer, skill2 integer, skill3 integer, assist_uid integer, primary key (party_id, slot));
create table if not exists play_ext (id integer primary key check (id = 1), mission_type integer, surprise integer,
  helper_uid integer, helper_kind integer, npc_id integer, campaign_lots integer);
create table if not exists unlocks (mission_id integer primary key, mission_type integer, by_mission integer, at integer);
create table if not exists stepup (head integer primary key, try_count integer, restart_count integer, next_id integer);
create table if not exists box_state (gacha_id integer primary key, total_count integer default 0, reset_count integer default 0);
create table if not exists box_slots (gacha_id integer, slot_id integer, drawn integer, primary key (gacha_id, slot_id));
)");
    favor::schema(st.h);
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
    u32 forced = it != pending.end() ? forced_error(it->second.method) : 0;
    bool ok = forced ? false : dispatch(ctx, fid, out);
    if (forced) rc.refusal = forced;
    if (rc.refusal) {
        st.exec("rollback");
        errors[fid] = rc.refusal;
        LOGW("server", "fid %08x (%s): refused with error %u", fid, it != pending.end() ? it->second.method.c_str() : "?", rc.refusal);
        st.exec("begin");
        out = body(base_data(ctx));
        st.exec("commit");
        return true;
    }
    errors[fid] = 0;
    // Extension modules' additions to every answered response (ext::OnResponse), in the
    // request's transaction.
    if (ok && ext::has_response_hooks() && it != pending.end()) {
        Value v = mp_decode(out);
        if (Value* d = v.type == Value::Map ? v.find_mut("data") : nullptr; d && d->type == Value::Map) {
            if (ext::on_response(ctx, it->second, *d)) out = mp_encode(v);
        }
    }
    st.exec(ok ? "commit" : "rollback");
    return ok;
}

bool Server::dispatch(ext::Ctx& ctx, u32 fid, std::vector<u8>& out) {
    auto it = pending.find(fid);
    Request r;
    if (it != pending.end()) r = it->second;
    const ext::Handler* h = ext::find(r.method);
    if (!h) return false;
    if (!ext::is_core_api(r.method)) ext::ensure_schema(ctx.st);  // the modules' tables (add_core_api)
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

int64_t event_now() {
    Server* s = g_server && g_server->ok ? g_server : nullptr;
    return s ? event_clock_of(s->m.h) : clock_now();
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
    ext::ensure_schema(c.st);
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
void apply_client_master(sqlite3* db, int64_t t, int64_t ev, const std::string& server_master) {
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
