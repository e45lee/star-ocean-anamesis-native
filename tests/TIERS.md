# Gate tiers: what runs when

Every gate test is listed once, in [`tiers.json`](tiers.json) (the single source of truth: tier, measured time, what it covers, command); `tools/gate.sh` runs a tier from it and `tools/tests_for.py` picks the per-change tests from it. The table below is generated from it (`tools/gate.py --markdown` rewrites it).

| Tier | When | What | Wall time |
|---|---|---|---|
| **T0** | every commit | the incremental build, then the fast deterministic checks in parallel: the server and runtime unit tests, every port selftest (one boot), every replay corpus, the docs / format / evidence / no-380 / schema checks, pytest, the coverage and impact maps current | about 1.5 minutes (the port selftest's boot is the long pole: 92 s; without it 43 s) |
| **T1** | per change | T0, then what `tools/tests_for.py` selects for the changed paths: the replay against the parent build, the tests/diff shards and port sessions that exercise the touched APIs (the cheapest set covering them), smoke for client changes, the emulator / viewer gates when their scope is touched | 2-6 minutes for one area (the shards run in parallel) |
| **T2** | per batch, before merging to main | T0, the full tests/diff (all flows, all targets, parallel), the broad port session set, the emulator and viewer sessions, the CDN check; with a `build-win/`, the Windows tests `win:*` (else SKIP) | about 25 minutes (the full tests/diff and the sessions share the 12 slots; the `win:*` tests add about 7) |
| **T3** | occasional (nightly, before a release) | the slow or rarely affected: Sphere 211's long runs, the episode download, the full new-player download, the demos, smoke vs the emulator, the stand-in fetch, the debug-window sessions | |

```sh
tools/gate.sh T0                      # every commit
tools/gate.sh T1 --git-diff main      # per change (or --for PATH...)
tools/gate.sh T2 --out /tmp/gate-t2   # before reporting a batch
tools/gate.sh shard:battle session:gacha   # named tests
tools/gate.sh T1 --git-diff main --list    # the plan only
tools/tests_for.py --git-diff main    # what T1 would pick, and why
tools/gate.sh T1 --git-diff main --software-gl   # the clients on llvmpipe, not the host GPU (docs/testing-software-gl.md)
```

`tools/gate.sh` runs the build first and alone, then everything else at once: the checks on 4 workers, the game tests in parallel (each queues for a game slot: control/README.md "The slot pool"), and the selected tests/diff shards and flows in one tests/diff run. Each test writes `OUT/<test>/` and `OUT/<test>.log`; the summary table (PASS / FAIL, the time against the measured one) goes to the terminal and `OUT/summary.txt`; exit 1 when anything fails.

## The permanent gates (server/PLAN-schema.md S11, PLAN-readability.md R19)

These hold on every commit and every merge to main; none has a `known` failure, so any finding fails the gate:

- **T0 `server-docs`**: `tools/check_server_docs.sh --evidence {base}`, enforcing: every handler's 2.5 block (with a label, or `Rules: none (transport)`), every hook's and every `server/include/soaserver/` function's doc comment, docs links resolve (a docs/server-rules.md link is an anchor, `docs/server-rules.md#titles`, since R20), docs/server-rules.md gives every section an anchor and its register of (c) and (d) rules is regenerated (`tools/server_rules_doc.py --check`), API-INDEX.md and errors.h fresh, no "agent" notes in server/ code, every server/ path named exists, a README in every server/src folder, and the evidence manifest (the code's and the rules doc's with its history) not shrunk against `{base}` (a merge: its first parent). A commit that deletes labelled code lists what went in a message line starting `Evidence removed:` (server/README.md "Comment conventions").
- **T0 `server-format`**: `tools/format_server.sh --check` (clang-format 18) fails on any unformatted server/ file.
- **G9, the end state of every game run**: soadrive's `Run.stop()` (control/soadrive/targets.py `Run.state_check`), so every session (control/run.py and its wrapper scripts), every tests/diff run and the Windows runs, checks the server's end state with `tools/schema_inventory.py --check --strict STATE MASTER`: `pragma foreign_key_check` empty, every master reference resolved against the master the server ran with, the state at this build's schema version. A violation is a failed step (`FAIL  state check (G9): ...` in the run's steps.txt; the session's or the flow's verdict FAIL, and control/run.py exits 1 whatever the session's own verdict); a clean state is the step `PASS  state check: foreign keys hold, master references resolve, version N`.
- **T0 `schema-inventory`**: RELS's `m:` rows equal the server's `state::master_refs()` (one list for both checks), and the SQL lint of S0.

## How tests_for.py chooses (T1)

`tests/impact.json` (generated) records which server APIs each test exercises: the replay corpora from their requests.txt, the tests/diff shards and flows from their packet logs, the sessions from their logs (`request X`) or, until a run is recorded, from the API names in their script. A change maps to tests by path:

- docs only: nothing beyond T0;
- `server/src/api/<area>/<file>`: the APIs the file answers plus what its module hooks reach (`soa-server --list-apis`, `--list-hooks`), then the corpora that send them and the cheapest shards and sessions covering them;
- `server/src/rules/<x>_rules*`: the API folder of that name; the rest of `server/` and `tools/server_*`: every corpus and every shard;
- `runtime/`, `platform370/`, `port/src/`, `emulator/src/`, the build: the broad set (every shard, smoke, the gate-scope sessions);
- `tests/diff/`, `control/`, `phone370.sh`: every shard; a test script itself: that test.
- a T1 check with an `area` that holds the path: that check (`english-report` for `data/english/` and `tools/english_*`);
- never the Windows tests (`win:*`, kind `platform`, no impact entry): T2 runs them when `build-win/` exists (their `requires`; else SKIP), or by name (`tools/gate.sh win:seeded`).

Regenerate the map after adding a test or a corpus: `tools/gate.sh T2 --out /tmp/g && tools/tests_for.py --regen --observed /tmp/g` (T0's `impact-map` check fails when an API or a test is missing from it).

## The tests

Times are wall times measured on the development machine (32 cores, 45 GB) on 2026-10-03, with the other agents' clients running; T3's are the estimates of port/README.md (not re-measured). A game test's time excludes its wait for a slot.

<!-- tiers-table: tools/gate.py --markdown -->
| Tier | Test | Time | Clients | What | Command |
|---|---|---|---|---|---|
| T0 | `build` | 1 s | - | the incremental build (0.1 s with nothing to do; a header change rebuilds minutes) | `scripts/build.sh --target soa soa-server soa-emu soa-viewer soa-webview-render soaruntime_tests soa_env_tests soa_zip_tests soa_codec_tests soa_gamefiles_tests soa_cli_tests` |
| T0 | `server-selftest` | 45 s | - | the server library's and the wire layer's unit tests | `build/server/soa-server --selftest` |
| T0 | `runtime-tests` | 1 s | - | the runtime's unit tests (jvm, cpu, jni) | `build/runtime/soaruntime_tests` |
| T0 | `zip-tests` | 1 s | - | the ZIP reader (common/ soa_zip on minizip-ng): synthetic archives, an archive nested in another read in place, byte ranges, CRC checks, ZIP64 past 4 GiB (sparse file), concurrent readers | `build/common/soa_zip_tests` |
| T0 | `gamefiles-tests` | 1 s | - | the game files where the programs find them (common/ soa_gamefiles): the download as a folder, a flat zip or a zip with a top folder (FileTree: locate in place, read, list), the zip-aware install lookups (the APK by content, the download zip, extract_entry) | `build/common/soa_gamefiles_tests` |
| T0 | `env-rule` | 1 s | - | the environment rule (soa/env.h: the on/off words, numbers checked) and every removed SOA_* setting's one warning line naming its flag, in each program (docs/environment.md) | `build/common/soa_env_tests && tests/env_removed.sh` |
| T0 | `cli` | 1 s | - | the five programs' command lines on CLI11 (soa, soa-server, soa-emu, soa-viewer, soa-webview-render; common/include/soa/cli.h and the shared option groups) against the hand-written parsers they replaced (tests/cli/legacy.cpp): every old option defined, every option in a table row, each row parsing to the same configuration and outcome (the deliberate differences listed) | `build/tests/cli/soa_cli_tests` |
| T0 | `codec` | 1 s | - | soa_codec's unit tests (common/include/soa: Base64 with Android's and Aska's spellings, the SharedPreferences XML) | `build/common/soa_codec_tests` |
| T0 | `replay` | 15 s | - | every replay corpus twice with this build (determinism, no crash); T1 compares with the parent build instead (replay-parent) | `tools/server_replay_diff.sh build/server/soa-server build/server/soa-server` |
| T0 | `replay-coverage` | 4 s | - | server/tests/replay/COVERAGE.md is current (the APIs without a corpus) | `python3 tools/replay_coverage.py --check` |
| T0 | `server-docs` | 1 s | - | enforcing (R19): every handler's 2.5 block with a label, every hook's and include/soaserver function's doc comment, docs links (docs/server-rules.md links are #anchors and resolve, R20), docs/server-rules.md's anchors and its generated register fresh (tools/server_rules_doc.py --check), API-INDEX.md fresh, no agent mentions in server/ code, the evidence manifest (with the rules doc and its history) not shrunk against {base} (HEAD~1, or the --git-diff rev) | `tools/check_server_docs.sh --evidence {base}` |
| T0 | `server-format` | 6 s | - | server/ C++ formatted (clang-format 18; enforced: any unformatted file fails) | `tools/format_server.sh --check` |
| T0 | `schema-inventory` | 1 s | - | the state schema inventory parses (server/PLAN-schema.md), its master references (RELS m: rows) are the server's state::master_refs() (S11), and the SQL lint (S0: INSERTs name their columns, no INSERT OR REPLACE on an FK parent) | `python3 tools/schema_inventory.py > /dev/null && python3 tools/schema_inventory.py --lint` |
| T0 | `no-380` | 1 s | - | no reference to the offline build outside the allowed places (tools/check_no_380.sh) | `tools/check_no_380.sh` |
| T0 | `thread-local` | 3 s | - | no non-trivial thread_local in our code (a destructor or a dynamic initializer, read from the built objects; cpp-httplib's allowed), and no program but soa-server references __cxa_thread_atexit (per-thread state: runtime/src/core/thread_record.h) | `tools/check_thread_local.py` |
| T0 | `pytest-control` | 50 s | - | the slot pool, the driver library control/soadrive (log cursor, FIFO, resend rules) and tools/tests_for.py's path rules (no game) | `.venv/bin/python -m pytest -q control/tests` |
| T0 | `pytest-soa-save` | 45 s | - | soa_save's unit tests and the tools' tests, including the English table (tests/test_english_text.py: data/english/master-en.tsv and glossary.tsv fresh, i.e. `tools/english_text.py build --check`; the checks, E3, the MT import, the story tables) (no game) | `.venv/bin/python -m pytest -q tests` |
| T0 | `soa-selftest` | 70 s | 1 | every port selftest (natives off; every registered test, one boot; carried past a crashing test) | `port/scripts/selftest_resilient.sh {out}` |
| T0 | `live-check-guard` | 15 s | 1 | soa's --live-check switches families on: an unknown family fails at start; a short headless run with --live-check kernel:every=1 leaves a counts file with checks > 0 and 0 mismatches (it once parsed and checked nothing for a day) | `tests/live_check_guard.sh build/port/soa {out} {tmp}` |
| T0 | `impact-map` | 3 s | - | tests/impact.json knows every API soa-server answers and every test of tests/tiers.json | `python3 tools/tests_for.py --check` |
| T1 | `replay-parent` | 60 s | - | RG4: every corpus replayed by the parent commit's server and this one, compared byte for byte | `tools/server_build_at.sh {base} {tmp}/parent && tools/server_replay_diff.sh {tmp}/parent/soa-server build/server/soa-server` |
| T1 | `english-report` | 7 s | - | the English coverage report runs over the committed tables and the masters (docs/PLAN-english.md E1/E11: rows per source and prefix, the failing rows kept Japanese, the stale and older-Global rows; lists in {out}/report). Its freshness check (`build --check`) is T0's pytest-soa-save | `.venv/bin/python tools/english_text.py report --out {out}/report` |
| T1 | `shard:login` | 2.2 min | 3 | title, Login, the data check, the notice board and LOGIN BONUS, home; 3 targets compared | `tests/diff/run.sh login --out {out}` |
| T1 | `shard:battle` | 4.7 min | 3 | login, the campaign battle 1-05 (mission map, battle, results), home | `tests/diff/run.sh battle --out {out}` |
| T1 | `shard:gacha` | 4.2 min | 3 | login, a 10-draw from home (SaleGacha), the coins and draws | `tests/diff/run.sh gacha --out {out}` |
| T1 | `shard:tutorial-entry` | 3.0 min | 3 | a new player: 19001, terms, name, CreatePlayer, the opening scene, UpdateTutorial(1) | `tests/diff/run.sh tutorial-entry --out {out}` |
| T1 | `shard:tutorial-scene` | 4.5 min | 3 | from tutorial_status 1 (prepared): a tutorial scene, UpdateTutorial(2), the battle's MissionStart | `tests/diff/run.sh tutorial-scene --out {out}` |
| T1 | `shard:tutorial-battle` | 5.5 min | 3 | from tutorial_status 2 (prepared): the battle tutorial ms00_001, its NPC party, MissionEnd, UpdateTutorial(3) | `tests/diff/run.sh tutorial-battle --out {out}` |
| T1 | `shard:tutorial-home` | 5.7 min | 3 | from tutorial_status 3 (prepared): the third scene, the mission menu, 1-01's story, home, the home tutorial, UpdateTutorial(9) | `tests/diff/run.sh tutorial-home --out {out}` |
| T1 | `flow:event` | 5.5 min | 3 | the summer event (--enable-events): the board, story mc99_565, battle me99_1054, drops (a full flow, shard-sized) | `tests/diff/run.sh event --out {out}` |
| T1 | `smoke` | 4.0 min | 1 | the port's screens against the baselines (title, home, character list, detail, other) | `port/scripts/smoke.sh build/port/soa {out} tests/smoke-base` |
| T2 | `diff-full` | 17.5 min | 9 | the full flows seeded, tutorial, event on emu / port-server / port-inproc, all at once | `tests/diff/run.sh --out {out}` |
| T2 | `session:battle` | 3.8 min | 1 | ミッション, mf01_001's battle, MissionEnd, the results, home; the player's EXP in the state | `port/scripts/battle_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:gacha` | 3.8 min | 1 | the gacha screen, its tabs, a 10-draw (SaleGacha), the presentation; the coins debited | `port/scripts/gacha_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:campaign` | 5.2 min | 1 | Episode 1 -> Mere -> 1-05 through the map, its battle, then the story mission it unlocks | `port/scripts/campaign_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:campaign-en` | 5.2 min | 1 | the campaign session with soa --lang en (docs/PLAN-english.md C4/E11): the in-process server serves the -en master and the English story files; 1-05 and the story mission it unlocks, in English | `port/scripts/campaign_session.sh build/port/soa {out} {tmp} --lang en` |
| T2 | `session:events` | 5.2 min | 1 | event missions with --clock layouts | `port/scripts/events_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:home` | 6.9 min | 1 | every home button by the phase or request it leads to | `port/scripts/home_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:home-en` | 6.9 min | 1 | the home session with soa --lang en (docs/PLAN-english.md E11): every home button in English (the -en master, the English UI art, the client's strings and word wrap); no reference shots (session:home compares none either) | `port/scripts/home_session.sh build/port/soa {out} {tmp} --lang en` |
| T2 | `session:coins` | 7.0 min | 1 | paid currency: a player with 50 stones draws once, the sale-stopped dialog (patched) opens the coin shop, the birth month entered (10009 -> the birth dialog), the L set bought (paid + free stones, the record), still there after a re-login, the birth month not asked again | `port/scripts/coins_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:coins-server` | 7.3 min | 1 | the coins session with soa --server (soa-server over the wire) | `port/scripts/coins_session.sh --target port-server build/port/soa {out} {tmp}` |
| T2 | `session:party` | 4.4 min | 1 | party sets 1 and 2 edited (UpdatePartySet), the home character (UpdateHome), a battle with set 2 | `port/scripts/party_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:rental` | 5.4 min | 1 | a rental helper fought as member 4; a second boot a day later: the rental bonus | `port/scripts/rental_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:growth` | 5.7 min | 1 | strengthening, evolution, limit break, weapon custom (gear set, removed, purified) | `port/scripts/growth_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:storage` | 7.0 min | 1 | the equipment storage (deposit, withdraw, sell) and the overflow box (a present's weapon on a full inventory, listed, badge cleared, taken out), across a re-login | `port/scripts/storage_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:storage-server` | 7.0 min | 1 | session:storage against soa-server (soa --server) | `port/scripts/storage_session.sh --target port-server build/port/soa {out} {tmp}` |
| T2 | `session:items` | 5.5 min | 1 | the item lock (LockItem / UnlockItem: varargs on the FakeApiCaller route), a sale and an enhancement with one material, across a re-login | `port/scripts/items_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:items-server` | 5.5 min | 1 | session:items against soa-server (soa --server) | `port/scripts/items_session.sh --target port-server build/port/soa {out} {tmp}` |
| T2 | `session:mastery` | 7.0 min | 1 | ロール選択 (ChangeRole), マスタリー and キャラデコ in-process: a 師弟 pair formed, five trainings (the fifth with the pass medal) to 皆伝, a favourite and a decoration set, kept after a re-login, parted | `port/scripts/mastery_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:mastery-server` | 7.0 min | 1 | the mastery session against soa-server (the wire route of ChangeRole, the mastery and decoration APIs) | `port/scripts/mastery_session.sh --target port-server build/port/soa {out} {tmp}` |
| T2 | `session:stamps` | 6.0 min | 1 | キャラクター > スタンプ編成: the default stamps and palette shown, a slot changed (SetStampSlot), kept after a re-login | `port/scripts/stamps_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:stamps-server` | 6.0 min | 1 | session:stamps against soa-server (soa --server) | `port/scripts/stamps_session.sh --target port-server build/port/soa {out} {tmp}` |
| T2 | `session:add-item` | 5.0 min | 1 | AddItem as a map: a drawn weapon is in the item list at once and the client sells it, no re-login | `port/scripts/add_item_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:add-item-server` | 5.0 min | 1 | session:add-item against soa-server (soa --server) | `port/scripts/add_item_session.sh --target port-server build/port/soa {out} {tmp}` |
| T2 | `session:deepspace` | 5.4 min | 1 | deep-space expeditions: started, returned, collected, a quick return, two ships, achievements | `port/scripts/deepspace_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:tower` | 4.3 min | 1 | the tower's floor list, a floor's battle, the next floor unlocked (--restore-tower) | `port/scripts/tower_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:badges` | 5.5 min | 1 | the NEW badges: a 10-draw's new characters show NEW, 戻る sends ClearNewCharacter, cleared, still cleared after a re-login | `port/scripts/badges_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:badges-server` | 5.5 min | 1 | session:badges against soa-server (soa --server) | `port/scripts/badges_session.sh --target port-server build/port/soa {out} {tmp}` |
| T2 | `session:settings` | 7.0 min | 1 | その他設定's 一時保管庫設定 on, still on after a restart (screen and state), 初期設定に戻す, the シナリオライブラリ from planted Episode 1 clears | `port/scripts/settings_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:settings-server` | 7.0 min | 1 | session:settings against soa-server (soa --server) | `port/scripts/settings_session.sh --target port-server build/port/soa {out} {tmp}` |
| T2 | `session:simulator-continue` | 8.0 min | 1 | the battle simulator (TrainingMissionStart: the current party, no play record), a lost battle continued for 100 coins and retired (MissionContinue 1 / 0, MissionFailed), a re-login | `port/scripts/simulator_continue_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:simulator-continue-server` | 8.0 min | 1 | session:simulator-continue against soa-server (soa --server) | `port/scripts/simulator_continue_session.sh --target port-server build/port/soa {out} {tmp}` |
| T2 | `session:equipment` | 5.5 min | 1 | an accessory's factor inheritance on the strengthening screen (InheritAccessory), the equipment screen's 自動設定 (EquipAuto), a re-login | `port/scripts/equipment_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:equipment-server` | 5.5 min | 1 | session:equipment against soa-server (soa --server) | `port/scripts/equipment_session.sh --target port-server build/port/soa {out} {tmp}` |
| T2 | `session:restore` | 4.8 min | 1 | home, a battle, a 10-draw, the server state after each | `port/scripts/restore_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:restore-missions` | 6.2 min | 1 | a surprise-enemy battle, two step-up gacha steps, MissionStart refused at stamina 0 | `port/scripts/restore_missions.sh build/port/soa {out} {tmp}` |
| T2 | `session:favor` | 5.4 min | 1 | favor set between two boots, taps on the home character (UpdateFavorByTap), a battle's favor | `port/scripts/restore_favor_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:newplayer` | 15.2 min | 1 | a new player: terms, name, CreatePlayer, the tutorial (and the seeded player's login) | `port/scripts/newplayer_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:tutorial` | 12.7 min | 1 | the new player's tutorial and its milestones (tests/tutorial_milestones.txt) | `port/scripts/tutorial_session.sh build/port/soa {out} {tmp}` |
| T2 | `session:rebase-inproc` | 2.5 min | 1 | the in-process boot: title, Login, the data check, home, the popups, LOCAL00001 | `port/scripts/rebase_inproc_session.sh build/port/soa {out} {tmp}` |
| T2 | `emu:seeded` | 4.7 min | 1 | the 3.7.0 emulator against soa-server: login, battle, gacha (emulator gate scope) | `emulator/scripts/emulator_session.sh build/emulator/soa-emu build/server/soa-server {out}` |
| T2 | `emu:newplayer` | 11.3 min | 1 | the emulator's new player and tutorial (emulator gate scope) | `emulator/scripts/emulator_session.sh --new-player build/emulator/soa-emu build/server/soa-server {out}` |
| T3 | `emu:summer` | 6.1 min | 1 | the summer event demo on the emulator (emulator gate scope) | `emulator/scripts/summer_demo.sh {out}` |
| T2 | `selftest-lang-en` | 40 s | 1 | platform370's --lang en on the booted client (docs/PLAN-english.md B1/B7/E10): CLanguage Current = en, Default 0x100, Voice 0; the three language hooks present; font-en.fpk tried; the hooked CCocosLabel::SetText keeps the Japanese without port_en_* rows. The plain soa-selftest checks the --lang ja side (nothing hooked) | `port/scripts/selftest_resilient.sh {out} 'platform370/lang --lang en'` |
| T2 | `selftest-live:home` | 4.0 min | 1 | the layout selftests of render / scene / anim on home's live objects (soa --selftest on the wire, started at home: the character model, its animation) | `port/scripts/selftest_live.sh build/port/soa {out} {tmp} layout- --at home` |
| T3 | `selftest-live:battle` | 5.0 min | 1 | the same layout selftests 15 s into mf01_001's battle | `port/scripts/selftest_live.sh build/port/soa {out} {tmp} layout- --at battle` |
| T2 | `viewer:boot` | 40 s | 1 | soa-viewer boots (viewer gate scope) | `emulator-viewer/scripts/viewer_boot.sh build/emulator-viewer/soa-viewer {out}` |
| T2 | `viewer:session` | 4.6 min | 1 | soa-viewer's session (viewer gate scope) | `emulator-viewer/scripts/viewer_session.sh build/emulator-viewer/soa-viewer {out}` |
| T2 | `win:battle-gacha` | 5.2 min | 1 | Windows (soa.exe from WSL through interop, staged in C:\soa-win): the restore session: home, a battle, a 10-draw, the server state after each | `scripts/windows-test.sh battle-gacha {out} {tmp}` |
| T2 | `win:runtime-tests` | 30 s | - | Windows: soaruntime_tests.exe (the runtime's tests, the GDB stub's over 127.0.0.1 and [::1]) exits 0, its exit-time destructors included | `scripts/windows-test.sh runtime-tests {out} {tmp}` |
| T2 | `win:selftest` | 7.5 min | 1 | Windows: soa.exe --selftest (every native selftest, one boot) and soa-server.exe --selftest exit 0 | `scripts/windows-test.sh selftest {out} {tmp}` |
| T2 | `win:native-order` | 30 s | - | Windows: soa.exe --list-native byte-identical to Linux's (static-initializer order: natives, selftests and test hooks register in the same order; cmake/init_order.cmake) | `scripts/windows-test.sh native-order {out} {tmp}` |
| T2 | `win:seeded` | 5.8 min | 1 | Windows: soa-emu.exe against soa-server.exe: login, battle, gacha (the emulator's seeded session) | `scripts/windows-test.sh seeded {out} {tmp}` |
| T2 | `win:viewer-boot` | 45 s | 1 | Windows: soa-viewer.exe boots to the title and the terms prompt (the viewer's boot) | `scripts/windows-test.sh viewer-boot {out} {tmp}` |
| T2 | `win:shard-login` | 5.0 min | 3 | Windows: the tests/diff shard login on the three Windows targets (soa-emu.exe, soa.exe --server, soa.exe in process), compared as on Linux | `scripts/windows-test.sh shard-login {out} {tmp}` |
| T2 | `server-cdn` | 4.0 min | - | the CDN's answers byte-identical with the parent build **Known failure:** the two builds' logs list the same CDN lines in a different order, so it reports DIFFERENT even for identical server sources (2026-10-03: HEAD~1 and HEAD with no server change) | `tools/server_build_at.sh {base} {tmp}/parent && tools/server_cdn_check.sh {tmp}/parent/soa-server build/server/soa-server {out}` |
| T3 | `session:sphere211` | 17.0 min | 1 | Sphere 211: five battles with a rental, the boss, floor 1 cleared, the reroll, floor 2 | `port/scripts/sphere211_session.sh build/port/soa {out} {tmp}` |
| T3 | `session:sphere211-continue` | 7.0 min | 1 | a lost Sphere 211 battle continued and retired, the stamina healed, the achievements | `port/scripts/sphere211_continue_session.sh build/port/soa {out} {tmp}` |
| T3 | `session:episode-movie` | 8.0 min | 1 | an episode pack downloaded, the opening movie | `port/scripts/episode_movie_session.sh build/port/soa {out} {tmp} 2` |
| T3 | `session:newplayer-download` | 15.0 min | 1 | the full 3 GB download from the in-process CDN, then the new player | `SOA_PHONE=none port/scripts/newplayer_session.sh build/port/soa {out} {tmp}` |
| T3 | `session:gdb-probe` | 2.2 min | 1 | the guest debugger at a milestone (soadrive/gdb.py over the runtime's --gdb stub): attach at home, a breakpoint hit, x0 and memory read, a step, detach, the client runs on | `control/run.py gdb-probe build/port/soa {out} {tmp}` |
| T3 | `session:home-character` | 6.7 min | 1 | seed variants with a chosen home character (tools/make_test_seed.py --home): 2B (2D-only in 3.7.0, here with --home3d-all) and Evelysse (cp0002) in the 3D home: idle, long idle, talk lines, interactive mode (docs/home3d.md) | `control/run.py home-character build/port/soa {out} {tmp} --home role_cc0015_b01a_6551 --home role_cp0002_b01a_6025 --home3d-all` |
| T3 | `session:debug` | 2.0 min | 1 | the framework's debug windows | `port/scripts/debug_session.sh build/port/soa {out} {tmp}` |
| T3 | `session:debug-input` | 2.0 min | 1 | the debug windows' input | `port/scripts/debug_input_session.sh build/port/soa {out} {tmp}` |
| T3 | `session:profile-extra` | 5.0 min | 1 | the profiling flow over the screens the others don't visit | `port/scripts/profile_extra.sh build/port/soa {out} {tmp}` |
| T3 | `smoke-vs-emu` | 5.0 min | 1 | the smoke baselines against soa-emu | `port/scripts/smoke_vs_emu.sh {out} tests/smoke-base` |
| T3 | `emu:boot` | 2.0 min | 1 | the emulator's no-server boot | `emulator/scripts/emulator_boot.sh build/emulator/soa-emu {out}` |
| T3 | `emu:nier` | 10.0 min | 1 | the NieR collaboration demo on the emulator | `emulator/scripts/nier_demo.sh {out}` |
| T3 | `emu:standin-fetch` | 10.0 min | 1 | the stand-in assets fetched through the CDN | `emulator/scripts/standin_fetch_test.sh build/emulator/soa-emu build/server/soa-server {out}` |
| T3 | `emu:lang-fetch` | 5.0 min | 1 | soa-server --english: the -en master fetched through the CDN by soa-emu (with --lang en when it has it) | `emulator/scripts/lang_fetch_test.sh build/emulator/soa-emu build/server/soa-server {out}` |
| T3 | `rebase-server-diff` | 10.0 min | 1 | the in-process server against soa-server | `port/scripts/rebase_server_diff.sh shared {out}` |
<!-- /tiers-table -->

## Measured (2026-10-03)

| | Before | After |
|---|---|---|
| tests/diff, the 3 full flows | 1,803 s, one flow at a time (seeded 465, tutorial 919, event 419; the integrator's run, gate-phase1) | 1,035-1,078 s all at once (17-18 min), alongside the 7 shards or 12 sessions on the same 12 slots; the tutorial flow alone 740-810 s |
| title -> home in every flow | 165-185 s (a blind 90 s wait at the data check's dialog) | 84-110 s |
| per-change gating | a full flow (7-15 min) or a session (3-15 min) | a shard: login 2.2, gacha 4.2, battle 4.7, tutorial-entry 3.0, -scene 4.5, -battle 5.5, -home 5.7 min; several in parallel take the longest one's time |
| every shard + the full flows at once (30 runs, 12 slots) | - | 1,035 s; every run PASS; fps median 59.5, p10 49.6 |
| T0 | - (no tier; agents ran the checks one by one) | 57-95 s (the port selftest's boot is the long pole) |
| T2 (T0, the full tests/diff, 16 port sessions, 3 emulator sessions, 2 viewer, the CDN check; + the tutorial-home shard) | - | 1,503 s wall (25 min) on the merged build; every session PASS but `session:home` (its notice check waits for a log line main's new web view no longer prints) |

**Flakiness seen** (and what was done): once, every client's screenshots turned black at the same second (11:25, all three tutorial runs; the frames kept coming at 60 fps) and soa-emu then crashed inside the NVIDIA WSL driver (libnvwgf2umx.so) at quit: a machine-wide GPU event, not the code (the same flows passed before); right after it no client could create its GLX context (`glx: failed to create drisw screen`) until the host recovered. tests/diff labels such a crash "in the host GPU driver" (its backtrace is in /usr/lib/wsl/drivers) and notes a GLX failure, so they read as the host's; the tutorial flow's `GetServerTime` changes place under load (masked: compared by count, `tools/compare_packets.py --float-time-sync`); twelve clients booting in the same second pushed the load to 32 and made `session:growth` and `session:tutorial` time out (the pool now spaces starts 4 s apart; both PASS when rerun); `server-cdn` reports DIFFERENT for identical server sources (log order; KNOWN). `session:rebase-inproc` failed at the data check's dialog on every run (fixed in the script). `pytest-soa-save` is KNOWN in a worktree (see the table). `no-380` was KNOWN until its two lines were fixed (2026-10-03); it is a plain check again, so a new reference fails T0.
