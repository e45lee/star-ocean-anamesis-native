// Unit tests of the gear purification's pure rules (rules/gear_rules.h), against hand values.
// Run in --selftest; not differential (the server has no guest counterpart).
#include <cmath>

#include "soaserver/native_test.h"
#include "rules/gear_rules.h"

namespace soa::server {
namespace {

NATIVE_TEST("items/gear-rules") {
    // (b) CCustomGear::UpdatePurificationPlate: (int)((sum x 0.01 + 1) x (atk + int)) + 30 x sum
    t.expect_eq(gear_rules::rank_value(0, 0, 30), 0u, "nothing");
    t.expect_eq(gear_rules::rank_value(5, 0, 30), 150u, "one rarity-5 material, no base");
    t.expect_eq(gear_rules::rank_value(10, 200, 30), 520u, "base 200 x 1.1 + 300");
    t.expect_eq(gear_rules::rank_value(3, 333, 30), 432u, "truncated (342.99 -> 342) + 90");
    // (b) extraction chance min(p x sum x 0.01 + p, 100)
    if (std::fabs(gear_rules::extract_chance(50, 10) - 55.0f) > 1e-4f) t.fail("chance 50 + 10%%");
    if (std::fabs(gear_rules::extract_chance(50, 250) - 100.0f) > 1e-4f) t.fail("chance capped at 100");
}

}  // namespace
}  // namespace soa::server
