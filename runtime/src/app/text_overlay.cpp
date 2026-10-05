// The on-screen text box of the emulated KeyboardActivity (app/text_overlay.h).
#include "app/text_overlay.h"

#include <GLES3/gl3.h>
#include <SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "android/platform.h"
#include "core/log.h"
#include "frontend/text_entry.h"
#include "soa/fonts.h"

namespace soa::app::text_overlay {

namespace te = soa::text_entry;
using u8 = std::uint8_t;
using s64 = std::int64_t;

namespace {

// ---------------------------------------------------------------------------
// Look

struct Color {
    int r, g, b, a;  // straight alpha, 0-255
};
constexpr Color kPanel{8, 12, 20, 200};
constexpr Color kField{24, 32, 44, 235};
constexpr Color kFieldBorder{70, 160, 230, 255};
constexpr Color kText{255, 255, 255, 255};
constexpr Color kHint{175, 185, 200, 255};
constexpr Color kCounterFull{255, 170, 60, 255};
constexpr Color kComposition{255, 228, 140, 255};
constexpr Color kCaret{255, 255, 255, 255};
constexpr long kBlinkMs = 530;  // the caret's on/off time (solid for one period after each edit)

s64 now_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

// ---------------------------------------------------------------------------
// Font (render thread only: FreeType objects aren't thread-safe)

struct Glyph {
    std::vector<u8> bmp;  // 8-bit coverage, w x h
    int w = 0, h = 0, left = 0, top = 0, advance = 0;
};

struct Font {
    bool tried = false;
    FT_Library lib = nullptr;
    // The main face (the built-in Noto Sans JP), then any fallbacks for the code points it lacks
    // (none today). Metrics come from the main face.
    std::vector<FT_Face> faces;
    std::vector<int> sizes;  // the pixel size set on each face
    std::map<std::pair<int, char32_t>, Glyph> cache;
    int size = 0;  // the size ascender() / descender() refer to

    bool ok() const { return !faces.empty(); }

    void set_size(int px) {
        size = px;
        size_on(0, px);
    }
    void size_on(size_t i, int px) {
        if (sizes[i] == px) return;
        FT_Set_Pixel_Sizes(faces[i], 0, px);
        sizes[i] = px;
    }
    // Ascender / descender (positive, pixels) of the main face at the current size.
    int ascender() const { return (int)(faces[0]->size->metrics.ascender >> 6); }
    int descender() const { return (int)(-faces[0]->size->metrics.descender >> 6); }

    const Glyph& glyph(int px, char32_t cp) {
        auto key = std::make_pair(px, cp);
        auto it = cache.find(key);
        if (it != cache.end()) return it->second;
        // the first face that has the code point; none: the main face's .notdef (index 0)
        size_t fi = 0;
        for (size_t i = 0; i < faces.size(); i++)
            if (FT_Get_Char_Index(faces[i], cp) != 0) {
                fi = i;
                break;
            }
        size_on(fi, px);
        Glyph g;
        if (FT_Load_Char(faces[fi], cp, FT_LOAD_RENDER) == 0) {
            FT_GlyphSlot s = faces[fi]->glyph;
            g.w = (int)s->bitmap.width, g.h = (int)s->bitmap.rows;
            g.left = s->bitmap_left, g.top = s->bitmap_top;
            g.advance = (int)(s->advance.x >> 6);
            if (s->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY && g.w > 0 && g.h > 0) {
                g.bmp.resize((size_t)g.w * g.h);
                for (int y = 0; y < g.h; y++) memcpy(&g.bmp[(size_t)y * g.w], s->bitmap.buffer + (ptrdiff_t)y * s->bitmap.pitch, g.w);
            } else {
                g.w = g.h = 0;
            }
        }
        if (cache.size() > 4096) cache.clear();
        return cache.emplace(key, std::move(g)).first->second;
    }

    bool add_face(const fonts::Data& d) {
        FT_Face f = nullptr;
        if (FT_New_Memory_Face(lib, d.bytes, (FT_Long)d.size, 0, &f) != 0) return false;
        faces.push_back(f);
        sizes.push_back(0);
        return true;
    }
};
Font g_font;

void init_font() {
    if (g_font.tried) return;
    g_font.tried = true;
    fonts::Data font = fonts::regular();
    if (FT_Init_FreeType(&g_font.lib) != 0 || !g_font.add_face(font)) {
        LOGW("text", "can't load the built-in font %s, the keyboard shows in the title bar only", font.name);
        if (g_font.lib) FT_Done_FreeType(g_font.lib);
        g_font.lib = nullptr;
        return;
    }
    LOGI("text", "text box font: %s (built in, %zu bytes)", font.name, font.size);
}

// ---------------------------------------------------------------------------
// The CPU canvas: premultiplied RGBA, row 0 at the top

struct Canvas {
    int w = 0, h = 0;
    std::vector<u8> px;

    void reset(int nw, int nh) {
        w = nw, h = nh;
        px.assign((size_t)w * h * 4, 0);
    }
    // Source-over of `c` with extra coverage `cov` (0-255) at (x, y).
    void blend(int x, int y, const Color& c, int cov) {
        if (x < 0 || y < 0 || x >= w || y >= h) return;
        int a = c.a * cov / 255;
        if (a <= 0) return;
        u8* d = &px[((size_t)y * w + x) * 4];
        int inv = 255 - a;
        d[0] = (u8)((c.r * a + d[0] * inv + 127) / 255);
        d[1] = (u8)((c.g * a + d[1] * inv + 127) / 255);
        d[2] = (u8)((c.b * a + d[2] * inv + 127) / 255);
        d[3] = (u8)(a + (d[3] * inv + 127) / 255);
    }
    void fill(const Rect& r, const Color& c) {
        for (int y = std::max(0, r.y); y < std::min(h, r.y + r.h); y++)
            for (int x = std::max(0, r.x); x < std::min(w, r.x + r.w); x++) blend(x, y, c, 255);
    }
    void frame(const Rect& r, int t, const Color& c) {
        fill({r.x, r.y, r.w, t}, c);
        fill({r.x, r.y + r.h - t, r.w, t}, c);
        fill({r.x, r.y + t, t, r.h - 2 * t}, c);
        fill({r.x + r.w - t, r.y + t, t, r.h - 2 * t}, c);
    }
};

int text_width(int px, std::string_view s) {
    int w = 0;
    for (size_t i = 0; i < s.size();) w += g_font.glyph(px, te::decode(s, i)).advance;
    return w;
}

// Draws `s` with its pen starting at x, baseline y, clipped to `clip`; returns the end x.
int draw_text(Canvas& cv, int px, int x, int y, std::string_view s, const Color& c, const Rect& clip) {
    for (size_t i = 0; i < s.size();) {
        const Glyph& g = g_font.glyph(px, te::decode(s, i));
        for (int gy = 0; gy < g.h; gy++) {
            int yy = y - g.top + gy;
            if (yy < clip.y || yy >= clip.y + clip.h) continue;
            for (int gx = 0; gx < g.w; gx++) {
                int xx = x + g.left + gx;
                if (xx < clip.x || xx >= clip.x + clip.w) continue;
                if (int cov = g.bmp[(size_t)gy * g.w + gx]) cv.blend(xx, yy, c, cov);
            }
        }
        x += g.advance;
    }
    return x;
}

// What the panel shows; the image is redrawn when this changes.
struct View {
    std::string text, comp;
    size_t cursor = 0, comp_cursor = 0;
    int max_len = 0;
    bool numeric = false;
    bool caret_on = true;
    int w = 0, h = 0, font_px = 0;
    bool operator==(const View&) const = default;
};

Canvas g_canvas;
View g_drawn;
bool g_have_drawn = false;
unsigned g_canvas_gen = 0;  // bumped on each redraw (the textures upload when stale)
unsigned g_seen_serial = ~0u;
s64 g_last_edit_ms = 0;

// Composes the panel for `v` at layout `L` (panel-relative coordinates).
void compose(const View& v, const Layout& L) {
    Canvas& cv = g_canvas;
    cv.reset(L.panel.w, L.panel.h);
    cv.fill({0, 0, cv.w, cv.h}, kPanel);
    cv.fill({0, 0, cv.w, std::max(1, L.font_px / 20)}, kFieldBorder);  // a top edge
    const int pad = std::max(4, L.font_px / 2);
    Rect field{L.field.x - L.panel.x, L.field.y - L.panel.y, L.field.w, L.field.h};
    Rect all{0, 0, cv.w, cv.h};

    // row 1: the hint and the counter
    g_font.set_size(L.small_px);
    int row1_h = L.small_px * 3 / 2;
    int base1 = pad + (row1_h - (g_font.ascender() + g_font.descender())) / 2 + g_font.ascender();
    std::string hint = v.numeric ? "Enter: OK   Esc: Cancel   Numbers only" : "Enter: OK   Esc: Cancel";
    draw_text(cv, L.small_px, field.x, base1, hint, kHint, all);
    size_t n = te::utf8_len(v.text);
    std::string counter = v.max_len > 0 ? std::to_string(n) + "/" + std::to_string(v.max_len) : std::to_string(n);
    bool full = v.max_len > 0 && n >= (size_t)v.max_len;
    draw_text(cv, L.small_px, field.x + field.w - text_width(L.small_px, counter), base1, counter, full ? kCounterFull : kHint, all);

    // row 2: the field
    int border = std::max(1, L.font_px / 22);
    cv.fill(field, kField);
    cv.frame(field, border, kFieldBorder);
    Rect inner{field.x + pad / 2, field.y + border, field.w - pad, field.h - 2 * border};
    g_font.set_size(L.font_px);
    int asc = g_font.ascender(), desc = g_font.descender();
    int base2 = field.y + (field.h - (asc + desc)) / 2 + asc;
    std::string_view text = v.text, before = text.substr(0, v.cursor), after = text.substr(v.cursor);
    int caret_w = std::max(2, L.font_px / 20);
    int w_before = text_width(L.font_px, before), w_comp = text_width(L.font_px, v.comp);
    int caret_x = w_before + text_width(L.font_px, std::string_view(v.comp).substr(0, v.comp_cursor));
    int scroll = std::max(0, caret_x + caret_w - inner.w);
    int x = inner.x - scroll;
    x = draw_text(cv, L.font_px, x, base2, before, kText, inner);
    if (!v.comp.empty()) {
        int x0 = x;
        x = draw_text(cv, L.font_px, x, base2, v.comp, kComposition, inner);
        int ul = std::max(1, L.font_px / 24);
        Rect u{std::max(x0, inner.x), base2 + std::max(2, desc / 2), std::min(x, inner.x + inner.w) - std::max(x0, inner.x), ul};
        if (u.w > 0) cv.fill(u, kComposition);
        (void)w_comp;
    }
    draw_text(cv, L.font_px, x, base2, after, kText, inner);
    if (v.caret_on) {
        int cx = inner.x - scroll + caret_x;
        cv.fill({cx, base2 - asc, caret_w, asc + desc}, kCaret);
    }
}

// ---------------------------------------------------------------------------
// GL: one texture and one quad on the presenting context

const char* kVs = R"(#version 300 es
uniform vec4 u_rect;  // x0, y0, x1, y1 in NDC
out vec2 v_uv;
void main() {
    vec2 c = vec2(float(gl_VertexID & 1), float(gl_VertexID >> 1));
    v_uv = vec2(c.x, 1.0 - c.y);  // the image's row 0 is its top
    gl_Position = vec4(mix(u_rect.xy, u_rect.zw, c), 0.0, 1.0);
}
)";
const char* kFs = R"(#version 300 es
precision mediump float;
uniform sampler2D u_tex;
in vec2 v_uv;
out vec4 o;
void main() { o = texture(u_tex, v_uv); }
)";

struct GlRes {
    bool failed = false;
    GLuint prog = 0, vao = 0, tex = 0;
    GLint u_rect = -1, u_tex = -1;
    int tex_w = 0, tex_h = 0;
    unsigned gen = ~0u;  // the canvas generation in the texture
};
std::unordered_map<void*, GlRes> g_res;  // by context: VAOs aren't shared between contexts

GLuint compile(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512] = {};
        glGetShaderInfoLog(s, sizeof log, nullptr, log);
        LOGW("text", "text box shader: %s", log);
        glDeleteShader(s);
        return 0;
    }
    return s;
}

bool setup(GlRes& r) {
    if (r.prog || r.failed) return !r.failed;
    GLuint vs = compile(GL_VERTEX_SHADER, kVs), fs = compile(GL_FRAGMENT_SHADER, kFs);
    if (vs && fs) {
        r.prog = glCreateProgram();
        glAttachShader(r.prog, vs);
        glAttachShader(r.prog, fs);
        glLinkProgram(r.prog);
        GLint ok = 0;
        glGetProgramiv(r.prog, GL_LINK_STATUS, &ok);
        if (!ok) glDeleteProgram(r.prog), r.prog = 0;
    }
    if (vs) glDeleteShader(vs);
    if (fs) glDeleteShader(fs);
    if (!r.prog) {
        LOGW("text", "the text box's GL program failed; the keyboard shows in the title bar only");
        r.failed = true;
        return false;
    }
    r.u_rect = glGetUniformLocation(r.prog, "u_rect");
    r.u_tex = glGetUniformLocation(r.prog, "u_tex");
    glGenVertexArrays(1, &r.vao);
    glGenTextures(1, &r.tex);
    return true;
}

// Draws g_canvas at `panel` (drawable pixels, top-left origin) into `fbo`, saving and restoring
// the GL state it changes. (present_scaled already restores the scissor, rasterizer discard,
// colour mask and framebuffer bindings, but this keeps to itself anyway.)
void draw_gl(int ww, int wh, unsigned fbo, const Rect& panel) {
    GlRes& r = g_res[SDL_GL_GetCurrentContext()];
    GLint prog, vao, active, tex, sampler, draw_fb, unpack_buf, ua, url, usr, usp, vp[4];
    GLint bsrc_rgb, bdst_rgb, bsrc_a, bdst_a, beq_rgb, beq_a;
    glGetIntegerv(GL_CURRENT_PROGRAM, &prog);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
    glGetIntegerv(GL_ACTIVE_TEXTURE, &active);
    glActiveTexture(GL_TEXTURE0);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex);
    glGetIntegerv(GL_SAMPLER_BINDING, &sampler);
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &draw_fb);
    glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &unpack_buf);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &ua);
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &url);
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, &usr);
    glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &usp);
    glGetIntegerv(GL_VIEWPORT, vp);
    glGetIntegerv(GL_BLEND_SRC_RGB, &bsrc_rgb);
    glGetIntegerv(GL_BLEND_DST_RGB, &bdst_rgb);
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &bsrc_a);
    glGetIntegerv(GL_BLEND_DST_ALPHA, &bdst_a);
    glGetIntegerv(GL_BLEND_EQUATION_RGB, &beq_rgb);
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &beq_a);
    const GLenum caps[] = {GL_BLEND, GL_DEPTH_TEST, GL_STENCIL_TEST, GL_CULL_FACE, GL_SAMPLE_ALPHA_TO_COVERAGE, GL_SAMPLE_COVERAGE, GL_SCISSOR_TEST};
    GLboolean was[std::size(caps)];
    for (size_t i = 0; i < std::size(caps); i++) was[i] = glIsEnabled(caps[i]);

    if (setup(r)) {
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glBindSampler(0, 0);
        glBindTexture(GL_TEXTURE_2D, r.tex);
        if (r.tex_w != g_canvas.w || r.tex_h != g_canvas.h) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_canvas.w, g_canvas.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, g_canvas.px.data());
            r.tex_w = g_canvas.w, r.tex_h = g_canvas.h;
        } else if (r.gen != g_canvas_gen) {
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_canvas.w, g_canvas.h, GL_RGBA, GL_UNSIGNED_BYTE, g_canvas.px.data());
        }
        r.gen = g_canvas_gen;
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
        glViewport(0, 0, ww, wh);
        for (GLenum c : caps) glDisable(c);
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  // premultiplied
        glUseProgram(r.prog);
        glBindVertexArray(r.vao);
        float x0 = 2.0f * panel.x / ww - 1, x1 = 2.0f * (panel.x + panel.w) / ww - 1;
        float y0 = 2.0f * (wh - panel.y - panel.h) / wh - 1, y1 = 2.0f * (wh - panel.y) / wh - 1;
        glUniform4f(r.u_rect, x0, y0, x1, y1);
        glUniform1i(r.u_tex, 0);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    glBindVertexArray(vao);
    glUseProgram(prog);
    for (size_t i = 0; i < std::size(caps); i++) (was[i] ? glEnable : glDisable)(caps[i]);
    glBlendEquationSeparate(beq_rgb, beq_a);
    glBlendFuncSeparate(bsrc_rgb, bdst_rgb, bsrc_a, bdst_a);
    glViewport(vp[0], vp[1], vp[2], vp[3]);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_fb);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ua);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, url);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, usr);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, usp);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, unpack_buf);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBindSampler(0, sampler);
    glActiveTexture(active);
}

}  // namespace

Layout layout(int vx, int vy, int vw, int vh, int dh) {
    Layout L;
    int top = dh - (vy + vh);
    L.font_px = std::max(12, (vh + 15) / 30);
    L.small_px = std::max(10, L.font_px * 55 / 100);
    int pad = std::max(4, L.font_px / 2);
    int row1 = L.small_px * 3 / 2, field_h = L.font_px * 8 / 5;
    int ph = pad + row1 + pad / 2 + field_h + pad;
    L.panel = {vx, top + vh - ph, vw, ph};
    L.field = {vx + pad, L.panel.y + pad + row1 + pad / 2, vw - 2 * pad, field_h};
    return L;
}

void draw(int ww, int wh, unsigned target_fbo, int vx, int vy, int vw, int vh) {
    auto& p = platform();
    if (!p.text_active) return;
    init_font();
    if (!g_font.ok() || vw <= 0 || vh <= 0) return;
    Layout L = layout(vx, vy, vw, vh, wh);
    if (L.panel.w <= 0 || L.panel.h <= 0) return;
    View v;
    unsigned serial;
    {
        std::lock_guard lk(p.text_mutex);
        v.text = p.text_editing;
        v.cursor = te::clamp_cursor(v.text, p.text_cursor);
        v.comp = p.text_composition;
        v.comp_cursor = te::clamp_cursor(v.comp, p.text_comp_cursor);
        v.max_len = p.text_max_len;
        v.numeric = p.text_numeric;
        serial = p.text_serial.load();
    }
    s64 now = now_ms();
    if (serial != g_seen_serial) g_seen_serial = serial, g_last_edit_ms = now;
    v.caret_on = ((now - g_last_edit_ms) / kBlinkMs) % 2 == 0;
    v.w = L.panel.w, v.h = L.panel.h, v.font_px = L.font_px;
    if (!g_have_drawn || !(v == g_drawn)) {
        compose(v, L);
        g_drawn = v, g_have_drawn = true;
        g_canvas_gen++;
    }
    draw_gl(ww, wh, target_fbo, L.panel);
}

}  // namespace soa::app::text_overlay
