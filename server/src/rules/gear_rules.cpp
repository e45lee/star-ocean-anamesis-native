// The gear purification's pure rules (rules/gear_rules.h). Port code, not guest behaviour.
#include "rules/gear_rules.h"

#include <algorithm>

namespace soa::server::gear_rules {

u32 rank_value(u32 rarity_sum, u32 base_attack_int, u32 rare_factor) {
    // (b) CCustomGear::UpdatePurificationPlate
    float f = (float)rarity_sum * 0.01f;
    return (u32)(int)((f + 1.0f) * (float)base_attack_int) + rare_factor * rarity_sum;
}

float extract_chance(u32 p, u32 rarity_sum) {
    // (b) the same function
    return std::min((float)(p * rarity_sum) * 0.01f + (float)p, 100.0f);
}

}  // namespace soa::server::gear_rules
