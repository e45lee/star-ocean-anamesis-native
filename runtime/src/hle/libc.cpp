// Bionic libc: strings, memory, conversions, ctype/locale, process basics.
#include <ctype.h>
#include <errno.h>
#include <locale.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <sys/mman.h>
#endif
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>

#include <mutex>

#include "core/hle.h"
#include "core/log.h"
#include "hle/format.h"

namespace soa {
namespace {

#ifndef _WIN32  // Windows: hle/libc_win32.cpp (no glibc locale_t; wchar_t is 16-bit there)
// ---- locale ----
// Guest locale_t values are host glibc locale_t objects. LC_GLOBAL_LOCALE is -1 on both.
locale_t c_locale() {
    static locale_t l = newlocale(LC_ALL_MASK, "C", (locale_t)0);
    return l;
}
locale_t fixloc(u64 l) {
    if (l == 0 || l == ~0ull) return c_locale();
    return (locale_t)l;
}
int bionic_mask_to_host(int m) {
    // Bionic: LC_CTYPE..LC_MESSAGES = 0..5, LC_ALL = 6; masks are (1 << cat). LC_ALL_MASK = 0x3f + extras.
    int out = 0;
    static const int map[] = {LC_CTYPE_MASK, LC_NUMERIC_MASK, LC_TIME_MASK, LC_COLLATE_MASK, LC_MONETARY_MASK, LC_MESSAGES_MASK};
    for (int i = 0; i < 6; i++)
        if (m & (1 << i)) out |= map[i];
    if ((m & 0x3f) == 0x3f) out = LC_ALL_MASK;
    return out;
}
void th_newlocale(Cpu& c) {
    int mask = bionic_mask_to_host((int)c.x(0));
    const char* name = arg_str(c, 1);
    u64 base = c.x(2);
    // Bionic only supports "C"/"POSIX"/"C.UTF-8" (and "" = default).
    locale_t b = (base == 0 || base == ~0ull) ? (locale_t)0 : (locale_t)base;
    const char* hn = (name && (!strcmp(name, "") || strstr(name, "UTF-8") || strstr(name, "utf8"))) ? "C.UTF-8" : "C";
    locale_t l = newlocale(mask ? mask : LC_ALL_MASK, hn, b);
    if (!l) l = newlocale(mask ? mask : LC_ALL_MASK, "C", b);
    ret_ptr(c, l);
}
void th_freelocale(Cpu& c) {
    u64 l = c.x(0);
    if (l && l != ~0ull && (locale_t)l != c_locale()) freelocale((locale_t)l);
}
void th_uselocale(Cpu& c) {
    u64 l = c.x(0);
    locale_t prev = uselocale(l ? (locale_t)l : (locale_t)0);
    ret_ptr(c, prev);
}
void th_setlocale(Cpu& c) {
    int cat = (int)c.x(0);
    const char* name = arg_str(c, 1);
    // Bionic categories 0..6 match glibc's LC_CTYPE..LC_ALL.
    if (name && *name && !strstr(name, "UTF") && strcmp(name, "C") && strcmp(name, "POSIX")) name = "C";
    const char* r = setlocale(cat, name ? (strcmp(name, "") ? name : "C.UTF-8") : nullptr);
    static thread_local char buf[64];
    if (!r) r = "C";
    snprintf(buf, sizeof buf, "%s", r);
    ret_ptr(c, buf);
}

#define CTYPE_L(fn) \
    void th_##fn(Cpu& c) { ret(c, (u64)fn((int)c.x(0), fixloc(c.x(1)))); }
CTYPE_L(isdigit_l)
CTYPE_L(islower_l)
CTYPE_L(isupper_l)
CTYPE_L(isxdigit_l)
CTYPE_L(tolower_l)
CTYPE_L(toupper_l)
#define WCTYPE_L(fn) \
    void th_##fn(Cpu& c) { ret(c, (u64)fn((wint_t)c.x(0), fixloc(c.x(1)))); }
WCTYPE_L(iswalpha_l)
WCTYPE_L(iswblank_l)
WCTYPE_L(iswcntrl_l)
WCTYPE_L(iswdigit_l)
WCTYPE_L(iswlower_l)
WCTYPE_L(iswprint_l)
WCTYPE_L(iswpunct_l)
WCTYPE_L(iswspace_l)
WCTYPE_L(iswupper_l)
WCTYPE_L(iswxdigit_l)
WCTYPE_L(towlower_l)
WCTYPE_L(towupper_l)

void th_strcoll_l(Cpu& c) { ret(c, (u64)(s64)strcoll_l(arg_str(c, 0), arg_str(c, 1), fixloc(c.x(2)))); }
void th_strxfrm_l(Cpu& c) { ret(c, strxfrm_l((char*)c.x(0), arg_str(c, 1), c.x(2), fixloc(c.x(3)))); }
void th_wcscoll_l(Cpu& c) { ret(c, (u64)(s64)wcscoll_l((const wchar_t*)c.x(0), (const wchar_t*)c.x(1), fixloc(c.x(2)))); }
void th_wcsxfrm_l(Cpu& c) { ret(c, wcsxfrm_l((wchar_t*)c.x(0), (const wchar_t*)c.x(1), c.x(2), fixloc(c.x(3)))); }
void th_strtoll_l(Cpu& c) { ret(c, (u64)strtoll_l(arg_str(c, 0), (char**)c.x(1), (int)c.x(2), fixloc(c.x(3)))); }
void th_strtoull_l(Cpu& c) { ret(c, (u64)strtoull_l(arg_str(c, 0), (char**)c.x(1), (int)c.x(2), fixloc(c.x(3)))); }
#endif

// long double on AArch64 is IEEE binary128, returned in q0.
void set_ldouble(Cpu& c, long double v) {
    __float128 q = (__float128)v;
    V128 r;
    std::memcpy(&r, &q, 16);
    c.set_v(0, r);
}
void th_strtold(Cpu& c) { set_ldouble(c, strtold(arg_str(c, 0), (char**)c.x(1))); }
#ifndef _WIN32
void th_strtold_l(Cpu& c) { set_ldouble(c, strtold_l(arg_str(c, 0), (char**)c.x(1), fixloc(c.x(2)))); }
void th_wcstold(Cpu& c) { set_ldouble(c, wcstold((const wchar_t*)c.x(0), (wchar_t**)c.x(1))); }
#endif

void th_ctype_get_mb_cur_max(Cpu& c) { ret(c, MB_CUR_MAX); }

void th_localeconv(Cpu& c) { ret_ptr(c, localeconv()); }

// ---- errno / process ----
void th_errno(Cpu& c) { ret_ptr(c, &errno); }

void th_stack_chk_fail(Cpu& c) {
    LOGE("libc", "stack corruption detected");
    dump_guest_state(c);
    fatal("__stack_chk_fail");
}
void th_abort(Cpu& c) {
    LOGE("libc", "guest called abort()");
    dump_guest_state(c);
    fatal("abort");
}
void th_exit(Cpu& c) {
    LOGI("libc", "guest called exit(%d)", (int)c.x(0));
    fflush(stdout);
    _exit((int)c.x(0));
}
void th_android_set_abort_message(Cpu& c) { LOGE("libc", "abort message: %s", arg_str(c, 0)); }

std::mutex g_atexit_mutex;
void th_cxa_atexit(Cpu& c) { ret(c, 0); }  // never run at exit; the process just ends
void th_cxa_finalize(Cpu& c) {}

void th_raise(Cpu& c) {
    LOGE("libc", "guest raise(%d)", (int)c.x(0));
    dump_guest_state(c);
    fatal("raise");
}

void th_div(Cpu& c) {
    div_t r = div((int)c.x(0), (int)c.x(1));
    ret(c, (u64)(u32)r.quot | ((u64)(u32)r.rem << 32));
}

void th_getenv(Cpu& c) {
    const char* n = arg_str(c, 0);
    // Don't leak the host environment into the guest except for a few harmless variables.
    const char* v = nullptr;
    if (!strcmp(n, "TZ") || !strcmp(n, "HOME") || !strcmp(n, "TMPDIR")) v = getenv(n);
    ret_ptr(c, v);
}

// ---- qsort with guest comparator ----
thread_local u64 t_qsort_cmp;
int qsort_tramp(const void* a, const void* b) { return (int)guest_call(t_qsort_cmp, {(u64)a, (u64)b}); }
void th_qsort(Cpu& c) {
    u64 saved = t_qsort_cmp;
    t_qsort_cmp = c.x(3);
    qsort((void*)c.x(0), c.x(1), c.x(2), qsort_tramp);
    t_qsort_cmp = saved;
}

void th_rand(Cpu& c) { ret(c, (u64)(u32)guest_rand()); }  // bionic RAND_MAX 0x7fffffff on both hosts

}  // namespace

void register_libc(Hle& h) {
    // memory
    HLE_WRAP(h, malloc);
    HLE_WRAP(h, free);
    HLE_WRAP(h, calloc);
    HLE_WRAP(h, realloc);
#ifndef _WIN32
    HLE_WRAP(h, mmap);
    HLE_WRAP(h, munmap);
    h.fn("mremap", [](Cpu& c) { ret_ptr(c, mremap((void*)c.x(0), c.x(1), c.x(2), (int)c.x(3), (void*)c.x(4))); });
#endif

    // strings (identical ABI)
    HLE_WRAP_T(h, "memchr", const void* (*)(const void*, int, size_t), memchr);
    HLE_WRAP(h, memcmp);
    HLE_WRAP(h, memcpy);
    HLE_WRAP(h, memmove);
    HLE_WRAP(h, memset);
    HLE_WRAP(h, strcat);
    HLE_WRAP_T(h, "strchr", const char* (*)(const char*, int), strchr);
    HLE_WRAP(h, strcmp);
    HLE_WRAP(h, strcpy);
    HLE_WRAP(h, strlen);
    HLE_WRAP(h, strncmp);
    HLE_WRAP(h, strncpy);
    HLE_WRAP_T(h, "strrchr", const char* (*)(const char*, int), strrchr);
    HLE_WRAP_T(h, "strstr", const char* (*)(const char*, const char*), strstr);
    HLE_WRAP(h, strcasecmp);
    HLE_WRAP(h, strtok);
    HLE_WRAP(h, strerror);
#ifndef _WIN32  // the wide-character functions (guest wchar_t is 32-bit) and the long conversions (guest long is 64-bit): libc_win32.cpp
    HLE_WRAP(h, wcscpy);
    HLE_WRAP(h, wcslen);
    HLE_WRAP_T(h, "wmemchr", const wchar_t* (*)(const wchar_t*, wchar_t, size_t), wmemchr);
    HLE_WRAP(h, wmemcmp);
    HLE_WRAP(h, wmemcpy);
    HLE_WRAP(h, wmemmove);
    HLE_WRAP(h, wmemset);
    HLE_WRAP(h, btowc);
    HLE_WRAP(h, wctob);
    HLE_WRAP(h, mbrlen);
    HLE_WRAP(h, mbrtowc);
    HLE_WRAP(h, mbsnrtowcs);
    HLE_WRAP(h, mbsrtowcs);
    HLE_WRAP(h, mbtowc);
    HLE_WRAP(h, wcrtomb);
    HLE_WRAP(h, wcsnrtombs);
#endif

    // conversions
    HLE_WRAP(h, atof);
    HLE_WRAP(h, atoi);
#ifndef _WIN32
    HLE_WRAP(h, atol);
#endif
    HLE_WRAP(h, strtod);
    HLE_WRAP(h, strtof);
#ifndef _WIN32
    HLE_WRAP(h, strtol);
#endif
    HLE_WRAP(h, strtoll);
#ifndef _WIN32
    HLE_WRAP(h, strtoul);
#endif
    HLE_WRAP(h, strtoull);
#ifndef _WIN32
    HLE_WRAP(h, wcstod);
    HLE_WRAP(h, wcstof);
    HLE_WRAP(h, wcstol);
    HLE_WRAP(h, wcstoll);
    HLE_WRAP(h, wcstoul);
    HLE_WRAP(h, wcstoull);
#endif
    h.fn("strtold", th_strtold);
#ifndef _WIN32
    h.fn("strtold_l", th_strtold_l);
    h.fn("wcstold", th_wcstold);
    h.fn("strtoll_l", th_strtoll_l);
    h.fn("strtoull_l", th_strtoull_l);
#endif

    // ctype / locale
    HLE_WRAP(h, isupper);
    HLE_WRAP(h, isxdigit);
    HLE_WRAP(h, tolower);
    HLE_WRAP(h, toupper);
#ifndef _WIN32
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
    h.fn("newlocale", th_newlocale);
    h.fn("freelocale", th_freelocale);
    h.fn("uselocale", th_uselocale);
    h.fn("setlocale", th_setlocale);
#endif
    h.fn("localeconv", th_localeconv);
    h.fn("__ctype_get_mb_cur_max", th_ctype_get_mb_cur_max);

    // process
    h.fn("__errno", th_errno);
    h.fn("__stack_chk_fail", th_stack_chk_fail);
    static u64 stack_chk_guard = 0x5f3759df1badf00dull;
    h.data("__stack_chk_guard", &stack_chk_guard);
    h.fn("abort", th_abort);
    h.fn("exit", th_exit);
    h.fn("android_set_abort_message", th_android_set_abort_message);
    h.fn("__cxa_atexit", th_cxa_atexit);
    h.fn("__cxa_finalize", th_cxa_finalize);
    h.fn("raise", th_raise);
    h.fn("div", th_div);
    h.fn("getenv", th_getenv);
    h.fn("qsort", th_qsort);
    h.fn("rand", th_rand);
#ifndef _WIN32
    HLE_WRAP(h, getpid);
    HLE_WRAP(h, gettid);
    HLE_WRAP(h, geteuid);
#endif
}

}  // namespace soa
