// Fonts for the page renderer: host TrueType/OpenType files through stb_truetype, loaded once and
// shared by every page (from the Dragalia Lost project's renderer).
//
// This game's pages are Japanese, as on the phone, where Android's WebView draws them with the
// system's Japanese font (Noto Sans CJK JP): so the regular face is a Japanese font found on the
// host (SOA_WEBVIEW_FONT, then IPAex Gothic, Noto Sans CJK, the Debian "fonts-japanese-gothic"
// alternative, IPA Gothic, Droid Sans Fallback), with a Latin family (DejaVu, Liberation, ...) as
// a fallback for glyphs it lacks (Droid Sans Fallback has no Latin). Bold: Noto Sans CJK Bold if
// installed, else drawn twice (synthetic bold). The text box of the game's keyboard
// (runtime/src/app/text_overlay.cpp, FreeType) searches the same kind of list; docs/webview.md
// "Fonts" proposes one shared search.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <string>
#include <vector>

#include "internal.h"

// The implementation lives here, with external linkage: page.cpp uses stb_truetype too.
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

namespace soa::webview {

struct FontFace {
    std::string path;
    std::vector<uint8_t> data;
    stbtt_fontinfo info{};
};

const stbtt_fontinfo* face_info(const FontFace* f) { return &f->info; }
const std::string& face_path(const FontFace* f) { return f->path; }

Rect Rect::clamp(const Rect& o) const { return {std::max(x0, o.x0), std::max(y0, o.y0), std::min(x1, o.x1), std::min(y1, o.y1)}; }

namespace {

FontFace* load_face(const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return nullptr;
    auto* face = new FontFace;
    face->path = path;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    face->data.resize(n > 0 ? (size_t)n : 0);
    bool ok = n > 0 && fread(face->data.data(), 1, (size_t)n, f) == (size_t)n;
    fclose(f);
    int off = ok ? stbtt_GetFontOffsetForIndex(face->data.data(), 0) : -1;  // a .ttc: its first face
    if (off < 0 || !stbtt_InitFont(&face->info, face->data.data(), off)) {
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
        const std::string u = "/usr/share/fonts/truetype/", o = "/usr/share/fonts/opentype/";
        std::vector<std::string> ja = {o + "ipaexfont-gothic/ipaexg.ttf",       o + "noto/NotoSansCJK-Regular.ttc", u + "noto/NotoSansCJK-Regular.ttc",
                                       u + "fonts-japanese-gothic.ttf",         o + "ipafont-gothic/ipagp.ttf",     o + "ipafont-gothic/ipag.ttf",
                                       u + "droid/DroidSansFallbackFull.ttf"};
        std::vector<std::string> ja_bold = {o + "noto/NotoSansCJK-Bold.ttc", u + "noto/NotoSansCJK-Bold.ttc"};
        std::vector<std::string> latin = {u + "dejavu/DejaVuSans.ttf", u + "liberation2/LiberationSans-Regular.ttf",
                                          u + "liberation/LiberationSans-Regular.ttf", u + "noto/NotoSans-Regular.ttf", u + "freefont/FreeSans.ttf"};
        std::vector<std::string> mono = {u + "dejavu/DejaVuSansMono.ttf", u + "liberation2/LiberationMono-Regular.ttf",
                                         u + "liberation/LiberationMono-Regular.ttf", u + "noto/NotoSansMono-Regular.ttf"};
        if (const char* e = getenv("SOA_WEBVIEW_FONT"); e && *e) ja.insert(ja.begin(), e);
        for (auto& p : ja)
            if ((lib.faces[kRegular] = load_face(p))) break;
        for (auto& p : ja_bold)
            if ((lib.faces[kBold] = load_face(p))) break;
        for (auto& p : mono)
            if ((lib.faces[kMono] = load_face(p))) break;
        for (auto& p : latin)
            if (FontFace* f = load_face(p)) {
                lib.fallbacks.push_back(f);
                break;
            }
        if (!lib.faces[kRegular] && !lib.fallbacks.empty()) lib.faces[kRegular] = lib.fallbacks[0];  // no Japanese font: Latin only
        lib.ok = lib.faces[kRegular] != nullptr;
        for (int k = 1; k < kStyles; k++)
            if (!lib.faces[k]) lib.faces[k] = k == kBoldItalic && lib.faces[kBold] ? lib.faces[kBold] : lib.faces[kRegular];
        if (lib.ok)
            WV_LOGI("fonts: %s (bold %s), %zu fallback(s)", lib.faces[kRegular]->path.c_str(),
                    lib.faces[kBold] == lib.faces[kRegular] ? "synthetic" : lib.faces[kBold]->path.c_str(), lib.fallbacks.size());
        else
            WV_LOGW("no font found (install fonts-ipaexfont or fonts-noto-cjk, or set SOA_WEBVIEW_FONT=/path/to/font.ttf): pages draw no text");
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
    FontLib& lib = fonts();
    int g = stbtt_FindGlyphIndex(&f.face->info, (int)cp);
    if (g || cp < 0x20) return {f.face, g, stbtt_ScaleForMappingEmToPixels(&f.face->info, f.px)};
    for (FontFace* fb : lib.fallbacks)
        if (int h = stbtt_FindGlyphIndex(&fb->info, (int)cp)) return {fb, h, stbtt_ScaleForMappingEmToPixels(&fb->info, f.px)};
    return {f.face, 0, stbtt_ScaleForMappingEmToPixels(&f.face->info, f.px)};
}

}  // namespace soa::webview
