#pragma once
// Passes (subscriptions) as player state: the module's functions its tests and the shop's README
// name (api/shop/subscription.cpp). The other domains use ext::subscription_active /
// ext::subscription_state (soaserver/ext.h). docs/server-rules.md "Passes".
#include "soaserver/ext.h"

namespace soa::server::subscription {

// (a) content type 20: a pass (docs/api.md "Content types").
constexpr u32 kContentTypePass = 20;

// Grants `days` of the master_subscription_plan `plan` at `t`: (d) extends a running plan, else
// runs from `t`.
void grant_plan(ext::Ctx& ctx, u32 plan, u32 days, int64_t t);
// --galaxy-pass: grants the Galaxy Pass when it isn't running at `t`.
void keep_galaxy_pass(ext::Ctx& ctx, int64_t t);
// Subscription: {type id: SubscriptionInfo} of the recorded plans.
Value subscription_info(ext::Ctx& ctx);
// SubscriptionPlan: {plan id: SubscriptionPlanInfo}.
Value subscription_plan_info(ext::Ctx& ctx);

}  // namespace soa::server::subscription
