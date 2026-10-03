// Passes / subscriptions (ギャラクシーパス and the other content-type-20 products) as player state
// (api/shop/subscription.h). Port code, not guest behaviour. Rules in docs/server-rules.md "Deep
// space" ("Subscription ships") and "Passes (subscriptions)"; labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// What the client reads (b):
//   Subscription      {type: SubscriptionInfo} master_subscription_type_id, opened_at, closed_at.
//                     Kept at CParameterManager+0x9600, a map keyed by the type;
//                     CParameterUtility::EnableSubscriptionType(type) is true while the entry's
//                     closed_at (SubscriptionInfo +0xd0, the third field) is after the client's
//                     clock (CTimeUtility::CompTime(NowTime, closed_at)). Read for type 3 by the
//                     deep space ship count (CUIUtility::GetSubscriptionShipCount,
//                     CDeepSpace::SetupAfterConnection), type 2 by CItemStorage::Progress, and by
//                     tPartyData::Initialize / CMultiPlay3.
//   SubscriptionPlan  {plan id: SubscriptionPlanInfo} master_subscription_plan_id, updated_at,
//                     opened_at, closed_at.
// A number map replaces the client's whole map, so both are sent whole.
#include "api/shop/subscription.h"

#include <algorithm>
#include <string>
#include <vector>

#include "core/log.h"
#include "soaserver/config.h"
#include "soaserver/ext.h"
#include "core/modules.h"

namespace soa::server::subscription {

using ext::Ctx;
using ext::Row;

namespace {

// (d) the days of a pass whose master row has no count: the Galaxy Pass's 30.
constexpr u32 kDefaultPassDays = 30;

}  // namespace

// (a) content type 20 = a pass (docs/api.md "Content types"): master_direct_item_shop /
// master_item_set rows of type 20 name a master_subscription_plan (content_id) with num 30 for the
// Galaxy Pass (pshop_galaxypass_001) and 14 for the character passes; (d) num is the days the pass
// runs. (d) A grant while the plan still runs extends it by num days; otherwise it runs from now.
void grant_plan(Ctx& ctx, u32 plan, u32 days, int64_t t) {
    if (!ctx.m.one("select count(*) from master_subscription_plan where id = ?", {plan})) {
        LOGW("server", "pass %u: no master_subscription_plan row, not granted", plan);
        return;
    }
    int64_t closed = ctx.st.one("select ifnull(max(closed_at), 0) from subscription where plan_id = ?", {plan});
    int64_t from = closed > t ? closed : t;
    int64_t opened = closed > t ? ctx.st.one("select opened_at from subscription where plan_id = ?", {plan}) : t;
    ctx.st.q(
        "insert into subscription (plan_id, opened_at, closed_at, updated_at) values (?, ?, ?, ?)"
        " on conflict(plan_id) do update set opened_at = excluded.opened_at, closed_at = excluded.closed_at, "
        "updated_at = excluded.updated_at",
        {plan, opened, from + (int64_t)days * 86400, t});
    LOGI("server", "pass %u granted: %u days, until %s", plan, days, ctx.fmt_time(from + (int64_t)days * 86400).c_str());
}

namespace {

// Grant hook for content type 20 (a pass; the core can't grant it): the plan `id` for `num` days.
// Rules: docs/server-rules.md "Passes"
//   (a) num the days (30 for the Galaxy Pass, 14 for the character passes); (d) 30 when 0.
// Adds nothing to the grant's lists (the pass reaches the client through Subscription).
void grant_subscription_plan(Ctx& ctx, u32 id, u32 num, Value&, Value&, Value&) { grant_plan(ctx, id, num ? num : kDefaultPassDays, ctx.now()); }

}  // namespace

// --galaxy-pass (port option, (d) the user's choice): the Galaxy Pass as if bought and
// auto-renewed ((b) the feature is "auto_renewable_subscriptions", CParameterUtility::
// IsOpenSubscriptions). The pass is the master_direct_item_shop product of type 20 whose plan
// has is_galaxypass (a: pshop_galaxypass_001, 30 days); it is granted again whenever a full player
// load finds it expired (d).
void keep_galaxy_pass(Ctx& ctx, int64_t t) {
    u32 plan = 0, days = 0;
    ctx.m.q(
        "select s.content_id, s.num from master_direct_item_shop s join master_subscription_plan p on p.id = s.content_id "
        "where s.content_type = 20 and p.is_galaxypass = 1 order by s.order_id, s.id limit 1",
        {}, [&](const Row& product_row) {
            plan = (u32)product_row.i("content_id");
            days = (u32)product_row.i("num");
        });
    if (!plan) return;
    if (ctx.st.one("select count(*) from subscription where plan_id = ? and closed_at > ?", {plan, t})) return;
    grant_plan(ctx, plan, days ? days : kDefaultPassDays, t);
}

Value subscription_info(Ctx& ctx) {
    // (a) master_subscription: the types (type_id) a plan (plan_id) gives. (d) when two plans give
    // one type, the later closed_at is sent.
    struct Window {
        int64_t opened = 0, closed = 0;
    };
    std::vector<std::pair<u32, Window>> types;
    ctx.st.q("select * from subscription order by plan_id", {}, [&](const Row& plan_row) {
        ctx.m.q("select type_id from master_subscription where plan_id = ? order by order_id, id", {plan_row.i("plan_id")}, [&](const Row& type_row) {
            u32 type = (u32)type_row.i("type_id");
            auto it = std::find_if(types.begin(), types.end(), [&](auto& known) { return known.first == type; });
            if (it == types.end()) types.push_back({type, {plan_row.i("opened_at"), plan_row.i("closed_at")}});
            else if (plan_row.i("closed_at") > it->second.closed) it->second = {plan_row.i("opened_at"), plan_row.i("closed_at")};
        });
    });
    Value info = Value::object();
    for (auto& [type, window] : types) {
        Value entry = Value::object();
        entry["master_subscription_type_id"] = type;
        entry["opened_at"] = ctx.fmt_time(window.opened);
        entry["closed_at"] = ctx.fmt_time(window.closed);
        info[std::to_string(type)] = entry;
    }
    return info;
}
Value subscription_plan_info(Ctx& ctx) {
    Value info = Value::object();
    ctx.st.q("select * from subscription order by plan_id", {}, [&](const Row& plan_row) {
        Value entry = Value::object();
        entry["master_subscription_plan_id"] = (u32)plan_row.i("plan_id");
        entry["updated_at"] = ctx.fmt_time(plan_row.i("updated_at"));
        entry["opened_at"] = ctx.fmt_time(plan_row.i("opened_at"));
        entry["closed_at"] = ctx.fmt_time(plan_row.i("closed_at"));
        info[std::to_string(plan_row.i("plan_id"))] = entry;
    });
    return info;
}

namespace {

// OnPlayerLoad hook (Login, GetPlayer, NoLoginStart's full player state).
// Rules: docs/server-rules.md "Passes"
//   (b) the keys and fields (EnableSubscriptionType reads Subscription); (d) which responses.
//   (d) --galaxy-pass: the Galaxy Pass granted first when it isn't running (keep_galaxy_pass).
// Adds: Subscription, SubscriptionPlan.
void load_subscriptions(Ctx& ctx, const Request&, Value& data) {
    if (config().galaxy_pass) keep_galaxy_pass(ctx, ctx.now());
    data["Subscription"] = subscription_info(ctx);
    data["SubscriptionPlan"] = subscription_plan_info(ctx);
}

}  // namespace

}  // namespace soa::server::subscription

namespace soa::server {

// (b) EnableSubscriptionType: a type is on while its closed_at is after the clock.
bool ext::subscription_active(Ctx& ctx, u32 type, int64_t t) {
    bool on = false;
    ctx.st.q("select plan_id, closed_at from subscription where closed_at > ?", {t}, [&](const Row& plan_row) {
        if (ctx.m.one("select count(*) from master_subscription where plan_id = ? and type_id = ?", {plan_row.i("plan_id"), type})) on = true;
    });
    return on;
}
Value ext::subscription_state(Ctx& ctx) { return subscription::subscription_info(ctx); }

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_subscription() {
    using namespace ext;
    add_grant(subscription::kContentTypePass, subscription::grant_subscription_plan);
    add_player_load(subscription::load_subscriptions);
}

}  // namespace soa::server
