// aafdump: the game's animations (.aaf) in text: header, targets, controllers, keys; their values
// (soa_models' evaluator, soa/aaf.h: the game's CalcValue bit for bit); and the proof of that
// against values the game computed (docs/notes.md "Animations (AAF) for tools").
//
// Usage: aafdump [--data DIR|ZIP] ANIM [options]
//   ANIM          a game path from the 3.7.0 download (--data; default work/SOA-3.7.0-canonical-data.zip
//                 of the checkout) or a local file: an .aaf, or a motion package (.apk, "\0ISF"):
//                 PKG lists its members, PKG:MEMBER (e.g. Motion/FemaleTwoHandedSword.apk:idle.aaf)
//                 dumps one
//   --asf MODEL   name the targets by the model's node tree (kind, index; "missing" when absent)
//   --keys        print every controller's keys too
//   --sample T    every controller's value at frame T
//   --csv OUT     every controller sampled at each frame 0..length (--step S, default 1) as CSV
//   --verify DIR  compare with the guest's values recorded by the live selftest anim/aaf-eval-dump
//                 (SOA_AAF_EVAL_DUMP=DIR): exit 1 on any difference
#include <soa/aaf.h>
#include <soa/aff.h>
#include <soa/asf.h>
#include <soa/aska_image.h>
#include <soa/file_tree.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using soa::aff::Bytes;
namespace aaf = soa::aaf;

namespace {

bool read_file(const std::string& path, Bytes& out) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    out.assign(std::istreambuf_iterator<char>(f), {});
    return true;
}

std::string repo_dir_of(const char* argv0) {
    std::string p = argv0;
    size_t s = p.rfind('/');
    return (s == std::string::npos ? std::string(".") : p.substr(0, s)) + "/../../..";
}

struct Source {
    std::string data_path;
    std::shared_ptr<const soa::FileTree> tree;
    bool load(const std::string& arg, Bytes& out, std::string* err) {
        std::string name;
        Bytes raw;
        if (read_file(arg, raw)) {
            name = soa::aff::game_name_of(arg);
        } else {
            if (!tree) tree = soa::FileTree::open(data_path, err);
            if (!tree) return false;
            if (!tree->read(arg, raw)) { if (err) *err = arg + ": not a file and not in " + data_path; return false; }
            name = arg;
        }
        return soa::aff::decode_game_file(name, raw, out, err);
    }
};

void print_anim(const aaf::Animation& a, const soa::asf::Scene* s, bool keys) {
    printf("AAF version 0x%x, %u targets, controllers %zu (A %u, B %u, C %u), length %g frames, flags 0x%x\n", a.version,
           a.target_count, a.controllers.size(), a.count_a, a.count_b, a.count_c, a.length, a.flags);
    std::map<std::string, const soa::asf::Node*> by_name;
    if (s)
        for (const auto& n : s->nodes) by_name[n.name] = &n;
    const Bytes& d = *a.file;
    for (size_t ti = 0; ti < a.targets.size(); ti++) {
        const aaf::Target& t = a.targets[ti];
        printf("target %zu %s type %d flags 0x%x", ti, t.name.c_str(), t.type, t.flags);
        if (s) {
            auto it = by_name.find(t.name);
            if (it == by_name.end()) printf(" [node missing]");
            else printf(" [node %d %s]", it->second->index, soa::asf::node_kind_name(it->second->kind));
        }
        printf("\n");
        for (int ci : t.controllers) {
            const aaf::Controller& c = a.controllers[ci];
            printf("  ctrl @0x%zx %s", c.offset, aaf::controller_kind_name(c.kind));
            if (c.keyframed()) {
                std::string why;
                bool ok = aaf::supported(c, &why);
                printf(" %s %s %s%s", aaf::attribute_name(c.attr), aaf::cp_type_name(c.cp_type), aaf::compression_name(c.comp),
                       c.frame_sorted() ? " frame-sorted" : "");
                if (c.constant()) {
                    float v[4] = {0, 0, 0, 0};
                    aaf::evaluate_constant(a, c, v);
                    int n = aaf::components(c.cp_type);
                    printf(" constant (");
                    for (int i = 0; i < n; i++) printf(i ? " %g" : "%g", v[i]);
                    printf(")");
                } else {
                    printf(" keys %u range [%g, %g] pre %d post %d", c.count, c.start, c.end, c.pre, c.post);
                    if (!ok) printf(" (not evaluated: %s)", why.c_str());
                }
            } else {
                printf(" (+1 %d, +4 %d, flags 0x%02x, size 0x%x)", c.sub, c.comp, c.flags, c.size);
                if (c.kind >= 6 && c.kind <= 8 && c.offset + 0x50 <= d.size()) {
                    // the constraint's source name (+0x20, when stored by name)
                    const char* src = (const char*)&d[c.offset + 0x20];
                    if (!memcmp(src, "R:", 2)) printf(" source %.32s", src + 2);
                }
            }
            printf("\n");
            if (keys && c.keyframed() && !c.constant()) {
                const uint8_t* kf = &d[c.kf];
                for (uint32_t k = 0; k < c.count && k < 4096; k++) {
                    float tk = soa::aff::rdf(kf + 0x18 + k * 4);
                    float v[4] = {0, 0, 0, 0};
                    if (aaf::supported(c)) aaf::evaluate(a, c, tk, v);
                    printf("    key %u t %g value (%g %g %g %g)\n", k, tk, v[0], v[1], v[2], v[3]);
                }
            }
        }
    }
}

int sample(const aaf::Animation& a, float t) {
    for (const aaf::Controller& c : a.controllers) {
        if (!c.keyframed() || (!c.constant() && !aaf::supported(c))) continue;
        float v[4] = {0, 0, 0, 1};
        if (c.constant()) aaf::evaluate_constant(a, c, v);
        else aaf::evaluate(a, c, t, v);
        int n = aaf::components(c.cp_type);
        printf("%s %s t=%g:", a.targets[c.target].name.c_str(), aaf::attribute_name(c.attr), t);
        for (int i = 0; i < (n == 3 ? 3 : n); i++) printf(" %.9g", v[i]);
        printf("\n");
    }
    return 0;
}

int csv(const aaf::Animation& a, const std::string& path, float step) {
    FILE* f = fopen(path.c_str(), "w");
    if (!f) { fprintf(stderr, "aafdump: cannot write %s\n", path.c_str()); return 1; }
    fprintf(f, "target,attribute,frame,x,y,z,w\n");
    for (const aaf::Controller& c : a.controllers) {
        if (!c.keyframed() || (!c.constant() && !aaf::supported(c))) continue;
        for (float t = 0; t <= a.length + 1e-3f; t += step) {
            float v[4] = {0, 0, 0, 1};
            if (c.constant()) aaf::evaluate_constant(a, c, v);
            else aaf::evaluate(a, c, t, v);
            int n = aaf::components(c.cp_type);
            fprintf(f, "%s,%s,%g", a.targets[c.target].name.c_str(), aaf::attribute_name(c.attr), t);
            for (int i = 0; i < 4; i++) {
                if (i < n) fprintf(f, ",%.9g", v[i]);
                else fprintf(f, ",");
            }
            fprintf(f, "\n");
        }
    }
    fclose(f);
    return 0;
}

// The guest's values (anim/aaf-eval-dump) against evaluate(), byte for byte.
int verify(const std::string& dir) {
    DIR* dp = opendir(dir.c_str());
    if (!dp) { fprintf(stderr, "aafdump: no directory %s\n", dir.c_str()); return 1; }
    std::vector<std::string> files;
    while (dirent* e = readdir(dp)) {
        std::string n = e->d_name;
        if (n.size() > 8 && n.substr(n.size() - 8) == ".aafeval") files.push_back(dir + "/" + n);
    }
    closedir(dp);
    std::sort(files.begin(), files.end());
    struct Tally { long ok = 0, bad = 0, skipped = 0; };
    std::map<std::string, Tally> by_type;
    long total_bad = 0, total_ok = 0, total_skip = 0;
    int shown = 0;
    for (const std::string& path : files) {
        Bytes d;
        bool ok = read_file(path, d) && d.size() >= 16;
        bool v2 = ok && !memcmp(d.data(), "AAFEVAL2", 8);  // (AAFEVAL1: no call field, CalcValue only)
        if (!ok || (!v2 && memcmp(d.data(), "AAFEVAL1", 8))) {
            fprintf(stderr, "aafdump: %s: not a dump\n", path.c_str());
            return 1;
        }
        uint32_t fsz = soa::aff::rd32(&d[8]);
        Bytes file(d.begin() + 12, d.begin() + 12 + fsz);
        size_t p = 12 + fsz;
        uint32_t nrec = soa::aff::rd32(&d[p]);
        p += 4;
        aaf::Animation a;
        std::string err;
        if (!aaf::load(file, a, &err)) { fprintf(stderr, "aafdump: %s: %s\n", path.c_str(), err.c_str()); return 1; }
        std::map<size_t, const aaf::Controller*> by_off;
        for (const auto& c : a.controllers) by_off[c.offset] = &c;
        const size_t rs = v2 ? 28 : 24;
        for (uint32_t r = 0; r < nrec && p + rs <= d.size(); r++, p += rs) {
            uint32_t off = soa::aff::rd32(&d[p]);
            uint32_t call = v2 ? soa::aff::rd32(&d[p + 4]) : 0;
            size_t vp = p + (v2 ? 12 : 8);
            float t = soa::aff::rdf(&d[vp - 4]);
            auto it = by_off.find(off);
            std::string key = "?";
            if (it == by_off.end()) { total_skip++; continue; }
            const aaf::Controller& c = *it->second;
            key = std::string(aaf::cp_type_name(c.cp_type)) + "/" + aaf::compression_name(c.comp) +
                  (c.constant() ? "/constant" : "") + " pre" + std::to_string(c.pre) + " post" + std::to_string(c.post);
            if (call) key += " CalcValueConstant(" + std::to_string(call - 1) + ")";
            uint32_t mine[4] = {0x7fbadbad, 0x7fbadbad, 0x7fbadbad, 0x7fbadbad};
            bool have = call ? aaf::evaluate_constant(a, c, (float*)mine) : (aaf::supported(c) && aaf::evaluate(a, c, t, (float*)mine));
            if (!have) { by_type[key].skipped++; total_skip++; continue; }
            if (!memcmp(mine, &d[vp], 16)) {
                by_type[key].ok++;
                total_ok++;
            } else {
                by_type[key].bad++;
                total_bad++;
                if (shown++ < 4000) {
                    const uint32_t* g = (const uint32_t*)&d[vp];
                    float gf[4], mf[4];
                    memcpy(gf, g, 16);
                    memcpy(mf, mine, 16);
                    printf("DIFF %s ctrl @0x%x %s %s t=%.9g guest (%.9g %.9g %.9g %.9g | %08x %08x %08x %08x) tool (%.9g %.9g %.9g %.9g | %08x %08x %08x %08x)\n",
                           path.c_str(), off, a.targets[c.target].name.c_str(), key.c_str(), t, gf[0], gf[1], gf[2], gf[3],
                           g[0], g[1], g[2], g[3], mf[0], mf[1], mf[2], mf[3], mine[0], mine[1], mine[2], mine[3]);
                }
            }
        }
    }
    for (const auto& [k, v] : by_type)
        printf("%-48s equal %ld, different %ld, not evaluated %ld\n", k.c_str(), v.ok, v.bad, v.skipped);
    printf("verify: %zu files, %ld values equal, %ld different, %ld not evaluated\n", files.size(), total_ok, total_bad, total_skip);
    return total_bad == 0 && total_ok > 0 ? 0 : 1;
}

void usage() {
    fprintf(stderr, "usage: aafdump [--data DIR|ZIP] ANIM[:MEMBER] [--asf MODEL] [--keys] [--sample T] [--csv OUT [--step S]]\n"
                    "       aafdump --verify DIR\n");
}

}  // namespace

int main(int argc, char** argv) {
    Source src;
    src.data_path = repo_dir_of(argv[0]) + "/work/SOA-3.7.0-canonical-data.zip";
    std::string anim, asf, csv_out, verify_dir;
    bool keys = false, have_sample = false;
    float sample_t = 0, step = 1;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        auto next = [&]() -> std::string {
            if (i + 1 >= argc) { usage(); exit(2); }
            return argv[++i];
        };
        if (a == "--data") src.data_path = next();
        else if (a == "--asf") asf = next();
        else if (a == "--keys") keys = true;
        else if (a == "--sample") { have_sample = true; sample_t = std::stof(next()); }
        else if (a == "--csv") csv_out = next();
        else if (a == "--step") step = std::stof(next());
        else if (a == "--verify") verify_dir = next();
        else if (a == "-h" || a == "--help") { usage(); return 0; }
        else if (!a.empty() && a[0] == '-') { usage(); return 2; }
        else anim = a;
    }
    if (!verify_dir.empty()) return verify(verify_dir);
    if (anim.empty()) { usage(); return 2; }
    std::string err, member;
    size_t colon = anim.find(".apk:");
    if (colon != std::string::npos) {
        member = anim.substr(colon + 5);
        anim = anim.substr(0, colon + 4);
    }
    Bytes file;
    if (!src.load(anim, file, &err)) { fprintf(stderr, "aafdump: %s\n", err.c_str()); return 1; }
    auto entries = soa::aska::isf_entries(file);
    if (!entries.empty()) {
        if (member.empty()) {
            printf("package %s: %zu members\n", anim.c_str(), entries.size());
            for (const auto& e : entries) printf("  %s %u bytes\n", e.name.c_str(), e.size);
            return 0;
        }
        bool found = false;
        for (const auto& e : entries)
            if (e.name == member) {
                file = Bytes(file.begin() + e.offset, file.begin() + e.offset + e.size);
                found = true;
            }
        if (!found) { fprintf(stderr, "aafdump: %s has no member %s\n", anim.c_str(), member.c_str()); return 1; }
    }
    aaf::Animation a;
    if (!aaf::load(file, a, &err)) { fprintf(stderr, "aafdump: %s\n", err.c_str()); return 1; }
    std::unique_ptr<soa::asf::Scene> scene;
    Bytes model;
    if (!asf.empty()) {
        if (!src.load(asf, model, &err)) { fprintf(stderr, "aafdump: %s\n", err.c_str()); return 1; }
        scene = std::make_unique<soa::asf::Scene>();
        if (!soa::asf::load(model, *scene, &err)) { fprintf(stderr, "aafdump: %s: %s\n", asf.c_str(), err.c_str()); return 1; }
    }
    if (have_sample) return sample(a, sample_t);
    if (!csv_out.empty()) return csv(a, csv_out, step);
    print_anim(a, scene.get(), keys);
    return 0;
}
