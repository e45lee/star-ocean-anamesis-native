// CTimeUtility::str2time_t (info_layout.h; port/decomp/info/time.c): a date string to a time_t. The
// conversion is the runtime's mktime, called through the lib's mktime@plt, so platform370's local-time
// rule (docs/client-changes.md "Local time: daylight saving", soa::mktime_local; --no-dst-fix) applies as
// it does to the guest's call. Live check (family `info`): the original after the native on the same
// arguments (it only reads them), the results compared.
#include <cstring>

#include "native/common/arm_float.h"
#include "native/common/native.h"
#include "native/info/gen/info_addresses.h"
#include "native/info/info_family.h"
#include "native/info/info_guest.h"
#include "native/info/info_layout.h"
#include "native/params/params_layout.h"

namespace soa::native::info {

namespace {

// CSTLStringUtility_Base<S>::AToF(S const&) on a std::string temporary of `field` (a long one in storage
// of its own from the STL allocator, freed after), as each field's conversion builds it.
float atof_field(const char* field) {
    static const u64 f = g::sym("_ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_"
                                "13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE4AToFERKS8_");
    params::String s;
    std::memset(&s, 0, sizeof s);
    u64 n = std::strlen(field);
    char* storage = nullptr;
    if (n < 23) {
        s.r.s.head.size = static_cast<u8>(n << 1);
        std::memcpy(&s.r.s.data[0], field, n);
    } else {
        u64 cap = (n + 16) & ~u64(15);
        storage = static_cast<char*>(g::StringAllocate(cap));
        std::memcpy(storage, field, n);
        storage[n] = 0;
        s.r.l.cap = cap | 1;
        s.r.l.size = n;
        s.r.l.data = storage;
    }
    GuestResult r = guest_call(f, GuestArgs().p(&s));
    if (storage) g::StlFree(storage);
    float v;
    std::memcpy(&v, &r.v0.lo, 4);
    return v;
}

// The fields the guest would read uninitialised (a time asked for, fewer than six fields): left to it.
constexpr s64 kGuest = INT64_MIN;

s64 convert(const char* text, s64 fallback, bool date_only, bool slashes) {
    if (!text) return fallback;
    bool dash = std::strchr(text, '-'), slash = std::strchr(text, '/');
    const char* sep = (!(!dash && slashes) && !slash) ? "-- ::" : "// ::";
    if (std::strlen(text) >= 64) return kGuest;  // (the guest's 64-byte copy overflows its frame)
    char buf[64];
    std::strcpy(buf, text);
    char* field[6] = {};
    char* p = std::strchr(buf, sep[0]);
    if (!p) return fallback;
    *p = 0;
    field[0] = buf;
    char* q = std::strchr(p + 1, sep[1]);
    if (!q) return fallback;
    *q = 0;
    field[1] = p + 1;
    char* rest = q + 1;
    int n = 2;
    if (char* a = std::strchr(rest, sep[2])) {
        *a = 0;
        field[2] = rest;
        rest = a + 1;
        n = 3;
        if (char* b = std::strchr(rest, sep[3])) {
            *b = 0;
            field[3] = rest;
            rest = b + 1;
            n = 4;
            if (char* c = std::strchr(rest, sep[4])) {
                *c = 0;
                field[4] = rest;
                rest = c + 1;  // (the sixth separator is the terminator: nothing to cut)
                n = 5;
            }
        }
    }
    field[n] = rest;
    GuestTm tm{};
    if (!date_only) {
        if (n < 5) return kGuest;
        tm.tm_sec = armf::cvtzs(atof_field(field[5]));
        tm.tm_min = armf::cvtzs(atof_field(field[4]));
        tm.tm_hour = armf::cvtzs(atof_field(field[3]));
    }
    tm.tm_mday = armf::cvtzs(atof_field(field[2]));
    tm.tm_mon = armf::cvtzs(atof_field(field[1])) - 1;
    tm.tm_year = armf::cvtzs(atof_field(field[0])) - 1900;
    // (tm_wday, tm_gmtoff and tm_zone are whatever the guest's frame held: mktime reads none of them)
    return static_cast<s64>(g::call(g::at(g::kPltMktime), {reinterpret_cast<u64>(&tm)}));
}

Fn f_str2time(fam(), "_ZN12CTimeUtility10str2time_tEPKclbb");

void h_str2time(Cpu& c) {
    const char* text = reinterpret_cast<const char*>(c.x(0));
    s64 fallback = static_cast<s64>(c.x(1));
    bool date_only = c.x(2) & 1, slashes = c.x(3) & 1;
    s64 r = convert(text, fallback, date_only, slashes);
    if (r == kGuest) {
        c.set_x(0, guest_call(f_str2time.orig, {c.x(0), c.x(1), c.x(2), c.x(3)}));
        return;
    }
    if (fam().due(f_str2time)) {
        live::RunBothFamily::Scope scope;
        s64 g = static_cast<s64>(guest_call(f_str2time.orig, {c.x(0), c.x(1), c.x(2), c.x(3)}));
        fam().result(f_str2time, g == r ? Outcome::Ok : Outcome::Mismatch,
                     g == r ? "" : std::string("\"") + (text ? text : "(null)") + "\": native " + std::to_string(r) + ", guest " +
                                       std::to_string(g));
    }
    c.set_x(0, static_cast<u64>(r));
}

}  // namespace

s64 CTimeUtility::str2time_t(const char* text, s64 fallback, bool date_only, bool slashes) {
    s64 r = convert(text, fallback, date_only, slashes);
    if (r != kGuest) return r;
    return static_cast<s64>(guest_call(f_str2time.orig ? f_str2time.orig : g::sym("_ZN12CTimeUtility10str2time_tEPKclbb"),
                                       {reinterpret_cast<u64>(text), static_cast<u64>(fallback), date_only, slashes}));
}

NATIVE_FUNCTION_ORIG("_ZN12CTimeUtility10str2time_tEPKclbb", h_str2time, "info: CTimeUtility::str2time_t", &f_str2time.orig);

}  // namespace soa::native::info

// ---- differential test ----

#include "native/common/test.h"

namespace soa::native::info {

// Date strings of every shape str2time_t reads (dashes, slashes, a date only, a time, fields of every
// length, a long field (a long std::string), junk, a missing separator): the guest's and the native's
// result for each, both ways of `date_only` and `slashes` where the guest reads no uninitialised field.
NATIVE_TEST("info/str2time") {
    static const char* const kTexts[] = {
        "2021-06-24 14:30:00", "2021/06/24 14:30:00", "2026-10-25 02:30:00", "2026-03-29 02:30:00", "2026-10-25 01:59:59",
        "1999-12-31 23:59:59", "2038-01-19 03:14:07", "2021-6-4 4:3:2", "2021-06-24", "2021/06/24", "20210624", "2021-06",
        "2021-06-24 14:30", "2021-06-24 14", "abcd-ef-gh ij:kl:mn", "2021-06-24 14:30:00 extra", "0x10-0x2-0x3 0:0:0",
        "2021-06-240000000000000000000000000 14:30:00", "", "-", "--", "2021--24 14:30:00", "2021-06-24T14:30:00",
        "1e3-1.5-2.9 1.9:2.9:3.9", "  2021-06-24 14:30:00", "2021-06-24  14:30:00"};
    static const char kGuestFn[] = "_ZN12CTimeUtility10str2time_tEPKclbb";
    int bad = 0;
    for (const char* s : kTexts)
        for (int flags = 0; flags < 4; flags++) {
            bool date_only = flags & 1, slashes = flags & 2;
            s64 n = convert(s, -7, date_only, slashes);
            if (n == kGuest) continue;
            s64 g = static_cast<s64>(t.call(kGuestFn, {reinterpret_cast<u64>(s), static_cast<u64>(-7), date_only, slashes}));
            if (n != g && bad++ < 8) t.fail("\"%s\" (%d): native %lld, guest %lld", s, flags, (long long)n, (long long)g);
        }
    if (convert(nullptr, -7, false, false) != -7) t.fail("null text");
}

}  // namespace soa::native::info
