// ext::Ctx: the services every handler gets (soaserver/ext.h). Port code, not guest behaviour.
// Plain functions over the request's DBs and RequestContext, so "go to definition" lands here; the
// server object makes the Ctx (core/server.cpp Server::make_ctx).
#include "api/missions/missions.h"   // start_mission, mission_end, play_state
#include "api/player/player_info.h"  // the player state builders
#include "api/player/roster.h"       // roster_info
#include "core/request_context.h"
#include "core/rewards.h"  // grant
#include "core/server.h"   // event_clock_of
#include "core/time.h"     // parse_time
#include "master/master.h"
#include "soaserver/ext.h"

namespace soa::server {

bool ext::Ctx::live() const { return request->live; }
ServerTime ext::Ctx::now() { return test.now ? ServerTime(test.now()) : clock_now(); }
EventTime ext::Ctx::event_now() { return test.event_now ? EventTime(test.event_now()) : event_clock_of(m.h); }
std::string ext::Ctx::fmt_time(int64_t t) { return format_time(t); }
int64_t ext::Ctx::parse_time(const std::string& s) { return server::parse_time(s); }
Value ext::Ctx::base_data() { return server::base_data(*this); }
Value ext::Ctx::roster() { return roster_info(*this); }
Value ext::Ctx::stock() { return stack_item_info_list(*this); }
Value ext::Ctx::items() { return item_info_list(*this); }
PlayerId ext::Ctx::player_id() { return server::player_id(*this); }
std::vector<u32> ext::Ctx::role_next(RoleId role) { return master::role_next(m.h, role); }
u32 ext::Ctx::role_level_cap(RoleId role) { return master::role_level_cap(m.h, role); }
u32 ext::Ctx::stamina_max(u32 level) { return master::stamina_max(m.h, level); }
void ext::Ctx::tick_stamina() { server::tick_stamina(*this); }
u32 ext::Ctx::global_u32(const char* key, u32 dflt) { return master::global_u32(m.h, key, dflt); }
std::vector<u32> ext::Ctx::player_next() { return master::player_next(m.h); }
u32 ext::Ctx::player_level_max() { return master::player_level_max(m.h); }
void ext::Ctx::grant(u32 type, u32 id, u32 num, Value& items, Value& stocks, Value& chars) {
    server::grant(*this, Drop{type, id, num, 0}, items, stocks, chars);
}
// A refusal inside the core mission is the module's to report: Nil, the core's refusal stays set.
Value ext::Ctx::core_mission(const Request& r, const MissionOverride* ov) {
    u32 outer = request->refusal;
    request->refusal = 0;
    std::vector<u8> b = r.method == "MissionStart" ? start_mission(*this, r, ov, false)
                        : r.method == "MissionEnd" ? mission_end(*this, r)
                                                   : play_state(*this, r);
    if (b.empty() || request->refusal) return Value();
    request->refusal = outer;
    Value v = mp_decode(b);
    const Value* d = v.find("data");
    return d ? *d : Value();
}
void ext::Ctx::set_error(u32 code) {
    request->refusal = code;
    if (test.on_refuse) test.on_refuse(code);
}

}  // namespace soa::server
