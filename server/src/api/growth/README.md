# api/growth: character growth

| File | What |
|---|---|
| `growth.cpp` (module `growth`) | the growth APIs, each with its doc block (signature, fid, rules with their labels, refusal codes, answer) |
| (`../gen/request_args.h`) | their request arguments by name (`args::BoostCharacterArgs`, ...), generated from `../gen/request_args.txt` and the measured wire layouts (`../gen/README.md` "Requests") |
| `mastery.cpp` (module `mastery`) | マスタリー (師弟): GetMasteryInfo, TrainMastery, ResetMastery; the inheritance (`mastery_inheritance`, `mastery_talent_of`) the roster, the battle status and UpdateAwakenLevel send |
| `mastery_tests.cpp` | `growth/mastery-pairing`, `growth/mastery-training`, `growth/mastery-awakening`, `growth/change-role` |
| `growth_tests.cpp` | `growth/equip-auto` (EquipAuto: the weapon of the role's kind, an accessory nobody wears, the skills); `growth/apis`: Boost, LimitBreak (by item and by the screen's row id), Evolution, AddStatus on a scratch server, with refusals (`server/economy-apis` is gone: its login bonus and achievement parts are `daily/login-bonus` and `presents/achievement-chain` since R16, its shop and exchange part `shop/item-shop-and-exchange` in `api/shop/shop_tests.cpp` since R18) |

| API | Handler | Rules (docs/server-rules.md) |
|---|---|---|
| BoostCharacter | `boost_character` | "5.1 Character EXP and level", "Character growth" |
| LimitBreakCharacter, LimitBreakCharacter_Legacy | `limit_break_character` (+ `limit_break_items`) | "5.2 Limit break", "Fixes found on the growth screens" |
| EvolutionCharacter | `evolution_character` | "5.3 Evolution", "Fixes found on the growth screens" |
| UpdateAwakenLevel | `update_awaken_level` | "5.4 Awakening, skills, mastery, universe" |
| AddStatusCharacter | `add_status_character` | "5.1 Character EXP and level" (seeds) |
| EquipWeapon, EquipAccessory | `equip_item` | "Character growth" |
| EquipSkill | `equip_skill` | "Character growth" |
| EquipAuto | `equip_auto` | "Auto-equip" |
| ChangeRole | `change_role` | "Role change" (#role-change) |
| GetMasteryInfo, TrainMastery, ResetMastery | `get_mastery_info`, `train_mastery`, `reset_mastery` (`mastery.cpp`) | "Mastery" (#mastery) |

- **Hooks:** none; the modules register their APIs (`register_growth`, `register_mastery`, in `core/modules.cpp`'s order). Its state is the core's `roster` (`state/schema.cpp`).
- **Pure rules:** `rules/growth_rules.{h,cpp}` (`growth_rules::boost_exp`, `stat_seed_gain`; tested by `rules/growth`), `rules::add_exp` (the EXP curve and cap).
- **State:** `roster` (level, exp, limit break, awakening, role, equipment: the core's table), the seed-raised `add_*` and the equipped skills `equip_skill1..3` (`roster` columns since PLAN-schema S4 merged the module's `roster_ext`; NULL: no skill), `stock` and the player's FOL (`core/wallet`), `counters` (boosts, limit breaks, evolutions, seeds: the achievements read them).
- **Mastery state:** `mastery` (schema version 17): one 師弟 pair per disciple, its dojo, type and the five trainings' cards.
- **What reads it back:** `Character` (`api/player/roster.cpp`: `add_*`), the battle status (`api/player/person_status.cpp`: level, limit break, awakening, equipment, seeds).
- **Proof and sessions:** the replay corpus `server/tests/replay/growth` (every API, accepted and refused); `port/scripts/growth_session.sh` (the growth screens on 3.7.0: strengthening, evolution, limit break; it reads the BoostCharacter / EvolutionCharacter / LimitBreakCharacter log lines).
