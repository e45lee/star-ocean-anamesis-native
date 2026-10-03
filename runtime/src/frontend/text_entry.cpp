#include "frontend/text_entry.h"

#include <algorithm>
#include <cstdint>

namespace soa::text_entry {

namespace {
bool is_cont(unsigned char c) { return (c & 0xc0) == 0x80; }
}  // namespace

size_t utf8_len(std::string_view s) {
    size_t n = 0;
    for (unsigned char c : s)
        if (!is_cont(c)) n++;
    return n;
}

size_t prev_boundary(std::string_view s, size_t pos) {
    pos = std::min(pos, s.size());
    if (pos == 0) return 0;
    do pos--;
    while (pos > 0 && is_cont((unsigned char)s[pos]));
    return pos;
}

size_t next_boundary(std::string_view s, size_t pos) {
    if (pos >= s.size()) return s.size();
    do pos++;
    while (pos < s.size() && is_cont((unsigned char)s[pos]));
    return pos;
}

size_t clamp_cursor(std::string_view text, size_t cursor) {
    cursor = std::min(cursor, text.size());
    while (cursor > 0 && cursor < text.size() && is_cont((unsigned char)text[cursor])) cursor--;
    return cursor;
}

size_t byte_offset(std::string_view s, size_t n) {
    size_t pos = 0;
    while (n-- > 0 && pos < s.size()) pos = next_boundary(s, pos);
    return pos;
}

char32_t decode(std::string_view s, size_t& pos) {
    size_t start = pos, end = next_boundary(s, pos);
    pos = end;
    if (start >= s.size()) return 0;
    unsigned char c0 = (unsigned char)s[start];
    size_t len = end - start;
    if (c0 < 0x80) return len == 1 ? c0 : 0xfffd;
    size_t want = c0 >= 0xf0 ? 4 : c0 >= 0xe0 ? 3 : c0 >= 0xc0 ? 2 : 0;
    if (want == 0 || want != len || c0 >= 0xf8) return 0xfffd;
    char32_t cp = c0 & (0x7f >> want);
    for (size_t i = 1; i < len; i++) cp = (cp << 6) | ((unsigned char)s[start + i] & 0x3f);
    return cp;
}

size_t insert(std::string& text, size_t& cursor, std::string_view add, const Field& f) {
    cursor = clamp_cursor(text, cursor);
    size_t have = utf8_len(text), room = f.max_len > 0 ? (have < (size_t)f.max_len ? f.max_len - have : 0) : SIZE_MAX;
    std::string keep;
    size_t n = 0;
    for (size_t i = 0; i < add.size() && n < room;) {
        size_t j = next_boundary(add, i);
        std::string_view cp = add.substr(i, j - i);
        i = j;
        unsigned char c0 = (unsigned char)cp[0];
        if (c0 < 0x20 || c0 == 0x7f || is_cont(c0)) continue;
        if (f.numeric && !(cp.size() == 1 && c0 >= '0' && c0 <= '9')) continue;
        keep += cp;
        n++;
    }
    text.insert(cursor, keep);
    cursor += keep.size();
    return n;
}

bool backspace(std::string& text, size_t& cursor) {
    cursor = clamp_cursor(text, cursor);
    if (cursor == 0) return false;
    size_t p = prev_boundary(text, cursor);
    text.erase(p, cursor - p);
    cursor = p;
    return true;
}

bool del(std::string& text, size_t& cursor) {
    cursor = clamp_cursor(text, cursor);
    if (cursor >= text.size()) return false;
    text.erase(cursor, next_boundary(text, cursor) - cursor);
    return true;
}

bool left(const std::string& text, size_t& cursor) {
    size_t c = clamp_cursor(text, cursor);
    cursor = prev_boundary(text, c);
    return cursor != c;
}

bool right(const std::string& text, size_t& cursor) {
    size_t c = clamp_cursor(text, cursor);
    cursor = next_boundary(text, c);
    return cursor != c;
}

bool home(size_t& cursor) {
    bool moved = cursor != 0;
    cursor = 0;
    return moved;
}

bool end(const std::string& text, size_t& cursor) {
    bool moved = cursor != text.size();
    cursor = text.size();
    return moved;
}

}  // namespace soa::text_entry
