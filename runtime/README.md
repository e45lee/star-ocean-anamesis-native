# runtime/: the JIT host runtime (libsoaruntime)

Everything a program needs to run the Android `libSOA.so` (ARM64) on x86-64 Linux, without the game-specific parts. The port (`port/`, the `soa` binary) is one host program built on it; the 3.7.0 emulator (`emulator/`, `soa-emu`) and the 3.8.0 viewer (`emulator-viewer/`) are others. What the 3.7.0 client needs beyond the runtime (its Java answers, `fmod`, the device clock, the `service_stop_day` patch, the network glue) is the library `platform370/` (`platform370/README.md`), built on these extension points: `soa-emu` links it, and the port will in P1 of `docs/history/PLAN-rebase-370.md`.

The runtime knows nothing about:
- which build of the game it runs (the port and the emulator run 3.7.0, the viewer, `emulator-viewer/`, the offline build);
- the local server (`server/` at the repo root, libsoaserver);
- the port's native replacements (`port/src/native/`);
- the window toolkit, in its core: SDL, input and the audio device live in the optional desktop host loop, `src/app/` (target `soaruntime_app`), which `soa` and `soa-emu` share.

Whatever differs between hosts is set by the host through the extension points below.

## What's in it

| Folder | Contents |
|---|---|
| `src/core/` | ELF loader (`loader.h`: the game library), the dynarmic JIT CPU and guest calls (`cpu.h`, `abi.h`), the HLE registry (`hle.h`), the guest filesystem view (`vfs.h`), the emulated device (`device.h`), logging (`log.h`), tracing (`SOA_TRACE`), profiling (`SOA_PROFILE` / `SOA_COVERAGE`), the runtime self-test registry (`selftest.h`) |
| `src/hle/` | The Android imports: bionic libc / libm / pthreads over glibc, EGL emulated over the host's GL contexts (`egl.cpp`; `gfx.h`: `GfxHooks`, the host's contexts and window) and GLES to host GL (`gles.cpp`), OpenSL ES (mixed by the host through `audio.h`), `dlopen` |
| `src/android/` | NDK objects: `AAssetManager` over APKs the host adds (`ndk.h`), `ANativeWindow`, input queue, SharedPreferences, zip; the platform state shared with the host (`platform.h`) |
| `src/jni/` | The C++ JVM: the Java classes the game calls through JNI (`java_android.cpp`; `java_playcore.cpp`, the Play Core classes that only the viewer's lib, `emulator-viewer/`, uses) |
| `src/frontend/` | Movie playback via ffmpeg (`movie.h`; the host draws and mixes it) |
| `src/app/` | The desktop host loop (`app/host.h`): the SDL2 window and its GLES contexts (`app/sdl_gl.h`; X11 or Wayland), presentation and screenshots, mouse and keyboard input, text entry and its on-screen box (`app/text_overlay.h`; below, "Text entry"), the audio device and its null sink, the control commands (`--do`, `--shot`, `--control` FIFO), the `ANativeActivity` bring-up (`JNI_OnLoad`, `onCreate`, the start-up callbacks) and the main loop. Moved from `port/src/main.cpp`; a separate target because it links SDL2 |
| `tests/` | `soaruntime_tests`: the extension points, exercised without a game |

Includes are written from `src/`: `#include "core/cpu.h"`. The include path of a runtime user is `runtime/src` (target `soaruntime_iface`).

## Building and linking

`runtime/CMakeLists.txt` is a subdirectory of the repository's build (`cmake -S . -B build`, the root `README.md`, "Building"), added before `server/`, `port/` and `emulator/`, into `build/runtime/`. The root `CMakeLists.txt` provides what it uses (`cmake/deps.cmake`): the `dynarmic` target (CMake `FetchContent`, pinned), `soa::EGL` / `soa::GLESv2` (Mesa's libraries, the Khronos headers from vcpkg), `ZLIB::ZLIB`, and for `soaruntime_app` `soa::SDL2` (vcpkg). The runtime links dynarmic, EGL, GLESv2, zlib, pthread and dl.

| Target | Use |
|---|---|
| `soaruntime_iface` | INTERFACE: include dir, compile definitions, libraries |
| `soaruntime_objs` | OBJECT: the runtime's objects. The port links them **first**: link order is static-initializer order, and `soa` keeps the order it had before the split (`port/CMakeLists.txt`) |
| `soaruntime` | STATIC archive of the same objects. Link it whole (`$<LINK_LIBRARY:WHOLE_ARCHIVE,soaruntime>`): a plain static link drops objects nothing references, such as the self-registering `RUNTIME_TEST`s |
| `soaruntime_tests` | The extension-point tests. They link `soaruntime` alone, so a runtime that needed port code would fail to link |
| `soaruntime_app` | STATIC: the desktop host loop (`src/app/`), with SDL2. Not part of `soaruntime`. `soa` and `soa-emu` link it as a plain library: it has no self-registering objects |

**The runtime must not include anything from `port/`, `server/`, `emulator/` or `platform370/`.** This is enforced three ways:
1. **Configure time:** `runtime/CMakeLists.txt` checks that every quoted `#include` in `runtime/` names a file in `runtime/src` (or next to the including file), or dynarmic.
2. **Compile time:** the runtime's include path is `runtime/src` only.
3. **Link time:** `soaruntime_tests` links the whole archive without the port.

## Extension points

A host program brings the runtime up in this order. `port/src/main.cpp` and `emulator/src/main.cpp` are the references. A 3.7.0 host also calls `platform370::install(cfg)` before `hle_init()` and `platform370::install_patches(*lib)` after `load_library` (`platform370/README.md` "API").

```
host_hooks() = {...}; device_config() = {...};   // what the host provides / the device it emulates
vfs_init({data_dir});
cpu_global_init();
hle_init();            // built-in imports, then the hle_add_registrar() callbacks
jni::Vm::get().init(); // built-in Java classes, then the add_class_installer() callbacks
load_library(lib);     // imports are bound here
asset_manager().add_apk(...) ...;  // the host's APK list
run_initializers(*lib);
app::run(*lib, cfg);    // optional desktop host loop (app/host.h): window, JNI_OnLoad, ANativeActivity_onCreate, main loop
```

### HLE imports (`core/hle.h`)
- **`bool hle_add_registrar(std::function<void(Hle&)>)`:** the callback runs at the end of `hle_init()`, after the built-in modules, in registration order. Register before `hle_init()`; a static initializer works (`static bool r = hle_add_registrar(...)`).
- **`HostFn Hle::override_fn(name, HostFn f)`:** binds the import `name` to `f`, replacing a built-in thunk or adding a new import (e.g. a libm function only one build imports). It returns the host function it replaced, or nullptr, so `f` can delegate: `g_orig(c)`.
- **`HostFn Hle::host_fn(name)`:** the host function an import is bound to.
- `Hle::fn` / `Hle::data` (the built-in modules' registration) are public too. Example: platform370 supplies its own `getaddrinfo` / `gethostbyname` / `connect` (`platform370/src/net_370.cpp`).
- **When:** imports are resolved when a library is loaded, so override before `load_library()`.
- **Signature:** a `HostFn` is `void(Cpu&)`. It reads its arguments from the guest registers (`arg<T>(c, i)`, or `wrap<&fn>()` for a C function of the same signature) and sets `x0`.

### Java classes and methods (`jni/jvm.h`)
- **`bool jni::add_class_installer(std::function<void(Vm&)>)`:** the callback runs at the end of `Vm::init()`, after the built-in classes, in registration order. Register before `Vm::init()`.
- In an installer, or at any time:
  - **`vm.define_class(name, super)`** and **`vm.def(cls, name, sig, impl, is_static)`** add classes and methods;
  - **`vm.override_method(cls, name, sig, fn, is_static)`** replaces a method. `fn(self, args, original)` gets the implementation it replaces (from `cls` or its nearest superclass; empty if none) to delegate to. The `Method` object is reused, so method IDs the game already holds stay valid.
- **Example:** the port shows its local server's web pages by overriding `SOAActivity.ShowWebView`, falling back to the runtime's implementation (`port/src/native/ui/webview_local.cpp`).
- Unknown methods return 0 with a warning (`jni: unknown method ...`). That is how missing ones show up.

### The emulated device (`core/device.h`)
`DeviceConfig& device_config()`:
- **`guest_cpus`:** the CPU count the guest sees (`sysconf`, `/sys/devices/system/cpu/{present,possible}`). Default 8; 0 = the host's count.
- **`app_version`:** what `SOAActivity.GetApplicationVersion` returns. The host sets it (the port and the emulator through `platform370::install`: `"3.7.0"`); the runtime has no default version.

### The desktop host loop (`app/host.h`, target `soaruntime_app`)
- **`app::install_host_hooks()`:** sets `host_hooks()` (audio device, text input, movies). Call it first.
- **`app::start_watchdog()`:** `SOA_WATCHDOG`.
- **`app::run(lib, HostConfig&)`:** never returns. It opens the window, starts the activity and runs the main loop. `HostConfig` holds:
  - the window: title, size, landscape, fullscreen, `hidden` (headless, still rendering: `soa --headless` and `--selftest`, `soa-emu --headless`) and the game's render size;
  - `font`: the text box's font (`--font` in soa, soa-emu and soa-viewer; below, "Text entry");
  - the scripted shots and actions, and the control FIFO;
  - two hooks: `command` (control commands the loop doesn't know; the port's `phase:` / `call:` debug commands) and `tick` (once per main-loop iteration; the port's `--selftest` runner).

### The host's frontend (`android/platform.h`, `hle/gfx.h`, `hle/audio.h`)
- **`HostHooks& host_hooks()`:**
  - `start_text_input`: `SOAActivity.StartKeyboardActivity`;
  - `play_movie`: `SOAActivity.PlayMovie`, with `platform().movie_*` set;
  - `start_audio`: the first OpenSL ES output mix. It must be idempotent.
  Unset hooks do nothing.
- **`set_gfx_hooks(GfxHooks*)`:** the host's GL contexts behind the guest's EGL (create, share, make current on the window or for a pbuffer, swap, swap interval, the window's drawable size), offscreen presentation, the viewport, the overlay drawn after each frame. Below, "Graphics".
- **`audio_mix(out, frames, rate)`** and **`movie_mix_audio`**: the host's audio device pulls from these.
- **`platform()`:** the surface size, the text-entry and movie state, `quit_requested`. `platform_post_ui` / `platform_run_ui_tasks` are the UI-thread queue, which the host runs from its main loop.

### Assets (`android/ndk.h`)
- **The APK list is the host's:** `asset_manager().add_apk(path)` for each APK, in order (a later APK wins). The runtime names no APK. The port and the emulator add the single 3.7.0 APK.
- Play Asset Delivery packs: `platform_add_asset_pack(name)`.
- `set_download_dir(dir, prefer)` and `set_standin_dir(dir)` add directory sources.
- **Not the runtime's job:** finding and extracting `libSOA.so`; the host passes a path to `load_library`.

### Guest function hooks (`core/cpu.h`)
A host can replace a guest function, or filter its calls, with host code:
- **`u64 make_original_trampoline(u64 guest_addr)`:** builds guest code that runs the function's original first two instructions and jumps back to the rest. Call it **before** hooking. It returns 0 when one of them is PC-relative (it can't be moved).
- **`void hook_guest_function(u64 guest_addr, const char* name, HostFn fn)`:** overwrites the function's entry with `SVC #n; RET`, so every call (direct, PLT or virtual) runs `fn`. `fn` reads the guest registers (`c.x(0)`, `c.x(8)` for an sret result, ...) and sets the result registers; to defer to the original it calls the trampoline, e.g. `guest_call_raw(orig, ints, n, nullptr, 0, c.x(8))`.
- **When:** after `load_library`, before guest code runs (`run_initializers`), so no JIT has translated the entry yet. Later patches need `invalidate_guest_code`. The function must be at least 8 bytes long (the stub is two instructions).
- **Users:** the port's native replacements (`port/src/native/common/native.cpp`: a registry by symbol, with size checks and aliases) and platform370's one patch (`platform370/src/patch_370.cpp`, used by `soa-emu`).

### Self-tests (`core/selftest.h`)
- `RUNTIME_TEST("area/name") { ... t.fail(...); t.expect_eq(a, b, "what"); }` registers a test of the runtime itself that needs no game code.
- The host's runner runs `runtime_tests()`. `soa --selftest` runs them first, through an adapter in `port/src/native/common/test.cpp`, then the port's `NATIVE_TEST`s. Today there are four: `frontend/movie-ends-without-audio-device`, `audio/opensl-queue-drains`, `cpu/tbi-tagged-data-addresses` and `jni/references-low-byte` (below, "Platform fidelity"). `soaruntime_tests` also runs the `cpu/` and `jni/` ones.
- Tests that need the guest library or port code are `NATIVE_TEST`s in the port.
- The extension-point tests are a separate program, `soaruntime_tests`, so that `soa --selftest` doesn't change:

```sh
build/runtime/soaruntime_tests     # prints ok/FAIL per check, PASS/FAIL at the end
```

## Graphics: the guest's EGL over SDL's GL contexts

The window, its surface and every GL context belong to the host: `app/sdl_gl.cpp` creates them with SDL2 (`SDL_WINDOW_OPENGL`, `SDL_GL_CreateContext`, `SDL_GL_MakeCurrent`, `SDL_GL_SwapWindow`) on whatever video driver SDL picks. The runtime never opens an EGL display or surface itself: `hle/egl.cpp` emulates the guest's 17 EGL imports over `GfxHooks`, and `hle/gles.cpp` passes its GL calls to the host's GLES. There is no X11 code left in the build; the window system is SDL's business.

**What the guest gets** (`Aska::RenderDeviceGL`, 3.7.0 and soa-viewer's 3.8.0 alike; every call is logged under `egl`):
- `eglGetDisplay` / `eglInitialize`: a pseudo display; the guest is told EGL 1.4.
- One config: RGBA8, depth 24, stencil 8, no multisampling, window and pbuffer surfaces, ES2 and ES3 renderable, `EGL_NATIVE_VISUAL_ID` 1 (Android's `WINDOW_FORMAT_RGBA_8888`: the game passes it to `ANativeWindow_setBuffersGeometry`, which ignores it). `eglChooseConfig` matches requests against it by the EGL rules (at least / mask / exact). The game asks three times: `{DEPTH 24}` (1 config: it keeps depth 24), `{SURFACE_TYPE SWAP_BEHAVIOR_PRESERVED}` (0 configs; it doesn't use the result) and RGBA8 + D24 + S8 ES2 (1). Unknown attributes fail with `EGL_BAD_ATTRIBUTE` and a warning.
- Surfaces are tokens: the window surface (created again whenever the game's window size changes) and one 1x1 pbuffer. Framebuffer 0 of a context bound to either is a stand-in FBO (`gles.cpp`, "Default-framebuffer emulation"): the Android window's size (or its buffer geometry) for the window, the pbuffer's size for a pbuffer. Each context has one stand-in per kind, so the main context's visits to the pbuffer (`RenderDeviceGL::SetCurrentContext`) don't discard its frame, and binding a surface moves a context's "framebuffer 0" binding to that surface's stand-in. `eglQuerySurface` answers the sizes the game expects, `eglSurfaceAttrib(EGL_SWAP_BEHAVIOR, EGL_BUFFER_DESTROYED)` is recorded, and `eglGetError` has a per-thread error like EGL's.
- Contexts are the host's, one SDL context per guest context (the guest makes 4: a temporary ES2 one for its version check, a root ES3 context that is never made current, and two ES3 contexts sharing with it: the render thread's and a worker's). `eglGetCurrentContext` is per thread.
- `eglSwapBuffers` on the window: the stand-in is blitted to the window, letterboxed (`GL_LINEAR`), the host's overlay (movies, screenshots) is drawn, and `SDL_GL_SwapWindow` presents. `eglSwapInterval` is `SDL_GL_SetSwapInterval`.

**How SDL is made to fit EGL** (`app/sdl_gl.h`):
- **Creation without side effects.** `SDL_GL_CreateContext` makes the new context current on the calling thread, on the window it is given, and `SDL_GL_SHARE_WITH_CURRENT_CONTEXT` shares with whatever is current there; EGL's `eglCreateContext` does neither, and the share context may be current on another thread (EGL forbids binding it twice). So contexts are created on a private hidden 1x1 window, under a mutex, and each share group has an anchor context that only the creation code ever makes current: a new context is created while its group's anchor is current, and the thread's previous binding is restored.
- **Pbuffers.** SDL2's Wayland backend can't bind a context without a surface (`SDL_GL_MakeCurrent(NULL, ctx)` releases it), and an EGL surface can be current on one thread only, so a context bound to a guest pbuffer is bound to a hidden 1x1 window of its thread's own: a pool of 8 made at start-up on the main thread, one per thread, given back when the thread exits. The window's own buffers are never drawn to (framebuffer 0 is the stand-in).
- **The window's config:** OpenGL ES 3.0, RGB8 with no alpha, depth or stencil (the game draws into FBOs; the window only receives the blit, and an alpha channel could make a compositor show it translucent). The log line `window framebuffer: RGBA 8880, 0 sample buffer(s)` confirms it.
- **GL entry points** stay libEGL's `eglGetProcAddress` (`gles.cpp`), resolved at `hle_init` before any window exists, which `SDL_GL_GetProcAddress` can't be, and without making the runtime link SDL. They are libglvnd's dispatch stubs, which call the vendor of the context current on the thread. SDL's contexts are EGL contexts from the same `libEGL.so.1`: under X11 `SDL_HINT_VIDEO_X11_FORCE_EGL` keeps SDL off GLX, which is also the Mesa EGL-on-X11 path the port used before SDL owned the contexts; Wayland only has EGL. The log line `SDL's context is libEGL's, glClear is SDL's` checks it once: libEGL's `eglGetCurrentContext` returns SDL's context (it would return none for a GLX context), and `SDL_GL_GetProcAddress` returns the same pointers (which alone proves little: glvnd hands out the same stubs through GLX).

**Headless** (`HostConfig::hidden`, `soa --headless`): the window is created hidden (`SDL_WINDOW_HIDDEN`, as are the private windows) and never shown, and the frame is still rendered, so screenshots work. Under X11 the hidden window's back buffer is presented into and read back, as before. Under Wayland a window that is never shown has no buffers SDL presents (it skips the swaps), so the frame is presented into an offscreen framebuffer of the window's size and screenshots read it back from there (`GfxHooks::offscreen_present`; the log says `presenting offscreen`). That isn't the default under X11 because Mesa d3d12 rounds the scaled `GL_LINEAR` blit into an FBO differently from the blit into the window on a few rows (by 1 in 8 bits: 616-1,269 of 945k pixels of the smoke screens), and the X11 path is pixel-identical to the baselines. `SOA_OFFSCREEN_PRESENT=1/0` forces it on or off for headless runs.

**Video driver:** SDL's choice: X11 when `DISPLAY` is set (SDL2 prefers it to Wayland), else Wayland; `SDL_VIDEODRIVER=wayland` or `=x11` chooses. The `main: window ... (x11|wayland[, hidden])` log line names it. vcpkg's SDL2 is built with both backends (`vcpkg.json`), which load their libraries at run time.

## Text entry: the game's keyboard and the on-screen box

The game asks for text (the new player's name: `CUIUtility::StringInput` → `BAS::GetKeyboardEditText`; also `CFriendMenu::ToClose`) through the Java `SOAActivity.StartKeyboardActivity(type, lines, max, initial)` (`jni/java_android.cpp`; the name field asks for type 0, 1 line, max 14), then **blocks its logic thread** in `Platform::Android::GetKeyboardEditText_Android`, polling `IsEndKeyboardActivity` every millisecond, and reads `GetEditText`. The host plays the KeyboardActivity: `platform().text_*` (`android/platform.h`) is the field, and `app/host.cpp` edits it.

- **The editor** (`frontend/text_entry.h`, tests `frontend/text-*`, also in `soaruntime_tests`): UTF-8 with a byte cursor on code point boundaries. Everything that adds text goes through `insert`, which drops control characters, keeps only ASCII digits in a numeric field (type 1) and keeps the code points that fit the maximum (Android's `LengthFilter` does the same; before, a typed chunk that didn't fit was dropped whole and a paste ignored both rules). Keys: Backspace, Delete, Left, Right, Home, End, Ctrl+V, Enter (`GetEditText` returns the text), Esc (an empty string).
- **IME:** SDL text input is on only while the keyboard is open (SDL starts it on; the host stops it at start-up so an IME never takes the game's keys), with `SDL_SetTextInputRect` on the box's field (window points; also after a resize). `SDL_HINT_IME_SUPPORT_EXTENDED_TEXT` makes a composition arrive whole (`SDL_TEXTEDITING_EXT`). The composition is shown underlined at the cursor and isn't part of the text until the IME commits it (`SDL_TEXTINPUT`); while there is one the editing keys are the IME's.
- **The box** (`app/text_overlay.h`): a semi-transparent panel across the bottom of the letterboxed game image: a hint row ("Enter: OK   Esc: Cancel", "Numbers only" for a numeric field, and the `n/max` counter, orange at the maximum), and the field (text, composition, a caret blinking at 530 ms and solid after each edit, scrolled to keep the caret visible). Sizes follow the game image's height (font `vh/30`), so it scales with the window, HiDPI and fullscreen. It is composed on the CPU into one premultiplied RGBA image (redrawn only when what it shows changes), uploaded to one texture and drawn as one blended quad (a `#version 300 es` program, positions from `gl_VertexID`) from `GfxHooks::draw_overlay`, in window space after the letterboxed blit and before a screenshot is read. It runs on the game's own context, so it saves and restores everything it changes (program, VAO (one per context), texture unit 0's binding and sampler, the active unit, blend state, depth / stencil / cull / coverage / scissor enables, viewport, draw framebuffer, the unpack buffer and alignment / row length / skips). While the keyboard is closed it returns before any GL call.
- **The font** (FreeType from vcpkg, zlib only; render thread only): `HostConfig::font` (`--font`), else IPAex Gothic, Noto Sans CJK, Droid Sans Fallback at their Debian/Ubuntu (and Arch/Fedora Noto) paths, else `fc-match :lang=ja`. A face without Latin (Droid Sans Fallback) or Japanese gets a fallback face from `fc-match`. One log line names it (`text box font: ...`). With no font, or `none`, one log line says the keyboard shows in the title bar only, and nothing is drawn. The window title always shows the text too.
- **Repainting while the game is stopped (idle presenting, `hle/gfx.h`).** While the keyboard is open the game presents no frames: the logic thread sleeps in `GetKeyboardEditText_Android` and the RenderThread (`Aska::RenderThread::Handler`, the thread whose context is on the window) waits for work in `pthread_cond_wait` (`Aska::Event::Wait`); `SOA_WATCHDOG=5` used to fire 5 s after the keyboard opened. Only the window's thread can present (an EGL surface is current on one thread; the JNI calls come on the logic thread, and the host's main thread has no context on the window). So `th_cond_wait` (`hle/libc_thread.cpp`) on the window's thread waits in slices, 100 ms normally (the RenderThread is already waiting when the keyboard opens) and 33 ms while idle presenting is on, and after a slice in which nothing was presented, presents the last frame again (`present_again`: the stand-in blit + `draw_overlay` + swap). A slice's timeout is never returned to the guest, and the guest's mutex stays held during the repaint, so no signal is lost. The host turns it on while text entry is active. With the keyboard closed the slices cost a timed wait instead of a plain one (the RenderThread is woken every frame long before 100 ms). A `shot:` taken while the keyboard is open now shows the dialog and the box.
- **Test commands** (control FIFO / `--do`; they go through the same SDL event path): `type:TEXT` (one `SDL_TEXTINPUT` per code point), `compose:TEXT` (a composition with its caret at the end; empty clears it), `key:enter|escape|backspace|delete|left|right|home|end`. `text:STRING` is unchanged: it finishes the entry with STRING at once, bypassing the editor. A `shot:` is served at the next present, so put a `wait:` between a `shot:` and the next edit.
- **A game quirk:** the name dialog says 12 characters (「12文字まで入力できます」) but opens the keyboard with max 14; 決定 with 13 or 14 characters shows the game's own error (「文字が入力されていないか、文字数上限を超えている…」), and CreatePlayer is not sent. The box's counter shows the keyboard's maximum, 14, as Android's would.

## Environment: the runtime's diagnostics

The runtime reads no setting from the environment: the programs take flags (`--font`, `--headless`,
...). These diagnostic switches are the same in soa, soa-emu and soa-viewer, read through
`common/include/soa/env.h`'s rule: a switch is off when unset, empty, `0`, `false`, `no` or `off`
(any case) and on otherwise; numbers are range-checked (a bad value is warned about and the default
used). The programs' own lists: `port/README.md` "Environment" (soa), `emulator/README.md`,
`emulator-viewer/README.md`; the removed settings: `docs/environment.md`.

| Variable | Effect (source) |
|---|---|
| `SOA_TRACE="sym[=float][:off[,off..]];..."` | log calls, arguments and results of guest functions (mangled names or `0x<ELF vaddr>`), optionally overriding a float result (`core/trace.cpp`); not installed under soa `--selftest` |
| `SOA_COVERAGE=DIR` | every guest function executed, `DIR/coverage.tsv` (`core/profile.cpp`; port/README.md "Profiling") |
| `SOA_PROFILE=DIR` | sampled guest stacks, `DIR/stacks.folded`; wins over `SOA_COVERAGE`'s dir when both are set and differ |
| `SOA_PROFILE_HZ=N` | the sample rate, 10..10000 (default 1000) |
| `SOA_PROFILE_HOST=1` | with `SOA_PROFILE`: host PCs inside natives, `DIR/host.tsv` |
| `SOA_WATCHDOG=S` | 1..86400 seconds without a presented frame: log every guest stack (`app/host.cpp`; default off) |
| `SOA_AUDIO_DUMP=DIR` | each OpenSL ES player's PCM as `DIR/playerN.wav`, before mixing (`hle/opensles.cpp`) |
| `SOA_TRACE_RT=1` | log render-target allocations and viewports (`hle/gles.cpp`) |
| `SOA_OFFSCREEN_PRESENT=1\|0` | headless only: present offscreen (on) or into the hidden window (off); unset = offscreen unless the video driver is x11 (see "Graphics") |
| `SOA_GL_HOST_SRGB_ETC2=1` | pass sRGB ETC2 textures to the driver instead of decoding them (default off) |
| `SOA_GL_MAP_INVALIDATE=0` | don't add `GL_MAP_INVALIDATE_RANGE_BIT` to the engine's overwrite maps (default on) |
| `SOA_GL_RELEASE_SHADER_COMPILER=1` | pass `glReleaseShaderCompiler` to the driver (default dropped) |
| `SOA_DIRECT_CALLS=0` | send host-thunk calls through the JIT (default on: called directly; `core/cpu.cpp`) |
| `SOA_FAULT_LOG=1` | Windows: log every first-chance fault (module offsets of the host stack, the guest pc; `core/cpu.cpp`): a crash inside a system DLL can end the process without the crash report |

Host variables: `HOME` (the programs' default data dirs); `TZ`, `HOME` and `TMPDIR` are the only
host variables the guest's `getenv` sees (`hle/libc.cpp`); child processes (`ffmpeg` for movies,
`fc-match` for the font) inherit the environment. SDL reads its own (`SDL_VIDEODRIVER`,
`SDL_AUDIODRIVER`, any `SDL_*` hint). The runtime sets `SDL_HINT_VIDEO_X11_FORCE_EGL` (`app/sdl_gl.cpp`)
and `SDL_HINT_IME_SUPPORT_EXTENDED_TEXT` (`app/host.cpp`) at normal priority, so the environment's
`SDL_VIDEO_X11_FORCE_EGL` / `SDL_IME_SUPPORT_EXTENDED_TEXT` override them: left so on purpose (SDL's
documented behaviour), but `SDL_VIDEO_X11_FORCE_EGL=0` would give X11 GLX contexts, which the EGL
emulation doesn't expect.

## Platform fidelity: what the guest may rely on

Two properties of an ARM64 Android phone that game code depends on, found by the 3.7.0 emulator (`emulator/README.md` "The lost first request" and "Error replies and the tagged-address crash"). Both are in the runtime, so `soa` gets them too.

**JNI handles have a non-zero low byte** (`jni/jvm.h` `TaggedAlloc`). ART's references are indirect references whose low bits carry the reference kind, so their low byte is never zero. 3.7.0 `LocalKVS::SetBinaryAndroid` (ELF 0x1f28474) tests the low byte of the `java.lang.Boolean` *reference* `SetSharedPreferences` returns. Our references are the host addresses of the `Object`s, and with plain `new` 1 in 16 of them ended in `00`. Now `Object` (so every string, array, class, instance and box), `Method` (jmethodID) and `Field` (jfieldID) are allocated at 8 (mod 16) past a 16-aligned block.
- **Rule:** every object the guest can hold a handle to must be created with `new` (the `Vm` helpers do), never as a static, a member, on the stack or through `std::make_shared` / an allocator.
- **Check:** `call_thunk` logs `W/jni: ... returned a reference with a zero low byte` once per method if an object-returning method breaks the rule.
- **Not references:** the `JNIEnv*` / `JavaVM*` handles are the addresses of `Vm`'s table pointers. ART's are plain heap pointers too, which the game only dereferences.
- **Behaviour:** a guest that converts a reference to a boolean now always sees "true" for a non-null reference, as on a phone; before, 1 in 16 references read as false.
- **Cost:** 16 bytes more per object; the objects are never freed in practice.

**Top Byte Ignore** (`core/cpu.cpp` `CpuCallbacks::tbi`). Linux enables TBI0 for user space: the CPU ignores bits 56-63 of a data address. 3.7.0 `Socket::Poll` reads `[fdset + 0x1ffffffffffffff8]` when another thread has set the socket's fd to -1. On a phone that reads `fdset - 8`; here it was a non-canonical x86-64 address and crashed.
- **How:** the memory callbacks (reads, writes, exclusive reads and writes, the 128-bit CAS, DC ZVA) clear the top byte. Instruction fetches are unchanged, since TBI covers data only.
- **The fastmem path doesn't change.** dynarmic's fastmem uses the guest address as it is, so a tagged address faults. Its signal handler (`backend/exception_handler_posix.cpp`) looks the fault up by host RIP, not by fault address, and redirects to the callback. `recompile_on_fastmem_failure` then keeps that one instruction on the callbacks.
- **Cost:** none measurable. The mask is one AND on the callback path only. The host profile of a smoke run has no samples in the memory callbacks before or after; smoke wall time was 66.1 s before and 64.4 / 66.2 s after (67.8 s on a loaded machine).
- **Not masked: host code that dereferences guest pointers**, e.g. the HLE thunks (`memcpy`, `strlen`, ...) and the JNI functions. A tagged pointer passed to an import would still fault in host code. Masking every pointer argument would also change opaque values the guest gets back (`pthread_create`'s argument, callback cookies). The game's allocator is the host's `malloc`, so the guest only makes tagged pointers by arithmetic, as in `Poll`, and those are dereferenced by guest code. If such a case shows up, mask that thunk's argument.

Tests: `cpu/tbi-tagged-data-addresses` (hand-encoded loads, stores, a byte read-modify-write, 128-bit load/store and an LDAXR/STLXR loop through tags 0xb4, 0xff, 0x01 and 0x20, on the fastmem-fault path and the recompiled one) and `jni/references-low-byte` (256 of each handle kind through the JNIEnv table: strings, classes, method and field IDs, `NewObject`, `AllocObject`, arrays, global, local and weak refs, `Call*ObjectMethod` returns of `Boolean` / `Integer` / `this`, and `SetSharedPreferences` read the guest's way). Without the fixes the first crashes exactly as soa-emu did (SIGSEGV in `CpuCallbacks::MemoryRead64`, fault address 0) and the second finds 383 of 6,656 handles with a zero low byte.
