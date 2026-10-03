// Reconstructed gacha pools: the read-only accessor of data/gacha_pools.sqlite3.
// See gacha_pools.h and docs/server-rules.md "Gacha pools (reconstructed)". Source labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include "master/gacha_pools.h"

#include <sys/stat.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <map>

#include "core/log.h"
#include "soaserver/config.h"

namespace soa::server::gacha_pools {
namespace {

bool exists(const std::string& p) {
    struct stat s;
    return !p.empty() && stat(p.c_str(), &s) == 0 && S_ISREG(s.st_mode);
}

// A prepared statement bound to integers / text, stepped by the caller.
struct Stmt {
    sqlite3_stmt* s = nullptr;
    Stmt(sqlite3* db, const char* sql) {
        if (db && sqlite3_prepare_v2(db, sql, -1, &s, nullptr) != SQLITE_OK) {
            LOGE("gacha", "sql: %s: %s", sqlite3_errmsg(db), sql);
            s = nullptr;
        }
    }
    ~Stmt() { sqlite3_finalize(s); }
    Stmt& i(int k, int64_t v) {
        if (s) sqlite3_bind_int64(s, k, v);
        return *this;
    }
    Stmt& t(int k, const std::string& v) {
        if (s) sqlite3_bind_text(s, k, v.c_str(), (int)v.size(), SQLITE_TRANSIENT);
        return *this;
    }
    bool row() { return s && sqlite3_step(s) == SQLITE_ROW; }
    int64_t col_i(int c) { return sqlite3_column_int64(s, c); }
    double col_f(int c) { return sqlite3_column_double(s, c); }
    std::string col_s(int c) {
        const unsigned char* p = sqlite3_column_text(s, c);
        return p ? (const char*)p : "";
    }
};

std::string fmt(const char* f, double v) {
    char b[64];
    snprintf(b, sizeof b, f, v);
    return b;
}

}  // namespace

Pools::~Pools() {
    if (db_) sqlite3_close(db_);
}

bool Pools::open(const std::string& path) {
    std::vector<std::string> cands;
    if (!path.empty()) cands.push_back(path);
    else {
        if (const char* e = getenv("SOA_GACHA_POOLS")) cands.push_back(e);
        if (std::string p = find_repo_file("data/gacha_pools.sqlite3"); !p.empty()) cands.push_back(p);
    }
    for (auto& c : cands) {
        if (!exists(c)) continue;
        sqlite3* db = nullptr;
        if (sqlite3_open_v2(c.c_str(), &db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) {
            sqlite3_close(db);
            continue;
        }
        // A git-lfs pointer file (not fetched) is not a database.
        Stmt chk(db, "select value from meta where key = 'format'");
        if (!chk.row()) {
            LOGE("gacha", "%s is not a gacha pool file (an old Git LFS pointer? tools/build_gacha_pools.py makes the real file)", c.c_str());
            sqlite3_close(db);
            continue;
        }
        if (db_) sqlite3_close(db_);
        db_ = db;
        path_ = c;
        LOGI("gacha", "reconstructed gacha pools: %s (format %s)", c.c_str(), chk.col_s(0).c_str());
        return true;
    }
    LOGW("gacha", "no reconstructed gacha pools (data/gacha_pools.sqlite3; tools/build_gacha_pools.py)");
    return false;
}

bool Pools::gacha(uint32_t id, Gacha& g) const {
    Stmt s(db_,
           "select id_label, name, kind, gacha_type, is_bulk_bonus, bulk_count, is_stepup, stepup_number, "
           "next_stepup_gacha_id from gacha where gacha_id = ?");
    if (!s.i(1, id).row()) return false;
    g = Gacha{};
    g.id = id;
    g.id_label = s.col_s(0);
    g.name = s.col_s(1);
    g.kind = s.col_s(2);
    g.gacha_type = (uint32_t)s.col_i(3);
    g.is_bulk_bonus = s.col_i(4) != 0;
    g.bulk_count = (uint32_t)s.col_i(5);
    g.is_stepup = s.col_i(6) != 0;
    g.stepup_number = (uint32_t)s.col_i(7);
    g.next_stepup_gacha_id = (uint32_t)s.col_i(8);
    Stmt r(db_, "select rank, rate, bonus_rate from gacha_rank where gacha_id = ?");
    r.i(1, id);
    while (r.row()) {
        std::string k = r.col_s(0);
        size_t n = std::string("SABCD").find(k);
        if (k.size() != 1 || n == std::string::npos) continue;
        g.rate[n] = r.col_f(1);
        g.bonus_rate[n] = r.col_f(2);
    }
    return true;
}

uint32_t Pools::id_of(const std::string& id_label) const {
    Stmt s(db_, "select gacha_id from gacha where id_label = ?");
    return s.t(1, id_label).row() ? (uint32_t)s.col_i(0) : 0;
}

int Pools::set_id(uint32_t id, int rank) const {
    if (rank < 0 || rank >= kRanks) return 0;
    Stmt s(db_, "select ifnull(set_id, 0) from gacha_rank where gacha_id = ? and rank = ?");
    return s.i(1, id).t(2, std::string(1, "SABCD"[rank])).row() ? (int)s.col_i(0) : 0;
}

std::vector<Unit> Pools::units(uint32_t id, int rank, const std::string& now) const {
    std::vector<Unit> out;
    int sid = set_id(id, rank);
    if (!sid) return out;
    // (a)+(d) R-WINDOW: a unit takes part from its release time on
    Stmt s(db_,
           "select content_type, content_id, weight from pool_set where set_id = ? and released_at <= ? "
           "order by rowid");
    s.i(1, sid).t(2, now);
    while (s.row()) out.push_back({(uint32_t)s.col_i(0), (uint32_t)s.col_i(1), (uint32_t)s.col_i(2)});
    return out;
}

std::vector<Unit> Pools::all_units(uint32_t id, int rank) const { return units(id, rank, "9999"); }

void Pools::rank_weights(uint32_t id, bool bonus, const std::string& now, uint64_t w[kRanks]) const {
    Gacha g;
    for (int k = 0; k < kRanks; k++) w[k] = 0;
    if (!gacha(id, g) || g.kind == "box") return;
    for (int k = 0; k < kRanks; k++) {
        double r = bonus ? g.bonus_rate[k] : g.rate[k];  // (a) master_gacha rank rates, in percent
        // (d) a rank with nothing released yet is skipped; the others keep their relative rates
        if (r > 0 && !units(id, k, now).empty()) w[k] = (uint64_t)std::llround(r * 100000.0);
    }
}

bool Pools::draw(uint32_t id, bool bonus, const std::string& now, uint64_t r_rank, uint64_t r_unit, int& rank, Unit& unit) const {
    uint64_t w[kRanks], sum = 0;
    rank_weights(id, bonus, now, w);
    for (auto x : w) sum += x;
    if (!sum && bonus) {  // (d) a bonus row without rates (is_bulk_bonus with all-zero bonus rates): a normal draw
        rank_weights(id, false, now, w);
        for (auto x : w) sum += x;
    }
    if (!sum) return false;
    uint64_t r = r_rank % sum;
    rank = kRanks - 1;
    for (int k = 0; k < kRanks; k++) {
        if (r < w[k]) {
            rank = k;
            break;
        }
        r -= w[k];
    }
    std::vector<Unit> pool = units(id, rank, now);
    uint64_t tw = 0;
    for (auto& u : pool) tw += u.weight;
    if (!tw) return false;
    uint64_t x = r_unit % tw;  // (d) R-WEIGHT: equal weights within a rank
    for (auto& u : pool) {
        if (x < u.weight) {
            unit = u;
            return true;
        }
        x -= u.weight;
    }
    unit = pool.back();
    return true;
}

std::vector<RateLine> Pools::rate_lines(uint32_t id, const std::string& now) const {
    std::vector<RateLine> out;
    Gacha g;
    if (!gacha(id, g) || g.kind == "box") return out;
    uint32_t order = 0;
    auto line = [&](uint32_t type, const std::string& msg, const std::string& text, uint32_t cid = 0, const std::string& pct = "") {
        out.push_back({type, msg, cid, pct, text, ++order});
    };
    // Rarity groups: ★5 = S + A, ★4 = B, ★3 = C (a: R-RANK-ROLE / R-RANK-WEAPON); D is never used.
    struct Group {
        const char* star;
        std::vector<int> ranks;
        const char* total_msg;
        const char* head_msg;
    };
    const Group groups[] = {{"★5", {kS, kA}, "gacha_tilte_message_0002", "gacha_tilte_message_0005"},
                            {"★4", {kB}, "gacha_tilte_message_0003", "gacha_tilte_message_0006"},
                            {"★3", {kC, kD}, "gacha_tilte_message_0004", "gacha_tilte_message_0007"}};
    uint32_t unit_type = g.kind == "role" ? 4 : 5;
    auto section = [&](bool bonus) {
        uint64_t w[kRanks], sum = 0;
        rank_weights(id, bonus, now, w);
        for (auto x : w) sum += x;
        if (!sum) return false;
        for (auto& gr : groups) {
            double total = 0;
            std::map<std::pair<uint32_t, uint32_t>, double> pct;  // unit -> percent (a unit may be in S and A)
            std::vector<std::pair<uint32_t, uint32_t>> order_units;
            for (int k : gr.ranks) {
                if (!w[k]) continue;
                double rk = 100.0 * (double)w[k] / (double)sum;
                total += rk;
                std::vector<Unit> pool = units(id, k, now);
                uint64_t tw = 0;
                for (auto& u : pool) tw += u.weight;
                for (auto& u : pool) {
                    auto key = std::make_pair(u.content_type, u.content_id);
                    if (!pct.count(key)) order_units.push_back(key);
                    pct[key] += rk * u.weight / (double)tw;
                }
            }
            if (total <= 0) continue;
            line(3, gr.head_msg, fmt((std::string(gr.star) + "提供割合 %.5f%%").c_str(), total));
            line(6, "", "");
            for (auto& key : order_units) line(key.first == 2 ? 4 : unit_type == 4 ? 5 : unit_type, "", "", key.second, fmt("%.5f%%", pct[key]));
            line(7, "", "");
        }
        return true;
    };
    // The by-rarity summary (gacha_tilte_message_0001..0004), then the per-unit list
    // (0010, 0005..0007), then the bulk draw's bonus slot (0008) (b: the rate dialog's texts in
    // master_text; d: this layout).
    uint64_t w[kRanks], sum = 0;
    rank_weights(id, false, now, w);
    for (auto x : w) sum += x;
    line(3, "gacha_tilte_message_0001", "レアリティー別提供割合");
    for (auto& gr : groups) {
        double total = 0;
        for (int k : gr.ranks) total += sum ? 100.0 * (double)w[k] / (double)sum : 0.0;
        if (total > 0) line(2, gr.total_msg, fmt((std::string(gr.star) + ":%.5f%%").c_str(), total));
    }
    line(1, "", "");
    line(3, "gacha_tilte_message_0010", "一般提供割合");
    section(false);
    if (g.is_bulk_bonus) {
        uint64_t b[kRanks], bs = 0;
        rank_weights(id, true, now, b);
        for (auto x : b) bs += x;
        if (bs) {
            line(1, "", "");
            line(3, "gacha_tilte_message_0008", "10連ガチャ特典枠");
            section(true);
        }
    }
    return out;
}

std::vector<RateInfo> Pools::rate_info(uint32_t id, const std::string& now) const {
    std::vector<RateInfo> out;
    std::vector<uint32_t> seen;
    uint32_t cur = id;
    // (a) step-ups chain through next_stepup_gacha_id; the last step points back into the chain
    while (cur && std::find(seen.begin(), seen.end(), cur) == seen.end() && seen.size() < 64) {
        seen.push_back(cur);
        Gacha g;
        if (!gacha(cur, g)) break;
        RateInfo ri;
        ri.id = cur;
        ri.title = g.name;
        ri.stepup_number = g.is_stepup ? g.stepup_number : 0;
        ri.lines = rate_lines(cur, now);
        out.push_back(std::move(ri));
        if (!g.is_stepup) break;
        cur = g.next_stepup_gacha_id;
    }
    return out;
}

}  // namespace soa::server::gacha_pools

// ---- tests (--selftest; not differential: the server has no guest counterpart) -------------
#include "soaserver/native_test.h"

namespace soa::server::gacha_pools {
namespace {

Pools* test_pools() {
    static Pools p;
    static bool tried = false;
    if (!tried) {
        tried = true;
        p.open();
    }
    return p.is_open() ? &p : nullptr;
}

NATIVE_TEST("server/gacha-pools") {
    Pools* p = test_pools();
    if (!p) return;  // the file isn't there (a checkout without it; tools/build_gacha_pools.py makes it): nothing to check
    const std::string now = "2021-06-10 15:00:00";
    // gacha_role_0001 (the standard character gacha, open 2016..2030): S 2.2 A 3.8 B 26.1 C 67.9
    Gacha g;
    uint32_t std_id = p->id_of("gacha_role_0001");
    if (!t.expect_eq(p->gacha(std_id, g), true, "gacha_role_0001 known")) return;
    t.expect_eq(g.kind, std::string("role"), "kind");
    if (std::fabs(g.rate[kS] - 2.2) > 1e-9 || std::fabs(g.rate[kC] - 67.9) > 1e-9) t.fail("rates %f %f", g.rate[kS], g.rate[kC]);
    for (int k = kS; k <= kC; k++)
        if (p->units(std_id, k, now).empty()) t.fail("rank %d empty", k);
    if (!p->units(std_id, kD, now).empty()) t.fail("rank D not empty");
    // the pool grows with the clock (R-WINDOW)
    if (p->units(std_id, kS, "2018-01-01 00:00:00").size() >= p->units(std_id, kS, now).size())
        t.fail("the ace pool didn't grow between 2018 and 2021");
    // draw frequencies follow the rank rates
    int hits[kRanks] = {};
    for (int n = 0; n < 20000; n++) {
        int rank;
        Unit u;
        if (!p->draw(std_id, false, now, t.rand_u64(), t.rand_u64(), rank, u)) {
            t.fail("draw failed");
            return;
        }
        hits[rank]++;
        if (u.content_type != 2) t.fail("not a role");
    }
    if (std::abs(hits[kC] - 13580) > 400 || std::abs(hits[kB] - 5220) > 350 || hits[kD])
        t.fail("rank frequencies S %d A %d B %d C %d D %d", hits[kS], hits[kA], hits[kB], hits[kC], hits[kD]);
    // the rate dialog's unit rows add up to 100 % in the general section and again in the
    // bulk draw's bonus slot
    double total[2] = {};
    int units = 0, sec = 0;
    for (auto& l : p->rate_lines(std_id, now)) {
        if (l.message_id == "gacha_tilte_message_0008") sec = 1;
        if (l.type == 4 || l.type == 5) {
            units++;
            total[sec] += atof(l.percentage.c_str());
        }
    }
    if (!units || std::fabs(total[0] - 100.0) > 0.05 || (g.is_bulk_bonus && std::fabs(total[1] - 100.0) > 0.05))
        t.fail("rate rows: %d units, %.5f %% + bonus %.5f %%", units, total[0], total[1]);
    // every gacha with a pool can draw at the end of its window and shows a non-empty rate list
    std::vector<uint32_t> ids;
    {
        sqlite3* db = nullptr;
        if (sqlite3_open_v2(p->path().c_str(), &db, SQLITE_OPEN_READONLY, nullptr) == SQLITE_OK) {
            Stmt q(db,
                   "select gacha_id, min(closed_at, '2021-06-24 14:30:00') from gacha where kind != 'box' "
                   "order by gacha_id");
            while (q.row()) {
                uint32_t gid = (uint32_t)q.col_i(0);
                int rank;
                Unit u;
                if (!p->draw(gid, false, q.col_s(1), t.rand_u64(), t.rand_u64(), rank, u)) t.fail("gacha %u: no draw", gid);
                else if (p->rate_lines(gid, q.col_s(1)).empty()) t.fail("gacha %u: no rate lines", gid);
            }
        }
        sqlite3_close(db);
    }
}

}  // namespace
}  // namespace soa::server::gacha_pools
