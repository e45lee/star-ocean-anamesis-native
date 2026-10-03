#pragma once
// The frontend's side of the guest's EGL (hle/egl.cpp): host GLES contexts on the frontend's window,
// presentation and the overlay. The runtime emulates EGL for the guest (a pseudo display, config and
// surfaces) and asks these hooks for the real things: the frontend (app/host.cpp: SDL2) owns the
// window, its surface and the GL contexts. Context handles are opaque to the runtime; the guest
// sees them as its EGLContexts.

namespace soa {

struct GfxHooks {
    virtual ~GfxHooks() = default;

    // ---- host GL contexts (OpenGL ES, same config as the window)
    // A new ES `es_major` context sharing objects with `share` (null: a new share group). It must not
    // change which context is current on the calling thread. Null on failure.
    virtual void* create_context(void* share, int es_major) = 0;
    virtual void destroy_context(void* ctx) = 0;
    // Makes `ctx` current on this thread: on the window's surface (`window`), else on a surface of
    // the frontend's choosing whose framebuffer is never used (the runtime emulates the guest's
    // pbuffers with framebuffer objects). Null `ctx` releases this thread's context.
    virtual bool make_current(void* ctx, bool window) = 0;
    // Presents the window's back buffer (the context current on this thread must be on the window).
    virtual bool swap_window() = 0;
    virtual bool set_swap_interval(int interval) = 0;
    // The window's drawable size in pixels.
    virtual void drawable_size(int* w, int* h) = 0;
    // Present into an offscreen framebuffer of the window's size instead of the window's own
    // (headless: the hidden window's buffers may never exist on some window systems).
    virtual bool offscreen_present() { return false; }
    // The last failure's message, for logs.
    virtual const char* last_error() { return ""; }

    // ---- presentation
    virtual void before_swap() {}
    virtual void after_swap() {}
    // Where the game image lands in the window (for mapping mouse coordinates).
    virtual void set_viewport_rect(int x, int y, int w, int h) {}
    // Draw host UI (movies, screenshots) over the presented frame before swapping. `target_fbo` is
    // the framebuffer that stands for the window (0, or the offscreen one: offscreen_present()).
    virtual void draw_overlay(int window_w, int window_h, unsigned target_fbo) {}
};

void set_gfx_hooks(GfxHooks* h);

// Presents the last frame again (the window stand-in, letterboxed, plus GfxHooks::draw_overlay), when
// the calling thread's context is on the window surface; false (nothing done) otherwise.
bool present_again();

// Idle presenting: repaints while the game shows no new frames. A frontend overlay that changes over
// the game's last frame turns it on (the text-entry box: while the game waits for the keyboard its
// logic thread blocks, and its render thread waits for work). The thread whose context is on the
// window waits in pthread_cond_wait (hle/libc_thread.cpp) in slices of kIdleCheckMs (it may have
// started waiting before idle presenting was turned on), and while idle presenting is on, of
// kIdlePresentMs, presenting the last frame again (present_again) after a slice in which no frame
// was presented.
constexpr int kIdlePresentMs = 33;
constexpr int kIdleCheckMs = 100;
void set_idle_present(bool on);
bool idle_present_on();
// For the HLE's blocking waits: this thread's context is on the window surface.
bool window_thread();
// Presents the last frame again when none was presented for kIdlePresentMs (on the window thread).
void idle_present();

}  // namespace soa
