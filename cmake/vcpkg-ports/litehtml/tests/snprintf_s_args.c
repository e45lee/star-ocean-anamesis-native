/*
 * BUG REPORT (for microsoft/vcpkg, port `litehtml`)
 * ==================================================
 *
 * Title: [litehtml] v0.10 overflows every snprintf buffer by one byte on Windows; please backport
 *        upstream fix d4cbcba
 *
 * Summary
 *   litehtml v0.10 (the version vcpkg's port builds) defines, in include/litehtml/os_types.h:
 *
 *       #define t_snprintf(s, n, format, ...) _snprintf_s(s, _TRUNCATE, n, format, __VA_ARGS__)
 *
 *   _snprintf_s takes (buffer, sizeOfBuffer, count, format, ...). The macro passes _TRUNCATE as
 *   sizeOfBuffer and the real buffer size as count. With that order the C runtime writes a NUL one
 *   byte past the end of the buffer on every call, even when the formatted text is short.
 *   litehtml formats numbers and strings into fixed-size buffers throughout, so this corrupts
 *   memory next to those buffers.
 *
 *   litehtml fixed this upstream on 2026-07-13, after v0.10 (released 2026-06-13):
 *     commit d4cbcba78e40 "fix snprintf buffer overflow on windows"
 *     (master now has: _snprintf_s(s, n, _TRUNCATE, format, __VA_ARGS__))
 *   There is no litehtml release with the fix yet, and vcpkg's port (version 0.10, patches
 *   use-vcpkg-gumbo.patch and fix-relative-includes.patch) does not carry it.
 *
 * Impact seen
 *   Built with MinGW-w64 for x64-mingw-static and run on Windows, the first document litehtml
 *   parsed threw std::bad_alloc. Replacing the Windows t_snprintf/t_itoa with the non-Windows
 *   definitions (snprintf) made pages render. That the overflow causes the bad_alloc (by
 *   clobbering a neighbouring heap object) is inferred, not traced.
 *
 * Reproduction (this file)
 *   It calls _snprintf_s into a 16-byte buffer with 64 guard bytes on each side, in litehtml's
 *   argument order and in the documented one, and reports changed guard bytes.
 *     x86_64-w64-mingw32-gcc-posix -O0 -o t0.exe snprintf_s_args.c && ./t0.exe
 *     x86_64-w64-mingw32-gcc-posix -O3 -o t3.exe snprintf_s_args.c && ./t3.exe
 *
 *   Output (identical at -O0 and -O3):
 *     litehtml order, short string   ret=  3  buf="abc"               guard bytes changed: before=0 after=1 (first at buf+16, value 0x00)
 *     litehtml order, long string    ret= -1  buf="0123456789abcdef"  guard bytes changed: before=0 after=1 (first at buf+16, value 0x00)
 *     correct order, short string    ret=  3  buf="abc"               guard bytes changed: before=0 after=0
 *     correct order, long string     ret= -1  buf="0123456789abcde"   guard bytes changed: before=0 after=0
 *     snprintf, long string          ret= 26  buf="0123456789abcde"   guard bytes changed: before=0 after=0
 *
 *   Expected: no byte outside the buffer changes (as with the documented order and snprintf).
 *   Actual: with litehtml's order a NUL is written at buf[16], one past the end; for the long
 *   string the buffer is also left without a terminator inside it.
 *
 * Environment
 *   litehtml v0.10 (vcpkg port litehtml 0.10, builtin-baseline fdd4e6059c803f56bb5df86e285bf374d9d44407)
 *   Toolchain: MinGW-w64 11.0.1 (Ubuntu mingw-w64 11.0.1-3build1), x86_64-w64-mingw32-gcc-posix 13,
 *   default CRT (msvcrt), triplet x64-mingw-static, cross-compiled on Ubuntu 24.04 (WSL2)
 *   Run on: Microsoft Windows [Version 10.0.26200.9550]
 *   Not tested: MSVC builds, the UCRT. The argument order is wrong regardless of compiler.
 *
 * Suggested fix
 *   Backport upstream commit d4cbcba as a port patch (the one-line argument swap in
 *   include/litehtml/os_types.h), or update the port once litehtml tags a release containing it.
 *   (t_itoa's _itoa_s(value, buffer, size, radix) has the documented argument order.)
 */

// Minimal test for litehtml's Windows t_snprintf (include/litehtml/os_types.h before
// mingw-snprintf.patch):
//   #define t_snprintf(s, n, format, ...) _snprintf_s(s, _TRUNCATE, n, format, __VA_ARGS__)
// _snprintf_s is (buffer, sizeOfBuffer, count, format, ...): _TRUNCATE ((size_t)-1) belongs in
// `count`, but litehtml passes it as `sizeOfBuffer`, so the runtime is told the buffer is
// unbounded. This writes into a buffer with guard bytes on both sides, with litehtml's argument
// order and with the correct one, and reports whether anything outside the buffer changed.
//
// Build and run (from the repo root, on WSL; the .exe runs on the Windows host):
//   x86_64-w64-mingw32-gcc-posix -O0 -o /tmp/t0.exe cmake/vcpkg-ports/litehtml/tests/snprintf_s_args.c && /tmp/t0.exe
//   x86_64-w64-mingw32-gcc-posix -O3 -o /tmp/t3.exe cmake/vcpkg-ports/litehtml/tests/snprintf_s_args.c && /tmp/t3.exe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GUARD 64
#define SIZE 16
#define FILL 0xA5

struct area {
    unsigned char before[GUARD];
    char buf[SIZE];
    unsigned char after[GUARD];
};

static void reset(struct area* a) { memset(a, FILL, sizeof *a); }

// Bytes changed outside buf (before / after), and the first changed offset after it.
static int check(const char* what, const struct area* a, int ret) {
    int before = 0, after = 0, first_after = -1;
    for (int i = 0; i < GUARD; i++) before += a->before[i] != FILL;
    for (int i = 0; i < GUARD; i++)
        if (a->after[i] != FILL) {
            after++;
            if (first_after < 0) first_after = i;
        }
    printf("%-46s ret=%3d  buf=\"%.*s\"  guard bytes changed: before=%d after=%d", what, ret, SIZE, a->buf, before, after);
    if (after) printf(" (first at buf+%d, value 0x%02x)", SIZE + first_after, a->after[first_after]);
    printf("\n");
    return before + after;
}

int main(void) {
    struct area* a = malloc(sizeof *a);
    int bad = 0, ret;
    const char* shortstr = "abc";                         // fits
    const char* longstr = "0123456789abcdefghijklmnop";   // longer than the buffer

    // litehtml's order: _snprintf_s(s, _TRUNCATE, n, format, ...)
    reset(a);
    ret = _snprintf_s(a->buf, _TRUNCATE, SIZE, "%s", shortstr);
    bad += check("litehtml order, short string", a, ret);
    reset(a);
    ret = _snprintf_s(a->buf, _TRUNCATE, SIZE, "%s", longstr);
    bad += check("litehtml order, long string", a, ret);

    // The documented order: _snprintf_s(s, n, _TRUNCATE, format, ...)
    reset(a);
    ret = _snprintf_s(a->buf, SIZE, _TRUNCATE, "%s", shortstr);
    check("correct order, short string", a, ret);
    reset(a);
    ret = _snprintf_s(a->buf, SIZE, _TRUNCATE, "%s", longstr);
    check("correct order, long string", a, ret);

    // What the patch uses instead.
    reset(a);
    ret = snprintf(a->buf, SIZE, "%s", longstr);
    check("snprintf (the patch), long string", a, ret);

    printf("%s\n", bad ? "RESULT: litehtml's argument order writes outside the buffer"
                       : "RESULT: no write outside the buffer with litehtml's order (this runtime)");
    free(a);
    return bad ? 1 : 0;
}
