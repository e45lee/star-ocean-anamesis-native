// Differential test of resource_ahsl.cpp: AHSLDatabase<T, 9>::GetData on a private database (zeroed,
// its critical section built by the guest's constructor) filled with synthetic shader keys: inline
// and external tag / entry arrays, keys sharing a bucket and a tag but differing later, hits and
// misses; the guest original and the native look up the same keys. In --selftest natives aren't
// installed: t.call reaches the guest code.
#include <cstring>
#include <memory>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "native/common/test.h"
#include "native/resource/resource_layout.h"

using namespace soa;
using namespace soa::native::resource;

namespace {

// A shader key's size: byte 2 and the low 3 bits of byte 3 (ShaderKeyUtil::GetShaderKeySize).
int key_size(const u8* k) { return k[2] | (k[3] & 7) << 8; }

// A shader key: size < 128 in byte 2's low 7 bits; byte 2's top bit is the tag's low bit, and it is
// also the size's bit 7 (GetShaderKeySize reads the whole byte): a key with it set is 128 bytes
// longer, and GetData compares that many. Every buffer holds the longest key (an earlier version
// allocated size + 8 bytes, and both sides read up to 128 bytes past it: on Windows a key at the
// end of a heap page faulted); a lookup key compared against a shorter stored key with the same
// tag stays inside the stored key's buffer too.
constexpr int kKeyBuffer = 0x80 + 0x7f + 8;
std::vector<u8> make_key(TestContext& t, u8 b0, u8 b1, u8 b2, int size) {
    std::vector<u8> k(kKeyBuffer);
    for (auto& b : k) b = (u8)t.rand_u64();
    k[0] = b0;
    k[1] = b1;
    k[2] = (u8)((b2 & 0x80) | (size & 0x7f));
    k[3] = (u8)(k[3] & ~7);
    if ((int)k.size() < key_size(k.data()) + 8) t.fail("make_key: key size %d in a %d-byte buffer", key_size(k.data()), (int)k.size());
    return k;
}

template <typename T>
void run_database(TestContext& t, const char* get_sym) {
    using DB = AHSLDatabase<T>;
    static std::unique_ptr<u8[]> storage(new u8[sizeof(DB) + 16]);
    auto* db = reinterpret_cast<DB*>((reinterpret_cast<u64>(storage.get()) + 15) & ~u64(15));
    std::memset((void*)db, 0, sizeof(DB));
    t.call("_ZN4Aska19FastCriticalSectionC2Ev", {(u64)&db->m_cs});
    std::vector<std::vector<u8>> keys;
    std::vector<std::unique_ptr<AHSLEntry<T>[]>> ext_entries;
    std::vector<std::unique_ptr<u8[]>> ext_tags;
    keys.reserve(400);
    // 24 buckets: some with up to 8 inline entries, some external (up to 20)
    for (int b = 0; b < 24; b++) {
        u8 b0 = (u8)t.rand_u64(), b1top = (u8)(t.rand_int(0, 1) << 7);
        u32 bucket = (u32)b0 << 1 | b1top >> 7;
        if (db->m_nodes[bucket].m_count) continue;
        bool ext = b % 3 == 0;
        int n = ext ? t.rand_int(9, 20) : t.rand_int(1, 8);
        AHSLNode<T>& node = db->m_nodes[bucket];
        AHSLTagBucket& tb = db->m_tags[bucket];
        AHSLEntry<T>* entries = node.m_entries;
        u8* tags = tb.m_tags;
        if (ext) {
            ext_entries.emplace_back(new AHSLEntry<T>[n]);
            ext_tags.emplace_back(new u8[n]);
            entries = node.m_ext = ext_entries.back().get();
            tags = tb.m_extTags = ext_tags.back().get();
        }
        node.m_capacity = tb.m_capacity = (u16)(ext ? n : 8);
        node.m_count = tb.m_count = (u16)n;
        u8 shared_b1 = (u8)t.rand_u64();
        for (int i = 0; i < n; i++) {
            // half the keys share the bucket's tag (byte 1, byte 2's top bit) and differ later
            u8 kb1 = (u8)((i % 2 ? shared_b1 : (u8)t.rand_u64()) & 0x7f) | b1top;
            keys.push_back(make_key(t, b0, kb1, i % 2 ? 0x80 : (u8)t.rand_u64(), t.rand_int(6, 40)));
            const u8* k = keys.back().data();
            entries[i].m_key = k;
            entries[i].m_data = reinterpret_cast<T*>(0x10000 + keys.size() * 0x10);
            tags[i] = (u8)(k[1] << 1 | k[2] >> 7);
        }
    }
    int hits = 0;
    auto lookup = [&](const u8* key) {
        u64 g = t.call(get_sym, {(u64)db, (u64)key});
        u64 n = (u64)db->GetData(key);
        if (g) hits++;
        return t.expect_eq(n, g, "GetData");
    };
    for (auto& k : keys)
        if (!lookup(k.data())) break;
    // misses: a key's copy with one byte past the tag changed; keys in empty buckets
    for (auto& k : keys) {
        std::vector<u8> m = k;
        m[4 + t.rand_int(0, key_size(m.data()) - 5)] ^= 0x10;  // (a byte GetData compares)
        if (!lookup(m.data())) break;
    }
    for (int i = 0; i < 64; i++) {
        auto k = make_key(t, (u8)t.rand_u64(), (u8)t.rand_u64(), (u8)t.rand_u64(), t.rand_int(4, 30));
        if (!lookup(k.data())) break;
    }
    t.expect_eq(hits >= (int)keys.size(), true, "every stored key found");
    t.expect_eq(db->m_cs.m_lock, FastCriticalSection::kFree, "lock released");
    t.call("_ZN4Aska19FastCriticalSectionD2Ev", {(u64)&db->m_cs});
}

}  // namespace

NATIVE_TEST("resource/ahsl-get-data") {
    run_database<ShaderCache>(t, "_ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE7GetDataEPKh");
    run_database<ShaderDiskCache>(t, "_ZN4Aska12AHSLDatabaseINS_15ShaderDiskCacheELh9EE7GetDataEPKh");
}
