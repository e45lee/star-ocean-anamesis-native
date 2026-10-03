#pragma once
// Reconstructed gacha pools for the local server.
//
// The live server drew from tables (master_gacha.table_name = master_gacha_item_*) that the
// client never had. tools/build_gacha_pools.py rebuilds a pool per gacha from the 3.7.0 master
// data and writes port/server-data/gacha_pools.sqlite3; this is its read-only accessor. The
// rules and their sources are in docs/server-rules.md, "Gacha pools (reconstructed)", and in the
// file's own `rule` table.
//
// A draw: pick a rank S/A/B/C/D by the gacha's rank rates (the bonus rates for the bonus draw of
// a bulk draw), then a unit of that rank's pool by weight. Only units with released_at <= the
// server clock take part, so a unit released mid-window joins on its release day; a rank whose
// pool is still empty at that time is skipped and the other ranks keep their relative rates.
//
// The same numbers feed GetGachaRate (rate_info), so the rate dialog shows what is drawn.
#include <sqlite3.h>

#include <cstdint>
#include <string>
#include <vector>

namespace soa::server::gacha_pools {

enum Rank { kS = 0, kA, kB, kC, kD, kRanks };

struct Unit {
    uint32_t content_type = 0;  // 1 item (weapon), 2 role (character): the master content types
    uint32_t content_id = 0;
    uint32_t weight = 1;
};

struct Gacha {
    uint32_t id = 0;
    std::string id_label, name, kind;  // kind: "role", "weapon" or "box" (box: use master_box_gacha)
    uint32_t gacha_type = 0;
    bool is_bulk_bonus = false, is_stepup = false;
    uint32_t bulk_count = 0, stepup_number = 0, next_stepup_gacha_id = 0;
    double rate[kRanks] = {}, bonus_rate[kRanks] = {};  // percent, from master_gacha
};

// One row of a GachaRateContentInfoList (CGachaRateContentInfo: type, message_id, content_id,
// percentage, direct_message, order_id). Row types, from CGachaRatio::CreateRatioList /
// ListItemUpdate (b): 1 separator line, 2 text line, 3 section title, 4 character (content_id =
// role; the client shows its name, rarity, class and weapon icons), 5 item with rarity icon
// (weapon), 8 item without it, 6 / 7 open / close a block of rows that the client sorts.
// Text rows show direct_message when it is set, otherwise message_id; unit rows show
// `percentage` as given ("%.5f%%" in the live texts, gacha_tilte_message_0009).
struct RateLine {
    uint32_t type = 0;
    std::string message_id;
    uint32_t content_id = 0;
    std::string percentage;
    std::string direct_message;
    uint32_t order_id = 0;
};

// One CGachaRateInfo (id, title, introduction_msg, bonus_msg, stepup_number,
// GachaRateContentInfoList). CGachaRatio::SearchRatioInfo takes the first entry for a normal
// gacha and the entry whose stepup_number is the current step for a step-up (b).
struct RateInfo {
    uint32_t id = 0;
    std::string title, introduction_msg, bonus_msg;
    uint32_t stepup_number = 0;
    std::vector<RateLine> lines;
};

class Pools {
public:
    Pools() = default;
    ~Pools();
    Pools(const Pools&) = delete;
    Pools& operator=(const Pools&) = delete;

    // Opens the file read-only. An empty path searches $SOA_GACHA_POOLS, then
    // port/server-data/gacha_pools.sqlite3 in the repo (core/paths.h).
    bool open(const std::string& path = "");
    bool is_open() const { return db_ != nullptr; }
    const std::string& path() const { return path_; }

    bool gacha(uint32_t gacha_id, Gacha& out) const;
    uint32_t id_of(const std::string& id_label) const;  // 0 when unknown
    // The rank's pool at `now` ("YYYY-MM-DD HH:MM:SS", the server clock); empty when none.
    std::vector<Unit> units(uint32_t gacha_id, int rank, const std::string& now) const;
    // The rank's whole pool (every unit up to the end of the window), ignoring release times.
    std::vector<Unit> all_units(uint32_t gacha_id, int rank) const;
    // One draw. r_rank / r_unit are uniform 64-bit random numbers. False when the gacha is
    // unknown, a box gacha, or has nothing to draw at `now`.
    bool draw(uint32_t gacha_id, bool bonus, const std::string& now, uint64_t r_rank, uint64_t r_unit, int& rank, Unit& unit) const;
    // The effective rank weights of a draw at `now` (rates of ranks with an empty pool are 0),
    // in 1/100000 percent. Their sum is the denominator of draw()'s rank pick.
    void rank_weights(uint32_t gacha_id, bool bonus, const std::string& now, uint64_t w[kRanks]) const;
    // GetGachaRate: one entry for a normal gacha, one per step (following next_stepup_gacha_id
    // from `gacha_id`) for a step-up.
    std::vector<RateInfo> rate_info(uint32_t gacha_id, const std::string& now) const;
    // The rows of one gacha (see RateLine).
    std::vector<RateLine> rate_lines(uint32_t gacha_id, const std::string& now) const;

private:
    sqlite3* db_ = nullptr;
    std::string path_;
    int set_id(uint32_t gacha_id, int rank) const;
};

}  // namespace soa::server::gacha_pools
