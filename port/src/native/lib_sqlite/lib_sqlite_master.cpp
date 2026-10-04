// Test support shared by the differential tests that run the game's queries on the 3.7.0 master
// (lib_sqlite_test.cpp: the host SQLite against the guest's 3.13.0; yayoi's SQLite driver tests): the
// master staged at an Android path, and the query corpus (every "SELECT * FROM ..." string of the 3.7.0
// lib and every table's own queries, instantiated with the master's values).
#include "native/lib_sqlite/lib_sqlite_master.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iterator>
#include <regex>

#include "core/paths.h"
#include "core/vfs.h"

namespace soa::native::lib_sqlite {

// The 3.7.0 master copied to a guest path (the game ATTACHes its decrypted copy by its Android path).
std::string stage_master(TestContext& t, std::string* host_copy, const char* file_name) {
    std::string src = find_repo_file("data/basmaster-3.7.0.sqlite3");
    if (src.empty()) {
        t.fail("data/basmaster-3.7.0.sqlite3 not found");
        return "";
    }
    std::string guest = guest_internal_dir() + "/" + file_name;
    *host_copy = host_path(guest.c_str());
    std::ifstream in(src, std::ios::binary);
    std::ofstream out(*host_copy, std::ios::binary | std::ios::trunc);
    out << in.rdbuf();
    if (!out) t.fail("can't copy the master to %s", host_copy->c_str());
    return guest;
}

// ---- the query corpus ----


// The game's query strings: every NUL-terminated "SELECT * FROM ..." in the 3.7.0 lib.
std::vector<std::string> lib_queries(TestContext& t) {
    std::string path = find_repo_file("work/libSOA-3.7.0.so");
    std::ifstream f(path, std::ios::binary);
    if (!f) {
        t.fail("work/libSOA-3.7.0.so not found");
        return {};
    }
    std::string bytes((std::istreambuf_iterator<char>(f)), {});
    std::set<std::string> out;
    const std::string key = "SELECT * FROM ";
    for (size_t p = bytes.find(key); p != std::string::npos; p = bytes.find(key, p + 1)) {
        if (p > 0 && bytes[p - 1] != '\0') continue;
        size_t e = bytes.find('\0', p);
        out.insert(bytes.substr(p, e - p));
    }
    return {out.begin(), out.end()};
}


namespace {

std::string table_of(const std::string& sql) {
    static const std::regex re("FROM `?(\\w+)`?");
    std::smatch m;
    return std::regex_search(sql, m, re) ? m[1].str() : "";
}

// The column a placeholder at `pos` compares with: "col = ?", "`col` <= ?", "col IN (" ...; or, for
// "'%s' >= `col`", the one after it.
std::string column_at(const std::string& sql, size_t pos) {
    static const std::regex before("`?(\\w+)`?\\s*(?:NOT\\s+)?(=|<=|>=|<|>|IN\\s*\\(|IN|IS NOT|IS)\\s*'?$");
    static const std::regex after("^'?\\s*(>=|<=|<|>|=)\\s*`?(\\w+)`?");
    std::smatch m;
    std::string pre = sql.substr(0, std::min(pos, sql.size())), post = pos + 2 < sql.size() ? sql.substr(pos + 2) : "";
    if (std::regex_search(pre, m, before)) return m[1].str();
    if (std::regex_search(post, m, after)) return m[2].str();
    return "";
}

// One template -> the queries to run: placeholders ('?' bound as text; %s / %u / %d formatted in; a
// trailing "IN (" / "= " / "<= " completed as the game's code completes it) filled from the master's
// rows, up to `n` tuples, plus a tuple that matches nothing.
std::vector<Query> instantiate(Master& m, const std::string& tmpl, size_t n) {
    std::vector<Query> out;
    // %s as a table name ("SELECT * FROM %s WHERE col ..."): every table with the columns used.
    if (tmpl.rfind("SELECT * FROM %s", 0) == 0) {
        static const std::regex col("(\\w+) (IN|=)");
        std::vector<std::string> need;
        for (auto it = std::sregex_iterator(tmpl.begin(), tmpl.end(), col); it != std::sregex_iterator(); ++it) need.push_back((*it)[1]);
        for (auto& [tb, cols] : m.columns) {
            bool ok = !need.empty();
            for (auto& c : need) ok = ok && cols.count(c);
            if (!ok) continue;
            std::string s = tmpl;
            s.replace(14, 2, tb);
            for (auto& q : instantiate(m, s, n)) out.push_back(q);
        }
        return out;
    }
    if (tmpl.find("__TABLE_NAME__") != std::string::npos) {
        for (auto& [tb, cols] : m.columns) {
            std::string s = std::regex_replace(tmpl, std::regex("__TABLE_NAME__"), tb);
            std::string c = column_at(s, s.find('?') == std::string::npos ? s.size() : s.find('?'));
            if (s.find('?') != std::string::npos && !cols.count(c)) continue;
            for (auto& q : instantiate(m, s, n)) out.push_back(q);
        }
        return out;
    }
    std::string tb = table_of(tmpl);
    // the placeholders, in order: (position, kind, column)
    struct Ph {
        size_t pos;
        char kind;  // '?', 's', 'u' (number), 'E' (trailing: a value), 'I' (trailing IN list)
        std::string col;
    };
    std::vector<Ph> ph;
    for (size_t k = 0; k < tmpl.size(); k++) {
        if (tmpl[k] == '?') ph.push_back({k, '?', column_at(tmpl, k)});
        else if (tmpl[k] == '%' && k + 1 < tmpl.size() && strchr("sud", tmpl[k + 1])) ph.push_back({k, tmpl[k + 1] == 's' ? 's' : 'u', column_at(tmpl, k)});
    }
    static const std::regex in_end("IN\\s*\\($"), eq_end("(=|<=|>=|<|>)\\s*$");
    char trailing = std::regex_search(tmpl, in_end) ? 'I' : std::regex_search(tmpl, eq_end) ? 'E' : 0;
    if (trailing) ph.push_back({tmpl.size(), trailing, column_at(tmpl + "''", tmpl.size())});
    if (ph.empty()) return {{tmpl, {}}};
    std::vector<std::string> cols;
    for (auto& p : ph) {
        if (p.col.empty() || !m.columns[tb].count(p.col)) return {{"-- no column for a placeholder: " + tmpl, {}}};
        cols.push_back(p.col);
    }
    auto raw = m.samples(tb, cols, n, false), lit = m.samples(tb, cols, n, true);
    if (raw.size() != lit.size()) return {};
    raw.push_back(std::vector<std::string>(cols.size(), "-12345"));
    lit.push_back(std::vector<std::string>(cols.size(), "-12345"));
    std::vector<std::string> in_list;  // a trailing IN list: up to 10 of the column's values
    if (trailing == 'I')
        for (auto& r : m.samples(tb, {ph.back().col}, 10, true)) in_list.push_back(r[0]);
    for (size_t r = 0; r < raw.size(); r++) {
        Query q;
        size_t last = 0;
        for (size_t k = 0; k < ph.size(); k++) {
            q.sql += tmpl.substr(last, ph[k].pos - last);
            last = ph[k].pos + (ph[k].kind == '?' ? 1 : ph[k].kind == 'E' || ph[k].kind == 'I' ? 0 : 2);
            switch (ph[k].kind) {
            case '?': q.sql += "?", q.params.push_back(raw[r][k]); break;
            case 's': q.sql += raw[r][k]; break;  // (inside the template's quotes)
            case 'u': q.sql += lit[r][k]; break;
            case 'E': q.sql += lit[r][k]; break;
            case 'I': {
                std::string l = lit[r][k];
                for (auto& v : in_list) l += "," + v;
                q.sql += l + ")";
                break;
            }
            }
        }
        q.sql += tmpl.substr(std::min(last, tmpl.size()));
        out.push_back(std::move(q));
    }
    return out;
}

}  // namespace

// The whole corpus: the lib's templates, plus every table's "SELECT * FROM t" and "... WHERE id=?".
std::vector<Query> corpus(TestContext& t, Master& m, size_t n) {
    std::vector<Query> qs;
    std::vector<std::string> tmpls = lib_queries(t);
    for (auto& [tb, cols] : m.columns) {
        tmpls.push_back("SELECT * FROM " + tb);
        if (cols.count("id")) tmpls.push_back("SELECT * FROM " + tb + " WHERE id=?");
    }
    for (auto& s : tmpls)
        if (s == "SELECT * FROM ") qs.push_back({s, {}});  // (a prefix the code completes: run as is, an error in both)
        else for (auto& q : instantiate(m, s, n)) qs.push_back(std::move(q));
    return qs;
}

}  // namespace soa::native::lib_sqlite
