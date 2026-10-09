// Aska::Audio3DObject::UpdateMatrix and Aska::AudioListener::Compute (port/decomp/audio/mixer.c; the
// layouts in audio_layout.h): the 3D sound's listener and emitters follow scene nodes. The sound thread's
// Process3DEngine copies each node's world matrix into its object under the object's lock
// (UpdateMatrix, also from Audio3DEngine::UpdateAll3DObjectMatrix), and SoundProcessSync derives the
// listener's ear position and orientation from that copy (Compute). The math is Aska's (Vector::
// ApplyMatrix, Quaternion::Create: guest calls, native where the math subsystem replaced them).
#include <cmath>
#include <cstring>
#include <string>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/audio/audio_check.h"
#include "native/audio/audio_layout.h"
#include "native/common/arm_float.h"
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

// ---- Aska::AudioEmitter::Compute ----
//
// The order of operations and the comparisons are the disassembly's (no fused multiply-adds; the NaN
// cases as AArch64 has them: armf's arithmetic, FMAX / FMINNM below, the branch conditions written as
// the guest's flags take them). sqrt: FSQRT, and the libm's sqrtf when that gives a NaN; acosf, powf and
// sqrtf are the host's, as the runtime's libm HLE gives them to the guest.

namespace {

using armf::F;

// FMINNM: a quiet NaN operand loses to a number; a signalling one (or two NaNs) gives a NaN.
F minnm(F a, F b) {
    bool na = std::isnan(a.v), nb = std::isnan(b.v);
    if (na != nb && !armf::is_snan(a.v) && !armf::is_snan(b.v)) return na ? b : a;
    return F(armf::min(a.v, b.v));
}
F maxf(F a, F b) { return F(armf::max(a.v, b.v)); }
F sqrt_guest(F x) {
    float r = std::sqrt(x.v);
    return F(std::isnan(r) ? ::sqrtf(x.v) : r);
}
F fconst(u64 vaddr) { return F(*reinterpret_cast<const float*>(main_lib()->base + vaddr)); }
F dist(const Vector& p, const Vector& q) {
    F dx = F(p.x) - F(q.x), dy = F(p.y) - F(q.y), dz = F(p.z) - F(q.z);
    return sqrt_guest(dx * dx + dy * dy + dz * dz);
}
F curve_value(void* curve, F x) {
    const u64* vt = *reinterpret_cast<const u64* const*>(curve);
    GuestResult r = guest_call(vt[AudioEmitter::kSlotCurveValue], GuestArgs().p(curve).f(x.v));
    float v;
    std::memcpy(&v, &r.v0, 4);
    return F(v);
}

struct EmitterFns {
    u64 quaternion_create = guest::sym("_ZN4Aska10Quaternion6CreateEPKNS_6MatrixE");
    u64 matrix_create = guest::sym("_ZN4Aska6Matrix6CreateEPKNS_10QuaternionE");
    u64 invert = guest::sym("_ZNK4Aska6Matrix14InvertLowErrorEPS0_");
    u64 apply_no_transport = guest::sym("_ZN4Aska6Vector22ApplyMatrixNoTransportEPKNS_6MatrixE");
    u64 sound_manager = guest::sym("_ZN4Aska6Global15m_pSoundManagerE");
};
const EmitterFns& efns() {
    static const EmitterFns f;
    return f;
}

}  // namespace

void AudioEmitter::Compute() {
    const EmitterFns& fn = efns();
    const SoundManager* sm = *reinterpret_cast<SoundManager* const*>(fn.sound_manager);
    for (float& g : m_gains) g = 0.0f;
    alignas(16) Matrix m;
    base.m_cs.Enter();
    m = base.m_matrix;
    base.m_cs.Leave();
    const F px(m.m[0][3]), py(m.m[1][3]), pz(m.m[2][3]);
    alignas(16) Quaternion q;
    guest_call(fn.quaternion_create, {(u64)&q, (u64)&m});  // (its result isn't used)
    const Vector& L = sm->m_listener.m_position;
    F dx = F(L.x) - px, dy = F(L.y) - py, dz = F(L.z) - pz;
    const F d2 = dx * dx + dy * dy + dz * dz;
    const F distance = sqrt_guest(d2);
    // The near / far shares: all far beyond the outer radius, all near inside the inner one, between:
    // linear in the distance.
    F nearShare(0.0f), farShare(1.0f);
    const F outer(sm->m_outerRadius);
    if (outer * outer > d2) {  // (b.le not taken: ordered and greater)
        const F inner(sm->m_innerRadius);
        if (inner * inner < d2) {  // (b.pl not taken)
            F span = maxf(outer - inner, F(0.0f));
            F inv = F(1.0f) / span;
            F t = (span - (distance - inner)) * inv;
            nearShare = t < F(0.0f) ? F(0.0f) : minnm(t, F(1.0f));
            farShare = F(1.0f) - nearShare;
        } else {
            farShare = F(0.0f);
            nearShare = F(1.0f);
        }
    }
    alignas(16) Matrix listener, inverse, inv_copy;
    guest_call(fn.matrix_create, {(u64)&listener, (u64)&sm->m_listener.m_orientation});
    guest_call(fn.invert, {(u64)&listener, (u64)&inverse});
    inv_copy = inverse;
    alignas(16) Vector v = {(px - F(L.x)).v, (py - F(L.y)).v, (pz - F(L.z)).v, 1.0f};
    guest_call(fn.apply_no_transport, {(u64)&v, (u64)&inv_copy});
    // The angle of the source around the listener's up axis (in the listener's frame: x, z), 0..2pi.
    const F eps = fconst(kEmitterEpsilon), two_pi = fconst(kEmitterTwoPi);
    F angle(0.0f), far = F(0.0f), near = F(1.0f);
    F vx(v.x), vz(v.z);
    if (!(std::fabs(vx.v) < eps.v) || !(std::fabs(vz.v) < eps.v)) {
        F len = sqrt_guest(vx * vx + F(0.0f) + vz * vz);
        if (!(len < eps)) {
            F inv = F(1.0f) / len;
            vx = inv * vx;
            vz = inv * vz;
        }
        F c = vz < F(-1.0f) ? F(-1.0f) : minnm(vz, F(1.0f));
        F a(::acosf(c.v));
        F a2 = vx > F(0.0f) ? two_pi - a : a;
        if (!(a2 < F(0.0f))) angle = minnm(a2, two_pi);
        near = nearShare;
        far = farShare;
    }
    // The far share between the two speakers whose angles bracket the source's.
    const float* t = sm->m_speakerAngles;
    if (far >= eps) {  // (b.lt: an unordered share skips)
        int lo, hi;
        if (angle < F(t[2])) lo = 2, hi = 2;
        else if (angle < F(t[0])) lo = 2, hi = 0;
        else if (angle < F(t[4])) lo = 0, hi = 4;
        else if (angle < F(t[5])) lo = 4, hi = 5;
        else if (angle < F(t[1])) lo = 5, hi = 1;
        else lo = 1, hi = 1;
        if (lo == hi) hi = 2;
        F top = hi == 2 ? F(t[hi]) + two_pi : F(t[hi]);
        F frac = (angle - F(t[lo])) / (top - F(t[lo]));
        frac = frac < F(0.0f) ? F(0.0f) : minnm(frac, F(1.0f));
        m_gains[lo] = (F(m_gains[lo]) + far * (F(1.0f) - frac)).v;
        m_gains[hi] = (F(m_gains[hi]) + far * frac).v;
    }
    // The near share over five speakers by inverse distance.
    if (near >= eps) {
        const Vector& P = v;
        F i2 = F(1.0f) / dist(P, sm->m_speakers[2]);
        F sum = i2 + F(0.0f);
        F i0 = F(1.0f) / dist(P, sm->m_speakers[0]);
        sum = sum + i0;
        F i4 = F(1.0f) / dist(P, sm->m_speakers[4]);
        sum = sum + i4;
        F i5 = F(1.0f) / dist(P, sm->m_speakers[5]);
        sum = sum + i5;
        F i1 = F(1.0f) / dist(P, sm->m_speakers[1]);
        F norm = F(1.0f) / (sum + i1);
        F g2 = F(m_gains[2]) + near * (norm * i2), g4 = F(m_gains[4]) + near * (norm * i4), g5 = F(m_gains[5]) + near * (norm * i5);
        F g0 = F(m_gains[0]) + near * (norm * i0), g1 = F(m_gains[1]) + near * (norm * i1);
        m_gains[1] = g1.v, m_gains[2] = g2.v, m_gains[0] = g0.v, m_gains[4] = g4.v, m_gains[5] = g5.v;
    }
    // The two attenuation curves and the master volume.
    F unit(sm->m_distanceUnit), range(m_rangeScale);
    F c1 = curve_value(sm->m_listenerCurve, distance / (F(sm->m_listenerRange) * unit * range));
    F c2 = curve_value(m_curve, distance / (F(m_distanceScale) * unit * range));
    F att = c1 * c2;
    F vol(0.0f);
    if (!(F(sm->m_volumeDb) <= fconst(kEmitterSilentDb))) vol = F(::powf(10.0f, (F(sm->m_volumeDb) * fconst(kEmitterDbScale)).v)) * fconst(kEmitterVolumeScale);
    F k = att * vol;
    for (int i : {0, 1, 2, 4, 5}) m_gains[i] = (k * F(m_gains[i])).v;
    m_computed = 1;
}

// ---- The live check (audio_check.h) ----
//
// Both are pure functions of the object's node (its world matrix now) or its matrix copy: the native for
// real, then the guest original and the native again, each on a shadow of the object (its lock free);
// the two shadows must agree. (A real object that differs from them only means the node moved
// meanwhile; it isn't compared.)

namespace {

CheckedFn g_update("_ZN4Aska13Audio3DObject12UpdateMatrixEv"), g_compute("_ZN4Aska13AudioListener7ComputeEv"),
    g_emitter("_ZN4Aska12AudioEmitter7ComputeEv");

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
    static FastCriticalSection& cs_of(AudioEmitter& o) { return o.base.m_cs; }
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
void emitter_checked(Cpu& c) {
    pure_checked<AudioEmitter, &AudioEmitter::Compute, offsetof(AudioEmitter, m_gains), offsetof(AudioEmitter, m_computed) + 1>(c, g_emitter);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska13Audio3DObject12UpdateMatrixEv", update_checked, "audio: Aska::Audio3DObject::UpdateMatrix", &g_update.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska13AudioListener7ComputeEv", compute_checked, "audio: Aska::AudioListener::Compute", &g_compute.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12AudioEmitter7ComputeEv", emitter_checked, "audio: Aska::AudioEmitter::Compute", &g_emitter.orig);

}  // namespace soa::native::audio
