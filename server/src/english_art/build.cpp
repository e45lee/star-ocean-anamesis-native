// The English art build (soaserver/english_art.h): each recipe's source from the user's download,
// edited, written as the -en member; cached by a stamp of everything that goes into it.
//
// (d) The -en images are ours (PLAN-english.md Q4): the game's own image with its Japanese text
// cleared and English drawn in the game's font; a source without a recipe stays Japanese (the
// client's per-file fallback, docs/english.md 6.3). The same pass gives the scenes with layout
// labels their -en copy (docs/server-rules.md#english-labels; english.md 7.14).
#include <algorithm>
#include <atomic>
#include <mutex>
#include <thread>
#include <cstdio>
#include <cstring>
#include <set>

#include <soa/file_tree.h>
#include <soa/png.h>

#include "cdn/files.h"
#include "core/log.h"
#include "english_art/art.h"
#include "soa/adld.h"
#include "soaserver/english_art.h"

namespace soa::server::english_art {
namespace {

// Part of every stamp: bump when the generator's output for the same inputs changes.
constexpr const char* kGenerator = "english-art 4";  // 4: the layout labels (english.md 7.14)
constexpr const char* kFontName = "Font/etc2/font.fpk";
constexpr const char* kOutputsList = "outputs.txt";

bool read_text(const std::string& path, std::string& out) {
    Bytes d;
    if (!cdn::files::read_file(path, d)) return false;
    out.assign(d.begin(), d.end());
    return true;
}

bool write_text(const std::string& path, const std::string& s) { return cdn::files::write_file(path, (const uint8_t*)s.data(), s.size()); }

void mkdirs_for(const std::string& path) {
    size_t slash = path.rfind('/');
    if (slash != std::string::npos) cdn::files::mkdirs(path.substr(0, slash));
}

// The sprite table of a Cocos scene: "<name>,x,y,w,h" lines (the atlas member <stem>.csv).
std::map<std::string, Rect> parse_csv(const Bytes& d, const aska::IsfEntry& e) {
    std::map<std::string, Rect> out;
    std::string s((const char*)&d[e.offset], e.size), line;
    size_t p = 0;
    while (p <= s.size()) {
        size_t nl = s.find('\n', p);
        line = s.substr(p, nl == std::string::npos ? std::string::npos : nl - p);
        p = nl == std::string::npos ? s.size() + 1 : nl + 1;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        size_t c1 = line.find(',');
        if (c1 == std::string::npos) continue;
        Rect r;
        if (sscanf(line.c_str() + c1 + 1, "%d,%d,%d,%d", &r.x, &r.y, &r.w, &r.h) == 4) out[line.substr(0, c1)] = r;
    }
    return out;
}

const Rect* find_sprite(const std::map<std::string, Rect>& sprites, const std::string& name) {
    auto it = sprites.find(name);
    if (it == sprites.end()) it = sprites.find(name + ".png");
    return it == sprites.end() ? nullptr : &it->second;
}

}  // namespace

std::string en_name(const std::string& rel) {
    size_t slash = rel.rfind('/'), dot = rel.rfind('.');
    if (dot == std::string::npos || (slash != std::string::npos && dot < slash)) return rel + "-en";
    return rel.substr(0, dot) + "-en" + rel.substr(dot);
}

bool edit_image(const Recipe& recipe, Bytes& d, const Font& font, Canvas* png_out, std::string* err) {
    auto fail = [&](const std::string& why) {
        if (err) *err = why;
        return false;
    };
    std::string why;
    auto entries = aska::isf_entries(d);
    std::map<std::string, Rect> sprites;
    const aska::IsfEntry* image_entry = nullptr;
    for (auto& e : entries) {
        if (e.name.size() > 4 && e.name.compare(e.name.size() - 4, 4, ".csv") == 0) sprites = parse_csv(d, e);
        if (e.name.size() > 4 && e.name.compare(e.name.size() - 4, 4, ".aif") == 0 && !image_entry) image_entry = &e;
    }
    auto imgs = aska::find_images(d);
    if (imgs.empty()) return fail("no image in " + recipe.source);
    const aska::ImageRef& img = imgs[0];  // the atlas (a scene has one) or the image
    if (!aska::block_bytes(img.fmt))
        return fail(recipe.source + ": pixel format " + std::to_string(img.fmt) + " (only ETC2 RGBA8 / RGB8 / RGB8A1 are written)");
    if (image_entry && (img.data < image_entry->offset || img.data + img.data_size > (size_t)image_entry->offset + image_entry->size))
        return fail(recipe.source + ": the image isn't inside the .aif member");
    Canvas canvas(img.w, img.h);
    if (!aska::decode_image(d, img, canvas.px, &why)) return fail(why);
    const Canvas orig = canvas;
    for (size_t i = 0; i < recipe.labels.size(); i++) {
        const Label& l = recipe.labels[i];
        std::vector<Rect> where;
        if (l.sprites.empty()) where.push_back({0, 0, img.w, img.h});
        for (auto& name : l.sprites) {
            const Rect* r = find_sprite(sprites, name);
            if (!r) return fail(recipe.source + ": labels[" + std::to_string(i) + "]: no sprite " + name);
            where.push_back(*r);
        }
        for (auto& r : where) apply_label(canvas, font, l, r, &orig);
    }
    // re-encode only the 4x4 blocks whose pixels changed: everything else keeps the game's bytes
    int bpb = aska::block_bytes(img.fmt), bw = (img.w + 3) / 4, bh = (img.h + 3) / 4;
    for (int by = 0; by < bh; by++)
        for (int bx = 0; bx < bw; bx++) {
            uint8_t blk[16][4];
            bool changed = false;
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++) {
                    int px = std::min(bx * 4 + x, img.w - 1), py = std::min(by * 4 + y, img.h - 1);
                    memcpy(blk[y * 4 + x], canvas.at(px, py), 4);
                    changed |= memcmp(canvas.at(px, py), orig.at(px, py), 4) != 0;
                }
            if (changed) aska::encode_block(img.fmt, blk, &d[img.data + ((size_t)by * bw + bx) * bpb]);
        }
    if (png_out) {  // what the client will draw: the re-encoded pixels
        png_out->w = img.w, png_out->h = img.h;
        aska::decode_image(d, img, png_out->px, nullptr);
    }
    if (image_entry) aska::isf_update_sum(d, *image_entry);
    return true;
}

bool edit_labels(Bytes& d, const LabelTable& labels, size_t* replaced, std::string* err) {
    auto entries = aska::isf_entries(d);
    std::vector<Bytes> fresh(entries.size());
    std::vector<const Bytes*> payloads(entries.size(), nullptr);
    size_t n = 0;
    for (auto& e : entries) {
        if (e.name.size() < 5 || e.name.compare(e.name.size() - 5, 5, ".msgp") != 0) continue;
        Bytes tree(d.begin() + e.offset, d.begin() + e.offset + e.size);
        size_t k = 0;
        std::string why;
        auto fn = [&](const std::string& text) -> const std::string* {
            auto it = labels.find(text);
            return it == labels.end() ? nullptr : &it->second;
        };
        if (!rewrite_labels(tree, fn, &fresh[e.index], &k, &why)) {
            if (err) *err = e.name + ": " + why;
            return false;
        }
        if (k) payloads[e.index] = &fresh[e.index], n += k;
    }
    if (replaced) *replaced = n;
    if (!n) return true;
    Bytes out;
    if (!aska::isf_repack(d, payloads, out, err)) return false;
    d.swap(out);
    return true;
}

bool apply_scene(const Recipe* recipe, const LabelTable* labels, const Bytes& source_plain, const Font& font, const std::string& en_rel, Bytes& out,
                 Canvas* png_out, size_t* replaced, std::string* err) {
    Bytes d;
    std::string why;
    if (replaced) *replaced = 0;
    if (!aska::slz_decode(source_plain, d, &why)) {
        if (err) *err = why;
        return false;
    }
    if (recipe && !edit_image(*recipe, d, font, png_out, err)) return false;
    if (labels && !labels->empty() && !edit_labels(d, *labels, replaced, err)) return false;
    out = adld::encrypt(en_rel, aska::slz_encode(d), adld::kXor);
    return true;
}

bool apply_recipe(const Recipe& recipe, const Bytes& source_plain, const Font& font, const std::string& en_rel, Bytes& out, Canvas* png_out,
                  std::string* err) {
    return apply_scene(&recipe, nullptr, source_plain, font, en_rel, out, png_out, nullptr, err);
}

bool scene_labels(const Bytes& source_plain, const LabelTable& labels, LabelTable& found, std::string* err) {
    found.clear();
    // the node trees come first in a scene: decode the first chunks, then up to the last .msgp
    Bytes d;
    if (!aska::slz_decode(source_plain, d, err, 65536)) return false;
    auto entries = aska::isf_entries(d);
    size_t need = 0;
    for (auto& e : entries)
        if (e.name.size() > 5 && e.name.compare(e.name.size() - 5, 5, ".msgp") == 0) need = std::max(need, (size_t)e.offset + e.size);
    if (entries.empty()) {  // the table itself past the first chunk (not in 3.7.0): the whole file
        if (!aska::slz_decode(source_plain, d, err)) return false;
        entries = aska::isf_entries(d);
    } else if (need > d.size() && !aska::slz_decode(source_plain, d, err, need)) {
        return false;
    }
    for (auto& e : entries) {
        if (e.name.size() < 5 || e.name.compare(e.name.size() - 5, 5, ".msgp") != 0 || (size_t)e.offset + e.size > d.size()) continue;
        Bytes tree(d.begin() + e.offset, d.begin() + e.offset + e.size);
        auto fn = [&](const std::string& text) -> const std::string* {
            auto it = labels.find(text);
            if (it != labels.end()) found[it->first] = it->second;
            return nullptr;
        };
        if (!rewrite_labels(tree, fn, nullptr, nullptr, err)) return false;
    }
    return true;
}

bool build(const Options& opts, Stats* stats, std::string* err) {
    Stats st;
    auto fail = [&](const std::string& why) {
        if (err) *err = why;
        if (stats) *stats = st;
        return false;
    };
    bool have_recipes = !opts.recipes.empty() && cdn::files::is_dir(opts.recipes);
    if (!have_recipes && opts.labels.empty()) return fail("english art: no recipe folder " + opts.recipes + " and no layout labels");
    if (!have_recipes && !opts.recipes.empty()) LOGW("english", "art: no recipe folder %s: only the layout labels", opts.recipes.c_str());
    std::string why;
    auto tree = FileTree::open(opts.download, &why);
    if (!tree) return fail("english art: the download: " + why);
    // the game font: only the recipes draw text (the layout labels are the client's to draw)
    Bytes font_file;
    Font font;
    std::string font_sha;
    if (have_recipes) {
        if (!tree->read(kFontName, font_file)) return fail(std::string("english art: no ") + kFontName + " in the download");
        if (!font.load(adld::decrypt(kFontName, font_file), &why)) return fail("english art: " + why);
        cdn::files::Sha1 fh;
        fh.add(font_file.data(), font_file.size());
        font_sha = fh.hex();
    }
    std::string cache = opts.cache.empty() ? opts.out + ".art-cache" : opts.cache;
    cdn::files::mkdirs(cache);

    // one job per -en file: a recipe's source, a scene with layout labels, or both
    struct Job {
        std::string name;  // the recipe file ("" = labels only)
        bool has_recipe = false;
        Recipe recipe;
        std::string recipe_text, source;
        Bytes src;
        LabelTable labels;  // the scene's labels that get English
        std::string en_rel, key, stamp_path, out_path;
    };
    std::map<std::string, Job> by_out;
    std::vector<std::string> names, recipes;
    if (have_recipes) cdn::files::walk(opts.recipes, "", names);
    for (auto& n : names)
        if (n.size() > 5 && n.compare(n.size() - 5, 5, ".json") == 0) recipes.push_back(n);
    for (auto& name : recipes) {
        st.recipes++;
        std::string text;
        Recipe recipe;
        if (!read_text(opts.recipes + "/" + name, text) || !parse_recipe(text, recipe, &why)) {
            LOGW("english", "art recipe %s: %s", name.c_str(), why.c_str());
            st.failed++;
            continue;
        }
        for (auto& source : recipe.sources) {  // one output per source
            std::string en_rel = en_name(source);
            if (by_out.count(en_rel)) {
                LOGW("english", "art recipe %s: %s has another recipe; skipped", name.c_str(), source.c_str());
                st.failed++;
                continue;
            }
            Bytes src;
            if (!tree->read(source, src)) {
                LOGW("english", "art recipe %s: %s not in the download; its image stays Japanese", name.c_str(), source.c_str());
                st.failed++;
                continue;
            }
            Job& j = by_out[en_rel];
            j.name = name, j.has_recipe = true, j.recipe = recipe, j.recipe.source = source, j.recipe_text = text, j.source = source;
            j.src = std::move(src), j.en_rel = en_rel;
        }
    }
    // the layout labels (docs/server-rules.md#english-labels): every scene of the download (UI/ and
    // TalkScene/ .csf) whose node tree has a label the table translates, found at run time; (b) the
    // client loads the scene's -en copy and draws its trees' LabelText; (d) one file per scene
    if (!opts.labels.empty()) {
        std::vector<std::string> scenes;
        for (const char* dir : {"UI", "TalkScene"})
            for (auto& rel : tree->files(dir))
                if (rel.size() > 4 && rel.compare(rel.size() - 4, 4, ".csf") == 0 && rel.find('-', rel.rfind('/') + 1) == std::string::npos)
                    scenes.push_back(rel);
        std::vector<LabelTable> found(scenes.size());
        std::vector<Bytes> srcs(scenes.size());
        std::atomic<size_t> next{0};
        std::mutex mu;
        auto scan = [&] {
            for (size_t i; (i = next++) < scenes.size();) {
                Bytes src;
                std::string swhy;
                if (!tree->read(scenes[i], src)) continue;
                if (!scene_labels(adld::decrypt(scenes[i], src), opts.labels, found[i], &swhy)) {
                    std::lock_guard<std::mutex> lock(mu);
                    LOGW("english", "labels: %s: %s", scenes[i].c_str(), swhy.c_str());
                    continue;
                }
                if (!found[i].empty()) srcs[i] = std::move(src);
            }
        };
        size_t nt = std::max(1u, std::min(8u, std::thread::hardware_concurrency()));
        std::vector<std::thread> pool;
        for (size_t k = 1; k < nt; k++) pool.emplace_back(scan);
        scan();
        for (auto& t : pool) t.join();
        for (size_t i = 0; i < scenes.size(); i++) {
            if (found[i].empty()) continue;
            std::string en_rel = en_name(scenes[i]);
            Job& j = by_out[en_rel];
            if (!j.has_recipe) j.source = scenes[i], j.src = std::move(srcs[i]), j.en_rel = en_rel;
            j.labels = std::move(found[i]);
            st.label_scenes++;
        }
    }
    std::set<std::string> outputs;
    std::vector<Job*> jobs;
    for (auto& [en_rel, j] : by_out) {
        outputs.insert(en_rel);
        cdn::files::Sha1 h;
        h.add(kGenerator, strlen(kGenerator) + 1);
        if (j.has_recipe) h.add(j.recipe_text.data(), j.recipe_text.size());
        h.add("\0labels\0", 8);
        for (auto& [ja, en] : j.labels) {
            h.add(ja.data(), ja.size() + 1);
            h.add(en.data(), en.size() + 1);
        }
        h.add(j.source.data(), j.source.size() + 1);
        if (j.has_recipe) h.add(font_sha.data(), font_sha.size());
        h.add(j.src.data(), j.src.size());
        j.key = h.hex(), j.stamp_path = cache + "/" + en_rel + ".stamp", j.out_path = opts.out + "/" + en_rel;
        std::string old;
        if (opts.png.empty() && read_text(j.stamp_path, old) && old == j.key && cdn::files::stat_file(j.out_path, nullptr)) {
            st.cached++;
            continue;
        }
        jobs.push_back(&j);
    }
    // the edits, in parallel (each output is independent: the same bytes in any order)
    std::mutex mu;
    std::atomic<size_t> next{0};
    auto work = [&] {
        for (size_t i; (i = next++) < jobs.size();) {
            Job& j = *jobs[i];
            Bytes out;
            Canvas png;
            std::string jwhy;
            size_t replaced = 0;
            bool ok = apply_scene(j.has_recipe ? &j.recipe : nullptr, &j.labels, adld::decrypt(j.source, j.src), font, j.en_rel, out,
                                  opts.png.empty() || !j.has_recipe ? nullptr : &png, &replaced, &jwhy);
            std::lock_guard<std::mutex> lock(mu);
            if (!ok) {
                LOGW("english", "art %s: %s", j.name.empty() ? j.source.c_str() : j.name.c_str(), jwhy.c_str());
                outputs.erase(j.en_rel);
                st.failed++;
                continue;
            }
            mkdirs_for(j.out_path);
            mkdirs_for(j.stamp_path);
            if (!cdn::files::write_file(j.out_path, out.data(), out.size()) || !write_text(j.stamp_path, j.key)) {
                LOGW("english", "art: cannot write %s", j.out_path.c_str());
                st.failed++;
                continue;
            }
            if (!opts.png.empty() && j.has_recipe) {
                std::string p = opts.png + "/" + j.en_rel + ".png";
                mkdirs_for(p);
                if (!soa::png_write(p, png.w, png.h, 4, png.px.data())) LOGW("english", "art: cannot write %s", p.c_str());
            }
            st.built++;
            st.labels_replaced += replaced;
            LOGI("english", "art: %s (%zu image labels, %zu layout labels, %zu bytes)", j.en_rel.c_str(), j.has_recipe ? j.recipe.labels.size() : 0,
                 replaced, out.size());
        }
    };
    size_t n = std::min<size_t>(jobs.size(), std::max(1u, std::min(8u, std::thread::hardware_concurrency())));
    std::vector<std::thread> pool;
    for (size_t k = 1; k < n; k++) pool.emplace_back(work);
    work();
    for (auto& t : pool) t.join();
    // the -en files of recipes that are gone (listed by the previous build) are removed
    std::string list;
    if (read_text(cache + "/" + kOutputsList, list)) {
        size_t p = 0;
        while (p < list.size()) {
            size_t nl = list.find('\n', p);
            std::string rel = list.substr(p, nl == std::string::npos ? std::string::npos : nl - p);
            p = nl == std::string::npos ? list.size() : nl + 1;
            if (rel.empty() || outputs.count(rel) || rel.find("..") != std::string::npos) continue;
            if (::remove((opts.out + "/" + rel).c_str()) == 0) st.removed++;
            ::remove((cache + "/" + rel + ".stamp").c_str());
        }
    }
    std::string now;
    for (auto& o : outputs) now += o + "\n";
    write_text(cache + "/" + kOutputsList, now);
    if (stats) *stats = st;
    return true;
}

bool check_roundtrip(const std::string& download, size_t* scenes, size_t* trees, std::string* err) {
    std::string why;
    auto tree = FileTree::open(download, &why);
    if (!tree) {
        if (err) *err = "the download: " + why;
        return false;
    }
    size_t ns = 0, nt = 0;
    std::string bad;
    for (const char* dir : {"UI", "TalkScene"})
        for (auto& rel : tree->files(dir)) {
            if (rel.size() < 5 || rel.compare(rel.size() - 4, 4, ".csf") != 0) continue;
            Bytes src, d, again, tr;
            if (!tree->read(rel, src) || !aska::slz_decode(adld::decrypt(rel, src), d, &why)) {
                bad += rel + ": " + why + "\n";
                continue;
            }
            ns++;
            if (!aska::isf_repack(d, {}, again, &why) || again != d) bad += rel + ": the ISF repack differs " + why + "\n";
            for (auto& e : aska::isf_entries(d)) {
                if (e.name.size() < 5 || e.name.compare(e.name.size() - 5, 5, ".msgp") != 0) continue;
                nt++;
                Bytes t(d.begin() + e.offset, d.begin() + e.offset + e.size);
                if (aska::isf_payload_sum(d, e) != (uint32_t)(d[16 + e.index * 16 + 12] | d[16 + e.index * 16 + 13] << 8 |
                                                              d[16 + e.index * 16 + 14] << 16 | (uint32_t)d[16 + e.index * 16 + 15] << 24))
                    bad += rel + ": " + e.name + ": the sum isn't the payload's\n";
                auto keep = [](const std::string&) -> const std::string* { return nullptr; };
                if (!rewrite_labels(t, keep, &tr, nullptr, &why) || tr != t) bad += rel + ": " + e.name + ": the label walk differs " + why + "\n";
            }
        }
    if (scenes) *scenes = ns;
    if (trees) *trees = nt;
    if (!bad.empty() && err) *err = bad;
    return bad.empty();
}

}  // namespace soa::server::english_art
