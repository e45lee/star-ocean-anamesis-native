#pragma once
// The one line breaker of the English text (docs/english.md 3.2 and 7.9; PLAN-english E7, E10, E12).
// The client breaks lines only at \n, so English is broken at spaces by us, in three places that all
// call this:
//   - the derivation of the served English (server/src/master/english_derive.cpp, the C++ twin of
//     tools/english_core.py Font.rebreak): breaks collapsed, tags kept whole, the font's advances;
//   - the client's word wrap of labels (platform370 text_370.cpp, --lang en): existing breaks kept,
//     Japanese lines left alone, the client's own measure (CalcStringRect);
//   - the client's box fit (fit_box: the home's speech box, E12): breaks collapsed, then the fewest
//     lines that fit a box at the largest scale.
// The rules, option by option, are pinned by common/tests/line_break_vectors.tsv, which the C++ unit
// tests (soa_text_tests) and tests/test_line_break.py (against english_core.Font.rebreak) both run.
#include <functional>
#include <string>
#include <string_view>

namespace soa::text {

// Python's str.isspace / re's \s on str (the derivation's notion of white space).
bool is_space(char32_t c);
// Kana, kanji, CJK punctuation, full-width forms (U+3000-30FF, 4E00-9FFF, FF00-FFEF).
bool has_japanese(std::string_view utf8);
// The length in bytes of the tag `<...>` starting at byte i (1 to 40 code points between < and >,
// none of them <, > or \n: tools/english_core.py TAG), or 0.
size_t tag_at(std::string_view utf8, size_t i);

struct BreakOptions {
    // true: each existing line is broken on its own and the breaks stay (the client's label wrap);
    // false: first every white-space run that holds a \n becomes one space (re.sub(r"\s*\n\s*", " ")).
    bool keep_breaks = false;
    // true: a line with Japanese in it is left as it is (the client's label wrap).
    bool skip_japanese = false;
    // true: a tag (tag_at) is part of a word; its spaces never break (tools/english_core.py rebreak).
    bool tags_are_words = true;
    // true: white space (is_space) is stripped from both ends of the text first (str.strip()).
    bool trim = false;
    // true: a line the greedy break splits into n lines is broken at the narrowest width that still
    // gives n lines, so the lines come out even (no last line of one word; the client's label wrap).
    // The derivation never sets it (english_core has no such mode).
    bool balance = false;
};

// The width of one line (no \n in it), in any unit; the budget is in the same unit.
using Measure = std::function<double(std::string_view line)>;

// Greedy breaking at ASCII spaces: words are joined with " " while the line's measure stays within
// the budget; a word wider than the budget stands alone. Exactly english_core.Font.rebreak for
// {keep_breaks false, skip_japanese false, tags_are_words true}: the text is split at every " " (an
// empty word between two spaces is kept, one at the start of a line is dropped, a line ending in a
// space keeps it) and an empty last line is not emitted.
std::string break_lines(std::string_view text, double budget, const Measure& measure, const BreakOptions& opt);

// The size of a text of one or more lines.
struct Extent {
    double w, h;
};
using MeasureText = std::function<Extent(std::string_view text)>;
struct BoxFit {
    std::string text;  // re-broken
    double scale;      // <= 1: the font scale at which `text` fits the box
};
// A text fitted into a box (E12): its breaks collapsed (and its ends trimmed), re-broken at the
// box's width / k for the fewest lines n whose height at scale k = min(1, box_h / height of n lines)
// fits, at the scale min(1, box_w / w, box_h / h) of the result (what CCocosLabel::DrawSelf's
// shrink-to-fit gives a fixed-size label). Because the greedy break never gains lines at a wider
// width, that is the largest scale at which the text fits. Tags are words (the label's measure must
// not count them when it doesn't draw them).
BoxFit fit_box(std::string_view text, double box_w, double box_h, const MeasureText& measure);

}  // namespace soa::text
