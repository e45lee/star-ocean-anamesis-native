// Local server: the rental ("helper") list of the mission menu, FollowList, and the
// rental bonus. Our code (port), not guest behaviour; every rule carries its source label:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
// docs/server-rules.md "Rental helpers" has the same rules in prose.
//
// Client side (3.7.0, b): CMissionMenu::CreateRentalCharactorList ->
// CParameterUtility::CreateRentalListAuto(mission type, mission id):
//   - a mission with master_mission_npc rows lists those NPCs (tCharaData::InitializeNPC), from
//     master data alone: nothing to serve;
//   - otherwise CParameterUtility::CreateRentalList walks the `BattleRental` info
//     (CBattleRentalInfoList at CParameterManager+0x62c8, its map at +0x6300; the live schema
//     dump, --fake-server-schema) and makes one tCharaData::InitializeRental(player, pc) per
//     entry, skipping players in BlacklistID (+0x6638) and flagging those in FollowID (+0x6350).
//     The entries are CFollowInfo = {order, player: CFollowPlayerInfo, pc: CFollowPersonInfo} (the
//     child names are the classes' pParseName; b), keyed by id as a string like the other ...Map
//     infos; `Follow` (FollowList's list, +0x63b8) has the same shape.
// No request is made when the list opens: the list is whatever `BattleRental` the client got
// last. The 3.7.0 server's route for it isn't known; (d) we send it with every full-state player
// response (Login, GetPlayMission ...), and FollowList answers the same entries as `Follow`.
#include <algorithm>
#include <ctime>
#include <string>
#include <vector>

#include "core/log.h"
#include "core/request_args.h"
#include "core/time.h"
#include "soaserver/ext.h"
#include "core/response.h"
#include "api/player/roster.h"  // owns_character
#include "api/social/rental.h"
#include "core/modules.h"

namespace soa::server {
namespace {
using namespace ext;

// (d) The synthetic rental players: there are no other players on a local server, so the list is
// made of clones of the player's own roster: the kRentalMax highest-level characters (one per
// role, ties by uid), each lent by a "player" with the player's own name and level. Their ids are
// the roster uid with bit 40 set (rental.h), so MissionStart can find the character again.
constexpr int kRentalMax = 10;
constexpr u32 kRentalPlayerBase = 0x7d000000;  // (d) synthetic player ids (roster uids are 0x7e......)

// UpdateSupport(u64 character_uid) (b: docs/api.md); 0 when missing.
struct UpdateSupportArgs {
    CharacterUid character_uid;
    static UpdateSupportArgs from(const Request& req) { return {CharacterUid(args::int_at(req, 0))}; }
};

// A lent character: its roster uid and its place in the list (1-based).
struct Lender {
    CharacterUid uid;
    u32 order;
};

std::vector<Lender> lenders(Ctx& ctx) {
    std::vector<Lender> out;
    std::vector<u32> roles;
    ctx.st.q("select uid, role_id from roster order by level desc, uid", {}, [&](const Row& roster_row) {
        if ((int)out.size() >= kRentalMax) return;
        u32 role = (u32)roster_row.i("role_id");
        if (std::find(roles.begin(), roles.end(), role) != roles.end()) return;
        roles.push_back(role);
        out.push_back({roster_row.id<CharacterUid>("uid"), (u32)out.size() + 1});
    });
    return out;
}

// A key of a map value (nullptr when `v` isn't a map or lacks it).
const Value* field(const Value& v, const char* key) { return v.type == Value::Map ? v.find(key) : nullptr; }

// The roster entry (CPersonInfo) whose id is `uid`; nullptr when none. The last match wins, as the
// list has one per uid.
const Value* roster_entry(const Value& roster, CharacterUid uid) {
    const Value* found = nullptr;
    for (auto& entry : roster.arr)
        if (field(entry, "id") && field(entry, "id")->u == uid.v) found = &entry;
    return found;
}

// CFollowPersonInfo (b: property names from CFollowPersonInfo::Initialize and fields.txt): the
// roster character as the core reports it, plus the lender's player id and the equipment's
// master ids and levels (InitializeRental reads the weapon / accessory master item ids).
Value follow_person_info(Ctx& ctx, const Value& character, u32 lender_player_id) {
    Value person = character;
    u64 uid = field(character, "id") ? field(character, "id")->u : 0;
    person["id"] = rental::id_of(CharacterUid(uid));
    person["player_id"] = lender_player_id;
    for (const char* slot : {"weapon", "accessory"}) {
        const Value* item_uid_value = field(character, (std::string(slot) + "_item_id").c_str());  // a uid (CPersonInfo)
        u64 item_uid = item_uid_value ? item_uid_value->u : 0;
        u32 master_item_id = 0, level = 0, limit_break = 0;
        if (item_uid)
            ctx.st.q("select master_item_id, level, limit_break from items where uid = ?", {item_uid}, [&](const Row& item_row) {
                master_item_id = (u32)item_row.i("master_item_id");
                level = (u32)std::max<int64_t>(1, item_row.i("level"));
                limit_break = (u32)item_row.i("limit_break");
            });
        person[std::string(slot) + "_master_item_id"] = master_item_id;
        person[std::string(slot) + "_level"] = level;
        person[std::string(slot) + "_limit_break_count"] = limit_break;
    }
    return person;
}

// CFollowPlayerInfo (b: CFollowPlayerInfo::Initialize; values d): the player's own name and level
// under the id `player_id`.
Value follow_player_info(Ctx& ctx, u32 player_id) {
    Value state = ctx.base_data();
    const Value* player = state.find("Player");
    Value info = Value::object();
    info["id"] = player_id;
    info["name"] = player && player->find("name") ? player->find("name")->s : std::string();
    info["level"] = player ? (u32)player->get_u("level", 1) : 1u;
    info["last_login_at"] = ctx.fmt_time(ctx.now());
    info["played_with_at"] = "";
    info["follow_status"] = 0u;  // (d) neither following nor followed
    info["is_block"] = false;
    info["is_rookie"] = false;
    info["is_subscription"] = false;
    info["title"] = 0u;
    info["sphere211_floor_level"] = 0u;
    info["sphere211_previous_floor_level"] = 0u;
    return info;
}

// ---- rental bonus ---------------------------------------------------------------------------
// master_rental_bonus rows {id 1..10, present_message_id rental_bonus_1, content item_coin_37
// "サポートメダル", num 300..750} (a). The medal is "the reward you get when a character you set
// for rental is rented" and uimsg_sphere211_getting_rental_bonus reads "yesterday %u users rented
// you ... %s x %u arrived from your followers" (a: master_text): a daily payout by the number of
// rentals the day before. The row whose id is that number, capped at the last row, pays (d: the
// id-as-count reading; b: CUIUtility::GetMasterRentalBonus(id) looks rows up by id).
// On a local server nobody else rents the player's characters, so (d) the rentals counted are
// the player's own rentals of the clones above (MissionStart counts them per rental day, the
// daily reset of master_global login_bonus_reset_hour); each earlier day still unpaid pays once,
// into the present box, on the next full-state player response. RentalCount / RentalBonus (the
// top-level uints of the response, b: schema) carry the last paid day's count and row id.
constexpr u32 kReasonRentalBonus = 3;  // (d) the present reason type (a plain "%s" line), as achievements

void rental_bonus(Ctx& ctx, Value& data) {
    int64_t today = day_start(ctx.now(), (int)ctx.global_u32("login_bonus_reset_hour", 4));  // (a)
    std::vector<std::pair<int64_t, u32>> due;  // day, rentals
    ctx.st.q("select rental_day, count from follow_rental where paid = 0 and count > 0 and rental_day < ? order by rental_day", {today},
             [&](const Row& rental_row) { due.emplace_back(rental_row.i("rental_day"), (u32)rental_row.i("count")); });
    if (due.empty()) return;
    u32 last_row_id = (u32)ctx.m.one("select max(id) from master_rental_bonus", {}, 0);
    u32 paid_count = 0, paid_row_id = 0;
    for (auto& [day, count] : due) {
        u32 row_id = std::min(count, last_row_id);
        ctx.m.q("select * from master_rental_bonus where id = ?", {row_id}, [&](const Row& bonus_row) {
            add_present(ctx, (u32)bonus_row.i("content_type"), (u32)bonus_row.i("content_id"), (u32)bonus_row.i("num"), kReasonRentalBonus, row_id);
            LOGI("server", "rental bonus: %u rentals on day %lld -> row %u: %u x %s", count, (long long)day, row_id,  // read by rental_session.sh
                 (u32)bonus_row.i("num"), bonus_row.s("content_id_label").c_str());
        });
        ctx.st.q("update follow_rental set paid = 1 where rental_day = ?", {day});
        paid_count = count;
        paid_row_id = row_id;
    }
    data["RentalCount"] = paid_count;
    data["RentalBonus"] = paid_row_id;
    data["PresentBoxCount"] = (u32)ctx.st.one("select count(*) from presents where received_at is null", {});
}

// OnPlayerLoad: BattleRental (the rental list, rental::follow_map) on every full player state, and
// the rental bonus of the days before (rental_bonus above).
void load_follow(Ctx& ctx, const Request&, Value& data) {
    data["BattleRental"] = rental::follow_map(ctx);
    rental_bonus(ctx, data);
}

// FollowList() -> FollowListRes                                                  fid 9bddc9d7
// API: docs/api.md#followlist   Rules: docs/server-rules.md "Rental helpers"
//
// The follow menu's lists (CFriendMenu, CSphereFloor, CFollowNeighbor send it).
//   (b) the response keys Follow, FollowPlayerList, FollowID, MutualFollowID (docs/api.md);
//   (d) Follow is the rental list (rental::follow_map); nobody is followed on a local server, so
//       the other three are empty.
// Answers: the player state with the four lists.
std::vector<u8> follow_list(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["Follow"] = rental::follow_map(ctx);
    data["FollowPlayerList"] = Value::object();
    data["FollowID"] = Value::array();
    data["MutualFollowID"] = Value::array();
    return body(data);
}

// UpdateSupport(u64 character_uid) -> UpdateSupportRes                           fid 3e77af96
// API: docs/api.md#updatesupport   Rules: docs/server-rules.md "Rental helpers"
//
// The character the player lends to other players (the character dialog's レンタル button,
// uimsg_ch_dialog_rental).
//   (b) request and answer: docs/api.md (UpdateSupport(unsigned long) -> Player.support_pc_id);
//       the character is a uid (CRentalBonus::Setup shows support_pc_id's card through
//       tCharaData::Initialize(uid)).
//   (d) it must be owned; otherwise refused (no body) like SetAssist.
//   Stored as player.support_uid; the core's Player sends it (api/player/player_info.cpp
//   player_info, with the default there).
// Answers: the player state (Player.support_pc_id).
std::vector<u8> update_support(Ctx& ctx, const Request& req) {
    const auto args = UpdateSupportArgs::from(req);
    if (!owns_character(ctx, args.character_uid)) {
        LOGW("server", "UpdateSupport %llu refused: not an owned character", (unsigned long long)args.character_uid.v);
        return {};
    }
    ctx.st.q("update player set support_uid = ?", {args.character_uid});
    LOGI("server", "UpdateSupport: support character %llu", (unsigned long long)args.character_uid.v);
    return with_player_state(ctx);
}

}  // namespace

namespace rental {

Value follow_map(Ctx& ctx) {
    Value roster = ctx.roster();
    Value follow = Value::object();
    for (auto& lender : lenders(ctx)) {
        const Value* character = roster_entry(roster, lender.uid);
        if (!character) continue;
        u32 lender_player_id = kRentalPlayerBase + lender.order;
        Value entry = Value::object();
        entry["order"] = lender.order;
        entry["player"] = follow_player_info(ctx, lender_player_id);
        entry["pc"] = follow_person_info(ctx, *character, lender_player_id);
        follow[std::to_string(lender_player_id)] = entry;
    }
    return follow;
}

// GetPlayerDetailInfo's SearchResult entry for the player (api/events/ranking.cpp).
Value own_follow_entry(Ctx& ctx) {
    Value roster = ctx.roster();
    std::optional<CharacterUid> home_uid = ctx.st.one_opt<CharacterUid>("select home_uid from player", {});  // NULL: none
    std::vector<Lender> lent = lenders(ctx);
    // (d) the character shown: the home character (the player's own pick), else the one the
    // rental list lends first (the highest level)
    const Value* character = nullptr;
    for (std::optional<CharacterUid> want : {home_uid, lent.empty() ? std::nullopt : std::optional(lent[0].uid)}) {
        if (character || !want) continue;
        character = roster_entry(roster, *want);
    }
    u32 player_id = ctx.player_id().v;  // the wire's number
    Value entry = Value::object();
    entry["order"] = 1u;
    entry["player"] = follow_player_info(ctx, player_id);
    if (character) {
        Value person = follow_person_info(ctx, *character, player_id);
        person["id"] = field(*character, "id")->u;  // the player's own character: its roster uid, not a rental id
        entry["pc"] = person;
    }
    return entry;
}

}  // namespace rental

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_follow() {
    using namespace ext;
    add_player_load(load_follow);
    add_api({"FollowList"}, follow_list);
    add_api({"UpdateSupport"}, update_support);
}

}  // namespace soa::server
