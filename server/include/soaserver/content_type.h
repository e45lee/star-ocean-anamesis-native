#pragma once
// Content types (docs/history/PLAN-readability.md 2.3; port code, not guest behaviour): what a
// `content_type` column or response field names, the client's Common::ContentType.
// (a) The values and their meanings from the master rows that use them (docs/api.md "Content
// types", with an example content_id_label each); (b) CParameterUtility::CheckCommonContentTypeRange
// accepts values below 0x15 and 99.
#include <cstdint>

namespace soa::server {

enum class ContentType : uint32_t {
    kNone = 0,             // a master row's "nothing" (e.g. MaterialCompose's result_type 0)
    kItem = 1,             // a unique item: weapon / accessory (master_item; owned as CItemInfo with a uid)
    kCharacter = 2,        // a character (master_role)
    kFol = 3,              // FOL; num is the amount, content_id 0
    kFreeCoin = 4,         // free coins (紋章石); num is the amount, content_id 0
    kStackItem = 5,        // a stack item: materials, limit-break items, gacha tickets as items
    kGachaTicket = 6,      // a gacha ticket (ticketgacha_role_0003)
    kMissionItem = 7,      // a mission ticket / battle consumable (ticketmission_0001, item_bomb_01)
    kGrowthMaterial = 8,   // EXP / evolution materials (item_exp_all_01, item_revo_shot_01)
    kEventCoin = 9,        // an exchange currency (event coins: item_coin_118)
    kHealItem = 10,        // a stamina heal item (item_heal_50)
    kPremiumPass = 11,     // a premium login bonus pass (premiumlogin_bonus_2020_02)
    kStamp = 12,           // a chat stamp (stamp_1135)
    kTitle = 13,           // a title (title_scenario_0073)
    kGear = 15,            // a gear (item_gear_sword_50_1_000280)
    kFavorItem = 16,       // a favor item (item_favor_up_09)
    kDecoObject = 17,      // a deco object (de01head_049a)
    kDecoHair = 18,        // a deco hair colour (deco_hair_010101)
    kPass = 20,            // a pass / subscription product (pshop_galaxypass_001)
    kGearLottery = 98,     // a gear-drop lottery (a master_gear_lottery category: gear_drop_1)
    kItemSet = 99,         // an item set (master_item_set; expands to its contents)
};

// The number a column, a request or a response holds.
constexpr uint32_t to_u32(ContentType type) { return static_cast<uint32_t>(type); }
// A column's or a request's number as a content type (any number: unknown ones stay as they are).
constexpr ContentType as_content_type(uint64_t v) { return static_cast<ContentType>(static_cast<uint32_t>(v)); }
// The stack items (owned as a count, CStackItemInfo): 5..10 and 16 (a).
constexpr bool is_stack_item(ContentType type) {
    return (type >= ContentType::kStackItem && type <= ContentType::kHealItem) || type == ContentType::kFavorItem;
}

}  // namespace soa::server
