// soa/line_break.h (build/common/soa_text_tests; T0 `line-break`): every row of
// common/tests/line_break_vectors.tsv (shared with tests/test_line_break.py) through break_lines with
// the file's measure, then fit_box's rules on a fixed measure. Usage: soa_text_tests [VECTORS.tsv].
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include <soa/line_break.h>

namespace {

int g_fail = 0;
void check(bool ok, const std::string& what) {
    if (!ok) {
        fprintf(stderr, "FAIL: %s\n", what.c_str());
        g_fail++;
    }
}

std::string unescape(const std::string& s) {
    std::string o;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '\\' && i + 1 < s.size() && (s[i + 1] == 'n' || s[i + 1] == 't')) o += s[++i] == 'n' ? '\n' : '\t';
        else o += s[i];
    }
    return o;
}

std::vector<std::string> split_tabs(const std::string& line) {
    std::vector<std::string> f(1);
    for (char c : line) {
        if (c == '\t') f.emplace_back();
        else f.back() += c;
    }
    return f;
}

// The vectors' measure (the file's header).
double vector_width(std::string_view line, bool player) {
    double w = 0;
    for (size_t i = 0; i < line.size();) {
        size_t t = soa::text::tag_at(line, i);
        if (t) {
            if (player && line.substr(i, t) == "<player>") w += 16;
            i += t;
            continue;
        }
        unsigned char c = (unsigned char)line[i];
        size_t n = c < 0x80 ? 1 : (c >> 5) == 6 ? 2 : (c >> 4) == 14 ? 3 : 4;
        char32_t cp = n == 1 ? c : n == 2 ? (c & 0x1f) : n == 3 ? (c & 0x0f) : (c & 0x07);
        for (size_t k = 1; k < n && i + k < line.size(); k++) cp = cp << 6 | ((unsigned char)line[i + k] & 0x3f);
        i += n;
        if (cp < 0x80 && std::string_view("il'.,! |").find((char)cp) != std::string_view::npos) w += 1;
        else if (cp < 0x80 && std::string_view("mwMW").find((char)cp) != std::string_view::npos) w += 3;
        else if (cp >= 0x3000 && cp <= 0xffff) w += 4;
        else w += 2;
    }
    return w;
}

void vectors(const std::string& path) {
    std::ifstream in(path);
    check((bool)in, "open " + path);
    std::string line;
    int rows = 0;
    bool header = false;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto f = split_tabs(line);
        if (!header) {
            header = true;
            check(line == "text\tbudget\tkeep_breaks\tskip_japanese\ttags_are_words\ttrim\tplayer\texpected", "vectors header: " + line);
            continue;
        }
        if (f.size() != 8) {
            check(false, "malformed vector: " + line);
            continue;
        }
        soa::text::BreakOptions o;
        o.keep_breaks = f[2] == "1", o.skip_japanese = f[3] == "1", o.tags_are_words = f[4] == "1", o.trim = f[5] == "1";
        bool player = f[6] == "1";
        std::string got = soa::text::break_lines(unescape(f[0]), std::stod(f[1]), [&](std::string_view l) { return vector_width(l, player); }, o);
        check(got == unescape(f[7]), "break_lines(\"" + f[0] + "\", " + f[1] + ", " + f[2] + f[3] + f[4] + f[5] + f[6] + ") = \"" + got + "\", want \"" + f[7] + "\"");
        rows++;
    }
    check(rows >= 40, "only " + std::to_string(rows) + " vectors");
    fprintf(stderr, "line_break: %d vectors\n", rows);
}

// fit_box with a fixed-advance measure: 10 per byte, lines 30 apart and 24 high (h = 30 n - 6), a
// 100 x 54 box (two lines).
void fit_box() {
    auto m = [](std::string_view s) {
        double w = 0, n = 1, cur = 0;
        for (char ch : s) {
            if (ch == '\n') n++, cur = 0;
            else w = std::max(w, cur += 10);
        }
        return soa::text::Extent{w, 30 * n - 6};
    };
    struct Case {
        const char* in;
        const char* want;
        double scale;
    } cases[] = {
        {"aaa bbb", "aaa bbb", 1},                                // fits as it is
        {"aaa\nbbb", "aaa bbb", 1},                               // the line break collapsed
        {"aaaa bbbb cccc", "aaaa bbbb\ncccc", 1},                  // two lines at full size
        {"aaa  \n  bbb", "aaa bbb", 1},                           // the white space around a break goes
        {"  aaa bbb \n", "aaa bbb", 1},                           // the ends trimmed
        {"aaaa bbbb cccc dddd eeee", "aaaa bbbb cccc\ndddd eeee", 100.0 / 140},  // 3 lines at full size: 2 wider ones, shrunk
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 100.0 / 510},  // one word
        {"", "", 1},
    };
    for (const Case& c : cases) {
        soa::text::BoxFit f = soa::text::fit_box(c.in, 100, 54, m);
        check(f.text == c.want && std::fabs(f.scale - c.scale) < 1e-6,
              std::string("fit_box(\"") + c.in + "\") = \"" + f.text + "\" at " + std::to_string(f.scale));
        soa::text::Extent e = m(f.text);
        check(e.w * f.scale <= 100.01 && e.h * f.scale <= 54.01, std::string("fit_box(\"") + c.in + "\") leaves the box");
    }
}

void classes() {
    check(soa::text::has_japanese("回復") && soa::text::has_japanese("ＨＰ") && !soa::text::has_japanese("Cafe ×2 ―"), "has_japanese");
    check(soa::text::is_space(0x3000) && soa::text::is_space(0x85) && !soa::text::is_space(0x200b), "is_space");
    check(soa::text::tag_at("a<b c>", 1) == 5 && soa::text::tag_at("<>", 0) == 0 && soa::text::tag_at("<a\n>", 0) == 0, "tag_at");
    check(soa::text::tag_at("<" + std::string(40, 'x') + ">", 0) == 42 && soa::text::tag_at("<" + std::string(41, 'x') + ">", 0) == 0, "tag_at's 40");
    std::string kana40;
    for (int i = 0; i < 40; i++) kana40 += "あ";
    check(soa::text::tag_at("<" + kana40 + ">", 0) == 122, "tag_at counts code points");
}

}  // namespace

int main(int argc, char** argv) {
    vectors(argc > 1 ? argv[1] : std::string(SOA_REPO_DIR) + "/common/tests/line_break_vectors.tsv");
    fit_box();
    classes();
    if (g_fail) {
        fprintf(stderr, "soa_text_tests: %d failure(s)\n", g_fail);
        return 1;
    }
    fprintf(stderr, "soa_text_tests: PASS\n");
    return 0;
}
