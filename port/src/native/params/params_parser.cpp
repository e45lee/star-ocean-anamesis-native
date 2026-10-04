// CParameterParser: the parameter getters over an ASON map (params_layout.h; port/decomp/params/parser.c,
// the conversions read from the disassembly: ucvtf / scvtf / fcvt for float, fcvtzs / fcvtzu for the
// integers). Each getter keeps its own kind set (README.md "The parser's kinds").
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "native/common/arm_float.h"
#include "native/common/native.h"
#include "native/hash/hash_layout.h"
#include "native/params/params_check.h"
#include "native/params/params_guest.h"
#include "native/params/params_parser.h"

namespace soa::native::params {

// ---- the key-hash cache ----

namespace {
thread_local const KeyHashes* t_keys = nullptr;
}

KeyHashes::KeyHashes(const AMap* map) : map_(map), pairs_(map->m_pairs), count_(map->m_count), outer_(t_keys) {
    if (count_ <= kInline) {
        hash_ = inline_hash_;
        named_ = inline_named_;
    } else {
        heap_hash_.resize(count_);
        heap_named_.resize(count_);
        hash_ = heap_hash_.data();
        named_ = heap_named_.data();
    }
    for (u32 i = 0; i < count_; i++) {
        const AValue& k = pairs_[i].key;
        const char* s = k.m_kind == AValue::kString ? k.m_body.str.m_cstr : nullptr;
        hash_[i] = k.m_kind == AValue::kString ? hash::CHash32::OfCString(s) : 0;
        named_[i] = s != nullptr;
    }
    t_keys = this;
}
KeyHashes::~KeyHashes() { t_keys = outer_; }
const KeyHashes* KeyHashes::current() { return t_keys; }

// ---- the getters ----

namespace {

template <typename T>
ParserResult<T> Found(T v) {
    return {v, 1};
}
template <typename T>
ParserResult<T> None() {
    return {T{}, 0};
}

// GetParserValue's checked entry (below): the getters' lookups, as the guest's go through the PLT.
const AValue* ParserValueEntry(const AMap* map, u32 hash);

const char* EmptyString() { return (const char*)g::at(g::kEmptyString); }

// The by-key getters build "not found " / "not match " + key in a stack string and drop it (a log
// compiled out). A key of up to 12 characters fits the short string (nothing to see); a longer one
// goes through __grow_by_and_replace, i.e. an STL block allocated and freed: done the same way.
void DropMessage(u64 prefix_vaddr, const char* key) {
    u64 len = std::strlen(key);
    if (len <= 12) return;
    alignas(16) String s;
    std::memset(&s, 0, sizeof s);
    s.r.s.head.size = 10 << 1;
    std::memcpy(s.r.s.data, (const void*)g::at(prefix_vaddr), 10);
    g::GrowByAndReplace(&s, 22, len - 12, 10, 10, 0, len, key);
    if (s.is_long()) g::StlFree(s.r.l.data);
}

const char* CString(const AValue* v) { return v->m_body.str.m_cstr; }  // (+0x10, read for any kind as the guest does)
u32 Low32(const AValue* v) { return (u32)v->m_body.u; }
u8 Low8(const AValue* v) { return (u8)v->m_body.u; }

// The conversions, as each getter does them; `none` is the result for a kind it doesn't take (the
// by-key getters drop a "not match " message then).
ParserResult<float> ToFloat(const AValue* v, bool& bad) {
    switch (v->m_kind) {
    case AValue::kUInt: return Found((float)v->m_body.u);  // ucvtf s, x (one rounding)
    case AValue::kSInt: return Found((float)v->m_body.s);  // scvtf s, x
    case AValue::kFloat: return Found((float)v->m_body.d);  // fcvt s, d
    case AValue::kString:
        if (!CString(v)) break;
        return Found((float)std::atof(CString(v)));  // the guest's atof is the host's (HLE)
    default: break;
    }
    bad = true;
    return None<float>();
}
ParserResult<s32> ToInt(const AValue* v, bool& bad) {
    switch (v->m_kind) {
    case AValue::kUInt:
    case AValue::kSInt: return Found((s32)Low32(v));
    case AValue::kFloat: return Found(armf::cvtzs_w(v->m_body.d));
    case AValue::kString:
        if (!CString(v)) break;
        return Found(g::StringToInt(CString(v)));
    default: break;
    }
    bad = true;
    return None<s32>();
}
// by_hash: GetValueUInt(map, unsigned) also takes a bool (kind 1); the by-key one doesn't.
ParserResult<u32> ToUInt(const AValue* v, bool& bad, bool by_hash) {
    switch (v->m_kind) {
    case AValue::kBool:
        if (!by_hash) break;
        return Found((u32)Low8(v));
    case AValue::kUInt:
    case AValue::kSInt: return Found(Low32(v));
    case AValue::kFloat: return Found(armf::cvtzu_w(v->m_body.d));
    case AValue::kString:
        if (!CString(v)) break;
        return Found(g::StringToUInt(CString(v)));
    default: break;
    }
    bad = true;
    return None<u32>();
}
ParserResult<s64> ToLong(const AValue* v, bool& bad) {
    switch (v->m_kind) {
    case AValue::kUInt:
    case AValue::kSInt: return Found(v->m_body.s);
    case AValue::kFloat: return Found(armf::cvtzs_x(v->m_body.d));
    case AValue::kString:
        if (!CString(v)) break;
        return Found(g::StringToLong(CString(v)));
    default: break;
    }
    bad = true;
    return None<s64>();
}
ParserResult<u64> ToULong(const AValue* v, bool& bad) {
    switch (v->m_kind) {
    case AValue::kUInt:
    case AValue::kSInt: return Found(v->m_body.u);
    case AValue::kFloat: return Found(armf::cvtzu_x(v->m_body.d));
    case AValue::kString:
        if (!CString(v)) break;
        return Found(g::StringToULong(CString(v)));
    default: break;
    }
    bad = true;
    return None<u64>();
}
// pair<unsigned char, bool>: ((u32)x | 0x100) & 0xffff in w0. The double case converts with fcvtzs w,
// so the bool byte is bits 8-15 of the int, or 1 (a guest quirk).
ParserResult<u8> ToUTiny(const AValue* v, bool& bad) {
    auto packed = [](u32 x) {
        u32 r = (x | 0x100) & 0xffff;
        return ParserResult<u8>{(u8)r, (u8)(r >> 8)};
    };
    switch (v->m_kind) {
    case AValue::kUInt:
    case AValue::kSInt: return packed(Low8(v));
    case AValue::kFloat: return packed((u32)armf::cvtzs_w(v->m_body.d));
    case AValue::kString:
        if (!CString(v)) break;
        return packed(g::StringToUTiny(CString(v)));
    default: break;
    }
    bad = true;
    return None<u8>();
}
// bool from an unsigned: 0 and 1 are found, anything else isn't.
ParserResult<u8> BoolOf(ParserResult<u32> u) {
    if (!u.found) return None<u8>();
    if (u.value == 0) return Found<u8>(0);
    if (u.value == 1) return Found<u8>(1);
    return None<u8>();
}
ParserResult<const char*> ToString(const AValue* v) {
    if (v && v->m_kind != AValue::kNil && CString(v)) return Found(CString(v));
    return {EmptyString(), 0};
}

// A by-key lookup: AMap::Get_(key); a missing key drops "not found " + key.
const AValue* Lookup(const AMap* map, const char* key) {
    const AValue* v = g::AMapGet(map, key);
    if (!v) DropMessage(g::kNotFound, key);
    return v;
}
template <typename T, typename Conv>
ParserResult<T> ByKey(const AMap* map, const char* key, int line, Conv conv) {
    if (!map) g::Assert(g::kParameterParserCpp, line, g::kApObjectIsNull);
    const AValue* v = Lookup(map, key);
    if (!v) return None<T>();
    bool bad = false;
    ParserResult<T> r = conv(v, bad);
    if (bad) DropMessage(g::kNotMatch, key);
    return r;
}
template <typename T, typename Conv>
ParserResult<T> ByHash(const AMap* map, u32 hash, int line, Conv conv) {
    if (!map) g::Assert(g::kParameterParserCpp, line, g::kApObjectIsNull);
    const AValue* v = ParserValueEntry(map, hash);
    if (!v) return None<T>();
    bool bad = false;
    return conv(v, bad);
}

}  // namespace

const AValue* CParameterParser::GetParserValue(const AMap* map, u32 hash) {
    if (!map) g::Assert(g::kParameterParserH, 0x2c, g::kApParserIsNull);
    if (hash == 0) return nullptr;
    const KeyHashes* k = KeyHashes::current();
    if (k && k->covers(map)) {
        for (u32 i = 0; i < k->count(); i++)
            if (k->hash(i) == hash) return &map->m_pairs[i].value;
        return nullptr;
    }
    for (u32 i = 0; i < map->m_count; i++) {
        const ASON_Pair& p = map->m_pairs[i];
        if (p.key.m_kind == AValue::kString && hash::CHash32::OfCString(p.key.m_body.str.m_cstr) == hash) return &p.value;
    }
    return nullptr;
}

double CParameterParser::GetValue(const AValue* v) {
    if (!v) {
        g::Assert(g::kParameterParserCpp, 0x228, g::kApValueIsNull);
        return 0.0;
    }
    switch (v->m_kind) {
    case AValue::kFloat: return v->m_body.d;
    case AValue::kSInt: return (double)v->m_body.s;  // scvtf d
    case AValue::kUInt: return (double)v->m_body.u;  // ucvtf d
    default: return 0.0;
    }
}

// By hash.
ParserResult<const char*> CParameterParser::GetValueString(const AMap* map, u32 hash) {
    if (!map) g::Assert(g::kParameterParserCpp, 0x37, g::kApObjectIsNull);
    return ToString(ParserValueEntry(map, hash));
}
ParserResult<float> CParameterParser::GetValueFloat(const AMap* map, u32 hash) { return ByHash<float>(map, hash, 0xa5, ToFloat); }
ParserResult<s32> CParameterParser::GetValueInt(const AMap* map, u32 hash) { return ByHash<s32>(map, hash, 0xe5, ToInt); }
ParserResult<u32> CParameterParser::GetValueUInt(const AMap* map, u32 hash) {
    return ByHash<u32>(map, hash, 0x125, [](const AValue* v, bool& bad) { return ToUInt(v, bad, true); });
}
ParserResult<s64> CParameterParser::GetValueLong(const AMap* map, u32 hash) { return ByHash<s64>(map, hash, 0x167, ToLong); }
ParserResult<u64> CParameterParser::GetValueULong(const AMap* map, u32 hash) { return ByHash<u64>(map, hash, 0x1a7, ToULong); }
ParserResult<u8> CParameterParser::GetValueBool(const AMap* map, u32 hash) { return BoolOf(GetValueUInt(map, hash)); }
ParserResult<u8> CParameterParser::GetValueUTiny(const AMap* map, u32 hash) { return ByHash<u8>(map, hash, 0x20f, ToUTiny); }

// The game string of `s` (GetValue<std::string>'s inlined constructor: a short string up to 22
// characters, else a block of (n + 16) & ~15 from the STL allocator), and the found flag at +0x18.
namespace {
void MakeStdString(libcxx::pair<String, bool>* out, ParserResult<const char*> r) {
    String& s = out->first;
    std::memset(&s, 0, sizeof s);
    u64 n = std::strlen(r.value);
    char* p;
    if (n < 23) {
        s.r.s.head.size = (u8)(n << 1);
        p = s.r.s.data;
    } else {
        u64 alloc = (n + 16) & ~u64(15);
        p = (char*)g::StlAllocate(alloc, g::kStlStringH, 0x1c);
        if (!p) g::Assert(g::kStlAllocatorH, 0xbe, g::kAllocatedIsNull);
        s.r.l.size = n;
        s.r.l.data = p;
        s.r.l.cap = alloc | 1;
    }
    std::memcpy(p, r.value, n);
    p[n] = 0;
    *(u8*)&out->second = r.found;
}
}  // namespace

void CParameterParser::GetValueStdString(libcxx::pair<String, bool>* out, const AMap* map, u32 hash) {
    MakeStdString(out, GetValueString(map, hash));
}

// By key.
ParserResult<const char*> CParameterParser::GetValueString(const AMap* map, const char* key) {
    if (!map) g::Assert(g::kParameterParserCpp, 0x12, g::kApObjectIsNull);
    const AValue* v = Lookup(map, key);
    return ToString(v);
}
ParserResult<float> CParameterParser::GetValueFloat(const AMap* map, const char* key) { return ByKey<float>(map, key, 0x7d, ToFloat); }
ParserResult<s32> CParameterParser::GetValueInt(const AMap* map, const char* key) { return ByKey<s32>(map, key, 0xbe, ToInt); }
ParserResult<u32> CParameterParser::GetValueUInt(const AMap* map, const char* key) {
    return ByKey<u32>(map, key, 0xfe, [](const AValue* v, bool& bad) { return ToUInt(v, bad, false); });
}
ParserResult<s64> CParameterParser::GetValueLong(const AMap* map, const char* key) { return ByKey<s64>(map, key, 0x140, ToLong); }
ParserResult<u64> CParameterParser::GetValueULong(const AMap* map, const char* key) { return ByKey<u64>(map, key, 0x180, ToULong); }
ParserResult<u8> CParameterParser::GetValueBool(const AMap* map, const char* key) {
    ParserResult<u32> u = GetValueUInt(map, key);
    if (!u.found) return None<u8>();
    ParserResult<u8> b = BoolOf(u);
    if (!b.found) DropMessage(g::kNotMatch, key);
    return b;
}
ParserResult<u8> CParameterParser::GetValueUTiny(const AMap* map, const char* key) { return ByKey<u8>(map, key, 0x1e8, ToUTiny); }
void CParameterParser::GetValueStdString(libcxx::pair<String, bool>* out, const AMap* map, const char* key) {
    MakeStdString(out, GetValueString(map, key));
}

// ---- binding: hand-written HostFns (the pair results), each through the live check ----

namespace {

template <typename T>
u64 Bits(T v) {
    u64 b = 0;
    std::memcpy(&b, &v, sizeof(T));
    return b;
}
template <typename T>
ParserResult<T> FromRegs(Regs g) {
    ParserResult<T> r;
    if constexpr (sizeof(T) == 8) {
        std::memcpy(&r.value, &g.x0, 8);
        r.found = (u8)g.x1;
    } else {
        std::memcpy(&r.value, &g.x0, sizeof(T));
        r.found = (u8)(g.x0 >> (8 * sizeof(T)));
    }
    return r;
}

template <typename K>
u64 ArgOf(K k) {
    if constexpr (std::is_pointer_v<K>) return (u64)k;
    else return (u64)(u32)k;
}

// A getter's checked entry: the native, or (every n-th call, --live-check params) the native and the
// original compared.
template <Fn& F, typename T, typename K, ParserResult<T> (*Impl)(const AMap*, K)>
ParserResult<T> Entry(const AMap* map, K key) {
    if (__builtin_expect(!fam().due(F), 1)) return Impl(map, key);
    return FromRegs<T>(check_pure(F, [&] { return ToRegs(Impl(map, key)); }, {(u64)map, ArgOf(key)}, sizeof(T) == 8));
}
template <Fn& F, typename T, typename K, ParserResult<T> (*Impl)(const AMap*, K)>
void Host(Cpu& c) {
    Regs r = ToRegs(Entry<F, T, K, Impl>((const AMap*)c.x(0), (K)c.x(1)));
    c.set_x(0, r.x0);
    if constexpr (sizeof(T) == 8) c.set_x(1, r.x1);
}

#define PARSER_SYM(name, type) "_ZN16CParameterParser" name "EPKN4Aska4ASON6AValue4AMapE" type
#define PARSER_GETVALUE_T(t, type) "_ZN16CParameterParser8GetValueI" t "EENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapE" type

using H = u32;
using Key = const char*;
// The members as plain function pointers (the overloads chosen by their key type).
constexpr ParserResult<const char*> (*kStringH)(const AMap*, H) = &CParameterParser::GetValueString;
constexpr ParserResult<float> (*kFloatH)(const AMap*, H) = &CParameterParser::GetValueFloat;
constexpr ParserResult<s32> (*kIntH)(const AMap*, H) = &CParameterParser::GetValueInt;
constexpr ParserResult<u32> (*kUIntH)(const AMap*, H) = &CParameterParser::GetValueUInt;
constexpr ParserResult<s64> (*kLongH)(const AMap*, H) = &CParameterParser::GetValueLong;
constexpr ParserResult<u64> (*kULongH)(const AMap*, H) = &CParameterParser::GetValueULong;
constexpr ParserResult<u8> (*kBoolH)(const AMap*, H) = &CParameterParser::GetValueBool;
constexpr ParserResult<u8> (*kUTinyH)(const AMap*, H) = &CParameterParser::GetValueUTiny;
constexpr ParserResult<const char*> (*kStringK)(const AMap*, Key) = &CParameterParser::GetValueString;
constexpr ParserResult<float> (*kFloatK)(const AMap*, Key) = &CParameterParser::GetValueFloat;
constexpr ParserResult<s32> (*kIntK)(const AMap*, Key) = &CParameterParser::GetValueInt;
constexpr ParserResult<u32> (*kUIntK)(const AMap*, Key) = &CParameterParser::GetValueUInt;
constexpr ParserResult<s64> (*kLongK)(const AMap*, Key) = &CParameterParser::GetValueLong;
constexpr ParserResult<u64> (*kULongK)(const AMap*, Key) = &CParameterParser::GetValueULong;
constexpr ParserResult<u8> (*kBoolK)(const AMap*, Key) = &CParameterParser::GetValueBool;
constexpr ParserResult<u8> (*kUTinyK)(const AMap*, Key) = &CParameterParser::GetValueUTiny;

// One guest symbol bound to a getter: its live-check counters and the HostFn.
#define BIND_GETTER(var, sym, T, K, impl, note)                                         \
    Fn var(fam(), sym);                                                                 \
    NATIVE_FUNCTION_ORIG(sym, (&Host<var, T, K, impl>), "params: " note, &var.orig)

// By hash: CParameterParser::GetValue<T>(map, unsigned) and the typed GetValue*(map, unsigned).
BIND_GETTER(fGetValueStringH, PARSER_SYM("14GetValueString", "j"), const char*, H, kStringH, "CParameterParser::GetValueString(map, hash)");
BIND_GETTER(fGetValueFloatH, PARSER_SYM("13GetValueFloat", "j"), float, H, kFloatH, "CParameterParser::GetValueFloat(map, hash)");
BIND_GETTER(fGetValueIntH, PARSER_SYM("11GetValueInt", "j"), s32, H, kIntH, "CParameterParser::GetValueInt(map, hash)");
BIND_GETTER(fGetValueUIntH, PARSER_SYM("12GetValueUInt", "j"), u32, H, kUIntH, "CParameterParser::GetValueUInt(map, hash)");
BIND_GETTER(fGetValueLongH, PARSER_SYM("12GetValueLong", "j"), s64, H, kLongH, "CParameterParser::GetValueLong(map, hash)");
BIND_GETTER(fGetValueULongH, PARSER_SYM("13GetValueULong", "j"), u64, H, kULongH, "CParameterParser::GetValueULong(map, hash)");
BIND_GETTER(fGetValueBoolH, PARSER_SYM("12GetValueBool", "j"), u8, H, kBoolH, "CParameterParser::GetValueBool(map, hash)");
BIND_GETTER(fGetValueUTinyH, PARSER_SYM("13GetValueUTiny", "j"), u8, H, kUTinyH, "CParameterParser::GetValueUTiny(map, hash)");
BIND_GETTER(fGetValueTFloatH, PARSER_GETVALUE_T("f", "j"), float, H, kFloatH, "CParameterParser::GetValue<float>(map, hash)");
BIND_GETTER(fGetValueTIntH, PARSER_GETVALUE_T("i", "j"), s32, H, kIntH, "CParameterParser::GetValue<int>(map, hash)");
BIND_GETTER(fGetValueTUIntH, PARSER_GETVALUE_T("j", "j"), u32, H, kUIntH, "CParameterParser::GetValue<unsigned int>(map, hash)");
BIND_GETTER(fGetValueTLongH, PARSER_GETVALUE_T("l", "j"), s64, H, kLongH, "CParameterParser::GetValue<long>(map, hash)");
BIND_GETTER(fGetValueTULongH, PARSER_GETVALUE_T("m", "j"), u64, H, kULongH, "CParameterParser::GetValue<unsigned long>(map, hash)");
BIND_GETTER(fGetValueTBoolH, PARSER_GETVALUE_T("b", "j"), u8, H, kBoolH, "CParameterParser::GetValue<bool>(map, hash)");
BIND_GETTER(fGetValueTUTinyH, PARSER_GETVALUE_T("h", "j"), u8, H, kUTinyH, "CParameterParser::GetValue<unsigned char>(map, hash)");
BIND_GETTER(fGetValueTPcH, PARSER_GETVALUE_T("Pc", "j"), const char*, H, kStringH, "CParameterParser::GetValue<char*>(map, hash)");
// By key (the GetValue<T>(map, char const*) of float, int, unsigned, long, unsigned long and char* are
// 4-byte tail branches to the typed getters: left to the guest, they land on these natives).
BIND_GETTER(fGetValueStringK, PARSER_SYM("14GetValueString", "PKc"), const char*, Key, kStringK, "CParameterParser::GetValueString(map, key)");
BIND_GETTER(fGetValueFloatK, PARSER_SYM("13GetValueFloat", "PKc"), float, Key, kFloatK, "CParameterParser::GetValueFloat(map, key)");
BIND_GETTER(fGetValueIntK, PARSER_SYM("11GetValueInt", "PKc"), s32, Key, kIntK, "CParameterParser::GetValueInt(map, key)");
BIND_GETTER(fGetValueUIntK, PARSER_SYM("12GetValueUInt", "PKc"), u32, Key, kUIntK, "CParameterParser::GetValueUInt(map, key)");
BIND_GETTER(fGetValueLongK, PARSER_SYM("12GetValueLong", "PKc"), s64, Key, kLongK, "CParameterParser::GetValueLong(map, key)");
BIND_GETTER(fGetValueULongK, PARSER_SYM("13GetValueULong", "PKc"), u64, Key, kULongK, "CParameterParser::GetValueULong(map, key)");
BIND_GETTER(fGetValueBoolK, PARSER_SYM("12GetValueBool", "PKc"), u8, Key, kBoolK, "CParameterParser::GetValueBool(map, key)");
BIND_GETTER(fGetValueUTinyK, PARSER_SYM("13GetValueUTiny", "PKc"), u8, Key, kUTinyK, "CParameterParser::GetValueUTiny(map, key)");
BIND_GETTER(fGetValueTBoolK, PARSER_GETVALUE_T("b", "PKc"), u8, Key, kBoolK, "CParameterParser::GetValue<bool>(map, key)");
BIND_GETTER(fGetValueTUTinyK, PARSER_GETVALUE_T("h", "PKc"), u8, Key, kUTinyK, "CParameterParser::GetValue<unsigned char>(map, key)");

// GetParserValue: a pointer in x0.
Fn fGetParserValue(fam(), PARSER_SYM("14GetParserValue", "j"));
const AValue* ParserValueEntry(const AMap* map, u32 hash) {
    if (__builtin_expect(!fam().due(fGetParserValue), 1)) return CParameterParser::GetParserValue(map, hash);
    return (const AValue*)check_pure(fGetParserValue, [&] { return Regs{(u64)CParameterParser::GetParserValue(map, hash), 0}; },
                                     {(u64)map, (u64)hash}, false)
        .x0;
}
void HostGetParserValue(Cpu& c) { c.set_x(0, (u64)ParserValueEntry((const AMap*)c.x(0), (u32)c.x(1))); }
NATIVE_FUNCTION_ORIG(PARSER_SYM("14GetParserValue", "j"), HostGetParserValue, "params: CParameterParser::GetParserValue", &fGetParserValue.orig);

// GetValue(AValue const*): a double in d0.
Fn fGetValueDouble(fam(), "_ZN16CParameterParser8GetValueEPKN4Aska4ASON6AValueE");
void HostGetValueDouble(Cpu& c) {
    const AValue* v = (const AValue*)c.x(0);
    double d = CParameterParser::GetValue(v);
    if (fam().due(fGetValueDouble)) {
        live::RunBothFamily::Scope scope;
        GuestArgs a;
        a.i((u64)v);
        GuestResult g = guest_call(fGetValueDouble.orig, a);
        u64 nb = Bits(d), gb = g.v0.lo;
        char m[96];
        snprintf(m, sizeof m, "native %#llx guest %#llx", (unsigned long long)nb, (unsigned long long)gb);
        fam().result(fGetValueDouble, nb == gb ? Outcome::Ok : Outcome::Mismatch, m);
    }
    c.set_d(0, d);
}
NATIVE_FUNCTION_ORIG("_ZN16CParameterParser8GetValueEPKN4Aska4ASON6AValueE", HostGetValueDouble, "params: CParameterParser::GetValue(AValue const*)",
                     &fGetValueDouble.orig);

// GetValue<std::string>(map, hash / key): the pair through x8. The check runs the original into a
// private pair and compares the strings' representation and the flag.
template <typename K>
void StdStringChecked(Fn& f, libcxx::pair<String, bool>* out, const AMap* map, K key) {
    CParameterParser::GetValueStdString(out, map, key);
    if (!fam().due(f)) return;
    live::RunBothFamily::Scope scope;
    alignas(16) libcxx::pair<String, bool> mine;
    std::memset(&mine, 0, sizeof mine);
    GuestArgs a;
    a.i((u64)map).i(ArgOf(key)).sret(&mine);
    guest_call(f.orig, a);
    std::string d = diff_strings(out->first, mine.first);
    if (d.empty() && *(u8*)&out->second != *(u8*)&mine.second) d = "the found flag";
    free_copy(mine.first);
    fam().result(f, d.empty() ? Outcome::Ok : Outcome::Mismatch, d);
}
#define STDSTRING_GETVALUE(type) "_ZN16CParameterParser8GetValueINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEEENS1_4pairIT_bEEPKN4Aska4ASON6AValue4AMapE" type
Fn fGetValueStdStringH(fam(), STDSTRING_GETVALUE("j"));
Fn fGetValueStdStringK(fam(), STDSTRING_GETVALUE("PKc"));
void HostStdStringH(Cpu& c) {
    StdStringChecked(fGetValueStdStringH, (libcxx::pair<String, bool>*)c.x(8), (const AMap*)c.x(0), (u32)c.x(1));
}
void HostStdStringK(Cpu& c) {
    StdStringChecked(fGetValueStdStringK, (libcxx::pair<String, bool>*)c.x(8), (const AMap*)c.x(0), (const char*)c.x(1));
}
NATIVE_FUNCTION_ORIG(STDSTRING_GETVALUE("j"), HostStdStringH, "params: CParameterParser::GetValue<std::string>(map, hash)",
                     &fGetValueStdStringH.orig);
NATIVE_FUNCTION_ORIG(STDSTRING_GETVALUE("PKc"), HostStdStringK, "params: CParameterParser::GetValue<std::string>(map, key)",
                     &fGetValueStdStringK.orig);

}  // namespace

// The entries the property natives call (params_parser.h).
template <>
ParserResult<u32> GetValueByHash<u32>(const AMap* m, u32 h) { return Entry<fGetValueTUIntH, u32, H, kUIntH>(m, h); }
template <>
ParserResult<s32> GetValueByHash<s32>(const AMap* m, u32 h) { return Entry<fGetValueTIntH, s32, H, kIntH>(m, h); }
template <>
ParserResult<float> GetValueByHash<float>(const AMap* m, u32 h) { return Entry<fGetValueTFloatH, float, H, kFloatH>(m, h); }
template <>
ParserResult<u8> GetValueByHash<u8>(const AMap* m, u32 h) { return Entry<fGetValueTUTinyH, u8, H, kUTinyH>(m, h); }
template <>
ParserResult<u64> GetValueByHash<u64>(const AMap* m, u32 h) { return Entry<fGetValueTULongH, u64, H, kULongH>(m, h); }
// (bool: GetValue<bool>'s pair<bool, bool>)
template <>
ParserResult<bool> GetValueByHash<bool>(const AMap* m, u32 h) {
    ParserResult<u8> r = Entry<fGetValueTBoolH, u8, H, kBoolH>(m, h);
    return {r.value != 0, r.found};
}
void GetValueStdStringByHash(libcxx::pair<String, bool>* out, const AMap* map, u32 hash) {
    StdStringChecked(fGetValueStdStringH, out, map, hash);
}

}  // namespace soa::native::params
