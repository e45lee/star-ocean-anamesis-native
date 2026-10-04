#pragma once
// Mastery (マスタリー, 師弟): GetMasteryInfo, TrainMastery, ResetMastery (api/growth/mastery.cpp).
// Port code, not guest behaviour; the rules are in docs/server-rules.md#mastery.
#include "soaserver/ext.h"

namespace soa::server {

// What a disciple inherited from its master, as CPersonInfo / CPersonStatusInfo carry it
// (parent_master_role_id, mastery_talent_id): both 0 unless the pair cleared all five trainings
// (b: tCharaData::InitializeMastery takes a non-zero parent role as a finished training).
struct MasteryInheritance {
    bool graduated = false;
    u32 parent_master_role_id = 0;
    u32 mastery_talent_id = 0;
};

// The character `uid`'s inheritance (graduated = false when it is no graduated disciple).
MasteryInheritance mastery_inheritance(ext::Ctx& ctx, CharacterUid uid);

// The master's talent a disciple inherits: the talent in the master role's
// master_role.mastery_talent_slot, from master_awaken (the role's category at `awaken_level`)
// when that row sets the slot, else from master_role (0: none). Exposed for UpdateAwakenLevel
// (api/growth/growth.cpp), which reports the change to a graduated disciple.
u32 mastery_talent_of(ext::Ctx& ctx, RoleId master_role, u32 awaken_level);

// The disciple whose graduated master is `master_uid` (none: no such pair), for UpdateAwakenLevel.
std::optional<CharacterUid> graduated_disciple_of(ext::Ctx& ctx, CharacterUid master_uid);

// GetMasteryInfo / TrainMastery / ResetMastery (their doc blocks are in mastery.cpp). Public for the tests.
std::vector<u8> get_mastery_info(ext::Ctx& ctx, const Request& req);
std::vector<u8> train_mastery(ext::Ctx& ctx, const Request& req);
std::vector<u8> reset_mastery(ext::Ctx& ctx, const Request& req);

}  // namespace soa::server
