// The English art build (soaserver/english_art.h): each recipe's source from the user's download,
// edited, written as the -en member; cached by a stamp of everything that goes into it.
//
// (d) The -en images are ours (PLAN-english.md Q4): the game's own image with its Japanese text
// cleared and English drawn in the game's font; a source without a recipe stays Japanese (the
// client's per-file fallback, docs/english.md 6.3).
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
#include "soaserver/adld.h"
#include "soaserver/english_art.h"

namespace soa::server::english_art {
namespace {

// Part of every stamp: bump when the generator's output for the same inputs changes.
constexpr const char* kGenerator = "english-art 2";
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

bool apply_recipe(const Recipe& recipe, const Bytes& source_plain, const Font& font, const std::string& en_rel, Bytes& out, Canvas* png_out,
                  std::string* err) {
    auto fail = [&](const std::string& why) {
        if (err) *err = why;
        return false;
    };
    Bytes d;
    std::string why;
    if (!aska::slz_decode(source_plain, d, &why)) return fail(why);
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
    if (img.fmt != aska::kEtc2Rgba8 && img.fmt != aska::kEtc2Rgb8)
        return fail(recipe.source + ": pixel format " + std::to_string(img.fmt) + " (only ETC2 RGBA8 / RGB8 are written)");
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
        for (auto& r : where) apply_label(canvas, font, l, r);
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
    out = adld::encrypt(en_rel, aska::slz_encode(d), adld::kXor);
    return true;
}

bool build(const Options& opts, Stats* stats, std::string* err) {
    Stats st;
    auto fail = [&](const std::string& why) {
        if (err) *err = why;
        if (stats) *stats = st;
        return false;
    };
    if (!cdn::files::is_dir(opts.recipes)) return fail("english art: no recipe folder " + opts.recipes);
    std::string why;
    auto tree = FileTree::open(opts.download, &why);
    if (!tree) return fail("english art: the download: " + why);
    Bytes font_file;
    if (!tree->read(kFontName, font_file)) return fail(std::string("english art: no ") + kFontName + " in the download");
    Font font;
    if (!font.load(adld::decrypt(kFontName, font_file), &why)) return fail("english art: " + why);
    cdn::files::Sha1 fh;
    fh.add(font_file.data(), font_file.size());
    std::string font_sha = fh.hex();
    std::string cache = opts.cache.empty() ? opts.out + ".art-cache" : opts.cache;
    cdn::files::mkdirs(cache);

    std::vector<std::string> names, recipes;
    cdn::files::walk(opts.recipes, "", names);
    for (auto& n : names)
        if (n.size() > 5 && n.compare(n.size() - 5, 5, ".json") == 0) recipes.push_back(n);
    std::set<std::string> outputs;
    struct Job {
        std::string name;
        Recipe recipe;
        Bytes src;
        std::string en_rel, key, stamp_path, out_path;
    };
    std::vector<Job> jobs;
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
            Recipe one = recipe;
            one.source = source;
            std::string en_rel = en_name(source);
            if (outputs.count(en_rel)) {
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
            outputs.insert(en_rel);
            cdn::files::Sha1 h;
            h.add(kGenerator, strlen(kGenerator) + 1);
            h.add(text.data(), text.size());
            h.add(source.data(), source.size() + 1);
            h.add(font_sha.data(), font_sha.size());
            h.add(src.data(), src.size());
            std::string key = h.hex(), stamp_path = cache + "/" + en_rel + ".stamp", out_path = opts.out + "/" + en_rel, old;
            if (opts.png.empty() && read_text(stamp_path, old) && old == key && cdn::files::stat_file(out_path, nullptr)) {
                st.cached++;
                continue;
            }
            jobs.push_back({name, std::move(one), std::move(src), en_rel, key, stamp_path, out_path});
        }
    }
    // the edits, in parallel (each output is independent: the same bytes in any order)
    std::mutex mu;
    std::atomic<size_t> next{0};
    auto work = [&] {
        for (size_t i; (i = next++) < jobs.size();) {
            Job& j = jobs[i];
            Bytes out;
            Canvas png;
            std::string jwhy;
            bool ok = apply_recipe(j.recipe, adld::decrypt(j.recipe.source, j.src), font, j.en_rel, out, opts.png.empty() ? nullptr : &png, &jwhy);
            std::lock_guard<std::mutex> lock(mu);
            if (!ok) {
                LOGW("english", "art recipe %s: %s", j.name.c_str(), jwhy.c_str());
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
            if (!opts.png.empty()) {
                std::string p = opts.png + "/" + j.en_rel + ".png";
                mkdirs_for(p);
                if (!soa::png_write(p, png.w, png.h, 4, png.px.data())) LOGW("english", "art: cannot write %s", p.c_str());
            }
            st.built++;
            LOGI("english", "art: %s (%zu labels, %zu bytes)", j.en_rel.c_str(), j.recipe.labels.size(), out.size());
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

}  // namespace soa::server::english_art
