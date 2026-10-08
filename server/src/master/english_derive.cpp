// The derived layer of the English text (english_derive.h; docs/server-rules.md#english-derive):
// tools/english_core.py and tools/english_text.py `build`, rule for rule, in C++. Each function names
// the Python it mirrors; the regular expressions are spelled out as scanners with Python's semantics
// (code points, Unicode \d / \s / \b). Port code, not guest behaviour.
#include "master/english_derive.h"

#include <sqlite3.h>
#include <utf8proc.h>

#include <algorithm>
#include <cstring>
#include <functional>

#include "english_art/art.h"
#include "soaserver/cdn.h"
#include "soaserver/msgpack.h"
#include <soa/line_break.h>

namespace soa::server::english {

namespace {

using U = std::u32string;

// ---- UTF-8 <-> code points ------------------------------------------------------------------------
U u32(const std::string& s) {
    U out;
    out.reserve(s.size());
    const uint8_t* p = (const uint8_t*)s.data();
    utf8proc_ssize_t n = (utf8proc_ssize_t)s.size(), i = 0;
    while (i < n) {
        utf8proc_int32_t cp;
        utf8proc_ssize_t k = utf8proc_iterate(p + i, n - i, &cp);
        if (k <= 0) {  // invalid UTF-8: keep the byte as U+FFFD (the inputs are valid UTF-8)
            cp = 0xfffd;
            k = 1;
        }
        out.push_back((char32_t)cp);
        i += k;
    }
    return out;
}
std::string u8(const U& s) {
    std::string out;
    out.reserve(s.size());
    uint8_t b[4];
    for (char32_t c : s) {
        utf8proc_ssize_t k = utf8proc_encode_char((utf8proc_int32_t)c, b);
        out.append((const char*)b, (size_t)k);
    }
    return out;
}

// ---- character classes (Python's str / re) ------------------------------------------------------
// KANA = [぀-ヿ一-鿿]
bool is_kana(char32_t c) { return (c >= 0x3040 && c <= 0x30ff) || (c >= 0x4e00 && c <= 0x9fff); }
bool has_kana(const U& s) {
    for (char32_t c : s)
        if (is_kana(c)) return true;
    return false;
}
// str.isspace() / re's \s for str patterns
bool is_space(char32_t c) {
    return (c >= 0x09 && c <= 0x0d) || (c >= 0x1c && c <= 0x20) || c == 0x85 || c == 0xa0 || c == 0x1680 || (c >= 0x2000 && c <= 0x200a) ||
           c == 0x2028 || c == 0x2029 || c == 0x202f || c == 0x205f || c == 0x3000;
}
// re's \d: Unicode decimal digits (category Nd)
bool is_digit(char32_t c) {
    if (c < 0x80) return c >= '0' && c <= '9';
    return utf8proc_category((utf8proc_int32_t)c) == UTF8PROC_CATEGORY_ND;
}
// re's \w: alphanumeric (letters, numbers) or '_'
bool is_word(char32_t c) {
    if (c < 0x80) return isalnum((int)c) || c == '_';
    utf8proc_category_t k = utf8proc_category((utf8proc_int32_t)c);
    return (k >= UTF8PROC_CATEGORY_LU && k <= UTF8PROC_CATEGORY_LO) || (k >= UTF8PROC_CATEGORY_ND && k <= UTF8PROC_CATEGORY_NO);
}

U normalize(const U& s, int options) {
    std::string in = u8(s);
    utf8proc_uint8_t* out = nullptr;
    utf8proc_ssize_t n = utf8proc_map((const utf8proc_uint8_t*)in.data(), (utf8proc_ssize_t)in.size(), &out, (utf8proc_option_t)options);
    if (n < 0) return s;
    U r = u32(std::string((const char*)out, (size_t)n));
    free(out);
    return r;
}
U nfkc_u(const U& s) { return normalize(s, UTF8PROC_STABLE | UTF8PROC_COMPOSE | UTF8PROC_COMPAT); }
U nfkd_u(const U& s) { return normalize(s, UTF8PROC_STABLE | UTF8PROC_DECOMPOSE | UTF8PROC_COMPAT); }

bool starts(const U& s, size_t i, const char* lit) {
    for (size_t k = 0; lit[k]; k++)
        if (i + k >= s.size() || s[i + k] != (char32_t)(unsigned char)lit[k]) return false;
    return true;
}
bool contains(const U& s, const char* lit) {
    for (size_t i = 0; i < s.size(); i++)
        if (starts(s, i, lit)) return true;
    return false;
}
U lit(const char* s) { return u32(s); }

// unesc / esc: the master's two-character "\n" <-> a newline
U unesc(const U& s) {
    U o;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '\\' && i + 1 < s.size() && s[i + 1] == 'n') {
            o += U'\n';
            i++;
        } else o += s[i];
    }
    return o;
}
U esc(const U& s) {
    U o;
    for (char32_t c : s) {
        if (c == '\n') o += U"\\n";
        else o += c;
    }
    return o;
}
// english_core.ws_key: the text without its white space (WS_CHARS: tab, newline, space, U+00A0,
// U+3000; a master-encoded "\n" is a newline first), the key of the rules id-ws and memory-ws
U ws_key_u(const U& s) {
    U o;
    for (char32_t c : unesc(s))
        if (c != '\t' && c != '\n' && c != ' ' && c != 0xa0 && c != 0x3000) o += c;
    return o;
}
// english_core.same_ja != None: Global's ja is 3.7.0's exactly, or but for white space (some text left)
bool same_ja(const std::string& gl_ja, const std::string& ja) {
    if (gl_ja == ja) return true;
    U k = ws_key_u(u32(ja));
    return !k.empty() && ws_key_u(u32(gl_ja)) == k;
}
// str.strip()
U strip(const U& s) {
    size_t a = 0, b = s.size();
    while (a < b && is_space(s[a])) a++;
    while (b > a && is_space(s[b - 1])) b--;
    return s.substr(a, b - a);
}

// ---- SPEC / SPEC_STRICT: %(?:\d+\$)?[-+#0]*\d*(?:\.\d+)?(?:ll|l|h)?[dusfxXc] ----------------------
size_t spec_at(const U& s, size_t i, bool positional) {
    if (i >= s.size() || s[i] != '%') return 0;
    auto rest = [&](size_t j) -> size_t {
        while (j < s.size() && (s[j] == '-' || s[j] == '+' || s[j] == '#' || s[j] == '0')) j++;
        while (j < s.size() && is_digit(s[j])) j++;
        if (j + 1 < s.size() && s[j] == '.' && is_digit(s[j + 1])) {
            j++;
            while (j < s.size() && is_digit(s[j])) j++;
        }
        if (j + 1 < s.size() && s[j] == 'l' && s[j + 1] == 'l') j += 2;
        else if (j < s.size() && (s[j] == 'l' || s[j] == 'h')) j++;
        if (j < s.size() && s[j] < 0x80 && s[j] != 0 && std::strchr("dusfxXc", (int)s[j])) return j + 1;
        return 0;
    };
    size_t j = i + 1;
    if (positional) {
        size_t k = j;
        while (k < s.size() && is_digit(s[k])) k++;
        if (k > j && k < s.size() && s[k] == '$') {
            size_t e = rest(k + 1);
            if (e) return e - i;
        }
    }
    size_t e = rest(j);
    return e ? e - i : 0;
}
std::vector<U> specs(const U& s, bool positional) {
    std::vector<U> out;
    for (size_t i = 0; i < s.size();) {
        size_t n = spec_at(s, i, positional);
        if (n) {
            out.push_back(s.substr(i, n));
            i += n;
        } else i++;
    }
    return out;
}
bool has_spec(const U& s) {
    for (size_t i = 0; i < s.size(); i++)
        if (spec_at(s, i, true)) return true;
    return false;
}

// ---- TAG: <[^<>\n]{1,40}> ---------------------------------------------------------------------------
size_t tag_at(const U& s, size_t i) {
    if (s[i] != '<') return 0;
    size_t j = i + 1;
    while (j < s.size() && s[j] != '<' && s[j] != '>' && s[j] != '\n') j++;
    size_t run = j - i - 1;
    if (run >= 1 && run <= 40 && j < s.size() && s[j] == '>') return run + 2;
    return 0;
}
std::vector<U> tags(const U& s) {
    std::vector<U> out;
    for (size_t i = 0; i < s.size();) {
        size_t n = tag_at(s, i);
        if (n) {
            out.push_back(s.substr(i, n));
            i += n;
        } else i++;
    }
    return out;
}
// STORY_TAG = <player>|<font ?color=[^<>]*>|<fontsize=[^<>]*>|</font>, fullmatch of a TAG
bool story_tag(const U& t) {
    if (t == U"<player>" || t == U"</font>") return true;
    if (t.empty() || t.back() != '>') return false;
    for (size_t k = 1; k + 1 < t.size(); k++)
        if (t[k] == '<' || t[k] == '>') return false;
    return starts(t, 0, "<font color=") || starts(t, 0, "<fontcolor=") || starts(t, 0, "<fontsize=");
}

// ---- NUM: \d+(?:\.\d+)? -------------------------------------------------------------------------------
size_t num_at(const U& s, size_t i) {
    if (!is_digit(s[i])) return 0;
    size_t j = i;
    while (j < s.size() && is_digit(s[j])) j++;
    if (j + 1 < s.size() && s[j] == '.' && is_digit(s[j + 1])) {
        j++;
        while (j < s.size() && is_digit(s[j])) j++;
    }
    return j - i;
}
std::vector<U> nums(const U& s) {
    std::vector<U> out;
    for (size_t i = 0; i < s.size();) {
        size_t n = num_at(s, i);
        if (n) {
            out.push_back(s.substr(i, n));
            i += n;
        } else i++;
    }
    return out;
}

// GL_TOKEN / GL_MARKUP (english_core.py)
const char* const kMarkup[] = {"<NUM", "<STR", "<INSERT", "</INSERT", "<EMDASH>"};
const char* const kBrackets[] = {"[G]", "[R]", "[Y]", "[B]", "[Blue]", "[Red]", "[Green]", "[Yellow]", "[White]", "[-]"};
bool gl_markup(const U& s) {
    for (const char* m : kMarkup)
        if (contains(s, m)) return true;
    return false;
}
bool gl_token(const U& s) {
    if (gl_markup(s)) return true;
    for (const char* m : kBrackets)
        if (contains(s, m)) return true;
    return false;
}
// GL_MARKUP.sub("", s)
U gl_markup_removed(const U& s) {
    U o;
    for (size_t i = 0; i < s.size();) {
        size_t n = 0;
        for (const char* m : kMarkup)
            if (starts(s, i, m)) {
                n = strlen(m);
                break;
            }
        if (n) i += n;
        else o += s[i++];
    }
    return o;
}
U replace_all(const U& s, const U& from, const U& to) {
    U o;
    for (size_t i = 0; i < s.size();) {
        if (!from.empty() && s.compare(i, from.size(), from) == 0) {
            o += to;
            i += from.size();
        } else o += s[i++];
    }
    return o;
}
// int() of a \d+ run (ASCII digits in the data)
int to_int(const U& d) {
    int v = 0;
    for (char32_t c : d) v = v * 10 + (c >= '0' && c <= '9' ? (int)(c - '0') : 0);
    return v;
}

// fix_percent(en, ja): in a printf row a literal % must be %%
U fix_percent_u(const U& en, const U& ja) {
    if (!has_spec(ja)) return en;
    U o;
    for (size_t i = 0; i < en.size();) {
        if (en[i] != '%') {
            o += en[i++];
            continue;
        }
        if (i + 1 < en.size() && en[i + 1] == '%') {
            o += U"%%";
            i += 2;
            continue;
        }
        size_t n = spec_at(en, i, true);
        if (n) {
            o += en.substr(i, n);
            i += n;
        } else {
            o += U"%%";
            i++;
        }
    }
    return o;
}

// rewrite_tokens (E3)
bool rewrite_u(U en, const U& ja, U* out, std::string* why) {
    en = replace_all(en, lit("<EMDASH>"), U"―");
    // INSERT = <INSERT \d+>([^<>/]*)/([^<>]*)</INSERT> -> group 2
    {
        U o;
        for (size_t i = 0; i < en.size();) {
            size_t end = 0;
            U g2;
            if (starts(en, i, "<INSERT ")) {
                size_t j = i + 8, d0 = j;
                while (j < en.size() && is_digit(en[j])) j++;
                if (j > d0 && j < en.size() && en[j] == '>') {
                    size_t k = j + 1;
                    while (k < en.size() && en[k] != '<' && en[k] != '>' && en[k] != '/') k++;
                    if (k < en.size() && en[k] == '/') {
                        size_t m = k + 1;
                        while (m < en.size() && en[m] != '<' && en[m] != '>') m++;
                        if (starts(en, m, "</INSERT>")) {
                            g2 = en.substr(k + 1, m - k - 1);
                            end = m + 9;
                        }
                    }
                }
            }
            if (end) {
                o += g2;
                i = end;
            } else o += en[i++];
        }
        en = o;
    }
    // NUMSTR = <(NUM|STR) (\d+)>
    struct Tok {
        size_t at, len;
        int n;
    };
    std::vector<Tok> toks;
    for (size_t i = 0; i < en.size();) {
        if (starts(en, i, "<NUM ") || starts(en, i, "<STR ")) {
            size_t j = i + 5, d0 = j;
            while (j < en.size() && is_digit(en[j])) j++;
            if (j > d0 && j < en.size() && en[j] == '>') {
                toks.push_back({i, j + 1 - i, to_int(en.substr(d0, j - d0))});
                i = j + 1;
                continue;
            }
        }
        i++;
    }
    std::vector<U> sp = specs(ja, false);
    if (!toks.empty()) {
        if (sp.empty()) return *why = "composition", false;
        std::vector<int> ns;
        for (auto& t : toks) ns.push_back(t.n);
        std::vector<int> sorted = ns;
        std::sort(sorted.begin(), sorted.end());
        if (sorted.size() != sp.size()) return *why = "tokens don't match", false;
        for (size_t k = 0; k < sorted.size(); k++)
            if (sorted[k] != (int)k + 1) return *why = "tokens don't match", false;
        if (ns != sorted) return *why = "reorder needed", false;
        U o;
        size_t last = 0;
        for (auto& t : toks) {
            o += en.substr(last, t.at - last);
            o += sp[t.n - 1];
            last = t.at + t.len;
        }
        o += en.substr(last);
        en = o;
    }
    if (gl_markup(en)) return *why = "unknown Global token", false;
    en = fix_percent_u(en, ja);
    if (specs(en, false) != sp) return *why = "specifiers", false;
    *out = en;
    return true;
}

// ---- the font: fold, width, rebreak (english_core.Font) ---------------------------------------------
int adv_of(const Advances& f, char32_t c) {
    auto it = f.adv.find((uint32_t)c);
    if (it != f.adv.end()) return it->second;
    auto q = f.adv.find('?');
    return q == f.adv.end() ? 0 : q->second;
}
U fold_u(const Advances& f, const U& s) {
    U out;
    for (char32_t c : s) {
        U r;
        switch (c) {  // FOLD
            case 0x2014:
                r = U"―";
                break;
            case 0x2013:
                r = U"-";
                break;
            case 0x2018:
            case 0x2019:
                r = U"'";
                break;
            case 0x201c:
            case 0x201d:
                r = U"\"";
                break;
            case 0x2022:
            case 0xb7:
                r = U"・";
                break;
            case 0x2122:
            case 0xae:
                r = U"";
                break;
            case 0x20ac:
                r = U"EUR";
                break;
            case 0xa0:
                r = U" ";
                break;
            default:
                r = U(1, c);
        }
        if (r.size() == 1 && !f.has((uint32_t)r[0]) && r[0] != '\n' && r[0] != '\t') {
            U d = nfkd_u(r), k;
            for (char32_t x : d)
                if (f.has((uint32_t)x)) k += x;
            r = k.empty() ? U"?" : k;
        }
        out += r;
    }
    return out;
}
int width(const Advances& f, const U& line, bool player_px) {
    int extra = 0;
    U rest;
    for (size_t i = 0; i < line.size();) {
        size_t n = tag_at(line, i);
        if (n) {
            if (player_px && replace_all(line.substr(i, n), U"\x01", U" ") == U"<player>") extra += 120;
            i += n;
        } else rest += line[i++];
    }
    int w = extra;
    for (char32_t c : rest) w += adv_of(f, c);
    return w;
}
std::vector<U> split(const U& s, char32_t sep) {
    std::vector<U> out(1);
    for (char32_t c : s) {
        if (c == sep) out.emplace_back();
        else out.back() += c;
    }
    return out;
}
int widest(const Advances& f, const U& text) {
    int w = 0;
    for (auto& l : split(text, '\n')) w = std::max(w, width(f, l, false));
    return w;
}
// english_core.Font.rebreak: the shared breaker (soa/line_break.h) in its derivation mode (breaks
// collapsed, tags are words), measured with width() above.
U rebreak_u(const Advances& f, const U& text, int budget, bool player_px) {
    soa::text::BreakOptions o;  // keep_breaks false, skip_japanese false, tags_are_words true, trim false
    // width() on UTF-8 without a copy: the tags (tag_at, the same TAG) count 0, <player> 120
    auto measure = [&](std::string_view line) {
        int w = 0;
        for (size_t i = 0; i < line.size();) {
            size_t t = soa::text::tag_at(line, i);
            if (t) {
                if (player_px && line.substr(i, t) == "<player>") w += 120;
                i += t;
                continue;
            }
            utf8proc_int32_t cp;
            utf8proc_ssize_t k = utf8proc_iterate((const uint8_t*)line.data() + i, (utf8proc_ssize_t)(line.size() - i), &cp);
            if (k <= 0) cp = 0xfffd, k = 1;
            w += adv_of(f, (char32_t)cp);
            i += (size_t)k;
        }
        return (double)w;
    };
    return u32(soa::text::break_lines(u8(text), budget, measure, o));
}

// ---- check (english_core.check, without the glossary and the budget) -------------------------------
struct Problems {
    bool specifiers = false, positional = false, tags = false, kana = false, glyphs = false, token = false, story_tag = false;
    bool any() const { return specifiers || positional || tags || kana || glyphs || token || story_tag; }
};
std::vector<U> sorted_tags(const U& s) {
    auto t = tags(s);
    std::sort(t.begin(), t.end());
    return t;
}
bool tags_subset(const std::vector<U>& tj, const std::vector<U>& te) {
    for (auto& t : te)
        if (std::find(tj.begin(), tj.end(), t) == tj.end()) return false;
    size_t opens = 0, closes = 0;
    for (auto& t : te) {
        if (starts(t, 0, "<font")) opens++;
        if (t == U"</font>") closes++;
    }
    return opens == closes;
}
Problems check(const Advances& f, const U& ja, const U& en, bool subset) {
    Problems p;
    auto sj = specs(ja, true), se = specs(en, true);
    auto tj = sorted_tags(ja), te = sorted_tags(en);
    if (sj != se) p.specifiers = true;
    else if (!sj.empty()) {
        // re.sub(SPEC + "|%%", "", en).count("%")
        size_t pct = 0;
        for (size_t i = 0; i < en.size();) {
            size_t n = spec_at(en, i, true);
            if (n) i += n;
            else if (en[i] == '%' && i + 1 < en.size() && en[i + 1] == '%') i += 2;
            else pct += en[i++] == '%';
        }
        if (pct) p.specifiers = true;
    }
    for (size_t i = 0; i < en.size(); i++)  // %\d+\$
        if (en[i] == '%') {
            size_t j = i + 1;
            while (j < en.size() && is_digit(en[j])) j++;
            if (j > i + 1 && j < en.size() && en[j] == '$') p.positional = true;
        }
    if (tj != te && !(subset && tags_subset(tj, te))) p.tags = true;
    if (has_kana(en)) p.kana = true;
    for (char32_t c : en)
        if (c != '\n' && c != '\t' && !f.has((uint32_t)c)) p.glyphs = true;
    if (gl_markup(en)) p.token = true;
    return p;
}

// ---- the sources ---------------------------------------------------------------------------------
struct Src {
    std::map<std::string, std::string> jp;                 // message_id -> text_value (JP master)
    std::unordered_map<std::string, std::string> gl_en, gl_ja;
    std::unordered_map<std::string, bool> gl_ja_null;     // Global's ja text_value is NULL (Python's None)
    std::vector<std::string> gl_ja_order;                  // message_ids of gl_ja, first insertion order
};
bool read_rows(const std::string& path, const char* sql, const std::function<void(const std::string&, const std::string&, bool)>& fn,
               std::string* err) {
    sqlite3* db = nullptr;
    if (sqlite3_open_v2(path.c_str(), &db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) {
        if (err) *err = "cannot open " + path;
        sqlite3_close(db);
        return false;
    }
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        if (err) *err = path + ": " + sqlite3_errmsg(db);
        sqlite3_close(db);
        return false;
    }
    while (sqlite3_step(st) == SQLITE_ROW) {
        const unsigned char* a = sqlite3_column_text(st, 0);
        const unsigned char* b = sqlite3_column_text(st, 1);
        fn(a ? (const char*)a : "", b ? (const char*)b : "", b != nullptr);
    }
    sqlite3_finalize(st);
    sqlite3_close(db);
    return true;
}

std::string sha1_of(const std::string& s) { return cdn::sha1_hex((const uint8_t*)s.data(), s.size()); }

// Sources.gl_english (filters 1, 2, 4, 5)
bool gl_english(const Src& s, const std::string& mid, U* out) {
    auto e = s.gl_en.find(mid);
    if (e == s.gl_en.end() || e->second.empty()) return false;
    auto j = s.gl_ja.find(mid);
    std::string ja = j == s.gl_ja.end() ? "" : j->second;
    U en = u32(e->second);
    bool ja_null = j == s.gl_ja.end() || s.gl_ja_null.at(mid);
    if (has_kana(en) || (!ja_null && e->second == j->second) || gl_token(en)) return false;
    if (specs(en, false) != specs(u32(ja), false)) return false;
    *out = en;
    return true;
}
// Sources.gl_token_english
bool gl_token_english(const Src& s, const std::string& mid, U* out) {
    auto e = s.gl_en.find(mid);
    if (e == s.gl_en.end() || e->second.empty()) return false;
    auto j = s.gl_ja.find(mid);
    U en = u32(e->second);
    bool ja_null = j == s.gl_ja.end() || s.gl_ja_null.at(mid);
    if (has_kana(en) || (!ja_null && e->second == j->second) || !gl_markup(en)) return false;
    if (gl_token(gl_markup_removed(replace_all(en, lit("</INSERT>"), U"")))) return false;
    *out = en;
    return true;
}

// Memory (exact and template)
struct Memory {
    std::map<std::string, std::string> exact;     // ja -> en (UTF-8)
    std::map<std::string, std::string> exact_ws;  // ws_key(ja) -> en (memory-ws)
    std::map<std::string, std::string> templ;     // key -> template
};
void numkey(const U& ja, U* key, std::vector<U>* ns) {
    U n = nfkc_u(ja);
    ns->clear();
    key->clear();
    for (size_t i = 0; i < n.size();) {
        size_t k = num_at(n, i);
        if (k) {
            ns->push_back(n.substr(i, k));
            *key += U'\0';
            i += k;
        } else *key += n[i++];
    }
}
bool template_unsafe(const U& t) {
    static const char* months[] = {"January", "February", "March",     "April",   "May",      "June",
                                   "July",    "August",   "September", "October", "November", "December"};
    for (const char* m : months)
        if (contains(t, m)) return true;
    for (size_t i = 0; i + 2 < t.size(); i++)
        if (t[i] == '}' && (starts(t, i + 1, "st") || starts(t, i + 1, "nd") || starts(t, i + 1, "rd") || starts(t, i + 1, "th")) &&
            (i + 3 >= t.size() || !is_word(t[i + 3])))
            return true;
    return false;
}
Memory make_memory(const Src& s) {
    std::map<std::string, std::map<std::string, int>> exact, exact_ws, tmpl;
    for (auto& mid : s.gl_ja_order) {
        const std::string& ja8 = s.gl_ja.at(mid);
        if (ja8.empty()) continue;
        U en;
        if (!gl_english(s, mid, &en)) continue;
        std::string en8 = u8(en);
        exact[ja8][en8]++;
        U ja = u32(ja8), key, wk = ws_key_u(ja);
        if (!wk.empty()) exact_ws[u8(wk)][en8]++;
        std::vector<U> ns;
        numkey(ja, &key, &ns);
        if (ns.empty()) continue;
        std::vector<U> sorted_ns = ns;
        std::sort(sorted_ns.begin(), sorted_ns.end());
        if (std::adjacent_find(sorted_ns.begin(), sorted_ns.end()) != sorted_ns.end()) continue;
        std::vector<U> ens = nums(en);
        std::sort(ens.begin(), ens.end());
        if (ens != sorted_ns) continue;
        U t;
        for (size_t i = 0; i < en.size();) {
            size_t k = num_at(en, i);
            if (k) {
                U m = en.substr(i, k);
                auto it = std::find(ns.begin(), ns.end(), m);
                if (it != ns.end()) t += u32("{" + std::to_string(it - ns.begin()) + "}");
                else t += m;
                i += k;
            } else t += en[i++];
        }
        // NUM.search(re.sub(r"\{\d+\}", "", t))
        U bare;
        for (size_t i = 0; i < t.size();) {
            if (t[i] == '{') {
                size_t j = i + 1;
                while (j < t.size() && is_digit(t[j])) j++;
                if (j > i + 1 && j < t.size() && t[j] == '}') {
                    i = j + 1;
                    continue;
                }
            }
            bare += t[i++];
        }
        bool has_num = false;
        for (char32_t c : bare) has_num |= is_digit(c);
        if (has_num || template_unsafe(t)) continue;
        tmpl[u8(key)][u8(t)]++;
    }
    auto pick = [](const std::map<std::string, int>& c) {  // min by (-count, string)
        const std::string* best = nullptr;
        int bc = 0;
        for (auto& [e, n] : c)
            if (!best || n > bc) best = &e, bc = n;  // the map is sorted: the first of the top count
        return *best;
    };
    Memory m;
    for (auto& [k, c] : exact) m.exact[k] = pick(c);
    for (auto& [k, c] : exact_ws) m.exact_ws[k] = pick(c);
    for (auto& [k, c] : tmpl) m.templ[k] = pick(c);
    return m;
}
// Memory.lookup: (english, kind) or false
bool lookup(const Memory& m, const std::string& ja8, U* en, bool* exact) {
    auto e = m.exact.find(ja8);
    if (e != m.exact.end()) {
        *en = u32(e->second);
        *exact = true;
        return true;
    }
    auto w = m.exact_ws.find(u8(ws_key_u(u32(ja8))));  // memory-ws: the same text but for white space
    if (w != m.exact_ws.end()) {
        *en = u32(w->second);
        *exact = true;
        return true;
    }
    U key;
    std::vector<U> ns;
    numkey(u32(ja8), &key, &ns);
    if (ns.empty()) return false;
    auto t = m.templ.find(u8(key));
    if (t == m.templ.end()) return false;
    U tt = u32(t->second), o;
    for (size_t i = 0; i < tt.size();) {  // \{(\d+)\} -> nums[int]
        if (tt[i] == '{') {
            size_t j = i + 1;
            while (j < tt.size() && is_digit(tt[j])) j++;
            if (j > i + 1 && j < tt.size() && tt[j] == '}') {
                o += ns[(size_t)to_int(tt.substr(i + 1, j - i - 1))];
                i = j + 1;
                continue;
            }
        }
        o += tt[i++];
    }
    // re.sub(r"\b1 (time|hit|day|turn|battle|mission)s\b", r"1 \1", en, flags=re.I)
    static const char* words[] = {"time", "hit", "day", "turn", "battle", "mission"};
    U r;
    for (size_t i = 0; i < o.size();) {
        size_t end = 0;
        if (o[i] == '1' && (i == 0 || !is_word(o[i - 1])) && i + 1 < o.size() && o[i + 1] == ' ') {
            for (const char* w : words) {
                size_t n = strlen(w), j = i + 2;
                bool ok = j + n < o.size();
                for (size_t k = 0; ok && k < n; k++) ok = std::tolower((int)(o[j + k] < 0x80 ? o[j + k] : 0)) == w[k];
                if (ok && (o[j + n] == 's' || o[j + n] == 'S') && (j + n + 1 >= o.size() || !is_word(o[j + n + 1]))) {
                    r += U"1 " + o.substr(j, n);
                    end = j + n + 1;
                    break;
                }
            }
        }
        if (end) i = end;
        else r += o[i++];
    }
    *en = r;
    *exact = false;
    return true;
}

}  // namespace

std::string ws_key(const std::string& s) { return u8(ws_key_u(u32(s))); }

namespace {

// english_text.finish for a derived candidate: (served English in the master encoding, passes)
bool finish(const Advances& f, const U& en, const std::string& ja8, std::string* out) {
    U ja = u32(ja8), jn = unesc(ja), e = unesc(en);
    e = fold_u(f, e);
    e = fix_percent_u(e, ja);
    bool jn_nl = jn.find('\n') != U::npos, e_nl = e.find('\n') != U::npos;
    if (jn_nl && !e_nl) e = rebreak_u(f, e, std::max(widest(f, jn), 200), false);
    Problems p = ja8.empty() ? check(f, e, e, false) : check(f, jn, e, true);
    *out = u8(esc(e));
    return !p.any();
}
// english_text.story_finish for a derived (official) candidate; `ja` with real newlines
bool story_finish(const Advances& f, const U& en, const U& ja, int budget, std::string* out) {
    U e = unesc(en);
    e = fold_u(f, e);
    e = strip(e);
    // english_text.story_break: the fewest n whose break at story_budget(n) takes at most n lines
    U r;
    for (int n = 1; n < 25; n++) {
        int b = n <= kStoryLines ? budget : budget * (40 * n - 10) / (40 * kStoryLines - 10);
        r = rebreak_u(f, e, b, true);
        if ((int)std::count(r.begin(), r.end(), U'\n') + 1 <= n) break;
    }
    e = r;
    Problems p = check(f, ja, e, false);
    auto ts = tags(e);
    bool bad = false;
    for (auto& t : ts) bad |= !story_tag(t);
    if (bad) p.story_tag = true;
    else if (p.tags) {
        size_t opens = 0, closes = 0;
        for (auto& t : ts) {
            if (starts(t, 0, "<font")) opens++;
            if (t == U"</font>") closes++;
        }
        if (opens == closes) p.tags = false;
    }
    *out = u8(esc(e));
    return !p.any();
}

}  // namespace

// ---- public ----------------------------------------------------------------------------------------
std::string nfkc(const std::string& s) { return u8(nfkc_u(u32(s))); }
std::string fold(const Advances& f, const std::string& s) { return u8(fold_u(f, u32(s))); }
std::string rebreak(const Advances& f, const std::string& s, int budget, bool player_px) { return u8(rebreak_u(f, u32(s), budget, player_px)); }
std::string fix_percent(const std::string& en, const std::string& ja) { return u8(fix_percent_u(u32(en), u32(ja))); }
bool rewrite_tokens(const std::string& en, const std::string& ja, std::string* out, std::string* why) {
    U o;
    std::string w;
    if (!rewrite_u(u32(en), u32(ja), &o, &w)) {
        if (why) *why = w;
        return false;
    }
    *out = u8(o);
    return true;
}

bool load_advances(const std::vector<uint8_t>& fpk_plain, Advances& out, std::string* err) {
    english_art::Font font;
    if (!font.load(fpk_plain, err)) return false;
    out.adv.clear();
    for (auto& [id, g] : font.glyphs) out.adv[id] = g.adv;
    return true;
}

bool story_lines(const std::vector<uint8_t>& plain, StoryFile& out) {
    Value v = mp_decode(plain);
    const Value* rows = v.find("master_text");
    if (!rows || rows->type != Value::Arr) return false;
    for (auto& r : rows->arr) {
        const Value* mid = r.find("message_id");
        const Value* text = r.find("text_value");
        out.lines.emplace_back(mid && mid->type == Value::Str ? mid->s : "", text && text->type == Value::Str ? text->s : "");
    }
    return true;
}

bool derive(const DeriveInput& in, Derived& d, std::string* err) {
    Src s;
    if (!read_rows(
            in.master, "select message_id, text_value from master_text", [&](const std::string& m, const std::string& t, bool) { s.jp[m] = t; }, err))
        return false;
    if (!read_rows(
            in.global, "select message_id, text_value from master_text where lang='en'",
            [&](const std::string& m, const std::string& t, bool) { s.gl_en[m] = t; }, err))
        return false;
    if (!read_rows(
            in.global, "select message_id, text_value from master_text where lang='ja'",
            [&](const std::string& m, const std::string& t, bool notnull) {
                if (!s.gl_ja.count(m)) s.gl_ja_order.push_back(m);
                s.gl_ja[m] = t;
                s.gl_ja_null[m] = !notnull;
            },
            err))
        return false;
    const Advances& f = in.font;
    Memory mem = make_memory(s);
    // Derived (english_text.py): per JP row in message_id order
    for (auto& [mid, ja8] : s.jp) {
        d.jp_sha1[mid] = sha1_of(ja8);
        U ja = u32(ja8), cand;
        const char* source = nullptr;
        U off;
        auto gj = s.gl_ja.find(mid);
        // (a) id, or (d) id-ws: Global's ja is this text but for white space (english.md 7.9)
        bool gl_same = gj != s.gl_ja.end() && !s.gl_ja_null.at(mid) && same_ja(gj->second, ja8);
        // (a) Global's English by id (the five filters)
        if (gl_english(s, mid, &off) && gl_same) {
            cand = off, source = "official";
            d.official++;
        } else {
            // (a)+(d) E3: a Global token row rewritten
            U tok, e3;
            std::string why;
            if (gl_token_english(s, mid, &tok) && gl_same && rewrite_u(tok, ja, &e3, &why)) {
                cand = e3, source = "official";
                d.e3++;
            }
        }
        if (!source && has_kana(ja)) {
            // (d) exact, then template memory
            bool exact = false;
            if (lookup(mem, ja8, &cand, &exact)) {
                source = exact ? "memory" : "template";
                (exact ? d.memory : d.templ)++;
            }
        }
        if (!source) continue;
        std::string e;
        if (finish(f, cand, ja8, &e)) d.master[mid] = Entry{sha1_of(ja8), e, source};
        else d.failing++;
    }
    // the layout labels (docs/server-rules.md#english-labels): (d) the JP rows with the same
    // Japanese, (a) Global's English for it through the memory, finished as a master row
    if (!in.labels.empty()) {
        std::map<std::string, std::vector<std::string>> by_text, by_ws;
        for (auto& [mid, ja8] : s.jp) {
            by_text[ja8].push_back(mid);
            std::string k = u8(ws_key_u(u32(ja8)));
            if (!k.empty()) by_ws[k].push_back(mid);
        }
        for (auto& ja8 : in.labels) {
            std::vector<std::string>& mids = d.label_mids[ja8];
            auto e = by_text.find(ja8);
            if (e != by_text.end()) mids = e->second;
            auto w = by_ws.find(u8(ws_key_u(u32(ja8))));
            if (w != by_ws.end())
                for (auto& m : w->second)
                    if (std::find(mids.begin(), mids.end(), m) == mids.end()) mids.push_back(m);
            U cand;
            bool exact = false;
            std::string en;
            if (has_kana(u32(ja8)) && lookup(mem, ja8, &cand, &exact) && finish(f, cand, ja8, &en))
                d.labels[ja8] = Entry{sha1_of(ja8), en, exact ? "memory" : "template"};
        }
    }
    // StoryDerived
    d.files = in.story;
    for (auto& file : in.story)
        for (auto& [mid, ja8] : file.lines) {
            U ja = u32(ja8), en;
            d.story_sha1[mid] = sha1_of(ja8);
            bool ok = false;
            auto gj = s.gl_ja.find(mid);
            U gja = gj == s.gl_ja.end() ? U() : unesc(u32(gj->second));
            if (gl_english(s, mid, &en)) ok = gja == ja;  // story_official
            if (!ok) {
                U tok;
                std::string why;
                if (gl_token_english(s, mid, &tok) && gja == ja) ok = rewrite_u(tok, esc(ja), &en, &why);  // story_official_e3
            }
            if (!ok) {
                d.story.erase(mid);  // a later file's line of the same id replaces an earlier one (Python's dict)
                continue;
            }
            std::string e;
            if (story_finish(f, en, ja, in.story_budget, &e)) {
                d.story[mid] = Entry{sha1_of(ja8), e, "official"};
                d.story_official++;
            } else {
                d.story.erase(mid);
                d.story_failing++;
            }
        }
    return true;
}

Table merge_master(const Derived& d, const Table& ours) {
    Table out;
    for (auto& [mid, sha] : d.jp_sha1) {
        auto o = ours.find(mid);
        bool our = o != ours.end() && o->second.ja_sha1 == sha;
        if (our && (o->second.source == "human" || o->second.source == "reviewed")) {
            out[mid] = o->second;
            continue;
        }
        auto dv = d.master.find(mid);
        if (dv != d.master.end()) {
            out[mid] = dv->second;
            continue;
        }
        if (our && (o->second.source == "machine" || o->second.source == "agent")) out[mid] = o->second;  // (agent: ranked as machine)
    }
    // new message_ids: our rows with no JP row and an empty ja_sha1 (client strings, human rows)
    for (auto& [mid, e] : ours)
        if (!d.jp_sha1.count(mid) && e.ja_sha1.empty()) out[mid] = e;
    return out;
}

std::map<std::string, Table> merge_story(const Derived& d, const Table& ours) {
    // per line (the last file's line of an id, as Python's dict): our human row, the derived, our machine row
    std::map<std::string, Entry> served;
    for (auto& [mid, sha] : d.story_sha1) {
        auto o = ours.find(mid);
        bool our = o != ours.end() && o->second.ja_sha1 == sha;
        auto dv = d.story.find(mid);
        if (our && (o->second.source == "human" || o->second.source == "reviewed")) served[mid] = o->second;
        else if (dv != d.story.end()) served[mid] = dv->second;
        else if (our && (o->second.source == "machine" || o->second.source == "agent")) served[mid] = o->second;
    }
    std::map<std::string, Table> out;
    for (auto& file : d.files)
        for (auto& [mid, ja] : file.lines) {
            auto it = served.find(mid);
            if (it != served.end()) out[file.stem][mid] = it->second;
        }
    return out;
}

// (d) the order of docs/server-rules.md#english-labels: the same Japanese takes the same English
Table resolve_labels(const Derived* d, const Table& master, const Table& ours) {
    auto rank = [](const std::string& src) {
        if (src == "human" || src == "reviewed") return 0;
        if (src == "official") return 1;
        if (src == "memory" || src == "template") return 2;
        return 3;  // machine, agent
    };
    Table out;
    for (auto& [ja, our] : ours) {
        bool our_en = !our.en.empty();
        if (our_en && rank(our.source) == 0) {
            out[ja] = our;
            continue;
        }
        // the served master rows with this Japanese: the best source, the first in label_mids' order
        const Entry* best = nullptr;
        if (d) {
            auto lm = d->label_mids.find(ja);
            if (lm != d->label_mids.end())
                for (auto& mid : lm->second) {
                    auto m = master.find(mid);
                    auto js = d->jp_sha1.find(mid);
                    if (m == master.end() || js == d->jp_sha1.end() || m->second.ja_sha1 != js->second) continue;
                    if (!best || rank(m->second.source) < rank(best->source)) best = &m->second;
                }
        }
        const Entry* mem = nullptr;
        if (d) {
            auto it = d->labels.find(ja);
            if (it != d->labels.end()) mem = &it->second;
        }
        const Entry* pick = nullptr;
        if (best && rank(best->source) <= 2) pick = best;
        else if (mem) pick = mem;
        else if (our_en) pick = &our;
        else if (best) pick = best;
        if (pick) out[ja] = Entry{our.ja_sha1, pick->en, pick->source};
    }
    return out;
}

std::string table_text(const Table& t) {
    std::string s = "message_id\tja_sha1\ten\tsource\n";
    for (auto& [mid, e] : t) s += mid + "\t" + e.ja_sha1 + "\t" + e.en + "\t" + e.source + "\n";
    return s;
}

}  // namespace soa::server::english
