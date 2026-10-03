# Handoff: on-screen text box for the game's keyboard (text entry)

Status 2026-10-03: stopped early (user request). Investigation done and the repaint mechanism found.
No code is committed: the work-in-progress (idle presenting in the HLE and an editor module) was discarded. It is reproduced in full in the appendix, so it can be re-applied. It built; it was never verified at run time.
No overlay drawing, font or IME code was written.

## Goal (the approved spec)
Replace the window-title-only feedback of the emulated KeyboardActivity with a text box drawn over the game. The title is invisible in fullscreen.
- **The box:** a semi-transparent panel near the bottom, like a phone keyboard bar. It shows:
  - the current text with a blinking cursor;
  - the hint "Enter = OK, Esc = cancel";
  - a counter of length against the maximum ("5/14");
  - "numbers only" for numeric fields (type 1);
  - the **IME composition preview** (SDL_TEXTEDITING text, underlined, at the cursor).
- **IME window:** `SDL_SetTextInputRect` is set to the box, so the IME candidate window appears next to it.
- **Drawing:** after the game's frame, in window space, after the letterboxed blit. It scales with the window (HiDPI, fullscreen).
- **Repainting:** while the game presents no frames (it doesn't while the keyboard is open), the last frame keeps being presented with the overlay, so the box updates as you type.
- **Text rendering with Japanese support:**
  - The library is FreeType (vcpkg), or stb_truetype pinned through FetchContent.
  - The font is a system CJK font found at run time: a configurable path (env `SOA_FONT`, or an option), then known paths or fontconfig.
  - Clean fallback when no font is found: a log line, and the title-only behaviour.
  - Document the requirement in README Setup (`fonts-ipaexfont` or `fonts-noto-cjk`).
- **Keep:**
  - the window-title hint;
  - the `text:` control command, unchanged;
  - headless runs (a `shot:` while the keyboard is open should show the box);
  - soa, soa-emu and soa-viewer all get it (they all use `app::run`: verified, `port/src/main.cpp:530`, `emulator/src/main.cpp:255`, `emulator-viewer/src/main.cpp:276`).
- **Cheap editing extras:**
  - Left, Right, Home, End and Delete.
  - **Paste (Ctrl+V) must respect max length and the numeric filter**: today it bypasses both (a bug, `host.cpp` `handle_text_event`).
- **Test commands** (test-only, documented):
  - `type:TEXT`: like SDL_TEXTINPUT, through the same editor;
  - `compose:TEXT`: an IME preview;
  - `key:enter|escape|backspace|delete|left|right|home|end`: `text:` bypasses the editor, so a scripted Enter needs this.
- **Gates:**
  - Build everything; `build/runtime/soaruntime_tests`; `soa --selftest`.
  - A screenshot proof in the name dialog: empty box, typed text with cursor, Japanese text, a composition preview, the max-length counter, then Enter, after which CreatePlayer carries the name.
  - Then, one at a time: port `newplayer_session.sh` and `tutorial_session.sh` (they use `text:`), `emulator_session.sh --new-player`, `viewer_boot.sh`, `smoke.sh` (pixels unchanged when no keyboard is open).
  - Docs: `runtime/README.md` ("Graphics", the host), `port/README.md` (controls), `README.md` Setup (font).

## How the game behaves while its keyboard is open (verified)
- **Call chain** (3.7.0, Ghidra: `tools/decomp.sh --v370 ... 'GetKeyboardEditText|CDialogEditText::Execute'`):
  - The name field: `CUIUtility::StringInput`, then `Platform::Android::GetKeyboardEditText_Android(type, lines, max, initial)` (ELF 0x1e38c38 in 3.7.0).
  - It calls the Java `StartKeyboardActivity(IIILjava/lang/String;)V`, then **blocks the game's logic thread** in `do { Aska::Thread::SleepU(1000); CallMethod("IsEndKeyboardActivity") } while (!result)`, then calls `GetEditText`.
  - The caller is `CCocosDirector::InputProgress`, through touch dispatch, so the whole update loop stops.
  - `CDialogEditText::Execute(const char*, bool numeric, unsigned)` is a second caller: `CKeyboardActivity::Start(0, numeric ? 0x10 : 1)`. It spins on `IsEnd()` the same way. Its type argument looks like a max length, not a type. That is unverified; check which screens use it before assuming a numeric field exists.
- **The name dialog:** `StartKeyboardActivity(type=0, lines=1, max=14, "")`.
- **No frames are presented while it waits.** Measured with `SOA_WATCHDOG=5 SOA_PROFILE=1`: the watchdog fires 5 s after the keyboard opens, with stacks:
  - the logic thread is in `[hle]nanosleep` < `Aska::Thread::SleepU` < `GetKeyboardEditText_Android`;
  - **`Aska::RenderThread::Handler()` waits in `[hle]pthread_cond_wait` < `Aska::Event::Wait(unsigned)`**.
  - The RenderThread is the thread whose context is current on the window surface (`hle/egl.cpp` header: the render thread's context is on the window).
- **Repainting can't happen on the thread that calls the JNI.** The first experiment called `present_again()` from `IsEndKeyboardActivity`. It always returned false: that call runs on the logic thread, which has no window surface current.
- **The host's main thread can't present either.** The EGL window surface is current on the RenderThread, and an EGL surface can be current on one thread only.
- **What does work:** repaint on the RenderThread, while it waits in `pthread_cond_wait`.
- **Consequence for scripts today:** `control/flowctl.py` `name_entry` notes "While the keyboard is open the game renders no frames, so no screenshot before the text". A `shot:` request is only served at the next present. Idle presenting fixes that too.

## Design (chosen; part done)
1. **Idle presenting** (runtime HLE; written and compiled, **never verified**; the code is in the appendix):
   - **`hle/gfx.h` + `hle/egl.cpp`:**
     - `present_again()`: re-blits the window stand-in FBO, letterboxed, and calls `GfxHooks::draw_overlay` and swap (`gles::present_and_swap`). It runs only when this thread's current draw surface is the live Window surface.
     - `set_idle_present(bool)` / `idle_present_on()` / `window_thread()` / `idle_present()`. `idle_present()` presents again only if no present happened for `kIdlePresentMs` = 33 ms. `g_last_present_ns` is updated by `th_eglSwapBuffers` and by `present_again`.
   - **`hle/libc_thread.cpp` `th_cond_wait`:**
     - Not the window thread: the plain wait, as before.
     - The window thread: waits in `pthread_cond_timedwait` slices of `kIdleCheckMs` = 100 ms, or 33 ms while idle presenting is on. On a timeout it calls `idle_present()` and keeps waiting: a slice timeout is never returned to the guest.
     - **Why slices even when off:** the first version only sliced while the flag was on. It didn't work, because the RenderThread had already entered an untimed wait before the keyboard opened (the run2 watchdog showed it still in `pthread_cond_wait`). Slicing on the window thread lets it notice the flag within 100 ms.
     - Cost: up to 10 wakeups/s of an idle render thread. Pixels are unchanged; `smoke.sh` must confirm.
   - **`app/host.cpp` main loop:** `set_idle_present(platform().text_active)` each iteration.
   - **Verify first:** rerun the scratch flow (below) with `SOA_WATCHDOG=5`. The watchdog must stay silent, the perf line must show fps while the keyboard is open, and `kb-open.png` (a `shot:` taken while the keyboard is open) must be written.
   - `gles::present_and_swap` calls `before_swap` / `after_swap` (frame counter, perf). Present-time state is saved and restored by `present_scaled`.
   - `pthread_cond_timedwait` with an absolute CLOCK_REALTIME time is fine: `th_cond_init` creates the host cond with default attributes (REALTIME).
2. **Editor** (`runtime/src/frontend/text_entry.{h,cpp}`; written, **not wired, no tests**; the code is in the appendix):
   - Pure UTF-8 operations with a byte cursor on code point boundaries: `insert` (drops control characters, keeps digits only when numeric, truncates to the code points that fit `max_len`, like Android's LengthFilter), `backspace`, `del`, `left`, `right`, `home`, `end`, `clamp_cursor`, and `byte_offset` (SDL_TEXTEDITING's start is in code points).
   - **Next:**
     - Add the `RUNTIME_TEST("frontend/text-...")` tests.
     - Add `run_runtime_tests("frontend/text-")` to `runtime/tests/extension_points_test.cpp` (it matches by prefix with strncmp).
     - Note a behaviour change: today a SDL_TEXTINPUT that doesn't fit is dropped whole; with `insert`, the prefix that fits is kept.
3. **Platform state** (`android/platform.h`; to do): add `size_t text_cursor`, `std::string text_composition`, `int text_comp_cursor` (byte offset in the composition), all under `text_mutex`.
   - `StartKeyboardActivity` (`jni/java_android.cpp`) sets `text_cursor = text_editing.size()` and clears the composition, where it sets `text_editing`.
   - Keep `text_editing` / `text_value` / `text_active` with their current meaning (`update_title` and `text:` use them).
4. **Host event handling** (`app/host.cpp`; to do):
   - **Rework `handle_text_event`** to call the editor:
     - `SDL_TEXTINPUT` calls `insert`.
     - `SDL_TEXTEDITING` (and `SDL_TEXTEDITING_EXT`: free its text) sets the composition and its cursor (`ev.edit.start` code points).
     - Ctrl+V calls `insert`, which fixes the paste bug.
     - **The editing keys are ignored while a composition is non-empty: the IME owns them.**
   - **Text input on and off, in the main loop, on the `text_active` edges** (not in the event handler: today `SDL_StartTextInput` runs only on the first event, so an IME never starts composing before a key):
     - rising edge: `SDL_StartTextInput()` + `SDL_SetTextInputRect` (the box's field rect, in window **points**: divide drawable pixels by drawable/window size; `map_mouse` does the inverse);
     - again on window resize;
     - falling edge: `SDL_StopTextInput()`, including after `text:`, which doesn't stop it today.
   - **Control commands** in `run_command` build an `SDL_Event` and call `handle_text_event`, so they go through the real path:
     - `type:TEXT`: one SDL_TEXTINPUT per code point (the SDL text field is 32 bytes);
     - `compose:TEXT`: SDL_TEXTEDITING with the cursor at the end; empty clears;
     - `key:NAME`.
     - Document them with the other commands, in the comment above `run_command` and in `port/README.md`.
5. **Overlay drawing** (to do): new `runtime/src/app/text_overlay.{h,cpp}`, linked into `soaruntime_app`; FreeType goes there only.
   - **Order:** call it from `Gfx::draw_overlay` in `host.cpp`, after `movie_draw` and **before** the `shot_requested` check, so screenshots include it. Zero GL calls when the keyboard is closed.
   - **Composition on the CPU:**
     - The whole panel is one RGBA image (premultiplied alpha), redrawn only when the state changes (text, cursor, composition, blink phase, size).
     - Upload it to one texture and draw one quad with a tiny ES 3.0 program: the vertex position comes from `gl_VertexID` + a `u_rect` uniform, so there are no attributes; blending is `GL_ONE, GL_ONE_MINUS_SRC_ALPHA`.
     - A blit (the movie's trick, `frontend/movie.cpp`) can't blend, which is why it's a program.
   - **GL state:** it runs on the **game's own context**. Save and restore the program, the VAO (one VAO per context: VAOs aren't shared; key it by `SDL_GL_GetCurrentContext()`), the active texture + TEXTURE_2D binding on unit 0, the sampler binding on unit 0 (the game may use sampler objects), blend enable/func/equation, depth / stencil / cull / alpha-to-coverage enables, the viewport, the draw FBO, `PIXEL_UNPACK_BUFFER`, and the UNPACK alignment / row length / skip.
     - `present_scaled` already restores the scissor, rasterizer discard, colour mask, clear colour and the FBO bindings.
   - **Layout** (one pure function shared by the main thread, for the IME rect, and the render thread):
     - The panel spans the game viewport's width (`set_viewport_rect` gives `vx`, `vy`, `vw`, `vh` in drawable pixels, GL bottom-up) and sits at its bottom.
     - The main font is about `vh/30` px (43 px at 1296).
     - Row 1, small (about 0.55×): "Enter: OK   Esc: Cancel" (+ "Numbers only"), with the "n/max" counter right-aligned.
     - Row 2: the field: text, the composition underlined at the cursor, a 2 px caret blinking at about 530 ms (solid for a moment after each edit), and horizontal scrolling that keeps the caret visible.
   - **Threading:** `draw_overlay` runs on the render thread and the editor state changes on the main thread. Copy the state under `text_mutex` into locals.
6. **Font** (to do):
   - **FreeType:** add `{"name": "freetype", "default-features": false, "features": ["zlib"]}` to `vcpkg.json`; the default features pull brotli, bzip2 and libpng. **Never edit `cmake/vcpkg-triplets/`.**
     - After the first configure, read `build/vcpkg_installed/x64-linux/share/freetype/` for the target name (`Freetype::Freetype`) and add a `find_package` to `cmake/deps.cmake`.
   - **The search:**
     - `SOA_FONT` first (optionally a `HostConfig::font` field);
     - then known paths: `/usr/share/fonts/opentype/ipaexfont-gothic/ipaexg.ttf` (on this machine), `/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf`, Noto CJK `/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc` (face 0);
     - then `fc-match -f '%{file}' ':lang=ja'`;
     - log one line with what was picked.
   - **No font:** log "no font, the keyboard shows in the title bar only" and skip the overlay.
   - Glyphs: `FT_Set_Pixel_Sizes` + `FT_Load_Char(FT_LOAD_RENDER)`, a glyph cache per size, `.notdef` for missing glyphs.

## Test approach
- **The scratch driver** (was `/home/fish/.claude/jobs/ac4802d9/tmp/text-overlay-scratch/name.sh`): `port/scripts/newplayer_session.sh` part 2, trimmed, from the worktree root:
  1. `. port/scripts/phone370.sh`; `phone370_prepare "$TMP/newplayer/data"`; `rm -f "$TMP/newplayer/data/data/shared_prefs/Game.xml"`.
  2. Start soa: `SOA_HEADLESS=1 SDL_AUDIODRIVER=dummy SOA_RESTORE_NEW_PLAYER=1 SOA_SERVER_SEED_RNG=1 timeout -k 10 1200 build/port/soa --data "$TMP/newplayer/data" --size 729x1296 --control "$TMP/newplayer/fifo" > "$OUT/newplayer.log" 2>&1 &` and save `pid=$!`.
  3. Wait for the log line `port_debug: phase 1 `, then `control/soactl.py FIFO wait:8000`.
  4. Tap `tap:364:970` until `error 19001` is logged (about 10 s apart, up to 6 times).
  5. `wait:3000 tap:364:689 wait:3000` (the terms' 同意する).
  6. Tap the name field `tap:364:647` (after `wait:1500`) until `StartKeyboardActivity(` is logged. Every third try, tap 同意する again.
  7. With the keyboard open, `shot:`, `type:` and so on. 決定 is at `tap:364:790`; CreatePlayer is logged as `request CreatePlayer (fid ...): "NAME"`.
  8. `quit`, then `wait $pid`.
- **A faster variant:** `control/flowctl.py name-entry FIFO LOG NAME SHOT` does steps 6-7 with `text:`.
- **Proof screenshots** go to the report folder: empty box; `type:Claire` with the caret; `type:` with Japanese (e.g. クレア); `compose:くれあ`; 14+ characters for the counter at its maximum; then `key:enter` (not `text:`) and check CreatePlayer.
- Whether a numeric field exists is still open: check the callers of `CDialogEditText::Execute` / `CKeyboardActivity::Start` (`tools/callers.py`).
- **Pitfalls:**
  - `SOA_PROFILE=1` writes its output into a directory named `1/` in the cwd. Remove it, never commit it.
  - Kill only your own PIDs (from `$!`).
  - At most 3 game processes.

## Remaining steps (estimates)
1. Verify idle presenting (watchdog silent, `shot:` while the keyboard is open), then `smoke.sh` for unchanged pixels: 0.5 h.
2. Platform fields, the editor wired into `handle_text_event`, the edge handling, the control commands, the editor tests: 1-1.5 h.
3. FreeType dependency, font discovery, the overlay (layout, CPU composition, GL quad, state save and restore), the IME rect: 2-3 h.
4. Proof screenshots, then the gates (newplayer, tutorial, emulator `--new-player`, viewer boot, smoke, selftest), then docs (runtime README "Graphics" + host, port README controls, README Setup fonts): 1.5-2 h.

## Appendix: the discarded work-in-progress code
### A. Idle presenting
The diff against `d63a2bb`; apply it with `git apply`.
It touches `runtime/src/app/host.cpp`, `hle/egl.cpp`, `hle/gfx.h` and `hle/libc_thread.cpp`.

```diff
diff --git a/runtime/src/app/host.cpp b/runtime/src/app/host.cpp
index daa1f97..c1122bb 100644
--- a/runtime/src/app/host.cpp
+++ b/runtime/src/app/host.cpp
@@ -746,6 +746,7 @@ void app::run(LoadedLib& lib, HostConfig& cfg) {
                 break;
             }
         }
+        set_idle_present(platform().text_active);
         platform_run_ui_tasks();
         g_pinch.update();
         if (cfg.tick) cfg.tick();  // HostConfig::tick (the port: --selftest)
diff --git a/runtime/src/hle/egl.cpp b/runtime/src/hle/egl.cpp
index abb7861..6d1dd3e 100644
--- a/runtime/src/hle/egl.cpp
+++ b/runtime/src/hle/egl.cpp
@@ -20,6 +20,7 @@
 #include <EGL/eglext.h>
 
 #include <atomic>
+#include <chrono>
 #include <cstring>
 #include <mutex>
 #include <set>
@@ -38,6 +39,15 @@ namespace {
 
 GfxHooks* g_hooks = nullptr;
 
+// Idle presenting (gfx.h).
+std::atomic<bool> g_idle_present{false};
+std::atomic<s64> g_last_present_ns{0};  // the last window present (the guest's or an idle one)
+s64 steady_ns() { return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }
+bool window_current() {
+    egl_emu::Surface* s = egl_emu::current_draw();
+    return s && s->kind == egl_emu::Surface::Window && !s->destroyed;
+}
+
 // ---- objects
 
 // The display: any address the guest can compare; EGL_NO_DISPLAY is 0.
@@ -414,6 +424,7 @@ void th_eglSwapBuffers(Cpu& c) {
     if (s != t_draw) return ret(c, fail(EGL_BAD_SURFACE, EGL_FALSE));
     t_error = EGL_SUCCESS;
     if (s->kind != egl_emu::Surface::Window) return ret(c, EGL_TRUE);  // a pbuffer: no-op
+    g_last_present_ns.store(steady_ns(), std::memory_order_relaxed);
     if (!gles::present_and_swap()) {
         static std::atomic<int> logged{0};
         if (logged.fetch_add(1) < 4) LOGW("egl", "swap failed: %s", g_hooks->last_error());
@@ -459,6 +470,24 @@ GfxHooks* hooks() { return g_hooks; }
 
 void set_gfx_hooks(GfxHooks* h) { g_hooks = h; }
 
+
+bool present_again() {
+    if (!window_current()) return false;
+    g_last_present_ns.store(steady_ns(), std::memory_order_relaxed);
+    return gles::present_and_swap();
+}
+
+void set_idle_present(bool on) { g_idle_present.store(on, std::memory_order_relaxed); }
+
+bool idle_present_on() { return g_idle_present.load(std::memory_order_relaxed); }
+
+bool window_thread() { return window_current(); }
+
+void idle_present() {
+    if (steady_ns() - g_last_present_ns.load(std::memory_order_relaxed) < (s64)kIdlePresentMs * 1000000) return;
+    present_again();
+}
+
 void register_egl(Hle& h) {
     h.fn("eglGetDisplay", th_eglGetDisplay);
     h.fn("eglInitialize", th_eglInitialize);
diff --git a/runtime/src/hle/gfx.h b/runtime/src/hle/gfx.h
index cf3b046..9acd545 100644
--- a/runtime/src/hle/gfx.h
+++ b/runtime/src/hle/gfx.h
@@ -42,4 +42,24 @@ struct GfxHooks {
 
 void set_gfx_hooks(GfxHooks* h);
 
+// Presents the last frame again (the window stand-in, letterboxed, plus GfxHooks::draw_overlay), when
+// the calling thread's context is on the window surface; false (nothing done) otherwise.
+bool present_again();
+
+// Idle presenting: repaints while the game shows no new frames. A frontend overlay that changes over
+// the game's last frame turns it on (the text-entry box: while the game waits for the keyboard its
+// logic thread blocks, and its render thread waits for work). The thread whose context is on the
+// window waits in pthread_cond_wait (hle/libc_thread.cpp) in slices of kIdleCheckMs (it may have
+// started waiting before idle presenting was turned on), and while idle presenting is on, of
+// kIdlePresentMs, presenting the last frame again (present_again) after a slice in which no frame
+// was presented.
+constexpr int kIdlePresentMs = 33;
+constexpr int kIdleCheckMs = 100;
+void set_idle_present(bool on);
+bool idle_present_on();
+// For the HLE's blocking waits: this thread's context is on the window surface.
+bool window_thread();
+// Presents the last frame again when none was presented for kIdlePresentMs (on the window thread).
+void idle_present();
+
 }  // namespace soa
diff --git a/runtime/src/hle/libc_thread.cpp b/runtime/src/hle/libc_thread.cpp
index 131a5dd..453308b 100644
--- a/runtime/src/hle/libc_thread.cpp
+++ b/runtime/src/hle/libc_thread.cpp
@@ -18,6 +18,7 @@
 
 #include "core/hle.h"
 #include "core/log.h"
+#include "hle/gfx.h"
 #include "hle/thread.h"
 
 namespace soa {
@@ -242,7 +243,23 @@ void th_cond_init(Cpu& c) { ret(c, (u64)pthread_cond_init((pthread_cond_t*)c.x(0
 void th_cond_destroy(Cpu& c) { ret(c, (u64)pthread_cond_destroy((pthread_cond_t*)c.x(0))); }
 void th_cond_signal(Cpu& c) { ret(c, (u64)pthread_cond_signal((pthread_cond_t*)c.x(0))); }
 void th_cond_broadcast(Cpu& c) { ret(c, (u64)pthread_cond_broadcast((pthread_cond_t*)c.x(0))); }
-void th_cond_wait(Cpu& c) { ret(c, (u64)pthread_cond_wait((pthread_cond_t*)c.x(0), fix_mutex(c.x(1)))); }
+void th_cond_wait(Cpu& c) {
+    auto* cv = (pthread_cond_t*)c.x(0);
+    pthread_mutex_t* m = fix_mutex(c.x(1));
+    if (!window_thread()) return ret(c, (u64)pthread_cond_wait(cv, m));
+    // Idle presenting (hle/gfx.h): the window's thread (the game's RenderThread, waiting for its next
+    // frame's work) waits in slices, so that it notices idle presenting turned on while it already
+    // waits, and then repaints the last frame between slices. A slice's timeout is not a wakeup.
+    for (;;) {
+        timespec t;
+        clock_gettime(CLOCK_REALTIME, &t);
+        t.tv_nsec += (idle_present_on() ? kIdlePresentMs : kIdleCheckMs) * 1000000L;
+        if (t.tv_nsec >= 1000000000L) t.tv_sec++, t.tv_nsec -= 1000000000L;
+        int r = pthread_cond_timedwait(cv, m, &t);
+        if (r != ETIMEDOUT) return ret(c, (u64)r);
+        if (idle_present_on()) idle_present();
+    }
+}
 void th_cond_timedwait(Cpu& c) {
     ret(c, (u64)pthread_cond_timedwait((pthread_cond_t*)c.x(0), fix_mutex(c.x(1)), (const timespec*)c.x(2)));
 }
```

### B. `runtime/src/frontend/text_entry.h`
```cpp
#pragma once
// The text-entry editor behind the emulated KeyboardActivity (jni/java_android.cpp
// StartKeyboardActivity; the host's keyboard handling in app/host.cpp and its on-screen box,
// app/text_overlay.h). Pure string operations on UTF-8 text with a byte-offset cursor that always
// sits on a code point boundary, so they can be tested without a window.
//
// The field's rules are the ones the game asks for: at most `max_len` code points (<= 0: no limit;
// the name field asks for 14) and, for a numeric field (type 1), ASCII digits only. Everything that
// adds text goes through insert(), so typing, an IME's committed text and a paste obey them alike:
// a too-long insertion keeps the code points that fit (an Android EditText's InputFilter
// .LengthFilter does the same).
#include <cstddef>
#include <string>
#include <string_view>

namespace soa::text_entry {

// Code points in `s` (UTF-8; continuation bytes aren't counted).
size_t utf8_len(std::string_view s);
// The code point boundary before / after byte offset `pos` (pos itself at the ends).
size_t prev_boundary(std::string_view s, size_t pos);
size_t next_boundary(std::string_view s, size_t pos);

struct Field {
    int max_len = 0;       // code points; <= 0: no limit
    bool numeric = false;  // ASCII digits only
};

// Inserts `add` at `cursor` and moves the cursor past it. Control characters (below U+0020, and
// DEL) are dropped, and for a numeric field everything but '0'-'9'; then as many leading code
// points as fit under max_len. Returns the number of code points inserted.
size_t insert(std::string& text, size_t& cursor, std::string_view add, const Field& f);

// Editing keys; each keeps the cursor on a boundary and returns whether anything changed.
bool backspace(std::string& text, size_t& cursor);  // deletes the code point before the cursor
bool del(std::string& text, size_t& cursor);        // deletes the code point after it
bool left(const std::string& text, size_t& cursor);
bool right(const std::string& text, size_t& cursor);
bool home(size_t& cursor);
bool end(const std::string& text, size_t& cursor);

// A cursor clamped into the text and moved back onto a code point boundary.
size_t clamp_cursor(std::string_view text, size_t cursor);

// The byte offset of code point `n` in `s` (s.size() past the end): SDL_TEXTEDITING's start is in
// code points.
size_t byte_offset(std::string_view s, size_t n);

}  // namespace soa::text_entry
```

### C. `runtime/src/frontend/text_entry.cpp`
```cpp
#include "frontend/text_entry.h"

#include <algorithm>
#include <cstdint>

namespace soa::text_entry {

namespace {
bool is_cont(unsigned char c) { return (c & 0xc0) == 0x80; }
}  // namespace

size_t utf8_len(std::string_view s) {
    size_t n = 0;
    for (unsigned char c : s)
        if (!is_cont(c)) n++;
    return n;
}

size_t prev_boundary(std::string_view s, size_t pos) {
    pos = std::min(pos, s.size());
    if (pos == 0) return 0;
    do pos--;
    while (pos > 0 && is_cont((unsigned char)s[pos]));
    return pos;
}

size_t next_boundary(std::string_view s, size_t pos) {
    if (pos >= s.size()) return s.size();
    do pos++;
    while (pos < s.size() && is_cont((unsigned char)s[pos]));
    return pos;
}

size_t clamp_cursor(std::string_view text, size_t cursor) {
    cursor = std::min(cursor, text.size());
    while (cursor > 0 && cursor < text.size() && is_cont((unsigned char)text[cursor])) cursor--;
    return cursor;
}

size_t byte_offset(std::string_view s, size_t n) {
    size_t pos = 0;
    while (n-- > 0 && pos < s.size()) pos = next_boundary(s, pos);
    return pos;
}

size_t insert(std::string& text, size_t& cursor, std::string_view add, const Field& f) {
    cursor = clamp_cursor(text, cursor);
    size_t have = utf8_len(text), room = f.max_len > 0 ? (have < (size_t)f.max_len ? f.max_len - have : 0) : SIZE_MAX;
    std::string keep;
    size_t n = 0;
    for (size_t i = 0; i < add.size() && n < room;) {
        size_t j = next_boundary(add, i);
        std::string_view cp = add.substr(i, j - i);
        i = j;
        unsigned char c0 = (unsigned char)cp[0];
        if (c0 < 0x20 || c0 == 0x7f || is_cont(c0)) continue;
        if (f.numeric && !(cp.size() == 1 && c0 >= '0' && c0 <= '9')) continue;
        keep += cp;
        n++;
    }
    text.insert(cursor, keep);
    cursor += keep.size();
    return n;
}

bool backspace(std::string& text, size_t& cursor) {
    cursor = clamp_cursor(text, cursor);
    if (cursor == 0) return false;
    size_t p = prev_boundary(text, cursor);
    text.erase(p, cursor - p);
    cursor = p;
    return true;
}

bool del(std::string& text, size_t& cursor) {
    cursor = clamp_cursor(text, cursor);
    if (cursor >= text.size()) return false;
    text.erase(cursor, next_boundary(text, cursor) - cursor);
    return true;
}

bool left(const std::string& text, size_t& cursor) {
    size_t c = clamp_cursor(text, cursor);
    cursor = prev_boundary(text, c);
    return cursor != c;
}

bool right(const std::string& text, size_t& cursor) {
    size_t c = clamp_cursor(text, cursor);
    cursor = next_boundary(text, c);
    return cursor != c;
}

bool home(size_t& cursor) {
    bool moved = cursor != 0;
    cursor = 0;
    return moved;
}

bool end(const std::string& text, size_t& cursor) {
    bool moved = cursor != text.size();
    cursor = text.size();
    return moved;
}

}  // namespace soa::text_entry
```
