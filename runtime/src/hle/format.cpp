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

}  // namespace soa
