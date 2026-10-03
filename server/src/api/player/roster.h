#pragma once
// The roster as the client receives it (port code, not guest behaviour): CPersonInfo, one owned
// character, and the `Character` list of every owned character (api/player/roster.cpp).
#include "soaserver/ext.h"

namespace soa::server {

// One owned character (CPersonInfo) from its `roster` row; `owner_player_id` is its player_id key.
Value person_info(ext::Ctx& ctx, const ext::Row& roster_row, u32 owner_player_id);
// Character: every owned character (CPersonInfo), by uid.
Value roster_info(ext::Ctx& ctx);
// Whether the character of `roster_row` has growth: a seed's add_* raised (AddStatusCharacter) or
// an equipped skill (EquipSkill). The replies send add_* (CPersonInfo, CPersonStatusInfo) and the
// equipped skills (UpdateCharacter) only then: before PLAN-schema S4 they lived in roster_ext, a
// row of which only those two APIs made, and the replies sent them when it existed. The one case
// this reads differently from that row: one whose seeds and skills are all 0 (EquipSkill(0,0,0),
// or a seed at its cap on a character without growth) sent them as 0, and now leaves them out.
bool has_growth(const ext::Row& roster_row);

}  // namespace soa::server
