// Differential tests of the `containers` natives against the 3.7.0 guest (--selftest containers/):
// the guest functions run as ARM64 code (natives aren't installed in --selftest), the natives on the
// same inputs (random, plus the shapes the game uses).
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/containers/containers_layout.h"
#include "native/containers/containers_object_container.h"
#include "native/libcxx/libcxx_layout.h"

namespace soa::native::containers {
namespace {

std::string rand_text(TestContext& t, size_t maxlen) {
    std::string s((size_t)t.rand_int(0, (int)maxlen), ' ');
    for (auto& c : s) c = (char)t.rand_int(1, 255);
    return s;
}

NATIVE_TEST("containers/utf8-to-multibyte") {
    constexpr const char* kSym = "_ZN4Aska13StringUtility15Utf8ToMultiByteEPKcPcj";
    for (int k = 0; k < 400; k++) {
        std::string s = k % 5 == 0 ? std::string("Character/cp0303/role_cp0303_b04a_6131.aif") : rand_text(t, k % 3 ? 40 : 300);
        int mode = t.rand_int(0, 4);  // 0: size query, 1: copy with a cap, 2: null dst + cap, 3: dst + cap 0, 4: exact cap
        u32 cap = mode == 1 ? (u32)t.rand_int(1, 400) : mode == 2 ? 5 : mode == 4 ? (u32)s.size() + 1 : 0;
        bool dst = mode == 1 || mode == 3 || mode == 4;
        std::vector<char> g(512, '\x5a'), n(512, '\x5a');
        u32 rg = (u32)t.call(kSym, {(u64)s.c_str(), dst ? (u64)g.data() : 0, cap});
        u32 rn = (u32)StringUtility::Utf8ToMultiByte(s.c_str(), dst ? n.data() : nullptr, cap);
        if (rg != rn || g != n) {
            t.fail("case %d (mode %d, len %zu, cap %u): guest %#x native %#x%s", k, mode, s.size(), cap, rg, rn, g != n ? ", bytes differ" : "");
            return;
        }
    }
}

// The accessors of the four executed TObjectContainer instantiations on containers with the guest's
// vtable (slot 4 = the instantiation's own NumElements).
template <typename T>
void objc_case(TestContext& t, const char* mangled) {
    using C = memory::TObjectContainer<T>;
    std::string m = mangled;
    std::string vt = "_ZTVN9Framework16TObjectContainer" + m + "E";
    std::string num = "_ZNK9Framework16TObjectContainer" + m + "11NumElementsEv";
    std::string r = "_ZN9Framework16TObjectContainer" + m + "8rElementEm";
    std::string cr = "_ZNK9Framework16TObjectContainer" + m + "9crElementEm";
    std::vector<u8> storage(64 * sizeof(T));
    for (int k = 0; k < 30; k++) {
        C c{};
        c.vtable = (const void*)(t.sym(vt.c_str()) + 0x10);
        c.m_count = (u64)t.rand_int(1, 64);
        c.m_elements = reinterpret_cast<T*>(storage.data());
        u64 i = (u64)t.rand_int(0, (int)c.m_count - 1);
        u64 gn = t.call(num.c_str(), {(u64)&c}), gr = t.call(r.c_str(), {(u64)&c, i}), gcr = t.call(cr.c_str(), {(u64)&c, i});
        u64 nn = c.NumElements(), nr = (u64)c.rElement(i), ncr = (u64)c.crElement(i);
        if (gn != nn || gr != nr || gcr != ncr) {
            t.fail("%s: count %llu i %llu: guest %llu %#llx %#llx native %llu %#llx %#llx", mangled, (unsigned long long)c.m_count, (unsigned long long)i,
                   (unsigned long long)gn, (unsigned long long)gr, (unsigned long long)gcr, (unsigned long long)nn, (unsigned long long)nr, (unsigned long long)ncr);
            return;
        }
    }
}

NATIVE_TEST("containers/object-container") {
    objc_case<memory::SoundElement>(t, "INS_6CSound8CElementEE");
    objc_case<memory::CollisionShapeGroup>(t, "IN9Collision19CollisionShapeGroupEE");
    objc_case<memory::IFixedLengthAllocatorRef*>(t, "IPNS_21IFixedLengthAllocatorEE");
    objc_case<memory::BehaviorQueueRef*>(t, "IP13BehaviorQueueE");
}

}  // namespace

void tom_quick_sort(bool descend, void** a, s32 lo, s32 hi, const void* ctx);
libcxx::basic_string<char>* stl_replace_self(libcxx::basic_string<char>* s, const libcxx::basic_string<char>& from, const libcxx::basic_string<char>& to,
                                             bool* replaced);
void stl_replace(libcxx::basic_string<char>* out, const libcxx::basic_string<char>& src, const libcxx::basic_string<char>& from,
                 const libcxx::basic_string<char>& to, bool* replaced);

namespace {

// TOMQuickSort<RenderableObject>: random keys (many equal, some NaN-free ties), random ranges; the
// resulting order must be the guest's exactly (equal keys included).
// THashMap<std::string, CAssetInfo>::Find_ on tables built by hand (the guest's bucket layout: state,
// key string short or long, the 0xa0-byte value), probing with present, absent and colliding keys.
NATIVE_TEST("containers/hash-map-find-asset") {
    using String = libcxx::String;
    using Map = THashMap<String, Opaque<0xa0>>;
    using Bucket = THashMapBucket<TPair<String, Opaque<0xa0>>>;
    using It = THashMapIterator<Bucket>;
    constexpr const char* kSym =
        "_ZNK4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_"
        "CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE5Find_ERSG_";
    auto make = [](String& g, const std::string& v) {
        std::memset(&g, 0, sizeof g);
        if (v.size() < 23) {
            g.r.s.head.size = (u8)(v.size() << 1);
            std::memcpy((char*)&g + 1, v.data(), v.size());
        } else {
            g.r.l.cap = (v.size() + 16) | 1;
            g.r.l.size = v.size();
            g.r.l.data = const_cast<char*>(v.data());
        }
    };
    for (int k = 0; k < 60; k++) {
        u64 count = (u64)t.rand_int(0, 40);
        std::vector<Bucket> buckets(count);
        std::vector<std::string> names;
        for (int i = 0; i < 30; i++) names.push_back(std::string(k % 2 ? "Character/cp" : "c") + std::to_string(t.rand_int(0, 50)) + (i % 3 ? std::string(30, 'x') : ""));
        names.push_back("");
        std::memset(buckets.data(), 0, count * sizeof(Bucket));
        for (u64 i = 0; i < count; i++) {
            buckets[i].m_state = (u8)t.rand_int(0, 2);
            make(buckets[i].m_value.first, names[(size_t)t.rand_int(0, (int)names.size() - 1)]);
        }
        alignas(8) Map m{};
        m.table.m_buckets.m_data = buckets.data();
        m.table.m_buckets.m_count = count;
        for (int q = 0; q < 40; q++) {
            String key;
            std::string probe = q % 7 == 0 ? "absent" + std::to_string(q) : names[(size_t)t.rand_int(0, (int)names.size() - 1)];
            make(key, probe);
            It g{};
            t.call(kSym, GuestArgs().sret(&g).p(&m).p(&key));
            It n = m.Find_(key);
            if (g.m_bucket != n.m_bucket || g.m_begin != n.m_begin || g.m_end != n.m_end) {
                t.fail("Find_ case %d probe \"%s\" (%llu buckets): guest bucket %td, native %td", k, probe.c_str(), (unsigned long long)count,
                       g.m_bucket - buckets.data(), n.m_bucket - buckets.data());
                return;
            }
        }
    }
}

// CSTLStringUtility_Base<std::string>::ReplaceSelf / Replace on strings the guest built (its insert),
// patterns that occur 0..n times, overlap, grow or shrink the string, short and long forms.
NATIVE_TEST("containers/stl-string-replace") {
    using Str = libcxx::basic_string<char>;
    constexpr const char* kInsert = "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE6insertEmPKc";
    constexpr const char* kDtor = "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEED2Ev";
#define UTIL_SYM(m) \
    "_ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE" m
    auto make = [&](Str& s, const std::string& v) {
        std::memset(&s, 0, sizeof s);
        if (!v.empty()) t.call(kInsert, {(u64)&s, 0, (u64)v.c_str()});
    };
    auto text = [&](int maxlen, const char* alphabet) {
        std::string v((size_t)t.rand_int(0, maxlen), ' ');
        for (auto& c : v) c = alphabet[t.rand_int(0, (int)std::strlen(alphabet) - 1)];
        return v;
    };
    for (int k = 0; k < 400; k++) {
        std::string base = text(k % 3 ? 30 : 120, "abc/._");
        std::string from = text(3, "abc/");
        if (from.empty()) from = "a";
        std::string to = text(k % 4 ? 4 : 40, "xyz/");
        if (to.find(from) != std::string::npos && to.size() >= from.size()) to = "Z";  // (keeps the guest's loop finite)
        Str g, n, f, tt, go, no;
        make(g, base), make(n, base), make(f, from), make(tt, to);
        bool gr = true, nr = true;
        bool* gp = k % 5 ? &gr : nullptr;
        bool* np = gp ? &nr : nullptr;
        if (k % 2) {
            u64 r = t.call(UTIL_SYM("11ReplaceSelfERS8_RKS8_SC_Pb"), {(u64)&g, (u64)&f, (u64)&tt, (u64)gp});
            Str* rn = stl_replace_self(&n, f, tt, np);
            if (r != (u64)&g || rn != &n) t.fail("ReplaceSelf's result");
        } else {
            make(go, ""), make(no, "");
            t.call(UTIL_SYM("7ReplaceERKS8_SB_SB_Pb"), GuestArgs().sret(&go).p(&g).p(&f).p(&tt).p(gp));
            stl_replace(&no, n, f, tt, np);
        }
        const Str& a = k % 2 ? g : go;
        const Str& b = k % 2 ? n : no;
        bool same = std::string(a.data(), a.size()) == std::string(b.data(), b.size()) && a.is_long() == b.is_long() && a.capacity() == b.capacity() &&
                    gr == nr && std::string(g.data(), g.size()) == std::string(n.data(), n.size());
        for (Str* s : {&g, &n, &f, &tt}) t.call(kDtor, {(u64)s});
        if (!(k % 2)) t.call(kDtor, {(u64)&go}), t.call(kDtor, {(u64)&no});
        if (!same) {
            t.fail("case %d: \"%s\" / \"%s\" -> \"%s\": results differ", k, base.c_str(), from.c_str(), to.c_str());
            return;
        }
    }
#undef UTIL_SYM
}

NATIVE_TEST("containers/tom-quick-sort") {
    constexpr int kObjs = 400;
    std::vector<u8> objs(kObjs * 0x1c0);
    std::vector<float> ctx(2 * kObjs);
    for (int k = 0; k < 300; k++) {
        int distinct = t.rand_int(1, k % 3 == 0 ? 4 : 1000);
        for (int i = 0; i < kObjs; i++) {
            *(u16*)&objs[i * 0x1c0 + 0x1b8] = (u16)t.rand_int(0, kObjs - 1);
            ctx[2 * i + 1] = (float)t.rand_int(0, distinct) * 0.5f - 3.0f;
        }
        int n = t.rand_int(0, k % 5 == 0 ? 20 : 350);
        int lo = t.rand_int(0, std::min(n, 5)), hi = t.rand_int(lo, n);
        std::vector<void*> g(n), v;
        for (auto& p : g) p = &objs[(size_t)t.rand_int(0, kObjs - 1) * 0x1c0];
        v = g;
        bool desc = k & 1;
        t.call(desc ? "_ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE7DescendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE"
                    : "_ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE6AscendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE",
               {(u64)g.data(), (u64)lo, (u64)hi, (u64)ctx.data()});
        tom_quick_sort(desc, v.data(), lo, hi, ctx.data());
        if (g != v) {
            t.fail("case %d (%s, n %d, [%d, %d), %d keys): orders differ", k, desc ? "Descend" : "Ascend", n, lo, hi, distinct);
            return;
        }
    }
}

}  // namespace
}  // namespace soa::native::containers

