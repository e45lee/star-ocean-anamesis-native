// Differential tests of the ASON natives (data_formats_ason_*.cpp) against the 3.7.0 guest
// (--selftest data_formats/ason-): the guest functions run as ARM64 code (natives aren't installed in
// --selftest), the natives on the same inputs. Inputs: random msgpack documents in every encoding
// (all widths, non-minimal forms, embedded NULs, strings longer than the 0x200-byte scratch, bin / ext /
// fixext, deep and wide containers, several roots), fed whole or in pieces, plus truncated and corrupt
// ones; random Malloc sequences crossing blocks; Pack with every room size.
//
// Two ASONs built the same way (guest constructor + Init) take the guest's and the native's run; their
// allocations are at different addresses, so every word that points into an ASON's own blocks (or its
// block table) is compared as (block, offset).
#include <algorithm>
#include <cstring>
#include <set>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/data_formats/data_formats_layout.h"

namespace soa::native::data_formats {
namespace {

template <typename T>
struct Obj {
    alignas(16) unsigned char raw[sizeof(T) + 0x40] = {};
    T* get() { return reinterpret_cast<T*>(raw); }
    u64 addr() { return (u64)raw; }
};

struct Ason {
    TestContext& t;
    Obj<ASON> o;
    Ason(TestContext& tc, u32 work, bool keep) : t(tc) {
        t.call("_ZN4Aska4ASONC1Ev", {o.addr()});
        s64 r = (s64)t.call("_ZN4Aska4ASON4InitEjb", {o.addr(), work, keep ? 1u : 0u});
        if (r != 0) t.fail("ASON::Init(%#x) = %lld", work, (long long)r);
    }
    ~Ason() { t.call("_ZN4Aska4ASOND1Ev", {o.addr()}); }
    ASON* operator->() { return o.get(); }
    ASON* get() { return o.get(); }
};

// A word of an ASON's state, with pointers into its blocks / block table made comparable.
struct Norm {
    const ASON* a;
    u64 operator()(u64 w) const {
        const ASON_WorkBufferContext* b = a->m_work.m_begin;
        size_t n = a->m_work.m_end - a->m_work.m_begin;
        for (size_t i = 0; i < n; i++)
            if (w >= (u64)b[i].m_buffer && w < (u64)b[i].m_buffer + b[i].m_size) return 1ull << 63 | (u64)i << 40 | (w - (u64)b[i].m_buffer);
        if (w >= (u64)b && w < (u64)(b + n)) return 1ull << 62 | (w - (u64)b);
        return w;
    }
};

std::string hex(u64 v) {
    char s[24];
    snprintf(s, sizeof s, "%llx", (unsigned long long)v);
    return s;
}

// The allocator state of an ASON, normalized (empty when equal).
std::string diff_state(const ASON* x, const ASON* y) {
    Norm nx{x}, ny{y};
    struct F { const char* name; u64 a, b; };
    std::vector<F> f = {
        {"m_temp", nx((u64)x->m_temp), ny((u64)y->m_temp)},
        {"m_tempSize", x->m_tempSize, y->m_tempSize},
        {"m_tempUsed", x->m_tempUsed, y->m_tempUsed},
        {"blocks", (u64)(x->m_work.m_end - x->m_work.m_begin), (u64)(y->m_work.m_end - y->m_work.m_begin)},
        {"block capacity", (u64)(x->m_work.m_capEnd - x->m_work.m_begin), (u64)(y->m_work.m_capEnd - y->m_work.m_begin)},
        {"m_currentWork", nx((u64)x->m_currentWork), ny((u64)y->m_currentWork)},
        {"m_totalWorkSize", x->m_totalWorkSize, y->m_totalWorkSize},
        {"m_workIndex", x->m_workIndex, y->m_workIndex},
        {"m_status", (u64)x->m_status.code, (u64)y->m_status.code},
    };
    for (const u64* w = (const u64*)&x->m_root, *v = (const u64*)&y->m_root; w < (const u64*)(&x->m_root + 1); w++, v++)
        f.push_back({"m_root word", nx(*w), ny(*v)});
    size_t n = std::min(x->m_work.m_end - x->m_work.m_begin, y->m_work.m_end - y->m_work.m_begin);
    for (size_t i = 0; i < n; i++) {
        f.push_back({"block size", x->m_work.m_begin[i].m_size, y->m_work.m_begin[i].m_size});
        f.push_back({"block used", x->m_work.m_begin[i].m_used, y->m_work.m_begin[i].m_used});
        f.push_back({"block owned", x->m_work.m_begin[i].m_owned, y->m_work.m_begin[i].m_owned});
    }
    for (auto& e : f)
        if (e.a != e.b) return std::string(e.name) + ": guest " + hex(e.a) + ", native " + hex(e.b);
    return "";
}

// Two values (and what they hold) compared word by word, normalized; empty when equal. Containers
// are followed once each (stale frames and copied values share element arrays, even cyclically).
struct ValueDiff {
    Norm nx, ny;
    std::set<const void*> seen;
    std::string operator()(const AValue& x, const AValue& y, const std::string& at) {
        // The fields the kind defines (the other bytes are whatever the previous value left: in a
        // live check both runs share addresses and compare them raw; here the ASONs differ).
        auto field = [&](const char* name, u64 a, u64 b) {
            return a == b ? std::string() : at + " (kind " + std::to_string(x.m_kind) + ") " + name + ": guest " + hex(a) + ", native " + hex(b);
        };
        std::string d = field("kind", x.m_kind, y.m_kind);
        const ASON_ValueBody& p = x.m_body;
        const ASON_ValueBody& q = y.m_body;
        switch (x.m_kind) {
            case AValue::kNil: break;
            case AValue::kBool: if (d.empty()) d = field("bool", p.raw[0], q.raw[0]); break;
            case AValue::kUInt: case AValue::kSInt: case AValue::kFloat: if (d.empty()) d = field("value", p.u, q.u); break;
            case AValue::kString:
                if (d.empty()) d = field("data", nx((u64)p.str.m_data), ny((u64)q.str.m_data));
                if (d.empty()) d = field("cstr", nx((u64)p.str.m_cstr), ny((u64)q.str.m_cstr));
                if (d.empty()) d = field("length", x.m_length, y.m_length);
                if (d.empty()) d = field("data work", x.m_dataWork, y.m_dataWork);
                if (d.empty()) d = field("cstr work", x.m_cstrWork, y.m_cstrWork);
                break;
            case AValue::kArray: case AValue::kMap:
                if (d.empty()) d = field("elements", nx((u64)p.array.m_elements), ny((u64)q.array.m_elements));
                if (d.empty()) d = field("count", p.array.m_count, q.array.m_count);
                if (d.empty()) d = field("work", p.array.m_work, q.array.m_work);
                break;
            case AValue::kBinary: case AValue::kExt: {
                u16 pw, qw;
                size_t at_w = x.m_kind == AValue::kBinary ? 0x0c : 0x0e;
                std::memcpy(&pw, &p.raw[at_w], 2), std::memcpy(&qw, &q.raw[at_w], 2);
                if (d.empty()) d = field("data", nx((u64)p.bin.m_data), ny((u64)q.bin.m_data));
                if (d.empty()) d = field("size", p.bin.m_size, q.bin.m_size);
                if (d.empty()) d = field("work", pw, qw);
                if (d.empty() && x.m_kind == AValue::kExt) d = field("ext type", (u8)p.bin.m_extType, (u8)q.bin.m_extType);
                break;
            }
            default: break;
        }
        if (!d.empty()) return d;
        if ((x.m_kind == AValue::kArray || x.m_kind == AValue::kMap) && x.m_body.array.m_elements && y.m_body.array.m_elements &&
            seen.insert(x.m_body.array.m_elements).second) {
            u32 n = std::min<u32>(x.m_body.array.m_count, 0x20000);
            for (u32 i = 0; i < n; i++) {
                std::string d;
                if (x.m_kind == AValue::kArray) {
                    d = (*this)(x.m_body.array.m_elements[i], y.m_body.array.m_elements[i], at + "[" + std::to_string(i) + "]");
                } else {
                    const ASON_Pair& p = x.m_body.map.m_pairs[i];
                    const ASON_Pair& q = y.m_body.map.m_pairs[i];
                    d = (*this)(p.key, q.key, at + ".key" + std::to_string(i));
                    if (d.empty()) d = (*this)(p.value, q.value, at + ".value" + std::to_string(i));
                }
                if (!d.empty()) return d;
            }
        }
        if (x.m_kind == AValue::kString && x.m_body.str.m_cstr && y.m_body.str.m_cstr && std::strcmp(x.m_body.str.m_cstr, y.m_body.str.m_cstr) != 0)
            return at + ": C strings differ";
        if (x.m_kind == AValue::kString && x.m_body.str.m_data && y.m_body.str.m_data && x.m_length < 0x100000 &&
            std::memcmp(x.m_body.str.m_data, y.m_body.str.m_data, x.m_length) != 0)
            return at + ": string bytes differ";
        return "";
    }
};
std::string diff_value(const AValue& x, Norm nx, const AValue& y, Norm ny, const std::string& at) { return ValueDiff{nx, ny, {}}(x, y, at); }

// ---- random msgpack ---------------------------------------------------------------------------------

struct Gen {
    TestContext& t;
    std::vector<u8> b;
    int max_depth = 4;
    explicit Gen(TestContext& tc) : t(tc) {}
    int r(int lo, int hi) { return t.rand_int(lo, hi); }
    void be(u64 v, int n) {
        for (int i = n - 1; i >= 0; i--) b.push_back((u8)(v >> (8 * i)));
    }
    void bytes(size_t n, bool nul) {
        for (size_t i = 0; i < n; i++) b.push_back(nul && r(0, 15) == 0 ? 0 : (u8)r(1, 255));
    }
    void str() {
        int pick = r(0, 9);
        size_t n = pick < 5 ? (size_t)r(0, 31) : pick < 8 ? (size_t)r(0, 300) : (size_t)r(0x1f0, 0x500);
        int form = n < 32 ? r(0, 3) : n < 256 ? r(1, 3) : r(2, 3);
        if (form == 0) b.push_back((u8)(0xa0 | n));
        else if (form == 1) b.push_back(0xd9), be(n, 1);
        else if (form == 2) b.push_back(0xda), be(n, 2);
        else b.push_back(0xdb), be(n, 4);
        bytes(n, r(0, 3) == 0);
    }
    void scalar() {
        switch (r(0, 15)) {
            case 0: b.push_back(0xc0); break;
            case 1: b.push_back((u8)(0xc2 + r(0, 1))); break;
            case 2: b.push_back((u8)r(0, 0x7f)); break;
            case 3: b.push_back((u8)r(0xe0, 0xff)); break;
            case 4: {  // uint 8..64
                int w = r(0, 3);
                b.push_back((u8)(0xcc + w));
                be(t.rand_u64() >> r(0, 63), 1 << w);
                break;
            }
            case 5: {  // int 8..64
                int w = r(0, 3);
                b.push_back((u8)(0xd0 + w));
                be(t.rand_u64(), 1 << w);
                break;
            }
            case 6: {
                float f = (float)(t.rand_u64() % 100000) / 7.0f;
                u32 u;
                std::memcpy(&u, &f, 4);
                b.push_back(0xca), be(u, 4);
                break;
            }
            case 7: b.push_back(0xcb), be(t.rand_u64(), 8); break;
            case 8: case 9: case 10: str(); break;
            case 11: {  // bin 8/16/32
                size_t n = (size_t)r(0, 300);
                int w = n < 256 ? r(0, 2) : r(1, 2);
                b.push_back((u8)(0xc4 + w));
                be(n, 1 << w);
                bytes(n, true);
                break;
            }
            case 12: {  // fixext
                int w = r(0, 4);
                b.push_back((u8)(0xd4 + w));
                b.push_back((u8)r(0, 255));
                bytes((size_t)1 << w, true);
                break;
            }
            case 13: {  // ext 8/16/32
                size_t n = (size_t)r(0, 70);
                int w = r(0, 2);
                b.push_back((u8)(0xc7 + w));
                be(n, 1 << w);
                b.push_back((u8)r(0, 255));
                bytes(n, true);
                break;
            }
            default: str(); break;
        }
    }
    void value(int depth) {
        int pick = r(0, 9);
        if (depth >= max_depth || pick < 6) return scalar();
        bool map = pick >= 8;
        u32 n = r(0, 7) == 0 ? (u32)r(16, 40) : (u32)r(0, 6);
        int form = n < 16 ? r(0, 2) : r(1, 2);
        if (form == 0) b.push_back((u8)((map ? 0x80 : 0x90) | n));
        else if (form == 1) b.push_back(map ? 0xde : 0xdc), be(n, 2);
        else b.push_back(map ? 0xdf : 0xdd), be(n, 4);
        for (u32 i = 0; i < n; i++) {
            if (map) {
                if (r(0, 4)) str();
                else value(depth + 1);
            }
            value(depth + 1);
        }
    }
};

// One random document, maybe damaged.
std::vector<u8> random_doc(TestContext& t, int k) {
    Gen g(t);
    int roots = k % 7 == 0 ? t.rand_int(2, 4) : 1;
    for (int i = 0; i < roots; i++) g.value(0);
    if (k % 11 == 0) {  // deeper than the 32 frames
        g.b.clear();
        int d = t.rand_int(30, 36);
        for (int i = 0; i < d; i++) g.b.push_back(0x91);
        g.b.push_back(0x01);
    }
    if (k % 13 == 0 && g.b.size() > 2) g.b.resize((size_t)t.rand_int(1, (int)g.b.size() - 1));  // truncated
    if (k % 17 == 0 && g.b.size() > 2) g.b[(size_t)t.rand_int(0, (int)g.b.size() - 1)] = 0xc1;  // corrupt
    if (k % 19 == 0) {  // a wide array: crosses blocks
        g.b.clear();
        g.b.push_back(0xdc), g.be(700, 2);
        for (int i = 0; i < 700; i++) g.b.push_back((u8)t.rand_int(0, 0x7f));
    }
    return g.b;
}

constexpr const char* kUnpackTrue = "_ZN4Aska4ASON17UnpackMessagePackILb1EEENS_6StatusEPNS0_18MessagePackContextEPKamPm";
constexpr const char* kUnpackFalse = "_ZN4Aska4ASON17UnpackMessagePackILb0EEENS_6StatusEPNS0_18MessagePackContextEPKamPm";

// Feeds `doc` to UnpackMessagePack<Build> on two ASONs, comparing after every call. Whole documents
// the way DeserializeBinary does (a fresh context per root, until the input is used up); or a single
// root in up to three pieces, resuming while a call stopped inside a token's trail (m_state != 0).
template <bool Build>
bool unpack_case(TestContext& t, const std::vector<u8>& doc, int k) {
    bool keep = t.rand_int(0, 3) != 0;
    u32 work = t.rand_int(0, 2) ? 0x2000 : 0x4000;
    Ason ga(t, work, keep), na(t, work, keep);
    auto* gc = new ASON_MessagePackContext;
    auto* nc = new ASON_MessagePackContext;
    auto reset = [&] {
        std::memset(gc, 0, sizeof *gc);
        for (auto& f : gc->m_frames) f.m_work = ga->m_workIndex;
        std::memcpy(nc, gc, sizeof *gc);
    };
    bool pieces = doc.size() > 3 && t.rand_int(0, 2) == 0;
    std::vector<u64> cuts;
    if (pieces) {
        cuts.push_back((u64)t.rand_int(1, (int)doc.size() - 1));
        if (t.rand_int(0, 1)) cuts.push_back((u64)t.rand_int(1, (int)doc.size() - 1));
        std::sort(cuts.begin(), cuts.end());
    }
    cuts.push_back(doc.size());
    u64 goff = 0, noff = 0;
    bool ok = true;
    const s8* data = (const s8*)doc.data();
    reset();
    size_t piece = 0;
    for (int call = 0; call < 8 && ok; call++) {
        u64 len = cuts[piece];
        if (!pieces && call) reset();  // (DeserializeBinary: a fresh context per root)
        Status gs{0x5a5a};
        t.call(Build ? kUnpackTrue : kUnpackFalse, GuestArgs().sret(&gs).i(ga.o.addr()).p(gc).p(data).i(len).p(&goff));
        Status ns = na->UnpackMessagePack<Build>(nc, data, len, &noff);
        std::string d;
        if (gs.code != ns.code) d = "status " + hex((u64)gs.code) + " vs " + hex((u64)ns.code);
        else if (goff != noff) d = "*off " + hex(goff) + " vs " + hex(noff);
        else if (gc->m_state != nc->m_state || gc->m_trail != nc->m_trail || gc->m_top != nc->m_top)
            d = "state " + hex(gc->m_state) + "/" + hex(gc->m_trail) + "/" + hex(gc->m_top) + " vs " + hex(nc->m_state) + "/" + hex(nc->m_trail) + "/" +
                hex(nc->m_top);
        if (d.empty()) d = diff_state(ga.get(), na.get());
        ValueDiff vd{Norm{ga.get()}, Norm{na.get()}, {}};
        if (d.empty()) d = vd(gc->m_value, nc->m_value, "m_value");
        for (u32 f = 0; f < 32 && d.empty(); f++) {
            const ASON_UnpackFrame& x = gc->m_frames[f];
            const ASON_UnpackFrame& y = nc->m_frames[f];
            d = vd(x.m_value, y.m_value, "frame" + std::to_string(f));
            if (d.empty()) d = vd(x.m_mapKey, y.m_mapKey, "frame" + std::to_string(f) + ".key");
            if (d.empty() && (x.m_remaining != y.m_remaining || x.m_ct != y.m_ct || x.m_work != y.m_work)) d = "frame" + std::to_string(f) + " counters";
        }
        if (!d.empty()) {
            t.fail("unpack<%d> case %d (%zu bytes, %s, end %llu, call %d): %s", Build, k, doc.size(), pieces ? "pieces" : "whole", (unsigned long long)len, call,
                   d.c_str());
            ok = false;
        }
        if (gs.code < 0) break;
        if (pieces) {
            // (resume only a call that stopped in a trail; a finished root leaves its last state behind,
            // which the game never resumes: with a 0 trail the guest would run off the buffer)
            if (gc->m_state == 0 || goff + gc->m_trail <= len || ++piece >= cuts.size()) break;
        } else if (goff >= len) {
            break;
        }
    }
    delete gc;
    delete nc;
    return ok;
}

NATIVE_TEST("data_formats/ason-unpack") {
    int bad = 0;
    for (int k = 0; k < 400 && bad < 3; k++) {
        std::vector<u8> doc = random_doc(t, k);
        if (doc.empty()) continue;
        if (!unpack_case<true>(t, doc, k)) bad++;
        if (!unpack_case<false>(t, doc, k)) bad++;
    }
}

// Malloc: random sizes (0, small, crossing blocks, larger than a block) on two ASONs.
NATIVE_TEST("data_formats/ason-malloc") {
    for (int k = 0; k < 40; k++) {
        Ason ga(t, 0x2000, true), na(t, 0x2000, true);
        for (int i = 0; i < 60; i++) {
            int pick = t.rand_int(0, 9);
            u64 n = pick == 0 ? 0 : pick < 7 ? (u64)t.rand_int(1, 200) : pick < 9 ? (u64)t.rand_int(0x400, 0x1800) : (u64)t.rand_int(0x2000, 0x9000);
            u64 g = t.call("_ZN4Aska4ASON6MallocEm", {ga.o.addr(), n});
            u64 v = (u64)na->Malloc(n);
            std::string d = Norm{ga.get()}(g) != Norm{na.get()}(v) ? "result " + hex(Norm{ga.get()}(g)) + " vs " + hex(Norm{na.get()}(v)) : diff_state(ga.get(), na.get());
            if (!d.empty()) {
                t.fail("malloc case %d step %d (%llu bytes): %s", k, i, (unsigned long long)n, d.c_str());
                return;
            }
        }
    }
}

// UnpackValue_str on its own: every combination of null / empty / keep, strings around the scratch size.
NATIVE_TEST("data_formats/ason-unpack-value-str") {
    for (int k = 0; k < 200; k++) {
        bool keep = k % 3 != 0;
        Ason ga(t, 0x2000, keep), na(t, 0x2000, keep);
        std::string s((size_t)(k % 4 == 0 ? t.rand_int(0, 4) : t.rand_int(0x100, 0x300)), 'x');
        for (auto& c : s) c = (char)t.rand_int(k % 5 == 0 ? 0 : 1, 255);
        const s8* p = k % 17 == 0 ? nullptr : (const s8*)s.data();
        u16 work = (u16)t.rand_int(0, 3);
        for (int rep = 0; rep < 3; rep++) {  // (again: the scratch is reused or overflows to new[])
            AValue gv{}, nv{};
            std::memset(&gv, 0x33, sizeof gv);
            std::memset(&nv, 0x33, sizeof nv);
            s32 g = (s32)t.call("_ZN4Aska4ASON15UnpackValue_strEPNS0_6AValueEPKaS4_jt", {ga.o.addr(), (u64)&gv, (u64)s.data(), (u64)p, (u64)s.size(), work});
            s32 n = na->UnpackValue_str(&nv, (const s8*)s.data(), p, (u32)s.size(), work);
            std::string d = g != n ? "result" : diff_state(ga.get(), na.get());
            if (d.empty()) d = diff_value(gv, Norm{ga.get()}, nv, Norm{na.get()}, "v");
            if (!d.empty()) {
                t.fail("unpack-value-str case %d rep %d (len %zu keep %d): %s", k, rep, s.size(), keep, d.c_str());
                return;
            }
        }
    }
}

// Pack<true> / <false> over documents the guest parsed, with every room size around the packed size.
NATIVE_TEST("data_formats/ason-pack") {
    int bad = 0;
    for (int k = 0; k < 160 && bad < 3; k++) {
        Gen g(t);
        g.value(0);
        Ason a(t, 0x4000, true);
        s64 r = (s64)t.call("_ZN4Aska4ASON17DeserializeBinaryEPKvm", {a.o.addr(), (u64)g.b.data(), (u64)g.b.size()});
        if (r <= 0) continue;
        const AValue* root = &a->m_root;
        // count
        u64 gw = (u64)t.rand_int(0, 5), nw = gw;
        Status gs{0x5a}, ns{0x5a};
        t.call("_ZNK4Aska4ASON15PackMessagePackILb0EEENS_6StatusEPKNS0_6AValueEPhmPm", GuestArgs().sret(&gs).i(a.o.addr()).p(root).i(0).i(0).p(&gw));
        ns = a->PackMessagePack<false>(root, nullptr, 0, &nw);
        if (gs.code != ns.code || gw != nw) {
            t.fail("pack<false> case %d: status %lld/%lld, written %llu/%llu", k, (long long)gs.code, (long long)ns.code, (unsigned long long)gw, (unsigned long long)nw);
            bad++;
            continue;
        }
        u64 need = gw;
        for (int rep = 0; rep < 6; rep++) {
            u64 size = rep == 0 ? need : rep == 1 ? need + 3 : (u64)t.rand_int(0, (int)need + 2);
            u64 start = rep == 5 ? (u64)t.rand_int(0, 3) : 0;
            std::vector<u8> gb(need + 16, 0xee), nb(need + 16, 0xee);
            gw = nw = start;
            a->m_status.code = 0;
            t.call("_ZNK4Aska4ASON15PackMessagePackILb1EEENS_6StatusEPKNS0_6AValueEPhmPm", GuestArgs().sret(&gs).i(a.o.addr()).p(root).p(gb.data() + start).i(size).p(&gw));
            s64 gst = a->m_status.code;
            a->m_status.code = 0;
            ns = a->PackMessagePack<true>(root, nb.data() + start, size, &nw);
            if (gs.code != ns.code || gw != nw || gb != nb || gst != a->m_status.code) {
                t.fail("pack<true> case %d rep %d (need %llu, size %llu): status %lld/%lld, written %llu/%llu, m_status %lld/%lld%s", k, rep,
                       (unsigned long long)need, (unsigned long long)size, (long long)gs.code, (long long)ns.code, (unsigned long long)gw,
                       (unsigned long long)nw, (long long)gst, (long long)a->m_status.code, gb != nb ? ", bytes differ" : "");
                bad++;
                break;
            }
        }
    }
}

// The header writers with every value class and room.
NATIVE_TEST("data_formats/ason-pack-values") {
    Ason a(t, 0x2000, true);
    for (int k = 0; k < 3000; k++) {
        u64 v = t.rand_u64() >> t.rand_int(0, 63);
        if (k & 1) v = (u64)-(s64)v;
        u64 room = (u64)t.rand_int(0, 10);
        int which = k % 4;
        u8 gb[16], nb[16];
        std::memset(gb, 0xee, 16), std::memset(nb, 0xee, 16);
        a->m_status.code = 0;
        u64 g = 0, n = 0;
        s8 type = (s8)t.rand_int(-128, 127);
        if (which == 2 || which == 3) v &= t.rand_int(0, 1) ? 0x1f : t.rand_int(0, 1) ? 0x11 : 0x1ffff;
        switch (which) {
            case 0: g = t.call("_ZNK4Aska4ASON13PackValue_u64ILb1EEElPhmm", {a.o.addr(), (u64)gb, v, room}); break;
            case 1: g = t.call("_ZNK4Aska4ASON13PackValue_s64ILb1EEElPhlm", {a.o.addr(), (u64)gb, v, room}); break;
            case 2: g = t.call("_ZNK4Aska4ASON13PackValue_strILb1EEElPhmm", {a.o.addr(), (u64)gb, v, room}); break;
            case 3: g = t.call("_ZNK4Aska4ASON13PackValue_extILb1EEElPhmam", {a.o.addr(), (u64)gb, v, (u64)(u8)type, room}); break;
        }
        s64 gst = a->m_status.code;
        a->m_status.code = 0;
        switch (which) {
            case 0: n = (u64)a->PackValue_u64(nb, v, room); break;
            case 1: n = (u64)a->PackValue_s64(nb, (s64)v, room); break;
            case 2: n = (u64)a->PackValue_str(nb, v, room); break;
            case 3: n = (u64)a->PackValue_ext(nb, v, type, room); break;
        }
        if (g != n || std::memcmp(gb, nb, 16) != 0 || gst != a->m_status.code) {
            t.fail("PackValue %d (v %#llx room %llu): %#llx vs %#llx", which, (unsigned long long)v, (unsigned long long)room, (unsigned long long)g, (unsigned long long)n);
            return;
        }
    }
}

// AMap::Get_ by C string and by value on parsed maps (the same objects: results compare as pointers).
NATIVE_TEST("data_formats/ason-amap-get") {
    for (int k = 0; k < 120; k++) {
        Gen g(t);
        u32 n = (u32)t.rand_int(1, 20);
        g.b.push_back(0xde), g.be(n, 2);
        for (u32 i = 0; i < n; i++) {
            if (t.rand_int(0, 3)) g.str();
            else g.scalar();
            g.scalar();
        }
        bool keep = k % 4 != 0;
        Ason a(t, 0x4000, keep);
        if ((s64)t.call("_ZN4Aska4ASON17DeserializeBinaryEPKvm", {a.o.addr(), (u64)g.b.data(), (u64)g.b.size()}) <= 0) continue;
        AMap* m = &a->m_root.m_body.map;
        for (u32 i = 0; i < m->m_count + 3; i++) {
            const AValue* key = i < m->m_count ? &m->m_pairs[i].key : &m->m_pairs[0].value;
            std::string name = key->m_kind == AValue::kString && key->m_body.str.m_cstr ? key->m_body.str.m_cstr : i % 2 ? "nope" : "";
            u64 g1 = t.call("_ZN4Aska4ASON6AValue4AMap4Get_EPKc", {(u64)m, (u64)name.c_str()});
            u64 n1 = (u64)m->Get_(name.c_str());
            AValue copy = *key;
            u64 g2 = t.call("_ZN4Aska4ASON6AValue4AMap4Get_EPKS1_", {(u64)m, (u64)&copy});
            u64 n2 = (u64)m->Get_(&copy);
            u64 g3 = t.call("_ZN4Aska4ASON6AValue4AMap4Get_EPKS1_", {(u64)m, (u64)key});
            u64 n3 = (u64)m->Get_(key);
            if (g1 != n1 || g2 != n2 || g3 != n3) {
                t.fail("AMap::Get_ case %d key %u (kind %u): %llx/%llx %llx/%llx %llx/%llx", k, i, key->m_kind, (unsigned long long)g1, (unsigned long long)n1,
                       (unsigned long long)g2, (unsigned long long)n2, (unsigned long long)g3, (unsigned long long)n3);
                return;
            }
        }
        if (t.call("_ZN4Aska4ASON6AValue4AMap4Get_EPKc", {(u64)m, 0}) != (u64)m->Get_((const char*)nullptr)) t.fail("Get_(nullptr)");
    }
}

// MakeAValue_Array / _Map and both SetString on two ASONs.
NATIVE_TEST("data_formats/ason-build-values") {
    for (int k = 0; k < 60; k++) {
        bool keep = k % 3 != 0;
        Ason ga(t, 0x2000, keep), na(t, 0x2000, keep);
        for (int i = 0; i < 40; i++) {
            AValue gv, nv;
            std::memset(&gv, 0x44, sizeof gv);
            std::memset(&nv, 0x44, sizeof nv);
            Status gs{0x5a}, ns{0x5a};
            int op = t.rand_int(0, 3);
            std::string s((size_t)(t.rand_int(0, 3) ? t.rand_int(0, 40) : t.rand_int(0x200, 0x900)), 'q');
            for (auto& c : s) c = (char)t.rand_int(t.rand_int(0, 5) ? 1 : 0, 255);
            u32 len = t.rand_int(0, 2) ? (u32)s.size() : (u32)t.rand_int(0, (int)s.size() + 5);
            if (len > s.size()) s.resize(len + 1, 'z');
            const char* sp = i % 23 == 0 ? nullptr : s.c_str();
            u32 cnt = t.rand_int(0, 4) ? (u32)t.rand_int(0, 20) : (u32)t.rand_int(100, 400);
            AValue* gp = i % 29 == 0 ? nullptr : &gv;
            AValue* np = gp ? &nv : nullptr;
            switch (op) {
                case 0:
                    t.call("_ZN4Aska4ASON16MakeAValue_ArrayEPNS0_6AValueEj", GuestArgs().sret(&gs).i(ga.o.addr()).p(gp).i(cnt));
                    ns = na->MakeAValue_Array(np, cnt);
                    break;
                case 1:
                    t.call("_ZN4Aska4ASON14MakeAValue_MapEPNS0_6AValueEj", GuestArgs().sret(&gs).i(ga.o.addr()).p(gp).i(cnt));
                    ns = na->MakeAValue_Map(np, cnt);
                    break;
                case 2:
                    t.call("_ZN4Aska4ASON6AValue9SetStringEPKcPS0_", GuestArgs().sret(&gs).p(&gv).p(sp).i(ga.o.addr()));
                    ns = nv.SetString(sp, na.get());
                    break;
                case 3:
                    t.call("_ZN4Aska4ASON6AValue9SetStringEPKcjPS0_", GuestArgs().sret(&gs).p(&gv).p(sp).i(len).i(ga.o.addr()));
                    ns = nv.SetString(sp, len, na.get());
                    break;
            }
            std::string d = gs.code != ns.code ? "status " + hex((u64)gs.code) + " vs " + hex((u64)ns.code) : diff_state(ga.get(), na.get());
            if (d.empty()) d = diff_value(gv, Norm{ga.get()}, nv, Norm{na.get()}, "v");
            if (!d.empty()) {
                t.fail("build case %d step %d op %d (len %u, count %u): %s", k, i, op, len, cnt, d.c_str());
                return;
            }
        }
    }
}

}  // namespace
}  // namespace soa::native::data_formats
