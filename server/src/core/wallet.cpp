// The player's wallet (core/wallet.h; port code, not guest behaviour).
#include "core/wallet.h"

#include <algorithm>

#include "master/master.h"
#include "soaserver/ext.h"

namespace soa::server::wallet {

using ext::Sql;

Coins coins(sqlite3* st) {
    Sql db{st};
    Coins c;
    c.free = (u32)db.one("select free_coin from player", {});
    c.paid = (u32)db.one("select pay_coin from player", {});
    return c;
}
CoinSplit split(const Coins& have, u32 price, bool paid_only) {
    CoinSplit s;
    s.free = paid_only ? 0 : std::min(have.free, price);
    s.paid = price - s.free;
    return s;
}
bool covers(const Coins& have, u32 price, bool paid_only) { return split(have, price, paid_only).paid <= have.paid; }
void take(sqlite3* st, const CoinSplit& s) {
    Sql db{st};
    db.q("update player set free_coin = free_coin - ?, pay_coin = pay_coin - ?", {s.free, s.paid});
}
bool spend_coins(sqlite3* st, u32 price, bool paid_only) {
    Coins have = coins(st);
    if (!covers(have, price, paid_only)) return false;
    take(st, split(have, price, paid_only));
    return true;
}
void add_free_coins(sqlite3* st, u32 n) {
    Sql db{st};
    db.q("update player set free_coin = free_coin + ?", {n});
}

void add_paid_coins(sqlite3* st, u32 n) {
    Sql db{st};
    db.q("update player set pay_coin = pay_coin + ?", {n});
}

u32 fol(sqlite3* st) {
    Sql db{st};
    return (u32)db.one("select fol from player", {});
}
void add_fol(sqlite3* st, sqlite3* m, int64_t delta) {
    int64_t cap = master::global_u32(m, "item_fol_max_num", 4200000000u);  // (a) master_global item_fol_max_num
    Sql db{st};
    db.q("update player set fol = max(0, min(fol + ?, ?))", {delta, cap});
}

u32 stock_count(sqlite3* st, u32 item) {
    Sql db{st};
    return (u32)db.one("select ifnull(sum(count), 0) from stock where master_item_id = ?", {item});
}
void add_stock(sqlite3* st, sqlite3* m, u32 item, int64_t delta) {
    int64_t cap = master::global_u32(m, "item_stock_max_num", 100000000u);  // (a) master_global item_stock_max_num
    Sql mdb{m}, db{st};
    u32 type = (u32)mdb.one("select type from master_item where id = ?", {item});
    db.q("insert into stock (master_item_id, item_type, count) values (?,?,0) on conflict(master_item_id) do nothing", {item, type});
    db.q("update stock set count = max(0, min(count + ?, ?)) where master_item_id = ?", {delta, cap, item});
}

}  // namespace soa::server::wallet
