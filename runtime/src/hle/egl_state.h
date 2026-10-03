#pragma once
// Shared between the guest's EGL (egl.cpp) and GLES (gles.cpp): the emulated surfaces and what is
// current on each thread, and the default-framebuffer emulation that renders the guest's surfaces
// into framebuffer objects.

namespace soa {
struct GfxHooks;

namespace egl_emu {

// An EGLSurface handed to the guest. Neither kind has host storage of its own: framebuffer 0 of a
// context bound to one is an FBO (gles.cpp: default_fbo()). The window surface's size is the
// Android window's (native_window(), ANativeWindow_setBuffersGeometry); a pbuffer's is its own.
struct Surface {
    enum Kind { Window, Pbuffer } kind = Window;
    int width = 0, height = 0;  // pbuffers only
    int swap_behavior = 0;      // EGL_SWAP_BEHAVIOR (eglSurfaceAttrib)
    bool destroyed = false;
};

// This thread's current context (a host handle from GfxHooks::create_context) and draw surface.
void* current_context();
Surface* current_draw();

GfxHooks* hooks();

}  // namespace egl_emu

// gles.cpp: the default-framebuffer emulation, for egl.cpp.
namespace gles {
// After eglMakeCurrent: rebinds framebuffer 0 (or a stand-in for the previous surface) to the stand-in
// for the new draw surface.
void on_make_current();
// eglSwapBuffers on the window surface: blits the window stand-in (letterboxed) to the window,
// draws the frontend's overlay, swaps, and rebinds the stand-in.
bool present_and_swap();
// eglDestroyContext: forgets the context's stand-ins (they die with the context).
void forget_context(void* ctx);
}  // namespace gles

}  // namespace soa
