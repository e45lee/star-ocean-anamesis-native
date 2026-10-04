// Aska::THashMap<char const*, int, EntityObject::StringHasher, EntityObject::StringEqualTo, ...>: the
// EntityObject's column-name map (ColumnMap in yayoi_layout.h), from the Ghidra decompile
// (port/decomp/yayoi/sqlite_driver.c). Open addressing over containers' bucket layout; keys are
// SQLite's column-name pointers, hashed by SpookyHash V2 (the hash subsystem's native) and compared
// with strcmp.
#include <cmath>
#include <cstring>

#include "native/hash/hash_layout.h"
#include "native/yayoi/yayoi_guest.h"
#include "native/yayoi/yayoi_layout.h"
#include "native/yayoi/yayoi_sqlite.h"

namespace soa::native::yayoi {

namespace {
constexpr u8 kEmpty = 0, kUsed = 1, kDeleted = 2;
// operator new's limit for n buckets of 0x18 (Rehash_: n < 0xaaaaaaaaaaaaaab, else no allocation)
constexpr u64 kMaxBuckets = 0xaaaaaaaaaaaaaabull;
}  // namespace

u64 fcvtpu(float f) {
    // FCVTPU (float -> u64, toward +infinity): NaN and anything <= -1 give 0, too large saturates.
    if (std::isnan(f)) return 0;
    f = std::ceil(f);
    if (f <= 0.0f) return 0;
    if (f >= 18446744073709551616.0f) return ~0ull;
    return (u64)f;
}

u64 ColumnMap::Hash(const char* key) {
    u64 h1 = 0, h2 = 0;
    hash::SpookyHashV2::Hash128(key, std::strlen(key), &h1, &h2);
    return h1;
}

const void* column_map_vtable() {
    static const u64 vt = guest::sym("_ZTVN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEEE") + 0x10;
    return (const void*)vt;
}

ColumnBucket* ColumnMap::Find(const char* key) const {
    ColumnBucket* data = table.m_buckets.m_data;
    u64 count = table.m_buckets.m_count;
    if (count) {
        u64 h = Hash(key);
        for (u64 i = 0; i < count; i++) {
            ColumnBucket* b = &data[(h + i) % count];
            if (b->m_state == kUsed) {
                if (std::strcmp(b->m_value.first, key) == 0) return b;
            } else if (b->m_state == kEmpty) {
                break;
            }
        }
    }
    return end();
}

void ColumnMap::GrowFor(u64 extra) {
    u64 need = fcvtpu((float)((u64)table.m_size + (u64)table.m_deleted + extra) / table.m_maxLoadFactor);
    if (table.m_buckets.m_count < need) Rehash_(need << 1 | 1);
}

// Emplace_ and Insert_ share the probe: the key's bucket when present (not inserted), else the first
// deleted bucket on the way or the empty bucket that ends the probe; a full table without either
// inserts nothing (the end iterator).
namespace {
ColumnMapInsertResult place(ColumnMap* m, const char* key, const s32* value) {
    ColumnBucket* data = m->table.m_buckets.m_data;
    u64 count = m->table.m_buckets.m_count;
    ColumnBucket* target = nullptr;
    if (count) {
        u64 h = ColumnMap::Hash(key);
        ColumnBucket* tomb = nullptr;
        for (u64 i = 0; i < count; i++) {
            ColumnBucket* b = &data[(h + i) % count];
            if (b->m_state == kUsed) {
                if (std::strcmp(b->m_value.first, key) == 0) return {{b, data, data + count}, 0, {}};
            } else if (b->m_state == kEmpty) {
                target = tomb ? tomb : b;
                break;
            } else if (b->m_state == kDeleted && !tomb) {
                tomb = b;
            }
        }
        if (!target) target = tomb;
    }
    if (!target) {
        data = m->table.m_buckets.m_data;
        ColumnBucket* e = data + m->table.m_buckets.m_count;
        return {{e, data, e}, 0, {}};
    }
    target->m_value.first = key;
    if (value) target->m_value.second = *value;
    if (target->m_state == kEmpty) {
        m->table.m_size++;
    } else if (target->m_state == kDeleted) {
        m->table.m_deleted--;
        m->table.m_size++;
    }
    target->m_state = kUsed;
    return {{target, data, data + m->table.m_buckets.m_count}, 1, {}};
}

// The iterator's ++: the next used bucket, or the end.
void advance(ColumnMapIterator* it) {
    do {
        if (it->m_bucket == it->m_end) return;
        ++it->m_bucket;
    } while (it->m_bucket != it->m_end && it->m_bucket->m_state != kUsed);
}
}  // namespace

ColumnMapInsertResult ColumnMap::Emplace_(const char* const* key) { return place(this, *key, nullptr); }

ColumnMapInsertResult ColumnMap::Insert_(const ColumnPair* pair) { return place(this, pair->first, &pair->second); }

void ColumnMap::Insert(ColumnMapIterator* first, const ColumnMapIterator* last) {
    u64 n = 0;
    if (first->m_bucket != last->m_bucket) {
        ColumnMapIterator it = *first;
        do {
            n++;
            advance(&it);
        } while (it.m_bucket != last->m_bucket);
    }
    u64 need = fcvtpu((float)(n + (u64)table.m_size + (u64)table.m_deleted) / table.m_maxLoadFactor);
    if (need > table.m_buckets.m_count) Rehash_(need << 1 | 1);
    while (first->m_bucket != last->m_bucket) {
        Insert_(&first->m_bucket->m_value);
        advance(first);
    }
}

void ColumnMap::Rehash_(u64 count) {
    ColumnMap tmp;
    std::memset(&tmp, 0, sizeof tmp);  // (the guest's stack temporary: only the fields below are set)
    tmp.table.vtable = column_map_vtable();
    tmp.table.m_maxLoadFactor = 0.75f;
    ColumnBucket* buckets = count < kMaxBuckets ? (ColumnBucket*)gfn::aligned_malloc(count * sizeof(ColumnBucket), 8) : nullptr;
    if (!buckets) count = 0;
    for (u64 i = 0; i < count; i++) buckets[i].m_state = kEmpty;
    tmp.table.m_buckets.m_data = buckets;
    tmp.table.m_buckets.m_count = count;
    // The temporary takes this map's load factor when it is positive (FCMP 0, load; B.PL: a NaN or
    // a load <= 0 keeps 0.75).
    if (table.m_maxLoadFactor > 0.0f) tmp.table.m_maxLoadFactor = table.m_maxLoadFactor;

    ColumnBucket* b = table.m_buckets.m_data;
    ColumnBucket* e = b + table.m_buckets.m_count;
    ColumnMapIterator first{e, b, e}, last{e, b, e};
    if (table.m_size != 0) {
        first.m_bucket = b;
        while (first.m_bucket != e && first.m_bucket->m_state != kUsed) ++first.m_bucket;
    }
    tmp.Insert(&first, &last);

    std::swap(table.m_size, tmp.table.m_size);
    std::swap(table.m_deleted, tmp.table.m_deleted);
    std::swap(table.m_buckets.m_data, tmp.table.m_buckets.m_data);
    std::swap(table.m_buckets.m_count, tmp.table.m_buckets.m_count);
    std::swap(table.m_maxLoadFactor, tmp.table.m_maxLoadFactor);
    if (tmp.table.m_buckets.m_data) gfn::aligned_free(tmp.table.m_buckets.m_data);
}

void ColumnMap::Dtor() {
    table.vtable = column_map_vtable();
    if (table.m_buckets.m_data) {
        gfn::aligned_free(table.m_buckets.m_data);
        table.m_buckets.m_data = nullptr;
        table.m_buckets.m_count = 0;
    }
    table.m_size = 0;
    table.m_deleted = 0;
}

void ColumnMap::DtorDelete() {
    table.vtable = column_map_vtable();
    if (table.m_buckets.m_data) gfn::aligned_free(table.m_buckets.m_data);
    gfn::operator_delete(this);
}

}  // namespace soa::native::yayoi
