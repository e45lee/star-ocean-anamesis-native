// Unit tests of the English text table (english_text.h; --selftest "server/english-text"). Server
// code, no guest counterpart.
#include <unistd.h>

#include <cstdio>
#include <string>

#include <soa/paths.h>

#include "master/english_text.h"
#include "soaserver/cdn.h"
#include "soaserver/config.h"
#include "soaserver/native_test.h"

namespace soa::server {
namespace {

std::string sha1_of(const std::string& s) { return cdn::sha1_hex((const uint8_t*)s.data(), s.size()); }

bool write_text(const std::string& path, const std::string& s) {
    FILE* f = fopen(path.c_str(), "wb");
    if (!f) return false;
    fwrite(s.data(), 1, s.size(), f);
    fclose(f);
    return true;
}

// The table's parse, the matching rule (replace / stale / new id / none), display() with and
// without --english, the printf check of the rate headings.
NATIVE_TEST("server/english-text") {
    std::string dir = soa::temp_dir(), path = dir + "/soa-english-test-" + std::to_string(getpid()) + ".tsv",
                bad = dir + "/soa-english-test-" + std::to_string(getpid()) + "-bad.tsv";
    write_text(path,
               "message_id\tja_sha1\ten\tsource\n"
               "a_new\t\tNew text\thuman\n"
               "a_old\t" +
                   sha1_of("古い") +
                   "\tOld\tofficial\n"
                   "a_same\t" +
                   sha1_of("同じ") + "\tSame\\nline\tofficial\n");
    write_text(bad, "message_id\ten\n");
    english::Table tab;
    std::string err;
    t.expect_eq(english::load(path, tab, &err), true, "load");
    t.expect_eq(tab.size(), (size_t)3, "rows");
    t.expect_eq(tab.count("a_same") ? tab["a_same"].en : "", std::string("Same\\nline"), "en kept as is (\\n two characters)");
    english::Table b;
    t.expect_eq(english::load(bad, b, &err), false, "a wrong header refused");
    t.expect_eq(english::load(dir + "/soa-english-test-none.tsv", b, &err), false, "a missing file refused");
    const english::Entry* e = nullptr;
    t.expect_eq(english::match(tab, "a_same", "同じ", &e) == english::Match::kReplace, true, "replace");
    t.expect_eq(e && e->en == "Same\\nline", true, "the entry");
    t.expect_eq(english::match(tab, "a_old", "新しい", &e) == english::Match::kStale, true, "stale");
    t.expect_eq(english::match(tab, "a_new", "", &e) == english::Match::kNewId, true, "new id");
    t.expect_eq(english::match(tab, "none", "x", &e) == english::Match::kNone && !e, true, "none");

    ServerConfig saved = config();
    config().english = false;
    config().english_text = path;
    t.expect_eq(english::display("a_same", "同じ"), std::string("同じ"), "without --english: Japanese");
    config().english = true;
    t.expect_eq(english::display("a_same", "同じ"), std::string("Same\\nline"), "--english: English");
    t.expect_eq(english::display("a_old", "新しい"), std::string("新しい"), "--english, stale: Japanese");
    t.expect_eq(english::display("a_new", ""), std::string("New text"), "--english, a new id");
    t.expect_eq(english::display("other", "他"), std::string("他"), "--english, no row: Japanese");
    config().english_text = dir + "/soa-english-test-none.tsv";
    t.expect_eq(english::display("a_same", "同じ"), std::string("同じ"), "--english without a table: Japanese");
    config() = saved;

    t.expect_eq(english::same_specifiers("★5提供割合 %.5f%%", "5★ Odds %.5f%%"), true, "same conversions");
    t.expect_eq(english::same_specifiers("★5提供割合 %.5f%%", "5★ Odds %.3f%%"), false, "other precision");
    t.expect_eq(english::same_specifiers("%s %d日目", "Day %d %s"), false, "other order");
    t.expect_eq(english::same_specifiers("100%達成", "100% done"), true, "no conversion");
    remove(path.c_str());
    remove(bad.c_str());
}

}  // namespace
}  // namespace soa::server
