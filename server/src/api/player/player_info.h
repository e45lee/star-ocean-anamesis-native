#pragma once
// The player state the client receives (port code, not guest behaviour): the builders of
// CPlayerInfo (Player), CWalletInfo (Wallet), CPersonInfo (Character), PartySetInfo (PartySet),
// CStackItemInfo (StockItem), CItemInfo (Item) and CPersonStatusInfo (a battle member), and the
// whole player state of Login / GetPlayer (api/player/player_info.cpp). Every value carries its
// source label there; docs/server-rules.md#player-load.
#include <string>
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

// (a) stamina regenerates one point per master_global stamina_heal_time seconds, up to
// master_player_level.stamina (writes the regenerated value).
void tick_stamina(ext::Ctx& ctx);
// data.Player (CPlayerInfo; the client keeps it at CParameterManager+0x638): the player's row, the
// stocks and the entry-flow state. Ticks the stamina first.
Value player_info(ext::Ctx& ctx);
// data.Wallet (CWalletInfo, CParameterManager+0x1f20): the free and paid coins.
Value wallet_info(ext::Ctx& ctx);
// The player's id (player.id: CHash32 of the search id; id 0 without a player).
PlayerId player_id(ext::Ctx& ctx);
Value stack_item_info_list(ext::Ctx& ctx);      // StockItem (CStackItemInfo list)
// Which owned items item_info_list lists.
struct ItemSelection {
    enum Kind { kInventory, kStored, kOne } kind = kInventory;
    ItemUid uid{};  // kOne: the item
    static ItemSelection inventory() { return {}; }  // not in the equipment storage
    static ItemSelection stored() { return {kStored, {}}; }  // in the equipment storage
    static ItemSelection one(ItemUid uid) { return {kOne, uid}; }  // the one item, stored or not
};
// Item (CItemInfo list): by default the inventory's items, those not in the equipment storage;
// api/storage/storage.cpp's StorageItem lists the stored ones, each with CStorageItemInfo's
// update_at_time, and UpdateStorageItem one item.
Value item_info_list(ext::Ctx& ctx, ItemSelection which = ItemSelection::inventory());
// {Time, Player, Wallet}: the player state every answer carries (ext::Ctx::base_data).
Value base_data(ext::Ctx& ctx);
// Which of soa-server's CDN keys (api/entry/entry.h add_cdn_paths) a full player state carries.
enum class CdnKeys {
    kNone,            // GetPlayer, NoLoginStart
    kAll,             // Login, SimpleLogin: AssetPath, MasterPath, r_ver, LatestEpisodeVersion, a_ver
    kAppVersionOnly,  // CreatePlayer: a_ver
};
// The whole player state of Login / SimpleLogin / CreatePlayer / GetPlayer / NoLoginStart: Player,
// Wallet, the roster, the party sets, the stocks and items, the favor state and the modules'
// OnPlayerLoad keys (docs/server-rules.md#player-load). Stamps last_login_at.
std::vector<u8> full_player_state(ext::Ctx& ctx, const Request& req, CdnKeys cdn = CdnKeys::kNone);
// The home character's master_role.same_role_id (id 0 when none: the favor module's "none").
SameRoleId home_same_role(ext::Ctx& ctx);

}  // namespace soa::server
