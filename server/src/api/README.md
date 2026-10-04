# server/src/api: the modules, by domain

One folder per API group of `docs/api.md`, so the catalogue, the code and the rules share one vocabulary (`../../PLAN-readability.md` section 2.1). Each module file registers its handlers and hooks from its `register_<module>()` function, called in `../core/modules.cpp`'s order; `../../API-INDEX.md` maps every API to its handler and lists the hooks in run order. The core's own APIs are here too (step R8 moved them out of `../core/server.cpp`), registered first with `ext::add_core_api`: the entry flow in `entry/`, the player load, parties and home character in `player/`, the missions in `missions/`, the gacha in `gacha/`, the present box in `presents/`, the favor APIs in `favor/favor_api.cpp`.

| Folder | What |
|---|---|
| `campaign/` | the story campaign (ActiveMissionList, the world map), called around each request by the request lifecycle (`../core/lifecycle.cpp` `server::answer`) |
| `daily/` | login bonus (+ achievements, for now), premium and favor login bonuses, StaminaHealByFavor |
| `debug/` | the `Debug*` APIs, stubs (`ext::add_stub`) |
| `deepspace/` | deep space expeditions |
| `entry/` | the entry flow: Login, CreatePlayer, the tutorial, terms, name, server time (core) |
| `events/` | event missions, campaigns' client dates, rankings, world boss, favor drop, enable-events |
| `favor/` | favorability rules; UpdateFavorByTap, UseFavorItem (core) |
| `gacha/` | the draws, GetGachaInData, step-up chains, box gacha, the rate dialog (core) |
| `growth/` | BoostCharacter … EquipSkill |
| `items/` | compose, grade up, sell, lock, heal items; gear |
| `missions/` | MissionStart, MissionEnd, the drop roll, master_campaign, the play state (core) |
| `player/` | the player state and its load (core), parties, assist and home character (core), home footer, titles, the notice page |
| `presents/` | PresentList, GetPresent(Array) (core), present texts |
| `shop/` | item shop, exchange, subscriptions (passes) |
| `social/` | follow lists and rental helpers; the follow menu's lists (Blacklist, GetRecentlyPlayedList, SearchPlayer); the social calls' stubs (Follow*, Blacklist*, UpdateFollowMax, Neighbor*, LocationRegist) |
| `sphere211/` | Sphere 211 |
| `tower/` | the tower (`--restore-tower`) |
