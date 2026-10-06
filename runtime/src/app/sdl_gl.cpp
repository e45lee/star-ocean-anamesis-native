// The host GL contexts behind the guest's EGL (app/sdl_gl.h).
#include "app/sdl_gl.h"
#include "core/thread_record.h"

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#ifdef _WIN32
#include <windows.h>
#endif

#include <atomic>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/log.h"
#include "hle/gl_host.h"

namespace soa::app::sdlgl {

namespace {

SDL_Window* g_window = nullptr;
SDL_Window* g_creator = nullptr;  // the private hidden window contexts are created on

// The surfaces of contexts bound to a guest pbuffer: one hidden 1x1 window per thread that binds
// one, taken from a pool made at start-up on the main thread (SDL wants windows made there).
// SDL2's Wayland backend has no surfaceless binding (SDL_GL_MakeCurrent(NULL, ctx) releases the
// context there), and an EGL surface can be current on one thread only, so each thread gets its
// own. The guest's framebuffer 0 on a pbuffer is a stand-in FBO anyway (hle/gles.cpp), so the
// window's own buffers are never drawn to. A thread gives its window back when it exits.
constexpr int kPbufferWindows = 8;
std::mutex g_pool_m;
std::vector<SDL_Window*> g_pool;  // free windows
struct ThreadWindow {
    SDL_Window* win = nullptr;
    ~ThreadWindow() {
        if (!win) return;
        if (SDL_GL_GetCurrentWindow() == win) SDL_GL_MakeCurrent(nullptr, nullptr);
        std::lock_guard lk(g_pool_m);
        g_pool.push_back(win);
    }
};

// This thread's pbuffer window, or null (the pool is empty: then the context is bound without a
// surface, which SDL's X11 backend supports and its Wayland backend doesn't).
SDL_Window* thread_window() {
    ThreadWindow& t_window = thread_object<ThreadWindow>();  // (given back at the thread's end: core/thread_record.h)
    if (t_window.win) return t_window.win;
    std::lock_guard lk(g_pool_m);
    if (g_pool.empty()) {
        static std::atomic<bool> warned{false};
        if (!warned.exchange(true)) LOGW("gl", "more than %d threads bind a pbuffer: binding without a surface", kPbufferWindows);
        return nullptr;
    }
    t_window.win = g_pool.back();
    g_pool.pop_back();
    return t_window.win;
}

// A share group: the anchor context, and how many guest contexts are in the group.
struct Group {
    SDL_GLContext anchor = nullptr;
    int members = 0;
};
std::mutex g_create_m;  // creation and deletion; the anchors and g_creator's surface are current only under it
std::unordered_map<void*, Group*> g_group_of;  // guest-visible context -> its group

// Logged once, on the first context bound to the window: the window's framebuffer, whether SDL's
// context is an EGL context of the libEGL the runtime's GL entry points come from (libEGL's
// eglGetProcAddress, hle/gles.cpp: then libEGL's current context is SDL's; under GLX it would be
// none), and whether SDL resolves the same entry points.
void check_window_context() {
    static std::atomic<bool> done{false};
    if (done.exchange(true)) return;
    GLint samples = 0, r = 0, g = 0, b = 0, a = 0;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &samples);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_BACK, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, &r);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_BACK, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, &g);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_BACK, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, &b);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_BACK, GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, &a);
    void* sdl_clear = SDL_GL_GetProcAddress("glClear");
    bool egl = eglGetCurrentContext() == (EGLContext)SDL_GL_GetCurrentContext();
    LOGI("gl", "window framebuffer: RGBA %d%d%d%d, %d sample buffer(s); %s, %s; SDL's context %s libEGL's, glClear %s SDL's", r,
         g, b, a, samples, (const char*)glGetString(GL_VERSION), (const char*)glGetString(GL_RENDERER), egl ? "is" : "is NOT",
         sdl_clear == (void*)glh::glClear ? "is" : "is NOT");
    if (samples) LOGW("gl", "the window is multisampled: the scaled glBlitFramebuffer to it will fail");
    if (!egl) LOGW("gl", "SDL's GL context isn't an EGL context of the runtime's libEGL");
}

// Binds `ctx` on `win` (null: no surface) on this thread.
bool bind(SDL_Window* win, SDL_GLContext ctx) { return SDL_GL_MakeCurrent(win, ctx) == 0; }

}  // namespace

void set_attributes() {
    // SDL's X11 backend creates OpenGL ES contexts through GLX by default; through EGL they are
    // the same Mesa EGL contexts the runtime's GL entry points (libEGL, hle/gles.cpp) dispatch to,
    // as before SDL owned them. Wayland always uses EGL.
    SDL_SetHint(SDL_HINT_VIDEO_X11_FORCE_EGL, "1");
#ifdef _WIN32
    // Windows: OpenGL ES through EGL (not WGL), from the ANGLE linked into this program. SDL loads
    // its EGL and GLES libraries by path: the program itself, which exports ANGLE's EGL entry
    // points (app/egl_exports_win32.def); GL functions come from its eglGetProcAddress. So SDL's
    // contexts are the contexts of the ANGLE the runtime's GL entry points dispatch to.
    SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
    char exe[MAX_PATH];
    if (GetModuleFileNameA(nullptr, exe, sizeof exe)) {
        SDL_setenv("SDL_VIDEO_EGL_DRIVER", exe, 1);
        SDL_setenv("SDL_VIDEO_GL_DRIVER", exe, 1);
    }
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    // No alpha: a window with an alpha channel can be shown translucent by a compositor.
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
}

void init(SDL_Window* window) {
    g_window = window;
    g_creator = SDL_CreateWindow("soa-gl", 0, 0, 1, 1, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
    if (!g_creator) LOGE("gl", "can't create the context-creation window: %s", SDL_GetError());
    for (int i = 0; i < kPbufferWindows; i++)
        if (SDL_Window* w = SDL_CreateWindow("soa-gl-pbuffer", 0, 0, 1, 1, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN)) g_pool.push_back(w);
}

void* create_context(void* share, int es_major) {
    std::lock_guard lk(g_create_m);
    if (!g_creator) return nullptr;
    SDL_Window* prev_win = SDL_GL_GetCurrentWindow();
    SDL_GLContext prev_ctx = SDL_GL_GetCurrentContext();
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, es_major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    Group* g = nullptr;
    bool new_group = false;
    if (share) {
        auto it = g_group_of.find(share);
        if (it == g_group_of.end()) {
            SDL_SetError("unknown share context %p", share);
            return nullptr;
        }
        g = it->second;
    } else {
        SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
        SDL_GLContext anchor = SDL_GL_CreateContext(g_creator);  // current on g_creator now
        if (!anchor) {
            bind(prev_win, prev_ctx);
            return nullptr;
        }
        g = new Group{anchor, 0};
        new_group = true;
    }
    SDL_GLContext ctx = nullptr;
    if (bind(g_creator, g->anchor)) {
        SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
        ctx = SDL_GL_CreateContext(g_creator);
        SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
    }
    std::string err = ctx ? "" : SDL_GetError();
    bind(prev_win, prev_ctx);
    if (!ctx) {
        if (new_group) {
            SDL_GL_DeleteContext(g->anchor);
            delete g;
        }
        SDL_SetError("%s", err.c_str());
        return nullptr;
    }
    g->members++;
    g_group_of[ctx] = g;
    return ctx;
}

void destroy_context(void* ctx) {
    std::lock_guard lk(g_create_m);
    SDL_GL_DeleteContext((SDL_GLContext)ctx);  // releases it first if it is current on this thread
    auto it = g_group_of.find(ctx);
    if (it == g_group_of.end()) return;
    Group* g = it->second;
    g_group_of.erase(it);
    if (--g->members == 0) {
        SDL_GL_DeleteContext(g->anchor);
        delete g;
    }
}

bool make_current(void* ctx, bool window) {
    if (!ctx) return bind(nullptr, nullptr);
    if (!bind(window ? g_window : thread_window(), (SDL_GLContext)ctx)) return false;
    if (window) check_window_context();
    return true;
}

bool swap_window() {
    SDL_GL_SwapWindow(g_window);
    return true;
}

bool set_swap_interval(int interval) { return SDL_GL_SetSwapInterval(interval) == 0; }

void drawable_size(int* w, int* h) { SDL_GL_GetDrawableSize(g_window, w, h); }

}  // namespace soa::app::sdlgl
