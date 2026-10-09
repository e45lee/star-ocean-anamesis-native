// Rewards: granting a content and adding a character (core/rewards.h). Port code, not guest
// behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption (docs/api.md "Content types"; docs/server-rules.md#gacha-rules).
#include "core/rewards.h"

#include <algorithm>

#include "api/player/player_info.h"  // player_id
#include "core/log.h"
#include "core/server.h"  // next_uid
#include "core/wallet.h"

namespace soa::server {

using ext::Row;

// Grants a content (drop, present, gacha). Content types (a, by example from the master rows
// using them; docs/api.md "Content types"): 1 unique item (weapon / accessory), 2 character,
// 3 FOL, 4 free coin, 5..10 and 16 stack items (materials, tickets, event coins, heal items,
// favor items). The other types are the modules' (ext::add_grant: gear 15, gear lottery 98, the
// premium pass 11, stamps 12, titles 13, deco 17 / 18, passes 20); (d) a type nobody grants
// (item sets 99 outside grant_with_item_sets) is logged and not granted.
void grant(ext::Ctx& ctx, const Grant& what, Granted& granted, storage::EquipSource source) {
    const PlayerId pid = player_id(ctx);
    if (what.type == ContentType::kItem) {
        for (u32 k = 0; k < what.num; k++) {
            // (b) a unit the inventory has no room for goes to the overflow box
            // (storage::to_one_time_storage, docs/server-rules.md#storage)
            if (storage::to_one_time_storage(ctx, source)) storage::add_one_time(ctx, MasterItemId(what.id), 1);
            else granted.items.push(new_item(ctx, MasterItemId(what.id), ItemSource{what.type, what.drop_type}));
        }
    } else if (what.type == ContentType::kCharacter) {
        Added a = add_character(ctx, RoleId(what.id));
        if (!a.dup && a.uid.v) {
            Value e = Value::object();
            e["id"] = a.uid.v;
            e["master_role_id"] = what.id;
            e["drop_type"] = what.drop_type;
            e["is_new"] = 1u;  // the NEW badge until ClearNewCharacter (docs/server-rules.md#new-badges)
            granted.characters.push(e);
        }
    } else if (what.type == ContentType::kFol) {  // (a) master_global item_fol_max_num caps FOL
        wallet::add_fol(ctx.st.h, ctx.m.h, what.num);
    } else if (what.type == ContentType::kFreeCoin) {
        wallet::add_free_coins(ctx.st.h, what.num);
    } else if (!is_stack_item(what.type)) {
        // content types an extension module grants (ext::Grant, e.g. gear 15 / 98 in api/items/gear.cpp)
        if (const ext::GrantFn* g = ext::find_grant(what.type)) {
            (*g)(ctx, what, granted);
            return;
        }
        LOGW("server", "content type %u (id %u x%u) not granted yet", to_u32(what.type), what.id, what.num);
    } else {
        u32 itype = (u32)ctx.m.one("select type from master_item where id = ?", {what.id});
        ext::add_stock(ctx, what.id, what.num);  // (a) capped at master_global item_stock_max_num
        Value e = Value::object();
        e["id"] = what.id;
        e["player_id"] = pid.v;
        e["master_item_id"] = what.id;
        e["item_type"] = itype;
        e["use_count"] = (u32)ctx.st.one("select count from stock where master_item_id = ?", {what.id});
        e["num"] = what.num;
        e["drop_type"] = what.drop_type;
        granted.stocks.push(e);
    }
}

Value new_item(ext::Ctx& ctx, MasterItemId id, std::optional<ItemSource> source) {
    const ItemUid uid = next_item_uid(ctx);
    u32 itype = (u32)ctx.m.one("select type from master_item where id = ?", {id});
    ctx.st.q("insert into items (uid, master_item_id, item_type, created_at) values (?,?,?,?)", {uid, id, itype, ctx.now()});
    Value e = Value::object();
    e["id"] = uid.v;
    e["player_id"] = player_id(ctx).v;
    e["master_item_id"] = id.v;
    e["item_type"] = itype;
    if (source) {
        e["content_type"] = to_u32(source->content_type);
        e["drop_type"] = source->drop_type;
    }
    e["boosted_point"] = 0u;
    e["limit_break_count"] = 0u;
    return e;
}

// A new character, or a duplicate: (b) a drawn role is a duplicate when the player owns a
// role of the same role_category_id (CLimitOverCharacter matches by
// CUIUtility::GetCharaCategoryId_FromCharaRoleId). A duplicate raises the owned character's
// limit break by one up to its maximum, (b) the number of master_rank rows of its rank
// minus one (CParameterUtility::CalcMasterRole2LimitBreakMax); beyond it, (a)+(c) the
// master_role_duplication_item material (by the role's limitbreak_id, else its rank) goes to
// the stack items.
Added add_character(ext::Ctx& ctx, RoleId role) {
    Added a;
    int64_t have = -1;
    ctx.st.q("select uid, role_id, limit_break from roster where role_id = ? limit 1", {role}, [&](const Row& r) {
        have = r.i("uid");
        a.owned_role = (u32)r.i("role_id");
        a.lb_before = (u32)r.i("limit_break");
    });
    if (have < 0) {
        // (master_role has no NULL role_category_id in 3.7.0, so the NULL-as-0 reads below and
        // plain one() agree; kept by name, docs/history/PLAN-readability.md 1.5)
        int64_t cat = one_null_as_zero(ctx.m, "select role_category_id from master_role where id = ?", {role}, -1);
        std::vector<std::pair<u64, u32>> owned;
        ctx.st.q("select uid, role_id, limit_break from roster order by uid", {}, [&](const Row& r) {
            if (have < 0 && one_null_as_zero(ctx.m, "select role_category_id from master_role where id = ?", {r.i("role_id")}, -2) == cat) {
                have = r.i("uid");
                a.owned_role = (u32)r.i("role_id");
                a.lb_before = (u32)r.i("limit_break");
            }
        });
    }
    if (have < 0) {
        a.uid = next_character_uid(ctx);
        ctx.st.q("insert into roster (uid, role_id, level, exp, created_at) values (?,?,1,0,?)", {a.uid, role, ctx.now()});
        return a;
    }
    a.dup = true;
    a.uid = CharacterUid((u64)have);
    int64_t rank = ctx.m.one("select rank from master_role where id = ?", {a.owned_role});
    u32 max = (u32)std::max<int64_t>(0, ctx.m.one("select count(*) from master_rank where rank = ?", {rank}) - 1);
    if (a.lb_before < max) {
        a.lb_after = a.lb_before + 1;
        ctx.st.q("update roster set limit_break = ? where uid = ?", {a.lb_after, have});
    } else {
        a.lb_after = a.lb_before;
        int64_t lbid = ctx.m.one("select limitbreak_id from master_role where id = ?", {role});
        ctx.m.q(
            "select master_item_id, num from master_role_duplication_item where limitbreak_id = ? "
            "union all select master_item_id, num from master_role_duplication_item where limitbreak_id is null and rank = ? limit 1",
            {lbid, rank}, [&](const Row& r) {
                if (a.item) return;
                a.item = (u32)r.i("master_item_id");
                a.item_num = (u32)r.i("num");
            });
        if (a.item) {
            ext::add_stock(ctx, a.item, a.item_num);  // (a) capped at master_global item_stock_max_num
        }
    }
    return a;
}

namespace {
// (d) How deep item sets may nest: in 3.7.0's master_item_set a set holds at most a set that
// holds a set (184028475 -> 2482068609 -> 1244723512); a set that (directly or not) contains
// itself would recurse for ever, so beyond this depth the set is logged and not granted.
constexpr int kMaxItemSetDepth = 8;

void grant_item_set_level(ext::Ctx& ctx, const Grant& what, Granted& granted, u32* free_coins, int depth) {
    if (what.type == ContentType::kItemSet) {
        if (depth >= kMaxItemSetDepth) {
            LOGW("server", "item set %u nested deeper than %d sets (a set containing itself?): not granted", what.id, kMaxItemSetDepth);
            return;
        }
        ctx.m.q("select content_type, content_id, num from master_item_set where item_set_id = ? order by order_id", {what.id},
                [&](const Row& set_row) {
                    const Grant member{as_content_type(set_row.i("content_type")), (u32)set_row.i("content_id"), (u32)set_row.i("num") * what.num, 0};
                    grant_item_set_level(ctx, member, granted, free_coins, depth + 1);
                });
        return;
    }
    if (what.type == ContentType::kFreeCoin && free_coins) *free_coins += what.num;
    ctx.grant(Grant{what.type, what.id, what.num, 0}, granted);
}
}  // namespace

// (a) content type 99 is a master_item_set id (docs/api.md "Content types"): its rows, in
// order_id order, each `num` times the set's count. Shared by the shop, the exchange, the event
// ranking rewards (R18: their copies were one function each) and Sphere 211's ranking reward.
void grant_with_item_sets(ext::Ctx& ctx, const Grant& what, Granted& granted, u32* free_coins) {
    grant_item_set_level(ctx, what, granted, free_coins, 0);
}

}  // namespace soa::server
