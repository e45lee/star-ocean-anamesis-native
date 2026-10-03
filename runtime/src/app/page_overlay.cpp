// A host-drawn image over the game (page_overlay.h). The GL side is the Dragalia Lost project's
// web view blit (platformdl/src/webview_dl.cpp webview_draw_overlay): a texture behind a read
// framebuffer, blitted into the window's framebuffer, with the bindings it touches restored.
#include "app/page_overlay.h"

#include <GLES3/gl3.h>

#include <algorithm>
#include <cmath>
#include <mutex>

namespace soa::app::page_overlay {
namespace {

std::mutex g_m;
bool g_visible = false;
int g_x = 0, g_y = 0, g_sw = 0, g_sh = 0;  // the game-screen rectangle
int g_w = 0, g_h = 0;                      // the picture
std::vector<uint8_t> g_rgba;
bool g_new = false;  // a picture the render thread hasn't uploaded
InputHandler g_input;
bool g_captured = false;  // a gesture that started inside is in progress

// render thread only
GLuint g_tex = 0, g_fbo = 0;
int g_tex_w = 0, g_tex_h = 0;

bool inside(float x, float y) { return g_visible && x >= g_x && x < g_x + g_sw && y >= g_y && y < g_y + g_sh; }

}  // namespace

void show(int x, int y, int w_screen, int h_screen, int w, int h, std::vector<uint8_t> rgba) {
    std::lock_guard lk(g_m);
    g_x = x, g_y = y, g_sw = w_screen, g_sh = h_screen, g_w = w, g_h = h;
    g_rgba = std::move(rgba);
    g_new = true;
    g_visible = w > 0 && h > 0 && (size_t)w * h * 4 <= g_rgba.size();
}

void hide() {
    std::lock_guard lk(g_m);
    g_visible = false;
    g_captured = false;
}

bool visible() {
    std::lock_guard lk(g_m);
    return g_visible;
}

void set_input_handler(InputHandler h) {
    std::lock_guard lk(g_m);
    g_input = std::move(h);
}

bool touch(int action, float x, float y) {
    InputHandler h;
    float rx, ry;
    {
        std::lock_guard lk(g_m);
        if (action == 0) g_captured = inside(x, y);
        if (!g_captured) return false;
        if (action == 1 || action == 3) g_captured = false;
        h = g_input;
        rx = x - g_x, ry = y - g_y;
    }
    if (h) h(action == 3 ? 1 : action, rx, ry, 0);
    return true;
}

bool wheel(float x, float y, float dy) {
    InputHandler h;
    float rx, ry;
    {
        std::lock_guard lk(g_m);
        if (!inside(x, y)) return false;
        h = g_input;
        rx = x - g_x, ry = y - g_y;
    }
    if (h) h(3, rx, ry, dy);
    return true;
}

void draw(unsigned target_fbo, int vx, int vy, int vw, int vh, int W, int H) {
    std::lock_guard lk(g_m);
    if (!g_visible || W <= 0 || H <= 0 || vw <= 0 || vh <= 0) return;
    GLint prev_tex, prev_unpack, prev_align, prev_row, prev_read, prev_draw;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &prev_tex);
    glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &prev_unpack);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &prev_align);
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &prev_row);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &prev_read);
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prev_draw);
    if (!g_tex) {
        glGenTextures(1, &g_tex);
        glGenFramebuffers(1, &g_fbo);
    }
    glBindTexture(GL_TEXTURE_2D, g_tex);
    if (g_new) {
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        if (g_tex_w != g_w || g_tex_h != g_h) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, g_w, g_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            g_tex_w = g_w, g_tex_h = g_h;
        }
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_w, g_h, GL_RGBA, GL_UNSIGNED_BYTE, g_rgba.data());
        g_new = false;
    }
    glBindFramebuffer(GL_READ_FRAMEBUFFER, g_fbo);
    glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_tex, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target_fbo);
    // game-screen pixels -> the letterboxed viewport (GL: y from the bottom); the rows are top-down,
    // so the destination's y range is flipped
    int dx0 = vx + (int)std::lround((double)g_x * vw / W), dx1 = vx + (int)std::lround((double)(g_x + g_sw) * vw / W);
    int dtop = vy + vh - (int)std::lround((double)g_y * vh / H), dbot = vy + vh - (int)std::lround((double)(g_y + g_sh) * vh / H);
    glBlitFramebuffer(0, 0, g_tex_w, g_tex_h, dx0, dtop, dx1, dbot, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, prev_read);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, prev_draw);
    glBindTexture(GL_TEXTURE_2D, prev_tex);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, prev_unpack);
    glPixelStorei(GL_UNPACK_ALIGNMENT, prev_align);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, prev_row);
}

}  // namespace soa::app::page_overlay
