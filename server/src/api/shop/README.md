# api/shop: shops and passes

| File | Module | What |
|---|---|---|
| `shop.cpp` | `shop` | **ItemShopList** (`item_shop_list_api`), **ExItemShop** (`ex_item_shop`: `buy_item_shop_row`), **ExshopExchangeList** (`exshop_exchange_list`), **ExshopExchange** (`exshop_exchange`: `exchange_refusal`, `exchange_data`); the builders `item_shop_info` (CItemShopInfo), `item_shop_list` (ItemShopInfoList), `exchange_counts` (ExchangeShopExCount); the args structs `args::ExItemShopArgs`, `args::ExshopExchangeArgs`; the exchange shops on the event calendar (`exchange_window_open`, `client_master_shops`: the `ClientMaster` hook); the shop state on every full player load (`load_shops`: `OnPlayerLoad`). The periods are `rules/growth_rules.h`'s `shop_period_start` |
| `subscription.{h,cpp}` | `subscription` | passes (namespace `subscription`): `grant_plan`, the `Grant` hook for content type 20 (`kContentTypePass`), `--galaxy-pass` (`keep_galaxy_pass`), `Subscription` / `SubscriptionPlan` (`subscription_info`, `subscription_plan_info`; the `OnPlayerLoad` hook `load_subscriptions`); `ext::subscription_active` / `ext::subscription_state` for deep space |
| `coins.cpp` | `coins` | paid currency (docs/server-rules.md#paid-currency): **CoinList** (`coin_list_api`), **CoinDepositCreate** (`coin_deposit_create`), **CoinDepositAndroidUpdate** / **CoinDepositIOSUpdate** / **CoinDepositAmazonUpdate** (`coin_deposit_update`), **DirectItemShopList** (`direct_item_shop_list`, empty); the products from `master_text`'s coin labels (`products`, `coin_info`, `coin_list`); `CoinList` on every full player load (`load_coin_list`: `OnPlayerLoad`) |
| `coins_tests.cpp` | | `shop/coins` (the products, a purchase credited paid + free and recorded, a retry not credited twice, the refusals, the iOS / Amazon updates, the list methods) |
| `shop_tests.cpp` | | `shop/item-shop-and-exchange` (a monthly row bought, sold out, a new period; an exchange paid, granted, counted), `shop/subscription` (a pass granted, extended, expired; `--galaxy-pass` renewing it) |

Every handler and hook carries the 2.5 doc block. Item sets (content type 99) are expanded by `core/rewards.h` `grant_with_item_sets` (shared with the event ranking rewards).

**Hooks and their order** (`../../core/modules.cpp`; `soa-server --list-hooks`): `shop` registers its schema, its four APIs, the `ClientMaster` hook and its `OnPlayerLoad` (`ItemShopInfoList`, `ExchangeShopExCount`); `subscription` its schema, `Grant` 20 and its `OnPlayerLoad` (`Subscription`, `SubscriptionPlan`). `coins` (registered last) its five APIs and its `OnPlayerLoad` (`CoinList`).

**State** (`server.sqlite3`; the tables are `../../state/schema.cpp`'s, STRICT since PLAN-schema S10; `../../../PLAN-schema.md` section 1): `shop_counts` (per item-shop row: this period's count, the period, the count ever), `exchange_counts` (per contents row: the count exchanged; its shop is the master's, the `shop_id` column went in S2), `subscription` (per plan: opened_at, closed_at, updated_at), `coin_deposit` (per purchase: product, platform, started / completed, the stones credited; schema step 18); the wallet (`player.free_coin` / `pay_coin`), `stock` (event coins, the exchanged items), `counters` (`exchange`, for the achievements).

**Rules**: docs/server-rules.md#shops, docs/server-rules.md#shops-modules (under "Growth and economy"), "Exchange shops on the event calendar", "Passes (subscriptions)", "Enabling events by keyword" (the enabled events' shops).

**Proof and sessions**: the replay corpora `economy` (item-shop rows to their limit and refused, the exchange shop accepted and refused, `--galaxy-pass`) and `growth` (four item-shop sets); `port/scripts/deepspace_session.sh` (runs with `--galaxy-pass`: the pass ships).
