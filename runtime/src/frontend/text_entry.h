#pragma once
// The text-entry editor behind the emulated KeyboardActivity (jni/java_android.cpp
// StartKeyboardActivity; the host's keyboard handling in app/host.cpp and its on-screen box,
// app/text_overlay.h). Pure string operations on UTF-8 text with a byte-offset cursor that always
// sits on a code point boundary, so they can be tested without a window.
//
// The field's rules are the ones the game asks for: at most `max_len` code points (<= 0: no limit;
// the name field asks for 14) and, for a numeric field (type 1), ASCII digits only. Everything that
// adds text goes through insert(), so typing, an IME's committed text and a paste obey them alike:
// a too-long insertion keeps the code points that fit (an Android EditText's InputFilter
// .LengthFilter does the same).
#include <cstddef>
#include <string>
#include <string_view>

namespace soa::text_entry {

// Code points in `s` (UTF-8; continuation bytes aren't counted).
size_t utf8_len(std::string_view s);
// The code point boundary before / after byte offset `pos` (pos itself at the ends).
size_t prev_boundary(std::string_view s, size_t pos);
size_t next_boundary(std::string_view s, size_t pos);

struct Field {
    int max_len = 0;       // code points; <= 0: no limit
    bool numeric = false;  // ASCII digits only
};

// Inserts `add` at `cursor` and moves the cursor past it. Control characters (below U+0020, and
// DEL) are dropped, and for a numeric field everything but '0'-'9'; then as many leading code
// points as fit under max_len. Returns the number of code points inserted.
size_t insert(std::string& text, size_t& cursor, std::string_view add, const Field& f);

// Editing keys; each keeps the cursor on a boundary and returns whether anything changed.
bool backspace(std::string& text, size_t& cursor);  // deletes the code point before the cursor
bool del(std::string& text, size_t& cursor);        // deletes the code point after it
bool left(const std::string& text, size_t& cursor);
bool right(const std::string& text, size_t& cursor);
bool home(size_t& cursor);
bool end(const std::string& text, size_t& cursor);

// A cursor clamped into the text and moved back onto a code point boundary.
size_t clamp_cursor(std::string_view text, size_t cursor);

// The byte offset of code point `n` in `s` (s.size() past the end): SDL_TEXTEDITING's start is in
// code points.
size_t byte_offset(std::string_view s, size_t n);

// Decodes the code point at byte offset `pos` and moves `pos` past it (U+FFFD for a malformed
// sequence, which is skipped as one unit up to the next boundary).
char32_t decode(std::string_view s, size_t& pos);

}  // namespace soa::text_entry
