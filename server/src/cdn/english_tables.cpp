// The English tables of an --english server (soaserver/cdn.h english_tables;
// docs/server-rules.md#english-derive): an explicit table as it is, or the derived layer
// (master/english_derive.h) with our own rows merged on top. Our code.
#include <chrono>
#include <set>
#include <vector>

#include <soa/file_tree.h>

#include "cdn/files.h"
#include "core/log.h"
#include "master/english_derive.h"
#include "master/english_text.h"
#include "soa/adld.h"
#include "soaserver/cdn.h"
#include "soaserver/english_art.h"

namespace soa::server::cdn {

namespace {
// The TS_*.tsv tables of a folder, by stem; a missing folder is no tables.
bool load_story_tables(const std::string& dir, std::map<std::string, english::Table>& out, std::string* err) {
    if (dir.empty()) return true;
    std::vector<std::string> names;
    files::walk(dir, "", names);
    for (auto& rel : names) {
        if (rel.find('/') != std::string::npos || rel.rfind("TS_", 0) != 0 || rel.size() < 7 || rel.compare(rel.size() - 4, 4, ".tsv") != 0) continue;
        english::Table t;
        if (!english::load(dir + "/" + rel, t, err)) return false;
        out[rel.substr(0, rel.size() - 4)] = std::move(t);
    }
    return true;
}
double since(std::chrono::steady_clock::time_point t0) { return std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count(); }
}  // namespace

bool english_tables(const Options& opts, const FileTree& download, EnglishTables& out, std::string* err) {
    out = EnglishTables{};
    auto t0 = std::chrono::steady_clock::now();
    // the layout labels to translate (english.md 7.14): a bad file is logged, the rest goes on
    english::Table labels;
    std::string lwhy;
    if (!opts.english_labels.empty() && !english::load_labels(opts.english_labels, labels, &lwhy)) {
        LOGW("cdn", "english labels: %s: the layout labels stay Japanese", lwhy.c_str());
        labels.clear();
    }
    if (!labels.empty()) {
        // (d) labels.tsv holds the SHA-1 of each label's Japanese, not the text (no game text in
        // git): the text is the download's, found in its scenes' node trees
        std::set<std::string> texts;
        english_art::label_texts(download, texts);
        std::vector<std::string> stale;
        size_t listed = labels.size();
        labels = english::labels_by_text(labels, texts, &stale);
        if (!stale.empty())
            LOGW("cdn", "english labels: %zu of %zu rows of %s match no label of the download's scenes (first %s)", stale.size(), listed,
                 opts.english_labels.c_str(), stale[0].c_str());
    }
    if (opts.english_full) {
        // the whole tables, as they are (tests); the labels: our rows only
        if (!opts.english_text.empty() && !english::load(opts.english_text, out.master, err)) return false;
        out.labels = english::resolve_labels(nullptr, out.master, labels);
        return load_story_tables(opts.english_story, out.story, err);
    }
    // (a) Global's English and (d) the derivation rules (english_derive.h), with our rows on top
    if (opts.english_global.empty()) {
        if (err) *err = "no Global master (data/basmaster-gl.sqlite3): no derived English";
        return false;
    }
    // read by a package's smoke run (the lookup of the shipped Global master)
    LOGI("cdn", "english derive: Global master %s", opts.english_global.c_str());
    english::DeriveInput in;
    in.master = opts.master;
    in.global = opts.english_global;
    std::vector<uint8_t> fpk;
    std::string why;
    if (!download.read("Font/etc2/font.fpk", fpk) || !english::load_advances(adld::decrypt("Font/etc2/font.fpk", fpk), in.font, &why)) {
        if (err) *err = "the download's Font/etc2/font.fpk: " + (why.empty() ? std::string("missing") : why);
        return false;
    }
    // (b) the story files: every Scenario/TS_*.msgp of the download (english_core.py's glob)
    for (auto& base : download.list("Scenario")) {
        if (base.rfind("TS_", 0) != 0 || base.size() < 8 || base.compare(base.size() - 5, 5, ".msgp") != 0) continue;
        std::vector<uint8_t> f;
        std::string rel = "Scenario/" + base;
        if (!download.read(rel, f)) continue;
        english::StoryFile sf;
        sf.stem = base.substr(0, base.size() - 5);
        if (english::story_lines(adld::decrypt(rel, f), sf)) in.story.push_back(std::move(sf));
    }
    for (auto& [ja, e] : labels) in.labels.push_back(ja);
    english::Table ours;
    if (!opts.english_text.empty() && !english::load(opts.english_text, ours, err)) return false;
    std::map<std::string, english::Table> ours_story;
    if (!load_story_tables(opts.english_story, ours_story, err)) return false;
    english::Table ours_lines;
    for (auto& [stem, t] : ours_story)
        for (auto& [mid, e] : t) ours_lines[mid] = e;
    english::Derived d;
    if (!english::derive(in, d, err)) return false;
    out.master = english::merge_master(d, ours);
    out.story = english::merge_story(d, ours_lines);
    out.labels = english::resolve_labels(&d, out.master, labels);
    out.derived = true;
    LOGI("cdn",
         "english derive: %zu official (%zu by E3), %zu memory, %zu template, %zu failing; story %zu official lines, %zu failing; with our "
         "%zu + %zu rows: %zu master rows, %zu story files (%.2f s)",
         d.official + d.e3, d.e3, d.memory, d.templ, d.failing, d.story_official, d.story_failing, ours.size(), ours_lines.size(), out.master.size(),
         out.story.size(), since(t0));
    std::map<std::string, size_t> by_source;
    for (auto& [ja, e] : out.labels) by_source[e.source]++;
    std::string sources;
    for (auto& [src, n] : by_source) sources += (sources.empty() ? "" : ", ") + std::to_string(n) + " " + src;
    LOGI("cdn", "english labels: %zu of %zu layout labels with English (%s)", out.labels.size(), labels.size(), sources.c_str());
    return true;
}

bool write_english_tables(const EnglishTables& t, const std::string& dir) {
    files::mkdirs(dir + "/story-en");
    std::string m = english::table_text(t.master);
    bool ok = files::write_file(dir + "/master-en.tsv", (const uint8_t*)m.data(), m.size());
    for (auto& [stem, table] : t.story) {
        std::string s = english::table_text(table);
        ok &= files::write_file(dir + "/story-en/" + stem + ".tsv", (const uint8_t*)s.data(), s.size());
    }
    std::string l = "ja\ten\tsource\n";
    for (auto& [ja, e] : t.labels) l += ja + "\t" + e.en + "\t" + e.source + "\n";
    ok &= files::write_file(dir + "/labels-en.tsv", (const uint8_t*)l.data(), l.size());
    LOGI("cdn", "english tables: %zu master rows, %zu story files -> %s", t.master.size(), t.story.size(), dir.c_str());
    return ok;
}

}  // namespace soa::server::cdn
