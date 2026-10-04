// The story campaign's hooks around each request (soaserver/api_campaign.h): the progress from
// MissionStart / MissionEnd / MissionTalk / EndMissionTalk, and the campaign's keys spliced into the
// responses. server::answer (core/lifecycle.cpp) calls them for both hosts. Port code (restore
// run), not guest behaviour; the master data, the progress and the lists are master_data.cpp,
// progress.cpp and lists.cpp (api/campaign/campaign.h).
//
// Rule sources: (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
// docs/server-rules.md#campaign lists the same rules.
#include <cinttypes>
#include <mutex>
#include <string>
#include <vector>

#include "api/campaign/campaign.h"
#include "core/log.h"
#include "soaserver/config.h"

namespace soa::server::campaign {

// ---- the response splice ----------------------------------------------------------------------
Value merge_maps(const Value& base, const Value& over) {
    if (base.type != Value::Map || over.type != Value::Map) return over;
    Value out = Value::object();
    for (auto& [key, value] : base.map)
        if (!over.find(key)) out.map.emplace_back(key, value);
    for (auto& entry : over.map) out.map.push_back(entry);
    return out;
}

// Rewrites root = {..., "data": {entries...}, ...} so that data holds `add`: the entries whose keys
// `add` doesn't name keep their order, then `add`'s in order. An existing key of the same name is
// replaced, except that a map-valued entry is merged into an existing map (e.g. the server core's
// Player keeps its fields). False if the root isn't of that shape.
bool splice_data(Value& root, const std::vector<std::pair<std::string, Value>>& add) {
    if (root.type != Value::Map) return false;
    Value* data = root.find_mut("data");
    if (!data || data->type != Value::Map) return false;
    Value out = Value::object();
    for (auto& [key, value] : data->map) {
        bool replaced = false;
        for (auto& added : add) replaced |= added.first == key;
        if (!replaced) out.map.emplace_back(key, value);
    }
    for (auto& [key, value] : add) {
        const Value* old = data->find(key);
        out.map.emplace_back(key, old ? merge_maps(*old, value) : value);
    }
    *data = std::move(out);
    return true;
}

// The body as a Value: false when it isn't one msgpack value that encodes back to the same bytes
// (malformed, or not in the encoder's canonical form: the splice then leaves it alone, as it can't
// re-encode the rest unchanged). The server's bodies and the fake server's files are canonical.
bool decode_body(const std::vector<char>& body, Value& out) {
    const uint8_t *p = (const uint8_t*)body.data(), *e = p + body.size();
    out = mp_decode(p, e);
    return p == e && mp_encode(out) == std::vector<uint8_t>(body.begin(), body.end());
}

namespace {

// The client's FunctionIDs of the requests the campaign watches (docs/api.md;
// port/src/native/api/gen/fakeapi_tables.inc).
constexpr u32 kGetPlayMission = 0x7c1b7a1b, kGetWorldMapInfoList = 0x15a9bdbd, kGetPlayer = 0x9a056905;
constexpr u32 kMissionStart = 0xb7c62bc2, kMissionEnd = 0x8312a64c, kMissionTalk = 0x816dc8b4, kMissionFailed = 0x479604f6;
// msgpack's empty map: a body that holds nothing (the host's fallback for an unanswered request).
constexpr u8 kEmptyMsgpackMap = 0x80;

// The argument of a request that is a master_mission id ((b) the client passes the mission id; we
// don't rely on its position): among the first n integer arguments.
u32 mission_arg(const Request& req, int n) {
    const Master& m = master();
    for (int i = 0; i < n && i < (int)req.ints.size(); i++)
        if (m.missions.count((u32)req.ints[i])) return (u32)req.ints[i];
    return 0;
}
// Integer argument k (1-based, as the registers x1..: every argument of these methods is an
// integer); 0 when absent. For the log lines.
uint64_t arg(const Request& req, size_t k) { return k >= 1 && k <= req.ints.size() ? (uint64_t)req.ints[k - 1] : 0; }

// The keys the campaign adds to the response of `fid`, in their order.
std::vector<std::pair<std::string, Value>> campaign_keys(u32 fid, const State& s) {
    std::vector<std::pair<std::string, Value>> add;
    // MissionStart's MissionParameter / PlayMission come from the server core (api/missions/), which
    // takes the mission from the request. The full player state (GetPlayer) and GetPlayMission (the
    // answer after a story scene's EndMissionTalk, core/lifecycle.cpp) are the login delivery.
    bool login = fid == kGetPlayer || fid == kGetPlayMission;
    if (login || fid == kGetWorldMapInfoList || fid == kMissionEnd || fid == kMissionTalk)
        add.push_back({"Player", build_player(s, login && s.seeded)});
    if (login || fid == kGetWorldMapInfoList || fid == kMissionEnd || fid == kMissionTalk)
        add.push_back({"ActiveWorldMapMissionList", build_world_map_list(s)});
    // (d) Every response carries the current ActiveMissionList, so the menus always see the
    // progress (the 3.7.0 server's exact choice of responses isn't known).
    add.push_back({"ActiveMissionList", build_active_mission_list(s)});
    return add;
}

}  // namespace

bool enabled() { return config().enabled; }

std::vector<uint8_t> active_mission_list_msgpack() {
    std::lock_guard<std::mutex> held(lock());
    return mp_encode(build_active_mission_list(state()));
}

// Before the server handles a request (server::answer): the progress it implies.
//   (b) MissionStart: the mission started (among its arguments).
//   (b) MissionEnd: only sent for a finished (won) mission; it clears the one named, else the one
//       started.
//   (b) MissionTalk: a story-scene mission (master_mission.talk_event_id) played: cleared.
//   (b) GetWorldMapInfoList(u32 episode): the episode the next world-map list is for.
void on_request(const Request& req) {
    if (!enabled()) return;
    const uint32_t fid = req.fid;
    std::lock_guard<std::mutex> held(lock());
    State& s = state();
    if (fid == kMissionStart) {
        s.playing = mission_arg(req, 7);
        LOGI("server", "campaign: MissionStart(%" PRIu64 ", %" PRIu64 ", %" PRIu64 ", ...) -> mission %u", arg(req, 1), arg(req, 2), arg(req, 3),
             s.playing);
    } else if (fid == kMissionEnd) {
        // (b) CApiCaller::MissionEnd is only sent for a finished (won) mission; a lost one sends
        // MissionFailed / MissionLose. The mission is the one started, unless an argument names one.
        u32 id = mission_arg(req, 2);
        if (!id) id = s.playing;
        LOGI("server", "campaign: MissionEnd(%" PRIu64 ", %" PRIu64 ") -> mission %u", arg(req, 1), arg(req, 2), id);
        clear_mission(s, id, "cleared");
    } else if (fid == kMissionTalk) {
        // (b) MissionTalk is sent when a story-scene mission (master_mission.talk_event_id) is played.
        u32 id = mission_arg(req, 3);
        LOGI("server", "campaign: MissionTalk(%" PRIu64 ", %" PRIu64 ", %" PRIu64 ", %" PRIu64 ") -> mission %u", arg(req, 1), arg(req, 2),
             arg(req, 3), arg(req, 4) & 0xff, id);
        clear_mission(s, id, "story scene played:");
    } else if (fid == kGetWorldMapInfoList) {
        // (b) GetWorldMapInfoList(u32): CWorldMapMenu::CallReceiveApi passes the episode
        // (master_selectpart id, e.g. chapter_1 or Episode03); the answer lists that episode's maps.
        s.wm_episode = (u32)arg(req, 1);
        LOGI("server", "campaign: GetWorldMapInfoList(%u)", s.wm_episode);
    } else if (fid == kMissionFailed) {
        LOGI("server", "campaign: MissionFailed(%" PRIu64 ", %" PRIu64 ")", arg(req, 1), arg(req, 2));
    }
}

void end_mission_talk(uint32_t mission) {
    if (!enabled()) return;
    std::lock_guard<std::mutex> held(lock());
    State& s = state();
    auto it = master().missions.find(mission);
    if (it == master().missions.end() || !it->second.talk) {
        LOGI("server", "campaign: EndMissionTalk(%u): not a story mission; ignored", mission);
        return;
    }
    clear_mission(s, mission, "story scene played:");
}

// After the server answered (server::answer: accepted, or not handled): the campaign's keys
// spliced into the body (campaign_keys). GetWorldMapInfoList has no server handler (the host's
// fallback answers {}) and an empty body is a bare {data: {}, status: 0}; GetPlayMission is
// answered by the server core (its play state), so its body is kept.
bool on_response(uint32_t fid, const std::string& name, std::vector<char>& body) {
    if (!enabled()) return false;
    std::lock_guard<std::mutex> held(lock());
    State& s = state();
    std::vector<std::pair<std::string, Value>> add = campaign_keys(fid, s);
    Value root;
    if (fid == kGetWorldMapInfoList || body.empty() || (body.size() == 1 && (u8)body[0] == kEmptyMsgpackMap)) {
        root = Value::object();
        root["data"] = Value::object();
        root["status"] = 0u;
    } else if (!decode_body(body, root)) {
        root = Value();  // splice_data refuses it
    }
    bool ok = splice_data(root, add);
    if (!ok) LOGW("server", "campaign: %s: unexpected response shape; not changed", name.c_str());
    else {
        std::vector<u8> out = mp_encode(root);
        body.assign(out.begin(), out.end());
    }
    return ok;
}

}  // namespace soa::server::campaign
