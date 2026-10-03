# Environment variables

The programs are `soa` (`port/`), `soa-server` (`server/app/`), `soa-emu` (`emulator/`), `soa-viewer`
(`emulator-viewer/`) and the web view's page renderer `soa-webview-render` (`webview/tools/`).

**The rule (2026-10-03, the user's decision: "prefer command-line flags").** A setting is a
command-line flag, in every program that has it. The environment carries only diagnostics and the
test harness's switches, and every one of them is read through one helper,
[`common/include/soa/env.h`](../common/include/soa/env.h) (the header-only `soa_env` target every
library links):

- **one on/off rule** (`env_on` / `env_bool`): unset or empty = the switch's default; `0`, `false`,
  `no`, `off` (any case) = off; anything else = on;
- **numbers checked like flags** (`env_int`): a value that isn't a whole number in the variable's
  range is warned about (`soa: SOA_PROFILE_HZ=5: expected a number in 10..10000; using 1000`) and the
  default is used;
- **the removed settings** are one table there (`kRemoved`): a program that finds one of them set
  prints one line at startup naming the flag, e.g. `soa: SOA_CLOCK is gone: use --clock`, and
  otherwise ignores it. Only the programs that have the flag warn (soa-server doesn't for
  `SOA_HEADLESS`).

Gate: `tests/env_removed.sh` runs every program with every removed variable set and checks the lines;
`build/common/soa_env_tests` checks the helper (both in T0, `env-rule`).

The audit this replaced (what each program read before, who set it, the findings and the 10
recommendations) is [`docs/history/environment-audit-2026-10-03.md`](history/environment-audit-2026-10-03.md).

## Removed: variable → flag

| Variable | Flag | Warns in |
|---|---|---|
| `SOA_REPO` | `--repo DIR` | soa, soa-server, soa-emu, soa-viewer |
| `SOA_DOWNLOAD_DIR` | `--download-dir DIR` | soa, soa-server, soa-emu, soa-viewer |
| `SOA_DOWNLOAD_PREFER` | `--download-prefer` (new in soa and soa-emu) | soa, soa-emu, soa-viewer |
| `SOA_STANDIN_ASSETS` | `--standin-assets DIR\|off` | soa, soa-server |
| `SOA_GUEST_CPUS` | `--guest-cpus N\|host` | soa, soa-emu, soa-viewer |
| `SOA_HEADLESS` | `--headless` / `--windowed` (`--windowed` new in soa-emu and soa-viewer) | soa, soa-emu, soa-viewer |
| `SOA_FONT` | `--font PATH` | soa, soa-emu, soa-viewer |
| `SOA_WEBVIEW_FONT` | `--font PATH` (one flag for the text box and the web view's pages; new in soa-webview-render) | soa, soa-webview-render |
| `SOA_NATIVES` | `--natives route\|none` | soa |
| `SOA_FAKE_SERVER` | `--fake-server DIR` (new) | soa |
| `SOA_FAKE_SERVER_SCHEMA` | `--fake-server-schema FILE` (new) | soa |
| `SOA_MEMSTATS` | `--memstats [S]` (new) | soa |
| `SOA_RESTORE` | (gone before: `--server inproc` is the default) | soa |
| `SOA_<FAMILY>_CHECK`, `_CHECK_EVERY`, `_CHECK_OUT`, `_CHECK_ONLY`, `_CHECK_TRACE`, `_CHECK_DUMP` | `--live-check FAMILY[,FAMILY..][:KEY[=VALUE]..]` (new; keys `every=N`, `budget=N`, `out=FILE`, `only=SUB\|SUB`, `trace`, `dump`) | soa |
| `SOA_SERVER_DB` | `--db FILE` | soa, soa-server |
| `SOA_SERVER_MASTER` | `--master FILE` | soa, soa-server |
| `SOA_GACHA_POOLS` | `--gacha-pools FILE` | soa, soa-server |
| `SOA_SERVER_SEED` | `--seed FILE` | soa, soa-server |
| `SOA_SERVER_GAME_XML` | `--game-xml FILE` | soa, soa-server |
| `SOA_SERVER_SEED_RNG` | `--seed-rng N` | soa, soa-server |
| `SOA_RESTORE_NEW_PLAYER` | `--new-player` | soa, soa-server |
| `SOA_CLOCK` | `--clock "YYYY-MM-DD HH:MM:SS"` | soa, soa-server |
| `SOA_START_COINS` | `--start-coins N` | soa, soa-server |
| `SOA_GALAXY_PASS` | `--galaxy-pass` | soa, soa-server |
| `SOA_ENABLE_EVENTS` | `--enable-events` | soa, soa-server |
| `SOA_EVENT_KEYWORDS` | `--event-keywords "a,b,!c"` | soa, soa-server |
| `SOA_RESTORE_TOWER` | `--restore-tower` | soa, soa-server |
| `SOA_MASTER_DB` | `--campaign-master-db FILE` | soa, soa-server |
| `SOA_CAMPAIGN_SEED` | `--campaign-seed LABEL` | soa, soa-server |
| `SOA_SERVER_FAIL` | `--fail M:CODE[,..]` | soa, soa-server |
| `SOA_SERVER_SURPRISE` | `--surprise` | soa, soa-server |
| `SOA_LOG_PACKETS` | `--log-packets DIR` | soa, soa-server |

`soa --server HOST` warns about server flags given on its command line ("have no effect ... give them
to soa-server"); with the variables gone there is nothing else to warn about.

## What stays in the environment

Diagnostics and test switches, by library (the programs that link it read them):

**The runtime** (soa, soa-emu, soa-viewer): `SOA_TRACE`, `SOA_COVERAGE`, `SOA_PROFILE`,
`SOA_PROFILE_HZ` (10..10000), `SOA_PROFILE_HOST`, `SOA_WATCHDOG` (0..86400 s), `SOA_AUDIO_DUMP`,
`SOA_TRACE_RT`, `SOA_OFFSCREEN_PRESENT`, `SOA_GL_HOST_SRGB_ETC2`, `SOA_GL_MAP_INVALIDATE`,
`SOA_GL_RELEASE_SHADER_COMPILER`, `SOA_DIRECT_CALLS`. Documented in
[`runtime/README.md`](../runtime/README.md) "Environment", linked from the three programs' READMEs.

**soa's own** (`port/src`): `SOA_SELFTEST_DELAY` (0..3600 s), `SOA_SELFTEST_START_FILE`,
`SOA_SELFTEST_SKIP`, `SOA_SELFTEST_REPEAT` (1..10000), `SOA_TEST_HOOKS_SKIP`, `SOA_TEST_HOOKS_ALL`,
`SOA_STUB_TRACE`, `SOA_WIRE_DUMP`. Documented in [`port/README.md`](../port/README.md) "Environment".

**The server library** (soa, soa-server): `SOA_NOTICE_HTML_DUMP` (the self-test `player/notice`
writes the page there). **The web view** (soa, soa-webview-render): `SOA_WEBVIEW_DUMP_CSS`.

**Emitted by a generator, not built now:** `SOA_ASKA_MATH_OFF` / `SOA_ASKA_MATH_SKIP`
(`tools/gen_aska_math_a2c.py`, through `soa/env.h`). The other generators only name switches of the
removed families in comments (`SOA_*_A2C`, `SOA_*_OFF`, `SOA_OBJBASE_ALL`, which lived in hand-written
files that are gone); a family rebuilt with them should read them through `soa/env.h` too.

Behaviour changes from the one rule: `SOA_TRACE_RT`, `SOA_STUB_TRACE` and `SOA_TEST_HOOKS_ALL` were on
whenever set, so `=0` turned them on; now it turns them off. `SOA_GL_HOST_SRGB_ETC2`,
`SOA_GL_RELEASE_SHADER_COMPILER`, `SOA_GL_MAP_INVALIDATE`, `SOA_DIRECT_CALLS` and
`SOA_OFFSCREEN_PRESENT` looked at the first character; now `off` / `no` / `false` work too. Defaults
are unchanged (`SOA_GL_MAP_INVALIDATE`, `SOA_DIRECT_CALLS` default on; `SOA_OFFSCREEN_PRESENT` unset
= offscreen unless the video driver is x11). `SOA_PROFILE_HZ` out of range was clamped; now it is
warned about and the default used.

### Setting or diagnostic: the borderline ones

| Variable | Went | Why |
|---|---|---|
| `SOA_FAKE_SERVER`, `SOA_FAKE_SERVER_SCHEMA` | flags | they choose what the FakeApiCaller route serves and where a dump goes: run settings, not switches of a diagnostic (the task's list) |
| `SOA_MEMSTATS` | flag `--memstats [S]` | a run setting with a value, used from session scripts and by hand; the control command `memstats` stays for on-demand snapshots |
| `SOA_LOG_PACKETS` | removed (flag existed) | it had `--log-packets`, which tests/diff passes |
| `SOA_NATIVES` | removed (flag existed) | `--natives` / `--no-native` |
| `SOA_GUEST_CPUS` | removed (flag existed) | a device setting (`--guest-cpus`) |
| `SOA_SELFTEST_DELAY`, `SOA_SELFTEST_START_FILE` | environment | they modify `--selftest` for the harness (`selftest_resilient.sh`, live-object tests), like `SOA_SELFTEST_SKIP` / `_REPEAT` |
| `SOA_TRACE` | environment | a diagnostic, though tutorial_session.sh, rental_session.sh and emulator_session.sh use it as a test probe (the damage values) |
| `SOA_PROFILE`, `SOA_COVERAGE`, `SOA_WATCHDOG` | environment | diagnostics shared by three programs (the task's list) |
| `SOA_OFFSCREEN_PRESENT`, the `SOA_GL_*`, `SOA_DIRECT_CALLS` | environment | escape hatches for driver and JIT problems, not settings anyone runs with |
| the live check's per-family switches | flag `--live-check` | they chose what a run checks and where its counts go, per family; one flag covers every family |

## Host and library variables

| Variable | Where | Effect |
|---|---|---|
| `HOME` | soa, soa-emu, soa-viewer `main` | the default data dir (`~/.local/share/soa-linux-370`, `soa-emulator-370/phone`, `soa-viewer-380`); `--data` overrides |
| `TZ`, `HOME`, `TMPDIR` | runtime `hle/libc.cpp` | the only host variables the guest's `getenv` sees (all others are null). `TZ` is also the local time `--clock` / `--device-clock` are read in |
| `SDL_VIDEODRIVER`, `SDL_AUDIODRIVER`, any `SDL_*` hint | SDL2 | SDL picks the driver (`SDL_AUDIODRIVER=dummy` / `disk`: the scripts and tests/diff set `dummy`). The runtime sets `SDL_HINT_VIDEO_X11_FORCE_EGL` (`app/sdl_gl.cpp`) and `SDL_HINT_IME_SUPPORT_EXTENDED_TEXT` (`app/host.cpp`) at normal priority, so the environment overrides them. Left that way (SDL's documented behaviour); `SDL_VIDEO_X11_FORCE_EGL=0` would give X11 GLX contexts, which the EGL emulation doesn't expect |
| everything else | child processes | `ffmpeg` (movies, `posix_spawnp`) and `fc-match` (the text box's font search) inherit the environment (`PATH`, fontconfig's `FONTCONFIG_*`); the guest's own `popen` is refused |

soa-server reads `SOA_NOTICE_HTML_DUMP` only (in `--selftest`): no `HOME`, SDL or children.

## What the scripts read (not the programs)

Script interfaces; no binary reads them, and none is a removed name, so a script's caller can set
them without a warning:

| Variable | Read by | Effect |
|---|---|---|
| `WATCH=1` | every `port/scripts/*_session.sh`, `smoke.py`, `restore_missions.sh`, `profile_extra.sh` | pass `--windowed` instead of `--headless` |
| `SEED_RNG` | the session scripts that fix the server's RNG, `smoke.py` | the `--seed-rng` value (default 1; 605 in the Sphere 211 sessions) |
| `CAMPAIGN_SEED`, `CAMPAIGN_MASTER_DB` | `campaign_session.sh` (`CAMPAIGN_SEED` also `rental_session.sh`, `episode_movie_session.sh`) | `--campaign-seed` (default `mf01_001`), `--campaign-master-db` |
| `SOA_PHONE`, `SOA_SHARED_PHONE`, `SOA_EPISODE_PACKS` | `port/scripts/phone370.sh`, `scripts/shared-phone.sh`, `scripts/make-phone-370.sh` | the phone a run starts from |
| `SOA`, `SOA_EMU`, `SOA_SERVER` | tests/diff, `selftest_resilient.sh` | the binaries |
| `SOA_SLOTS`, `SOA_SLOT_DIR`, `SOA_SLOT_STAGGER`, `SOA_SLOT_MIN_FREE_GB`, `SOA_SLOT_HELD` | `control/soaslot.py` / `.sh` | the machine-wide game slot pool (`control/README.md`) |
| `SOA_SLOT_SOFTWARE_GL` | `control/soaslot.py` / `.sh` (`tools/gate.sh --software-gl` sets it) | opt-in, default off: the clients the pool starts render on Mesa's llvmpipe (`GALLIUM_DRIVER=llvmpipe LIBGL_ALWAYS_SOFTWARE=1` in their environment) instead of the host GPU ([`testing-software-gl.md`](testing-software-gl.md)) |
| `SOA_LIB`, `SOA_V370`, `SOA_V380`, `SOA_GHIDRA_MCP_PROJECT` | `tools/common.sh`, the decompile scripts, `scripts/ghidra-mcp.sh` | the library and Ghidra project |
| `EMU_DATA`, `SERVER_ARGS`, `KEEP_DATA`, `SMOKE_CLOCK`, `SMOKE_KEEP_DATA`, `PER_RUN_TIMEOUT`, `FLOW_*`, `RENTAL_*` | the emulator scripts, smoke, flowctl, rental | per-script knobs (their headers) |

Some scripts also pass their caller's environment on (tests/diff's `proc.py`, `smoke.py`): a removed
variable in the caller's shell then shows up as its warning line in the program's log, nothing else.
`port/scripts/restore_session.sh` passes extra arguments after its three to soa (e.g.
`--campaign-seed mf01_001`, `--live-check FAMILY`).
