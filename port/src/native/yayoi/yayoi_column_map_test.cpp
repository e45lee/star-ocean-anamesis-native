// Differential test of the column map's THashMap<char const*, int, StringHasher, StringEqualTo>
// members (yayoi_column_map.cpp) against the 3.7.0 guest: each side builds its maps (an EntityObject's,
// so the guest constructor made them) and runs the same calls; the maps' states (every bucket) and the
// results are logged and compared (yayoi_sqlite_test_util.h).
#include <cmath>

#include "native/yayoi/yayoi_sqlite_test_util.h"

namespace soa::native::yayoi {
namespace {

using namespace test;

const char* key(int i) {
    static std::vector<std::string> keys = [] {
        std::vector<std::string> v;
        for (int k = 0; k < 200; k++) v.push_back(fmt("column_%d%s", k, k % 7 ? "" : "_long_name_for_the_hash"));
        return v;
    }();
    return keys[(size_t)i].c_str();
}

std::string insert_text(const ColumnMapInsertResult& r) {
    return fmt("it %td/%td inserted %d", r.m_it.m_bucket - r.m_it.m_begin, r.m_it.m_end - r.m_it.m_begin, r.m_inserted);
}

ColumnMapInsertResult emplace(Side& s, ColumnMap* m, const char* k) {
    ColumnMapInsertResult r{};
    GuestArgs a;
    a.p(m).p(&k).sret(&r);
    guest_call(s.fn(MAP "8Emplace_ERSA_"), a);
    return r;
}
ColumnMapInsertResult insert(Side& s, ColumnMap* m, const char* k, s32 v) {
    ColumnMapInsertResult r{};
    ColumnPair p{k, v};
    GuestArgs a;
    a.p(m).p(&p).sret(&r);
    guest_call(s.fn(MAP "7Insert_ERKSB_"), a);
    return r;
}
void rehash(Side& s, ColumnMap* m, u64 n) { s.call(MAP "7Rehash_Em", {(u64)m, n}); }
void range_insert(Side& s, ColumnMap* m, const ColumnMap& from) {
    ColumnBucket* b = from.table.m_buckets.m_data;
    ColumnBucket* e = b + from.table.m_buckets.m_count;
    ColumnMapIterator first{b, b, e}, last{e, b, e};
    while (first.m_bucket != e && first.m_bucket->m_state != 1) ++first.m_bucket;
    s.call(MAP "6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSG_14THashMapBucketISB_EENS8_ISJ_EEEEEEEEvT_SN_",
           {(u64)m, (u64)&first, (u64)&last});
}

void script(Side& s) {
    u64 e1 = s.new_entity(), e2 = s.new_entity(), e3 = s.new_entity();
    ColumnMap* a = &((EntityObject*)e1)->m_columns;
    ColumnMap* b = &((EntityObject*)e2)->m_columns;
    ColumnMap* c = &((EntityObject*)e3)->m_columns;
    s.add(map_state(*a));
    // Emplace_ past a full table (17 buckets, no growth here): the end iterator once full
    for (int i = 0; i < 20; i++) {
        ColumnMapInsertResult r = emplace(s, a, key(i));
        if (r.m_inserted) r.m_it.m_bucket->m_value.second = i * 10;
        s.add(fmt("emplace %d ", i) + insert_text(r));
    }
    s.add(map_state(*a));
    s.add("again " + insert_text(emplace(s, a, key(3))) + " " + insert_text(insert(s, a, key(4), 99)));
    // deleted buckets: a new key takes the first one on its probe
    for (u64 i = 0; i < a->table.m_buckets.m_count; i += 3)
        if (a->table.m_buckets.m_data[i].m_state == 1) {
            a->table.m_buckets.m_data[i].m_state = 2;
            a->table.m_size--;
            a->table.m_deleted++;
        }
    s.add("deleted " + map_state(*a));
    for (int i = 40; i < 46; i++) s.add(fmt("insert %d ", i) + insert_text(insert(s, a, key(i), i)));
    s.add(map_state(*a));
    // Rehash_: bigger, odd sizes, then down to 0 buckets (the range insert grows the temporary)
    rehash(s, a, 37);
    s.add("rehash 37 " + map_state(*a));
    rehash(s, a, 5);
    s.add("rehash 5 " + map_state(*a));
    rehash(s, a, 0);
    s.add("rehash 0 " + map_state(*a));
    // the range insert from another map (growing this one)
    for (int i = 100; i < 160; i++) {
        b->GrowFor(1);  // (b's growth by the native helper on both sides: b is only the source)
        ColumnMapInsertResult r = emplace(s, b, key(i));
        r.m_it.m_bucket->m_value.second = i;
    }
    s.add("b " + map_state(*b));
    range_insert(s, c, *b);
    s.add("c " + map_state(*c));
    range_insert(s, c, *a);
    s.add("c+a " + map_state(*c));
    // load factors: not positive (the temporary keeps 0.75), NaN (kept; no growth)
    c->table.m_maxLoadFactor = -1.0f;
    rehash(s, c, 11);
    s.add("load -1 " + map_state(*c));
    c->table.m_maxLoadFactor = std::nanf("");
    rehash(s, c, 300);
    range_insert(s, c, *b);
    s.add("load nan " + map_state(*c));
    // ~THashMap (D2) on a map, then D0 on one from operator new
    s.call(MAP "D2Ev", {(u64)b});
    s.add("dtor " + map_state(*b));
    {
        static const u64 op_new = guest::sym("_Znwm");
        auto* m = (ColumnMap*)guest_call(op_new, {sizeof(ColumnMap)});
        std::memset(m, 0, sizeof *m);
        m->table.vtable = column_map_vtable();
        m->table.m_maxLoadFactor = 0.75f;
        m->table.m_buckets.m_data = (ColumnBucket*)gfn::aligned_malloc(17 * sizeof(ColumnBucket), 8);
        m->table.m_buckets.m_count = 17;
        s.call(MAP "D0Ev", {(u64)m});
        s.add("D0 done");
    }
    s.delete_entity(e1);
    s.delete_entity(e2);
    s.delete_entity(e3);
}

}  // namespace

NATIVE_TEST("yayoi/column-map") {
    Side g{"guest", false, {}}, n{"native", true, {}};
    script(g);
    script(n);
    same_logs(t, g, n, "column map");
    t.expect_eq(g.log.size() > 30, true, "the script ran");
}

}  // namespace soa::native::yayoi
