// soa_models' unit tests (build/common/soa_models_tests): synthetic AFF data built here, no game
// files. The index-list codecs against encoders written from their decoders' rules; a minimal ASF
// (a root, one mesh object: a material, a skinned meshset whose vertices sit in the AMF buffer and
// whose indices are a TriListComp block) read back; AAF tracks evaluated at keys, between keys and
// out of range.
#include <soa/aaf.h>
#include <soa/aff.h>
#include <soa/asf.h>

#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using soa::aff::Bytes;

static int g_fail = 0;
#define CHECK(c)                                                                  \
    do {                                                                          \
        if (!(c)) {                                                               \
            fprintf(stderr, "%s:%d: CHECK(%s)\n", __FILE__, __LINE__, #c);        \
            g_fail++;                                                             \
        }                                                                         \
    } while (0)

namespace {

void put16(Bytes& b, size_t at, uint16_t v) { memcpy(&b[at], &v, 2); }
void put32(Bytes& b, size_t at, uint32_t v) { memcpy(&b[at], &v, 4); }
void put64(Bytes& b, size_t at, uint64_t v) { memcpy(&b[at], &v, 8); }
void putf(Bytes& b, size_t at, float v) { memcpy(&b[at], &v, 4); }
void tag(Bytes& b, size_t at, const char* t) { memcpy(&b[at], t, 4); }
// a chunk {tag, size, 0, next} at the end of b, `size` bytes (16-aligned)
size_t chunk(Bytes& b, const char* t, size_t size) {
    size_t at = b.size();
    b.resize(at + size, 0);
    tag(b, at, t);
    put32(b, at + 4, (uint32_t)size);
    put32(b, at + 0xc, (uint32_t)size);
    return at;
}

// TriListComp's encoder (the inverse of DecompressTriangleList): triangles only (no quads), the
// high watermark constant K.
Bytes tri_encode(const std::vector<uint16_t>& idx, uint16_t K) {
    std::vector<uint16_t> w{K};
    uint32_t hw = (uint32_t)K + 0xffff;
    for (size_t i = 0; i + 2 < idx.size(); i += 3) {
        // keep a >= b so the decoder doesn't read a quad
        for (int k = 0; k < 3; k++) {
            hw &= 0xffff;
            uint32_t v = idx[i + k];
            w.push_back((uint16_t)(hw - v));
            if (hw <= v + K) hw = v + K;
        }
    }
    Bytes out(w.size() * 2);
    memcpy(out.data(), w.data(), out.size());
    return out;
}

// IdxBufComp's encoder: count, first index, then one run of 3-bit deltas per index (small steps).
struct BitW {
    Bytes b;
    uint64_t pos = 0;
    void put(uint32_t v, unsigned n) {
        for (unsigned i = 0; i < n; i++, pos++) {
            if (pos / 8 >= b.size()) b.push_back(0);
            if ((v >> i) & 1) b[pos / 8] |= (uint8_t)(1 << (pos & 7));
        }
    }
};

void test_codecs() {
    std::vector<uint16_t> idx = {2, 1, 0, 3, 2, 0, 5, 4, 3, 7, 6, 5};
    Bytes enc = tri_encode(idx, 4);
    Bytes dec(idx.size() * 2);
    CHECK(soa::aff::decompress_triangle_list(enc.data(), enc.size(), dec.data(), dec.size()));
    CHECK(!memcmp(dec.data(), idx.data(), dec.size()));
    // stored (0xffff): a < b makes a quad (a, b, c), (a, d, b)
    std::vector<uint16_t> raw = {0xffff, 1, 2, 3, 4, 9, 8, 7};
    Bytes rb(raw.size() * 2);
    memcpy(rb.data(), raw.data(), rb.size());
    Bytes out(9 * 2);
    CHECK(soa::aff::decompress_triangle_list(rb.data(), rb.size(), out.data(), out.size()));
    uint16_t want[9] = {1, 2, 3, 1, 4, 2, 9, 8, 7};
    CHECK(!memcmp(out.data(), want, sizeof want));
    // too small an output fails
    Bytes small(4 * 2);
    CHECK(!soa::aff::decompress_triangle_list(rb.data(), rb.size(), small.data(), small.size()));

    // IdxBufComp: count 6, first 10, one run of 5 deltas of 3 bits (+1 -2 +3 0 -1)
    BitW w;
    w.put(6, 32);
    w.put(10, 16);
    w.put(5, 16);
    int deltas[5] = {1, -2, 3, 0, -1};
    for (int d : deltas) w.put((uint32_t)d & 7, 3);
    w.put(0, 32);
    Bytes ib(6 * 2);
    CHECK(soa::aff::decompress_index_buffer(w.b.data(), w.b.size(), ib.data(), ib.size()));
    uint16_t iw[6] = {10, 11, 9, 12, 12, 11};
    CHECK(!memcmp(ib.data(), iw, sizeof iw));
}

// The vertex formats: Seaside Maria's bits (docs/notes.md "Meshes (ASF)") and a plain float one.
void test_vertex_format() {
    std::vector<soa::asf::VertexElement> e;
    CHECK(soa::asf::vertex_format(0x10040080994ull, e));
    CHECK(e.size() == 6);
    if (e.size() == 6) {
        CHECK(e[0].usage == soa::asf::kPosition && e[0].type == 4 && e[0].offset == 0);
        CHECK(e[1].usage == soa::asf::kNormal && e[1].type == 10 && e[1].offset == 16);
        CHECK(e[2].usage == soa::asf::kTexcoord && e[2].type == 13 && e[2].offset == 24);
        CHECK(e[3].usage == soa::asf::kTangent && e[3].type == 10 && e[3].offset == 28);
        CHECK(e[4].usage == soa::asf::kBlendWeight && e[4].type == 14 && e[4].offset == 36);
        CHECK(e[5].usage == soa::asf::kBlendIndex && e[5].type == 15 && e[5].offset == 44);
    }
    CHECK(soa::asf::vertex_format(0x211, e));  // float3 position, float3 normal (index 0 of 0xf0: float4.. -> 1: float3), uv float2
    CHECK(!e.empty() && e[0].type == 3);
    CHECK(!soa::asf::vertex_format(0x7, e));  // position code 7: rejected
}

// A minimal ASF: ROOT, a mesh object node, its '__oa' (no textures, one material, a bone list, one
// meshset), the node tree, and an AMF chunk with a raw buffer (vertices) and a TriListComp buffer
// (indices).
Bytes build_asf(std::vector<uint8_t>& vertices, std::vector<uint16_t>& indices) {
    Bytes b(0x10, 0);
    tag(b, 0, " FSA");
    size_t arf = chunk(b, " FRa", 0x30);
    put32(b, arf + 0xc, 0x30);  // the 'head' follows
    put32(b, arf + 0x18, 0x10227);
    tag(b, arf + 0x1c, " DRD");
    size_t head = chunk(b, "daeh", 0x20);
    // '__oa': header 0xd0, then '__lm', 'lpnb', 'stam', 'ydbm' + 'idxl' + 'vlas', 'mess'
    size_t oa = chunk(b, "__oa", 0xd0);
    put16(b, oa + 0x70, 1);  // meshsets
    put16(b, oa + 0x7e, 0);  // textures
    memcpy(&b[oa + 0xb0], "R:m_testShape", 13);
    size_t lm = chunk(b, "__lm", 0x10);
    size_t bones = chunk(b, "lpnb", 0x20);
    put32(b, bones + 4, 0x10 + 2 * 2);
    put16(b, bones + 0x10, 0);  // node 0 (ROOT)
    put16(b, bones + 0x12, 2);  // node 2 (the joint)
    size_t mat = chunk(b, "stam", 0x60);
    b[mat + 0x16] = 1;   // one constant
    b[mat + 0x18] = 0;   // no textures
    put32(b, mat + 0x20, 0x40);  // constants at +0x40
    put32(b, mat + 0x2c, 0x40);
    put32(b, mat + 0x1c, 0x60);  // (shader graph: none)
    put32(b, mat + 0x3c, 0x110);
    put16(b, mat + 0x40, 5);     // id 5, index 0, count 1, values at +8 from the entry
    b[mat + 0x43] = 1 << 2;
    put32(b, mat + 0x44, 8);
    putf(b, mat + 0x48, 0.25f);
    putf(b, mat + 0x4c, 0.5f);
    putf(b, mat + 0x50, 0.75f);
    putf(b, mat + 0x54, 1.0f);
    size_t body = chunk(b, "ydbm", 0x20);
    const uint32_t nv = 4;
    put32(b, body + 0x10, nv);
    put32(b, body + 0x14, (uint32_t)indices.size());
    b[body + 0x18] = 0;  // triangle list
    size_t pal = chunk(b, "ipnb", 0x20);
    put32(b, pal + 4, 0x10 + 2 * 2);
    put16(b, pal + 0x10, 1);  // blend index 0 -> bone 1 (node 2)
    put16(b, pal + 0x12, 0);
    size_t il = chunk(b, "lxdi", 0x40);
    uint8_t ig[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0xa1};
    memcpy(&b[il + 0x20], ig, 16);
    size_t vl = chunk(b, "salv", 0x50);
    uint64_t bits = 0x40000000ull | 0x200 | 0x1 | (uint64_t)0x100 << 32;  // pos float3, uv float2, weights ushort4n, joints
    // uv group: code 2 -> 0x50400 float4 ... use code 1 (0x50200: float2, 8 bytes)
    bits = 0x40000000ull | 0x100 | 0x1 | (uint64_t)0x100 << 32;
    put64(b, vl + 0x10, bits);
    std::vector<soa::asf::VertexElement> el;
    soa::asf::vertex_format(bits, el);
    uint16_t stride = 12 + 8 + 8 + 4;
    put16(b, vl + 0x18, stride);
    uint8_t vg[16] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0xb2};
    memcpy(&b[vl + 0x20], vg, 16);
    size_t mess = chunk(b, "ssem", 0x20);
    put32(b, mess + 0x10, (uint32_t)(body - mess));
    put32(b, mess + 0x14, (uint32_t)(mat - mess));
    b[mess + 0x19] = 0xff;
    (void)lm;
    // the node tree: ROOT (kind 0), m_test (kind 3, its '__oa' at `oa`), a joint (kind 2)
    size_t tree = chunk(b, "eert", 0x110);
    put32(b, tree + 0x10, 3);
    put32(b, tree + 0x18 + 0 * 4, 1);
    put32(b, tree + 0x18 + 2 * 4, 1);
    put32(b, tree + 0x18 + 3 * 4, 1);
    auto node = [&](const char* name, int kind, int parent, size_t size) {
        size_t n = chunk(b, "atta", size);
        memcpy(&b[n + 0x10], name, strlen(name));
        put32(b, n + 0x3c, (uint32_t)parent);
        b[n + 0x49] = (uint8_t)kind;
        putf(b, n + 0x8c, 1.0f);
        putf(b, n + 0x9c, 1.0f);
        for (int i = 0; i < 4; i++) putf(b, n + 0xa0 + i * 4, 1.0f);
        return n;
    };
    node("ROOT", 0, 0, 0x100);
    size_t mn = node("R:m_test", 3, 0, 0x220);
    put32(b, mn + 0x34, (uint32_t)oa);
    size_t jn = node("R:Joint", 2, 0, 0x150);
    putf(b, jn + 0x84, 10.0f);  // pos y 10
    for (int i = 0; i < 4; i++) putf(b, jn + 0x100 + i * 20, 1.0f);  // inverse bind: identity ...
    putf(b, jn + 0x100 + 7 * 4, -10.0f);                             // ... translated by -10 in y
    putf(b, jn + 0x14c, 1.0f);  // joint orient w
    // the tree's size covers its nodes
    put32(b, tree + 0xc, (uint32_t)(b.size() - tree));
    put32(b, tree + 4, (uint32_t)(b.size() - tree));
    size_t eof = chunk(b, "_foe", 0x10);
    (void)eof;
    put32(b, head + 0xc, (uint32_t)(oa - head));
    put32(b, 4, (uint32_t)b.size());  // the AskaFile's size: the AMF chunk follows
    // vertices and the TriListComp indices
    vertices.assign((size_t)nv * stride, 0);
    for (uint32_t v = 0; v < nv; v++) {
        float p[3] = {(float)(v & 1), (float)(v >> 1), 0.0f};
        memcpy(&vertices[v * stride], p, 12);
        float uv[2] = {(float)(v & 1), (float)(v >> 1)};
        memcpy(&vertices[v * stride + 12], uv, 8);
        uint16_t w[4] = {0xffff, 0, 0, 0};
        memcpy(&vertices[v * stride + 20], w, 8);
        vertices[v * stride + 28] = 0;
    }
    Bytes tri = tri_encode(indices, 4);
    // AMF: header chunk, two 'buff', two 'addr', then the buffers back to back (16-aligned)
    size_t amf = b.size();
    size_t vb = (vertices.size() + 15) & ~size_t(15), tb = (tri.size() + 15) & ~size_t(15);
    size_t entries = 0x10 + 2 * 0x40 + 2 * 0x60;
    b.resize(amf + entries + vb + tb, 0);
    tag(b, amf, " FMA");
    put32(b, amf + 4, (uint32_t)(entries + vb + tb));
    size_t p = amf + 0x10;
    auto buff = [&](uint64_t size, int16_t type, uint64_t decoded, size_t data_at) {
        tag(b, p, "ffub");
        put32(b, p + 4, 0x40);
        put32(b, p + 0xc, 0x40);
        put64(b, p + 0x10, size);
        put64(b, p + 0x18, data_at - p);  // its bytes, from the entry
        put16(b, p + 0x2c, (uint16_t)type);
        put64(b, p + 0x30, decoded);
        p += 0x40;
    };
    buff(vertices.size(), 0, vertices.size(), amf + entries);
    buff(tri.size(), 0xa, indices.size() * 2, amf + entries + vb);
    auto addr = [&](const uint8_t* g, uint64_t size, uint64_t off, int16_t buf, uint64_t decoded, bool last) {
        tag(b, p, "rdda");
        put32(b, p + 4, 0x60);
        put32(b, p + 0xc, last ? 0 : 0x60);
        memcpy(&b[p + 0x10], g, 16);
        put64(b, p + 0x20, size);
        put64(b, p + 0x28, off);
        put16(b, p + 0x3c, (uint16_t)buf);
        put64(b, p + 0x48, decoded);
        p += 0x60;
    };
    addr(vg, vertices.size(), 0, 0, vertices.size(), false);
    addr(ig, tri.size(), 0, 0xa, indices.size() * 2, true);
    memcpy(&b[amf + entries], vertices.data(), vertices.size());
    memcpy(&b[amf + entries + vb], tri.data(), tri.size());
    return b;
}

void test_asf() {
    std::vector<uint8_t> vertices;
    std::vector<uint16_t> indices = {2, 1, 0, 3, 1, 2};
    Bytes f = build_asf(vertices, indices);
    soa::asf::Scene s;
    std::string err;
    std::vector<std::string> warn;
    bool ok = soa::asf::load(f, s, &err, &warn);
    if (!ok) fprintf(stderr, "asf: %s\n", err.c_str());
    for (auto& w : warn) fprintf(stderr, "asf warning: %s\n", w.c_str());
    CHECK(ok);
    CHECK(s.nodes.size() == 3);
    CHECK(s.objects.size() == 1);
    if (s.nodes.size() == 3) {
        CHECK(s.nodes[0].kind == soa::asf::kRoot && s.nodes[0].parent == -1);
        CHECK(s.nodes[1].name == "m_test" && s.nodes[1].object == 0);
        CHECK(s.nodes[2].joint && s.nodes[2].pos[1] == 10.0f && s.nodes[2].inverse_bind[7] == -10.0f);
    }
    if (s.objects.size() == 1) {
        const auto& o = s.objects[0];
        CHECK(o.name == "m_testShape");
        CHECK(o.bones.size() == 2 && o.bones[1] == 2);
        CHECK(o.materials.size() == 1 && o.materials[0].constants.size() == 1);
        if (!o.materials.empty() && !o.materials[0].constants.empty())
            CHECK(o.materials[0].constants[0].values[0][2] == 0.75f);
        CHECK(o.meshsets.size() == 1);
        if (!o.meshsets.empty()) {
            const auto& m = o.meshsets[0];
            CHECK(m.vertices == vertices);
            CHECK(m.indices.size() == indices.size() * 2 && !memcmp(m.indices.data(), indices.data(), m.indices.size()));
            CHECK(m.palette.size() == 2 && m.palette[0] == 1);
        }
    }
}

// An AAF with one target and three controllers: TX Normal Hermite (2 keys), translate Vector_Linear
// (2 keys, post cycle), rotation Quaternion_Linear (2 equal keys).
Bytes build_aaf() {
    Bytes b(0x10, 0);
    tag(b, 0, " FAA");
    size_t arf = chunk(b, " FRa", 0x20);
    put32(b, arf + 0xc, 0x20);
    size_t h = b.size();
    b.resize(h + 0x30, 0);
    put16(b, h, 0x2e);
    put16(b, h + 4, 1);   // targets
    put16(b, h + 6, 3);   // controllers (B)
    putf(b, h + 0x10, 10.0f);
    put32(b, h + 0x20, (uint32_t)b.size());
    size_t t = b.size();
    b.resize(t + 0x28, 0);
    b[t] = 0;
    b[t + 1] = 0;
    put16(b, t + 2, 3);
    memcpy(&b[t + 8], "R:Joint", 7);
    auto ctrl = [&](uint8_t cp, uint8_t attr, uint8_t post, const std::vector<float>& times, const std::vector<float>& cps) {
        size_t c = b.size();
        size_t size = 0xc + 0x18 + times.size() * 4 + cps.size() * 4;
        b.resize(c + size, 0);
        put16(b, c + 2, (uint16_t)size);
        b[c + 5] = 0x40;
        put16(b, c + 6, 0xc);
        size_t kf = c + 0xc;
        b[kf + 5] = cp;
        b[kf + 6] = attr;
        b[kf + 9] = post;
        putf(b, kf + 0xc, times.front());
        putf(b, kf + 0x10, times.back());
        put32(b, kf + 0x14, (uint32_t)times.size());
        for (size_t i = 0; i < times.size(); i++) putf(b, kf + 0x18 + i * 4, times[i]);
        for (size_t i = 0; i < cps.size(); i++) putf(b, kf + 0x18 + times.size() * 4 + i * 4, cps[i]);
    };
    ctrl(soa::aaf::kNormal, soa::aaf::kTranslateX, 0, {0, 10}, {1, 0, 0, 3, 0, 0});
    ctrl(soa::aaf::kVectorLinear, soa::aaf::kTranslateXYZ, 2, {0, 10}, {0, 0, 0, 10, 20, 30});
    ctrl(soa::aaf::kQuaternionLinear, soa::aaf::kRotateQuaternion, 0, {0, 10}, {0, 0, 0, 1, 0, 0, 0, 1});
    put32(b, t + 4, (uint32_t)(b.size() - t));
    return b;
}

void test_aaf() {
    Bytes f = build_aaf();
    soa::aaf::Animation a;
    std::string err;
    bool ok = soa::aaf::load(f, a, &err);
    if (!ok) fprintf(stderr, "aaf: %s\n", err.c_str());
    CHECK(ok);
    CHECK(a.targets.size() == 1 && a.controllers.size() == 3);
    if (a.controllers.size() != 3) return;
    const auto& tx = a.controllers[0];
    const auto& tr = a.controllers[1];
    const auto& rq = a.controllers[2];
    CHECK(soa::aaf::supported(tx) && soa::aaf::supported(tr) && soa::aaf::supported(rq));
    float v[4] = {0, 0, 0, 0};
    soa::aaf::evaluate(a, tx, 0.0f, v);
    CHECK(v[0] == 1.0f);
    soa::aaf::evaluate(a, tx, 10.0f, v);
    CHECK(v[0] == 3.0f);
    soa::aaf::evaluate(a, tx, 5.0f, v);  // Hermite with zero tangents: the midpoint
    CHECK(v[0] == 2.0f);
    soa::aaf::evaluate(a, tx, -5.0f, v);  // pre 0: hold the first key
    CHECK(v[0] == 1.0f);
    soa::aaf::evaluate(a, tr, 2.5f, v);
    CHECK(v[0] == 2.5f && v[1] == 5.0f && v[2] == 7.5f);
    soa::aaf::evaluate(a, tr, 12.5f, v);  // post 2 (cycle): 12.5 -> 2.5
    CHECK(v[0] == 2.5f && v[1] == 5.0f && v[2] == 7.5f);
    soa::aaf::evaluate(a, rq, 3.0f, v);
    CHECK(v[3] == 1.0f && v[0] == 0.0f);
}

}  // namespace

int main() {
    test_codecs();
    test_vertex_format();
    test_asf();
    test_aaf();
    if (g_fail) {
        fprintf(stderr, "soa_models_tests: %d failures\n", g_fail);
        return 1;
    }
    printf("soa_models_tests: ok\n");
    return 0;
}
