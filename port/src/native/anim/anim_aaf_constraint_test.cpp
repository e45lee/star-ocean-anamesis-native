// anim/aaf-constraint-dump: the guest's own PRS constraint evaluation, recorded for the glTF viewer's
// proof (tools/gltf-viewer/verify_constraints.py: tools/gltf-viewer/constraints.js gives the game's
// results from the same inputs; docs/notes.md "Animations (AAF) for tools").
//
// On a live screen (port/scripts/selftest_live.sh SOA OUT TMP anim/aaf-constraint --at battle) probes on
// Aska::AafPRSConstraintController::SetPoint / SetPointAxis / SetOrient / SetOrientAxis take the calls the
// game makes. For each, the test runs the guest function once itself (guest_call: the constraint is
// idempotent, the game's own call follows) and records, as one JSON line in SOA_AAF_CONSTRAINT_DUMP:
// the kind, the definition (offset, axis mask, per source its weight and own offset), the target's world
// matrix before and after, its parent's world matrix, and per source its world matrix, its local
// position (+0x80) and its parent's world matrix (the source's container +0xf0, its +0xe8). Matrices are
// the HierarchicalObject's world matrix at +0x40: 16 floats, rows, translation in column 3.
// Without SOA_AAF_CONSTRAINT_DUMP, or at the title, the test notes it and passes.
#include <soa/env.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <string>

#include "native/common/test.h"
#include "native/render/render_test_util.h"

namespace soa::native::anim {
namespace {

using namespace render::testutil;

TEST_PROBE(g_probeSetPoint, "_ZN4Aska26AafPRSConstraintController8SetPointEPNS_18HierarchicalObjectE");
TEST_PROBE(g_probeSetPointAxis, "_ZN4Aska26AafPRSConstraintController12SetPointAxisEPNS_18HierarchicalObjectE");
TEST_PROBE(g_probeSetOrient, "_ZN4Aska26AafPRSConstraintController9SetOrientEPNS_18HierarchicalObjectE");
TEST_PROBE(g_probeSetOrientAxis, "_ZN4Aska26AafPRSConstraintController13SetOrientAxisEPNS_18HierarchicalObjectE");

float rdf(u64 p) {
    float v;
    std::memcpy(&v, reinterpret_cast<const void*>(p), 4);
    return v;
}
u64 rdp(u64 p) {
    u64 v;
    std::memcpy(&v, reinterpret_cast<const void*>(p), 8);
    return v;
}

std::string floats(u64 p, int n) {
    std::string s = "[";
    char b[32];
    for (int i = 0; i < n; i++) {
        std::snprintf(b, sizeof b, "%s%.9g", i ? "," : "", rdf(p + 4 * i));
        s += b;
    }
    return s + "]";
}

// the parent object of a HierarchicalObject (its container +0xf0, the container's +0xe8), or 0
u64 parent_of(u64 obj) {
    u64 c = obj ? rdp(obj + 0xf0) : 0;
    return c ? rdp(c + 0xe8) : 0;
}

struct Dump {
    std::mutex mu;
    FILE* f = nullptr;
    int records = 0;
};

void record(Dump& d, const char* kind, Probe& p, Cpu& c) {
    u64 self = c.x(0), target = c.x(1);
    u64 def = rdp(self + 0x10);  // the definition: count at +0x12, axis mask at +0x10, sources' offsets from +0x34
    if (!self || !target || !def) return;
    u8 count = *reinterpret_cast<const u8*>(def + 0x12);
    u8 axes = *reinterpret_cast<const u8*>(def + 0x10);
    u64 list = rdp(self + 0x38);  // {object, weight} pairs, 16 bytes
    std::string before = floats(target + 0x40, 16);
    guest_call(p.orig, GuestArgs().p(reinterpret_cast<void*>(self)).p(reinterpret_cast<void*>(target)));
    char id[96];
    std::snprintf(id, sizeof id, "\"ms\":%lld,\"target\":\"%llx\",",
                  (long long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(),
                  (unsigned long long)target);
    std::string line = std::string("{") + id + "\"kind\":\"" + kind + "\",\"axes\":" + std::to_string(axes) +
                       ",\"offset\":" + floats(self + 0x44, 4) + ",\"before\":" + before +
                       ",\"after\":" + floats(target + 0x40, 16);
    u64 tp = parent_of(target);
    if (tp) line += ",\"target_parent\":" + floats(tp + 0x40, 16);
    line += ",\"sources\":[";
    for (u8 k = 0; k < count && list; k++) {
        u64 obj = rdp(list + 16 * k);
        float w = rdf(list + 16 * k + 8);
        line += std::string(k ? "," : "") + "{\"weight\":" + std::to_string(w) + ",\"offset\":" + floats(def + 0x34 + 0x30 * k, 3);
        if (obj) {
            line += ",\"world\":" + floats(obj + 0x40, 16) + ",\"local\":" + floats(obj + 0x80, 3);
            u64 pa = parent_of(obj);
            if (pa) line += ",\"parent\":" + floats(pa + 0x40, 16);
        }
        line += "}";
    }
    line += "]}\n";
    std::lock_guard lk(d.mu);
    if (d.f) {
        std::fputs(line.c_str(), d.f);
        d.records++;
    }
}

}  // namespace

NATIVE_TEST("anim/aaf-constraint-dump") {
    const char* path = env::env_str("SOA_AAF_CONSTRAINT_DUMP");
    if (!path || !*path) {
        fprintf(stderr, "anim/aaf-constraint-dump: SOA_AAF_CONSTRAINT_DUMP not set: nothing recorded\n");
        return;
    }
    if (!live_screen()) {
        fprintf(stderr, "anim/aaf-constraint-dump: not on a live screen: nothing animates\n");
        return;
    }
    static Dump d;
    d.f = std::fopen(path, "w");
    t.expect_eq(d.f != nullptr, true, "the dump file opens");
    if (!d.f) return;
    struct { Probe* p; const char* kind; } probes[] = {
        {&g_probeSetPoint, "point"}, {&g_probeSetOrient, "orient"},
        {&g_probeSetPointAxis, "point_axis"}, {&g_probeSetOrientAxis, "orient_axis"},
    };
    // up to 90 s or 600 records, the four in turn (a screen may use only some of them; orient comes
    // less often: it waits longer), at most 200 of a kind
    int per[4] = {0, 0, 0, 0};
    auto until = std::chrono::steady_clock::now() + std::chrono::seconds(90);
    for (int round = 0; std::chrono::steady_clock::now() < until && d.records < 600; round++) {
        int k = round % 4;
        if (per[k] >= 200) continue;
        auto& pr = probes[k];
        // the next 40 calls in a row (one frame's constraints come in the same order every frame: taking only
        // the first would see one target)
        int taken = 0;
        if (probe_call(t, *pr.p, [&](Cpu& c) {
                record(d, pr.kind, *pr.p, c);
                return ++taken >= 40;
            }, k == 1 ? 4000 : k == 0 ? 1000 : 300, pr.kind, false))
            per[k] += taken;
    }
    {
        std::lock_guard lk(d.mu);
        std::fclose(d.f);
        d.f = nullptr;
    }
    fprintf(stderr, "anim/aaf-constraint-dump: %d constraint evaluations recorded in %s\n", d.records, path);
}

}  // namespace soa::native::anim
