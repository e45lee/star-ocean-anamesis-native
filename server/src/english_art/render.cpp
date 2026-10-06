// The English art's drawing (art.h): the text in the game's font, its outline / glow / shadow, and
// the cover that clears the Japanese. Integer arithmetic only (the same bytes on every platform).
#include <algorithm>
#include <cstdlib>
#include <cstring>

#include "english_art/art.h"

namespace soa::server::english_art {
namespace {

// UTF-8 to code points (an invalid byte becomes U+FFFD, which the font draws as '?').
std::vector<uint32_t> utf8_points(const std::string& s) {
    std::vector<uint32_t> out;
    for (size_t i = 0; i < s.size();) {
        uint8_t c = (uint8_t)s[i];
        int n = c < 0x80 ? 1 : (c >> 5) == 6 ? 2 : (c >> 4) == 14 ? 3 : (c >> 3) == 30 ? 4 : 0;
        if (!n || i + n > s.size()) {
            out.push_back(0xfffd);
            i++;
            continue;
        }
        uint32_t cp = n == 1 ? c : c & (0x7f >> n);
        for (int k = 1; k < n; k++) cp = cp << 6 | ((uint8_t)s[i + k] & 0x3f);
        out.push_back(cp);
        i += n;
    }
    return out;
}

// One axis of an area-average resample: n0 source samples onto n1 (source sample j covers
// [j * n1, (j + 1) * n1), destination i covers [i * n0, (i + 1) * n0)).
void resample_axis(const int* src, int n0, int* dst, int n1, int stride_src, int stride_dst) {
    for (int i = 0; i < n1; i++) {
        int64_t lo = (int64_t)i * n0, hi = lo + n0, sum = 0;
        for (int64_t j = lo / n1; j < n0 && j * n1 < hi; j++) {
            int64_t a = std::max(lo, j * n1), b = std::min(hi, (j + 1) * n1);
            if (b > a) sum += (int64_t)src[j * stride_src] * (b - a);
        }
        dst[(int64_t)i * stride_dst] = (int)((sum + n0 / 2) / n0);
    }
}

Coverage resample(const Coverage& src, int w1, int h1) {
    std::vector<int> a(src.a.begin(), src.a.end()), mid((size_t)w1 * src.h), out((size_t)w1 * h1);
    for (int y = 0; y < src.h; y++) resample_axis(&a[(size_t)y * src.w], src.w, &mid[(size_t)y * w1], w1, 1, 1);
    for (int x = 0; x < w1; x++) resample_axis(&mid[x], src.h, &out[x], h1, w1, w1);
    Coverage c(w1, h1);
    for (size_t i = 0; i < out.size(); i++) c.a[i] = (uint8_t)std::min(255, out[i]);
    return c;
}

// The maximum over a disc of radius r (r <= 0: a copy).
Coverage dilate(const Coverage& in, int r) {
    if (r <= 0) return in;
    Coverage out(in.w, in.h);
    for (int y = 0; y < in.h; y++)
        for (int x = 0; x < in.w; x++) {
            int m = 0;
            for (int dy = -r; dy <= r && m < 255; dy++)
                for (int dx = -r; dx <= r; dx++)
                    if (dx * dx + dy * dy <= r * r + r) m = std::max(m, (int)in.get(x + dx, y + dy));
            out.a[(size_t)y * in.w + x] = (uint8_t)m;
        }
    return out;
}

// A box blur of radius r, twice (close to a Gaussian).
Coverage blur(const Coverage& in, int r) {
    if (r <= 0) return in;
    Coverage cur = in;
    for (int pass = 0; pass < 2; pass++) {
        Coverage h(cur.w, cur.h), v(cur.w, cur.h);
        int n = 2 * r + 1;
        for (int y = 0; y < cur.h; y++)
            for (int x = 0; x < cur.w; x++) {
                int s = 0;
                for (int k = -r; k <= r; k++) s += cur.get(x + k, y);
                h.a[(size_t)y * cur.w + x] = (uint8_t)((s + n / 2) / n);
            }
        for (int y = 0; y < cur.h; y++)
            for (int x = 0; x < cur.w; x++) {
                int s = 0;
                for (int k = -r; k <= r; k++) s += h.get(x, y + k);
                v.a[(size_t)y * cur.w + x] = (uint8_t)((s + n / 2) / n);
            }
        cur = v;
    }
    return cur;
}

// Source-over of colour `col` at coverage `cov` (0..255) onto an RGBA8 pixel (straight alpha).
void over(uint8_t* d, Rgba col, int cov) {
    int a = (col.a * cov + 127) / 255;
    if (a <= 0) return;
    int da = d[3];
    int keep = (da * (255 - a) + 127) / 255;  // the destination's share
    int oa = a + keep;
    for (int c = 0; c < 3; c++) {
        int sc = c == 0 ? col.r : c == 1 ? col.g : col.b;
        d[c] = (uint8_t)std::min(255, (sc * a + d[c] * keep + oa / 2) / oa);
    }
    d[3] = (uint8_t)std::min(255, oa);
}

Rect intersect(Rect a, Rect b) {
    int x0 = std::max(a.x, b.x), y0 = std::max(a.y, b.y);
    int x1 = std::min(a.x + a.w, b.x + b.w), y1 = std::min(a.y + a.h, b.y + b.h);
    return {x0, y0, std::max(0, x1 - x0), std::max(0, y1 - y0)};
}

}  // namespace

Coverage render_text(const Font& font, const std::string& utf8, const Style& st, int max_w) {
    struct Placed {
        const Glyph* g;
        int pen, line;
    };
    // lines ("\n"), each laid out from pen 0, then shifted by the alignment within the widest
    std::vector<Placed> placed;
    std::vector<int> widths(1, 0);
    int pen = 0, line = 0;
    for (uint32_t cp : utf8_points(utf8)) {
        if (cp == '\n') {
            widths[line] = pen;
            widths.push_back(0);
            line++, pen = 0;
            continue;
        }
        const Glyph* g = font.find(cp);
        if (!g) continue;
        placed.push_back({g, pen, line});
        pen += g->adv + st.tracking;
    }
    widths[line] = pen;
    if (placed.empty()) return Coverage(1, 1);
    int widest = *std::max_element(widths.begin(), widths.end());
    int line_h = font.size + st.leading;
    for (auto& p : placed) {
        int slack = widest - widths[p.line];
        p.pen += st.align == "left" ? 0 : st.align == "right" ? slack : slack / 2;
    }
    int x0 = 0, x1 = widest, y0 = 0, y1 = font.size + line * line_h;
    for (auto& p : placed) {
        x0 = std::min(x0, p.pen + p.g->xoff);
        x1 = std::max(x1, p.pen + p.g->xoff + p.g->w);
        y0 = std::min(y0, p.g->yoff + p.line * line_h);
        y1 = std::max(y1, p.g->yoff + p.g->h + p.line * line_h);
    }
    int bold = std::max(0, st.bold);
    Coverage native(x1 - x0 + bold, y1 - y0);
    for (auto& p : placed)
        for (int y = 0; y < p.g->h; y++)
            for (int x = 0; x < p.g->w; x++) {
                int tx = p.pen + p.g->xoff + x - x0, ty = p.g->yoff + p.line * line_h + y - y0;
                uint8_t& t = native.a[(size_t)ty * native.w + tx];
                t = std::max(t, font.page_alpha(p.g->x + x, p.g->y + y));
            }
    if (bold) {  // widen each stroke to the right by `bold` font pixels
        Coverage b = native;
        for (int y = 0; y < native.h; y++)
            for (int x = 0; x < native.w; x++)
                for (int k = 1; k <= bold; k++) b.a[(size_t)y * native.w + x] = std::max(b.a[(size_t)y * native.w + x], native.get(x - k, y));
        native = b;
    }
    // the style's size, then squeezed horizontally to fit, then shrunk
    int h1 = std::max(1, (native.h * st.size + font.size / 2) / font.size);
    int w1 = std::max(1, (native.w * st.size + font.size / 2) / font.size);
    if (max_w > 0 && w1 > max_w) {
        int min_w = std::max(1, w1 * std::clamp(st.squeeze, 10, 100) / 100);
        if (min_w <= max_w) {
            w1 = max_w;
        } else {
            h1 = std::max(1, h1 * max_w / min_w);
            w1 = max_w;
        }
    }
    return resample(native, w1, h1);
}

void inpaint(Canvas& c, Rect area, Rect clip) {
    clip = intersect(clip, {0, 0, c.w, c.h});
    Rect r = intersect(area, clip);
    if (r.w <= 0 || r.h <= 0) return;
    // Premultiplied channels (colour * alpha, alpha * 255) of the region and a one-pixel ring.
    int W = r.w + 2, H = r.h + 2;
    std::vector<int> v((size_t)W * H * 4, 0);
    std::vector<uint8_t> kind((size_t)W * H, 0);  // 0 outside the clip, 1 fixed (the ring), 2 unknown
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++) {
            int ix = r.x + x - 1, iy = r.y + y - 1;
            bool inside = x >= 1 && y >= 1 && x <= r.w && y <= r.h;
            bool in_clip = ix >= clip.x && iy >= clip.y && ix < clip.x + clip.w && iy < clip.y + clip.h;
            size_t k = (size_t)y * W + x;
            kind[k] = inside ? 2 : in_clip ? 1 : 0;
            if (kind[k] == 1) {
                const uint8_t* p = c.at(ix, iy);
                for (int ch = 0; ch < 3; ch++) v[k * 4 + ch] = p[ch] * p[3];
                v[k * 4 + 3] = p[3] * 255;
            }
        }
    // A start: per row, the line between the row's left and right ring pixels, averaged with the
    // column's line between its top and bottom ones (a missing end takes the other's value).
    auto ring = [&](int x, int y, int ch, bool& ok) {
        size_t k = (size_t)y * W + x;
        ok = kind[k] == 1;
        return v[k * 4 + ch];
    };
    for (int y = 1; y <= r.h; y++)
        for (int x = 1; x <= r.w; x++)
            for (int ch = 0; ch < 4; ch++) {
                bool lok, rok, tok, bok;
                int l = ring(0, y, ch, lok), rr = ring(W - 1, y, ch, rok), t = ring(x, 0, ch, tok), b = ring(x, H - 1, ch, bok);
                int64_t sum = 0, n = 0;
                if (lok || rok) {
                    if (!lok) l = rr;
                    if (!rok) rr = l;
                    sum += ((int64_t)l * (W - 1 - x) + (int64_t)rr * x) / (W - 1), n++;
                }
                if (tok || bok) {
                    if (!tok) t = b;
                    if (!bok) b = t;
                    sum += ((int64_t)t * (H - 1 - y) + (int64_t)b * y) / (H - 1), n++;
                }
                v[((size_t)y * W + x) * 4 + ch] = n ? (int)(sum / n) : 0;
            }
    // Successive over-relaxation (omega 15/8, in place, rows in order) of the discrete Laplace
    // equation; neighbours outside the clip are left out.
    int iters = 4 * std::min(r.w, r.h) + 20;
    const int dxs[4] = {1, -1, 0, 0}, dys[4] = {0, 0, 1, -1};
    for (int it = 0; it < iters; it++)
        for (int y = 1; y <= r.h; y++)
            for (int x = 1; x <= r.w; x++) {
                size_t k = (size_t)y * W + x;
                int64_t s[4] = {0, 0, 0, 0};
                int n = 0;
                for (int d = 0; d < 4; d++) {
                    size_t q = (size_t)(y + dys[d]) * W + (x + dxs[d]);
                    if (!kind[q]) continue;
                    for (int ch = 0; ch < 4; ch++) s[ch] += v[q * 4 + ch];
                    n++;
                }
                if (!n) continue;
                for (int ch = 0; ch < 4; ch++) {
                    int64_t avg = (s[ch] + n / 2) / n, cur = v[k * 4 + ch];
                    int64_t nv = cur + (avg - cur) * 15 / 8;
                    v[k * 4 + ch] = (int)std::clamp<int64_t>(nv, 0, 255 * 255);
                }
            }
    for (int y = 1; y <= r.h; y++)
        for (int x = 1; x <= r.w; x++) {
            const int* q = &v[((size_t)y * W + x) * 4];
            uint8_t* p = c.at(r.x + x - 1, r.y + y - 1);
            int a = std::clamp((q[3] + 127) / 255, 0, 255);
            p[3] = (uint8_t)a;
            for (int ch = 0; ch < 3; ch++) p[ch] = a ? (uint8_t)std::clamp((q[ch] + a / 2) / a, 0, 255) : 0;
        }
}

void draw_text(Canvas& c, const Coverage& text, const Style& st, Rect box, Rect clip) {
    clip = intersect(clip, {0, 0, c.w, c.h});
    int ow = std::max(0, st.outline_width), gr = std::max(0, st.glow_radius);
    int pad = ow + 2 * gr + std::max(std::abs(st.shadow_dx), std::abs(st.shadow_dy)) + 1;
    Coverage fill(text.w + 2 * pad, text.h + 2 * pad);
    for (int y = 0; y < text.h; y++)
        for (int x = 0; x < text.w; x++) fill.a[(size_t)(y + pad) * fill.w + x + pad] = text.a[(size_t)y * text.w + x];
    // the ink's bounds place the text: centred vertically, aligned horizontally
    int ix0 = fill.w, ix1 = -1, iy0 = fill.h, iy1 = -1;
    for (int y = 0; y < fill.h; y++)
        for (int x = 0; x < fill.w; x++)
            if (fill.a[(size_t)y * fill.w + x] > 0) ix0 = std::min(ix0, x), ix1 = std::max(ix1, x), iy0 = std::min(iy0, y), iy1 = std::max(iy1, y);
    if (ix1 < 0) return;
    int inkw = ix1 - ix0 + 1, inkh = iy1 - iy0 + 1;
    int ox = st.align == "left" ? box.x - ix0 : st.align == "right" ? box.x + box.w - 1 - ix1 : box.x + (box.w - inkw) / 2 - ix0;
    int oy = box.y + (box.h - inkh) / 2 - iy0;
    ox += st.dx, oy += st.dy;
    Coverage outl = dilate(fill, ow);
    auto paint = [&](const Coverage& cov, Rgba col, int sx, int sy) {
        if (!col.a) return;
        for (int y = 0; y < cov.h; y++)
            for (int x = 0; x < cov.w; x++) {
                int a = cov.a[(size_t)y * cov.w + x];
                int px = ox + x + sx, py = oy + y + sy;
                if (!a || px < clip.x || py < clip.y || px >= clip.x + clip.w || py >= clip.y + clip.h) continue;
                over(c.at(px, py), col, a);
            }
    };
    if (gr && st.glow.a) paint(blur(dilate(outl, gr), gr), st.glow, 0, 0);
    if (st.shadow.a) paint(outl, st.shadow, st.shadow_dx, st.shadow_dy);
    if (ow && st.outline.a) paint(outl, st.outline, 0, 0);
    paint(fill, st.fill, 0, 0);
}

void apply_label(Canvas& c, const Font& font, const Label& label, Rect sprite, const Canvas* shape) {
    Rect box{sprite.x + label.box.x, sprite.y + label.box.y, label.box.w, label.box.h};
    Rect cov = label.has_cover ? Rect{sprite.x + label.cover.x, sprite.y + label.cover.y, label.cover.w, label.cover.h} : box;
    if (label.style.cover == "inpaint") {
        inpaint(c, cov, sprite);
    } else if (label.style.cover == "fill") {
        Rect r = intersect(intersect(cov, sprite), {0, 0, c.w, c.h});
        for (int y = r.y; y < r.y + r.h; y++)
            for (int x = r.x; x < r.x + r.w; x++) {
                uint8_t* p = c.at(x, y);
                p[0] = label.style.cover_color.r, p[1] = label.style.cover_color.g, p[2] = label.style.cover_color.b,
                p[3] = label.style.cover_color.a;
            }
    } else if (label.style.cover == "shade") {  // cover_color laid over the picture (its alpha kept), its edges faded over 4 px
        Rect r = intersect(intersect(cov, sprite), {0, 0, c.w, c.h});
        for (int y = r.y; y < r.y + r.h; y++)
            for (int x = r.x; x < r.x + r.w; x++) {
                int edge = std::min(std::min(x - cov.x, cov.x + cov.w - 1 - x), std::min(y - cov.y, cov.y + cov.h - 1 - y));
                uint8_t* p = c.at(x, y);
                uint8_t a = shape ? shape->at(x, y)[3] : p[3];  // the picture's shape is kept
                over(p, label.style.cover_color, std::min(255, (edge + 1) * 255 / 5));
                p[3] = a;
            }
    }
    if (label.text.empty()) return;
    Coverage text = render_text(font, label.text, label.style, box.w);
    draw_text(c, text, label.style, box, sprite);
}

}  // namespace soa::server::english_art
