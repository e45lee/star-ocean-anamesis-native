# Control layer (shared by the port, the 3.7.0 emulator and the viewer, `emulator-viewer/`)

`soa`, `soa-emu` and `soa-viewer` all read the same control commands. The FIFO lives in the shared host loop (`runtime/src/app/host.cpp`, `--control FIFO`). These two tools drive any of them.

| Tool | What |
|---|---|
| `soactl.py FIFO CMD...` | Sends commands to a running instance: `tap:X:Y`, `drag:X1:Y1:X2:Y2`, `wheel:X:Y:DY`, `back`, `text:STRING`, `shot:PATH`, `wait:MS`, `quit`. The port also has native debug commands (`phase:`, `call:`, `uiset:`, `debugwin:`) that the emulators lack. |
| `flowctl.py` | Higher-level flows built on `soactl.py`: `wait-log`, `tap-until` (tap until a log line appears), `login-popups` (closes the notice board and the LOGIN BONUS popup), `name-entry`. |

**Used by:**
- the port's sessions and smoke test (`port/scripts/`);
- `emulator/scripts/emulator_session.sh` and `emulator_boot.sh`;
- `emulator-viewer/scripts/viewer_lib.sh`.

The old `port/scripts/soactl.py` and `flowctl.py` are forwarding stubs, kept for branches that still use those paths.
