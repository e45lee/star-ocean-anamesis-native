// Differential tests of Audio3DObject::UpdateMatrix and AudioListener::Compute (audio_3d.cpp): private
// objects built by the guest's AudioListener constructor, a fake scene node whose world matrix (vtable
// slot 19, a fake function) is random, or no node; the guest functions on one copy, the natives on
// another; the matrices, ear positions and orientations compared bit for bit.
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
