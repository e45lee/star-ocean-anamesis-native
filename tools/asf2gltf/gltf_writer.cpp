// asf2gltf's glTF writer (gltf_writer.h). The mapping from the game's scene (docs/notes.md "Meshes
// (ASF)", "glTF export") in short:
//   nodes      every ASF node, in file order, under one extra root that scales centimetres to
//              metres; joints: T(pos) * R(joint orient (x) rotation) * S (Aska::MatrixCalcFunc),
//              other nodes: T(pos + offset + R(A - S.B)) * R * S with the pivot terms A (+0xd0),
//              B (+0xe0) (HierarchicalObjectContainer::MakeMatrix)
//   meshes     one per mesh object, one primitive per meshset; attributes converted to floats
//              (positions' w and a fourth texture component kept as _POSITION_W / _TEXCOORDn_ZW)
//   skins      one per mesh object: its bone list ('lpnb'), inverse bind matrices from the joints
//   materials  metallic-roughness approximations of the game's toon shaders: the base colour
//              texture and normal map found in the material's shader graph, the rest in extras
//   textures   level 0 of every referenced texture as PNG (RG11 normal maps with z rebuilt)
#include "gltf_writer.h"

#include <soa/aaf.h>
#include <soa/png.h>

#include <nlohmann/json.hpp>

#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <set>

using json = nlohmann::ordered_json;
using soa::aff::Bytes;
namespace asf = soa::asf;

namespace gltf {

namespace {

constexpr int kFloat = 5126, kUByte = 5121, kUShort = 5123, kUInt = 5125;

std::string hex32(uint32_t v) {
    char b[16];
    snprintf(b, sizeof b, "0x%08x", v);
    return b;
}
std::string hexbytes(const uint8_t* p, size_t n) {
    std::string s;
    char b[4];
    for (size_t i = 0; i < n; i++) snprintf(b, sizeof b, "%02x", p[i]), s += b;
    return s;
}

struct Quat {
    double x = 0, y = 0, z = 0, w = 1;
};
Quat qmul(const Quat& a, const Quat& b) {  // Hamilton product a*b (b applied first)
    return {a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y, a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
            a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w, a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z};
}
Quat qnorm(Quat q) {
    double n = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    if (n == 0) return {};
    return {q.x / n, q.y / n, q.z / n, q.w / n};
}
void qrot(const Quat& q, const double v[3], double out[3]) {
    double x = q.x, y = q.y, z = q.z, w = q.w;
    double R[3][3] = {{1 - 2 * y * y - 2 * z * z, 2 * x * y - 2 * w * z, 2 * x * z + 2 * w * y},
                      {2 * x * y + 2 * w * z, 1 - 2 * x * x - 2 * z * z, 2 * y * z - 2 * w * x},
                      {2 * x * z - 2 * w * y, 2 * y * z + 2 * w * x, 1 - 2 * x * x - 2 * y * y}};
    for (int i = 0; i < 3; i++) out[i] = R[i][0] * v[0] + R[i][1] * v[1] + R[i][2] * v[2];
}

// The binary buffer and its views / accessors.
struct Builder {
    json doc;
    Bytes bin;
    size_t view(const void* data, size_t n, int target = 0, size_t stride = 0) {
        while (bin.size() % 4) bin.push_back(0);
        size_t off = bin.size();
        bin.insert(bin.end(), (const uint8_t*)data, (const uint8_t*)data + n);
        json v = {{"buffer", 0}, {"byteOffset", off}, {"byteLength", n}};
        if (stride) v["byteStride"] = stride;
        if (target) v["target"] = target;
        doc["bufferViews"].push_back(v);
        return doc["bufferViews"].size() - 1;
    }
    size_t accessor(const void* data, size_t count, int ctype, const char* type, int comps, int target,
                    bool normalized = false, bool minmax = false) {
        size_t csize = ctype == kFloat || ctype == kUInt ? 4 : ctype == kUShort ? 2 : 1;
        size_t n = count * comps * csize;
        json a = {{"bufferView", view(data, n, target)}, {"componentType", ctype}, {"count", count}, {"type", type}};
        if (normalized) a["normalized"] = true;
        if (minmax && ctype == kFloat && count) {
            const float* f = (const float*)data;
            json mn = json::array(), mx = json::array();
            for (int c = 0; c < comps; c++) {
                float lo = f[c], hi = f[c];
                for (size_t i = 1; i < count; i++) lo = std::min(lo, f[i * comps + c]), hi = std::max(hi, f[i * comps + c]);
                mn.push_back(lo);
                mx.push_back(hi);
            }
            a["min"] = mn;
            a["max"] = mx;
        }
        doc["accessors"].push_back(a);
        return doc["accessors"].size() - 1;
    }
    size_t image_png(const std::string& name, int w, int h, const Bytes& rgba) {
        std::vector<uint8_t> png;
        soa::png_encode(w, h, 4, rgba.data(), png);
        size_t v = view(png.data(), png.size());
        doc["images"].push_back({{"name", name}, {"mimeType", "image/png"}, {"bufferView", v}});
        return doc["images"].size() - 1;
    }
};

// One vertex attribute read as floats (normalized types mapped to [0,1] / [-1,1] as GL does).
bool read_element(const asf::Meshset& m, const asf::VertexElement& e, size_t v, float out[4], int& comps) {
    asf::TypeInfo t;
    if (!asf::type_info(e.type, t)) return false;
    comps = t.components;
    const uint8_t* p = m.vertices.data() + v * m.stride + e.offset;
    if (v * m.stride + e.offset + t.bytes > m.vertices.size()) return false;
    for (int c = 0; c < comps; c++) {
        switch (t.gl_type) {
        case 0x1406: memcpy(&out[c], p + c * 4, 4); break;
        case 0x140b: {
            uint16_t h;
            memcpy(&h, p + c * 2, 2);
            int s = h >> 15, ex = (h >> 10) & 31, mt = h & 1023;
            float f = ex == 0 ? std::ldexp((float)mt, -24) : ex == 31 ? INFINITY : std::ldexp((float)(mt | 1024), ex - 25);
            out[c] = s ? -f : f;
            break;
        }
        case 0x1402: {
            int16_t s;
            memcpy(&s, p + c * 2, 2);
            out[c] = t.normalized ? std::max(-1.0f, s / 32767.0f) : (float)s;
            break;
        }
        case 0x1403: {
            uint16_t s;
            memcpy(&s, p + c * 2, 2);
            out[c] = t.normalized ? s / 65535.0f : (float)s;
            break;
        }
        case 0x1401: out[c] = t.normalized ? p[c] / 255.0f : (float)p[c]; break;
        default: return false;  // the packed 10-10-10-2 types: not seen in the 3.7.0 models
        }
    }
    return true;
}

// The material's shader graph (the 'stam' +0x1c block: records {u16 size, u16 op, ...}): which
// texture slot feeds the base colour (op 0x85 samples slot +0xc into register +0xf; the lighting
// op 0x49's first register argument is the albedo) and which one is a normal map (op 0x85 with
// mode 0x0c, decoded by op 0x86). Partly understood: docs/notes.md "Materials".
struct GraphRoles {
    int base = -1, normal = -1;
    bool lit = false;  // has the lighting op
    std::vector<std::pair<int, int>> samples;  // (slot, register)
};
GraphRoles graph_roles(const asf::Material& mat) {
    GraphRoles r;
    if (mat.raw.size() < 0x20) return r;
    uint32_t g = soa::aff::rd32(&mat.raw[0x1c]);
    std::map<int, int> reg_slot;
    for (size_t q = g; q + 8 <= mat.raw.size();) {
        uint16_t size = soa::aff::rd16(&mat.raw[q]), op = soa::aff::rd16(&mat.raw[q + 2]);
        if (size < 8 || q + size > mat.raw.size()) break;
        const uint8_t* p = &mat.raw[q + 8];
        if (op == 0x85 && size >= 0x10) {
            int slot = soa::aff::rd16(p + 4), mode = p[6], reg = p[7];
            reg_slot[reg] = slot;
            r.samples.push_back({slot, reg});
            if (mode == 0x0c) r.normal = slot;
        } else if (op == 0x49 && size >= 0xc) {
            r.lit = true;
            auto it = reg_slot.find(p[1]);
            if (it != reg_slot.end()) r.base = it->second;
        }
        q += size;
    }
    return r;
}

int prim_mode(int prim) {
    switch (prim) {
    case 0: return 4;  // triangles
    case 2: return 1;  // lines
    case 3: return 3;  // line strip
    case 4: return 5;  // triangle strip
    case 5: return 6;  // triangle fan
    case 7: return 0;  // points
    default: return -1;
    }
}

}  // namespace

bool write(const Input& in, const Options& opt, const std::string& out_path, std::string* err) {
    const asf::Scene& s = *in.scene;
    Builder b;
    json& doc = b.doc;
    doc["asset"] = {{"version", "2.0"}, {"generator", "asf2gltf (star-ocean-anamnesis-reverse)"}};
    doc["asset"]["extras"] = {{"source", in.source_name}};
    std::set<std::string> ext_used;

    // physics-driven joints: the dynamics chains' records ({u32 node, ...} x count at +0x128)
    std::map<int, std::string> physics;
    for (const asf::Node& n : s.nodes) {
        if (n.kind != asf::kDynamicsChain || n.chunk_size < 0x130) continue;
        // (records are read from the scene file through the node's chunk: the node keeps none)
    }

    // ---- nodes
    size_t root = s.nodes.size();
    std::vector<std::vector<int>> kids(s.nodes.size());
    for (const asf::Node& n : s.nodes)
        if (n.parent >= 0 && n.parent < (int)s.nodes.size() && n.parent != n.index) kids[n.parent].push_back(n.index);
    for (const asf::Node& n : s.nodes) {
        json j;
        j["name"] = n.name;
        double t[3] = {n.pos[0], n.pos[1], n.pos[2]};
        Quat r = {n.rot[0], n.rot[1], n.rot[2], n.rot[3]};
        if (n.joint) {
            r = qmul({n.joint_orient[0], n.joint_orient[1], n.joint_orient[2], n.joint_orient[3]}, r);
        } else {
            double a[3], rv[3];
            for (int i = 0; i < 3; i++) {
                t[i] += n.pos_offset[i];
                a[i] = n.pivot[1][i] - n.scale[i] * n.pivot[2][i];
            }
            qrot(r, a, rv);
            for (int i = 0; i < 3; i++) t[i] += rv[i];
        }
        r = qnorm(r);
        if (t[0] || t[1] || t[2]) j["translation"] = {t[0], t[1], t[2]};
        if (r.x || r.y || r.z || r.w != 1) j["rotation"] = {r.x, r.y, r.z, r.w};
        if (n.scale[0] != 1 || n.scale[1] != 1 || n.scale[2] != 1) j["scale"] = {n.scale[0], n.scale[1], n.scale[2]};
        if (!kids[n.index].empty()) j["children"] = kids[n.index];
        json x = {{"asf_kind", asf::node_kind_name(n.kind)}, {"asf_kind_code", n.kind}, {"asf_index", n.index}};
        if (n.joint && (n.joint_orient[0] || n.joint_orient[1] || n.joint_orient[2]))
            x["joint_orient"] = {n.joint_orient[0], n.joint_orient[1], n.joint_orient[2], n.joint_orient[3]};
        bool piv = false;
        for (int i = 0; i < 3; i++) piv |= n.pivot[1][i] != 0 || n.pivot[2][i] != 0 || n.pos_offset[i] != 0;
        if (piv) x["pivots_baked"] = true;
        auto ph = physics.find(n.index);
        if (ph != physics.end()) x["physics_driven"] = ph->second;
        j["extras"] = x;
        doc["nodes"].push_back(j);
    }
    json rootj = {{"name", "asf2gltf_root (cm to m)"}, {"scale", {0.01, 0.01, 0.01}}, {"children", json::array()}};
    for (const asf::Node& n : s.nodes)
        if (n.parent < 0 || n.parent == n.index || n.parent >= (int)s.nodes.size()) rootj["children"].push_back(n.index);
    rootj["extras"] = {{"note", "the game's units are centimetres; this node scales them to metres"}};
    doc["nodes"].push_back(rootj);
    doc["scenes"] = {{{"name", in.source_name}, {"nodes", {root}}}};
    doc["scene"] = 0;

    // ---- textures (by id, across the scene's objects)
    std::map<uint32_t, const asf::Texture*> tex_by_id;
    for (const auto& o : s.objects)
        for (const auto& t : o.textures)
            if (!t.levels.empty()) tex_by_id.emplace(t.id, &t);
    std::map<uint32_t, int> tex_index;  // id -> glTF texture
    auto texture_of = [&](uint32_t id, bool normal) -> int {
        auto have = tex_index.find(id | (normal ? 0x80000000u : 0));
        if (have != tex_index.end()) return have->second;
        auto it = tex_by_id.find(id);
        if (it == tex_by_id.end()) return -1;
        const asf::TextureLevel& l = it->second->levels[0];
        Bytes rgba;
        std::string e;
        if (!asf::decode_texture(s, l, rgba, &e)) return -1;
        if (normal && (l.fmt == 50 || l.fmt == 51)) {
            for (size_t i = 0; i < rgba.size(); i += 4) {
                double x = rgba[i] / 127.5 - 1, y = rgba[i + 1] / 127.5 - 1;
                double z = std::sqrt(std::max(0.0, 1 - x * x - y * y));
                rgba[i + 2] = (uint8_t)std::lround((z + 1) * 127.5);
            }
        }
        if (doc["samplers"].is_null()) doc["samplers"].push_back({{"magFilter", 9729}, {"minFilter", 9987}, {"wrapS", 10497}, {"wrapT", 10497}});
        size_t img = b.image_png(hex32(id) + (normal ? "_normal" : ""), l.w, l.h, rgba);
        doc["textures"].push_back({{"sampler", 0}, {"source", img}, {"name", hex32(id)}});
        int idx = (int)doc["textures"].size() - 1;
        tex_index[id | (normal ? 0x80000000u : 0)] = idx;
        return idx;
    };

    // ---- objects: meshes, skins, materials
    for (const asf::Object& o : s.objects) {
        json mesh = {{"name", o.name}, {"primitives", json::array()}};
        std::vector<int> mat_index(o.materials.size(), -1);
        for (size_t mi = 0; mi < o.materials.size(); mi++) {
            const asf::Material& m = o.materials[mi];
            GraphRoles roles = graph_roles(m);
            json mj = {{"name", o.name + "_" + std::to_string(mi)}};
            json pbr = {{"metallicFactor", 0.0}, {"roughnessFactor", 0.8}};
            int base_slot = roles.base;
            std::array<float, 4> factor{1, 1, 1, 1};
            for (const auto& c : m.constants)
                if (!roles.lit && c.id == 5 && c.index == 0 && !c.values.empty()) factor = c.values[0];
            if (base_slot < 0 && !roles.lit && !m.textures.empty() && factor == std::array<float, 4>{1, 1, 1, 1}) base_slot = 0;
            if (base_slot >= 0 && base_slot < (int)m.textures.size()) {
                int t = texture_of(m.textures[base_slot].id, false);
                if (t >= 0) pbr["baseColorTexture"] = {{"index", t}};
            }
            if (factor != std::array<float, 4>{1, 1, 1, 1}) pbr["baseColorFactor"] = {factor[0], factor[1], factor[2], 1.0};
            mj["pbrMetallicRoughness"] = pbr;
            if (roles.normal >= 0 && roles.normal < (int)m.textures.size()) {
                int t = texture_of(m.textures[roles.normal].id, true);
                if (t >= 0) mj["normalTexture"] = {{"index", t}};
            }
            json slots = json::array();
            for (size_t k = 0; k < m.textures.size(); k++) {
                const auto& t = m.textures[k];
                json sj = {{"id", hex32(t.id)}, {"class", std::string((const char*)&t.cls, 4)}, {"wrap", t.wrap}, {"kind", t.slot_kind}};
                if ((int)k == base_slot) sj["role"] = "baseColor";
                else if ((int)k == roles.normal) sj["role"] = "normal";
                else if (tex_by_id.count(t.id)) {
                    int ti = texture_of(t.id, false);
                    if (ti >= 0) sj["texture"] = ti;
                } else sj["note"] = "not in this file (supplied by the game)";
                slots.push_back(sj);
            }
            json consts = json::array();
            for (const auto& c : m.constants) {
                json v = json::array();
                for (auto& x : c.values) v.push_back({x[0], x[1], x[2], x[3]});
                consts.push_back({{"id", c.id}, {"index", c.index}, {"values", v}});
            }
            mj["extras"] = {{"asf_texture_slots", slots}, {"asf_constants", consts}, {"asf_flags", hex32(m.flags)},
                            {"asf_blend", m.blend}, {"asf_lit_toon_shader", roles.lit},
                            {"asf_shader_graph", m.raw.size() > 0x20 ? hexbytes(m.raw.data() + soa::aff::rd32(&m.raw[0x1c]),
                                                                           m.raw.size() - soa::aff::rd32(&m.raw[0x1c])) : ""}};
            doc["materials"].push_back(mj);
            mat_index[mi] = (int)doc["materials"].size() - 1;
        }
        // geometry, per meshset (a meshset that draws another's geometry reuses its accessors)
        std::vector<json> attrs(o.meshsets.size());
        std::vector<long> idx_acc(o.meshsets.size(), -1);
        for (size_t k = 0; k < o.meshsets.size(); k++) {
            const asf::Meshset& m = o.meshsets[k];
            if (m.shares >= 0) continue;
            size_t nv = m.vertex_count;
            if (m.vertices.size() < nv * m.stride || nv == 0) continue;
            json a;
            std::map<std::string, int> sets;
            for (const asf::VertexElement& e : m.elements) {
                std::vector<float> f(nv * 4);
                int comps = 0;
                bool ok = true;
                for (size_t v = 0; v < nv && ok; v++) ok = read_element(m, e, v, &f[v * 4], comps);
                if (!ok) continue;
                auto take = [&](int from, int n) {
                    std::vector<float> o2(nv * n);
                    for (size_t v = 0; v < nv; v++)
                        for (int c = 0; c < n; c++) o2[v * n + c] = from + c < comps ? f[v * 4 + from + c] : 0.0f;
                    return o2;
                };
                switch (e.usage) {
                case asf::kPosition: {
                    auto p = take(0, 3);
                    a["POSITION"] = b.accessor(p.data(), nv, kFloat, "VEC3", 3, 34962, false, true);
                    if (comps == 4) {
                        auto w = take(3, 1);
                        a["_POSITION_W"] = b.accessor(w.data(), nv, kFloat, "SCALAR", 1, 34962);
                    }
                    break;
                }
                case asf::kNormal: {
                    auto p = take(0, 3);
                    for (size_t v = 0; v < nv; v++) {
                        float* q = &p[v * 3];
                        float l = std::sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2]);
                        if (l > 0) q[0] /= l, q[1] /= l, q[2] /= l; else q[2] = 1;
                    }
                    a["NORMAL"] = b.accessor(p.data(), nv, kFloat, "VEC3", 3, 34962);
                    break;
                }
                case asf::kTangent: {
                    auto p = take(0, 4);
                    for (size_t v = 0; v < nv; v++) {
                        float* q = &p[v * 4];
                        float l = std::sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2]);
                        if (l > 0) q[0] /= l, q[1] /= l, q[2] /= l; else q[0] = 1;
                        q[3] = q[3] < 0 ? -1.0f : 1.0f;
                    }
                    a["TANGENT"] = b.accessor(p.data(), nv, kFloat, "VEC4", 4, 34962);
                    break;
                }
                case asf::kTexcoord: {
                    std::string nm = "TEXCOORD_" + std::to_string(sets["uv"]++);
                    auto p = take(0, 2);
                    a[nm] = b.accessor(p.data(), nv, kFloat, "VEC2", 2, 34962);
                    if (comps == 4) {
                        auto z = take(2, 2);
                        a["_" + nm + "_ZW"] = b.accessor(z.data(), nv, kFloat, "VEC2", 2, 34962);
                    }
                    break;
                }
                case asf::kColor: {
                    auto p = take(0, 4);
                    a["COLOR_" + std::to_string(sets["color"]++)] = b.accessor(p.data(), nv, kFloat, "VEC4", 4, 34962);
                    break;
                }
                case asf::kBlendWeight: {
                    auto p = take(0, 4);
                    for (size_t v = 0; v < nv; v++) {
                        float* q = &p[v * 4];
                        float sum = q[0] + q[1] + q[2] + q[3];
                        if (sum > 0) for (int c = 0; c < 4; c++) q[c] /= sum; else q[0] = 1;
                    }
                    a["WEIGHTS_0"] = b.accessor(p.data(), nv, kFloat, "VEC4", 4, 34962);
                    break;
                }
                case asf::kBlendIndex: {
                    // palette index -> the object's bone list (the skin's joints)
                    std::vector<uint16_t> j(nv * 4);
                    for (size_t v = 0; v < nv; v++)
                        for (int c = 0; c < 4; c++) {
                            int pi = (int)f[v * 4 + c];
                            j[v * 4 + c] = pi < (int)m.palette.size() ? m.palette[pi] : 0;
                        }
                    a["JOINTS_0"] = b.accessor(j.data(), nv, kUShort, "VEC4", 4, 34962);
                    break;
                }
                default: break;
                }
            }
            if (!a.contains("POSITION")) continue;
            if (a.contains("JOINTS_0") && !a.contains("WEIGHTS_0")) {
                std::vector<float> w(nv * 4, 0.0f);
                for (size_t v = 0; v < nv; v++) w[v * 4] = 1;
                a["WEIGHTS_0"] = b.accessor(w.data(), nv, kFloat, "VEC4", 4, 34962);
            }
            attrs[k] = a;
            if (m.index_count && !m.indices.empty())
                idx_acc[k] = (long)b.accessor(m.indices.data(), m.index_count, m.index32 ? kUInt : kUShort, "SCALAR", 1, 34963);
        }
        bool skinned = false;
        for (size_t k = 0; k < o.meshsets.size(); k++) {
            const asf::Meshset& m = o.meshsets[k];
            size_t g = m.shares >= 0 ? (size_t)m.shares : k;
            if (g >= attrs.size() || attrs[g].is_null()) continue;
            int mode = prim_mode(o.meshsets[g].prim);
            if (mode < 0) continue;
            json p = {{"attributes", attrs[g]}, {"mode", mode}};
            if (idx_acc[g] >= 0) p["indices"] = idx_acc[g];
            if (m.material >= 0) p["material"] = mat_index[m.material];
            json px = {{"asf_meshset", k}, {"asf_vertex_bits", hex32((uint32_t)(o.meshsets[g].asm_bits >> 32)) + hex32((uint32_t)o.meshsets[g].asm_bits).substr(2)},
                       {"asf_stride", o.meshsets[g].stride}};
            json el = json::array();
            for (const auto& e : o.meshsets[g].elements)
                el.push_back({{"usage", asf::usage_name(e.usage)}, {"index", e.index}, {"offset", e.offset}, {"type", e.type}});
            px["asf_vertex_format"] = el;
            p["extras"] = px;
            skinned |= attrs[g].contains("JOINTS_0");
            mesh["primitives"].push_back(p);
        }
        if (mesh["primitives"].empty()) continue;
        doc["meshes"].push_back(mesh);
        size_t mesh_i = doc["meshes"].size() - 1;
        json& node = doc["nodes"][o.node];
        node["mesh"] = mesh_i;
        if (skinned && !o.bones.empty()) {
            std::vector<float> ibm(o.bones.size() * 16);
            json joints = json::array();
            for (size_t i = 0; i < o.bones.size(); i++) {
                int ni = o.bones[i];
                joints.push_back(ni);
                const asf::Node* n = ni < (int)s.nodes.size() ? &s.nodes[ni] : nullptr;
                for (int r = 0; r < 4; r++)
                    for (int c = 0; c < 4; c++)  // column-major from the stored rows
                        ibm[i * 16 + c * 4 + r] = (n && n->joint) ? n->inverse_bind[r * 4 + c] : (r == c ? 1.0f : 0.0f);
            }
            size_t acc = b.accessor(ibm.data(), o.bones.size(), kFloat, "MAT4", 16, 0);
            doc["skins"].push_back({{"name", o.name}, {"joints", joints}, {"inverseBindMatrices", acc}});
            node["skin"] = doc["skins"].size() - 1;
        }
    }

    // ---- animations (soa/aaf.h)
    // (added with the evaluator)

    if (!ext_used.empty()) doc["extensionsUsed"] = std::vector<std::string>(ext_used.begin(), ext_used.end());
    while (b.bin.size() % 4) b.bin.push_back(0);
    std::string base = out_path;
    bool glb = !opt.separate;
    if (opt.separate) {
        std::string bin_name = base;
        size_t dot = bin_name.rfind('.');
        if (dot != std::string::npos) bin_name = bin_name.substr(0, dot);
        bin_name += ".bin";
        std::ofstream bf(bin_name, std::ios::binary);
        bf.write((const char*)b.bin.data(), b.bin.size());
        size_t slash = bin_name.rfind('/');
        doc["buffers"] = {{{"byteLength", b.bin.size()}, {"uri", slash == std::string::npos ? bin_name : bin_name.substr(slash + 1)}}};
    } else {
        doc["buffers"] = {{{"byteLength", b.bin.size()}}};
    }
    std::string js = doc.dump(glb ? -1 : 1);
    std::ofstream f(out_path, std::ios::binary);
    if (!f) { if (err) *err = "cannot write " + out_path; return false; }
    if (!glb) {
        f << js;
        return true;
    }
    while (js.size() % 4) js += ' ';
    auto u32 = [&](uint32_t v) { f.write((const char*)&v, 4); };
    u32(0x46546c67);  // "glTF"
    u32(2);
    u32((uint32_t)(12 + 8 + js.size() + 8 + b.bin.size()));
    u32((uint32_t)js.size());
    u32(0x4e4f534a);  // "JSON"
    f.write(js.data(), js.size());
    u32((uint32_t)b.bin.size());
    u32(0x004e4942);  // "BIN\0"
    f.write((const char*)b.bin.data(), b.bin.size());
    return (bool)f;
}

}  // namespace gltf
