// The master caches' maps (master_hash.h).
#include "native/master/master_hash.h"

#include <cmath>

#include "native/common/gen/common_addresses.h"
#include "native/common/live_call.h"
#include "native/master/gen/master_addresses.h"
#include "native/master/master_family.h"
#include "native/master/master_guest.h"
#include "native/memory/memory_callees.h"

namespace soa::native::master {

u64 fcvtpu(float f) {
    if (std::isnan(f) || f <= -1.0f) return 0;
    if (f >= 18446744073709551616.0f) return ~u64(0);
    float c = std::ceil(f);
    return c <= 0 ? 0 : (u64)c;
}

void* U32Map::alloc_block(u64 n) {
    using memory::kStlAllocateCallee;
    void* p = kStlAllocateCallee.direct()
                  ? memory::CAssignedMemoryManagerForSTLAllocator::Allocate(n, (const char*)g::at(g::kUnorderedMapH), 0x1c)
                  : (void*)live::out_call(family(), kStlAllocateCallee.addr(), {n, g::at(g::kUnorderedMapH), 0x1c});
    if (!p) g::Assert(native::kStrStlAllocatorH, 0xbe, native::kStrAllocatedMemoryIsNull);
    return p;
}

void U32Map::free_block(void* p) { g::StlFree(p); }

U32Node* U32Map::find(u32 key) const {
    u64 n = bucket_count;
    if (!n) return nullptr;
    u64 i = constrain(key, n);
    U32Node* p = buckets[i];
    if (!p) return nullptr;
    for (p = p->next; p; p = p->next) {
        if (constrain(p->hash, n) != i) return nullptr;
        if (p->key == key) return p;
    }
    return nullptr;
}

void U32Map::rehash(u64 n) {
    static const u64 next_prime = g::sym("_ZNSt6__ndk112__next_primeEm");
    if (n == 1) n = 2;
    else if (n & (n - 1)) n = live::out_call(family(), next_prime, {n});
    u64 bc = bucket_count;
    if (n > bc) return rehash_exact(n);
    if (n == bc) return;
    u64 need = fcvtpu((float)size / max_load_factor);
    u64 m;
    if (bc >= 3 && !(bc & (bc - 1))) {
        u64 x = need - 1;
        u32 lz = x ? (u32)__builtin_clzll(x) : 64;
        m = u64(1) << ((64 - lz) & 63);
    } else {
        m = live::out_call(family(), next_prime, {need});
    }
    u64 to = n < m ? m : n;
    if (to < bc) rehash_exact(to);
}

void U32Map::rehash_exact(u64 n) {
    if (!n) {
        U32Node** old = buckets;
        buckets = nullptr;
        if (old) free_block(old);
        bucket_count = 0;
        return;
    }
    auto** nb = (U32Node**)alloc_block(n << 3);
    U32Node** old = buckets;
    buckets = nb;
    if (old) free_block(old);
    bucket_count = n;
    for (u64 i = 0; i < n; i++) buckets[i] = nullptr;
    U32Node* pp = anchor();
    U32Node* cp = pp->next;
    if (!cp) return;
    u64 chash = constrain(cp->hash, n);
    buckets[chash] = pp;
    pp = cp;
    for (cp = cp->next; cp; cp = pp->next) {
        u64 nhash = constrain(cp->hash, n);
        if (nhash == chash) {
            pp = cp;
        } else if (!buckets[nhash]) {
            buckets[nhash] = pp;
            pp = cp;
            chash = nhash;
        } else {
            U32Node* np = cp;
            while (np->next && cp->key == np->next->key) np = np->next;
            pp->next = np->next;
            np->next = buckets[nhash]->next;
            buckets[nhash]->next = cp;
        }
    }
}

void U32Map::insert(U32Node* nd) {
    u64 h = nd->hash;
    u64 bc = bucket_count;
    if (bc == 0 || max_load_factor * (float)bc < (float)(size + 1)) {
        u64 grow = (bc < 3 ? 1 : (u64)((bc & (bc - 1)) != 0)) | (bc << 1);
        u64 need = fcvtpu((float)(size + 1) / max_load_factor);
        rehash(grow < need ? need : grow);
        bc = bucket_count;
    }
    u64 i = constrain(h, bc);
    U32Node* pn = buckets[i];
    if (!pn) {
        pn = anchor();
        nd->next = pn->next;
        pn->next = nd;
        buckets[i] = pn;
        if (nd->next) buckets[constrain(nd->next->hash, bc)] = nd;
    } else {
        nd->next = pn->next;
        pn->next = nd;
    }
    ++size;
}

void U32Map::unlink(U32Node* nd) {
    u64 bc = bucket_count;
    u64 i = constrain(nd->hash, bc);
    U32Node* pn = buckets[i];
    while (pn->next != nd) pn = pn->next;
    if (pn == anchor() || constrain(pn->hash, bc) != i) {
        if (!nd->next || constrain(nd->next->hash, bc) != i) buckets[i] = nullptr;
    }
    if (nd->next) {
        u64 j = constrain(nd->next->hash, bc);
        if (j != i) buckets[j] = pn;
    }
    pn->next = nd->next;
    nd->next = nullptr;
    --size;
}

}  // namespace soa::native::master
