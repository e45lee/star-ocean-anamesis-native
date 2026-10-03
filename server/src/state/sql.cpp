// The server's one SQLite wrapper (soaserver/sql.h). Port code, not guest behaviour.
#include "soaserver/sql.h"

#include "core/log.h"

namespace soa::server::sql {

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

bool Sql::open(const std::string& path, bool ro) {
    int fl = ro ? SQLITE_OPEN_READONLY : (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    if (sqlite3_open_v2(path.c_str(), &h, fl, nullptr) != SQLITE_OK) {
        LOGE("server", "can't open %s: %s", path.c_str(), h ? sqlite3_errmsg(h) : "?");
        if (h) sqlite3_close(h);
        h = nullptr;
        return false;
    }
    return true;
}
void Sql::close() {
    if (h) sqlite3_close(h);
    h = nullptr;
}

bool Sql::exec(const std::string& sql) {
    char* err = nullptr;
    if (sqlite3_exec(h, sql.c_str(), nullptr, nullptr, &err) == SQLITE_OK) return true;
    LOGE("server", "sql error: %s in %s", err ? err : "?", sql.c_str());
    sqlite3_free(err);
    return false;
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

int64_t one_null_as_zero(Sql& db, const std::string& sql, std::initializer_list<Arg> args, int64_t dflt) {
    int64_t v = dflt;
    db.q(sql, args, [&](const Row& r) { v = r.v.begin()->second ? sqlite3_value_int64(r.v.begin()->second) : dflt; });
    return v;
}

}  // namespace soa::server::sql
