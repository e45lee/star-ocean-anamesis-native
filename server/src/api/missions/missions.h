#pragma once
// The missions (port code, not guest behaviour): MissionStart and its battle party
// (mission_start.cpp), MissionEnd and its rewards (mission_end.cpp), the drop roll (drops.cpp),
// the master_campaign rows (campaigns.cpp) and the play state (play_state.cpp: GetPlayMission,
// MissionFailed, MissionTalk, MissionRestart, GetMissionList). docs/server-rules.md "Server
// missions", "2. Missions".
#include <string>
#include <vector>

#include "core/request_context.h"
#include "core/rewards.h"  // Drop
#include "master/master.h"
#include "soaserver/ext.h"

namespace soa::server {

using MissionRef = master::MissionRef;

// Common::MissionType: the master table of a mission (b: CStageManager::CallMissionStart's first
// argument, CParameterUtility::FindMissionWithId(id, type); a: master_campaign.
// master_mission_model_type uses the same numbers).
enum class MissionType : u32 { kStory = 0, kEvent = 1, kTower = 2, kWorldMap = 3 };

// The battle's helper as MissionStart records it (play_ext.helper_kind; d: the server's own
// numbering, nothing on the wire).
enum class HelperKind : u32 {
    kNone = 0,
    kOwn = 1,     // one of the player's characters, outside the party
    kRental = 2,  // a rental character (a clone of the roster: api/social/rental.h)
    kNpc = 3,     // an NPC: the event mission's NPC helper, or an NPC id only recorded
};

// The master_campaign.type_id values the missions apply (a: the rows; b: what the client queries
// them for, docs/server-rules.md "Type-8 campaigns").
enum class CampaignType : u32 {
    kDropLots = 0,  // Campaign_evo_*_prism: lot_drop_count_add more lots, and master_campaign_drop
    kStamina = 1,   // the stamina cost x magnification (0.5)
    kFavor = 8,     // 友好 (*_yuukou_*): the battle favor x magnification (1.5)
};

// Common::MissionDropType: the badge the result screen gives a drop (b: ResultUtility::GetRewardType
// -> GetRewardBadgeIcon; docs/server-rules.md "MissionEnd drops").
enum class DropType : u32 {
    kPlain = 0,           // no badge
    kHostBonus = 1,       // hostb_badge
    kBeginner = 2,        // icon_wakaba (初心者)
    kKakin = 3,           // kakin_badge
    kFavor = 4,           // heartb_badge
    kCharacterBonus = 5,  // chara_badge
    kDeepSpacePlus = 7,   // ds_plus_badge
    kDefeat = 10,
    kGod = 11,            // god_badge
};
// The mission row of `type` (master::find_mission).
MissionRef find_mission(ext::Ctx& ctx, u32 type, u32 mission);

// A master_campaign row running now that applies to a mission (a: windows, model type, area).
struct Campaign {
    u32 id;
    CampaignType type;     // type_id
    double magnification;  // magnification
    u32 extra_lots;        // lot_drop_count_add
    std::string label;     // id_label
};
std::vector<Campaign> campaigns_for(ext::Ctx& ctx, const MissionRef& ref);

// (b) NetworkApiCaller::MissionEnd's request lambda serializes CBattleLogInfo (with its
// BattleEvaluationInfo list) with the request (soaserver/battle_log.h): the request's own log
// (soa-server: the wire's blob; soa: the FakeApiCaller route runs the same serializer,
// port/src/native/api/server_adapters.cpp). None: every value is its default.
inline const BattleLog& current_log(ext::Ctx& ctx) { return ctx.request->log(); }

// A u32 property of the battle log by name; `dflt` when missing.
inline u32 battle_log_u32(ext::Ctx& ctx, const char* name, u32 dflt) { return current_log(ctx).prop_u32(name, dflt); }

// The battle's evaluation value of `type` (1..6: 1 total damage, 2 enemies defeated, 3 rush-combo
// total damage, 4 highest hit count, 5 highest single damage, 6 clear time in ms), or -1 when the
// battle recorded none (docs/server-rules.md "Battle evaluation values").
inline int64_t battle_evaluation_value(ext::Ctx& ctx, int type) { return current_log(ctx).evaluation(type); }

struct Rolled {
    std::vector<Drop> drops;
    std::vector<u32> evaluations;  // master_battle_evaluation ids reached
    u32 surprise_lots = 0, campaign_lots = 0, bonus_lots = 0, bonus_extra = 0, eval_lots = 0;
};
// (a) master_mission_drop / master_common_drop / master_campaign_drop rows: `lots` lots from the
// rows `sql` selects with `key`, and (fixed) the is_fix_drop rows (drops.cpp).
void lottery(ext::Ctx& ctx, const std::string& sql, ext::Arg key, int64_t lots, DropType drop_type, std::vector<Drop>& out, bool fixed = true);
// The whole drop roll of a won mission (drops.cpp).
Rolled roll_drops(ext::Ctx& ctx, u32 mission, const std::string& table = "master_mission", u32 type = 0, u32 area = 0, bool surprise = false,
                  const std::vector<u32>& party_roles = {});
// What a mission played, for the extension modules (ext::MissionInfo).
ext::MissionInfo mission_info(ext::Ctx& ctx, const MissionRef& ref, u32 mission, const std::vector<u64>& uids);

// MissionStart, and the same start for a module (ext::Ctx::core_mission: `module_override`, the
// module's changes) or a MissionRestart (`restarting`: no stamina, no new play count).
std::vector<u8> start_mission(ext::Ctx& ctx, const Request& req, const ext::MissionOverride* module_override, bool restarting);
std::vector<u8> mission_start(ext::Ctx& ctx, const Request& req);
std::vector<u8> mission_end(ext::Ctx& ctx, const Request& req);
// The play state (play_state.cpp): GetPlayMission, MissionFailed, MissionTalk, MissionRestart /
// MultiMissionRestart.
std::vector<u8> get_play_mission(ext::Ctx& ctx, const Request& req);
std::vector<u8> mission_failed(ext::Ctx& ctx, const Request& req);
std::vector<u8> mission_talk(ext::Ctx& ctx, const Request& req);
std::vector<u8> mission_restart(ext::Ctx& ctx, const Request& req);
// The play state's answer for a module (ext::Ctx::core_mission): MissionFailed, MissionTalk, else
// GetPlayMission's.
std::vector<u8> play_state(ext::Ctx& ctx, const Request& req);

}  // namespace soa::server
