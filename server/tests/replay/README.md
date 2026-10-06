# Replay corpora: the proof that a server refactor changes nothing

Each folder here is a recorded (or generated) request sequence. `tools/server_replay_diff.sh` replays every one with two `soa-server` builds (a parent and a child commit) and compares what they emit. This is gate **RG4** of `server/PLAN-readability.md` (section 4.1): every step of that plan must pass it byte-identical.

```sh
tools/server_build_at.sh HEAD~1 build/rg4-parent           # the parent's soa-server (server-only build, ~45 s)
scripts/build.sh --target soa-server                        # the child: this checkout
tools/server_replay_diff.sh build/rg4-parent/soa-server build/server/soa-server
tools/server_replay_diff.sh build/server/soa-server build/server/soa-server   # stability: one binary twice
```

## What is compared

`soa-server <options> --replay DIR --out OUT` starts a fresh state from the corpus's server options and sends each request through the same path as soa-server's game connection: `submit`, the story campaign's `on_request`, `handle`, `error_code` and the campaign's `on_response`, plus soa-server's own `EndMissionTalk` (`net::live_backend()`, server/net/game.cpp). The server clock reads each request's recorded time, through the clock-source seam (`set_clock_source`, soaserver/server.h). Its output:

| File | What | Compared |
|---|---|---|
| `<n>-<Method>.msgp` | each reply body as the library answered it | byte-identical |
| `errors.txt` | `<n> <Method> <code>` (0 accepted, `not-handled`: no handler) | identical |
| `state.sql` | every table's schema and rows (sorted; the story campaign's progress is in the DB since PLAN-schema S12, before it the data dir's `server_campaign.txt` followed) | identical |
| `server.log` | the server's log, paths masked | tier 1: the lines of `tools/server_log_patterns.txt` (those scripts read) identical; tier 2: any other difference is printed and must be declared in the commit message |
| `replies.txt` | the bodies as text | not compared; shown for a body that differs |

Exit status: 0 identical, 2 only tier-2 log lines differ, 1 anything else.

What it does not cover: the wire layer's own work (the bridge, the Ninja cipher, packet framing, the LoginResult's extra `Player` map and the GetPlayerRes after it, the `wire_device` table) and the CDN (`r_ver` is empty in a replay). `server/tests/net` tests those.

## The corpora

| Corpus | Source | Requests |
|---|---|---|
| `seeded` | tests/diff's `seeded` flow, `emu` target (soa-emu + soa-server `--log-packets`), on 2eaaaf6: title, Login, the mission 1-05 (mf01_001) battle, a 10-draw | 10 |
| `tutorial` | tests/diff's `tutorial` flow, `emu` target: a new player, the refused Login (19001), CreatePlayer, the tutorial's scenes (MissionTalk / EndMissionTalk), the battle tutorial ms00_001, UpdateTutorial 1-9 | 27 |
| `event` | tests/diff's `event` flow, `emu` target, `--enable-events`: the summer event board (CheckEventRankingResult), story mc99_565 (EndMissionTalk), battle me99_1054 | 11 |
| `growth` | hand-written for R11 (`req` lines, on 487e3f6), the `seeded` options: Login; four item-shop sets for the materials (EXP items, `item_limitbreak_03`, seeds, awakening and evolution items); every growth API (BoostCharacter, LimitBreakCharacter(_Legacy), EvolutionCharacter, UpdateAwakenLevel, AddStatusCharacter, EquipWeapon / EquipAccessory, EquipSkill) and SetAssist, accepted and refused; UpdateParty, GetPlayer (the `Character` and `PartySet` builders with seeds, awakening and assists) and MissionStart (`CPersonStatusInfo` of the grown party) | 32 |
| `economy` | hand-written for R18 (`req` lines), the `seeded` options without the campaign seed, plus `--galaxy-pass` (the pass kept on every player load): at 2016-06-01 the item shop's sample rows (event coins, box tickets, gacha tickets: ItemShopList, ExItemShop to its limit, refusals), GachaTicket; at 2020-10-25 GetGachaInData, a step-up chain (in order, out of order), single / bulk / sale draws (weapons from the pools), GetGachaRate, a box series drawn to its last box (it refills; ResetBoxGacha refused and accepted), GetBoxGacha, the exchange shop (ExshopExchangeList, ExshopExchange accepted and refused by limit, `exchange_item_max`, items short, closed, unknown), a 2020 item-shop row with a reset period, GetPlayer | 46 |
| `event-extras` | hand-written for R18, the `seeded` options without the campaign seed: a world boss (GetWorldBossInfo, a won mission of its area with time bonuses and the gauges, a non-boss area) and an event ranking (a scored win, GetEventRankingInfo, ClearNewEventRanking, CheckEventRankingResult before and when due, ReceiveEventRankingResult, GetPlayerDetailInfo). The battles are the `event` corpus's me99_1054 MissionStart / MissionEnd bodies with the mission id replaced (the ranking mission's start is refused for its ticket item; its end still scores) | 17 |
| `deepspace` | hand-written for R18 (`req` lines, on 4e52a11), the `seeded` options: Login; DeepSpaceActiveList; DeepSpaceAutoMemberSelect (a weapon-kind and a role bonus); DeepSpaceMissionStart accepted and refused (party size, not on offer, a member twice / unknown / busy, no free ship: the seed has one limit-break ship; a bonus item not owned (10206) and one out of its window); MissionEnd early (refused) and of an unknown ship; quick returns paid in coins (MissionEndNow), also after the 04:00 reset of their daily count; MissionEnd's rewards (player, character and area EXP, FOL, drops), a rare offer it rolls, played and used up; GetPlayer | 41 |
| `sphere211` | hand-written for R18 (`req` lines, on 4e52a11), the `seeded` options: a dive on floor 1 of the season the clock replays: GetSphere211Info, Sphere211AutoMemberSelect / EquipAuto, Sphere211MissionStart (no such cell refused; an own helper; the rental slot, a lender refused once used), MissionContinue, MissionFailed, MissionEnd (the core MissionStart / MissionEnd underneath; a rare and two boss cells), StaminaHeal and UseRerollItem refused (no items), FloorClear, GetSphere211RankingInfo, SelectedFloor, ReturnSphere211 (the boxes opened), the next day's GetPlayer, and 40 days later a season change (the end result once, the ranking reward). Which missions are playable depends on the maps in `--download-dir` (the replay is deterministic on one download tree) | 32 |
| `missions` | hand-written for R15 (`req` lines, on 13b2367; one `wire` MissionEnd: the `event` flow's battle log with the mission id replaced), the `seeded` options, at 2017 and 2021 times: MissionStart / MissionEnd with no helper, an own helper (and one already in the party), a rental clone in the 4th and the 6th argument, a foreign rental id, a story NPC id, the event NPC helper (by `master_npc` and `master_mission_npc` id, and a wrong one); MissionRestart / MultiMissionRestart (and with nothing in progress), MissionFailed, GetPlayMission, MissionTalk, GetMissionList; refusals 10004 (stamina) and 10206 (ticket, vanish item), an unknown mission; the surprise roll, campaigns (2017 prism lots and drops; 2021 story stamina, 友好 favor ×1.5), the character bonus, battle evaluation (me99_MemLast_07); FollowList, UpdateSupport (accepted, refused); the rental bonus over three rental days (03:59 still the day before); (PLAN-schema S7) a MissionFailed after a surprise roll, then a MissionEnd naming the mission with no play; MissionRestart with an own helper and with a rental clone | 90 |
| `campaign` | hand-written for PLAN-schema S12 (`req` lines), the `tower` options without `--restore-tower` (the `seeded` player, `--campaign-seed mf01_001`): the story campaign's progress: mf01_001 cleared twice (a first clear, then again), the story scene mc01_030 by MissionTalk and again by EndMissionTalk, an EndMissionTalk of a battle mission (ignored), a failed mf01_002 (no clear), GetMissionList, a world map mission's clear (m02_06_mb161_10), GetWorldMapInfoList for two episodes, GetPlayer | 16 |
| `tower` | hand-written for R15, the `seeded` options plus `--restore-tower`: Login (the tower lists), two floors of `tower_01` cleared in turn (each MissionEnd lists again, the next floor unlocked), a MissionFailed, a story battle (its MissionEnd lists nothing), GetPlayer | 12 |
| `api-sweep` | generated (`tools/server_replay_record.py --sweep`): every method `soa-server --list-apis` says the library answers, once, without arguments, at 5 s steps from 03:58:00 (across the 04:00 reset) | 106 |
| `items-party` | hand-written (`req` lines; PLAN-readability R13/R14), the sweep's options: on the seeded state, three 10-draws of the weapon gacha `gacha_weapon_0009`, then the item, gear and party APIs with real arguments (compose with a copy, lock / sell, grade up, purification with and without a base, attach, the refusals, UpdateParty, UpdatePartySet: a set, an id out of range, unparsable text) and GetPlayer; then (R12) EquipWeapon moving a weapon from one character to another, EquipAccessory with a weapon (refused), EquipWeapon 0, GetPlayer | 46 |
| `hammers` | hand-written (`req` lines; agent srv-hammers), the `growth` options without the campaign seed: at 2019-05-03 (inside the sets' windows) the item shop's sets 00050 ×2 and 00051 ×3 (eight マジカルハンマー, two マジカルスレッド), two weapons from `ticketgacha_weapon_0003`, then ItemCompose / ItemComposeArray with the hammers (one, three, two at the cap, two plus a thread as an ordinary material) and GetPlayer | 13 |
| `mastery` | hand-written (`req` lines; task U step 3.4), the `growth` options: the growth corpus's item-shop sets, two rarity-6 attackers of the seed boosted to LV70 (a master-type role and one without a type), GetMasteryInfo, TrainMastery (pairing refused: below LV70, the roles swapped, another category, dojo 4; accepted; a training not next, items short, accepted with `item_set_00003` bought twice; a pass-medal training without medals), ResetMastery both ways round and refused, pairing again in dojos 2 and 3, GetPlayer; ChangeRole (the seed's cp0010_b01a_6165 to role_cp0010_b01a_6161; its own role, another person's role refused), ChangeMascot (a type-3 `master_home_message` person; an unknown id refused), GetPlayer; the decorations with none owned (GetDecoInfo, Favorite / UnFavoriteDecoObject skipped, SetCharacterDeco refused: not owned, no payload) | 39 |

| `storage` | hand-written (`req` lines; task U step 3.1), the `items-party` options (with the pass: 500 storage slots): 50 10-draws of `gacha_weapon_0009` fill the inventory to `item_stock`, a 51st sends its weapons to the overflow box; GetOneTimeStorageInfo, ClearNewOneTimeStorageItem, the box's withdraw refused (no room); DepositItem (accepted, again, an unknown uid), GetStorageInfo, Lock / UnlockStorageItem, SellItemsFromStorage refused (locked) and accepted, WithdrawItemFromStorage; the box's withdraws (more than held, one, two with one slot left, one in bulk), GetPlayer | 70 |
| `profile` | hand-written (`req` lines; agent fast-tests, 2026-10-03, from `tools/replay_coverage.py`'s gaps), the `items-party` options: the entry and player APIs with real arguments (SimpleLogin, UpdateView, UpdateKiyakuVersion, UpdatePlayerName, UpdateHome accepted and an unknown character, SetTitle: a default title, an achievement title not owned, 0), the presents (PresentList, GetPresent, GetPresentArray), AchievementActiveList / AchievementReceive, the favor APIs (UpdateFavorByTap, StaminaHealByFavor, UseFavorItem), LockItemArray / UnlockItem, the social lists (Blacklist, GetRecentlyPlayedList, SearchPlayer: refused, no other player), GetPlayer (PLAN-schema S9) two taps on a character with favor and the full loads that send them, the same day and the next; Home3DAnd2DSwitching 0 / 1 (34-37); (docs/unimplemented-apis.md part 3) the settings and account APIs (38-49: options, birth month, read marks, the refusals 10403 and 10009), SendErrorLog and CbtCertification (50, 51); SetStampSlot (52-55: a palette with two default stamps, an unowned stamp refused, the loads) | 55 |

| `sphere211-continue` | hand-written (`req` lines; Sphere211MissionContinue's bool), the `sphere211` options: a start-cell battle declined (0: ended as failed, nothing paid), はい with no battle in progress (10403), a battle continued (1: 100 coins) and won, GetSphere211Info | 9 |

| `compose-points` | hand-written (`req` lines; agent compose-points, 2026-10-06), the `items-party` options: four 10-draws of `gacha_weapon_0009`, then ItemCompose / ItemComposeArray as the strengthening screen previews them (docs/server-rules.md#compose-points): one material, several with a level up, to the cap and at it, a levelled material carrying points, a big success; GetPlayer | 13 |

| `stubs` | hand-written (`req` lines; docs/unimplemented-apis.md part 3 step 8), the `profile` options: Login, every stub once (the social calls with arguments: a player id, a location as f32 bits; the 27 `Debug*` without), GetPlayer: each answers `{Time}`, logs `stub: ...`, and the state is unchanged | 37 |

| `badges` | hand-written (`req` lines; docs/unimplemented-apis.md part 3 step 6), the `economy` options: Login, a 10-draw of a character gacha (two new characters, new stack items), GetPlayer (`is_new` in Character / StockItem), ClearNewCharacter (a new, a seeded and an unknown uid), ClearNewItem (an unknown uid), ClearNewStackItem (a new and an unknown id), GetPlayer (cleared) | 7 |

| `coins` | hand-written (`req` lines; docs/unimplemented-apis.md part 3 step 7, paid currency), the `economy` options: Login (CoinList on the player load), CoinList, a purchase of the テラ set (CoinDepositCreate, CoinDepositAndroidUpdate: paid and free stones), the same update again (not credited twice), CoinDepositIOSUpdate of an unknown deposit (10208), CoinDepositCreate of a product not sold (10208), the S set through CoinDepositAmazonUpdate, DirectItemShopList (empty), GetPlayer | 11 |

| `english` | hand-written (`req` lines; docs/PLAN-english.md E6, 2026-10-07), the `economy` options plus `--english --english-text server/tests/fixtures/english-fixture.tsv` (a fixture table, not the real one, so the corpus doesn't change with every translation update): Login (the login bonuses' present lines: Present_box_1 and the bonus name in English where the fixture has them, a Japanese name in an English template where not), PresentList, GetGachaRate (the rate headings: English, a stale row and one with other printf conversions left Japanese), GetPlayer | 4 |

The sweep is the coverage floor: with no arguments, some handlers decline (`not-handled`: 14 of 106 today) or refuse; the flows exercise the real arguments.

**Fidelity.** Replayed on the build they were recorded with, the flows' replies equal the recorded ones byte for byte, except Login's `r_ver` (the CDN's revision: no CDN is built in a replay, so it is empty).

## Files

- `requests.txt`: a header (`# tz: ZONE`, the zone the recording ran in; the replay runs in it), then one request per line:
  - `wire <n> <t> <Api> <hex>`: the request's plaintext body as the client sent it (`<n>-<Api>.bin` of the packet log), decoded again by `net::decode_request` at replay (battle log included). `<t>` is the server clock of the request in Unix seconds: the recorded reply's `data.Time`, or for a reply without one (a refusal) the log stamp plus the clock offset of the nearest reply. A `#` line before it repeats the packet log's method and arguments.
  - `req <n> <t> <Method> <fid> <ints> <strs> <vecs> <battle log>`: a request given by its arguments (the generated corpora). `-` is an empty list; ints comma-separated; strings hex, comma-separated (`_` an empty string); vectors `|`-separated groups of comma-separated ints (`_` an empty vector); the battle log hex (ASON).
- `options`: the recording's server options, one argument per line, paths relative to the repository root.

## Recording a corpus

```sh
tests/diff/run.sh seeded --target emu --keep --out /tmp/d      # or any soa-server --log-packets DIR
tools/server_replay_record.py /tmp/d/seeded/emu/packets server/tests/replay/seeded \
    --options '--master data/basmaster-3.7.0.sqlite3 --seed data/saves/seed/Game.xml --seed-rng 1 --clock "2026-10-01 12:00:05" --campaign-seed mf01_001 --download-dir work/download-3.7.0 --cdn-url http://production-game.so-ana.com' \
    --note "where it came from"
tools/server_replay_record.py --sweep server/tests/replay/api-sweep --options '...'
```

The options are the recording's (tests/diff gives every run `--master`, `--seed-rng 1`, `--clock "2026-10-01 12:00:05"`, the seed save unless a new player, `--download-dir`, and the flow's own: tests/diff/README.md). `--cdn-url` makes Login answer `AssetPath` / `MasterPath` as soa-server does.

The recorder refuses a packet log holding a player id other than the sanitized `LOCAL00001` (data/saves/README.md): a 10-character upper-case id anywhere in the requests, or the `BAS:PlayerID` of an untracked personal save on the machine. In-process logs (`soa --log-packets`) have no request bodies and aren't supported yet; the domain sessions' corpora of the plan (4.1) wait for that.

A corpus is re-recorded only when the client's requests change (a new flow, a changed flow); a server change never needs a new recording, since the comparison is between two builds on the same requests.

## Coverage: which APIs have a corpus

`tools/replay_coverage.py --write` replays every corpus and writes [`COVERAGE.md`](COVERAGE.md): each API the library answers (`soa-server --list-apis`) and the corpora that have it **accepted** (code 0) outside `api-sweep`, and the gaps (only refused, only the sweep's argument-less call, in no corpus). `tools/replay_coverage.py --check` (gate T0) fails when it is stale. **The rule:** to test a change to an API in the gap lists, add `req` lines for it to a corpus first (a replay takes seconds; a game session minutes), then regenerate COVERAGE.md. 2026-10-03: 74 of 106 APIs covered before the `profile` corpus, 92 after; the 14 left need state the seeded player lacks (growth and item materials, Sphere 211 items, another player for SearchPlayer).
