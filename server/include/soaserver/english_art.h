#pragma once
// The English UI art (docs/english.md "English UI art"; PLAN-english.md Q4, E9): the server's
// --english CDN step builds "-en" copies of the game's images with Japanese text, from the user's
// own download and committed recipes (standin-assets-en/recipes/*.json: the source file, the text
// boxes, the English text, the style). No game art is in git or in the release packages; the
// client with --lang en loads "<name>-en.<ext>" before "<name>.<ext>" (CGameResourceManager::
// FileExistLanguage, docs/english.md 6.3), so an image without a recipe stays Japanese.
//
// A Cocos scene (UI/etc2/*.csf) is rebuilt with its node tree and sprite table (.msgp, .csv) as they
// are and only the 4x4 pixel blocks under the labels re-encoded; a single image (Image/etc2/*.aif)
// the same way. The text is drawn with the game's own bitmap font (Font/etc2/font.fpk of the same
// download), so no font file ships. The output is ADLD XOR (encType 1) under the -en name, as the
// stand-in overlay holds its files, and is the same bytes for the same inputs on every platform.
#include <cstddef>
#include <string>
#include <vector>

namespace soa::server::english_art {

struct Options {
    std::string download;  // the 3.7.0 download: a folder or its zip (soa/file_tree.h)
    std::string recipes;   // the recipe folder (standin-assets-en/recipes)
    std::string out;       // the generated root: <out>/<dir>/<stem>-en<ext> (a CDN member root)
    std::string cache;     // stamps of what was built ("" = <out>.art-cache); kept outside `out`,
                           // which the CDN serves whole
    std::string png;       // also write each edited image as PNG here ("" = none; for review)
};

struct Stats {
    size_t recipes = 0;  // recipe files read
    size_t built = 0;    // -en files written
    size_t cached = 0;   // -en files already up to date (same recipe, source, font and generator)
    size_t failed = 0;   // recipes that couldn't be applied (logged; their image stays Japanese)
    size_t removed = 0;  // -en files of recipes that no longer exist, deleted
};

// Builds (or keeps, when up to date) the -en file of every recipe. False (and *err) only when
// nothing could be built: no recipe folder, no download or no font in it; a single bad recipe is
// logged and counted in stats->failed.
bool build(const Options& opts, Stats* stats = nullptr, std::string* err = nullptr);

// "UI/etc2/home.csf" -> "UI/etc2/home-en.csf" (the client's PostfixLanguageCodeFilepath for en).
std::string en_name(const std::string& rel);

}  // namespace soa::server::english_art
