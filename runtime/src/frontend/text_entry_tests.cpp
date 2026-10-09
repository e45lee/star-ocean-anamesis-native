// The text-entry editor (frontend/text_entry.h): pure UTF-8 editing, no window needed. Also run by
// build/runtime/soaruntime_tests.
#include <string>

#include "soaruntime/core/selftest.h"
#include "frontend/text_entry.h"

namespace soa {
namespace {

using namespace text_entry;

RUNTIME_TEST("frontend/text-utf8") {
    std::string s = "aクb";  // 1 + 3 + 1 bytes
    t.expect_eq(utf8_len(s), (size_t)3, "utf8_len");
    t.expect_eq(next_boundary(s, 1), (size_t)4, "next_boundary over a 3-byte code point");
    t.expect_eq(prev_boundary(s, 4), (size_t)1, "prev_boundary over a 3-byte code point");
    t.expect_eq(prev_boundary(s, 0), (size_t)0, "prev_boundary at the start");
    t.expect_eq(next_boundary(s, s.size()), s.size(), "next_boundary at the end");
    t.expect_eq(clamp_cursor(s, 2), (size_t)1, "clamp_cursor inside a code point");
    t.expect_eq(clamp_cursor(s, 99), s.size(), "clamp_cursor past the end");
    t.expect_eq(byte_offset(s, 2), (size_t)4, "byte_offset");
    t.expect_eq(byte_offset(s, 9), s.size(), "byte_offset past the end");
    size_t pos = 0;
    t.expect_eq(decode(s, pos), (char32_t)'a', "decode ASCII");
    t.expect_eq(decode(s, pos), (char32_t)0x30af, "decode U+30AF");
    t.expect_eq(pos, (size_t)4, "decode advances");
    std::string emoji = "\xf0\x9f\x98\x80", bad = "\xe3\x82";
    pos = 0;
    t.expect_eq(decode(emoji, pos), (char32_t)0x1f600, "decode a 4-byte code point");
    pos = 0;
    t.expect_eq(decode(bad, pos), (char32_t)0xfffd, "decode a truncated sequence");
    t.expect_eq(pos, bad.size(), "decode skips a truncated sequence whole");
}

RUNTIME_TEST("frontend/text-insert") {
    Field name{14, false};
    std::string text;
    size_t cur = 0;
    t.expect_eq(insert(text, cur, "Claire", name), (size_t)6, "insert count");
    t.expect_eq(text, std::string("Claire"), "insert text");
    t.expect_eq(cur, (size_t)6, "cursor after insert");
    left(text, cur), left(text, cur);
    insert(text, cur, "クレア", name);
    t.expect_eq(text, std::string("Claiクレアre"), "insert at the cursor");
    t.expect_eq(cur, (size_t)13, "cursor after a multibyte insert");
    // max length: the code points that fit are kept (Android's LengthFilter), the rest dropped
    t.expect_eq(insert(text, cur, "0123456789", name), (size_t)5, "insert truncated to max_len");
    t.expect_eq(utf8_len(text), (size_t)14, "length at max");
    t.expect_eq(insert(text, cur, "x", name), (size_t)0, "nothing fits at max");
    // control characters (a pasted newline, tab) are dropped
    std::string t2;
    size_t c2 = 0;
    insert(t2, c2, "a\nb\tc\x7f", Field{});
    t.expect_eq(t2, std::string("abc"), "control characters dropped");
    // numeric: digits only, then the length limit
    std::string num;
    size_t cn = 0;
    t.expect_eq(insert(num, cn, "1a2５3-4", Field{3, true}), (size_t)3, "numeric insert count");
    t.expect_eq(num, std::string("123"), "numeric filter + max length");
    // no limit
    std::string big;
    size_t cb = 0;
    insert(big, cb, std::string(100, 'z'), Field{0, false});
    t.expect_eq(big.size(), (size_t)100, "max_len 0 means no limit");
    // a field that starts over its limit (an initial text longer than max) takes nothing
    std::string over = "abcdef";
    size_t co = 6;
    t.expect_eq(insert(over, co, "g", Field{3, false}), (size_t)0, "over the limit already");
}

RUNTIME_TEST("frontend/text-keys") {
    std::string text = "aクb";
    size_t cur = text.size();
    t.expect_eq(backspace(text, cur), true, "backspace");
    t.expect_eq(text, std::string("aク"), "backspace removes b");
    t.expect_eq(backspace(text, cur), true, "backspace multibyte");
    t.expect_eq(text, std::string("a"), "backspace removes a whole code point");
    text = "aクb";
    cur = 0;
    t.expect_eq(backspace(text, cur), false, "backspace at the start");
    t.expect_eq(right(text, cur), true, "right");
    t.expect_eq(cur, (size_t)1, "right over a");
    t.expect_eq(del(text, cur), true, "delete");
    t.expect_eq(text, std::string("ab"), "delete removes a whole code point");
    t.expect_eq(end(text, cur), true, "end");
    t.expect_eq(cur, (size_t)2, "end position");
    t.expect_eq(del(text, cur), false, "delete at the end");
    t.expect_eq(right(text, cur), false, "right at the end");
    t.expect_eq(home(cur), true, "home");
    t.expect_eq(left(text, cur), false, "left at the start");
    t.expect_eq(home(cur), false, "home at the start");
    // a cursor left inside a code point (the text changed under it) is clamped first
    text = "クb";
    cur = 2;
    t.expect_eq(del(text, cur), true, "delete from a clamped cursor");
    t.expect_eq(text, std::string("b"), "clamped to the code point start");
}

}  // namespace
}  // namespace soa
