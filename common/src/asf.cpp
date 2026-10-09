// ASF scenes: the node tree, the mesh objects, their materials and textures (soa/asf.h).
#include <soa/asf.h>
#include <soa/aska_image.h>

#include <cstdio>

namespace soa::asf {

using aff::rd16;
using aff::rd32;
using aff::rd64;
using aff::rdf;
using aff::tag_is;

namespace {
void fail(std::string* err, const std::string& why) {
    if (err) *err = why;
}
std::string strip_r(const std::string& s) { return s.rfind("R:", 0) == 0 ? s.substr(2) : s; }
std::string cstr(const uint8_t* p, size_t n) {
    size_t k = 0;
    while (k < n && p[k]) k++;
    return std::string((const char*)p, k);
}
}  // namespace

// ---- vertex formats -------------------------------------------------------------------------------

bool type_info(uint8_t type, TypeInfo& o) {
    // RenderDeviceGL::BindVertexFormat(int, int, void*): type -> (size, GL type, normalized)
    switch (type) {
    case 1: o = {1, 0x1406, false, 4}; return true;
    case 2: o = {2, 0x1406, false, 8}; return true;
    case 3: o = {3, 0x1406, false, 12}; return true;
    case 4: o = {4, 0x1406, false, 16}; return true;
    case 5: o = {2, 0x140b, false, 4}; return true;   // half2
    case 6: o = {4, 0x140b, false, 8}; return true;   // half4
    case 8: o = {4, 0x1402, false, 8}; return true;   // short4
    case 9: o = {2, 0x1402, true, 4}; return true;    // short2 normalized
    case 10: o = {4, 0x1402, true, 8}; return true;   // short4 normalized
    case 11: o = {2, 0x1403, false, 4}; return true;  // ushort2
    case 12: o = {4, 0x1403, false, 8}; return true;  // ushort4
    case 13: o = {2, 0x1403, true, 4}; return true;   // ushort2 normalized
    case 14: o = {4, 0x1403, true, 8}; return true;   // ushort4 normalized
    case 15: o = {4, 0x1401, false, 4}; return true;  // ubyte4
    case 16: case 29: o = {4, 0x1401, true, 4}; return true;  // ubyte4 normalized
    case 23: o = {4, 0x8368, false, 4}; return true;  // GL_UNSIGNED_INT_2_10_10_10_REV
    case 24: o = {4, 0x8d9f, false, 4}; return true;  // GL_INT_2_10_10_10_REV
    default: return false;
    }
}

const char* usage_name(uint8_t u) {
    switch (u) {
    case kPosition: return "POSITION";
    case kColor: return "COLOR";
    case kNormal: return "NORMAL";
    case kTangent: return "TANGENT";
    case kTexcoord: return "TEXCOORD";
    case kBlendWeight: return "WEIGHTS";
    case kBlendIndex: return "JOINTS";
    default: return "";
    }
}

namespace {
// libSOA 3.7.0 @029d1cb0 .. @029d1ea0: element words (type << 8 | usage << 16 | index << 24) and
// their sizes, per bit group of the attribute bits.
const uint32_t kNormalWord[9] = {0x30400, 0x30300, 0x30300, 0x31800, 0x31c00, 0x30300, 0x30300, 0x30300, 0x30a00};
const uint32_t kNormalSize[9] = {0x10, 0xc, 0xc, 0x4, 0x4, 0xc, 0xc, 0xc, 0x8};
const uint32_t kUv0Word[13] = {0x50200, 0x50400, 0x50600, 0x50f00, 0x50100, 0x50c00, 0x50500, 0x50d00, 0x50d00, 0x50e00, 0x50900, 0x50d00, 0x50a00};
const uint32_t kUv0Size[13] = {0x8, 0x10, 0x8, 0x4, 0x4, 0x8, 0x4, 0x4, 0x4, 0x8, 0x4, 0x4, 0x8};
const uint32_t kUv1Word[12] = {0x1050400, 0x1050200, 0x1050d00, 0x1050e00, 0x1050600, 0x1050f00, 0x1050100, 0x1050c00, 0x1050900, 0x1050a00, 0x1050d00, 0x1050500};
const uint32_t kUv1Size[12] = {0x10, 0x8, 0x4, 0x8, 0x8, 0x4, 0x4, 0x8, 0x4, 0x8, 0x4, 0x4};
const uint32_t kUv2Word[12] = {0x2050200, 0x2050400, 0x2050d00, 0x2050e00, 0x2050600, 0x2050f00, 0x2050100, 0x2050c00, 0x2050900, 0x2050a00, 0x2050d00, 0x2050500};
const uint32_t kUv3Word[12] = {0x3050200, 0x3050400, 0x3050d00, 0x3050e00, 0x3050600, 0x3050f00, 0x3050100, 0x3050c00, 0x3050900, 0x3050a00, 0x3050d00, 0x3050500};
const uint32_t kUv23Size[12] = {0x8, 0x10, 0x4, 0x8, 0x8, 0x4, 0x4, 0x8, 0x4, 0x8, 0x4, 0x4};
const uint32_t kTangentWord[8] = {0x40400, 0x40600, 0x41800, 0x41800, 0x41800, 0x41800, 0x41800, 0x40a00};
const uint32_t kTangentSize[8] = {0x10, 0x8, 0x4, 0x4, 0x4, 0x4, 0x4, 0x8};
}  // namespace

bool vertex_format(uint64_t bits, std::vector<VertexElement>& out) {
    out.clear();
    uint32_t lo = (uint32_t)bits, hi = (uint32_t)(bits >> 32);
    uint32_t off = 0;
    auto add = [&](uint32_t word) {
        VertexElement e;
        e.offset = (uint8_t)(off & 0xff);
        e.type = (uint8_t)(word >> 8);
        e.usage = (uint8_t)(word >> 16);
        e.index = (uint8_t)(word >> 24);
        out.push_back(e);
    };
    // position (bits 0-3)
    switch (lo & 0xf) {
    case 0: break;
    case 1: add(0x10300); off = 0xc; break;
    case 4: add(0x10400); off = 0x10; break;
    case 8: add(0x10600); off = 8; break;
    case 9: add(0x10200); off = 8; break;
    case 0xc: add(0x10800); off = 8; break;
    default: return false;
    }
    // normal (bits 4-7)
    if (bits & 0xf0) {
        uint32_t i = (uint32_t)((bits & 0xf0) >> 4) - 1;
        if (i > 8 || !((0x139u >> i) & 1)) return false;
        add(kNormalWord[i]);
        off += kNormalSize[i];
    }
    if (bits & 0x300000000000ull) {  // a fifth texture set (bits 44-45)
        if ((hi & 0x3000) != 0x1000) return false;
        add(0x4050a00);
        off += 8;
    }
    if ((lo >> 28) & 1) {  // colour, ubyte4 normalized
        add(0x21d00);
        off += 4;
    } else if ((hi >> 5) & 1) {  // colour, float4
        add(0x20400);
        off += 0x10;
    }
    if ((hi >> 4) & 1) { add(0x6051d00); off += 4; }
    if ((hi >> 6) & 1) { add(0x6051d00); off += 4; }
    auto group = [&](uint64_t mask, int shift, int max, uint32_t valid, const uint32_t* words, const uint32_t* sizes) {
        if (!(bits & mask)) return true;
        uint32_t i = (uint32_t)((bits & mask) >> shift) - 1;
        if ((int)i > max || !((valid >> i) & 1)) return false;
        add(words[i]);
        off += sizes[i];
        return true;
    };
    if (!group(0xf00, 8, 12, 0x177f, kUv0Word, kUv0Size)) return false;
    if (!group(0xf000, 12, 11, 0xbff, kUv1Word, kUv1Size)) return false;
    if (!group(0xf00000, 20, 11, 0xbff, kUv2Word, kUv23Size)) return false;
    if (!group(0xf000000, 24, 11, 0xbff, kUv3Word, kUv23Size)) return false;
    if (!group(0xf0000, 16, 7, 0x8b, kTangentWord, kTangentSize)) return false;
    // blend weights (bits 40-43)
    if (bits & 0xf0000000000ull) {
        switch (hi & 0xf00) {
        case 0x100: add(0x60e00); off += 8; break;
        case 0x200: add(0x60d00); off += 4; break;
        case 0x300: add(0x60a00); off += 8; break;
        case 0x400: add(0x60900); off += 4; break;
        case 0x500: add(0x60400); off += 0x10; break;
        case 0x600: add(0x60200); off += 8; break;
        default: break;  // (the game's jump table rejects 7+ by its bound check: no element)
        }
    }
    if ((lo >> 30) & 1) add(0x70f00);  // blend indices, ubyte4
    return true;
}

// ---- nodes ----------------------------------------------------------------------------------------

const char* node_kind_name(int k) {
    switch (k) {
    case kRoot: return "root";
    case kTransform: return "transform";
    case kJoint: return "joint";
    case kObject: return "mesh";
    case kDynamicsChain: return "dynamics-chain";
    case 19: return "collision-group";
    case kCollisionSphere: return "collision-sphere";
    case kCollisionCapsule: return "collision-capsule";
    case kCollisionPlane: return "collision-plane";
    default: return "other";
    }
}

namespace {

void read_vec(const uint8_t* p, std::array<float, 4>& v) {
    for (int i = 0; i < 4; i++) v[i] = rdf(p + i * 4);
}

bool load_tree(const Bytes& d, size_t t, Scene& s, std::string* err) {
    uint32_t count = rd32(&d[t + 0x10]);
    size_t end = t + rd32(&d[t + 0xc]);
    if (end > d.size() || end <= t) end = d.size();
    size_t p = t + 0x110;
    s.nodes.reserve(count);
    while (s.nodes.size() < count) {
        if (p + 0x50 > end) return fail(err, "node tree truncated"), false;
        uint32_t size = rd32(&d[p + 0xc]);
        int kind = d[p + 0x49];
        int extra = d[p + 0x4d];
        uint16_t name_index = rd16(&d[p + 0x4e]);
        for (int k = 0; k <= extra; k++) {
            Node n;
            n.index = (int)s.nodes.size();
            if (k == 0) {
                n.raw_name = cstr(&d[p + 0x10], 32);
            } else {
                size_t li = (size_t)name_index + k - 1;
                n.raw_name = li < s.link_names.size() ? s.link_names[li] : "";
            }
            n.name = strip_r(n.raw_name);
            n.kind = kind == 0x2f ? 1 : kind;  // (CreateTree treats kind 0x2f as 1)
            n.hash = rd32(&d[p + 0x30]);
            n.link = rd32(&d[p + 0x34]);
            int parent = (int)rd32(&d[p + 0x3c]);
            n.parent = n.index == 0 ? -1 : parent;
            n.children = rd16(&d[p + 0x40]);
            n.flags = d[p + 0x4b];
            if (size >= 0x100) {
                read_vec(&d[p + 0x80], n.pos);
                read_vec(&d[p + 0x90], n.rot);
                read_vec(&d[p + 0xa0], n.scale);
                read_vec(&d[p + 0xb0], n.pos_offset);
                for (int r = 0; r < 4; r++) read_vec(&d[p + 0xc0 + r * 16], n.pivot[r]);
            }
            if (kind == kJoint && size >= 0x150) {
                n.joint = true;
                for (int i = 0; i < 16; i++) n.inverse_bind[i] = rdf(&d[p + 0x100 + i * 4]);
                read_vec(&d[p + 0x140], n.joint_orient);
            }
            n.chunk = p;
            n.chunk_size = size;
            s.nodes.push_back(n);
        }
        if (size == 0) break;
        p += size;
    }
    return true;
}

// The ' FIA' chunk of an object: its 'auid' chunk names the AMF block that holds the nested
// ' FIA' header and one 'Xgmi' image header per mip level.
bool load_texture(const Bytes& d, size_t fia, Scene& s, Texture& t, std::string* err) {
    size_t end = fia + rd32(&d[fia + 0xc]);
    size_t au = SIZE_MAX;
    for (size_t q = fia + 0x10; q + 0x30 <= end; q += 16)
        if (tag_is(&d[q], "diua")) { au = q; break; }
    if (au == SIZE_MAX) return fail(err, "texture without an auid chunk"), false;
    t.header = aff::auid_at(&d[au + 0x20]);
    Bytes h;
    if (!s.amf.block(t.header, h, err)) return false;
    if (h.size() < 0x10 || !tag_is(h.data(), " FIA")) return fail(err, "texture block isn't an AIF header"), false;
    for (size_t q = 0x10; q + 0x70 <= h.size(); q += 0x70) {
        if (!tag_is(&h[q], "Xgmi")) break;
        if (t.levels.empty()) {
            t.id = rd32(&h[q + 0x10]);
            t.cls = rd32(&h[q + 0x14]);
        }
        TextureLevel l;
        l.fmt = h[q + 0x20];
        l.w = rd16(&h[q + 0x28]);
        l.h = rd16(&h[q + 0x2a]);
        l.pixels = aff::auid_at(&h[q + 0x40]);
        t.levels.push_back(l);
    }
    return !t.levels.empty() || (fail(err, "texture without images"), false);
}

bool load_material(const Bytes& d, size_t m, Material& mat) {
    if (m + 0x40 > d.size()) return false;
    mat.chunk = m;
    int ntex = d[m + 0x18], nconst = d[m + 0x16];
    mat.flags = rd32(&d[m + 0x3c]);
    mat.blend = d[m + 0x41];
    size_t tex = m + (int32_t)rd32(&d[m + 0x2c]);
    for (int i = 0; i < ntex && tex + (i + 1) * 32 <= d.size(); i++) {
        const uint8_t* r = &d[tex + i * 32];
        TextureRef t;
        t.id = rd32(r);
        t.cls = rd32(r + 4);
        t.word8 = rd32(r + 8);
        t.wrap = rd16(r + 0xc);
        t.slot_kind = rd16(r + 0xe);
        memcpy(t.raw.data(), r, 32);
        mat.textures.push_back(t);
    }
    size_t c = m + (int32_t)rd32(&d[m + 0x20]);
    for (int i = 0; i < nconst && c + (i + 1) * 8 <= d.size(); i++) {
        const uint8_t* e = &d[c + i * 8];
        ShaderConst k;
        k.id = rd16(e);
        k.index = e[2];
        int n = e[3] >> 2;
        size_t v = c + i * 8 + (int32_t)rd32(e + 4);
        for (int j = 0; j < n && v + (j + 1) * 16 <= d.size(); j++) {
            std::array<float, 4> x;
            read_vec(&d[v + j * 16], x);
            k.values.push_back(x);
        }
        mat.constants.push_back(k);
    }
    size_t sz = rd32(&d[m + 4]);
    if (m + sz <= d.size()) mat.raw.assign(d.begin() + m, d.begin() + m + sz);
    return true;
}

bool load_object(const Bytes& d, size_t oa, Scene& s, Object& o, std::string* err, std::vector<std::string>* warn) {
    o.chunk = oa;
    o.name = strip_r(cstr(&d[oa + 0xb0], 32));
    int nmesh = rd16(&d[oa + 0x70]);
    int ntex = rd16(&d[oa + 0x7e]);
    size_t p = oa + 0xd0;
    // the textures, then '__lm' (the material list), an optional 'lpnb' (the bones), then the
    // meshsets ('mess')
    for (int i = 0; i < ntex; i++) {
        if (p + 16 > d.size() || !tag_is(&d[p], " FIA")) return fail(err, o.name + ": expected a texture chunk"), false;
        Texture t;
        std::string e;
        if (!load_texture(d, p, s, t, &e)) {
            if (warn) warn->push_back(o.name + ": texture " + std::to_string(i) + ": " + e);
        }
        o.textures.push_back(t);
        p += rd32(&d[p + 0xc]);
    }
    while (p + 16 <= d.size() && !tag_is(&d[p], "__lm")) {
        uint32_t n = rd32(&d[p + 0xc]);
        if (!n) return fail(err, o.name + ": no material list"), false;
        p += n;
    }
    p += rd32(&d[p + 0xc]);
    if (p + 16 <= d.size() && tag_is(&d[p], "lpnb")) {
        int n = (int)(rd32(&d[p + 4]) - 0x10) / 2;
        for (int i = 0; i < n; i++) o.bones.push_back(rd16(&d[p + 0x10 + i * 2]));
    }
    while (p + 16 <= d.size() && !tag_is(&d[p], "ssem")) {
        uint32_t n = rd32(&d[p + 0xc]);
        if (!n) return fail(err, o.name + ": no meshsets"), false;
        p += n;
    }
    std::vector<size_t> mat_chunks;
    for (int k = 0; k < nmesh; k++) {
        if (p + 0x20 > d.size() || !tag_is(&d[p], "ssem")) return fail(err, o.name + ": meshset chunk expected"), false;
        Meshset m;
        size_t body = p + (int32_t)rd32(&d[p + 0x10]);
        size_t mat = p + (int32_t)rd32(&d[p + 0x14]);
        int ref = (int8_t)d[p + 0x19];
        int16_t shares = (int16_t)rd16(&d[p + 0x1c]);
        m.flags = rd16(&d[p + 0x1e]);
        size_t mi = 0;
        for (; mi < mat_chunks.size() && mat_chunks[mi] != mat; mi++) {}
        if (mi == mat_chunks.size()) {
            Material mm;
            load_material(d, mat, mm);
            o.materials.push_back(mm);
            mat_chunks.push_back(mat);
        }
        m.material = (int)mi;
        if (shares != 0 && ref != k) {
            m.shares = ref;  // AofHandler::Attach: RenderablePrimitive::CreateReference(meshset ref)
        } else {
            m.vertex_count = rd32(&d[body + 0x10]);
            m.index_count = rd32(&d[body + 0x14]);
            m.prim = d[body + 0x18];
            size_t il = body + 0x20;
            if (tag_is(&d[il], "ipnb")) {
                int n = (int)(rd32(&d[il + 4]) - 0x10) / 2;
                for (int i = 0; i < n; i++) m.palette.push_back(rd16(&d[il + 0x10 + i * 2]));
                il += rd32(&d[il + 0xc]);
            }
            size_t vl = il + rd32(&d[il + 0xc]);
            m.asm_bits = rd64(&d[vl + 0x10]);
            m.stride = rd16(&d[vl + 0x18]);
            m.index32 = m.vertex_count > 0x10000;
            if (!vertex_format(m.asm_bits, m.elements) && warn)
                warn->push_back(o.name + ": meshset " + std::to_string(k) + ": vertex bits rejected by CreateVertexFormat");
            std::string e;
            // index list: inline (AUID zero) at chunk + its +0x10, else the AMF block
            m.index_block = aff::auid_at(&d[il + 0x20]);
            size_t ibytes = (size_t)m.index_count * (m.index32 ? 4 : 2);
            if (m.index_block.zero()) {
                size_t at = il + rd32(&d[il + 0x10]);
                if (at + ibytes <= d.size()) m.indices.assign(d.begin() + at, d.begin() + at + ibytes);
            } else if (!s.amf.block(m.index_block, m.indices, &e) && warn) {
                warn->push_back(o.name + ": meshset " + std::to_string(k) + ": indices: " + e);
            }
            m.vertex_block = aff::auid_at(&d[vl + 0x20]);
            size_t vbytes = (size_t)m.vertex_count * m.stride;
            if (m.vertex_block.zero()) {
                size_t at = vl + rd32(&d[vl + 0x1c]);
                if (at + vbytes <= d.size()) m.vertices.assign(d.begin() + at, d.begin() + at + vbytes);
            } else if (!s.amf.block(m.vertex_block, m.vertices, &e) && warn) {
                warn->push_back(o.name + ": meshset " + std::to_string(k) + ": vertices: " + e);
            }
        }
        o.meshsets.push_back(std::move(m));
        p += rd32(&d[p + 0xc]);
    }
    return true;
}

}  // namespace

bool load(const Bytes& d, Scene& s, std::string* err, std::vector<std::string>* warn) {
    s = Scene();
    if (d.size() < 0x40 || !tag_is(d.data(), " FSA")) return fail(err, "not an ASF file"), false;
    std::string e;
    if (!s.amf.parse(d, &e) && warn) warn->push_back("AMF: " + e);
    // the resource header ('aRF ', +0x10): its +0xc is the offset of the file's own header ('head'
    // chunk), whose +0xc is the offset of the first scene chunk
    size_t arf = 0x10;
    if (!tag_is(&d[arf], " FRa")) return fail(err, "no resource chunk"), false;
    size_t head = arf + rd32(&d[arf + 0xc]);
    if (head + 16 > d.size()) return fail(err, "no file header"), false;
    size_t first = head + rd32(&d[head + 0xc]);
    size_t tree = SIZE_MAX, names = SIZE_MAX;
    aff::walk_chunks(d, first, s.amf.present() ? d.size() : d.size(), [&](size_t p) {
        if (tag_is(&d[p], "_foe") || tag_is(&d[p], " FMA")) return false;
        if (tag_is(&d[p], "eert")) tree = p;
        if (tag_is(&d[p], "lnbc")) names = p;
        return true;
    });
    if (names != SIZE_MAX) {
        uint32_t n = rd32(&d[names + 0x10]);
        for (uint32_t i = 0; i < n && names + 0x20 + (i + 1) * 0x20 <= d.size(); i++)
            s.link_names.push_back(cstr(&d[names + 0x20 + i * 0x20], 0x20));
    }
    if (tree == SIZE_MAX) return fail(err, "no node tree"), false;
    if (!load_tree(d, tree, s, err)) return false;
    for (Node& n : s.nodes) {
        if (n.kind != kObject) continue;
        size_t oa = n.link;
        if (oa + 0xd0 > d.size() || !tag_is(&d[oa], "__oa")) {
            if (warn) warn->push_back(n.name + ": its object chunk isn't at 0x" + std::to_string(oa));
            continue;
        }
        Object o;
        o.node = n.index;
        if (!load_object(d, oa, s, o, err, warn)) return false;
        n.object = (int)s.objects.size();
        s.objects.push_back(std::move(o));
    }
    return true;
}

bool decode_texture(const Scene& s, const TextureLevel& t, Bytes& rgba, std::string* err) {
    size_t n = 0;
    const uint8_t* p = s.amf.raw_block(t.pixels, &n);
    if (!p) return fail(err, "pixel block " + t.pixels.hex() + " not found"), false;
    aska::Bytes copy(p, p + n);
    aska::ImageRef r;
    r.data = 0;
    r.data_size = n;
    r.fmt = t.fmt;
    r.w = t.w;
    r.h = t.h;
    return aska::decode_image(copy, r, rgba, err);
}

}  // namespace soa::asf
