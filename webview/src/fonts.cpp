// Fonts for the page renderer: host TrueType/OpenType files through stb_truetype, loaded once and
// shared by every page (from the Dragalia Lost project's renderer).
//
// This game's pages are Japanese, as on the phone, where Android's WebView draws them with the
// system's Japanese font (Noto Sans CJK JP): so the faces are Noto Sans JP (its Japanese subset,
// Latin included), regular and bold, built into the program (soa/fonts.h, cmake/fonts.cmake) and
// read in place. Italic is the upright face, monospace the regular one. The keyboard's text box
// (runtime/src/app/text_overlay.cpp, FreeType) uses the same regular face.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <string>
#include <vector>

#include "internal.h"
#include "soa/fonts.h"

// The implementation lives here, with external linkage: page.cpp uses stb_truetype too.
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

namespace soa::webview {

struct FontFace {
    const char* name;
    stbtt_fontinfo info{};
};

const stbtt_fontinfo* face_info(const FontFace* f) { return &f->info; }

Rect Rect::clamp(const Rect& o) const { return {std::max(x0, o.x0), std::max(y0, o.y0), std::min(x1, o.x1), std::min(y1, o.y1)}; }

namespace {

FontFace* load_face(const soa::fonts::Data& d) {
    auto* face = new FontFace;
    face->name = d.name;
    int off = stbtt_GetFontOffsetForIndex(d.bytes, 0);
    if (off < 0 || !stbtt_InitFont(&face->info, d.bytes, off)) {
        delete face;
        return nullptr;
    }
    return face;
}

}  // namespace

FontLib& fonts() {
    static FontLib lib;
    static std::once_flag once;
    std::call_once(once, [] {
        lib.faces[kRegular] = load_face(soa::fonts::regular());
        lib.faces[kBold] = load_face(soa::fonts::bold());
        lib.ok = lib.faces[kRegular] != nullptr;
        for (int k = 1; k < kStyles; k++)
            if (!lib.faces[k]) lib.faces[k] = k == kBoldItalic && lib.faces[kBold] ? lib.faces[kBold] : lib.faces[kRegular];
        if (lib.ok)
            WV_LOGI("fonts: %s (bold %s), built in", lib.faces[kRegular]->name,
                    lib.faces[kBold] == lib.faces[kRegular] ? "synthetic" : lib.faces[kBold]->name);
        else
            WV_LOGW("the built-in font doesn't load: pages draw no text");
    });
    return lib;
}

uint32_t next_cp(const char*& s) {
    auto c = (unsigned char)*s++;
    if (c < 0x80) return c;
    int n = c >= 0xf0 ? 3 : c >= 0xe0 ? 2 : c >= 0xc0 ? 1 : 0;
    uint32_t cp = c & (0x3f >> n);
    for (int k = 0; k < n && (*s & 0xc0) == 0x80; k++) cp = cp << 6 | (*s++ & 0x3f);
    return cp;
}

Glyph glyph_for(const Font& f, uint32_t cp) {
    return {f.face, stbtt_FindGlyphIndex(&f.face->info, (int)cp), stbtt_ScaleForMappingEmToPixels(&f.face->info, f.px)};
}

}  // namespace soa::webview
