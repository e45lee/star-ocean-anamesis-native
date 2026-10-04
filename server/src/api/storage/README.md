# api/storage: the equipment storage and the overflow box

The item menu's 装備倉庫 (equipment storage: deposit, withdraw, sell, lock) and 一時保管庫 (the
overflow box: equipment the full inventory had no room for). Port code, not guest behaviour: every
rule carries its source label (a)-(d) in the code, and the handlers carry the doc block of
`../../../PLAN-readability.md` 2.5.

| File | Module | What |
|---|---|---|
| `storage.h` | | what the rest of the server asks: `item_stock`, `storage_stock` (Player's caps), `inventory_count`, `to_one_time_storage` (whether a new piece of equipment goes to the box; the settings' options plug in there), `add_one_time` |
| `storage.cpp` | `storage` | GetStorageInfo, DepositItem, WithdrawItemFromStorage, SellItemsFromStorage, LockStorageItem / UnlockStorageItem; the caps |
| `one_time.cpp` | `storage` | GetOneTimeStorageInfo, WithdrawItemFromOneTimeStorage / BulkWithdrawItemFromOneTimeStorage, ClearNewOneTimeStorageItem; filling the box; the OnResponse hook that reports `AddOneTimeStorageInfo` |
| `storage_tests.cpp` | | `storage/deposit-withdraw`, `storage/sell-lock`, `storage/stock-caps`, `storage/one-time` |

**APIs** (`../../../API-INDEX.md` has the fids): the ten above, registered in `register_storage()`
(which calls `register_one_time_storage()`; `../../core/modules.cpp`).

**Hooks** (`soa-server --list-hooks`): OnResponse, `AddOneTimeStorageInfo` on any answer that put
equipment in the box. Who fills it: the core's `grant` (content type 1: presents, drops, shops, the
exchange; `../../core/rewards.cpp`) and the gacha's weapon draws (`../gacha/gacha.cpp`
`draw_weapon`, the box gacha through `grant`).

**State** (schema version 13): `items.stored_at` (NULL: in the inventory; else the deposit time, sent
as `update_at_time`; a stored item keeps its row, gear and lock) and `one_time_storage` (one row per
master item: `num`, `is_new`, `updated_at`).

**Rules:** docs/server-rules.md#storage. **Tests:** the ones above, `server/schema-migrate-v13`, the
`storage` replay corpus (`../../../tests/replay/storage`). **Session:** `port/scripts/storage_session.sh`
(in-process and `--target port-server`).
