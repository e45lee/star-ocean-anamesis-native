// The story campaign's hooks (soaserver/api_campaign.h): the progress from MissionStart /
// MissionEnd / MissionTalk (an OnResponse hook, in the request's transaction: only an accepted
// request clears) and EndMissionTalk, and the campaign's keys spliced into the responses
// (server::answer, core/lifecycle.cpp, for both hosts). Port code (restore
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
#include "core/request_args.h"
#include "soaserver/config.h"
#include "soaserver/ext.h"
#include "soaserver/fids.h"  // the requests the campaign watches

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
// re-encode the rest unchanged). The server's bodies are canonical.
bool decode_body(const std::vector<char>& body, Value& out) {
    const uint8_t *p = (const uint8_t*)body.data(), *e = p + body.size();
    out = mp_decode(p, e);
    return p == e && mp_encode(out) == std::vector<uint8_t>(body.begin(), body.end());
}

namespace {

// msgpack's empty map: a body that holds nothing (the host's fallback for an unanswered request).
constexpr u8 kEmptyMsgpackMap = 0x80;

// A request's mission when the campaign has it ((b) the client passes the mission id: the
// methods' args structs, core/request_args.h), else 0.
u32 campaign_mission(u32 id) { return master().missions.count(id) ? id : 0; }
// MissionEnd's mission: the request's, else the one of the last accepted MissionStart. (b) The
// mission is the one started unless an argument names one. Takes the campaign's lock.
u32 mission_end_mission(const Request& req) {
    if (u32 id = campaign_mission(args::MissionEndArgs::from(req).mission)) return id;
    std::lock_guard<std::mutex> held(lock());
    return session().playing;
}
// MissionTalk's mission: (b) MissionTalk(type, mission, talk, flag), the story-scene mission played.
u32 mission_talk_mission(const Request& req) {
    const auto talk = args::MissionTalkArgs::from(req);
    return talk.has_mission ? campaign_mission(talk.mission) : 0;
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
    bool login = fid == fids::kGetPlayer || fid == fids::kGetPlayMission;
    if (login || fid == fids::kGetWorldMapInfoList || fid == fids::kMissionEnd || fid == fids::kMissionTalk)
        add.push_back({"Player", build_player(s, login && s.seeded)});
    if (login || fid == fids::kGetWorldMapInfoList || fid == fids::kMissionEnd || fid == fids::kMissionTalk)
        add.push_back({"ActiveWorldMapMissionList", build_world_map_list(s)});
    // (d) Every response carries the current ActiveMissionList, so the menus always see the
    // progress (the 3.7.0 server's exact choice of responses isn't known).
    add.push_back({"ActiveMissionList", build_active_mission_list(s)});
    return add;
}

}  // namespace

bool enabled() { return config().enabled; }

std::mutex& lock() {
    static std::mutex mu;
    return mu;
}
Session& session() {
    static Session s;
    return s;
}

namespace {
// The progress of the live server's state (its own read transaction; an empty one without a
// server), with the session's episode. Called around a request, never inside one.
State live_state() {
    State s;
    ext::with_live_server([&](ext::Ctx& ctx) { s = load_state(ctx); });
    std::lock_guard<std::mutex> held(lock());
    s.wm_episode = session().wm_episode;
    return s;
}
}  // namespace

std::vector<uint8_t> active_mission_list_msgpack() { return mp_encode(build_active_mission_list(live_state())); }

// Before the server handles a request (server::answer): the log of what it implies, and the
// session's episode. The progress itself is recorded by the OnResponse hook below, in the
// request's transaction, once the request is accepted.
//   (b) GetWorldMapInfoList(u32 episode): the episode the next world-map list is for.
void on_request(const Request& req) {
    if (!enabled()) return;
    const uint32_t fid = req.fid;
    if (fid == fids::kMissionStart) {
        LOGI("server", "campaign: MissionStart(%" PRIu64 ", %" PRIu64 ", %" PRIu64 ", ...) -> mission %u", arg(req, 1), arg(req, 2), arg(req, 3),
             campaign_mission(args::MissionStartArgs::from(req).mission));
    } else if (fid == fids::kMissionEnd) {
        LOGI("server", "campaign: MissionEnd(%" PRIu64 ", %" PRIu64 ") -> mission %u", arg(req, 1), arg(req, 2), mission_end_mission(req));
    } else if (fid == fids::kMissionTalk) {
        LOGI("server", "campaign: MissionTalk(%" PRIu64 ", %" PRIu64 ", %" PRIu64 ", %" PRIu64 ") -> mission %u", arg(req, 1), arg(req, 2),
             arg(req, 3), arg(req, 4) & 0xff, mission_talk_mission(req));
    } else if (fid == fids::kGetWorldMapInfoList) {
        // (b) GetWorldMapInfoList(u32): CWorldMapMenu::CallReceiveApi passes the episode
        // (master_selectpart id, e.g. chapter_1 or Episode03); the answer lists that episode's maps.
        u32 episode = (u32)arg(req, 1);
        {
            std::lock_guard<std::mutex> held(lock());
            session().wm_episode = episode;
        }
        LOGI("server", "campaign: GetWorldMapInfoList(%u)", episode);
    } else if (fid == fids::kMissionFailed) {
        LOGI("server", "campaign: MissionFailed(%" PRIu64 ", %" PRIu64 ")", arg(req, 1), arg(req, 2));
    }
}

namespace {
// OnResponse (an accepted request, in its transaction; adds no keys): the progress it implies.
//   (b) MissionStart: the mission started (MissionStartArgs) is the one playing.
//   (b) MissionEnd: CApiCaller::MissionEnd is only sent for a finished (won) mission; a lost one
//       sends MissionFailed / MissionLose. It clears the mission named, else the one started.
//   (b) MissionTalk: sent when a story-scene mission (master_mission.talk_event_id) is played:
//       cleared.
// A refused request (a refusal, --fail, a failed statement) is rolled back with its clear.
bool record_progress(ext::Ctx& ctx, const Request& req, Value&) {
    if (req.fid == fids::kMissionStart) {
        u32 id = campaign_mission(args::MissionStartArgs::from(req).mission);
        std::lock_guard<std::mutex> held(lock());
        session().playing = id;
    } else if (req.fid == fids::kMissionEnd) {
        if (u32 id = mission_end_mission(req)) clear_mission(ctx, id, "cleared");
    } else if (req.fid == fids::kMissionTalk) {
        if (u32 id = mission_talk_mission(req)) clear_mission(ctx, id, "story scene played:");
    }
    return false;
}
}  // namespace

void register_campaign() { ext::add_response_hook(record_progress); }

void end_mission_talk(uint32_t mission) {
    if (!enabled()) return;
    auto it = master().missions.find(mission);
    if (it == master().missions.end() || !it->second.talk) {
        LOGI("server", "campaign: EndMissionTalk(%u): not a story mission; ignored", mission);
        return;
    }
    // Not a request of its own: the live server's own transaction, around the request
    // (server::answer's EndMissionTalk).
    ext::with_live_server([&](ext::Ctx& ctx) { clear_mission(ctx, mission, "story scene played:"); });
}

// After the server answered (server::answer: accepted, or not handled): the campaign's keys
// spliced into the body (campaign_keys). GetWorldMapInfoList has no server handler (the host's
// fallback answers {}) and an empty body is a bare {data: {}, status: 0}; GetPlayMission is
// answered by the server core (its play state), so its body is kept.
bool on_response(uint32_t fid, const std::string& name, std::vector<char>& body) {
    if (!enabled()) return false;
    const State s = live_state();
    std::vector<std::pair<std::string, Value>> add = campaign_keys(fid, s);
    Value root;
    if (fid == fids::kGetWorldMapInfoList || body.empty() || (body.size() == 1 && (u8)body[0] == kEmptyMsgpackMap)) {
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
