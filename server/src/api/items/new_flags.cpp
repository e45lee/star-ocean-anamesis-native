// Local server: the NEW badges of owned characters, weapons / accessories and stack items
// (ClearNewCharacter, ClearNewItem, ClearNewStackItem). Rules in docs/server-rules.md#new-badges;
// labels: (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// The flags are the state's roster.is_new, items.is_new and stock.is_new (schema step 13): a row
// gained after that step is new until the client clears it; the player state sends them as the
// lists' is_new (api/player/roster.cpp roster_info, api/player/player_info.cpp item_info_list /
// stack_item_info_list).
#include "api/items/items.h"
#include "core/log.h"
#include "core/modules.h"
#include "core/response.h"
#include "soaserver/ext.h"

namespace soa::server {
namespace {
using namespace ext;

// ClearNewCharacter(vector<u64> character uids) -> ClearNewCharacterRes      fid 36ce009c
// API: docs/api.md#clearnewcharacter
// Rules: docs/server-rules.md#new-badges
//
// The client viewed new characters (CParameterUtility::tCharaData::ClearNewStatus,
// CPartyComposition::Progress).
//   (b) OnClearNewCharacterRes (@014d2ef8) copies each UpdateCharacterList entry's is_new (its
//       CUpdateCharacterInfo +0x2a0) into the Character with the same id (+0x400); the entry's
//       keys are CUpdateCharacterInfo::Initialize's (@0163f48c) `id` (u64) and `is_new` (u32).
//   (d) Only owned characters are listed and cleared; an unknown uid is skipped.
// Answers: the player state {Time, Player, Wallet} with UpdateCharacterList [{id, is_new: 0}].
std::vector<u8> clear_new_character(Ctx& ctx, const Request& req) {
    Value data = ctx.base_data(), list = Value::array();
    for (u64 uid : uid_list(req)) {
        if (!ctx.st.one("select count(*) from roster where uid = ?", {CharacterUid(uid)})) continue;
        ctx.st.q("update roster set is_new = 0 where uid = ?", {CharacterUid(uid)});
        Value e = Value::object();
        e["id"] = uid;
        e["is_new"] = 0u;
        list.push(e);
    }
    LOGI("server", "ClearNewCharacter: %zu character(s)", list.arr.size());
    data["UpdateCharacterList"] = list;
    return body(data);
}

// ClearNewItem(vector<u64> item uids) -> ClearNewItemRes                     fid 22b15407
// API: docs/api.md#clearnewitem
// Rules: docs/server-rules.md#new-badges
//
// The client viewed new weapons / accessories (the item lists, the party's weapon and accessory
// lists, the weapon custom and the storage screens).
//   (b) OnClearNewItemRes (@014d28a8) reads ItemClearNewList as a list of ids (one u32 each) and
//       sets is_new = 0 (+0x240) on the Item of each (its id compared as a u32).
//   (d) Only owned items are listed and cleared; an unknown uid is skipped.
// Answers: the player state with ItemClearNewList [uid...].
std::vector<u8> clear_new_item(Ctx& ctx, const Request& req) {
    Value data = ctx.base_data(), ids = Value::array();
    for (ItemUid uid : item_uid_list(req)) {
        if (!owns_item(ctx, uid)) continue;
        ctx.st.q("update items set is_new = 0 where uid = ?", {uid});
        ids.push(uid.v);
    }
    LOGI("server", "ClearNewItem: %zu item(s)", ids.arr.size());
    data["ItemClearNewList"] = ids;
    return body(data);
}

// ClearNewStackItem(vector<u32> master item ids) -> ClearNewStackItemRes      fid aabac605
// API: docs/api.md#clearnewstackitem
// Rules: docs/server-rules.md#new-badges
//
// The client viewed new stack items (CItemPossessionList::ClearIsNewStackItem).
//   (b) OnClearNewStackItemRes (@014d2bd0) reads StackItemClearNewList as a list of master item
//       ids (u32) and sets is_new = 0 (+0x120) on the StockItem of each.
//   (d) Only held stack items (a stock row) are listed and cleared.
// Answers: the player state with StackItemClearNewList [master item id...].
std::vector<u8> clear_new_stack_item(Ctx& ctx, const Request& req) {
    Value data = ctx.base_data(), ids = Value::array();
    for (u64 id : uid_list(req)) {
        if (!ctx.st.one("select count(*) from stock where master_item_id = ?", {MasterItemId((u32)id)})) continue;
        ctx.st.q("update stock set is_new = 0 where master_item_id = ?", {MasterItemId((u32)id)});
        ids.push((u32)id);
    }
    LOGI("server", "ClearNewStackItem: %zu stack item(s)", ids.arr.size());
    data["StackItemClearNewList"] = ids;
    return body(data);
}

}  // namespace

// The module's registrations (src/core/modules.cpp calls this; server/ARCHITECTURE.md "The module
// registry and its order").
void register_new_flags() {
    ext::add_api({"ClearNewCharacter"}, clear_new_character);
    ext::add_api({"ClearNewItem"}, clear_new_item);
    ext::add_api({"ClearNewStackItem"}, clear_new_stack_item);
}

}  // namespace soa::server
