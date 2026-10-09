// asf2gltf: the game's 3D models (.asf) and their animations (.aaf) as glTF 2.0 (docs/notes.md
// "Meshes (ASF)", "Models and animation"; the reader is soa_models: soa/asf.h, soa/aaf.h).
//
// Usage: asf2gltf [--data DIR|ZIP] MODEL [options]
//   MODEL        a game path read from the 3.7.0 download (--data; default
//                work/SOA-3.7.0-canonical-data.zip of the checkout), e.g. Character/etc2/hi/cp0303_b04a.asf,
//                or a local file (ADLD-wrapped with its game path in it, or already decoded)
//   -o OUT       OUT.glb (one self-contained file), or OUT.gltf + OUT.bin with --gltf
//   --info       print the scene (nodes, objects, meshsets, vertex formats, materials, textures)
//   --textures DIR  also write every texture level 0 as DIR/<object>_<id>.png
//   --check-gl-dump DIR  compare every meshset's vertex and index bytes with the buffers a run of
//                the game uploaded (soa with SOA_GL_BUFFER_DUMP=DIR): prints one line per meshset
//                and "match N/M"; exit 1 unless every meshset matched
#include <soa/aff.h>
#include <soa/asf.h>
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
            printf("\n");
        }
        for (size_t i = 0; i < o.materials.size(); i++) {
            const Material& m = o.materials[i];
            printf("  material %zu flags 0x%x blend %d:", i, m.flags, m.blend);
            for (const TextureRef& t : m.textures) printf(" tex(0x%08x %.4s wrap %d kind %d)", t.id, (const char*)&t.cls, t.wrap, t.slot_kind);
            for (const ShaderConst& c : m.constants) {
                printf(" const(0x%x/%d", c.id, c.index);
                for (auto& v : c.values) printf(" %.3f,%.3f,%.3f,%.3f", v[0], v[1], v[2], v[3]);
                printf(")");
            }
            printf("\n");
        }
        for (size_t i = 0; i < o.meshsets.size(); i++) {
            const Meshset& m = o.meshsets[i];
            printf("  meshset %zu: material %d prim %d, %u vertices x %u bytes, %u indices%s, bits 0x%llx, palette %zu, flags 0x%x",
                   i, m.material, m.prim, m.vertex_count, m.stride, m.index_count, m.index32 ? " (32-bit)" : "",
                   (unsigned long long)m.asm_bits, m.palette.size(), m.flags);
            if (m.shares >= 0) printf(", draws meshset %d", m.shares);
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
    return ok == total ? 0 : 1;
}

void usage() {
    fprintf(stderr,
            "usage: asf2gltf [--data DIR|ZIP] MODEL [-o OUT.glb] [--gltf] [--aaf ANIM]... [--no-ext]\n"
            "                [--info] [--textures DIR] [--check-gl-dump DIR]\n");
}

}  // namespace

int main(int argc, char** argv) {
    Source src;
    src.data_path = repo_dir_of(argv[0]) + "/work/SOA-3.7.0-canonical-data.zip";
    std::string model, out, textures_dir, gl_dump;
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
        else if (a == "--info") info = true;
        else if (a == "--textures") textures_dir = next();
        else if (a == "--check-gl-dump") gl_dump = next();
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
    if (!out.empty()) {
        gltf::Input in;
        in.scene = &scene;
        in.source_name = name;
        Source* sp = &src;
        for (const std::string& a : anims) {
            gltf::Anim an;
            if (!load_input(*sp, a, an.file, an.name, &err)) { fprintf(stderr, "asf2gltf: %s\n", err.c_str()); return 1; }
            in.anims.push_back(std::move(an));
        }
        if (!gltf::write(in, opt, out, &err)) { fprintf(stderr, "asf2gltf: %s\n", err.c_str()); return 1; }
    }
    return rc;
}
