// The desktop host loop (app/host.h): SDL2 window/input/audio around the runtime, the
// ANativeActivity bring-up and the main loop. Moved from port/src/main.cpp unchanged; the port's
// own pieces (its debug commands, --selftest) plug in through HostConfig's hooks.
#include <soa/env.h>
#include <GLES3/gl3.h>
#include <SDL.h>
#include <zlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cmath>
#include <chrono>
#include <functional>
#include <mutex>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include <thread>

#include "app/host.h"
#include "app/page_overlay.h"
#include "app/sdl_gl.h"
#include "app/text_overlay.h"
#include "android/ndk.h"
#include "android/platform.h"
#include "core/cpu.h"
#include "core/hle.h"
#include "core/loader.h"
#include "core/log.h"
#include "core/profile.h"
#include "core/vfs.h"
#include "frontend/movie.h"
#include "frontend/text_entry.h"
#include "hle/audio.h"
#include "hle/gfx.h"
#include "jni/jvm.h"

using namespace soa;
namespace sdlgl = soa::app::sdlgl;

namespace {
extern std::atomic<float> g_audio_peak;
SDL_Window* g_window = nullptr;
std::string g_title = "STAR OCEAN -anamnesis-";
app::HostConfig* g_cfg = nullptr;  // run()'s config: the host's command hook

// ---------------------------------------------------------------------------
// Graphics hooks

struct Gfx final : GfxHooks {
    std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
    int frames = 0;
    std::atomic<float> fps{0};

    // The guest's EGL contexts (app/sdl_gl.h).
    void* create_context(void* share, int es_major) override { return sdlgl::create_context(share, es_major); }
    void destroy_context(void* ctx) override { sdlgl::destroy_context(ctx); }
    bool make_current(void* ctx, bool window) override { return sdlgl::make_current(ctx, window); }
    bool swap_window() override { return sdlgl::swap_window(); }
    bool set_swap_interval(int interval) override { return sdlgl::set_swap_interval(interval); }
    void drawable_size(int* w, int* h) override { sdlgl::drawable_size(w, h); }
    // Headless off X11: the frame is presented into an offscreen framebuffer of the window's size,
    // and screenshots read it back from there. A Wayland window that is never shown has no buffers
    // SDL presents (it skips the swaps), so they aren't relied on. Under X11 the hidden window's
    // back buffer works, and it keeps the screenshots pixel-identical with windowed runs and the
    // smoke baselines: Mesa d3d12's scaled blit into an FBO rounds a few rows differently (by 1)
    // than into the window. SOA_OFFSCREEN_PRESENT=1/0 forces it on/off for headless runs.
    bool offscreen = false;
    bool offscreen_present() override { return offscreen; }
    const char* last_error() override { return SDL_GetError(); }
    std::atomic<int> vx{0}, vy{0}, vw{0}, vh{0};
    std::atomic<bool> shot_requested{false};
    std::string shot_path;
    void set_viewport_rect(int x, int y, int w, int h) override {
        vx = x, vy = y, vw = w, vh = h;
    }
    void draw_overlay(int ww, int wh, unsigned target_fbo) override {
        if (movie_active()) movie_draw(ww, wh, target_fbo);
        // a host-drawn page (app/page_overlay.h; no GL call unless one is shown)
        if (app::page_overlay::visible()) app::page_overlay::draw(target_fbo, vx, vy, vw, vh, platform().width, platform().height);
        app::text_overlay::draw(ww, wh, target_fbo, vx, vy, vw, vh);  // no-op unless the keyboard is open
        if (shot_requested.exchange(false)) write_screenshot(ww, wh, target_fbo);
    }
    void write_screenshot(int w, int h, unsigned fbo);
    std::atomic<u64> total_frames{0};
    void after_swap() override {
        total_frames.fetch_add(1, std::memory_order_relaxed);
        frames++;
        auto now = std::chrono::steady_clock::now();
        double dt = std::chrono::duration<double>(now - last).count();
        if (dt >= 1.0) {
            fps = frames / dt;
            static int n = 0;
            if (++n % 10 == 0) LOGI("perf", "%.1f fps, audio peak %.2f", fps.load(), g_audio_peak.exchange(0));
            frames = 0;
            last = now;
        }
    }
};
Gfx g_gfx;

}  // namespace

// SOA_WATCHDOG=SECONDS: once frames have started, if none is presented for that long, log it and
// print every guest thread's stack (full stacks need SOA_PROFILE too). For catching deadlocks.
void app::start_watchdog() {
    int secs = (int)env::env_int("SOA_WATCHDOG", 0, 86400, 0);
    if (secs <= 0) return;
    std::thread([secs] {
        u64 last = 0;
        int still = 0;
        bool reported = false;
        for (;;) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            u64 f = g_gfx.total_frames.load(std::memory_order_relaxed);
            if (f == 0 || f != last) {
                last = f, still = 0, reported = false;
                continue;
            }
            if (++still >= secs && !reported) {
                LOGE("watchdog", "no frame presented for %d s (frame %llu); guest thread stacks:", still, (unsigned long long)f);
                profile_print_thread_stacks(stderr);
                reported = true;
            }
        }
    }).detach();
}

namespace {


void png_chunk(std::string& out, const char* type, const std::string& data) {
    auto be32 = [&](u32 v) {
        out.push_back(v >> 24), out.push_back(v >> 16), out.push_back(v >> 8), out.push_back(v);
    };
    be32((u32)data.size());
    std::string td = std::string(type, 4) + data;
    out += td;
    be32((u32)crc32(0, (const Bytef*)td.data(), td.size()));
}

void Gfx::write_screenshot(int w, int h, unsigned fbo) {
    std::vector<u8> px((size_t)w * h * 4);
    GLint prev = 0;
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &prev);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, px.data());
    glBindFramebuffer(GL_READ_FRAMEBUFFER, prev);
    std::string raw;
    for (int y = h - 1; y >= 0; y--) {
        raw.push_back(0);
        for (int x = 0; x < w; x++) raw.append((const char*)&px[((size_t)y * w + x) * 4], 3);
    }
    uLongf zlen = compressBound(raw.size());
    std::string z(zlen, 0);
    compress2((Bytef*)z.data(), &zlen, (const Bytef*)raw.data(), raw.size(), 6);
    z.resize(zlen);
    std::string png = "\x89PNG\r\n\x1a\n", ihdr;
    for (u32 v : {(u32)w, (u32)h}) ihdr.push_back(v >> 24), ihdr.push_back(v >> 16), ihdr.push_back(v >> 8), ihdr.push_back(v);
    ihdr += std::string("\x08\x02\x00\x00\x00", 5);
    png_chunk(png, "IHDR", ihdr);
    png_chunk(png, "IDAT", z);
    png_chunk(png, "IEND", "");
    std::ofstream(shot_path, std::ios::binary) << png;
    LOGI("main", "screenshot saved to %s", shot_path.c_str());
}

// ---------------------------------------------------------------------------
// Audio

SDL_AudioDeviceID g_audio_dev = 0;
constexpr int kAudioRate = 48000;

std::atomic<float> g_audio_peak{0};

// One mix at a time: the device callback or the null sink below.
std::mutex g_audio_mix_m;
std::atomic<s64> g_audio_last_pull_ns{0};  // the device callback's last run (steady clock)

s64 steady_ns() { return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }

void mix_output(float* out, int frames) {
    std::lock_guard lk(g_audio_mix_m);
    audio_mix(out, frames, kAudioRate);
    movie_mix_audio(out, frames, kAudioRate);
    float peak = g_audio_peak.load(std::memory_order_relaxed);
    for (int i = 0; i < frames * 2; i++) {
        out[i] = std::clamp(out[i], -1.0f, 1.0f);
        peak = std::max(peak, std::fabs(out[i]));
    }
    g_audio_peak.store(peak, std::memory_order_relaxed);
}

void audio_callback(void*, Uint8* stream, int len) {
    g_audio_last_pull_ns.store(steady_ns(), std::memory_order_relaxed);
    mix_output((float*)stream, len / (int)(sizeof(float) * 2));
}

// The null sink: the OpenSL ES players (hle/opensles.cpp) only consume their buffer queues when
// the output pulls audio, and the game learns that a sound has ended only from those buffers
// being played (SLVoice buffer callbacks -> end of stream -> SoundObject finished). With no audio
// device (headless runs, no PulseAudio) or a device whose callback stalls (WSLg audio hiccups)
// nothing was ever played: every sound stayed "playing" forever, and whatever waits for a sound
// to end waited too (CEventScenario::IsEnd's list of SEs to finish, voiced lines in auto mode).
// On Android the OpenSL mixer always runs, so while the device isn't pulling, this thread pulls
// at the device's rate (wall clock) and discards the samples.
void null_sink_loop() {
    constexpr int kPeriod = 1024;
    constexpr s64 kStallNs = 250'000'000;
    std::vector<float> buf(kPeriod * 2);
    bool active = false;
    s64 t0 = 0;
    u64 mixed = 0;
    for (;;) {
        std::this_thread::sleep_for(std::chrono::microseconds(kPeriod * 1'000'000LL / kAudioRate));
        s64 now = steady_ns();
        if (g_audio_dev && now - g_audio_last_pull_ns.load(std::memory_order_relaxed) < kStallNs) {
            active = false;
            continue;
        }
        if (!active) {
            active = true, t0 = now, mixed = 0;
            static bool said = false;
            if (!said) LOGI("audio", "no audio device pulling: the null sink plays the sound queues (silently, in real time)");
            said = true;
        }
        u64 due = (u64)((now - t0) * (s64)kAudioRate / 1'000'000'000LL);
        if (due > mixed + kAudioRate / 2) mixed = due - kPeriod;  // don't catch up on long stalls
        while (mixed + kPeriod <= due) {
            mix_output(buf.data(), kPeriod);
            mixed += kPeriod;
        }
    }
}

}  // namespace

// HostHooks::start_audio (android/platform.h; registered in main()).
static void host_start_audio() {
    if (g_audio_dev) return;
    // The null sink starts after the device is (or isn't) open: it reads g_audio_dev.
    struct StartSink {
        ~StartSink() {
            static std::once_flag once;
            std::call_once(once, [] { std::thread(null_sink_loop).detach(); });
        }
    } start_sink;
    SDL_AudioSpec want{}, have{};
    want.freq = kAudioRate;
    want.format = AUDIO_F32SYS;
    want.channels = 2;
    want.samples = 1024;
    want.callback = audio_callback;
    g_audio_dev = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
    if (!g_audio_dev) {
        LOGW("audio", "SDL_OpenAudioDevice failed: %s (continuing without sound)", SDL_GetError());
        return;
    }
    g_audio_last_pull_ns.store(steady_ns(), std::memory_order_relaxed);
    SDL_PauseAudioDevice(g_audio_dev, 0);
    LOGI("audio", "audio device open: %d Hz, %d frames", have.freq, have.samples);
}

// HostHooks::start_text_input.
static void host_start_text_input() {
    // The SDL event loop (main thread) picks this up.
}

// HostHooks::play_movie.
static void host_play_movie() {
    auto& p = platform();
    // movie_playing goes true only once the movie runs: PlayMovie comes from the game thread, and
    // the main loop's end check (movie_playing && !movie_active()) used to see the flag before
    // movie_start had begun, "ended" the movie at once and left it playing unwatched.
    bool ok = movie_start(p.movie_path, p.movie_is_file, p.movie_volume);
    if (!ok) LOGW("movie", "can't play %s; skipping it", p.movie_path.c_str());
    p.movie_playing = ok;
}

namespace {

// ---------------------------------------------------------------------------
// Input

s64 now_ns() { return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }

void push_touch(int action, float x, float y) {
    if (app::page_overlay::touch(action, x, y)) return;  // a touch on a host-drawn page (app/page_overlay.h)
    InputEvent e;
    e.type = 2;          // AINPUT_EVENT_TYPE_MOTION
    e.source = 0x1002;   // AINPUT_SOURCE_TOUCHSCREEN
    e.action = action;
    e.time_ns = now_ns();
    e.pointer_count = 1;
    e.pointers[0] = {0, x, y, action == 1 ? 0.0f : 1.0f};
    input_queue().push(e);
}

// ---------------------------------------------------------------------------
// Pinch emulation: the mouse wheel drives a two-finger pinch centred on the cursor.
//
// Aska::TouchCallback records one pointer per motion event (the one indexed by the action),
// so MOVE events for a pinch are sent one finger at a time.

void push_motion(int action, std::initializer_list<InputEvent::Pointer> ptrs) {
    InputEvent e;
    e.type = 2;
    e.source = 0x1002;
    e.action = action;
    e.time_ns = now_ns();
    e.pointer_count = 0;
    for (auto& p : ptrs) e.pointers[e.pointer_count++] = p;
    input_queue().push(e);
}

struct Pinch {
    bool active = false;
    float cx = 0, cy = 0;       // centre (game coordinates)
    float spread = 0, target = 0;  // half-distance between the fingers
    std::chrono::steady_clock::time_point last_input;

    float min_spread() const { return platform().height * 0.02f; }
    float max_spread() const { return platform().height * 0.45f; }
    // The fingers sit on a line parallel to the screen diagonal. Pinch consumers such as
    // CViewerBehavoir compare max(dWidth/screenW, dHeight/screenH) of the fingers' bounding box,
    // so a purely horizontal pinch-in (dHeight = 0) would never register as zooming out.
    InputEvent::Pointer finger(int id) const {
        float w = (float)platform().width, h = (float)platform().height, diag = std::sqrt(w * w + h * h);
        float sign = id == 0 ? -1.0f : 1.0f;
        float x = cx + sign * spread * w / diag, y = cy + sign * spread * h / diag;
        return {id, std::clamp(x, 0.0f, w - 1), std::clamp(y, 0.0f, h - 1), 1.0f};
    }

    // dy > 0: wheel up = fingers apart (zoom in); dy < 0: together (zoom out).
    void wheel(float gx, float gy, float dy) {
        if (!active) {
            active = true;
            cx = gx, cy = gy;
            spread = target = platform().height * 0.15f;
            push_motion(0, {finger(0)});                   // ACTION_DOWN
            push_motion(5 | (1 << 8), {finger(0), finger(1)});  // ACTION_POINTER_DOWN, index 1
        }
        target = std::clamp(target * std::pow(1.15f, dy), min_spread(), max_spread());
        last_input = std::chrono::steady_clock::now();
    }

    // Called every main-loop iteration: moves the fingers towards the target, and lifts them
    // once the wheel has been idle for a moment.
    void update() {
        if (!active) return;
        if (spread != target) {
            float step = platform().height * 0.012f;
            spread = std::fabs(target - spread) <= step ? target : spread + (target > spread ? step : -step);
            push_motion(2, {finger(0)});  // ACTION_MOVE, one finger per event
            push_motion(2, {finger(1)});
            return;
        }
        if (std::chrono::steady_clock::now() - last_input > std::chrono::milliseconds(250)) end();
    }

    void end() {
        if (!active) return;
        push_motion(6 | (1 << 8), {finger(0), finger(1)});  // ACTION_POINTER_UP, index 1
        auto f = finger(0);
        f.pressure = 0;
        push_motion(1, {f});  // ACTION_UP
        active = false;
    }
};
Pinch g_pinch;

void push_key(int action, int keycode) {
    InputEvent e;
    e.type = 1;          // AINPUT_EVENT_TYPE_KEY
    e.source = 0x101;    // AINPUT_SOURCE_KEYBOARD
    e.action = action;   // AKEY_EVENT_ACTION_DOWN / UP
    e.keycode = keycode;
    e.time_ns = now_ns();
    input_queue().push(e);
}

// Window coordinates -> the game's screen coordinates, through the letterboxed viewport.
void map_mouse(int wx, int wy, float& x, float& y) {
    int ww, wh, pw, ph;
    SDL_GetWindowSize(g_window, &ww, &wh);
    SDL_GL_GetDrawableSize(g_window, &pw, &ph);
    if (pw <= 0 || ph <= 0) pw = ww, ph = wh;
    float sx = (float)wx * pw / std::max(1, ww), sy = (float)wy * ph / std::max(1, wh);
    int vw = g_gfx.vw, vh = g_gfx.vh, vx = g_gfx.vx, vy = g_gfx.vy;
    if (vw <= 0 || vh <= 0) vx = 0, vy = 0, vw = pw, vh = ph;
    // viewport y is from the bottom in GL terms
    float top = (float)(ph - (vy + vh));
    x = std::clamp((sx - vx) / vw, 0.0f, 1.0f) * platform().width;
    y = std::clamp((sy - top) / vh, 0.0f, 1.0f) * platform().height;
}

void update_title() {
    std::string t = g_title;
    auto& p = platform();
    if (p.text_active) {
        std::lock_guard lk(p.text_mutex);
        t += "  |  Type text, Enter to confirm, Esc to cancel: " + p.text_editing + "_";
    } else {
        char buf[32];
        snprintf(buf, sizeof buf, "  |  %.0f fps", g_gfx.fps.load());
        t += buf;
    }
    SDL_SetWindowTitle(g_window, t.c_str());
}

// ---------------------------------------------------------------------------
// Text entry (the emulated KeyboardActivity: platform().text_*). Keys, committed text (typing, an
// IME, a paste) and the IME's composition go through the editor (frontend/text_entry.h), which
// keeps the field's max length and numeric filter; app/text_overlay.h draws the box.

// Ends text entry: Enter (`ok`) hands the text to the game (GetEditText), Esc an empty string.
void finish_text(Platform& p, bool ok) {
    p.text_value = ok ? p.text_editing : std::string();
    p.text_composition.clear();
    p.text_serial++;
    p.text_active = false;
}

void insert_text(Platform& p, std::string_view add) {
    text_entry::insert(p.text_editing, p.text_cursor, add, {p.text_max_len, p.text_numeric});
    p.text_serial++;
}

bool handle_text_event(const SDL_Event& ev) {
    auto& p = platform();
    if (!p.text_active) {
        if (ev.type == SDL_TEXTEDITING_EXT) SDL_free(ev.editExt.text);
        return false;
    }
    switch (ev.type) {
    case SDL_TEXTINPUT: {  // committed text: typed, or the IME's result
        std::lock_guard lk(p.text_mutex);
        p.text_composition.clear();
        insert_text(p, ev.text.text);
        return true;
    }
    case SDL_TEXTEDITING:      // the IME's composition (start: its caret, in code points)
    case SDL_TEXTEDITING_EXT: {  // the same, unlimited length (SDL_HINT_IME_SUPPORT_EXTENDED_TEXT)
        bool ext = ev.type == SDL_TEXTEDITING_EXT;
        const char* text = ext ? ev.editExt.text : ev.edit.text;
        int start = ext ? ev.editExt.start : ev.edit.start;
        {
            std::lock_guard lk(p.text_mutex);
            p.text_composition = text ? text : "";
            p.text_comp_cursor = text_entry::byte_offset(p.text_composition, (size_t)std::max(0, start));
            p.text_serial++;
        }
        if (ext) SDL_free(ev.editExt.text);
        return true;
    }
    case SDL_KEYDOWN: {
        auto k = ev.key.keysym.sym;
        if (k == SDLK_F11 || k == SDLK_F12) return false;  // fullscreen, screenshot
        std::lock_guard lk(p.text_mutex);
        if (!p.text_composition.empty()) return true;  // the IME owns the keys while it composes
        auto& t = p.text_editing;
        auto& c = p.text_cursor;
        bool changed = false;
        if (k == SDLK_BACKSPACE) changed = text_entry::backspace(t, c);
        else if (k == SDLK_DELETE) changed = text_entry::del(t, c);
        else if (k == SDLK_LEFT) changed = text_entry::left(t, c);
        else if (k == SDLK_RIGHT) changed = text_entry::right(t, c);
        else if (k == SDLK_HOME) changed = text_entry::home(c);
        else if (k == SDLK_END) changed = text_entry::end(t, c);
        else if (k == SDLK_RETURN || k == SDLK_KP_ENTER) finish_text(p, true);
        else if (k == SDLK_ESCAPE) finish_text(p, false);
        else if (k == SDLK_v && (ev.key.keysym.mod & KMOD_CTRL)) {
            if (char* clip = SDL_GetClipboardText()) {  // a paste obeys the field like typing does
                insert_text(p, clip);
                SDL_free(clip);
            }
        }
        if (changed) p.text_serial++;
        return true;
    }
    case SDL_KEYUP:
        return ev.key.keysym.sym != SDLK_F11 && ev.key.keysym.sym != SDLK_F12;
    default:
        return false;
    }
}

// The box's text field in window coordinates (points), for the IME's candidate window.
SDL_Rect text_input_rect() {
    int ww, wh, pw, ph;
    SDL_GetWindowSize(g_window, &ww, &wh);
    SDL_GL_GetDrawableSize(g_window, &pw, &ph);
    if (pw <= 0 || ph <= 0) pw = ww, ph = wh;
    int vw = g_gfx.vw, vh = g_gfx.vh, vx = g_gfx.vx, vy = g_gfx.vy;
    if (vw <= 0 || vh <= 0) vx = 0, vy = 0, vw = pw, vh = ph;
    auto f = app::text_overlay::layout(vx, vy, vw, vh, ph).field;
    return {f.x * ww / pw, f.y * wh / ph, f.w * ww / pw, f.h * wh / ph};
}

// Each main-loop iteration: SDL text input on while the game's keyboard is open (and off otherwise,
// so an IME doesn't take the game's keys), the IME rect kept on the box, idle presenting on so the
// box repaints while the game shows no frames.
void update_text_input() {
    static bool was = false;
    static SDL_Rect last{};
    bool on = platform().text_active;
    if (on != was) {
        was = on;
        if (on) {
            SDL_StartTextInput();
            last = {};
        } else {
            SDL_StopTextInput();
            std::lock_guard lk(platform().text_mutex);
            platform().text_composition.clear();
        }
    }
    if (on) {
        SDL_Rect r = text_input_rect();
        if (r.x != last.x || r.y != last.y || r.w != last.w || r.h != last.h) {  // also after a resize
            SDL_SetTextInputRect(&r);
            last = r;
        }
    }
    set_idle_present(on);
}

// The test commands type:, compose: and key: (run_command) go through handle_text_event like
// SDL's events.
void command_type(const std::string& s) {
    for (size_t i = 0; i < s.size();) {
        size_t j = text_entry::next_boundary(s, i);
        SDL_Event ev{};
        ev.type = SDL_TEXTINPUT;
        memcpy(ev.text.text, s.data() + i, std::min(j - i, sizeof ev.text.text - 1));
        i = j;
        handle_text_event(ev);
    }
}
void command_compose(const std::string& s) {
    SDL_Event ev{};
    ev.type = SDL_TEXTEDITING_EXT;
    ev.editExt.text = SDL_strdup(s.c_str());
    ev.editExt.start = (Sint32)text_entry::utf8_len(s);  // the caret at the end
    if (!handle_text_event(ev)) LOGW("control", "compose: the keyboard isn't open");
}
void command_key(const std::string& name) {
    static const std::pair<const char*, SDL_Keycode> kKeys[] = {
        {"enter", SDLK_RETURN}, {"escape", SDLK_ESCAPE}, {"backspace", SDLK_BACKSPACE}, {"delete", SDLK_DELETE},
        {"left", SDLK_LEFT}, {"right", SDLK_RIGHT}, {"home", SDLK_HOME}, {"end", SDLK_END},
    };
    for (auto& [n, k] : kKeys)
        if (name == n) {
            SDL_Event ev{};
            ev.type = SDL_KEYDOWN;
            ev.key.state = SDL_PRESSED;
            ev.key.keysym.sym = k;
            if (!handle_text_event(ev)) LOGW("control", "key: the keyboard isn't open");
            return;
        }
    LOGW("control", "key: unknown key '%s'", name.c_str());
}

// ---------------------------------------------------------------------------
// Scripted/remote control: "tap:X:Y", "drag:X1:Y1:X2:Y2[:MS]", "wheel:X:Y:DY", "back", "text:STRING",
// "shot:PATH", "resize:W:H", "fullscreen", "quit"; the control FIFO also accepts "wait:MS".
// Text entry while the game's keyboard is open: "text:STRING" finishes it with STRING at once (no
// editor, no box); for testing the editor and the box (they go through the SDL event path):
// "type:TEXT" (typed, one SDL_TEXTINPUT per code point), "compose:TEXT" (an IME composition with its
// caret at the end; empty clears it), "key:enter|escape|backspace|delete|left|right|home|end".

std::mutex g_control_mutex;
std::vector<std::string> g_control_cmds;

void run_command(const std::string& cmd) {
    LOGI("control", "%s", cmd.c_str());
    // tap/drag coordinates are window pixels, mapped like the mouse.
    float tx, ty, tx2, ty2;
    if (sscanf(cmd.c_str(), "tap:%f:%f", &tx, &ty) == 2) {
        map_mouse((int)tx, (int)ty, tx, ty);
        push_touch(0, tx, ty);
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        push_touch(1, tx, ty);
    } else if (float ms = 300; sscanf(cmd.c_str(), "drag:%f:%f:%f:%f:%f", &tx, &ty, &tx2, &ty2, &ms) >= 4) {
        // drag:X1:Y1:X2:Y2[:MS]: MS (default 300) is the drag's duration, in 30 ms steps; a slow
        // drag reaches the game as a drag even when it renders few frames (machine load).
        map_mouse((int)tx, (int)ty, tx, ty);
        map_mouse((int)tx2, (int)ty2, tx2, ty2);
        push_touch(0, tx, ty);
        int steps = std::max(10, (int)(ms / 30));
        for (int i = 1; i <= steps; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            push_touch(2, tx + (tx2 - tx) * i / steps, ty + (ty2 - ty) * i / steps);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(ms > 300 ? 200 : 0));
        push_touch(1, tx2, ty2);
    } else if (sscanf(cmd.c_str(), "wheel:%f:%f:%f", &tx, &ty, &tx2) == 3) {  // wheel:X:Y:DY
        map_mouse((int)tx, (int)ty, tx, ty);
        if (!app::page_overlay::wheel(tx, ty, tx2)) g_pinch.wheel(tx, ty, tx2);
    } else if (cmd == "back") {
        push_key(0, 4);
        push_key(1, 4);
    } else if (cmd.rfind("text:", 0) == 0) {
        auto& p = platform();
        std::lock_guard lk(p.text_mutex);
        p.text_value = cmd.substr(5);
        p.text_active = false;
    } else if (cmd.rfind("type:", 0) == 0) {
        if (!platform().text_active) LOGW("control", "type: the keyboard isn't open");
        command_type(cmd.substr(5));
    } else if (cmd.rfind("compose:", 0) == 0) {
        command_compose(cmd.substr(8));
    } else if (cmd.rfind("key:", 0) == 0) {
        command_key(cmd.substr(4));
    } else if (cmd.rfind("shot:", 0) == 0) {
        g_gfx.shot_path = cmd.substr(5);
        g_gfx.shot_requested = true;
    } else if (cmd.rfind("movie:", 0) == 0) {  // test hook: movie:asset/path.mp4
        auto& p = platform();
        p.movie_path = cmd.substr(6);
        p.movie_is_file = false;
        p.movie_playing = true;
        frontend_play_movie();
    } else if (cmd == "skip") {
        movie_stop();
        platform().movie_playing = false;
    } else if (sscanf(cmd.c_str(), "resize:%f:%f", &tx, &ty) == 2) {
        SDL_SetWindowFullscreen(g_window, 0);
        SDL_SetWindowSize(g_window, (int)tx, (int)ty);
    } else if (cmd == "fullscreen") {
        SDL_SetWindowFullscreen(g_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else if (cmd == "profile-dump") {
        profile_dump();
    } else if (cmd == "quit") {
        platform().quit_requested = true;
    } else if (g_cfg && g_cfg->command && g_cfg->command(cmd)) {  // the host's own commands (HostConfig::command)
    } else {
        LOGW("control", "unknown command '%s'", cmd.c_str());
    }
}

// Reads commands (one per line) from a FIFO so a running instance can be driven externally.
void control_thread(std::string path) {
    unlink(path.c_str());
    if (mkfifo(path.c_str(), 0600) != 0) {
        LOGE("control", "mkfifo %s failed", path.c_str());
        return;
    }
    LOGI("control", "listening on %s", path.c_str());
    for (;;) {
        FILE* f = fopen(path.c_str(), "r");
        if (!f) return;
        char line[1024];
        while (fgets(line, sizeof line, f)) {
            std::string l = line;
            while (!l.empty() && (l.back() == '\n' || l.back() == '\r')) l.pop_back();
            if (l.empty()) continue;
            std::lock_guard lk(g_control_mutex);
            g_control_cmds.push_back(l);
        }
        fclose(f);
    }
}

// ---------------------------------------------------------------------------
// ANativeActivity

struct ANativeActivityGuest {
    u64 callbacks, vm, env, clazz, internalDataPath, externalDataPath;
    s32 sdkVersion, pad;
    u64 instance, assetManager, obbPath;
};
enum CallbackSlot {
    onStart = 0, onResume, onSaveInstanceState, onPause, onStop, onDestroy, onWindowFocusChanged, onNativeWindowCreated,
    onNativeWindowResized, onNativeWindowRedrawNeeded, onNativeWindowDestroyed, onInputQueueCreated, onInputQueueDestroyed,
    onContentRectChanged, onConfigurationChanged, onLowMemory
};
u64 g_callbacks[16];
ANativeActivityGuest g_activity;

void activity_cb(CallbackSlot s, std::initializer_list<u64> extra = {}) {
    u64 fn = g_callbacks[s];
    if (!fn) return;
    GuestArgs a;
    a.i((u64)&g_activity);
    for (u64 v : extra) a.i(v);
    LOGD("main", "activity callback %d", (int)s);
    guest_call(fn, a);
}

}  // namespace

void app::install_host_hooks() {
    // The runtime's calls into this frontend (runtime/src/android/platform.h).
    host_hooks().start_audio = host_start_audio;
    host_hooks().start_text_input = host_start_text_input;
    host_hooks().play_movie = host_play_movie;
}

void app::run(LoadedLib& lib, HostConfig& cfg) {
    g_cfg = &cfg;
    g_title = cfg.title;
    auto& vm = jni::Vm::get();
    auto& am = asset_manager();
    int width = cfg.width, height = cfg.height;
    const bool landscape = cfg.landscape, fullscreen = cfg.fullscreen;
    const std::string& render_size = cfg.render_size;
    std::vector<std::string>& shots = cfg.shots;
    std::vector<std::string>& actions = cfg.actions;
    const std::string& control_path = cfg.control_path;

    // ---- window ----
    // SDL picks the video driver (X11 or Wayland; SDL_VIDEODRIVER chooses). The window is an
    // OpenGL ES window: SDL owns its surface and the GL contexts, the runtime emulates the guest's
    // EGL over them (hle/egl.cpp, app/sdl_gl.h).
    // An IME's composition arrives whole (SDL_TEXTEDITING_EXT), not in 32-byte pieces.
    SDL_SetHint(SDL_HINT_IME_SUPPORT_EXTENDED_TEXT, "1");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) fatal("SDL_Init: %s", SDL_GetError());
    sdlgl::set_attributes();
    SDL_DisplayMode desktop{};
    if (SDL_GetDesktopDisplayMode(0, &desktop) != 0 || desktop.w <= 0) desktop.w = 1920, desktop.h = 1080;
    if (width <= 0 || height <= 0) {
        // STAR OCEAN: anamnesis is a portrait game; its layouts and home camera assume a tall screen.
        if (landscape) {
            width = std::min(1280, desktop.w * 9 / 10);
            height = width * 9 / 16;
        } else {
            height = desktop.h * 9 / 10;
            width = height * 9 / 16;
        }
    }
    if (fullscreen) width = desktop.w, height = desktop.h;
    Uint32 wflags = (cfg.hidden ? SDL_WINDOW_HIDDEN : SDL_WINDOW_SHOWN) | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                    (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    g_window = SDL_CreateWindow(g_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, wflags);
    if (!g_window) fatal("SDL_CreateWindow: %s", SDL_GetError());
    sdlgl::init(g_window);
    // SDL starts with text input on; it is on only while the game's keyboard is open
    // (update_text_input), so an IME never takes the game's keys.
    SDL_StopTextInput();
    app::text_overlay::set_font_request(cfg.font);
    if (cfg.hidden) {
        // SOA_OFFSCREEN_PRESENT (env_tristate): unset = offscreen unless the video driver is x11.
        g_gfx.offscreen = env::env_tristate("SOA_OFFSCREEN_PRESENT").value_or(strcmp(SDL_GetCurrentVideoDriver(), "x11") != 0);
    }

    // The game's screen size. It lays out its UI and allocates its render targets for this once, at
    // startup (phones never resize), and the frontend scales the result into the window. Rendering
    // at the desktop size by default keeps it sharp when the window is enlarged or made fullscreen;
    // smaller windows get a downsampled (supersampled) image.
    int game_w = width, game_h = height;
    if (render_size == "desktop") {
        double scale = std::min((double)desktop.w / width, (double)desktop.h / height);
        if (scale > 1.0) game_w = (int)(width * scale + 0.5), game_h = (int)(height * scale + 0.5);
    } else if (render_size != "window" && sscanf(render_size.c_str(), "%dx%d", &game_w, &game_h) != 2) {
        fatal("bad --render-size '%s'", render_size.c_str());
    }
    game_w &= ~1, game_h &= ~1;
    LOGI("main", "window %dx%d (%s%s), desktop %dx%d, game screen %dx%d%s", width, height, SDL_GetCurrentVideoDriver(),
         cfg.hidden ? (g_gfx.offscreen ? ", hidden, presenting offscreen" : ", hidden") : "", desktop.w, desktop.h, game_w,
         game_h, cfg.size_note.c_str());
    set_gfx_hooks(&g_gfx);
    platform().width = game_w;
    platform().height = game_h;
    auto& win = native_window();
    win.width = game_w;
    win.height = game_h;
    win.host_window = g_window;

    // ---- activity ----
    std::string internal = guest_internal_dir(), external = guest_external_dir(), obb = "/storage/emulated/0/Android/obb/" + std::string(kPackageName);
    g_activity = {};
    g_activity.callbacks = (u64)g_callbacks;
    g_activity.vm = vm.vm_ptr();
    g_activity.env = vm.env_ptr();
    g_activity.clazz = (u64)vm.activity;
    g_activity.internalDataPath = (u64)strdup(internal.c_str());
    g_activity.externalDataPath = (u64)strdup(external.c_str());
    g_activity.sdkVersion = 30;
    g_activity.assetManager = (u64)&am;
    g_activity.obbPath = (u64)strdup(obb.c_str());

    u64 onload = lib.sym("JNI_OnLoad");
    if (onload) LOGI("main", "JNI_OnLoad = %#lx", guest_call(onload, {vm.vm_ptr(), 0}));
    u64 oncreate = lib.sym("ANativeActivity_onCreate");
    if (!oncreate) fatal("ANativeActivity_onCreate not found");
    guest_call(oncreate, {(u64)&g_activity, 0, 0});
    activity_cb(onStart);
    activity_cb(onResume);
    activity_cb(onNativeWindowCreated, {(u64)&win});
    activity_cb(onInputQueueCreated, {(u64)&input_queue()});
    static s32 rect[4] = {0, 0, game_w, game_h};
    activity_cb(onContentRectChanged, {(u64)rect});
    activity_cb(onWindowFocusChanged, {1});
    LOGI("main", "activity started");
    if (!control_path.empty()) std::thread(control_thread, control_path).detach();

    // ---- event loop ----
    bool mouse_down = false;
    auto start_time = std::chrono::steady_clock::now();
    auto last_title = start_time;
    int shot_counter = 0;
    while (!platform().quit_requested) {
        SDL_Event ev;
        while (SDL_WaitEventTimeout(&ev, 10)) {
            if (ev.type == SDL_QUIT) platform().quit_requested = true;
            // The window's close button. SDL2 sends SDL_QUIT only when the last window closes, and
            // the GL backend keeps hidden helper windows (app/sdl_gl.cpp), so the game window's
            // close arrives only as a window event.
            if (ev.type == SDL_WINDOWEVENT && ev.window.event == SDL_WINDOWEVENT_CLOSE &&
                ev.window.windowID == SDL_GetWindowID(g_window))
                platform().quit_requested = true;
            if (handle_text_event(ev)) continue;
            // While a movie plays, a click or Esc/Space/Enter skips it (MoviePlayerActivity's skip dialog).
            if (platform().movie_playing) {
                bool skip = ev.type == SDL_MOUSEBUTTONDOWN ||
                            (ev.type == SDL_KEYDOWN && (ev.key.keysym.sym == SDLK_ESCAPE || ev.key.keysym.sym == SDLK_SPACE || ev.key.keysym.sym == SDLK_RETURN));
                if (skip) {
                    movie_stop();
                    platform().movie_playing = false;
                }
                continue;
            }
            float x, y;
            switch (ev.type) {
            case SDL_MOUSEWHEEL: {
                if (mouse_down) break;  // don't mix with a drag in progress
                int mx, my;
                SDL_GetMouseState(&mx, &my);
                map_mouse(mx, my, x, y);
                float dy = ev.wheel.preciseY != 0 ? ev.wheel.preciseY : (float)ev.wheel.y;
                if (ev.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) dy = -dy;
                if (app::page_overlay::wheel(x, y, dy)) break;  // scrolls a host-drawn page
                g_pinch.wheel(x, y, dy);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
                if (g_pinch.active) g_pinch.end();
                if (ev.button.button == SDL_BUTTON_LEFT) {
                    map_mouse(ev.button.x, ev.button.y, x, y);
                    push_touch(0, x, y);
                    mouse_down = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (ev.button.button == SDL_BUTTON_LEFT && mouse_down) {
                    map_mouse(ev.button.x, ev.button.y, x, y);
                    push_touch(1, x, y);
                    mouse_down = false;
                }
                break;
            case SDL_MOUSEMOTION:
                if (mouse_down) {
                    map_mouse(ev.motion.x, ev.motion.y, x, y);
                    push_touch(2, x, y);
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if (ev.key.repeat) break;
                if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_F12) {
                    g_gfx.shot_path = vfs_config().root + "/screenshot-" + std::to_string(shot_counter++) + ".png";
                    g_gfx.shot_requested = true;
                    break;
                }
                if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_F11) {
                    bool fs = SDL_GetWindowFlags(g_window) & SDL_WINDOW_FULLSCREEN_DESKTOP;
                    SDL_SetWindowFullscreen(g_window, fs ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                    break;
                }
                if (ev.key.keysym.sym == SDLK_ESCAPE || ev.key.keysym.sym == SDLK_BACKSPACE) push_key(ev.type == SDL_KEYDOWN ? 0 : 1, 4 /*AKEYCODE_BACK*/);
                break;
            }
        }
        update_text_input();
        platform_run_ui_tasks();
        g_pinch.update();
        if (cfg.tick) cfg.tick();  // HostConfig::tick (the port: --selftest)
        if (platform().movie_playing && !movie_active()) {
            LOGI("movie", "ended");
            movie_stop();
            platform().movie_playing = false;
        }
        auto now = std::chrono::steady_clock::now();
        // Remote commands run in order; "wait:MS" holds the rest of the queue for that long.
        static auto control_resume = std::chrono::steady_clock::now();
        while (now >= control_resume) {
            std::string c;
            {
                std::lock_guard lk(g_control_mutex);
                if (g_control_cmds.empty()) break;
                c = g_control_cmds.front();
                g_control_cmds.erase(g_control_cmds.begin());
            }
            int ms;
            if (sscanf(c.c_str(), "wait:%d", &ms) == 1) control_resume = now + std::chrono::milliseconds(ms);
            else run_command(c);
        }
        while (!actions.empty()) {
            std::string act = actions.front();
            auto c1 = act.find(':');
            if (std::chrono::duration<double>(now - start_time).count() < atof(act.substr(0, c1).c_str())) break;
            actions.erase(actions.begin());
            run_command(act.substr(c1 + 1));
        }

        if (!shots.empty() && !g_gfx.shot_requested) {
            auto colon = shots.front().find(':');
            double when = atof(shots.front().substr(0, colon).c_str());
            if (std::chrono::duration<double>(now - start_time).count() >= when) {
                g_gfx.shot_path = shots.front().substr(colon + 1);
                g_gfx.shot_requested = true;
                shots.erase(shots.begin());
            }
        }
        if (now - last_title > std::chrono::milliseconds(500) || platform().text_active) {
            update_title();
            last_title = now;
        }
    }
    LOGI("main", "quitting");
    profile_dump();
    fflush(stdout);
    _exit(0);
}
