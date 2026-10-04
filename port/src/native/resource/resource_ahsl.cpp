// Aska::AHSLDatabase<T, 9>::GetData, both instantiations (ShaderCache: the compiled shaders, L1;
// ShaderDiskCache: the disk cache, L2), port/decomp/resource/ahsl.c. The shader cache looks every
// draw's shader key up here (AHSLCacheManagerV2::SearchOrCompile / SearchBindedVS), under the
// database's FastCriticalSection (inlined in the guest: sync's Enter / Leave here).
#include <cstring>

#include "core/cpu.h"
#include "native/common/native_method.h"
#include "native/resource/resource_check.h"
#include "native/resource/resource_layout.h"

namespace soa::native::resource {

namespace {
// Aska::ShaderKeyUtil::GetShaderKeySize(key): 11 bits from bytes 2..3 (a 5-instruction leaf the
// guest calls; read here).
inline s32 shader_key_size(const u8* key) { return key[2] | (key[3] & 7) << 8; }
}  // namespace

// The bucket: the key's first 9 bits (byte 0, the top bit of byte 1); the one-byte tag: the low 7
// bits of byte 1 and the top bit of byte 2; then the key from byte 2 on (GetShaderKeySize - 2 bytes)
// against each entry with that tag. The bucket's tags and entries are inline (8) or in m_ext*.
template <typename T>
T* AHSLDatabase<T>::GetData(const u8* key) {
    u32 bucket = (u32)key[0] << 1 | key[1] >> 7;
    u8 tag = (u8)(key[1] << 1 | key[2] >> 7);
    s32 size = shader_key_size(key);
    m_cs.Enter();
    T* found = nullptr;
    const AHSLNode<T>& node = m_nodes[bucket];
    const AHSLTagBucket& tags = m_tags[bucket];
    const u8* tag_bytes = tags.m_extTags ? tags.m_extTags : tags.m_tags;
    for (u32 i = 0; i < node.m_count; i++) {
        if (tag_bytes[i] != tag) continue;
        const AHSLEntry<T>* entries = node.m_ext ? node.m_ext : node.m_entries;
        if (std::memcmp(key + 2, entries[i].m_key + 2, (size_t)(s64)(size - 2)) == 0) {
            found = entries[i].m_data;
            break;
        }
    }
    m_cs.Leave();
    return found;
}

template ShaderCache* AHSLDatabase<ShaderCache>::GetData(const u8*);
template ShaderDiskCache* AHSLDatabase<ShaderDiskCache>::GetData(const u8*);

// ---- bindings and live checks (resource_check.h: read-only under its lock, the guest after the native) ----

namespace {

CheckedFn g_get_l1("_ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE7GetDataEPKh"), g_get_l2("_ZN4Aska12AHSLDatabaseINS_15ShaderDiskCacheELh9EE7GetDataEPKh");

template <auto M>
void getter(Cpu& c, CheckedFn& f) {
    if (!live::check_due(f)) return wrap_method<M>()(c);
    live::check_getter(c, f, wrap_method<M>(), ~0ull);
}
void get_l1_checked(Cpu& c) { getter<&AHSLDatabase<ShaderCache>::GetData>(c, g_get_l1); }
void get_l2_checked(Cpu& c) { getter<&AHSLDatabase<ShaderDiskCache>::GetData>(c, g_get_l2); }

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE7GetDataEPKh", get_l1_checked,
                     "resource: Aska::AHSLDatabase<ShaderCache, 9>::GetData (sync's FastCriticalSection)", &g_get_l1.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12AHSLDatabaseINS_15ShaderDiskCacheELh9EE7GetDataEPKh", get_l2_checked,
                     "resource: Aska::AHSLDatabase<ShaderDiskCache, 9>::GetData", &g_get_l2.orig);

}  // namespace soa::native::resource
