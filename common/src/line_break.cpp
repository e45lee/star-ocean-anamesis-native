// The English line breaker (soa/line_break.h). Port code, not guest behaviour: the rules are
// tools/english_core.py Font.rebreak's, pinned by common/tests/line_break_vectors.tsv.
#include "soa/line_break.h"

#include <vector>

namespace soa::text {

namespace {

// The code point at byte i and its length (invalid UTF-8: the byte alone, as U+FFFD).
char32_t decode(std::string_view s, size_t i, size_t* len) {
    unsigned char c = (unsigned char)s[i];
    size_t n = c < 0x80 ? 1 : (c >> 5) == 6 ? 2 : (c >> 4) == 14 ? 3 : (c >> 3) == 30 ? 4 : 0;
    if (n == 0 || i + n > s.size()) return *len = 1, 0xfffd;
    char32_t cp = n == 1 ? c : n == 2 ? (c & 0x1f) : n == 3 ? (c & 0x0f) : (c & 0x07);
    for (size_t k = 1; k < n; k++) {
        unsigned char d = (unsigned char)s[i + k];
        if ((d & 0xc0) != 0x80) return *len = 1, 0xfffd;
        cp = cp << 6 | (d & 0x3f);
    }
    *len = n;
    return cp;
}

// str.strip(): white space off both ends.
std::string_view strip(std::string_view s) {
    size_t a = 0, b = s.size();
    while (a < b) {
        size_t n;
        if (!is_space(decode(s, a, &n))) break;
        a += n;
    }
    while (b > a) {
        size_t k = b - 1;
        while (k > a && ((unsigned char)s[k] & 0xc0) == 0x80) k--;  // back to the code point's first byte
        size_t n;
        if (!is_space(decode(s, k, &n)) || k + n != b) break;
        b = k;
    }
    return s.substr(a, b - a);
}

// re.sub(r"\s*\n\s*", " ", s): every white-space run that holds a \n becomes one space.
std::string collapse_breaks(std::string_view s) {
    std::string out;
    out.reserve(s.size());
    size_t i = 0;
    while (i < s.size()) {
        size_t n;
        if (!is_space(decode(s, i, &n))) {
            out.append(s.substr(i, n));
            i += n;
            continue;
        }
        size_t j = i;
        bool nl = false;
        while (j < s.size()) {
            size_t m;
            if (!is_space(decode(s, j, &m))) break;
            nl |= s[j] == '\n';
            j += m;
        }
        if (nl) out += ' ';
        else out.append(s.substr(i, j - i));
        i = j;
    }
    return out;
}

// The words of a line: split at every ASCII space (outside tags when tags are words).
std::vector<std::string_view> words(std::string_view line, bool tags_are_words) {
    std::vector<std::string_view> out;
    size_t start = 0, i = 0;
    while (i < line.size()) {
        if (tags_are_words && line[i] == '<') {
            size_t t = tag_at(line, i);
            if (t) {
                i += t;
                continue;
            }
        }
        if (line[i] == ' ') {
            out.push_back(line.substr(start, i - start));
            start = ++i;
        } else {
            i++;
        }
    }
    out.push_back(line.substr(start));
    return out;
}

// The greedy break of one line (english_core.Font.rebreak's loop).
void greedy(std::string_view line, double budget, const Measure& measure, bool tags_are_words, std::string* out) {
    std::vector<std::string> lines;
    std::string cur;
    for (std::string_view w : words(line, tags_are_words)) {
        std::string cand = cur.empty() ? std::string(w) : cur + " " + std::string(w);
        if (!cur.empty() && measure(cand) > budget) {
            lines.push_back(std::move(cur));
            cur = std::string(w);
        } else {
            cur = std::move(cand);
        }
    }
    if (!cur.empty()) lines.push_back(std::move(cur));
    for (size_t k = 0; k < lines.size(); k++) {
        if (k) *out += '\n';
        *out += lines[k];
    }
}

size_t count_lines(const std::string& s) {
    size_t n = 1;
    for (char c : s) n += c == '\n';
    return n;
}

// The greedy break at the narrowest budget (to 1/64 of the budget) that gives as many lines as the
// greedy break at `budget`: even lines.
void balanced(std::string_view line, double budget, const Measure& measure, bool tags_are_words, std::string* out) {
    std::string best;
    greedy(line, budget, measure, tags_are_words, &best);
    size_t n = count_lines(best);
    if (n < 2) return void(*out += best);
    double lo = 0, hi = budget;
    while (hi - lo > budget / 64) {
        double mid = (lo + hi) / 2;
        std::string t;
        greedy(line, mid, measure, tags_are_words, &t);
        if (count_lines(t) <= n) hi = mid, best = std::move(t);
        else lo = mid;
    }
    *out += best;
}

}  // namespace

bool is_space(char32_t c) {
    return (c >= 0x09 && c <= 0x0d) || (c >= 0x1c && c <= 0x20) || c == 0x85 || c == 0xa0 || c == 0x1680 || (c >= 0x2000 && c <= 0x200a) ||
           c == 0x2028 || c == 0x2029 || c == 0x202f || c == 0x205f || c == 0x3000;
}

bool has_japanese(std::string_view s) {
    for (size_t i = 0; i < s.size();) {
        size_t n;
        char32_t cp = decode(s, i, &n);
        if ((cp >= 0x3000 && cp <= 0x30ff) || (cp >= 0x4e00 && cp <= 0x9fff) || (cp >= 0xff00 && cp <= 0xffef)) return true;
        i += n;
    }
    return false;
}

size_t tag_at(std::string_view s, size_t i) {
    if (i >= s.size() || s[i] != '<') return 0;
    size_t j = i + 1, run = 0;
    while (j < s.size() && s[j] != '<' && s[j] != '>' && s[j] != '\n') {
        if (((unsigned char)s[j] & 0xc0) != 0x80) run++;  // code points, not bytes
        j++;
    }
    if (run >= 1 && run <= 40 && j < s.size() && s[j] == '>') return j + 1 - i;
    return 0;
}

std::string break_lines(std::string_view text, double budget, const Measure& measure, const BreakOptions& opt) {
    if (opt.trim) text = strip(text);
    std::string out;
    if (!opt.keep_breaks) {
        std::string flat = collapse_breaks(text);
        if (opt.skip_japanese && has_japanese(flat)) return flat;
        greedy(flat, budget, measure, opt.tags_are_words, &out);
        return out;
    }
    // each line on its own; a line that fits (or has no space) stays exactly as it is
    size_t start = 0;
    while (true) {
        size_t nl = text.find('\n', start);
        std::string_view line = text.substr(start, nl == std::string_view::npos ? std::string_view::npos : nl - start);
        if (line.find(' ') == std::string_view::npos || (opt.skip_japanese && has_japanese(line)) || measure(line) <= budget)
            out.append(line);
        else if (opt.balance)
            balanced(line, budget, measure, opt.tags_are_words, &out);
        else
            greedy(line, budget, measure, opt.tags_are_words, &out);
        if (nl == std::string_view::npos) break;
        out += '\n';
        start = nl + 1;
    }
    return out;
}

BoxFit fit_box(std::string_view text, double box_w, double box_h, const MeasureText& measure) {
    BreakOptions opt;
    opt.trim = true;
    std::string flat = break_lines(text, 1e300, [](std::string_view) { return 0.0; }, opt);  // collapsed, trimmed, one line
    auto width = [&](std::string_view line) { return measure(line).w; };
    auto scale_of = [&](Extent e) {
        double k = 1;
        if (e.w > box_w && e.w > 0) k = box_w / e.w;
        if (e.h > box_h && e.h > 0 && box_h / e.h < k) k = box_h / e.h;
        return k;
    };
    std::string probe = "Ag", wrapped = flat;
    for (int n = 1; n <= 24; n++, probe += "\nAg") {
        double hn = measure(probe).h;
        double k = hn > box_h && hn > 0 ? box_h / hn : 1.0;
        wrapped = break_lines(flat, box_w / k, width, opt);
        Extent e = measure(wrapped);
        if (e.h <= box_h / k * 1.001) return {wrapped, scale_of(e)};
    }
    return {wrapped, scale_of(measure(wrapped))};
}

}  // namespace soa::text
