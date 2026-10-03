// The page renderer (soawebview/page.h): litehtml's document_container drawn in software, from the
// Dragalia Lost project's renderer (platformdl/src/webview_page.cpp). Changes: Japanese line
// breaking (split_text), the wide-viewport mode (load), the language (ja-JP), no WebP.
//
// Coordinates: litehtml lays the page out in CSS pixels, `width / zoom` wide; the canvas is in
// device pixels, so every draw call scales by zoom. Fonts are made at their device size.
#include <litehtml.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <future>
#include <map>
#include <unordered_map>

#include "internal.h"

#include <stb_truetype.h>

namespace soa::webview {

namespace lh = litehtml;

namespace {

struct Canvas {
    uint8_t* px;
    int w, h;
    float zoom;
    std::vector<Rect> clips;
    Rect clip() const { return clips.empty() ? Rect{0, 0, w, h} : clips.back(); }
    Rect dev(const lh::position& p) const {
        return {(int)std::floor(p.x * zoom + 0.5f), (int)std::floor(p.y * zoom + 0.5f), (int)std::floor((p.x + p.width) * zoom + 0.5f),
                (int)std::floor((p.y + p.height) * zoom + 0.5f)};
    }
    // src-over of a straight-alpha colour with coverage a (0..255)
    void blend(int x, int y, uint8_t r, uint8_t g, uint8_t b, int a) {
        if (a <= 0) return;
        uint8_t* d = px + ((size_t)y * w + x) * 4;
        if (a >= 255) {
            d[0] = r, d[1] = g, d[2] = b, d[3] = 255;
            return;
        }
        int da = d[3], oa = a + da * (255 - a) / 255;
        if (oa <= 0) return;
        d[0] = (uint8_t)((r * a + d[0] * da * (255 - a) / 255) / oa);
        d[1] = (uint8_t)((g * a + d[1] * da * (255 - a) / 255) / oa);
        d[2] = (uint8_t)((b * a + d[2] * da * (255 - a) / 255) / oa);
        d[3] = (uint8_t)oa;
    }
    void fill(Rect r, lh::web_color c, const lh::border_radiuses* rad = nullptr) {
        Rect full = r;
        r = r.clamp(clip());
        if (r.empty() || c.alpha == 0) return;
        float tl = 0, tr = 0, br = 0, bl = 0;
        if (rad) {
            tl = rad->top_left_x * zoom, tr = rad->top_right_x * zoom, br = rad->bottom_right_x * zoom, bl = rad->bottom_left_x * zoom;
            float lim = std::min(full.x1 - full.x0, full.y1 - full.y0) / 2.0f;
            tl = std::min(tl, lim), tr = std::min(tr, lim), br = std::min(br, lim), bl = std::min(bl, lim);
        }
        bool round = tl > 0.5f || tr > 0.5f || br > 0.5f || bl > 0.5f;
        for (int y = r.y0; y < r.y1; y++)
            for (int x = r.x0; x < r.x1; x++) {
                int a = c.alpha;
                if (round) {
                    float fx = x + 0.5f, fy = y + 0.5f, cx = 0, cy = 0, rr = 0;
                    if (fx < full.x0 + tl && fy < full.y0 + tl) cx = full.x0 + tl, cy = full.y0 + tl, rr = tl;
                    else if (fx > full.x1 - tr && fy < full.y0 + tr) cx = full.x1 - tr, cy = full.y0 + tr, rr = tr;
                    else if (fx > full.x1 - br && fy > full.y1 - br) cx = full.x1 - br, cy = full.y1 - br, rr = br;
                    else if (fx < full.x0 + bl && fy > full.y1 - bl) cx = full.x0 + bl, cy = full.y1 - bl, rr = bl;
                    if (rr > 0) {
                        float dist = std::hypot(fx - cx, fy - cy);
                        float cov = std::clamp(rr - dist + 0.5f, 0.0f, 1.0f);
                        a = (int)(a * cov);
                    }
                }
                blend(x, y, c.red, c.green, c.blue, a);
            }
    }
};

}  // namespace

// ===========================================================================================
// The document container
struct WebPage::Impl : lh::document_container {
    Fetch fetch;
    std::string url, title_;
    int width = 0, height = 0;
    float zoom = 1;
    std::string html;
    std::string source;      // the HTML as loaded (resize reloads it when the zoom changes)
    float device_zoom = 1;   // load()'s zoom argument
    int viewport_w = 0;      // the viewport meta's width, CSS pixels (0: none)
    lh::document::ptr doc;
    std::map<std::string, std::shared_ptr<Image>> images;
    std::map<std::string, std::shared_future<std::shared_ptr<Image>>> pending;
    std::string clicked;
    Canvas* cv = nullptr;
    // glyph cache: (face, glyph, size*4, subpixel x) -> bitmap
    struct GlyphBitmap {
        int w = 0, h = 0, xoff = 0, yoff = 0;
        std::vector<uint8_t> a;
    };
    std::unordered_map<std::string, GlyphBitmap> glyphs;

    std::string abs(const char* src, const char* baseurl) const {
        return resolve_url(baseurl && *baseurl ? std::string(baseurl) : url, src ? src : "");
    }

    // ---- fonts
    lh::uint_ptr create_font(const lh::font_description& d, const lh::document*, lh::font_metrics* fm) override {
        FontLib& lib = fonts();
        std::string fam = d.family;
        for (auto& ch : fam) ch = (char)tolower((unsigned char)ch);
        bool mono = fam.find("mono") != std::string::npos || fam.find("courier") != std::string::npos || fam.find("consolas") != std::string::npos;
        bool bold = d.weight >= 600, italic = d.style != lh::font_style_normal;
        int st = mono ? kMono : bold && italic ? kBoldItalic : bold ? kBold : italic ? kItalic : kRegular;
        auto* f = new Font;
        f->face = lib.faces[st] ? lib.faces[st] : lib.faces[kRegular];
        f->synth_bold = bold && f->face && lib.faces[kBold] == lib.faces[kRegular];
        f->px = d.size * zoom;
        f->zoom = zoom;
        f->decoration = d.decoration_line;
        f->ascent = f->px * 0.8f, f->descent = f->px * 0.2f;
        float line_gap = 0;
        if (f->face) {
            int a, de, lg;
            stbtt_GetFontVMetrics(face_info(f->face), &a, &de, &lg);
            float s = stbtt_ScaleForMappingEmToPixels(face_info(f->face), f->px);
            f->ascent = a * s, f->descent = -de * s, line_gap = lg * s;
        }
        if (fm) {
            fm->font_size = d.size;
            fm->ascent = f->ascent / zoom;
            fm->descent = f->descent / zoom;
            fm->height = (f->ascent + f->descent + line_gap) / zoom;
            fm->x_height = f->px * 0.5f / zoom;
            if (f->face) {
                int x0, y0, x1, y1;
                if (stbtt_GetCodepointBox(face_info(f->face), 'x', &x0, &y0, &x1, &y1))
                    fm->x_height = y1 * stbtt_ScaleForMappingEmToPixels(face_info(f->face), f->px) / zoom;
            }
            fm->ch_width = text_width("0", (lh::uint_ptr)f);
            fm->draw_spaces = (d.decoration_line != 0);
            fm->sub_shift = d.size / 5;
            fm->super_shift = d.size / 3;
        }
        return (lh::uint_ptr)f;
    }
    void delete_font(lh::uint_ptr h) override { delete (Font*)h; }
    lh::pixel_t text_width(const char* text, lh::uint_ptr h) override {
        auto* f = (Font*)h;
        if (!f || !f->face) return 0;
        float x = 0;
        Glyph prev{nullptr, 0, 0};
        for (const char* s = text; *s;) {
            Glyph g = glyph_for(*f, next_cp(s));
            int adv, lsb;
            stbtt_GetGlyphHMetrics(face_info(g.face), g.index, &adv, &lsb);
            if (prev.face == g.face && prev.index) x += stbtt_GetGlyphKernAdvance(face_info(g.face), prev.index, g.index) * g.scale;
            x += adv * g.scale;
            prev = g;
        }
        if (f->synth_bold) x += 1;
        return x / zoom;
    }
    const GlyphBitmap& glyph_bitmap(const Glyph& g, float px, int sub) {
        char key[96];
        snprintf(key, sizeof key, "%p:%d:%d:%d", (void*)g.face, g.index, (int)(px * 4), sub);
        auto it = glyphs.find(key);
        if (it != glyphs.end()) return it->second;
        GlyphBitmap b;
        int x0, y0, x1, y1;
        float sx = sub / 4.0f;
        stbtt_GetGlyphBitmapBoxSubpixel(face_info(g.face), g.index, g.scale, g.scale, sx, 0, &x0, &y0, &x1, &y1);
        b.w = x1 - x0, b.h = y1 - y0, b.xoff = x0, b.yoff = y0;
        if (b.w > 0 && b.h > 0) {
            b.a.resize((size_t)b.w * b.h);
            stbtt_MakeGlyphBitmapSubpixel(face_info(g.face), b.a.data(), b.w, b.h, b.w, g.scale, g.scale, sx, 0, g.index);
        }
        return glyphs.emplace(key, std::move(b)).first->second;
    }
    void draw_text(lh::uint_ptr hdc, const char* text, lh::uint_ptr h, lh::web_color color, const lh::position& pos) override {
        auto* c = (Canvas*)hdc;
        auto* f = (Font*)h;
        if (!c || !f || !f->face) return;
        Rect clip = c->clip();
        float x = pos.x * zoom, baseline = (pos.y + pos.height) * zoom - f->descent;
        float x_start = x;
        Glyph prev{nullptr, 0, 0};
        for (const char* s = text; *s;) {
            uint32_t cp = next_cp(s);
            Glyph g = glyph_for(*f, cp);
            if (prev.face == g.face && prev.index) x += stbtt_GetGlyphKernAdvance(face_info(g.face), prev.index, g.index) * g.scale;
            int adv, lsb;
            stbtt_GetGlyphHMetrics(face_info(g.face), g.index, &adv, &lsb);
            if (cp > ' ') {
                int ix = (int)std::floor(x);
                int sub = (int)((x - ix) * 4) & 3;
                const GlyphBitmap& b = glyph_bitmap(g, f->px, sub);
                int by = (int)std::lround(baseline);
                for (int pass = 0; pass < (f->synth_bold ? 2 : 1); pass++)
                    for (int yy = 0; yy < b.h; yy++) {
                        int py = by + b.yoff + yy;
                        if (py < clip.y0 || py >= clip.y1) continue;
                        for (int xx = 0; xx < b.w; xx++) {
                            int pxx = ix + b.xoff + xx + pass;
                            if (pxx < clip.x0 || pxx >= clip.x1) continue;
                            int a = b.a[(size_t)yy * b.w + xx];
                            if (a) c->blend(pxx, py, color.red, color.green, color.blue, a * color.alpha / 255);
                        }
                    }
            }
            x += adv * g.scale;
            prev = g;
        }
        float thick = std::max(1.0f, f->px / 16);
        auto line = [&](float y) { c->fill({(int)x_start, (int)std::lround(y), (int)std::ceil(x), (int)std::lround(y + thick)}, color); };
        if (f->decoration & lh::text_decoration_line_underline) line(baseline + thick);
        if (f->decoration & lh::text_decoration_line_line_through) line(baseline - f->ascent * 0.3f);
        if (f->decoration & lh::text_decoration_line_overline) line(baseline - f->ascent);
    }
    lh::pixel_t pt_to_px(float pt) const override { return pt * 96 / 72; }
    lh::pixel_t get_default_font_size() const override { return 16; }
    const char* get_default_font_name() const override { return "sans-serif"; }

    // ---- boxes
    void draw_list_marker(lh::uint_ptr hdc, const lh::list_marker& m) override {
        auto* c = (Canvas*)hdc;
        if (!c) return;
        Rect r = c->dev(m.pos);
        if (m.marker_type == lh::list_style_type_square) {
            c->fill(r, m.color);
        } else if (m.marker_type == lh::list_style_type_disc || m.marker_type == lh::list_style_type_circle) {
            lh::border_radiuses rad{};
            rad.top_left_x = rad.top_right_x = rad.bottom_left_x = rad.bottom_right_x = m.pos.width / 2;
            c->fill(r, m.color, &rad);
            if (m.marker_type == lh::list_style_type_circle) {
                int t = std::max(1, (int)(zoom));
                Rect in{r.x0 + t, r.y0 + t, r.x1 - t, r.y1 - t};
                lh::border_radiuses rin = rad;
                rin.top_left_x = rin.top_right_x = rin.bottom_left_x = rin.bottom_right_x = (m.pos.width / 2) - t / zoom;
                lh::web_color bg{255, 255, 255, 255};
                c->fill(in, bg, &rin);
            }
        }
    }
    void load_image(const char* src, const char* baseurl, bool) override {
        std::string u = abs(src, baseurl);
        if (u.empty() || images.count(u) || pending.count(u)) return;
        if (u.rfind("data:", 0) == 0) {
            images[u] = nullptr;  // data: URLs: not decoded
            return;
        }
        Fetch fe = fetch;
        pending[u] = std::async(std::launch::async, [fe, u]() -> std::shared_ptr<Image> {
                         FetchResult r = fe(u);
                         if (r.status < 200 || r.status >= 300) {
                             WV_LOGW("image %s: %ld %s", u.c_str(), r.status, r.error.c_str());
                             return nullptr;
                         }
                         auto img = decode_image(r.body);
                         if (!img) WV_LOGW("image %s: can't decode (%zu bytes)", u.c_str(), r.body.size());
                         return img;
                     }).share();
    }
    void wait_images() {
        for (auto& [u, f] : pending) images[u] = f.get();
        pending.clear();
    }
    std::shared_ptr<Image> image(const std::string& u) {
        auto it = images.find(u);
        if (it != images.end()) return it->second;
        auto p = pending.find(u);
        if (p != pending.end()) {
            auto img = p->second.get();
            images[u] = img;
            pending.erase(p);
            return img;
        }
        return nullptr;
    }
    void get_image_size(const char* src, const char* baseurl, lh::size& sz) override {
        auto img = image(abs(src, baseurl));
        sz.width = img ? (lh::pixel_t)img->w : 0;
        sz.height = img ? (lh::pixel_t)img->h : 0;
    }
    void draw_image(lh::uint_ptr hdc, const lh::background_layer& layer, const std::string& src, const std::string& base_url) override {
        auto* c = (Canvas*)hdc;
        if (!c) return;
        auto img = image(abs(src.c_str(), base_url.c_str()));
        if (!img || img->w <= 0) return;
        Rect clip = c->dev(layer.clip_box).clamp(c->clip());
        Rect o = c->dev(layer.origin_box);
        int ow = o.x1 - o.x0, oh = o.y1 - o.y0;
        if (clip.empty() || ow <= 0 || oh <= 0) return;
        bool rx = layer.repeat == lh::background_repeat_repeat || layer.repeat == lh::background_repeat_repeat_x;
        bool ry = layer.repeat == lh::background_repeat_repeat || layer.repeat == lh::background_repeat_repeat_y;
        // A single image whose box has another aspect ratio: cropped to fill it ("object-fit: cover",
        // which pages use for thumbnails and litehtml doesn't implement) rather than stretched.
        float sx0 = 0, sy0 = 0, sw = (float)img->w, sh = (float)img->h;
        if (!rx && !ry) {
            float ia = (float)img->w / img->h, ba = (float)ow / oh;
            if (std::fabs(ia / ba - 1) > 0.02f) {
                if (ia > ba) sw = img->h * ba, sx0 = (img->w - sw) / 2;
                else sh = img->w / ba, sy0 = (img->h - sh) / 2;
            }
        }
        for (int y = clip.y0; y < clip.y1; y++) {
            int ty = y - o.y0;
            if (ry) ty = ((ty % oh) + oh) % oh;
            else if (ty < 0 || ty >= oh) continue;
            float fy = sy0 + (ty + 0.5f) * sh / oh - 0.5f;
            int y0i = std::clamp((int)std::floor(fy), 0, img->h - 1), y1i = std::min(y0i + 1, img->h - 1);
            float wy = std::clamp(fy - y0i, 0.0f, 1.0f);
            for (int x = clip.x0; x < clip.x1; x++) {
                int tx = x - o.x0;
                if (rx) tx = ((tx % ow) + ow) % ow;
                else if (tx < 0 || tx >= ow) continue;
                float fx = sx0 + (tx + 0.5f) * sw / ow - 0.5f;
                int x0i = std::clamp((int)std::floor(fx), 0, img->w - 1), x1i = std::min(x0i + 1, img->w - 1);
                float wx = std::clamp(fx - x0i, 0.0f, 1.0f);
                float px[4];
                for (int k = 0; k < 4; k++) {
                    auto at = [&](int xx, int yy) { return (float)img->rgba[((size_t)yy * img->w + xx) * 4 + k]; };
                    px[k] = (at(x0i, y0i) * (1 - wx) + at(x1i, y0i) * wx) * (1 - wy) + (at(x0i, y1i) * (1 - wx) + at(x1i, y1i) * wx) * wy;
                }
                c->blend(x, y, (uint8_t)px[0], (uint8_t)px[1], (uint8_t)px[2], (int)px[3]);
            }
        }
    }
    void draw_solid_fill(lh::uint_ptr hdc, const lh::background_layer& layer, const lh::web_color& color) override {
        auto* c = (Canvas*)hdc;
        if (!c) return;
        c->clips.push_back(c->dev(layer.clip_box).clamp(c->clip()));
        c->fill(c->dev(layer.border_box), color, &layer.border_radius);
        c->clips.pop_back();
    }
    static lh::web_color mix(const lh::background_layer::gradient_base& g, float t) {
        const auto& pts = g.color_points;
        if (pts.empty()) return lh::web_color::transparent;
        if (t <= pts.front().offset) return pts.front().color;
        for (size_t k = 1; k < pts.size(); k++)
            if (t <= pts[k].offset) {
                float span = pts[k].offset - pts[k - 1].offset, w = span > 0 ? (t - pts[k - 1].offset) / span : 1;
                auto a = pts[k - 1].color, b = pts[k].color;
                auto l = [w](uint8_t p, uint8_t q) { return (uint8_t)(p + (q - p) * w); };
                return lh::web_color(l(a.red, b.red), l(a.green, b.green), l(a.blue, b.blue), l(a.alpha, b.alpha));
            }
        return pts.back().color;
    }
    void draw_linear_gradient(lh::uint_ptr hdc, const lh::background_layer& layer, const lh::background_layer::linear_gradient& g) override {
        auto* c = (Canvas*)hdc;
        if (!c) return;
        Rect r = c->dev(layer.clip_box).clamp(c->clip()).clamp(c->dev(layer.border_box));
        float sx = g.start.x * zoom, sy = g.start.y * zoom, dx = (g.end.x - g.start.x) * zoom, dy = (g.end.y - g.start.y) * zoom;
        float len2 = dx * dx + dy * dy;
        for (int y = r.y0; y < r.y1; y++)
            for (int x = r.x0; x < r.x1; x++) {
                float t = len2 > 0 ? ((x + 0.5f - sx) * dx + (y + 0.5f - sy) * dy) / len2 : 0;
                auto col = mix(g, t);
                c->blend(x, y, col.red, col.green, col.blue, col.alpha);
            }
    }
    void draw_radial_gradient(lh::uint_ptr hdc, const lh::background_layer& layer, const lh::background_layer::radial_gradient& g) override {
        auto* c = (Canvas*)hdc;
        if (!c) return;
        Rect r = c->dev(layer.clip_box).clamp(c->clip()).clamp(c->dev(layer.border_box));
        float cx = g.position.x * zoom, cy = g.position.y * zoom, rx = std::max(1e-3f, g.radius.x * zoom), ry = std::max(1e-3f, g.radius.y * zoom);
        for (int y = r.y0; y < r.y1; y++)
            for (int x = r.x0; x < r.x1; x++) {
                float t = std::hypot((x + 0.5f - cx) / rx, (y + 0.5f - cy) / ry);
                auto col = mix(g, t);
                c->blend(x, y, col.red, col.green, col.blue, col.alpha);
            }
    }
    void draw_conic_gradient(lh::uint_ptr hdc, const lh::background_layer& layer, const lh::background_layer::conic_gradient& g) override {
        auto* c = (Canvas*)hdc;
        if (!c) return;
        Rect r = c->dev(layer.clip_box).clamp(c->clip()).clamp(c->dev(layer.border_box));
        float cx = g.position.x * zoom, cy = g.position.y * zoom;
        for (int y = r.y0; y < r.y1; y++)
            for (int x = r.x0; x < r.x1; x++) {
                float a = std::atan2(x + 0.5f - cx, -(y + 0.5f - cy)) * 180 / (float)M_PI - g.angle;
                float t = std::fmod(a + 720, 360.0f) / 360;
                auto col = mix(g, t);
                c->blend(x, y, col.red, col.green, col.blue, col.alpha);
            }
    }
    void draw_borders(lh::uint_ptr hdc, const lh::borders& b, const lh::position& pos, bool) override {
        auto* c = (Canvas*)hdc;
        if (!c) return;
        Rect r = c->dev(pos);
        auto w = [&](const lh::border& s) {
            if (s.style == lh::border_style_none || s.style == lh::border_style_hidden || s.width <= 0 || s.color.alpha == 0) return 0;
            return std::max(1, (int)std::lround(s.width * zoom));
        };
        int lt = w(b.left), tp = w(b.top), rt = w(b.right), bt = w(b.bottom);
        bool rounded = b.radius.top_left_x > 0 || b.radius.top_right_x > 0 || b.radius.bottom_left_x > 0 || b.radius.bottom_right_x > 0;
        if (rounded && lt == tp && tp == rt && rt == bt && lt > 0 && b.left.color == b.top.color && b.top.color == b.right.color &&
            b.right.color == b.bottom.color) {
            // a uniform rounded border: the ring between the outer and inner rounded rectangles
            std::vector<uint8_t> save;
            Rect in{r.x0 + lt, r.y0 + lt, r.x1 - lt, r.y1 - lt};
            Rect cl = r.clamp(c->clip());
            if (cl.empty()) return;
            // outer fill, then restore the inside
            save.resize((size_t)(cl.x1 - cl.x0) * (cl.y1 - cl.y0) * 4);
            for (int y = cl.y0; y < cl.y1; y++) memcpy(&save[(size_t)(y - cl.y0) * (cl.x1 - cl.x0) * 4], c->px + ((size_t)y * c->w + cl.x0) * 4, (size_t)(cl.x1 - cl.x0) * 4);
            c->fill(r, b.left.color, &b.radius);
            lh::border_radiuses ir = b.radius;
            float t = lt / zoom;
            for (float* v : {&ir.top_left_x, &ir.top_right_x, &ir.bottom_left_x, &ir.bottom_right_x}) *v = std::max(0.0f, *v - t);
            // inside: put the saved pixels back where the inner rounded rect covers
            float itl = ir.top_left_x * zoom, itr = ir.top_right_x * zoom, ibr = ir.bottom_right_x * zoom, ibl = ir.bottom_left_x * zoom;
            Rect ic = in.clamp(cl);
            for (int y = ic.y0; y < ic.y1; y++)
                for (int x = ic.x0; x < ic.x1; x++) {
                    float fx = x + 0.5f, fy = y + 0.5f, cx = 0, cy = 0, rr = 0;
                    if (fx < in.x0 + itl && fy < in.y0 + itl) cx = in.x0 + itl, cy = in.y0 + itl, rr = itl;
                    else if (fx > in.x1 - itr && fy < in.y0 + itr) cx = in.x1 - itr, cy = in.y0 + itr, rr = itr;
                    else if (fx > in.x1 - ibr && fy > in.y1 - ibr) cx = in.x1 - ibr, cy = in.y1 - ibr, rr = ibr;
                    else if (fx < in.x0 + ibl && fy > in.y1 - ibl) cx = in.x0 + ibl, cy = in.y1 - ibl, rr = ibl;
                    float cov = rr > 0 ? std::clamp(rr - std::hypot(fx - cx, fy - cy) + 0.5f, 0.0f, 1.0f) : 1;
                    if (cov <= 0) continue;
                    uint8_t* d = c->px + ((size_t)y * c->w + x) * 4;
                    const uint8_t* s = &save[((size_t)(y - cl.y0) * (cl.x1 - cl.x0) + (x - cl.x0)) * 4];
                    for (int k = 0; k < 4; k++) d[k] = (uint8_t)(s[k] * cov + d[k] * (1 - cov));
                }
            return;
        }
        if (tp) c->fill({r.x0, r.y0, r.x1, r.y0 + tp}, b.top.color);
        if (bt) c->fill({r.x0, r.y1 - bt, r.x1, r.y1}, b.bottom.color);
        if (lt) c->fill({r.x0, r.y0 + tp, r.x0 + lt, r.y1 - bt}, b.left.color);
        if (rt) c->fill({r.x1 - rt, r.y0 + tp, r.x1, r.y1 - bt}, b.right.color);
    }

    // ---- document
    void set_caption(const char* caption) override {
        if (title_.empty() && caption) title_ = caption;  // the head's <title>, not an <svg>'s
    }
    void set_base_url(const char* base) override {
        if (base && *base) url = resolve_url(url, base);
    }
    void link(const std::shared_ptr<lh::document>&, const lh::element::ptr&) override {}
    // Japanese line breaking (text_ja.cpp): litehtml's own breaks only at spaces and ideographs.
    void split_text(const char* text, const std::function<void(const char*)>& on_word, const std::function<void(const char*)>& on_space) override {
        split_text_ja(text, on_word, on_space);
    }
    void on_anchor_click(const char* u, const lh::element::ptr&) override { clicked = u ? abs(u, nullptr) : ""; }
    void on_mouse_event(const lh::element::ptr&, lh::mouse_event) override {}
    void set_cursor(const char*) override {}
    void transform_text(lh::string& text, lh::text_transform tt) override {
        if (tt == lh::text_transform_uppercase)
            for (auto& ch : text) ch = (char)toupper((unsigned char)ch);
        else if (tt == lh::text_transform_lowercase)
            for (auto& ch : text) ch = (char)tolower((unsigned char)ch);
        else if (tt == lh::text_transform_capitalize && !text.empty())
            text[0] = (char)toupper((unsigned char)text[0]);
    }
    void import_css(lh::string& text, const lh::string& href, lh::string& baseurl) override {
        std::string u = resolve_url(baseurl.empty() ? url : baseurl, href);
        FetchResult r = fetch(u);
        if (r.status < 200 || r.status >= 300) {
            WV_LOGW("stylesheet %s: %ld %s", u.c_str(), r.status, r.error.c_str());
            return;
        }
        text = simplify_css(r.body);
        baseurl = u;
        if (const char* dump = getenv("SOA_WEBVIEW_DUMP_CSS")) {  // debugging: the stylesheet as litehtml gets it
            if (FILE* f = fopen(dump, "ab")) {
                fprintf(f, "/* %s */\n%s\n", u.c_str(), text.c_str());
                fclose(f);
            }
        }
    }
    void set_clip(const lh::position& pos, const lh::border_radiuses&) override {
        if (cv) cv->clips.push_back(cv->dev(pos).clamp(cv->clip()));
    }
    void del_clip() override {
        if (cv && !cv->clips.empty()) cv->clips.pop_back();
    }
    void get_viewport(lh::position& vp) const override {
        vp.x = 0, vp.y = 0;
        vp.width = width / zoom, vp.height = height / zoom;
    }
    lh::element::ptr create_element(const char*, const lh::string_map&, const std::shared_ptr<lh::document>&) override { return nullptr; }
    void get_media_features(lh::media_features& m) const override {
        m.type = lh::media_type_screen;
        m.width = m.device_width = width / zoom;
        m.height = m.device_height = height / zoom;
        m.color = 8;
        m.monochrome = 0;
        m.color_index = 256;
        m.resolution = 96 * zoom;
    }
    void get_language(lh::string& language, lh::string& culture) const override {
        language = "ja";
        culture = "JP";
    }

    void layout() {
        if (doc) doc->render(width / zoom);
    }
};

WebPage::WebPage(Fetch fetch) : d_(std::make_unique<Impl>()) { d_->fetch = std::move(fetch); }
WebPage::~WebPage() = default;

void WebPage::load(const std::string& html, const std::string& url, int width, int height, float zoom) {
    d_->doc.reset();
    d_->images.clear();
    d_->pending.clear();
    d_->glyphs.clear();
    d_->title_.clear();
    d_->url = url;
    d_->width = std::max(1, width), d_->height = std::max(1, height);
    d_->zoom = d_->device_zoom = zoom > 0 ? zoom : 1;
    d_->source = html;
    // The Android WebView's wide-viewport mode (setUseWideViewPort + setLoadWithOverviewMode, which
    // SOAActivity.ShowWebView sets): a page whose viewport meta names a width is laid out that wide
    // and scaled to fit the view.
    d_->viewport_w = viewport_width(html);
    if (d_->viewport_w > 0) d_->zoom = (float)d_->width / d_->viewport_w;
    fonts();
    // Inline <style> blocks go through the CSS simplifier too.
    std::string h = html;
    for (size_t p = 0; (p = h.find("<style", p)) != std::string::npos;) {
        size_t open = h.find('>', p);
        size_t close = open == std::string::npos ? std::string::npos : h.find("</style>", open);
        if (close == std::string::npos) break;
        std::string css = simplify_css(h.substr(open + 1, close - open - 1));
        h.replace(open + 1, close - open - 1, css);
        p = open + 1 + css.size();
    }
    d_->html = h;
    d_->doc = lh::document::createFromString(h, d_.get());
    d_->wait_images();
    d_->layout();
}

void WebPage::resize(int width, int height) {
    width = std::max(1, width), height = std::max(1, height);
    if (d_->viewport_w > 0 && width != d_->width && d_->doc) {  // a new zoom: the fonts are made at their device size
        std::string src = d_->source, url = d_->url;
        load(src, url, width, height, d_->device_zoom);
        return;
    }
    d_->width = width, d_->height = height;
    d_->layout();
}

bool WebPage::loaded() const { return (bool)d_->doc; }
float WebPage::zoom() const { return d_->zoom; }
int WebPage::content_height() const { return d_->doc ? (int)std::ceil(d_->doc->height() * d_->zoom) : 0; }
std::string WebPage::title() const { return d_->title_; }

void WebPage::draw(uint8_t* rgba, int w, int h, int scroll_y, bool opaque) {
    if (opaque) memset(rgba, 255, (size_t)w * h * 4);
    else memset(rgba, 0, (size_t)w * h * 4);
    if (!d_->doc) return;
    Canvas c{rgba, w, h, d_->zoom, {}};
    d_->cv = &c;
    lh::position vclip(0, 0, w / d_->zoom, h / d_->zoom);
    d_->doc->draw((lh::uint_ptr)&c, 0, -scroll_y / d_->zoom, &vclip);
    d_->cv = nullptr;
}

std::string WebPage::tap(int x, int y, int scroll_y) {
    if (!d_->doc) return "";
    d_->clicked.clear();
    lh::position::vector redraw;
    float dx = x / d_->zoom, dy = (y + scroll_y) / d_->zoom;
    d_->doc->on_mouse_over(dx, dy, x / d_->zoom, y / d_->zoom, redraw);
    d_->doc->on_lbutton_down(dx, dy, x / d_->zoom, y / d_->zoom, redraw);
    d_->doc->on_lbutton_up(dx, dy, x / d_->zoom, y / d_->zoom, redraw);
    d_->doc->on_mouse_leave(redraw);
    return d_->clicked;
}

}  // namespace soa::webview
