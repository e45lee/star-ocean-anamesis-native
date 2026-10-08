// Aska::Audio3DObject::UpdateMatrix and Aska::AudioListener::Compute (port/decomp/audio/mixer.c; the
// layouts in audio_layout.h): the 3D sound's listener and emitters follow scene nodes. The sound thread's
// Process3DEngine copies each node's world matrix into its object under the object's lock
// (UpdateMatrix, also from Audio3DEngine::UpdateAll3DObjectMatrix), and SoundProcessSync derives the
// listener's ear position and orientation from that copy (Compute). The math is Aska's (Vector::
// ApplyMatrix, Quaternion::Create: guest calls, native where the math subsystem replaced them).
#include <cstring>
#include <string>

#include "core/cpu.h"
#include "native/audio/audio_check.h"
#include "native/audio/audio_layout.h"
#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/common/native_method.h"

namespace soa::native::audio {

namespace {

const Matrix kIdentity = {{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};

u64 apply_matrix_fn() {
    static const u64 f = guest::sym("_ZNK4Aska6Vector11ApplyMatrixEPS0_PKNS_6MatrixE");
    return f;
}
u64 quaternion_create_fn() {
    static const u64 f = guest::sym("_ZN4Aska10Quaternion6CreateEPKNS_6MatrixE");
    return f;
}

}  // namespace

void Audio3DObject::UpdateMatrix() {
    m_cs.Enter();
    if (!m_node) {
        m_matrix = kIdentity;
    } else {
        const u64* vt = *reinterpret_cast<const u64* const*>(m_node);
        const auto* world = reinterpret_cast<const Matrix*>(guest_call(vt[kSlotNodeWorldMatrix], {(u64)m_node}));
        std::memcpy(&m_matrix, world, sizeof m_matrix);
    }
    m_cs.Leave();
}

void AudioListener::Compute() {
    base.m_cs.Enter();
    Matrix m = base.m_matrix;
    base.m_cs.Leave();
    alignas(16) Vector ear = {0.0f, 0.0f, m_offsetZ, 1.0f};
    guest_call(apply_matrix_fn(), {(u64)&ear, (u64)&m_position, (u64)&m});
    guest_call(quaternion_create_fn(), {(u64)&m_orientation, (u64)&m});
}

// ---- The live check (audio_check.h) ----
//
// Both are pure functions of the object's node (its world matrix now) or its matrix copy: the native for
// real, then the guest original and the native again, each on a shadow of the object (its lock free);
// the two shadows must agree. (A real object that differs from them only means the node moved
// meanwhile; it isn't compared.)

namespace {

CheckedFn g_update("_ZN4Aska13Audio3DObject12UpdateMatrixEv"), g_compute("_ZN4Aska13AudioListener7ComputeEv");

template <typename T>
struct ShadowOf {
    alignas(16) T obj;
    explicit ShadowOf(const T& real) {
        std::memcpy(&obj, &real, sizeof obj);
        FastCriticalSection& cs = cs_of(obj);
        cs.m_lock = FastCriticalSection::kFree;
        cs.m_waiters = FastCriticalSection::kWaiterBias;
    }
    static FastCriticalSection& cs_of(Audio3DObject& o) { return o.m_cs; }
    static FastCriticalSection& cs_of(AudioListener& o) { return o.base.m_cs; }
};

template <typename T, void (T::*M)(), size_t kFrom, size_t kTo>
void pure_checked(Cpu& c, CheckedFn& f) {
    auto* self = reinterpret_cast<T*>(c.x(0));
    (self->*M)();
    if (!live::check_due(f)) return;
    live::CheckScope scope;
    std::string why;
    for (int attempt = 0; attempt < 2; attempt++) {
        ShadowOf<T> g(*self), n(*self);
        guest_call(f.orig, {(u64)&g.obj});
        (n.obj.*M)();
        why = live::diff_bytes((const u8*)&n.obj, (const u8*)&g.obj, kFrom, kTo);
        if (why.empty()) break;
    }
    live::check_result(f, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}
void update_checked(Cpu& c) {
    pure_checked<Audio3DObject, &Audio3DObject::UpdateMatrix, offsetof(Audio3DObject, m_matrix), sizeof(Audio3DObject)>(c, g_update);
}
void compute_checked(Cpu& c) {
    pure_checked<AudioListener, &AudioListener::Compute, offsetof(AudioListener, m_position), sizeof(AudioListener)>(c, g_compute);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska13Audio3DObject12UpdateMatrixEv", update_checked, "audio: Aska::Audio3DObject::UpdateMatrix", &g_update.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska13AudioListener7ComputeEv", compute_checked, "audio: Aska::AudioListener::Compute", &g_compute.orig);

}  // namespace soa::native::audio
