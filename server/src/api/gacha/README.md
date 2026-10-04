# api/gacha: the gacha

| File | Module | What |
|---|---|---|
| `gacha.h` | | the domain's functions: `gacha_open`, the step-up and box builders, the handlers |
| `gacha.cpp` | `gacha` (core) | **GetGachaInData** (`get_gacha_in_data`: the open banners' GachaHashMap, StepUpGacha, BoxGachaList); the draws **Gacha, GachaOnce, SaleGacha, SaleGachaOnce, GachaTicket** (`gacha`, as named steps over a `GachaDraw`: `count_and_price`, `check_stepup`, `pay_draw`, `draw_units` (`draw_weapon`, `add_drawn_role`, `add_limit_break`, `add_chips`), `gacha_data` (`advance_stepup`)): price and currency (free coins first; `core/wallet.h`), rank rates, a unit from the reconstructed pools (`ctx.pools`, `master/gacha_pools.h`) or by rarity (`draw_role`), duplicates, limit breaks, character chips, the step-up advance |
| `stepup.cpp` | | step-up chains: `stepup_chain`, `stepup_closed`, `stepup_gacha_info` (StepUpGacha: CStepUpGachaInfoList, a map keyed by step) |
| `box.cpp` | `box_gacha` (core) | **BoxGacha** (`box_gacha`: `box_ticket`, `draw_slots`, `refill_last_box`), **ResetBoxGacha**, **GetBoxGacha**; the box slots and series, `box_gacha_info` (BoxGacha: CBoxGachaInfo map keyed by slot) and `box_gacha_list_info` (BoxGachaList: CBoxGachaListInfo map keyed by box) |
| `rates.cpp` | `gacha_rate` (core) | **GetGachaRate** (`get_gacha_rate`): the rate dialog from the pools (`gacha_rate_from_pools`, CGachaRateInfo pages); the player state only without them |
| `gacha_tests.cpp` | | `gacha/stepup-box` (step-up order and shape, single / bulk draws, chips, coins short, a box series drawn, refilled and reset, the box list), `gacha/enable-events` (`--enable-events` opens the matching banners) |

Every handler carries the 2.5 doc block (signature, fid, API and rules links, the rules with their labels, the refusal codes, the answer). The core's APIs register with `ext::add_core_api`, before the modules; no hook adds keys to their responses.

**State** (`server.sqlite3`; the tables are `../../state/schema.cpp`'s, STRICT with their foreign keys since PLAN-schema S10): `gacha_history` (one row per unit drawn; the achievements count it; a character draw's `role_id` and `character_uid`, a weapon draw's `item_uid` with `role_id` NULL, each → `roster` / `items` ON DELETE SET NULL; one `uid` column, `role_id` 0 for a weapon, until S10), `stepup` (per chain: `next_id` the current step, `try_count`, `restart_count`; no row = step 1), `box_state` (per box: `total_count`, `reset_count`), `box_slots` (per slot: copies drawn; → `box_state` ON DELETE CASCADE, so BoxGacha writes the box's row before its slots), the wallet (`player.free_coin` / `pay_coin`), `stock` (tickets, chips), `roster` and `items` (the units).

**Rules**: docs/server-rules.md#gacha-rules (4.1 what's open, 4.2 cost, 4.3 rates and pool, 4.4 step-up and box, 4.5 the reconstructed pools), "Gacha: step-up and box", "Step-up gacha state", "Single and bulk draws of `Gacha`", "Step-up and box gacha lists".

**Proof and sessions**: the replay corpora `economy` (GachaTicket, a step-up chain in and out of order, single / bulk / sale / weapon draws, GetGachaRate, a box series drawn to its refilling last box, resets) and `seeded` (a 10-draw); `port/scripts/gacha_session.sh` (reads "GetGachaInData: N gachas open" and "Gacha N (label): 10 draws for"), `restore_missions.sh` (the step-up steps: "step-up chain N step 1 -> 2"), `emulator/scripts/summer_demo.sh` and `nier_demo.sh` (the draw line).
