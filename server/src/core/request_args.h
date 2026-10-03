#pragma once
// The core handlers' request arguments by name (port code, not guest behaviour). A Request carries
// its arguments positionally (ints, strs, vecs in the method's order: soaserver/server.h); each
// struct here reads one method's, with the defaults the handlers used when an argument is missing
// (none of them logs). The method signatures are docs/api.md's **Method** lines (the client's
// FakeApiCaller methods). The modules get theirs in their domain steps (server/PLAN-readability.md
// R10-R18).
#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "soaserver/ids.h"
#include "soaserver/server.h"

namespace soa::server::args {

// The k-th integer argument, `dflt` when the request has fewer.
inline u64 int_at(const Request& r, size_t k, u64 dflt = 0) { return r.ints.size() > k ? r.ints[k] : dflt; }
// The k-th string argument, "" when the request has fewer.
inline std::string str_at(const Request& r, size_t k) { return r.strs.size() > k ? r.strs[k] : std::string(); }

// CreatePlayer(const char* name, const char* uuid): an empty or missing name is "Player".
struct CreatePlayerArgs {
    std::string name, uuid;
    static CreatePlayerArgs from(const Request& r) {
        CreatePlayerArgs a;
        a.name = r.strs.size() > 0 && !r.strs[0].empty() ? r.strs[0] : "Player";
        a.uuid = str_at(r, 1);
        return a;
    }
};

// UpdateTutorial(u64 tutorial_status).
struct UpdateTutorialArgs {
    u64 status = 0;
    static UpdateTutorialArgs from(const Request& r) { return {int_at(r, 0)}; }
};

// UpdateView(Common::ViewFlagType kind, u64 flags).
struct UpdateViewArgs {
    u64 kind = 0, flags = 0;
    static UpdateViewArgs from(const Request& r) { return {int_at(r, 0), int_at(r, 1)}; }
};

// UpdateKiyakuVersion(const char* version).
struct UpdateKiyakuVersionArgs {
    std::string version;
    static UpdateKiyakuVersionArgs from(const Request& r) { return {str_at(r, 0)}; }
};

// UpdatePlayerName(const char* name): "" = unchanged.
struct UpdatePlayerNameArgs {
    std::string name;
    static UpdatePlayerNameArgs from(const Request& r) { return {str_at(r, 0)}; }
};

// UpdateParty(u32 party_id, u64 uid1, u64 uid2, u64 uid3): the party id defaults to 1.
struct UpdatePartyArgs {
    u32 party_id = 1;
    CharacterUid member_uid[3];  // the three members' owned uids (0 = empty)
    static UpdatePartyArgs from(const Request& r) {
        UpdatePartyArgs a;
        a.party_id = r.ints.size() > 0 ? (u32)r.ints[0] : 1;
        for (size_t k = 0; k < 3; k++) a.member_uid[k] = CharacterUid(int_at(r, k + 1));
        return a;
    }
};

// UpdatePartySet(PartySetInfo const&): the wire's string (the party set as text).
struct UpdatePartySetArgs {
    std::string text;
    static UpdatePartySetArgs from(const Request& r) { return {str_at(r, 0)}; }
};

// SetAssist(u64 character_uid, u64 assist_uid).
struct SetAssistArgs {
    CharacterUid character_uid;
    std::optional<CharacterUid> assist_uid;  // 0: none (take the assist off)
    static SetAssistArgs from(const Request& r) { return {CharacterUid(int_at(r, 0)), nonzero<CharacterUid>(int_at(r, 1))}; }
};

// UpdateHome(u64 character_uid).
struct UpdateHomeArgs {
    CharacterUid character_uid;
    static UpdateHomeArgs from(const Request& r) { return {CharacterUid(int_at(r, 0))}; }
};

// MissionStart(u32 type, u32 mission, u32 helper index + 1, u64 own helper uid, u32 NPC helper id,
// u64 rental uid, u32) (b: CStageManager::CallMissionStart; docs/api.md).
struct MissionStartArgs {
    u32 type = 0, mission = 0;
    u32 helper_index_plus_1 = 0;  // which helper kind the client picked (0 = none)
    u64 own_helper_uid = 0;
    u32 npc_helper_id = 0;  // a master_mission_npc or master_npc id
    u64 rental_uid = 0;
    static MissionStartArgs from(const Request& r) {
        MissionStartArgs a;
        a.type = (u32)int_at(r, 0);
        a.mission = (u32)int_at(r, 1);
        a.helper_index_plus_1 = (u32)int_at(r, 2);
        a.own_helper_uid = int_at(r, 3);
        a.npc_helper_id = (u32)int_at(r, 4);
        a.rental_uid = int_at(r, 5);
        return a;
    }
};

// MissionEnd(u32 mission (+0x54), u32 (+0x5c)).
struct MissionEndArgs {
    u32 mission = 0;
    static MissionEndArgs from(const Request& r) { return {(u32)int_at(r, 0)}; }
};

// MissionTalk(u32 type, u32 mission, u32 talk, u8 flag): the mission when the request has one.
struct MissionTalkArgs {
    bool has_mission = false;
    u32 mission = 0;
    static MissionTalkArgs from(const Request& r) {
        MissionTalkArgs a;
        a.has_mission = r.ints.size() > 1;
        a.mission = (u32)int_at(r, 1);
        return a;
    }
};

// BoxGacha(u32 gacha_id, u32 count): count at least 1, 1 when missing.
struct BoxGachaArgs {
    u32 gacha_id = 0, count = 1;
    static BoxGachaArgs from(const Request& r) {
        BoxGachaArgs a;
        a.gacha_id = (u32)int_at(r, 0);
        a.count = r.ints.size() > 1 ? std::max<u32>(1, (u32)r.ints[1]) : 1;
        return a;
    }
};

// ResetBoxGacha(u32 gacha_id); GetGachaRate(u32 gacha_id, const char*).
struct GachaIdArgs {
    u32 gacha_id = 0;
    static GachaIdArgs from(const Request& r) { return {(u32)int_at(r, 0)}; }
};

// Gacha(u32 gacha_id, const char* hash, u32 n), GachaOnce / SaleGacha / SaleGachaOnce (the same),
// GachaTicket(u32 gacha_id, u32 n, const char*): `n` is the second integer (0 when missing).
struct GachaArgs {
    u32 gacha_id = 0;
    u64 n = 0;  // Gacha: 1 = the single draw; GachaTicket: the draws
    static GachaArgs from(const Request& r) { return {(u32)int_at(r, 0), int_at(r, 1)}; }
};

// GetPresentArray(CSTLVector<u64> const& ids) / GetPresent(u64 id).
struct GetPresentArgs {
    std::vector<u64> present_ids;
    static GetPresentArgs from(const Request& r) {
        GetPresentArgs a;
        if (!r.vecs.empty()) a.present_ids = r.vecs[0];
        else if (!r.ints.empty()) a.present_ids.push_back(r.ints[0]);
        return a;
    }
};

}  // namespace soa::server::args
