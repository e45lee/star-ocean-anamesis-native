# Plan: one driver layer for the port and the emulator

Status: **plan only** (agent `summer-demo`, 2026-10-01). Nothing below is done yet. `port/scripts/*` is
being edited by another agent (p5a-test-baseline), so the migration starts after that lands.

**Scope (the user, 2026-10-01).** This covers only what the port (`soa`, 3.7.0 client, in-process
server: the default, no `--restore` / `SOA_RESTORE`) and the emulator (`soa-emu` + `soa-server`) can
share: the driver library, the start / stop / screenshot / wait / milestone helpers, the flows both
programs run (title and login, the download, popups, missions and battles, stories, events, gacha,
the new player and tutorial), and the session scripts that could run against either program. Scripts
specific to one program stay where they are ("Stays", at the end).

## 1. What is duplicated today

Both programs run the same 3.7.0 UI at 729x1296 and take the same control FIFO commands (`tap`, `drag`,
`shot`, `wait`, `quit`; `runtime/src/app/host.cpp`). The scripts that drive them were written
separately and copy each other.

| # | What | Where (copies) |
|---|---|---|
| D1 | **Process lifecycle**: start under `timeout -k`, keep `$!`, kill by PID on exit / Ctrl-C (TERM, wait up to 10 s, KILL), an RSS cap of 6 GB | `emulator/scripts/emulator_session.sh` (`cleanup`, `alive`), `emulator_boot.sh`, `summer_demo.sh` (copied from emulator_session), `emulator-viewer/scripts/viewer_lib.sh`; in the port each of ~20 `port/scripts/*_session.sh` has its own `timeout ... & pid=$!; trap 'kill $pid'` (no RSS check, no KILL fallback) |
| D2 | **Free ports** (the `socket.bind(0)` Python snippet) | `emulator_boot.sh`, `emulator_session.sh`, `summer_demo.sh` |
| D3 | **Repo files in a worktree** (`repo_file`: fall back to the main checkout that `work/` links to; ignore empty files) | `emulator_session.sh`, `summer_demo.sh`; the port sessions instead `cd` to the repo root and use relative paths |
| D4 | **Waiting for milestones**, three implementations of the same thing: bash `wait_for` / `tap_until` / `poll` / `more_than` over grep | `emulator_session.sh`, `summer_demo.sh` |
| | `flowctl.py wait-log` / `tap-until` (log cursor in `LOG.pos`) | port sessions via `check` / `checkt` / `tapw` / `logw` wrappers redefined per script (`events_session.sh`, `restore_session.sh`, `campaign_session.sh`, `rental_session.sh`, `home_session.sh`, `tower_session.sh`, `sphere211*_session.sh`, `deepspace_session.sh`, `party_session.sh`) |
| D5 | **The download after Login** (決定 364:1043 → ダウンロード 515:800 → bundles until no GET for 30 s → 完了 364:790; the pre-downloaded-phone variant) | `port/scripts/phone370.sh` (`phone370_data`, waits on `port_debug: phase 19`), `emulator_session.sh` (`download`, `data_on_phone`), `summer_demo.sh` (copy + an EMU_DATA variant that taps the three buttons in turn) |
| D6 | **Title → Login**: wait for the title, TAP TO START until Login | `phone370.sh` (`phone370_title/login`: phase 1, tap 364:1000, `request Login`), `emulator_session.sh` and `summer_demo.sh` (`< NoLoginStartRes`, tap 364:713, the 1002 / リトライ fallback) |
| D7 | **Tap coordinates** of the 3.7.0 UI, as literals | mission start: 364:905 single play, 620:1120 no rental, 364:900 ミッション開始, 515:712 決定 (8 files: `campaign/events/rental/tower/growth_session.sh`, `sphere211*_session.sh`, `emulator_session.sh`, `summer_demo.sh`); results OK 510:1040 (9 files); story skip 115:1240 + はい 515:742 (8, incl. `viewer_session.sh`); gacha 425:1250 / 540:945 / 515:800 / 364:1190 / 577:1199 / 364:1002 (`restore_session.sh`, `gacha_session.sh`, `emulator_session.sh`, `summer_demo.sh`); home 60:1245 (8); イベント 90:1085 (`events_session.sh`, `summer_demo.sh`) |
| D8 | **Result pages until back** (OK at 510:1040 until the menu returns) | `events_session.sh` `results()` (phase 5), `campaign_session.sh`, `restore_session.sh`, `restore_missions.sh`, `rental_session.sh`, `restore_favor_session.sh`, `emulator_session.sh` (GetMissionList), `summer_demo.sh` (CheckEventRankingResult) |
| D9 | **Server-state checks**: run `tools/server_state.py`, then `sed`/`grep` its text (coins, stamina, `mission X: cleared`, `gacha` lines, roster) | `emulator_session.sh`, `summer_demo.sh`, `restore_session.sh`, `restore_missions.sh`, `newplayer_session.sh`, `tutorial_session.sh`, `growth_drive.sh`, `rebase_inproc_session.sh` |
| D10 | **Screen checks**: RMSE against a reference (`flowctl.py wait-screen` with the smoke baseline; `viewer_lib.sh` with its own refs; `smoke.py`), colour probes (`emulator_session.sh` planet-select brightness; `summer_demo.sh` flat-frame retake, beach board, story popup; `flowctl.py` LOGIN BONUS fingerprint) | as listed |
| D11 | **Screenshot naming / output layout**: `OUT/shots/NN-name.png` (port), `OUT/name.png` (emulator_session), `OUT/NN-name.png` + contact sheet (summer_demo) | all session scripts |
| D12 | **Battle-log check** (decode the MissionEnd `battle_log` msgpack, compare `mission_time` with the server's line) | `emulator_session.sh` (heredoc); the port's sessions check `MissionEnd mission ...` log lines only |
| D13 | **Event / story flow** (event list → board → story → battle) | `events_session.sh` (port, `--clock` layouts), `summer_demo.sh` (emulator, beach / story-popup probes) |
| D14 | **New player + tutorial** (terms, name entry, tutorial rounds, `tests/tutorial_milestones.txt`) | `newplayer_session.sh`, `tutorial_session.sh` (port), `emulator_session.sh --new-player`; already shared: `flowctl.py name-entry`, `tools/compare_tutorial.py`, `tests/tutorial_milestones.txt` |

Already shared and working: `scripts/shared-phone.sh` (the pre-downloaded phone, linked per run: used by `phone370.sh`, `emulator_session.sh`, `summer_demo.sh`; it removes most of D5's download runs but not the dialog handling), `control/soactl.py`, `control/flowctl.py` (`login-popups` has 15 users in
both trees, `name-entry`), `tools/server_state.py`, `tools/compare_tutorial.py`,
`tools/contact_sheet.py` (new with summer_demo.sh).

### The one real difference: where milestones are read

| Milestone | port (`soa`, in-process server) | emulator (`soa-emu` + `soa-server`) |
|---|---|---|
| a request arrived | `I/server: request X (fid ...)` in soa's log | the same line in `server.log`; `> X` / `< XRes` in `packets.log` (`--log-packets`) |
| a server rule fired | `I/server: MissionEnd mission ...` etc. in soa's log | the same lines in `server.log` |
| a client phase | `port_debug: phase N` (a port native; 19 session scripts wait on it) | none (no natives) |
| HTTP / JNI events | `I/http: GET`, `ShowWebView(...)` in soa's log | the same lines in `emu.log` (shared runtime) |
| server state | the port's state DB | `soa-server --data`'s DB; both read by `tools/server_state.py` |
| navigation shortcuts | `phase:` / `call:` / `uiset:` FIFO commands | none |

So shared flows must not use `phase:` commands, and must name milestones abstractly (below), each
target mapping them to its own log. Two changes would remove most of the gap:
- **a packet log for the in-process server** (the server library already has it for `soa-server`:
  expose the same option in `soa`, e.g. `--log-packets DIR`), so `> X` / `< XRes` exist for both;
- **phase lines in the emulator** without natives: `SOA_TRACE` on the 3.7.0 phase-change function
  (the runtime's trace works in `soa-emu`), printed in the same `phase N` form. Until then the emulator
  maps "phase reached" to the request or a screen probe that follows it.

## 2. Proposed layout

One Python package used by both; shell scripts become thin wrappers.

```
control/
  soactl.py, flowctl.py      unchanged CLIs (kept for every existing caller), re-implemented on soadrive
  soadrive/                  the library
    fifo.py        send commands, wait until queued (today's soactl.py)
    proc.py        Program: start under timeout -k with a PID, stop (TERM, wait, KILL), Ctrl-C, RSS cap,
                   free ports, headless / --watch, scratch dirs, repo_file (worktree fallback)   [D1-D3]
    targets.py     Port(soa, data dir, client save) and Emu(soa-emu + soa-server: ports, --seed,
                   --enable-events, --clock, --log-packets, CDN); each knows its log files and the
                   phone (download / pre-downloaded copy, like phone370_prepare and EMU_DATA)
    milestones.py  LogCursor (flowctl's Log, one per file), Milestones: request(name), reply(name),
                   server(regex), phase(n), http(regex); wait / tap_until / poll; the PASS/FAIL recorder
                   that prints the summary and writes milestones.txt                              [D4, D12]
    screens.py     numbered shots per section (flat-frame retake), RMSE match against refs, colour
                   probes (bright, warm/beach, dark band), the LOGIN BONUS fingerprint, the contact sheet [D10, D11]
    state.py       server state as data (import tools/server_state.py's reader; no sed on its text) [D9]
    ui370.py       the 3.7.0 UI's tap points at 729x1296, by name (TAP_TO_START, MISSION_SINGLE_PLAY,
                   RENTAL_NONE, PARTY_START, CONFIRM_OK, RESULT_OK, STORY_SKIP, STORY_SKIP_YES,
                   FOOTER_HOME, FOOTER_GACHA, HOME_EVENT, HOME_MISSION, GACHA_10, SUMMON_START,
                   SUMMON_ALL_SKIP, ...), each with the file/screenshot it was taken from          [D7]
    flows/
      launch.py    title (with the リトライ fallback) → Login → download / data check → popups → home  [D5, D6]
      mission.py   detail → single play → rental (none / index) → party → start → battle shots →
                   MissionEnd → result pages until back                                          [D8]
      story.py     story detail → start → skip → back
      event.py     event list → board (by probe, never scrolled) → story / battle                [D13]
      campaign.py  ミッション → planet → map → node
      gacha.py     gacha menu → banner → single / 10 → summon → results → home
      newplayer.py terms → name → tutorial rounds → milestone list                               [D14]
  run.py           `control/run.py --target port|emu SESSION [--out DIR] [--watch] [target options]`
  sessions/        named sessions composed from flows (Python): seeded (login + 1-05 + 10-draw),
                   newplayer, summer-demo, events, campaign, rental, party, growth, home, tower,
                   deepspace, sphere211, favor, missions
  tests/           pytest for soadrive without a game: LogCursor, milestone parsing, state parsing,
                   probes on stored screenshots, flows against a fake FIFO (records commands)
```

Thin wrappers keep today's entry points and arguments, e.g. `emulator/scripts/summer_demo.sh` →
`exec control/run.py --target emu summer-demo "$@"`, `emulator_session.sh [--new-player]` →
`--target emu seeded|newplayer`, `port/scripts/events_session.sh` → `--target port events`. Each
session runs against either target unless it needs a target-only feature (then it says so and refuses
the other target with a clear message).

Rules for the library: no fixed sleeps without a following milestone or probe; every tap that can be
dropped goes through `tap_until`; kill only PIDs it started; never `pgrep -f`; outputs in OUT, phones and
server state in a scratch dir (deleted unless kept); the sanitized player `LOCAL00001` only.

## 3. Migration order

Each step is one or a few commits, keeps every old entry point working, and is gated as in section 4.

1. **soadrive core, no callers changed:** `fifo.py`, `proc.py`, `milestones.py` (LogCursor moved from
   `flowctl.py`), `screens.py`, `state.py`, with `control/tests/`. `soactl.py` and `flowctl.py` become
   thin CLIs over it (same arguments, same output); their existing callers are the regression test.
2. **ui370.py**: collect the coordinates from the scripts in D7 into names; no caller changes yet.
3. **Emulator first** (no other agent edits `emulator/scripts/`): port `summer_demo.sh` and
   `emulator_session.sh` (seeded, `--new-player`) to `control/run.py --target emu` sessions; the shell
   files become wrappers. Their milestone lists must come out identical (compare `milestones.txt`).
4. **Server-side parity for milestones**: a packet log for the port's in-process server; the
   emulator's phase trace (`SOA_TRACE` mapping). Both additive and opt-in.
5. **Port target**: `targets.Port` (data dir, client save, the phone via `scripts/shared-phone.sh` as `phone370.sh` does), then the
   seeded session against `--target port` (it replaces `restore_session.sh`'s login + battle + gacha
   path) and `newplayer` / `tutorial`. `phone370.sh` keeps its functions as wrappers for the remaining
   shell callers.
6. **Port sessions one by one**, in order of overlap with the emulator: `events_session.sh` (+ the
   summer flow), `campaign_session.sh`, `rental_session.sh`, `party_session.sh`, `home_session.sh`,
   `growth_session.sh` / `growth_drive.sh`, `tower_session.sh`, `deepspace_session.sh`,
   `sphere211_session.sh` / `sphere211_continue_session.sh`, `restore_favor_session.sh`,
   `restore_missions.sh`, `episode_movie_session.sh` (taps only; its MovieFinished check reads the
   server's log). Each: rewrite as a session, keep the `.sh` as a wrapper, drop `phase:`
   shortcuts in favour of taps where both programs must run it, run against both targets once.
   Rename the `restore_*` sessions (the switch is gone); keep the old file names as wrappers until no
   caller uses them.
7. **A GDB remote stub in the runtime** (the user, 2026-10-02; done alongside these control changes): `runtime/` serves
   the GDB remote serial protocol for the **guest** (AArch64) on `--gdb HOST:PORT` (soa, soa-emu, soa-viewer;
   off by default), so `gdb-multiarch` (installed) can attach to the running client.
   - **Target description:** aarch64 core registers (x0-x30, sp, pc, cpsr) and the FP/SIMD registers (v0-v31, fpsr,
     fpcr) via `qXfer:features:read`, read/written from dynarmic's state of the stopped thread(s).
   - **Memory:** `m`/`M`/`X` on guest memory (the runtime's guest address space; unmapped ranges answer an error).
   - **Threads:** each guest thread (the game's pthreads on the JIT) is a GDB thread (`qfThreadInfo`, `H`, `T`), all-stop:
     a stop halts every guest CPU at its next block boundary (dynarmic `HaltExecution`).
   - **Breakpoints:** `Z0`/`z0` software breakpoints by invalidating the JIT block at the address and checking the PC on
     block entry (or dynarmic's own breakpoint/`ExceptionRaised` hook); hardware-style `Z1` mapped to the same.
     Watchpoints (`Z2`-`Z4`) later, through the runtime's memory access hooks if cheap.
   - **Stepping:** `s` by a one-instruction JIT block (dynarmic single-step option); `c`, `vCont`, Ctrl-C (`\x03`)
     interrupt.
   - **Symbols:** `qXfer:libraries-svr4:read` (or a `monitor` command printing the load base), so gdb loads
     `work/libSOA-3.7.0.so`'s symbols at the right base; a `control/gdbinit-soa` with the setup (`set
     architecture aarch64`, `target remote`, `add-symbol-file` at the base).
   - **Integration with the control layer:** `soadrive` can start a target with `--gdb` and attach a scripted gdb
     (gdb's Python API or `gdb -batch -ex`) to read guest state at a milestone (e.g. dump a struct at a breakpoint),
     which the native rebuild uses to compare natives with the guest. A `monitor` command passthrough to the
     control FIFO commands (`shot:`, `tap:`) is optional.
   - **Gate:** a runtime test (attach, break on a known function such as `CHome::GetAdjutant`, read x0/memory,
     step, continue, detach) headless; the client keeps running correctly after detach; no cost when `--gdb` is off
     (frame times unchanged).
8. **Cleanup**: delete duplicated helpers from wrappers, update `control/README.md`, `emulator/README.md`,
   `port/README.md`; remove the forwarding stubs `port/scripts/soactl.py` / `flowctl.py` once no branch
   needs them.

## 4. Keeping the tests green during it

- **Golden milestones:** before a session is moved, run the old script and keep its PASS/FAIL list
  (and the server state dump) as the reference; the new session must produce the same milestones in
  the same order and the same state diff (gacha draws are deterministic with `--seed-rng 1` and a fixed
  `--clock`). Screenshot sets are compared by name and by eye on a contact sheet, not by pixels.
- **Old entry points keep working** at every step (wrappers with the same arguments and exit codes);
  `smoke.sh`, the selftests and every session named in a gate keep their command lines.
- **Library tests without a game** (`control/tests/`, pytest, seconds): run on every commit touching
  `control/`.
- **Gate scope as today:** a change to `control/soadrive/` runs the library tests plus one session per
  target (`--target emu seeded`, `--target port seeded`) and `smoke.sh`; a moved session runs itself on
  both targets. Emulator / viewer gates still follow the user's gate-scope rule.
- **One session at a time**, each in its own commit, so a regression bisects to one move; parallel
  runs with separate OUT / scratch dirs and free ports (≤ 6 game processes, ≥ 8 GB free).
- **Coordination:** no edits under `port/scripts/` while another agent owns it (today: p5a-test-baseline);
  steps 1-4 touch only `control/`, `emulator/scripts/`, `tools/` and the server library.

## Stays (program-specific; not consolidated)

| Script | Why it stays |
|---|---|
| `port/scripts/smoke.sh`, `smoke.py` | the port's screenshot regression (P5a: new 3.7.0 baselines in `work/port-test/smoke-base`, matched against soa-emu by `smoke_vs_emu.sh`); may later import `soadrive.screens` for RMSE |
| `port/scripts/selftest_battle.sh`, `selftest_resilient.sh`, `selftest_home.py`, `selftest_screens.py` | drive `soa --selftest` (guest calls, natives off): no emulator equivalent |
| `port/scripts/debug_session.sh`, `debug_input_session.sh` | the port's debug windows through `call:` / `uiset:` natives |
| `port/scripts/battle_session.sh`, `gacha_session.sh` | rewritten by P5a for the in-process server after this plan was written: re-check whether they can move to shared flows (step 6) |
| `port/scripts/rebase_inproc_session.sh`, `rebase_server_diff.sh` | compare the port's in-process server with soa-server: about the port's server wiring |
| `port/scripts/apinotify_live.sh`, `profile_extra.sh`, `profile_report.py`, `host_profile.py`, `coverage_diff.py` | port profiling / coverage / native live checks |
| `port/scripts/remaining.py`, `agent-worktree.sh` | repo housekeeping |
| `emulator/scripts/emulator_boot.sh` | the emulator's no-server boot check (no flow to share); may import `soadrive.proc` |
| `emulator-viewer/scripts/*` | the 3.8.0 viewer: a different UI and its own references; may import `soadrive.proc` / `screens` later |
| `scripts/build.sh`, `fetch-deps.sh`, `run-port.sh`, `run-emulator-370.sh`, `run-viewer-380.sh` | end-user launchers, not test drivers |
| `tests/test_kvs.py`, `test_saves.py`, `test_script.py` | `soa_save` unit tests (no game); `tests/tutorial_milestones.txt` stays as the shared data file the newplayer flow reads |
