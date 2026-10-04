// The premium login bonus and the favor ("friendly", フレンドリープレゼント) login bonus, with
// StaminaHealByFavor. Port code, not guest behaviour. Rules: docs/server-rules.md "Premium and
// favor login bonuses"; every rule carries its source label: (a) master data, (b) client-side
// evidence, (c) outside knowledge, (d) assumption.
//
// State: `premium_pass` (one row per pass owned: the page reached, the last grant) and
// `favor_bonus_state` (one row: the last favor bonus day, its tier and lot character, the last
// stamina heal).
#include <algorithm>
#include <ctime>

#include "core/log.h"
#include "core/time.h"
#include "soaserver/ext.h"
#include "api/favor/favor.h"
#include "rules/growth_rules.h"
#include "core/modules.h"

namespace soa::server {
namespace {
using namespace ext;

// (a) content type 11 = a premium login bonus pass, content_id = its master_premium_login_bonus
// (docs/api.md "Content types").
constexpr u32 kContentPremiumPass = 11;

// The start of the current login day: (a)+(b) master_global login_bonus_reset_hour, as the
// login bonus.
int64_t login_day_start(Ctx& ctx) { return day_start(ctx.now(), (int)ctx.global_u32("login_bonus_reset_hour", 4)); }

// The response's Player map, nullptr when it has none.
Value* player_map(Value& data) {
    for (auto& entry : data.map)
        if (entry.first == "Player" && entry.second.type == Value::Map) return &entry.second;
    return nullptr;
}

// ---- premium login bonus ------------------------------------------------------------------

// Grant hook for content type 11 (core/rewards.cpp grant: a present, an item set).
// Rules: docs/server-rules.md "Premium and favor login bonuses"
//   (a) content type 11 = a premium login bonus pass, content_id = its master_premium_login_bonus
//       (the pass was sold in master_direct_item_shop, pshop_ploginbonus_001; docs/api.md "Content
//       types"). There is no purchase route in the port, so the bonus is off unless the state
//       holds a pass (d): a type-11 grant records one, from page 0.
void grant_premium_pass(Ctx& ctx, u32 pass_id, u32, Value&, Value&, Value&) {
    ctx.st.q("insert into premium_pass (id, granted_at) values (?, ?) on conflict(id) do update set granted_at = excluded.granted_at, day_index = 0",
             {pass_id, ctx.now()});
    LOGI("server", "premium login bonus pass %u granted", pass_id);
}

// Grants the next page of premium pass `pass_id` (at page `day`, named `name_message_id`) to the
// present box and records it. Returns the page granted, 0 for none.
//   (d) one page per login day, not looping (the table has no is_loop; 14 pages each)
u32 grant_premium_page(Ctx& ctx, u32 pass_id, u32 day, const std::string& name_message_id, int64_t now) {
    u32 last_idx =
        (u32)ctx.m.one("select max(order_idx) from master_premium_login_bonus_contents where master_premium_login_bonus_id = ?", {pass_id});
    u32 next = growth_rules::next_login_day(day, last_idx, false);
    if (!next) return 0;
    ctx.m.q("select * from master_premium_login_bonus_contents where master_premium_login_bonus_id = ? and order_idx = ?", {pass_id, next},
            [&](const Row& content) {
                // (a) Present_box_6 "%s %d日目" (d: the template for this bonus)
                add_present(ctx, (u32)content.i("content_type"), (u32)content.i("content_id"), (u32)content.i("num"), kPresentPremiumLogin, pass_id,
                            format_present(text(ctx.m, "Present_box_6"), text(ctx.m, name_message_id), next));
            });
    ctx.st.q("update premium_pass set day_index = ?, last_at = ? where id = ?", {next, now, pass_id});
    LOGI("server", "premium login bonus %u: day %u", pass_id, next);
    return next;
}

// The premium login bonus of each pass the player holds: a new page each login day; adds
// PremiumLoginBonus to `data` (`granted` counts the pages granted).
void premium_login_bonus(Ctx& ctx, Value& data, int& granted) {
    int64_t t = ctx.now(), today = login_day_start(ctx);
    Value list = Value::array();
    ctx.st.q("select * from premium_pass order by id", {}, [&](const Row& pass_row) {
        u32 pass_id = (u32)pass_row.i("id");
        u32 day = (u32)pass_row.i("day_index");
        int64_t last_at = pass_row.i("last_at");
        std::string name_message_id, opened_at, closed_at;
        bool known = false;
        ctx.m.q("select * from master_premium_login_bonus where id = ?", {pass_id}, [&](const Row& bonus_row) {
            known = true;
            name_message_id = bonus_row.s("name_message_id");
            opened_at = bonus_row.s("opened_at");
            closed_at = bonus_row.s("closed_at");
        });
        if (!known) return;
        bool received_now = false;
        // (a) the master row's window; (a)+(b) the daily reset (login_bonus_reset_hour, as the login
        // bonus)
        if (open_at(opened_at, closed_at, t) && last_at < today) {
            if (u32 next = grant_premium_page(ctx, pass_id, day, name_message_id, t)) {
                day = next;
                received_now = true;
                granted++;
            }
        }
        if (!day) return;
        // (b) CPremiumLoginBonusInfo's fields (Initialize); the popup lists the entries with
        // is_updated (PremiumLoginBonusModel::GetList, CPopupManager::CheckStart case 1);
        // (d) is_next false (no follow-up pass)
        Value info = Value::object();
        info["player_id"] = ctx.player_id().v;
        info["master_premium_login_bonus_id"] = pass_id;
        info["current_idx"] = day;
        info["created_at"] = ctx.fmt_time(pass_row.i("granted_at"));
        info["updated_at"] = ctx.fmt_time(received_now ? t : last_at);
        info["is_updated"] = received_now;
        info["is_next"] = false;
        list.push(info);
    });
    data["PremiumLoginBonus"] = list;
}

// ---- favor login bonus --------------------------------------------------------------------
// (a) master_favor_bonus: tiers by required_count characters at favor level >=
// required_min_master_favor_level (4), each with present_count lots and stamina_recovery_value;
// master_favor_bonus_contents: the lots by rate_weigh. (d) the tier is the open row with the
// largest required_count the player meets; once per day after the daily reset; the lots go to the
// present box with Present_favor_1 "%sのフレンドリープレゼント" naming a random qualifying
// character (lot_character_id, b: CFavorBonusContetsResultInfo's field).
// master_global favor_login_bonus_limit (5): the client never reads it (b: the key's string isn't
// in the 3.7.0 or the offline library, nor are its siblings favor_tap_bonus_limit /
// favor_event_drop_bonus_limit, so all three are server-side keys; CFavorCharacterLoginBonus::Setup
// shows one character's lot list, however long). Like those siblings (5 taps a day, 3 event-drop bonuses a day, section 8)
// it is read as a per-day cap: (d) at most favor_login_bonus_limit lots a day. With the 3.7.0
// tiers (present_count 0..3, once a day) it never binds.
struct FavorTier {
    u32 id = 0, present_count = 0, stamina = 0;  // master_favor_bonus id, present_count, stamina_recovery_value
};

// The favor tier the player meets now (id 0: none); *lot_uids = one character uid per qualifying
// same_role_id.
FavorTier favor_tier(Ctx& ctx, std::vector<u64>* lot_uids = nullptr) {
    int64_t t = ctx.now();
    std::map<SameRoleId, u64> uid_by_same_role;  // same_role_id -> a character (lot_uid: plain until S10)
    ctx.st.q("select uid, role_id from roster order by uid", {}, [&](const Row& roster_row) {
        const SameRoleId same_role_id = ctx.m.one_id<SameRoleId>("select same_role_id from master_role where id = ?", {roster_row.i("role_id")});
        if (same_role_id.v && !uid_by_same_role.count(same_role_id)) uid_by_same_role[same_role_id] = (u64)roster_row.i("uid");
    });
    FavorTier best;
    u32 best_count = 0;
    ctx.m.q("select * from master_favor_bonus order by required_count", {}, [&](const Row& tier_row) {
        if (!open_at(tier_row.s("opened_at"), tier_row.s("closed_at"), t)) return;
        u32 min_level = (u32)tier_row.i("required_min_master_favor_level"), required = (u32)tier_row.i("required_count");
        std::vector<u64> qualifying;
        for (auto& [same_role_id, uid] : uid_by_same_role)
            if (favor::level_of(ctx.st.h, ctx.m.h, t, same_role_id) >= min_level) qualifying.push_back(uid);
        if (qualifying.size() >= required && required >= best_count) {
            best = FavorTier{(u32)tier_row.i("id"), (u32)tier_row.i("present_count"), (u32)tier_row.i("stamina_recovery_value")};
            best_count = required;
            if (lot_uids) *lot_uids = qualifying;
        }
    });
    return best;
}

// One master_favor_bonus_contents row a lot can draw.
struct FavorLot {
    u32 row, type, id, num, weight;  // row: master_favor_bonus_contents.id; content type / id / num; rate_weigh
};

// The open master_favor_bonus_contents rows with a weight (a: opened_at / closed_at, rate_weigh).
std::vector<FavorLot> favor_lot_pool(Ctx& ctx, int64_t now) {
    std::vector<FavorLot> pool;
    std::string now_text = ctx.fmt_time(now);
    ctx.m.q("select * from master_favor_bonus_contents where (opened_at is null or opened_at <= ?) and (closed_at is null or closed_at > ?)",
            {now_text, now_text}, [&](const Row& content) {
                if (content.i("rate_weigh") > 0)
                    pool.push_back({(u32)content.i("id"), (u32)content.i("content_type"), (u32)content.i("content_id"), (u32)content.i("num"),
                                    (u32)content.i("rate_weigh")});
            });
    return pool;
}

// The present line of a favor lot: (a) Present_favor_1 "%sのフレンドリープレゼント" with the
// character's master_person name.
std::string favor_lot_line(Ctx& ctx, u32 role_id) {
    std::string name_message_id;
    ctx.m.q("select p.name_message_id from master_role r join master_person p on p.id = r.master_person_id where r.id = ?", {role_id},
            [&](const Row& person_row) { name_message_id = person_row.s("name_message_id"); });
    return format_present(text(ctx.m, "Present_favor_1"), text(ctx.m, name_message_id));
}

// The favor login bonus, once per login day: draws the tier's lots into the present box and adds
// FavorBonusContetsResultInfo to `data` (`granted` counts it).
void favor_login_bonus(Ctx& ctx, Value& data, int& granted) {
    int64_t today = login_day_start(ctx), t = ctx.now();
    int64_t done_at = ctx.st.one("select day_at from favor_bonus_state where id = 1", {}, 0);
    if (done_at >= today) return;
    std::vector<u64> lot_uids;
    FavorTier tier = favor_tier(ctx, &lot_uids);
    if (!tier.id || lot_uids.empty()) return;
    u64 lot_uid = lot_uids[(*ctx.rng)() % lot_uids.size()];
    u32 lot_role = (u32)ctx.st.one("select role_id from roster where uid = ?", {lot_uid});
    std::vector<FavorLot> pool = favor_lot_pool(ctx, t);
    Value drawn = Value::array();
    u64 weight_sum = 0;
    for (auto& lot : pool) weight_sum += lot.weight;
    std::string line = favor_lot_line(ctx, lot_role);
    u32 lots_today = std::min(tier.present_count, ctx.global_u32("favor_login_bonus_limit", 5));  // (a) key, (d) reading
    for (u32 k = 0; k < lots_today && weight_sum; k++) {
        u64 x = (*ctx.rng)() % weight_sum;
        for (auto& lot : pool) {
            if (x < lot.weight) {
                add_present(ctx, lot.type, lot.id, lot.num, kPresentFavorBonus, lot_role, line);
                // (b) FavorBonusContetsInfoList is an InfoBaseValueArray<u32> (its vtable's
                // DeserializeArray / Initialize; 3.7.0): the drawn master_favor_bonus_contents ids.
                // CFavorCharacterLoginBonus::Setup reads them (CParameterManager+0x8658) with
                // CMasterParameterFavorBonusContents::ParameterByIDList, and CPopupManager::CheckStart
                // opens the popup (case 6) only when the list is non-empty. Objects
                // {content_type, content_id, num}, sent until 2026-10-02, left it empty: no popup.
                drawn.push(Value(lot.row));
                break;
            }
            x -= lot.weight;
        }
    }
    ctx.st.q(
        "insert or replace into favor_bonus_state (id, day_at, bonus_id, lot_uid, healed_at) values (1, ?, ?, ?, "
        "ifnull((select healed_at from favor_bonus_state where id = 1), 0))",
        {t, tier.id, lot_uid});
    Value result = Value::object();
    result["lot_character_id"] = lot_uid;
    result["FavorBonusContetsInfoList"] = drawn;
    data["FavorBonusContetsResultInfo"] = result;
    granted++;
    LOGI("server", "favor login bonus %u: %zu present(s) from character %llu", tier.id, drawn.arr.size(), (unsigned long long)lot_uid);
}

// Player keys the favor bonus reports (a: CPlayerInfo fields favor_bonus_received_at,
// stamina_update_by_favor; d: the times of the last bonus / heal, empty when never).
void favor_player_keys(Ctx& ctx, Value& data) {
    Value* player = player_map(data);
    if (!player) return;
    int64_t bonus_at = ctx.st.one("select day_at from favor_bonus_state where id = 1", {}, 0);
    int64_t healed_at = ctx.st.one("select healed_at from favor_bonus_state where id = 1", {}, 0);
    (*player)["favor_bonus_received_at"] = bonus_at ? ctx.fmt_time(bonus_at) : std::string();
    (*player)["stamina_update_by_favor"] = healed_at ? ctx.fmt_time(healed_at) : std::string();
}

// OnPlayerLoad hook (after the login bonus and the achievements: core/modules.cpp): the premium
// and favor login bonuses on a full-state player response.
// Rules: docs/server-rules.md "Premium and favor login bonuses"
// Adds: PremiumLoginBonus (CPremiumLoginBonusInfo list), FavorBonusContetsResultInfo on the
// day's favor bonus, Player.favor_bonus_received_at / stamina_update_by_favor, and
// PresentBoxCount when a page or a favor bonus was granted.
void load_daily_bonuses(Ctx& ctx, const Request&, Value& data) {
    int granted = 0;
    premium_login_bonus(ctx, data, granted);
    favor_login_bonus(ctx, data, granted);
    favor_player_keys(ctx, data);
    if (granted) data["PresentBoxCount"] = (u32)ctx.st.one("select count(*) from presents where received_at is null", {});
}

// StaminaHealByFavor() -> StaminaHealByFavorRes                           fid 960546a3
// API: docs/api.md#staminahealbyfavor   Rules: docs/server-rules.md "Premium and favor login bonuses"
//
// The favor tier's daily stamina heal.
//   (a) the favor tier's stamina_recovery_value, added to the current stamina (d: overflow kept,
//       as the other heals); (d) once per day (after the daily reset), recorded as
//       Player.stamina_update_by_favor.
// Answers: the player state with IsHealedByFavor (a: schema) and the favor Player keys.
std::vector<u8> stamina_heal_by_favor(Ctx& ctx, const Request&) {
    ctx.tick_stamina();
    int64_t today = login_day_start(ctx), t = ctx.now();
    int64_t healed_at = ctx.st.one("select healed_at from favor_bonus_state where id = 1", {}, 0);
    FavorTier tier = favor_tier(ctx);
    bool healed = tier.id && tier.stamina && healed_at < today;
    if (healed) {
        ctx.st.q("update player set stamina = stamina + ?", {tier.stamina});
        // the regeneration clock restarts at the maximum, as the other heals (api/items/items.cpp)
        u32 level = (u32)ctx.st.one("select level from player", {});
        if ((u32)ctx.st.one("select stamina from player", {}) >= ctx.stamina_max(level)) ctx.st.q("update player set stamina_at = ?", {t});
        ctx.st.q(
            "insert into favor_bonus_state (id, day_at, healed_at) values (1, 0, ?) on conflict(id) do update set healed_at = excluded.healed_at",
            {t});
        LOGI("server", "StaminaHealByFavor: +%u (tier %u)", tier.stamina, tier.id);
    }
    Value data = ctx.base_data();
    data["IsHealedByFavor"] = healed;
    favor_player_keys(ctx, data);
    return body(data);
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_daily() {
    using namespace ext;
    add_grant(kContentPremiumPass, grant_premium_pass);
    add_player_load(load_daily_bonuses);
    add_api({"StaminaHealByFavor"}, stamina_heal_by_favor);
}

}  // namespace soa::server
