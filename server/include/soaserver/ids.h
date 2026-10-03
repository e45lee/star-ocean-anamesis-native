#pragma once
// Typed ids (server/PLAN-readability.md 2.3, step R12; port code, not guest behaviour). An id names
// one kind of thing: an owned object (`*Uid`: a character, an item) or a master row (`*Id`). Each
// kind is its own type, so passing a RoleId where a CharacterUid is expected doesn't compile; the
// only way between a kind and its number is explicit (`CharacterUid(n)`, `.v`).
//
// "None": since PLAN-schema S4 the state's reference columns hold NULL for "none" (roster.weapon_uid
// / accessory_uid / assist_uid, player.home_uid / support_uid / title_id, roster.equip_skill1..3), and
// they read as std::optional<…> (sql::Row::opt). The wire still says "none" with 0 (or_zero). Columns
// not yet converted keep their 0 sentinel and read as a plain id with value 0 (sql::Row::id): party /
// party_member (until S6), gear_items.item_uid (0 = the gear box, until S5), the play / ds_ship uid
// lists (text, until S7), favor_bonus_state.lot_uid and gacha_history.uid (until S10).
//
// Kept public (beside sql.h) so the module API (soaserver/ext.h) and the SQL wrapper can use them;
// the uid scheme's constants are src/core/ids.h.
#include <compare>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>

namespace soa::server {

template <class Tag, class Rep>
struct Id {
    using rep = Rep;
    Rep v = 0;
    constexpr Id() = default;
    constexpr explicit Id(Rep value) : v(value) {}
    friend constexpr auto operator<=>(const Id&, const Id&) = default;
};

// An owned character (roster.uid), u64.
using CharacterUid = Id<struct CharacterUidTag, uint64_t>;
// An owned unique item: a weapon or an accessory (items.uid), u64.
using ItemUid = Id<struct ItemUidTag, uint64_t>;
// The player (CHash32 of the search id), u32.
using PlayerId = Id<struct PlayerIdTag, uint32_t>;
// master_role.id (a character's role), u32.
using RoleId = Id<struct RoleIdTag, uint32_t>;
// master_role.same_role_id (one character across its roles: favor, the home), u32.
using SameRoleId = Id<struct SameRoleIdTag, uint32_t>;
// master_item.id (and a weapon's / accessory's master id), u32.
using MasterItemId = Id<struct MasterItemIdTag, uint32_t>;
// master_mission.id, u32.
using MissionId = Id<struct MissionIdTag, uint32_t>;
// master_gacha.id, u32.
using GachaId = Id<struct GachaIdTag, uint32_t>;
// master_title.id, u32.
using TitleId = Id<struct TitleIdTag, uint32_t>;
// master_area.id, u32.
using AreaId = Id<struct AreaIdTag, uint32_t>;
// A master skill id (roster.equip_skill1..3), u32.
using SkillId = Id<struct SkillIdTag, uint32_t>;

// The wire's form of an optional reference: the id, or 0 for none (the client's "none").
template <class Tag, class Rep>
constexpr Rep or_zero(const std::optional<Id<Tag, Rep>>& id) {
    return id ? id->v : Rep(0);
}
// A wire / request value where 0 means none, as an optional reference.
template <class T>
constexpr std::optional<T> nonzero(typename T::rep v) {
    return v ? std::optional<T>(T(v)) : std::nullopt;
}

}  // namespace soa::server

template <class Tag, class Rep>
struct std::hash<soa::server::Id<Tag, Rep>> {
    size_t operator()(const soa::server::Id<Tag, Rep>& id) const noexcept { return std::hash<Rep>()(id.v); }
};
