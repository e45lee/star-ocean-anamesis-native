// Layout tests for containers_layout.h (port/PLAN.md task 6, types first): the guest's own code builds
// and fills each container (its constructor or the constructor it inlines, then its methods, called
// through t.call: natives are not installed in --selftest), and the host reads the result through
// the recovered classes. A wrong offset reads a wrong field and fails the comparison. No natives.
#include <cstring>
#include <vector>

#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "native/containers/containers_layout.h"

namespace soa::native::containers {
namespace {

const void* vtable_of(TestContext& t, const char* zt) { return (const void*)(t.sym(zt) + 0x10); }

}  // namespace

NATIVE_TEST("containers/layout-tstaticstring") {
    TStaticString16 s16;
    std::memset(&s16, 0x55, sizeof s16);
    t.call("_ZN9Framework13TStaticStringILm16EE3SetEPKc", {(u64)&s16, (u64)"hello"});
    t.expect_eq(std::string(s16.m_str), std::string("hello"), "TStaticString<16>::Set short");
    t.call("_ZN9Framework13TStaticStringILm16EE3SetEPKc", {(u64)&s16, (u64)"0123456789abcdefghij"});
    t.expect_eq(std::string(s16.m_str, 16), std::string("0123456789abcde\0", 16), "TStaticString<16>::Set truncates to 15 + NUL");

    TStaticString32 s32;
    std::memset(&s32, 0x55, sizeof s32);
    t.call("_ZN9Framework13TStaticStringILm32EE3SetEPKc", {(u64)&s32, (u64)"role_cp0303_b04a_6131"});
    t.expect_eq(std::string(s32.m_str), std::string("role_cp0303_b04a_6131"), "TStaticString<32>::Set");

    TStaticString256 s256;
    std::memset(&s256, 0x55, sizeof s256);
    std::strcpy(s256.m_str, "Parameter/");
    u64 r = t.call("_ZN9Framework13TStaticStringILm256EEpLEPKc", {(u64)&s256, (u64)"master_text.bin"});
    t.expect_eq(r, (u64)&s256, "operator+= returns this");
    t.expect_eq(std::string(s256.m_str), std::string("Parameter/master_text.bin"), "TStaticString<256>::operator+=");
}

// THashMap<unsigned, unsigned long>: constructed as CHandleManager_Base::Initialize inlines it, filled
// with the guest's operator[]; the host finds every key by HashInt + linear probing in m_buckets.
NATIVE_TEST("containers/layout-thashmap") {
    THashMapU32U64 m;
    std::memset(&m, 0, sizeof m);
    m.table.vtable = vtable_of(t, "_ZTVN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEEE");
    m.table.m_maxLoadFactor = 0.75f;
    const char* index = "_ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEEixERS7_";
    std::vector<u32> keys;
    u32 seed = (u32)t.rand_u64();
    for (u32 i = 0; i < 60; i++) keys.push_back(seed + i * 2654435761u);  // distinct
    std::vector<u64> slots;
    for (u32 k : keys) {
        u64* v = (u64*)t.call(index, {(u64)&m, (u64)&k});
        *v = (u64)k * 3 + 1;
        slots.push_back((u64)v);
    }
    t.expect_eq(m.table.m_size, (u32)keys.size(), "m_size == keys inserted");
    t.expect_eq(m.table.m_deleted, 0u, "m_deleted");
    t.expect_eq(m.table.m_maxLoadFactor, 0.75f, "m_maxLoadFactor");
    u64 n = m.table.m_buckets.m_count;
    if (!m.table.m_buckets.m_data || n < keys.size()) {
        t.fail("bucket array %p x %llu", (void*)m.table.m_buckets.m_data, (unsigned long long)n);
        return;
    }
    u64 used = 0;
    for (u64 i = 0; i < n; i++) used += m.table.m_buckets.m_data[i].m_state == 1;
    t.expect_eq(used, (u64)keys.size(), "buckets in state 1");
    for (size_t j = 0; j < keys.size(); j++) {
        u32 k = keys[j];
        u64 h = HashInt(k);
        const THashMapBucket<TPair<u32, u64>>* found = nullptr;
        for (u64 i = 0; i < n; i++) {
            auto& b = m.table.m_buckets.m_data[(h + i) % n];
            if (b.m_state == 0) break;
            if (b.m_state == 1 && b.m_value.first == k) { found = &b; break; }
        }
        if (!found) { t.fail("key %u not found by host probing", k); continue; }
        t.expect_eq(found->m_value.second, (u64)k * 3 + 1, "value");
        // The guest's operator[] on an existing key returns the same value slot.
        u64* again = (u64*)t.call(index, {(u64)&m, (u64)&k});
        t.expect_eq((u64)again, (u64)&found->m_value.second, "operator[] result = &bucket.m_value.second");
    }
    t.expect_eq(m.table.m_size, (u32)keys.size(), "lookups don't insert");
    t.call("_ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEED2Ev", {(u64)&m});
    t.expect_eq((u64)m.table.m_buckets.m_data, (u64)0, "dtor frees the buckets");
    t.expect_eq(m.table.m_size, 0u, "dtor clears m_size");
}

// TAddressManager<AddressNode>: constructed as MappedMemoryManager::MappedMemoryManager inlines it
// (vtable TPoolLegacy, SecurePool, a 7-slot table from new[], vtable TAddressManager), filled with
// Register; the host walks the node list, the pool and the bucket trees.
NATIVE_TEST("containers/layout-taddressmanager") {
    TAddressManagerAddressNode a;
    std::memset(&a, 0, sizeof a);
    auto& tree = a.base.base;
    auto& pool = tree.base;
    pool.vtable = vtable_of(t, "_ZTVN4Aska11TPoolLegacyINS_11AddressNodeELb0EEE");
    pool.m_used.vtable = vtable_of(t, "_ZTVN4Aska9TBitArrayIjLb0EEE");
    const u32 kPool = 16, kTable = 7;
    u64 ok = t.call("_ZN4Aska11TPoolLegacyINS_11AddressNodeELb0EE10SecurePoolEjbPKvPKj", {(u64)&pool, kPool, 0, 0, 0});
    t.expect_eq(ok & 1, (u64)1, "SecurePool");
    t.expect_eq(pool.m_used.m_numBits, kPool, "pool capacity (m_used.m_numBits)");
    t.expect_eq(pool.m_used.m_numWords, 1u, "m_used.m_numWords");
    t.expect_eq((int)pool.m_used.m_ownsBits, 1, "m_used.m_ownsBits");
    t.expect_eq((int)pool.m_ownsPool, 1, "m_ownsPool");
    if (!pool.m_pool || !pool.m_used.m_bits) { t.fail("SecurePool allocated nothing"); return; }
    pool.vtable = vtable_of(t, "_ZTVN4Aska15TAddressManagerINS_11AddressNodeEEE");
    tree.m_table = (AddressNode**)guest::new_array_nothrow(kTable * 8);
    std::memset(tree.m_table, 0, kTable * 8);
    tree.m_tableSize = kTable;
    tree.m_lastSlot = tree.m_table;

    // 20 keys: 16 from the pool, 4 from operator new (a full pool).
    std::vector<u64> keys;
    for (int i = 0; i < 20; i++) keys.push_back((t.rand_u64() & ~7ull) | 0x10);
    std::vector<AddressNode*> nodes;
    for (u64& k : keys) nodes.push_back((AddressNode*)t.call("_ZN4Aska15TAddressManagerINS_11AddressNodeEE8RegisterEPKv", {(u64)&a, (u64)&k}));
    t.expect_eq(tree.m_nodeCount, (u32)keys.size(), "m_nodeCount");
    t.expect_eq(pool.m_count, kPool, "pool slots taken (m_count)");
    t.expect_eq((u64)tree.m_head, (u64)nodes.front(), "m_head = first node");
    t.expect_eq((u64)tree.m_tail, (u64)nodes.back(), "m_tail = last node");
    const void* node_vt = vtable_of(t, "_ZTVN4Aska11AddressNodeE");
    u8* pool_lo = (u8*)pool.m_pool;
    u8* pool_hi = pool_lo + kPool * sizeof(AddressNode);
    for (size_t i = 0; i < nodes.size(); i++) {
        AddressNode* nd = nodes[i];
        u64 key;
        std::memcpy(&key, nd->base.m_key, 8);
        t.expect_eq(key, keys[i], "node key at +0x28");
        t.expect_eq(nd->base.vtable, node_vt, "node vtable");
        t.expect_eq((u64)nd->base.m_prev, i ? (u64)nodes[i - 1] : 0, "list m_prev");
        t.expect_eq((u64)nd->base.m_next, i + 1 < nodes.size() ? (u64)nodes[i + 1] : 0, "list m_next");
        bool in_pool = (u8*)nd >= pool_lo && (u8*)nd < pool_hi;
        t.expect_eq(in_pool, i < kPool, "the first 16 nodes are pool slots");
        if (in_pool) t.expect_eq(((u8*)nd - pool_lo) % sizeof(AddressNode), (size_t)0, "pool stride 0x30");
        // The bucket: the guest's CalcHashValue vs the host's fold; the host finds the node in that tree.
        u32 h = (u32)t.call("_ZNK4Aska15TAddressManagerINS_11AddressNodeEE13CalcHashValueEPKv", {(u64)&a, (u64)&keys[i]});
        u32 hh = 0;
        for (int b = 0; b < 8; b++) hh = (hh % kTable) * 8 + ((const u8*)&keys[i])[b];
        hh %= kTable;
        t.expect_eq(h, hh, "CalcHashValue");
        const TBinaryNode<8>* p = &tree.m_table[h]->base;
        while (p && (const void*)p != (const void*)nd) {
            u64 pk;
            std::memcpy(&pk, p->m_key, 8);
            p = keys[i] < pk ? p->m_left : p->m_right;
        }
        t.expect_eq((u64)p, (u64)nd, "node reachable in its bucket's tree (m_left / m_right)");
        t.expect_eq(t.call("_ZN4Aska15TAddressManagerINS_11AddressNodeEE12IsRegisteredEPKv", {(u64)&a, (u64)&keys[i]}) & 0xff, (u64)1, "IsRegistered");
    }
    u32 bits = pool.m_used.m_bits[0];
    t.expect_eq(bits, 0xffffu, "m_used bits: 16 slots taken");
    // ~THash (D2): FreeTable (nodes back to the pool / deleted, the table deleted), ~TBinaryTree
    // (the pool and its bits deleted).
    t.call("_ZN4Aska5THashINS_11AddressNodeEED2Ev", {(u64)&a});
    t.expect_eq(tree.m_nodeCount, 0u, "dtor: m_nodeCount");
    t.expect_eq((u64)tree.m_table, (u64)0, "dtor: m_table");
    t.expect_eq((u64)pool.m_used.m_bits, (u64)0, "dtor: m_used.m_bits");
}

NATIVE_TEST("containers/layout-tbitarray") {
    TBitArrayU32 b;
    std::memset(&b, 0, sizeof b);
    b.vtable = vtable_of(t, "_ZTVN4Aska9TBitArrayIjLb0EEE");
    t.call("_ZN4Aska9TBitArrayIjLb0EE5AllocEjPKj", {(u64)&b, 100, 0});
    t.expect_eq(b.m_numWords, 4u, "m_numWords");
    t.expect_eq(b.m_numBits, 100u, "m_numBits");
    t.expect_eq((int)b.m_ownsBits, 1, "m_ownsBits");
    if (!b.m_bits) { t.fail("no bits"); return; }
    t.expect_eq(b.m_bits[0] | b.m_bits[3], 0u, "cleared");
    // With the caller's storage: not owned.
    u32 mine[2] = {~0u, ~0u};
    t.call("_ZN4Aska9TBitArrayIjLb0EE5AllocEjPKj", {(u64)&b, 40, (u64)mine});
    t.expect_eq((u64)b.m_bits, (u64)mine, "caller's storage");
    t.expect_eq((int)b.m_ownsBits, 0, "not owned");
    t.expect_eq(mine[0] | mine[1], 0u, "storage cleared");
    t.call("_ZN4Aska9TBitArrayIjLb0EED2Ev", {(u64)&b});
}

NATIVE_TEST("containers/layout-tpoolfast") {
    TPoolFastVector p;
    std::memset(&p, 0, sizeof p);
    p.vtable = vtable_of(t, "_ZTVN4Aska9TPoolFastINS_6VectorELb0EEE");
    t.call("_ZN4Aska9TPoolFastINS_6VectorELb0EE10SecurePoolEjPS1_", {(u64)&p, 100, 0});
    if (!p.m_pool || !p.m_used.m_bits) { t.fail("SecurePool allocated nothing"); return; }
    t.expect_eq((int)p.m_ownsPool, 1, "m_ownsPool");
    t.expect_eq(p.m_used.m_numWords, 2u, "m_used.m_numWords (64-bit words)");
    t.expect_eq(p.m_used.m_numBits, 100u, "m_used.m_numBits");
    t.expect_eq((int)p.m_used.m_ownsBits, 1, "m_used.m_ownsBits");
    const char* scoop = "_ZN4Aska9TPoolFastINS_6VectorELb0EE5ScoopEi";
    u64 a = t.call(scoop, {(u64)&p, 3});
    t.expect_eq(a, (u64)&p.m_pool[0], "Scoop(3) = slot 0");
    u64 b = t.call(scoop, {(u64)&p, 5});
    t.expect_eq(b, (u64)&p.m_pool[3], "Scoop(5) = slot 3 (16-byte elements)");
    t.expect_eq(p.m_count, 8u, "m_count");
    t.expect_eq(p.m_cursor, 8u, "m_cursor");
    t.expect_eq(p.m_used.m_bits[0], (u64)0xff, "used bits");
    t.call("_ZN4Aska9TPoolFastINS_6VectorELb0EED2Ev", {(u64)&p});
    t.expect_eq((u64)p.m_pool, (u64)0, "dtor: m_pool");
    t.expect_eq((u64)p.m_used.m_bits, (u64)0, "dtor: m_used.m_bits");
}

// TArray<unsigned, false>: the constructor MasterNpcBaseParameterModel::GetParameter inlines, then its
// push pattern (Resize(size + 1); m_data[size] = v).
NATIVE_TEST("containers/layout-tarray") {
    TArrayU32 a;
    std::memset(&a, 0, sizeof a);
    a.vtable = vtable_of(t, "_ZTVN4Aska6TArrayIjLb0EEE");
    a.m_minCapacity = 8;
    std::vector<s64> caps;
    for (u32 i = 0; i < 20; i++) {
        t.call("_ZN4Aska6TArrayIjLb0EE6ResizeElb", {(u64)&a, (u64)(a.m_size + 1), 0});
        if (!a.m_data) { t.fail("Resize allocated nothing"); return; }
        a.m_data[a.m_size - 1] = i * 7 + 1;
        if (caps.empty() || caps.back() != a.m_capacity) caps.push_back(a.m_capacity);
    }
    t.expect_eq(a.m_size, (s64)20, "m_size");
    t.expect_eq(caps, (std::vector<s64>{8, 18, 38}), "m_capacity: max(n, m_minCapacity), then 2n");
    for (u32 i = 0; i < 20; i++) t.expect_eq(a.m_data[i], i * 7 + 1, "elements kept across reallocation");
    t.expect_eq((int)(a.m_flags & 1), 0, "m_flags: no allocation failure");
    t.call("_ZN4Aska6TArrayIjLb0EED2Ev", {(u64)&a});
    t.expect_eq((u64)a.m_data, (u64)0, "dtor: m_data");
    t.expect_eq(a.m_size, (s64)0, "dtor: m_size");
    t.expect_eq((int)(a.m_flags2 & 1), 1, "dtor sets m_flags2 bit 0");
}

// TDynamicArray<unsigned, TAllocator<unsigned>>: Insert_(pos, n, TUninitializedFillN{n, &value}) at the
// end, twice (the second reallocates: capacity max(size + n, 2 * capacity)).
NATIVE_TEST("containers/layout-tdynamicarray") {
    TDynamicArrayU32 d;
    std::memset(&d, 0, sizeof d);
    d.vtable = vtable_of(t, "_ZTVN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEEE");
    const char* insert = "_ZN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEE7Insert_INS_6Memory19TUninitializedFillNIjEEEENS_14TArrayIteratorIS3_EEPKjmRKT_";
    u32 v1 = 0x11111111, v2 = 0x22222222;
    struct { u64 n; const u32* value; } fill1{3, &v1}, fill2{2, &v2};
    u64 it = t.call(insert, {(u64)&d, (u64)d.m_end, 3, (u64)&fill1});
    if (!d.m_begin) { t.fail("Insert_ allocated nothing"); return; }
    t.expect_eq(it, (u64)d.m_begin, "Insert_ returns the position (new storage)");
    t.expect_eq((u64)(d.m_end - d.m_begin), (u64)3, "m_end - m_begin");
    t.expect_eq((u64)(d.m_capEnd - d.m_begin), (u64)3, "m_capEnd - m_begin");
    t.call(insert, {(u64)&d, (u64)d.m_end, 2, (u64)&fill2});
    t.expect_eq((u64)(d.m_end - d.m_begin), (u64)5, "m_end after the second insert");
    t.expect_eq((u64)(d.m_capEnd - d.m_begin), (u64)6, "m_capEnd: 2x capacity");
    std::vector<u32> got(d.m_begin, d.m_end);
    t.expect_eq(got, (std::vector<u32>{v1, v1, v1, v2, v2}), "elements");
    t.call("_ZN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEED2Ev", {(u64)&d});
    t.expect_eq((u64)d.m_begin | (u64)d.m_end | (u64)d.m_capEnd, (u64)0, "dtor clears");
}

// TStack<unsigned, 10>: the D2 puts m_data back on the inline storage (deleting a grown buffer) and
// resets {capacity, top} to {10, -1}.
NATIVE_TEST("containers/layout-tstack") {
    TStackU32x10 s;
    std::memset(&s, 0, sizeof s);
    s.vtable = vtable_of(t, "_ZTVN4Aska6TStackIjLi10EEE");
    s.m_data = (u32*)guest::new_array_nothrow(64 * 4);
    s.m_capacity = 64;
    s.m_top = 12;
    t.call("_ZN4Aska6TStackIjLi10EED2Ev", {(u64)&s});
    t.expect_eq((u64)s.m_data, (u64)s.m_inline, "m_data = the inline storage at +0x08");
    t.expect_eq(s.m_capacity, 10u, "m_capacity = N");
    t.expect_eq(s.m_top, -1, "m_top = -1");
    u32 src = 0x12345678, dst = 0;
    t.call("_ZN4Aska6TStackIjLi10EE11CopyElementEPKjPj", {(u64)&s, (u64)&src, (u64)&dst});
    t.expect_eq(dst, src, "CopyElement");
}

NATIVE_TEST("containers/layout-ringbuffer") {
    RingBuffer r;
    std::memset(&r, 0, sizeof r);
    alignas(16) u8 buf[64];
    std::memset(buf, 0, sizeof buf);
    t.expect_eq(t.call("_ZN4Aska10RingBuffer4OpenEPKvm", {(u64)&r, (u64)buf, sizeof buf}) & 0xff, (u64)1, "Open");
    t.expect_eq((u64)r.m_buffer, (u64)buf, "m_buffer");
    t.expect_eq(r.m_size, (u64)64, "m_size");
    t.expect_eq((u64)r.m_owned.m_ptr, (u64)0, "not owned");
    u8 one[10], two[5], out[10];
    for (int i = 0; i < 10; i++) one[i] = (u8)(0xa0 + i);
    for (int i = 0; i < 5; i++) two[i] = (u8)(0x10 + i);
    // PushBack on an empty buffer (m_back 0) has no room below m_back: 0 bytes.
    t.expect_eq(t.call("_ZN4Aska10RingBuffer8PushBackEPKvm", {(u64)&r, (u64)one, 10}), (u64)0, "PushBack at m_back 0");
    t.expect_eq(t.call("_ZN4Aska10RingBuffer9PushFrontEPKvm", {(u64)&r, (u64)one, 10}), (u64)10, "PushFront");
    t.expect_eq(t.call("_ZN4Aska10RingBuffer9PushFrontEPKvm", {(u64)&r, (u64)two, 5}), (u64)5, "PushFront 2");
    t.expect_eq(r.m_front, (u64)15, "m_front moves up");
    t.expect_eq(std::memcmp(buf, one, 10) | std::memcmp(buf + 10, two, 5), 0, "bytes written at m_buffer + m_front");
    t.expect_eq(r.m_used, 15, "m_used");
    t.expect_eq(t.call("_ZN4Aska10RingBuffer7PopBackEPvm", {(u64)&r, (u64)out, 10}), (u64)10, "PopBack");
    t.expect_eq(std::memcmp(out, one, 10), 0, "PopBack reads at m_buffer + m_back");
    t.expect_eq(r.m_back, (u64)10, "m_back moves up");
    t.expect_eq(r.m_used, 5, "m_used after PopBack");
    void* where = nullptr;
    u64 n = t.call("_ZNK4Aska10RingBuffer20PrivatePeepPushFrontEPPvm", {(u64)&r, (u64)&where, 4});
    t.expect_eq(n, (u64)4, "PrivatePeepPushFront");
    t.expect_eq((u64)where, (u64)(buf + 15), "PrivatePeepPushFront: m_buffer + m_front");
    t.call("_ZN4Aska10RingBuffer5ResetEv", {(u64)&r});
    t.expect_eq(r.m_front | r.m_back | (u64)r.m_used, (u64)0, "Reset");
    t.call("_ZN4Aska10RingBuffer5CloseEv", {(u64)&r});
    t.expect_eq((u64)r.m_buffer | r.m_size, (u64)0, "Close");
}

NATIVE_TEST("containers/layout-tlist") {
    TListLink l;
    std::memset(&l, 0, sizeof l);
    l.m_sentinel.m_prev = l.m_sentinel.m_next = &l.m_sentinel;
    LinkElement e[3];
    std::memset(e, 0, sizeof e);
    for (auto& x : e) t.call("_ZN4Aska5TListINS_11LinkElementEE3AddEPS1_", {(u64)&l, (u64)&x});
    t.expect_eq(l.m_count, 3, "m_count");
    t.expect_eq((u64)l.m_sentinel.m_next, (u64)&e[0], "sentinel.m_next = first");
    t.expect_eq((u64)l.m_sentinel.m_prev, (u64)&e[2], "sentinel.m_prev = last");
    t.expect_eq((u64)e[0].m_next, (u64)&e[1], "e0.m_next");
    t.expect_eq((u64)e[1].m_prev, (u64)&e[0], "e1.m_prev");
    t.expect_eq((u64)e[2].m_next, (u64)&l.m_sentinel, "e2.m_next = sentinel");
    t.expect_eq((u64)e[0].m_prev, (u64)&l.m_sentinel, "e0.m_prev = sentinel");
    t.call("_ZN4Aska5TListINS_11LinkElementEE6DeleteEPS1_", {(u64)&l, (u64)&e[1]});
    t.expect_eq(l.m_count, 2, "Delete: m_count");
    t.expect_eq((u64)e[0].m_next, (u64)&e[2], "Delete: relinked");
    t.expect_eq((u64)e[1].m_next | (u64)e[1].m_prev, (u64)0, "Delete: links cleared");
}

// THierarchy<CTimeElement>::DetachSelf: B (with child D) leaves parent A (children B, C); D moves to A.
NATIVE_TEST("containers/layout-thierarchy") {
    struct alignas(16) Node {
        THierarchyOpaque h;
        u8 rest[0x40];
    };
    Node n[4];
    std::memset(n, 0, sizeof n);
    auto* A = &n[0].h;
    auto* B = &n[1].h;
    auto* C = &n[2].h;
    auto* D = &n[3].h;
    A->m_firstChild = (Opaque<8>*)B;
    B->m_parent = (Opaque<8>*)A;
    B->m_nextSibling = (Opaque<8>*)C;
    C->m_parent = (Opaque<8>*)A;
    B->m_firstChild = (Opaque<8>*)D;
    D->m_parent = (Opaque<8>*)B;
    B->unk_20 = 0x1234;
    t.call("_ZN9Framework10THierarchyINS_12CTimeElementEE10DetachSelfEPS1_", {(u64)B, (u64)B});
    t.expect_eq((u64)A->m_firstChild, (u64)C, "A's first child = C");
    t.expect_eq((u64)C->m_nextSibling, (u64)D, "D appended to A's children");
    t.expect_eq((u64)D->m_parent, (u64)A, "D's parent = A");
    t.expect_eq((u64)B->m_parent | (u64)B->m_nextSibling | (u64)B->m_firstChild | B->unk_20, (u64)0, "B unlinked, +0x20 cleared");
}

}  // namespace soa::native::containers
