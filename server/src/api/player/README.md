# api/player: the player state, parties, home and profile

What the client keeps about the player (CPlayerInfo, CWalletInfo, the roster, the party sets, the stocks and items), the whole player load of the login, and the home's own APIs and keys.

| File | Module | What |
|---|---|---|
| `player_info.{h,cpp}` | `player` (core) | the player state the client receives: `player_info` (CPlayerInfo, Player), `wallet_info` (CWalletInfo), `stack_item_info_list` (CStackItemInfo, StockItem), `item_info_list` (CItemInfo, Item), `base_data` ({Time, Player, Wallet}), `tick_stamina`; the whole player load `full_player_state` (+ the modules' `OnPlayerLoad` keys); GetPlayer / NoLoginStart (`get_player`) |
| `roster.{h,cpp}` | - | the roster: `person_info` (CPersonInfo, one owned character) and `roster_info` (Character, every one) |
| `party_set.{h,cpp}` | - | the party sets: `party_set_info` (PartySetInfo, PartySet: every set 1..`party_set_max`, the unsaved ones filled from set 1) and `party_member_uids` (a party's members, for MissionStart) |
| `person_status.{h,cpp}` | - | `person_status_info` (CPersonStatusInfo: a battle member's status, in four steps: base stats, equipment, favor and awakening, seeds) |
| `party.{h,cpp}` | `party` (core) | UpdateParty, UpdatePartySet (PartySetInfo as its serialized text: `parse_party_set_text` → `PartySetText`; test `party_tests.cpp`, `player/party-set-text`) |
| `assist.cpp` | `assist` (core) | SetAssist (the `assist` pairs that `person_info` reports) |
| `home.{h,cpp}` | `home_character` (core) | UpdateHome (`update_home`: the home character, `Player.home_pc_id`) |
| `home_footer.cpp` | `home` | `FooterMissionInfo` (`OnPlayerLoad`: the home footer's feature flags); the follow menu's lists are `../social/social.cpp`'s |
| `titles.cpp` | `title` | SetTitle (`set_title`, its args struct `args::SetTitleArgs` beside it); title grants (`Grant` 13), `TitleList` + `Player.title` (`OnPlayerLoad`), the titles a request added (`OnResponse`) |
| `notice.cpp` | `notice` | the notice board: `WebView` (`OnPlayerLoad`) and the page itself (`server::web_page`, `soaserver/server.h`) |

- **APIs**: GetPlayer, NoLoginStart, UpdateParty, UpdatePartySet, SetAssist, UpdateHome (the core's, registered with `ext::add_core_api` before the modules), SetTitle (a module's). API-INDEX.md lists them with their fids, handlers and tests.
- **Hooks** (their order slots are API-INDEX.md section 2's, pinned by `server/module-order`): `OnPlayerLoad` `home` (FooterMissionInfo), `notice` (WebView), `title` (TitleList, Player.title); `Grant` 13 `title`; `OnResponse` `title` (TitleList, AddTitleList, PresentGetResult.result.Title).
- **State**: the `player` row (Player, Wallet), `stock`, `items`; the roster part: `roster` (the core's), `roster_ext` (api/growth/: seeds and equipped skills), `assist`, `party`, `party_member`, `party_set` (server/PLAN-schema.md; its S4 merges `roster_ext` and `assist` into `roster`); `titles` (the owned titles; created by the module's schema); the `meta` keys read into Player: `tutorial_status`, `view_status`, `view_status2`, `kiyaku_version` (api/entry), `support_uid` (api/social/rental.cpp), `ds_time_saving_count` (api/deepspace), `title` (titles.cpp; PLAN-schema S3 makes them `player` columns).
- **Rules**: docs/server-rules.md "Player load", "Party sets", "Assist", "3. Battle party status (`CPersonStatusInfo`)", "Home character", "12. Home", "Titles", "Notice board page".
- **Tests**: `player_tests.cpp` (`player/home-pc-id`), `home_footer.cpp` (`player/home-footer`), `titles.cpp` (`player/titles`), `notice.cpp` (`player/notice`); the replay corpora (`server/tests/replay/growth` replays SetAssist and the roster builders).
- **Sessions**: `port/scripts/home_session.sh` (the notice board, the footer, titles, the follow menu), `party_session.sh` (parties, assist, UpdateHome).
