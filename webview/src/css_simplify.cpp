// The CSS simplifier (soawebview/page.h simplify_css), from the Dragalia Lost project's renderer
// (platformdl/src/webview_page.cpp) unchanged: its rewrites target Tailwind v4 stylesheets; this
// game's pages (CSS 2.1 with a few CSS3 properties) mostly pass through.
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

#include "soawebview/page.h"

namespace soa::webview {

// ===========================================================================================
// CSS simplifier
//
// litehtml 0.10 implements CSS 2.1 with flexbox, custom properties and media queries; it drops
// whole @layer / @supports blocks and every declaration with calc(), oklch() or a logical
// property, which is all of a Tailwind v4 stylesheet (Dawnshard's pages). This rewrites them:
//   @layer X { R } -> R;  @layer a, b; -> nothing;  @supports: only Tailwind's custom-property
//   fallback block is kept (unwrapped), the others (color-mix() and such) are dropped; @property,
//   @keyframes, @container, @font-face: dropped; @media kept (its contents rewritten);
//   rules nested in a declaration block (CSS nesting: &:hover ...): dropped;
//   var(--x) of a :root/:host custom property, or of one the same rule sets: substituted;
//   var(--x, fallback) of a property whose only global value is `initial`: the fallback;
//   calc() of lengths and numbers: evaluated; oklch(): rgba(); :where( -> :is(;
//   padding/margin-inline/-block(-start/-end), inset: the physical properties.
namespace {

size_t skip_ws_comments(const std::string& s, size_t i) {
    for (;;) {
        while (i < s.size() && isspace((unsigned char)s[i])) i++;
        if (i + 1 < s.size() && s[i] == '/' && s[i + 1] == '*') {
            size_t e = s.find("*/", i + 2);
            i = e == std::string::npos ? s.size() : e + 2;
            continue;
        }
        return i;
    }
}

// Index of the first of `stops` at nesting depth 0 from i (strings, comments, (), [] skipped), or npos.
size_t find_top(const std::string& s, size_t i, const char* stops) {
    int depth = 0;
    while (i < s.size()) {
        char c = s[i];
        if (c == '"' || c == '\'') {
            for (i++; i < s.size() && s[i] != c; i++)
                if (s[i] == '\\') i++;
            i++;
            continue;
        }
        if (c == '\\') {
            i += 2;
            continue;
        }
        if (c == '/' && i + 1 < s.size() && s[i + 1] == '*') {
            size_t e = s.find("*/", i + 2);
            i = e == std::string::npos ? s.size() : e + 2;
            continue;
        }
        if (depth == 0 && strchr(stops, c)) return i;
        if (c == '(' || c == '[') depth++;
        else if ((c == ')' || c == ']') && depth > 0) depth--;
        i++;
    }
    return std::string::npos;
}

// s[open] == '{': the index of its '}' (or s.size()).
size_t block_end(const std::string& s, size_t open) {
    int depth = 0;
    for (size_t i = open; i < s.size();) {
        size_t j = find_top(s, i, "{}");
        if (j == std::string::npos) return s.size();
        if (s[j] == '{') depth++;
        else if (--depth == 0) return j;
        i = j + 1;
    }
    return s.size();
}

std::string trim(const std::string& s) {
    size_t a = 0, b = s.size();
    while (a < b && isspace((unsigned char)s[a])) a++;
    while (b > a && isspace((unsigned char)s[b - 1])) b--;
    return s.substr(a, b - a);
}

struct CssRule {
    std::string media;  // "" or the @media prelude it is in
    std::string selector;
    std::vector<std::pair<std::string, std::string>> decls;
};

void parse_decls(const std::string& body, std::vector<std::pair<std::string, std::string>>& out) {
    size_t i = 0;
    while (i < body.size()) {
        i = skip_ws_comments(body, i);
        if (i >= body.size()) break;
        size_t j = find_top(body, i, ";{");
        if (j != std::string::npos && body[j] == '{') {  // a nested rule: dropped
            i = block_end(body, j) + 1;
            continue;
        }
        if (j == std::string::npos) j = body.size();
        std::string d = body.substr(i, j - i);
        i = j + 1;
        size_t c = d.find(':');
        if (c == std::string::npos) continue;
        std::string name = trim(d.substr(0, c)), value = trim(d.substr(c + 1));
        if (!name.empty()) out.emplace_back(name, value);
    }
}

std::string fmt_num(double v);

// Media Queries 4 ranges, (width>=40rem), as level 3's (min-width:640px), which litehtml knows.
std::string rewrite_media(const std::string& q) {
    std::string out;
    size_t i = 0;
    while (i < q.size()) {
        size_t open = q.find('(', i);
        if (open == std::string::npos) break;
        size_t close = q.find(')', open);
        if (close == std::string::npos) break;
        out += q.substr(i, open - i);
        std::string f = q.substr(open + 1, close - open - 1), g;
        for (char ch : f)
            if (!isspace((unsigned char)ch)) g += ch;
        std::string rep = "(" + f + ")";
        for (const char* name : {"width", "height"}) {
            size_t n = strlen(name);
            if (g.compare(0, n, name) != 0 || g.size() <= n || (g[n] != '<' && g[n] != '>')) continue;
            bool ge = g[n] == '>', eq = g.size() > n + 1 && g[n + 1] == '=';
            const char* v = g.c_str() + n + 1 + (eq ? 1 : 0);
            char* end;
            double x = strtod(v, &end);
            if (end == v) break;
            if (!strcmp(end, "rem") || !strcmp(end, "em")) x *= 16;
            else if (strcmp(end, "px") && *end) break;
            if (!eq) x += ge ? 0.02 : -0.02;
            rep = std::string("(") + (ge ? "min-" : "max-") + name + ":" + fmt_num(x) + "px)";
        }
        out += rep;
        i = close + 1;
    }
    return out + q.substr(std::min(i, q.size()));
}

void parse_rules(const std::string& s, const std::string& media, std::vector<CssRule>& rules, std::string& imports) {
    size_t i = 0;
    while (true) {
        i = skip_ws_comments(s, i);
        if (i >= s.size()) return;
        if (s[i] == '@') {
            size_t n = i + 1;
            while (n < s.size() && (isalnum((unsigned char)s[n]) || s[n] == '-')) n++;
            std::string name = s.substr(i + 1, n - i - 1);
            for (auto& ch : name) ch = (char)tolower((unsigned char)ch);
            size_t j = find_top(s, n, ";{");
            if (j == std::string::npos) return;
            std::string prelude = trim(s.substr(n, j - n));
            if (s[j] == ';') {
                if (name == "import") imports += "@import " + prelude + ";\n";
                i = j + 1;
                continue;
            }
            size_t e = block_end(s, j);
            std::string inner = s.substr(j + 1, e - j - 1);
            if (name == "layer") parse_rules(inner, media, rules, imports);
            else if (name == "media") {
                std::string q = rewrite_media(prelude);
                parse_rules(inner, media.empty() ? q : media + " and " + q, rules, imports);
            }
            else if (name == "supports" && prelude.find("-webkit-hyphens") != std::string::npos) parse_rules(inner, media, rules, imports);
            i = e + 1;
            continue;
        }
        size_t j = find_top(s, i, "{;");
        if (j == std::string::npos) return;
        if (s[j] == ';') {  // stray
            i = j + 1;
            continue;
        }
        size_t e = block_end(s, j);
        CssRule r;
        r.media = media;
        r.selector = trim(s.substr(i, j - i));
        parse_decls(s.substr(j + 1, e - j - 1), r.decls);
        rules.push_back(std::move(r));
        i = e + 1;
    }
}

// ---- values

std::string fmt_num(double v) {
    char b[32];
    snprintf(b, sizeof b, "%.4f", v);
    std::string s = b;
    while (!s.empty() && s.back() == '0') s.pop_back();
    if (!s.empty() && s.back() == '.') s.pop_back();
    if (s == "-0") s = "0";
    return s;
}

// The arguments of the function call whose '(' is at s[open]: [open+1, close).
size_t paren_end(const std::string& s, size_t open) {
    int depth = 0;
    for (size_t i = open; i < s.size(); i++) {
        if (s[i] == '(') depth++;
        else if (s[i] == ')' && --depth == 0) return i;
    }
    return std::string::npos;
}

using VarMap = std::unordered_map<std::string, std::string>;

// var() substitution (see above). depth: recursion guard for values referring to others.
std::string subst_vars(const std::string& v, const VarMap& local, const VarMap& global, const VarMap& initial_only, int depth = 0) {
    if (depth > 8 || v.find("var(") == std::string::npos) return v;
    std::string out;
    size_t i = 0;
    while (true) {
        size_t p = v.find("var(", i);
        if (p == std::string::npos || (p > 0 && (isalnum((unsigned char)v[p - 1]) || v[p - 1] == '-'))) {
            if (p == std::string::npos) {
                out += v.substr(i);
                break;
            }
            out += v.substr(i, p + 4 - i);
            i = p + 4;
            continue;
        }
        size_t close = paren_end(v, p + 3);
        if (close == std::string::npos) {
            out += v.substr(i);
            break;
        }
        out += v.substr(i, p - i);
        std::string args = v.substr(p + 4, close - p - 4);
        size_t comma = find_top(args, 0, ",");
        std::string name = trim(args.substr(0, comma));
        std::string fallback = comma == std::string::npos ? "" : trim(args.substr(comma + 1));
        const std::string* val = nullptr;
        if (auto it = local.find(name); it != local.end()) val = &it->second;
        else if (auto it2 = global.find(name); it2 != global.end()) val = &it2->second;
        if (val && *val == "initial" && comma != std::string::npos) val = nullptr;  // the guaranteed-invalid value: the fallback
        if (val) out += subst_vars(*val, local, global, initial_only, depth + 1);
        else if (comma != std::string::npos && (initial_only.count(name) || !global.count(name)))
            out += subst_vars(fallback, local, global, initial_only, depth + 1);
        else out += v.substr(p, close + 1 - p);
        i = close + 1;
    }
    return out;
}

// calc(): numbers with units; + - * / and parentheses. Fails (false) on mixed units in a sum.
struct Q {
    double v = 0;
    std::string unit;
};
struct CalcParser {
    const std::string& s;
    size_t i = 0;
    bool ok = true;
    explicit CalcParser(const std::string& str) : s(str) {}
    void ws() {
        while (i < s.size() && isspace((unsigned char)s[i])) i++;
    }
    Q primary() {
        ws();
        if (i < s.size() && s[i] == '(') {
            i++;
            Q q = sum();
            ws();
            if (i < s.size() && s[i] == ')') i++;
            else ok = false;
            return q;
        }
        if (s.compare(i, 5, "calc(") == 0) {
            i += 4;
            return primary();
        }
        char* end = nullptr;
        double v = strtod(s.c_str() + i, &end);
        if (end == s.c_str() + i) {
            ok = false;
            return {};
        }
        i = end - s.c_str();
        Q q{v, ""};
        while (i < s.size() && (isalpha((unsigned char)s[i]) || s[i] == '%')) q.unit += s[i++];
        if (q.unit == "rem") q = {v * 16, "px"};  // the root font size is the default 16px (Tailwind: calc(.65rem + 4px))
        return q;
    }
    Q product() {
        Q a = primary();
        for (;;) {
            ws();
            if (i >= s.size() || (s[i] != '*' && s[i] != '/')) return a;
            char op = s[i++];
            Q b = primary();
            if (op == '*') {
                if (!a.unit.empty() && !b.unit.empty()) ok = false;
                a = {a.v * b.v, a.unit.empty() ? b.unit : a.unit};
            } else {
                if (!b.unit.empty() || b.v == 0) ok = false;
                else a.v /= b.v;
            }
        }
    }
    Q sum() {
        Q a = product();
        for (;;) {
            ws();
            if (i >= s.size() || (s[i] != '+' && s[i] != '-')) return a;
            char op = s[i++];
            Q b = product();
            if (a.unit != b.unit) {
                if (a.v == 0 && a.unit.empty()) a.unit = b.unit;
                else if (!(b.v == 0 && b.unit.empty())) ok = false;
            }
            a.v += op == '+' ? b.v : -b.v;
        }
    }
};

std::string eval_calcs(const std::string& v) {
    std::string out;
    size_t i = 0;
    while (true) {
        size_t p = v.find("calc(", i);
        if (p == std::string::npos) {
            out += v.substr(i);
            return out;
        }
        size_t close = paren_end(v, p + 4);
        if (close == std::string::npos) {
            out += v.substr(i);
            return out;
        }
        out += v.substr(i, p - i);
        std::string expr = v.substr(p + 5, close - p - 5);
        CalcParser cp(expr);
        Q q = cp.sum();
        cp.ws();
        if (cp.ok && cp.i == expr.size()) out += fmt_num(q.v) + q.unit;
        else out += v.substr(p, close + 1 - p);
        i = close + 1;
    }
}

uint8_t to_srgb8(double c) {
    c = std::clamp(c, 0.0, 1.0);
    c = c <= 0.0031308 ? 12.92 * c : 1.055 * std::pow(c, 1 / 2.4) - 0.055;
    return (uint8_t)std::lround(c * 255);
}

std::string convert_oklch(const std::string& v) {
    std::string out;
    size_t i = 0;
    while (true) {
        size_t p = v.find("oklch(", i);
        if (p == std::string::npos) {
            out += v.substr(i);
            return out;
        }
        size_t close = paren_end(v, p + 5);
        if (close == std::string::npos) {
            out += v.substr(i);
            return out;
        }
        out += v.substr(i, p - i);
        std::string args = v.substr(p + 6, close - p - 6);
        for (auto& ch : args)
            if (ch == '/' || ch == ',') ch = ' ';
        double n[4] = {0, 0, 0, 1};
        bool pct[4] = {};
        int k = 0;
        const char* c = args.c_str();
        bool ok = true;
        while (*c && k < 4) {
            while (*c == ' ') c++;
            if (!*c) break;
            if (!strncmp(c, "none", 4)) {
                n[k++] = 0, c += 4;
                continue;
            }
            char* end;
            double x = strtod(c, &end);
            if (end == c) {
                ok = false;
                break;
            }
            c = end;
            if (*c == '%') pct[k] = true, c++;
            while (isalpha((unsigned char)*c)) c++;  // deg
            n[k++] = x;
        }
        if (!ok || k < 3) {
            out += v.substr(p, close + 1 - p);
        } else {
            double L = pct[0] ? n[0] / 100 : n[0], C = pct[1] ? n[1] * 0.004 : n[1], h = n[2] * M_PI / 180;
            double A = k > 3 ? (pct[3] ? n[3] / 100 : n[3]) : 1;
            double a = C * std::cos(h), b = C * std::sin(h);
            double l_ = L + 0.3963377774 * a + 0.2158037573 * b, m_ = L - 0.1055613458 * a - 0.0638541728 * b,
                   s_ = L - 0.0894841775 * a - 1.2914855480 * b;
            double l = l_ * l_ * l_, m = m_ * m_ * m_, s = s_ * s_ * s_;
            double r = 4.0767416621 * l - 3.3077115913 * m + 0.2309699292 * s;
            double g = -1.2684380046 * l + 2.6097574011 * m - 0.3413193965 * s;
            double bl = -0.0041960863 * l - 0.7034186147 * m + 1.7076147010 * s;
            char buf[64];
            snprintf(buf, sizeof buf, "rgba(%d, %d, %d, %s)", to_srgb8(r), to_srgb8(g), to_srgb8(bl), fmt_num(std::clamp(A, 0.0, 1.0)).c_str());
            out += buf;
        }
        i = close + 1;
    }
}

std::vector<std::string> split_values(const std::string& v) {
    std::vector<std::string> out;
    size_t i = 0;
    while (i < v.size()) {
        while (i < v.size() && isspace((unsigned char)v[i])) i++;
        if (i >= v.size()) break;
        size_t j = find_top(v, i, " \t\n");
        if (j == std::string::npos) j = v.size();
        out.push_back(v.substr(i, j - i));
        i = j;
    }
    return out;
}

void emit_decl(std::string& out, const std::string& name, const std::string& value) {
    auto put = [&](const std::string& n, const std::string& v) { out += n + ":" + v + ";"; };
    auto pair = [&](const char* a, const char* b) {
        auto vs = split_values(value);
        if (vs.empty()) return;
        put(a, vs[0]);
        put(b, vs.size() > 1 ? vs[1] : vs[0]);
    };
    for (const char* box : {"padding", "margin"}) {
        std::string b = box;
        if (name == b + "-inline") return pair((b + "-left").c_str(), (b + "-right").c_str());
        if (name == b + "-block") return pair((b + "-top").c_str(), (b + "-bottom").c_str());
        if (name == b + "-inline-start") return put(b + "-left", value);
        if (name == b + "-inline-end") return put(b + "-right", value);
        if (name == b + "-block-start") return put(b + "-top", value);
        if (name == b + "-block-end") return put(b + "-bottom", value);
    }
    if (name == "inset") {
        auto vs = split_values(value);
        if (vs.empty()) return;
        const char* sides[4] = {"top", "right", "bottom", "left"};
        for (int k = 0; k < 4; k++) {
            size_t idx = vs.size() == 1 ? 0 : vs.size() == 2 ? k % 2 : vs.size() == 3 ? (k == 3 ? 1 : k) : k;
            put(sides[k], vs[std::min(idx, vs.size() - 1)]);
        }
        return;
    }
    if (name == "inset-inline") return pair("left", "right");
    if (name == "inset-block") return pair("top", "bottom");
    put(name, value);
}

}  // namespace

std::string simplify_css(const std::string& css) {
    std::vector<CssRule> rules;
    std::string out;
    parse_rules(css, "", rules, out);
    // The global custom properties: :root / :host ones (Tailwind's theme), and the ones only ever
    // set to `initial` (Tailwind's per-element defaults: a var() of them takes its fallback).
    VarMap global, initial_only, any;
    for (auto& r : rules) {
        // (and the universal selector's: Tailwind's --tw-* defaults, e.g. --tw-border-style: solid)
        bool root = r.media.empty() && (r.selector.find(":root") != std::string::npos || r.selector.find(":host") != std::string::npos ||
                                        r.selector.rfind("*", 0) == 0);
        for (auto& [n, v] : r.decls) {
            if (n.rfind("--", 0) != 0) continue;
            if (root) global[n] = v;
            if (v == "initial") {
                if (!any.count(n)) initial_only[n] = v;
            } else initial_only.erase(n);
            any[n] = v;
        }
    }
    // Theme values referring to others (--default-font-family: var(--font-sans)), evaluated.
    for (auto& [n, v] : global) v = convert_oklch(eval_calcs(subst_vars(v, {}, global, initial_only)));
    for (auto& r : rules) {
        VarMap local;
        for (auto& [n, v] : r.decls)
            if (n.rfind("--", 0) == 0 && v.find("var(") == std::string::npos) local[n] = v;
        std::string sel = r.selector;
        for (size_t p; (p = sel.find(":where(")) != std::string::npos;) sel.replace(p, 7, ":is(");
        std::string body;
        for (auto& [n, v] : r.decls) {
            std::string val = convert_oklch(eval_calcs(subst_vars(v, local, global, initial_only)));
            emit_decl(body, n, val);
        }
        if (body.empty()) continue;
        if (!r.media.empty()) out += "@media " + r.media + "{";
        out += sel + "{" + body + "}";
        if (!r.media.empty()) out += "}";
        out += "\n";
    }
    return out;
}

}  // namespace soa::webview
