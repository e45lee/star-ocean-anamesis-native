# port/src: where things live

The `soa` binary is built from every `*.cpp` under this folder (`port/CMakeLists.txt`, `GLOB_RECURSE`; part of the repository's build, `cmake -S . -B build`: `build/port/soa`) plus the JIT host runtime library, `runtime/` at the repo root (`libsoaruntime`; `runtime/README.md`), whose objects are linked first, and the local server library, `server/` at the repo root (`libsoaserver`; `server/README.md`), linked last. Includes are always written from here or from `runtime/src`: `#include "native/battle/battle_calc.h"`, `#include "core/cpu.h"`.

The runtime (`runtime/src/`) holds what any host of the Android `libSOA.so` needs:

| Folder | What it is |
|---|---|
| `runtime/src/core/` | Loader (ELF mapping), the dynarmic JIT CPU, guest memory, the HLE registry, the emulated device (`core/device.h`), tracing, profiling, the runtime self-test registry (`core/selftest.h`) |
| `runtime/src/hle/` | High-level emulation of the Android imports: libc, pthreads, EGL emulated over the host's GL contexts (`egl.cpp`), GLES → host GL (`gles.cpp`, `etc2.cpp`), OpenSL ES, `dlopen` |
| `runtime/src/android/` | NDK surface: `AAssetManager` over the APKs, the download dir and the stand-in overlay; SharedPreferences (`prefs`); zip; the platform state and the host's hooks (`platform.h`) |
| `runtime/src/jni/` | The C++ JVM emulation: the Java classes the game calls through JNI |
| `runtime/src/frontend/` | Movie playback (ffmpeg) |

This folder is the port:

| Folder | What it is |
|---|---|
| `main.cpp` | Command line and startup: the 3.7.0 APK and lib, platform370, the server mode (`--server inproc\|HOST`), natives, `--selftest` (as `HostConfig::tick`) and the port's debug commands (`HostConfig::command`). The window, input, audio and main loop are the runtime's desktop host loop, `runtime/src/app/host.h` |
| `core/` | Port-only run state: options (`core/options.h`: `ClientOptions` + `ServerOptions`, the two groups of `soa --help`) and repo paths (`core/paths.h`). The rest of `core/` is in `runtime/src/core/`; both are reached as `core/...` |
| (`server/` at the repo root) | The local game server for `--server inproc` is the library `libsoaserver` (`server/README.md`; rules in `docs/server-rules.md`). The port's side of it (capturing requests from the guest as the wire carries them, battle log included, the `soaserver/hooks.h` asset index, the config from the run options, the in-process CDN, the tests that need the game) is `native/api/server_adapters.*`, `server_cdn.cpp` and `zz_server_guest_test.cpp` |
| (`platform370/` at the repo root) | The 3.7.0 platform layer shared with `soa-emu` (`platform370/README.md`) |
| `native/` | Guest functions replaced by native C++: everything below |

## `native/`
**Since the rebase's revision 2 (2026-10-01) the native families are gone** (`docs/history/PLAN-rebase-370.md`; git history keeps them) and are being rebuilt for 3.7.0, as readable C++ from the Ghidra decompile, each in a subsystem folder with its differential tests. What is here now: the in-process route, the test and check infrastructure, and the port's own hooks (`native/README.md` "What's native now"). A generated file goes in a **`gen/`** subfolder and names its generator in its first lines (`tools/gen_*.py`); **never edit `gen/` by hand**.

File-name conventions inside a folder:
- `<family>.cpp` / `.h`: natives.
- `*_test.cpp`: selftests (`soa --selftest "<prefix>/"`). `zz_*_test.cpp` must register last. `--selftest` runs the runtime's own `RUNTIME_TEST`s (`runtime/src/core/selftest.h`) first, then these, then the server library's.

| Folder | Contents |
|---|---|
| `common/` | Native framework: registration (`native.h`: `NATIVE_FUNCTION`, `--natives route\|none`), the selftest harness (`test.h`), guest-call helpers (`guest_std`, `guest_stub`), the live-check library (`live_check`) and its register file (`a2c_regs`), `arm_float.h`, memstats, guest-call benchmarks, and the port's debug control commands (`port_debug.cpp`: the `CPhase::Progress` wrapper) |
| `api/` | The in-process route: the `FakeApiCaller` hooks (`fakeapi.cpp`, `gen/fakeapi_tables.inc`), the adapters to the server library (`server_adapters.*`), the in-process CDN (`server_cdn.cpp`), the wire-format test (`wire_test.cpp`, `gen/wire_table.inc`), the server tests that need the game |
| `restore/` | The tower opt-in (`restore_tower.cpp`, `--restore-tower`; `docs/client-changes.md` "Tower") |
| `ui/` | The notice board's local page (`webview_local.cpp`; `docs/client-changes.md` "Notice board page") |

`native/README.md` has how to write a native and its tests.
