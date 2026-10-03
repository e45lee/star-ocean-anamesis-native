# Control layer (shared by the port, the 3.7.0 emulator and the viewer, `emulator-viewer/`)

`soa`, `soa-emu` and `soa-viewer` all read the same control commands. The FIFO lives in the shared host loop (`runtime/src/app/host.cpp`, `--control FIFO`). These two tools drive any of them.

| Tool | What |
|---|---|
| `soactl.py FIFO CMD...` | Sends commands to a running instance: `tap:X:Y`, `drag:X1:Y1:X2:Y2`, `wheel:X:Y:DY`, `back`, `text:STRING`, `shot:PATH`, `wait:MS`, `quit`; while the game's keyboard is open, test-only `type:TEXT`, `compose:TEXT` and `key:enter|escape|backspace|delete|left|right|home|end` drive the text box's editor (`runtime/README.md`, "Text entry"). The port also has native debug commands (`phase:`, `call:`, `uiset:`, `debugwin:`) that the emulators lack. |
| `flowctl.py` | Higher-level flows built on `soactl.py`: `wait-log`, `tap-until` (tap until a log line appears), `login-popups` (closes the notice board and the LOGIN BONUS popup), `name-entry`. |
| `gdbclient.py`, `gdbinit-soa` | The guest's GDB stub (`--gdb HOST:PORT`; runtime/README.md "Debugging the guest with gdb"): `gdbclient.py` is a small protocol client for tests and scripts (stop, registers, memory, breakpoints by symbol, step, continue, detach; also a one-shot CLI), `gdbinit-soa` the gdb-multiarch setup. Tests: `control/tests/test_gdbclient.py`. |

**Used by:**
- the port's sessions and smoke test (`port/scripts/`);
- `emulator/scripts/emulator_session.sh` and `emulator_boot.sh`;
- `emulator-viewer/scripts/viewer_lib.sh`.

The old `port/scripts/soactl.py` and `flowctl.py` are forwarding stubs, kept for branches that still use those paths.

## The slot pool (`soaslot.py`, `soaslot.sh`): parallel runs queue instead of overloading the machine

Every game client a test starts (`soa`, `soa-emu`, `soa-viewer`) first takes one of N machine-wide **slots**: an exclusive `flock` on one of N files in `/tmp/soa-slots` (`SOA_SLOT_DIR`), the same place for every worktree and shell. When all are taken the run waits (`soaslot: NAME: waiting for a slot`) and starts as soon as one frees; no run is refused. The lock belongs to the open file descriptor, which the client inherits, so a slot lasts exactly as long as its client (or the script holding it) and frees itself when it exits or is killed: no stale locks, no cleanup, killing by PID works as before.

| Who | How |
|---|---|
| `tests/diff` (`diffdrive/targets.py`) | each target's run takes a slot before it starts anything (`soaslot.acquire`), passes it to the client, frees it at the end; the time a run queued is noted and not counted in its time |
| `port/scripts/*_session.sh` | `phone370_prepare` (every session calls it) takes one slot for the script's lifetime (`soaslot_take`, fd 9); the sessions run one client at a time |
| `port/scripts/smoke.py`, `selftest_resilient.sh` | one slot for the run |
| `emulator/scripts/emulator_session.sh`, `summer_demo.sh`, `nier_demo.sh`, `emulator_boot.sh`, `standin_fetch_test.sh`, `emulator-viewer/scripts/viewer_lib.sh` | one slot, taken before the server starts |
| anything else | `control/soaslot.py run [--name N] -- timeout -k 10 600 build/port/soa ...` (execs the command: `$!` stays the game's PID), or in a shell script `. control/soaslot.sh; soaslot_take NAME` |

Only clients take slots, never `soa-server` (a server waits for its client; servers holding slots while their clients queue would deadlock). A script started under a slot (`SOA_SLOT_HELD=1`) doesn't take a second one.

- `control/soaslot.py status`: who holds which slot, for how long. `control/soaslot.py slots`: N.
- `SOA_SLOTS=N` overrides the pool's size (`0`: no pool). The default is the measured `DEFAULT_SLOTS` (12, below), capped by nproc/2 and MemTotal/3 GB on a smaller machine.
- `SOA_SLOT_STAGGER` (default 4 s): a client starts at least that long after the previous one, machine-wide. Booting is a client's heaviest part (the JIT translates the game's startup): twelve session scripts that took their slots in the same second pushed the load to 32 on the 32 cores and two of them timed out; spaced 4 s apart they don't.
- `SOA_SLOT_SOFTWARE_GL=1` (opt-in; default off: the host GPU): the clients started through the pool render on Mesa's llvmpipe instead of the host GPU. `acquire()`, `run` (also `run --software-gl`) and `soaslot_take` put `GALLIUM_DRIVER=llvmpipe LIBGL_ALWAYS_SOFTWARE=1` in the environment the clients inherit (overriding a `GALLIUM_DRIVER=d3d12` from the profile; other llvmpipe knobs such as `LP_NUM_THREADS` pass through); the programs read nothing new. One switch for a whole run: `tools/gate.sh T1 ... --software-gl`, or `SOA_SLOT_SOFTWARE_GL=1 tests/diff/run.sh ...` / a session script. The client's log line `I/gl: window framebuffer: ... llvmpipe (LLVM ...)` confirms it. Why and what it costs: [`docs/testing-software-gl.md`](../docs/testing-software-gl.md).
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
