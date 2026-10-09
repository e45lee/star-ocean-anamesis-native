// Differential tests of the params natives against the 3.7.0 guest (in --selftest no native is
// installed: t.call reaches the original code, the natives are called directly). Maps are built in host
// memory (HostAson) with every value kind and the edge values of each conversion; every property
// instantiation of gen/params_instantiations.inc is run; elements and property lists are random (seeded
// by the test name); params/corpus replays the recorded Deserialize inputs of the four flows.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <limits>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include <soa/env.h>

#include "soaruntime/core/cpu.h"
#include "native/common/test.h"
#include "native/hash/hash_layout.h"
#include "native/params/params_check.h"
#include "native/params/params_corpus.h"
#include "native/params/params_guest.h"
#include "native/params/params_layout.h"
#include "native/params/params_parser.h"
#include "native/params/params_property.h"

using namespace soa;
using namespace soa::native::params;

namespace {

// ---- values ----

CorpusValue Nil() { return {}; }
CorpusValue Num(u32 kind, u64 bits) {
    CorpusValue v;
    v.kind = kind;
    std::memcpy(v.body, &bits, 8);
    return v;
}
CorpusValue UInt(u64 x) { return Num(AValue::kUInt, x); }
CorpusValue SInt(s64 x) { return Num(AValue::kSInt, (u64)x); }
CorpusValue Dbl(double d) {
    u64 b;
    std::memcpy(&b, &d, 8);
    return Num(AValue::kFloat, b);
}
CorpusValue Bool(bool b) { return Num(AValue::kBool, b ? 1 : 0); }
CorpusValue Str(const std::string& s, bool cstr = true) {
    CorpusValue v;
    v.kind = AValue::kString;
    v.length = (u32)s.size();
    v.has_data = true;
    v.data = s;
    v.has_cstr = cstr;
    v.cstr = s;
    return v;
}
CorpusValue Map(std::vector<std::pair<CorpusValue, CorpusValue>> kv) {
    CorpusValue v;
    v.kind = AValue::kMap;
    for (auto& [k, x] : kv) {
        v.items.push_back(k);
        v.items.push_back(x);
    }
    return v;
}
CorpusValue Arr(std::vector<CorpusValue> xs) {
    CorpusValue v;
    v.kind = AValue::kArray;
    v.items = std::move(xs);
    return v;
}

// The values every getter is tried on: each kind, the conversions' edges.
std::vector<CorpusValue> EdgeValues() {
    const double nan = std::numeric_limits<double>::quiet_NaN(), inf = std::numeric_limits<double>::infinity();
    std::vector<CorpusValue> v = {
        Nil(), Bool(false), Bool(true), UInt(0), UInt(1), UInt(2), UInt(255), UInt(256), UInt(0x1234), UInt(0x7fffffff),
        UInt(0x80000000), UInt(0xffffffff), UInt(0x100000001), UInt(0xffffffffffffffff), UInt(0x8000000000000001), UInt(0x00ffffff00000001),
        SInt(-1), SInt(-7), SInt(-129), SInt(INT64_MIN), SInt(-0x100000000), Dbl(0.0), Dbl(-0.0), Dbl(0.5), Dbl(-0.5), Dbl(1.0),
        Dbl(1.9999), Dbl(255.9), Dbl(256.0), Dbl(0x1234 + 0.75), Dbl(-1.0), Dbl(-200.25), Dbl(3.14159), Dbl(2147483647.5), Dbl(2147483648.0),
        Dbl(4294967295.9), Dbl(4294967296.0), Dbl(-2147483649.0), Dbl(1e19), Dbl(1.8446744073709552e19), Dbl(9.3e18), Dbl(-9.3e18),
        Dbl(1e300), Dbl(-1e300), Dbl(nan), Dbl(-nan), Dbl(inf), Dbl(-inf), Dbl(1e-310), Dbl(16777217.0), Str("0"), Str("1"), Str("2"),
        Str("42"), Str("-5"), Str("300"), Str("4294967296"), Str("3.75"), Str("1e3"), Str("abc"), Str(""), Str(" 12 "), Str("0x10"),
        Str("99999999999999999999"), Str("12", false), Str("a long string value of more than twenty-two characters"),
        Arr({UInt(1)}), Map({{Str("x"), UInt(1)}}), Num(AValue::kBinary, 0), Num(AValue::kExt, 0),
    };
    return v;
}

u32 Hash(const std::string& s) { return soa::native::hash::CHash32::OfCString(s.c_str()); }

Regs GuestRegs(TestContext& t, const char* sym, u64 a0, u64 a1) {
    GuestArgs a;
    a.i(a0).i(a1);
    GuestResult g = t.call(sym, a);
    return {g.x0, g.x1};
}

#define PP(name, type) "_ZN16CParameterParser" name "EPKN4Aska4ASON6AValue4AMapE" type
#define PT(t, type) "_ZN16CParameterParser8GetValueI" t "EENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapE" type
#define STDSTRING_GETVALUE(type) "_ZN16CParameterParser8GetValueINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEEENS1_4pairIT_bEEPKN4Aska4ASON6AValue4AMapE" type

struct HashGetter {
    const char* sym;
    Regs (*native)(const AMap*, u32);
    bool wide;
};
struct KeyGetter {
    const char* sym;
    Regs (*native)(const AMap*, const char*);
    bool wide;
};
template <typename T, ParserResult<T> (*F)(const AMap*, u32)>
Regs NH(const AMap* m, u32 h) {
    return ToRegs(F(m, h));
}
template <typename T, ParserResult<T> (*F)(const AMap*, const char*)>
Regs NK(const AMap* m, const char* k) {
    return ToRegs(F(m, k));
}
using CP = CParameterParser;
const HashGetter kHashGetters[] = {
    {PP("14GetValueString", "j"), NH<const char*, CP::GetValueString>, true},
    {PP("13GetValueFloat", "j"), NH<float, CP::GetValueFloat>, false},
    {PP("11GetValueInt", "j"), NH<s32, CP::GetValueInt>, false},
    {PP("12GetValueUInt", "j"), NH<u32, CP::GetValueUInt>, false},
    {PP("12GetValueLong", "j"), NH<s64, CP::GetValueLong>, true},
    {PP("13GetValueULong", "j"), NH<u64, CP::GetValueULong>, true},
    {PP("12GetValueBool", "j"), NH<u8, CP::GetValueBool>, false},
    {PP("13GetValueUTiny", "j"), NH<u8, CP::GetValueUTiny>, false},
    {PT("f", "j"), NH<float, CP::GetValueFloat>, false},
    {PT("i", "j"), NH<s32, CP::GetValueInt>, false},
    {PT("j", "j"), NH<u32, CP::GetValueUInt>, false},
    {PT("l", "j"), NH<s64, CP::GetValueLong>, true},
    {PT("m", "j"), NH<u64, CP::GetValueULong>, true},
    {PT("b", "j"), NH<u8, CP::GetValueBool>, false},
    {PT("h", "j"), NH<u8, CP::GetValueUTiny>, false},
    {PT("Pc", "j"), NH<const char*, CP::GetValueString>, true},
};
const KeyGetter kKeyGetters[] = {
    {PP("14GetValueString", "PKc"), NK<const char*, CP::GetValueString>, true},
    {PP("13GetValueFloat", "PKc"), NK<float, CP::GetValueFloat>, false},
    {PP("11GetValueInt", "PKc"), NK<s32, CP::GetValueInt>, false},
    {PP("12GetValueUInt", "PKc"), NK<u32, CP::GetValueUInt>, false},
    {PP("12GetValueLong", "PKc"), NK<s64, CP::GetValueLong>, true},
    {PP("13GetValueULong", "PKc"), NK<u64, CP::GetValueULong>, true},
    {PP("12GetValueBool", "PKc"), NK<u8, CP::GetValueBool>, false},
    {PP("13GetValueUTiny", "PKc"), NK<u8, CP::GetValueUTiny>, false},
    {PT("b", "PKc"), NK<u8, CP::GetValueBool>, false},
    {PT("h", "PKc"), NK<u8, CP::GetValueUTiny>, false},
    // (the 4-byte tail branches: the guest's, landing on the typed getters' original code here)
    {PT("f", "PKc"), NK<float, CP::GetValueFloat>, false},
    {PT("i", "PKc"), NK<s32, CP::GetValueInt>, false},
    {PT("j", "PKc"), NK<u32, CP::GetValueUInt>, false},
    {PT("l", "PKc"), NK<s64, CP::GetValueLong>, true},
    {PT("m", "PKc"), NK<u64, CP::GetValueULong>, true},
    {PT("Pc", "PKc"), NK<const char*, CP::GetValueString>, true},
};

bool SameRegs(Regs a, Regs b, bool wide) { return a.x0 == b.x0 && (!wide || a.x1 == b.x1); }

// The getters' map: every edge value under a short key ("k<i>") and a long one (> 12 characters: the
// by-key getters' dropped message then allocates), plus keys that aren't strings, a key without its C
// string, an empty key and a duplicate (the first one counts).
struct GetterMap {
    std::vector<std::string> keys;
    std::vector<u32> kinds;  // each key's value kind (the first one's), 0 when absent
    CorpusValue map;
};
GetterMap MakeGetterMap() {
    GetterMap g;
    std::vector<std::pair<CorpusValue, CorpusValue>> kv;
    auto values = EdgeValues();
    for (size_t i = 0; i < values.size(); i++) {
        std::string s = "k" + std::to_string(i), l = "a_long_key_number_" + std::to_string(i);
        kv.push_back({Str(s), values[i]});
        kv.push_back({Str(l), values[i]});
        g.keys.push_back(s);
        g.keys.push_back(l);
        g.kinds.push_back(values[i].kind);
        g.kinds.push_back(values[i].kind);
    }
    kv.push_back({UInt(7), UInt(1)});
    kv.push_back({Str("nocstr", false), UInt(5)});
    kv.push_back({Str(""), UInt(6)});
    kv.push_back({Str("k3"), UInt(99)});  // a duplicate of k3
    for (const char* k : {"nocstr", "", "absent", "an_absent_key_with_a_long_name"}) {
        g.keys.push_back(k);
        g.kinds.push_back(*k && std::strcmp(k, "nocstr") ? 0 : AValue::kUInt);
    }
    g.map = Map(kv);
    return g;
}

const AMap* MapOf(const HostAson& h) { return &h.root()->m_body.map; }

}  // namespace

// The constants the natives pass on to the guest (asserts, the dropped messages, the allocator's file).
NATIVE_TEST("params/guest-constants") {
    auto s = [](u64 va) { return std::string((const char*)g::at(va)); };
    t.expect_eq(s(g::kApObjectIsNull), std::string("apObject is null."), "apObject");
    t.expect_eq(s(g::kApParserIsNull), std::string("apParser is null."), "apParser");
    t.expect_eq(s(g::kApValueIsNull), std::string("apValue is null."), "apValue");
    t.expect_eq(s(g::kNotFound), std::string("not found "), "not found");
    t.expect_eq(s(g::kNotMatch), std::string("not match "), "not match");
    t.expect_eq(s(g::kEmptyString), std::string(""), "empty");
    t.expect_eq(s(native::kStrNumElementsIsZero), std::string("aNumElements is zero."), "aNumElements");
    t.expect_eq(s(native::kStrAllocatedMemoryIsNull), std::string("pAllocatedMemory is null."), "pAllocatedMemory");
    auto ends = [&](u64 va, const char* tail) {
        std::string x = s(va);
        return x.size() >= strlen(tail) && x.compare(x.size() - strlen(tail), strlen(tail), tail) == 0;
    };
    t.expect_eq(ends(g::kParameterParserCpp, "Parameter\\ParameterParser.cpp"), true, "ParameterParser.cpp");
    t.expect_eq(ends(g::kParameterParserH, "Game/Parameter/ParameterParser.h"), true, "ParameterParser.h");
    t.expect_eq(ends(g::kParameterBaseCpp, "Parameter\\ParameterBase.cpp"), true, "ParameterBase.cpp");
    t.expect_eq(ends(native::kStrStlAllocatorH, "Framework/STL_Allocator.h"), true, "STL_Allocator.h");
    t.expect_eq(ends(native::kStrStlStringH, "Framework/STL_String.h"), true, "STL_String.h");
}

// GetParserValue (also hash 0, an absent hash, the key-hash cache) and every getter by hash.
NATIVE_TEST("params/parser-by-hash") {
    GetterMap gm = MakeGetterMap();
    HostAson a(gm.map);
    const AMap* m = MapOf(a);
    std::vector<u32> hashes = {0, 0x12345678};
    for (auto& k : gm.keys) hashes.push_back(Hash(k));
    int bad = 0;
    for (int cached = 0; cached < 2; cached++) {
        std::unique_ptr<KeyHashes> keys(cached ? new KeyHashes(m) : nullptr);
        for (u32 h : hashes) {
            u64 g = t.call(PP("14GetParserValue", "j"), {(u64)m, h});
            u64 n = (u64)CParameterParser::GetParserValue(m, h);
            if (g != n && bad++ < 5) t.fail("GetParserValue(%#x)%s: native %#llx guest %#llx", h, cached ? " (cached)" : "", (unsigned long long)n, (unsigned long long)g);
            for (const HashGetter& hg : kHashGetters) {
                Regs gr = GuestRegs(t, hg.sym, (u64)m, h), nr = hg.native(m, h);
                if (!SameRegs(gr, nr, hg.wide) && bad++ < 20)
                    t.fail("%s(%#x)%s: native %#llx %#llx guest %#llx %#llx", hg.sym, h, cached ? " (cached)" : "", (unsigned long long)nr.x0,
                           (unsigned long long)nr.x1, (unsigned long long)gr.x0, (unsigned long long)gr.x1);
            }
        }
    }
    t.expect_eq(bad, 0, "by-hash mismatches");
}

// Every getter by key (AMap::Get_; a missing key or a kind the getter doesn't take drops a message,
// which allocates for a key over 12 characters).
NATIVE_TEST("params/parser-by-key") {
    GetterMap gm = MakeGetterMap();
    HostAson a(gm.map);
    const AMap* m = MapOf(a);
    int bad = 0;
    for (auto& k : gm.keys) {
        for (const KeyGetter& kg : kKeyGetters) {
            Regs gr = GuestRegs(t, kg.sym, (u64)m, (u64)k.c_str()), nr = kg.native(m, k.c_str());
            if (!SameRegs(gr, nr, kg.wide) && bad++ < 20)
                t.fail("%s(\"%s\"): native %#llx %#llx guest %#llx %#llx", kg.sym, k.c_str(), (unsigned long long)nr.x0, (unsigned long long)nr.x1,
                       (unsigned long long)gr.x0, (unsigned long long)gr.x1);
        }
    }
    t.expect_eq(bad, 0, "by-key mismatches");
}

// GetValue(AValue const*) (a double in d0) and GetValue<std::string> by hash and by key (x8).
NATIVE_TEST("params/parser-double-and-string") {
    int bad = 0;
    for (auto& v : EdgeValues()) {
        HostAson a(v);
        GuestArgs ga;
        ga.i((u64)a.root());
        GuestResult g = t.call("_ZN16CParameterParser8GetValueEPKN4Aska4ASON6AValueE", ga);
        double n = CParameterParser::GetValue(a.root());
        u64 nb;
        std::memcpy(&nb, &n, 8);
        if (nb != g.v0.lo && bad++ < 5) t.fail("GetValue(kind %u): native %#llx guest %#llx", v.kind, (unsigned long long)nb, (unsigned long long)g.v0.lo);
    }
    GetterMap gm = MakeGetterMap();
    HostAson a(gm.map);
    const AMap* m = MapOf(a);
    for (size_t ki = 0; ki < gm.keys.size(); ki++) {
        const std::string& k = gm.keys[ki];
        // (an array, map, binary or ext value: GetValueString takes the 8 bytes at +0x10 (a count) as the
        // C string, and GetValue<std::string>'s strlen faults in the guest too)
        if (gm.kinds[ki] >= AValue::kArray) continue;
        for (int by_key = 0; by_key < 2; by_key++) {
            alignas(16) StdStringResult gs, ns;
            std::memset(&gs, 0xcc, sizeof gs);
            std::memset(&ns, 0xcc, sizeof ns);
            GuestArgs ga;
            ga.i((u64)m).i(by_key ? (u64)k.c_str() : (u64)Hash(k)).sret(&gs);
            t.call(by_key ? STDSTRING_GETVALUE("PKc") : STDSTRING_GETVALUE("j"), ga);
            if (by_key) CParameterParser::GetValueStdString(&ns, m, k.c_str());
            else CParameterParser::GetValueStdString(&ns, m, Hash(k));
            std::string d = diff_strings(ns.first, gs.first);
            if (d.empty() && std::memcmp(&ns.second, &gs.second, 8) != 0) d = "the bool and the bytes after it";
            if (!d.empty() && bad++ < 10) t.fail("GetValue<std::string>(%s \"%s\"): %s", by_key ? "key" : "hash", k.c_str(), d.c_str());
            free_copy(ns.first);
            free_copy(gs.first);
        }
    }
    t.expect_eq(bad, 0, "mismatches");
}

// ---- properties ----

namespace {

struct ValueRow {
    const char* t;
    u32 n;
    const char* sym;
    const char* ztv;
};
#define PARAMS_TEST_VROW(T, N, CONV, SYM, ZTV) {#T, N, SYM, ZTV},
struct StringRow {
    u32 n;
    const char* sym;
    const char* crypt;
    const char* ztv;
};
#define PARAMS_TEST_SROW(N, SYM, CRYPT, ZTV) {N, SYM, CRYPT, ZTV},
#include "native/params/gen/params_instantiations.inc"
const ValueRow kValueRows[] = {PARAMS_VALUES(PARAMS_TEST_VROW)};
const StringRow kStringRows[] = {PARAMS_STRINGS(PARAMS_TEST_SROW)};

// A property object (0x40 bytes, enough for either kind) in host memory.
struct alignas(16) PropBuf {
    u8 b[0x40];
};
u64 HashVtable(TestContext& t) { return t.sym("_ZTVN9Framework7CHash32E") + 0x10; }

void InitProperty(TestContext& t, PropBuf& p, const char* ztv, u32 name, bool named, u64 value_pattern) {
    std::memset(p.b, 0, sizeof p.b);
    u64 vt = t.sym(ztv) + 0x10;
    std::memcpy(p.b, &vt, 8);
    p.b[0x10] = named;
    u64 hv = HashVtable(t);
    std::memcpy(p.b + 0x18, &hv, 8);
    std::memcpy(p.b + 0x20, &name, 4);
    std::memcpy(p.b + 0x28, &value_pattern, 8);
}

// A game string of `s` with at least `cap` capacity (cap <= 22: short).
void MakeString(String& dst, const std::string& s, u64 cap) {
    std::memset(&dst, 0, sizeof dst);
    if (cap <= 22 && s.size() <= 22) {
        dst.r.s.head.size = u8(s.size() << 1);
        std::memcpy(dst.r.s.data, s.data(), s.size());
        return;
    }
    if (cap < s.size()) cap = s.size();
    u64 alloc = (cap + 16) & ~u64(15);
    char* p = (char*)g::StlAllocate(alloc, native::kStrStlStringH, 0x1c);
    std::memset(p, 0x77, alloc);
    std::memcpy(p, s.data(), s.size());
    p[s.size()] = 0;
    dst.r.l.cap = alloc | 1;
    dst.r.l.size = s.size();
    dst.r.l.data = p;
}

std::string Repeat(const char* unit, size_t n) {
    std::string s;
    while (s.size() < n) s += unit;
    s.resize(n);
    return s;
}

}  // namespace

// Every CParameterPropertyValue<T, N, Conv>::Deserialize against its guest instantiation, on every
// edge value (and a missing key): the object's 0x30 bytes and the result.
NATIVE_TEST("params/property-values") {
    auto values = EdgeValues();
    std::vector<std::pair<CorpusValue, CorpusValue>> kv;
    for (size_t i = 0; i < values.size(); i++) kv.push_back({Str("v" + std::to_string(i)), values[i]});
    HostAson a(Map(kv));
    const AMap* m = MapOf(a);
    int bad = 0, runs = 0;
    for (const ValueRow& r : kValueRows) {
        for (size_t i = 0; i <= values.size(); i++) {
            u32 name = Hash("v" + std::to_string(i));  // (i == size: absent)
            PropBuf gp, np;
            InitProperty(t, gp, r.ztv, name, true, 0x5a5a5a5a5a5a5a5aull);
            np = gp;
            u64 gr = t.call(r.sym, {(u64)gp.b, (u64)m}) & 0xff;
            PropertyDeserialize fn = KnownProperty(*(const void**)np.b);
            if (!fn) {
                t.fail("%s: not bound", r.sym);
                return;
            }
            bool nr = fn((IParameterProperty*)np.b, m);
            runs++;
            if ((gr != nr || std::memcmp(gp.b, np.b, 0x30) != 0) && bad++ < 10)
                t.fail("%s on value %zu: result native %d guest %d, %s", r.sym, i, (int)nr, (int)gr,
                       live::RunBothFamily::diff_bytes(np.b, gp.b, 0x30).c_str());
        }
    }
    t.expect_eq(runs, (int)(std::size(kValueRows) * (values.size() + 1)), "runs");
    t.expect_eq(bad, 0, "property value mismatches");
}

// Every CParameterPropertyBase<N>::CryptString: sources of 0..100 bytes into destinations short and
// long (the growth through __grow_by), and the source as its own destination.
NATIVE_TEST("params/property-cryptstring") {
    const size_t lens[] = {0, 1, 5, 21, 22, 23, 30, 46, 47, 48, 100};
    const u64 caps[] = {0, 22, 30, 47, 200};
    int bad = 0;
    for (const StringRow& r : kStringRows) {
        CryptStringFn fn = KnownCryptString(r.crypt);
        if (!fn) {
            t.fail("%s: not bound", r.crypt);
            return;
        }
        for (size_t len : lens) {
            for (u64 cap : caps) {
                if ((size_t)t.rand_int(0, 3) != 0 && len != 23) continue;  // (a sample; 23 always: the first growth)
                alignas(16) String src, gd, nd;
                MakeString(src, Repeat("\x01Xy\xff~ ", len), len);
                MakeString(gd, "old contents", cap);
                copy_string(nd, gd);
                t.call(r.crypt, {(u64)&gd, (u64)&src});
                fn(nd, src);
                std::string d = diff_strings(nd, gd);
                if (!d.empty() && bad++ < 10) t.fail("%s len %zu cap %llu: %s", r.crypt, len, (unsigned long long)cap, d.c_str());
                free_copy(gd);
                free_copy(nd);
                free_copy(src);
            }
        }
        // aliasing: CryptString(s, s) clears it
        alignas(16) String gs, ns;
        MakeString(gs, "aliased string longer than twenty-two", 0);
        copy_string(ns, gs);
        t.call(r.crypt, {(u64)&gs, (u64)&gs});
        fn(ns, ns);
        std::string d = diff_strings(ns, gs);
        if (!d.empty() && bad++ < 10) t.fail("%s aliased: %s", r.crypt, d.c_str());
        free_copy(gs);
        free_copy(ns);
    }
    t.expect_eq(bad, 0, "CryptString mismatches");
}

// Every CParameterPropertyString<std::string, N>::Deserialize: string values short, long and absent,
// other kinds, into destinations short and long.
NATIVE_TEST("params/property-strings") {
    std::vector<CorpusValue> vals = {Str(""), Str("abc"), Str(Repeat("0123456789", 22)), Str(Repeat("xy", 23)), Str(Repeat("long value ", 9)),
                                     Str("nocstr", false), UInt(5), Nil(), Bool(true)};
    std::vector<std::pair<CorpusValue, CorpusValue>> kv;
    for (size_t i = 0; i < vals.size(); i++) kv.push_back({Str("s" + std::to_string(i)), vals[i]});
    HostAson a(Map(kv));
    const AMap* m = MapOf(a);
    const u64 caps[] = {0, 47};
    int bad = 0;
    for (const StringRow& r : kStringRows) {
        for (size_t i = 0; i <= vals.size(); i++) {
            for (u64 cap : caps) {
                PropBuf gp, np;
                InitProperty(t, gp, r.ztv, Hash("s" + std::to_string(i)), true, 0);
                String& gs = *(String*)(gp.b + 0x28);
                MakeString(gs, "previous", cap);
                np = gp;
                copy_string(*(String*)(np.b + 0x28), gs);
                u64 gr = t.call(r.sym, {(u64)gp.b, (u64)m}) & 0xff;
                bool nr = KnownProperty(*(const void**)np.b)((IParameterProperty*)np.b, m);
                std::string d = live::RunBothFamily::diff_bytes(np.b, gp.b, 0x28);
                if (d.empty()) d = diff_strings(*(String*)(np.b + 0x28), gs);
                if (d.empty() && gr != nr) d = "the result";
                if (!d.empty() && bad++ < 10) t.fail("%s value %zu cap %llu: %s", r.sym, i, (unsigned long long)cap, d.c_str());
                free_copy(gs);
                free_copy(*(String*)(np.b + 0x28));
            }
        }
    }
    t.expect_eq(bad, 0, "string property mismatches");
}

// ---- elements ----

namespace {

// A synthetic element: CParameterElementBase, then its properties in 0x40-byte slots, linked in
// order; a property's name from the pool or none (CHash32() = 0). Two copies are built the same way.
struct Element {
    std::vector<PropBuf> buf;  // [0]: the element base; [1..]: properties
    CParameterElementBase* base() { return (CParameterElementBase*)buf[0].b; }
    IParameterProperty* prop(size_t k) { return (IParameterProperty*)buf[1 + k].b; }
};
struct PropSpec {
    bool string;
    size_t row;
    u32 name;
    bool named;
    std::string initial;
    u64 cap;
};

void Build(TestContext& t, Element& e, const std::vector<PropSpec>& specs, const void* foreign_vt, size_t foreign_at, bool self_link) {
    e.buf.assign(1 + specs.size(), PropBuf{});
    u64 evt = t.sym("_ZTV21CParameterElementBase") + 0x10;
    std::memcpy(e.buf[0].b, &evt, 8);
    for (size_t k = 0; k < specs.size(); k++) {
        const PropSpec& s = specs[k];
        InitProperty(t, e.buf[1 + k], s.string ? kStringRows[s.row].ztv : kValueRows[s.row].ztv, s.name, s.named, 0x1122334455667788ull + k);
        if (s.string) MakeString(*(String*)(e.buf[1 + k].b + 0x28), s.initial, s.cap);
        if (k == foreign_at) std::memcpy(e.buf[1 + k].b, &foreign_vt, 8);
    }
    for (size_t k = 0; k < specs.size(); k++) e.base()->AddProperty(e.prop(k));  // (the native AddProperty: tested below)
    if (self_link && !specs.empty()) e.prop(specs.size() - 1)->m_next = e.prop(specs.size() - 1);
}
void FreeStrings(Element& e, const std::vector<PropSpec>& specs) {
    for (size_t k = 0; k < specs.size(); k++)
        if (specs[k].string) free_copy(*(String*)(e.buf[1 + k].b + 0x28));
}
// The properties' bytes but m_next (each copy links its own), the strings by their representation.
std::string Compare(Element& n, Element& g, const std::vector<PropSpec>& specs) {
    for (size_t k = 0; k < specs.size(); k++) {
        size_t bytes = specs[k].string ? 0x28 : 0x30;
        std::string d = live::RunBothFamily::diff_bytes(n.buf[1 + k].b, g.buf[1 + k].b, 8);
        if (d.empty()) d = live::RunBothFamily::diff_bytes(n.buf[1 + k].b + 0x10, g.buf[1 + k].b + 0x10, bytes - 0x10);
        if (d.empty() && specs[k].string) d = diff_strings(*(String*)(n.buf[1 + k].b + 0x28), *(String*)(g.buf[1 + k].b + 0x28));
        if (!d.empty()) return "property " + std::to_string(k) + ": " + d;
    }
    return {};
}

}  // namespace

// CParameterElementBase::Deserialize on random elements and maps: lists of up to 40 properties (the
// short walk and the sorted index), names shared by several properties (the first gets the key),
// unnamed properties and an empty key (hash 0), keys that aren't strings or lack the C string,
// duplicate keys (each pair is a call), a property with a vtable that isn't bound (the literal walk).
NATIVE_TEST("params/element-deserialize") {
    const char* pool[] = {"Id", "Token", "Level", "Role", "PersonID", "Weapon", "Name", "", "rarity", "hp", "atk", "a_long_property_name",
                          "x", "y", "z", "speed", "range", "radius", "flag", "count"};
    // a vtable copy (unbound address, the same slots): the literal walk through guest calls
    alignas(16) static u64 foreign[8];
    std::memcpy(foreign, (const void*)(t.sym(kValueRows[0].ztv)), sizeof foreign);
    const void* foreign_vt = &foreign[2];
    // (no array / map / binary values: a string property's GetValue<std::string> faults on them in the guest)
    std::vector<CorpusValue> values;
    for (auto& v : EdgeValues())
        if (v.kind < AValue::kArray) values.push_back(v);
    int bad = 0;
    for (int iter = 0; iter < 400; iter++) {
        size_t np = (size_t)t.rand_int(0, iter % 4 == 0 ? 40 : 12);
        std::vector<PropSpec> specs;
        for (size_t k = 0; k < np; k++) {
            PropSpec s;
            s.string = t.rand_int(0, 4) == 0;
            s.row = (size_t)t.rand_int(0, s.string ? (int)std::size(kStringRows) - 1 : (int)std::size(kValueRows) - 1);
            s.named = t.rand_int(0, 9) != 0;
            s.name = s.named ? Hash(pool[t.rand_int(0, (int)std::size(pool) - 1)]) : 0;
            s.initial = t.rand_int(0, 1) ? "init" : Repeat("initial long value ", 30);
            s.cap = t.rand_int(0, 1) ? 0 : 60;
            specs.push_back(s);
        }
        std::vector<std::pair<CorpusValue, CorpusValue>> kv;
        size_t nk = (size_t)t.rand_int(0, 30);
        for (size_t i = 0; i < nk; i++) {
            int r = t.rand_int(0, 19);
            CorpusValue key = r == 0 ? UInt(3) : r == 1 ? Str(pool[t.rand_int(0, 19)], false) : Str(pool[t.rand_int(0, (int)std::size(pool) - 1)]);
            CorpusValue v = t.rand_int(0, 3) == 0 ? Str(t.rand_int(0, 1) ? "str" : Repeat("value ", 7)) : values[(size_t)t.rand_int(0, (int)values.size() - 1)];
            kv.push_back({key, v});
        }
        HostAson a(Map(kv));
        const AMap* m = MapOf(a);
        size_t foreign_at = iter % 7 == 3 && np ? (size_t)t.rand_int(0, (int)np - 1) : (size_t)-1;
        if (foreign_at != (size_t)-1 && specs[foreign_at].string) foreign_at = (size_t)-1;  // (the copy is a value vtable)
        Element ge, ne;
        Build(t, ge, specs, foreign_vt, foreign_at, false);
        Build(t, ne, specs, foreign_vt, foreign_at, false);
        u64 gr = t.call("_ZN21CParameterElementBase11DeserializeEPKN4Aska4ASON6AValue4AMapE", {(u64)ge.base(), (u64)m}) & 0xff;
        bool nr = ne.base()->Deserialize(m);
        std::string d = Compare(ne, ge, specs);
        if (d.empty() && gr != nr) d = "the result";
        if (!d.empty() && bad++ < 10) t.fail("iteration %d (%zu properties, %zu keys): %s", iter, np, nk, d.c_str());
        FreeStrings(ge, specs);
        FreeStrings(ne, specs);
    }
    t.expect_eq(bad, 0, "element mismatches");
}

// AddProperty: the list built by the guest and by the native from the same sequence of adds (new
// properties, ones already in the list, the last one again: the self link).
NATIVE_TEST("params/element-addproperty") {
    int bad = 0;
    for (int iter = 0; iter < 300; iter++) {
        alignas(16) static IParameterProperty gn[16], nn[16];
        alignas(16) CParameterElementBase ge{nullptr, nullptr}, ne{nullptr, nullptr};
        std::memset(gn, 0, sizeof gn);
        std::memset(nn, 0, sizeof nn);
        int ops = t.rand_int(1, 20);
        bool self = false;
        for (int o = 0; o < ops && !self; o++) {
            int k = t.rand_int(0, 15);
            // (adding to a self-linked list other than its last spins: stop once linked to itself)
            t.call("_ZN21CParameterElementBase11AddPropertyEP18IParameterProperty", {(u64)&ge, (u64)&gn[k]});
            ne.AddProperty(&nn[k]);
            for (int j = 0; j < 16; j++) self |= gn[j].m_next == &gn[j];
        }
        auto idx = [](IParameterProperty* p, IParameterProperty* base) { return p ? (long)(p - base) : -1L; };
        bool same = idx(ge.m_first, gn) == idx(ne.m_first, nn);
        for (int j = 0; j < 16; j++) same &= idx(gn[j].m_next, gn) == idx(nn[j].m_next, nn);
        if (!same && bad++ < 5) t.fail("iteration %d: the lists differ", iter);
    }
    t.expect_eq(bad, 0, "AddProperty mismatches");
}

// CParameterBase::pGetRoot / Find on a CParameterPlayer (pParseName "Player") over maps with and
// without the key.
NATIVE_TEST("params/base-getroot") {
    alignas(16) static u8 player[0x200];
    t.call("_ZN16CParameterPlayerC1Ev", {(u64)player});
    const CParameterBase* b = (const CParameterBase*)player;
    HostAson with(Map({{Str("Other"), UInt(1)}, {Str("Player"), Map({{Str("Id"), UInt(5)}})}}));
    HostAson without(Map({{Str("Other"), UInt(1)}}));
    for (const HostAson* h : {&with, &without}) {
        const AMap* m = MapOf(*h);
        t.expect_eq((u64)b->pGetRoot(m), t.call("_ZNK14CParameterBase8pGetRootEPKN4Aska4ASON6AValue4AMapE", {(u64)player, (u64)m}), "pGetRoot");
        t.expect_eq((u64)((CParameterBase*)player)->Find(m), t.call("_ZN14CParameterBase4FindEPKN4Aska4ASON6AValue4AMapE", {(u64)player, (u64)m}) & 0xff, "Find");
    }
    t.call("_ZN16CParameterPlayerD1Ev", {(u64)player});
}

// The recorded inputs of CParameterElementBase::Deserialize over the login, battle, gacha and story
// flows (port/src/native/params/testdata/*.corpus; `soa --live-check params:dump:out=FILE`): each
// element rebuilt twice (its properties at their offsets, their vtables, names, values and strings),
// deserialized by the guest and by the native, compared whole.
NATIVE_TEST("params/corpus") {
    std::vector<std::string> files;
    auto scan = [&](const std::string& dir) {
        if (DIR* d = opendir(dir.c_str())) {
            while (dirent* e = readdir(d)) {
                std::string n = e->d_name;
                if (n.size() > 7 && n.compare(n.size() - 7, 7, ".corpus") == 0) files.push_back(dir + "/" + n);
            }
            closedir(d);
        }
    };
    const char* dir = "port/src/native/params/testdata";
    scan(dir);
    if (const char* more = env::env_str("SOA_PARAMS_CORPUS")) scan(more);  // (the whole recordings: README.md "Tests")
    if (files.empty()) {
        t.fail("no corpus in %s (run soa from the repository root)", dir);
        return;
    }
    size_t records = 0;
    int bad = 0;
    for (const std::string& f : files) {
        std::vector<CorpusRecord> recs;
        if (!corpus_read(f, recs)) {
            t.fail("%s: unreadable", f.c_str());
            continue;
        }
        for (const CorpusRecord& r : recs) {
            records++;
            HostAson a(r.map);
            const AMap* m = MapOf(a);
            // the element: its properties at their recorded offsets (from the element), at least 0x10 after it
            s64 lo = 0, hi = 0x10;
            for (auto& p : r.props) {
                lo = std::min(lo, p.offset);
                hi = std::max<s64>(hi, p.offset + 0x40);
            }
            std::vector<PropBuf> gbuf((size_t)((hi - lo + 15) / 16) + 1), nbuf(gbuf.size());
            auto at = [&](std::vector<PropBuf>& b, s64 off) { return (u8*)b.data() + (off - lo); };
            auto build = [&](std::vector<PropBuf>& b) {
                std::memset(b.data(), 0, b.size() * sizeof(PropBuf));
                u64 evt = t.sym("_ZTV21CParameterElementBase") + 0x10;
                CParameterElementBase* e = (CParameterElementBase*)at(b, 0);
                e->vtable = (const void*)evt;
                IParameterProperty** link = &e->m_first;
                for (auto& p : r.props) {
                    u8* o = at(b, p.offset);
                    std::memcpy(o, p.head, 0x28);
                    u64 vt = t.sym(p.ztv.c_str()) + 0x10, hv = HashVtable(t);
                    std::memcpy(o, &vt, 8);
                    std::memcpy(o + 0x18, &hv, 8);
                    if (p.kind == 0) std::memcpy(o + 0x28, p.value, 8);
                    else MakeString(*(String*)(o + 0x28), p.bytes, p.capacity);
                    *link = (IParameterProperty*)o;
                    link = &((IParameterProperty*)o)->m_next;
                }
                if (r.self_linked && !r.props.empty()) *link = (IParameterProperty*)at(b, r.props.back().offset);
                return e;
            };
            CParameterElementBase* ge = build(gbuf);
            CParameterElementBase* ne = build(nbuf);
            if (r.self_linked) continue;  // (a self-linked list spins on a key no property has, in both)
            u64 gr = t.call("_ZN21CParameterElementBase11DeserializeEPKN4Aska4ASON6AValue4AMapE", {(u64)ge, (u64)m}) & 0xff;
            bool nr = ne->Deserialize(m);
            std::string d;
            for (auto& p : r.props) {
                u8 *go = at(gbuf, p.offset), *no = at(nbuf, p.offset);
                d = live::RunBothFamily::diff_bytes(no, go, 8);  // (m_next: each copy links its own)
                if (d.empty()) d = live::RunBothFamily::diff_bytes(no + 0x10, go + 0x10, p.kind == 0 ? 0x20 : 0x18);
                if (d.empty() && p.kind == 1) d = diff_strings(*(String*)(no + 0x28), *(String*)(go + 0x28));
                if (!d.empty()) {
                    d = p.ztv + " at " + std::to_string(p.offset) + ": " + d;
                    break;
                }
            }
            if (d.empty() && gr != nr) d = "the result";
            if (!d.empty() && bad++ < 10) t.fail("%s record %zu (%s): %s", f.c_str(), records, r.element.c_str(), d.c_str());
            for (auto& p : r.props)
                if (p.kind == 1) {
                    free_copy(*(String*)(at(gbuf, p.offset) + 0x28));
                    free_copy(*(String*)(at(nbuf, p.offset) + 0x28));
                }
        }
    }
    fprintf(stderr, "params/corpus: %zu records from %zu files\n", records, files.size());
    t.expect_eq(records > 0, true, "records");
    t.expect_eq(bad, 0, "corpus mismatches");
}
