#pragma once
// The gear purification's pure rules (port code, not guest behaviour): the two formulas
// CCustomGear::UpdatePurificationPlate shows on the purification screen. The handler is
// GenerateGear (api/items/gear.cpp); docs/server-rules.md#gear. Labels: (a) master data,
// (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include <cstdint>

namespace soa::server::gear_rules {

using u32 = uint32_t;

// The purification's rank value, (b) CCustomGear::UpdatePurificationPlate:
//   (int)((sum of material rarities x 0.01 + 1.0) x (base attack + base intelligence))
//   + master_global rare_factor_for_normal_gear x (sum of material rarities)
// (float arithmetic, as the client). The master_gear_probability row used is the one with the
// largest rank_threshold below it.
u32 rank_value(u32 rarity_sum, u32 base_attack_int, u32 rare_factor);

// The factor extraction chance in percent, (b) the same function: min(p x sum x 0.01 + p, 100),
// p = the base weapon's extraction rate, sum = the materials' rarities.
float extract_chance(u32 p, u32 rarity_sum);

}  // namespace soa::server::gear_rules
