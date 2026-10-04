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

}  // namespace soa::server::args
