// The player state the client receives (api/player/player_info.h). Port code, not guest
// behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption (docs/server-rules.md "Player load").
#include "api/player/player_info.h"

#include <algorithm>
#include <map>

#include "api/entry/entry.h"  // add_cdn_paths, time_only
#include "api/favor/favor.h"  // favor levels and the favor state of the player load
#include "api/items/items.h"  // item_equipped
#include "api/player/party_set.h"  // party_set_info
#include "api/player/roster.h"  // roster_info
#include "core/log.h"
#include "core/server.h"  // has_player
#include "soaserver/config.h"

namespace soa::server {

using ext::body;
using ext::Row;

// (a) stamina regenerates one point per master_global stamina_heal_time seconds, up to
// master_player_level.stamina.
void tick_stamina(ext::Ctx& ctx) {
    ctx.st.q("select level, stamina, stamina_at from player", {}, [&](const Row& player_row) {
        u32 max = ctx.stamina_max((u32)player_row.i("level"));
        int64_t now = clock_now(), at = player_row.i("stamina_at");
        auto [stamina, carry] =
            rules::regen_stamina((u32)player_row.i("stamina"), max, (u64)std::max<int64_t>(0, now - at), ctx.global_u32("stamina_heal_time", 180));
        ctx.st.q("update player set stamina = ?, stamina_at = ?", {stamina, stamina >= max ? now : now - (int64_t)carry});
    });
}

namespace {

// Player.support_pc_id: the character the player lends (レンタル), as a uid.
//   (b) CRentalBonus::Setup builds its card with tCharaData::Initialize(CParameterManager+0xba8 =
//       Player.support_pc_id): UpdateSupport's owned character (player.support_uid, api/social/rental.cpp).
//   (d) Unset or no longer owned: the highest-level character (ties by uid), the first of the
//       rental list's lenders (api/social/rental.cpp).
u64 support_uid(ext::Ctx& ctx, const Row& player_row) {
    u64 uid = (u64)player_row.i("support_uid");  // NULL: unset (0)
    if (!uid || !ctx.st.one("select count(*) from roster where uid = ?", {uid}))
        uid = (u64)ctx.st.one("select uid from roster order by level desc, uid limit 1", {}, 0);
    return uid;
}

// The stock caps of Player (player_info, step 2).
void add_stock_caps(ext::Ctx& ctx, Value& player) {
    player["item_stock"] = ctx.global_u32("item_stock_max", 500);  // (a) master_global item_stock_max
    player["storage_stock"] = 500u;                                // (d)
    player["gear_stock"] = ctx.global_u32("gear_stock_max", 500);  // (a) master_global gear_stock_max
    // (b) CPlayerInfo gear_num (+0x978, CParameterUtility::NowGearItemCount: the ギア所持
    // count of the gear screens) = the free gears (api/items/gear.cpp's table; d: attached gears
    // don't count). Before PLAN-schema S1 it was sent only once the module's table existed, so a
    // new state's first player load lacked it (but on soa-server, whose bridge made the tables).
    player["gear_num"] = (u32)ctx.st.one("select count(*) from gear_items where item_uid = 0", {});
    player["follow_max"] = ctx.global_u32("follow_default", 30);  // (a) master_global follow_default
}

// The state other domains keep for Player, in the player row (player_info, step 4; in meta until
// PLAN-schema S3).
void add_domain_state(const Row& player_row, Value& player) {
    // Entry flow: tutorial progress, UI tutorials seen, accepted terms version (b: the client reads
    // them back; docs/server-rules.md "Entry flow").
    player["tutorial_status"] = (u32)player_row.i("tutorial_status");
    player["view_status"] = (u64)player_row.i("view_status");  // the u64 word's int64 bits (all ones: -1)
    player["view_status2"] = (u64)player_row.i("view_status2");
    player["kiyaku_version"] = player_row.s("kiyaku_version");
    // Deep space (api/deepspace/deepspace.cpp): quick returns used today, which the client's
    // quick-return dialog prices the next one by (CDeepSpaceQuickReturnDialog::Open).
    player["time_saving_use_count"] = (u32)player_row.i("time_saving_count");
    // Titles (api/player/titles.cpp): the selected master_title id, which the status bar's plate
    // shows (b: CCommon::UpdateMyStatus -> CParameterUtility::SetPlayerTitle, +0xed8).
    player["title"] = (u32)player_row.i("title_id");  // NULL: none (0)
}

}  // namespace

Value player_info(ext::Ctx& ctx) {
    tick_stamina(ctx);
    Value player = Value::object();
    ctx.st.q("select * from player", {}, [&](const Row& player_row) {
        // 1. the player's row
        u32 level = (u32)player_row.i("level");
        player["id"] = (u32)player_row.i("id");
        player["name"] = player_row.s("name");
        player["search_id"] = player_row.s("search_id");
        player["level"] = level;
        player["exp"] = (u32)player_row.i("exp");
        player["fol"] = (u32)player_row.i("fol");
        player["stamina"] = (u32)player_row.i("stamina");
        player["stamina_max"] = ctx.stamina_max(level);  // (a) master_player_level.stamina
        player["stamina_update"] = format_time(player_row.i("stamina_at"));
        // The home character's uid (b): 3.7.0's CHome::GetAdjutant (@01aebe38) takes
        // CParameterManager+0x8698 (FavorBonusContetsResultInfo.lot_character_id, also a uid:
        // CFavorCharacterLoginBonus::Setup builds its card from it) when set, else +0xd08
        // (Player.home_pc_id), and finds it among the owned characters by CPersonInfo uid; with
        // no match it shows party 1's first member. (The client before the rebase read a role
        // id here; docs/server-rules.md "Home character".)
        player["home_pc_id"] = (u64)player_row.i("home_uid");
        player["party_id"] = (u32)player_row.i("party_id");
        player["support_pc_id"] = support_uid(ctx, player_row);
        // 2. the stock caps
        add_stock_caps(ctx, player);
        // 3. the times; (d) updated_at is the answer's time
        player["created_at"] = format_time(player_row.i("created_at"));
        player["updated_at"] = format_time(clock_now());
        player["last_login_at"] = format_time(player_row.i("last_login_at"));
        // (d) the 3D home: Home3DAnd2DSwitching (3.7.0's CHome::Progress) has no handler, so the
        // flag never changes
        player["is_3d_home"] = true;
        // 4. the state other domains keep in the player row
        add_domain_state(player_row, player);
    });
    return player;
}

Value wallet_info(ext::Ctx& ctx) {
    Value wallet = Value::object();
    ctx.st.q("select free_coin, pay_coin from player", {}, [&](const Row& player_row) {
        wallet["free_coin"] = (u32)player_row.i("free_coin");
        wallet["pay_coin"] = (u32)player_row.i("pay_coin");
        // (d) the total is free + paid, and android_coin (the paid coins bought on Android) is
        // every paid coin: the local server has no other store
        wallet["total_coin"] = (u32)(player_row.i("free_coin") + player_row.i("pay_coin"));
        wallet["android_coin"] = (u32)player_row.i("pay_coin");
    });
    return wallet;
}

u32 player_id(ext::Ctx& ctx) { return (u32)ctx.st.one("select id from player", {}); }

// StockItem: every stack item held (CStackItemInfo, one per master item with a count).
Value stack_item_info_list(ext::Ctx& ctx) {
    Value list = Value::array();
    u32 pid = player_id(ctx);
    ctx.st.q("select * from stock where count > 0 order by master_item_id", {}, [&](const Row& stock_row) {
        Value info = Value::object();
        info["id"] = (u32)stock_row.i("master_item_id");
        info["player_id"] = pid;
        info["master_item_id"] = (u32)stock_row.i("master_item_id");
        info["item_type"] = (u32)stock_row.i("item_type");
        info["use_count"] = (u32)stock_row.i("count");
        // (b) CStackItemInfo's fields (its Initialize): master_item_id, num, item_type,
        // sort_name_idx, is_new, use_count, player_id; the count held is `num` (the shops
        // and the exchange show it as 所持数)
        info["num"] = (u32)stock_row.i("count");
        list.push(info);
    });
    return list;
}

// Item: every owned weapon and accessory (CItemInfo), plus the modules' keys (ext::ItemExtra:
// a weapon's AttachedGearInfoList, api/items/gear.cpp).
Value item_info_list(ext::Ctx& ctx, const std::string& where) {
    Value list = Value::array();
    u32 pid = player_id(ctx);
    ext::Sql state{ctx.st.h}, master{ctx.m.h};
    ctx.st.q("select * from items " + where + " order by uid", {}, [&](const Row& item_row) {
        Value info = Value::object();
        info["id"] = (u64)item_row.i("uid");
        info["player_id"] = pid;
        info["master_item_id"] = (u32)item_row.i("master_item_id");
        info["item_type"] = (u32)item_row.i("item_type");
        info["boosted_point"] = (u32)item_row.i("exp");
        info["limit_break_count"] = (u32)item_row.i("limit_break");
        // (b) CItemInfo also has level, is_equip, is_lock, num, is_new (its Initialize); the
        // compose level and the lock flag are api/items/'s
        info["level"] = (u32)std::max<int64_t>(1, item_row.i("level"));
        info["is_lock"] = item_row.i("locked") != 0;
        info["is_equip"] = item_equipped(ctx, (u64)item_row.i("uid"));
        info["num"] = 1u;
        ext::item_extra(state, master, (u64)item_row.i("uid"), info);  // extension modules' keys (ext::ItemExtra, e.g. attached gear)
        list.push(info);
    });
    return list;
}

Value base_data(ext::Ctx& ctx) {
    Value data = Value::object();
    // (b) data.Time: the server's clock. CServerTime::UpdateServerTimeOffset (run by every
    // DeserializeToInfo) parses it and keeps its difference from the device clock, so the
    // client's NowTime follows the server's; the client's stamina (StaminaUtility::NowStamina
    // = stamina + (NowTime - str2time_t(stamina_update)) / heal time, up to the max) and the
    // banner windows are computed against it.
    data["Time"] = format_time(clock_now());
    data["Player"] = player_info(ctx);
    data["Wallet"] = wallet_info(ctx);
    return data;
}

std::vector<u8> full_player_state(ext::Ctx& ctx, const Request& req, CdnKeys cdn) {
    ctx.st.q("update player set last_login_at = ?", {clock_now()});
    Value data = base_data(ctx);
    if (cdn != CdnKeys::kNone) add_cdn_paths(ctx, data, cdn == CdnKeys::kAppVersionOnly);
    data["Character"] = roster_info(ctx);
    data["PartySet"] = party_set_info(ctx);
    data["StockItem"] = stack_item_info_list(ctx);
    data["Item"] = item_info_list(ctx);
    favor::add_player_state(ctx.st.h, ctx.m.h, clock_now(), home_same_role(ctx), data);
    ext::player_load(ctx, req, data);  // the modules' keys (OnPlayerLoad: login bonus, achievements, shop counters, ...)
    // (b) data.PresentBoxCount on every player load: the home / other-menu present badge. The
    // login-bonus module sends it only when it grants a page.
    if (!data.find("PresentBoxCount")) data["PresentBoxCount"] = (u32)ctx.st.one("select count(*) from presents where received_at is null", {});
    return body(data);
}

// The home character's master_role.same_role_id (0 when none).
u32 home_same_role(ext::Ctx& ctx) {
    u32 role_id = (u32)ctx.st.one("select r.role_id from player p join roster r on r.uid = p.home_uid", {});
    return role_id ? (u32)ctx.m.one("select same_role_id from master_role where id = ?", {role_id}) : 0u;
}

namespace {

// GetPlayer() / NoLoginStart(search id) -> GetPlayerRes / NoLoginStartRes  fid 9a056905 / 95804837
// API: docs/api.md#getplayer, docs/api.md#nologinstart
// Rules: docs/server-rules.md "Player load", "Session and login"
//
// The whole player state: 3.7.0's title sends NoLoginStart and then Login; GetPlayer refreshes it
// (e.g. CPresentbox::Progress after receiving presents).
//   (d) Without a player (the new-player flow): data.Time only.
// Answers: the whole player state without the CDN keys (full_player_state), or data.Time.
std::vector<u8> get_player(ext::Ctx& ctx, const Request& req) { return has_player(ctx) ? full_player_state(ctx, req) : time_only(ctx); }

}  // namespace

// The player load's APIs (src/core/modules.cpp: the core's APIs first).
void register_player() { ext::add_core_api({"GetPlayer", "NoLoginStart"}, get_player); }

}  // namespace soa::server
