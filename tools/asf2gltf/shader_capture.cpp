#include "shader_capture.h"

#include <soa/aff.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <vector>

namespace gltf {
namespace asf = soa::asf;
using json = nlohmann::ordered_json;

namespace {

uint64_t fnv(const uint8_t* p, size_t n) {
    uint64_t h = 0xcbf29ce484222325ull;
    for (size_t i = 0; i < n; i++) h = (h ^ p[i]) * 0x100000001b3ull;
    return h;
}

std::vector<std::string> split(const std::string& s, char c) {
    std::vector<std::string> f;
    size_t a = 0, b;
    while ((b = s.find(c, a)) != std::string::npos) { f.push_back(s.substr(a, b - a)); a = b + 1; }
    f.push_back(s.substr(a));
    return f;
}

bool read_text(const std::string& path, std::string& out) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    std::stringstream ss;
    ss << f.rdbuf();
    out = ss.str();
    return true;
}

// "name 0xTYPE = v v v": every uniform's captured value (arrays by element)
std::map<std::string, std::vector<double>> read_uniforms(const std::string& path) {
    std::map<std::string, std::vector<double>> u;
    std::ifstream f(path);
    std::string line;
    while (std::getline(f, line)) {
        size_t eq = line.find(" = ");
        if (eq == std::string::npos) continue;
        std::string name = line.substr(0, line.find(' '));
        std::istringstream vs(line.substr(eq + 3));
        std::vector<double> v;
        double x;
        while (vs >> x) v.push_back(x);
        u[name] = v;
    }
    return u;
}

bool engine_uniform(const std::string& n) {
    return n.rfind("cv", 0) == 0 || n.rfind("cm", 0) == 0 || n.rfind("vcv", 0) == 0 || n.rfind("camSkin", 0) == 0 ||
           n.rfind("eProjector", 0) == 0 || n.rfind("ePROJECTOR", 0) == 0;
}

}  // namespace

json capture_shaders(const asf::Scene& s, const std::string& dir, std::string* err) {
    json out = json::object();
    std::ifstream draws(dir + "/draws.tsv");
    if (!draws) return out;
    // the model's textures by the hash of their level 0 (what the dump names a bound texture by)
    std::map<uint32_t, std::string> hash_of;
    for (const auto& o : s.objects)
        for (const auto& t : o.textures) {
            if (t.levels.empty()) continue;
            size_t n = 0;
            const uint8_t* p = s.amf.raw_block(t.levels[0].pixels, &n);
            if (!p) continue;
            char h[32];
            snprintf(h, sizeof h, "%016llx", (unsigned long long)fnv(p, n));
            hash_of[t.id] = h;
        }
    struct Draw { std::string n, prog; long count; std::vector<std::string> units; std::string blend, cull, depth; };
    std::vector<Draw> list;
    std::string line;
    while (std::getline(draws, line)) {
        auto f = split(line, '\t');
        if (f.size() < 11) continue;
        list.push_back({f[0], f[1], std::stol(f[4]), split(f[7], ','), f[8], f[9], f[10]});
    }
    json shaders = json::array();
    std::map<std::string, int> shader_index;  // glsl -> index
    std::map<std::string, std::pair<int, int>> program_shaders;  // program -> (vertex, fragment)
    auto program = [&](const std::string& p) -> std::pair<int, int> {
        auto have = program_shaders.find(p);
        if (have != program_shaders.end()) return have->second;
        std::string text;
        std::pair<int, int> r{-1, -1};
        if (read_text(dir + "/program_" + p + ".txt", text)) {
            std::vector<size_t> at;
            for (size_t q = text.find("==== shader "); q != std::string::npos; q = text.find("==== shader ", q + 1)) at.push_back(q);
            for (size_t i = 0; i < at.size(); i++) {
                size_t b = text.find('\n', at[i]) + 1, e = i + 1 < at.size() ? at[i + 1] : text.size();
                std::string glsl = text.substr(b, e - b);
                while (!glsl.empty() && (glsl.back() == '\n')) glsl.pop_back();
                if (glsl.rfind("#version", 0) != 0) continue;
                bool vertex = glsl.find("gl_Position") != std::string::npos;
                auto it = shader_index.find(glsl);
                int idx;
                if (it == shader_index.end()) {
                    idx = (int)shaders.size();
                    shader_index[glsl] = idx;
                    shaders.push_back({{"stage", vertex ? "vertex" : "fragment"}, {"glsl", glsl}, {"programs", json::array()}});
                } else {
                    idx = it->second;
                }
                shaders[idx]["programs"].push_back(std::stoi(p));
                (vertex ? r.first : r.second) = idx;
            }
        }
        program_shaders[p] = r;
        return r;
    };
    static const std::regex kUniform(R"(uniform\s+(\w+)\s+(\w+)\s*(\[\s*(\d+)\s*\])?\s*;)");
    static const std::regex kAttr(R"(layout\s*\(\s*location\s*=\s*(\d+)\s*\)\s*in\s+\w+\s+\w+\s+(in_\w+)\s*;)");
    static const std::map<std::string, std::string> kSemantics = {
        {"in_POSITION0", "POSITION (object space, as stored)"}, {"in_NORMAL0", "NORMAL"}, {"in_TEXCOORD0", "TEXCOORD (both UV sets: xy, zw)"},
        {"in_BINORMAL0", "TANGENT (xyz, w the bitangent sign)"}, {"in_BLENDINDICES0", "the meshset's palette indices (not joints)"},
        {"in_BLENDWEIGHT0", "WEIGHTS"}, {"in_COLOR0", "COLOR"}};
    json materials = json::object();
    for (const auto& o : s.objects)
        for (size_t mi = 0; mi < o.materials.size(); mi++) {
            const asf::Material& m = o.materials[mi];
            std::vector<std::string> want;
            for (const auto& t : m.textures) {
                auto it = hash_of.find(t.id);
                want.push_back(it == hash_of.end() ? "" : it->second);
            }
            if (want.empty()) continue;
            std::set<long> counts;  // the index counts of the meshsets drawn with this material
            for (const auto& ms : o.meshsets)
                if (ms.material == (int)mi) counts.insert((long)ms.index_count);
            std::set<std::string> seen_programs;
            json passes = json::array();
            for (const Draw& d : list) {
                bool match = d.units.size() >= want.size() && counts.count(d.count);
                for (size_t k = 0; match && k < want.size(); k++) match = want[k].empty() || d.units[k] == want[k];
                if (!match || !seen_programs.insert(d.prog + "|" + d.blend + "|" + d.cull + "|" + d.depth).second) continue;
                auto [vs, fs] = program(d.prog);
                if (vs < 0 || fs < 0) continue;
                auto u = read_uniforms(dir + "/draw_" + d.n + ".txt");
                json uni = json::object();
                std::set<std::string> declared;
                for (int st : {vs, fs}) {
                    std::string g = shaders[st]["glsl"];
                    for (std::sregex_iterator it(g.begin(), g.end(), kUniform), end; it != end; ++it) {
                        std::string type = (*it)[1], name = (*it)[2];
                        if (!declared.insert(name).second) continue;
                        json e = {{"type", type}};
                        if ((*it)[4].matched) e["count"] = std::stoi((*it)[4]);
                        std::smatch sm;
                        if (std::regex_match(name, sm, std::regex(R"(s(\d+))"))) {
                            int slot = std::stoi(sm[1]);
                            e["texture_slot"] = slot;
                            if (slot >= (int)m.textures.size()) e["engine"] = "a texture the engine binds (shadow map, BRDF table, ...)";
                        } else if (engine_uniform(name)) {
                            bool per_draw = name.rfind("camSkin", 0) == 0 || name.rfind("cm", 0) == 0 || name == "vcvWorldEyePos";
                            e["engine"] = per_draw ? "per draw (the pose and the camera)" : "the scene's lighting (captured)";
                            if (!per_draw) {
                                json vals = json::array();
                                int n = e.value("count", 1);
                                for (int k = 0; k < n; k++) {
                                    auto v = u.find(n > 1 ? name + "[" + std::to_string(k) + "]" : name);
                                    if (v != u.end()) vals.push_back(v->second);
                                }
                                e["captured"] = vals;
                            }
                        } else if (name == "cfAlphaThreshold") {
                            e["material"] = "header +0x1b / 255";
                            if (u.count(name)) e["captured"] = u[name];
                        } else {
                            // a material constant: found by its value (the graph's load ops name them:
                            // eConstColor_Color_Color<n> = constant 5 index n, eALBEDO_CONSTCOLOR = 0x14)
                            auto v = u.find(name);
                            if (v == u.end()) v = u.find(name + "[0]");
                            if (v != u.end()) e["captured"] = v->second;
                            json from = json::array();
                            if (v != u.end())
                                for (const auto& c : m.constants)
                                    for (size_t k = 0; k < c.values.size(); k++) {
                                        bool same = v->second.size() >= 4;
                                        for (int q = 0; same && q < 4; q++) same = std::fabs(v->second[q] - c.values[k][q]) < 1e-5;
                                        if (same) from.push_back({{"id", c.id}, {"index", c.index}, {"element", k}});
                                    }
                            if (!from.empty()) e["constant"] = from;
                            else e["derived"] = "computed by the engine from the material (not a stored constant)";
                        }
                        uni[name] = e;
                    }
                }
                json attrs = json::object();
                std::string vg = shaders[vs]["glsl"];
                for (std::sregex_iterator it(vg.begin(), vg.end(), kAttr), end; it != end; ++it) {
                    std::string nm = (*it)[2];
                    auto sem = kSemantics.find(nm);
                    attrs[nm] = {{"location", std::stoi((*it)[1])}, {"stream", sem == kSemantics.end() ? std::string("?") : sem->second}};
                }
                passes.push_back({{"program", std::stoi(d.prog)}, {"vertexShader", vs}, {"fragmentShader", fs}, {"capture_draw", std::stoi(d.n)},
                                  {"state", {{"blend", d.blend}, {"cull", d.cull}, {"depth", d.depth}}}, {"attributes", attrs}, {"uniforms", uni}});
            }
            if (!passes.empty()) materials[o.name + "/" + std::to_string(mi)] = {{"passes", passes}};
        }
    if (materials.empty() && err) *err = dir + ": no draw of this model's materials";
    out["shaders"] = shaders;
    out["materials"] = materials;
    return out;
}

bool write_raw_streams(const asf::Scene& s, const std::string& dir, std::string* err) {
    for (const auto& o : s.objects)
        for (size_t k = 0; k < o.meshsets.size(); k++) {
            const asf::Meshset& m = o.meshsets[k];
            if (m.shares >= 0 || m.vertices.empty()) continue;
            std::vector<float> f;
            json els = json::array();
            for (const auto& e : m.elements) els.push_back({{"usage", asf::usage_name(e.usage)}, {"index", e.index}, {"type", e.type}});
            for (size_t v = 0; v < m.vertex_count; v++)
                for (const auto& e : m.elements) {
                    asf::TypeInfo t;
                    float x[4] = {0, 0, 0, 1};
                    if (asf::type_info(e.type, t) && v * m.stride + e.offset + t.bytes <= m.vertices.size()) {
                        const uint8_t* p = m.vertices.data() + v * m.stride + e.offset;
                        for (int c = 0; c < t.components && c < 4; c++) {
                            switch (t.gl_type) {
                            case 0x1406: memcpy(&x[c], p + c * 4, 4); break;
                            case 0x140b: {
                                uint16_t h = soa::aff::rd16(p + c * 2);
                                int sg = h >> 15, ex = (h >> 10) & 31, mt = h & 1023;
                                float y = ex == 0 ? std::ldexp((float)mt, -24) : ex == 31 ? INFINITY : std::ldexp((float)(mt | 1024), ex - 25);
                                x[c] = sg ? -y : y;
                                break;
                            }
                            case 0x1402: { int16_t q; memcpy(&q, p + c * 2, 2); x[c] = t.normalized ? std::max(-1.0f, q / 32767.0f) : (float)q; break; }
                            case 0x1403: { uint16_t q; memcpy(&q, p + c * 2, 2); x[c] = t.normalized ? q / 65535.0f : (float)q; break; }
                            case 0x1400: { int8_t q = (int8_t)p[c]; x[c] = t.normalized ? std::max(-1.0f, q / 127.0f) : (float)q; break; }
                            case 0x1401: x[c] = t.normalized ? p[c] / 255.0f : (float)p[c]; break;
                            default: break;
                            }
                        }
                    }
                    f.insert(f.end(), x, x + 4);
                }
            std::vector<uint32_t> idx(m.index_count);
            for (size_t i = 0; i < m.index_count && (i + 1) * (m.index32 ? 4 : 2) <= m.indices.size(); i++)
                idx[i] = m.index32 ? soa::aff::rd32(&m.indices[i * 4]) : soa::aff::rd16(&m.indices[i * 2]);
            std::string base = dir + "/" + o.name + "_" + std::to_string(k);
            std::ofstream a(base + ".f32", std::ios::binary), b(base + ".u32", std::ios::binary), c(base + ".json");
            if (!a || !b || !c) { if (err) *err = "cannot write " + base; return false; }
            a.write((const char*)f.data(), (std::streamsize)(f.size() * 4));
            b.write((const char*)idx.data(), (std::streamsize)(idx.size() * 4));
            c << json({{"vertices", m.vertex_count}, {"indices", m.index_count}, {"material", m.material}, {"elements", els}}).dump(1);
        }
    return true;
}

}  // namespace gltf
