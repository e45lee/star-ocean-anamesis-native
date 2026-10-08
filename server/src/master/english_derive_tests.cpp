// Unit tests of the derivation's text rules (english_derive.h; --selftest "server/english-derive"):
// the expected strings are tools/english_core.py's output for the same input (the full-data
// comparison is tests/test_english_derive.py). Server code, no guest counterpart.
#include <sqlite3.h>
#include <unistd.h>

#include <cstdio>
#include <string>
#include <vector>

#include "master/english_derive.h"
#include "soa/adld.h"
#include "soaserver/config.h"
#include "soaserver/native_test.h"
#include <soa/file_tree.h>
#include <soa/install.h>
#include <soa/paths.h>

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
    t.expect_eq(english::ws_key("購入に失敗しました。\\n\\n再起動\u3000して ください。\t\u00a0"),
                std::string("購入に失敗しました。再起動してください。"), "ws_key: master \\n, U+3000, space, tab, U+00A0 removed");

    // id-ws and memory-ws (english.md 7.9) on two scratch masters: the same rows as
    // tests/test_english_text.py test_ws_rules_scratch_masters
    std::string dir = soa::temp_dir() + "/soa-english-derive-test-" + std::to_string(getpid());
    std::string jp = dir + "-jp.sqlite3", gl = dir + "-gl.sqlite3";
    auto make = [&](const std::string& path, const char* sql) {
        unlink(path.c_str());
        sqlite3* db = nullptr;
        bool ok = sqlite3_open(path.c_str(), &db) == SQLITE_OK && sqlite3_exec(db, sql, nullptr, nullptr, nullptr) == SQLITE_OK;
        sqlite3_close(db);
        return ok;
    };
    if (!make(jp,
              "create table master_text (message_id text, text_value text);"
              "insert into master_text values ('t_id_ws', '購入に失敗しました。\\n再起動してください。');"
              "insert into master_text values ('t_mem_ws', 'ピックアップ武器ガチャ　');"
              "insert into master_text values ('t_older', '体力が上がる');"
              "insert into master_text values ('t_blank', '　');") ||
        !make(gl,
              "create table master_text (lang text, message_id text, text_value text);"
              "insert into master_text values ('ja', 't_id_ws', '購入に失敗しました。\\n\\n再起動してください。');"
              "insert into master_text values ('en', 't_id_ws', 'Purchase failed.\\nPlease restart.');"
              "insert into master_text values ('ja', 'g_mem', 'ピックアップ武器ガチャ');"
              "insert into master_text values ('en', 'g_mem', 'Weapons Campaign Draw');"
              "insert into master_text values ('ja', 't_older', '攻撃が上がる');"
              "insert into master_text values ('en', 't_older', 'ATK up');"
              "insert into master_text values ('ja', 't_blank', '');"
              "insert into master_text values ('en', 't_blank', 'Blank');"))
        return t.fail("scratch masters in %s", soa::temp_dir().c_str());
    english::DeriveInput in;
    in.master = jp, in.global = gl, in.font = font;
    english::Derived d;
    if (!english::derive(in, d, &err)) return t.fail("derive: %s", err.c_str());
    unlink(jp.c_str());
    unlink(gl.c_str());
    auto served = [&](const char* mid) {
        return d.master.count(mid) ? d.master.at(mid).en + " [" + d.master.at(mid).source + "]" : std::string("-");
    };
    t.expect_eq(served("t_id_ws"), std::string("Purchase failed.\\nPlease restart. [official]"), "id-ws: Global's English by id");
    t.expect_eq(served("t_mem_ws"), std::string("Weapons Campaign Draw [memory]"), "memory-ws");
    t.expect_eq(served("t_older"), std::string("-"), "an older Global text is not the same line");
    t.expect_eq(served("t_blank"), std::string("-"), "white space only is no text to match");
}

NATIVE_TEST("server/english-labels-resolve") {
    // english_derive.h resolve_labels: the precedence of a layout label's English (english.md 7.14)
    using english::Entry;
    english::Derived d;
    d.jp_sha1 = {{"m_off", "s1"}, {"m_mach", "s2"}, {"m_mach2", "s3"}, {"m_stale", "s4"}, {"m_off2", "s5"}};
    d.label_mids = {{"公式", {"m_mach", "m_off"}},  // the official row wins over the earlier machine row
                    {"機械", {"m_mach2"}},
                    {"古い", {"m_stale"}},
                    {"人", {"m_off2"}}};
    d.labels = {{"記憶", Entry{"h", "Memory EN", "memory"}}, {"公式", Entry{"h", "Memory loses", "memory"}}};
    english::Table master = {{"m_off", Entry{"s1", "Official EN", "official"}},
                             {"m_mach", Entry{"s2", "Machine EN", "machine"}},
                             {"m_mach2", Entry{"s3", "Master machine", "machine"}},
                             {"m_stale", Entry{"other", "Stale EN", "official"}},
                             {"m_off2", Entry{"s5", "Official 2", "official"}}};
    english::Table ours = {
        {"公式", Entry{"x1", "", "derived"}},     {"機械", Entry{"x2", "Our machine", "machine"}},  // ours before the master's machine row
        {"記憶", Entry{"x3", "", "derived"}},     {"古い", Entry{"x4", "", "derived"}},              // the master row's Japanese changed: none
        {"人", Entry{"x5", "Human EN", "human"}},          // human over official
        {"無", Entry{"x6", "", "derived"}}};
    auto r = english::resolve_labels(&d, master, ours);
    auto en = [&](const char* ja) { return r.count(ja) ? r[ja].en + "|" + r[ja].source + "|" + r[ja].ja_sha1 : std::string("-"); };
    t.expect_eq(en("公式"), std::string("Official EN|official|x1"), "a master row's official English");
    t.expect_eq(en("機械"), std::string("Our machine|machine|x2"), "our machine row before a master machine row");
    t.expect_eq(en("記憶"), std::string("Memory EN|memory|x3"), "Global's memory");
    t.expect_eq(en("古い"), std::string("-"), "a stale master row isn't used");
    t.expect_eq(en("人"), std::string("Human EN|human|x5"), "our human row first");
    t.expect_eq(en("無"), std::string("-"), "nothing: the label stays Japanese");
    d.label_mids["無"] = {"m_mach2"};
    r = english::resolve_labels(&d, master, ours);
    t.expect_eq(en("無"), std::string("Master machine|machine|x6"), "last: a master machine row");
    r = english::resolve_labels(nullptr, master, ours);
    t.expect_eq(r.size() == 2 && en("機械") == "Our machine|machine|x2", true, "no derivation: our rows only");
}

}  // namespace
}  // namespace soa::server
