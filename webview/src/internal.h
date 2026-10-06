#pragma once
// libsoawebview's internals, shared by its files (fonts.cpp, image.cpp, page.cpp, log.cpp).
#include <litehtml.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "soawebview/page.h"

struct stbtt_fontinfo;

namespace soa::webview {

// ---- log.cpp
void log(int level, const char* fmt, ...) __attribute__((format(printf, 2, 3)));
#define WV_LOGI(...) ::soa::webview::log(1, __VA_ARGS__)
#define WV_LOGW(...) ::soa::webview::log(2, __VA_ARGS__)

// ---- fonts.cpp: the built-in fonts (soa/fonts.h) through stb_truetype, loaded once, shared by every page.
struct FontFace;
enum FaceStyle { kRegular, kBold, kItalic, kBoldItalic, kMono, kStyles };
struct FontLib {
    FontFace* faces[kStyles] = {};
    bool ok = false;
};
FontLib& fonts();
const stbtt_fontinfo* face_info(const FontFace* f);

struct Font {
    FontFace* face;
    bool synth_bold;        // no bold face: drawn twice
    float px;               // em size, device pixels
    float ascent, descent;  // device pixels
    int decoration;
    float zoom;
};
struct Glyph {
    FontFace* face;
    int index;
    float scale;
};
uint32_t next_cp(const char*& s);
Glyph glyph_for(const Font& f, uint32_t cp);

// ---- image.cpp
struct Image {
    int w = 0, h = 0;
    std::vector<uint8_t> rgba;
};
std::shared_ptr<Image> decode_image(const std::string& data);

// ---- the canvas (page.cpp draws on it)
struct Rect {
    int x0, y0, x1, y1;  // device pixels, [x0, x1)
    bool empty() const { return x1 <= x0 || y1 <= y0; }
    Rect clamp(const Rect& o) const;
};

}  // namespace soa::webview
