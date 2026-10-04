// The master_campaign rows that apply to a mission (api/missions/missions.h). Port code, not guest
// behaviour.
// Every rule carries its source label, (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption (docs/server-rules.md "Server missions").
#include "api/missions/missions.h"

#include "core/server.h"  // event_clock_of
#include "rules/mission_rules.h"

namespace soa::server {

using ext::body;
using ext::Row;

MissionRef find_mission(ext::Ctx& ctx, u32 type, u32 mission) { return master::find_mission(ctx.m.h, type, mission); }

std::vector<Campaign> campaigns_for(ext::Ctx& ctx, const MissionRef& ref) {
    std::vector<Campaign> running;
    // (d) campaigns are dated event content: the event calendar (server.h event_now), as the
    // client sees them (api/events/event_missions.cpp moves master_campaign by the same whole
    // years and sends CampaignInfo).
    EventTime now = event_clock_of(ctx.m.h);
    ctx.m.q("select * from master_campaign order by id", {}, [&](const Row& campaign_row) {
        // (a) the window: opened_day opened_time .. closed_day closed_time, week_id
        if (!mission_rules::campaign_active(campaign_row.s("opened_day"), campaign_row.s("opened_time"), campaign_row.s("closed_day"),
                                            campaign_row.s("closed_time"), (int)campaign_row.i("week_id"), now.v))
            return;
        // (a) master_mission_model_type (the mission type, -2 every type) and master_area_id (0 every area)
        if (!mission_rules::campaign_applies((int)campaign_row.i("master_mission_model_type"), (u32)campaign_row.i("master_area_id"), ref.type,
                                             ref.area))
            return;
        running.push_back({(u32)campaign_row.i("id"), CampaignType((u32)campaign_row.i("type_id")), campaign_row.f("magnification"),
                           (u32)campaign_row.i("lot_drop_count_add"), campaign_row.s("id_label")});
    });
    return running;
}

}  // namespace soa::server
