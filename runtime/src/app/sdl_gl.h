#pragma once
// The host GL contexts behind the guest's EGL (hle/gfx.h, GfxHooks): OpenGL ES contexts that SDL2
// creates for its window, on whatever video driver SDL picked (X11 through EGL, or Wayland).
//
// SDL ties context creation to a window surface: SDL_GL_CreateContext makes the new context current
// on the calling thread, on the window it's given, and SDL_GL_SHARE_WITH_CURRENT_CONTEXT shares with
// whatever is current on that thread. The guest's eglCreateContext does neither, and its share
// context may be current on another thread. So contexts are created on a private hidden 1x1 window
// (never the game window, which the render thread may hold), and each share group has an anchor
// context that only the creation code (under a mutex) ever makes current: a new context is created
// while its group's anchor is current. The calling thread's previous binding is restored afterwards.
#include <SDL.h>

namespace soa::app::sdlgl {

// After SDL_Init, before SDL_CreateWindow: the GL attributes and hints the window is created with
// (SDL_WINDOW_OPENGL picks the window's EGL config at creation): OpenGL ES 3.0, RGB8 without alpha,
// depth or stencil (the game renders into framebuffer objects, hle/gles.cpp; the window only
// receives the scaled blit), and EGL rather than GLX under X11.
void set_attributes();

// After the game window exists (main thread): creates the private hidden windows (context creation;
// the per-thread surfaces of contexts bound to a guest pbuffer, sdl_gl.cpp).
void init(SDL_Window* window);

void* create_context(void* share, int es_major);
void destroy_context(void* ctx);
bool make_current(void* ctx, bool window);
bool swap_window();
bool set_swap_interval(int interval);
void drawable_size(int* w, int* h);

}  // namespace soa::app::sdlgl
