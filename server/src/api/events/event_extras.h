#pragma once
// The event extras' shared declarations (api/events/): the favor event drop's two halves, run in one
// fixed order by world_boss.cpp's MissionResultExtra (the favor drops first, so the world boss
// counts their target items, then the time bonuses, then the world boss).
#include "soaserver/ext.h"

namespace soa::server::event_extras {

// (b) Common::MissionType 1: an event mission (ext::MissionInfo.type; master_event_mission).
constexpr u32 kMissionTypeEvent = 1;

// MissionStart: decides the favor event drop bonus (MissionParameter.is_event_drop_by_favor).
void favor_start(ext::Ctx& ctx, const ext::MissionInfo& mission, Value& param, Value& data);
// MissionEnd (win): the favor bonus lots (drop_type 4), spent characters stamped.
void favor_result(ext::Ctx& ctx, const ext::MissionInfo& mission, Value& data);

}  // namespace soa::server::event_extras
