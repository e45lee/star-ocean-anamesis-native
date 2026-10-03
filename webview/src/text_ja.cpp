// Japanese text for the page renderer: line-break opportunities (split_text_ja) and the viewport
// meta (viewport_width). New here; the Dragalia renderer's pages were English.
//
// litehtml 0.10 breaks lines only at white space and before/after each CJK unified ideograph
// (document_container::split_text: U+4E00..U+9FCC), so a run of kana, full-width punctuation or
// katakana is one unbreakable word and a Japanese paragraph overflows its box. split_text_ja gives a
// break opportunity between two characters when either is CJK (ideographs, kana, CJK punctuation,
// full-width forms, Hangul), except before a character that may not start a line (closing brackets
// and punctuation, small kana, the prolonged sound mark) and after one that may not end a line
// (opening brackets): the basic kinsoku shori (JIS X 4051's line-start and line-end prohibitions,
// the subset Android's WebView, ICU's line breaker, applies in its default "normal" strictness).
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <string>

#include "internal.h"

namespace soa::webview {
namespace {

bool is_cjk(char32_t c) {
    return (c >= 0x2E80 && c <= 0x2FDF) ||  // CJK radicals, Kangxi radicals
           (c >= 0x3000 && c <= 0x30FF) ||  // CJK symbols and punctuation, hiragana, katakana
           (c >= 0x3100 && c <= 0x31FF) ||  // bopomofo, Hangul compatibility jamo, katakana phonetic extensions
           (c >= 0x3200 && c <= 0x9FFF) ||  // enclosed CJK, CJK compatibility, extension A, unified ideographs
           (c >= 0xAC00 && c <= 0xD7AF) ||  // Hangul syllables
           (c >= 0xF900 && c <= 0xFAFF) ||  // CJK compatibility ideographs
           (c >= 0xFE30 && c <= 0xFE4F) ||  // CJK compatibility forms
           (c >= 0xFF00 && c <= 0xFFEF) ||  // half-width and full-width forms
           (c >= 0x20000 && c <= 0x3FFFF);  // extensions B..
}

// May not start a line (closing punctuation, small kana, iteration and prolonged sound marks).
bool no_line_start(char32_t c) {
    static const char32_t s[] = U")]},.:;!?%"
                                U"、。，．・：；？！゛゜ヽヾゝゞ々ー"
                                U"’”）〕］｝〉》」』】〙〗〟｠»"
                                U"ぁぃぅぇぉっゃゅょゎゕゖァィゥェォッャュョヮヵヶㇰㇱㇲㇳㇴㇵㇶㇷㇸㇹㇺㇻㇼㇽㇾㇿ"
                                U"‐゠–〜～";
    for (char32_t x : s)
        if (x && x == c) return true;
    return false;
}

// May not end a line (opening brackets).
bool no_line_end(char32_t c) {
    static const char32_t s[] = U"([{‘“（〔［｛〈《「『【〘〖〝｟«";
    for (char32_t x : s)
        if (x && x == c) return true;
    return false;
}

void append_utf8(std::string& out, char32_t c) {
    if (c < 0x80) out += (char)c;
    else if (c < 0x800) out += (char)(0xc0 | c >> 6), out += (char)(0x80 | (c & 0x3f));
    else if (c < 0x10000) out += (char)(0xe0 | c >> 12), out += (char)(0x80 | (c >> 6 & 0x3f)), out += (char)(0x80 | (c & 0x3f));
    else
        out += (char)(0xf0 | c >> 18), out += (char)(0x80 | (c >> 12 & 0x3f)), out += (char)(0x80 | (c >> 6 & 0x3f)),
            out += (char)(0x80 | (c & 0x3f));
}

}  // namespace

void split_text_ja(const char* text, const std::function<void(const char*)>& on_word, const std::function<void(const char*)>& on_space) {
    std::string word;
    char32_t prev = 0;  // the last code point of `word`
    auto flush = [&] {
        if (!word.empty()) on_word(word.c_str());
        word.clear();
        prev = 0;
    };
    for (const char* s = text; *s;) {
        char32_t c = next_cp(s);
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f') {
            flush();
            std::string sp(1, (char)c);
            on_space(sp.c_str());
            continue;
        }
        if (prev && (is_cjk(prev) || is_cjk(c)) && !no_line_end(prev) && !no_line_start(c)) flush();
        append_utf8(word, c);
        prev = c;
    }
    flush();
}

int viewport_width(const std::string& html) {
    // <meta name="viewport" content="width=640, user-scalable=no">: the first viewport meta
    size_t head_end = html.find("</head");
    for (size_t p = 0; (p = html.find("<meta", p)) != std::string::npos && (head_end == std::string::npos || p < head_end); p += 5) {
        size_t e = html.find('>', p);
        if (e == std::string::npos) return 0;
        std::string tag = html.substr(p, e - p);
        for (auto& ch : tag) ch = (char)tolower((unsigned char)ch);
        if (tag.find("viewport") == std::string::npos) continue;
        size_t c = tag.find("content=");
        if (c == std::string::npos) return 0;
        size_t w = tag.find("width", c);
        while (w != std::string::npos && w > 0 && (tag[w - 1] == '-' || isalpha((unsigned char)tag[w - 1]))) w = tag.find("width", w + 5);  // not min-width
        if (w == std::string::npos) return 0;
        size_t i = w + 5;
        while (i < tag.size() && (tag[i] == ' ' || tag[i] == '=')) i++;
        int n = atoi(tag.c_str() + i);
        return n > 0 ? n : 0;  // "device-width": 0
    }
    return 0;
}

}  // namespace soa::webview
