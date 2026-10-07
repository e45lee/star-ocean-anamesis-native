// Unit tests of the derivation's text rules (english_derive.h; --selftest "server/english-derive"):
// the expected strings are tools/english_core.py's output for the same input (the full-data
// comparison is tests/test_english_derive.py). Server code, no guest counterpart.
#include <cstdio>
#include <string>
#include <vector>

#include "master/english_derive.h"
#include "soaserver/adld.h"
#include "soaserver/config.h"
#include "soaserver/native_test.h"
#include <soa/file_tree.h>
#include <soa/install.h>

namespace soa::server {
namespace {

NATIVE_TEST("server/english-derive-rules") {
    // the font from the 3.7.0 download, its zip read in place (or a folder given as the download)
    std::string download = find_repo_file(soa::install::kRepoDownloadZip);
    if (download.empty()) return t.skip("%s not found (the 3.7.0 download: local data)", soa::install::kRepoDownloadZip);
    auto tree = FileTree::open(download);
    std::vector<uint8_t> fpk;
    if (!tree || !tree->read("Font/etc2/font.fpk", fpk)) return t.fail("%s: no Font/etc2/font.fpk", download.c_str());
    english::Advances font;
    std::string err;
    if (!english::load_advances(adld::decrypt("Font/etc2/font.fpk", fpk), font, &err)) return t.fail("font: %s", err.c_str());
    t.expect_eq(font.adv['a'], 18, "advance of a");
    t.expect_eq(font.adv['?'], 21, "advance of ?");
    t.expect_eq(english::fold(font, "café — “quote” 50% ™ né"), std::string("cafe ― \"quote\" 50%  ne"), "fold");
    t.expect_eq(english::fold(font, "日本語 ok"), std::string("日本語 ok"), "fold keeps the font's glyphs");
    t.expect_eq(english::nfkc("ＡＢＣ１２３　ｶﾀｶﾅ"), std::string("ABC123 カタカナ"), "NFKC");
    t.expect_eq(english::rebreak(font, "Thanks to your efforts, I was able to <player> find the <font color=red>red key</font> at last.\nNew line",
                                 300, true),
                std::string("Thanks to your\nefforts, I was able\nto <player> find the\n<font color=red>red key</font> at last.\nNew line"),
                "rebreak (a tag one word, <player> 120 px)");
    t.expect_eq(english::fix_percent("50% more %d", "%d"), std::string("50%% more %d"), "%% in a printf row");
    std::string out, why;
    t.expect_eq(english::rewrite_tokens("Day <NUM 2> <STR 1>", "%s %d日目", &out, &why), false, "E3: a reorder stays a gap");
    t.expect_eq(english::rewrite_tokens("<STR 1> <NUM 2> <INSERT 2>Time/Times</INSERT><EMDASH>", "%s %d回", &out, &why) && out == "%s %d Times―",
                true, "E3: tokens, INSERT, EMDASH");
}

}  // namespace
}  // namespace soa::server
