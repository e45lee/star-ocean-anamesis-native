// Layout tests of data_formats_layout.h (types first, port/PLAN.md task 6): every recovered offset is
// read on real guest objects the guest's own code built, and compared with what the guest's accessors
// return (or with the input the guest parsed). No natives are bound: these tests prove the layouts the
// code agents build on. They run in `soa --selftest data_formats/` (natives off, t.call reaches the guest).
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "native/api/client_battle_log.h"
#include "native/common/guest_std.h"
#include "native/common/guest_stub.h"
#include "native/common/test.h"
#include "native/data_formats/data_formats_layout.h"

namespace soa::native::data_formats {
namespace {

// A host buffer for a guest object (identity-mapped memory; the guest's own new[] / delete[] manage
// what the object allocates).
template <typename T>
struct Obj {
    alignas(16) unsigned char raw[sizeof(T) + 0x40] = {};
    T* get() { return reinterpret_cast<T*>(raw); }
    u64 addr() { return (u64)raw; }
};

u64 vtable_of(TestContext& t, const char* ztv) { return t.sym(ztv) + 0x10; }

// ---- a msgpack writer for the inputs ------------------------------------------------------------------
struct Mp {
    std::vector<u8> b;
    Mp& raw(std::initializer_list<u8> v) { b.insert(b.end(), v); return *this; }
    Mp& be(u64 v, int n) { for (int i = n - 1; i >= 0; i--) b.push_back((u8)(v >> (8 * i))); return *this; }
    Mp& map(u32 n) { return n < 16 ? raw({(u8)(0x80 | n)}) : raw({0xde}).be(n, 2); }
    Mp& arr(u32 n) { return n < 16 ? raw({(u8)(0x90 | n)}) : raw({0xdc}).be(n, 2); }
    Mp& str(const std::string& s) {
        if (s.size() < 32) raw({(u8)(0xa0 | s.size())});
        else raw({0xd9, (u8)s.size()});
        b.insert(b.end(), s.begin(), s.end());
        return *this;
    }
    Mp& uint(u64 v) { return v < 128 ? raw({(u8)v}) : raw({0xcf}).be(v, 8); }
    Mp& sint(s64 v) { return v >= -32 ? raw({(u8)(s8)v}) : raw({0xd3}).be((u64)v, 8); }
    Mp& f64(double d) { u64 u; std::memcpy(&u, &d, 8); return raw({0xcb}).be(u, 8); }
    Mp& f32(float f) { u32 u; std::memcpy(&u, &f, 4); return raw({0xca}).be(u, 4); }
    Mp& bin(std::initializer_list<u8> v) { raw({0xc4, (u8)v.size()}); return raw(v); }
    Mp& fixext1(s8 type, u8 v) { return raw({0xd4, (u8)type, v}); }
};

std::string body_str(const AValue& v) { return std::string(v.m_body.str.m_data ? v.m_body.str.m_data : "", v.m_length); }

// Guest Init / ctor / dtor of an ASON.
struct GuestAson {
    TestContext& t;
    Obj<ASON> o;
    explicit GuestAson(TestContext& tc, u32 work = 0x2000, bool keep = true) : t(tc) {
        t.call("_ZN4Aska4ASONC1Ev", {o.addr()});
        s64 r = (s64)t.call("_ZN4Aska4ASON4InitEjb", {o.addr(), work, keep ? 1u : 0u});
        if (r != 0) t.fail("ASON::Init(%#x) = %lld", work, (long long)r);
    }
    ~GuestAson() { t.call("_ZN4Aska4ASOND1Ev", {o.addr()}); }
    ASON* operator->() { return o.get(); }
    s64 deserialize(const std::vector<u8>& in) {
        return (s64)t.call("_ZN4Aska4ASON17DeserializeBinaryEPKvm", {o.addr(), (u64)in.data(), (u64)in.size()});
    }
};

// ---- ASON: the object and its allocator ----------------------------------------------------------------
NATIVE_TEST("data_formats/layout-ason-object") {
    Obj<ASON> o;
    ASON* a = o.get();
    t.call("_ZN4Aska4ASONC1Ev", {o.addr()});
    t.expect_eq((u64)a->vtable, vtable_of(t, "_ZTVN4Aska4ASONE"), "ASON::vtable");
    t.expect_eq((u64)a->m_work.vtable,
                vtable_of(t, "_ZTVN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEEE"),
                "ASON::m_work.vtable");
    t.expect_eq(a->m_initialized, false, "ASON::m_initialized before Init");
    t.expect_eq((s64)t.call("_ZN4Aska4ASON4InitEjb", {o.addr(), 0x3000, 1}), (s64)0, "ASON::Init");
    t.expect_eq(a->m_initialized, true, "ASON::m_initialized");
    t.expect_eq(a->m_keepCStrings, true, "ASON::m_keepCStrings");
    t.expect_eq(a->m_work.m_end - a->m_work.m_begin, (long)1, "one work block");
    t.expect_eq(a->m_work.m_capEnd - a->m_work.m_begin, (long)4, "4 reserved blocks (AlignedMalloc(0x80))");
    t.expect_eq(a->m_currentWork, a->m_work.m_begin, "ASON::m_currentWork");
    t.expect_eq(a->m_totalWorkSize, (u64)0x3000, "ASON::m_totalWorkSize");
    t.expect_eq(a->m_currentWork->m_size, (u64)0x3000, "WorkBufferContext::m_size");
    t.expect_eq(a->m_currentWork->m_owned, true, "WorkBufferContext::m_owned");
    t.expect_eq(a->m_workIndex, (u16)0, "ASON::m_workIndex");
    // InitMemory took m_temp's 0x200 bytes from the block.
    t.expect_eq((u64)a->m_temp, (u64)a->m_currentWork->m_buffer, "ASON::m_temp is the block's first bytes");
    t.expect_eq(a->m_tempSize, (u64)0x200, "ASON::m_tempSize");
    t.expect_eq(a->m_tempUsed, (u64)0, "ASON::m_tempUsed");
    t.expect_eq(a->m_currentWork->m_used, (u64)0x200, "WorkBufferContext::m_used");
    t.expect_eq(a->m_root.m_kind, (u32)AValue::kNil, "ASON::m_root nil");

    // Malloc bumps the current block (rounded to 4).
    u64 used = a->m_currentWork->m_used;
    u64 p = t.call("_ZN4Aska4ASON6MallocEm", {o.addr(), 13});
    t.expect_eq(p, (u64)a->m_currentWork->m_buffer + used, "Malloc's result");
    t.expect_eq(a->m_currentWork->m_used, used + 16, "Malloc's bump");
    // A request over the block grows the allocator by m_totalWorkSize: a second block, m_workIndex 1.
    u64 big = t.call("_ZN4Aska4ASON6MallocEm", {o.addr(), 0x2f00});
    t.expect_eq(a->m_work.m_end - a->m_work.m_begin, (long)2, "a second work block");
    t.expect_eq(a->m_currentWork, a->m_work.m_begin + 1, "the new block is current");
    t.expect_eq(a->m_workIndex, (u16)1, "ASON::m_workIndex after growth");
    t.expect_eq(a->m_totalWorkSize, (u64)0x6000, "ASON::m_totalWorkSize after growth");
    t.expect_eq(big, (u64)a->m_currentWork->m_buffer, "the big block's first bytes");
    // TemporaryMalloc / TemporaryFree use m_temp.
    u64 tp = t.call("_ZN4Aska4ASON15TemporaryMallocEm", {o.addr(), 10});
    t.expect_eq(tp, (u64)a->m_temp, "TemporaryMalloc's result");
    t.expect_eq(a->m_tempUsed, (u64)12, "TemporaryMalloc's bump");
    t.call("_ZN4Aska4ASON13TemporaryFreeEPv", {o.addr(), tp});
    t.expect_eq(a->m_tempUsed, (u64)0, "TemporaryFree resets m_tempUsed");
    // An error lands in m_status: DeserializeBinary(nullptr) is a bad argument.
    t.call("_ZN4Aska4ASON17DeserializeBinaryEPKvm", {o.addr(), 0, 0});
    t.expect_eq(a->m_status.code, (s64)-0x3bd, "ASON::m_status (bad argument)");
    t.call("_ZN4Aska4ASON4TermEv", {o.addr()});
    t.expect_eq(a->m_initialized, false, "ASON::m_initialized after Term");
    t.expect_eq((u64)a->m_currentWork, (u64)0, "ASON::m_currentWork after Term");
    t.call("_ZN4Aska4ASOND1Ev", {o.addr()});
}

// ---- ASON: values the guest's msgpack reader built ------------------------------------------------------
NATIVE_TEST("data_formats/layout-ason-values") {
    const std::string longstr(40, 'x');
    Mp m;
    m.map(10)
        .str("name").str("abc")
        .str("n").uint(5)
        .str("big").uint(0x1234567890ull)
        .str("neg").sint(-3)
        .str("f64").f64(1.25)
        .str("f32").f32(-2.5f)
        .str("arr").arr(3).uint(1).raw({0xc3}).raw({0xc0})
        .str("bin").bin({1, 2, 3})
        .str("ext").fixext1(7, 0x42)
        .str("long").str(longstr);
    GuestAson a(t);
    s64 n = a.deserialize(m.b);
    t.expect_eq(n, (s64)m.b.size(), "DeserializeBinary's byte count");
    t.expect_eq(a->m_multiRoot, false, "ASON::m_multiRoot (one root)");
    const AValue& root = a->m_root;
    if (!t.expect_eq(root.m_kind, (u32)AValue::kMap, "root kind")) return;
    if (!t.expect_eq(root.m_body.map.m_count, (u32)10, "AMap::m_count")) return;
    const char* keys[] = {"name", "n", "big", "neg", "f64", "f32", "arr", "bin", "ext", "long"};
    AMap* map = const_cast<AMap*>(&root.m_body.map);
    for (u32 i = 0; i < 10; i++) {
        const ASON_Pair& p = map->m_pairs[i];
        t.expect_eq(p.key.m_kind, (u32)AValue::kString, "key kind");
        t.expect_eq(body_str(p.key), std::string(keys[i]), "key bytes (m_body.str.m_data, m_length)");
        t.expect_eq(std::string(p.key.m_body.str.m_cstr ? p.key.m_body.str.m_cstr : "(null)"), std::string(keys[i]),
                    "key C string (m_body.str.m_cstr)");
        // The guest's lookup by name returns this pair's value.
        u64 g = t.call("_ZN4Aska4ASON6AValue4AMap4Get_EPKc", {(u64)map, (u64)keys[i]});
        t.expect_eq(g, (u64)&p.value, "AMap::Get_(char const*) -> &pair.value");
        // And by AValue key.
        u64 g2 = t.call("_ZN4Aska4ASON6AValue4AMap4Get_EPKS1_", {(u64)map, (u64)&p.key});
        t.expect_eq(g2, (u64)&p.value, "AMap::Get_(AValue const*) -> &pair.value");
    }
    auto val = [&](u32 i) -> const AValue& { return map->m_pairs[i].value; };
    t.expect_eq(val(0).m_kind, (u32)AValue::kString, "name kind");
    t.expect_eq(body_str(val(0)), std::string("abc"), "name");
    t.expect_eq(val(1).m_kind, (u32)AValue::kUInt, "n kind");
    t.expect_eq(val(1).m_body.u, (u64)5, "n");
    t.expect_eq(val(2).m_body.u, (u64)0x1234567890ull, "big");
    t.expect_eq(val(3).m_kind, (u32)AValue::kSInt, "neg kind");
    t.expect_eq(val(3).m_body.s, (s64)-3, "neg");
    t.expect_eq(val(4).m_kind, (u32)AValue::kFloat, "f64 kind");
    t.expect_eq(val(4).m_body.d, 1.25, "f64");
    t.expect_eq(val(5).m_kind, (u32)AValue::kFloat, "f32 kind");
    t.expect_eq(val(5).m_body.d, -2.5, "f32 (widened)");
    const AValue& arr = val(6);
    t.expect_eq(arr.m_kind, (u32)AValue::kArray, "arr kind");
    if (t.expect_eq(arr.m_body.array.m_count, (u32)3, "AArray::m_count")) {
        t.expect_eq(arr.m_body.array.m_elements[0].m_body.u, (u64)1, "arr[0]");
        t.expect_eq(arr.m_body.array.m_elements[1].m_kind, (u32)AValue::kBool, "arr[1] kind");
        t.expect_eq(arr.m_body.array.m_elements[1].m_body.b, true, "arr[1]");
        t.expect_eq(arr.m_body.array.m_elements[2].m_kind, (u32)AValue::kNil, "arr[2] kind");
    }
    const AValue& bin = val(7);
    t.expect_eq(bin.m_kind, (u32)AValue::kBinary, "bin kind");
    t.expect_eq(bin.m_body.bin.m_size, (u32)3, "ASON_BinaryBody::m_size");
    if (bin.m_body.bin.m_data) t.expect_eq(bin.m_body.bin.m_data[2], (u8)3, "bin[2]");
    const AValue& ext = val(8);
    t.expect_eq(ext.m_kind, (u32)AValue::kExt, "ext kind");
    t.expect_eq(ext.m_body.bin.m_extType, (s8)7, "ASON_BinaryBody::m_extType");
    t.expect_eq(ext.m_body.bin.m_size, (u32)1, "ext size");
    if (ext.m_body.bin.m_data) t.expect_eq(ext.m_body.bin.m_data[0], (u8)0x42, "ext data");
    t.expect_eq(body_str(val(9)), longstr, "long string");
    // AValue::Get copies the body: kind 5 copies data, cstr and length (24 bytes).
    u64 out[4] = {};
    t.expect_eq((u32)t.call("_ZNK4Aska4ASON6AValue3GetEPv", {(u64)&val(9), (u64)out}) & 0xff, 1u, "AValue::Get");
    t.expect_eq(out[0], (u64)val(9).m_body.str.m_data, "Get: m_data");
    t.expect_eq(out[1], (u64)val(9).m_body.str.m_cstr, "Get: m_cstr");
    t.expect_eq((u32)out[2], val(9).m_length, "Get: m_length");

    // Round trip: the guest's writer, then its reader again; the trees match field by field.
    s64 size = (s64)t.call("_ZNK4Aska4ASON18CalcSerializedSizeEv", {a.o.addr()});
    std::vector<u8> buf((size_t)(size > 0 ? size : 1));
    s64 w = (s64)t.call("_ZNK4Aska4ASON9SerializeEPvm", {a.o.addr(), (u64)buf.data(), (u64)buf.size()});
    t.expect_eq(w, size, "Serialize's length == CalcSerializedSize");
    GuestAson b(t);
    t.expect_eq(b.deserialize(buf), w, "re-read byte count");
    t.expect_eq(b->m_root.m_body.map.m_count, (u32)10, "re-read map count");
    for (u32 i = 0; i < 10 && i < b->m_root.m_body.map.m_count; i++)
        t.expect_eq(body_str(b->m_root.m_body.map.m_pairs[i].key), std::string(keys[i]), "re-read key");

    // Two concatenated roots: m_multiRoot, the root an array of both.
    Mp two;
    two.uint(7).str("z");
    GuestAson c(t);
    t.expect_eq(c.deserialize(two.b), (s64)two.b.size(), "two roots: byte count");
    t.expect_eq(c->m_multiRoot, true, "ASON::m_multiRoot");
    t.expect_eq(c->m_root.m_kind, (u32)AValue::kArray, "two roots: an array");
    if (t.expect_eq(c->m_root.m_body.array.m_count, (u32)2, "two roots: count")) {
        t.expect_eq(c->m_root.m_body.array.m_elements[0].m_body.u, (u64)7, "root 0");
        t.expect_eq(body_str(c->m_root.m_body.array.m_elements[1]), std::string("z"), "root 1");
    }
}

// ---- ASON: values built through the guest's builders ------------------------------------------------------
NATIVE_TEST("data_formats/layout-ason-build") {
    GuestAson a(t, 0x2000, true);
    alignas(16) AValue v = {};
    Status st{-1};
    t.call("_ZN4Aska4ASON14MakeAValue_MapEPNS0_6AValueEj", GuestArgs().sret(&st).p(a.o.get()).p(&v).i(3));
    t.expect_eq(st.code, (s64)0, "MakeAValue_Map status (x8)");
    t.expect_eq(v.m_kind, (u32)AValue::kMap, "MakeAValue_Map kind");
    t.expect_eq(v.m_body.map.m_count, (u32)3, "MakeAValue_Map count");
    u8* lo = (u8*)a->m_currentWork->m_buffer;
    t.expect_eq((u8*)v.m_body.map.m_pairs >= lo && (u8*)(v.m_body.map.m_pairs + 3) <= lo + a->m_currentWork->m_used, true,
                "the pairs are in the current work block");
    t.expect_eq(v.m_body.map.m_pairs[2].value.m_kind, (u32)AValue::kNil, "pairs cleared");
    // SetString: data and (keepCStrings) a terminated copy, both stamped with m_workIndex.
    ASON_Pair& p0 = v.m_body.map.m_pairs[0];
    t.call("_ZN4Aska4ASON6AValue9SetStringEPKcPS0_", GuestArgs().sret(&st).p(&p0.key).p("hello").p(a.o.get()));
    t.expect_eq(st.code, (s64)0, "SetString status (x8)");
    t.expect_eq(p0.key.m_kind, (u32)AValue::kString, "SetString kind");
    t.expect_eq(p0.key.m_length, (u32)5, "SetString m_length");
    t.expect_eq(body_str(p0.key), std::string("hello"), "SetString m_data");
    t.expect_eq(std::string(p0.key.m_body.str.m_cstr ? p0.key.m_body.str.m_cstr : ""), std::string("hello"),
                "SetString m_cstr");
    t.expect_eq(p0.key.m_dataWork, a->m_workIndex, "SetString m_dataWork");
    t.expect_eq(p0.key.m_cstrWork, a->m_workIndex, "SetString m_cstrWork");
    t.call("_ZN4Aska4ASON16MakeAValue_ArrayEPNS0_6AValueEj", GuestArgs().sret(&st).p(a.o.get()).p(&p0.value).i(4));
    t.expect_eq(p0.value.m_kind, (u32)AValue::kArray, "MakeAValue_Array kind");
    t.expect_eq(p0.value.m_body.array.m_count, (u32)4, "MakeAValue_Array count");
    // The guest finds the value by the key we read back.
    u64 g = t.call("_ZN4Aska4ASON6AValue4AMap4Get_EPKc", {(u64)&v.m_body.map, (u64)"hello"});
    t.expect_eq(g, (u64)&p0.value, "AMap::Get_ of the built map");
    // Without keepCStrings there is no C string (m_cstrWork 0xffff).
    GuestAson b(t, 0x2000, false);
    alignas(16) AValue s = {};
    t.call("_ZN4Aska4ASON6AValue9SetStringEPKcPS0_", GuestArgs().sret(&st).p(&s).p("abc").p(b.o.get()));
    t.expect_eq((u64)s.m_body.str.m_cstr, (u64)0, "no m_cstr without keepCStrings");
    t.expect_eq(s.m_cstrWork, (u16)0xffff, "m_cstrWork 0xffff without keepCStrings");
    t.expect_eq(b->m_keepCStrings, false, "ASON::m_keepCStrings false");
}

// ---- the client's serializer (AsonSerializer::Serialize<CBattleLogInfo>) --------------------------------
struct SerializerSeen {
    int keys = 0, ends = 0, bad = 0;
    std::string first_bad;
    void fail(const std::string& what) { if (!bad++) first_bad = what; }
};

NATIVE_TEST("data_formats/layout-ason-serializer") {
    u64 pm_slot = t.sym("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE");
    u64 pm = pm_slot ? *(u64*)pm_slot : 0;
    if (!pm) { t.fail("no CParameterManager"); return; }
    const u64 key_fn = t.sym("_ZN15_AsonSerializer13Serialize_KeyEPKc");
    const u64 end_fn = t.sym("_ZN22AsonSerializer_Prepare19Serialize_EndObjectEv");
    stub_isolated_at(key_fn, "dataf_ason_key", 2);
    stub_isolated_at(end_fn, "dataf_prepare_endobject", 1);
    const std::string key_name = stub_name(key_fn), end_name = stub_name(end_fn);
    const u64 key_orig = stub_original(key_fn), end_orig = stub_original(end_fn);
    const u64 ser_vt = vtable_of(t, "_ZTV15_AsonSerializer"), prep_vt = vtable_of(t, "_ZTV22AsonSerializer_Prepare");
    GuestAson a(t, 0x4000, true);
    SerializerSeen seen;
    StubSession ss;
    ss.only = {key_name, end_name};
    // _AsonSerializer::Serialize_Key writes the key into m_map->m_pairs[m_indices[m_level]].key.
    ss.behave[key_name] = [&](Cpu& c) {
        auto* s = reinterpret_cast<_AsonSerializer*>(c.x(0));
        const char* key = (const char*)c.x(1);
        seen.keys++;
        if ((u64)s->vtable != ser_vt) seen.fail("_AsonSerializer::vtable");
        if (s->m_ason != a.o.get()) seen.fail("_AsonSerializer::m_ason");
        if (s->m_values.m_capacity < 10 || s->m_maps.m_capacity < 10 || s->m_arrays.m_capacity < 10) seen.fail("TStack capacities");
        if (s->m_level < 0 || (u64)s->m_level >= s->m_indices.m_size) seen.fail("m_level within m_indices");
        u32 idx = s->m_indices.m_data[s->m_level];
        AMap* m = s->m_map;
        guest_call(key_orig, {c.x(0), c.x(1)});
        if (!m || idx >= m->m_count) { seen.fail("m_map / index"); return; }
        const AValue& k = m->m_pairs[idx].key;
        if (k.m_kind != AValue::kString || body_str(k) != key) seen.fail(std::string("key written: ") + key);
        // The value slot the next Serialize_Value fills is the pair's value: m_value is not it (it is the object).
        if (s->m_counts.m_data == nullptr) seen.fail("_AsonSerializer::m_counts.m_data");
    };
    ss.behave[end_name] = [&](Cpu& c) {
        auto* p = reinterpret_cast<AsonSerializer_Prepare*>(c.x(0));
        seen.ends++;
        if ((u64)p->vtable != prep_vt) seen.fail("AsonSerializer_Prepare::vtable");
        if (p->m_depth < 1) seen.fail("AsonSerializer_Prepare::m_depth");
        if (p->m_levels.m_top < 0 || p->m_levels.m_capacity < 10) seen.fail("AsonSerializer_Prepare::m_levels");
        if (!p->m_counts.m_data || p->m_counts.m_minCapacity != 8) seen.fail("AsonSerializer_Prepare::m_counts");
        s32 depth = p->m_depth, top = p->m_levels.m_top;
        s32 restored = p->m_levels.m_data[top];
        guest_call(end_orig, {c.x(0)});
        if (p->m_depth != depth - 1 || p->m_levels.m_top != top - 1 || p->m_level != restored)
            seen.fail("Serialize_EndObject's pops (m_depth, m_levels, m_level)");
    };
    t.call("_ZN14AsonSerializer9SerializeI14CBattleLogInfoEEvRT_jmb",
           {a.o.addr(), pm + server_port::kParamBattleLogInfo, 0, 0x4000, 1});
    fprintf(stderr, "data_formats/layout-ason-serializer: %d keys, %d prepare EndObjects checked\n", seen.keys, seen.ends);
    if (seen.keys == 0) t.fail("Serialize_Key never ran");
    if (seen.ends == 0) t.fail("AsonSerializer_Prepare::Serialize_EndObject never ran");
    if (seen.bad) t.fail("%d serializer layout mismatches; first: %s", seen.bad, seen.first_bad.c_str());
    // The document: the root is a map whose keys the guest's lookup finds.
    if (!t.expect_eq(a->m_root.m_kind, (u32)AValue::kMap, "battle log root kind")) return;
    AMap* m = &a->m_root.m_body.map;
    for (u32 i = 0; i < m->m_count; i++) {
        const AValue& k = m->m_pairs[i].key;
        if (!k.m_body.str.m_cstr) { t.fail("battle log key %u has no C string", i); continue; }
        u64 g = t.call("_ZN4Aska4ASON6AValue4AMap4Get_EPKc", {(u64)m, (u64)k.m_body.str.m_cstr});
        t.expect_eq(g, (u64)&m->m_pairs[i].value, "battle log AMap::Get_");
    }
}

// ---- ACSV through Framework::CACSV ----------------------------------------------------------------------
float cell_as_float(const ACSV& a, u64 row, u64 col) {
    u64 i = col + a.m_numColumns * row;
    if (a.m_blankBits.m_bits[i >> 5] & (1u << (i & 31))) return 0.0f;
    const ACSV_AValue& v = a.m_values[i];
    switch (a.m_types[col]) {
    case ACSV::kBool: return v.m_value.u8v ? 1.0f : 0.0f;
    case ACSV::kS8: return (float)(s8)v.m_value.u8v;
    case ACSV::kU8: return (float)v.m_value.u8v;
    case ACSV::kS16: return (float)(s16)v.m_value.u16v;
    case ACSV::kU16: return (float)v.m_value.u16v;
    case ACSV::kS32: return (float)(s32)v.m_value.u32v;
    case ACSV::kU32: return (float)v.m_value.u32v;
    case ACSV::kS64: return (float)(s64)v.m_value.u64v;
    case ACSV::kU64: return (float)v.m_value.u64v;
    case ACSV::kFloat: { float f; std::memcpy(&f, &v.m_value.u32v, 4); return f; }
    case ACSV::kDouble: { double d; std::memcpy(&d, &v.m_value.u64v, 8); return (float)d; }
    default: return 0.0f;
    }
}

NATIVE_TEST("data_formats/layout-acsv") {
    // Columns: an int, a float, a string, a column with a blank cell, a negative int.
    const char* text = "1,2.5,abc,7,-4\n300,0.25,\"q,d\",,-70000\n70000,3.75,long text here more than 22,9,5\n";
    Obj<CACSV> o;
    CACSV* c = o.get();
    t.call("_ZN9Framework5CACSVC1Ev", {o.addr()});
    t.expect_eq((u64)c->m_acsv.vtable, vtable_of(t, "_ZTVN4Aska4ACSVE"), "ACSV::vtable");
    t.expect_eq((u64)c->m_acsv.m_blankBits.vtable, vtable_of(t, "_ZTVN4Aska9TBitArrayIjLb0EEE"), "TBitArray vtable");
    t.expect_eq(c->m_acsv.m_separator, ',', "ACSV::m_separator");
    t.call("_ZN9Framework5CACSV5ParseEPKc", {o.addr(), (u64)text});
    t.expect_eq(c->m_isParsed, true, "CACSV::m_isParsed");
    t.expect_eq((u8)t.call("_ZNK9Framework5CACSV8IsParsedEv", {o.addr()}), (u8)1, "CACSV::IsParsed");
    u64 rows = t.call("_ZNK9Framework5CACSV7NumRowsEv", {o.addr()});
    u64 cols = t.call("_ZNK9Framework5CACSV10NumColumnsEv", {o.addr()});
    t.expect_eq(rows, c->m_acsv.m_numRows, "NumRows == ACSV::m_numRows");
    t.expect_eq(cols, c->m_acsv.m_numColumns, "NumColumns == ACSV::m_numColumns");
    t.expect_eq(rows, (u64)3, "3 rows");
    t.expect_eq(cols, (u64)5, "5 columns");
    t.expect_eq(c->m_acsv.m_capColumns >= cols && c->m_acsv.m_capRows >= rows, true, "Init's capacities");
    t.expect_eq(c->m_acsv.m_extension, (u32)3, "ACSV::m_extension (CACSV::Parse inits with 3)");
    t.expect_eq((u64)c->m_acsv.m_memory[2].m_buffer, (u64)c->m_acsv.m_values, "WorkMemory 2 is m_values");
    t.expect_eq((u64)c->m_acsv.m_memory[0].m_buffer, (u64)c->m_acsv.m_types, "WorkMemory 0 is m_types");
    t.expect_eq(c->m_acsv.m_blankBits.m_numBits >= rows * cols, true, "TBitArray::m_numBits");
    for (u64 r = 0; r < rows; r++)
        for (u64 col = 0; col < cols; col++) {
            u32 type = c->m_acsv.m_types[col];
            u64 i = col + cols * r;
            bool blank = c->m_acsv.m_blankBits.m_bits[i >> 5] & (1u << (i & 31));
            t.expect_eq((u8)t.call("_ZNK9Framework5CACSV7IsBlankEmm", {o.addr(), r, col}), (u8)blank, "IsBlank == the blank bit");
            if (type == ACSV::kString) {
                guest::String gs;
                gs.init();
                t.call("_ZNK9Framework5CACSV6StringEmm", GuestArgs().sret(&gs).p(c).i(r).i(col));
                std::string mine = blank ? "" : std::string(c->m_acsv.m_values[i].m_value.str, c->m_acsv.m_values[i].m_length);
                t.expect_eq(gs.str(), mine, "CACSV::String == ACSV_AValue {str, m_length}");
                gs.destroy();
            } else {
                float g = guest_invoke<float>(t.sym("_ZNK9Framework5CACSV5ValueEmm"), (u64)c, r, col);
                float mine = cell_as_float(c->m_acsv, r, col);
                if (!(g == mine || (std::isnan(g) && std::isnan(mine))))
                    t.fail("CACSV::Value(%llu, %llu) type %u: guest %g, from the layout %g", (unsigned long long)r,
                           (unsigned long long)col, type, g, mine);
            }
            // ACSV::GetValue (the 16-byte copy for a string cell) reads the same cell.
            alignas(16) u8 out[16] = {};
            if (!blank && (u8)t.call("_ZNK4Aska4ACSV8GetValueENS0_4TypeEmmPv", {(u64)&c->m_acsv, 12, col, r, (u64)out}))
                t.expect_eq(std::memcmp(out, &c->m_acsv.m_values[i], 16), 0, "ACSV::GetValue copies m_values[c + cols * r]");
        }
    fprintf(stderr, "data_formats/layout-acsv: column types");
    for (u64 col = 0; col < cols; col++) fprintf(stderr, " %u", c->m_acsv.m_types[col]);
    fprintf(stderr, "\n");
    // The blank cell (row 1, column 3).
    t.expect_eq((u8)t.call("_ZNK9Framework5CACSV7IsBlankEmm", {o.addr(), 1, 3}), (u8)1, "row 1 column 3 is blank");
    t.call("_ZN9Framework5CACSV7ReleaseEv", {o.addr()});
    t.expect_eq(c->m_isParsed, false, "CACSV::Release clears m_isParsed");
    t.expect_eq((u64)c->m_acsv.m_workArea, (u64)0, "ACSV::Term frees the work area");
    t.call("_ZN9Framework5CACSVD2Ev", {o.addr()});
}

// ---- Framework::CCSV -----------------------------------------------------------------------------------
NATIVE_TEST("data_formats/layout-ccsv") {
    const char* text = "a,1.5,b\nlonger string than twenty-two characters,,3\nx\n";
    Obj<CCSV> o;
    CCSV* c = o.get();
    t.call("_ZN9Framework4CCSVC1Ev", {o.addr()});
    t.expect_eq(c->m_separator, ',', "CCSV::m_separator");
    t.expect_eq(c->m_quote, '"', "CCSV::m_quote");
    t.call("_ZN9Framework4CCSV9SeparatorEc", {o.addr(), (u64)';'});
    t.expect_eq(c->m_separator, ';', "CCSV::Separator writes m_separator");
    t.call("_ZN9Framework4CCSV9SeparatorEc", {o.addr(), (u64)','});
    t.call("_ZN9Framework4CCSV5QuoteEc", {o.addr(), (u64)'\''});
    t.expect_eq(c->m_quote, '\'', "CCSV::Quote writes m_quote");
    t.call("_ZN9Framework4CCSV5QuoteEc", {o.addr(), (u64)'"'});
    t.call("_ZN9Framework4CCSV5ParseEPKcb", {o.addr(), (u64)text, 0});
    t.expect_eq(c->m_isParsed, true, "CCSV::m_isParsed");
    u64 rows = t.call("_ZNK9Framework4CCSV7NumRowsEv", {o.addr()});
    t.expect_eq(rows, (u64)(c->m_rows.size()), "NumRows == m_rows' size");
    t.expect_eq(rows, (u64)3, "3 rows");
    for (u64 r = 0; r < rows; r++) {
        const StlVectorElement& row = c->m_rows.begin_[r];
        u64 n = t.call("_ZNK9Framework4CCSV11NumElementsEm", {o.addr(), r});
        t.expect_eq(n, (u64)(row.size()), "NumElements == the row's size");
        for (u64 i = 0; i < n; i++) {
            const tElement* e = &row.begin_[i];
            t.expect_eq(t.call("_ZNK9Framework4CCSV7ElementEmm", {o.addr(), r, i}), (u64)e, "Element == &row[i]");
            t.expect_eq((u32)t.call("_ZNK9Framework4CCSV8tElement4TypeEv", {(u64)e}), e->m_kind, "tElement::Type == m_kind");
            if (e->m_kind == tElement::kValue)
                t.expect_eq(guest_invoke<double>(t.sym("_ZNK9Framework4CCSV8tElement5ValueEv"), (u64)e), e->m_data.value,
                            "tElement::Value == m_data.value");
            if (e->m_kind == tElement::kString)
                t.expect_eq(t.call("_ZNK9Framework4CCSV8tElement6StringEv", {(u64)e}), (u64)e->m_data.string,
                            "tElement::String == m_data.string");
        }
    }
    // The cells as the input has them.
    auto cell = [&](u64 r, u64 i) -> const tElement& { return c->m_rows.begin_[r].begin_[i]; };
    if (c->m_rows.size() == 3 && c->m_rows.begin_[1].size() == 3) {
        t.expect_eq(cell(0, 0).m_kind, (u32)tElement::kString, "a: string");
        t.expect_eq(((const guest::String*)cell(0, 0).m_data.string)->str(), std::string("a"), "a");
        t.expect_eq(cell(0, 1).m_kind, (u32)tElement::kValue, "1.5: value");
        t.expect_eq(cell(0, 1).m_data.value, 1.5, "1.5");
        t.expect_eq(((const guest::String*)cell(1, 0).m_data.string)->str(),
                    std::string("longer string than twenty-two characters"), "long string (heap form)");
        t.expect_eq(cell(1, 1).m_kind, (u32)tElement::kBlank, "blank cell");
        t.expect_eq(cell(1, 2).m_data.value, 3.0, "3");
    } else {
        t.fail("unexpected CCSV shape");
    }
    t.expect_eq(c->m_empty.m_kind, (u32)tElement::kBlank, "CCSV::m_empty is blank");
    t.expect_eq(t.call("_ZNK9Framework4CCSV11ElementSafeEmm", {o.addr(), 7, 7}), (u64)&c->m_empty,
                "ElementSafe out of range == &m_empty");
    t.call("_ZN9Framework4CCSVD2Ev", {o.addr()});
}

}  // namespace
}  // namespace soa::native::data_formats
