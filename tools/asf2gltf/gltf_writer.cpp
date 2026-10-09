// asf2gltf's glTF writer (gltf_writer.h). The mapping from the game's scene (docs/notes.md "Meshes
// (ASF)", "glTF export") in short:
//   nodes      every ASF node, in file order, under one extra root that scales centimetres to
//              metres and turns the model (which faces -Z) to glTF's +Z; joints: T(pos) * R(joint orient (x) rotation) * S (Aska::MatrixCalcFunc),
//              other nodes: T(pos + offset + R(A - S.B)) * R * S with the pivot terms A (+0xd0),
//              B (+0xe0) (HierarchicalObjectContainer::MakeMatrix)
//   meshes     one per mesh object, one primitive per meshset; attributes converted to floats
//              (positions' w and the third and fourth texture components kept as _POSITION_W, _TEXCOORD_n_Z / _W)
//   skins      one per mesh object: its bone list ('lpnb'), inverse bind matrices from the joints
//   materials  metallic-roughness approximations of the game's toon shaders: the base colour
//              texture and normal map found in the material's shader graph, the rest in extras
//   textures   level 0 of every referenced texture as PNG (RG11 normal maps with z rebuilt)
#include "gltf_writer.h"

#include <soa/aaf.h>
#include <soa/png.h>

#include <nlohmann/json.hpp>

#include <array>
#include <cmath>
#include <functional>
#include <cstdio>
#include <fstream>
#include <cstring>
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

using Mat4 = std::array<double, 16>;  // row-major, column vectors (translation in column 3)
Mat4 identity4() { return {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}; }
Mat4 mul4(const Mat4& a, const Mat4& b) {
    Mat4 r{};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++) r[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
    return r;
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
        std::string png = soa::png_encode(w, h, 4, rgba.data());
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

// The material's shader graph (the 'stam' +0x1c block, records {u16 size, u16 op, payload from +8}),
// read for what a static material can carry: where the albedo, the alpha, the normal map and the
// roughness come from. The meaning of each op was read off the GLSL the game builds from it
// (SOA_GL_DRAW_DUMP, Seaside Maria's 13 materials; docs/notes.md "Materials"):
//   0x85 sample: +0 UV set, +4 texture slot, +6 mode (0x0c: a normal map), +7 register
//   0x02 / 0x2e / 0x03 load constant 5 ("eConstColor_Color_Color<n>") / 0x14 (eALBEDO_CONSTCOLOR) /
//        0x13 (eConstVector) index +0 into register +1;  0x88 the vertex colour into +0
//   0x8c +0 == 1: register +7 = component +4 of register +3 (else an arithmetic form, not followed)
//   0x8a register +7 = register +1 * register +3;  0x8b with a register at +4: the same (the
//        pareo's vertex colour times its texture; else a function of +1, not followed)
//   0x49 (GGX), 0x28 (Lambert), 0x32 (Marschner: hair), 0x24 the lighting: +1 albedo, +2 alpha
//        (the alpha test's); 0x49: +7 the normal, +0xc the roughness (alpha^2 = (r + g) / 2),
//        +0xf the specular reflectance F0
//   0x8d the output: +0 colour, +1 alpha (when it isn't the colour register: the lighting's +2)
struct Src {
    enum Kind { kNone, kConst, kTex, kOther } kind = kNone;
    int slot = -1, uv = 0, comp = -1;       // a texture (comp -1: all of it)
    std::array<float, 4> factor{1, 1, 1, 1};  // times a constant
    bool vertex_color = false;
};
struct GraphInfo {
    bool lit = false;
    int lighting = 0;  // the lighting op
    Src albedo, alpha, normal, roughness, f0;
    std::vector<std::pair<int, int>> uv_of_slot;  // (slot, UV set)
};
GraphInfo read_graph(const asf::Material& mat) {
    GraphInfo r;
    if (mat.raw.size() < 0x24) return r;
    uint32_t g = soa::aff::rd32(&mat.raw[0x1c]), end = soa::aff::rd32(&mat.raw[0x20]);
    auto constant = [&](int id, int index) {
        Src x;
        x.kind = Src::kConst;
        for (const auto& c : mat.constants)
            if (c.id == id && c.index == index && !c.values.empty()) x.factor = c.values[0];
        return x;
    };
    auto mul = [](Src a, Src b) {
        if (a.kind == Src::kNone) return b;
        if (b.kind == Src::kNone) return a;
        if (a.kind == Src::kTex && b.kind == Src::kTex) {
            if (b.vertex_color && !a.vertex_color) std::swap(a, b);
            if (!a.vertex_color) return Src{Src::kOther};
        }
        if (a.kind == Src::kOther || b.kind == Src::kOther) return Src{Src::kOther};
        Src t = a.kind == Src::kTex ? a : b, o = a.kind == Src::kTex ? b : a;
        if (t.vertex_color && o.kind == Src::kTex) {  // the vertex colour times a texture: glTF's COLOR_0 does it
            o.vertex_color = true;
            return o;
        }
        for (int i = 0; i < 4; i++) t.factor[i] *= o.factor[i];
        t.vertex_color |= o.vertex_color;
        return t;
    };
    std::map<int, Src> reg;
    int out_color = -1, out_alpha = -1, lit_alpha = -1;
    std::map<int, Src> at_lighting;
    for (size_t q = g; q + 8 <= mat.raw.size() && q < end;) {
        uint16_t size = soa::aff::rd16(&mat.raw[q]), op = soa::aff::rd16(&mat.raw[q + 2]);
        if (size < 8 || q + size > mat.raw.size()) break;
        const uint8_t* p = &mat.raw[q + 8];
        size_t n = size - 8;
        if (op == 0x85 && n >= 8) {
            Src x;
            x.kind = Src::kTex;
            x.uv = p[0];
            x.slot = soa::aff::rd16(p + 4);
            reg[p[7]] = x;
            r.uv_of_slot.push_back({x.slot, x.uv});
            if (p[6] == 0x0c) r.normal = x;
        } else if ((op == 0x02 || op == 0x2e || op == 0x03) && n >= 4) {
            reg[p[1]] = constant(op == 0x02 ? 5 : op == 0x2e ? 0x14 : 0x13, p[0]);
        } else if (op == 0x88 && n >= 4) {
            Src x;
            x.kind = Src::kTex;  // (a "texture" of white; mul() folds it into the other side)
            x.vertex_color = true;
            reg[p[0]] = x;
        } else if (op == 0x8c && n >= 8) {
            if (p[0] == 1) {
                Src x = reg.count(p[3]) ? reg[p[3]] : Src{Src::kOther};
                if (x.kind == Src::kTex) x.comp = p[4];
                else if (x.kind == Src::kConst) x.factor = {x.factor[p[4] & 3], x.factor[p[4] & 3], x.factor[p[4] & 3], x.factor[p[4] & 3]};
                reg[p[7]] = x;
            } else {
                reg[p[7]] = Src{Src::kOther};
            }
        } else if ((op == 0x8a || (op == 0x8b && n >= 8 && p[4] >= 0x80)) && n >= 8) {
            Src a2 = reg.count(p[1]) ? reg[p[1]] : Src{Src::kOther}, b2 = reg.count(p[3]) ? reg[p[3]] : Src{Src::kOther};
            reg[p[7]] = mul(a2, b2);
        } else if (op == 0x8b && n >= 8) {
            reg[p[7]] = Src{Src::kOther};
        } else if ((op == 0x49 || op == 0x28 || op == 0x32 || op == 0x24) && n >= 3) {
            r.lit = true;
            r.lighting = op;
            r.albedo = reg.count(p[1]) ? reg[p[1]] : Src{};
            lit_alpha = p[2];
            at_lighting = reg;
            if (op == 0x49 && n >= 0x10) {
                if (reg.count(p[0xc])) r.roughness = reg[p[0xc]];
                if (reg.count(p[0xf])) r.f0 = reg[p[0xf]];
            }
        } else if (op == 0x8d && n >= 2) {
            out_color = p[0];
            out_alpha = p[1];
        }
        q += size;
    }
    if (out_alpha >= 0 && out_alpha != out_color) r.alpha = reg.count(out_alpha) ? reg[out_alpha] : Src{};
    else if (lit_alpha >= 0) r.alpha = at_lighting.count(lit_alpha) ? at_lighting[lit_alpha] : Src{};
    if (!r.lit && out_color >= 0) r.albedo = reg.count(out_color) ? reg[out_color] : Src{};
    // a whole vector as the alpha: its w
    if (r.alpha.kind == Src::kTex && r.alpha.comp < 0) r.alpha.comp = 3;
    if (r.alpha.kind == Src::kConst) r.alpha.factor = {r.alpha.factor[3], r.alpha.factor[3], r.alpha.factor[3], r.alpha.factor[3]};
    return r;
}

// Whether the game uploads a texture as sRGB (it then reads its colour channels linearized):
// see docs/notes.md "Meshes (ASF)" (Xgmi).
// (Xgmi +0x26: 2 colour, uploaded sRGB; 4 data (normal maps, the hair's shift), linear; the
// EAC formats have no sRGB form. Checked against the GL formats of Seaside Maria's uploads.)
bool texture_srgb(const asf::Texture& t) { return t.xgmi[0x26] == 2 && (t.levels.empty() || (t.levels[0].fmt != 50 && t.levels[0].fmt != 51)); }

double srgb_to_linear(double c) { return c <= 0.04045 ? c / 12.92 : std::pow((c + 0.055) / 1.055, 2.4); }
double linear_to_srgb(double c) { return c <= 0.0031308 ? c * 12.92 : 1.055 * std::pow(c, 1 / 2.4) - 0.055; }

// The game's space is left-handed: its models are the mirror images of what a right-handed reader
// draws from the same numbers (Seaside Maria's LeftHand came out on her right, her triangles wound
// clockwise: the faces showed their backs). Everything below the root is mirrored in x once it is
// written: node translations (x) and rotations ((x, y, z, w) -> (x, -y, -z, w)), positions, normals,
// tangents (x, and the bitangent sign), the inverse bind matrices (M·IBM·M) and the translation /
// rotation animation outputs. Scale is unchanged. The triangles keep their order: the game's are
// clockwise (against their normals) in its space, counter-clockwise once mirrored, as glTF wants.
void mirror_x(Builder& b, size_t root) {
    json& doc = b.doc;
    auto data = [&](size_t acc) -> float* {
        json& a = doc["accessors"][acc];
        json& v = doc["bufferViews"][(size_t)a["bufferView"]];
        return (float*)&b.bin[(size_t)v["byteOffset"] + (size_t)a.value("byteOffset", 0)];
    };
    for (size_t i = 0; i < doc["nodes"].size(); i++) {
        if (i == root) continue;
        json& n = doc["nodes"][i];
        if (n.contains("translation")) n["translation"][0] = -(double)n["translation"][0];
        if (n.contains("rotation")) {
            n["rotation"][1] = -(double)n["rotation"][1];
            n["rotation"][2] = -(double)n["rotation"][2];
        }
    }
    std::set<size_t> done;
    if (doc.contains("meshes"))
        for (json& mesh : doc["meshes"])
            for (json& p : mesh["primitives"]) {
                for (const char* att : {"POSITION", "NORMAL", "TANGENT"}) {
                    if (!p["attributes"].contains(att)) continue;
                    size_t ai = p["attributes"][att];
                    if (!done.insert(ai).second) continue;
                    json& a = doc["accessors"][ai];
                    size_t comps = std::string(att) == "TANGENT" ? 4 : 3, n = a["count"];
                    float* f = data(ai);
                    for (size_t v = 0; v < n; v++) {
                        f[v * comps] = -f[v * comps];
                        if (comps == 4) f[v * comps + 3] = -f[v * comps + 3];
                    }
                    if (a.contains("min") && a.contains("max")) {
                        double lo = a["min"][0], hi = a["max"][0];
                        a["min"][0] = -hi;
                        a["max"][0] = -lo;
                    }
                }
            }
    if (doc.contains("skins"))
        for (json& sk : doc["skins"]) {
            size_t ai = sk["inverseBindMatrices"];
            if (!done.insert(ai).second) continue;
            float* f = data(ai);
            size_t n = doc["accessors"][ai]["count"];
            for (size_t k = 0; k < n; k++)
                for (int c = 0; c < 4; c++)
                    for (int r = 0; r < 4; r++)
                        if ((r == 0) != (c == 0)) f[k * 16 + c * 4 + r] = -f[k * 16 + c * 4 + r];
        }
    if (doc.contains("animations"))
        for (json& an : doc["animations"])
            for (json& ch : an["channels"]) {
                std::string path = ch["target"]["path"];
                if ((size_t)ch["target"]["node"] == root || (path != "translation" && path != "rotation")) continue;
                size_t ai = an["samplers"][(size_t)ch["sampler"]]["output"];
                if (!done.insert(ai).second) continue;
                json& a = doc["accessors"][ai];
                size_t n = a["count"];
                float* f = data(ai);
                for (size_t v = 0; v < n; v++) {
                    if (path == "translation") f[v * 3] = -f[v * 3];
                    else f[v * 4 + 1] = -f[v * 4 + 1], f[v * 4 + 2] = -f[v * 4 + 2];
                }
                if (a.contains("min") && a.contains("max")) {
                    std::vector<int> neg = path == "translation" ? std::vector<int>{0} : std::vector<int>{1, 2};
                    for (int c : neg) {
                        double lo = a["min"][c], hi = a["max"][c];
                        a["min"][c] = -hi;
                        a["max"][c] = -lo;
                    }
                }
            }
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
    for (const asf::Node& n : s.nodes)
        for (int j : n.chain)
            if (j >= 0 && j < (int)s.nodes.size()) physics[j] = n.name;

    // ---- nodes
    size_t root = s.nodes.size();
    std::vector<Mat4> local(s.nodes.size(), identity4());
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
        {
            double R[3][3], e[3];
            for (int c = 0; c < 3; c++) {
                double u[3] = {c == 0 ? 1.0 : 0.0, c == 1 ? 1.0 : 0.0, c == 2 ? 1.0 : 0.0};
                qrot(r, u, e);
                for (int i = 0; i < 3; i++) R[i][c] = e[i] * n.scale[c];
            }
            Mat4& L = local[n.index];
            for (int i = 0; i < 3; i++) {
                for (int c = 0; c < 3; c++) L[i * 4 + c] = R[i][c];
                L[i * 4 + 3] = t[i];
            }
            L[12] = L[13] = L[14] = 0;
            L[15] = 1;
        }
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
        if (ph != physics.end())
            x["physics_driven"] = "physics-driven at run time (dynamics chain " + ph->second + "): keeps its rest pose here";
        j["extras"] = x;
        doc["nodes"].push_back(j);
    }
    // the rest pose's world matrices (a skinned mesh's vertices are in its object node's space: they
    // are moved to the model's, where the inverse bind matrices are)
    std::vector<Mat4> world(s.nodes.size());
    std::vector<char> done(s.nodes.size(), 0);
    std::function<const Mat4&(int)> world_of = [&](int i) -> const Mat4& {
        if (done[i]) return world[i];
        done[i] = 1;
        const asf::Node& n = s.nodes[i];
        world[i] = (n.parent >= 0 && n.parent < (int)s.nodes.size() && n.parent != i) ? mul4(world_of(n.parent), local[i]) : local[i];
        return world[i];
    };
    json rootj = {{"name", "asf2gltf_root (cm to m, faces +Z)"}, {"rotation", {0, 1, 0, 0}}, {"scale", {0.01, 0.01, 0.01}}, {"children", json::array()}};
    for (const asf::Node& n : s.nodes)
        if (n.parent < 0 || n.parent == n.index || n.parent >= (int)s.nodes.size()) rootj["children"].push_back(n.index);
    rootj["extras"] = {{"note", "the game's units are centimetres and its models face -Z; this node scales them to metres and turns them to face +Z (glTF's front)"}};
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

    // ---- textures made for a material: the base colour with its alpha, the roughness
    // (UV set n of the game's shaders is the n-th pair of a meshset's texture coordinates: glTF's TEXCOORD_n)
    auto uv_pairs = [&](const asf::Meshset& m, size_t v, std::vector<std::array<float, 2>>& out) {
        out.clear();
        for (const asf::VertexElement& e : m.elements) {
            if (e.usage != asf::kTexcoord) continue;
            float f[4] = {0, 0, 0, 0};
            int comps = 0;
            if (!read_element(m, e, v, f, comps)) continue;
            for (int c = 0; c + 1 < comps || c == 0; c += 2) out.push_back({f[c], c + 1 < comps ? f[c + 1] : 0.0f});
        }
    };
    std::map<std::string, int> baked;
    auto add_texture = [&](const std::string& name, int w, int h, const Bytes& rgba) {
        if (doc["samplers"].is_null()) doc["samplers"].push_back({{"magFilter", 9729}, {"minFilter", 9987}, {"wrapS", 10497}, {"wrapT", 10497}});
        size_t img = b.image_png(name, w, h, rgba);
        doc["textures"].push_back({{"sampler", 0}, {"source", img}, {"name", name}});
        return (int)doc["textures"].size() - 1;
    };
    auto decode0 = [&](const asf::Texture* t, Bytes& rgba) {
        std::string e;
        return t && !t->levels.empty() && asf::decode_texture(s, t->levels[0], rgba, &e);
    };
    // The specular colour F0 (a texture's rgb, uploaded sRGB) as glTF's metalness: metals have a black
    // albedo and a bright F0 (Maria's chains, pendant, hair ornaments: F0 ~0.3); dielectrics ~0.01-0.04
    struct F0Map {
        Bytes px;
        int w = 0, h = 0;
        bool srgb = true;
        bool ok() const { return w > 0; }
        // (metalness, linear F0 rgb) at UV (u, v)
        double at(double u, double v, double f[3]) const {
            int x = ((int)std::floor(u * w) % w + w) % w, y = ((int)std::floor(v * h) % h + h) % h;
            double mx = 0;
            for (int c = 0; c < 3; c++) {
                double raw = px[((size_t)y * w + x) * 4 + c] / 255.0;
                f[c] = srgb ? srgb_to_linear(raw) : raw;
                mx = std::max(mx, f[c]);
            }
            return std::min(1.0, std::max(0.0, (mx - 0.06) / (0.2 - 0.06)));
        }
    };
    auto f0_map = [&](const asf::Texture* ft) {
        F0Map f;
        if (ft && decode0(ft, f.px)) {
            f.w = ft->levels[0].w;
            f.h = ft->levels[0].h;
            f.srgb = texture_srgb(*ft);
        }
        return f;
    };
    auto baked_base = [&](const asf::Object& o, size_t mi, const asf::Texture* at, const Src& albedo, const asf::Texture* alt,
                          const Src& alpha, const asf::Texture* ft, json& notes) -> int {
        char key[200];
        bool cross = at && alt && alpha.uv != albedo.uv;
        snprintf(key, sizeof key, "%08x/%d/%d|%08x/%d/%d|%08x|%s", at ? at->id : 0, albedo.comp, albedo.uv, alt ? alt->id : 0, alpha.comp,
                 alpha.uv, ft ? ft->id : 0, cross ? (o.name + "/" + std::to_string(mi)).c_str() : "");
        auto have = baked.find(key);
        if (have != baked.end()) return have->second;
        Bytes ca, aa;
        if (at && !decode0(at, ca)) at = nullptr;
        if (alt && !decode0(alt, aa)) alt = nullptr;
        if (!at && !alt) return -1;
        const asf::TextureLevel& L = (at ? at : alt)->levels[0];
        int w = L.w, h = L.h;
        Bytes out((size_t)w * h * 4, 255);
        if (at) {
            bool lin = !texture_srgb(*at);
            for (size_t i = 0; i < (size_t)w * h; i++)
                for (int c = 0; c < 3; c++) {
                    uint8_t v = ca[i * 4 + (albedo.comp < 0 ? c : (albedo.comp & 3))];
                    out[i * 4 + c] = lin ? (uint8_t)std::lround(linear_to_srgb(v / 255.0) * 255) : v;
                }
            F0Map f0 = f0_map(ft);
            if (f0.ok()) {  // metals: their colour is their F0
                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++) {
                        double f[3], m = f0.at((x + 0.5) / w, (y + 0.5) / h, f);
                        if (m <= 0) continue;
                        uint8_t* q = &out[((size_t)y * w + x) * 4];
                        for (int c = 0; c < 3; c++)
                            q[c] = (uint8_t)std::lround(linear_to_srgb(srgb_to_linear(q[c] / 255.0) * (1 - m) + std::min(1.0, f[c] * 2.5) * m) * 255);
                    }
            }
        }
        if (alt) {
            const asf::TextureLevel& A = alt->levels[0];
            int ac = alpha.comp & 3;
            bool lin_a = texture_srgb(*alt) && ac < 3;  // an sRGB texture's colour channel reads linearized
            auto sample = [&](float u, float v) {
                int x = ((int)std::floor(u * A.w) % A.w + A.w) % A.w, y = ((int)std::floor(v * A.h) % A.h + A.h) % A.h;
                uint8_t c = aa[((size_t)y * A.w + x) * 4 + ac];
                return lin_a ? (uint8_t)std::lround(srgb_to_linear(c / 255.0) * 255) : c;
            };
            if (!cross) {
                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++) out[((size_t)y * w + x) * 4 + 3] = sample((x + 0.5f) / w, (y + 0.5f) / h);
            } else {
                // the alpha is read through another UV set: drawn into the base colour's UV space,
                // triangle by triangle, from the meshsets that use this material
                for (size_t i = 3; i < out.size(); i += 4) out[i] = 0;
                std::vector<std::array<float, 2>> p0, p1, p2;
                for (const asf::Meshset& m : o.meshsets) {
                    if (m.material != (int)mi || m.prim != 0 || m.indices.empty()) continue;
                    auto index = [&](size_t i) { return m.index32 ? soa::aff::rd32(&m.indices[i * 4]) : (uint32_t)soa::aff::rd16(&m.indices[i * 2]); };
                    for (size_t t = 0; t + 2 < m.index_count; t += 3) {
                        uv_pairs(m, index(t), p0);
                        uv_pairs(m, index(t + 1), p1);
                        uv_pairs(m, index(t + 2), p2);
                        size_t need = (size_t)std::max(albedo.uv, alpha.uv);
                        if (p0.size() <= need || p1.size() <= need || p2.size() <= need) continue;
                        float x0 = p0[albedo.uv][0] * w, y0 = p0[albedo.uv][1] * h, x1 = p1[albedo.uv][0] * w, y1 = p1[albedo.uv][1] * h,
                              x2 = p2[albedo.uv][0] * w, y2 = p2[albedo.uv][1] * h;
                        float area = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
                        if (std::fabs(area) < 1e-12f) continue;
                        int xa = (int)std::floor(std::min({x0, x1, x2})) - 1, xb = (int)std::ceil(std::max({x0, x1, x2})) + 1;
                        int ya = (int)std::floor(std::min({y0, y1, y2})) - 1, yb = (int)std::ceil(std::max({y0, y1, y2})) + 1;
                        for (int y = ya; y <= yb; y++)
                            for (int x = xa; x <= xb; x++) {
                                float px = x + 0.5f, py = y + 0.5f;
                                float b1 = ((px - x0) * (y2 - y0) - (x2 - x0) * (py - y0)) / area;
                                float b2 = ((x1 - x0) * (py - y0) - (px - x0) * (y1 - y0)) / area;
                                float b0 = 1 - b1 - b2;
                                const float e = -0.02f;  // (a little over the edges, against seams)
                                if (b0 < e || b1 < e || b2 < e) continue;
                                float u = b0 * p0[alpha.uv][0] + b1 * p1[alpha.uv][0] + b2 * p2[alpha.uv][0];
                                float v = b0 * p0[alpha.uv][1] + b1 * p1[alpha.uv][1] + b2 * p2[alpha.uv][1];
                                int xx = ((x % w) + w) % w, yy = ((y % h) + h) % h;
                                out[((size_t)yy * w + xx) * 4 + 3] = sample(u, v);
                            }
                    }
                }
                notes.push_back("the alpha (texture " + hex32(alt->id) + ", UV set " + std::to_string(alpha.uv) +
                                ") is redrawn into the base colour's UV set " + std::to_string(albedo.uv) + " from this material's triangles");
            }
        }
        std::string name = (at ? hex32(at->id) : std::string("white")) + (alt ? "_alpha_" + hex32(alt->id) : std::string()) +
                           (ft ? "_metal_" + hex32(ft->id) : std::string());
        int t = add_texture(name, w, h, out);
        baked[key] = t;
        return t;
    };
    auto baked_roughness = [&](const asf::Texture* rt, const asf::Texture* ft) -> int {
        std::string key = "rough/" + hex32(rt->id) + "/" + (ft ? hex32(ft->id) : std::string());
        auto have = baked.find(key);
        if (have != baked.end()) return have->second;
        Bytes in;
        if (!decode0(rt, in)) return -1;
        const asf::TextureLevel& L = rt->levels[0];
        Bytes out((size_t)L.w * L.h * 4, 255);
        F0Map f0 = f0_map(ft);
        for (size_t i = 0; i < (size_t)L.w * L.h; i++) {
            double a2 = (in[i * 4] + in[i * 4 + 1]) / (2 * 255.0);
            out[i * 4 + 1] = (uint8_t)std::lround(std::pow(std::max(a2, 0.000225), 0.25) * 255);
            double f[3];
            out[i * 4 + 2] = f0.ok() ? (uint8_t)std::lround(f0.at((i % L.w + 0.5) / L.w, (i / L.w + 0.5) / L.h, f) * 255) : 0;
        }
        int t = add_texture(hex32(rt->id) + "_roughness" + (ft ? "_metal_" + hex32(ft->id) : std::string()), L.w, L.h, out);
        baked[key] = t;
        return t;
    };

    // ---- objects: meshes, skins, materials
    for (const asf::Object& o : s.objects) {
        json mesh = {{"name", o.name}, {"primitives", json::array()}};
        std::vector<int> mat_index(o.materials.size(), -1);
        for (size_t mi = 0; mi < o.materials.size(); mi++) {
            const asf::Material& m = o.materials[mi];
            GraphInfo gi = read_graph(m);
            json mj = {{"name", o.name + "_" + std::to_string(mi)}};
            json pbr = {{"metallicFactor", 0.0}, {"roughnessFactor", 0.8}};
            const asf::Texture* none = nullptr;
            auto tex_of = [&](const Src& x) -> const asf::Texture* {
                if (x.kind != Src::kTex || x.slot < 0 || x.slot >= (int)m.textures.size()) return none;
                auto it = tex_by_id.find(m.textures[x.slot].id);
                return it == tex_by_id.end() ? none : it->second;
            };
            std::string mode = m.blend ? "BLEND" : m.alpha_test ? "MASK" : "OPAQUE";
            json notes = json::array();
            // base colour and alpha
            const asf::Texture* at = tex_of(gi.albedo);
            const asf::Texture* alt = mode != "OPAQUE" ? tex_of(gi.alpha) : none;
            std::array<float, 4> factor{1, 1, 1, 1};
            if (gi.albedo.kind == Src::kTex || gi.albedo.kind == Src::kConst)
                for (int i = 0; i < 3; i++) factor[i] = gi.albedo.factor[i];
            if (mode != "OPAQUE" && gi.alpha.kind == Src::kConst) factor[3] = gi.alpha.factor[3];
            if (mode != "OPAQUE" && gi.alpha.kind == Src::kTex) factor[3] = gi.alpha.factor[gi.alpha.comp & 3];
            for (float& f : factor) f = std::min(1.0f, std::max(0.0f, f));
            // the specular colour as metalness, when it is a whole texture read through the same UV set
            const asf::Texture* ft = gi.f0.comp < 0 && gi.f0.uv == gi.albedo.uv ? tex_of(gi.f0) : none;
            if (at || alt) {
                int t = baked_base(o, mi, at, gi.albedo, alt, gi.alpha, ft, notes);
                if (t >= 0) pbr["baseColorTexture"] = {{"index", t}, {"texCoord", at ? gi.albedo.uv : gi.alpha.uv}};
            } else if (gi.albedo.kind == Src::kNone && !m.textures.empty() && !gi.lit) {
                int t = texture_of(m.textures[0].id, false);  // (no graph: the first texture)
                if (t >= 0) pbr["baseColorTexture"] = {{"index", t}};
            }
            if (factor != std::array<float, 4>{1, 1, 1, 1}) pbr["baseColorFactor"] = {factor[0], factor[1], factor[2], factor[3]};
            // roughness: the GGX alpha^2 is (r + g) / 2 of the texture; glTF's roughness is alpha^(1/2)
            if (const asf::Texture* rt = tex_of(gi.roughness)) {
                const asf::Texture* fr = gi.roughness.uv == gi.albedo.uv ? ft : none;
                int t = baked_roughness(rt, fr);
                if (t >= 0) {
                    pbr["metallicRoughnessTexture"] = {{"index", t}, {"texCoord", gi.roughness.uv}};
                    pbr["roughnessFactor"] = 1.0;
                    if (fr) pbr["metallicFactor"] = 1.0;
                }
            }
            if (m.blend == 1) {
                // additive (SRC_ALPHA, ONE: the pareo's print, the eyes' highlight): glTF has no additive
                // mode; the colour goes to the emission and the surface itself is clear (BLEND, alpha 0.5
                // of the texture's), so it brightens what is behind it instead of covering it
                if (pbr.contains("baseColorTexture")) {
                    mj["emissiveTexture"] = pbr["baseColorTexture"];
                    mj["emissiveFactor"] = {factor[0], factor[1], factor[2]};
                }
                pbr["baseColorFactor"] = {0.0, 0.0, 0.0, factor[3] * 0.5};
            }
            mj["pbrMetallicRoughness"] = pbr;
            if (const asf::Texture* nt = tex_of(gi.normal)) {
                int t = texture_of(nt->id, true);
                if (t >= 0) mj["normalTexture"] = {{"index", t}, {"texCoord", gi.normal.uv}};
            }
            if (mode != "OPAQUE") mj["alphaMode"] = mode;
            if (mode == "MASK") mj["alphaCutoff"] = m.alpha_ref / 255.0;
            if (m.double_sided) mj["doubleSided"] = true;
            json slots = json::array();
            for (size_t k = 0; k < m.textures.size(); k++) {
                const auto& t = m.textures[k];
                json sj = {{"id", hex32(t.id)}, {"class", std::string((const char*)&t.cls, 4)}, {"wrap", t.wrap}, {"kind", t.slot_kind}};
                auto role = [&](const Src& x) { return x.kind == Src::kTex && x.slot == (int)k; };
                json roles = json::array();
                if (role(gi.albedo)) roles.push_back("albedo");
                if (role(gi.alpha) && mode != "OPAQUE") roles.push_back("alpha");
                if (role(gi.normal)) roles.push_back("normal");
                if (role(gi.roughness)) roles.push_back("roughness (GGX alpha^2 = (r + g) / 2)");
                if (role(gi.f0)) roles.push_back(gi.f0.comp < 0 ? "specular F0 (rgb)" : "specular F0 (one channel)");
                if (!roles.empty()) sj["roles"] = roles;
                if (!tex_by_id.count(t.id)) sj["note"] = "not in this file (supplied by the game)";
                else if (roles.empty()) {
                    int ti = texture_of(t.id, false);
                    if (ti >= 0) sj["texture"] = ti;
                }
                slots.push_back(sj);
            }
            json consts = json::array();
            for (const auto& c : m.constants) {
                json v = json::array();
                for (auto& x : c.values) v.push_back({x[0], x[1], x[2], x[3]});
                consts.push_back({{"id", c.id}, {"index", c.index}, {"values", v}});
            }
            static const std::map<int, const char*> kLighting = {{0x49, "GGX (specular F0, roughness, normal map)"}, {0x28, "Lambert"},
                                                                 {0x32, "Marschner hair (docs/render/hair-shader.md)"}, {0x24, "lashes (0x24)"}};
            auto lt = kLighting.find(gi.lighting);
            size_t g0 = m.raw.size() >= 0x24 ? soa::aff::rd32(&m.raw[0x1c]) : 0, g1 = m.raw.size() >= 0x24 ? soa::aff::rd32(&m.raw[0x20]) : 0;
            mj["extras"] = {{"asf_texture_slots", slots}, {"asf_constants", consts}, {"asf_flags", hex32(m.flags)},
                            {"asf_blend", m.blend == 1 ? "additive (SRC_ALPHA, ONE): BLEND here" : m.blend == 2 ? "alpha" : "opaque"},
                            {"asf_lighting", lt == kLighting.end() ? std::string("none") : std::string(lt->second)},
                            {"asf_shader_graph", g1 > g0 && g1 <= m.raw.size() ? hexbytes(m.raw.data() + g0, g1 - g0) : ""}};
            if (!notes.empty()) mj["extras"]["notes"] = notes;
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
            bool bake = !o.bones.empty() && o.node >= 0;
            if (bake) {
                bake = false;
                for (const asf::VertexElement& e : m.elements) bake |= e.usage == asf::kBlendIndex;
            }
            const Mat4& W = world_of(o.node >= 0 ? o.node : 0);
            auto xform = [&](float* q, bool point) {
                double v[3] = {q[0], q[1], q[2]};
                for (int i = 0; i < 3; i++) q[i] = (float)(W[i * 4] * v[0] + W[i * 4 + 1] * v[1] + W[i * 4 + 2] * v[2] + (point ? W[i * 4 + 3] : 0));
            };
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
                    if (bake)
                        for (size_t v = 0; v < nv; v++) xform(&p[v * 3], true);
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
                        if (bake) xform(q, false);
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
                        if (bake) xform(q, false);
                        float l = std::sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2]);
                        if (l > 0) q[0] /= l, q[1] /= l, q[2] /= l; else q[0] = 1;
                        q[3] = q[3] < 0 ? -1.0f : 1.0f;
                    }
                    a["TANGENT"] = b.accessor(p.data(), nv, kFloat, "VEC4", 4, 34962);
                    break;
                }
                case asf::kTexcoord: {
                    // each pair of components is a UV set of the game's shaders (xy, zw): one TEXCOORD_n each
                    for (int c = 0; c < comps || c == 0; c += 2) {
                        auto p = take(c, 2);
                        a["TEXCOORD_" + std::to_string(sets["uv"]++)] = b.accessor(p.data(), nv, kFloat, "VEC2", 2, 34962);
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
            // a joint with weight 0 is set to 0 (the glTF validator's rule; it has no effect)
            if (a.contains("JOINTS_0") && a.contains("WEIGHTS_0")) {
                json& ja = doc["accessors"][(size_t)a["JOINTS_0"]];
                json& wa = doc["accessors"][(size_t)a["WEIGHTS_0"]];
                json& jv = doc["bufferViews"][(size_t)ja["bufferView"]];
                json& wv = doc["bufferViews"][(size_t)wa["bufferView"]];
                uint16_t* jp = (uint16_t*)&b.bin[(size_t)jv["byteOffset"]];
                const float* wp = (const float*)&b.bin[(size_t)wv["byteOffset"]];
                for (size_t i = 0; i < nv * 4; i++)
                    if (wp[i] == 0) jp[i] = 0;
            }
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
        // a skinned mesh goes on a node of its own at the scene's root (glTF ignores a skinned mesh
        // node's transforms); the object's node keeps its place in the tree
        json* nodep = &doc["nodes"][o.node];
        if (skinned && !o.bones.empty()) {
            doc["nodes"].push_back({{"name", o.name + " (skinned mesh)"}, {"extras", {{"asf_object_node", o.node}}}});
            doc["scenes"][0]["nodes"].push_back(doc["nodes"].size() - 1);
            nodep = &doc["nodes"].back();
        }
        json& node = *nodep;
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

    // ---- animations (soa/aaf.h): one glTF animation per .aaf. Rotation keys (quaternion
    // tracks) go out as they are, premultiplied by the joint orient: LINEAR (the game slerps) or
    // STEP; a Vector Hermite translation / scale whose tangents map goes out as CUBICSPLINE
    // (tangent / key interval in seconds); everything else is sampled at every frame (LINEAR).
    // Constraints and other controllers are recorded in the animation's extras.
    std::map<std::string, int> node_by_name;
    for (const asf::Node& n : s.nodes) node_by_name.emplace(n.name, n.index);
    for (const Anim& an : in.anims) {
        soa::aaf::Animation a;
        std::string e;
        if (!soa::aaf::load(an.file, a, &e)) { if (err) *err = an.name + ": " + e; return false; }
        json anim = {{"name", an.title.empty() ? an.name : an.title}, {"channels", json::array()}, {"samplers", json::array()}};
        json ax = {{"source", an.name}, {"fps", opt.fps}, {"length_frames", a.length}};
        if (!an.role.empty()) ax["role"] = an.role;
        json channel_notes = json::array(), skipped = json::array(), unmatched = json::array();
        const float fps = opt.fps;
        const float length = a.length > 0 ? a.length : 1.0f;
        auto add_sampler = [&](const std::vector<float>& times, const std::vector<float>& values, int comps,
                               const char* interp) {
            std::vector<float> secs(times.size());
            for (size_t i = 0; i < times.size(); i++) secs[i] = times[i] / fps;
            size_t ti = b.accessor(secs.data(), secs.size(), kFloat, "SCALAR", 1, 0, false, true);
            const char* type = comps == 4 ? "VEC4" : comps == 3 ? "VEC3" : "SCALAR";
            size_t vi = b.accessor(values.data(), values.size() / comps, kFloat, type, comps, 0);
            anim["samplers"].push_back({{"input", ti}, {"output", vi}, {"interpolation", interp}});
            return anim["samplers"].size() - 1;
        };
        // the controllers of each node, by attribute
        struct Tracks { std::vector<const soa::aaf::Controller*> t[3], txyz, s[3], sxyz, rq, rot_other; };
        std::map<int, Tracks> tracks;
        for (size_t ti = 0; ti < a.targets.size(); ti++) {
            const auto& tg = a.targets[ti];
            for (int ci : tg.controllers) {
                const auto& c = a.controllers[ci];
                if (!c.keyframed()) {
                    json k = {{"target", tg.name}, {"controller", soa::aaf::controller_kind_name(c.kind)}};
                    if (c.kind >= 6 && c.kind <= 8 && c.offset + 0x40 <= an.file.size()) {
                        const char* src = (const char*)&an.file[c.offset + 0x20];
                        if (!memcmp(src, "R:", 2)) k["source"] = std::string(src + 2, strnlen(src + 2, 30));
                        k["not_baked"] = "constraint evaluation not reproduced (docs/notes.md: Animations (AAF) for tools)";
                    }
                    skipped.push_back(k);
                    continue;
                }
                auto it = node_by_name.find(tg.name);
                if (tg.type != 0 || it == node_by_name.end()) {
                    unmatched.push_back({{"target", tg.name}, {"attribute", soa::aaf::attribute_name(c.attr)}});
                    continue;
                }
                std::string why;
                bool euler = c.attr >= soa::aaf::kRotateX && c.attr <= soa::aaf::kRotateXYZ;
                if (!soa::aaf::supported(c, &why) && !c.constant() && !euler) {
                    skipped.push_back({{"target", tg.name}, {"attribute", soa::aaf::attribute_name(c.attr)}, {"why", why}});
                    continue;
                }
                Tracks& T = tracks[it->second];
                switch (c.attr) {
                case soa::aaf::kTranslateX: case soa::aaf::kTranslateY: case soa::aaf::kTranslateZ: T.t[c.attr - 1].push_back(&c); break;
                case soa::aaf::kTranslateXYZ: T.txyz.push_back(&c); break;
                case soa::aaf::kScaleX: case soa::aaf::kScaleY: case soa::aaf::kScaleZ: T.s[c.attr - 10].push_back(&c); break;
                case soa::aaf::kScaleXYZ: T.sxyz.push_back(&c); break;
                case soa::aaf::kRotateQuaternion: T.rq.push_back(&c); break;
                case soa::aaf::kRotateX: case soa::aaf::kRotateY: case soa::aaf::kRotateZ: case soa::aaf::kRotateXYZ:
                    T.rot_other.push_back(&c);
                    break;
                default:
                    skipped.push_back({{"target", tg.name}, {"attribute", soa::aaf::attribute_name(c.attr)},
                                       {"why", "not a node transform (a value the game's code reads)"}});
                }
            }
        }
        auto value_of = [&](const soa::aaf::Controller& c, float f, float out[4]) {
            if (c.constant()) soa::aaf::evaluate_constant(a, c, out);
            else soa::aaf::evaluate(a, c, f, out);
        };
        std::vector<float> frames;
        for (float f = 0; f <= length + 1e-4f; f += 1.0f) frames.push_back(f);
        if (frames.back() < length) frames.push_back(length);
        for (auto& [ni, T] : tracks) {
            const asf::Node& n = s.nodes[ni];
            bool piv = false;
            for (int i = 0; i < 3; i++) piv |= n.pivot[1][i] != 0 || n.pivot[2][i] != 0 || n.pos_offset[i] != 0;
            Quat jo = n.joint ? Quat{n.joint_orient[0], n.joint_orient[1], n.joint_orient[2], n.joint_orient[3]} : Quat{};
            // rotation
            if (!T.rq.empty()) {
                const auto& c = *T.rq.back();
                std::vector<float> times, vals;
                const char* interp = "LINEAR";
                bool exact = c.constant() || (c.pre == 0 && c.post == 0);
                if (c.constant()) {
                    float v[4] = {0, 0, 0, 1};
                    value_of(c, 0, v);
                    times = {0.0f};
                    Quat q = qnorm(qmul(jo, {v[0], v[1], v[2], v[3]}));
                    vals = {(float)q.x, (float)q.y, (float)q.z, (float)q.w};
                } else if (exact) {
                    const uint8_t* kf = &an.file[c.kf];
                    if (c.cp_type == soa::aaf::kQuaternionStep) interp = "STEP";
                    Quat prev{};
                    for (uint32_t k = 0; k < c.count; k++) {
                        float tk = soa::aff::rdf(kf + 0x18 + k * 4);
                        float v[4] = {0, 0, 0, 1};
                        value_of(c, tk, v);
                        Quat q = qmul(jo, {v[0], v[1], v[2], v[3]});
                        // the game's slerp takes the short way: keep neighbours in one hemisphere
                        if (k && prev.x * q.x + prev.y * q.y + prev.z * q.z + prev.w * q.w < 0) q = {-q.x, -q.y, -q.z, -q.w};
                        prev = q;
                        times.push_back(tk);
                        vals.insert(vals.end(), {(float)q.x, (float)q.y, (float)q.z, (float)q.w});
                    }
                } else {
                    for (float f : frames) {
                        float v[4] = {0, 0, 0, 1};
                        value_of(c, f, v);
                        Quat q = qnorm(qmul(jo, {v[0], v[1], v[2], v[3]}));
                        times.push_back(f);
                        vals.insert(vals.end(), {(float)q.x, (float)q.y, (float)q.z, (float)q.w});
                    }
                }
                size_t si = add_sampler(times, vals, 4, interp);
                anim["channels"].push_back({{"sampler", si}, {"target", {{"node", ni}, {"path", "rotation"}}}});
                channel_notes.push_back({{"node", n.name}, {"path", "rotation"}, {"from", std::string(soa::aaf::cp_type_name(c.cp_type)) + " " + soa::aaf::compression_name(c.comp)},
                                         {"interpolation", interp}, {"how", c.constant() ? "constant" : exact ? "keys as they are (slerp = glTF LINEAR)" : "sampled every frame (out-of-range mode)"}});
            }
            if (T.rq.empty() && !T.rot_other.empty()) {
                // Euler tracks: the game's controller returns Quaternion::CreateFromEuler(x, y, z) = Rz Ry Rx
                // (docs/notes.md); sampled every frame, premultiplied by the joint orient
                std::vector<float> times, vals;
                for (float f : frames) {
                    float e[3] = {0, 0, 0};
                    for (const auto* c : T.rot_other) {
                        float v[4] = {0, 0, 0, 0};
                        if (c->constant()) {
                            if (c->comp == soa::aaf::kF32)
                                for (int i = 0; i < 3; i++) v[i] = soa::aff::rdf(&an.file[c->kf + 0xc + i * 4]);
                        } else {
                            soa::aaf::evaluate_track(a, *c, f, v);
                        }
                        if (c->attr == soa::aaf::kRotateXYZ) for (int i = 0; i < 3; i++) e[i] = v[i];
                        else e[c->attr - soa::aaf::kRotateX] = v[0];
                    }
                    Quat qx{std::sin(e[0] / 2.0), 0, 0, std::cos(e[0] / 2.0)}, qy{0, std::sin(e[1] / 2.0), 0, std::cos(e[1] / 2.0)},
                        qz{0, 0, std::sin(e[2] / 2.0), std::cos(e[2] / 2.0)};
                    Quat q = qnorm(qmul(jo, qmul(qz, qmul(qy, qx))));
                    times.push_back(f);
                    vals.insert(vals.end(), {(float)q.x, (float)q.y, (float)q.z, (float)q.w});
                }
                size_t si = add_sampler(times, vals, 4, "LINEAR");
                anim["channels"].push_back({{"sampler", si}, {"target", {{"node", ni}, {"path", "rotation"}}}});
                channel_notes.push_back({{"node", n.name}, {"path", "rotation"}, {"interpolation", "LINEAR"},
                                         {"how", "Euler angles sampled every frame, as Rz Ry Rx (Quaternion::CreateFromEuler)"}});
            }
            // translation / scale
            for (int which = 0; which < 2; which++) {
                auto& comp = which ? T.s : T.t;
                auto& vec = which ? T.sxyz : T.txyz;
                if (vec.empty() && comp[0].empty() && comp[1].empty() && comp[2].empty()) continue;
                const char* path = which ? "scale" : "translation";
                std::vector<float> times, vals;
                const char* interp = "LINEAR";
                std::string how = "sampled every frame";
                bool cubic_ok = !which ? !piv : true;
                if (!vec.empty() && comp[0].empty() && comp[1].empty() && comp[2].empty() && cubic_ok && !vec.back()->constant() &&
                    vec.back()->comp == soa::aaf::kF32 && vec.back()->pre == 0 && vec.back()->post == 0 &&
                    (vec.back()->cp_type == soa::aaf::kVector || vec.back()->cp_type == soa::aaf::kVectorLinear ||
                     vec.back()->cp_type == soa::aaf::kVectorStep)) {
                    const auto& c = *vec.back();
                    const uint8_t* kf = &an.file[c.kf];
                    const uint8_t* cp = kf + 0x18 + (size_t)c.count * 4;
                    if (c.cp_type == soa::aaf::kVector) {
                        // CUBICSPLINE: [in, value, out] per key; the game's tangents are per interval
                        interp = "CUBICSPLINE";
                        how = "Hermite keys as glTF cubic spline (tangent / interval in seconds)";
                        for (uint32_t k = 0; k < c.count; k++) {
                            float tk = soa::aff::rdf(kf + 0x18 + k * 4);
                            float dprev = k ? (tk - soa::aff::rdf(kf + 0x18 + (k - 1) * 4)) / fps : 0;
                            float dnext = k + 1 < c.count ? (soa::aff::rdf(kf + 0x18 + (k + 1) * 4) - tk) / fps : 0;
                            const uint8_t* p = cp + (size_t)k * 36;
                            times.push_back(tk);
                            for (int i = 0; i < 3; i++) vals.push_back(dprev ? soa::aff::rdf(p + 12 + i * 4) / dprev : 0.0f);
                            for (int i = 0; i < 3; i++) vals.push_back(soa::aff::rdf(p + i * 4));
                            for (int i = 0; i < 3; i++) vals.push_back(dnext ? soa::aff::rdf(p + 24 + i * 4) / dnext : 0.0f);
                        }
                    } else {
                        interp = c.cp_type == soa::aaf::kVectorStep ? "STEP" : "LINEAR";
                        how = "keys as they are";
                        for (uint32_t k = 0; k < c.count; k++) {
                            times.push_back(soa::aff::rdf(kf + 0x18 + k * 4));
                            for (int i = 0; i < 3; i++) vals.push_back(soa::aff::rdf(cp + ((size_t)k * 3 + i) * 4));
                        }
                    }
                } else {
                    for (float f : frames) {
                        float v3[3] = {which ? n.scale[0] : n.pos[0], which ? n.scale[1] : n.pos[1], which ? n.scale[2] : n.pos[2]};
                        if (!vec.empty()) {
                            float v[4] = {v3[0], v3[1], v3[2], 1};
                            value_of(*vec.back(), f, v);
                            for (int i = 0; i < 3; i++) v3[i] = v[i];
                        }
                        for (int i = 0; i < 3; i++)
                            if (!comp[i].empty()) {
                                float v[4] = {v3[i], 0, 0, 0};
                                value_of(*comp[i].back(), f, v);
                                v3[i] = v[0];
                            }
                        if (!which && !n.joint) {  // the pivot terms, as for the rest pose
                            double rv[3], av[3];
                            for (int i = 0; i < 3; i++) av[i] = n.pivot[1][i] - n.scale[i] * n.pivot[2][i];
                            qrot({n.rot[0], n.rot[1], n.rot[2], n.rot[3]}, av, rv);
                            for (int i = 0; i < 3; i++) v3[i] += (float)(n.pos_offset[i] + rv[i]);
                        }
                        times.push_back(f);
                        vals.insert(vals.end(), {v3[0], v3[1], v3[2]});
                    }
                }
                size_t si = add_sampler(times, vals, 3, interp);
                anim["channels"].push_back({{"sampler", si}, {"target", {{"node", ni}, {"path", path}}}});
                channel_notes.push_back({{"node", n.name}, {"path", path}, {"interpolation", interp}, {"how", how}});
            }
        }
        ax["channels"] = channel_notes;
        if (!skipped.empty()) ax["not_exported"] = skipped;
        if (!unmatched.empty()) ax["targets_not_in_model"] = unmatched;
        for (auto& [k, v] : an.extras.items()) ax[k] = v;
        anim["extras"] = ax;
        if (!anim["channels"].empty()) doc["animations"].push_back(anim);
    }

    mirror_x(b, root);
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
