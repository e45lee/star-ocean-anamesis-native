// english-art: the English UI art of soaserver/english_art.h (docs/english.md "English UI art")
// built without a server, for writing recipes: the -en files into OUT, and with --png each edited
// image as PNG for review. The server's --english CDN step runs the same build.
//
//   build/tools/english_art/english-art [--download DIR|ZIP] [--recipes DIR] --out DIR [--png DIR] [--cache DIR]
//
// Defaults: the download work/SOA-3.7.0-canonical-data.zip (read in place) and the recipes standin-assets-en/recipes of this
// checkout. Exit status 0 when every recipe was applied, 1 otherwise.
#include <cstdio>
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
    app.add_option("--out", o.out, "where the -en files go")->required();
    app.add_option("--png", o.png, "also write each edited image as PNG here");
    app.add_option("--cache", o.cache, "the build stamps (default: OUT.art-cache)");
    CLI11_PARSE(app, argc, argv);
    if (o.download.empty()) o.download = soa::server::find_repo_file(soa::install::kRepoDownloadZip);
    if (o.recipes.empty()) o.recipes = soa::server::find_repo_file("standin-assets-en/recipes");
    soa::server::english_art::Stats st;
    std::string err;
    if (!soa::server::english_art::build(o, &st, &err)) {
        fprintf(stderr, "english-art: %s\n", err.c_str());
        return 1;
    }
    printf("english-art: %zu recipes: %zu built, %zu up to date, %zu failed, %zu removed\n", st.recipes, st.built, st.cached, st.failed, st.removed);
    return st.failed ? 1 : 0;
}
