# tests/diff: the port against the emulator

Each **flow** runs once per **target**, each against a fresh server state with the same seed, and the port's runs are compared with the emulator's. It's the regression gate for natives rebuilt on 3.7.0 (port/PLAN.md task 6): a port native that changes what the client sends, what the server ends up with or what the screen shows makes a flow FAIL.

```sh
tests/diff/run.sh                         # every flow, every target (about 28 minutes)
tests/diff/run.sh seeded --target emu,port-server
tests/diff/run.sh tutorial --out /tmp/diff --keep
tests/diff/run.sh seeded --inject 'port-inproc:--start-coins 1000'   # must FAIL (see below)
```

Options: `FLOW...` (default all), `--target` (comma list, default `emu,port-server,port-inproc`), `--out DIR` (default a fresh `/tmp/tests-diff.XXXX`), `--keep` (keep the run phones), `--sequential` (one target at a time; the default runs the targets of a flow in parallel), `--inject TARGET:ARGS` (extra server arguments for one target). Env: `SOA`, `SOA_EMU`, `SOA_SERVER` (the binaries), `SOA_PHONE` (`scripts/shared-phone.sh`; default the shared pre-downloaded phone). Headless; kills only the processes it started (by PID, their own process groups); exit 1 on any difference.

## Targets

| Target | Client | Server | Packet log |
|---|---|---|---|
| `emu` (the reference) | `build/emulator/soa-emu`: the unmodified 3.7.0 client under the JIT, no natives | `build/server/soa-server` | soa-server `--log-packets` |
| `port-server` | `build/port/soa --server 127.0.0.1:PORT`: the port's client (natives), its own network code | `build/server/soa-server` | soa-server `--log-packets` |
| `port-inproc` | `build/port/soa` (the default `--server inproc`: the FakeApiCaller route) | the same server library, in-process | soa `--log-packets` (`port/src/native/api/packet_log.h`) |

Every run gets: the shared phone linked (no client save, no local KVS: a fresh device UUID), the server options `--seed data/saves/seed/Game.xml` (not for the new player), `--seed-rng 1`, `--clock "2026-10-01 12:00:05"` and the flow's own, the client `--device-clock` at the same time, a 729x1296 headless window, and its own ports and directories.

## Flows

| Flow | What | Server options | Time (3 targets in parallel) |
|---|---|---|---|
| `seeded` | title → Login → the data check → the notice board and the LOGIN BONUS → home → ミッション → Mere → 1-05 (mf01_001) → the battle → the results → ガチャ → a 10-draw of the first recommended banner → home | `--campaign-seed mf01_001` | ~7.5 min |
| `tutorial` | a new player: Login refused (19001) → terms → the name → CreatePlayer → the tutorial's scenes, the battle tutorial ms00_001, the mission-menu step, home, the home tutorial (UpdateTutorial 9); `tests/tutorial_milestones.txt` checked on every target (`tools/compare_tutorial.py check`) | `--new-player` | ~14 min |
| `event` | イベント → the 水着イベント2020 board → story mc99_565 (skipped: EndMissionTalk) → the battle it unlocks, me99_1054 → the results → the board → home | `--enable-events` | ~7 min |

The flows are `tests/diff/diffdrive/flows/*.py`; the taps are `emulator/scripts/emulator_session.sh`'s and `summer_demo.sh`'s (`diffdrive/ui370.py` names them). Every milestone is read from what all three targets have: the packet log (`> Name` / `< NameRes`), the client's log (`ShowWebView(http`, `StartKeyboardActivity(`) and the server's state; no `phase:` commands or port-only log lines.

## What is compared (`OUT/<flow>/report.txt`)

For each port target against `emu`:

1. **The run's own milestones**: every step reached (the waits above), plus the flow's state checks (the mission cleared, the coins debited, ten draws, the event drops, ...). A failed step leaves `OUT/<flow>/<target>/fail-NN.png` (the screen at that moment).
2. **Packets** (`tools/compare_packets.py`): the ordered requests (name, FunctionID, arguments) and replies (name, the data map's top-level keys, the status). Always masked: times, connection and request numbers, ciphers, sizes, device UUIDs, session keys and bridge tokens (the tool's own masks); the battle log's length (`--mask-battle-log`: it grows with the battle's length, which the party's AI and the frame timing decide; the battle's effect is compared in the state); a `NoLoginStart` repeated right after the first was answered (`--collapse-title-repeat`: the title sometimes sends it twice within a second; seen on soa-emu in 1 run of 2). Against `port-inproc` also `--transport-neutral`: the bridge handshake (StartBridge, the bridge POST, UpdateSession), the second reply soa-server sends to a Login (GetPlayerRes), Login's wire-only arguments (UUID, push token, advertising id), CreatePlayer's but the name (the route captures the name only) and the DeviceType (`dev=`) are what only the wire has.
3. **The server's state at the end** (`diffdrive/state.py`): every table, row by row; masked: time columns (`*_at`, `day`, `date`, ...: the server clock runs on from `--clock` in real time) and `player.id` / `player.search_id` (a new player's are hashes of the device UUID, new every run); not compared: `wire_device` (soa-server's record of the bridge's device UUIDs) and `meta`.
4. **Screenshots**: the flow's milestone screens (`SCREENS` in each flow) by RMSE against the emulator's (ImageMagick on 182x324 copies, as the smoke test). Limits: 0.08 for still screens; home at 0.08 with the character blanked on both images (`screens.HOME_CHARACTER`: her idle motion differs from run to run, up to 0.15 unmasked; the header, buttons, badges and footer are compared); the gacha detail and the closed result with the banner carousel blanked (`screens.GACHA_CAROUSEL`: it turns every few seconds; the banner drawn is in SaleGacha's arguments); 0.10 for the event board and the tutorial's map. Shown (`info`) but not gated: battle frames, the summon presentation, the result pages (the clear time), the opening scene, and the notice board (in-process it shows the page text, the port's web-view stand-in: `docs/client-changes.md`; soa-emu and `soa --server` show an empty page). A screen neither run took (no LOGIN BONUS that day) is no difference; one only one run took is. Screens are taken settled (two shots 1.5 s apart within RMSE 0.01, at most six tries).

A flow PASSes when every run PASSes and every comparison PASSes; the summary is `OUT/summary.txt`.

## Reading a failure

- **A run's milestone FAILs**: the report lists it; `OUT/<flow>/<target>/fail-NN.png` shows the screen, `client.log` / `server.log` / `packets/packets.log` the rest. If only one target fails, that target differs (or is slower: the waits are generous, but a native that makes a screen slower than its wait shows up here).
- **Packets differ**: the report has a unified diff of the normalized sequences (`-` the emulator, `+` the port). A request with different arguments is a client difference (what a native computed); a reply with different keys or status is the server answering differently (e.g. different state before it); a missing / extra request is a client flow difference. `-v` on `tools/compare_packets.py` prints both sequences.
- **State differs**: the rows only one side has, per table (up to six each). A different EXP, FOL, drop or draw usually follows a request difference above; on its own it means the server saw the same requests in a different state or order.
- **A screen differs**: compare `OUT/<flow>/emu/shots/NAME.png` with the port's. A small excess over the limit on an animated screen is noise (raise that screen's limit, with a note); anything else is a rendering difference.

A difference is either a **test artefact** (mask it in one place, `tools/compare_packets.py` or `diffdrive/state.py`, with the reason written next to it and here) or a **real difference** (fix it: server-first, `docs/client-changes.md` for a client change).

### Differences found while building it (2026-10-02)

- **`GetMissionList` was never sent on the in-process route** (fixed): `IApiCaller::GetMissionList` is a base stub the FakeApiCaller inherits, so the mission select never asked the server (soa-emu and `soa --server` send it on ミッション and back from the results). The route now queues it (`port/src/native/api/fakeapi.cpp` `h_get_mission_list`; `docs/client-changes.md`).
- **`GetMissionList` had no server handler** (fixed, server-side): soa-server answered its `{Time}` stand-in, the in-process route the canned stand-in without `Time`, and neither got the events' `ActiveEventMissionList` / `CampaignInfo`. It is answered with `data.Time` plus the campaign's and the events' additions now (`server/src/core/server.cpp`; `docs/server-rules.md`).
- **soa-emu sometimes sends the title's `NoLoginStart` twice** within a second (1 run of 2): a timing artefact, collapsed (above).
- **Test artefacts masked:** the new player's id (above); home's character pose; the in-process CreatePlayer's missing UUID (the route captures the name only; the server keys nothing on it but `wire_device`).
- **No client save on the phone:** with `data/saves/client/Game.xml` ミッション opened the episode select (the save's last episode) instead of the planet select, on every target, so the flows start like `emulator_session.sh`, without one.

### The deliberate difference

`tests/diff/run.sh seeded --target emu,port-inproc --inject 'port-inproc:--start-coins 299000'` (2026-10-02) gives the in-process run's player 299,000 free coins instead of 300,000. Every step still plays and the packets are equal (a reply's data keys don't change), but the flow FAILs on the state: `player` differs, `free_coin` 297500 on the emulator against 296500 in-process after the 10-draw (exit 1). The screenshots did not catch it: one digit of the header's 紋章石 count is far below the RMSE limits, so the state and packet comparisons are what catch numeric differences; the screenshots catch layout and rendering. Any server option that changes a reward or a draw works the same way.

## Adding a flow

1. `tests/diff/diffdrive/flows/<name>.py` with `NAME`, `config(Config)` (the server options every target gets, the clock, `client_save` / `new_player`), `SCREENS` (`{name: RMSE limit or None}`) and `run(s)`: drive with `s.tap_until(name, secs, xy, pred)`, `s.wait_for(name, secs, pred)`, `s.ctl(cmds...)`, `s.shot(name)`, `s.state(tag)`, `s.check(name, cond)`; predicates on `s.in_packets(rx)`, `s.n_packets(rx)` / `s.more_than(rx, n)`, `s.in_client(rx)`, `s.in_server(rx)`. Start with `launch.title(s)` and `launch.login_to_home(s)` (or the tutorial's start). Use only what every target has (no `phase:` commands, no `port_debug` lines), and name new tap points in `ui370.py`.
2. Register it in `FLOWS` in `tests/diff/difftest.py`.
3. Run it twice on every target; anything that differs between two `emu` runs is an artefact to mask (or a flow step to make deterministic) before a port difference means anything.

The package's layout (`proc`, `fifo`, `screens`, `state`, `ui370`, `targets`, `flows/`) is the one `control/PLAN-consolidate.md` plans for `control/soadrive/`; the flows can move there as they are once it exists (only `compare.py` and `difftest.py` are tests/diff's own).
