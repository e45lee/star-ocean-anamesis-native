#pragma once
// The growth APIs' request arguments by name (port code, not guest behaviour), as
// core/request_args.h does for the core's: each struct reads one method's positional arguments
// (docs/api.md's **Method** / **Request** lines), with the defaults the handlers used when one is
// missing (0; none of them logs).
#include "core/request_args.h"

namespace soa::server::args {

// BoostCharacter(u64 character_uid, u32 master_item_id, u32 count): `count` EXP items.
struct BoostCharacterArgs {
    CharacterUid character_uid;
    u32 master_item_id = 0, count = 0;
    static BoostCharacterArgs from(const Request& r) { return {CharacterUid(int_at(r, 0)), (u32)int_at(r, 1), (u32)int_at(r, 2)}; }
};

// LimitBreakCharacter(u64 character_uid, u32 id) and LimitBreakCharacter_Legacy: `id` is a
// master_character_limit_break row id (what the limit-break screen sends) or a master item id.
struct LimitBreakCharacterArgs {
    CharacterUid character_uid;
    u32 row_or_item_id = 0;
    static LimitBreakCharacterArgs from(const Request& r) { return {CharacterUid(int_at(r, 0)), (u32)int_at(r, 1)}; }
};

// EvolutionCharacter(u64 character_uid).
struct EvolutionCharacterArgs {
    CharacterUid character_uid;
    static EvolutionCharacterArgs from(const Request& r) { return {CharacterUid(int_at(r, 0))}; }
};

// UpdateAwakenLevel(u64 character_uid, u32 awaken_level): the level to reach.
struct UpdateAwakenLevelArgs {
    CharacterUid character_uid;
    u32 awaken_level = 0;
    static UpdateAwakenLevelArgs from(const Request& r) { return {CharacterUid(int_at(r, 0)), (u32)int_at(r, 1)}; }
};

// AddStatusCharacter(u64 character_uid, u32 master_item_id, u32 count): `count` seeds of one kind.
// (docs/api.md's Request line calls the two u32 "status kind" and "amount"; the server reads a
// seed item and a count, as the strengthening screen's preview does.)
struct AddStatusCharacterArgs {
    CharacterUid character_uid;
    u32 master_item_id = 0, count = 0;
    static AddStatusCharacterArgs from(const Request& r) { return {CharacterUid(int_at(r, 0)), (u32)int_at(r, 1), (u32)int_at(r, 2)}; }
};

// EquipWeapon / EquipAccessory(u64 character_uid, u64 item_uid): item 0 takes it off.
struct EquipItemArgs {
    CharacterUid character_uid;
    std::optional<ItemUid> item_uid;  // 0: none (take it off)
    static EquipItemArgs from(const Request& r) { return {CharacterUid(int_at(r, 0)), nonzero<ItemUid>(int_at(r, 1))}; }
};

// EquipSkill(u64 character_uid, u32 skill1, u32 skill2, u32 skill3): the three equipped skills,
// kept as the request's 64-bit integers (they are stored as they came).
struct EquipSkillArgs {
    CharacterUid character_uid;
    u64 skill[3] = {0, 0, 0};
    static EquipSkillArgs from(const Request& r) { return {CharacterUid(int_at(r, 0)), {int_at(r, 1), int_at(r, 2), int_at(r, 3)}}; }
};

// EquipAuto(u64 character_uid): the character the equipment screen's 自動設定 is for (b: a lambda
// among CPartyEquip's (@01d94a88) waits on EquipAuto's fid; the request has one u64, docs/api.md).
struct EquipAutoArgs {
    CharacterUid character_uid;
    static EquipAutoArgs from(const Request& r) { return {CharacterUid(int_at(r, 0))}; }
};

// ChangeRole(u64 character_uid, u32 master_role_id) (b: CRoleSelect's request lambda @01c72678:
// the screen's character, the role chosen).
struct ChangeRoleArgs {
    CharacterUid character_uid;
    RoleId role_id;
    static ChangeRoleArgs from(const Request& r) { return {CharacterUid(int_at(r, 0)), RoleId((u32)int_at(r, 1))}; }
};

// TrainMastery(u64 disciple_uid, u64 master_uid, u8 dojo_no, u32 step_type_id, u8 step, u8 option)
// (b: the two request lambdas; docs/server-rules.md#mastery):
//   - pairing (CMasteryTrainingSelect, @01ba2880): (+0x3530 the 弟子 card, +0x800 the 師匠 card,
//     the dojo index + 1, the pair's master_mastery_step type, 0, 0);
//   - a training (CMasteryTrainingConfirmationDialog::StartTraining's lambda @01b939e8):
//     (DojoInfo's disciple, its master, the dialog's first u8 + 1, the DojoInfo's type, the
//     disciple's cleared trainings + 1 (tCharaData+0x13ec), (the pass medal ? 4 : 1) + the
//     chosen training's index 0..2).
struct TrainMasteryArgs {
    CharacterUid disciple_uid, master_uid;
    u32 dojo_no = 0, step_type_id = 0, step = 0, option = 0;
    static TrainMasteryArgs from(const Request& r) {
        return {CharacterUid(int_at(r, 0)), CharacterUid(int_at(r, 1)), (u32)int_at(r, 2), (u32)int_at(r, 3), (u32)int_at(r, 4), (u32)int_at(r, 5)};
    }
};

// ResetMastery(u64, u64): the pair to part (師弟解消). (b) The two callers send it in either order:
// CMasteryTrainingSelect's lambda @01ba4910 (the 師匠 card +0x800, the 弟子 card +0x3530),
// CMasteryTrainingAllClearDialog's @01b94244 (its DojoInfo's two characters, master first as
// CMasteryTop::UpdateList builds it). The handler finds the pair either way.
struct ResetMasteryArgs {
    CharacterUid a, b;
    static ResetMasteryArgs from(const Request& r) { return {CharacterUid(int_at(r, 0)), CharacterUid(int_at(r, 1))}; }
};

}  // namespace soa::server::args
