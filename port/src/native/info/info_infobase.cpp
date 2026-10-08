// InfoBase::DeserializeChild (info_layout.h; port/decomp/info/person_status.c): the walk every info
// object's deserialization goes through. Live check (family `info`): the original runs again on the same
// object and map after the native (deserializing the same map twice gives the same values), and every
// property's bytes (its value, or its string by content) must be what the native left.
#include <cstring>
#include <vector>

#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/data_formats/data_formats_layout.h"
#include "native/hash/hash_layout.h"
#include "native/info/gen/info_addresses.h"
#include "native/info/info_family.h"
#include "native/info/info_guest.h"
#include "native/info/info_layout.h"
#include "native/params/gen/params_addresses.h"
#include "native/params/params_layout.h"
#include <unordered_set>

namespace soa::native::info {

namespace {

using data_formats::AMap;
using data_formats::AValue;

// lower_bound(key) (the end node when absent).
const PropertyNode* find(const PropertyMap& m, u32 key) {
    auto* end = reinterpret_cast<const PropertyNode*>(&m.root);
    const PropertyNode* result = end;
    for (auto* nd = reinterpret_cast<const PropertyNode*>(m.root); nd;) {
        if (!(nd->value.first < key)) {
            result = nd;
            nd = nd->left;
        } else {
            nd = nd->right;
        }
    }
    if (result != end && key < result->value.first) return end;
    return result;
}

}  // namespace

bool InfoBase::DeserializeArray(const void*) { return false; }

bool InfoBase::DeserializeChild(const void* map_) {
    const AMap* map = reinterpret_cast<const AMap*>(map_);
    u32 count;
    if (!map) {
        g::Assert(g::kInfoBaseH, 0x86, params::g::kApParserIsNull);
        count = 0;  // (the guest reads address 8 here: a crash)
    } else {
        count = map->m_count;
    }
    auto* pend = reinterpret_cast<const PropertyNode*>(&m_properties.root);
    auto* cend = reinterpret_cast<const PropertyNode*>(&m_children.root);
    for (u32 i = 0; i < count; i++) {
        const data_formats::ASON_Pair& pair = map->m_pairs[i];
        u32 h = hash::CHash32::OfCString(pair.key.m_body.str.m_cstr);
        if (m_properties.root) {
            const PropertyNode* n = find(m_properties, h);
            if (n != pend) g::vcall(n->value.second, params::IParameterProperty::kSlotDeserialize, {(u64)map});
        }
        if (m_children.root) {
            const PropertyNode* n = find(m_children, h);
            if (n != cend) {
                u32 kind = pair.value.m_kind;
                if (kind == AValue::kArray) g::vcall(n->value.second, kSlotDeserializeArray, {(u64)&pair.value.m_body});
                else if (kind == AValue::kMap) g::vcall(n->value.second, kSlotDeserializeChild, {(u64)&pair.value.m_body});
            }
        }
    }
    return true;
}

namespace {

Fn f_child(fam(), "_ZN8InfoBase16DeserializeChildEPKN4Aska4ASON6AValue4AMapE");

// The string properties' vtables (params' generated list of the instantiations).
bool is_string_property(u64 vt) {
    static const std::unordered_set<u64>* set = [] {
        auto* s = new std::unordered_set<u64>();
#define INFO_STRING_VT(N, SYM, CRYPT, ZTV) s->insert(g::sym(ZTV) + 16);
#include "native/params/gen/params_instantiations.inc"
        PARAMS_STRINGS(INFO_STRING_VT)
#undef INFO_STRING_VT
        return s;
    }();
    return set->count(vt) != 0;
}

// Every property's state: its bytes, a string by content.
std::vector<u8> props_state(const InfoBase* o) {
    std::vector<u8> out;
    const libcxx::tree_node_base* end = reinterpret_cast<const libcxx::tree_node_base*>(&o->m_properties.root);
    for (auto* n = reinterpret_cast<const libcxx::tree_node_base*>(o->m_properties.begin_node); n != end;) {
        auto* pn = reinterpret_cast<const PropertyNode*>(n);
        auto* p = reinterpret_cast<const u8*>(pn->value.second);
        const u64 vt = *reinterpret_cast<const u64*>(p);
        out.insert(out.end(), reinterpret_cast<const u8*>(&vt), reinterpret_cast<const u8*>(&vt) + 8);
        out.insert(out.end(), p + 0x10, p + 0x11);  // m_named
        out.insert(out.end(), p + 0x20, p + 0x24);  // the name hash
        if (is_string_property(vt)) {
            auto* s = reinterpret_cast<const params::String*>(p + 0x28);
            out.insert(out.end(), s->data(), s->data() + s->size());
            out.push_back(0xff);
        } else {
            out.insert(out.end(), p + 0x28, p + 0x30);
        }
        // in-order successor
        if (n->right) {
            n = n->right;
            while (n->left) n = n->left;
        } else {
            while (n->parent->left != n) n = n->parent;
            n = n->parent;
        }
    }
    return out;
}

bool h_child_impl(InfoBase* self, const void* map) {
    bool r = self->DeserializeChild(map);
    // (checked only without children: rerunning a child's DeserializeArray could append to it twice)
    if (!self->m_children.root && fam().due(f_child)) {
        live::RunBothFamily::Scope scope;
        std::vector<u8> n = props_state(self);
        bool g = guest_call(f_child.orig, {(u64)self, (u64)map}) & 1;
        std::vector<u8> after = props_state(self);
        bool ok = g == r && n == after;
        fam().result(f_child, ok ? Outcome::Ok : Outcome::Mismatch, ok ? "" : "a property differs after the original's run");
    }
    return r;
}
void h_child(Cpu& c) { c.set_x(0, h_child_impl(reinterpret_cast<InfoBase*>(c.x(0)), reinterpret_cast<const void*>(c.x(1)))); }

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN8InfoBase16DeserializeChildEPKN4Aska4ASON6AValue4AMapE", h_child, "info: InfoBase::DeserializeChild", &f_child.orig);

}  // namespace soa::native::info

// ---- differential test ----

#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "native/info/info_class.h"

namespace soa::native::info {

namespace {

struct Msgpack {
    std::vector<u8> b;
    void be(u64 v, int n) {
        for (int i = n - 1; i >= 0; i--) b.push_back((u8)(v >> (8 * i)));
    }
    void map(u32 n) { b.push_back(0xdf), be(n, 4); }
    void str(const char* s) {
        u64 n = std::strlen(s);
        b.push_back(0xdb), be(n, 4), b.insert(b.end(), s, s + n);
    }
    void uint(u64 v) { b.push_back(0xcf), be(v, 8); }
    void array(u32 n) { b.push_back(0xdd), be(n, 4); }
    void f32(float f) {
        u32 x;
        std::memcpy(&x, &f, 4);
        b.push_back(0xca), be(x, 4);
    }
};

}  // namespace

// CPersonStatusInfo (the guest's constructor and Initialize) deserialized from one map by the guest's
// DeserializeChild and by the native: every property's state must agree (values, strings, the keys that
// aren't the info's ignored; a key twice: the property deserializes the whole map twice).
NATIVE_TEST("info/deserialize-child") {
    Msgpack m;
    m.map(9);
    m.str("id"), m.uint(0x123456789abcull);
    m.str("player_name"), m.str("a player name longer than twenty-two bytes");
    m.str("level"), m.uint(57);
    m.str("hp"), m.uint(4321);
    m.str("skill1_label"), m.str("short");
    m.str("no_such_key"), m.uint(9);
    m.str("up_exp_rate"), m.f32(1.5f);
    m.str("is_rookie"), m.uint(1);
    m.str("level"), m.uint(58);
    alignas(16) u8 ason[sizeof(data_formats::ASON)];
    t.call("_ZN4Aska4ASONC1Ev", {(u64)ason});
    t.call("_ZN4Aska4ASON4InitEjb", {(u64)ason, 0x4000, 1});
    t.call("_ZN4Aska4ASON11DeserializeEPKvm", {(u64)ason, (u64)m.b.data(), m.b.size()});
    const auto* root = &reinterpret_cast<const data_formats::ASON*>(ason)->m_root;
    if (root->m_kind != AValue::kMap) {
        t.fail("the test document isn't a map");
        return;
    }
    std::vector<u64> a(0x2000 / 8), b(0x2000 / 8);
    for (u64* o : {a.data(), b.data()}) {
        t.call("_ZN17CPersonStatusInfoC2Ev", {(u64)o});
        t.call("_ZN17CPersonStatusInfo10InitializeEv", {(u64)o});
    }
    // (the children aren't touched: no key of the document names one)
    t.call("_ZN8InfoBase16DeserializeChildEPKN4Aska4ASON6AValue4AMapE", {(u64)a.data(), (u64)&root->m_body});
    reinterpret_cast<InfoBase*>(b.data())->DeserializeChild(&root->m_body);
    if (props_state(reinterpret_cast<InfoBase*>(a.data())) != props_state(reinterpret_cast<InfoBase*>(b.data())))
        t.fail("the properties differ");
    u64 id;
    std::memcpy(&id, reinterpret_cast<const u8*>(b.data()) + 0x38 + 0x28, 8);  // "id" (u64 at +0x38)
    if (id != 0x123456789abcull) t.fail("the document wasn't read (id %#llx)", (unsigned long long)id);
    for (u64* o : {a.data(), b.data()}) t.call("_ZN17CPersonStatusInfoD2Ev", {(u64)o});
    t.call("_ZN4Aska4ASOND1Ev", {(u64)ason});
}


// The children: CPersonStatusInfo's (an info, a derived info sharing its key, a list of infos, a list of
// values, a number map) deserialized from one document by the guest's DeserializeChild and by the native
// (each child's own DeserializeChild / DeserializeArray is the guest's from both): the whole state must
// agree (info_state: the properties, the maps, the children, the lists' and the map's elements). The
// live check can't run this case (the original after the native would append to the lists twice).
NATIVE_TEST("info/deserialize-child-children") {
    Msgpack m;
    m.map(7);
    m.str("id"), m.uint(77);
    m.str("Assist"), m.map(2);
    m.str("assist_role_id"), m.uint(7);
    m.str("assist_favor"), m.uint(9);
    m.str("UniverseDeityBoostInfo"), m.map(1);
    m.str("add_hp"), m.uint(5);
    m.str("CharacterDecoObject"), m.array(2);
    m.map(3);
    m.str("player_character_id"), m.uint(11);
    m.str("attach_bone"), m.str("a bone name longer than twenty-two bytes");
    m.str("pos_x"), m.f32(1.5f);
    m.map(1);
    m.str("index"), m.uint(3);
    m.str("UniverseEffectualTalentInfoList"), m.array(3);
    m.uint(1), m.uint(2), m.uint(3);
    m.str("factor_list"), m.map(1);
    m.str("5"), m.map(1);
    m.str("factor_id"), m.uint(42);
    m.str("no_such_key"), m.uint(1);
    alignas(16) u8 ason[sizeof(data_formats::ASON)];
    t.call("_ZN4Aska4ASONC1Ev", {(u64)ason});
    t.call("_ZN4Aska4ASON4InitEjb", {(u64)ason, 0x4000, 1});
    t.call("_ZN4Aska4ASON11DeserializeEPKvm", {(u64)ason, (u64)m.b.data(), m.b.size()});
    const auto* root = &reinterpret_cast<const data_formats::ASON*>(ason)->m_root;
    if (root->m_kind != AValue::kMap) {
        t.fail("the test document isn't a map");
        return;
    }
    const InfoClass& K = kInfo_CPersonStatusInfo;
    std::vector<u64> a(K.size / 8 + 1), b(K.size / 8 + 1);
    for (u64* o : {a.data(), b.data()}) {
        t.call("_ZN17CPersonStatusInfoC2Ev", {(u64)o});
        t.call("_ZN17CPersonStatusInfo10InitializeEv", {(u64)o});
    }
    t.call("_ZN8InfoBase16DeserializeChildEPKN4Aska4ASON6AValue4AMapE", {(u64)a.data(), (u64)&root->m_body});
    reinterpret_cast<InfoBase*>(b.data())->DeserializeChild(&root->m_body);
    auto* pa = reinterpret_cast<const u8*>(a.data());
    auto* pb = reinterpret_cast<const CPersonStatusInfo*>(b.data());
    if (info_state(K, pa) != info_state(K, reinterpret_cast<const u8*>(b.data()))) {
        t.fail("the state differs");
        for (const InfoChild& ch : K.children) {  // (which child, and where)
            auto x = info_state(*ch.cls, pa + ch.offset), y = info_state(*ch.cls, reinterpret_cast<const u8*>(b.data()) + ch.offset);
            if (x != y) {
                size_t i = 0;
                while (i < x.size() && i < y.size() && x[i] == y[i]) i++;
                t.fail("child %s at +%#x differs at %llu (%llu / %llu)", ch.cls->name, ch.offset, (unsigned long long)i,
                       (unsigned long long)x.size(), (unsigned long long)y.size());
            }
        }
    }
    // (the document reached the children)
    if (pb->m_Assist.m_assist_role_id.m_value != 7) t.fail("Assist wasn't read");
    auto* deco = reinterpret_cast<const InfoContainer*>(&pb->m_CharacterDecoObject);
    if ((deco->m_body[1] - deco->m_body[0]) / kInfo_CCharacterDecoObjectInfo.size != 2) t.fail("the deco list isn't two");
    auto* talents = reinterpret_cast<const InfoContainer*>(&pb->m_UniverseEffectualTalentInfoList);
    if ((talents->m_body[1] - talents->m_body[0]) / 0x30 != 3) t.fail("the talent list isn't three");
    auto* factors = reinterpret_cast<const InfoContainer*>(&pb->m_factor_list);
    if (factors->m_body[2] != 1) {
        t.fail("the factor map isn't one");
    } else {  // (its element, a copy of a temporary that wasn't initialized, registered and read its own properties)
        auto* node = reinterpret_cast<const u8*>(factors->m_body[0]);
        u32 id;
        std::memcpy(&id, node + 0x28 + offsetof(CFactorInfo, m_factor_id.m_value), 4);
        if (id != 42) t.fail("the factor's id is %u", id);
    }
    for (u64* o : {a.data(), b.data()}) t.call("_ZN17CPersonStatusInfoD2Ev", {(u64)o});
    t.call("_ZN4Aska4ASOND1Ev", {(u64)ason});
}

}  // namespace soa::native::info
