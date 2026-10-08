// english-art: the English UI art of soaserver/english_art.h (docs/english.md "English UI art")
// built without a server, for writing recipes: the -en files into OUT, and with --png each edited
// image as PNG for review. The server's --english CDN step runs the same build.
//
//   build/tools/english_art/english-art [--download DIR|ZIP] [--recipes DIR] --out DIR [--png DIR] [--cache DIR]
//                                       [--labels TSV]
//   build/tools/english_art/english-art --check-roundtrip [--download DIR|ZIP]
//
// --labels: the layout labels (docs/english.md 7.14) from a table of ja, en columns (master encoding,
// a header line; e.g. soa-server --english-dump's labels-en.tsv). --check-roundtrip: the label tools
// against every scene of the download (english_art::check_roundtrip).
//
// Defaults: the download work/SOA-3.7.0-canonical-data.zip (read in place) and the recipes standin-assets-en/recipes of this
// checkout. Exit status 0 when every recipe was applied, 1 otherwise.
#include <cstdio>
#include <fstream>
#include <string>

#include <soa/cli.h>
#include <soa/install.h>

#include "soaserver/config.h"
#include "soaserver/english_art.h"

int main(int argc, char** argv) {
    soa::server::english_art::Options o;
    CLI::App app{"english-art: build the English UI art (-en images) from the download and the recipes"};
    app.add_option("--download", o.download, "the 3.7.0 download, its zip or a folder (default: the checkout's work/SOA-3.7.0-canonical-data.zip)");
    app.add_option("--recipes", o.recipes, "the recipe folder (default: the checkout's standin-assets-en/recipes)");
    std::string labels;
    bool check = false;
    app.add_option("--out", o.out, "where the -en files go");
    app.add_option("--labels", labels, "the layout labels: a TSV with a header and ja, en columns (master encoding)");
    app.add_flag("--check-roundtrip", check, "check the label tools against every scene of the download, then exit");
    app.add_option("--png", o.png, "also write each edited image as PNG here");
    app.add_option("--cache", o.cache, "the build stamps (default: OUT.art-cache)");
    CLI11_PARSE(app, argc, argv);
    if (o.download.empty()) o.download = soa::server::find_repo_file(soa::install::kRepoDownloadZip);
    if (check) {
        size_t scenes = 0, trees = 0;
        std::string err;
        bool ok = soa::server::english_art::check_roundtrip(o.download, &scenes, &trees, &err);
        printf("english-art: %zu scenes, %zu node trees: %s\n%s", scenes, trees, ok ? "the same bytes" : "DIFFERENT", err.c_str());
        return ok ? 0 : 1;
    }
    if (o.out.empty()) {
        fprintf(stderr, "english-art: --out is required\n");
        return 2;
    }
    if (o.recipes.empty()) o.recipes = soa::server::find_repo_file("standin-assets-en/recipes");
    if (!labels.empty()) {
        std::ifstream in(labels, std::ios::binary);
        std::string line;
        auto unesc = [](const std::string& s) {
            std::string r;
            for (size_t i = 0; i < s.size(); i++)
                if (s[i] == '\\' && i + 1 < s.size() && s[i + 1] == 'n') r += '\n', i++;
                else r += s[i];
            return r;
        };
        for (bool first = true; std::getline(in, line); first = false) {
            size_t a = line.find('\t'), b = a == std::string::npos ? a : line.find('\t', a + 1);
            if (first || a == std::string::npos) continue;
            std::string en = line.substr(a + 1, b == std::string::npos ? std::string::npos : b - a - 1);
            if (!en.empty()) o.labels[unesc(line.substr(0, a))] = unesc(en);
        }
        if (o.labels.empty()) fprintf(stderr, "english-art: no labels in %s\n", labels.c_str());
    }
    soa::server::english_art::Stats st;
    std::string err;
    if (!soa::server::english_art::build(o, &st, &err)) {
        fprintf(stderr, "english-art: %s\n", err.c_str());
        return 1;
    }
    printf("english-art: %zu recipes, %zu scenes with layout labels: %zu built (%zu labels), %zu up to date, %zu failed, %zu removed\n", st.recipes,
           st.label_scenes, st.built, st.labels_replaced, st.cached, st.failed, st.removed);
    return st.failed ? 1 : 0;
}
