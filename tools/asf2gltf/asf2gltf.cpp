// asf2gltf: the game's 3D models (.asf) and their animations (.aaf) as glTF 2.0 (docs/notes.md
// "Meshes (ASF)", "Models and animation"; the reader is soa_models: soa/asf.h, soa/aaf.h).
//
// Usage: asf2gltf [--data DIR|ZIP] MODEL [options]
//   MODEL        a game path read from the 3.7.0 download (--data; default
//                work/SOA-3.7.0-canonical-data.zip of the checkout), e.g. Character/etc2/hi/cp0303_b04a.asf,
//                or a local file (ADLD-wrapped with its game path in it, or already decoded)
//   -o OUT       OUT.glb (one self-contained file), or OUT.gltf + OUT.bin with --gltf
//   --aaf ANIM   an animation: an .aaf, PKG.apk:MEMBER.aaf (a motion package's member), or PKG.apk
//                (every .aaf in it); repeatable; each becomes a named glTF animation
//   --set FILE   an animation set (JSON, tools/asf2gltf/anim_set.py): {"animations": [{"source": ANIM,
//                "name": ..., "role": ..., "extras": {...}}]}: names, roles and the effect triggers
//   --fps N      the game's animation frames per second (default 60: docs/notes.md)
//   --info       print the scene (nodes, objects, meshsets, vertex formats, materials, textures)
//   --textures DIR  also write every texture level 0 as DIR/<object>_<id>.png
//   --check-gl-dump DIR  compare every meshset's vertex and index bytes with the buffers a run of
//                the game uploaded (soa with SOA_GL_BUFFER_DUMP=DIR): prints one line per meshset
//                and "match N/M"; exit 1 unless every meshset matched
//   --shaders DIR  a capture of the game drawing the model (soa with SOA_GL_DRAW_DUMP=DIR): each
//                material's own GLSL, uniforms and draw state go into SOA_aska_shader
//   --raw-out DIR  the meshsets as the game's vertex shaders read them (shader_replay.py)
#include <soa/aaf.h>
#include <soa/aff.h>
#include <soa/asf.h>
#include <soa/aska_image.h>
#include <soa/file_tree.h>
#include <soa/png.h>

#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "gltf_writer.h"
#include "shader_capture.h"

using soa::aff::Bytes;

namespace {

std::string repo_dir_of(const char* argv0) {
    std::string p = argv0;
    size_t s = p.rfind('/');
    std::string dir = s == std::string::npos ? "." : p.substr(0, s);
    // build/tools/asf2gltf/asf2gltf -> the checkout
    return dir + "/../../..";
}

bool read_file(const std::string& path, Bytes& out) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    out.assign(std::istreambuf_iterator<char>(f), {});
    return true;
}

struct Source {
    std::shared_ptr<const soa::FileTree> tree;
    std::string data_path;
    bool open(std::string* err) {
        if (tree) return true;
        tree = soa::FileTree::open(data_path, err);
        return tree != nullptr;
    }
};

// MODEL (or an animation) as decoded bytes: a local file, or a game path from the download.
bool load_input(Source& src, const std::string& arg, Bytes& out, std::string& name, std::string* err) {
    Bytes raw;
    if (read_file(arg, raw)) {
        name = soa::aff::game_name_of(arg);
    } else {
        if (!src.open(err)) return false;
        if (!src.tree->read(arg, raw)) {
            if (err) *err = arg + ": not a file and not in " + src.data_path;
            return false;
        }
        name = arg;
    }
    return soa::aff::decode_game_file(name, raw, out, err);
}

void print_info(const soa::asf::Scene& s) {
    using namespace soa::asf;
    for (const Modifier& m : s.modifiers) {
        printf("modifier %s kind %d base node %d (%s) scale %g method %u ranges", m.name.c_str(), m.kind, m.base,
               m.base >= 0 && m.base < (int)s.nodes.size() ? s.nodes[m.base].name.c_str() : "?", m.scale, m.method);
        for (uint32_t r : m.ranges) printf(" %u", r);
        printf("\n");
        for (const ModifierTarget& t : m.targets) {
            printf("  target node %d (%s) weight %g:", t.node, t.node >= 0 && t.node < (int)s.nodes.size() ? s.nodes[t.node].name.c_str() : "?", t.weight);
            for (size_t k = 0; k < t.counts.size(); k++) printf(" %u vertices (%zu bytes)", t.counts[k], t.data[k].size());
            printf("\n");
            if (!t.data.empty() && t.data[0].size() >= 60)
                for (int v = 0; v < 3; v++) {
                    const uint8_t* q = &t.data[0][v * 20];
                    printf("    v%d:", v);
                    for (int k = 0; k < 20; k++) printf(" %02x", q[k]);
                    printf("\n");
                }
        }
    }
    printf("nodes %zu, objects %zu, link names %zu, AMF buffers %zu, blocks %zu\n", s.nodes.size(), s.objects.size(),
           s.link_names.size(), s.amf.buffers().size(), s.amf.blocks().size());
    for (const Node& n : s.nodes) {
        printf("node %3d %-28s %-17s parent %3d pos (%.3f %.3f %.3f) rot (%.4f %.4f %.4f %.4f) scale (%.3f %.3f %.3f)",
               n.index, n.name.c_str(), node_kind_name(n.kind), n.parent, n.pos[0], n.pos[1], n.pos[2], n.rot[0],
               n.rot[1], n.rot[2], n.rot[3], n.scale[0], n.scale[1], n.scale[2]);
        if (n.joint) printf(" orient (%.4f %.4f %.4f %.4f)", n.joint_orient[0], n.joint_orient[1], n.joint_orient[2], n.joint_orient[3]);
        bool off = false;
        for (float v : n.pos_offset) off |= v != 0;
        for (auto& r : n.pivot)
            for (int i = 0; i < 3; i++) off |= r[i] != 0;
        if (off) printf(" offset/pivot!");
        printf(" flags 0x%02x\n", n.flags);
    }
    for (const Object& o : s.objects) {
        printf("object %s (node %d): %zu textures, %zu materials, %zu meshsets, %zu bones\n", o.name.c_str(), o.node,
               o.textures.size(), o.materials.size(), o.meshsets.size(), o.bones.size());
        for (const Texture& t : o.textures) {
            printf("  texture 0x%08x", t.id);
            for (const TextureLevel& l : t.levels) printf(" [fmt %d %dx%d]", l.fmt, l.w, l.h);
            printf("\n    xgmi");
            for (int q = 0x10; q < 0x40; q++) printf(" %02x", t.xgmi[q]);
            printf("\n");
        }
        for (size_t i = 0; i < o.materials.size(); i++) {
            const Material& m = o.materials[i];
            printf("  material %zu flags 0x%x blend %d%s%s:", i, m.flags, m.blend, m.double_sided ? " double-sided" : "",
                   m.alpha_test ? (" alpha-test " + std::to_string(m.alpha_ref)).c_str() : "");
            for (const TextureRef& t : m.textures) printf(" tex(0x%08x %.4s wrap %d kind %d)", t.id, (const char*)&t.cls, t.wrap, t.slot_kind);
            for (const ShaderConst& c : m.constants) {
                printf(" const(0x%x/%d", c.id, c.index);
                for (auto& v : c.values) printf(" %.3f,%.3f,%.3f,%.3f", v[0], v[1], v[2], v[3]);
                printf(")");
            }
            printf("\n");
            if (m.raw.size() >= 0x24) {  // the shader graph's records {u16 size, u16 op, ...}
                size_t g = soa::aff::rd32(&m.raw[0x1c]), gend = soa::aff::rd32(&m.raw[0x20]);
                for (size_t q = g; q + 4 <= gend && q + 4 <= m.raw.size();) {
                    uint16_t size = soa::aff::rd16(&m.raw[q]), op = soa::aff::rd16(&m.raw[q + 2]);
                    if (size < 4 || q + size > m.raw.size()) break;
                    printf("    op 0x%02x:", op);
                    for (size_t k = q + 4; k < q + size; k++) printf(" %02x", m.raw[k]);
                    printf("\n");
                    q += size;
                }
            }
        }
        for (size_t i = 0; i < o.meshsets.size(); i++) {
            const Meshset& m = o.meshsets[i];
            printf("  meshset %zu: material %d prim %d, %u vertices x %u bytes, %u indices%s, bits 0x%llx, palette %zu, flags 0x%x",
                   i, m.material, m.prim, m.vertex_count, m.stride, m.index_count, m.index32 ? " (32-bit)" : "",
                   (unsigned long long)m.asm_bits, m.palette.size(), m.flags);
            if (m.shares >= 0) printf(", draws meshset %d", m.shares);
            printf("\n    palette:");
            for (size_t k = 0; k < m.palette.size(); k++) {
                int b = m.palette[k] < o.bones.size() ? o.bones[m.palette[k]] : -1;
                printf(" %zu=%s", k, b >= 0 && b < (int)s.nodes.size() ? s.nodes[b].name.c_str() : "?");
            }
            printf("\n   ");
            for (const VertexElement& e : m.elements) printf(" %s%d@%d:t%d", usage_name(e.usage), e.index, e.offset, e.type);
            printf("\n");
        }
    }
}

uint64_t fnv(const uint8_t* p, size_t n) {
    uint64_t h = 0xcbf29ce484222325ull;
    for (size_t i = 0; i < n; i++) h = (h ^ p[i]) * 0x100000001b3ull;
    return h;
}

// Each meshset's vertex and index bytes against the dump's uploads (DIR/<fnv1a64>.bin): equal hash
// and equal bytes.
int check_gl_dump(const soa::asf::Scene& s, const std::string& dir) {
    int total = 0, ok = 0;
    for (const auto& o : s.objects)
        for (size_t i = 0; i < o.meshsets.size(); i++) {
            const auto& m = o.meshsets[i];
            if (m.shares >= 0) continue;
            for (int which = 0; which < 2; which++) {
                const Bytes& b = which ? m.indices : m.vertices;
                total++;
                char name[64];
                snprintf(name, sizeof name, "/%016llx.bin", (unsigned long long)fnv(b.data(), b.size()));
                Bytes got;
                bool found = read_file(dir + name, got) && got == b;
                ok += found;
                printf("%-5s %s meshset %zu %s: %zu bytes %s\n", found ? "match" : "MISS", o.name.c_str(), i,
                       which ? "indices" : "vertices", b.size(), name + 1);
            }
        }
    printf("match %d/%d\n", ok, total);
    // With SOA_GL_DRAW_DUMP's draws.tsv in the same dir: the draws of this model (an index count
    // of one of its meshsets, a texture of its own on some unit): the draw's number (draw_N.txt has
    // its uniforms), program, the texture of each unit by this file's ids, blend / cull / depth write
    std::ifstream draws(dir + "/draws.tsv");
    if (draws) {
        std::map<std::string, std::string> id_of_hash;
        for (const auto& o : s.objects)
            for (const auto& t : o.textures) {
                if (t.levels.empty()) continue;
                size_t n = 0;
                const uint8_t* p = s.amf.raw_block(t.levels[0].pixels, &n);
                if (!p) continue;
                char h[32], id[16];
                snprintf(h, sizeof h, "%016llx", (unsigned long long)fnv(p, n));
                snprintf(id, sizeof id, "0x%08x", t.id);
                id_of_hash.emplace(h, id);
            }
        struct Cand { std::string name; std::set<std::string> tex; };  // a meshset and its material's texture ids
        std::map<long, std::vector<Cand>> by_count;
        for (const auto& o : s.objects)
            for (size_t i = 0; i < o.meshsets.size(); i++) {
                Cand c{o.name + "/" + std::to_string(i), {}};
                int mi = o.meshsets[i].material;
                if (mi >= 0 && mi < (int)o.materials.size())
                    for (const auto& t : o.materials[mi].textures) {
                        char id[16];
                        snprintf(id, sizeof id, "0x%08x", t.id);
                        c.tex.insert(id);
                    }
                by_count[(long)o.meshsets[i].index_count].push_back(c);
            }
        std::string line;
        while (std::getline(draws, line)) {
            std::vector<std::string> f;
            size_t a2 = 0, b2;
            while ((b2 = line.find('\t', a2)) != std::string::npos) { f.push_back(line.substr(a2, b2 - a2)); a2 = b2 + 1; }
            f.push_back(line.substr(a2));
            if (f.size() < 11) continue;
            auto mc = by_count.find(std::stol(f[4]));
            if (mc == by_count.end()) continue;
            std::string units;
            bool ours = false;
            std::set<std::string> drawn;
            size_t p = 0;
            for (int u = 0; u < 8; u++) {
                size_t c = f[7].find(',', p);
                std::string h = f[7].substr(p, c == std::string::npos ? std::string::npos : c - p);
                auto it = id_of_hash.find(h);
                if (it != id_of_hash.end()) ours = true, drawn.insert(it->second);
                units += " u" + std::to_string(u) + "=" + (it != id_of_hash.end() ? it->second : h == "-" ? "-" : h == "?" ? "?" : "other");
                if (c == std::string::npos) break;
                p = c + 1;
            }
            if (!ours) continue;
            // among the meshsets with this index count, those whose material uses the most of the bound textures
            // (the shadow / depth passes bind none of them: all candidates are listed)
            std::string who;
            size_t best = 0;
            for (const auto& w : mc->second) {
                size_t uses = 0;
                for (const auto& t : drawn) uses += w.tex.count(t);
                best = std::max(best, uses);
            }
            for (const auto& w : mc->second) {
                size_t uses = 0;
                for (const auto& t : drawn) uses += w.tex.count(t);
                if (best && uses == best) who += (who.empty() ? "" : "|") + w.name;
            }
            if (who.empty())
                for (const auto& w : mc->second) who += (who.empty() ? "" : "|") + w.name;
            printf("draw %s: %s program %s count %s%s | %s | %s | %s\n", f[0].c_str(), who.c_str(), f[1].c_str(), f[4].c_str(), units.c_str(),
                   f[8].c_str(), f[9].c_str(), f[10].c_str());
        }
    }
    return ok == total ? 0 : 1;
}

// ANIM (an .aaf, PKG.apk:MEMBER, or PKG.apk: all its .aaf members) as animations.
bool add_anims(Source& src, const std::string& arg, std::vector<gltf::Anim>& out, std::string* err) {
    std::string path = arg, member;
    size_t colon = arg.find(".apk:");
    if (colon != std::string::npos) {
        path = arg.substr(0, colon + 4);
        member = arg.substr(colon + 5);
    }
    Bytes file;
    std::string name;
    if (!load_input(src, path, file, name, err)) return false;
    auto entries = soa::aska::isf_entries(file);
    if (entries.empty()) {
        gltf::Anim an;
        an.name = name.empty() ? path : name;
        an.file = std::move(file);
        out.push_back(std::move(an));
        return true;
    }
    bool found = false;
    for (const auto& e : entries) {
        bool aaf = e.name.size() > 4 && e.name.substr(e.name.size() - 4) == ".aaf";
        if (member.empty() ? !aaf : e.name != member) continue;
        if ((size_t)e.offset + e.size > file.size()) continue;
        gltf::Anim an;
        an.name = path + ":" + e.name;
        an.file.assign(file.begin() + e.offset, file.begin() + e.offset + e.size);
        out.push_back(std::move(an));
        found = true;
    }
    if (!found && err) *err = arg + ": no such member";
    return found;
}

void usage() {
    fprintf(stderr,
            "usage: asf2gltf [--data DIR|ZIP] MODEL [-o OUT.glb] [--gltf] [--aaf ANIM]... [--set FILE] [--fps N] [--no-ext]\n"
            "                [--info] [--textures DIR] [--check-gl-dump DIR] [--shaders DIR] [--raw-out DIR]\n");
}

}  // namespace

int main(int argc, char** argv) {
    Source src;
    src.data_path = repo_dir_of(argv[0]) + "/work/SOA-3.7.0-canonical-data.zip";
    std::string model, out, textures_dir, gl_dump, set_file, shaders_dir, raw_dir;
    std::vector<std::string> anims;
    bool info = false;
    gltf::Options opt;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        auto next = [&]() -> std::string {
            if (i + 1 >= argc) { usage(); exit(2); }
            return argv[++i];
        };
        if (a == "--data") src.data_path = next();
        else if (a == "-o") out = next();
        else if (a == "--gltf") opt.separate = true;
        else if (a == "--no-ext") opt.extensions = false;
        else if (a == "--aaf") anims.push_back(next());
        else if (a == "--set") set_file = next();
        else if (a == "--fps") opt.fps = std::stof(next());
        else if (a == "--info") info = true;
        else if (a == "--textures") textures_dir = next();
        else if (a == "--check-gl-dump") gl_dump = next();
        else if (a == "--shaders") shaders_dir = next();
        else if (a == "--raw-out") raw_dir = next();
        else if (a == "-h" || a == "--help") { usage(); return 0; }
        else if (!a.empty() && a[0] == '-') { usage(); return 2; }
        else model = a;
    }
    if (model.empty()) { usage(); return 2; }
    std::string err, name;
    Bytes file;
    if (!load_input(src, model, file, name, &err)) { fprintf(stderr, "asf2gltf: %s\n", err.c_str()); return 1; }
    soa::asf::Scene scene;
    std::vector<std::string> warnings;
    if (!soa::asf::load(file, scene, &err, &warnings)) { fprintf(stderr, "asf2gltf: %s: %s\n", model.c_str(), err.c_str()); return 1; }
    for (auto& w : warnings) fprintf(stderr, "asf2gltf: warning: %s\n", w.c_str());
    if (info) print_info(scene);
    if (!textures_dir.empty()) {
        for (const auto& o : scene.objects)
            for (const auto& t : o.textures) {
                if (t.levels.empty()) continue;
                Bytes rgba;
                if (!soa::asf::decode_texture(scene, t.levels[0], rgba, &err)) {
                    fprintf(stderr, "asf2gltf: %s texture 0x%08x: %s\n", o.name.c_str(), t.id, err.c_str());
                    continue;
                }
                char fn[256];
                snprintf(fn, sizeof fn, "%s/%s_%08x.png", textures_dir.c_str(), o.name.c_str(), t.id);
                soa::png_write(fn, t.levels[0].w, t.levels[0].h, 4, rgba.data());
            }
    }
    int rc = 0;
    if (!gl_dump.empty()) rc |= check_gl_dump(scene, gl_dump);
    if (!raw_dir.empty() && !gltf::write_raw_streams(scene, raw_dir, &err)) { fprintf(stderr, "asf2gltf: %s\n", err.c_str()); return 1; }
    if (!out.empty()) {
        gltf::Input in;
        in.scene = &scene;
        in.source_name = name;
        if (!shaders_dir.empty()) {
            in.shaders = gltf::capture_shaders(scene, shaders_dir, &err);
            if (!in.shaders.contains("materials") || in.shaders["materials"].empty())
                fprintf(stderr, "asf2gltf: warning: %s\n", err.empty() ? "no shaders captured" : err.c_str());
        }
        for (const std::string& a : anims)
            if (!add_anims(src, a, in.anims, &err)) { fprintf(stderr, "asf2gltf: %s\n", err.c_str()); return 1; }
        if (!set_file.empty()) {
            Bytes js;
            if (!read_file(set_file, js)) { fprintf(stderr, "asf2gltf: cannot read %s\n", set_file.c_str()); return 1; }
            nlohmann::ordered_json set = nlohmann::ordered_json::parse(js.begin(), js.end(), nullptr, false);
            if (set.is_discarded() || !set.contains("animations")) { fprintf(stderr, "asf2gltf: %s: not an animation set\n", set_file.c_str()); return 1; }
            for (auto& e : set["animations"]) {
                std::vector<gltf::Anim> one;
                if (!add_anims(src, e.value("source", ""), one, &err)) { fprintf(stderr, "asf2gltf: %s\n", err.c_str()); return 1; }
                for (auto& an : one) {
                    an.title = e.value("name", "");
                    an.role = e.value("role", "");
                    if (e.contains("extras")) an.extras = e["extras"];
                    in.anims.push_back(std::move(an));
                }
            }
        }
        if (!gltf::write(in, opt, out, &err)) { fprintf(stderr, "asf2gltf: %s\n", err.c_str()); return 1; }
    }
    return rc;
}
