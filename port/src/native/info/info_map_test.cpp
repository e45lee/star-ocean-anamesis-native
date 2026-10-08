// Differential test of IInfoBaseMap<K, T>::DeserializeChild (info_map.cpp): for every map of
// gen/info_classes.h INFO_MAP_DESERIALIZERS, two containers built alike (InfoCode::Ctor), one document (a
// map of five pairs: keys "5", "12", "5" again, "3" and "4294967301" (a u64 key; a u32 map's parse wraps
// it), each value a map naming every property of T's Initialize, an array, or a number) deserialized by
// the guest's function (no natives in --selftest: T's constructor, Initialize and DeserializeChild are the
// guest's) and by the native, twice (the second run empties the map and builds it again): the keys and
// every node's T (info_state) must agree.
#include <cstring>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/data_formats/data_formats_layout.h"
#include "native/info/info_class.h"

namespace soa::native::info {

bool info_map_deserialize_child(const InfoClass& M, void* self, const void* map);
std::vector<u8> info_map_state(const InfoClass& M, const void* self);

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
};

struct MapRow {
    const InfoClass* cls;
    const char* sym;
};
#define INFO_MAP_ROW(C, SYM) {&kInfo_##C, SYM},
const MapRow kMapRows[] = {INFO_MAP_DESERIALIZERS(INFO_MAP_ROW)};
#undef INFO_MAP_ROW

// T's value: every key its Initialize names, numbered from `seed`.
void element(Msgpack& m, const InfoClass& T, u64 seed) {
    std::vector<const char*> keys;
    for (const InfoStep& s : T.init)
        if (s.kind == InfoStep::kProperty && s.key) keys.push_back(s.key);
    m.map((u32)keys.size());
    for (size_t i = 0; i < keys.size(); i++) m.str(keys[i]), m.uint(seed + i);
}

}  // namespace

NATIVE_TEST("info/map-deserialize-child") {
    int maps = 0, nodes = 0;
    for (const MapRow& row : kMapRows) {
        const InfoClass& M = *row.cls;
        const InfoClass& T = *M.elem;
        Msgpack m;
        m.map(5);
        m.str("5"), element(m, T, 10);
        m.str("12"), m.array(1), m.uint(3);
        m.str("5"), element(m, T, 20);
        m.str("3"), m.uint(9);
        m.str("4294967301"), element(m, T, 30);
        alignas(16) u8 ason[sizeof(data_formats::ASON)];
        t.call("_ZN4Aska4ASONC1Ev", {(u64)ason});
        t.call("_ZN4Aska4ASON4InitEjb", {(u64)ason, 0x10000, 1});
        t.call("_ZN4Aska4ASON11DeserializeEPKvm", {(u64)ason, (u64)m.b.data(), m.b.size()});
        const auto* root = &reinterpret_cast<const data_formats::ASON*>(ason)->m_root;
        if (root->m_kind != data_formats::AValue::kMap) {
            t.fail("%s: the test document isn't a map", M.name);
            t.call("_ZN4Aska4ASOND1Ev", {(u64)ason});
            continue;
        }
        alignas(16) u8 a[0x50], b[0x50];
        for (u8* o : {a, b}) {
            std::memset(o, 0, sizeof a);
            InfoCode::Ctor(M, o);
        }
        for (int run = 0; run < 2; run++) {
            u64 g = t.call(row.sym, {(u64)a, (u64)&root->m_body}) & 0xff;
            bool n = info_map_deserialize_child(M, b, &root->m_body);
            if (g != (u64)n) t.fail("%s run %d: result guest %llu native %d", M.name, run, (unsigned long long)g, (int)n);
            std::vector<u8> sa = info_map_state(M, a), sb = info_map_state(M, b);
            if (sa != sb) {
                size_t i = 0;
                while (i < sa.size() && i < sb.size() && sa[i] == sb[i]) i++;
                t.fail("%s run %d: the maps differ at byte %zu (%zu / %zu)", M.name, run, i, sa.size(), sb.size());
            }
        }
        nodes += (int)reinterpret_cast<const InfoContainer*>(b)->m_body[2];
        maps++;
        for (u8* o : {a, b}) InfoCode::Dtor(M, o);
        t.call("_ZN4Aska4ASOND1Ev", {(u64)ason});
    }
    if (maps < 60 || nodes < 3 * maps) t.fail("too few maps (%d) or nodes (%d)", maps, nodes);
}

}  // namespace soa::native::info
