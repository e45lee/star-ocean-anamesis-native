// Unit tests of the English art generator (soaserver/english_art.h; --selftest "english-art/"):
// recipes, the drawing on a synthetic font and picture, and, with the 3.7.0 download in work/, a
// recipe applied to the real common.csf (only the labels' blocks change, the scene's other members
// stay byte-identical, two builds give the same bytes, the second build is a cache hit).
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <string>

#include <soa/aska_image.h>
#include <soa/file_tree.h>
#include <soa/paths.h>

#include "cdn/files.h"
#include "english_art/art.h"
#include "soaserver/adld.h"
#include "soaserver/config.h"
#include "soaserver/english_art.h"
#include "soaserver/native_test.h"

namespace soa::server::english_art {
namespace {

// A font of two glyphs: 'A' (a 10x16 solid block) and '?' (a 6x16 one), advances 12 and 8.
Font test_font() {
    Font f;
    f.size = 24;
    f.aw = 32, f.ah = 32;
    f.alpha.assign(32 * 32, 0);
    for (int y = 0; y < 16; y++)
        for (int x = 0; x < 16; x++) f.alpha[y * 32 + x] = 255;
    f.glyphs['A'] = {0, 0, 10, 16, 1, 4, 12};
    f.glyphs['?'] = {0, 0, 6, 16, 1, 4, 8};
    return f;
}

Canvas test_canvas() {
    Canvas c(64, 48);
    for (int y = 0; y < c.h; y++)
        for (int x = 0; x < c.w; x++) {
            uint8_t* p = c.at(x, y);
            p[0] = (uint8_t)(x * 4), p[1] = (uint8_t)(y * 5), p[2] = 100, p[3] = 255;
        }
    return c;
}

}  // namespace

NATIVE_TEST("english-art/recipe-parse") {
    Recipe r;
    std::string err;
    const char* ok = R"({"note": "x", "source": "UI/etc2/common.csf",
        "styles": {"s": {"size": 17, "fill": "#ff8000", "glow": "#00b4ffc0", "glow_radius": 2, "clear": "fill"}},
        "labels": [{"jp": "ホーム", "text": "Home", "sprites": ["a.png"], "box": [1, 2, 30, 10], "cover": [0, 1, 32, 12],
                    "style": "s", "size": 15, "_why": "comment"}]})";
    if (!parse_recipe(ok, r, &err)) t.fail("a valid recipe: %s", err.c_str());
    t.expect_eq(r.source, std::string("UI/etc2/common.csf"), "source");
    if (r.labels.size() == 1) {
        const Label& l = r.labels[0];
        t.expect_eq(l.style.size, 15, "the label's own size wins over its style");
        t.expect_eq(l.style.fill == Rgba{255, 128, 0, 255}, true, "the style's fill");
        t.expect_eq(l.style.glow.a, (uint8_t)0xc0, "#rrggbbaa");
        t.expect_eq(l.style.cover, std::string("fill"), "clear");
        t.expect_eq(l.has_cover && l.cover.w == 32 && l.box.x == 1 && l.sprites.size() == 1, true, "box / cover / sprites");
        t.expect_eq(l.text, std::string("Home"), "text");
    } else {
        t.fail("labels: %zu", r.labels.size());
    }
    const char* bad[] = {
        R"({"source": "a.csf", "labels": [{"box": [0, 0, 1, 1], "colour": "#fff"}]})",          // unknown key
        R"({"source": "a.csf", "labels": [{"box": [0, 0, 1, 1], "fill": "white"}]})",           // bad colour
        R"({"source": "a.csf", "labels": [{"text": "x"}]})",                                    // no box
        R"({"source": "a.csf", "labels": [{"box": [0, 0, 0, 1]}]})",                            // empty box
        R"({"source": "a.csf", "labels": [{"box": [0, 0, 1, 1], "style": "nope"}]})",           // no such style
        R"({"labels": []})",                                                                    // no source
        R"({"source": "../x.csf", "labels": []})",                                              // a path out of the download
        R"({"source": "a.csf", "labels": [{"box": [0, 0, 1, 1], "clear": "erase"}]})",          // bad mode
        R"({"source": "a.csf",)",                                                               // JSON syntax
    };
    for (const char* b : bad)
        if (parse_recipe(b, r, &err)) t.fail("accepted: %s", b);
}

NATIVE_TEST("english-art/en-name") {
    t.expect_eq(en_name("UI/etc2/home.csf"), std::string("UI/etc2/home-en.csf"), "csf");
    t.expect_eq(en_name("Image/etc2/banner_x.aif"), std::string("Image/etc2/banner_x-en.aif"), "aif");
    t.expect_eq(en_name("a.b/c"), std::string("a.b/c-en"), "no extension");
}

NATIVE_TEST("english-art/draw") {
    Font font = test_font();
    Style st;
    st.size = 24;
    Coverage a = render_text(font, "AA", st, 0);
    // two glyphs, advance 12: ink 1..10 and 13..22 of a 24 x 24 cell (yoff 4, h 16)
    t.expect_eq(a.w == 24 && a.h == 24, true, "native size");
    t.expect_eq(a.get(0, 10) == 0 && a.get(1, 10) == 255 && a.get(11, 10) == 0 && a.get(13, 10) == 255 && a.get(5, 3) == 0 && a.get(5, 4) == 255,
                true, "glyph placement");
    Coverage two = render_text(font, "A\nAA", st, 0);  // two lines, the first centred over the second
    t.expect_eq(two.w == 24 && two.h == 48 && two.get(1, 10) == 0 && two.get(7, 10) == 255 && two.get(1, 34) == 255, true, "two lines");
    Coverage q = render_text(font, "\xe3\x83\x9b", st, 0);  // ホ: not in the font -> '?'
    t.expect_eq(q.w, 8, "a missing glyph draws as '?'");
    st.size = 12;
    Coverage half = render_text(font, "AA", st, 0);
    t.expect_eq(half.w == 12 && half.h == 12, true, "scaled to the size");
    Coverage fit = render_text(font, "AAAA", st, 20);
    t.expect_eq(fit.w, 20, "squeezed to the box");
    st.squeeze = 90;
    Coverage shrunk = render_text(font, "AAAA", st, 10);
    t.expect_eq(shrunk.w == 10 && shrunk.h < 12, true, "shrunk when squeezing is not enough");

    // a label: the cover and the text stay inside the sprite; the same input, the same pixels
    Label l;
    l.box = {4, 4, 24, 12};
    l.text = "AA";
    l.style.size = 12;
    l.style.outline = {0, 0, 0, 255};
    l.style.outline_width = 1;
    l.style.glow = {0, 128, 255, 200};
    l.style.glow_radius = 2;
    Canvas c1 = test_canvas(), c2 = test_canvas();
    const Canvas orig = test_canvas();
    Rect sprite{8, 8, 32, 24};
    apply_label(c1, font, l, sprite);
    apply_label(c2, font, l, sprite);
    t.expect_eq(c1.px, c2.px, "deterministic");
    bool outside_same = true, inside_changed = false;
    for (int y = 0; y < c1.h; y++)
        for (int x = 0; x < c1.w; x++) {
            bool in = x >= sprite.x && y >= sprite.y && x < sprite.x + sprite.w && y < sprite.y + sprite.h;
            bool same = !memcmp(c1.at(x, y), orig.at(x, y), 4);
            if (!in && !same) outside_same = false;
            if (in && !same) inside_changed = true;
        }
    t.expect_eq(outside_same, true, "nothing drawn outside the sprite");
    t.expect_eq(inside_changed, true, "the label is drawn");
    // the text's fill (white) is in the first glyph: ink 12 x 8 px centred in the 24 x 12 box
    const uint8_t* mid = c1.at(sprite.x + 12, sprite.y + 10);
    t.expect_eq(mid[0] == 255 && mid[1] == 255 && mid[2] == 255, true, "the fill colour");

    // inpaint of a flat area surrounded by one colour gives that colour
    Canvas flat(20, 20);
    for (int i = 0; i < 400; i++) flat.px[i * 4] = 10, flat.px[i * 4 + 1] = 20, flat.px[i * 4 + 2] = 30, flat.px[i * 4 + 3] = 255;
    for (int y = 5; y < 10; y++)
        for (int x = 5; x < 15; x++) flat.at(x, y)[0] = 250;
    inpaint(flat, {5, 5, 10, 5}, {0, 0, 20, 20});
    bool uniform = true;
    for (int i = 0; i < 400; i++) uniform &= flat.px[i * 4] == 10 && flat.px[i * 4 + 3] == 255;
    t.expect_eq(uniform, true, "inpaint restores a flat surround");
}

NATIVE_TEST("english-art/common-csf") {
    std::string dl = find_repo_file("work/download-3.7.0"), recipes = find_repo_file("standin-assets-en/recipes");
    if (dl.empty() || recipes.empty()) {
        t.skip("work/download-3.7.0 or standin-assets-en/recipes not found (the download is local data)");
        return;
    }
    auto tree = FileTree::open(dl);
    Bytes font_file, src;
    if (!tree || !tree->read("Font/etc2/font.fpk", font_file) || !tree->read("UI/etc2/common.csf", src)) {
        t.fail("the download lacks the font or common.csf");
        return;
    }
    Font font;
    std::string err, text;
    if (!font.load(adld::decrypt("Font/etc2/font.fpk", font_file), &err)) t.fail("%s", err.c_str());
    t.expect_eq(font.glyphs.count('A') && font.glyphs.size() > 7000, true, "the game font's glyphs");
    Bytes rj;
    if (!cdn::files::read_file(recipes + "/common.json", rj)) {
        t.fail("no common.json recipe");
        return;
    }
    text.assign(rj.begin(), rj.end());
    Recipe recipe;
    if (!parse_recipe(text, recipe, &err)) t.fail("common.json: %s", err.c_str());
    Bytes out1;
    if (!apply_recipe(recipe, adld::decrypt("UI/etc2/common.csf", src), font, "UI/etc2/common-en.csf", out1, nullptr, &err))
        t.fail("%s", err.c_str());
    t.expect_eq(adld::flags_of(out1.data(), out1.size()), adld::kXor, "ADLD XOR");
    Bytes a, b;
    aska::slz_decode(adld::decrypt("UI/etc2/common-en.csf", out1), a);
    aska::slz_decode(adld::decrypt("UI/etc2/common.csf", src), b);
    t.expect_eq(a.size(), b.size(), "the scene keeps its size");
    auto ea = aska::isf_entries(a), eb = aska::isf_entries(b);
    t.expect_eq(ea.size(), eb.size(), "the same members");
    for (size_t i = 0; i < ea.size() && i < eb.size(); i++) {
        bool same = !memcmp(&a[ea[i].offset], &b[eb[i].offset], ea[i].size);
        bool is_aif = ea[i].name.size() > 4 && ea[i].name.substr(ea[i].name.size() - 4) == ".aif";
        if (is_aif == same) t.fail("%s: %s", ea[i].name.c_str(), is_aif ? "unchanged" : "changed");
        if (aska::isf_payload_sum(a, ea[i]) !=
            (uint32_t)(a[16 + i * 16 + 12] | a[16 + i * 16 + 13] << 8 | a[16 + i * 16 + 14] << 16 | (uint32_t)a[16 + i * 16 + 15] << 24))
            t.fail("%s: ISF sum", ea[i].name.c_str());
    }
    // the original file's sums follow the same rule (the rule is the game's files')
    for (auto& e : eb)
        if (aska::isf_payload_sum(b, e) != (uint32_t)(b[16 + e.index * 16 + 12] | b[16 + e.index * 16 + 13] << 8 | b[16 + e.index * 16 + 14] << 16 |
                                                      (uint32_t)b[16 + e.index * 16 + 15] << 24))
            t.fail("3.7.0 %s: the sum rule doesn't hold", e.name.c_str());

    // build(): written, then a cache hit; a removed recipe's output is deleted
    std::string tmp = soa::temp_dir() + "/soa-english-art-test-" + std::to_string(getpid());
    std::string rdir = tmp + "/recipes", out = tmp + "/out";
    cdn::files::mkdirs(rdir);
    cdn::files::write_file(rdir + "/common.json", rj.data(), rj.size());
    Options o{dl, rdir, out, "", ""};
    Stats s1, s2, s3;
    if (!build(o, &s1, &err)) t.fail("build: %s", err.c_str());
    t.expect_eq(s1.built == 1 && s1.failed == 0, true, "first build writes the file");
    Bytes built;
    cdn::files::read_file(out + "/UI/etc2/common-en.csf", built);
    t.expect_eq(built, out1, "two builds (build() and apply_recipe), the same bytes");
    build(o, &s2, &err);
    t.expect_eq(s2.built == 0 && s2.cached == 1, true, "second build is a cache hit");
    ::remove((rdir + "/common.json").c_str());
    build(o, &s3, &err);
    t.expect_eq(s3.removed, (size_t)1, "a removed recipe's output is deleted");
    t.expect_eq(cdn::files::stat_file(out + "/UI/etc2/common-en.csf", nullptr), false, "deleted");
    for (const char* f : {"/out.art-cache/outputs.txt"}) ::remove((tmp + f).c_str());
    for (const char* d : {"/out/UI/etc2", "/out/UI", "/out", "/out.art-cache/UI/etc2", "/out.art-cache/UI", "/out.art-cache", "/recipes", ""})
        ::rmdir((tmp + d).c_str());
}

}  // namespace soa::server::english_art
