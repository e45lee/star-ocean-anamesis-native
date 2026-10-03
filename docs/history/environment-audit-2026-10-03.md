# Environment variables: the audit of 2026-10-03 (before the cleanup)

> **History.** The audit of 2026-10-03 (at `ca75424`) that led to the environment cleanup, moved here from
> `docs/environment.md` when the cleanup was done (branch `port/env-flags`, the same day). It describes the
> environment **before** the cleanup: most `SOA_*` settings below are command-line flags now and the
> variables print a warning. The current state: [`docs/environment.md`](../environment.md).


An audit (2026-10-03, at `ca75424`) of every environment variable the four runnable programs read:
`soa` (`port/`), `soa-server` (`server/app/`), `soa-emu` (`emulator/`) and `soa-viewer`
(`emulator-viewer/`). Variables are attributed by the link graph, not by the directory they are read in:

| Library | Linked into |
|---|---|
| `runtime/` (`soaruntime` objects, `soaruntime_app`) | soa, soa-emu, soa-viewer |
| `platform370/` | soa, soa-emu (reads no variables) |
| `server/` (`soaserver`, `soanet`) | soa (in-process, whole archive), soa-server |
| `webview/` (`soawebview`) | soa |

The attribution was checked against the built binaries (`strings build/*/soa*`): every `SOA_*` name below
appears in exactly the programs listed for it.

Column legend:
- **CLI**: the command-line option that does the same; "flag wins" = the environment is a fallback read
  only when the option wasn't given.
- **Docs**: where it is documented. `help` = the program's `--help` text; `pR` = `port/README.md`
  ("Run options" / "Running" / "Profiling" tables), `rR` = `runtime/README.md`, `nR` =
  `port/src/native/README.md`, `sR` = `server/README.md`, `eR` / `vR` = `emulator/README.md` /
  `emulator-viewer/README.md`, `wv` = `docs/webview.md`, `sr` = `docs/server-rules.md`.
- **Kind**: `setting` (user-facing), `debug`, `test` (a test-harness interface), `dead`.

## soa

54 `SOA_*` variables (25 run options, 5 more in `main`, 6 self-test / debug switches in
`port/src/native/common`, 2 from the server library, 2 from the web view, 14 from the runtime), the
dormant `SOA_<FAMILY>_CHECK*` family, plus `HOME` and the SDL / guest pass-through below.

Run options (`port/src/core/options.cpp` `options_from_env`, called after the command line; a flag
always wins). Booleans here use `env_on`: set, non-empty and not `0`.

| Variable | Read at | Effect, format, default | CLI | Docs | Kind |
|---|---|---|---|---|---|
| `SOA_REPO` | options.cpp:57 | the source checkout repo files are read from; default: found from the executable | `--repo DIR` (flag wins) | help, pR | setting |
| `SOA_DOWNLOAD_DIR` | options.cpp:60 | the 3.7.0 download tree, the asset fallback (and the in-process CDN's content); default `<repo>/work/download-3.7.0` with `--server inproc`, none with `--server HOST` | `--download-dir DIR` (flag wins) | help, pR | setting |
| `SOA_DOWNLOAD_PREFER` | options.cpp:61 | bool: the download tree wins over the APK; default off | **none** in soa (soa-viewer has `--download-prefer`) | help, pR | setting |
| `SOA_STANDIN_ASSETS` | options.cpp:63 | stand-in asset dir, or `0` / `off` = none; inproc default `<repo>/standin-assets` | `--standin-assets DIR\|off` (flag wins) | help, pR | setting |
| `SOA_FAKE_SERVER` | options.cpp:68 | the FakeApiCaller route's canned-responses dir; inproc default `<repo>/port/fakeapi/responses`; no effect with `--server HOST` or `--natives none` (the route's hooks aren't installed) | none | pR, api.md, sr | debug |
| `SOA_FAKE_SERVER_SCHEMA` | options.cpp:69 | file: dump the response key schema there at `CGame::OnInitialize` (`fakeapi.cpp:589`) | none | pR, api.md | debug |
| `SOA_GUEST_CPUS` | options.cpp:71 | N or `host` (=0, the host's count); default 8. No range check (the flag requires 1..256) | `--guest-cpus N\|host` (flag wins) | help, pR | setting |
| `SOA_MEMSTATS` | options.cpp:76 | `atoi`: 1 = a memory snapshot per phase change, S > 1 also every S s; default 0 | none (`--control memstats` is on demand) | pR | debug |
| `SOA_RESTORE_NEW_PLAYER` | options.cpp:79 | bool: the server starts without a player | `--new-player` (flag wins) | help, pR, sr | setting |
| `SOA_SERVER_DB` | options.cpp:80 | the server state DB; inproc default `DATA/server.sqlite3` | `--db FILE` | help, pR, sR | setting |
| `SOA_SERVER_GAME_XML` | options.cpp:81 | the last seed fallback; inproc default `DATA/data/shared_prefs/Game.xml` | `--game-xml FILE` | help, pR | setting |
| `SOA_SERVER_MASTER` | options.cpp:82 | the 3.7.0 master DB; default `data/basmaster-3.7.0.sqlite3` | `--master FILE` | help, pR, sr | setting |
| `SOA_SERVER_SEED` | options.cpp:83 | the save a new state is seeded from | `--seed FILE` | help, pR, sr | setting |
| `SOA_SERVER_SEED_RNG` | options.cpp:85 | `strtoull` base 0: a fixed server RNG seed; default the time | `--seed-rng N` | help, pR | test (every session script sets it) |
| `SOA_START_COINS` | options.cpp:90 | free coins of a new player, `strtoul` base 0 (the flag is base 10); default 300000 | `--start-coins N` | help, pR, sr | setting |
| `SOA_CLOCK` | options.cpp:95 | `"YYYY-MM-DD[ HH:MM:SS]"` local time, or Unix seconds: the server clock starts there; unparsable = silently ignored (the flag exits 2) | `--clock` | help, pR, sr, api.md | setting |
| `SOA_GALAXY_PASS` | options.cpp:96 | bool: the player holds the Galaxy Pass | `--galaxy-pass` | help, pR, sr | setting |
| `SOA_ENABLE_EVENTS` | options.cpp:97 | bool: open every event / gacha matching the keywords all year | `--enable-events` | help, pR, sR, sr | setting |
| `SOA_EVENT_KEYWORDS` | options.cpp:98 | comma list, `!word` excludes; default `水着,夏,サマー,!福袋` | `--event-keywords` | help, pR, sR, sr | setting |
| `SOA_RESTORE_TOWER` | options.cpp:99 | bool: serve the tower and open its menu | `--restore-tower` | help, pR, client-changes.md | setting |
| `SOA_MASTER_DB` | options.cpp:100 | the campaign module's master DB | `--campaign-master-db FILE` | help, pR, campaign README | debug |
| `SOA_CAMPAIGN_SEED` | options.cpp:101 | a mission label (e.g. `mf01_001`): seed the campaign progress up to it | `--campaign-seed LABEL` | help, pR, sr, eR | test (campaign/episode/rental sessions) |
| `SOA_SERVER_FAIL` | options.cpp:102 | `Method:code[,Method:code]`: force error replies | `--fail` | help, pR, sr | test |
| `SOA_LOG_PACKETS` | options.cpp:103 | dir: the in-process packet log (`DIR/packets.log` + bodies) | `--log-packets DIR` | help, pR | debug / test (tests/diff) |
| `SOA_SERVER_SURPRISE` | options.cpp:104 | **`atoi`** (not `env_on`): non-zero number = force surprise missions | `--surprise` | help, pR, sr | test (`restore_missions.sh`) |

Read in `port/src/main.cpp`:

| Variable | Read at | Effect, format, default | CLI | Docs | Kind |
|---|---|---|---|---|---|
| `SOA_RESTORE` | main.cpp:343 | only a warning that it is gone (the in-process server is the default) | (`--restore` exits 2) | port/REMAINING.md (as removed) | dead |
| `SOA_NATIVES` | main.cpp:345 | `route` / `all` / `none`; default `route`; a bad value is `fatal` | `--natives`, `--no-native` (flag wins) | help, pR | debug |
| `SOA_HEADLESS` | main.cpp:502 | **`atoi`**: non-zero = hidden window; unset = headless only for `--selftest` | `--headless` / `--windowed` (flag wins) | help, pR, README.md | test (every session script exports it) |
| `SOA_SELFTEST_DELAY` | main.cpp:526 | seconds to wait after boot before `--selftest` runs; default 10 | none | nR | test |
| `SOA_SELFTEST_START_FILE` | main.cpp:527 | `--selftest` waits until this file exists instead | none | pR, nR | test |

Self-test and debug switches in `port/src/native/` (soa only):

| Variable | Read at | Effect | CLI | Docs | Kind |
|---|---|---|---|---|---|
| `SOA_SELFTEST_SKIP` | common/test.cpp:142 | comma list of test names `--selftest` skips | none | **none** (only the script's comment) | test (`selftest_resilient.sh`) |
| `SOA_SELFTEST_REPEAT` | common/test.cpp:152, 177 | run each matching test N times (port and server-library tests) | none | **none** | test |
| `SOA_TEST_HOOKS_SKIP` | common/test.cpp:53 | comma list of test-hook symbols (or `all`) not to install | none | **none** | test |
| `SOA_TEST_HOOKS_ALL` | common/test.cpp:65 | set at all (even `0`) = also install the three rebase-skipped cocos hooks | none | **none** | test |
| `SOA_STUB_TRACE` | common/guest_stub.cpp:204 | set at all (even `0`) = print stubbed calls | none | docs/notes.md | debug |
| `SOA_WIRE_DUMP` | api/wire_test.cpp:74 | file: the wire self-tests append their dumps there | none | **none** | debug |
| `SOA_<FAMILY>_CHECK`, `_CHECK_EVERY`, `_CHECK_OUT`, `_CHECK_ONLY`, `_CHECK_TRACE`, `_CHECK_DUMP` | common/live_check.cpp:81-91, 676-682 | the live guest-replay check of a native family; names built from the family's prefix | none | nR (as the pattern, prefix example `SOA_TAG`) | dead: no `live::Family` is constructed anywhere in `port/src` |

Server library (`server/src`, linked in-process) and web view (`webview/src`), soa's copies:

| Variable | Read at | Effect | CLI | Docs | Kind |
|---|---|---|---|---|---|
| `SOA_GACHA_POOLS` | server/src/master/gacha_pools.cpp:68 | the reconstructed gacha pools file, when `--gacha-pools` is empty; default `data/gacha_pools.sqlite3` in the checkout | `--gacha-pools FILE` (flag wins) | help, pR, sr | setting |
| `SOA_NOTICE_HTML_DUMP` | server/src/api/player/notice.cpp:293 | file: the self-test `player/notice` writes the notice page's HTML there | none | wv | debug (self-test only) |
| `SOA_WEBVIEW_FONT` | webview/src/fonts.cpp:74 | a font file tried first for the web view's Japanese face | none (`--font` is the text box's, not the web view's) | wv | setting |
| `SOA_WEBVIEW_DUMP_CSS` | webview/src/page.cpp:473 | file: append each stylesheet as litehtml gets it | none | wv | debug |

Runtime (`runtime/src`), the same in soa, soa-emu and soa-viewer:

| Variable | Read at | Effect, format, default | CLI | Docs | Kind |
|---|---|---|---|---|---|
| `SOA_TRACE` | core/trace.cpp:68 | `sym[=float][:off[,off..]];...` (mangled names or `0x<vaddr>`): log calls, args and results, optionally override the float result; not installed under soa `--selftest` | none | rR, eR, vR, notes.md (not pR) | debug / test (`tutorial_session.sh`, `emulator_session.sh`, `rental_session.sh`) |
| `SOA_COVERAGE` | core/profile.cpp:804 | dir: every guest function executed (`coverage.tsv`) | none | pR, rR, eR, vR | debug |
| `SOA_PROFILE` | core/profile.cpp:805 | dir: sampled guest stacks (`stacks.folded`); wins over `SOA_COVERAGE`'s dir if both differ | none | pR, rR, eR, vR | debug |
| `SOA_PROFILE_HZ` | core/profile.cpp:812 | sample rate, clamped 10..10000; default 1000 | none | pR | debug |
| `SOA_PROFILE_HOST` | core/profile.cpp:603 | bool (set, non-empty, not `0`), with `SOA_PROFILE`: host PCs inside natives (`host.tsv`) | none | pR | debug |
| `SOA_WATCHDOG` | app/host.cpp:110 | seconds without a presented frame before logging every guest stack; default off | none | pR, rR, eR, vR | debug |
| `SOA_OFFSCREEN_PRESENT` | app/host.cpp:747 | headless only: first char `0` = present to the hidden window, else offscreen; unset = offscreen unless the SDL video driver is `x11` | none | rR | debug |
| `SOA_FONT` | app/text_overlay.cpp:156 | the keyboard text box's font file, or `none`; default IPAex / Noto CJK / Droid / `fc-match` | `--font PATH` (flag wins) | help, pR, rR, README.md | setting |
| `SOA_GL_HOST_SRGB_ETC2` | hle/gles.cpp:105 | first char not `0` = pass sRGB ETC2 to the driver instead of decoding; default off (decode) | none | pR | debug |
| `SOA_GL_MAP_INVALIDATE` | hle/gles.cpp:174 | first char `0` = don't add `GL_MAP_INVALIDATE_RANGE_BIT`; default on | none | pR | debug |
| `SOA_GL_RELEASE_SHADER_COMPILER` | hle/gles.cpp:360 | first char not `0` = pass `glReleaseShaderCompiler` through; default dropped | none | pR | debug |
| `SOA_TRACE_RT` | hle/gles.cpp:268 | set at all (even `0`) = log render-target allocations and viewports | none | **none** | debug |
| `SOA_AUDIO_DUMP` | hle/opensles.cpp:93 | dir: each OpenSL ES player's PCM as `playerN.wav` | none | pR, notes.md | debug |
| `SOA_DIRECT_CALLS` | core/cpu.cpp:485 | first char `0` = always go through the JIT for host thunks; default on | none | nR | debug |

Non-`SOA_` inputs:

| Variable | Where | Effect |
|---|---|---|
| `HOME` | port main.cpp:170 | the default data dir `~/.local/share/soa-linux-370` (`--data` overrides) |
| `TZ`, `HOME`, `TMPDIR` | runtime hle/libc.cpp:156 | the only host variables the guest's `getenv` sees (all others return null). `TZ` also sets the local time that `--clock` / `SOA_CLOCK` / `--device-clock` are parsed in |
| `SDL_VIDEODRIVER`, `SDL_AUDIODRIVER`, any `SDL_*` hint | SDL2 itself | SDL picks the driver (documented in pR for `SDL_VIDEODRIVER`, `SDL_AUDIODRIVER=disk`). The code sets `SDL_HINT_VIDEO_X11_FORCE_EGL=1` (app/sdl_gl.cpp:97) and `SDL_HINT_IME_SUPPORT_EXTENDED_TEXT=1` (app/host.cpp:721) with `SDL_SetHint`, i.e. normal priority, so the environment variables `SDL_VIDEO_X11_FORCE_EGL` / `SDL_IME_SUPPORT_EXTENDED_TEXT` override them |
| child processes | runtime frontend/movie.cpp:48 (`ffmpeg`, `posix_spawnp` with the whole `environ`), app/text_overlay.cpp:139 (`fc-match` via `popen`) | inherit the full environment (`PATH` finds them; fontconfig's `FONTCONFIG_*` apply). No variable is set for them. The guest's own `popen` is refused |

## soa-server

4 `SOA_*` variables. The command line is the interface; `ServerConfig` (`server/include/soaserver/config.h`)
is filled from it.

| Variable | Read at | Effect | CLI | Docs | Kind |
|---|---|---|---|---|---|
| `SOA_ENABLE_EVENTS` | server/app/main.cpp:210 | `env_on`-style bool, as soa | `--enable-events` (flag wins) | help, sR | setting |
| `SOA_EVENT_KEYWORDS` | server/app/main.cpp:214 | comma list, as soa | `--event-keywords` (flag wins) | help, sR | setting |
| `SOA_GACHA_POOLS` | server/src/master/gacha_pools.cpp:68 | as soa | `--gacha-pools FILE` (flag wins) | help, sr | setting |
| `SOA_NOTICE_HTML_DUMP` | server/src/api/player/notice.cpp:293 | `--selftest player/notice` writes the HTML there | none | wv (`SOA_NOTICE_HTML_DUMP=… soa-server --selftest player/notice`) | debug |

No `HOME`, SDL or child processes. **Not read**, although `soa-server --help` names them next to the
flags: `SOA_SERVER_DB`, `SOA_SERVER_MASTER`, `SOA_SERVER_SEED`, `SOA_SERVER_GAME_XML`,
`SOA_SERVER_SEED_RNG`, `SOA_RESTORE_NEW_PLAYER`, `SOA_MASTER_DB`, `SOA_CAMPAIGN_SEED`,
`SOA_SERVER_FAIL`, `SOA_SERVER_SURPRISE` (see Findings).

## soa-emu

14 `SOA_*` variables, all the runtime's (the soa table's "Runtime" section: `SOA_TRACE`,
`SOA_COVERAGE`, `SOA_PROFILE`, `SOA_PROFILE_HZ`, `SOA_PROFILE_HOST`, `SOA_WATCHDOG`,
`SOA_OFFSCREEN_PRESENT`, `SOA_FONT`, `SOA_GL_HOST_SRGB_ETC2`, `SOA_GL_MAP_INVALIDATE`,
`SOA_GL_RELEASE_SHADER_COMPILER`, `SOA_TRACE_RT`, `SOA_AUDIO_DUMP`, `SOA_DIRECT_CALLS`), plus the
non-`SOA_` inputs of soa's last table. `emulator/src/main.cpp` itself reads only `HOME` (line 212: the
default data dir `~/.local/share/soa-emulator-370/phone`).

| Variable | CLI in soa-emu | Docs for soa-emu |
|---|---|---|
| `SOA_FONT` | `--font PATH` (flag wins) | help |
| `SOA_TRACE`, `SOA_PROFILE`, `SOA_COVERAGE`, `SOA_WATCHDOG` | none | eR:46 ("the runtime's environment switches") |
| `SOA_PROFILE_HZ`, `SOA_PROFILE_HOST`, `SOA_OFFSCREEN_PRESENT`, the three `SOA_GL_*`, `SOA_AUDIO_DUMP`, `SOA_DIRECT_CALLS` | none | only in pR / rR / nR, written as soa's |
| `SOA_TRACE_RT` | none | none |

soa-emu reads **no** `SOA_DOWNLOAD_DIR`, `SOA_HEADLESS` or `SOA_REPO` (it has `--download-dir`,
`--headless`, `--repo` only), and no server variables (the server is a separate soa-server).

## soa-viewer

16 `SOA_*` variables: the runtime's 14 (as soa-emu) plus two in `emulator-viewer/src/main.cpp`:

| Variable | Read at | Effect | CLI | Docs | Kind |
|---|---|---|---|---|---|
| `SOA_DOWNLOAD_DIR` | emulator-viewer/src/main.cpp:266 | the asset fallback dir; default none | `--download-dir DIR` (flag wins) | help, vR | setting |
| `SOA_DOWNLOAD_PREFER` | emulator-viewer/src/main.cpp:268 | bool (set, non-empty, not `0`) | `--download-prefer` (flag wins) | help, vR | setting |

Plus `HOME` (main.cpp:225: default data dir `~/.local/share/soa-viewer-380`) and the runtime's non-`SOA_`
inputs. `vR:43` lists the same four runtime switches as `eR`.

## Shared

- **runtime/** reads 14 variables (all debug, except `SOA_FONT`), the same in soa, soa-emu and
  soa-viewer; only `SOA_FONT` has a flag (`--font`, in all three). `runtime/README.md` documents
  `SOA_WATCHDOG`, `SOA_FONT`, `SOA_OFFSCREEN_PRESENT` and points at the tracing / profiling ones; the
  GL switches, `SOA_AUDIO_DUMP` and `SOA_PROFILE_HZ` / `_HOST` are in `port/README.md` only.
- **server/** reads `SOA_GACHA_POOLS` and `SOA_NOTICE_HTML_DUMP` itself, so both soa and soa-server
  honour them. Every other server setting reaches the library through `ServerConfig`: soa fills it from
  `RunOptions` (CLI + `SOA_*`), soa-server from its CLI plus `SOA_ENABLE_EVENTS` / `SOA_EVENT_KEYWORDS`.
- **webview/** (soa only) reads `SOA_WEBVIEW_FONT`, `SOA_WEBVIEW_DUMP_CSS`. The `SOA_WEBVIEW` switch is
  gone (4c6b80e): the web view is always on with the in-process server.
- **platform370/** reads nothing.

### What the scripts set

No binary reads these; they are script interfaces only: `SOA_PHONE`, `SOA_SHARED_PHONE`,
`SOA_EPISODE_PACKS` (port/scripts/phone370.sh, scripts/shared-phone.sh, scripts/make-phone-370.sh);
`SOA`, `SOA_EMU`, `SOA_SERVER` (tests/diff: the binaries); `SOA_LIB`, `SOA_V370`, `SOA_V380`
(tools/common.sh, decomp scripts, server/tests/ninja/tools); `SOA_GHIDRA_MCP_PROJECT`
(scripts/ghidra-mcp.sh); `EMU_DATA`, `SERVER_ARGS`, `KEEP_DATA`, `SMOKE_CLOCK`, `PER_RUN_TIMEOUT`,
`FLOW_MAX_RMSE` / `FLOW_NOTICE_WAIT` / `FLOW_BONUS_WAIT` (control/flowctl.py), `NINJA_CHECK_BIN`.

Variables the scripts set **for the programs** when they launch them:

| Variable | Set by | Program |
|---|---|---|
| `SOA_HEADLESS` (`${SOA_HEADLESS:-1}`, exported) | every `port/scripts/*_session.sh`, `restore_missions.sh`, `profile_extra.sh`, `smoke.py` | soa |
| `SOA_SERVER_SEED_RNG` (`1`; `605` in the Sphere 211 sessions) | nearly every port session script, `smoke.py` | soa |
| `SOA_RESTORE_NEW_PLAYER=1` | `tutorial_session.sh`, `newplayer_session.sh` | soa |
| `SOA_CAMPAIGN_SEED` | `campaign_session.sh`, `episode_movie_session.sh`, `rental_session.sh` | soa |
| `SOA_CLOCK` | `rental_session.sh`, `restore_missions.sh` | soa |
| `SOA_SERVER_SURPRISE=1` | `restore_missions.sh` | soa |
| `SOA_TRACE` (`CCharacterObject::OnDamage`) | `tutorial_session.sh`, `rental_session.sh`; `emulator_session.sh --new-player` | soa; soa-emu |
| `SOA_PROFILE`, `SOA_COVERAGE` | `profile_extra.sh` (and documented by-hand runs) | soa |
| `SOA_SELFTEST_SKIP` | `selftest_resilient.sh` | soa |
| `SDL_AUDIODRIVER` (`dummy` unless set) | `tutorial_session.sh`, `newplayer_session.sh`, tests/diff `targets.py` | soa, soa-emu |

soa-server is always configured by flags in the scripts (`emulator_session.sh`, tests/diff pass
`--seed-rng 1`, `--clock`, `--seed`, ...). tests/diff's `proc.py` passes the caller's whole environment to
every program, so a `SOA_*` in the caller's shell reaches soa, soa-server and soa-emu alike.

So `SOA_SERVER_SEED_RNG`, `SOA_SERVER_SURPRISE`, `SOA_CAMPAIGN_SEED`, `SOA_SELFTEST_*`,
`SOA_TEST_HOOKS_*` and (mostly) `SOA_HEADLESS` are in practice a test-harness interface for soa.

## Findings

### Undocumented (read, documented nowhere)

`SOA_SELFTEST_SKIP`, `SOA_SELFTEST_REPEAT`, `SOA_TEST_HOOKS_SKIP`, `SOA_TEST_HOOKS_ALL`, `SOA_WIRE_DUMP`
(soa); `SOA_TRACE_RT` (all three runtime programs). Documented only in a code comment or a historical
note: `SOA_STUB_TRACE` (docs/notes.md), `SOA_DIRECT_CALLS` (port/src/native/README.md). `SOA_TRACE` is in
runtime/, emulator/ and viewer READMEs but not in `port/README.md`, soa's main document.

### Dead

- `SOA_RESTORE`: read only to warn that it is gone (main.cpp:343).
- The `SOA_<FAMILY>_CHECK*` family (live_check.cpp): the harness is compiled into soa but no family is
  registered since the natives were removed, so no prefix exists. `port/src/native/README.md` still
  describes it, and `tools/gen_*_a2c.py` would generate `SOA_ARENA_CHECK`, `SOA_OBJBASE_CHECK`,
  `SOA_OBJBASE_ALL`, `SOA_DYNAMICS_A2C`, `SOA_RENDER_A2C`, `SOA_INFOBASE_A2C`, `SOA_ASKA_MATH_OFF` /
  `_SKIP` into code that isn't built any more.
- `zz_server_guest_test.cpp:64-86` (`server/no-setenv-state`) exempts a `setenv("SDL_VIDEODRIVER")` and
  says it's "the only setenv in port/src"; there is none now.

### Stale docs (documented, no longer read)

- **`soa-server --help`** marks `--master`, `--seed`, `--game-xml`, `--seed-rng`, `--new-player`,
  `--campaign-master-db`, `--campaign-seed`, `--fail`, `--surprise` with soa's variable names
  (`(SOA_SERVER_MASTER; default …)`, `(SOA_RESTORE_NEW_PLAYER=1)`), which read as if soa-server honoured
  them; it doesn't (only `--db` says `(soa: SOA_SERVER_DB)`). `server/app/main.cpp:208`'s comment "the same environment fallbacks as soa" is true
  only for the two event variables. `server/README.md:107` ("`--data` for soa's `SOA_SERVER_*`
  variables") says it right but tersely. `server/include/soaserver/config.h`'s field comments name the
  `SOA_*` variables too, and its header says "the server reads nothing else", which the library's own
  `getenv("SOA_GACHA_POOLS")` / `getenv("SOA_NOTICE_HTML_DUMP")` contradict.
- `SOA_FAKE_SERVER_DRIVE`: described as current in `docs/client-changes.md:87` and `docs/api.md:205`
  (port/README.md:301 says it was removed on 2026-10-01).
- `SOA_WEBVIEW`: `docs/webview.md:192` correctly says it's gone; `docs/webview.md:239` (the W0 plan row)
  still describes the feature "behind `SOA_WEBVIEW`" (historical).
- `docs/notes.md` still names removed native switches as if live: `SOA_NO_APINOTIFY_NATIVE`,
  `SOA_NO_BATTLE_CALC_NATIVE`, `SOA_NO_BATTLE_CORE_NATIVE`, `SOA_NO_DEBUGWIN_NATIVE`,
  `SOA_NATIVE_AUDIO`, `SOA_NATIVE_INPUT`, `SOA_PARAM_DUMP`, `SOA_BATTLE_CORE_CHECK`,
  `SOA_BATTLE_DAMAGE_LOG` (lines ~424-1726). They describe past verification runs; whether notes.md
  counts as history is the user's call. `docs/history/` mentions many more (`SOA_ORACLE_370`,
  `SOA_OBJBASE_*`, `SOA_*_A2C`, `SOA_GUEST_REPORT`, `SOA_INFOBASE_GEN`, `SOA_PARAM_LAYOUT_DUMP`,
  `SOA_RESTORE370_ON`); those are historical by design.
- `SOA_ENGLISH` (docs/basmaster-gl.md:330) and `SOA_API` (server/PLAN-readability.md) are proposals, not
  variables.
- `docs/server-rules.md:570` gives the master DB as "`SOA_SERVER_MASTER`, else …" without `--master`
  (soa-server has only the flag).

### No command-line equivalent (candidates for one)

- soa: `SOA_DOWNLOAD_PREFER` (soa-viewer has `--download-prefer`), `SOA_FAKE_SERVER`,
  `SOA_FAKE_SERVER_SCHEMA`, `SOA_MEMSTATS`, `SOA_SELFTEST_DELAY` / `SOA_SELFTEST_START_FILE` (both modify
  `--selftest`), `SOA_WEBVIEW_FONT` (could fold into `--font`, as docs/webview.md:152 already proposes:
  "one environment variable, `SOA_FONT`, for both").
- runtime (all three): `SOA_TRACE`, `SOA_PROFILE` / `SOA_COVERAGE`, `SOA_WATCHDOG` are user-visible
  diagnostics used across programs; the GL switches are deliberate escape hatches and probably fine as
  environment only.

### Inconsistencies

- **The same setting, different interfaces per program.**
  - `SOA_DOWNLOAD_DIR`: soa and soa-viewer read it, soa-emu doesn't (yet the viewer's help says "as soa
    / soa-emu --download-dir; env SOA_DOWNLOAD_DIR"). `--download-prefer` exists in soa-viewer only;
    soa has the variable only, soa-emu neither.
  - `SOA_HEADLESS`: soa only; soa-emu / soa-viewer have `--headless` and no `--windowed`.
  - `SOA_REPO`: soa only; the other three have `--repo` only.
  - Server settings: soa reads `SOA_SERVER_MASTER` etc.; soa-server takes `--master` etc. but not the
    variables, except `SOA_ENABLE_EVENTS` / `SOA_EVENT_KEYWORDS` / `SOA_GACHA_POOLS`. A shell that
    exports `SOA_SERVER_MASTER` gets different masters in soa and soa-server.
  - Naming: the server's run options mix `SOA_SERVER_*` (`DB`, `MASTER`, `SEED`, `GAME_XML`,
    `SEED_RNG`, `FAIL`, `SURPRISE`), `SOA_RESTORE_*` (`NEW_PLAYER`, `TOWER`: from the removed
    `--restore`), bare names (`SOA_CLOCK`, `SOA_START_COINS`, `SOA_GALAXY_PASS`, `SOA_ENABLE_EVENTS`,
    `SOA_EVENT_KEYWORDS`, `SOA_GACHA_POOLS`, `SOA_CAMPAIGN_SEED`, `SOA_LOG_PACKETS`) and one that doesn't
    match its flag at all (`SOA_MASTER_DB` = `--campaign-master-db`, easily confused with
    `SOA_SERVER_MASTER` = `--master`). `SOA_RESTORE_NEW_PLAYER` = `--new-player`.
- **`--gacha-pools` / `SOA_GACHA_POOLS` (added today) bypass soa's `RunOptions`**: `options_from_env`
  has no line for it; the library reads the variable when the path is empty. The precedence is the
  same (flag, variable, `data/gacha_pools.sqlite3`), but it is the one run option not in
  `RunOptions`, and it is how soa-server ends up honouring it.
- **`soa --server HOST` ignores server variables silently.** Server flags given with `--server HOST`
  get a warning ("have no effect … give them to soa-server"); the same settings from `SOA_SERVER_*`
  etc. don't (`server_flags` collects only flags).
- **Five truthiness rules for switches:** `env_on` (set, non-empty, not `0`: options.cpp, soa-server's
  event switch, the viewer, `SOA_PROFILE_HOST`); `atoi != 0` (`SOA_HEADLESS`, `SOA_SERVER_SURPRISE`,
  so `=yes` is off); "set at all" (`SOA_TRACE_RT`, `SOA_STUB_TRACE`, `SOA_TEST_HOOKS_ALL`: `=0` turns
  them on); first char not `0` (`SOA_GL_HOST_SRGB_ETC2`, `SOA_GL_RELEASE_SHADER_COMPILER`); default-on
  unless first char `0` (`SOA_DIRECT_CALLS`, `SOA_GL_MAP_INVALIDATE`, `SOA_OFFSCREEN_PRESENT` when
  set).
- **Env vs flag validation differ:** `SOA_GUEST_CPUS` has no 1..256 check; `SOA_START_COINS` parses
  base 0 (so `0300` is octal) vs the flag's base 10; an unparsable `SOA_CLOCK` is ignored silently
  where `--clock` exits 2; a bad `SOA_NATIVES` is `fatal` where `--natives` exits 2.
- **SDL hints are overridable from the environment** (normal-priority `SDL_SetHint`):
  `SDL_VIDEO_X11_FORCE_EGL=0` would put SDL's X11 contexts back on GLX, which the runtime's EGL
  emulation assumes they aren't. Probably harmless, undocumented.

### Recommendations (for the user to decide; none implemented)

1. Fix `soa-server --help` (and config.h's comments): drop the `SOA_*` names from options soa-server
   doesn't read, or make soa-server read the same variables as soa through one shared
   `options_from_env`-style helper in the server library (then also `SOA_GACHA_POOLS` moves there and
   soa's `RunOptions` gets it).
2. Decide whether server settings should have environment fallbacks at all: they are mainly a
   test-harness interface (session scripts) and could become flags in the scripts, leaving the
   environment to debugging switches.
3. If the variables stay: rename toward one scheme (e.g. `SOA_SERVER_<FLAG>` for every server flag;
   `SOA_MASTER_DB` → `SOA_SERVER_CAMPAIGN_MASTER_DB`, `SOA_RESTORE_*` → `SOA_SERVER_NEW_PLAYER` /
   `_RESTORE_TOWER`), keeping the old names as warned aliases for a while.
4. Warn in soa for server variables under `--server HOST`, as for the flags.
5. One truthiness rule (`env_on`) and the flags' validation for every variable.
6. Make the runtime-program options consistent: `--download-prefer` in soa and soa-emu,
   `SOA_DOWNLOAD_DIR` in soa-emu (or drop it from the viewer), `--windowed` / `SOA_HEADLESS` in the
   emulators or neither.
7. Remove dead code: `SOA_RESTORE`'s warning (eventually), the `live_check` harness or its README text
   if it won't come back, the `SDL_VIDEODRIVER` exemption in `server/no-setenv-state`.
8. Document `SOA_SELFTEST_SKIP` / `_REPEAT`, `SOA_TEST_HOOKS_*`, `SOA_TRACE_RT`, `SOA_WIRE_DUMP`, and
   `SOA_TRACE` in port/README.md; list the runtime's switches once in `runtime/README.md` and link it
   from the three program READMEs.
9. Fix the stale `SOA_FAKE_SERVER_DRIVE` mentions in docs/client-changes.md and docs/api.md; decide
   about the removed switches in docs/notes.md.
10. Consider `--fake-server DIR`, `--memstats [S]` for soa, and fold `SOA_WEBVIEW_FONT` into
    `--font` / `SOA_FONT` as docs/webview.md proposes.
