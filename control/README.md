# Control layer (shared by the port, the 3.7.0 emulator and the viewer, `emulator-viewer/`)

`soa`, `soa-emu` and `soa-viewer` all read the same control commands. The FIFO lives in the shared host loop (`runtime/src/app/host.cpp`, `--control FIFO`). Everything that drives them is one library, `soadrive/`, with thin CLIs and runners over it.

| Tool | What |
|---|---|
| `soactl.py FIFO CMD...` | (or `soactl.py [--windows-paths] tcp:HOST:PORT CMD...`, the TCP channel) Sends commands to a running instance: `tap:X:Y`, `drag:X1:Y1:X2:Y2`, `wheel:X:Y:DY`, `back`, `text:STRING`, `shot:PATH`, `wait:MS`, `quit`; while the game's keyboard is open, test-only `type:TEXT`, `compose:TEXT` and `key:enter|escape|backspace|delete|left|right|home|end` drive the text box's editor (`runtime/README.md`, "Text entry"). `tap:`, `drag:` and `back` hold the touch until the game has seen it (3 frames after it read the down, at least 80 ms) and the commands after them wait for the release, so a tap takes at any frame rate (`runtime/README.md`, "Scripted taps"); test hooks `frame-delay:MS` (a slow client) and `input-pacing:0` (the old fixed 80 ms hold). The port also has native debug commands (`phase:`, `call:`, `uiset:`, `debugwin:`, `mission:`, `clock:`) that the emulators lack. (`soadrive/fifo.py`) |
| `flowctl.py` | The waits and flows as commands for shell scripts: `wait-log`, `tap-until` (tap until a log line appears), `wait-screen`, `login-popups` (closes the notice board and the LOGIN BONUS popup), `name-entry`. (`soadrive/milestones.py`, `popups.py`) |
| `run.py [--target T] SESSION ARGS...` | Runs a named session (`soadrive/sessions/`); `run.py --list` lists them with their targets and the scripts that wrap them. |
| `gdbclient.py`, `gdbinit-soa` | The guest's GDB stub (`--gdb HOST:PORT`, `[::1]:PORT`; Linux and Windows; runtime/README.md "Debugging the guest with gdb"): `gdbclient.py` is a small protocol client for tests and scripts (stop, registers, memory, breakpoints by symbol, also on natives, step, continue, detach, `natives()` from `monitor natives`; also a one-shot CLI; IPv6 addresses in brackets; standard library only, so a Windows python runs it too). `gdbinit-soa`: the gdb-multiarch setup for the stub, and in a host gdb on soa itself the commands `soa-native-break SYMBOL` (a breakpoint on the C++ behind a guest symbol) and `soa-natives TEXT`. Tests: `control/tests/test_gdbclient.py` (`SOA_GDB_DEMO=.../soaruntime_tests.exe` for a Windows build: its `::1` cases skip, WSL's mirrored networking shares only 127.0.0.1). Sessions attach it at a milestone through `soadrive/gdb.py` (`Config(gdb=True)`, `Run.gdb()`). |
| `soaslot.py`, `soaslot.sh` | The machine-wide game slot pool (below). |

**Used by:** the port's sessions and smoke test (`port/scripts/`), the emulator's (`emulator/scripts/`), tests/diff (`tests/diff/difftest.py`), `emulator-viewer/scripts/viewer_lib.sh`. The old `port/scripts/soactl.py` and `flowctl.py` are forwarding stubs, kept for branches that still use those paths.

## soadrive: the driver library

One package for the port (`soa`, in-process server or `--server`) and the emulator (`soa-emu` + `soa-server`), the plan's layout (`PLAN-consolidate.md`):

| Module | What |
|---|---|
| `fifo.py` | the control FIFO: one write per batch, the screenshots waited for (and given up when the client died); a `tcp:HOST:PORT` address is the TCP channel instead (`--control tcp:...`, one connection per batch; `CLIENT_PATH`: the client's spelling of the shot paths) |
| `winhost.py` | Windows clients from WSL (README.md "Windows"): a target given a `.exe` (`build-win/...`) runs the staged copy in `C:\soa-win` (`SOA_WIN_STAGE`), from there, with Windows paths, the TCP control channel (port 0, read from the log), its phone and server state on the Windows drive (linked back into the run's dirs), the shared phone hard-linked by `scripts/windows/link-phone.ps1`, the server's state read from a snapshot (SQLite can't share its locks across the drive), the client's environment through `WSLENV`. `Proc`'s RSS cap sees only the interop process for a `.exe` |
| `proc.py` | a program under `timeout -k` in its own process group, stopped by PID (TERM, 10 s, KILL), the 6 GB RSS cap; free ports; `repo_file` (a worktree falls back to the main checkout's untracked files) |
| `milestones.py` | the one wait implementation: whole-file predicates (`grep`, `count`), the `LOG.pos` cursor (`LogCursor`: what `flowctl.py wait-log` chains), `poll`, `tap_until_log` (no resend once another phase began) |
| `screens.py`, `popups.py` | RMSE, probes, settled shots; the login popups (the LOGIN BONUS fingerprint) and the name dialog |
| `state.py` | the server state DB as data (tests/diff's comparison). Every run's end state is also checked when it stops (`targets.Run.state_check`: PLAN-schema G9, `tools/schema_inventory.py --check --strict`; a violation is a failed step and fails the session or the flow) |
| `ui370.py` | the 3.7.0 UI's tap points at 729x1296, by name |
| `targets.py` | `Run`: one client (+ its server) started fresh: the targets `emu`, `port-server`, `port-inproc`; the layouts (tests/diff's run dir, the port sessions' `OUT/log.txt` + `TMP/data`, the emulator session's `OUT/emu.log`); its waits (`wait_for`, `tap_until` on predicates; `wait_log`, `tap_log` on the cursor), shots, state dumps. **Fail fast:** every wait, FIFO send and popup loop checks `Run.alive()` (the client and its soa-server running, and the client's log showing no crash, no host GPU failure and frame-rate lines at least every 2 minutes), so a dead client fails the step within seconds, named: `the client is gone: host GPU (D3D12: Removing Device)` with a `HOST-GPU-FAILURE:` line (the host's GPU dropped out: WSL's D3D12 device removed, no GLX context, a crash in the NVIDIA driver; rerun), `crashed (...)`, `exited (status N)`, `stuck (...)`; `tools/gate.sh` marks such failures `[host GPU failure: rerun]` |
| `gdb.py` | `Config(gdb=True)` starts the client with the runtime's GDB stub (`--gdb 127.0.0.1:0`, the port read from the client's log line, so a Windows client works too; `[::1]:0` with `Config(loopback="::1")` on Linux); `Run.gdb()` attaches `control/gdbclient.py` at a milestone (read guest registers and memory, breakpoints) and detaches after. `Config(loopback="::1")` also puts port-server's soa-server and the client's `--server` / `--http` on `[::1]` |
| `prepared.py` | prepared server states (a replay corpus cut at a request: the tests/diff shards) |
| `flows/` | named flows every target runs: `launch` (title, Login, the data check or download, home, popups), `mission` (the campaign's 1-05; the port's `mission:` shortcut and result pages), `gacha`, `event`, `tutorial`; tests/diff's flows and shards |
| `sessions/` | the named sessions behind the scripts (each: `TARGETS`, its wrapper `WRAPPER`, `options`, `main`); `common.py` their command lines, layouts and verdicts |

**Sessions** (`control/run.py --list`; the first target is the default, the one its script always ran):

| Session | Script | Targets |
|---|---|---|
| `login` | `port/scripts/rebase_inproc_session.sh` | port-inproc |
| `battle-gacha` | `port/scripts/restore_session.sh` | port-inproc |
| `battle`, `party`, `favor`, `missions` | `battle_session.sh`, `party_session.sh`, `restore_favor_session.sh`, `restore_missions.sh` | port-inproc (the `mission:` / `phase:0xf` shortcut) |
| `gacha` | `gacha_session.sh` | port-inproc, port-server, emu |
| `campaign`, `rental`, `events`, `tower`, `home`, `growth`, `deepspace`, `sphere211`, `sphere211-continue`, `episode-movie` | `<name>_session.sh` | port-inproc (the phase lines, the in-process server's lines) |
| `tutorial`, `entry` | `tutorial_session.sh`, `newplayer_session.sh` | port-inproc |
| `seeded`, `newplayer` | `emulator/scripts/emulator_session.sh [--new-player]` | emu, port-server, port-inproc |
| `summer-demo` | `emulator/scripts/summer_demo.sh` | emu, port-server, port-inproc |
| `home-character` | (`control/run.py home-character SOA OUT TMP [--home ROLE]... [--home3d-all]`; T3) | port-inproc: a boot per `--home` role from a seed variant (`tools/make_test_seed.py --home`), the home's idle, long idle, talk and interactive-mode shots, the files the client loaded for the character (`docs/home3d.md`) |
| `gdb-probe` | (`control/run.py gdb-probe [--ipv6] SOA OUT TMP`; T3; `soa.exe` for a Windows run) | port-inproc, port-server, emu: the guest debugger at home (attach, a breakpoint, registers and memory, a step; on the port also `monitor natives` and a natived function: stopped before the native runs, stepped through it; detach); `--ipv6`: the programs over `::1` |

A session refuses a target it doesn't list, with the reason (`TARGETS_WHY`): most port sessions use the port's own commands and log lines (`phase:`, `mission:`, `clock:`, `port_debug: phase N`), which soa-emu lacks. The scripts keep their names, arguments, environment knobs, output files and exit codes. Not converted (one program's own tools, PLAN-consolidate.md "Stays"): `smoke.sh`, the selftests, the debug-window sessions, `profile_extra.sh`, `smoke_vs_emu.sh`, `rebase_server_diff.sh` (it runs `emulator_session.sh`), `emulator_boot.sh`, `nier_demo.sh`, `standin_fetch_test.sh`, the viewer's scripts.

**Tests without a game:** `control/tests/` (pytest; T0's `pytest-control`): the cursor and its LOG.pos contract with flowctl.py, the resend rules, the FIFO, ui370's points, every session module's interface, the slot pool, tools/tests_for.py's rules (a session module maps to its script's tests).

## The slot pool (`soaslot.py`, `soaslot.sh`): parallel runs queue instead of overloading the machine

Every game client a test starts (`soa`, `soa-emu`, `soa-viewer`) first takes one of N machine-wide **slots**: an exclusive `flock` on one of N files in `/tmp/soa-slots` (`SOA_SLOT_DIR`), the same place for every worktree and shell. When all are taken the run waits (`soaslot: NAME: waiting for a slot`) and starts as soon as one frees; no run is refused. The lock belongs to the open file descriptor, which the client inherits, so a slot lasts exactly as long as its client (or the script holding it) and frees itself when it exits or is killed: no stale locks, no cleanup, killing by PID works as before.

| Who | How |
|---|---|
| `tests/diff` and `control/run.py` (`control/soadrive/targets.py`) | each target's run takes a slot before it starts anything (`soaslot.acquire`), passes it to the client, frees it at the end; the time a run queued is noted and not counted in its time |
| the sessions (`control/run.py`: `port/scripts/*_session.sh`, `emulator_session.sh`, `summer_demo.sh`) | one slot for the session's lifetime, its clients (one at a time) under it; a TERM / HUP to run.py stops them first |
| the remaining shell scripts (`port/scripts/debug_*session.sh`, `profile_extra.sh`) | `phone370_prepare` takes one slot for the script's lifetime (`soaslot_take`, fd 9) |
| `port/scripts/smoke.py`, `selftest_resilient.sh` | one slot for the run |
| `emulator/scripts/nier_demo.sh`, `emulator_boot.sh`, `standin_fetch_test.sh`, `emulator-viewer/scripts/viewer_lib.sh` | one slot, taken before the server starts |
| anything else | `control/soaslot.py run [--name N] -- timeout -k 10 600 build/port/soa ...` (execs the command: `$!` stays the game's PID), or in a shell script `. control/soaslot.sh; soaslot_take NAME` |

Only clients take slots, never `soa-server` (a server waits for its client; servers holding slots while their clients queue would deadlock). A script started under a slot (`SOA_SLOT_HELD=1`) doesn't take a second one.

- `control/soaslot.py status`: who holds which slot, for how long. `control/soaslot.py slots`: N.
- `SOA_SLOTS=N` overrides the pool's size (`0`: no pool). The default is `DEFAULT_SLOTS` (15 since 2026-10-04, the user's choice; 12 was the measured choice below), capped by nproc/2 and MemTotal/3 GB on a smaller machine.
- `SOA_SLOT_STAGGER` (default 4 s): a client starts at least that long after the previous one, machine-wide. Booting is a client's heaviest part (the JIT translates the game's startup): twelve session scripts that took their slots in the same second pushed the load to 32 on the 32 cores and two of them timed out; spaced 4 s apart they don't.
- `SOA_SLOT_SOFTWARE_GL=1` (opt-in; default off: the host GPU): the clients started through the pool render on Mesa's llvmpipe instead of the host GPU. `acquire()`, `run` (also `run --software-gl`) and `soaslot_take` put `GALLIUM_DRIVER=llvmpipe LIBGL_ALWAYS_SOFTWARE=1` (overriding a `GALLIUM_DRIVER=d3d12` from the profile) and `LP_NUM_THREADS=4` (unless the caller set one) in the environment the clients inherit; control/soadrive's runs apply it too; the programs read nothing new. One switch for a whole run: `tools/gate.sh T1 ... --software-gl`, or `SOA_SLOT_SOFTWARE_GL=1 tests/diff/run.sh ...` / a session script. The client's log line `I/gl: window framebuffer: ... llvmpipe (LLVM ...)` confirms it. Why and what it costs: [`docs/testing-software-gl.md`](../docs/testing-software-gl.md).
- `SOA_SLOT_MIN_FREE_GB` (default 8, the agents' rule): a run also waits while MemAvailable is below it, which covers game processes that don't go through the pool (an older branch's scripts, a hand-started `soa`).
- Tests: `control/tests/test_soaslot.py` (pytest, no game).

### Measuring the pool's size (2026-10-03)

Several tests/diff runs at once (3 clients each: soa-emu, soa --server, soa in-process; battle, gacha, login and tutorial shards, which boot, fight, draw and play scenes), with the other agents' clients running too. `control/soaslot.py fps OUT...` summarizes the `I/perf: X fps` lines every client logs each 10 s (runtime/src/app/host.cpp; the game runs at 60), per client and overall; the load and MemAvailable were sampled every 20 s.

| Clients (this run / machine) | Load (peak, 32 cores) | MemAvailable (min) | fps median / p10 / samples < 30 | Runs |
|---|---|---|---|---|
| 3 / ~6 (tests/diff seeded, tutorial, event, one flow at a time) | | | 59.6 / 55.9 / 2% | all PASS |
| 6 / ~11 | | | 59.5 / 53.4 / 5% | all PASS but a tap bug since fixed |
| 9 / 16 | 12 | 21 GB | 59.5 / 54.7 / 2% | all PASS |
| 15 / 20 | 31.6 | 10 GB | 58.3 / 36.4 / 5% (booting clients 20-28 fps) | one FAIL: a step timed out (UpdateTutorial(7) not within 120 s) |

The samples under 30 fps at low load are loading screens (a scene or the battle loading). So the machine holds about 16 clients; at 20 the CPU is saturated and memory nears the 8 GB floor. **N = 12** (`DEFAULT_SLOTS`) leaves room for the processes outside the pool (an agent's build, a hand-started client, branches without the pool). Re-measure on another machine the same way (`SOA_SLOTS=K`, K/3 tests/diff runs at once, then `soaslot.py fps`).
