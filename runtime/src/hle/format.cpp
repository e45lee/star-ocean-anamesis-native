#include <cstring>
#include <mutex>
#include "hle/format.h"

#include <cstdio>
#include <cwchar>

#include "core/log.h"

namespace soa {

namespace {

template <typename C>
int host_snprintf(C* buf, size_t n, const C* fmt, ...);

template <>
int host_snprintf<char>(char* buf, size_t n, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int r = vsnprintf(buf, n, fmt, ap);
    va_end(ap);
    return r;
}
template <>
int host_snprintf<wchar_t>(wchar_t* buf, size_t n, const wchar_t* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int r = vswprintf(buf, n, fmt, ap);
    va_end(ap);
    return r;
}

// Formats one conversion spec with a single argument, appending to out.
template <typename C, typename T>
void emit(std::basic_string<C>& out, const std::basic_string<C>& spec, T v) {
    C small[256];
    int n = host_snprintf<C>(small, 256, spec.c_str(), v);
    if (n < 0) {
        if constexpr (std::is_same_v<C, wchar_t>) {
            // vswprintf fails when the result doesn't fit; retry larger.
            for (size_t cap = 4096; cap <= (1u << 24); cap *= 4) {
                std::vector<C> big(cap);
                n = host_snprintf<C>(big.data(), cap, spec.c_str(), v);
                if (n >= 0) {
                    out.append(big.data(), n);
                    return;
                }
            }
        }
        return;
    }
    if (n < 256) {
        out.append(small, n);
        return;
    }
    std::vector<C> big(n + 1);
    host_snprintf<C>(big.data(), n + 1, spec.c_str(), v);
    out.append(big.data(), n);
}

template <typename C>
std::basic_string<C> format_impl(const C* fmt, VaSource& va) {
    std::basic_string<C> out;
    if (!fmt) return out;
    const C* p = fmt;
    while (*p) {
        if (*p != '%') {
            out.push_back(*p++);
            continue;
        }
        const C* start = p++;
        if (*p == '%') {
            out.push_back('%');
            p++;
            continue;
        }
        std::basic_string<C> spec;
        spec.push_back('%');
        // positional args are not supported
        const C* q = p;
        while (*q >= '0' && *q <= '9') q++;
        if (*q == '$') LOGW("fmt", "positional printf argument not supported");
        // flags
        while (*p == '-' || *p == '+' || *p == ' ' || *p == '#' || *p == '0' || *p == '\'') spec.push_back(*p++);
        // width
        if (*p == '*') {
            int w = (int)va.next_int();
            auto ws = std::to_string(w);
            spec.append(ws.begin(), ws.end());
            p++;
        } else {
            while (*p >= '0' && *p <= '9') spec.push_back(*p++);
        }
        // precision
        if (*p == '.') {
            spec.push_back(*p++);
            if (*p == '*') {
                int pr = (int)va.next_int();
                if (pr < 0) {
                    spec.pop_back();  // negative precision = omitted
                } else {
                    auto ps = std::to_string(pr);
                    spec.append(ps.begin(), ps.end());
                }
                p++;
            } else {
                while (*p >= '0' && *p <= '9') spec.push_back(*p++);
            }
        }
        // length
        int len = 0;  // 0 none, 1 hh, 2 h, 3 l, 4 ll, 5 L, 6 j/z/t
        if (*p == 'h') {
            p++;
            len = 2;
            if (*p == 'h') p++, len = 1;
        } else if (*p == 'l') {
            p++;
            len = 3;
            if (*p == 'l') p++, len = 4;
        } else if (*p == 'L' || *p == 'q') {
            p++;
            len = 5;
        } else if (*p == 'j' || *p == 'z' || *p == 't') {
            p++;
            len = 6;
        }
        C conv = *p;
        if (!conv) {
            out.append(start, p);
            break;
        }
        p++;
        switch (conv) {
        case 'd':
        case 'i': {
            u64 raw = va.next_int();
            s64 v;
            switch (len) {
            case 1: v = (signed char)raw; break;
            case 2: v = (short)raw; break;
            case 3:
            case 4:
            case 5:
            case 6: v = (s64)raw; break;
            default: v = (int)raw; break;
            }
            spec.push_back('l');
            spec.push_back('l');
            spec.push_back(conv);
            emit<C>(out, spec, (long long)v);
            break;
        }
        case 'u':
        case 'o':
        case 'x':
        case 'X': {
            u64 raw = va.next_int();
            u64 v;
            switch (len) {
            case 1: v = (unsigned char)raw; break;
            case 2: v = (unsigned short)raw; break;
            case 3:
            case 4:
            case 5:
            case 6: v = raw; break;
            default: v = (unsigned)raw; break;
            }
            spec.push_back('l');
            spec.push_back('l');
            spec.push_back(conv);
            emit<C>(out, spec, (unsigned long long)v);
            break;
        }
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'a':
        case 'A': {
            if (len == 5) {
                V128 q = va.next_quad();
                __float128 f;
                std::memcpy(&f, &q, 16);
                spec.push_back('L');
                spec.push_back(conv);
                emit<C>(out, spec, (long double)f);
            } else {
                spec.push_back(conv);
                emit<C>(out, spec, va.next_double());
            }
            break;
        }
        case 'c':
        case 'C': {
            u64 raw = va.next_int();
            if (len == 3 || conv == 'C') {
                spec.push_back('l');
                spec.push_back('c');
                emit<C>(out, spec, (wint_t)raw);
            } else {
                spec.push_back('c');
                emit<C>(out, spec, (int)raw);
            }
            break;
        }
        case 's':
        case 'S': {
            u64 raw = va.next_int();
            if (len == 3 || conv == 'S') {
                spec.push_back('l');
                spec.push_back('s');
                emit<C>(out, spec, raw ? (const wchar_t*)raw : L"(null)");
            } else {
                spec.push_back('s');
                emit<C>(out, spec, raw ? (const char*)raw : "(null)");
            }
            break;
        }
        case 'p': {
            spec.push_back('p');
            emit<C>(out, spec, (void*)va.next_int());
            break;
        }
        case 'n': {
            u64 raw = va.next_int();
            if (raw) {
                switch (len) {
                case 1: *(signed char*)raw = (signed char)out.size(); break;
                case 2: *(short*)raw = (short)out.size(); break;
                case 3:
                case 4:
                case 6: *(long long*)raw = (long long)out.size(); break;
                default: *(int*)raw = (int)out.size(); break;
                }
            }
            break;
        }
        case 'm': {
            spec.push_back('m');
            emit<C>(out, spec, 0);
            break;
        }
        default:
            out.append(start, p);
            break;
        }
    }
    return out;
}

}  // namespace

std::string guest_format(const char* fmt, VaSource& va) { return format_impl<char>(fmt, va); }
std::wstring guest_wformat(const wchar_t* fmt, VaSource& va) { return format_impl<wchar_t>(fmt, va); }

std::vector<u64> scanf_args(const char* fmt, VaSource& va) {
    std::vector<u64> out;
    const char* p = fmt;
    while (p && *p) {
        if (*p++ != '%') continue;
        if (*p == '%') {
            p++;
            continue;
        }
        bool suppress = false;
        if (*p == '*') suppress = true, p++;
        while (*p >= '0' && *p <= '9') p++;
        while (*p == 'h' || *p == 'l' || *p == 'L' || *p == 'q' || *p == 'j' || *p == 'z' || *p == 't' || *p == 'm') p++;
        char conv = *p;
        if (!conv) break;
        p++;
        if (conv == '[') {
            if (*p == '^') p++;
            if (*p == ']') p++;
            while (*p && *p != ']') p++;
            if (*p) p++;
        }
        if (!suppress) out.push_back(va.next_int());
        if (out.size() >= 32) break;
    }
    out.resize(32, 0);
    return out;
}

std::string host_scanf_format(const char* fmt, bool win) {
    std::string out;
    if (!fmt) return out;
    if (!win) return fmt;
    const char* p = fmt;
    while (*p) {
        if (*p != '%') {
            out.push_back(*p++);
            continue;
        }
        out.push_back(*p++);
        if (*p == '%') {
            out.push_back(*p++);
            continue;
        }
        if (*p == '*') out.push_back(*p++);
        while (*p >= '0' && *p <= '9') out.push_back(*p++);
        // (the 64-bit integer lengths spelled as `ll`, which every Windows CRT's scanf reads: z, j, t
        // are 64-bit on both ABIs, but older CRTs don't know them)
        if ((*p == 'l' || *p == 'z' || *p == 'j' || *p == 't') && p[1] != 'l' && p[1] && std::strchr("dioxXun", p[1])) {
            out += "ll";
            p++;
        }
        while (*p == 'h' || *p == 'l' || *p == 'L' || *p == 'q' || *p == 'j' || *p == 'z' || *p == 't' || *p == 'm') out.push_back(*p++);
        if (*p == '[') {
            out.push_back(*p++);
            if (*p == '^') out.push_back(*p++);
            if (*p == ']') out.push_back(*p++);
            while (*p && *p != ']') out.push_back(*p++);
            if (*p) out.push_back(*p++);
        } else if (*p) {
            out.push_back(*p++);
        }
    }
    return out;
}

// glibc's random() (random_r.c, TYPE_3: x**31 + x**3 + 1, seeded with 1 as an unseeded rand()):
// r[i] = r[i-3] + r[i-31], the first 310 outputs dropped, each output the sum >> 1.
s32 glibc_random(bool reset) {
    static std::mutex m;
    static u32 r[34];
    static int i = -1;
    std::lock_guard lk(m);
    if (reset || i < 0) {
        s32 w[34];
        w[0] = 1;
        for (int k = 1; k < 31; k++) {
            w[k] = (s32)((16807LL * w[k - 1]) % 2147483647);
            if (w[k] < 0) w[k] += 2147483647;
        }
        for (int k = 31; k < 34; k++) w[k] = w[k - 31];
        for (int k = 0; k < 34; k++) r[k] = (u32)w[k];
        i = 34;
        for (int k = 0; k < 310; k++) {
            r[i % 34] = r[(i - 31) % 34] + r[(i - 3) % 34];
            i++;
        }
        if (reset) return 0;
    }
    u32 v = r[(i - 31) % 34] + r[(i - 3) % 34];
    r[i % 34] = v;
    i++;
    if (i >= 34 * 1000000) i = i % 34 + 34;
    return (s32)(v >> 1);
}

s32 guest_rand() {
#ifdef _WIN32
    return glibc_random();
#else
    return (s32)rand();
#endif
}

namespace {
// ISO 8601 week-based year and week number (%G, %V)
int iso_weeks_in_year(long y) {
    auto p = [](long v) { return ((v + v / 4 - v / 100 + v / 400) % 7 + 7) % 7; };
    return 52 + (p(y) == 4 || p(y - 1) == 3);
}
void iso_week(const struct tm& t, int* year, int* week) {
    int y = t.tm_year + 1900;
    int w = (t.tm_yday - (t.tm_wday + 6) % 7 + 10) / 7;
    if (w < 1) {
        y--;
        w = iso_weeks_in_year(y);
    } else if (w > iso_weeks_in_year(y)) {
        y++;
        w = 1;
    }
    *year = y, *week = w;
}
}  // namespace

std::string strftime_c89_format(const char* fmt, const struct tm& t, long gmtoff) {
    std::string out;
    auto lit = [&](const std::string& s) {
        for (char ch : s) {
            if (ch == '%') out += '%';
            out += ch;
        }
    };
    for (const char* p = fmt; *p; p++) {
        if (*p != '%') {
            out += *p;
            continue;
        }
        const char* start = p++;
        char flag = 0;  // glibc / bionic: '-' no padding, '_' spaces, '0' zeros
        while (*p == '-' || *p == '_' || *p == '0' || *p == '^' || *p == '#') flag = *p++;
        while (*p == 'E' || *p == 'O') p++;  // (alternative forms: the C locale has none)
        if (!*p) {  // a trailing '%': as it was
            out.append(start);
            break;
        }
        char conv = *p;
        // a number with the default padding char and width, or the flag's
        auto num = [&](long v, int width, char pad) {
            if (flag == '-') width = 0;
            else if (flag == '_') pad = ' ';
            else if (flag == '0') pad = '0';
            std::string d = std::to_string(v < 0 ? -v : v);
            std::string r = v < 0 ? "-" : "";
            for (int i = (int)d.size(); i < width; i++) r += pad;
            lit(r + d);
        };
        int hour12 = t.tm_hour % 12 == 0 ? 12 : t.tm_hour % 12;
        int iy, iw;
        switch (conv) {
        // C89 conversions msvcrt has: kept (with a flag, numeric ones are written out here)
        case 'd': flag ? num(t.tm_mday, 2, '0') : (void)(out += "%d"); break;
        case 'H': flag ? num(t.tm_hour, 2, '0') : (void)(out += "%H"); break;
        case 'I': flag ? num(hour12, 2, '0') : (void)(out += "%I"); break;
        case 'j': flag ? num(t.tm_yday + 1, 3, '0') : (void)(out += "%j"); break;
        case 'm': flag ? num(t.tm_mon + 1, 2, '0') : (void)(out += "%m"); break;
        case 'M': flag ? num(t.tm_min, 2, '0') : (void)(out += "%M"); break;
        case 'S': flag ? num(t.tm_sec, 2, '0') : (void)(out += "%S"); break;
        case 'y': flag ? num((t.tm_year + 1900) % 100, 2, '0') : (void)(out += "%y"); break;
        case 'Y': flag ? num(t.tm_year + 1900, 1, '0') : (void)(out += "%Y"); break;
        case 'a': case 'A': case 'b': case 'B': case 'c': case 'p': case 'U': case 'w': case 'W':
        case 'x': case 'X': case 'Z': case '%':
            out += '%';
            out += conv;
            break;
        // the rest: written out
        case 'F': out += "%Y-%m-%d"; break;
        case 'T': out += "%H:%M:%S"; break;
        case 'D': out += "%m/%d/%y"; break;
        case 'R': out += "%H:%M"; break;
        case 'r': out += "%I:%M:%S %p"; break;
        case 'h': out += "%b"; break;
        case 'n': out += '\n'; break;
        case 't': out += '\t'; break;
        case 'e': num(t.tm_mday, 2, ' '); break;
        case 'k': num(t.tm_hour, 2, ' '); break;
        case 'l': num(hour12, 2, ' '); break;
        case 'C': num((t.tm_year + 1900) / 100, 2, '0'); break;
        case 'u': num(t.tm_wday == 0 ? 7 : t.tm_wday, 1, '0'); break;
        case 'P': lit(t.tm_hour < 12 ? "am" : "pm"); break;
        case 'G': iso_week(t, &iy, &iw); num(iy, 1, '0'); break;
        case 'g': iso_week(t, &iy, &iw); num(iy % 100, 2, '0'); break;
        case 'V': iso_week(t, &iy, &iw); num(iw, 2, '0'); break;
        case 'z': {
            long a = gmtoff < 0 ? -gmtoff : gmtoff;
            char b[16];
            snprintf(b, sizeof b, "%c%02ld%02ld", gmtoff < 0 ? '-' : '+', a / 3600, a / 60 % 60);
            lit(b);
            break;
        }
        case 's': {
            // the tm as local time with the given offset: days from the civil date, then the offset
            long long y = t.tm_year + 1900LL, m = t.tm_mon + 1;
            y -= m <= 2;
            long long era = (y >= 0 ? y : y - 399) / 400, yoe = y - era * 400;
            long long doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + t.tm_mday - 1, doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
            long long days = era * 146097 + doe - 719468;
            lit(std::to_string(days * 86400 + t.tm_hour * 3600LL + t.tm_min * 60LL + t.tm_sec - gmtoff));
            break;
        }
        default: out.append(start, p + 1); break;  // unknown: as it was (the host decides)
        }
    }
    return out;
}

}  // namespace soa
