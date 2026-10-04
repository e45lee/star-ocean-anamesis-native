// Layout tests for params_layout.h (port/PLAN.md task 6, types first): the recovered classes read against
// objects the guest's own code built. A private CParameterPlayer is constructed and deserialized by the
// guest from a msgpack document the test writes; private properties of the other value types are
// deserialized by their guest instantiations; the running game's CocosCommonResource parameter is walked
// read-only. Fields read through the layout classes are compared with the input, with the guest's
// accessors (NameHash, CompareName, pParameter, rParameter, GetParserValue, pGetRoot) and with the
// vtables' symbols. No natives here: in --selftest every t.call reaches the guest code.
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "native/common/test.h"
#include "native/params/params_layout.h"

using namespace soa;
using namespace soa::native::params;
using soa::native::data_formats::ASON;
using soa::native::data_formats::ASON_Pair;

namespace {

template <typename T>
struct Obj {
    alignas(16) unsigned char raw[sizeof(T) + 0x40];
    Obj() { std::memset(raw, 0xa5, sizeof raw); }
    T* get() { return reinterpret_cast<T*>(raw); }
    u64 addr() { return (u64)raw; }
};

u64 vtable_of(TestContext& t, const char* ztv) { return t.sym(ztv) + 0x10; }
u64 slot(const void* vtable, int i) { return reinterpret_cast<const u64*>(vtable)[i]; }

// A msgpack writer for the inputs (only what these tests need).
struct Mp {
    std::vector<u8> b;
    Mp& raw(std::initializer_list<u8> v) { b.insert(b.end(), v); return *this; }
    Mp& be(u64 v, int n) { for (int i = n - 1; i >= 0; i--) b.push_back((u8)(v >> (8 * i))); return *this; }
    Mp& map(u32 n) { return raw({(u8)(0x80 | n)}); }
    Mp& str(const std::string& s) {
        if (s.size() < 32) raw({(u8)(0xa0 | s.size())});
        else raw({0xd9, (u8)s.size()});
        b.insert(b.end(), s.begin(), s.end());
        return *this;
    }
    Mp& uint(u64 v) { return v < 128 ? raw({(u8)v}) : raw({0xcf}).be(v, 8); }
    Mp& sint(s64 v) { return v >= -32 ? raw({(u8)(s8)v}) : raw({0xd3}).be((u64)v, 8); }
    Mp& f32(float f) { u32 u; std::memcpy(&u, &f, 4); return raw({0xca}).be(u, 4); }
    Mp& boolean(bool v) { return raw({(u8)(v ? 0xc3 : 0xc2)}); }
};

// A guest ASON (Init with C strings kept: the parser's hash lookups need them).
struct GuestAson {
    TestContext& t;
    alignas(16) u8 raw[sizeof(ASON) + 0x40] = {};
    explicit GuestAson(TestContext& tc) : t(tc) {
        t.call("_ZN4Aska4ASONC1Ev", {(u64)raw});
        s64 r = (s64)t.call("_ZN4Aska4ASON4InitEjb", {(u64)raw, 0x4000, 1});
        if (r != 0) t.fail("ASON::Init = %lld", (long long)r);
    }
    ~GuestAson() { t.call("_ZN4Aska4ASOND1Ev", {(u64)raw}); }
    ASON* get() { return reinterpret_cast<ASON*>(raw); }
    const AMap* parse(const std::vector<u8>& in) {
        s64 n = (s64)t.call("_ZN4Aska4ASON17DeserializeBinaryEPKvm", {(u64)raw, (u64)in.data(), (u64)in.size()});
        if (n != (s64)in.size() || get()->m_root.m_kind != AValue::kMap) {
            t.fail("DeserializeBinary = %lld", (long long)n);
            return nullptr;
        }
        return &get()->m_root.m_body.map;
    }
};

// The pair of `map` whose key is the string `key` (host walk), or null.
const ASON_Pair* find_pair(const AMap* map, const char* key) {
    for (u32 i = 0; i < map->m_count; i++) {
        const ASON_Pair& p = map->m_pairs[i];
        if (p.key.m_kind == AValue::kString && p.key.m_body.str.m_cstr && std::strcmp(p.key.m_body.str.m_cstr, key) == 0)
            return &p;
    }
    return nullptr;
}

// Framework::CHash32(char const*) by the guest: the hash the properties compare.
u32 guest_hash(TestContext& t, const char* s) {
    alignas(16) CHash32Ref h{};
    t.call("_ZN9Framework7CHash32C1EPKc", {(u64)&h, (u64)s});
    return h.m_hash;
}

// A string property's value decrypted host-side (each byte ^ N).
template <u32 N>
std::string decrypt(const CParameterPropertyString<N>& p) {
    std::string s(p.m_value.data(), p.m_value.size());
    for (char& c : s) c = char(c ^ CParameterPropertyBase<N>::kCryptKey);
    return s;
}

// The properties' common checks: the name hash, the guest's NameHash / CompareName on it.
template <u32 N>
void check_name(TestContext& t, const CParameterPropertyBase<N>& b, const char* name) {
    u32 h = guest_hash(t, name);
    t.expect_eq(b.m_named, true, "m_named after Initialize");
    t.expect_eq(b.m_name.vtable, (const void*)vtable_of(t, "_ZTVN9Framework7CHash32E"), "m_name: a CHash32");
    t.expect_eq(b.m_name.m_hash, h, "m_name.m_hash = CHash32(name)");
    t.expect_eq((u32)guest_call(slot(b.base.vtable, IParameterProperty::kSlotNameHash), {(u64)&b}), h,
                "NameHash (slot 2) = m_name");
    t.expect_eq(guest_call(slot(b.base.vtable, IParameterProperty::kSlotCompareNameStr), {(u64)&b, (u64)name}) & 1,
                (u64)1, "CompareName(char const*) (slot 0)");
    t.expect_eq(guest_call(slot(b.base.vtable, IParameterProperty::kSlotCompareNameHash), {(u64)&b, (u64)h}) & 1,
                (u64)1, "CompareName(unsigned) (slot 1)");
    t.expect_eq(guest_call(slot(b.base.vtable, IParameterProperty::kSlotCompareNameHash), {(u64)&b, (u64)(h ^ 1)}) & 1,
                (u64)0, "CompareName(other hash)");
}

}  // namespace

// A private CParameterPlayer: the guest constructor, then CParameterPlayer::Deserialize of a document with
// a "Player" map; every property read through the layout against the input, the vtables against the
// symbols, the property list against AddProperty's order; the parser and CParameterBase's lookups.
NATIVE_TEST("params/layout-player") {
    static Obj<CParameterPlayer> o;
    std::memset(o.raw, 0xa5, sizeof o.raw);
    CParameterPlayer* p = o.get();
    t.call("_ZN16CParameterPlayerC1Ev", {o.addr()});
    CParameterPlayerElement& e = p->m_element;

    // The constructor: vtables of the parameter, the element and each property; empty list.
    t.expect_eq(p->base.vtable, (const void*)vtable_of(t, "_ZTV16CParameterPlayer"), "CParameterPlayer vtable");
    t.expect_eq(e.base.vtable, (const void*)vtable_of(t, "_ZTV23CParameterPlayerElement"), "element vtable");
    t.expect_eq(e.base.m_first, (IParameterProperty*)nullptr, "m_first = 0 before Initialize");
    t.expect_eq(p->m_valid, false, "m_valid = 0");
    t.expect_eq(e.m_id.base.base.vtable, (const void*)vtable_of(t, "_ZTV23CParameterPropertyValueIjLj36E18CPropertyConverterE"), "Id vtable");
    t.expect_eq(e.m_token.base.base.vtable, (const void*)vtable_of(t, "_ZTV23CParameterPropertyValueIjLj37E18CPropertyConverterE"), "Token vtable");
    t.expect_eq(e.m_role.base.base.vtable, (const void*)vtable_of(t, "_ZTV23CParameterPropertyValueIiLj39E18CPropertyConverterE"), "Role vtable");
    const char* kZtvName =
        "_ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_"
        "22CSTLStringAllocatorInfEEEEELj42EE";
    t.expect_eq(e.m_name.base.base.vtable, (const void*)vtable_of(t, kZtvName), "Name vtable");
    t.expect_eq(e.m_id.base.base.m_next, (IParameterProperty*)nullptr, "property m_next = 0");
    t.expect_eq(e.m_id.base.m_named, false, "m_named = 0 before Initialize");
    t.expect_eq(e.m_id.base.m_name.m_hash, (u32)0, "CHash32() = 0");
    t.expect_eq(e.m_name.m_value.size(), (u64)0, "Name: empty string");

    // The vtables' slots: the IParameterProperty interface on an instantiation, CParameterBase's on the
    // parameter, CParameterElementBase's on the element.
    const void* vt = e.m_id.base.base.vtable;
    t.expect_eq(slot(vt, 0), t.sym("_ZNK22CParameterPropertyBaseILj36EE11CompareNameEPKc"), "slot 0 CompareName(char const*)");
    t.expect_eq(slot(vt, 1), t.sym("_ZNK22CParameterPropertyBaseILj36EE11CompareNameEj"), "slot 1 CompareName(unsigned)");
    t.expect_eq(slot(vt, 2), t.sym("_ZNK22CParameterPropertyBaseILj36EE8NameHashEv"), "slot 2 NameHash");
    t.expect_eq(slot(vt, 3), t.sym("_ZN23CParameterPropertyValueIjLj36E18CPropertyConverterE11DeserializeEPKN4Aska4ASON6AValue4AMapE"), "slot 3 Deserialize");
    t.expect_eq(slot(vt, 4), t.sym("_ZNK23CParameterPropertyValueIjLj36E18CPropertyConverterE6PrintCEv"), "slot 4 PrintC");
    const void* pvt = p->base.vtable;
    t.expect_eq(slot(pvt, CParameterBase::kSlotInitialize), t.sym("_ZN16CParameterPlayer10InitializeEv"), "Player slot 2 Initialize");
    t.expect_eq(slot(pvt, CParameterBase::kSlotParseName), t.sym("_ZNK16CParameterPlayer10pParseNameEv"), "Player slot 3 pParseName");
    t.expect_eq(slot(pvt, CParameterBase::kSlotDeserialize), t.sym("_ZN16CParameterPlayer11DeserializeEPKN4Aska4ASON6AValue4AMapE"), "Player slot 4 Deserialize");
    t.expect_eq(slot(pvt, CParameterBase::kSlotReleaseParameter), t.sym("_ZN14CParameterBase16ReleaseParameterEPKc"), "Player slot 5 ReleaseParameter");
    t.expect_eq(slot(pvt, CParameterBase::kSlotGetRoot), t.sym("_ZNK14CParameterBase8pGetRootEPKN4Aska4ASON6AValue4AMapE"), "Player slot 6 pGetRoot");
    const void* evt = e.base.vtable;
    t.expect_eq(slot(evt, CParameterElementBase::kSlotInitialize), t.sym("_ZN23CParameterPlayerElement10InitializeEv"), "element slot 0 Initialize");
    t.expect_eq(slot(evt, CParameterElementBase::kSlotDeserialize), t.sym("_ZN21CParameterElementBase11DeserializeEPKN4Aska4ASON6AValue4AMapE"), "element slot 1 Deserialize");
    const char* parse_name = (const char*)guest_call(slot(pvt, CParameterBase::kSlotParseName), {o.addr()});
    t.expect_eq(std::string(parse_name ? parse_name : ""), std::string("Player"), "pParseName");

    // The document: {"Other": 1, "Player": {...7 keys, an unknown one...}}. A long name (a heap string).
    const std::string name = "LOCAL player name, long enough";
    Mp m;
    m.map(2).str("Other").uint(1).str("Player").map(8)
        .str("Id").uint(123456)
        .str("Token").uint(0xdeadbeef)
        .str("Level").uint(77)
        .str("Role").sint(-5)
        .str("Unknown").uint(9)
        .str("PersonID").uint(4242)
        .str("Weapon").uint(31)
        .str("Name").str(name);
    GuestAson a(t);
    const AMap* root = a.parse(m.b);
    if (!root) return;
    const ASON_Pair* player = find_pair(root, "Player");
    if (!t.expect_eq(player != nullptr, true, "the Player pair")) return;

    // CParameterBase's lookups on the root map.
    t.expect_eq(guest_call(slot(pvt, CParameterBase::kSlotGetRoot), {o.addr(), (u64)root}), (u64)&player->value,
                "pGetRoot = &pair(\"Player\").value");
    t.expect_eq(t.call("_ZN14CParameterBase4FindEPKN4Aska4ASON6AValue4AMapE", {o.addr(), (u64)root}) & 1, (u64)1, "Find");
    // The parser's hash lookup: &pair.value of the key whose CHash32 matches.
    const AMap* pm = &player->value.m_body.map;
    const ASON_Pair* level = find_pair(pm, "Level");
    t.expect_eq(t.call("_ZN16CParameterParser14GetParserValueEPKN4Aska4ASON6AValue4AMapEj", {(u64)pm, guest_hash(t, "Level")}),
                (u64)&level->value, "GetParserValue(hash(\"Level\")) = &pair.value");
    t.expect_eq(t.call("_ZN16CParameterParser14GetParserValueEPKN4Aska4ASON6AValue4AMapEj", {(u64)pm, guest_hash(t, "Nope")}),
                (u64)0, "GetParserValue(absent) = 0");

    u64 ok = t.call("_ZN16CParameterPlayer11DeserializeEPKN4Aska4ASON6AValue4AMapE", {o.addr(), (u64)root});
    t.expect_eq(ok & 1, (u64)1, "Deserialize");
    t.expect_eq(p->m_valid, true, "m_valid after Deserialize");
    t.expect_eq(t.call("_ZNK16CParameterPlayer10pParameterEv", {o.addr()}), (u64)&e, "pParameter = &m_element");

    // The values, through the layout.
    t.expect_eq(e.m_id.m_value, (u32)123456, "Id");
    t.expect_eq(e.m_token.m_value, (u32)0xdeadbeef, "Token");
    t.expect_eq(e.m_level.m_value, (u32)77, "Level");
    t.expect_eq(e.m_role.m_value, (s32)-5, "Role (int)");
    t.expect_eq(e.m_personId.m_value, (u32)4242, "PersonID");
    t.expect_eq(e.m_weapon.m_value, (u32)31, "Weapon");
    t.expect_eq(e.m_name.m_value.is_long(), true, "Name: a long string");
    t.expect_eq(decrypt(e.m_name), name, "Name ^ 42 = the input");
    t.expect_eq(std::memcmp(e.m_name.m_value.data(), name.data(), 1) != 0, true, "Name stored encrypted");
    // The names and the guest's name accessors.
    check_name(t, e.m_id.base, "Id");
    check_name(t, e.m_token.base, "Token");
    check_name(t, e.m_level.base, "Level");
    check_name(t, e.m_role.base, "Role");
    check_name(t, e.m_personId.base, "PersonID");
    check_name(t, e.m_weapon.base, "Weapon");
    check_name(t, e.m_name.base, "Name");

    // The list: AddProperty's order (Initialize's), then the end.
    const IParameterProperty* want[] = {&e.m_id.base.base, &e.m_token.base.base, &e.m_level.base.base, &e.m_role.base.base,
                                        &e.m_personId.base.base, &e.m_weapon.base.base, &e.m_name.base.base};
    const IParameterProperty* q = e.base.m_first;
    for (const IParameterProperty* w : want) {
        t.expect_eq(q, w, "property list order");
        if (!q) break;
        q = q->m_next;
    }
    t.expect_eq(q, (const IParameterProperty*)nullptr, "list end");

    // The AddProperty quirk: a second Initialize re-adds the last property, which isn't compared on the way,
    // so it is linked to itself; the defaults are written again (Token -1), the string isn't reset.
    t.call("_ZN23CParameterPlayerElement10InitializeEv", {(u64)&e});
    t.expect_eq(e.m_name.base.base.m_next, (IParameterProperty*)&e.m_name, "second Initialize: last->m_next = last");
    t.expect_eq(e.m_id.base.base.m_next, (IParameterProperty*)&e.m_token, "second Initialize: the others unchanged");
    t.expect_eq(e.m_token.m_value, (u32)0xffffffff, "Token default -1");
    t.expect_eq(e.m_id.m_value, (u32)0, "Id default 0");
    t.expect_eq(decrypt(e.m_name), name, "Name kept by Initialize");
    e.m_name.base.base.m_next = nullptr;  // undo the self-link (the destructor doesn't walk the list anyway)

    t.call("_ZN16CParameterPlayerD1Ev", {o.addr()});  // frees the long name
}

// Private properties of the other value types (float, bool, u8, u64, the radian converter): set up as
// their elements' inlined constructors and Initialize do (vtable, m_next, the name), deserialized by the
// guest instantiation, read through CParameterPropertyValue<T, N, Conv>::m_value.
NATIVE_TEST("params/layout-property-values") {
    Mp m;
    m.map(6).str("f").f32(1.5f).str("b").boolean(true).str("u8").uint(200).str("u64").uint(0x123456789aull)
        .str("rad").f32(90.0f).str("i").sint(-7);
    GuestAson a(t);
    const AMap* map = a.parse(m.b);
    if (!map) return;

    auto setup = [&](auto& prop, const char* ztv, const char* key) {
        std::memset((void*)&prop, 0xa5, sizeof prop);
        prop.base.base.vtable = (const void*)vtable_of(t, ztv);
        prop.base.base.m_next = nullptr;
        prop.base.m_named = true;
        t.call("_ZN9Framework7CHash32C1EPKc", {(u64)&prop.base.m_name, (u64)key});
        t.expect_eq((u32)guest_call(slot(prop.base.base.vtable, IParameterProperty::kSlotNameHash), {(u64)&prop}),
                    prop.base.m_name.m_hash, "NameHash = m_name");
        return guest_call(slot(prop.base.base.vtable, IParameterProperty::kSlotDeserialize), {(u64)&prop, (u64)map}) & 1;
    };
    auto tail_untouched = [&](const auto& prop, u64 n) {
        const u8* b = reinterpret_cast<const u8*>(&prop);
        bool same = true;
        for (u64 i = 0x28 + n; i < sizeof prop; i++) same &= b[i] == 0xa5;
        return same;
    };

    static CParameterPropertyValueF32_96 pf;
    t.expect_eq(setup(pf, "_ZTV23CParameterPropertyValueIfLj96E18CPropertyConverterE", "f"), (u64)1, "float Deserialize");
    t.expect_eq(pf.m_value, 1.5f, "float m_value");
    t.expect_eq(tail_untouched(pf, 4), true, "float: 4 bytes written");

    static CParameterPropertyValueBool96 pb;
    t.expect_eq(setup(pb, "_ZTV23CParameterPropertyValueIbLj96E18CPropertyConverterE", "b"), (u64)1, "bool Deserialize");
    t.expect_eq(reinterpret_cast<const u8*>(&pb)[0x28], (u8)1, "bool m_value");
    t.expect_eq(tail_untouched(pb, 1), true, "bool: 1 byte written");

    static CParameterPropertyValueU8_186 pu8;
    t.expect_eq(setup(pu8, "_ZTV23CParameterPropertyValueIhLj186E18CPropertyConverterE", "u8"), (u64)1, "u8 Deserialize");
    t.expect_eq(pu8.m_value, (u8)200, "u8 m_value");
    t.expect_eq(tail_untouched(pu8, 1), true, "u8: 1 byte written");

    static CParameterPropertyValueU64_103 pu64;
    t.expect_eq(setup(pu64, "_ZTV23CParameterPropertyValueImLj103E18CPropertyConverterE", "u64"), (u64)1, "u64 Deserialize");
    t.expect_eq(pu64.m_value, (u64)0x123456789aull, "u64 m_value");

    static CParameterPropertyValueRad118 prad;
    t.expect_eq(setup(prad, "_ZTV23CParameterPropertyValueIfLj118E24CPropertyConverterRadianE", "rad"), (u64)1,
                "radian Deserialize");
    volatile float pi = 3.14159274f, d180 = 180.0f;  // the guest's constants: (v * pi) / 180, two roundings
    float want = (90.0f * pi) / d180;
    t.expect_eq(prad.m_value, want, "radian m_value = v * pi / 180");

    // A missing key leaves the value alone and returns 0.
    static CParameterPropertyValueS32_39 pmiss;
    t.expect_eq(setup(pmiss, "_ZTV23CParameterPropertyValueIiLj39E18CPropertyConverterE", "absent"), (u64)0,
                "missing key: Deserialize = 0");
    t.expect_eq(tail_untouched(pmiss, 0), true, "missing key: value untouched");
    static CParameterPropertyValueS32_39 pi32;
    t.expect_eq(setup(pi32, "_ZTV23CParameterPropertyValueIiLj39E18CPropertyConverterE", "i"), (u64)1, "int Deserialize");
    t.expect_eq(pi32.m_value, (s32)-7, "int m_value");
}

// The running game's CocosCommonResource parameter (read-only): the map's nodes, each element's property
// list, names and decrypted strings, through the layout; the guest's rParameter / pParseName / NameHash.
NATIVE_TEST("params/layout-live-cocos-common-resource") {
    u64 pmgr = *reinterpret_cast<const u64*>(t.sym("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE"));
    if (!t.expect_eq(pmgr != 0, true, "CParameterManager instance")) return;
    auto* ccr = reinterpret_cast<const CParameterCocosCommonResource*>(
        t.call("_ZNK17CParameterManager29pParameterCocosCommonResourceEv", {pmgr}));
    if (!t.expect_eq(ccr != nullptr, true, "pParameterCocosCommonResource")) return;
    t.expect_eq(ccr->base.vtable, (const void*)vtable_of(t, "_ZTV29CParameterCocosCommonResource"), "vtable");
    t.expect_eq(t.call("_ZNK29CParameterCocosCommonResource10rParameterEv", {(u64)ccr}), (u64)&ccr->m_resources,
                "rParameter = &m_resources");
    const char* pn = (const char*)guest_call(slot(ccr->base.vtable, CParameterBase::kSlotParseName), {(u64)ccr});
    t.expect_eq(std::string(pn ? pn : ""), std::string("CocosCommonResource"), "pParseName");
    const auto& mp = ccr->m_resources;
    t.expect_eq(mp.max_load_factor, 1.0f, "max_load_factor");
    if (mp.size == 0) {
        std::fprintf(stderr, "    params/layout-live-cocos-common-resource: the map is empty at this point (nothing to walk)\n");
        return;
    }
    const u64 evt = vtable_of(t, "_ZTV36CParameterCocosCommonResourceElement");
    u64 n = 0, key_is_pp = 0;
    for (auto* node = mp.first; node && n < 100000; node = node->next, n++) {
        const CParameterCocosCommonResourceElement& el = node->value.second;
        if (!t.expect_eq((u64)el.base.vtable, evt, "element vtable")) return;
        t.expect_eq(el.base.m_first, (IParameterProperty*)&el.m_processingPriority, "m_first");
        t.expect_eq(el.m_processingPriority.base.base.m_next, (IParameterProperty*)&el.m_destinationName, "list 1");
        t.expect_eq(el.m_destinationName.base.base.m_next, (IParameterProperty*)&el.m_sourceName, "list 2");
        t.expect_eq(el.m_sourceName.base.base.m_next, (IParameterProperty*)nullptr, "list end");
        if (n < 4) {
            check_name(t, el.m_processingPriority.base, "processing_priority");
            check_name(t, el.m_destinationName.base, "distnation_name");
            check_name(t, el.m_sourceName.base, "souce_name");
        }
        std::string key(node->value.first.data(), node->value.first.size());
        // DeserializeParameter keys each element by its "processing_priority" string (the map's find /
        // __construct_node take GetValue<char*>(map, "processing_priority")).
        key_is_pp += key == decrypt(el.m_processingPriority);
    }
    t.expect_eq(n, mp.size, "node count = size");
    std::fprintf(stderr, "    params/layout-live-cocos-common-resource: %llu elements walked\n", (unsigned long long)n);
    t.expect_eq(key_is_pp, n, "the map key = the decrypted processing_priority");
}
