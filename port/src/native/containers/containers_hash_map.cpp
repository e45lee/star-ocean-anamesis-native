// Aska::THashMap<std::string, CAssetInfo, Hasher_CSTLString>::Find_: the resource manager's asset
// table lookup (containers_layout.h; port/decomp/containers/hash.c). Open addressing, linear probing
// from h = Framework::CHash32 of the key; equal = same length and bytes.
#include <cstring>

#include "native/common/live_leaf.h"
#include "native/containers/containers_family.h"
#include "native/containers/containers_layout.h"
#include "native/libcxx/libcxx_layout.h"

namespace soa::native::containers {

namespace {

using String = libcxx::String;
using CAssetInfo = Opaque<0xa0>;  // (the client's asset record; only its size matters here)
using AssetMap = THashMap<String, CAssetInfo>;
using AssetBucket = THashMapBucket<TPair<String, CAssetInfo>>;
static_assert(sizeof(AssetBucket) == 0xc0 && offsetof(AssetBucket, m_value) == 8);
static_assert(sizeof(AssetMap) == 0x30);

// Framework::CHash32 of a string (Hasher_CSTLString): zlib's CRC-32 table, seeded with the length, no
// final xor (the hash subsystem's CHash32::Of; kept here until that subsystem is on main).
u32 chash32(const char* s, u64 n) {
    struct Table {
        u32 t[256];
        constexpr Table() : t{} {
            for (u32 i = 0; i < 256; i++) {
                u32 c = i;
                for (int k = 0; k < 8; k++) c = (c & 1) ? (c >> 1) ^ 0xEDB88320u : c >> 1;
                t[i] = c;
            }
        }
    };
    static constexpr Table kTable;
    u32 h = (u32)n;
    for (u64 i = 0; i < n; i++) h = kTable.t[(h ^ (u8)s[i]) & 0xff] ^ (h >> 8);
    return h;
}

}  // namespace

template <>
THashMapIterator<AssetBucket> AssetMap::Find_(const String& key) const {
    AssetBucket* buckets = table.m_buckets.m_data;
    u64 count = table.m_buckets.m_count;
    THashMapIterator<AssetBucket> it{buckets + count, buckets, buckets + count};
    u64 h = chash32(key.data(), key.size());
    for (u64 i = 0; i < count; i++) {
        AssetBucket& b = buckets[(i + h) % count];
        if (b.m_state == 1) {
            const String& k = b.m_value.first;
            if (k.size() == key.size() && std::memcmp(k.data(), key.data(), key.size()) == 0) {
                it.m_bucket = &b;
                return it;
            }
        } else if (b.m_state == 0) {
            break;
        }
    }
    return it;
}

// ---- natives ----

namespace {
void Find_asset(Cpu& c) {
    auto* map = reinterpret_cast<const AssetMap*>(c.x(0));
    *reinterpret_cast<THashMapIterator<AssetBucket>*>(c.x(8)) = map->Find_(*reinterpret_cast<const String*>(c.x(1)));
}
}  // namespace

LEAF_HOSTFN(family(),
            "_ZNK4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_"
            "CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE5Find_ERSG_",
            &Find_asset, sizeof(AssetMap), live::kVoid, "Aska::THashMap<std::string, CAssetInfo>::Find_", {live::out(8, 0x18)});

}  // namespace soa::native::containers
