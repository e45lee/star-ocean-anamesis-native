// The favor APIs: UpdateFavorByTap and UseFavorItem (api/favor/favor.h has the rules). Port code,
// not guest behaviour; every rule carries its source label, (a) master data, (b) client-side
// evidence, (c) outside knowledge, (d) assumption (docs/server-rules.md "8. Favor").
#include "api/favor/favor.h"
#include "api/player/player_info.h"  // base_data, home_same_role, stack_item_info_list
#include "core/request_args.h"       // args::int_at

namespace soa::server {

namespace {

// UpdateFavorByTap(u32 same_role_id): the home character's same_role_id when missing.
struct UpdateFavorByTapArgs {
    bool has_same_role_id = false;
    u32 same_role_id = 0;
    static UpdateFavorByTapArgs from(const Request& req) {
        if (req.ints.empty()) return {};
        return {true, (u32)req.ints[0]};
    }
};

// UseFavorItem(u32 master_item_id, u32 count, u32 same_role_id) (docs/api.md); 0 when missing.
struct UseFavorItemArgs {
    u32 master_item_id = 0, count = 0, same_role_id = 0;
    static UseFavorItemArgs from(const Request& req) { return {(u32)args::int_at(req, 0), (u32)args::int_at(req, 1), (u32)args::int_at(req, 2)}; }
};

// (b) the favor achievements follow the favor: the `Achievement` state (ext::achievement_state;
// docs/server-rules.md "Favor achievements"). A core handler gets no ext::ensure_schema before it
// runs, so it is made sure of here.
void add_achievements(ext::Ctx& ctx, Value& data) {
    ext::ensure_schema(ctx.st);
    data["Achievement"] = ext::achievement_state(ctx);
}

// UpdateFavorByTap(u32 same_role_id) -> UpdateFavorByTapRes                fid e06ec7b3
// API: docs/api.md#updatefavorbytap   Rules: docs/server-rules.md#gains, docs/server-rules.md#responses
//
// A tap on the home character (CHome::UpdateFavorPointByTap sends it).
//   (a) master_global favor_tap_bonus_point (50) points, at most favor_tap_bonus_limit (5) taps per
//       character per day; (d) the day starts at login_bonus_reset_hour, as the other daily
//       counters; (d) a tap past the limit, or on a character without favor, changes nothing.
//   (b) the client writes UpdateFavorByTapResultInfo into its favor map and +0xb660.
// Answers: the player state (as before the tap) with UpdateFavorByTapResultInfo and Achievement.
std::vector<u8> update_favor_by_tap(ext::Ctx& ctx, const Request& req) {
    const auto args = UpdateFavorByTapArgs::from(req);
    Value data = base_data(ctx);
    favor::tap(ctx.st.h, ctx.m.h, clock_now(), args.has_same_role_id ? args.same_role_id : home_same_role(ctx), data);
    add_achievements(ctx, data);
    return ext::body(data);
}

// UseFavorItem(u32 master_item_id, u32 count, u32 same_role_id) -> UseFavorItemRes   fid 88af959e
// API: docs/api.md#usefavoritem   Rules: docs/server-rules.md#gains, docs/server-rules.md#responses
//
// Favor items on a character.
//   (a) master_favor_item_effect.favor_up_point per item; (d) target_type 0 works on any
//       character, otherwise only on the row's master_role_same_role_id; (d) the count is capped
//       by the stack held, and the stack is debited.
// Answers: the player state (as before the items) with UseFavorResultInfo, Achievement and
// StockItem ((d) the whole stack list).
std::vector<u8> use_favor_item(ext::Ctx& ctx, const Request& req) {
    const auto args = UseFavorItemArgs::from(req);
    Value data = base_data(ctx);
    favor::use_item(ctx.st.h, ctx.m.h, clock_now(), args.master_item_id, args.count, args.same_role_id, data);
    add_achievements(ctx, data);
    data["StockItem"] = stack_item_info_list(ctx);
    return ext::body(data);
}

}  // namespace

// The favor APIs (src/core/modules.cpp: the core's APIs first).
void register_favor() {
    ext::add_core_api({"UpdateFavorByTap"}, update_favor_by_tap);
    ext::add_core_api({"UseFavorItem"}, use_favor_item);
}

}  // namespace soa::server
