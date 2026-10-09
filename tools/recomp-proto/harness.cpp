// The prototype's differential harness (docs/PLAN-recomp.md, "The prototype"): loads the 3.7.0
// libSOA.so with the runtime (no natives), and for every function of functions.txt runs the
// original under the JIT (guest_call_raw) and the recompiled C++ (gen.cpp) on the same random
// inputs, comparing the result registers and every byte of the memory the arguments point at.
// Then times both on a few functions. Built and run by tools/recomp-proto/build.sh.
//
//   harness LIB [FUNCTIONS.txt] [ITERATIONS]
#include <algorithm>
#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "recomp_rt.h"
#include "soaruntime/core/cpu.h"
#include "soaruntime/core/hle.h"
#include "soaruntime/core/loader.h"
#include "soaruntime/core/vfs.h"

extern const rc::Entry rc_table[];
extern const unsigned rc_table_size;

namespace rc {
u64 lib_base = 0;
static u64 g_fallback_calls = 0;

static Fn lookup(u64 target) {
    u64 va = target - lib_base;
    const Entry* e = std::lower_bound(rc_table, rc_table + rc_table_size, va, [](const Entry& x, u64 v) { return x.vaddr < v; });
    return e != rc_table + rc_table_size && e->vaddr == va ? e->fn : nullptr;
}

void call(St& s, u64 target) {
    if (Fn f = lookup(target)) {
        u64 lr = s.x[30];
        f(s);
        s.x[30] = lr;  // (a RET left pc = lr; the caller continues at its own label)
        return;
    }
    // Not recompiled (an import's PLT stub, or a function outside the sample): the JIT runs it.
    g_fallback_calls++;
    soa::V128 v[8];
    for (int i = 0; i < 8; i++) v[i] = {s.v[i].lo, s.v[i].hi};
    soa::GuestResult g = soa::guest_call_raw(target, s.x, 8, v, 8, s.x[8]);
    s.x[0] = g.x0;
    s.x[1] = g.x1;
    s.v[0] = {g.v0.lo, g.v0.hi};
    s.v[1] = {g.v1.lo, g.v1.hi};
    s.v[2] = {g.v2.lo, g.v2.hi};
    s.v[3] = {g.v3.lo, g.v3.hi};
}
}  // namespace rc

using namespace rc::types;

struct Sample {
    u64 va, size;
    std::string name, spec;
    rc::Fn fn;
};

static constexpr int kRegions = 16;
static constexpr size_t kRegion = 4096;
alignas(4096) static u8 g_arena[kRegions * kRegion];
static u8 g_snap[sizeof g_arena], g_after_jit[sizeof g_arena];
alignas(16) static u8 g_stack[1 << 16];

static std::mt19937_64 rng(12345);

static u32 rand_float_bits() {
    u64 r = rng();
    int k = r % 100;
    std::uniform_real_distribution<float> small(-10.f, 10.f), big(-1e4f, 1e4f);
    if (k < 70) return std::bit_cast<u32>(small(rng));
    if (k < 80) return std::bit_cast<u32>(big(rng));
    if (k < 85) return (r >> 8 & 1) ? 0x80000000u : 0u;
    if (k < 88) return (r >> 8 & 1) ? 0xff800000u : 0x7f800000u;
    if (k < 91) return 0x7f800000u | (u32)(r >> 32 & 0x807fffffu) | 1u;  // NaNs, quiet or signalling
    if (k < 94) return (u32)(r >> 32) & 0x807fffffu;                       // denormals
    return (u32)(r >> 32);
}
static void fill_float(u8* p) {
    for (size_t i = 0; i < kRegion; i += 4) {
        u32 b = rand_float_bits();
        memcpy(p + i, &b, 4);
    }
}
static void fill_bytes(u8* p) {
    for (size_t i = 0; i < kRegion; i++) p[i] = (u8)rng();
    p[kRegion - 1] = 0;
    // (a NUL somewhere in the middle sometimes, for the strlen callers)
    if (rng() % 2) p[rng() % 300] = 0;
}

struct Inputs {
    u64 x[16];
    int nx = 0;
    soa::V128 v[8];
    int nv = 0;
};

static Inputs make_inputs(const std::string& spec) {
    Inputs in;
    int region = 0;
    std::istringstream ss(spec);
    std::string t;
    for (int r = 0; r < kRegions; r++) fill_float(g_arena + r * kRegion);
    while (ss >> t) {
        char c = t[0];
        if (c == 'p' || c == 's') {
            u8* p = g_arena + (region++) * kRegion;
            if (c == 's') fill_bytes(p);
            in.x[in.nx++] = (u64)p;
        } else if (c == 'n') in.x[in.nx++] = rng() % 257;
        else if (c == 'i') in.x[in.nx++] = rng() % 3;
        else if (c == 'c') in.x[in.nx++] = rng() % 256;
        else if (c == 'K') in.x[in.nx++] = 64;
        else if (c == 'x') in.x[in.nx++] = rng();
        else if (c == 'f') in.v[in.nv++] = {rand_float_bits(), 0};
    }
    return in;
}

static void run_recomp(const Sample& f, const Inputs& in, rc::St& s) {
    memset(&s, 0, sizeof s);
    for (int i = 0; i < in.nx && i < 8; i++) s.x[i] = in.x[i];
    for (int i = 0; i < in.nv; i++) s.v[i] = {in.v[i].lo, in.v[i].hi};
    s.x[8] = (u64)(g_arena + 15 * kRegion);
    u64 sp = ((u64)g_stack + sizeof g_stack - 4096) & ~15ull;
    for (int i = 8; i < in.nx; i++) memcpy((void*)(sp + 8 * (i - 8)), &in.x[i], 8);  // stack arguments
    s.sp = sp;
    s.x[30] = 0xdead0000;
    s.tpidr = (u64)soa::guest_thread().tls;
    f.fn(s);
}

static soa::GuestResult run_jit(const Sample& f, const Inputs& in) {
    // (all eight argument registers of each kind, zero beyond the arguments: the JIT's
    // registers would otherwise keep the previous call's values, and the recompiled run starts
    // from zeros)
    u64 x[16] = {};
    soa::V128 v[8] = {};
    for (int i = 0; i < in.nx; i++) x[i] = in.x[i];
    for (int i = 0; i < in.nv; i++) v[i] = in.v[i];
    return soa::guest_call_raw(rc::lib_base + f.va, x, std::max(8, in.nx), v, 8, (u64)(g_arena + 15 * kRegion));
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: harness LIB [FUNCTIONS.txt] [ITERATIONS]\n");
        return 2;
    }
    std::string list = argc > 2 ? argv[2] : std::string(std::filesystem::path(argv[0]).parent_path() / "functions.txt");
    int iters = argc > 3 ? atoi(argv[3]) : 2000;
    std::string dir = std::filesystem::temp_directory_path().string() + "/recomp-proto.XXXXXX";
    if (!mkdtemp(dir.data())) return 1;
    soa::vfs_init({dir});
    soa::cpu_global_init();
    soa::hle_init();
    soa::LoadedLib* lib = soa::load_library(argv[1]);
    rc::lib_base = lib->base;

    std::vector<Sample> fns;
    std::ifstream in(list);
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ls(line);
        Sample f;
        std::string va;
        ls >> va >> f.size >> f.name;
        std::getline(ls, f.spec);
        f.va = std::stoull(va, nullptr, 16);
        f.fn = rc::lookup(rc::lib_base + f.va);
        fns.push_back(f);
    }

    int bad_fns = 0;
    u64 total_runs = 0, total_bad = 0;
    printf("function\tguest bytes\truns\tmismatches\tfirst mismatch\n");
    for (auto& f : fns) {
        if (!f.fn) {
            printf("%s\t%" PRIu64 "\t-\t-\tnot generated\n", f.name.c_str(), f.size);
            bad_fns++;
            continue;
        }
        int bad = 0;
        std::string first;
        for (int it = 0; it < iters; it++) {
            Inputs inp = make_inputs(f.spec);
            memcpy(g_snap, g_arena, sizeof g_arena);
            soa::GuestResult g = run_jit(f, inp);
            memcpy(g_after_jit, g_arena, sizeof g_arena);
            memcpy(g_arena, g_snap, sizeof g_arena);
            rc::St s;
            run_recomp(f, inp, s);
            std::string why;
            if (s.x[0] != g.x0) why = "x0";
            else if (s.v[0].lo != g.v0.lo || s.v[0].hi != g.v0.hi) why = "v0";
            else if (memcmp(g_arena, g_after_jit, sizeof g_arena) != 0) {
                size_t k = 0;
                while (g_arena[k] == g_after_jit[k]) k++;
                char b[96];
                snprintf(b, sizeof b, "memory region %zu +0x%zx", k / kRegion, k % kRegion);
                why = b;
            }
            if (!why.empty()) {
                if (!bad) {
                    char b[160];
                    snprintf(b, sizeof b, "%s (iteration %d: x0 %" PRIx64 " vs %" PRIx64 ", v0 %" PRIx64 " vs %" PRIx64 ")", why.c_str(), it, s.x[0], g.x0, s.v[0].lo, g.v0.lo);
                    first = b;
                }
                bad++;
            }
        }
        total_runs += iters;
        total_bad += bad;
        if (bad) bad_fns++;
        printf("%s\t%" PRIu64 "\t%d\t%d\t%s\n", f.name.c_str(), f.size, iters, bad, first.c_str());
    }
    printf("\nfunctions %zu, with mismatches or not generated %d; runs %" PRIu64 ", mismatching runs %" PRIu64 "; fallback (JIT) calls %" PRIu64 "\n", fns.size(), bad_fns,
           total_runs, total_bad, rc::g_fallback_calls);

    // Timing: the same inputs, many calls, JIT vs recompiled (the JIT's figure includes guest_call's entry cost).
    printf("\ntiming (ns per call, same inputs; best of 9)\tjit (incl. guest_call entry)\trecomp\tratio\n");
    for (auto& f : fns) {
        if (!f.fn) continue;
        static const char* timed[] = {"_ZN4Aska6Matrix3MulEPKS0_S2_", "_ZN4Aska6Matrix6InvertEv", "_ZN4Aska4Hash3CRCEPKhmPj", "_ZN4Aska6detail12SpookyHashV26UpdateEPKvm",
                                      "_ZN4Aska3Box13IsIntersectedEPKS0_", "_ZN4Aska4Hash3MD5EPKcmPcmS3_m", "_ZNK4Aska6Matrix11ApplyVectorEPNS_6VectorEPKS1_"};
        if (std::find_if(std::begin(timed), std::end(timed), [&](const char* n) { return f.name == n; }) == std::end(timed)) continue;
        Inputs inp = make_inputs(f.spec);
        for (int i = 0; i < inp.nx; i++)
            if (f.spec.find('n') != std::string::npos && inp.x[i] < 257) inp.x[i] = 256;  // the longest input
        memcpy(g_snap, g_arena, sizeof g_arena);
        // (the best of 9 rounds each: the machine is shared; the 16 KiB copy per call restores the
        // inputs for both and is subtracted, measured alone the same way)
        const int n = 5000;
        auto per_call = [&](auto body) {
            double best = 1e30;
            for (int round = 0; round < 9; round++) {
                auto t0 = std::chrono::steady_clock::now();
                for (int i = 0; i < n; i++) {
                    memcpy(g_arena, g_snap, 4 * kRegion);
                    body();
                    asm volatile("" ::: "memory");
                }
                auto t1 = std::chrono::steady_clock::now();
                best = std::min(best, std::chrono::duration<double, std::nano>(t1 - t0).count() / n);
            }
            return best;
        };
        rc::St s;
        double copy = per_call([] {});
        double jit = per_call([&] { run_jit(f, inp); });
        double rec = per_call([&] { run_recomp(f, inp, s); });
        printf("%s\t%.0f\t%.0f\t%.1fx\n", f.name.c_str(), jit - copy, rec - copy, (jit - copy) / (rec - copy));
    }
    std::filesystem::remove_all(dir);
    return bad_fns ? 1 : 0;
}
