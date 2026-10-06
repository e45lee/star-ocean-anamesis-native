// The game's bitmap font for the English art (art.h, Font; docs/english.md 3.1).
#include <cstring>

#include "english_art/art.h"

namespace soa::server::english_art {
namespace {

int32_t rd_i32(const uint8_t* p) { return (int32_t)(p[0] | p[1] << 8 | p[2] << 16 | (uint32_t)p[3] << 24); }

}  // namespace

bool Font::load(const Bytes& fpk_plain, std::string* err) {
    auto fail = [&](const char* why) {
        if (err) *err = std::string("font: ") + why;
        return false;
    };
    Bytes d;
    std::string why;
    if (!aska::slz_decode(fpk_plain, d, &why)) return fail(why.c_str());
    const aska::IsfEntry *table = nullptr, *page = nullptr;
    auto entries = aska::isf_entries(d);
    for (auto& e : entries) {
        if (e.name == "fontData.bin") table = &e;
        if (e.name == "font_0.aif") page = &e;
    }
    if (!table || !page) return fail("no fontData.bin / font_0.aif in the ISF");
    if (table->size < 12) return fail("short glyph table");
    const uint8_t* t = &d[table->offset];
    size = rd_i32(t);
    uint32_t count = (uint32_t)rd_i32(t + 8);
    if (size <= 0 || 12 + (uint64_t)count * 40 > table->size) return fail("bad glyph table header");
    glyphs.clear();
    for (uint32_t i = 0; i < count; i++) {
        const uint8_t* r = t + 12 + i * 40;
        Glyph g;
        uint32_t id = (uint32_t)rd_i32(r) & 0xffff;  // (b) RegistryFont keeps the low 16 bits
        g.x = rd_i32(r + 4), g.y = rd_i32(r + 8), g.w = rd_i32(r + 12), g.h = rd_i32(r + 16);
        g.xoff = rd_i32(r + 20), g.yoff = rd_i32(r + 24), g.adv = rd_i32(r + 28);
        glyphs.emplace(id, g);  // the first record of an id wins
    }
    Bytes aif(d.begin() + page->offset, d.begin() + page->offset + page->size);
    auto imgs = aska::find_images(aif);
    if (imgs.empty()) return fail("no image in font_0.aif");
    Bytes rgba;
    if (!aska::decode_image(aif, imgs[0], rgba, &why)) return fail(why.c_str());
    aw = imgs[0].w, ah = imgs[0].h;
    alpha.resize((size_t)aw * ah);
    for (size_t i = 0; i < alpha.size(); i++) alpha[i] = rgba[i * 4 + 3];
    return true;
}

const Glyph* Font::find(uint32_t cp) const {
    auto it = glyphs.find(cp & 0xffff);
    if (it == glyphs.end()) it = glyphs.find('?');  // (b) the client's fallback glyph
    return it == glyphs.end() ? nullptr : &it->second;
}

}  // namespace soa::server::english_art
