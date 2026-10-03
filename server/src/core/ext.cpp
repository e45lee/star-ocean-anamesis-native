// The local server's extension registry and SQLite helpers (see ext.h). Port code, not guest
// behaviour.
#include "soaserver/ext.h"

#include <algorithm>
#include <cstdlib>
#include <set>

#include "core/modules.h"
#include "core/log.h"
#include "master/master.h"
#include "core/wallet.h"

namespace soa::server::ext {

int64_t Row::i(const char* k) const {
    auto it = v.find(k);
    return it == v.end() || !it->second ? 0 : sqlite3_value_int64(it->second);
}
double Row::f(const char* k) const {
    auto it = v.find(k);
    return it == v.end() || !it->second ? 0 : sqlite3_value_double(it->second);
}
std::string Row::s(const char* k) const {
    auto it = v.find(k);
    if (it == v.end() || !it->second) return "";
    const unsigned char* t = sqlite3_value_text(it->second);
    return t ? (const char*)t : "";
}
bool Row::null(const char* k) const {
    auto it = v.find(k);
    return it == v.end() || !it->second || sqlite3_value_type(it->second) == SQLITE_NULL;
}

void Sql::exec(const std::string& sql) {
    char* err = nullptr;
    if (sqlite3_exec(h, sql.c_str(), nullptr, nullptr, &err) != SQLITE_OK) {
        LOGE("server", "sql error: %s in %s", err ? err : "?", sql.c_str());
        sqlite3_free(err);
    }
}
int Sql::q(const std::string& sql, std::initializer_list<Arg> args, const std::function<void(const Row&)>& fn) {
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(h, sql.c_str(), -1, &st, nullptr) != SQLITE_OK) {
        LOGE("server", "sql prepare: %s in %s", sqlite3_errmsg(h), sql.c_str());
        return 0;
    }
    int k = 1;
    for (const Arg& a : args) {
        if (a.t == Arg::I) sqlite3_bind_int64(st, k, a.i);
        else if (a.t == Arg::F) sqlite3_bind_double(st, k, a.d);
        else if (a.t == Arg::S) sqlite3_bind_text(st, k, a.s.c_str(), -1, SQLITE_TRANSIENT);
        else sqlite3_bind_null(st, k);
        k++;
    }
    int n = 0, rc;
    while ((rc = sqlite3_step(st)) == SQLITE_ROW) {
        n++;
        if (fn) {
            Row r;
            for (int c = 0; c < sqlite3_column_count(st); c++) r.v[sqlite3_column_name(st, c)] = sqlite3_column_value(st, c);
            fn(r);
        }
    }
    if (rc != SQLITE_DONE) LOGE("server", "sql step: %s in %s", sqlite3_errmsg(h), sql.c_str());
    sqlite3_finalize(st);
    return n;
}
int64_t Sql::one(const std::string& sql, std::initializer_list<Arg> args, int64_t dflt) {
    int64_t v = dflt;
    q(sql, args, [&](const Row& r) {
        auto it = r.v.begin();
        v = it != r.v.end() && it->second && sqlite3_value_type(it->second) != SQLITE_NULL ? sqlite3_value_int64(it->second) : dflt;
    });
    return v;
}

namespace {
std::map<std::string, Handler>& apis() {
    static std::map<std::string, Handler> m;
    return m;
}
std::vector<std::function<void(Ctx&, const Request&, Value&)>>& loads() {
    static std::vector<std::function<void(Ctx&, const Request&, Value&)>> v;
    return v;
}
std::vector<std::function<bool(Ctx&, const Request&, Value&)>>& responses() {
    static std::vector<std::function<bool(Ctx&, const Request&, Value&)>> v;
    return v;
}
std::vector<std::function<void(Sql&, int64_t, int64_t)>>& client_masters() {
    static std::vector<std::function<void(Sql&, int64_t, int64_t)>> v;
    return v;
}
std::vector<const char*>& schemas() {
    static std::vector<const char*> v;
    return v;
}
std::map<u32, GrantFn>& grants() {
    static std::map<u32, GrantFn> m;
    return m;
}
std::vector<ItemExtraFn>& item_extras() {
    static std::vector<ItemExtraFn> v;
    return v;
}
}  // namespace

// ---- the registry's order record and its errors (modules.cpp register_all) ----------------
namespace {
const char* g_module = nullptr;  // the module register_all is running
std::vector<HookInfo>& hook_log() {
    static std::vector<HookInfo> v;
    return v;
}
std::vector<std::string>& errors() {
    static std::vector<std::string> v;
    return v;
}
std::string short_path(const char* file) {
    std::string f = file ? file : "";
    size_t p = f.rfind("/server/");
    return p == std::string::npos ? f : f.substr(p + 1);
}
void registration_error(const std::string& what, const char* file, int line) {
    std::string e = what + " (" + short_path(file) + ":" + std::to_string(line) + ")";
    LOGE("server", "module registry: %s", e.c_str());
    errors().push_back(e);
}
}  // namespace

void set_registering_module(const char* name) { g_module = name; }
void record_hook(const char* kind, const char* file, int line, std::string detail) {
    hook_log().push_back({kind, g_module ? g_module : "?", short_path(file), std::move(detail), line});
}
std::vector<HookInfo> hook_order() {
    modules::register_all();
    return hook_log();
}
std::vector<std::string> registration_errors() {
    modules::register_all();
    return errors();
}

void add_grant(u32 content_type, GrantFn fn, const char* file, int line) {
    if (grants().count(content_type)) {
        registration_error("content type " + std::to_string(content_type) + " granted twice", file, line);
        return;
    }
    grants()[content_type] = std::move(fn);
    record_hook("Grant", file, line, "content type " + std::to_string(content_type));
}
void add_item_extra(ItemExtraFn fn, const char* file, int line) {
    item_extras().push_back(std::move(fn));
    record_hook("ItemExtra", file, line);
}
const GrantFn* find_grant(u32 content_type) {
    modules::register_all();
    auto it = grants().find(content_type);
    return it == grants().end() ? nullptr : &it->second;
}
void item_extra(Sql& st, Sql& m, u64 uid, Value& item) {
    modules::register_all();
    for (auto& f : item_extras()) f(st, m, uid, item);
}

namespace {
std::vector<std::function<void(Ctx&, const MissionInfo&, Value&, Value&)>>& start_extras() {
    static std::vector<std::function<void(Ctx&, const MissionInfo&, Value&, Value&)>> v;
    return v;
}
std::vector<std::function<void(Ctx&, const MissionInfo&, Value&)>>& result_extras() {
    static std::vector<std::function<void(Ctx&, const MissionInfo&, Value&)>> v;
    return v;
}
}  // namespace
void add_mission_start_extra(MissionStartFn fn, const char* file, int line) {
    start_extras().push_back(std::move(fn));
    record_hook("MissionStartExtra", file, line);
}
void add_mission_result_extra(MissionResultFn fn, const char* file, int line) {
    result_extras().push_back(std::move(fn));
    record_hook("MissionResultExtra", file, line);
}
void mission_start_extra(Ctx& c, const MissionInfo& mi, Value& param, Value& data) {
    ensure_schema(c.st);
    for (auto& f : start_extras()) f(c, mi, param, data);
}
void mission_result_extra(Ctx& c, const MissionInfo& mi, Value& data) {
    ensure_schema(c.st);
    for (auto& f : result_extras()) f(c, mi, data);
}
void add_drop(Ctx& c, Value& d, u32 type, u32 id, u32 num, u32 drop_type) {
    if (!num) return;
    Value items = Value::array(), stocks = Value::array(), chars = Value::array();
    c.grant(type, id, num, items, stocks, chars);
    // (b) the result screen lists DropList entries by their first property, the content id, with
    // content_type and drop_type (api/missions/mission_end.cpp); the owned uids go in AddItem /
    // AddCharacter.
    Value& dl = d["DropList"];
    if (dl.type != Value::Map) {
        dl = Value::object();
        dl["fol"] = 0u;
        dl["free_coin"] = 0u;
        dl["up_fol_rate"] = 0u;
    }
    auto list = [&](const char* k) -> Value& {
        Value& v = dl[k];
        if (v.type != Value::Arr) v = Value::array();
        return v;
    };
    for (Value e : items.arr) {
        e["drop_type"] = drop_type;
        Value& add = d["AddItem"];
        if (add.type != Value::Arr) add = Value::array();
        add.push(e);
        e["id"] = e.get_u("master_item_id");
        list("item").push(e);
    }
    for (Value e : chars.arr) {
        e["drop_type"] = drop_type;
        Value& add = d["AddCharacter"];
        if (add.type != Value::Map) add = Value::object();
        add[std::to_string(e.get_u("id"))] = e;
        e["id"] = e.get_u("master_role_id");
        e["content_type"] = 2u;
        list("character").push(e);
    }
    for (Value e : stocks.arr) {
        e["drop_type"] = drop_type;
        list("stock_item").push(e);
    }
    if (type == 3) dl["fol"] = (u32)dl.get_u("fol") + num;
    if (type == 4) dl["free_coin"] = (u32)dl.get_u("free_coin") + num;
    if (!stocks.arr.empty()) d["StockItem"] = c.stock();
    Value base = c.base_data();  // FOL / coins / Player as they are now
    for (auto& [k, v] : base.map) d[k] = v;
}

static std::map<std::string, std::string>& api_files() {
    static std::map<std::string, std::string> f;
    return f;
}
void add_api(std::initializer_list<const char*> methods, Handler h, const char* file, int line) {
    for (const char* m : methods) {
        if (apis().count(m)) {
            registration_error(std::string("method ") + m + " registered twice (first by " + short_path(api_files()[m].c_str()) + ")", file, line);
            continue;
        }
        apis()[m] = h, api_files()[m] = file;
    }
}
namespace {
std::set<std::string>& core_apis() {
    static std::set<std::string> s;
    return s;
}
}  // namespace
void add_core_api(std::initializer_list<const char*> methods, Handler h, const char* file, int line) {
    add_api(methods, h, file, line);
    for (const char* m : methods) core_apis().insert(m);
}
bool is_core_api(const std::string& method) {
    modules::register_all();
    return core_apis().count(method) > 0;
}
std::map<std::string, std::string> api_sources() {
    modules::register_all();
    return api_files();
}
void add_player_load(PlayerLoadFn fn, const char* file, int line) {
    loads().push_back(std::move(fn));
    record_hook("OnPlayerLoad", file, line);
}
void add_schema(const char* sql, const char* file, int line) {
    schemas().push_back(sql);
    // the detail: the first table it creates
    std::string s = sql, t;
    size_t p = s.find("exists ");
    if (p != std::string::npos) {
        p += 7;
        size_t e = s.find_first_of(" (", p);
        t = s.substr(p, e == std::string::npos ? std::string::npos : e - p);
    }
    record_hook("Schema", file, line, t);
}
void add_response_hook(ResponseFn fn, const char* file, int line) {
    responses().push_back(std::move(fn));
    record_hook("OnResponse", file, line);
}
bool has_response_hooks() {
    modules::register_all();
    return !responses().empty();
}
bool on_response(Ctx& c, const Request& r, Value& data) {
    ensure_schema(c.st);
    bool changed = false;
    for (auto& f : responses()) changed |= f(c, r, data);
    return changed;
}
void add_client_master(ClientMasterFn fn, const char* file, int line) {
    client_masters().push_back(std::move(fn));
    record_hook("ClientMaster", file, line);
}
void client_master(sqlite3* db, int64_t now, int64_t event_now) {
    modules::register_all();
    Sql s;
    s.h = db;
    for (auto& f : client_masters()) f(s, now, event_now);
}

const Handler* find(const std::string& method) {
    modules::register_all();
    auto it = apis().find(method);
    return it == apis().end() ? nullptr : &it->second;
}
void player_load(Ctx& c, const Request& r, Value& data) {
    ensure_schema(c.st);
    for (auto& f : loads()) f(c, r, data);
}
void ensure_schema(Sql& st) {
    modules::register_all();
    if (!st.h) return;
    for (const char* s : schemas()) st.exec(s);
}

double global_f(Ctx& c, const char* key, double dflt) { return master::global_f(c.m.h, key, dflt); }

// The wallet (core/wallet.h).
u32 stock_count(Ctx& c, u32 item) { return wallet::stock_count(c.st.h, item); }
void add_stock(Ctx& c, u32 item, int64_t delta) { wallet::add_stock(c.st.h, c.m.h, item, delta); }
u32 fol(Ctx& c) { return wallet::fol(c.st.h); }
void add_fol(Ctx& c, int64_t delta) { wallet::add_fol(c.st.h, c.m.h, delta); }
void count(Ctx& c, const std::string& key, int64_t n) {
    c.st.q("insert into counters values (?, ?) on conflict(key) do update set value = value + excluded.value", {key, n});
}
int64_t counter(Ctx& c, const std::string& key) { return c.st.one("select value from counters where key = ?", {key}); }
void add_present(Ctx& c, u32 type, u32 id, u32 num, u32 reason_type, u32 reason_param, const std::string& text) {
    c.st.q("insert into presents (content_type, content_id, num, reason_type, reason_param, created_at) values (?,?,?,?,?,?)",
           {type, id, num, reason_type, reason_param, c.now()});
    if (!text.empty()) c.st.q("insert or replace into present_texts values (last_insert_rowid(), ?)", {text});
}
const char* const kSchemaCounters = "create table if not exists counters (key text primary key, value integer)";

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_counters() { add_schema(kSchemaCounters); }

}  // namespace soa::server::ext
