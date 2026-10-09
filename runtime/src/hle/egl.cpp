// EGL for the guest: emulated over the frontend's GL contexts (gfx.h, GfxHooks; app/host.cpp creates
// them with SDL2 on its window, X11 or Wayland). The runtime never opens a host EGL display or
// surface itself: the guest gets a pseudo display, one config, and surface tokens; contexts are the
// frontend's (their handles are what the guest sees as EGLContext).
//
// What libSOA does with EGL (Aska::RenderDeviceGL, see runtime/README.md, "Graphics"):
//   - eglChooseConfig three times (InitFrameBufferConfig): {DEPTH 24} (no config: it falls back to
//     depth 16), {SURFACE_TYPE SWAP_BEHAVIOR_PRESERVED} (result unused), then RGBA8 + D24 (or 16) + S8,
//     ES2-renderable; eglGetConfigAttrib(EGL_NATIVE_VISUAL_ID) becomes the format argument of
//     ANativeWindow_setBuffersGeometry.
//   - one 1x1 pbuffer (Init), the draw surface of every context that isn't presenting;
//   - contexts: a temporary ES2 one for the version check (CheckGLESVersion: made current on the
//     pbuffer, glGetString, destroyed), a root ES3 context that is never made current, and two ES3
//     contexts sharing with it: the render thread's (on the window surface) and a worker's;
//   - the window surface, recreated when the window size changes, with eglSurfaceAttrib(
//     EGL_SWAP_BEHAVIOR, EGL_BUFFER_DESTROYED); eglQuerySurface for its width and height;
//     eglSwapInterval(1); eglGetCurrentContext to test "is my context current" on every thread.
// Every call is logged (tag "egl"); unexpected attributes are logged as warnings.
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <atomic>
#include <chrono>
#include <cinttypes>
#include <cstring>
#include <mutex>
#include <set>
#include <string>
#include <unordered_map>

#include "soaruntime/android/ndk.h"
#include "soaruntime/core/hle.h"
#include "soaruntime/core/log.h"
#include "hle/egl_state.h"
#include "hle/gfx.h"

namespace soa {

namespace {

GfxHooks* g_hooks = nullptr;

// Idle presenting (gfx.h).
std::atomic<bool> g_idle_present{false};
std::atomic<s64> g_last_present_ns{0};  // the last window present (the guest's or an idle one)
s64 steady_ns() { return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }
bool window_current() {
    egl_emu::Surface* s = egl_emu::current_draw();
    return s && s->kind == egl_emu::Surface::Window && !s->destroyed;
}

// ---- objects

// The display: any address the guest can compare; EGL_NO_DISPLAY is 0.
struct Display {
    bool initialized = false;
} g_display;

// The one config: what the frontend's contexts render with (RGBA8, and the D24S8 of the stand-in
// framebuffers, gles.cpp), as an Android driver would describe it.
struct Config {
    EGLint id;
    EGLint red, green, blue, alpha, depth, stencil;
} const g_config = {1, 8, 8, 8, 8, 24, 8};

constexpr EGLint kSurfaceTypes = EGL_WINDOW_BIT | EGL_PBUFFER_BIT;
constexpr EGLint kRenderableTypes = EGL_OPENGL_ES2_BIT | EGL_OPENGL_ES3_BIT_KHR;
// EGL_NATIVE_VISUAL_ID on Android is the window's pixel format: WINDOW_FORMAT_RGBA_8888.
constexpr EGLint kNativeVisual = 1;

std::mutex g_mutex;  // the sets below
std::set<const void*> g_surfaces;               // live egl_emu::Surface objects (destroyed ones are kept, flagged)
std::unordered_map<void*, int> g_contexts;      // host context -> ES major version

thread_local EGLint t_error = EGL_SUCCESS;
thread_local void* t_ctx = nullptr;
thread_local egl_emu::Surface* t_draw = nullptr;

template <typename T>
T fail(EGLint err, T r) {
    t_error = err;
    return r;
}

bool valid_display(EGLDisplay d) {
    if (d != (EGLDisplay)&g_display) return fail(EGL_BAD_DISPLAY, false);
    if (!g_display.initialized) return fail(EGL_NOT_INITIALIZED, false);
    return true;
}
bool valid_config(EGLConfig c) { return c == (EGLConfig)&g_config || fail(EGL_BAD_CONFIG, false); }
egl_emu::Surface* surface(EGLSurface s) {
    std::lock_guard lk(g_mutex);
    auto* p = (egl_emu::Surface*)s;
    if (!g_surfaces.count(p) || p->destroyed) return fail(EGL_BAD_SURFACE, (egl_emu::Surface*)nullptr);
    return p;
}
bool valid_context(EGLContext c) {
    std::lock_guard lk(g_mutex);
    return g_contexts.count((void*)c) || fail(EGL_BAD_CONTEXT, false);
}

std::string attribs_str(const EGLint* a) {
    std::string s;
    char buf[32];
    for (; a && *a != EGL_NONE; a += 2) {
        snprintf(buf, sizeof buf, "%#x=%d ", a[0], a[1]);
        s += buf;
    }
    return s;
}

// ---- configs

bool config_attrib(EGLint attr, EGLint* v) {
    const Config& c = g_config;
    switch (attr) {
    case EGL_CONFIG_ID: *v = c.id; return true;
    case EGL_BUFFER_SIZE: *v = c.red + c.green + c.blue + c.alpha; return true;
    case EGL_RED_SIZE: *v = c.red; return true;
    case EGL_GREEN_SIZE: *v = c.green; return true;
    case EGL_BLUE_SIZE: *v = c.blue; return true;
    case EGL_ALPHA_SIZE: *v = c.alpha; return true;
    case EGL_DEPTH_SIZE: *v = c.depth; return true;
    case EGL_STENCIL_SIZE: *v = c.stencil; return true;
    case EGL_LUMINANCE_SIZE: case EGL_ALPHA_MASK_SIZE: case EGL_SAMPLES: case EGL_SAMPLE_BUFFERS: case EGL_LEVEL:
    case EGL_MIN_SWAP_INTERVAL: case EGL_BIND_TO_TEXTURE_RGB: case EGL_BIND_TO_TEXTURE_RGBA: case EGL_NATIVE_RENDERABLE:
    case EGL_TRANSPARENT_RED_VALUE: case EGL_TRANSPARENT_GREEN_VALUE: case EGL_TRANSPARENT_BLUE_VALUE:
        *v = 0;
        return true;
    case EGL_MAX_SWAP_INTERVAL: *v = 1; return true;
    case EGL_COLOR_BUFFER_TYPE: *v = EGL_RGB_BUFFER; return true;
    case EGL_CONFIG_CAVEAT: *v = EGL_NONE; return true;
    case EGL_TRANSPARENT_TYPE: *v = EGL_NONE; return true;
    case EGL_SURFACE_TYPE: *v = kSurfaceTypes; return true;
    case EGL_RENDERABLE_TYPE: case EGL_CONFORMANT: *v = kRenderableTypes; return true;
    case EGL_NATIVE_VISUAL_ID: *v = kNativeVisual; return true;
    case EGL_NATIVE_VISUAL_TYPE: *v = EGL_NONE; return true;
    case EGL_MAX_PBUFFER_WIDTH: case EGL_MAX_PBUFFER_HEIGHT: *v = 16384; return true;
    case EGL_MAX_PBUFFER_PIXELS: *v = 16384 * 16384; return true;
    default: return false;
    }
}

// EGL 1.5 section 3.4.1.2: does the config match one requested attribute?
bool config_matches(EGLint attr, EGLint want) {
    if (want == EGL_DONT_CARE) return true;
    EGLint have = 0;
    if (!config_attrib(attr, &have)) return false;
    switch (attr) {
    case EGL_BUFFER_SIZE: case EGL_RED_SIZE: case EGL_GREEN_SIZE: case EGL_BLUE_SIZE: case EGL_ALPHA_SIZE:
    case EGL_DEPTH_SIZE: case EGL_STENCIL_SIZE: case EGL_LUMINANCE_SIZE: case EGL_ALPHA_MASK_SIZE:
    case EGL_SAMPLES: case EGL_SAMPLE_BUFFERS:
        return have >= want;  // at least
    case EGL_SURFACE_TYPE: case EGL_RENDERABLE_TYPE: case EGL_CONFORMANT:
        return (have & want) == want;  // mask
    case EGL_MAX_PBUFFER_WIDTH: case EGL_MAX_PBUFFER_HEIGHT: case EGL_MAX_PBUFFER_PIXELS:
    case EGL_NATIVE_VISUAL_ID:
        return true;  // ignored
    default:
        return have == want;  // exact
    }
}

// ---- thunks

void th_eglGetDisplay(Cpu& c) {
    LOGI("egl", "eglGetDisplay(%#" PRIx64 ") = %p", c.x(0), (void*)&g_display);
    ret_ptr(c, &g_display);
}

void th_eglInitialize(Cpu& c) {
    if ((EGLDisplay)c.x(0) != (EGLDisplay)&g_display) {
        ret(c, fail(EGL_BAD_DISPLAY, EGL_FALSE));
        return;
    }
    g_display.initialized = true;
    // The guest is told EGL 1.4, like the Android 4.x-era EGL the game was written against.
    if (c.x(1)) *(EGLint*)c.x(1) = 1;
    if (c.x(2)) *(EGLint*)c.x(2) = 4;
    LOGI("egl", "eglInitialize: emulated EGL 1.4 over the frontend's GL contexts");
    t_error = EGL_SUCCESS;
    ret(c, EGL_TRUE);
}

void th_eglChooseConfig(Cpu& c) {
    auto* attribs = (const EGLint*)c.x(1);
    auto* out = (EGLConfig*)c.x(2);
    EGLint size = (EGLint)c.x(3);
    auto* num = (EGLint*)c.x(4);
    if (!valid_display((EGLDisplay)c.x(0))) return ret(c, EGL_FALSE);
    if (!num) return ret(c, fail(EGL_BAD_PARAMETER, EGL_FALSE));
    bool match = true;
    for (const EGLint* a = attribs; a && *a != EGL_NONE; a += 2) {
        EGLint dummy;
        if (!config_attrib(a[0], &dummy)) {
            LOGW("egl", "eglChooseConfig: unknown attribute %#x", a[0]);
            return ret(c, fail(EGL_BAD_ATTRIBUTE, EGL_FALSE));
        }
        if (!config_matches(a[0], a[1])) match = false;
    }
    EGLint n = match ? 1 : 0;
    if (out) {
        n = std::min(n, size);
        if (n > 0) out[0] = (EGLConfig)&g_config;
    }
    *num = n;
    LOGI("egl", "eglChooseConfig(%s) = %d config(s)", attribs_str(attribs).c_str(), n);
    t_error = EGL_SUCCESS;
    ret(c, EGL_TRUE);
}

void th_eglGetConfigAttrib(Cpu& c) {
    EGLint attr = (EGLint)c.x(2);
    auto* out = (EGLint*)c.x(3);
    if (!valid_display((EGLDisplay)c.x(0)) || !valid_config((EGLConfig)c.x(1))) return ret(c, EGL_FALSE);
    EGLint v = 0;
    if (!config_attrib(attr, &v)) {
        LOGW("egl", "eglGetConfigAttrib: unknown attribute %#x", attr);
        return ret(c, fail(EGL_BAD_ATTRIBUTE, EGL_FALSE));
    }
    if (out) *out = v;
    LOGI("egl", "eglGetConfigAttrib(%#x) = %d", attr, v);
    t_error = EGL_SUCCESS;
    ret(c, EGL_TRUE);
}

egl_emu::Surface* new_surface(egl_emu::Surface::Kind kind) {
    auto* s = new egl_emu::Surface;
    s->kind = kind;
    s->swap_behavior = EGL_BUFFER_DESTROYED;
    std::lock_guard lk(g_mutex);
    g_surfaces.insert(s);
    return s;
}

void th_eglCreateWindowSurface(Cpu& c) {
    auto* win = (NativeWindow*)c.x(2);
    auto* attribs = (const EGLint*)c.x(3);
    if (!valid_display((EGLDisplay)c.x(0)) || !valid_config((EGLConfig)c.x(1))) return ret_ptr(c, EGL_NO_SURFACE);
    if (win != &native_window()) {
        LOGW("egl", "eglCreateWindowSurface: unknown native window %p", (void*)win);
        return ret_ptr(c, fail(EGL_BAD_NATIVE_WINDOW, EGL_NO_SURFACE));
    }
    if (attribs && *attribs != EGL_NONE) LOGW("egl", "eglCreateWindowSurface: attributes ignored: %s", attribs_str(attribs).c_str());
    egl_emu::Surface* s = new_surface(egl_emu::Surface::Window);
    LOGI("egl", "eglCreateWindowSurface = %p", (void*)s);
    t_error = EGL_SUCCESS;
    ret_ptr(c, s);
}

void th_eglCreatePbufferSurface(Cpu& c) {
    auto* attribs = (const EGLint*)c.x(2);
    if (!valid_display((EGLDisplay)c.x(0)) || !valid_config((EGLConfig)c.x(1))) return ret_ptr(c, EGL_NO_SURFACE);
    int w = 0, h = 0;
    for (const EGLint* a = attribs; a && *a != EGL_NONE; a += 2) {
        if (a[0] == EGL_WIDTH) w = a[1];
        else if (a[0] == EGL_HEIGHT) h = a[1];
        else LOGW("egl", "eglCreatePbufferSurface: attribute %#x=%d ignored", a[0], a[1]);
    }
    if (w < 0 || h < 0) return ret_ptr(c, fail(EGL_BAD_PARAMETER, EGL_NO_SURFACE));
    egl_emu::Surface* s = new_surface(egl_emu::Surface::Pbuffer);
    // A 0x0 pbuffer still gets a 1x1 stand-in framebuffer (an FBO can't be empty).
    s->width = std::max(w, 1);
    s->height = std::max(h, 1);
    LOGI("egl", "eglCreatePbufferSurface(%dx%d) = %p", w, h, (void*)s);
    t_error = EGL_SUCCESS;
    ret_ptr(c, s);
}

// Surfaces are tokens without host storage: a destroyed one is only flagged (and kept, so its
// address is never reused for a later surface the guest could mistake for it). A context that is
// still current on it keeps drawing into its stand-in until it's released, as EGL defers the
// destruction of a current surface.
void th_eglDestroySurface(Cpu& c) {
    if (!valid_display((EGLDisplay)c.x(0))) return ret(c, EGL_FALSE);
    egl_emu::Surface* s = surface((EGLSurface)c.x(1));
    if (!s) return ret(c, EGL_FALSE);
    {
        std::lock_guard lk(g_mutex);
        s->destroyed = true;
    }
    LOGI("egl", "eglDestroySurface(%p)", (void*)s);
    t_error = EGL_SUCCESS;
    ret(c, EGL_TRUE);
}

void th_eglCreateContext(Cpu& c) {
    auto share = (EGLContext)c.x(2);
    auto* attribs = (const EGLint*)c.x(3);
    if (!valid_display((EGLDisplay)c.x(0)) || !valid_config((EGLConfig)c.x(1))) return ret_ptr(c, EGL_NO_CONTEXT);
    if (share != EGL_NO_CONTEXT && !valid_context(share)) return ret_ptr(c, EGL_NO_CONTEXT);
    int major = 1;
    for (const EGLint* a = attribs; a && *a != EGL_NONE; a += 2) {
        if (a[0] == EGL_CONTEXT_CLIENT_VERSION) major = a[1];  // = EGL_CONTEXT_MAJOR_VERSION
        else LOGW("egl", "eglCreateContext: attribute %#x=%d ignored", a[0], a[1]);
    }
    if (major < 2 || major > 3) {
        LOGW("egl", "eglCreateContext: OpenGL ES %d not supported", major);
        return ret_ptr(c, fail(EGL_BAD_MATCH, EGL_NO_CONTEXT));
    }
    void* ctx = g_hooks->create_context((void*)share, major);
    LOGI("egl", "eglCreateContext(share=%p, ES %d) = %p", (void*)share, major, ctx);
    if (!ctx) {
        LOGE("egl", "can't create a host GL context: %s", g_hooks->last_error());
        return ret_ptr(c, fail(EGL_BAD_ALLOC, EGL_NO_CONTEXT));
    }
    {
        std::lock_guard lk(g_mutex);
        g_contexts[ctx] = major;
    }
    t_error = EGL_SUCCESS;
    ret_ptr(c, ctx);
}

// EGL defers destroying a context that is current until it's released; a context the guest
// destroys is current nowhere in practice (CheckGLESVersion releases its context first), and the
// host context is deleted at once.
void th_eglDestroyContext(Cpu& c) {
    auto ctx = (EGLContext)c.x(1);
    if (!valid_display((EGLDisplay)c.x(0)) || !valid_context(ctx)) return ret(c, EGL_FALSE);
    {
        std::lock_guard lk(g_mutex);
        g_contexts.erase((void*)ctx);
    }
    if (t_ctx == (void*)ctx) t_ctx = nullptr, t_draw = nullptr;
    gles::forget_context((void*)ctx);
    g_hooks->destroy_context((void*)ctx);
    LOGI("egl", "eglDestroyContext(%p)", (void*)ctx);
    t_error = EGL_SUCCESS;
    ret(c, EGL_TRUE);
}

void th_eglMakeCurrent(Cpu& c) {
    auto draw = (EGLSurface)c.x(1), read = (EGLSurface)c.x(2);
    auto ctx = (EGLContext)c.x(3);
    if (!valid_display((EGLDisplay)c.x(0))) return ret(c, EGL_FALSE);
    if (ctx == EGL_NO_CONTEXT) {
        if (draw != EGL_NO_SURFACE || read != EGL_NO_SURFACE) return ret(c, fail(EGL_BAD_MATCH, EGL_FALSE));
        if (t_ctx && !g_hooks->make_current(nullptr, false)) {
            LOGE("egl", "eglMakeCurrent(release) failed: %s", g_hooks->last_error());
            return ret(c, fail(EGL_BAD_ACCESS, EGL_FALSE));
        }
        t_ctx = nullptr, t_draw = nullptr;
        t_error = EGL_SUCCESS;
        return ret(c, EGL_TRUE);
    }
    if (!valid_context(ctx)) return ret(c, EGL_FALSE);
    if (draw == EGL_NO_SURFACE || read == EGL_NO_SURFACE) {
        // Surfaceless (EGL_KHR_surfaceless_context): not advertised to the guest, which doesn't use it.
        LOGW("egl", "eglMakeCurrent without a surface");
        return ret(c, fail(EGL_BAD_MATCH, EGL_FALSE));
    }
    egl_emu::Surface* d = surface(draw);
    egl_emu::Surface* r = surface(read);
    if (!d || !r) return ret(c, EGL_FALSE);
    if (d != r) LOGW("egl", "eglMakeCurrent: read surface %p differs from draw surface %p; reads use the draw surface", (void*)r, (void*)d);
    bool window = d->kind == egl_emu::Surface::Window;
    if (!g_hooks->make_current((void*)ctx, window)) {
        LOGE("egl", "eglMakeCurrent(%p, %s) failed: %s", (void*)ctx, window ? "window" : "pbuffer", g_hooks->last_error());
        return ret(c, fail(EGL_BAD_ACCESS, EGL_FALSE));
    }
    t_ctx = (void*)ctx;
    t_draw = d;
    gles::on_make_current();
    t_error = EGL_SUCCESS;
    ret(c, EGL_TRUE);
}

void th_eglGetCurrentContext(Cpu& c) { ret_ptr(c, t_ctx); }

void th_eglQuerySurface(Cpu& c) {
    EGLint attr = (EGLint)c.x(2);
    auto* out = (EGLint*)c.x(3);
    if (!valid_display((EGLDisplay)c.x(0))) return ret(c, EGL_FALSE);
    egl_emu::Surface* s = surface((EGLSurface)c.x(1));
    if (!s) return ret(c, EGL_FALSE);
    bool window = s->kind == egl_emu::Surface::Window;
    auto& w = native_window();
    bool scaled = w.buffer_width > 0 && w.buffer_height > 0;
    EGLint v;
    switch (attr) {
    // The game sees the Android window's size, not the host window's (gles.cpp: default_fbo()).
    case EGL_WIDTH: v = window ? (scaled ? w.buffer_width : w.width) : s->width; break;
    case EGL_HEIGHT: v = window ? (scaled ? w.buffer_height : w.height) : s->height; break;
    case EGL_CONFIG_ID: v = g_config.id; break;
    case EGL_SWAP_BEHAVIOR: v = s->swap_behavior; break;
    case EGL_RENDER_BUFFER: v = EGL_BACK_BUFFER; break;
    case EGL_MULTISAMPLE_RESOLVE: v = EGL_MULTISAMPLE_RESOLVE_DEFAULT; break;
    case EGL_HORIZONTAL_RESOLUTION: case EGL_VERTICAL_RESOLUTION: case EGL_PIXEL_ASPECT_RATIO: v = EGL_UNKNOWN; break;
    case EGL_LARGEST_PBUFFER: case EGL_MIPMAP_TEXTURE: case EGL_MIPMAP_LEVEL: v = 0; break;
    case EGL_TEXTURE_FORMAT: case EGL_TEXTURE_TARGET: v = EGL_NO_TEXTURE; break;
    default:
        LOGW("egl", "eglQuerySurface: unknown attribute %#x", attr);
        return ret(c, fail(EGL_BAD_ATTRIBUTE, EGL_FALSE));
    }
    if (out) *out = v;
    t_error = EGL_SUCCESS;
    ret(c, EGL_TRUE);
}

void th_eglSurfaceAttrib(Cpu& c) {
    EGLint attr = (EGLint)c.x(2), value = (EGLint)c.x(3);
    if (!valid_display((EGLDisplay)c.x(0))) return ret(c, EGL_FALSE);
    egl_emu::Surface* s = surface((EGLSurface)c.x(1));
    if (!s) return ret(c, EGL_FALSE);
    LOGI("egl", "eglSurfaceAttrib(%p, %#x, %#x)", (void*)s, attr, value);
    if (attr == EGL_SWAP_BEHAVIOR) {
        if (value != EGL_BUFFER_DESTROYED && value != EGL_BUFFER_PRESERVED) return ret(c, fail(EGL_BAD_PARAMETER, EGL_FALSE));
        // Preserved isn't in the config's EGL_SURFACE_TYPE; the stand-in framebuffer keeps its
        // contents across swaps either way.
        if (value == EGL_BUFFER_PRESERVED) return ret(c, fail(EGL_BAD_MATCH, EGL_FALSE));
        s->swap_behavior = value;
    } else if (attr != EGL_MIPMAP_LEVEL && attr != EGL_MULTISAMPLE_RESOLVE) {
        return ret(c, fail(EGL_BAD_ATTRIBUTE, EGL_FALSE));
    }
    t_error = EGL_SUCCESS;
    ret(c, EGL_TRUE);
}

void th_eglSwapBuffers(Cpu& c) {
    if (!valid_display((EGLDisplay)c.x(0))) return ret(c, EGL_FALSE);
    egl_emu::Surface* s = surface((EGLSurface)c.x(1));
    if (!s) return ret(c, EGL_FALSE);
    // Swapping a surface that isn't this thread's current draw surface is EGL_BAD_SURFACE.
    if (s != t_draw) return ret(c, fail(EGL_BAD_SURFACE, EGL_FALSE));
    t_error = EGL_SUCCESS;
    if (s->kind != egl_emu::Surface::Window) return ret(c, EGL_TRUE);  // a pbuffer: no-op
    g_last_present_ns.store(steady_ns(), std::memory_order_relaxed);
    if (!gles::present_and_swap()) {
        static std::atomic<int> logged{0};
        if (logged.fetch_add(1) < 4) LOGW("egl", "swap failed: %s", g_hooks->last_error());
        return ret(c, fail(EGL_BAD_SURFACE, EGL_FALSE));
    }
    ret(c, EGL_TRUE);
}

void th_eglSwapInterval(Cpu& c) {
    EGLint interval = (EGLint)c.x(1);
    if (!valid_display((EGLDisplay)c.x(0))) return ret(c, EGL_FALSE);
    if (!t_ctx) return ret(c, fail(EGL_BAD_CONTEXT, EGL_FALSE));
    if (!t_draw) return ret(c, fail(EGL_BAD_SURFACE, EGL_FALSE));
    // Only the window has a swap chain; the interval belongs to the host window's surface.
    if (t_draw->kind == egl_emu::Surface::Window && !g_hooks->set_swap_interval(std::clamp(interval, 0, 1))) {
        static std::atomic<int> logged{0};
        if (logged.fetch_add(1) < 4) LOGW("egl", "eglSwapInterval(%d): %s", interval, g_hooks->last_error());
    }
    t_error = EGL_SUCCESS;
    ret(c, EGL_TRUE);
}

void th_eglGetError(Cpu& c) {
    EGLint e = t_error;
    t_error = EGL_SUCCESS;
    ret(c, e);
}

void th_eglGetProcAddress(Cpu& c) {
    const char* n = arg_str(c, 0);
    u64 a = Hle::get().lookup(n);
    LOGD("egl", "eglGetProcAddress(%s) = %#" PRIx64, n, a);
    ret(c, a);
}

}  // namespace

namespace egl_emu {
void* current_context() { return t_ctx; }
Surface* current_draw() { return t_ctx ? t_draw : nullptr; }
GfxHooks* hooks() { return g_hooks; }
}  // namespace egl_emu

void set_gfx_hooks(GfxHooks* h) { g_hooks = h; }


bool present_again() {
    if (!window_current()) return false;
    g_last_present_ns.store(steady_ns(), std::memory_order_relaxed);
    return gles::present_and_swap();
}

void set_idle_present(bool on) { g_idle_present.store(on, std::memory_order_relaxed); }

bool idle_present_on() { return g_idle_present.load(std::memory_order_relaxed); }

bool window_thread() { return window_current(); }

void idle_present() {
    if (steady_ns() - g_last_present_ns.load(std::memory_order_relaxed) < (s64)kIdlePresentMs * 1000000) return;
    present_again();
}

void register_egl(Hle& h) {
    h.fn("eglGetDisplay", th_eglGetDisplay);
    h.fn("eglInitialize", th_eglInitialize);
    h.fn("eglChooseConfig", th_eglChooseConfig);
    h.fn("eglGetConfigAttrib", th_eglGetConfigAttrib);
    h.fn("eglCreateWindowSurface", th_eglCreateWindowSurface);
    h.fn("eglCreatePbufferSurface", th_eglCreatePbufferSurface);
    h.fn("eglDestroySurface", th_eglDestroySurface);
    h.fn("eglCreateContext", th_eglCreateContext);
    h.fn("eglDestroyContext", th_eglDestroyContext);
    h.fn("eglMakeCurrent", th_eglMakeCurrent);
    h.fn("eglGetCurrentContext", th_eglGetCurrentContext);
    h.fn("eglQuerySurface", th_eglQuerySurface);
    h.fn("eglSurfaceAttrib", th_eglSurfaceAttrib);
    h.fn("eglSwapBuffers", th_eglSwapBuffers);
    h.fn("eglSwapInterval", th_eglSwapInterval);
    h.fn("eglGetError", th_eglGetError);
    h.fn("eglGetProcAddress", th_eglGetProcAddress);
}

}  // namespace soa
