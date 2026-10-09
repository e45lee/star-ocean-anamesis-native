// Differential tests of Audio3DObject::UpdateMatrix and AudioListener::Compute (audio_3d.cpp): private
// objects built by the guest's AudioListener constructor, a fake scene node whose world matrix (vtable
// slot 19, a fake function) is random, or no node; the guest functions on one copy, the natives on
// another; the matrices, ear positions and orientations compared bit for bit.
#include <cmath>
#include <cstdio>
#include <cstring>

#include "core/cpu.h"
#include "native/audio/audio_layout.h"
#include "native/common/guest_stub.h"
#include "native/common/test.h"

using namespace soa;
using namespace soa::native;
using namespace soa::native::audio;

NATIVE_TEST("audio/3d-listener") {
    static const u64 fWorld = fake_function("audio.t.world-matrix", 1);
    alignas(16) u64 node_vtable[32] = {};
    node_vtable[Audio3DObject::kSlotNodeWorldMatrix] = fWorld;
    alignas(16) u64 node[4] = {(u64)node_vtable, 0, 0, 0};
    alignas(16) Matrix world;
    StubSession ss;
    ss.only = {"audio.t.world-matrix"};
    ss.behave["audio.t.world-matrix"] = [&](Cpu& c) { c.set_x(0, (u64)&world); };
    for (int i = 0; i < 300 && !t.failures(); i++) {
        alignas(16) AudioListener g, n;
        std::memset((void*)&g, 0, sizeof g);
        t.call("_ZN4Aska13AudioListenerC1Ev", {(u64)&g});
        // a random rotation-ish matrix with a translation, or random values
        for (auto& row : world.m)
            for (float& v : row) v = (float)t.rand_int(-2000, 2000) / 1000.0f;
        if (i % 3 == 0) {
            world.m[3][0] = world.m[3][1] = world.m[3][2] = 0.0f;
            world.m[3][3] = 1.0f;
        }
        g.m_offsetZ = (float)t.rand_int(-100, 100) / 10.0f;
        g.base.m_node = i % 7 == 0 ? nullptr : node;
        std::memcpy((void*)&n, &g, sizeof g);
        t.call("_ZN4Aska13Audio3DObject12UpdateMatrixEv", {(u64)&g});
        n.base.UpdateMatrix();
        if (std::memcmp(&g.base.m_matrix, &n.base.m_matrix, sizeof(Matrix)) != 0) t.fail("UpdateMatrix %d: the matrices differ", i);
        t.call("_ZN4Aska13AudioListener7ComputeEv", {(u64)&g});
        n.Compute();
        if (std::memcmp(&g.m_position, &n.m_position, sizeof(Vector)) != 0) t.fail("Compute %d: the positions differ", i);
        if (std::memcmp(&g.m_orientation, &n.m_orientation, sizeof(Quaternion)) != 0) t.fail("Compute %d: the orientations differ", i);
        if (n.base.m_cs.m_lock != FastCriticalSection::kFree) t.fail("lock left held");
        t.call("_ZN4Aska19FastCriticalSectionD1Ev", {(u64)&g.base.m_cs});
    }
}

// AudioEmitter::Compute: private emitters (the guest's constructor) placed around the live listener (the
// sound manager's: read only, the sound thread owns it) at distances across its inner and outer radii, in
// every direction (also on its up axis: no angle), with random distance scales; the emitter's curve is a
// fake (slot 15: a fake function, x -> x * 0.75 + 0.125, or NaN now and then); the listener's is the live
// one. The guest's and the native's gains (and the flag) compared bit for bit; a difference that a second
// run of both doesn't repeat is the sound thread moving the listener meanwhile (none expected at the title).
NATIVE_TEST("audio/3d-emitter") {
    const auto* sm = *reinterpret_cast<SoundManager* const*>(t.sym("_ZN4Aska6Global15m_pSoundManagerE"));
    if (!sm || !sm->m_listenerCurve) {
        t.fail("the sound manager (or its listener curve) isn't up");
        return;
    }
    static const u64 fCurve = fake_function("audio.t.emitter-curve", 1, 1);
    alignas(16) u64 curve_vtable[32] = {};
    curve_vtable[AudioEmitter::kSlotCurveValue] = fCurve;
    alignas(16) u64 curve[2] = {(u64)curve_vtable, 0};
    bool nan_curve = false;
    StubSession ss;
    ss.only = {"audio.t.emitter-curve"};
    ss.behave["audio.t.emitter-curve"] = [&](Cpu& c) {
        float x = c.s(0), r = nan_curve ? NAN : x * 0.75f + 0.125f;
        u32 b;
        std::memcpy(&b, &r, 4);
        c.set_v(0, V128{b, 0});
    };
    const Vector L = sm->m_listener.m_position;
    const float outer = sm->m_outerRadius > 0 ? sm->m_outerRadius : 10.0f;
    fprintf(stderr, "    listener (%g, %g, %g), radii %g / %g, unit %g, volume %g dB\n", L.x, L.y, L.z, sm->m_innerRadius, sm->m_outerRadius,
            sm->m_distanceUnit, sm->m_volumeDb);
    int nonzero = 0;
    for (int i = 0; i < 2000 && !t.failures(); i++) {
        alignas(16) AudioEmitter g;
        std::memset((void*)&g, 0, sizeof g);
        t.call("_ZN4Aska12AudioEmitterC1Ev", {(u64)&g});
        for (auto& row : g.base.m_matrix.m)
            for (float& v : row) v = (float)t.rand_int(-1000, 1000) / 1000.0f;
        float r = outer * (float)t.rand_int(0, 2000) / 1000.0f;
        float dx = (float)t.rand_int(-1000, 1000), dy = (float)t.rand_int(-1000, 1000), dz = (float)t.rand_int(-1000, 1000);
        int kind = t.rand_int(0, 19);
        if (kind == 0) dx = dz = 0;            // on the up axis
        if (kind == 1) dx = dy = dz = 0;       // at the listener
        float len = std::sqrt(dx * dx + dy * dy + dz * dz);
        if (len > 0) dx = dx / len * r, dy = dy / len * r, dz = dz / len * r;
        g.base.m_matrix.m[0][3] = L.x + dx;
        g.base.m_matrix.m[1][3] = L.y + dy;
        g.base.m_matrix.m[2][3] = L.z + dz;
        if (kind == 2) g.base.m_matrix.m[0][3] = NAN;
        g.m_distanceScale = (float)t.rand_int(1, 2000);
        g.m_rangeScale = (float)t.rand_int(1, 30) / 10.0f;
        g.m_curve = curve;
        nan_curve = kind == 3;
        bool same = false;
        for (int attempt = 0; attempt < 2 && !same; attempt++) {
            alignas(16) AudioEmitter a = g, b = g;  // (bytewise copies: only g's lock is destroyed)
            t.call("_ZN4Aska12AudioEmitter7ComputeEv", {(u64)&a});
            b.Compute();
            same = std::memcmp(a.m_gains, b.m_gains, sizeof a.m_gains) == 0 && a.m_computed == b.m_computed;
            if (!same && attempt == 1) {
                t.fail("emitter %d (kind %d, r %g): the gains differ", i, kind, r);
                for (int k = 0; k < AudioEmitter::kSpeakers; k++)
                    if (std::memcmp(&a.m_gains[k], &b.m_gains[k], 4)) t.fail("  gain %d: guest %.9g native %.9g", k, a.m_gains[k], b.m_gains[k]);
            }
            if (same) for (float v : b.m_gains) nonzero += v != 0.0f;
            if (b.base.m_cs.m_lock != FastCriticalSection::kFree) t.fail("lock left held");
        }
        t.call("_ZN4Aska19FastCriticalSectionD1Ev", {(u64)&g.base.m_cs});
    }
    fprintf(stderr, "    %d nonzero gains\n", nonzero);
}
