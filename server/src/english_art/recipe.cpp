// The English art recipes (art.h, parse_recipe): JSON files, one per source image (or per group of
// images with the same labels: "sources")
// (standin-assets-en/recipes/*.json; the format is docs/english.md "English UI art").
//
//   {"source": "UI/etc2/common.csf",
//    "styles": {"footer": {"size": 17, "bold": 1, "fill": "#ffffff", "outline": "#0b3a78", ...}},
//    "labels": [{"sprites": ["menubtn_home_on.png", ...], "box": [x, y, w, h], "cover": [x, y, w, h],
//                "jp": "ホーム", "text": "Home", "style": "footer", "size": 16, ...}]}
//
// A label takes its named style, then any style key of its own. Keys starting with "_" and "note"
// are comments; any other unknown key is an error (a typo would otherwise be silently ignored).
#include <nlohmann/json.hpp>

#include <cstdio>

#include "english_art/art.h"

namespace soa::server::english_art {
namespace {

using json = nlohmann::json;

struct Fail {
    std::string why;
};

bool comment_key(const std::string& k) { return k == "note" || (!k.empty() && k[0] == '_'); }

int as_int(const json& v, const std::string& what) {
    if (!v.is_number_integer()) throw Fail{what + ": an integer expected"};
    return v.get<int>();
}

// "#rrggbb" or "#rrggbbaa".
Rgba as_color(const json& v, const std::string& what) {
    if (!v.is_string()) throw Fail{what + ": a colour \"#rrggbb[aa]\" expected"};
    std::string s = v.get<std::string>();
    unsigned r, g, b, a = 255;
    int n = 0;
    if (s.size() == 7 && sscanf(s.c_str(), "#%2x%2x%2x%n", &r, &g, &b, &n) == 3 && n == 7) return {(uint8_t)r, (uint8_t)g, (uint8_t)b, 255};
    if (s.size() == 9 && sscanf(s.c_str(), "#%2x%2x%2x%2x%n", &r, &g, &b, &a, &n) == 4 && n == 9)
        return {(uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a};
    throw Fail{what + ": bad colour \"" + s + "\""};
}

Rect as_rect(const json& v, const std::string& what) {
    if (!v.is_array() || v.size() != 4) throw Fail{what + ": [x, y, w, h] expected"};
    Rect r{as_int(v[0], what), as_int(v[1], what), as_int(v[2], what), as_int(v[3], what)};
    if (r.w <= 0 || r.h <= 0) throw Fail{what + ": an empty rectangle"};
    return r;
}

std::string as_string(const json& v, const std::string& what) {
    if (!v.is_string()) throw Fail{what + ": a string expected"};
    return v.get<std::string>();
}

// One style key into `st`; false when `k` isn't a style key.
bool style_key(Style& st, const std::string& k, const json& v, const std::string& where) {
    std::string w = where + "." + k;
    if (k == "size") st.size = as_int(v, w);
    else if (k == "bold") st.bold = as_int(v, w);
    else if (k == "tracking") st.tracking = as_int(v, w);
    else if (k == "leading") st.leading = as_int(v, w);
    else if (k == "squeeze") st.squeeze = as_int(v, w);
    else if (k == "fill") st.fill = as_color(v, w);
    else if (k == "outline") st.outline = as_color(v, w);
    else if (k == "outline_width") st.outline_width = as_int(v, w);
    else if (k == "glow") st.glow = as_color(v, w);
    else if (k == "glow_radius") st.glow_radius = as_int(v, w);
    else if (k == "shadow") st.shadow = as_color(v, w);
    else if (k == "shadow_dx") st.shadow_dx = as_int(v, w);
    else if (k == "shadow_dy") st.shadow_dy = as_int(v, w);
    else if (k == "clear") {
        st.cover = as_string(v, w);
        if (st.cover != "inpaint" && st.cover != "fill" && st.cover != "none") throw Fail{w + ": inpaint, fill or none"};
    } else if (k == "clear_color") st.cover_color = as_color(v, w);
    else if (k == "align") {
        st.align = as_string(v, w);
        if (st.align != "left" && st.align != "center" && st.align != "right") throw Fail{w + ": left, center or right"};
    } else if (k == "dx") st.dx = as_int(v, w);
    else if (k == "dy") st.dy = as_int(v, w);
    else return false;
    if (st.size <= 0 || st.size > 200) throw Fail{where + ".size: 1..200"};
    if (st.bold < 0 || st.bold > 4 || st.outline_width < 0 || st.outline_width > 8 || st.glow_radius < 0 || st.glow_radius > 16)
        throw Fail{where + ": bold 0..4, outline_width 0..8, glow_radius 0..16"};
    return true;
}

}  // namespace

bool parse_recipe(const std::string& text, Recipe& out, std::string* err) {
    out = Recipe();
    try {
        json j = json::parse(text);
        if (!j.is_object()) throw Fail{"a JSON object expected"};
        std::map<std::string, Style> styles;
        if (j.contains("styles")) {
            if (!j["styles"].is_object()) throw Fail{"styles: an object expected"};
            for (auto& [name, sv] : j["styles"].items()) {
                if (!sv.is_object()) throw Fail{"styles." + name + ": an object expected"};
                Style st;
                for (auto& [k, v] : sv.items())
                    if (!comment_key(k) && !style_key(st, k, v, "styles." + name)) throw Fail{"styles." + name + ": unknown key " + k};
                styles[name] = st;
            }
        }
        for (auto& [k, v] : j.items()) {
            if (comment_key(k) || k == "styles") continue;
            if (k == "source") out.sources.push_back(as_string(v, "source"));
            else if (k == "sources") {
                if (!v.is_array() || v.empty()) throw Fail{"sources: a non-empty array expected"};
                for (auto& sv : v) out.sources.push_back(as_string(sv, "sources"));
            } else if (k == "labels") {
                if (!v.is_array()) throw Fail{"labels: an array expected"};
                for (size_t i = 0; i < v.size(); i++) {
                    const json& lv = v[i];
                    std::string where = "labels[" + std::to_string(i) + "]";
                    if (!lv.is_object()) throw Fail{where + ": an object expected"};
                    Label l;
                    if (lv.contains("style")) {
                        std::string name = as_string(lv["style"], where + ".style");
                        if (!styles.count(name)) throw Fail{where + ".style: no style " + name};
                        l.style = styles[name];
                    }
                    bool has_box = false;
                    for (auto& [lk, lval] : lv.items()) {
                        if (comment_key(lk) || lk == "style") continue;
                        if (lk == "sprites") {
                            if (!lval.is_array()) throw Fail{where + ".sprites: an array expected"};
                            for (auto& s : lval) l.sprites.push_back(as_string(s, where + ".sprites"));
                        } else if (lk == "box") {
                            l.box = as_rect(lval, where + ".box");
                            has_box = true;
                        } else if (lk == "cover") {
                            l.cover = as_rect(lval, where + ".cover");
                            l.has_cover = true;
                        } else if (lk == "text") {
                            l.text = as_string(lval, where + ".text");
                        } else if (lk == "jp") {
                            l.jp = as_string(lval, where + ".jp");
                        } else if (!style_key(l.style, lk, lval, where)) {
                            throw Fail{where + ": unknown key " + lk};
                        }
                    }
                    if (!has_box) throw Fail{where + ": no box"};
                    out.labels.push_back(l);
                }
            } else {
                throw Fail{"unknown key " + k};
            }
        }
        if (out.sources.empty()) throw Fail{"no source"};
        for (auto& src : out.sources)
            if (src.empty() || src.find("..") != std::string::npos || src[0] == '/') throw Fail{"source: a relative path in the download"};
        out.source = out.sources[0];
        return true;
    } catch (const Fail& f) {
        if (err) *err = f.why;
    } catch (const json::exception& e) {
        if (err) *err = e.what();
    }
    return false;
}

}  // namespace soa::server::english_art
