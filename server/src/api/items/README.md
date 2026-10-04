# api/items: items and gear

Owned weapons and accessories (the state's `items`), stack items (`stock`, through `core/wallet`), stamina refills, and the gear of the weapon custom screens. Port code, not guest behaviour: every rule carries its source label (a)-(d) in the code, and the handlers carry the doc block of `../../../PLAN-readability.md` 2.5.

| File | Module | What |
|---|---|---|
| `items.h` | | what the two modules share: `item_type::` (master_item types 1 / 3 / 10), `uid_list` (the uid-list argument), `item_equipped` (the one "worn by a character" query) |
| `items.cpp` | `items` | ItemCompose(Array), ItemGradeUp(Array), MaterialCompose, SellItem(Array) / SellStackItem, LockItem(Array) / UnlockItem(Array), UseHealItem, StaminaHeal; the item rules of `../../rules/growth_rules.h` (`compose_points`, `item_level`, `sell_price`, `heal_points`) |
| `gear.cpp` | `gear` | GetGearInfo, ClearNewGear, AttachGear, RemoveGear, SellGear, UpdateGearStock, GenerateGear (the purification, as named steps); the hooks below; the purification's formulas are `../../rules/gear_rules.{h,cpp}` |
| `new_flags.cpp` | `new_flags` | ClearNewCharacter, ClearNewItem, ClearNewStackItem: the NEW badges (`roster.is_new`, `items.is_new`, `stock.is_new`, schema step 13; sent as the player state lists' `is_new`) |
| `items_tests.cpp` | | `items/apis` (compose with a copy, lock / sell, stack sale, heal items, StaminaHeal; moved from `growth/apis`), `items/limit-break-achievement` (type 6 counts raises), `items/limit-break-items` (hammers: generic, ALL, family, the accessory thread, one that doesn't fit, the cap) |
| `new_flags_tests.cpp` | | `items/new-badges` (the seed not new; a granted weapon, character and first stack new in the lists; the three ClearNew* clear owned ids only; more of a held stack isn't new again) |
| `gear_tests.cpp` | | `items/gear-apis`, `items/gear-barney-chance` (`../../rules/gear_rules_tests.cpp`: `items/gear-rules`) |

**APIs** (`../../../API-INDEX.md` has the fids): the seventeen above, registered in `register_items()`, `register_new_flags()` and `register_gear()` (`../../core/modules.cpp`).

**Hooks** (`soa-server --list-hooks`): `gear` adds each weapon's `AttachedGearInfoList` (ItemExtra), the content grants 15 (a gear item) and 98 (a gear lottery) (Grant), and `GearInfoList` + `GearBarneyChanceInfo` on every full-state response (OnPlayerLoad).

**State:** `items` (the core's: uid, master item, type, boosted points `exp`, limit break, level, lock), `stock` (`core/wallet`), the player's FOL and coins (`core/wallet`), `counters` (`weapon_boost`, `accessory_boost`; `weapon_limit_break`, `accessory_limit_break`: the limit-break raises, one per copy or fitting limit-break item ("hammer") fed; `weapon_grade_up`, `gear_attach`, `gear_generate`), and the module's `gear_items`, `gear_barney` (every table is created by `../../state/schema.cpp`). Since PLAN-schema S5 (schema version 5) `items` and `gear_items` are STRICT; `gear_items.item_uid` is the weapon the gear is set in, NULL for the gear box (0 before), read as `std::optional<ItemUid>` and sent as 0 (`player_item_id`); it references `items` ON DELETE CASCADE, so a gear set in a weapon that is gone goes with it (the gear list deleted it by hand before), and one gear per weapon slot (unique index `gear_items_slot`). Gear uids are `GearUid`, weapon uids `ItemUid`, master items `MasterItemId` (`soaserver/ids.h`); the request lists that mix gear and weapon uids (RemoveGear's argument, GenerateGear's materials) stay numbers until they are looked up.

**Rules:** docs/server-rules.md#weapons-and-accessories, docs/server-rules.md#items-and-stamina, docs/server-rules.md#stamina, docs/server-rules.md#gear, docs/server-rules.md#growth-screen-fixes. **Tests:** the ones above; the item APIs also run with real arguments in the `items-party` replay corpus, ItemCompose with limit-break items in `hammers` (`../../../tests/replay/`). **Session:** `port/scripts/growth_session.sh` (weapon custom: AttachGear, RemoveGear, GenerateGear; it reads their log lines); `port/scripts/badges_session.sh` (the NEW badges: ClearNewCharacter, in-process and `--server`, and after a re-login).
