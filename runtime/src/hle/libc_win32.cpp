// Bionic libc on a Windows host (port/PLAN.md 5b, W): the imports whose host function can't be
// bound directly there, because the guest's ABI (Linux / bionic, LP64) differs from MinGW's (LLP64):
//   - long is 64-bit in the guest (atol / strtol / strtoul);
//   - wchar_t is 32-bit UTF-32 in the guest, 16-bit on Windows (the wide-character functions are
//     implemented here over char32_t; the multibyte encoding is UTF-8, as in bionic);
//   - no glibc locale_t (bionic's locales are "C" / "C.UTF-8" anyway: one C locale here);
//   - struct tm / timeval / timespec / stat have other layouts or field widths;
//   - errno values above ERANGE differ (hle/guest_errno.h), open() flags differ;
//   - no mmap, futex, sysconf, getrlimit: VirtualAlloc, WaitOnAddress, GetSystemInfo, constants;
//   - guest descriptors: CRT descriptors for files, core/host_fd.h for pipes.
// The other files' Linux-only registrations are under #ifndef _WIN32; register_libc_win32 runs
// after them (hle_init). Imports still missing on Windows (sockets, select, ...) resolve to the
// "unimplemented import" thunk, which names them when the guest calls one.
#ifdef _WIN32
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <windows.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstring>
#include <random>
#include <string>

#include "core/device.h"
#include "core/hle.h"
#include "core/host_fd.h"
#include "core/host_mem.h"
#include "core/log.h"
#include "core/vfs.h"
#include "hle/guest_errno.h"

namespace soa {

void to_bionic_stat(const struct stat& s, u64 dst);  // libc_stdio.cpp
void register_net_win32(Hle& h);                     // net_win32.cpp

int guest_errno(int host) {
    switch (host) {
    case EDEADLK: return 35;
    case ENAMETOOLONG: return 36;
    case ENOLCK: return 37;
    case ENOSYS: return 38;
    case ENOTEMPTY: return 39;
    case EILSEQ: return 84;
    case ETIMEDOUT: return 110;
    case EWOULDBLOCK: return 11;
    case EINPROGRESS: return 115;
    case EALREADY: return 114;
    case ENOTSOCK: return 88;
    case EADDRINUSE: return 98;
    case EADDRNOTAVAIL: return 99;
    case ENETUNREACH: return 101;
    case ECONNABORTED: return 103;
    case ECONNRESET: return 104;
    case ENOBUFS: return 105;
    case EISCONN: return 106;
    case ENOTCONN: return 107;
    case ECONNREFUSED: return 111;
    case EHOSTUNREACH: return 113;
    case EOVERFLOW: return 75;
    case ECANCELED: return 125;
    case EOPNOTSUPP: return 95;
    default: return host;  // 1..34 are the same numbers
    }
}

namespace {

void set_errno_guest() { errno = guest_errno(errno); }

// ---- memory ----
// mmap: anonymous private mappings only (what the game asks for); Linux PROT / MAP values.
void th_mmap(Cpu& c) {
    u64 addr = c.x(0), len = c.x(1);
    int flags = (int)c.x(3), fd = (int)c.x(4);
    constexpr int kMapAnonymous = 0x20, kMapFixed = 0x10;
    if (!(flags & kMapAnonymous) || fd != -1 || (flags & kMapFixed)) {
        LOGE("libc", "mmap(%#llx, %llu, flags %#x, fd %d): only anonymous mappings on Windows", (unsigned long long)addr, (unsigned long long)len, flags, fd);
        errno = ENOSYS;
        ret(c, ~0ull);  // MAP_FAILED
        return;
    }
    void* p = hostmem::map_rw(len, true);
    if (!p) errno = ENOMEM;
    ret(c, p ? (u64)p : ~0ull);
}
void th_munmap(Cpu& c) {
    hostmem::unmap((void*)c.x(0), c.x(1));
    ret(c, 0);
}
// mremap(old, old_size, new_size, MREMAP_MAYMOVE): a new mapping, the contents copied (VirtualAlloc
// regions can't grow in place); without MAYMOVE it fails, as Linux may.
void th_mremap(Cpu& c) {
    void* old = (void*)c.x(0);
    u64 old_size = c.x(1), new_size = c.x(2);
    if (!((int)c.x(3) & 1)) {
        errno = ENOMEM;
        return ret(c, ~0ull);
    }
    void* p = hostmem::map_rw(new_size, true);
    if (!p) {
        errno = ENOMEM;
        return ret(c, ~0ull);
    }
    memcpy(p, old, std::min(old_size, new_size));
    hostmem::unmap(old, old_size);
    ret(c, (u64)p);
}

// ---- locale: one "C" locale ----
// Guest locale_t values are opaque; newlocale hands out this non-null cookie.
u8 g_c_locale_cookie;
void th_newlocale(Cpu& c) { ret_ptr(c, &g_c_locale_cookie); }
void th_freelocale(Cpu&) {}
void th_uselocale(Cpu& c) { ret(c, ~0ull); }  // LC_GLOBAL_LOCALE
void th_setlocale(Cpu& c) {
    const char* name = arg_str(c, 1);
    ret_ptr(c, name && strstr(name, "UTF") ? "C.UTF-8" : "C");
}

// ---- 64-bit long ----
void th_atol(Cpu& c) { ret(c, (u64)strtoll(arg_str(c, 0), nullptr, 10)); }
void th_strtol(Cpu& c) {
    long long v = strtoll(arg_str(c, 0), (char**)c.x(1), (int)c.x(2));
    if (errno == ERANGE) errno = guest_errno(ERANGE);
    ret(c, (u64)v);
}
void th_strtoul(Cpu& c) { ret(c, (u64)strtoull(arg_str(c, 0), (char**)c.x(1), (int)c.x(2))); }
void th_strtoll_l(Cpu& c) { ret(c, (u64)strtoll(arg_str(c, 0), (char**)c.x(1), (int)c.x(2))); }
void th_strtoull_l(Cpu& c) { ret(c, (u64)strtoull(arg_str(c, 0), (char**)c.x(1), (int)c.x(2))); }
// long double on AArch64 is IEEE binary128, returned in q0 (as libc.cpp's strtold)
void set_ldouble(Cpu& c, long double v) {
    __float128 q = (__float128)v;
    V128 r;
    std::memcpy(&r, &q, 16);
    c.set_v(0, r);
}
void th_strtold_l(Cpu& c) { set_ldouble(c, strtold(arg_str(c, 0), (char**)c.x(1))); }

// ---- ctype in the C locale ----
#define CTYPE_L(name, expr) \
    void th_##name(Cpu& c) { int ch = (int)c.x(0); ret(c, (u64)(s64)(expr)); }
CTYPE_L(isdigit_l, isdigit(ch))
CTYPE_L(islower_l, islower(ch))
CTYPE_L(isupper_l, isupper(ch))
CTYPE_L(isxdigit_l, isxdigit(ch))
CTYPE_L(tolower_l, tolower(ch))
CTYPE_L(toupper_l, toupper(ch))
// wide ctype: ASCII classes (bionic's C.UTF-8 classifies only ASCII too, outside its tables)
bool wascii(u32 w) { return w < 0x80; }
CTYPE_L(iswalpha_l, wascii(ch) && isalpha(ch))
CTYPE_L(iswblank_l, ch == ' ' || ch == '\t')
CTYPE_L(iswcntrl_l, wascii(ch) && iscntrl(ch))
CTYPE_L(iswdigit_l, ch >= '0' && ch <= '9')
CTYPE_L(iswlower_l, wascii(ch) && islower(ch))
CTYPE_L(iswprint_l, wascii(ch) ? isprint(ch) : ch >= 0xa0)
CTYPE_L(iswpunct_l, wascii(ch) && ispunct(ch))
CTYPE_L(iswspace_l, wascii(ch) && isspace(ch))
CTYPE_L(iswupper_l, wascii(ch) && isupper(ch))
CTYPE_L(iswxdigit_l, wascii(ch) && isxdigit(ch))
CTYPE_L(towlower_l, wascii(ch) ? tolower(ch) : ch)
CTYPE_L(towupper_l, wascii(ch) ? toupper(ch) : ch)
#undef CTYPE_L
void th_strcoll_l(Cpu& c) { ret(c, (u64)(s64)strcmp(arg_str(c, 0), arg_str(c, 1))); }
void th_strxfrm_l(Cpu& c) {
    size_t n = strlen(arg_str(c, 1));
    if (n < c.x(2)) memcpy((void*)c.x(0), arg_str(c, 1), n + 1);
    ret(c, n);
}

// ---- wide characters: the guest's wchar_t is char32_t ----
using gw = char32_t;
size_t gwlen(const gw* s) {
    size_t n = 0;
    while (s[n]) n++;
    return n;
}
int gwcmp_n(const gw* a, const gw* b, size_t n) {
    for (size_t i = 0; i < n; i++)
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    return 0;
}
void th_wcslen(Cpu& c) { ret(c, gwlen((const gw*)c.x(0))); }
void th_wcscpy(Cpu& c) {
    memmove((void*)c.x(0), (const void*)c.x(1), (gwlen((const gw*)c.x(1)) + 1) * 4);
    ret(c, c.x(0));
}
void th_wmemchr(Cpu& c) {
    const gw* s = (const gw*)c.x(0);
    for (size_t i = 0; i < c.x(2); i++)
        if (s[i] == (gw)c.x(1)) return ret_ptr(c, s + i);
    ret(c, 0);
}
void th_wmemcmp(Cpu& c) { ret(c, (u64)(s64)gwcmp_n((const gw*)c.x(0), (const gw*)c.x(1), c.x(2))); }
void th_wmemcpy(Cpu& c) {
    memcpy((void*)c.x(0), (const void*)c.x(1), c.x(2) * 4);
    ret(c, c.x(0));
}
void th_wmemmove(Cpu& c) {
    memmove((void*)c.x(0), (const void*)c.x(1), c.x(2) * 4);
    ret(c, c.x(0));
}
void th_wmemset(Cpu& c) {
    gw* s = (gw*)c.x(0);
    for (size_t i = 0; i < c.x(2); i++) s[i] = (gw)c.x(1);
    ret(c, c.x(0));
}
void th_wcscoll_l(Cpu& c) {
    const gw *a = (const gw*)c.x(0), *b = (const gw*)c.x(1);
    size_t n = std::min(gwlen(a), gwlen(b)) + 1;
    ret(c, (u64)(s64)gwcmp_n(a, b, n));
}
void th_wcsxfrm_l(Cpu& c) {
    size_t n = gwlen((const gw*)c.x(1));
    if (n < c.x(2)) memcpy((void*)c.x(0), (const void*)c.x(1), (n + 1) * 4);
    ret(c, n);
}

// UTF-8 <-> UTF-32 (bionic's multibyte encoding in every locale it supports). mbstate_t is
// bionic's 4 bytes: the bytes of an incomplete sequence (up to 3) and their count in byte 3.
constexpr size_t kIllegal = (size_t)-1, kIncomplete = (size_t)-2;
int utf8_len(u8 b) { return b < 0x80 ? 1 : (b >> 5) == 6 ? 2 : (b >> 4) == 14 ? 3 : (b >> 3) == 30 ? 4 : 0; }
size_t mbrtowc_impl(gw* pwc, const char* s, size_t n, u8* st) {
    if (!s) {  // reset
        if (st) memset(st, 0, 4);
        return 0;
    }
    if (n == 0) return kIncomplete;
    u8 buf[4];
    int have = st ? st[3] : 0;
    memcpy(buf, st, have);
    size_t used = 0;
    int need = have ? utf8_len(buf[0]) : 0;
    while (true) {
        if (!have) {
            buf[0] = (u8)s[used++];
            have = 1;
            need = utf8_len(buf[0]);
            if (!need) return errno = EILSEQ, kIllegal;
        }
        while (have < need && used < n) buf[have++] = (u8)s[used++];
        if (have < need) {
            if (st) memcpy(st, buf, have), st[3] = (u8)have;
            return kIncomplete;
        }
        break;
    }
    u32 w = need == 1 ? buf[0] : need == 2 ? buf[0] & 0x1f : need == 3 ? buf[0] & 0x0f : buf[0] & 0x07;
    for (int i = 1; i < need; i++) {
        if ((buf[i] & 0xc0) != 0x80) return errno = EILSEQ, kIllegal;
        w = w << 6 | (buf[i] & 0x3f);
    }
    if (st) memset(st, 0, 4);
    if (pwc) *pwc = w;
    return w ? used : 0;
}
size_t wcrtomb_impl(char* s, gw w) {
    if (!s) return 1;
    if (w < 0x80) return s[0] = (char)w, 1;
    if (w < 0x800) return s[0] = (char)(0xc0 | w >> 6), s[1] = (char)(0x80 | (w & 0x3f)), 2;
    if (w >= 0xd800 && w < 0xe000) return errno = EILSEQ, kIllegal;
    if (w < 0x10000) return s[0] = (char)(0xe0 | w >> 12), s[1] = (char)(0x80 | (w >> 6 & 0x3f)), s[2] = (char)(0x80 | (w & 0x3f)), 3;
    if (w < 0x110000)
        return s[0] = (char)(0xf0 | w >> 18), s[1] = (char)(0x80 | (w >> 12 & 0x3f)), s[2] = (char)(0x80 | (w >> 6 & 0x3f)), s[3] = (char)(0x80 | (w & 0x3f)), 4;
    return errno = EILSEQ, kIllegal;
}
u8 g_mbstate_internal[4];  // for the functions called with a null mbstate_t
u8* state(u64 p, u8* internal) { return p ? (u8*)p : internal; }

void th_mbrtowc(Cpu& c) {
    static thread_local u8 st[4];
    ret(c, mbrtowc_impl((gw*)c.x(0), (const char*)c.x(1), c.x(2), state(c.x(3), st)));
}
void th_mbrlen(Cpu& c) {
    static thread_local u8 st[4];
    ret(c, mbrtowc_impl(nullptr, (const char*)c.x(0), c.x(1), state(c.x(2), st)));
}
void th_mbtowc(Cpu& c) {
    if (!c.x(1)) return ret(c, 0);  // stateless encoding
    size_t r = mbrtowc_impl((gw*)c.x(0), (const char*)c.x(1), c.x(2), nullptr);
    ret(c, r == kIncomplete ? (u64)-1 : (u64)(s64)(ssize_t)r);
}
void th_wcrtomb(Cpu& c) {
    char tmp[4];
    ret(c, c.x(0) ? wcrtomb_impl((char*)c.x(0), (gw)c.x(1)) : wcrtomb_impl(tmp, 0));
}
void th_btowc(Cpu& c) { ret(c, (int)c.x(0) >= 0 && (int)c.x(0) < 0x80 ? c.x(0) : (u64)(u32)-1); }  // WEOF
void th_wctob(Cpu& c) { ret(c, (u32)c.x(0) < 0x80 ? c.x(0) : (u64)-1); }
// mbsnrtowcs(dst, &src, nms, len, ps) / mbsrtowcs(dst, &src, len, ps)
size_t mbsnrtowcs_impl(gw* dst, const char** src, size_t nms, size_t len, u8* st) {
    const char* s = *src;
    size_t k = 0;
    while (!dst || k < len) {
        gw w;
        size_t r = mbrtowc_impl(&w, s, nms, st);
        if (r == kIllegal) {
            if (dst) *src = s;
            return kIllegal;
        }
        if (r == kIncomplete) {  // the rest of the input is a partial character
            if (dst) *src = s + nms;
            return k;
        }
        if (r == 0) {  // the terminating null
            if (dst) dst[k] = 0, *src = nullptr;
            return k;
        }
        if (dst) dst[k] = w;
        k++;
        s += r;
        nms -= r;
    }
    *src = s;
    return k;
}
void th_mbsnrtowcs(Cpu& c) {
    static thread_local u8 st[4];
    ret(c, mbsnrtowcs_impl((gw*)c.x(0), (const char**)c.x(1), c.x(2), c.x(3), state(c.x(4), st)));
}
void th_mbsrtowcs(Cpu& c) {
    static thread_local u8 st[4];
    ret(c, mbsnrtowcs_impl((gw*)c.x(0), (const char**)c.x(1), (size_t)-1, c.x(2), state(c.x(3), st)));
}
// wcsnrtombs(dst, &src, nwc, len, ps)
void th_wcsnrtombs(Cpu& c) {
    char* dst = (char*)c.x(0);
    const gw** src = (const gw**)c.x(1);
    size_t nwc = c.x(2), len = c.x(3), k = 0;
    const gw* s = *src;
    for (; nwc; nwc--, s++) {
        char tmp[4];
        size_t r = wcrtomb_impl(tmp, *s);
        if (r == kIllegal) {
            if (dst) *src = s;
            return ret(c, kIllegal);
        }
        if (*s == 0) {
            if (dst) {
                if (k >= len) break;
                dst[k] = 0;
                *src = nullptr;
            }
            return ret(c, k);
        }
        if (dst) {
            if (k + r > len) break;
            memcpy(dst + k, tmp, r);
        }
        k += r;
    }
    if (dst) *src = s;
    ret(c, k);
}
// wcsto*: the number's characters are ASCII; convert the prefix and map the end pointer back.
template <typename F>
void wcsto(Cpu& c, F conv) {
    const gw* ws = (const gw*)c.x(0);
    std::string a;
    for (const gw* p = ws; *p && *p < 0x80; p++) a += (char)*p;
    char* end = nullptr;
    conv(a.c_str(), &end);
    if (c.x(1)) *(const gw**)c.x(1) = ws + (end - a.c_str());
}
void th_wcstod(Cpu& c) {
    double d = 0;
    wcsto(c, [&](const char* s, char** e) { d = strtod(s, e); });
    c.set_d(0, d);
}
void th_wcstof(Cpu& c) {
    float f = 0;
    wcsto(c, [&](const char* s, char** e) { f = strtof(s, e); });
    c.set_s(0, f);
}
void th_wcstold(Cpu& c) {
    long double d = 0;
    wcsto(c, [&](const char* s, char** e) { d = strtold(s, e); });
    set_ldouble(c, d);
}
void th_wcstoll(Cpu& c) {
    long long v = 0;
    wcsto(c, [&](const char* s, char** e) { v = strtoll(s, e, (int)c.x(2)); });
    ret(c, (u64)v);
}
void th_wcstoull(Cpu& c) {
    unsigned long long v = 0;
    wcsto(c, [&](const char* s, char** e) { v = strtoull(s, e, (int)c.x(2)); });
    ret(c, (u64)v);
}

// ---- time: bionic's layouts ----
struct BionicTm {
    s32 tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst, pad;
    s64 tm_gmtoff;
    u64 tm_zone;
};
static_assert(sizeof(BionicTm) == 56);
void to_bionic_tm(const tm& t, BionicTm* b, bool utc) {
    b->tm_sec = t.tm_sec, b->tm_min = t.tm_min, b->tm_hour = t.tm_hour, b->tm_mday = t.tm_mday, b->tm_mon = t.tm_mon;
    b->tm_year = t.tm_year, b->tm_wday = t.tm_wday, b->tm_yday = t.tm_yday, b->tm_isdst = t.tm_isdst;
    if (utc) {
        b->tm_gmtoff = 0;
        b->tm_zone = (u64) "UTC";
    } else {
        long tz = _timezone;  // seconds west of UTC (_get_timezone is the UCRT's only, not msvcrt.dll's)
        b->tm_gmtoff = -(s64)tz + (t.tm_isdst > 0 ? 3600 : 0);
        b->tm_zone = (u64)_tzname[t.tm_isdst > 0 ? 1 : 0];
    }
}
tm from_bionic_tm(const BionicTm* b) {
    tm t{};
    memcpy(&t, b, 9 * 4);
    return t;
}
void th_gmtime_r(Cpu& c) {
    tm t;
    __time64_t s = *(const s64*)c.x(0);
    if (_gmtime64_s(&t, &s) != 0) return ret(c, 0);
    to_bionic_tm(t, (BionicTm*)c.x(1), true);
    ret(c, c.x(1));
}
void th_localtime_r(Cpu& c) {
    tm t;
    __time64_t s = *(const s64*)c.x(0);
    if (_localtime64_s(&t, &s) != 0) return ret(c, 0);
    to_bionic_tm(t, (BionicTm*)c.x(1), false);
    ret(c, c.x(1));
}
void th_gmtime(Cpu& c) {
    static thread_local BionicTm b;
    c.set_x(1, (u64)&b);
    th_gmtime_r(c);
}
void th_localtime(Cpu& c) {
    static thread_local BionicTm b;
    c.set_x(1, (u64)&b);
    th_localtime_r(c);
}
void th_mktime(Cpu& c) {
    auto* b = (BionicTm*)c.x(0);
    tm t = from_bionic_tm(b);
    s64 r = _mktime64(&t);
    if (r != -1) to_bionic_tm(t, b, false);
    ret(c, (u64)r);
}
void th_strftime(Cpu& c) {
    tm t = from_bionic_tm((const BionicTm*)c.x(3));
    ret(c, strftime((char*)c.x(0), c.x(1), arg_str(c, 2), &t));
}
void th_time(Cpu& c) {
    s64 t = _time64(nullptr);
    if (c.x(0)) *(s64*)c.x(0) = t;
    ret(c, (u64)t);
}
void th_difftime(Cpu& c) { c.set_d(0, (double)((s64)c.x(0) - (s64)c.x(1))); }

// clock ids (Linux): 0 REALTIME, 1 MONOTONIC, 2 PROCESS_CPUTIME, 3 THREAD_CPUTIME, 4 MONOTONIC_RAW,
// 5 REALTIME_COARSE, 6 MONOTONIC_COARSE, 7 BOOTTIME.
int clock_gettime_guest(int id, s64* ts) {
    clockid_t h = id == 0 || id == 5 ? CLOCK_REALTIME : id == 2 ? CLOCK_PROCESS_CPUTIME_ID : id == 3 ? CLOCK_THREAD_CPUTIME_ID : CLOCK_MONOTONIC;
    timespec t;
    if (clock_gettime(h, &t) != 0) return -1;
    ts[0] = t.tv_sec;
    ts[1] = t.tv_nsec;  // the guest's tv_nsec is 64-bit
    return 0;
}
void th_clock_gettime(Cpu& c) { ret(c, (u64)(s64)clock_gettime_guest((int)c.x(0), (s64*)c.x(1))); }
void th_gettimeofday(Cpu& c) {
    if (u64 tv = c.x(0)) {
        s64 ts[2];
        clock_gettime_guest(0, ts);
        ((s64*)tv)[0] = ts[0];
        ((s64*)tv)[1] = ts[1] / 1000;
    }
    if (u64 tz = c.x(1)) memset((void*)tz, 0, 8);
    ret(c, 0);
}

// ---- sysconf / getrlimit / syscall ----
void th_sysconf(Cpu& c) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    MEMORYSTATUSEX ms{sizeof ms};
    GlobalMemoryStatusEx(&ms);
    int n = (int)c.x(0);
    s64 r;
    switch (n) {
    case 0x0006: r = 100; break;   // _SC_CLK_TCK
    case 0x000b: r = 1024; break;  // _SC_OPEN_MAX
    case 0x0027:
    case 0x0028: r = 4096; break;
    case 0x004c: r = 16384; break;
    case 0x0060:
    case 0x0061: r = device_config().guest_cpus > 0 ? device_config().guest_cpus : (s64)si.dwNumberOfProcessors; break;
    case 0x0062: r = (s64)(ms.ullTotalPhys / 4096); break;
    case 0x0063: r = (s64)(ms.ullAvailPhys / 4096); break;
    default:
        LOGW("libc", "sysconf(%#x) unsupported", n);
        r = -1;
        errno = EINVAL;
        break;
    }
    ret(c, (u64)r);
}
void th_getrlimit(Cpu& c) {
    u64* r = (u64*)c.x(1);
    r[0] = r[1] = (int)c.x(0) == 7 ? 1024 : ~0ull;  // RLIMIT_NOFILE, else RLIM_INFINITY
    ret(c, 0);
}
// futex (FUTEX_WAIT / FUTEX_WAKE, private or not) over WaitOnAddress / WakeByAddress*.
s64 futex(u64 addr, int op, u32 val, u64 timeout) {
    switch (op & 0x7f) {
    case 0:    // FUTEX_WAIT
    case 9: {  // FUTEX_WAIT_BITSET (absolute timeout: treated as relative to now, rarely used)
        DWORD ms = INFINITE;
        if (timeout) {
            const s64* ts = (const s64*)timeout;
            ms = (DWORD)std::min<s64>(ts[0] * 1000 + ts[1] / 1000000, 0x7ffffffe);
        }
        if (*(volatile u32*)addr != val) return errno = EAGAIN, -1;
        if (!WaitOnAddress((volatile void*)addr, &val, 4, ms)) return errno = ETIMEDOUT, errno = guest_errno(errno), -1;
        return 0;
    }
    case 1:     // FUTEX_WAKE
    case 10: {  // FUTEX_WAKE_BITSET
        if ((s32)val == 1) WakeByAddressSingle((void*)addr);
        else WakeByAddressAll((void*)addr);
        return 1;
    }
    default:
        LOGW("libc", "futex op %d unsupported", op);
        return errno = guest_errno(ENOSYS), -1;
    }
}
void th_syscall(Cpu& c) {
    s64 nr = (s64)c.x(0);
    u64 a1 = c.x(1), a2 = c.x(2), a3 = c.x(3), a4 = c.x(4);
    s64 r;
    switch (nr) {
    case 98: r = futex(a1, (int)a2, (u32)a3, a4); break;
    case 172: r = (s64)GetCurrentProcessId(); break;
    case 178: r = gettid(); break;
    case 278: {  // getrandom
        static thread_local std::random_device rd;  // the OS's generator
        u8* p = (u8*)a1;
        for (size_t i = 0; i < a2; i++) p[i] = (u8)rd();
        r = (s64)a2;
        break;
    }
    case 113: r = clock_gettime_guest((int)a1, (s64*)a2); break;
    case 122:
    case 123: r = (s64)a2; break;  // sched_{set,get}affinity: leave the mask as it is
    case 168:                       // getcpu
        if (a1) *(u32*)a1 = GetCurrentProcessorNumber();
        if (a2) *(u32*)a2 = 0;
        r = 0;
        break;
    case 167: r = 0; break;  // prctl
    default:
        LOGW("libc", "syscall(%lld) unsupported", (long long)nr);
        errno = guest_errno(ENOSYS);
        r = -1;
        break;
    }
    ret(c, (u64)r);
}

// ---- file descriptors (CRT descriptors; pipes from core/host_fd.h) ----
int oflags_to_host(int f) {
    int out = f & 3;  // O_RDONLY / O_WRONLY / O_RDWR
    if (f & 0100) out |= _O_CREAT;
    if (f & 0200) out |= _O_EXCL;
    if (f & 01000) out |= _O_TRUNC;
    if (f & 02000) out |= _O_APPEND;
    if (f & 02000000) out |= _O_NOINHERIT;  // O_CLOEXEC
    return out | _O_BINARY;
}
void th_open(Cpu& c) {
    std::string hp = host_path(arg_str(c, 0));
    int mode = (int)c.x(2);
    int crt = _open(hp.c_str(), oflags_to_host((int)c.x(1)), (mode & 0200 ? _S_IWRITE : 0) | _S_IREAD);
    if (crt < 0) set_errno_guest();
    int fd = hostfd::adopt_file(crt);
    LOGD("io", "open(%s -> %s, %#x) = %d", arg_str(c, 0), hp.c_str(), (int)c.x(1), fd);
    ret(c, (u64)(s64)fd);
}
void th_close(Cpu& c) { ret(c, (u64)(s64)hostfd::close((int)c.x(0))); }
void th_read(Cpu& c) { ret(c, (u64)(s64)hostfd::read((int)c.x(0), (void*)c.x(1), c.x(2))); }
void th_write(Cpu& c) {
    int fd = (int)c.x(0);
    if (fd == 1 || fd == 2) {  // the guest's stdout / stderr: the host's, unbuffered
        fwrite((const void*)c.x(1), 1, c.x(2), fd == 1 ? stdout : stderr);
        return ret(c, c.x(2));
    }
    ret(c, (u64)(s64)hostfd::write(fd, (const void*)c.x(1), c.x(2)));
}
// (a guest descriptor that isn't a file: the CRT calls fail with EBADF on -1)
void th_lseek64(Cpu& c) { ret(c, (u64)(s64)_lseeki64(hostfd::crt_of((int)c.x(0)), (s64)c.x(1), (int)c.x(2))); }
void th_fsync(Cpu& c) { ret(c, (u64)(s64)_commit(hostfd::crt_of((int)c.x(0)))); }
void th_ftruncate(Cpu& c) { ret(c, (u64)(s64)(_chsize_s(hostfd::crt_of((int)c.x(0)), (s64)c.x(1)) == 0 ? 0 : -1)); }
void th_pipe(Cpu& c) {
    int fds[2];
    int r = hostfd::make_pipe(fds);
    if (r == 0) ((s32*)c.x(0))[0] = fds[0], ((s32*)c.x(0))[1] = fds[1];
    ret(c, (u64)(s64)r);
}
void th_fstat(Cpu& c) {
    int fd = (int)c.x(0);
    struct stat s{};
    if (hostfd::emulated(fd) || hostfd::socket_of(fd) != ~(uintptr_t)0) {
        s.st_mode = hostfd::emulated(fd) ? _S_IFIFO | 0600 : 0140600;  // a pipe / a socket (S_IFSOCK)
    } else if (fstat(hostfd::crt_of(fd), &s) != 0) {
        set_errno_guest();
        return ret(c, (u64)-1);
    }
    to_bionic_stat(s, c.x(1));
    ret(c, 0);
}
// fcntl: F_GETFD/F_SETFD (1/2), F_GETFL/F_SETFL (3/4): accepted, nothing to change.
void th_fcntl(Cpu& c) {
    int cmd = (int)c.x(1);
    ret(c, cmd == 3 ? 2 /* O_RDWR */ : 0);
}
void th_readlink(Cpu& c) {
    errno = EINVAL;  // no symlinks
    ret(c, (u64)-1);
}

}  // namespace

void register_libc_win32(Hle& h) {
    h.fn("mmap", th_mmap);
    h.fn("munmap", th_munmap);
    h.fn("mremap", th_mremap);

    h.fn("newlocale", th_newlocale);
    h.fn("freelocale", th_freelocale);
    h.fn("uselocale", th_uselocale);
    h.fn("setlocale", th_setlocale);
    h.fn("atol", th_atol);
    h.fn("strtol", th_strtol);
    h.fn("strtoul", th_strtoul);
    h.fn("strtoll_l", th_strtoll_l);
    h.fn("strtoull_l", th_strtoull_l);
    h.fn("strtold_l", th_strtold_l);
    h.fn("isdigit_l", th_isdigit_l);
    h.fn("islower_l", th_islower_l);
    h.fn("isupper_l", th_isupper_l);
    h.fn("isxdigit_l", th_isxdigit_l);
    h.fn("tolower_l", th_tolower_l);
    h.fn("toupper_l", th_toupper_l);
    h.fn("iswalpha_l", th_iswalpha_l);
    h.fn("iswblank_l", th_iswblank_l);
    h.fn("iswcntrl_l", th_iswcntrl_l);
    h.fn("iswdigit_l", th_iswdigit_l);
    h.fn("iswlower_l", th_iswlower_l);
    h.fn("iswprint_l", th_iswprint_l);
    h.fn("iswpunct_l", th_iswpunct_l);
    h.fn("iswspace_l", th_iswspace_l);
    h.fn("iswupper_l", th_iswupper_l);
    h.fn("iswxdigit_l", th_iswxdigit_l);
    h.fn("towlower_l", th_towlower_l);
    h.fn("towupper_l", th_towupper_l);
    h.fn("strcoll_l", th_strcoll_l);
    h.fn("strxfrm_l", th_strxfrm_l);
    h.fn("wcscoll_l", th_wcscoll_l);
    h.fn("wcsxfrm_l", th_wcsxfrm_l);

    h.fn("wcslen", th_wcslen);
    h.fn("wcscpy", th_wcscpy);
    h.fn("wmemchr", th_wmemchr);
    h.fn("wmemcmp", th_wmemcmp);
    h.fn("wmemcpy", th_wmemcpy);
    h.fn("wmemmove", th_wmemmove);
    h.fn("wmemset", th_wmemset);
    h.fn("btowc", th_btowc);
    h.fn("wctob", th_wctob);
    h.fn("mbrlen", th_mbrlen);
    h.fn("mbrtowc", th_mbrtowc);
    h.fn("mbsnrtowcs", th_mbsnrtowcs);
    h.fn("mbsrtowcs", th_mbsrtowcs);
    h.fn("mbtowc", th_mbtowc);
    h.fn("wcrtomb", th_wcrtomb);
    h.fn("wcsnrtombs", th_wcsnrtombs);
    h.fn("wcstod", th_wcstod);
    h.fn("wcstof", th_wcstof);
    h.fn("wcstold", th_wcstold);
    h.fn("wcstol", th_wcstoll);
    h.fn("wcstoll", th_wcstoll);
    h.fn("wcstoul", th_wcstoull);
    h.fn("wcstoull", th_wcstoull);

    h.fn("getpid", [](Cpu& c) { ret(c, (u64)GetCurrentProcessId()); });
    h.fn("gettid", [](Cpu& c) { ret(c, (u64)(s64)gettid()); });
    h.fn("geteuid", [](Cpu& c) { ret(c, 10123); });  // an Android app uid

    h.fn("clock_gettime", th_clock_gettime);
    h.fn("gettimeofday", th_gettimeofday);
    h.fn("time", th_time);
    h.fn("difftime", th_difftime);
    h.fn("gmtime", th_gmtime);
    h.fn("localtime", th_localtime);
    h.fn("localtime_r", th_localtime_r);
    h.fn("gmtime_r", th_gmtime_r);
    h.fn("mktime", th_mktime);
    h.fn("strftime", th_strftime);
    h.fn("strftime_l", [](Cpu& c) { th_strftime(c); });
    h.fn("sysconf", th_sysconf);
    h.fn("syscall", th_syscall);
    h.fn("getrlimit", th_getrlimit);

    h.fn("open", th_open);
    h.fn("fcntl", th_fcntl);
    h.fn("close", th_close);
    h.fn("read", th_read);
    h.fn("write", th_write);
    h.fn("lseek64", th_lseek64);
    h.fn("fsync", th_fsync);
    h.fn("ftruncate", th_ftruncate);
    h.fn("fchmod", [](Cpu& c) { ret(c, 0); });
    h.fn("fchown", [](Cpu& c) { ret(c, 0); });
    h.fn("pipe", th_pipe);
    h.fn("fstat", th_fstat);
    h.fn("utimes", [](Cpu& c) { ret(c, 0); });
    h.fn("readlink", th_readlink);

    register_net_win32(h);  // after fcntl: it wraps it for sockets
}

}  // namespace soa
#endif
