#pragma once
// The player's wallet (port code, not guest behaviour): coins (紋章石: free and paid), FOL and
// stack items, one copy of each rule. `st` is the state DB, `m` the master DB. ext.h's
// stock_count / add_stock / fol / add_fol are these, for the modules.
#include <sqlite3.h>

#include <cstdint>

#include "soaserver/server.h"

namespace soa::server::wallet {

// ---- coins ------------------------------------------------------------------------------------
struct Coins {
    u32 free = 0, paid = 0;  // player.free_coin, player.pay_coin
};
// How a price is paid.
struct CoinSplit {
    u32 free = 0, paid = 0;
};
// The player's coins now.
Coins coins(sqlite3* st);
// Free coins first, the rest paid: (a) master_text uimsg_buy_history_explan, the client's coin
// purchase history text, "紋章石を使用する際は無償入手分から先に消費されます" (coins are spent
// from the free ones first; its key is in the 3.7.0 library's strings). Every coin payment
// follows it (the shops, StaminaHeal, the gacha, Sphere 211's continue, deep space's quick
// return). `paid_only` (a gacha's is_pay_coin, (a)) takes paid coins only.
CoinSplit split(const Coins& have, u32 price, bool paid_only = false);
// Whether `have` pays `price` (split's paid part within the paid coins).
bool covers(const Coins& have, u32 price, bool paid_only = false);
// Takes a split's coins.
void take(sqlite3* st, const CoinSplit& s);
// The whole payment: false (nothing taken) when the coins don't cover `price`.
bool spend_coins(sqlite3* st, u32 price, bool paid_only = false);
// Adds free coins (a granted content type 4).
void add_free_coins(sqlite3* st, u32 n);
// Adds paid coins (a coin-shop purchase: api/shop/coins.cpp, docs/server-rules.md#paid-currency).
void add_paid_coins(sqlite3* st, u32 n);

// ---- FOL --------------------------------------------------------------------------------------
u32 fol(sqlite3* st);
// Adds (or with a negative delta, takes) FOL: never below 0, (a) capped at master_global item_fol_max_num.
void add_fol(sqlite3* st, sqlite3* m, int64_t delta);

// ---- stack items --------------------------------------------------------------------------------
// Owned stack items of a master item.
u32 stock_count(sqlite3* st, u32 item);
// Adds (or takes) stack items: never below 0, (a) capped at master_global item_stock_max_num.
void add_stock(sqlite3* st, sqlite3* m, u32 item, int64_t delta);

}  // namespace soa::server::wallet
