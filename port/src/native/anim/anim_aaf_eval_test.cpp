// anim/aaf-eval-dump: the guest's own keyframe evaluation, recorded for tools/aafdump --verify (the
// proof that soa_models' evaluator, soa/aaf.h, gives the game's values bit for bit; docs/notes.md
// "Animations (AAF) for tools").
//
// On a live screen (port/scripts/selftest_live.sh SOA OUT TMP anim/aaf-eval --at home|battle) a probe
// on Aska::AafHandler::SetValues / BlendValues takes the handlers the game evaluates. For each new
// animation file the test copies the file from guest memory and calls every keyframe controller's
// CalcValue(out, t) (vtable slot 12) at a fixed set of frames: forward through the keyed range and
// past both ends (the out-of-range modes), every key time and the midpoints, and pseudo-random
// jumps back and forth (the controllers keep their current interval: the search must give the
// same value from anywhere). Each output buffer starts as 0x7fbadbad in all four words, so the
// components a controller leaves alone are visible. It writes SOA_AAF_EVAL_DUMP/<n>.aafeval:
//   "AAFEVAL2", u32 file size, the file, u32 records, then per record
//   {u32 controller header offset, u32 call, f32 frame, u32 out[4]}: call 0 CalcValue(out, frame);
// for the constant controllers (the header's +5 bit 7: their one value is kept in the controller's
// slots, the game reads it with CalcValueConstant(out, i), vtable slot 41) call 1 / 2 is
// CalcValueConstant(out, 0 / 1) (frame 0).
// The guest's controllers are the game's: a probed handler's next frame recomputes its values (the
// controllers search their interval from wherever they are). Without SOA_AAF_EVAL_DUMP, or at the
// title (no animation), the test notes it and passes.
#include <soa/env.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include "native/anim/anim_layout.h"
#include "native/common/test.h"
#include "native/render/render_test_util.h"

namespace soa::native::anim {
namespace {

using namespace render::testutil;

TEST_PROBE(g_probeEvalSet, "_ZN4Aska10AafHandler9SetValuesEf");
TEST_PROBE(g_probeEvalBlend, "_ZN4Aska10AafHandler11BlendValuesEff");

u32 rd32u(const u8* p) {
    u32 v;
    std::memcpy(&v, p, 4);
    return v;
}
float rdfu(const u8* p) {
    float v;
    std::memcpy(&v, p, 4);
    return v;
}

// The frames a controller is evaluated at (deterministic: the same on every run).
std::vector<float> frames_for(const u8* kf) {
    float s0 = rdfu(kf + 0xc), s1 = rdfu(kf + 0x10);
    u32 n = rd32u(kf + 0x14);
    float len = s1 - s0;
    std::vector<float> f;
    float span = len > 0 ? len : 10.0f;
    for (float t = s0 - span * 0.5f; t <= s1 + span * 0.5f; t += span / 97.0f) f.push_back(t);
    for (u32 i = 0; i < n && i < 512; i++) {
        float k = rdfu(kf + 0x18 + i * 4);
        f.push_back(k);
        if (i + 1 < n) f.push_back((k + rdfu(kf + 0x18 + (i + 1) * 4)) * 0.5f);
    }
    u32 r = 12345;
    for (int i = 0; i < 64; i++) {
        r = r * 1103515245u + 12345u;
        f.push_back(s0 - span * 2.0f + span * 5.0f * (float)((r >> 8) & 0xffff) / 65535.0f);
    }
    f.push_back(s0);
    f.push_back(s1);
    f.push_back(s0 - span * 3.25f);
    f.push_back(s1 + span * 3.25f);
    return f;
}

struct Recorder {
    std::mutex mu;
    std::set<const void*> seen;
    std::string dir;
    int files = 0;
    long records = 0;
};

// One handler: its file and every keyframe controller's values. Runs on the calling (worker) thread
// before the guest's SetValues.
void record_handler(TestContext& t, Recorder& rec, const AafHandler* h) {
    const u8* file = static_cast<const u8*>(h->m_file);
    if (!file || !h->m_infos || !(h->m_flags & 2)) return;
    {
        std::lock_guard lk(rec.mu);
        if (!rec.seen.insert(file).second) return;
    }
    u32 size = rd32u(file + 4);
    if (size < 0x40 || size > (64u << 20)) return;
    std::vector<u8> out;
    auto put32 = [&](u32 v) { out.insert(out.end(), (u8*)&v, (u8*)&v + 4); };
    out.insert(out.end(), (const u8*)"AAFEVAL2", (const u8*)"AAFEVAL2" + 8);
    put32(size);
    out.insert(out.end(), file, file + size);
    size_t count_at = out.size();
    put32(0);
    u32 nrec = 0;
    for (u32 i = 0; i < h->m_controllerCount; i++) {
        const AafControllerInfo& in = h->m_infos[i];
        if (!in.m_controller || !in.m_header || !in.m_keyHeader) continue;
        if (in.m_header[0] > 3) continue;  // keyframe controllers only (SetController's LocalSetController)
        u64 vt = *reinterpret_cast<const u64*>(in.m_controller);
        u64 calc = *reinterpret_cast<const u64*>(vt + 12 * 8);      // CalcValue(void*, float)
        u64 calc_const = *reinterpret_cast<const u64*>(vt + 41 * 8);  // CalcValueConstant(void*, int)
        u32 off = (u32)(in.m_header - file);
        if (off >= size) continue;
        auto record = [&](u32 call, float f, const u32 val[4]) {
            put32(off);
            put32(call);
            u32 fb;
            std::memcpy(&fb, &f, 4);
            put32(fb);
            for (int k = 0; k < 4; k++) put32(val[k]);
            nrec++;
        };
        if (in.m_header[5] & 0x80) {
            for (u32 idx = 0; idx < 2; idx++) {
                alignas(16) u32 val[4] = {0x7fbadbad, 0x7fbadbad, 0x7fbadbad, 0x7fbadbad};
                guest_call(calc_const, GuestArgs().p(in.m_controller).p(val).i(idx));
                record(1 + idx, 0.0f, val);
            }
            continue;
        }
        for (float f : frames_for(in.m_keyHeader)) {
            alignas(16) u32 val[4] = {0x7fbadbad, 0x7fbadbad, 0x7fbadbad, 0x7fbadbad};
            guest_call(calc, GuestArgs().p(in.m_controller).p(val).f(f));
            record(0, f, val);
        }
    }
    std::memcpy(&out[count_at], &nrec, 4);
    int n;
    {
        std::lock_guard lk(rec.mu);
        n = rec.files++;
        rec.records += nrec;
    }
    std::string path = rec.dir + "/" + std::to_string(n) + ".aafeval";
    if (FILE* fp = std::fopen(path.c_str(), "wb")) {
        std::fwrite(out.data(), 1, out.size(), fp);
        std::fclose(fp);
    } else {
        t.expect_eq(true, false, ("cannot write " + path).c_str());
    }
}

}  // namespace

NATIVE_TEST("anim/aaf-eval-dump") {
    const char* dir = env::env_str("SOA_AAF_EVAL_DUMP");
    if (!dir || !*dir) {
        fprintf(stderr, "anim/aaf-eval-dump: SOA_AAF_EVAL_DUMP not set: nothing recorded\n");
        return;
    }
    static Recorder rec;
    rec.dir = dir;
    if (!live_screen()) {
        fprintf(stderr, "anim/aaf-eval-dump: not on a live screen: nothing animates\n");
        return;
    }
    // Take handlers for up to 40 s (or 48 files): SetValues and BlendValues both start a handler's frame.
    auto until = std::chrono::steady_clock::now() + std::chrono::seconds(40);
    int rounds = 0;
    while (std::chrono::steady_clock::now() < until && rec.files < 48) {
        Probe& p = (rounds++ & 1) ? g_probeEvalBlend : g_probeEvalSet;
        probe_call(t, p, [&](Cpu& c) {
            record_handler(t, rec, reinterpret_cast<const AafHandler*>(c.x(0)));
            return true;
        }, 3000, "AafHandler::SetValues / BlendValues", false);
    }
    fprintf(stderr, "anim/aaf-eval-dump: %d animation files, %ld values recorded in %s\n", rec.files, rec.records, dir);
    t.expect_eq(rec.files > 0, true, "at least one animation recorded");
}

}  // namespace soa::native::anim
