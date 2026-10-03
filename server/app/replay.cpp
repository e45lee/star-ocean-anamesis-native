// soa-server --replay and --list-apis (replay.h). Test tooling: no game rule lives here.
#include "replay.h"

#include <sqlite3.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "net/game.h"
#include "net/wire.h"
#include "soaserver/battle_log.h"
#include "soaserver/config.h"
#include "soaserver/ext.h"
#include "soaserver/log.h"
#include "soaserver/msgpack.h"
#include "soaserver/server.h"

namespace soa::server::app {

namespace {

// ---- the clock source: the recorded request's time ------------------------------------------
int64_t g_wall = 0;
int64_t replay_wall() { return g_wall; }

// ---- the log: every line into OUT/server.log ---------------------------------------------------
FILE* g_log = nullptr;
bool g_verbose = false;
void log_to_file(LogLevel lvl, const char* tag, const char* msg) {
    static const char* names[] = {"T", "D", "I", "W", "E"};
    if (g_log) fprintf(g_log, "%s/%s: %s\n", names[(int)lvl], tag, msg);
}
bool log_level(LogLevel l) { return l >= (g_verbose ? LogLevel::Debug : LogLevel::Info); }

std::vector<uint8_t> unhex(const std::string& h, bool* ok) {
    std::vector<uint8_t> v;
    *ok = h.size() % 2 == 0;
    for (size_t i = 0; *ok && i < h.size(); i += 2) {
        unsigned b = 0;
        if (sscanf(h.c_str() + i, "%2x", &b) != 1) *ok = false;
        v.push_back((uint8_t)b);
    }
    return v;
}

std::vector<std::string> split(const std::string& s, char sep) {
    std::vector<std::string> v;
    size_t p = 0;
    for (;;) {
        size_t q = s.find(sep, p);
        v.push_back(s.substr(p, q == std::string::npos ? std::string::npos : q - p));
        if (q == std::string::npos) return v;
        p = q + 1;
    }
}

// A `req` line's fields (server/tests/replay/README.md): "-" is an empty list.
bool parse_req_fields(const std::vector<std::string>& f, Request* r) {
    // req <n> <t> <Method> <fid> <ints> <strs> <vecs> <battle log>
    if (f.size() != 9) return false;
    r->method = f[3];
    r->fid = (u32)strtoul(f[4].c_str(), nullptr, 16);
    if (f[5] != "-")
        for (auto& x : split(f[5], ',')) r->ints.push_back(strtoull(x.c_str(), nullptr, 10));
    bool ok = true;
    if (f[6] != "-")
        for (auto& x : split(f[6], ',')) {
            auto b = x == "_" ? std::vector<uint8_t>() : unhex(x, &ok);
            if (!ok) return false;
            r->strs.emplace_back(b.begin(), b.end());
        }
    if (f[7] != "-")
        for (auto& g : split(f[7], '|')) {
            std::vector<u64> v;
            if (g != "_")
                for (auto& x : split(g, ',')) v.push_back(strtoull(x.c_str(), nullptr, 10));
            r->vecs.push_back(std::move(v));
        }
    if (f[8] != "-") {
        auto b = unhex(f[8], &ok);
        if (!ok) return false;
        r->battle_log = parse_battle_log(b.data(), b.size());
    }
    return true;
}

// ---- a reply as text (OUT/replies.txt) -----------------------------------------------------------
void print_value(const Value& v, std::string& o, int ind) {
    char b[64];
    switch (v.type) {
        case Value::Nil:
            o += "nil";
            break;
        case Value::Bool:
            o += v.b ? "true" : "false";
            break;
        case Value::Int:
            snprintf(b, sizeof b, "%" PRId64, v.i), o += b;
            break;
        case Value::UInt:
            snprintf(b, sizeof b, "%" PRIu64, v.u), o += b;
            break;
        case Value::Float:
            snprintf(b, sizeof b, "%.17g", v.f), o += b;
            break;
        case Value::Str:
            o += "\"" + v.s + "\"";
            break;
        case Value::Arr:
            if (v.arr.empty()) {
                o += "[]";
                break;
            }
            o += "[\n";
            for (auto& e : v.arr) {
                o += std::string(ind + 2, ' ');
                print_value(e, o, ind + 2);
                o += "\n";
            }
            o += std::string(ind, ' ') + "]";
            break;
        case Value::Map:
            if (v.map.empty()) {
                o += "{}";
                break;
            }
            o += "{\n";
            for (auto& [k, e] : v.map) {
                o += std::string(ind + 2, ' ') + k + ": ";
                print_value(e, o, ind + 2);
                o += "\n";
            }
            o += std::string(ind, ' ') + "}";
            break;
    }
}

bool write_file(const std::string& path, const void* p, size_t n) {
    FILE* f = fopen(path.c_str(), "wb");
    if (!f) return false;
    fwrite(p, 1, n, f);
    fclose(f);
    return true;
}

// ---- the end state (OUT/state.sql) -----------------------------------------------------------
std::string sql_literal(sqlite3_stmt* s, int col) {
    char b[64];
    switch (sqlite3_column_type(s, col)) {
        case SQLITE_NULL:
            return "NULL";
        case SQLITE_INTEGER:
            snprintf(b, sizeof b, "%lld", (long long)sqlite3_column_int64(s, col));
            return b;
        case SQLITE_FLOAT:
            snprintf(b, sizeof b, "%.17g", sqlite3_column_double(s, col));
            return b;
        case SQLITE_BLOB: {
            const uint8_t* p = (const uint8_t*)sqlite3_column_blob(s, col);
            int n = sqlite3_column_bytes(s, col);
            std::string o = "X'";
            for (int i = 0; i < n; i++) snprintf(b, sizeof b, "%02x", p[i]), o += b;
            return o + "'";
        }
        default: {
            std::string t((const char*)sqlite3_column_text(s, col), sqlite3_column_bytes(s, col)), o = "'";
            for (char c : t) o += c == '\'' ? std::string("''") : std::string(1, c);
            return o + "'";
        }
    }
}

bool dump_state(const std::string& db, const std::string& data_dir, const std::string& out) {
    sqlite3* h = nullptr;
    if (sqlite3_open_v2(db.c_str(), &h, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) {
        sqlite3_close(h);
        return false;
    }
    std::string o;
    std::vector<std::pair<std::string, std::string>> tables;
    sqlite3_stmt* s = nullptr;
    sqlite3_prepare_v2(h, "select name, sql from sqlite_master where type in ('table', 'index') and sql is not null order by type desc, name", -1, &s,
                       nullptr);
    while (sqlite3_step(s) == SQLITE_ROW) tables.emplace_back((const char*)sqlite3_column_text(s, 0), (const char*)sqlite3_column_text(s, 1));
    sqlite3_finalize(s);
    for (auto& [name, sql] : tables) {
        o += sql + ";\n";
        if (sql.compare(0, 12, "CREATE TABLE") != 0 && sql.compare(0, 12, "create table") != 0) continue;
        std::vector<std::string> rows;
        std::string q = "select * from \"" + name + "\"";
        if (sqlite3_prepare_v2(h, q.c_str(), -1, &s, nullptr) != SQLITE_OK) continue;
        while (sqlite3_step(s) == SQLITE_ROW) {
            std::string r = "INSERT INTO \"" + name + "\" VALUES(";
            for (int c = 0; c < sqlite3_column_count(s); c++) r += (c ? "," : "") + sql_literal(s, c);
            rows.push_back(r + ");");
        }
        sqlite3_finalize(s);
        std::sort(rows.begin(), rows.end());
        for (auto& r : rows) o += r + "\n";
    }
    sqlite3_close(h);
    // The side files of the data dir (state outside the DB: the story campaign's progress).
    for (const char* side : {"server_campaign.txt"}) {
        std::ifstream f(data_dir + "/" + side, std::ios::binary);
        o += std::string("-- file ") + side + (f ? ":\n" : ": (none)\n");
        if (f) o += std::string(std::istreambuf_iterator<char>(f), {});
    }
    return write_file(out, o.data(), o.size());
}

}  // namespace

int replay(const std::string& dir, const std::string& out, bool verbose) {
    std::ifstream in(dir + "/requests.txt");
    if (!in) {
        fprintf(stderr, "soa-server --replay: no %s/requests.txt\n", dir.c_str());
        return 2;
    }
    mkdir(out.c_str(), 0755);
    std::string data = out + "/data";
    mkdir(data.c_str(), 0755);
    ServerConfig& c = config();
    c.enabled = true;
    c.data_root = data;
    // The replay starts from a fresh state and deletes it first: never a state DB given by --db.
    if (!c.db.empty()) {
        fprintf(stderr, "soa-server --replay: --db is not allowed (the replay's state is OUT/data/server.sqlite3)\n");
        return 2;
    }
    c.db = data + "/server.sqlite3";
    for (const char* suffix : {"", "-wal", "-shm"}) unlink((c.db + suffix).c_str());
    unlink((data + "/server_campaign.txt").c_str());
    if (!c.has_seed_rng) {
        fprintf(stderr, "soa-server --replay: needs --seed-rng (the corpus's options)\n");
        return 2;
    }
    g_verbose = verbose;
    g_log = fopen((out + "/server.log").c_str(), "w");
    FILE* errors = fopen((out + "/errors.txt").c_str(), "w");
    FILE* replies = fopen((out + "/replies.txt").c_str(), "w");
    if (!g_log || !errors || !replies) {
        fprintf(stderr, "soa-server --replay: can't write into %s\n", out.c_str());
        return 2;
    }
    set_log_sink(log_to_file, log_level);
    set_clock_source(replay_wall);
    const int64_t offset = c.has_clock ? c.clock_offset : 0;  // Server::init's --clock offset
    auto backend = net::live_backend();
    std::string line;
    int lineno = 0, n_req = 0, status = 0;
    while (std::getline(in, line)) {
        lineno++;
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ls(line);
        std::vector<std::string> f;
        for (std::string w; ls >> w;) f.push_back(w);
        Request r;
        bool ok = f.size() >= 3;
        if (ok && f[0] == "wire" && f.size() == 5) {
            // wire <n> <t> <WireApi name> <the request's plaintext body, hex>
            const net::WireApi* api = net::api_by_name(f[3]);
            std::vector<uint8_t> body = unhex(f[4], &ok);
            net::Decoded d;
            std::string err;
            ok = ok && api && net::decode_request(*api, body.data(), body.size(), &d, &err);
            if (ok) r = d.req;
        } else if (ok && f[0] == "req") {
            ok = parse_req_fields(f, &r);
        } else {
            ok = false;
        }
        if (!ok) {
            fprintf(stderr, "soa-server --replay: %s/requests.txt:%d: unreadable request\n", dir.c_str(), lineno);
            status = 2;
            break;
        }
        std::string n = f[1];
        g_wall = strtoll(f[2].c_str(), nullptr, 10) - offset;  // the server clock reads the recorded time
        fprintf(g_log, "== %s %s\n", n.c_str(), r.method.c_str());
        std::vector<uint8_t> body;
        uint32_t code = backend->call(r, &body);
        n_req++;
        write_file(out + "/" + n + "-" + r.method + ".msgp", body.data(), body.size());
        fprintf(errors, "%s %s %s\n", n.c_str(), r.method.c_str(), code == net::kNotHandled ? "not-handled" : std::to_string(code).c_str());
        std::string text;
        print_value(mp_decode(body), text, 0);
        fprintf(replies, "== %s %s\n%s\n", n.c_str(), r.method.c_str(), text.c_str());
    }
    fclose(errors);
    fclose(replies);
    set_log_sink(nullptr, nullptr);
    fclose(g_log);
    g_log = nullptr;
    if (status) return status;
    if (!dump_state(c.db, data, out + "/state.sql")) {
        fprintf(stderr, "soa-server --replay: can't read the state %s\n", c.db.c_str());
        return 1;
    }
    fprintf(stderr, "soa-server --replay: %d requests from %s into %s\n", n_req, dir.c_str(), out.c_str());
    return 0;
}

int list_apis() {
    std::map<std::string, std::string> by;  // method -> answered by
    std::map<std::string, std::string> fid;
    for (auto& a : net::apis()) {
        char b[16];
        snprintf(b, sizeof b, "%08x", a.fid);
        by.emplace(a.method, "-");
        fid.emplace(a.method, b);
    }
    for (auto& [m, file] : ext::api_sources()) {
        size_t p = file.rfind("/server/");
        by[m] = p == std::string::npos ? file : file.substr(p + 1);
    }
    for (auto& [m, b] : by) {
        auto f = fid.find(m);
        printf("%s\t%s\t%s\n", m.c_str(), f == fid.end() ? "-" : f->second.c_str(), b.c_str());
    }
    return 0;
}

int list_hooks() {
    for (const ext::HookInfo& h : ext::hook_order())
        printf("%s\t%s\t%s:%d\t%s\n", h.kind.c_str(), h.module.c_str(), h.file.c_str(), h.line, h.detail.c_str());
    return 0;
}

}  // namespace soa::server::app
