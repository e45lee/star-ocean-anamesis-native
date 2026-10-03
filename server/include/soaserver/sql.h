#pragma once
// The server's one SQLite wrapper (port code, not guest behaviour): a handle to the state or the
// master DB, statements with bound arguments, rows read by column name. Every handler sees it as
// ext::Sql / ext::Row / ext::Arg (soaserver/ext.h); the server object owns the two handles it
// opens with Sql::open (src/core/server.h), the handlers borrow them through their ext::Ctx.
// Defined in src/state/sql.cpp (server/PLAN-readability.md 1.5: the core's former Db and the
// modules' ext::Sql were two copies; PLAN-schema S1 merged them).
#include <sqlite3.h>

#include <cstddef>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <map>
#include <string>

namespace soa::server::sql {

// One result row, its values by column name (valid only during the row callback). A NULL value or
// a column the row doesn't have reads as 0 / 0.0 / "".
struct Row {
    std::map<std::string, sqlite3_value*> v;
    int64_t i(const char* k) const;
    double f(const char* k) const;
    std::string s(const char* k) const;
    bool null(const char* k) const;
};

// A bound argument: an integer (unsigned 64-bit values keep their bits), a double, a text or NULL.
struct Arg {
    enum { I, S, N, F } t;
    int64_t i = 0;
    double d = 0;
    std::string s;
    Arg(int v) : t(I), i(v) {}
    Arg(unsigned v) : t(I), i(v) {}
    Arg(long v) : t(I), i(v) {}
    Arg(unsigned long v) : t(I), i((int64_t)v) {}
    Arg(long long v) : t(I), i(v) {}
    Arg(unsigned long long v) : t(I), i((int64_t)v) {}
    Arg(double v) : t(F), d(v) {}
    Arg(const char* v) : t(S), s(v) {}
    Arg(std::string v) : t(S), s(std::move(v)) {}
    Arg(std::nullptr_t) : t(N) {}
};

// A handle (borrowed: copying it doesn't copy the connection; the server object closes it).
// Errors are logged ("sql error" / "sql prepare" / "sql step"), not returned.
struct Sql {
    sqlite3* h = nullptr;
    // Opens the DB at `path` (read-only: `ro`, else read-write, created when missing); false
    // (logged) when it can't.
    bool open(const std::string& path, bool ro);
    void close();
    // Runs `sql` (any number of statements); false (logged) when it fails.
    bool exec(const std::string& sql);
    // Runs `sql` with `args`, calling `fn` per row; the number of rows.
    int q(const std::string& sql, std::initializer_list<Arg> args, const std::function<void(const Row&)>& fn = {});
    // The first column of the last row: `dflt` when there is no row or its value is NULL.
    int64_t one(const std::string& sql, std::initializer_list<Arg> args, int64_t dflt = 0);
};

// one() as the core's former Db::one read it: `dflt` when there is no row, but a NULL value reads
// as 0 (Sql::one reads it as `dflt`). Kept, by name, at the five core sites whose default isn't 0
// (server/PLAN-readability.md 1.5), each decided and commented at the site: MissionStart's
// party_id, the character bonus's and the rewards' two role categories, the step-up chain's step.
int64_t one_null_as_zero(Sql& db, const std::string& sql, std::initializer_list<Arg> args, int64_t dflt);

}  // namespace soa::server::sql
