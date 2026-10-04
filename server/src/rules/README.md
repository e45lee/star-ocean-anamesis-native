# server/src/rules: pure game rules

Functions over values, no DB and no request, unit-tested on their own. The domain steps of `../../PLAN-readability.md` (R13, R18) gather the rest here as `rules::<domain>` (`rules::deepspace` since R18; `gear_rules` is here since R13).

| File | What |
|---|---|
| `rules.cpp` | `rules::` of `soaserver/server.h` (public: the port's tests use them): `weighted_pick`, `add_exp`, `round_half_away`, `interpolate_level`, `regen_stamina` |
| `mission_rules.{h,cpp}` | `mission_rules::`: the mission tables, the surprise roll, campaign windows and stamina, evaluation ranks, the step-up and box gacha picks (docs/server-rules.md#server-missions; the handlers are in `../api/missions/`) |
| `deepspace_rules.{h,cpp}` | `rules::deepspace`: the deep space bonus curve, the quick-return price, the play limits and their week (docs/server-rules.md#deepspace; the handlers are in `../api/deepspace/`) |
| `gear_rules.{h,cpp}` | `gear_rules::`: the gear purification's rank value and factor extraction chance, the client's own formulas (`CCustomGear::UpdatePurificationPlate`; docs/server-rules.md#gear; the handler is `../api/items/gear.cpp`'s GenerateGear); tests `gear_rules_tests.cpp` (`items/gear-rules`) |
| `growth_rules.{h,cpp}` | `growth_rules::`: character growth (boost EXP, seeds), item compose / level / sale price, stamina heals, the item shop's monthly period, the login-bonus day (docs/server-rules.md#growth-rules, docs/server-rules.md#growth-and-economy; the handlers are in `../api/growth/`, `../api/items/`, `../api/shop/`, `../api/daily/`). The namespace keeps its name until its callers' domain steps rename it `rules::growth` (2.2) |

Tests: `deepspace_rules_tests.cpp` (`rules/deepspace`), `growth_rules_tests.cpp` (`rules/growth`), `mission_rules_tests.cpp` (`rules/missions`), `rules_tests.cpp` (also `rules::`'s: `server/weighted-pick`, `server/add-exp`, `server/level-interpolation`, `server/stamina`); `soa-server --selftest "rules/"`.
