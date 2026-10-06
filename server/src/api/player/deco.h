#pragma once
// Character decorations (キャラデコ): the owned decorations, their favourites and each character's
// setting (api/player/deco.cpp). Port code, not guest behaviour; docs/server-rules.md#deco.
#include "soaserver/ext.h"

namespace soa::server {

// (d) uid scheme: the owned decorations' ids (CDecoObjectInfo.id) are kDecoUid0 + the row's id.
constexpr u64 kDecoUid0 = 0x7b000000;

// The decoration keys of one character's CPersonInfo (hair_id, pose_id, CharacterDecoObject),
// added to `info` when the character has a setting (SetCharacterDeco); nothing otherwise.
void add_character_deco(ext::Ctx& ctx, CharacterUid uid, Value& info);

// GetDecoInfo / SetCharacterDeco / FavoriteDecoObject / UnFavoriteDecoObject (their doc blocks are
// in deco.cpp). Public for the tests.
std::vector<u8> get_deco_info(ext::Ctx& ctx, const Request& req);
std::vector<u8> set_character_deco(ext::Ctx& ctx, const Request& req);
std::vector<u8> favorite_deco_object(ext::Ctx& ctx, const Request& req);
// Grants one decoration (content types 17 and 18, the ext::add_grant hooks); false when owned already.
bool grant_deco(ext::Ctx& ctx, u32 master_deco_id);

}  // namespace soa::server
