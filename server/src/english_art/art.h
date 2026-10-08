#pragma once
// The pieces of the English art generator (soaserver/english_art.h), internal to
// server/src/english_art and its tests: the game font, the recipe, the text renderer, the cover.
// All arithmetic is integer, so a build gives the same bytes on every platform.
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include <soa/aska_image.h>

#include "soaserver/english_art.h"

namespace soa {
class FileTree;
}

namespace soa::server::english_art {

using Bytes = std::vector<uint8_t>;

struct Rgba {
    uint8_t r = 0, g = 0, b = 0, a = 0;
    bool operator==(const Rgba& o) const { return r == o.r && g == o.g && b == o.b && a == o.a; }
};

struct Rect {
    int x = 0, y = 0, w = 0, h = 0;
};

// An RGBA8 picture, straight alpha, rows top-down.
struct Canvas {
    int w = 0, h = 0;
    Bytes px;
    Canvas() = default;
    Canvas(int w_, int h_) : w(w_), h(h_), px((size_t)w_ * h_ * 4, 0) {}
    uint8_t* at(int x, int y) { return &px[((size_t)y * w + x) * 4]; }
    const uint8_t* at(int x, int y) const { return &px[((size_t)y * w + x) * 4]; }
};

// An 8-bit coverage map (the text's alpha before colouring).
struct Coverage {
    int w = 0, h = 0;
    Bytes a;
    Coverage() = default;
    Coverage(int w_, int h_) : w(w_), h(h_), a((size_t)w_ * h_, 0) {}
    uint8_t get(int x, int y) const { return x < 0 || y < 0 || x >= w || y >= h ? 0 : a[(size_t)y * w + x]; }
};

// ---- the game font (Font/etc2/font.fpk; docs/english.md 3.1) -----------------------------------
// The ISF image holds fontData.bin (u32 24, u32 24, u32 count, then count BMFont-style records of
// ten i32: id, x, y, w, h, xoff, yoff, xadvance, page, chnl) and font_0.aif (one 2048x2048 ETC2
// RGBA8 page, white glyphs on alpha). The client keys glyphs by the id's low 16 bits
// (CBitmapFontManager::RegistryFont) and draws '?' for a missing one.
struct Glyph {
    int x = 0, y = 0, w = 0, h = 0, xoff = 0, yoff = 0, adv = 0;
};
class Font {
public:
    int size = 24;  // the glyphs' design size (the header's first word)
    std::map<uint32_t, Glyph> glyphs;
    int aw = 0, ah = 0;
    Bytes alpha;  // the page's alpha, aw * ah

    // From the font file's decrypted bytes (ADLD removed): SLZ, ISF, the table and the page.
    bool load(const Bytes& fpk_plain, std::string* err);
    // The glyph of a code point, or '?' (nullptr when the font has neither).
    const Glyph* find(uint32_t cp) const;
    uint8_t page_alpha(int x, int y) const { return x < 0 || y < 0 || x >= aw || y >= ah ? 0 : alpha[(size_t)y * aw + x]; }
};

// ---- recipes ------------------------------------------------------------------------------------
struct Style {
    int size = 18;                 // the text's height in pixels (the font's 24 px scaled)
    int bold = 0;                  // widen strokes by this many font pixels (before scaling)
    int tracking = 0;              // extra advance per character, in font pixels
    int leading = 0;               // extra space between lines ("\n" in the text), in font pixels
    int squeeze = 70;              // narrowest horizontal scale (percent) to fit the box, before shrinking
    Rgba fill{255, 255, 255, 255};
    Rgba outline;                  // drawn under the fill, outline_width px around it
    int outline_width = 0;
    Rgba glow;                     // a soft halo under everything: the outline's shape spread by glow_radius
    int glow_radius = 0;
    Rgba shadow;                   // the outlined text again, shadow_dx / shadow_dy px away
    int shadow_dx = 0, shadow_dy = 0;
    std::string cover = "inpaint";  // what replaces the Japanese: "inpaint" (smooth fill from the box's
                                    // surroundings), "fill" (cover_color), "shade" (cover_color laid
                                    // over the picture, faded edges) or "none"
    Rgba cover_color;
    std::string align = "center";  // horizontal: left, center, right (vertical: centred on the ink)
    int dx = 0, dy = 0;            // a nudge of the text, in pixels
};

struct Label {
    std::vector<std::string> sprites;  // the atlas sprites (.csv names) it applies to; empty: the whole image
    Rect box;                          // the text box, relative to each sprite (or the image)
    Rect cover;                        // the area to clear (default: the box)
    bool has_cover = false;
    std::string text;                  // the English (UTF-8; the font's glyphs only)
    std::string jp;                    // the Japanese it replaces (documentation)
    Style style;
};

struct Recipe {
    std::string source;                // the download's file, e.g. "UI/etc2/common.csf" (the first of sources)
    std::vector<std::string> sources;  // "source", or "sources": the same labels on several files (one -en file each)
    std::vector<Label> labels;
};

// Parses a recipe file (JSON; the format is docs/english.md "English UI art"). False and *err on a
// syntax error, an unknown key, or a value of the wrong type.
bool parse_recipe(const std::string& json, Recipe& out, std::string* err);

// ---- drawing ------------------------------------------------------------------------------------
// The text's coverage at the style's size, squeezed (down to style.squeeze %) and then shrunk to
// fit max_w pixels.
Coverage render_text(const Font& font, const std::string& utf8, const Style& style, int max_w);
// Replaces `area` (clipped to `clip`) with a smooth fill from the pixels around it inside `clip`
// (a discrete Laplace solve on premultiplied colour).
void inpaint(Canvas& c, Rect area, Rect clip);
// Draws a label's text (glow, shadow, outline, fill) into `box`, clipped to `clip`.
void draw_text(Canvas& c, const Coverage& text, const Style& style, Rect box, Rect clip);
// Applies one label at the origin (ox, oy) of a sprite of size (sw, sh): the cover, then the text.
// `shape` (when given): the unedited picture, whose alpha a "shade" cover keeps (a band never covers
// the picture's transparent margin, nor leaves a hole where an earlier inpaint thinned the alpha).
void apply_label(Canvas& c, const Font& font, const Label& label, Rect sprite, const Canvas* shape = nullptr);

// ---- the file -----------------------------------------------------------------------------------
// The -en file of `recipe` from the source file's decrypted bytes (ADLD removed): its image(s)
// decoded, the labels drawn, the changed blocks re-encoded, the ISF sums updated, SLZ'd and ADLD
// XOR'd under `en_rel`. *png_out (when not null) gets the edited picture. False and *err on failure.
bool apply_recipe(const Recipe& recipe, const Bytes& source_plain, const Font& font, const std::string& en_rel, Bytes& out, Canvas* png_out,
                  std::string* err);

// ---- the layout labels (docs/english.md 7.14) ---------------------------------------------------
// Called with the text of each LabelText / ButtonText str value of a node tree (the .msgp member of
// a scene); returns its replacement, or nullptr to keep it.
using LabelFn = std::function<const std::string*(const std::string& text)>;
// Walks the msgpack stream `msgp`; with `out`, writes it again with the replaced labels (the smallest
// str header for a new text) and every other byte as it was. *replaced: the labels fn replaced.
// False and *err on a malformed stream.
bool rewrite_labels(const Bytes& msgp, const LabelFn& fn, Bytes* out, size_t* replaced = nullptr, std::string* err = nullptr);
// The labels of `labels` a scene's node trees have (the scene's decrypted bytes; only the members up
// to its last .msgp are decoded).
bool scene_labels(const Bytes& source_plain, const LabelTable& labels, LabelTable& found, std::string* err = nullptr);
// A scene's decoded ISF image with its node trees' labels replaced (the image laid out again,
// aska::isf_repack); unchanged when none matches. *replaced: how many.
bool edit_labels(Bytes& isf, const LabelTable& labels, size_t* replaced, std::string* err);
// The recipe's labels drawn into the decoded image `isf` (the changed blocks re-encoded, the sum updated).
bool edit_image(const Recipe& recipe, Bytes& isf, const Font& font, Canvas* png_out, std::string* err);
// The -en file of a source: the recipe's image edit (when not null), then the layout labels (when
// not null), SLZ'd and ADLD XOR'd under `en_rel`.
bool apply_scene(const Recipe* recipe, const LabelTable* labels, const Bytes& source_plain, const Font& font, const std::string& en_rel, Bytes& out,
                 Canvas* png_out, size_t* replaced, std::string* err);

}  // namespace soa::server::english_art
